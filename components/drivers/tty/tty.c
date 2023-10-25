/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-07     linzhenxing  first version
 * 2023-06-26     WangXiaoyao  fix bug on foreground app switch
 */
#include <dfs_file.h>
#include <dfs_fs.h>
#include <lwp.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <tty.h>
#include <tty_ldisc.h>
#include <shell.h>

#if defined(RT_USING_POSIX_DEVIO)
#include <termios.h>
#endif

#define DBG_TAG               "TTY"
#ifdef RT_TTY_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_TTY_DEBUG */
#include <rtdbg.h>

const struct termios tty_std_termios = {  /* for the benefit of tty drivers  */
    .c_iflag = IMAXBEL | IUCLC | INLCR | ICRNL | IGNPAR,
    .c_oflag = OPOST,
    .c_cflag = B38400 | CS8 | CREAD | HUPCL,
    .c_lflag = ISIG | ECHOE  | TOSTOP | NOFLSH,
    RT_NULL,/* .c_line = N_TTY, */
    .c_cc = INIT_C_CC,
    .__c_ispeed = 38400,
    .__c_ospeed = 38400
};

void tty_initstack(struct tty_node *node)
{
    node->lwp = RT_NULL;
    node->next = RT_NULL;
}

static struct tty_node tty_node_cache = { RT_NULL, RT_NULL };

static struct tty_node *_tty_node_alloc(void)
{
    struct tty_node *node = tty_node_cache.next;

    if (node == RT_NULL)
    {
        node = rt_calloc(1, sizeof(struct tty_node));
    }
    else
    {
        tty_node_cache.next = node->next;
    }

    return node;
}

static void _tty_node_free(struct tty_node *node)
{
    node->next = tty_node_cache.next;
    tty_node_cache.next = node;
}

int tty_push(struct tty_node **head, struct rt_lwp *lwp)
{
    struct tty_node *node = _tty_node_alloc();

    if (!node)
    {
        return -1;
    }

    node->lwp = lwp;
    node->next = *head;
    *head = node;

    return 0;
}

struct rt_lwp *tty_pop(struct tty_node **head, struct rt_lwp *target_lwp)
{
    struct tty_node *node;
    struct rt_lwp *lwp = RT_NULL;

    if (!head || !*head)
    {
        return RT_NULL;
    }

    node = *head;

    if (target_lwp != RT_NULL && node->lwp != target_lwp)
    {
        struct tty_node *prev = RT_NULL;

        while (node != RT_NULL && node->lwp != target_lwp)
        {
            prev = node;
            node = node->next;
        }

        if (node != RT_NULL)
        {
            /* prev is impossible equ RT_NULL */
            prev->next = node->next;
            lwp = target_lwp;
            _tty_node_free(node);
        }
    }
    else
    {
        lwp = (*head)->lwp;
        *head = (*head)->next;
        node->lwp = RT_NULL;
        _tty_node_free(node);
    }

    return lwp;
}

/**
 *  tty_check_change    -   check for POSIX terminal changes
 *  @tty: tty to check
 *
 *  If we try to write to, or set the state of, a terminal and we're
 *  not in the foreground, send a SIGTTOU.  If the signal is blocked or
 *  ignored, go ahead and perform the operation.  (POSIX 7.2)
 *
 *  Locking: ctrl_lock
 */

int __tty_check_change(struct tty_struct *tty, int sig)
{
    pid_t pgrp = 0, tty_pgrp = 0;
    int ret = 0;
    struct rt_lwp *lwp;

    lwp = lwp_self();

    if (lwp == RT_NULL)
    {
        return 0;
    }

    if (lwp->tty != tty)
    {
        return 0;
    }

    pgrp = lwp->__pgrp;
    tty_pgrp = tty->pgrp;

    if (tty_pgrp && (pgrp != tty->pgrp))
    {
        lwp_signal_kill(lwp, sig, SI_USER, 0);
    }

    if (!tty_pgrp)
    {
        LOG_D("sig=%d, tty->pgrp == -1!\n", sig);
    }
    return ret;
}

int tty_check_change(struct tty_struct *tty)
{
    return __tty_check_change(tty, SIGTTOU);
}

