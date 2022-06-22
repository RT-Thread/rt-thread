/***************************************************************************//**
 * @file
 * @brief Low Energy Sensor (LESENSE) Peripheral API
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
#include "em_lesense.h"
#if defined(LESENSE_COUNT) && (LESENSE_COUNT > 0)
#include "em_assert.h"
#include "em_bitband.h"
#include "em_cmu.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup LESENSE
 * @brief Low Energy Sensor (LESENSE) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Initialize the LESENSE module.
 *
 * @details
 *   This function configures the main parameters of the LESENSE interface.
 *   Please refer to the initialization parameter type definition
 *   (LESENSE_Init_TypeDef) for more details.
 *
 * @note
 *   LESENSE_Init() has been designed for initializing LESENSE once in an
 *   operation cycle. Be aware of the effects of reconfiguration if using this
 *   function from multiple sources in your code. This function has not been
 *   designed to be re-entrant.
 *   Requesting reset by setting @p reqReset to true is required in each reset
 *   or power-on cycle in order to configure the default values of the RAM
 *   mapped LESENSE registers.
 *   Notice that GPIO pins used by the LESENSE module must be properly
 *   configured by the user explicitly, in order for the LESENSE to work as
 *   intended.
 *   (When configuring pins, one should remember to consider the sequence of
 *   configuration, in order to avoid unintended pulses/glitches on output
 *   pins.)
 *
 * @param[in] init
 *   LESENSE initialization structure.
 *
 * @param[in] reqReset
 *   Request to call LESENSE_Reset() first in order to initialize all LESENSE
 *   registers with the default value.
 ******************************************************************************/
void LESENSE_Init(LESENSE_Init_TypeDef const *init, bool const reqReset)
{
  /* Sanity check of initialization values */
  EFM_ASSERT((uint32_t)init->timeCtrl.startDelay < 4U);
  EFM_ASSERT((uint32_t)init->perCtrl.dacPresc < 32U);

  /* Reset LESENSE registers if requested. */
  if (reqReset)
  {
    LESENSE_Reset();
  }

  /* Set sensor start delay for each channel. */
  LESENSE_StartDelaySet((uint32_t)init->timeCtrl.startDelay);

  /* LESENSE core control configuration.
   * Set PRS source, SCANCONF register usage strategy, interrupt and
   * DMA trigger level condition, DMA wakeup condition, bias mode,
   * enable/disable to sample both ACMPs simultaneously, enable/disable to store
   * SCANRES in CNT_RES after each scan, enable/disable to always write to the
   * result buffer, even if it is full, enable/disable LESENSE running in debug
   * mode. */
  LESENSE->CTRL = ((uint32_t)init->coreCtrl.prsSel <<
                   _LESENSE_CTRL_PRSSEL_SHIFT) |
                  (uint32_t)init->coreCtrl.scanConfSel |
                  (uint32_t)init->coreCtrl.bufTrigLevel |
                  (uint32_t)init->coreCtrl.wakeupOnDMA |
                  ((uint32_t)init->coreCtrl.invACMP0 <<
                   _LESENSE_CTRL_ACMP0INV_SHIFT) |
                  ((uint32_t)init->coreCtrl.invACMP1 <<
                   _LESENSE_CTRL_ACMP1INV_SHIFT) |
                  ((uint32_t)init->coreCtrl.dualSample <<
                   _LESENSE_CTRL_DUALSAMPLE_SHIFT) |
                  ((uint32_t)init->coreCtrl.storeScanRes <<
                   _LESENSE_CTRL_STRSCANRES_SHIFT) |
                  ((uint32_t)init->coreCtrl.bufOverWr <<
                   _LESENSE_CTRL_BUFOW_SHIFT) |
                  ((uint32_t)init->coreCtrl.debugRun <<
                   _LESENSE_CTRL_DEBUGRUN_SHIFT);

  /* Set scan mode in the CTRL register using the provided function, don't
   * start scanning immediately. */
  LESENSE_ScanModeSet((LESENSE_ScanMode_TypeDef)init->coreCtrl.scanStart, false);

  /* LESENSE peripheral control configuration.
   * Set DAC0 and DAC1 data source, conversion mode, output mode. Set DAC
   * prescaler and reference. Set ACMP0 and ACMP1 control mode. Set ACMP and DAC
   * duty cycle (warm up) mode. */
  LESENSE->PERCTRL = ((uint32_t)init->perCtrl.dacCh0Data <<
                      _LESENSE_PERCTRL_DACCH0DATA_SHIFT) |
                     ((uint32_t)init->perCtrl.dacCh0ConvMode <<
                      _LESENSE_PERCTRL_DACCH0CONV_SHIFT) |
                     ((uint32_t)init->perCtrl.dacCh0OutMode <<
                      _LESENSE_PERCTRL_DACCH0OUT_SHIFT) |
                     ((uint32_t)init->perCtrl.dacCh1Data <<
                      _LESENSE_PERCTRL_DACCH1DATA_SHIFT) |
                     ((uint32_t)init->perCtrl.dacCh1ConvMode <<
                      _LESENSE_PERCTRL_DACCH1CONV_SHIFT) |
                     ((uint32_t)init->perCtrl.dacCh1OutMode <<
                      _LESENSE_PERCTRL_DACCH1OUT_SHIFT) |
                     ((uint32_t)init->perCtrl.dacPresc <<
                      _LESENSE_PERCTRL_DACPRESC_SHIFT) |
                     (uint32_t)init->perCtrl.dacRef |
                     ((uint32_t)init->perCtrl.acmp0Mode <<
                      _LESENSE_PERCTRL_ACMP0MODE_SHIFT) |
                     ((uint32_t)init->perCtrl.acmp1Mode <<
                      _LESENSE_PERCTRL_ACMP1MODE_SHIFT) |
                     (uint32_t)init->perCtrl.warmupMode;

  /* LESENSE decoder general control configuration.
   * Set decoder input source, select PRS input for decoder bits.
   * Enable/disable the decoder to check the present state.
   * Enable/disable decoder to channel interrupt mapping.
   * Enable/disable decoder hysteresis on PRS output.
   * Enable/disable decoder hysteresis on count events.
   * Enable/disable decoder hysteresis on interrupt requests.
   * Enable/disable count mode on LESPRS0 and LESPRS1. */
  LESENSE->DECCTRL = (uint32_t)init->decCtrl.decInput |
                     ((uint32_t)init->decCtrl.prsChSel0 <<
                      _LESENSE_DECCTRL_PRSSEL0_SHIFT) |
                     ((uint32_t)init->decCtrl.prsChSel1 <<
                      _LESENSE_DECCTRL_PRSSEL1_SHIFT) |
                     ((uint32_t)init->decCtrl.prsChSel2 <<
                      _LESENSE_DECCTRL_PRSSEL2_SHIFT) |
                     ((uint32_t)init->decCtrl.prsChSel3 <<
                      _LESENSE_DECCTRL_PRSSEL3_SHIFT) |
                     ((uint32_t)init->decCtrl.chkState <<
                      _LESENSE_DECCTRL_ERRCHK_SHIFT) |
                     ((uint32_t)init->decCtrl.intMap <<
                      _LESENSE_DECCTRL_INTMAP_SHIFT) |
                     ((uint32_t)init->decCtrl.hystPRS0 <<
                      _LESENSE_DECCTRL_HYSTPRS0_SHIFT) |
                     ((uint32_t)init->decCtrl.hystPRS1 <<
                      _LESENSE_DECCTRL_HYSTPRS1_SHIFT) |
                     ((uint32_t)init->decCtrl.hystPRS2 <<
                      _LESENSE_DECCTRL_HYSTPRS2_SHIFT) |
                     ((uint32_t)init->decCtrl.hystIRQ <<
                      _LESENSE_DECCTRL_HYSTIRQ_SHIFT) |
                     ((uint32_t)init->decCtrl.prsCount <<
                      _LESENSE_DECCTRL_PRSCNT_SHIFT);

  /* Set initial LESENSE decoder state. */
  LESENSE_DecoderStateSet((uint32_t)init->decCtrl.initState);

  /* LESENSE bias control configuration. */
  LESENSE->BIASCTRL = (uint32_t)init->coreCtrl.biasMode;
}


