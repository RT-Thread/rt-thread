/***************************************************************************//**
 * @file
 * @brief Clock management unit (CMU) Peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
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
#include "em_part.h"
#include "em_cmu.h"
#include "em_assert.h"
#include "em_bitband.h"
#include "em_emu.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup CMU
 * @brief Clock management unit (CMU) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** Maximum allowed core frequency when using 0 wait states on flash access. */
#define CMU_MAX_FREQ_0WS    16000000
/** Maximum allowed core frequency when using 1 wait states on flash access */
#define CMU_MAX_FREQ_1WS    32000000
/** Maximum frequency before HFLE needs to be enabled on Giant Gecko */
#define CMU_MAX_FREQ_HFLE   32000000

/** Low frequency A group identifier */
#define CMU_LFA             0

/** Low frequency B group identifier */
#define CMU_LFB             1

/** @endcond */

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *   Configure flash access wait states to most conservative setting for
 *   this target. Retain SCBTP setting.
 ******************************************************************************/
static void CMU_FlashWaitStateMax(void)
{
  uint32_t cfg;

  cfg = MSC->READCTRL;

  switch(cfg & _MSC_READCTRL_MODE_MASK)
  {
  case MSC_READCTRL_MODE_WS1:
  case MSC_READCTRL_MODE_WS0:
#if defined(_EFM32_GIANT_FAMILY)
  case MSC_READCTRL_MODE_WS2:
    cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS2;
#else
    cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS1;
#endif
    break;
  case MSC_READCTRL_MODE_WS1SCBTP:
  case MSC_READCTRL_MODE_WS0SCBTP:
#if defined(_EFM32_GIANT_FAMILY)
  case MSC_READCTRL_MODE_WS2SCBTP:
    cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS2SCBTP;
#else
    cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS1SCBTP;
#endif
    break;
  }
  MSC->READCTRL = cfg;
}


/***************************************************************************//**
 * @brief Convert dividend to prescaler logarithmic value. Only works for even
 *        numbers equal to 2^n
 * @param[in] div Unscaled dividend,
 * @return Base 2 logarithm of input, as used by fixed prescalers
 ******************************************************************************/
__STATIC_INLINE uint32_t CMU_DivToLog2(CMU_ClkDiv_TypeDef div)
{
  uint32_t log2;

  /* Prescalers take argument of 32768 or less */
  EFM_ASSERT((div>0) && (div <= 32768));

  /* Count leading zeroes and "reverse" result, Cortex-M3 intrinsic */
  log2 = (31 - __CLZ(div));

  return log2;
}


/***************************************************************************//**
 * @brief Convert logarithm of 2 prescaler to division factor
 * @param[in] log2
 * @return Dividend
 ******************************************************************************/
__STATIC_INLINE uint32_t CMU_Log2ToDiv(uint32_t log2)
{
  return 1<<log2;
}


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

  cfg = MSC->READCTRL;

#if defined(_EFM32_GIANT_FAMILY)
  if (hfcoreclk > CMU_MAX_FREQ_1WS)
  {
    switch(cfg & _MSC_READCTRL_MODE_MASK)
    {
    case MSC_READCTRL_MODE_WS0SCBTP:
    case MSC_READCTRL_MODE_WS1SCBTP:
      cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS2SCBTP;
      break;
    case MSC_READCTRL_MODE_WS0:
    case MSC_READCTRL_MODE_WS1:
    default:
      cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS2;
      break;
    }
  }
#endif

  if ((hfcoreclk > CMU_MAX_FREQ_0WS) && (hfcoreclk <= CMU_MAX_FREQ_1WS))
  {
    switch (cfg & _MSC_READCTRL_MODE_MASK)
    {
#if defined(_EFM32_GIANT_FAMILY)
    case MSC_READCTRL_MODE_WS2SCBTP:
#endif
    case MSC_READCTRL_MODE_WS0SCBTP:
    case MSC_READCTRL_MODE_WS1SCBTP:
      cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS1SCBTP;
      break;

    default:
      cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS1;
      break;
    }
  }

  if (hfcoreclk <= CMU_MAX_FREQ_0WS)
  {
    switch (cfg & _MSC_READCTRL_MODE_MASK)
    {
#if defined(_EFM32_GIANT_FAMILY)
    case MSC_READCTRL_MODE_WS2SCBTP:
#endif
    case MSC_READCTRL_MODE_WS1SCBTP:
    case MSC_READCTRL_MODE_WS0SCBTP:
      cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS0SCBTP;
      break;

    default:
      cfg = (cfg & ~_MSC_READCTRL_MODE_MASK) | MSC_READCTRL_MODE_WS0;
      break;
    }
  }

  MSC->READCTRL = cfg;
}


#if defined(USB_PRESENT)
/***************************************************************************//**
 * @brief
 *   Get the USBC frequency
 *
 * @return
 *   USBC frequency in Hz
 ******************************************************************************/
static uint32_t CMU_USBCClkGet(void)
{
  uint32_t ret;
  CMU_Select_TypeDef clk;

  /* Get selected clock source */
  clk = CMU_ClockSelectGet(cmuClock_USBC);

  switch(clk)
  {
  case cmuSelect_LFXO:
    ret = SystemLFXOClockGet();
    break;
  case cmuSelect_LFRCO:
    ret = SystemLFRCOClockGet();
    break;
  case cmuSelect_HFCLK:
    ret = SystemHFClockGet();
    break;
  default:
    /* Clock is not enabled */
    ret = 0;
    break;
  }
  return ret;
}
#endif


