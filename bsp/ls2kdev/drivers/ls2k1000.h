#ifndef _LS2K1000_H__
#define _LS2K1000_H__

#include <mips.h>
#include "interrupt.h"
#include <rthw.h>

#define APB_BASE         CKSEG1ADDR(0xbfe00000)

#define UART0_BASE_ADDR  (0xbfe00000)
#define UART0_OFF        (0x0)
#define UART0_BASE       CKSEG1ADDR(UART0_BASE_ADDR + UART0_OFF)

#define UARTx_BASE(x)    ((APB_BASE | (0x0 << 12) | (x << 8)))

#define LIOINTC0_BASE    CKSEG1ADDR(0x1fe11400)
#define CORE0_INTISR0    CKSEG1ADDR(0x1fe11040)

#define LIOINTC1_BASE    CKSEG1ADDR(0x1fe11440)
#define CORE0_INTISR1    CKSEG1ADDR(0x1fe11048)

#define GPIO_BASE        (0xFFFFFFFFBFE10500)
#define PLL_SYS_BASE     (0xFFFFFFFFBFE10480)
#define RTC_BASE         (0xFFFFFFFFBFE07820)

#define GEN_CONFIG0_REG  (0xFFFFFFFFBfe10420)


/*
 * General PM Configuration Register
 */
#define PMCON_BASE          (APB_BASE | (0x7 << 12))

/*
 * Power Management1 Configuration Registers
 */
#define PM1_BASE            (PMCON_BASE + 0x0C)
#define PM1_STS             HWREG32(PM1_BASE)
#define PM1_EN              HWREG32(PM1_BASE + 0x04)
#define PM1_CNT             HWREG32(PM1_BASE + 0x08)

/*
 * Watch Dog Configuration Registers
 */
#define WDT_BASE            (PMCON_BASE + 0x30)
#define WDT_EN              HWREG32(WDT_BASE)
#define WDT_SET             HWREG32(WDT_BASE + 0x04)
#define WDT_TIMER           HWREG32(WDT_BASE + 0x08)

void rt_hw_timer_handler(void);
void rt_hw_uart_init(void);

#endif

