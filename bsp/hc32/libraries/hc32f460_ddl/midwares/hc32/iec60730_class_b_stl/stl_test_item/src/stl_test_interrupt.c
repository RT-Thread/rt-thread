/**
 *******************************************************************************
 * @file  stl_test_interrupt.c
 * @brief This file provides firmware functions to manage the interrupt test.
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
#include "stl_test_interrupt.h"

/**
 * @addtogroup STL_IEC60730
 * @{
 */

/**
 * @defgroup STL_IEC60730_Interrupt_Runtime STL IEC60730 Interrupt Runtime
 * @brief IEC60730 interrupt runtime test
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
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
static uint32_t m_u32TestParamTableSize;
static stc_stl_int_params_t *m_pstcTestParamTable;
/**
 * @}
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_Interrupt_Global_Functions STL IEC60730 Interrupt Global Functions
 * @{
 */

/**
 * @brief  Interrupt test table initialize in runtime.
 * @param  [in] pstcParamsTable     Test case table
 * @param  [in] u32TableSize        Test case size
 * @retval uint32_t:
 *           - STL_OK:              Initialize successfully.
 *           - STL_ERR:             Initialize unsuccessfully.
 */
uint32_t STL_IntRuntimeTableInit(stc_stl_int_params_t *pstcParamsTable, uint32_t u32TableSize)
{
    uint32_t i;
    uint32_t u32Ret = STL_ERR;

    if ((pstcParamsTable != NULL) && (u32TableSize != 0UL)) {
        for (i = 0UL; i < u32TableSize; i++) {
            pstcParamsTable[i].u32PrivateParam = 0UL;
        }

        m_pstcTestParamTable = pstcParamsTable;
        m_u32TestParamTableSize = u32TableSize;
        u32Ret = STL_OK;
    }

    return u32Ret;
}

/**
 * @brief  Interrupt test initialize in runtime.
 * @param  [in] pstcParamsTable     Test case table
 * @param  [in] u32TableSize        Test case size
 * @retval uint32_t:
 *           - STL_OK:              Test pass.
 *           - STL_ERR:             Test error.
 */
uint32_t STL_IntRuntimeTest(void)
{
    uint32_t i;
    uint32_t u32Ret = STL_OK;
    stc_stl_int_params_t *pstcTestParam;
    static uint32_t u32SystickCount;

    if (++u32SystickCount == STL_SYSTICK_TICK_FREQ) {
        for (i = 0UL; i < m_u32TestParamTableSize; i++) {
            pstcTestParam = &m_pstcTestParamTable[i];

            if ((pstcTestParam->u32PrivateParam < pstcTestParam->u32FreqLowerVal) || \
                    (pstcTestParam->u32PrivateParam > pstcTestParam->u32FreqUpperVal)) {
                u32Ret = STL_ERR;
            }
            pstcTestParam->u32PrivateParam = 0UL;
        }
        u32SystickCount = 0UL;
    }

    return u32Ret;
}

/**
 * @brief  Update interrupt count in runtime.
 * @param  [in] u8Num               Params index
 * @param  [in] u32TableSize        Test case size
 * @retval uint32_t:
 *           - STL_OK:              Test pass.
 *           - STL_ERR:             Test error.
 */
void STL_IntUpdateCount(uint8_t u8ParamIndex)
{
    stc_stl_int_params_t *pstcTestParam;

    if (u8ParamIndex < m_u32TestParamTableSize) {
        pstcTestParam = &m_pstcTestParamTable[u8ParamIndex];
        pstcTestParam->u32PrivateParam++;
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
 ******************************************************************************/
