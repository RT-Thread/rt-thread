/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
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
/******************************************************************************/
/** \file lcd.h
 **
 ** Header file for lcd Converter functions
 ** @link LCD Group Some description @endlink
 **
 **   - 2019-04-02      First Version
 **
 ******************************************************************************/
#ifndef __LCD_H__
#define __LCD_H__
/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"

/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

/**
******************************************************************************
** \brief LCD bias源选择
*****************************************************************************/
 typedef enum
 {
    LcdInResHighPower = 6,//内部电阻分压，大功耗模式
    LcdInResLowPower  = 4,//内部电阻分压，小功耗模式
    LcdInResMidPower  = 2,//内部电阻分压，中功耗模式
    LcdExtCap          = 1,//电容分压模式，需要外部电路配合
    LcdExtRes          = 0,//外部电阻模式，需要外部电路配合
 }en_lcd_biassrc_t;

/**
******************************************************************************
** \brief LCD duty选择                  LCD_CR0    Duty
*****************************************************************************/
 typedef enum
 {
    LcdStatic = 0u,        // 静态显示
    LcdDuty2  = 1u,        // 1/2duty
    LcdDuty3  = 2u,        // 1/3duty
    LcdDuty4  = 3u,        // 1/4duty
    LcdDuty6  = 5u,        // 1/6duty
    LcdDuty8  = 7u,        // 1/8duty
 }en_lcd_duty_t;

/**
******************************************************************************
** \brief LCD bias配置位                 LCD_CR0    Bias
*****************************************************************************/
 typedef enum
 {
    LcdBias3 = 0u,        // 1/3 BIAS
    LcdBias2 = 1u,        // 1/2 BIAS
 }en_lcd_bias_t;

/**
******************************************************************************
** \brief LCD 电压泵时钟频率选择         LCD_CR0    CpClk
*****************************************************************************/
 typedef enum
 {
    LcdClk2k  = 0u,        // 2k
    LcdClk4k  = 1u,        // 4k
    LcdClk8k  = 2u,        // 8k
    LcdClk16k = 3u         // 16k
 }en_lcd_cpclk_t;

/**
******************************************************************************
** \brief LCD 扫描频率选择                LCD_CR0    LcdClk
*****************************************************************************/
 typedef enum
 {
    LcdClk64hz   = 0u,    // 64hz
    LcdClk128hz  = 1u,    // 128hz
    LcdClk256hz  = 2u,    // 256hz
    LcdClk512hz  = 3u     // 512hz
 }en_lcd_scanclk_t;

/**
******************************************************************************
** \brief LCD 使能控制                    LCD_CR0    EN
*****************************************************************************/
typedef enum
{
    LcdEnable   =1u,    //LCD使能
    LcdDisable  =0u     //LCD禁止
}en_lcd_en_t;

/**
 ******************************************************************************
 ** \brief LCD显示模式               LCD_CR1    Mode
 *****************************************************************************/
 typedef enum
 {
    LcdMode0 = 0,///<模式0
    LcdMode1 = 1,///<模式1
 }en_lcd_dispmode_t;

 /**
 ******************************************************************************
 ** \brief LCD时钟源选择             LCD_CR1    ClkSrc
 *****************************************************************************/
 typedef enum
 {
    LcdXTL = 1,///<外部XTL
    LcdRCL = 0,///<内部RCL
 }en_lcd_clk_t;


/**
******************************************************************************
** \brief LCD CR1寄存器的使能位、标志位
*****************************************************************************/
typedef enum
{
    LcdBlinkEn   = 6u,  //LCD闪屏配置位
    LcdIe        = 9u,  //LCD 中断使能位
    LcdDmaEn     = 10u, //LCD DMA硬件触发使能位
}en_cr1_t;

/**
 ******************************************************************************
 ** \brief LCD显示SEG COM端口寄存器的配置
 *****************************************************************************/
typedef struct
{
    uint32_t u32Seg0_31;      ///<SEG0-31配置
    union{
        uint32_t seg32_51_com0_8;
        struct
        {
            uint32_t Seg32_35     :4;
            uint32_t Seg36Com7    :1;
            uint32_t Seg37Com6    :1;
            uint32_t Seg38Com5    :1;
            uint32_t Seg39Com4    :1;
            uint32_t Seg40        :1;
            uint32_t Seg41        :1;
            uint32_t Seg42        :1;
            uint32_t Seg43        :1;
            uint32_t Mux          :1;
            uint32_t Seg44        :1;
            uint32_t Seg45        :1;
            uint32_t Seg46        :1;
            uint32_t Seg47        :1;
            uint32_t Seg48        :1;
            uint32_t Seg49        :1;
            uint32_t Seg50        :1;
            uint32_t Seg51        :1;
            uint32_t Com0_3       :4;
        }segcom_bit;
    }stc_seg32_51_com0_8_t;
}stc_lcd_segcom_t;

/**
 ******************************************************************************
 ** \brief LCD端口配置参数
 *****************************************************************************/
typedef struct stc_lcd_segcompara
{
    en_lcd_duty_t LcdDuty;       ///<占空比
    en_lcd_biassrc_t LcdBiasSrc; ///<时钟源
    uint8_t u8MaxSeg;             ///<最大SEG口
}stc_lcd_segcompara_t;

/**
 ******************************************************************************
 ** \brief I2C初始化配置结构
 *****************************************************************************/
typedef struct
{
    en_lcd_biassrc_t    LcdBiasSrc;    //偏置源选择
    en_lcd_duty_t       LcdDuty;       //duty配置选择
    en_lcd_bias_t       LcdBias;       //偏压选择
    en_lcd_cpclk_t      LcdCpClk;      //电压泵时钟频率选择
    en_lcd_scanclk_t    LcdScanClk;    //扫描频率选择
    en_lcd_dispmode_t   LcdMode;       //显示模式选择
    en_lcd_clk_t        LcdClkSrc;     //时钟源选择
    en_lcd_en_t         LcdEn;         //LCD使能
}stc_lcd_cfg_t;

/*******************************************************************************
 ** \brief lcd相关函数声明
 ******************************************************************************/

extern boolean_t Lcd_GetItStatus(void);
extern void Lcd_ClearItPendingBit(void);
extern en_result_t Lcd_GetSegCom(stc_lcd_segcompara_t *pstcSegComPara,stc_lcd_segcom_t *pstcSegCom);
extern void Lcd_SetSegCom(stc_lcd_segcom_t *pstcSegCom);
extern void Lcd_Init(stc_lcd_cfg_t *pstcLcdCfg);
extern void Lcd_FullDisp(void);
extern void Lcd_ClearDisp(void);
extern en_result_t Lcd_WriteRam(uint8_t u8Row,uint32_t u32Data);

 
//@} // LCDGroup

#ifdef __cplusplus
#endif

#endif /* __LCD_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


