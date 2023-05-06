#ifndef DFS_MNT_H__
#define DFS_MNT_H__

#include <rtservice.h>
#include <rtthread.h>

struct dfs_mnt;
struct dfs_dentry;
struct dfs_filesystem_ops;

struct dfs_mnt
{
    struct dfs_mnt *parent;         /* 指向此文件系统的挂载点所属的文件系统，即父文件系统 */
    struct dfs_dentry *root;        /* 指向这个文件系统根的dentry*/

    rt_list_t sibling;              /* 兄弟挂载点，并列链表 */
    rt_list_t child;                /* 子挂载点链表 */

    char *fullpath;                 /* 相对于dfs的目录树, 这个fullpath 表示从"/"算起的挂接路径 */
    int flags;                      /*此文件系统的挂载标志*/

#define MNT_IS_ALLOCED 0x1          /* 当前mnt结构体初始化成功 */
#define MNT_IS_ADDLIST 0x2          /* 当前mnt结构体已经加入链表中 */
#define MNT_IS_MOUNTED 0x4          /* 当前mnt结构体已经挂接成功 */
    struct dfs_dentry *mountpoint;  /* 指向此文件系统的挂载点的dentry */

    rt_atomic_t ref_count;          /* reference count */

    rt_device_t dev_id;             /* 挂接的设备 */
    const struct dfs_filesystem_ops *fs_ops;

    void *data;
};

struct dfs_mnt *dfs_mnt_create(const char *path);
int dfs_mnt_destroy(struct dfs_mnt* mnt);
int dfs_mnt_list(struct dfs_mnt* mnt);
int dfs_mnt_insert(struct dfs_mnt* mnt, struct dfs_mnt* child);

struct dfs_mnt *dfs_mnt_lookup(const char *path);
const char *dfs_mnt_get_mounted_path(struct rt_device *device);

struct dfs_mnt* dfs_mnt_ref(struct dfs_mnt* mnt);
int dfs_mnt_unref(struct dfs_mnt* mnt);

rt_bool_t dfs_mnt_has_child_mnt(struct dfs_mnt *mnt, const char* fullpath);

#endif
