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
/** \file clk.c
 **
 ** A detailed description is available at
 ** @link ClkGroup Clock description @endlink
 **
 **   - 2018-03-09  1.0  Jason First version for Device Driver Library of Clock.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "clk.h"

/**
 *******************************************************************************
 ** \addtogroup ClkGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CLK_XTAL_TIMEOUT                    ((uint16_t)0x1000)
#define CLK_XTAL32_TIMEOUT                  ((uint8_t)0x05)
#define CLK_HRC_TIMEOUT                     ((uint16_t)0x1000)
#define CLK_MRC_TIMEOUT                     ((uint8_t)0x05)
#define CLK_LRC_TIMEOUT                     ((uint8_t)0x05)
#define CLK_MPLL_TIMEOUT                    ((uint16_t)0x1000)
#define CLK_UPLL_TIMEOUT                    ((uint16_t)0x1000)
#define CLK_FCG_STABLE                      ((uint16_t)0x1000)
#define CLK_SYSCLK_STABLE                   ((uint16_t)0x1000)
#define CLK_USBCLK_STABLE                   ((uint16_t)0x1000)

#define CLK_PLLN_MIN                        20u
#define CLK_PLLN_MAX                        60u

#define CLK_PLL_VCO_IN_MIN                  8*1000*1000
#define CLK_PLL_VCO_IN_MAX                  24*1000*1000

#define CLK_PLL_VCO_OUT_MIN                 240*1000*1000
#define CLK_PLL_VCO_OUT_MAX                 480*1000*1000

#define CLK_PLL_OUT_MAX                     200*1000*1000

#define ENABLE_CLOCK_REG0_WRITE()           (M4_SYSREG->FPRC = 0xa501)
#define DISABLE_CLOCK_REG0_WRITE()          (M4_SYSREG->FPRC = 0xa500)

#define ENABLE_CLOCK_REG1_WRITE()           (M4_SYSREG->FPRC = 0xa502)
#define DISABLE_CLOCK_REG1_WRITE()          (M4_SYSREG->FPRC = 0xa500)

#define ENABLE_FCG0_REG_WRITE()             (M4_MSTP->FCG0PC = 0xa5a50001)
#define DISABLE_FCG0_REG_WRITE()            (M4_MSTP->FCG0PC = 0xa5a50000)

#define DEFAULT_FCG0                        0xFFFFFAEE
#define DEFAULT_FCG1                        0xFFFFFFFF
#define DEFAULT_FCG2                        0xFFFFFFFF
#define DEFAULT_FCG3                        0xFFFF

#define FCG0_OFFSET_FCM                     16u
#define FCG1_OFFSET_CAN0                    0u
#define FCG1_OFFSET_CAN1                    1u
#define FCG1_OFFSET_QSPI                    4u
#define FCG1_OFFSET_USBFS                   8u
#define FCG1_OFFSET_USBHS                   9u
#define FCG1_OFFSET_ETHER                   11u
#define FCG1_OFFSET_EXMC_SMC                13u
#define FCG1_OFFSET_EXMC_DMC                14u
#define FCG1_OFFSET_EXMC_NFC                15u
#define FCG1_OFFSET_SPI                     16u
#define FCG3_OFFSET_ADC0                    0u
#define FCG3_OFFSET_ADC1                    1u
#define FCG3_OFFSET_ADC2                    2u
#define FCG3_OFFSET_DAC                     4u

/*! Parameter validity check for XTAL stablization time \a stb. */
#define IS_XTAL_STB_VALID(stb)                                                 \
(   (ClkXtalStbCycle35      ==  (stb))      ||                                 \
    (ClkXtalStbCycle67      ==  (stb))      ||                                 \
    (ClkXtalStbCycle131     ==  (stb))      ||                                 \
    (ClkXtalStbCycle259     ==  (stb))      ||                                 \
    (ClkXtalStbCycle547     ==  (stb))      ||                                 \
    (ClkXtalStbCycle1059    ==  (stb))      ||                                 \
    (ClkXtalStbCycle2147    ==  (stb))      ||                                 \
    (ClkXtalStbCycle4291    ==  (stb))      ||                                 \
    (ClkXtalStbCycle8163    ==  (stb))                                         \
)

/*! Parameter validity check for stop XTAL \a syssrc \a pllsrc. */
#define IS_XTAL_STOP_VALID(syssrc,pllsrc)                                      \
(   (ClkSysSrcXTAL          !=  (syssrc))   &&                                 \
    (ClkPllSrcXTAL          !=  (pllsrc))                                      \
)

/*! Parameter validity check for stop XTAL32 \a syssrc. */
#define IS_XTAL32_STOP_VALID(syssrc)        (ClkSysSrcXTAL32 != (syssrc))

/*! Parameter validity check for stop HRC \a syssrc \a pllsrc. */
#define IS_HRC_STOP_VALID(syssrc,pllsrc)                                       \
(   (ClkSysSrcHRC           !=  (syssrc))   &&                                 \
    (ClkPllSrcHRC           !=  (pllsrc))                                      \
)

/*! Parameter validity check for stop MRC \a syssrc. */
#define IS_MRC_STOP_VALID(syssrc)           (ClkSysSrcMRC != syssrc)

/*! Parameter validity check for stop LRC \a syssrc. */
#define IS_LRC_STOP_VALID(syssrc)           (ClkSysSrcLRC != syssrc)

/*! Parameter validity check for stop MPLL \a syssrc. */
#define IS_MPLL_STOP_VALID(syssrc)          (CLKSysSrcMPLL != syssrc)

/*! Parameter validity check for pll source \a src. */
#define IS_PLL_SOURCE(src)                                                     \
(   (ClkPllSrcXTAL          ==  (src))      ||                                 \
    (ClkPllSrcHRC           ==  (src))                                         \
)

/*! Parameter validity check for plln \a plln. */
#define IS_PLLN_VALID(plln)                                                    \
(   (CLK_PLLN_MIN           <=  (plln))     &&                                 \
    (CLK_PLLN_MAX           >=  (plln))                                        \
)

/*! Parameter validity check for pllp \a pllp. */
#define IS_PLLP_VALID(pllp)                                                    \
(   (ClkPllp2               ==  (pllp))     ||                                 \
    (ClkPllp4               ==  (pllp))     ||                                 \
    (ClkPllp8               ==  (pllp))                                        \
)

/*! Parameter validity check for pllm \a pllm. */
#define IS_PLLM_VALID(pllm)                                                    \
(   (ClkPllm1               ==  (pllm))     ||                                 \
    (ClkPllm2               ==  (pllm))     ||                                 \
    (ClkPllm3               ==  (pllm))                                        \
)

/*! Parameter validity check for pllsource/pllm \a vco_in. */
#define IS_PLL_VCO_IN_VALID(vco_in)                                            \
(   (CLK_PLL_VCO_IN_MIN     <=  (vco_in))   &&                                 \
    (CLK_PLL_VCO_IN_MAX     >=  (vco_in))                                      \
)

/*! Parameter validity check for pllsource/pllm*plln \a vco_out. */
#define IS_PLL_VCO_OUT_VALID(vco_out)                                          \
(   (CLK_PLL_VCO_OUT_MIN    <=  (vco_out))  &&                                 \
    (CLK_PLL_VCO_OUT_MAX    >=  (vco_out))                                     \
)

/*! Parameter validity check for pllsource/pllm*plln/pllp \a pll_out. */
#define IS_PLL_OUT_VALID(pll_out)           (CLK_PLL_OUT_MAX >= (pll_out))

/*! Parameter validity check for system clock source \a syssrc. */
#define IS_SYSCLK_SOURCE(syssrc)                                               \
(   (ClkSysSrcHRC           ==  (syssrc))   ||                                 \
    (ClkSysSrcMRC           ==  (syssrc))   ||                                 \
    (ClkSysSrcLRC           ==  (syssrc))   ||                                 \
    (ClkSysSrcXTAL          ==  (syssrc))   ||                                 \
    (ClkSysSrcXTAL32        ==  (syssrc))   ||                                 \
    (CLKSysSrcMPLL          ==  (syssrc))                                      \
)

