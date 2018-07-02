/*****************************************************************************
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
/** \file icg.h
 **
 ** A detailed description is available at
 ** @link IcgGroup Icg description @endlink
 **
 **   - 2018-03-15  1.0  yangjp First version for Device Driver Library of Icg.
 **
 ******************************************************************************/

#ifndef __ICG_H__
#define __ICG_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup IcgGroup Initial Configuration(Icg)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief Wdt and Swdt running status after reset
 **
 ******************************************************************************/
#define WDT_AUTO_START            ((uint16_t)0x0000)  /*!< After Reset,Wdt Auto Start */
#define WDT_STOPPED               ((uint16_t)0x0001)  /*!< After Reset,Wdt Is Stopped */

#define SWDT_AUTO_START           WDT_AUTO_START
#define SWDT_STOPPED              WDT_STOPPED

/**
 *******************************************************************************
 ** \brief Wdt and Swdt Refresh Error Or Underflow Triggering Event Type
 **
 ******************************************************************************/
#define WDT_INTERRUPT_REQUEST     ((uint16_t)0x0000)  /*!< Interrupt Request  */
#define WDT_RESET_REQUEST         ((uint16_t)0x0002)  /*!< Reset Request      */

#define SWDT_INTERRUPT_REQUEST    WDT_INTERRUPT_REQUEST
#define SWDT_RESET_REQUEST        WDT_RESET_REQUEST

/**
 *******************************************************************************
 ** \brief Wdt and Swdt Count Cycles
 **
 ******************************************************************************/
#define WDT_COUNT_256CYCLE        ((uint16_t)0x0000)  /*!< 256 Cycle    */
#define WDT_COUNT_4096CYCLE       ((uint16_t)0x0004)  /*!< 4096 Cycle   */
#define WDT_COUNT_16384CYCLE      ((uint16_t)0x0008)  /*!< 16384 Cycle  */
#define WDT_COUNT_65536CYCLE      ((uint16_t)0x000C)  /*!< 65536 Cycle  */

#define SWDT_COUNT_256CYCLE       WDT_COUNT_256CYCLE
#define SWDT_COUNT_4096CYCLE      WDT_COUNT_4096CYCLE
#define SWDT_COUNT_16384CYCLE     WDT_COUNT_16384CYCLE
#define SWDT_COUNT_65536CYCLE     WDT_COUNT_65536CYCLE

/**
 *******************************************************************************
 ** \brief Wdt Clock Source(PCLK3) Division
 **
 ******************************************************************************/
#define WDT_PCLK3_DIV4            ((uint16_t)0x0020)  /*!< PCLK3/4     */
#define WDT_PCLK3_DIV64           ((uint16_t)0x0060)  /*!< PCLK3/64    */
#define WDT_PCLK3_DIV128          ((uint16_t)0x0070)  /*!< PCLK3/128   */
#define WDT_PCLK3_DIV256          ((uint16_t)0x0080)  /*!< PCLK3/256   */
#define WDT_PCLK3_DIV512          ((uint16_t)0x0090)  /*!< PCLK3/512   */
#define WDT_PCLK3_DIV1024         ((uint16_t)0x00A0)  /*!< PCLK3/1024  */
#define WDT_PCLK3_DIV2048         ((uint16_t)0x00B0)  /*!< PCLK3/2048  */
#define WDT_PCLK3_DIV8192         ((uint16_t)0x00D0)  /*!< PCLK3/8192  */

/**
 *******************************************************************************
 ** \brief SWdt Clock Source(SWDTCLK) Division
 **
 ******************************************************************************/
#define SWDT_SWDTCLK_DIV1         ((uint16_t)0x0000)  /*!< SWDTCLK/1     */
#define SWDT_SWDTCLK_DIV16        ((uint16_t)0x0040)  /*!< SWDTCLK/16    */
#define SWDT_SWDTCLK_DIV32        ((uint16_t)0x0050)  /*!< SWDTCLK/32    */
#define SWDT_SWDTCLK_DIV64        ((uint16_t)0x0060)  /*!< SWDTCLK/64    */
#define SWDT_SWDTCLK_DIV128       ((uint16_t)0x0070)  /*!< SWDTCLK/128   */
#define SWDT_SWDTCLK_DIV256       ((uint16_t)0x0080)  /*!< SWDTCLK/256   */
#define SWDT_SWDTCLK_DIV2048      ((uint16_t)0x00B0)  /*!< SWDTCLK/2048  */

