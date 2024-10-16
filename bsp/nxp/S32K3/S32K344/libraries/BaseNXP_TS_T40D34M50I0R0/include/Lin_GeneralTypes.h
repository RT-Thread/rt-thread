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
*   @file    Lin_GeneralTypes.h
*   @implements     Lin_GeneralTypes.h_Artifact
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - General Types.
*   @details API header for all types and constants that are shared among the AUTOSAR LIN modules
*            Lin, LinIf and LinTrcv.
*            This file contains sample code only. It is not part of the production code deliverables
*   @addtogroup BASENXP_COMPONENT
*   @{
*/


#ifndef LIN_GENERAL_TYPES_H
#define LIN_GENERAL_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** 
@{
* @brief Parameters that shall be published within the modules header file.
*       The integration of incompatible files shall be avoided.
*/
#define LIN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION      4
#define LIN_GENERALTYPES_AR_RELEASE_MINOR_VERSION      7
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
/**
* @brief          Checksum models for the LIN Frame.
* @details        This type is used to specify the Checksum model to be
*                 used for the LIN Frame.
* @implements     Lin_FrameCsModelType_enum
*/
typedef enum
    {
    LIN_ENHANCED_CS,    /**< @brief Enhanced checksum model.*/
    LIN_CLASSIC_CS      /**< @brief Classic checksum model.*/
    } Lin_FrameCsModelType;

/**
* @brief          Frame response types.
* @details        This type is used to specify whether the frame
*                 processor is required to transmit the response
*                 part of the LIN frame.
* @implements     Lin_FrameResponseType_enum
*/

typedef enum
    {
    LIN_FRAMERESPONSE_TX = 0,   /**< @brief Response is generated from this node*/
    LIN_FRAMERESPONSE_RX,       /**< @brief Response is generated from another node and is
                                    relevant for this node.*/
    LIN_FRAMERESPONSE_IGNORE    /**< @brief Response is generated from another node and is
                                    irrelevant for this node*/
    } Lin_FrameResponseType;

/**
* @brief          LIN Frame and Channel states operation.
* @details        LIN operation states for a LIN channel or frame, as returned
*                 by the API service Lin_GetStatus().
*                 part of the LIN frame.
* @implements     Lin_StatusType_enum
*/
typedef enum
    {
    LIN_NOT_OK = 0,     /**< @brief Development or production error
                                    occurred.*/
    LIN_TX_OK,          /**< @brief Successful transmission.*/
    LIN_TX_BUSY,        /**< @brief Ongoing transmission (Header or
                                    Response).*/
    LIN_TX_HEADER_ERROR,/**< @brief Erroneous header transmission such
                                    as:
                                     - Mismatch between sent and read
                                       back data
                                     - Identifier parity error
                                     - Physical bus error.*/
    LIN_TX_ERROR,       /**< @brief Erroneous transmission such as:
                                     - Mismatch between sent and read
                                       back data
                                     - Physical bus error.*/
    LIN_RX_OK,          /**< @brief Reception of correct response.*/
    LIN_RX_BUSY,        /**< @brief Ongoing reception:
                                    at least one response byte has
                                    been received, but the checksum
                                    byte has not been received.*/
    LIN_RX_ERROR,       /**< @brief Erroneous reception such as:
                                     - Framing error
                                     - Overrun error
                                     - Checksum error
                                     - Short response.*/
    LIN_RX_NO_RESPONSE, /**< @brief No response byte has been received
                                    so far.*/
                        /**< @brief This is a mess !!
                                   Frame status is mixed with channel
                                   status but i kept it here only
                                   because of LIN168.*/
    LIN_OPERATIONAL,    /**< @brief Normal operation;
                                     - The related LIN channel is ready
                                       to transmit next header
                                     - No data from previous frame
                                       available (e.g. after
                                       initialization).*/
    LIN_CH_SLEEP        /**< @brief Sleep mode operation;
                                     - In this mode wake-up detection
                                       from slave nodes is enabled.*/
    } Lin_StatusType;
    
/**
* @brief          LIN Slave error type.
* @details        This type represents the slave error types that are detected during header reception
*                 and response transmission / reception
* @implements     Lin_SlaveErrorType_enum
*/

typedef enum
    {
        LIN_ERR_HEADER = 0, /**< @brief Error in header */
        
        LIN_ERR_RESP_STOPBIT, /**< @brief Framing error in response */
        
        LIN_ERR_RESP_CHKSUM, /**< @brief Checksum error */
        
        LIN_ERR_RESP_DATABIT, /**< @brief Monitoring error of transmitted data bit in response */
        
        LIN_ERR_NO_RESP, /**< @brief No response */
        
        LIN_ERR_INC_RESP /**< @brief Incomplete response */
        
    } Lin_SlaveErrorType;    

/**
* @brief          Transceiver Wake Up Mode Types.
* @details        Wake up operating modes of the LIN Transceiver Driver.
*/

typedef enum
    {
    LINTRCV_WUMODE_ENABLE,      /**< @brief The notification for wakeup events is enabled
                                            on the addressed network.*/
    LINTRCV_WUMODE_DISABLE,     /**< @brief The notification for wakeup events is disabled
                                            on the addressed network.*/
    LINTRCV_WUMODE_CLEAR        /**< @brief A stored wakeup event is cleared
                                            on the addressed network.*/
    } LinTrcv_TrcvWakeupModeType;
    
/**
* @brief          Transceiver Wake Up Reason Types.
* @details        This type denotes the wake up reason detected by the LIN transceiver.
*/

typedef enum
    {
    LINTRCV_WU_ERROR,               /**< @brief Due to an error wake up reason was not detected. */
    
    LINTRCV_WU_NOT_SUPPORTED,       /**< @brief The transceiver does not support any information
                                                for the wake up reason.*/
    LINTRCV_WU_BY_BUS,              /**< @brief The transceiver has detected, that the network
                                                has caused the wake up of the ECU.*/
    LINTRCV_WU_BY_PIN,              /**< @brief The transceiver has detected a wake-up event at
                                                one of the transceiver's pins (not at the LIN bus).*/
    LINTRCV_WU_INTERNALLY,          /**< @brief The transceiver has detected, that the network has been woken up
                                                by the ECU via a request to NORMAL mode.*/
    LINTRCV_WU_RESET,               /**< @brief The transceiver has detected, that the wake up is
                                                due to an ECU reset.*/
    LINTRCV_WU_POWER_ON             /**< @brief The transceiver has detected, that the wake up is
                                                due to an ECU reset after power on.*/
    } LinTrcv_TrcvWakeupReasonType;

/**
* @brief          Operating modes of the LIN Transceiver Driver.
*/

typedef enum
{
    LINTRCV_TRCV_MODE_NORMAL    = (uint8)0x00U, /**< @brief Transceiver mode NORMAL */
    LINTRCV_TRCV_MODE_STANDBY   = (uint8)0x01U,  /**< @brief Transceiver mode STANDBY */
    LINTRCV_TRCV_MODE_SLEEP     = (uint8)0x02U  /**< @brief Transceiver mode SLEEP */
} LinTrcv_TrcvModeType;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          Data length of a LIN Frame.
* @details        This type is used to specify the number of SDU
*                 data bytes to copy.
* @implements     Lin_FrameDlType_typedef
*/
typedef uint8 Lin_FrameDlType;

/**
* @brief          The LIN identifier (0..0x3F) with its parity bits.
* @details        Represents all valid protected Identifier used by
*                 Lin_SendFrame().
* @implements     Lin_FramePidType_typedef
*/
typedef uint8 Lin_FramePidType;

/**
* @brief          The LIN identifier (0..0x3F) with its parity bits.
* @details        This Type is used to provide PID, checksum model,
*                 data length and SDU pointer from the LIN Interface
*                 to the LIN driver.
* @implements     Lin_PduType_struct
*/
typedef struct
    {
    Lin_FramePidType      Pid;     /**< @brief LIN frame identifier.*/
    Lin_FrameCsModelType  Cs;      /**< @brief Checksum model type.*/
    Lin_FrameResponseType Drc;     /**< @brief Response type.*/
    Lin_FrameDlType       Dl;      /**< @brief Data length.*/
    uint8*                SduPtr;  /**< @brief Pointer to Sdu.*/
    } Lin_PduType;
/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* LIN_GENERAL_TYPES_H */

/** @} */
