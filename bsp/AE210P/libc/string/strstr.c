#include <string.h>

/* FIXME: LICENSE */
__attribute__((used))
char *strstr(const char *haystack, const char *needle)
{
	const char *start_s1 = (void *)0;
	const char *in_s2 = (void *)0;

	for (; *haystack != '\0'; haystack++) {

		if (!start_s1) {

			/* first char of match */
			if (*haystack == *needle) {

				/* remember start of matching substring in haystack */
				start_s1 = haystack;
				in_s2 = needle + 1;
				/* done already? */
				if (*in_s2 == '\0')
					return (char*)start_s1;
			}
			/* continued mis-match
			   else
			   nothing ; */
		}
		else {

			/* continued match */
			if (*haystack == *in_s2) {

				in_s2++;
				/* done */
				if (*in_s2 == '\0')
					return (char*)start_s1;
			}
			else
				/* first char of mis-match */
				start_s1 = (void *)0;
		}
	}

	return (void *)0;
}
