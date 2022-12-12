/******************************************************************************************************************************************
* 文件名称: SWM341_exti.c
* 功能说明: SWM341单片机的外部中断功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0      2016年1月30日
* 升级记录:
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
#include "SWM341_exti.h"

/******************************************************************************************************************************************
* 函数名称: EXTI_Init()
* 功能说明: 指定引脚外部中断初始化
* 输    入: GPIO_TypeDef * GPIOx  指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n         指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t mode      有效值有EXTI_FALL_EDGE、EXTI_RISE_EDGE、EXTI_BOTH_EDGE、EXTI_LOW_LEVEL、EXTI_HIGH_LEVEL
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void EXTI_Init(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t mode)
{
    EXTI_Close(GPIOx, n);           //配置关键寄存器前先关闭

    if(mode & 0x10)
    {
        GPIOx->INTLVLTRG |= (0x01 << n);            //电平触发

        if(mode & 0x01)
            GPIOx->INTRISEEN |= (0x01 << n);                //高电平触发
        else
            GPIOx->INTRISEEN &= ~(0x01 << n);               //低电平触发
    }
    else
    {
        GPIOx->INTLVLTRG &= ~(0x01 << n);           //边沿触发

        if(mode & 0x02)
        {
            GPIOx->INTBE |= (0x01 << n);                //双边沿触发
        }
        else
        {
            GPIOx->INTBE &= ~(0x01 << n);               //单边沿触发

            if(mode & 0x01)
                GPIOx->INTRISEEN |= (0x01 << n);            //上升沿触发
            else
                GPIOx->INTRISEEN &= ~(0x01 << n);           //下降沿触发
        }
    }

    GPIOx->INTCLR = (1 << n);       //清除掉因为模式配置可能产生的中断
}

/******************************************************************************************************************************************
* 函数名称: EXTI_Open()
* 功能说明: 指定引脚外部中断打开（即使能）
* 输    入: GPIO_TypeDef * GPIOx  指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n         指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void EXTI_Open(GPIO_TypeDef * GPIOx, uint32_t n)
{
    GPIOx->INTEN |= (0x01 << n);
}

/******************************************************************************************************************************************
* 函数名称: EXTI_Close()
* 功能说明: 指定引脚外部中断关闭（即禁能）
* 输    入: GPIO_TypeDef * GPIOx  指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n         指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void EXTI_Close(GPIO_TypeDef * GPIOx, uint32_t n)
{
    GPIOx->INTEN &= ~(0x01 << n);
}

/******************************************************************************************************************************************
* 函数名称: EXTI_State()
* 功能说明: 指定引脚是否触发了中断
* 输    入: GPIO_TypeDef * GPIOx  指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n         指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: uint32_t  1 此引脚触发了中断    0 此引脚未触发中断
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t EXTI_State(GPIO_TypeDef * GPIOx, uint32_t n)
{
    return (GPIOx->INTSTAT >> n) & 0x01;
}

/******************************************************************************************************************************************
* 函数名称: EXTI_RawState()
* 功能说明: 指定引脚是否满足过/了中断触发条件，当此中断关闭时可通过调用此函数以查询的方式检测引脚上是否满足过/了中断触发条件
* 输    入: GPIO_TypeDef * GPIOx  指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n         指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: uint32_t  1 此引脚满足过/了中断触发条件    0 此引脚未满足过/了中断触发条件
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t EXTI_RawState(GPIO_TypeDef * GPIOx, uint32_t n)
{
    return (GPIOx->INTRAWSTAT >> n) & 0x01;
}

/******************************************************************************************************************************************
* 函数名称: EXTI_Clear()
* 功能说明: 指定引脚外部中断清除（即清除中断标志，以免再次进入此中断）
* 输    入: GPIO_TypeDef * GPIOx  指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC、GPIOD、GPIOE、GPIOM、GPION
*           uint32_t n         指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 只能清除边沿触发中断的标志，电平触发中断的标志无法清除，只能在引脚电平不符合中断触发条件后硬件自动清除
******************************************************************************************************************************************/
void EXTI_Clear(GPIO_TypeDef * GPIOx, uint32_t n)
{
    GPIOx->INTCLR = (0x01 << n);
}
