/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#ifndef __CH56X_SYS_H__
#define __CH56X_SYS_H__

#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define sys_safe_access_enter(sys) \
        do { \
            sys->SAFE_ACCESS_SIG.reg = SAFE_ACCESS_SIG_1; \
            sys->SAFE_ACCESS_SIG.reg = SAFE_ACCESS_SIG_2; \
        } while(0)

#define sys_safe_access_leave(sys) \
        do sys->SAFE_ACCESS_SIG.reg = 0; while(0)

union _sys_safe_access_sig
{
    uint8_t reg;
    struct
    {
        uint8_t safe_acc_mode   : 2;  // RO, current safe access, 11b => RWA ok
        uint8_t resv_2          : 2;
        uint8_t safe_acc_timer  : 3;  // RO, current safe access time count
        uint8_t resv_7          : 1;
    };
};
#define RB_SAFE_ACC_MODE        0x03
#define RB_SAFE_ACC_TIMER       0x70

#define SAFE_ACCESS_SIG_1       0x57
#define SAFE_ACCESS_SIG_2       0xa8

union _sys_glob_rom_cfg
{
    uint8_t reg;
    struct
    {
        uint8_t rom_ext_re      : 1;  // RO, allow programmer to read FlashROM
        uint8_t code_ram_we     : 1;  // RWA, code SRAM writaboe
        uint8_t rom_data_we     : 1;  // RWA, FlashROM data erasable/writable
        uint8_t rom_code_we     : 1;  // RWA, FlashROM code erasable/writable
        uint8_t rom_code_ofs    : 1;  // RWA, FlashROM offset for user code
        uint8_t resv_5          : 3;
    };
};
#define RB_ROM_EXT_RE           0x01
#define RB_CODE_RAM_WE          0x02
#define RB_ROM_DATA_WE          0x04
#define RB_ROM_CODE_WE          0x08
#define RB_ROM_CODE_OFS         0x10

#define ROM_CODE_OFS_0x00000    0
#define ROM_CODE_OFS_0x04000    1

union _sys_rst_boot_stat
{
    uint8_t reg;
    struct
    {
        uint8_t reset_flag      : 2;  // RO, last reset cause
        uint8_t cfg_reset_en    : 1;  // RO, external reset pin (#RST) status
        uint8_t cfg_boot_en     : 1;  // RO, reset as 1
        uint8_t cfg_debug_en    : 1;  // RO
        uint8_t boot_loader     : 1;  // RO
        uint8_t resv_6          : 2;
    };
};
#define RB_RESET_FLAG           0x03
#define RB_CFG_RESET_EN         0x04
#define RB_CFG_BOOT_EN          0x08
#define RB_CFG_DEBUG_EN         0x10
#define RB_BOOT_LOADER          0x20

#define RESET_FLAG_IS_SOFT      0
#define RESET_FLAG_IS_POR       1
#define RESET_FLAG_IS_WDOG      2
#define RESET_FLAG_IS_RSTPIN    3

union _sys_rst_wdog_ctrl
{
    uint8_t reg;
    struct
    {
        uint8_t software_reset  : 1;  // WA/WZ, system software reset, auto clear
#if defined(SOC_SERIES_CH569)
        uint8_t wdog_rst_en     : 1;  // RWA, enable watchdog overflow to reset
        uint8_t wdog_int_en     : 1;  // RWA, enable watchdog overflow interrupt
        uint8_t wdog_int_flag   : 1;  // RW1, watchdog counter overflow
#else
        uint8_t resv_2          : 3;
#endif
        uint8_t resv_4          : 4;  // RO, B.7-6 must write 01b
    };
};
#define RB_SOFTWARE_RESET       0x01
#ifdef SOC_SERIES_CH569
#define RB_WDOG_RST_EN          0x02
#define RB_WDOG_INT_EN          0x04
#define RB_WDOG_INT_FLAG        0x08
#endif
#define wdog_ctrl_wdat(v)       (0x40 | (v))

union _sys_clk_pll_div
{
    uint8_t reg;
    struct
    {
        uint8_t pll_div         : 4;  // RWA, min 2
        uint8_t resv_4          : 4;  // RWA, B.7-6 must write 01b
    };
};
#define clk_pll_div_wdat(div)   (0x40 | (div))

union _sys_clk_cfg_ctrl
{
    uint8_t reg;
    struct
    {
        uint8_t pll_sleep       : 1;  // RWA, PLL sleep control
        uint8_t sel_pll         : 1;  // RWA, clock source select
        uint8_t resv_6          : 6;  // RWA, must write 10b
    };
};
#define RB_CLK_PLL_SLEEP        0x01
#define RB_CLK_SEL_PLL          0x02

#define CLK_PLL_SLEEP_DISABLE   0
#define CLK_PLL_SLEEP_ENABLE    1
#define CLK_SEL_PLL_HSE_30M     0
#define CLK_SEL_PLL_USB_480M    1
#define clk_cfg_ctrl_wdat(v)    (0x80 | (v))

