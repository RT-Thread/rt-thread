/**
 ****************************************************************************************
 *
 * @file custom_config_sdk.h
 *
 * @brief Configuration for Generic-SDK
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef __CUSTOM_CONFIG_SDK_H__
#define __CUSTOM_CONFIG_SDK_H__

/// Global Define : Chipset Model
#if (TIN_SKU_BUILD_ID == TIN_SKU_WIFI6_B24_5_BLE || (defined(BSP_MCU_RRQ61051_208) || defined(BSP_MCU_RRQ61051_408)))
 #define CHIPSET_NAME    "RA6W2-RRQ61051"
#else
 #define CHIPSET_NAME    "RA6W1-RRQ61001"
#endif                                 /* TIN_SKU_BUILD_ID == TIN_SKU_WIFI6_B24_5_BLE || (BSP_MCU_RRQ61051_208 || BSP_MCU_RRQ61051_408) */

///
/// Features for RA6W1/RA6W2 SDK
///

#if (SIGMA_TEST_APP == 1)
 #define SIGMA_TEST_ENABLE
 #define STA_CERT_ENABLE
 #undef ATCMD_IF_SUPPORT
 #undef ATCMD_SECURE_CHANNEL
#endif

// SDK Name
// Show the kind of SDK displayed by the "ver" command in the console.
//
// - SDK Version     : VX.Y.Z.R SDK_NAME
//
#undef  SDK_NAME
#define SDK_NAME    ""                 // Default No name tag.

// SDK Version number
// Define the SDK version number by the "ver" command in the console.
//
// - SDK Version     : X.M.Y.Z.R
//
// #define SDK_VER_PRODUCT_LINE     X       // SDK Product line number
// #define SDK_VER_MODE             M       // SDK Mode number (Standalone:0 / Linux Driver:1)
// #define SDK_VER_TARGET           Y       // SDK Target release
// #define SDK_VER_BRANCH           Z       // SDK Branch number
// #define SDK_VER_R                    R       // SDK R&D build number
//
#include "sdk_ver.h"
#if (CFG_WIFI == 1)
 #include "rm_wifi.h"
#endif

///////////////////////////////////////////////////////////////////////
//
// Software module features of RA6W1/RA6W2 SDK
//
///////////////////////////////////////////////////////////////////////

// -----------------------
// HW Related Features
// -----------------------

//
// Enable/Disable WPS button
//
// To enable this feature,
// : EVK board configuration
// connect BTN2 to P0_12 (Default PIN, See EVK Board manual)
// : customer can change its configuration
// ~/sdk/bsp/config/boards/brd_io_config_rrq61x.h
//
#define __SUPPORT_WPS_BTN__

//
// Enable/Disable Factory Reset button
//
// To enable this feature,
// : EVK board configuration
// connect BTN1 to P0_13 (Default PIN, See EVK Board manual)
// : customer can change its configuration
// ~/sdk/bsp/config/boards/brd_io_config_rrq61x.h
//
#define __SUPPORT_FACTORY_RESET_BTN__

//
// Enable/Disable RF antenna share for Wi-Fi & BT co-existence
//
#undef  __SUPPORT_BTCOEX__

//
// UART2 interface connect to MCU for AT-CMD
// This interface (UART2) initialize when AT-CMD module start...
//
// When enable this feature,
// customer can change the default values for UART2
// - DEFAULT_UART_BAUD : 115,200bps
// - UART_BITPERCHAR   : 8bits
// - UART_PARITY       : No parity
// - UART_STOPBIT      : 1 stopbit
// - UART_FLOW_CTRL    : No flow-control
//
// : Or can change UART2 configuration values thought ATB command.
// See AT-CMD user manual.
#undef  __SUPPORT_UART2__

//
// Enable/Disable OSPI sflash api
// Remove it after FSP merged
#ifndef RRQ61X_OSPI_W_ENABLED
 #define RRQ61X_OSPI_W_ENABLED
#endif                                 /* RRQ61X_OSPI_W_ENABLED */

// -----------------------
// Wi-Fi Features
// -----------------------

//
// Support Wi-Fi WPA3-Personal features. ( SAE, OWE )
//
// Note #1) See Wi-Fi specification to understand WPA3 SAE and OWE operation.
// Note #2) If "__SUPPORT_ATCMD__" is enabled, this feature is default enabled also.
//
//
#define __SUPPORT_WPA3_PERSONAL__

