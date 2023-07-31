/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-16     zhangjun     first version
 * 2021-02-20     lizhirui     fix warning
 * 2023-06-26     shell        clear ref to parent on waitpid()
 *                             Remove recycling of lwp on waitpid() and leave it to defunct routine
 */

#include <rthw.h>
#include <rtthread.h>

#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */

#include "lwp.h"
#include "lwp_pid.h"
#include "lwp_signal.h"
#include "tty.h"

#ifdef ARCH_MM_MMU
#include "lwp_user_mm.h"
#endif

#define DBG_TAG    "LWP_PID"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define PID_MAX 10000

#define PID_CT_ASSERT(name, x) \
    struct assert_##name {char ary[2 * (x) - 1];}

PID_CT_ASSERT(pid_min_nr, RT_LWP_MAX_NR > 1);
PID_CT_ASSERT(pid_max_nr, RT_LWP_MAX_NR < PID_MAX);

static struct lwp_avl_struct lwp_pid_ary[RT_LWP_MAX_NR];
static struct lwp_avl_struct *lwp_pid_free_head = RT_NULL;
static int lwp_pid_ary_alloced = 0;
static struct lwp_avl_struct *lwp_pid_root = RT_NULL;
static pid_t current_pid = 0;

struct lwp_avl_struct *lwp_get_pid_ary(void)
{
    return lwp_pid_ary;
}

static pid_t lwp_pid_get(void)
{
    rt_base_t level;
    struct lwp_avl_struct *p;
    pid_t pid = 0;

    level = rt_hw_interrupt_disable();
    p = lwp_pid_free_head;
    if (p)
    {
        lwp_pid_free_head = (struct lwp_avl_struct *)p->avl_right;
    }
    else if (lwp_pid_ary_alloced < RT_LWP_MAX_NR)
    {
        p = lwp_pid_ary + lwp_pid_ary_alloced;
        lwp_pid_ary_alloced++;
    }
    if (p)
    {
        int found_noused = 0;

        RT_ASSERT(p->data == RT_NULL);
        for (pid = current_pid + 1; pid < PID_MAX; pid++)
        {
            if (!lwp_avl_find(pid, lwp_pid_root))
            {
                found_noused = 1;
                break;
            }
        }
        if (!found_noused)
        {
            for (pid = 1; pid <= current_pid; pid++)
            {
                if (!lwp_avl_find(pid, lwp_pid_root))
                {
                    found_noused = 1;
                    break;
                }
            }
        }
        p->avl_key = pid;
        lwp_avl_insert(p, &lwp_pid_root);
        current_pid = pid;
    }
    rt_hw_interrupt_enable(level);
    return pid;
}

static void lwp_pid_put(pid_t pid)
{
    rt_base_t level;
    struct lwp_avl_struct *p;

    level = rt_hw_interrupt_disable();
    p  = lwp_avl_find(pid, lwp_pid_root);
    if (p)
    {
        p->data = RT_NULL;
        lwp_avl_remove(p, &lwp_pid_root);
        p->avl_right = lwp_pid_free_head;
        lwp_pid_free_head = p;
    }
    rt_hw_interrupt_enable(level);
}

static void lwp_pid_set_lwp(pid_t pid, struct rt_lwp *lwp)
{
    rt_base_t level;
    struct lwp_avl_struct *p;

    level = rt_hw_interrupt_disable();
    p  = lwp_avl_find(pid, lwp_pid_root);
    if (p)
    {
        p->data = lwp;
    }
    rt_hw_interrupt_enable(level);
}

static void __exit_files(struct rt_lwp *lwp)
{
    int fd = lwp->fdt.maxfd - 1;

    while (fd >= 0)
    {
        struct dfs_file *d;

        d = lwp->fdt.fds[fd];
        if (d)
        {
            dfs_file_close(d);
            fdt_fd_release(&lwp->fdt, fd);
        }
        fd--;
    }
}

