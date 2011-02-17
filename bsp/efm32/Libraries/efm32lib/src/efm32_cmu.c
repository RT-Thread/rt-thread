/***************************************************************************//**
 * @file
 * @brief Clock management unit (CMU) peripheral API for EFM32.
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

#include "efm32_cmu.h"
#include "efm32_assert.h"
#include "efm32_bitband.h"
#include "efm32_emu.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup CMU
 * @brief EFM32 clock management unit utilities.
 * @{
 ******************************************************************************/

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** Maximum allowed core frequency when using 0 wait states on flash access. */
#define CMU_MAX_FREQ_0WS    16000000

/** Low frequency A group identifier */
#define CMU_LFA             0

/** Low frequency B group identifier */
#define CMU_LFB             1

/** @endcond (DO_NOT_INCLUDE_WITH_DOXYGEN) */

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *   Configure flash access wait states in order to support given HFCORECLK
 *   frequency.
 *
 * @param[in] hfcoreclk
 *   HFCORECLK frequency that flash access wait states must be configured for.
 ******************************************************************************/
static void CMU_FlashWaitStateControl(uint32_t hfcoreclk)
{
  uint32_t cfg;

  if (hfcoreclk > CMU_MAX_FREQ_0WS)
  {
    switch (MSC->READCTRL & _MSC_READCTRL_MODE_MASK)
    {
    case MSC_READCTRL_MODE_WS0:
      cfg = MSC_READCTRL_MODE_WS1;
      break;

    case MSC_READCTRL_MODE_WS0SCBTP:
      cfg = MSC_READCTRL_MODE_WS1SCBTP;
      break;

    default:
      return;
    }
  }
  else
  {
    switch (MSC->READCTRL & _MSC_READCTRL_MODE_MASK)
    {
    case MSC_READCTRL_MODE_WS1:
      cfg = MSC_READCTRL_MODE_WS0;
      break;

    case MSC_READCTRL_MODE_WS1SCBTP:
      cfg = MSC_READCTRL_MODE_WS0SCBTP;
      break;

    default:
      return;
    }
  }

  MSC->READCTRL = cfg;
}


/***************************************************************************//**
 * @brief
 *   Get the LFnCLK frequency based on current configuration.
 *
 * @param[in] group
 *   LF group, 0 = A, 1 = B, ...
 *
 * @return
 *   The LFnCLK frequency in Hz. If no LFnCLK is selected (disabled), 0 is
 *   returned.
 ******************************************************************************/
static uint32_t CMU_LFClkGet(unsigned int group)
{
  uint32_t ret;

  switch ((CMU->LFCLKSEL >> (group * 2)) & 0x3)
  {
  case _CMU_LFCLKSEL_LFA_LFRCO:
    ret = SystemLFRCOClockGet();
    break;

  case _CMU_LFCLKSEL_LFA_LFXO:
    ret = SystemLFXOClockGet();
    break;

  case _CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2:
    ret = SystemCoreClockGet() / 2;
    break;

  default:
    ret = 0;
    break;
  }

  return ret;
}


/***************************************************************************//**
 * @brief
 *   Wait for ongoing sync of register(s) to low frequency domain to complete.
 *
 * @param[in] mask
 *   Bitmask corresponding to SYNCBUSY register defined bits, indicating
 *   registers that must complete any ongoing synchronization.
 ******************************************************************************/
static __INLINE void CMU_Sync(uint32_t mask)
{
  /* Avoid deadlock if modifying the same register twice when freeze mode is */
  /* activated. */
  if (CMU->FREEZE & CMU_FREEZE_REGFREEZE)
    return;

  /* Wait for any pending previous write operation to have been completed */
  /* in low frequency domain */
  while (CMU->SYNCBUSY & mask) ;
}


/** @endcond (DO_NOT_INCLUDE_WITH_DOXYGEN) */

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Calibrate clock.
 *
 * @details
 *   Run a calibration for HFCLK against a selectable reference clock. Please
 *   refer to the EFM32 reference manual, CMU chapter, for further details.
 *
 * @note
 *   This function will not return until calibration measurement is completed.
 *
 * @param[in] HFCycles
 *   The number of HFCLK cycles to run calibration. Increasing this number
 *   increases precision, but the calibration will take more time.
 *
 * @param[in] ref
 *   The reference clock used to compare HFCLK with.
 *
 * @return
 *   The number of ticks the reference clock after HFCycles ticks on the HF
 *   clock.
 ******************************************************************************/
uint32_t CMU_Calibrate(uint32_t HFCycles, CMU_Osc_TypeDef ref)
{
  /* Set reference clock source */
  switch (ref)
  {
  case cmuOsc_LFXO:
    CMU->CALCTRL = CMU_CALCTRL_REFSEL_LFXO;
    break;

  case cmuOsc_LFRCO:
    CMU->CALCTRL = CMU_CALCTRL_REFSEL_LFRCO;
    break;

  case cmuOsc_HFXO:
    CMU->CALCTRL = CMU_CALCTRL_REFSEL_HFXO;
    break;

  case cmuOsc_HFRCO:
    CMU->CALCTRL = CMU_CALCTRL_REFSEL_HFRCO;
    break;

  case cmuOsc_AUXHFRCO:
    CMU->CALCTRL = CMU_CALCTRL_REFSEL_AUXHFRCO;
    break;

  default:
    EFM_ASSERT(0);
    return 0;
  }

  /* Set top value */
  CMU->CALCNT = HFCycles;

  /* Start calibration */
  CMU->CMD = CMU_CMD_CALSTART;

  /* Wait until calibration completes */
  while (CMU->STATUS & CMU_STATUS_CALBSY) ;

  return CMU->CALCNT;
}