//
// Support Wi-Fi WPA Enterprise feature.
//
// This feature is internal feature in ~/library/libsupplicant.a
// When enable this feature, more detail features are support below sub-features.
// In sub-feature, WPA3-Enterprise feature will be selected. Default is Enable.
//
// Note) If "__SUPPORT_ATCMD__" is enabled, this feature is default enabled also.
// Refer to AT-CMD user's guide document for how to use it.
//
#define __SUPPORT_WPA_ENTERPRISE__

//
// Support customer call-back functions to notify Wi-Fi connection status.
//
// This features notify the Wi-Fi connection status through registered customer call-back function.
// - Wi-Fi connection status
// - Wi-Fi disconnection status
// - Wi-Fi connection failed status
//
// Customers can change these call-back function to whatever operation they want.
// - static void user_wifi_conn(void *arg)
// - static void user_wifi_conn_fail(void *arg)
// - static void user_wifi_disconn(void *arg)
//
// These functions are registered through the "void rm_wifi_register_wifi_notify_cb(void)"
// in ~/projects/rrq61x/rrq61x/src/user_app.c
// And when start the RA6W1/RA6W2, "register_wifi_notifi_cb()" is called in net_stack_init().
//
// In case of enabled "AT-CMD feature", the RA6W1/RA6W2 notifies the connection status to MCU.
// Customer can check this function "atcmd_asynchony_event()"
// in ~/sdk/interfaces/wifi/system/src/at_cmd/atcmd.c
// These notification are reported through internal events operation.
//
// - STA connect OK
// : +WFJAP:1,TEST_SSID,IP_ADDR
// - STA connect Fail
// : +WFJAP:0,TIMEOUT
// : +WFJAP:0,WRONGPWD
// : +WFJAP:0,ACCESSLIMIT
// : +WFJAP:0,OTHER,reason_code
// - STA disconnect
// : +WFDAP:0,AUTH_NOT_VALID
// : +WFDAP:0,DEAUTH
// : +WFDAP:0,INACTIVITY
// : +WFDAP:0,APBUSY
// : +WFDAP:0,OTHER,reason_code
//
#undef  __SUPPORT_WIFI_CONN_CB__

//
// Support Wi-Fi Concurrent-mode.
//
// Wi-Fi Concurrent mode means two interface will be enabled.
// One (wlan0) is STA and the other (wlan1) is Soft-AP.
//
// In easy-setup, three types of Wi-Fi operation mode will be provided.
// SYSMODE(WLAN MODE) ?
// 1. Station
// 2. Soft-AP
// 3. Station & SOFT-AP                   <= Wi-Fi Concurrent-mode
// MODE ?  [1/2/3/Quit] (Default Station) :
//
#define  __SUPPORT_WIFI_CONCURRENT__

// -----------------------
// System Features
// -----------------------

//
// Fast Connection on SLEEP mode 2
//
// Enable/Disable Fast-connection feature.
// This function is internal one and Customer just can select enable/disable when SDK rebuild.
//
// And AT-CMD mode, two AT-CMDs are supported to handle by MCU.
// : AT+GETFASTCONN
// : AT+SETFASTCONN
//
#define __SUPPORT_FAST_CONN_SLEEP_2__

//
// Support cipher suites of TLS session by H/W engine.
//
// When enable this feature, only HW cipher-suites of CC312 HW enbine are used to communicate for TLS.
// This operation set in each TLS application to start TLS operation.
//
// #if defined(__SUPPORT_TLS_HW_CIPHER_SUITES__)
// preset = MBEDTLS_SSL_PRESET_RRQ_HW;
// #endif /* __SUPPORT_TLS_HW_CIPHER_SUITES__ */
#undef  __SUPPORT_TLS_HW_CIPHER_SUITES__

//
// Enable/Disable AT-CMD module
//
// When this feature is enabled, more detailed sub-features are supported.
// Customer can check all AT-CMDs in ~/sdk/interfaces/wifi/system/src/at_cmd/atcmd.c
//
#if (ATCMD_IF_SUPPORT == 1)
 #define __SUPPORT_ATCMD__
#else
 #undef  __SUPPORT_ATCMD__
#endif                                 // (ATCMD_IF_SUPPORT == 1)

//
// Support FAT filesystem
//
// Configurations are defined in ~/sdk/middleware/storage/fat/ffconf.h
#undef  __SUPPORT_FAT_FS__

// -----------------------
// Network Features
// -----------------------

