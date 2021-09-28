/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-21 10:43:59
 * @LastEditTime: 2021-04-21 10:44:00
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef FT_PSCI_H
#define FT_PSCI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"

    void FPsci_CpuOn(s32 CpuIdMask, u32 BootAddr);
    void FPsci_Reset(void);

#ifdef __cplusplus
}
#endif

#endif // !
