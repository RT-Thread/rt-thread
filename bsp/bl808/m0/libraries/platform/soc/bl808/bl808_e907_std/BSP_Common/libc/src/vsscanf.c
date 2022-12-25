/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * vsscanf.c
 *
 * vsscanf(), from which the rest of the scanf()
 * family is built
 */

#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
//#include <wmlibc.h>
#include <compat_attribute.h>

#ifndef LONG_BIT
#define LONG_BIT (CHAR_BIT*sizeof(long))
#endif

enum flag {
	FL_SPLAT = 0x01,	/* Drop the value, do not assign */
	FL_INV   = 0x02,	/* Character-set with inverse */
	FL_WIDTH = 0x04,	/* Field width specified */
	FL_MINUS = 0x08,	/* Negative number */
};

enum ranks {
	rank_char     = -2,
	rank_short    = -1,
	rank_int      = 0,
	rank_long     = 1,
	rank_longlong = 2,
	rank_ptr      = INT_MAX	/* Special value used for pointers */
};

#define MIN_RANK	rank_char
#define MAX_RANK	rank_longlong

#define INTMAX_RANK	rank_longlong
#define SIZE_T_RANK	rank_long
#define PTRDIFF_T_RANK	rank_long

enum bail {
	bail_none = 0,		/* No error condition */
	bail_eof,		/* Hit EOF */
	bail_err		/* Conversion mismatch */
};

static __inline const char *skipspace(const char *p)
{
	while (isspace((unsigned char)*p))
		p++;
	return p;
}

#undef set_bit
static __inline void set_bit(unsigned long *bitmap, unsigned int bit)
{
	bitmap[bit / LONG_BIT] |= 1UL << (bit % LONG_BIT);
}

#undef test_bit
static __inline int test_bit(unsigned long *bitmap, unsigned int bit)
{
	return (int)(bitmap[bit / LONG_BIT] >> (bit % LONG_BIT)) & 1;
}

