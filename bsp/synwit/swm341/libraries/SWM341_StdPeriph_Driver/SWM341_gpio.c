/******************************************************************************************************************************************
* 文件名称: SWM341_gpio.c
* 功能说明: SWM341单片机的通用输入输出功能驱动库
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
#include "SWM341_gpio.h"


/******************************************************************************************************************************************
* 函数名称: GPIO_Init()
* 功能说明: 引脚初始化，包含引脚方向、上拉、下拉、开漏
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t dir           引脚方向，0 输入        1 输出
*           uint32_t pull_up       上拉使能
*           uint32_t pull_down     下拉使能
*           uint32_t open_drain    开漏使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_Init(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t dir, uint32_t pull_up, uint32_t pull_down, uint32_t open_drain)
{
    PORT_TypeDef * PORTx = PORTA;

    switch((uint32_t)GPIOx)
    {
    case ((uint32_t)GPIOA):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOA_Pos);

        PORTx = PORTA;
        break;

    case ((uint32_t)GPIOB):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOB_Pos);

        PORTx = PORTB;
        break;

    case ((uint32_t)GPIOC):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOC_Pos);

        PORTx = PORTC;
        break;

    case ((uint32_t)GPIOD):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOD_Pos);

        PORTx = PORTD;
        break;

    case ((uint32_t)GPIOE):
        SYS->CLKEN1 |= (0x01 << SYS_CLKEN1_GPIOE_Pos);

        PORTx = PORTE;
        break;

    case ((uint32_t)GPIOM):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOM_Pos);

        PORTx = PORTM;
        break;

    case ((uint32_t)GPION):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPION_Pos);

        PORTx = PORTN;
        break;
    }

    PORT_Init(PORTx, n, 0, 1);          //PORTx.PINn引脚配置为GPIO功能，数字输入开启
    if(dir == 1)
    {
        GPIOx->DIR |= (0x01 << n);
    }
    else
    {
        GPIOx->DIR &= ~(0x01 << n);
    }

    if(pull_up == 1)     PORTx->PULLU |=  (1 << n);
    else                 PORTx->PULLU &= ~(1 << n);
    if(pull_down == 1)   PORTx->PULLD |=  (1 << n);
    else                 PORTx->PULLD &= ~(1 << n);
    if(open_drain == 1)  PORTx->OPEND |=  (1 << n);
    else                 PORTx->OPEND &= ~(1 << n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_SetBit()
* 功能说明: 将参数指定的引脚电平置高
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    *(&GPIOx->DATAPIN0 + n) = 1;
}

/******************************************************************************************************************************************
* 函数名称: GPIO_ClrBit()
* 功能说明: 将参数指定的引脚电平置低
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    *(&GPIOx->DATAPIN0 + n) = 0;
}

/******************************************************************************************************************************************
* 函数名称: GPIO_InvBit()
* 功能说明: 将参数指定的引脚电平反转
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    *(&GPIOx->DATAPIN0 + n) = 1 - *(&GPIOx->DATAPIN0 + n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_GetBit()
* 功能说明: 读取参数指定的引脚的电平状态
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 参数指定的引脚的电平状态  0 低电平   1 高电平
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    return *(&GPIOx->DATAPIN0 + n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_SetBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置高
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平置高的引脚的个数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFF >> (16 - w);

    GPIOx->ODR |= (bits << n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_ClrBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置低
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平置低的引脚的个数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_ClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFF >> (16 - w);

    GPIOx->ODR &= ~(bits << n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_InvBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平反转
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平反转的引脚的个数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_InvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFF >> (16 - w);

    GPIOx->ODR ^= (bits << n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_GetBits()
* 功能说明: 读取参数指定的从n开始的w位连续引脚的电平状态
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平置高的引脚的个数
* 输    出: 参数指定的从n开始的w位连续引脚的电平状态 0 低电平   1 高电平
*           返回值的第0位表示引脚n的电平状态、返回值的第1位表示引脚n+1的电平状态... ...返回值的第w位表示引脚n+w的电平状态
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t GPIO_GetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFF >> (16 - w);

    return ((GPIOx->IDR >> n) & bits);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_AtomicSetBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置高，确保引脚”读-改-写“操作的原子性（不被中断ISR打断）
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w      指定要将引脚电平置高的引脚的个数
* 输    出: 无
* 注意事项: 当GPIOx的16个引脚中，有些在主循环中操作，有些在中断ISR中操作时，GPIOx的引脚必须都用GPIO_Atomic类型函数操作
******************************************************************************************************************************************/
void GPIO_AtomicSetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFF >> (16 - w);

    __disable_irq();
    GPIOx->ODR |= (bits << n);
    __enable_irq();
}

/******************************************************************************************************************************************
* 函数名称: GPIO_AtomicClrBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置低，确保引脚”读-改-写“操作的原子性（不被中断ISR打断）
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平置低的引脚的个数
* 输    出: 无
* 注意事项: 当GPIOx的16个引脚中，有些在主循环中操作，有些在中断ISR中操作时，GPIOx的引脚必须都用GPIO_Atomic类型函数操作
******************************************************************************************************************************************/
void GPIO_AtomicClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFF >> (16 - w);

    __disable_irq();
    GPIOx->ODR &= ~(bits << n);
    __enable_irq();
}

/******************************************************************************************************************************************
* 函数名称: GPIO_AtomicInvBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平反转，确保引脚”读-改-写“操作的原子性（不被中断ISR打断）
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平反转的引脚的个数
* 输    出: 无
* 注意事项: 当GPIOx的16个引脚中，有些在主循环中操作，有些在中断ISR中操作时，GPIOx的引脚必须都用GPIO_Atomic类型函数操作
******************************************************************************************************************************************/
void GPIO_AtomicInvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFF >> (16 - w);

    __disable_irq();
    GPIOx->ODR ^= (bits << n);
    __enable_irq();
}
