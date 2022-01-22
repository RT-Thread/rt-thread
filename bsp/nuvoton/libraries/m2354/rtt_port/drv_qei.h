/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-4-20       FYChou           First version
*
* Tips:
* QEI compare interrupt flag *(pulse_encoder->user_data): If compare value is
* not null, after execute device init, compare interrupt will be enabled automatic.
* When the interrupt occur, interrupt flag will be set 1.
*
******************************************************************************/

#ifndef __DRV_QEI_H__
#define __DRV_QEI_H__

#include <rtthread.h>

rt_int32_t nu_qei_get_maxval(rt_device_t *pulse_encoder);
rt_int32_t nu_qei_get_cmpval(rt_device_t *pulse_encoder);
rt_int32_t nu_qei_get_type(rt_device_t *pulse_encoder);
void nu_qei_set_maxval_type(rt_device_t *pulse_encoder, rt_uint32_t u32val, rt_uint8_t u8type);
void nu_qei_set_cmpval(rt_device_t *pulse_encoder, rt_uint32_t u32val);


#endif // __DRV_QEI_H___
