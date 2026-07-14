/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_EQEI_H__
#define __DRV_EQEI_H__
#include "rtthread.h"
#include "rtdevice.h"

rt_int32_t nu_eqei_get_maxval(rt_device_t pulse_encoder);
rt_int32_t nu_eqei_get_cmpval(rt_device_t pulse_encoder);
rt_int32_t nu_eqei_get_type(rt_device_t pulse_encoder);
void nu_eqei_set_maxval_type(rt_device_t pulse_encoder, rt_uint32_t u32val, enum rt_pulse_encoder_type eType);
void nu_eqei_set_cmpval(rt_device_t pulse_encoder, rt_uint32_t u32val);

#endif /* __DRV_EQEI_H__ */