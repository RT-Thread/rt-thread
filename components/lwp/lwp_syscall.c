/*
 * File      : lwp_syscall.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

/* RT-Thread System call */
#include <lwp.h>
#include <lwp_mem.h>
#include <lwp_syscall.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME    "[LWP_CALL]"
#define DBG_COLOR
#define DBG_LEVEL           DBG_WARNING
#include <rtdbg.h>

/* thread/process */
void sys_exit(int value)
{
    /* TODO: handle the return_value */

    dbg_log(DBG_LOG, "enter sys_exit\n");

    rt_thread_delete(rt_thread_self());

    rt_schedule();

    return;
}

/* syscall: "read" ret: "ssize_t" args: "int" "void *" "size_t" */
ssize_t sys_read(int fd, void *buf, size_t nbyte)
{
    return read(fd, buf, nbyte);
}

/* syscall: "write" ret: "ssize_t" args: "int" "const void *" "size_t" */
ssize_t sys_write(int fd, const void *buf, size_t nbyte)
{
    return write(fd, buf, nbyte);
}

/* syscall: "lseek" ret: "off_t" args: "int" "off_t" "int" */
off_t sys_lseek(int fd, off_t offset, int whence)
{
    return lseek(fd, offset, whence);
}

/* syscall: "open" ret: "int" args: "const char *" "int" "..." */
int sys_open(const char *name, int mode, ...)
{
    return open(name, mode, 0);
}

/* syscall: "close" ret: "int" args: "int" */
int sys_close(int fd)
{
    return close(fd);
}

/* syscall: "ioctl" ret: "int" args: "int" "u_long" "..." */
int sys_ioctl(int fd, unsigned long cmd, void* data)
{
    return ioctl(fd, cmd, data);
}

/* syscall: "nanosleep" ret: "int" args: "const struct timespec *" "struct timespec *" */
int sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    rt_tick_t tick;

    dbg_log(DBG_LOG, "sys_nanosleep\n");

    tick = rqtp->tv_sec * RT_TICK_PER_SECOND + (rqtp->tv_nsec * RT_TICK_PER_SECOND)/ 1000000000;
    rt_thread_delay(tick);

    if (rmtp)
    {
        tick = rt_tick_get() - tick;
        /* get the passed time */
        rmtp->tv_sec = tick/RT_TICK_PER_SECOND;
        rmtp->tv_nsec = (tick%RT_TICK_PER_SECOND) * (1000000000/RT_TICK_PER_SECOND);
    }

    return 0;
}

/* syscall: "getpriority" ret: "int" args: "int" "id_t" */
int sys_getpriority(int which, id_t who)
{
    if (which == PRIO_PROCESS)
    {
        rt_thread_t tid;

        tid = rt_thread_self();
        if (who == (id_t)tid || who == 0xff)
        {
            return tid->current_priority;
        }
    }

    return 0xff;
}

/* syscall: "setpriority" ret: "int" args: "int" "id_t" "int" */
int sys_setpriority(int which, id_t who, int prio)
{
    if (which == PRIO_PROCESS)
    {
        rt_thread_t tid;

        tid = rt_thread_self();
        if ((who == (id_t)tid || who == 0xff) && (prio >= 0 && prio < RT_THREAD_PRIORITY_MAX))
        {
            rt_thread_control(tid, RT_THREAD_CTRL_CHANGE_PRIORITY, &prio);
            return 0;
        }
    }

    return -1;
}

/* syscall: "gettimeofday" ret: "int" args: "struct timeval *" "struct timezone *" */
int sys_gettimeofday(struct timeval *tp, struct timezone *tzp)
{
    if (tp)
    {
        tp->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        tp->tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);
    }

    return 0;
}

/* syscall: "settimeofday" ret: "int" args: "const struct timeval *" "const struct timezone *" */
int sys_settimeofday(const struct timeval *tv, const struct timezone *tzp)
{
    return 0;
}

/* syscall: "msgget" ret: "int" args: "key_t" "int" */
int sys_msgget(key_t key, int msgflg)
{
    return -1;
}

/* syscall: "msgsnd" ret: "int" args: "int" "const void *" "size_t" "int" */
int sys_msgsend(int msqid, const void *msgp, size_t msgsz, int msgflg)
{
    return -1;
}

/* syscall: "msgrcv" ret: "int" args: "int" "void *" "size_t" "long" "int" */
int sys_msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
    return -1;
}

/* syscall: "sys_log" ret: "int" args: "const char*" "size" */
int sys_log(const char* log, int size)
{
    rt_device_t console = rt_console_get_device();

    if (console) rt_device_write(console, -1, log, size);

    return 0;
}

void *sys_malloc(size_t size)
{
    return rt_lwp_mem_malloc(size);
}

void sys_free(void *addr)
{
    rt_lwp_mem_free(addr);
}

void *sys_realloc(void *rmem, size_t newsize)
{
    return rt_lwp_mem_realloc(rmem, newsize);
}

int sys_fstat(int file, struct stat *buf)
{
    return fstat(file, buf);
}

const static void* func_table[] =
{
    (void *)sys_exit,           // 0x01
    (void *)sys_read,           // 0x02
    (void *)sys_write,          // 0x03
    (void *)sys_lseek,          // 0x04
    (void *)sys_open,           // 0x05
    (void *)sys_close,          // 0x06
    (void *)sys_ioctl,          // 0x07

    (void *)sys_nanosleep,      // 0x08

    (void *)sys_getpriority,    // 0x09
    (void *)sys_setpriority,    // 0x0a

    (void *)sys_gettimeofday,   // 0x0b
    (void *)sys_settimeofday,   // 0x0c
        
    (void *)sys_malloc,         // 0x0d
    (void *)sys_free,           // 0x0e
    (void *)sys_realloc,      //0x0f
    (void *)sys_fstat,           // 0x10
};

const void *lwp_get_sys_api(rt_uint32_t number)
{
    const void *func = RT_NULL;

    if (number == 0xff)
    {
        func = (void *)sys_log;
    }
    else
    {
        number -= 1;
        if (number < sizeof(func_table)/sizeof(func_table[0]))
        {
            func = func_table[number];
        }
    }

    return func;
}
