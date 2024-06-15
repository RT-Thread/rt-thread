/******************************************************************************************************************************************
* 文件名称: SWM341_spi.c
* 功能说明: SWM341单片机的SPI功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0      2016年1月30日
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
#include "SWM341_spi.h"


/******************************************************************************************************************************************
* 函数名称: SPI_Init()
* 功能说明: SPI同步串行接口初始化，包括帧长度设定、时序设定、速度设定、中断设定、FIFO触发设定
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           SPI_InitStructure * initStruct  包含SPI相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Init(SPI_TypeDef * SPIx, SPI_InitStructure * initStruct)
{
    uint32_t fast = 0, no_sync = 0;

    switch((uint32_t)SPIx)
    {
    case ((uint32_t)SPI0):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_SPI0_Pos);
        break;

    case ((uint32_t)SPI1):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_SPI1_Pos);
        break;
    }

    SPI_Close(SPIx);    //一些关键寄存器只能在SPI关闭时设置

    if(initStruct->clkDiv == SPI_CLKDIV_2)
    {
        fast = 1;
        no_sync = 1;
    }
    else if(initStruct->clkDiv == SPI_CLKDIV_4)
    {
        no_sync = 1;
    }

    SPIx->CTRL &= ~(SPI_CTRL_FFS_Msk | SPI_CTRL_CPHA_Msk | SPI_CTRL_CPOL_Msk | SPI_CTRL_SIZE_Msk | SPI_CTRL_MSTR_Msk | SPI_CTRL_FAST_Msk | SPI_CTRL_NSYNC_Msk |
                    SPI_CTRL_CLKDIV_Msk | SPI_CTRL_SSN_H_Msk | SPI_CTRL_RFTHR_Msk | SPI_CTRL_TFTHR_Msk);
    SPIx->CTRL |= (initStruct->FrameFormat     << SPI_CTRL_FFS_Pos)    |
                  (initStruct->SampleEdge      << SPI_CTRL_CPHA_Pos)   |
                  (initStruct->IdleLevel       << SPI_CTRL_CPOL_Pos)   |
                  ((initStruct->WordSize-1)    << SPI_CTRL_SIZE_Pos)   |
                  (initStruct->Master          << SPI_CTRL_MSTR_Pos)   |
                  (fast                        << SPI_CTRL_FAST_Pos)   |
                  (no_sync                     << SPI_CTRL_NSYNC_Pos)  |
                  ((initStruct->clkDiv & 7)    << SPI_CTRL_CLKDIV_Pos) |
                  (0                           << SPI_CTRL_SSN_H_Pos)  |
                  ((initStruct->RXThreshold > 0 ? initStruct->RXThreshold-1 : 0) << SPI_CTRL_RFTHR_Pos)  |
                  (initStruct->TXThreshold     << SPI_CTRL_TFTHR_Pos)  |
                  (1                           << SPI_CTRL_RFCLR_Pos)  |
                  (1                           << SPI_CTRL_TFCLR_Pos);
    SPIx->CTRL &= ~(SPI_CTRL_RFCLR_Msk | SPI_CTRL_TFCLR_Msk);

    SPIx->IF = 0x37F;   //清除中断标志
    SPIx->IE = 0x000;
    SPIx->IE |= (initStruct->RXThresholdIEn << SPI_IE_RFTHR_Pos) |
                (initStruct->TXThresholdIEn << SPI_IE_TFTHR_Pos) |
                (initStruct->TXCompleteIEn  << SPI_IE_FTC_Pos);

    switch((uint32_t)SPIx)
    {
    case ((uint32_t)SPI0):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TXCompleteIEn)
        {
            NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(SPI0_IRQn);
        }
        break;

    case ((uint32_t)SPI1):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TXCompleteIEn)
        {
            NVIC_EnableIRQ(SPI1_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(SPI1_IRQn);
        }
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: SPI_Open()
* 功能说明: SPI打开，允许收发
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Open(SPI_TypeDef * SPIx)
{
    SPIx->CTRL |= (0x01 << SPI_CTRL_EN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: SPI_Close()
* 功能说明: SPI关闭，禁止收发
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Close(SPI_TypeDef * SPIx)
{
    SPIx->CTRL &= ~SPI_CTRL_EN_Msk;
}

/******************************************************************************************************************************************
* 函数名称: SPI_Read()
* 功能说明: 读取一个数据
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: uint32_t              读取到的数据
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SPI_Read(SPI_TypeDef * SPIx)
{
    return SPIx->DATA;
}

/******************************************************************************************************************************************
* 函数名称: SPI_Write()
* 功能说明: 写入一个数据
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           uint32_t                要写入的数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Write(SPI_TypeDef * SPIx, uint32_t data)
{
    SPIx->DATA = data;
}

/******************************************************************************************************************************************
* 函数名称: SPI_WriteWithWait()
* 功能说明: 写入一个数据并等待数据完全发送出去
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1、SPI1
*           uint32_t                要写入的数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_WriteWithWait(SPI_TypeDef * SPIx, uint32_t data)
{
    SPIx->STAT |= (1 << SPI_STAT_WTC_Pos);

    SPIx->DATA = data;

    while((SPIx->STAT & SPI_STAT_WTC_Msk) == 0);
}

/******************************************************************************************************************************************
* 函数名称: SPI_ReadWrite()
* 功能说明: 发送一个数据，并返回发送过程中接收到的
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           uint32_t data           要发送的数据
* 输    出: uint32_t              接收到的数据
* 注意事项: 对于同一个SPI模块，此函数不应与SPI_Write()混着用，因为SPI_Write()不清除SPI_STAT_RFNE状态
******************************************************************************************************************************************/
uint32_t SPI_ReadWrite(SPI_TypeDef * SPIx, uint32_t data)
{
    SPIx->DATA = data;
    while(!(SPIx->STAT & SPI_STAT_RFNE_Msk));

    return SPIx->DATA;
}