/***************************************************************************//**
 * @brief
 *   Get clock divisor/prescaler.
 *
 * @param[in] clock
 *   Clock point to get divisor/prescaler for. Notice that not all clock points
 *   have a divisor/prescaler. Please refer to CMU overview in reference manual.
 *
 * @return
 *   The current clock point divisor/prescaler. #cmuClkDiv_1 is returned
 *   if @p clock specifies a clock point without a divisor/prescaler.
 ******************************************************************************/
CMU_ClkDiv_TypeDef CMU_ClockDivGet(CMU_Clock_TypeDef clock)
{
  uint32_t           divReg;
  CMU_ClkDiv_TypeDef ret;

  /* Get divisor reg id */
  divReg = (clock >> CMU_DIV_REG_POS) & CMU_DIV_REG_MASK;

  switch (divReg)
  {
  case CMU_HFPERCLKDIV_REG:
    ret = (CMU_ClkDiv_TypeDef)((CMU->HFPERCLKDIV &
                                _CMU_HFPERCLKDIV_HFPERCLKDIV_MASK) >>
                               _CMU_HFPERCLKDIV_HFPERCLKDIV_SHIFT);
    break;

  case CMU_HFCORECLKDIV_REG:
    ret = (CMU_ClkDiv_TypeDef)((CMU->HFCORECLKDIV &
                                _CMU_HFCORECLKDIV_HFCORECLKDIV_MASK) >>
                               _CMU_HFCORECLKDIV_HFCORECLKDIV_SHIFT);
    break;

  case CMU_LFAPRESC0_REG:
    switch (clock)
    {
    case cmuClock_RTC:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFAPRESC0 & _CMU_LFAPRESC0_RTC_MASK) >>
                                  _CMU_LFAPRESC0_RTC_SHIFT));
      break;

#if defined(LETIMER_COUNT) && (LETIMER_COUNT > 0)
    case cmuClock_LETIMER0:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFAPRESC0 & _CMU_LFAPRESC0_LETIMER0_MASK) >>
                                  _CMU_LFAPRESC0_LETIMER0_SHIFT));
      break;
#endif

#if defined(LCD_PRESENT)
    case cmuClock_LCDpre:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFAPRESC0 & _CMU_LFAPRESC0_LCD_MASK) >>
                                  _CMU_LFAPRESC0_LCD_SHIFT) + cmuClkDiv_16);
      break;
#endif /* defined(LCD_PRESENT) */

    default:
      EFM_ASSERT(0);
      ret = cmuClkDiv_1;
      break;
    }
    break;

  case CMU_LFBPRESC0_REG:
    switch (clock)
    {
#if defined(LEUART_COUNT) && (LEUART_COUNT > 0)
    case cmuClock_LEUART0:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART0_MASK) >>
                                  _CMU_LFBPRESC0_LEUART0_SHIFT));
      break;
#endif

#if defined(LEUART_COUNT) && (LEUART_COUNT > 1)
    case cmuClock_LEUART1:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART1_MASK) >>
                                  _CMU_LFBPRESC0_LEUART1_SHIFT));
      break;
#endif /* (LEUART_COUNT > 1) */

    default:
      EFM_ASSERT(0);
      ret = cmuClkDiv_1;
      break;
    }
    break;

  default:
    EFM_ASSERT(0);
    ret = cmuClkDiv_1;
    break;
  }

  return(ret);
}


/***************************************************************************//**
 * @brief
 *   Set clock divisor/prescaler.
 *
 * @note
 *   If setting a LF clock prescaler, synchronization into the low frequency
 *   domain is required. If the same register is modified before a previous
 *   update has completed, this function will stall until the previous
 *   synchronization has completed. Please refer to CMU_FreezeEnable() for
 *   a suggestion on how to reduce stalling time in some use cases.
 *
 * @param[in] clock
 *   Clock point to set divisor/prescaler for. Notice that not all clock points
 *   have a divisor/prescaler, please refer to CMU overview in the reference
 *   manual.
 *
 * @param[in] div
 *   The clock divisor to use (<= cmuClkDiv_512).
 ******************************************************************************/
void CMU_ClockDivSet(CMU_Clock_TypeDef clock, CMU_ClkDiv_TypeDef div)
{
  uint32_t freq;
  uint32_t divReg;

  /* Get divisor reg id */
  divReg = (clock >> CMU_DIV_REG_POS) & CMU_DIV_REG_MASK;

  switch (divReg)
  {
  case CMU_HFPERCLKDIV_REG:
    EFM_ASSERT(div <= cmuClkDiv_512);

    CMU->HFPERCLKDIV = (CMU->HFPERCLKDIV & ~_CMU_HFPERCLKDIV_HFPERCLKDIV_MASK) |
                       (div << _CMU_HFPERCLKDIV_HFPERCLKDIV_SHIFT);
    break;

  case CMU_HFCORECLKDIV_REG:
    EFM_ASSERT(div <= cmuClkDiv_512);

    /* Configure worst case wait states for flash access before setting divisor */
    CMU_FlashWaitStateControl(CMU_MAX_FREQ_0WS + 1);

    CMU->HFCORECLKDIV = (CMU->HFCORECLKDIV & ~_CMU_HFCORECLKDIV_HFCORECLKDIV_MASK) |
                        (div << _CMU_HFCORECLKDIV_HFCORECLKDIV_SHIFT);

    /* Update CMSIS core clock variable */
    /* (The function will update the global variable) */
    freq = SystemCoreClockGet();

    /* Optimize flash access wait state setting for current core clk */
    CMU_FlashWaitStateControl(freq);
    break;

  case CMU_LFAPRESC0_REG:
    switch (clock)
    {
    case cmuClock_RTC:
      EFM_ASSERT(div <= cmuClkDiv_32768);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFAPRESC0);

      CMU->LFAPRESC0 = (CMU->LFAPRESC0 & ~_CMU_LFAPRESC0_RTC_MASK) |
                       (div << _CMU_LFAPRESC0_RTC_SHIFT);
      break;

#if defined(LETIMER_COUNT) && (LETIMER_COUNT > 0)
    case cmuClock_LETIMER0:
      EFM_ASSERT(div <= cmuClkDiv_32768);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFAPRESC0);

      CMU->LFAPRESC0 = (CMU->LFAPRESC0 & ~_CMU_LFAPRESC0_LETIMER0_MASK) |
                       (div << _CMU_LFAPRESC0_LETIMER0_SHIFT);
      break;
#endif

#if defined(LCD_PRESENT)
    case cmuClock_LCDpre:
      EFM_ASSERT((div >= cmuClkDiv_16) && (div <= cmuClkDiv_128));

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFAPRESC0);

      CMU->LFAPRESC0 = (CMU->LFAPRESC0 & ~_CMU_LFAPRESC0_LCD_MASK) |
                       ((div - cmuClkDiv_16) << _CMU_LFAPRESC0_LCD_SHIFT);
      break;
