/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_posix.c, the interface related implementations of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2009-05-27     Yi.qiu       The first version.
+------------------------------------------------------------------------------
*/
#include <string.h>
#include <dfs_util.h>
#include <dfs_posix.h>

/*
+------------------------------------------------------------------------------
| Function    : open
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int open(const char *file, int flags, int mode)
{
	int fd, result;
	struct dfs_fd* d;

	/* allocate a fd */
	fd = fd_new();
	if (fd < 0) return -1;
	d  = fd_get(fd);

	result = dfile_raw_open(d, file, flags);
	if (result < 0)
	{
		rt_set_errno(result);
		fd_put(d);
		fd_put(d);

		return -1;
	}

	/* release the ref-count of fd */
	fd_put(d);
	return fd;
}

/*
+------------------------------------------------------------------------------
| Function    : close
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int close(int fd)
{
	int result;
	struct dfs_fd* d;

	d = fd_get(fd);
	if (d == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return -1;
	}

	result = dfile_raw_close(d);
	fd_put(d);
	fd_put(d);

	if (result < 0)
	{
		rt_set_errno(result);
		return -1;
	}
	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : read
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int read(int fd, char *buf, int   len)
{
	int result;
	struct dfs_fd* d;

	/* get the fd */
	d  = fd_get(fd);
	if (d == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return -1;
	}

	result = dfile_raw_read(d, buf, len);
	if (result < 0)
	{
		rt_set_errno(result);
		fd_put(d);

		return -1;
	}

	/* release the ref-count of fd */
	fd_put(d);
	return result;
}

/*
+------------------------------------------------------------------------------
| Function    : write
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int write(int fd, char *buf, int   len)
{
	int result;
	struct dfs_fd* d;

	/* get the fd */
	d  = fd_get(fd);
	if (d == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return -1;
	}

	result = dfile_raw_write(d, buf, len);
	if (result < 0)
	{
		rt_set_errno(result);
		fd_put(d);

		return -1;
	}

	/* release the ref-count of fd */
	fd_put(d);
	return result;
}

/*
+------------------------------------------------------------------------------
| Function    : lseek
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int lseek(int fd, int offset, int dir)
{
	int result;
	struct dfs_fd* d;

	d  = fd_get(fd);
	if (d == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return -1;
	}

	switch (dir)
	{
	case DFS_SEEK_SET:
		break;

	case DFS_SEEK_CUR:
		offset += d->pos;
		break;

	case DFS_SEEK_END:
		offset += d->size;
		break;
	}

	result = dfile_raw_lseek(d, offset);
	if (result < 0)
	{
		rt_set_errno(result);
		fd_put(d);
		return -1;
	}

	/* release the ref-count of fd */
	fd_put(d);
	return offset;
}

/*
+------------------------------------------------------------------------------
| Function    : rename
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int rename(const char* old, const char* new )
{
	int result;

	result = dfile_raw_rename(old, new);
	if (result < 0)
	{
		rt_set_errno(result);
		return -1;
	}
	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : unlink
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int unlink(const char *pathname)
{
	int result;

	result = dfile_raw_unlink(pathname);
	if (result < 0)
	{
		rt_set_errno(result);
		return -1;
	}
	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : stat
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int stat(const char *file, struct dfs_stat *buf)
{
	int result;

	result = dfile_raw_stat(file, (struct dfs_stat *)buf);
	if (result < 0)
	{
		rt_set_errno(result);
		return -1;
	}
	return result;
}

/*
+------------------------------------------------------------------------------
| Function    : mkdir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int mkdir (const char *path, rt_uint16_t mode)
{
	int fd;
	struct dfs_fd* d;
	int result;

	fd = fd_new();
	d = fd_get(fd);

	result = dfile_raw_open(d, path, DFS_O_DIRECTORY | DFS_O_CREAT);
	fd_put(d);
	fd_put(d);

	if (result < 0)
	{
		rt_set_errno(result);
		return -1;
	}

	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : rmdir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int rmdir(const char *pathname)
{
	int result;

	result = dfile_raw_unlink(pathname);
	if (result < 0)
	{
		rt_set_errno(result);
		return -1;
	}

	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : opendir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
DIR* opendir(const char* name)
{
	struct dfs_fd* d;
	int fd, result;
	DIR* t;

	t = RT_NULL;

	/* allocate a fd */
	fd = fd_new();
	if (fd == -1) { rt_kprintf("no fd\n"); return RT_NULL; }
	d  = fd_get(fd);

	result = dfile_raw_open(d, name, DFS_O_RDONLY | DFS_O_DIRECTORY);
	if (result >= 0)
	{
		/* open successfully */
		t = (DIR *) rt_malloc (sizeof(DIR));
		if (t == RT_NULL)
		{
			dfile_raw_close(d);
			fd_put(d);
		}
		else
		{
		    rt_memset(t, 0, sizeof(DIR));
		    t->fd = fd;
		}
		fd_put(d);
		return t;
	}

	/* open failed */
	fd_put(d);
	fd_put(d);
	rt_set_errno(result);

	return RT_NULL;
}

