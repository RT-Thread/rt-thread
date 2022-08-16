/******************************************************************************************************************************************
* 文件名称: SWM341_cordic.c
* 功能说明: SWM341单片机的CORDIC功能驱动库
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
#include "SWM341_cordic.h"


/******************************************************************************************************************************************
* 函数名称: CORDIC_Init()
* 功能说明: CORDIC初始化
* 输    入: CORDIC_TypeDef * CORDICx  指定要被设置的CORDIC，有效值包括CORDIC
* 输    出: 无
* 注意事项: CORDIC模块依赖DIV模块，因为CORDIC_Arctan()要使用硬件除法模块计算参数值
******************************************************************************************************************************************/
void CORDIC_Init(CORDIC_TypeDef * CORDICx)
{
    switch((uint32_t)CORDICx)
    {
    case ((uint32_t)CORDIC):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_CORDIC_Pos);
        break;
    }
}
