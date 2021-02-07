/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-16     zhangjun     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <dfs_posix.h>

#include "lwp.h"
#include "lwp_pid.h"
#include "lwp_console.h"

#ifdef RT_USING_USERSPACE
#include "lwp_user_mm.h"

#ifdef RT_USING_GDBSERVER
#include <hw_breakpoint.h>
#include <lwp_gdbserver.h>
#endif

#endif

#define DBG_TAG    "LWP_PID"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

struct rt_pid_struct
{
    struct rt_lwp* pidmap[RT_LWP_MAX_NR];
    pid_t last_pid;
};
static struct rt_pid_struct pid_struct = {0};

int libc_stdio_get_console(void);

static void __exit_files(struct rt_lwp *lwp)
{
    int fd = lwp->fdt.maxfd - 1;

    while (fd >= 0)
    {
        struct dfs_fd *d;

        d = lwp->fdt.fds[fd];
        if (d)
        {
            dfs_file_close(d);
            fdt_fd_release(&lwp->fdt, fd);
        }
        fd--;
    }
}

struct rt_lwp* lwp_new(void)
{
    uint32_t i;
    rt_base_t level;
    struct rt_lwp* lwp = RT_NULL;

    level = rt_hw_interrupt_disable();
    /* first scan */
    for (i=pid_struct.last_pid; i<RT_LWP_MAX_NR; i++)
    {
        if (!pid_struct.pidmap[i])
        {
            break;
        }
    }

    /* if first scan failed, scan the pidmap start with 0 */
    if (i >= RT_LWP_MAX_NR)
    {
        for (i=0; i<pid_struct.last_pid; i++)
        {
            if (!pid_struct.pidmap[i])
            {
                break;
            }
        }
    }

    if (i >= RT_LWP_MAX_NR)
    {
        /* if second scan also failed */
        LOG_W("pidmap fulled\n");
        pid_struct.last_pid = 0;
        goto out;
    }
    pid_struct.last_pid = (i + 1)%RT_LWP_MAX_NR;
    lwp = (struct rt_lwp *)rt_malloc(sizeof(struct rt_lwp));
    if (lwp == RT_NULL)
    {
        LOG_E("no memory for lwp struct!\n");
        goto out;
    }
    rt_memset(lwp, 0, sizeof(*lwp));
    rt_list_init(&lwp->wait_list);
    lwp->pid = i;
    pid_struct.pidmap[i] = lwp;
    rt_list_init(&lwp->t_grp);
    rt_list_init(&lwp->object_list);
    lwp->address_search_head = RT_NULL;
    rt_wqueue_init(&lwp->wait_queue);

    lwp->ref = 1;
out:
    rt_hw_interrupt_enable(level);
    return lwp;
}

static void lwp_user_obj_free(struct rt_lwp *lwp)
{
    rt_base_t level = 0;
    struct rt_list_node *list = RT_NULL, *node = RT_NULL;
    struct rt_object *object = RT_NULL;

    list = &(lwp->object_list);

    level = rt_hw_interrupt_disable();
    while ((node = list->next) != list)
    {
        object = rt_list_entry(node, struct rt_object, lwp_obj_list);
        /* remove from kernel object list */
        switch (object->type)
        {
        case RT_Object_Class_Thread:
        {
            rt_thread_t tid = (rt_thread_t)object;
            if (tid->stat != RT_THREAD_CLOSE)
            {
                rt_thread_delete(tid);
            }
            break;
        }
        case RT_Object_Class_Semaphore:
            rt_sem_delete((rt_sem_t)object);
            break;
        case RT_Object_Class_Mutex:
            rt_mutex_delete((rt_mutex_t)object);
            break;
        case RT_Object_Class_Event:
            rt_event_delete((rt_event_t)object);
            break;
        case RT_Object_Class_MailBox:
            rt_mb_delete((rt_mailbox_t)object);
            break;
        case RT_Object_Class_MessageQueue:
            rt_mq_delete((rt_mq_t)object);
            break;
        case RT_Object_Class_Device:
            rt_device_close((rt_device_t)object);
            break;
        case RT_Object_Class_Timer:
            rt_timer_delete((rt_timer_t)object);
            break;
        case RT_Object_Class_Channel:
            /* remove from object list */
            rt_list_remove(&object->list);
            break;
        case RT_Object_Class_Custom:
            rt_custom_object_destroy(object);
            break;
        default:
            LOG_E("input object type(%d) error", object->type);
            /* remove from object list */
            rt_list_remove(&object->list);
            break;
        }
    }
    rt_hw_interrupt_enable(level);
}

