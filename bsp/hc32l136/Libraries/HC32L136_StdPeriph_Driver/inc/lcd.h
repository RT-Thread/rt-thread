/******************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file lcd.h
 **
 ** Headerfile for LCD functions
 **  
 **
 ** History:
 **   - 2018-05-03   CJ    First Version
 **
 *****************************************************************************/

#ifndef __LCD_H__
#define __LCD_H__

#include "ddl.h"
#include "interrupts_hc32l136.h"

/**
 *******************************************************************************
 ** \def group LCD Group LCD
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
#define LCDFULLWRITE  0XFFFFFFFF ///<LCD全显
#define LCDFULLCLEAR  0X00000000 ///<LCD全清 
#define LCDRAM0_7SIZE 31 
#define LCDRAM8_FSIZE 7
#define LCDRAMSIZE    0x0F
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
 /**
 ******************************************************************************
 ** \brief LCD bias源选择
 *****************************************************************************/
 typedef enum en_lcd_biassrc
 {
    LcdInRes_High = 6,///<内部电阻分压，大功耗模式
    LcdInRes_Low  = 4,///<内部电阻分压，小功耗模式 
    LcdInRes_Mid  = 2,///<内部电阻分压，中功耗模式 
    LcdExtCap     = 1,///<外部电容分压模式
    LcdExtRes     = 0,///<外部电阻模式
 }en_lcd_biassrc_t;
  /**
 ******************************************************************************
 ** \brief LCD duty源选择
 *****************************************************************************/
 typedef enum en_lcd_duty
 {
    LcdStatic   = 0,///<静态
    LcdDuty2  = 1,///<1/2duty
    LcdDuty3  = 2,///<1/3duty 
    LcdDuty4  = 3,///<1/4duty
    LcdDuty6  = 5,///<1/6duty
    LcdDuty8  = 7,///<1/8duty
 }en_lcd_duty_t;
/**
 ******************************************************************************
 ** \brief LCD bias配置
 *****************************************************************************/
 typedef enum en_lcd_bias
 {
    LcdBias3 = 0,///<1/3 BIAS
    LcdBias2 = 1,///<1/2 BIAS
 }en_lcd_bias_t;
 /**
 ******************************************************************************
 ** \brief LCD 电压泵时钟频率配置
 *****************************************************************************/
 typedef enum en_lcd_cpclk
 {
    LcdClk2k  = 0,///<2k
    LcdClk4k  = 1,///<4k
    LcdClk8k  = 2,///<8k
    LcdClk16k = 3,///<16k
 }en_lcd_cpclk_t;
  /**
 ******************************************************************************
 ** \brief LCD 扫描频率配置
 *****************************************************************************/
 typedef enum en_lcd_scanclk
 {
    LcdClk64hz   = 0,///<64hz
    LcdClk128hz  = 1,///<128hz
    LcdClk256hz  = 2,///<256hz
    LcdClk512hz  = 3,///<512hz
 }en_lcd_scanclk_t;
/**
 ******************************************************************************
 ** \brief LCD功能使能
 *****************************************************************************/
 typedef enum en_lcd_func
 {
    LcdEn      = 0,///<模块使能
    LcdBlinkEn = 1,///<LCD闪屏使能
 }en_lcd_func_t;
/**
 ******************************************************************************
 ** \brief LCD显示模式
 *****************************************************************************/
 typedef enum en_lcd_dispmode
 {
    LcdMode0 = 0,///<模式0
    LcdMode1 = 1,///<模式1
 }en_lcd_dispmode_t;
/**
 ******************************************************************************
 ** \brief LCD时钟源选择
 *****************************************************************************/
 typedef enum en_lcd_clk
 {
    LcdXTL = 1,///<外部32k
    LcdRCL = 0,///<内部32k
 }en_lcd_clk_t;
/**
 ******************************************************************************
 ** \brief LCD显示SEG COM端口配置
 *****************************************************************************/
