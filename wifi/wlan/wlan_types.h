/** @file wlan_types.h
 *  @brief This header file contains definition for global types
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
 */
/*************************************************************
Change log:
	10/11/05: add Doxygen format comments 
	01/11/06: Add IEEE Association response type. Add TSF TLV information.
	01/31/06: Add support to selectively enabe the FW Scan channel filter
	04/10/06: Add power_adapt_cfg_ext command
	04/18/06: Remove old Subscrive Event and add new Subscribe Event
	          implementation through generic hostcmd API
	05/03/06: Add auto_tx hostcmd
	08/28/06: Add LED_CTRL hostcmd
************************************************************/

#ifndef _WLAN_TYPES_
#define _WLAN_TYPES_


typedef char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed long s32;
typedef unsigned long u32;

typedef signed long long s64;
typedef unsigned long long u64;

typedef u32 dma_addr_t;
typedef u32 dma64_addr_t;
/* Dma addresses are 32-bits wide.  */
#ifndef __ATTRIB_ALIGN__
//#define __ATTRIB_ALIGN__ __attribute__((aligned(4)))
#define __ATTRIB_ALIGN__  //(__aligned(4))
#endif

#ifndef __ATTRIB_PACK__
//#define __ATTRIB_PACK__ __attribute__ ((packed))
#define __ATTRIB_PACK__   //changed by dennis for compiler compatibility 
#endif


typedef long LONG;
typedef unsigned long long ULONGLONG;
typedef u32 WLAN_OID;

#define MRVDRV_MAX_MULTICAST_LIST_SIZE	32
#define MRVDRV_MAX_CHANNEL_SIZE		14
#define MRVDRV_ETH_ADDR_LEN             6
#define MRVDRV_MAX_SSID_LENGTH			32
#define MRVDRV_MAX_BSS_DESCRIPTS		16
/** WEP list macros & data structures */
#define MRVL_KEY_BUFFER_SIZE_IN_BYTE  16
#define MRVL_MAX_KEY_WPA_KEY_LENGTH     32

#define HOSTCMD_SUPPORTED_RATES G_SUPPORTED_RATES

#define	BAND_B			(0x01)
#define	BAND_G			(0x02)
#define ALL_802_11_BANDS	(BAND_B | BAND_G)

#define B_SUPPORTED_RATES		8
#define G_SUPPORTED_RATES		14

#define	WLAN_SUPPORTED_RATES		14
#define WLAN_MAX_SSID_LENGTH		32

#define	MAX_POWER_ADAPT_GROUP		5
#ifndef	ETH_ALEN				  //add by dennis
#define ETH_ALEN			6
#endif
typedef u8 WLAN_802_11_RATES[WLAN_SUPPORTED_RATES];
typedef u8 WLAN_802_11_MAC_ADDRESS[ETH_ALEN];

/** WLAN_802_11_NETWORK_TYPE */
typedef enum _WLAN_802_11_NETWORK_TYPE
{
    Wlan802_11FH,
    Wlan802_11DS,
    /*defined as upper bound */
    Wlan802_11NetworkTypeMax
} WLAN_802_11_NETWORK_TYPE, *PWLAN_802_11_NETWORK_TYPE;

/** WLAN_802_11_NETWORK_INFRASTRUCTURE */
typedef enum _WLAN_802_11_NETWORK_INFRASTRUCTURE
{
    Wlan802_11IBSS,
    Wlan802_11Infrastructure,
    Wlan802_11AutoUnknown,
    /*defined as upper bound */
    Wlan802_11InfrastructureMax
} WLAN_802_11_NETWORK_INFRASTRUCTURE, *PWLAN_802_11_NETWORK_INFRASTRUCTURE;

#define IEEE_MAX_IE_SIZE  256

/** IEEE Type definitions  */
typedef enum _IEEEtypes_ElementId_e
{
    SSID = 0,
    SUPPORTED_RATES = 1,
    FH_PARAM_SET = 2,
    DS_PARAM_SET = 3,
    CF_PARAM_SET = 4,

    IBSS_PARAM_SET = 6,

    COUNTRY_INFO = 7,

    ERP_INFO = 42,
    EXTENDED_SUPPORTED_RATES = 50,

    VENDOR_SPECIFIC_221 = 221,
    WMM_IE = VENDOR_SPECIFIC_221,

    WPS_IE = VENDOR_SPECIFIC_221,

    WPA_IE = VENDOR_SPECIFIC_221,
    RSN_IE = 48,

    EXTRA_IE = 133,
} __ATTRIB_PACK__ IEEEtypes_ElementId_e;

#define CAPINFO_MASK    (~( W_BIT_15 | W_BIT_14 |               \
                            W_BIT_12 | W_BIT_11 | W_BIT_9) )

