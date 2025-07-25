/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "proc.h"
#include "procfs.h"

#include <rthw.h>
#include <rtdbg.h>

#include <fcntl.h>
#include <errno.h>

/*
 * This is the root in the proc tree..
 */
static struct proc_dentry _proc_root = {
    .mode       = S_IFDIR | (S_IRUSR | S_IRGRP | S_IROTH) | (S_IXUSR | S_IXGRP | S_IXOTH),
    .ref_count  = 1,

    .parent = &_proc_root,
    .node.sibling = RT_LIST_OBJECT_INIT(_proc_root.node.sibling),
    .node.subnode = RT_LIST_OBJECT_INIT(_proc_root.node.subnode),

    .fops = RT_NULL,

    .name = "/",
    .data = RT_NULL,
};

static int _proc_find(struct proc_dentry **parent, const char *name)
{
    struct proc_dentry *dentry = RT_NULL, *tmp;

    dfs_vfs_for_each_subnode(dentry, tmp, (*parent), node)
    {
        if (dentry == RT_NULL)
        {
            break;
        }

        if (rt_strcmp(dentry->name, name) == 0)
        {
            *parent = dentry;
            return 0;
        }
    }

    return -1;
}

static int proc_find(struct proc_dentry **parent, const char **name, rt_bool_t force_lookup)
{
    int ret = 0;
    char *tmp = RT_NULL;

    if (!(*parent))
    {
        *parent = &_proc_root;
    }

    tmp = rt_strdup(*name);
    if (tmp)
    {
        char *begin = tmp, *end = RT_NULL;
        if (*begin == '/')
        {
            begin++;
            if (*begin == '\0')
            {
                rt_free(tmp);
                *parent = proc_acquire(*parent);
                return ret;
            }
        }

        while (1)
        {
            end = rt_strstr(begin, "/");
            if (end)
            {
                *end = '\0';
                ret = _proc_find(parent, begin);
                if (ret < 0 || !S_ISDIR((*parent)->mode))
                {
                    *parent = RT_NULL;
                    ret = -1;
                    break;
                }
                begin = end + 1;
            }
            else if (force_lookup)
            {
                ret = _proc_find(parent, begin);
                if (ret < 0)
                {
                    if ((*parent)->ops && (*parent)->ops->lookup)
                    {
                        *parent = (*parent)->ops->lookup(*parent, begin);
                        if (*parent == RT_NULL)
                        {
                            ret = -1;
                        }
                    }
                    else
                    {
                        *parent = RT_NULL;
                    }
                }
                else
                {
                    *parent = proc_acquire(*parent);
                }
                break;
            }
            else
            {
                *parent = proc_acquire(*parent);
                break;
            }
        }

        *name = *name + (begin - tmp);

        rt_free(tmp);
    }

    return ret;
}

static void *single_start(struct dfs_seq_file *seq, off_t *index)
{
    return NULL + (*index == 0);
}

static void *single_next(struct dfs_seq_file *seq, void *data, off_t *index)
{
    ++*index;
    return NULL;
}

static void single_stop(struct dfs_seq_file *seq, void *data)
{
}

static int proc_open(struct dfs_file *file)
{
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (entry->single_show)
    {
        struct dfs_seq_ops *seq_ops = (struct dfs_seq_ops *)rt_calloc(1, sizeof(struct dfs_seq_ops));
        if (seq_ops)
        {
            int ret = 0;

            seq_ops->start = single_start;
            seq_ops->next = single_next;
            seq_ops->stop = single_stop;
            seq_ops->show = entry->single_show;

            ret = dfs_seq_open(file, seq_ops);
            if (ret != 0)
            {
                rt_free(seq_ops);
            }
            return ret;
        }
    }

    return dfs_seq_open(file, entry->seq_ops);
}

static int proc_close(struct dfs_file *file)
{
    struct dfs_seq_file *seq = file->data;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (seq && entry->single_show && seq->ops)
    {
        rt_free((void *)seq->ops);
        seq->ops = RT_NULL;
    }

    return dfs_seq_release(file);
}

static const struct dfs_file_ops proc_file_ops = {
    .open   = proc_open,
    .read   = dfs_seq_read,
    .lseek  = dfs_seq_lseek,
    .close  = proc_close,
};

