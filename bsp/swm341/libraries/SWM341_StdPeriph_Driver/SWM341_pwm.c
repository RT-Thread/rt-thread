/******************************************************************************************************************************************
* 文件名称: SWM341_pwm.c
* 功能说明: SWM341单片机的PWM功能驱动库
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
#include "SWM341_pwm.h"


/******************************************************************************************************************************************
* 函数名称: PWM_Init()
* 功能说明: PWM初始化
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           PWM_InitStructure * initStruct  包含PWM相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_Init(PWM_TypeDef * PWMx, PWM_InitStructure * initStruct)
{
    SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_PWM_Pos);

    PWMx->CR = (initStruct->Mode         << PWM_CR_MODE_Pos)   |
               (1                        << PWM_CR_MULT_Pos)   |    // 多次计数模式（即非单次）
               (0                        << PWM_CR_DIR_Pos)    |    // 向上计数
               (0                        << PWM_CR_CLKSRC_Pos) |    // 系统时钟
               ((initStruct->Clkdiv - 1) << PWM_CR_CLKDIV_Pos) |
               (0                        << PWM_CR_RPTNUM_Pos); // 每次计数器溢出都执行寄存器重加载

    PWMx->OCR = ((initStruct->IdleLevelA  ? 1 : 0) << PWM_OCR_IDLEA_Pos)  |
                ((initStruct->IdleLevelB  ? 1 : 0) << PWM_OCR_IDLEB_Pos)  |
                ((initStruct->IdleLevelAN ? 1 : 0) << PWM_OCR_IDLEAN_Pos) |
                ((initStruct->IdleLevelBN ? 1 : 0) << PWM_OCR_IDLEBN_Pos) |
                ((initStruct->OutputInvA  ? 1 : 0) << PWM_OCR_INVA_Pos)   |
                ((initStruct->OutputInvB  ? 1 : 0) << PWM_OCR_INVB_Pos)   |
                ((initStruct->OutputInvAN ? 1 : 0) << PWM_OCR_INVAN_Pos)  |
                ((initStruct->OutputInvBN ? 1 : 0) << PWM_OCR_INVBN_Pos);

    PWMx->PERIOD = initStruct->Period - 1;

    PWMx->CMPA  = initStruct->HdutyA;
    PWMx->CMPA2 = initStruct->HdutyA2;
    PWMx->DZA   = initStruct->DeadzoneA;

    PWMx->CMPB  = initStruct->HdutyB;
    PWMx->CMPB2 = initStruct->HdutyB2;
    PWMx->DZB   = initStruct->DeadzoneB;

    PWMG->RELOADEN = 0x3F;

    PWMx->IF = 0x3F;
    PWMx->IE = ((initStruct->UpOvfIE    ? 1 : 0) << PWM_IE_UPOVF_Pos)  |
               ((initStruct->DownOvfIE  ? 1 : 0) << PWM_IE_DNOVF_Pos)  |
               ((initStruct->UpCmpAIE   ? 1 : 0) << PWM_IE_UPCMPA_Pos) |
               ((initStruct->DownCmpAIE ? 1 : 0) << PWM_IE_DNCMPA_Pos) |
               ((initStruct->UpCmpBIE   ? 1 : 0) << PWM_IE_UPCMPB_Pos) |
               ((initStruct->DownCmpBIE ? 1 : 0) << PWM_IE_DNCMPB_Pos);

    if(initStruct->UpOvfIE || initStruct->DownOvfIE || initStruct->UpCmpAIE ||
       initStruct->DownCmpAIE || initStruct->UpCmpBIE || initStruct->DownCmpBIE)
    {
        switch((uint32_t)PWMx)
        {
        case((uint32_t)PWM0):
            NVIC_EnableIRQ(PWM0_IRQn);
            break;

        case((uint32_t)PWM1):
            NVIC_EnableIRQ(PWM1_IRQn);
            break;

        case((uint32_t)PWM2):
            NVIC_EnableIRQ(PWM2_IRQn);
            break;

        case((uint32_t)PWM3):
            NVIC_EnableIRQ(PWM3_IRQn);
            break;

        case((uint32_t)PWM4):
            NVIC_EnableIRQ(PWM4_IRQn);
            break;
        }
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_Start()
* 功能说明: 启动PWM，开始PWM输出
* 输    入: uint32_t pwm          PWM0_MSK、PWM1_MSK、PWM2_MSK、PWM3_MSK、PWM4_MSK、PWM5_MSK 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_Start(uint32_t pwm)
{
    PWMG->START |= pwm;
}

/******************************************************************************************************************************************
* 函数名称: PWM_Stop()
* 功能说明: 关闭PWM，停止PWM输出
* 输    入: uint32_t pwm          PWM0_MSK、PWM1_MSK、PWM2_MSK、PWM3_MSK、PWM4_MSK、PWM5_MSK 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_Stop(uint32_t pwm)
{
    PWMG->START &= ~pwm;
}

/******************************************************************************************************************************************
* 函数名称: PWM_Restart()
* 功能说明: 重启PWM，将PWM计数器清零，然后使用新的周期、高电平时长、死区时长设定值开始计数
* 输    入: uint32_t pwm          PWM0_MSK、PWM1_MSK、PWM2_MSK、PWM3_MSK、PWM4_MSK、PWM5_MSK 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_Restart(uint32_t pwm)
{
    PWMG->RESTART = (pwm << PWMG_RESTART_PWM0_Pos);
}

/******************************************************************************************************************************************
* 函数名称: PWM_ReloadEn()
* 功能说明: 只有当 Reload Enable 时，写入 PERIOD、CMPA、CMPB、DZA、DZB 等寄存器的值才会（在计数器溢出时）加载到内部工作寄存器
* 输    入: uint32_t pwm          PWM0_MSK、PWM1_MSK、PWM2_MSK、PWM3_MSK、PWM4_MSK、PWM5_MSK 及其“或”
* 输    出: 无
* 注意事项: 如果需要保证在写 PERIOD、CMPA、CMPB、DZA、DZB 等寄存器过程中，这些寄存器的值不会被加载到内部工作寄存器，可以如下操作：
*           第一步、PWM_ReloadDis(PWM0_MSK | PWM1_MSK);
*           第二步、写 PERIOD、CMPA、CMPB、DZA、DZB 等寄存器
*           第三步、PWM_ReloadEn(PWM0_MSK | PWM1_MSK);
******************************************************************************************************************************************/
void PWM_ReloadEn(uint32_t pwm)
{
    PWMG->RELOADEN |= pwm;
}

