/***************************************************************************//**
* \file cy_syspm.c
* \version 4.0
*
* This driver provides the source code for API power management.
*
********************************************************************************
* \copyright
* Copyright 2016-2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cy_syspm.h"
#include "cy_ipc_drv.h"
#include "cy_ipc_sema.h"
#include "cy_ipc_pipe.h"
#include "cy_prot.h"


/*******************************************************************************
*       Internal Functions
*******************************************************************************/
static void EnterDeepSleepRam(cy_en_syspm_waitfor_t waitFor);

static void SetReadMarginTrimUlp(void);
static void SetReadMarginTrimLp(void);
static void SetWriteAssistTrimUlp(void);
static void SetWriteAssistTrimLp(void);
static bool IsVoltageChangePossible(void);


/*******************************************************************************
*       Internal Defines
*******************************************************************************/
#ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE

    /** The internal define for clock divider */
    #define SYSPM_CLK_DIVIDER         (9U)

    /* Mask for the fast clock divider value */
    #define SYSPM_FAST_CLK_DIV_Msk    (0xFF000000UL)

    /* Position for the fast clock divider value */
    #define SYSPM_FAST_CLK_DIV_Pos    (24UL)

    /* Mask for the slow clock divider value */
    #define SYSPM_SLOW_CLK_DIV_Msk    (0x00FF0000UL)

    /* Position for the slow clock divider value */
    #define SYSPM_SLOW_CLK_DIV_Pos    (16UL)

    /* Mask for both slow and fast mask clock dividers */
    #define SYSPM_CLK_DIV_MASK        (SYSPM_FAST_CLK_DIV_Msk | SYSPM_SLOW_CLK_DIV_Msk)

    #if (CY_CPU_CORTEX_M4)
        #define CUR_CORE_DP_MASK      (0x01UL)
        #define OTHER_CORE_DP_MASK    (0x02UL)
    #else
        #define CUR_CORE_DP_MASK      (0x02UL)
        #define OTHER_CORE_DP_MASK    (0x01UL)
    #endif

#endif /* #ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE */

/* The define for the current active bus master */
#if (CY_CPU_CORTEX_M0P)
    #define ACTIVE_BUS_MASTER           CPUSS_MS_ID_CM0
#else
    #define ACTIVE_BUS_MASTER           CPUSS_MS_ID_CM4
#endif /* (CY_CPU_CORTEX_M0P) */

/* Define of MMIO group where UDB is located */
#define MMIO_UDB_GROUP_NR              (4U)

/* Define of MMIO group where UDB is located */
#define MMIO_UDB_SLAVE_NR              (3U)

/* The UDB placement on MMIO slave level */
#define PERI_UDB_SLAVE_ENABLED         ((uint32_t) 1UL << MMIO_UDB_GROUP_NR)

/* The definition for the delay of the LDO after its output 
* voltage is changed
*/
#define LDO_STABILIZATION_DELAY_US     (9U)

/* Define to indicate that a 10 us delay is needed */
#define NEED_DELAY                     (0x0U)

/* Slow output register */
#define CLK_OUTPUT_SLOW_MASK           (0x06U)

/* Slow control register */
#define TST_DDFT_FAST_CTL_MASK         (62U)

/* Load value for the timer to count delay after exiting Deep Sleep */
#define IMO_10US_DELAY                 (68U)

/* Define to indicate that a 10 us delay was done after exiting Deep Sleep */
#define DELAY_DONE                     (0xAAAAAAAAU)

/* Define for transitional 0.95 V for the LDO regulator */
#define LDO_OUT_VOLTAGE_0_95V          (0x0BU)

/* Define for transitional 1.1 V for the LDO regulator */
#define LDO_OUT_VOLTAGE_1_1V           (0x17U)

/* Define for transitional 1.15 V for the LDO regulator */
#define LDO_OUT_VOLTAGE_1_15V          (0x1BU)

/* The definition for the delay of the Buck supply regulator 
* stabilization after it is configured with enabled Buck output 1 */
#define BUCK_INIT_STABILIZATION_US     (900U)

/* The definition for the delay of the Buck supply regulator 
* stabilization after it is configured with enabled Buck 
* output 2 only
*/
#define BUCK_OUT2_INIT_DELAY_US        (600U)

/* The definition for the delay of the Buck regulator after its output
* voltage is changed
*/
#define BUCK_OUT2_STABILIZATION_DELAY_US    (200U)

/* Define for transitional 0.95 V for buck regulator */
#define BUCK_OUT1_VOLTAGE_0_95V             (3U)

/* Define for a Buck regulator stabilization delay from 0.9 V to 0.95 V */
#define BUCK_OUT1_0_9V_TO_0_95V_DELAY_US    (52U)

/* Define for a Buck regulator stabilization delay from 0.95 V to 1.1 V */
#define BUCK_OUT1_0_95V_TO_1_1V_DELAY_US    (145U)

/* Define for an LDO stabilization delay from 0.9 V to 0.95 V */
#define LDO_0_9V_TO_0_95V_DELAY_US          (3U)

/* Define for an LDO regulator stabilization delay from 0.95 V to 1.1 V */
#define LDO_0_95V_TO_1_1V_DELAY_US          (7U)

/* Define for ROM trim in LP mode */
#define CPUSS_TRIM_ROM_LP                 (0x00000013U)

/* Define for RAM trim in LP mode */
#define CPUSS_TRIM_RAM_LP                 (0x00004013U)

/* Define for ROM trim in ULP mode   */
#define CPUSS_TRIM_ROM_ULP                (0x00000012U)

/* Define for trim RAM in ULP mode */
#define CPUSS_TRIM_RAM_ULP                (0x00006012U)

/* Define for IPC0 notification */
#define SYSPM_IPC_NOTIFY_STRUCT0          ((uint32_t) 0x1UL << CY_IPC_INTR_SYSCALL1)

/* The define of bit positions of the syscall return status */
#define SYSCALL_STATUS_MASK               (0xFF000000U)

/* The define for the success return status of the syscall */
#define SYSCALL_STATUS_SUCCESS            (0xA0000000U)

/* The define for device TO *B Revision ID */
#define SYSPM_DEVICE_PSOC6ABLE2_REV_0B    (0x22U)

/* The pointer to the Cy_EnterDeepSleep() function in the ROM */
#define ROM_ENTER_DEEP_SLEEP_ADDR    (*(uint32_t *) 0x00000D30UL)

/* The define to call the ROM Cy_EnterDeepSleep() function. 
* The ROM Cy_EnterDeepSleep() function prepares the system for the Deep Sleep 
* and restores the system after wakeup from the Deep Sleep. */
typedef void (*cy_cb_syspm_deep_sleep_t)(cy_en_syspm_waitfor_t waitFor, bool *wasEventSent);

#define EnterDeepSleepSrom(waitFor, wasEventSent) \
       ((cy_cb_syspm_deep_sleep_t) ROM_ENTER_DEEP_SLEEP_ADDR)((waitFor), &(wasEventSent))

/* Mask for the RAM read assist bits */
#define CPUSS_TRIM_RAM_CTL_RA_MASK                   ((uint32_t) 0x3U << 8U)

/* The define for SROM opcode to set the flash voltage bit */
#define FLASH_VOLTAGE_BIT_ULP_OPCODE                 (0x0C000003U)

/* The define for SROM opcode to clear the flash voltage bit */
#define FLASH_VOLTAGE_BIT_LP_OPCODE                  (0x0C000001U)

/* The define for SROM opcode to set the flash voltage bit */
#define FLASH_VOLTAGE_BIT_ULP_PSOC6ABLE2_OPCODE      (0x30000101U)

/* The define for SROM to clear the flash voltage bit */
#define FLASH_VOLTAGE_BIT_LP_PSOC6ABLE2_OPCODE       (0x30000001U)

/* The wait time for transition into the minimum regulator current mode
*/
#define SET_MIN_CURRENT_MODE_DELAY_US         (1U)

/* The wait delay time that occurs before the active reference is settled.
*  Intermediate delay is used in transition into the normal regulator current 
*  mode
*/
#define ACT_REF_SETTLE_DELAY_US         (8U)

/* The wait delay time that occurs after the active reference is settled. 
*  Final delay is used in transition into the normal regulator current mode
*/
#define SET_NORMAL_CURRENT_MODE_DELAY_US     (1U)

/* The internal define of the tries number in the 
* Cy_SysPm_SystemSetMinRegulatorCurrent() function
*/
#define WAIT_DELAY_TRYES                (100U)

/* The define of retained power mode of the CM4 */
#define CM4_PWR_STS_RETAINED            (2UL)

/* The define for number of callback roots */
#define CALLBACK_ROOT_NR                (5U)

/* Mask for checking the CM4 Deep Sleep status */
#define CM4_DEEPSLEEP_MASK     (CPUSS_CM4_STATUS_SLEEPING_Msk | CPUSS_CM4_STATUS_SLEEPDEEP_Msk)

/* Mask for checking the CM0P Deep Sleep status */
#define CM0_DEEPSLEEP_MASK     (CPUSS_CM0_STATUS_SLEEPING_Msk | CPUSS_CM0_STATUS_SLEEPDEEP_Msk)

/* The mask to unlock the Hibernate power mode */
#define HIBERNATE_UNLOCK_VAL                 ((uint32_t) 0x3Au << SRSS_PWR_HIBERNATE_UNLOCK_Pos)

/* The mask to set the Hibernate power mode */
#define SET_HIBERNATE_MODE                   ((HIBERNATE_UNLOCK_VAL |\
                                               SRSS_PWR_HIBERNATE_FREEZE_Msk |\
                                               SRSS_PWR_HIBERNATE_HIBERNATE_Msk))

/* The mask to retain the Hibernate power mode status */
#define HIBERNATE_RETAIN_STATUS_MASK         ((SRSS_PWR_HIBERNATE_TOKEN_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk |\
                                               SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk))

/** The mask for the Hibernate wakeup sources */
#define HIBERNATE_WAKEUP_MASK               ((SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk |\
                                              SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk |\
                                              SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk |\
                                              SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk))

/** The define to update the token to indicate the transition into Hibernate */
#define HIBERNATE_TOKEN                    ((uint32_t) 0x1BU << SRSS_PWR_HIBERNATE_TOKEN_Pos)


/* The mask for low power modes the power circuits (POR/BOD, Bandgap 
*  reference, Reference buffer, Current reference) when active core regulator is
*  LDO
*/
#define PWR_CIRCUITS_SET_LPMODE_LDO_MASK        (SRSS_PWR_CTL_LINREG_LPMODE_Msk | PWR_CIRCUITS_SET_LPMODE_BUCK_MASK)

/* The mask for low power modes the power circuits (POR/BOD, Bandgap 
*  reference, Reference buffer, Current reference) when active core regulator is
*  Buck
*/
#define PWR_CIRCUITS_SET_LPMODE_BUCK_MASK       (SRSS_PWR_CTL_PORBOD_LPMODE_Msk |\
                                                 SRSS_PWR_CTL_BGREF_LPMODE_Msk |\
                                                 SRSS_PWR_CTL_VREFBUF_LPMODE_Msk |\
                                                 SRSS_PWR_CTL_IREF_LPMODE_Msk)

/*******************************************************************************
*       Internal Variables
*******************************************************************************/

/* Array of the callback roots */
static cy_stc_syspm_callback_t* pmCallbackRoot[CALLBACK_ROOT_NR] = {NULL, NULL, NULL, NULL, NULL};

#if (CY_CPU_CORTEX_M4)
    /* Global boolean variable used to clear the  Event Register of the CM4 core */
    static bool wasEventSent = false;
#endif /* (CY_CPU_CORTEX_M4) */


/*******************************************************************************
* Function Name: Cy_SysPm_ReadStatus
****************************************************************************//**
*
* Reads the power modes status of the system and CPU(s).
*
* \return 
* The current power mode. See \ref group_syspm_return_status.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_ReadStatus
*
*******************************************************************************/
uint32_t Cy_SysPm_ReadStatus(void)
{
    uint32_t pmStatus = 0UL;

    /* Check whether CM4 is in Deep Sleep mode */
    if ((CPUSS_CM4_STATUS & CM4_DEEPSLEEP_MASK) == CM4_DEEPSLEEP_MASK)
    {
        pmStatus |= CY_SYSPM_STATUS_CM4_DEEPSLEEP;
    }
    /* Check whether CM4 is in Sleep mode */
    else if(0U != _FLD2VAL(CPUSS_CM4_STATUS_SLEEPING, CPUSS_CM4_STATUS))
    {
        pmStatus |= CY_SYSPM_STATUS_CM4_SLEEP;
    }
    else
    {
        pmStatus |= CY_SYSPM_STATUS_CM4_ACTIVE;
    }

    /* Check whether CM0p is in Deep Sleep mode */
    if ((CPUSS_CM0_STATUS & CM0_DEEPSLEEP_MASK) == CM0_DEEPSLEEP_MASK)
    {
        pmStatus |= CY_SYSPM_STATUS_CM0_DEEPSLEEP;
    }
    /* Check whether CM0p is in Sleep mode*/
    else if (0U != _FLD2VAL(CPUSS_CM0_STATUS_SLEEPING, CPUSS_CM0_STATUS))
    {
        pmStatus |= CY_SYSPM_STATUS_CM0_SLEEP;
    }
    else
    {
        pmStatus |= CY_SYSPM_STATUS_CM0_ACTIVE;
    }

    /* Check whether the device is in LP mode by reading 
    *  the core voltage:
    *  - 0.9V (nominal) - System ULP mode
    *  - 1.1V (nominal) - System LP mode
    */
    
    /* Read current active regulator */
    if (Cy_SysPm_LdoIsEnabled())
    {
        /* Current active regulator is LDO */
        if (Cy_SysPm_LdoGetVoltage() != CY_SYSPM_LDO_VOLTAGE_ULP)
        {
            pmStatus |= CY_SYSPM_STATUS_SYSTEM_LP;
        }
        else
        {
            pmStatus |= CY_SYSPM_STATUS_SYSTEM_ULP;
        }
    }
    else
    {
        /* Current active regulator is Buck */
        if (Cy_SysPm_BuckGetVoltage1() != CY_SYSPM_BUCK_OUT1_VOLTAGE_ULP)
        {
            pmStatus |= CY_SYSPM_STATUS_SYSTEM_LP;
        }
        else
        {
            pmStatus |= CY_SYSPM_STATUS_SYSTEM_ULP;
        }
    }

    return pmStatus;
}