//
// Support IPv6 feature
// Sub feature is defined in ~/sdk/interfaces/wifi/stack/lwip/src/include/lwipopts.h
//
#ifndef __SUPPORT_IPV4__
 #define __SUPPORT_IPV4__    1
#endif

#ifndef __SUPPORT_IPV6__
 #define __SUPPORT_IPV6__    1
#endif

//
// Support DHCP Server on the RA6W1/RA6W2 Soft-AP mode.
//
#define __SUPPORT_DHCP_SVR__

//
// Support SNTP Client feature
//
// This feature enable SNTP client to get current time from the defined Internet time server.
//
#if (CFG_WIFI == 1)
 #define __SUPPORT_SNTP_CLIENT__
#endif

//
// Support Websocket Client
//
// This feature enable Websocket client to communicate with peer Websocket server.
//
#define  __SUPPORT_WEBSOCKET_CLIENT__

//
// Support "nslookup" network utility
//
// This function is used to get IP-address from doman-name.
// Support console-command under "net" command layer.
//
// Default disabled.
//
#define __SUPPORT_NSLOOKUP__

//
// Support Auto-start HTTP server application when system starting.
//
// Customer can check this task in ~/core/system/src/common/main/sys_apps.c
//
// static const app_task_info_t sys_apps_table[] = {
// ...
// #if defined ( __HTTP_SVR_AUTO_START__ )
// { APP_HTTP_SVR, auto_run_http_svr, 256, (OS_TASK_PRIORITY_NORMAL + 6), TRUE, FALSE, HTTP_SVR_PORT, RUN_AP_MODE },
// #endif // __HTTP_SVR_AUTO_START__
//
// Note) If "__SUPPORT_ATCMD__" is enabled, this feature is default enabled also.
// Refer to AT-CMD user's guide document for how to use it.
//
#undef  __HTTP_SVR_AUTO_START__

//
// Support CLI command on Console for HTTP-Server operation
// This feature supports to check the operation status with console command.
//
// NET              : Network
// -------          : --------------------------------
// http-server      : http-server -I [wlan0|wlan1] [start|stop]
//
// These commands operate with own IP-address and 80 port number as default.
//
#undef __SUPPORT_HTTP_SERVER_FOR_CLI__

//
// Support CLI command on Console for HTTP-Client operation
// This feature supports to check the operation status with console command.
//
// NET              : Network
// -------          : --------------------------------
// http-client      : http-client help
//
// [/RRQ61000/NET] # http-client
//
// Usage: HTTP Client
// Name
// http-client - HTTP Client
// SYNOPSIS
// http-client [OPTION]...URL
// DESCRIPTION
// Request client's method to URL
// -i [wlan0|wlan1]
// Set interface of HTTP Client
// -status
// Display status of HTTP Client
// -help
// Display help
// -head
// Request HEAD method to URI
// -get
// Request GET method to URI
// -post RESOURCE
// Request POST method to URI with RESOURCE
// -put RESOURCE
// Request PUT method to URI with RESOURCE
// -incoming Size
// Set incoming buffer size of TLS Contents
// -outgoing Size
// Set outgoing buffer size of TLS Contents
// -sni <Server Name Indicator>
// Set SNI for TLS extension
// -alpn <ALPN Protocols>
// Set ALPN for TLS extension
//
#undef __SUPPORT_HTTP_CLIENT_FOR_CLI__

//
// Support DNS 2nd cache internally.
//
// This function supports semi-cache operation to reduce DNS query time.
// The address found as a new domain name is stored in the memory,
// and when a new DNS Query is performed, the address is first found in the cache area.
// This caching IP addresses are also save in NVRAM to reload when booting time.
//
// Stores up to 25 domain-names and IP address.
// The maximum length of domain name is 128 Bytes.
//
// Note) If this feature is enabled,
// do not use 4KB from SFLASH_USER_AREA_START area for other purpose.
//
#undef  __DNS_2ND_CACHE_SUPPORT__

#ifdef __DNS_2ND_CACHE_SUPPORT__
 #undef  __DNS_2ND_CACHE_INFO__
#endif                                 /* __DNS_2ND_CACHE_SUPPORT__ */

//
// Support "dns cache" info utility
//
// This function is for viewing DNS cache information.
// Support console-command under "net" command layer.
//
// Default disabled.
#undef  __DNS_CACHE_INFO__

