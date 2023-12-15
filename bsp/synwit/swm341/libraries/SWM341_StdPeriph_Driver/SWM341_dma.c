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
                     ((initStruct->Count ? initStruct->Count - 1 : 0) << DMA_CR_LEN_Pos);

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

    int totalBytes = initStruct->Count * (1 << initStruct->Unit);

    if(initStruct->DstAddrInc == 2)     // Destination Scatter-Gather Transfer
    {
        DMA->CH[chn].DSTSGADDR1 = initStruct->DstAddr + totalBytes / 4 * 1;
        DMA->CH[chn].DSTSGADDR2 = initStruct->DstAddr + totalBytes / 4 * 2;
        DMA->CH[chn].DSTSGADDR3 = initStruct->DstAddr + totalBytes / 4 * 3;
    }
    if(initStruct->SrcAddrInc == 2)     // Source      Scatter-Gather Transfer
    {
        DMA->CH[chn].SRCSGADDR1 = initStruct->SrcAddr + totalBytes / 4 * 1;
        DMA->CH[chn].SRCSGADDR2 = initStruct->SrcAddr + totalBytes / 4 * 2;
        DMA->CH[chn].SRCSGADDR3 = initStruct->SrcAddr + totalBytes / 4 * 3;
    }

    DMA->PRI &= ~(1 << chn);
    DMA->PRI |= (initStruct->Priority << chn);

    DMA->IM |= (1 << chn);  // 默认全部关闭
    DMA->DSTSGIM |= (3 << (chn * 2));
    DMA->SRCSGIM |= (3 << (chn * 2));
    DMA->IE |= (1 << chn);  // 标志总是可查
    DMA->DSTSGIE |= (3 << (chn * 2));
    DMA->SRCSGIE |= (3 << (chn * 2));

    DMA_CH_INTClr(chn, initStruct->INTEn);
    DMA_CH_INTEn(chn, initStruct->INTEn);

    if(initStruct->INTEn) NVIC_EnableIRQ(DMA_IRQn);
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
* 函数名称: DMA_CH_SetCount()
* 功能说明: 设置传输 Unit 个数
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           uint32_t count          传输 Unit 个数，最大取值0x100000
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_SetCount(uint32_t chn, uint32_t count)
{
    DMA->CH[chn].CR &= ~DMA_CR_LEN_Msk;
    DMA->CH[chn].CR |= ((count - 1) << DMA_CR_LEN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_GetRemaining()
* 功能说明: 查询剩余的传输 Unit 个数
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
* 输    出: uint32_t              剩余的传输 Unit 个数
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t DMA_CH_GetRemaining(uint32_t chn)
{
    return (DMA->CH[chn].DSTSR & DMA_DSTSR_LEN_Msk);
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_SetSrcAddress()
* 功能说明: 设置传输源地址
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           uint32_t address        源地址
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_SetSrcAddress(uint32_t chn, uint32_t address)
{
    DMA->CH[chn].SRC = address;
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_SetDstAddress()
* 功能说明: 设置传输目的地址
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           uint32_t address        目的地址
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_SetDstAddress(uint32_t chn, uint32_t address)
{
    DMA->CH[chn].DST = address;
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTEn()
* 功能说明: DMA中断使能
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           uint32_t it             interrupt type，有效值有 DMA_IT_DONE、DMA_IT_DSTSG_HALF、DMA_IT_DSTSG_DONE、DMA_IT_SRCSG_HALF、
*                                   DMA_IT_SRCSG_DONE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTEn(uint32_t chn, uint32_t it)
{
    DMA->IM &= ~(it << chn);
    DMA->DSTSGIM &= ~((it >>  8) << (chn * 2));
    DMA->SRCSGIM &= ~((it >> 16) << (chn * 2));
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTDis()
* 功能说明: DMA中断禁止
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           uint32_t it             interrupt type，有效值有 DMA_IT_DONE、DMA_IT_DSTSG_HALF、DMA_IT_DSTSG_DONE、DMA_IT_SRCSG_HALF、
*                                   DMA_IT_SRCSG_DONE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTDis(uint32_t chn, uint32_t it)
{
    DMA->IM |=  (it << chn);
    DMA->DSTSGIM |=  ((it >>  8) << (chn * 2));
    DMA->SRCSGIM |=  ((it >> 16) << (chn * 2));
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTClr()
* 功能说明: DMA中断标志清除
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           uint32_t it             interrupt type，有效值有 DMA_IT_DONE、DMA_IT_DSTSG_HALF、DMA_IT_DSTSG_DONE、DMA_IT_SRCSG_HALF、
*                                   DMA_IT_SRCSG_DONE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTClr(uint32_t chn, uint32_t it)
{
    DMA->IF = (it << chn);
    DMA->DSTSGIF = ((it >>  8) << (chn * 2));
    DMA->SRCSGIF = ((it >> 16) << (chn * 2));
}

/******************************************************************************************************************************************
* 函数名称: DMA_CH_INTStat()
* 功能说明: DMA中断状态查询
* 输    入: uint32_t chn          指定要配置的通道，有效值有DMA_CH0、DMA_CH1、DMA_CH2、DMA_CH3
*           uint32_t it             interrupt type，有效值有 DMA_IT_DONE、DMA_IT_DSTSG_HALF、DMA_IT_DSTSG_DONE、DMA_IT_SRCSG_HALF、
*                                   DMA_IT_SRCSG_DONE 及其“或”
* 输    出: uint32_t              1 指定中断已发生    0 指定中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t DMA_CH_INTStat(uint32_t chn, uint32_t it)
{
    return ((DMA->IF & (it << chn)) ||
            (DMA->DSTSGIF & ((it >>  8) << (chn * 2))) ||
            (DMA->SRCSGIF & ((it >> 16) << (chn * 2))));
}
