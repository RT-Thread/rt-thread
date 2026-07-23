/*******************************************************************************
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
/** \file interrupts_hc32l17x.h
 **
 ** Interrupt common define.
 ** @link IRQGroup Some description @endlink
 **
 **   - 2019-03-01  1.0  Lux     First version.
 **
 ******************************************************************************/
#ifndef __INTERRUPTS_HC32L17x_H__
#define __INTERRUPTS_HC32L17x_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "hc32l196_ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
#define DDL_IRQ_LEVEL_DEFAULT                   3u

//<<此选项会打开interrupt_hc32xxx.c中的中断回调函数，用户如果需要实现中断服务函数，
//<<可在源码文件中定义该文件中用"__WEAK"声明的同名中断服务函数即可。
#define INT_CALLBACK_ON                                  1u  //<<(默认值)
//<<此选项会关闭interrupt_hc32xxx.c中的中断回调函数，此时用户可在该文件中自行定义中断服务函数的实现。
#define INT_CALLBACK_OFF                                 0u
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
#define INT_CALLBACK_PORTA                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTB                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTC                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTD                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTE                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTF                       INT_CALLBACK_ON
#define INT_CALLBACK_DMAC                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM3                        INT_CALLBACK_ON
#define INT_CALLBACK_UART0                       INT_CALLBACK_ON
#define INT_CALLBACK_UART1                       INT_CALLBACK_ON
#define INT_CALLBACK_UART2                       INT_CALLBACK_ON
#define INT_CALLBACK_UART3                       INT_CALLBACK_ON
#define INT_CALLBACK_LPUART0                     INT_CALLBACK_ON
#define INT_CALLBACK_LPUART1                     INT_CALLBACK_ON
#define INT_CALLBACK_SPI0                        INT_CALLBACK_ON
#define INT_CALLBACK_SPI1                        INT_CALLBACK_ON
#define INT_CALLBACK_I2C0                        INT_CALLBACK_ON
#define INT_CALLBACK_I2C1                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM0                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM1                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM2                        INT_CALLBACK_ON
#define INT_CALLBACK_LPTIM0                      INT_CALLBACK_ON
#define INT_CALLBACK_LPTIM1                      INT_CALLBACK_ON
#define INT_CALLBACK_TIM4                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM5                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM6                        INT_CALLBACK_ON
#define INT_CALLBACK_PCA                         INT_CALLBACK_ON
#define INT_CALLBACK_WDT                         INT_CALLBACK_ON
#define INT_CALLBACK_RTC                         INT_CALLBACK_ON
#define INT_CALLBACK_ADC                         INT_CALLBACK_ON
#define INT_CALLBACK_DAC                         INT_CALLBACK_ON
#define INT_CALLBACK_PCNT                        INT_CALLBACK_ON
#define INT_CALLBACK_VC0                         INT_CALLBACK_ON
#define INT_CALLBACK_VC1                         INT_CALLBACK_ON
#define INT_CALLBACK_VC2                         INT_CALLBACK_ON
#define INT_CALLBACK_LVD                         INT_CALLBACK_ON
#define INT_CALLBACK_LCD                         INT_CALLBACK_ON
#define INT_CALLBACK_FLASH                       INT_CALLBACK_ON
#define INT_CALLBACK_RAM                         INT_CALLBACK_ON
#define INT_CALLBACK_CLKTRIM                     INT_CALLBACK_ON
 
 
/**
 *******************************************************************************
 ** \brief 中断优先级数据类型定义
 ** \note
 ******************************************************************************/
typedef enum en_irq_level
{
    IrqLevel0  = 0u,               ///< 优先级0
    IrqLevel1  = 1u,               ///< 优先级1
    IrqLevel2  = 2u,               ///< 优先级2
    IrqLevel3  = 3u,               ///< 优先级3
} en_irq_level_t; 


/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< 系统中断使能开关
extern void EnableNvic(IRQn_Type enIrq, en_irq_level_t enLevel, boolean_t bEn);


#ifdef __cplusplus
}
#endif


#endif /* __INTERRUPTS_HC32L19x_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
