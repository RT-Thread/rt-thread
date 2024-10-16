/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
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
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file    Siul2_Port_Ip.c
*
*   @addtogroup Port_IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Siul2_Port_Ip.h"
#include "SchM_Port.h"
#ifdef PORT_ENABLE_USER_MODE_SUPPORT
   #define USER_MODE_REG_PROT_ENABLED   (PORT_ENABLE_USER_MODE_SUPPORT)
   #include "RegLockMacros.h"
   #include "OsIf_Internal.h"
#endif
#ifdef MCAL_ENABLE_FAULT_INJECTION
#include "Mcal.h"
#endif

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
* @brief Parameters that shall be published within the driver header file and also in the
* module's description file
*/
#define SIUL2_PORT_IP_VENDOR_ID_C                     43
#define SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C      4
#define SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C      7
#define SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_C   0
#define SIUL2_PORT_IP_SW_MAJOR_VERSION_C              5
#define SIUL2_PORT_IP_SW_MINOR_VERSION_C              0
#define SIUL2_PORT_IP_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files Siul2_Port_Ip.c and Siul2_Port_Ip.h are of the same version */
#if (SIUL2_PORT_IP_VENDOR_ID_C != SIUL2_PORT_IP_VENDOR_ID_H)
    #error "Siul2_Port_Ip.c and Siul2_Port_Ip.h have different vendor ids"