typedef struct _IEEEtypes_CapInfo_t
{
    u8 Ess:1;
    u8 Ibss:1;
    u8 CfPollable:1;
    u8 CfPollRqst:1;
    u8 Privacy:1;
    u8 ShortPreamble:1;
    u8 Pbcc:1;
    u8 ChanAgility:1;
    u8 SpectrumMgmt:1;
    u8 Rsrvd3:1;
    u8 ShortSlotTime:1;
    u8 Apsd:1;
    u8 Rsvrd2:1;
    u8 DSSSOFDM:1;
    u8 Rsrvd1:2;
} __ATTRIB_PACK__ IEEEtypes_CapInfo_t;

typedef struct
{
    u8 ElementId;
    u8 Len;
} __ATTRIB_PACK__ IEEEtypes_Header_t;

/** IEEEtypes_CfParamSet_t */
typedef struct _IEEEtypes_CfParamSet_t
{
    u8 ElementId;
    u8 Len;
    u8 CfpCnt;
    u8 CfpPeriod;
    u16 CfpMaxDuration;
    u16 CfpDurationRemaining;
} __ATTRIB_PACK__ IEEEtypes_CfParamSet_t;

typedef struct IEEEtypes_IbssParamSet_t
{
    u8 ElementId;
    u8 Len;
    u16 AtimWindow;
} __ATTRIB_PACK__ IEEEtypes_IbssParamSet_t;

/** IEEEtypes_SsParamSet_t */
typedef union _IEEEtypes_SsParamSet_t
{
    IEEEtypes_CfParamSet_t CfParamSet;
    IEEEtypes_IbssParamSet_t IbssParamSet;
} __ATTRIB_PACK__ IEEEtypes_SsParamSet_t;

/** IEEEtypes_FhParamSet_t */
typedef struct _IEEEtypes_FhParamSet_t
{
    u8 ElementId;
    u8 Len;
    u16 DwellTime;
    u8 HopSet;
    u8 HopPattern;
    u8 HopIndex;
} __ATTRIB_PACK__ IEEEtypes_FhParamSet_t;

typedef struct _IEEEtypes_DsParamSet_t
{
    u8 ElementId;
    u8 Len;
    u8 CurrentChan;
} __ATTRIB_PACK__ IEEEtypes_DsParamSet_t;

/** IEEEtypes_DsParamSet_t */
typedef union IEEEtypes_PhyParamSet_t
{
    IEEEtypes_FhParamSet_t FhParamSet;
    IEEEtypes_DsParamSet_t DsParamSet;
} __ATTRIB_PACK__ IEEEtypes_PhyParamSet_t;

typedef struct _IEEEtypes_ERPInfo_t
{
    u8 ElementId;
    u8 Len;
    u8 ERPFlags;
} __ATTRIB_PACK__ IEEEtypes_ERPInfo_t;

typedef u16 IEEEtypes_AId_t;
typedef u16 IEEEtypes_StatusCode_t;

typedef struct
{
    IEEEtypes_CapInfo_t Capability;
    IEEEtypes_StatusCode_t StatusCode;
    IEEEtypes_AId_t AId;
    u8 IEBuffer[1];
} __ATTRIB_PACK__ IEEEtypes_AssocRsp_t;

typedef struct
{
    u8 ElementId;
    u8 Len;
    u8 Oui[3];
    u8 OuiType;
    u8 OuiSubtype;
    u8 Version;
} __ATTRIB_PACK__ IEEEtypes_VendorHeader_t;

typedef struct
{
    IEEEtypes_VendorHeader_t VendHdr;

    /* IE Max - size of previous fields */
    u8 Data[IEEE_MAX_IE_SIZE - sizeof(IEEEtypes_VendorHeader_t)];

}
__ATTRIB_PACK__ IEEEtypes_VendorSpecific_t;

typedef struct
{
    IEEEtypes_Header_t IeeeHdr;

    /* IE Max - size of previous fields */
    u8 Data[IEEE_MAX_IE_SIZE - sizeof(IEEEtypes_Header_t)];

}
__ATTRIB_PACK__ IEEEtypes_Generic_t;

/** TLV  type ID definition */
#define PROPRIETARY_TLV_BASE_ID		0x0100

/* Terminating TLV Type */
#define MRVL_TERMINATE_TLV_ID		0xffff

#define TLV_TYPE_SSID				0x0000
#define TLV_TYPE_RATES				0x0001
#define TLV_TYPE_PHY_FH				0x0002
#define TLV_TYPE_PHY_DS				0x0003
#define TLV_TYPE_CF				    0x0004
#define TLV_TYPE_IBSS				0x0006

#define TLV_TYPE_DOMAIN				0x0007

#define TLV_TYPE_POWER_CAPABILITY   0x0021

