/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_pgl.c
  * @author  FMSH Application Team
  * @brief   Src file of PGL FL Module
  *******************************************************************************************************
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
  *******************************************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"

/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @addtogroup PGL
  * @{
  */

#ifdef FL_PGL_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup LUT_FL_Private_Macros
  * @{
  */

#define         IS_FL_PGL_LUT_INSTANCE(INSTANCE)                ((INSTANCE) == PGL)

#define         IS_FL_PGL_LUT_EDGE(__VALUE__)              (((__VALUE__) == FL_PGL_LUT_EDGE_RISING)||\
                                                            ((__VALUE__) == FL_PGL_LUT_EDGE_FALLING)||\
                                                            ((__VALUE__) == FL_PGL_LUT_EDGE_BOTH)||\
                                                            ((__VALUE__) == FL_PGL_LUT_EDGE_NONE))


#define         IS_FL_PGL_LUT_OUT(__VALUE__)              (((__VALUE__) == FL_PGL_LUT_OUTPUT_COMBINE_LOGIC)||\
                                                           ((__VALUE__) == FL_PGL_LUT_OUTPUT_SYNC_SAMPLING)||\
                                                           ((__VALUE__) == FL_PGL_LUT_OUTPUT_DIGITAL_FILTER))

#define         IS_FL_PGL_LUT_INPUTSEL(__VALUE__)          (((__VALUE__) == FL_PGL_LUT_INPUT_GROUP0)||\
                                                            ((__VALUE__) == FL_PGL_LUT_INPUT_GROUP1)||\
                                                            ((__VALUE__) == FL_PGL_LUT_INPUT_GROUP2)||\
                                                            ((__VALUE__) == FL_PGL_LUT_INPUT_GROUP3)||\
                                                            ((__VALUE__) == FL_PGL_LUT_INPUT_DISABLE))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CRC_FL_EF_Init
  * @{
  */

/**
  * @brief  复位对应PGL寄存器.
  * @param  PGLx
  * @retval ErrorStatus枚举值:
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_PGL_DeInit(PGL_Type *PGLx)
{
    assert_param(IS_FL_PGL_LUT_INSTANCE(PGLx));
    /* 使能外设复位 */
    FL_RMU_EnablePeripheralReset(RMU);
    /* 复位PGL外设寄存器 */
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_PGL);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_PGL);
    /* 关闭外设总线时钟与工作时钟 */
    FL_CMU_DisableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_PGL);
    /* 锁定外设复位 */
    FL_RMU_DisablePeripheralReset(RMU);
    return FL_PASS;
}

/**
  * @brief  根据 lutInit 的配置信息初始化对应外设入口地址的寄存器值
  * @param  PGLx PGLx
  * @param  lutInit 指向一个 @ref FL_PGL_LUT_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_PGL_LUT_Init(PGL_Type *PGLx, uint32_t LUTx, FL_PGL_LUT_InitTypeDef *lutInit)
{
    /* 入口参数检查 */
    assert_param(IS_FL_PGL_LUT_INSTANCE(PGLx));
    assert_param(IS_FL_PGL_LUT_EDGE(lutInit->edge));
    assert_param(IS_FL_PGL_LUT_OUT(lutInit->outMode));
    assert_param(IS_FL_PGL_LUT_INPUTSEL(lutInit->input3));
    assert_param(IS_FL_PGL_LUT_INPUTSEL(lutInit->input2));
    assert_param(IS_FL_PGL_LUT_INPUTSEL(lutInit->input1));
    assert_param(IS_FL_PGL_LUT_INPUTSEL(lutInit->input0));
    /* 总线时钟使能 */
    FL_CMU_EnableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_PGL);
    /*有效边沿选择*/
    FL_PGL_SetLUTEffectiveEdge(PGLx, LUTx, lutInit->edge);
    /*输出模式选择*/
    FL_PGL_SetLUTOutputMode(PGLx, LUTx, lutInit->outMode);
    /*输入3选择*/
    if(lutInit->input3 == FL_PGL_LUT_INPUT_DISABLE)
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT3, FL_PGL_LUT_INPUT_GROUP0);
        FL_PGL_EnableLUTInputMask(PGLx, LUTx, FL_PGL_INPUT3);    /* 屏蔽输入3通道 */
    }
    else
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT3, lutInit->input3);
    }
    /*输入2选择*/
    if(lutInit->input2 == FL_PGL_LUT_INPUT_DISABLE)
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT2, FL_PGL_LUT_INPUT_GROUP0);
        FL_PGL_EnableLUTInputMask(PGLx, LUTx, FL_PGL_INPUT2);    /* 屏蔽输入2通道 */
    }
    else
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT2, lutInit->input2);
    }
    /*输入1选择*/
    if(lutInit->input1 == FL_PGL_LUT_INPUT_DISABLE)
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT1, FL_PGL_LUT_INPUT_GROUP0);
        FL_PGL_EnableLUTInputMask(PGLx, LUTx, FL_PGL_INPUT1);    /* 屏蔽输入1通道 */
    }
    else
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT1, lutInit->input1);
    }
    /*输入0选择*/
    if(lutInit->input0 == FL_PGL_LUT_INPUT_DISABLE)
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT0, FL_PGL_LUT_INPUT_GROUP0);
        FL_PGL_EnableLUTInputMask(PGLx, LUTx, FL_PGL_INPUT0);    /* 屏蔽输入0通道 */
    }
    else
    {
        FL_PGL_SetLUTInputSource(PGLx, LUTx, FL_PGL_INPUT0, lutInit->input0);
    }
    return FL_PASS;
}

/**
* @brief   设置 PGL_InitStruct 为默认配置
* @param   PGL_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_PGL_LUT_InitTypeDef 结构体
*
* @retval  None
*/
void FL_PGL_StructInit(FL_PGL_LUT_InitTypeDef *PGL_InitStruct)
{
    PGL_InitStruct->edge                = FL_PGL_LUT_EDGE_NONE;
    PGL_InitStruct->outMode             = FL_PGL_LUT_OUTPUT_COMBINE_LOGIC;
    PGL_InitStruct->input3              = FL_PGL_LUT_INPUT_DISABLE;
    PGL_InitStruct->input2              = FL_PGL_LUT_INPUT_DISABLE;
    PGL_InitStruct->input1              = FL_PGL_LUT_INPUT_DISABLE;
    PGL_InitStruct->input0              = FL_PGL_LUT_INPUT_DISABLE;
}

/**
  * @}
  */

#endif /* FL_PGL_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
