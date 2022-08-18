/******************************************************************************************************************************************
* 文件名称: SWM320_port.c
* 功能说明: SWM320单片机的端口引脚功能选择库函数
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
#include "SWM320_port.h"


/******************************************************************************************************************************************
* 函数名称: PORT_Init()
* 功能说明: 端口引脚功能选择，可用的功能见"SWM320_port.h"文件
* 输    入: uint32_t PORTx            指定PORT端口，有效值包括PORTA、PORTB、PORTC、PORTM、PORTN、PORTP
*           uint32_t n              指定PORT引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN22、PIN23
*           uint32_t func           指定端口引脚要设定的功能，其可取值见"SWM320_port.h"文件
*           uint32_t digit_in_en    数字输入使能
* 输    出: 无
* 注意事项: 当引脚标号n为偶数时，func取值只能是FUNMUX0开头的，如FUNMUX0_UART0_RXD
*           当引脚标号n为奇数时，func取值只能是FUNMUX1开头的，如FUNMUX1_UART0_TXD
******************************************************************************************************************************************/
void PORT_Init(uint32_t PORTx, uint32_t n, uint32_t func, uint32_t digit_in_en)
{
    switch((uint32_t)PORTx)
    {
        case ((uint32_t)PORTA):
            if(func > 99)
            {
                if(n < PIN6)
                {
                    PORT->PORTA_MUX0 &= ~(0x1F << (n*5));
                    PORT->PORTA_MUX0 |= (func-100) << (n*5);
                }
                else if(n < PIN12)
                {
                    PORT->PORTA_MUX1 &= ~(0x1F << ((n-6)*5));
                    PORT->PORTA_MUX1 |= (func-100) << ((n-6)*5);
                }
            }

            PORT->PORTA_SEL &= ~(0x03 << (n*2));
            PORT->PORTA_SEL |= (func > 99 ? 1 : func) << (n*2);

            PORT->PORTA_INEN &= ~(0x01 << n);
            PORT->PORTA_INEN |= (digit_in_en << n);
            break;

        case ((uint32_t)PORTB):
            if(func > 99)
            {
                if(n < PIN6)
                {
                    PORT->PORTB_MUX0 &= ~(0x1F << (n*5));
                    PORT->PORTB_MUX0 |= (func-100) << (n*5);
                }
                else if(n < PIN12)
                {
                    PORT->PORTB_MUX1 &= ~(0x1F << ((n-6)*5));
                    PORT->PORTB_MUX1 |= (func-100) << ((n-6)*5);
                }
            }

            PORT->PORTB_SEL &= ~(0x03 << (n*2));
            PORT->PORTB_SEL |= (func > 99 ? 1 : func) << (n*2);

            PORT->PORTB_INEN &= ~(0x01 << n);
            PORT->PORTB_INEN |= (digit_in_en << n);
            break;

        case ((uint32_t)PORTC):
            if(func > 99)
            {
                if(n < PIN6)
                {
                    PORT->PORTC_MUX0 &= ~(0x1F << (n*5));
                    PORT->PORTC_MUX0 |= (func-100) << (n*5);
                }
                else if(n < PIN12)
                {
                    PORT->PORTC_MUX1 &= ~(0x1F << ((n-6)*5));
                    PORT->PORTC_MUX1 |= (func-100) << ((n-6)*5);
                }
            }

            PORT->PORTC_SEL &= ~(0x03 << (n*2));
            PORT->PORTC_SEL |= (func > 99 ? 1 : func) << (n*2);

            PORT->PORTC_INEN &= ~(0x01 << n);
            PORT->PORTC_INEN |= (digit_in_en << n);
            break;

        case ((uint32_t)PORTM):
            if(func > 99)
            {
                if(n < PIN6)
                {
                    PORT->PORTM_MUX0 &= ~(0x1F << (n*5));
                    PORT->PORTM_MUX0 |= (func-100) << (n*5);
                }
                else if(n < PIN12)
                {
                    PORT->PORTM_MUX1 &= ~(0x1F << ((n-6)*5));
                    PORT->PORTM_MUX1 |= (func-100) << ((n-6)*5);
                }
                else if(n < PIN18)
                {
                    PORT->PORTM_MUX2 &= ~(0x1F << ((n-12)*5));
                    PORT->PORTM_MUX2 |= (func-100) << ((n-12)*5);
                }
                else if(n < PIN24)
                {
                    PORT->PORTM_MUX3 &= ~(0x1F << ((n-18)*5));
                    PORT->PORTM_MUX3 |= (func-100) << ((n-18)*5);
                }
            }

            if(n < 16)
            {
                PORT->PORTM_SEL0 &= ~(0x03 << (n*2));
                PORT->PORTM_SEL0 |= (func > 99 ? 1 : func) << (n*2);
            }
            else
            {
                PORT->PORTM_SEL1 &= ~(0x03 << ((n-16)*2));
                PORT->PORTM_SEL1 |= (func > 99 ? 1 : func) << ((n-16)*2);
            }

            PORT->PORTM_INEN &= ~(0x01 << n);
            PORT->PORTM_INEN |= (digit_in_en << n);
            break;

        case ((uint32_t)PORTN):
            if(func > 99)
            {
                if(n < PIN6)
                {
                    PORT->PORTN_MUX0 &= ~(0x1F << (n*5));
                    PORT->PORTN_MUX0 |= (func-100) << (n*5);
                }
                else if(n < PIN12)
                {
                    PORT->PORTN_MUX1 &= ~(0x1F << ((n-6)*5));
                    PORT->PORTN_MUX1 |= (func-100) << ((n-6)*5);
                }
                else if(n < PIN18)
                {
                    PORT->PORTN_MUX2 &= ~(0x1F << ((n-12)*5));
                    PORT->PORTN_MUX2 |= (func-100) << ((n-12)*5);
                }
            }

            if(n < 16)
            {
                PORT->PORTN_SEL0 &= ~(0x03 << (n*2));
                PORT->PORTN_SEL0 |= (func > 99 ? 1 : func) << (n*2);
            }
            else
            {
                PORT->PORTN_SEL1 &= ~(0x03 << ((n-16)*2));
                PORT->PORTN_SEL1 |= (func > 99 ? 1 : func) << ((n-16)*2);
            }

            PORT->PORTN_INEN &= ~(0x01 << n);
            PORT->PORTN_INEN |= (digit_in_en << n);
            break;

        case ((uint32_t)PORTP):
            if(func > 99)
            {
                if(n < PIN6)
                {
                    PORT->PORTP_MUX0 &= ~(0x1F << (n*5));
                    PORT->PORTP_MUX0 |= (func-100) << (n*5);
                }
                else if(n < PIN12)
                {
                    PORT->PORTP_MUX1 &= ~(0x1F << ((n-6)*5));
                    PORT->PORTP_MUX1 |= (func-100) << ((n-6)*5);
                }
                else if(n < PIN18)
                {
                    PORT->PORTP_MUX2 &= ~(0x1F << ((n-12)*5));
                    PORT->PORTP_MUX2 |= (func-100) << ((n-12)*5);
                }
                else if(n < PIN24)
                {
                    PORT->PORTP_MUX3 &= ~(0x1F << ((n-18)*5));
                    PORT->PORTP_MUX3 |= (func-100) << ((n-18)*5);
                }
            }

            if(n < 16)
            {
                PORT->PORTP_SEL0 &= ~(0x03 << (n*2));
                PORT->PORTP_SEL0 |= (func > 99 ? 1 : func) << (n*2);
            }
            else
            {
                PORT->PORTP_SEL1 &= ~(0x03 << ((n-16)*2));
                PORT->PORTP_SEL1 |= (func > 99 ? 1 : func) << ((n-16)*2);
            }

            PORT->PORTP_INEN &= ~(0x01 << n);
            PORT->PORTP_INEN |= (digit_in_en << n);
            break;
    }
}
