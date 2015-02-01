/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 * 
 * Miscellaneous functions which don't belong elsewhere.
 */

#ifndef MISC_H
#define MISC_H

typedef enum { ERROR = 1, WARNING = 2, INFO = 3 } error_type;
void debug_mesg(error_type type, char *fmt, ...);
size_t safe_strnlen(const char *s, size_t n);

#endif
