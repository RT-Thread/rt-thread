/******************************************************************************************************************************************
* 文件名称: SWM341_sdram.c
* 功能说明: SWM341单片机的SDRAM驱动程序
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
#include "SWM341_sdram.h"

/******************************************************************************************************************************************
* 函数名称: SDRAM_Init()
* 功能说明: SDRAM控制器初始化
* 输    入: SDRAM_InitStructure * initStruct    包含 SDRAM 控制器相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SDRAM_Init(SDRAM_InitStructure * initStruct)
{
    uint32_t cyclesPerUs = CyclesPerUs / (initStruct->ClkDiv + 1);  // 1us有多少个SDRAM_CLK周期
    uint32_t row_n;

    SYS->CLKEN1 |= (1 << SYS_CLKEN1_SDRAM_Pos);

    SDRAMC->TIM = (initStruct->TimeTRP  << SDRAMC_TIM_TRP_Pos)  |
                  (initStruct->TimeTRCD << SDRAMC_TIM_TRCD_Pos) |
                  (initStruct->TimeTRC  << SDRAMC_TIM_TRC_Pos)  |
                  ((cyclesPerUs * 200)  << SDRAMC_TIM_T100US_Pos);  // 要求大于100us

    SDRAMC->CFG = (initStruct->Size       << SDRAMC_CFG_SIZE_Pos)     |
                  (initStruct->ClkDiv     << SDRAMC_CFG_CLKDIV_Pos)   |
                  (initStruct->CASLatency << SDRAMC_CFG_CASDELAY_Pos) |
                  (((SystemCoreClock / (initStruct->ClkDiv + 1)) > 66000000) << SDRAMC_CFG_HIGHFREQ_Pos);

    switch(initStruct->Size)
    {
    case SDRAM_SIZE_2MB:  row_n = 2048; break;
    case SDRAM_SIZE_8MB:  row_n = 4096; break;
    case SDRAM_SIZE_16MB: row_n = 4096; break;
    case SDRAM_SIZE_32MB: row_n = 8192; break;
    default:              row_n = 4096; break;
    }

    SDRAMC->T64 = (initStruct->RefreshTime * 1000 / row_n + 1) * cyclesPerUs;

    SDRAMC->CR = (1 << SDRAMC_CR_PWRON_Pos);

    while(SDRAMC->CR & SDRAMC_CR_PWRON_Msk) __NOP();    //等待初始完成
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
    SDRAMC->CR &= ~SDRAMC_CR_ENTERSRF_Msk;

    for(int i = 0; i < 100; i++) __NOP();
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
    SDRAMC->CR |= SDRAMC_CR_ENTERSRF_Msk;

    for(int i = 0; i < 100; i++) __NOP();
}