typedef struct stc_lcd_segcom
{
    uint32_t u32Seg0_31;      ///<SEG0-31配置
    boolean_t bMux;           ///<SEG32-35
    uint8_t u8Com0_3;         ///<COM0-3配置
    union Seg32_39VLcdCom7_4  ///<Seg32_39/Com7_4配置
    {
        uint8_t SegVLcdCom;
        struct
        {
            uint8_t Seg39Com4   :1;
            uint8_t Seg38Com5   :1;
            uint8_t Seg37Com6   :1;
            uint8_t Seg36Com7   :1;
            uint8_t Seg35LcdH   :1;
            uint8_t Seg34Lcd3   :1;
            uint8_t Seg33Lcd2   :1;
            uint8_t Seg32Lcd1   :1;
            
        }Bits;
    }Seg32_39VLcdCom7_4_t;
}stc_lcd_segcom_t;
/**
 ******************************************************************************
 ** \brief LCD端口配置参数
 *****************************************************************************/
typedef struct stc_lcd_segcompara
{
    en_lcd_duty_t enDuty;       ///<占空比
    en_lcd_biassrc_t enBiasSrc; ///<时钟源
    uint8_t u8MaxSeg;           ///<最大SEG口
}stc_lcd_segcompara_t;
/**
 ******************************************************************************
 ** \brief I2C初始化配置结构
 *****************************************************************************/
typedef struct stc_lcd_config
{
    en_lcd_biassrc_t enBiasSrc;  ///<Bias源选择
    en_lcd_duty_t  enDuty;       ///<占空比选择
    en_lcd_bias_t enBias;        ///bias配置
    en_lcd_cpclk_t enCpClk;      ///<电压泵时钟频率选择
    en_lcd_scanclk_t enScanClk;  ///<扫描频率选择
    en_lcd_dispmode_t enDispMode;///<显示模式选择
    en_lcd_clk_t enClk;          ///<模块clk选择
    boolean_t       bTouchNvic;  ///<是否使能NVIC
}stc_lcd_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
 //LCD初始化函数
 en_result_t LCD_Init(stc_lcd_config_t *pstcLcdCfg);
  //lcd模块关闭函数
 en_result_t LCD_DeInit(void);
  //lcd 时钟源选择函数
 en_result_t LCD_SetClkSrc(en_lcd_clk_t enLcdClk);
 //lcd bias源选择函数
 en_result_t LCD_SelBiasSrc(en_lcd_biassrc_t enBiasSrc);
 //lcd duty配置函数
 en_result_t LCD_SetDuty(en_lcd_duty_t enDuty);
 //lcd bias配置函数
 en_result_t LCD_SetBias(en_lcd_bias_t enBias);
 //lcd电压泵时钟频率选择
 en_result_t LCD_SelCpClk(en_lcd_cpclk_t enCpClk);
 //lcd扫描频率选择
 en_result_t LCD_SelScanClk(en_lcd_scanclk_t enScanClk);
 //lcd 功能使能禁止函数
 en_result_t LCD_EnFunc(en_lcd_func_t enFunc,boolean_t bFlag);
 //lcd显示模式函数
 en_result_t LCD_SetDispMode(en_lcd_dispmode_t enDispMode);
 //lcd对比度设置
 en_result_t LCD_SetContrast(uint8_t u8Contrast);
 //lcd闪屏计数器设置
 en_result_t LCD_SetBlinkCnt(uint8_t u8BlinkCnt);
  //lcd中断清除
 en_result_t LCD_ClrIntState(void);
 //LCD运行模式获取端口配置
 en_result_t LCD_GetSegCom(stc_lcd_segcompara_t *pstcSegComPara,stc_lcd_segcom_t *pstcSegCom);
 //lcd segcom端口配置
 en_result_t LCD_SetSegCom(stc_lcd_segcom_t *pstcSegCom);
 //lcd全显
 en_result_t LCD_FullDisp(void);
 //lcd全清
 en_result_t LCD_ClearDisp(void);
 //lcd写RAM函数
 en_result_t LCD_WriteRam(uint16_t u16Row, uint32_t u32List, boolean_t bData);
 en_result_t LCD_WriteRam0_7Int32(uint8_t u8Row,uint32_t u32Data);
 en_result_t LCD_WriteRam8_FInt8(uint8_t u8Row,uint8_t u8Data);

 
//@} // LCDGroup

#ifdef __cplusplus
#endif

#endif /* __LCD_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


