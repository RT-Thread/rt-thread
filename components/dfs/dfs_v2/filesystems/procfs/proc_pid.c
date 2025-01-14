/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#define __RT_IPC_SOURCE__

#include "proc.h"
#include "procfs.h"

#include <rthw.h>
#include <rtdbg.h>

#include <fcntl.h>
#include <errno.h>

#include "lwp_internal.h"
#include <dfs_dentry.h>
#include "lwp_internal.h"

#if defined(RT_USING_SMART)

#include "lwp.h"
#include "lwp_pid.h"
#include <lwp_user_mm.h>

struct pid_dentry
{
    const char *name;
    mode_t mode;
    const struct dfs_file_ops *fops;
    const struct proc_ops *ops;
    const struct dfs_seq_ops *seq_ops;
    int (*single_show)(struct dfs_seq_file *seq, void *data);
    void *data;
};

static char stat_transform(int __stat)
{
    switch (__stat)
    {
    case RT_THREAD_RUNNING:
        return 'R';
    default:
        return 'T';
    }
}

static int stat_single_show(struct dfs_seq_file *seq, void *data)
{
    struct proc_dentry *dentry = (struct proc_dentry *)seq->file->vnode->data;
    rt_list_t *list;
    int mask = 0;
    rt_thread_t thread;
    rt_uint64_t user_time_lwp = 0;
    rt_uint64_t system_time_lwp = 0;
    int lwp_oncpu = RT_CPUS_NR;
    int lwp_oncpu_ok = 0;
    struct rt_lwp *lwp = RT_NULL;
    char** argv = RT_NULL;
    char *filename = RT_NULL;
    char *dot = RT_NULL;

    lwp_pid_lock_take();

    lwp = lwp_from_pid_locked(dentry->pid);
    argv = lwp_get_command_line_args(lwp);

    if (lwp)
    {
        dfs_seq_printf(seq,"%d ",dentry->pid);
        if (argv)
        {
            filename = strrchr(argv[0], '/');
            dot = strchr(argv[0], '.');

            if (filename != NULL)
            {
                filename++;
            }
            else
            {
                filename = argv[0];
            }

            if (dot != NULL)
            {
                *dot = '\0';
            }

            if (filename != NULL)
            {
                dfs_seq_printf(seq,"(%s) ", filename);
            }
            else
            {
                dfs_seq_printf(seq,"(%s) ", argv[0]);
            }

            lwp_free_command_line_args(argv);
        }
        else
        {
            dfs_seq_printf(seq,"(%s) ", "");
        }

        if (lwp->terminated)
        {
            dfs_seq_printf(seq,"%c ",'Z');
        }
        else
        {
            list = lwp->t_grp.next;
            while (list != &lwp->t_grp)
            {
                thread = rt_list_entry(list, struct rt_thread, sibling);
                user_time_lwp = user_time_lwp + thread->user_time;
                system_time_lwp = system_time_lwp + thread->system_time;

                #if RT_CPUS_NR > 1
                    #define ONCPU(thread) RT_SCHED_CTX(thread).oncpu
                #else
                    #define ONCPU(thread) 0
                #endif
                if (lwp_oncpu_ok == 0)
                {
                    lwp_oncpu = ONCPU(thread);
                    lwp_oncpu_ok = 1;
                }
                if (stat_transform(RT_SCHED_CTX(thread).stat) == 'R')
                {
                    lwp_oncpu = ONCPU(thread);
                    mask = 1;
                }
                list = list->next;
            }

            if (mask == 1)
            {
                dfs_seq_printf(seq,"%c ",'R');
            }
            else
            {
                dfs_seq_printf(seq,"%c ",'S');
            }
        }
        lwp_pid_lock_release();

        if (lwp->parent != NULL)
            dfs_seq_printf(seq,"%d ",lwp->parent->pid);
        else
            dfs_seq_printf(seq,"0 ");

        dfs_seq_printf(seq, "1 1 0 -1 4194560 48245 133976064 732 425574 ");
        dfs_seq_printf(seq,"%llu ",user_time_lwp);//utime
        dfs_seq_printf(seq,"%llu ",system_time_lwp);//stime
        dfs_seq_printf(seq, "1204291 518742 20 0 1 0 50 ");
        dfs_seq_printf(seq, "%d ",rt_aspace_count_vsz(lwp->aspace));//VSZ
        dfs_seq_printf(seq, "1422 18446744073709551615 ");
        dfs_seq_printf(seq, "1 1 0 0 0 0 671173123 4096 1260 0 0 0 17 ");
        dfs_seq_printf(seq, "%d ", lwp_oncpu);//CPU
        dfs_seq_printf(seq, "0 0 0 0 0 0 0 0 0 0 0 0 0");
        dfs_seq_printf(seq,"\n");
    }
    else
    {
        lwp_pid_lock_release();
    }

    return 0;
}

