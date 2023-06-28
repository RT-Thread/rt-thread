/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021.12.07     linzhenxing      first version
 */
#ifndef __TTY_H__
#define __TTY_H__
#include <rthw.h>
#include <rtthread.h>
#include <tty_ldisc.h>
#ifdef RT_USING_SMART
#include <lwp.h>
#endif
#if defined(RT_USING_POSIX_TERMIOS)
#include <poll.h>
#include <termios.h>
#endif

#ifndef ENOIOCTLCMD
#define ENOIOCTLCMD     (515) /* No ioctl command */
#endif

#define current lwp_self()
#define __DISABLED_CHAR '\0'

struct tty_node
{
    struct rt_lwp *lwp;
    struct tty_node *next;
};

void tty_initstack(struct tty_node *node);
int tty_push(struct tty_node **head, struct rt_lwp *lwp);
struct rt_lwp *tty_pop(struct tty_node **head, struct rt_lwp *target_lwp);
/*
 * When a break, frame error, or parity error happens, these codes are
 * stuffed into the flags buffer.
 */
#define TTY_NORMAL  0
#define TTY_BREAK   1
#define TTY_FRAME   2
#define TTY_PARITY  3
#define TTY_OVERRUN 4

#define INTR_CHAR(tty) ((tty)->init_termios.c_cc[VINTR])
#define QUIT_CHAR(tty) ((tty)->init_termios.c_cc[VQUIT])
#define ERASE_CHAR(tty) ((tty)->init_termios.c_cc[VERASE])
#define KILL_CHAR(tty) ((tty)->init_termios.c_cc[VKILL])
#define EOF_CHAR(tty) ((tty)->init_termios.c_cc[VEOF])
#define TIME_CHAR(tty) ((tty)->init_termios.c_cc[VTIME])
#define MIN_CHAR(tty) ((tty)->init_termios.c_cc[VMIN])
#define SWTC_CHAR(tty) ((tty)->init_termios.c_cc[VSWTC])
#define START_CHAR(tty) ((tty)->init_termios.c_cc[VSTART])
#define STOP_CHAR(tty) ((tty)->init_termios.c_cc[VSTOP])
#define SUSP_CHAR(tty) ((tty)->init_termios.c_cc[VSUSP])
#define EOL_CHAR(tty) ((tty)->init_termios.c_cc[VEOL])
#define REPRINT_CHAR(tty) ((tty)->init_termios.c_cc[VREPRINT])
#define DISCARD_CHAR(tty) ((tty)->init_termios.c_cc[VDISCARD])
#define WERASE_CHAR(tty) ((tty)->init_termios.c_cc[VWERASE])
#define LNEXT_CHAR(tty) ((tty)->init_termios.c_cc[VLNEXT])
#define EOL2_CHAR(tty) ((tty)->init_termios.c_cc[VEOL2])

#define _I_FLAG(tty,f)  ((tty)->init_termios.c_iflag & (f))
#define _O_FLAG(tty,f)  ((tty)->init_termios.c_oflag & (f))
#define _C_FLAG(tty,f)  ((tty)->init_termios.c_cflag & (f))
#define _L_FLAG(tty,f)  ((tty)->init_termios.c_lflag & (f))

#define I_IGNBRK(tty)   _I_FLAG((tty),IGNBRK)
#define I_BRKINT(tty)   _I_FLAG((tty),BRKINT)
#define I_IGNPAR(tty)   _I_FLAG((tty),IGNPAR)
#define I_PARMRK(tty)   _I_FLAG((tty),PARMRK)
#define I_INPCK(tty)    _I_FLAG((tty),INPCK)
#define I_ISTRIP(tty)   _I_FLAG((tty),ISTRIP)
#define I_INLCR(tty)    _I_FLAG((tty),INLCR)
#define I_IGNCR(tty)    _I_FLAG((tty),IGNCR)
#define I_ICRNL(tty)    _I_FLAG((tty),ICRNL)
#define I_IUCLC(tty)    _I_FLAG((tty),IUCLC)
#define I_IXON(tty)     _I_FLAG((tty),IXON)
#define I_IXANY(tty)    _I_FLAG((tty),IXANY)
#define I_IXOFF(tty)    _I_FLAG((tty),IXOFF)
#define I_IMAXBEL(tty)  _I_FLAG((tty),IMAXBEL)
#define I_IUTF8(tty)    _I_FLAG((tty), IUTF8)

