/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-7-16      Peng Fan     Just put the file here, should be implemented in
 *                             future
 */

#include <rtthread.h>
#include <sep6200.h>

#define PLL_CFG(_f, _r) {.f = _f, .r = _r} /*f(frequency, MHz); r(config register value)*/
#define MHz	1000000UL
/*
*SEP0611_CLOCK
*├── APLL
*│   └── CPU
*├── DPLL
*│   └── DDR
*└── MPLL
*    └── BUS1
*        ├── BUS2
*        │   ├── DMAC1
*        │   ├── ESRAM
*        │   ├── LCDC
*        │   ├── NAND
*        │   ├── NOR
*        │   ├── SDIO1
*        │   ├── SDIO2
*        │   └── VPU
*        ├── BUS3
*        │   ├── BUS5
*        │   │   ├── I2C1
*        │   │   ├── I2C2
*        │   │   ├── I2C3
*        │   │   ├── I2S
*        │   │   ├── SPI1
*        │   │   ├── SPI2
*        │   │   ├── SPI3
*        │   │   ├── UART1
*        │   │   ├── UART2
*        │   │   ├── UART3
*        │   │   └── UART4
*        │   ├── DMAC2
*        │   ├── GPU
*        │   └── USB
*        ├── BUS4
*        │   ├── GPIO
*        │   ├── GPSCTRL
*        │   ├── PWM
*        │   ├── RTC
*        │   ├── SYSCTRL
*        │   ├── TIMER
*        │   └── VIC
*        ├── DS1_2
*        ├── DS1_3
*        └── GPS
*/

enum sep0611_clk_gate{
  DDRC = 0, BUS1, BUS2, BUS3, DS1_2,
  DS1_3, USBC, DMAC1, NAND, DMAC2,
  ESRAM, SDIO1, SDIO2, GPU, VPU,
  BUS4, BUS5, VIC_, SYSCTRL, PRTC,
  TIMER, GPSCTRL, GPIO, LCDC2HDMI, DDRPHY,
  UART1, UART2, UART3, UART4, SPI1,
  SPI2, SPI3,

  I2C1 = 32, I2C2, I2C3, I2S, PWM,
  H2X, LCDC, NOR, GPSHCLK, GPS,
};

typedef struct {
	unsigned long f;
	unsigned long r;
}pll_t;

static pll_t apll_tab[] = {
  PLL_CFG(800*MHz, 0x00010810),
};

static pll_t mpll_tab[] = {
  PLL_CFG(480*MHz, 0x00013C12),   // 480MHz
};

static pll_t dpll_tab[] = {
  PLL_CFG(400*MHz, 0x00010812),   // 402MHz
};

static void rt_hw_set_system_clock(void)
{
  /*apll, mpll, dpll is set in uboot when system boots up*/
}

static void rt_hw_set_usb_clock(void)
{

}

static void rt_hw_set_peripheral_clock(void)
{

}
/**
 * @brief System Clock Configuration
 */
/* apll mpll dpll should be set in u-boot, Here just set clock
 * of the pherial
 */
void rt_hw_set_apll_clock(void)
{

}
void rt_hw_set_mpll_clock(void)
{

}
void rt_hw_set_dpll_clock(void)
{

}
void rt_hw_clock_init(void)
{
	/* set system clock */
	rt_hw_set_system_clock();
}

/**
 * @brief Get system clock
 */
rt_uint32_t rt_hw_get_clock(void)
{
}

/**
 * @brief Enable module clock
 */
void rt_hw_enable_module_clock(rt_uint8_t module)
{
  if (module >= 32) {
    write_reg(SEP6200_PMU_CLK_GT_CFG2, (1 << (module - 32)) | read_reg(SEP6200_PMU_CLK_GT_CFG2));
  } else {
    write_reg(SEP6200_PMU_CLK_GT_CFG1, (1 << module) | read_reg(SEP6200_PMU_CLK_GT_CFG1));
  }
}

/**
 * @brief Disable module clock
 */
void rt_hw_disable_module_clock(rt_uint8_t module)
{
  if (module >= 32) {
    write_reg(SEP6200_PMU_CLK_GT_CFG2, ~(1 << (module - 32)) & read_reg(SEP6200_PMU_CLK_GT_CFG2));
  } else {
    write_reg(SEP6200_PMU_CLK_GT_CFG1, ~(1 << module) & read_reg(SEP6200_PMU_CLK_GT_CFG1));
  }
}
