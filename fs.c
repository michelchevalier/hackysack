/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "misc.h"
#include "stack.h"
#include "fs.h"
#include "trie.h"
#include "default_config.h"

size_t trienodesize = sizeof(trienode);

int check_gz(char *path)
{
    int fd;
    size_t red;
    unsigned char magic[2];
    fd = open(path, O_RDONLY | O_NOFOLLOW);
    if (fd < 0) {
        debug_mesg(ERROR, "Could not open: %s\n", path);
        return 0;
    }
    red = read(fd, (void *)magic, 2);
    if (red != 2) {
        debug_mesg(WARNING, "Could not read gzip magic from: %s\n", path);
        return 0;
    }
    if (!(magic[0] == 0x1f) || !(magic[1] == 0x8b)) {
        return 0;
    }
    return 1;
}

int mmap_files()
{
    DIR *current_dirh;
    struct dirent *entry;
    char *stack, *stack_ptr, *stack_ptr_tmp, *eos;
    char *current_path, *next_dir;
    size_t current_path_length, next_dir_length;
    trienode *trietop;
    
    size_t stack_size = memory_limit / 16;
    stack = (char *)calloc(1, stack_size); // Most memory limits will be divisible by 2^4 I guess.
    if (!stack) {
        debug_mesg(ERROR, "Unable to allocate memory for stack. Check configured limit.\n");
        exit(EX_OSERR);
    }
    stack_ptr = stack;
    eos = stack + stack_size;
    trietop = (trienode *)calloc(1, trienodesize);
    if (!trietop) {
        debug_mesg(ERROR, "Unable to allocate memory for trie. Check configured limit.\n");
        exit(EX_OSERR);
    }

    current_path = (char *)malloc(max_path); // Don't strictly need all of this.
    if (!current_path) {
        debug_mesg(ERROR, "Unable to allocate memory for maximum path name.\n");
        exit(EX_OSERR);
    }
    current_path_length = safe_strnlen(htdocs_name, max_path - 1);
    if ((current_path_length == max_path) || !current_path_length) {
        debug_mesg(ERROR, "Could not process base directory: %s\n", htdocs_name);
        exit(EX_OSERR);
    }
    memcpy((void *)current_path, htdocs_name, current_path_length);

    do {
        current_path[current_path_length] = '/';
        current_path[current_path_length + 1] = 0;
        current_path_length++;
        debug_mesg(INFO, "Scanning directory: %s\n", current_path);
        current_dirh = opendir(current_path);
        if (!current_dirh) {
            debug_mesg(ERROR, "Could not open directory %s. Aborting scan.\n", current_path);
            break;
        }

        while((entry = readdir(current_dirh)))
        {
            if (entry->d_name[0] == '.') {
                continue;
            }
            switch(entry->d_type) {
                case DT_DIR:
                     /* append current_path + new_entry onto recurse list.
                     */
                    if (current_path_length + safe_strnlen(entry->d_name, 256) > max_path - 1) {
                        debug_mesg(WARNING, "Skipping too-long path: %s/%s\n", current_path, entry->d_name);
                    }
                    stack_ptr_tmp = STACKCAT(stack_ptr, current_path, entry->d_name, eos);
                    if (stack_ptr_tmp) {
                        stack_ptr = stack_ptr_tmp;
                    }
                    else {
                        debug_mesg(WARNING, "Not enough memory to recurse: %s/%s\n", current_path, entry->d_name);
                    }
                    break;
                case DT_REG:
                    /* If file, check if .gz or .tag */
                    
                    stack_ptr_tmp = STACKCAT(stack_ptr, current_path, entry->d_name, eos);
                    if (!stack_ptr_tmp) {
                        debug_mesg(WARNING, "Unable to process file: %s/%s\n", current_path, entry->d_name);
                        continue;
                    }
                    debug_mesg(INFO, "Found file: %s\n", stack_ptr);
                    if (!STACKCMP(stack_ptr_tmp - 4, ".gz", eos)) {
                        if (!check_gz(stack_ptr)) {
                            debug_mesg(WARNING, "Skipping: %s since it's not a valid gzip.\n", stack_ptr);
                            continue;
                        }
                        printf("%d\n", trie_add_string(trietop, stack_ptr, 1));
                    }
                    else if (!STACKCMP(stack_ptr_tmp - 5, ".tag", eos)) {
                    }
                    else {
                        debug_mesg(WARNING, "Skipping: %s since it doesn't end in gz\n", stack_ptr);
                        continue;
                    }
                    break;
                default: break;
            }
        }
        if (!entry && errno) { // entry = readdir() returned NULL because there was an error
            debug_mesg(ERROR, "readdir() failed on %s.\n", current_path);
        }
        if (current_dirh && (closedir(current_dirh) < 0)) {
            debug_mesg(ERROR, "unable to close directory handle on %s\n", current_path);
            exit(EX_OSERR);
        }
        if (stack_ptr > stack) { // There are still directories to scan.
            next_dir = STACK_POP(stack_ptr, stack);
            if (!next_dir) {
                debug_mesg(ERROR, "Internal error: unable to scan directories.");
                exit(EX_SOFTWARE);
            }
            stack_ptr = next_dir;
            next_dir_length = safe_strnlen(next_dir, max_path);
            if (next_dir_length) {
                memcpy(current_path, next_dir, next_dir_length);
                current_path_length = next_dir_length;
            }
            else {
                debug_mesg(ERROR, "Internal error: unable to scan directories.");
                exit(EX_SOFTWARE);
            }
        }
        else {
            current_dirh = NULL; // Is this the end, my Friend?
        }
    } while (current_dirh);
    free((char *)stack);
    free((char *)current_path);
    return 0;
}
