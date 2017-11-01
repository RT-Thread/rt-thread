/*
 * File      : string.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-08-14     Bernard      the first version
 * 2010-02-15     Gary Lee     add strlcpy
 * 2010-03-17     Bernard      add strlcpy implementation to this file.
 *                             fix strlcpy declaration
 * 2010-03-24     Bernard      add strchr and strtok implementation.
 */

#include <rtthread.h>
#include <stdint.h>

#if !defined (RT_USING_NEWLIB) && defined (RT_USING_MINILIBC)
#include "string.h"

/* there is no strcpy and strcmp implementation in RT-Thread */
char *strcpy(char *dest, const char *src)
{
	return (char *)rt_strncpy(dest, src, rt_strlen(src) + 1);
}

char *strncpy(char *dest, const char *src, size_t siz)
{
	return (char *)rt_strncpy(dest, src, siz);
}

size_t strlcpy(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0)
	{
		do
		{
			if ((*d++ = *s++) == 0) break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0)
	{
		if (siz != 0) *d = '\0';	/* NUL-terminate dst */
		while (*s++) ;
	}

	return(s - src - 1);			/* count does not include NUL */
}

int strcmp (const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
		s1++, s2++;
	return (*s1 - *s2);
}

/**
 * strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */
int strncmp(const char *cs,const char *ct, size_t count)
{
	register signed char __res = 0;

	while (count) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
		count--;
	}

	return __res;
}

char *strcat(char * dest, const char * src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++) != '\0')
		;

	return tmp;
}

char *strncat(char *dest, const char *src, size_t count)
{
	char *tmp = dest;

	if (count) {
		while (*dest)
			dest++;
		while ((*dest++ = *src++)) {
			if (--count == 0) {
				*dest = '\0';
				break;
			}
		}
	}

	return tmp;
}

char *strrchr(const char *t, int c) 
{
	register char ch;
	register const char *l=0;

	ch = c;
	for (;;) 
	{
		if (*t == ch) l=t; 
		if (!*t) return (char*)l; 
		++t;
	}
	
	return (char*)l;
}


int  strncasecmp ( const char* s1, const char* s2, size_t len )
{
	register unsigned int  x2;
	register unsigned int  x1;
	register const char*   end = s1 + len;

	while (1)
	{
		if ((s1 >= end) )
			return 0;

		x2 = *s2 - 'A'; if ((x2 < 26u)) x2 += 32;
		x1 = *s1 - 'A'; if ((x1 < 26u)) x1 += 32;
		s1++; s2++;

		if (x2 != x1)
			break;

		if (x1 == (unsigned int)-'A')
			break;
	}

	return x1 - x2;
}

/* private function */
#define isdigit(c)  ((unsigned)((c) - '0') < 10)

rt_inline int divide(int *n, int base)
{
	rt_int32_t res;

	/* optimized for processor which does not support divide instructions. */
	if (base == 10)
	{
		res = ((int)*n) % 10U;
		*n = ((int)*n) / 10U;
	}
	else
	{
		res = ((int)*n) % 16U;
		*n = ((int)*n) / 16U;
	}

	return res;
}

rt_inline int skip_atoi(const char **s)
{
	register int i=0;
	while (isdigit(**s)) i = i*10 + *((*s)++) - '0';

	return i;
}

unsigned char _ctype[] = {
_C,_C,_C,_C,_C,_C,_C,_C,			/* 0-7 */
_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,		/* 8-15 */
_C,_C,_C,_C,_C,_C,_C,_C,			/* 16-23 */
_C,_C,_C,_C,_C,_C,_C,_C,			/* 24-31 */
_S|_SP,_P,_P,_P,_P,_P,_P,_P,			/* 32-39 */
_P,_P,_P,_P,_P,_P,_P,_P,			/* 40-47 */
_D,_D,_D,_D,_D,_D,_D,_D,			/* 48-55 */
_D,_D,_P,_P,_P,_P,_P,_P,			/* 56-63 */
_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,	/* 64-71 */
_U,_U,_U,_U,_U,_U,_U,_U,			/* 72-79 */
_U,_U,_U,_U,_U,_U,_U,_U,			/* 80-87 */
_U,_U,_U,_P,_P,_P,_P,_P,			/* 88-95 */
_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,	/* 96-103 */
_L,_L,_L,_L,_L,_L,_L,_L,			/* 104-111 */
_L,_L,_L,_L,_L,_L,_L,_L,			/* 112-119 */
_L,_L,_L,_P,_P,_P,_P,_C,			/* 120-127 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 128-143 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 144-159 */
_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,   /* 160-175 */
_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,       /* 176-191 */
_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,       /* 192-207 */
_U,_U,_U,_U,_U,_U,_U,_P,_U,_U,_U,_U,_U,_U,_U,_L,       /* 208-223 */
_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,       /* 224-239 */
_L,_L,_L,_L,_L,_L,_L,_P,_L,_L,_L,_L,_L,_L,_L,_L};      /* 240-255 */

#define __ismask(x) (_ctype[(int)(unsigned char)(x)])