/***************************************************************************//**
 * @brief
 *   Set scan frequency for periodic scanning.
 *
 * @details
 *   This function only applies to LESENSE if period counter is being used as
 *   a trigger for scan start.
 *   The calculation is based on the following formula:
 *   Fscan = LFACLKles / ((1+PCTOP)*2^PCPRESC)
 *
 * @note
 *   Note that the calculation does not necessarily result in the requested
 *   scan frequency due to integer division. Check the return value for the
 *   resulted scan frequency.
 *
 * @param[in] refFreq
 *   Select reference LFACLK clock frequency in Hz. If set to 0, the current
 *   clock frequency is being used as a reference.
 *
 * @param[in] scanFreq
 *   Set the desired scan frequency in Hz.
 *
 * @return
 *   Frequency in Hz calculated and set by this function. Users can use this to
 *   compare the requested and set values.
 ******************************************************************************/
uint32_t LESENSE_ScanFreqSet(uint32_t refFreq, uint32_t const scanFreq)
{
  uint32_t tmp;
  uint32_t pcPresc = 0UL;  /* Period counter prescaler. */
  uint32_t clkDiv  = 1UL;  /* Clock divisor value (2^pcPresc). */
  uint32_t pcTop   = 63UL; /* Period counter top value (max. 63). */
  uint32_t calcScanFreq;   /* Variable for testing the calculation algorithm. */


  /* If refFreq is set to 0, the currently configured reference clock is
   * assumed. */
  if (!refFreq)
  {
    refFreq = CMU_ClockFreqGet(cmuClock_LESENSE);
  }

  /* Max. value of pcPresc is 128, thus using reference frequency less than
   * 33554431Hz (33.554431MHz), the frequency calculation in the while loop
   * below will not overflow. */
  EFM_ASSERT(refFreq < ((uint32_t)UINT32_MAX / 128UL));

  /* Sanity check of scan frequency value. */
  EFM_ASSERT((scanFreq > 0U) && (scanFreq <= refFreq));

  /* Calculate the minimum necessary prescaler value in order to provide the
   * biggest possible resolution for setting scan frequency.
   * Maximum number of calculation cycles is 7 (value of lesenseClkDiv_128). */
  while ((refFreq / ((uint32_t)scanFreq * clkDiv) > (pcTop + 1UL)) &&
         (pcPresc < lesenseClkDiv_128))
  {
    ++pcPresc;
    clkDiv = (uint32_t)1UL << pcPresc;
  }

  /* Calculate pcTop value. */
  pcTop = ((uint32_t)refFreq / ((uint32_t)scanFreq * clkDiv)) - 1UL;

  /* Clear current PCPRESC and PCTOP settings. Be aware of the effect of
   * non-atomic Read-Modify-Write on LESENSE->TIMCRTL. */
  tmp = LESENSE->TIMCTRL & (~(_LESENSE_TIMCTRL_PCPRESC_MASK)&
                            ~(_LESENSE_TIMCTRL_PCTOP_MASK));

  /* Set new values in tmp while reserving other settings. */
  tmp |= ((uint32_t)pcPresc << _LESENSE_TIMCTRL_PCPRESC_SHIFT) |
         ((uint32_t)pcTop << _LESENSE_TIMCTRL_PCTOP_SHIFT);

  /* Set values in LESENSE_TIMCTRL register. */
  LESENSE->TIMCTRL = tmp;

  /* For testing the calculation algorithm. */
  calcScanFreq = ((uint32_t)refFreq / ((uint32_t)(1UL + pcTop) * clkDiv));

  return calcScanFreq;
}


