/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_util.h, some misc definitions of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2005-01-26     ffxz         The first version
+------------------------------------------------------------------------------
*/

#ifndef __DFS_UTIL_H__
#define __DFS_UTIL_H__

#include <dfs_def.h>

int dir_name(const char* path, char* dirname, int len);
int file_name(const char* path, char* filename, int len);

int next_dir_name(const char* path, int pos, char* next);
void build_fullpath(const char *directory, const char *filename, char *fullpath);
int str_is_prefix(const char* prefix, const char* str);

#if !defined(RT_USING_MINILIBC) && !defined(RT_USING_NEWLIB)
char *strrchr(const char *t, int c);
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION / 10000 < 35)
#include <stddef.h>
int strncasecmp(const char* s1, const char* s2, size_t len);
#endif /* end of __ARMCC_VERSION */
#endif

#endif
