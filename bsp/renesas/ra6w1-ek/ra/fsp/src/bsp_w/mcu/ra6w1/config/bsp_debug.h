/**
 * \addtogroup PLA_BSP_CONFIG
 * \{
 * \addtogroup BSP_DEBUG Debug Configuration
 * \brief Board debug support configuration definitions
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file bsp_debug.h
 *
 * @brief Board Support Package. Debug Configuration.
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef BSP_DEBUG_H_
#define BSP_DEBUG_H_

/**
 * \addtogroup DEBUG_SETTINGS
 *
 * \brief Debugging settings
 *
 * \{
 */

/* -------------------------------------- Debug settings ---------------------------------------- */

/**
 * \brief Enable debugger
 */
#ifndef dg_configENABLE_DEBUGGER
 #define dg_configENABLE_DEBUGGER    (1)
#endif

/**
 * \brief Use SW cursor
 */
#ifndef dg_configUSE_SW_CURSOR
 #define dg_configUSE_SW_CURSOR      (0)
 #define SW_CURSOR_PORT              (0)
 #define SW_CURSOR_PIN               (0)
#else
 #if (DEVICE_FAMILY == DA1468X)
  #if dg_configBLACK_ORCA_MB_REV == BLACK_ORCA_MB_REV_D
   #if !defined SW_CURSOR_PORT && !defined SW_CURSOR_PIN
    #define SW_CURSOR_PORT           (0)
    #define SW_CURSOR_PIN            (7)
   #endif
  #else
   #if !defined SW_CURSOR_PORT && !defined SW_CURSOR_PIN
    #define SW_CURSOR_PORT           (2)
    #define SW_CURSOR_PIN            (3)
   #endif
  #endif
 #elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
  #if !defined SW_CURSOR_PORT && !defined SW_CURSOR_PIN
   #define SW_CURSOR_PORT            (0)
   #define SW_CURSOR_PIN             (16)
  #endif
 #endif
#endif

/* ---------------------------------------------------------------------------------------------- */

/**
 * \}
 */

/**
 * \addtogroup DEBUG_SETTINGS
 * \{
 * \addtogroup SYSTEM_VIEW
 *
 * \brief System View configuration settings
 * \{
 */

/* ----------------------------- Segger System View configuration ------------------------------- */

/**
 * \brief Segger's System View
 *
 * When enabled the application should also call SEGGER_SYSVIEW_Conf() to enable system monitoring.
 * configTOTAL_HEAP_SIZE should be increased by dg_configSYSTEMVIEW_STACK_OVERHEAD bytes for each system task.
 * For example, if there are 8 system tasks configTOTAL_HEAP_SIZE should be increased by
 * (8 * dg_configSYSTEMVIEW_STACK_OVERHEAD) bytes.
 *
 * - 0 : Disabled
 * - 1 : Enabled
 *
 */
#ifndef dg_configSYSTEMVIEW
 #define dg_configSYSTEMVIEW                   (0)
#endif

/**
 * \brief Stack size overhead when System View API is used
 *
 * All thread stack sizes plus the the stack of IRQ handlers will be increased by that amount
 * to avoid stack overflow when System View is monitoring the system.
 */
#ifndef dg_configSYSTEMVIEW_STACK_OVERHEAD
 #define dg_configSYSTEMVIEW_STACK_OVERHEAD    (256)
#endif

/*
 * Enable/Disable System View monitoring time critical interrupt handlers (CPM, USB).
 * Disabling ISR monitoring could help reducing assertions triggered by System View monitoring overhead.
 *
 */

/**
 * \brief Let System View monitor CPM related ISRs (SWTIM1_Handler / WKUP_GPIO_Handler).
 *
 * - 0 : Disabled
 * - 1 : Enabled
 */
#ifndef dg_configSYSTEMVIEW_MONITOR_CPM_ISR
 #define dg_configSYSTEMVIEW_MONITOR_CPM_ISR    (1)
#endif

/**
 * \brief Let System View monitor USB related ISRs (USB_Handler / VBUS_Handler).
 *
 * - 0 : Disabled
 * - 1 : Enabled
 */
#ifndef dg_configSYSTEMVIEW_MONITOR_USB_ISR
 #define dg_configSYSTEMVIEW_MONITOR_USB_ISR    (1)
#endif

/* ---------------------------------------------------------------------------------------------- */

/**
 * \}
 * \}
 */

/* --------------------------------- DEBUG GPIO handling macros --------------------------------- */
#if (DEVICE_FAMILY == DA1468X)
 #define DBG_CONFIGURE(flag, name, func)      \
    {                                         \
        if (flag == 1) {                      \
            name ## _MODE_REG = 0x300 + func; \
        }                                     \
    }

 #define DBG_CONFIGURE_HIGH(flag, name)       \
    {                                         \
        if (flag == 1) {                      \
            name ## _SET_REG  = name ## _PIN; \
            name ## _MODE_REG = 0x300;        \
        }                                     \
    }

 #define DBG_CONFIGURE_LOW(flag, name)         \
    {                                          \
        if (flag == 1) {                       \
            name ## _RESET_REG = name ## _PIN; \
            name ## _MODE_REG  = 0x300;        \
        }                                      \
    }

 #define DBG_SET_HIGH(flag, name)            \
    {                                        \
        if (flag == 1) {                     \
            name ## _SET_REG = name ## _PIN; \
        }                                    \
    }

 #define DBG_SET_LOW(flag, name)               \
    {                                          \
        if (flag == 1) {                       \
            name ## _RESET_REG = name ## _PIN; \
        }                                      \
    }
#elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

 #define DBG_GET_SET_PAD_LATCH_REG(name)      *(((volatile uint32_t *) (&name ## _SET_REG) ==                 \
                                                 (volatile uint32_t *) (&GPIO->P0_SET_DATA_REG)) ? &CRG_TOP-> \
                                                P0_SET_PAD_LATCH_REG : &CRG_TOP->P1_SET_PAD_LATCH_REG)
 #define DBG_GET_RESET_PAD_LATCH_REG(name)    *(((volatile uint32_t *) (&name ## _SET_REG) ==                 \
                                                 (volatile uint32_t *) (&GPIO->P0_SET_DATA_REG)) ? &CRG_TOP-> \
                                                P0_RESET_PAD_LATCH_REG : &CRG_TOP->                           \
                                                P1_RESET_PAD_LATCH_REG)
 #define DBG_TOGGLE_PIN_PAD_LATCH(name)       DBG_GET_SET_PAD_LATCH_REG(name) = name ## _PIN; \
    DBG_GET_RESET_PAD_LATCH_REG(name) = name ## _PIN
 #define DBG_SET_PIN_REG(name)                name ## _SET_REG   = name ## _PIN
 #define DBG_RESET_PIN_REG(name)              name ## _RESET_REG = name ## _PIN

 #define DBG_CONFIGURE(flag, name, func)                                     \
    {                                                                        \
        if (flag == 1) {                                                     \
            ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, COM_IS_UP) == 1); \
            name ## _MODE_REG = 0x300 + func;                                \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                  \
        }                                                                    \
    }

 #define DBG_CONFIGURE_HIGH(flag, name)                                      \
    {                                                                        \
        if (flag == 1) {                                                     \
            ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1); \
            name ## _MODE_REG = 0x300;                                       \
            DBG_SET_PIN_REG(name);                                           \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                  \
        }                                                                    \
    }

 #define DBG_CONFIGURE_LOW(flag, name)                                       \
    {                                                                        \
        if (flag == 1) {                                                     \
            ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1); \
            name ## _MODE_REG = 0x300;                                       \
            DBG_RESET_PIN_REG(name);                                         \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                  \
        }                                                                    \
    }

 #define DBG_SET_HIGH(flag, name)                                            \
    {                                                                        \
        if (flag == 1) {                                                     \
            ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1); \
            name ## _MODE_REG = 0x300;                                       \
            DBG_SET_PIN_REG(name);                                           \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                  \
        }                                                                    \
    }

 #define DBG_SET_LOW(flag, name)                                             \
    {                                                                        \
        if (flag == 1) {                                                     \
            ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1); \
            name ## _MODE_REG = 0x300;                                       \
            DBG_RESET_PIN_REG(name);                                         \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                  \
        }                                                                    \
    }

#elif (DEVICE_FAMILY == DA1640X)

 #define DBG_GET_SET_PAD_LATCH_REG(name)   // *(((volatile uint32_t *)(&name##_SET_REG) == (volatile uint32_t *)(&GPIO->P0_SET_DATA_REG)) ? &CRG_TOP->P0_SET_PAD_LATCH_REG : &CRG_TOP->P1_SET_PAD_LATCH_REG)
 #define DBG_GET_RESET_PAD_LATCH_REG(name) // *(((volatile uint32_t *)(&name##_SET_REG) == (volatile uint32_t *)(&GPIO->P0_SET_DATA_REG)) ? &CRG_TOP->P0_RESET_PAD_LATCH_REG : &CRG_TOP->P1_RESET_PAD_LATCH_REG)
 #define DBG_TOGGLE_PIN_PAD_LATCH(name)    /* DBG_GET_SET_PAD_LATCH_REG(name) = name##_PIN; */ \
                                           /* DBG_GET_RESET_PAD_LATCH_REG(name) = name##_PIN */
 #define DBG_SET_PIN_REG(name)             // name##_SET_REG = name##_PIN
 #define DBG_RESET_PIN_REG(name)           // name##_RESET_REG = name##_PIN

 #define DBG_CONFIGURE(flag, name, func)                                         \
    {                                                                            \
        if (flag == 1) {                                                         \
            /*ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, COM_IS_UP) == 1);*/ \
            name ## _MODE_REG = 0x300 + func;                                    \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                      \
        }                                                                        \
    }

 #define DBG_CONFIGURE_HIGH(flag, name)                                          \
    {                                                                            \
        if (flag == 1) {                                                         \
            /*ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1);*/ \
            name ## _MODE_REG = 0x300;                                           \
            DBG_SET_PIN_REG(name);                                               \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                      \
        }                                                                        \
    }

 #define DBG_CONFIGURE_LOW(flag, name)                                           \
    {                                                                            \
        if (flag == 1) {                                                         \
            /*ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1);*/ \
            name ## _MODE_REG = 0x300;                                           \
            DBG_RESET_PIN_REG(name);                                             \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                      \
        }                                                                        \
    }

 #define DBG_SET_HIGH(flag, name)                                                \
    {                                                                            \
        if (flag == 1) {                                                         \
            /*ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1);*/ \
            name ## _MODE_REG = 0x300;                                           \
            DBG_SET_PIN_REG(name);                                               \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                      \
        }                                                                        \
    }

 #define DBG_SET_LOW(flag, name)                                                 \
    {                                                                            \
        if (flag == 1) {                                                         \
            /*ASSERT_WARNING(REG_GETF(CRG_TOP, SYS_STAT_REG, AUD_IS_UP) == 1);*/ \
            name ## _MODE_REG = 0x300;                                           \
            DBG_RESET_PIN_REG(name);                                             \
            DBG_TOGGLE_PIN_PAD_LATCH(name);                                      \
        }                                                                        \
    }

#endif

/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------- HardFault or NMI event ------------------------------------ */

#ifndef EXCEPTION_DEBUG
 #define EXCEPTION_DEBUG    (0)        // Requires GPIO config.
#endif

/* ---------------------------------------------------------------------------------------------- */

/* --------------------------------- Clock and Power Manager ------------------------------------ */

#if (DEVICE_FAMILY == DA1468X)

 #ifndef CPM_DEBUG
  #define CPM_DEBUG                   (0)
 #endif

 #ifndef CPM_USE_FUNCTIONAL_DEBUG
  #define CPM_USE_FUNCTIONAL_DEBUG    (0) // Requires GPIO config.
 #endif

 #ifndef CPM_USE_TIMING_DEBUG
  #define CPM_USE_TIMING_DEBUG        (0) // Requires GPIO config.
 #endif

 #ifndef CPM_USE_RCX_DEBUG
  #define CPM_USE_RCX_DEBUG           (0) // Requires logging.
 #endif

#elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X) || (DEVICE_FAMILY == DA1640X))

 #ifndef PWR_MGR_DEBUG
  #define PWR_MGR_DEBUG               (0)
 #endif

 #ifndef SYS_TIM_DEBUG
  #define SYS_TIM_DEBUG               (0)
 #endif

 #ifndef PWR_MGR_FUNCTIONAL_DEBUG
  #define PWR_MGR_FUNCTIONAL_DEBUG    (0) // Requires GPIO config.
 #endif

 #ifndef PWR_MGR_USE_TIMING_DEBUG
  #define PWR_MGR_USE_TIMING_DEBUG    (0) // Requires GPIO config.
 #endif

 #ifndef CLK_MGR_USE_TIMING_DEBUG
  #define CLK_MGR_USE_TIMING_DEBUG    (0) // Requires GPIO config.
 #endif

#endif

/* Controls which RAM blocks will be retained when the MEASURE_SLEEP_CURRENT test mode is used
 * (optional). */
#ifndef dg_configTESTMODE_RETAIN_RAM
 #define dg_configTESTMODE_RETAIN_RAM      (0x1F)
#endif

/* Controls whether the Cache will be retained when the MEASURE_SLEEP_CURRENT test mode is used
 * (optional). */
#ifndef dg_configTESTMODE_RETAIN_CACHE
 #define dg_configTESTMODE_RETAIN_CACHE    (0)
