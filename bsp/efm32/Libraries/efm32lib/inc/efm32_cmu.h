/***************************************************************************//**
 * @file
 * @brief Clock management unit (CMU) API for EFM32.
 * @author Energy Micro AS
 * @version 1.3.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __EFM32_CMU_H
#define __EFM32_CMU_H

#include <stdbool.h>
#include "efm32.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup CMU
 * @{
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/* Select register ids, for internal use */
#define CMU_NOSEL_REG              0
#define CMU_HFCLKSEL_REG           1
#define CMU_LFACLKSEL_REG          2
#define CMU_LFBCLKSEL_REG          3

#define CMU_SEL_REG_POS            0
#define CMU_SEL_REG_MASK           0xf

/* Divisor register ids, for internal use */
#define CMU_NODIV_REG              0
#define CMU_HFPERCLKDIV_REG        1
#define CMU_HFCORECLKDIV_REG       2
#define CMU_LFAPRESC0_REG          3
#define CMU_LFBPRESC0_REG          4

#define CMU_DIV_REG_POS            4
#define CMU_DIV_REG_MASK           0xf

/* Enable register ids, for internal use */
#define CMU_NO_EN_REG              0
#define CMU_HFPERCLKDIV_EN_REG     1
#define CMU_HFPERCLKEN0_EN_REG     2
#define CMU_HFCORECLKEN0_EN_REG    3
#define CMU_LFACLKEN0_EN_REG       4
#define CMU_LFBCLKEN0_EN_REG       5
#define CMU_PCNT_EN_REG            6

#define CMU_EN_REG_POS             8
#define CMU_EN_REG_MASK            0xf

/* Enable register bit position, for internal use */
#define CMU_EN_BIT_POS             12
#define CMU_EN_BIT_MASK            0x1f

/** @endcond (DO_NOT_INCLUDE_WITH_DOXYGEN) */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Clock divisors. */
typedef enum
{
  cmuClkDiv_1     = 0,  /**< Divide clock by 1. */
  cmuClkDiv_2     = 1,  /**< Divide clock by 2. */
  cmuClkDiv_4     = 2,  /**< Divide clock by 4. */
  cmuClkDiv_8     = 3,  /**< Divide clock by 8. */
  cmuClkDiv_16    = 4,  /**< Divide clock by 16. */
  cmuClkDiv_32    = 5,  /**< Divide clock by 32. */
  cmuClkDiv_64    = 6,  /**< Divide clock by 64. */
  cmuClkDiv_128   = 7,  /**< Divide clock by 128. */
  cmuClkDiv_256   = 8,  /**< Divide clock by 256. */
  cmuClkDiv_512   = 9,  /**< Divide clock by 512. */
  cmuClkDiv_1024  = 10, /**< Divide clock by 1024. */
  cmuClkDiv_2048  = 11, /**< Divide clock by 2048. */
  cmuClkDiv_4096  = 12, /**< Divide clock by 4096. */
  cmuClkDiv_8192  = 13, /**< Divide clock by 8192. */
  cmuClkDiv_16384 = 14, /**< Divide clock by 16384. */
  cmuClkDiv_32768 = 15  /**< Divide clock by 32768. */
} CMU_ClkDiv_TypeDef;


/** High frequency RC bands. */
typedef enum
{
  /** 1MHz RC band. */
  cmuHFRCOBand_1MHz  = _CMU_HFRCOCTRL_BAND_1MHZ,
  /** 7MHz RC band. */
  cmuHFRCOBand_7MHz  = _CMU_HFRCOCTRL_BAND_7MHZ,
  /** 11MHz RC band. */
  cmuHFRCOBand_11MHz = _CMU_HFRCOCTRL_BAND_11MHZ,
  /** 14MHz RC band. */
  cmuHFRCOBand_14MHz = _CMU_HFRCOCTRL_BAND_14MHZ,
  /** 21MHz RC band. */
  cmuHFRCOBand_21MHz = _CMU_HFRCOCTRL_BAND_21MHZ,
  /** 28MHz RC band. */
  cmuHFRCOBand_28MHz = _CMU_HFRCOCTRL_BAND_28MHZ
} CMU_HFRCOBand_TypeDef;


