/** @file wlan_dev.h
 *  @brief This file contains definitions and data structures specific
 *          to Marvell 802.11 NIC. It contains the Device Information
 *          structure wlan_adapter.  
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
 */
/*************************************************************
Change log:
	09/26/05: add Doxygen format comments 
	01/11/06: Conditionalize new scan/join structures.
	04/18/06: Remove old Subscrive Event and add new Subscribe Event
		  implementation through generic hostcmd API
	05/08/06: Remove PermanentAddr from Adapter

 ************************************************************/

#ifndef _WLAN_DEV_H_
#define _WLAN_DEV_H_
#include "include.h"
#include "wlan_thread.h"
#include "wlan_types.h"
#include "wlan_defs.h"
#include "rt_wlan_dev.h"
#include "..\os\os_timers.h"
#include "hostcmd.h"
#include <netif/ethernetif.h>
#define	MAX_BSSID_PER_CHANNEL		16

/* For the extended Scan */
#define MAX_EXTENDED_SCAN_BSSID_LIST    MAX_BSSID_PER_CHANNEL (MRVDRV_MAX_CHANNEL_SIZE + 1)
struct net_device_stats			  //this struct copied form LInux
{
	unsigned long	rx_packets;		/* total packets received	*/
	unsigned long	tx_packets;		/* total packets transmitted	*/
	unsigned long	rx_bytes;		/* total bytes received 	*/
	unsigned long	tx_bytes;		/* total bytes transmitted	*/
	unsigned long	rx_errors;		/* bad packets received		*/
	unsigned long	tx_errors;		/* packet transmit problems	*/
	unsigned long	rx_dropped;		/* no space in linux buffers	*/
	unsigned long	tx_dropped;		/* no space available in linux	*/
	unsigned long	multicast;		/* multicast packets received	*/
	unsigned long	collisions;

	/* detailed rx_errors: */
	unsigned long	rx_length_errors;
	unsigned long	rx_over_errors;		/* receiver ring buff overflow	*/
	unsigned long	rx_crc_errors;		/* recved pkt with crc error	*/
	unsigned long	rx_frame_errors;	/* recv'd frame alignment error */
	unsigned long	rx_fifo_errors;		/* recv'r fifo overrun		*/
	unsigned long	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	unsigned long	tx_aborted_errors;
	unsigned long	tx_carrier_errors;
	unsigned long	tx_fifo_errors;
	unsigned long	tx_heartbeat_errors;
	unsigned long	tx_window_errors;
	
	/* for cslip etc */
	unsigned long	rx_compressed;
	unsigned long	tx_compressed;
};
typedef struct _PER_CHANNEL_BSSID_LIST_DATA
{
    u8 ucStart;
    u8 ucNumEntry;
} PER_CHANNEL_BSSID_LIST_DATA, *PPER_CHANNEL_BSSID_LIST_DATA;

typedef struct _MRV_BSSID_IE_LIST
{
    WLAN_802_11_FIXED_IEs FixedIE;
    u8 VariableIE[MRVDRV_SCAN_LIST_VAR_IE_SPACE];
} MRV_BSSID_IE_LIST, *PMRV_BSSID_IE_LIST;

#define	MAX_REGION_CHANNEL_NUM	2

/** Chan-Freq-TxPower mapping table*/
typedef struct _CHANNEL_FREQ_POWER
{
        /** Channel Number		*/
    u16 Channel;
        /** Frequency of this Channel	*/
    u32 Freq;
        /** Max allowed Tx power level	*/
    u16 MaxTxPower;
        /** TRUE:channel unsupported;  FLASE:supported*/
    BOOLEAN Unsupported;
} CHANNEL_FREQ_POWER;

/** region-band mapping table*/
typedef struct _REGION_CHANNEL
{
        /** TRUE if this entry is valid		     */
    BOOLEAN Valid;
        /** Region code for US, Japan ...	     */
    u8 Region;
        /** Band B/G/A, used for BAND_CONFIG cmd	     */
    u8 Band;
        /** Actual No. of elements in the array below */
    u8 NrCFP;
        /** chan-freq-txpower mapping table*/
    CHANNEL_FREQ_POWER *CFP;
} REGION_CHANNEL;

