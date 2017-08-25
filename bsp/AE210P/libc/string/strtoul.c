#include <string.h>
#include <ctype.h>

/* FIXME: LICENSE */
__attribute__((used))
unsigned long int strtoul(const char *nptr, char **endptr, int base)
{
	const char *s;
	unsigned long acc, cutoff;
	int c;
	int neg, any, cutlim;

	s = nptr;
	do
		c = *s++;
	while (isspace(c));

	if (c == '-') {

		neg = 1;
		c = *s++;
	}
	else {
		neg = 0;
		if (c == '+')
			c = *s++;
	}

	if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {

		c = s[1];
		s += 2;
		base = 16;
	}

	if (base == 0)
		base = c == '0' ? 8 : 10;

#ifndef ULONG_MAX
#define ULONG_MAX (unsigned long) -1
#endif

	cutoff = ULONG_MAX / (unsigned long)base;
	cutlim = ULONG_MAX % (unsigned long)base;

	for (acc = 0, any = 0;; c = *s++) {

		if (isdigit(c))
			c -= '0';

		else if (isalpha(c))

			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;

		if (c >= base)
			break;

		if (any < 0)
			continue;

		// FIXME
		if (acc > cutoff || (acc == cutoff && c > cutlim)) {

			any = -1;
			acc = ULONG_MAX;
		}
		else {
			any = 1;
			acc *= (unsigned long)base;
			acc += c;
		}
	}
	if (neg && any > 0)
		acc = -acc;

	if (endptr != 0)
		*endptr = (char *)(any ? s - 1 : nptr);

	return acc;
}
