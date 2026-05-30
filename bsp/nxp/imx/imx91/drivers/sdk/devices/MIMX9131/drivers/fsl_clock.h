/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @brief CLOCK driver version. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(1, 0, 1))

/*!
 * @brief CCM reg macros to map corresponding registers.
 */
#define CCM_REG_OFF(root, off) (*((volatile uint32_t *)((uintptr_t)(root) + (off))))
#define CCM_REG(root)          CCM_REG_OFF(root, 0U)

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY \
    (250000000UL) /* When using Overdrive Voltage, the maximum frequency of cm33 is 250 MHz */
#endif

/*! LPM_SETTING
 *  0b000..LPCG will be OFF in any CPU mode.
 *  0b001..LPCG will be ON in RUN mode, OFF in WAIT/STOP/SUSPEND mode.
 *  0b010..LPCG will be ON in RUN/WAIT mode, OFF in STOP/SUSPEND mode.
 *  0b011..LPCG will be ON in RUN/WAIT/STOP mode, OFF in SUSPEND mode.
 *  0b100..LPCG will be ON in RUN/WAIT/STOP/SUSPEND mode.
 */
#define CCM_LPCG_LPM_SETTING_0 (0U)
#define CCM_LPCG_LPM_SETTING_1 (1U)
#define CCM_LPCG_LPM_SETTING_2 (2U)
#define CCM_LPCG_LPM_SETTING_3 (3U)
#define CCM_LPCG_LPM_SETTING_4 (4U)

/*******************************************************************************
 * PLL Definitions
 ******************************************************************************/

/*! @brief PLL initialzation data. */
typedef struct _fracn_pll_init
{
    uint32_t rdiv;
    uint32_t mfi;
    uint32_t mfn;
    uint32_t mfd;
    uint32_t odiv;
} fracn_pll_init_t;

/*! @brief PLL PFD initialzation data. */
typedef struct _fracn_pll_pfd_init
{
    uint32_t mfi;
    uint32_t mfn;
    bool div2_en;
} fracn_pll_pfd_init_t;

/*!
 * @brief PLL init.
 *
 * @param pll PLL base addr.
 * @param pll_cfg PLL initailization data.
 */
static inline void CLOCK_PllInit(PLL_Type *pll, const fracn_pll_init_t *pll_cfg)
{
    /* Bypass PLL */
    pll->CTRL.SET = PLL_CTRL_CLKMUX_BYPASS_MASK;
    /* Disable output and PLL */
    pll->CTRL.CLR = PLL_CTRL_CLKMUX_EN_MASK | PLL_CTRL_POWERUP_MASK;
    /* Set rdiv, mfi, and odiv */
    pll->DIV.RW = PLL_DIV_RDIV(pll_cfg->rdiv) | PLL_DIV_MFI(pll_cfg->mfi) | PLL_DIV_ODIV(pll_cfg->odiv);
    /* Disable spread spectrum modulation */
    pll->SPREAD_SPECTRUM.CLR = PLL_SPREAD_SPECTRUM_ENABLE_MASK;
    /* Set mfn and mfd */
    pll->NUMERATOR.RW   = PLL_NUMERATOR_MFN(pll_cfg->mfn);
    pll->DENOMINATOR.RW = PLL_DENOMINATOR_MFD(pll_cfg->mfd);

    /* Power up for locking */
    pll->CTRL.SET = PLL_CTRL_POWERUP_MASK;
    while ((pll->PLL_STATUS & PLL_PLL_STATUS_PLL_LOCK_MASK) == 0UL)
    {
    }

    /* Enable PLL and clean bypass*/
    pll->CTRL.SET = PLL_CTRL_CLKMUX_EN_MASK;
    pll->CTRL.CLR = PLL_CTRL_CLKMUX_BYPASS_MASK;
    __DSB();
    __ISB();
}

/*!
 * @brief PLL PFD init.
 *
 * @param pll PLL base addr.
 * @param pfd_n The PFD index number.
 * @param pfd_cfg PLL PFD initailization data.
 */
static inline void CLOCK_PllPfdInit(PLL_Type *pll, uint32_t pfd_n, const fracn_pll_pfd_init_t *pfd_cfg)
{
    /* Bypass DFS*/
    pll->DFS[pfd_n].DFS_CTRL.SET = PLL_DFS_BYPASS_EN_MASK;
    /* Disable output and DFS */
    pll->DFS[pfd_n].DFS_CTRL.CLR = PLL_DFS_CLKOUT_EN_MASK | PLL_DFS_ENABLE_MASK;
    /* Set mfi and mfn */
    pll->DFS[pfd_n].DFS_DIV.RW = PLL_DFS_MFI(pfd_cfg->mfi) | PLL_DFS_MFN(pfd_cfg->mfn);
    /* Enable output and DFS*/
    pll->DFS[pfd_n].DFS_CTRL.SET = PLL_DFS_CLKOUT_EN_MASK;
    /* Enable div2 */
    if (pfd_cfg->div2_en)
    {
        pll->DFS[pfd_n].DFS_CTRL.SET = PLL_DFS_CLKOUT_DIVBY2_EN_MASK;
    }
    /* Enable DFS for locking*/
    pll->DFS[pfd_n].DFS_CTRL.SET = PLL_DFS_ENABLE_MASK;
    while (((pll->DFS_STATUS & PLL_DFS_STATUS_DFS_OK_MASK) & (1UL << pfd_n)) == 0UL)
    {
    }
    /* Clean bypass */
    pll->DFS[pfd_n].DFS_CTRL.CLR = PLL_DFS_BYPASS_EN_MASK;
    __DSB();
    __ISB();
}

/*******************************************************************************
 * Clock Source Definitions
 ******************************************************************************/

/*!
 * @brief Clock name.
 */
