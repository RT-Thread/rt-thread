/******************************************************************************************************************************************
* 文件名称: SWM320_gpio.c
* 功能说明: SWM320单片机的通用输入输出功能驱动库
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
#include "SWM320_gpio.h"


/******************************************************************************************************************************************
* 函数名称: GPIO_Init()
* 功能说明: 引脚初始化，包含引脚方向、上拉电阻、下拉电阻
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
*           uint32_t dir           引脚方向，0 输入        1 输出
*           uint32_t pull_up       上拉电阻，0 关闭上拉    1 开启上拉
*           uint32_t pull_down     下拉电阻，0 关闭下拉    1 开启下拉
* 输    出: 无
* 注意事项: GPIOA、GPIOC、GPIOM、GPIOP只有上拉，GPIOB、GPION只有下拉（PN0、PN1、PN2三个引脚有上拉没下拉）
******************************************************************************************************************************************/
void GPIO_Init(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t dir, uint32_t pull_up, uint32_t pull_down)
{
    switch((uint32_t)GPIOx)
    {
    case ((uint32_t)GPIOA):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOA_Pos);

        PORT_Init(PORTA, n, 0, 1);          //PORTA.PINn引脚配置为GPIO功能，数字输入开启
        if(dir == 1)
        {
            GPIOA->DIR |= (0x01 << n);
        }
        else
        {
            GPIOA->DIR &= ~(0x01 << n);
        }

        if(pull_up == 1)
            PORT->PORTA_PULLU |= (0x01 << n);
        else
            PORT->PORTA_PULLU &= ~(0x01 << n);
        break;

    case ((uint32_t)GPIOB):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOB_Pos);

        PORT_Init(PORTB, n, 0, 1);          //PORTB.PINn引脚配置为GPIO功能，数字输入开启
        if(dir == 1)
        {
            GPIOB->DIR |= (0x01 << n);
        }
        else
        {
            GPIOB->DIR &= ~(0x01 << n);
        }

        if(pull_down == 1)
            PORT->PORTB_PULLD |= (0x01 << n);
        else
            PORT->PORTB_PULLD &= ~(0x01 << n);
        break;

    case ((uint32_t)GPIOC):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOC_Pos);

        PORT_Init(PORTC, n, 0, 1);          //PORTC.PINn引脚配置为GPIO功能，数字输入开启
        if(dir == 1)
        {
            GPIOC->DIR |= (0x01 << n);
        }
        else
        {
            GPIOC->DIR &= ~(0x01 << n);
        }

        if(pull_up == 1)
            PORT->PORTC_PULLU |= (0x01 << n);
        else
            PORT->PORTC_PULLU &= ~(0x01 << n);
        break;

    case ((uint32_t)GPIOM):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOM_Pos);

        PORT_Init(PORTM, n, 0, 1);          //PORTM.PINn引脚配置为GPIO功能，数字输入开启
        if(dir == 1)
        {
            GPIOM->DIR |= (0x01 << n);
        }
        else
        {
            GPIOM->DIR &= ~(0x01 << n);
        }

        if(pull_up == 1)
            PORT->PORTM_PULLU |= (0x01 << n);
        else
            PORT->PORTM_PULLU &= ~(0x01 << n);
        break;

    case ((uint32_t)GPION):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_GPION_Pos);

        PORT_Init(PORTN, n, 0, 1);          //PORTN.PINn引脚配置为GPIO功能，数字输入开启
        if(dir == 1)
        {
            GPION->DIR |= (0x01 << n);
        }
        else
        {
            GPION->DIR &= ~(0x01 << n);
        }

        if(pull_down == 1)
            PORT->PORTN_PULLD |= (0x01 << n);
        else
            PORT->PORTN_PULLD &= ~(0x01 << n);
        break;

    case ((uint32_t)GPIOP):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOP_Pos);

        PORT_Init(PORTP, n, 0, 1);          //PORTP.PINn引脚配置为GPIO功能，数字输入开启
        if(dir == 1)
        {
            GPIOP->DIR |= (0x01 << n);
        }
        else
        {
            GPIOP->DIR &= ~(0x01 << n);
        }

        if(pull_up == 1)
            PORT->PORTP_PULLU |= (0x01 << n);
        else
            PORT->PORTP_PULLU &= ~(0x01 << n);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: GPIO_SetBit()
