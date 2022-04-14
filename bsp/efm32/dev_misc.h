/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-02-22   onelife     Initial creation for EFM32
 */

#ifndef __DEV_MISC_H__
#define __DEV_MISC_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
rt_err_t rt_hw_misc_init(void);
rt_int32_t rt_hw_get_temp(void);
rt_uint32_t rt_hw_get_vdd(void);

#endif /* __DEV_MISC_H__ */
