/******************************************************************************
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
/** \file exint.h
 **
 ** A detailed description is available at
 ** @link ExintGroup exint description @endlink
 **
 **   - 2018-03-12  1.0  Zhangxl First version for Device Driver Library of exint
 **
 ******************************************************************************/

#ifndef __EXINT_H__
#define __EXINT_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32f480.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup ExintGroup External Interrupts (EXINT)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief Enumeration to filter clock setting for EXTI and NMI
 **
 ** \note
 ******************************************************************************/
typedef enum
{
    Pclk3Div1   = 0,
    Pclk3Div8   = 1,
    Pclk3Div32  = 2,
    Pclk3Div64  = 3,
}en_flt_clk_t;

/**
 *******************************************************************************
 ** \brief Enumeration to NMI detection
 **
 ** \note
 ******************************************************************************/
typedef enum
{
    NmiFallingEdge = 0,         ///< Falling edge detection
    NmiRisingEdge  = 1,         ///< Rising edge detection
}en_nmi_lvl_t;

/**
 *******************************************************************************
 ** \brief Enumeration to EXTI detection
 **
 ** \note
 ******************************************************************************/
typedef enum
{
    ExIntFallingEdge = 0,       ///< Falling edge detection
    ExIntRisingEdge  = 1,       ///< Rising edge detection
    ExIntBothEdge    = 2,       ///< Falling or Rising edge detection
    ExIntLowLevel    = 3,       ///< "L" level detection
}en_exti_lvl_t;

/**
 *******************************************************************************
 ** \brief Enumeration to define an index for EXINT
 **
 ** \note
 ******************************************************************************/
typedef enum
{
    ExtiCh00    =  0,
    ExtiCh01    =  1,
    ExtiCh02    =  2,
    ExtiCh03    =  3,
    ExtiCh04    =  4,
    ExtiCh05    =  5,
    ExtiCh06    =  6,
    ExtiCh07    =  7,
    ExtiCh08    =  8,
    ExtiCh09    =  9,
    ExtiCh10    = 10,
    ExtiCh11    = 11,
    ExtiCh12    = 12,
    ExtiCh13    = 13,
    ExtiCh14    = 14,
    ExtiCh15    = 15,
    ExtiChMax
}en_exti_ch_t;

/**
 *******************************************************************************
 ** \brief External Interrupt configuration
 **
 ** \note The EXINT configuration
 ******************************************************************************/
typedef struct stc_exint_config
{
    en_exti_ch_t      enExitCh;         ///< External Int CH.0~15 ref@ en_exti_ch_t
    boolean_t         bFltEn;           ///< TRUE: Enable filter function
    en_flt_clk_t      enFltClk;         ///< Filter clock, ref@en_flt_clk_t for details
    en_exti_lvl_t     enExtiLvl;        ///< Detection level, ref@en_exti_lvl_t for details
    func_ptr_t        pfnExtiCallback;  ///< Callback pointers
}stc_exint_config_t;

/**
 *******************************************************************************
 ** \brief Enumeration to NMI Trigger source
 **
 ** \note
 ******************************************************************************/
typedef enum
{
    NmiSrcSwdt     = 1ul << 0,
    NmiSrcWdt      = 1ul << 1,
    NmiSrcVdu1     = 1ul << 2,
    NmiSrcVdu2     = 1ul << 3,
    NmiSrcSRCStop  = 1ul << 5,
    NmiSrcMRCStop  = 1ul << 6,
    NmiSrcNmi      = 1ul << 7,
    NmiSrcSramPE   = 1ul << 8,
    NmiSrcSramDE   = 1ul << 9,
    NmiSrcMpu      = 1ul << 11,
}en_nmi_src_t;

/**
 *******************************************************************************
 ** \brief NMI configuration
 **
 ** \note The NMI configuration
 ******************************************************************************/
typedef struct
{
    boolean_t       bFltEn;             ///< TRUE: Enable filter function
    en_flt_clk_t    enFltClk;           ///< Filter clock, ref@en_flt_clk_t for details
    en_nmi_lvl_t    enNmiLvl;           ///< Detection level, ref@en_nmi_lvl_t for details
    uint8_t         u16NmiSrc;          ///< NMI trigger source, ref@en_nmi_src_t for details
    func_ptr_t      pfnNmiCallback;     ///< Callback pointers
}stc_nmi_config_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
extern en_result_t Exint_Init(stc_exint_config_t stcConfig);

extern en_result_t Nmi_Init(stc_nmi_config_t stcNmiConfig);

extern en_result_t Nmi_DeInit(void);

extern uint16_t Nmi_IrqFlgGet(void);

extern en_result_t Nmi_IrqFlgClr(uint16_t u16NmiSrc);

//@} // ExintGroup

#ifdef __cplusplus
}
#endif

#endif /* __EXINT_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