typedef enum _clock_name
{
    kCLOCK_Osc24M          = 0,  /*!< 24MHz Oscillator. */
    kCLOCK_ArmPll          = 1,  /* ARM PLL */
    kCLOCK_ArmPllOut       = 2,  /* ARM PLL Out */
    kCLOCK_DramPll         = 3,  /* DRAM PLL */
    kCLOCK_DramPllOut      = 4,  /* DRAM PLL Out */
    kCLOCK_SysPll1         = 5,  /* SYSTEM PLL1 */
    kCLOCK_SysPll1Pfd0     = 6,  /* SYSTEM PLL1 PFD0 */
    kCLOCK_SysPll1Pfd0Div2 = 7,  /* SYSTEM PLL1 PFD0 DIV2  */
    kCLOCK_SysPll1Pfd1     = 8,  /* SYSTEM PLL1 PFD1 */
    kCLOCK_SysPll1Pfd1Div2 = 9,  /* SYSTEM PLL1 PFD1 DIV2  */
    kCLOCK_SysPll1Pfd2     = 10, /* SYSTEM PLL1 PFD2 */
    kCLOCK_SysPll1Pfd2Div2 = 11, /* SYSTEM PLL1 PFD2 DIV2  */
    kCLOCK_AudioPll1       = 12, /* AUDIO PLL1 */
    kCLOCK_AudioPll1Out    = 13, /* AUDIO PLL1 Out */
    kCLOCK_VideoPll1       = 14, /* VEDIO PLL1 */
    kCLOCK_VideoPll1Out    = 15, /* VEDIO PLL1 Out */
    kCLOCK_Ext             = 16, /* Ext */
} clock_name_t;

extern const clock_name_t s_clockSourceName[][4];
/*******************************************************************************
 * Clock Root Definitions
 ******************************************************************************/

/*! @brief Clock root configuration */
typedef struct _clock_root_config_t
{
    bool clockOff;
    uint8_t mux; /*!< See #clock_root_mux_source_t for details. */
    uint8_t div; /*!< it's the actual divider */
} clock_root_config_t;

/*!
 * @brief Root clock index
 */