/*******************************************************************************
* Function Name: Cy_SysPm_CpuEnterSleep
****************************************************************************//**
*
* Sets executing CPU to Sleep mode.
*
* Puts the CPU executing this function into CPU Sleep power mode. If callback 
* functions were registered they are also executed.
*
* For more detail about switching into CPU Sleep power mode and debug,
* refer to the device technical reference manual (TRM).
*
* If at least one callback function with the CY_SYSPM_SLEEP type was registered,
* the following algorithm is executed:
* Prior to entering CPU Sleep mode, all callback functions of the CY_SYSPM_SLEEP
* type with the CY_SYSPM_CHECK_READY parameter are called. This allows the 
* driver to signal whether it is ready to enter the low power mode. If any of 
* the callbacks of the CY_SYSPM_SLEEP type with the CY_SYSPM_CHECK_READY 
* parameter returns CY_SYSPM_FAIL, the remaining callbacks of the 
* CY_SYSPM_SLEEP type with the CY_SYSPM_CHECK_READY parameter are skipped.
* After the first CY_SYSPM_FAIL, all the CY_SYSPM_SLEEP callbacks that were 
* previously executed before getting the CY_SYSPM_CHECK_FAIL are executed with 
* the CY_SYSPM_CHECK_FAIL parameter. The CPU Sleep mode is not entered and the 
* Cy_SysPm_CpuEnterSleep() function returns CY_SYSPM_FAIL.
*
* If all of the callbacks of the CY_SYSPM_SLEEP type with the 
* CY_SYSPM_CHECK_READY parameter return CY_SYSPM_SUCCESS, then all 
* callbacks of the CY_SYSPM_SLEEP type with the CY_SYSPM_CHECK_FAIL parameters 
* calls are skipped. All callbacks of the CY_SYSPM_SLEEP type and then
* CY_SYSPM_BEFORE_TRANSITION parameter calls are executed, allowing the 
* peripherals to prepare for CPU Sleep. The CPU then enters Sleep mode.
* This is a CPU-centric power mode. This means that the CPU has entered Sleep
* mode and its main clock is removed. Any enabled interrupt can cause a CPU 
* wakeup from Sleep mode. 
*
* For multi-core devices, CPU wakeup can also be performed using the Send Event 
* (SEV) assembly instruction executed from the other active CPU. Such wakeup is 
* expected only if the CPU Sleep power mode is done with WFE assembly 
* instruction.
*
* After a wakeup from CPU Sleep, all of the registered callbacks of the 
* CY_SYSPM_SLEEP type and with the CY_SYSPM_AFTER_TRANSITION parameter are 
* executed to return the peripherals to CPU active operation. 
* The Cy_SysPm_CpuEnterSleep() function returns CY_SYSPM_SUCCESS.
* No callbacks of the CY_SYSPM_SLEEP type with the CY_SYSPM_BEFORE_TRANSITION 
* parameter or callbacks of the CY_SYSPM_SLEEP type and 
* CY_SYSPM_AFTER_TRANSITION parameter callbacks are executed if CPU Sleep mode 
* is not entered.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the 
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating 
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* To support control of callback execution order th following method is 
* implemented. Callback function with the CY_SYSPM_CHECK_READY and 
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are 
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and 
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they 
* are registered. 

* The return value from executed callback functions with the 
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* \ref cy_en_syspm_callback_mode_t, except the CY_SYSPM_CHECK_READY, are ignored
*
* \note The Arm BSD assembly instruction is not required in this function 
* because the function implementation ensures the SLEEPDEEP bit of SCS register 
* is settled prior executing WFI/WFE instruction.
*
* \param waitFor
* Selects wait for action. See \ref cy_en_syspm_waitfor_t.
*
* \return
* Entered status, see \ref cy_en_syspm_status_t.
*
* \sideeffect
* This function clears the Event Register of the CM4 CPU after wakeup from WFE.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_CpuEnterSleep
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CpuEnterSleep(cy_en_syspm_waitfor_t waitFor)
{
    uint32_t interruptState;
    uint32_t cbSleepRootIdx = (uint32_t) CY_SYSPM_SLEEP;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    
    CY_ASSERT_L3(CY_SYSPM_IS_WAIT_FOR_VALID(waitFor));

    /* Call registered callback functions with CY_SYSPM_CHECK_READY parameter */
    if (pmCallbackRoot[cbSleepRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_CHECK_READY);
    }

    /* The CPU can switch into the Sleep power mode only when
    *  all executed registered callback functions with the CY_SYSPM_CHECK_READY 
    *  parameter return CY_SYSPM_SUCCESS.
    */
    if(retVal == CY_SYSPM_SUCCESS)
    {
        /* Call the registered callback functions with 
        * CY_SYSPM_BEFORE_TRANSITION parameter
        */
        interruptState = Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_BEFORE_TRANSITION);
        }

        /* The CPU enters the Sleep power mode upon execution of WFI/WFE */
        SCB_SCR &= (uint32_t) ~SCB_SCR_SLEEPDEEP_Msk;

        if(waitFor != CY_SYSPM_WAIT_FOR_EVENT)
        {
            __WFI();
        }
        else
        {
            __WFE();

        #if (CY_CPU_CORTEX_M4)

            /* For the CM4 CPU, the WFE instruction is called twice. 
            *  The second WFE call clears the Event Register of CM4 CPU.
            *  Cypress ID #279077.
            */
            if(wasEventSent)
            {
                __WFE();
            }

            wasEventSent = true;
        #endif /* (CY_CPU_CORTEX_M4) */
        }
        Cy_SysLib_ExitCriticalSection(interruptState);

        /* Call the registered callback functions with the 
        *  CY_SYSPM_AFTER_TRANSITION parameter
        */
        if (pmCallbackRoot[cbSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_AFTER_TRANSITION);
        }
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to
        *  undo everything done in the callback with the CY_SYSPM_CHECK_READY 
        *  parameter
        */
        (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_CHECK_FAIL);
        retVal = CY_SYSPM_FAIL;
    }
    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_CpuEnterDeepSleep
****************************************************************************//**
*
* Sets executing CPU to the Deep Sleep mode.
*
* Puts the CPU executing the function into CPU Deep Sleep. For a single CPU
* devices the device will immediately transition to system Deep Sleep. For a 
* dual CPU devices the device will transition to system Deep Sleep only after 
* both CPUs are in CPU Deep Sleep power mode. 
*
* Prior to entering the CPU Deep Sleep mode, all callbacks of the 
* CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_READY parameter registered 
* callbacks are called, allowing the driver to signal whether it is ready to 
* enter the power mode. If any CY_SYSPM_DEEPSLEEP type with the 
* CY_SYSPM_CHECK_READY parameter call returns CY_SYSPM_FAIL, the remaining 
* callback CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_READY parameter are 
* skipped. After the first CY_SYSPM_FAIL, all the CY_SYSPM_SLEEP callbacks that 
* were previously executed before getting the CY_SYSPM_CHECK_FAIL are executed 
* with the CY_SYSPM_CHECK_FAIL parameter. The CPU Deep Sleep mode is not entered
* and the Cy_SysPm_CpuEnterDeepSleep() function returns CY_SYSPM_FAIL.
*
* If all callbacks of the CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_READY
* parameter return CY_SYSPM_SUCCESS, then all callbacks of the 
* CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_FAIL parameter calls are 
* skipped. All callbacks of the CY_SYSPM_DEEPSLEEP type with the 
* CY_SYSPM_BEFORE_TRANSITION parameter calls are then executed, allowing the 
* peripherals to prepare for CPU Deep Sleep. The Deep Sleep mode is then 
* entered. Any enabled interrupt can cause a wakeup from the Deep Sleep mode.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the 
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating 
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* The return value from executed callback functions with the 
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* If the firmware attempts to enter this mode before the system is ready (that
* is, when PWR_CONTROL.LPM_READY = 0), then the CPU(s) will go into the CPU
* Sleep mode instead and automatically enter system Deep Sleep mode when the
* system is ready. On dual CPU devices, if one CPU enters CPU Deep Sleep and the 
* other CPU remains active or is in CPU Sleep the first CPU will remain in CPU 
* Deep Sleep. A CPU Deep Sleep is functionally identical to CPU Sleep.
*
* The device enters system Deep Sleep mode when all the CPU(s) are in CPU 
* Deep Sleep, there are no busy peripherals, the debugger is not active, and the
* Deep Sleep power and reference are ready (PWR_CONTROL.LPM_READY=1).
*
* The peripherals that do not need a clock or that receive a clock from their
* external interface (e.g. I2C/SPI) may continue operating in system Deep Sleep.
* All circuits using current from Vccdpslp supply are limited by its maximum 
* current specification of the Deep Sleep regulator.
*
* Wakeup occurs when an interrupt asserts from a Deep Sleep active peripheral.
* For more detail, see the corresponding peripheral's datasheet.
*
* For multi-core devices, CPU wakeup can also be performed using the Send Event 
* (SEV) assembly instruction executed from the other active CPU. Such wakeup is 
* expected only if the CPU Sleep power mode is done with WFE assembly 
* instruction.
*
* \note 
* For multi-CPU devices, the second CPU, if it did not participate in 
* system wakeup, remains in CPU Deep Sleep mode. Any Deep Sleep capable 
* interrupt routed to this CPU can also wake it.
*
* For more detail about switching into the system Deep Sleep power mode and 
* debug, refer to the device TRM.
*
* A normal wakeup from the Deep Sleep power mode returns to either ULP or LP 
* mode, depending on the previous state and programmed behavior for the 
* particular wakeup interrupt. As soon as the system resumes LP or ULP mode the 
* CPU(s) return to CPU Active or CPU Deep Sleep mode, depending on their 
* configured wakeup settings.
*
* After wakeup from CPU Deep Sleep, all of the registered callbacks with
* CY_SYSPM_DEEPSLEEP type with CY_SYSPM_AFTER_TRANSITION are executed to return 
* peripherals to active operation. The Cy_SysPm_CpuEnterDeepSleep() function 
* returns CY_SYSPM_SUCCESS. No callbacks are executed with CY_SYSPM_DEEPSLEEP 
* type with CY_SYSPM_BEFORE_TRANSITION or CY_SYSPM_AFTER_TRANSITION parameter, 
* if Deep Sleep mode was not entered.
*
* To support control of callback execution order th following method is 
* implemented. Callback function with the CY_SYSPM_CHECK_READY and 
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are 
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and 
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they 
* are registered.
*
* \param waitFor 
* Selects wait for action. See \ref cy_en_syspm_waitfor_t.
*
* \sideeffect
* This side effect is applicable only for devices with a UDBs.
* You can obtain unpredictable behavior of the UDB block after the device wakeup
* from system Deep Sleep.
* Unpredictable behavior scenario:
* * The first CPU saves non-retained UDB configuration registers and goes into
*   the CPU Deep Sleep (Cy_SysPm_CpuEnterDeepSleep() function).
* * These non-retained UDB configuration registers are modified in runtime by 
*   another (second) active CPU.
* * The second CPU saves non-retained UDB configuration registers and goes into
*   the CPU Deep Sleep (Cy_SysPm_CpuEnterDeepSleep() function).
*   These conditions save different values of the non-retained UDB configuration
*   registers. On the first CPU wakeup (system wakeup from Deep Sleep), these 
*   registers are restored by the values saved on the first CPU. After the 
*   second CPU wakeup, these registers are "reconfigured" by the values saved on
*   the second CPU.
*   Be aware of this situation.
*
* \sideeffect
* This function clears the Event Register of CM4 CPU after wakeup from WFE.
*
* \sideeffect
* This side effect is applicable only for rev-08 of the CY8CKIT-062.
* This function changes the slow and fast clock dividers to
* SYSPM_CLK_DIVIDER right before entering into system Deep Sleep and restores
* these dividers after wakeup.
*
* \return
* Entered status, see \ref cy_en_syspm_status_t.
*
* \note
* The FLL/PLL are not restored right before the CPU(s) start executing the 
* instructions after System Deep Sleep. This can affect the peripheral that is 
* driven by PLL/FLL. Ensure that the PLL/FLL are properly restored (locked)
* after wakeup from System Deep Sleep. Refer to the 
* \ref group_sysclk driver documentation for information about how to 
* read the PLL/FLL lock statuses.
*
* \note The Arm BSD assembly instruction is not required in this function 
* because the function implementation ensures the SLEEPDEEP bit of SCS register 
* is settled prior executing the WFI/WFE instruction.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_CpuEnterDeepSleep
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CpuEnterDeepSleep(cy_en_syspm_waitfor_t waitFor)
{
    uint32_t interruptState;
    uint32_t cbDeepSleepRootIdx = (uint32_t) CY_SYSPM_DEEPSLEEP;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;

    CY_ASSERT_L3(CY_SYSPM_IS_WAIT_FOR_VALID(waitFor));

    /* Call the registered callback functions with the CY_SYSPM_CHECK_READY 
    *  parameter
    */
    if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback(CY_SYSPM_DEEPSLEEP, CY_SYSPM_CHECK_READY);
    }

    /* The CPU can switch into the Deep Sleep power mode only when
    *  all executed registered callback functions with the CY_SYSPM_CHECK_READY
    *  parameter return CY_SYSPM_SUCCESS
    */
    if (retVal == CY_SYSPM_SUCCESS)
    {
        /* Call the registered callback functions with the 
        * CY_SYSPM_BEFORE_TRANSITION parameter
        */
        interruptState = Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_DEEPSLEEP, CY_SYSPM_BEFORE_TRANSITION);
        }

        static cy_stc_syspm_backup_regs_t regs;

        if (0U != cy_device->udbPresent)
        {
            /* Check whether the UDB disabled on MMIO level */
            if (0UL != (PERI_GR_SL_CTL(MMIO_UDB_SLAVE_NR) & PERI_UDB_SLAVE_ENABLED))
            {
                /* Save non-retained registers */
                Cy_SysPm_SaveRegisters(&regs);
            }
        }

        /* Different device families and revisions have a different Deep Sleep entries */
        if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
        {
            /* The CPU enters Deep Sleep and wakes up in the RAM */
            EnterDeepSleepRam(waitFor);
        }
        else
        {

        #if (CY_CPU_CORTEX_M4)
            /* Repeat the WFI/WFE instruction if a wake up was not intended. 
            *  Cypress ID #272909
            */
            do
            {
        #endif /* (CY_CPU_CORTEX_M4) */

                /* The CPU enters Deep Sleep mode upon execution of WFI/WFE */
                SCB_SCR |= SCB_SCR_SLEEPDEEP_Msk;

                if(waitFor != CY_SYSPM_WAIT_FOR_EVENT)
                {
                    __WFI();
                }
                else
                {
                    __WFE();

                #if (CY_CPU_CORTEX_M4)
                    /* Call the WFE instruction twice to clear the Event register 
                    *  of the CM4 CPU. Cypress ID #279077
                    */
                    if(wasEventSent)
                    {
                        __WFE();
                    }
                    wasEventSent = true;
                #endif /* (CY_CPU_CORTEX_M4) */
                }

        #if (CY_CPU_CORTEX_M4)
            } while (_FLD2VAL(CPUSS_CM4_PWR_CTL_PWR_MODE, CPUSS_CM4_PWR_CTL) == CM4_PWR_STS_RETAINED);
        #endif /* (CY_CPU_CORTEX_M4) */
        }

        if (0U != cy_device->udbPresent)
        {
            /* Do not restore the UDB if it is disabled on MMIO level */
            if (0UL != (PERI_GR_SL_CTL(MMIO_UDB_SLAVE_NR) & PERI_UDB_SLAVE_ENABLED))
            {
                /* Restore non-retained registers */
                Cy_SysPm_RestoreRegisters(&regs);
            }
        }

        Cy_SysLib_ExitCriticalSection(interruptState);

        /* Call the registered callback functions with the CY_SYSPM_AFTER_TRANSITION 
        *  parameter
        */
        if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_DEEPSLEEP, CY_SYSPM_AFTER_TRANSITION);
        }
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to 
        * undo everything done in the callback with the CY_SYSPM_CHECK_READY 
        * parameter
        */
        (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_DEEPSLEEP, CY_SYSPM_CHECK_FAIL);
        retVal = CY_SYSPM_FAIL;
    }
    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_SystemEnterHibernate
