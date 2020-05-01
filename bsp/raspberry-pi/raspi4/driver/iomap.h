#ifndef __RASPI4_H__
#define __RASPI4_H__

//gpio
#define GPIO_BASE (0xFE000000 + 0x00200000)

//uart
#define UART0_BASE                  (0xFE000000 + 0x00201000)
#define PL011_BASE                  UART0_BASE
#define IRQ_PL011                   (121 + 32)
#define UART_REFERENCE_CLOCK        (48000000)

// 0x40, 0x44, 0x48, 0x4c: Core 0~3 Timers interrupt control
#define CORE0_TIMER_IRQ_CTRL    HWREG32(0xFF800040)
#define TIMER_IRQ               30
#define NON_SECURE_TIMER_IRQ    (1 << 1)

//gic max
#define ARM_GIC_NR_IRQS             (512)
#define INTC_BASE                   (0xff800000)
#define GIC_V2_DISTRIBUTOR_BASE     (INTC_BASE + 0x00041000)
#define GIC_V2_CPU_INTERFACE_BASE   (INTC_BASE + 0x00042000)
#define GIC_V2_HYPERVISOR_BASE      (INTC_BASE + 0x00044000)
#define GIC_V2_VIRTUAL_CPU_BASE     (INTC_BASE + 0x00046000)

#define GIC_PL400_DISTRIBUTOR_PPTR  GIC_V2_DISTRIBUTOR_BASE
#define GIC_PL400_CONTROLLER_PPTR   GIC_V2_CPU_INTERFACE_BASE

#endif