#endif

/* Controls whether the ECC RAM will be retained when the MEASURE_SLEEP_CURRENT test mode is used
 * (optional). */
#ifdef dg_config_TESTMODE_RETAIN_ECCRAM
 #error "dg_config_TESTMODE_RETAIN_ECCRAM is no longer supported. "
"Use dg_configTESTMODE_RETAIN_ECCRAM instead (no underscore)!"
#endif

#ifndef dg_configTESTMODE_RETAIN_ECCRAM
 #define dg_configTESTMODE_RETAIN_ECCRAM    (0)
#endif

/* ---------------------------------------------------------------------------------------------- */

/* --------------------------------------- USB Charger ------------------------------------------ */

#if (DEVICE_FAMILY == DA1468X)

 #ifndef DEBUG_USB_CHARGER
  #define DEBUG_USB_CHARGER           (0)
 #endif

 #ifndef DEBUG_USB_CHARGER_FSM
  #define DEBUG_USB_CHARGER_FSM       (0)
 #endif

 #ifndef DEBUG_USB_CHARGER_PRINT
  #define DEBUG_USB_CHARGER_PRINT     (0)
 #endif

 #ifndef USB_CHARGER_TIMING_DEBUG
  #define USB_CHARGER_TIMING_DEBUG    (0) // Requires GPIO config.
 #endif

#elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

 #ifndef SYS_CHARGER_TIMING_DEBUG
  #define SYS_CHARGER_TIMING_DEBUG    (0)
 #endif

#endif                                 /* DEVICE_FAMILY */

/* ---------------------------------------------------------------------------------------------- */

/* ------------------------------------------ Flash --------------------------------------------- */
#ifndef FLASH_DEBUG
 #define FLASH_DEBUG           (0)     // Requires GPIO config.
#endif

#ifndef __DBG_QSPI_ENABLED
 #define __DBG_QSPI_ENABLED    (0)
#endif

/* ---------------------------------------------------------------------------------------------- */

/* ------------------------------------------ Common -------------------------------------------- */
#ifndef CMN_TIMING_DEBUG
 #define CMN_TIMING_DEBUG    (0)       // Requires GPIO config.
#endif

/* ---------------------------------------------------------------------------------------------- */

/* ------------------------------------ GPIO configuration -------------------------------------- */

/* Enable/Disable GPIO pin assignment conflict detection
 */
#define DEBUG_GPIO_ALLOC_MONITOR_ENABLED    (0)

/* Exception handling debug configuration
 *
 */
#if (EXCEPTION_DEBUG == 0)

// Dummy values to suppress compiler errors
 #define EXCEPTIONDBG_MODE_REG     *(volatile int *) 0x20000000
 #define EXCEPTIONDBG_SET_REG      *(volatile int *) 0x20000000
 #define EXCEPTIONDBG_RESET_REG    *(volatile int *) 0x20000000
 #define EXCEPTIONDBG_PIN          (0)

#else

 #if (DEVICE_FAMILY == DA1468X)

// Tick (P3[0])
  #define EXCEPTIONDBG_MODE_REG     GPIO->P30_MODE_REG
  #define EXCEPTIONDBG_SET_REG      GPIO->P3_SET_DATA_REG
  #define EXCEPTIONDBG_RESET_REG    GPIO->P3_RESET_DATA_REG
  #define EXCEPTIONDBG_PIN          (1 << 0)

 #elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

// Tick
  #define EXCEPTIONDBG_MODE_REG     GPIO->P0_30_MODE_REG
  #define EXCEPTIONDBG_SET_REG      GPIO->P0_SET_DATA_REG
  #define EXCEPTIONDBG_RESET_REG    GPIO->P0_RESET_DATA_REG
  #define EXCEPTIONDBG_PIN          (1 << 30)

 #endif                                /* DEVICE_FAMILY */

#endif                                 /* EXCEPTION_DEBUG */

/* Functional debug configuration
 *
 * Note that GPIO overlapping is allowed if the tracked events are discrete and the initial GPIO
 * configuration is the same! No checking is performed for erroneous configuration though!
 *
 */
#if (DEVICE_FAMILY == DA1468X)

 #if (CPM_USE_FUNCTIONAL_DEBUG == 0)

// Tick (initial configuration: low)
  #define CPMDBG_TICK_MODE_REG         *(volatile int *) 0x20000000
  #define CPMDBG_TICK_SET_REG          *(volatile int *) 0x20000000
  #define CPMDBG_TICK_RESET_REG        *(volatile int *) 0x20000000
  #define CPMDBG_TICK_PIN              (0)

// External Wake-up (initial configuration: low)
  #define CPMDBG_EXT_WKUP_MODE_REG     *(volatile int *) 0x20000000
  #define CPMDBG_EXT_WKUP_SET_REG      *(volatile int *) 0x20000000
  #define CPMDBG_EXT_WKUP_RESET_REG    *(volatile int *) 0x20000000
  #define CPMDBG_EXT_WKUP_PIN          (0)

// Active / Sleep (initial configuration: high)
  #define CPMDBG_POWERUP_MODE_REG      *(volatile int *) 0x20000000
  #define CPMDBG_POWERUP_SET_REG       *(volatile int *) 0x20000000
  #define CPMDBG_POWERUP_RESET_REG     *(volatile int *) 0x20000000
  #define CPMDBG_POWERUP_PIN           (0)

 #else

// Tick (P2[3])
  #define CPMDBG_TICK_MODE_REG         GPIO->P23_MODE_REG
  #define CPMDBG_TICK_SET_REG          GPIO->P2_SET_DATA_REG
  #define CPMDBG_TICK_RESET_REG        GPIO->P2_RESET_DATA_REG
  #define CPMDBG_TICK_PIN              (1 << 3)

// External Wake-up (P3[0])
  #define CPMDBG_EXT_WKUP_MODE_REG     GPIO->P30_MODE_REG
  #define CPMDBG_EXT_WKUP_SET_REG      GPIO->P3_SET_DATA_REG
  #define CPMDBG_EXT_WKUP_RESET_REG    GPIO->P3_RESET_DATA_REG
  #define CPMDBG_EXT_WKUP_PIN          (1 << 0)

// Active / Sleep (P1[4])
  #define CPMDBG_POWERUP_MODE_REG      GPIO->P14_MODE_REG
  #define CPMDBG_POWERUP_SET_REG       GPIO->P1_SET_DATA_REG
  #define CPMDBG_POWERUP_RESET_REG     GPIO->P1_RESET_DATA_REG
  #define CPMDBG_POWERUP_PIN           (1 << 4)
 #endif

#elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

 #if (PWR_MGR_FUNCTIONAL_DEBUG == 0)

