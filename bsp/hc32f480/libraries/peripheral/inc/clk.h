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
/** \file clk.h
 **
 ** A detailed description is available at
 ** @link ClkGroup Clock description @endlink
 **
 **   - 2018-03-09  1.0  Jason First version for Device Driver Library of Clock.
 **
 ******************************************************************************/

#ifndef __CLK_H__
#define __CLK_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup ClkGroup Clock Manage Unit(CMU)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief  The system clock source.
 **
 ******************************************************************************/
typedef enum en_clk_sys_source
{
    ClkSysSrcHRC                    = 0u,   ///< The system clock source is HRC.
    ClkSysSrcMRC                    = 1u,   ///< The system clock source is MRC.
    ClkSysSrcLRC                    = 2u,   ///< The system clock source is LRC.
    ClkSysSrcXTAL                   = 3u,   ///< The system clock source is XTAL.
    ClkSysSrcXTAL32                 = 4u,   ///< The system clock source is XTAL32.
    CLKSysSrcMPLL                   = 5u,   ///< The system clock source is MPLL.
} en_clk_sys_source_t;

/**
 *******************************************************************************
 ** \brief  The pll clock source.
 **
 ******************************************************************************/
typedef enum en_clk_pll_source
{
    ClkPllSrcXTAL                   = 0u,   ///< The pll clock source is XTAL.
    ClkPllSrcHRC                    = 1u,   ///< The pll clock source is HRC.
} en_clk_pll_source_t;

/**
 *******************************************************************************
 ** \brief  The usb clock source.
 **
 ******************************************************************************/
typedef enum en_clk_usb_source
{
    ClkUsbSrcSysDiv2                = 2u,   ///< The usb clock source is 1/2 system clock.
    ClkUsbSrcSysDiv3                = 3u,   ///< The usb clock source is 1/3 system clock.
    ClkUsbSrcSysDiv4                = 4u,   ///< The usb clock source is 1/4 system clock.
    ClkUsbSrcMpllq                  = 5u,   ///< The usb clock source is MPLLQ.
    ClkUsbSrcUpllp                  = 6u,   ///< The usb clock source is UPLLP.
    ClkUsbSrcUpllq                  = 8u,   ///< The usb clock source is UPLLQ.
} en_clk_usb_source_t;

/**
 *******************************************************************************
 ** \brief  The adc clock source.
 **
 ******************************************************************************/
typedef enum en_clk_adc_source
{
    ClkAdcSrcSysDiv                 = 0u,   ///< The adc clock source is division from system clock.
    ClkAdcSrcMpllq                  = 4u,   ///< The adc clock source is MPLLQ.
    ClkAdcSrcUpllp                  = 5u,   ///< The adc clock source is UPLLP.
    ClkAdcSrcUpllq                  = 6u,   ///< The adc clock source is UPLLQ.
} en_clk_adc_source_t;

/**
 *******************************************************************************
 ** \brief  The clock output source.
 **
 ******************************************************************************/
typedef enum en_clk_output_source
{
    ClkOutputSrcHrc                 = 0u,   ///< The clock output source is HRC
    ClkOutputSrcMrc                 = 1u,   ///< The clock output source is MRC.
    ClkOutputSrcLrc                 = 2u,   ///< The clock output source is LRC.
    ClkOutputSrcXtal                = 3u,   ///< The clock output source is XTAL.
    ClkOutputSrcXtal32              = 4u,   ///< The clock output source is XTAL32
    ClkOutputSrcRtcLrc              = 5u,   ///< The clock output source is RTCLRC.
    ClkOutputSrcMpllp               = 6u,   ///< The clock output source is MPLLP.
    ClkOutputSrcUpllp               = 7u,   ///< The clock output source is UPLLP.
    ClkOutputSrcMpllq               = 8u,   ///< The clock output source is MPLLQ
    ClkOutputSrcUpllq               = 9u,   ///< The clock output source is UPLLQ.
    ClkOutputSrcSysclk              = 11u,  ///< The clock output source is system clock.
} en_clk_output_source_t;

