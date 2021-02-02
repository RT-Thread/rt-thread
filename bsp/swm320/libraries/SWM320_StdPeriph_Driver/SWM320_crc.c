/****************************************************************************************************************************************** 
* 文件名称: SWM320_crc.c
* 功能说明:	SWM320单片机的CRC模块驱动库
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项: 
* 版本日期:	V1.1.0		2017年10月25日
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
#include "SWM320_crc.h"


/****************************************************************************************************************************************** 
* 函数名称:	CRC_Init()
* 功能说明:	CRC 初始化
* 输    入: CRC_TypeDef * CRCx	指定要被设置的CRC接口，有效值包括CRC
*			uint32_t mode		工作模式，有效值有：CRC32_IN32、CRC32_IN16、CRC32_IN8、CRC16_IN16、CRC16_IN8
*			uint32_t out_not	输出结果是否取反
*			uint32_t out_rev	输出结果是否翻转
*			uint32_t ini_val	CRC初始值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Init(CRC_TypeDef * CRCx, uint32_t mode, uint32_t out_not, uint32_t out_rev, uint32_t ini_val)
{
	switch((uint32_t)CRCx)
	{
	case ((uint32_t)CRC):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_CRC_Pos);
		break;
	}
	
	CRCx->CR = (1 << CRC_CR_EN_Pos) |
			   (mode << CRC_CR_CRC16_Pos) |
			   (out_not << CRC_CR_ONOT_Pos) |
			   (out_rev << CRC_CR_OREV_Pos);
	
	CRCx->INIVAL = ini_val;
}
