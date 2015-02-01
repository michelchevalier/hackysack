/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 * 
 * mmap() files from disk into memory, index in a hash.
 */

#ifndef FS_H
#define FS_H

/* check_gz: Look for the gzip magic bytes in a file
 * path: string containing path to potential gzip
 * RETURNS: 0 if not a gzip, 1 if a valid gzip
 */
int check_gz(char *path);

/* mmap_files: 
 * RETURNS: Nothing
 */
int mmap_files();

#endif