/**
 *******************************************************************************
 ** \brief  The clock frequence source for measure or reference.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_source
{
    ClkFcmSrcXtal                   = 0u,   ///< The clock frequence measure or reference source is XTAL
    ClkFcmSrcXtal32                 = 1u,   ///< The clock frequence measure or reference source is XTAL32.
    ClkFcmSrcHrc                    = 2u,   ///< The clock frequence measure or reference source is HRC.
    ClkFcmSrcLrc                    = 3u,   ///< The clock frequence measure or reference source is LRC.
    ClkFcmSrcSwdtrc                 = 4u,   ///< The clock frequence measure or reference source is SWDTRC
    ClkFcmSrcPclk1                  = 5u,   ///< The clock frequence measure or reference source is PCLK1.
    ClkFcmSrcUpllp                  = 6u,   ///< The clock frequence measure or reference source is UPLLP.
    ClkFcmSrcMrc                    = 7u,   ///< The clock frequence measure or reference source is MRC.
    ClkFcmSrcMpllp                  = 8u,   ///< The clock frequence measure or reference source is MPLLP.
    ClkFcmSrcRtcLrc                 = 9u,   ///< The clock frequence measure or reference source is RTCLRC.
} en_clk_fcm_intref_source_t,en_clk_fcm_measure_source_t;

/**
 *******************************************************************************
 ** \brief  The clock flag status.
 **
 ******************************************************************************/
typedef enum en_clk_flag
{
    ClkFlagHRCRdy                   = 0u,   ///< The clock flag is HRC ready.
    ClkFlagXTALRdy                  = 1u,   ///< The clock flag is XTAL ready.
    ClkFlagMPLLRdy                  = 2u,   ///< The clock flag is MPLL ready.
    ClkFlagUPLLRdy                  = 3u,   ///< The clock flag is UPLL ready.
    ClkFlagXTALStoppage             = 4u,   ///< The clock flag is XTAL stoppage.
} en_clk_flag_t;

/**
 *******************************************************************************
 ** \brief  The clock frequence measure flag status.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_flag
{
    ClkFcmFlagOvf                   = 0u,   ///< The clock frequence flag is counter overflow.
    ClkFcmFlagMendf                 = 1u,   ///< The clock frequence flag is end of measurement.
    ClkFcmFlagErrf                  = 2u,   ///< The clock frequence flag is frequence abnormal.
} en_clk_fcm_flag_t;

/**
 *******************************************************************************
 ** \brief  The source of xtal.
 **
 ******************************************************************************/
typedef enum en_clk_xtal_mode
{
    ClkXtalModeOsc                  = 0u,   ///< Use external high speed osc as source.
    ClkXtalModeExtClk               = 1u,   ///< Use external clk as source.
} en_clk_xtal_mode_t;

/**
 *******************************************************************************
 ** \brief  The drive capability of xtal.
 **
 ******************************************************************************/
typedef enum en_clk_xtal_drv
{
    ClkXtalHighDrv                  = 0u,   ///< High drive capability.20MHz~24MHz.
    ClkXtalMidDrv                   = 1u,   ///< Midlle drive capability.16MHz~20MHz.
    ClkXtalLowDrv                   = 2u,   ///< Low drive capability.8MHz~16MHz.
    ClkXtalTinyDrv                  = 3u,   ///< Tiny drive capability.8MHz.
} en_clk_xtal_drv_t;

/**
 *******************************************************************************
 ** \brief  The validity of frcut.
 **
 ******************************************************************************/
typedef enum en_clk_xtal_frcut
{
    ClkXtalFrcutValid               = 0u,   ///< Frcut valid.
    ClkXtalFrcutInvalid             = 1u,   ///< Frcut invalid.
} en_clk_xtal_frcut_t;

