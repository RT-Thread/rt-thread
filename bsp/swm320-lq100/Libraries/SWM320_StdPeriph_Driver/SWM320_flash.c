/******************************************************************************************************************************************
* 文件名称: SWM320_flash.c
* 功能说明: 使用芯片的IAP功能将片上Flash模拟成EEPROM来保存数据，掉电后不丢失
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2017年10月25日
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


__attribute__((section("PlaceInRAM")))
static void switchTo80M(void)
{
    uint32_t i;

    for (i = 0; i < 50; i++) __NOP();

    FLASH->CFG0 = 0x4bf;
    FLASH->CFG1 = 0xabfc7a6e;

    for (i = 0; i < 50; i++) __NOP();
}

/******************************************************************************************************************************************
* 函数名称: FLASH_Erase()
* 功能说明: 片内Flash擦除
* 输    入: uint32_t addr           擦除地址
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Erase(uint32_t addr)
{
//  switchTo80M();

    FLASH->ERASE = addr | ((uint32_t)1 << FLASH_ERASE_REQ_Pos);
    while ((FLASH->STAT & FLASH_STAT_ERASE_GOING_Msk) == 0);
    while ((FLASH->STAT & FLASH_STAT_ERASE_GOING_Msk) == 1);

    FLASH->ERASE = 0;

//  switchTo40M();
}

/******************************************************************************************************************************************
* 函数名称: FLASH_Write()
* 功能说明: 片内Flash写入
* 输    入: uint32_t addr           写入地址
*           uint32_t buff[]         要写入的数据
*           uint32_t size           要写入数据的个数，字为单位
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t size)
{
    uint32_t i, j;

    switchTo80M();

    FLASH->CACHE |= (1 << FLASH_CACHE_PROG_Pos);

    for (i = 0; i < size / 4; i++)
    {
        FLASH->ADDR = addr + i * 4 * 4;

        for (j = 0; j < 4; j++)
            FLASH->DATA = buff[i * 4 + j];
        while ((FLASH->STAT & FLASH_STAT_FIFO_EMPTY_Msk) == 0) __NOP();
    }
    if ((size % 4) != 0)
    {
        FLASH->ADDR = addr + i * 4 * 4;

        for (j = 0; j < size % 4; j++)
            FLASH->DATA = buff[i * 4 + j];
        while ((FLASH->STAT & FLASH_STAT_FIFO_EMPTY_Msk) == 0) __NOP();
    }
    while (FLASH->STAT & FLASH_STAT_PROG_GOING_Msk);

    FLASH->CACHE |= (1 << FLASH_CACHE_CLEAR_Pos);
    FLASH->CACHE = 0;

//  switchTo40M();
}