void lwp_free(struct rt_lwp* lwp)
{
    rt_base_t level;

    if (lwp == NULL) return ;

    LOG_D("lwp free: %p\n", lwp);

    level = rt_hw_interrupt_disable();

    lwp->finish = 1;
    if (lwp->args != RT_NULL)
    {
#ifndef RT_USING_USERSPACE
        rt_free(lwp->args);
#endif
        lwp->args = RT_NULL;
    }

    if (lwp->fdt.fds != RT_NULL)
    {
        /* auto clean fds */
        __exit_files(lwp);
        lwp_user_obj_free(lwp);
        rt_free(lwp->fdt.fds);
        lwp->fdt.fds = RT_NULL;
    }

    /* free data section */
    if (lwp->data_entry != RT_NULL)
    {
        rt_free_align(lwp->data_entry);
        lwp->data_entry = RT_NULL;
    }

    /* free text section */
    if (lwp->lwp_type == LWP_TYPE_DYN_ADDR)
    {
        if (lwp->text_entry)
        {
            LOG_D("lwp text free: %p", lwp->text_entry);
#ifndef RT_USING_USERSPACE
#ifdef RT_USING_CACHE
            rt_free_align(lwp->text_entry);
#else
            rt_free(lwp->text_entry);
#endif
#endif
            lwp->text_entry = RT_NULL;
        }
    }

#ifdef RT_USING_USERSPACE
    lwp_unmap_user_space(lwp);
#endif

    /* for children */
    while (lwp->first_child)
    {
        struct rt_lwp *child;

        child = lwp->first_child;
        lwp->first_child = child->sibling;
        if (child->finish)
        {
            pid_struct.pidmap[lwp_to_pid(child)] = RT_NULL;
            rt_free(child);
        }
        else
        {
            child->sibling = RT_NULL;
            child->parent = RT_NULL;
        }
    }

    /* for parent */
    {
        struct rt_lwp *console_lwp;

        console_lwp = rt_console_get_foreground();
        if (lwp == console_lwp)
        {
            rt_console_set_foreground(lwp->parent);
        }

        if (lwp->parent)
        {
            struct rt_thread *thread;
            if (!rt_list_isempty(&lwp->wait_list))
            {
                thread = rt_list_entry(lwp->wait_list.next, struct rt_thread, tlist);
                thread->error = RT_EOK;
                thread->msg_ret = (void*)lwp->lwp_ret;
                rt_thread_resume(thread);
            }
        }
        else
        {
            pid_struct.pidmap[lwp_to_pid(lwp)] = RT_NULL;
            rt_free(lwp);
        }
    }

    rt_hw_interrupt_enable(level);
}

void lwp_ref_inc(struct rt_lwp *lwp)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    lwp->ref++;
    rt_hw_interrupt_enable(level);
}

void lwp_ref_dec(struct rt_lwp *lwp)
{
    rt_base_t level;
    int ref;

    level = rt_hw_interrupt_disable();
    if (lwp->ref)
    {
        lwp->ref--;
        ref = lwp->ref;
        if (!ref)
        {
#ifdef RT_USING_GDBSERVER
            struct rt_channel_msg msg;

            if (lwp->debug)
            {
                memset(&msg, 0, sizeof msg);
                rt_raw_channel_send(gdb_get_server_channel(), &msg);
            }
#endif
            lwp_free(lwp);
        }
    }
    rt_hw_interrupt_enable(level);
}

struct rt_lwp* lwp_from_pid(pid_t pid)
{
    return pid_struct.pidmap[pid];
}

pid_t lwp_to_pid(struct rt_lwp* lwp)
{
    return lwp->pid;
}

char* lwp_pid2name(int32_t pid)
{
    struct rt_lwp* lwp;
    char* process_name = RT_NULL;

    lwp = pid_struct.pidmap[pid];
    if (lwp)
    {
        process_name = strrchr(lwp->cmd, '/');
        process_name = process_name? process_name + 1: lwp->cmd;
    }
    return process_name;
}