/***************************************************************************//**
 * @brief
 *   Set scan mode of the LESENSE channels.
 *
 * @details
 *   This function configures how the scan start is being triggered. It can be
 *   used for re-configuring the scan mode while running the application but it
 *   is also used by LESENSE_Init() for initialization.
 *
 * @note
 *   Users can configure the scan mode by LESENSE_Init() function, but only with
 *   a significant overhead. This simple function serves the purpose of
 *   controlling this parameter after the channel has been configured.
 *   Please be aware the effects of the non-atomic Read-Modify-Write cycle!
 *
 * @param[in] scanMode
 *   Select where to map LESENSE alternate excitation channels.
 *   @li lesenseScanStartPeriodic - New scan is started each time the period
 *                                  counter overflows.
 *   @li lesenseScanStartOneShot - Single scan is performed when
 *                                 LESENSE_ScanStart() is called.
 *   @li lesenseScanStartPRS - New scan is triggered by pulse on PRS channel.
 *
 * @param[in] start
 *   If true, LESENSE_ScanStart() is immediately issued after configuration.
 ******************************************************************************/
void LESENSE_ScanModeSet(LESENSE_ScanMode_TypeDef const scanMode,
                         bool const start)
{
  uint32_t tmp; /* temporary storage of the CTRL register value */


  /* Save the CTRL register value to tmp.
   * Please be aware the effects of the non-atomic Read-Modify-Write cycle! */
  tmp = LESENSE->CTRL & ~(_LESENSE_CTRL_SCANMODE_MASK);
  /* Setting the requested scanMode to the CTRL register. Casting signed int
   * (enum) to unsigned long (uint32_t). */
  tmp |= (uint32_t)scanMode;

  /* Write the new value to the CTRL register. */
  LESENSE->CTRL = tmp;

  /* Start sensor scanning if requested. */
  if (start)
  {
    LESENSE_ScanStart();
  }
}


/***************************************************************************//**
 * @brief
 *   Set start delay of sensor interaction on each channel.
 *
 * @details
 *   This function sets start delay of sensor interaction on each channel.
 *   It can be used for adjusting the start delay while running the application
 *   but it is also used by LESENSE_Init() for initialization.
 *
 * @note
 *   Users can configure the start delay by LESENSE_Init() function, but only
 *   with a significant overhead. This simple function serves the purpose of
 *   controlling this parameter after the channel has been configured.
 *   Please be aware the effects of the non-atomic Read-Modify-Write cycle!
 *
 * @param[in] startDelay
 *   Number of LFACLK cycles to delay. Valid range: 0-3 (2 bit).
 ******************************************************************************/
void LESENSE_StartDelaySet(uint8_t const startDelay)
{
  uint32_t tmp; /* temporary storage of the TIMCTRL register value */


  /* Sanity check of startDelay. */
  EFM_ASSERT(startDelay < 4U);

  /* Save the TIMCTRL register value to tmp.
   * Please be aware the effects of the non-atomic Read-Modify-Write cycle! */
  tmp = LESENSE->TIMCTRL & ~(_LESENSE_TIMCTRL_STARTDLY_MASK);
  /* Setting the requested startDelay to the TIMCTRL register. */
  tmp |= (uint32_t)startDelay << _LESENSE_TIMCTRL_STARTDLY_SHIFT;

  /* Write the new value to the TIMCTRL register. */
  LESENSE->TIMCTRL = tmp;
}


/***************************************************************************//**
 * @brief
 *   Set clock division for LESENSE timers.
 *
 * @details
 *   Use this function to configure the clock division for the LESENSE timers
 *   used for excitation timing.
 *   The division setting is global, but the clock source can be selected for
 *   each channel using LESENSE_ChannelConfig() function, please refer to the
 *   documentation of it for more details.
 *
 * @note
 *   If AUXHFRCO is used for excitation timing, LFACLK can not exceed 500kHz.
 *   LFACLK can not exceed 50kHz if the ACMP threshold level (ACMPTHRES) is not
 *   equal for all channels.
 *
 * @param[in] clk
 *   Select clock to prescale.
 *    @li lesenseClkHF - set AUXHFRCO clock divisor for HF timer.
 *    @li lesenseClkLF - set LFACLKles clock divisor for LF timer.
 *
 * @param[in] clkDiv
 *   Clock divisor value. Valid range depends on the @p clk value.
 ******************************************************************************/
