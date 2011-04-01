#include <rtthread.h>   
#include <dfs_def.h>   
#include <dfs_fs.h>
#include "uffs/uffs_fs.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_fd.h"
#include "uffs_ext.h"

/* mount and unmount file system */ 
int dfs_uffs_mount(struct dfs_filesystem* fs, unsigned long rwflag, const void* data)   
{
	return ((uffs_InitMountTable() == U_SUCC) ? 0 : -1);   
}      

int dfs_uffs_unmount(struct dfs_filesystem* fs)   
{
	uffs_ReleaseObjectBuf();
	return uffs_ReleaseMountTable();  
}      

int dfs_uffs_mkfs(const char* device_name)   
{        
	return uffs_format(NULL);   
}      

int dfs_uffs_statfs(struct dfs_filesystem* fs, struct statfs *buf)   
{
	int ret = U_SUCC;
	uffs_MountTable *entry = (uffs_MountTable*)(fs->dev_id->user_data);
	struct uffs_StorageAttrSt *attr = entry->dev->attr;

	buf->f_bsize  = attr->page_data_size * attr->pages_per_block;
	buf->f_blocks = attr->total_blocks;
	buf->f_bfree  = 0;

	return ret;   
}      

int dfs_uffs_open(struct dfs_fd* fd)   
{	
	int ret=U_SUCC;

	if (fd->flags & DFS_O_DIRECTORY)
	{//文件夹
		uffs_DIR *dirp;
		/* open directory */
		
		if (fd->flags & DFS_O_CREAT)
		{//创建
			ret = uffs_open(fd->path,UO_CREATE|UO_DIR);
			if(ret != U_SUCC)
			{
				return U_FAIL;
			}
		}

		dirp = uffs_opendir(fd->path);
		if(dirp == NULL) 
		{
			uffs_set_error(-UEMFILE);
			ret = U_FAIL;
		}

		fd->data = dirp;

		return U_SUCC;
	}
	else
	{//文件
		uffs_Object *fp;
		
		int mode = UO_RDONLY;

		if (fd->flags & DFS_O_WRONLY) mode |= UO_WRONLY;
		if ((fd->flags & DFS_O_ACCMODE) & DFS_O_RDWR) mode |= UO_WRONLY;
		/* Opens the file, if it is existing. If not, a new file is created. */
		if (fd->flags & DFS_O_CREAT) mode |= UO_CREATE;
		/* Creates a new file. If the file is existing, it is truncated and overwritten. */
		if (fd->flags & DFS_O_TRUNC) mode |= UO_TRUNC;
		/* Creates a new file. The function fails if the file is already existing. */
		if (fd->flags & DFS_O_EXCL) mode |= UO_EXCL;

		/* allocate a fd */
		
		/* open directory */
		fp = uffs_GetObject();
		if(fp == NULL) 
		{
			uffs_set_error(-UEMFILE);
			ret = U_FAIL;
		}

		if(uffs_OpenObject(fp, fd->path, mode) == RT_EOK)
		{
			struct uffs_stat stat_buf;

			uffs_stat(fd->path, &stat_buf);

			fd->pos  = fp->pos;
			fd->size = stat_buf.st_size;
			fd->data = fp;

			if(fd->flags & DFS_O_APPEND)
			{
				fd->pos = uffs_SeekObject(fp, 0, USEEK_END);
			}
			ret = U_SUCC;
		}
		else
		{
			/* open failed, return */
			uffs_set_error(-uffs_GetObjectErr(fp));
			uffs_PutObject(fp);
			return U_FAIL;
		}
	}

	return ret;  
}      

int dfs_uffs_close(struct dfs_fd* fd)   
{
	int ret=U_SUCC;

	if (fd->type == FT_DIRECTORY)
	{
		uffs_DIR* dirp;

		dirp = (uffs_DIR*)(fd->data);
		RT_ASSERT(dirp != RT_NULL);

		uffs_closedir(dirp);
	}
	else if (fd->type == FT_REGULAR)
	{
		uffs_Object* fp;

		fp = (uffs_Object*)(fd->data);

		RT_ASSERT(fd != RT_NULL);

		ret = uffs_CloseObject(fp);
		uffs_PutObject(fp);
	}

	return ret;   
}      

int dfs_uffs_ioctl(struct dfs_fd* fd, int cmd, void *args)   
{
	return -DFS_STATUS_ENOSYS;   
}      

int dfs_uffs_read(struct dfs_fd* fd, void* buf, rt_size_t count)   
{
	uffs_Object* fp;
	uffs_DIR* dirp;

	if (fd->type == FT_DIRECTORY)
	{
		dirp = (uffs_DIR*)(fd->data);
		fp = dirp->obj;
	}
	else
	{
		fp = (uffs_Object*)(fd->data);
	}

	RT_ASSERT(fd != RT_NULL);

	/* update position */
	fd->pos  = fp->pos;

	return uffs_ReadObject(fp, buf, count);  
}      

