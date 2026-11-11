/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_CLOCKS_RA6W1_H
#define BSP_CLOCKS_RA6W1_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "../all/bsp_delay.h"
#include "../all/bsp_mcu_api.h"
#include "../all/bsp_clocks.h"

/* TODO get rid of the following legacy definitions from sdk_defs.h: */
#define REG_GETF(base, reg, field) \
    (((base->reg) & (base ## _ ## reg ## _ ## field ## _Msk)) >> (base ## _ ## reg ## _ ## field ## _Pos))

#define REG_SETF(base, reg, field, new_val)                                \
    base->reg = ((base->reg & ~(base ## _ ## reg ## _ ## field ## _Msk)) | \
                 ((base ## _ ## reg ## _ ## field ## _Msk) &((new_val) << (base ## _ ## reg ## _ ## field ## _Pos))))

#define GLOBAL_INT_DISABLE()                      \
    do {                                          \
        unsigned int __l_irq_rest;                \
        __ASM volatile ("mrs   %0, primask  \n\t" \
                        "mov   r1, $1     \n\t"   \
                        "msr   primask, r1  \n\t" \
                        : "=r" (__l_irq_rest)     \
                        :                         \
                        : "r1"                    \
                        );                        \
        /*DBG_CONFIGURE_HIGH(CMN_TIMING_DEBUG, CMNDBG_CRITICAL_SECTION);*/

#define GLOBAL_INT_RESTORE()                                              \
    if (__l_irq_rest == 0) {                                              \
        /*DBG_CONFIGURE_LOW(CMN_TIMING_DEBUG, CMNDBG_CRITICAL_SECTION);*/ \
    }                                                                     \
    __ASM volatile ("msr   primask, %0  \n\t"                             \
                    :                                                     \
                    : "r" (__l_irq_rest)                                  \
                    :                                                     \
                    );                                                    \
}                                                                         \
    while (0)

#define REG_SET_BIT(base, reg, field)                                 \
    do {                                                              \
        base->reg |= (1 << (base ## _ ## reg ## _ ## field ## _Pos)); \
    } while (0)

#define REG_CLR_BIT(base, reg, field)                           \
    do {                                                        \
        base->reg &= ~(base ## _ ## reg ## _ ## field ## _Msk); \
    } while (0)

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define HW_CLK_DELAY_OVERHEAD_CYCLES    (72)
#define HW_CLK_CYCLES_PER_DELAY_REP     (4)

#define MAX_PLL_LCKCHK_TIME             (0x00007FFF)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**
 * \brief The type of the LP clock
 */
typedef enum lp_clk_is_type
{
    LP_CLK_IS_RCX,                     // 32K internal RC oscillator
    LP_CLK_IS_XTAL32K,                 // 32K Crystal oscillator
    LP_CLK_IS_SWCLK,                   // Test_clk
    LP_CLK_IS_INVALID
} lp_clk_is_t;

/**
 * \}
 */

/**
 * \brief The AMBA High-Performance Bus (AHB) clock divider
 */
typedef enum ahbdiv_type
{
    ahb_div1 = 0,                      //!< Divide by 1
    ahb_div2,                          //!< Divide by 2
    ahb_div4,                          //!< Divide by 4
    ahb_div8,                          //!< Divide by 8
    ahb_div16,                         //!< Divide by 16
} ahb_div_t;

/**
 * \brief The AMBA Peripheral Bus (APB) clock divider
 */
typedef enum apbdiv_type
{
    apb_div1 = 0,                      //!< Divide by 1
    apb_div2,                          //!< Divide by 2
    apb_div4,                          //!< Divide by 4
    apb_div8,                          //!< Divide by 8
    apb_div16,                         //!< Divide by 16
} apb_div_t;

/**
 * \brief Get the divider of the AMBA High Speed Bus.
 *
 * \return The AMBA High Speed Bus divider
 */
__STATIC_FORCEINLINE ahb_div_t hw_clk_get_hclk_div (void)
{
    return (ahb_div_t) REG_GETF(CRG_TOP, CLK_AMBA_REG, HCLK_DIV);
}

/**
 * \brief Set the divider of the AMBA High Speed Bus.
 *
 * \param div The AMBA High Speed Bus divider
 */
__STATIC_FORCEINLINE void hw_clk_set_hclk_div (ahb_div_t div)
{
    BSP_CHECK_DEBUG(div <= ahb_div16);

    GLOBAL_INT_DISABLE();
    REG_SETF(CRG_TOP, CLK_AMBA_REG, HCLK_DIV, div);
    GLOBAL_INT_RESTORE();
}

/**
 * \brief The type of the system clock
 */
typedef enum sys_clk_is_type
{
    SYS_CLK_IS_NONE = 0,               /* RUNNING_AT_LP_CLK */
    SYS_CLK_IS_XTAL40M,                /* RUNNING_AT_XTAL40M */
    SYS_CLK_IS_LP,
    SYS_CLK_IS_PLL240M,                /* RUNNING_AT_PLL240M : descoped */
    SYS_CLK_IS_PLL192M,                /* RUNNING_AT_PLL192M : descoped */
    SYS_CLK_IS_PLL160M,                /* RUNNING_AT_PLL160M */
    SYS_CLK_IS_PLL137M,                /* SYS_CLK_IS_PLL137M */
    SYS_CLK_IS_PLL106M,                /* SYS_CLK_IS_PLL106M */
    SYS_CLK_IS_INVALID
} sys_clk_is_t;

/**
 * \}
 */

/**
 * \brief The type of clock to be calibrated
 */
typedef enum cal_clk_sel_type
{
    CALIBRATE_XTAL32K = 0,
    CALIBRATE_RCX32K,
    CALIBRATE_DIVN_CLK,
} cal_clk_t;

/**
 * \brief The reference clock used for calibration
 */
typedef enum cal_ref_clk_sel_type
{
    CALIBRATE_REF_XTAL32K = 0,
    CALIBRATE_REF_RCX32K,
    CALIBRATE_REF_DIVN_CLK,
    CALIBRATE_REF_EXT,
} cal_ref_clk_t;

/**
 * \brief The system clock type
 *
 * \note Must only be used with functions cm_sys_clk_init/set()
 */
typedef enum sysclk_type
{
    sysclk_RC32    = 0,                //!< RC32
    sysclk_XTAL40M = 2,                //!< 40MHz
    sysclk_PLL480  = 6,                //!< 480MHz
    sysclk_LP      = 255,              //!< not applicable
} sys_clk_t;

/**
 * \brief The CPU clock type (speed)
 *
 */
typedef enum cpu_clk_type
{
    cpuclk_2M  = 2,                    //!< 2.5 MHz, divided by 16 in XTAL
    cpuclk_5M  = 5,                    //!< 5  MHz, divided by 8 in XTAL
    cpuclk_10M = 10,                   //!< 10 MHz, divided by 4 in XTAL
    cpuclk_20M = 20,                   //!< 20 MHz, divided by 2 in XTAL

    cpuclk_26M = 26,                   //!< 26 MHz, divided by 4 in SYSCLK 106MHz
    cpuclk_34M = 34,                   //!< 34 MHz, divided by 4 in SYSCLK 137MHz
    cpuclk_40M = 40,                   //!< 40 MHz, divided by 4 in SYSCLK 160MHz

    cpuclk_53M = 53,                   //!< 53 MHz, divided by 2 in SYSCLK 106MHz
    cpuclk_68M = 68,                   //!< 68 MHz, divided by 2 in SYSCLK 137MHz
    cpuclk_80M = 80,                   //!< 80 MHz, divided by 2 in SYSCLK 160MHz

    cpuclk_106M = 106,                 //!< 106 MHz
    cpuclk_137M = 137,                 //!< 137 MHz
    cpuclk_160M = 160                  //!< 160 MHz
} cpu_clk_t;

/**
 * \brief The type of the fpll clock
 */
typedef enum fpll_clock_type
{
    FPLL_98M = 0,
    FPLL_90M = 1,
    DIVN_40M = 2,
} fpll_clk_t;

/**
 * \brief The type of the fpll mode
 */
typedef enum fpll_clock_mode
{
    FPLL_MODE_USE_IRM = 0,
    FPLL_MODE_NO_IRM  = 1
} fpll_mode_t;

/**
 * \brief Get the XTAL32M settling time.
 *
 * \return The number of 256KHz clock cycles required for XTAL40M to settle
 */
__STATIC_FORCEINLINE uint16_t hw_clk_get_xtalm_settling_time (void)
{
    /* TODO for DA1640x */
    return 0;
}

/**
 * \brief Check if the XTAL40M is enabled.
 *
 * \return true if the XTAL40M is enabled, else false.
 */
__STATIC_INLINE bool hw_clk_check_xtal40m_status (void)
{
    /* TODO for DA1640x */
    return true;
}

/**
 * \brief Activate the XTAL40M.
 */
__STATIC_INLINE void hw_clk_enable_xtal40m (void)
{
    /* Do nothing if XTAL40M is already up and running. */
    if (REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_XTAL40M))
    {
        return;
    }

    // Check if TIM power domain is enabled
#if DEVICE_FPGA
#else
    BSP_CHECK_DEBUG(REG_GETF(CRG_TOP, SYS_STATUS_REG, SYS_IS_UP));
#endif

#if DEVICE_FPGA
    REG_SET_BIT(CRG_COM, XTAL40M_CTRL_REG, XTAL40M_EN);
#else
    REG_SET_BIT(CRG_COM, XTAL40M_CTRL_REG, XTAL40M_EN);

// Delay
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    BSP_CHECK_DEBUG(REG_GETF(CRG_COM, XTAL40M_CTRL_REG, XTAL40M_RDY));
#endif
}

/**
 * \brief Deactivate the XTAL40M.
 */
__STATIC_INLINE void hw_clk_disable_xtal40m (void)
{
    REG_CLR_BIT(CRG_COM, XTAL40M_CTRL_REG, XTAL40M_EN);
}

/**
 * \brief Check if the XTAL40M has settled.
 *
 * \return true if the XTAL40M has settled, else false.
 */
__STATIC_INLINE bool hw_clk_is_xtalm_started (void)
{
    return true;
}

/**
 * \brief Return the clock used as the system clock.
 *
 * \return The type of the system clock
 */
__STATIC_FORCEINLINE sys_clk_is_t hw_clk_get_sysclk (void)
{
    sys_clk_is_t clk = SYS_CLK_IS_NONE;

    if (REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_XTAL40M))
    {
        clk = SYS_CLK_IS_XTAL40M;
    }
    else if (REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_LP_CLK))
    {
        clk = SYS_CLK_IS_LP;
    }
    else if (REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_PLL))
    {
        uint8_t mode = REG_GETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL);
        clk = (sys_clk_is_t) (SYS_CLK_IS_PLL240M + mode);
    }

    BSP_CHECK_DEBUG(clk < SYS_CLK_IS_INVALID);

    return clk;
}

/**
 * \brief Check whether the XTAL32K is the Low Power clock.
 *
 * \return true if XTAL32K is the LP clock, else false.
 */
__STATIC_INLINE bool hw_clk_lp_is_xtal32k (void)
{
    if (REG_GETF(RTC, CLK_XTAL32K_REG, XTAL_CLK_SEL) == LP_CLK_IS_XTAL32K)
    {
        return true;
    }

    return false;
}

/**
 * \brief Set RCX as the Low Power clock.
 *
 * \warning The RCX must have been enabled before calling this function!
 *
 * \note Call with interrupts disabled to ensure that CLK_CTRL_REG
 *       read/modify/write operation is not interrupted
 */
__STATIC_INLINE void hw_clk_lp_set_rcx (void)
{
#if DEVICE_FPGA
#else
    BSP_CHECK_DEBUG(__get_PRIMASK() == 1 || __get_BASEPRI());
    BSP_CHECK_DEBUG(REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_LP_CLK));

    REG_SET_BIT(RTC, CLK_XTAL32K_REG, PDB_OSC_EN);
    REG_SETF(RTC, CLK_XTAL32K_REG, XTAL_CLK_SEL, LP_CLK_IS_RCX);
#endif
}

/**
 * \brief Set XTAL32K as the Low Power clock.
 *
 * \warning The XTAL32K must have been enabled before calling this function!
 *
 * \note Call with interrupts disabled to ensure that CLK_CTRL_REG
 *       read/modify/write operation is not interrupted
 */
__STATIC_INLINE void hw_clk_lp_set_xtal32k (void)
{
    BSP_CHECK_DEBUG(__get_PRIMASK() == 1 || __get_BASEPRI());
#if DEVICE_FPGA
#else
    BSP_CHECK_DEBUG(REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_LP_CLK));
#endif
    REG_SET_BIT(RTC, CLK_XTAL32K_REG, XTAL_BAT_EN);
    REG_SETF(RTC, CLK_XTAL32K_REG, XTAL_CLK_SEL, LP_CLK_IS_XTAL32K);
}

/**
 * \brief Set an external SWCLK as the Low Power clock.
 *
 * \note Call with interrupts disabled to ensure that CLK_CTRL_REG
 *       read/modify/write operation is not interrupted
 */
__STATIC_INLINE void hw_clk_lp_set_swclk (void)
{
    BSP_CHECK_DEBUG(__get_PRIMASK() == 1 || __get_BASEPRI());
#if DEVICE_FPGA
#else
    BSP_CHECK_DEBUG(REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_LP_CLK));
#endif
    REG_SETF(RTC, CLK_XTAL32K_REG, XTAL_CLK_SEL, LP_CLK_IS_SWCLK);
}

/**
 * \brief Enable RCX but does not set it as the LP clock.
 */
__STATIC_INLINE void hw_clk_enable_rcx (void)
{
    REG_SET_BIT(RTC, CLK_XTAL32K_REG, PDB_OSC_EN);
}

/**
 * \brief Disable RCX.
 *
 * \warning RCX must not be the LP clock
 */
__STATIC_INLINE void hw_clk_disable_rcx (void)
{
    if (REG_GETF(RTC, CLK_XTAL32K_REG, XTAL_CLK_SEL) != LP_CLK_IS_RCX)
    {
        REG_CLR_BIT(RTC, CLK_XTAL32K_REG, PDB_OSC_EN);
    }
}

/**
 * \brief Enable XTAL32K but do not set it as the LP clock.
 */
__STATIC_INLINE void hw_clk_enable_xtal32k (void)
{
    REG_SET_BIT(RTC, CLK_XTAL32K_REG, XTAL_BAT_EN);
}

/**
 * \brief Enable XTAL32K from XTAL40MHz but do not set it as the LP clock.
 */
__STATIC_INLINE void hw_clk_enable_external (void)
{
}

/**
 * \brief Disable XTAL32K.
 *
 * \warning XTAL32K must not be the LP clock.
 */
__STATIC_INLINE void hw_clk_disable_xtal32k (void)
{
    if (REG_GETF(RTC, CLK_XTAL32K_REG, XTAL_CLK_SEL) != LP_CLK_IS_XTAL32K)
    {
        REG_CLR_BIT(RTC, CLK_XTAL32K_REG, XTAL_BAT_EN);
    }
}

/**
 * \brief Disable XTAL32K from XTAL40M.
 *
 * \warning XTAL32K must not be the LP clock.
 */
__STATIC_INLINE void hw_clk_disable_external (void)
{
    BSP_CHECK_DEBUG(REG_GETF(RTC, CLK_XTAL32K_REG, XTAL_CLK_SEL) == LP_CLK_IS_XTAL32K);

    REG_CLR_BIT(RTC, CLK_XTAL32K_REG, XTAL_BAT_EN);
}

/**
 * \brief Set System clock.
 *
 * \param[in] mode The new system clock.
 *
 * \note System clock switch to PLL is only allowed when current system clock is XTAL40M.
 * System clock switch from PLL is only allowed when new system clock is XTAL40M.
 */
__STATIC_FORCEINLINE void hw_clk_set_sysclk (sys_clk_is_t mode)
{
    /* Make sure a valid sys clock is requested */
    BSP_CHECK_DEBUG(mode <= SYS_CLK_IS_PLL106M);
#if (0)

    /* Switch to PLL is only allowed when current system clock is XTAL32M */
    BSP_CHECK_DEBUG(mode != SYS_CLK_IS_PLL ||
                    REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_XTAL32M) ||
                    REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_PLL96M))

    /* Switch to PLL is only allowed when HDIV and PDIV are 0 */
    BSP_CHECK_DEBUG(mode != SYS_CLK_IS_PLL || (hw_clk_get_hclk_div() == ahb_div1 && hw_clk_get_pclk_div() == apb_div1));

    /* Switch from PLL is only allowed when new system clock is XTAL32M */
    BSP_CHECK_DEBUG(!REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_PLL96M) ||
                    mode == SYS_CLK_IS_XTAL40M ||
                    mode == SYS_CLK_IS_PLL);
#endif
    GLOBAL_INT_DISABLE();
    if (mode < SYS_CLK_IS_PLL240M)
    {
        // sys_clk_is_t clk = hw_clk_get_sysclk();
        if (mode == SYS_CLK_IS_XTAL40M)
        {
            REG_SET_BIT(CRG_COM, XTAL40M_CTRL_REG, XTAL40M_EN);
        }
        else if (mode == SYS_CLK_IS_LP)
        {
            REG_SET_BIT(CRG_COM, XTAL32K_CTRL_REG, XTAL32K_ENABLE);
            BSP_CHECK_DEBUG(0);
        }

        REG_SETF(CRG_TOP, CLK_CTRL_REG, SYS_CLK_SEL, mode);
    }
    else
    {
        sys_clk_is_t clk = hw_clk_get_sysclk();

        if ((clk != SYS_CLK_IS_XTAL40M) && (clk != SYS_CLK_IS_LP))
        {
            REG_SETF(CRG_TOP, CLK_CTRL_REG, SYS_CLK_SEL, SYS_CLK_IS_XTAL40M); // XTAL
            while (REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_PLL))
            {
            }
        }

        /* PLL_CLK_SEL,
         * 0: set to SYS_CLK=240Mhz
         * 1: set to SYS_CLK=192Mhz
         * 2: set to SYS_CLK=160Mhz
         * 3: set to SYS_CLK=137.14Mhz
         * 4: set to SYS_CLK=106Mhz
         */
        REG_SETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL, (unsigned) (mode - SYS_CLK_IS_PLL240M));

        REG_SETF(CRG_TOP, CLK_CTRL_REG, PLL_CPU_ENABLE, 1);

        REG_SETF(CRG_TOP, CLK_CTRL_REG, SYS_CLK_SEL, 3); // PLL
    }

    GLOBAL_INT_RESTORE();

    /* Wait until the switch is done! */
    switch (mode)
    {
        case SYS_CLK_IS_XTAL40M:
        {
            while (!REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_XTAL40M))
            {
            }

            return;
        }

        case SYS_CLK_IS_LP:
        {
            while (!REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_LP_CLK))
            {
            }

            return;
        }

        case SYS_CLK_IS_PLL160M:
        case SYS_CLK_IS_PLL137M:
        case SYS_CLK_IS_PLL106M:
        {
            while (!REG_GETF(CRG_TOP, CLK_CTRL_REG, RUNNING_AT_PLL))
            {
            }

            return;
        }

        default:
            BSP_CHECK_DEBUG(0);
    }
}

