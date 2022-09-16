/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2022-3-15       Wayne            First version
*
******************************************************************************/

#ifndef __DRV_TRNG_H__
#define __DRV_TRNG_H__

#include <rtdevice.h>

rt_err_t nu_trng_init(void);
rt_uint32_t nu_trng_rand(struct hwcrypto_rng *ctx);

#endif
