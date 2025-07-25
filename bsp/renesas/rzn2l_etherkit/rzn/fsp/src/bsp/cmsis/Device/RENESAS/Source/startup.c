/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
extern void bsp_master_mpu_init(void);
extern void bsp_global_system_counter_init(void);

#if BSP_FEATURE_TFU_SUPPORTED
extern void bsp_tfu_init(void);

#endif

#if BSP_CFG_C_RUNTIME_INIT
extern void bsp_loader_data_init(void);
extern void bsp_loader_bss_init(void);
extern void bsp_static_constructor_init(void);

#endif

#if !(BSP_CFG_RAM_EXECUTION)
extern void bsp_copy_to_ram(void);
extern void bsp_application_bss_init(void);

#endif

#if !BSP_CFG_PORT_PROTECT
extern void bsp_release_port_protect(void);

#endif

extern void bsp_memory_protect_setting(void);
extern void bsp_irq_cfg_common(void);

extern void R_BSP_WarmStart(bsp_warm_start_event_t event);

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
int32_t main(void);

#if BSP_CFG_EARLY_INIT
static void bsp_init_uninitialized_vars(void);

#endif

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the MCU and the runtime environment.
 **********************************************************************************************************************/
void SystemInit (void)
{
#if BSP_CFG_EARLY_INIT

    /* Initialize uninitialized BSP variables early for use in R_BSP_WarmStart. */
    bsp_init_uninitialized_vars();
#endif

    /* Call before initializing clock and variables. */
    R_BSP_WarmStart(BSP_WARM_START_RESET);

    /* Configure system clocks. */
    bsp_clock_init();

    /* Call post clock initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_POST_CLOCK);

#if BSP_CFG_C_RUNTIME_INIT

    /* Copy the loader data from external Flash to internal RAM. */
    bsp_loader_data_init();

    /* Clear loader bss section in internal RAM. */
    bsp_loader_bss_init();
#endif

    /* Initialize SystemCoreClock variable. */
    SystemCoreClockUpdate();

    /* Set memory attributes, etc. */
    bsp_memory_protect_setting();

#if !(BSP_CFG_RAM_EXECUTION)

    /* Copy the application program from external Flash to internal RAM. */
    bsp_copy_to_ram();

    /* Clear bss section in internal RAM. */
    bsp_application_bss_init();
#endif

#if BSP_CFG_C_RUNTIME_INIT

    /* Initialize static constructors */
    bsp_static_constructor_init();
#endif

#if !BSP_CFG_PORT_PROTECT

    /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
     * disable writes. */
    bsp_release_port_protect();
#endif

    /* Call Post C runtime initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_POST_C);

    /* Initialize the Master-MPU settings. */
    bsp_master_mpu_init();

    /* Initialize global system counter. The counter is enabled and is incrementing. */
    bsp_global_system_counter_init();

    /* GIC initialization */
    bsp_irq_cfg_common();

    /* Initialize GIC interrupts. */
    bsp_irq_cfg();

#if BSP_FEATURE_TFU_SUPPORTED

    /* Initialize the TFU settings. */
    bsp_tfu_init();
#endif

#if defined(__GNUC__)
    extern void entry(void);
    entry();
#elif defined(__ICCARM__)
    extern void __low_level_init(void);
    __low_level_init();
#else
    /* Jump to main. */
    main();
#endif
}

/** @} (end addtogroup BSP_MCU) */

#if BSP_CFG_EARLY_INIT

/*******************************************************************************************************************//**
 * Initialize BSP variables not handled by C runtime startup.
 **********************************************************************************************************************/
static void bsp_init_uninitialized_vars (void)
{
    g_protect_port_counter = 0;

    extern volatile uint16_t g_protect_counters[];
    for (uint32_t i = 0; i < 4; i++)
    {
        g_protect_counters[i] = 0;
    }

    SystemCoreClockUpdate();
}

#endif