typedef struct _wlan_802_11_security_t
{
    BOOLEAN WPAEnabled;
    BOOLEAN WPA2Enabled;
    WLAN_802_11_WEP_STATUS WEPStatus;
    WLAN_802_11_AUTHENTICATION_MODE AuthenticationMode;
    WLAN_802_11_ENCRYPTION_MODE EncryptionMode;
} wlan_802_11_security_t;

/** Current Basic Service Set State Structure */
typedef struct
{
    BSSDescriptor_t BSSDescriptor;

        /** band */
    u8 band;

        /** number of rates supported */
    int NumOfRates;

        /** supported rates*/
    u8 DataRates[WLAN_SUPPORTED_RATES];

        /** wmm enable? */
    u8 wmm_enabled;

        /** uapsd enable?*/
    u8 wmm_uapsd_enabled;
} CurrentBSSParams_t;

/** sleep_params */
typedef struct SleepParams
{
    u16 sp_error;
    u16 sp_offset;
    u16 sp_stabletime;
    u8 sp_calcontrol;
    u8 sp_extsleepclk;
    u16 sp_reserved;
} SleepParams;

/** sleep_period */
typedef struct SleepPeriod
{
    u16 period;
    u16 reserved;
} SleepPeriod;

/** info for debug purpose */
typedef struct _wlan_dbg
{
    u32 num_cmd_host_to_card_failure;
    u32 num_cmd_sleep_cfm_host_to_card_failure;
    u32 num_tx_host_to_card_failure;
    u32 num_event_deauth;
    u32 num_event_disassoc;
    u32 num_event_link_lost;
    u32 num_cmd_deauth;
    u32 num_cmd_assoc_success;
    u32 num_cmd_assoc_failure;
    u32 num_tx_timeout;
    u32 num_cmd_timeout;
    u16 TimeoutCmdId;
    u16 TimeoutCmdAct;
    u16 LastCmdId;
    u16 LastCmdRespId;
} wlan_dbg;

/** Data structure for the Marvell WLAN device */
typedef struct _wlan_dev
{
        /** device name */
    char name[DEV_NAME_LEN];
        /** card pointer */
 
        /** IO port */
    u32 ioport;
        /** Upload received */
    u32 upld_rcv;
        /** Upload type */
    u32 upld_typ;
        /** Upload length */
    u32 upld_len;
        /** netdev pointer */
   // struct net_device *netdev;
	struct rt_wlan_dev	 *netdev;
    /* Upload buffer */
    u8 upld_buf[WLAN_UPLD_SIZE];
    /* Download sent: 
       bit0 1/0=data_sent/data_tx_done, 
       bit1 1/0=cmd_sent/cmd_tx_done, 
       all other bits reserved 0 */
    u8 dnld_sent;
} wlan_dev_t, *pwlan_dev_t;

/* Data structure for WPS information */
typedef struct
{
    IEEEtypes_VendorSpecific_t wpsIe;
    BOOLEAN SessionEnable;
} wps_t;

/** Private structure for the MV device */
struct _wlan_private
{
    int open;

    wlan_adapter *adapter;
    wlan_dev_t wlan_dev;

    struct net_device_stats stats;

        /** thread to service interrupts */
    wlan_thread MainThread;

#ifdef REASSOCIATION
        /** thread to service mac events */
    wlan_thread ReassocThread;
#endif                          /* REASSOCIATION */
};

/** Wlan Adapter data structure*/
struct _wlan_adapter
{
    u8 TmpTxBuf[WLAN_UPLD_SIZE] ;
        /** STATUS variables */
    WLAN_HARDWARE_STATUS HardwareStatus;
    u32 FWReleaseNumber;
    u32 fwCapInfo;
    u8 chip_rev;

        /** Command-related variables */
    u16 SeqNum;
    CmdCtrlNode *CmdArray;
        /** Current Command */
    CmdCtrlNode *CurCmd;
    int CurCmdRetCode;

        /** Command Queues */
        /** Free command buffers */
    struct list_head CmdFreeQ;
        /** Pending command buffers */
    struct list_head CmdPendingQ;

        /** Variables brought in from private structure */
    int irq;

