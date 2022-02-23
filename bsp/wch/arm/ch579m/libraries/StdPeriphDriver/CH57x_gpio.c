/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_gpio.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description
*******************************************************************************/

#include "CH57x_common.h"


/*******************************************************************************
* Function Name  : GPIOA_ModeCfg
* Description    : GPIOA端口引脚模式配置
* Input          : pin:  PA0-PA15
                    GPIO_Pin_0 - GPIO_Pin_15
                   mode:
                    GPIO_ModeIN_Floating  -  浮空输入
                    GPIO_ModeIN_PU        -  上拉输入
                    GPIO_ModeIN_PD        -  下拉输入
                    GPIO_ModeOut_PP_5mA   -  推挽输出最大5mA
                    GPIO_ModeOut_PP_20mA  -  推挽输出最大20mA
* Return         : None
*******************************************************************************/
void GPIOA_ModeCfg( UINT32 pin, GPIOModeTypeDef mode )
{
    switch(mode)
    {
        case GPIO_ModeIN_Floating:
            R32_PA_PD_DRV &= ~pin;
            R32_PA_PU     &= ~pin;
            R32_PA_DIR    &= ~pin;
            break;

        case GPIO_ModeIN_PU:
            R32_PA_PD_DRV &= ~pin;
            R32_PA_PU     |= pin;
            R32_PA_DIR    &= ~pin;
            break;

        case GPIO_ModeIN_PD:
            R32_PA_PD_DRV |= pin;
            R32_PA_PU     &= ~pin;
            R32_PA_DIR    &= ~pin;
            break;

        case GPIO_ModeOut_PP_5mA:
            R32_PA_PD_DRV &= ~pin;
            R32_PA_DIR    |= pin;
            break;

        case GPIO_ModeOut_PP_20mA:
            R32_PA_PD_DRV |= pin;
            R32_PA_DIR    |= pin;
            break;

        default:
            break;
    }
}

/*******************************************************************************
* Function Name  : GPIOB_ModeCfg
* Description    : GPIOB端口引脚模式配置
* Input          : pin:  PB0-PB23
                    GPIO_Pin_0 - GPIO_Pin_23
                   mode:
                    GPIO_ModeIN_Floating  -  浮空输入
                    GPIO_ModeIN_PU        -  上拉输入
                    GPIO_ModeIN_PD        -  下拉输入
                    GPIO_ModeOut_PP_5mA   -  推挽输出最大5mA
                    GPIO_ModeOut_PP_20mA  -  推挽输出最大20mA
* Return         : None
*******************************************************************************/
void GPIOB_ModeCfg( UINT32 pin, GPIOModeTypeDef mode )
{
    switch(mode)
    {
        case GPIO_ModeIN_Floating:
            R32_PB_PD_DRV &= ~pin;
            R32_PB_PU     &= ~pin;
            R32_PB_DIR    &= ~pin;
            break;

        case GPIO_ModeIN_PU:
            R32_PB_PD_DRV &= ~pin;
            R32_PB_PU     |= pin;
            R32_PB_DIR    &= ~pin;
            break;

        case GPIO_ModeIN_PD:
            R32_PB_PD_DRV |= pin;
            R32_PB_PU     &= ~pin;
            R32_PB_DIR    &= ~pin;
            break;

        case GPIO_ModeOut_PP_5mA:
            R32_PB_PD_DRV &= ~pin;
            R32_PB_DIR    |= pin;
            break;

        case GPIO_ModeOut_PP_20mA:
            R32_PB_PD_DRV |= pin;
            R32_PB_DIR    |= pin;
            break;

        default:
            break;
    }
}

/*******************************************************************************
* Function Name  : GPIOA_ITModeCfg
* Description    : GPIOA引脚中断模式配置
* Input          : pin:  PA0-PA15
                    GPIO_Pin_0 - GPIO_Pin_15
                   mode:
                    GPIO_ITMode_LowLevel   -  低电平触发
                    GPIO_ITMode_HighLevel  -  高电平触发
                    GPIO_ITMode_FallEdge   -  下降沿触发
                    GPIO_ITMode_RiseEdge   -  上升沿触发
* Return         : None
*******************************************************************************/
void GPIOA_ITModeCfg( UINT32 pin, GPIOITModeTpDef mode )
{
    switch( mode )
    {
        case GPIO_ITMode_LowLevel:      // 低电平触发
            R16_PA_INT_MODE &= ~pin;
            R32_PA_CLR |= pin;
            break;

        case GPIO_ITMode_HighLevel:     // 高电平触发
            R16_PA_INT_MODE &= ~pin;
            R32_PA_OUT |= pin;
            break;

        case GPIO_ITMode_FallEdge:      // 下降沿触发
            R16_PA_INT_MODE |= pin;
            R32_PA_CLR |= pin;
            break;

        case GPIO_ITMode_RiseEdge:      // 上升沿触发
            R16_PA_INT_MODE |= pin;
            R32_PA_OUT |= pin;
            break;

        default :
            break;
    }
    R16_PA_INT_IF = pin;
    R16_PA_INT_EN |= pin;
}