/**
 *******************************************************************************
 ** \brief  The stablization time of XTAL.
 **
 ** \note   It depends on SUPDRV bit.
 ******************************************************************************/
typedef enum en_clk_xtal_stb_cycle
{
    ClkXtalStbCycle35               = 1u,   ///< Stablization time is 35(36) cycle.
    ClkXtalStbCycle67               = 2u,   ///< Stablization time is 67(68) cycle.
    ClkXtalStbCycle131              = 3u,   ///< Stablization time is 131(132) cycle.
    ClkXtalStbCycle259              = 4u,   ///< Stablization time is 259(260) cycle.
    ClkXtalStbCycle547              = 5u,   ///< Stablization time is 547(548) cycle.
    ClkXtalStbCycle1059             = 6u,   ///< Stablization time is 1059(1060) cycle.
    ClkXtalStbCycle2147             = 7u,   ///< Stablization time is 2147(2148) cycle.
    ClkXtalStbCycle4291             = 8u,   ///< Stablization time is 4291(4292) cycle.
    ClkXtalStbCycle8163             = 9u,   ///< Stablization time is 8163(8164) cycle.
} en_clk_xtal_stb_cycle_t;

/**
 *******************************************************************************
 ** \brief  The handle of xtal stappage.
 **
 ******************************************************************************/
typedef enum en_clk_xtal_stp_mode
{
    ClkXtalStpModeInt               = 0u,   ///< The handle of stoppage is interrupt.
    ClkXtalStpModeReset             = 1u,   ///< The handle of stoppage is reset.
} en_clk_xtal_stp_mode_t;

/**
 *******************************************************************************
 ** \brief  The drive capability of xtal32.
 **
 ******************************************************************************/
typedef enum en_clk_xtal32_drv
{
    ClkXtal32MidDrv                 = 0u,   ///< High drive capability.32.768KHz.
    ClkXtal32HighDrv                = 1u,   ///< Midlle drive capability.32.768KHz.
    ClkXtal32LowDrv                 = 2u,   ///< Low drive capability.32.768KHz.
    ClkXtal32TinyDrv                = 3u,   ///< Tiny drive capability.32.768KHz.
} en_clk_xtal32_drv_t;

/**
 *******************************************************************************
 ** \brief  The filter mode of xtal32.
 **
 ******************************************************************************/
typedef enum en_clk_xtal32_filter_mode
{
    ClkXtal32FilterModeFull         = 0u,   ///< Valid in run,stop,power down mode.
    ClkXtal32FilterModePart         = 1u,   ///< Valid in run mode.
    ClkXtal32FilterModeNone         = 2u,   ///< Invalid in run,stop,power down mode.
} en_clk_xtal32_filter_mode_t;

/**
 *******************************************************************************
 ** \brief  The division factor of vco out.The result is pll out.
 **
 ******************************************************************************/
typedef enum en_clk_pllp_factor
{
    ClkPllp2                       = 1u,    ///< 2 division.
    ClkPllp4                       = 2u,    ///< 4 division.
    ClkPllp8                       = 4u,    ///< 8 division.
} en_clk_pllp_factor_t;

/**
 *******************************************************************************
 ** \brief  The division factor of pll source.The result is vco in.
 **
 ******************************************************************************/
typedef enum en_clk_pllm_factor
{
    ClkPllm1                        = 1u,   ///< 1 division.
    ClkPllm2                        = 2u,   ///< 2 division.
    ClkPllm3                        = 3u,   ///< 3 division.
} en_clk_pllm_factor_t;

/**
 *******************************************************************************
 ** \brief  The division factor of system clock.
 **
 ******************************************************************************/