void lwp_user_object_lock_init(struct rt_lwp *lwp)
{
    rt_mutex_init(&lwp->object_mutex, "lwp_obj", RT_IPC_FLAG_PRIO);
}

void lwp_user_object_lock_destroy(struct rt_lwp *lwp)
{
    rt_mutex_detach(&lwp->object_mutex);
}

void lwp_user_object_lock(struct rt_lwp *lwp)
{
    if (lwp)
    {
        rt_mutex_take(&lwp->object_mutex, RT_WAITING_FOREVER);
    }
    else
    {
        RT_ASSERT(0);
    }
}

void lwp_user_object_unlock(struct rt_lwp *lwp)
{
    if (lwp)
    {
        rt_mutex_release(&lwp->object_mutex);
    }
    else
    {
        RT_ASSERT(0);
    }
}

int lwp_user_object_add(struct rt_lwp *lwp, rt_object_t object)
{
    int ret = -1;

    if (lwp && object)
    {
        lwp_user_object_lock(lwp);
        if (!lwp_avl_find((avl_key_t)object, lwp->object_root))
        {
            struct lwp_avl_struct *node;

            node = (struct lwp_avl_struct *)rt_malloc(sizeof(struct lwp_avl_struct));
            if (node)
            {
                rt_base_t level;

                level = rt_hw_interrupt_disable();
                object->lwp_ref_count++;
                rt_hw_interrupt_enable(level);
                node->avl_key = (avl_key_t)object;
                lwp_avl_insert(node, &lwp->object_root);
                ret = 0;
            }
        }
        lwp_user_object_unlock(lwp);
    }
    return ret;
}

static rt_err_t _object_node_delete(struct rt_lwp *lwp, struct lwp_avl_struct *node)
{
    rt_err_t ret = -1;
    rt_object_t object;

    if (!lwp || !node)
    {
        return ret;
    }
    object = (rt_object_t)node->avl_key;
    object->lwp_ref_count--;
    if (object->lwp_ref_count == 0)
    {
        /* remove from kernel object list */
        switch (object->type)
        {
        case RT_Object_Class_Semaphore:
            ret = rt_sem_delete((rt_sem_t)object);
            break;
        case RT_Object_Class_Mutex:
            ret = rt_mutex_delete((rt_mutex_t)object);
            break;
        case RT_Object_Class_Event:
            ret = rt_event_delete((rt_event_t)object);
            break;
        case RT_Object_Class_MailBox:
            ret = rt_mb_delete((rt_mailbox_t)object);
            break;
        case RT_Object_Class_MessageQueue:
            ret = rt_mq_delete((rt_mq_t)object);
            break;
        case RT_Object_Class_Timer:
            ret = rt_timer_delete((rt_timer_t)object);
            break;
        case RT_Object_Class_Custom:
            ret = rt_custom_object_destroy(object);
            break;
        default:
            LOG_E("input object type(%d) error", object->type);
            break;
        }
    }
    else
    {
        ret = 0;
    }
    lwp_avl_remove(node, &lwp->object_root);
    rt_free(node);
    return ret;
}

rt_err_t lwp_user_object_delete(struct rt_lwp *lwp, rt_object_t object)
{
    rt_err_t ret = -1;

    if (lwp && object)
    {
        struct lwp_avl_struct *node;

        lwp_user_object_lock(lwp);
        node = lwp_avl_find((avl_key_t)object, lwp->object_root);
        ret = _object_node_delete(lwp, node);
        lwp_user_object_unlock(lwp);
    }
    return ret;
}

void lwp_user_object_clear(struct rt_lwp *lwp)
{
    struct lwp_avl_struct *node;

    lwp_user_object_lock(lwp);
    while ((node = lwp_map_find_first(lwp->object_root)) != RT_NULL)
    {
        _object_node_delete(lwp, node);
    }
    lwp_user_object_unlock(lwp);
}