#endif /* defined(LCD_PRESENT) */

    default:
      EFM_ASSERT(0);
      break;
    }
    break;

  case CMU_LFBPRESC0_REG:
    switch (clock)
    {
#if defined(LEUART_PRESENT)
    case cmuClock_LEUART0:
      EFM_ASSERT(div > cmuClkDiv_8);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFBPRESC0);

      CMU->LFBPRESC0 = (CMU->LFBPRESC0 & ~_CMU_LFBPRESC0_LEUART0_MASK) |
                       (((uint32_t) div) << _CMU_LFBPRESC0_LEUART0_SHIFT);
      break;

#if (LEUART_COUNT > 1)
    case cmuClock_LEUART1:
      EFM_ASSERT(div > cmuClkDiv_8);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFBPRESC0);

      CMU->LFBPRESC0 = (CMU->LFBPRESC0 & ~_CMU_LFBPRESC0_LEUART1_MASK) |
                       (((uint32_t) div) << _CMU_LFBPRESC0_LEUART1_SHIFT);
      break;
#endif /* (LEUART_COUNT > 1) */
#endif /* defined(LEUART_PRESENT) */


    default:
      EFM_ASSERT(0);
      break;
    }
    break;

  default:
    EFM_ASSERT(0);
    break;
  }
}


/***************************************************************************//**
 * @brief
 *   Enable/disable a clock.
 *
 * @details
 *   In general, module clocking is disabled after a reset. If a module
 *   clock is disabled, the registers of that module are not accessible and
 *   reading from such registers may return undefined values. Writing to
 *   registers of clock disabled modules have no effect. One should normally
 *   avoid accessing module registers of a module with a disabled clock.
 *
 * @note
 *   If enabling/disabling a LF clock, synchronization into the low frequency
 *   domain is required. If the same register is modified before a previous
 *   update has completed, this function will stall until the previous
 *   synchronization has completed. Please refer to CMU_FreezeEnable() for
 *   a suggestion on how to reduce stalling time in some use cases.
 *
 * @param[in] clock
 *   The clock to enable/disable. Notice that not all defined clock
 *   points have separate enable/disable control, please refer to CMU overview
 *   in reference manual.
 *
 * @param[in] enable
 *   @li true - enable specified clock.
 *   @li false - disable specified clock.
 ******************************************************************************/
void CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable)
{
  volatile uint32_t *reg;
  uint32_t          bit;
  uint32_t          sync = 0;

  /* Identify enable register */
  switch ((clock >> CMU_EN_REG_POS) & CMU_EN_REG_MASK)
  {
  case CMU_HFPERCLKDIV_EN_REG:
    reg = &(CMU->HFPERCLKDIV);
    break;

  case CMU_HFPERCLKEN0_EN_REG:
    reg = &(CMU->HFPERCLKEN0);
    break;

  case CMU_HFCORECLKEN0_EN_REG:
    reg = &(CMU->HFCORECLKEN0);
    break;

  case CMU_LFACLKEN0_EN_REG:
    reg  = &(CMU->LFACLKEN0);
    sync = CMU_SYNCBUSY_LFACLKEN0;
    break;

  case CMU_LFBCLKEN0_EN_REG:
    reg  = &(CMU->LFBCLKEN0);
    sync = CMU_SYNCBUSY_LFBCLKEN0;
    break;

  case CMU_PCNT_EN_REG:
    reg = &(CMU->PCNTCTRL);
    break;

  default: /* Cannot enable/disable clock point */
    EFM_ASSERT(0);
    return;
  }

  /* Get bit position used to enable/disable */
  bit = (clock >> CMU_EN_BIT_POS) & CMU_EN_BIT_MASK;

  /* LF synchronization required? */
  if (sync)
  {
    CMU_Sync(sync);
  }

  /* Set/clear bit as requested */
  BITBAND_Peripheral(reg, bit, (unsigned int) enable);
}


/***************************************************************************//**
 * @brief
 *   Get clock frequency for a clock point.
 *
 * @param[in] clock
 *   Clock point to fetch frequency for.
 *
 * @return
 *   The current frequency in Hz.
 ******************************************************************************/
