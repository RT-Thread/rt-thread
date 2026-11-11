/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#if BSP_FEATURE_BSP_USE_TCS
 #include "bsp_tcs.h"
 #include "bsp_otp.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include "bsp_rand.h"
#ifdef RM_STDIO_W
#include "rm_stdio_w_cfg.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define TRNG_SYS_RETRY_LIMIT (1000)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef void (* bsp_init_func_ptr)(void);

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
extern void R_BSP_WarmStart(bsp_warm_start_event_t event);

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
void        bsp_wdt_freeze_cfg(void);
static void ra6w1_SystemInitPostC(void);

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Handle WDT Freeze.
 *
 * WDT is enabled after reset by default.
 * In case r_wdog_w module is not included in the project, WDT should be disabled by BSP.
 * bsp_wdt_freeze_cfg weak function - will disable WDT in case r_wdog_w module is not included.
 * bsp_wdt_freeze_cfg normal function - will do nothing, hence WDT remains enabled, in case r_wdog_w is included.
 **********************************************************************************************************************/
BSP_WEAK_REFERENCE void bsp_wdt_freeze_cfg (void)
{
    CRG_TOP->SET_FREEZE_REG_b.FRZ_SYS_WDOG = 1;
}

static void ra6w1_SystemInitPostC (void)
{
    /*
     * TIN-TODO: This is a weak function that freezes the watchdog. It is redefined in
     * r_wdog_w, where it does nothing. I suppose that it is helpful as it allows for test
     * runners that do not need to explicitly freeze the watchdog, but from an SDK point of view
     * the watchdog is the applications responsibility. The startup code should only refresh it where
     * necessary.
     *//* If WDT watchdog is not used - freeze it */
    uint32_t s = 0U;

    for (int tries = 0; tries < TRNG_SYS_RETRY_LIMIT; tries++)
    {
        s = trng_rand() & (uint32_t) HW_ACC_PRNG_SEED_REG_PRNG_SEED_VAL_Msk;

        if (s != 0U)
        {
            break;
        }
    }

    bsp_wdt_freeze_cfg();

    /* Initialize SystemCoreClock variable. */
    SystemCoreClockUpdate();

#if BSP_FEATURE_BSP_USE_TCS

    /* enable OTP to read TCS values */
    bsp_otp_init();
    bsp_otp_mode_set(BSP_OTP_MODE_READ);

    /* get TCS values */
    bsp_tcs_get_trim_values_from_cs();

    /* Close OTP */
    bsp_otp_close();
#endif

#if defined(CONFIG_RETARGET) || defined(CONFIG_RTT)
    /* This is needed to initialize stdout, so that it can be used by putchar (that doesn't initialize stdout,
     * contrary to printf). Putchar is needed by the Unity test framework
     * This also has the side effect of changing stdout to unbuffered (which seems more reasonable)
     */
    setvbuf(stdout, NULL, _IONBF, 0);
#endif

    /* TIN_HACK_WIFI: This was here in fsp-rrq and was removed in fsp-da but did not go anywhere else?
     * TODO: the following clock configuration must be removed, see TVR-398
     */
    REG_SETF(CRG_TOP, CLK_AMBA_REG, PERI_CLK_ENABLE, 1);
    REG_SETF(CRG_TOP, CLK_AMBA_REG, TIMER_CLK_ENABLE, 1);

    /* Initialize SystemWakeupSource variable. */
    SystemWakeupSourceUpdate();

#if !BSP_CFG_OSPI_8_LINES_SUPPORT

    /* Use pins PIN1_00-PIN1_03 as GPIO instead of OQSPI lines. */
    CRG_TOP->CLK_AMBA_REG_b.OQSPI_GPIO_MODE = 1;
#endif

    // TIN-TODO: This does not seem secure at all, since the initial seed is a constant.

     /* Initiate the seed with TRNG */
    if (s == 0U)
    {
        s = 1U;
    }

    srand(s);

    /* Call Post C runtime initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_POST_C);
}

/*
 * Add pointer to ra6w1_SystemInitPostC() in an array that will go in the .init_array section.
 * __libc_init_array() (which is called by _start()) calls all function pointers in .init_array.
 */
BSP_PLACE_IN_SECTION(BSP_SECTION_INIT) BSP_ALIGN_VARIABLE(__alignof__(bsp_init_func_ptr))
static bsp_init_func_ptr ra6w1_init_array_entry[] =
{
    ra6w1_SystemInitPostC,
};

/** @} (end addtogroup BSP_MCU_PRV) */