typedef enum en_clk_sysclk_div_factor
{
    ClkSysclkDiv1                   = 0u,   ///< 1 division.
    ClkSysclkDiv2                   = 1u,   ///< 2 division.
    ClkSysclkDiv4                   = 2u,   ///< 4 division.
    ClkSysclkDiv8                   = 3u,   ///< 8 division.
    ClkSysclkDiv16                  = 4u,   ///< 16 division.
    ClkSysclkDiv32                  = 5u,   ///< 32 division.
    ClkSysclkDiv64                  = 6u,   ///< 64 division.
} en_clk_sysclk_div_factor_t;

/**
 *******************************************************************************
 ** \brief  The division factor of system clock.It will be used for debug clock.
 **
 ******************************************************************************/
typedef enum en_clk_tpiuclk_div_factor
{
    ClkTpiuclkDiv1                  = 0u,   ///< 1 division.
    ClkTpiuclkDiv2                  = 1u,   ///< 2 division.
    ClkTpiuclkDiv4                  = 2u,   ///< 4 division.
} en_clk_tpiuclk_div_factor_t;

/**
 *******************************************************************************
 ** \brief  The division factor of clock output.
 **
 ******************************************************************************/
typedef enum en_clk_output_div_factor
{
    ClkOutputDiv1                   = 0u,   ///< 1 division.
    ClkOutputDiv2                   = 1u,   ///< 2 division.
    ClkOutputDiv4                   = 2u,   ///< 4 division.
    ClkOutputDiv8                   = 3u,   ///< 8 division.
    ClkOutputDiv16                  = 4u,   ///< 16 division.
    ClkOutputDiv32                  = 5u,   ///< 32 division.
    ClkOutputDiv64                  = 6u,   ///< 64 division.
    ClkOutputDiv128                 = 7u,   ///< 128 division.
} en_clk_output_div_factor_t;

/**
 *******************************************************************************
 ** \brief  The division factor of fcm measure source.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_measure_div_factor
{
    ClkFcmMeaDiv1                   = 0u,   ///< 1 division.
    ClkFcmMeaDiv4                   = 1u,   ///< 4 division.
    ClkFcmMeaDiv8                   = 2u,   ///< 8 division.
    ClkFcmMeaDiv32                  = 3u,   ///< 32 division.
} en_clk_fcm_measure_div_factor_t;

/**
 *******************************************************************************
 ** \brief  The division factor of fcm reference source.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_intref_div_factor
{
    ClkFcmIntrefDiv32               = 0u,   ///< 32 division.
    ClkFcmIntrefDiv128              = 1u,   ///< 128 division.
    ClkFcmIntrefDiv1024             = 2u,   ///< 1024 division.
    ClkFcmIntrefDiv8192             = 3u,   ///< 8192 division.
} en_clk_fcm_intref_div_factor_t;

/**
 *******************************************************************************
 ** \brief  The edge of the fcm reference source.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_edge
{
    ClkFcmEdgeRising                = 0u,   ///< Rising edge.
    ClkFcmEdgeFalling               = 1u,   ///< Falling edge.
    ClkFcmEdgeBoth                  = 2u,   ///< Both edeg.
} en_clk_fcm_edge_t;

/**
 *******************************************************************************
 ** \brief  The filter clock of the fcm reference source.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_filter_clk
{
    ClkFcmFilterClkNone             = 0u,   ///< None filter.
    ClkFcmFilterClkFcmSrc           = 1u,   ///< Use fcm measurement source as filter clock.
    ClkFcmFilterClkFcmSrcDiv4       = 2u,   ///< Use 1/4 fcm measurement source as filter clock.
    ClkFcmFilterClkFcmSrcDiv16      = 3u,   ///< Use 1/16 fcm measurement source as filter clock.
} en_clk_fcm_filter_clk_t;

/**
 *******************************************************************************
 ** \brief  The fcm reference source.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_refer
{
    ClkFcmExtRef                    = 0u,   ///< Use external reference.
    ClkFcmInterRef                  = 1u,   ///< Use internal reference.
} en_clk_fcm_refer_t;

/**
 *******************************************************************************
 ** \brief  The handle of fcm abnormal.
 **
 ******************************************************************************/
