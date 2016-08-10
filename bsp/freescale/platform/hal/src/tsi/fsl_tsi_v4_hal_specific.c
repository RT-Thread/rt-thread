/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "fsl_tsi_hal.h"
#include <assert.h>
#if FSL_FEATURE_SOC_TSI_COUNT

static int32_t TSI_HAL_MeasurementBlocking(TSI_Type * base, uint32_t electrode, uint32_t noise_mode);

uint32_t tsi_hal_gencs/*[TSI_INSTANCE_COUNT]*/;

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_EnableLowPower
* Description   : Function enables low power
*END**************************************************************************/
void TSI_HAL_EnableLowPower(TSI_Type * base)
{
    TSI_HAL_EnableStop(base);
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_Init
* Description   : Function inits the whole TSI peripheral
*
*END**************************************************************************/
void TSI_HAL_Init(TSI_Type * base)
{
    TSI_WR_GENCS(base, 0);
    tsi_hal_gencs = 0;
    TSI_WR_DATA(base, 0);
    TSI_WR_TSHD(base, 0);
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_SetConfiguration
* Description   : Function set the whole TSI peripheral by handled configuration
*
*END**************************************************************************/
void TSI_HAL_SetConfiguration(TSI_Type * base, tsi_config_t *config)
{
    assert(config != NULL);

    uint32_t is_enabled = TSI_HAL_IsModuleEnabled(base);
    uint32_t is_int_enabled = TSI_HAL_IsInterruptEnabled(base);
    
    if (is_enabled) {
        TSI_HAL_DisableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_DisableInterrupt(base);
    }
    
    TSI_HAL_SetPrescaler(base, config->ps);
    TSI_HAL_SetNumberOfScans(base, config->nscn);
    TSI_HAL_SetReferenceChargeCurrent(base, config->refchrg);
    TSI_HAL_SetElectrodeChargeCurrent(base, config->extchrg);
    TSI_HAL_SetMode(base, config->mode);
    TSI_HAL_SetOscilatorVoltageRails(base, config->dvolt);
    TSI_HAL_SetLowThreshold(base, config->thresl);
    TSI_HAL_SetHighThreshold(base, config->thresh);
    
    if (is_enabled) {
        TSI_HAL_EnableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_EnableInterrupt(base);
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_Recalibrate
* Description   : Function do recalibration process of TSI main parameters to
*                 find the gold cut on all enabled electrodes
*
*END**************************************************************************/
#define TSI_RECALIBRATE_MAX_SIGNAL_VAL (65535U)
uint32_t TSI_HAL_Recalibrate(TSI_Type * base, tsi_config_t *config, const uint32_t electrodes, const tsi_parameter_limits_t *parLimits)
{
    assert(config != NULL);

    uint32_t is_enabled = TSI_HAL_IsModuleEnabled(base);
    uint32_t is_int_enabled = TSI_HAL_IsInterruptEnabled(base);
    uint32_t lowest_signal = TSI_RECALIBRATE_MAX_SIGNAL_VAL;

    if(electrodes == 0)
    {
      return 0;
    }
    
    if (is_enabled) {
        TSI_HAL_DisableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_DisableInterrupt(base);
    }
    
    if(parLimits == NULL)
    {
      uint32_t elec;
      uint32_t res;
      /* parLimits are not used in NOISE mode so this is calibration of noise mode. */
      
      /* To determine the noise level the below algorithm can be used: */
      /*1. Initialize Rs = maxrs; Dvolt = minDv (set other configurations also) */
      config->ps = kTsiElecOscPrescaler_8div;
      config->nscn = kTsiConsecutiveScansNumber_16time;
      config->refchrg = kTsiRefOscChargeCurrent_8uA;
      config->extchrg = kTsiExtOscChargeCurrent_64uA;   /* Rs[2:0] */
      config->mode = kTsiAnalogModeSel_AutoNoise;
      config->dvolt = kTsiOscVolRails_Dv_029;           /* Dvolt 0.29V */
      config->thresl = 0;
      config->thresh = 0;
      
      TSI_HAL_SetConfiguration(base, config);
      
      
      /* get first enabled electrode */
      elec = FSL_FEATURE_TSI_CHANNEL_COUNT;/* Initialize to be an invalid value */
      for (uint32_t i = 0U; i < FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
      {
        if ((uint32_t)(1 << i) & electrodes)
        {
          elec = i;
          break;
        }
      }
        
      for(int i=0;i<4;i++)
      {
        TSI_HAL_SetOscilatorVoltageRails(base, config->dvolt);
           /* Rs[2:0] */
        config->extchrg = kTsiExtOscChargeCurrent_64uA;
        
        for(int j=0; j < 8; j++)
        {
          TSI_HAL_SetElectrodeChargeCurrent(base, config->extchrg);
          /*2. Perform a noise cycle. */
          res = TSI_HAL_MeasurementBlocking(base, elec, 1);
          
          /*3. If TSIcounter < 3, go to step 8 */
          if(res < 3)
          {
            break;
          }
          /*4. If Rs = minrs, go to step 6. */
          /*5. Reduce value of Rs. go to step 2 */
          if(config->extchrg != kTsiExtOscChargeCurrent_500nA)
          {
            config->extchrg = (tsi_external_osc_charge_current_t)((uint32_t)(config->extchrg) - 1);
          }
        }
        
        if(res < 3)
        {
          break;
        }
        /*6. If Dvolt = maxDv, go to END */
        /*7. Increase value of Dvolt. Set Rs = maxrs. go to step 2 */
        if(config->dvolt == kTsiOscVolRails_Dv_103)
        {
          config->dvolt = ((tsi_oscilator_voltage_rails_t)((uint32_t)config->dvolt - 1));
        }
      }
      /*8. Rs = maxrs, reduce value of Dvolt. */
      if(config->extchrg == kTsiExtOscChargeCurrent_500nA)
      {
        if(config->dvolt != kTsiOscVolRails_Dv_029)
        { 
          config->dvolt = ((tsi_oscilator_voltage_rails_t)((uint32_t)config->dvolt + 1));
        }
      }
      
      /*9. If Rs > minrs, (Reduce value of Rs, go to END) */
      if(config->extchrg > kTsiExtOscChargeCurrent_500nA)
      {
        config->extchrg = (tsi_external_osc_charge_current_t)((uint32_t)(config->extchrg) - 1);
      }
      
      /*10. END Get value of Rs and Dvolt. */
      TSI_HAL_SetElectrodeChargeCurrent(base, config->extchrg);
      TSI_HAL_SetOscilatorVoltageRails(base, config->dvolt);      
    }else
    {
      // Normal capacitive mode calibration
      
      TSI_HAL_SetNumberOfScans(base, config->nscn);
      TSI_HAL_SetPrescaler(base, config->ps);
      TSI_HAL_SetElectrodeChargeCurrent(base, config->extchrg);
      TSI_HAL_SetReferenceChargeCurrent(base, config->refchrg);

       TSI_HAL_EnableModule(base);

      for (uint32_t i = 0U; i < 16U; i++) 
          {
          if ((uint32_t)(1 << i) & electrodes) 
                  {
              int32_t counter = TSI_HAL_MeasurementBlocking(base, i, 0);
              if (counter < lowest_signal) {
                  lowest_signal = counter;
              }
          }
      }
    }
    
    if (!is_enabled) {
        TSI_HAL_EnableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_EnableInterrupt(base);
    }
    if (lowest_signal == TSI_RECALIBRATE_MAX_SIGNAL_VAL) {
        lowest_signal = 0U;  /* not valid */
    }

    return lowest_signal;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_MeasurementBlocking
* Description   : Function do blocking measurement of enabled electrodes
*                 It used just for recalibration process
*END**************************************************************************/
static int32_t TSI_HAL_MeasurementBlocking(TSI_Type * base, uint32_t electrode, uint32_t noise_mode)
{
    int32_t result;
    uint32_t gencs = 0;
 
    uint32_t timeout = 1000000;
    /* measure only if at least one electrode is enabled */
    TSI_HAL_EnableSoftwareTriggerScan(base);
    TSI_HAL_SetMeasuredChannelNumber(base, electrode);
    TSI_HAL_SetMode(base, TSI_HAL_GetMode(base)); /* force to HW right analog mode. */    
    TSI_HAL_EnableModule(base);
    TSI_HAL_StartSoftwareTrigger(base);
    
    //while((TSI_HAL_GetEndOfScanFlag(base) == 0U) && (--timeout))
    while(((gencs & TSI_GENCS_EOSF_MASK) == 0U) && (--timeout))
    {
      gencs = TSI_GENCS_REG(base);
      /* Do nothing, just to meet MISRA C 2004 rule 14.3 . */
    }
    
    if(timeout == 0)
    {
      result = 0;
    }else
    {
      if(noise_mode)
      {
        result = (gencs & TSI_GENCS_MODE_MASK) >> TSI_GENCS_MODE_SHIFT; //TSI_HAL_GetNoiseResult(base);
      }else
      {
        result = TSI_HAL_GetCounter(base);
      }
    }
    
    TSI_HAL_ClearEndOfScanFlag(base);
    TSI_HAL_DisableModule(base);
    
    return result;
}
#endif
