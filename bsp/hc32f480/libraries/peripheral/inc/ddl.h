/*******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file ddl.h
 **
 ** A detailed description is available at
 ** @link DdlGroup Ddl common description @endlink
 **
 **   - 2018-1-15  1.0  Zhangxl First version for Device Driver Library of Ddl
 **     common part.
 **
 ******************************************************************************/

#ifndef __DDL_H__
#define __DDL_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <string.h>
#include "base_types.h"
#include "system_hc32f480.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup DdlGroup Device Driver Library (DDL)
 **
 ******************************************************************************/

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief Level
 **
 ** \note Specifies levels.
 **
 ******************************************************************************/
typedef enum en_level
{
    DdlLow = 0u,                        ///< Low level  '0'
    DdlHigh = 1u                        ///< High level '1'
} en_level_t;

/**
 *******************************************************************************
 ** \brief Generic Flag Code
 **
 ** \note Specifies flags.
 **
 ******************************************************************************/
typedef enum en_flag
{
    DdlClr = 0u,                        ///< Flag clr '0'
    DdlSet = 1u                         ///< Flag set '1'
} en_stat_flag_t, en_irq_flag_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! Memory clear */
#define DDL_ZERO_STRUCT(x)              memset((void*)&(x), 0x00, (sizeof(x)))

/*! Decimal to BCD */
#define DEC2BCD(x)                      ((((x) / 10) << 4) + ((x) % 10))

/*! BCD to decimal */
#define BCD2DEC(x)                      ((((x) >> 4) * 10) + ((x) & 0x0F))

/*! Returns the minimum value out of two values */
#define MIN(x, y)                       ((x) < (y) ? (x) : (y))

/*! Returns the maximum value out of two values */
#define MAX(x, y)                       ((x) > (y) ? (x) : (y))

/*! Returns the dimension of an array */
#define ARRAY_SZ(X)                     (sizeof(X) / sizeof(X[0]))

/*! Check if it is a functional state */
#define IS_FUNCTIONAL_STATE(state)      (((state) == Disable) || ((state) == Enable))

#define BIT_SET(value,bit)              ((value) |= (bit))

#define BIT_CLEAR(value,bit)            ((value) &= ~(bit))

#define BIT_READ(value,bit)             ((value) & (bit))

#define BIT_VALUE(index)                (1 << index)

/*! Ddl assert, you can add your own assert functions by implement the function
Ddl_AssertHook definition follow the function Ddl_AssertHook declaration */
#ifdef __DEBUG

#define DDL_ASSERT(x)                   ((x) ? (void)0 : Ddl_AssertHandler((uint8_t *)__FILE__, __LINE__))

void Ddl_AssertHandler(uint8_t* file, uint32_t line);
#else

#define DDL_ASSERT(x)                   (void)(x)

#endif

/**
 *******************************************************************************
 ** \brief IRQ name definition for HC32F_M14X series
 ******************************************************************************/
#define CSV_IRQHandler(void)               IRQ000_Handler(void) ///< CSV
#define SWDT_IRQHandler(void)              IRQ001_Handler(void) ///< SWDT
#define LVD_IRQHandler(void)               IRQ002_Handler(void) ///< LVD
#define TIMER4PWM_EMI_IRQHandler(void)     IRQ003_Handler(void) ///< Timer4
#define EXTI07_IRQHandler(void)            IRQ004_Handler(void) ///< External interrupt ch.0-7
#define EXTI815_IRQHandler(void)           IRQ005_Handler(void) ///< External interrupt ch.8-15
#define DTIM_IRQHandler(void)              IRQ006_Handler(void) ///< Dual timer
//                                         IRQ007_Handler(void) ///< Reserved
//                                         IRQ008_Handler(void) ///< Reserved
//                                         IRQ009_Handler(void) ///< Reserved
//                                         IRQ010_Handler(void) ///< Reserved
//                                         IRQ011_Handler(void) ///< Reserved
//                                         IRQ012_Handler(void) ///< Reserved
//                                         IRQ013_Handler(void) ///< Reserved
//                                         IRQ014_Handler(void) ///< Reserved
#define MSC4RX_IRQHandler(void)            IRQ015_Handler(void) ///< MSC ch.4, RX
#define MSC4TX_IRQHandler(void)            IRQ016_Handler(void) ///< MSC ch.4, TX
#define MSC5RX_IRQHandler(void)            IRQ017_Handler(void) ///< MSC ch.5, RX
#define MSC5TX_IRQHandler(void)            IRQ018_Handler(void) ///< MSC ch.5, TX
#define MSC6RX_DMAC0_IRQHandler(void)      IRQ019_Handler(void) ///< MSC ch.6, RX, DMAC ch. 0
#define MSC6TX_DMAC1_IRQHandler(void)      IRQ020_Handler(void) ///< MSC ch.6, TX, DMAC ch. 1
//                                         IRQ021_Handler(void) ///< Reserved
//                                         IRQ022_Handler(void) ///< Reserved
//                                         IRQ023_Handler(void) ///< Reserved
#define OSC_CC_RP_IRQHandler(void)         IRQ024_Handler(void) ///< OSC / Clock Counter / RAM parity
#define ADC_IRQHandler(void)               IRQ025_Handler(void) ///< ADC
#define VC_IRQHandler(void)                IRQ026_Handler(void) ///< VC
//                                         IRQ027_Handler(void) ///< Reserved
#define TIM4CNT_IRQHandler(void)           IRQ028_Handler(void) ///< Timer4 zero, peak detect
//                                         IRQ029_Handler(void) ///< Reserved
#define TIM4OCO_IRQHandler(void)           IRQ030_Handler(void) ///< Timer4 output match
#define CTIM03_FLASH_IRQHandler(void)      IRQ031_Handler(void) ///< CT ch.0-3, Flash

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

/* Initialize uart for printf */
extern void Ddl_UartInit(void);

/* A approximate delay */
extern void Ddl_Delay1ms(uint32_t u32Cnt);

//@} // DdlGroup

#ifdef __cplusplus
}
#endif

#endif /* __DDL_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