#define TLV_TYPE_KEY_MATERIAL       (PROPRIETARY_TLV_BASE_ID + 0)
#define TLV_TYPE_CHANLIST           (PROPRIETARY_TLV_BASE_ID + 1)
#define TLV_TYPE_NUMPROBES          (PROPRIETARY_TLV_BASE_ID + 2)
#define TLV_TYPE_RSSI_LOW           (PROPRIETARY_TLV_BASE_ID + 4)
#define TLV_TYPE_SNR_LOW            (PROPRIETARY_TLV_BASE_ID + 5)
#define TLV_TYPE_FAILCOUNT          (PROPRIETARY_TLV_BASE_ID + 6)
#define TLV_TYPE_BCNMISS            (PROPRIETARY_TLV_BASE_ID + 7)
#define TLV_TYPE_LED_GPIO           (PROPRIETARY_TLV_BASE_ID + 8)
#define TLV_TYPE_LEDBEHAVIOR        (PROPRIETARY_TLV_BASE_ID + 9)
#define TLV_TYPE_PASSTHROUGH        (PROPRIETARY_TLV_BASE_ID + 10)
#define TLV_TYPE_POWER_TBL_2_4GHZ   (PROPRIETARY_TLV_BASE_ID + 12)
#define TLV_TYPE_POWER_TBL_5GHZ     (PROPRIETARY_TLV_BASE_ID + 13)
#define TLV_TYPE_WMMQSTATUS         (PROPRIETARY_TLV_BASE_ID + 16)
#define TLV_TYPE_CRYPTO_DATA        (PROPRIETARY_TLV_BASE_ID + 17)
#define TLV_TYPE_WILDCARDSSID       (PROPRIETARY_TLV_BASE_ID + 18)
#define TLV_TYPE_TSFTIMESTAMP       (PROPRIETARY_TLV_BASE_ID + 19)
#define TLV_TYPE_POWERADAPTCFGEXT   (PROPRIETARY_TLV_BASE_ID + 20)
#define TLV_TYPE_RSSI_HIGH          (PROPRIETARY_TLV_BASE_ID + 22)
#define TLV_TYPE_SNR_HIGH           (PROPRIETARY_TLV_BASE_ID + 23)
#define TLV_TYPE_AUTO_TX            (PROPRIETARY_TLV_BASE_ID + 24)
#define TLV_TYPE_WPS_ENROLLEE_PROBE_REQ_TLV    (PROPRIETARY_TLV_BASE_ID + 27)

#define TLV_TYPE_STARTBGSCANLATER   (PROPRIETARY_TLV_BASE_ID + 30)
#define TLV_TYPE_AUTH_TYPE          (PROPRIETARY_TLV_BASE_ID + 31)

/** TLV related data structures*/
/** MrvlIEtypesHeader_t */
typedef struct _MrvlIEtypesHeader
{
    u16 Type;
    u16 Len;
} __ATTRIB_PACK__ MrvlIEtypesHeader_t;

/** MrvlIEtypes_Data_t */
typedef struct _MrvlIEtypes_Data_t
{
    MrvlIEtypesHeader_t Header;
    u8 Data[1];
} __ATTRIB_PACK__ MrvlIEtypes_Data_t;

/** MrvlIEtypes_RatesParamSet_t */
typedef struct _MrvlIEtypes_RatesParamSet_t
{
    MrvlIEtypesHeader_t Header;
    u8 Rates[1];
} __ATTRIB_PACK__ MrvlIEtypes_RatesParamSet_t;

/** MrvlIEtypes_SsIdParamSet_t */
typedef struct _MrvlIEtypes_SsIdParamSet_t
{
    MrvlIEtypesHeader_t Header;
    u8 SsId[1];
} __ATTRIB_PACK__ MrvlIEtypes_SsIdParamSet_t;

/** MrvlIEtypes_WildCardSsIdParamSet_t */
typedef struct _MrvlIEtypes_WildCardSsIdParamSet_t
{
    MrvlIEtypesHeader_t Header;
    u8 MaxSsidLength;
    u8 SsId[1];
} __ATTRIB_PACK__ MrvlIEtypes_WildCardSsIdParamSet_t;

/** ChanScanMode_t */
typedef struct
{
    u8 PassiveScan:1;
    u8 DisableChanFilt:1;
    u8 Reserved_2_7:6;
} __ATTRIB_PACK__ ChanScanMode_t;

/** ChanScanParamSet_t */
typedef struct _ChanScanParamSet_t
{
    u8 RadioType;
    u8 ChanNumber;
    ChanScanMode_t ChanScanMode;
    u16 MinScanTime;
    u16 MaxScanTime;
} __ATTRIB_PACK__ ChanScanParamSet_t;

/** MrvlIEtypes_ChanListParamSet_t */
typedef struct _MrvlIEtypes_ChanListParamSet_t
{
    MrvlIEtypesHeader_t Header;
    ChanScanParamSet_t ChanScanParam[1];
} __ATTRIB_PACK__ MrvlIEtypes_ChanListParamSet_t;

/** CfParamSet_t */
typedef struct _CfParamSet_t
{
    u8 CfpCnt;
    u8 CfpPeriod;
    u16 CfpMaxDuration;
    u16 CfpDurationRemaining;
} __ATTRIB_PACK__ CfParamSet_t;

/** IbssParamSet_t */
typedef struct _IbssParamSet_t
{
    u16 AtimWindow;
} __ATTRIB_PACK__ IbssParamSet_t;

