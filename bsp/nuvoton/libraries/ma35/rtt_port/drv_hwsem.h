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

#ifndef __DRV_HWSEM_H__
#define __DRV_HWSEM_H__

#include <rtdevice.h>

typedef enum
{
    evHWSEM0 = 0,
    evHWSEM1,
    evHWSEM2,
    evHWSEM3,
    evHWSEM4,
    evHWSEM5,
    evHWSEM6,
    evHWSEM7,
    evHWSEM_CNT,
} E_HWSEM_ID;

struct nu_mutex
{
    E_HWSEM_ID id;
};
typedef struct nu_mutex *nu_mutex_t;

nu_mutex_t nu_mutex_init(struct rt_device *device, E_HWSEM_ID id);
rt_err_t nu_mutex_take(nu_mutex_t mutex, rt_int32_t timeout);
rt_err_t nu_mutex_release(nu_mutex_t mutex);
void nu_mutex_deinit(struct rt_device *device, E_HWSEM_ID id);


#endif /* __DRV_HWSEM_H__ */