****************************************************************************//**
*
* Sets the device into system Hibernate mode.
*
* Puts the device into the system Hibernate power mode. Prior to entering 
* Hibernate mode, all callbacks of the CY_SYSPM_HIBERNATE type are executed. 
*
* First, callbacks of the CY_SYSPM_HIBERNATE type are called with the 
* CY_SYSPM_CHECK_READY parameter. This allows the callback to signal that the 
* driver is not ready to enter the system Hibernate power mode. If any of the 
* callback return CY_SYSPM_FAIL, the remaining CY_SYSPM_HIBERNATE callbacks are 
* skipped. In this case, all of the callbacks that have already been called are 
* called again with the CY_SYSPM_CHECK_FAIL parameter. System Hibernate mode is 
* not entered and the Cy_SysPm_SystemEnterHibernate() function returns 
* CY_SYSPM_FAIL.
*
* If all CY_SYSPM_HIBERNATE callbacks with the CY_SYSPM_CHECK_READY parameter 
* return CY_SYSPM_SUCCESS, then all CY_SYSPM_HIBERNATE callbacks with 
* CY_SYSPM_CHECK_FAIL calls are skipped and all CY_SYSPM_HIBERNATE callbacks 
* with CY_SYSPM_BEFORE_TRANSITION parameter are executed allowing the 
* peripherals to prepare for system Hibernate. 
*
* The I/O output state is automatically frozen by hardware system and Hibernate 
* mode is then entered. In Hibernate mode, all internal supplies are off and no 
* internal state is retained. The only exception is resources powered by the 
* Vbackup domain continue to operate, if enabled. For multi-CPU devices, there 
* is no handshake with the CPUs and the chip will enter Hibernate power 
* mode immediately.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the 
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating 
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* The return value from executed callback functions with the 
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* Wakeup from system Hibernate is triggered by toggling the wakeup pin(s), WDT
* match, or back-up domain RTC alarm expiration, depending on how the they are 
* configured. A wakeup causes a normal boot procedure.
* To configure the wakeup pin(s), a digital input pin must be configured, and
* resistively pulled up or down to the inverse state of the wakeup polarity. To
* distinguish a Hibernate mode from a general reset wakeup event, the
* Cy_SysLib_GetResetReason() function can be used. The wakeup pin and low-power 
* comparators are active-low by default. The wakeup pin or the LPComparators 
* polarity can be changed with the \ref Cy_SysPm_SetHibernateWakeupSource() 
* function.
* This function call will not return if system Hibernate mode is entered. 
* The CY_SYSPM_HIBERNATE callbacks with the CY_SYSPM_AFTER_TRANSITION parameter
* are never executed.
*
* This function freezes the I/O pins implicitly. Entering system Hibernate mode 
* before freezing the I/O pins is not possible. The I/O pins remain frozen after
* waking from Hibernate mode until the firmware unfreezes them with 
* a \ref Cy_SysPm_IoUnfreeze() function call.
*
* Boot firmware should reconfigure the I/O pins as required by the application 
* prior unfreezing them.
*
* To support control of callback execution order th following method is 
* implemented. Callback function with the CY_SYSPM_CHECK_READY and 
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are 
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and 
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they 
* are registered.
*
* \return
* Entered status, see \ref cy_en_syspm_status_t.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SystemEnterHibernate
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemEnterHibernate(void)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    uint32_t cbHibernateRootIdx = (uint32_t) CY_SYSPM_HIBERNATE;
    /* Call the registered callback functions with the 
    * CY_SYSPM_CHECK_READY parameter
    */
    if (pmCallbackRoot[cbHibernateRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback(CY_SYSPM_HIBERNATE, CY_SYSPM_CHECK_READY);
    }

    /* The system can switch into Hibernate power mode only when
    *  all executed registered callback functions with CY_SYSPM_CHECK_READY
    *  parameter return CY_SYSPM_SUCCESS.
    */
    if(retVal == CY_SYSPM_SUCCESS)
    {
        /* Call registered callback functions with CY_SYSPM_BEFORE_TRANSITION 
        *  parameter
        */
        (void) Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbHibernateRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_HIBERNATE, CY_SYSPM_BEFORE_TRANSITION);
        }

        /* Preserve the token that will be retained through a wakeup sequence.
         * This could be used by Cy_SysLib_GetResetReason() to differentiate
         * Wakeup from a general reset event.
         * Preserve the wakeup source(s) configuration.
         */
        SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & HIBERNATE_WAKEUP_MASK) | HIBERNATE_TOKEN;

        /* Disable overriding by the peripherals the next pin-freeze command */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* The second write causes freezing of I/O cells to save the I/O-cell state */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* Third write cause system to enter Hibernate */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* Read register to make sure it is settled */
        (void) SRSS_PWR_HIBERNATE;

        /* Wait for transition */
        __WFI();

        /* The callback function calls with the CY_SYSPM_AFTER_TRANSITION 
        * parameter in the Hibernate power mode are not applicable as system 
        * wake-up was made on system reboot.
        */

        /* A wakeup from Hibernate is performed by toggling of the wakeup 
        * pins, or WDT matches, or Backup domain alarm expires. This depends on 
        * what item is configured in the Hibernate register. After a wakeup 
        * event, a normal Boot procedure occurs. 
        * There is no need to exit from the critical section.
        */
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to 
        * undo everything done in the callback with the CY_SYSPM_CHECK_READY 
        * parameter. The return value should be CY_SYSPM_SUCCESS.
        */
        (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_HIBERNATE, CY_SYSPM_CHECK_FAIL);
        retVal = CY_SYSPM_FAIL;
    }
    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_SystemEnterLp
