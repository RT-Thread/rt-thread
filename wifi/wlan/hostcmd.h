/** @file hostcmd.h
 * 
 * @brief This file contains the function prototypes, data structure 
 * and defines for all the host/station commands
 *  
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
 */
/********************************************************
Change log:
	10/11/05: Add Doxygen format comments
	01/11/06: Update association struct to reflect IEEE passthrough response
	          Conditionalize new scan/join structures
	04/10/06: Add hostcmd generic API and power_adapt_cfg_ext command
	04/18/06: Remove old Subscrive Event and add new Subscribe Event
	          implementation through generic hostcmd API
	05/03/06: Add auto_tx hostcmd
	05/04/06: Add IBSS coalescing related new hostcmd
	08/28/06: Add LED_CTRL hostcmd
	08/29/06: Add ledgpio private command
********************************************************/

#ifndef __HOSTCMD__H
#define __HOSTCMD__H
#include    "..\os\os_headers.h"
/*  802.11-related definitions */

/** TxPD descriptor */
typedef struct _TxPD
{
    /** Current Tx packet status */
    u32 TxStatus;
    /** Tx Control */
    u32 TxControl;
    u32 TxPacketLocation;
    /** Tx packet length */
    u16 TxPacketLength;
    /** First 2 byte of destination MAC address */
    u8 TxDestAddrHigh[2];
    /** Last 4 byte of destination MAC address */
    u8 TxDestAddrLow[4];
    /** Pkt Priority */
    u8 Priority;
    /** Trasnit Pkt Flags*/
    u8 Flags;
    /** Amount of time the packet has been queued in the driver (units = 2ms)*/
    u8 PktDelay_2ms;
    /** Reserved */
    u8 Reserved1;

} __ATTRIB_PACK__ TxPD, *PTxPD;

/** RxPD Descriptor */
typedef struct _RxPD
{
        /** Current Rx packet status */
    u16 RxStatus;

        /** SNR */
    u8 SNR;

        /** Tx Control */
    u8 RxControl;

        /** Pkt Length */
    u16 PktLen;

        /** Noise Floor */
    u8 NF;

        /** Rx Packet Rate */
    u8 RxRate;

        /** Pkt offset */
    u32 PktOffset;
    u8 RxPacketType;
    u8 Reserved_1[3];
        /** Pkt Priority */
    u8 Priority;
    u8 Reserved[3];

}  RxPD, *PRxPD;

//#if defined(__KERNEL__)

/** CmdCtrlNode */
typedef struct _CmdCtrlNode
{
    /* CMD link list */
    struct list_head list;

    u32 Status;

    /* CMD ID */
    WLAN_OID cmd_oid;

    /*CMD wait option: wait for finish or no wait */
    u16 wait_option;

    /* command parameter */
    void *pdata_buf;

    /*command data */
    u8 *BufVirtualAddr;

    u16 CmdFlags;

    /* wait queue */
    //u16 CmdWaitQWoken;
	#define CmdWaitQWoken (0x01)
	struct   rt_event cmdwait;	 //only set or rec the 0x01
}  CmdCtrlNode, *PCmdCtrlNode;

//#endif

/** MRVL_WEP_KEY */
typedef struct _MRVL_WEP_KEY
{
    u32 Length;
    u32 KeyIndex;
    u32 KeyLength;
    u8 KeyMaterial[MRVL_KEY_BUFFER_SIZE_IN_BYTE];
}  MRVL_WEP_KEY, *PMRVL_WEP_KEY;

typedef ULONGLONG WLAN_802_11_KEY_RSC;

/** WLAN_802_11_KEY */
typedef struct _WLAN_802_11_KEY
{
    u32 Length;
    u32 KeyIndex;
    u32 KeyLength;
    WLAN_802_11_MAC_ADDRESS BSSID;
    WLAN_802_11_KEY_RSC KeyRSC;
    u8 KeyMaterial[MRVL_MAX_KEY_WPA_KEY_LENGTH];
}  WLAN_802_11_KEY;

/** MRVL_WPA_KEY */
typedef struct _MRVL_WPA_KEY
{
    u32 KeyIndex;
    u32 KeyLength;
    u32 KeyRSC;
    u8 KeyMaterial[MRVL_MAX_KEY_WPA_KEY_LENGTH];
} MRVL_WPA_KEY, *PMRVL_WPA_KEY;

/** MRVL_WLAN_WPA_KEY */
typedef struct _MRVL_WLAN_WPA_KEY
{
    u8 EncryptionKey[16];
    u8 MICKey1[8];
    u8 MICKey2[8];
} MRVL_WLAN_WPA_KEY, *PMRVL_WLAN_WPA_KEY;

/* Received Signal Strength Indication  in dBm*/
typedef LONG WLAN_802_11_RSSI;

/** WLAN_802_11_WEP */
typedef struct _WLAN_802_11_WEP
{
    /* Length of this structure */
    u32 Length;

    /* 0 is the per-client key, 1-N are the global keys */
    u32 KeyIndex;

    /* length of key in bytes */
    u32 KeyLength;

    /* variable length depending on above field */
    u8 KeyMaterial[1];
} __ATTRIB_PACK__ WLAN_802_11_WEP;

