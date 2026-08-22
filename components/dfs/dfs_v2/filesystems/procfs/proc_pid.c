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
#ifdef ARCH_MM_MMU
#include <stdint.h>
#include <mm_aspace.h>
#include <mm_flag.h>
#include <mmu.h>
#endif

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

#ifdef ARCH_MM_MMU
#define PROC_MAP_MAX 256

struct proc_map_entry
{
    uintptr_t start;
    uintptr_t end;
    uintptr_t offset;
    rt_size_t resident_pages;
    rt_bool_t writable;
    rt_bool_t shared;
    rt_bool_t executable;
    char name[DFS_PATH_MAX];
};

struct proc_map_context
{
    struct rt_lwp *lwp;
    struct proc_map_entry *entries;
    rt_size_t count;
    rt_bool_t smaps;
};

static void proc_map_permissions(rt_varea_t varea, struct proc_map_entry *entry)
{
    entry->writable = rt_hw_mmu_attr_test_perm(
        varea->attr, RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_USER);
    entry->shared = (varea->flag & MMF_MAP_SHARED) != 0;
    entry->executable = (varea->flag & MMF_TEXT) != 0;
}

static void proc_map_name(rt_varea_t varea, struct proc_map_entry *entry)
{
    const char *name = RT_NULL;

    if (varea->mem_obj && varea->mem_obj->get_name)
    {
        name = varea->mem_obj->get_name(varea);
    }

    if (!name || !name[0] || !rt_strcmp(name, "anonymous") ||
        !rt_strcmp(name, "reference") || !rt_strcmp(name, "null"))
    {
        name = "[anon]";
    }
    rt_strncpy(entry->name, name, sizeof(entry->name) - 1);
    entry->name[sizeof(entry->name) - 1] = '\0';
}

static int proc_map_collect(rt_varea_t varea, void *arg)
{
    struct proc_map_context *context = (struct proc_map_context *)arg;
    struct proc_map_entry *entry;
    uintptr_t address;
    uintptr_t end;

    if (context->count >= PROC_MAP_MAX || !varea || varea->size == 0)
    {
        return 0;
    }

    entry = &context->entries[context->count++];
    entry->start = (uintptr_t)varea->start;
    entry->end = entry->start + varea->size;
    entry->offset = (uintptr_t)varea->offset * ARCH_PAGE_SIZE;
    entry->resident_pages = 0;
    proc_map_permissions(varea, entry);
    proc_map_name(varea, entry);

    address = entry->start;
    end = entry->end;
    while (address < end)
    {
        if (rt_hw_mmu_v2p(varea->aspace, (void *)address) != ARCH_MAP_FAILED)
        {
            entry->resident_pages++;
        }
        address += ARCH_PAGE_SIZE;
    }

    return 0;
}

static void proc_map_context_free(struct proc_map_context *context)
{
    if (context)
    {
        if (context->lwp)
        {
            lwp_from_pid_release_lock(context->lwp);
        }
        if (context->entries)
        {
            rt_free(context->entries);
        }
        rt_free(context);
    }
}

static void *proc_maps_start(struct dfs_seq_file *seq, off_t *index)
{
    struct proc_map_context *context = (struct proc_map_context *)seq->data;

    return context && *index < (off_t)context->count ?
        &context->entries[*index] : RT_NULL;
}

static void *proc_maps_next(struct dfs_seq_file *seq, void *data, off_t *index)
{
    struct proc_map_context *context = (struct proc_map_context *)seq->data;

    RT_UNUSED(data);
    *index += 1;
    return context && *index < (off_t)context->count ?
        &context->entries[*index] : RT_NULL;
}

static void proc_maps_stop(struct dfs_seq_file *seq, void *data)
{
    RT_UNUSED(seq);
    RT_UNUSED(data);
}

