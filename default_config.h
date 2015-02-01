/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 *
 * Default startup configuration.
 */

#include <stddef.h>

#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

extern char *htdocs_name;
extern int debug;
extern size_t memory_limit;
extern size_t memory_overhead;
extern size_t max_path;
extern int maplocked;

#endif