typedef enum _clock_root
{
    kCLOCK_Root_A55Periph      = 0,  /*!< CLOCK Root Arm A55 Periph. */
    kCLOCK_Root_A55MtrBus      = 1,  /*!< CLOCK Root Arm A55 MTR BUS. */
    kCLOCK_Root_A55            = 2,  /*!< CLOCK Root Arm A55. */
    kCLOCK_Root_M33            = 3,  /*!< CLOCK Root M33. */
    kCLOCK_Root_Sentinel       = 4,  /*!< CLOCK Root Sentinel. */
    kCLOCK_Root_BusWakeup      = 5,  /*!< CLOCK Root Bus Wakeup. */
    kCLOCK_Root_BusAon         = 6,  /*!< CLOCK Root Bus Aon. */
    kCLOCK_Root_WakeupAxi      = 7,  /*!< CLOCK Root Wakeup Axi. */
    kCLOCK_Root_SwoTrace       = 8,  /*!< CLOCK Root Swo Trace. */
    kCLOCK_Root_M33Systick     = 9,  /*!< CLOCK Root M33 Systick. */
    kCLOCK_Root_Flexio1        = 10, /*!< CLOCK Root Flexio1. */
    kCLOCK_Root_Flexio2        = 11, /*!< CLOCK Root Flexio2. */
    kCLOCK_Root_Lpit1          = 12, /*!< CLOCK Root Lpit1. */
    kCLOCK_Root_Lpit2          = 13, /*!< CLOCK Root Lpit2. */
    kCLOCK_Root_Lptmr1         = 14, /*!< CLOCK Root Lptmr1. */
    kCLOCK_Root_Lptmr2         = 15, /*!< CLOCK Root Lptmr2. */
    kCLOCK_Root_Tpm1           = 16, /*!< CLOCK Root Tpm1. */
    kCLOCK_Root_Tpm2           = 17, /*!< CLOCK Root Tpm2. */
    kCLOCK_Root_Tpm3           = 18, /*!< CLOCK Root Tpm3. */
    kCLOCK_Root_Tpm4           = 19, /*!< CLOCK Root Tpm4. */
    kCLOCK_Root_Tpm5           = 20, /*!< CLOCK Root Tpm5. */
    kCLOCK_Root_Tpm6           = 21, /*!< CLOCK Root Tpm6. */
    kCLOCK_Root_Flexspi1       = 22, /*!< CLOCK Root Flexspi1. */
    kCLOCK_Root_Can1           = 23, /*!< CLOCK Root Can1. */
    kCLOCK_Root_Can2           = 24, /*!< CLOCK Root Can2. */
    kCLOCK_Root_Lpuart1        = 25, /*!< CLOCK Root Lpuart1. */
    kCLOCK_Root_Lpuart2        = 26, /*!< CLOCK Root Lpuart2. */
    kCLOCK_Root_Lpuart3        = 27, /*!< CLOCK Root Lpuart3. */
    kCLOCK_Root_Lpuart4        = 28, /*!< CLOCK Root Lpuart4. */
    kCLOCK_Root_Lpuart5        = 29, /*!< CLOCK Root Lpuart5. */
    kCLOCK_Root_Lpuart6        = 30, /*!< CLOCK Root Lpuart6. */
    kCLOCK_Root_Lpuart7        = 31, /*!< CLOCK Root Lpuart7. */
    kCLOCK_Root_Lpuart8        = 32, /*!< CLOCK Root Lpuart8. */
    kCLOCK_Root_Lpi2c1         = 33, /*!< CLOCK Root Lpi2c1. */
    kCLOCK_Root_Lpi2c2         = 34, /*!< CLOCK Root Lpi2c2. */
    kCLOCK_Root_Lpi2c3         = 35, /*!< CLOCK Root Lpi2c3. */
    kCLOCK_Root_Lpi2c4         = 36, /*!< CLOCK Root Lpi2c4. */
    kCLOCK_Root_Lpi2c5         = 37, /*!< CLOCK Root Lpi2c5. */
    kCLOCK_Root_Lpi2c6         = 38, /*!< CLOCK Root Lpi2c6. */
    kCLOCK_Root_Lpi2c7         = 39, /*!< CLOCK Root Lpi2c7. */
    kCLOCK_Root_Lpi2c8         = 40, /*!< CLOCK Root Lpi2c8. */
    kCLOCK_Root_Lpspi1         = 41, /*!< CLOCK Root Lpspi1. */
    kCLOCK_Root_Lpspi2         = 42, /*!< CLOCK Root Lpspi2. */
    kCLOCK_Root_Lpspi3         = 43, /*!< CLOCK Root Lpspi3. */
    kCLOCK_Root_Lpspi4         = 44, /*!< CLOCK Root Lpspi4. */
    kCLOCK_Root_Lpspi5         = 45, /*!< CLOCK Root Lpspi5. */
    kCLOCK_Root_Lpspi6         = 46, /*!< CLOCK Root Lpspi6. */
    kCLOCK_Root_Lpspi7         = 47, /*!< CLOCK Root Lpspi7. */
    kCLOCK_Root_Lpspi8         = 48, /*!< CLOCK Root Lpspi8. */
    kCLOCK_Root_I3c1           = 49, /*!< CLOCK Root I3c1. */
    kCLOCK_Root_I3c2           = 50, /*!< CLOCK Root I3c2. */
    kCLOCK_Root_Usdhc1         = 51, /*!< CLOCK Root Usdhc1. */
    kCLOCK_Root_Usdhc2         = 52, /*!< CLOCK Root Usdhc2. */
    kCLOCK_Root_Usdhc3         = 53, /*!< CLOCK Root Usdhc3. */
    kCLOCK_Root_Sai1           = 54, /*!< CLOCK Root Sai1. */
    kCLOCK_Root_Sai2           = 55, /*!< CLOCK Root Sai2. */
    kCLOCK_Root_Sai3           = 56, /*!< CLOCK Root Sai3. */
    kCLOCK_Root_CcmCko1        = 57, /*!< CLOCK Root Ccm Cko1. */
    kCLOCK_Root_CcmCko2        = 58, /*!< CLOCK Root Ccm Cko2. */
    kCLOCK_Root_CcmCko3        = 59, /*!< CLOCK Root Ccm Cko3. */
    kCLOCK_Root_CcmCko4        = 60, /*!< CLOCK Root Ccm Cko4. */
    kCLOCK_Root_Hsio           = 61, /*!< CLOCK Root Hsio. */
    kCLOCK_Root_HsioUsbTest60M = 62, /*!< CLOCK Root Hsio Usb Test 60M. */
    kCLOCK_Root_HsioAcscan80M  = 63, /*!< CLOCK Root Hsio Acscan 80M. */
    kCLOCK_Root_HsioAcscan480M = 64, /*!< CLOCK Root Hsio Acscan 480M. */
    kCLOCK_Root_Nic            = 65, /*!< CLOCK Root Nic. */
    kCLOCK_Root_NicApb         = 66, /*!< CLOCK Root Nic Apb. */
    kCLOCK_Root_MlApb          = 67, /*!< CLOCK Root Ml Apb. */
    kCLOCK_Root_Ml             = 68, /*!< CLOCK Root Ml. */
    kCLOCK_Root_MediaAxi       = 69, /*!< CLOCK Root Media Axi. */
    kCLOCK_Root_MediaApb       = 70, /*!< CLOCK Root Media Apb. */
    kCLOCK_Root_MediaLdb       = 71, /*!< CLOCK Root Media Ldb. */
    kCLOCK_Root_MediaDispPix   = 72, /*!< CLOCK Root Media Disp Pix. */
    kCLOCK_Root_CamPix         = 73, /*!< CLOCK Root Cam Pix. */
    kCLOCK_Root_MipiTestByte   = 74, /*!< CLOCK Root Mipi Test Byte. */
    kCLOCK_Root_MipiPhyCfg     = 75, /*!< CLOCK Root Mipi Phy Cfg. */
    kCLOCK_Root_DramAlt        = 76, /*!< CLOCK Root Dram Alt. */
    kCLOCK_Root_DramApb        = 77, /*!< CLOCK Root Dram Apb. */
    kCLOCK_Root_Adc            = 78, /*!< CLOCK Root Adc. */
    kCLOCK_Root_Pdm            = 79, /*!< CLOCK Root Pdm. */
    kCLOCK_Root_Tstmr1         = 80, /*!< CLOCK Root Tstmr1. */
    kCLOCK_Root_Tstmr2         = 81, /*!< CLOCK Root Tstmr2. */
    kCLOCK_Root_Mqs1           = 82, /*!< CLOCK Root MQS1. */
    kCLOCK_Root_Mqs2           = 83, /*!< CLOCK Root MQS2. */
    kCLOCK_Root_AudioXCVR      = 84, /*!< CLOCK Root Audio XCVR. */
    kCLOCK_Root_Spdif          = 85, /*!< CLOCK Root Spdif. */
    kCLOCK_Root_Enet           = 86, /*!< CLOCK Root Enet. */
    kCLOCK_Root_EnetTimer1     = 87, /*!< CLOCK Root Enet Timer1. */
    kCLOCK_Root_EnetTimer2     = 88, /*!< CLOCK Root Enet Timer2. */
    kCLOCK_Root_EnetRef        = 89, /*!< CLOCK Root Enet Ref. */
    kCLOCK_Root_EnetRefPhy     = 90, /*!< CLOCK Root Enet Ref Phy. */
    kCLOCK_Root_I3c1Slow       = 91, /*!< CLOCK Root I3c1Slow. */
    kCLOCK_Root_I3c2Slow       = 92, /*!< CLOCK Root I3c2Slow. */
    kCLOCK_Root_UsbPhyBurunin  = 93, /*!< CLOCK Root Usb Phy Burunin. */
    kCLOCK_Root_PalCameScan    = 94, /*!< CLOCK Root Pal Came Scan. */
} clock_root_t;