/** WLAN_802_11_SSID */
typedef struct _WLAN_802_11_SSID
{
    /* SSID Length */
    u32 SsidLength;

    /* SSID information field */
    u8 Ssid[WLAN_MAX_SSID_LENGTH];
} __ATTRIB_PACK__ WLAN_802_11_SSID;

typedef u32 WLAN_802_11_FRAGMENTATION_THRESHOLD;
typedef u32 WLAN_802_11_RTS_THRESHOLD;
typedef u32 WLAN_802_11_ANTENNA;

/** wlan_offset_value */
typedef struct _wlan_offset_value
{
    u32 offset;
    u32 value;
} wlan_offset_value;

/** WLAN_802_11_FIXED_IEs */
typedef struct _WLAN_802_11_FIXED_IEs
{
    u8 Timestamp[8];
    u16 BeaconInterval;
    u16 Capabilities;
} WLAN_802_11_FIXED_IEs;

/** WLAN_802_11_VARIABLE_IEs */
typedef struct _WLAN_802_11_VARIABLE_IEs
{
    u8 ElementID;
    u8 Length;
    u8 data[1];
} WLAN_802_11_VARIABLE_IEs;

/** WLAN_802_11_AI_RESFI */
typedef struct _WLAN_802_11_AI_RESFI
{
    u16 Capabilities;
    u16 StatusCode;
    u16 AssociationId;
} WLAN_802_11_AI_RESFI;

/** WLAN_802_11_AI_REQFI */
typedef struct _WLAN_802_11_AI_REQFI
{
    u16 Capabilities;
    u16 ListenInterval;
    WLAN_802_11_MAC_ADDRESS CurrentAPAddress;
} WLAN_802_11_AI_REQFI;

/* Define general data structure */
/** HostCmd_DS_GEN */
typedef struct _HostCmd_DS_GEN
{
    u16 Command;
    u16 Size;
    u16 SeqNum;
    u16 Result;
} __ATTRIB_PACK__ HostCmd_DS_GEN, HostCmd_DS_802_11_DEEP_SLEEP;

#define S_DS_GEN    sizeof(HostCmd_DS_GEN)
/*
 * Define data structure for HostCmd_CMD_GET_HW_SPEC
 * This structure defines the response for the GET_HW_SPEC command
 */
/** HostCmd_DS_GET_HW_SPEC */
typedef struct _HostCmd_DS_GET_HW_SPEC
{
    /* HW Interface version number */
    u16 HWIfVersion;

    /* HW version number */
    u16 Version;

    /* Max number of TxPD FW can handle */
    u16 NumOfTxPD;

    /* Max no of Multicast address  */
    u16 NumOfMCastAdr;

    /* MAC address */
    u8 PermanentAddr[6];

    /* Region Code */
    u16 RegionCode;

    /* Number of antenna used */
    u16 NumberOfAntenna;

    /* FW release number, example 0x1234=1.2.3.4 */
    u32 FWReleaseNumber;

    u32 Reserved_1;

    u32 Reserved_2;

    u32 Reserved_3;

    /*FW/HW Capability */
    u32 fwCapInfo;
} __ATTRIB_PACK__ HostCmd_DS_GET_HW_SPEC;

typedef struct _HostCmd_DS_802_11_SUBSCRIBE_EVENT
{
    u16 Action;
    u16 Events;
} __ATTRIB_PACK__ HostCmd_DS_802_11_SUBSCRIBE_EVENT;

/* 
 * This scan handle Country Information IE(802.11d compliant) 
 * Define data structure for HostCmd_CMD_802_11_SCAN 
 */
/** HostCmd_DS_802_11_SCAN */
typedef struct _HostCmd_DS_802_11_SCAN
{
    u8 BSSType;
    u8 BSSID[ETH_ALEN];
    u8 TlvBuffer[1];
    /* MrvlIEtypes_SsIdParamSet_t   SsIdParamSet; 
     * MrvlIEtypes_ChanListParamSet_t       ChanListParamSet;
     * MrvlIEtypes_RatesParamSet_t  OpRateSet; 
     * */
} __ATTRIB_PACK__ HostCmd_DS_802_11_SCAN;

typedef struct _HostCmd_DS_802_11_SCAN_RSP
{
    u16 BSSDescriptSize;
    u8 NumberOfSets;
    u8 BssDescAndTlvBuffer[1];

} __ATTRIB_PACK__ HostCmd_DS_802_11_SCAN_RSP;

/** HostCmd_CMD_802_11_GET_LOG */
typedef struct _HostCmd_DS_802_11_GET_LOG
{
    u32 mcasttxframe;
    u32 failed;
    u32 retry;
    u32 multiretry;
    u32 framedup;
    u32 rtssuccess;
    u32 rtsfailure;
    u32 ackfailure;
    u32 rxfrag;
    u32 mcastrxframe;
    u32 fcserror;
    u32 txframe;
    u32 reserved;
} __ATTRIB_PACK__ HostCmd_DS_802_11_GET_LOG;

