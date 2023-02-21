/******************************************************************************************************************************************
* 文件名称: SWM320_norflash.c
* 功能说明: SWM320单片机的NOR Flash驱动程序
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
#include "SWM320_norflash.h"


/******************************************************************************************************************************************
* 函数名称: NORFL_Init()
* 功能说明: NOR Flash控制器初始化
* 输    入: NORFL_InitStructure * initStruct    包含NOR Flash控制器相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void NORFL_Init(NORFL_InitStructure * initStruct)
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

    SYS->CLKEN |= (1 << SYS_CLKEN_NORFL_Pos);

    NORFLC->CR = ((initStruct->DataWidth == 8 ? 1 : 0) << NORFLC_CR_BYTEIF_Pos) |
                 (initStruct->WELowPulseTime << NORFLC_CR_WRTIME_Pos) |
                 (initStruct->OEPreValidTime << NORFLC_CR_RDTIME_Pos);

    NORFLC->IE = 3;
    NORFLC->IF = 3;     // 清除中断标志
    if(initStruct->OperFinishIEn)  NORFLC->IM &= ~(1 << NORFLC_IM_FINISH_Pos);
    else                           NORFLC->IM |=  (1 << NORFLC_IM_FINISH_Pos);
    if(initStruct->OperTimeoutIEn) NORFLC->IM &= ~(1 << NORFLC_IM_TIMEOUT_Pos);
    else                           NORFLC->IM |=  (1 << NORFLC_IM_TIMEOUT_Pos);
}

/******************************************************************************************************************************************
* 函数名称: NORFL_ChipErase()
* 功能说明: NOR Flash整片擦除
* 输    入: 无
* 输    出: uint32_t          0 擦除成功    1 擦除超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t NORFL_ChipErase(void)
{
    uint32_t res;

    NORFLC->CMD = (NORFL_CMD_CHIP_ERASE << NORFLC_CMD_CMD_Pos);

    while(((NORFLC->IF & NORFLC_IF_FINISH_Msk) == 0) &&
          ((NORFLC->IF & NORFLC_IF_TIMEOUT_Msk) == 0)) __NOP();

    if(NORFLC->IF & NORFLC_IF_FINISH_Msk)  res = 0;
    else                                   res = 1;

    NORFLC->IF = NORFLC_IF_FINISH_Msk | NORFLC_IF_TIMEOUT_Msk;

    return res;
}

/******************************************************************************************************************************************
* 函数名称: NORFL_SectorErase()
* 功能说明: NOR Flash扇区擦除
* 输    入: uint32_t addr     要擦除扇区的起始地址
* 输    出: uint32_t          0 擦除成功    1 擦除超时
* 注意事项: MX29LV128DB 前8扇区为8K、后255扇区为64K    MX29LV128DT 前255扇区为64K、后8扇区为8K
******************************************************************************************************************************************/
uint32_t NORFL_SectorErase(uint32_t addr)
{
    uint32_t res;

    NORFLC->ADDR = addr;
    NORFLC->CMD = (NORFL_CMD_SECTOR_ERASE << NORFLC_CMD_CMD_Pos);

    while(((NORFLC->IF & NORFLC_IF_FINISH_Msk) == 0) &&
          ((NORFLC->IF & NORFLC_IF_TIMEOUT_Msk) == 0)) __NOP();

    if(NORFLC->IF & NORFLC_IF_FINISH_Msk)  res = 0;
    else                                   res = 1;

    NORFLC->IF = NORFLC_IF_FINISH_Msk | NORFLC_IF_TIMEOUT_Msk;

    return res;
}

/******************************************************************************************************************************************
* 函数名称: NORFL_Write()
* 功能说明: NOR Flash写
* 输    入: uint32_t addr     数据要写入的地址
*           uint32_t data       要写入的数据
* 输    出: uint32_t          0 写入成功    1 写入超时
* 注意事项: 硬件连接，数据线为16位时，半字写入；数据线为8位时，字节写入
******************************************************************************************************************************************/
uint32_t NORFL_Write(uint32_t addr, uint32_t data)
{
    uint32_t res;

    NORFLC->ADDR = addr;
    NORFLC->CMD = (NORFL_CMD_PROGRAM << NORFLC_CMD_CMD_Pos) | (data << NORFLC_CMD_DATA_Pos);

    while(((NORFLC->IF & NORFLC_IF_FINISH_Msk) == 0) &&
          ((NORFLC->IF & NORFLC_IF_TIMEOUT_Msk) == 0)) __NOP();

    if(NORFLC->IF & NORFLC_IF_FINISH_Msk)  res = 0;
    else                                   res = 1;

    NORFLC->IF = NORFLC_IF_FINISH_Msk | NORFLC_IF_TIMEOUT_Msk;

    return res;
}

/******************************************************************************************************************************************
* 函数名称: NORFL_Read()
* 功能说明: NOR Flash读
* 输    入: uint32_t addr     数据要读出的地址
* 输    出: uint32_t          读出的数据
* 注意事项: 硬件连接，数据线为16位时，半字读出；数据线为8位时，字节读出
******************************************************************************************************************************************/
uint32_t NORFL_Read(uint32_t addr)
{
    NORFLC->ADDR = addr;
    NORFLC->CMD = (NORFL_CMD_READ << NORFLC_CMD_CMD_Pos);

    return (NORFLC->CMD & NORFLC_CMD_DATA_Msk);
}

/******************************************************************************************************************************************
* 函数名称: NORFL_ReadID()
* 功能说明: NOR Flash读ID
* 输    入: uint32_t id_addr  ID地址，此参数是芯片相关的，每种芯片都不同
* 输    出: uint16_t          读取到的ID
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t NORFL_ReadID(uint32_t id_addr)
{
    uint16_t id;

    NORFLC->CMD = (NORFL_CMD_AUTO_SELECT << NORFLC_CMD_CMD_Pos);

    NORFLC->ADDR = id_addr;
    NORFLC->CMD = (NORFL_CMD_READ << NORFLC_CMD_CMD_Pos);

    id = NORFLC->CMD & NORFLC_CMD_DATA_Msk;

    NORFLC->CMD = (NORFL_CMD_RESET << NORFLC_CMD_CMD_Pos);  // 退出ID读取模式

    return id;
}
