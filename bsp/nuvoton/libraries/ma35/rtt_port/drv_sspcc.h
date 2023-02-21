/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-10-20      Wayne        First version
*
******************************************************************************/

#ifndef __DRV_SSPCC_H__
#define __DRV_SSPCC_H__

#include "rtthread.h"

#define SSPCC_SET_REALM(IP, REALM) \
        do { \
            rt_kprintf("Set %s realm to %s(%d)\n", #IP, #REALM, REALM); \
            SSPCC_SetRealm(IP, REALM); \
            rt_kprintf("Get %s realm is %d ....%s\n", #IP, SSPCC_GetRealm(IP), (SSPCC_GetRealm(IP)==REALM)?"Success":"Failure"); \
        } while(0)

#define SSPCC_SET_GPIO_REALM(PORT, PIN, REALM) \
        do { \
            rt_kprintf("Set %s%s realm to %s(%d)\n", #PORT, #PIN, #REALM, REALM); \
            SSPCC_SetRealm_GPIO((uint32_t)PORT, PIN, REALM); \
            rt_kprintf("Get %s%s realm is %d ....%s\n", #PORT, #PIN, SSPCC_GetRealm_GPIO((uint32_t)PORT, PIN), (SSPCC_GetRealm_GPIO((uint32_t)PORT, PIN)==REALM)?"Success":"Failure"); \
        } while(0)

rt_err_t nu_sspcc_init(void);

#endif /* __DRV_SSPCC_H__ */
