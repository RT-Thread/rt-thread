/** @file host.h
 * 
 * @brief This file contains definitions of WLAN commands.
 *  
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
 */
/********************************************************
Change log:
    10/11/05: Add Doxygen format comments
    01/11/06: Remove assoc response codes; full IEEE assoc resp now returned
    04/06/06: Add TSPEC, queue metrics, and MSDU expiry support
    04/10/06: Add power_adapt_cfg_ext command
    04/18/06: Remove old Subscrive Event and add new Subscribe Event
              implementation through generic hostcmd API
    05/03/06: Add auto_tx hostcmd
    05/04/06: Add IBSS coalescing related new hostcmd and event
    08/28/06: Add LED_CTRL hostcmd
********************************************************/

#ifndef _HOST_H_
#define _HOST_H_

/** PUBLIC DEFINITIONS */
#define DEFAULT_AD_HOC_CHANNEL       6
#define DEFAULT_AD_HOC_CHANNEL_A    36

/** IEEE 802.11 OIDs */
#define OID_802_11_INFRASTRUCTURE_MODE        0x00008001
#define OID_802_11_FRAGMENTATION_THRESHOLD    0x00008002
#define OID_802_11_RTS_THRESHOLD              0x00008003
#define OID_802_11_ADD_WEP                    0x00008004
#define OID_802_11_REMOVE_WEP                 0x00008005
#define OID_802_11_TX_RETRYCOUNT              0x00008006
#define OID_802_11D_ENABLE                    0x00008007

#define HostCmd_OPTION_WAITFORRSP             0x0002

/** Host Command ID */
#define HostCmd_CMD_GET_HW_SPEC               0x0003
#define HostCmd_CMD_802_11_RESET              0x0005
#define HostCmd_CMD_802_11_SCAN               0x0006
#define HostCmd_CMD_802_11_GET_LOG            0x000b
#define HostCmd_CMD_MAC_MULTICAST_ADR         0x0010
#define HostCmd_CMD_802_11_EEPROM_ACCESS      0x0059
#define HostCmd_CMD_802_11_ASSOCIATE          0x0012
#define HostCmd_CMD_802_11_SET_WEP            0x0013
#define HostCmd_CMD_802_11_SNMP_MIB           0x0016
#define HostCmd_CMD_MAC_REG_ACCESS            0x0019
#define HostCmd_CMD_BBP_REG_ACCESS            0x001a
#define HostCmd_CMD_RF_REG_ACCESS             0x001b
#define HostCmd_CMD_802_11_RADIO_CONTROL      0x001c
#define HostCmd_CMD_802_11_RF_CHANNEL         0x001d
#define HostCmd_CMD_802_11_RF_TX_POWER        0x001e
#define HostCmd_CMD_802_11_RSSI               0x001f
#define HostCmd_CMD_802_11_RF_ANTENNA         0x0020

#define HostCmd_CMD_802_11_PS_MODE	      0x0021

#define HostCmd_CMD_802_11_DEAUTHENTICATE     0x0024
#define HostCmd_CMD_MAC_CONTROL               0x0028
#define HostCmd_CMD_802_11_AD_HOC_START       0x002b
#define HostCmd_CMD_802_11_AD_HOC_JOIN        0x002c

#define HostCmd_CMD_802_11_KEY_MATERIAL       0x005e

#define HostCmd_CMD_802_11_DEEP_SLEEP         0x003e

#define HostCmd_CMD_802_11_AD_HOC_STOP        0x0040

#define HostCmd_CMD_802_11_HOST_SLEEP_CFG     0x0043
#define HostCmd_CMD_802_11_WAKEUP_CONFIRM     0x0044

#define HostCmd_CMD_802_11_MAC_ADDRESS        0x004D
#define HostCmd_CMD_802_11_EEPROM_ACCESS      0x0059

#define HostCmd_CMD_GSPI_BUS_CONFIG           0x005A

#define HostCmd_CMD_802_11_BAND_CONFIG        0x0058

#define HostCmd_CMD_802_11D_DOMAIN_INFO       0x005b

#define HostCmd_CMD_802_11_SLEEP_PARAMS          0x0066

#define HostCmd_CMD_802_11_INACTIVITY_TIMEOUT    0x0067

#define HostCmd_CMD_802_11_SLEEP_PERIOD          0x0068
#define HostCmd_CMD_802_11_BCA_CONFIG_TIMESHARE  0x0069

