/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/**
*   @file       Power_Ip_PMC.c
*   @version    5.0.0
*
*   @brief
*   @brief   POWER driver implementations.
*   @details POWER driver implementations.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif





/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_Private.h"
#include "Power_Ip_PMC.h"

#if (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API))
#include "Aec_Ip.h"
#endif

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_PMC_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE)
      #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
      #include "RegLockMacros.h"
    #endif /* (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_PMC_VENDOR_ID_C                      43
#define POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_PMC_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_PMC_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_PMC_SW_MAJOR_VERSION_C               5
#define POWER_IP_PMC_SW_MINOR_VERSION_C               0
#define POWER_IP_PMC_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API))
/* Check if Power_Ip_PMC.c file and Aec_Ip.h file are of the same vendor */
#if (POWER_IP_PMC_VENDOR_ID_C != AEC_IP_VENDOR_ID)
    #error "Power_Ip_PMC.c and Aec_Ip.h have different vendor ids"
#endif

/* Check if Power_Ip_PMC.c file and Aec_Ip.h file are of the same Autosar version */
#if ((POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION_C != AEC_IP_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PMC_AR_RELEASE_MINOR_VERSION_C != AEC_IP_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PMC_AR_RELEASE_REVISION_VERSION_C != AEC_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PMC.c and Aec_Ip.h are different"
#endif

