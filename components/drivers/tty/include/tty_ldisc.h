/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021.12.07     linzhenxing      first version
 */
#ifndef __TTY_LDISC_
#define __TTY_LDISC_
#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <tty.h>
#if defined(RT_USING_POSIX_TERMIOS)
#include <termios.h>
#endif
struct tty_struct;

struct tty_ldisc_ops
{
    char    *name;
    int num;

    int (*open)     (struct dfs_file *fd);
    int (*close)    (struct tty_struct *tty);
    int (*ioctl)    (struct dfs_file *fd, int cmd, void *args);
    int (*read)     (struct dfs_file *fd, void *buf, size_t count);
    int (*write)    (struct dfs_file *fd, const void *buf, size_t count);
    int (*flush)    (struct dfs_file *fd);
    int (*lseek)    (struct dfs_file *fd, off_t offset);
    int (*getdents) (struct dfs_file *fd, struct dirent *dirp, uint32_t count);

    int (*poll)     (struct dfs_file *fd, struct rt_pollreq *req);
    void (*set_termios) (struct tty_struct *tty, struct termios *old);
    int (*receive_buf) (struct tty_struct *tty,char *cp, int count);

    int refcount;
};

struct tty_ldisc
{
    struct tty_ldisc_ops *ops;
    struct tty_struct *tty;
};

#define TTY_LDISC_MAGIC 0x5403

int tty_register_ldisc(int disc, struct tty_ldisc_ops *new_ldisc);
void tty_ldisc_kill(struct tty_struct *tty);
void tty_ldisc_init(struct tty_struct *tty);
void tty_ldisc_release(struct tty_struct *tty);
void n_tty_init(void);

#endif // __TTY_LDISC_
