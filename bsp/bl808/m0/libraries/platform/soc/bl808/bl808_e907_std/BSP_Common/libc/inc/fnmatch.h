#ifndef _FNMATCH_H
#define _FNMATCH_H

#include <extern.h>

#define FNM_NOMATCH		1

#define FNM_PATHNAME		1
#define FNM_FILE_NAME		FNM_PATHNAME
#define FNM_NOESCAPE		2
#define FNM_PERIOD		4

__extern int fnmatch(const char *, const char *, int);

#endif /* _FNMATCH_H */