uint32_t CMU_ClockFreqGet(CMU_Clock_TypeDef clock)
{
  uint32_t ret;

  switch (clock)
  {
  case cmuClock_HF:
    ret = SystemHFClockGet();
    break;

  case cmuClock_HFPER:
#if defined(USART_COUNT) && (USART_COUNT > 0)
  case cmuClock_USART0:
#endif
#if defined(USART_COUNT) && (USART_COUNT > 1)
  case cmuClock_USART1:
#endif
#if defined(USART_COUNT) && (USART_COUNT > 2)
  case cmuClock_USART2:
#endif
#if defined(UART_COUNT) && (UART_COUNT > 0)
  case cmuClock_UART0:
#endif
#if defined(TIMER_COUNT) && (TIMER_COUNT > 0)
  case cmuClock_TIMER0:
#endif
#if defined(TIMER_COUNT) && (TIMER_COUNT > 1)
  case cmuClock_TIMER1:
#endif
#if defined(TIMER_COUNT) && (TIMER_COUNT > 2)
  case cmuClock_TIMER2:
#endif
#if defined(ACMP_COUNT) && (ACMP_COUNT > 0)
  case cmuClock_ACMP0:
#endif
#if defined(ACMP_COUNT) && (ACMP_COUNT > 1)
  case cmuClock_ACMP1:
#endif
#if defined(PRS_PRESENT)
  case cmuClock_PRS:
#endif
#if defined(DAC_COUNT) && (DAC_COUNT > 0)
  case cmuClock_DAC0:
#endif
#if defined(GPIO_PRESENT)
  case cmuClock_GPIO:
#endif
#if defined(VCMP_PRESENT)
  case cmuClock_VCMP:
#endif
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
  case cmuClock_ADC0:
#endif
#if defined(I2C_COUNT) && (I2C_COUNT > 0)
  case cmuClock_I2C0:
    ret   = SystemHFClockGet();
    ret >>= (CMU->HFPERCLKDIV & _CMU_HFPERCLKDIV_HFPERCLKDIV_MASK) >>
            _CMU_HFPERCLKDIV_HFPERCLKDIV_SHIFT;
    break;
#endif
  case cmuClock_CORE:
#if defined(AES_PRESENT)
  case cmuClock_AES:
#endif
#if defined(DMA_PRESENT)
  case cmuClock_DMA:
#endif
  case cmuClock_CORELE:
#if defined(EBI_PRESENT)
  case cmuClock_EBI:
#endif
    ret = SystemCoreClockGet();
    break;

  case cmuClock_LFA:
    ret = CMU_LFClkGet(CMU_LFA);
    break;
#if defined(RTC_PRESENT)
  case cmuClock_RTC:
    ret   = CMU_LFClkGet(CMU_LFA);
    ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_RTC_MASK) >>
            _CMU_LFAPRESC0_RTC_SHIFT;
    break;
#endif

#if defined(LETIMER_COUNT) && (LETIMER_COUNT > 0)
  case cmuClock_LETIMER0:
    ret   = CMU_LFClkGet(CMU_LFA);
    ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_LETIMER0_MASK) >>
            _CMU_LFAPRESC0_LETIMER0_SHIFT;
    break;
#endif

#if defined(LCD_PRESENT)
  case cmuClock_LCDpre:
    ret   = CMU_LFClkGet(CMU_LFA);
    ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_LCD_MASK) >>
            _CMU_LFAPRESC0_LCD_SHIFT;
    break;

  case cmuClock_LCD:
    ret   = CMU_LFClkGet(CMU_LFA);
    ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_LCD_MASK) >>
            _CMU_LFAPRESC0_LCD_SHIFT;
    ret /= (1 + ((CMU->LCDCTRL & _CMU_LCDCTRL_FDIV_MASK) >>
                 _CMU_LCDCTRL_FDIV_SHIFT));
    break;
#endif /* defined(LCD_PRESENT) */

#if defined(PCNT_COUNT) && (PCNT_COUNT > 0)
  case cmuClock_PCNT0:
#endif
#if defined(PCNT_COUNT) && (PCNT_COUNT > 1)
  case cmuClock_PCNT1:
#endif
#if defined(PCNT_COUNT) && (PCNT_COUNT > 2)
  case cmuClock_PCNT2:
#endif
#if (PCNT_COUNT > 3)
#error Add support for more PCNT instances
#endif
    ret = CMU_LFClkGet(CMU_LFA);
    break;

  case cmuClock_LFB:
    ret = CMU_LFClkGet(CMU_LFB);
    break;

#if defined(LEUART_COUNT) && (LEUART_COUNT > 0)
  case cmuClock_LEUART0:
    ret   = CMU_LFClkGet(CMU_LFB);
    ret >>= (CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART0_MASK) >>
            _CMU_LFBPRESC0_LEUART0_SHIFT;
    break;
#endif

#if defined(LEUART_COUNT) && (LEUART_COUNT > 1)
  case cmuClock_LEUART1:
    ret   = CMU_LFClkGet(CMU_LFB);
    ret >>= (CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART1_MASK) >>
            _CMU_LFBPRESC0_LEUART1_SHIFT;
    break;
#endif /* LEUART_COUNT > 1) */

#if (LEUART_COUNT > 2)
#error Add support for more LEUART instances
#endif

  default:
    EFM_ASSERT(0);
    ret = 0;
    break;
  }
  return ret;
}


/**************************************************************************//**
 * @brief
 *   Get currently selected reference clock used for a clock branch.
 *
 * @param[in] clock
 *   Clock branch to fetch selected ref. clock for. One of:
 *   @li #cmuClock_HF
 *   @li #cmuClock_LFA
 *   @li #cmuClock_LFB
 *
 * @return
 *   Reference clock used for clocking selected branch, #cmuSelect_Error if
 *   invalid @p clock provided.
 *****************************************************************************/