void LESENSE_ClkDivSet(LESENSE_ChClk_TypeDef const clk,
                       LESENSE_ClkPresc_TypeDef const clkDiv)
{
  uint32_t tmp;


  /* Select clock to prescale */
  switch (clk)
  {
  case lesenseClkHF:
  {
    /* Sanity check of clock divisor for HF clock. */
    EFM_ASSERT((uint32_t)clkDiv <= lesenseClkDiv_8);

    /* Clear current AUXPRESC settings. */
    tmp = LESENSE->TIMCTRL & ~(_LESENSE_TIMCTRL_AUXPRESC_MASK);

    /* Set new values in tmp while reserving other settings. */
    tmp |= ((uint32_t)clkDiv << _LESENSE_TIMCTRL_AUXPRESC_SHIFT);

    /* Set values in LESENSE_TIMCTRL register. */
    LESENSE->TIMCTRL = tmp;
  }
  break;

  case lesenseClkLF:
  {
    /* Clear current LFPRESC settings. */
    tmp = LESENSE->TIMCTRL & ~(_LESENSE_TIMCTRL_LFPRESC_MASK);

    /* Set new values in tmp while reserving other settings. */
    tmp |= ((uint32_t)clkDiv << _LESENSE_TIMCTRL_LFPRESC_SHIFT);

    /* Set values in LESENSE_TIMCTRL register. */
    LESENSE->TIMCTRL = tmp;
  }
  break;

  default:
  {
    EFM_ASSERT(0);
  }
  break;
  }
}


/***************************************************************************//**
 * @brief
 *   Configure all (16) LESENSE sensor channels.
 *
 * @details
 *   This function configures all the sensor channels of LESENSE interface.
 *   Please refer to the configuration parameter type definition
 *   (LESENSE_ChAll_TypeDef) for more details.
 *
 * @note
 *   Channels can be configured individually using LESENSE_ChannelConfig()
 *   function.
 *   Notice that pins used by the LESENSE module must be properly configured
 *   by the user explicitly, in order for the LESENSE to work as intended.
 *   (When configuring pins, one should remember to consider the sequence of
 *   configuration, in order to avoid unintended pulses/glitches on output
 *   pins.)
 *
 * @param[in] confChAll
 *   Configuration structure for all (16) LESENSE sensor channels.
 ******************************************************************************/
void LESENSE_ChannelAllConfig(LESENSE_ChAll_TypeDef const *confChAll)
{
  uint32_t i;


  /* Iterate through all the 16 channels */
  for (i = 0U; i < 16U; ++i)
  {
    /* Configure scan channels. */
    LESENSE_ChannelConfig(&confChAll->Ch[i], i);
  }
}


/***************************************************************************//**
 * @brief
 *   Configure a single LESENSE sensor channel.
 *
 * @details
 *   This function configures a single sensor channel of the LESENSE interface.
 *   Please refer to the configuration parameter type definition
 *   (LESENSE_ChDesc_TypeDef) for more details.
 *
 * @note
 *   This function has been designed to minimize the effects of sensor channel
 *   reconfiguration while LESENSE is in operation, however one shall be aware
 *   of these effects and the right timing of calling this function.
 *   Parameter @p useAltEx must be true in the channel configuration in order to
 *   use alternate excitation pins.
 *
 * @param[in] confCh
 *   Configuration structure for a single LESENSE sensor channel.
 *
 * @param[in] chIdx
 *   Channel index to configure (0-15).
 ******************************************************************************/