union _sys_clk_mod_aux
{
    uint8_t reg;
    struct
    {
        uint8_t int_125m_en     : 1;  // RWA, USB PHY 125MHz to ETH
        uint8_t ext_125m_en     : 1;  // RWA, external 125MHz to ETH
        uint8_t mco_sel_msk     : 2;  // RWA, MCO output select
        uint8_t mco_en          : 1;  // RWA, MCO output enable
        uint8_t resv_5          : 3;
    };
};
#define RB_INT_125M_EN          0x01
#define RB_EXT_125M_EN          0x02
#define RB_MCO_SEL_MSK          0x0c
#define RB_MCO_EN               0x10

#define MCO_SEL_MSK_125M        0
#define MCO_SEL_MSK_25M         1
#define MCO_SEL_MSK_2_5M        2

/* All bits are RWA (need safe_access_sig), 0/1 : clock on/off
*/
union _sys_slp_clk_off0
{
    uint8_t reg;
    struct
    {
        uint8_t tmr0    : 1;
        uint8_t tmr1    : 1;
        uint8_t tmr2    : 1;
        uint8_t pwmx    : 1;
        uint8_t uart0   : 1;
        uint8_t uart1   : 1;
        uint8_t uart2   : 1;
        uint8_t uart3   : 1;
    };
};
#define RB_SLP_CLK_TMR0         0x01
#define RB_SLP_CLK_TMR1         0x02
#define RB_SLP_CLK_TMR2         0x04
#define RB_SLP_CLK_PWMX         0x08
#define RB_SLP_CLK_UART0        0x10
#define RB_SLP_CLK_UART1        0x20
#define RB_SLP_CLK_UART2        0x40
#define RB_SLP_CLK_UART3        0x80

#define SYS_SLP_CLK_ON          0
#define SYS_SLP_CLK_OFF         1

/* All writable bits are RWA (need safe_access_sig), 0/1 : clock on/off
*/
union _sys_slp_clk_off1
{
    uint8_t reg;
    struct
    {
        uint8_t spi0    : 1;
        uint8_t spi1    : 1;
#if defined(SOC_CH567)
        uint8_t sdc     : 1;
        uint8_t led     : 1;
        uint8_t usb0    : 1;
        uint8_t usb1    : 1;
        uint8_t resv_6  : 1;
#elif defined(SOC_CH568)
        uint8_t sdc     : 1;
        uint8_t led     : 1;
        uint8_t resv_4  : 1;
        uint8_t usb1    : 1;
        uint8_t sata    : 1;
        uint8_t ecdc    : 1;
#else
        uint8_t emmc    : 1;
        uint8_t hspi    : 1;
        uint8_t usbhs   : 1;
        uint8_t usbss   : 1;
        uint8_t serd    : 1;
        uint8_t dvp     : 1;
#endif
    };
};
#define RB_SLP_CLK_SPI0         0x01
#define RB_SLP_CLK_SPI1         0x02
#if defined(SOC_WCH_CH567)
#define RB_SLP_CLK_SDC          0x04
#define RB_SLP_CLK_LED          0x08
#define RB_SLP_CLK_USB0         0x10
#define RB_SLP_CLK_USB1         0x20
#define RB_SLP_CLK_ECDC         0x80
#elif defined(SOC_WCH_CH568)
#define RB_SLP_CLK_SDC          0x04
#define RB_SLP_CLK_LED          0x08
#define RB_SLP_CLK_USB1         0x20
#define RB_SLP_CLK_SATA         0x40
#define RB_SLP_CLK_ECDC         0x80
#else
#define RB_SLP_CLK_EMMC         0x04
#define RB_SLP_CLK_HSPI         0x08
#define RB_SLP_CLK_USBHS        0x10
#define RB_SLP_CLK_USBSS        0x20
#define RB_SLP_CLK_SERD         0x40
#define RB_SLP_CLK_DVP          0x80
#endif

/* All writable bits are RWA (need safe_access_sig)
*/
union _sys_slp_wake_ctrl
{
    uint8_t reg;
    struct
    {
#if defined(SOC_WCH_CH567)
        uint8_t usb0_wake       : 1;
        uint8_t usb1_wake       : 1;
        uint8_t resv_2          : 2;
        uint8_t gpio_wake       : 1;
        uint8_t resv_5          : 3;
#elif defined(SOC_WCH_CH568)
        uint8_t resv_0          : 1;
        uint8_t usb1_wake       : 1;
        uint8_t sata_wake       : 1;
        uint8_t resv_3          : 1;
        uint8_t gpio_wake       : 1;
        uint8_t resv_5          : 3;
#else
        uint8_t usbhs_wake      : 1;
        uint8_t usbss_wake      : 1;
        uint8_t clk_eth         : 1;
        uint8_t clk_ecdc        : 1;
        uint8_t gpio_wake       : 1;
        uint8_t eth_wake        : 1;
        uint8_t resv_6          : 2;
#endif
    };
};
#if defined(SOC_WCH_CH567)
#define RB_SLP_USB0_WAKE        0x01
#define RB_SLP_USB1_WAKE        0x02
#define RB_SLP_GPIO_WAKE        0x10
#elif defined(SOC_WCH_CH568)
#define RB_SLP_USB1_WAKE        0x02
#define RB_SLP_SATA_WAKE        0x04
#define RB_SLP_GPIO_WAKE        0x10
#else
#define RB_SLP_USBHS_WAKE       0x01
#define RB_SLP_USBSS_WAKE       0x02
#define RB_SLP_CLK_ETH          0x04
#define RB_SLP_CLK_ECDC         0x08
#define RB_SLP_GPIO_WAKE        0x10
#define RB_SLP_ETH_WAKE         0x20
#endif