#define HostCmd_CMD_802_11_BG_SCAN_CONFIG        0x006b
#define HostCmd_CMD_802_11_BG_SCAN_QUERY         0x006c

#define HostCmd_CMD_802_11_CAL_DATA_EXT          0x006d

#define HostCmd_CMD_WMM_ADDTS_REQ                0x006E
#define HostCmd_CMD_WMM_DELTS_REQ                0x006F
#define HostCmd_CMD_WMM_QUEUE_CONFIG             0x0070
#define HostCmd_CMD_WMM_GET_STATUS               0x0071

#define HostCmd_CMD_802_11_TPC_CFG               0x0072

#define HostCmd_CMD_802_11_FW_WAKE_METHOD        0x0074

#define HostCmd_CMD_802_11_LED_CONTROL           0x004e

#define HostCmd_CMD_802_11_SUBSCRIBE_EVENT       0x0075

#define HostCmd_CMD_802_11_RATE_ADAPT_RATESET    0x0076

#define HostCmd_CMD_802_11_CRYPTO                0x0078

#define HostCmd_CMD_802_11_TX_RATE_QUERY	0x007f

#define HostCmd_CMD_802_11_POWER_ADAPT_CFG_EXT	0x007e

#define HostCmd_CMD_GET_TSF                      0x0080

#define HostCmd_CMD_WMM_QUEUE_STATS              0x0081

#define HostCmd_CMD_802_11_AUTO_TX		0x0082
#define HostCmd_CMD_802_11_IBSS_COALESCING_STATUS 0x0083

#define HostCmd_CMD_MEM_ACCESS			0x0086

#ifdef MFG_CMD_SUPPORT
#define HostCmd_CMD_MFG_COMMAND               0x0089
#define HostCmd_RET_MFG_COMMAND               0x8089
#endif

#define HostCmd_CMD_TX_PKT_STATS              0x008d

#define HostCmd_CMD_802_11_LDO_CONFIG         0x0096

#define HostCmd_CMD_VERSION_EXT               0x0097

/* For the IEEE Power Save */
#define HostCmd_SubCmd_Enter_PS               0x0030
#define HostCmd_SubCmd_Exit_PS                0x0031
#define HostCmd_SubCmd_Sleep_Confirmed        0x0034
#define HostCmd_SubCmd_Full_PowerDown         0x0035
#define HostCmd_SubCmd_Full_PowerUp           0x0036

/* Command RET code, MSB is set to 1 */
#define HostCmd_RET_HW_SPEC_INFO              0x8003
#define HostCmd_RET_802_11_RESET              0x8005
#define HostCmd_RET_802_11_SCAN               0x8006
#define HostCmd_RET_802_11_GET_LOG            0x800b
#define HostCmd_RET_MAC_CONTROL               0x8028
#define HostCmd_RET_MAC_MULTICAST_ADR         0x8010
#define HostCmd_RET_802_11_DEAUTHENTICATE     0x8024
#define HostCmd_RET_802_11_ASSOCIATE          0x8012
#define HostCmd_RET_802_11_SET_WEP            0x8013
#define HostCmd_RET_802_3_STAT                0x8015
#define HostCmd_RET_802_11_SNMP_MIB           0x8016
#define HostCmd_RET_MAC_REG_ACCESS            0x8019
#define HostCmd_RET_BBP_REG_ACCESS            0x801a
#define HostCmd_RET_RF_REG_ACCESS             0x801b
#define HostCmd_RET_802_11_RADIO_CONTROL      0x801c
#define HostCmd_RET_802_11_RF_CHANNEL         0x801d
#define HostCmd_RET_802_11_RSSI               0x801f
#define HostCmd_RET_802_11_RF_TX_POWER        0x801e
#define HostCmd_RET_802_11_RF_ANTENNA         0x8020
#define HostCmd_RET_802_11_PS_MODE            0x8021

#define HostCmd_RET_802_11_AD_HOC_START       0x802B
#define HostCmd_RET_802_11_AD_HOC_JOIN        0x802C

#define HostCmd_RET_802_11_KEY_MATERIAL       0x805e

#define HostCmd_ACT_SET                       0x0001
#define HostCmd_ACT_GET                       0x0000

#define HostCmd_RET_802_11_AD_HOC_STOP        0x8040