//
// Support User DHCP-client hostname function.
//
// This feature support to set user DHCP hostname rather than default value (RA6WX-XXYY).
// When enable this feature, console command is enabled.
//
// Note #1) This feature complies with RFCs(952, 1123).
// : RFCs(952, 1123) mandate that a hostname's labels may contain only
// the ASCII letters 'a' through 'z' (case-insensitive),
// the digits '0' through '9', and the hyphen.
// Hostname labels cannot begin or end with a hyphen.
// No other symbols, punctuation characters, or blank spaces are permitted.
//
// Note #2) If "__SUPPORT_ATCMD__" is enabled, this feature is default enabled also.
//
// - AT+NWDHCHN
// - AT+NWDHCHNDEL
//
// Refer to AT-CMD user's guide document for how to use it.
//
#undef  __USER_DHCP_HOSTNAME__

//
// Support iPerf tool for network performance measurement.
//
// This test operation can operate using by console commands.
//
// Note) iPerf 2.X version is compatible but don't compatible with iPerf V3.X on peer device.
//
// [/RRQ61000/NET] # iperf -help
// Usage:  iperf -I [WLAN0|WLAN1] [-s|-c host][options]
// iperf [-h] [-v]
//
// Client/Server:
// -I      Interface [WLAN0|WLAN1]
// -i      seconds between periodic bandwidth reports
// -u      use UDP rather than TCP
// -p, #   server port to listen on/connect to
// -f, [kmKM]   format to report: Kbits, Mbits, KBytes, MBytes
// -d      finsh service
// ex) iperf -I [wlan0|wlan1] -d -c -u : udp clinet
// iperf -I [wlan0|wlan1] -d -c    : tcp clinet
// iperf -I [wlan0|wlan1] -d -u    : udp server
// iperf -I [wlan0|wlan1] -d       : tcp server
//
// Server specific:
// -s      run in server mode
// -T  #   Rx Time Out Min:1 sec. 'F' Forever
//
// Client specific:
// -c      <host>   run in client mode, connecting to <host>
// -t  #   time in seconds to transmit for (default 10 secs)
// -x  #   tcp API mode default:basic tcp(API) 1:Altcp 2:Socket
// -y  #   Transmit delay, tick 1 ~ 100
// -l  #   PacketSize option (UDP default 1470, IPv6 1448 TCP 1000)
// -n  #   UDP Tx packet number
// -P, #   Pair Index (0,1,2)
// (default Max, Step 1~100 Mbps)
// -O      use Main Packet Pool
//
// Miscellaneous:
// -h      print this message
// -v      print version
//
// Refer to "RA6W1/RA6W2 Getting Started Guide" document for more detailed information
// to use iPerf tool on the RA6W1/RA6W2.
//
#if (CFG_WIFI == 1)
 #define __SUPPORT_IPERF__             // support iperf
 #undef  __SUPPORT_IPERF3__            // support iperf3
 #define __SUPPORT_WIFI_DBG__          // support wifi debug
#endif

//
// Easy-setup on console
//
// Support CLI command on Console to create/save Wi-Fi connection profile in NVRAM.
//
#if CFG_WIFI 
#define __SUPPORT_EASY_SETUP__         // Easy Setup application.
#endif
// -------------------
// User Features
// -------------------

//
// User can set maximum size of http-client's tx buffer. (Default 4KB, Available 2KB~8KB)
//
// HTTPC_REQ_DATA_MAX_SIZE affects the size of TX_PAYLOAD_MAX_SIZE and USER_ATCMD_BUF defined in atcmd.h.
// TX_PAYLOAD_MAX_SIZE and USER_ATCMD_BUF must always be greater than HTTPC_REQ_DATA_MAX_SIZE.
//
// #define TX_PAYLOAD_MAX_SIZE              HTTPC_REQ_DATA_MAX_SIZE
// #define USER_ATCMD_BUF                   (TX_PAYLOAD_MAX_SIZE + 32)
//
#define HTTPC_REQ_DATA_MAX_SIZE    (1024 * 4)
#if (HTTPC_REQ_DATA_MAX_SIZE < (1024 * 2))
 #error "Supporting buffer size error : Too small !!!"
#elif (HTTPC_REQ_DATA_MAX_SIZE > (1024 * 8))
 #error "Supporting buffer size error : Too large !!!"
#endif

///////////////////////////////////////////////////////////////////////
//
// SUB-features for Generic-SDK
//
///////////////////////////////////////////////////////////////////////
//