int dfs_uffs_write(struct dfs_fd* fd, const void* buf, rt_size_t count)   
{
	uffs_Object* fp;
	u32 byte_write;
	struct uffs_stat stat_buf;

	if(fd->type == FT_DIRECTORY)
	{
		return -DFS_STATUS_EISDIR;
	}

	fp = (uffs_Object*)(fd->data);
	RT_ASSERT(fp != RT_NULL);

	byte_write = uffs_WriteObject(fp, buf, count);

	/* update position and file size */
	fd->pos  = fp->pos;

	uffs_stat(fp->name, &stat_buf);
	fd->size = stat_buf.st_size;

	return byte_write;   
}      

int dfs_uffs_flush(struct dfs_fd* fd)   
{
	uffs_Object* fp;

	fp = (uffs_Object*)(fd->data);
	RT_ASSERT(fp != RT_NULL);

	return uffs_FlushObject(fp); 
}      

int dfs_uffs_lseek(struct dfs_fd* fd, rt_off_t offset)   
{
	uffs_Object* fp;

	fp = (uffs_Object*)(fd->data);
	RT_ASSERT(fp != RT_NULL);

	return uffs_SeekObject(fp, offset, USEEK_SET);
}      

int dfs_uffs_getdents(struct dfs_fd* fd, struct dirent* dir, rt_uint32_t count)   
{
	uffs_DIR* dirp;
	struct uffs_dirent *ent;
	rt_uint32_t index;
	struct dirent* d;

	dirp = (uffs_DIR*)(fd->data);
	RT_ASSERT(dirp != RT_NULL);

	/* make integer count */
	count = (count / sizeof(struct dirent)) * sizeof(struct dirent);
	if ( count == 0 ) return -DFS_STATUS_EINVAL;

	index = 0;
	while (1)
	{
		d = dir + index;

		ent = uffs_readdir(dirp);
		if(ent == RT_NULL)break;


		d->d_type = DFS_DT_DIR;

		d->d_namlen = ent->d_namelen;
		d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
		rt_strncpy(d->d_name, ent->d_name, rt_strlen(ent->d_name) + 1);

		index ++;
		if ( index * sizeof(struct dirent) >= count )
			break;
	}
	return index * sizeof(struct dirent);
}      

//Delete a File or Directory
int dfs_uffs_unlink(struct dfs_filesystem* fs, const char* path)   
{
	int ret;
	int err = 0;

	ret = uffs_DeleteObject(path, &err);
	uffs_set_error(-err);

	return ret;   
}      

int dfs_uffs_stat(struct dfs_filesystem* fs, const char* path, struct stat* st)   
{
	int ret=U_SUCC;
	struct uffs_stat stat_buf;

	ret = uffs_stat(path, &stat_buf);

	if (ret == U_SUCC)
	{
		st->st_dev = 0;
		//st->st_mode = stat_buf.st_mode;
		
		st->st_mode = DFS_S_IFREG | DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH |
		DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;
		if (stat_buf.st_mode & US_IFDIR)
		{
			st->st_mode &= ~DFS_S_IFREG;
			st->st_mode |= DFS_S_IFDIR | DFS_S_IXUSR | DFS_S_IXGRP | DFS_S_IXOTH;
		}
		if (stat_buf.st_mode & US_IREAD)
			st->st_mode &= ~(DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH);
		st->st_size = stat_buf.st_size;
		st->st_mtime= stat_buf.st_mtime;
		st->st_blksize= stat_buf.st_blksize;

		return U_SUCC;
	}

	return U_FAIL;
}      

int dfs_uffs_rename(struct dfs_filesystem* fs, const char* oldpath, const char* newpath)   
{
	int ret;
	int err = 0;

	ret = uffs_RenameObject(oldpath, newpath, &err);
	uffs_set_error(-err);

	return ret;  
}      

struct dfs_filesystem_operation _uffs =    
{           
	"uffs",           
	dfs_uffs_mount,           
	dfs_uffs_unmount,           
	dfs_uffs_mkfs,           
	dfs_uffs_statfs,              
	dfs_uffs_open,           
	dfs_uffs_close,           
	dfs_uffs_ioctl,           
	dfs_uffs_read,           
	dfs_uffs_write,           
	dfs_uffs_flush,           
	dfs_uffs_lseek,           
	dfs_uffs_getdents,           
	dfs_uffs_unlink,           
	dfs_uffs_stat,           
	dfs_uffs_rename,   
};      

int dfs_uffs_init(void)   
{       
	/* register UFFS file system */       
	return dfs_register(&_uffs);   
} 