#define HostCmd_RET_802_11_HOST_SLEEP_CFG     0x8043
#define HostCmd_RET_802_11_WAKEUP_CONFIRM     0x8044

#define HostCmd_RET_802_11_MAC_ADDRESS        0x804D
#define HostCmd_RET_802_11_EEPROM_ACCESS      0x8059

#define HostCmd_RET_CMD_GSPI_BUS_CONFIG       0x805A

#define HostCmd_RET_802_11_BAND_CONFIG        0x8058

#define HostCmd_RET_802_11_SLEEP_PARAMS          0x8066

#define HostCmd_RET_802_11_INACTIVITY_TIMEOUT    0x8067

#define HostCmd_RET_802_11_SLEEP_PERIOD          0x8068
#define HostCmd_RET_802_11_BCA_CONFIG_TIMESHARE  0x8069

#define HostCmd_RET_802_11D_DOMAIN_INFO          0x805B

#define HostCmd_RET_802_11_BG_SCAN_CONFIG    0x806b
#define HostCmd_RET_802_11_BG_SCAN_QUERY     0x806c

#define HostCmd_RET_802_11_CAL_DATA_EXT      0x806d

#define HostCmd_RET_WMM_ADDTS_REQ            0x806E
#define HostCmd_RET_WMM_DELTS_REQ            0x806F
#define HostCmd_RET_WMM_QUEUE_CONFIG         0x8070
#define HostCmd_RET_WMM_GET_STATUS           0x8071

#define HostCmd_RET_802_11_TPC_CFG           0x8072

#define HostCmd_RET_802_11_LED_CONTROL       0x804e

#define HostCmd_RET_802_11_FW_WAKE_METHOD    0x8074

#define HostCmd_RET_802_11_SUBSCRIBE_EVENT   0x8075

#define HostCmd_RET_802_11_RATE_ADAPT_RATESET	0x8076

#define HostCmd_RET_802_11_CRYPTO               0x8078

#define HostCmd_RTE_802_11_TX_RATE_QUERY 	0x807f

#define HostCmd_RET_GET_TSF             	0x8080

#define HostCmd_RET_WMM_QUEUE_STATS     	0x8081

#define HostCmd_RET_802_11_POWER_ADAPT_CFG_EXT	0x807e

#define HostCmd_RET_802_11_AUTO_TX		0x8082
#define HostCmd_RET_802_11_IBSS_COALESCING_STATUS	0x8083

#define HostCmd_RET_MEM_ACCESS		      0x8086

#define HostCmd_RET_802_11_LDO_CONFIG         0x8096

#define HostCmd_RET_VERSION_EXT               0x8097

/** General Result Code*/
/* OK */
#define HostCmd_RESULT_OK                    0x0000
/* Genenral error */
#define HostCmd_RESULT_ERROR                 0x0001
/* Command is not valid */
#define HostCmd_RESULT_NOT_SUPPORT           0x0002
/* Command is pending */
#define HostCmd_RESULT_PENDING               0x0003
/* System is busy (command ignored) */
#define HostCmd_RESULT_BUSY                  0x0004
/* Data buffer is not big enough */
#define HostCmd_RESULT_PARTIAL_DATA          0x0005

/* Definition of action or option for each command */

/* Define general purpose action */
#define HostCmd_ACT_GEN_READ                    0x0000
#define HostCmd_ACT_GEN_WRITE                   0x0001
#define HostCmd_ACT_GEN_GET                     0x0000
#define HostCmd_ACT_GEN_SET                     0x0001
#define HostCmd_ACT_GEN_REMOVE                  0x0002
#define HostCmd_ACT_GEN_OFF                     0x0000
#define HostCmd_ACT_GEN_ON                      0x0001

/* Define action or option for HostCmd_CMD_802_11_SET_WEP */
#define HostCmd_ACT_ADD                         0x0002
#define HostCmd_ACT_REMOVE                      0x0004

#define HostCmd_TYPE_WEP_40_BIT                 0x0001
#define HostCmd_TYPE_WEP_104_BIT                0x0002

#define HostCmd_WEP_KEY_INDEX_MASK              0x3fff

/* Define action or option for HostCmd_CMD_802_11_SCAN */
#define HostCmd_BSS_TYPE_BSS                    0x0001
#define HostCmd_BSS_TYPE_IBSS                   0x0002
#define HostCmd_BSS_TYPE_ANY                    0x0003

