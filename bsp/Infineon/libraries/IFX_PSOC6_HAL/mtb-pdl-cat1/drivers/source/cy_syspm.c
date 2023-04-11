/***************************************************************************//**
* \file cy_syspm.c
* \version 5.91
*
* This driver provides the source code for API power management.
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)

#include "cy_syspm.h"
#include "cy_ipc_drv.h"
#include "cy_prot.h"

#if defined (CY_DEVICE_SECURE)
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 17.2', 4, \
'Checked manually. All the recursive cycles are handled properly.');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.6', 3, \
'Checked manually. Assignment of Local to global variable does not create any issue.');
#endif

#if ((CY_CPU_CORTEX_M0P) && (defined(CY_DEVICE_SECURE)))
    #include "cy_pra_cfg.h"
#endif /* #if ((CY_CPU_CORTEX_M0P) && (defined(CY_DEVICE_SECURE))) */

/*******************************************************************************
*       Internal Functions
*******************************************************************************/
static void EnterDeepSleepRam(cy_en_syspm_waitfor_t waitFor);

#if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
static void SetReadMarginTrimUlp(void);
static void SetReadMarginTrimLp(void);
static void SetWriteAssistTrimUlp(void);
static void SetWriteAssistTrimLp(void);
static bool IsVoltageChangePossible(void);
#endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */


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
#endif /* #ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE */


#if (CY_CPU_CORTEX_M4)
    #define CUR_CORE_DP_MASK      (0x01UL << 28u)
    #define OTHER_CORE_DP_MASK    (0x02UL << 28u)
#else
    #define CUR_CORE_DP_MASK      (0x02UL << 28u)
    #define OTHER_CORE_DP_MASK    (0x01UL << 28u)
#endif

#define SYSPM_IPC_STRUCT_ADDR_MASK    (0x0FFFFFFFUL)
#define SYSPM_IPC_STRUCT_UDB_DP_MASK  (0x04UL << 28u)

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

#if ((CY_CPU_CORTEX_M0P) && (defined(CY_DEVICE_SECURE)))
    /* Define to indicate that a 10 us delay was done after exiting Deep Sleep */
    #define DELAY_DONE                 (1U)

    /* Register address which is used to indicate delay done event */
    #define DELAY_FLAG_REGISTER_ADDR   (&FLASHC_BIST_STATUS)
#else
    #define DELAY_DONE                 (0xAAAAAAAAU)
    #define DELAY_FLAG_REGISTER_ADDR   (&FLASHC_BIST_DATA_0)
#endif /* ((CY_CPU_CORTEX_M0P) && (defined(CY_DEVICE_SECURE))) */

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
#define ROM_ENTER_DEEP_SLEEP_ADDR         (*(uint32_t *) 0x00000D30UL)

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    #define PM_HIBERNATE_ENTER_HIBERNATE    (0UL)
    #define PM_HIBERNATE_IO_UNFREEZE        (1UL)
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

/* The define to call the ROM Cy_EnterDeepSleep() function.
* The ROM Cy_EnterDeepSleep() function prepares the system for the Deep Sleep
* and restores the system after wakeup from the Deep Sleep. */
typedef void (*cy_cb_syspm_deep_sleep_t)(cy_en_syspm_waitfor_t waitFor, bool *wasEventSent);

#define EnterDeepSleepSrom(waitFor, wasEventSent) \
       ((cy_cb_syspm_deep_sleep_t) ROM_ENTER_DEEP_SLEEP_ADDR)((waitFor), &(wasEventSent))

/* Mask for the RAM read assist bits */
#define CPUSS_TRIM_RAM_CTL_RA_MASK                   ((uint32_t) 0x3U << 8U)

/* Mask for the RAM write check bits */
#define CPUSS_TRIM_RAM_CTL_WC_MASK                   (0x3UL << 10U)

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
#define SET_MIN_CURRENT_MODE_DELAY_US        (1U)

/* The wait delay time that occurs before the active reference is settled.
*  Intermediate delay is used in transition into the normal regulator current
*  mode
*/
#define ACT_REF_SETTLE_DELAY_US              (8U)

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


/* The mask for low power modes the power circuits (POR/BOD, Bandgap reference,
*  Reference buffer, Current reference) when active core regulator is LDO
*/
#define PWR_CIRCUITS_SET_LPMODE_LDO_MASK        (SRSS_PWR_CTL_LINREG_LPMODE_Msk | PWR_CIRCUITS_SET_LPMODE_BUCK_MASK)

/* The mask for low power modes the power circuits (POR/BOD, Bandgap reference,
*  Reference buffer, Current reference) when active core regulator is Buck
*/
#define PWR_CIRCUITS_SET_LPMODE_BUCK_MASK       (SRSS_PWR_CTL_PORBOD_LPMODE_Msk |\
                                                 SRSS_PWR_CTL_BGREF_LPMODE_Msk |\
                                                 SRSS_PWR_CTL_VREFBUF_LPMODE_Msk |\
                                                 SRSS_PWR_CTL_IREF_LPMODE_Msk)

/* The wakeup holdoff for the system regulator minimum current mode.
   Cypress ID DRV2123
*/
#define SRSS_PWR_TRIM_WAKE_LP                   (0x50U)


/*******************************************************************************
*       Internal Variables
*******************************************************************************/

/* Array of the callback roots */
static cy_stc_syspm_callback_t* pmCallbackRoot[CALLBACK_ROOT_NR] = {NULL, NULL, NULL, NULL, NULL};

/* The array of the pointers to failed callback */
static cy_stc_syspm_callback_t* failedCallback[CALLBACK_ROOT_NR] = {NULL, NULL, NULL, NULL, NULL};