static int tty_open(struct dfs_file *fd)
{
    int ret = 0;
    int noctty = 0;
    struct tty_struct *tty = RT_NULL;
    struct tty_ldisc *ld = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);

    ld = tty->ldisc;
    if (ld->ops->open)
    {
        ret = ld->ops->open(fd);
    }
    noctty = (fd->flags & O_NOCTTY);

    rt_device_t device = (rt_device_t)fd->vnode->data;
    if (fd->vnode->ref_count == 1)
    {
        ret = rt_device_open(device, fd->flags);
    }
    if (current == RT_NULL) //kernel mode not lwp
    {
        return ret;
    }

    if (!noctty &&
        current->leader &&
        !current->tty &&
        tty->session == -1)
    {
        current->tty = tty;
        current->tty_old_pgrp = 0;
        tty->session = current->session;
        tty->pgrp = current->__pgrp;
        tty->foreground = current;
    }

    return ret;
}

static int tty_close(struct dfs_file *fd)
{
    int ret = 0;
    struct tty_struct *tty = RT_NULL;
    struct tty_ldisc *ld = RT_NULL;
    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);
    ld = tty->ldisc;
    if (ld->ops->close)
    {
        //ld->ops->close(tty);
    }
    if (fd->vnode->ref_count == 1)
    {
        ret = rt_device_close((rt_device_t)tty);
    }
    return ret;
}

static int tiocsctty(struct tty_struct *tty, int arg)
{
    if (current->leader &&
        (current->session == tty->session))
    {
        return 0;
    }

    /*
     * The process must be a session leader and
     * not have a controlling tty already.
     */
    if (!current->leader || current->tty)
    {
        return -EPERM;
    }

    if (tty->session > 0)
    {
        LOG_E("this tty have control process\n");

    }
    current->tty = tty;
    current->tty_old_pgrp = 0;
    tty->session = current->session;
    tty->pgrp = current->__pgrp;
    tty->foreground = current;
    if (tty->type == TTY_DRIVER_TYPE_PTY)
    {
        tty->other_struct->foreground = current;
    }
    return 0;
}

static int tiocswinsz(struct tty_struct *tty, struct winsize *p_winsize)
{
    rt_kprintf("\x1b[8;%d;%dt", p_winsize->ws_col, p_winsize->ws_row);
    return 0;
}

static int tiocgwinsz(struct tty_struct *tty, struct winsize *p_winsize)
{
    if(rt_thread_self() != rt_thread_find(FINSH_THREAD_NAME))
    {
        /* only can be used in tshell thread; otherwise, return default size */
        p_winsize->ws_col = 80;
        p_winsize->ws_row = 24;
    }
    else
    {
        #define _TIO_BUFLEN 20
        char _tio_buf[_TIO_BUFLEN];
        unsigned char cnt1, cnt2, cnt3, i;
        char row_s[4], col_s[4];
        char *p;

        rt_memset(_tio_buf, 0, _TIO_BUFLEN);

        /* send the command to terminal for getting the window size of the terminal */
        rt_kprintf("\033[18t");

        /* waiting for the response from the terminal */
        i = 0;
        while(i < _TIO_BUFLEN)
        {
            _tio_buf[i] = finsh_getchar();
            if(_tio_buf[i] != 't')
            {
                i ++;
            }
            else
            {
                break;
            }
        }
        if(i == _TIO_BUFLEN)
        {
            /* buffer overloaded, and return default size */
            p_winsize->ws_col = 80;
            p_winsize->ws_row = 24;
            return 0;
        }

        /* interpreting data eg: "\033[8;1;15t" which means row is 1 and col is 15 (unit: size of ONE character) */
        rt_memset(row_s,0,4);
        rt_memset(col_s,0,4);
        cnt1 = 0;
        while(cnt1 < _TIO_BUFLEN && _tio_buf[cnt1] != ';')
        {
            cnt1++;
        }
        cnt2 = ++cnt1;
        while(cnt2 < _TIO_BUFLEN && _tio_buf[cnt2] != ';')
        {
            cnt2++;
        }
        p = row_s;
        while(cnt1 < cnt2)
        {
            *p++ = _tio_buf[cnt1++];
        }
        p = col_s;
        cnt2++;
        cnt3 = rt_strlen(_tio_buf) - 1;
        while(cnt2 < cnt3)
        {
            *p++ = _tio_buf[cnt2++];
        }

        /* load the window size date */
        p_winsize->ws_col = atoi(col_s);
        p_winsize->ws_row = atoi(row_s);
    #undef _TIO_BUFLEN
    }

    p_winsize->ws_xpixel = 0;/* unused */
    p_winsize->ws_ypixel = 0;/* unused */

    return 0;
}