#define O_OPOST(tty)    _O_FLAG((tty),OPOST)
#define O_OLCUC(tty)    _O_FLAG((tty),OLCUC)
#define O_ONLCR(tty)    _O_FLAG((tty),ONLCR)
#define O_OCRNL(tty)    _O_FLAG((tty),OCRNL)
#define O_ONOCR(tty)    _O_FLAG((tty),ONOCR)
#define O_ONLRET(tty)   _O_FLAG((tty),ONLRET)
#define O_OFILL(tty)    _O_FLAG((tty),OFILL)
#define O_OFDEL(tty)    _O_FLAG((tty),OFDEL)
#define O_NLDLY(tty)    _O_FLAG((tty),NLDLY)
#define O_CRDLY(tty)    _O_FLAG((tty),CRDLY)
#define O_TABDLY(tty)   _O_FLAG((tty),TABDLY)
#define O_BSDLY(tty)    _O_FLAG((tty),BSDLY)
#define O_VTDLY(tty)    _O_FLAG((tty),VTDLY)
#define O_FFDLY(tty)    _O_FLAG((tty),FFDLY)

#define C_BAUD(tty)     _C_FLAG((tty),CBAUD)
#define C_CSIZE(tty)    _C_FLAG((tty),CSIZE)
#define C_CSTOPB(tty)   _C_FLAG((tty),CSTOPB)
#define C_CREAD(tty)    _C_FLAG((tty),CREAD)
#define C_PARENB(tty)   _C_FLAG((tty),PARENB)
#define C_PARODD(tty)   _C_FLAG((tty),PARODD)
#define C_HUPCL(tty)    _C_FLAG((tty),HUPCL)
#define C_CLOCAL(tty)   _C_FLAG((tty),CLOCAL)
#define C_CIBAUD(tty)   _C_FLAG((tty),CIBAUD)
#define C_CRTSCTS(tty)  _C_FLAG((tty),CRTSCTS)

#define L_ISIG(tty)     _L_FLAG((tty),ISIG)
#define L_ICANON(tty)   _L_FLAG((tty),ICANON)
#define L_XCASE(tty)    _L_FLAG((tty),XCASE)
#define L_ECHO(tty)     _L_FLAG((tty),ECHO)
#define L_ECHOE(tty)    _L_FLAG((tty),ECHOE)
#define L_ECHOK(tty)    _L_FLAG((tty),ECHOK)
#define L_ECHONL(tty)   _L_FLAG((tty),ECHONL)
#define L_NOFLSH(tty)   _L_FLAG((tty),NOFLSH)
#define L_TOSTOP(tty)   _L_FLAG((tty),TOSTOP)
#define L_ECHOCTL(tty)  _L_FLAG((tty),ECHOCTL)
#define L_ECHOPRT(tty)  _L_FLAG((tty),ECHOPRT)
#define L_ECHOKE(tty)   _L_FLAG((tty),ECHOKE)
#define L_FLUSHO(tty)   _L_FLAG((tty),FLUSHO)
#define L_PENDIN(tty)   _L_FLAG((tty),PENDIN)
#define L_IEXTEN(tty)   _L_FLAG((tty),IEXTEN)
#define L_EXTPROC(tty)  _L_FLAG((tty), EXTPROC)

/*
 * Where all of the state associated with a tty is kept while the tty
 * is open.  Since the termios state should be kept even if the tty
 * has been closed --- for things like the baud rate, etc --- it is
 * not stored here, but rather a pointer to the real state is stored
 * here.  Possible the winsize structure should have the same
 * treatment, but (1) the default 80x24 is usually right and (2) it's
 * most often used by a windowing system, which will set the correct
 * size each time the window is created or resized anyway.
 *                      - TYT, 9/14/92
 */
struct tty_struct
{
    struct rt_device parent;
    int type;
    int subtype;
    int init_flag;
    int index;  //for pty
    int pts_lock;   //for pty

    struct tty_struct *other_struct; //for pty

    struct termios init_termios;
    struct winsize winsize;
    struct rt_mutex lock;
    pid_t pgrp;
    pid_t session;
    struct rt_lwp *foreground;
    struct tty_node *head;

    struct tty_ldisc *ldisc;
    void *disc_data;
    struct rt_device *io_dev;

    struct rt_wqueue wait_queue;

#define RT_TTY_BUF 1024
    rt_list_t tty_drivers;
};

enum
{
    TTY_INIT_FLAG_NONE = 0,
    TTY_INIT_FLAG_ALLOCED,
    TTY_INIT_FLAG_REGED,
    TTY_INIT_FLAG_INITED,
};

#define TTY_DRIVER_TYPE_SYSTEM      0x0001
#define TTY_DRIVER_TYPE_CONSOLE     0x0002
#define TTY_DRIVER_TYPE_SERIAL      0x0003
#define TTY_DRIVER_TYPE_PTY         0x0004
#define TTY_DRIVER_TYPE_SCC         0x0005  /* scc driver */
#define TTY_DRIVER_TYPE_SYSCONS     0x0006

