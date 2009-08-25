/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: codeclib.h 19704 2009-01-07 09:53:46Z zagor $
 *
 * Copyright (C) 2005 Dave Chapman
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#ifndef __CODECLIB_H__
#define __CODECLIB_H__
#include "ffmpeg_config.h"
// #include "codecs.h"
// #include <sys/types.h>

extern struct codec_api *ci;
extern size_t mem_ptr;
extern size_t bufsize;
extern unsigned char* mp3buf;     /* The actual MP3 buffer from Rockbox                 */
extern unsigned char* mallocbuf;  /* The free space after the codec in the codec buffer */
extern unsigned char* filebuf;    /* The rest of the MP3 buffer                         */

/* Standard library functions that are used by the codecs follow here */

/* Get these functions 'out of the way' of the standard functions. Not doing
 * so confuses the cygwin linker, and maybe others. These functions need to
 * be implemented elsewhere */
#define malloc(x) codec_malloc(x)
#define calloc(x,y) codec_calloc(x,y)
#define realloc(x,y) codec_realloc(x,y)
#define free(x) codec_free(x)
#define alloca(x) __builtin_alloca(x)

void* codec_malloc(size_t size);
void* codec_calloc(size_t nmemb, size_t size);
void* codec_realloc(void* ptr, size_t size);
void codec_free(void* ptr);

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);

size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strcmp(const char *, const char *);

void qsort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));

#define abs(x) ((x)>0?(x):-(x))
#define labs(x) abs(x)

/*MDCT library functions*/

extern void mdct_backward(int n, int32_t *in, int32_t *out);

#if defined(CPU_ARM) && (ARM_ARCH == 4)
/* optimised unsigned integer division for ARMv4, in IRAM */
unsigned udiv32_arm(unsigned a, unsigned b);
#define UDIV32(a, b) udiv32_arm(a, b)
#else
/* default */
#define UDIV32(a, b) (a / b)
#endif

#endif