// Dummy values to suppress compiler errors
  #define PWRDBG_TICK_MODE_REG        *(volatile int *) 0x20000000
  #define PWRDBG_TICK_SET_REG         *(volatile int *) 0x20000000
  #define PWRDBG_TICK_RESET_REG       *(volatile int *) 0x20000000
  #define PWRDBG_TICK_PIN             (0)

  #define PWRDBG_POWERUP_MODE_REG     *(volatile int *) 0x20000000
  #define PWRDBG_POWERUP_SET_REG      *(volatile int *) 0x20000000
  #define PWRDBG_POWERUP_RESET_REG    *(volatile int *) 0x20000000
  #define PWRDBG_POWERUP_PIN          (0)

 #else

// Tick
  #define PWRDBG_TICK_MODE_REG        GPIO->P0_19_MODE_REG
  #define PWRDBG_TICK_SET_REG         GPIO->P0_SET_DATA_REG
  #define PWRDBG_TICK_RESET_REG       GPIO->P0_RESET_DATA_REG
  #define PWRDBG_TICK_PIN             (1 << 19)

// Active / Sleep
  #define PWRDBG_POWERUP_MODE_REG     GPIO->P0_21_MODE_REG
  #define PWRDBG_POWERUP_SET_REG      GPIO->P0_SET_DATA_REG
  #define PWRDBG_POWERUP_RESET_REG    GPIO->P0_RESET_DATA_REG
  #define PWRDBG_POWERUP_PIN          (1 << 21)

 #endif                                /* PWR_MGR_FUNCTIONAL_DEBUG */

#endif                                 /* DEVICE_FAMILY */

/* Timing debug configuration
 *
 * Note that in this mode the pad latches are removed immediately after the execution resumes from
 * the __WFI(). Because of this, it is not advised to use this feature in projects that use GPIOS.
 * Nevertheless, in case it is used, make sure that the "peripheral initialization" is also done
 * at that point, modifying sys_power_mgr.c accordingly.
 *
 * Note also that GPIO overlapping is allowed if the tracked events are discrete and the initial
 * GPIO configuration is the same! No checking is performed for erroneous configuration though!
 *
 */
#if (DEVICE_FAMILY == DA1468X)

 #if (CPM_USE_TIMING_DEBUG == 0)

// CPM: sleep or idle entry (until __WFI() is called) (initial configuration: high)
  #define CPMDBG_SLEEP_ENTER_MODE_REG         *(volatile int *) 0x20000000
  #define CPMDBG_SLEEP_ENTER_SET_REG          *(volatile int *) 0x20000000
  #define CPMDBG_SLEEP_ENTER_RESET_REG        *(volatile int *) 0x20000000
  #define CPMDBG_SLEEP_ENTER_PIN              (0)

// CPM: sleep or idle exit (initial configuration: low)
  #define CPMDBG_SLEEP_EXIT_MODE_REG          *(volatile int *) 0x20000000
  #define CPMDBG_SLEEP_EXIT_SET_REG           *(volatile int *) 0x20000000
  #define CPMDBG_SLEEP_EXIT_RESET_REG         *(volatile int *) 0x20000000
  #define CPMDBG_SLEEP_EXIT_PIN               (0)

// Low clocks (initial configuration: low)
  #define CPMDBG_LOWER_CLOCKS_MODE_REG        *(volatile int *) 0x20000000
  #define CPMDBG_LOWER_CLOCKS_SET_REG         *(volatile int *) 0x20000000
  #define CPMDBG_LOWER_CLOCKS_RESET_REG       *(volatile int *) 0x20000000
  #define CPMDBG_LOWER_CLOCKS_PIN             (0)

// XTAL16M settling (initial configuration: low)
  #define CPMDBG_XTAL16M_SETTLED_MODE_REG     *(volatile int *) 0x20000000
  #define CPMDBG_XTAL16M_SETTLED_SET_REG      *(volatile int *) 0x20000000
  #define CPMDBG_XTAL16M_SETTLED_RESET_REG    *(volatile int *) 0x20000000
  #define CPMDBG_XTAL16M_SETTLED_PIN          (0)

 #else

// CPM: sleep or idle entry (until __WFI() is called) (P1[7])
  #define CPMDBG_SLEEP_ENTER_MODE_REG         GPIO->P17_MODE_REG
  #define CPMDBG_SLEEP_ENTER_SET_REG          GPIO->P1_SET_DATA_REG
  #define CPMDBG_SLEEP_ENTER_RESET_REG        GPIO->P1_RESET_DATA_REG
  #define CPMDBG_SLEEP_ENTER_PIN              (1 << 7)

// CPM: sleep or idle exit (P1[6])
  #define CPMDBG_SLEEP_EXIT_MODE_REG          GPIO->P16_MODE_REG
  #define CPMDBG_SLEEP_EXIT_SET_REG           GPIO->P1_SET_DATA_REG
  #define CPMDBG_SLEEP_EXIT_RESET_REG         GPIO->P1_RESET_DATA_REG
  #define CPMDBG_SLEEP_EXIT_PIN               (1 << 6)

// Low clocks (P1[5])
  #define CPMDBG_LOWER_CLOCKS_MODE_REG        GPIO->P15_MODE_REG
  #define CPMDBG_LOWER_CLOCKS_SET_REG         GPIO->P1_SET_DATA_REG
  #define CPMDBG_LOWER_CLOCKS_RESET_REG       GPIO->P1_RESET_DATA_REG
  #define CPMDBG_LOWER_CLOCKS_PIN             (1 << 5)

// XTAL16M settling (P1[4])
  #define CPMDBG_XTAL16M_SETTLED_MODE_REG     GPIO->P14_MODE_REG
  #define CPMDBG_XTAL16M_SETTLED_SET_REG      GPIO->P1_SET_DATA_REG
  #define CPMDBG_XTAL16M_SETTLED_RESET_REG    GPIO->P1_RESET_DATA_REG
  #define CPMDBG_XTAL16M_SETTLED_PIN          (1 << 4)

 #endif                                /* CPM_USE_TIMING_DEBUG */

#elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X) || (DEVICE_FAMILY == DA1640X))

 #if (PWR_MGR_USE_TIMING_DEBUG == 0)

// Dummy values to suppress compiler errors
  #define PWRDBG_SLEEP_ENTER_MODE_REG     *(volatile int *) 0x20000000
  #define PWRDBG_SLEEP_ENTER_SET_REG      *(volatile int *) 0x20000000
  #define PWRDBG_SLEEP_ENTER_RESET_REG    *(volatile int *) 0x20000000
  #define PWRDBG_SLEEP_ENTER_PIN          (0)

  #define PWRDBG_SLEEP_EXIT_MODE_REG      *(volatile int *) 0x20000000
  #define PWRDBG_SLEEP_EXIT_SET_REG       *(volatile int *) 0x20000000
  #define PWRDBG_SLEEP_EXIT_RESET_REG     *(volatile int *) 0x20000000
  #define PWRDBG_SLEEP_EXIT_PIN           (0)

 #else

