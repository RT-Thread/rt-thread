/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/**
*   @file    Std_Types.h
*   @implements     Std_Types.h_Artifact
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - Standard types definition.
*   @details AUTOSAR standard types header file. It contains all types that are used across several
*                modules of the basic software and that are platform and compiler independent
*
*   @addtogroup BASENXP_COMPONENT
*   @{
*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Platform_Types.h"
/**
* @brief Include compiler abstraction
*/
#include "Compiler.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the standard types header file and also in the
*        module's description file
*/
#define STD_VENDOR_ID                     43
#define STD_AR_RELEASE_MAJOR_VERSION      4
#define STD_AR_RELEASE_MINOR_VERSION      7
#define STD_AR_RELEASE_REVISION_VERSION   0
#define STD_SW_MAJOR_VERSION              5
#define STD_SW_MINOR_VERSION              0
#define STD_SW_PATCH_VERSION              0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Platform_Types header file are of the same Autosar version */
#if ((STD_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
    (STD_AR_RELEASE_MINOR_VERSION  != PLATFORM_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Std_Types.h and Platform_Types.h are different"
#endif
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Compiler header file are of the same Autosar version */
#if ((STD_AR_RELEASE_MAJOR_VERSION != COMPILER_AR_RELEASE_MAJOR_VERSION) || \
    (STD_AR_RELEASE_MINOR_VERSION  != COMPILER_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Std_Types.h and Compiler.h are different"
#endif
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/**
* @brief Physical state 5V or 3.3V
* @implements SymbolDefinitions_enum
*/
#define STD_HIGH    0x01U

/**
* @brief Physical state 0V.
* @implements SymbolDefinitions_enum
*/
#define STD_LOW     0x00U

/**
* @brief Logical state active.
* @implements SymbolDefinitions_enum
*/
#define STD_ACTIVE  0x01U

/**
* @brief Logical state idle.
* @implements SymbolDefinitions_enum
*/
#define STD_IDLE    0x00U

/**
* @brief ON State.
* @implements SymbolDefinitions_enum
*/
#define STD_ON      0x01U

/**
* @brief OFF state.
* @implements SymbolDefinitions_enum
*/
#define STD_OFF     0x00U

/**
* @brief Return code for failure/error.
* @implements SymbolDefinitions_enum
*/
#define E_NOT_OK    0x01U

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/**
* @brief According to SWS_Mem_00070: In case a service is not relevant for a specific memory device technology, 
*        the service shall always return E_MEM_SERVICE_NOT_AVAIL.
*        The return code is implementation-defined (see SWS_Std_00011 and SWS_Std_00005).
* @implements SymbolDefinitions_enum
*/
#define E_MEM_SERVICE_NOT_AVAIL    0x02U

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief Because E_OK is already defined within OSEK, the symbol E_OK has to be shared. To avoid
*        name clashes and redefinition problems, the symbols have to be defined in the following way
*       (approved within implementation).
*/
#ifndef STATUSTYPEDEFINED
    #define STATUSTYPEDEFINED
    /**
    * @brief Success return code
    */
    #define E_OK      0x00U
    /**
    * @brief This type is defined for OSEK compliance.
    */
    typedef uint8 StatusType;
#endif

/**
* @brief This type can be used as standard API return type which is shared between the RTE and the
*        BSW modules.
*/
/* @implements Std_ReturnType_type */
typedef uint8 Std_ReturnType;

/**
* @brief This type shall be used to request the version of a BSW module using the
*       "ModuleName"_GetVersionInfo() function.
*/
/* @implements Std_VersionInfoType_structure */
typedef struct
{
    uint16  vendorID;               /**< @brief vendor ID */
    uint16  moduleID;               /**< @brief BSW module ID */
    uint8   sw_major_version;       /**< @brief BSW module software major version */
    uint8   sw_minor_version;       /**< @brief BSW module software minor version */
    uint8   sw_patch_version;       /**< @brief BSW module software patch version */
} Std_VersionInfoType;

/**
* @brief The type of the Std_TransformerError.
* @implements Std_TransformerErrorCode_type 
*/
typedef uint8 Std_TransformerErrorCode;

/**
* @brief The Std_TransformerClass represents the transformer class in which the error occurred.
* @implements Std_TransformerClass_enum 
*/
typedef enum
{
    STD_TRANSFORMER_UNSPECIFIED = (uint8)0x00, /**< @brief Transformer of a unspecified transformer class.*/
    STD_TRANSFORMER_SERIALIZER = (uint8)0x01,  /**< @brief Transformer of a serializer class. */
    STD_TRANSFORMER_SAFETY = (uint8)0x02,      /**< @brief Transformer of a safety class. */
    STD_TRANSFORMER_SECURITY = (uint8)0x03,    /**< @brief Transformer of a security class. */
    STD_TRANSFORMER_CUSTOM = (uint8)0xFF       /**< @brief Transformer of a custom class not standardized by AUTOSAR.*/
} Std_TransformerClass;

/**
* @brief Std_TransformerError represents a transformer error in the context of a certain transformer chain.
*
* @implements Std_TransformerError_structure */
typedef struct
{   
    Std_TransformerErrorCode errorCode;          /**< @brief The specific meaning of the values of Std_TransformerErrorCode is to be seen for the specific transformer chain 
                                                 for which the data type represents the transformer error. */
    Std_TransformerClass transformerClass;       /**< @brief The transformerClass */
} Std_TransformerError;

/**
* @brief This type can be used as standard API return type which is shared between the RTE and the
*        BSW modules.
* @implements Std_TransformerForwardCode_enum 
*/
typedef enum
{
    ERROR_OK                 = (uint8)0x00,      /**< @brief No specific error to be injected.*/
    E_SAFETY_INVALID_REP = (uint8)0x01,      /**< @brief Repeat the last used sequence number. */
    E_SAFETY_INVALID_SEQ = (uint8)0x02,      /**< @brief Generate a deliberately wrong CRC. */
    E_SAFETY_INVALID_CRC = (uint8)0x03       /**< @brief Use a wrong sequence number. */
} Std_TransformerForwardCode;

/**
* @brief Std_TransformerError represents a transformer error in the context of a certain transformer chain.
*
* @implements Std_TransformerForward_structure */
typedef struct
{   
    Std_TransformerForwardCode errorCode;          /**< @brief The specific meaning of the values of Std_TransformerErrorCode is to be seen for the specific transformer chain 
                                                 for which the data type represents the transformer error. */
    Std_TransformerClass transformerClass;       /**< @brief The transformerClass */
} Std_TransformerForward;

/**
* @brief This type is used to encode the different type of messages. - Currently this encoding is limited to
* the distinction between requests and responses in C/S communication.
*
* @implements Std_MessageTypeType_enum 
*/
typedef enum
{
    STD_MESSAGETYPE_REQUEST  = (uint8)0x00,      /**< @brief Message type for a request message.*/
    STD_MESSAGETYPE_RESPONSE = (uint8)0x01,      /**< @brief Message type for a response message. */
} Std_MessageTypeType;

/**
* @brief This type is used to encode different types of results for response messages. - Currently this
* encoding is limited to the distinction between OK and ERROR responses.
*
* @implements Std_MessageResultType_enum 
*/
typedef enum
{
    STD_MESSAGERESULT_OK    = (uint8)0x00,      /**< @brief STD_MESSAGERESULT_OK.*/
    STD_MESSAGERESULT_ERROR = (uint8)0x01,      /**< @brief Messageresult for an ERROR response. */
} Std_MessageResultType;

/**
* @brief Type for the function pointer to extract the relevant protocol header fields of the message and
* the type of the message result of a transformer. - At the time being, this is limited to the types
* used for C/S communication (i.e., REQUEST and RESPONSE and OK and ERROR)
*
* @implements Std_ExtractProtocolHeaderFieldsType_structure 
*/
typedef Std_ReturnType (*Std_ExtractProtocolHeaderFieldsType)(
    const uint8* buffer,                                        /**< @brief Buffer allocated by the RTE, where the transformed data has to be stored by the transformer */
    uint32 bufferLength,                                        /**< @brief Length of the buffer */
    Std_MessageTypeType* messageType,                           /**< @brief Canonical representation of the message type (extracted from the transformers protocol header)*/
    Std_MessageResultType* messageResult                        /**< @brief Canonical representation of the message result type (extracted from the transformers protocol header)*/
);

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STD_TYPES_H */

/** @} */
