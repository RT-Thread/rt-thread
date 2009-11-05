#ifndef _FNMATCH_H
#define _FNMATCH_H

#include <sys/cdefs.h>

__BEGIN_DECLS

int fnmatch(const char *pattern, const char *string, int flags) __THROW;

#define FNM_NOESCAPE 1
#define FNM_PATHNAME 2
#define FNM_FILE_NAME 2
#define FNM_PERIOD 4
#define FNM_LEADING_DIR 8
#define FNM_CASEFOLD 16

#define FNM_NOMATCH 1

__END_DECLS

#endif