// Power manager: sleep or idle entry (until __WFI() is called)
  #define PWRDBG_SLEEP_ENTER_MODE_REG     GPIO->P0_17_MODE_REG
  #define PWRDBG_SLEEP_ENTER_SET_REG      GPIO->P0_SET_DATA_REG
  #define PWRDBG_SLEEP_ENTER_RESET_REG    GPIO->P0_RESET_DATA_REG
  #define PWRDBG_SLEEP_ENTER_PIN          (1 << 17)

// Power manager: sleep or idle exit
  #define PWRDBG_SLEEP_EXIT_MODE_REG      GPIO->P0_18_MODE_REG
  #define PWRDBG_SLEEP_EXIT_SET_REG       GPIO->P0_SET_DATA_REG
  #define PWRDBG_SLEEP_EXIT_RESET_REG     GPIO->P0_RESET_DATA_REG
  #define PWRDBG_SLEEP_EXIT_PIN           (1 << 18)

 #endif                                /* CLK_MGR_USE_TIMING_DEBUG */

 #if (CLK_MGR_USE_TIMING_DEBUG == 0)

// Dummy values to suppress compiler errors
  #define CLKDBG_LOWER_CLOCKS_MODE_REG        *(volatile int *) 0x20000000
  #define CLKDBG_LOWER_CLOCKS_SET_REG         *(volatile int *) 0x20000000
  #define CLKDBG_LOWER_CLOCKS_RESET_REG       *(volatile int *) 0x20000000
  #define CLKDBG_LOWER_CLOCKS_PIN             (0)

  #define CLKDBG_XTAL32M_SETTLED_MODE_REG     *(volatile int *) 0x20000000
  #define CLKDBG_XTAL32M_SETTLED_SET_REG      *(volatile int *) 0x20000000
  #define CLKDBG_XTAL32M_SETTLED_RESET_REG    *(volatile int *) 0x20000000
  #define CLKDBG_XTAL32M_SETTLED_PIN          (0)

  #define CLKDBG_XTAL32M_READY_MODE_REG       *(volatile int *) 0x20000000
  #define CLKDBG_XTAL32M_READY_SET_REG        *(volatile int *) 0x20000000
  #define CLKDBG_XTAL32M_READY_RESET_REG      *(volatile int *) 0x20000000
  #define CLKDBG_XTAL32M_READY_PIN            (0)

  #define CLKDBG_PLL_ON_MODE_REG              *(volatile int *) 0x20000000
  #define CLKDBG_PLL_ON_SET_REG               *(volatile int *) 0x20000000
  #define CLKDBG_PLL_ON_RESET_REG             *(volatile int *) 0x20000000
  #define CLKDBG_PLL_ON_PIN                   (0)

 #else

// Low clocks
  #define CLKDBG_LOWER_CLOCKS_MODE_REG        GPIO->P0_26_MODE_REG
  #define CLKDBG_LOWER_CLOCKS_SET_REG         GPIO->P0_SET_DATA_REG
  #define CLKDBG_LOWER_CLOCKS_RESET_REG       GPIO->P0_RESET_DATA_REG
  #define CLKDBG_LOWER_CLOCKS_PIN             (1 << 26)

// XTAL32M settling
  #define CLKDBG_XTAL32M_SETTLED_MODE_REG     GPIO->P0_27_MODE_REG
  #define CLKDBG_XTAL32M_SETTLED_SET_REG      GPIO->P0_SET_DATA_REG
  #define CLKDBG_XTAL32M_SETTLED_RESET_REG    GPIO->P0_RESET_DATA_REG
  #define CLKDBG_XTAL32M_SETTLED_PIN          (1 << 27)

// XTAL32M Ready IRQ
  #define CLKDBG_XTAL32M_READY_MODE_REG       GPIO->P0_28_MODE_REG
  #define CLKDBG_XTAL32M_READY_SET_REG        GPIO->P0_SET_DATA_REG
  #define CLKDBG_XTAL32M_READY_RESET_REG      GPIO->P0_RESET_DATA_REG
  #define CLKDBG_XTAL32M_READY_PIN            (1 << 28)

// PLL is on
  #define CLKDBG_PLL_ON_MODE_REG              GPIO->P0_29_MODE_REG
  #define CLKDBG_PLL_ON_SET_REG               GPIO->P0_SET_DATA_REG
  #define CLKDBG_PLL_ON_RESET_REG             GPIO->P0_RESET_DATA_REG
  #define CLKDBG_PLL_ON_PIN                   (1 << 29)

 #endif                                /* CLK_MGR_USE_TIMING_DEBUG */

#endif                                 /* DEVICE_FAMILY */

#if (DEVICE_FAMILY == DA1468X)

 #if (USB_CHARGER_TIMING_DEBUG == 0)

// CHRG: Inside critical section (initial configuration: low)
  #define CHRGDBG_CRITICAL_SECTION_MODE_REG     *(volatile int *) 0x20000000
  #define CHRGDBG_CRITICAL_SECTION_SET_REG      *(volatile int *) 0x20000000
  #define CHRGDBG_CRITICAL_SECTION_RESET_REG    *(volatile int *) 0x20000000
  #define CHRGDBG_CRITICAL_SECTION_PIN          (0)

// CHRG: FSM task (initial configuration: low)
  #define CHRGDBG_FSM_TASK_MODE_REG             *(volatile int *) 0x20000000
  #define CHRGDBG_FSM_TASK_SET_REG              *(volatile int *) 0x20000000
  #define CHRGDBG_FSM_TASK_RESET_REG            *(volatile int *) 0x20000000
  #define CHRGDBG_FSM_TASK_PIN                  (0)

// CHRG: Control task (initial configuration: low)
  #define CPMDBG_CONTROL_TASK_MODE_REG          *(volatile int *) 0x20000000
  #define CPMDBG_CONTROL_TASK_SET_REG           *(volatile int *) 0x20000000
  #define CPMDBG_CONTROL_TASK_RESET_REG         *(volatile int *) 0x20000000
  #define CPMDBG_CONTROL_TASK_PIN               (0)

 #else

// CHRG: Inside critical section (P3[2])
  #define CHRGDBG_CRITICAL_SECTION_MODE_REG     GPIO->P32_MODE_REG
  #define CHRGDBG_CRITICAL_SECTION_SET_REG      GPIO->P3_SET_DATA_REG
  #define CHRGDBG_CRITICAL_SECTION_RESET_REG    GPIO->P3_RESET_DATA_REG
  #define CHRGDBG_CRITICAL_SECTION_PIN          (1 << 2)