/**
 * \brief Enable the PLL.
 */
uint32_t hw_clk_pll_sys_on(void);

/**
 * \brief Disable the PLL.
 *
 * \warning The System clock must have been set to XTAL40M before calling this function!
 */
void hw_clk_pll_sys_off(void);

/**
 * \brief Check if the PLL is enabled.
 *
 * \return true if the PLL is enabled, else false.
 */
__STATIC_FORCEINLINE bool hw_clk_check_pll_status (void)
{
#if DEVICE_FPGA
    return REG_GETF(CRG_COM, PLL1_ARM_CTRL_REG, DPLL1_EN);
#else
    return REG_GETF(CRG_COM, PLL1_ARM_CTRL_REG, DPLL1_EN);
#endif
}

/**
 * \brief Check if the PLL is on and has locked.
 *
 * \return true if the PLL has locked, else false.
 */
__STATIC_FORCEINLINE bool hw_clk_is_pll_locked (void)
{
#if DEVICE_FPGA
    return REG_GETF(CRG_COM, PLL1_ARM_CTRL_REG, PLL_LOCK);
#else
    return REG_GETF(CRG_COM, PLL1_ARM_CTRL_REG, PLL_LOCK);
#endif
}

/**
 * \brief Activate a System clock.
 *
 * \param[in] clk The clock to activate.
 */
