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

#ifndef __DRV_CRC_H__
#define __DRV_CRC_H__

rt_err_t nu_crc_init(void);

rt_uint32_t nu_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length);

#endif