static int tty_ioctl(struct dfs_file *fd, int cmd, void *args)
{
    int ret = 0;
    void *p = (void *)args;
    struct tty_struct *tty = RT_NULL;
    struct tty_struct *real_tty = RT_NULL;
    struct tty_ldisc *ld = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);

    if (tty->type == TTY_DRIVER_TYPE_PTY && tty->subtype == PTY_TYPE_MASTER)
    {
        real_tty = tty->other_struct;
    }
    else
    {
        real_tty = tty;
    }

    switch (cmd)
    {
    case TIOCSCTTY:
        return tiocsctty(real_tty, 1);
    case TIOCGWINSZ:
        return tiocgwinsz(real_tty, p);
    case TIOCSWINSZ:
        return tiocswinsz(real_tty, p);
    }

    ld = tty->ldisc;
    if (ld->ops->ioctl)
    {
        ret = ld->ops->ioctl(fd, cmd, args);
    }
    return ret;
}

#ifdef RT_USING_DFS_V2
static ssize_t tty_read(struct dfs_file *fd, void *buf, size_t count, off_t *pos)
#else
static ssize_t tty_read(struct dfs_file *fd, void *buf, size_t count)
#endif
{
    int ret = 0;
    struct tty_struct *tty = RT_NULL;
    struct tty_ldisc *ld = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);

    ld = tty->ldisc;
    if (ld && ld->ops->read)
    {
        ret = ld->ops->read(fd, buf, count);
    }
    return ret;
}

#ifdef RT_USING_DFS_V2
static ssize_t tty_write(struct dfs_file *fd, const void *buf, size_t count, off_t *pos)
#else
static ssize_t tty_write(struct dfs_file *fd, const void *buf, size_t count )
#endif
{
    int ret = 0;
    struct tty_struct *tty = RT_NULL;
    struct tty_ldisc *ld = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);

    ld = tty->ldisc;
    if (ld && ld->ops->write)
    {
        ret = ld->ops->write(fd, buf, count);
    }

    return ret;
}

static int tty_poll(struct dfs_file *fd, struct rt_pollreq *req)
{
    int ret = 0;
    struct tty_struct *tty = RT_NULL;
    struct tty_ldisc *ld = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);
    ld = tty->ldisc;
    if (ld->ops->poll)
    {
        ret = ld->ops->poll(fd, req);
    }
    return ret;
}

static const struct dfs_file_ops tty_fops =
{
    .open   = tty_open,
    .close  = tty_close,
    .ioctl  = tty_ioctl,
    .read   = tty_read,
    .write  = tty_write,
    .poll   = tty_poll,
};

const struct dfs_file_ops *tty_get_fops(void)
{
    return &tty_fops;
}

int tty_init(struct tty_struct *tty, int type, int subtype, struct rt_device *iodev)
{
    if (tty)
    {
        struct tty_node *node = NULL;

        node = rt_calloc(1, sizeof(struct tty_node));
        if (node)
        {
            tty->type = type;
            tty->subtype = subtype;
            tty->io_dev = iodev;

            tty->head = node;
            tty_initstack(tty->head);

            tty->pgrp = -1;
            tty->session = -1;
            tty->foreground = RT_NULL;

            rt_mutex_init(&tty->lock, "ttyLock", RT_IPC_FLAG_PRIO);
            rt_wqueue_init(&tty->wait_queue);
            rt_spin_lock_init(&tty->spinlock);

            tty_ldisc_init(tty);
            tty->init_termios = tty_std_termios;
            tty->init_flag = TTY_INIT_FLAG_REGED;
        }
    }

    return 0;
}
