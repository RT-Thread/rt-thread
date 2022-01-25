/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 * All rights reserved
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-04     Grissiom     add comment
 */

#ifndef __VMM_CONTEXT_H__
#define __VMM_CONTEXT_H__

#include <armv7.h> // for struct rt_hw_stack

#include "vmm.h"

void vmm_context_init(void *context_addr);
#ifdef RT_VMM_USING_DOMAIN
void vmm_context_init_domain(struct vmm_domain *domain);
#endif
void vmm_virq_pending(int irq);
void vmm_verify_guest_status(struct rt_hw_stack *sp);

void vmm_show_guest(void);
#endif

