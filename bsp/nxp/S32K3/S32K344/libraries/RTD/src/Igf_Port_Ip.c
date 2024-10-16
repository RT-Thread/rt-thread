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
*   @file    Igf_Port_Ip.c
*
*   @addtogroup Igf_IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Igf_Port_Ip.h"
#include "SchM_Port.h"

/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/*
* @brief Parameters that shall be published within the driver header file and also in the
* module's description file
*/
#define IGF_PORT_IP_VENDOR_ID_C                     43
#define IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_C      4
#define IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_C      7
#define IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_C   0
#define IGF_PORT_IP_SW_MAJOR_VERSION_C              5
#define IGF_PORT_IP_SW_MINOR_VERSION_C              0
#define IGF_PORT_IP_SW_PATCH_VERSION_C              0

/*=================================================================================================
*                                      FILE VERSION CHECKS
=================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Igf_Port_Ip.c and SchM_Port.h are of the same AutoSar version */
    #if ((IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_PORT_AR_RELEASE_MAJOR_VERSION) || \
         (IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_PORT_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Igf_Port_Ip.c and SchM_Port.h are different"
    #endif
#endif

/* Check if the files Igf_Port_Ip.c and Igf_Port_Ip.h are of the same version */
#if (IGF_PORT_IP_VENDOR_ID_C != IGF_PORT_IP_VENDOR_ID_H)
    #error "Igf_Port_Ip.c and Igf_Port_Ip.h have different vendor ids"
#endif
/* Check if Igf_Port_Ip.c and Igf_Port_Ip.h are of the same Autosar version */
#if ((IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_C    != IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_H)  || \
     (IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_C    != IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_H)   || \
     (IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_C != IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Igf_Port_Ip.c and Igf_Port_Ip.h are different"
#endif
/* Check if Igf_Port_Ip.c and Igf_Port_Ip.h are of the same Software version */
#if ((IGF_PORT_IP_SW_MAJOR_VERSION_C != IGF_PORT_IP_SW_MAJOR_VERSION_H) || \
     (IGF_PORT_IP_SW_MINOR_VERSION_C != IGF_PORT_IP_SW_MINOR_VERSION_H) || \
     (IGF_PORT_IP_SW_PATCH_VERSION_C != IGF_PORT_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Igf_Port_Ip.c and Igf_Port_Ip.h are different"
#endif
/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL VARIABLES
=================================================================================================*/
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER
#define PORT_START_SEC_CONST_32
#include "Port_MemMap.h"

/**
* @brief IGF base address array declaration
*/
const uint32 Port_au32IgfBaseAddr[] =
{
#ifdef  IP_IGF_BASE
    IP_IGF_BASE
#endif
};

#define PORT_STOP_SEC_CONST_32
#include "Port_MemMap.h"
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER */

/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
                                       LOCAL FUNCTIONS
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL FUNCTIONS
=================================================================================================*/
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/**
* @brief        Initializes the IGF IP Driver
* @details      The function Port_Igf_Init will initialize ALL IGF channels with the
*               configuration set pointed to by the parameter pIgfConfigPtr.
*
* @param[in]    pIgfConfigPtr  A pointer to the structure which contains initialization parameters
*
* @return none
*
* @pre    none
*
*
*/
void Igf_Port_Ip_Init(uint8 u8NumChannels, const Igf_Port_Ip_ChannelConfigType *pIgfConfigPtr)
{
    uint8   u8ChannelIndex;
    uint32  u32RegValue;
    uint8   u8IfgInstance;
    uint8   u8IgfChannel;
#ifdef IP_IGF_BASE
    IGF_Type * base = (IGF_Type *)IP_IGF_BASE;
#endif /* IP_IGF_BASE */

    /* Initialize all IGF channels present in the configuration */
    for (u8ChannelIndex = (uint8)0U; u8ChannelIndex < u8NumChannels; u8ChannelIndex++)
    {
        u8IfgInstance = (uint8)pIgfConfigPtr[u8ChannelIndex].u8IgfInstance;
        u8IgfChannel = (uint8)pIgfConfigPtr[u8ChannelIndex].u8IgfChannel;
        base = (IGF_Type *)Port_au32IgfBaseAddr[u8IfgInstance];

        /* Enter critical region */
        SchM_Enter_Port_PORT_EXCLUSIVE_AREA_11();
        /* Make sure that the IGF channel is disabled so we can update it with the configuration params */
        base->MCR[u8IgfChannel].MCR &= ~(IGF_MCR_FGEN_MASK);
        /* Exit critical region */
        SchM_Exit_Port_PORT_EXCLUSIVE_AREA_11();

        /* Prepare and write the MCR register */
        u32RegValue = (uint32)pIgfConfigPtr[u8ChannelIndex].u32IgfMCR;
        base->MCR[u8IgfChannel].MCR = u32RegValue;

        /* Prepare and write the PRESR register, only if the register should be configured */
        u32RegValue = (uint32)pIgfConfigPtr[u8ChannelIndex].u32IgfPRESR;
        if (IGF_PORT_IP_REG_NOT_CONFIGURED_U32 != u32RegValue)
        {
            base->MCR[u8IgfChannel].PRESR = u32RegValue;
        }

        /* Prepare and write the RTH register, only if the register should be configured */
        u32RegValue = (uint32)pIgfConfigPtr[u8ChannelIndex].u32IgfRTH;
        if (IGF_PORT_IP_REG_NOT_CONFIGURED_U32 != u32RegValue)
        {
            base->MCR[u8IgfChannel].RTHR = u32RegValue;
        }

        /* Prepare and write the FTH register, only if the register should be configured */
        u32RegValue = (uint32)pIgfConfigPtr[u8ChannelIndex].u32IgfFTH;
        if (IGF_PORT_IP_REG_NOT_CONFIGURED_U32 != u32RegValue)
        {
            base->MCR[u8IgfChannel].FTHR = u32RegValue;
        }

        /* Enter critical region */
        SchM_Enter_Port_PORT_EXCLUSIVE_AREA_11();
        /* Enable the IGF Channel by setting the FGEN bit */
        base->MCR[u8IgfChannel].MCR |= IGF_MCR_FGEN_MASK;
        /* Exit critical region */
        SchM_Exit_Port_PORT_EXCLUSIVE_AREA_11();
    }
}

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER */

#ifdef __cplusplus
}
#endif
/** @} */
