/******************************************************************************************************************************************
* 文件名称: SWM320_pwm.c
* 功能说明: SWM320单片机的PWM功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2017年10月25日
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
#include "SWM320.h"
#include "SWM320_pwm.h"


/******************************************************************************************************************************************
* 函数名称: PWM_Init()
* 功能说明: PWM初始化
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           PWM_InitStructure * initStruct  包含PWM相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_Init(PWM_TypeDef * PWMx, PWM_InitStructure * initStruct)
{
    uint32_t bit_offset = 0;

    SYS->CLKEN |= (0x01 << SYS_CLKEN_PWM_Pos);

    SYS->CLKDIV &= ~SYS_CLKDIV_PWM_Msk;
    SYS->CLKDIV |= (initStruct->clk_div << SYS_CLKDIV_PWM_Pos);

    PWM_Stop(PWMx, 1, 1);   //一些关键寄存器只能在PWM停止时设置

    PWMx->MODE = initStruct->mode;

    PWMx->PERA = initStruct->cycleA;
    PWMx->HIGHA = initStruct->hdutyA;
    PWMx->DZA = initStruct->deadzoneA;

    PWMx->PERB = initStruct->cycleB;
    PWMx->HIGHB = initStruct->hdutyB;
    PWMx->DZB = initStruct->deadzoneB;

    PWMx->INIOUT &= ~(PWM_INIOUT_PWMA_Msk | PWM_INIOUT_PWMB_Msk);
    PWMx->INIOUT |= (initStruct->initLevelA << PWM_INIOUT_PWMA_Pos) |
                    (initStruct->initLevelB << PWM_INIOUT_PWMB_Pos);

    PWMG->IM = 0x00000000;

    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        bit_offset = 0;
        break;

    case((uint32_t)PWM1):
        bit_offset = 2;
        break;

    case((uint32_t)PWM2):
        bit_offset = 4;
        break;

    case((uint32_t)PWM3):
        bit_offset = 6;
        break;

    case((uint32_t)PWM4):
        bit_offset = 8;
        break;

    case((uint32_t)PWM5):
        bit_offset = 10;
        break;
    }

    PWMG->IRS = ((0x01 << bit_offset) | (0x01 << (bit_offset+1))  | (0x01 << (bit_offset+12)) | (0x01 << (bit_offset+13))); //清除中断标志
    PWMG->IE &= ~((0x01 << bit_offset) | (0x01 << (bit_offset+1))  | (0x01 << (bit_offset+12)) | (0x01 << (bit_offset+13)));
    PWMG->IE |= (initStruct->NCycleAIEn << bit_offset) | (initStruct->NCycleBIEn << (bit_offset+1)) |
                (initStruct->HEndAIEn << (bit_offset+12)) | (initStruct->HEndBIEn << (bit_offset+13));

    if(initStruct->NCycleAIEn | initStruct->NCycleBIEn | initStruct->HEndAIEn | initStruct->HEndBIEn)
    {
        NVIC_EnableIRQ(PWM_IRQn);
    }
    else if((PWMG->IE & (~((0x01 << bit_offset) | (0x01 << (bit_offset+1))  | (0x01 << (bit_offset+12)) | (0x01 << (bit_offset+13))))) == 0)
    {
        NVIC_DisableIRQ(PWM_IRQn);
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_Start()
* 功能说明: 启动PWM，开始PWM输出
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chA            0 通道A不启动        1 通道A启动
*           uint32_t chB            0 通道B不启动        1 通道B启动
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_Start(PWM_TypeDef * PWMx, uint32_t chA, uint32_t chB)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        PWMG->CHEN |= (chA << PWMG_CHEN_PWM0A_Pos) | (chB << PWMG_CHEN_PWM0B_Pos);
        break;

    case((uint32_t)PWM1):
        PWMG->CHEN |= (chA << PWMG_CHEN_PWM1A_Pos) | (chB << PWMG_CHEN_PWM1B_Pos);
        break;

    case((uint32_t)PWM2):
        PWMG->CHEN |= (chA << PWMG_CHEN_PWM2A_Pos) | (chB << PWMG_CHEN_PWM2B_Pos);
        break;

    case((uint32_t)PWM3):
        PWMG->CHEN |= (chA << PWMG_CHEN_PWM3A_Pos) | (chB << PWMG_CHEN_PWM3B_Pos);
        break;

    case((uint32_t)PWM4):
        PWMG->CHEN |= (chA << PWMG_CHEN_PWM4A_Pos) | (chB << PWMG_CHEN_PWM4B_Pos);
        break;

    case((uint32_t)PWM5):
        PWMG->CHEN |= (chA << PWMG_CHEN_PWM5A_Pos) | (chB << PWMG_CHEN_PWM5B_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_Stop()
* 功能说明: 关闭PWM，停止PWM输出
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chA            0 通道A不关闭        1 通道A关闭
*           uint32_t chB            0 通道B不关闭        1 通道B关闭
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_Stop(PWM_TypeDef * PWMx, uint32_t chA, uint32_t chB)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        PWMG->CHEN &= ~((chA << PWMG_CHEN_PWM0A_Pos) | (chB << PWMG_CHEN_PWM0B_Pos));
        break;

    case((uint32_t)PWM1):
        PWMG->CHEN &= ~((chA << PWMG_CHEN_PWM1A_Pos) | (chB << PWMG_CHEN_PWM1B_Pos));
        break;

    case((uint32_t)PWM2):
        PWMG->CHEN &= ~((chA << PWMG_CHEN_PWM2A_Pos) | (chB << PWMG_CHEN_PWM2B_Pos));
        break;

    case((uint32_t)PWM3):
        PWMG->CHEN &= ~((chA << PWMG_CHEN_PWM3A_Pos) | (chB << PWMG_CHEN_PWM3B_Pos));
        break;

    case((uint32_t)PWM4):
        PWMG->CHEN &= ~((chA << PWMG_CHEN_PWM4A_Pos) | (chB << PWMG_CHEN_PWM4B_Pos));
        break;

    case((uint32_t)PWM5):
        PWMG->CHEN &= ~((chA << PWMG_CHEN_PWM5A_Pos) | (chB << PWMG_CHEN_PWM5B_Pos));
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_SetCycle()
* 功能说明: 设置周期
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
*           uint16_t cycle          要设定的周期值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_SetCycle(PWM_TypeDef * PWMx, uint32_t chn, uint16_t cycle)
{
    if(chn == PWM_CH_A)
        PWMx->PERA = cycle;
    else if(chn == PWM_CH_B)
        PWMx->PERB = cycle;
}

/******************************************************************************************************************************************
* 函数名称: PWM_GetCycle()
* 功能说明: 获取周期
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要查询哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: uint16_t              获取到的周期值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t PWM_GetCycle(PWM_TypeDef * PWMx, uint32_t chn)
{
    uint16_t cycle = 0;

    if(chn == PWM_CH_A)
        cycle = PWMx->PERA;
    else if(chn == PWM_CH_B)
        cycle = PWMx->PERB;

    return cycle;
}

/******************************************************************************************************************************************
* 函数名称: PWM_SetHDuty()
* 功能说明: 设置高电平时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
*           uint16_t hduty          要设定的高电平时长
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_SetHDuty(PWM_TypeDef * PWMx, uint32_t chn, uint16_t hduty)
{
    if(chn == PWM_CH_A)
        PWMx->HIGHA = hduty;
    else if(chn == PWM_CH_B)
        PWMx->HIGHB = hduty;
}

/******************************************************************************************************************************************
* 函数名称: PWM_GetHDuty()
* 功能说明: 获取高电平时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要查询哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: uint16_t              获取到的高电平时长
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t PWM_GetHDuty(PWM_TypeDef * PWMx, uint32_t chn)
{
    uint16_t hduty = 0;

    if(chn == PWM_CH_A)
        hduty = PWMx->HIGHA;
    else if(chn == PWM_CH_B)
        hduty = PWMx->HIGHB;

    return hduty;
}

/******************************************************************************************************************************************
* 函数名称: PWM_SetDeadzone()
* 功能说明: 设置死区时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
*           uint8_t deadzone        要设定的死区时长
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_SetDeadzone(PWM_TypeDef * PWMx, uint32_t chn, uint8_t deadzone)
{
    if(chn == PWM_CH_A)
        PWMx->DZA = deadzone;
    else if(chn == PWM_CH_B)
        PWMx->DZB = deadzone;
}

/******************************************************************************************************************************************
* 函数名称: PWM_GetDeadzone()
* 功能说明: 获取死区时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要查询哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: uint8_t                   获取到的死区时长
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t  PWM_GetDeadzone(PWM_TypeDef * PWMx, uint32_t chn)
{
    uint8_t deadzone = 0;

    if(chn == PWM_CH_A)
        deadzone = PWMx->DZA;
    else if(chn == PWM_CH_B)
        deadzone = PWMx->DZB;

    return deadzone;
}


/******************************************************************************************************************************************
* 函数名称: PWM_IntNCycleEn()
* 功能说明: 新周期开始中断使能
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntNCycleEn(PWM_TypeDef * PWMx, uint32_t chn)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_NEWP0A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_NEWP0B_Pos);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_NEWP1A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_NEWP1B_Pos);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_NEWP2A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_NEWP2B_Pos);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_NEWP3A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_NEWP3B_Pos);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_NEWP4A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_NEWP4B_Pos);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_NEWP5A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_NEWP5B_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntNCycleDis()
* 功能说明: 新周期开始中断禁能
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntNCycleDis(PWM_TypeDef * PWMx, uint32_t chn)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_NEWP0A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_NEWP0B_Pos);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_NEWP1A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_NEWP1B_Pos);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_NEWP2A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_NEWP2B_Pos);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_NEWP3A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_NEWP3B_Pos);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_NEWP4A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_NEWP4B_Pos);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_NEWP5A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_NEWP5B_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntNCycleClr()
* 功能说明: 新周期开始中断标志清除
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntNCycleClr(PWM_TypeDef * PWMx, uint32_t chn)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_NEWP0A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_NEWP0B_Pos);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_NEWP1A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_NEWP1B_Pos);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_NEWP2A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_NEWP2B_Pos);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_NEWP3A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_NEWP3B_Pos);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_NEWP4A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_NEWP4B_Pos);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_NEWP5A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_NEWP5B_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntNCycleStat()
* 功能说明: 新周期开始中断是否发生
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: uint32_t              1 新周期开始中断已发生    0 新周期开始中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWM_IntNCycleStat(PWM_TypeDef * PWMx, uint32_t chn)
{
    uint32_t int_stat = 0;

    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_NEWP0A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_NEWP0B_Msk);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_NEWP1A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_NEWP1B_Msk);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_NEWP2A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_NEWP2B_Msk);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_NEWP3A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_NEWP3B_Msk);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_NEWP4A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_NEWP4B_Msk);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_NEWP5A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_NEWP5B_Msk);
        break;
    }

    return int_stat;
}


/******************************************************************************************************************************************
* 函数名称: PWM_IntHEndEn()
* 功能说明: 高电平结束中断使能
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntHEndEn(PWM_TypeDef * PWMx, uint32_t chn)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_HEND0A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_HEND0B_Pos);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_HEND1A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_HEND1B_Pos);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_HEND2A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_HEND2B_Pos);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_HEND3A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_HEND3B_Pos);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_HEND4A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_HEND4B_Pos);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) PWMG->IE |= (0x01 << PWMG_IE_HEND5A_Pos);
        else                PWMG->IE |= (0x01 << PWMG_IE_HEND5B_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntHEndDis()
* 功能说明: 高电平结束中断禁能
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntHEndDis(PWM_TypeDef * PWMx, uint32_t chn)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_HEND0A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_HEND0B_Pos);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_HEND1A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_HEND1B_Pos);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_HEND2A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_HEND2B_Pos);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_HEND3A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_HEND3B_Pos);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_HEND4A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_HEND4B_Pos);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) PWMG->IE &= ~(0x01 << PWMG_IE_HEND5A_Pos);
        else                PWMG->IE &= ~(0x01 << PWMG_IE_HEND5B_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntHEndClr()
* 功能说明: 高电平结束中断标志清除
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntHEndClr(PWM_TypeDef * PWMx, uint32_t chn)
{
    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_HEND0A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_HEND0B_Pos);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_HEND1A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_HEND1B_Pos);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_HEND2A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_HEND2B_Pos);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_HEND3A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_HEND3B_Pos);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_HEND4A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_HEND4B_Pos);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) PWMG->IRS = (0x01 << PWMG_IRS_HEND5A_Pos);
        else                PWMG->IRS = (0x01 << PWMG_IRS_HEND5B_Pos);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntHEndStat()
* 功能说明: 高电平结束中断是否发生
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4、PWM5
*           uint32_t chn            选择要设置哪个通道，有效值：PWM_CH_A、PWM_CH_B
* 输    出: uint32_t              1 高电平结束中断已发生    0 高电平结束中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWM_IntHEndStat(PWM_TypeDef * PWMx, uint32_t chn)
{
    uint32_t int_stat = 0;

    switch((uint32_t)PWMx)
    {
    case((uint32_t)PWM0):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_HEND0A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_HEND0B_Msk);
        break;

    case((uint32_t)PWM1):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_HEND1A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_HEND1B_Msk);
        break;

    case((uint32_t)PWM2):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_HEND2A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_HEND2B_Msk);
        break;

    case((uint32_t)PWM3):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_HEND3A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_HEND3B_Msk);
        break;

    case((uint32_t)PWM4):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_HEND4A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_HEND4B_Msk);
        break;

    case((uint32_t)PWM5):
        if(chn == PWM_CH_A) int_stat = (PWMG->IF & PWMG_IF_HEND5A_Msk);
        else                int_stat = (PWMG->IF & PWMG_IF_HEND5B_Msk);
        break;
    }

    return int_stat;
}
