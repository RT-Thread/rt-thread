/******************************************************************************************************************************************
* 文件名称: SWM341_flash.c
* 功能说明: 使用芯片的IAP功能将片上Flash模拟成EEPROM来保存数据，掉电后不丢失
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0      2016年1月30日
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
#include "SWM341.h"
#include "SWM341_flash.h"


const IAP_Cache_Reset_t IAP_Cache_Reset = (IAP_Cache_Reset_t)0x11000401;
const IAP_Flash_Param_t IAP_Flash_Param = (IAP_Flash_Param_t)0x11000431;
const IAP_Flash_Erase_t IAP_Flash_Erase = (IAP_Flash_Erase_t)0x11000471;
const IAP_Flash_Write_t IAP_Flash_Write = (IAP_Flash_Write_t)0x110004C1;


/******************************************************************************************************************************************
* 函数名称: FLASH_Erase()
* 功能说明: FLASH扇区擦除，每个扇区4K字节
* 输    入: uint32_t addr     要擦除扇区的地址，必须4K对齐，即addr%4096 == 0
* 输    出: uint32_t          FLASH_RES_OK、FLASH_RES_TO、FLASH_RES_ERR
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t FLASH_Erase(uint32_t addr)
{
    if(addr % 4096 != 0) return FLASH_RES_ERR;

    __disable_irq();

    IAP_Flash_Erase(addr/4096, 0x0B11FFAC);

    IAP_Cache_Reset((FMC->CACHE | FMC_CACHE_CCLR_Msk), 0x0B11FFAC); // Cache Clear

    __enable_irq();

    return FLASH_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: FLASH_Write()
* 功能说明: FLASH数据写入
* 输    入: uint32_t addr     数据要写入到Flash中的地址，四字对齐
*           uint32_t buff[]     要写入Flash中的数据
*           uint32_t count      要写入数据的个数，以字为单位，且必须是4的整数倍，即最少写入4个字
* 输    出: uint32_t          FLASH_RES_OK、FLASH_RES_TO、FLASH_RES_ERR
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t count)
{
    if(addr % 16 != 0) return FLASH_RES_ERR;
    if(count % 4 != 0) return FLASH_RES_ERR;

    __disable_irq();

    IAP_Flash_Write(addr, (uint32_t)buff, count/4, 0x0B11FFAC);

    IAP_Cache_Reset((FMC->CACHE | FMC_CACHE_CCLR_Msk), 0x0B11FFAC); // Cache Clear

    __enable_irq();

    return FLASH_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: Flash_Param_at_xMHz()
* 功能说明: 将Flash参数设置成xMHz主频下运行时所需的参数
* 输    入: uint32_t x        取值30、40、80、120、150
* 输    出: 无
* 注意事项: 系统主频越高，Flash访问等待周期越长
******************************************************************************************************************************************/
void Flash_Param_at_xMHz(uint32_t x)
{
//    __disable_irq();
    switch(x)
    {
        case 30:
            IAP_Flash_Param(0x8949, 0x0FA1, 0x0B11FFAC);
            break;

        case 40:
            IAP_Flash_Param(0x8A49, 0x14A9, 0x0B11FFAC);
            break;

        case 80:
            IAP_Flash_Param(0xD349, 0x294A, 0x0B11FFAC);
            break;

        case 120:
            IAP_Flash_Param(0x11C89, 0x3D6B, 0x0B11FFAC);
            break;

        case 150:
        default:
            IAP_Flash_Param(0x16589, 0x4C74, 0x0B11FFAC);
            break;
    }
//    __enable_irq();
}
