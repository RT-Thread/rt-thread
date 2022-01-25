/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-28 22:15:48
 * @LastEditTime: 2021-04-28 22:15:48
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_math.h"

u32 Ft_Abs(s32 num)
{
    return (num >= 0 ? num : -num);
}