/* Define action or option for HostCmd_CMD_802_11_SCAN */
#define HostCmd_SCAN_TYPE_ACTIVE                0x0000
#define HostCmd_SCAN_TYPE_PASSIVE               0x0001

/* Radio type definitions for the channel TLV */
#define HostCmd_SCAN_RADIO_TYPE_BG		0
#define HostCmd_SCAN_RADIO_TYPE_A		1

/* Define action or option for HostCmd_CMD_MAC_CONTROL */
#define HostCmd_ACT_MAC_RX_ON                   0x0001
#define HostCmd_ACT_MAC_TX_ON                   0x0002
#define HostCmd_ACT_MAC_LOOPBACK_ON             0x0004
#define HostCmd_ACT_MAC_WEP_ENABLE              0x0008
#define HostCmd_ACT_MAC_ETHERNETII_ENABLE       0x0010
#define HostCmd_ACT_MAC_PROMISCUOUS_ENABLE      0x0080
#define HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE    0x0100
#define HostCmd_ACT_MAC_STRICT_PROTECTION_ENABLE  0x0400
#define HostCmd_ACT_MAC_ADHOC_G_PROTECTION_ON	  0x2000

/* Define action or option or constant for HostCmd_CMD_MAC_MULTICAST_ADR */
#define HostCmd_SIZE_MAC_ADR                    6
#define HostCmd_MAX_MCAST_ADRS                  32

#define RADIO_ON                                0x01
#define RADIO_OFF                               0x00

/* Define action or option for CMD_802_11_RF_CHANNEL */
#define HostCmd_OPT_802_11_RF_CHANNEL_GET       0x00
#define HostCmd_OPT_802_11_RF_CHANNEL_SET       0x01

#define HostCmd_ACT_SET_RX                      0x0001
#define HostCmd_ACT_SET_TX                      0x0002
#define HostCmd_ACT_SET_BOTH                    0x0003
#define HostCmd_ACT_GET_RX                      0x0004
#define HostCmd_ACT_GET_TX                      0x0008
#define HostCmd_ACT_GET_BOTH                    0x000c

/** Card Event definition */
#define MACREG_INT_CODE_DUMMY_HOST_WAKEUP_SIGNAL       0x00000001
#define MACREG_INT_CODE_LINK_LOST_WITH_SCAN     0x00000002
#define MACREG_INT_CODE_LINK_LOST       	0x00000003
#define MACREG_INT_CODE_LINK_SENSED             0x00000004
#define MACREG_INT_CODE_MIB_CHANGED             0x00000006
#define MACREG_INT_CODE_INIT_DONE               0x00000007
#define MACREG_INT_CODE_DEAUTHENTICATED         0x00000008
#define MACREG_INT_CODE_DISASSOCIATED           0x00000009
#define MACREG_INT_CODE_PS_AWAKE                0x0000000a
#define MACREG_INT_CODE_PS_SLEEP                0x0000000b
#define MACREG_INT_CODE_MIC_ERR_MULTICAST       0x0000000d
#define MACREG_INT_CODE_MIC_ERR_UNICAST         0x0000000e
#define MACREG_INT_CODE_WM_AWAKE                0x0000000f
#define MACREG_INT_CODE_DEEP_SLEEP_AWAKE        0x00000010
#define MACREG_INT_CODE_ADHOC_BCN_LOST          0x00000011
#define MACREG_INT_CODE_HOST_SLEEP_AWAKE        0x00000012
#define MACREG_INT_CODE_WMM_STATUS_CHANGE	0x00000017
#define MACREG_INT_CODE_BG_SCAN_REPORT		0x00000018
#define MACREG_INT_CODE_RSSI_LOW		0x00000019
#define MACREG_INT_CODE_SNR_LOW			0x0000001a
#define MACREG_INT_CODE_MAX_FAIL		0x0000001b
#define MACREG_INT_CODE_RSSI_HIGH		0x0000001c
#define MACREG_INT_CODE_SNR_HIGH		0x0000001d
#define MACREG_INT_CODE_IBSS_COALESCED		0x0000001e

/* Define bitmap conditions for HOST_SLEEP_CFG */
#define HOST_SLEEP_CFG_CANCEL			0xffffffff

#endif /* _HOST_H_ */
