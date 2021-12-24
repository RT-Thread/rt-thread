/* posix_getline.h
 * RT-Thread POSIX
 * getdelim(), getline() - read a delimited record from stream, ersatz implementation
 * This code is unlicensed -- free and released into the public domain.
 * https://man7.org/linux/man-pages/man3/getline.3.html
 * Authors:
 *     https://github.com/ivanrad/getline
 *
 * Meco Man    2020-09-03    porting to RT-Thread
 */


#ifndef POSIX_GETLINE_H
#define POSIX_GETLINE_H

#include <stdio.h>
#include <sys/types.h>

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

#endif /* POSIX_GETLINE_H */