CMU_Select_TypeDef CMU_ClockSelectGet(CMU_Clock_TypeDef clock)
{
  CMU_Select_TypeDef ret;
  uint32_t           selReg;

  selReg = (clock >> CMU_SEL_REG_POS) & CMU_SEL_REG_MASK;

  switch (selReg)
  {
  case CMU_HFCLKSEL_REG:
    switch (CMU->STATUS & (CMU_STATUS_HFRCOSEL | CMU_STATUS_HFXOSEL |
                           CMU_STATUS_LFRCOSEL | CMU_STATUS_LFXOSEL))
    {
    case CMU_STATUS_LFXOSEL:
      ret = cmuSelect_LFXO;
      break;

    case CMU_STATUS_LFRCOSEL:
      ret = cmuSelect_LFRCO;
      break;

    case CMU_STATUS_HFXOSEL:
      ret = cmuSelect_HFXO;
      break;

    default:
      ret = cmuSelect_HFRCO;
      break;
    }
    break;

  case CMU_LFACLKSEL_REG:
    switch (CMU->LFCLKSEL & _CMU_LFCLKSEL_LFA_MASK)
    {
    case _CMU_LFCLKSEL_LFA_LFRCO:
      ret = cmuSelect_LFRCO;
      break;

    case _CMU_LFCLKSEL_LFA_LFXO:
      ret = cmuSelect_LFXO;
      break;

    case _CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2:
      ret = cmuSelect_CORELEDIV2;
      break;

    default:
      ret = cmuSelect_Disabled;
      break;
    }
    break;

  case CMU_LFBCLKSEL_REG:
    switch (CMU->LFCLKSEL & _CMU_LFCLKSEL_LFB_MASK)
    {
    case _CMU_LFCLKSEL_LFB_LFRCO:
      ret = cmuSelect_LFRCO;
      break;

    case _CMU_LFCLKSEL_LFB_LFXO:
      ret = cmuSelect_LFXO;
      break;

    case _CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2:
      ret = cmuSelect_CORELEDIV2;
      break;

    default:
      ret = cmuSelect_Disabled;
      break;
    }
    break;

  default:
    EFM_ASSERT(0);
    ret = cmuSelect_Error;
    break;
  }

  return ret;
}


/**************************************************************************//**
 * @brief
 *   Select reference clock/oscillator used for a clock branch.
 *
 * @details
 *   Notice that if a selected reference is not enabled prior to selecting its
 *   use, it will be enabled, and this function will wait for the selected
 *   oscillator to be stable. It will however NOT be disabled if another
 *   reference clock is selected later.
 *
 *   This feature is particularly important if selecting a new reference
 *   clock for the clock branch clocking the core, otherwise the system
 *   may halt.
 *
 * @param[in] clock
 *   Clock branch to select reference clock for. One of:
 *   @li #cmuClock_HF
 *   @li #cmuClock_LFA
 *   @li #cmuClock_LFB
 *
 * @param[in] ref
 *   Reference selected for clocking, please refer to reference manual for
 *   for details on which reference is available for a specific clock branch.
 *****************************************************************************/
void CMU_ClockSelectSet(CMU_Clock_TypeDef clock, CMU_Select_TypeDef ref)
{
  uint32_t        select;
  CMU_Osc_TypeDef osc;
  uint32_t        freq;
  uint32_t        selReg;
  uint32_t        lfShift;
  uint32_t        tmp;

  selReg = (clock >> CMU_SEL_REG_POS) & CMU_SEL_REG_MASK;

  switch (selReg)
  {
  case CMU_HFCLKSEL_REG:
    switch (ref)
    {
    case cmuSelect_LFXO:
      select = CMU_CMD_HFCLKSEL_LFXO;
      osc    = cmuOsc_LFXO;
      break;

    case cmuSelect_LFRCO:
      select = CMU_CMD_HFCLKSEL_LFRCO;
      osc    = cmuOsc_LFRCO;
      break;

    case cmuSelect_HFXO:
      select = CMU_CMD_HFCLKSEL_HFXO;
      osc    = cmuOsc_HFXO;
      break;

    case cmuSelect_HFRCO:
      select = CMU_CMD_HFCLKSEL_HFRCO;
      osc    = cmuOsc_HFRCO;
      break;

    default:
      EFM_ASSERT(0);
      return;
    }

    /* Ensure selected oscillator is enabled, waiting for it to stabilize */
    CMU_OscillatorEnable(osc, true, true);

    /* Configure worst case wait states for flash access before selecting */
    CMU_FlashWaitStateControl(CMU_MAX_FREQ_0WS + 1);

    /* Switch to selected oscillator */
    CMU->CMD = select;

    /* Keep EMU module informed */
    EMU_UpdateOscConfig();

    /* Update CMSIS core clock variable */
    /* (The function will update the global variable) */
    freq = SystemCoreClockGet();

    /* Optimize flash access wait state setting for currently selected core clk */
    CMU_FlashWaitStateControl(freq);
    break;

  case CMU_LFACLKSEL_REG:
  case CMU_LFBCLKSEL_REG:
    if (selReg == CMU_LFACLKSEL_REG)
      lfShift = _CMU_LFCLKSEL_LFA_SHIFT;
    else
      lfShift = _CMU_LFCLKSEL_LFB_SHIFT;

    switch (ref)
    {
    case cmuSelect_Disabled:
      tmp = _CMU_LFCLKSEL_LFA_DISABLED;
      break;

    case cmuSelect_LFXO:
      /* Ensure selected oscillator is enabled, waiting for it to stabilize */
      CMU_OscillatorEnable(cmuOsc_LFXO, true, true);
      tmp = _CMU_LFCLKSEL_LFA_LFXO;
      break;

    case cmuSelect_LFRCO:
      /* Ensure selected oscillator is enabled, waiting for it to stabilize */
      CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);
      tmp = _CMU_LFCLKSEL_LFA_LFRCO;
      break;

    case cmuSelect_CORELEDIV2:
      /* Ensure HFCORE to LE clocking is enabled */
      BITBAND_Peripheral(&(CMU->HFCORECLKEN0), _CMU_HFCORECLKEN0_LE_SHIFT, 1);
      tmp = _CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2;
      break;

    default:
      EFM_ASSERT(0);
      return;
    }
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~(_CMU_LFCLKSEL_LFA_MASK << lfShift)) |
                    (tmp << lfShift);
    break;

  default:
    EFM_ASSERT(0);
    break;
  }
}


