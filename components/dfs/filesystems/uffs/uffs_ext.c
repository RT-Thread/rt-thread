/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  uffs filesystem examples.
*/
#include <rtthread.h>

//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uffs/uffs_config.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_find.h"
#include "uffs/uffs_fd.h"
#include "emu/cmdline.h"
#include "uffs_ext.h"

#include <dfs_posix.h>
#include <rtgui/filerw.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#define PFX "exp: "

#define MAX_PATH_LENGTH 128

#if (0)
//uffs拷贝函数,参数之间加空格
//需要从elm拷贝到uffs时(跨文件系统),参数名称前加::
//例如uffs_copy("::/01.hdc  /dir1/01.hdc")
//上例从SD卡拷贝一个文件01.hdc到flash中,
//也可用dfs的函数,那样就不用考虑是否跨文件系统了.
int uffs_copy(const char *tail)
{
	const char *src;
	const char *des;
	char buf[100];
	int fd1=-1, fd2=-1;
	int len;
	int src_local = FALSE, des_local = FALSE;
	int fd3=-1, fd4=-1;

	if(!tail) 
		return FALSE;

	src = cli_getparam(tail, &des);

	if(!des)
		return FALSE;

	if(memcmp(src, "::", 2) == 0) 
	{
		src += 2;
		src_local = TRUE;
	}
	if(memcmp(des, "::", 2) == 0) 
	{
		des += 2;
		des_local = TRUE;
	}
	
	if(src_local) 
	{	
		//if((fp1 = fopen(src, "rb")) == NULL) 
		if((fd3 = open(src,O_RDONLY,0)) < 0)
		{
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", src);
			goto fail_ext;
		}
	}
	else 
	{
		if((fd1 = uffs_open(src, UO_RDONLY)) < 0) 
		{
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", src);
			goto fail_ext;
		}
	}

	if(des_local) 
	{
		if((fd4 = open(des,O_WRONLY | O_CREAT,0)) < 0) 
		{
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", des);
			goto fail_ext;
		}
	}
	else 
	{	
		if((fd2 = uffs_open(des, UO_RDWR|UO_CREATE|UO_TRUNC)) < 0) 
		{
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", des);
			goto fail_ext;
		}
	}
	
	uffs_Perror(UFFS_ERR_NORMAL, "copy %s to %s... ",src,des);

	while((src_local ? (1) : (uffs_eof(fd1) == 0))) 
	{
		if(src_local) 
		{
			len = read(fd3, buf, sizeof(buf));
		}
		else 
		{
			len = uffs_read(fd1, buf, sizeof(buf));
		}
		if(len == 0) 
			break;
		if(len < 0) 
		{
			uffs_Perror(UFFS_ERR_NORMAL, "read file %s fail!", src);
			break;
		}
		if(des_local) 
		{
			if(write(fd4, buf, len) != len) 
			{
				uffs_Perror(UFFS_ERR_NORMAL, "write file %s fail!", des);
				break;
			}
		}
		else 
		{
			if(uffs_write(fd2, buf, len) != len) 
			{
				uffs_Perror(UFFS_ERR_NORMAL, "write file %s fail ?", des);
				break;
			}
		}
	}
	uffs_Perror(UFFS_ERR_NORMAL, "succ.");
fail_ext:
	if(fd1 > 0)
		uffs_close(fd1);
	if(fd2 > 0)
		uffs_close(fd2);
	if(fd3 > 0) 
		close(fd3);
	if(fd4 > 0)
		close(fd4);

	return TRUE;
}
FINSH_FUNCTION_EXPORT(uffs_copy, copy files. local file start with ::)
#endif

//计算路径下的文件(夹)个数
int CountFileUnder(const char *dir)
{
	int count = 0;
	uffs_DIR *dirp;

	dirp = uffs_opendir(dir);
	if(dirp) 
	{
		while(uffs_readdir(dirp) != NULL)
			count++;
		if(dirp != NULL)
			uffs_closedir(dirp);
	}
	return count;
}

/*
 * 函数功能: 列出文件清单
 * 输入参数: name:分区名称
 * 返回参数: 成功:TRUE,失败:rt_false
 */
