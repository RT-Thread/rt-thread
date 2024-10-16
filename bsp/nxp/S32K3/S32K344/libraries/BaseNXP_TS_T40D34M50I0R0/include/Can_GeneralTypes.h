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
*   @file    Can_GeneralTypes.h
*   @implements Can_GeneralTypes.h_Artifact
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - General Types.
*   @details API header for all types and constants that are shared among the AUTOSAR CAN
*            modules Can, CanIf and CanTrcv.
*            This file contains sample code only. It is not part of the production code deliverables
*   @addtogroup BASENXP_COMPONENT
*   @{
*/

#ifndef CAN_GENERAL_TYPES_H
#define CAN_GENERAL_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "ComStack_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/** 
@{
* @brief Parameters that shall be published within the modules header file.
*       The integration of incompatible files shall be avoided.
*/
#define CAN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION      4
#define CAN_GENERALTYPES_AR_RELEASE_MINOR_VERSION      7

/**@}*/
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Transmit request could not be processed because no
*        transmit object was available
* @implements SymbolDefinitions_enum
*/
#define CAN_BUSY    0x02
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/**
* @brief          CAN Controller State Modes of operation.
* @details        States that are used by the several ControllerMode functions
* @implements     Can_ControllerStateType_enum
*/
typedef enum
{
    CAN_CS_UNINIT  = 0U,    /**< @brief CAN controller state UNINIT */
    CAN_CS_STARTED,         /**< @brief CAN controller state STARTED */
    CAN_CS_STOPPED,         /**< @brief CAN controller state STOPPED */
    CAN_CS_SLEEP            /**< @brief CAN controller state SLEEP */
} Can_ControllerStateType;

/**
* @brief          CAN Controller State Modes of operation.
* @details        Error states of a CAN controller
* @implements     Can_ErrorStateType_enum
*/
typedef enum
{
    CAN_ERRORSTATE_ACTIVE = 0U,     /**< @brief The CAN controller takes fully part in communication. */
    CAN_ERRORSTATE_PASSIVE,         /**< @brief The CAN controller takes part in communication, but does not send active error frames. */
    CAN_ERRORSTATE_BUSOFF           /**< @brief The CAN controller does not take part in communication. */
} Can_ErrorStateType;

/**
* @brief          CAN Transceiver modes.
* @details        Operating modes of the CAN Transceiver Driver.
*
*/
typedef enum
{
    CANTRCV_TRCVMODE_NORMAL = 0U, /**< @brief Transceiver mode NORMAL */
    CANTRCV_TRCVMODE_STANDBY,     /**< @brief Transceiver mode STANDBY */
    CANTRCV_TRCVMODE_SLEEP        /**< @brief Transceiver mode SLEEP */
} CanTrcv_TrcvModeType;

/**
* @brief          
* @details   This type shall be used to control the CAN transceiver concerning wake up events and wake up notifications.     
* According to [SWS_CanTrcv_00164] it should be present in Can_GeneralTypes.h
*/
typedef enum
{
	CANTRCV_WUMODE_ENABLE = 0x00,   /* The notification for wakeup events is enabled on the addressed transceiver. */
	CANTRCV_WUMODE_DISABLE = 0x01,  /* The notification for wakeup events is disabled on the addressed transceiver. */
	CANTRCV_WUMODE_CLEAR = 0x02	 	/* A stored wakeup event is cleared on the addressed transceiver. */
} CanTrcv_TrcvWakeupModeType;


/**
* @brief          
* @details   This type denotes the wake up reason detected by the CAN transceiver in detail.
* According to [SWS_CanTrcv_00165] it should be present in Can_GeneralTypes.h
*/
typedef enum
{
	CANTRCV_WU_ERROR	 		= 0, /* Due to an error wake up reason was not detected. This value may only be reported when error was reported to DEM before. */
	CANTRCV_WU_NOT_SUPPORTED 	= 1, /* The transceiver does not support any information for the wake up reason.  */
	CANTRCV_WU_BY_BUS			= 2, /* The transceiver has detected, that the network has caused the wake up of the ECU. */
	CANTRCV_WU_INTERNALLY		= 3, /* The transceiver has detected, that the network has woken up by the ECU via a request to NORMAL mode. */
	CANTRCV_WU_RESET			= 4, /* The transceiver has detected, that the "wake up" is due to an ECU reset. */
	CANTRCV_WU_POWER_ON			= 5, /* The transceiver has detected, that the "wake up" is due to an ECU reset after power on. */
	CANTRCV_WU_BY_PIN			= 6, /* The transceiver has detected a wake-up event at one of the transceiver's pins (not at the CAN bus). */
	CANTRCV_WU_BY_SYSERR		= 7  /* The transceiver has detected, that the wake up of the ECU was caused by a HW related device failure. */
} CanTrcv_TrcvWakeupReasonType;

/**
* @brief        CAN Controller Error Types of operation.
* @details      The enumeration represents a superset of CAN Error Types which typical CAN HW is able to report.
*               That means not all CAN HW will be able to support the complete set.
*/
typedef enum
{
    CAN_ERROR_BIT_MONITORING1        = 0x01,    /* A 0 was transmitted and a 1 was read back */
    CAN_ERROR_BIT_MONITORING0        = 0x02,    /* A 1 was transmitted and a 0 was read back */
    CAN_ERROR_BIT                    = 0x03,    /* The HW reports a CAN bit error but cannot report distinguish between CAN_ERROR_BIT_MONITORING1 and CAN_ERROR_BIT_MONITORING0 */
    CAN_ERROR_CHECK_ACK_FAILED       = 0x04,    /* Acknowledgement check failed */
    CAN_ERROR_ACK_DELIMITER          = 0x05,    /* Acknowledgement delimiter check failed */
    CAN_ERROR_ARBITRATION_LOST       = 0x06,    /* The sender lost in arbitration */
    CAN_ERROR_OVERLOAD               = 0x07,    /* CAN overload detected via an overload frame. Indicates that the receive buffers of a receiver are full */
    CAN_ERROR_CHECK_FORM_FAILED      = 0x08,    /* Violations of the fixed frame format */
    CAN_ERROR_CHECK_STUFFING_FAILED  = 0x09,    /* Stuffing bits not as expected */
    CAN_ERROR_CHECK_CRC_FAILED       = 0xA,     /* CRC failed */
    CAN_ERROR_BUS_LOCK               = 0xB      /* Bus lock (Bus is stuck to dominant level) */
} Can_ErrorType;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @{
* @brief          Can_IdType
* @details        Represents the Identifier of an L-PDU. The two most significant bits specify theframe type:
* -00 CAN message with Standard CAN ID
* -01 CAN FD frame with Standard CAN ID
* -10 CAN message with Extended CAN ID
* -11 CAN FD frame with Extended CAN ID
* @implements     Can_IdType_type
*/
typedef  uint32 Can_IdType;


/**
* @brief          Can_PduType
* @details        Type used to provide ID, DLC, SDU from CAN interface to CAN driver.
*                 HTH or HRH = ID+DLC+SDU.
* @implements     Can_PduType_structure
*/
typedef struct
{
    Can_IdType id; /**< @brief CAN L-PDU = Data Link Layer Protocol Data Unit.
                                             Consists of Identifier, DLC and Data(SDU)  It is
                                             uint32 for CAN_EXTENDEDID=STD_ON, else is uint16.
                                             */
    PduIdType swPduHandle; /**< @brief The L-PDU Handle = defined and placed
                                                     inside the CanIf module layer. Each handle
                                                     represents an L-PDU, which is a constant
                                                     structure with information for Tx/Rx
                                                     processing. */
    uint8 length; /**< @brief DLC = Data Length Code (part of L-PDU that describes
                                            the SDU length). */
    uint8 * sdu; /**< @brief CAN L-SDU = Link Layer Service Data
                                                          Unit. Data that is transported inside
                                                          the L-PDU. */
} Can_PduType;


/**
* @{
* @brief          Can_HwHandleType
* @details        Represents the hardware object handles of a CAN hardware unit.
                  For CAN hardware units with more than 255 HW objects use extended range.
*                    used by "Can_Write" function.
*                 The driver does not distinguish between Extended and Mixed transmission modes.
*                 Extended transmission mode of operation behaves the same as Mixed mode.
* @implements     Can_HwHandleType_type
*/
typedef uint16 Can_HwHandleType;

/**
* @brief          Can_HwType
* @details        This type defines a data structure which clearly provides an Hardware Object 
                    Handle including its corresponding CAN Controller and therefore CanDrv as well 
                    as the specific CanId.
* @implements     Can_HwType_structure
*/

typedef struct
{
    Can_IdType CanId; /**< @brief Standard/Extended CAN ID of CAN L-PDU. */
                                             
    Can_HwHandleType  Hoh; /**< @brief ID of the corresponding Hardware Object Range */
    
    uint8 ControllerId; /**< @brief ControllerId provided by CanIf clearly 
                                            identify the corresponding controller */
                                            
} Can_HwType;

/**
* @brief          Can_TimeStampType
* @details        Variables of this type are used to express time stamps based on relative time.
*/
typedef struct
{
    uint32 nanoseconds;   /**< @brief Nanoseconds part of the time. */
    uint32 seconds;       /**< @brief Seconds part of the time. */
}Can_TimeStampType;


/** @brief Contains CAN XL specific information. */
typedef struct {
    /** @brief Priority ID of a CAN XL message. */
    uint16 PriorityId;
    /** @brief VCID of a CAN XL message. */
    uint16 Vcid;
    /** @brief SDU type of a CAN XL message. */
    uint8 SduType;
    /** @brief Acceptance field of a CAN XL message. */
    uint32 AcceptanceField;
    /** @brief Simple extended content field of a CAN XL message. */
    uint8 Sec;
} CanXL_Params;
/** @brief This type extends the classical Can_PduType with a larger PDU length, the CanXL_Params and a
sec to indicate simple or extended content. */
typedef struct {
    /** @brief Contains the PDU ID. */
    PduIdType swPduHandle;
    /** @brief Length of the data. */
    uint16 length;
    /** @brief SDU data pointer. */
    uint8 * sdu;
    /** @brief Pointer to CAN XL params */
    CanXL_Params * XLParams;
} CanXL_PduType;
/** @brief This type defines a data structure which provides a CAN XL Hardware Object Handle including its
corresponding CAN Controller and therefore CanDrv as well as the specific CAN XL parameters. */
typedef struct {
    /** @brief Pointer to CAN XL params. */
    CanXL_Params * XLParams;
    /** @brief ControllerId provided by CanIf, identifies the corresponding CAN XL controller. */
    uint8 ControllerId;
    /** @brief ID of the corresponding CAN XL Hardware Object Range */
    Can_HwHandleType Hoh;
} CanXL_HwType;
/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /*CAN_GENERAL_TYPES_H*/

/** @} */