/**  HostCmd_CMD_MAC_CONTROL */
typedef struct _HostCmd_DS_MAC_CONTROL
{
    u16 Action;
    u16 Reserved;
} __ATTRIB_PACK__ HostCmd_DS_MAC_CONTROL;

/**  HostCmd_CMD_MAC_MULTICAST_ADR */
typedef struct _HostCmd_DS_MAC_MULTICAST_ADR
{
    u16 Action;
    u16 NumOfAdrs;
    u8 MACList[MRVDRV_ETH_ADDR_LEN * MRVDRV_MAX_MULTICAST_LIST_SIZE];
} __ATTRIB_PACK__ HostCmd_DS_MAC_MULTICAST_ADR;

/**  HostCmd_CMD_802_11_DEAUTHENTICATE */
typedef struct _HostCmd_DS_802_11_DEAUTHENTICATE
{
    u8 MacAddr[6];
    u16 ReasonCode;
} __ATTRIB_PACK__ HostCmd_DS_802_11_DEAUTHENTICATE;

/** HostCmd_DS_802_11_ASSOCIATE */
typedef struct _HostCmd_DS_802_11_ASSOCIATE
{
    u8 PeerStaAddr[6];
    IEEEtypes_CapInfo_t CapInfo;
    u16 ListenInterval;
    u8 Reserved1[3];

    /*
     *  MrvlIEtypes_SsIdParamSet_t  SsIdParamSet;
     *  MrvlIEtypes_PhyParamSet_t   PhyParamSet;
     *  MrvlIEtypes_SsParamSet_t    SsParamSet;
     *  MrvlIEtypes_RatesParamSet_t RatesParamSet;
     */
} __ATTRIB_PACK__ HostCmd_DS_802_11_ASSOCIATE;

/** HostCmd_RET_802_11_ASSOCIATE */
typedef struct
{
    IEEEtypes_AssocRsp_t assocRsp;
} __ATTRIB_PACK__ HostCmd_DS_802_11_ASSOCIATE_RSP;

/**  HostCmd_RET_802_11_AD_HOC_JOIN */
typedef struct _HostCmd_DS_802_11_AD_HOC_RESULT
{
    u8 PAD[3];
    u8 BSSID[MRVDRV_ETH_ADDR_LEN];
} __ATTRIB_PACK__ HostCmd_DS_802_11_AD_HOC_RESULT;

/**  HostCmd_CMD_802_11_SET_WEP */
typedef struct _HostCmd_DS_802_11_SET_WEP
{
    /* ACT_ADD, ACT_REMOVE or ACT_ENABLE  */
    u16 Action;

    /* Key Index selected for Tx */
    u16 KeyIndex;

    /* 40, 128bit or TXWEP */
    u8 WEPTypeForKey1;

    u8 WEPTypeForKey2;
    u8 WEPTypeForKey3;
    u8 WEPTypeForKey4;
    u8 WEP1[16];
    u8 WEP2[16];
    u8 WEP3[16];
    u8 WEP4[16];
} __ATTRIB_PACK__ HostCmd_DS_802_11_SET_WEP;

/** HostCmd_DS_802_11_AD_HOC_STOP */
typedef struct _HostCmd_DS_802_11_AD_HOC_STOP		  // we will not support the AD HOC mode .dennis//
{
	u16 uninvalid1;
	u16 uninvalid2;
} __ATTRIB_PACK__ HostCmd_DS_802_11_AD_HOC_STOP;

/**  HostCmd_CMD_802_11_SNMP_MIB */
typedef struct _HostCmd_DS_802_11_SNMP_MIB
{
    u16 QueryType;
    u16 OID;
    u16 BufSize;
    u8 Value[128];
} __ATTRIB_PACK__ HostCmd_DS_802_11_SNMP_MIB;

/** HostCmd_CMD_MAC_REG_ACCESS */
typedef struct _HostCmd_DS_MAC_REG_ACCESS
{
    u16 Action;
    u16 Offset;
    u32 Value;
} __ATTRIB_PACK__ HostCmd_DS_MAC_REG_ACCESS;

/** HostCmd_CMD_BBP_REG_ACCESS */
typedef struct _HostCmd_DS_BBP_REG_ACCESS
{
    u16 Action;
    u16 Offset;
    u8 Value;
    u8 Reserved[3];
} __ATTRIB_PACK__ HostCmd_DS_BBP_REG_ACCESS;

/**  HostCmd_CMD_RF_REG_ACCESS */
typedef struct _HostCmd_DS_RF_REG_ACCESS
{
    u16 Action;
    u16 Offset;
    u8 Value;
    u8 Reserved[3];
} __ATTRIB_PACK__ HostCmd_DS_RF_REG_ACCESS;