__STATIC_FORCEINLINE void hw_clk_enable_sysclk (sys_clk_is_t clk)
{
    switch (clk)
    {
        case SYS_CLK_IS_LP:
        {
            if (hw_clk_lp_is_xtal32k() == false)
            {
                hw_clk_enable_xtal32k();
            }

            break;
        }

        case SYS_CLK_IS_XTAL40M:
        {
            // REG_SETF(CRG_DIGPLL, PLL320M_CFG1_REG, ENABLE_PLL320M, 0);
            hw_clk_enable_xtal40m();

            // REG_SETF(CRG_TOP,CLK_CTRL_REG, DIVC_CLK_SEL, 0);  // 0: div1, 1: div2
            break;
        }

        case SYS_CLK_IS_PLL160M:
        {
            REG_SETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL, 2);
            break;
        }

        case SYS_CLK_IS_PLL137M:
        {
            // REG_SETF(CRG_DIGPLL, PLL320M_CFG1_REG, ENABLE_PLL320M, 1);
            // while(REG_GETF(CRG_DIGPLL, PLL320M_STATUS_REG,PLL320M_PLL_OK)==0);
            REG_SETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL, 3);
            break;
        }

        case SYS_CLK_IS_PLL106M:
        {
            // REG_SETF(CRG_DIGPLL, PLL320M_CFG1_REG, ENABLE_PLL320M, 1);
            // while(REG_GETF(CRG_DIGPLL, PLL320M_STATUS_REG,PLL320M_PLL_OK)==0);
            REG_SETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL, 4);
            break;
        }

        default:

            /* An invalid clock is requested */
            BSP_CHECK_DEBUG(0);
    }
}

