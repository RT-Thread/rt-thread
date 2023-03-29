/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-02-06     RT-Thread      first version
 */
#ifndef __RASPI4_H__
#define __RASPI4_H__

#include <rtthread.h>

//https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0.pdf

#define __REG32(x)  (*((volatile unsigned int *)(x)))
#define __REG16(x)  (*((volatile unsigned short *)(x)))

/* GIC IRQ MAX */
#define MAX_HANDLERS                (256)

/* base address */
#define PER_BASE                    (0xFE000000)

//gpio offset
#define GPIO_BASE_OFFSET            (0x00200000)


#define PL011_UART_BASE_OFFSET      (0x00201000)
//pl011 offset
#define PL011_UART0_BASE_OFFSET     (0x00201000)
#define PL011_UART2_BASE_OFFSET     (0x00201400)
#define PL011_UART3_BASE_OFFSET     (0x00201600)
#define PL011_UART4_BASE_OFFSET     (0x00201800)
#define PL011_UART5_BASE_OFFSET     (0x00201A00)

//pactl cs offset
#define PACTL_CS_OFFSET             (0x00204E00)

//aux offset
#define AUX_BASE_OFFSET             (0x00215000)

/* GPIO */
#define GPIO_BASE_ADDR              (PER_BASE + GPIO_BASE_OFFSET)
extern size_t gpio_base_addr;
#define GPIO_BASE                   (gpio_base_addr)
#define GPIO_IRQ_NUM                (3)   //40 pin mode
#define IRQ_GPIO0                   (96 + 49) //bank0 (0 to 27)
#define IRQ_GPIO1                   (96 + 50) //bank1 (28 to 45)
#define IRQ_GPIO2                   (96 + 51) //bank2 (46 to 57)
#define IRQ_GPIO3                   (96 + 52) //bank3

/* Timer (ARM side) */
#define ARM_TIMER_IRQ       (64)
extern size_t arm_timer_base;
#define ARM_TIMER_BASE      (PER_BASE + 0xB000)
#define ARM_TIMER_LOAD      HWREG32(arm_timer_base + 0x400)
#define ARM_TIMER_VALUE     HWREG32(arm_timer_base + 0x404)
#define ARM_TIMER_CTRL      HWREG32(arm_timer_base + 0x408)
#define ARM_TIMER_IRQCLR    HWREG32(arm_timer_base + 0x40C)
#define ARM_TIMER_RAWIRQ    HWREG32(arm_timer_base + 0x410)
#define ARM_TIMER_MASKIRQ   HWREG32(arm_timer_base + 0x414)
#define ARM_TIMER_RELOAD    HWREG32(arm_timer_base + 0x418)
#define ARM_TIMER_PREDIV    HWREG32(arm_timer_base + 0x41C)
#define ARM_TIMER_CNTR      HWREG32(arm_timer_base + 0x420)

/* UART PL011 */
#define UART_BASE                   (PER_BASE + PL011_UART_BASE_OFFSET)
//extern uint32_t uart_base_addr;
#define UART0_BASE                  (UART_BASE + 0x0)
#define UART2_BASE                  (UART_BASE + 0x400)
#define UART3_BASE                  (UART_BASE + 0x600)
#define UART4_BASE                  (UART_BASE + 0x800)
#define UART5_BASE                  (UART_BASE + 0xA00)
#define IRQ_AUX_UART                (96 + 29)
#define UART_REFERENCE_CLOCK        (48000000)

/* AUX */
//#define AUX_BASE_ADDR               (PER_BASE + AUX_BASE_OFFSET)
//extern uint32_t aux_addr;
//#define AUX_BASE                    (aux_addr + 0x0)

#define AUX_BASE                    (PER_BASE + AUX_BASE_OFFSET)
#define IRQ_PL011                   (96 + 57)

/* Peripheral IRQ OR-ing */
#define PACTL_CS_ADDR               (PER_BASE + PACTL_CS_OFFSET)
extern size_t     pactl_cs_base;
#define PACTL_CS                    HWREG32(pactl_cs_base)
typedef enum
{
    IRQ_SPI0 = 0x00000000,
    IRQ_SPI1 = 0x00000002,
    IRQ_SPI2 = 0x00000004,
    IRQ_SPI3 = 0x00000008,
    IRQ_SPI4 = 0x00000010,
    IRQ_SPI5 = 0x00000020,
    IRQ_SPI6 = 0x00000040,
    IRQ_I2C0 = 0x00000100,
    IRQ_I2C1 = 0x00000200,
    IRQ_I2C2 = 0x00000400,
    IRQ_I2C3 = 0x00000800,
    IRQ_I2C4 = 0x00001000,
    IRQ_I2C5 = 0x00002000,
    IRQ_I2C6 = 0x00004000,
    IRQ_I2C7 = 0x00008000,
    IRQ_UART5 = 0x00010000,
    IRQ_UART4 = 0x00020000,
    IRQ_UART3 = 0x00040000,
    IRQ_UART2 = 0x00080000,
    IRQ_UART0 = 0x00100000
} PACTL_CS_VAL;