        /** Async and Sync Event variables */
    u32 IntCounter;
    u32 IntCounterSaved;        /* save int for DS/PS */
    u32 EventCause;
    u8 nodeName[16];            /* nickname */

        /** spin locks */
   // spinlock_t QueueSpinLock __ATTRIB_ALIGN__;
//	int QueueSpinLock ;//__ATTRIB_ALIGN__;
        /** Timers */
    WLAN_DRV_TIMER MrvDrvCommandTimer ;// __ATTRIB_ALIGN__;
    BOOLEAN CommandTimerIsSet;

#ifdef REASSOCIATION
        /**Reassociation timer*/
    BOOLEAN ReassocTimerIsSet;
    WLAN_DRV_TIMER MrvDrvTimer;// __ATTRIB_ALIGN__;
#endif                          /* REASSOCIATION */

        /** Event Queues */
    struct rt_event ds_awake_q;// __ATTRIB_ALIGN__;

    u8 HisRegCpy;

    /** bg scan related variable */
    HostCmd_DS_802_11_BG_SCAN_CONFIG *bgScanConfig;
    u32 bgScanConfigSize;

    /** WMM related variable*/
    WMM_DESC wmm;

        /** current ssid/bssid related parameters*/
    CurrentBSSParams_t CurBssParams;

    WLAN_802_11_NETWORK_INFRASTRUCTURE InfrastructureMode;

    BSSDescriptor_t *pAttemptedBSSDesc;

    WLAN_802_11_SSID AttemptedSSIDBeforeScan;
    WLAN_802_11_SSID PreviousSSID;
    u8 PreviousBSSID[MRVDRV_ETH_ADDR_LEN];

    BSSDescriptor_t *ScanTable;
    u32 NumInScanTable;

    u8 ScanType;
    u32 ScanMode;
    u16 SpecificScanTime;
    u16 ActiveScanTime;
    u16 PassiveScanTime;

    u16 BeaconPeriod;
    u8 AdhocCreate;
    BOOLEAN AdhocLinkSensed;

#ifdef REASSOCIATION
        /** Reassociation on and off */
    BOOLEAN Reassoc_on;
    SEMAPHORE ReassocSem;
#endif                          /* REASSOCIATION */

    BOOLEAN ATIMEnabled;

        /** MAC address information */
    u8 CurrentAddr[MRVDRV_ETH_ADDR_LEN];
    u8 MulticastList[MRVDRV_MAX_MULTICAST_LIST_SIZE]
        [MRVDRV_ETH_ADDR_LEN];
    u32 NumOfMulticastMACAddr;

    u16 HWRateDropMode;
    u16 RateBitmap;
    u16 Threshold;
    u16 FinalRate;
        /** control G Rates */
    BOOLEAN adhoc_grate_enabled;

    WLAN_802_11_ANTENNA TxAntenna;
    WLAN_802_11_ANTENNA RxAntenna;

    u8 AdhocChannel;
    WLAN_802_11_FRAGMENTATION_THRESHOLD FragThsd;
    WLAN_802_11_RTS_THRESHOLD RTSThsd;

    u32 DataRate;
    BOOLEAN Is_DataRate_Auto;

        /** number of association attempts for the current SSID cmd */
    u16 ListenInterval;
    u8 TxRetryCount;

        /** Tx-related variables (for single packet tx) */
    struct sk_buff *CurrentTxSkb;
    struct sk_buff RxSkbQ;
    BOOLEAN TxLockFlag;
    u16 gen_null_pkg;
   // spinlock_t CurrentTxLock __ATTRIB_ALIGN__;
//	int CurrentTxLock ; //temporarily
        /** NIC Operation characteristics */
    u16 CurrentPacketFilter;
    u32 MediaConnectStatus;
    u16 RegionCode;
    u16 TxPowerLevel;
    u8 MaxTxPowerLevel;
    u8 MinTxPowerLevel;

        /** POWER MANAGEMENT AND PnP SUPPORT */
    BOOLEAN SurpriseRemoved;
    u16 AtimWindow;

    u16 PSMode;                 /* Wlan802_11PowerModeCAM=disable
                                   Wlan802_11PowerModeMAX_PSP=enable */
    u16 MultipleDtim;
    u16 BCNMissTimeOut;
    u32 PSState;
    BOOLEAN NeedToWakeup;

