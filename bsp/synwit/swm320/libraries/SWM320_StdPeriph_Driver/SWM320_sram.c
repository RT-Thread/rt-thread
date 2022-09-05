/******************************************************************************************************************************************
* 文件名称: SWM320_sram.c
* 功能说明: SWM320单片机的SRAM驱动程序
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
#include "SWM320_sram.h"


/******************************************************************************************************************************************
* 函数名称: SRAM_Init()
* 功能说明: SRAM控制器初始化
* 输    入: SRAM_InitStructure * initStruct    包含 SRAM 控制器相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SRAM_Init(SRAM_InitStructure * initStruct)
{
    uint32_t i;

    // 配置SRAM前需要刷新下SDRAM控制器
    do {
        SYS->CLKEN |=  (1 << SYS_CLKEN_SDRAM_Pos);

        while(SDRAMC->REFDONE == 0);
        SDRAMC->REFRESH &= ~(1 << SDRAMC_REFRESH_EN_Pos);

        for(i = 0; i < 1000; i++) __NOP();
        SYS->CLKEN &= ~(1 << SYS_CLKEN_SDRAM_Pos);
    } while(0);

    SYS->CLKEN |= (1 << SYS_CLKEN_RAMC_Pos);
    for(i = 0; i < 10; i++) __NOP();

    SRAMC->CR = (initStruct->ClkDiv << SRAMC_CR_RWTIME_Pos) |
                (initStruct->DataWidth << SRAMC_CR_BYTEIF_Pos) |
                (0 << SRAMC_CR_HBLBDIS_Pos);    // 使能字节、半字访问
}