#endif
/* Check if Siul2_Port_Ip.c and Siul2_Port_Ip.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_C != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip.c and Siul2_Port_Ip.h are different"
#endif
/* Check if Siul2_Port_Ip.c and Siul2_Port_Ip.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_C != SIUL2_PORT_IP_SW_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_MINOR_VERSION_C != SIUL2_PORT_IP_SW_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_PATCH_VERSION_C != SIUL2_PORT_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip.c and Siul2_Port_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Siul2_Port_Ip.c and RegLockMacros.h are of the same version */
    #ifdef PORT_ENABLE_USER_MODE_SUPPORT
        #if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
             (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AutoSar Version Numbers of Siul2_Port_Ip.c and RegLockMacros.h are different"
        #endif
        /* Check if the files Siul2_Port_Ip.c and OsIf_Internal.h are of the same version */
        #if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C != OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION) || \
             (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C != OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AutoSar Version Numbers of Siul2_Port_Ip.c and OsIf_Internal.h are different"
        #endif
    #endif /* PORT_ENABLE_USER_MODE_SUPPORT */
    /* Check if the files Siul2_Port_Ip.c and SchM_Port.h are of the same version */
    #if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_PORT_AR_RELEASE_MAJOR_VERSION) || \
         (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_PORT_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Siul2_Port_Ip.c and SchM_Port.h are different"
    #endif
    #ifdef MCAL_ENABLE_FAULT_INJECTION
        #if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
             (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AutoSar Version Numbers of Siul2_Port_Ip.c and Mcal.h are different"
        #endif
    #endif
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
#define SIUL2_NUM_OF_PIN_PORT           16u

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/
#define PORT_START_SEC_CONST_32
#include "Port_MemMap.h"

#if (STD_ON == PORT_VIRTWRAPPER_SUPPORT)
/**
* @brief Base address array for Siul2 instances
*/
const uint32 Port_au32Siul2BaseAddr[][SIUL2_PDAC_SLOT_NUM] =
{
    {
        #ifdef SIUL2_PDAC0_BASE
        SIUL2_PDAC0_BASE,
        #endif
        #ifdef SIUL2_PDAC1_BASE
        SIUL2_PDAC1_BASE,
        #endif
        #ifdef SIUL2_PDAC2_BASE
        SIUL2_PDAC2_BASE,
        #endif
        #ifdef SIUL2_PDAC3_BASE
        SIUL2_PDAC3_BASE,
        #endif
        #ifdef SIUL2_PDAC4_BASE
        SIUL2_PDAC4_BASE,
        #endif
        #ifdef SIUL2_PDAC5_BASE
        SIUL2_PDAC5_BASE,
        #endif
    }
};
#else
/**
* @brief Base address array for Siul2 instances
*/
const uint32 Port_au32Siul2BaseAddr[] =
{
#ifdef IP_SIUL2_BASE
    IP_SIUL2_BASE
#endif
#ifdef IP_SIUL2_0_BASE
    IP_SIUL2_0_BASE
#endif
#ifdef IP_SIUL2_1_BASE
    ,IP_SIUL2_1_BASE
#endif
#ifdef IP_SIUL2_AE_BASE
    ,IP_SIUL2_AE_BASE
#endif
};
#endif /* STD_ON == PORT_VIRTWRAPPER_SUPPORT */

#define PORT_STOP_SEC_CONST_32
#include "Port_MemMap.h"

#define PORT_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Port_MemMap.h"

static const Siul2_Port_Ip_PinSettingsConfig * pPort_Setting;

#define PORT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Port_MemMap.h"

#define PORT_START_SEC_VAR_CLEARED_32
#include "Port_MemMap.h"

static uint32 u32MaxPinConfigured;

#define PORT_STOP_SEC_VAR_CLEARED_32
#include "Port_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * given structure.
 *
 * @param[in] pinNumber the number of configured pins in structure
 * @param[in] config the configuration structure
  */
static void Siul2_Port_Ip_PinInit(const Siul2_Port_Ip_PinSettingsConfig * config);

/*!
 * @brief Write to Input Multiplexed Signal Configuration Register
 *
 * This function configures the register with the provided in the
 * given structure.
 *
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_WriteIMCRConfiguration(const Siul2_Port_Ip_PinSettingsConfig * config);

#ifdef SIUL2_PORT_IP_HAS_ADC_INTERLEAVE
/*!
 * @brief Write to Device configuration module Register
 *
 * This function configures the adc muxing mode with the provided in the
 * given structure.
 *
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_WriteDCMConfiguration(const Siul2_Port_Ip_PinSettingsConfig * config);
#endif /* SIUL2_PORT_IP_HAS_ADC_INTERLEAVE */

/*!
 * @brief Get the MSCR configuration from the MSCR register
 *
 * @param[in] pinNumber the number of configured pins in structure
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_GetMSCRConfiguration(Siul2_Port_Ip_PinSettingsConfig * config,
                                                      const Siul2_Port_Ip_PortType * const base,
                                                      uint16 pin
                                                     );

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_Init
 * Description   : This function configures the pin feature with the options
 * provided in the given structure.
 *
 *END**************************************************************************/
static void Siul2_Port_Ip_PinInit(const Siul2_Port_Ip_PinSettingsConfig * config)
{
    uint32 pinsValues = 0U;
    uint8 siulInstance = 0U;

    SIUL2_PORT_IP_DEV_ASSERT((boolean)(config != NULL_PTR));
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(config->pinPortIdx < SIUL2_MSCR_COUNT));

#ifdef IP_SIUL2
    if (config->base == IP_SIUL2)
    {
        siulInstance = 0U;
    }
#endif /* IP_SIUL2 */
#ifdef IP_SIUL2_0
    if (config->base == IP_SIUL2_0)
    {
        siulInstance = 0U;
    }
#endif /* IP_SIUL2_0 */
#ifdef IP_SIUL2_1
    else
    {
        siulInstance = 1U;
    }
#endif /* IP_SIUL2_1 */

    if (config->pullConfig != PORT_INTERNAL_PULL_NOT_ENABLED)
    {
        pinsValues |= SIUL2_MSCR_PUE(1);
        pinsValues |= SIUL2_MSCR_PUS(config->pullConfig);
    }

    if (PORT_OUTPUT_BUFFER_NOT_AVAILABLE != config->outputBuffer)
    {
        pinsValues |= SIUL2_MSCR_OBE(config->outputBuffer);
    }
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA)
    if (PORT_INVERT_NOT_AVAILABLE != config->invert)
    {
        pinsValues |= SIUL2_MSCR_INV(config->invert);
    }
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER)
    if (PORT_PULL_KEEP_NOT_AVAILABLE != config->pullKeep)
    {
        pinsValues |= SIUL2_MSCR_PKE(config->pullKeep);
    }
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT)
    if (PORT_RECEIVER_NOT_AVAILABLE != config->receiverSel)
    {
        pinsValues |= SIUL2_MSCR_RCVR(config->receiverSel);
    }
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT*/
#endif /* FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT*/
#ifdef FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN)
    if (PORT_OPEN_DRAIN_NOT_AVAILABLE != config->openDrain)
    {
        pinsValues |= SIUL2_MSCR_ODE(config->openDrain);
    }
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH)
    if (PORT_DRIVE_STRENTGTH_NOT_AVAILABLE != config->driveStrength)
    {
        pinsValues |= SIUL2_MSCR_DSE(config->driveStrength);
    }
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER)
    if (PORT_INPUT_FILTER_NOT_AVAILABLE != config->inputFilter)
    {
        pinsValues |= SIUL2_MSCR_IFE(config->inputFilter);
    }
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER */
    if (PORT_INPUT_BUFFER_NOT_AVAILABLE != config->inputBuffer)
    {
        pinsValues |= SIUL2_MSCR_IBE(config->inputBuffer);
    }
    if (PORT_SLEW_RATE_NOT_AVAILABLE != config->slewRateCtrlSel)
    {
        pinsValues |= SIUL2_MSCR_SRE(config->slewRateCtrlSel);
    }
    if (PORT_SAFE_MODE_NOT_AVAILABLE != config->safeMode)
    {
        pinsValues |= SIUL2_MSCR_SMC(config->safeMode);
    }
    pinsValues |= SIUL2_MSCR_SSS(config->mux);

    /* Configure initial value for GPIO pin in GPIO mux */
    /* SWS_Port_00055 : The function Port_Init shall set the port pin output latch to a default level (defined during configuration) before setting the port pin direction to output. */
    if ((PORT_MUX_AS_GPIO == config->mux) && (PORT_OUTPUT_BUFFER_ENABLED == config->outputBuffer))
    {
#if (STD_ON == PORT_VIRTWRAPPER_SUPPORT)
        /* If the value is low or high */
        if (config->initValue != PORT_PIN_LEVEL_NOTCHANGED_U8)
        {
            /* Write the value into GPDO register */
            PORT_WRITE8(SIUL2_GPDO_ADDR8(siulInstance, config->mscrPdacSlot, (uint16)config->pinPortIdx), config->initValue);
        }
#else
        /* If the value is low or high */
        if (config->initValue != PORT_PIN_LEVEL_NOTCHANGED_U8)
        {
            /* Write the value into GPDO register */
            PORT_WRITE8(SIUL2_GPDO_ADDR8(siulInstance, (uint16)config->pinPortIdx), config->initValue);
        }
#endif /* STD_ON == PORT_VIRTWRAPPER_SUPPORT */
    }
    /* Write to Input Multiplexed Signal Configuration Register */
    Siul2_Port_Ip_WriteIMCRConfiguration(config);

    /* Fault injection label for testing purpose */
