# 进程文件系统 (procfs)

## 数据结构

```c
struct proc_dentry
{
    rt_uint32_t mode;
    rt_atomic_t ref_count;

    struct proc_dentry *parent;
    struct dfs_vfs_node node;

    const struct dfs_file_ops *fops;
    const struct proc_ops *ops;

    char *name;
    void *data;
};
```

```log
root { mode: S_IFDIR, ref_count: 1, parent: root, name: /, child->next: file1->node }
    |
    |—— file1 { mode: S_IFREG, ref_count: 1, parent: root, name: file1, node->next: link1->node }
    |—— link1 { mode: S_IFLNK, ref_count: 1, parent: root, name: link1, data: fullpath, node->next: dir1->node }
    |—— dir1 { mode: S_IFDIR, ref_count: 1, parent: root, name: dir1, node->next: file3->node, child->next: file2->node }
    |    |
    |    |—— dir2 { mode: S_IFDIR, ref_count: 1, parent: dir1, name: dir2, node->next: link2->node }
    |    |—— link2 { mode: S_IFLNK, ref_count: 1, parent: dir1, name: link2, data: fullpath, node->next: file2->node }
    |    |—— file2 { mode: S_IFREG, ref_count: 1, parent: dir1, name: file2 }
    |
    |—— file3 { mode: S_IFREG, ref_count: 1, parent: root, name: file3 }
```

## API 介绍

```c
struct proc_dentry *dfs_proc_find(const char *name);

struct proc_dentry *proc_mkdir_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                    const struct dfs_file_ops *fops, void *data);
struct proc_dentry *proc_mkdir_mode(const char *name, mode_t mode, struct proc_dentry *parent);
struct proc_dentry *proc_mkdir(const char *name, struct proc_dentry *parent);

struct proc_dentry *proc_create_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                     const struct dfs_file_ops *fops, void *data);

struct proc_dentry *proc_symlink(const char *name, struct proc_dentry *parent, const char *dest);

struct proc_dentry *proc_acquire(struct proc_dentry *dentry);
void proc_release(struct proc_dentry *dentry);

void proc_remove(struct proc_dentry *dentry);
```

- dfs_proc_find

  查找指定节点，并返回节点数据指针

  | 入参 | 说明                                                 |
  | ---- | ---------------------------------------------------- |
  | name | 从 procfs 的 root 起始的完整路径，比如 “/dir1/file2” |

- proc_mkdir_data

  创建一个目录，并返回节点数据指针

  | 入参   | 说明                                                         |
  | ------ | ------------------------------------------------------------ |
  | name   | 从 procfs 的 root 起始的完整路径，比如 “/dir1/file2”<br />从 parent 起始的完整路径 |
  | mode   | 权限配置                                                     |
  | parent | 指定创建目录的起始节点                                       |
  | fops   | 文件操作接口配置                                             |
  | data   | 私有数据                                                     |

- proc_mkdir_mode

  创建一个目录，并返回节点数据指针

  | 入参   | 说明                                                         |
  | ------ | ------------------------------------------------------------ |
  | name   | 从 procfs 的 root 起始的完整路径，比如 “/dir1/file2”<br />从 parent 起始的完整路径 |
  | mode   | 权限配置                                                     |
  | parent | 指定创建目录的起始节点                                       |

- proc_mkdir

  创建一个目录，并返回节点数据指针

  | 入参 | 说明                                                         |
  | ---- | ------------------------------------------------------------ |
  | name | 从 procfs 的 root 起始的完整路径，比如 “/dir1/file2”<br />从 parent 起始的完整路径 |
  | mode | 权限配置                                                     |

- proc_create_data

  创建一个文件，并返回节点数据指针

  | 入参   | 说明                                                         |
  | ------ | ------------------------------------------------------------ |
  | name   | 从 procfs 的 root 起始的完整路径，比如 “/dir1/file2”<br />从 parent 起始的完整路径 |
  | mode   | 权限配置                                                     |
  | parent | 指定创建文件的起始节点                                       |
  | fops   | 文件操作接口配置                                             |
  | data   | 私有数据                                                     |

- proc_symlink

  创建一个符号链接，并返回节点数据指针

  | 入参   | 说明                                                         |
  | ------ | ------------------------------------------------------------ |
  | name   | 从 procfs 的 root 起始的完整路径，比如 “/dir1/file2”<br />从 parent 起始的完整路径 |
  | parent | 指定创建文件的起始节点                                       |
  | dest   | 链接的目标文件完整路径                                       |

- proc_acquire

  引用一个节点，并返回节点数据指针

  | 入参   | 说明           |
  | ------ | -------------- |
  | dentry | 需要引用的节点 |

- proc_release

  释放一个节点

  | 入参   | 说明           |
  | ------ | -------------- |
  | dentry | 需要释放的节点 |

- proc_remove

  删除一个节点包含子节点

  | 入参   | 说明           |
  | ------ | -------------- |
  | dentry | 需要删除的节点 |

## msh 调试命令

- proc_dump

  遍历打印指定节点含子节点的信息（名称、引用计数），比如 `proc_dump /dir1` 或者 `proc_dump`

- proc_remove

  删除指定节点含子节点，比如 `proc_remove /dir1` 或者 `proc_remove /file3`

- proc_symlink

  创建一个符号链接，`proc_symlink /link3 /mnt`

- proc_echo

  创建一个空文件，`proc_echo /file4`

- proc_mkdir

  创建一个空目录，`proc_mkdir /dir3`

- proc_pid

 创建一个 pid 目录，`proc_pid /101`