void LESENSE_ChannelConfig(LESENSE_ChDesc_TypeDef const *confCh,
                           uint32_t const chIdx)
{
  uint32_t tmp; /* Service variable. */


  /* Sanity check of configuration parameters */
  EFM_ASSERT(chIdx < 16U);
  EFM_ASSERT(confCh->exTime < 64U);
  EFM_ASSERT(confCh->sampleDelay < 128U);
  EFM_ASSERT(confCh->measDelay < 128U);
  /* Not a complete assert, as the max. value of acmpThres depends on other
   * configuration parameters, check the parameter description of acmpThres for
   * for more details! */
  EFM_ASSERT(confCh->acmpThres < 4096U);
  EFM_ASSERT(!(confCh->chPinExMode == lesenseChPinExDACOut &&
               (chIdx != 2U) && (chIdx != 3U) && (chIdx != 4U) && (chIdx != 5U)));
  EFM_ASSERT(!(confCh->chPinIdleMode == lesenseChPinIdleDACCh1 &&
               ((chIdx != 12U) && (chIdx != 13U) && (chIdx != 14U) && (chIdx != 15U))));
  EFM_ASSERT(!(confCh->chPinIdleMode == lesenseChPinIdleDACCh0 &&
               ((chIdx != 0U) && (chIdx != 1U) && (chIdx != 2U) && (chIdx != 3U))));


  /* Configure chIdx setup in LESENSE idle phase.
   * Read-modify-write in order to support reconfiguration during LESENSE
   * operation. */
  tmp               = (LESENSE->IDLECONF & ~((uint32_t)0x3UL << (chIdx * 2UL)));
  tmp              |= ((uint32_t)confCh->chPinIdleMode << (chIdx * 2UL));
  LESENSE->IDLECONF = tmp;

  /* Channel specific timing configuration on scan channel chIdx.
   * Set excitation time, sampling delay, measurement delay. */
  LESENSE_ChannelTimingSet(chIdx,
                           (uint32_t)confCh->exTime,
                           (uint32_t)confCh->sampleDelay,
                           (uint32_t)confCh->measDelay);

  /* Channel specific configuration of clocks, sample mode, excitation pin mode
   * alternate excitation usage and interrupt mode on scan channel chIdx in
   * LESENSE_CHchIdx_INTERACT. */
  LESENSE->CH[chIdx].INTERACT = ((uint32_t)confCh->exClk <<
                                 _LESENSE_CH_INTERACT_EXCLK_SHIFT) |
                                ((uint32_t)confCh->sampleClk <<
                                 _LESENSE_CH_INTERACT_SAMPLECLK_SHIFT) |
                                (uint32_t)confCh->sampleMode |
                                (uint32_t)confCh->intMode |
                                (uint32_t)confCh->chPinExMode |
                                ((uint32_t)confCh->useAltEx <<
                                 _LESENSE_CH_INTERACT_ALTEX_SHIFT);

  /* Configure channel specific counter comparison mode, optional result
   * forwarding to decoder, optional counter value storing and optional result
   * inverting on scan channel chIdx in LESENSE_CHchIdx_EVAL. */
  LESENSE->CH[chIdx].EVAL = (uint32_t)confCh->compMode |
                            ((uint32_t)confCh->shiftRes <<
                             _LESENSE_CH_EVAL_DECODE_SHIFT) |
                            ((uint32_t)confCh->storeCntRes <<
                             _LESENSE_CH_EVAL_STRSAMPLE_SHIFT) |
                            ((uint32_t)confCh->invRes <<
                             _LESENSE_CH_EVAL_SCANRESINV_SHIFT);

  /* Configure analog comparator (ACMP) threshold and decision threshold for
   * counter separately with the function provided for that. */
  LESENSE_ChannelThresSet(chIdx,
                         (uint32_t)confCh->acmpThres,
                         (uint32_t)confCh->cntThres);

  /* Enable/disable interrupts on channel.
   * Note: BITBAND_Peripheral() function is used for setting/clearing single
   * bit peripheral register bitfields. Read the function description in
   * efm32_bitband.h for more details. */
  BITBAND_Peripheral(&(LESENSE->IEN),
                     (uint32_t)chIdx,
                     (uint32_t)confCh->enaInt);

  /* Enable/disable CHchIdx pin. */
  BITBAND_Peripheral(&(LESENSE->ROUTE),
                     (uint32_t)chIdx,
                     (uint32_t)confCh->enaPin);

  /* Enable/disable scan channel chIdx. */
  BITBAND_Peripheral(&(LESENSE->CHEN),
                     (uint32_t)chIdx,
                     (uint32_t)confCh->enaScanCh);
}


/***************************************************************************//**
 * @brief
 *   Configure the LESENSE alternate excitation pins.
 *
 * @details
 *   This function configures the alternate excitation channels of the LESENSE
 *   interface. Please refer to the configuration parameter type definition
 *   (LESENSE_ConfAltEx_TypeDef) for more details.
 *
 * @note
 *   Parameter @p useAltEx must be true in the channel configuration structrure
 *   (LESENSE_ChDesc_TypeDef) in order to use alternate excitation pins on the
 *   channel.
 *
 * @param[in] confAltEx
 *   Configuration structure for LESENSE alternate excitation pins.
 ******************************************************************************/
void LESENSE_AltExConfig(LESENSE_ConfAltEx_TypeDef const *confAltEx)
{
  uint32_t i;
  uint32_t tmp;


  /* Configure alternate excitation mapping.
   * Atomic read-modify-write using BITBAND_Peripheral function in order to
   * support reconfiguration during LESENSE operation. */
  BITBAND_Peripheral(&(LESENSE->CTRL),
                     _LESENSE_CTRL_ALTEXMAP_SHIFT,
                     (uint32_t)confAltEx->altExMap);

  /* Iterate through all the 8 alternate excitation channels */
  for (i = 0U; i < 8U; ++i)
  {
    /* Enable/disable alternate excitation pin i.
     * Atomic read-modify-write using BITBAND_Peripheral function in order to
     * support reconfiguration during LESENSE operation. */
    BITBAND_Peripheral(&(LESENSE->ROUTE),
                       (16UL + i),
                       (uint32_t)confAltEx->AltEx[i].enablePin);

    /* Setup the idle phase state of alternate excitation pin i.
     * Read-modify-write in order to support reconfiguration during LESENSE
     * operation. */
    tmp                = (LESENSE->ALTEXCONF & ~((uint32_t)0x3UL << (i * 2UL)));
    tmp               |= ((uint32_t)confAltEx->AltEx[i].idleConf << (i * 2UL));
    LESENSE->ALTEXCONF = tmp;

    /* Enable/disable always excite on channel i */
    BITBAND_Peripheral(&(LESENSE->ALTEXCONF),
                       (16UL + i),
                       (uint32_t)confAltEx->AltEx[i].alwaysEx);
  }
}