static struct proc_dentry *proc_create(struct proc_dentry **parent, const char *name, mode_t mode)
{
    int ret = 0;
    struct proc_dentry *dentry = RT_NULL;

    ret = proc_find(parent, &name, 0);
    if (ret >= 0)
    {
        dentry = *parent;
        ret = proc_find(&dentry, &name, 1);
        if (ret < 0)
        {
            dentry = rt_calloc(1, sizeof(struct proc_dentry));
            if (dentry)
            {
                dentry->mode = mode;
                dentry->ref_count = 1;
                dentry->name = rt_strdup(name);
                dfs_vfs_init_node(&dentry->node);
            }
        }
        else
        {
            proc_release(dentry);
            dentry = RT_NULL;
        }
    }

    return dentry;
}

/**
 * @brief    The dentry reference count is incremented by one
 *
 * @param    dentry
 *
 * @return   dentry
 */
struct proc_dentry *proc_acquire(struct proc_dentry *dentry)
{
    if (dentry)
    {
        dentry->ref_count += 1;
    }

    return dentry;
}

/**
 * @brief    The dentry reference count is minus one, or release
 *
 * @param    dentry
 *
 * @return   none
 */
void proc_release(struct proc_dentry *dentry)
{
    if (dentry)
    {
        if (dentry->ref_count == 1)
        {
            if (dentry->name)
            {
                rt_free(dentry->name);
            }

            if (S_ISLNK(dentry->mode) && dentry->data)
            {
                rt_free(dentry->data);
            }

            rt_free(dentry);
        }
        else
        {
            dentry->ref_count -= 1;
        }
    }
}

static struct proc_dentry *proc_register(struct proc_dentry *parent, struct proc_dentry *child)
{
    child->parent = parent;
    dfs_vfs_append_node(&parent->node, &child->node);
    child->ref_count += 1;
    child->pid = parent->pid;

    return child;
}

/**
 * @brief    Make a dir
 *
 * @param    name fullpath based on _proc_root or parent
 * @param    mode permission configuration
 * @param    parent can be empty
 * @param    fops
 * @param    data
 *
 * @return   dentry
 */
struct proc_dentry *proc_mkdir_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                    const struct dfs_file_ops *fops, void *data)
{
    struct proc_dentry *dentry, *_parent = parent;

    if (mode == 0)
        mode = (S_IRUSR | S_IRGRP | S_IROTH) | (S_IXUSR | S_IXGRP | S_IXOTH);

    dentry = proc_create(&_parent, name, S_IFDIR | mode);
    if (dentry)
    {
        dentry->fops = fops;
        dentry->data = data;

        dentry = proc_register(_parent, dentry);
    }
    proc_release(_parent);

    return dentry;
}

/**
 * @brief    Make a dir
 *
 * @param    name fullpath based on _proc_root or parent
 * @param    mode permission configuration
 * @param    parent can be empty
 *
 * @return   dentry
 */
struct proc_dentry *proc_mkdir_mode(const char *name, mode_t mode, struct proc_dentry *parent)
{
    return proc_mkdir_data(name, mode, parent, NULL, NULL);
}

/**
 * @brief    Make a dir
 *
 * @param    name fullpath based on _proc_root or parent
 * @param    parent can be empty
 *
 * @return   dentry
 */
struct proc_dentry *proc_mkdir(const char *name, struct proc_dentry *parent)
{
    return proc_mkdir_data(name, 0, parent, NULL, NULL);
}

static struct proc_dentry *proc_create_reg(const char *name, mode_t mode, struct proc_dentry **parent)
{
    struct proc_dentry *dentry = RT_NULL;

    if ((mode & S_IFMT) == 0)
        mode |= S_IFREG;
    if ((mode & (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO)) == 0)
        mode |= S_IRUSR | S_IRGRP | S_IROTH;

    if (!S_ISREG(mode))
    {
        *parent = RT_NULL;
        return dentry;
    }

    return proc_create(parent, name, mode);
}

/**
 * @brief    Make a file
 *
 * @param    name fullpath based on _proc_root or parent
 * @param    mode permission configuration
 * @param    parent can be empty
 * @param    fops
 * @param    data
 *
 * @return   dentry
 */
struct proc_dentry *proc_create_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                     const struct dfs_file_ops *fops, void *data)
{
    struct proc_dentry *dentry, *_parent = parent;

