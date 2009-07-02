 /*
 * File      : efs.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, 2007, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-08-16     Yi.Qiu		The first version.
 */
 
#include "efs.h"
#include "ls.h"
#include "ui.h"
#include "fat.h"
#include <string.h>

#define EFS_MAX		2

struct dfs_filesystem_operation efs;

/**
 * This function will initialize efsl to DFS interface.
 * 
 * @return 0 on succesful
 */
int efsl_init()
{
	/* init EFS filesystem operations */
	efs.name[0] = 'e';
	efs.name[1] = 'f';
	efs.name[2] = 's';
	efs.name[3]	= '\0';

	efs.mount 	= efs_mount;
	efs.unmount = efs_unmount;
	efs.open 	= efs_open;
	efs.close 	= efs_close;
	efs.ioctl 	= efs_ioctl;
	efs.read 	= efs_read;
	efs.write 	= efs_write;
	efs.lseek 	= efs_lseek;
	efs.getdents= efs_getdents;
	efs.unlink 	= efs_unlink;
	efs.stat 	= efs_stat;
	efs.rename 	= efs_rename;

	/* register EFS file system */
	dfs_register(&efs);

	return 0;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_mount(struct dfs_filesystem* fs)
{
	efsl_fs* efsfs;
	int result;

	/* allocate an EFS filesystem entry */
	efsfs = (efsl_fs*) rt_malloc (sizeof(efsl_fs));

	/* init efs filesystem struct */
	efsfs->partition.ioman = rt_malloc(sizeof(IOManager));
	efsfs->partition.ioman->device = fs->dev_id;

	part_initPartition(&efsfs->partition);
	ioman_init(efsfs->partition.ioman);
	result = fs_initFs(&efsfs->filesystem ,&efsfs->partition);

	/* set to DFS filesystem user data */
	fs->data = efsfs;
	
	return result;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_unmount(struct dfs_filesystem* fs)
{
	efsl_fs* efsfs;

	efsfs = (efsl_fs*) fs->data;
	if ( efsfs == RT_NULL ) return -DFS_STATUS_EINVAL;

	fs_flushFs(&efsfs->filesystem);
	rt_free(efsfs->partition.ioman);
	rt_free(efsfs);

	fs->data = RT_NULL;

	return 0;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_open(struct dfs_fd* file)
{
	File* efsfile;
	DirList* efsdir;
	efsl_fs* efsfs = (efsl_fs*)(file->fs->data);
	int result = 0;
	
	/* parameter check */
	if ( file == RT_NULL || file->fs == RT_NULL || 
		file->fs->data == RT_NULL ) 
	{	
		dfs_log(DFS_DEBUG_INFO, ("Invalid argument"));		
		return -DFS_STATUS_EINVAL;
	}

	/* open directory */
	if(file->flags & DFS_O_DIRECTORY)
	{
		/* write directory is not supported */
		if(file->flags & DFS_O_WRONLY || file->flags & DFS_O_RDWR)
		{
			dfs_log(DFS_DEBUG_INFO, ("write directory isn't supported"));			
			return -DFS_STATUS_EISDIR;
		}
		
		/* create directory */
		if(file->flags & DFS_O_CREAT)
		{
			dfs_log(DFS_DEBUG_INFO, ("create directory"));
			result = mk_dir(&efsfs->filesystem, file->path);
			if(result < 0) 
			{
				dfs_log(DFS_DEBUG_INFO, ("directory %s has existed", file->path));
				return -DFS_STATUS_EEXIST;
			}	
		}
		
		efsdir = (DirList*)rt_malloc(sizeof(DirList));
		if(efsdir == RT_NULL) 
		{
			dfs_log(DFS_DEBUG_INFO, ("memory alloc failed"));
			return -DFS_STATUS_ENOMEM;		
		}
		
		result = ls_openDir(efsdir, &efsfs->filesystem, file->path);
		if(result < 0)
		{
			dfs_log(DFS_DEBUG_INFO, ("open directory %s failed", file->path));
			rt_free(efsdir);
		}	
		else 
		{
			file->data = efsdir;
		}	
	}
	/* open file */
	else
	{
		efsfile = (File *)rt_malloc(sizeof(File));
		if (efsfile == RT_NULL) 
		{
			dfs_log(DFS_DEBUG_INFO, ("memory alloc failed"));			
			return -DFS_STATUS_ENOMEM;		
		}

		result = file_fopen(efsfile, &efsfs->filesystem, file->path, file->flags);
		if(result < 0)	
		{	
			dfs_log(DFS_DEBUG_INFO, ("open file %s failed", file->path));
			rt_free(efsfile);
		}	
		else
		{
			file->pos  = efsfile->FilePtr;
			file->size = efsfile->FileSize;
			file->data = efsfile;
		}
	}

	return result;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_close(struct dfs_fd* file)
{
	int result = 0;
	
	if (!file || !(file->flags & DFS_F_OPEN)) return -DFS_STATUS_EBADF;
	
	if(!(file->flags & DFS_F_DIRECTORY)) 
		result = file_fclose((File *)file->data);
	else
	{
		dfs_log(DFS_DEBUG_INFO, ("close a directory, %s", file->path));
	}

	dfs_log(DFS_DEBUG_INFO, ("close a file, %s", file->path));

	/* free directory or file */
	rt_free(file->data);
	file->data = RT_NULL;

	return result;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_ioctl(struct dfs_fd* file, int cmd, void* args)
{
	return 0;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_read(struct dfs_fd* file, void* buf, rt_size_t len)
{
	File* efsfile = file->data;
	int result = 0;

	/* parameter check */
	RT_ASSERT(efsfile != RT_NULL);
	
	result = file_read(efsfile, len, buf);
	file->pos = efsfile->FilePtr;

	dfs_log(DFS_DEBUG_INFO, ("read file %s %d bytes", file->path, result));
	
	return result;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_write(struct dfs_fd* file, const void* buf, rt_size_t len)
{
	File* efsfile = file->data;
	int result = 0;

	/* parameter check */
	RT_ASSERT(efsfile != RT_NULL);
	
	result = file_write(efsfile, len, (euint8 *)buf);
	file->pos = efsfile->FilePtr;
	file->size = efsfile->FileSize;

	dfs_log(DFS_DEBUG_INFO, ("write file %s %d bytes", file->path, result));
	
	return result;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_lseek(struct dfs_fd* file, rt_off_t offset)
{
	int result = 0;
	DirList* efsdir;
	efsl_fs* efsfs = (efsl_fs *)file->fs->data;

	/* parameter check */
	RT_ASSERT(efsfs   != RT_NULL);

	/* seek directory */
	if(file->flags & DFS_O_DIRECTORY)
	{
		efsdir = (DirList*)file->data;
		
		/* only support offset equels zero */
		if(offset == 0)
		{
			result = ls_openDir(efsdir, &efsfs->filesystem, file->path);
			if(result < 0)
			{
				dfs_log(DFS_DEBUG_INFO, ("open directory %s failed", file->path));
			}		
		}
		/* should implement in future version */
		else
		{
			dfs_log(DFS_DEBUG_INFO, ("not implement"));
		}
	}
	/* seek file */
	else
	{
		File* efsfile = file->data;
		
		/* parameter check */
		if ( efsfile == RT_NULL) return -DFS_STATUS_EBADF;

		result = file_setpos(efsfile, offset);
	}
	
	return result;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_getdents(struct dfs_fd* file, struct dfs_dirent* dirp, rt_uint32_t count)
{
	DirList* efsdir = (DirList*)file->data;
	struct dfs_dirent* d;
	int result = 0;

	/* fd check */
	if ( efsdir == RT_NULL) return -DFS_STATUS_EBADF;

	/* flags check */
	if(!(file->flags & DFS_F_DIRECTORY)) return -DFS_STATUS_EBADF;

	/* make integer count */
	count = (count / sizeof(struct dfs_dirent)) * sizeof(struct dfs_dirent);
	if ( count == 0 ) return -DFS_STATUS_EINVAL;

	while(1)
	{
		/* it's the end of file */
		if(ls_getNext(efsdir) < 0) return 0;

		d = dirp + result;
    		/* copy dirent name */
		fat_ShortnameToString(efsdir->currentEntry.FileName, d->d_name);
		d->d_reclen = (euint16)sizeof(struct dfs_dirent);	

		/* set type */
		d->d_type = DFS_DT_UNKNOWN;
		if (efsdir->currentEntry.Attribute & ATTR_DIRECTORY ) d->d_type &= DFS_DT_DIR;
		else d->d_type &= DFS_DT_REG;

		result ++;

		/* is it enough? */
		if ( result * sizeof(struct dfs_dirent) >= count )
			break;
	}

	return result * sizeof(struct dfs_dirent);
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_unlink(struct dfs_filesystem* fs, const char* path)
{
	efsl_fs* efsfs;

	RT_ASSERT(fs   != RT_NULL);
	efsfs = (efsl_fs *)fs->data;

	RT_ASSERT(path  != RT_NULL);
	RT_ASSERT(efsfs != RT_NULL);
	
	return un_link(&efsfs->filesystem, (euint8 *)path);
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_stat(struct dfs_filesystem* fs, const char *path, struct dfs_stat *st)
{
	FileRecord entry;
	FileLocation loc;
	efsl_fs* efsfs = (efsl_fs*)(fs->data);

	/* parameter check */
	RT_ASSERT(efsfs != RT_NULL);
	
	/* file does not exist */
	if(fs_findFile(&efsfs->filesystem, (char *)path, &loc, 0) == 0)
	{
		dfs_log(DFS_DEBUG_ERROR, ("can't find direntry"));		
		return -DFS_STATUS_ENOENT;
	}

	dir_getFileStructure(&efsfs->filesystem, &entry, &loc);

	st->st_dev = fs->dev_id;
	st->st_mode = DFS_S_IFREG | DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH | 
	DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;
	if ( entry.Attribute & ATTR_DIRECTORY )
	{
		st->st_mode &= ~DFS_S_IFREG;
		st->st_mode |= DFS_S_IFDIR | DFS_S_IXUSR | DFS_S_IXGRP | DFS_S_IXOTH;
	}
	if ( entry.Attribute & ATTR_READ_ONLY )
		st->st_mode &= ~(DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH);

	st->st_size  = entry.FileSize;
	st->st_mtime = entry.WriteTime;
	
	return 0;
}

/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_rename(struct dfs_filesystem* fs, const char* oldpath, const char* newpath)
{
	FileRecord old_entry, new_entry;
	FileLocation old_loc, new_loc;
	efsl_fs* efsfs;
	eint8 fatfilename[11];
	
	efsfs = (efsl_fs*) fs->data ;
	RT_ASSERT(efsfs != RT_NULL);

	dir_getFatFileName((eint8 *)newpath, &fatfilename[0]);	
	
	/* parameters check */
	if (strlen(oldpath) > DFS_PATH_MAX || 
		strlen(newpath) > DFS_PATH_MAX ||
		/* old path is a directory that contains newpath */
		strncmp(oldpath, newpath, strlen(newpath)) == 0) 
		{
			dfs_log(DFS_DEBUG_ERROR, ("old path is a directory that contains newpath"));					
			return -DFS_STATUS_EINVAL;
		}	

	/* if can't find old direntry */
	if(fs_findFile(&efsfs->filesystem, (eint8 *)oldpath, &old_loc, 0) == 0)
	{
		dfs_log(DFS_DEBUG_ERROR, ("can't find old direntry"));		
		return -DFS_STATUS_ENOENT;
	}
	dir_getFileStructure(&efsfs->filesystem, &old_entry, &old_loc);

	/* if the new direntry exist */
	if(fs_findFile(&efsfs->filesystem, (eint8 *)newpath, &new_loc, 0) > 0)
	{
		dfs_log(DFS_DEBUG_ERROR, ("new direntry existed"));
		return -DFS_STATUS_ENOENT;
	}
	if(fs_findFreeFile(&efsfs->filesystem, (eint8 *)newpath, &new_loc, 0))
	{
		memCpy(&old_entry, &new_entry, sizeof(FileRecord));	
		memCpy(fatfilename, new_entry.FileName, 11);
		dir_createDirectoryEntry(&efsfs->filesystem, &new_entry, &new_loc);
	}

	/* delete the old direntry */
	old_entry.FileName[0] = 0xe5;
	dir_updateDirectoryEntry(&efsfs->filesystem, &old_entry, &old_loc);	

	return 0;
}