/** Clock points in CMU. Please refer to CMU overview in reference manual. */
typedef enum
{
  /*******************/
  /* HF clock branch */
  /*******************/

  /** High frequency clock */
  cmuClock_HF = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                (CMU_HFCLKSEL_REG << CMU_SEL_REG_POS) |
                (CMU_NO_EN_REG << CMU_EN_REG_POS) |
                (0 << CMU_EN_BIT_POS),

  /**********************************/
  /* HF peripheral clock sub-branch */
  /**********************************/

  /** High frequency peripheral clock */
  cmuClock_HFPER = (CMU_HFPERCLKDIV_REG << CMU_DIV_REG_POS) |
                   (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                   (CMU_HFPERCLKDIV_EN_REG << CMU_EN_REG_POS) |
                   (_CMU_HFPERCLKDIV_HFPERCLKEN_SHIFT << CMU_EN_BIT_POS),

  /** Universal sync/async receiver/transmitter 0 clock. */
#if defined(USART_COUNT) && (USART_COUNT > 0)
  cmuClock_USART0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                    (_CMU_HFPERCLKEN0_USART0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Universal sync/async receiver/transmitter 1 clock. */
#if defined(USART_COUNT) && (USART_COUNT > 1)
  cmuClock_USART1 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                    (_CMU_HFPERCLKEN0_USART1_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Universal sync/async receiver/transmitter 2 clock. */
#if defined(USART_COUNT) && (USART_COUNT > 2)
  cmuClock_USART2 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                    (_CMU_HFPERCLKEN0_USART2_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Universal async receiver/transmitter 0 clock. */
#if defined(UART_COUNT) && (UART_COUNT > 0)
  cmuClock_UART0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                   (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                   (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                   (_CMU_HFPERCLKEN0_UART0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Timer 0 clock. */
#if defined(TIMER_COUNT) && (TIMER_COUNT > 0)
  cmuClock_TIMER0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                    (_CMU_HFPERCLKEN0_TIMER0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Timer 1 clock. */
#if defined(TIMER_COUNT) && (TIMER_COUNT > 1)
  cmuClock_TIMER1 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                    (_CMU_HFPERCLKEN0_TIMER1_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Timer 2 clock. */
#if defined(TIMER_COUNT) && (TIMER_COUNT > 2)
  cmuClock_TIMER2 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                    (_CMU_HFPERCLKEN0_TIMER2_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Analog comparator 0 clock. */
#if defined(ACMP_COUNT) && (ACMP_COUNT > 0)
  cmuClock_ACMP0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                   (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                   (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                   (_CMU_HFPERCLKEN0_ACMP0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Analog comparator 1 clock. */
#if defined(ACMP_COUNT) && (ACMP_COUNT > 1)
  cmuClock_ACMP1 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                   (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                   (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                   (_CMU_HFPERCLKEN0_ACMP1_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Peripheral reflex system clock. */
#if defined(PRS_PRESENT)
  cmuClock_PRS = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                 (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                 (_CMU_HFPERCLKEN0_PRS_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Digital to analog converter 0 clock. */
#if defined(DAC_COUNT) && (DAC_COUNT > 0)
  cmuClock_DAC0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                  (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                  (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                  (_CMU_HFPERCLKEN0_DAC0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** General purpose input/output clock. */
#if defined(GPIO_PRESENT)
  cmuClock_GPIO = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                  (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                  (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                  (_CMU_HFPERCLKEN0_GPIO_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Voltage comparator clock. */
#if defined(VCMP_PRESENT)
  cmuClock_VCMP = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                  (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                  (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                  (_CMU_HFPERCLKEN0_VCMP_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Analog to digital converter 0 clock. */
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
  cmuClock_ADC0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                  (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                  (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                  (_CMU_HFPERCLKEN0_ADC0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** I2C 0 clock. */
#if defined(I2C_COUNT) && (I2C_COUNT > 0)
  cmuClock_I2C0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                  (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                  (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS) |
                  (_CMU_HFPERCLKEN0_I2C0_SHIFT << CMU_EN_BIT_POS),
#endif

  /**********************/
  /* HF core sub-branch */
  /**********************/

  /** Core clock */
  cmuClock_CORE = (CMU_HFCORECLKDIV_REG << CMU_DIV_REG_POS) |
                  (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                  (CMU_NO_EN_REG << CMU_EN_REG_POS) |
                  (0 << CMU_EN_BIT_POS),

  /** Advanced encryption standard accelerator clock. */
#if defined(AES_PRESENT)
  cmuClock_AES = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                 (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS) |
                 (_CMU_HFCORECLKEN0_AES_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Direct memory access controller clock. */
#if defined(DMA_PRESENT)
  cmuClock_DMA = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                 (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS) |
                 (_CMU_HFCORECLKEN0_DMA_SHIFT << CMU_EN_BIT_POS),
#endif
  /** Low energy clocking module clock. */
  cmuClock_CORELE = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS) |
                    (_CMU_HFCORECLKEN0_LE_SHIFT << CMU_EN_BIT_POS),

  /** External bus interface clock. */
#if defined(EBI_PRESENT)
  cmuClock_EBI = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                 (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS) |
                 (_CMU_HFCORECLKEN0_EBI_SHIFT << CMU_EN_BIT_POS),
#endif

  /***************/
  /* LF A branch */
  /***************/

  /** Low frequency A clock */
  cmuClock_LFA = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                 (CMU_LFACLKSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_NO_EN_REG << CMU_EN_REG_POS) |
                 (0 << CMU_EN_BIT_POS),

  /** Real time counter clock. */
#if defined(RTC_PRESENT)
  cmuClock_RTC = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS) |
                 (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS) |
                 (_CMU_LFACLKEN0_RTC_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Low energy timer 0 clock. */
#if defined(LETIMER_COUNT) && (LETIMER_COUNT > 0)
  cmuClock_LETIMER0 = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS) |
                      (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                      (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS) |
                      (_CMU_LFACLKEN0_LETIMER0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Liquid crystal display, pre FDIV clock. */
#if defined(LCD_PRESENT)
  cmuClock_LCDpre = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS) |
                    (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                    (CMU_NO_EN_REG << CMU_EN_REG_POS) |
                    (0 << CMU_EN_BIT_POS),

  /** Liquid crystal display clock. Please notice that FDIV prescaler
   * must be set by special API. */
  cmuClock_LCD = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                 (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS) |
                 (_CMU_LFACLKEN0_LCD_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Pulse counter 0 clock. */
#if defined(PCNT_COUNT) && (PCNT_COUNT > 0)
  cmuClock_PCNT0 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                   (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                   (CMU_PCNT_EN_REG << CMU_EN_REG_POS) |
                   (_CMU_PCNTCTRL_PCNT0CLKEN_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Pulse counter 1 clock. */
#if defined(PCNT_COUNT) && (PCNT_COUNT > 1)
  cmuClock_PCNT1 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                   (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                   (CMU_PCNT_EN_REG << CMU_EN_REG_POS) |
                   (_CMU_PCNTCTRL_PCNT1CLKEN_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Pulse counter 2 clock. */
#if defined(PCNT_COUNT) && (PCNT_COUNT > 2)
  cmuClock_PCNT2 = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                   (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                   (CMU_PCNT_EN_REG << CMU_EN_REG_POS) |
                   (_CMU_PCNTCTRL_PCNT2CLKEN_SHIFT << CMU_EN_BIT_POS),
#endif

  /***************/
  /* LF B branch */
  /***************/

  /** Low frequency B clock */
  cmuClock_LFB = (CMU_NODIV_REG << CMU_DIV_REG_POS) |
                 (CMU_LFBCLKSEL_REG << CMU_SEL_REG_POS) |
                 (CMU_NO_EN_REG << CMU_EN_REG_POS) |
                 (0 << CMU_EN_BIT_POS),

  /** Low energy universal asynchronous receiver/transmitter 0 clock. */
#if defined(LEUART_COUNT) && (LEUART_COUNT > 0)
  cmuClock_LEUART0 = (CMU_LFBPRESC0_REG << CMU_DIV_REG_POS) |
                     (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                     (CMU_LFBCLKEN0_EN_REG << CMU_EN_REG_POS) |
                     (_CMU_LFBCLKEN0_LEUART0_SHIFT << CMU_EN_BIT_POS),
#endif

  /** Low energy universal asynchronous receiver/transmitter 1 clock. */
#if defined(LEUART_COUNT) && (LEUART_COUNT > 1)
  cmuClock_LEUART1 = (CMU_LFBPRESC0_REG << CMU_DIV_REG_POS) |
                     (CMU_NOSEL_REG << CMU_SEL_REG_POS) |
                     (CMU_LFBCLKEN0_EN_REG << CMU_EN_REG_POS) |
                     (_CMU_LFBCLKEN0_LEUART1_SHIFT << CMU_EN_BIT_POS),
#endif
} CMU_Clock_TypeDef;


/** Oscillator types. */
typedef enum
{
  cmuOsc_LFXO,      /**< Low frequency crystal oscillator. */
  cmuOsc_LFRCO,     /**< Low frequency RC oscillator. */
  cmuOsc_HFXO,      /**< High frequency crystal oscillator. */
  cmuOsc_HFRCO,     /**< High frequency RC oscillator. */
  cmuOsc_AUXHFRCO   /**< Auxiliary high frequency RC oscillator. */
} CMU_Osc_TypeDef;


/** Selectable clock sources. */
typedef enum
{
  cmuSelect_Error,     /**< Usage error. */
  cmuSelect_Disabled,  /**< Clock selector disabled. */
  cmuSelect_LFXO,      /**< Low frequency crystal oscillator. */
  cmuSelect_LFRCO,     /**< Low frequency RC oscillator. */
  cmuSelect_HFXO,      /**< High frequency crystal oscillator. */
  cmuSelect_HFRCO,     /**< High frequency RC oscillator. */
  cmuSelect_CORELEDIV2 /**< Core low energy clock divided by 2. */
} CMU_Select_TypeDef;


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

uint32_t CMU_Calibrate(uint32_t HFCycles, CMU_Osc_TypeDef reference);

CMU_ClkDiv_TypeDef CMU_ClockDivGet(CMU_Clock_TypeDef clock);
void CMU_ClockDivSet(CMU_Clock_TypeDef clock, CMU_ClkDiv_TypeDef div);
void CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable);
uint32_t CMU_ClockFreqGet(CMU_Clock_TypeDef clock);
CMU_Select_TypeDef CMU_ClockSelectGet(CMU_Clock_TypeDef clock);
void CMU_ClockSelectSet(CMU_Clock_TypeDef clock, CMU_Select_TypeDef ref);

void CMU_FreezeEnable(bool enable);

CMU_HFRCOBand_TypeDef CMU_HFRCOBandGet(void);
void CMU_HFRCOBandSet(CMU_HFRCOBand_TypeDef band);
uint32_t CMU_HFRCOStartupDelayGet(void);
void CMU_HFRCOStartupDelaySet(uint32_t delay);

/***************************************************************************//**
 * @brief
 *   Clear one or more pending CMU interrupts.
 *
 * @param[in] flags
 *   CMU interrupt sources to clear.
 ******************************************************************************/
static __INLINE void CMU_IntClear(uint32_t flags)
{
  CMU->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more CMU interrupts.
 *
 * @param[in] flags
 *   CMU interrupt sources to disable.
 ******************************************************************************/
static __INLINE void CMU_IntDisable(uint32_t flags)
{
  CMU->IEN &= ~flags;
}


/***************************************************************************//**
 * @brief
 *   Enable one or more CMU interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using CMU_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] flags
 *   CMU interrupt sources to enable.
 ******************************************************************************/
static __INLINE void CMU_IntEnable(uint32_t flags)
{
  CMU->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending CMU interrupts.
 *
 * @return
 *   CMU interrupt sources pending.
 ******************************************************************************/
static __INLINE uint32_t CMU_IntGet(void)
{
  return(CMU->IF);
}


/**************************************************************************//**
 * @brief
 *   Set one or more pending CMU interrupts from SW.
 *
 * @param[in] flags
 *   CMU interrupt sources to set to pending.
 *****************************************************************************/
static __INLINE void CMU_IntSet(uint32_t flags)
{
  CMU->IFS = flags;
}

uint32_t CMU_LCDClkFDIVGet(void);
void CMU_LCDClkFDIVSet(uint32_t div);

/***************************************************************************//**
 * @brief
 *   Lock the CMU in order to protect some of its registers against unintended
 *   modification.
 *
 * @details
 *   Please refer to the reference manual for CMU registers that will be
 *   locked.
 *
 * @note
 *   If locking the CMU registers, they must be unlocked prior to using any
 *   CMU API functions modifying CMU registers protected by the lock.
 ******************************************************************************/
static __INLINE void CMU_Lock(void)
{
  CMU->LOCK = CMU_LOCK_LOCKKEY_LOCK;
}

void CMU_OscillatorEnable(CMU_Osc_TypeDef osc, bool enable, bool wait);
uint32_t CMU_OscillatorTuningGet(CMU_Osc_TypeDef osc);
void CMU_OscillatorTuningSet(CMU_Osc_TypeDef osc, uint32_t val);
bool CMU_PCNTClockExternalGet(unsigned int inst);
void CMU_PCNTClockExternalSet(unsigned int inst, bool external);

/***************************************************************************//**
 * @brief
 *   Unlock the CMU so that writing to locked registers again is possible.
 ******************************************************************************/
static __INLINE void CMU_Unlock(void)
{
  CMU->LOCK = CMU_LOCK_LOCKKEY_UNLOCK;
}


/** @} (end addtogroup CMU) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_CMU_H */
