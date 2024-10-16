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
*   @file           Eth_GeneralTypes.h
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP driver type definitions header file
*   @details Definitions of types for the Ethernet driver
*            This file contains sample code only. It is not part of the production code deliverables
*   @addtogroup BASENXP_COMPONENT
*   @{
*/

#ifndef ETH_GENERALTYPES_H
#define ETH_GENERALTYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "ComStackTypes.h" /* Mandatory include - see the SWS */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** 
@{
* @brief Parameters that shall be published within the modules header file.
*       The integration of incompatible files shall be avoided.
*/
#define ETH_GENERALTYPES_AR_RELEASE_MAJOR_VERSION      4
#define ETH_GENERALTYPES_AR_RELEASE_MINOR_VERSION      7

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
* @brief          The Ethernet driver state.
* @details        A variable of this type holds the state of the Ethernet driver
*                 module. The driver is at the ETH_STATE_UNINIT at the beginning
*                 until the Eth_Init() function is called. The state remains
*                 equal to the ETH_STATE_INIT until the Eth_ControllerInit()
*                 function is called. Then the state is ETH_STATE_ACTIVE.
* @implements     Eth_StateType_enum
*/
typedef enum
{
    ETH_STATE_UNINIT = 0, /**< The driver has not been initialized yet */
    ETH_STATE_INIT        /**< The driver has not been configured and
                               the controller was configured */
} Eth_StateType;

/**
* @brief          The Ethernet controller mode.
* @details        This type is used to store the information whether the
*                 Ethernet controller is stopped or running.
* @implements     Eth_ModeType_enum
*/
typedef enum
{
    ETH_MODE_DOWN                       = 0U, /**< Controller is shut down */
    ETH_MODE_ACTIVE                     = 1U, /**< Controller is active */
    ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST = 2U  /**< Controller is active with wakeup request. */
}  Eth_ModeType;

/**
* @brief          The Ethernet reception status
* @details        This status is returned by the @c Eth_Receive() function to indicate
*                 whether any frame has been received and if yes, whether there is any
*                 frame still waiting in the queue (for another @c Eth_Receive() call).
* @implements     Eth_RxStatusType_enum
*/
typedef enum
{
    ETH_RECEIVED = 0,   /**< A frame has been received and there are no more frames in the queue */
    ETH_NOT_RECEIVED,   /**< No frames received */
    ETH_RECEIVED_MORE_DATA_AVAILABLE /**< A frame received and at least another one in the queue detected */
} Eth_RxStatusType;

/**
* @brief          Action type for PHY address filtering
* @details        The Enumeration type describes the action to be taken
*                 for the MAC address given in *PhysAddrPtr
* @implements     Eth_FilterActionType_enum
*/
typedef enum
{
    ETH_ADD_TO_FILTER = 0,    /**< Add address to the filter */
    ETH_REMOVE_FROM_FILTER    /**< Remove address */
} Eth_FilterActionType;

/**
* @brief          The Ethernet quality of timestamp type
* @details        Depending on the HW, quality information regarding the evaluated time stamp 
*                 might be supported. If not supported, the value shall be always Valid. For 
*                 Uncertain and Invalid values, the upper layer shall discard the time stamp.
* @implements     Eth_TimeStampQualType_enum
*/
typedef enum
{
    ETH_VALID = 0,         /**< Success */
    ETH_INVALID,       /**< General failure */
    ETH_UNCERTAIN     /**< Ethernet hardware access failure */
}  Eth_TimeStampQualType;

/**
* @brief          This type defines the transceiver modes
* @details        The Enumeration type describes the transceiver modes
* @implements     EthTrcv_ModeType_enum
*/
typedef enum
{
    ETHTRCV_MODE_DOWN = 0,    /**<  Transceiver disabled */
    ETHTRCV_MODE_ACTIVE       /**<  Transceiver enable */
} EthTrcv_ModeType;
/**
* @brief This type defines the Ethernet link state. The link state changes after an Ethernet cable gets plugged in and the transceivers on both ends negotiated the transmission parameters (i.e. baud rate and duplex mode)
* @implements     EthTrcv_LinkStateType_enum
*/
typedef enum
{
    /**< @brief No physical Ethernet connection established. */
    ETHTRCV_LINK_STATE_DOWN = (uint8)0x0U,
    /**< @brief Physical Ethernet connection established. */
    ETHTRCV_LINK_STATE_ACTIVE  = (uint8)0x1U
    
} EthTrcv_LinkStateType;

/**
* @brief This type defines the Ethernet link state. The link state changes after an Ethernet cable gets plugged in and the transceivers on both ends negotiated the transmission parameters (i.e. baud rate and duplex mode)
* @implements     EthTrcv_StateType_enum
*/
typedef enum
{
    /**< @brief Driver is not yet configured */
    ETHTRCV_STATE_UNINIT = (uint8)0x0U,
    /**< @brief Driver is configured. */
    ETHTRCV_STATE_INIT  = (uint8)0x1U
    
} EthTrcv_StateType;

/**
* @brief This type defines the Ethernet baud rate. The baud rate gets either negotiated between the connected transceivers or has to be configured.
* @implements     EthTrcv_BaudRateType_enum
*/
typedef enum
{
    /**< @brief 10MBIT Ethernet connection */
    ETHTRCV_BAUD_RATE_10MBIT = (uint8)0x0U,
    /**< @brief 100MBIT Ethernet connection */
    ETHTRCV_BAUD_RATE_100MBIT  = (uint8)0x1U,
    /**< @brief 1000MBIT Ethernet connection */
    ETHTRCV_BAUD_RATE_1000MBIT = (uint8)0x2U,
    /**< @brief 2500MBIT Ethernet connection */
    ETHTRCV_BAUD_RATE_2500MBIT

} EthTrcv_BaudRateType;

/**
* @brief This type defines the Ethernet duplex mode. The duplex mode gets either negotiated between the connected transceivers or has to be configured.
* @implements     EthTrcv_DuplexModeType_enum
*/
typedef enum
{
    /**< @brief Half duplex Ethernet connection */
    ETHTRCV_DUPLEX_MODE_HALF = (uint8)0x0U,
    /**< @brief Full duplex Ethernet connection */
    ETHTRCV_DUPLEX_MODE_FULL  = (uint8)0x1U
    
} EthTrcv_DuplexModeType;

/**
* @brief This type controls the transceiver wake up modes and/or clears the wake-up reason.
* @implements     EthTrcv_WakeupModeType_enum
*/
typedef enum
{
    /**< @brief Transceiver wake up disabled */
    ETHTRCV_WUM_DISABLE = (uint8)0x0U,
    /**< @brief Transceiver wake up enabled */
    ETHTRCV_WUM_ENABLE  = (uint8)0x1U,
    /**< @brief Transceiver wake up reason cleared. */
    ETHTRCV_WUM_CLEAR
    
} EthTrcv_WakeupModeType;

/**
* @brief This type defines the transceiver wake up reasons.
* @implements     EthTrcv_WakeupReasonType_enum
*/
typedef enum
{
    /**< @brief No wake up reason detected. */
    ETHTRCV_WUR_NONE = (uint8)0x0U,
    /**< @brief General wake up detected, no distinct reason supported by hardware. */
    ETHTRCV_WUR_GENERAL  = (uint8)0x1U,
    /**< @brief Internal wake up detected. Available if supported by hardware. */
    ETHTRCV_WUR_INTERNAL  = (uint8)0x3U,
    /**< @brief Reset wake up detected. Available if supported by hardware. */
    ETHTRCV_WUR_RESET  = (uint8)0x4U,
    /**< @brief Power on wake up detected. Available if supported by hardware. */
    ETHTRCV_WUR_POWER_ON  = (uint8)0x5U,
    /**< @brief Pin wake up detected. Available if supported by hardware. */
    ETHTRCV_WUR_PIN  = (uint8)0x6U,
    /**< @brief System error wake up detected. Available if supported by hardware. */
    ETHTRCV_WUR_SYSERR  = (uint8)0x7U,
    /**< @brief Wake-up on data line (WUP = wake up pulse) detected while link is down of the corresponding Ethernet hardware (e.g. PHY).
Only available if EthTrcvWakeupSleepOn DatalineEnabled is set to TRUE */
    ETHTRCV_WUR_WODL_WUP  = (uint8)0x8U,
    /**< @brief Wake-up on data line (WUR = wake up request) detected while link is active of the used Ethernet hardware (e.g. PHY). 
Only available if EthTrcvWakeupSleepOnDataline Enabled is set to TRUE */
    ETHTRCV_WUR_WODL_WUR  = (uint8)0x9U,
    /**< @brief Device internal transfer of wake-up on data line from a neighboring PHY. Only possible if Ethernet hardware is compliant to OA TC10. 
Only available if EthTrcvWakeupSleepOn DatalineEnabled is set to TRUE. */
    ETHTRCV_WUR_TRANSFER  = (uint8)0xAU

} EthTrcv_WakeupReasonType;

/**
* @brief Describes the possible PHY test modes
* @implements     EthTrcv_PhyTestModeType_enum
*/
typedef enum
{
    /**< @brief normal operation */
    ETHTRCV_PHYTESTMODE_NONE = (uint8)0x0U,
    /**< @brief test transmitter droop */
    ETHTRCV_PHYTESTMODE_1  = (uint8)0x1U,
    /**< @brief test master timing jitter */
    ETHTRCV_PHYTESTMODE_2  = (uint8)0x2U,
    /**< @brief test slave timing jitter */
    ETHTRCV_PHYTESTMODE_3  = (uint8)0x3U,
    /**< @brief test transmitter distortion */
    ETHTRCV_PHYTESTMODE_4  = (uint8)0x4U,
    /**< @brief test power spectral density (PSD) mask */
    ETHTRCV_PHYTESTMODE_5  = (uint8)0x5U
    
} EthTrcv_PhyTestModeType;

/**
* @brief Describes the possible PHY loopback modes
* @implements     EthTrcv_PhyLoopbackModeType_enum
*/
typedef enum
{
    /**< @brief normal operation */
    ETHTRCV_PHYLOOPBACK_NONE = (uint8)0x0U,
    /**< @brief internal loopback */
    ETHTRCV_PHYLOOPBACK_INTERNAL  = (uint8)0x1U,
    /**< @brief external loopback */
    ETHTRCV_PHYLOOPBACK_EXTERNAL  = (uint8)0x2U,
    /**< @brief remote loopback */
    ETHTRCV_PHYLOOPBACK_REMOTE  = (uint8)0x3U
    
} EthTrcv_PhyLoopbackModeType;

/**
* @brief Describes the possible PHY transmit modes
* @implements     EthTrcv_PhyTxModeType_enum
*/
typedef enum
{
    /**< @brief normal operation */
    ETHTRCV_PHYTXMODE_NORMAL = (uint8)0x0U,
    /**< @brief transmitter disabled */
    ETHTRCV_PHYTXMODE_TX_OFF  = (uint8)0x1U,
    /**< @brief scrambler disabled */
    ETHTRCV_PHYTXMODE_SCRAMBLER_OFF  = (uint8)0x2U
    
} EthTrcv_PhyTxModeType;

/**
* @brief Describes the results of the cable diagnostics.
* @implements     EthTrcv_CableDiagResultType_enum
*/
typedef enum
{
    /**< @brief Cable diagnostic ok */
    ETHTRCV_CABLEDIAG_OK = (uint8)0x0U,
    /**< @brief Cable diagnostic failed */
    ETHTRCV_CABLEDIAG_ERROR  = (uint8)0x1U,
    /**< @brief Short circuit detected */
    ETHTRCV_CABLEDIAG_SHORT  = (uint8)0x2U,
    /**< @brief Open circuit detected */
    ETHTRCV_CABLEDIAG_OPEN  = (uint8)0x3U,
    /**< @brief cable diagnostic is still running */
    ETHTRCV_CABLEDIAG_PENDING  = (uint8)0x4U,
    /**< @brief cable diagnostics has detected wrong polarity of the "Ethernet physical+" or "Ethernet physical-" lines */
    ETHTRCV_CABLEDIAG_WRONG_POLARITY  = (uint8)0x5U
    
} EthTrcv_CableDiagResultType;

/**
* @brief  Status supervision used for Development Error Detection. The state shall be available for debugging.
* @implements     EthSwt_StateType_enum
*/
typedef enum
{
    ETHSWT_STATE_UNINIT             = (uint8)0x0U, /**< @brief The Eth Switch Driver is not yet configured. */
    ETHSWT_STATE_INIT               = (uint8)0x1U, /**< @brief The Eth Switch Driver is configured */
    ETHSWT_STATE_PORTINIT_COMPLETED = (uint8)0x2U, /**< @brief Port initialization is completed. */
    ETHSWT_STATE_ACTIVE             = (uint8)0x3U  /**< @brief The Eth Switch driver is active. */
} EthSwt_StateType;

/**
* @brief  MAC learning type enumeration.
* @implements     EthSwt_MacLearningType_enum
*/
typedef enum
{
    ETHSWT_MACLEARNING_HWDISABLED  = (uint8)0x0U, /**< @brief If hardware learning disabled, the switch must not learn new MAC addresses */
    ETHSWT_MACLEARNING_HWENABLED   = (uint8)0x1U, /**< @brief If hardware learning enabled, the switch learns new MAC addresses */
    ETHSWT_MACLEARNING_SWENABLED   = (uint8)0x2U  /**< @brief If software learning enabled, the hardware learning is disabled and the switch forwards packets  with an unknown source address to a host CPU */
} EthSwt_MacLearningType;

/**
* @brief Type to request or obtain the port mirroring state (enable/disable) for a particular port mirror configuration per Ethernet switch.
* @implements     EthSwt_PortMirrorStateType_enum
*/
typedef enum
{
    PORT_MIRROR_DISABLED = (uint8)0x0U, /**< @brief port mirroring disabled. */
    PORT_MIRROR_ENABLED  = (uint8)0x1U  /**< @brief port mirroring enabled. */
} EthSwt_PortMirrorStateType;

/**
* @brief  Holds information if upper layer or EthSwt is owner of mgmt_obj.
* @implements     EthSwt_MgmtOwner_enum
*/
typedef enum
{
    ETHSWT_MGMT_OBJ_UNUSED               = (uint8)0x0U, /**< @brief Object unused */
    ETHSWT_MGMT_OBJ_OWNED_BY_ETHSWT      = (uint8)0x1U, /**< @brief Object used and EthSwt collects needed data */
    ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER = (uint8)0x2U  /**< @brief Object used and the upper layer does calculations */
} EthSwt_MgmtOwner;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief         Frame type.
* @details       This type is used to pass the value of type or length field in the
*                Ethernet frame header. It is 16 bits long unsigned integer.
*                - Values less than or equal to 1500 represent the length.
*                - Values grater than 1500 represent the type (i.e. 0x800 = IP).
* @implements     Eth_FrameType_type
*/
typedef uint16 Eth_FrameType;

/**
* @brief         Type used to pass transmit or receive data to or from the driver.
* @details       This type was defined as 8 bit wide unsigned integer because
*                this definition is available on all CPU types.
* @implements     Eth_DataType_type
*/
typedef uint8 Eth_DataType;

/**
* @brief         Type used to identify the ethernet buffer. 
* @details       This type was defined for index of buffer used in transmitted and received data.
* @implements     Eth_BufIdxType_type
*/
typedef uint32 Eth_BufIdxType;

/**
* @brief         Type used to express the timestamp value. 
* @details       Variables of this type are used for expressing time stamps including relative time 
*                and absolute calendar time. The absolute time starts acc. to "[5], Annex C/C1" 
*                specification at 1970-01-01.
*                0 to 281474976710655s
*                == 3257812230d
*                [0xFFFF FFFF FFFF]
*                0 to 999999999ns
*                [0x3B9A C9FF]
*                invalid value in nanoseconds: [0x3B9A CA00] to [0x3FFF FFFF]
*                Bit 30 and 31 reserved, default: 0
* @implements    Eth_TimeStampType_struct
*/
typedef struct
{
    uint32 nanoseconds;   /**< @brief Nanoseconds part of the time */
    uint32 seconds;       /**< @brief 32 bit LSB of the 48 bits Seconds part of the time */
    uint16 secondsHi;     /**< @brief 16 bit MSB of the 48 bits Seconds part of the time */
} Eth_TimeStampType;

/**
* @brief         Type used to express the diff between timestamp values. 
* @details       Variables of this type are used to express time differences in a usual way. The 
*                described "TimeInterval" type referenced in ", chapter 6.3.3.3" will not be used 
*                and hereby slightly simplified.
* @implements    Eth_TimeIntDiffType_structure
*/
typedef struct
{
    Eth_TimeStampType diff;   /**< @brief diff time difference */
    boolean sign;       /**< @brief Positive (True) Or negative (False) time */
} Eth_TimeIntDiffType;

/**
* @brief         Type used to express frequency ratio. 
* @details       Variables of this type are used to express frequency ratios. 
* @implements    Eth_RateRatioType_structure
*/
typedef struct
{
    Eth_TimeIntDiffType IngressTimeStampDelta;   /**< @brief   IngressTimeStampSync2 -IngressTimeStampSync1 */
    Eth_TimeIntDiffType OriginTimeStampDelta;       /**< @brief OriginTimeStampSync2[FUP2]-OriginTimeStampSync1[FUP1] */
} Eth_RateRatioType;

/**
* @brief         Type used to statistic counter for diagnostics. 
* @details       Variables of this type are used to statistic counter for diagnostics. 
* @implements    Eth_CounterType_structure
*/
typedef struct{
    uint32 DropPktBufOverrun;
    uint32 DropPktCrc;
    uint32 UndersizePkt;
    uint32 OversizePkt;
    uint32 AlgnmtErr;
    uint32 SqeTestErr;
    uint32 DiscInbdPkt;
    uint32 ErrInbdPkt;
    uint32 DiscOtbdPkt;
    uint32 ErrOtbdPkt;
    uint32 SnglCollPkt;
    uint32 MultCollPkt;
    uint32 DfrdPkt;
    uint32 LatCollPkt;
    uint32 HwDepCtr0;
    uint32 HwDepCtr1;
    uint32 HwDepCtr2;
    uint32 HwDepCtr3;
}Eth_CounterType;

/**
* @brief         Type used to statistic counter for diagnostics. 
* @details       Variables of this type are used to statistic counter for diagnostics. 
* @implements    Eth_RxStatsType_structure
*/
typedef struct
{
   uint32 RxStatsDropEvents;
   uint32 RxStatsOctets;
   uint32 RxStatsPkts;
   uint32 RxStatsBroadcastPkts;
   uint32 RxStatsMulticastPkts;
   uint32 RxStatsCrcAlignErrors;
   uint32 RxStatsUndersizePkts;
   uint32 RxStatsOversizePkts;
   uint32 RxStatsFragments;
   uint32 RxStatsJabbers;
   uint32 RxStatsCollisions;
   uint32 RxStatsPkts64Octets;
   uint32 RxStatsPkts65to127Octets;
   uint32 RxStatsPkts128to255Octets;
   uint32 RxStatsPkts256to511Octets;
   uint32 RxStatsPkts512to1023Octets;
   uint32 RxStatsPkts1024to1518Octets;
   uint32 RxUnicastFrames;
}Eth_RxStatsType;

/**
* @brief         Type used to statistic counter for diagnostics. 
* @details       Variables of this type are used to statistic counter for diagnostics. 
* @implements    Eth_TxStatsType_structure
*/
typedef struct
{
    uint32 TxNumberOfOctets;
    uint32 TxNUcastPkts;
    uint32 TxUniCastPkts;
}Eth_TxStatsType;

/**
* @brief         Type used to statistic counter for diagnostics. 
* @details       Variables of this type are used to statistic counter for diagnostics. 
* @implements    Eth_TxErrorCounterValuesType_structure
*/
typedef struct
{
    uint32 TxDroppedNoErrorPkts;
    uint32 TxDroppedErrorPkts;
    uint32 TxDeferredTrans;
    uint32 TxSingleCollision;
    uint32 TxMultipleCollision;
    uint32 TxLateCollision;
    uint32 TxExcessiveCollison;
}Eth_TxErrorCounterValuesType;

/**
* @brief         Type used for VLAN management in EthSwt. 
* @details       Variables of this type are used to store information related to VLAN. 
* @implements    Eth_MacVlanType_structure
*/
typedef struct
{
    uint8 MacAddr[6];
    uint16 VlanId;
    uint8 SwitchPort;
}Eth_MacVlanType;

/**
 * @brief    Type for holding the management information received/transmitted on Switches (ports).
 * @details  It contains the switch index and the port index of the switch
*/
typedef struct
{
    uint8            SwitchIdx;      /**< @brief Switch index */
    uint8            SwitchPortIdx;  /**< @brief Port index of the switch */
} EthSwt_MgmtInfoType;

/**
* @brief The EthSwt_PortMirrorCfgType specify the port mirror configuration which is set up per Ethernet switch. The configuration is written to the Ethernet switch driver by calling EthSwt_WritePortMirrorConfiguration. One port mirror configuration is maintained per Ethernet Switch.
*/
typedef struct
{
    uint8    srcMacAddrFilter[6U];      /**< @brief Specifies the source MAC address [0..255,0..255,0..255,0..255,0..255,0..255] that should be mirrored. If set to 0,0,0,0,0,0, no source MAC address filtering shall take place. */
    uint8    dstMacAddrFilter[6U];      /**< @brief Specifies the destination MAC address [0..255,0..255,0..255,0..255,0..255,0..255] that should be mirrored. If set to 0,0,0,0,0,0, no destination MAC address filtering shall take place. */
    uint16   VlanIdFilter;              /**< @brief Specifies the VLAN address 0..4094 that should be mirrored. If set to 65535, no VLAN filtering shall take place. */
    uint8    MirroringPacketDivider;    /**< @brief Divider if only a subset of received frames should be mirrored. E.g. MirroringPacketDivider = 2 means every second frames is mirrored */
    uint8    MirroringMode;             /**< @brief specifies the mode how the mirrored traffic should be tagged : 0x00 == No VLAN retagging; 0x01 == VLAN retagging; 0x03 == VLAN Double tagging */
    uint32   TrafficDirectionIngressBitMask;   /**< @brief Specifies the bit mask of Ethernet switch ingress port traffic direction to be mirrored. The bit mask is calculated depending of the values of EthSwtPortIdx. (e.g. set EthSwtPortIdx == 2 => TrafficDirectionIngressBitMask = 0b0000 0000 0000 0000 0000 0000 0000 0100). 0b0 == enable ingress port mirroring 0b1 == disable ingress port mirroring Example: TrafficDirectionIngressBitMask = 0b0000 0000 0000 0000 0000 0000 0000 0100 => Ingress traffic mirroring is enabled of Ethernet switch port with EthSwtPortIdx=2 */
    uint32   TrafficDirectionEgressBitMask;    /**< @brief Specifies the bit mask of Ethernet switch egress port traffic direction to be mirrored. The bit mask is calculated depending of the values of EthSwtPortIdx. (e.g. set EthSwtPortIdx == 2 => TrafficDirectionEgressBitMask = 0b0000 0000 0000 0000 0000 0000 0000 0100). 0b0 == enable egress port mirroring 0b1 == disable egress port mirroring Example: TrafficDirectionEgressBitMask = 0b0000 0000 0000 0000 0000 0000 0000 0001 => Egress traffic mirroring is enabled of Ethernet switch port with EthSwtPortIdx=0 */
    uint8    CapturePortIdx;    /**< @brief Specifies the Ethernet switch port which capture the mirrored traffic */
    uint16   ReTaggingVlanId;    /**< @brief Specifies the VLAN address 0..4094 which shall be used for re-tagging if MirroringMode is set to 0x01 (VLAN re-tagging). If the value is set to 65535, the value shall be ignored, because the VLAN address for re-tagging is provided by the Ethernet switch configuration */
    uint16   DoubleTaggingVlanId;    /**< @brief Specifies the VLAN address 0..4094 which shall be used for double-tagging if MirroringMode is set to 0x02 (VLAN double tagging). If the value is set to 65535, the value shall be ignored, because the VLAN address for double tagging is provided by the Ethernet switch configuration */
} EthSwt_PortMirrorCfgType;


/**
* @brief  Will be set from EthSwt and marks EthSwt_MgmtObject as valid or not. So the upper layer will be able to detect inconsistencies.
*/
typedef struct
{
    Std_ReturnType    IngressTimestampValid;  /**< @brief IngressTimestampValid shall be set to E_NOT_OK if ingress timestamp is not available */
    Std_ReturnType    EgressTimestampValid;   /**< @brief EgressTimestampValid shall be set to E_NOT_OK if ingress timestamp is not available. */
    Std_ReturnType    MgmtInfoValid;          /**< @brief MgmtInfoValid shall be set to E_NOT_OK if ingress timestamp is not available(e.g. timeout). */
} EthSwt_MgmtObjectValidType;

/**
* @brief  Provides information about all struct member elements. The ownership gives information whether EthSwt has finished its activities in providing all struct member elements.
*/
typedef struct
{
    EthSwt_MgmtObjectValidType    Validation;         /**< @brief The validation information for the mgmt_obj. */
    Eth_TimeStampType             IngressTimestamp;   /**< @brief The ingress timestamp value out of the switch. */
    Eth_TimeStampType             EgressTimestamp;    /**< @brief The egress timestamp value out of the switch. */
    EthSwt_MgmtInfoType           MgmtInfo;           /**< @brief Received/Transmitted Management information of the switches. */
    EthSwt_MgmtOwner              Ownership;          /**< @brief The ownership of MgmtObj. */
} EthSwt_MgmtObjectType;
/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* ETH_GENERALTYPES_H */
/** @} */