#if !defined(RENESAS_AT25SL_8MB_OTA) && !defined(NORMAL_4MB_OTA)
 #undef  __SUPPORT_OTA__
#endif                                 // !RENESAS_AT25SL_8MB_OTA && !NORMAL_4MB_OTA

#if defined(CONFIG_PLT_TEST)
 #define __SUPPORT_PRODTEST__
 #ifndef __SUPPORT_ATCMD__
  #define __SUPPORT_ATCMD__
 #endif
#endif

#if defined __SUPPORT_FAST_CONN_SLEEP_2__
 #define __SUPPORT_DHCPC_IP_TO_STATIC_IP__
 #undef  __BOOT_CONN_TIME_PRINT__
#endif                                 // __SUPPORT_FAST_CONN_SLEEP_2__

#if defined(__SUPPORT_ATCMD__)

//
// Default interface of RRQ61x EVK is UART2.
// Customer can change the type of host-interfaces among four types listed below.
// __ATCMD_IF_UART2__ / __ATCMD_IF_UART3__ / __ATCMD_IF_SPI__ / __ATCMD_IF_SDIO__
// When one is enabled, the other 3 should be disabled.
//
 #if (ATCMD_IF_SUPPORT == 1)
  #undef  __ATCMD_IF_UART2__               // AT-CMD over UART2
  #undef  __ATCMD_IF_UART3__               // AT-CMD over UART3
  #undef  __ATCMD_IF_SPI__                 // AT-CMD over SPI
  #undef  __ATCMD_IF_SDIO__                // AT-CMD over SDIO
 #else

/* UART3 is dedicated to FSP, so UART2 is used for AT-CMD */
  #define __ATCMD_IF_UART2__               // AT-CMD over UART2
  #undef  __ATCMD_IF_UART3__               // AT-CMD over UART3
  #undef  __ATCMD_IF_SPI__                 // AT-CMD over SPI
  #undef  __ATCMD_IF_SDIO__                // AT-CMD over SDIO
 #endif                                    // (ATCMD_IF_SUPPORT == 1)

 #define __SUPPORT_TCP_RECVDATA_HEX_MODE__ // Support AT+TCPDATAMODE command
 #undef  __ENABLE_TXFIFO_CHK_IN_LOW_BAUDRATE__
 #define __SUPPORT_NOTIFY_RTC_WAKEUP__
 #undef  __USER_UART_CONFIG__              // Support Customer's UART configuration

 #undef  __TRIGGER_DPM_MCU_WAKEUP__        // MCU Wakeup-triggering when DPM UC wakeup
 #define  __DPM_WAKEUP_NOTICE_ADDITIONAL__ // Report DPM Wakeup RTC/ETC
 #undef  __SUPPORT_DPM_ABNORM_MSG__        // Send message to MCU when wake-up from DPM Abnormal stat
 #undef __SUPPORT_DPM_EXT_WU_MON__         // DPM monitor for External Wakeup
 #if defined(__SUPPORT_DPM_EXT_WU_MON__)
  #undef  __SUPPORT_UC_WU_MON__            // DPM monitor for UC Wakeup
 #endif                                    // __SUPPORT_DPM_EXT_WU_MON__

 #undef  __DISABLE_ESC_DATA_ECHO__         // Echo ESC data input ( Data Tx Mode )
 #if defined(__DISABLE_ESC_DATA_ECHO__)
  #define __ENABLE_ESC_DATA_DUMP__         // Tx Data dump on UART2
 #endif                                    // __DISABLE_ESC_DATA_ECHO__

 #undef __SUPPORT_HTTP_SERVER_FOR_ATCMD__  // HTTP server
 #undef  __SUPPORT_HTTP_SERVER_FOR_CLI__

 #undef __SUPPORT_HTTP_CLIENT_FOR_ATCMD__  // HTTP client
 #undef  __SUPPORT_HTTP_CLIENT_FOR_CLI__