/** MrvlIEtypes_SsParamSet_t */
typedef struct _MrvlIEtypes_SsParamSet_t
{
    MrvlIEtypesHeader_t Header;
    union
    {
        CfParamSet_t CfParamSet[1];
        IbssParamSet_t IbssParamSet[1];
    } cf_ibss;
} __ATTRIB_PACK__ MrvlIEtypes_SsParamSet_t;

/** FhParamSet_t */
typedef struct _FhParamSet_t
{
    u16 DwellTime;
    u8 HopSet;
    u8 HopPattern;
    u8 HopIndex;
} __ATTRIB_PACK__ FhParamSet_t;

/** DsParamSet_t */
typedef struct _DsParamSet_t
{
    u8 CurrentChan;
} __ATTRIB_PACK__ DsParamSet_t;

/** MrvlIEtypes_PhyParamSet_t */
typedef struct _MrvlIEtypes_PhyParamSet_t
{
    MrvlIEtypesHeader_t Header;
    union
    {
        FhParamSet_t FhParamSet[1];
        DsParamSet_t DsParamSet[1];
    } fh_ds;
} __ATTRIB_PACK__ MrvlIEtypes_PhyParamSet_t;

/** MrvlIEtypes_RsnParamSet_t */
typedef struct _MrvlIEtypes_RsnParamSet_t
{
    MrvlIEtypesHeader_t Header;
    u8 RsnIE[1];
} __ATTRIB_PACK__ MrvlIEtypes_RsnParamSet_t;

/** MrvlIEtypes_WmmParamSet_t */
typedef struct _MrvlIEtypes_WmmParamSet_t
{
    MrvlIEtypesHeader_t Header;
    u8 WmmIE[1];
} __ATTRIB_PACK__ MrvlIEtypes_WmmParamSet_t;

typedef struct
{
    MrvlIEtypesHeader_t Header;
    u8 QueueIndex;
    u8 Disabled;
    u8 Reserved1;
    u8 Reserved2;
    u8 FlowRequired;
    u8 FlowCreated;
    u32 Reserved3;
} __ATTRIB_PACK__ MrvlIEtypes_WmmQueueStatus_t;

/** Table of TSF values returned in the scan result */
typedef struct
{
    MrvlIEtypesHeader_t Header;
    u64 tsfTable[1];
} __ATTRIB_PACK__ MrvlIEtypes_TsfTimestamp_t;

/**  Local Power Capability */
typedef struct _MrvlIEtypes_PowerCapability_t
{
    MrvlIEtypesHeader_t Header;
    s8 MinPower;
    s8 MaxPower;
} __ATTRIB_PACK__ MrvlIEtypes_PowerCapability_t;

/** MrvlIEtypes_RssiParamSet_t */
typedef struct _MrvlIEtypes_RssiThreshold_t
{
    MrvlIEtypesHeader_t Header;
    u8 RSSIValue;
    u8 RSSIFreq;
} __ATTRIB_PACK__ MrvlIEtypes_RssiParamSet_t;

/** MrvlIEtypes_SnrThreshold_t */
typedef struct _MrvlIEtypes_SnrThreshold_t
{
    MrvlIEtypesHeader_t Header;
    u8 SNRValue;
    u8 SNRFreq;
} __ATTRIB_PACK__ MrvlIEtypes_SnrThreshold_t;

/** MrvlIEtypes_FailureCount_t */
typedef struct _MrvlIEtypes_FailureCount_t
{
    MrvlIEtypesHeader_t Header;
    u8 FailValue;
    u8 FailFreq;
} __ATTRIB_PACK__ MrvlIEtypes_FailureCount_t;

/** MrvlIEtypes_BeaconsMissed_t */
typedef struct _MrvlIEtypes_BeaconsMissed_t
{
    MrvlIEtypesHeader_t Header;
    u8 BeaconMissed;
    u8 Reserved;
} __ATTRIB_PACK__ MrvlIEtypes_BeaconsMissed_t;

/** MrvlIEtypes_NumProbes_t */
typedef struct _MrvlIEtypes_NumProbes_t
{
    MrvlIEtypesHeader_t Header;
    u16 NumProbes;
} __ATTRIB_PACK__ MrvlIEtypes_NumProbes_t;

/** MrvlIEtypes_StartBGScanLater_t */
typedef struct _MrvlIEtypes_StartBGScanLater_t
{
    MrvlIEtypesHeader_t Header;
    u16 StartLater;
} __ATTRIB_PACK__ MrvlIEtypes_StartBGScanLater_t;

typedef struct _LedGpio_t
{
    u8 LedNum;                  /* LED # mapped to GPIO pin # below */
    u8 GpioNum;                 /* GPIO pin # used to control LED # above */
} __ATTRIB_PACK__ LedGpio_t;

/** MrvlIEtypes_LedGpio_t */
typedef struct _MrvlIEtypes_LedGpio_t
{
    MrvlIEtypesHeader_t Header;
    LedGpio_t LedGpio[1];
} __ATTRIB_PACK__ MrvlIEtypes_LedGpio_t;