typedef enum en_clk_fcm_abnormal_handle
{
    ClkFcmHandleInterrupt           = 0u,   ///< The handle of fcm abnormal is interrupt.
    ClkFcmHandleReset               = 1u,   ///< The handle of fcm abnormal is reset.
} en_clk_fcm_abnormal_handle_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of XTAL.
 **
 ** \note   Configures the XTAL if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_xtal_cfg
{
    en_functional_state_t           enFastStartup;  ///< Enable fast start up or not.

    en_clk_xtal_mode_t              enMode;         ///< Select xtal mode.

    en_clk_xtal_drv_t               enDrv;          ///< Select xtal drive capability.

    en_clk_xtal_frcut_t             enFrcut;        ///< Use frcut or not.
} stc_clk_xtal_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of XTAL stoppage.
 **
 ** \note   Configures the XTAL stoppage if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_xtal_stp_cfg
{
    en_functional_state_t           enDetect;       ///< Enable detect stoppage or not.

    en_clk_xtal_stp_mode_t          enMode;         ///< Select the handle of xtal stoppage.

    en_functional_state_t           enModeReset;    ///< Enable reset for handle the xtal stoppage.

    en_functional_state_t           enModeInt;      ///< Enable interrupt for handle the xtal stoppage.
} stc_clk_xtal_stp_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of XTAL32.
 **
 ** \note   Configures the XTAL32 if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_xtal32_cfg
{
    en_functional_state_t           enFastStartup;  ///< Enable fast start up or not.

    en_clk_xtal32_drv_t             enDrv;          ///< Select xtal32 drive capability.

    en_clk_xtal32_filter_mode_t     enFilterMode;   ///< The filter mode of xtal32.
} stc_clk_xtal32_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of PLL.
 **
 ** \note   Configures the PLL if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_pll_cfg
{
    uint16_t                        plln;           ///< Multiplication factor of vco out.

    en_clk_pllp_factor_t            pllp;           ///< Division factor of pll put.

    en_clk_pllm_factor_t            pllm;           ///< Division factor of vco in.
} stc_clk_mpll_cfg_t, stc_clk_upll_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of system clock.
 **
 ** \note   Configures the system clock if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_sysclk_cfg
{
    en_clk_sysclk_div_factor_t      hclkDiv;        ///< Division for hclk.

    en_clk_sysclk_div_factor_t      exclkDiv;       ///< Division for exclk.

    en_clk_sysclk_div_factor_t      pclk0Div;       ///< Division for pclk0.

    en_clk_sysclk_div_factor_t      pclk1Div;       ///< Division for pclk1.

    en_clk_sysclk_div_factor_t      pclk2Div;       ///< Division for pclk2.

    en_clk_sysclk_div_factor_t      pclk3Div;       ///< Division for pclk3.

    en_clk_sysclk_div_factor_t      pclk4Div;       ///< Division for pclk4.
} stc_clk_sysclk_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of clock output.
 **
 ** \note   Configures the clock output if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_output_cfg
{
    en_clk_output_source_t          enOutputSrc;    ///< The clock output source.

    en_clk_output_div_factor_t      enOutputDiv;    ///< The division factor of clock output source.
} stc_clk_output_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of fcm window.
 **
 ** \note   Configures the fcm window if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_fcm_window_cfg
{
    uint16_t                        windowLower;    ///< The lower value of the window.

    uint16_t                        windowUpper;    ///< The upper value of the window.
} stc_clk_fcm_window_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of fcm measurement.
 **
 ** \note   Configures the fcm measurement if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_fcm_measure_cfg
{
    en_clk_fcm_measure_source_t     enSrc;          ///< The measurement source.

    en_clk_fcm_measure_div_factor_t enSrcDiv;       ///< The division factor of measurement source.
} stc_clk_fcm_measure_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of fcm reference.
 **
 ** \note   Configures the fcm reference if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_fcm_reference_cfg
{
    en_clk_fcm_refer_t              enRefSel;       ///< Select reference.

    en_functional_state_t           enExtRef;       ///< Enable external reference or not.

    en_clk_fcm_intref_source_t      enIntRefSrc;    ///< Select internal reference.

    en_clk_fcm_intref_div_factor_t  enIntRefDiv;    ///< The division factor of internal reference.

    en_clk_fcm_edge_t               enEdge;         ///< The edge of internal reference.

    en_clk_fcm_filter_clk_t         enFilterClk;    ///< The filter clock of internal reference.
} stc_clk_fcm_reference_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of fcm interrupt.
 **
 ** \note   Configures the fcm interrupt if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_fcm_interrupt_cfg
{
    en_clk_fcm_abnormal_handle_t    enHandleSel;    ///< Use interrupr or reset.

    en_functional_state_t           enHandleReset;  ///< Enable reset or not.

    en_functional_state_t           enHandleInterrupt;  ///< Enable interrupt or not.

    en_functional_state_t           enOvfInterrupt; ///< Enable overflow interrupt or not.

    en_functional_state_t           enEndInterrupt; ///< Enable measurement end interrupt or not.
} stc_clk_fcm_interrupt_cfg_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of fcm.
 **
 ** \note   Configures the fcm if needed.
 **
 ******************************************************************************/