/***************************************************************************//**
 * @brief
 *   Get the AUX clock frequency. Used by MSC flash programming and LESENSE,
 *   by default also as debug clock.
 *
 * @return
 *   AUX Frequency in Hz
 ******************************************************************************/
static uint32_t CMU_AUXClkGet(void)
{
  uint32_t ret;

#if defined (_EFM32_GECKO_FAMILY)
  /* Gecko has a fixed 14Mhz AUXHFRCO clock */
  ret = 14000000;
#else
  switch(CMU->AUXHFRCOCTRL & _CMU_AUXHFRCOCTRL_BAND_MASK)
  {
  case CMU_AUXHFRCOCTRL_BAND_1MHZ:
    ret = 1000000;
    break;
  case CMU_AUXHFRCOCTRL_BAND_7MHZ:
    ret = 7000000;
    break;
  case CMU_AUXHFRCOCTRL_BAND_11MHZ:
    ret = 11000000;
    break;
  case CMU_AUXHFRCOCTRL_BAND_14MHZ:
    ret = 14000000;
    break;
  case CMU_AUXHFRCOCTRL_BAND_21MHZ:
    ret = 21000000;
    break;
  case CMU_AUXHFRCOCTRL_BAND_28MHZ:
    ret = 28000000;
    break;
  default:
    ret = 0;
    break;
  }
#endif
  return ret;
}


/***************************************************************************//**
 * @brief
 *   Get the Debug Trace clock frequency
 *
 * @return
 *   Debug Trace frequency in Hz
 ******************************************************************************/
static uint32_t CMU_DBGClkGet(void)
{
  uint32_t ret;
  CMU_Select_TypeDef clk;

  /* Get selected clock source */
  clk = CMU_ClockSelectGet(cmuClock_DBG);

  switch(clk)
  {
  case cmuSelect_HFCLK:
    ret = SystemHFClockGet();
#if defined(_EFM32_GIANT_FAMILY)
    /* Giant Gecko has an additional divider, not used by USBC */
    ret = ret / (1 + ((CMU->CTRL & _CMU_CTRL_HFCLKDIV_MASK) >>
                      _CMU_CTRL_HFCLKDIV_SHIFT));
#endif
    break;

  case cmuSelect_AUXHFRCO:
    ret = CMU_AUXClkGet();
    break;

  default:
    EFM_ASSERT(0);
    ret = 0;
    break;
  }
  return ret;
}


/***************************************************************************//**
 * @brief
 *   Get the LFnCLK frequency based on current configuration.
 *
 * @param[in] lfClkBranch
 *   LF branch, 0 = LFA, 1 = LFB, ...
 *
 * @return
 *   The LFnCLK frequency in Hz. If no LFnCLK is selected (disabled), 0 is
 *   returned.
 ******************************************************************************/