/* Check if Power_Ip_PMC.c file and Aec_Ip.h file are of the same Software version */
#if ((POWER_IP_PMC_SW_MAJOR_VERSION_C != AEC_IP_SW_MAJOR_VERSION) || \
     (POWER_IP_PMC_SW_MINOR_VERSION_C != AEC_IP_SW_MINOR_VERSION) || \
     (POWER_IP_PMC_SW_PATCH_VERSION_C != AEC_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_PMC.c and Aec_Ip.h are different"
#endif
#endif

/* Check if Power_Ip_PMC.c file and Power_Ip_Private.h file are of the same vendor */
#if (POWER_IP_PMC_VENDOR_ID_C != POWER_IP_PRIVATE_VENDOR_ID)
    #error "Power_Ip_PMC.c and Power_Ip_Private.h have different vendor ids"
#endif

/* Check if Power_Ip_PMC.c file and Power_Ip_Private.h file are of the same Autosar version */
#if ((POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PMC_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PMC_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PMC.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip_PMC.c file and Power_Ip_Private.h file are of the same Software version */
#if ((POWER_IP_PMC_SW_MAJOR_VERSION_C != POWER_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (POWER_IP_PMC_SW_MINOR_VERSION_C != POWER_IP_PRIVATE_SW_MINOR_VERSION) || \
     (POWER_IP_PMC_SW_PATCH_VERSION_C != POWER_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_PMC.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip_PMC.c file and Power_Ip_PMC.h file are of the same vendor */
#if (POWER_IP_PMC_VENDOR_ID_C != POWER_IP_PMC_VENDOR_ID)
    #error "Power_Ip_PMC.c and Power_Ip_PMC.h have different vendor ids"
#endif

/* Check if Power_Ip_PMC.c file and Power_Ip_PMC.h file are of the same Autosar version */
#if ((POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PMC_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PMC_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PMC_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PMC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PMC.c and Power_Ip_PMC.h are different"
#endif

/* Check if Power_Ip_PMC.c file and Power_Ip_PMC.h file are of the same Software version */
#if ((POWER_IP_PMC_SW_MAJOR_VERSION_C != POWER_IP_PMC_SW_MAJOR_VERSION) || \
     (POWER_IP_PMC_SW_MINOR_VERSION_C != POWER_IP_PMC_SW_MINOR_VERSION) || \
     (POWER_IP_PMC_SW_PATCH_VERSION_C != POWER_IP_PMC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_PMC.c and Power_Ip_PMC.h are different"
#endif

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_PMC_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE)
        #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if Power_Ip_PMC.c file and RegLockMacros.h file are of the same Autosar version */
            #if ((POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
                (POWER_IP_PMC_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
                #error "AutoSar Version Numbers of Power_Ip_PMC.c and RegLockMacros.h are different"
            #endif
        #endif
    #endif /* (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL MACROS
==================================================================================================*/
#ifdef POWER_IP_LASTMILE_SUPPORT
  #if (STD_ON == POWER_IP_LASTMILE_SUPPORT)
      
#define FASTREC_TIME_WAIT           15U
#define NORMAL_TIME_WAIT            50U  
 
  #endif
#endif
/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#if (defined(POWER_IP_VOLTAGE_ERROR_ISR_USED))
  #if (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON)

#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

static volatile Power_Ip_PMC_StatusType Power_Ip_ePMCStatus = PMC_UNINIT;

#if (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API))
static volatile Power_Ip_PMC_StatusType Power_Ip_ePMCAeStatus = PMC_UNINIT;
#endif

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

  #endif
#endif
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_PMC_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE)
/**
* @brief            This function will enable writing in User mode by configuring REG_PROT
*/
void Power_Ip_PMC_SetUserAccessAllowed(void)
{
#if (defined(IP_PMC_BASE))
    SET_USER_ACCESS_ALLOWED(IP_PMC_BASE, PMC_PROT_MEM_U32);
#endif
}
    #endif
  #endif /* MCAL_PMC_REG_PROT_AVAILABLE */
#endif /* POWER_IP_ENABLE_USER_MODE_SUPPORT */


/**
* @brief            This function configure the Power Management Controller
* @details          The operating voltages are monitored by a set of on-chip supervisory circuits
*                   to ensure that this device works within the correct voltage range.
*
* @param[in]        ConfigPtr   Pointer to PMC configuration structure.
*
* @return           void
*
*/
void Power_Ip_PMC_PowerInit(const Power_Ip_PMC_ConfigType * ConfigPtr)
{
#if !(defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_009) || defined(POWER_IP_DERIVATIVE_008))
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint32 LvscValue;
    uint32 LastMileRegValue;
#endif
    uint32 ConfigValue = 0;
    (void)ConfigPtr;
    (void)ConfigValue;

    /* After the initial power ramp-up of the MCU, in PMC_LVSC register the POR flag
     * and the LVR flags are all set to 1. The GNG flags will have an arbitrary value.
     * Therefore, after the initial power ramp-up, all flags in PMC_LVSC must be
     * cleared by writing 0xFFFF_FFFF */

    if (PMC_LVSC_RAMP_UP_RESET_FLAGS_RWBITS_MASK == (IP_PMC->LVSC & PMC_LVSC_RAMP_UP_RESET_FLAGS_RWBITS_MASK))
    {
        IP_PMC->LVSC = PMC_LVSC_RWBITS_MASK;
    }
#if defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_009) || defined(POWER_IP_DERIVATIVE_008)
    /* Initialize the rest of the PMC module */
    ConfigValue = IP_PMC->CONFIG;
    ConfigValue &= (~(uint32)PMC_CONFIG_RWBITS_MASK);
    ConfigValue |= (ConfigPtr->ConfigRegister & (uint32)PMC_CONFIG_RWBITS_MASK);
    IP_PMC->CONFIG = ConfigValue;
#else
    /* Initialize the rest of the PMC module  */
    if (PMC_CONFIG_LAST_MILE_REG_ENABLE == (ConfigPtr->ConfigRegister & PMC_CONFIG_LMEN_MASK))
    {
        IP_PMC->CONFIG = (uint32)(ConfigPtr->ConfigRegister & (~(uint32)PMC_CONFIG_LMEN_MASK));

        /* If external BJT is using on the PCB board, the program needs to wait for the LVD15S bit to be cleared, then LMEN is enabled */
        if(PMC_CONFIG_LM_BASE_CONTROL_ENABLE == (ConfigPtr->ConfigRegister & PMC_CONFIG_LMBCTLEN_MASK))
        {
            Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

                LvscValue = IP_PMC->LVSC;
            } while ( (PMC_LVSC_V15_ABOVE_LV != (LvscValue & PMC_LVSC_LVD15S_MASK)) && (!TimeoutOccurred) );

            if (!TimeoutOccurred)
            {
                ConfigValue = IP_PMC->CONFIG;
                ConfigValue = (uint32)(ConfigValue & (~(uint32)PMC_CONFIG_LMEN_MASK));
                ConfigValue = (uint32)(ConfigValue | (uint32)(PMC_CONFIG_LAST_MILE_REG_ENABLE & PMC_CONFIG_LMEN_MASK));
                IP_PMC->CONFIG = ConfigValue;
            }
            else
            {
                Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
            }
        }
        else
        {
            ConfigValue = IP_PMC->CONFIG;
            ConfigValue = (uint32)(ConfigValue & (~(uint32)PMC_CONFIG_LMEN_MASK));
            ConfigValue = (uint32)(ConfigValue | (uint32)(PMC_CONFIG_LAST_MILE_REG_ENABLE & PMC_CONFIG_LMEN_MASK));
            IP_PMC->CONFIG = ConfigValue;
        }
    }
    else
    {
        IP_PMC->CONFIG = ConfigPtr->ConfigRegister;

        if (PMC_CONFIG_LAST_MILE_REG_AUTO_ENABLE == (ConfigPtr->ConfigRegister & PMC_CONFIG_LMAUTOEN_MASK))
        {
            Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

                LastMileRegValue = (IP_PMC->CONFIG & PMC_CONFIG_LMSTAT_MASK);
            } while ((PMC_CONFIG_LAST_MILE_REG_ON != LastMileRegValue) && (!TimeoutOccurred));

            if (TimeoutOccurred)
            {
                Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
            }
            else
            {
                /* do nothing */
            }
        }
    }
#endif
#if (defined(POWER_IP_VOLTAGE_ERROR_ISR_USED))
  #if (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON)
    /* make Status of PMC to initialized to check in the interrupt function */
    Power_Ip_ePMCStatus = PMC_INIT;
  #endif
#endif
#if (defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_009) || defined(POWER_IP_DERIVATIVE_008))
    ConfigValue = ConfigPtr->SMPSRegister;
    if (PMC_SMPSCONFIG_DITHEREN_MASK == (ConfigValue & PMC_SMPSCONFIG_DITHEREN_MASK))
    {
        /* Write 0 to bit DITHEREN */
        IP_PMC->SMPSCONFIG = 0U;
        /* Write new configurtion to SMPS */
        ConfigValue &= (~(uint32)PMC_SMPSCONFIG_DITHEREN_MASK);
        IP_PMC->SMPSCONFIG = ConfigValue;
        /* Set bit DITHEREN */
        ConfigValue |= PMC_SMPSCONFIG_DITHEREN_MASK;
        IP_PMC->SMPSCONFIG = ConfigValue;
    }
    else
    {
        IP_PMC->SMPSCONFIG = ConfigValue;
    }
#endif
}