#ifdef MCAL_ENABLE_FAULT_INJECTION
    MCAL_FAULT_INJECTION_POINT(PORT_CHANGE_DIRECTION_VALUE);
#endif

    /* SWS_Port_00043 : The function Port_Init shall avoid glitches and spikes on the affected port pins. Hint: Perform output enable and/or input enable as a final step of the pad initialization. */
    /* Write to Multiplexed Signal Configuration Register */
    config->base->MSCR[config->pinPortIdx] = pinsValues;

#ifdef SIUL2_PORT_IP_HAS_ADC_INTERLEAVE
    /* Write to DCM GPR Register to config adc interleave mux mode */
    Siul2_Port_Ip_WriteDCMConfiguration(config);
#endif /* SIUL2_PORT_IP_HAS_ADC_INTERLEAVE */
}

#ifdef SIUL2_PORT_IP_HAS_ADC_INTERLEAVE
/*!
 * @brief Write to Device configuration module Register
 *
 * This function configures the adc muxing mode with the provided in the
 * given structure.
 *
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_WriteDCMConfiguration(const Siul2_Port_Ip_PinSettingsConfig * config)
{
    uint32 dcmrwf4RegValue;
    uint8 iterator;
    uint32 adcInterleaves;
    dcmrwf4RegValue = PORT_READ32(DCM_DCMRWF4_ADDR32);

    for (iterator = 0; iterator < FEATURE_ADC_INTERLEAVE_MAX_MUX_MODE; iterator++)
    {
        adcInterleaves = (uint32)config->adcInterleaves[iterator];
        if ((uint32)MUX_MODE_NOT_AVAILABLE != adcInterleaves)
        {
            if (DCM_DCMRWF4_ADC_CLEAR_VALUE_FLAG == (adcInterleaves & DCM_DCMRWF4_ADC_CLEAR_VALUE_FLAG))
            {
                /* Clear ADC Interleave bit */
                dcmrwf4RegValue &= ((~DCM_DCMRWF4_ADC_INTERLEAVE_MASK) | adcInterleaves);
            }
            else
            {
                /* Set ADC Interleave bit */
                dcmrwf4RegValue |= adcInterleaves;
            }
        }
    }

    PORT_WRITE32(DCM_DCMRWF4_ADDR32, dcmrwf4RegValue);
}
#endif /* SIUL2_PORT_IP_HAS_ADC_INTERLEAVE */