int32_t lwp_name2pid(const char* name)
{
    uint32_t pid;
    rt_thread_t main_thread;
    char* process_name = RT_NULL;
    struct rt_lwp* lwp = RT_NULL;

    for (pid=0; pid<RT_LWP_MAX_NR; pid++)
    {
        if (pid_struct.pidmap[pid])
        {
            lwp = pid_struct.pidmap[pid];
            process_name = strrchr(lwp->cmd, '/');
            process_name = process_name? process_name + 1: lwp->cmd;
            if (!rt_strncmp(name, process_name, RT_NAME_MAX))
            {
                main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
                if (!(main_thread->stat & RT_THREAD_CLOSE))
                {
                    return pid;
                }
            }
        }
    }
    return -1;
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

    lwp_self = (struct rt_lwp*)rt_thread_self()->lwp;
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
        struct rt_lwp **lwp_node;

        *status = lwp->lwp_ret;
        lwp_node = &lwp_self->first_child;
        while (*lwp_node != lwp)
        {
            RT_ASSERT(*lwp_node != RT_NULL);
            lwp_node = &(*lwp_node)->sibling;
        }
        (*lwp_node) = lwp->sibling;

        pid_struct.pidmap[pid] = RT_NULL;
        rt_free(lwp);
    }

quit:
    rt_hw_interrupt_enable(level);
    return ret;
}

#ifdef RT_USING_FINSH
/* copy from components/finsh/cmd.c */
static void object_split(int len)
{
    while (len--) rt_kprintf("-");
}

static void print_thread_info(struct rt_thread* thread, int maxlen)
{
    rt_uint8_t *ptr;
    rt_uint8_t stat;

#ifdef RT_USING_SMP
    if (thread->oncpu != RT_CPU_DETACHED)
        rt_kprintf("%-*.*s %3d %3d ", maxlen, RT_NAME_MAX, thread->name, thread->oncpu, thread->current_priority);
    else
        rt_kprintf("%-*.*s N/A %3d ", maxlen, RT_NAME_MAX, thread->name, thread->current_priority);
#else
    rt_kprintf("%-*.*s %3d ", maxlen, RT_NAME_MAX, thread->name, thread->current_priority);
#endif /*RT_USING_SMP*/

    stat = (thread->stat & RT_THREAD_STAT_MASK);
    if (stat == RT_THREAD_READY)        rt_kprintf(" ready  ");
    else if ((stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK) rt_kprintf(" suspend");
    else if (stat == RT_THREAD_INIT)    rt_kprintf(" init   ");
    else if (stat == RT_THREAD_CLOSE)   rt_kprintf(" close  ");
    else if (stat == RT_THREAD_RUNNING) rt_kprintf(" running");

#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
    ptr = (rt_uint8_t *)thread->stack_addr + thread->stack_size;
    while (*ptr == '#')ptr --;

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
            ((rt_uint32_t)thread->sp - (rt_uint32_t)thread->stack_addr),
            thread->stack_size,
            ((rt_uint32_t)ptr - (rt_uint32_t)thread->stack_addr) * 100 / thread->stack_size,
            thread->remaining_tick,
            thread->error);
#else
    ptr = (rt_uint8_t *)thread->stack_addr;
    while (*ptr == '#')ptr ++;

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
            (thread->stack_size + (rt_uint32_t)thread->stack_addr - (rt_uint32_t)thread->sp),
            thread->stack_size,
            (thread->stack_size + (rt_uint32_t)thread->stack_addr - (rt_uint32_t) ptr) * 100
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
    struct rt_lwp* lwp = RT_NULL;
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
        threads = (struct rt_thread **)rt_calloc(count, sizeof(struct rt_thread*));
        if (threads)
        {
            index = rt_object_get_pointers(RT_Object_Class_Thread, (rt_object_t *)threads, count);

            if (index > 0)
            {
                for (index = 0; index <count; index ++)
                {
                    struct rt_thread th;

                    thread = threads[index];
                    level = rt_hw_interrupt_disable();
                    if ((thread->type & ~RT_Object_Class_Static) != RT_Object_Class_Thread)
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

    for (index=0; index<RT_LWP_MAX_NR; index++)
    {
        if (pid_struct.pidmap[index])
        {
            lwp = pid_struct.pidmap[index];
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
    lwp_kill(pid, sig);
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

    while((pid = lwp_name2pid(argv[1])) >= 0)
    {
        lwp_kill(pid, 0);
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
    if ((struct rt_lwp*)thread_to_exit->lwp != lwp)
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
            thread->error = RT_EINTR;
            dsb();
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

    level = rt_hw_interrupt_disable();
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
            dsb();
            rt_thread_wakeup(thread);
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
    if (!lwp) return;

    thread = rt_thread_self();
    main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (thread != main_thread)
    {
        return;
    }

    while (1)
    {
        int subthread_is_terminated;

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