static int cmdline_single_show(struct dfs_seq_file *seq, void *data)
{
    struct proc_dentry *dentry = (struct proc_dentry *)seq->file->vnode->data;
    struct rt_lwp *lwp;
    char** argv;

    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(dentry->pid);
    argv = lwp_get_command_line_args(lwp);
    lwp_pid_lock_release();

    if (argv)
    {
        for (int i = 0; argv[i] != NULL; i++)
        {
            dfs_seq_printf(seq, "%s ", argv[i]);
        }
        dfs_seq_puts(seq, "\n");

        lwp_free_command_line_args(argv);
    }
    else
    {
        dfs_seq_puts(seq, "error\n");
    }

    return 0;
}

struct proc_dentry *proc_pid_fd_lookup(struct proc_dentry *parent, const char *name)
{
    struct proc_dentry *dentry = RT_NULL;
    char num[DIRENT_NAME_MAX];
    struct rt_lwp *lwp;
    struct dfs_fdtable *table;

    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(parent->pid);
    table = lwp ? &lwp->fdt : RT_NULL;
    lwp_pid_lock_release();

    if (!table)
    {
        return RT_NULL;
    }

    dfs_file_lock();
    for (int i = 0; i < table->maxfd; i++)
    {
        struct dfs_file *file = table->fds[i];
        if (file)
        {
            rt_snprintf(num, DIRENT_NAME_MAX, "%d", i);
            if (rt_strcmp(num, name) == 0)
            {
                dentry = rt_calloc(1, sizeof(struct proc_dentry));
                if (dentry)
                {
                    dentry->mode = (S_IFLNK | (S_IRUSR | S_IRGRP | S_IROTH) | (S_IWUSR | S_IWGRP | S_IWOTH) | (S_IXUSR | S_IXGRP | S_IXOTH));
                    dentry->ref_count = 1;
                    dentry->name = rt_strdup(name);
                    dentry->data = (void *)dfs_dentry_full_path(file->dentry);

                    if (dentry->data == RT_NULL)
                    {
                        //todo add vnode->data
                        if (file->vnode->type == FT_SOCKET)
                            dentry->data = (void *)rt_strdup("socket");
                        else if (file->vnode->type == FT_USER)
                            dentry->data = (void *)rt_strdup("user");
                        else if (file->vnode->type == FT_DEVICE)
                            dentry->data = (void *)rt_strdup("device");
                        else
                            dentry->data = (void *)rt_strdup("unknown");
                    }

                    dentry->pid = parent->pid;
                    break;
                }
            }
        }
    }
    dfs_file_unlock();

    return dentry;
}

int proc_pid_fd_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    int ret = 0, index = 0;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;
    struct rt_lwp *lwp;
    struct dfs_fdtable *table;

    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(entry->pid);
    LWP_LOCK(lwp);
    table = lwp ? &lwp->fdt : RT_NULL;

    if (!table->fds)
    {
        LWP_UNLOCK(lwp);
        lwp_pid_lock_release();
        return 0;
    }

    count = (count / sizeof(struct dirent));
    if (count == 0)
    {
        LWP_UNLOCK(lwp);
        lwp_pid_lock_release();
        return -EINVAL;
    }

    dfs_file_lock();
    for (int i = 0; i < table->maxfd; i++)
    {
        struct dfs_file *df = table->fds[i];
        if (df)
        {
            if (index >= file->fpos)
            {
                struct dirent *d = dirp + index - file->fpos;

                d->d_type = DT_SYMLINK;
                d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
                rt_snprintf(d->d_name, DIRENT_NAME_MAX, "%d", i);
                d->d_namlen = rt_strlen(d->d_name);

                ret++;
            }

            index++;
            if (index - file->fpos >= count)
            {
                break;
            }
        }
    }
    dfs_file_unlock();
    LWP_UNLOCK(lwp);
    lwp_pid_lock_release();

    if (ret > 0)
    {
        file->fpos = index;
        ret = ret * sizeof(struct dirent);
    }

    return ret;
}

