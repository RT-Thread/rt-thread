/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#ifndef __ACODEC_NAU8822_H__
#define __ACODEC_NAU8822_H__

#include <rtdevice.h>

typedef struct
{
    char      *i2c_bus_name;

    char      *i2s_bus_name;

    rt_int32_t pin_phonejack_en;

    rt_int32_t pin_phonejack_det;

} S_NU_NAU8822_CONFIG;

int nu_hw_nau8822_init(S_NU_NAU8822_CONFIG *psCodecConfig);

#endif /* __ACODEC_NAU8822_H__ */
