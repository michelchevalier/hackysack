/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 */

/* "Style" guide. Try to use const strings everywhere. Avoid use of string functions. Minimize use of malloc and friends.
 * Don't do anything CPU intensive during normal operation. Leave to the sysadmin or the user's browser. If you must,
 * do it at initialization.
 * Try to "fold ifs back in" -- don't make the "else" clause the normal or nominal code-path. This makes for less nested code.
 * Don't cuddle 'else's.
 * Tabs are four spaces.
 * There's a space after keywords and commas.
 */

#include "fs.h"
#include "default_config.h"

int main(int argc, char *argv[])
{
    memory_overhead = (memory_limit / 16)   // for the stack used during the initial recursive mmap
        + max_path;                         // for the maximum path length used during initial mmap
    mmap_files();
}