/** MrvlIEtypes_LedBehavior_t */
typedef struct _MrvlIEtypes_LedBehavior_t
{
    MrvlIEtypesHeader_t Header;
    u8 FirmwareState;           /* Firmware State */
    u8 LedNum;                  /* LED # */
    u8 LedState;                /* LED State corresponding to Firmware State */
    u8 LedArgs;                 /* Arguments for LED State */
} __ATTRIB_PACK__ MrvlIEtypes_LedBehavior_t;

typedef struct _PA_Group_t
{
    u16 PowerAdaptLevel;
    u16 RateBitmap;
    u32 Reserved;
} __ATTRIB_PACK__ PA_Group_t;

/** MrvlIEtypes_PA_Group_t */
typedef struct _MrvlIEtypes_PowerAdapt_Group_t
{
    MrvlIEtypesHeader_t Header;
    PA_Group_t PA_Group[MAX_POWER_ADAPT_GROUP];
} __ATTRIB_PACK__ MrvlIEtypes_PowerAdapt_Group_t;

typedef struct _AutoTx_MacFrame_t
{
    u16 Interval;               /* in seconds */
    u8 Priority;                /* User Priority: 0~7, ignored if non-WMM */
    u8 Reserved;                /* set to 0 */
    u16 FrameLen;               /* Length of MAC frame payload */
    u8 DestMacAddr[ETH_ALEN];
    u8 SrcMacAddr[ETH_ALEN];
    u8 Payload[4];			    //changed by dennis
} __ATTRIB_PACK__ AutoTx_MacFrame_t;

/** MrvlIEtypes_AutoTx_t */
typedef struct _MrvlIEtypes_AutoTx_t
{
    MrvlIEtypesHeader_t Header;
    AutoTx_MacFrame_t AutoTx_MacFrame;
} __ATTRIB_PACK__ MrvlIEtypes_AutoTx_t;

typedef struct
{
    u8 value;
    u8 Freq;
} Threshold;

typedef struct
{
    u16 EventsBitmap;           /* bit 0: RSSI low,  bit 1: SNR low,
                                 * bit 2: RSSI high, bit 3: SNR high
                                 */
    Threshold Rssi_low;
    Threshold Snr_low;
    Threshold Rssi_high;
    Threshold Snr_high;
} wlan_subscribe_event;

/** Auth type to be used in the Authentication portion of an Assoc seq */
typedef struct
{
    MrvlIEtypesHeader_t Header;
    u16 AuthType;
} __ATTRIB_PACK__ MrvlIEtypes_AuthType_t;

#define MRVDRV_MAX_SUBBAND_802_11D		83
#define COUNTRY_CODE_LEN			3

/** Data structure for Country IE*/
typedef struct _IEEEtypes_SubbandSet
{
    u8 FirstChan;
    u8 NoOfChan;
    u8 MaxTxPwr;
} __ATTRIB_PACK__ IEEEtypes_SubbandSet_t;

typedef struct _IEEEtypes_CountryInfoSet
{
    u8 ElementId;
    u8 Len;
    u8 CountryCode[COUNTRY_CODE_LEN];
    IEEEtypes_SubbandSet_t Subband[1];
} __ATTRIB_PACK__ IEEEtypes_CountryInfoSet_t;

typedef struct _IEEEtypes_CountryInfoFullSet
{
    u8 ElementId;
    u8 Len;
    u8 CountryCode[COUNTRY_CODE_LEN];
    IEEEtypes_SubbandSet_t Subband[MRVDRV_MAX_SUBBAND_802_11D];
} __ATTRIB_PACK__ IEEEtypes_CountryInfoFullSet_t;

typedef struct _MrvlIEtypes_DomainParamSet
{
    MrvlIEtypesHeader_t Header;
    u8 CountryCode[COUNTRY_CODE_LEN];
    IEEEtypes_SubbandSet_t Subband[1];
} __ATTRIB_PACK__ MrvlIEtypes_DomainParamSet_t;

/** Size of a TSPEC.  Used to allocate necessary buffer space in commands */
#define WMM_TSPEC_SIZE              63

/** Extra IE bytes allocated in messages for appended IEs after a TSPEC */
#define WMM_ADDTS_EXTRA_IE_BYTES    256

/** Extra TLV bytes allocated in messages for configuring WMM Queues */
#define WMM_QUEUE_CONFIG_EXTRA_TLV_BYTES 64
/** Maximum number of AC QOS queues available in the driver/firmware */
#define MAX_AC_QUEUES 4

/** enum of WMM AC_QUEUES */
typedef enum
{
    WMM_AC_BK,
    WMM_AC_BE,
    WMM_AC_VI,
    WMM_AC_VO,
} __ATTRIB_PACK__ wlan_wmm_ac_e;

/** data structure of WMM QoS information */
typedef struct
{
    u8 ParaSetCount:4;
    u8 Reserved:3;
    u8 QosUAPSD:1;
} __ATTRIB_PACK__ IEEEtypes_WmmQosInfo_t;