//
// Support User-format to send HTTP-Client request ( header + body )
//
// When a customer requests an http-client using AT-CMD,
// the header format already defined in http_client.c is not used, but the header is written in free form.
// If there is data to be sent, such as PUT or POST, it can be configured in the form of header + data.
//
// This function is used by MCU through AT-CMDs.
// : AT+NWHTC=<URL>,message,'XXXXX'
//
// Note) Refer to AT-CMD user's guide document for how to use it.
//
 #define __SUPPORT_HTTP_CLIENT_USER_MSG__

 #define __SUPPORT_WPA3_PERSONAL__     // Wi-Fi WPA3-Personal ( SAE, OWE )
 #define __SUPPORT_WPA_ENTERPRISE__    // Wi-Fi WPA Enterprise
 #define __SUPPORT_FAST_CONN_SLEEP_2__

 #undef  __ENABLE_TRANSFER_MNG__       // Ring-Buffer for throughput
 #define __USER_DHCP_HOSTNAME__        // User DHCP-client hostname
 #define __SUPPORT_DETAILED_ERR_CODE__ // Support detailed error code

 #define __SUPPORT_RSSI_CMD__          // AT+WFRSSI
 #if (ATCMD_IF_SUPPORT == 1)
  #define __SUPPORT_ATCMD_TLS__        // TLS session
 #else
  #undef  __SUPPORT_ATCMD_TLS__        // TLS session
 #endif                                // (ATCMD_IF_SUPPORT == 1)
 #undef  __SUPPORT_USER_CMD_HELP__     // User AT-CMD Help
 #undef  __SUPPORT_PERI_CTRL__         // Support LED/I2C/PWM/ADC over AT-CMD
 #undef  __SUPPORT_LMAC_RF_CMD__       // AT-CMDs for LMAC/RF
 #undef  __SUPPORT_PERI_CMD__          // AT-CMDs for peripheral devices

// Reconfig for AT-CMD
 #undef  __SUPPORT_HELLO_WORLD__
#endif                                 // __SUPPORT_ATCMD__

// If RAM build mode then always enable LMAC RF CMDs ...
#if (dg_configCODE_LOCATION == NON_VOLATILE_IS_NONE) && defined(CONFIG_PLT_TEST)
 #undef  __SUPPORT_FAST_CONN_SLEEP_2__
 #undef  __SUPPORT_OTA__
 #undef  __SUPPORT_MQTT__
 #undef  __SUPPORT_HTTP_SERVER_FOR_ATCMD__ // HTTP server
 #undef  __SUPPORT_HTTP_CLIENT_FOR_ATCMD__ // HTTP client
 #undef  __SUPPORT_WPA3_PERSONAL__         // Wi-Fi WPA3-Personal ( SAE, OWE )
 #undef  __SUPPORT_WPA_ENTERPRISE__        // Wi-Fi WPA Enterprise
#endif

#if defined(__SUPPORT_PRODTEST__)
 #define __USER_UART_CONFIG__              // Set to default, not to read from NVRam
 #define __SUPPORT_PRODTEST_CONSOLE__      // Enable if requires for quick test
 #define __SUPPORT_TCS_CMD__
 #ifdef  __SUPPORT_TCS_CMD__
  #define TEST_TCS_OTP                     // For test OTP
 #endif
 #ifndef  __SUPPORT_LMAC_RF_CMD__
  #define __SUPPORT_LMAC_RF_CMD__
 #endif
#endif

#if defined(__SUPPORT_BTCOEX__)
 #undef  __SUPPORT_BTCOEX_1PIN__         // 1PIN BTCOEX
#endif                                   // __SUPPORT_BTCOEX__

#if defined(__SUPPORT_FACTORY_RESET_BTN__)
 #define __SUPPORT_FACTORY_RST_APMODE__  // Factory reset AP-Mode
 #undef  __SUPPORT_FACTORY_RST_STAMODE__ // Factory reset STA-Mode
#endif                                   // __SUPPORT_FACTORY_RESET_BTN__

#if defined(__SUPPORT_OTA__)
 #undef  __OTA_UPDATE_MCU_FW__
 #if defined(__OTA_UPDATE_MCU_FW__) && !defined(__ATCMD_IF_SPI__) && !defined(__ATCMD_IF_SDIO__)
  #if (ATCMD_IF_SUPPORT == 1)
   #undef  __SUPPORT_UART2__
  #else
   #define __SUPPORT_UART2__
  #endif                               // (ATCMD_IF_SUPPORT == 1)
 #endif                                // __OTA_UPDATE_MCU_FW__ ...
#endif                                 // __SUPPORT_OTA__

#if defined(__SUPPORT_WPA_ENTERPRISE__)
 #define __SUPPORT_WPA3_ENTERPRISE__

 #if defined(__SUPPORT_WPA3_ENTERPRISE__)
  #define __SUPPORT_WPA3_ENTERPRISE_192B__ // Unsupported on RA6W1/RA6W2
 #endif                                    // __SUPPORT_WPA3_ENTERPRISE__
