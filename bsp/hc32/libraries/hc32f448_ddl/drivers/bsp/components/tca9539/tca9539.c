/**
 *******************************************************************************
 * @file  tca9539.c
 * @brief This file provides firmware functions for IO expand IC TCA9539.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-12-15       CDT             Add null pointer check
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "tca9539.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @defgroup TCA9539 IO Expand IC TCA9539
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
 * @defgroup TCA9539_Global_Functions TCA9539 Global Functions
 * @{
 */

/**
 * @brief  Initialize TCA9539.
 * @param  [in] pstcTca9539LL           Pointer to a @ref stc_tca9539_ll_t structure.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t TCA9539_Init(const stc_tca9539_ll_t *pstcTca9539LL)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8TempData[2];

    if ((pstcTca9539LL == NULL) || (pstcTca9539LL->Reset == NULL) || (pstcTca9539LL->Init == NULL) ||
        (pstcTca9539LL->Write == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcTca9539LL->Reset();
        pstcTca9539LL->Init();
        /* All Pins are input as default */
        u8TempData[1] = 0xFFU;
        u8TempData[0] = TCA9539_REG_CONFIG_PORT0;
        pstcTca9539LL->Write(&u8TempData[0], &u8TempData[1], 1U);
        u8TempData[0] = TCA9539_REG_CONFIG_PORT1;
        pstcTca9539LL->Write(&u8TempData[0], &u8TempData[1], 1U);
    }

    return i32Ret;
}

