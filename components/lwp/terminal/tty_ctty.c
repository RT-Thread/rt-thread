/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-30     Shell        init ver.
 */
#define DBG_TAG "lwp.ctty"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define TTY_CONF_INCLUDE_CCHARS
#include "tty_config.h"
#include "tty_internal.h"
#include "terminal.h"

static int fops_open(struct dfs_file *file)
{
    return -EINVAL;
}

static rt_err_t ctty_readlink(struct rt_device *dev, char *buf, int len)
{
    int rc = -ENXIO;
    lwp_tty_t tp;
    rt_session_t sess;
    rt_processgroup_t pgrp;
    rt_lwp_t lwp;

    lwp = lwp_self();
    if (lwp)
    {
        pgrp = lwp->pgrp;
        if (pgrp)
        {
            sess = pgrp->session;
            if (sess)
            {
                tp = sess->ctty;
                if (tp)
                {
                    tty_lock(tp);

                    if (lwp->pgrp == pgrp && pgrp->session == sess && sess->ctty == tp)
                    {
                        rt_strncpy(buf, tp->parent.parent.name, len);
                        rc = RT_EOK;
                    }

                    tty_unlock(tp);
                }
            }
        }
    }

    return rc;
}

static struct dfs_file_ops ctty_file_ops = {
    .open = fops_open,
};

/* character device for tty */
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops tty_dev_ops = {
    /* IO directly through device is not allowed */
};
#else
#error Must enable RT_USING_DEVICE_OPS in Kconfig
#endif

rt_inline void device_setup(rt_device_t ctty)
{
    ctty->type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    ctty->ops = &tty_dev_ops;
#else
#error Must enable RT_USING_DEVICE_OPS in Kconfig
#endif
}

/* register device to DFS */
static int lwp_ctty_register(rt_device_t ctty)
{
    rt_err_t rc = -RT_ENOMEM;
    const char *tty_name = "tty";

    device_setup(ctty);
    rc = rt_device_register(ctty, tty_name, RT_DEVICE_FLAG_DYNAMIC);
    if (rc == RT_EOK)
    {
        ctty->readlink = &ctty_readlink;
        ctty->fops = &ctty_file_ops;
    }
    return rc;
}

static struct rt_device ctty;

static int lwp_ctty_init(void)
{
    return lwp_ctty_register(&ctty);
}
INIT_DEVICE_EXPORT(lwp_ctty_init);