/******************************************************************************************************************************************
* 函数名称: PWM_ReloadDis()
* 功能说明: 只有当 Reload Enable 时，写入 PERIOD、CMPA、CMPB、DZA、DZB 等寄存器的值才会（在计数器溢出时）加载到内部工作寄存器
* 输    入: uint32_t pwm          PWM0_MSK、PWM1_MSK、PWM2_MSK、PWM3_MSK、PWM4_MSK、PWM5_MSK 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_ReloadDis(uint32_t pwm)
{
    PWMG->RELOADEN &= ~pwm;
}

/******************************************************************************************************************************************
* 函数名称: PWM_BrkInPolarity()
* 功能说明: 设置刹车输入有效极性
* 输    入: uint32_t brk          PWM_BRK0、PWM_BRK1、PWM_BRK2 及其“或”
*           uint32_t level          0 低电平刹车   1 高电平刹车
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_BrkInPolarity(uint32_t brk, uint32_t level)
{
    if(level)
        PWMG->BRKPOL |= brk;
    else
        PWMG->BRKPOL &= ~brk;
}

/******************************************************************************************************************************************
* 函数名称: PWM_BrkConfig()
* 功能说明: 刹车配置
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
*           uint32_t brk            刹车输入，PWM_BRK0、PWM_BRK1、PWM_BRK2 及其“或”
*           uint32_t out            刹车过程中PWMxA/PWMxB输出电平
*           uint32_t outN           刹车过程中PWMxAN/PWMxBN输出电平
*           uint32_t outHold        刹车信号撤销后，0 输出立即恢复   1 输出保持到计数器溢出再恢复
*           uint32_t stpCount       刹车状态下是否停止计数，1 停止计数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_BrkConfig(PWM_TypeDef * PWMx, uint32_t chn, uint32_t brk, uint32_t out, uint32_t outN, uint32_t outHold, uint32_t stpCount)
{
    if(chn == PWM_CH_A)
    {
        PWMx->BRKIN &= ~(0x7 << PWM_BRKIN_BRK0A_Pos);
        PWMx->BRKIN |=  (brk << PWM_BRKIN_BRK0A_Pos);

        PWMx->BRKCR &= ~(PWM_BRKCR_OUTA_Msk | PWM_BRKCR_OUTAN_Msk | PWM_BRKCR_OFFA_Msk);
        PWMx->BRKCR |= (out      << PWM_BRKCR_OUTA_Pos)  |
                       (outN     << PWM_BRKCR_OUTAN_Pos) |
                       (outHold  << PWM_BRKCR_OFFA_Pos)  |
                       (stpCount << PWM_BRKCR_STPCNT_Pos);
    }
    else
    {
        PWMx->BRKIN &= ~(0x7 << PWM_BRKIN_BRK0B_Pos);
        PWMx->BRKIN |=  (brk << PWM_BRKIN_BRK0B_Pos);

        PWMx->BRKCR &= ~(PWM_BRKCR_OUTB_Msk | PWM_BRKCR_OUTBN_Msk | PWM_BRKCR_OFFB_Msk);
        PWMx->BRKCR |= (out      << PWM_BRKCR_OUTB_Pos)  |
                       (outN     << PWM_BRKCR_OUTBN_Pos) |
                       (outHold  << PWM_BRKCR_OFFB_Pos)  |
                       (stpCount << PWM_BRKCR_STPCNT_Pos);
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_OvfTrigger()
* 功能说明: 计数器溢出时发出触发信号配置
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t en_up          向上计数时，计数器溢出是否发出触发信号
*           uint32_t en_down        向下计数时，计数器溢出是否发出触发信号
*           uint32_t trig_chn       触发信号有8个通道，选择此触发信号输出到哪个通道，取值PWM_TRG_0、PWM_TRG_1、...、PWM_TRG_7
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_OvfTrigger(PWM_TypeDef * PWMx, uint32_t en_up, uint32_t en_down, uint32_t trig_chn)
{
    PWMx->OVFTRG = (en_up    << PWM_OVFTRG_UPEN_Pos) |
                   (en_down  << PWM_OVFTRG_DNEN_Pos) |
                   (trig_chn << PWM_OVFTRG_MUX_Pos);
}

/******************************************************************************************************************************************
* 函数名称: PWM_CmpTrigger()
* 功能说明: 计数器等于指定数值时发出触发信号配置
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint16_t match          计数值等于match时发出触发信号
*           uint32_t dir            PWM_DIR_UP 向上计数时计数器与match值比较   PWM_DIR_DOWN 向下计数时计数器与match值比较
*           uint32_t width          发出的触发信号的宽度，0 无输出   1 4个时钟周期   2 8个时钟周期    ...   63 252个时钟周期
*           uint32_t trig_chn       触发信号有8个通道，选择此触发信号输出到哪个通道，，取值PWM_TRG_0、PWM_TRG_1、...、PWM_TRG_7
*           uint32_t adc_trig_pos   在发出指定宽度触发信号的同时，还会在该触发信号宽度的 adc_trig_pos/8 位置处发出adc触发信号，取值0--7
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_CmpTrigger(PWM_TypeDef * PWMx, uint16_t match, uint32_t dir, uint32_t width, uint32_t trig_chn, uint32_t adc_trig_pos)
{
    PWMx->CMPTRG = (1        << PWM_CMPTRG_EN_Pos)    |
                   (match    << PWM_CMPTRG_CMP_Pos)   |
                   (dir      << PWM_CMPTRG_DIR_Pos)   |
                   (width    << PWM_CMPTRG_WIDTH_Pos) |
                   (trig_chn << PWM_CMPTRG_MUX_Pos);

    PWM0->CMPTRG &= ~PWM_CMPTRG_ATP_Msk;
    PWM0->CMPTRG |= (adc_trig_pos << PWM_CMPTRG_ATP_Pos);
}

/******************************************************************************************************************************************
* 函数名称: PWM_OutMask()
* 功能说明: 输出屏蔽，当指定输入信号为高时，PWM输出固定电平
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
*           uint32_t evt            PWMxY 由哪路 event 输入信号屏蔽，取值PWM_EVT_DIS、PWM_EVT_0、PWM_EVT_1、...、PWM_EVT_6
*           uint32_t out            PWMxY 输出被屏蔽时输出什么电平
*           uint32_t evt_n          PWMxYN由哪路 event 输入信号屏蔽，取值PWM_EVT_DIS、PWM_EVT_0、PWM_EVT_1、...、PWM_EVT_6
*           uint32_t out_n          PWMxYN输出被屏蔽时输出什么电平
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_OutMask(PWM_TypeDef * PWMx, uint32_t chn, uint32_t evt, uint32_t out, uint32_t evt_n, uint32_t out_n)
{
    if(chn == PWM_CH_A)
    {
        PWMx->EVMUX &= ~(PWM_EVMUX_MASKA_Msk | PWM_EVMUX_MASKAN_Msk);
        PWMx->EVMUX |= (evt   << PWM_EVMUX_MASKA_Pos) |
                       (evt_n << PWM_EVMUX_MASKAN_Pos);

        PWMx->EVMSK &= ~(PWM_EVMSK_OUTA_Msk | PWM_EVMSK_OUTAN_Msk);
        PWMx->EVMSK |= (out   << PWM_EVMSK_OUTA_Pos)  |
                       (out_n << PWM_EVMSK_OUTAN_Pos) |
                       (1     << PWM_EVMSK_IMME_Pos);
    }
    else
    {
        PWMx->EVMUX &= ~(PWM_EVMUX_MASKB_Msk | PWM_EVMUX_MASKBN_Msk);
        PWMx->EVMUX |= (evt   << PWM_EVMUX_MASKB_Pos) |
                       (evt_n << PWM_EVMUX_MASKBN_Pos);

        PWMx->EVMSK &= ~(PWM_EVMSK_OUTB_Msk | PWM_EVMSK_OUTBN_Msk);
        PWMx->EVMSK |= (out   << PWM_EVMSK_OUTB_Pos)  |
                       (out_n << PWM_EVMSK_OUTBN_Pos) |
                       (1     << PWM_EVMSK_IMME_Pos);
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_SetPeriod()
* 功能说明: 设置周期
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint16_t period         要设定的周期值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_SetPeriod(PWM_TypeDef * PWMx, uint16_t period)
{
    PWMx->PERIOD = period - 1;
}

/******************************************************************************************************************************************
* 函数名称: PWM_GetPeriod()
* 功能说明: 获取周期
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
* 输    出: uint16_t              获取到的周期值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t PWM_GetPeriod(PWM_TypeDef * PWMx)
{
    return PWMx->PERIOD + 1;
}

/******************************************************************************************************************************************
* 函数名称: PWM_SetHDuty()
* 功能说明: 设置高电平时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
*           uint16_t hduty          要设定的高电平时长
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_SetHDuty(PWM_TypeDef * PWMx, uint32_t chn, uint16_t hduty)
{
    if(chn == PWM_CH_A)
        PWMx->CMPA = hduty;
    else
        PWMx->CMPB = hduty;
}

/******************************************************************************************************************************************
* 函数名称: PWM_GetHDuty()
* 功能说明: 获取高电平时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
* 输    出: uint16_t              获取到的高电平时长
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t PWM_GetHDuty(PWM_TypeDef * PWMx, uint32_t chn)
{
    if(chn == PWM_CH_A)
        return PWMx->CMPA;
    else
        return PWMx->CMPB;
}

/******************************************************************************************************************************************
* 函数名称: PWM_SetHDuty2()
* 功能说明: 设置高电平时长，用于非对称中心对齐模式
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
*           uint16_t hduty          要设定的前半周期高电平时长
*           uint16_t hduty2         要设定的后半周期高电平时长
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_SetHDuty2(PWM_TypeDef * PWMx, uint32_t chn, uint16_t hduty, uint16_t hduty2)
{
    if(chn == PWM_CH_A)
    {
        PWMx->CMPA  = hduty;
        PWMx->CMPA2 = hduty2;
    }
    else
    {
        PWMx->CMPB  = hduty;
        PWMx->CMPB2 = hduty2;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_GetHDuty2()
* 功能说明: 获取高电平时长，用于非对称中心对齐模式
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
* 输    出: uint16_t *hduty           获取到的前半周期高电平时长
*           uint16_t *hduty2        获取到的后半周期高电平时长
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_GetHDuty2(PWM_TypeDef * PWMx, uint32_t chn, uint16_t *hduty, uint16_t *hduty2)
{
    if(chn == PWM_CH_A)
    {
        *hduty  = PWMx->CMPA;
        *hduty2 = PWMx->CMPA2;
    }
    else
    {
        *hduty  = PWMx->CMPB;
        *hduty2 = PWMx->CMPB2;
    }
}

/******************************************************************************************************************************************
* 函数名称: PWM_SetDeadzone()
* 功能说明: 设置死区时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
*           uint16_t deadzone       要设定的死区时长，取值范围0--1023
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_SetDeadzone(PWM_TypeDef * PWMx, uint32_t chn, uint16_t deadzone)
{
    if(chn == PWM_CH_A)
        PWMx->DZA = deadzone;
    else
        PWMx->DZB = deadzone;
}

/******************************************************************************************************************************************
* 函数名称: PWM_GetDeadzone()
* 功能说明: 获取死区时长
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t chn            指定要被设置的PWM通道，有效值包括PWM_CH_A、PWM_CH_B
* 输    出: uint16_t              获取到的死区时长
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t PWM_GetDeadzone(PWM_TypeDef * PWMx, uint32_t chn)
{
    if(chn == PWM_CH_A)
        return PWMx->DZA;
    else
        return PWMx->DZB;
}


/******************************************************************************************************************************************
* 函数名称: PWM_IntEn()
* 功能说明: 中断使能
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t it             interrupt type，有效值包括PWM_IT_OVF_UP、PWM_IT_OVF_DOWN、PWM_IT_CMPA_UP、PWM_IT_CMPB_UP、
*                                   PWM_IT_CMPA_DOWN、PWM_IT_CMPB_DOWN 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntEn(PWM_TypeDef * PWMx, uint32_t it)
{
    PWMx->IE |= it;
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntDis()
* 功能说明: 中断禁能
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t it             interrupt type，有效值包括PWM_IT_OVF_UP、PWM_IT_OVF_DOWN、PWM_IT_CMPA_UP、PWM_IT_CMPB_UP、
*                                   PWM_IT_CMPA_DOWN、PWM_IT_CMPB_DOWN 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntDis(PWM_TypeDef * PWMx, uint32_t it)
{
    PWMx->IE &= ~it;
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntClr()
* 功能说明:中断标志清除
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t it             interrupt type，有效值包括PWM_IT_OVF_UP、PWM_IT_OVF_DOWN、PWM_IT_CMPA_UP、PWM_IT_CMPB_UP、
*                                   PWM_IT_CMPA_DOWN、PWM_IT_CMPB_DOWN 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_IntClr(PWM_TypeDef * PWMx, uint32_t it)
{
    PWMx->IF = it;
}

/******************************************************************************************************************************************
* 函数名称: PWM_IntStat()
* 功能说明: 中断标志查询
* 输    入: PWM_TypeDef * PWMx        指定要被设置的PWM，有效值包括PWM0、PWM1、PWM2、PWM3、PWM4
*           uint32_t it             interrupt type，有效值包括PWM_IT_OVF_UP、PWM_IT_OVF_DOWN、PWM_IT_CMPA_UP、PWM_IT_CMPB_UP、
*                                   PWM_IT_CMPA_DOWN、PWM_IT_CMPB_DOWN 及其“或”
* 输    出: uint32_t              0 中断标志未置起   非0 中断标志已置起
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWM_IntStat(PWM_TypeDef * PWMx, uint32_t it)
{
    return (PWMx->IF & it);
}

/******************************************************************************************************************************************
* 函数名称: PWM_BrkIntEn()
* 功能说明: 刹车中断使能
* 输    入: uint32_t brkit            brake interrupt type，有效值包括 PWM_BRKIT_BRK0、PWM_BRKIT_BRK0、PWM_BRKIT_BRK0 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_BrkIntEn(uint32_t brkit)
{
    PWMG->BRKIE |= brkit;
}

/******************************************************************************************************************************************
* 函数名称: PWM_BrkIntDis()
* 功能说明: 刹车中断禁能
* 输    入: uint32_t brkit            brake interrupt type，有效值包括 PWM_BRKIT_BRK0、PWM_BRKIT_BRK0、PWM_BRKIT_BRK0 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_BrkIntDis(uint32_t brkit)
{
    PWMG->BRKIE &= ~brkit;
}

/******************************************************************************************************************************************
* 函数名称: PWM_BrkIntClr()
* 功能说明:中断标志清除
* 输    入: uint32_t brkit            brake interrupt type，有效值包括 PWM_BRKIT_BRK0、PWM_BRKIT_BRK0、PWM_BRKIT_BRK0 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWM_BrkIntClr(uint32_t brkit)
{
    PWMG->BRKIF = brkit;
}

/******************************************************************************************************************************************
* 函数名称: PWM_BrkIntStat()
* 功能说明: 刹车中断标志查询
* 输    入: uint32_t brkit            brake interrupt type，有效值包括 PWM_BRKIT_BRK0、PWM_BRKIT_BRK0、PWM_BRKIT_BRK0 及其“或”
* 输    出: uint32_t              0 中断标志未置起   非0 中断标志已置起
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWM_BrkIntStat(uint32_t brkit)
{
    return (PWMG->BRKIF & brkit);
}
