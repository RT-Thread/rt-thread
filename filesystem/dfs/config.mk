#+------------------------------------------------------------------------------
#|        Device FileSystem                                           
#+------------------------------------------------------------------------------
#|        Copyright 2004, 2005  www.fayfayspace.org.                  
#|        All rights reserved.                                        
#+------------------------------------------------------------------------------
#| File      : config.mk, the configuration of makefile               
#+------------------------------------------------------------------------------
#| Chang Logs:                                                        
#| Date           Author       notes                                  
#| 2005-01-22     ffxz         The first version.                     
#+------------------------------------------------------------------------------

KERNEL_ROOT=$(DFS_ROOT_DIR)/../..
include $(KERNEL_ROOT)/config.mk

CFLAGS	+=-I$(KERNEL_ROOT)/include -I$(DFS_ROOT_DIR)/include -I.

# Source and objects
DFS_SRC	= $(DFS_ROOT_DIR)/src/dfs_fs.c $(DFS_ROOT_DIR)/src/dfs_init.c \
	$(DFS_ROOT_DIR)/src/dfs_util.c $(DFS_ROOT_DIR)/src/dfs_raw.c \
	$(DFS_ROOT_DIR)/src/dfs_api.c $(DFS_ROOT_DIR)/src/dfs_task.c \
	$(DFS_ROOT_DIR)/src/dfs_cache.c

ifneq ($(RT_USING_NEWLIB), 1)
DFS_SRC += $(DFS_ROOT_DIR)/src/dfs_posix.c
endif

DFS_OBJS= $(DFS_SRC:.c=.o)

FAT_SRC	= $(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_init.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_mount.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_fat.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_misc.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_file.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_cache.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_filename.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_direntry.c \
	$(DFS_ROOT_DIR)/filesystems/fatfs/fatfs_mkfs.c
FAT_OBJS	= $(FAT_SRC:.c=.o)