typedef struct
{
    u8 Aifsn:4;
    u8 Acm:1;
    u8 Aci:2;
    u8 Reserved:1;
} __ATTRIB_PACK__ IEEEtypes_WmmAciAifsn_t;

/**  data structure of WMM ECW */
typedef struct
{
    u8 EcwMin:4;
    u8 EcwMax:4;
} __ATTRIB_PACK__ IEEEtypes_WmmEcw_t;

/** data structure of WMM AC parameters  */
typedef struct
{
    IEEEtypes_WmmAciAifsn_t AciAifsn;
    IEEEtypes_WmmEcw_t Ecw;
    u16 TxopLimit;
} __ATTRIB_PACK__ IEEEtypes_WmmAcParameters_t;

/** data structure of WMM Info IE  */
typedef struct
{

    /**
     * WMM Info IE - Vendor Specific Header:
     *   ElementId   [221/0xdd]
     *   Len         [7] 
     *   Oui         [00:50:f2]
     *   OuiType     [2]
     *   OuiSubType  [0]
     *   Version     [1]
     */
    IEEEtypes_VendorHeader_t VendHdr;

    IEEEtypes_WmmQosInfo_t QoSInfo;

} __ATTRIB_PACK__ IEEEtypes_WmmInfo_t;

/** data structure of WMM parameter IE  */
typedef struct
{
    /**
     * WMM Parameter IE - Vendor Specific Header:
     *   ElementId   [221/0xdd]
     *   Len         [24] 
     *   Oui         [00:50:f2]
     *   OuiType     [2]
     *   OuiSubType  [1]
     *   Version     [1]
     */
    IEEEtypes_VendorHeader_t VendHdr;

    IEEEtypes_WmmQosInfo_t QoSInfo;
    u8 Reserved;

    /** AC Parameters Record WMM_AC_BE, WMM_AC_BK, WMM_AC_VI, WMM_AC_VO */
    IEEEtypes_WmmAcParameters_t AcParams[MAX_AC_QUEUES];

} __ATTRIB_PACK__ IEEEtypes_WmmParameter_t;

/**
 *  @brief Firmware command structure to retrieve the firmware WMM status.
 *
 *  Used to retrieve the status of each WMM AC Queue in TLV 
 *    format (MrvlIEtypes_WmmQueueStatus_t) as well as the current WMM
 *    parameter IE advertised by the AP.  
 *  
 *  Used in response to a MACREG_INT_CODE_WMM_STATUS_CHANGE event signalling
 *    a QOS change on one of the ACs or a change in the WMM Parameter in
 *    the Beacon.
 *
 *  TLV based command, byte arrays used for max sizing purpose. There are no 
 *    arguments sent in the command, the TLVs are returned by the firmware.
 */
typedef struct
{
    u8 queueStatusTlv[sizeof(MrvlIEtypes_WmmQueueStatus_t) * MAX_AC_QUEUES];
    u8 wmmParamTlv[sizeof(IEEEtypes_WmmParameter_t) + 2];

}
__ATTRIB_PACK__ HostCmd_DS_WMM_GET_STATUS;

/**
 *  @brief Enumeration for the command result from an ADDTS or DELTS command 
 */
typedef enum
{
    TSPEC_RESULT_SUCCESS = 0,
    TSPEC_RESULT_EXEC_FAILURE = 1,
    TSPEC_RESULT_TIMEOUT = 2,
    TSPEC_RESULT_DATA_INVALID = 3,

} __ATTRIB_PACK__ wlan_wmm_tspec_result_e;

/**
 *  @brief IOCTL structure to send an ADDTS request and retrieve the response.
 *
 *  IOCTL structure from the application layer relayed to firmware to 
 *    instigate an ADDTS management frame with an appropriate TSPEC IE as well
 *    as any additional IEs appended in the ADDTS Action frame.
 *
 *  @sa wlan_wmm_addts_req_ioctl
 */
typedef struct
{
    wlan_wmm_tspec_result_e commandResult;
    u32 timeout_ms;

    u8 ieeeStatusCode;

    u8 tspecData[WMM_TSPEC_SIZE];

    u8 addtsExtraIEBuf[WMM_ADDTS_EXTRA_IE_BYTES];

} __ATTRIB_PACK__ wlan_ioctl_wmm_addts_req_t;

/**
 *  @brief IOCTL structure to send a DELTS request.
 *
 *  IOCTL structure from the application layer relayed to firmware to 
 *    instigate an DELTS management frame with an appropriate TSPEC IE.
 *
 *  @sa wlan_wmm_delts_req_ioctl
 */
typedef struct
{
    wlan_wmm_tspec_result_e commandResult;      //!< Firmware execution result

    u8 ieeeReasonCode;          //!< IEEE reason code sent, unused for WMM 

    u8 tspecData[WMM_TSPEC_SIZE];       //!< TSPEC to send in the DELTS

} __ATTRIB_PACK__ wlan_ioctl_wmm_delts_req_t;