/***************************************************************************//**
 * @brief
 *   Enable/disable LESENSE scan channel and the pin assigned to it.
 *
 * @details
 *   Use this function to enable/disable a selected LESENSE scan channel and the
 *   pin assigned to.
 *
 * @note
 *   Users can enable/disable scan channels and the channel pin by
 *   LESENSE_ChannelConfig() function, but only with a significant overhead.
 *   This simple function serves the purpose of controlling these parameters
 *   after the channel has been configured.
 *
 * @param[in] chIdx
 *   Identifier of the scan channel. Valid range: 0-15.
 *
 * @param[in] enaScanCh
 *   Enable/disable the selected scan channel by setting this parameter to
 *   true/false respectively.
 *
 * @param[in] enaPin
 *   Enable/disable the pin assigned to the channel selected by @p chIdx.
 ******************************************************************************/
void LESENSE_ChannelEnable(uint8_t const chIdx,
                           bool const enaScanCh,
                           bool const enaPin)
{
  /* Enable/disable the assigned pin of scan channel chIdx.
   * Note: BITBAND_Peripheral() function is used for setting/clearing single
   * bit peripheral register bitfields. Read the function description in
   * efm32_bitband.h for more details. */
  BITBAND_Peripheral(&(LESENSE->ROUTE),
                     (uint32_t)chIdx,
                     (uint32_t)enaPin);

  /* Enable/disable scan channel chIdx. */
  BITBAND_Peripheral(&(LESENSE->CHEN),
                     (uint32_t)chIdx,
                     (uint32_t)enaScanCh);
}


/***************************************************************************//**
 * @brief
 *   Enable/disable LESENSE scan channel and the pin assigned to it.
 *
 * @details
 *   Use this function to enable/disable LESENSE scan channels and the pins
 *   assigned to them using a mask.
 *
 * @note
 *   Users can enable/disable scan channels and channel pins by using
 *   LESENSE_ChannelAllConfig() function, but only with a significant overhead.
 *   This simple function serves the purpose of controlling these parameters
 *   after the channel has been configured.
 *
 * @param[in] chMask
 *   Set the corresponding bit to 1 to enable, 0 to disable the selected scan
 *   channel.
 *
 * @param[in] pinMask
 *   Set the corresponding bit to 1 to enable, 0 to disable the pin on selected
 *   channel.
 ******************************************************************************/
void LESENSE_ChannelEnableMask(uint16_t chMask, uint16_t pinMask)
{
  /* Enable/disable all channels at once according to the mask. */
  LESENSE->CHEN = chMask;
  /* Enable/disable all channel pins at once according to the mask. */
  LESENSE->ROUTE = pinMask;
}


/***************************************************************************//**
 * @brief
 *   Set LESENSE channel timing parameters.
 *
 * @details
 *   Use this function to set timing parameters on a selected LESENSE channel.
 *
 * @note
 *   Users can configure the channel timing parameters by
 *   LESENSE_ChannelConfig() function, but only with a significant overhead.
 *   This simple function serves the purpose of controlling these parameters
 *   after the channel has been configured.
 *
 * @param[in] chIdx
 *   Identifier of the scan channel. Valid range: 0-15.
 *
 * @param[in] exTime
 *   Excitation time on chIdx. Excitation will last exTime+1 excitation clock
 *   cycles. Valid range: 0-63 (6 bits).
 *
 * @param[in] sampleDelay
 *   Sample delay on chIdx. Sampling will occur after sampleDelay+1 sample clock
 *   cycles. Valid range: 0-127 (7 bits).
 *
 * @param[in] measDelay
 *   Measure delay on chIdx. Sensor measuring is delayed for measDelay+1
 *   excitation clock cycles. Valid range: 0-127 (7 bits).
 ******************************************************************************/
void LESENSE_ChannelTimingSet(uint8_t const chIdx,
                              uint8_t const exTime,
                              uint8_t const sampleDelay,
                              uint8_t const measDelay)
{
  /* Sanity check of parameters. */
  EFM_ASSERT(exTime < 64U);
  EFM_ASSERT(sampleDelay < 128U);
  EFM_ASSERT(measDelay < 128U);

  /* Channel specific timing configuration on scan channel chIdx.
   * Setting excitation time, sampling delay, measurement delay. */
  LESENSE->CH[chIdx].TIMING = ((uint32_t)exTime <<
                               _LESENSE_CH_TIMING_EXTIME_SHIFT) |
                              ((uint32_t)sampleDelay <<
                               _LESENSE_CH_TIMING_SAMPLEDLY_SHIFT) |
                              ((uint32_t)measDelay <<
                               _LESENSE_CH_TIMING_MEASUREDLY_SHIFT);
}