// CHRG: FSM task (P3[3])
  #define CHRGDBG_FSM_TASK_MODE_REG             GPIO->P33_MODE_REG
  #define CHRGDBG_FSM_TASK_SET_REG              GPIO->P3_SET_DATA_REG
  #define CHRGDBG_FSM_TASK_RESET_REG            GPIO->P3_RESET_DATA_REG
  #define CHRGDBG_FSM_TASK_PIN                  (1 << 3)

// CHRG: Control task (P3[4])
  #define CPMDBG_CONTROL_TASK_MODE_REG          GPIO->P34_MODE_REG
  #define CPMDBG_CONTROL_TASK_SET_REG           GPIO->P3_SET_DATA_REG
  #define CPMDBG_CONTROL_TASK_RESET_REG         GPIO->P3_RESET_DATA_REG
  #define CPMDBG_CONTROL_TASK_PIN               (1 << 4)

 #endif                                /* USB_CHARGER_TIMING_DEBUG */

#elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
 #if (SYS_CHARGER_TIMING_DEBUG == 0)

  #define SYS_CHARGER_DBG_VBUS_MODE_REG          *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_VBUS_SET_REG           *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_VBUS_RESET_REG         *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_VBUS_PIN               (0)

  #define SYS_CHARGER_DBG_CH_EVT_MODE_REG        *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_CH_EVT_SET_REG         *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_CH_EVT_RESET_REG       *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_CH_EVT_PIN             (0)

  #define SYS_CHARGER_DBG_PRE_CH_MODE_REG        *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_PRE_CH_SET_REG         *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_PRE_CH_RESET_REG       *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_PRE_CH_PIN             (0)

  #define SYS_CHARGER_DBG_CH_MODE_REG            *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_CH_SET_REG             *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_CH_RESET_REG           *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_CH_PIN                 (0)

  #define SYS_CHARGER_DBG_EOC_MODE_REG           *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_EOC_SET_REG            *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_EOC_RESET_REG          *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_EOC_PIN                (0)

  #define SYS_CHARGER_DBG_ENUM_DONE_MODE_REG     *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_ENUM_DONE_SET_REG      *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_ENUM_DONE_RESET_REG    *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_ENUM_DONE_PIN          (0)

  #define SYS_CHARGER_DBG_SUS_MODE_REG           *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_SUS_SET_REG            *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_SUS_RESET_REG          *(volatile int *) 0x20000000
  #define SYS_CHARGER_DBG_SUS_PIN                (0)

 #else

  #define SYS_CHARGER_DBG_VBUS_MODE_REG          GPIO->P1_10_MODE_REG
  #define SYS_CHARGER_DBG_VBUS_SET_REG           GPIO->P1_SET_DATA_REG
  #define SYS_CHARGER_DBG_VBUS_RESET_REG         GPIO->P1_RESET_DATA_REG
  #define SYS_CHARGER_DBG_VBUS_PIN               (1 << 10)

  #define SYS_CHARGER_DBG_CH_EVT_MODE_REG        GPIO->P1_11_MODE_REG
  #define SYS_CHARGER_DBG_CH_EVT_SET_REG         GPIO->P1_SET_DATA_REG
  #define SYS_CHARGER_DBG_CH_EVT_RESET_REG       GPIO->P1_RESET_DATA_REG
  #define SYS_CHARGER_DBG_CH_EVT_PIN             (1 << 11)

  #define SYS_CHARGER_DBG_PRE_CH_MODE_REG        GPIO->P1_12_MODE_REG
  #define SYS_CHARGER_DBG_PRE_CH_SET_REG         GPIO->P1_SET_DATA_REG
  #define SYS_CHARGER_DBG_PRE_CH_RESET_REG       GPIO->P1_RESET_DATA_REG
  #define SYS_CHARGER_DBG_PRE_CH_PIN             (1 << 12)

  #define SYS_CHARGER_DBG_CH_MODE_REG            GPIO->P1_13_MODE_REG
  #define SYS_CHARGER_DBG_CH_SET_REG             GPIO->P1_SET_DATA_REG
  #define SYS_CHARGER_DBG_CH_RESET_REG           GPIO->P1_RESET_DATA_REG
  #define SYS_CHARGER_DBG_CH_PIN                 (1 << 13)

  #define SYS_CHARGER_DBG_EOC_MODE_REG           GPIO->P1_14_MODE_REG
  #define SYS_CHARGER_DBG_EOC_SET_REG            GPIO->P1_SET_DATA_REG
  #define SYS_CHARGER_DBG_EOC_RESET_REG          GPIO->P1_RESET_DATA_REG
  #define SYS_CHARGER_DBG_EOC_PIN                (1 << 14)

  #define SYS_CHARGER_DBG_ENUM_DONE_MODE_REG     GPIO->P1_15_MODE_REG
  #define SYS_CHARGER_DBG_ENUM_DONE_SET_REG      GPIO->P1_SET_DATA_REG
  #define SYS_CHARGER_DBG_ENUM_DONE_RESET_REG    GPIO->P1_RESET_DATA_REG
  #define SYS_CHARGER_DBG_ENUM_DONE_PIN          (1 << 15)

  #define SYS_CHARGER_DBG_SUS_MODE_REG           GPIO->P1_16_MODE_REG
  #define SYS_CHARGER_DBG_SUS_SET_REG            GPIO->P1_SET_DATA_REG
  #define SYS_CHARGER_DBG_SUS_RESET_REG          GPIO->P1_RESET_DATA_REG
  #define SYS_CHARGER_DBG_SUS_PIN                (1 << 16)

 #endif                                /* SYS_CHARGER_TIMING_DEBUG */
#endif                                 /* DEVICE_FAMILY */

#if (CMN_TIMING_DEBUG == 0)

// Common: Inside critical section (initial configuration: low)
 #define CMNDBG_CRITICAL_SECTION_MODE_REG     *(volatile int *) 0x20000000
 #define CMNDBG_CRITICAL_SECTION_SET_REG      *(volatile int *) 0x20000000
 #define CMNDBG_CRITICAL_SECTION_RESET_REG    *(volatile int *) 0x20000000
 #define CMNDBG_CRITICAL_SECTION_PIN          (0)

#else

 #if (DEVICE_FAMILY == DA1468X)

// Common: Inside critical section (P4[0])
  #define CMNDBG_CRITICAL_SECTION_MODE_REG     GPIO->P40_MODE_REG
  #define CMNDBG_CRITICAL_SECTION_SET_REG      GPIO->P4_SET_DATA_REG
  #define CMNDBG_CRITICAL_SECTION_RESET_REG    GPIO->P4_RESET_DATA_REG
  #define CMNDBG_CRITICAL_SECTION_PIN          (1 << 0)

 #elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