#define isalnum(c)	((__ismask(c)&(_U|_L|_D)) != 0)
#define isalpha(c)	((__ismask(c)&(_U|_L)) != 0)
#define iscntrl(c)	((__ismask(c)&(_C)) != 0)
#define isgraph(c)	((__ismask(c)&(_P|_U|_L|_D)) != 0)
#define islower(c)	((__ismask(c)&(_L)) != 0)
#define isprint(c)	((__ismask(c)&(_P|_U|_L|_D|_SP)) != 0)
#define ispunct(c)	((__ismask(c)&(_P)) != 0)
#define isspace(c)	((__ismask(c)&(_S)) != 0)
#define isupper(c)	((__ismask(c)&(_U)) != 0)
#define isxdigit(c)	((__ismask(c)&(_D|_X)) != 0)

#define isascii(c) (((unsigned char)(c))<=0x7f)
#define toascii(c) (((unsigned char)(c))&0x7f)

static inline unsigned char __tolower(unsigned char c)
{
	if (isupper(c))
		c -= 'A'-'a';
	return c;
}

static inline unsigned char __toupper(unsigned char c)
{
	if (islower(c))
		c -= 'a'-'A';
	return c;
}

int tolower(int c) 
{
	return __tolower(c);
}

int toupper(int c)
{
	return __toupper(c);
}

/**
 * simple_strtoul - convert a string to an unsigned long
 * @cp: The start of the string
 * @endp: A pointer to the end of the parsed string will be placed here
 * @base: The number base to use
 */
unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)
{
	unsigned long result = 0,value;

	if (!base) {
		base = 10;
		if (*cp == '0') {
			base = 8;
			cp++;
			if ((toupper(*cp) == 'X') && isxdigit(cp[1])) {
				cp++;
				base = 16;
			}
		}
	} else if (base == 16) {
		if (cp[0] == '0' && toupper(cp[1]) == 'X')
			cp += 2;
	}
	while (isxdigit(*cp) &&
	       (value = isdigit(*cp) ? *cp-'0' : toupper(*cp)-'A'+10) < base) {
		result = result*base + value;
		cp++;
	}
	if (endp)
		*endp = (char *)cp;
	return result;
}

/**
 * simple_strtol - convert a string to a signed long
 * @cp: The start of the string
 * @endp: A pointer to the end of the parsed string will be placed here
 * @base: The number base to use
 */
long simple_strtol(const char *cp,char **endp,unsigned int base)
{
	if(*cp=='-')
		return -simple_strtoul(cp+1,endp,base);
	return simple_strtoul(cp,endp,base);
}

/**
 * simple_strtoull - convert a string to an unsigned long long
 * @cp: The start of the string
 * @endp: A pointer to the end of the parsed string will be placed here
 * @base: The number base to use
 */
unsigned long long simple_strtoull(const char *cp,char **endp,unsigned int base)
{
	unsigned long long result = 0, value;

	if (*cp == '0') {
		cp++;
		if ((toupper(*cp) == 'X') && isxdigit (cp[1])) {
			base = 16;
			cp++;
		}
		if (!base) {
			base = 8;
		}
	}
	if (!base) {
		base = 10;
	}
	while (isxdigit (*cp) && (value = isdigit (*cp)
				? *cp - '0'
				: (islower (*cp) ? toupper (*cp) : *cp) - 'A' + 10) < base) {
		result = result * base + value;
		cp++;
	}
	if (endp)
		*endp = (char *) cp;
	return result;
}

/**
 * simple_strtoll - convert a string to a signed long long
 * @cp: The start of the string
 * @endp: A pointer to the end of the parsed string will be placed here
 * @base: The number base to use
 */
long long simple_strtoll(const char *cp,char **endp,unsigned int base)
{
	if(*cp=='-')
		return -simple_strtoull(cp+1,endp,base);
	return simple_strtoull(cp,endp,base);
}

/**
 * vsscanf - Unformat a buffer into a list of arguments
 * @buf:	input buffer
 * @fmt:	format of buffer
 * @args:	arguments
 */