#if (CY_CPU_CORTEX_M4)
    /* Global boolean variable used to clear the  Event Register of the CM4 core */
    static bool wasEventSent = false;
#endif /* (CY_CPU_CORTEX_M4) */


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

#if (__CORTEX_M == 0) || (defined (__CM0P_PRESENT) && (__CM0P_PRESENT == 1))
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
#endif /* (__CORTEX_M == 0) || (defined (__CM0P_PRESENT) && (__CM0P_PRESENT == 1)) */

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
            if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
            {
                /* For the CM4 CPU, the WFE instruction is called twice.
                *  The second WFE call clears the Event Register of CM4 CPU.
                *  Cypress ID #279077.
                */
                if(wasEventSent)
                {
                    __WFE();
                }

                wasEventSent = true;
            }
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


cy_en_syspm_status_t Cy_SysPm_CpuEnterDeepSleep(cy_en_syspm_waitfor_t waitFor)
{
    /* Structure for registers that should retain while Deep Sleep mode */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    static cy_stc_syspm_backup_regs_t bkpRegs;
    uint8_t deviceRev = Cy_SysLib_GetDeviceRevision();
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    uint32_t interruptState;
    uint32_t cbDeepSleepRootIdx = (uint32_t) CY_SYSPM_DEEPSLEEP;
    uint32_t ddftStructData = 0UL;
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

        /* Preparation for the System Deep Sleep mode */

#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        /* Acquire the IPC to prevent changing of the shared resources at the same time */
        while (0U == _FLD2VAL(IPC_STRUCT_ACQUIRE_SUCCESS, REG_IPC_STRUCT_ACQUIRE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT))))
        {
            /* Wait until the IPC structure is released by another CPU */
        }

        ddftStructData = REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT));

        if (0U != (ddftStructData & OTHER_CORE_DP_MASK))
        {
            ddftStructData &= ~SYSPM_IPC_STRUCT_ADDR_MASK;

            Cy_SysPm_SaveRegisters(&bkpRegs);

        #ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE
            if (deviceRev == CY_SYSLIB_DEVICE_REV_0A)
            {
                /* Increase the clock divider for the slow and fast clocks to SYSPM_CLK_DIVIDER */
                CPUSS_CM0_CLOCK_CTL =
                _CLR_SET_FLD32U(CPUSS_CM0_CLOCK_CTL, CPUSS_CM0_CLOCK_CTL_SLOW_INT_DIV, SYSPM_CLK_DIVIDER);

                CPUSS_CM4_CLOCK_CTL =
                _CLR_SET_FLD32U(CPUSS_CM4_CLOCK_CTL, CPUSS_CM4_CLOCK_CTL_FAST_INT_DIV, SYSPM_CLK_DIVIDER);
            }
            else
        #endif /* #ifndef CY_PSOC6ABLE2_REV_0A_SUPPORT_DISABLE */
            {
                /* Set the clock divider equal to 2 for the slow and fast clocks */
                CPUSS_CM0_CLOCK_CTL =
                _CLR_SET_FLD32U(CPUSS_CM0_CLOCK_CTL, CPUSS_CM0_CLOCK_CTL_SLOW_INT_DIV, 1);

                CPUSS_CM4_CLOCK_CTL =
                _CLR_SET_FLD32U(CPUSS_CM4_CLOCK_CTL, CPUSS_CM4_CLOCK_CTL_FAST_INT_DIV, 1);
            }

            ddftStructData |= (uint32_t) &bkpRegs;
        }

        ddftStructData |= CUR_CORE_DP_MASK;

        /* Update pointer to the latest saved structure */
        REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = ddftStructData;

        /* Release the IPC */
        REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 0U;

        /* Read the release value to make sure it is set */
        (void) REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT));

#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */

    #if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
        /* Trigger PRA access to CM0 core to allow CM0 to store configuration */
        CY_PRA_FUNCTION_CALL_VOID_VOID(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_PM_FUNC_CM4_DP_FLAG_SET);
    #endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

        /* Different device families and revisions have a different Deep Sleep entries */
        if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
        {
            /* The CPU enters Deep Sleep and wakes up in the RAM */
            EnterDeepSleepRam(waitFor);
        }
        else
        {

        #if (CY_CPU_CORTEX_M0P)
            /* Check if there is a pending syscall */
            CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 13.5', 1, \
            'Inspected manually, no side effect during functions call.');
            if (Cy_IPC_Drv_IsLockAcquired(Cy_IPC_Drv_GetIpcBaseAddress(CY_IPC_CHAN_SYSCALL_CM0)) ||
                Cy_IPC_Drv_IsLockAcquired(Cy_IPC_Drv_GetIpcBaseAddress(CY_IPC_CHAN_SYSCALL_CM4)))
            {
                CY_MISRA_BLOCK_END('MISRA C-2012 Rule 13.5');
                /* Do not put the CPU into Deep Sleep and return pending status */
                retVal = CY_SYSPM_SYSCALL_PENDING;
            }
            else
        #endif /* (CY_CPU_CORTEX_M0P) */
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
                    }

            #if (CY_CPU_CORTEX_M4)
                } while (_FLD2VAL(CPUSS_CM4_PWR_CTL_PWR_MODE, CPUSS_CM4_PWR_CTL) == CM4_PWR_STS_RETAINED);
        #if defined(CY_DEVICE_SECURE)
                CY_PRA_CM0_WAKEUP();
        #endif /* (CY_DEVICE_SECURE) */
            #endif /* (CY_CPU_CORTEX_M4) */
            }
        }

        /* Acquire the IPC to prevent changing of the shared resources at the same time */
        while (0U == _FLD2VAL(IPC_STRUCT_ACQUIRE_SUCCESS, REG_IPC_STRUCT_ACQUIRE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT))))
        {
            /* Wait until the IPC structure is released by another CPU */
        }

        ddftStructData = REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT));

    /* Removed for the security devices as this part is done by CM0 only */
    #if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
        if (0U != (ddftStructData & OTHER_CORE_DP_MASK))
        {
            cy_stc_syspm_backup_regs_t *ptrRegs;

            ptrRegs = (cy_stc_syspm_backup_regs_t *) (SYSPM_IPC_STRUCT_ADDR_MASK & ddftStructData);

            /* Restore saved registers */
            Cy_SysPm_RestoreRegisters(ptrRegs);
        }
    #endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

        ddftStructData &= ~CUR_CORE_DP_MASK;

        /* Update pointer to the latest saved structure */
        REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = ddftStructData;

        /* Release the IPC */
        REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 0U;

        Cy_SysLib_ExitCriticalSection(interruptState);
    }

    if (retVal == CY_SYSPM_SUCCESS)
    {
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
        *  undo everything done in the callback with the CY_SYSPM_CHECK_READY
        *  parameter
        */
        if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_DEEPSLEEP, CY_SYSPM_CHECK_FAIL);
        }

        /* Rewrite return value to indicate fail */
        if (retVal != CY_SYSPM_SYSCALL_PENDING)
        {
            retVal = CY_SYSPM_FAIL;
        }
    }
    return retVal;
}


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

    #if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
        CY_PRA_FUNCTION_CALL_VOID_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY,
                                        CY_PRA_PM_FUNC_HIBERNATE,
                                        PM_HIBERNATE_ENTER_HIBERNATE);
    #else
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
    #endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

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