/**
 * \brief Deactivate a System clock.
 *
 * \param[in] clk The clock to deactivate.
 */
__STATIC_FORCEINLINE void hw_clk_disable_sysclk (sys_clk_is_t clk)
{
    switch (clk)
    {
        case SYS_CLK_IS_XTAL40M:
        {
            hw_clk_disable_xtal40m();

            return;
        }

        case SYS_CLK_IS_LP:
        {
            hw_clk_disable_rcx();

            return;
        }

        case SYS_CLK_IS_PLL160M:
        {
            // TODO:
            return;
        }

        case SYS_CLK_IS_PLL137M:
        {
            // TODO:
            return;
        }

        case SYS_CLK_IS_PLL106M:
        {
            // TODO:
            return;
        }

        default:

            /* An invalid clock is requested */
            BSP_CHECK_DEBUG(0);
    }
}

/**
 * \brief Check if a System clock is enabled.
 *
 * \return true if the System clock is enabled, else false.
 */
__STATIC_INLINE bool hw_clk_is_enabled_sysclk (sys_clk_is_t clk)
{
    switch (clk)
    {
        case SYS_CLK_IS_XTAL40M:
        {
            return hw_clk_check_xtal40m_status();
        }

        case SYS_CLK_IS_PLL160M:
        {
            if (REG_GETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL) == 2)
            {
                return true;
            }

            break;
        }

        case SYS_CLK_IS_PLL137M:
        {
            if (REG_GETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL) == 3)
            {
                return true;
            }

            break;
        }

        case SYS_CLK_IS_PLL106M:
        {
            if (REG_GETF(CRG_TOP, CLK_CTRL_REG, PLL_CLK_SEL) == 4)
            {
                return true;
            }

            break;
        }

        default:
        {
            /* An invalid clock is requested */
            BSP_CHECK_DEBUG(0);
            break;
        }
    }

    return false;
}