typedef struct stc_clk_fcm_cfg
{
    stc_clk_fcm_window_cfg_t        *pstcFcmWindowCfg;  ///< Window configuration struct.

    stc_clk_fcm_measure_cfg_t       *pstcFcmMeaCfg;     ///< Measurement configuration struct.

    stc_clk_fcm_reference_cfg_t     *pstcFcmRefCfg;     ///< Reference configuration struct.

    stc_clk_fcm_interrupt_cfg_t     *pstcFcmIntCfg;     ///< Interrupt configuration struct.

} stc_clk_fcm_cfg_t;

/**
 *******************************************************************************
 ** \brief  Clock frequence structure.
 **
 ******************************************************************************/
typedef struct stc_clk_freq
{
    uint32_t                        sysclkFreq;         ///< System clock frequence.
    uint32_t                        hclkFreq;           ///< Hclk frequence.
    uint32_t                        exckFreq;           ///< Exclk frequence.
    uint32_t                        pclk0Freq;          ///< Pclk0 frequence.
    uint32_t                        pclk1Freq;          ///< Pclk1 frequence.
    uint32_t                        pclk2Freq;          ///< Pclk2 frequence.
    uint32_t                        pclk3Freq;          ///< Pclk3 frequence.
    uint32_t                        pclk4Freq;          ///< Pclk4 frequence.
} stc_clk_freq_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CLK_FCG0_PERIPH_RAMHS       ((uint32_t)0x00000001)
#define CLK_FCG0_PERIPH_RAM0        ((uint32_t)0x00000010)
#define CLK_FCG0_PERIPH_ECCRAM      ((uint32_t)0x00000100)
#define CLK_FCG0_PERIPH_BRAM        ((uint32_t)0x00000400)
#define CLK_FCG0_PERIPH_SMI         ((uint32_t)0x00001000)
#define CLK_FCG0_PERIPH_DMA         ((uint32_t)0x00004000)
#define CLK_FCG0_PERIPH_FCM         ((uint32_t)0x00010000)
#define CLK_FCG0_PERIPH_PTDIS       ((uint32_t)0x00020000)
#define CLK_FCG0_PERIPH_AES         ((uint32_t)0x00100000)
#define CLK_FCG0_PERIPH_HASH        ((uint32_t)0x00200000)
#define CLK_FCG0_PERIPH_TRNG        ((uint32_t)0x00400000)
#define CLK_FCG0_PERIPH_CRC         ((uint32_t)0x00800000)
#define CLK_FCG0_PERIPH_DCU0        ((uint32_t)0x01000000)
#define CLK_FCG0_PERIPH_DCU1        ((uint32_t)0x02000000)
#define CLK_FCG0_PERIPH_DCU2        ((uint32_t)0x04000000)
#define CLK_FCG0_PERIPH_DCU3        ((uint32_t)0x08000000)