/**************************************************************************//**
 * @brief
 *   CMU low frequency register synchronization freeze control.
 *
 * @details
 *   Some CMU registers requires synchronization into the low frequency (LF)
 *   domain. The freeze feature allows for several such registers to be
 *   modified before passing them to the LF domain simultaneously (which
 *   takes place when the freeze mode is disabled).
 *
 *   Another usage scenario of this feature, is when using an API (such
 *   as the CMU API) for modifying several bit fields consecutively in the
 *   same register. If freeze mode is enabled during this sequence, stalling
 *   can be avoided.
 *
 * @note
 *   When enabling freeze mode, this function will wait for all current
 *   ongoing CMU synchronization to LF domain to complete (Normally
 *   synchronization will not be in progress.) However for this reason, when
 *   using freeze mode, modifications of registers requiring LF synchronization
 *   should be done within one freeze enable/disable block to avoid unecessary
 *   stalling.
 *
 * @param[in] enable
 *   @li true - enable freeze, modified registers are not propagated to the
 *       LF domain
 *   @li false - disable freeze, modified registers are propagated to LF
 *       domain
 *****************************************************************************/
void CMU_FreezeEnable(bool enable)
{
  if (enable)
  {
    /*
     * Wait for any ongoing LF synchronization to complete. This is just to
     * protect against the rare case when a user
     * - modifies a register requiring LF sync
     * - then enables freeze before LF sync completed
     * - then modifies the same register again
     * since modifying a register while it is in sync progress should be
     * avoided.
     */
    while (CMU->SYNCBUSY) ;

    CMU->FREEZE = CMU_FREEZE_REGFREEZE;
  }
  else
  {
    CMU->FREEZE = 0;
  }
}


/***************************************************************************//**
 * @brief
 *   Get HFRCO band in use.
 *
 * @return
 *   HFRCO band in use.
 ******************************************************************************/
CMU_HFRCOBand_TypeDef CMU_HFRCOBandGet(void)
{
  return (CMU_HFRCOBand_TypeDef)((CMU->HFRCOCTRL & _CMU_HFRCOCTRL_BAND_MASK) >>
                                 _CMU_HFRCOCTRL_BAND_SHIFT);
}


/***************************************************************************//**
 * @brief
 *   Set HFRCO band and the tuning value based on the value in the calibration
 *   table made during production.
 *
 * @param[in] band
 *   HFRCO band to activate.
 ******************************************************************************/
void CMU_HFRCOBandSet(CMU_HFRCOBand_TypeDef band)
{
  uint32_t           tuning;
  uint32_t           freq;
  CMU_Select_TypeDef osc;

  /* Read tuning value from calibration table */
  switch (band)
  {
  case cmuHFRCOBand_1MHz:
    tuning = (DEVINFO->HFRCOCAL0 & _DEVINFO_HFRCOCAL0_BAND1_MASK) >>
             _DEVINFO_HFRCOCAL0_BAND1_SHIFT;
    break;

  case cmuHFRCOBand_7MHz:
    tuning = (DEVINFO->HFRCOCAL0 & _DEVINFO_HFRCOCAL0_BAND7_MASK) >>
             _DEVINFO_HFRCOCAL0_BAND7_SHIFT;
    break;

  case cmuHFRCOBand_11MHz:
    tuning = (DEVINFO->HFRCOCAL0 & _DEVINFO_HFRCOCAL0_BAND11_MASK) >>
             _DEVINFO_HFRCOCAL0_BAND11_SHIFT;
    break;

  case cmuHFRCOBand_14MHz:
    tuning = (DEVINFO->HFRCOCAL0 & _DEVINFO_HFRCOCAL0_BAND14_MASK) >>
             _DEVINFO_HFRCOCAL0_BAND14_SHIFT;
    break;

  case cmuHFRCOBand_21MHz:
    tuning = (DEVINFO->HFRCOCAL1 & _DEVINFO_HFRCOCAL1_BAND21_MASK) >>
             _DEVINFO_HFRCOCAL1_BAND21_SHIFT;
    break;

  case cmuHFRCOBand_28MHz:
    tuning = (DEVINFO->HFRCOCAL1 & _DEVINFO_HFRCOCAL1_BAND28_MASK) >>
             _DEVINFO_HFRCOCAL1_BAND28_SHIFT;
    break;

  default:
    EFM_ASSERT(0);
    return;
  }

  /* If HFRCO is used for core clock, we have to consider flash access WS. */
  osc = CMU_ClockSelectGet(cmuClock_HF);
  if (osc == cmuSelect_HFRCO)
  {
    /* Configure worst case wait states for flash access before setting divider */
    CMU_FlashWaitStateControl(CMU_MAX_FREQ_0WS + 1);
  }

  /* Set band/tuning */
  CMU->HFRCOCTRL = (CMU->HFRCOCTRL &
                    ~(_CMU_HFRCOCTRL_BAND_MASK | _CMU_HFRCOCTRL_TUNING_MASK)) |
                   (band << _CMU_HFRCOCTRL_BAND_SHIFT) |
                   (tuning << _CMU_HFRCOCTRL_TUNING_SHIFT);

  /* If HFRCO is used for core clock, optimize flash WS */
  if (osc == cmuSelect_HFRCO)
  {
    /* Update CMSIS core clock variable and get current core clock */
    /* (The function will update the global variable) */
    /* NOTE! We need at least 21 cycles before setting zero wait state to flash */
    /* (i.e. WS0) when going from the 28MHz to 1MHz in the HFRCO band */
    freq = SystemCoreClockGet();

    /* Optimize flash access wait state setting for current core clk */
    CMU_FlashWaitStateControl(freq);
  }
}