/**
 *******************************************************************************
 ** \brief Wdt and Swdt Allow Refresh Percent
 **
 ******************************************************************************/
#define WDT_100PCT                ((uint16_t)0x0000)  /*!< 100%               */
#define WDT_0To25PCT              ((uint16_t)0x0100)  /*!< 0%~25%             */
#define WDT_25To50PCT             ((uint16_t)0x0200)  /*!< 25%~50%            */
#define WDT_0To50PCT              ((uint16_t)0x0300)  /*!< 0%~50%             */
#define WDT_50To75PCT             ((uint16_t)0x0400)  /*!< 50%~75%            */
#define WDT_0To25PCT_50To75PCT    ((uint16_t)0x0500)  /*!< 0%~25% & 50%~75%   */
#define WDT_25To75PCT             ((uint16_t)0x0600)  /*!< 25%~75%            */
#define WDT_0To75PCT              ((uint16_t)0x0700)  /*!< 0%~75%             */
#define WDT_75To100PCT            ((uint16_t)0x0800)  /*!< 75%~100%           */
#define WDT_0To25PCT_75To100PCT   ((uint16_t)0x0900)  /*!< 0%~25% & 75%~100%  */
#define WDT_25To50PCT_75To100PCT  ((uint16_t)0x0A00)  /*!< 25%~50% & 75%~100% */
#define WDT_0To50PCT_75To100PCT   ((uint16_t)0x0B00)  /*!< 0%~50% & 75%~100%  */
#define WDT_50To100PCT            ((uint16_t)0x0C00)  /*!< 50%~100%           */
#define WDT_0To25PCT_50To100PCT   ((uint16_t)0x0D00)  /*!< 0%~25% & 50%~100%  */
#define WDT_25To100PCT            ((uint16_t)0x0E00)  /*!< 25%~100%           */
#define WDT_0To100PCT             ((uint16_t)0x0F00)  /*!< 0%~100%            */

#define SWDT_100PCT               WDT_100PCT
#define SWDT_0To25PCT             WDT_0To25PCT
#define SWDT_25To50PCT            WDT_25To50PCT
#define SWDT_0To50PCT             WDT_0To50PCT
#define SWDT_50To75PCT            WDT_50To75PCT
#define SWDT_0To25PCT_50To75PCT   WDT_0To25PCT_50To75PCT
#define SWDT_25To75PCT            WDT_25To75PCT
#define SWDT_0To75PCT             WDT_0To75PCT
#define SWDT_75To100PCT           WDT_75To100PCT
#define SWDT_0To25PCT_75To100PCT  WDT_0To25PCT_75To100PCT
#define SWDT_25To50PCT_75To100PCT WDT_25To50PCT_75To100PCT
#define SWDT_0To50PCT_75To100PCT  WDT_0To50PCT_75To100PCT
#define SWDT_50To100PCT           WDT_50To100PCT
#define SWDT_0To25PCT_50To100PCT  WDT_0To25PCT_50To100PCT
#define SWDT_25To100PCT           WDT_25To100PCT
#define SWDT_0To100PCT            WDT_0To100PCT

/**
 *******************************************************************************
 ** \brief Wdt enable/disable Count In Sleep Mode
 **
 ******************************************************************************/
#define WDT_ENABLE_SLEEP_COUNT    ((uint16_t)0x0000)
#define WDT_DISABLE_SLEEP_COUNT   ((uint16_t)0x1000)

/**
 *******************************************************************************
 ** \brief SWdt enable/disable Count In Sleep Mode and stop mode
 **
 ******************************************************************************/
#define SWDT_ENABLE_SLEEP_STOP_COUNT   ((uint16_t)0x0000)
#define SWDT_DISABLE_SLEEP_STOP_COUNT  ((uint16_t)0x1000)

/**
 *******************************************************************************
 ** \brief icg config function on/off
 **
 ******************************************************************************/
#ifndef ICG_FUNC_ON
    #define ICG_FUNC_ON           (1u)
#endif

#ifndef ICG_FUNC_OFF
    #define ICG_FUNC_OFF          (0u)
#endif