/** HostCmd_CMD_802_11_RADIO_CONTROL */
typedef struct _HostCmd_DS_802_11_RADIO_CONTROL
{
    u16 Action;
    u16 Control;
} __ATTRIB_PACK__ HostCmd_DS_802_11_RADIO_CONTROL;

/* HostCmd_DS_802_11_SLEEP_PARAMS */
typedef struct _HostCmd_DS_802_11_SLEEP_PARAMS
{
    /* ACT_GET/ACT_SET */
    u16 Action;

    /* Sleep clock error in ppm */
    u16 Error;

    /* Wakeup offset in usec */
    u16 Offset;

    /* Clock stabilization time in usec */
    u16 StableTime;

    /* Control periodic calibration */
    u8 CalControl;

    /* Control the use of external sleep clock */
    u8 ExternalSleepClk;

    /* Reserved field, should be set to zero */
    u16 Reserved;
} __ATTRIB_PACK__ HostCmd_DS_802_11_SLEEP_PARAMS;

/* HostCmd_DS_802_11_SLEEP_PERIOD */
typedef struct _HostCmd_DS_802_11_SLEEP_PERIOD
{
    /* ACT_GET/ACT_SET */
    u16 Action;

    /* Sleep Period in msec */
    u16 Period;
} __ATTRIB_PACK__ HostCmd_DS_802_11_SLEEP_PERIOD;

/* HostCmd_DS_802_11_BCA_TIMESHARE */
typedef struct _HostCmd_DS_802_11_BCA_TIMESHARE
{
    /* ACT_GET/ACT_SET */
    u16 Action;

    /* Type: WLAN, BT */
    u16 TrafficType;

    /* 20msec - 60000msec */
    u32 TimeShareInterval;

    /* PTA arbiter time in msec */
    u32 BTTime;
} __ATTRIB_PACK__ HostCmd_DS_802_11_BCA_TIMESHARE;

/* HostCmd_DS_802_11_INACTIVITY_TIMEOUT */
typedef struct _HostCmd_DS_802_11_INACTIVITY_TIMEOUT
{
    /* ACT_GET/ACT_SET */
    u16 Action;

    /* Inactivity timeout in msec */
    u16 Timeout;
} __ATTRIB_PACK__ HostCmd_DS_802_11_INACTIVITY_TIMEOUT;

/** HostCmd_CMD_802_11_RF_CHANNEL */
typedef struct _HostCmd_DS_802_11_RF_CHANNEL
{
    u16 Action;
    u16 CurrentChannel;
    u16 RFType;
    u16 Reserved;
    u8 ChannelList[32];
} __ATTRIB_PACK__ HostCmd_DS_802_11_RF_CHANNEL;

/**  HostCmd_CMD_802_11_RSSI */
typedef struct _HostCmd_DS_802_11_RSSI
{
    /* weighting factor */
    u16 N;

    u16 Reserved_0;
    u16 Reserved_1;
    u16 Reserved_2;
} __ATTRIB_PACK__ HostCmd_DS_802_11_RSSI;

/** HostCmd_DS_802_11_RSSI_RSP */
typedef struct _HostCmd_DS_802_11_RSSI_RSP
{
    u16 SNR;
    u16 NoiseFloor;
    u16 AvgSNR;
    u16 AvgNoiseFloor;
} __ATTRIB_PACK__ HostCmd_DS_802_11_RSSI_RSP;

/** HostCmd_DS_802_11_MAC_ADDRESS */
typedef struct _HostCmd_DS_802_11_MAC_ADDRESS
{
    u16 Action;
    u8 MacAdd[ETH_ALEN];
} __ATTRIB_PACK__ HostCmd_DS_802_11_MAC_ADDRESS;

/** HostCmd_CMD_802_11_RF_TX_POWER */
typedef struct _HostCmd_DS_802_11_RF_TX_POWER
{
    u16 Action;
    u16 CurrentLevel;
    u8 MaxPower;
    u8 MinPower;
} __ATTRIB_PACK__ HostCmd_DS_802_11_RF_TX_POWER;

/** HostCmd_CMD_802_11_RF_ANTENNA */
typedef struct _HostCmd_DS_802_11_RF_ANTENNA
{
    u16 Action;

    /*  Number of antennas or 0xffff(diversity) */
    u16 AntennaMode;

} __ATTRIB_PACK__ HostCmd_DS_802_11_RF_ANTENNA;

/** HostCmd_CMD_802_11_PS_MODE */
typedef struct _HostCmd_DS_802_11_PS_MODE
{
    u16 Action;
    u16 NullPktInterval;
    u16 MultipleDtim;
    u16 BCNMissTimeOut;
    u16 LocalListenInterval;
    u16 AdhocAwakePeriod;
} __ATTRIB_PACK__ HostCmd_DS_802_11_PS_MODE;

/** PS_CMD_ConfirmSleep */
typedef struct _PS_CMD_ConfirmSleep
{
    u16 Command;
    u16 Size;
    u16 SeqNum;
    u16 Result;

    u16 Action;
    u16 Reserved1;
    u16 MultipleDtim;
    u16 Reserved;
    u16 LocalListenInterval;
} __ATTRIB_PACK__ PS_CMD_ConfirmSleep, *PPS_CMD_ConfirmSleep;