cy_en_syspm_status_t Cy_SysPm_SystemSetMinRegulatorCurrent(void)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_CANCELED;

#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_VOID(CY_PRA_MSG_TYPE_FUNC_POLICY,
                                                                    CY_PRA_PM_FUNC_SET_MIN_CURRENT);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    /* Check are the power circuits are ready to enter into regulator minimum
    *  current mode
    */
    if (0U != _FLD2VAL(SRSS_PWR_CTL_LPM_READY, SRSS_PWR_CTL))
    {
        if(Cy_SysPm_LdoIsEnabled())
        {
            /* Configure the minimum current mode for LDO regulator */
            SRSS_PWR_CTL |= PWR_CIRCUITS_SET_LPMODE_LDO_MASK;

            /* Extend wakeup time for LDO 1.1 V */
            if (Cy_SysPm_LdoGetVoltage() == CY_SYSPM_LDO_VOLTAGE_1_1V)
            {
                /* Cypress ID DRV2123 */
                SRSS_PWR_TRIM_WAKE_CTL = SRSS_PWR_TRIM_WAKE_LP;
            }
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
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */

    return retVal;
}


cy_en_syspm_status_t Cy_SysPm_SystemSetNormalRegulatorCurrent(void)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_TIMEOUT;

#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_VOID(CY_PRA_MSG_TYPE_FUNC_POLICY,
                                                                    CY_PRA_PM_FUNC_SET_NORMAL_CURRENT);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    uint32_t timeOut = WAIT_DELAY_TRYES;

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

        /* Restore original wakeup time in Normal for LDO 1.1 V */
        if (Cy_SysPm_LdoIsEnabled() && (Cy_SysPm_LdoGetVoltage() == CY_SYSPM_LDO_VOLTAGE_1_1V))
        {
            /* Cypress ID DRV2123 */
            SRSS_PWR_TRIM_WAKE_CTL = SFLASH_PWR_TRIM_WAKE_CTL;
        }

        retVal= CY_SYSPM_SUCCESS;
    }
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */

    return retVal;
}


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

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    CY_PRA_REG32_SET(CY_PRA_INDX_SRSS_PWR_HIBERNATE, (SRSS_PWR_HIBERNATE & (uint32_t) ~polarityMask) | wakeupSource);
#else
    SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & (uint32_t) ~polarityMask) | wakeupSource;
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;
}


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

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    CY_PRA_REG32_SET(CY_PRA_INDX_SRSS_PWR_HIBERNATE, (SRSS_PWR_HIBERNATE & (uint32_t) ~clearWakeupSourceMask));
#else
    SRSS_PWR_HIBERNATE &= (uint32_t) ~clearWakeupSourceMask;
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;
}


cy_en_syspm_status_t Cy_SysPm_BuckEnable(cy_en_syspm_buck_voltage1_t voltage)
{
    CY_ASSERT_L3(CY_SYSPM_IS_BUCK_VOLTAGE1_VALID(voltage));

    cy_en_syspm_status_t retVal = CY_SYSPM_INVALID_STATE;

#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY,
                                                                     CY_PRA_PM_FUNC_BUCK_ENABLE,
                                                                     voltage);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))

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

            /* Remove additional wakeup delay from Deep Sleep for LDO.
            *  Cypress ID #290172
            */
            SRSS_PWR_TRIM_WAKE_CTL = 0UL;
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
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */

    return retVal;
}


cy_en_syspm_status_t Cy_SysPm_BuckSetVoltage1(cy_en_syspm_buck_voltage1_t voltage)
{
    CY_ASSERT_L3(CY_SYSPM_IS_BUCK_VOLTAGE1_VALID(voltage));

    cy_en_syspm_status_t retVal = CY_SYSPM_INVALID_STATE;

#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY,
                                                                     CY_PRA_PM_FUNC_BUCK_ENABLE,
                                                                     voltage);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))

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
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */

    return retVal;
}


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