#if (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API))
/**
* @brief            This function configure the Power Management Controller AE
* @details          The operating voltages are monitored by a set of on-chip supervisory circuits
*                   to ensure that this device works within the correct voltage range.
*
* @param[in]        ConfigPtr   Pointer to PMC configuration structure.
*
* @return           void
*
*/
void Power_Ip_PMC_AE_PowerInit(const Power_Ip_PMC_ConfigType * ConfigPtr)
{
    uint32 TmpAe;

    Aec_Ip_SpiRead((uint32)(&(IP_PMC_AE->CONFIG)),POWER_IP_DATAWIDTH_32,&TmpAe);
    TmpAe = (uint32)(TmpAe & (uint32)(~PMC_AE_CONFIG_RWBITS_MASK32));
    TmpAe = (uint32)(TmpAe | (uint32)(ConfigPtr->PmcAeConfig));
    Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->CONFIG)),POWER_IP_DATAWIDTH_32,TmpAe);

    Aec_Ip_SpiRead((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,&TmpAe);
    TmpAe = (uint32)(TmpAe & (uint32)(~(PMC_AE_MONITOR_RWBITS_MASK32 | PMC_AE_MONITOR_W1C_BITS_MASK32)));
    TmpAe = (uint32)(TmpAe | (uint32)(ConfigPtr->PmcAeMonitor));
    Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,TmpAe);

