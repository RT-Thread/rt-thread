/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * atof.c
 *
 * The atof() function
 */

#include <stddef.h>
#include <stdint.h>
#include <ctype.h>
#include <inttypes.h>
#include <string.h>

static inline int digitval(int ch)
{
	if (ch >= '0' && ch <= '9') {
		return ch - '0';
	} else if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A' + 10;
	} else if (ch >= 'a' && ch <= 'z') {
		return ch - 'a' + 10;
	} else {
		return -1;
	}
}

double strntof(const char *nptr, char **endptr, int base, size_t n)
{
	int minus = 0;
	double v = 0.0, m = 0.0, divisor = 1.0;
	int d;

	while (n && isspace((unsigned char)*nptr)) {
		nptr++;
		n--;
	}

	/* Single optional + or - */
	if (n) {
		char c = *nptr;
		if (c == '-' || c == '+') {
			minus = (c == '-');
			nptr++;
			n--;
		}
	}

	if (base == 0) {
		if (n >= 2 && nptr[0] == '0' &&
		    (nptr[1] == 'x' || nptr[1] == 'X')) {
			n -= 2;
			nptr += 2;
			base = 16;
		} else if (n >= 1 && nptr[0] == '0') {
			n--;
			nptr++;
			base = 8;
		} else {
			base = 10;
		}
	} else if (base == 16) {
		if (n >= 2 && nptr[0] == '0' &&
		    (nptr[1] == 'x' || nptr[1] == 'X')) {
			n -= 2;
			nptr += 2;
		}
	}

	while (n && (d = digitval(*nptr)) >= 0 && d < base) {
		v = v * base + d;
		n--;
		nptr++;
	}

	if (*nptr == '.') {
		n--;
		nptr++;
		while (n && (d = digitval(*nptr)) >= 0 && d < base) {
			m = m * base + d;
			n--;
			nptr++;
			divisor *= 10.0;
		}
	}

	if (endptr)
		*endptr = (char *)nptr;

	v = v + (m / divisor);

	return minus ? -v : v;
}


double atof(const char *nptr)
{
	return strntof(nptr, NULL, 0, strlen(nptr));
}

