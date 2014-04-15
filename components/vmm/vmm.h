/*
 *  VMM startup file.
 *
 * COPYRIGHT (C) 2013, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
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
 * 2013-06-15     Bernard      the first verion
 */

#ifndef __VMM_H__
#define __VMM_H__

#ifndef __ASSEMBLY__
#include <stddef.h> // for size_t
#endif

#define VMM_VERIFY_GUEST

#include <rtt_api.h>

#ifndef __ASSEMBLY__

void vmm_iomap_init(struct vmm_iomap *iomap);
unsigned long vmm_find_iomap(const char *name);
unsigned long vmm_find_iomap_by_pa(unsigned long pa);

void vmm_vector_init(void);

#ifndef RT_USING_LOGTRACE
/* If the rshell is run, we could not rt_kprintf in some situation because
 * write to a vbus channel *Would BLOCK*. So we cannot use it in interrupt
 * context, we cannot use it within the context of idle(vmm). */
#define vmm_debug(fmt, ...)
#define vmm_verbose(fmt, ...)
#define vmm_info(fmt, ...)
#else // have RT_USING_LOGTRACE
#define vmm_debug(fmt, ...)   log_trace(LOG_TRACE_DEBUG  "[vmm]"fmt, ##__VA_ARGS__)
#define vmm_verbose(fmt, ...) log_trace(LOG_TRACE_VERBOSE"[vmm]"fmt, ##__VA_ARGS__)
#define vmm_info(fmt, ...)    log_trace(LOG_TRACE_INFO   "[vmm]"fmt, ##__VA_ARGS__)
#endif // RT_USING_LOGTRACE
#endif

#define ARRAY_SIZE(ar)     (sizeof(ar)/sizeof(ar[0]))

#endif