int vsscanf(const char *buffer, const char *format, va_list ap)
{
	const char *p = format;
	char ch;
	unsigned char uc;
	const char *q = buffer;
	const char *qq;
	uintmax_t val = 0;
	int rank = rank_int;	/* Default rank */
	unsigned int width = UINT_MAX;
	int base;
	unsigned int flags = 0;
	enum {
		st_normal,	/* Ground state */
		st_flags,	/* Special flags */
		st_width,	/* Field width */
		st_modifiers,	/* Length or conversion modifiers */
		st_match_init,	/* Initial state of %[ sequence */
		st_match,	/* Main state of %[ sequence */
		st_match_range,	/* After - in a %[ sequence */
	} state = st_normal;
	char *sarg = NULL;	/* %s %c or %[ string argument */
	enum bail bail = bail_none;
	__UNUSED__ int sign;
	int converted = 0;	/* Successful conversions */
	unsigned long matchmap[((1 << CHAR_BIT) + (LONG_BIT - 1)) / LONG_BIT];
	int matchinv = 0;	/* Is match map inverted? */
	unsigned char range_start = 0;

	while ((ch = *p++) && !bail) {
		switch (state) {
		case st_normal:
			if (ch == '%') {
				state = st_flags;
				flags = 0;
				rank = rank_int;
				width = UINT_MAX;
			} else if (isspace((unsigned char)ch)) {
				q = skipspace(q);
			} else {
				if (*q == ch)
					q++;
				else
					bail = bail_err; /* Match failure */
			}
			break;

		case st_flags:
			switch (ch) {
			case '*':
				flags |= FL_SPLAT;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				width = (ch - '0');
				state = st_width;
				flags |= FL_WIDTH;
				break;
			default:
				state = st_modifiers;
				p--;	/* Process this character again */
				break;
			}
			break;

		case st_width:
			if (ch >= '0' && ch <= '9') {
				width = width * 10 + (ch - '0');
			} else {
				state = st_modifiers;
				p--;	/* Process this character again */
			}
			break;

		case st_modifiers:
			switch (ch) {
				/* Length modifiers - nonterminal sequences */
			case 'h':
				rank--;	/* Shorter rank */
				break;
			case 'l':
				rank++;	/* Longer rank */
				break;
			case 'j':
				rank = INTMAX_RANK;
				break;
			case 'z':
				rank = SIZE_T_RANK;
				break;
			case 't':
				rank = PTRDIFF_T_RANK;
				break;
			case 'L':
			case 'q':
				rank = rank_longlong;	/* long double/long long */
				break;

			default:
				/* Output modifiers - terminal sequences */
				/* Next state will be normal */
				state = st_normal;

				/* Canonicalize rank */
				if (rank < MIN_RANK)
					rank = MIN_RANK;
				else if (rank > MAX_RANK)
					rank = MAX_RANK;

				switch (ch) {
				case 'P':	/* Upper case pointer */
				case 'p':	/* Pointer */
					rank = rank_ptr;
					base = 0;
					sign = 0;
					goto scan_int;

				case 'i':	/* Base-independent integer */
					base = 0;
					sign = 1;
					goto scan_int;

				case 'd':	/* Decimal integer */
					base = 10;
					sign = 1;
					goto scan_int;

				case 'o':	/* Octal integer */
					base = 8;
					sign = 0;
					goto scan_int;

				case 'u':	/* Unsigned decimal integer */
					base = 10;
					sign = 0;
					goto scan_int;

				case 'x':	/* Hexadecimal integer */
				case 'X':
					base = 16;
					sign = 0;
					goto scan_int;

				case 'n':	/* # of characters consumed */
					val = (q - buffer);
					goto set_integer;

				      scan_int:
					q = skipspace(q);
					if (!*q) {
						bail = bail_eof;
						break;
					}
					val =
					    strntoumax(q, (char **)&qq, base,
						       width);
					if (qq == q) {
						bail = bail_err;
						break;
					}
					q = qq;
					if (!(flags & FL_SPLAT))
						converted++;
					/* fall through */

				      set_integer:
					if (!(flags & FL_SPLAT)) {
						switch (rank) {
						case rank_char:
							*va_arg(ap,
								unsigned char *)
								= val;
							break;
						case rank_short:
							*va_arg(ap,
								unsigned short
								*) = val;
							break;
						case rank_int:
							*va_arg(ap,
								unsigned int *)
							    = val;
							break;
						case rank_long:
							*va_arg(ap,
								unsigned long *)
								= val;
							break;
						case rank_longlong:
							*va_arg(ap,
								unsigned long
								long *) = val;
							break;
						case rank_ptr:
							*va_arg(ap, void **) =
								(void *)
								(uintptr_t)val;
							break;
						default:
						    break;
						}
					}
					break;

				case 'c':	/* Character */
					/* Default width == 1 */
					width = (flags & FL_WIDTH) ? width : 1;
					if (flags & FL_SPLAT) {
						while (width--) {
							if (!*q) {
								bail = bail_eof;
								break;
							}
						}
					} else {
						sarg = va_arg(ap, char *);
						while (width--) {
							if (!*q) {
								bail = bail_eof;
								break;
							}
							*sarg++ = *q++;
						}
						if (!bail)
							converted++;
					}
					break;

				case 's':	/* String */
					uc = 1;	/* Anything nonzero */
					if (flags & FL_SPLAT) {
						while (width-- && (uc = *q) &&
						       !isspace(uc)) {
							q++;
						}
					} else {
						char *sp;
						sp = sarg = va_arg(ap, char *);
						while (width-- && (uc = *q) &&
						       !isspace(uc)) {
							*sp++ = uc;
							q++;
						}
						if (sarg != sp) {
							/* Terminate output */
							*sp = '\0';
							converted++;
						}
					}
					if (!uc)
						bail = bail_eof;
					break;

				case '[':	/* Character range */
					sarg = (flags & FL_SPLAT) ? NULL
						: va_arg(ap, char *);
					state = st_match_init;
					matchinv = 0;
					memset(matchmap, 0, sizeof matchmap);
					break;

				case '%':	/* %% sequence */
					if (*q == '%')
						q++;
					else
						bail = bail_err;
					break;

				default:	/* Anything else */
					/* Unknown sequence */
					bail = bail_err;
					break;
				}
			}
			break;

		case st_match_init:	/* Initial state for %[ match */
			if (ch == '^' && !(flags & FL_INV)) {
				matchinv = 1;
			} else {
				set_bit(matchmap, (unsigned char)ch);
				state = st_match;
			}
			break;

		case st_match:	/* Main state for %[ match */
			if (ch == ']') {
				goto match_run;
			} else if (ch == '-') {
				range_start = (unsigned char)ch;
				state = st_match_range;
			} else {
				set_bit(matchmap, (unsigned char)ch);
			}
			break;

		case st_match_range:	/* %[ match after - */
			if (ch == ']') {
				/* - was last character */
				set_bit(matchmap, (unsigned char)'-');
				goto match_run;
			} else {
				int i;
				for (i = range_start; i < (unsigned char)ch;
				     i++)
					set_bit(matchmap, i);
				state = st_match;
			}
			break;

		      match_run:	/* Match expression finished */
			qq = q;
			uc = 1;	/* Anything nonzero */
			while (width && (uc = *q)
			       && test_bit(matchmap, uc)^matchinv) {
				if (sarg)
					*sarg++ = uc;
				q++;
			}
			if (q != qq && sarg) {
				*sarg = '\0';
				converted++;
			} else {
				bail = bail_err;
			}
			if (!uc)
				bail = bail_eof;
			break;
		default:
		    break;
		}
	}

	if (bail == bail_eof && !converted)
		converted = -1;	/* Return EOF (-1) */

	return converted;
}