void Cy_SysPm_BuckEnableVoltage2(void)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    CY_PRA_FUNCTION_CALL_VOID_VOID(CY_PRA_MSG_TYPE_SECURE_ONLY,
                                   CY_PRA_PM_FUNC_BUCK_ENABLE_VOLTAGE2);
#else
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
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
}


void Cy_SysPm_BuckSetVoltage2(cy_en_syspm_buck_voltage2_t voltage, bool waitToSettle)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    cy_stc_pra_voltage2_t voltageSettings;
    voltageSettings.praVoltage = voltage;
    voltageSettings.praWaitToSettle = waitToSettle;

    CY_PRA_FUNCTION_CALL_VOID_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY,
                                    CY_PRA_PM_FUNC_BUCK_SET_VOLTAGE2,
                                    &voltageSettings);
#else
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
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
}


cy_en_syspm_status_t Cy_SysPm_LdoSetVoltage(cy_en_syspm_ldo_voltage_t voltage)
{
    CY_ASSERT_L3(CY_SYSPM_IS_LDO_VOLTAGE_VALID(voltage));

    cy_en_syspm_status_t retVal = CY_SYSPM_INVALID_STATE;

#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY,
                                                                     CY_PRA_PM_FUNC_LDO_SET_VOLTAGE,
                                                                     voltage);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
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
            *  for 0.9 V LDO. Cypress ID #290172
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
            if (Cy_SysPm_SystemIsMinRegulatorCurrentSet())
            {
                /* Cypress ID DRV2123 */
                SRSS_PWR_TRIM_WAKE_CTL = SRSS_PWR_TRIM_WAKE_LP;
            }
            else
            {
                SRSS_PWR_TRIM_WAKE_CTL = SFLASH_PWR_TRIM_WAKE_CTL;
            }

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
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */

    return retVal;
}


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
        #if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
            /* Disable the LDO, Deep Sleep, nWell, and Retention regulators */
            SRSS_PWR_CTL |= (_VAL2FLD(SRSS_PWR_CTL_DPSLP_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_RET_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_NWELL_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL_LINREG_DIS, 1U));

            retVal = CY_SYSPM_SUCCESS;
        #endif /* !(CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
        }
        break;

        default:
            retVal = CY_SYSPM_FAIL;
        break;
    }

    return retVal;
}


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


bool Cy_SysPm_RegisterCallback(cy_stc_syspm_callback_t* handler)
{
    bool retVal = false;

    /* Verify the input parameters. */
    if ((handler != NULL) && (handler->callbackParams != NULL) && (handler->callback != NULL))
    {
        uint32_t callbackRootIdx = (uint32_t) handler->type;

        /* If the callback list is not empty. */
        if (pmCallbackRoot[callbackRootIdx] != NULL)
        {
            cy_stc_syspm_callback_t* curCallback = pmCallbackRoot[callbackRootIdx];
            cy_stc_syspm_callback_t* insertPos  = curCallback;

            /* Find the callback after which the new callback is to be
             * inserted. Ensure the given callback has not been registered.
             */
            while ((NULL != curCallback->nextItm) && (curCallback != handler))
            {
                curCallback = curCallback->nextItm;
                /* Callbacks with the same order value are stored in the order
                 * they are registered.
                 */
                if (curCallback->order <= handler->order)
                {
                    insertPos = curCallback;
                }
            }
            /* If the callback has not been registered. */
            if (curCallback != handler)
            {
                /* If the callback is to be inserted at the beginning of the list. */
                if ((insertPos->prevItm == NULL) && (handler->order < insertPos->order))
                {
                    handler->nextItm = insertPos;
                    handler->prevItm = NULL;
                    handler->nextItm->prevItm = handler;
                    pmCallbackRoot[callbackRootIdx] = handler;
                }
                else
                {
                    handler->nextItm = insertPos->nextItm;
                    handler->prevItm = insertPos;

                    /* If the callback is not inserted at the end of the list. */
                    if (handler->nextItm != NULL)
                    {
                        handler->nextItm->prevItm = handler;
                    }
                    insertPos->nextItm = handler;
                }
                retVal = true;
            }
        }
        else
        {
            /* The callback list is empty. */
            pmCallbackRoot[callbackRootIdx] = handler;
            handler->nextItm = NULL;
            handler->prevItm = NULL;
            retVal = true;
        }
    }
    return retVal;
}


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

        if (mode == CY_SYSPM_CHECK_READY)
        {
            /* Update the pointer to  the failed callback with the result of the callback execution.
            *  If the callback fails, the value of the pointer will be updated
            *  with the address of the callback which returned CY_SYSPM_FAIL, else,
            *  it will be updated with NULL.
            */
            if(retVal == CY_SYSPM_FAIL)
            {
                failedCallback[(uint32_t) type] = lastExecutedCallback;
            }
            else
            {
                failedCallback[(uint32_t) type] = NULL;
            }
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


cy_stc_syspm_callback_t* Cy_SysPm_GetFailedCallback(cy_en_syspm_callback_type_t type)
{
    return failedCallback[(uint32_t) type];
}


void Cy_SysPm_IoUnfreeze(void)
{
    uint32_t interruptState;
    interruptState = Cy_SysLib_EnterCriticalSection();

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    CY_PRA_FUNCTION_CALL_VOID_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_PM_FUNC_HIBERNATE, PM_HIBERNATE_IO_UNFREEZE);
#else
    /* Preserve the last reset reason and wakeup polarity. Then, unfreeze I/O:
     * write PWR_HIBERNATE.FREEZE=0, .UNLOCK=0x3A, .HIBERANTE=0
     */
    SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & HIBERNATE_RETAIN_STATUS_MASK) | HIBERNATE_UNLOCK_VAL;

    /* Lock the Hibernate mode:
    * write PWR_HIBERNATE.HIBERNATE=0, UNLOCK=0x00, HIBERANTE=0
    */
    SRSS_PWR_HIBERNATE &= HIBERNATE_RETAIN_STATUS_MASK;
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;

    Cy_SysLib_ExitCriticalSection(interruptState);
}


