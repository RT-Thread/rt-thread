/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-07-13   onelife     Initial creation for using EFM32 ADC module to
 *                            interface the Freescale MMA7361L
 * 2011-08-02   onelife     Add digital interface support of using EFM32 IIC
 *                            module for the Freescale MMA7455L
 */

#ifndef __DEV_ACCEL_H__
#define __DEV_ACCEL_H__

/* Includes ------------------------------------------------------------------*/
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
#include "mma7455l.h"
#endif

/* Exported types ------------------------------------------------------------*/
struct efm32_accel_result_t
{
    rt_int32_t              x;
    rt_int32_t              y;
    rt_int32_t              z;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/*  MMA7361LC
    g-Select    g-Range     Sensitivity
    0           1.5 g       800 mV/g
    1           6 g         206 mV/g

    MMA7455L
    g-Select    g-Range     Sensitivity
    0           2 g         64 LSB/g
    1           4 g         32 LSB/g
    2           8 g         16 LSB/g
*/
#define ACCEL_G_SELECT          (0)

#define ACCEL_CAL_SAMPLES       (4)     /* Must be multiple of 2 */
#define ACCEL_CAL_ROUND         (50)
#define ACCEL_CAL_SIMPLE        (0)
#define ACCEL_CAL_INTERACT      (1)

#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
/* Reading_at_1g = Sensitivity * Max_reading / Refference_voltage */
#define ACCEL_CAL_1G_VALUE      {993, 256}

#define ACCEL_X_ADC_CH          ADC_SCANCTRL_INPUTMASK_CH2
#define ACCEL_Y_ADC_CH          ADC_SCANCTRL_INPUTMASK_CH3
#define ACCEL_Z_ADC_CH          ADC_SCANCTRL_INPUTMASK_CH4
#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
#define ACCEL_CAL_1G_VALUE      {0x3f, 0x1f, 0x0f}
#define ACCEL_IIC_SLAVE_ADDRESS (0x1d)

#define ACCEL_INT1_PORT         (gpioPortD)
#define ACCEL_INT1_PIN          (13)
#define ACCEL_INT2_PORT         (gpioPortD)
#define ACCEL_INT2_PIN          (12)

#define ACCEL_MODE_STANDBY      (1 << 0)
#define ACCEL_MODE_MEASUREMENT  (1 << 1)
#define ACCEL_MODE_LEVEL        (1 << 2)
#define ACCEL_MODE_PULSE        (1 << 3)
#define ACCEL_RANGE_8G          (1 << 4)
#define ACCEL_RANGE_4G          (1 << 5)
#define ACCEL_RANGE_2G          (1 << 6)
#define ACCEL_INTPIN_INVERSE    (1 << 7)
#define ACCEL_INT_LEVEL_PULSE   (1 << 8)
#define ACCEL_INT_PULSE_LEVEL   (1 << 9)
#define ACCEL_INT_SINGLE_DOUBLE (1 << 10)
#define ACCEL_DISABLE_X         (1 << 11)
#define ACCEL_DISABLE_Y         (1 << 12)
#define ACCEL_DISABLE_Z         (1 << 13)
#define ACCEL_THRESHOLD_INTEGER (1 << 14)   /* For level detection only */
#define ACCEL_BANDWIDTH_125HZ   (1 << 15)
#define ACCEL_LEVEL_AND         (1 << 16)
#define ACCEL_PULSE_AND         (1 << 17)
#define ACCEL_DRIVE_STRONG      (1 << 18)
#define ACCEL_SOURCE_LEVEL_X    (1 << 19)
#define ACCEL_SOURCE_LEVEL_Y    (1 << 20)
#define ACCEL_SOURCE_LEVEL_Z    (1 << 21)
#define ACCEL_SOURCE_PULSE_X    (1 << 22)
#define ACCEL_SOURCE_PULSE_Y    (1 << 23)
#define ACCEL_SOURCE_PULSE_Z    (1 << 24)

#define ACCEL_SHIFT_MODE        (0)
#define ACCEL_SHIFT_RANGE       (4)
#define ACCEL_SHIFT_INT         (8)
#define ACCEL_SHIFT_DISABLE     (11)
#define ACCEL_SHIFT_SOURCE      (19)

#define ACCEL_MASK_MODE         (0X0000000f << ACCEL_SHIFT_MODE)
#define ACCEL_MASK_RANGE        (0X00000007 << ACCEL_SHIFT_RANGE)
#define ACCEL_MASK_INT          (0X00000007 << ACCEL_SHIFT_INT)
#define ACCEL_MASK_DISABLE      (0X00000007 << ACCEL_SHIFT_DISABLE)
#define ACCEL_MASK_SOURCE       (0X0000003f << ACCEL_SHIFT_SOURCE)
#endif

/* Exported functions ------------------------------------------------------- */
rt_err_t efm_accel_get_data(struct efm32_accel_result_t *data,
    rt_bool_t lowResolution);
rt_err_t efm_accel_config(rt_uint32_t config,
    rt_uint8_t level_threshold,
    rt_uint8_t pulse_threshold,
    rt_uint8_t pulse_duration,
    rt_uint8_t pulse_latency,
    rt_uint8_t pulse_duration2);
rt_err_t efm_accel_auto_zero(rt_uint8_t mode, rt_tick_t period);
rt_err_t efm_accel_init(void);

#endif /*__DEV_ACCEL_H__ */
