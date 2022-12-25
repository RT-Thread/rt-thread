/*
 * klibc/extern.h
 */

#ifndef _EXTERN_H
#define _EXTERN_H

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define __alias(x) __attribute__((weak, alias(x)))

#endif				/* _EXTERN_H */
