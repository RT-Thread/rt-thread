/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-3-4        CHChen           First version
*
******************************************************************************/

#ifndef __DRV_TRNG_H__
#define __DRV_TRNG_H__

rt_err_t nu_trng_init(void);
void nu_trng_open(void);
rt_uint32_t nu_trng_rand(struct hwcrypto_rng *ctx);

#endif
