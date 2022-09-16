/******************************************************************************************************************************************
* 文件名称: SWM341_crc.c
* 功能说明: SWM341单片机的CRC模块驱动库
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
#include "SWM341_crc.h"


/******************************************************************************************************************************************
* 函数名称: CRC_Init()
* 功能说明: CRC 初始化
* 输    入: CRC_TypeDef * CRCx        指定要被设置的CRC接口，有效值包括CRC
*           CRC_InitStructure * initStruct    包含CRC相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Init(CRC_TypeDef * CRCx, CRC_InitStructure * initStruct)
{
    switch((uint32_t)CRCx)
    {
    case ((uint32_t)CRC):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_CRC_Pos);
        break;
    }

    CRCx->INIVAL = initStruct->init_crc;

    CRCx->CR = (1 << CRC_CR_EN_Pos) |
               (initStruct->Poly << CRC_CR_POLY_Pos) |
               (initStruct->in_width << CRC_CR_IBIT_Pos) |
               (initStruct->in_rev << CRC_CR_IREV_Pos) |
               (initStruct->in_not << CRC_CR_INOT_Pos) |
               (initStruct->out_rev << CRC_CR_OREV_Pos) |
               (initStruct->out_not << CRC_CR_ONOT_Pos);
}


/******************************************************************************************************************************************
* 函数名称: CRC_SetInitVal()
* 功能说明: 设置CRC计算初始值
* 输    入: CRC_TypeDef * CRCx        指定要被设置的CRC接口，有效值包括CRC
*           uint32_t init_crc       CRC计算初始值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_SetInitVal(CRC_TypeDef * CRCx, uint32_t init_crc)
{
    CRCx->INIVAL = init_crc;

    CRCx->CR |= (1 << CRC_CR_EN_Pos);
}
