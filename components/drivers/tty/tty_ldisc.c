#include <tty.h>
#include <tty_ldisc.h>

#define DBG_TAG               "TTY_LDISC"
#ifdef RT_TTY_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_TTY_DEBUG */
#include <rtdbg.h>

extern struct tty_ldisc_ops n_tty_ops;
static struct tty_ldisc_ops *tty_ldiscs[NR_LDISCS] = {
    &n_tty_ops, /* N_TTY = 0 */
};

static struct tty_ldisc_ops *get_ldops(int disc)
{
    struct tty_ldisc_ops *ldops = RT_NULL;
    int level = 0;
    level = rt_hw_interrupt_disable();
    ldops = tty_ldiscs[disc];
    if (ldops)
    {
        ldops->refcount++;
    }
    rt_hw_interrupt_enable(level);
    return ldops;
}

static void put_ldops(struct tty_ldisc_ops *ldops)
{
    int level = 0;

    level = rt_hw_interrupt_disable();
    ldops->refcount--;
    rt_hw_interrupt_enable(level);
}

static struct tty_ldisc *tty_ldisc_get(struct tty_struct *tty, int disc)
{
    struct tty_ldisc *ld = RT_NULL;
    struct tty_ldisc_ops *ldops = RT_NULL;

    if (disc < N_TTY || disc >= NR_LDISCS)
    {
        return RT_NULL;
    }

    ldops = get_ldops(disc);
    if (ldops == RT_NULL)
    {
        LOG_E("tty ldisc get error\n");
        return RT_NULL;
    }

    ld = rt_malloc(sizeof(struct tty_ldisc));
    if (ld == RT_NULL)
    {
        ldops->refcount--;
        return RT_NULL;
    }

    ld->ops = ldops;
    ld->tty = tty;

    return ld;
}

/**
 *  tty_ldisc_put       -   release the ldisc
 *
 *  Complement of tty_ldisc_get().
 */
static void tty_ldisc_put(struct tty_ldisc *ld)
{
    if (ld)
    {
        put_ldops(ld->ops);
        rt_free(ld);
    }
}

/**
 *  tty_ldisc_close     -   close a line discipline
 *  @tty: tty we are opening the ldisc on
 *  @ld: discipline to close
 *
 *  A helper close method. Also a convenient debugging and check
 *  point.
 */
static void tty_ldisc_close(struct tty_struct *tty, struct tty_ldisc *ld)
{
    if (ld && ld->ops->close)
    {
        ld->ops->close(tty);
    }
}

/**
 *  tty_ldisc_kill  -   teardown ldisc
 *  @tty: tty being released
 *
 *  Perform final close of the ldisc and reset tty->ldisc
 */
void tty_ldisc_kill(struct tty_struct *tty)
{
    if (tty && tty->ldisc)
    {
        /*
        * Now kill off the ldisc
        */
        tty_ldisc_close(tty, tty->ldisc);
        tty_ldisc_put(tty->ldisc);
        /* Force an oops if we mess this up */
        tty->ldisc = NULL;
    }
}

int tty_register_ldisc(int disc, struct tty_ldisc_ops *new_ldisc)
{
    int ret = 0;
    int level = 0;

    if (disc < N_TTY || disc >= NR_LDISCS)
    {
        return -EINVAL;
    }

    level = rt_hw_interrupt_disable();
    tty_ldiscs[disc] = new_ldisc;
    new_ldisc->num = disc;
    new_ldisc->refcount = 0;
    rt_hw_interrupt_enable(level);

    return ret;
}

/**
 *  tty_ldisc_release       -   release line discipline
 *  @tty: tty being shut down (or one end of pty pair)
 *
 *  Called during the final close of a tty or a pty pair in order to shut
 *  down the line discpline layer. On exit, each tty's ldisc is NULL.
 */

void tty_ldisc_release(struct tty_struct *tty)
{
    int level = 0;
    struct tty_struct *o_tty = tty->other_struct;

    /*
     * Shutdown this line discipline. As this is the final close,
     * it does not race with the set_ldisc code path.
     */
    level = rt_hw_interrupt_disable();
    tty_ldisc_kill(tty);
    if (o_tty)
    {
        tty_ldisc_kill(o_tty);
    }
    rt_hw_interrupt_enable(level);
}

/**
 *  tty_ldisc_init      -   ldisc setup for new tty
 *  @tty: tty being allocated
 *
 *  Set up the line discipline objects for a newly allocated tty. Note that
 *  the tty structure is not completely set up when this call is made.
 */

void tty_ldisc_init(struct tty_struct *tty)
{
    if (tty)
    {
        tty->ldisc = tty_ldisc_get(tty, N_TTY);
    }
}
