/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 *
 * stack functions for stack local use within single-threaded function. consume popped items before any other pushes.
 */

#include "hash.h"

inline uint32_t HASH(char *key)
{
    if (!key) {
        return UINT32_MAX;
    }
    uint32_t hash = 2166136261UL;
    do
    {
        hash ^= (uint8_t)(*key);
        hash *= 16777619L;
    }
    while((uint8_t)(*++key) != '\0');
    return hash;
}