/** HostCmd_CMD_802_11_FW_WAKE_METHOD */
typedef struct _HostCmd_DS_802_11_FW_WAKEUP_METHOD
{
    u16 Action;
    u16 Method;
} __ATTRIB_PACK__ HostCmd_DS_802_11_FW_WAKEUP_METHOD;

/** HostCmd_DS_802_11_RATE_ADAPT_RATESET */
typedef struct _HostCmd_DS_802_11_RATE_ADAPT_RATESET
{
    u16 Action;
    u16 HWRateDropMode;
    u16 Bitmap;
    u16 Threshold;
    u16 FinalRate;
} __ATTRIB_PACK__ HostCmd_DS_802_11_RATE_ADAPT_RATESET;

/** HostCmd_DS_802_11_AD_HOC_START*/
typedef struct _HostCmd_DS_802_11_AD_HOC_START
{
    u8 SSID[MRVDRV_MAX_SSID_LENGTH];
    u8 BSSType;
    u16 BeaconPeriod;
    u8 DTIMPeriod;
    IEEEtypes_SsParamSet_t SsParamSet;
    IEEEtypes_PhyParamSet_t PhyParamSet;
    u16 Reserved1;
    IEEEtypes_CapInfo_t Cap;
    u8 DataRate[HOSTCMD_SUPPORTED_RATES];
    u8 tlv_memory_size_pad[100];
} __ATTRIB_PACK__ HostCmd_DS_802_11_AD_HOC_START;

/** AdHoc_BssDesc_t */
typedef struct _AdHoc_BssDesc_t
{
    u8 BSSID[6];
    u8 SSID[32];
    u8 BSSType;
    u16 BeaconPeriod;
    u8 DTIMPeriod;
    u8 TimeStamp[8];
    u8 LocalTime[8];
    IEEEtypes_PhyParamSet_t PhyParamSet;
    IEEEtypes_SsParamSet_t SsParamSet;
    IEEEtypes_CapInfo_t Cap;
    u8 DataRates[HOSTCMD_SUPPORTED_RATES];

    /* DO NOT ADD ANY FIELDS TO THIS STRUCTURE.      It is used below in the
     *      Adhoc join command and will cause a binary layout mismatch with 
     *      the firmware 
     */
} __ATTRIB_PACK__ AdHoc_BssDesc_t;

/** HostCmd_DS_802_11_AD_HOC_JOIN */
typedef struct _HostCmd_DS_802_11_AD_HOC_JOIN
{
    AdHoc_BssDesc_t BssDescriptor;
    u16 Reserved1;
    u16 Reserved2;

} __ATTRIB_PACK__ HostCmd_DS_802_11_AD_HOC_JOIN;

typedef union _KeyInfo_WEP_t
{
    u8 Reserved;

    /* bits 1-4: Specifies the index of key */
    u8 WepKeyIndex;

    /* bit 0: Specifies that this key is 
     * to be used as the default for TX data packets 
     * */
    u8 isWepDefaultKey;
} __ATTRIB_PACK__ KeyInfo_WEP_t;

typedef union _KeyInfo_TKIP_t
{
    u8 Reserved;

    /* bit 2: Specifies that this key is 
     * enabled and valid to use */
    u8 isKeyEnabled;

    /* bit 1: Specifies that this key is
     * to be used as the unicast key */
    u8 isUnicastKey;

    /* bit 0: Specifies that this key is 
     * to be used as the multicast key */
    u8 isMulticastKey;
} __ATTRIB_PACK__ KeyInfo_TKIP_t;

typedef union _KeyInfo_AES_t
{
    u8 Reserved;

    /* bit 2: Specifies that this key is
     * enabled and valid to use */
    u8 isKeyEnabled;

    /* bit 1: Specifies that this key is
     * to be used as the unicast key */
    u8 isUnicastKey;

    /* bit 0: Specifies that this key is 
     * to be used as the multicast key */
    u8 isMulticastKey;
} __ATTRIB_PACK__ KeyInfo_AES_t;

/** KeyMaterial_TKIP_t */
typedef struct _KeyMaterial_TKIP_t
{
    /* TKIP encryption/decryption key */
    u8 TkipKey[16];

    /* TKIP TX MIC Key */
    u8 TkipTxMicKey[16];

    /* TKIP RX MIC Key */
    u8 TkipRxMicKey[16];
} __ATTRIB_PACK__ KeyMaterial_TKIP_t, *PKeyMaterial_TKIP_t;

/** KeyMaterial_AES_t */
typedef struct _KeyMaterial_AES_t
{
    /* AES encryption/decryption key */
    u8 AesKey[16];
} __ATTRIB_PACK__ KeyMaterial_AES_t, *PKeyMaterial_AES_t;