static int proc_maps_show(struct dfs_seq_file *seq, void *data)
{
    struct proc_map_entry *entry = (struct proc_map_entry *)data;
    char permissions[5];

    permissions[0] = 'r';
    permissions[1] = entry->writable ? 'w' : '-';
    permissions[2] = entry->executable ? 'x' : '-';
    permissions[3] = entry->shared ? 's' : 'p';
    permissions[4] = '\0';

    dfs_seq_printf(seq, "%0*lx-%0*lx %s %0*lx 00:00 0",
                   (int)(sizeof(uintptr_t) * 2), (unsigned long)entry->start,
                   (int)(sizeof(uintptr_t) * 2), (unsigned long)entry->end,
                   permissions, (int)(sizeof(uintptr_t) * 2),
                   (unsigned long)entry->offset);
    if (entry->name[0])
    {
        dfs_seq_printf(seq, " %s", entry->name);
    }
    dfs_seq_puts(seq, "\n");

    if (((struct proc_map_context *)seq->data)->smaps)
    {
        rt_size_t resident_kb = entry->resident_pages * (ARCH_PAGE_SIZE / 1024);
        rt_size_t private_dirty = entry->writable && !entry->shared ? resident_kb : 0;

        dfs_seq_printf(seq, "Size: %lu kB\n", (unsigned long)((entry->end - entry->start) / 1024));
        dfs_seq_printf(seq, "Rss: %lu kB\n", (unsigned long)resident_kb);
        dfs_seq_printf(seq, "Pss: %lu kB\n", (unsigned long)resident_kb);
        dfs_seq_puts(seq, "Shared_Clean: 0 kB\n");
        dfs_seq_puts(seq, "Shared_Dirty: 0 kB\n");
        dfs_seq_puts(seq, "Private_Clean: 0 kB\n");
        dfs_seq_printf(seq, "Private_Dirty: %lu kB\n", (unsigned long)private_dirty);
        dfs_seq_printf(seq, "Anonymous: %lu kB\n", entry->name[0] == '[' ?
                       (unsigned long)resident_kb : 0UL);
        dfs_seq_puts(seq, "Swap: 0 kB\n\n");
    }

    return 0;
}

static const struct dfs_seq_ops proc_maps_seq_ops = {
    .start = proc_maps_start,
    .stop = proc_maps_stop,
    .next = proc_maps_next,
    .show = proc_maps_show,
};

static int proc_maps_open(struct dfs_file *file)
{
    struct proc_dentry *dentry = (struct proc_dentry *)file->vnode->data;
    struct proc_map_context *context;
    struct dfs_seq_file *seq;
    rt_varea_t varea;
    int ret;

    context = rt_calloc(1, sizeof(*context));
    if (!context)
    {
        return -RT_ENOMEM;
    }
    context->lwp = lwp_from_pid_and_lock(dentry->pid);
    if (!context->lwp || !context->lwp->aspace)
    {
        proc_map_context_free(context);
        return -RT_ENOENT;
    }
    context->smaps = !rt_strcmp(dentry->name, "smaps");
    context->entries = rt_calloc(PROC_MAP_MAX, sizeof(*context->entries));
    if (!context->entries)
    {
        proc_map_context_free(context);
        return -RT_ENOMEM;
    }

    RD_LOCK(context->lwp->aspace);
    varea = ASPACE_VAREA_FIRST(context->lwp->aspace);
    while (varea)
    {
        proc_map_collect(varea, context);
        varea = ASPACE_VAREA_NEXT(varea);
    }
    RD_UNLOCK(context->lwp->aspace);

    ret = dfs_seq_open(file, &proc_maps_seq_ops);
    if (ret != RT_EOK)
    {
        proc_map_context_free(context);
        return ret;
    }
    seq = (struct dfs_seq_file *)file->data;
    seq->data = context;
    return RT_EOK;
}

static int proc_maps_close(struct dfs_file *file)
{
    struct dfs_seq_file *seq = (struct dfs_seq_file *)file->data;
    struct proc_map_context *context = seq ? (struct proc_map_context *)seq->data : RT_NULL;
    int ret = dfs_seq_release(file);

    proc_map_context_free(context);
    file->data = RT_NULL;
    return ret;
}