/*! Parameter validity check for usb clock source \a usbsrc. */
#define IS_USBCLK_SOURCE(usbsrc)                                               \
(   (ClkUsbSrcSysDiv2       ==  (usbsrc))   ||                                 \
    (ClkUsbSrcSysDiv3       ==  (usbsrc))   ||                                 \
    (ClkUsbSrcSysDiv4       ==  (usbsrc))   ||                                 \
    (ClkUsbSrcMpllq         ==  (usbsrc))   ||                                 \
    (ClkUsbSrcUpllp         ==  (usbsrc))   ||                                 \
    (ClkUsbSrcUpllq         ==  (usbsrc))                                      \
)

/*! Parameter validity check for adc clock source \a adcsrc. */
#define IS_ADCCLK_SOURCE(adcsrc)                                               \
(   (ClkAdcSrcSysDiv        ==  (adcsrc))   ||                                 \
    (ClkAdcSrcMpllq         ==  (adcsrc))   ||                                 \
    (ClkAdcSrcUpllp         ==  (adcsrc))   ||                                 \
    (ClkAdcSrcUpllq         ==  (adcsrc))                                      \
)

/*! Parameter validity check for output clock source \a outsrc. */
#define IS_OUTPUTCLK_SOURCE(outsrc)                                            \
(   (ClkOutputSrcHrc        ==  (outsrc))   ||                                 \
    (ClkOutputSrcMrc        ==  (outsrc))   ||                                 \
    (ClkOutputSrcLrc        ==  (outsrc))   ||                                 \
    (ClkOutputSrcXtal       ==  (outsrc))   ||                                 \
    (ClkOutputSrcXtal32     ==  (outsrc))   ||                                 \
    (ClkOutputSrcRtcLrc     ==  (outsrc))   ||                                 \
    (ClkOutputSrcMpllp      ==  (outsrc))   ||                                 \
    (ClkOutputSrcUpllp      ==  (outsrc))   ||                                 \
    (ClkOutputSrcMpllq      ==  (outsrc))   ||                                 \
    (ClkOutputSrcUpllq      ==  (outsrc))   ||                                 \
    (ClkOutputSrcSysclk     ==  (outsrc))                                      \
)

/*! Parameter validity check for fcm source \a fcmsrc. */
#define IS_FCM_SOURCE(fcmsrc)                                                  \
(   (ClkFcmSrcXtal          ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcXtal32        ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcHrc           ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcLrc           ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcSwdtrc        ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcPclk1         ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcUpllp         ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcMrc           ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcMpllp         ==  (fcmsrc))   ||                                 \
    (ClkFcmSrcRtcLrc        ==  (fcmsrc))                                      \
)

/*! Parameter validity check for fcm reference \a ref. */
#define IS_FCM_REF(ref)                                                        \
(   (ClkFcmExtRef           ==  (ref))      ||                                 \
    (ClkFcmInterRef         ==  (ref))                                         \
)

/*! Parameter validity check for fcm edge \a edge. */
#define IS_FCM_EDGE(edge)                                                      \
(   (ClkFcmEdgeRising       ==  (edge))     ||                                 \
    (ClkFcmEdgeFalling      ==  (edge))     ||                                 \
    (ClkFcmEdgeBoth         ==  (edge))                                        \
)

/*! Parameter validity check for fcm filter clock \a clk. */
#define IS_FCM_FILTER_CLK(clk)                                                 \
(   (ClkFcmFilterClkNone    ==  (clk))      ||                                 \
    (ClkFcmFilterClkFcmSrc  ==  (clk))      ||                                 \
    (ClkFcmFilterClkFcmSrcDiv4  ==  (clk))  ||                                 \
    (ClkFcmFilterClkFcmSrcDiv16 ==  (clk))                                     \
)

/*! Parameter validity check for fcm abnormal handle \a handle. */
#define IS_FCM_HANDLE(handle)                                                  \
(   (ClkFcmHandleInterrupt  ==  (handle))   ||                                 \
    (ClkFcmHandleReset      ==  (handle))                                      \
)

/*! Parameter validity check for debug clock division \a div. */
#define IS_TPIUCLK_DIV_VALID(div)                                              \
(   (ClkTpiuclkDiv1         ==  (div))      ||                                 \
    (ClkTpiuclkDiv2         ==  (div))      ||                                 \
    (ClkTpiuclkDiv4         ==  (div))                                         \
)

/*! Parameter validity check for output clock division \a div. */
#define IS_OUTPUTCLK_DIV_VALID(div)                                            \
(   (ClkOutputDiv1          ==  (div))      ||                                 \
    (ClkOutputDiv2          ==  (div))      ||                                 \
    (ClkOutputDiv4          ==  (div))      ||                                 \
    (ClkOutputDiv8          ==  (div))      ||                                 \
    (ClkOutputDiv16         ==  (div))      ||                                 \
    (ClkOutputDiv32         ==  (div))      ||                                 \
    (ClkOutputDiv64         ==  (div))      ||                                 \
    (ClkOutputDiv128        ==  (div))                                         \
)

/*! Parameter validity check for fcm measurement source division \a div. */
#define IS_FCM_MEASRC_DIV_VALID(div)                                           \
(   (ClkFcmMeaDiv1          ==  (div))      ||                                 \
    (ClkFcmMeaDiv4          ==  (div))      ||                                 \
    (ClkFcmMeaDiv8          ==  (div))      ||                                 \
    (ClkFcmMeaDiv32         ==  (div))                                         \
)

/*! Parameter validity check for internal reference source division \a div. */
#define IS_FCM_INTREF_DIV_VALID(div)                                           \
(   (ClkFcmIntrefDiv32      ==  (div))      ||                                 \
    (ClkFcmIntrefDiv128     ==  (div))      ||                                 \
    (ClkFcmIntrefDiv1024    ==  (div))      ||                                 \
    (ClkFcmIntrefDiv8192    ==  (div))                                         \
)

/*! Parameter validity check for clock status \a flag. */
#define IS_CLK_FLAG(flag)                                                      \
(   (ClkFlagHRCRdy          ==  (flag))     ||                                 \
    (ClkFlagXTALRdy         ==  (flag))     ||                                 \
    (ClkFlagMPLLRdy         ==  (flag))     ||                                 \
    (ClkFlagUPLLRdy         ==  (flag))     ||                                 \
    (ClkFlagXTALStoppage    ==  (flag))                                        \
)

/*! Parameter validity check for fcm status \a flag. */
#define IS_FCM_FLAG(flag)                                                      \
(   (ClkFcmFlagOvf          ==  (flag))     ||                                 \
    (ClkFcmFlagMendf        ==  (flag))     ||                                 \
    (ClkFcmFlagErrf         ==  (flag))                                        \
)

/*! Parameter validity check for system clock config \a cfg. */
#define IS_SYSCLK_CONFIG_VALID(cfg)                                            \
(   (cfg->hclkDiv           <=  (cfg->pclk1Div))    &&                         \
    (cfg->hclkDiv           <=  (cfg->pclk3Div))    &&                         \
    (cfg->hclkDiv           <=  (cfg->pclk4Div))    &&                         \
    (cfg->pclk0Div          <=  (cfg->pclk1Div))    &&                         \
    (cfg->pclk0Div          <=  (cfg->pclk3Div))    &&                         \
    ((cfg->pclk2Div-cfg->pclk4Div   ==  3)          ||                         \
    (cfg->pclk2Div-cfg->pclk4Div    ==  2)          ||                         \
    (cfg->pclk2Div-cfg->pclk4Div    ==  1)          ||                         \
    (cfg->pclk2Div-cfg->pclk4Div    ==  0)          ||                         \
    (cfg->pclk4Div-cfg->pclk2Div    ==  1)          ||                         \
    (cfg->pclk4Div-cfg->pclk2Div    ==  2)          ||                         \
    (cfg->pclk4Div-cfg->pclk2Div    ==  3))                                    \
)

/*! Parameter validity check for peripheral in fcg0. */
#define IS_CLK_FCG0_PERIPH(per)                                                \
(   (((per) & (0xF00CAAEE)) == (0X00))  &&                                     \
    ((0x00) != (per))                                                          \
)

/*! Parameter validity check for peripheral in fcg1. */
#define IS_CLK_FCG1_PERIPH(per)                                                \
(   (((per) & (0x808E14AC)) == (0X00))  &&                                     \
    ((0x00) != (per))                                                          \
)