cy_en_syspm_status_t Cy_SysPm_WriteVoltageBitForFlash(cy_en_syspm_flash_voltage_bit_t value)
{
    CY_ASSERT_L3(CY_SYSPM_IS_BIT_FOR_FLASH_VALID(value));

    cy_en_syspm_status_t retVal = CY_SYSPM_CANCELED;

#if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
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
#else
    (void)value;
#endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

    return retVal;
}


#if !((CY_CPU_CORTEX_M4) && (defined (CY_DEVICE_SECURE)))
void Cy_SysPm_SaveRegisters(cy_stc_syspm_backup_regs_t *regs)
{
    CY_ASSERT_L1(NULL != regs);

    /* Save the registers before Deep Sleep */
    regs->CY_SYSPM_CM0_CLOCK_CTL_REG = CPUSS_CM0_CLOCK_CTL;
    regs->CY_SYSPM_CM4_CLOCK_CTL_REG = CPUSS_CM4_CLOCK_CTL;

    if ((0U != cy_device->udbPresent) && (0UL != (PERI_GR_SL_CTL(MMIO_UDB_SLAVE_NR) & PERI_UDB_SLAVE_ENABLED)))
    {
        regs->CY_SYSPM_UDB_UDBIF_BANK_CTL_REG = UDB_UDBIF_BANK_CTL;

        regs->CY_SYSPM_UDB_BCTL_MDCLK_EN_REG = UDB_BCTL_MDCLK_EN;
        regs->CY_SYSPM_UDB_BCTL_MBCLK_EN_REG = UDB_BCTL_MBCLK_EN;
        regs->CY_SYSPM_UDB_BCTL_BOTSEL_L_REG = UDB_BCTL_BOTSEL_L;
        regs->CY_SYSPM_UDB_BCTL_BOTSEL_U_REG = UDB_BCTL_BOTSEL_U;
        regs->CY_SYSPM_UDB_BCTL_QCLK_EN0_REG = UDB_BCTL_QCLK_EN_0;
        regs->CY_SYSPM_UDB_BCTL_QCLK_EN1_REG = UDB_BCTL_QCLK_EN_1;
        regs->CY_SYSPM_UDB_BCTL_QCLK_EN2_REG = UDB_BCTL_QCLK_EN_2;
    }
}


void Cy_SysPm_RestoreRegisters(cy_stc_syspm_backup_regs_t const *regs)
{
    CY_ASSERT_L1(NULL != regs);

    /* Restore the registers after Deep Sleep */
    CPUSS_CM0_CLOCK_CTL = regs->CY_SYSPM_CM0_CLOCK_CTL_REG;
    CPUSS_CM4_CLOCK_CTL = regs->CY_SYSPM_CM4_CLOCK_CTL_REG;

    if ((0U != cy_device->udbPresent) && (0UL != (PERI_GR_SL_CTL(MMIO_UDB_SLAVE_NR) & PERI_UDB_SLAVE_ENABLED)))
    {
        UDB_BCTL_MDCLK_EN  = regs->CY_SYSPM_UDB_BCTL_MDCLK_EN_REG;
        UDB_BCTL_MBCLK_EN  = regs->CY_SYSPM_UDB_BCTL_MBCLK_EN_REG;
        UDB_BCTL_BOTSEL_L  = regs->CY_SYSPM_UDB_BCTL_BOTSEL_L_REG;
        UDB_BCTL_BOTSEL_U  = regs->CY_SYSPM_UDB_BCTL_BOTSEL_U_REG;
        UDB_BCTL_QCLK_EN_0 = regs->CY_SYSPM_UDB_BCTL_QCLK_EN0_REG;
        UDB_BCTL_QCLK_EN_1 = regs->CY_SYSPM_UDB_BCTL_QCLK_EN1_REG;
        UDB_BCTL_QCLK_EN_2 = regs->CY_SYSPM_UDB_BCTL_QCLK_EN2_REG;

        UDB_UDBIF_BANK_CTL = regs->CY_SYSPM_UDB_UDBIF_BANK_CTL_REG;
    }
}
#endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */


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
* \return
* - true - System Deep Sleep was occurred.
* - false - System Deep Sleep was not occurred.
*
*******************************************************************************/
CY_SECTION_RAMFUNC_BEGIN
#if !defined (__ICCARM__)
    CY_NOINLINE
#endif
static void EnterDeepSleepRam(cy_en_syspm_waitfor_t waitFor)
{
#if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))

    /* Store the address of the Deep Sleep indicator into the RAM */
    volatile uint32_t *delayDoneFlag = DELAY_FLAG_REGISTER_ADDR;
#endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

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

    #if defined(CY_DEVICE_SECURE)
        CY_PRA_CM0_WAKEUP();
    #endif /* defined(CY_DEVICE_SECURE) */
#endif /* (CY_CPU_CORTEX_M4) */

#if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    /* Set 10 uS delay only under condition that the FLASHC_BIST_DATA[0] is
    *  cleared. Cypress ID #288510
    */
    if (*delayDoneFlag == NEED_DELAY)
    {
        uint32_t ddftSlowCtl;
        uint32_t clkOutputSlow;
        uint32_t ddftFastCtl;

    #if defined(CY_DEVICE_SECURE)
        Cy_PRA_CloseSrssMain2();
    #endif /* defined(CY_DEVICE_SECURE) */

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

    #if defined(CY_DEVICE_SECURE)
        Cy_PRA_OpenSrssMain2();
    #endif /* defined(CY_DEVICE_SECURE) */
    }
#endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
}
CY_SECTION_RAMFUNC_END

