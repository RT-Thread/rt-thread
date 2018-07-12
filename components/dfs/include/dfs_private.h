#ifndef DFS_PRIVATE_H__
#define DFS_PRIVATE_H__

#include <dfs.h>

#ifdef DFS_DEBUG_ENABLE
#define DBG_ENABLE

#ifdef RT_DFS_DEBUG_LOG_LEVEL_0
#define DBG_LEVEL			DBG_LOG
#endif

#ifdef RT_DFS_DEBUG_LOG_LEVEL_1
#define DBG_LEVEL			DBG_INFO
#endif

#ifdef RT_DFS_DEBUG_LOG_LEVEL_2
#define DBG_LEVEL			DBG_WARNING
#endif

#ifdef RT_DFS_DEBUG_LOG_LEVEL_3
#define DBG_LEVEL			DBG_ERROR
#endif
#endif

#define DBG_SECTION_NAME	"[ DFS]"
#define DBG_COLOR
#include <rtdbg.h>

#define NO_WORKING_DIR  "system does not support working directory\n"

/* extern variable */
extern const struct dfs_filesystem_ops *filesystem_operation_table[];
extern struct dfs_filesystem filesystem_table[];
extern const struct dfs_mount_tbl mount_table[];

extern char working_directory[];

#endif