static const struct proc_ops proc_pid_fd_ops = {
    .lookup = proc_pid_fd_lookup,
};

static const struct dfs_file_ops proc_pid_fd_fops = {
    .getdents = proc_pid_fd_getdents,
};

int proc_pid_exe_readlink(struct proc_dentry *dentry, char *buf, int len)
{
    struct rt_lwp *lwp;

    lwp = lwp_self();
    len = rt_snprintf(buf, len, "%s", lwp ? lwp->exe_file : "null");

    return len;
}

static const struct proc_ops proc_pid_exe_ops = {
    .readlink = proc_pid_exe_readlink,
};

int proc_pid_cwd_readlink(struct proc_dentry *dentry, char *buf, int len)
{
    struct rt_lwp *lwp;

    lwp = lwp_self();
    len = rt_snprintf(buf, len, "%s", lwp ? lwp->working_directory : "null");

    return len;
}

static const struct proc_ops proc_pid_cwd_ops = {
    .readlink = proc_pid_cwd_readlink,
};

static struct pid_dentry pid_dentry_base[] = {
    {"cmdline", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, 0, 0, 0, cmdline_single_show, 0},
    {"cwd", S_IFLNK | S_IRUSR | S_IXUSR, 0, &proc_pid_cwd_ops, 0, 0},
    {"exe", S_IFLNK | S_IRUSR | S_IXUSR, 0, &proc_pid_exe_ops, 0, 0},
    {"fd", S_IFDIR | S_IRUSR | S_IXUSR, &proc_pid_fd_fops, &proc_pid_fd_ops, 0, 0, 0},
    {"mounts", S_IFLNK | S_IRUSR | S_IXUSR, 0, 0, 0, 0, "/proc/mounts"},
    {"stat", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, 0, 0, 0, stat_single_show, 0},
};

int proc_pid(int pid)
{
    char pid_str[64] = {0};
    struct proc_dentry *dentry;

    rt_snprintf(pid_str, 64, "%d", pid);
    pid_str[63] = 0;

    dentry = proc_mkdir(pid_str, 0);
    if (dentry)
    {
        struct proc_dentry *ent;

        dentry->pid = pid;
        for (int j = 0; j < sizeof(pid_dentry_base) / sizeof(struct pid_dentry); j++)
        {
            if (S_ISDIR(pid_dentry_base[j].mode))
            {
                ent = proc_mkdir_data(pid_dentry_base[j].name, pid_dentry_base[j].mode, dentry,
                                      pid_dentry_base[j].fops, pid_dentry_base[j].data);
            }
            else if (S_ISLNK(pid_dentry_base[j].mode))
            {
                if (pid_dentry_base[j].data == RT_NULL)
                {
                    pid_dentry_base[j].data = "NULL";
                }

                ent = proc_symlink(pid_dentry_base[j].name, dentry, pid_dentry_base[j].data);
            }
            else
            {
                ent = proc_create_data(pid_dentry_base[j].name, pid_dentry_base[j].mode, dentry,
                                       pid_dentry_base[j].fops, pid_dentry_base[j].data);
            }

            if (ent)
            {
                if (pid_dentry_base[j].ops)
                {
                    ent->ops = pid_dentry_base[j].ops;
                }

                if (pid_dentry_base[j].seq_ops)
                {
                    ent->seq_ops = pid_dentry_base[j].seq_ops;
                }

                if (pid_dentry_base[j].single_show)
                {
                    ent->single_show = pid_dentry_base[j].single_show;
                }

                proc_release(ent);
            }
        }
        proc_release(dentry);
    }

    return 0;
}

int msh_proc_pid(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i <= argc - 1; i++)
        {
            proc_pid(atoi(argv[i]));
        }
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(msh_proc_pid, proc_pid, proc pid);

#endif