/* tty magic number */
#define TTY_MAGIC       0x5401

/*
 * These bits are used in the flags field of the tty structure.
 *
 * So that interrupts won't be able to mess up the queues,
 * copy_to_cooked must be atomic with respect to itself, as must
 * tty->write.  Thus, you must use the inline functions set_bit() and
 * clear_bit() to make things atomic.
 */
#define TTY_THROTTLED 0
#define TTY_IO_ERROR 1
#define TTY_OTHER_CLOSED 2
#define TTY_EXCLUSIVE 3
#define TTY_DEBUG 4
#define TTY_DO_WRITE_WAKEUP 5
#define TTY_PUSH 6
#define TTY_CLOSING 7
#define TTY_DONT_FLIP 8
#define TTY_HW_COOK_OUT 14
#define TTY_HW_COOK_IN 15
#define TTY_PTY_LOCK 16
#define TTY_NO_WRITE_SPLIT 17

#define NR_LDISCS       30

/* line disciplines */
#define N_TTY       0
#define N_SLIP      1
#define N_MOUSE     2
#define N_PPP       3
#define N_STRIP     4
#define N_AX25      5
#define N_X25       6   /* X.25 async */
#define N_6PACK     7
#define N_MASC      8   /* Reserved for Mobitex module <kaz@cafe.net> */
#define N_R3964     9   /* Reserved for Simatic R3964 module */
#define N_PROFIBUS_FDL  10  /* Reserved for Profibus */
#define N_IRDA      11  /* Linux IrDa - http://irda.sourceforge.net/ */
#define N_SMSBLOCK  12  /* SMS block mode - for talking to GSM data */
                /* cards about SMS messages */
#define N_HDLC      13  /* synchronous HDLC */
#define N_SYNC_PPP  14  /* synchronous PPP */
#define N_HCI       15  /* Bluetooth HCI UART */
#define N_GIGASET_M101  16  /* Siemens Gigaset M101 serial DECT adapter */
#define N_SLCAN     17  /* Serial / USB serial CAN Adaptors */
#define N_PPS       18  /* Pulse per Second */
#define N_V253      19  /* Codec control over voice modem */
#define N_CAIF      20      /* CAIF protocol for talking to modems */
#define N_GSM0710   21  /* GSM 0710 Mux */
#define N_TI_WL     22  /* for TI's WL BT, FM, GPS combo chips */
#define N_TRACESINK 23  /* Trace data routing for MIPI P1149.7 */
#define N_TRACEROUTER   24  /* Trace data routing for MIPI P1149.7 */
#define N_NCI       25  /* NFC NCI UART */

/* Used for packet mode */
#define TIOCPKT_DATA         0
#define TIOCPKT_FLUSHREAD    1
#define TIOCPKT_FLUSHWRITE   2
#define TIOCPKT_STOP         4
#define TIOCPKT_START        8
#define TIOCPKT_NOSTOP      16
#define TIOCPKT_DOSTOP      32

/* pty subtypes */
#define PTY_TYPE_MASTER         0x0001
#define PTY_TYPE_SLAVE          0x0002

/* serial subtype definitions */
#define SERIAL_TYPE_NORMAL  1

#define max(a, b) ({\
        typeof(a) _a = a;\
        typeof(b) _b = b;\
        _a > _b ? _a : _b; })

#define min(a, b) ({\
        typeof(a) _a = a;\
        typeof(b) _b = b;\
        _a < _b ? _a : _b; })

void mutex_lock(rt_mutex_t mutex);
void mutex_unlock(rt_mutex_t mutex);
int __tty_check_change(struct tty_struct *tty, int sig);
int tty_check_change(struct tty_struct *tty);

rt_inline struct rt_wqueue *wait_queue_get(struct rt_lwp *lwp, struct tty_struct *tty)
{
    if (lwp == RT_NULL)
    {
        return &tty->wait_queue;
    }
    return &lwp->wait_queue;
}

rt_inline struct rt_wqueue *wait_queue_current_get(struct rt_lwp *lwp, struct tty_struct *tty)
{
    return wait_queue_get(lwp, tty);
}

rt_inline void tty_wakeup_check(struct tty_struct *tty)
{
    struct rt_wqueue *wq = NULL;

    wq = wait_queue_current_get(tty->foreground, tty);
    rt_wqueue_wakeup(wq, (void*)POLLIN);
}

int tty_init(struct tty_struct *tty, int type, int subtype, struct rt_device *iodev);
const struct dfs_file_ops *tty_get_fops(void);

int n_tty_ioctl_extend(struct tty_struct *tty, int cmd, void *arg);

void console_ldata_init(struct tty_struct *tty);
int n_tty_receive_buf(struct tty_struct *tty, char *cp, int count);

#endif /*__TTY_H__*/