static int _object_dup(struct lwp_avl_struct *node, void *arg)
{
    rt_object_t object;
    struct rt_lwp *dst_lwp = (struct rt_lwp *)arg;

    object = (rt_object_t)node->avl_key;
    lwp_user_object_add(dst_lwp, object);
    return 0;
}

void lwp_user_object_dup(struct rt_lwp *dst_lwp, struct rt_lwp *src_lwp)
{
    lwp_user_object_lock(src_lwp);
    lwp_avl_traversal(src_lwp->object_root, _object_dup, dst_lwp);
    lwp_user_object_unlock(src_lwp);
}

struct rt_lwp* lwp_new(void)
{
    pid_t pid;
    rt_base_t level;
    struct rt_lwp* lwp = RT_NULL;

    lwp = (struct rt_lwp *)rt_malloc(sizeof(struct rt_lwp));
    if (lwp == RT_NULL)
    {
        return lwp;
    }
    memset(lwp, 0, sizeof(*lwp));
    //lwp->tgroup_leader = RT_NULL;
    rt_list_init(&lwp->wait_list);
    lwp->leader = 0;
    lwp->session = -1;
    lwp->tty = RT_NULL;
    rt_list_init(&lwp->t_grp);
    rt_list_init(&lwp->timer);
    lwp_user_object_lock_init(lwp);
    lwp->address_search_head = RT_NULL;
    rt_wqueue_init(&lwp->wait_queue);
    lwp->ref = 1;

    lwp_signal_init(&lwp->signal);

    level = rt_hw_interrupt_disable();
    pid = lwp_pid_get();
    if (pid == 0)
    {
        lwp_user_object_lock_destroy(lwp);
        rt_free(lwp);
        lwp = RT_NULL;
        LOG_E("pid slot fulled!\n");
        goto out;
    }
    lwp->pid = pid;
    lwp_pid_set_lwp(pid, lwp);

#ifdef LWP_ENABLE_ASID
    lwp->generation = 0;
    lwp->asid = 0;
#endif

out:
    rt_hw_interrupt_enable(level);
    return lwp;
}