int uffs_ls(const char *name)
{
	uffs_DIR *dirp;
	struct uffs_dirent *ent;
	struct uffs_stat stat_buf;
	int count = 0;
	char buf[MAX_FILENAME_LENGTH+2];
	char *sub;

	if(name == NULL) 
	{
		return FALSE;
	}

	dirp = uffs_opendir(name); //会获得一个uffs_DIR实例

	if(dirp == NULL) 
	{
		rt_kprintf("Can't open '%s' for list\n", name);
	}
	else 
	{
		rt_kprintf("%-16s%-8s%-8s%-8s\n","name","type","size","serial");
		rt_kprintf("-----------------------------------------\n");
		ent = uffs_readdir(dirp);
		while(ent) 
		{
			rt_kprintf("%-16s", ent->d_name);
			strcpy(buf, name);
			sub = buf;
			if(name[strlen(name)-1] != '/')
				sub = strcat(buf, "/");
			sub = strcat(sub, ent->d_name);

			if(ent->d_type & FILE_ATTR_DIR) 
			{
				sub = strcat(sub, "/");
				rt_kprintf("%-8s", "<DIR>");
				rt_kprintf("%-8d", CountFileUnder(sub));
			}
			else
			{
				uffs_stat(sub, &stat_buf);
				rt_kprintf("%-8s", "");
				rt_kprintf("%-8d", stat_buf.st_size);
			}
			rt_kprintf("%-8d\n", ent->d_ino);
			count++;
			ent = uffs_readdir(dirp);
		}
		
		if(dirp != NULL)
			uffs_closedir(dirp);

		rt_kprintf("Total: %d objects.\n", count);
	}

	return TRUE;
}


/*
 * 函数功能: 格式化分区
 * 输入参数: 分区名称
 * 返回参数: 
 */
int uffs_format(const char *name)
{
	int ret;
	const char *mount = "/";
	uffs_Device *dev;

	if(name) 
	{
		mount = name;
	}

	dev = uffs_GetDeviceFromMountPoint(mount);
	if(dev == NULL) 
	{
		uffs_Perror(UFFS_ERR_NORMAL, "Can't get device from mount point.");
	}
	else 
	{
		if(dev->ref_count == 1) 
		{
			ret = uffs_FormatDevice(dev);
			uffs_Perror(UFFS_ERR_NORMAL, "Format %s.",ret==RT_EOK?"succ":"fail");
		}
		else 
		{
			uffs_Perror(UFFS_ERR_NORMAL, "dev->ref_count: %d, can't format this device.", dev->ref_count);
		}
		uffs_PutDevice(dev);
	}
	return TRUE;	
}

/*
 * 函数功能: 创建一个文件
 * 输入参数: 文件名称
 * 返回参数: 
 */
int uffs_mkfile(const char *name)
{
	uffs_Object *fp;
	int ret = 0;
	int err = 0;

	fp = uffs_GetObject();	

	if(fp != NULL) 
	{
		if(uffs_CreateObject(fp, name, UO_CREATE) != U_SUCC) 
		{
			err = fp->err;
			ret = -1;
			uffs_Perror(UFFS_ERR_NORMAL, "Create %s fail, err: %d", name, uffs_get_error());
		}
		else 
		{
			uffs_Perror(UFFS_ERR_NORMAL, "Create %s succ.", name);
			uffs_CloseObject(fp);
			ret = 0;
		}
		uffs_PutObject(fp);
	}
	else 
	{
		err = UEMFILE;
		ret = -1;
	}
	
	uffs_set_error(-err);
	return ret;
}
#if (0)
#ifdef RT_USING_FINSH
FINSH_FUNCTION_EXPORT(uffs_ls, list uffs system files.)
FINSH_FUNCTION_EXPORT(uffs_mkfile, make uffs system file.)
FINSH_FUNCTION_EXPORT(uffs_mkdir, make uffs system dir.)
FINSH_FUNCTION_EXPORT(uffs_rmdir, remove uffs system dir.)
FINSH_FUNCTION_EXPORT(uffs_format, format uffs partition.)
#endif
#endif
