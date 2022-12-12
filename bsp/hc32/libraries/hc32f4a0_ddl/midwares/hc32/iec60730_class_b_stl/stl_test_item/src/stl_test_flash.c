/**
 *******************************************************************************
 * @file  stl_test_flash.c
 * @brief This file provides firmware functions to manage the flash test.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "stl_conf.h"
#include "stl_utility.h"
#include "stl_sw_crc32.h"
#include "stl_test_flash.h"

/**
 * @addtogroup STL_IEC60730
 * @{
 */

/**
 * @defgroup STL_IEC60730_Flash STL IEC60730 Flash
 * @brief IEC60730 flash test
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CC_BULID_CRC32_VALUE    (*(volatile uint32_t *)(&STL_ROM_CRC32_CC_CHECKSUM))

#if defined (__CC_ARM)                  /* keil Compiler */
#define STL_CRC32_XOR_VALUE     (0xFFFFFFFFUL)
#elif defined (__IAR_SYSTEMS_ICC__)     /* IAR Compiler */
#define STL_CRC32_XOR_VALUE     (0x00000000UL)
#endif

#define SW_CRC32_VALUE_XOR(x)   ((x) ^ STL_CRC32_XOR_VALUE)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @defgroup STL_IEC60730_Flash_Local_Variables STL IEC60730 Flash Local Variables
 * @{
 */
STL_USED const uint32_t __checksum STL_SECTION(".checksum") = 0UL;
/**
 * @}
 */

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_Flash_Global_Functions STL IEC60730 Flash Global Functions
 * @{
 */

/**
 * @brief  Flash test in startup.
 * @param  None
 * @retval uint32_t:
 *           - STL_OK:          Test pass.
 *           - STL_ERR:         Flash CRC value error.
 */
uint32_t STL_FlashStartupTest(void)
{
    uint32_t u32CalcCrc32Value;
    uint32_t u32Ret = STL_ERR;

    u32CalcCrc32Value = STL_CalculateCRC32Value(STL_CRC32_INIT_VALUE, (uint8_t *)STL_ROM_CRC32_START, STL_ROM_CRC32_SIZE);
    u32CalcCrc32Value = SW_CRC32_VALUE_XOR(u32CalcCrc32Value);
    if (CC_BULID_CRC32_VALUE == u32CalcCrc32Value) {
        u32Ret = STL_OK;
    }

    return u32Ret;
}

/**
 * @brief  Flash test in runtime.
 * @param  None
 * @retval uint32_t:
 *           - STL_OK:          Test pass.
 *           - STL_OK:          Flash CRC32 value error.
 */
uint32_t STL_FlashRuntimeTest(void)
{
    uint32_t u32Ret = STL_OK;
    const uint32_t u32CheckEndAddr = STL_ROM_CRC32_END + 4UL - STL_ROM_CRC32_BLOCK_SIZE;
    static uint32_t u32CalcLen;
    static uint32_t u32CheckAddr = STL_ROM_CRC32_START;
    static uint32_t u32CalcCrc32Value = STL_CRC32_INIT_VALUE;

    if (u32CheckAddr < STL_ROM_CRC32_END) {
        if (u32CheckAddr == STL_ROM_CRC32_START) {
            u32CalcCrc32Value = STL_CRC32_INIT_VALUE;   /* Update CRC32 init value */
        }

        if (u32CheckAddr < u32CheckEndAddr) {
            u32CalcLen = STL_ROM_CRC32_BLOCK_SIZE;
        } else {
            u32CalcLen = STL_ROM_CRC32_END - u32CheckAddr + 1UL;
        }
        u32CalcCrc32Value = STL_CalculateCRC32Value(u32CalcCrc32Value, (uint8_t *)u32CheckAddr, u32CalcLen);

        u32CheckAddr += u32CalcLen;       /* Update address */
    } else {
        u32CheckAddr = STL_ROM_CRC32_START;             /* Update address */
        u32CalcCrc32Value = SW_CRC32_VALUE_XOR(u32CalcCrc32Value);
        if (CC_BULID_CRC32_VALUE == u32CalcCrc32Value) {
            STL_Printf("********    CRC32 verify ok in runtime    ********\r\n");
        } else {
            STL_Printf("********   CRC32 verify error in runtime   ********\r\n");
            STL_Printf("* Calc_CRC32= 0x%x:CC Build_CRC32= 0x%x *\r\n", u32CalcCrc32Value, CC_BULID_CRC32_VALUE);
            u32Ret = STL_ERR;
        }
    }

    return u32Ret;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
