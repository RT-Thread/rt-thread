/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-11-11      Wayne            First version
*
******************************************************************************/

#ifndef __DRV_SLCD_H__
#define __DRV_SLCD_H__

#include <rtdevice.h>
#include "NuMicro.h"

struct nu_slcd_pixel
{
    uint32_t m_u32Com;
    uint32_t m_u32Seg;
    uint32_t m_u32OnFlag;
};
typedef struct nu_slcd_pixel *nu_slcd_pixel_t;

typedef enum
{
    NU_SLCD_CMD_SET_LCD_CFG,       /* SLCD configuration */
    NU_SLCD_CMD_SET_CP_VOLTAGE,    /* Internal charge pump voltage */
    NU_SLCD_CMD_CNT
} NU_SLCD_CMD;

#endif /* __DRV_SLCD_H__ */