/***************************************************************************//**
 * @brief
 *   Set LESENSE channel threshold parameters.
 *
 * @details
 *   Use this function to set threshold parameters on a selected LESENSE
 *   channel.
 *
 * @note
 *   Users can configure the channel threshold parameters by
 *   LESENSE_ChannelConfig() function, but only with a significant overhead.
 *   This simple function serves the purpose of controlling these parameters
 *   after the channel has been configured.
 *
 * @param[in] chIdx
 *   Identifier of the scan channel. Valid range: 0-15.
 *
 * @param[in] acmpThres
 *   ACMP threshold.
 *   @li If perCtrl.dacCh0Data or perCtrl.dacCh1Data is set to
 *   #lesenseDACIfData, acmpThres defines the 12-bit DAC data in the
 *   corresponding data register of the DAC interface (DACn_CH0DATA and
 *   DACn_CH1DATA). In this case, the valid range is: 0-4095 (12 bits).
 *
 *   @li If perCtrl.dacCh0Data or perCtrl.dacCh1Data is set to
 *   #lesenseACMPThres, acmpThres defines the 6-bit Vdd scaling factor of ACMP
 *   negative input (VDDLEVEL in ACMP_INPUTSEL register). In this case, the
 *   valid range is: 0-63 (6 bits).
 *
 * @param[in] cntThres
 *   Decision threshold for counter comparison.
 *   Valid range: 0-65535 (16 bits).
 ******************************************************************************/
void LESENSE_ChannelThresSet(uint8_t const chIdx,
                             uint16_t const acmpThres,
                             uint16_t const cntThres)
{
  uint32_t tmp; /* temporary storage */


  /* Sanity check for acmpThres only, cntThres is 16bit value. */
  EFM_ASSERT(acmpThres < 4096U);
  /* Sanity check for LESENSE channel id. */
  EFM_ASSERT(chIdx < 16);

  /* Save the INTERACT register value of channel chIdx to tmp.
   * Please be aware the effects of the non-atomic Read-Modify-Write cycle! */
  tmp = LESENSE->CH[chIdx].INTERACT & ~(_LESENSE_CH_INTERACT_ACMPTHRES_MASK);
  /* Set the ACMP threshold value to the INTERACT register of channel chIdx. */
  tmp |= (uint32_t)acmpThres << _LESENSE_CH_INTERACT_ACMPTHRES_SHIFT;
  /* Write the new value to the INTERACT register. */
  LESENSE->CH[chIdx].INTERACT = tmp;

  /* Save the EVAL register value of channel chIdx to tmp.
   * Please be aware the effects of the non-atomic Read-Modify-Write cycle! */
  tmp = LESENSE->CH[chIdx].EVAL & ~(_LESENSE_CH_EVAL_COMPTHRES_MASK);
  /* Set the counter threshold value to the INTERACT register of channel chIdx. */
  tmp |= (uint32_t)cntThres << _LESENSE_CH_EVAL_COMPTHRES_SHIFT;
  /* Write the new value to the EVAL register. */
  LESENSE->CH[chIdx].EVAL = tmp;
}


/***************************************************************************//**
 * @brief
 *   Configure all LESENSE decoder states.
 *
 * @details
 *   This function configures all the decoder states of the LESENSE interface.
 *   Please refer to the configuration parameter type definition
 *   (LESENSE_DecStAll_TypeDef) for more details.
 *
 * @note
 *   Decoder states can be configured individually using
 *   LESENSE_DecoderStateConfig() function.
 *
 * @param[in] confDecStAll
 *   Configuration structure for all (16) LESENSE decoder states.
 ******************************************************************************/
void LESENSE_DecoderStateAllConfig(LESENSE_DecStAll_TypeDef const *confDecStAll)
{
  uint32_t i;


  /* Iterate through all the 16 decoder states. */
  for (i = 0U; i < 16U; ++i)
  {
    /* Configure decoder state i. */
    LESENSE_DecoderStateConfig(&confDecStAll->St[i], i);
  }
}


/***************************************************************************//**
 * @brief
 *   Configure a single LESENSE decoder state.
 *
 * @details
 *   This function configures a single decoder state of the LESENSE interface.
 *   Please refer to the configuration parameter type definition
 *   (LESENSE_DecStDesc_TypeDef) for more details.
 *
 * @param[in] confDecSt
 *   Configuration structure for a single LESENSE decoder state.
 *
 * @param[in] decSt
 *   Decoder state index to configure (0-15).
 ******************************************************************************/