/*!
 * @brief Write to Input Multiplexed Signal Configuration Register
 *
 * This function configures the register with the provided in the
 * given structure.
 *
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_WriteIMCRConfiguration(const Siul2_Port_Ip_PinSettingsConfig * config)
{
    uint8 inputMuxIterator;
    uint32 imcrRegIdx;
#if (STD_ON == PORT_VIRTWRAPPER_SUPPORT)
    uint8 imcrPdacSlot;
#endif /* PORT_VIRTWRAPPER_SUPPORT*/

#ifdef IP_SIUL2_0_BASE
    SIUL2_Type * imcrBase = (SIUL2_Type *)IP_SIUL2_0_BASE;
#endif /* IP_SIUL2_0_BASE */
#ifdef IP_SIUL2_BASE
    SIUL2_Type * imcrBase = (SIUL2_Type *)IP_SIUL2_BASE;
#endif /* IP_SIUL2_BASE */

    if (PORT_INPUT_BUFFER_ENABLED == config->inputBuffer)
    {
        for (inputMuxIterator = 0U; inputMuxIterator < FEATURE_SIUL2_MAX_NUMBER_OF_INPUT; inputMuxIterator++)
        {
            /* Check if input mux information needs to be configured */
            if (PORT_INPUT_MUX_NO_INIT != config->inputMux[inputMuxIterator])
            {
                /* Write to Input Mux register */
                imcrRegIdx = config->inputMuxReg[inputMuxIterator];
                /* If the IMCR number is higher than 512 then the IMCR register is on siul2_1 */
                if (imcrRegIdx < SIUL2_MAX_NUM_OF_IMCR_REG)
                {
                    /* Use the base address of SIUL2_0 */
                    #ifdef IP_SIUL2_0_BASE
                        imcrBase = (SIUL2_Type *)IP_SIUL2_0_BASE;
                    #endif /* IP_SIUL2_0_BASE */
                    #ifdef IP_SIUL2_BASE
                        imcrBase = (SIUL2_Type *)IP_SIUL2_BASE;
                    #if (STD_ON == PORT_VIRTWRAPPER_SUPPORT)
                        imcrPdacSlot = config->imcrPdacSlot;
                        imcrBase = (SIUL2_Type *)Port_au32Siul2BaseAddr[0][imcrPdacSlot];
                    #endif /* PORT_VIRTWRAPPER_SUPPORT*/
                    #endif /* IP_SIUL2_BASE */
                }
#ifdef IP_SIUL2_1_BASE
                else
                {
                    /* Use the base address of SIUL2_1 */
                    imcrBase = (SIUL2_Type *)IP_SIUL2_1_BASE;
                    imcrRegIdx = imcrRegIdx - SIUL2_MAX_NUM_OF_IMCR_REG;
                }
#endif /* IP_SIUL2_1_BASE */
                if (imcrRegIdx < SIUL2_IMCR_COUNT)
                {
                    /* Config input signal */
                    imcrBase->IMCR[imcrRegIdx % SIUL2_MAX_NUM_OF_IMCR_REG] = SIUL2_IMCR_SSS(config->inputMux[inputMuxIterator]);
                }
            }
        }
    }
}

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * given structure.
 *
 * @param[in] pinNumber the number of configured pins in structure
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_GetMSCRConfiguration(Siul2_Port_Ip_PinSettingsConfig * config,
                                                      const Siul2_Port_Ip_PortType * const base,
                                                      uint16 pin
                                                     )
{
    uint32 u32RegVal = 0UL;
    /* This var used to fix misra rule 10.8 to 10.5*/
    uint32 u32TempVal = 0UL;
    Siul2_Port_Ip_PortPullConfig pullValue;

    u32RegVal = base->MSCR[pin];
    u32TempVal = (u32RegVal & SIUL2_MSCR_SSS_MASK) >> SIUL2_MSCR_SSS_SHIFT;
    config->mux = (Siul2_Port_Ip_PortMux)(u32TempVal);
    u32TempVal = (u32RegVal & SIUL2_MSCR_SMC_MASK) >> SIUL2_MSCR_SMC_SHIFT;
    config->safeMode = (Siul2_Port_Ip_PortSafeMode)(u32TempVal);

    if (0U == ((u32RegVal & SIUL2_MSCR_PUE_MASK) >> SIUL2_MSCR_PUE_SHIFT))
    {
        pullValue = PORT_INTERNAL_PULL_NOT_ENABLED;
    }
    else
    {
        u32TempVal = (u32RegVal & SIUL2_MSCR_PUS_MASK) >> SIUL2_MSCR_PUS_SHIFT;
        pullValue = (Siul2_Port_Ip_PortPullConfig)(u32TempVal);
    }

    config->pullConfig = pullValue;
    u32TempVal = (u32RegVal & SIUL2_MSCR_SRE_MASK) >> SIUL2_MSCR_SRE_SHIFT;
    config->slewRateCtrlSel = (Siul2_Port_Ip_PortSlewRateControl)(u32TempVal);
#ifdef FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT)
    u32TempVal = (u32RegVal & SIUL2_MSCR_RCVR_MASK) >> SIUL2_MSCR_RCVR_SHIFT;
    config->receiverSel = (Siul2_Port_Ip_PortReceiverSelect)(u32TempVal);
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN)
    u32TempVal = (u32RegVal & SIUL2_MSCR_ODE_MASK) >> SIUL2_MSCR_ODE_SHIFT;
    config->openDrain = (Siul2_Port_Ip_PortOpenDrain)(u32TempVal);
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH)
    u32TempVal = (u32RegVal & SIUL2_MSCR_DSE_MASK) >> SIUL2_MSCR_DSE_SHIFT;
    config->driveStrength = (Siul2_Port_Ip_PortDriveStrength)(u32TempVal);
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER)
    u32TempVal = (u32RegVal & SIUL2_MSCR_IFE_MASK) >> SIUL2_MSCR_IFE_SHIFT;
    config->inputFilter = (Siul2_Port_Ip_PortInputFilter)(u32TempVal);
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA)
    u32TempVal = (u32RegVal & SIUL2_MSCR_INV_MASK) >> SIUL2_MSCR_INV_SHIFT;
    config->invert = (Siul2_Port_Ip_PortInvert)(u32TempVal);
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER
#if (STD_ON == FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER)
    u32TempVal = (u32RegVal & SIUL2_MSCR_PKE_MASK) >> SIUL2_MSCR_PKE_SHIFT;
    config->pullKeep = (Siul2_Port_Ip_PortPullKeep)(u32TempVal);