/******************************************************************************************************************************************
* 函数名称: SPI_IsRXEmpty()
* 功能说明: 接收FIFO是否空，如果不空则可以继续SPI_Read()
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: uint32_t              1 接收FIFO空    0 接收FIFO非空
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SPI_IsRXEmpty(SPI_TypeDef * SPIx)
{
    return (SPIx->STAT & SPI_STAT_RFNE_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: SPI_IsTXFull()
* 功能说明: 发送FIFO是否满，如果不满则可以继续SPI_Write()
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: uint32_t              1 发送FIFO满    0 发送FIFO不满
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SPI_IsTXFull(SPI_TypeDef * SPIx)
{
    return (SPIx->STAT & SPI_STAT_TFNF_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: SPI_IsTXEmpty()
* 功能说明: 发送FIFO是否空
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: uint32_t              1 发送FIFO空    0 发送FIFO非空
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SPI_IsTXEmpty(SPI_TypeDef * SPIx)
{
    return (SPIx->STAT & SPI_STAT_TFE_Msk) ? 1 : 0;
}


/******************************************************************************************************************************************
* 函数名称: SPI_INTEn()
* 功能说明: 中断使能
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           uint32_t it             interrupt type，有效值SPI_IT_RX_OVF、SPI_IT_RX_FULL、SPI_IT_RX_HFULL、SPI_IT_TX_EMPTY、SPI_IT_TX_HFULL、
*                                   SPI_IT_RX_THRES、SPI_IT_TX_THRES、SPI_IT_TX_DONE、SPI_IT_CS_FALL、SPI_IT_CS_RISE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_INTEn(SPI_TypeDef * SPIx, uint32_t it)
{
    SPIx->IE |= it;
}

/******************************************************************************************************************************************
* 函数名称: SPI_INTDis()
* 功能说明: 中断禁止
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           uint32_t it             interrupt type，有效值SPI_IT_RX_OVF、SPI_IT_RX_FULL、SPI_IT_RX_HFULL、SPI_IT_TX_EMPTY、SPI_IT_TX_HFULL、
*                                   SPI_IT_RX_THRES、SPI_IT_TX_THRES、SPI_IT_TX_DONE、SPI_IT_CS_FALL、SPI_IT_CS_RISE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_INTDis(SPI_TypeDef * SPIx, uint32_t it)
{
    SPIx->IE &= ~it;
}

/******************************************************************************************************************************************
* 函数名称: SPI_INTClr()
* 功能说明: 中断标志清除
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           uint32_t it             interrupt type，有效值SPI_IT_RX_OVF、SPI_IT_RX_FULL、SPI_IT_RX_HFULL、SPI_IT_TX_EMPTY、SPI_IT_TX_HFULL、
*                                   SPI_IT_RX_THRES、SPI_IT_TX_THRES、SPI_IT_TX_DONE、SPI_IT_CS_FALL、SPI_IT_CS_RISE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_INTClr(SPI_TypeDef * SPIx, uint32_t it)
{
    SPIx->IF = it;
}

/******************************************************************************************************************************************
* 函数名称: SPI_INTStat()
* 功能说明: 中断状态查询
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           uint32_t it             interrupt type，有效值SPI_IT_RX_OVF、SPI_IT_RX_FULL、SPI_IT_RX_HFULL、SPI_IT_TX_EMPTY、SPI_IT_TX_HFULL、
*                                   SPI_IT_RX_THRES、SPI_IT_TX_THRES、SPI_IT_TX_DONE、SPI_IT_CS_FALL、SPI_IT_CS_RISE 及其“或”
* 输    出: uint32_t              1 中断发生    0 中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SPI_INTStat(SPI_TypeDef * SPIx, uint32_t it)
{
    return (SPIx->IF & it) ? 1 : 0;
}


/******************************************************************************************************************************************
* 函数名称: I2S_Init()
* 功能说明: I2S音频串行接口初始化，包括帧格式、数据长度、时钟频率、中断设定、FIFO触发设定
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
*           I2S_InitStructure * initStruct  包含I2S相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2S_Init(SPI_TypeDef * SPIx, I2S_InitStructure * initStruct)
{
    switch((uint32_t)SPIx)
    {
    case ((uint32_t)SPI0):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_SPI0_Pos);
        break;

    case ((uint32_t)SPI1):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_SPI1_Pos);
        break;
    }

    I2S_Close(SPIx);    //一些关键寄存器只能在SPI关闭时设置

    SPIx->CTRL &= ~(SPI_CTRL_FFS_Msk | SPI_CTRL_RFTHR_Msk | SPI_CTRL_TFTHR_Msk);
    SPIx->CTRL |= (SPI_FORMAT_I2S              << SPI_CTRL_FFS_Pos)    |
                  ((initStruct->RXThreshold > 0 ? initStruct->RXThreshold-1 : 0) << SPI_CTRL_RFTHR_Pos)  |
                  (initStruct->TXThreshold     << SPI_CTRL_TFTHR_Pos)  |
                  (1                           << SPI_CTRL_RFCLR_Pos)  |
                  (1                           << SPI_CTRL_TFCLR_Pos);
    SPIx->CTRL &= ~(SPI_CTRL_RFCLR_Msk | SPI_CTRL_TFCLR_Msk);

    SPIx->I2SCR &= ~(SPI_I2SCR_MSTR_Msk | SPI_I2SCR_DIEN_Msk | SPI_I2SCR_DOEN_Msk | SPI_I2SCR_FFMT_Msk | SPI_I2SCR_DLEN_Msk | SPI_I2SCR_CHLEN_Msk | SPI_I2SCR_PCMSYNW_Msk);
    SPIx->I2SCR |= ((initStruct->Mode & 0x04 ? 1 : 0) << SPI_I2SCR_MSTR_Pos) |
                   ((initStruct->Mode & 0x02 ? 1 : 0) << SPI_I2SCR_DOEN_Pos) |
                   ((initStruct->Mode & 0x01 ? 1 : 0) << SPI_I2SCR_DIEN_Pos) |
                   ((initStruct->FrameFormat & 0x03)  << SPI_I2SCR_FFMT_Pos) |
                   (initStruct->DataLen               << SPI_I2SCR_DLEN_Pos) |
                   (initStruct->ChannelLen            << SPI_I2SCR_CHLEN_Pos) |
                   ((initStruct->FrameFormat & 0x04 ? 1 : 0) << SPI_I2SCR_PCMSYNW_Pos);

    SPIx->I2SPR &= ~SPI_I2SPR_SCLKDIV_Msk;
    SPIx->I2SPR |= (SystemCoreClock / initStruct->ClkFreq / 2 - 1) << SPI_I2SPR_SCLKDIV_Pos;

    SPIx->IF = 0x37F;   //清除中断标志
    SPIx->IE = 0x000;
    SPIx->IE |= (initStruct->RXThresholdIEn << SPI_IE_RFTHR_Pos) |
                (initStruct->TXThresholdIEn << SPI_IE_TFTHR_Pos) |
                (initStruct->TXCompleteIEn  << SPI_IE_FTC_Pos);

    switch((uint32_t)SPIx)
    {
    case ((uint32_t)SPI0):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TXCompleteIEn)
        {
            NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(SPI0_IRQn);
        }
        break;

    case ((uint32_t)SPI1):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TXCompleteIEn)
        {
            NVIC_EnableIRQ(SPI1_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(SPI1_IRQn);
        }
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: I2S_Open()
* 功能说明: I2S打开，允许收发
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2S_Open(SPI_TypeDef * SPIx)
{
    SPIx->CTRL |= (0x01 << SPI_CTRL_EN_Pos);    //使能SPI才能使用TX Complete中断
    SPIx->I2SCR |= (0x01 << SPI_I2SCR_EN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: I2S_Close()
* 功能说明: I2S关闭，禁止收发
* 输    入: SPI_TypeDef * SPIx        指定要被设置的SPI，有效值包括SPI0、SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2S_Close(SPI_TypeDef * SPIx)
{
    SPIx->CTRL &= ~SPI_CTRL_EN_Msk;
    SPIx->I2SCR &= ~SPI_I2SCR_EN_Msk;
}