/** MrvlIEtype_KeyParamSet_t */
typedef struct _MrvlIEtype_KeyParamSet_t
{
    /* Type ID */
    u16 Type;

    /* Length of Payload */
    u16 Length;

    /* Type of Key: WEP=0, TKIP=1, AES=2 */
    u16 KeyTypeId;

    /* Key Control Info specific to a KeyTypeId */
    u16 KeyInfo;

    /* Length of key */
    u16 KeyLen;

    /* Key material of size KeyLen */
    u8 Key[32];
} __ATTRIB_PACK__ MrvlIEtype_KeyParamSet_t, *PMrvlIEtype_KeyParamSet_t;

/** HostCmd_DS_802_11_KEY_MATERIAL */
typedef struct _HostCmd_DS_802_11_KEY_MATERIAL
{
    u16 Action;

    MrvlIEtype_KeyParamSet_t KeyParamSet;
} __ATTRIB_PACK__ HostCmd_DS_802_11_KEY_MATERIAL;

/** HostCmd_DS_802_11_HOST_SLEEP_CFG */
typedef struct _HostCmd_DS_HOST_802_11_HOST_SLEEP_CFG
{
    /* bit0=1: non-unicast data
     * bit1=1: unicast data
     * bit2=1: mac events
     * bit3=1: magic packet 
     */
    u32 conditions;

    u8 gpio;

    /* in milliseconds */
    u8 gap;
} __ATTRIB_PACK__ HostCmd_DS_802_11_HOST_SLEEP_CFG;

/** HostCmd_DS_802_11_CAL_DATA_EXT */
typedef struct _HostCmd_DS_802_11_CAL_DATA_EXT
{
    u16 Action;
    u16 Revision;
    u16 CalDataLen;
    u8 CalData[1024];
} __ATTRIB_PACK__ HostCmd_DS_802_11_CAL_DATA_EXT;

/** HostCmd_DS_802_11_EEPROM_ACCESS */
typedef struct _HostCmd_DS_802_11_EEPROM_ACCESS
{
    u16 Action;

    /* multiple 4 */
    u16 Offset;
    u16 ByteCount;
    u8 Value;
} __ATTRIB_PACK__ HostCmd_DS_802_11_EEPROM_ACCESS;

/** HostCmd_DS_CMD_GSPI_BUS_CONFIG */
typedef struct _HostCmd_DS_CMD_GSPI_BUS_CONFIG
{
    u16 Action;

    /* Data format Bit[1:0], Delay method Bit[2] */
    /* 1--Number of dummy clocks to wait for read r/w port */
    /* 0--Number of 10ns to wait for read r/w port */
    u16 BusDelayMode;

    /*Host time delay to read GSPI port register */
    u16 HostTimeDelayToReadPort;
    /*Host time delay to read GSPI register */
    u16 HostTimeDelayToReadregister;
} __ATTRIB_PACK__ HostCmd_DS_CMD_GSPI_BUS_CONFIG;

/** HostCmd_DS_802_11_BG_SCAN_CONFIG */
typedef struct _HostCmd_DS_802_11_BG_SCAN_CONFIG
{
    /** Action */
    u16 Action;

    /** 
     *  Enable/Disable
     *  0 - Disable
     *  1 - Enable 
     */
    u8 Enable;

    /**
     *  bssType
     *  1 - Infrastructure
     *  2 - IBSS
     *  3 - any 
     */
    u8 BssType;

    /** 
     * ChannelsPerScan 
     *   Number of channels to scan during a single scanning opportunity
     */
    u8 ChannelsPerScan;

    u8 Reserved1[3];

    /** ScanInterval */
    u32 ScanInterval;

    /**
     * StoreCondition
     * - SSID Match
     * - SSID Match & Exceed SNR Threshold 
     */
    u32 StoreCondition;

    /** 
     * ReportConditions
     * - SSID Match
     * - SSID Match & Exceed SNR Threshold
     */
    u32 ReportConditions;

    u16 Reserved2;

    /*  Attach TLV based parameters as needed:
     *
     *  MrvlIEtypes_SsIdParamSet_t          Set specific SSID filter
     *  MrvlIEtypes_ChanListParamSet_t      Set the channels & channel params
     *  MrvlIEtypes_NumProbes_t             Number of probes per SSID/broadcast
     *  MrvlIEtypes_WildCardSsIdParamSet_t  Wildcard SSID matching patterns
     *  MrvlIEtypes_SnrThreshold_t          SNR Threshold for match/report  
     */

} __ATTRIB_PACK__ HostCmd_DS_802_11_BG_SCAN_CONFIG;

/** HostCmd_DS_802_11_BG_SCAN_QUERY */
typedef struct _HostCmd_DS_802_11_BG_SCAN_QUERY
{
    u8 Flush;
} __ATTRIB_PACK__ HostCmd_DS_802_11_BG_SCAN_QUERY;

/** HostCmd_DS_802_11_BG_SCAN_QUERY_RSP */
typedef struct _HostCmd_DS_802_11_BG_SCAN_QUERY_RSP
{
    u32 ReportCondition;
    HostCmd_DS_802_11_SCAN_RSP scanresp;
} __ATTRIB_PACK__ HostCmd_DS_802_11_BG_SCAN_QUERY_RSP;