****************************************************************************//**
*
* Sets device into system Low Power mode.
*
* Returns the system to the default LP mode by raising the core voltage. 
* In the LP mode, the clock frequencies can be increased to t
he LP mode 
* limitations. Refer to the device datasheet for frequency limitations in the 
* LP mode. Approximate LP limit values - \ref group_syspm_lp_limitations.
*
* Prior to entering the system LP mode, all the registered CY_SYSPM_LP callbacks
* with CY_SYSPM_CHECK_READY parameter are called. This allows the driver to 
* signal that it is not ready to enter the system LP mode. If any CY_SYSPM_LP 
* callbacks with the CY_SYSPM_CHECK_READY parameter call return CY_SYSPM_FAIL,
* the remaining CY_SYSPM_LP callbacks with the 
* CY_SYSPM_CHECK_READY parameter calls are skipped.
*
* After a CY_SYSPM_FAIL, all of the CY_SYSPM_LP callbacks with 
* CY_SYSPM_CHECK_FAIL parameter are executed that correspond to the 
* CY_SYSPM_LP callbacks with CY_SYSPM_CHECK_READY parameter that occurred up to 
* the point of failure. System LP mode is not entered and the 
* Cy_SysPm_SystemEnterLp() function returns CY_SYSPM_FAIL.
*
* If all CY_SYSPM_LP callbacks with the CY_SYSPM_CHECK_READY 
* parameter return CY_SYSPM_SUCCESS, then all CY_SYSPM_LP callbacks with
* CY_SYSPM_CHECK_FAIL are skipped and all CY_SYSPM_LP callbacks with the 
* CY_SYSPM_BEFORE_TRANSITION parameter are executed. This allows the 
* peripherals to prepare for LP mode. The system LP mode is then entered.
*
* After entering the system LP mode, all of the registered 
* CY_SYSPM_LP callbacks with the CY_SYSPM_AFTER_TRANSITION parameter 
* are executed to complete preparing the peripherals for low power operation. 
* The Cy_SysPm_SystemEnterLp() function returns CY_SYSPM_SUCCESS. 
* No CY_SYSPM_LP callbacks with the CY_SYSPM_BEFORE_TRANSITION or 
* CY_SYSPM_AFTER_TRANSITION parameter are executed if the system LP mode is not
* entered.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the 
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating 
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* The return value from executed callback functions with the 
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* To support control of callback execution order th following method is 
* implemented. Callback function with the CY_SYSPM_CHECK_READY and 
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are 
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and 
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they 
* are registered.
*
* \return
* - CY_SYSPM_SUCCESS - Entered the system LP mode.
* - CY_SYSPM_INVALID_STATE - The system LP mode was not set. The system LP mode 
*   was not set because the protection context value is higher than zero 
*   (PC > 0) or the device revision does not support modifying registers 
*   (to enter LP mode) via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until 
*   the function returns CY_SYSPM_SUCCESS.
* - CY_SYSPM_FAIL - The system LP mode is not entered.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SystemEnterLp
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemEnterLp(void)
{
    uint32_t interruptState;
    uint32_t cbLpRootIdx = (uint32_t) CY_SYSPM_LP;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;

    /* Call the registered callback functions with the 
    * CY_SYSPM_CHECK_READY parameter
    */
    if (pmCallbackRoot[cbLpRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback(CY_SYSPM_LP, CY_SYSPM_CHECK_READY);
    }

    /* The system can switch into LP only when
    * all executed registered callback functions with the 
    * CY_SYSPM_CHECK_READY parameter return CY_SYSPM_SUCCESS
    */
    if (retVal == CY_SYSPM_SUCCESS)
    {
        
        /* Call the registered callback functions with the 
        * CY_SYSPM_BEFORE_TRANSITION parameter
        */
        interruptState = Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbLpRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_LP, CY_SYSPM_BEFORE_TRANSITION);
        }

        /* Read current active regulator and set LP voltage*/
        if (Cy_SysPm_LdoIsEnabled())
        {
            /* Current active regulator is LDO */
            if (Cy_SysPm_LdoGetVoltage() != CY_SYSPM_LDO_VOLTAGE_LP)
            {
                retVal = Cy_SysPm_LdoSetVoltage(CY_SYSPM_LDO_VOLTAGE_LP);
            }
        }
        else
        {
            /* Current active regulator is Buck */
            if (Cy_SysPm_BuckGetVoltage1() != CY_SYSPM_BUCK_OUT1_VOLTAGE_LP)
            {
                retVal = Cy_SysPm_BuckSetVoltage1(CY_SYSPM_BUCK_OUT1_VOLTAGE_LP);
            }
        }

        Cy_SysLib_ExitCriticalSection(interruptState);

        /* Call the registered callback functions with the 
        * CY_SYSPM_AFTER_TRANSITION parameter
        */
        if (pmCallbackRoot[cbLpRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_LP, CY_SYSPM_AFTER_TRANSITION);
        }
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to 
        * undo everything done in the callback with the CY_SYSPM_CHECK_READY 
        * parameter
        */
        (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_LP, CY_SYSPM_CHECK_FAIL);
        retVal = CY_SYSPM_FAIL;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_SystemEnterUlp
****************************************************************************//**
*
* Sets device into system Ultra Low Power mode.
*
* System ULP mode is similar to system LP mode. The difference is that the 
* system is put under \ref group_syspm_ulp_limitations.
*
* Before entering system ULP mode, the user must configure the system so 
* the maximum clock frequencies are less than the ULP mode specifications 
* presented in the device datasheet. Refer to the device datasheet for 
* the maximum clock limitations in the ULP mode with reduced core supply 
* regulator voltages.
*
* Prior to entering system ULP mode, all the registered CY_SYSPM_ULP callbacks 
* with CY_SYSPM_CHECK_READY parameter are called. This allows the driver to 
* signal if it is not ready to enter system ULP mode. If any CY_SYSPM_ULP 
* callback with the CY_SYSPM_CHECK_READY parameter call returns CY_SYSPM_FAIL, 
* the remaining CY_SYSPM_ULP callbacks with the CY_SYSPM_CHECK_READY parameter 
* are skipped.
*
* After a CY_SYSPM_FAIL, all of the CY_SYSPM_ULP callbacks with the
* CY_SYSPM_CHECK_FAIL parameter are executed that correspond to the 
* CY_SYSPM_ULP callback with CY_SYSPM_CHECK_READY parameter that occurred up to 
* the point of failure. System ULP mode is not entered 
* and the Cy_SysPm_SystemEnterUlp() function returns CY_SYSPM_FAIL.
*
* If all CY_SYSPM_ULP callbacks with the CY_SYSPM_CHECK_READY 
* parameter return CY_SYSPM_SUCCESS, then all CY_SYSPM_ULP 
* callbacks with CY_SYSPM_CHECK_FAIL calls are skipped and all CY_SYSPM_ULP 
* callbacks with the CY_SYSPM_BEFORE_TRANSITION parameter are executed. This 
* allows preparation for ULP. The system ULP mode is then entered.
*
* After entering system ULP, all of the registered CY_SYSPM_ULP callbacks with 
* the CY_SYSPM_AFTER_TRANSITION parameter are executed to complete preparing the 
* peripherals for ULP operation. The Cy_SysPm_SystemEnterUlp() function 
* returns CY_SYSPM_SUCCESS. No CY_SYSPM_ULP callbacks with the 
* CY_SYSPM_BEFORE_TRANSITION or CY_SYSPM_AFTER_TRANSITION parameter are 
* executed, if ULP mode is not entered.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the 
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating 
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* The return value from executed callback functions with the 
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* To support control of callback execution order th following method is 
* implemented. Callback function with the CY_SYSPM_CHECK_READY and 
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are 
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and 
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they 
* are registered.
*
* \return
* - CY_SYSPM_SUCCESS - Entered system ULP mode.
* - CY_SYSPM_INVALID_STATE - System ULP mode was not set. The ULP mode was not 
*   set because the protection context value is higher than zero (PC > 0) or the 
*   device revision does not support modifying registers (to enter system 
*   ULP mode) via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until 
*   the function returns CY_SYSPM_SUCCESS.
* - CY_SYSPM_FAIL - The system ULP mode is not entered.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SystemEnterUlp
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemEnterUlp(void)
{
    uint32_t interruptState;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    uint32_t cbUlpRootIdx = (uint32_t) CY_SYSPM_ULP;

    /* Call the registered callback functions with the 
    * CY_SYSPM_CHECK_READY parameter
    */
    if (pmCallbackRoot[cbUlpRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback(CY_SYSPM_ULP, CY_SYSPM_CHECK_READY);
    }

    /* The system can switch into the ULP only when
    * all executed registered callback functions with the 
    * CY_SYSPM_CHECK_READY parameter return CY_SYSPM_SUCCESS
    */
    if (retVal == CY_SYSPM_SUCCESS)
    {
        /* Call the registered callback functions with the 
        * CY_SYSPM_BEFORE_TRANSITION parameter
        */
        interruptState = Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbUlpRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_ULP, CY_SYSPM_BEFORE_TRANSITION);
        }

        /* Read current active regulator and set ULP voltage*/
        if (Cy_SysPm_LdoIsEnabled())
        {
            /* Current active regulator is LDO */
            if (Cy_SysPm_LdoGetVoltage() != CY_SYSPM_LDO_VOLTAGE_ULP)
            {
                retVal = Cy_SysPm_LdoSetVoltage(CY_SYSPM_LDO_VOLTAGE_ULP);
            }
        }
        else
        {
            /* Current active regulator is Buck */
            if (Cy_SysPm_BuckGetVoltage1() != CY_SYSPM_BUCK_OUT1_VOLTAGE_ULP)
            {
                retVal = Cy_SysPm_BuckSetVoltage1(CY_SYSPM_BUCK_OUT1_VOLTAGE_ULP);
            }
        }

        Cy_SysLib_ExitCriticalSection(interruptState);

        /* Call the registered callback functions with the 
        * CY_SYSPM_AFTER_TRANSITION parameter
        */
        if (pmCallbackRoot[cbUlpRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_ULP, CY_SYSPM_AFTER_TRANSITION);
        }
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to 
        * undo everything done in the callback with the CY_SYSPM_CHECK_READY 
        * parameter
        */
        (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_ULP, CY_SYSPM_CHECK_FAIL);
        retVal = CY_SYSPM_FAIL;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_SystemSetMinRegulatorCurrent
****************************************************************************//**
*
* Sets the system into minimum core regulator current mode. This mode limits 
* maximum current available for the system core logic.
*
* Minimum regulator current mode modifies operation of the system in LP or ULP 
* modes to further reduce current consumption. If the system current is below 
* datasheet current limits for the active core voltage regulator (LDO or Buck),
* this mode may be entered. The user is responsible for ensuring the 
* regulator current limit is met in their application.
*
* When in minimum regulator current mode, the following system resources are 
* also set to their LP mode:
* - Linear regulator (If LDO is active regulator)
* - POR/BOD circuit
* - Bandgap reference circuit
* - Reference buffer circuit
* - Current reference circuit
*
* The LDO and Buck current limits must be met prior to entering this 
* mode. If these are not met, the device may brown out, resulting in an 
* exception or reset. These changes also reduce power supply rejection of 
* the affected system resources, which can result in increased noise or response
* time. These effects must be evaluated in each application.
*
* \return
* See \ref cy_en_syspm_status_t.
* - CY_SYSPM_SUCCESS - Minimum regulator current mode was set
* - CY_SYSPM_CANCELED - The power circuits were not ready to enter into 
*   minimum current mode. You should call the function again.
*
* Refer to device datasheet for maximum current value in regulator minimum 
* current mode.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SystemSetMinRegulatorCurrent
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemSetMinRegulatorCurrent(void)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_CANCELED;

    /* Check are the power circuits are ready to enter into regulator minimum 
    *  current mode
    */
    if (0U != _FLD2VAL(SRSS_PWR_CTL_LPM_READY, SRSS_PWR_CTL))
    {
        /* Configure the minimum current mode for LDO regulator */
        if(Cy_SysPm_LdoIsEnabled())
        {
            SRSS_PWR_CTL |= PWR_CIRCUITS_SET_LPMODE_LDO_MASK;
        }
        else
        {
            /* Configure the minimum current mode for Buck regulator */
            SRSS_PWR_CTL |= PWR_CIRCUITS_SET_LPMODE_BUCK_MASK;
        }

        /* This wait time allows the circuits to remove their dependence on
        *  the Active mode circuits, such as active Reference
        */
        Cy_SysLib_DelayUs(SET_MIN_CURRENT_MODE_DELAY_US);

        /* Disable active reference */
        SRSS_PWR_CTL |= SRSS_PWR_CTL_ACT_REF_DIS_Msk;
        
        retVal = CY_SYSPM_SUCCESS;
    }
    
    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_SystemSetNormalRegulatorCurrent
****************************************************************************//**
*
* Sets the system to normal regulator current mode.
*
* Normal regulator current mode modifies operation of the system in LP or ULP 
* modes to provide maximum core current consumption. If the LDO core regulator 
* is in use, the normal mode output current limits may be used. If the buck 
* regulator is in use, its reduced current output limits still apply.
*
* When in normal regulator current mode, the following system resources are set 
* to their normal mode:
* - Linear regulator (If LDO is active regulator)
* - POR/BOD circuit
* - Bandgap reference circuit
* - Reference buffer circuit
* - Current reference circuit
*
* \return
* - CY_SYSPM_SUCCESS - Normal regulator current mode was set
* - CY_SYSPM_TIMEOUT - The timeout occurred because device was not 
*   ready to enter into the normal regulator current mode
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SystemSetNormalRegulatorCurrent
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemSetNormalRegulatorCurrent(void)
{
    uint32_t timeOut = WAIT_DELAY_TRYES;
    cy_en_syspm_status_t retVal = CY_SYSPM_TIMEOUT;

    /* Configure the regulator normal current mode for the POR/BOD circuits 
    *  and for the Bandgap Voltage and Current References
    */
    if (Cy_SysPm_LdoIsEnabled())
    {
        SRSS_PWR_CTL &= (uint32_t) ~CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_LDO_MASK;
    }
    else
    {
        SRSS_PWR_CTL &= (uint32_t) ~CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_BUCK_MASK;
    }

    /* This wait time allows setting active Reference */
    Cy_SysLib_DelayUs(ACT_REF_SETTLE_DELAY_US);

    while ((0U == _FLD2VAL(SRSS_PWR_CTL_ACT_REF_OK, SRSS_PWR_CTL)) && (0U != timeOut))
    {
        timeOut--;
    }

    if (0U != timeOut)
    {
        /* Disable the low-power for Bandgap reference circuit */
        SRSS_PWR_CTL &= (uint32_t) ~SRSS_PWR_CTL_BGREF_LPMODE_Msk;
        
        /* Delay to finally set the normal current mode */
        Cy_SysLib_DelayUs(SET_NORMAL_CURRENT_MODE_DELAY_US);
        
        retVal= CY_SYSPM_SUCCESS;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_CpuSleepOnExit
****************************************************************************//**
*
* This function configures the sleep-on-exit feature of the CPU.
*
* This API sets the SLEEPONEXIT bit of the SCR register.
* 
* When the sleep-on-exit feature is enabled (the SLEEPONEXIT bit is set), 
* the CPU wakes up to service the interrupt and then immediately goes
* back to sleep. Because of this, the unstacking process is not carried out, so 
* this feature is useful for interrupt driven application and helps to 
* reduce unnecessary stack push and pop operations.
* The CPU does not go to sleep if the interrupt handler returns to 
* another interrupt handler (nested interrupt). 
* You can use this feature in applications that require the CPU to only run 
* when an interrupt occurs.
*
* When the sleep-on-exit feature is disabled (the SLEEPONEXIT bit is cleared), 
* the CPU returns back to the main thread after servicing the interrupt
* without going back to sleep.
*
* Refer to the Arm documentation about the sleep-on-exit feature and 
* SLEEPONEXIT in the SCR register.
*
* \param enable
* - True if enable sleep-on-exit feature.
* - False if disable sleep-on-exit feature.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_CpuSleepOnExit
*
*******************************************************************************/
void Cy_SysPm_CpuSleepOnExit(bool enable)
{
    if(enable)
    {
        /* Enable sleep-on-exit feature */
        SCB_SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
    else
    {
        /* Disable sleep-on-exit feature */
        SCB_SCR &= (uint32_t) ~(SCB_SCR_SLEEPONEXIT_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_SysPm_SetHibernateWakeupSource
****************************************************************************//**
*
* This function configures sources to wake up the device from the system 
* Hibernate power mode. Sources can be wakeup pins, LPComparators, Watchdog (WDT)
* interrupt, or a Real-Time clock (RTC) alarm (interrupt). Wakeup from system 
* Hibernate always results in a device reset and normal boot process.
*
* Wakeup pins:
*
* A wakeup is supported by up to two pins with programmable polarity. These pins
* are typically connected to the GPIO pins or on-chip peripherals under some 
* conditions. See device datasheet for specific pin connections.
* Setting the wakeup pin to this level will cause a wakeup from system Hibernate
* mode. The wakeup pins are active-low by default.
*
* LPComparators:
*
* A wakeup is supported by up to two LPComps with programmable polarity. 
* Setting the LPComp to this level will cause a wakeup from system Hibernate
* mode. The wakeup LPComps are active-low by default.
*
* \note The low-power comparators should be configured and enabled before 
* switching to system Hibernate mode. Refer to the LPComp
* driver description for more detail.
*
* Watchdog Timer:
* 
* \note The WDT should be configured and enabled before entering to system 
* Hibernate mode.
*
* A wakeup is performed by a WDT interrupt.
*
* Real-time Clock:
*
* A wakeup is performed by the RTC alarm.
* Refer to the Real-Time Clock (RTC) driver description for more detail.
*
* For information about wakeup sources and their assignment in specific 
* devices, refer to the appropriate device TRM.
*
* \param wakeupSource 
* The source to be configured as a wakeup source from 
* the system Hibernate power mode, see \ref cy_en_syspm_hibernate_wakeup_source_t.
* The input parameter values can be ORed. For example, if you want to enable 
* LPComp0 (active high) and WDT, call this function:
* Cy_SysPm_SetHibernateWakeupSource(CY_SYSPM_HIBERNATE_LPCOMP0_HIGH | CY_SYSPM_HIBERNATE_WDT).
*
* \warning Do not call this function with different polarity levels for the same
* wakeup source. For example, do not call a function like this:
* Cy_SysPm_SetHibernateWakeupSource(CY_SYSPM_HIBERNATE_LPCOMP0_LOW, CY_SYSPM_HIBERNATE_LPCOMP0_HIGH);
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SetHibernateWakeupSource
*
*******************************************************************************/
void Cy_SysPm_SetHibernateWakeupSource(uint32_t wakeupSource)
{
    CY_ASSERT_L3(CY_SYSPM_IS_WAKE_UP_SOURCE_VALID(wakeupSource));
    
    uint32_t polarityMask = 0U;
    
    if (0U != _FLD2VAL(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, wakeupSource))
    {
        /* Reconfigure the wakeup pins and LPComp polarity based on the input */
        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK;
        }
        
        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_LPCOMP1_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK;
        }
        
        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_PIN0_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK;
        }
        
        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_PIN1_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK;
        }
    }

    SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & (uint32_t) ~polarityMask) | wakeupSource;

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;
}


/*******************************************************************************
* Function Name: Cy_SysPm_ClearHibernateWakeupSource
****************************************************************************//**
*
* This function disables a wakeup source that was previously configured to 
* wake up the device from the system Hibernate mode.
*
* \param wakeupSource
* For the source to be disabled, see \ref cy_en_syspm_hibernate_wakeup_source_t.
* The input parameters values can be ORed. For example, if you want to disable 
* LPComp0 (active high) and WDT call this function:
* Cy_SysPm_ClearHibernateWakeupSource(CY_SYSPM_HIBERNATE_LPCOMP0_HIGH | CY_SYSPM_HIBERNATE_WDT).
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_ClearHibernateWakeupSource
*
*******************************************************************************/
void Cy_SysPm_ClearHibernateWakeupSource(uint32_t wakeupSource)
{
    CY_ASSERT_L3(CY_SYSPM_IS_WAKE_UP_SOURCE_VALID(wakeupSource));
    
    uint32_t clearWakeupSourceMask = wakeupSource & (uint32_t) ~SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk;

    if (0U != _FLD2VAL(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, wakeupSource))
    {
        /* Clear the high active level of the requested sources */
        if ((uint32_t) CY_SYSPM_HIBERNATE_LPCOMP0_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_LPCOMP0_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK;
        }
        
        if ((uint32_t) CY_SYSPM_HIBERNATE_LPCOMP1_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_LPCOMP1_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK;
        }
        
        if ((uint32_t) CY_SYSPM_HIBERNATE_PIN0_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_PIN0_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK;
        }
        
        if ((uint32_t) CY_SYSPM_HIBERNATE_PIN1_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_PIN1_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK;
        }
    }

    SRSS_PWR_HIBERNATE &= (uint32_t) ~clearWakeupSourceMask;

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;
}


/*******************************************************************************
* Function Name: Cy_SysPm_BuckEnable
****************************************************************************//**
*
* Switch the core supply regulator to Buck core regulator instead of the LDO 
* regulator.
* The Buck core regulator provides output voltage(s) using one external 
* inductor and can supply Vccd with higher efficiency than the LDO under some
* conditions, such as high external supply voltage.
*
* Before changing from LDO to Buck, ensure that the circuit board has 
* connected Vccbuck1 to Vccd and also populated the 
* necessary external components for the Buck regulator, including an 
* inductor and a capacitor for each output.
* Refer to the device TRM for more detail.
*
* When changing from a higher voltage to a lower voltage 
* (from system LP = LDO 1.1 V (nominal) to system ULP = Buck 0.9 V (nominal)), 
* ensure that:
* * The device maximum operating frequency for all the Clk_HF paths, peripheral,
*   and slow clock are under the \ref group_syspm_ulp_limitations.
* * The total current consumption is under the \ref group_syspm_ulp_limitations.
* 
* * The appropriate wait states values are set for the flash using 
*   the Cy_SysLib_SetWaitStates() function as explained below.
*
* <b>Setting wait states values for flash</b> 
*
* The flash access time when the core output voltage is 0.9 V (nominal) is 
* longer than at 1.1 V (nominal). Therefore, the number of the wait states must 
* be adjusted. Use the Cy_SysLib_SetWaitStates() function to set the appropriate
* wait state values for flash. 
*
* To change from a higher voltage (LDO 1.1 V) to a lower voltage (Buck 0.9 V), 
* call the Cy_SysLib_SetWaitStates(true, hfClkFreqMz) function before changing 
* the voltage, where hfClkFreqMz is the frequency of HfClk0 in MHz.
*
* To change from a lower voltage (LDO 0.9 V (nominal) to a higher voltage 
* (Buck 1.1 V (nominal)), call the Cy_SysLib_SetWaitStates(false, 
* hfClkFreqMz) function to set the wait states after the voltage change. 
* It is optional, but can be done to improve performance. The clock frequency 
* may now be increased up to system LP mode limits for the new voltage.
* 
* \note 1. If the final Buck output is set to 0.9 V (nominal) - the system is in
*  ULP mode and flash allows read-only operations.
* \note 2. If the final Buck output is set to 1.1 V (nominal) - the system is in
*  LP mode flash allows the read and write operations.
* \note 3. The actual device Vccd voltage can be different from the nominal 
*  voltage because the actual voltage value depends on conditions
*  including the load current.
*
* \warning There is no safe way to go back to the LDO after the 
*  Buck regulator supplies a core. The function enabling the BUck regulator 
*  switches off the LDO.
*
* For more detail, refer to the \ref group_syspm_switching_into_ulp and
* \ref group_syspm_switching_into_lp sections.
* Refer to the \ref group_syslib driver for more detail about setting wait
* states.
*
* \param voltage
* The desired output 1 regulator voltage (Vccbuck1).
* See \ref cy_en_syspm_buck_voltage1_t.
* 
* \return
* - CY_SYSPM_SUCCESS - The voltage is set.
* - CY_SYSPM_INVALID_STATE - The voltage was not set. The voltage cannot be set 
*   because the protection context value is higher than zero (PC > 0) or the 
*   device revision does not support modifying registers via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until 
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
*
* \note 
* The function is applicable only for devices with a Buck regulator.
*
* Function uses a critical section to prevent interrupting the regulators
* switch.
* 
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_BuckEnable
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_BuckEnable(cy_en_syspm_buck_voltage1_t voltage)
{
    CY_ASSERT_L3(CY_SYSPM_IS_BUCK_VOLTAGE1_VALID(voltage));

    cy_en_syspm_status_t retVal = CY_SYSPM_INVALID_STATE;

    /* Enable the Buck regulator only if it was not enabled previously.
    *  If the LDO is disabled, the device is sourced by the Buck regulator
    */
    if (Cy_SysPm_LdoIsEnabled())
    {
        uint32_t interruptState;
        interruptState = Cy_SysLib_EnterCriticalSection();

        /* Update the RAM and ROM trim values when final target Buck 0.9 V */
        if (CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V == voltage)
        {
            if (Cy_SysPm_LdoGetVoltage() != CY_SYSPM_LDO_VOLTAGE_0_9V)
            {
                retVal = Cy_SysPm_LdoSetVoltage(CY_SYSPM_LDO_VOLTAGE_0_9V);
            }
            else
            {
                retVal = CY_SYSPM_SUCCESS;
            }

            if (CY_SYSPM_SUCCESS == retVal)
            {
                /* Increase LDO output voltage to 0.95 V nominal */
                SRSS_PWR_TRIM_PWRSYS_CTL = _CLR_SET_FLD32U((SRSS_PWR_TRIM_PWRSYS_CTL), 
                SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM, LDO_OUT_VOLTAGE_0_95V);
            }
        }

        /* Update the RAM and ROM trim values when the final target Buck 1.1 V */
        if (CY_SYSPM_BUCK_OUT1_VOLTAGE_1_1V == voltage)
        {
            if (Cy_SysPm_LdoGetVoltage() != CY_SYSPM_LDO_VOLTAGE_1_1V)
            {
                retVal = Cy_SysPm_LdoSetVoltage(CY_SYSPM_LDO_VOLTAGE_1_1V);
            }
            else
            {
                retVal = CY_SYSPM_SUCCESS;
            }

            if (CY_SYSPM_SUCCESS == retVal)
            {
                /* Set the LDO 1.15 V as final Buck output is 1.1 V */
                SRSS_PWR_TRIM_PWRSYS_CTL = _CLR_SET_FLD32U((SRSS_PWR_TRIM_PWRSYS_CTL), 
                SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM, LDO_OUT_VOLTAGE_1_15V);
            }
        }

        /* Proceed only if previous settings were done successfully */
        if (CY_SYSPM_SUCCESS == retVal)
        {
            /* A delay for the supply to stabilize at the new voltage */
            Cy_SysLib_DelayUs(LDO_STABILIZATION_DELAY_US);

            /* Disable the Deep Sleep, nWell, and Retention regulators */
            SRSS_PWR_CTL |= (_VAL2FLD(SRSS_PWR_CTL_DPSLP_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_RET_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_NWELL_REG_DIS, 1U));

            /* Configure the Buck regulator */
            SRSS_PWR_BUCK_CTL = 
            _CLR_SET_FLD32U((SRSS_PWR_BUCK_CTL), SRSS_PWR_BUCK_CTL_BUCK_OUT1_SEL, (uint32_t) voltage);

            SRSS_PWR_BUCK_CTL |= _VAL2FLD(SRSS_PWR_BUCK_CTL_BUCK_EN, 1U);

            SRSS_PWR_BUCK_CTL |= _VAL2FLD(SRSS_PWR_BUCK_CTL_BUCK_OUT1_EN, 1U);

            /* Wait until Buck output 1 is stable */
            Cy_SysLib_DelayUs(BUCK_INIT_STABILIZATION_US);

            /* Disable the LDO, because Vbuckout1 and LDO are shorted */
            SRSS_PWR_CTL |= _VAL2FLD(SRSS_PWR_CTL_LINREG_DIS, 1U);
        }

        Cy_SysLib_ExitCriticalSection(interruptState);
    }
    else
    {
        /* The Buck is already enabled, so just update the Buck voltage */
        cy_en_syspm_buck_voltage1_t curBuckVoltage = Cy_SysPm_BuckGetVoltage1();
        
        if (voltage != curBuckVoltage)
        {
            retVal = Cy_SysPm_BuckSetVoltage1(voltage);
        }
        else
        {
            retVal = CY_SYSPM_SUCCESS;
        }
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_BuckSetVoltage1
****************************************************************************//**
*
* Sets the output 1 voltage for the Buck regulator that can supply the device 
* core. This output can supply the device core instead of the LDO regulator.
*
* When changing from a higher voltage 1.1 V (nominal) to a lower voltage 0.9 V 
* (nominal), ensure that:
* * The device maximum operating frequency for all the Clk_HF paths, peripheral,
*   and slow clock are under the \ref group_syspm_ulp_limitations.
* * The total current consumption is under the \ref group_syspm_ulp_limitations.
* * The appropriate wait states values are set for the flash using 
*   the Cy_SysLib_SetWaitStates() function as explained below.
*
* <b>Setting wait states values for flash</b>
*
* The flash access time when the core output voltage is 0.9 V (nominal) is 
* longer than at 1.1 V (nominal). Therefore, the number of the wait states must 
* be adjusted. Use the Cy_SysLib_SetWaitStates() function to set the appropriate
* wait state values for flash. 
*
* To change from a higher voltage to a lower voltage 0.9 V (nominal), 
* call the Cy_SysLib_SetWaitStates(true, hfClkFreqMz) function before changing 
* the voltage, where hfClkFreqMz is the frequency of HfClk0 in MHz.
*
* To change from a lower voltage to a higher voltage 1.1 V (nominal), call 
* the Cy_SysLib_SetWaitStates(false, hfClkFreqMz) function to set the 
* wait states. It is optional, but can be done to improve the performance. 
* The clock frequency may now be increased up to 
* \ref group_syspm_lp_limitations for a new voltage.
* 
* \note 1. The output is set to 0.9 V (nominal) - the system  is in ULP mode 
*  flash allows read-only operations.
* \note 2. The output is set to 1.1 V (nominal) - the system is in LP mode and 
*  flash allows the read and write operations.
* \note 3. The actual device Vccd voltage can be different from the nominal 
*  voltage because the actual voltage value depends on the conditions
*  including the load current.
*
* For more detail, refer to the \ref group_syspm_switching_into_ulp and
* \ref group_syspm_switching_into_lp sections.
* Refer to the \ref group_syslib driver for more detail about setting the 
* wait states.
*
* \param voltage
* The desired output 1 regulator voltage (Vccbuck1).
* See \ref cy_en_syspm_buck_voltage1_t
*
* \return
* - CY_SYSPM_SUCCESS - The voltage is set.
* - CY_SYSPM_INVALID_STATE - The voltage was not set. The voltage cannot be set 
*   because the protection context value is higher than zero (PC > 0) or the 
*   device revision does not support modifying registers via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until 
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_BuckSetVoltage1(cy_en_syspm_buck_voltage1_t voltage)
{
    CY_ASSERT_L3(CY_SYSPM_IS_BUCK_VOLTAGE1_VALID(voltage));

    cy_en_syspm_status_t retVal = CY_SYSPM_INVALID_STATE;

    /* Change the voltage only if protection context is set to zero (PC = 0) 
    *  or the device revision supports modifying registers via syscall
    */
    if (IsVoltageChangePossible())
    {
        uint32_t interruptState;
        interruptState = Cy_SysLib_EnterCriticalSection();

        if (CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V == voltage)
        {
            /* Set bit of the flash voltage control register before ULP mode is set */
            retVal = Cy_SysPm_WriteVoltageBitForFlash(CY_SYSPM_FLASH_VOLTAGE_BIT_ULP);
            
            if (CY_SYSPM_SUCCESS == retVal)
            {
                /* Update read-write margin value for the ULP mode */
                SetReadMarginTrimUlp();
            }
        }
        else
        {
            /* Increase Buck output voltage to 0.95 V nominal */
            SRSS_PWR_BUCK_CTL = 
            _CLR_SET_FLD32U((SRSS_PWR_BUCK_CTL), SRSS_PWR_BUCK_CTL_BUCK_OUT1_SEL, BUCK_OUT1_VOLTAGE_0_95V);
            
            /* Wait until regulator is stable on higher intermediate voltage */
            Cy_SysLib_DelayUs(BUCK_OUT1_0_9V_TO_0_95V_DELAY_US);
            
            /* Update write assist value for the LP mode */
            SetWriteAssistTrimLp();

            retVal = CY_SYSPM_SUCCESS;
        }

        /* Proceed only if previous settings were done successfully */
        if (CY_SYSPM_SUCCESS == retVal)
        {
            /* The system may continue operating while the voltage on Vccd 
            * discharges to the new voltage. The time it takes to reach the 
            * new voltage depends on the conditions, including the load current
            * on Vccd and the external capacitor size.
            */
            SRSS_PWR_BUCK_CTL = 
            _CLR_SET_FLD32U((SRSS_PWR_BUCK_CTL), SRSS_PWR_BUCK_CTL_BUCK_OUT1_SEL, (uint32_t) voltage);

            if (CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V == voltage)
            {
                /* Update write assist value for the ULP mode */
                SetWriteAssistTrimUlp();
            }
            else
            {
                /* Delay stabilizing at the new voltage is required only
                *  when changing from a lower voltage to a higher voltage
                */
                Cy_SysLib_DelayUs(BUCK_OUT1_0_95V_TO_1_1V_DELAY_US);

                /* Update read-write margin value for the LP mode */
                SetReadMarginTrimLp();

                /* Clear bit of the flash voltage control register after 
                * the LP mode is set
                */
                retVal = Cy_SysPm_WriteVoltageBitForFlash(CY_SYSPM_FLASH_VOLTAGE_BIT_LP);
            }
        }

        Cy_SysLib_ExitCriticalSection(interruptState);
    }
    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_BuckIsOutputEnabled
****************************************************************************//**
*
* This function gets the current output status of the Buck outputs.
*
* \param output
* The Buck regulator output. See \ref cy_en_syspm_buck_out_t.
*
* \return
* - True if the requested output is enabled.
* - False if the requested output is disabled.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_BuckIsOutputEnabled
*
*******************************************************************************/
bool Cy_SysPm_BuckIsOutputEnabled(cy_en_syspm_buck_out_t output)
{
    CY_ASSERT_L3(CY_SYSPM_IS_BUCK_OUTPUT_VALID(output));

    bool retVal = false;

    if (output == CY_SYSPM_BUCK_VBUCK_1)
    {
        retVal = (_FLD2BOOL(SRSS_PWR_BUCK_CTL_BUCK_OUT1_EN, SRSS_PWR_BUCK_CTL));
    }

    /* Return false if device does not have the second Buck output (SIMO) */
    if (0U != cy_device->sysPmSimoPresent)
    {
        if(output == CY_SYSPM_BUCK_VRF)
        {
            retVal = ((0U != _FLD2VAL(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_HW_SEL, SRSS_PWR_BUCK_CTL2)) ||
                      (0U != _FLD2VAL(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_EN, SRSS_PWR_BUCK_CTL2)));
        }
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: Cy_SysPm_BuckEnableVoltage2
****************************************************************************//**
*
* Enable the output 2 voltage (Vbuckrf) of the SIMO Buck regulator. 
* The output 2 voltage (Vbuckrf) of the Buck regulator is typically used to 
* supply the BLE radio.
* This function does following actions, when the Buck regulator does not 
* supply the core: 
* * Enables the Buck regulator
* * Enables the output 2, but do not enables the output 1.
*
* \note The function does not affect Buck output 1 that typically supplies core.
*
* \warning The function does not select the Buck output 2 voltage and 
* does not set/clear the HW-controlled bit for Buck output 2. Call
* Cy_SysPm_BuckSetVoltage2() or Cy_SysPm_BuckSetVoltage2HwControl() to 
* configure the Buck output 2.
*
* The function works only on devices with the SIMO Buck regulator.
* Refer to the device datasheet for information on whether the device contains 
* the SIMO Buck.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_BuckEnableVoltage2
*
*******************************************************************************/
void Cy_SysPm_BuckEnableVoltage2(void)
{
    /* Do nothing if device does not have the second Buck output (SIMO) */
    if (0U != cy_device->sysPmSimoPresent)
    {
        if (!Cy_SysPm_BuckIsEnabled())
        {
            /* Enable the SIMO Buck regulator */
            SRSS_PWR_BUCK_CTL |= _VAL2FLD(SRSS_PWR_BUCK_CTL_BUCK_EN, 1U);
        }

        /* Enable the SIMO Buck output 2 */
        SRSS_PWR_BUCK_CTL2 |= _VAL2FLD(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_EN, 1U);

        /* Wait until the output is stable */
        Cy_SysLib_DelayUs(BUCK_OUT2_INIT_DELAY_US);
    }
}


/*******************************************************************************
* Function Name: Cy_SysPm_BuckSetVoltage2
****************************************************************************//**
*
* This function sets output voltage 2 (Vbuckrf) of the SIMO Buck regulator.
* 
* \param voltage
* The voltage of the Buck regulator output 2 (Vbuckrf). 
* See \ref cy_en_syspm_buck_voltage2_t.
*
* \param waitToSettle
* - True to enable the 200 us delay after setting a higher voltage.
* - False to disable the 200 us delay after setting a higher voltage.
*
* \warning You must enable the delay (waitToSettle = true)
* while changing from a lower voltage to a higher voltage.
*
* \note The 200 us delay is required only when changing from a
* lower voltage to a higher voltage. When changing from a higher voltage to a 
* lower one, the delay is not required.
*
* The function works only on devices with the SIMO Buck regulator.
* Refer to the device datasheet for information on whether the device contains 
* SIMO Buck.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_BuckSetVoltage2
*
*******************************************************************************/
void Cy_SysPm_BuckSetVoltage2(cy_en_syspm_buck_voltage2_t voltage, bool waitToSettle)
{
    /* Do nothing if device does not have the second Buck output (SIMO) */
    if (0U != cy_device->sysPmSimoPresent)
    {
        uint32_t curVoltage;

        CY_ASSERT_L3(CY_SYSPM_IS_BUCK_VOLTAGE2_VALID(voltage));
        
        /* Get the current voltage */
        curVoltage = (uint32_t) Cy_SysPm_BuckGetVoltage2();

        if ((uint32_t) voltage != curVoltage)
        {
            SRSS_PWR_BUCK_CTL2 = 
            _CLR_SET_FLD32U((SRSS_PWR_BUCK_CTL2), SRSS_PWR_BUCK_CTL2_BUCK_OUT2_SEL, (uint32_t) voltage);

            /* Delay stabilizing at the new voltage is required only
            *  when changing from a lower voltage to a higher voltage.
            */
            if(waitToSettle && ((uint32_t) voltage > curVoltage))
            {
                Cy_SysLib_DelayUs(BUCK_OUT2_STABILIZATION_DELAY_US);
            }
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SysPm_LdoSetVoltage
****************************************************************************//**
*
* Set output voltage on the core LDO regulator. 
*
* When changing from a higher voltage to a lower voltage as when the device 
* enters system ULP mode, ensure that:
* * The device maximum operating frequency for all the Clk_HF paths, peripheral,
*   and slow clock are under the \ref group_syspm_ulp_limitations.
* * The total current consumption is under the \ref group_syspm_ulp_limitations.
* * The appropriate wait states values are set for the flash using 
*   The Cy_SysLib_SetWaitStates() function as explained below.
*
* <b>Setting wait states values for flash</b>
*
* The flash access time when the core voltage is 0.9 V (nominal) is 
* longer than at 1.1 V (nominal). Therefore, the number of the wait states must 
* be adjusted. Use the Cy_SysLib_SetWaitStates() function to set the appropriate
* wait state values for flash. 
*
* To change from a higher voltage to a lower voltage 0.9 V (nominal), 
* call the Cy_SysLib_SetWaitStates(true, hfClkFreqMz) function before changing 
* the voltage, where hfClkFreqMz is the frequency of HfClk0 in MHz.
*
* To change from a lower voltage to a higher voltage 1.1 V (nominal), calling 
* the Cy_SysLib_SetWaitStates(false, hfClkFreqMz) function to set the 
* wait states is optional, but can be done to improve performance. 
* The clock frequency may now be increased up to 
* \ref group_syspm_lp_limitations.
* 
* \note 1. The output is set to 0.9 V (nominal) - the system is in ULP mode and 
* flash works for read-only operation.
* \note 2. The output is set to 1.1 V (nominal) - the system is in LP mode 
* and flash works for read and write operations.
* \note 3. The actual device Vccd voltage can be different from the nominal 
* voltage because the actual voltage value depends on conditions
* including the load current.
*
* For more detail, refer to the \ref group_syspm_switching_into_ulp and
* \ref group_syspm_switching_into_lp sections.
* Refer to the \ref group_syslib driver for more detail about setting the wait
* states.
*
* \param voltage
* The desired output regulator voltage.
* See \ref cy_en_syspm_ldo_voltage_t voltage
*
* \return
* - CY_SYSPM_SUCCESS - The voltage is set. 
* - CY_SYSPM_INVALID_STATE - The voltage was not set. The voltage cannot be set 
*   because the protection context value is higher than zero (PC > 0) or the 
*   device revision does not support modifying registers via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until 
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_LdoSetVoltage(cy_en_syspm_ldo_voltage_t voltage)
{
    CY_ASSERT_L3(CY_SYSPM_IS_LDO_VOLTAGE_VALID(voltage));

    cy_en_syspm_status_t retVal = CY_SYSPM_INVALID_STATE;

    /* Change the voltage only if protection context is set to zero (PC = 0), 
    *  or the device revision supports modifying registers via syscall
    */
    if (IsVoltageChangePossible())
    {
        uint32_t interruptState;
        uint32_t trimVoltage;
        
        interruptState = Cy_SysLib_EnterCriticalSection();

        if (CY_SYSPM_LDO_VOLTAGE_0_9V == voltage)
        {
            /* Remove additional wakeup delay from Deep Sleep 
            *  for 1.1 V LDO. Cypress ID #290172
            */
            SRSS_PWR_TRIM_WAKE_CTL = 0UL;
            
            trimVoltage =  SFLASH_LDO_0P9V_TRIM;

            /* Set bit of the flash voltage control register before the ULP is set */
            retVal = Cy_SysPm_WriteVoltageBitForFlash(CY_SYSPM_FLASH_VOLTAGE_BIT_ULP);

            if (CY_SYSPM_SUCCESS == retVal)
            {
                /* Update read-write margin value for the ULP mode */
                SetReadMarginTrimUlp();
            }
        }
        else
        {
            /* Configure additional wakeup delay from Deep Sleep 
            *  for 1.1 V LDO. Cypress ID #290172
            */
            SRSS_PWR_TRIM_WAKE_CTL = SFLASH_PWR_TRIM_WAKE_CTL;
            
            trimVoltage = SFLASH_LDO_1P1V_TRIM;

            SRSS_PWR_TRIM_PWRSYS_CTL = 
            _CLR_SET_FLD32U((SRSS_PWR_TRIM_PWRSYS_CTL), SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM, LDO_OUT_VOLTAGE_0_95V);

            /* A delay for the supply to stabilize at the new higher voltage */
            Cy_SysLib_DelayUs(LDO_0_9V_TO_0_95V_DELAY_US);
            
            /* Update write assist value for the LP mode */
            SetWriteAssistTrimLp();

            retVal = CY_SYSPM_SUCCESS;
        }

        if (CY_SYSPM_SUCCESS == retVal)
        {
            /* The system may continue operating while the voltage on Vccd 
            *  discharges to the new voltage. The time it takes to reach the 
            *  new voltage depends on the conditions, including the load current
            *  on Vccd and the external capacitor size.
            */
            SRSS_PWR_TRIM_PWRSYS_CTL = 
            _CLR_SET_FLD32U((SRSS_PWR_TRIM_PWRSYS_CTL), SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM, trimVoltage);

            if (CY_SYSPM_LDO_VOLTAGE_0_9V == voltage)
            {
                /* Update write assist value for the ULP mode */
                SetWriteAssistTrimUlp();
            }
            else
            {
                /* A delay for the supply to stabilize at the new intermediate voltage */
                Cy_SysLib_DelayUs(LDO_0_95V_TO_1_1V_DELAY_US);
                
                /* Update read-write margin value for the LP mode */
                SetReadMarginTrimLp();
                
                /* Clear bit of the flash voltage control register after 
                * the LP mode is set
                */
                retVal = Cy_SysPm_WriteVoltageBitForFlash(CY_SYSPM_FLASH_VOLTAGE_BIT_LP);
            }
        }

        Cy_SysLib_ExitCriticalSection(interruptState);
    }
    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_LdoSetMode
****************************************************************************//**
*
* Configures the core LDO regulator operating mode to one of three modes. 
* Disabled - turns off the LDO regulator and should be selected only after the 
* Buck regulator is operating. Normal mode configures the LDO for operation at 
* the maximum output current limit. Minimal current mode optimizes the LDO at a
* reduced output current limit. Specific device current limits can be found in 
* the device datasheet.
*
* \param mode
* The desired LDO regulator operating mode.
* See \ref cy_en_syspm_ldo_mode_t voltage
*
* \return
* - CY_SYSPM_SUCCESS - Requested regulator current mode was set
* - CY_SYSPM_CANCELED - The power circuits were not ready to enter into 
*   minimum current mode. You should try to call the function again
* - CY_SYSPM_TIMEOUT - Timeout occurred because of active reference was not 
*   ready to enter into the normal regulator current mode
* - CY_SYSPM_FAIL - incorrect mode value was passed
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_LdoSetMode(cy_en_syspm_ldo_mode_t mode)
{
    CY_ASSERT_L3(CY_SYSPM_IS_LDO_MODE_VALID(mode));
    
    cy_en_syspm_status_t retVal = CY_SYSPM_CANCELED;
    
    switch (mode)
    {
        case CY_SYSPM_LDO_MODE_NORMAL:
        {
            retVal = Cy_SysPm_SystemSetNormalRegulatorCurrent();
        }
        break;

        case CY_SYSPM_LDO_MODE_MIN:
        {
            retVal = Cy_SysPm_SystemSetMinRegulatorCurrent();
        }
        break;

        case CY_SYSPM_LDO_MODE_DISABLED:
        {
            /* Disable the LDO, Deep Sleep, nWell, and Retention regulators */
            SRSS_PWR_CTL |= (_VAL2FLD(SRSS_PWR_CTL_DPSLP_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_RET_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_NWELL_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_LINREG_DIS, 1U));

            retVal = CY_SYSPM_SUCCESS;
        }
        break;
        
        default:
            retVal = CY_SYSPM_FAIL;
        break;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_LdoGetMode
****************************************************************************//**
*
* Returns the current core LDO regulator operating mode.
*
* \return
* The LDO regulator operating mode.
* See \ref cy_en_syspm_ldo_mode_t mode
*
*******************************************************************************/
cy_en_syspm_ldo_mode_t Cy_SysPm_LdoGetMode(void)
{
    cy_en_syspm_ldo_mode_t retVal;

    if (!Cy_SysPm_LdoIsEnabled())
    {
        retVal = CY_SYSPM_LDO_MODE_DISABLED;
    }
    else if (Cy_SysPm_SystemIsMinRegulatorCurrentSet())
    {
        retVal = CY_SYSPM_LDO_MODE_MIN;
    }
    else
    {
        retVal = CY_SYSPM_LDO_MODE_NORMAL;
    }
    
    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_RegisterCallback
****************************************************************************//**
*
* Registers a new syspm callback.
*
* A callback is a function called after an event in the driver or
* middleware module has occurred. The handler callback API will be executed if
* the specific event occurs. SysPm callbacks are called when changing power 
* modes. See \ref cy_stc_syspm_callback_t.
*
* \note The registered callbacks are executed in two orders, based on callback 
* mode \ref cy_en_syspm_callback_mode_t. For modes CY_SYSPM_CHECK_READY and 
* CY_SYSPM_BEFORE_TRANSITION, the order is same order as callbacks were 
* registered.
* For modes CY_SYSPM_AFTER_TRANSITION and CY_SYSPM_CHECK_FAIL, the order is 
* reverse as the order callbacks were registered.
*
* \param handler
* The address of the syspm callback structure.
* See \ref cy_stc_syspm_callback_t.
*
* \return
* - True if a callback was registered.
* - False if a callback was not registered.
*
* \note Do not modify the registered structure in run-time.
* \warning After being registered, the SysPm callback structures must be 
* allocated during power mode transition.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_Callback_Func_Declaration
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_Callback_Params_Declaration
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_Callback_Structure_Declaration
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_Callback_Func_Implementation
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_RegisterCallback
*
*******************************************************************************/
bool Cy_SysPm_RegisterCallback(cy_stc_syspm_callback_t* handler)
{
    bool retVal = false;

    /* Verify input */
    if ((handler != NULL) && (handler->callbackParams != NULL) && (handler->callback != NULL))
    {
        uint32_t callbackRootIdx = (uint32_t) handler->type;
        retVal = true;

        /* Get the required power mode root */
        cy_stc_syspm_callback_t* curCallback = pmCallbackRoot[callbackRootIdx];
        cy_stc_syspm_callback_t* lastRegCallback = NULL;
        
        /* Search last registered callback item */
        while (curCallback != NULL)
        {
            if (curCallback == handler)
            {
                /* Do not register already registered callback item */
                retVal = false;
                break;
            }

            /* Safe callback before switching into the next item */
            lastRegCallback = curCallback;

            curCallback = curCallback->nextItm;
        }

        /* Link requested callback item to the linked list */
        if (retVal)
        {
            if (pmCallbackRoot[callbackRootIdx] == NULL)
            {
                /* Link first callback item to the linked list */
                pmCallbackRoot[callbackRootIdx] = handler;
            }
            else
            {
                /* Link requested item to previous item */
                lastRegCallback->nextItm = handler;
            }

            /* Update links to next and previous callback items of requested
            *  callback item
            */
            handler->prevItm = lastRegCallback;
            handler->nextItm = NULL;
        }
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_UnregisterCallback
****************************************************************************//**
*
* This function unregisters a callback.
*
* The registered callback can be unregistered and the function returns true. 
* Otherwise, false is returned.
*
* \param handler The item that should be unregistered.
* See \ref cy_stc_syspm_callback_t.
*
* \return
* - True if callback was unregistered.
* - False if it was not unregistered or no callbacks are registered.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_UnregisterCallback
*
*******************************************************************************/
bool Cy_SysPm_UnregisterCallback(cy_stc_syspm_callback_t const *handler)
{
    bool retVal = false;

    if (handler != NULL)
    {
        uint32_t callbackRootIdx = (uint32_t) handler->type;
        cy_stc_syspm_callback_t* curCallback = pmCallbackRoot[callbackRootIdx];
        
        /* Search requested callback item in the linked list */
        while (curCallback != NULL)
        {
            /* Requested callback is found */
            if (curCallback == handler)
            {
                retVal = true;
                break;
            }
            
            /* Go to next callback item in the linked list */
            curCallback = curCallback->nextItm;
        }
        
        if (retVal)
        {
            /* Requested callback is first in the list */
            if (pmCallbackRoot[callbackRootIdx] == handler)
            {
                /* Check whether this the only callback registered */
                if (pmCallbackRoot[callbackRootIdx]->nextItm != NULL)
                {
                    pmCallbackRoot[callbackRootIdx] = pmCallbackRoot[callbackRootIdx]->nextItm;
                    pmCallbackRoot[callbackRootIdx]->prevItm = NULL;
                }
                else
                {
                    /* We had only one callback */
                    pmCallbackRoot[callbackRootIdx] = NULL;
                }
            }
            else
            {
                /* Update links of related to unregistered callback items */
                curCallback->prevItm->nextItm = curCallback->nextItm;
                
                if (curCallback->nextItm != NULL)
                {
                    curCallback->nextItm->prevItm = curCallback->prevItm;
                }
            }
        }
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_ExecuteCallback
****************************************************************************//**
*
* The function executes all registered callbacks with provided type and mode.
* \note This low-level function is being used by \ref Cy_SysPm_CpuEnterSleep,
* \ref Cy_SysPm_CpuEnterDeepSleep, \ref Cy_SysPm_SystemEnterHibernate, 
* \ref Cy_SysPm_SystemEnterUlp and \ref Cy_SysPm_SystemEnterLp API functions. 
* However, it might be also useful as an independent API function in some custom
* applications.
*
* \note The registered callbacks will be executed in order based on 
* \ref cy_en_syspm_callback_type_t value. There are two possible callback 
* execution orders:
* * From first registered to last registered. This order applies to 
*   callbacks with mode CY_SYSPM_CHECK_READY and CY_SYSPM_BEFORE_TRANSITION.
* * Backward flow execution: 
*   - From last registered to the first registered. This order applies 
*     to callbacks with mode CY_SYSPM_AFTER_TRANSITION.
*   - From last called to the first registered callback. This order applies 
*     to callbacks with mode CY_SYSPM_CHECK_FAIL. Note that, the last called 
*     callback function  that generated the CY_SYSPM_CHECK_FAIL is skipped when 
*     mode CY_SYSPM_CHECK_FAIL. This is because the callback that returns 
*     CY_SYSPM_FAIL already knows that it failed and will not take any action 
*     that requires correction.
*
* If no callbacks are registered, returns CY_SYSPM_SUCCESS.
*
* \param type
* The callback type. See \ref cy_en_syspm_callback_type_t.
*
* \param mode
* The callback mode. See \ref cy_en_syspm_callback_mode_t.
*
* \return
* - CY_SYSPM_SUCCESS if callback successfully completed or nor callbacks 
*   registered.
* - CY_SYSPM_FAIL one of the executed callback(s) returned fail.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_ExecuteCallback
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_ExecuteCallback(cy_en_syspm_callback_type_t type, cy_en_syspm_callback_mode_t mode)
{
    CY_ASSERT_L3(CY_SYSPM_IS_CALLBACK_TYPE_VALID(type));
    CY_ASSERT_L3(CY_SYSPM_IS_CALLBACK_MODE_VALID(mode));
    
    static cy_stc_syspm_callback_t* lastExecutedCallback = NULL;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    cy_stc_syspm_callback_t* curCallback = pmCallbackRoot[(uint32_t) type];
    cy_stc_syspm_callback_params_t curParams;
    
    if ((mode == CY_SYSPM_BEFORE_TRANSITION) || (mode == CY_SYSPM_CHECK_READY))
    {
        /* Execute registered callbacks with order from first registered to the
        *  last registered. Stop executing if CY_SYSPM_FAIL was returned in 
        *  CY_SYSPM_CHECK_READY mode
        */
        while ((curCallback != NULL) && ((retVal != CY_SYSPM_FAIL) || (mode != CY_SYSPM_CHECK_READY)))
        {
            /* The modes defined in the .skipMode element are not executed */
            if (0UL == ((uint32_t) mode & curCallback->skipMode))
            {
                /* Update elements for local callback parameter values */
                curParams.base = curCallback->callbackParams->base;
                curParams.context = curCallback->callbackParams->context;

                retVal = curCallback->callback(&curParams, mode);
                
                /* Update callback pointer with value of executed callback. 
                * Such update is required to execute further callbacks in 
                * backward order after exit from LP mode or to undo 
                * configuration after callback returned fail: from last called
                * to first registered.
                */
                lastExecutedCallback = curCallback;
            }
            curCallback = curCallback->nextItm;
        }
    }
    else
    {
        /* Execute registered callbacks with order from lastCallback or last 
        * executed to the first registered callback. Such a flow is required if 
        * a previous callback function returned CY_SYSPM_FAIL or a previous 
        * callback mode was CY_SYSPM_BEFORE_TRANSITION. Such an order is 
        * required to undo configurations in correct backward order.
        */
        if (mode != CY_SYSPM_CHECK_FAIL)
        {
            while (curCallback->nextItm != NULL)
            {
                curCallback = curCallback->nextItm;
            }
        }
        else
        {
            /* Skip last executed callback that returns CY_SYSPM_FAIL, as this 
            *  callback already knows that it failed.
            */
            curCallback = lastExecutedCallback;

            if (curCallback != NULL)
            {
                curCallback = curCallback->prevItm;
            }
        }

        /* Execute callback functions with required type and mode */
        while (curCallback != NULL)
        {
            /* The modes defined in the .skipMode element are not executed */
            if (0UL == ((uint32_t) mode & curCallback->skipMode))
            {
                /* Update elements for local callback parameter values */
                curParams.base = curCallback->callbackParams->base;
                curParams.context = curCallback->callbackParams->context;

                retVal = curCallback->callback(&curParams, mode);
            }
            curCallback = curCallback->prevItm;
        }
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_IoUnfreeze
****************************************************************************//**
*
* This function unfreezes the I/O cells that are automatically frozen when 
* Hibernate is entered with the call to \ref Cy_SysPm_SystemEnterHibernate().
*
* I/O cells remain frozen after a wakeup from Hibernate mode until the
* firmware unfreezes them by calling this function.
*
* If the firmware must retain the data value on the pin, then the
* value must be read and re-written to the pin's port data register before 
* calling this function. Furthermore, the drive mode must be re-programmed 
* before the pins are unfrozen. If this is not done, the pin will change to 
* the default state the moment the freeze is removed.
*
* Note that I/O cell configuration can be changed while frozen. The new 
* configuration becomes effective only after the pins are unfrozen.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_IoUnfreeze
*
*******************************************************************************/
void Cy_SysPm_IoUnfreeze(void)
{
    uint32_t interruptState;
    interruptState = Cy_SysLib_EnterCriticalSection();

    /* Preserve the last reset reason and wakeup polarity. Then, unfreeze I/O:
     * write PWR_HIBERNATE.FREEZE=0, .UNLOCK=0x3A, .HIBERANTE=0
     */
    SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & HIBERNATE_RETAIN_STATUS_MASK) | HIBERNATE_UNLOCK_VAL;

    /* Lock the Hibernate mode: 
    * write PWR_HIBERNATE.HIBERNATE=0, UNLOCK=0x00, HIBERANTE=0
    */
    SRSS_PWR_HIBERNATE &= HIBERNATE_RETAIN_STATUS_MASK;
    
    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;

    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_SysPm_WriteVoltageBitForFlash
****************************************************************************//**
*
* Function that changes the voltage setting for flash.
*
* \note
* Call this function before system enters ULP mode. Call this function after 
* the system enters LP mode.
* 
* \param value
* Value to be set in the flash voltage control register. 
* See \ref cy_en_syspm_flash_voltage_bit_t.
*
* \return
* - CY_SYSPM_SUCCESS - The voltage is set. 
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until 
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_WriteVoltageBitForFlash
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_WriteVoltageBitForFlash(cy_en_syspm_flash_voltage_bit_t value)
{
    CY_ASSERT_L3(CY_SYSPM_IS_BIT_FOR_FLASH_VALID(value));
    
    cy_en_syspm_status_t retVal = CY_SYSPM_CANCELED;
    uint16_t curDeviceRevision = Cy_SysLib_GetDeviceRevision();
    uint16_t curDevice = Cy_SysLib_GetDevice();

    /* Check the current protection context value. We can have a direct register
    *  update if protection context is = 0 */
    if ((Cy_Prot_GetActivePC(ACTIVE_BUS_MASTER) == 0U) && (curDevice == CY_SYSLIB_DEVICE_PSOC6ABLE2) && 
                                                          (curDeviceRevision <= SYSPM_DEVICE_PSOC6ABLE2_REV_0B))
    {
        FLASHC_FM_CTL_ANA_CTL0 = 
        _CLR_SET_FLD32U((FLASHC_FM_CTL_ANA_CTL0), FLASHC_FM_CTL_ANA_CTL0_VCC_SEL, value);
    
        retVal = CY_SYSPM_SUCCESS;
    }

    /* Update the flash voltage bit using a syscall. This can be done on devices
    *  that support modifying registers via syscall.
    */
    if (((curDevice == CY_SYSLIB_DEVICE_PSOC6ABLE2) && (curDeviceRevision > SYSPM_DEVICE_PSOC6ABLE2_REV_0B)) ||
                                                       (curDevice != CY_SYSLIB_DEVICE_PSOC6ABLE2))
    {
        uint32_t syscallCode;
        IPC_STRUCT_Type *ipcSyscallBase = Cy_IPC_Drv_GetIpcBaseAddress(CY_IPC_CHAN_SYSCALL);
        
        /* Set required syscall code */
        if (curDevice == CY_SYSLIB_DEVICE_PSOC6ABLE2)
        {
            syscallCode = (CY_SYSPM_FLASH_VOLTAGE_BIT_LP != value) ? 
            FLASH_VOLTAGE_BIT_ULP_PSOC6ABLE2_OPCODE : FLASH_VOLTAGE_BIT_LP_PSOC6ABLE2_OPCODE;
        }
        else
        {
            syscallCode = (CY_SYSPM_FLASH_VOLTAGE_BIT_LP != value) ? 
            FLASH_VOLTAGE_BIT_ULP_OPCODE : FLASH_VOLTAGE_BIT_LP_OPCODE;
        }

        /* Tries to acquire the IPC structure and pass the arguments to SROM API */
        if (Cy_IPC_Drv_SendMsgWord(ipcSyscallBase, SYSPM_IPC_NOTIFY_STRUCT0, syscallCode) == CY_IPC_DRV_SUCCESS)
        {
            /* Checks whether the IPC structure is not locked */
            while (Cy_IPC_Drv_IsLockAcquired(ipcSyscallBase))
            {
                /* Polls whether the IPC is released */
            }
    
            /* Check the return status of a syscall */
            uint32_t syscallStatus = Cy_IPC_Drv_ReadDataValue(ipcSyscallBase);
    
            if (SYSCALL_STATUS_SUCCESS == (syscallStatus & SYSCALL_STATUS_MASK))
            {
                retVal = CY_SYSPM_SUCCESS;
            }
        }
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_SysPm_SaveRegisters
****************************************************************************//**
*
* Saves non-retained UDB registers before system entering system Deep Sleep.
* Must be called if programmable logic or function are implemented in the UDB 
* array. 
* 
* \warning
* Only one CPU on dual CPU devices should call this function. If both CPUs call
* this function the UDB state restored may be inconsistent with the expected 
* state when restored.
*
* Cypress ID #280370.
*
* \param regs
* The structure where the registers are saved.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SaveRestoreRegisters
*
*******************************************************************************/
void Cy_SysPm_SaveRegisters(cy_stc_syspm_backup_regs_t *regs)
{
    CY_ASSERT_L1(NULL != regs);
    
    /* Save the registers before Deep Sleep */
    regs->CY_SYSPM_UDB_UDBIF_BANK_CTL_REG = UDB_UDBIF_BANK_CTL;

    regs->CY_SYSPM_UDB_BCTL_MDCLK_EN_REG = UDB_BCTL_MDCLK_EN;
    regs->CY_SYSPM_UDB_BCTL_MBCLK_EN_REG = UDB_BCTL_MBCLK_EN;
    regs->CY_SYSPM_UDB_BCTL_BOTSEL_L_REG = UDB_BCTL_BOTSEL_L;
    regs->CY_SYSPM_UDB_BCTL_BOTSEL_U_REG = UDB_BCTL_BOTSEL_U;
    regs->CY_SYSPM_UDB_BCTL_QCLK_EN0_REG = UDB_BCTL_QCLK_EN_0;
    regs->CY_SYSPM_UDB_BCTL_QCLK_EN1_REG = UDB_BCTL_QCLK_EN_1;
    regs->CY_SYSPM_UDB_BCTL_QCLK_EN2_REG = UDB_BCTL_QCLK_EN_2;
}


/*******************************************************************************
* Function Name: Cy_SysPm_RestoreRegisters
****************************************************************************//**
*
* Restores non-retained UDB registers before system entering system Deep Sleep.
* Must be called if programmable logic or function are implemented in the UDB 
* array. 
* 
* \warning
* Only one CPU on dual CPU devices should call this function. If both CPUs call
* this function the UDB state restored may be inconsistent with the expected 
* state when restored.
*
* Cypress ID #280370.
*
* \param regs
* The structure with data stored (using Cy_SysPm_SaveRegisters()) into the 
* required non-retained registers after Deep Sleep.
*
* \funcusage
* \snippet syspm/4.0/snippet/main.c snippet_Cy_SysPm_SaveRestoreRegisters
*
*******************************************************************************/
void Cy_SysPm_RestoreRegisters(cy_stc_syspm_backup_regs_t const *regs)
{
    CY_ASSERT_L1(NULL != regs);
    
    /* Restore the registers after Deep Sleep */
    UDB_BCTL_MDCLK_EN  = regs->CY_SYSPM_UDB_BCTL_MDCLK_EN_REG;
    UDB_BCTL_MBCLK_EN  = regs->CY_SYSPM_UDB_BCTL_MBCLK_EN_REG;
    UDB_BCTL_BOTSEL_L  = regs->CY_SYSPM_UDB_BCTL_BOTSEL_L_REG;
    UDB_BCTL_BOTSEL_U  = regs->CY_SYSPM_UDB_BCTL_BOTSEL_U_REG;
    UDB_BCTL_QCLK_EN_0 = regs->CY_SYSPM_UDB_BCTL_QCLK_EN0_REG;
    UDB_BCTL_QCLK_EN_1 = regs->CY_SYSPM_UDB_BCTL_QCLK_EN1_REG;
    UDB_BCTL_QCLK_EN_2 = regs->CY_SYSPM_UDB_BCTL_QCLK_EN2_REG;

    UDB_UDBIF_BANK_CTL = regs->CY_SYSPM_UDB_UDBIF_BANK_CTL_REG;
}


/*******************************************************************************
* Function Name: EnterDeepSleepRam
****************************************************************************//**
*
* The internal function that prepares the system for Deep Sleep and 
* restores the system after a wakeup from Deep Sleep.
*
* \param waitFor
* Selects wait for action. See \ref cy_en_syspm_waitfor_t.
*
*******************************************************************************/
#if defined (__ICCARM__)
    #pragma diag_suppress=Ta023
    __ramfunc
#else
    CY_SECTION(".cy_ramfunc") CY_NOINLINE
#endif
static void EnterDeepSleepRam(cy_en_syspm_waitfor_t waitFor)
{
    /* Store the address of the Deep Sleep indicator into the RAM */
    volatile uint32_t *delayDoneFlag = &FLASHC_BIST_DATA_0;

#ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE
    if (Cy_SysLib_GetDeviceRevision() == CY_SYSLIB_DEVICE_REV_0A)
    {
        /* Acquire the IPC to prevent changing of the shared resources at the same time */
        while(0U == _FLD2VAL(IPC_STRUCT_ACQUIRE_SUCCESS, REG_IPC_STRUCT_ACQUIRE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT))))
        {
            /* Wait until the IPC structure is released by another CPU */
        }

        /* Set the flag that the current CPU entered Deep Sleep */
        REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) |= CUR_CORE_DP_MASK;

        /* Change the slow and fast clock dividers only under the condition that 
        *  the other CPU is already in Deep Sleep. Cypress ID #284516
        */
        if (0U != (REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) & OTHER_CORE_DP_MASK))
        {
            /* Get the divider values of the slow and high clocks and store them into 
            *  the IPC data register
            */
            REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 
            (REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) & ((uint32_t) ~(SYSPM_CLK_DIV_MASK))) |
            (((uint32_t)(_FLD2VAL(CPUSS_CM0_CLOCK_CTL_SLOW_INT_DIV, CPUSS_CM0_CLOCK_CTL) << SYSPM_SLOW_CLK_DIV_Pos)) |
             ((uint32_t)(_FLD2VAL(CPUSS_CM4_CLOCK_CTL_FAST_INT_DIV, CPUSS_CM4_CLOCK_CTL) << SYSPM_FAST_CLK_DIV_Pos)));

            /* Increase the clock divider for the slow and fast clocks to SYSPM_CLK_DIVIDER */
            CPUSS_CM0_CLOCK_CTL = 
            _CLR_SET_FLD32U(CPUSS_CM0_CLOCK_CTL, CPUSS_CM0_CLOCK_CTL_SLOW_INT_DIV, SYSPM_CLK_DIVIDER);

            CPUSS_CM4_CLOCK_CTL = 
            _CLR_SET_FLD32U(CPUSS_CM4_CLOCK_CTL, CPUSS_CM4_CLOCK_CTL_FAST_INT_DIV, SYSPM_CLK_DIVIDER);

            /* Read the divider value to make sure it is set */
            (void) CPUSS_CM0_CLOCK_CTL;
            (void) CPUSS_CM4_CLOCK_CTL;
        }

        /* Release the IPC */
        REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 0U;

        /* Read this register to make sure it is settled */
        (void) REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT));
    }
#endif /* #ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE */

#if (CY_CPU_CORTEX_M4)

    /* Store the address of the CM4 power status register */
    volatile uint32_t *cpussCm4PwrCtlAddr = &CPUSS_CM4_PWR_CTL;

    /* Repeat the WFI/WFE instruction if a wake up was not intended. 
    *  Cypress ID #272909
    */
    do
    {
#endif /* (CY_CPU_CORTEX_M4) */

        /* The CPU enters Deep Sleep mode upon execution of WFI/WFE */
        SCB_SCR |= SCB_SCR_SLEEPDEEP_Msk;

        if(waitFor != CY_SYSPM_WAIT_FOR_EVENT)
        {
            __WFI();
        }
        else
        {
            __WFE();

        #if (CY_CPU_CORTEX_M4)
            /* Call the WFE instruction twice to clear the Event register 
            *  of the CM4 CPU. Cypress ID #279077
            */
            if(wasEventSent)
            {
                __WFE();
            }
            wasEventSent = true;
        #endif /* (CY_CPU_CORTEX_M4) */
        }

#if (CY_CPU_CORTEX_M4)
    } while (_FLD2VAL(CPUSS_CM4_PWR_CTL_PWR_MODE, (*cpussCm4PwrCtlAddr)) == CM4_PWR_STS_RETAINED);
#endif /* (CY_CPU_CORTEX_M4) */

    /* Acquire the IPC to prevent changing of the shared resources at the same time */
    while(0U == _FLD2VAL(IPC_STRUCT_ACQUIRE_SUCCESS, REG_IPC_STRUCT_ACQUIRE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT))))
    {
        /* Wait until the IPC structure is released by another CPU */
    }

#ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE
    if (Cy_SysLib_GetDeviceRevision() == CY_SYSLIB_DEVICE_REV_0A)
    {
        /* Read and change the slow and fast clock dividers only under the condition 
        * that the other CPU is already in Deep Sleep. Cypress ID #284516
        */
        if(0U != (REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) & OTHER_CORE_DP_MASK))
        {
            /* Restore the clock dividers for the slow and fast clocks */
            CPUSS_CM0_CLOCK_CTL = 
            _CLR_SET_FLD32U(CPUSS_CM0_CLOCK_CTL, CPUSS_CM0_CLOCK_CTL_SLOW_INT_DIV, 
                           (_FLD2VAL(SYSPM_SLOW_CLK_DIV, REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)))));

            CPUSS_CM4_CLOCK_CTL = 
            _CLR_SET_FLD32U(CPUSS_CM4_CLOCK_CTL, CPUSS_CM4_CLOCK_CTL_FAST_INT_DIV, 
                           (_FLD2VAL(SYSPM_FAST_CLK_DIV, REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)))));
        }

        /* Indicate that the current CPU is out of Deep Sleep */
        REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) &= ((uint32_t) ~CUR_CORE_DP_MASK);
    }
    else
#endif /* #ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE */
    {
        /* Set 10 uS delay only under condition that the FLASHC_BIST_DATA[0] is 
        *  cleared. Cypress ID #288510
        */
        if (*delayDoneFlag == NEED_DELAY)
        {
            uint32_t ddftSlowCtl;
            uint32_t clkOutputSlow;
            uint32_t ddftFastCtl;

            /* Save timer configuration */
            ddftSlowCtl   = SRSS_TST_DDFT_SLOW_CTL_REG;
            clkOutputSlow = SRSS_CLK_OUTPUT_SLOW;
            ddftFastCtl   = SRSS_TST_DDFT_FAST_CTL_REG;

            /* Configure the counter to be sourced by IMO */
            SRSS_TST_DDFT_SLOW_CTL_REG = SRSS_TST_DDFT_SLOW_CTL_MASK;
            SRSS_CLK_OUTPUT_SLOW       = CLK_OUTPUT_SLOW_MASK;
            SRSS_TST_DDFT_FAST_CTL_REG = TST_DDFT_FAST_CTL_MASK;

            /* Load the down-counter to count the 10 us */
            SRSS_CLK_CAL_CNT1 = IMO_10US_DELAY;

            while (0U == (SRSS_CLK_CAL_CNT1 & SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE_Msk))
            {
                /* Wait until the counter stops counting */
            }

            /* Indicate that delay was done */
            *delayDoneFlag = DELAY_DONE;
            
            /* Restore timer configuration */
            SRSS_TST_DDFT_SLOW_CTL_REG = ddftSlowCtl;
            SRSS_CLK_OUTPUT_SLOW       = clkOutputSlow;
            SRSS_TST_DDFT_FAST_CTL_REG = ddftFastCtl;
        }
    }

    /* Release the IPC */
    REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 0U;
}
#if defined (__ICCARM__)
    #pragma diag_default=Ta023
#endif


/*******************************************************************************
* Function Name: SetReadMarginTrimUlp
****************************************************************************//**
*
* This is the internal function that updates the read-margin trim values for the
* RAM and ROM. The trim update is done during transition of regulator voltage 
* from higher to a lower one.
*
*******************************************************************************/
static void SetReadMarginTrimUlp(void)
{
    /* Update read-write margin value for the ULP mode. Cypress ID#297292 */
    if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
    {
        CPUSS_TRIM_RAM_CTL = (CPUSS_TRIM_RAM_CTL & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RM_Msk)) |
                             (CPUSS_TRIM_RAM_ULP & CPUSS_TRIM_RAM_CTL_RM_Msk);

        CPUSS_TRIM_ROM_CTL = (CPUSS_TRIM_ROM_CTL & ((uint32_t) ~CPUSS_TRIM_ROM_CTL_RM_Msk)) |
                             (CPUSS_TRIM_ROM_ULP & CPUSS_TRIM_ROM_CTL_RM_Msk);
    }
    else
    {
        CPUSS_TRIM_RAM_CTL = (SFLASH_CPUSS_TRIM_RAM_CTL_HALF_ULP & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RA_MASK)) | 
                             (CPUSS_TRIM_RAM_CTL | CPUSS_TRIM_RAM_CTL_RA_MASK);

        CPUSS_TRIM_ROM_CTL = SFLASH_CPUSS_TRIM_ROM_CTL_HALF_ULP;
    }
}


/*******************************************************************************
* Function Name: SetReadMarginTrimLp
****************************************************************************//**
*
* The internal function that updates the read-margin trim values for the 
* RAM and ROM. The trim update is done during transition of regulator voltage 
* from a lower to a higher one.
*
*******************************************************************************/
static void SetReadMarginTrimLp(void)
{
    /* Update read-write margin value for the LP mode. Cypress ID#297292 */
    if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
    {
        CPUSS_TRIM_RAM_CTL = (CPUSS_TRIM_RAM_CTL & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RM_Msk)) |
                             (CPUSS_TRIM_RAM_LP & CPUSS_TRIM_RAM_CTL_RM_Msk);

        CPUSS_TRIM_ROM_CTL = (CPUSS_TRIM_ROM_CTL & ((uint32_t) ~CPUSS_TRIM_ROM_CTL_RM_Msk)) |
                             (CPUSS_TRIM_ROM_LP & CPUSS_TRIM_ROM_CTL_RM_Msk);
    }
    else
    {
        CPUSS_TRIM_RAM_CTL = (SFLASH_CPUSS_TRIM_ROM_CTL_LP & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RA_MASK)) | 
                             (CPUSS_TRIM_RAM_CTL | CPUSS_TRIM_RAM_CTL_RA_MASK);

        CPUSS_TRIM_ROM_CTL =  SFLASH_CPUSS_TRIM_ROM_CTL_LP;
    }
}


/*******************************************************************************
* Function Name: SetWriteAssistTrimUlp
****************************************************************************//**
*
* The internal function that updates the write assistant trim value for the 
* RAM. The trim update is done during transition of regulator voltage 
* from higher to a lower.
*
*******************************************************************************/
static void SetWriteAssistTrimUlp(void)
{
    /* Update write assist value for the LP mode. Cypress ID#297292 */
    if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
    {
        CPUSS_TRIM_RAM_CTL = (CPUSS_TRIM_RAM_CTL & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_WA_Msk)) |
                             (CPUSS_TRIM_RAM_ULP & CPUSS_TRIM_RAM_CTL_WA_Msk);
    }
    else
    {
        CPUSS_TRIM_RAM_CTL = (SFLASH_CPUSS_TRIM_ROM_CTL_ULP & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RA_MASK)) |
                             (CPUSS_TRIM_RAM_CTL | CPUSS_TRIM_RAM_CTL_RA_MASK);
    }
}


/*******************************************************************************
* Function Name: SetWriteAssistTrimLp
****************************************************************************//**
*
* The internal function that updates the write assistant trim value for the 
* RAM. The trim update is done during transition of regulator voltage 
* from lower to a higher one.
*
*******************************************************************************/
static void SetWriteAssistTrimLp(void)
{
    /* Update write assist value for the LP mode. Cypress ID#297292 */
    if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
    {
        CPUSS_TRIM_RAM_CTL = (CPUSS_TRIM_RAM_CTL & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_WA_Msk)) |
                             (CPUSS_TRIM_RAM_LP & CPUSS_TRIM_RAM_CTL_WA_Msk);
    }
    else
    {
        CPUSS_TRIM_RAM_CTL = (SFLASH_CPUSS_TRIM_ROM_CTL_HALF_LP & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RA_MASK)) |
                             (CPUSS_TRIM_RAM_CTL | CPUSS_TRIM_RAM_CTL_RA_MASK);

        CPUSS_TRIM_ROM_CTL = SFLASH_CPUSS_TRIM_ROM_CTL_HALF_LP;
    }
}


/*******************************************************************************
* Function Name: IsVoltageChangePossible
****************************************************************************//**
*
* The internal function that checks wherever it is possible to change the core 
* voltage. The voltage change is possible only when the protection context is 
* set to zero (PC = 0), or the device supports modifying registers via syscall.
*
*******************************************************************************/
static bool IsVoltageChangePossible(void)
{
    bool retVal = true;

    if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
    {
        uint32_t curProtContext = Cy_Prot_GetActivePC(ACTIVE_BUS_MASTER);

        retVal = ((Cy_SysLib_GetDeviceRevision() > SYSPM_DEVICE_PSOC6ABLE2_REV_0B) || (curProtContext == 0U));
    }

    return retVal;
}


/* [] END OF FILE */
