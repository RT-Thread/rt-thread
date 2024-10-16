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

#ifndef SIUL2_PORT_IP_H
#define SIUL2_PORT_IP_H

/**
*   @file    Siul2_Port_Ip.h
*
*   @defgroup Port_IPL Port IPL
*   @{
*/

#if defined(__cplusplus)
extern "C" {
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Std_Types.h"
#include "Siul2_Port_Ip_Cfg.h"
#include "Siul2_Port_Ip_Types.h"
#include "Siul2_Port_Ip_Defines.h"
#include "Devassert.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
 * @brief Parameters that shall be published within the driver header file and also in the
 *        module's description file
 */
#define SIUL2_PORT_IP_VENDOR_ID_H                     43
#define SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H      4
#define SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H      7
#define SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_H   0
#define SIUL2_PORT_IP_SW_MAJOR_VERSION_H              5
#define SIUL2_PORT_IP_SW_MINOR_VERSION_H              0
#define SIUL2_PORT_IP_SW_PATCH_VERSION_H              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Siul2_Port_Ip.h and Std_Types.h are of the same version */
    #if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H != STD_AR_RELEASE_MAJOR_VERSION) || \
         (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Siul2_Port_Ip.h and Std_Types.h are different"
    #endif
    /* Check if the files Siul2_Port_Ip.h and Devassert.h are of the same version */
    #if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
         (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H != DEVASSERT_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Siul2_Port_Ip.h and Devassert.h are different"
    #endif
#endif

/* Check if the files Siul2_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same version */
#if (SIUL2_PORT_IP_VENDOR_ID_H != SIUL2_PORT_IP_VENDOR_ID_CFG_H)
    #error "Siul2_Port_Ip.h and Siul2_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Siul2_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_H != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip.h and Siul2_Port_Ip_Cfg.h are different"
#endif
/* Check if Siul2_Port_Ip.h and Siul2_Port_Ip_Cfg.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_H != SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
     (SIUL2_PORT_IP_SW_MINOR_VERSION_H != SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
     (SIUL2_PORT_IP_SW_PATCH_VERSION_H != SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip.h and Siul2_Port_Ip_Cfg.h are different"
#endif

/* Check if the files Siul2_Port_Ip.h and Siul2_Port_Ip_Types.h are of the same version */
#if (SIUL2_PORT_IP_VENDOR_ID_H != SIUL2_PORT_IP_TYPES_VENDOR_ID_H)
    #error "Siul2_Port_Ip.h and Siul2_Port_Ip_Types.h have different vendor ids"
#endif
/* Check if Siul2_Port_Ip.h and Siul2_Port_Ip_Types.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != SIUL2_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != SIUL2_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_H != SIUL2_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip.h and Siul2_Port_Ip_Types.h are different"
#endif
/* Check if Siul2_Port_Ip.h and Siul2_Port_Ip_Types.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_H != SIUL2_PORT_IP_TYPES_SW_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_MINOR_VERSION_H != SIUL2_PORT_IP_TYPES_SW_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_PATCH_VERSION_H != SIUL2_PORT_IP_TYPES_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip.h and Siul2_Port_Ip_Types.h are different"
#endif

/* Check if the files Siul2_Port_Ip.h and Siul2_Port_Ip_Defines.h are of the same version */
#if (SIUL2_PORT_IP_VENDOR_ID_H != SIUL2_PORT_IP_DEFINES_VENDOR_ID_H)
    #error "Siul2_Port_Ip.h and Siul2_Port_Ip_Defines.h have different vendor ids"
#endif
/* Check if Siul2_Port_Ip.h and Siul2_Port_Ip_Defines.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H    != SIUL2_PORT_IP_DEFINES_AR_RELEASE_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H    != SIUL2_PORT_IP_DEFINES_AR_RELEASE_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_H != SIUL2_PORT_IP_DEFINES_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip.h and Siul2_Port_Ip_Defines.h are different"
#endif
/* Check if Siul2_Port_Ip.h and Siul2_Port_Ip_Defines.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_H != SIUL2_PORT_IP_DEFINES_SW_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_MINOR_VERSION_H != SIUL2_PORT_IP_DEFINES_SW_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_PATCH_VERSION_H != SIUL2_PORT_IP_DEFINES_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip.h and Siul2_Port_Ip_Defines.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#if (STD_ON == PORT_VIRTWRAPPER_SUPPORT)
/**
* @brief Base address array for Siul2 instances
*/
extern const uint32 Port_au32Siul2BaseAddr[][SIUL2_PDAC_SLOT_NUM];
#else
/**
* @brief Base address array for Siul2 instances
*/
extern const uint32 Port_au32Siul2BaseAddr[];
#endif /* STD_ON == PORT_VIRTWRAPPER_SUPPORT */
#define PORT_WRITE8(address, value)        ((*(volatile uint8*)(address))=  (value))

#define PORT_WRITE32(address, value)       ((*(volatile uint32*)(address))= (value))
#define PORT_READ32(address)              (*(volatile uint32*)(address))

#if (STD_ON == PORT_VIRTWRAPPER_SUPPORT)
    #define SIUL2_MSCR_ADDR32(INSTANCE, PDAC, PIN)  ((uint32)Port_au32Siul2BaseAddr[(INSTANCE)][(PDAC)] + (uint32)0x0240UL + (uint32)((PIN)<<2))
    #define SIUL2_IMCR_ADDR32(INSTANCE,PDAC, PIN)  ((uint32)Port_au32Siul2BaseAddr[(INSTANCE)][(PDAC)] + (uint32)0x0A40UL + (uint32)((PIN)<<2))
    #define SIUL2_GPDO_ADDR8(INSTANCE, PDAC, PIN)  ((uint32)Port_au32Siul2BaseAddr[(INSTANCE)][(PDAC)] + (uint32)0x1300UL + (((PIN) & ~3UL) | (~((PIN) & 3UL) & 3UL)))
#else
    #define SIUL2_MSCR_ADDR32(INSTANCE, PIN)  ((uint32)Port_au32Siul2BaseAddr[(INSTANCE)] + (uint32)0x0240UL + (uint32)((PIN)<<2))
    #define SIUL2_IMCR_ADDR32(INSTANCE, PIN)  ((uint32)Port_au32Siul2BaseAddr[(INSTANCE)] + (uint32)0x0A40UL + (uint32)((PIN)<<2))
    #define SIUL2_GPDO_ADDR8(INSTANCE, PIN)  ((uint32)Port_au32Siul2BaseAddr[(INSTANCE)] + (uint32)0x1300UL + (((PIN) & ~3UL) | (~((PIN) & 3UL) & 3UL)))
#endif /* STD_ON == PORT_VIRTWRAPPER_SUPPORT */

/* @brief Mask definitions for IMCR bit field SSS */
#define SIUL2_IMCR_SSS_U32                              ((uint32)0x00000007U)
#define SIUL2_IMCR_SSS_OFFSET_U32                       ((uint32)0)

#ifdef SIUL2_PORT_IP_HAS_ADC_INTERLEAVE
#define  DCM_DCMRWF4_ADDR32                  (uint32)&(IP_DCM_GPR->DCMRWF4)
#define  DCM_DCMRWF4_ADC_CLEAR_VALUE_FLAG    (uint32)0x8000UL
#define  DCM_DCMRWF4_ADC_INTERLEAVE_MASK     (uint32)0x0000067EUL   /* Mask all adc interleave bits */
#endif /* SIUL2_PORT_IP_HAS_ADC_INTERLEAVE */
#define  PORT_PIN_LEVEL_NOTCHANGED_U8        ((uint8)2)    /**< @brief Not changed port pin logic. */

#if (SIUL2_PORT_IP_DEV_ERROR_DETECT == STD_ON)
#define SIUL2_PORT_IP_DEV_ASSERT(par) DevAssert(par)
#else
#define SIUL2_PORT_IP_DEV_ASSERT(par)
#endif
#define SIUL2_MAX_NUM_OF_IMCR_REG       512u


/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
/* @brief Allocate defined section for PORT code. */
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/*!
 * @brief Configures the internal resistor.
 *
 * This function configures the internal resistor.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTA_AE, etc.)
 * @param[in] pin Port pin number
 * @param[in] pullConfig The pull configuration
 */
void Siul2_Port_Ip_SetPullSel(Siul2_Port_Ip_PortType * const base,
                         uint16 pin,
                         Siul2_Port_Ip_PortPullConfig pullConfig);

/*!
 * @brief Configures the output buffer and output signal.
 *
 * This function configures the output buffer for the pin
 * and the path for output signal from module to pin
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTA_AE, etc.)
 * @param[in] pin Port pin number
 * @param[in] enable Enable output buffer
 * @param[in] mux Pin muxing slot selection
 */
void Siul2_Port_Ip_SetOutputBuffer(Siul2_Port_Ip_PortType * const base,
                              uint16 pin,
                              boolean enable,
                              Siul2_Port_Ip_PortMux mux);

/*!
 * @brief Configures the input buffer and input signal.
 *
 * This function configures the input buffer for the pin
 * and the path for input signal from pin to module
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTA_AE, etc.),
 *            NULL if disabling inputMux only
 * @param[in] pin Port pin number
 * @param[in] enable Enable input buffer
 * @param[in] inputMuxReg Pin muxing register slot selection
 * @param[in] inputMux Pin muxing slot selection
 *
 * @note: There are some pins controlled by both SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4 and SIUL2_5 instances
 * In order to configure correctly and be consistent with other platforms, the
 * inputMuxReg parameter of SIUL2_3 instance must be added 512 units.
 * For example: The actual inputMuxReg is 10 then the value there must be (10 + 512)
 */
void Siul2_Port_Ip_SetInputBuffer(Siul2_Port_Ip_PortType * const base,
                             uint16 pin,
                             boolean enable,
                             uint32 inputMuxReg,
                             Siul2_Port_Ip_PortInputMux inputMux);

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in] pinCount The number of configured pins in structure
 * @param[in] config The configuration structure
 * @return The status of the operation
 */
Siul2_Port_Ip_PortStatusType Siul2_Port_Ip_Init(uint32 pinCount,
                       const Siul2_Port_Ip_PinSettingsConfig config[]);

/*!
 * @brief Configures the pin with the values form the configuration structure
 *
 * This function configures the pin configuration with the values form the configuration structure
 *
 * @param[in] base Port base pointer
 * @param[in] pin Port pin number
 * @param[in] direction The direction of pin
 * @return void
 */
void Siul2_Port_Ip_SetPinDirection(Siul2_Port_Ip_PortType * const base,
                                   uint16 pin,
                                   Siul2_Port_Ip_PortDirectionType direction);

/*!
 * @brief This function configures the pin configuration with the values from the configuration structure
 *
 * This function configures the pin configuration with the values from the configuration structure
 *
 * @param[in] base Port base pointer
 * @param[in] pin Port pin number
 * @return MSCR register value
 */
uint32 Siul2_Port_Ip_RevertPinConfiguration(const Siul2_Port_Ip_PortType * const base,
                                           uint16 pin);

/*!
 * @brief This function shall return the value of the pin configuration register.
 *
 * This function shall return the value of the pin configuration register.
 *
 * @param[in] base Port base pointer
 * @param[in] pin Port pin number
 * @param[out] config->pointer to output configuration structure information
 * @return MSCR register value
 */
void Siul2_Port_Ip_GetPinConfiguration(const Siul2_Port_Ip_PortType * const base,
                                       Siul2_Port_Ip_PinSettingsConfig * config,
                                       uint16 pin);
#if (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT))
#if (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE))
#if (defined(PORT_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == PORT_SIUL2_REG_PROT_AVAILABLE))
/*!
 * @brief Enables SIUL2 registers writing in User Mode by configuring REG_PROT
 *
  */
void Siul2_Port_Ip_SetUserAccessAllowed(void);
#endif /* (defined(PORT_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == PORT_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT)) */

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#if defined(__cplusplus)
}
#endif

/** @} */

#endif /* SIUL2_PORT_IP_H */
