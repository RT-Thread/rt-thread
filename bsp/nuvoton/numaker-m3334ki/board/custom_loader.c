/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2024-3-26       Wayne        First version
*
******************************************************************************/

#include "rtconfig.h"

#if defined(BSP_USING_CUSTOM_LOADER)

#include "NuMicro.h"

#ifndef __CUSTOM_LOADER_INFO_ATTRIBUTE
#define __CUSTOM_LOADER_INFO_ATTRIBUTE  __attribute__((used, section("CLINFO")))
#endif

/* Use an unsigned integer number as version number. */
#define DEF_FW_VER_NUM     0x20240328

typedef struct
{
#define DEF_MAGIC_NUM      0xA5A5A5A5
    uint32_t m_u32MagicNum1;
    uint32_t m_u32FwVer;
    uint32_t m_u32Reserved;
    uint32_t m_u32MagicNum2;
} customer_loader_info;

static const customer_loader_info s_CLInfo __CUSTOM_LOADER_INFO_ATTRIBUTE =
{
    .m_u32MagicNum1 = DEF_MAGIC_NUM,
    .m_u32FwVer     = DEF_FW_VER_NUM,
    .m_u32Reserved  = sizeof(customer_loader_info),
    .m_u32MagicNum2 = ~DEF_MAGIC_NUM,
};

static uint32_t custom_loader_swapbank(void)
{
    uint32_t u32CurBank, u32NextBank;

    u32CurBank = RMC_GET_ISP_BANK_SELECTION();
    u32NextBank = (~u32CurBank & 0x1);

    SYS_UnlockReg();
    RMC_ENABLE_ISP();

    RMC_RemapBank(u32NextBank);

    return RMC_GET_ISP_BANK_SELECTION();
}

uint32_t custom_loader_exec_last(void)
{
    uint32_t u32CurBankNo = 0;
    customer_loader_info *psInfoBank1 = (customer_loader_info *)((uint32_t)&s_CLInfo + RMC_APROM_BANK0_END);

    if ((psInfoBank1->m_u32MagicNum1 == s_CLInfo.m_u32MagicNum1) &&
            (psInfoBank1->m_u32MagicNum2 == s_CLInfo.m_u32MagicNum2) &&
            (psInfoBank1->m_u32FwVer > s_CLInfo.m_u32FwVer))
    {
        // Swap to Bank#1
        u32CurBankNo = custom_loader_swapbank();
    }
    /* else Stay bank#0 */

    return u32CurBankNo;
}

void *custom_loader_get_info(void)
{
    return (void *)&s_CLInfo;
}

#endif