void lwp_free(struct rt_lwp* lwp)
{
    rt_base_t level;

    if (lwp == RT_NULL)
    {
        return;
    }

    LOG_D("lwp free: %p\n", lwp);

    level = rt_hw_interrupt_disable();
    lwp->finish = 1;
    rt_hw_interrupt_enable(level);

    if (lwp->args != RT_NULL)
    {
#ifndef ARCH_MM_MMU
        lwp->args_length = RT_NULL;
#ifndef ARCH_MM_MPU
        rt_free(lwp->args);
#endif /* not defined ARCH_MM_MPU */
#endif /* ARCH_MM_MMU */
        lwp->args = RT_NULL;
    }

    if (lwp->fdt.fds != RT_NULL)
    {
        /* auto clean fds */
        __exit_files(lwp);
        rt_free(lwp->fdt.fds);
        lwp->fdt.fds = RT_NULL;
    }

    lwp_user_object_clear(lwp);
    lwp_user_object_lock_destroy(lwp);

    /* free data section */
    if (lwp->data_entry != RT_NULL)
    {
#ifdef ARCH_MM_MMU
        rt_free_align(lwp->data_entry);
#else
#ifdef ARCH_MM_MPU
        rt_lwp_umap_user(lwp, lwp->text_entry, 0);
        rt_lwp_free_user(lwp, lwp->data_entry, lwp->data_size);
#else
        rt_free_align(lwp->data_entry);
#endif /* ARCH_MM_MPU */
#endif /* ARCH_MM_MMU */
        lwp->data_entry = RT_NULL;
    }

    /* free text section */
    if (lwp->lwp_type == LWP_TYPE_DYN_ADDR)
    {
        if (lwp->text_entry)
        {
            LOG_D("lwp text free: %p", lwp->text_entry);
#ifndef ARCH_MM_MMU
            rt_free((void*)lwp->text_entry);
#endif /* not defined ARCH_MM_MMU */
            lwp->text_entry = RT_NULL;
        }
    }

#ifdef ARCH_MM_MMU
    lwp_unmap_user_space(lwp);
#endif

    level = rt_hw_interrupt_disable();
    /* for children */
    while (lwp->first_child)
    {
        struct rt_lwp *child;

        child = lwp->first_child;
        lwp->first_child = child->sibling;
        if (child->finish)
        {
            lwp_pid_put(lwp_to_pid(child));
            rt_hw_interrupt_enable(level);
            rt_free(child);
            level = rt_hw_interrupt_disable();
        }
        else
        {
            child->sibling = RT_NULL;
            child->parent = RT_NULL;
        }
    }

    rt_hw_interrupt_enable(level);
    if (!lwp->background)
    {
        struct termios *old_stdin_termios = get_old_termios();
        struct rt_lwp *old_lwp = NULL;

        if (lwp->session == -1)
        {
            tcsetattr(1, 0, old_stdin_termios);
        }
        level = rt_hw_interrupt_disable();
        if (lwp->tty != RT_NULL)
        {
            rt_mutex_take(&lwp->tty->lock, RT_WAITING_FOREVER);
            old_lwp = tty_pop(&lwp->tty->head, RT_NULL);
            rt_mutex_release(&lwp->tty->lock);
            if (lwp->tty->foreground == lwp)
            {
                lwp->tty->foreground = old_lwp;
                lwp->tty = RT_NULL;
            }
        }
    }
    else
    {
        level = rt_hw_interrupt_disable();
    }

    /* for parent */
    if (lwp->parent)
    {
        struct rt_thread *thread;
        if (!rt_list_isempty(&lwp->wait_list))
        {
            thread = rt_list_entry(lwp->wait_list.next, struct rt_thread, tlist);
            thread->error = RT_EOK;
            thread->msg_ret = (void*)(rt_size_t)lwp->lwp_ret;
            rt_thread_resume(thread);
            rt_hw_interrupt_enable(level);
            return;
        }
        else
        {
            struct rt_lwp **it = &lwp->parent->first_child;

            while (*it != lwp)
            {
                it = &(*it)->sibling;
            }
            *it = lwp->sibling;
        }
    }

    timer_list_free(&lwp->timer);
    lwp_pid_put(lwp_to_pid(lwp));
    rt_hw_interrupt_enable(level);
    rt_free(lwp);
}

int lwp_ref_inc(struct rt_lwp *lwp)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    lwp->ref++;
    rt_hw_interrupt_enable(level);

    return 0;
}

int lwp_ref_dec(struct rt_lwp *lwp)
{
    rt_base_t level;
    int ref = -1;

    level = rt_hw_interrupt_disable();
    if (lwp->ref)
    {
        lwp->ref--;
        ref = lwp->ref;
    }
    rt_hw_interrupt_enable(level);
    if (!ref)
    {
        struct rt_channel_msg msg;

        if (lwp->debug)
        {
            memset(&msg, 0, sizeof msg);
            rt_raw_channel_send(gdb_server_channel(), &msg);
        }
        lwp_signal_detach(&lwp->signal);

#ifndef ARCH_MM_MMU
#ifdef RT_LWP_USING_SHM
        lwp_shm_lwp_free(lwp);
#endif /* RT_LWP_USING_SHM */
#endif /* not defined ARCH_MM_MMU */
        lwp_free(lwp);

        return 0;
    }

    return -1;
}

struct rt_lwp* lwp_from_pid(pid_t pid)
{
    rt_base_t level;
    struct lwp_avl_struct *p;
    struct rt_lwp *lwp = RT_NULL;

    level = rt_hw_interrupt_disable();
    p  = lwp_avl_find(pid, lwp_pid_root);
    if (p)
    {
        lwp = (struct rt_lwp *)p->data;
    }
    rt_hw_interrupt_enable(level);
    return lwp;
}

pid_t lwp_to_pid(struct rt_lwp* lwp)
{
    if (!lwp)
    {
        return 0;
    }
    return lwp->pid;
}