* 功能说明: 将参数指定的引脚电平置高
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    *((volatile uint32_t *)(0x42000000 + ((uint32_t)&GPIOx->DATA - 0x40000000)*32 + n*4)) = 1;
}

/******************************************************************************************************************************************
* 函数名称: GPIO_ClrBit()
* 功能说明: 将参数指定的引脚电平置低
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    *((volatile uint32_t *)(0x42000000 + ((uint32_t)&GPIOx->DATA - 0x40000000)*32 + n*4)) = 0;
}

/******************************************************************************************************************************************
* 函数名称: GPIO_InvBit()
* 功能说明: 将参数指定的引脚电平反转
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    *((volatile uint32_t *)(0x42000000 + ((uint32_t)&GPIOx->DATA - 0x40000000)*32 + n*4)) = 1 - *((volatile uint32_t *)(0x42000000 + ((uint32_t)&GPIOx->DATA - 0x40000000)*32 + n*4));
}

/******************************************************************************************************************************************
* 函数名称: GPIO_GetBit()
* 功能说明: 读取参数指定的引脚的电平状态
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
* 输    出: 参数指定的引脚的电平状态  0 低电平   1 高电平
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
    return ((GPIOx->DATA >> n) & 0x01);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_SetBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置高
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
*           uint32_t w             指定要将引脚电平置高的引脚的个数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFFFF >> (24 - w);

    GPIOx->DATA |= (bits << n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_ClrBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置低
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
*           uint32_t w             指定要将引脚电平置低的引脚的个数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_ClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFFFF >> (24 - w);

    GPIOx->DATA &= ~(bits << n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_InvBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平反转
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
*           uint32_t w             指定要将引脚电平反转的引脚的个数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_InvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFFFF >> (24 - w);

    GPIOx->DATA ^= (bits << n);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_GetBits()
* 功能说明: 读取参数指定的从n开始的w位连续引脚的电平状态
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOM、GPION、GPIOP
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
*           uint32_t w             指定要将引脚电平置高的引脚的个数
* 输    出: 参数指定的从n开始的w位连续引脚的电平状态 0 低电平   1 高电平
*           返回值的第0位表示引脚n的电平状态、返回值的第1位表示引脚n+1的电平状态... ...返回值的第w位表示引脚n+w的电平状态
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t GPIO_GetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFFFF >> (24 - w);

    return ((GPIOx->DATA >> n) & bits);
}

/******************************************************************************************************************************************
* 函数名称: GPIO_AtomicSetBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置高，确保引脚”读-改-写“操作的原子性（不被中断ISR打断）
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w      指定要将引脚电平置高的引脚的个数
* 输    出: 无
* 注意事项: 当GPIOx的16个引脚中，有些在主循环中操作，有些在中断ISR中操作时，GPIOx的引脚必须都用GPIO_Atomic类型函数操作
******************************************************************************************************************************************/
void GPIO_AtomicSetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFFFF >> (24 - w);

    __disable_irq();
    GPIOx->DATA |= (bits << n);
    __enable_irq();
}

/******************************************************************************************************************************************
* 函数名称: GPIO_AtomicClrBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平置低，确保引脚”读-改-写“操作的原子性（不被中断ISR打断）
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平置低的引脚的个数
* 输    出: 无
* 注意事项: 当GPIOx的16个引脚中，有些在主循环中操作，有些在中断ISR中操作时，GPIOx的引脚必须都用GPIO_Atomic类型函数操作
******************************************************************************************************************************************/
void GPIO_AtomicClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFFFF >> (24 - w);

    __disable_irq();
    GPIOx->DATA &= ~(bits << n);
    __enable_irq();
}

/******************************************************************************************************************************************
* 函数名称: GPIO_AtomicInvBits()
* 功能说明: 将参数指定的从n开始的w位连续引脚的电平反转，确保引脚”读-改-写“操作的原子性（不被中断ISR打断）
* 输    入: GPIO_TypeDef * GPIOx      指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD
*           uint32_t n             指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t w             指定要将引脚电平反转的引脚的个数
* 输    出: 无
* 注意事项: 当GPIOx的16个引脚中，有些在主循环中操作，有些在中断ISR中操作时，GPIOx的引脚必须都用GPIO_Atomic类型函数操作
******************************************************************************************************************************************/
void GPIO_AtomicInvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
    uint32_t bits;

    bits = 0xFFFFFF >> (24 - w);

    __disable_irq();
    GPIOx->DATA ^= (bits << n);
    __enable_irq();
}
