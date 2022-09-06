/******************************************************************************************************************************************
* 文件名称: SWM320_lcd.c
* 功能说明: SWM320单片机的LCD功能驱动库
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
#include "SWM320_lcd.h"

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
        SYS->CLKEN |= (0x01 << SYS_CLKEN_LCD_Pos);
        break;
    }

    LCDx->CR0 = ((initStruct->HnPixel - 1) << LCD_CR0_HPIX_Pos) |
                ((initStruct->VnPixel - 1) << LCD_CR0_VPIX_Pos) |
                (initStruct->ClkAlways << LCD_CR0_DCLK_Pos) |
                (initStruct->HsyncWidth << LCD_CR0_HLOW_Pos);

    LCDx->CR1 = ((initStruct->Hfp - 1) << LCD_CR1_HFP_Pos)  |
                ((initStruct->Hbp - 1) << LCD_CR1_HBP_Pos)  |
                ((initStruct->Vfp - 1) << LCD_CR1_VFP_Pos)  |
                ((initStruct->Vbp - 1) << LCD_CR1_VBP_Pos)  |
                (initStruct->ClkDiv << LCD_CR1_DCLKDIV_Pos) |
                (initStruct->SamplEdge << LCD_CR1_DCLKINV_Pos);

    LCDx->IE = 1;
    LCDx->IF = 1;   //清除标志
    if(initStruct->IntEOTEn) LCD_INTEn(LCDx);
    else                     LCD_INTDis(LCDx);

    switch((uint32_t)LCDx)
    {
    case ((uint32_t)LCD):
        if(initStruct->IntEOTEn)
        {
            NVIC_EnableIRQ(LCD_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(LCD_IRQn);
        }
        break;
    }
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
    LCDx->START |= (1 << LCD_START_GO_Pos) | (1 << LCD_START_BURST_Pos);
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
    LCDx->IM = 0;
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
    LCDx->IM = 1;
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
* 输    出: uint32_t          1 完成指定长度的数据传输    0 未完成指定长度的数据传输
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t LCD_INTStat(LCD_TypeDef * LCDx)
{
    return (LCDx->IF & 0x01) ? 1 : 0;
}
