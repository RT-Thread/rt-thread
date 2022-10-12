/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_aes.c
  * @author  FMSH Application Team
  * @brief   Src file of AES FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @addtogroup AES
  * @{
  */

#ifdef FL_AES_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup AES_FL_Private_Macros
  * @{
  */

#define         IS_FL_AES_INSTANCE(INSTANCE)                (((INSTANCE) == AES))

#define         IS_FL_AES_KEYLENGTH(__VALUE__)               (((__VALUE__) == FL_AES_KEY_LENGTH_128B)||\
                                                             ((__VALUE__) == FL_AES_KEY_LENGTH_192B)||\
                                                             ((__VALUE__) == FL_AES_KEY_LENGTH_256B))

#define         IS_FL_AES_CIPHERMODE(__VALUE__)             (((__VALUE__) == FL_AES_CIPHER_ECB)||\
                                                             ((__VALUE__) == FL_AES_CIPHER_CBC)||\
                                                             ((__VALUE__) == FL_AES_CIPHER_CTR)||\
                                                             ((__VALUE__) == FL_AES_CIPHER_MULTH))

#define         IS_FL_AES_OPERATIONMODE(__VALUE__)          (((__VALUE__) == FL_AES_OPERATION_MODE_ENCRYPTION)||\
                                                             ((__VALUE__) == FL_AES_OPERATION_MODE_KEYDERIVATION)||\
                                                             ((__VALUE__) == FL_AES_OPERATION_MODE_DECRYPTION)||\
                                                             ((__VALUE__) == FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION))

#define         IS_FL_AES_DATATYPE(__VALUE__)               (((__VALUE__) == FL_AES_DATA_TYPE_32B)||\
                                                             ((__VALUE__) == FL_AES_DATA_TYPE_16B)||\
                                                             ((__VALUE__) == FL_AES_DATA_TYPE_8B)||\
                                                             ((__VALUE__) == FL_AES_DATA_TYPE_1B))
/**
  * @}
  */

/** @addtogroup AES_FL_EF_Init
  * @{
  */

/**
  * @brief  复位AES外设
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_AES_DeInit(void)
{
    /* 外设复位使能 */
    FL_RCC_EnablePeripheralReset();
    /* 复位AES */
    FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_AES);
    FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_AES);
    /* 关闭总线时钟 */
    FL_RCC_DisableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_AES);
    /* 锁定外设复位功能 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  根据 AES_InitStructer 初始化对应外设入口地址的寄存器值.
  *
  * @param  AESx 外设入口地址
  * @param  AES_InitStructer 指向 @ref FL_AES_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_AES_Init(AES_Type *AESx, FL_AES_InitTypeDef *AES_InitStructer)
{
    /* 入口合法性检查 */
    assert_param(IS_FL_AES_INSTANCE(AESx));
    assert_param(IS_FL_AES_KEYLENGTH(AES_InitStructer->keyLength));
    assert_param(IS_FL_AES_CIPHERMODE(AES_InitStructer->cipherMode));
    assert_param(IS_FL_AES_OPERATIONMODE(AES_InitStructer->operationMode));
    assert_param(IS_FL_AES_DATATYPE(AES_InitStructer->dataType));
    FL_AES_Disable(AES);
    if(FL_AES_IsEnabled(AESx) == 0)
    {
        /* 开启总线时钟 */
        FL_RCC_EnableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_AES);
        /* key长度 */
        FL_AES_SetKeySize(AESx, AES_InitStructer->keyLength);
        /* 数据流处理模式 */
        FL_AES_SetCipherMode(AESx, AES_InitStructer->cipherMode);
        /* 操作模式 */
        FL_AES_SetOperationMode(AESx, AES_InitStructer->operationMode);
        /* 数据类型 */
        FL_AES_SetDataType(AESx, AES_InitStructer->dataType);
    }
    else
    {
        return FL_FAIL;
    }
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_AES_InitTypeDef 结构体初始化为默认配置
  * @param  AES_InitStructer 指向 @ref FL_AES_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_AES_StructInit(FL_AES_InitTypeDef *AES_InitStructer)
{
    AES_InitStructer->keyLength      = FL_AES_KEY_LENGTH_128B;
    AES_InitStructer->cipherMode     = FL_AES_CIPHER_ECB;
    AES_InitStructer->operationMode  = FL_AES_OPERATION_MODE_ENCRYPTION;
    AES_InitStructer->dataType       = FL_AES_DATA_TYPE_32B;
}
/**
  * @}
  */

#endif /* FL_AES_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
