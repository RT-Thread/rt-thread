/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-10-5       Wayne        First version
*
******************************************************************************/

#ifndef __DRV_WHC_H__
#define __DRV_WHC_H__

#include "drv_common.h"

typedef struct
{
    uint32_t content[WHC_BUFFER_LEN];
} nu_whc_msg;
typedef nu_whc_msg *nu_whc_msg_t;

#endif /* __DRV_WHC_H__ */