cy_en_syspm_status_t Cy_SysPm_SetSRAMMacroPwrMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    cy_stc_pra_sram_power_mode_config_t pwrModeConfig;
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
    cy_en_syspm_status_t status = CY_SYSPM_BAD_PARAM;

    CY_ASSERT_L1( sramNum < CPUSS_SRAM_COUNT );

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    pwrModeConfig.sramNum = sramNum;
    pwrModeConfig.sramMacroNum = sramMacroNum;
    pwrModeConfig.sramPwrMode = sramPwrMode;

    status = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_PM_FUNC_SRAM_MACRO_PWR_MODE, &pwrModeConfig);

#else

    if(sramNum == CY_SYSPM_SRAM0_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum < CPUSS_RAMC0_MACRO_NR );
        if (sramMacroNum < CPUSS_RAMC0_MACRO_NR)
        {
            CPUSS_RAM0_PWR_CTL(sramMacroNum) = _VAL2FLD(CPUSS_V2_RAM0_PWR_MACRO_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                                _VAL2FLD(CPUSS_V2_RAM0_PWR_MACRO_CTL_PWR_MODE, sramPwrMode);
            status = CY_SYSPM_SUCCESS;
        }
    }
    else if(sramNum == CY_SYSPM_SRAM1_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC1_PRESENT );
        CY_ASSERT_L1( sramMacroNum == 0UL );

        CPUSS_RAM1_PWR_CTL = _VAL2FLD(CPUSS_V2_RAM1_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                    _VAL2FLD(CPUSS_V2_RAM1_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;
    }
    else if(sramNum == CY_SYSPM_SRAM2_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC2_PRESENT );
        CY_ASSERT_L1( sramMacroNum == 0UL );

        CPUSS_RAM2_PWR_CTL = _VAL2FLD(CPUSS_V2_RAM2_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                    _VAL2FLD(CPUSS_V2_RAM2_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;
    }
    else
    {
        /* Invalid SRAM Number */
    }
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
    return status;
}

cy_en_syspm_sram_pwr_mode_t Cy_SysPm_GetSRAMMacroPwrMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum)
{
    uint32_t retVal = (uint32_t)CY_SYSPM_SRAM_PWR_MODE_INVALID;

    CY_ASSERT_L1( sramNum < CPUSS_SRAM_COUNT );

    if(sramNum == CY_SYSPM_SRAM0_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum < CPUSS_RAMC0_MACRO_NR );
        if (sramMacroNum < CPUSS_RAMC0_MACRO_NR)
        {
            retVal = _FLD2VAL(CPUSS_V2_RAM0_PWR_MACRO_CTL_PWR_MODE, CPUSS_RAM0_PWR_CTL(sramMacroNum));
        }
    }
    else if(sramNum == CY_SYSPM_SRAM1_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum == 0UL );
        retVal = _FLD2VAL(CPUSS_V2_RAM1_PWR_CTL_PWR_MODE, CPUSS_RAM1_PWR_CTL);
    }
    else if(sramNum == CY_SYSPM_SRAM2_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum == 0UL );
        retVal = _FLD2VAL(CPUSS_V2_RAM2_PWR_CTL_PWR_MODE, CPUSS_RAM2_PWR_CTL);
    }
    else
    {
        /* Invalid SRAM Number */
    }
    return (cy_en_syspm_sram_pwr_mode_t)retVal;
}

cy_en_syspm_status_t Cy_SysPm_SetSRAMPwrMode(cy_en_syspm_sram_index_t sramNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    cy_stc_pra_sram_power_mode_config_t pwrModeConfig;
#else
    uint32 idx;
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
    cy_en_syspm_status_t status = CY_SYSPM_BAD_PARAM;
    CY_ASSERT_L1( sramNum < CPUSS_SRAM_COUNT );

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    pwrModeConfig.sramNum = sramNum;
    pwrModeConfig.sramPwrMode = sramPwrMode;

    status = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_PM_FUNC_SRAM_PWR_MODE, &pwrModeConfig);
