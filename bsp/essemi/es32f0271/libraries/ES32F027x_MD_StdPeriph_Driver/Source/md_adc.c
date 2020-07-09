/**
  ******************************************************************************
  * @file    md_adc.c
  * @brief   ES32F0271 ADC Source File.
  *
  * @version V1.00.01
  * @data    7/01/2019
  * @author  Taipei AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */


/* Includes -------------------------------------------------------------------*/
#include "md_adc.h"
#include "md_syscfg.h"
#include <stdio.h>


/** @addtogroup Micro_Driver
  * @{
  */


/** @defgroup ADC ADC
  * @brief ADC micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
#define Reference_V1  1       //First reference point
#define Reference_V2  2        //Second reference point

double Ideal_V1;
double Ideal_V2;
double Reference_V1_ADCValue ;
double Reference_V2_ADCValue ;

/* Private function prototypes ------------------------------------------------*/
void (*md_adc_SS0_sample[])(ADC_TypeDef *, uint32_t) =
{
  md_adc_set_ss0_mux0_mux0,
  md_adc_set_ss0_mux0_mux1,
  md_adc_set_ss0_mux0_mux2,
  md_adc_set_ss0_mux0_mux3,
  md_adc_set_ss0_mux0_mux4,
  md_adc_set_ss0_mux0_mux5,
  md_adc_set_ss0_mux0_mux6,
  md_adc_set_ss0_mux0_mux7,
  md_adc_set_ss0_mux1_mux8,
  md_adc_set_ss0_mux1_mux9,
  md_adc_set_ss0_mux1_mux10,
  md_adc_set_ss0_mux1_mux11,
  md_adc_set_ss0_mux1_mux12,
  md_adc_set_ss0_mux1_mux13,
  md_adc_set_ss0_mux1_mux14,
  md_adc_set_ss0_mux1_mux15
};

void (*md_adc_SS1_sample[])(ADC_TypeDef *, uint32_t) =
{
  md_adc_set_ss0_mux0_mux0,
  md_adc_set_ss0_mux0_mux1,
  md_adc_set_ss0_mux0_mux2,
  md_adc_set_ss0_mux0_mux3,
  md_adc_set_ss0_mux0_mux4,
  md_adc_set_ss0_mux0_mux5,
  md_adc_set_ss0_mux0_mux6,
  md_adc_set_ss0_mux0_mux7,
};

void (*md_adc_SS2_sample[])(ADC_TypeDef *, uint32_t) =
{
  md_adc_set_ss0_mux0_mux0,
  md_adc_set_ss0_mux0_mux1,
  md_adc_set_ss0_mux0_mux2,
  md_adc_set_ss0_mux0_mux3,
};

/* Public functions -----------------------------------------------------------*/
/** @defgroup ADC_PUB_FUNC ADC Public Functions
  * @brief ADC Public Functions
  * @{
  */
/**
  * @brief  ADC Initialization Function.
  * @param  ADC Instance.
  * @param  channel
  * @retval None
  */
