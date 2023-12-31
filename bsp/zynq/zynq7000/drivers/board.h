#ifndef __BOARD_H__
#define __BOARD_H__

#if defined(__CC_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void*)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
extern int __bss_end;
#define HEAP_BEGIN      ((void*)&__bss_end)
#endif

#define HEAP_END        (void*)(0x20100000-1)
#define GIC_IRQ_START  0
#define MAX_HANDLERS 96
#define GIC_ACK_INTID_MASK 0x000003ff
#define ARM_GIC_MAX_NR 1
#define ARM_GIC_NR_IRQS MAX_HANDLERS

#include "rtthread.h"
#include "xparameters.h"

#define Zynq7000_GIC_CPU_BASE XPAR_PS7_SCUGIC_0_BASEADDR
#define Zynq7000_GIC_DIST_BASE XPAR_PS7_SCUGIC_0_DIST_BASEADDR

rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return Zynq7000_GIC_DIST_BASE;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return Zynq7000_GIC_CPU_BASE;
}

#define __REG32(x) (*((volatile unsigned int *)(x)))
#define __REG16(x) (*((volatile unsigned short *)(x)))

void rt_hw_board_init();

int rt_hw_uart_init(void);

#endif