/**
 *  @brief Internal command structure used in executing an ADDTS command.
 *
 *  Relay information between the IOCTL layer and the firmware command and 
 *    command response procedures.
 *
 *  @sa wlan_wmm_addts_req_ioctl
 *  @sa wlan_cmd_wmm_addts_req
 *  @sa wlan_cmdresp_wmm_addts_req
 */
typedef struct
{
    wlan_wmm_tspec_result_e commandResult;
    u32 timeout_ms;

    u8 dialogToken;
    u8 ieeeStatusCode;

    int tspecDataLen;
    u8 tspecData[WMM_TSPEC_SIZE];
    u8 addtsExtraIEBuf[WMM_ADDTS_EXTRA_IE_BYTES];

} wlan_cmd_wmm_addts_req_t;

/**
 *  @brief Internal command structure used in executing an DELTS command.
 *
 *  Relay information between the IOCTL layer and the firmware command and 
 *    command response procedures.
 *
 *  @sa wlan_wmm_delts_req_ioctl
 *  @sa wlan_cmd_wmm_delts_req
 *  @sa wlan_cmdresp_wmm_delts_req
 */
typedef struct
{
    wlan_wmm_tspec_result_e commandResult;

    u8 dialogToken;

    u8 ieeeReasonCode;

    int tspecDataLen;
    u8 tspecData[WMM_TSPEC_SIZE];

} wlan_cmd_wmm_delts_req_t;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_ADDTS_REQ firmware command
 *
 */
typedef struct
{
    wlan_wmm_tspec_result_e commandResult;
    u32 timeout_ms;

    u8 dialogToken;
    u8 ieeeStatusCode;
    u8 tspecData[WMM_TSPEC_SIZE];
    u8 addtsExtraIEBuf[WMM_ADDTS_EXTRA_IE_BYTES];

} __ATTRIB_PACK__ HostCmd_DS_WMM_ADDTS_REQ;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_DELTS_REQ firmware command
 */
typedef struct
{
    wlan_wmm_tspec_result_e commandResult;
    u8 dialogToken;
    u8 ieeeReasonCode;
    u8 tspecData[WMM_TSPEC_SIZE];

} __ATTRIB_PACK__ HostCmd_DS_WMM_DELTS_REQ;

/**
 *  @brief Enumeration for the action field in the Queue configure command
 */
typedef enum
{
    WMM_QUEUE_CONFIG_ACTION_GET = 0,
    WMM_QUEUE_CONFIG_ACTION_SET = 1,
    WMM_QUEUE_CONFIG_ACTION_DEFAULT = 2,

    WMM_QUEUE_CONFIG_ACTION_MAX
} __ATTRIB_PACK__ wlan_wmm_queue_config_action_e;

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_QUEUE_CONFIG firmware cmd
 *
 *  Set/Get/Default the Queue parameters for a specific AC in the firmware.
 *
 */
typedef struct
{
    wlan_wmm_queue_config_action_e action;      //!< Set, Get, or Default
    wlan_wmm_ac_e accessCategory;       //!< WMM_AC_BK(0) to WMM_AC_VO(3)

    /** @brief MSDU lifetime expiry per 802.11e
     *
     *   - Ignored if 0 on a set command 
     *   - Set to the 802.11e specified 500 TUs when defaulted
     */
    u16 msduLifetimeExpiry;

    u8 tlvBuffer[WMM_QUEUE_CONFIG_EXTRA_TLV_BYTES];     //!< Not supported yet

} __ATTRIB_PACK__ HostCmd_DS_WMM_QUEUE_CONFIG;

/**
 *  @brief Internal command structure used in executing a queue config command.
 *
 *  Relay information between the IOCTL layer and the firmware command and 
 *    command response procedures.
 *
 *  @sa wlan_wmm_queue_config_ioctl
 *  @sa wlan_cmd_wmm_queue_config
 *  @sa wlan_cmdresp_wmm_queue_config
 */
typedef struct
{
    wlan_wmm_queue_config_action_e action;      //!< Set, Get, or Default
    wlan_wmm_ac_e accessCategory;       //!< WMM_AC_BK(0) to WMM_AC_VO(3)
    u16 msduLifetimeExpiry;     //!< lifetime expiry in TUs

    int tlvBufLen;              //!< Not supported yet
    u8 tlvBuffer[WMM_QUEUE_CONFIG_EXTRA_TLV_BYTES];     //!< Not supported yet

} wlan_cmd_wmm_queue_config_t;

/**
 *  @brief IOCTL structure to configure a specific AC Queue's parameters
 *
 *  IOCTL structure from the application layer relayed to firmware to 
 *    get, set, or default the WMM AC queue parameters.
 *
 *  - msduLifetimeExpiry is ignored if set to 0 on a set command
 *
 *  @sa wlan_wmm_queue_config_ioctl
 */
typedef struct
{
    wlan_wmm_queue_config_action_e action;      //!< Set, Get, or Default
    wlan_wmm_ac_e accessCategory;       //!< WMM_AC_BK(0) to WMM_AC_VO(3)
    u16 msduLifetimeExpiry;     //!< lifetime expiry in TUs

    u8 supportedRates[10];      //!< Not supported yet

} __ATTRIB_PACK__ wlan_ioctl_wmm_queue_config_t;