// Common: Inside critical section
  #define CMNDBG_CRITICAL_SECTION_MODE_REG     GPIO->P0_24_MODE_REG
  #define CMNDBG_CRITICAL_SECTION_SET_REG      GPIO->P0_SET_DATA_REG
  #define CMNDBG_CRITICAL_SECTION_RESET_REG    GPIO->P0_RESET_DATA_REG
  #define CMNDBG_CRITICAL_SECTION_PIN          (1 << 24)

 #endif                                /* DEVICE_FAMILY */

#endif                                 /* CMN_TIMING_DEBUG */

/* Flash debug configuration
 *
 */
#if (FLASH_DEBUG == 0)

// Write page (initial configuration: low)
 #define FLASHDBG_PAGE_PROG_MODE_REG            *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_SET_REG             *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_RESET_REG           *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_PIN                 (0)

// Program page wait loop (initial configuration: low)
 #define FLASHDBG_PAGE_PROG_WL_MODE_REG         *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_WL_SET_REG          *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_WL_RESET_REG        *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_WL_PIN              (0)

// Program page wait loop - pending irq check (initial configuration: low)
 #define FLASHDBG_PAGE_PROG_WL_IRQ_MODE_REG     *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_WL_IRQ_SET_REG      *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_WL_IRQ_RESET_REG    *(volatile int *) 0x20000000
 #define FLASHDBG_PAGE_PROG_WL_IRQ_PIN          (0)

// Suspend op (initial configuration: low)
 #define FLASHDBG_SUSPEND_MODE_REG              *(volatile int *) 0x20000000
 #define FLASHDBG_SUSPEND_SET_REG               *(volatile int *) 0x20000000
 #define FLASHDBG_SUSPEND_RESET_REG             *(volatile int *) 0x20000000
 #define FLASHDBG_SUSPEND_PIN                   (0)

// Erase sector cmd (initial configuration: low)
 #define FLASHDBG_SECTOR_ERASE_MODE_REG         *(volatile int *) 0x20000000
 #define FLASHDBG_SECTOR_ERASE_SET_REG          *(volatile int *) 0x20000000
 #define FLASHDBG_SECTOR_ERASE_RESET_REG        *(volatile int *) 0x20000000
 #define FLASHDBG_SECTOR_ERASE_PIN              (0)

// Notify task (initial configuration: low)
 #define FLASHDBG_TASK_NOTIFY_MODE_REG          *(volatile int *) 0x20000000
 #define FLASHDBG_TASK_NOTIFY_SET_REG           *(volatile int *) 0x20000000
 #define FLASHDBG_TASK_NOTIFY_RESET_REG         *(volatile int *) 0x20000000
 #define FLASHDBG_TASK_NOTIFY_PIN               (0)

// Suspend action (low level) (initial configuration: low)
 #define FLASHDBG_SUSPEND_ACTION_MODE_REG       *(volatile int *) 0x20000000
 #define FLASHDBG_SUSPEND_ACTION_SET_REG        *(volatile int *) 0x20000000
 #define FLASHDBG_SUSPEND_ACTION_RESET_REG      *(volatile int *) 0x20000000
 #define FLASHDBG_SUSPEND_ACTION_PIN            (0)

// Resume op (initial configuration: low)
 #define FLASHDBG_RESUME_MODE_REG               *(volatile int *) 0x20000000
 #define FLASHDBG_RESUME_SET_REG                *(volatile int *) 0x20000000
 #define FLASHDBG_RESUME_RESET_REG              *(volatile int *) 0x20000000
 #define FLASHDBG_RESUME_PIN                    (0)

#else

 #if (DEVICE_FAMILY == DA1468X)

// Write page (initial configuration: low)
  #define FLASHDBG_PAGE_PROG_MODE_REG            GPIO->P30_MODE_REG
  #define FLASHDBG_PAGE_PROG_SET_REG             GPIO->P3_SET_DATA_REG
  #define FLASHDBG_PAGE_PROG_RESET_REG           GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_PAGE_PROG_PIN                 (1 << 0)

// Program page wait loop (initial configuration: low)
  #define FLASHDBG_PAGE_PROG_WL_MODE_REG         GPIO->P31_MODE_REG
  #define FLASHDBG_PAGE_PROG_WL_SET_REG          GPIO->P3_SET_DATA_REG
  #define FLASHDBG_PAGE_PROG_WL_RESET_REG        GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_PAGE_PROG_WL_PIN              (1 << 1)

// Program page wait loop - pending irq check (initial configuration: low)
  #define FLASHDBG_PAGE_PROG_WL_IRQ_MODE_REG     GPIO->P32_MODE_REG
  #define FLASHDBG_PAGE_PROG_WL_IRQ_SET_REG      GPIO->P3_SET_DATA_REG
  #define FLASHDBG_PAGE_PROG_WL_IRQ_RESET_REG    GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_PAGE_PROG_WL_IRQ_PIN          (1 << 2)

// Suspend op (initial configuration: low)
  #define FLASHDBG_SUSPEND_MODE_REG              GPIO->P33_MODE_REG
  #define FLASHDBG_SUSPEND_SET_REG               GPIO->P3_SET_DATA_REG
  #define FLASHDBG_SUSPEND_RESET_REG             GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_SUSPEND_PIN                   (1 << 3)

// Erase sector cmd (initial configuration: low)
  #define FLASHDBG_SECTOR_ERASE_MODE_REG         GPIO->P34_MODE_REG
  #define FLASHDBG_SECTOR_ERASE_SET_REG          GPIO->P3_SET_DATA_REG
  #define FLASHDBG_SECTOR_ERASE_RESET_REG        GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_SECTOR_ERASE_PIN              (1 << 4)

// Notify task (initial configuration: low)
  #define FLASHDBG_TASK_NOTIFY_MODE_REG          GPIO->P35_MODE_REG
  #define FLASHDBG_TASK_NOTIFY_SET_REG           GPIO->P3_SET_DATA_REG
  #define FLASHDBG_TASK_NOTIFY_RESET_REG         GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_TASK_NOTIFY_PIN               (1 << 5)

// Suspend action (low level) (initial configuration: low)
  #define FLASHDBG_SUSPEND_ACTION_MODE_REG       GPIO->P36_MODE_REG
  #define FLASHDBG_SUSPEND_ACTION_SET_REG        GPIO->P3_SET_DATA_REG
  #define FLASHDBG_SUSPEND_ACTION_RESET_REG      GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_SUSPEND_ACTION_PIN            (1 << 6)

// Resume op (initial configuration: low)
  #define FLASHDBG_RESUME_MODE_REG               GPIO->P37_MODE_REG
  #define FLASHDBG_RESUME_SET_REG                GPIO->P3_SET_DATA_REG
  #define FLASHDBG_RESUME_RESET_REG              GPIO->P3_RESET_DATA_REG
  #define FLASHDBG_RESUME_PIN                    (1 << 7)

 #elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

  #if DEVICE_FPGA

   #if (PWR_MGR_FUNCTIONAL_DEBUG == 1) || (PWR_MGR_USE_TIMING_DEBUG == 1) || (CLK_MGR_USE_TIMING_DEBUG == 1)
    #error "Flash debug pins are also used by clock manager and power manager"
   #endif

