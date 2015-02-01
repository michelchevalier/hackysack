/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 *
 * a self-sizing hash.
 */

#include <stdint.h>

#ifndef HASH_H
#define HASH_H

typedef struct _resource {
    char *path;
    char *data;
    struct _resource *next;
} resource;

inline uint32_t HASH(char *key);
#endif