#if (defined(POWER_IP_VOLTAGE_ERROR_ISR_USED))
  #if (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON)
    /* make Status of PMC to initialized to check in the interrupt function */
    Power_Ip_ePMCAeStatus = PMC_INIT;
  #endif
#endif
}
#endif

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))
/**
* @brief            This function prepares the PMC module for Standby/Low Power entry.
* @details          If the Lastmile Regulator is enabled, clear both PMC_LVSC[LMEN]
*                   and PMC_LSVC[LMBCTLEN] simultaneously and notify the application
*                   of the regulator disablement. The LVD/HVD Interrupts are also
*                   disabled.
*
* @param[in]        void
*
* @return           void
*
*/
void Power_Ip_PMC_PrepareLowPowerEntry(void)
{
    uint32 TempValue = 0U;

    /* Disable LVD/HVD Interrupts */
    TempValue = IP_PMC->CONFIG;
    TempValue = (uint32)(TempValue & (uint32)( ~(PMC_CONFIG_LVDIE_MASK | PMC_CONFIG_HVDIE_MASK) ) );
    TempValue = (uint32)(TempValue | (uint32)(PMC_CONFIG_LVD_INTERRUPTS_DISABLE | PMC_CONFIG_HVD_INTERRUPTS_DISABLE));
    IP_PMC->CONFIG = TempValue;

#if !(defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_009) || defined(POWER_IP_DERIVATIVE_008))
    /* Disable LM Regulator, if enabled, and notify the application */
    if ((PMC_CONFIG_LAST_MILE_REG_ENABLE == ((uint32)(IP_PMC->CONFIG & PMC_CONFIG_LMEN_MASK))) || \
        (PMC_CONFIG_LAST_MILE_REG_AUTO_ENABLE == ((uint32)(IP_PMC->CONFIG & PMC_CONFIG_LMAUTOEN_MASK))))
    {
        TempValue = IP_PMC->CONFIG;
        TempValue = (uint32)(TempValue & (uint32)( ~(PMC_CONFIG_LMBCTLEN_MASK | PMC_CONFIG_LMEN_MASK | PMC_CONFIG_LMAUTOEN_MASK) ) );
        TempValue = (uint32)(TempValue | (uint32)(PMC_CONFIG_LM_BASE_CONTROL_DISABLE | PMC_CONFIG_LAST_MILE_REG_DISABLE | PMC_CONFIG_LAST_MILE_REG_AUTO_DISABLE));
        IP_PMC->CONFIG = TempValue;

        /* Notify the application of the regulator disablement to further signal the SBC, if needed */
#ifdef POWER_IP_PMC_NOTIFICATION
        POWER_IP_PMC_NOTIFICATION(POWER_IP_LAST_MILE_REGULATOR_DISABLED);
#else
        Power_Ip_ReportPowerErrors(POWER_IP_PMC_ERROR, POWER_IP_LAST_MILE_REGULATOR_DISABLED);
#endif
    }
#endif
}
#endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */

#if (defined(POWER_IP_VOLTAGE_ERROR_ISR_USED))
  #if (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON)