/*******************************************************************************
* Function Name  : GPIOB_ITModeCfg
* Description    : GPIOB引脚中断模式配置
* Input          : pin:  PB0-PB15
                    GPIO_Pin_0 - GPIO_Pin_15
                   mode:
                    GPIO_ITMode_LowLevel   -  低电平触发
                    GPIO_ITMode_HighLevel  -  高电平触发
                    GPIO_ITMode_FallEdge   -  下降沿触发
                    GPIO_ITMode_RiseEdge   -  上升沿触发
* Return         : None
*******************************************************************************/
void GPIOB_ITModeCfg( UINT32 pin, GPIOITModeTpDef mode )
{
    switch( mode )
    {
        case GPIO_ITMode_LowLevel:      // 低电平触发
            R16_PB_INT_MODE &= ~pin;
            R32_PB_CLR |= pin;
            break;

        case GPIO_ITMode_HighLevel:     // 高电平触发
            R16_PB_INT_MODE &= ~pin;
            R32_PB_OUT |= pin;
            break;

        case GPIO_ITMode_FallEdge:      // 下降沿触发
            R16_PB_INT_MODE |= pin;
            R32_PB_CLR |= pin;
            break;

        case GPIO_ITMode_RiseEdge:      // 上升沿触发
            R16_PB_INT_MODE |= pin;
            R32_PB_OUT |= pin;
            break;

        default :
            break;
    }
    R16_PB_INT_IF = pin;
    R16_PB_INT_EN |= pin;
}


/*******************************************************************************
* Function Name  : GPIOPinRemap
* Description    : 外设功能引脚映射
* Input          : s:
                    ENABLE  - 引脚映射
                    DISABLE - 默认引脚
                   perph:
                    RB_PIN_SPI0   -  SPI0:  PA12/PA13/PA14/PA15 -> PB12/PB13/PB14/PB15
                    RB_PIN_UART3  -  UART3: PA4/PA5 ->  PB20/PB21
                    RB_PIN_UART2  -  UART2: PA6/PA7 ->  PB22/PB23
                    RB_PIN_UART1  -  UART1: PA8/PA9 ->  PB8/PB9
                    RB_PIN_UART0  -  UART0: PB4/PB7 ->  PA15/PA14
                    RB_PIN_TMR3   -  TMR3:  PA2 ->  PB18
                    RB_PIN_TMR2   -  TMR2:  PA11 ->  PB11
                    RB_PIN_TMR1   -  TMR1:  PA10 ->  PB10
                    RB_PIN_TMR0   -  TMR0:  PA3 ->  PB19
* Return         : None
*******************************************************************************/
void GPIOPinRemap( UINT8 s, UINT16 perph )
{
    if( s )     R16_PIN_ALTERNATE |= perph;
    else        R16_PIN_ALTERNATE &= ~perph;
}

/*******************************************************************************
* Function Name  : GPIOAGPPCfg
* Description    : 模拟外设GPIO引脚功能控制
* Input          : s:
                    ENABLE  - 打开模拟外设功能，关闭数字功能
                    DISABLE - 启用数字功能，关闭模拟外设功能
                   perph:
                    RB_PIN_ADC0_1_IE      -  ADC0-1通道
                    RB_PIN_ADC2_3_IE      -  ADC2-3通道
                    RB_PIN_ADC4_5_IE      -  ADC4-5通道
                    RB_PIN_ADC6_7_IE      -  ADC6-7通道
                    RB_PIN_ADC8_9_IE      -  ADC8-9通道
                    RB_PIN_ADC10_11_IE    -  ADC10-11通道
                    RB_PIN_ADC12_13_IE    -  ADC12-13通道
                    RB_PIN_XT32K_IE       -  外部32K引脚
                    RB_PIN_USB_IE         -  USB功能信号引脚
                    RB_PIN_ETH_IE         -  以太网功能信号引脚
                    RB_PIN_SEG0_3_IE      -  LCD控制器SEG0-3驱动引脚
                    RB_PIN_SEG4_7_IE      -  LCD控制器SEG4-7驱动引脚
                    RB_PIN_SEG8_11_IE     -  LCD控制器SEG8-11驱动引脚
                    RB_PIN_SEG12_15_IE    -  LCD控制器SEG12-15驱动引脚
                    RB_PIN_SEG16_19_IE    -  LCD控制器SEG16-19驱动引脚
                    RB_PIN_SEG20_23_IE    -  LCD控制器SEG20-23驱动引脚
* Return         : None
*******************************************************************************/
void GPIOAGPPCfg( UINT8 s, UINT16 perph )
{
    if( s )     R16_PIN_ANALOG_IE |= perph;
    else        R16_PIN_ANALOG_IE &= ~perph;
}