char* lwp_pid2name(int32_t pid)
{
    struct rt_lwp *lwp;
    char* process_name = RT_NULL;

    lwp = lwp_from_pid(pid);
    if (lwp)
    {
        process_name = strrchr(lwp->cmd, '/');
        process_name = process_name? process_name + 1: lwp->cmd;
    }
    return process_name;
}

pid_t lwp_name2pid(const char *name)
{
    int idx;
    pid_t pid = 0;
    rt_thread_t main_thread;
    char* process_name = RT_NULL;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    for (idx = 0; idx < RT_LWP_MAX_NR; idx++)
    {
        /* 0 is reserved */
        struct rt_lwp *lwp = (struct rt_lwp *)lwp_pid_ary[idx].data;

        if (lwp)
        {
            process_name = strrchr(lwp->cmd, '/');
            process_name = process_name? process_name + 1: lwp->cmd;
            if (!rt_strncmp(name, process_name, RT_NAME_MAX))
            {
                main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
                if (!(main_thread->stat & RT_THREAD_CLOSE))
                {
                    pid = lwp->pid;
                }
            }
        }
    }
    rt_hw_interrupt_enable(level);
    return pid;
}

int lwp_getpid(void)
{
    return ((struct rt_lwp *)rt_thread_self()->lwp)->pid;
}

pid_t waitpid(pid_t pid, int *status, int options)
{
    pid_t ret = -1;
    rt_base_t level;
    struct rt_thread *thread;
    struct rt_lwp *lwp;
    struct rt_lwp *lwp_self;

    level = rt_hw_interrupt_disable();
    lwp = lwp_from_pid(pid);
    if (!lwp)
    {
        goto quit;
    }

    lwp_self = (struct rt_lwp *)rt_thread_self()->lwp;
    if (!lwp_self)
    {
        goto quit;
    }
    if (lwp->parent != lwp_self)
    {
        goto quit;
    }

    if (lwp->finish)
    {
        ret = pid;
    }
    else
    {
        if (!rt_list_isempty(&lwp->wait_list))
        {
            goto quit;
        }
        thread = rt_thread_self();
        rt_thread_suspend_with_flag(thread, RT_UNINTERRUPTIBLE);
        rt_list_insert_before(&lwp->wait_list, &(thread->tlist));
        rt_schedule();
        if (thread->error == RT_EOK)
        {
            ret = pid;
        }
    }

    if (ret != -1)
    {
        /* delete from sibling list of its parent */
        struct rt_lwp **lwp_node;

        *status = lwp->lwp_ret;
        lwp_node = &lwp_self->first_child;
        while (*lwp_node != lwp)
        {
            RT_ASSERT(*lwp_node != RT_NULL);
            lwp_node = &(*lwp_node)->sibling;
        }
        (*lwp_node) = lwp->sibling;
        lwp->parent = RT_NULL;
    }

quit:
    rt_hw_interrupt_enable(level);
    return ret;
}

#ifdef RT_USING_FINSH
/* copy from components/finsh/cmd.c */
static void object_split(int len)
{
    while (len--)
    {
        rt_kprintf("-");
    }
}