    dentry = proc_create_reg(name, mode, &_parent);
    if (dentry)
    {
        dentry->fops = fops ? fops : &proc_file_ops;
        dentry->data = data;

        dentry = proc_register(_parent, dentry);
    }
    proc_release(_parent);

    return dentry;
}

/**
 * @brief    Make a file
 *
 * @param    name fullpath based on _proc_root or parent
 * @param    mode permission configuration
 * @param    parent can be empty
 * @param    show
 * @param    data
 *
 * @return   dentry
 */
struct proc_dentry *proc_create_single_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                            int (*show)(struct dfs_seq_file *, void *), void *data)
{
    struct proc_dentry *dentry, *_parent = parent;

    dentry = proc_create_reg(name, mode, &_parent);
    if (dentry)
    {
        dentry->fops = &proc_file_ops;
        dentry->single_show = show;
        dentry->data = data;

        dentry = proc_register(_parent, dentry);
    }
    proc_release(_parent);

    return dentry;
}

/**
 * @brief    Make a symlink
 *
 * @param    name fullpath based on _proc_root or parent
 * @param    parent can be empty
 * @param    dest  link file fullpath
 *
 * @return   dentry
 */
struct proc_dentry *proc_symlink(const char *name, struct proc_dentry *parent, const char *dest)
{
    struct proc_dentry *dentry, *_parent = parent;

    dentry = proc_create(&_parent, name, (S_IFLNK | (S_IRUSR | S_IRGRP | S_IROTH)
                         | (S_IWUSR | S_IWGRP | S_IWOTH) | (S_IXUSR | S_IXGRP | S_IXOTH)));
    if (dentry)
    {
        dentry->data = (void *)rt_strdup(dest);
        if (dentry->data)
        {
            dentry = proc_register(_parent, dentry);
        }
        else
        {
            proc_release(dentry);
            dentry = NULL;
        }
    }
    proc_release(_parent);

    return dentry;
}

static void remove_proc_subtree(struct proc_dentry *dentry)
{
    struct proc_dentry *iter = RT_NULL, *iter_tmp, *tmp = RT_NULL;

    dfs_vfs_for_each_subnode(iter, iter_tmp, dentry, node)
    {
        if (iter == RT_NULL)
        {
            break;
        }

        if (tmp)
        {
            proc_release(tmp);
            tmp = RT_NULL;
        }

        tmp = iter;

        if (S_ISDIR(dentry->mode))
        {
            remove_proc_subtree(iter);
        }
    }

    if (tmp)
    {
        proc_release(tmp);
        tmp = RT_NULL;
    }
}

/**
 * @brief    remove a dentry
 *
 * @param    dentry
 *
 * @return   none
 */
void proc_remove(struct proc_dentry *dentry)
{
    if (dentry && dentry != &_proc_root)
    {
        if (S_ISDIR(dentry->mode))
        {
            remove_proc_subtree(dentry);
        }

        dfs_vfs_remove_node(&dentry->node);
        proc_release(dentry);
    }
}

/**
 * @brief    find dentry exist
 *
 * @param    name fullpath based on _proc_root
 *
 * @return   dentry
 */
struct proc_dentry *dfs_proc_find(const char *name)
{
    struct proc_dentry *dentry = RT_NULL;

    proc_find(&dentry, &name, 1);

    return dentry;
}

/**
 * @brief    remove a dentry on parent
 *
 * @param    name fullpath based on parent
 * @param    parent
 *
 * @return   none
 */
void proc_remove_dentry(const char *name, struct proc_dentry *parent)
{
    struct proc_dentry *dentry = parent;

    if (proc_find(&dentry, &name, 1) >= 0)
    {
        proc_remove(dentry);
        proc_release(dentry);
    }
}

#define _COLOR_RED      "\033[31m"
#define _COLOR_GREEN    "\033[32m"
#define _COLOR_BLUE     "\033[34m"
#define _COLOR_CYAN     "\033[36m"
#define _COLOR_WHITE    "\033[37m"
#define _COLOR_NORMAL   "\033[0m"

