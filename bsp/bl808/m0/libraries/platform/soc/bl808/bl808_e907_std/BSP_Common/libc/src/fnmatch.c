/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * fnmatch.c
 *
 * Original implementation by Kay Sievers, modified by H. Peter Anvin.
 */

#include <fnmatch.h>

int fnmatch(const char *p, const char *s, int flags)
{
	if (flags & FNM_PATHNAME && *s == '/')
		return (*p != '/') || fnmatch(p+1, s+1, flags);
	if (flags & FNM_PERIOD && *s == '.')
		return (*p != '.') || fnmatch(p+1, s+1, flags);

	flags &= ~FNM_PERIOD;	/* Only applies at beginning */

	if (!(flags & FNM_NOESCAPE) && *p == '\\') {
		p++;
		return (*p != *s) || fnmatch(p+1, s+1, flags);
	}

	if (*s == '\0') {
		while (*p == '*')
			p++;
		return (*p != '\0');
	}

	switch (*p) {
	case '[':
		{
			int not_mark = 0;
			p++;
			if (*p == '!') {
				not_mark = 1;
				p++;
			}
			while ((*p != '\0') && (*p != ']')) {
				int match = 0;
				if (p[1] == '-') {
					if ((*s >= *p) && (*s <= p[2]))
						match = 1;
					p += 3;
				} else {
					match = (*p == *s);
					p++;
				}
				if (match ^ not_mark) {
					while ((*p != '\0') && (*p != ']'))
						p++;
					if (*p == ']')
						return fnmatch(p+1, s+1, flags);
				}
			}
		}
		break;
	case '*':
		if (fnmatch(p, s+1, flags))
			return fnmatch(p+1, s, flags);
		return 0;
	case '\0':
		if (*s == '\0') {
			return 0;
		}
		break;
	default:
		if ((*p == *s) || (*p == '?'))
			return fnmatch(p+1, s+1, flags);
		break;
	}
	return 1;
}
