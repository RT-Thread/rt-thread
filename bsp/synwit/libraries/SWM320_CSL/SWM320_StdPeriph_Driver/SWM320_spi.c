/******************************************************************************************************************************************
* 文件名称: SWM320_spi.c
* 功能说明: SWM320单片机的SPI功能驱动库
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
#include "SWM320_spi.h"


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
    switch((uint32_t)SPIx)
    {
    case ((uint32_t)SPI0):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_SPI0_Pos);
        break;

    case ((uint32_t)SPI1):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_SPI0_Pos);     //与SPI0使用同一位时钟使能
        break;
    }

    SPI_Close(SPIx);    //一些关键寄存器只能在SPI关闭时设置

    SPIx->CTRL &= ~(SPI_CTRL_FFS_Msk | SPI_CTRL_CPHA_Msk | SPI_CTRL_CPOL_Msk |
                  SPI_CTRL_SIZE_Msk | SPI_CTRL_MSTR_Msk | SPI_CTRL_CLKDIV_Msk | SPI_CTRL_SSN_H_Msk);
    SPIx->CTRL |= (initStruct->FrameFormat   << SPI_CTRL_FFS_Pos) |
                (initStruct->SampleEdge    << SPI_CTRL_CPHA_Pos) |
                (initStruct->IdleLevel     << SPI_CTRL_CPOL_Pos) |
                ((initStruct->WordSize-1)  << SPI_CTRL_SIZE_Pos) |
                (initStruct->Master        << SPI_CTRL_MSTR_Pos) |
                (initStruct->clkDiv        << SPI_CTRL_CLKDIV_Pos) |
                (0                         << SPI_CTRL_SSN_H_Pos);

    SPIx->IF = (0x01 << SPI_IF_RFOVF_Pos);  //清除中断标志
    SPIx->IE &= ~(SPI_IE_RFHF_Msk | SPI_IE_TFHF_Msk | SPI_IE_FTC_Msk);
    SPIx->IE |= (initStruct->RXHFullIEn << SPI_IE_RFHF_Pos) |
                (initStruct->TXEmptyIEn << SPI_IE_TFE_Pos) |
                (initStruct->TXCompleteIEn << SPI_IE_FTC_Pos);

    switch((uint32_t)SPIx)
    {
    case ((uint32_t)SPI0):
        if(initStruct->RXHFullIEn | initStruct->TXEmptyIEn | initStruct->TXCompleteIEn)
        {
            NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(SPI0_IRQn);
        }
        break;

    case ((uint32_t)SPI1):
        if(initStruct->RXHFullIEn | initStruct->TXEmptyIEn | initStruct->TXCompleteIEn)
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
*                                   SPI_IT_TX_DONE 及其“或”
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
*                                   SPI_IT_TX_DONE 及其“或”
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
*                                   SPI_IT_TX_DONE 及其“或”
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
*                                   SPI_IT_TX_DONE 及其“或”
* 输    出: uint32_t              1 中断发生    0 中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SPI_INTStat(SPI_TypeDef * SPIx, uint32_t it)
{
    return (SPIx->IF & it) ? 1 : 0;
}