#endif                                     /* __SUPPORT_WPA_ENTERPRISE__ */

#if defined(__SUPPORT_IPERF__)
 #undef  __IPERF_BANDWIDTH__               // Debug only
 #undef  __IPERF_PRINT_MIB__               // Print iPerf MIB Info.
 #undef  __LIB_IPERF_PRINT_MIB__           // Print iPerf MIB Info.
#endif                                     // __SUPPORT_IPERF__

#if defined(__SUPPORT_EASY_SETUP__)
 #define __SUPPORT_APP_CONSOLE_INPUT__     // Handle application's console input
 #undef  __SUPPORT_DFS_CH_IN_SOFTAP__      // Support DFS channel in SoftAP
#endif                                     // __SUPPORT_EASY_SETUP__

#if defined(__SUPPORT_WPS_BTN__) || defined(__SUPPORT_FACTORY_RESET_BTN__)

//
// Enable LED for WPS PBC and Factory Reset
//
// To enable this feature,
// : EVK board configuration
// connect LED0 to P1_14 (Default PIN, See EVK Board manual)
// : customer can change its configuration
// ~/sdk/bsp/config/boards/brd_io_config_rrq61x.h
//
 #if defined (LED0)
   #define  __SUPPORT_EVK_LED__
 #endif
 #define  __SUPPORT_FACTORY_RST_CONCURR_MODE__
#endif                                 /* defined (__SUPPORT_WPS_BTN__) || defined (__SUPPORT_FACTORY_RESET_BTN__) */

///////////////////////////////////////////////////////////////////////
//
// DEPENDENT-features for customer SDK
//
///////////////////////////////////////////////////////////////////////

#if defined(__SUPPORT_ATCMD__)
 #if defined(__ATCMD_IF_SDIO__)
  #undef  __SUPPORT_WPS_BTN__           // WPS button
  #undef  __SUPPORT_FACTORY_RESET_BTN__ // Factory reset Button
 #endif                                 // __ATCMD_IF_SDIO__

 #if defined(__SUPPORT_OTA__)
  #define __OTA_UPDATE_MCU_FW__
  #if defined(__OTA_UPDATE_MCU_FW__) && !defined(__ATCMD_IF_SPI__) && !defined(__ATCMD_IF_SDIO__)
   #if (ATCMD_IF_SUPPORT == 1)
    #undef  __SUPPORT_UART2__
   #else
    #define __SUPPORT_UART2__
   #endif                              // (ATCMD_IF_SUPPORT == 1)
  #endif                               // __OTA_UPDATE_MCU_FW__
 #endif                                // __SUPPORT_OTA__

 #if defined(__SUPPORT_WIFI_PROVISIONING__)
  #define __PROVISION_ATCMD__          // provisioining at cmd
 #endif                                // __SUPPORT_WIFI_PROVISIONING__

 #ifdef __SUPPORT_WEBSOCKET_CLIENT__
  #define __SUPPORT_WEBSOCKET_CLIENT_FOR_ATCMD__
 #endif                                // __SUPPORT_WEBSOCKET_CLIENT__

 #if defined(__SUPPORT_LMAC_RF_CMD__)
  #define __ENABLE_LMAC_CMD__
  #define __ENABLE_LMAC_TX_CMD__
  #define __ENABLE_RF_CMD__
 #endif                                // __SUPPORT_LMAC_RF_CMD__
#endif                                 // __SUPPORT_ATCMD__

#if defined(__SUPPORT_HTTP_SERVER_FOR_CLI__) || defined(__SUPPORT_HTTP_SERVER_FOR_ATCMD__)
 #undef  __HTTP_SVR_AUTO_START__
#endif                                 // __SUPPORT_HTTP_SERVER_FOR_CLI__ || __SUPPORT_HTTP_SERVER_FOR_ATCMD__

////////////////////////////////////////////////////////////////////////////
//
// !!! Notice !!!
// Do not remove this line and do not move the location in this file.
//

#include "sys_feature_sdk.h"

////////////////////////////////////////////////////////////////////////////

#if (CFG_WIFI == 0)
 #undef __SUPPORT_SNTP_CLIENT__
 #undef __SUPPORT_P2P__
#endif

#endif                                 // __CUSTOM_CONFIG_SDK_H__

/* EOF */