static uint32_t CMU_LFClkGet(unsigned int lfClkBranch)
{
  uint32_t ret;

  EFM_ASSERT(lfClkBranch == CMU_LFA || lfClkBranch == CMU_LFB);

  switch ((CMU->LFCLKSEL >> (lfClkBranch * 2)) & 0x3)
  {
  case _CMU_LFCLKSEL_LFA_LFRCO:
    ret = SystemLFRCOClockGet();
    break;

  case _CMU_LFCLKSEL_LFA_LFXO:
    ret = SystemLFXOClockGet();
    break;

  case _CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2:
#if defined (_EFM32_GIANT_FAMILY)
    /* Giant Gecko can use a /4 divider (and must if >32MHz) or HFLE is set */
    if(((CMU->HFCORECLKDIV & _CMU_HFCORECLKDIV_HFCORECLKLEDIV_MASK) == CMU_HFCORECLKDIV_HFCORECLKLEDIV_DIV4)||
       (CMU->CTRL & CMU_CTRL_HFLE))
    {
      ret = SystemCoreClockGet() / 4;
    }
    else
    {
      ret = SystemCoreClockGet() / 2;
    }
#else
    ret = SystemCoreClockGet() / 2;
#endif
    break;

  case _CMU_LFCLKSEL_LFA_DISABLED:
#if defined (_EFM32_GIANT_FAMILY) || defined (_EFM32_TINY_FAMILY)
    /* Check LF Extended bit setting for ULFRCO clock */
    if(CMU->LFCLKSEL >> (_CMU_LFCLKSEL_LFAE_SHIFT + lfClkBranch * 4))
    {
      ret = SystemULFRCOClockGet();
    }
    else
    {
      ret = 0;
    }
#else
    ret = 0;
#endif
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
__STATIC_INLINE void CMU_Sync(uint32_t mask)
{
  /* Avoid deadlock if modifying the same register twice when freeze mode is */
  /* activated. */
  if (CMU->FREEZE & CMU_FREEZE_REGFREEZE)
    return;

  /* Wait for any pending previous write operation to have been completed */
  /* in low frequency domain */
  while (CMU->SYNCBUSY & mask)
    ;
}


/** @endcond */

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
  EFM_ASSERT(HFCycles <= (_CMU_CALCNT_CALCNT_MASK >> _CMU_CALCNT_CALCNT_SHIFT));

  /* Set reference clock source */
  switch (ref)
  {
  case cmuOsc_LFXO:
    CMU->CALCTRL = CMU_CALCTRL_UPSEL_LFXO;
    break;

  case cmuOsc_LFRCO:
    CMU->CALCTRL = CMU_CALCTRL_UPSEL_LFRCO;
    break;

  case cmuOsc_HFXO:
    CMU->CALCTRL = CMU_CALCTRL_UPSEL_HFXO;
    break;

  case cmuOsc_HFRCO:
    CMU->CALCTRL = CMU_CALCTRL_UPSEL_HFRCO;
    break;

  case cmuOsc_AUXHFRCO:
    CMU->CALCTRL = CMU_CALCTRL_UPSEL_AUXHFRCO;
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
  while (CMU->STATUS & CMU_STATUS_CALBSY)
    ;

  return CMU->CALCNT;
}


#if defined (_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
/***************************************************************************//**
 * @brief
 *   Configure clock calibration
 *
 * @details
 *   Configure a calibration for a selectable clock source against another
 *   selectable reference clock.
 *   Refer to the EFM32 reference manual, CMU chapter, for further details.
 *
 * @note
 *   After configuration, a call to CMU_CalibrateStart() is required, and
 *   the resulting calibration value can be read out with the
 *   CMU_CalibrateCountGet() function call.
 *
 * @param[in] downCycles
 *   The number of downSel clock cycles to run calibration. Increasing this
 *   number increases precision, but the calibration will take more time.
 *
 * @param[in] downSel
 *   The clock which will be counted down downCycles
 *
 * @param[in] upSel
 *   The reference clock, the number of cycles generated by this clock will
 *   be counted and added up, the result can be given with the
 *   CMU_CalibrateCountGet() function call.
 ******************************************************************************/
void CMU_CalibrateConfig(uint32_t downCycles, CMU_Osc_TypeDef downSel,
                         CMU_Osc_TypeDef upSel)
{
  /* Keep untouched configuration settings */
  uint32_t calCtrl = CMU->CALCTRL & ~(_CMU_CALCTRL_UPSEL_MASK | _CMU_CALCTRL_DOWNSEL_MASK);

  /* 20 bits of precision to calibration count register */
  EFM_ASSERT(downCycles <= (_CMU_CALCNT_CALCNT_MASK >> _CMU_CALCNT_CALCNT_SHIFT));

  /* Set down counting clock source - down counter */
  switch (downSel)
  {
  case cmuOsc_LFXO:
    calCtrl |= CMU_CALCTRL_DOWNSEL_LFXO;
    break;

  case cmuOsc_LFRCO:
    calCtrl |= CMU_CALCTRL_DOWNSEL_LFRCO;
    break;

  case cmuOsc_HFXO:
    calCtrl |= CMU_CALCTRL_DOWNSEL_HFXO;
    break;

  case cmuOsc_HFRCO:
    calCtrl |= CMU_CALCTRL_DOWNSEL_HFRCO;
    break;

  case cmuOsc_AUXHFRCO:
    calCtrl |= CMU_CALCTRL_DOWNSEL_AUXHFRCO;
    break;

  default:
    EFM_ASSERT(0);
  }

  /* Set top value to be counted down by the downSel clock */
  CMU->CALCNT = downCycles;

  /* Set reference clock source - up counter */
  switch (upSel)
  {
  case cmuOsc_LFXO:
    calCtrl |= CMU_CALCTRL_UPSEL_LFXO;
    break;

  case cmuOsc_LFRCO:
    calCtrl |= CMU_CALCTRL_UPSEL_LFRCO;
    break;

  case cmuOsc_HFXO:
    calCtrl |= CMU_CALCTRL_UPSEL_HFXO;
    break;

  case cmuOsc_HFRCO:
    calCtrl |= CMU_CALCTRL_UPSEL_HFRCO;
    break;

  case cmuOsc_AUXHFRCO:
    calCtrl |= CMU_CALCTRL_UPSEL_AUXHFRCO;
    break;

  default:
    EFM_ASSERT(0);
  }

  CMU->CALCTRL = calCtrl;
}
#endif


/***************************************************************************//**
 * @brief
 *   Get clock divisor/prescaler.
 *
 * @param[in] clock
 *   Clock point to get divisor/prescaler for. Notice that not all clock points
 *   have a divisor/prescaler. Please refer to CMU overview in reference manual.
 *
 * @return
 *   The current clock point divisor/prescaler. 1 is returned
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
#if defined(_EFM32_GIANT_FAMILY)
  case CMU_HFCLKDIV_REG:
    ret = 1 + ((CMU->CTRL & _CMU_CTRL_HFCLKDIV_MASK) >>
               _CMU_CTRL_HFCLKDIV_SHIFT);
    break;
#endif

  case CMU_HFPERCLKDIV_REG:
    ret = (CMU_ClkDiv_TypeDef)((CMU->HFPERCLKDIV &
                                _CMU_HFPERCLKDIV_HFPERCLKDIV_MASK) >>
                               _CMU_HFPERCLKDIV_HFPERCLKDIV_SHIFT);
    ret = CMU_Log2ToDiv(ret);
    break;

  case CMU_HFCORECLKDIV_REG:
    ret = (CMU_ClkDiv_TypeDef)((CMU->HFCORECLKDIV &
                                _CMU_HFCORECLKDIV_HFCORECLKDIV_MASK) >>
                               _CMU_HFCORECLKDIV_HFCORECLKDIV_SHIFT);
    ret = CMU_Log2ToDiv(ret);
    break;

  case CMU_LFAPRESC0_REG:
    switch (clock)
    {
    case cmuClock_RTC:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFAPRESC0 & _CMU_LFAPRESC0_RTC_MASK) >>
                                  _CMU_LFAPRESC0_RTC_SHIFT));
      ret = CMU_Log2ToDiv(ret);
      break;

#if defined(_CMU_LFAPRESC0_LETIMER0_MASK)
    case cmuClock_LETIMER0:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFAPRESC0 & _CMU_LFAPRESC0_LETIMER0_MASK) >>
                                  _CMU_LFAPRESC0_LETIMER0_SHIFT));
      ret = CMU_Log2ToDiv(ret);
      break;
#endif

#if defined(_CMU_LFPRESC0_LCD_MASK)
    case cmuClock_LCDpre:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFAPRESC0 & _CMU_LFAPRESC0_LCD_MASK) >>
                                  _CMU_LFAPRESC0_LCD_SHIFT) + cmuClkDiv_16);
      ret = CMU_Log2ToDiv(ret);
      break;
#endif

#if defined(_CMU_LFAPRESC0_LESENSE_MASK)
    case cmuClock_LESENSE:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFAPRESC0 & _CMU_LFAPRESC0_LESENSE_MASK) >>
                                  _CMU_LFAPRESC0_LESENSE_SHIFT));
      ret = CMU_Log2ToDiv(ret);
      break;
#endif

    default:
      EFM_ASSERT(0);
      ret = cmuClkDiv_1;
      break;
    }
    break;

  case CMU_LFBPRESC0_REG:
    switch (clock)
    {
#if defined(_CMU_LFPRESC0_LEUART0_MASK)
    case cmuClock_LEUART0:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART0_MASK) >>
                                  _CMU_LFBPRESC0_LEUART0_SHIFT));
      ret = CMU_Log2ToDiv(ret);
      break;
#endif

#if defined(_CMU_LFPRESC0_LEUART1_MASK)
    case cmuClock_LEUART1:
      ret = (CMU_ClkDiv_TypeDef)(((CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART1_MASK) >>
                                  _CMU_LFBPRESC0_LEUART1_SHIFT));
      ret = CMU_Log2ToDiv(ret);
      break;
#endif

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
#if defined (_EFM32_GIANT_FAMILY)
  case CMU_HFCLKDIV_REG:
    EFM_ASSERT((div>=cmuClkDiv_1) && (div<=cmuClkDiv_8));

    /* Configure worst case wait states for flash access before setting divisor */
    CMU_FlashWaitStateMax();

    /* Set divider */
    CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_HFCLKDIV_MASK) |
      ((div-1) << _CMU_CTRL_HFCLKDIV_SHIFT);

    /* Update CMSIS core clock variable */
    /* (The function will update the global variable) */
    freq = SystemCoreClockGet();

    /* Optimize flash access wait state setting for current core clk */
    CMU_FlashWaitStateControl(freq);
    break;
#endif

  case CMU_HFPERCLKDIV_REG:
    EFM_ASSERT((div >= cmuClkDiv_1) && (div <= cmuClkDiv_512));
    /* Convert to correct scale */
    div = CMU_DivToLog2(div);
    CMU->HFPERCLKDIV = (CMU->HFPERCLKDIV & ~_CMU_HFPERCLKDIV_HFPERCLKDIV_MASK) |
                       (div << _CMU_HFPERCLKDIV_HFPERCLKDIV_SHIFT);
    break;

  case CMU_HFCORECLKDIV_REG:
    EFM_ASSERT(div <= cmuClkDiv_512);

    /* Configure worst case wait states for flash access before setting divisor */
    CMU_FlashWaitStateMax();

    /* Convert to correct scale */
    div = CMU_DivToLog2(div);

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

      /* Convert to correct scale */
      div = CMU_DivToLog2(div);

      CMU->LFAPRESC0 = (CMU->LFAPRESC0 & ~_CMU_LFAPRESC0_RTC_MASK) |
                       (div << _CMU_LFAPRESC0_RTC_SHIFT);
      break;

#if defined(_CMU_LFAPRESC0_LETIMER0_MASK)
    case cmuClock_LETIMER0:
      EFM_ASSERT(div <= cmuClkDiv_32768);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFAPRESC0);

      /* Convert to correct scale */
      div = CMU_DivToLog2(div);

      CMU->LFAPRESC0 = (CMU->LFAPRESC0 & ~_CMU_LFAPRESC0_LETIMER0_MASK) |
                       (div << _CMU_LFAPRESC0_LETIMER0_SHIFT);
      break;
