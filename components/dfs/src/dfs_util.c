/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_utl.c, some misc functions of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2005-01-26     ffxz		  The first version
+------------------------------------------------------------------------------
*/

#include <string.h>

#include <dfs_fs.h>
#include <dfs_util.h>

/*
+------------------------------------------------------------------------------
| Function    : dir_name
+------------------------------------------------------------------------------
| Description : Gets the directory name in specified path string
|
| Parameters  : path, the specified path string
|               path_name, return the path name in this parameter
|               len, the length of path name
| Returns     : the status of path_name:
|               0 , successful
|               -1, failed
| For Example :
| path,			dir_name
| /,			/
| /usr,			/
| /usr/lib,		/usr
| /usr/lib/,	/usr
+------------------------------------------------------------------------------
*/
int dir_name(const char* path, char* dirname, int len)
{
	int pos;

	if ( path[0] == '/' && path[1] == '\0' )
	{
		*dirname++ = '/';
		*dirname = '\0';
		return 0;
	}

	pos = strlen(path);
	while ( *(path + pos - 1) =='/' ) pos --;
	while ( pos > 0 && *(path + pos - 1) != '/' ) pos --;
	while ( pos > 0 && *(path + pos - 1) == '/' ) pos --;

	if ( pos > len ) return -1;

	if ( pos != 0) 
	{
		memcpy(dirname, path, pos);
		*(dirname+pos) = '\0';
	}
	else 
	{
		*dirname++ = '/';
		*dirname   = '\0';
	}

	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : file_name
+------------------------------------------------------------------------------
| Description : Gets the file name in specified path string
|
| Parameters  : path, the specified path string
|               filename, return the path name in this parameter
|               len, the length of file name
| Returns     : the status of file_name:
|               0 , successful
|               -1, failed
| For Example :
| path,			filename
| /,			RT_NULL
| /usr,			usr
| /usr/lib,		lib
| /usr/lib/,	lib
+------------------------------------------------------------------------------
*/
int file_name(const char* path, char* filename, int len)
{
	int pos, size;

	if ( path[0] == '/' && path[1] == '\0' )
	{
		*filename = '\0';
		return 0;
	}

	pos = strlen(path);
	while ( *(path + pos -1)=='/' ) pos --;
	size = pos;

	while ( *(path + pos -1) != '/' && pos > 0 ) pos --;

	if ( size - pos > len ) return -1;
	else size = size - pos ;

	memcpy(filename, path + pos, size);
	*(filename+size) = '\0';

	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : next_path_name
+------------------------------------------------------------------------------
| Description : Gets the next directory name from specified path string
|
| Parameters  : path, the specified path string
|               pos, the specified position of path string
|               next, return the next path in this parameter
| Returns     : the position of next directory item, 
|               -1, if pos reach in the end of the specified path string
| For Example :
+------------------------------------------------------------------------------
*/
int next_dir_name(const char* path, int pos, char* next)
{
	const char* q;

	if ( pos > strlen(path) || pos < 0|| path == RT_NULL ) return -1;

	q = path + pos;

	/* check for firt '/' */
	while ( *q == '/' ) q++;
	if ( *q == '\0' )
	{
		*next = '\0';
		return -1;
	}

	while ( *q != '/' && *q != '\0' )
	{
		*next++ = *q++;
	}
	*next = '\0';

	return q - path + 1;
}

/*
+------------------------------------------------------------------------------
| Function    : build_fullpath
+------------------------------------------------------------------------------
| Description : make up the full path from directory and filename
|
| Parameters  : path, the specified path string
|               filename, return the path name in this parameter
|               fullpath, the returned full path name
| Returns     : null
+------------------------------------------------------------------------------
*/
void build_fullpath(const char *directory, const char *filename, char *fullpath)
{
	char elem[DFS_PATH_MAX + 1];
	int pos, start, len;

	len = 0;
	/* check parameters */
	RT_ASSERT(directory != RT_NULL);
	RT_ASSERT(filename != RT_NULL);
	RT_ASSERT(fullpath != RT_NULL);

	/* copy full of directory */
	strncpy(fullpath, directory, DFS_PATH_MAX + 1);

	for (pos = 0; filename[pos] != '\0'; )
	{
		/* strip '//' */
		while (filename[pos] == '/') pos++;

		/* get the filename element, save to elem array */
		for (start = pos; filename[pos] != '/' && filename[pos] != '\0'; pos++)
			len = pos - start + 1;

		strncpy(elem, filename + start, DFS_PATH_MAX + 1);
		/* clear the end of elem */
		elem[(len < DFS_PATH_MAX + 1? len : DFS_PATH_MAX + 1)] = '\0';

		/* strip '..' */
		if (elem[0] == '.' && elem[1] == '.')
		{
			if (strlen(fullpath) == 0) strcpy(fullpath, ""); /* empty filename */
			else if (fullpath[0] == '/' && fullpath[1] !='\0')
			{
				int i = strlen(fullpath);

				while (fullpath[i - 1] == '/') i--;
				while (i > 0 && fullpath[i - 1] != '/') i--;

				fullpath[i] = '\0';
			}
		}
		/* not '.', copy as normally */
		else if (elem[0] != '.')
		{
			len = strlen(fullpath);
			
			if (len == 0) strncpy(fullpath, elem, DFS_PATH_MAX + 1);
			else if (fullpath[len - 1] == '/')
			{
				if (elem[0] == '/') strncat(fullpath, elem + 1, DFS_PATH_MAX + 1);
				else strncat(fullpath, elem, DFS_PATH_MAX + 1);
			}
			else
			{
				if (elem[0] == '/') strcat(fullpath, elem);
				else
				{
					strncat(fullpath, "/", DFS_PATH_MAX + 1);
					strncat(fullpath + 1, elem, DFS_PATH_MAX + 1);
				}
			}
		}
	}

	if ( fullpath[0] != '/' && fullpath[(len = strlen(fullpath)) - 1] == '/')
	{
		fullpath[len - 1] = '\0';
	}
}

int str_is_prefix(const char* prefix, const char* str)
{
	while ((*prefix) && (*str) && (*prefix == *str))
	{
		prefix ++;
		str ++;
	}
	
	if (*prefix == 0) return 0;
	
	return -1;
}

#if !defined(RT_USING_MINILIBC) && !defined(RT_USING_NEWLIB)
#if !defined(__ICCARM__)
char *strrchr(const char *t, int c)
{
	register char ch;
	register const char *l=0;

	ch = c;
	for (;;)
	{
		if ((*t == ch)) l=t;
		if ((!*t)) return (char*)l; ++t;
	}
}
#endif

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION / 10000 < 35)
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
		
        if ((x2 != x1))
            break;
			
        if ((x1 == (unsigned int)-'A'))
            break;
    }

    return x1 - x2;
}
#endif /* end of __ARMCC_VERSION */

#endif