/**
 * \brief Configure pin to connect an external digital clock.
 */
__STATIC_INLINE void hw_clk_configure_ext32k_pins (void)
{
#if DEVICE_FPGA
#else

    // GPIO-> P0_23_MODE_REG = 0;
#endif
}

/**
 * \brief Activate a FPLL clock.
 *
 * \param[in] freq_type The clock to activate.
 * \param[in] fpll_mode The clock to activate.
 */
__STATIC_INLINE void hw_clk_enable_fpll (fpll_clk_t freq_type, fpll_mode_t fpll_mode)
{
#if DEVICE_FPGA
#else
    REG_SETF(RTC, LDO_ENABLE_REG, LDO_EN_LDO_PLL1, 1);
    REG_SETF(CRG_COM, XTAL40M_CTRL_REG, XTAL40M_EN, 1);

// REG_SETF(CRG_COM, PLL1_ARM_CTRL_REG, DPLL1_EN, 1);
    REG_SETF(CRG_COM, XTAL40M_CTRL_REG, XTAL40M_FPLL_EN, 1);
    if (freq_type == DIVN_40M)
    {
        REG_SETF(FPLL, PLLD_CTRL_REG, FPLL_EN, 1);
        REG_SETF(FPLL, PLLD_CTRL_REG, BYPASS_SEL, 1);

        REG_SETF(FPLL, PLLD_CTRL_REG, PFD_CP_EN, 0);
        REG_SETF(FPLL, PLLD_CTRL_REG, CLKOUT_EN, 0);
        REG_SETF(FPLL, PLLD_CTRL_REG, VCO_EN, 0);
    }
    else if ((freq_type == FPLL_98M) || (freq_type == FPLL_90M))
    {
 #if 1

        // REG_SETF(FPLL, PLLD_CTRL_REG, FBDIV_SEL,fpll_mode);
        REG_SETF(FPLL, PLLD_IRQ_MASK_REG, MIRQ_PLL_LOCK, 1);
        REG_SETF(FPLL, PLLD_IRQ_MASK_REG, MIRQ_PLL_LOST_LOCK, 1);

        REG_SETF(FPLL, PLLD_CONFIG_REG, INDIV, 5);
        REG_SETF(FPLL, PLLD_CONFIG_REG, OUTDIV, 3);
        REG_SETF(FPLL, PLLD_CONFIG_REG, BIAS_HOLD, 0);
        if (fpll_mode == FPLL_MODE_NO_IRM)
        {
            if (freq_type == FPLL_98M)
            {
                // DIV = 98.304*2 / 5 (freq after input divider)=39.3216, INT = int(DIV) = 39 (0x27), FRAC = (DIV-INT)*2^13 = 2634 (0x0A4A)
                REG_SETF(FPLL, PLLD_FBDIV_REG, FBDIV, (0x27 << 13) | (0xA << 8) | (0x4A));
            }
            else if (freq_type == FPLL_90M)
            {
                // DIV = 36.12672, INT = 36 (0x24), FRAC = 1038 (0x040E)
                REG_SETF(FPLL, PLLD_FBDIV_REG, FBDIV, (0x24 << 13) | (0x4 << 8) | (0x0E));
            }
        }

        REG_SETF(FPLL, PLLD_CTRL_REG, BYPASS_SEL, 1);
        REG_SETF(FPLL, PLLD_CTRL_REG, VCO_EN, 1);
        REG_SETF(FPLL, PLLD_CTRL_REG, FPLL_EN, 1);
        REG_SETF(FPLL, PLLD_CTRL_REG, PFD_CP_EN, 1);
        REG_SETF(FPLL, PLLD_CTRL_REG, CLKOUT_EN, 1);

        // Wait 5us
// for(i=0; i<50; i++) {;}
// REG_SETF(FPLL, PLLD_CONFIG_REG, BIAS_HOLD, 1);

        // Wait for flag_lock to go HIGH
        while (REG_GETF(FPLL, PLLD_STATUS_REG, STA_PLL_LOCK) == 0)
        {
            ;
        }

        REG_SETF(FPLL, PLLD_CTRL_REG, CLKOUT_EN, 1);

// jason230810            REG_SETF(FPLL, PLLD_CTRL_REG, BYPASS_SEL, 0);
 #else

// LDO_ENABLE_REG.LDO_EN_LDO_PLL1  = 1 // DPLL & FPLL LDO EN
// XTAL40M_CTRL_REG.XTAL40M_EN = 1  // xtal 40M
// XTAL40M_CTRL_REG.XTAL40M_FPLL_EN  =1   // xtal 40M (FPLL path)
// GPIO_CLK_SEL_REG.FPLL98M_OUTPUT_EN  =1 // Pad dedicated setting
// PLLD_FBDIV_REG.FBDIV  = 0x4EA0E // 39.3142
// PLLD_CTRL_REG = 0x3E // FPLL EN
// PLLD_CONFIG_REG.OUTDIV = 1   // vco/2

        if (fpll_mode == FPLL_MODE_NO_IRM)
        {
            if (freq_type == FPLL_98M)
            {
                REG_SETF(FPLL, PLLD_FBDIV_REG, FBDIV, 0x4ea4a);
            }
            else if (freq_type == FPLL_90M)
            {
                REG_SETF(FPLL, PLLD_FBDIV_REG, FBDIV, 0x4840e);
            }
        }

        FPLL->PLLD_CTRL_REG = 0x3e;
        REG_SETF(FPLL, PLLD_CONFIG_REG, OUTDIV, 3);
        while (REG_GETF(FPLL, PLLD_STATUS_REG, STA_PLL_LOCK) == 0)
        {
            ;
        }
 #endif
    }
    return;
#endif
}

