/****************************************************************************************************************************************** 
* 文件名称:	SWM320_flash.c
* 功能说明:	使用芯片的IAP功能将片上Flash模拟成EEPROM来保存数据，掉电后不丢失
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0		2017年10月25日
* 升级记录: 
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
#include "SWM320_flash.h"


IAP_Cache_Reset_t IAP_Cache_Reset = (IAP_Cache_Reset_t)0x11000601;
IAP_Flash_Param_t IAP_Flash_Param = (IAP_Flash_Param_t)0x11000681;
IAP_Flash_Erase_t IAP_Flash_Erase = (IAP_Flash_Erase_t)0x11000781;
IAP_Flash_Write_t IAP_Flash_Write = (IAP_Flash_Write_t)0x11000801;


/****************************************************************************************************************************************** 
* 函数名称: FLASH_Erase()
* 功能说明:	片内Flash擦除
* 输    入: uint32_t addr			擦除地址，扇区大小为4K Byte
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Erase(uint32_t addr)
{	
	__disable_irq();
	
	IAP_Flash_Erase(addr / 0x1000);
	
	IAP_Cache_Reset();
	
	__enable_irq();
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Write()
* 功能说明:	片内Flash写入
* 输    入: uint32_t addr			写入地址
*			uint32_t buff[]			要写入的数据
*			uint32_t count			要写入数据的个数，以字为单位，且必须是4的整数倍，即最少写入4个字
* 输    出: 无
* 注意事项: 写入数据个数必须是4的整数倍，即最少写入4个字
******************************************************************************************************************************************/
void FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t count)
{
	__disable_irq();
	
	IAP_Flash_Write(addr, (uint32_t)buff, count/4);
	
	IAP_Cache_Reset();
	
	__enable_irq();
}

/****************************************************************************************************************************************** 
* 函数名称: Flash_Param_at_120MHz()
* 功能说明:	将Flash参数设置成120MHz主频下运行时所需的参数
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void Flash_Param_at_120MHz(void)
{
	__disable_irq();
	
	IAP_Flash_Param(0x48a, 0xabfc7a6e);
	
	__enable_irq();
}
