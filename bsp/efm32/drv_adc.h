/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-02-21   onelife     Initial creation for EFM32
 * 2011-07-14   onelife     Add multiple channels support for scan mode
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct efm32_adc_device_t
{
    ADC_TypeDef             *adc_device;
    rt_uint8_t              mode;
    rt_uint8_t              singleCount;
    rt_uint8_t              singleDmaChannel;
    rt_uint8_t              scanCount;
    rt_uint8_t              scanDmaChannel;
};

struct efm32_adc_control_single_t
{
    rt_uint8_t              count;
    rt_uint8_t              dmaChannel;
    ADC_InitSingle_TypeDef  *init;
};

struct efm32_adc_control_scan_t
{
    rt_uint8_t              count;
    rt_uint8_t              dmaChannel;
    ADC_InitScan_TypeDef    *init;
};

struct efm32_adc_control_t
{
    rt_uint8_t              mode;
    struct efm32_adc_control_scan_t     scan;
    struct efm32_adc_control_single_t   single;
};

struct efm32_adc_result_t
{
    rt_uint8_t              mode;
    void                    *buffer;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define ADC_MODE_SINGLE         (0x01)
#define ADC_MODE_SCAN           (0x02)
#define ADC_MODE_TAILGATE       (0x04)
#define ADC_OP_SINGLE_REPEAT    (0x10)
#define ADC_OP_SCAN_REPEAT      (0x20)
#define ADC_MASK_MODE           (0x0f)
#define ADC_MASK_OP             (0xf0)

/* Exported functions ------------------------------------------------------- */
void rt_hw_adc_init(void);

#endif /*__DRV_ADC_H__ */