/**
 *******************************************************************************
 ** \brief Wdt hardware start init configuration
 **
 ******************************************************************************/
/* wdt hardware start enable/disable */
#define ICG0_WDT_HARDWARE_START         ICG_FUNC_OFF

/* wdt register config */
#define ICG0_WDT_AUTS                   WDT_STOPPED
#define ICG0_WDT_ITS                    WDT_RESET_REQUEST
#define ICG0_WDT_PERI                   WDT_COUNT_65536CYCLE
#define ICG0_WDT_CKS                    WDT_PCLK3_DIV8192
#define ICG0_WDT_WDPT                   WDT_0To100PCT
#define ICG0_WDT_SLTPOFF                WDT_DISABLE_SLEEP_COUNT

/* wdt enable/disable hardware start */
#if ICG0_WDT_HARDWARE_START == ICG_FUNC_ON
    #define ICG0_WDT_REG_CONFIG         (ICG0_WDT_AUTS | ICG0_WDT_ITS | ICG0_WDT_PERI | \
                                         ICG0_WDT_CKS | ICG0_WDT_WDPT | ICG0_WDT_SLTPOFF)
#else
    #define ICG0_WDT_REG_CONFIG         ((uint16_t)0xFFFF)
#endif

/**
 *******************************************************************************
 ** \brief Swdt hardware start init configuration
 **
 ******************************************************************************/
/* swdt hardware start enable/disable */
#define ICG0_SWDT_HARDWARE_START        ICG_FUNC_OFF

/* swdt register config */
#define ICG0_SWDT_AUTS                  SWDT_STOPPED
#define ICG0_SWDT_ITS                   SWDT_RESET_REQUEST
#define ICG0_SWDT_PERI                  SWDT_COUNT_16384CYCLE
#define ICG0_SWDT_CKS                   SWDT_SWDTCLK_DIV2048
#define ICG0_SWDT_WDPT                  SWDT_0To100PCT
#define ICG0_SWDT_SLTPOFF               SWDT_DISABLE_SLEEP_STOP_COUNT

/* swdt enable/disable hardware start */
#if ICG0_SWDT_HARDWARE_START == ICG_FUNC_ON
#define ICG0_SWDT_REG_CONFIG            (ICG0_SWDT_AUTS | ICG0_SWDT_ITS | ICG0_SWDT_PERI | \
                                         ICG0_SWDT_CKS | ICG0_SWDT_WDPT | ICG0_SWDT_SLTPOFF)
#else
    #define ICG0_SWDT_REG_CONFIG        ((uint16_t)0xFFFF)
#endif

/**
 *******************************************************************************
 ** \brief ICG register configuration
 **
 ******************************************************************************/
#define ICG0_REGISTER_CONSTANT          ((((uint32_t)ICG0_WDT_REG_CONFIG)<<16) | \
                                         ((uint32_t)ICG0_SWDT_REG_CONFIG))
// todo
#define ICG1_REGISTER_CONSTANT          (0xFFFFFFFF)

#define ICG2_REGISTER_CONSTANT          (0x78706860)

#define ICG3_REGISTER_CONSTANT          (0xF8F8F8F8)

/* ICG4~15 resevd */
#define ICG4_REGISTER_CONSTANT          (0xFFFFFFFF)
#define ICG5_REGISTER_CONSTANT          (0xFFFFFFFF)
#define ICG6_REGISTER_CONSTANT          (0xFFFFFFFF)
#define ICG7_REGISTER_CONSTANT          (0xFFFFFFFF)
#define ICG8_REGISTER_CONSTANT          (0xFFFFFFFF)
#define ICG9_REGISTER_CONSTANT          (0xFFFFFFFF)
#define ICG10_REGISTER_CONSTANT         (0xFFFFFFFF)
#define ICG11_REGISTER_CONSTANT         (0xFFFFFFFF)
#define ICG12_REGISTER_CONSTANT         (0xFFFFFFFF)
#define ICG13_REGISTER_CONSTANT         (0xFFFFFFFF)
#define ICG14_REGISTER_CONSTANT         (0xFFFFFFFF)
#define ICG15_REGISTER_CONSTANT         (0xFFFFFFFF)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/


//@} // IcgGroup

#ifdef __cplusplus
}
#endif

#endif /* __ICG_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
