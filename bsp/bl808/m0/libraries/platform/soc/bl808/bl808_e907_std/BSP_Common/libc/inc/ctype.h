/*
 * ctype.h
 *
 * This assumes ISO 8859-1, being a reasonable superset of ASCII.
 */

#ifndef _CTYPE_H
#define _CTYPE_H

#include <extern.h>
#include <libc_compiler.h>

#define _U      (1 << 0)
#define _L      (1 << 1)
#define _N      (1 << 2)
#define _S      (1 << 3)
#define _P      (1 << 4)
#define _C      (1 << 5)
#define _X      (1 << 6)
#define _B      (1 << 7)

/*
 * This relies on the following definitions:
 *
 * cntrl = !print
 * alpha = upper|lower
 * graph = punct|alpha|digit
 * blank = '\t' || ' ' (per POSIX requirement)
 */
enum {
	__ctype_upper = _U,
	__ctype_lower = _L,
	__ctype_digit = _N,
	__ctype_xdigit = _S,
	__ctype_space = _P,
	__ctype_print = _C,
	__ctype_punct = _X,
	__ctype_cntrl = _B
};

__extern int isalnum(int);
__extern int isalpha(int);
__extern int isascii(int);
__extern int isblank(int);
__extern int iscntrl(int);
__extern int isdigit(int);
__extern int isgraph(int);
__extern int islower(int);
__extern int isprint(int);
__extern int ispunct(int);
__extern int isspace(int);
__extern int isupper(int);
__extern int isxdigit(int);
__extern int toupper(int);
__extern int tolower(int);

extern const unsigned char __ctypes[];

__must_inline int __ctype_isalnum(int __c)
{
	return __ctypes[__c + 1] &
	    (__ctype_upper | __ctype_lower | __ctype_digit);
}

__must_inline int __ctype_isalpha(int __c)
{
	return __ctypes[__c + 1] & (__ctype_upper | __ctype_lower);
}

__must_inline int __ctype_isascii(int __c)
{
	return !(__c & ~0x7f);
}

__must_inline int __ctype_isblank(int __c)
{
	return (__c == '\t') || (__c == ' ');
}

__must_inline int __ctype_iscntrl(int __c)
{
	return __ctypes[__c + 1] & __ctype_cntrl;
}

__must_inline int __ctype_isdigit(int __c)
{
	return ((unsigned)__c - '0') <= 9;
}

__must_inline int __ctype_isgraph(int __c)
{
	return __ctypes[__c + 1] &
	    (__ctype_upper | __ctype_lower | __ctype_digit | __ctype_punct);
}

__must_inline int __ctype_islower(int __c)
{
	return __ctypes[__c + 1] & __ctype_lower;
}

__must_inline int __ctype_isprint(int __c)
{
	return __ctypes[__c + 1] & __ctype_print;
}

__must_inline int __ctype_ispunct(int __c)
{
	return __ctypes[__c + 1] & __ctype_punct;
}

__must_inline int __ctype_isspace(int __c)
{
	return __ctypes[__c + 1] & __ctype_space;
}

__must_inline int __ctype_isupper(int __c)
{
	return __ctypes[__c + 1] & __ctype_upper;
}

__must_inline int __ctype_isxdigit(int __c)
{
	return __ctypes[__c + 1] & __ctype_xdigit;
}

/* Note: this is decimal, not hex, to avoid accidental promotion to unsigned */
#define _toupper(__c) ((__c) & ~32)
#define _tolower(__c) ((__c) | 32)

__must_inline int __ctype_toupper(int __c)
{
	return __ctype_islower(__c) ? _toupper(__c) : __c;
}

__must_inline int __ctype_tolower(int __c)
{
	return __ctype_isupper(__c) ? _tolower(__c) : __c;
}

#endif				/* _CTYPE_H */