#endif

#if defined(LCD_PRESENT)
    case cmuClock_LCDpre:
      EFM_ASSERT((div >= cmuClkDiv_16) && (div <= cmuClkDiv_128));

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFAPRESC0);

      /* Convert to correct scale */
      div = CMU_DivToLog2(div);

      CMU->LFAPRESC0 = (CMU->LFAPRESC0 & ~_CMU_LFAPRESC0_LCD_MASK) |
                       ((div - cmuClkDiv_16) << _CMU_LFAPRESC0_LCD_SHIFT);
      break;
#endif /* defined(LCD_PRESENT) */

#if defined(LESENSE_PRESENT)
    case cmuClock_LESENSE:
      EFM_ASSERT(div <= cmuClkDiv_8);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFAPRESC0);

      /* Convert to correct scale */
      div = CMU_DivToLog2(div);

      CMU->LFAPRESC0 = (CMU->LFAPRESC0 & ~_CMU_LFAPRESC0_LESENSE_MASK) |
                       (div << _CMU_LFAPRESC0_LESENSE_SHIFT);
      break;
#endif /* defined(LESENSE_PRESENT) */

    default:
      EFM_ASSERT(0);
      break;
    }
    break;

  case CMU_LFBPRESC0_REG:
    switch (clock)
    {
#if defined(_CMU_LFBPRESC0_LEUART0_MASK)
    case cmuClock_LEUART0:
      EFM_ASSERT(div <= cmuClkDiv_8);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFBPRESC0);

      /* Convert to correct scale */
      div = CMU_DivToLog2(div);

      CMU->LFBPRESC0 = (CMU->LFBPRESC0 & ~_CMU_LFBPRESC0_LEUART0_MASK) |
                       (((uint32_t)div) << _CMU_LFBPRESC0_LEUART0_SHIFT);
      break;