/** HostCmd_DS_802_11_TPC_CFG */
typedef struct _HostCmd_DS_802_11_TPC_CFG
{
    u16 Action;
    u8 Enable;
    s8 P0;
    s8 P1;
    s8 P2;
    u8 UseSNR;
} __ATTRIB_PACK__ HostCmd_DS_802_11_TPC_CFG;

/** HostCmd_DS_802_11_LED_CTRL */
typedef struct _HostCmd_DS_802_11_LED_CTRL
{
    u16 Action;                 /* 0 = ACT_GET; 1 = ACT_SET; */
    u16 LedNums;                /* Numbers of LEDs supported */
    MrvlIEtypes_LedGpio_t LedGpio;
    MrvlIEtypes_LedBehavior_t LedBehavior[1];
} __ATTRIB_PACK__ HostCmd_DS_802_11_LED_CTRL;

/** HostCmd_DS_802_11_POWER_ADAPT_CFG_EXT */
typedef struct _HostCmd_DS_802_11_POWER_ADAPT_CFG_EXT
{
        /** Action */
    u16 Action;                 /* 0 = ACT_GET; 1 = ACT_SET; */
    u16 EnablePA;               /* 0 = disable; 1 = enable; */
    MrvlIEtypes_PowerAdapt_Group_t PowerAdaptGroup;
} __ATTRIB_PACK__ HostCmd_DS_802_11_POWER_ADAPT_CFG_EXT;

typedef struct _HostCmd_DS_802_11_IBSS_Status
{
    u16 Action;
    u16 Enable;
    u8 BSSID[ETH_ALEN];
    u16 BeaconInterval;
    u16 ATIMWindow;
    u16 UseGRateProtection;
} __ATTRIB_PACK__ HostCmd_DS_802_11_IBSS_Status;

#define CIPHER_TEST_RC4 (1)
#define CIPHER_TEST_AES (2)
#define CIPHER_TEST_AES_KEY_WRAP (3)

/** HostCmd_DS_802_11_CRYPTO */
typedef struct _HostCmd_DS_802_11_CRYPTO
{
    u16 EncDec;                 //Decrypt=0, Encrypt=1
    u16 Algorithm;              // RC4=1 AES=2 , AES_KEY_WRAP=3
    u16 KeyIVLength;            //Length of Key IV (bytes)              
    u8 KeyIV[32];               //Key IV
    u16 KeyLength;              //Length of Key (bytes)
    u8 Key[32];                 //Key
    /* MrvlIEtypes_Data_t   data  Plain text if EncDec=Encrypt, Ciphertext data if EncDec=Decrypt */
} __ATTRIB_PACK__ HostCmd_DS_802_11_CRYPTO;

typedef struct _HostCmd_TX_RATE_QUERY
{
    u16 TxRate;
} __ATTRIB_PACK__ HostCmd_TX_RATE_QUERY;

/** HostCmd_DS_802_11_AUTO_TX */
typedef struct _HostCmd_DS_802_11_AUTO_TX
{
        /** Action */
    u16 Action;                 /* 0 = ACT_GET; 1 = ACT_SET; */
    MrvlIEtypes_AutoTx_t AutoTx;
} __ATTRIB_PACK__ HostCmd_DS_802_11_AUTO_TX;

/** HostCmd_MEM_ACCESS */
typedef struct _HostCmd_DS_MEM_ACCESS
{
        /** Action */
    u16 Action;                 /* 0 = ACT_GET; 1 = ACT_SET; */
    u16 Reserved;
    u32 Addr;
    u32 Value;
} __ATTRIB_PACK__ HostCmd_DS_MEM_ACCESS;

typedef struct
{
    u64 TsfValue;
} __ATTRIB_PACK__ HostCmd_DS_GET_TSF;

#define	LDO_INTERNAL	0
#define LDO_EXTERNAL	1

typedef struct _HostCmd_DS_802_11_LDO_CONFIG
{
    u16 Action;                 /* 0 = ACT_GET; 1 = ACT_SET; */
    u16 PMSource;               /* 0 = LDO_INTERNAL; 1 = LDO_EXTERNAL */
}  HostCmd_DS_802_11_LDO_CONFIG;

typedef struct _HostCmd_DS_VERSION_EXT
{
    u8 versionStrSel;
    char versionStr[128];
}  HostCmd_DS_VERSION_EXT;

/** Define data structure for HostCmd_CMD_802_11D_DOMAIN_INFO */
typedef struct _HostCmd_DS_802_11D_DOMAIN_INFO
{
    u16 Action;
    MrvlIEtypes_DomainParamSet_t Domain;
}  HostCmd_DS_802_11D_DOMAIN_INFO;

/** Define data structure for HostCmd_RET_802_11D_DOMAIN_INFO */
typedef struct _HostCmd_DS_802_11D_DOMAIN_INFO_RSP
{
    u16 Action;
    MrvlIEtypes_DomainParamSet_t Domain;
}  HostCmd_DS_802_11D_DOMAIN_INFO_RSP;

