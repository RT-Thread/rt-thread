/*******************************************************************************
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
/** \file ddl.h
 **
 ** DDL common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2019-10-17  1.1  Lux
 **
 ******************************************************************************/

#ifndef __DDL_H__
#define __DDL_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"
#include "board_stkhc32l19x.h"
#include "hc32l19x.h"
#include "system_hc32l19x.h"
#include "hc32l196_sysctrl.h"
#include "interrupts_hc32l19x.h"
/* C binding of definitions if building with C++ compiler                     */
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/* Macro for initializing local structures to zero                            */
/******************************************************************************/
#define DDL_ZERO_STRUCT(x)          ddl_memclr((uint8_t*)&(x), (uint32_t)(sizeof(x)))

#define DEC2BCD(x)                  ((((x)/10)<<4) + ((x)%10))
#define BCD2DEC(x)                  ((((x)>>4)*10) + ((x)&0x0F))

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
 ******************************************************************************
 ** Global Device Series List
 ******************************************************************************/
#define DDL_DEVICE_SERIES_HC32L17X       (0u)

/**
 ******************************************************************************
 ** Global Device Package List
 ******************************************************************************/
// package definitions of HC device.
#define DDL_DEVICE_PACKAGE_HC_C         (0x00u)
#define DDL_DEVICE_PACKAGE_HC_F         (0x10u)
#define DDL_DEVICE_PACKAGE_HC_J         (0x20u)
#define DDL_DEVICE_PACKAGE_HC_K         (0x30u)

/******************************************************************************/
/* User Device Setting Include file                                           */
/******************************************************************************/
#include "ddl_device.h"  // MUST be included here!

/******************************************************************************/
/* Global type definitions ('typedef')                                        */
/******************************************************************************/
/**
 ******************************************************************************
 ** \brief Level
 **
 ** Specifies levels.
 **
 ******************************************************************************/
typedef enum en_level
{
    DdlLow      = 0u,  ///< Low level  '0'
    DdlHigh     = 1u   ///< High level '1'
} en_level_t;

/**
 ******************************************************************************
 ** \brief Generic Flag Code
 **
 ** Specifies flags.
 **
 ******************************************************************************/
typedef enum en_flag
{
    DdlClr = 0u,       ///< Flag clr '0'
    DdlSet = 1u        ///< Flag set '1'
} en_stat_flag_t, en_irq_flag_t;
/******************************************************************************/
/* Global variable declarations ('extern', definition in C source)            */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
extern void ddl_memclr(void* pu8Address, uint32_t u32Count);
uint32_t Log2(uint32_t u32Val);
/**
 *******************************************************************************
 ** This hook is part of wait loops.
 ******************************************************************************/
void delay1ms(uint32_t u32Cnt);
void delay100us(uint32_t u32Cnt);
void delay10us(uint32_t u32Cnt);
void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag);
void ClrBit(uint32_t addr, uint32_t offset);
boolean_t GetBit(uint32_t addr, uint32_t offset);
#ifdef __cplusplus
}
#endif

#endif /* __DDL_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/