    PS_CMD_ConfirmSleep PSConfirmSleep;
    u16 LocalListenInterval;
    u16 NullPktInterval;
    u16 AdhocAwakePeriod;
    u16 fwWakeupMethod;
    BOOLEAN IsDeepSleep;
    BOOLEAN bWakeupDevRequired;
    u32 WakeupTries;
    BOOLEAN bHostSleepConfigured;
    HostCmd_DS_802_11_HOST_SLEEP_CFG HSCfg;
        /** ARP filter related variable */
    u8 ArpFilter[ARP_FILTER_MAX_BUF_SIZE];
    u32 ArpFilterSize;

        /** Encryption parameter */
    wlan_802_11_security_t SecInfo;

    MRVL_WEP_KEY WepKey[MRVL_NUM_WEP_KEY];
    u16 CurrentWepKeyIndex;

    /** Buffer for TLVs passed from the application to be inserted into the
     *    association request to firmware 
     */
    u8 mrvlAssocTlvBuffer[MRVDRV_ASSOC_TLV_BUF_SIZE];

    /** Length of the data stored in mrvlAssocTlvBuffer*/
    u8 mrvlAssocTlvBufferLen;

    /** Buffer to store the association response for application retrieval */
    u8 assocRspBuffer[MRVDRV_ASSOC_RSP_BUF_SIZE];

    /** Length of the data stored in assocRspBuffer */
    int assocRspSize;

    /** Generice IEEE IEs passed from the application to be inserted into the
     *    association request to firmware 
     */
    u8 genIeBuffer[MRVDRV_GENIE_BUF_SIZE];

    /** Length of the data stored in genIeBuffer */
    u8 genIeBufferLen;

    BOOLEAN IsGTK_SET;

        /** Encryption Key*/
    u8 Wpa_ie[256];
    u8 Wpa_ie_len;

    HostCmd_DS_802_11_KEY_MATERIAL aeskey;

    /* Advanced Encryption Standard */
    BOOLEAN AdhocAESEnabled;
    struct rt_event cmd_EncKey;

    u16 RxAntennaMode;
    u16 TxAntennaMode;

        /** Requested Signal Strength*/
    u16 bcn_avg_factor;
    u16 data_avg_factor;
    u16 SNR[MAX_TYPE_B][MAX_TYPE_AVG];
    u16 NF[MAX_TYPE_B][MAX_TYPE_AVG];
    u8 RSSI[MAX_TYPE_B][MAX_TYPE_AVG];
    u8 rawSNR[DEFAULT_DATA_AVG_FACTOR];
    u8 rawNF[DEFAULT_DATA_AVG_FACTOR];
    u16 nextSNRNF;
    u16 numSNRNF;
    u32 RxPDAge;
    u16 RxPDRate;

    BOOLEAN RadioOn;

        /** Blue Tooth Co-existence Arbitration */
    HostCmd_DS_802_11_BCA_TIMESHARE bca_ts;

        /** sleep_params */
    SleepParams sp;

        /** sleep_period (Enhanced Power Save) */
    SleepPeriod sleep_period;

#define	MAX_REGION_CHANNEL_NUM	2
        /** Region Channel data */
    REGION_CHANNEL region_channel[MAX_REGION_CHANNEL_NUM];

    REGION_CHANNEL universal_channel[MAX_REGION_CHANNEL_NUM];

        /** 11D and Domain Regulatory Data */
    wlan_802_11d_domain_reg_t DomainReg;
    parsed_region_chan_11d_t parsed_region_chan;

        /** FSM variable for 11d support */
    wlan_802_11d_state_t State11D;
    u8 beaconBuffer[MAX_SCAN_BEACON_BUFFER];
    u8 *pBeaconBufEnd;

    HostCmd_DS_802_11_GET_LOG LogMsg;
    u16 ScanProbes;

    u32 PktTxCtrl;

    u8 *helper;
    u32 helper_len;
    u8 *fmimage;
    u32 fmimage_len;
    u16 TxRate;

    wps_t wps;

    wlan_dbg dbg;
    wlan_subscribe_event subevent;
    u32 num_cmd_timeout;
};

#endif /* _WLAN_DEV_H_ */