typedef struct
{
    u32 PktInitCnt;
    u32 PktSuccessCnt;
    u32 TxAttempts;
    u32 RetryFailure;
    u32 ExpiryFailure;
}  HostCmd_DS_TX_PKT_STAT_Entry;

typedef struct
{
    HostCmd_DS_TX_PKT_STAT_Entry StatEntry[HOSTCMD_SUPPORTED_RATES];
} HostCmd_DS_TX_PKT_STATS;

/** _HostCmd_DS_COMMAND*/
struct _HostCmd_DS_COMMAND
{

    /** Command Header */
    u16 Command;
    u16 Size;
    u16 SeqNum;
    u16 Result;

    /** Command Body */
    union
    {
        HostCmd_DS_GET_HW_SPEC hwspec;
        HostCmd_DS_802_11_PS_MODE psmode;
        HostCmd_DS_802_11_SCAN scan;
        HostCmd_DS_802_11_SCAN_RSP scanresp;
        HostCmd_DS_MAC_CONTROL macctrl;
        HostCmd_DS_802_11_ASSOCIATE associate;
        HostCmd_DS_802_11_ASSOCIATE_RSP associatersp;
        HostCmd_DS_802_11_DEAUTHENTICATE deauth;
        HostCmd_DS_802_11_SET_WEP wep;
        HostCmd_DS_802_11_AD_HOC_START ads;
        HostCmd_DS_802_11_AD_HOC_RESULT result;
        HostCmd_DS_802_11_GET_LOG glog;
        HostCmd_DS_802_11_SNMP_MIB smib;
        HostCmd_DS_802_11_RF_TX_POWER txp;
        HostCmd_DS_802_11_RF_ANTENNA rant;
        HostCmd_DS_802_11_RATE_ADAPT_RATESET rateset;
        HostCmd_DS_MAC_MULTICAST_ADR madr;
        HostCmd_DS_802_11_AD_HOC_JOIN adj;
        HostCmd_DS_802_11_RADIO_CONTROL radio;
        HostCmd_DS_802_11_RF_CHANNEL rfchannel;
        HostCmd_DS_802_11_RSSI rssi;
        HostCmd_DS_802_11_RSSI_RSP rssirsp;
        HostCmd_DS_802_11_AD_HOC_STOP adhoc_stop;
        HostCmd_DS_802_11_MAC_ADDRESS macadd;
        HostCmd_DS_802_11_KEY_MATERIAL keymaterial;
        HostCmd_DS_MAC_REG_ACCESS macreg;
        HostCmd_DS_BBP_REG_ACCESS bbpreg;
        HostCmd_DS_RF_REG_ACCESS rfreg;
        HostCmd_DS_802_11_CAL_DATA_EXT caldataext;
        HostCmd_DS_802_11_HOST_SLEEP_CFG hostsleepcfg;
        HostCmd_DS_802_11_EEPROM_ACCESS rdeeprom;
        HostCmd_DS_CMD_GSPI_BUS_CONFIG gspicfg;

        HostCmd_DS_802_11D_DOMAIN_INFO domaininfo;
        HostCmd_DS_802_11D_DOMAIN_INFO_RSP domaininforesp;
        HostCmd_DS_802_11_BG_SCAN_CONFIG bgscancfg;
        HostCmd_DS_802_11_BG_SCAN_QUERY bgscanquery;
        HostCmd_DS_802_11_BG_SCAN_QUERY_RSP bgscanqueryresp;
        HostCmd_DS_WMM_GET_STATUS getWmmStatus;
        HostCmd_DS_WMM_ADDTS_REQ addTsReq;
        HostCmd_DS_WMM_DELTS_REQ delTsReq;
        HostCmd_DS_WMM_QUEUE_CONFIG queueConfig;
        HostCmd_DS_WMM_QUEUE_STATS queueStats;
        HostCmd_DS_TX_PKT_STATS txPktStats;
        HostCmd_DS_802_11_SLEEP_PARAMS sleep_params;
        HostCmd_DS_802_11_BCA_TIMESHARE bca_timeshare;
        HostCmd_DS_802_11_INACTIVITY_TIMEOUT inactivity_timeout;
        HostCmd_DS_802_11_SLEEP_PERIOD ps_sleeppd;
        HostCmd_DS_802_11_TPC_CFG tpccfg;
        HostCmd_DS_802_11_LED_CTRL ledgpio;
        HostCmd_DS_802_11_FW_WAKEUP_METHOD fwwakeupmethod;

        HostCmd_DS_802_11_CRYPTO crypto;
        HostCmd_TX_RATE_QUERY txrate;
        HostCmd_DS_GET_TSF gettsf;
        HostCmd_DS_802_11_IBSS_Status ibssCoalescing;
        HostCmd_DS_802_11_LDO_CONFIG ldocfg;
        HostCmd_DS_VERSION_EXT verext;
    } params;
} ;

#endif