union _sys_slp_power_ctrl
{
    uint8_t reg;
    struct
    {
        uint8_t usbhs_pwrdn     : 1;  // RWA, USBHS power down (0:PWRUP)
        uint8_t resv_2          : 7;
    };
};
#define RB_SLP_USBHS_PWRDN      0x01

union _sys_serd_ana_cfg1
{
    uint16_t reg;
    struct
    {
        uint8_t serd_pll_cfg;         // RWA, reset as 0x5a
        uint8_t serd_30m_sel    : 1;  // RWA
        uint8_t serd_dn_tst     : 1;  // RWA
        uint8_t resv_10         : 6;
    };
};
#define RB_SERD_PLL_CFG         0x0ff
#define RB_SERD_30M_SEL         0x100
#define RB_SERD_DN_TST          0x200

union _sys_serd_ana_cfg2
{
    uint32_t reg;
    struct
    {
        uint32_t serd_trx_cfg   : 25;  // RWA, reset as 423015h
        uint32_t resv_25        : 7;
    };
};
#define RB_SERD_TRX_CFG         0x1000000

/*
 * 0x00  R8_SAFE_ACCESS_SIG: safe access signature register
 * 0x01  R8_CHIP_ID:         RF, chip ID register
 * 0x02  R8_SAFE_ACCESS_ID:  RF, read as 02h
 * 0x03  R8_WDOG_COUNT       RW, watchdog counter
 * 0x04  R8_GLOB_ROM_CFG:    ROM config register
 * 0x05  R8_RST_BOOT_STAT:   RO, boot state register
 * 0x06  R8_RST_WDOG_CTRL:   software reset & watchdog control register
 * 0x07  R8_GLOB_RESET_KEEP: RW, only power-on-reset can clear this register
 * 0x08  R8_CLK_PLL_DIV:     RWA, PLL output divisor register
 * 0x0a  R8_CLK_CFG_CTRL:    RWA, clock config register
 * 0x0b  R8_CLK_MOD_AUX:     RWA, clock auxiliary register
 * 0x0c  R8_SLP_CLK_OFF0:    RWA, sleep control register 0
 * 0x0d  R8_SLP_CLK_OFF1:    RWA, sleep control register 1
 * 0x0e  R8_SLP_WAKE_CTRL:   RWA, wakeup control register
 * 0x0f  R8_SLP_POWER_CTRL:  RWA, low power management register
 * 0x20  R16_SERD_ANA_CFG1:  RWA, SerDes PHY analog param config register 1
 * 0x24  R32_SERD_ANA_CFG2:  RWA, SerDes PHY analog param config register 2
 *
 * CAVEAT: gcc (as of 8.2.0) tends to read 32-bit word for bit field test.
 * Be careful for those with side effect for read.
 */
struct sys_registers
{
    union _sys_safe_access_sig  SAFE_ACCESS_SIG;
    uint8_t                     CHIP_ID;
    uint8_t                     SAFE_ACCESS_ID;
    uint8_t                     WDOG_COUNT;
    union _sys_glob_rom_cfg     GLOB_ROM_CFG;
    union _sys_rst_boot_stat    RST_BOOT_STAT;
    union _sys_rst_wdog_ctrl    RST_WDOG_CTRL;
    uint8_t                     GLOB_RESET_KEEP;
    union _sys_clk_pll_div      CLK_PLL_DIV;
    uint8_t                     resv_9;
    union _sys_clk_cfg_ctrl     CLK_CFG_CTRL;
    union _sys_clk_mod_aux      CLK_MOD_AUX;
    union _sys_slp_clk_off0     SLP_CLK_OFF0;
    union _sys_slp_clk_off1     SLP_CLK_OFF1;
    union _sys_slp_wake_ctrl    SLP_WAKE_CTRL;
    union _sys_slp_power_ctrl   SLP_POWER_CTRL;
#if defined(SOC_SERIES_CH569)
    uint32_t                    resv_10[4];
    union _sys_serd_ana_cfg1    SERD_ANA_CFG1;
    uint16_t                    resv_22;
    union _sys_serd_ana_cfg2    SERD_ANA_CFG2;
#endif
} __packed;

CHECK_STRUCT_SIZE(struct sys_registers, 0x28);

uint32_t sys_hclk_calc(void);
uint32_t sys_hclk_get(void);
int  sys_hclk_set(uint32_t freq);
int  sys_clk_off_by_irqn(uint8_t irqn, int off);
void sys_slp_clk_off0(uint8_t bits, int off);
void sys_slp_clk_off1(uint8_t bits, int off);

#ifdef __cplusplus
}
#endif

#endif