void LESENSE_DecoderStateConfig(LESENSE_DecStDesc_TypeDef const *confDecSt,
                                uint32_t const decSt)
{
  /* Sanity check of configuration parameters */
  EFM_ASSERT(decSt < 16U);
  EFM_ASSERT((uint32_t)confDecSt->confA.compMask < 16U);
  EFM_ASSERT((uint32_t)confDecSt->confA.compVal < 16U);
  EFM_ASSERT((uint32_t)confDecSt->confA.nextState < 16U);
  EFM_ASSERT((uint32_t)confDecSt->confB.compMask < 16U);
  EFM_ASSERT((uint32_t)confDecSt->confB.compVal < 16U);
  EFM_ASSERT((uint32_t)confDecSt->confB.nextState < 16U);

  /* Configure state descriptor A (LESENSE_STi_TCONFA) for decoder state i.
   * Setting sensor compare value, sensor mask, next state index,
   * transition action, interrupt flag option and state descriptor chaining
   * configurations. */
  LESENSE->ST[decSt].TCONFA = (uint32_t)confDecSt->confA.prsAct |
                              ((uint32_t)confDecSt->confA.compMask <<
                               _LESENSE_ST_TCONFA_MASK_SHIFT) |
                              ((uint32_t)confDecSt->confA.compVal <<
                               _LESENSE_ST_TCONFA_COMP_SHIFT) |
                              ((uint32_t)confDecSt->confA.nextState <<
                               _LESENSE_ST_TCONFA_NEXTSTATE_SHIFT) |
                              ((uint32_t)confDecSt->confA.setInt <<
                               _LESENSE_ST_TCONFA_SETIF_SHIFT) |
                              ((uint32_t)confDecSt->chainDesc <<
                               _LESENSE_ST_TCONFA_CHAIN_SHIFT);

  /* Configure state descriptor Bi (LESENSE_STi_TCONFB).
   * Setting sensor compare value, sensor mask, next state index, transition
   * action and interrupt flag option configurations. */
  LESENSE->ST[decSt].TCONFB = (uint32_t)confDecSt->confB.prsAct |
                              ((uint32_t)confDecSt->confB.compMask <<
                               _LESENSE_ST_TCONFB_MASK_SHIFT) |
                              ((uint32_t)confDecSt->confB.compVal <<
                               _LESENSE_ST_TCONFB_COMP_SHIFT) |
                              ((uint32_t)confDecSt->confB.nextState <<
                               _LESENSE_ST_TCONFB_NEXTSTATE_SHIFT) |
                              ((uint32_t)confDecSt->confB.setInt <<
                               _LESENSE_ST_TCONFB_SETIF_SHIFT);
}


/***************************************************************************//**
 * @brief
 *   Set LESENSE decoder state.
 *
 * @details
 *   This function can be used for setting the initial state of the LESENSE
 *   decoder.
 *
 * @note
 *   Make sure the LESENSE decoder state is initialized by this function before
 *   enabling the decoder!
 *
 * @param[in] decSt
 *   Decoder state to set as current state. Valid range: 0-15
 ******************************************************************************/
void LESENSE_DecoderStateSet(uint32_t decSt)
{
  EFM_ASSERT(decSt < 16U);

  LESENSE->DECSTATE = decSt & _LESENSE_DECSTATE_DECSTATE_MASK;
}


/***************************************************************************//**
 * @brief
 *   Get the current state of the LESENSE decoder.
 *
 * @return
 *   This function returns the value of LESENSE_DECSTATE register that
 *   represents the current state of the LESENSE decoder.
 ******************************************************************************/
uint32_t LESENSE_DecoderStateGet(void)
{
  return LESENSE->DECSTATE & _LESENSE_DECSTATE_DECSTATE_MASK;
}


/***************************************************************************//**
 * @brief
 *   Reset the LESENSE module.
 *
 * @details
 *   Use this function to reset the LESENSE registers.
 *
 * @note
 *   Resetting LESENSE registers is required in each reset or power-on cycle in
 *   order to configure the default values of the RAM mapped LESENSE registers.
 *   LESENSE_Reset() can be called on initialization by setting the @p reqReset
 *   parameter to true in LESENSE_Init().
 ******************************************************************************/
void LESENSE_Reset(void)
{
  uint32_t i;


  /* Disable all LESENSE interrupts first */
  LESENSE->IEN = _LESENSE_IEN_RESETVALUE;

  /* Clear all pending LESENSE interrupts */
  LESENSE->IFC = _LESENSE_IFC_MASK;

  /* Stop the decoder */
  LESENSE->DECCTRL |= LESENSE_DECCTRL_DISABLE;

  /* Stop sensor scan and clear result buffer */
  LESENSE->CMD = (LESENSE_CMD_STOP | LESENSE_CMD_CLEARBUF);

  /* Reset LESENSE configuration registers */
  LESENSE->CTRL      = _LESENSE_CTRL_RESETVALUE;
  LESENSE->PERCTRL   = _LESENSE_PERCTRL_RESETVALUE;
  LESENSE->DECCTRL   = _LESENSE_DECCTRL_RESETVALUE;
  LESENSE->BIASCTRL  = _LESENSE_BIASCTRL_RESETVALUE;
  LESENSE->CHEN      = _LESENSE_CHEN_RESETVALUE;
  LESENSE->IDLECONF  = _LESENSE_IDLECONF_RESETVALUE;
  LESENSE->ALTEXCONF = _LESENSE_ALTEXCONF_RESETVALUE;

  /* Disable LESENSE to control GPIO pins */
  LESENSE->ROUTE = _LESENSE_ROUTE_RESETVALUE;

  /* Reset all channel configuration registers */
  for (i = 0U; i < 16U; ++i)
  {
    LESENSE->CH[i].TIMING   = _LESENSE_CH_TIMING_RESETVALUE;
    LESENSE->CH[i].INTERACT = _LESENSE_CH_INTERACT_RESETVALUE;
    LESENSE->CH[i].EVAL     = _LESENSE_CH_EVAL_RESETVALUE;
  }

  /* Reset all decoder state configuration registers */
  for (i = 0U; i < 16U; ++i)
  {
    LESENSE->ST[i].TCONFA = _LESENSE_ST_TCONFA_RESETVALUE;
    LESENSE->ST[i].TCONFB = _LESENSE_ST_TCONFB_RESETVALUE;
  }
}


/** @} (end addtogroup LESENSE) */
/** @} (end addtogroup EM_Library) */

#endif /* defined(LESENSE_COUNT) && (LESENSE_COUNT > 0) */
