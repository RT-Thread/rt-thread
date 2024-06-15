/******************************************************************************************************************************************
* 文件名称: SWM341_dma2d.c
* 功能说明: SWM341单片机的DMA2D功能驱动库
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
#include "SWM341_dma2d.h"


/******************************************************************************************************************************************
* 函数名称: DMA2D_Init()
* 功能说明: DMA2D初始化
* 输    入: DMA2D_InitStructure * initStruct
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_Init(DMA2D_InitStructure * initStruct)
{
    SYS->CLKEN0 |= (1 << SYS_CLKEN0_DMA2D_Pos);

    DMA2D->CR &= ~DMA2D_CR_WAIT_Msk;
    DMA2D->CR |= (initStruct->Interval << DMA2D_CR_WAIT_Pos);

    DMA2D->IF = 0xFF;
    DMA2D->IE = (initStruct->IntEOTEn << DMA2D_IE_DONE_Pos);

    if(initStruct->IntEOTEn)
        NVIC_EnableIRQ(DMA2D_IRQn);
}


/******************************************************************************************************************************************
* 函数名称: DMA2D_PixelFill()
* 功能说明: DMA2D向指定存储器区域填充指定颜色
* 输    入: DMA2D_LayerSetting * outLayer 要填充的位置、大小、颜色格式等
*           uint32_t color                  要填充的颜色
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_PixelFill(DMA2D_LayerSetting * outLayer, uint32_t color)
{
    DMA2D->L[DMA2D_LAYER_OUT].COLOR = color;

    DMA2D->L[DMA2D_LAYER_OUT].MAR = outLayer->Address;
    DMA2D->L[DMA2D_LAYER_OUT].OR  = outLayer->LineOffset;
    DMA2D->L[DMA2D_LAYER_OUT].PFCCR = (outLayer->ColorMode << DMA2D_PFCCR_CFMT_Pos);

    DMA2D->NLR = ((outLayer->LineCount - 1) << DMA2D_NLR_NLINE_Pos) |
                 ((outLayer->LinePixel - 1) << DMA2D_NLR_NPIXEL_Pos);

    DMA2D->CR &= ~DMA2D_CR_MODE_Msk;
    DMA2D->CR |= (3 << DMA2D_CR_MODE_Pos) |
                 (1 << DMA2D_CR_START_Pos);
}


/******************************************************************************************************************************************
* 函数名称: DMA2D_PixelMove()
* 功能说明: DMA2D像素数据搬运
* 输    入: DMA2D_LayerSetting * fgLayer
*           DMA2D_LayerSetting * outLayer
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_PixelMove(DMA2D_LayerSetting * fgLayer, DMA2D_LayerSetting * outLayer)
{
    DMA2D->L[DMA2D_LAYER_FG].MAR = fgLayer->Address;
    DMA2D->L[DMA2D_LAYER_FG].OR  = fgLayer->LineOffset;
    DMA2D->L[DMA2D_LAYER_FG].PFCCR = (fgLayer->ColorMode << DMA2D_PFCCR_CFMT_Pos);

    DMA2D->L[DMA2D_LAYER_OUT].MAR = outLayer->Address;
    DMA2D->L[DMA2D_LAYER_OUT].OR  = outLayer->LineOffset;

    DMA2D->NLR = ((outLayer->LineCount - 1) << DMA2D_NLR_NLINE_Pos) |
                 ((outLayer->LinePixel - 1) << DMA2D_NLR_NPIXEL_Pos);

    DMA2D->CR &= ~DMA2D_CR_MODE_Msk;
    DMA2D->CR |= (0 << DMA2D_CR_MODE_Pos) |
                 (1 << DMA2D_CR_START_Pos);
}


/******************************************************************************************************************************************
* 函数名称: DMA2D_PixelConvert()
* 功能说明: DMA2D像素转换
* 输    入: DMA2D_LayerSetting * fgLayer
*           DMA2D_LayerSetting * outLayer
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_PixelConvert(DMA2D_LayerSetting * fgLayer, DMA2D_LayerSetting * outLayer)
{
    DMA2D->L[DMA2D_LAYER_FG].MAR = fgLayer->Address;
    DMA2D->L[DMA2D_LAYER_FG].OR  = fgLayer->LineOffset;
    DMA2D->L[DMA2D_LAYER_FG].PFCCR = (fgLayer->ColorMode << DMA2D_PFCCR_CFMT_Pos);

    DMA2D->L[DMA2D_LAYER_OUT].MAR = outLayer->Address;
    DMA2D->L[DMA2D_LAYER_OUT].OR  = outLayer->LineOffset;
    DMA2D->L[DMA2D_LAYER_OUT].PFCCR = (outLayer->ColorMode << DMA2D_PFCCR_CFMT_Pos);

    DMA2D->NLR = ((outLayer->LineCount - 1) << DMA2D_NLR_NLINE_Pos) |
                 ((outLayer->LinePixel - 1) << DMA2D_NLR_NPIXEL_Pos);

    DMA2D->CR &= ~DMA2D_CR_MODE_Msk;
    DMA2D->CR |= (1 << DMA2D_CR_MODE_Pos) |
                 (1 << DMA2D_CR_START_Pos);
}


/******************************************************************************************************************************************
* 函数名称: DMA2D_PixelBlend()
* 功能说明: DMA2D像素混合
* 输    入: DMA2D_LayerSetting * fgLayer
*           DMA2D_LayerSetting * bgLayer
*           DMA2D_LayerSetting * outLayer
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_PixelBlend(DMA2D_LayerSetting * fgLayer, DMA2D_LayerSetting * bgLayer, DMA2D_LayerSetting * outLayer)
{
    DMA2D->L[DMA2D_LAYER_FG].MAR = fgLayer->Address;
    DMA2D->L[DMA2D_LAYER_FG].OR  = fgLayer->LineOffset;
    DMA2D->L[DMA2D_LAYER_FG].PFCCR = (fgLayer->ColorMode << DMA2D_PFCCR_CFMT_Pos) |
                                     (fgLayer->AlphaMode << DMA2D_PFCCR_AINV_Pos) |
                                     (fgLayer->Alpha     << DMA2D_PFCCR_ALPHA_Pos);

    DMA2D->L[DMA2D_LAYER_BG].MAR = bgLayer->Address;
    DMA2D->L[DMA2D_LAYER_BG].OR  = bgLayer->LineOffset;
    DMA2D->L[DMA2D_LAYER_BG].PFCCR = (bgLayer->ColorMode << DMA2D_PFCCR_CFMT_Pos) |
                                     (bgLayer->AlphaMode << DMA2D_PFCCR_AINV_Pos) |
                                     (bgLayer->Alpha     << DMA2D_PFCCR_ALPHA_Pos);

    DMA2D->L[DMA2D_LAYER_OUT].MAR = outLayer->Address;
    DMA2D->L[DMA2D_LAYER_OUT].OR  = outLayer->LineOffset;
    DMA2D->L[DMA2D_LAYER_OUT].PFCCR = (outLayer->ColorMode << DMA2D_PFCCR_CFMT_Pos);

    DMA2D->NLR = ((outLayer->LineCount - 1) << DMA2D_NLR_NLINE_Pos) |
                 ((outLayer->LinePixel - 1) << DMA2D_NLR_NPIXEL_Pos);

    DMA2D->CR &= ~DMA2D_CR_MODE_Msk;
    DMA2D->CR |= (2 << DMA2D_CR_MODE_Pos) |
                 (1 << DMA2D_CR_START_Pos);
}


/******************************************************************************************************************************************
* 函数名称: DMA2D_IsBusy()
* 功能说明: DMA2D忙查询
* 输    入: 无
* 输    出: uint32_t              1 正在传输   0 传输完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t DMA2D_IsBusy(void)
{
    return (DMA2D->CR & DMA2D_CR_START_Msk) ? 1 : 0;
}


/******************************************************************************************************************************************
* 函数名称: DMA2D_INTEn()
* 功能说明: DMA2D中断使能，完成指定长度的数据传输时触发中断
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_INTEn(void)
{
    DMA2D->IE = DMA2D_IE_DONE_Msk;
}

/******************************************************************************************************************************************
* 函数名称: DMA2D_INTDis()
* 功能说明: DMA2D中断禁止，完成指定长度的数据传输时不触发中断
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_INTDis(void)
{
    DMA2D->IE = 0;
}

/******************************************************************************************************************************************
* 函数名称: DMA2D_INTClr()
* 功能说明: DMA2D中断标志清除
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA2D_INTClr(void)
{
    DMA2D->IF = DMA2D_IF_DONE_Msk;
}

/******************************************************************************************************************************************
* 函数名称: DMA2D_INTStat()
* 功能说明: DMA2D中断状态查询
* 输    入: 无
* 输    出: uint32_t          0 未完成指定长度的数据传输   1 完成指定长度的数据传输
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t DMA2D_INTStat(void)
{
    return (DMA2D->IF & DMA2D_IF_DONE_Msk) ? 1 : 0;
}