/**
 * \brief Deactivate a System clock.
 *
 * \param[in] clk The clock to deactivate.
 */
__STATIC_INLINE void hw_clk_disable_fpll (sys_clk_is_t clk)
{
    switch (clk)
    {
        case SYS_CLK_IS_XTAL40M:
        {
            hw_clk_disable_xtal40m();

            return;
        }

        default:

            /* An invalid clock is requested */
            BSP_CHECK_DEBUG(0);
    }
}

/**
 * \brief Configure XTAL40M.
 */
void hw_clk_xtalm_configure(void);

/**
 * \brief Perform XTAL40M RCOSC amplitude temperature compensation.
 */
void hw_clk_xtalm_compensate_amp(void);

/**
 * \brief Update XTAL40M Ready IRQ counter.
 *
 * \return The difference between the new and the old XTAL40M Ready IRQ counter
 *         in cycles of 32KHz clocks.
 */
int16_t hw_clk_xtalm_update_rdy_cnt(void);

/**
 * \brief Enable PLL
 *
 * \details
 */
void pll_on(void);

/**
 * \brief Disable PLL
 *
 * \details
 */
void pll_off(void);

/**
 * \brief Set Low Power clock.
 *
 * \param[in] mode The new low power clock.
 */
__STATIC_INLINE void hw_clk_set_lpclk (lp_clk_is_t mode)
{
    GLOBAL_INT_DISABLE();
    switch (mode)
    {
        case LP_CLK_IS_RCX:
        {
            hw_clk_lp_set_rcx();
            break;
        }

        case LP_CLK_IS_SWCLK:
        {
            hw_clk_lp_set_swclk();
            break;
        }

        case LP_CLK_IS_XTAL32K:
        {
            hw_clk_lp_set_xtal32k();
            break;
        }

        default:
        {
            BSP_CHECK_DEBUG(0);
            break;
        }
    }

    GLOBAL_INT_RESTORE();
}