#endif /* STD_ON == FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER */
#endif /* FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER */
    u32TempVal = (u32RegVal & SIUL2_MSCR_IBE_MASK) >> SIUL2_MSCR_IBE_SHIFT;
    config->inputBuffer = (Siul2_Port_Ip_PortInputBuffer)(u32TempVal);
    u32TempVal = (u32RegVal & SIUL2_MSCR_OBE_MASK) >> SIUL2_MSCR_OBE_SHIFT;
    config->outputBuffer = (Siul2_Port_Ip_PortOutputBuffer)(u32TempVal);
}

#if (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT))
#if (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE))
#if (defined(PORT_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == PORT_SIUL2_REG_PROT_AVAILABLE))
/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetUserAccessAllowed
 * Description   : Enables SIUL2 registers writing in User Mode by configuring REG_PROT
 *                 Sets the UAA (User Access Allowed) bit of the SIUL2 IP allowing SIUL2 registers writing in User Mode
 *
 *END**************************************************************************/

void Siul2_Port_Ip_SetUserAccessAllowed(void)
{
#ifdef IP_SIUL2_BASE
    SET_USER_ACCESS_ALLOWED(IP_SIUL2_BASE, SIUL2_PROT_MEM_U32);
    SET_USER_ACCESS_ALLOWED(IP_DCM_GPR_BASE, DCM_PROT_MEM_U32);
#endif /* IP_SIUL2_BASE */
#ifdef IP_SIUL2_0_BASE
    SET_USER_ACCESS_ALLOWED(IP_SIUL2_0_BASE, SIUL2_PROT_MEM_U32);
#endif /* IP_SIUL2_0_BASE */
#ifdef IP_SIUL2_1_BASE
    SET_USER_ACCESS_ALLOWED(IP_SIUL2_1_BASE, SIUL2_PROT_MEM_U32);
#endif /* IP_SIUL2_1_BASE */
}
#endif /* (defined(PORT_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == PORT_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT)) */

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/