static void dump_proc_subtree(struct proc_dentry *dentry, int tab)
{
    struct proc_dentry *iter = RT_NULL, *tmp;

    dfs_vfs_for_each_subnode(iter, tmp, dentry, node)
    {
        if (iter == RT_NULL)
        {
            break;
        }

        for(int i = 0; i < tab; i ++)
        {
            rt_kprintf("%-4s", i + 1 >= tab ? "|-" : " ");
        }

        if (S_ISDIR(iter->mode))
        {
            rt_kprintf(_COLOR_BLUE "%-20s" _COLOR_NORMAL " %d\n", iter->name, iter->ref_count);
            dump_proc_subtree(iter, tab + 1);
        }
        else if (S_ISLNK(iter->mode))
        {
            rt_kprintf(_COLOR_CYAN "%-20s" _COLOR_NORMAL " %d\n", iter->name, iter->ref_count);
        }
        else
        {
            rt_kprintf("%-20s %d\n", iter->name, iter->ref_count);
        }
    }
}

static void proc_dump(struct proc_dentry *dentry)
{
    if (dentry)
    {
        if (S_ISDIR(dentry->mode))
        {
            rt_kprintf(_COLOR_BLUE "%-20s" _COLOR_NORMAL " %d\n", dentry->name, dentry->ref_count);
            dump_proc_subtree(dentry, 1);
        }
        else if (S_ISLNK(dentry->mode))
        {
            rt_kprintf(_COLOR_CYAN "%-20s" _COLOR_NORMAL " %d\n", dentry->name, dentry->ref_count);
        }
        else
        {
            rt_kprintf("%-20s %d\n", dentry->name, dentry->ref_count);
        }
    }
}

static int msh_proc_dump(int argc, char** argv)
{
    const char *name = argc > 1 ? argv[1] : "/";
    struct proc_dentry *dentry = RT_NULL;

    int ret = proc_find(&dentry, &name, 1);
    if (ret >= 0)
    {
        proc_dump(dentry);
    }
    proc_release(dentry);

    return 0;
}
MSH_CMD_EXPORT_ALIAS(msh_proc_dump, proc_dump, proc dump);

static int msh_proc_remove(int argc, char** argv)
{
    if (argc > 1)
    {
        const char *name = argv[1];
        struct proc_dentry *dentry = RT_NULL;

        int ret = proc_find(&dentry, &name, 1);
        if (ret >= 0)
        {
            if (dentry != &_proc_root)
            {
                proc_remove(dentry);
            }
            else
            {
                struct proc_dentry *iter = RT_NULL, *iter_tmp, *tmp = RT_NULL;

                dfs_vfs_for_each_subnode(iter, iter_tmp, dentry, node)
                {
                    if (iter == RT_NULL)
                    {
                        break;
                    }

                    if (tmp)
                    {
                        proc_remove(tmp);
                    }

                    tmp = iter;
                }

                if (tmp)
                {
                    proc_remove(tmp);
                }
            }
        }
        proc_release(dentry);
    }
    else
    {
        rt_kprintf("proc_remove path\n");
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(msh_proc_remove, proc_remove, proc remove);

static int msh_proc_symlink(int argc, char** argv)
{
    if (argc > 2)
    {
        struct proc_dentry *entry = proc_symlink(argv[1], 0, argv[2]);
        if (entry)
        {
            proc_release(entry);
        }
    }
    else
    {
        rt_kprintf("proc_symlink path dest\n");
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(msh_proc_symlink, proc_symlink, proc symlink);

static int msh_proc_echo(int argc, char** argv)
{
    if (argc > 1)
    {
        for(int i = 1; i <= argc - 1; i ++)
        {
            struct proc_dentry *entry = proc_create_data(argv[i], 0, 0, 0, 0);
            if (entry)
            {
                proc_release(entry);
            }
        }
    }
    else
    {
        rt_kprintf("proc_echo path\n");
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(msh_proc_echo, proc_echo, proc echo);

static int msh_proc_mkdir(int argc, char** argv)
{
    if (argc > 1)
    {
        for(int i = 1; i <= argc - 1; i ++)
        {
            struct proc_dentry *entry = proc_mkdir(argv[i], 0);
            if (entry)
            {
                proc_release(entry);
            }
        }
    }
    else
    {
        rt_kprintf("proc_mkdir path\n");
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(msh_proc_mkdir, proc_mkdir, proc mkdir);
