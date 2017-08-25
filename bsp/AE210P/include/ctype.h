#ifndef __CTYPE_H__
#define __CTYPE_H__

static inline int islower(int c)
{
	return c >= 'a' && c <= 'z';
}

static inline int isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}

static inline int isalpha(int c)
{
	return islower(c) || isupper(c);
}

static inline int isdigit(int c)
{
	return c >= '0' && c <= '9';
}

static inline int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

static inline int isblank(int c)
{
	return c == ' ' || c == '\t';
}

static inline int isspace(int c)
{
	return c == ' ';
}

static inline int isxdigit(int c)
{
	return (c >= '0' && c <= '9') ||
		(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z');
}

// static inline int isascii(int c)
// static inline int iscntrl(int c)
// static inline int isgraph(int c)
// static inline int isprint(int c)
// static inline int ispunct(int c)
#endif /* __CTYPE_H__ */
