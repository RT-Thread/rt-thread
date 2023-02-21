/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-10-21      Wayne        First version
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

rt_int32_t nu_qei_get_maxval(struct rt_pulse_encoder_device *pulse_encoder);
rt_int32_t nu_qei_get_cmpval(struct rt_pulse_encoder_device *pulse_encoder);
rt_int32_t nu_qei_get_type(struct rt_pulse_encoder_device *pulse_encoder);
void nu_qei_set_maxval_type(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t u32val, enum rt_pulse_encoder_type eType);
void nu_qei_set_cmpval(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t u32val);

#endif // __DRV_QEI_H___
