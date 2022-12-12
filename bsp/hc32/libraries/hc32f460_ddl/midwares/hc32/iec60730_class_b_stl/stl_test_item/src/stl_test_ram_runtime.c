/**
 *******************************************************************************
 * @file  stl_test_ram_runtime.c
 * @brief This file provides firmware functions to manage the RAM test.
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
#include "stl_test_ram.h"

/**
 * @addtogroup STL_IEC60730
 * @{
 */

/**
 * @defgroup STL_IEC60730_RAM_Runtime STL IEC60730 RAM Runtime
 * @brief IEC60730 RAM runtime test
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup STL_IEC60730_RAM_Local_Variables STL IEC60730 RAM Local Variables
 * @{
 */
STL_USED uint32_t  m_au32MarchRAM[STL_MARCH_RAM_WORDS] STL_SECTION(".march_ram");
STL_USED uint32_t  m_au32MarchRAMBuf[STL_MARCH_RAM_BUF_WORDS] STL_SECTION(".march_ram_buf");
STL_USED uint32_t *m_pu32MarchRAM STL_SECTION(".march_ram_pointer");
STL_USED uint32_t  m_au32StackBoundary[STL_STACK_BOUNDARY_WORDS] STL_SECTION(".stack_boundary");
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_RAM_Global_Functions STL IEC60730 RAM Global Functions
 * @{
 */

/**
 * @brief  Stack test initialize in runtime.
 * @param  None
 * @retval uint32_t:
 *           - STL_OK:          Initialization pass.
 */
uint32_t STL_StackRuntimeInit(void)
{
    m_au32StackBoundary[0] = 0x5A5A5A5AUL;
    m_au32StackBoundary[1] = 0xA5A5A5A5UL;
    m_au32StackBoundary[2] = 0xAAAAAAAAUL;
    m_au32StackBoundary[3] = 0x55555555UL;
    return STL_OK;
}

/**
 * @brief  Stack test in runtime.
 * @param  None
 * @retval uint32_t:
 *           - STL_OK:          Test pass.
 *           - STL_ERR:         Stack boundary value error.
 */
uint32_t STL_StackRuntimeTest(void)
{
    if ((m_au32StackBoundary[0] != 0x5A5A5A5AUL) || \
            (m_au32StackBoundary[1] != 0xA5A5A5A5UL) || \
            (m_au32StackBoundary[2] != 0xAAAAAAAAUL) || \
            (m_au32StackBoundary[3] != 0x55555555UL)) {
        return STL_ERR;
    }

    return STL_OK;
}

/**
 * @brief  RAM test initialize in runtime.
 * @param  None
 * @retval uint32_t:
 *           - STL_OK:          Initialization pass.
 */
uint32_t STL_RamRuntimeInit(void)
{
    m_pu32MarchRAM = (uint32_t *)STL_MARCH_RAM_START;
    return STL_OK;
}

/**
 * @brief  RAM test in runtime.
 * @param  None
 * @retval uint32_t:
 *           - STL_OK:          Test pass.
 *           - STL_ERR:         Test fail.
 */
uint32_t STL_RamRuntimeTest(void)
{
    uint32_t i;        /* Index for RAM physical addressing */
    uint32_t u32Ret = STL_OK;

    if (m_pu32MarchRAM >= (uint32_t *)STL_MARCH_RAM_END) {
        /*------------- March C- to the RAM Buffer itself --------------- */
        m_pu32MarchRAM = &m_au32MarchRAMBuf[0];

        /*---------------------------- STEP 1 --------------------------------- */
        /* Write background with addresses increasing */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            *(m_pu32MarchRAM + i) = STL_MARCH_RAM_BCKGRND;
        }

        /*---------------------------- STEP 2 --------------------------------- */
        /* Verify background and write inverted background addresses increasing */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            if (*(m_pu32MarchRAM + i) != STL_MARCH_RAM_BCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i) = STL_MARCH_RAM_INVBCKGRND;
        }

        /*---------------------------- STEP 3 --------------------------------- */
        /* Verify inverted background and write background addresses increasing */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            if (*(m_pu32MarchRAM + i) != STL_MARCH_RAM_INVBCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i) = STL_MARCH_RAM_BCKGRND;
        }

        /*---------------------------- STEP 4 --------------------------------- */
        /* Verify background and write inverted background addresses decreasing */
        for (i = STL_MARCH_RAM_BUF_WORDS; i > 0UL ; --i) {
            if (*(m_pu32MarchRAM + i - 1UL) != STL_MARCH_RAM_BCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i - 1UL) = STL_MARCH_RAM_INVBCKGRND;
        }

        /*---------------------------- STEP 5 --------------------------------- */
        /* Verify inverted background and write background addresses decreasing */
        for (i = STL_MARCH_RAM_BUF_WORDS; i > 0UL ; --i) {
            if (*(m_pu32MarchRAM + i - 1UL) != STL_MARCH_RAM_INVBCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i - 1UL) = STL_MARCH_RAM_BCKGRND;
        }

        /*---------------------------- STEP 6 --------------------------------- */
        /* Verify background with addresses increasing */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            if (*(m_pu32MarchRAM + i) != STL_MARCH_RAM_BCKGRND) {
                u32Ret = STL_ERR;
            }
        }

        /* Prepare next Tranparent RAM test from the beginning of Class A area */
        m_pu32MarchRAM = (uint32_t *)STL_MARCH_RAM_START;
    } else {
        /*---------------------------- STEP 1 --------------------------------- */
        /* Save the content of the 6 words to be tested and start MarchC -
           Write background with addresses increasing */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            m_au32MarchRAMBuf[i] = *(m_pu32MarchRAM + i);
            *(m_pu32MarchRAM + i) = STL_MARCH_RAM_BCKGRND;
        }

        /*---------------------------- STEP 2 --------------------------------- */
        /* Verify background and write inverted background addresses increasing */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            if (*(m_pu32MarchRAM + i) != STL_MARCH_RAM_BCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i) = STL_MARCH_RAM_INVBCKGRND;
        }

        /*---------------------------- STEP 3 --------------------------------- */
        /* Verify inverted background and write background addresses increasing */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            if (*(m_pu32MarchRAM + i) != STL_MARCH_RAM_INVBCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i) = STL_MARCH_RAM_BCKGRND;
        }

        /*---------------------------- STEP 4 --------------------------------- */
        /* Verify background and write inverted background addresses decreasing */
        for (i = STL_MARCH_RAM_BUF_WORDS; i > 0UL; --i) {
            if (*(m_pu32MarchRAM + i - 1UL) != STL_MARCH_RAM_BCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i - 1UL) = STL_MARCH_RAM_INVBCKGRND;
        }

        /*---------------------------- STEP 5 --------------------------------- */
        /* Verify inverted background and write background addresses decreasing */
        for (i = STL_MARCH_RAM_BUF_WORDS; i > 0UL; --i) {
            if (*(m_pu32MarchRAM + i - 1UL) != STL_MARCH_RAM_INVBCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i - 1UL) = STL_MARCH_RAM_BCKGRND;
        }

        /*---------------------------- STEP 6 --------------------------------- */
        /* Verify background with addresses increasing */
        /* and restore the content of the 6 tested words */
        for (i = 0UL; i < STL_MARCH_RAM_BUF_WORDS; ++i) {
            if (*(m_pu32MarchRAM + i) != STL_MARCH_RAM_BCKGRND) {
                u32Ret = STL_ERR;
            }
            *(m_pu32MarchRAM + i) = m_au32MarchRAMBuf[i];
        }

        /* Prepare next Row Tranparent RAM test */
        m_pu32MarchRAM += STL_MARCH_RAM_BUF_WORDS;
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