/***************************************************************************//**
 * @brief
 *   Get the HFRCO startup delay.
 *
 * @details
 *   Please refer to the reference manual for further details.
 *
 * @return
 *   The startup delay in use.
 ******************************************************************************/
uint32_t CMU_HFRCOStartupDelayGet(void)
{
  return((CMU->HFRCOCTRL & _CMU_HFRCOCTRL_SUDELAY_MASK) >>
         _CMU_HFRCOCTRL_SUDELAY_SHIFT);
}


/***************************************************************************//**
 * @brief
 *   Set the HFRCO startup delay.
 *
 * @details
 *   Please refer to the reference manual for further details.
 *
 * @param[in] delay
 *   The startup delay to set (<= 31).
 ******************************************************************************/
void CMU_HFRCOStartupDelaySet(uint32_t delay)
{
  EFM_ASSERT(delay <= 31);

  delay         &= (_CMU_HFRCOCTRL_SUDELAY_MASK >> _CMU_HFRCOCTRL_SUDELAY_SHIFT);
  CMU->HFRCOCTRL = (CMU->HFRCOCTRL & ~(_CMU_HFRCOCTRL_SUDELAY_MASK)) |
                   (delay << _CMU_HFRCOCTRL_SUDELAY_SHIFT);
}


/***************************************************************************//**
 * @brief
 *   Get the LCD framerate divisor (FDIV) setting.
 *
 * @return
 *   The LCD framerate divisor.
 ******************************************************************************/
uint32_t CMU_LCDClkFDIVGet(void)
{
#if defined(LCD_PRESENT)
  return((CMU->LCDCTRL & _CMU_LCDCTRL_FDIV_MASK) >> _CMU_LCDCTRL_FDIV_SHIFT);
#else
  return 0;
#endif /* defined(LCD_PRESENT) */
}


/***************************************************************************//**
 * @brief
 *   Set the LCD framerate divisor (FDIV) setting.
 *
 * @note
 *   The FDIV field (CMU LCDCTRL register) should only be modified while the
 *   LCD module is clock disabled (CMU LFACLKEN0.LCD bit is 0). This function
 *   will NOT modify FDIV if the LCD module clock is enabled. Please refer to
 *   CMU_ClockEnable() for disabling/enabling LCD clock.
 *
 * @param[in] div
 *   The FDIV setting to use.
 ******************************************************************************/
void CMU_LCDClkFDIVSet(uint32_t div)
{
#if defined(LCD_PRESENT)
  EFM_ASSERT(div <= cmuClkDiv_128);

  /* Do not allow modification if LCD clock enabled */
  if (CMU->LFACLKEN0 & CMU_LFACLKEN0_LCD)
  {
    return;
  }

  div        <<= _CMU_LCDCTRL_FDIV_SHIFT;
  div         &= _CMU_LCDCTRL_FDIV_MASK;
  CMU->LCDCTRL = (CMU->LCDCTRL & ~_CMU_LCDCTRL_FDIV_MASK) | div;
#else
  (void) div; /* Unused parameter */
#endif /* defined(LCD_PRESENT) */
}


/***************************************************************************//**
 * @brief
 *   Enable/disable oscillator.
 *
 * @param[in] osc
 *   The oscillator to enable/disable.
 *
 * @param[in] enable
 *   @li true - enable specified oscillator.
 *   @li false - disable specified oscillator.
 *
 * @param[in] wait
 *   Only used if @p enable is true.
 *   @li true - wait for oscillator start-up time to timeout before returning.
 *   @li false - do not wait for oscillator start-up time to timeout before
 *     returning.
 ******************************************************************************/
void CMU_OscillatorEnable(CMU_Osc_TypeDef osc, bool enable, bool wait)
{
  uint32_t status;
  uint32_t enBit;
  uint32_t disBit;

  switch (osc)
  {
  case cmuOsc_HFRCO:
    enBit  = CMU_OSCENCMD_HFRCOEN;
    disBit = CMU_OSCENCMD_HFRCODIS;
    status = CMU_STATUS_HFRCORDY;
    break;

  case cmuOsc_HFXO:
    enBit  = CMU_OSCENCMD_HFXOEN;
    disBit = CMU_OSCENCMD_HFXODIS;
    status = CMU_STATUS_HFXORDY;
    break;

  case cmuOsc_AUXHFRCO:
    enBit  = CMU_OSCENCMD_AUXHFRCOEN;
    disBit = CMU_OSCENCMD_AUXHFRCODIS;
    status = CMU_STATUS_AUXHFRCORDY;
    break;

  case cmuOsc_LFRCO:
    enBit  = CMU_OSCENCMD_LFRCOEN;
    disBit = CMU_OSCENCMD_LFRCODIS;
    status = CMU_STATUS_LFRCORDY;
    break;

  case cmuOsc_LFXO:
    enBit  = CMU_OSCENCMD_LFXOEN;
    disBit = CMU_OSCENCMD_LFXODIS;
    status = CMU_STATUS_LFXORDY;
    break;

  default:
    /* Undefined clock source */
    EFM_ASSERT(0);
    return;
  }

  if (enable)
  {
    CMU->OSCENCMD = enBit;

    /* Wait for clock to stabilize if requested */
    if (wait)
    {
      while (!(CMU->STATUS & status)) ;
    }
  }
  else
  {
    CMU->OSCENCMD = disBit;
  }

  /* Keep EMU module informed */
  EMU_UpdateOscConfig();
}


/***************************************************************************//**
 * @brief
 *   Get oscillator frequency tuning setting.
 *
 * @param[in] osc
 *   Oscillator to get tuning value for, one of:
 *   @li #cmuOsc_LFRCO
 *   @li #cmuOsc_HFRCO
 *   @li #cmuOsc_AUXHFRCO
 *
 * @return
 *   The oscillator frequency tuning setting in use.
 ******************************************************************************/
