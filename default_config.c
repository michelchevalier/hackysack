/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 */

#include <stddef.h>

char *htdocs_name = "./public_html";
int debug = 3; /* 0 disabled. 1 +err. 2 +warn. 3 +info. */
size_t memory_limit = 1048576;
size_t memory_overhead = 0;
size_t max_path = 1024;
int maplocked = 1;
