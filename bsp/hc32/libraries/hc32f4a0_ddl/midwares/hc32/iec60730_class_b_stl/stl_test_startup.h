/**
 *******************************************************************************
 * @file  stl_test_startup.h
 * @brief This file contains all the functions prototypes of startup test.
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

#ifndef __STL_TEST_STARTUP_H__
#define __STL_TEST_STARTUP_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "stl_common.h"
#include "stl_conf.h"

/**
 * @addtogroup STL_IEC60730
 * @{
 */

/**
 * @addtogroup STL_IEC60730_Startup
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_Runtime_Global_Type STL IEC60730 Runtime Global Type
 * @{
 */
typedef struct stc_stl_case_startup {
    const char *pcCaseName;
    uint32_t (*pfnTest)(void);

    void (*pfnFailHandler)(void);
} stc_stl_case_startup_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_Startup_Case STL IEC60730 Startup Case
 * @{
 */
#define STL_STARTUP_CASE(CaseName, pfnTest, pfnFailHandler)                    \
    { #CaseName, pfnTest, pfnFailHandler }
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup STL_IEC60730_Startup_Global_Functions
 * @{
 */
void STL_StartupTest(void);
void STL_StartupTestCase(const stc_stl_case_startup_t *pstcCaseTable, uint32_t u32TableSize);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STL_TEST_STARTUP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
