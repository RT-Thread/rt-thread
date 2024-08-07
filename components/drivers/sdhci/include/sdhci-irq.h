#ifndef _SDHCI_IRQ_H
#define _SDHCI_IRQ_H

#include "sdhci_wait.h"
#include <stdint.h>
#include <stdbool.h>
#include <rtthread.h>
typedef unsigned long dma_addr_t;
typedef unsigned long phys_addr_t;
#define __le16 uint16_t
#define __le32 uint32_t
typedef unsigned long size_t;

#define SIZE_KB 1024
#define SIZE_MB (1024 * SIZE_KB)
#define SIZE_GB (1024 * SIZE_MB)

#define SIZE_ALIGN(size, align)         (((size) + (align) - 1) & ~((align) - 1))
#define SIZE_ALIGN_DOWN(size, align)    ((size) & ~((align) - 1))

#ifndef NULL
#define NULL (void*)0
#endif
#define gfp_t unsigned


enum irqreturn
{
    IRQ_NONE        = (0 << 0),
    IRQ_HANDLED     = (1 << 0),
    IRQ_WAKE_THREAD     = (1 << 1),
};
typedef enum irqreturn irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

#define IRQF_SHARED     0x00000080

#define local_irq_save(flags)     {flags = (unsigned long)rt_hw_interrupt_disable();}
#define local_irq_restore(flags)  rt_hw_interrupt_enable((rt_base_t)flags)

const void *free_irq(unsigned int irq, void *d);
int request_threaded_irq(unsigned int irq, irq_handler_t handler,
                         irq_handler_t thread_fn,
                         unsigned long irqflags, const char *name, void *dev_id);


#endif