/**
* @brief            This function handles the voltage error detection.
*
* @return           void
*
* @isr
* @implements Power_Ip_PMC_VoltageErrorIsr_Activity
*/
void Power_Ip_PMC_VoltageErrorIsr(void)
{
    uint32 RegValue;
    uint32 VoltageIsrEnabled;
    uint32 VoltageIsrStatus;
    uint32 EventReport;
    RegValue = IP_PMC->LVSC;

    VoltageIsrEnabled = RegValue & PMC_LVSC_OV_UV_IRQ_FLAGS_MASK32;

    if (PMC_UNINIT != Power_Ip_ePMCStatus)
    {

        VoltageIsrStatus = RegValue & PMC_LVSC_OV_UV_STATUS_FLAGS_MASK32;

        RegValue = IP_PMC->CONFIG;

        if (PMC_CONFIG_LVD_INTERRUPTS_DISABLE == (RegValue & PMC_CONFIG_LVDIE_MASK))
        {
            VoltageIsrEnabled = (VoltageIsrEnabled & (uint32)(~PMC_LVSC_UV_IRQ_FLAGS_MASK32));
        }
        else
        {
            IP_PMC->LVSC &= (uint32)(~PMC_LVSC_UV_IRQ_FLAGS_MASK32);
        }

        if (PMC_CONFIG_HVD_INTERRUPTS_DISABLE == (RegValue & PMC_CONFIG_HVDIE_MASK))
        {
            VoltageIsrEnabled = (VoltageIsrEnabled & (uint32)(~PMC_LVSC_OV_IRQ_FLAGS_MASK32));
        }
        else
        {
            IP_PMC->LVSC &= (uint32)(~PMC_LVSC_OV_IRQ_FLAGS_MASK32);
        }

        /* Align IRQ Flags with Status flags */
        VoltageIsrStatus = (VoltageIsrStatus >> 8U);
        EventReport = (VoltageIsrStatus & VoltageIsrEnabled);

        /* Check if there is any event to report */
        if ((uint32)0U != EventReport)
        {
            if (((EventReport & PMC_LVSC_UV_IRQ_FLAGS_MASK32) != (uint32)0U) && \
                ((EventReport & PMC_LVSC_OV_IRQ_FLAGS_MASK32) != (uint32)0U))
            {
#ifdef POWER_IP_ERROR_ISR_NOTIFICATION
                POWER_IP_ERROR_ISR_NOTIFICATION(POWER_IP_E_ISR_VOLTAGE_ERROR);
#else
                Power_Ip_ReportPowerErrors(POWER_IP_ISR_ERROR, POWER_IP_E_ISR_VOLTAGE_ERROR);
#endif
            }
            else if ((EventReport & PMC_LVSC_UV_IRQ_FLAGS_MASK32) != (uint32)0U)
            {
#ifdef POWER_IP_ERROR_ISR_NOTIFICATION
                POWER_IP_ERROR_ISR_NOTIFICATION(POWER_IP_E_ISR_LOW_VOLTAGE);
#else
                Power_Ip_ReportPowerErrors(POWER_IP_ISR_ERROR, POWER_IP_E_ISR_LOW_VOLTAGE);
#endif
            }
            else
            {
#ifdef POWER_IP_ERROR_ISR_NOTIFICATION
                POWER_IP_ERROR_ISR_NOTIFICATION(POWER_IP_E_ISR_HIGH_VOLTAGE);
#else
                Power_Ip_ReportPowerErrors(POWER_IP_ISR_ERROR, POWER_IP_E_ISR_HIGH_VOLTAGE);
#endif
            }

        }
    }
    else
    {
        /* Clear ISR flag */
        IP_PMC->LVSC = VoltageIsrEnabled;
    }
}

  #endif
#endif /* (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON) */

#if (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API))

