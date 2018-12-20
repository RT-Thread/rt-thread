/*
 *  VMM startup file.
 *
 * COPYRIGHT (C) 2013-2014, Real-Thread Information Technology Ltd
 * All rights reserved
 * 
 * SPDX-License-Identifier: Apache-2.0
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