// Write page (initial configuration: low)
   #define FLASHDBG_PAGE_PROG_MODE_REG            GPIO->P0_18_MODE_REG
   #define FLASHDBG_PAGE_PROG_SET_REG             GPIO->P0_SET_DATA_REG
   #define FLASHDBG_PAGE_PROG_RESET_REG           GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_PAGE_PROG_PIN                 (1 << 18)

// Program page wait loop (initial configuration: low)
   #define FLASHDBG_PAGE_PROG_WL_MODE_REG         GPIO->P0_19_MODE_REG
   #define FLASHDBG_PAGE_PROG_WL_SET_REG          GPIO->P0_SET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_RESET_REG        GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_PIN              (1 << 19)

// Program page wait loop - pending irq check (initial configuration: low)
   #define FLASHDBG_PAGE_PROG_WL_IRQ_MODE_REG     GPIO->P0_20_MODE_REG
   #define FLASHDBG_PAGE_PROG_WL_IRQ_SET_REG      GPIO->P0_SET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_IRQ_RESET_REG    GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_IRQ_PIN          (1 << 20)

// Suspend op (initial configuration: low)
   #define FLASHDBG_SUSPEND_MODE_REG              GPIO->P0_21_MODE_REG
   #define FLASHDBG_SUSPEND_SET_REG               GPIO->P0_SET_DATA_REG
   #define FLASHDBG_SUSPEND_RESET_REG             GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_SUSPEND_PIN                   (1 << 21)

// Erase sector cmd (initial configuration: low)
   #define FLASHDBG_SECTOR_ERASE_MODE_REG         GPIO->P0_26_MODE_REG
   #define FLASHDBG_SECTOR_ERASE_SET_REG          GPIO->P0_SET_DATA_REG
   #define FLASHDBG_SECTOR_ERASE_RESET_REG        GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_SECTOR_ERASE_PIN              (1 << 26)

// Notify task (initial configuration: low)
   #define FLASHDBG_TASK_NOTIFY_MODE_REG          GPIO->P0_27_MODE_REG
   #define FLASHDBG_TASK_NOTIFY_SET_REG           GPIO->P0_SET_DATA_REG
   #define FLASHDBG_TASK_NOTIFY_RESET_REG         GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_TASK_NOTIFY_PIN               (1 << 27)

// Suspend action (low level) (initial configuration: low)
   #define FLASHDBG_SUSPEND_ACTION_MODE_REG       GPIO->P0_28_MODE_REG
   #define FLASHDBG_SUSPEND_ACTION_SET_REG        GPIO->P0_SET_DATA_REG
   #define FLASHDBG_SUSPEND_ACTION_RESET_REG      GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_SUSPEND_ACTION_PIN            (1 << 28)

// Resume op (initial configuration: low)
   #define FLASHDBG_RESUME_MODE_REG               GPIO->P0_29_MODE_REG
   #define FLASHDBG_RESUME_SET_REG                GPIO->P0_SET_DATA_REG
   #define FLASHDBG_RESUME_RESET_REG              GPIO->P0_RESET_DATA_REG
   #define FLASHDBG_RESUME_PIN                    (1 << 29)

  #else

// Write page (initial configuration: low)
   #define FLASHDBG_PAGE_PROG_MODE_REG            GPIO->P1_01_MODE_REG
   #define FLASHDBG_PAGE_PROG_SET_REG             GPIO->P1_SET_DATA_REG
   #define FLASHDBG_PAGE_PROG_RESET_REG           GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_PAGE_PROG_PIN                 (1 << 1)

// Program page wait loop (initial configuration: low)
   #define FLASHDBG_PAGE_PROG_WL_MODE_REG         GPIO->P1_02_MODE_REG
   #define FLASHDBG_PAGE_PROG_WL_SET_REG          GPIO->P1_SET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_RESET_REG        GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_PIN              (1 << 2)

// Program page wait loop - pending irq check (initial configuration: low)
   #define FLASHDBG_PAGE_PROG_WL_IRQ_MODE_REG     GPIO->P1_03_MODE_REG
   #define FLASHDBG_PAGE_PROG_WL_IRQ_SET_REG      GPIO->P1_SET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_IRQ_RESET_REG    GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_PAGE_PROG_WL_IRQ_PIN          (1 << 3)

// Suspend op (initial configuration: low)
   #define FLASHDBG_SUSPEND_MODE_REG              GPIO->P1_04_MODE_REG
   #define FLASHDBG_SUSPEND_SET_REG               GPIO->P1_SET_DATA_REG
   #define FLASHDBG_SUSPEND_RESET_REG             GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_SUSPEND_PIN                   (1 << 4)

// Erase sector cmd (initial configuration: low)
   #define FLASHDBG_SECTOR_ERASE_MODE_REG         GPIO->P1_05_MODE_REG
   #define FLASHDBG_SECTOR_ERASE_SET_REG          GPIO->P1_SET_DATA_REG
   #define FLASHDBG_SECTOR_ERASE_RESET_REG        GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_SECTOR_ERASE_PIN              (1 << 5)

// Notify task (initial configuration: low)
   #define FLASHDBG_TASK_NOTIFY_MODE_REG          GPIO->P1_06_MODE_REG
   #define FLASHDBG_TASK_NOTIFY_SET_REG           GPIO->P1_SET_DATA_REG
   #define FLASHDBG_TASK_NOTIFY_RESET_REG         GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_TASK_NOTIFY_PIN               (1 << 6)

// Suspend action (low level) (initial configuration: low)
   #define FLASHDBG_SUSPEND_ACTION_MODE_REG       GPIO->P1_07_MODE_REG
   #define FLASHDBG_SUSPEND_ACTION_SET_REG        GPIO->P1_SET_DATA_REG
   #define FLASHDBG_SUSPEND_ACTION_RESET_REG      GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_SUSPEND_ACTION_PIN            (1 << 7)

// Resume op (initial configuration: low)
   #define FLASHDBG_RESUME_MODE_REG               GPIO->P1_08_MODE_REG
   #define FLASHDBG_RESUME_SET_REG                GPIO->P1_SET_DATA_REG
   #define FLASHDBG_RESUME_RESET_REG              GPIO->P1_RESET_DATA_REG
   #define FLASHDBG_RESUME_PIN                    (1 << 8)

  #endif                               /* DEVICE_FPGA */

 #endif                                /* DEVICE_FAMILY */

#endif                                 /* FLASH_DEBUG */

#endif /* BSP_DEBUG_H_ */

/**
 \}
 \}
 */
