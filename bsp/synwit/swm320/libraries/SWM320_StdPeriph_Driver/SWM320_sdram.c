/******************************************************************************************************************************************
* 文件名称: SWM320_sdram.c
* 功能说明: SWM320单片机的SDRAM驱动程序
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
#include "SWM320_sdram.h"

/******************************************************************************************************************************************
* 函数名称: SDRAM_Init()
* 功能说明: SDRAM控制器初始化
* 输    入: SDRAM_InitStructure * initStruct    包含 SDRAM 控制器相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SDRAM_Init(SDRAM_InitStructure * initStruct)
{
    uint32_t row_n;

    SYS->CLKEN |= (1 << SYS_CLKEN_SDRAM_Pos);

    SYS->CLKDIV &= ~SYS_CLKDIV_SDRAM_Msk;
    SYS->CLKDIV |= (1 << SYS_CLKDIV_SDRAM_Pos);     //2分频

    SDRAMC->CR0 = (2 << SDRAMC_CR0_BURSTLEN_Pos) |  //2 Burst Length为4
                  (initStruct->CASLatency << SDRAMC_CR0_CASDELAY_Pos);

    SDRAMC->CR1 = (initStruct->CellSize << SDRAMC_CR1_CELLSIZE_Pos) |
                  (initStruct->CellWidth << SDRAMC_CR1_CELL32BIT_Pos) |
                  ((initStruct->CellSize == SDRAM_CELLSIZE_16Mb ? SDRAM_CELLBANK_2 : SDRAM_CELLBANK_4) << SDRAMC_CR1_BANK_Pos) |
                  (0 << SDRAMC_CR1_32BIT_Pos) |
                  (initStruct->TimeTMRD << SDRAMC_CR1_TMRD_Pos) |
                  (initStruct->TimeTRRD << SDRAMC_CR1_TRRD_Pos) |
                  (initStruct->TimeTRAS << SDRAMC_CR1_TRAS_Pos) |
                  (initStruct->TimeTRC << SDRAMC_CR1_TRC_Pos) |
                  (initStruct->TimeTRCD << SDRAMC_CR1_TRCD_Pos) |
                  (initStruct->TimeTRP << SDRAMC_CR1_TRP_Pos);

    SDRAMC->LATCH = 0x02;

    switch(initStruct->CellSize)
    {
    case SDRAM_CELLSIZE_16Mb:  row_n = 11; break;
    case SDRAM_CELLSIZE_64Mb:  row_n = 12; break;
    case SDRAM_CELLSIZE_128Mb: row_n = 12; break;
    case SDRAM_CELLSIZE_256Mb: row_n = 13; break;
    default:                   row_n = 13; break;
    }

    SDRAMC->REFRESH = (1 << SDRAMC_REFRESH_EN_Pos) |
                      (((SystemCoreClock/2)/1000 * initStruct->RefreshTime / (1 << row_n)) << SDRAMC_REFRESH_RATE_Pos);

    while(SDRAMC->REFDONE == 0);
}

/******************************************************************************************************************************************
* 函数名称: SDRAM_Enable()
* 功能说明: SDRAM使能，使能后可读写SDRAM
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SDRAM_Enable(void)
{
    uint32_t i;

    SYS->CLKEN |= (1 << SYS_CLKEN_SDRAM_Pos);
    SDRAMC->REFRESH |= (1 << SDRAMC_REFRESH_EN_Pos);

    for(i = 0; i < 100; i++) __NOP();
}

/******************************************************************************************************************************************
* 函数名称: SDRAM_Disable()
* 功能说明: SDRAM禁能，禁能后SDRAM颗粒进入低功耗模式、并自刷新，不可读写
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SDRAM_Disable(void)
{
    uint32_t i;

    SYS->CLKEN |= (1 << SYS_CLKEN_SDRAM_Pos);
    SDRAMC->REFRESH &= ~(1 << SDRAMC_REFRESH_EN_Pos);

    for(i = 0; i < 100; i++) __NOP();
}
