/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021.12.07     linzhenxing      first version
 */
#include <dfs_file.h>
#include <dfs_fs.h>
#include <lwp.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <tty.h>
#include <tty_ldisc.h>

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
    node->next = node;
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

rt_inline int tty_sigismember(lwp_sigset_t *set, int _sig)
{
    unsigned long sig = _sig - 1;

    if (_LWP_NSIG_WORDS == 1)
    {
        return 1 & (set->sig[0] >> sig);
    }
    else
    {
        return 1 & (set->sig[sig / _LWP_NSIG_BPW] >> (sig % _LWP_NSIG_BPW));
    }
}

static int is_ignored(int sig)
{
    return (tty_sigismember(&current->signal_mask, sig) ||
        current->signal_handler[sig-1] == SIG_IGN);
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
    struct rt_lwp *lwp = tty->foreground;
    int ret = 0;
    int level = 0;

    level = rt_hw_interrupt_disable();
    if (current == RT_NULL)
    {
        rt_hw_interrupt_enable(level);
        return 0;
    }

    if (current->tty != tty)
    {
        rt_hw_interrupt_enable(level);
        return 0;
    }

    pgrp = current->__pgrp;
    tty_pgrp = tty->pgrp;

    if (tty_pgrp && (pgrp != tty->pgrp))
    {
        if (is_ignored(sig))
        {
            if (sig == SIGTTIN)
            {
                ret = -EIO;
            }
        }
        else
        {
            if (lwp)
            {
                lwp_kill(lwp_to_pid(lwp), sig);
            }
        }
    }
    rt_hw_interrupt_enable(level);

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

static int tty_ioctl(struct dfs_file *fd, int cmd, void *args)
{
    int ret = 0;
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
    }

    ld = tty->ldisc;
    if (ld->ops->ioctl)
    {
        ret = ld->ops->ioctl(fd, cmd, args);
    }
    return ret;
}

static int tty_read(struct dfs_file *fd, void *buf, size_t count)
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

static int tty_write(struct dfs_file *fd, const void *buf, size_t count)
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
    tty_open,
    tty_close,
    tty_ioctl,
    tty_read,
    tty_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    tty_poll,
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

            tty_ldisc_init(tty);
            tty->init_termios = tty_std_termios;
            tty->init_flag = TTY_INIT_FLAG_REGED;
        }
    }

    return 0;
}