/*!
 * @brief The enumerator of clock roots' clock source mux value.
 */
typedef enum _clock_root_mux_source
{
    /* ARM A55 Periph */
    kCLOCK_A55PERIPH_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_A55PERIPH_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_A55PERIPH_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_A55PERIPH_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* ARM A55 MTR BUS */
    kCLOCK_A55MTRBUS_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_A55MTRBUS_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_A55MTRBUS_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_A55MTRBUS_ClockRoot_MuxVideoPll1Out    = 3U,

    /* ARM A55 */
    kCLOCK_A55_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_A55_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_A55_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_A55_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* M33 */
    kCLOCK_M33_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_M33_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_M33_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_M33_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Sentinel */
    kCLOCK_SENTINEL_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_SENTINEL_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_SENTINEL_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_SENTINEL_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Bus Wakeup */
    kCLOCK_BUSWAKEUP_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_BUSWAKEUP_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_BUSWAKEUP_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_BUSWAKEUP_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Bus Aon */
    kCLOCK_BUSAON_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_BUSAON_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_BUSAON_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_BUSAON_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Wakeup Axi */
    kCLOCK_WAKEUPAXI_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_WAKEUPAXI_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_WAKEUPAXI_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_WAKEUPAXI_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Swo Trace */
    kCLOCK_SWOTRACE_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_SWOTRACE_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_SWOTRACE_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_SWOTRACE_ClockRoot_MuxVideoPll1Out    = 3U,

    /* M33 Systick */
    kCLOCK_M33SYSTICK_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_M33SYSTICK_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_M33SYSTICK_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_M33SYSTICK_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Flexio1 */
    kCLOCK_FLEXIO1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_FLEXIO1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Flexio2 */
    kCLOCK_FLEXIO2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_FLEXIO2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpit1 */
    kCLOCK_LPIT1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPIT1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPIT1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPIT1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpit2 */
    kCLOCK_LPIT2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPIT2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPIT2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPIT2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lptmr1 */
    kCLOCK_LPTMR1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPTMR1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPTMR1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPTMR1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lptmr2 */
    kCLOCK_LPTMR2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPTMR2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPTMR2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPTMR2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Tpm1 */
    kCLOCK_TPM1_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_TPM1_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_TPM1_ClockRoot_MuxAudioPll1Out = 2U,
    kCLOCK_TPM1_ClockRoot_MuxExt          = 3U,

    /* Tpm2 */
    kCLOCK_TPM2_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_TPM2_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_TPM2_ClockRoot_MuxAudioPll1Out = 2U,
    kCLOCK_TPM2_ClockRoot_MuxExt          = 3U,

    /* Tpm3 */
    kCLOCK_TPM3_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_TPM3_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_TPM3_ClockRoot_MuxAudioPll1Out = 2U,
    kCLOCK_TPM3_ClockRoot_MuxExt          = 3U,

    /* Tpm4 */
    kCLOCK_TPM4_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_TPM4_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_TPM4_ClockRoot_MuxAudioPll1Out = 2U,
    kCLOCK_TPM4_ClockRoot_MuxExt          = 3U,

    /* Tpm5 */
    kCLOCK_TPM5_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_TPM5_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_TPM5_ClockRoot_MuxAudioPll1Out = 2U,
    kCLOCK_TPM5_ClockRoot_MuxExt          = 3U,

    /* Tpm6 */
    kCLOCK_TPM6_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_TPM6_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_TPM6_ClockRoot_MuxAudioPll1Out = 2U,
    kCLOCK_TPM6_ClockRoot_MuxExt          = 3U,

    /* Flexspi1 */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Can1 */
    kCLOCK_CAN1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAN1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_CAN1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_CAN1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Can2 */
    kCLOCK_CAN2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAN2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_CAN2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_CAN2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart1 */
    kCLOCK_LPUART1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart2 */
    kCLOCK_LPUART2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart3 */
    kCLOCK_LPUART3_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART3_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART3_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART3_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart4 */
    kCLOCK_LPUART4_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART4_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART4_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART4_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart5 */
    kCLOCK_LPUART5_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART5_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART5_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART5_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart6 */
    kCLOCK_LPUART6_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART6_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART6_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART6_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart7 */
    kCLOCK_LPUART7_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART7_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART7_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART7_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpuart8 */
    kCLOCK_LPUART8_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART8_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPUART8_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPUART8_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c1 */
    kCLOCK_LPI2C1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c2 */
    kCLOCK_LPI2C2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c3 */
    kCLOCK_LPI2C3_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C3_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c4 */
    kCLOCK_LPI2C4_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C4_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c5 */
    kCLOCK_LPI2C5_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C5_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c6 */
    kCLOCK_LPI2C6_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C6_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c7 */
    kCLOCK_LPI2C7_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C7_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C7_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C7_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpi2c8 */
    kCLOCK_LPI2C8_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C8_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPI2C8_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPI2C8_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpspi1 */
    kCLOCK_LPSPI1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpspi2 */
    kCLOCK_LPSPI2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpspi3 */
    kCLOCK_LPSPI3_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI3_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpspi4 */
    kCLOCK_LPSPI4_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI4_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpispi5 */
    kCLOCK_LPSPI5_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI5_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpspi6 */
    kCLOCK_LPSPI6_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI6_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpspi7 */
    kCLOCK_LPSPI7_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI7_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI7_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI7_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Lpspi8 */
    kCLOCK_LPSPI8_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI8_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_LPSPI8_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_LPSPI8_ClockRoot_MuxVideoPll1Out    = 3U,

    /* I3c1 */
    kCLOCK_I3C1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_I3C1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_I3C1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* I3c2 */
    kCLOCK_I3C2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_I3C2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_I3C2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Usdhc1 */
    kCLOCK_Usdhc1_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_Usdhc1_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_Usdhc1_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_Usdhc1_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Usdhc2 */
    kCLOCK_Usdhc2_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_Usdhc2_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_Usdhc2_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_Usdhc2_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Usdhc3 */
    kCLOCK_Usdhc3_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_Usdhc3_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_Usdhc3_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_Usdhc3_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Sai1 */
    kCLOCK_SAI1_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_SAI1_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_SAI1_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_SAI1_ClockRoot_MuxExt          = 3U,

    /* Sai2 */
    kCLOCK_SAI2_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_SAI2_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_SAI2_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_SAI2_ClockRoot_MuxExt          = 3U,

    /* Sai3 */
    kCLOCK_SAI3_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_SAI3_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_SAI3_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_SAI3_ClockRoot_MuxExt          = 3U,

    /* Ccm Cko1 */
    kCLOCK_CCMCKO1_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_CCMCKO1_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_CCMCKO1_ClockRoot_MuxSysPll1Pfd1  = 2U,
    kCLOCK_CCMCKO1_ClockRoot_MuxAudioPll1Out = 3U,

    /* Ccm Cko2 */
    kCLOCK_CCMCKO2_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_CCMCKO2_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_CCMCKO2_ClockRoot_MuxSysPll1Pfd1  = 2U,
    kCLOCK_CCMCKO2_ClockRoot_MuxVideoPll1Out = 3U,

    /* Ccm Cko3 */
    kCLOCK_CCMCKO3_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_CCMCKO3_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_CCMCKO3_ClockRoot_MuxSysPll1Pfd1  = 2U,
    kCLOCK_CCMCKO3_ClockRoot_MuxAudioPll1Out = 3U,

    /* Ccm Cko4 */
    kCLOCK_CCMCKO4_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_CCMCKO4_ClockRoot_MuxSysPll1Pfd0  = 1U,
    kCLOCK_CCMCKO4_ClockRoot_MuxSysPll1Pfd1  = 2U,
    kCLOCK_CCMCKO4_ClockRoot_MuxVideoPll1Out = 3U,

    /* Hsio */
    kCLOCK_HSIO_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIO_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_HSIO_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_HSIO_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Hsio Usb Test 60M */
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Hsio Acscan 80M */
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Hsio Acscan 480M */
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Nic */
    kCLOCK_NIC_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_NIC_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_NIC_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_NIC_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Nic Apb */
    kCLOCK_NICAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_NICAPB_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_NICAPB_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_NICAPB_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Ml Apb */
    kCLOCK_MLAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_MLAPB_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_MLAPB_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_MLAPB_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Ml */
    kCLOCK_ML_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_ML_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_ML_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_ML_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Media Axi */
    kCLOCK_MEDIAAXI_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_MEDIAAXI_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_MEDIAAXI_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_MEDIAAXI_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Media Apb */
    kCLOCK_MEDIAAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_MEDIAAPB_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_MEDIAAPB_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_MEDIAAPB_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Media Ldb */
    kCLOCK_MEDIALDB_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_MEDIALDB_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_MEDIALDB_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_MEDIALDB_ClockRoot_MuxSysPll1Pfd0  = 3U,

    /* Media Disp Pix */
    kCLOCK_MEDIADISPPIX_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_MEDIADISPPIX_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_MEDIADISPPIX_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_MEDIADISPPIX_ClockRoot_MuxSysPll1Pfd0  = 3U,

    /* Cam Pix */
    kCLOCK_CAMPIX_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_CAMPIX_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_CAMPIX_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_CAMPIX_ClockRoot_MuxSysPll1Pfd0  = 3U,

    /* Mipi Test Byte */
    kCLOCK_MIPITESTBYTE_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_MIPITESTBYTE_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_MIPITESTBYTE_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_MIPITESTBYTE_ClockRoot_MuxSysPll1Pfd0  = 3U,

    /* Mipi Phy Cfg */
    kCLOCK_MIPIPHYCFG_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_MIPIPHYCFG_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_MIPIPHYCFG_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_MIPIPHYCFG_ClockRoot_MuxSysPll1Pfd0  = 3U,

    /* Dram Alt */
    kCLOCK_DRAMALT_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DRAMALT_ClockRoot_MuxSysPll1Pfd0 = 1U,
    kCLOCK_DRAMALT_ClockRoot_MuxSysPll1Pfd1 = 2U,
    kCLOCK_DRAMALT_ClockRoot_MuxSysPll1Pfd2 = 3U,

    /* Dram Apb */
    kCLOCK_DRAMAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_DRAMAPB_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_DRAMAPB_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_DRAMAPB_ClockRoot_MuxSysPll1Pfd2Div2 = 3U,

    /* Adc */
    kCLOCK_ADC_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ADC_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_ADC_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_ADC_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Pdm */
    kCLOCK_PDM_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_PDM_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_PDM_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_PDM_ClockRoot_MuxExt          = 3U,

    /* Tstmr1 */
    kCLOCK_TSTMR1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_TSTMR1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_TSTMR1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_TSTMR1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Tstmr2 */
    kCLOCK_TSTMR2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_TSTMR2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_TSTMR2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_TSTMR2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* MQS1 */
    kCLOCK_MQS1_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_MQS1_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_MQS1_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_MQS1_ClockRoot_MuxExt          = 3U,

    /* MQS2 */
    kCLOCK_MQS2_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_MQS2_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_MQS2_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_MQS2_ClockRoot_MuxExt          = 3U,

    /* Audio XCVR */
    kCLOCK_AUDIOXCVR_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_AUDIOXCVR_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_AUDIOXCVR_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_AUDIOXCVR_ClockRoot_MuxSysPll1Pfd2Div2 = 3U,

    /* Spdif */
    kCLOCK_SPDIF_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_SPDIF_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_SPDIF_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_SPDIF_ClockRoot_MuxExt          = 3U,

    /* Enet */
    kCLOCK_ENET_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENET_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_ENET_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_ENET_ClockRoot_MuxSysPll1Pfd2Div2 = 3U,

    /* Enet Timer1 */
    kCLOCK_ENETTSTMR1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENETTSTMR1_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_ENETTSTMR1_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_ENETTSTMR1_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Enet Timer2 */
    kCLOCK_ENETTSTMR2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENETTSTMR2_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_ENETTSTMR2_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_ENETTSTMR2_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Enet Ref */
    kCLOCK_ENETREF_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENETREF_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_ENETREF_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_ENETREF_ClockRoot_MuxSysPll1Pfd2Div2 = 3U,

    /* Enet Ref Phy */
    kCLOCK_ENETREFPHY_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENETREFPHY_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_ENETREFPHY_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_ENETREFPHY_ClockRoot_MuxVideoPll1Out    = 3U,

    /* I3c1 Slow */
    kCLOCK_I3C1SLOW_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C1SLOW_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_I3C1SLOW_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_I3C1SLOW_ClockRoot_MuxVideoPll1Out    = 3U,

    /* I3c2 Slow */
    kCLOCK_I3C2SLOW_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C2SLOW_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_I3C2SLOW_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_I3C2SLOW_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Usb Phy Burunin */
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxSysPll1Pfd0Div2 = 1U,
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxSysPll1Pfd1Div2 = 2U,
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxVideoPll1Out    = 3U,

    /* Pal Came Scan */
    kCLOCK_PALCAMESCAN_ClockRoot_MuxOsc24M       = 0U,
    kCLOCK_PALCAMESCAN_ClockRoot_MuxAudioPll1Out = 1U,
    kCLOCK_PALCAMESCAN_ClockRoot_MuxVideoPll1Out = 2U,
    kCLOCK_PALCAMESCAN_ClockRoot_MuxSysPll1Pfd2  = 3U,
} clock_root_mux_source_t;

