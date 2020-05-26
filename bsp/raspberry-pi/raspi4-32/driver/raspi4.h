#ifndef __RASPI4_H__
#define __RASPI4_H__
//https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0.pdf

#define __REG32(x)  (*((volatile unsigned int *)(x)))
#define __REG16(x)  (*((volatile unsigned short *)(x)))

/* GIC IRQ MAX */
#define MAX_HANDLERS                (256)

/* base address */
#define PER_BASE                    (0xFE000000)

/* GPIO */
#define GPIO_BASE                   (PER_BASE + 0x00200000)

/* Timer (ARM side) */
#define ARM_TIMER_IRQ       (64)
#define ARM_TIMER_BASE      (PER_BASE + 0xB000)
#define ARM_TIMER_LOAD      HWREG32(ARM_TIMER_BASE + 0x400)
#define ARM_TIMER_VALUE     HWREG32(ARM_TIMER_BASE + 0x404)
#define ARM_TIMER_CTRL      HWREG32(ARM_TIMER_BASE + 0x408)
#define ARM_TIMER_IRQCLR    HWREG32(ARM_TIMER_BASE + 0x40C)
#define ARM_TIMER_RAWIRQ    HWREG32(ARM_TIMER_BASE + 0x410)
#define ARM_TIMER_MASKIRQ   HWREG32(ARM_TIMER_BASE + 0x414)
#define ARM_TIMER_RELOAD    HWREG32(ARM_TIMER_BASE + 0x418)
#define ARM_TIMER_PREDIV    HWREG32(ARM_TIMER_BASE + 0x41C)
#define ARM_TIMER_CNTR      HWREG32(ARM_TIMER_BASE + 0x420)

/* UART PL011 */
#define UART0_BASE                  (PER_BASE + 0x00201000)
#define PL011_BASE                  UART0_BASE
#define IRQ_PL011                   (96 + 57)
#define UART_REFERENCE_CLOCK        (48000000)

// 0x40, 0x44, 0x48, 0x4c: Core 0~3 Timers interrupt control
#define CORE0_TIMER_IRQ_CTRL        HWREG32(0xFF800040)
#define TIMER_IRQ                   30
#define NON_SECURE_TIMER_IRQ        (1 << 1)

/* GIC */
#define INTC_BASE                   (0xff800000)
#define ARM_GIC_NR_IRQS             (512)
#define ARM_GIC_MAX_NR              (512)
#define GIC_V2_DISTRIBUTOR_BASE     (INTC_BASE + 0x00041000)
#define GIC_V2_CPU_INTERFACE_BASE   (INTC_BASE + 0x00042000)
#define GIC_V2_HYPERVISOR_BASE      (INTC_BASE + 0x00044000)
#define GIC_V2_VIRTUAL_CPU_BASE     (INTC_BASE + 0x00046000)

#define GIC_PL400_DISTRIBUTOR_PPTR  GIC_V2_DISTRIBUTOR_BASE
#define GIC_PL400_CONTROLLER_PPTR   GIC_V2_CPU_INTERFACE_BASE

#define GIC_IRQ_START   0

#define GIC_ACK_INTID_MASK  0x000003ff

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GIC_PL400_DISTRIBUTOR_PPTR;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return GIC_PL400_CONTROLLER_PPTR;
}

static inline  void __DSB(void)
{
    __asm__ volatile ("dsb 0xF":::"memory");
}

#endif