// 0x40, 0x44, 0x48, 0x4c: Core 0~3 Timers interrupt control
#define CORE0_TIMER_IRQ_CTRL        HWREG32(0xFF800040)
#define TIMER_IRQ                   30
#define NON_SECURE_TIMER_IRQ        (1 << 1)

/* GIC */
#define INTC_BASE                   (0xff800000)
#define ARM_GIC_NR_IRQS             (512)
#define ARM_GIC_MAX_NR              (512)
#define GIC_V2_BASE                 (INTC_BASE + 0x00040000)
extern size_t gic_base_addr;
#define GIC_V2_DISTRIBUTOR_BASE     (gic_base_addr + 0x1000)
#define GIC_V2_CPU_INTERFACE_BASE   (gic_base_addr + 0x2000)
#define GIC_V2_HYPERVISOR_BASE      (gic_base_addr + 0x4000)
#define GIC_V2_VIRTUAL_CPU_BASE     (gic_base_addr + 0x6000)

#define GIC_PL400_DISTRIBUTOR_PPTR  GIC_V2_DISTRIBUTOR_BASE
#define GIC_PL400_CONTROLLER_PPTR   GIC_V2_CPU_INTERFACE_BASE

#define GIC_IRQ_START   0

#define GIC_ACK_INTID_MASK  0x000003ff


//watchdog
#define WDT_BASE        (PER_BASE + 0x00100000)
extern size_t         wdt_base_addr;
#define PM_RSTC         HWREG32(wdt_base_addr + 0x1c)
#define PM_RSTS         HWREG32(wdt_base_addr + 0x20)
#define PM_WDOG         HWREG32(wdt_base_addr + 0x24)

#define PM_PASSWORD                 (0x5A000000)
#define PM_WDOG_TIME_SET            (0x000fffff)
#define PM_RSTS_HADWRH_SET          (0x00000040)
#define PM_RSTC_WRCFG_FULL_RESET    (0x00000020)
#define PM_RSTC_WRCFG_CLR           (0xffffffcf)
#define PM_RSTC_RESET               (0x00000102)

//timer
#define ST_BASE_OFFSET     (0x003000)
#define STIMER_BASE  (PER_BASE  + ST_BASE_OFFSET)
extern size_t stimer_base_addr;
#define STIMER_CS    __REG32(stimer_base_addr + 0x0000)
#define STIMER_CLO   __REG32(stimer_base_addr + 0x0004)
#define STIMER_CHI   __REG32(stimer_base_addr + 0x0008)
#define STIMER_C0    __REG32(stimer_base_addr + 0x000C)
#define STIMER_C1    __REG32(stimer_base_addr + 0x0010)
#define STIMER_C2    __REG32(stimer_base_addr + 0x0014)
#define STIMER_C3    __REG32(stimer_base_addr + 0x0018)

#define DELAY_MICROS(micros)                            \
    do{                                                 \
        rt_uint32_t compare = STIMER_CLO + micros * 25; \
        while (STIMER_CLO < compare);                   \
    } while (0)

//External Mass Media Controller (SD Card)
#define MMC0_BASE_ADDR    (PER_BASE+0x300000)
extern size_t mmc0_base_addr;
#define MMC2_BASE_ADDR    (PER_BASE+0x340000)
extern size_t mmc2_base_addr;

//mac
#define MAC_REG                 (void *)(0xfd580000)
extern uint8_t *                mac_reg_base_addr;

#define ETH_IRQ                 (160+29)

#define SEND_DATA_NO_CACHE      (0x08200000)
extern uint8_t *                eth_send_no_cache;

#define RECV_DATA_NO_CACHE      (0x08400000)
extern uint8_t *                eth_recv_no_cache;

/* the basic constants and interfaces needed by gic */
rt_inline size_t platform_get_gic_dist_base(void)
{
    return GIC_PL400_DISTRIBUTOR_PPTR;
}

rt_inline size_t platform_get_gic_cpu_base(void)
{
    return GIC_PL400_CONTROLLER_PPTR;
}

#endif