/**
 *   @brief Enumeration for the action field in the queue stats command
 */
typedef enum
{
    WMM_STATS_ACTION_START = 0,
    WMM_STATS_ACTION_STOP = 1,
    WMM_STATS_ACTION_GET_CLR = 2,
    WMM_STATS_ACTION_SET_CFG = 3,       /* Not currently used */
    WMM_STATS_ACTION_GET_CFG = 4,       /* Not currently used */

    WMM_STATS_ACTION_MAX
} __ATTRIB_PACK__ wlan_wmm_stats_action_e;

/** Number of bins in the histogram for the HostCmd_DS_WMM_QUEUE_STATS */
#define WMM_STATS_PKTS_HIST_BINS  7

/**
 *  @brief Command structure for the HostCmd_CMD_WMM_QUEUE_STATS firmware cmd
 *
 *  Turn statistical collection on/off for a given AC or retrieve the 
 *    accumulated stats for an AC and clear them in the firmware.
 */
typedef struct
{
    wlan_wmm_stats_action_e action;     //!< Start, Stop, or Get 
    wlan_wmm_ac_e accessCategory;       //!< WMM_AC_BK(0) to WMM_AC_VO(3)

    u16 pktCount;               //!< Number of successful packets transmitted
    u16 pktLoss;                //!< Packets lost; not included in pktCount
    u32 avgQueueDelay;          //!< Average Queue delay in microseconds
    u32 avgTxDelay;             //!< Average Transmission delay in microseconds
    u32 usedTime;               //!< Calculated medium time - Not currently used

    /** @brief Queue Delay Histogram; number of packets per queue delay range
     * 
     *  [0] -  0ms <= delay < 5ms
     *  [1] -  5ms <= delay < 10ms
     *  [2] - 10ms <= delay < 20ms
     *  [3] - 20ms <= delay < 30ms
     *  [4] - 30ms <= delay < 40ms
     *  [5] - 40ms <= delay < 50ms
     *  [6] - 50ms <= delay < msduLifetime (TUs)
     */
    u16 delayHistogram[WMM_STATS_PKTS_HIST_BINS];

    u16 reserved_u16_1;

} __ATTRIB_PACK__ HostCmd_DS_WMM_QUEUE_STATS;

/**
 *  @brief IOCTL structure to start, stop, and get statistics for a WMM AC
 *
 *  IOCTL structure from the application layer relayed to firmware to 
 *    start or stop statistical collection for a given AC.  Also used to 
 *    retrieve and clear the collected stats on a given AC.
 *
 *  @sa wlan_wmm_queue_stats_ioctl
 */
typedef struct
{
    wlan_wmm_stats_action_e action;     //!< Start, Stop, or Get 
    wlan_wmm_ac_e accessCategory;       //!< WMM_AC_BK(0) to WMM_AC_VO(3)
    u16 pktCount;               //!< Number of successful packets transmitted  
    u16 pktLoss;                //!< Packets lost; not included in pktCount    
    u32 avgQueueDelay;          //!< Average Queue delay in microseconds
    u32 avgTxDelay;             //!< Average Transmission delay in microseconds
    u32 usedTime;               //!< Calculated medium time 

    /** @brief Queue Delay Histogram; number of packets per queue delay range
     * 
     *  [0] -  0ms <= delay < 5ms
     *  [1] -  5ms <= delay < 10ms
     *  [2] - 10ms <= delay < 20ms
     *  [3] - 20ms <= delay < 30ms
     *  [4] - 30ms <= delay < 40ms
     *  [5] - 40ms <= delay < 50ms
     *  [6] - 50ms <= delay < msduLifetime (TUs)
     */
    u16 delayHistogram[WMM_STATS_PKTS_HIST_BINS];
} __ATTRIB_PACK__ wlan_ioctl_wmm_queue_stats_t;

/** 
 *  @brief IOCTL sub structure for a specific WMM AC Status
 */
typedef struct
{
    u8 wmmAcm;
    u8 flowRequired;
    u8 flowCreated;
    u8 disabled;
} __ATTRIB_PACK__ wlan_ioctl_wmm_queue_status_ac_t;

/**
 *  @brief IOCTL structure to retrieve the WMM AC Queue status
 *
 *  IOCTL structure from the application layer to retrieve:
 *     - ACM bit setting for the AC
 *     - Firmware status (flow required, flow created, flow disabled)
 *
 *  @sa wlan_wmm_queue_status_ioctl
 */
typedef struct
{
    wlan_ioctl_wmm_queue_status_ac_t acStatus[MAX_AC_QUEUES];
} __ATTRIB_PACK__ wlan_ioctl_wmm_queue_status_t;

/** Firmware status for a specific AC */
typedef struct
{
    u8 Disabled;
    u8 FlowRequired;
    u8 FlowCreated;
} WmmAcStatus_t;

#endif /* _WLAN_TYPES_ */