void md_adc_init(ADC_TypeDef *ADCx, md_adc_inittypedef *ADC_InitStruct, uint8_t *channel)
{
  uint8_t i = 0;

  md_syscfg_enable_cfg_currgen(SYSCFG);
  md_syscfg_set_cfg_vlrs(SYSCFG, ADC_InitStruct->VRLS);
  md_syscfg_enable_cfg_vrefen(SYSCFG);

  if (ADC_InitStruct->SSx == 0)
  {
    md_adc_set_ss0_con_sel(ADC, ADC_InitStruct->Sel);
    md_adc_set_ss0_con_type(ADC, ADC_InitStruct->Type);

    md_adc_set_srate_cntini(ADC, ADC_InitStruct->Cntini);
    md_adc_set_srate_cnt(ADC, ADC_InitStruct->Cnt);
    md_adc_set_frf_ffrst(ADC);


    for (i = 0; i < 16; i++)
      md_adc_SS0_sample[i](ADC, channel[i]);

    md_adc_enable_ier_ss0ie(ADC);
    md_adc_set_ss0_end_end(ADC, ADC_InitStruct->End);
    md_adc_enable_ss0_end_ie15(ADC);
    md_adc_set_gainh_ch8pga(ADC, MD_ADC_GAIN_CHPGA_X1);


    md_adc_set_srate(ADC, (ADC_InitStruct->Ckdiv) | ADC_SRATE_CKEN_MSK);
    md_adc_enable_ssen_ss0en(ADC);
  }
  else if (ADC_InitStruct->SSx == 1)
  {
    md_adc_set_ss1_con_sel(ADC, ADC_InitStruct->Sel);
    md_adc_set_ss1_con_type(ADC, ADC_InitStruct->Type);

    md_adc_set_srate_cntini(ADC, ADC_InitStruct->Cntini);
    md_adc_set_srate_cnt(ADC, ADC_InitStruct->Cnt);
    md_adc_set_frf_ffrst(ADC);

    for (i = 0; i < 8; i++)
      md_adc_SS1_sample[i](ADC, channel[i]);

    md_adc_enable_ier_ss1ie(ADC);
    md_adc_set_ss1_end_end(ADC, ADC_InitStruct->End);
    md_adc_enable_ss1_end_ie7(ADC);
    md_adc_set_gainh_ch8pga(ADC, MD_ADC_GAIN_CHPGA_X1);

    md_adc_set_srate(ADC, (ADC_InitStruct->Ckdiv) | ADC_SRATE_CKEN_MSK);
    md_adc_enable_ssen_ss1en(ADC);
  }
  else if (ADC_InitStruct->SSx == 2)
  {
    md_adc_set_ss2_con_sel(ADC, ADC_InitStruct->Sel);
    md_adc_set_ss2_con_type(ADC, ADC_InitStruct->Type);

    md_adc_set_srate_cntini(ADC, ADC_InitStruct->Cntini);
    md_adc_set_srate_cnt(ADC, ADC_InitStruct->Cnt);
    md_adc_set_frf_ffrst(ADC);

    for (i = 0; i < 4; i++)
      md_adc_SS2_sample[i](ADC, channel[i]);

    md_adc_enable_ier_ss2ie(ADC);
    md_adc_set_ss2_end_end(ADC, ADC_InitStruct->End);
    md_adc_enable_ss2_end_ie3(ADC);
    md_adc_set_gainh_ch8pga(ADC, MD_ADC_GAIN_CHPGA_X1);

    md_adc_set_srate(ADC, (ADC_InitStruct->Ckdiv) | ADC_SRATE_CKEN_MSK);
    md_adc_enable_ssen_ss2en(ADC);
  }
  else
  {
    md_adc_set_ss3_con_sel(ADC, ADC_InitStruct->Sel);
    md_adc_set_ss3_con_type(ADC, ADC_InitStruct->Type);

    md_adc_set_srate_cntini(ADC, ADC_InitStruct->Cntini);
    md_adc_set_srate_cnt(ADC, ADC_InitStruct->Cnt);
    md_adc_set_frf_ffrst(ADC);

    MODIFY_REG(ADC->SS3_MUX0, ADC_SS3_MUX0_MUX0_MSK, MD_ADC_SS_MUX_ADIN8 << ADC_SS3_MUX0_MUX0_POSS);

    md_adc_enable_ier_ss3ie(ADC);
    md_adc_set_ss3_end_end(ADC, ADC_InitStruct->End);
    md_adc_enable_ss3_end_ie0(ADC);
    md_adc_set_gainh_ch8pga(ADC, MD_ADC_GAIN_CHPGA_X1);

    md_adc_set_srate(ADC, (ADC_InitStruct->Ckdiv) | ADC_SRATE_CKEN_MSK);
    md_adc_enable_ssen_ss3en(ADC);
  }
}


