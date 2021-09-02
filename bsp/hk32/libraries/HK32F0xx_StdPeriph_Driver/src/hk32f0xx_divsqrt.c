/**
  *****************************************************************************************************
  * @file    hk32f0xx_divsqrt.h
  * @brief   hk32f0xx divsqrt  file.
  *          The file is the unique include file that the application programmer
    *          is using in the C source code.it is a patch file
  *****************************************************************************************************
**/


/* Define to prevent recursive inclusion -------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

#include "hk32f0xx_divsqrt.h"

/*******************************************************************************************************
* @function: HK_Dvsq_Init
* @brief:    使能DVSQ外设时钟
********************************************************************************************************/
void HK_Dvsq_Init(void)
{
    RCC_AHBPeriph_DVSQ_CLK_Enable();
}

/*******************************************************************************************************
* @function: HK_Dvsq_Divsion
* @brief:    DVSQ除法运算
* @param:    u32Dividend: 32位无符号被除数
* @param:    u32Divisor: 除数
* @param:    u32pRemainder: 用于存放余数的数据指针
* @param:    u8IsUnsigned: 1-启用无符号除法运算模式
                           0-启用带符号除法运算模式
* @param:    u8IsFastStart: 1-使用除法快速启动模式(硬件检测到除数写入后即刻开始运算)
*                           0-不使用除法快速启动模式(由软件启动除法运算)
*            FlagStatus定义在"hk32f0xx.h"里面
* @return:   商
* @note  :   u32开头的变量： 32位无符号型变量          e开头的变量： enum枚举类型
*******************************************************************************************************/
uint32_t HK_Dvsq_Divsion(uint32_t u32Dividend, uint32_t u32Divisor, uint32_t *u32pRemainder,
                         FlagStatus eIsUnsigned, FlagStatus eIsFastStart)
{
    DVSQ_Wait();

    // 是否使用无符号模式进行除法运算
    if (eIsUnsigned == SET)
        DVSQ_ConfigDivUnsigned();
    else
        DVSQ_ConfigDivSigned();

    // 是否启用快速启动除法功能
    if (eIsFastStart == SET)
    {
        DVSQ_EnableDivFastStart();

        DVSQ->DIVIDEND = u32Dividend;
        DVSQ->DIVISOR  = u32Divisor;

        DVSQ_Wait();

        *u32pRemainder = DVSQ->REMAINDER;
    }
    else
    {
        DVSQ_DisableDivFastStart();

        DVSQ->DIVIDEND = u32Dividend;
        DVSQ->DIVISOR  = u32Divisor;

        DVSQ_StartDivCalc();

        DVSQ_Wait();

        *u32pRemainder = DVSQ->REMAINDER;
    }

    return DVSQ->RES;
}

/*******************************************************************************************************
* @function: HK_Dvsq_Sqrt
* @brief:    DVSQ开方运算
* @param:    u32Radicand: 被开方数
* @param:    eIsHighPres: 1-启用高精度开方运算模式
*                         0-不启用高精度开方运算模式
*                         FlagStatus定义在"hk32f0xx.h"里面
* @return:   开方结果
* @note  :   u32开头的变量： 32位无符号型变量          e开头的变量： enum枚举类型
*******************************************************************************************************/
uint32_t HK_Dvsq_Sqrt(uint32_t u32Radicand, FlagStatus eIsHighPres)
{
    DVSQ_Wait();

    // 是否使能高精度开方模式
    if (eIsHighPres == SET)
        DVSQ_ConfigSqrtPresHigh();
    else
        DVSQ_ConfigSqrtPresNormal();

    DVSQ->RADICAND = u32Radicand;

    DVSQ_Wait();

    return DVSQ->RES;
}

