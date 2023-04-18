#include <stddef.h>
#include <rtthread.h>
#include <tty.h>
#if defined(RT_USING_POSIX_DEVIO)
#include <termios.h>
#endif

#define DBG_TAG               "TTY_IOCTL"
#ifdef RT_TTY_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_TTY_DEBUG */
#include <rtdbg.h>

/*
 * Internal flag options for termios setting behavior
 */
#define TERMIOS_FLUSH   1
#define TERMIOS_WAIT    2
#define TERMIOS_TERMIO  4
#define TERMIOS_OLD 8

/**
 *  set_termios     -   set termios values for a tty
 *  @tty: terminal device
 *  @arg: user data
 *  @opt: option information
 *
 *  Helper function to prepare termios data and run necessary other
 *  functions before using tty_set_termios to do the actual changes.
 *
 *  Locking:
 *      Called functions take ldisc and termios_rwsem locks
 */

static int set_termios(struct tty_struct *tty, void *arg, int opt)
{
    struct termios old_termios;
    struct tty_ldisc *ld = RT_NULL;
    struct termios *new_termios = (struct termios *)arg;
    int level = 0;
    int retval = tty_check_change(tty);

    if (retval)
    {
        return retval;
    }

    rt_memcpy(&old_termios, &(tty->init_termios), sizeof(struct termios));
    level = rt_hw_interrupt_disable();
    tty->init_termios = *new_termios;
    rt_hw_interrupt_enable(level);
    ld = tty->ldisc;
    if (ld != NULL)
    {
        if (ld->ops->set_termios)
        {
            ld->ops->set_termios(tty, &old_termios);
        }
    }
    return 0;
}

int n_tty_ioctl_extend(struct tty_struct *tty, int cmd, void *args)
{
    int ret = 0;
    void *p = (void *)args;
    struct tty_struct *real_tty = RT_NULL;

    if (tty->type == TTY_DRIVER_TYPE_PTY && tty->subtype == PTY_TYPE_MASTER)
    {
        real_tty = tty->other_struct;
    }
    else
    {
        real_tty = tty;
    }

    switch(cmd)
    {
    case TCGETS:
    {
        struct termios *tio = (struct termios *)p;
        if (tio == RT_NULL)
        {
            return -RT_EINVAL;
        }

        rt_memcpy(tio, &real_tty->init_termios, sizeof(real_tty->init_termios));
        return ret;
    }
    case TCSETSF:
    {
        return set_termios(real_tty, p,  TERMIOS_FLUSH | TERMIOS_WAIT | TERMIOS_OLD);
    }
    case TCSETSW:
    {
        return set_termios(real_tty, p, TERMIOS_WAIT | TERMIOS_OLD);
    }
    case TCSETS:
    {
        return set_termios(real_tty, p, TERMIOS_OLD);
    }
    default:
        break;
    }
    return -ENOIOCTLCMD;
}