int vsscanf(const char * buf, const char * fmt, va_list args)
{
	const char *str = buf;
	char *next;
	int num = 0;
	int qualifier;
	int base;
	int field_width = -1;
	int is_sign = 0;

	while(*fmt && *str) {
		/* skip any white space in format */
		/* white space in format matchs any amount of
		 * white space, including none, in the input.
		 */
		if (isspace(*fmt)) {
			while (isspace(*fmt))
				++fmt;
			while (isspace(*str))
				++str;
		}

		/* anything that is not a conversion must match exactly */
		if (*fmt != '%' && *fmt) {
			if (*fmt++ != *str++)
				break;
			continue;
		}

		if (!*fmt)
			break;
		++fmt;
		
		/* skip this conversion.
		 * advance both strings to next white space
		 */
		if (*fmt == '*') {
			while (!isspace(*fmt) && *fmt)
				fmt++;
			while (!isspace(*str) && *str)
				str++;
			continue;
		}

		/* get field width */
		if (isdigit(*fmt))
			field_width = skip_atoi(&fmt);

		/* get conversion qualifier */
		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L' || *fmt == 'Z') {
			qualifier = *fmt;
			fmt++;
		}
		base = 10;
		is_sign = 0;

		if (!*fmt || !*str)
			break;

		switch(*fmt++) {
		case 'c':
		{
			char *s = (char *) va_arg(args,char*);
			if (field_width == -1)
				field_width = 1;
			do {
				*s++ = *str++;
			} while(field_width-- > 0 && *str);
			num++;
		}
		continue;
		case 's':
		{
			char *s = (char *) va_arg(args, char *);
			if(field_width == -1)
				field_width = INT_MAX;
			/* first, skip leading white space in buffer */
			while (isspace(*str))
				str++;

			/* now copy until next white space */
			while (*str && !isspace(*str) && field_width--) {
				*s++ = *str++;
			}
			*s = '\0';
			num++;
		}
		continue;
		case 'n':
			/* return number of characters read so far */
		{
			int *i = (int *)va_arg(args,int*);
			*i = str - buf;
		}
		continue;
		case 'o':
			base = 8;
			break;
		case 'x':
		case 'X':
			base = 16;
			break;
		case 'd':
		case 'i':
			is_sign = 1;
		case 'u':
			break;
		case '%':
			/* looking for '%' in str */
			if (*str++ != '%') 
				return num;
			continue;
		default:
			/* invalid format; stop here */
			return num;
		}

		/* have some sort of integer conversion.
		 * first, skip white space in buffer.
		 */
		while (isspace(*str))
			str++;

		if (!*str || !isdigit(*str))
			break;

		switch(qualifier) {
		case 'h':
			if (is_sign) {
				short *s = (short *) va_arg(args,short *);
				*s = (short) simple_strtol(str,&next,base);
			} else {
				unsigned short *s = (unsigned short *) va_arg(args, unsigned short *);
				*s = (unsigned short) simple_strtoul(str, &next, base);
			}
			break;
		case 'l':
			if (is_sign) {
				long *l = (long *) va_arg(args,long *);
				*l = simple_strtol(str,&next,base);
			} else {
				unsigned long *l = (unsigned long*) va_arg(args,unsigned long*);
				*l = simple_strtoul(str,&next,base);
			}
			break;
		case 'L':
			if (is_sign) {
				long long *l = (long long*) va_arg(args,long long *);
				*l = simple_strtoll(str,&next,base);
			} else {
				unsigned long long *l = (unsigned long long*) va_arg(args,unsigned long long*);
				*l = simple_strtoull(str,&next,base);
			}
			break;
		case 'Z':
		{
			unsigned long *s = (unsigned long*) va_arg(args,unsigned long*);
			*s = (unsigned long) simple_strtoul(str,&next,base);
		}
		break;
		default:
			if (is_sign) {
				int *i = (int *) va_arg(args, int*);
				*i = (int) simple_strtol(str,&next,base);
			} else {
				unsigned int *i = (unsigned int*) va_arg(args, unsigned int*);
				*i = (unsigned int) simple_strtoul(str,&next,base);
			}
			break;
		}
		num++;

		if (!next)
			break;
		str = next;
	}
	return num;
}

/**
 * sscanf - Unformat a buffer into a list of arguments
 * @buf:	input buffer
 * @fmt:	formatting of buffer
 * @...:	resulting arguments
 */
int sscanf(const char * buf, const char * fmt, ...)
{
	va_list args;
	int i;

	va_start(args,fmt);
	i = vsscanf(buf,fmt,args);
	va_end(args);
	
	return i;
}

size_t strspn(const char *s, const char *accept)
{
	size_t l=0;
	int a=1,i, al=strlen(accept);

	while((a)&&(*s))
	{
		for(a=i=0;(!a)&&(i<al);i++)
			if (*s==accept[i]) a=1;
		if (a) l++;
		s++;
	}
	return l;
}

size_t strcspn(const char *s, const char *reject)
{
	size_t l=0;
	int a=1,i,al=strlen(reject);

	while((a)&&(*s))
	{
		for(i=0;(a)&&(i<al);i++)
			if (*s==reject[i]) a=0;
		if (a) l++;
		s++;
	}
	return l;
}

char*strtok_r(char*s,const char*delim,char**ptrptr)
{
	char*tmp=0;

	if (s==0) s=*ptrptr;
	s += strspn(s,delim);	/* overread leading delimiter */
	if (*s)
	{
		tmp=s;
		s+=strcspn(s,delim);

		if (*s) *s++=0;		/* not the end ? => terminate it */
	}
	*ptrptr=s;
	return tmp;
}

char *strtok(char *s, const char *delim)
{
	static char *strtok_pos;
	return strtok_r(s,delim,&strtok_pos);
}

char *strchr(const char *s1, int i)
{
	const unsigned char *s = (const unsigned char *)s1;
	unsigned char c = (unsigned int)i;

	while (*s && *s != c)
	{
		s++;
	}

	if (*s != c)
	{
		s = NULL;
	}

	return (char *) s;
}

long strtol(const char *str, char **endptr, int base)
{
    return simple_strtol(str, endptr, base);
}

long long strtoll(const char *str, char **endptr, int base)
{
    return simple_strtoll(str, endptr, base);
}

#endif
