/**
 * @file
 * @brief   System level header file.
 */

/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2019-04-15 09:35:40 -0500 (Mon, 15 Apr 2019) $
 * $Revision: 42499 $
 *
 ******************************************************************************/

#ifndef _MXC_SYS_H_
#define _MXC_SYS_H_

#include "mxc_config.h"
#include "uart_regs.h"
#include "i2c_regs.h"
#include "gcr_regs.h"
#include "tmr_regs.h"
#include "icc_regs.h"
#include "spi17y_regs.h"
#include "spimss_regs.h"
#include "gpio.h"
#include "flc_regs.h"
#include "dma.h"
#include "wdt_regs.h"

#ifdef __cplusplus
extern "C" {
#endif
#if defined ( __CC_ARM ) /* Suppressing the warning: "enum value is out of range of int" for Keil */
#pragma push
#pragma diag_suppress 66
#endif /* __CC_ARM */

/** @brief System reset0 enumeration. Used in SYS_PeriphReset0 function */
typedef enum {
    SYS_RESET0_DMA       = MXC_F_GCR_RSTR0_DMA,         /**< Reset DMA */
    SYS_RESET0_WDT       = MXC_F_GCR_RSTR0_WDT,         /**< Reset WDT */
    SYS_RESET0_GPIO0     = MXC_F_GCR_RSTR0_GPIO0,       /**< Reset GPIO0 */
    SYS_RESET0_TIMER0    = MXC_F_GCR_RSTR0_TIMER0,      /**< Reset TIMER0 */
    SYS_RESET0_TIMER1    = MXC_F_GCR_RSTR0_TIMER1,      /**< Reset TIMER1 */
    SYS_RESET0_TIMER2    = MXC_F_GCR_RSTR0_TIMER2,      /**< Reset TIMER2 */
    SYS_RESET0_UART0     = MXC_F_GCR_RSTR0_UART0,       /**< Reset UART0 */
    SYS_RESET0_UART1     = MXC_F_GCR_RSTR0_UART1,       /**< Reset UART1 */
    SYS_RESET0_SPI0      = MXC_F_GCR_RSTR0_SPI0,        /**< Reset SPI0 */
    SYS_RESET0_SPI1      = MXC_F_GCR_RSTR0_SPI1,        /**< Reset SPI1 */
    SYS_RESET0_I2C0      = MXC_F_GCR_RSTR0_I2C0,        /**< Reset I2C0 */
    SYS_RESET0_RTC       = MXC_F_GCR_RSTR0_RTC,         /**< Reset RTC */
    SYS_RESET0_SRST      = MXC_F_GCR_RSTR0_SRST,        /**< Soft reset */
    SYS_RESET0_PRST      = MXC_F_GCR_RSTR0_PRST,        /**< Peripheral reset */
    SYS_RESET0_SYSTEM    = MXC_F_GCR_RSTR0_SYSTEM,      /**< System reset */
} sys_reset0_t;

/** @brief System reset1 enumeration. Used in SYS_PeriphReset1 function */
typedef enum {
    SYS_RESET1_I2C1      = MXC_F_GCR_RSTR1_I2C1,        /**< Reset I2C1 */
} sys_reset1_t;

/** @brief System clock disable enumeration. Used in SYS_ClockDisable and SYS_ClockEnable functions */
typedef enum {
    SYS_PERIPH_CLOCK_GPIO0   = MXC_F_GCR_PERCKCN0_GPIO0D,     /**< Disable MXC_F_GCR_PERCKCN0_GPIO0D clock */
    SYS_PERIPH_CLOCK_DMA     = MXC_F_GCR_PERCKCN0_DMAD,       /**< Disable MXC_F_GCR_PERCKCN0_DMAD clock */
    SYS_PERIPH_CLOCK_SPI17Y  = MXC_F_GCR_PERCKCN0_SPI0D,      /**< Disable MXC_F_GCR_PERCKCN0_SPI0D clock */
    SYS_PERIPH_CLOCK_SPIMSS  = MXC_F_GCR_PERCKCN0_SPI1D,      /**< Disable MXC_F_GCR_PERCKCN0_SPI1D clock */
    SYS_PERIPH_CLOCK_UART0   = MXC_F_GCR_PERCKCN0_UART0D,     /**< Disable MXC_F_GCR_PERCKCN0_UART0D clock */
    SYS_PERIPH_CLOCK_UART1   = MXC_F_GCR_PERCKCN0_UART1D,     /**< Disable MXC_F_GCR_PERCKCN0_UART1D clock */
    SYS_PERIPH_CLOCK_I2C0    = MXC_F_GCR_PERCKCN0_I2C0D,      /**< Disable MXC_F_GCR_PERCKCN0_I2C0D clock */
    SYS_PERIPH_CLOCK_T0      = MXC_F_GCR_PERCKCN0_T0D,        /**< Disable MXC_F_GCR_PERCKCN0_T0D clock */
    SYS_PERIPH_CLOCK_T1      = MXC_F_GCR_PERCKCN0_T1D,        /**< Disable MXC_F_GCR_PERCKCN0_T1D clock */
    SYS_PERIPH_CLOCK_T2      = MXC_F_GCR_PERCKCN0_T2D,        /**< Disable MXC_F_GCR_PERCKCN0_T2D clock */
    SYS_PERIPH_CLOCK_I2C1    = MXC_F_GCR_PERCKCN0_I2C1D,      /**< Disable MXC_F_GCR_PERCKCN0_I2C1D clock */
} sys_periph_clock_t;

/** @brief Clock source */
typedef enum {
    SYS_CLOCK_NANORING      = MXC_V_GCR_CLKCN_CLKSEL_NANORING, /**< 8KHz nanoring on MAX32660 */
    SYS_CLOCK_HFXIN         = MXC_V_GCR_CLKCN_CLKSEL_HFXIN,    /**< 32KHz on MAX32660 */
    SYS_CLOCK_HFXIN_DIGITAL = 0x9,                             /**< External Clock Input*/
    SYS_CLOCK_HIRC          = MXC_V_GCR_CLKCN_CLKSEL_HIRC,     /**< High Frequency Internal Oscillator */
} sys_system_clock_t;

typedef void* sys_cfg_t;

typedef sys_cfg_t sys_cfg_i2c_t;
typedef sys_cfg_t sys_cfg_flc_t;
typedef sys_cfg_t sys_cfg_wdt_t;

/** @brief Map control */
typedef enum {
    MAP_A,
    MAP_B,
    MAP_C,
} sys_map_t;

/** @brief UART Flow control */
typedef enum {
    UART_FLOW_DISABLE,
    UART_FLOW_ENABLE,
} sys_uart_flow_t;

/** @brief UART system configuration object */
typedef struct {
    sys_map_t map;
    sys_uart_flow_t flow_flag;
} sys_cfg_uart_t;

/** @brief SPI17Y system configuration object */
typedef struct {
    sys_map_t map;
} sys_cfg_spi17y_t;

/** @brief SPIMSS system configuration object */
typedef struct {
    sys_map_t map;
} sys_cfg_spimss_t;

/** @brief I2S system configuration object */
typedef struct {
    sys_map_t map;
    dma_reqsel_t dma_reqsel_tx;
    dma_reqsel_t dma_reqsel_rx;
} sys_cfg_i2s_t;

/** @brief TIMER system configuration object */ 
typedef struct {
   int out_en;
} sys_cfg_tmr_t;

/** @brief Real Time Clock system configuration object */
typedef struct {
    mxc_tmr_regs_t* tmr;
}  sys_cfg_rtc_t;


/** @brief Pulse Train System Configuration Object */
typedef gpio_cfg_t sys_cfg_pt_t;

#if defined ( __CC_ARM ) /* Restore the warning: "enum is out of int range" for Keil */
#pragma pop
#endif /* __CC_ARM */
/***** Function Prototypes *****/
/**
 * @brief      Selects the system clock and enables it once ready
 * @param      clock   Enumeration for desired clock.
 * @param      tmr     Optional tmr pointer for timeout. NULL if undesired.
 *
 * @returns    #E_NO_ERROR is clock is succesfully selected
 */
int SYS_Clock_Select(sys_system_clock_t clock, mxc_tmr_regs_t* tmr);

/**
 * @brief      Enables the selected peripheral clock.
 * @param      clock   Enumeration for desired clock.
 */
void SYS_ClockEnable(sys_periph_clock_t clock);

/**
 * @brief      Disables the selected peripheral clock.
 * @param      clock   Enumeration for desired clock.
 */
void SYS_ClockDisable(sys_periph_clock_t clock);

/**
 * @brief      Enables the external 32k oscillator.
 * @param      sys_cfg system configuration object
 *
 * @returns    #E_NO_ERROR is successful, appropriate error otherwise
 */
int SYS_ClockEnable_X32K(sys_cfg_rtc_t *sys_cfg);

/**
 * @brief      Disables the external 32k oscillator.
 *
 * @returns    #E_NO_ERROR is successful, appropriate error otherwise
 */
int SYS_ClockDisable_X32K(void);

/**
 * @brief      System level initialization for UART module.
 * @param      uart      Pointer to UART module registers
 * @param      sys_cfg   System configuration object
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_UART_Init(mxc_uart_regs_t *uart, const sys_cfg_uart_t* sys_cfg);

/**
 * @brief      System level shutdown for UART module
 * @param      uart  Pointer to UART module registers
 *
 * @return     #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_UART_Shutdown(mxc_uart_regs_t *uart);

/**
 * @brief      System level initialization for I2C module.
 * @param      i2c  Pointer to I2C module registers
 * @param      sys_cfg  System configuration object
 * 
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_I2C_Init(mxc_i2c_regs_t *i2c,  const sys_cfg_i2c_t* sys_cfg);

/**
 * @brief      System level Shutdown for I2C module.
 * @param      i2c    Pointer to I2C module registers
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_I2C_Shutdown(mxc_i2c_regs_t *i2c);

/**
 * @brief      Init DMA system settings
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_DMA_Init(void);

/**
 * @brief      Shutdown DMA system specific settings
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_DMA_Shutdown(void);

/**
 * @brief Get the frequency of the I2C module source clock
 * @param      spim  Unused, pointer to I2C module registers
 *
 * @returns    frequency in Hz
 */
unsigned SYS_I2C_GetFreq(mxc_i2c_regs_t *i2c);

/**
 * @brief Get the frequency of the Timer module source clock.
 * @params     tmr  Unused, pointer to timer module registers
 *
 * @returns    frequency in Hz
 */
unsigned SYS_TMR_GetFreq(mxc_tmr_regs_t *tmr);

/**
 * @brief Reset the peripherals and/or CPU in the rstr0 register.
 * @param      Enumeration for what to reset. Can reset multiple items at once.
 */
void SYS_Reset0(sys_reset0_t reset);

/**
 * @brief Reset the peripherals and/or CPU in the rstr1 register.
 * @param      Enumeration for what to reset. Can reset multiple items at once.
 */
void SYS_Reset1(sys_reset1_t reset);

/**
 * @brief Clear Cache and Line buffer.
 */
void SYS_Flash_Operation(void);

/**
 * @brief      Init TMR system settings
 * @param      tmr Pointer to timer module registers
 * @param      sys_cfg System configuration object
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_TMR_Init(mxc_tmr_regs_t *tmr, const sys_cfg_tmr_t* sys_cfg);

/**
 * @brief      Init flash system settings
 * @param      sys_cfg System configuration object
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_FLC_Init(const sys_cfg_flc_t* sys_cfg);

/**
 * @brief      Shutdown flash system specific settings
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_FLC_Shutdown(void);

/**
 * @brief System level initialization for SPI17Y module.
 * @param      spi pointer to spi module registers
 * @param      sys_cfg System configuration object
 *
 * @returns    E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_SPI17Y_Init( mxc_spi17y_regs_t *spi, const sys_cfg_spi17y_t* sys_cfg);

/**
 * @brief System level shutdown for SPI17Y module
 * @param      pointer to spi module registers
 *
 * @returns    E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_SPI17Y_Shutdown(mxc_spi17y_regs_t *spi);

/**
 * @brief System level initialization for SPIMSS module.
 * @param      spi pointer to spi module registers
 * @param      sys_cfg System configuration object
 *
 * @returns    E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_SPIMSS_Init(mxc_spimss_regs_t *spi, const sys_cfg_spimss_t* sys_cfg);

/**
 * @brief      System level shutdown for SPIMSS module
 * @param      pointer to spi module registers
 *
 * @returns    E_NO_ERROR if everything is successful
 */
int SYS_SPIMSS_Shutdown(mxc_spimss_regs_t *spi);

/**
 * @brief      Shutdown Timer system specific settings
 * @param      tmr pointer to timer module registers
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_TMR_Shutdown(mxc_tmr_regs_t *tmr);

/**
 * @brief      System level initialization for I2S Module
 * @param      sys_cfg System configuration object
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_I2S_Init(const sys_cfg_i2s_t* sys_cfg);

/**
 * @brief System level shutdown of I2S module
 *
 * @returns    #E_NO_ERROR if everything is successful
 */
int SYS_I2S_Shutdown(void);

/**
 * @brief      Get the frequency of the I2S module source clock
 * @param      spimss  Pointer to I2S module registers
 *
 * @returns    frequency in Hz
 */
int SYS_I2S_GetFreq(mxc_spimss_regs_t *spimss);

/**
 * @brief      Init system settings for RTC square wave output.
 * @param      sys_cfg  System configuration object
 *
 * @returns    #E_NO_ERROR if successful, appropriate error otherwise
 */
int SYS_RTC_SqwavInit(const sys_cfg_rtc_t* sys_cfg);


/**
 * @brief      System Tick Configuration Helper
 *
 *             The function enables selection of the external clock source for
 *             the System Tick Timer. It initializes the System Timer and its
 *             interrupt, and starts the System Tick Timer. Counter is in free
 *             running mode to generate periodic interrupts.
 *
 * @param      ticks    Number of ticks between two interrupts.
 * @param      clk_src  Selects between default SystemClock or External Clock.
 *                      - 0 Use external clock source
 * @param tmr  Optional tmr pointer for timeout. NULL if undesired.
 *                      - 1 SystemClock
 *
 * @return     #E_NO_ERROR  Function succeeded, of #E_INVALID if an invalid value is requested
 */
int SYS_SysTick_Config(uint32_t ticks, int clk_src, mxc_tmr_regs_t* tmr);

/**
 * @brief      Disable System Tick timer
 */
void SYS_SysTick_Disable(void);

/**
 * @brief      Delay a requested number of SysTick Timer Ticks.
 * @param      ticks  Number of System Ticks to delay.
 * @note       This delay function is based on the clock used for the SysTick
 *             timer if the SysTick timer is enabled. If the SysTick timer is
 *             not enabled, the current SysTick registers are saved and the
 *             timer will use the SystemClock as the source for the delay. The
 *             delay is measured in clock ticks and is not based on the SysTick
 *             interval.
 *
 * @return     #E_NO_ERROR if everything is successful
 */
int SYS_SysTick_Delay(uint32_t ticks);

/**
 * @brief      Get the frequency of the SysTick Timer
 *
 * @return     frequency in Hz
 */
uint32_t SYS_SysTick_GetFreq(void);

/**
 * @brief      Delay a requested number of microseconds.
 * @param      us    Number of microseconds to delay.
 * @note       Calls SYS_SysTick_Delay().
 */
void SYS_SysTick_DelayUs(uint32_t us);

/**
 * @brief      Init WDT system settings
 * @param      wdt     watchdog registers
 * @param      sys_cfg System configuration object
 */
int SYS_WDT_Init(mxc_wdt_regs_t* wdt, const sys_cfg_wdt_t* sys_cfg);
#ifdef __cplusplus
}
#endif

#endif /* _MXC_SYS_H_*/

