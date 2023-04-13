/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     Jesven       the first version
 */

#ifndef  __BACKTRACE_H__
#define  __BACKTRACE_H__

struct bt_frame
{
    unsigned long fp;
    unsigned long pc;
};

void backtrace(unsigned long pc, unsigned long lr, unsigned long fp);
int rt_backtrace(void);

#endif  /*__BACKTRACE_H__*/
