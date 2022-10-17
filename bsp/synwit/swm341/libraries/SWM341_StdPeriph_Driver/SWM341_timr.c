/******************************************************************************************************************************************
* 文件名称: SWM341_timr.c
* 功能说明: SWM341单片机的计数器/定时器功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0      2016年1月30日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include "SWM341.h"
#include "SWM341_timr.h"


/******************************************************************************************************************************************
* 函数名称: TIMR_Init()
* 功能说明: TIMR定时器/计数器初始化
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，有效值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
*           uint32_t mode           对于TIMR0~4: TIMR_MODE_TIMER、TIMR_MODE_COUNTER、TIMR_MODE_OC、TIMR_MODE_IC
*                                   对于BTIMR0~11: TIMR_MODE_TIMER、TIMR_MODE_OC
*           uint16_t prediv         预分频，取值1-256
*           uint32_t period         定时/计数周期，取值1-16777216
*           uint32_t int_en         中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Init(TIMR_TypeDef * TIMRx, uint32_t mode, uint16_t prediv, uint32_t period, uint32_t int_en)
{
    if((TIMRx == TIMR0) || (TIMRx == TIMR1) || (TIMRx == TIMR2) || (TIMRx == TIMR3) || (TIMRx == TIMR4))
    {
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_TIMR_Pos);
    }
    else
    {
        SYS->CLKEN1 |= (0x01 << SYS_CLKEN1_BTIMR_Pos);
    }

    TIMR_Stop(TIMRx);   //一些关键寄存器只能在定时器停止时设置

    TIMRx->CR &= ~(TIMR_CR_MODE_Msk | TIMR_CR_CLKSRC_Msk);
    TIMRx->CR |= (mode << TIMR_CR_CLKSRC_Pos);

    TIMRx->PREDIV = prediv - 1;

    TIMRx->LOAD = period - 1;

    TIMRx->IF = (1 << TIMR_IF_TO_Pos);      //清除中断标志
    if(int_en) TIMRx->IE |=  (1 << TIMR_IE_TO_Pos);
    else       TIMRx->IE &= ~(1 << TIMR_IE_TO_Pos);

    switch((uint32_t)TIMRx)
    {
    case ((uint32_t)TIMR0):
        if(int_en) NVIC_EnableIRQ(TIMR0_IRQn);
        break;

    case ((uint32_t)TIMR1):
        if(int_en) NVIC_EnableIRQ(TIMR1_IRQn);
        break;

    case ((uint32_t)TIMR2):
        if(int_en) NVIC_EnableIRQ(TIMR2_IRQn);
        break;

    case ((uint32_t)TIMR3):
        if(int_en) NVIC_EnableIRQ(TIMR3_IRQn);
        break;

    case ((uint32_t)TIMR4):
        if(int_en) NVIC_EnableIRQ(TIMR4_IRQn);
        break;

    case ((uint32_t)BTIMR0):
        if(int_en) NVIC_EnableIRQ(BTIMR0_IRQn);
        break;

    case ((uint32_t)BTIMR1):
        if(int_en) NVIC_EnableIRQ(BTIMR1_IRQn);
        break;

    case ((uint32_t)BTIMR2):
        if(int_en) NVIC_EnableIRQ(BTIMR2_IRQn);
        break;

    case ((uint32_t)BTIMR3):
        if(int_en) NVIC_EnableIRQ(BTIMR3_IRQn);
        break;

    case ((uint32_t)BTIMR4):
        if(int_en) NVIC_EnableIRQ(BTIMR4_IRQn);
        break;

    case ((uint32_t)BTIMR5):
        if(int_en) NVIC_EnableIRQ(BTIMR5_IRQn);
        break;

    case ((uint32_t)BTIMR6):
        if(int_en) NVIC_EnableIRQ(BTIMR6_IRQn);
        break;

    case ((uint32_t)BTIMR7):
        if(int_en) NVIC_EnableIRQ(BTIMR7_IRQn);
        break;

    case ((uint32_t)BTIMR8):
        if(int_en) NVIC_EnableIRQ(BTIMR8_IRQn);
        break;

    case ((uint32_t)BTIMR9):
        if(int_en) NVIC_EnableIRQ(BTIMR9_IRQn);
        break;

    case ((uint32_t)BTIMR10):
        if(int_en) NVIC_EnableIRQ(BTIMR10_IRQn);
        break;

    case ((uint32_t)BTIMR11):
        if(int_en) NVIC_EnableIRQ(BTIMR11_IRQn);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: TIMR_Start()
* 功能说明: 启动定时器，从初始值开始计时/计数
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Start(TIMR_TypeDef * TIMRx)
{
    switch((uint32_t)TIMRx)
    {
    case ((uint32_t)TIMR0):
        TIMRG->EN |= (1 << TIMRG_EN_TIMR0_Pos);
        break;

    case ((uint32_t)TIMR1):
        TIMRG->EN |= (1 << TIMRG_EN_TIMR1_Pos);
        break;

    case ((uint32_t)TIMR2):
        TIMRG->EN |= (1 << TIMRG_EN_TIMR2_Pos);
        break;

    case ((uint32_t)TIMR3):
        TIMRG->EN |= (1 << TIMRG_EN_TIMR3_Pos);
        break;

    case ((uint32_t)TIMR4):
        TIMRG->EN |= (1 << TIMRG_EN_TIMR4_Pos);
        break;

    case ((uint32_t)BTIMR0):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR0_Pos);
        break;

    case ((uint32_t)BTIMR1):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR1_Pos);
        break;

    case ((uint32_t)BTIMR2):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR2_Pos);
        break;

    case ((uint32_t)BTIMR3):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR3_Pos);
        break;

    case ((uint32_t)BTIMR4):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR4_Pos);
        break;

    case ((uint32_t)BTIMR5):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR5_Pos);
        break;

    case ((uint32_t)BTIMR6):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR6_Pos);
        break;

    case ((uint32_t)BTIMR7):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR7_Pos);
        break;

    case ((uint32_t)BTIMR8):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR8_Pos);
        break;

    case ((uint32_t)BTIMR9):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR9_Pos);
        break;

    case ((uint32_t)BTIMR10):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR10_Pos);
        break;

    case ((uint32_t)BTIMR11):
        BTIMRG->EN |= (1 << TIMRG_EN_TIMR11_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: TIMR_Stop()
* 功能说明: 停止定时器
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Stop(TIMR_TypeDef * TIMRx)
{
    switch((uint32_t)TIMRx)
    {
    case ((uint32_t)TIMR0):
        TIMRG->EN &= ~(1 << TIMRG_EN_TIMR0_Pos);
        break;

    case ((uint32_t)TIMR1):
        TIMRG->EN &= ~(1 << TIMRG_EN_TIMR1_Pos);
        break;

    case ((uint32_t)TIMR2):
        TIMRG->EN &= ~(1 << TIMRG_EN_TIMR2_Pos);
        break;

    case ((uint32_t)TIMR3):
        TIMRG->EN &= ~(1 << TIMRG_EN_TIMR3_Pos);
        break;

    case ((uint32_t)TIMR4):
        TIMRG->EN &= ~(1 << TIMRG_EN_TIMR4_Pos);
        break;

    case ((uint32_t)BTIMR0):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR0_Pos);
        break;

    case ((uint32_t)BTIMR1):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR1_Pos);
        break;

    case ((uint32_t)BTIMR2):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR2_Pos);
        break;

    case ((uint32_t)BTIMR3):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR3_Pos);
        break;

    case ((uint32_t)BTIMR4):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR4_Pos);
        break;

    case ((uint32_t)BTIMR5):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR5_Pos);
        break;

    case ((uint32_t)BTIMR6):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR6_Pos);
        break;

    case ((uint32_t)BTIMR7):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR7_Pos);
        break;

    case ((uint32_t)BTIMR8):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR8_Pos);
        break;

    case ((uint32_t)BTIMR9):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR9_Pos);
        break;

    case ((uint32_t)BTIMR10):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR10_Pos);
        break;

    case ((uint32_t)BTIMR11):
        BTIMRG->EN &= ~(1 << TIMRG_EN_TIMR11_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: TIMR_Halt()
* 功能说明: 暂停定时器，计数值保持不变
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Halt(TIMR_TypeDef * TIMRx)
{
    TIMRx->HALT = 1;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_Resume()
* 功能说明: 恢复定时器，从暂停处继续计数
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Resume(TIMR_TypeDef * TIMRx)
{
    TIMRx->HALT = 0;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_GetCurValue()
* 功能说明: 获取当前计数值
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: uint32_t              当前计数值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_GetCurValue(TIMR_TypeDef * TIMRx)
{
    return TIMRx->VALUE;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_INTEn()
* 功能说明: 使能中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTEn(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE |= (1 << TIMR_IE_TO_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_INTDis()
* 功能说明: 禁能中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTDis(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE &= ~(1 << TIMR_IE_TO_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_INTClr()
* 功能说明: 清除中断标志
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTClr(TIMR_TypeDef * TIMRx)
{
    TIMRx->IF = (1 << TIMR_IF_TO_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_INTStat()
* 功能说明: 获取中断状态
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: uint32_t              0 TIMRx未产生中断    1 TIMRx产生了中断
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_INTStat(TIMR_TypeDef * TIMRx)
{
    return (TIMRx->IF & TIMR_IF_TO_Msk) ? 1 : 0;
}


/******************************************************************************************************************************************
* 函数名称: TIMR_OC_Init()
* 功能说明: 输出比较功能初始化
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
*           uint32_t match          当计数器的值递减到match时引脚输出电平翻转
*           uint32_t match_int_en   当计数器的值递减到match时是否产生中断
*           uint32_t init_lvl       初始输出电平
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_Init(TIMR_TypeDef * TIMRx, uint32_t match, uint32_t match_int_en, uint32_t init_lvl)
{
    TIMRx->OCMAT = match;
    if(init_lvl) TIMRx->OCCR |=  (1 << TIMR_OCCR_INITLVL_Pos);
    else         TIMRx->OCCR &= ~(1 << TIMR_OCCR_INITLVL_Pos);

    TIMRx->IF = (1 << TIMR_IF_OC0_Pos);     //清除中断标志
    if(match_int_en) TIMRx->IE |=  (1 << TIMR_IE_OC0_Pos);
    else             TIMRx->IE &= ~(1 << TIMR_IE_OC0_Pos);

    switch((uint32_t)TIMRx)
    {
    case ((uint32_t)TIMR0):
        if(match_int_en) NVIC_EnableIRQ(TIMR0_IRQn);
        break;

    case ((uint32_t)TIMR1):
        if(match_int_en) NVIC_EnableIRQ(TIMR1_IRQn);
        break;

    case ((uint32_t)TIMR2):
        if(match_int_en) NVIC_EnableIRQ(TIMR2_IRQn);
        break;

    case ((uint32_t)TIMR3):
        if(match_int_en) NVIC_EnableIRQ(TIMR3_IRQn);
        break;

    case ((uint32_t)TIMR4):
        if(match_int_en) NVIC_EnableIRQ(TIMR4_IRQn);
        break;

    case ((uint32_t)BTIMR0):
        if(match_int_en) NVIC_EnableIRQ(BTIMR0_IRQn);
        break;

    case ((uint32_t)BTIMR1):
        if(match_int_en) NVIC_EnableIRQ(BTIMR1_IRQn);
        break;

    case ((uint32_t)BTIMR2):
        if(match_int_en) NVIC_EnableIRQ(BTIMR2_IRQn);
        break;

    case ((uint32_t)BTIMR3):
        if(match_int_en) NVIC_EnableIRQ(BTIMR3_IRQn);
        break;

    case ((uint32_t)BTIMR4):
        if(match_int_en) NVIC_EnableIRQ(BTIMR4_IRQn);
        break;

    case ((uint32_t)BTIMR5):
        if(match_int_en) NVIC_EnableIRQ(BTIMR5_IRQn);
        break;

    case ((uint32_t)BTIMR6):
        if(match_int_en) NVIC_EnableIRQ(BTIMR6_IRQn);
        break;

    case ((uint32_t)BTIMR7):
        if(match_int_en) NVIC_EnableIRQ(BTIMR7_IRQn);
        break;

    case ((uint32_t)BTIMR8):
        if(match_int_en) NVIC_EnableIRQ(BTIMR8_IRQn);
        break;

    case ((uint32_t)BTIMR9):
        if(match_int_en) NVIC_EnableIRQ(BTIMR9_IRQn);
        break;

    case ((uint32_t)BTIMR10):
        if(match_int_en) NVIC_EnableIRQ(BTIMR10_IRQn);
        break;

    case ((uint32_t)BTIMR11):
        if(match_int_en) NVIC_EnableIRQ(BTIMR11_IRQn);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_OutputEn()
* 功能说明: 使能输出比较功能的波形输出
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_OutputEn(TIMR_TypeDef * TIMRx)
{
    TIMRx->OCCR &= ~(TIMR_OCCR_FORCEEN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_OutputDis()
* 功能说明: 禁止输出比较功能的波形输出，且让输出比较功能引脚保持level电平
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
*           uint32_t level          禁止输出波形后在引脚上保持的电平
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_OutputDis(TIMR_TypeDef * TIMRx, uint32_t level)
{
    if(level) TIMRx->OCCR |=  (1 << TIMR_OCCR_FORCELVL_Pos);
    else      TIMRx->OCCR &= ~(1 << TIMR_OCCR_FORCELVL_Pos);

    TIMRx->OCCR |= (TIMR_OCCR_FORCEEN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_SetMatch()
* 功能说明: 设置输出比较功能的比较值
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
*           uint32_t match          输出比较功能的比较值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_SetMatch(TIMR_TypeDef * TIMRx, uint32_t match)
{
    TIMRx->OCMAT = match;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_GetMatch()
* 功能说明: 获取输出比较功能的比较值
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: uint32_t              输出比较功能的比较值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_OC_GetMatch(TIMR_TypeDef * TIMRx)
{
    return TIMRx->OCMAT;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_INTEn()
* 功能说明: 使能输出比较中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_INTEn(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE |= (1 << TIMR_IE_OC0_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_INTDis()
* 功能说明: 禁能输出比较中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_INTDis(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE &= ~(1 << TIMR_IE_OC0_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_INTClr()
* 功能说明: 清除输出比较中断标志
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_INTClr(TIMR_TypeDef * TIMRx)
{
    TIMRx->IF = (1 << TIMR_IF_OC0_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_OC_INTStat()
* 功能说明: 获取输出比较中断状态
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、BTIMR0、BTIMR1、...、BTIMR11
* 输    出: uint32_t              0 输出比较match未发生   1 输出比较match发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_OC_INTStat(TIMR_TypeDef * TIMRx)
{
    return (TIMRx->IF & TIMR_IF_OC0_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_Init()
* 功能说明: 输入捕获功能初始化
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
*           uint32_t captureH_int_en    测量高电平长度完成中断使能
*           uint32_t captureL_int_en    测量低电平长度完成中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_Init(TIMR_TypeDef * TIMRx, uint32_t captureH_int_en, uint32_t captureL_int_en)
{
    TIMRx->IF = (TIMR_IF_ICR_Msk | TIMR_IF_ICF_Msk);
    if(captureH_int_en) TIMRx->IE |=  (1 << TIMR_IE_ICF_Pos);
    else                TIMRx->IE &= ~(1 << TIMR_IE_ICF_Pos);
    if(captureL_int_en) TIMRx->IE |=  (1 << TIMR_IE_ICR_Pos);
    else                TIMRx->IE &= ~(1 << TIMR_IE_ICR_Pos);

    switch((uint32_t)TIMRx)
    {
    case ((uint32_t)TIMR0):
        if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR0_IRQn);
        break;

    case ((uint32_t)TIMR1):
        if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR1_IRQn);
        break;

    case ((uint32_t)TIMR2):
        if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR2_IRQn);
        break;

    case ((uint32_t)TIMR3):
        if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR3_IRQn);
        break;

    case ((uint32_t)TIMR4):
        if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR4_IRQn);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_GetCaptureH()
* 功能说明: 获取高电平长度测量结果
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: uint32_t              高电平长度测量结果
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_GetCaptureH(TIMR_TypeDef * TIMRx)
{
    return TIMRx->ICHIGH;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_GetCaptureL()
* 功能说明: 获取低电平长度测量结果
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: uint32_t              低电平长度测量结果
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_GetCaptureL(TIMR_TypeDef * TIMRx)
{
    return TIMRx->ICLOW;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureH_INTEn()
* 功能说明: 使能输入捕获高电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTEn(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE |= (1 << TIMR_IE_ICF_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureH_INTDis()
* 功能说明: 禁能输入捕获高电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTDis(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE &= ~(1 << TIMR_IE_ICF_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureH_INTClr()
* 功能说明: 清除输入捕获高电平长度测量完成中断标志
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTClr(TIMR_TypeDef * TIMRx)
{
    TIMRx->IF = (1 << TIMR_IF_ICF_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureH_INTStat()
* 功能说明: 获取输入捕获高电平长度测量完成中断状态
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: uint32_t              0 高电平长度测量未完成    1 高电平长度测量完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_CaptureH_INTStat(TIMR_TypeDef * TIMRx)
{
    return (TIMRx->IF & TIMR_IF_ICF_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureL_INTEn()
* 功能说明: 使能输入捕获低电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTEn(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE |= (1 << TIMR_IE_ICR_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureL_INTDis()
* 功能说明: 禁能输入捕获低电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTDis(TIMR_TypeDef * TIMRx)
{
    TIMRx->IE &= ~(1 << TIMR_IE_ICR_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureL_INTClr()
* 功能说明: 清除输入捕获低电平长度测量完成中断标志
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTClr(TIMR_TypeDef * TIMRx)
{
    TIMRx->IF = (1 << TIMR_IF_ICR_Pos);
}

/******************************************************************************************************************************************
* 函数名称: TIMR_IC_CaptureL_INTStat()
* 功能说明: 获取输入捕获低电平长度测量完成中断状态
* 输    入: TIMR_TypeDef * TIMRx  指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4
* 输    出: uint32_t              0 低电平长度测量未完成    1 低电平长度测量完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_CaptureL_INTStat(TIMR_TypeDef * TIMRx)
{
    return (TIMRx->IF & TIMR_IF_ICR_Msk) ? 1 : 0;
}