/**
 * @brief  Initialize TCA9539 interrupt.
 * @param  [in] pstcTca9539LL           Pointer to a @ref stc_tca9539_ll_t structure.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t TCA9539_IntInit(const stc_tca9539_ll_t *pstcTca9539LL)
{
    int32_t i32Ret = LL_OK;

    if ((pstcTca9539LL == NULL) || (pstcTca9539LL->IntInit == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcTca9539LL->IntInit();
    }

    return i32Ret;
}

/**
 * @brief  Reset TCA9539.
 * @param  [in] pstcTca9539LL           Pointer to a @ref stc_tca9539_ll_t structure.
 * @retval int32_t:
 *           - LL_OK: Reset success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t TCA9539_Reset(const stc_tca9539_ll_t *pstcTca9539LL)
{
    int32_t i32Ret = LL_OK;

    if ((pstcTca9539LL == NULL) || (pstcTca9539LL->Reset == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcTca9539LL->Reset();
    }

    return i32Ret;
}

/**
 * @brief  Write TCA9539 pin output value.
 * @param  [in] pstcTca9539LL           Pointer to a @ref stc_tca9539_ll_t structure.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PORT0
 *           @arg TCA9539_IO_PORT1
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PIN0
 *           @arg TCA9539_IO_PIN1
 *           @arg TCA9539_IO_PIN2
 *           @arg TCA9539_IO_PIN3
 *           @arg TCA9539_IO_PIN4
 *           @arg TCA9539_IO_PIN5
 *           @arg TCA9539_IO_PIN6
 *           @arg TCA9539_IO_PIN7
 *           @arg TCA9539_IO_PIN_ALL:   All of the above
 * @param  [in] u8PinState              Pin state to be written.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_PIN_RESET
 *           @arg TCA9539_PIN_SET
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t TCA9539_WritePin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8TempData[2];

    if ((pstcTca9539LL == NULL) || (pstcTca9539LL->Read == NULL) || (pstcTca9539LL->Write == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        u8TempData[0] = u8Port + TCA9539_REG_OUTPUT_PORT0;
        pstcTca9539LL->Read(&u8TempData[0], &u8TempData[1], 1U);
        if (0U == u8PinState) {
            u8TempData[1] &= (uint8_t)(~u8Pin);
        } else {
            u8TempData[1] |= u8Pin;
        }
        pstcTca9539LL->Write(&u8TempData[0], &u8TempData[1], 1U);
    }

    return i32Ret;
}

/**
 * @brief  Read TCA9539 pin input value.
 * @param  [in] pstcTca9539LL           Pointer to a @ref stc_tca9539_ll_t structure.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PORT0
 *           @arg TCA9539_IO_PORT1
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PIN0
 *           @arg TCA9539_IO_PIN1
 *           @arg TCA9539_IO_PIN2
 *           @arg TCA9539_IO_PIN3
 *           @arg TCA9539_IO_PIN4
 *           @arg TCA9539_IO_PIN5
 *           @arg TCA9539_IO_PIN6
 *           @arg TCA9539_IO_PIN7
 *           @arg TCA9539_IO_PIN_ALL:   All of the above
 * @param  [out] pu8PinState            Pin state to be read.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_PIN_RESET
 *           @arg TCA9539_PIN_SET
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t TCA9539_ReadPin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin, uint8_t *pu8PinState)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8TempData[2];

    if ((pstcTca9539LL == NULL) || (pstcTca9539LL->Read == NULL) || (pu8PinState == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        u8TempData[0] = u8Port + TCA9539_REG_INPUT_PORT0;
        pstcTca9539LL->Read(&u8TempData[0], &u8TempData[1], 1U);
        if (0U != (u8TempData[1] & u8Pin)) {
            *pu8PinState = TCA9539_PIN_SET;
        } else {
            *pu8PinState = TCA9539_PIN_RESET;
        }
    }

    return i32Ret;
}

/**
 * @brief  Toggle TCA9539 pin output value.
 * @param  [in] pstcTca9539LL           Pointer to a @ref stc_tca9539_ll_t structure.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PORT0
 *           @arg TCA9539_IO_PORT1
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PIN0
 *           @arg TCA9539_IO_PIN1
 *           @arg TCA9539_IO_PIN2
 *           @arg TCA9539_IO_PIN3
 *           @arg TCA9539_IO_PIN4
 *           @arg TCA9539_IO_PIN5
 *           @arg TCA9539_IO_PIN6
 *           @arg TCA9539_IO_PIN7
 *           @arg TCA9539_IO_PIN_ALL:   All of the above
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t TCA9539_TogglePin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8TempData[2];

    if ((pstcTca9539LL == NULL) || (pstcTca9539LL->Read == NULL) || (pstcTca9539LL->Write == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        u8TempData[0] = u8Port + TCA9539_REG_OUTPUT_PORT0;
        pstcTca9539LL->Read(&u8TempData[0], &u8TempData[1], 1U);
        u8TempData[1] ^= u8Pin;
        pstcTca9539LL->Write(&u8TempData[0], &u8TempData[1], 1U);
    }

    return i32Ret;
}

/**
 * @brief  Configuration TCA9539 pin.
 * @param  [in] pstcTca9539LL           Pointer to a @ref stc_tca9539_ll_t structure.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PORT0
 *           @arg TCA9539_IO_PORT1
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_IO_PIN0
 *           @arg TCA9539_IO_PIN1
 *           @arg TCA9539_IO_PIN2
 *           @arg TCA9539_IO_PIN3
 *           @arg TCA9539_IO_PIN4
 *           @arg TCA9539_IO_PIN5
 *           @arg TCA9539_IO_PIN6
 *           @arg TCA9539_IO_PIN7
 *           @arg TCA9539_IO_PIN_ALL:   All of the above
 * @param  [in] u8Dir                   Pin output direction.
 *         This parameter can be one of the following values:
 *           @arg TCA9539_DIR_OUT
 *           @arg TCA9539_DIR_IN
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t TCA9539_ConfigPin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8TempData[2];

    if ((pstcTca9539LL == NULL) || (pstcTca9539LL->Read == NULL) || (pstcTca9539LL->Write == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        u8TempData[0] = u8Port + TCA9539_REG_CONFIG_PORT0;
        pstcTca9539LL->Read(&u8TempData[0], &u8TempData[1], 1U);
        if (TCA9539_DIR_OUT == u8Dir) {
            u8TempData[1] &= (uint8_t)(~u8Pin);
        } else {
            u8TempData[1] |= u8Pin;
        }
        pstcTca9539LL->Write(&u8TempData[0], &u8TempData[1], 1U);
    }

    return i32Ret;
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


/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
