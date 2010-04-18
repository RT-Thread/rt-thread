/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_raw.c, the raw APIs of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2005-02-22     ffxz         The first version.                     
+------------------------------------------------------------------------------
*/
#include <dfs_raw.h>
#include <dfs_util.h>
#include <string.h>

extern struct dfs_fd fd_table[];

#define NO_WORKING_DIR	"system does not support working dir\n"

/*
+------------------------------------------------------------------------------
| Function    : fd_new
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int fd_new(void)
{
	struct dfs_fd* d;
	int idx;

	/* lock filesystem */
	dfs_lock();

	/* find an empty fd entry */
#ifdef DFS_USING_STDIO
	for (idx = 3; idx < DFS_FD_MAX + 3 && fd_table[idx].ref_count > 0; idx++);
#else
	for (idx = 0; idx < DFS_FD_MAX && fd_table[idx].ref_count > 0; idx++);
#endif

	/* can't find an empty fd entry */
#ifdef DFS_USING_STDIO
	if (idx == DFS_FD_MAX + 3)
#else
	if (idx == DFS_FD_MAX)
#endif
	{
		idx = -1;
		goto __result;
	}

	d = &(fd_table[idx]);
	d->ref_count = 1;

__result:
	dfs_unlock();
	return idx;
}

/*
+------------------------------------------------------------------------------
| Function    : fd_get
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
struct dfs_fd* fd_get(int fd)
{
	struct dfs_fd* d;

#ifdef DFS_USING_STDIO
	if ( fd < 3 || fd > DFS_FD_MAX + 3) return RT_NULL;
#else
	if ( fd < 0 || fd > DFS_FD_MAX ) return RT_NULL;
#endif

	d = &fd_table[fd];

	dfs_lock();
	d->ref_count ++;
	dfs_unlock();

	return d;
}

/*
+------------------------------------------------------------------------------
| Function    : fd_put
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
void fd_put(struct dfs_fd* fd)
{
	dfs_lock();
	fd->ref_count --;
	/* clear this fd entry */
	if ( fd->ref_count == 0 )
	{
		rt_memset(fd, 0, sizeof(struct dfs_fd));
	}
	dfs_unlock();
};

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_open
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_open(struct dfs_fd* fd, const char *path, int flags)
{
	struct dfs_filesystem* fs;
	char *fullpath;
#ifdef DFS_USING_WORKDIR
	char full_path[DFS_PATH_MAX + 1];
#endif
	int fspathlen, result;

	/* parameter check */
	if ( fd == RT_NULL ) return -DFS_STATUS_EINVAL;

	/* make sure we have an absolute path */
	fullpath = (char*)path;
	if ( fullpath[0] != '/')
	{
#ifdef DFS_USING_WORKDIR
		/* build full path */
		fullpath = &full_path[0];
		dfs_lock();
		build_fullpath(working_directory, path, fullpath);
		dfs_unlock();
#else
		rt_kprintf(NO_WORKING_DIR);
		return -1;
#endif
	}

	dfs_log(DFS_DEBUG_INFO, ("open file:%s", fullpath));

	/* find filesystem */
	fs = dfs_filesystem_lookup(fullpath);
	if ( fs == RT_NULL ) return -DFS_STATUS_ENOENT;

	dfs_log(DFS_DEBUG_INFO, ("open in filesystem:%s", fs->ops->name));
	fd->fs = fs;

	/* initilize the fd item */
	fd->type = FT_REGULAR;
	//fd->ref_count = 1;
	fd->flags = flags;
	fd->size = 0;
	fd->pos = 0;

	fspathlen = strlen(fs->path);
	rt_memset(fd->path, 0, DFS_PATH_MAX + 1);
	if (*(fullpath + fspathlen) != '/') strcpy(fd->path, "/");
	strcat(fd->path, fullpath + fspathlen);

	/* specific file system open routine */
	if (fs->ops->open == RT_NULL)
	{
		/* clear fd */
		rt_memset(fd->path, 0, DFS_PATH_MAX + 1);

		fd->type = FT_REGULAR;
		fd->ref_count = 0;
		fd->fs = RT_NULL;
		fd->flags = 0;
		fd->size = 0;
		fd->pos = 0;
		fd->data = RT_NULL;

		return -DFS_STATUS_ENOSYS;
	}

	if ((result = fs->ops->open(fd)) < 0)
	{
		/* clear fd */
		fd->fs = RT_NULL;
		fd->flags = 0;
		fd->data = RT_NULL;

		dfs_log(DFS_DEBUG_INFO, ("open failed"));

		return result;
	}

	fd->flags |= DFS_F_OPEN;
	if ( flags & DFS_O_DIRECTORY )
	{
		fd->type = FT_DIRECTORY;
		fd->flags |= DFS_F_DIRECTORY;
	}

	dfs_log(DFS_DEBUG_INFO, ("open successful"));
	return 0;
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_close
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_close(struct dfs_fd* fd)
{
	int result = 0;

	if (fd != RT_NULL && fd->fs->ops->close != RT_NULL) result = fd->fs->ops->close(fd);

	/* close fd error, return */
	if ( result < 0 ) return result; 

	fd->flags &= ~DFS_F_OPEN;

	return result;
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_ioctl
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_ioctl(struct dfs_fd* fd, int cmd, void *args)
{
	struct dfs_filesystem* fs;

	if (fd == RT_NULL || fd->type != FT_REGULAR) return -DFS_STATUS_EINVAL;

	fs = fd->fs;
#if 0 /* not support right now */
	if (cmd == FILEGETSIZE)
	{
		if (args == RT_NULL) return -DFS_STATUS_EINVAL;

		*((rt_uint32_t *) args) = fd->size;

		return 0;
	}
	else if (cmd == FILEGETPOS)
	{
		if (args == RT_NULL) return -DFS_STATUS_EINVAL;

		*((rt_uint32_t *) args) = fd->pos;

		return 0;
	}
#endif

	if (fs->ops->ioctl != RT_NULL) return fs->ops->ioctl(fd, cmd, args);

	return -DFS_STATUS_ENOSYS;
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_read
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_read(struct dfs_fd* fd, void *buf, rt_size_t len)
{
	struct dfs_filesystem* fs;
	int result = 0;

	if (fd == RT_NULL) return -DFS_STATUS_EINVAL;
	
	fs = (struct dfs_filesystem*) fd->fs;
	if (fs->ops->read == RT_NULL) return -DFS_STATUS_ENOSYS;

	if ( (result = fs->ops->read(fd, buf, len)) < 0 ) fd->flags |= DFS_F_EOF;

	return result;
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_getdents
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_getdents(struct dfs_fd* fd, struct dfs_dirent* dirp, rt_size_t nbytes)
{
	struct dfs_filesystem* fs;

	/* parameter check */
	if (fd == RT_NULL || fd->type != FT_DIRECTORY) return -DFS_STATUS_EINVAL;

	fs = (struct dfs_filesystem*) fd->fs;
	if (fs->ops->getdents != RT_NULL) return fs->ops->getdents(fd, dirp, nbytes);

	return -DFS_STATUS_ENOSYS;
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_unlink
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_unlink(const char *path)
{
	struct dfs_filesystem* fs;
	char *fullpath, *real_path, search_path[DFS_PATH_MAX + 1];
#ifdef DFS_USING_WORKDIR
	char full_path[DFS_PATH_MAX+1];
#endif
	struct dfs_fd* fd;
	int index, fspathlen;

	/* Make sure we have an absolute path */
	fullpath = (char*)path;
	if ( fullpath[0] != '/')
	{
#ifdef DFS_USING_WORKDIR
		/* build full path */
		fullpath = full_path;
		dfs_lock();
		build_fullpath(working_directory, path, fullpath);
		dfs_unlock();
#else
		rt_kprintf(NO_WORKING_DIR);
		return -1;
#endif
	}

	if ( (fs = dfs_filesystem_lookup(fullpath)) == RT_NULL) return -DFS_STATUS_ENOENT;

	/* Check whether file is already open */
	dfs_lock();
	for (index = 0; index < DFS_FD_MAX; index++)
	{
		fd = &(fd_table[index]);
		if (fd->fs == RT_NULL) continue;

		build_fullpath(fd->fs->path, fd->path, search_path);
		if (strcmp(fullpath, search_path) == 0)
		{
			dfs_unlock();
			return -DFS_STATUS_EEXIST;
		}
	}
	dfs_unlock();

	fspathlen = strlen(fs->path);
	real_path = search_path;
	rt_memset( real_path, 0, sizeof( real_path ) );
	if (*(fullpath + fspathlen) != '/') strcpy(real_path, "/");
	strcat(real_path, fullpath + fspathlen);

	if (fs->ops->unlink != RT_NULL) return fs->ops->unlink(fs, real_path);

	return -DFS_STATUS_ENOSYS;
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_write
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_write(struct dfs_fd* fd, const void *buf, rt_size_t len)
{
	struct dfs_filesystem* fs = fd->fs;

	if (fd == RT_NULL) return -DFS_STATUS_EINVAL;
	if (fs->ops->write == RT_NULL) return -DFS_STATUS_ENOSYS;

	return fs->ops->write(fd, buf, len);
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_lseek
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_lseek(struct dfs_fd* fd, rt_off_t offset)
{
	struct dfs_filesystem* fs = fd->fs;

	if (fd == RT_NULL) return -DFS_STATUS_EINVAL;
	if (fs->ops->lseek == RT_NULL) return -DFS_STATUS_ENOSYS;

	return fs->ops->lseek(fd, offset);
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_stat
+------------------------------------------------------------------------------
| Description : get the file or directory stat description
|
| Parameters  : path, the file or directory path
|               buf,  the stat description will be saved in it
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_stat(const char *path, struct dfs_stat *buf)
{
	struct dfs_filesystem* fs;
	char* fullpath, real_path[DFS_PATH_MAX + 1];
#ifdef DFS_USING_WORKDIR
	char full_path[DFS_PATH_MAX + 1];
#endif
	int fspathlen;

	fullpath = (char*)path;
	if ( fullpath[0] != '/' )
	{
#ifdef DFS_USING_WORKDIR
		/* build full path */
		fullpath = full_path;
		dfs_lock();
		build_fullpath(working_directory, path, fullpath);
		dfs_unlock();
#else
		rt_kprintf(NO_WORKING_DIR);
		return -1;
#endif
	}

	if ( (fs = dfs_filesystem_lookup(fullpath)) == RT_NULL )
	{
		dfs_log(DFS_DEBUG_ERROR, ("can't find mounted filesystem on this path:%s", fullpath));
		return -DFS_STATUS_ENOENT;
	}

	fspathlen = strlen(fs->path);
	rt_memset(real_path, 0, sizeof(real_path));
	if (*(fullpath + fspathlen) != '/') real_path[0] = '/';
	strcat(real_path, fullpath + fspathlen);

	if (real_path[0] == '/' && real_path[1] == '\0')
	{
		/* it's the root directory */
		buf->st_dev   = 0;

		buf->st_mode = DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH |
			DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;
		buf->st_mode |= DFS_S_IFDIR | DFS_S_IXUSR | DFS_S_IXGRP | DFS_S_IXOTH;

		buf->st_size  = 0;
		buf->st_mtime = 0;
		buf->st_blksize = 512;
		return DFS_STATUS_OK;
	}
	
	if (fs->ops->stat == RT_NULL)
	{
		dfs_log(DFS_DEBUG_ERROR, ("the filesystem didn't implement this function"));
		return -DFS_STATUS_ENOSYS;
	}

	return fs->ops->stat(fs, real_path, buf);
}

/*
+------------------------------------------------------------------------------
| Function    : dfile_raw_rename
+------------------------------------------------------------------------------
| Description : 
|
| Parameters  : 
| Returns     : 
|
+------------------------------------------------------------------------------
*/
int dfile_raw_rename(const char* oldpath, const char* newpath)
{
	struct dfs_filesystem *oldfs, *newfs;
	char *oldfullpath, *newfullpath;
#ifdef DFS_USING_WORKDIR
	/* Change DFS_PATH_MAX to DFS_PATH_MAX + 1, yi.qiu@2008.09.23*/
	char old_realpath[DFS_PATH_MAX + 1], new_realpath[DFS_PATH_MAX + 1];
#endif

	oldfullpath = (char*)oldpath;
	newfullpath = (char*)newpath;

	if ( oldfullpath[0] != '/' )
	{
#ifdef DFS_USING_WORKDIR
		/* build full path */
		oldfullpath = old_realpath;
		dfs_lock();
		build_fullpath(working_directory, oldpath, oldfullpath);
		dfs_unlock();
#else
		rt_kprintf(NO_WORKING_DIR);
		return -1;
#endif
	}

	if ( newfullpath[0] != '/' )
	{
#ifdef DFS_USING_WORKDIR
		/* build full path */
		newfullpath = new_realpath;
		dfs_lock();
		build_fullpath(working_directory, newpath, newfullpath);
		dfs_unlock();
#else
		rt_kprintf(NO_WORKING_DIR);
		return -1;
#endif
	}

	if ( (oldfs = dfs_filesystem_lookup(oldfullpath)) == RT_NULL )
	{
		return -DFS_STATUS_ENOENT;
	}

	if ( (newfs = dfs_filesystem_lookup(newfullpath)) == RT_NULL )
	{
		return -DFS_STATUS_ENOENT;
	}

	if ( oldfs == newfs )
	{
		if ( oldfs->ops->rename == RT_NULL ) return -DFS_STATUS_ENOSYS;
		
		return oldfs->ops->rename(oldfs, oldfullpath, newfullpath);
	}

	/* not at same file system, return EXDEV */
	return -DFS_STATUS_EXDEV;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static char fullpath[256 + 1];
static struct dfs_fd fd;
static struct dfs_dirent dirent;
void ls(const char* pathname)
{
	struct dfs_stat stat;
	int length;

	/* list directory */
	if ( dfile_raw_open(&fd, pathname, DFS_O_DIRECTORY) == 0 )
	{
		rt_kprintf("Directory %s:\n", pathname);
		do
		{
			rt_memset(&dirent, 0, sizeof(struct dfs_dirent));
			length = dfile_raw_getdents(&fd, &dirent, sizeof(struct dfs_dirent));
			if ( length > 0 ) 
			{
				rt_memset(&stat, 0, sizeof(struct dfs_stat));

				/* build full path for each file */
				if (pathname[strlen(pathname) - 1] != '/')
					rt_snprintf(fullpath, sizeof(fullpath), "%s%c%s", pathname, '/', dirent.d_name);
				else
					rt_snprintf(fullpath, sizeof(fullpath), "%s%s", pathname, dirent.d_name);
				
				dfile_raw_stat(fullpath, &stat);
				if ( stat.st_mode & DFS_S_IFDIR )
				{
					rt_kprintf("%s\t\t<DIR>\n", dirent.d_name);
				}
				else
				{
					rt_kprintf("%s\t\t%lu\n", dirent.d_name, stat.st_size);
				}
			}
		}while(length > 0);

		dfile_raw_close(&fd);
	}
	else
	{
		rt_kprintf("No such directory\n");
	}
}
FINSH_FUNCTION_EXPORT(ls, list directory contents)

static void mkdir(const char* pathname)
{
	/* make a new directory */
	if (dfile_raw_open(&fd, pathname, DFS_O_DIRECTORY | DFS_O_CREAT) == 0)
	{
		dfile_raw_close(&fd);
	}
	else rt_kprintf("Can't mkdir %s\n", pathname);
}
FINSH_FUNCTION_EXPORT(mkdir, make a directory)

void rm(const char* filename)
{
	if (dfile_raw_unlink(filename) < 0)
	{
		rt_kprintf("Delete %s failed\n", filename);
	}
}
FINSH_FUNCTION_EXPORT(rm, remove files or directories)

void cat(const char* filename)
{
	rt_uint32_t length;
	char buffer[81];
	
	if (dfile_raw_open(&fd, filename, DFS_O_RDONLY) < 0)
	{
		rt_kprintf("Open %s failed\n", filename);
		return;
	}
	
	do
	{
		rt_memset(buffer, 0, sizeof(buffer));
		length = dfile_raw_read(&fd, buffer, 81);
		if (length > 0)
		{
			rt_kprintf("%s", buffer);
		}
	}while (length > 0);
	
	dfile_raw_close(&fd);
}
FINSH_FUNCTION_EXPORT(cat, print file)

#endif