static void print_thread_info(struct rt_thread* thread, int maxlen)
{
    rt_uint8_t *ptr;
    rt_uint8_t stat;

#ifdef RT_USING_SMP
    if (thread->oncpu != RT_CPU_DETACHED)
        rt_kprintf("%-*.*s %3d %3d ", maxlen, RT_NAME_MAX, thread->parent.name, thread->oncpu, thread->current_priority);
    else
        rt_kprintf("%-*.*s N/A %3d ", maxlen, RT_NAME_MAX, thread->parent.name, thread->current_priority);
#else
    rt_kprintf("%-*.*s %3d ", maxlen, RT_NAME_MAX, thread->parent.name, thread->current_priority);
#endif /*RT_USING_SMP*/

    stat = (thread->stat & RT_THREAD_STAT_MASK);
    if (stat == RT_THREAD_READY)        rt_kprintf(" ready  ");
    else if ((stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK) rt_kprintf(" suspend");
    else if (stat == RT_THREAD_INIT)    rt_kprintf(" init   ");
    else if (stat == RT_THREAD_CLOSE)   rt_kprintf(" close  ");
    else if (stat == RT_THREAD_RUNNING) rt_kprintf(" running");

#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
    ptr = (rt_uint8_t *)thread->stack_addr + thread->stack_size;
    while (*ptr == '#')ptr--;

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
            ((rt_uint32_t)thread->sp - (rt_uint32_t)thread->stack_addr),
            thread->stack_size,
            ((rt_uint32_t)ptr - (rt_uint32_t)thread->stack_addr) * 100 / thread->stack_size,
            thread->remaining_tick,
            thread->error);
#else
    ptr = (rt_uint8_t *)thread->stack_addr;
    while (*ptr == '#')ptr++;

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
            (thread->stack_size + (rt_uint32_t)(rt_size_t)thread->stack_addr - (rt_uint32_t)(rt_size_t)thread->sp),
            thread->stack_size,
            (thread->stack_size + (rt_uint32_t)(rt_size_t)thread->stack_addr - (rt_uint32_t)(rt_size_t)ptr) * 100
            / thread->stack_size,
            thread->remaining_tick,
            thread->error);
#endif
}

long list_process(void)
{
    int index;
    int maxlen;
    rt_ubase_t level;
    struct rt_thread *thread;
    struct rt_list_node *node, *list;
    const char *item_title = "thread";

    int count = 0;
    struct rt_thread **threads;

    maxlen = RT_NAME_MAX;
#ifdef RT_USING_SMP
    rt_kprintf("%-*.s %-*.s %-*.s cpu pri  status      sp     stack size max used left tick  error\n", 4, "PID", maxlen, "CMD", maxlen, item_title);
    object_split(4);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");
    rt_kprintf(                  "--- ---  ------- ---------- ----------  ------  ---------- ---\n");
#else
    rt_kprintf("%-*.s %-*.s %-*.s pri  status      sp     stack size max used left tick  error\n", 4, "PID", maxlen, "CMD", maxlen, item_title);
    object_split(4);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");
    rt_kprintf(                  "---  ------- ---------- ----------  ------  ---------- ---\n");
#endif /*RT_USING_SMP*/

    count = rt_object_get_length(RT_Object_Class_Thread);
    if (count > 0)
    {
        /* get thread pointers */
        threads = (struct rt_thread **)rt_calloc(count, sizeof(struct rt_thread *));
        if (threads)
        {
            index = rt_object_get_pointers(RT_Object_Class_Thread, (rt_object_t *)threads, count);

            if (index > 0)
            {
                for (index = 0; index <count; index++)
                {
                    struct rt_thread th;

                    thread = threads[index];
                    level = rt_hw_interrupt_disable();
                    if ((thread->parent.type & ~RT_Object_Class_Static) != RT_Object_Class_Thread)
                    {
                        rt_hw_interrupt_enable(level);
                        continue;
                    }

                    rt_memcpy(&th, thread, sizeof(struct rt_thread));
                    rt_hw_interrupt_enable(level);

                    if (th.lwp == RT_NULL)
                    {
                        rt_kprintf("     %-*.*s ", maxlen, RT_NAME_MAX, "kernel");
                        print_thread_info(&th, maxlen);
                    }
                }
            }
            rt_free(threads);
        }
    }

    for (index = 0; index < RT_LWP_MAX_NR; index++)
    {
        struct rt_lwp *lwp = (struct rt_lwp *)lwp_pid_ary[index].data;

        if (lwp)
        {
            list = &lwp->t_grp;
            for (node = list->next; node != list; node = node->next)
            {
                thread = rt_list_entry(node, struct rt_thread, sibling);
                rt_kprintf("%4d %-*.*s ", lwp_to_pid(lwp), maxlen, RT_NAME_MAX, lwp->cmd);
                print_thread_info(thread, maxlen);
            }
        }
    }
    return 0;
}
MSH_CMD_EXPORT(list_process, list process);

