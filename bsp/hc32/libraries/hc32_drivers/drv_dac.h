/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-12     CDT          first version
 */


#ifndef __DRV_DAC_H__
#define __DRV_DAC_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
struct dac_dev_init_params
{
    char name[8];
    uint16_t vref;       /*!< Specifies the ADC reference voltage, unit is mv */
    uint16_t data_align; /*!<Specify the data alignment.
             This parameter can be a value of @ref DAC_DATAREG_ALIGN_PATTERN */
    rt_bool_t dac_adp_enable;
    uint16_t dac_adp_sel; /*!<Specify the ADCx priority to be enabled.
             This parameter can be a value of @ref DAC_ADP_SELECT */
    rt_bool_t ch1_output_enable;
    rt_bool_t ch2_output_enable;
#if defined (HC32F4A0) || defined (HC32F448) || defined (HC32F4A8)
    uint16_t ch1_data_src;
    uint16_t ch2_data_src;
#endif
    rt_bool_t ch1_amp_enable;
    rt_bool_t ch2_amp_enable;
#if defined (HC32F472)
    uint16_t ch1_amp_gain;
    uint16_t ch2_amp_gain;
#endif
};

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
int rt_hw_dac_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_DAC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
