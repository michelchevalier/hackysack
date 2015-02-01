/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "misc.h"
#include "default_config.h"

void debug_mesg(error_type type, char *fmt, ...)
{
    char *err_str;
    va_list argp;
    int esc = 0;
    FILE *fp = stderr;

    if (debug < type) {
        return;
    }

    va_start(argp, fmt);
    do {
        switch (*fmt) {
            case '%':   esc = 1; break;
            case 's':   if (esc) { char *s = va_arg(argp, char *);
                                   fputs(s, fp);
                                   esc = 0;
                                   break;
                                 } 
            default:    { fputc(*fmt, fp);
                          esc = 0;
                        }
                        break;
        }
    } while(*fmt++);
    va_end(argp);
}

size_t safe_strnlen(const char *s, size_t n)
{
    if (s) {
        return strnlen(s, n);
    }
    else {
        return 0;
    }
}