/*******************************************************************************
 * Clock Gate Definitions
 ******************************************************************************/

/*! @brief Clock gate value */
typedef enum _clock_gate_value
{
    kCLOCK_Off = CCM_LPCG_LPM_SETTING_0,
    kCLOCK_On  = CCM_LPCG_LPM_SETTING_4,
} clock_gate_value_t;

/*!
 * @brief Clock LPCG index (Clock Gating Channel)
 */
typedef enum _clock_lpcg
{
    kCLOCK_A55            = 0,
    kCLOCK_Cm33           = 1,
    kCLOCK_Arm_Trout      = 2,
    kCLOCK_Sentinel       = 3,
    kCLOCK_Sim_Wakeup     = 4,
    kCLOCK_Sim_Aon        = 5,
    kCLOCK_Sim_Mega       = 6,
    kCLOCK_Anadig         = 7,
    kCLOCK_Src            = 8,
    kCLOCK_Ccm            = 9,
    kCLOCK_Gpc            = 10,
    kCLOCK_Adc1           = 11,
    kCLOCK_Wdog1          = 12,
    kCLOCK_Wdog2          = 13,
    kCLOCK_Wdog3          = 14,
    kCLOCK_Wdog4          = 15,
    kCLOCK_Wdog5          = 16,
    kCLOCK_Sema1          = 17,
    kCLOCK_Sema2          = 18,
    kCLOCK_Mu_A           = 19,
    kCLOCK_Mu_B           = 20,
    kCLOCK_Edma1          = 21,
    kCLOCK_Edma2          = 22,
    kCLOCK_Romcp_A55      = 23,
    kCLOCK_Romcp_M33      = 24,
    kCLOCK_Flexspi1       = 25,
    kCLOCK_Aon_Trdc       = 26,
    kCLOCK_Wkup_Trdc      = 27,
    kCLOCK_Ocotp          = 28,
    kCLOCK_Bbsm_Hp        = 29,
    kCLOCK_Bbsm           = 30,
    kCLOCK_Cstrace        = 31,
    kCLOCK_Csswo          = 32,
    kCLOCK_Iomuxc         = 33,
    kCLOCK_Gpio1          = 34,
    kCLOCK_Gpio2          = 35,
    kCLOCK_Gpio3          = 36,
    kCLOCK_Gpio4          = 37,
    kCLOCK_Flexio1        = 38,
    kCLOCK_Flexio2        = 39,
    kCLOCK_Lpit1          = 40,
    kCLOCK_Lpit2          = 41,
    kCLOCK_Lptmr1         = 42,
    kCLOCK_Lptmr2         = 43,
    kCLOCK_Tpm1           = 44,
    kCLOCK_Tpm2           = 45,
    kCLOCK_Tpm3           = 46,
    kCLOCK_Tpm4           = 47,
    kCLOCK_Tpm5           = 48,
    kCLOCK_Tpm6           = 49,
    kCLOCK_Can1           = 50,
    kCLOCK_Can2           = 51,
    kCLOCK_Lpuart1        = 52,
    kCLOCK_Lpuart2        = 53,
    kCLOCK_Lpuart3        = 54,
    kCLOCK_Lpuart4        = 55,
    kCLOCK_Lpuart5        = 56,
    kCLOCK_Lpuart6        = 57,
    kCLOCK_Lpuart7        = 58,
    kCLOCK_Lpuart8        = 59,
    kCLOCK_Lpi2c1         = 60,
    kCLOCK_Lpi2c2         = 61,
    kCLOCK_Lpi2c3         = 62,
    kCLOCK_Lpi2c4         = 63,
    kCLOCK_Lpi2c5         = 64,
    kCLOCK_Lpi2c6         = 65,
    kCLOCK_Lpi2c7         = 66,
    kCLOCK_Lpi2c8         = 67,
    kCLOCK_Lpspi1         = 68,
    kCLOCK_Lpspi2         = 69,
    kCLOCK_Lpspi3         = 70,
    kCLOCK_Lpspi4         = 71,
    kCLOCK_Lpspi5         = 72,
    kCLOCK_Lpspi6         = 73,
    kCLOCK_Lpspi7         = 74,
    kCLOCK_Lpspi8         = 75,
    kCLOCK_I3c1           = 76,
    kCLOCK_I3c2           = 77,
    kCLOCK_Usdhc1         = 78,
    kCLOCK_Usdhc2         = 79,
    kCLOCK_Usdhc3         = 80,
    kCLOCK_Sai1           = 81,
    kCLOCK_Sai2           = 82,
    kCLOCK_Sai3           = 83,
    kCLOCK_Ssi_W2ao       = 84,
    kCLOCK_Ssi_Ao2w       = 85,
    kCLOCK_Mipi_Csi       = 86,
    kCLOCK_Mipi_Dsi       = 87,
    kCLOCK_Lvds           = 88,
    kCLOCK_Lcdif          = 89,
    kCLOCK_Pxp            = 90,
    kCLOCK_Isi            = 91,
    kCLOCK_Nic_Media      = 92,
    kCLOCK_Ddr_Dfi        = 93,
    kCLOCK_Ddr_Ctl        = 94,
    kCLOCK_Ddr_Dfi_Ctl    = 95,
    kCLOCK_Ddr_Ssi        = 96,
    kCLOCK_Ddr_Bypass     = 97,
    kCLOCK_Ddr_Apb        = 98,
    kCLOCK_Ddr_Drampll    = 99,
    kCLOCK_Ddr_Clk_Ctl    = 100,
    kCLOCK_Nic_Central    = 101,
    kCLOCK_Gic600         = 102,
    kCLOCK_Nic_Apb        = 103,
    kCLOCK_Usb_Controller = 104,
    kCLOCK_Usb_Test_60m   = 105,
    kCLOCK_Hsio_Trout_24m = 106,
    kCLOCK_Pdm            = 107,
    kCLOCK_Mqs1           = 108,
    kCLOCK_Mqs2           = 109,
    kCLOCK_Aud_Xcvr       = 110,
    kCLOCK_Nicmix_Mecc    = 111,
    kCLOCK_Spdif          = 112,
    kCLOCK_Ssi_Ml2nic     = 113,
    kCLOCK_Ssi_Med2nic    = 114,
    kCLOCK_Ssi_Hsio2nic   = 115,
    kCLOCK_Ssi_W2nic      = 116,
    kCLOCK_Ssi_Nic2w      = 117,
    kCLOCK_Ssi_Nic2ddr    = 118,
    kCLOCK_Hsio_32k       = 119,
    kCLOCK_Enet1          = 120,
    kCLOCK_Enet_Qos       = 121,
    kCLOCK_Sys_Cnt        = 122,
    kCLOCK_Tstmr1         = 123,
    kCLOCK_Tstmr2         = 124,
    kCLOCK_Tmc            = 125,
    kCLOCK_Pmro           = 126,
    kCLOCK_IpInvalid,
} clock_lpcg_t;

