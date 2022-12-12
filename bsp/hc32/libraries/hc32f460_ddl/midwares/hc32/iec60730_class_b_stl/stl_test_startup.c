/**
 *******************************************************************************
 * @file  stl_test_startup.c
 * @brief This file provides firmware functions to manage the startup test.
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
#include "stl_common.h"
#include "stl_conf.h"
#include "stl_utility.h"
#include "stl_test_startup.h"

/**
 * @addtogroup STL_IEC60730
 * @{
 */

/**
 * @defgroup STL_IEC60730_Startup STL IEC60730 Startup
 * @brief IEC60730 startup test
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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_Startup_Global_Macros STL IEC60730 Startup Global Macros
 * @{
 */

/**
 * @brief  Power on self-test.
 * @param  None
 * @retval None
 */
STL_WEAK void STL_StartupTest(void)
{
    /* please implement this function. */
    for (;;) {
    }
}

/**
 * @brief  Power on self-test.
 * @param  [in] pstcCaseTable       Test case table
 * @param  [in] u32TableSize        Test case size
 * @retval None
 */
void STL_StartupTestCase(const stc_stl_case_startup_t *pstcCaseTable, uint32_t u32TableSize)
{
    uint32_t i;

    if ((pstcCaseTable != NULL) && (u32TableSize != 0UL)) {
        for (i = 0UL; i < u32TableSize; i++) {
            if (pstcCaseTable[i].pfnTest != NULL) {
                if (pstcCaseTable[i].pfnTest() != STL_OK) {
                    STL_Printf("%s test fail in startup\r\n", pstcCaseTable[i].pcCaseName);

                    if (pstcCaseTable[i].pfnFailHandler != NULL) {
                        pstcCaseTable[i].pfnFailHandler();
                    }
                }
            }
        }
    }
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
