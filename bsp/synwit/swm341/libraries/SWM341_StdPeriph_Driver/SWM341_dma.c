/******************************************************************************************************************************************
* 文件名称: SWM341_dma.c
* 功能说明: SWM341单片机的DMA功能驱动库
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
#include "SWM341_dma.h"

/******************************************************************************************************************************************
* 函数名称: DMA_CH_Init()
* 功能说明: DMA通道初始化
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           DMA_InitStructure * initStruct    包含DMA通道相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_Init(uint32_t chn, DMA_InitStructure * initStruct)
{
    DMA->EN = 1;            //每个通道都有自己独立的开关控制，所以总开关可以是一直开启的

    DMA_CH_Close(chn);      //关闭后配置

    DMA->CH[chn].CR = (initStruct->Mode << DMA_CR_AUTORE_Pos) |
                      ((initStruct->Count - 1) << DMA_CR_LEN_Pos);

    DMA->CH[chn].SRC = initStruct->SrcAddr;
    DMA->CH[chn].DST = initStruct->DstAddr;

    DMA->CH[chn].AM = (initStruct->SrcAddrInc << DMA_AM_SRCAM_Pos)  |
                      (initStruct->DstAddrInc << DMA_AM_DSTAM_Pos)  |
                      (initStruct->Unit       << DMA_AM_SRCBIT_Pos) |
                      (initStruct->Unit       << DMA_AM_DSTBIT_Pos);

    switch(initStruct->Handshake & DMA_HS_MSK)
    {
    case DMA_HS_NO:
        DMA->CH[chn].MUX = 0;
        break;

    case DMA_HS_SRC:
        DMA->CH[chn].MUX = ((initStruct->Handshake & 0xF) << DMA_MUX_SRCHSSIG_Pos) | (1 << DMA_MUX_SRCHSEN_Pos);
        break;

    case DMA_HS_DST:
        DMA->CH[chn].MUX = ((initStruct->Handshake & 0xF) << DMA_MUX_DSTHSSIG_Pos) | (1 << DMA_MUX_DSTHSEN_Pos);
        break;

    case DMA_HS_EXT:
        DMA->CH[chn].MUX = ((initStruct->Handshake & 0xF) << DMA_MUX_EXTHSSIG_Pos) | (1 << DMA_MUX_EXTHSEN_Pos);
        DMA->CH[chn].CR |= (1 << DMA_CR_STEPOP_Pos);
        break;

    default:
        break;
    }

    DMA->PRI &= ~(1 << chn);
    DMA->PRI |= (initStruct->Priority << chn);

    DMA->IF  = (1 << chn);      //清除中断标志
    DMA->IE |= (1 << chn);
    if(initStruct->DoneIE)  DMA->IM &= ~(1 << chn);
    else                    DMA->IM |=  (1 << chn);

    if(initStruct->DoneIE) NVIC_EnableIRQ(DMA_IRQn);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_Open()
* 功能说明: DMA通道开启，对于软件启动通道，开启后立即传输；对于硬件触发通道，开启后还需等出现触发信号后才开始搬运
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_Open(uint32_t chn)
{
    DMA->CH[chn].CR |= (1 << DMA_CR_RXEN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_Close()
* 功能说明: DMA通道关闭
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_Close(uint32_t chn)
{
    DMA->CH[chn].CR &= ~(DMA_CR_TXEN_Msk | DMA_CR_RXEN_Msk);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTEn()
* 功能说明: DMA中断使能，数据搬运完成后触发中断
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTEn(uint32_t chn)
{
    DMA->IM &= ~(1 << chn);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTDis()
* 功能说明: DMA中断禁止，数据搬运完成后不触发中断
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTDis(uint32_t chn)
{
    DMA->IM |= (1 << chn);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTClr()
* 功能说明: DMA中断标志清除
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTClr(uint32_t chn)
{
    DMA->IF = (1 << chn);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTStat()
* 功能说明: DMA中断状态查询
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
* 输    出: uint32_t              1 数据搬运完成    0 数据搬运未完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t DMA_CH_INTStat(uint32_t chn)
{
    return (DMA->IF & (1 << chn)) ? 1 : 0;
}