/**
* @brief            This function handle the high voltage detection on VDDINT or VDD15.
*
* @return           void
*
* @isr
*
*/
void Power_Ip_PMC_AE_VoltageDetectHvdOnVddintVdd15Isr(void)
{
    uint32 TmpAe;
    uint32 VoltageDetectFlags;
    uint32 VoltageDetectStatus;
    uint32 EventReport;

    /* Read Voltage Detect Flag */
    Aec_Ip_SpiRead((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,&TmpAe);

    VoltageDetectFlags = (TmpAe & (PMC_AE_MONITOR_HVDINTF_MASK | PMC_AE_MONITOR_HVD15F_MASK | PMC_AE_MONITOR_RWBITS_MASK32));

    if(PMC_UNINIT != Power_Ip_ePMCAeStatus)
    {
        VoltageDetectStatus = (TmpAe & (PMC_AE_MONITOR_HVDINTS_MASK | PMC_AE_MONITOR_HVD15S_MASK));
        if ((uint32)0U == (TmpAe & PMC_AE_MONITOR_HVDINT15IE_MASK))
        {
            VoltageDetectFlags = (VoltageDetectFlags & (uint32)(~(PMC_AE_MONITOR_HVDINTF_MASK | PMC_AE_MONITOR_HVD15F_MASK)));
        }
        /* Align IRQ Flags with Status flags */
        VoltageDetectStatus = (VoltageDetectStatus >> 16U);
        EventReport = (VoltageDetectStatus & VoltageDetectFlags);

        /* Check if there is any event to report */
        if ((uint32)0U != EventReport)
        {
            /* clear IRQ flags */
            Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);

            if((uint32)0x0U != (EventReport & PMC_AE_MONITOR_HVDINTF_MASK))
            {
#ifdef POWER_IP_DETECT_ISR_NOTIFICATION
                POWER_IP_DETECT_ISR_NOTIFICATION(POWER_IP_ISR_VOLTAGE_HVD_VDDINT_DETECT,POWER_IP_E_ISR_HIGH_VOLTAGE);
#else
                Power_Ip_ReportPowerErrors(POWER_IP_ISR_VOLTAGE_HVD_VDDINT_DETECT, POWER_IP_E_ISR_HIGH_VOLTAGE);
#endif
            }

            if((uint32)0x0U != (EventReport & PMC_AE_MONITOR_HVD15F_MASK))
            {
#ifdef POWER_IP_DETECT_ISR_NOTIFICATION
                POWER_IP_DETECT_ISR_NOTIFICATION(POWER_IP_ISR_VOLTAGE_HVD_15_DETECT,POWER_IP_E_ISR_HIGH_VOLTAGE);
#else
                Power_Ip_ReportPowerErrors(POWER_IP_ISR_VOLTAGE_HVD_15_DETECT, POWER_IP_E_ISR_HIGH_VOLTAGE);
#endif
            }
        }
    }
    else
    {
        /* clear IRQ flags */
        Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);
    }
}

/**
* @brief            This function handle the high voltage detection on VDD.
*
* @return           void
*
* @isr
*
*/
void Power_Ip_PMC_AE_VoltageDetectHvdOnVddIsr(void)
{
    uint32 TmpAe;
    uint32 VoltageDetectStatus;
    uint32 VoltageDetectFlags;
    uint32 EventReport;

    /* Read Voltage Detect Flag */
    Aec_Ip_SpiRead((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,&TmpAe);
    VoltageDetectFlags = (TmpAe & (PMC_AE_MONITOR_HVDVDDF_MASK | PMC_AE_MONITOR_RWBITS_MASK32));

    if(PMC_UNINIT != Power_Ip_ePMCAeStatus)
    {
        VoltageDetectStatus = (TmpAe & PMC_AE_MONITOR_HVDVDDS_MASK);
        if ((uint32)0U == (TmpAe & PMC_AE_MONITOR_HVDVDDIE_MASK))
        {
            VoltageDetectFlags = (VoltageDetectFlags & (uint32)(~PMC_AE_MONITOR_HVDVDDF_MASK));
        }
        /* Align IRQ Flags with Status flags */
        VoltageDetectStatus = (VoltageDetectStatus >> 16U);
        EventReport = (VoltageDetectStatus & VoltageDetectFlags);

        /* Check if there is any event to report */
        if ((uint32)0U != EventReport)
        {
            /* clear IRQ flags */
            Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);
#ifdef POWER_IP_DETECT_ISR_NOTIFICATION
            POWER_IP_DETECT_ISR_NOTIFICATION(POWER_IP_ISR_VOLTAGE_HVD_VDD_DETECT,POWER_IP_E_ISR_HIGH_VOLTAGE);
#else
            Power_Ip_ReportPowerErrors(POWER_IP_ISR_VOLTAGE_HVD_VDD_DETECT, POWER_IP_E_ISR_HIGH_VOLTAGE);
#endif
        }
    }
    else
    {
        /* clear IRQ flags */
        Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);
    }
}