/*! Parameter validity check for peripheral in fcg2. */
#define IS_CLK_FCG2_PERIPH(per)                                                \
(   (((per) & (0xFC007C0C)) == (0X00))  &&                                     \
    ((0x00) != (per))                                                          \
)

/*! Parameter validity check for peripheral in fcg3. */
#define IS_CLK_FCG3_PERIPH(per)                                                \
(   (((per) & (0XFFFFFEEB)) == (0X00))  &&                                     \
    ((0x00) != (per))                                                          \
)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief  Configures the external high speed oscillator(XTAL).
 **
 ** \param  [in] pstcXtalCfg            The XTAL configures struct.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_XtalConfig(stc_clk_xtal_cfg_t *pstcXtalCfg)
{
    DDL_ASSERT(NULL != pstcXtalCfg);

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_XTALCFGR_f.SUPDRV = pstcXtalCfg->enFastStartup;
    M4_SYSREG->CMU_XTALCFGR_f.XTALMS = pstcXtalCfg->enMode;
    M4_SYSREG->CMU_XTALCFGR_f.XTALDRV = pstcXtalCfg->enDrv;
    M4_SYSREG->CMU_XTALCFGR_f.FRCUT = pstcXtalCfg->enFrcut;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Configures the XTAL stablization time.
 **
 ** \param  [in] enXtalStb              The XTAL stalization time.
 **
 ** \retval None
 **
 ** \note   One of the stablization clock is 1/8 LRC clock.
 **
 ******************************************************************************/
void Clk_XtalStbConfig(en_clk_xtal_stb_cycle_t enXtalStb)
{
    DDL_ASSERT(IS_XTAL_STB_VALID(enXtalStb));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_XTALSTBCR_f.XTALSTB = enXtalStb;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Configures the XTAL stoppage.
 **
 ** \param  [in] pstcXtalStpCfg         The XTAL stoppage configures struct.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_XtalStpConfig(stc_clk_xtal_stp_cfg_t *pstcXtalStpCfg)
{
    DDL_ASSERT(NULL != pstcXtalStpCfg);

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_XTALSTDCR_f.XTALSTDE = pstcXtalStpCfg->enDetect;
    M4_SYSREG->CMU_XTALSTDCR_f.XTALSTDRIS = pstcXtalStpCfg->enMode;
    M4_SYSREG->CMU_XTALSTDCR_f.XTALSTDRE = pstcXtalStpCfg->enModeReset;
    M4_SYSREG->CMU_XTALSTDCR_f.XTALSTDIE = pstcXtalStpCfg->enModeInt;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the XTAL.
 **
 ** \param  [in] enNewState             The new state of the XTAL.
 ** \arg    Enable                      Enable XTAL.
 ** \arg    Disable                     Disable XTAL.
 **
 ** \retval None
 **
 ** \note   XTAL can not be stopped if it is used as system clock source or pll
 **         clock source.
 **
 ******************************************************************************/
void Clk_XtalCmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0;
    en_flag_status_t status;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(((Enable == enNewState) ?
                1 : IS_XTAL_STOP_VALID(M4_SYSREG->CMU_CKSWR_f.CKSW,
                M4_SYSREG->CMU_PLLCFGR_f.PLLSRC)));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_XTALCR_f.XTALSTP = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG0_WRITE();

    do
    {
        status = Clk_GetFlagStatus(ClkFlagXTALRdy);
        timeout++;
    }while((timeout != CLK_XTAL_TIMEOUT) && (status != ((Enable == enNewState) ? Set : Reset)));
}

/**
 *******************************************************************************
 ** \brief  Configures the external low speed oscillator(XTAL32).
 **
 ** \param  [in] pstcXtal32Cfg          The XTAL32 configures struct.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_Xtal32Config(stc_clk_xtal32_cfg_t *pstcXtal32Cfg)
{
    DDL_ASSERT(NULL != pstcXtal32Cfg);

    ENABLE_CLOCK_REG1_WRITE();

    M4_VBAT->CMU_XTAL32CFGR_f.XTAL32SUPDRV = pstcXtal32Cfg->enFastStartup;
    M4_VBAT->CMU_XTAL32CFGR_f.XTAL32DRV = pstcXtal32Cfg->enDrv;
    M4_VBAT->CMU_XTAL32NFR_f.XTAL32NF = pstcXtal32Cfg->enFilterMode;

    DISABLE_CLOCK_REG1_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the XTAL32.
 **
 ** \param  [in] enNewState             The new state of the XTAL32.
 ** \arg    Enable                      Enable XTAL32.
 ** \arg    Disable                     Disable XTAL32.
 **
 ** \retval None
 **
 ** \note   XTAL32 can not be stopped if it is used as system clock source.
 **
 ******************************************************************************/
void Clk_Xtal32Cmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(((Enable == enNewState) ?
                1 : IS_XTAL32_STOP_VALID(M4_SYSREG->CMU_CKSWR_f.CKSW)));

    ENABLE_CLOCK_REG1_WRITE();

    M4_VBAT->CMU_XTAL32CR_f.XTAL32STP = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG1_WRITE();

    do
    {
        timeout++;
    }while(timeout != CLK_XTAL32_TIMEOUT);
}

/**
 *******************************************************************************
 ** \brief  Trim the internal high speed oscillator(HRC).
 **
 ** \param  [in] trimValue              The trim value.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_HrcTrim(int8_t trimValue)
{
    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_HRCTRM = trimValue;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the HRC.
 **
 ** \param  [in] enNewState             The new state of the HRC.
 ** \arg    Enable                      Enable HRC.
 ** \arg    Disable                     Disable HRC.
 **
 ** \retval None
 **
 ** \note   HRC can not be stopped if it is used as system clock source or pll
 **         clock source.
 **
 ******************************************************************************/
void Clk_HrcCmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0;
    en_flag_status_t status;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_HRC_STOP_VALID(M4_SYSREG->CMU_CKSWR_f.CKSW,
                                M4_SYSREG->CMU_PLLCFGR_f.PLLSRC));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_HRCCR_f.HRCSTP = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG0_WRITE();

    do
    {
        status = Clk_GetFlagStatus(ClkFlagHRCRdy);
        timeout++;
    }while((timeout != CLK_HRC_TIMEOUT) && (status != ((Enable == enNewState) ? Set : Reset)));
}

/**
 *******************************************************************************
 ** \brief  Trim the internal middle speed oscillator(MRC).
 **
 ** \param  [in] trimValue              The trim value.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_MrcTrim(int8_t trimValue)
{
    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_MRCTRM = trimValue;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the MRC.
 **
 ** \param  [in] enNewState             The new state of the MRC.
 ** \arg    Enable                      Enable MRC.
 ** \arg    Disable                     Disable MRC.
 **
 ** \retval None
 **
 ** \note   MRC can not be stopped if it is used as system clock source.
 **
 ******************************************************************************/
void Clk_MrcCmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_MRC_STOP_VALID(M4_SYSREG->CMU_CKSWR_f.CKSW));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_MRCCR_f.MRCSTP = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG0_WRITE();

    do
    {
        timeout++;
    }while(timeout != CLK_MRC_TIMEOUT);
}

/**
 *******************************************************************************
 ** \brief  Trim the internal low speed oscillator(LRC).
 **
 ** \param  [in] trimValue              The trim value.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_LrcTrim(int8_t trimValue)
{
    ENABLE_CLOCK_REG1_WRITE();

    M4_VBAT->CMU_LRCTRM = trimValue;

    DISABLE_CLOCK_REG1_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the LRC.
 **
 ** \param  [in] enNewState             The new state of the LRC.
 ** \arg    Enable                      Enable LRC.
 ** \arg    Disable                     Disable LRC.
 **
 ** \retval None
 **
 ** \note   LRC can not be stopped if it is used as system clock source.
 **
 ******************************************************************************/
void Clk_LrcCmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_LRC_STOP_VALID(M4_SYSREG->CMU_CKSWR_f.CKSW));

    ENABLE_CLOCK_REG1_WRITE();

    M4_VBAT->CMU_LRCCR_f.LRCSTP = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG1_WRITE();

    do
    {
        timeout++;
    }while(timeout != CLK_LRC_TIMEOUT);
}

