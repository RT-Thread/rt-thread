/**
  ******************************************************************************
  * @file    bl602_l1c.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "bl602_l1c.h"
#include "bl602_common.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  L1C
 *  @{
 */

/** @defgroup  L1C_Private_Macros
 *  @{
 */

/*@} end of group L1C_Private_Macros */

/** @defgroup  L1C_Private_Types
 *  @{
 */

/*@} end of group L1C_Private_Types */

/** @defgroup  L1C_Private_Variables
 *  @{
 */
static intCallback_Type *l1cBmxErrIntCbfArra[L1C_BMX_ERR_INT_ALL] = { NULL };
static intCallback_Type *l1cBmxToIntCbfArra[L1C_BMX_TO_INT_ALL] = { NULL };

/*@} end of group L1C_Private_Variables */

/** @defgroup  L1C_Global_Variables
 *  @{
 */

/*@} end of group L1C_Global_Variables */

/** @defgroup  L1C_Private_Fun_Declaration
 *  @{
 */

/*@} end of group L1C_Private_Fun_Declaration */

/** @defgroup  L1C_Private_Functions
 *  @{
 */

/*@} end of group L1C_Private_Functions */

/** @defgroup  L1C_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  wrap set
 *
 * @param  wrap: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_Set_Wrap(BL_Fun_Type wrap)
{
    uint32_t tmpVal = 0;
    uint8_t cacheEn = 0;

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);
    cacheEn = BL_IS_REG_BIT_SET(L1C_BASE, L1C_CACHEABLE);

    if (cacheEn != 0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, L1C_CACHEABLE);
        BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);
    }

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);

    if (wrap == ENABLE) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, L1C_WRAP_DIS);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, L1C_WRAP_DIS);
    }

    BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);

    if (cacheEn != 0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, L1C_CACHEABLE);
        BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  cache way disable set
 *
 * @param  disableVal: cache way disable value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_Set_Way_Disable(uint8_t disableVal)
{
    uint32_t tmpVal = 0;
    uint8_t cacheEn = 0;

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);
    cacheEn = BL_IS_REG_BIT_SET(L1C_BASE, L1C_CACHEABLE);

    if (cacheEn != 0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, L1C_CACHEABLE);
        BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);
    }

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, L1C_WAY_DIS, disableVal);
    BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);

    if (cacheEn != 0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, L1C_CACHEABLE);
        BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Set for ROM 2T access if CPU freq >120MHz
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_IROM_2T_Access_Set(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, L1C_IROM_2T_ACCESS);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, L1C_IROM_2T_ACCESS);
    }

    BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  L1C BMX init
 *
 * @param  l1cBmxCfg: L1C BMX config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type L1C_BMX_Init(L1C_BMX_Cfg_Type *l1cBmxCfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((l1cBmxCfg->timeoutEn) <= 0xF);

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, L1C_BMX_TIMEOUT_EN, l1cBmxCfg->timeoutEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, L1C_BMX_ERR_EN, l1cBmxCfg->errEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, L1C_BMX_ARB_MODE, l1cBmxCfg->arbMod);
    BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(L1C_BMX_ERR_IRQn, L1C_BMX_ERR_IRQHandler);
    Interrupt_Handler_Register(L1C_BMX_TO_IRQn, L1C_BMX_TO_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  L1C BMX address monitor enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type L1C_BMX_Addr_Monitor_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(L1C_BASE, L1C_BMX_ERR_ADDR_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, L1C_BMX_ERR_ADDR_DIS);
    BL_WR_REG(L1C_BASE, L1C_BMX_ERR_ADDR_EN, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  L1C BMX address monitor disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type L1C_BMX_Addr_Monitor_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(L1C_BASE, L1C_BMX_ERR_ADDR_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, L1C_BMX_ERR_ADDR_DIS);
    BL_WR_REG(L1C_BASE, L1C_BMX_ERR_ADDR_EN, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  L1C BMX bus error response enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type L1C_BMX_BusErrResponse_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, L1C_BMX_ERR_EN);
    BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  L1C BMX bus error response disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type L1C_BMX_BusErrResponse_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(L1C_BASE, L1C_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, L1C_BMX_ERR_EN);
    BL_WR_REG(L1C_BASE, L1C_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get L1C BMX error status
 *
 * @param  errType: L1C BMX error status type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type L1C_BMX_Get_Status(L1C_BMX_BUS_ERR_Type errType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_L1C_BMX_BUS_ERR_TYPE(errType));

    tmpVal = BL_RD_REG(L1C_BASE, L1C_BMX_ERR_ADDR_EN);

    if (errType == L1C_BMX_BUS_ERR_TRUSTZONE_DECODE) {
        return BL_GET_REG_BITS_VAL(tmpVal, L1C_BMX_ERR_TZ) ? SET : RESET;
    } else {
        return BL_GET_REG_BITS_VAL(tmpVal, L1C_BMX_ERR_DEC) ? SET : RESET;
    }
}

/****************************************************************************/ /**
 * @brief  Get L1C BMX error address
 *
 * @param  None
 *
 * @return NP L1C BMX error address
 *
*******************************************************************************/
uint32_t L1C_BMX_Get_Err_Addr(void)
{
    return BL_RD_REG(L1C_BASE, L1C_BMX_ERR_ADDR);
}

/****************************************************************************/ /**
 * @brief  L1C BMX error interrupt callback install
 *
 * @param  intType: L1C BMX error interrupt type
 * @param  cbFun: callback
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type L1C_BMX_ERR_INT_Callback_Install(L1C_BMX_ERR_INT_Type intType, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_L1C_BMX_ERR_INT_TYPE(intType));

    l1cBmxErrIntCbfArra[intType] = cbFun;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  L1C BMX ERR interrupt IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void L1C_BMX_ERR_IRQHandler(void)
{
    L1C_BMX_ERR_INT_Type intType;

    for (intType = L1C_BMX_ERR_INT_ERR; intType < L1C_BMX_ERR_INT_ALL; intType++) {
        if (l1cBmxErrIntCbfArra[intType] != NULL) {
            l1cBmxErrIntCbfArra[intType]();
        }
    }

    while (1) {
        MSG("L1C_BMX_ERR_IRQHandler\r\n");
        BL602_Delay_MS(1000);
    }
}
#endif

/****************************************************************************/ /**
 * @brief  L1C BMX timeout interrupt callback install
 *
 * @param  intType: L1C BMX timeout interrupt type
 * @param  cbFun: callback
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type L1C_BMX_TIMEOUT_INT_Callback_Install(L1C_BMX_TO_INT_Type intType, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_L1C_BMX_TO_INT_TYPE(intType));

    l1cBmxToIntCbfArra[intType] = cbFun;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  L1C BMX Time Out interrupt IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void L1C_BMX_TO_IRQHandler(void)
{
    L1C_BMX_TO_INT_Type intType;

    for (intType = L1C_BMX_TO_INT_TIMEOUT; intType < L1C_BMX_TO_INT_ALL; intType++) {
        if (l1cBmxToIntCbfArra[intType] != NULL) {
            l1cBmxToIntCbfArra[intType]();
        }
    }

    while (1) {
        MSG("L1C_BMX_TO_IRQHandler\r\n");
        BL602_Delay_MS(1000);
    }
}
#endif

/*@} end of group L1C_Public_Functions */

/*@} end of group L1C */

/*@} end of group BL602_Peripheral_Driver */
