/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-12     Bernard      The first version
 */

#ifndef SIGNAL_H__
#define SIGNAL_H__

#include <libc/libc_signal.h>

#define SIG_DFL ((_sig_func_ptr)0)  /* Default action */
#define SIG_IGN ((_sig_func_ptr)1)  /* Ignore action */
#define SIG_ERR ((_sig_func_ptr)-1) /* Error return */

#endif