/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_Init
 * Description   : This function configures the pins with the options provided
 * in the given structure.
 *
 * @implements Siul2_Port_Ip_Init_Activity
 *END**************************************************************************/
Siul2_Port_Ip_PortStatusType Siul2_Port_Ip_Init(uint32 pinCount,
                                                const Siul2_Port_Ip_PinSettingsConfig config[]
                                               )
{
    uint32 i;

#if (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT))
#if (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE))
#if (defined(PORT_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == PORT_SIUL2_REG_PROT_AVAILABLE))
    /* Enable register access from user mode, if enabled from configuration file */
    OsIf_Trusted_Call(Siul2_Port_Ip_SetUserAccessAllowed);
#endif /* (defined(PORT_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == PORT_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT)) */

    /* Store the configuration pointer */
    pPort_Setting = config;

    /* Store the number of configured pins */
    u32MaxPinConfigured = pinCount;
    for (i = 0U; i < pinCount; i++)
    {
        Siul2_Port_Ip_PinInit(&config[i]);
    }

    return SIUL2_PORT_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetPullSel
 * Description   : This function configures the internal resistor.
 *
 * @implements Siul2_Port_Ip_SetPullSel_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetPullSel(Siul2_Port_Ip_PortType * const base,
                              uint16 pin,
                              Siul2_Port_Ip_PortPullConfig pullConfig
                             )
{
    uint32 regVal;
    uint32 pueVal;
    uint32 pusVal;

    SIUL2_PORT_IP_DEV_ASSERT((boolean)(base != NULL_PTR));
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* If that pin belongs to SIUL2_AE*/
#ifdef FEATURE_SIUL2_HAS_AE_INSTANCE
    if ((uint32)base > (uint32)SIUL2_AE)
    {
        pueVal = SIUL2_AE_MSCR_PUE_MASK;
        pusVal = SIUL2_AE_MSCR_PUS_MASK;
    }
    else
#endif /* FEATURE_SIUL2_HAS_AE_INSTANCE */
    {
        pueVal = SIUL2_MSCR_PUE_MASK;
        pusVal = SIUL2_MSCR_PUS_MASK;
    }

    /* Enter critical region */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_01();
    switch (pullConfig)
    {
        case PORT_INTERNAL_PULL_NOT_ENABLED:
        {
            /* Clear the Pull Enable bit field */
            base->MSCR[pin] &= ~pueVal;
            break;
        }

        case PORT_INTERNAL_PULL_DOWN_ENABLED:
        {
            regVal = base->MSCR[pin];
            /* Set the Pull Enable bit field */
            regVal |= pueVal;
            /* Clear the Pull Select bit field */
            regVal &= ~pusVal;
            base->MSCR[pin] = regVal;
            break;
        }
        case PORT_INTERNAL_PULL_UP_ENABLED:
        {
            regVal = base->MSCR[pin];
            /* Set the Pull Enable bit field */
            regVal |= pueVal;
            /* Set the Pull Select bit field */
            regVal |= pusVal;
            base->MSCR[pin] = regVal;
            break;
        }

        default:
            /* Invalid command */
            SIUL2_PORT_IP_DEV_ASSERT(FALSE);
            break;
    }
    /* Exit critical region */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_01();

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetOutputBuffer
 * Description   : This function configures the output buffer.
 *
 * @implements Siul2_Port_Ip_SetOutputBuffer_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetOutputBuffer(Siul2_Port_Ip_PortType * const base,
                                   uint16 pin,
                                   boolean enable,
                                   Siul2_Port_Ip_PortMux mux
                                  )
{
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(base != NULL_PTR));
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* Enter critical region */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_02();

    /* Clear the OBE bit field */
    base->MSCR[pin] &= ~SIUL2_MSCR_OBE_MASK;
    /* Write the OBE bit field with enable */
    base->MSCR[pin] |= SIUL2_MSCR_OBE(enable ? 1UL : 0UL);

    /* Clear the SSS bit field */
    base->MSCR[pin] &= ~SIUL2_MSCR_SSS_MASK;
    /* Write the SSS bit field with mux */
    base->MSCR[pin] |= SIUL2_MSCR_SSS(mux);

    /* Exit critical region */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_02();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetInputBuffer
 * Description   : This function configures the input buffer.
 *
 * @implements Siul2_Port_Ip_SetInputBuffer_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetInputBuffer(Siul2_Port_Ip_PortType * const base,
                                  uint16 pin,
                                  boolean enable,
                                  uint32 inputMuxReg,
                                  Siul2_Port_Ip_PortInputMux inputMux
                                 )
{
    /* Dummy address */
    SIUL2_Type * siul2Base = (SIUL2_Type *)0xFFFFFFFFU;
    uint32 imcrRegIdx = inputMuxReg;
    uint32 imcrVal;
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* Enter critical region */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_03();

    if (base != NULL_PTR)
    {
        /* Enable/disable input buffer for input signal */
        base->MSCR[pin] &= ~SIUL2_MSCR_IBE_MASK;
        base->MSCR[pin] |= SIUL2_MSCR_IBE(enable ? 1UL : 0UL);
    }

    /* Check input mux to configure input signal */
    if (inputMux != PORT_INPUT_MUX_NO_INIT)
    {
        if (imcrRegIdx < SIUL2_MAX_NUM_OF_IMCR_REG)
        {
#ifdef IP_SIUL2_0_BASE
            siul2Base = (SIUL2_Type *)IP_SIUL2_0_BASE;
#endif /* IP_SIUL2_0_BASE */
#ifdef IP_SIUL2_BASE
            siul2Base = (SIUL2_Type *)IP_SIUL2_BASE;
#endif /* IP_SIUL2_BASE */
        }
#ifdef IP_SIUL2_1_BASE
        else
        {
            siul2Base = (SIUL2_Type *)IP_SIUL2_1_BASE;
        }
#endif /* IP_SIUL2_1_BASE */
        if (imcrRegIdx < SIUL2_IMCR_COUNT)
        {
            /* Configure input mux */
            imcrVal  = siul2Base->IMCR[imcrRegIdx % SIUL2_MAX_NUM_OF_IMCR_REG];
            imcrVal &= ~SIUL2_IMCR_SSS_MASK;
            imcrVal |= SIUL2_IMCR_SSS(inputMux);
            siul2Base->IMCR[imcrRegIdx % SIUL2_MAX_NUM_OF_IMCR_REG] = imcrVal;
        }
    }

    /* Exit critical region */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_03();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetPinDirection
 * Description   : This function configures the pin direction
 *
 * @implements Siul2_Port_Ip_SetPinDirection_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetPinDirection(Siul2_Port_Ip_PortType * const base,
                                   uint16 pin,
                                   Siul2_Port_Ip_PortDirectionType direction
                                  )
{
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(base != NULL_PTR));
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* Enter critical region */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_04();

    switch (direction)
    {
    /* Direction pin IN */
    case SIUL2_PORT_IN:
        base->MSCR[pin] &= ~SIUL2_MSCR_OBE_MASK;
        base->MSCR[pin] |= SIUL2_MSCR_IBE(1UL);
        break;
    /* Direction pin OUT */
    case SIUL2_PORT_OUT:
        base->MSCR[pin] &= ~SIUL2_MSCR_IBE_MASK;
        base->MSCR[pin] |= SIUL2_MSCR_OBE(1UL);
        break;
    /* Direction pin IN OUT */
    case SIUL2_PORT_IN_OUT:
        base->MSCR[pin] |= (SIUL2_MSCR_IBE_MASK | SIUL2_MSCR_OBE_MASK);
        break;
    /* Direction pin HI_Z */
    case SIUL2_PORT_HI_Z:
        base->MSCR[pin] &= ~(SIUL2_MSCR_IBE_MASK | SIUL2_MSCR_OBE_MASK);
        break;
    default:
        /* Do nothing */
        break;
    }

    /* Exit critical region */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_04();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_RevertPinConfiguration
 * Description   : This function configures the pin configuration with the values from the configuration structure
 *
 * @implements Siul2_Port_Ip_RevertPinConfiguration_Activity
 *END**************************************************************************/
uint32 Siul2_Port_Ip_RevertPinConfiguration(const Siul2_Port_Ip_PortType * const base, uint16 pin)
{
    uint32 u32PinIdx;
    uint32 u32RegVal = 0xFFFFFFFFUL;
    const Siul2_Port_Ip_PinSettingsConfig * ConfigPtr = pPort_Setting;
    uint32 MaxPinConfigured = u32MaxPinConfigured;
    uint32 portNumber;
    uint32 u32MscrId;

    SIUL2_PORT_IP_DEV_ASSERT((boolean)(base != NULL_PTR));
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* Get the PortID:  Subtract the address of the first mscr from the base parameter then divide to 4 and 16 because there are 16 ports but each MSCR has 4 bytes */
#if (2 == SIUL2_NUM_SIUL2_INSTANCES_U8)
    /* Check if that pin belongs to SIUL2_1 or SIUL2_0 */
    if (base > (Siul2_Port_Ip_PortType *)IP_SIUL2_1_BASE)
    {
        portNumber = (uint32)((uint32)((uint32)((uint32)base - (uint32)SIUL2_1_MSCR_BASE) >> 2U) >> 4U);
    }
    else
    {
        portNumber = (uint32)((uint32)((uint32)((uint32)base - (uint32)SIUL2_0_MSCR_BASE) >> 2U) >> 4U);
    }
#else
    portNumber = (uint32)((uint32)((uint32)((uint32)base - (uint32)SIUL2_MSCR_BASE) >> 2U) >> 4U);
#endif

    /* Get the MscrID: 16 is the maximum number of pins per port so the portNumber need to multiply 16 */
    u32MscrId = (portNumber << 4U) + (uint32)pin;

    /* The loop to find the Mscr Id in pin configuration's structure */
    for (u32PinIdx = 0U; u32PinIdx < MaxPinConfigured; u32PinIdx++)
    {
        /* If we found that pin */
        if (ConfigPtr[u32PinIdx].pinPortIdx == u32MscrId)
        {
            Siul2_Port_Ip_PinInit(&ConfigPtr[u32PinIdx]);
            u32RegVal = base->MSCR[pin];
            /* Break the loop. Do not need to search in all pin configuration's structure */
            break;
        }
    }
    /* Return the MSCR value */
    return u32RegVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_GetPinConfiguration
 * Description   : This function returns the value of the pin configuration register.
 *
 * @implements Siul2_Port_Ip_GetPinConfiguration_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_GetPinConfiguration(const Siul2_Port_Ip_PortType * const base,
                                       Siul2_Port_Ip_PinSettingsConfig * config,
                                       uint16 pin
                                      )
{
    const Siul2_Port_Ip_PinSettingsConfig * ConfigPtr = pPort_Setting;
    uint32 MaxPinConfigured = u32MaxPinConfigured;
    uint32 portNumber;
    uint32 u32MscrId;
    uint32 u32MscrBase;
    uint32 u32PinIdx;
    uint8 inputMuxIterator;

    SIUL2_PORT_IP_DEV_ASSERT((boolean)(base != NULL_PTR));
    SIUL2_PORT_IP_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* Choose the MSCR base address for the pin */
#if (2 == SIUL2_NUM_SIUL2_INSTANCES_U8)
    if (base > (Siul2_Port_Ip_PortType *)IP_SIUL2_1_BASE)
    {
        u32MscrBase = (uint32)SIUL2_1_MSCR_BASE;
    }
    else
    {
        u32MscrBase = (uint32)SIUL2_0_MSCR_BASE;
    }
#else
    u32MscrBase = (uint32)SIUL2_MSCR_BASE;
#endif

    /* Get the PortID:  Subtract the address of the first mscr from the base parameter then divide to 4 and 16 because there are 16 ports and each MSCR has 4 bytes */
    portNumber = (uint32)((uint32)base - u32MscrBase) / 64UL;
    /* Get the MscrID: 16 is the maximum number of pins per port so the portNumber need to multiply 16 */
    u32MscrId = (portNumber << 4U) + (uint32)pin;

    for (u32PinIdx = 0U; u32PinIdx < MaxPinConfigured; u32PinIdx++)
    {
        /* If that pin was found */
        if (ConfigPtr[u32PinIdx].pinPortIdx == u32MscrId)
        {
            config->base = ConfigPtr[u32PinIdx].base;
            config->pinPortIdx = ConfigPtr[u32PinIdx].pinPortIdx;
            config->initValue = ConfigPtr[u32PinIdx].initValue;

            for (inputMuxIterator = 0U; inputMuxIterator < FEATURE_SIUL2_MAX_NUMBER_OF_INPUT; inputMuxIterator++)
            {
                config->inputMuxReg[inputMuxIterator] = ConfigPtr[u32PinIdx].inputMuxReg[inputMuxIterator];
                config->inputMux[inputMuxIterator] = ConfigPtr[u32PinIdx].inputMux[inputMuxIterator];
            }

            /* Get the MSCR configuration from register */
            Siul2_Port_Ip_GetMSCRConfiguration(config, base, pin);
            break;
        }
    }
}

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
