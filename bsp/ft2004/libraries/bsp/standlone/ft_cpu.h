/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-20 11:33:54
 * @LastEditTime: 2021-04-20 11:33:55
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef FT_CPU_H
#define FT_CPU_H

#include "ft_types.h"
#include "ft_error_code.h"
extern const u32 SoftAffiTable[4];
s32 FCpu_IdGet(void);
void FCpu_SpinLockInit(void);
void FCpu_SpinLock(void);
void FCpu_SpinUnlock(void);
s32 FCpu_AffinityGet(void);

#endif // !FT_SPIN_H