/**
* @brief            This function handle the low voltage detection on VDDC.
*
* @return           void
*
* @isr
*
*/
void Power_Ip_PMC_AE_VoltageDetectLvdOnVddcIsr(void)
{
    uint32 TmpAe;
    uint32 VoltageDetectStatus;
    uint32 VoltageDetectFlags;
    uint32 EventReport;

    /* Read Voltage Detect Flag */
    Aec_Ip_SpiRead((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,&TmpAe);
    VoltageDetectFlags = (TmpAe & (PMC_AE_MONITOR_LVDCF_MASK | PMC_AE_MONITOR_RWBITS_MASK32));

    if(PMC_UNINIT != Power_Ip_ePMCAeStatus)
    {
        VoltageDetectStatus = (TmpAe & PMC_AE_MONITOR_LVDCS_MASK);
        if ((uint32)0U == (TmpAe & PMC_AE_MONITOR_LVDCIE_MASK))
        {
            VoltageDetectFlags = (VoltageDetectFlags & (uint32)(~PMC_AE_MONITOR_LVDCF_MASK));
        }
        /* Align IRQ Flags with Status flags */
        VoltageDetectStatus = (VoltageDetectStatus >> 16U);
        EventReport = (VoltageDetectStatus & VoltageDetectFlags);

        /* Check if there is any event to report */
        if ((uint32)0U != EventReport)
        {
            /* clear IRQ flags */
            Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);
#ifdef POWER_IP_DETECT_ISR_NOTIFICATION
            POWER_IP_DETECT_ISR_NOTIFICATION(POWER_IP_ISR_VOLTAGE_LVD_VDDC_DETECT,POWER_IP_E_ISR_LOW_VOLTAGE);
#else
            Power_Ip_ReportPowerErrors(POWER_IP_ISR_VOLTAGE_LVD_VDDC_DETECT, POWER_IP_E_ISR_LOW_VOLTAGE);
#endif
        }
    }
    else
    {
        /* clear IRQ flags */
        Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);
    }
}

/**
* @brief            This function handle the low voltage detection on VLS.
*
* @return           void
*
* @isr
*
*/
void Power_Ip_PMC_AE_VoltageDetectLvdOnVlsIsr(void)
{


    uint32 TmpAe;
    uint32 VoltageDetectStatus;
    uint32 VoltageDetectFlags;
    uint32 EventReport;

    /* Read Voltage Detect Flag */
    Aec_Ip_SpiRead((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,&TmpAe);
    VoltageDetectFlags = (TmpAe & (PMC_AE_MONITOR_LVDVLSF_MASK | PMC_AE_MONITOR_RWBITS_MASK32));

    if(PMC_UNINIT != Power_Ip_ePMCAeStatus)
    {
        VoltageDetectStatus = (TmpAe & PMC_AE_MONITOR_LVDVLSS_MASK);
        if ((uint32)0U == (TmpAe & PMC_AE_MONITOR_LVDVLSIE_MASK))
        {
            VoltageDetectFlags = (VoltageDetectFlags & (uint32)(~PMC_AE_MONITOR_LVDVLSF_MASK));
        }
        /* Align IRQ Flags with Status flags */
        VoltageDetectStatus = (VoltageDetectStatus >> 16U);
        EventReport = (VoltageDetectStatus & VoltageDetectFlags);

        /* Check if there is any event to report */
        if ((uint32)0U != EventReport)
        {
            /* clear IRQ flags */
            Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);
#ifdef POWER_IP_DETECT_ISR_NOTIFICATION
            POWER_IP_DETECT_ISR_NOTIFICATION(POWER_IP_ISR_VOLTAGE_LVD_VLS_DETECT,POWER_IP_E_ISR_LOW_VOLTAGE);
#else
            Power_Ip_ReportPowerErrors(POWER_IP_ISR_VOLTAGE_LVD_VLS_DETECT, POWER_IP_E_ISR_LOW_VOLTAGE);
#endif
        }
    }
    else
    {
        /* clear IRQ flags */
        Aec_Ip_SpiWrite((uint32)(&(IP_PMC_AE->MONITOR)),POWER_IP_DATAWIDTH_32,VoltageDetectFlags);
    }
}
#endif