uint32_t CMU_OscillatorTuningGet(CMU_Osc_TypeDef osc)
{
  uint32_t ret;

  switch (osc)
  {
  case cmuOsc_LFRCO:
    ret = (CMU->LFRCOCTRL & _CMU_LFRCOCTRL_TUNING_MASK) >>
          _CMU_LFRCOCTRL_TUNING_SHIFT;
    break;

  case cmuOsc_HFRCO:
    ret = (CMU->HFRCOCTRL & _CMU_HFRCOCTRL_TUNING_MASK) >>
          _CMU_HFRCOCTRL_TUNING_SHIFT;
    break;

  case cmuOsc_AUXHFRCO:
    ret = (CMU->AUXHFRCOCTRL & _CMU_AUXHFRCOCTRL_TUNING_MASK) >>
          _CMU_AUXHFRCOCTRL_TUNING_SHIFT;
    break;

  default:
    EFM_ASSERT(0);
    ret = 0;
    break;
  }

  return(ret);
}


/***************************************************************************//**
 * @brief
 *   Set the oscillator frequency tuning control.
 *
 * @note
 *   Oscillator tuning is done during production, and the tuning value is
 *   automatically loaded after a reset. Changing the tuning value from the
 *   calibrated value is for more advanced use.
 *
 * @param[in] osc
 *   Oscillator to set tuning value for, one of:
 *   @li #cmuOsc_LFRCO
 *   @li #cmuOsc_HFRCO
 *   @li #cmuOsc_AUXHFRCO
 *
 * @param[in] val
 *   The oscillator frequency tuning setting to use.
 ******************************************************************************/
void CMU_OscillatorTuningSet(CMU_Osc_TypeDef osc, uint32_t val)
{
  switch (osc)
  {
  case cmuOsc_LFRCO:
    EFM_ASSERT(val <= (_CMU_LFRCOCTRL_TUNING_MASK >> _CMU_LFRCOCTRL_TUNING_SHIFT));

    val           &= (_CMU_LFRCOCTRL_TUNING_MASK >> _CMU_LFRCOCTRL_TUNING_SHIFT);
    CMU->LFRCOCTRL = (CMU->LFRCOCTRL & ~(_CMU_LFRCOCTRL_TUNING_MASK)) |
                     (val << _CMU_LFRCOCTRL_TUNING_SHIFT);
    break;

  case cmuOsc_HFRCO:
    EFM_ASSERT(val <= (_CMU_HFRCOCTRL_TUNING_MASK >> _CMU_HFRCOCTRL_TUNING_SHIFT));

    val           &= (_CMU_HFRCOCTRL_TUNING_MASK >> _CMU_HFRCOCTRL_TUNING_SHIFT);
    CMU->HFRCOCTRL = (CMU->HFRCOCTRL & ~(_CMU_HFRCOCTRL_TUNING_MASK)) |
                     (val << _CMU_HFRCOCTRL_TUNING_SHIFT);
    break;

  case cmuOsc_AUXHFRCO:
    EFM_ASSERT(val <= (_CMU_AUXHFRCOCTRL_TUNING_MASK >> _CMU_AUXHFRCOCTRL_TUNING_SHIFT));

    val             <<= _CMU_AUXHFRCOCTRL_TUNING_SHIFT;
    val              &= _CMU_AUXHFRCOCTRL_TUNING_MASK;
    CMU->AUXHFRCOCTRL = (CMU->AUXHFRCOCTRL & ~(_CMU_AUXHFRCOCTRL_TUNING_MASK)) | val;
    break;

  default:
    EFM_ASSERT(0);
    break;
  }
}


/**************************************************************************//**
 * @brief
 *   Determine if currently selected PCNTn clock used is external or LFBCLK.
 *
 * @param[in] inst
 *   PCNT instance number to get currently selected clock source for.
 *
 * @return
 *   @li true - selected clock is external clock.
 *   @li false - selected clock is LFBCLK.
 *****************************************************************************/
bool CMU_PCNTClockExternalGet(unsigned int inst)
{
  bool     ret;
  uint32_t setting;

  switch (inst)
  {
#if defined(PCNT_PRESENT)
  case 0:
    setting = CMU->PCNTCTRL & CMU_PCNTCTRL_PCNT0CLKSEL_PCNT0S0;
    break;

#if (PCNT_COUNT > 1)
  case 1:
    setting = CMU->PCNTCTRL & CMU_PCNTCTRL_PCNT1CLKSEL_PCNT1S0;
    break;

#if (PCNT_COUNT > 2)
  case 2:
    setting = CMU->PCNTCTRL & CMU_PCNTCTRL_PCNT2CLKSEL_PCNT2S0;
    break;
#endif
#endif
#endif

  default:
    setting = 0;
    break;
  }

  if (setting)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }
  return ret;
}


/**************************************************************************//**
 * @brief
 *   Select PCNTn clock.
 *
 * @param[in] inst
 *   PCNT instance number to set selected clock source for.
 *
 * @param[in] external
 *   Set to true to select external clock, false to select LFBCLK.
 *****************************************************************************/
void CMU_PCNTClockExternalSet(unsigned int inst, bool external)
{
#if defined(PCNT_PRESENT)
  uint32_t setting = 0;

  EFM_ASSERT(inst < PCNT_COUNT);

  if (external)
  {
    setting = 1;
  }

  BITBAND_Peripheral(&(CMU->PCNTCTRL), (inst * 2) + 1, setting);

#else
  (void) inst;     /* Unused parameter */
  (void) external; /* Unused parameter */
#endif
}


/** @} (end addtogroup CMU) */
/** @} (end addtogroup EFM32_Library) */
