/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs.c, the implementation of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2002-12-31     ffxz         The first version.                     
| 2005-01-22     ffxz         Clean up the code.                     
+------------------------------------------------------------------------------
*/
#include <dfs_def.h>
#include <dfs_config.h>

#include <dfs_fs.h>
#include <dfs_raw.h>

#include <string.h>

/* Global variables */
struct dfs_filesystem_operation* filesystem_operation_table[DFS_FILESYSTEM_TYPES_MAX + 1];
struct dfs_filesystem filesystem_table[DFS_FILESYSTEMS_MAX + 1];

rt_sem_t filesystem_table_lock;
rt_sem_t filesystem_operation_table_lock;

#ifdef RT_USING_WORKDIR	
char working_directory[DFS_PATH_MAX + 1];
rt_sem_t working_directory_lock;
#endif

struct dfs_fd fd_table[DFS_FD_MAX + 1];
rt_sem_t  fd_table_lock;

/*
+------------------------------------------------------------------------------
| Function    : dfs_init
+------------------------------------------------------------------------------
| Description : Inits the Device Filesystem
| Parameters  : null
| Returns     : null
+------------------------------------------------------------------------------
*/
void dfs_init()
{
	int index;

	/* clear filesystem operations table */
	for (index = 0; index < DFS_FILESYSTEM_TYPES_MAX + 1; index++) 
		filesystem_operation_table[index] = RT_NULL;

	/* create filesystem operations table lock */
	filesystem_operation_table_lock = rt_sem_create("sem_fot", 1, RT_IPC_FLAG_FIFO); 

	/* clear filesystem table */
	for (index = 0; index < DFS_FILESYSTEMS_MAX + 1; index++)
	{
		rt_memset(filesystem_table[index].path, 0, DFS_PATH_MAX + 1);

		filesystem_table[index].ops = RT_NULL;
		filesystem_table[index].dev_id = 0;
		filesystem_table[index].block_id = 0;
		filesystem_table[index].data = RT_NULL;
	}

	/* create filesystem table lock */
	filesystem_table_lock = rt_sem_create("sem_fst", 1, RT_IPC_FLAG_FIFO); 

#ifdef RT_USING_WORKDIR	
	/* set current working directory */
	strcpy(working_directory, "/");
	working_directory_lock = rt_sem_create("sem_wd", 1, RT_IPC_FLAG_FIFO); 
#endif

	/* clean fd table */
	for ( index = 0; index < DFS_FD_MAX; index ++)
	{
		rt_memset(&fd_table[index], 0, sizeof(struct dfs_fd));
	}

	/* create fd table lock */
	fd_table_lock = rt_sem_create("sem_fdt", 1, RT_IPC_FLAG_FIFO); 

#if defined(RT_USING_FINSH) && !defined(FINSH_USING_SYMTAB)
	dfs_export_finsh();
#endif
}