#endif

#if defined(_CMU_LFBPRESC0_LEUART1_MASK)
    case cmuClock_LEUART1:
      EFM_ASSERT(div <= cmuClkDiv_8);

      /* LF register about to be modified require sync. busy check */
      CMU_Sync(CMU_SYNCBUSY_LFBPRESC0);

      /* Convert to correct scale */
      div = CMU_DivToLog2(div);

      CMU->LFBPRESC0 = (CMU->LFBPRESC0 & ~_CMU_LFBPRESC0_LEUART1_MASK) |
                       (((uint32_t)div) << _CMU_LFBPRESC0_LEUART1_SHIFT);
      break;
#endif

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
  BITBAND_Peripheral(reg, bit, (unsigned int)enable);
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

  switch(clock & (CMU_CLK_BRANCH_MASK << CMU_CLK_BRANCH_POS))
  {
    case (CMU_HF_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret = SystemHFClockGet();
#if defined(_EFM32_GIANT_FAMILY)
      /* Giant Gecko has an additional divider, not used by USBC */
      ret = ret / (1 + ((CMU->CTRL & _CMU_CTRL_HFCLKDIV_MASK) >>
                   _CMU_CTRL_HFCLKDIV_SHIFT));
#endif
    } break;

#if defined(_CMU_HFPERCLKEN0_USART0_MASK) || \
    defined(_CMU_HFPERCLKEN0_USART1_MASK) || \
    defined(_CMU_HFPERCLKEN0_USART2_MASK) || \
    defined(_CMU_HFPERCLKEN0_UART0_MASK) || \
    defined(_CMU_HFPERCLKEN0_UART1_MASK) || \
    defined(_CMU_HFPERCLKEN0_TIMER0_MASK) || \
    defined(_CMU_HFPERCLKEN0_TIMER1_MASK) || \
    defined(_CMU_HFPERCLKEN0_TIMER2_MASK) || \
    defined(_CMU_HFPERCLKEN0_TIMER3_MASK) || \
    defined(_CMU_HFPERCLKEN0_ACMP0_MASK) || \
    defined(_CMU_HFPERCLKEN0_ACMP1_MASK) || \
    defined(_CMU_HFPERCLKEN0_DAC0_MASK) || \
    defined(_CMU_HFPERCLKEN0_ADC0_MASK) || \
    defined(_CMU_HFPERCLKEN0_I2C0_MASK) || \
    defined(_CMU_HFPERCLKEN0_I2C1_MASK) || \
    defined(PRS_PRESENT) || \
    defined(VCMP_PRESENT)|| \
    defined(GPIO_PRESENT)
    case (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = SystemHFClockGet();
#if defined (_EFM32_GIANT_FAMILY)
      /* Leopard/Giant Gecko has an additional divider */
      ret = ret / (1 + ((CMU->CTRL & _CMU_CTRL_HFCLKDIV_MASK) >>
                        _CMU_CTRL_HFCLKDIV_SHIFT));
#endif
      ret >>= (CMU->HFPERCLKDIV & _CMU_HFPERCLKDIV_HFPERCLKDIV_MASK) >>
              _CMU_HFPERCLKDIV_HFPERCLKDIV_SHIFT;
    } break;
#endif

#if defined(AES_PRESENT) || \
    defined(DMA_PRESENT) || \
    defined(EBI_PRESENT) || \
    defined(USB_PRESENT)
    case (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret = SystemCoreClockGet();
    } break;
#endif

    case (CMU_LFA_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret = CMU_LFClkGet(CMU_LFA);
    } break;
#if defined(_CMU_LFACLKEN0_RTC_MASK)
    case (CMU_RTC_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = CMU_LFClkGet(CMU_LFA);
      ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_RTC_MASK) >>
              _CMU_LFAPRESC0_RTC_SHIFT;
    } break;
#endif
#if defined(_CMU_LFACLKEN0_LETIMER0_MASK)
    case (CMU_LETIMER_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = CMU_LFClkGet(CMU_LFA);
      ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_LETIMER0_MASK) >>
              _CMU_LFAPRESC0_LETIMER0_SHIFT;
    } break;