/**
 * \brief Activate a Low Power clock.
 *
 * \param[in] clk The clock to activate.
 */
__STATIC_INLINE void hw_clk_enable_lpclk (lp_clk_is_t clk)
{
    switch (clk)
    {
        case LP_CLK_IS_RCX:
        {
            hw_clk_enable_rcx();

            return;
        }

        case LP_CLK_IS_XTAL32K:
        {
            hw_clk_enable_xtal32k();

            return;
        }

        case LP_CLK_IS_SWCLK:
        {
            // Nothing to do for SWCLK LP clock
            return;
        }

        default:

            /* An invalid clock is requested */
            BSP_CHECK_DEBUG(0);
    }
}

/**
 * \brief Deactivate a Low Power clock.
 *
 * \param[in] clk The clock to deactivate.
 */
__STATIC_INLINE void hw_clk_disable_lpclk (lp_clk_is_t clk)
{
    switch (clk)
    {
        case LP_CLK_IS_RCX:
        {
            hw_clk_disable_rcx();

            return;
        }

        case LP_CLK_IS_XTAL32K:
        {
            hw_clk_disable_xtal32k();

            return;
        }

        case LP_CLK_IS_SWCLK:
        {
            // Nothing to do for SWCLK LP clock
            return;
        }

        default:

            /* An invalid clock is requested */
            BSP_CHECK_DEBUG(0);
    }
}

