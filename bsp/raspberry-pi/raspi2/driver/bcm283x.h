#ifndef BCM283X_H__
#define BCM283X_H__

#include <rthw.h>

#define PER_BASE            (0x3F000000)
#define PER_BASE_40000000   (0x40000000)

/*
 *  GPIO
 */
#define GPIO_BASE       (PER_BASE + 0x200000)
#define GPIO_GPFSEL0    HWREG32(GPIO_BASE + 0x00)  /* GPIO Function Select 0 32bit R/W */
#define GPIO_GPFSEL1    HWREG32(GPIO_BASE + 0x04)  /* GPIO Function Select 1 32bit R/W */
#define GPIO_GPFSEL2    HWREG32(GPIO_BASE + 0x08)  /* GPIO Function Select 2 32bit R/W */
#define GPIO_GPFSEL4    HWREG32(GPIO_BASE + 0x10)  /* GPIO Function Select 4 32bit R/W */
#define GPIO_GPSET0     HWREG32(GPIO_BASE + 0x1C)
#define GPIO_GPCLR0     HWREG32(GPIO_BASE + 0x28)
#define GPIO_GPPUD      HWREG32(GPIO_BASE + 0x94)  /* GPIO Pin Pull-up/down Enable */
#define GPIO_GPPUDCLK0  HWREG32(GPIO_BASE + 0x98)  /* GPIO Pin Pull-up/down Enable Clock 0 */
#define GPIO_GPPUDCLK1  HWREG32(GPIO_BASE + 0x9C)  /* GPIO Pin Pull-up/down Enable Clock 1 */

/*
 *  Interrupt Controler
 */
#define IRQ_BASE            (PER_BASE + 0xB200)
#define IRQ_PEND_BASIC      HWREG32(IRQ_BASE + 0x00)
#define IRQ_PEND1           HWREG32(IRQ_BASE + 0x04)
#define IRQ_PEND2           HWREG32(IRQ_BASE + 0x08)
#define IRQ_FIQ_CONTROL     HWREG32(IRQ_BASE + 0x0C)
#define IRQ_ENABLE1         HWREG32(IRQ_BASE + 0x10)
#define IRQ_ENABLE2         HWREG32(IRQ_BASE + 0x14)
#define IRQ_ENABLE_BASIC    HWREG32(IRQ_BASE + 0x18)
#define IRQ_DISABLE1        HWREG32(IRQ_BASE + 0x1C)
#define IRQ_DISABLE2        HWREG32(IRQ_BASE + 0x20)
#define IRQ_DISABLE_BASIC   HWREG32(IRQ_BASE + 0x24)

/*
 *  System Timer
 */
#define STIMER_BASE         (PER_BASE  + 0x3000)
#define STIMER_CS           HWREG32(STIMER_BASE + 0x00)
#define STIMER_CLO          HWREG32(STIMER_BASE + 0x04)
#define STIMER_CHI          HWREG32(STIMER_BASE + 0x08)
#define STIMER_C0           HWREG32(STIMER_BASE + 0x0C)
#define STIMER_C1           HWREG32(STIMER_BASE + 0x10)
#define STIMER_C2           HWREG32(STIMER_BASE + 0x14)
#define STIMER_C3           HWREG32(STIMER_BASE + 0x18)

/*
 * ARM Timer
 */
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

/*
 *  Core Timer
 */
#define CTIMER_CTL          HWREG32(PER_BASE_40000000 + 0x00)  /* Control register */
#define CTIMER_PRE          HWREG32(PER_BASE_40000000 + 0x08)  /* Core timer prescaler */
#define CTIMER_LS32B        HWREG32(PER_BASE_40000000 + 0x1C)  /* Core timer access LS 32 bits */
#define CTIMER_MS32B        HWREG32(PER_BASE_40000000 + 0x20)  /* Core timer access MS 32 bits */

/*
 *  ARM Core Timer
 */
#define C0TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x40)  /* Core0 timers Interrupt control */
#define C1TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x44)  /* Core1 timers Interrupt control */
#define C2TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x48)  /* Core2 timers Interrupt control */
#define C3TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x4C)  /* Core3 timers Interrupt control */

/*
 *  ARM Core Mailbox interrupt
 */
#define C0MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x50)  /* Core0 Mailboxes Interrupt control */
#define C1MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x54)  /* Core1 Mailboxes Interrupt control */
#define C2MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x58)  /* Core2 Mailboxes Interrupt control */
#define C3MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x5C)  /* Core3 Mailboxes Interrupt control */

/*
 *  ARM Core IRQ/FIQ status
 */
#define C0_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x60)  /* Core0 IRQ Source */
#define C1_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x64)  /* Core1 IRQ Source */
#define C2_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x68)  /* Core2 IRQ Source */
#define C3_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x6C)  /* Core3 IRQ Source */
#define C0_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x70)  /* Core0 FIQ Source */
#define C1_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x74)  /* Core1 FIQ Source */
#define C2_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x78)  /* Core2 FIQ Source */
#define C3_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x7C)  /* Core3 FIQ Source */

#define IRQ_ARM_TIMER           0
#define IRQ_ARM_MAILBOX         1
#define IRQ_ARM_DB0             2
#define IRQ_ARM_DB1             3
#define IRQ_ARM_GPU0_HALT       4
#define IRQ_ARM_GPU1_HALT       5
#define IRQ_ARM_ILLEGAL_ACC1    6
#define IRQ_ARM_ILLEGAL_ACC0    7

#define IRQ_AUX                 29
#define IRQ_IIC_SPI_SLV         43
#define IRQ_PWA0                45
#define IRQ_PWA1                46
#define IRQ_SMI                 48
#define IRQ_GPIO0               49
#define IRQ_GPIO1               50
#define IRQ_GPIO2               51
#define IRQ_GPIO3               52
#define IRQ_IIC                 53
#define IRQ_SPI                 54
#define IRQ_PCM                 55
#define IRQ_UART                57

#endif

