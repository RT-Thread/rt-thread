/******************************************************************************************************************************************
* 文件名称: SWM341_dac.c
* 功能说明: SWM341单片机的DAC模块驱动库
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
#include "SWM341.h"
#include "SWM341_dac.h"


/******************************************************************************************************************************************
* 函数名称: DAC_Init()
* 功能说明: DAC 初始化
* 输    入: DAC_TypeDef * DACx    指定要被设置的DAC接口，有效值包括DAC
*           uint32_t format     数据格式，可取值DAC_FORMAT_LSB12B、DAC_FORMAT_MSB12B、DAC_FORMAT_8B
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DAC_Init(DAC_TypeDef * DACx, uint32_t format)
{
    switch((uint32_t)DACx)
    {
    case ((uint32_t)DAC):
        SYS->CLKEN1 |= (0x01 << SYS_CLKEN1_DAC_Pos);
        break;
    }

    SYS->DACCR &= ~SYS_DACCR_VRADJ_Msk;
    SYS->DACCR |= ((SYS->BACKUP[2] & 0x1F) << SYS_DACCR_VRADJ_Pos);

    DACx->CR = (format << DAC_CR_DHRFMT_Pos);
}

/******************************************************************************************************************************************
* 函数名称: DAC_Open()
* 功能说明: DAC 开启
* 输    入: DAC_TypeDef * DACx    指定要被设置的DAC接口，有效值包括DAC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DAC_Open(DAC_TypeDef * DACx)
{
    DACx->CR |= (1 << DAC_CR_EN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: DAC_Close()
* 功能说明: DAC 关闭
* 输    入: DAC_TypeDef * DACx    指定要被设置的DAC接口，有效值包括DAC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DAC_Close(DAC_TypeDef * DACx)
{
    DACx->CR &= ~DAC_CR_EN_Msk;
}