static void cmd_kill(int argc, char** argv)
{
    int pid;
    int sig = 0;

    if (argc < 2)
    {
        rt_kprintf("kill pid or kill pid -s signal\n");
        return;
    }

    pid = atoi(argv[1]);
    if (argc >= 4)
    {
        if (argv[2][0] == '-' && argv[2][1] == 's')
        {
            sig = atoi(argv[3]);
        }
    }
    lwp_signal_kill(lwp_from_pid(pid), sig, SI_USER, 0);
}
MSH_CMD_EXPORT_ALIAS(cmd_kill, kill, send a signal to a process);

static void cmd_killall(int argc, char** argv)
{
    int pid;
    if (argc < 2)
    {
        rt_kprintf("killall processes_name\n");
        return;
    }

    while((pid = lwp_name2pid(argv[1])) > 0)
    {
        lwp_signal_kill(lwp_from_pid(pid), SIGKILL, SI_USER, 0);
        rt_thread_mdelay(100);
    }
}
MSH_CMD_EXPORT_ALIAS(cmd_killall, killall, kill processes by name);

#endif

int lwp_check_exit_request(void)
{
    rt_thread_t thread = rt_thread_self();
    if (!thread->lwp)
    {
        return 0;
    }

    if (thread->exit_request == LWP_EXIT_REQUEST_TRIGGERED)
    {
        thread->exit_request = LWP_EXIT_REQUEST_IN_PROCESS;
        return 1;
    }
    return 0;
}

static int found_thread(struct rt_lwp* lwp, rt_thread_t thread)
{
    int found = 0;
    rt_base_t level;
    rt_list_t *list;

    level = rt_hw_interrupt_disable();
    list = lwp->t_grp.next;
    while (list != &lwp->t_grp)
    {
        rt_thread_t iter_thread;

        iter_thread = rt_list_entry(list, struct rt_thread, sibling);
        if (thread == iter_thread)
        {
            found = 1;
            break;
        }
        list = list->next;
    }
    rt_hw_interrupt_enable(level);
    return found;
}