#endif
#if defined(_CMU_LFACLKEN0_LCD_MASK)
    case (CMU_LCDPRE_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = CMU_LFClkGet(CMU_LFA);
      ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_LCD_MASK) >>
              _CMU_LFAPRESC0_LCD_SHIFT;
    } break;

    case (CMU_LCD_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = CMU_LFClkGet(CMU_LFA);
      ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_LCD_MASK) >>
              _CMU_LFAPRESC0_LCD_SHIFT;
      ret /= (1 + ((CMU->LCDCTRL & _CMU_LCDCTRL_FDIV_MASK) >>
                   _CMU_LCDCTRL_FDIV_SHIFT));
    } break;
#endif
#if defined(_CMU_LFACLKEN0_LESENSE_MASK)
    case (CMU_LESENSE_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = CMU_LFClkGet(CMU_LFA);
      ret >>= (CMU->LFAPRESC0 & _CMU_LFAPRESC0_LESENSE_MASK) >>
              _CMU_LFAPRESC0_LESENSE_SHIFT;
    } break;
#endif
    case (CMU_LFB_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret = CMU_LFClkGet(CMU_LFB);
    } break;
#if defined(_CMU_LFBCLKEN0_LEUART0_MASK)
    case (CMU_LEUART0_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = CMU_LFClkGet(CMU_LFB);
      ret >>= (CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART0_MASK) >>
              _CMU_LFBPRESC0_LEUART0_SHIFT;
    } break;
#endif
#if defined(_CMU_LFBCLKEN0_LEUART1_MASK)
    case (CMU_LEUART1_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret   = CMU_LFClkGet(CMU_LFB);
      ret >>= (CMU->LFBPRESC0 & _CMU_LFBPRESC0_LEUART1_MASK) >>
        _CMU_LFBPRESC0_LEUART1_SHIFT;
    } break;
#endif

    case (CMU_DBG_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret  = CMU_DBGClkGet();
    } break;

    case (CMU_AUX_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret  = CMU_AUXClkGet();
    } break;

#if defined(USB_PRESENT)
    case (CMU_USBC_CLK_BRANCH << CMU_CLK_BRANCH_POS):
    {
      ret = CMU_USBCClkGet();
    } break;
#endif
    default:
    {
      EFM_ASSERT(0);
      ret = 0;
    } break;
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
 *   @li #cmuClock_USBC
 *   @li #cmuClock_DBG
 *
 * @return
 *   Reference clock used for clocking selected branch, #cmuSelect_Error if
 *   invalid @p clock provided.
 *****************************************************************************/
CMU_Select_TypeDef CMU_ClockSelectGet(CMU_Clock_TypeDef clock)
{
  CMU_Select_TypeDef ret = cmuSelect_Disabled;
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
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
      if (CMU->LFCLKSEL & _CMU_LFCLKSEL_LFAE_MASK)
      {
        ret = cmuSelect_ULFRCO;
        break;
      }
#else
      ret = cmuSelect_Disabled;
#endif
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
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
      if (CMU->LFCLKSEL & _CMU_LFCLKSEL_LFBE_MASK)
      {
        ret = cmuSelect_ULFRCO;
        break;
      }
#else
      ret = cmuSelect_Disabled;
#endif
      break;
    }
    break;

  case CMU_DBGCLKSEL_REG:
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
    switch(CMU->CTRL & _CMU_CTRL_DBGCLK_MASK)
    {
    case CMU_CTRL_DBGCLK_AUXHFRCO:
      ret = cmuSelect_AUXHFRCO;
      break;

    case CMU_CTRL_DBGCLK_HFCLK:
      ret = cmuSelect_HFCLK;
      break;
    }
#endif
#if defined(_EFM32_GECKO_FAMILY)
    ret = cmuSelect_AUXHFRCO;
#endif
    break;


#if defined(USB_PRESENT)
  case CMU_USBCCLKSEL_REG:
    switch(CMU->STATUS & (CMU_STATUS_USBCHFCLKSEL |
                          CMU_STATUS_USBCLFXOSEL |
                          CMU_STATUS_USBCLFRCOSEL))
    {
    case CMU_STATUS_USBCHFCLKSEL:
      ret = cmuSelect_HFCLK;
      break;

    case CMU_STATUS_USBCLFXOSEL:
      ret = cmuSelect_LFXO;
      break;

    case CMU_STATUS_USBCLFRCOSEL:
      ret = cmuSelect_LFRCO;
      break;

    default:
      ret = cmuSelect_Disabled;
      break;
    }
    break;
#endif

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
 *   @li #cmuClock_USBC
 *   @li #cmuClock_DBG
 *
 * @param[in] ref
 *   Reference selected for clocking, please refer to reference manual for
 *   for details on which reference is available for a specific clock branch.
 *   @li #cmuSelect_HFRCO
 *   @li #cmuSelect_LFRCO
 *   @li #cmuSelect_HFXO
 *   @li #cmuSelect_LFXO
 *   @li #cmuSelect_CORELEDIV2
 *   @li #cmuSelect_AUXHFRC
 *   @li #cmuSelect_HFCLK
 *   @li #cmuSelect_ULFRCO
 *****************************************************************************/
