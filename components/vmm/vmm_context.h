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

