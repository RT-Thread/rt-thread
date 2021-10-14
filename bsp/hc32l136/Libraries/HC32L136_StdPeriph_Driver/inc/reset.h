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
/******************************************************************************/
/** \file reset.h
 **
 ** Headerfile for reset functions
 **  
 **
 ** History:
 **   - 2018-04-21   Lux     First Version
 **
 ******************************************************************************/

#ifndef __RESET_H__
#define __RESET_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup ResetGroup Reset (RST)
 **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/*******************************************************************************
 * Global definitions
 ******************************************************************************/


/**
 *******************************************************************************
 ** \brief 外设复位控制类型定义
 ** \note
 ******************************************************************************/
typedef enum
{
    ResetUart0   = 0x00000001u,             ///< 串口0
    ResetUart1   = 0x00000002u,             ///< 串口1
    ResetLpUart0 = 0x00000004u,             ///< 低功耗串口0
    ResetLpUart1 = 0x00000008u,             ///< 低功耗串口1
    ResetI2c0    = 0x00000010u,             ///< I2C0
    ResetI2c1    = 0x00000020u,             ///< I2C1    
    ResetSpi0    = 0x00000040u,             ///< SPI0   
    ResetSpi1    = 0x00000080u,             ///< SPI1   
    ResetBaseTim = 0x00000100u,             ///< BASETIM
    ResetLpTim   = 0x00000200u,             ///< LPTIM  
    ResetAdvTim  = 0x00000400u,             ///< ADVTIM 
    ResetTim3    = 0x00000800u,             ///< TIM3   
    ResetOpa     = 0x00002000u,             ///< OPA    
    ResetPca     = 0x00004000u,             ///< PCA    
    ResetAdc     = 0x00010000u,             ///< ADC    
    ResetVc      = 0x00020000u,             ///< VC     
    ResetRng     = 0x00040000u,             ///< RNG    
    ResetPcnt    = 0x00080000u,             ///< PCNT   
    ResetRtc     = 0x00100000u,             ///< RTC                    
    ResetTrim    = 0x00200000u,             ///< TRIM                   
    ResetLcd     = 0x00400000u,             ///< LCD                    
    ResetTick    = 0x01000000u,             ///< TICK                   
    ResetSwd     = 0x02000000u,             ///< SWD                    
    ResetCrc     = 0x04000000u,             ///< CRC                    
    ResetAes     = 0x08000000u,             ///< AES                    
    ResetGpio    = 0x10000000u,             ///< GPIO                   
    ResetDma     = 0x20000000u,             ///< DMA                    
    ResetDiv     = 0x40000000u,             ///< DIV                    
}en_reset_peripheral_t;



/**
 *******************************************************************************
 ** \brief 复位源（标识）显示
 **
 ** \note
 ******************************************************************************/
typedef struct
{
    uint8_t     u8Por5V     :1;         ///< 5V启动复位
    uint8_t     u8Por1_5V   :1;         ///< 1.5V启动复位
    uint8_t     u8Lvd       :1;         ///< 低电压检测复位
    uint8_t     u8Wdt       :1;         ///< 看门狗复位
    uint8_t     u8Pca       :1;         ///< PCA复位
    uint8_t     u8Lockup    :1;         ///< 系统异常复位
    uint8_t     u8Sysreq    :1;         ///< 软件复位
    uint8_t     u8RSTB      :1;         ///< RESET脚 复位
}stc_reset_cause_t;

/*******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< 获得复位源
en_result_t Reset_GetCause(stc_reset_cause_t *pstcOut);
///< 清除复位源
en_result_t Reset_Clear(stc_reset_cause_t stcval);
///< 外设模块复位控制
en_result_t Reset_SetPeripheralReset(en_reset_peripheral_t enPeri,boolean_t bFlag);

//@} // ResetGroup

#ifdef __cplusplus
#endif


#endif /* __RESET_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