/*
+------------------------------------------------------------------------------
| Function    : readdir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
struct dfs_dirent* readdir(DIR *d)
{
	int result;
	struct dfs_fd* fd;

	fd = fd_get(d->fd);
	if (fd == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return RT_NULL;
	}

	if (!d->num || (d->cur += ((struct dfs_dirent*)(d->buf + d->cur))->d_reclen) >= d->num)
	{
		result = dfile_raw_getdents(fd, (struct dfs_dirent*)d->buf, sizeof(d->buf) - 1);
		if (result <= 0)
		{
			rt_set_errno(result);
			fd_put(fd);

			return RT_NULL;
		}

		d->num = result;
		d->cur = 0;
	}

	fd_put(fd);
	return (struct dfs_dirent*)(d->buf+d->cur);
}

/*
+------------------------------------------------------------------------------
| Function    : telldir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
rt_off_t telldir(DIR *d)
{
	struct dfs_fd* fd;
	rt_off_t result;

	fd = fd_get(d->fd);
	if (fd == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return 0;
	}

	result = fd->pos - d->num + d->cur;
	fd_put(fd);

	return result;
}

/*
+------------------------------------------------------------------------------
| Function    : seekdir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
void seekdir(DIR *d, rt_off_t offset)
{
	struct dfs_fd* fd;

	fd = fd_get(d->fd);
	if (fd == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return ;
	}

	if (dfile_raw_lseek(fd, offset) >= 0) d->num = d->cur = 0;
	fd_put(fd);
}

/*
+------------------------------------------------------------------------------
| Function    : rewinddir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
void rewinddir(DIR *d)
{
	struct dfs_fd* fd;

	fd = fd_get(d->fd);
	if (fd == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return ;
	}

	if (dfile_raw_lseek(fd, 0) >= 0) d->num = d->cur = 0;
	fd_put(fd);
}

/*
+------------------------------------------------------------------------------
| Function    : closedir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int closedir(DIR* d)
{
	int result;
	struct dfs_fd* fd;

	fd = fd_get(d->fd);
	if (fd == RT_NULL)
	{
		rt_set_errno(-RT_ERROR);
		return -1;
	}

	result = dfile_raw_close(fd);
	fd_put(fd);

	fd_put(fd);
	rt_free(d);

	if (result < 0)
	{
		rt_set_errno(result);
		return -1;
	}
	else return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : chdir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
int chdir(const char *path)
{
	char* fullpath, full_path[DFS_PATH_MAX + 1];

	if(path == RT_NULL || rt_strlen(path) > DFS_PATH_MAX)
		return -1;

	fullpath = (char*)path;
	if ( fullpath[0] != '/' )
	{
		/* build full path */
		fullpath = full_path;
#ifdef DFS_USING_WORKDIR
		dfs_lock();
		build_fullpath(working_directory, path, fullpath);
		strcpy(working_directory, fullpath);
		dfs_unlock();
#endif
	}
	else
	{
#ifdef DFS_USING_WORKDIR
		dfs_lock();
		rt_strncpy(working_directory, path, strlen(path) + 1);
		working_directory[strlen(path)] = '\0';
		dfs_unlock();
#endif
	}

	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : chdir
+------------------------------------------------------------------------------
| Description :
|
| Parameters  :
| Returns     :
|
+------------------------------------------------------------------------------
*/
char* getcwd(char *buf, rt_size_t size)
{
#ifdef DFS_USING_WORKDIR
	dfs_lock();
	rt_strncpy(buf, working_directory, size);
	dfs_unlock();
#else
	rt_kprintf("WARNING: not support working directory\n");
#endif
	return buf;
}