void CMU_ClockSelectSet(CMU_Clock_TypeDef clock, CMU_Select_TypeDef ref)
{
  uint32_t        select = cmuOsc_HFRCO;
  CMU_Osc_TypeDef osc    = cmuOsc_HFRCO;
  uint32_t        freq;
  uint32_t        selReg;
  uint32_t        lfShift;
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
  uint32_t        lfExtendedShift;
  uint32_t        lfExtended = 0;
#endif
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
#if defined(_EFM32_GIANT_FAMILY)
      /* Adjust HFXO buffer current for high frequencies, enable HFLE for */
      /* frequencies above 32MHz */
      if(SystemHFXOClockGet() > CMU_MAX_FREQ_HFLE)
      {
        CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_HFXOBUFCUR_MASK) |
          CMU_CTRL_HFXOBUFCUR_BOOSTABOVE32MHZ |
          /* Must have HFLE enabled to access some LE peripherals >=32MHz */
          CMU_CTRL_HFLE;
      } else {
        /* This can happen if the user configures the EFM32_HFXO_FREQ to */
        /* use another oscillator frequency */
        CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_HFXOBUFCUR_MASK) |
          CMU_CTRL_HFXOBUFCUR_BOOSTUPTO32MHZ;
      }
#endif
      break;

    case cmuSelect_HFRCO:
      select = CMU_CMD_HFCLKSEL_HFRCO;
      osc    = cmuOsc_HFRCO;
      break;

#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
    case cmuSelect_ULFRCO:
      /* ULFRCO cannot be used as HFCLK  */
      EFM_ASSERT(0);
      break;
#endif

    default:
      EFM_ASSERT(0);
      return;
    }

    /* Ensure selected oscillator is enabled, waiting for it to stabilize */
    CMU_OscillatorEnable(osc, true, true);

    /* Configure worst case wait states for flash access before selecting */
    CMU_FlashWaitStateMax();

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
    {
      lfShift = _CMU_LFCLKSEL_LFA_SHIFT;
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
      lfExtendedShift = _CMU_LFCLKSEL_LFAE_SHIFT;
#endif
    }
    else
    {
      lfShift = _CMU_LFCLKSEL_LFB_SHIFT;
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
      lfExtendedShift = _CMU_LFCLKSEL_LFBE_SHIFT;
#endif
    }

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
#if defined(_EFM32_GIANT_FAMILY)
      /* If core frequency is > 32MHz on Giant/Leopard, enable HFLE and DIV4 */
      freq = SystemCoreClockGet();
      if(freq > CMU_MAX_FREQ_HFLE)
      {
        /* Enable CMU HFLE */
        BITBAND_Peripheral(&(CMU->CTRL), _CMU_CTRL_HFLE_SHIFT, 1);

        /* Enable DIV4 factor for peripheral clock */
        BITBAND_Peripheral(&(CMU->HFCORECLKDIV),
                           _CMU_HFCORECLKDIV_HFCORECLKLEDIV_SHIFT, 1);
      }
#endif
      break;

#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
    case cmuSelect_ULFRCO:
      /* ULFRCO is always enabled */
      tmp        = _CMU_LFCLKSEL_LFA_DISABLED;
      lfExtended = 1;
      break;
#endif

    default:
      /* Illegal clock source for LFA/LFB selected */
      EFM_ASSERT(0);
      return;
    }

#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~((_CMU_LFCLKSEL_LFA_MASK | _CMU_LFCLKSEL_LFAE_MASK) << lfShift)) |
                    (tmp << lfShift) | (lfExtended << lfExtendedShift);
#else
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~(_CMU_LFCLKSEL_LFA_MASK << lfShift)) |
                    (tmp << lfShift);
#endif
    break;

#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
  case CMU_DBGCLKSEL_REG:
    switch(ref)
    {
    case cmuSelect_AUXHFRCO:
      /* Select AUXHFRCO as debug clock */
      CMU->CTRL = (CMU->CTRL & ~(_CMU_CTRL_DBGCLK_MASK))| CMU_CTRL_DBGCLK_AUXHFRCO;
      break;

    case cmuSelect_HFCLK:
      /* Select divided HFCLK as debug clock */
      CMU->CTRL = (CMU->CTRL & ~(_CMU_CTRL_DBGCLK_MASK))| CMU_CTRL_DBGCLK_HFCLK;
      break;

    default:
      /* Illegal clock source for debug selected */
      EFM_ASSERT(0);
      return;
    }
    break;
#endif

#if defined(USB_PRESENT)
  case CMU_USBCCLKSEL_REG:
    switch(ref)
    {

    case cmuSelect_HFCLK:
      /* Select undivided HFCLK as clock source for USB */
      /* Oscillator must already be enabled, if not the core had stopped */
      CMU->CMD = CMU_CMD_USBCCLKSEL_HFCLKNODIV;
      /* Wait until clock is activated */
      while((CMU->STATUS & CMU_STATUS_USBCHFCLKSEL)==0);
      break;

    case cmuSelect_LFXO:
      /* Select LFXO as clock source for USB, can only be used in sleep mode */

      /* Ensure selected oscillator is enabled, waiting for it to stabilize */
      CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

      /* Switch oscillator */
      CMU->CMD = CMU_CMD_USBCCLKSEL_LFXO;

      /* Wait until clock is activated */
      while((CMU->STATUS & CMU_STATUS_USBCLFXOSEL)==0);
      break;

    case cmuSelect_LFRCO:
      /* Select LFRCO as clock source for USB, can only be used in sleep mode */

      /* Ensure selected oscillator is enabled, waiting for it to stabilize */
      CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);

      /* Switch oscillator */
      CMU->CMD = CMU_CMD_USBCCLKSEL_LFRCO;

      /* Wait until clock is activated */
      while((CMU->STATUS & CMU_STATUS_USBCLFRCOSEL)==0);
      break;

    default:
      /* Illegal clock source for USB */
      EFM_ASSERT(0);
      return;
    }
    /* Wait until clock has been activated */
    break;