/**
 *******************************************************************************
 ** \brief  Trim the internal low speed oscillator used for rtc(RTCLRC).
 **
 ** \param  [in] trimValue              The trim value.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_RtcLrcTrim(int8_t trimValue)
{
    ENABLE_CLOCK_REG1_WRITE();

    M4_VBAT->CMU_RTCLRCTRM = trimValue;

    DISABLE_CLOCK_REG1_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the RTCLRC.
 **
 ** \param  [in] enNewState             The new state of the RTCLRC.
 ** \arg    Enable                      Enable RTCLRC.
 ** \arg    Disable                     Disable RTCLRC.
 **
 ** \retval None
 **
 ** \note   If rtc select RTCLRC as clock,RTCLRC will be work even if RTCLRCSTP
 **         is stop.
 **
 ******************************************************************************/
void Clk_RtcLrcCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_CLOCK_REG1_WRITE();

    M4_VBAT->CMU_RTCLRCCR_f.RTCLRCSTP = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG1_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Select pll clock source.
 **
 ** \param  [in] enPllSrc               The pll clock source.
 ** \arg    ClkPllSrcXTAL               Select XTAL as pll clock source.
 ** \arg    ClkPllSrcHRC                Select HRC as pll clock source.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_SetPllSource(en_clk_pll_source_t enPllSrc)
{
    DDL_ASSERT(IS_PLL_SOURCE(enPllSrc));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_PLLCFGR_f.PLLSRC = enPllSrc;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Configures the MPLL.
 **
 ** \param  [in] pstcMpllCfg            The MPLL configures struct.
 **
 ** \retval None
 **
 ** \note   The pllsource/pllm is between 8MHz and 12MHz.
 **         The pllsource/pllm*plln is between 240MHz and 480MHz.
 **         The maximum of pllsource/pllm*plln/pllp is 200MHz.
 **
 ******************************************************************************/
void Clk_MpllConfig(stc_clk_mpll_cfg_t *pstcMpllCfg)
{
    uint32_t vcoIn = 0;
    uint32_t vcoOut = 0;

    DDL_ASSERT(NULL != pstcMpllCfg);
    DDL_ASSERT(IS_PLLN_VALID(pstcMpllCfg->plln));
    DDL_ASSERT(IS_PLLP_VALID(pstcMpllCfg->pllp));
    DDL_ASSERT(IS_PLLM_VALID(pstcMpllCfg->pllm));

    vcoIn = ((ClkPllSrcXTAL == M4_SYSREG->CMU_PLLCFGR_f.PLLSRC ?
              XTAL_VALUE : HRC_VALUE) / pstcMpllCfg->pllm);
    vcoOut = vcoIn * pstcMpllCfg->plln;

    DDL_ASSERT(IS_PLL_VCO_IN_VALID(vcoIn));
    DDL_ASSERT(IS_PLL_VCO_OUT_VALID(vcoOut));
    DDL_ASSERT(IS_PLL_OUT_VALID(vcoOut / (pstcMpllCfg->pllp*2)));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_PLLCFGR_f.MPLLN = pstcMpllCfg->plln - 1;
    M4_SYSREG->CMU_PLLCFGR_f.MPLLP = pstcMpllCfg->pllp;
    M4_SYSREG->CMU_PLLCFGR_f.MPLLM = pstcMpllCfg->pllm - 1;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the MPLL.
 **
 ** \param  [in] enNewState             The new state of the MPLL.
 ** \arg    Enable                      Enable MPLL.
 ** \arg    Disable                     Disable MPLL.
 **
 ** \retval None
 **
 ** \note   MPLL can not be stopped if it is used as system clock source.
 **
 ******************************************************************************/
void Clk_MpllCmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0;
    en_flag_status_t status;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_MPLL_STOP_VALID(M4_SYSREG->CMU_CKSWR_f.CKSW));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_PLLCR_f.MPLLOFF = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG0_WRITE();

    do
    {
        status = Clk_GetFlagStatus(ClkFlagMPLLRdy);
        timeout++;
    }while((timeout != CLK_MPLL_TIMEOUT) && (status != ((Enable == enNewState) ? Set : Reset)));
}

/**
 *******************************************************************************
 ** \brief  Configures the UPLL.
 **
 ** \param  [in] pstcUpllCfg            The UPLL configures struct.
 **
 ** \retval None
 **
 ** \note   The pllsource/pllm is between 8MHz and 12MHz.
 **         The pllsource/pllm*plln is between 240MHz and 480MHz.
 **         The maximum of pllsource/pllm*plln/pllp is 200MHz.
 **
 ******************************************************************************/
void Clk_UpllConfig(stc_clk_upll_cfg_t *pstcUpllCfg)
{
    uint32_t vcoIn = 0;
    uint32_t vcoOut = 0;

    DDL_ASSERT(NULL != pstcUpllCfg);
    DDL_ASSERT(IS_PLLN_VALID(pstcUpllCfg->plln));
    DDL_ASSERT(IS_PLLP_VALID(pstcUpllCfg->pllp));
    DDL_ASSERT(IS_PLLM_VALID(pstcUpllCfg->pllm));

    vcoIn = ((ClkPllSrcXTAL == M4_SYSREG->CMU_PLLCFGR_f.PLLSRC ?
            XTAL_VALUE : HRC_VALUE) / pstcUpllCfg->pllm);
    vcoOut = vcoIn * pstcUpllCfg->plln;

    DDL_ASSERT(IS_PLL_VCO_IN_VALID(vcoIn));
    DDL_ASSERT(IS_PLL_VCO_OUT_VALID(vcoOut));
    DDL_ASSERT(IS_PLL_OUT_VALID(vcoOut / (pstcUpllCfg->pllp*2)));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_UPLLCFGR_f.UPLLN = pstcUpllCfg->plln - 1;
    M4_SYSREG->CMU_UPLLCFGR_f.UPLLP = pstcUpllCfg->pllp;
    M4_SYSREG->CMU_UPLLCFGR_f.UPLLM = pstcUpllCfg->pllm - 1;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the UPLL.
 **
 ** \param  [in] enNewState             The new state of the UPLL.
 ** \arg    Enable                      Enable UPLL.
 ** \arg    Disable                     Disable UPLL.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_UpllCmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0;
    en_flag_status_t status;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_UPLLCR_f.UPLLOFF = ((Enable == enNewState) ? 0 : 1);

    DISABLE_CLOCK_REG0_WRITE();

    do
    {
        status = Clk_GetFlagStatus(ClkFlagUPLLRdy);
        timeout++;
    }while((timeout != CLK_UPLL_TIMEOUT) && (status != ((Enable == enNewState) ? Set : Reset)));
}

/**
 *******************************************************************************
 ** \brief  Select system clock source.
 **
 ** \param  [in] enTargetSysSrc         The system clock source.
 ** \arg    ClkSysSrcHRC                Select HRC as system clock source.
 ** \arg    ClkSysSrcMRC                Select MRC as system clock source.
 ** \arg    ClkSysSrcLRC                Select LRC as system clock source.
 ** \arg    ClkSysSrcXTAL               Select XTAL as system clock source.
 ** \arg    ClkSysSrcXTAL32             Select XTAL32 as system clock source.
 ** \arg    CLKSysSrcMPLL               Select MPLL as system clock source.
 **
 ** \retval None
 **
 ** \note   Must close all of the fcg register before switch system clock source.
 **
 ******************************************************************************/