#define clock_ip_name_t clock_lpcg_t

/*! @brief Clock ip name array for EDMA. */
#define EDMA_CLOCKS                \
    {                              \
        kCLOCK_Edma1, kCLOCK_Edma2 \
    }

/*
 * ! @brief Clock ip name array for MU.
 * clock of MU1_MUA, MU2_MUA is enabled by same LPCG42(Gate signal is clk_enable_mu_a)
 */
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu_A, kCLOCK_Mu_A \
    }

/*! @brief Clock ip name array for LCDIFV3. */
#define LCDIFV3_CLOCKS                 \
    {                                  \
        kCLOCK_IpInvalid, kCLOCK_Lcdif \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                                \
    {                                                                                                               \
        kCLOCK_IpInvalid, kCLOCK_Lpi2c1, kCLOCK_Lpi2c2, kCLOCK_Lpi2c3, kCLOCK_Lpi2c4, kCLOCK_Lpi2c5, kCLOCK_Lpi2c6, \
            kCLOCK_Lpi2c7, kCLOCK_Lpi2c8                                                                            \
    }

/*! @brief Clock ip name array for LPIT. */
#define LPIT_CLOCKS                                  \
    {                                                \
        kCLOCK_IpInvalid, kCLOCK_Lpit1, kCLOCK_Lpit2 \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                                                                                                \
    {                                                                                                               \
        kCLOCK_IpInvalid, kCLOCK_Lpspi1, kCLOCK_Lpspi2, kCLOCK_Lpspi3, kCLOCK_Lpspi4, kCLOCK_Lpspi5, kCLOCK_Lpspi6, \
            kCLOCK_Lpspi7, kCLOCK_Lpspi8                                                                            \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                                                                    \
    {                                                                                 \
        kCLOCK_Tpm1, kCLOCK_Tpm2, kCLOCK_Tpm3, kCLOCK_Tpm4, kCLOCK_Tpm5, kCLOCK_Tpm6, \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS                                    \
    {                                                    \
        kCLOCK_IpInvalid, kCLOCK_Flexio1, kCLOCK_Flexio2 \
    }

/*! @brief Clock ip name array for FLEXSPI. */
#define FLEXSPI_CLOCKS                    \
    {                                     \
        kCLOCK_IpInvalid, kCLOCK_Flexspi1 \
    }

/*! @brief Clock ip name array for TMU. */
#define TMU_CLOCKS  \
    {               \
        kCLOCK_Tmc, \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS                              \
    {                                               \
        kCLOCK_IpInvalid, kCLOCK_Can1, kCLOCK_Can2, \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                     \
    {                                                                                                     \
        kCLOCK_IpInvalid, kCLOCK_Lpuart1, kCLOCK_Lpuart2, kCLOCK_Lpuart3, kCLOCK_Lpuart4, kCLOCK_Lpuart5, \
            kCLOCK_Lpuart6, kCLOCK_Lpuart7, kCLOCK_Lpuart8                                                \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                               \
    {                                                            \
        kCLOCK_IpInvalid, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3, \
    }

/*! @brief Clock ip name array for PDM. */
#define PDM_CLOCKS \
    {              \
        kCLOCK_Pdm \
    }

/*! @brief Clock ip name array for ENET QOS. */
#define ENETQOS_CLOCKS  \
    {                   \
        kCLOCK_Enet_Qos \
    }

/*! @brief Clock ip name array for ENET. */
#define ENET_CLOCKS  \
    {                \
        kCLOCK_Enet1 \
    }

/*! @brief Clock ip name array for I3C. */
#define I3C_CLOCKS                                 \
    {                                              \
        kCLOCK_IpInvalid, kCLOCK_I3c1, kCLOCK_I3c2 \
    }

/*! @brief Clock ip name array for SEMA42. */
#define SEMA42_CLOCKS                                \
    {                                                \
        kCLOCK_IpInvalid, kCLOCK_Sema1, kCLOCK_Sema2 \
    }

/*******************************************************************************
 * Clock Root APIs
 ******************************************************************************/

/*!
 * @brief Set CCM Root Clock MUX node to certain value.
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param src Clock mux value to set, different mux has different value range. See \ref clock_root_mux_source_t.
 */
static inline void CLOCK_SetRootClockMux(clock_root_t root, uint8_t src)
{
    assert(src < 8U);
    CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW =
        (CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & ~(CCM_CLOCK_ROOT_MUX_MASK)) | CCM_CLOCK_ROOT_MUX(src);
    __DSB();
    __ISB();
}

/*!
 * @brief Get CCM Root Clock MUX value.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @return Clock mux value.
 */
static inline uint32_t CLOCK_GetRootClockMux(clock_root_t root)
{
    return (CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & CCM_CLOCK_ROOT_MUX_MASK) >> CCM_CLOCK_ROOT_MUX_SHIFT;
}

/*!
 * @brief Get CCM Root Clock Source.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @param src Clock mux value to get, see \ref clock_root_mux_source_t.
 * @return Clock source
 */
static inline clock_name_t CLOCK_GetRootClockSource(clock_root_t root, uint32_t src)
{
    return s_clockSourceName[root][src];
}

/*!
 * @brief Set CCM Root Clock DIV certain value.
 *
 * @param root Which root clock to set, see \ref clock_root_t.
 * @param div Clock div value to set, different divider has different value range.
 */
static inline void CLOCK_SetRootClockDiv(clock_root_t root, uint8_t div)
{
    assert(div);
    CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW =
        (CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & ~CCM_CLOCK_ROOT_DIV_MASK) |
        CCM_CLOCK_ROOT_DIV((uint32_t)div - 1UL);
    __DSB();
    __ISB();
}

/*!
 * @brief Get CCM DIV node value.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @return divider set for this root
 */
static inline uint32_t CLOCK_GetRootClockDiv(clock_root_t root)
{
    return ((CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & CCM_CLOCK_ROOT_DIV_MASK) >> CCM_CLOCK_ROOT_DIV_SHIFT) +
           1UL;
}

/*!
 * @brief Power Off Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
static inline void CLOCK_PowerOffRootClock(clock_root_t root)
{
    if (0UL == (CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & CCM_CLOCK_ROOT_OFF_MASK))
    {
        CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.SET = CCM_CLOCK_ROOT_OFF_MASK;
        __DSB();
        __ISB();
    }
}

/*!
 * @brief Power On Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
static inline void CLOCK_PowerOnRootClock(clock_root_t root)
{
    CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.CLR = CCM_CLOCK_ROOT_OFF_MASK;
    __DSB();
    __ISB();
}

/*!
 * @brief Configure Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param config root clock config, see \ref clock_root_config_t
 */
static inline void CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config)
{
    assert(config);
    CCM_CTRL->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW = CCM_CLOCK_ROOT_MUX(config->mux) |
                                                       CCM_CLOCK_ROOT_DIV((uint32_t)config->div - 1UL) |
                                                       (config->clockOff ? CCM_CLOCK_ROOT_OFF(config->clockOff) : 0UL);
    __DSB();
    __ISB();
}

/*******************************************************************************
 * Clock Gate APIs
 ******************************************************************************/

/*!
 * @brief Control the clock gate for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 * @param value Clock gate value to set, see \ref clock_gate_value_t.
 */
static inline void CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    CCM_CTRL->LPCG[name].AUTHEN |= CCM_LPCG_AUTHEN_CPULPM_MODE(1U);
    CCM_CTRL->LPCG[name].LPM_CUR = CCM_LPCG_LPM_CUR_LPM_SETTING_CUR(value);
    __DSB();
    __ISB();
}

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_On);
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_lpcg_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_Off);
}

/*******************************************************************************
 * Other APIs
 ******************************************************************************/

/*
 * Setup a variable for clock source frequencies
 */
extern volatile uint32_t g_clockSourceFreq[kCLOCK_Ext + 1];

/*!
 * @brief Gets the clock frequency for a specific IP module.
 *
 * This function gets the IP module clock frequency.
 *
 * @param name Which root clock to get, see \ref clock_root_t.
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetIpFreq(clock_root_t name);

#endif
