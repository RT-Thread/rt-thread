---------------------------------------------------------------------------
This file is part of Device File System in RT-Thread RTOS
COPYRIGHT (C) 2004-2011, RT-Thread Development Team

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

Change Logs:
Date           Author       Notes
2013-12-15     Jone.Chen    yuhua8688@tom.com
-----------------------------------------------------------------

This is a read-only file system,Commonly used in the web server

1.The file directory is about to build WFFS file system
2.makefsfile.zip is a tool for building the file system,UnZip it
  For example, will build web directory for the file system(in cmd)	

  makefsfile.exe -i web -o filedata.h

  notes:
  -i input directory 
  -o output file
3.Within the project include dfs_wffs.c
4.register and mount wffs
  define RT_USING_DFS_WFFS micro in rtconfig.h

 #ifdef RT_USING_DFS
 {
 	/* init the device filesystem */
	dfs_init();
	#ifdef RT_USING_DFS_WFFS
	/* init the wffs filesystam*/
	dfs_wffs_init();

	/* mount wffs as root directory */
	if (dfs_mount(RT_NULL, "/", "wffs", 0, 0) == 0)
	{
		rt_kprintf("File System initialized!\n");
	}
	else
		rt_kprintf("File System initialzation failed!\n");
	#endif
 }
 #endif
5.use dfs open() read() close() lseek() Operation file

