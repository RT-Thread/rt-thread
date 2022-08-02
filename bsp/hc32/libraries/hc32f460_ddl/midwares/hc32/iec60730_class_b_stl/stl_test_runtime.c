/**
 *******************************************************************************
 * @file  stl_test_runtime.c
 * @brief This file provides firmware functions to manage the runtime self-test.
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
#include "stl_test_runtime.h"
#include "stl_conf.h"
#include "stl_utility.h"

/**
 * @addtogroup STL_IEC60730
 * @{
 */

/**
 * @defgroup STL_IEC60730_Runtime STL IEC60730 Runtime
 * @brief IEC60730 runtime test
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
 * @defgroup STL_IEC60730_Runtime_Global_Macros STL IEC60730 Runtime Global Macros
 * @{
 */

/**
 * @brief  Self-test initialization in runtime.
 * @param  [in] pstcCaseTable       Test case table
 * @param  [in] u32TableSize        Test case size
 * @retval None
 */
void STL_RuntimeTestInit(const stc_stl_case_runtime_t *pstcCaseTable, uint32_t u32TableSize)
{
    uint32_t i;

#if (STL_PRINT_ENABLE == STL_ON)
    (void)STL_PrintfInit();   /* startup debug print */
#endif

    STL_Printf("********   Self-test runtime initialize   ********\r\n");

    if ((pstcCaseTable != NULL) && (u32TableSize != 0UL)) {
        for (i = 0UL; i < u32TableSize; i++) {
            if (pstcCaseTable[i].pfnInit != NULL) {
                if (pstcCaseTable[i].pfnInit() != STL_OK) {
                    STL_Printf("%s test initialization unsuccessfully in runtime\r\n", pstcCaseTable[i].pcCaseName);
                }
            }
        }
    }
}

/**
 * @brief  Self-test on runtime.
 * @param  [in] pstcCaseTable       Test case table
 * @param  [in] u32TableSize        Test case size
 * @retval None
 */
void STL_RuntimeTestCase(const stc_stl_case_runtime_t *pstcCaseTable, uint32_t u32TableSize)
{
    uint32_t i;

    if ((pstcCaseTable != NULL) && (u32TableSize != 0UL)) {
        for (i = 0UL; i < u32TableSize; i++) {
            if (pstcCaseTable[i].pfnTest != NULL) {
                if (pstcCaseTable[i].pfnTest() != STL_OK) {
                    STL_Printf("********   %s test fail in runtime  ********\r\n", pstcCaseTable[i].pcCaseName);

                    if (pstcCaseTable[i].pfnFailHandler != NULL) {
                        pstcCaseTable[i].pfnFailHandler();
                    }
                }
            }

            if (pstcCaseTable[i].pfnFeedDog != NULL) {
                pstcCaseTable[i].pfnFeedDog();
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