/**
  * @brief  Get the ADC calibration offset data
  * @param  vref: reference v
  * @param  vdd: external v
  * @param  offset:  Get Offset
  * @param  coefficient: Get Coefficient
  * @retval None
  */
void md_adc_calibration_data(double vdd, double vref,double *offset,double *coefficient)
{
  Ideal_V1 = Reference_V1 / vref * 4096;
  Ideal_V2 = Reference_V2 / vref * 4096;
  if (vdd == 5 && vref == 5)
  {
    if ((FC->ADCTRIM_VDD5V_VREF5V >> 24) == 0xA5)
    {
      Reference_V1_ADCValue = FC->ADCTRIM_VDD5V_VREF5V & 0xFFF;
      Reference_V2_ADCValue = (FC->ADCTRIM_VDD5V_VREF5V >> 12) & 0xFFF;
    }
  }
  else if (vdd == 3.3 && vref == 3.3)
  {
    if ((FC->ADCTRIM_VDD3V3_VREF3V3 >> 24) == 0xA5)
    {
      Reference_V1_ADCValue = FC->ADCTRIM_VDD3V3_VREF3V3 & 0xFFF;
      Reference_V2_ADCValue = (FC->ADCTRIM_VDD3V3_VREF3V3 >> 12) & 0xFFF;
    }
  }
  else if ((vdd == 5 && vref == 2.5) || (vdd == 3.3 && vref == 2.5))
  {
    if ((FC->ADCTRIM_VDD5V_VREF2V5 >> 24) == 0xA5)
    {
      Reference_V1_ADCValue = FC->ADCTRIM_VDD5V_VREF2V5 & 0xFFF;
      Reference_V2_ADCValue = (FC->ADCTRIM_VDD5V_VREF2V5 >> 12) & 0xFFF;
    }
  }
  else
  {

  }

//  Reference_V1_ADCValue = 115 ;
//  Reference_V2_ADCValue = 365 ;

  printf("Ideal_V1:%.2f\r\n", Ideal_V1);
  printf("Ideal_V2:%.2f\r\n", Ideal_V2);
  printf("Reference_V1_ADCValue:%.2f\r\n", Reference_V1_ADCValue);
  printf("Reference_V2_ADCValue:%.2f\r\n", Reference_V2_ADCValue);

  *offset = (Reference_V2 * Reference_V1_ADCValue - Reference_V1 * Reference_V2_ADCValue) / (Reference_V2 - Reference_V1);
  printf("Offset=%.2f\r\n", *offset);
  *coefficient = Ideal_V1 / (Reference_V1_ADCValue - *offset);
  printf("Coefficient=%.2f\r\n", *coefficient);
}

/**
  * @brief  Get the ADC fixed data
  * @param  SSx: Sequence SSx
  * @param  offset:input offset
  * @param  coefficient: input coefficient
  * @param  calibration :get calibration result
  * @retval None
  */

void md_adc_get_data(uint8_t SSx,double offset,double coefficient, uint16_t *calibration)
{
  uint16_t i, data, s_times;
  double calibration_value = 0;

  if (SSx == 0)
    s_times = 16;
  else if (SSx == 1)
    s_times = 8;
  else if (SSx == 2)
    s_times = 4;
  else
    s_times = 1;

  for (i = 0; i < s_times; i++)
  {
    if(SSx == 0)
     data = md_adc_get_ss0_data(ADC);
    else if(SSx == 1)
     data = md_adc_get_ss1_data(ADC);
    else if(SSx == 2) 
     data = md_adc_get_ss2_data(ADC);
    else
     data = md_adc_get_ss3_data(ADC);     
    if(data >= 4095)
      data = 4095;
    printf("data = %4d\r\n",data);
    calibration_value = (data - offset) * coefficient;
    if (calibration_value >= 4095)
      calibration_value = 4095;
    *calibration++=(uint16_t)calibration_value;
  }
}
/**
  * @} ADC_PUB_FUNC ADC Public Functions
  */

/**
  * @} ADC
  */

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