/**
 * \brief Enable clock for specific UART channel
 *
 * \param[in] channel UART channel to activate clock
 */
__STATIC_INLINE void hw_clk_enable_uart_w_clk (uint8_t channel)
{
    CRG_TOP->CLK_AMBA_REG_b.PERI_CLK_ENABLE = 1;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    switch (channel)
    {
        case 0:
        {
            CRG_PER->CLK_COM_REG_b.UART_ENABLE = 1;
            break;
        }

        case 1:
        {
            CRG_PER->CLK_COM_REG_b.UART2_ENABLE = 1;
            break;
        }

        case 2:
        {
            CRG_PER->CLK_COM_REG_b.UART3_ENABLE = 1;
            break;
        }
    }

    FSP_CRITICAL_SECTION_EXIT;
}

/**
 * \brief Disable clock for specific UART channel
 *
 * \param[in] channel UART channel to deactivate clock
 */
__STATIC_INLINE void hw_clk_disable_uart_w_clk (uint8_t channel)
{
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    switch (channel)
    {
        case 0:
        {
            CRG_PER->CLK_COM_REG_b.UART_ENABLE = 0;
            break;
        }

        case 1:
        {
            CRG_PER->CLK_COM_REG_b.UART2_ENABLE = 0;
            break;
        }

        case 2:
        {
            CRG_PER->CLK_COM_REG_b.UART3_ENABLE = 0;
            break;
        }
    }

    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 * @brief Enable the low-power crystal oscillator.
 *
 * This function enables the low-power 32kHz crystal oscillator by setting the XTAL_BAT_EN bit in the RTC register.
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_prv_lpclk_xtal_on ()
{
    RTC->CLK_XTAL32K_REG_b.XTAL_BAT_EN = 1;
}

/*******************************************************************************************************************//**
 * @brief Enable the low-power oscillator.
 *
 * This function enables the low-power internal RC oscillator by setting the PDB_OSC_EN bit in the RTC register.
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_prv_lpclk_osc_on ()
{
    RTC->CLK_XTAL32K_REG_b.PDB_OSC_EN = 1;
}

lp_clk_is_t bsp_prv_lpclk_get();
fsp_err_t   bsp_prv_lpclk_select(lp_clk_is_t type);
void        bsp_prv_rtc_mirror_init(void);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
