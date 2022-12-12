/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-21 11:53:38
 * @LastEditTime: 2021-04-21 11:53:38
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef FT_SMC_H
#define FT_SMC_H

#include "ft_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        /* data */
        u32 FunctionIdentifier;
        u32 a1;
        u32 a2;
        u32 a3;
        u32 a4;
        u32 a5;
        u32 a6;

    } FSmc_Data_t;

    void FSmc_Call(FSmc_Data_t *Input, FSmc_Data_t *Output);

#ifdef __cplusplus
}
#endif

#endif // !FT_SMC_H