#endif

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
    /* Wait for any ongoing LF synchronization to complete. This is just to */
    /* protect against the rare case when a user                            */
    /* - modifies a register requiring LF sync                              */
    /* - then enables freeze before LF sync completed                       */
    /* - then modifies the same register again                              */
    /* since modifying a register while it is in sync progress should be    */
    /* avoided.                                                             */
    while (CMU->SYNCBUSY)
      ;

    CMU->FREEZE = CMU_FREEZE_REGFREEZE;
  }
  else
  {
    CMU->FREEZE = 0;
  }
}


#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
/***************************************************************************//**
 * @brief
 *   Get AUXHFRCO band in use.
 *
 * @return
 *   AUXHFRCO band in use.
 ******************************************************************************/
CMU_AUXHFRCOBand_TypeDef CMU_AUXHFRCOBandGet(void)
{
  return (CMU_AUXHFRCOBand_TypeDef)((CMU->AUXHFRCOCTRL & _CMU_AUXHFRCOCTRL_BAND_MASK) >>
                                 _CMU_AUXHFRCOCTRL_BAND_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set AUIXHFRCO band and the tuning value based on the value in the
 *   calibration table made during production.
 *
 * @param[in] band
 *   AUXHFRCO band to activate.
 ******************************************************************************/
void CMU_AUXHFRCOBandSet(CMU_AUXHFRCOBand_TypeDef band)
{
  uint32_t           tuning;

  /* Read tuning value from calibration table */
  switch (band)
  {
  case cmuAUXHFRCOBand_1MHz:
    tuning = (DEVINFO->AUXHFRCOCAL0 & _DEVINFO_AUXHFRCOCAL0_BAND1_MASK) >>
             _DEVINFO_AUXHFRCOCAL0_BAND1_SHIFT;
    break;

  case cmuAUXHFRCOBand_7MHz:
    tuning = (DEVINFO->AUXHFRCOCAL0 & _DEVINFO_AUXHFRCOCAL0_BAND7_MASK) >>
             _DEVINFO_AUXHFRCOCAL0_BAND7_SHIFT;
    break;

  case cmuAUXHFRCOBand_11MHz:
    tuning = (DEVINFO->AUXHFRCOCAL0 & _DEVINFO_AUXHFRCOCAL0_BAND11_MASK) >>
             _DEVINFO_AUXHFRCOCAL0_BAND11_SHIFT;
    break;

  case cmuAUXHFRCOBand_14MHz:
    tuning = (DEVINFO->AUXHFRCOCAL0 & _DEVINFO_AUXHFRCOCAL0_BAND14_MASK) >>
             _DEVINFO_AUXHFRCOCAL0_BAND14_SHIFT;
    break;

  case cmuAUXHFRCOBand_21MHz:
    tuning = (DEVINFO->AUXHFRCOCAL1 & _DEVINFO_AUXHFRCOCAL1_BAND21_MASK) >>
             _DEVINFO_AUXHFRCOCAL1_BAND21_SHIFT;
    break;

  case cmuAUXHFRCOBand_28MHz:
    tuning = (DEVINFO->AUXHFRCOCAL1 & _DEVINFO_AUXHFRCOCAL1_BAND28_MASK) >>
             _DEVINFO_AUXHFRCOCAL1_BAND28_SHIFT;
    break;

  default:
    EFM_ASSERT(0);
    return;
  }

  /* Set band/tuning */
  CMU->AUXHFRCOCTRL = (CMU->AUXHFRCOCTRL &
                    ~(_CMU_AUXHFRCOCTRL_BAND_MASK | _CMU_AUXHFRCOCTRL_TUNING_MASK)) |
                   (band << _CMU_AUXHFRCOCTRL_BAND_SHIFT) |
                   (tuning << _CMU_AUXHFRCOCTRL_TUNING_SHIFT);

}
#endif


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
    CMU_FlashWaitStateMax();
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
  (void)div;  /* Unused parameter */
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

#if defined _CMU_LFCLKSEL_LFAE_ULFRCO
  case cmuOsc_ULFRCO:
    /* ULFRCO is always enabled, and cannot be turned off */
    return;
#endif

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
      while (!(CMU->STATUS & status))
        ;
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
#if defined(_CMU_PCNTCTRL_PCNT0CLKEN_MASK)
  case 0:
    setting = CMU->PCNTCTRL & CMU_PCNTCTRL_PCNT0CLKSEL_PCNT0S0;
    break;

#if defined(_CMU_PCNTCTRL_PCNT1CLKEN_MASK)
  case 1:
    setting = CMU->PCNTCTRL & CMU_PCNTCTRL_PCNT1CLKSEL_PCNT1S0;
    break;

#if defined(_CMU_PCNTCTRL_PCNT2CLKEN_MASK)
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
  (void)inst;      /* Unused parameter */
  (void)external;  /* Unused parameter */
#endif
}


/** @} (end addtogroup CMU) */
/** @} (end addtogroup EM_Library) */