#define CLK_FCG1_PERIPH_CAN0        ((uint32_t)0x00000001)
#define CLK_FCG1_PERIPH_CAN1        ((uint32_t)0x00000002)
#define CLK_FCG1_PERIPH_QSPI        ((uint32_t)0x00000010)
#define CLK_FCG1_PERIPH_I2C         ((uint32_t)0x00000040)
#define CLK_FCG1_PERIPH_USBFS       ((uint32_t)0x00000100)
#define CLK_FCG1_PERIPH_USBHS       ((uint32_t)0x00000200)
#define CLK_FCG1_PERIPH_ETH         ((uint32_t)0x00000800)
#define CLK_FCG1_PERIPH_EXMC_SMC    ((uint32_t)0x00002000)
#define CLK_FCG1_PERIPH_EXMC_DMC    ((uint32_t)0x00004000)
#define CLK_FCG1_PERIPH_EXMC_NFC    ((uint32_t)0x00008000)
#define CLK_FCG1_PERIPH_SPI         ((uint32_t)0x00010000)
#define CLK_FCG1_PERIPH_MSC0        ((uint32_t)0x00100000)
#define CLK_FCG1_PERIPH_MSC1        ((uint32_t)0x00200000)
#define CLK_FCG1_PERIPH_MSC2        ((uint32_t)0x00400000)
#define CLK_FCG1_PERIPH_UART0       ((uint32_t)0x01000000)
#define CLK_FCG1_PERIPH_UART1       ((uint32_t)0x02000000)
#define CLK_FCG1_PERIPH_UART2       ((uint32_t)0x04000000)
#define CLK_FCG1_PERIPH_UART3       ((uint32_t)0x08000000)
#define CLK_FCG1_PERIPH_UART4       ((uint32_t)0x10000000)
#define CLK_FCG1_PERIPH_UART5       ((uint32_t)0x20000000)
#define CLK_FCG1_PERIPH_UART6       ((uint32_t)0x40000000)

#define CLK_FCG2_PERIPH_TIM00       ((uint32_t)0x00000001)
#define CLK_FCG2_PERIPH_TIM01       ((uint32_t)0x00000002)
#define CLK_FCG2_PERIPH_TIM20       ((uint32_t)0x00000010)
#define CLK_FCG2_PERIPH_TIM21       ((uint32_t)0x00000020)
#define CLK_FCG2_PERIPH_TIM22       ((uint32_t)0x00000040)
#define CLK_FCG2_PERIPH_TIM23       ((uint32_t)0x00000080)
#define CLK_FCG2_PERIPH_TIM40       ((uint32_t)0x00000100)
#define CLK_FCG2_PERIPH_TIM41       ((uint32_t)0x00000200)
#define CLK_FCG2_PERIPH_EMB         ((uint32_t)0x00008000)
#define CLK_FCG2_PERIPH_TIM60       ((uint32_t)0x00010000)
#define CLK_FCG2_PERIPH_TIM61       ((uint32_t)0x00020000)
#define CLK_FCG2_PERIPH_TIM62       ((uint32_t)0x00040000)
#define CLK_FCG2_PERIPH_TIM63       ((uint32_t)0x00080000)
#define CLK_FCG2_PERIPH_TIM64       ((uint32_t)0x00100000)
#define CLK_FCG2_PERIPH_TIM65       ((uint32_t)0x00200000)
#define CLK_FCG2_PERIPH_TIM66       ((uint32_t)0x00400000)
#define CLK_FCG2_PERIPH_TIM67       ((uint32_t)0x00800000)
#define CLK_FCG2_PERIPH_TIM68       ((uint32_t)0x01000000)
#define CLK_FCG2_PERIPH_TIM69       ((uint32_t)0x02000000)