void Clk_SetSysClkSource(en_clk_sys_source_t enTargetSysSrc)
{
    __IO uint8_t temp = 0;
    __IO uint32_t timeout = 0;
    __IO uint32_t fcg0 = M4_MSTP->FCG0;
    __IO uint32_t fcg1 = M4_MSTP->FCG1;
    __IO uint32_t fcg2 = M4_MSTP->FCG2;
    __IO uint32_t fcg3 = M4_MSTP->FCG3;

    DDL_ASSERT(IS_SYSCLK_SOURCE(enTargetSysSrc));

    temp = M4_SYSREG->CMU_CKSWR_f.CKSW;

    /* Only current system clock source or target system clock source is MPLL
    need to close fcg0~fcg3 and open fcg0~fcg3 during switch system clock source.
    We need to backup fcg0~fcg3 before close them. */
    if(CLKSysSrcMPLL == temp || CLKSysSrcMPLL == enTargetSysSrc)
    {
        /* Close fcg0~fcg3. */
        M4_MSTP->FCG0 = DEFAULT_FCG0;
        M4_MSTP->FCG1 = DEFAULT_FCG1;
        M4_MSTP->FCG2 = DEFAULT_FCG2;
        M4_MSTP->FCG3 = DEFAULT_FCG3;

        /* Wait stable after close fcg. */
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }

    /* Switch to target system clock source. */
    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_CKSWR_f.CKSW = enTargetSysSrc;

    DISABLE_CLOCK_REG0_WRITE();

    if(CLKSysSrcMPLL == temp || CLKSysSrcMPLL == enTargetSysSrc)
    {
        /* Wait stable after switch system clock source.
        Only current system clock source or target system clock source is MPLL
        need to wait stable. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_SYSCLK_STABLE);

        /* Open fcg0~fcg3. */
        M4_MSTP->FCG0 = fcg0;
        M4_MSTP->FCG1 = fcg1;
        M4_MSTP->FCG2 = fcg2;
        M4_MSTP->FCG3 = fcg3;

        /* Wait stable after open fcg. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }
}

/**
 *******************************************************************************
 ** \brief  Get system clock source.
 **
 ** \param  None
 **
 ** \retval The system clock source.
 **
 ** \note   None
 **
 ******************************************************************************/
en_clk_sys_source_t Clk_GetSysClkSource(void)
{
    return (en_clk_sys_source_t)M4_SYSREG->CMU_CKSWR_f.CKSW;
}

/**
 *******************************************************************************
 ** \brief  Configures the division factor for hclk,exck,pclk0,pclk1,pclk2,pclk3,
 **         pclk4 from system clock.
 **
 ** \param  [in] pstcSysclkCfg          The system clock configures struct.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_SysClkConfig(stc_clk_sysclk_cfg_t *pstcSysclkCfg)
{
    __IO uint32_t timeout = 0;
    __IO uint32_t fcg0 = M4_MSTP->FCG0;
    __IO uint32_t fcg1 = M4_MSTP->FCG1;
    __IO uint32_t fcg2 = M4_MSTP->FCG2;
    __IO uint32_t fcg3 = M4_MSTP->FCG3;

    DDL_ASSERT(NULL != pstcSysclkCfg);
    DDL_ASSERT(IS_SYSCLK_CONFIG_VALID(pstcSysclkCfg));

    /* Only current system clock source is MPLL need to close fcg0~fcg3 and
    open fcg0~fcg3 during switch system clock division.
    We need to backup fcg0~fcg3 before close them. */
    if(CLKSysSrcMPLL == M4_SYSREG->CMU_CKSWR_f.CKSW)
    {
        /* Close fcg0~fcg3. */
        M4_MSTP->FCG0 = DEFAULT_FCG0;
        M4_MSTP->FCG1 = DEFAULT_FCG1;
        M4_MSTP->FCG2 = DEFAULT_FCG2;
        M4_MSTP->FCG3 = DEFAULT_FCG3;

        /* Wait stable after close fcg. */
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }

    /* Switch to target system clock division. */
    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_SCFGR_f.EXCKS = pstcSysclkCfg->exclkDiv;
    M4_SYSREG->CMU_SCFGR_f.PCLK4S = pstcSysclkCfg->pclk4Div;
    M4_SYSREG->CMU_SCFGR_f.PCLK3S = pstcSysclkCfg->pclk3Div;
    M4_SYSREG->CMU_SCFGR_f.PCLK2S = pstcSysclkCfg->pclk2Div;
    M4_SYSREG->CMU_SCFGR_f.PCLK1S = pstcSysclkCfg->pclk1Div;
    M4_SYSREG->CMU_SCFGR_f.PCLK0S = pstcSysclkCfg->pclk0Div;
    M4_SYSREG->CMU_SCFGR_f.HCLKS = pstcSysclkCfg->hclkDiv;

    DISABLE_CLOCK_REG0_WRITE();

    if(CLKSysSrcMPLL == M4_SYSREG->CMU_CKSWR_f.CKSW)
    {
        /* Wait stable after switch system clock division.
        Only current system clock source is MPLL need to wait stable. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_SYSCLK_STABLE);

        /* Open fcg0~fcg3. */
        M4_MSTP->FCG0 = fcg0;
        M4_MSTP->FCG1 = fcg1;
        M4_MSTP->FCG2 = fcg2;
        M4_MSTP->FCG3 = fcg3;

        /* Wait stable after open fcg. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }
}

/**
 *******************************************************************************
 ** \brief  Get clock frequence.
 **
 ** \param  [in] pstcClkFreq            The clock source struct.
 **
 ** \retval The clock frequence include system clock,hclk,exck,pclk0,pclk1,pclk2
 **         pclk3,pclk4.
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_GetClockFreq(stc_clk_freq_t *pstcClkFreq)
{
    uint8_t plln = 0, pllp = 0, pllm = 0, pllsource = 0;

    DDL_ASSERT(NULL != pstcClkFreq);

    /* Get system clock. */
    switch(M4_SYSREG->CMU_CKSWR_f.CKSW)
    {
        case ClkSysSrcHRC:
            /* HRC used as system clock. */
            pstcClkFreq->sysclkFreq = HRC_VALUE;
            break;
        case ClkSysSrcMRC:
            /* MRC used as system clock. */
            pstcClkFreq->sysclkFreq = MRC_VALUE;
            break;
        case ClkSysSrcLRC:
            /* LRC used as system clock. */
            pstcClkFreq->sysclkFreq = LRC_VALUE;
            break;
        case ClkSysSrcXTAL:
            /* XTAL used as system clock. */
            pstcClkFreq->sysclkFreq = XTAL_VALUE;
            break;
        case ClkSysSrcXTAL32:
            /* XTAL32 used as system clock. */
            pstcClkFreq->sysclkFreq = XTAL32_VALUE;
            break;
        default:
            /* MPLL used as system clock. */
            pllsource = M4_SYSREG->CMU_PLLCFGR_f.PLLSRC;
            plln = M4_SYSREG->CMU_PLLCFGR_f.MPLLN;
            pllp = M4_SYSREG->CMU_PLLCFGR_f.MPLLP;
            pllm = M4_SYSREG->CMU_PLLCFGR_f.MPLLM;

            /* PLLCLK = ((pllsrc / pllm) * plln) / pllp */
            if (ClkPllSrcXTAL == pllsource)
            {
                pstcClkFreq->sysclkFreq = (XTAL_VALUE)/(pllm+1)*(plln+1)/(pllp<<1);
            }
            else if (ClkPllSrcHRC == pllsource)
            {
                pstcClkFreq->sysclkFreq = (HRC_VALUE)/(pllm+1)*(plln+1)/(pllp<<1);
            }
            break;
    }

    /* Get hclk. */
    pstcClkFreq->hclkFreq = pstcClkFreq->sysclkFreq >> M4_SYSREG->CMU_SCFGR_f.HCLKS;;

    /* Get exck. */
    pstcClkFreq->exckFreq = pstcClkFreq->sysclkFreq >> M4_SYSREG->CMU_SCFGR_f.EXCKS;

    /* Get pclk0. */
    pstcClkFreq->pclk0Freq = pstcClkFreq->sysclkFreq >> M4_SYSREG->CMU_SCFGR_f.PCLK0S;

    /* Get pclk1. */
    pstcClkFreq->pclk1Freq = pstcClkFreq->sysclkFreq >> M4_SYSREG->CMU_SCFGR_f.PCLK1S;

    /* Get pclk2. */
    pstcClkFreq->pclk2Freq = pstcClkFreq->sysclkFreq >> M4_SYSREG->CMU_SCFGR_f.PCLK2S;

    /* Get pclk3. */
    pstcClkFreq->pclk3Freq = pstcClkFreq->sysclkFreq >> M4_SYSREG->CMU_SCFGR_f.PCLK3S;

    /* Get pclk4. */
    pstcClkFreq->pclk4Freq = pstcClkFreq->sysclkFreq >> M4_SYSREG->CMU_SCFGR_f.PCLK4S;
}

/**
 *******************************************************************************
 ** \brief  Select usb clock source.
 **
 ** \param  [in] enTargetUsbSrc         The usb clock source.
 ** \arg    ClkUsbSrcSysDiv2            Select 1/2 system clock as usb clock source.
 ** \arg    ClkUsbSrcSysDiv3            Select 1/3 system clock as usb clock source.
 ** \arg    ClkUsbSrcSysDiv4            Select 1/4 system clock as usb clock source.
 ** \arg    ClkUsbSrcMpllq              Select MPLLQ as usb clock source.
 ** \arg    ClkUsbSrcUpllp              Select UPLLP as usb clock source.
 ** \arg    ClkUsbSrcUpllq              Select UPLLQ as usb clock source.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_SetUsbClkSource(en_clk_usb_source_t enTargetUsbSrc)
{
    __IO uint32_t timeout = 0;
    __IO uint32_t fcg0 = M4_MSTP->FCG0;
    __IO uint32_t fcg1 = M4_MSTP->FCG1;
    __IO uint32_t fcg2 = M4_MSTP->FCG2;
    __IO uint32_t fcg3 = M4_MSTP->FCG3;

    DDL_ASSERT(IS_USBCLK_SOURCE(enTargetUsbSrc));

    /* Only current system clock source is MPLL need to close fcg0~fcg3 and
    open fcg0~fcg3 during switch USB clock source.
    We need to backup fcg0~fcg3 before close them. */
    if(CLKSysSrcMPLL == M4_SYSREG->CMU_CKSWR_f.CKSW)
    {
        /* Close fcg0~fcg3.Set bit to close it. */
        BIT_SET(M4_MSTP->FCG0,  BIT_VALUE(FCG0_OFFSET_FCM));
        BIT_SET(M4_MSTP->FCG1,  BIT_VALUE(FCG1_OFFSET_CAN0) |
                                BIT_VALUE(FCG1_OFFSET_CAN1) |
                                BIT_VALUE(FCG1_OFFSET_QSPI) |
                                BIT_VALUE(FCG1_OFFSET_USBFS) |
                                BIT_VALUE(FCG1_OFFSET_USBHS) |
                                BIT_VALUE(FCG1_OFFSET_ETHER) |
                                BIT_VALUE(FCG1_OFFSET_EXMC_SMC) |
                                BIT_VALUE(FCG1_OFFSET_EXMC_DMC) |
                                BIT_VALUE(FCG1_OFFSET_EXMC_NFC) |
                                BIT_VALUE(FCG1_OFFSET_SPI));

        M4_MSTP->FCG2 = DEFAULT_FCG2;

        BIT_SET(M4_MSTP->FCG3,  BIT_VALUE(FCG3_OFFSET_ADC0) |
                                BIT_VALUE(FCG3_OFFSET_ADC1) |
                                BIT_VALUE(FCG3_OFFSET_ADC2) |
                                BIT_VALUE(FCG3_OFFSET_DAC));

        /* Wait stable after close fcg. */
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }

    /* Switch to target usb clock source. */
    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_UFSCKCFGR_f.USBCKS = enTargetUsbSrc;

    DISABLE_CLOCK_REG0_WRITE();

    if(CLKSysSrcMPLL == M4_SYSREG->CMU_CKSWR_f.CKSW)
    {
        /* Wait stable after switch usb clock source.
        Only current system clock source or target system clock source is MPLL
        need to wait stable. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_USBCLK_STABLE);

        /* Open fcg0~fcg3. Write the backup value. */
        M4_MSTP->FCG0 = fcg0;
        M4_MSTP->FCG1 = fcg1;
        M4_MSTP->FCG2 = fcg2;
        M4_MSTP->FCG3 = fcg3;

        /* Wait stable after open fcg. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }

}

/**
 *******************************************************************************
 ** \brief  Select adc clock source.
 **
 ** \param  [in] enTargetAdcSrc         The adc clock source.
 ** \arg    ClkAdcSrcSysDiv             The adc clock source is division from
 **                                     system clock.
 ** \arg    ClkAdcSrcMpllq              Select MPLLQ as adc clock source.
 ** \arg    ClkAdcSrcUpllp              Select UPLLP as adc clock source.
 ** \arg    ClkAdcSrcUpllq              Select UPLLQ as adc clock source.
 **
 ** \retval None
 **
 ** \note   Must close usb,ether,exbus,can,qspi,spi,timer,fcm,adc and dac
 **         before switch adc clock source.
 **
 ******************************************************************************/
void Clk_SetAdcClkSource(en_clk_adc_source_t enTargetAdcSrc)
{
    __IO uint32_t timeout = 0;
    __IO uint32_t fcg0 = M4_MSTP->FCG0;
    __IO uint32_t fcg1 = M4_MSTP->FCG1;
    __IO uint32_t fcg2 = M4_MSTP->FCG2;
    __IO uint32_t fcg3 = M4_MSTP->FCG3;

    DDL_ASSERT(IS_ADCCLK_SOURCE(enTargetAdcSrc));

    /* Only current system clock source is MPLL need to close fcg0~fcg3 and
    open fcg0~fcg3 during switch ADC clock source.
    We need to backup fcg0~fcg3 before close them. */
    if(CLKSysSrcMPLL == M4_SYSREG->CMU_CKSWR_f.CKSW)
    {
        /* Close fcg0~fcg3.Set bit to close it. */
        BIT_SET(M4_MSTP->FCG0,  BIT_VALUE(FCG0_OFFSET_FCM));
        BIT_SET(M4_MSTP->FCG1,  BIT_VALUE(FCG1_OFFSET_CAN0) |
                                BIT_VALUE(FCG1_OFFSET_CAN1) |
                                BIT_VALUE(FCG1_OFFSET_QSPI) |
                                BIT_VALUE(FCG1_OFFSET_USBFS) |
                                BIT_VALUE(FCG1_OFFSET_USBHS) |
                                BIT_VALUE(FCG1_OFFSET_ETHER) |
                                BIT_VALUE(FCG1_OFFSET_EXMC_SMC) |
                                BIT_VALUE(FCG1_OFFSET_EXMC_DMC) |
                                BIT_VALUE(FCG1_OFFSET_EXMC_NFC) |
                                BIT_VALUE(FCG1_OFFSET_SPI));

        M4_MSTP->FCG2 = DEFAULT_FCG2;

        BIT_SET(M4_MSTP->FCG3,  BIT_VALUE(FCG3_OFFSET_ADC0) |
                                BIT_VALUE(FCG3_OFFSET_ADC1) |
                                BIT_VALUE(FCG3_OFFSET_ADC2) |
                                BIT_VALUE(FCG3_OFFSET_DAC));

        /* Wait stable after close fcg. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }

    /* Switch to target adc clock source. */
    ENABLE_CLOCK_REG1_WRITE();

    M4_SYSREG->CMU_ADCKSEL_f.ADCKSEL = enTargetAdcSrc;

    DISABLE_CLOCK_REG1_WRITE();

    if(CLKSysSrcMPLL == M4_SYSREG->CMU_CKSWR_f.CKSW)
    {
        /* Wait stable after switch adc clock source.
        Only current system clock source or target system clock source is MPLL
        need to wait stable. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_USBCLK_STABLE);

        /* Open fcg0~fcg3. */
        M4_MSTP->FCG0 = fcg0;
        M4_MSTP->FCG1 = fcg1;
        M4_MSTP->FCG2 = fcg2;
        M4_MSTP->FCG3 = fcg3;

        /* Wait stable after open fcg. */
        timeout = 0;
        do
        {
            timeout++;
        }while(timeout != CLK_FCG_STABLE);
    }
}

/**
 *******************************************************************************
 ** \brief  Configures the debug clock.
 **
 ** \param  [in] enTpiuDiv              The division of debug clock from system
 **                                     clock.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_TpiuClkConfig(en_clk_tpiuclk_div_factor_t enTpiuDiv)
{
    DDL_ASSERT(IS_TPIUCLK_DIV_VALID(enTpiuDiv));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_TPIUCKCFGR_f.TPIUCKS = enTpiuDiv;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the debug clock.
 **
 ** \param  [in] enNewState             The new state of the debug clock.
 ** \arg    Enable                      Enable debug clock.
 ** \arg    Disable                     Disable debug clock.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_TpiuClkCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_TPIUCKCFGR_f.TPIUCKOE = enNewState;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Configures the output clock.
 **
 ** \param  [in] pstcOutputCfg          The clock output configures struct.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_OutputClkConfig(stc_clk_output_cfg_t *pstcOutputCfg)
{
    DDL_ASSERT(NULL != pstcOutputCfg);
    DDL_ASSERT(IS_OUTPUTCLK_SOURCE(pstcOutputCfg->enOutputSrc));
    DDL_ASSERT(IS_OUTPUTCLK_DIV_VALID(pstcOutputCfg->enOutputDiv));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_MCOCFGR_f.MCOSEL = pstcOutputCfg->enOutputSrc;
    M4_SYSREG->CMU_MCOCFGR_f.MCODIV = pstcOutputCfg->enOutputDiv;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the clock output.
 **
 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_OutputClkCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_CLOCK_REG0_WRITE();

    M4_SYSREG->CMU_MCOCFGR_f.MCOEN = enNewState;

    DISABLE_CLOCK_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG0 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg0Periph          The peripheral in FCG0.
 ** \arg    CLK_FCG0_PERIPH_RAMHS       RAMHS clock
 ** \arg    CLK_FCG0_PERIPH_RAM0        RAM0 clock
 ** \arg    CLK_FCG0_PERIPH_ECCRAM      ECCRAM clock
 ** \arg    CLK_FCG0_PERIPH_BRAM        BRAM clock
 ** \arg    CLK_FCG0_PERIPH_SMI         SMI clock
 ** \arg    CLK_FCG0_PERIPH_DMA         DMA clock
 ** \arg    CLK_FCG0_PERIPH_FCM         FCM clock
 ** \arg    CLK_FCG0_PERIPH_PTDIS       PTDIS clock
 ** \arg    CLK_FCG0_PERIPH_AES         AES clock
 ** \arg    CLK_FCG0_PERIPH_HASH        HASH clock
 ** \arg    CLK_FCG0_PERIPH_TRNG        TRNG clock
 ** \arg    CLK_FCG0_PERIPH_CRC         CRC clock
 ** \arg    CLK_FCG0_PERIPH_DCU0        DCU0 clock
 ** \arg    CLK_FCG0_PERIPH_DCU1        DCU1 clock
 ** \arg    CLK_FCG0_PERIPH_DCU2        DCU2 clock
 ** \arg    CLK_FCG0_PERIPH_DCU2        DCU3 clock

 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CLK_FCG0_PERIPH(u32Fcg0Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_FCG0_REG_WRITE();

    if(Enable == enNewState)
    {
        M4_MSTP->FCG0 &= ~u32Fcg0Periph;
    }
    else
    {
        M4_MSTP->FCG0 |= u32Fcg0Periph;
    }

    DISABLE_FCG0_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG1 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg1Periph          The peripheral in FCG1.
 ** \arg    CLK_FCG1_PERIPH_CAN0        CAN0 clock
 ** \arg    CLK_FCG1_PERIPH_CAN1        CAN1 clock
 ** \arg    CLK_FCG1_PERIPH_QSPI        QSPI clock
 ** \arg    CLK_FCG1_PERIPH_I2C         I2C clock
 ** \arg    CLK_FCG1_PERIPH_USBFS       USBFS clock
 ** \arg    CLK_FCG1_PERIPH_USBHS       USBHS clock
 ** \arg    CLK_FCG1_PERIPH_ETH         ETH clock
 ** \arg    CLK_FCG1_PERIPH_EXMC_SMC    EXMC_SMC clock
 ** \arg    CLK_FCG1_PERIPH_EXMC_DMC    EXMC_DMC clock
 ** \arg    CLK_FCG1_PERIPH_EXMC_NFC    EXMC_NFC clock
 ** \arg    CLK_FCG1_PERIPH_SPI         SPI clock
 ** \arg    CLK_FCG1_PERIPH_MSC0        MSC0 clock
 ** \arg    CLK_FCG1_PERIPH_MSC1        MSC1 clock
 ** \arg    CLK_FCG1_PERIPH_MSC2        MSC2 clock
 ** \arg    CLK_FCG1_PERIPH_UART0       UART0 clock
 ** \arg    CLK_FCG1_PERIPH_UART1       UART1 clock
 ** \arg    CLK_FCG1_PERIPH_UART2       UART2 clock
 ** \arg    CLK_FCG1_PERIPH_UART3       UART3 clock
 ** \arg    CLK_FCG1_PERIPH_UART4       UART4 clock
 ** \arg    CLK_FCG1_PERIPH_UART5       UART5 clock
 ** \arg    CLK_FCG1_PERIPH_UART6       UART6 clock
 **
 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CLK_FCG1_PERIPH(u32Fcg1Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        M4_MSTP->FCG1 &= ~u32Fcg1Periph;
    }
    else
    {
        M4_MSTP->FCG1 |= u32Fcg1Periph;
    }
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG2 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg2Periph          The peripheral in FCG2.
 ** \arg    CLK_FCG2_PERIPH_TIM00       TIM00 clock
 ** \arg    CLK_FCG2_PERIPH_TIM01       TIM01 clock
 ** \arg    CLK_FCG2_PERIPH_TIM20       TIM20 clock
 ** \arg    CLK_FCG2_PERIPH_TIM21       TIM21 clock
 ** \arg    CLK_FCG2_PERIPH_TIM22       TIM22 clock
 ** \arg    CLK_FCG2_PERIPH_TIM23       TIM23 clock
 ** \arg    CLK_FCG2_PERIPH_TIM40       TIM40 clock
 ** \arg    CLK_FCG2_PERIPH_TIM41       TIM41 clock
 ** \arg    CLK_FCG2_PERIPH_EMB         EMB clock
 ** \arg    CLK_FCG2_PERIPH_TIM60       TIM60 clock
 ** \arg    CLK_FCG2_PERIPH_TIM61       TIM61 clock
 ** \arg    CLK_FCG2_PERIPH_TIM62       TIM62 clock
 ** \arg    CLK_FCG2_PERIPH_TIM63       TIM63 clock
 ** \arg    CLK_FCG2_PERIPH_TIM64       TIM64 clock
 ** \arg    CLK_FCG2_PERIPH_TIM65       TIM65 clock
 ** \arg    CLK_FCG2_PERIPH_TIM66       TIM66 clock
 ** \arg    CLK_FCG2_PERIPH_TIM67       TIM67 clock
 ** \arg    CLK_FCG2_PERIPH_TIM68       TIM68 clock
 ** \arg    CLK_FCG2_PERIPH_TIM69       TIM69 clock
 **
 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CLK_FCG2_PERIPH(u32Fcg2Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        M4_MSTP->FCG2 &= ~u32Fcg2Periph;
    }
    else
    {
        M4_MSTP->FCG2 |= u32Fcg2Periph;
    }
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG3 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg3Periph          The peripheral in FCG3.
 ** \arg    CLK_FCG3_PERIPH_ADC0        ADC0 clock
 ** \arg    CLK_FCG3_PERIPH_ADC1        ADC1 clock
 ** \arg    CLK_FCG3_PERIPH_ADC2        ADC2 clock
 ** \arg    CLK_FCG3_PERIPH_DAC         DAC clock
 ** \arg    CLK_FCG3_PERIPH_CMP         CMP clock
 **
 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CLK_FCG3_PERIPH(u32Fcg3Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        M4_MSTP->FCG3 &= ~u32Fcg3Periph;
    }
    else
    {
        M4_MSTP->FCG3 |= u32Fcg3Periph;
    }
}

/**
 *******************************************************************************
 ** \brief  Get the specified clock flag status.
 **
 ** \param  [in] enClkFlag              The specified clock flag.
 ** \arg    ClkFlagHRCRdy               HRC is ready or not.
 ** \arg    ClkFlagXTALRdy              XTAL is ready or not.
 ** \arg    ClkFlagMPLLRdy              MPLL is ready or not.
 ** \arg    ClkFlagUPLLRdy              UPLL is ready or not.
 ** \arg    ClkFlagXTALStoppage         XTAL is detected stoppage or not.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t Clk_GetFlagStatus(en_clk_flag_t enClkFlag)
{
    en_flag_status_t status;

    DDL_ASSERT(IS_CLK_FLAG(enClkFlag));

    switch(enClkFlag)
    {
        case ClkFlagHRCRdy:
            status = ((1 == M4_SYSREG->CMU_OSCSTBSR_f.HRCSTBF) ? Set : Reset);
            break;
        case ClkFlagXTALRdy:
            status = ((1 == M4_SYSREG->CMU_OSCSTBSR_f.XTALSTBF) ? Set : Reset);
            break;
        case ClkFlagMPLLRdy:
            status = ((1 == M4_SYSREG->CMU_OSCSTBSR_f.MPLLSTBF) ? Set : Reset);
            break;
        case ClkFlagUPLLRdy:
            status = ((1 == M4_SYSREG->CMU_OSCSTBSR_f.UPLLSTBF) ? Set : Reset);
            break;
        default:
            status = ((1 == M4_SYSREG->CMU_XTALSTDSR_f.XTALSTDF) ? Set : Reset);
            break;
    }

    return status;
}

/**
 *******************************************************************************
 ** \brief  Configures the clock frequence measurement.
 **
 ** \param  [in] pstcClkFcmCfg          The clock frequence measurement configures
 **                                     struct.
 **
 ** \retval None
 **
 ** \note   Configures the window,measurement,reference and interrupt independently.
 **
 ******************************************************************************/
void Clk_FcmConfig(stc_clk_fcm_cfg_t *pstcClkFcmCfg)
{
    DDL_ASSERT(NULL != pstcClkFcmCfg);

    /* Window config. */
    if(pstcClkFcmCfg->pstcFcmWindowCfg)
    {
        /* Set window lower. */
        M4_FCM->LVR = pstcClkFcmCfg->pstcFcmWindowCfg->windowLower;
        /* Set window upper. */
        M4_FCM->UVR = pstcClkFcmCfg->pstcFcmWindowCfg->windowUpper;
    }

    /* Measure config. */
    if(pstcClkFcmCfg->pstcFcmMeaCfg)
    {
        DDL_ASSERT(IS_FCM_SOURCE(pstcClkFcmCfg->pstcFcmMeaCfg->enSrc));
        DDL_ASSERT(IS_FCM_MEASRC_DIV_VALID(pstcClkFcmCfg->pstcFcmMeaCfg->enSrcDiv));

        /* Measure source. */
        M4_FCM->MCCR_f.MCKS = pstcClkFcmCfg->pstcFcmMeaCfg->enSrc;
        /* Measure source division. */
        M4_FCM->MCCR_f.MDIVS = pstcClkFcmCfg->pstcFcmMeaCfg->enSrcDiv;
    }

    /* Reference config. */
    if(pstcClkFcmCfg->pstcFcmRefCfg)
    {
        DDL_ASSERT(IS_FCM_REF(pstcClkFcmCfg->pstcFcmRefCfg->enRefSel));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcClkFcmCfg->pstcFcmRefCfg->enExtRef));
        DDL_ASSERT(IS_FCM_SOURCE(pstcClkFcmCfg->pstcFcmRefCfg->enIntRefSrc));
        DDL_ASSERT(IS_FCM_INTREF_DIV_VALID(pstcClkFcmCfg->pstcFcmRefCfg->enIntRefDiv));
        DDL_ASSERT(IS_FCM_EDGE(pstcClkFcmCfg->pstcFcmRefCfg->enEdge));
        DDL_ASSERT(IS_FCM_FILTER_CLK(pstcClkFcmCfg->pstcFcmRefCfg->enFilterClk));

        M4_FCM->RCCR_f.INEXS = pstcClkFcmCfg->pstcFcmRefCfg->enRefSel;
        M4_FCM->RCCR_f.EXREFE = pstcClkFcmCfg->pstcFcmRefCfg->enExtRef;
        M4_FCM->RCCR_f.RCKS = pstcClkFcmCfg->pstcFcmRefCfg->enIntRefSrc;
        M4_FCM->RCCR_f.RDIVS = pstcClkFcmCfg->pstcFcmRefCfg->enIntRefDiv;
        M4_FCM->RCCR_f.EDGES = pstcClkFcmCfg->pstcFcmRefCfg->enEdge;
        M4_FCM->RCCR_f.DNFS = pstcClkFcmCfg->pstcFcmRefCfg->enFilterClk;
    }

    /* Interrupt config. */
    if(pstcClkFcmCfg->pstcFcmIntCfg)
    {
        DDL_ASSERT(IS_FCM_HANDLE(pstcClkFcmCfg->pstcFcmIntCfg->enHandleSel));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcClkFcmCfg->pstcFcmIntCfg->enHandleReset));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcClkFcmCfg->pstcFcmIntCfg->enHandleInterrupt));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcClkFcmCfg->pstcFcmIntCfg->enOvfInterrupt));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcClkFcmCfg->pstcFcmIntCfg->enEndInterrupt));

        M4_FCM->RIER_f.ERRINTRS = pstcClkFcmCfg->pstcFcmIntCfg->enHandleSel;
        M4_FCM->RIER_f.ERRE = pstcClkFcmCfg->pstcFcmIntCfg->enHandleReset;
        M4_FCM->RIER_f.ERRIE = pstcClkFcmCfg->pstcFcmIntCfg->enHandleInterrupt;
        M4_FCM->RIER_f.MENDIE = pstcClkFcmCfg->pstcFcmIntCfg->enEndInterrupt;
        M4_FCM->RIER_f.OVFIE = pstcClkFcmCfg->pstcFcmIntCfg->enOvfInterrupt;
    }
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the clock frequence measurement.
 **
 ** \param  [in] enNewState             The new state of the clock frequence
 **                                     measurement.
 ** \arg    Enable                      Enable clock frequence measurement.
 ** \arg    Disable                     Disable clock frequence measurement.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_FcmCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    M4_FCM->STR = (Enable == enNewState ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  Get fcm counter value.
 **
 ** \param  None
 **
 ** \retval The fcm counter value.
 **
 ** \note   None
 **
 ******************************************************************************/
uint16_t Clk_GetFcmCounter(void)
{
    return M4_FCM->CNTR;
}

/**
 *******************************************************************************
 ** \brief  Get the specified fcm flag status.
 **
 ** \param  [in] enFcmFlag              The specified fcm flag.
 ** \arg    ClkFcmFlagOvf               The fcm counter overflow or not.
 ** \arg    ClkFcmFlagMendf             The end of the measurement or not.
 ** \arg    ClkFcmFlagErrf              Whether the frequence is abnormal or not.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t Clk_GetFcmFlag(en_clk_fcm_flag_t enFcmFlag)
{
    en_flag_status_t status;

    DDL_ASSERT(IS_FCM_FLAG(enFcmFlag));

    switch(enFcmFlag)
    {
        case ClkFcmFlagOvf:
            status = ((1 == M4_FCM->SR_f.OVF) ? Set : Reset);
            break;
        case ClkFcmFlagMendf:
            status = ((1 == M4_FCM->SR_f.MENDF) ? Set : Reset);
            break;
        default:
            status = ((1 == M4_FCM->SR_f.ERRF) ? Set : Reset);
            break;
    }

    return status;
}

/**
 *******************************************************************************
 ** \brief  Clear the specified fcm flag status.
 **
 ** \param  [in] enFcmFlag              The specified fcm flag.
 ** \arg    ClkFcmFlagOvf               Clear the fcm counter overflow flag.
 ** \arg    ClkFcmFlagMendf             Clear the end of the measurement flag.
 ** \arg    ClkFcmFlagErrf              Clear the frequence abnormal flag.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Clk_ClearFcmFlag(en_clk_fcm_flag_t enFcmFlag)
{
    DDL_ASSERT(IS_FCM_FLAG(enFcmFlag));

    switch(enFcmFlag)
    {
        case ClkFcmFlagOvf:
            M4_FCM->CLR_f.OVFCLR = Set;
            break;
        case ClkFcmFlagMendf:
            M4_FCM->CLR_f.MENDFCLR = Set;
            break;
        default:
            M4_FCM->CLR_f.ERRFCLR = Set;
            break;
    }
}

//@} // ClkGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