static const struct dfs_file_ops proc_maps_fops = {
    .open = proc_maps_open,
    .read = dfs_seq_read,
    .lseek = dfs_seq_lseek,
    .close = proc_maps_close,
};
#endif /* ARCH_MM_MMU */

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

    lwp = lwp_from_pid_and_lock(dentry->pid);
    argv = lwp ? lwp_get_command_line_args(lwp) : RT_NULL;

    if (lwp)
    {
        dfs_seq_printf(seq,"%d ",dentry->pid);
        if (argv)
        {
            if (argv[0])
            {
                filename = strrchr(argv[0], '/');

                if (filename != NULL)
                {
                    filename++;
                }
                else
                {
                    filename = argv[0];
                }

                dot = strchr(filename, '.');
                if (dot != NULL)
                {
                    *dot = '\0';
                }

                dfs_seq_printf(seq,"(%s) ", filename);
            }
            else
            {
                dfs_seq_printf(seq,"(%s) ", "");
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
        if (lwp->parent != NULL)
            dfs_seq_printf(seq,"%d ",lwp->parent->pid);
        else
            dfs_seq_printf(seq,"0 ");

        dfs_seq_printf(seq, "1 1 0 -1 4194560 48245 133976064 732 425574 ");
        dfs_seq_printf(seq,"%llu ",user_time_lwp);//utime
        dfs_seq_printf(seq,"%llu ",system_time_lwp);//stime
        dfs_seq_printf(seq, "1204291 518742 20 0 1 0 50 ");
#ifdef ARCH_MM_MMU
        dfs_seq_printf(seq, "%lu ", lwp->aspace ?
                       (unsigned long)rt_aspace_count_vsz(lwp->aspace) : 0UL);//VSZ
#else
        dfs_seq_puts(seq, "0 ");
#endif
        dfs_seq_printf(seq, "1422 18446744073709551615 ");
        dfs_seq_printf(seq, "1 1 0 0 0 0 671173123 4096 1260 0 0 0 17 ");
        dfs_seq_printf(seq, "%d ", lwp_oncpu);//CPU
        dfs_seq_printf(seq, "0 0 0 0 0 0 0 0 0 0 0 0 0");
        dfs_seq_printf(seq,"\n");
        lwp_from_pid_release_lock(lwp);
    }

    return 0;
}

static int cmdline_single_show(struct dfs_seq_file *seq, void *data)
{
    struct proc_dentry *dentry = (struct proc_dentry *)seq->file->vnode->data;
    struct rt_lwp *lwp;
    char** argv;

    lwp = lwp_from_pid_and_lock(dentry->pid);
    argv = lwp ? lwp_get_command_line_args(lwp) : RT_NULL;

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
    lwp_from_pid_release_lock(lwp);

    return 0;
}

static int proc_pid_status_show(struct dfs_seq_file *seq, void *data)
{
    struct proc_dentry *dentry = (struct proc_dentry *)seq->file->vnode->data;
    struct rt_lwp *lwp = lwp_from_pid_and_lock(dentry->pid);
    rt_size_t vm_size = 0;
    rt_size_t thread_count = 0;
    rt_list_t *node;
    char state;

    RT_UNUSED(data);
    if (!lwp)
    {
        return -RT_ENOENT;
    }

#ifdef ARCH_MM_MMU
    if (lwp->aspace)
    {
        vm_size = rt_aspace_count_vsz(lwp->aspace);
    }
#endif
    node = lwp->t_grp.next;
    while (node != &lwp->t_grp)
    {
        thread_count++;
        node = node->next;
    }
    state = lwp->terminated ? 'Z' : 'S';
    dfs_seq_printf(seq, "Name:\t%s\n", lwp->cmd);
    dfs_seq_printf(seq, "State:\t%c (sleeping)\n", state);
    dfs_seq_printf(seq, "Pid:\t%d\n", lwp->pid);
    dfs_seq_printf(seq, "PPid:\t%d\n", lwp->parent ? lwp->parent->pid : 0);
    dfs_seq_puts(seq, "Uid:\t0\t0\t0\t0\nGid:\t0\t0\t0\t0\n");
    dfs_seq_printf(seq, "Threads:\t%lu\n", (unsigned long)thread_count);
    dfs_seq_printf(seq, "VmSize:\t%lu kB\n", (unsigned long)(vm_size / 1024));
    dfs_seq_printf(seq, "VmRSS:\t%lu kB\n", (unsigned long)(vm_size / 1024));
    dfs_seq_puts(seq, "VmData:\t0 kB\nVmStk:\t0 kB\nVmExe:\t0 kB\nVmLib:\t0 kB\n");
    lwp_from_pid_release_lock(lwp);
    return 0;
}

static int proc_pid_statm_show(struct dfs_seq_file *seq, void *data)
{
    struct proc_dentry *dentry = (struct proc_dentry *)seq->file->vnode->data;
    struct rt_lwp *lwp = lwp_from_pid_and_lock(dentry->pid);
    rt_size_t size_pages = 0;
    rt_size_t text_pages = 0;
    rt_size_t data_pages = 0;

    RT_UNUSED(data);
    if (!lwp)
    {
        return -RT_ENOENT;
    }

#ifdef ARCH_MM_MMU
    if (lwp->aspace)
    {
        size_pages = (rt_aspace_count_vsz(lwp->aspace) + ARCH_PAGE_SIZE - 1) / ARCH_PAGE_SIZE;
    }
#endif
#ifdef ARCH_MM_MMU
    text_pages = (lwp->text_size + ARCH_PAGE_SIZE - 1) / ARCH_PAGE_SIZE;
    data_pages = (lwp->data_size + ARCH_PAGE_SIZE - 1) / ARCH_PAGE_SIZE;
#endif
    dfs_seq_printf(seq, "%lu %lu 0 %lu 0 %lu 0\n",
                   (unsigned long)size_pages, (unsigned long)size_pages,
                   (unsigned long)text_pages, (unsigned long)data_pages);
    lwp_from_pid_release_lock(lwp);
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

    lwp = lwp_from_pid_and_lock(dentry->pid);
    len = rt_snprintf(buf, len, "%s", lwp && lwp->exe_file ? lwp->exe_file : "null");
    lwp_from_pid_release_lock(lwp);

    return len;
}

static const struct proc_ops proc_pid_exe_ops = {
    .readlink = proc_pid_exe_readlink,
};

int proc_pid_cwd_readlink(struct proc_dentry *dentry, char *buf, int len)
{
    struct rt_lwp *lwp;

    lwp = lwp_from_pid_and_lock(dentry->pid);
    len = rt_snprintf(buf, len, "%s", lwp ? lwp->working_directory : "null");
    lwp_from_pid_release_lock(lwp);

    return len;
}

static const struct proc_ops proc_pid_cwd_ops = {
    .readlink = proc_pid_cwd_readlink,
};

static struct pid_dentry pid_dentry_base[] = {
    {"cmdline", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, 0, 0, 0, cmdline_single_show, 0},
    {"status", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, 0, 0, 0, proc_pid_status_show, 0},
    {"statm", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, 0, 0, 0, proc_pid_statm_show, 0},
    {"cwd", S_IFLNK | S_IRUSR | S_IXUSR, 0, &proc_pid_cwd_ops, 0, 0},
    {"exe", S_IFLNK | S_IRUSR | S_IXUSR, 0, &proc_pid_exe_ops, 0, 0},
    {"fd", S_IFDIR | S_IRUSR | S_IXUSR, &proc_pid_fd_fops, &proc_pid_fd_ops, 0, 0, 0},
    {"mounts", S_IFLNK | S_IRUSR | S_IXUSR, 0, 0, 0, 0, "/proc/mounts"},
    {"stat", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, 0, 0, 0, stat_single_show, 0},
#ifdef ARCH_MM_MMU
    {"maps", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, &proc_maps_fops, 0, 0, 0, 0},
    {"smaps", S_IFREG | S_IRUSR | S_IRGRP | S_IROTH, &proc_maps_fops, 0, 0, 0, 0},
#endif
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