void lwp_request_thread_exit(rt_thread_t thread_to_exit)
{
    rt_thread_t main_thread;
    rt_base_t level;
    rt_list_t *list;
    struct rt_lwp *lwp;

    lwp = lwp_self();

    if ((!thread_to_exit) || (!lwp))
    {
        return;
    }

    level = rt_hw_interrupt_disable();

    main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (thread_to_exit == main_thread)
    {
        goto finish;
    }
    if ((struct rt_lwp *)thread_to_exit->lwp != lwp)
    {
        goto finish;
    }

    for (list = lwp->t_grp.next; list != &lwp->t_grp; list = list->next)
    {
        rt_thread_t thread;

        thread = rt_list_entry(list, struct rt_thread, sibling);
        if (thread != thread_to_exit)
        {
            continue;
        }
        if (thread->exit_request == LWP_EXIT_REQUEST_NONE)
        {
            thread->exit_request = LWP_EXIT_REQUEST_TRIGGERED;
        }
        if ((thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
        {
            thread->error = -RT_EINTR;
            rt_hw_dsb();
            rt_thread_wakeup(thread);
        }
        break;
    }

    while (found_thread(lwp, thread_to_exit))
    {
        rt_thread_mdelay(10);
    }

finish:
    rt_hw_interrupt_enable(level);
    return;
}

void lwp_terminate(struct rt_lwp *lwp)
{
    rt_base_t level;
    rt_list_t *list;

    if (!lwp)
    {
        /* kernel thread not support */
        return;
    }

    LOG_D("%s(lwp=%p \"%s\")", __func__, lwp, lwp->cmd);

    level = rt_hw_interrupt_disable();

    /* stop the receiving of signals */
    if (!lwp->terminated)
    {
        lwp->terminated = RT_TRUE;

        /* broadcast exit request for sibling threads */
        for (list = lwp->t_grp.next; list != &lwp->t_grp; list = list->next)
        {
            rt_thread_t thread;

            thread = rt_list_entry(list, struct rt_thread, sibling);
            if (thread->exit_request == LWP_EXIT_REQUEST_NONE)
            {
                thread->exit_request = LWP_EXIT_REQUEST_TRIGGERED;
            }
            if ((thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
            {
                thread->error = RT_EINTR;
                rt_hw_dsb();
                rt_thread_wakeup(thread);
            }
        }
    }
    rt_hw_interrupt_enable(level);
}

void lwp_wait_subthread_exit(void)
{
    rt_base_t level;
    struct rt_lwp *lwp;
    rt_thread_t thread;
    rt_thread_t main_thread;

    lwp = lwp_self();
    if (!lwp)
    {
        return;
    }

    thread = rt_thread_self();
    main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (thread != main_thread)
    {
        return;
    }

    while (1)
    {
        int subthread_is_terminated;
        LOG_D("%s: wait for subthread exiting", __func__);

        level = rt_hw_interrupt_disable();
        subthread_is_terminated = (int)(thread->sibling.prev == &lwp->t_grp);
        if (!subthread_is_terminated)
        {
            rt_thread_t sub_thread;
            rt_list_t *list;
            int all_subthread_in_init = 1;

            /* check all subthread is in init state */
            for (list = thread->sibling.prev; list != &lwp->t_grp; list = list->prev)
            {

                sub_thread = rt_list_entry(list, struct rt_thread, sibling);
                if ((sub_thread->stat & RT_THREAD_STAT_MASK) != RT_THREAD_INIT)
                {
                    all_subthread_in_init = 0;
                    break;
                }
            }
            if (all_subthread_in_init)
            {
                /* delete all subthread */
                while ((list = thread->sibling.prev) != &lwp->t_grp)
                {
                    sub_thread = rt_list_entry(list, struct rt_thread, sibling);
                    rt_list_remove(&sub_thread->sibling);
                    rt_thread_delete(sub_thread);
                }
                subthread_is_terminated = 1;
            }
        }
        rt_hw_interrupt_enable(level);

        if (subthread_is_terminated)
        {
            break;
        }
        rt_thread_mdelay(10);
    }
}

static int _lwp_setaffinity(pid_t pid, int cpu)
{
    struct rt_lwp *lwp;
    int ret = -1;

    lwp = lwp_from_pid(pid);
    if (lwp)
    {
#ifdef RT_USING_SMP
        rt_list_t *list;

        lwp->bind_cpu = cpu;
        for (list = lwp->t_grp.next; list != &lwp->t_grp; list = list->next)
        {
            rt_thread_t thread;

            thread = rt_list_entry(list, struct rt_thread, sibling);
            rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)(rt_size_t)cpu);
        }
#endif
        ret = 0;
    }
    return ret;
}

int lwp_setaffinity(pid_t pid, int cpu)
{
    rt_base_t level;
    int ret;

#ifdef RT_USING_SMP
    if (cpu < 0 || cpu > RT_CPUS_NR)
    {
        cpu = RT_CPUS_NR;
    }
#endif
    level = rt_hw_interrupt_disable();
    ret = _lwp_setaffinity(pid, cpu);
    rt_hw_interrupt_enable(level);
    return ret;
}

#ifdef RT_USING_SMP
static void cmd_cpu_bind(int argc, char** argv)
{
    int pid;
    int cpu;

    if (argc < 3)
    {
        rt_kprintf("Useage: cpu_bind pid cpu\n");
        return;
    }

    pid = atoi(argv[1]);
    cpu = atoi(argv[2]);
    lwp_setaffinity((pid_t)pid, cpu);
}
MSH_CMD_EXPORT_ALIAS(cmd_cpu_bind, cpu_bind, set a process bind to a cpu);
#endif