#ifdef POWER_IP_LASTMILE_SUPPORT
  #if (STD_ON == POWER_IP_LASTMILE_SUPPORT)
/**
* @brief            This function to enable Last Mile regulator.
* @details          In Run Mode, chip run in high frequency(PLL), so power to supply to core and flash need to provide from Last Mile.
*                   to ensure that this device wasn't damage.
*                   This function required to call Power_Ip_Init first.
*
* @param[in]        BJTused   BJT used or not depend on PCB.
*
* @return           void
*
*/
void Power_Ip_PMC_EnableLastMile(boolean BJTused)
{
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    boolean TimeoutOccurred = FALSE;
    uint32 LvscValue;
    
    IP_PMC->CONFIG &= ~PMC_CONFIG_LMEN_MASK;
    
    /* If external BJT is using on the PCB board, the program needs to wait for the LVD15S bit to be cleared, then LMEN is enabled */
    if ((boolean)TRUE != BJTused)
    {
        IP_PMC->CONFIG |= PMC_CONFIG_LMBCTLEN_MASK;
        /* Check FASTREC status */
        if (0U != (IP_PMC->CONFIG & PMC_CONFIG_FASTREC_MASK))
        {
            /* If fast recovery enabled, wait for 15us*/
            Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, FASTREC_TIME_WAIT);
            do
            {
                TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            } while (!TimeoutOccurred);
        }
        else
        {
            /* If fast recovery disabled, wait for 50 us */
            Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, NORMAL_TIME_WAIT);
            do
            {
                TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            } while (!TimeoutOccurred);
        }
    }
    
    /* Check status LVD15S. Request turn on 1.5V */
    Power_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, POWER_IP_TIMEOUT_VALUE_US);
    
    do
    {
        TimeoutOccurred = Power_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);

        LvscValue = IP_PMC->LVSC;
    } while ((0U != (LvscValue & PMC_LVSC_LVD15S_MASK)) && (!TimeoutOccurred));
    
    if (!TimeoutOccurred)
    {
        /* Set LMEN */
        IP_PMC->CONFIG |= PMC_CONFIG_LMEN_MASK;
    }
    else
    {
        Power_Ip_ReportPowerErrors(POWER_IP_REPORT_TIMEOUT_ERROR, POWER_IP_ERR_CODE_RESERVED);
    }
}

/**
* @brief            This function to disable Last Mile regulator
* @details          This function can be used before LPM entry to switch power supply to core and flash.
*                   to ensure that this device works within the correct voltage range.
*                   This function required to call Power_Ip_Init first.
*
* @return           void
*
*/
void Power_Ip_PMC_DisableLastMile(void)
{
    /* If BJT used, LMEN and LMBCTLEN must be cleared simultaneously */
    if (0U != (IP_PMC->CONFIG & PMC_CONFIG_LMBCTLEN_MASK))
    {
        IP_PMC->CONFIG &= ~(PMC_CONFIG_LMBCTLEN_MASK | PMC_CONFIG_LMEN_MASK); 
    }
    else
    {
        IP_PMC->CONFIG &= ~PMC_CONFIG_LMEN_MASK;
    }
}
  #endif
#endif

#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