#else
    if(sramNum == CY_SYSPM_SRAM0_MEMORY)
    {
        for(idx = 0UL; idx < CPUSS_RAMC0_MACRO_NR; idx++)
        {
            CPUSS_RAM0_PWR_CTL(idx) = _VAL2FLD(CPUSS_V2_RAM0_PWR_MACRO_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                        _VAL2FLD(CPUSS_V2_RAM0_PWR_MACRO_CTL_PWR_MODE, sramPwrMode);
        }
        status = CY_SYSPM_SUCCESS;
    }
    else if(sramNum == CY_SYSPM_SRAM1_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC1_PRESENT );
        CPUSS_RAM1_PWR_CTL = _VAL2FLD(CPUSS_V2_RAM1_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                        _VAL2FLD(CPUSS_V2_RAM1_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;

    }
    else if(sramNum == CY_SYSPM_SRAM2_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC2_PRESENT );
        CPUSS_RAM2_PWR_CTL = _VAL2FLD(CPUSS_V2_RAM2_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                        _VAL2FLD(CPUSS_V2_RAM2_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;

    }
    else
    {
        /* Invalid SRAM Number */
    }
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
    return status;
}

#if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
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
                             (CPUSS_TRIM_RAM_CTL & CPUSS_TRIM_RAM_CTL_RA_MASK);

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
        CPUSS_TRIM_RAM_CTL = (SFLASH_CPUSS_TRIM_RAM_CTL_LP & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RA_MASK)) |
                             (CPUSS_TRIM_RAM_CTL & CPUSS_TRIM_RAM_CTL_RA_MASK);

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
        CPUSS_TRIM_RAM_CTL = (SFLASH_CPUSS_TRIM_RAM_CTL_ULP & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RA_MASK)) |
                             (CPUSS_TRIM_RAM_CTL & CPUSS_TRIM_RAM_CTL_RA_MASK);
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
        CPUSS_TRIM_RAM_CTL = (SFLASH_CPUSS_TRIM_RAM_CTL_HALF_LP & ((uint32_t) ~CPUSS_TRIM_RAM_CTL_RA_MASK)) |
                             (CPUSS_TRIM_RAM_CTL & CPUSS_TRIM_RAM_CTL_RA_MASK);

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
    bool retVal = false;
    uint32_t trimRamCheckVal = (CPUSS_TRIM_RAM_CTL & CPUSS_TRIM_RAM_CTL_WC_MASK);


    if (Cy_SysLib_GetDevice() == CY_SYSLIB_DEVICE_PSOC6ABLE2)
    {
        uint32_t curProtContext = Cy_Prot_GetActivePC(ACTIVE_BUS_MASTER);

        retVal = ((Cy_SysLib_GetDeviceRevision() > SYSPM_DEVICE_PSOC6ABLE2_REV_0B) || (curProtContext == 0U));
    }
    else
    {
        CPUSS_TRIM_RAM_CTL &= ~CPUSS_TRIM_RAM_CTL_WC_MASK;
        CPUSS_TRIM_RAM_CTL |= ((~trimRamCheckVal) & CPUSS_TRIM_RAM_CTL_WC_MASK);

        retVal = (trimRamCheckVal != (CPUSS_TRIM_RAM_CTL & CPUSS_TRIM_RAM_CTL_WC_MASK));
    }

    return retVal;
}
#endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */



bool Cy_SysPm_Cm4IsActive(void)
{
    return ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM4_ACTIVE) != 0U);
}


bool Cy_SysPm_Cm4IsSleep(void)
{
    return ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM4_SLEEP) != 0U);
}


bool Cy_SysPm_Cm4IsDeepSleep(void)
{
    return ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM4_DEEPSLEEP) != 0U);
}

#if (__CORTEX_M == 0) || (defined (__CM0P_PRESENT) && (__CM0P_PRESENT == 1))
bool Cy_SysPm_Cm0IsActive(void)
{
    return ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM0_ACTIVE) != 0U);
}

bool Cy_SysPm_Cm0IsSleep(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM0_SLEEP) != 0U);
}


bool Cy_SysPm_Cm0IsDeepSleep(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM0_DEEPSLEEP) != 0U);
}
#endif /* (__CORTEX_M == 0) || (defined (__CM0P_PRESENT) && (__CM0P_PRESENT == 1)) */

bool Cy_SysPm_IsSystemLp(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_SYSTEM_LP) != 0U);
}


bool Cy_SysPm_IsSystemUlp(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_SYSTEM_ULP) != 0U);
}


void Cy_SysPm_CpuSendWakeupEvent(void)
{
    __SEV();
}


bool Cy_SysPm_SystemIsMinRegulatorCurrentSet(void)
{
    uint32_t regMask = Cy_SysPm_LdoIsEnabled() ? CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_LDO_MASK : CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_BUCK_MASK;

    return ((SRSS_PWR_CTL & regMask) == regMask);
}


bool Cy_SysPm_BuckIsEnabled(void)
{
    return (0U != _FLD2VAL(SRSS_PWR_BUCK_CTL_BUCK_EN, SRSS_PWR_BUCK_CTL));
}


cy_en_syspm_buck_voltage1_t Cy_SysPm_BuckGetVoltage1(void)
{
    uint32_t retVal;
    retVal = _FLD2VAL(SRSS_PWR_BUCK_CTL_BUCK_OUT1_SEL, SRSS_PWR_BUCK_CTL);

    return ((cy_en_syspm_buck_voltage1_t) retVal);
}


cy_en_syspm_buck_voltage2_t Cy_SysPm_BuckGetVoltage2(void)
{
    uint32_t retVal = 0UL;

    if (0U != cy_device->sysPmSimoPresent)
    {
        retVal = _FLD2VAL(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_SEL, SRSS_PWR_BUCK_CTL2);
    }

    return ((cy_en_syspm_buck_voltage2_t) retVal);
}


void Cy_SysPm_BuckDisableVoltage2(void)
{
#if ((CY_CPU_CORTEX_M4) && (defined (CY_DEVICE_SECURE)))
    CY_PRA_FUNCTION_CALL_VOID_VOID(CY_PRA_MSG_TYPE_SECURE_ONLY,
                                   CY_PRA_PM_FUNC_BUCK_DISABLE_VOLTAGE2);
#else
    if (0U != cy_device->sysPmSimoPresent)
    {
        /* Disable the Vbuck2 output */
        SRSS_PWR_BUCK_CTL2 &= (uint32_t) ~_VAL2FLD(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_EN, 1U);
    }
#endif /* ((CY_CPU_CORTEX_M4) && (defined (CY_DEVICE_SECURE))) */
}


void Cy_SysPm_BuckSetVoltage2HwControl(bool hwControl)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    CY_PRA_FUNCTION_CALL_VOID_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY,
                                    CY_PRA_PM_FUNC_BUCK_VOLTAGE2_HW_CTRL,
                                    hwControl);
