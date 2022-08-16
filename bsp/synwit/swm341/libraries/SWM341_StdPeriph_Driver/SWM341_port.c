/******************************************************************************************************************************************
* 文件名称: SWM341_port.c
* 功能说明: SWM341单片机的端口引脚功能选择库函数
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
#include "SWM341_port.h"


/******************************************************************************************************************************************
* 函数名称: PORT_Init()
* 功能说明: 端口引脚功能选择
* 输    入: PORT_TypeDef * PORTx  指定PORT端口，有效值包括PORTA、PORTB、PORTC、PORTD、PORTE、PORTM、PORTN
*           uint32_t n              指定PORT引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*           uint32_t func           指定端口引脚要设定的功能，其可取值见"SWM201_port.h"文件
*           uint32_t digit_in_en    数字输入使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PORT_Init(PORT_TypeDef * PORTx, uint32_t n, uint32_t func, uint32_t digit_in_en)
{
    if(n < PIN8)
    {
        PORTx->FUNC0 &= ~(0x0F << (n*4));
        PORTx->FUNC0 |=  (func << (n*4));
    }
    else
    {
        PORTx->FUNC1 &= ~(0x0F << ((n-8)*4));
        PORTx->FUNC1 |=  (func << ((n-8)*4));
    }

    if(digit_in_en)  PORTx->INEN |=  (1 << n);
    else             PORTx->INEN &= ~(1 << n);
}
