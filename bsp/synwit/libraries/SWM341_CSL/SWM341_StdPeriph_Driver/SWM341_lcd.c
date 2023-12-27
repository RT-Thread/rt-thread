/******************************************************************************************************************************************
* 文件名称: SWM341_lcd.c
* 功能说明: SWM341单片机的LCD功能驱动库
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
#include "SWM341_lcd.h"

#include <string.h>


/******************************************************************************************************************************************
* 函数名称: LCD_Init()
* 功能说明: LCD初始化
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
*           LCD_InitStructure * initStruct    包含LCD相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void LCD_Init(LCD_TypeDef * LCDx, LCD_InitStructure * initStruct)
{
    switch((uint32_t)LCDx)
    {
    case ((uint32_t)LCD):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_LCD_Pos);
        break;
    }

    LCDx->CR  = ((initStruct->ClkDiv - 2)  << LCD_CR_CLKDIV_Pos)   |
                (initStruct->SampleEdge    << LCD_CR_CLKINV_Pos)   |
                (1                         << LCD_CR_CLKALW_Pos)   |
                ((initStruct->Format & 1)  << LCD_CR_FORMAT_Pos)   |
                ((initStruct->Format >> 1) << LCD_CR_SEREN_Pos)    |
                (1                         << LCD_CR_BURSTEN_Pos)  |
                (1                         << LCD_CR_BURSTLEN_Pos) |
                ((1-initStruct->IntEOTEn)  << LCD_CR_AUTORESTA_Pos);

    LCDx->CRH = ((initStruct->HsyncWidth - 1) << LCD_CRH_HSW_Pos) |
                ((initStruct->Hbp - 1)        << LCD_CRH_HBP_Pos) |
                ((initStruct->HnPixel - 1)    << LCD_CRH_PIX_Pos) |
                ((initStruct->Hfp - 1)        << LCD_CRH_HFP_Pos);

    LCDx->CRV = ((initStruct->VsyncWidth - 1) << LCD_CRV_VSW_Pos) |
                ((initStruct->Vbp - 1)        << LCD_CRV_VBP_Pos) |
                ((initStruct->VnPixel - 1)    << LCD_CRV_PIX_Pos) |
                ((initStruct->Vfp - 1)        << LCD_CRV_VFP_Pos);

    LCDx->BGC = initStruct->Background;

    LCDx->L[0].LCR = (1    << LCD_LCR_EN_Pos)   |
                     (0    << LCD_LCR_CKEN_Pos) |
                     (0xFF << LCD_LCR_ALPHA_Pos);

    LCDx->L[0].WHP = (0                         << LCD_WHP_STA_Pos) |
                     ((initStruct->HnPixel - 1) << LCD_WHP_STP_Pos);

    LCDx->L[0].WVP = (0                         << LCD_WVP_STA_Pos) |
                     ((initStruct->VnPixel - 1) << LCD_WVP_STP_Pos);

    LCDx->L[0].ADDR = initStruct->DataSource;

    LCDx->L[0].LLEN = (initStruct->HnPixel - 1);

    LCDx->IF = 1;   //清除标志
    LCDx->IE = initStruct->IntEOTEn;

    switch((uint32_t)LCDx)
    {
    case ((uint32_t)LCD):
        if(initStruct->IntEOTEn) NVIC_EnableIRQ(LCD_IRQn);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: LCD_LayerInit()
* 功能说明: LCD层初始化
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
*           uint32_t layerx     要初始化的LCD层，取值LCD_LAYER_1、LCD_LAYER_2
*           LCD_LayerInitStructure * initStruct    包含LCD层相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void LCD_LayerInit(LCD_TypeDef * LCDx, uint32_t layerx, LCD_LayerInitStructure * initStruct)
{
    LCDx->L[layerx].LCR = (1                 << LCD_LCR_EN_Pos)   |
                          (0                 << LCD_LCR_CKEN_Pos) |
                          (initStruct->Alpha << LCD_LCR_ALPHA_Pos);

    LCDx->L[layerx].WHP = (initStruct->HStart << LCD_WHP_STA_Pos) |
                          (initStruct->HStop  << LCD_WHP_STP_Pos);

    LCDx->L[layerx].WVP = (initStruct->VStart << LCD_WVP_STA_Pos) |
                          (initStruct->VStop  << LCD_WVP_STP_Pos);

    LCDx->L[layerx].ADDR = initStruct->DataSource;

    LCDx->L[layerx].LLEN = (initStruct->HStop - initStruct->HStart);

    LCD->CR |= (1 << LCD_CR_VBPRELOAD_Pos);
}

/******************************************************************************************************************************************
* 函数名称: LCD_SetLayerPos()
* 功能说明: LCD层位置设定
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
*           uint32_t layerx     要设置的LCD层，取值LCD_LAYER_1、LCD_LAYER_2
*           uint16_t hstart, uint16_t hstop, uint16_t vstart, uint16_t vstop，详细说明见 LCD_LayerInitStructure
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void LCD_SetLayerPos(LCD_TypeDef * LCDx, uint32_t layerx, uint16_t hstart, uint16_t hstop, uint16_t vstart, uint16_t vstop)
{
    LCDx->L[layerx].WHP = (hstart << LCD_WHP_STA_Pos) |
                          (hstop  << LCD_WHP_STP_Pos);

    LCDx->L[layerx].WVP = (vstart << LCD_WVP_STA_Pos) |
                          (vstop  << LCD_WVP_STP_Pos);

    LCD->CR |= (1 << LCD_CR_VBPRELOAD_Pos);
}

/******************************************************************************************************************************************
* 函数名称: LCD_Start()
* 功能说明: 启动一次数据传输
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void LCD_Start(LCD_TypeDef * LCDx)
{
    LCDx->START |= (1 << LCD_START_GO_Pos);
}

/******************************************************************************************************************************************
* 函数名称: LCD_IsBusy()
* 功能说明: 是否正在进行数据传输
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
* 输    出: uint32_t          1 正在传输数据    0 数据传输已完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t LCD_IsBusy(LCD_TypeDef * LCDx)
{
    return (LCDx->START & LCD_START_GO_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: LCD_INTEn()
* 功能说明: LCD中断使能，完成指定长度的数据传输时触发中断
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void LCD_INTEn(LCD_TypeDef * LCDx)
{
    LCDx->IE = 1;
}

/******************************************************************************************************************************************
* 函数名称: LCD_INTDis()
* 功能说明: LCD中断禁止，完成指定长度的数据传输时不触发中断
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void LCD_INTDis(LCD_TypeDef * LCDx)
{
    LCDx->IE = 0;
}

/******************************************************************************************************************************************
* 函数名称: LCD_INTClr()
* 功能说明: LCD中断标志清除
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void LCD_INTClr(LCD_TypeDef * LCDx)
{
    LCDx->IF = 1;
}

/******************************************************************************************************************************************
* 函数名称: LCD_INTStat()
* 功能说明: LCD中断状态查询
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
* 输    出: uint32_t          0 未完成指定长度的数据传输   非0 完成指定长度的数据传输
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t LCD_INTStat(LCD_TypeDef * LCDx)
{
    return (LCDx->IF & 1);
}


/******************************************************************************************************************************************
* 函数名称: MPULCD_Init()
* 功能说明: MPU LCD初始化
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
*           MPULCD_InitStructure * initStruct    包含MPU LCD相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void MPULCD_Init(LCD_TypeDef * LCDx, MPULCD_InitStructure * initStruct)
{
    switch((uint32_t)LCDx)
    {
    case ((uint32_t)LCD):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_LCD_Pos);
        __NOP();__NOP();__NOP();
        break;
    }

    LCDx->CR  = (1              << LCD_CR_MPUEN_Pos) |
                (LCD_FMT_RGB565 << LCD_CR_FORMAT_Pos);  //MPU模式只支持RGB565

    LCDx->L[0].LCR |= (1 << LCD_LCR_EN_Pos);            //MPU模式下需要使能Layer1

    LCDx->MPUCR = ((initStruct->RDHoldTime    - 1) << LCD_MPUCR_RDHOLD_Pos) |
                  ((initStruct->WRHoldTime    - 1) << LCD_MPUCR_WRHOLD_Pos) |
                  ((initStruct->CSFall_WRFall - 1) << LCD_MPUCR_CS0WR0_Pos) |
                  ((initStruct->WRRise_CSRise - 1) << LCD_MPUCR_WR1CS1_Pos) |
                  ((initStruct->RDCSRise_Fall - 1) << LCD_MPUCR_RCS1_0_Pos) |
                  ((initStruct->WRCSRise_Fall - 1) << LCD_MPUCR_WCS1_0_Pos);
}

void LCD_WR_REG(LCD_TypeDef * LCDx, uint16_t reg)
{
    LCDx->MPUIR = reg;
    while(LCD_IsBusy(LCDx)) __NOP();
}

void LCD_WR_DATA(LCD_TypeDef * LCDx, uint16_t val)
{
    LCDx->MPUDR = val;
    while(LCD_IsBusy(LCDx)) __NOP();
}

void LCD_WriteReg(LCD_TypeDef * LCDx, uint16_t reg, uint16_t val)
{
    LCDx->MPUIR = reg;
    while(LCD_IsBusy(LCDx)) __NOP();

    LCDx->MPUDR = val;
    while(LCD_IsBusy(LCDx)) __NOP();
}

uint16_t LCD_ReadReg(LCD_TypeDef * LCDx, uint16_t reg)
{
    LCDx->MPUIR = reg;
    while(LCD_IsBusy(LCDx)) __NOP();

    return LCDx->MPUDR;
}

/******************************************************************************************************************************************
* 函数名称: MPULCD_DMAStart()
* 功能说明: MPU LCD DMA搬运显示数据
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
*           uint32_t * buff     要搬运的显示数据
*           uint16_t hpix       横向像素数，即每行像素数，必须是偶数
*           uint16_t vpix       纵向像素数，即行数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void MPULCD_DMAStart(LCD_TypeDef * LCDx, uint32_t * buff, uint16_t hpix, uint16_t vpix)
{
    LCDx->MPUAR = (uint32_t)buff;

    LCDx->MPULEN = ((vpix - 1) << LCD_MPULEN_VPIX_Pos) |
                   ((hpix - 1) << LCD_MPULEN_HPIX_Pos);

    LCDx->START |= (1 << LCD_START_GO_Pos);
}

/******************************************************************************************************************************************
* 函数名称: MPULCD_DMABusy()
* 功能说明: MPU LCD DMA搬运显示数据忙查询
* 输    入: LCD_TypeDef * LCDx    指定要被设置的LCD，有效值包括LCD
* 输    出: uint32_t          1 搬运中   0 搬运完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t MPULCD_DMABusy(LCD_TypeDef * LCDx)
{
    return (LCDx->START & LCD_START_GO_Msk) ? 1 : 0;
}