#define CLK_FCG3_PERIPH_ADC0        ((uint32_t)0x00000001)
#define CLK_FCG3_PERIPH_ADC1        ((uint32_t)0x00000002)
#define CLK_FCG3_PERIPH_ADC2        ((uint32_t)0x00000004)
#define CLK_FCG3_PERIPH_DAC         ((uint32_t)0x00000010)
#define CLK_FCG3_PERIPH_CMP         ((uint32_t)0x00000100)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/* Xtal. */
void Clk_XtalConfig(stc_clk_xtal_cfg_t *pstcXtalCfg);

void Clk_XtalStbConfig(en_clk_xtal_stb_cycle_t enXtalStb);

void Clk_XtalCmd(en_functional_state_t enNewState);

void Clk_XtalStpConfig(stc_clk_xtal_stp_cfg_t *pstcXtalStpCfg);

/* Xtal32. */
void Clk_Xtal32Config(stc_clk_xtal32_cfg_t *pstcXtal32Cfg);

void Clk_Xtal32Cmd(en_functional_state_t enNewState);

/* Hrc. */
void Clk_HrcTrim(int8_t trimValue);

void Clk_HrcCmd(en_functional_state_t enNewState);

/* Mrc. */
void Clk_MrcTrim(int8_t trimValue);

void Clk_MrcCmd(en_functional_state_t enNewState);

/* Lrc. */
void Clk_LrcTrim(int8_t trimValue);

void Clk_LrcCmd(en_functional_state_t enNewState);

/* RtcLrc. */
void Clk_RtcLrcTrim(int8_t trimValue);

void Clk_RtcLrcCmd(en_functional_state_t enNewState);

/* Pll. */
void Clk_SetPllSource(en_clk_pll_source_t pllSrc);

void Clk_MpllConfig(stc_clk_mpll_cfg_t *pstcMpllCfg);

void Clk_MpllCmd(en_functional_state_t enNewState);

void Clk_UpllConfig(stc_clk_upll_cfg_t *pstcUpllCfg);

void Clk_UpllCmd(en_functional_state_t enNewState);

/* System clock. */
void Clk_SetSysClkSource(en_clk_sys_source_t enTargetSysSrc);

en_clk_sys_source_t Clk_GetSysClkSource(void);

void Clk_SysClkConfig(stc_clk_sysclk_cfg_t *pstcSysclkCfg);

/* Clock frequence and status. */
void Clk_GetClockFreq(stc_clk_freq_t *pstcClkFreq);

en_flag_status_t Clk_GetFlagStatus(en_clk_flag_t enClkFlag);

/* Others. */
void Clk_SetUsbClkSource(en_clk_usb_source_t enTargetUsbSrc);

void Clk_SetAdcClkSource(en_clk_adc_source_t enTargetAdcSrc);

void Clk_TpiuClkConfig(en_clk_tpiuclk_div_factor_t enTpiuDiv);

void Clk_TpiuClkCmd(en_functional_state_t enNewState);

void Clk_OutputClkConfig(stc_clk_output_cfg_t *pstcOutputCfg);

void Clk_OutputClkCmd(en_functional_state_t enNewState);

void Clk_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState);

void Clk_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState);

void Clk_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState);

void Clk_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState);

/* Fcm. */
void Clk_FcmConfig(stc_clk_fcm_cfg_t *pstcClkFcmCfg);

void Clk_FcmCmd(en_functional_state_t enNewState);

uint16_t Clk_GetFcmCounter(void);

en_flag_status_t Clk_GetFcmFlag(en_clk_fcm_flag_t enFcmFlag);

void Clk_ClearFcmFlag(en_clk_fcm_flag_t enFcmFlag);

//@} // ClkGroup

#ifdef __cplusplus
}
#endif

#endif /* __CLK_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