#else
    bool isBuckEnabled = Cy_SysPm_BuckIsEnabled();

    if ((0U != cy_device->sysPmSimoPresent) && isBuckEnabled)
    {
        if(hwControl)
        {
            SRSS_PWR_BUCK_CTL2 |= _VAL2FLD(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_HW_SEL, 1U);
        }
        else
        {
            SRSS_PWR_BUCK_CTL2 &= (uint32_t) ~_VAL2FLD(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_HW_SEL, 1U);
        }
    }
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
}


bool Cy_SysPm_BuckIsVoltage2HwControlled(void)
{
    bool retVal = false;

    if (0U != cy_device->sysPmSimoPresent)
    {
        retVal = (0U != _FLD2VAL(SRSS_PWR_BUCK_CTL2_BUCK_OUT2_HW_SEL, SRSS_PWR_BUCK_CTL2));
    }

    return retVal;
}


cy_en_syspm_ldo_voltage_t Cy_SysPm_LdoGetVoltage(void)
{
    uint32_t curVoltage;

    curVoltage = _FLD2VAL(SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM, SRSS_PWR_TRIM_PWRSYS_CTL);

    return ((curVoltage == (SFLASH_LDO_0P9V_TRIM)) ? CY_SYSPM_LDO_VOLTAGE_ULP : CY_SYSPM_LDO_VOLTAGE_LP);
}


bool Cy_SysPm_LdoIsEnabled(void)
{
    return ((0U != _FLD2VAL(SRSS_PWR_CTL_LINREG_DIS, SRSS_PWR_CTL)) ? false : true);
}


bool Cy_SysPm_IoIsFrozen(void)
{
    return (0U != _FLD2VAL(SRSS_PWR_HIBERNATE_FREEZE, SRSS_PWR_HIBERNATE));
}


void Cy_SysPm_PmicEnable(void)
{
    if (CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL =
        _VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY) |
        _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, 1U) |
        _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN, 1U);
    }
}


void Cy_SysPm_PmicDisable(cy_en_syspm_pmic_wakeup_polarity_t polarity)
{
    CY_ASSERT_L3(CY_SYSPM_IS_POLARITY_VALID(polarity));

    if (CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL =
        (_VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY) |
         _CLR_SET_FLD32U(BACKUP_PMIC_CTL, BACKUP_PMIC_CTL_POLARITY, (uint32_t) polarity)) &
        ((uint32_t) ~ _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN, 1U));
    }
}


void Cy_SysPm_PmicAlwaysEnable(void)
{
    BACKUP_PMIC_CTL |= _VAL2FLD(BACKUP_PMIC_CTL_PMIC_ALWAYSEN, 1U);
}


void Cy_SysPm_PmicEnableOutput(void)
{
    if (CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL |=
        _VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY) | _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, 1U);
    }
}


void Cy_SysPm_PmicDisableOutput(void)
{
    if (CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL =
        (BACKUP_PMIC_CTL | _VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY)) &
        ((uint32_t) ~ _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, 1U));
    }
}


void Cy_SysPm_PmicLock(void)
{
    BACKUP_PMIC_CTL = _CLR_SET_FLD32U(BACKUP_PMIC_CTL, BACKUP_PMIC_CTL_UNLOCK, 0U);
}


void Cy_SysPm_PmicUnlock(void)
{
    BACKUP_PMIC_CTL = _CLR_SET_FLD32U(BACKUP_PMIC_CTL, BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY);
}


bool Cy_SysPm_PmicIsEnabled(void)
{
    return (0U != _FLD2VAL(BACKUP_PMIC_CTL_PMIC_EN, BACKUP_PMIC_CTL));
}


bool Cy_SysPm_PmicIsOutputEnabled(void)
{
    return (0U != _FLD2VAL(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, BACKUP_PMIC_CTL));
}


bool Cy_SysPm_PmicIsLocked(void)
{
    return ((_FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL) == CY_SYSPM_PMIC_UNLOCK_KEY) ? false : true);
}


void Cy_SysPm_BackupSetSupply(cy_en_syspm_vddbackup_control_t vddBackControl)
{
    CY_ASSERT_L3(CY_SYSPM_IS_VDDBACKUP_VALID(vddBackControl));

    BACKUP_CTL = _CLR_SET_FLD32U((BACKUP_CTL), BACKUP_CTL_VDDBAK_CTL, (uint32_t) vddBackControl);
}


cy_en_syspm_vddbackup_control_t Cy_SysPm_BackupGetSupply(void)
{
    uint32_t retVal;
    retVal = _FLD2VAL(BACKUP_CTL_VDDBAK_CTL, BACKUP_CTL);

    return ((cy_en_syspm_vddbackup_control_t) retVal);
}


void Cy_SysPm_BackupEnableVoltageMeasurement(void)
{
    BACKUP_CTL |= BACKUP_CTL_VBACKUP_MEAS_Msk;
}


void Cy_SysPm_BackupDisableVoltageMeasurement(void)
{
    BACKUP_CTL &= ((uint32_t) ~BACKUP_CTL_VBACKUP_MEAS_Msk);
}


void Cy_SysPm_BackupSuperCapCharge(cy_en_syspm_sc_charge_key_t key)
{
    CY_ASSERT_L3(CY_SYSPM_IS_SC_CHARGE_KEY_VALID(key));

    if(key == CY_SYSPM_SC_CHARGE_ENABLE)
    {
        BACKUP_CTL = _CLR_SET_FLD32U((BACKUP_CTL), BACKUP_CTL_EN_CHARGE_KEY, (uint32_t) CY_SYSPM_SC_CHARGE_ENABLE);
    }
    else
    {
        BACKUP_CTL &= ((uint32_t) ~BACKUP_CTL_EN_CHARGE_KEY_Msk);
    }
}

#if defined (CY_DEVICE_SECURE)
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 17.2');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.6');
#endif

#endif
/* [] END OF FILE */
