/*
 * Copyright (c) 2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Date:        31. May 2019
 * $Revision:    V1.0
 *
 * Project:      WiFi (Wireless Fidelity Interface) Driver definitions
 */

/* History:
 *  Version 1.0
 *    Initial release
 */

#ifndef DRIVER_WIFI_H_
#define DRIVER_WIFI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define ARM_WIFI_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */

#define _ARM_Driver_WiFi_(n)      Driver_WiFi##n
#define  ARM_Driver_WiFi_(n) _ARM_Driver_WiFi_(n)


/****** WiFi SetOption/GetOption Function Option Codes *****/
#define ARM_WIFI_BSSID                      1U          ///< Station/AP Set/Get BSSID of AP to connect or of AP;        data = &bssid,    len =  6, uint8_t[6]
#define ARM_WIFI_TX_POWER                   2U          ///< Station/AP Set/Get transmit power;                         data = &power,    len =  4, uint32_t: 0 .. 20 [dBm]
#define ARM_WIFI_LP_TIMER                   3U          ///< Station    Set/Get low-power deep-sleep time;              data = &time,     len =  4, uint32_t [seconds]: 0 = disable (default)
#define ARM_WIFI_DTIM                       4U          ///< Station/AP Set/Get DTIM interval;                          data = &dtim,     len =  4, uint32_t [beacons]
#define ARM_WIFI_BEACON                     5U          ///<         AP Set/Get beacon interval;                        data = &interval, len =  4, uint32_t [ms]
#define ARM_WIFI_MAC                        6U          ///< Station/AP Set/Get MAC;                                    data = &mac,      len =  6, uint8_t[6]
#define ARM_WIFI_IP                         7U          ///< Station/AP Set/Get IPv4 static/assigned address;           data = &ip,       len =  4, uint8_t[4]
#define ARM_WIFI_IP_SUBNET_MASK             8U          ///< Station/AP Set/Get IPv4 subnet mask;                       data = &mask,     len =  4, uint8_t[4]
#define ARM_WIFI_IP_GATEWAY                 9U          ///< Station/AP Set/Get IPv4 gateway address;                   data = &ip,       len =  4, uint8_t[4]
#define ARM_WIFI_IP_DNS1                    10U         ///< Station/AP Set/Get IPv4 primary   DNS address;             data = &ip,       len =  4, uint8_t[4]
#define ARM_WIFI_IP_DNS2                    11U         ///< Station/AP Set/Get IPv4 secondary DNS address;             data = &ip,       len =  4, uint8_t[4]
#define ARM_WIFI_IP_DHCP                    12U         ///< Station/AP Set/Get IPv4 DHCP client/server enable/disable; data = &dhcp,     len =  4, uint32_t: 0 = disable, non-zero = enable (default)
#define ARM_WIFI_IP_DHCP_POOL_BEGIN         13U         ///<         AP Set/Get IPv4 DHCP pool begin address;           data = &ip,       len =  4, uint8_t[4]
#define ARM_WIFI_IP_DHCP_POOL_END           14U         ///<         AP Set/Get IPv4 DHCP pool end address;             data = &ip,       len =  4, uint8_t[4]
#define ARM_WIFI_IP_DHCP_LEASE_TIME         15U         ///<         AP Set/Get IPv4 DHCP lease time;                   data = &time,     len =  4, uint32_t [seconds]
#define ARM_WIFI_IP6_GLOBAL                 16U         ///< Station/AP Set/Get IPv6 global address;                    data = &ip6,      len = 16, uint8_t[16]
#define ARM_WIFI_IP6_LINK_LOCAL             17U         ///< Station/AP Set/Get IPv6 link local address;                data = &ip6,      len = 16, uint8_t[16]
#define ARM_WIFI_IP6_SUBNET_PREFIX_LEN      18U         ///< Station/AP Set/Get IPv6 subnet prefix length;              data = &len,      len =  4, uint32_t: 1 .. 127
#define ARM_WIFI_IP6_GATEWAY                19U         ///< Station/AP Set/Get IPv6 gateway address;                   data = &ip6,      len = 16, uint8_t[16]
#define ARM_WIFI_IP6_DNS1                   20U         ///< Station/AP Set/Get IPv6 primary   DNS address;             data = &ip6,      len = 16, uint8_t[16]
#define ARM_WIFI_IP6_DNS2                   21U         ///< Station/AP Set/Get IPv6 secondary DNS address;             data = &ip6,      len = 16, uint8_t[16]
#define ARM_WIFI_IP6_DHCP_MODE              22U         ///< Station/AP Set/Get IPv6 DHCPv6 client mode;                data = &mode,     len =  4, uint32_t: ARM_WIFI_IP6_DHCP_xxx (default Off)

/****** WiFi Security Type *****/
#define ARM_WIFI_SECURITY_OPEN              0U          ///< Open
#define ARM_WIFI_SECURITY_WEP               1U          ///< Wired Equivalent Privacy (WEP) with Pre-Sheared Key (PSK)
#define ARM_WIFI_SECURITY_WPA               2U          ///< WiFi Protected Access (WPA) with PSK
#define ARM_WIFI_SECURITY_WPA2              3U          ///< WiFi Protected Access II (WPA2) with PSK
#define ARM_WIFI_SECURITY_UNKNOWN           255U        ///< Unknown

/****** WiFi Protected Setup (WPS) Method *****/
#define ARM_WIFI_WPS_METHOD_NONE            0U          ///< Not used
#define ARM_WIFI_WPS_METHOD_PBC             1U          ///< Push Button Configuration
#define ARM_WIFI_WPS_METHOD_PIN             2U          ///< PIN

/****** WiFi IPv6 Dynamic Host Configuration Protocol (DHCP) Mode *****/
#define ARM_WIFI_IP6_DHCP_OFF               0U          ///< Static Host Configuration (default)
#define ARM_WIFI_IP6_DHCP_STATELESS         1U          ///< Dynamic Host Configuration stateless DHCPv6
#define ARM_WIFI_IP6_DHCP_STATEFULL         2U          ///< Dynamic Host Configuration statefull DHCPv6

/****** WiFi Event *****/
#define ARM_WIFI_EVENT_AP_CONNECT          (1UL << 0)   ///< Access Point: Station has connected;           arg = &mac, mac (uint8_t[6])
#define ARM_WIFI_EVENT_AP_DISCONNECT       (1UL << 1)   ///< Access Point: Station has disconnected;        arg = &mac, mac (uint8_t[6])
#define ARM_WIFI_EVENT_ETH_RX_FRAME        (1UL << 4)   ///< Ethernet Frame Received (in bypass mode only); arg = interface (0 = Station, 1 = Access Point)


/**
\brief WiFi Configuration
*/
typedef struct {
  const char   *ssid;                                   ///< Pointer to Service Set Identifier (SSID) null-terminated string
  const char   *pass;                                   ///< Pointer to Password null-terminated string
        uint8_t security;                               ///< Security type (ARM_WIFI_SECURITY_xxx)
        uint8_t ch;                                     ///< WiFi Channel (0 = auto, otherwise = exact channel)
        uint8_t reserved;                               ///< Reserved
        uint8_t wps_method;                             ///< WiFi Protected Setup (WPS) method (ARM_WIFI_WPS_METHOD_xxx)
  const char   *wps_pin;                                ///< Pointer to WiFi Protected Setup (WPS) PIN null-terminated string
} ARM_WIFI_CONFIG_t;

/**
\brief WiFi Scan Information
*/
typedef struct {
  char    ssid[32+1];                                   ///< Service Set Identifier (SSID) null-terminated string
  uint8_t bssid[6];                                     ///< Basic Service Set Identifier (BSSID)
  uint8_t security;                                     ///< Security type (ARM_WIFI_SECURITY_xxx)
  uint8_t ch;                                           ///< WiFi Channel
  uint8_t rssi;                                         ///< Received Signal Strength Indicator
} ARM_WIFI_SCAN_INFO_t;

/**
\brief WiFi Network Information
*/
typedef struct {
  char    ssid[32+1];                                   ///< Service Set Identifier (SSID) null-terminated string
  char    pass[64+1];                                   ///< Password null-terminated string
  uint8_t security;                                     ///< Security type (ARM_WIFI_SECURITY_xxx)
  uint8_t ch;                                           ///< WiFi Channel
  uint8_t rssi;                                         ///< Received Signal Strength Indicator
} ARM_WIFI_NET_INFO_t;

/****** Socket Address Family definitions *****/
#define ARM_SOCKET_AF_INET                  1           ///< IPv4
#define ARM_SOCKET_AF_INET6                 2           ///< IPv6

/****** Socket Type definitions *****/
#define ARM_SOCKET_SOCK_STREAM              1           ///< Stream socket
#define ARM_SOCKET_SOCK_DGRAM               2           ///< Datagram socket

/****** Socket Protocol definitions *****/
#define ARM_SOCKET_IPPROTO_TCP              1           ///< TCP
#define ARM_SOCKET_IPPROTO_UDP              2           ///< UDP

/****** Socket Option definitions *****/
#define ARM_SOCKET_IO_FIONBIO               1           ///< Non-blocking I/O (Set only, default = 0); opt_val = &nbio, opt_len = sizeof(nbio), nbio (integer): 0=blocking, non-blocking otherwise
#define ARM_SOCKET_SO_RCVTIMEO              2           ///< Receive timeout in ms (default = 0); opt_val = &timeout, opt_len = sizeof(timeout)
#define ARM_SOCKET_SO_SNDTIMEO              3           ///< Send timeout in ms (default = 0); opt_val = &timeout, opt_len = sizeof(timeout)
#define ARM_SOCKET_SO_KEEPALIVE             4           ///< Keep-alive messages (default = 0); opt_val = &keepalive, opt_len = sizeof(keepalive), keepalive (integer): 0=disabled, enabled otherwise
#define ARM_SOCKET_SO_TYPE                  5           ///< Socket Type (Get only); opt_val = &socket_type, opt_len = sizeof(socket_type), socket_type (integer): ARM_SOCKET_SOCK_xxx

/****** Socket Function return codes *****/
#define ARM_SOCKET_ERROR                   (-1)         ///< Unspecified error
#define ARM_SOCKET_ESOCK                   (-2)         ///< Invalid socket
#define ARM_SOCKET_EINVAL                  (-3)         ///< Invalid argument
#define ARM_SOCKET_ENOTSUP                 (-4)         ///< Operation not supported
#define ARM_SOCKET_ENOMEM                  (-5)         ///< Not enough memory
#define ARM_SOCKET_EAGAIN                  (-6)         ///< Operation would block or timed out
#define ARM_SOCKET_EINPROGRESS             (-7)         ///< Operation in progress
#define ARM_SOCKET_ETIMEDOUT               (-8)         ///< Operation timed out
#define ARM_SOCKET_EISCONN                 (-9)         ///< Socket is connected
#define ARM_SOCKET_ENOTCONN                (-10)        ///< Socket is not connected
#define ARM_SOCKET_ECONNREFUSED            (-11)        ///< Connection rejected by the peer
#define ARM_SOCKET_ECONNRESET              (-12)        ///< Connection reset by the peer
#define ARM_SOCKET_ECONNABORTED            (-13)        ///< Connection aborted locally
#define ARM_SOCKET_EALREADY                (-14)        ///< Connection already in progress
#define ARM_SOCKET_EADDRINUSE              (-15)        ///< Address in use
#define ARM_SOCKET_EHOSTNOTFOUND           (-16)        ///< Host not found


// Function documentation
/**
  \fn            ARM_DRIVER_VERSION ARM_WIFI_GetVersion (void)
  \brief         Get driver version.
  \return        \ref ARM_DRIVER_VERSION
*/
/**
  \fn            ARM_WIFI_CAPABILITIES ARM_WIFI_GetCapabilities (void)
  \brief         Get driver capabilities.
  \return        \ref ARM_WIFI_CAPABILITIES
*/
/**
  \fn            int32_t ARM_WIFI_Initialize (ARM_WIFI_SignalEvent_t cb_event)
  \brief         Initialize WiFi Module.
  \param[in]     cb_event Pointer to \ref ARM_WIFI_SignalEvent_t
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
*/
/**
  \fn            int32_t ARM_WIFI_Uninitialize (void)
  \brief         De-initialize WiFi Module.
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
*/
/**
  \fn            int32_t ARM_WIFI_PowerControl (ARM_POWER_STATE state)
  \brief         Control WiFi Module Power.
  \param[in]     state     Power state
                   - \ref ARM_POWER_OFF                : Power off: no operation possible
                   - \ref ARM_POWER_LOW                : Low-power mode: sleep or deep-sleep depending on \ref ARM_WIFI_LP_TIMER option set
                   - \ref ARM_POWER_FULL               : Power on: full operation at maximum performance
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid state)
*/
/**
  \fn            int32_t ARM_WIFI_GetModuleInfo (char *module_info, uint32_t max_len)
  \brief         Get Module information.
  \param[out]    module_info Pointer to character buffer were info string will be returned
  \param[in]     max_len     Maximum length of string to return (including null terminator)
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (NULL module_info pointer or max_len equals to 0)
*/
/**
  \fn            int32_t ARM_WIFI_SetOption (uint32_t interface, uint32_t option, const void *data, uint32_t len)
  \brief         Set WiFi Module Options.
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \param[in]     option    Option to set
  \param[in]     data      Pointer to data relevant to selected option
  \param[in]     len       Length of data (in bytes)
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface, NULL data pointer or len less than option specifies)
*/
/**
  \fn            int32_t ARM_WIFI_GetOption (uint32_t interface, uint32_t option, void *data, uint32_t *len)
  \brief         Get WiFi Module Options.
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \param[in]     option    Option to get
  \param[out]    data      Pointer to memory where data for selected option will be returned
  \param[in,out] len       Pointer to length of data (input/output)
                   - input: maximum length of data that can be returned (in bytes)
                   - output: length of returned data (in bytes)
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface, NULL data or len pointer, or *len less than option specifies)
*/
/**
  \fn            int32_t ARM_WIFI_Scan (ARM_WIFI_SCAN_INFO_t scan_info[], uint32_t max_num)
  \brief         Scan for available networks in range.
  \param[out]    scan_info Pointer to array of ARM_WIFI_SCAN_INFO_t structures where available Scan Information will be returned
  \param[in]     max_num   Maximum number of Network Information structures to return
  \return        number of ARM_WIFI_SCAN_INFO_t structures returned or error code
                   - value >= 0                        : Number of ARM_WIFI_SCAN_INFO_t structures returned
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (NULL scan_info pointer or max_num equal to 0)
*/
/**
  \fn            int32_t ARM_WIFI_Activate (uint32_t interface, ARM_WIFI_CONFIG_t *config)
  \brief         Activate interface (Connect to a wireless network or activate an access point).
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \param[in]     config    Pointer to ARM_WIFI_CONFIG_t structure where Configuration parameters are located
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_TIMEOUT     : Timeout occurred
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported (security type, channel autodetect or WPS not supported)
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface, NULL config pointer or invalid configuration)
*/
/**
  \fn            int32_t ARM_WIFI_Deactivate (uint32_t interface)
  \brief         Deactivate interface (Disconnect from a wireless network or deactivate an access point).
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface)
*/
/**
  \fn            uint32_t ARM_WIFI_IsConnected (void)
  \brief         Get station connection status.
  \return        station connection status
                   - value != 0: Station connected
                   - value = 0: Station not connected
*/
/**
  \fn            int32_t ARM_WIFI_GetNetInfo (ARM_WIFI_NET_INFO_t *net_info)
  \brief         Get station Network Information.
  \param[out]    net_info  Pointer to ARM_WIFI_NET_INFO_t structure where station Network Information will be returned
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed (station not connected)
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface or NULL net_info pointer)
*/
/**
  \fn            int32_t ARM_WIFI_BypassControl (uint32_t interface, uint32_t mode)
  \brief         Enable or disable bypass (pass-through) mode. Transmit and receive Ethernet frames (IP layer bypassed and WiFi/Ethernet translation).
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \param[in]     mode
                   - value = 1: all packets bypass internal IP stack
                   - value = 0: all packets processed by internal IP stack
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface or mode)
*/
/**
  \fn            int32_t ARM_WIFI_EthSendFrame (uint32_t interface, const uint8_t *frame, uint32_t len)
  \brief         Send Ethernet frame (in bypass mode only).
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \param[in]     frame    Pointer to frame buffer with data to send
  \param[in]     len      Frame buffer length in bytes
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_BUSY        : Driver is busy
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface or NULL frame pointer)
*/
/**
  \fn            int32_t ARM_WIFI_EthReadFrame (uint32_t interface, uint8_t *frame, uint32_t len)
  \brief         Read data of received Ethernet frame (in bypass mode only).
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \param[in]     frame    Pointer to frame buffer for data to read into
  \param[in]     len      Frame buffer length in bytes
  \return        number of data bytes read or error code
                   - value >= 0                        : Number of data bytes read
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (invalid interface or NULL frame pointer)
*/
/**
  \fn            uint32_t ARM_WIFI_EthGetRxFrameSize (uint32_t interface)
  \brief         Get size of received Ethernet frame (in bypass mode only).
  \param[in]     interface Interface (0 = Station, 1 = Access Point)
  \return        number of bytes in received frame
*/
/**
  \fn            int32_t ARM_WIFI_SocketCreate (int32_t af, int32_t type, int32_t protocol)
  \brief         Create a communication socket.
  \param[in]     af       Address family
  \param[in]     type     Socket type
  \param[in]     protocol Socket protocol
  \return        status information
                   - Socket identification number (>=0)
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument
                   - \ref ARM_SOCKET_ENOTSUP           : Operation not supported
                   - \ref ARM_SOCKET_ENOMEM            : Not enough memory
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketBind (int32_t socket, const uint8_t *ip, uint32_t ip_len, uint16_t port)
  \brief         Assign a local address to a socket.
  \param[in]     socket   Socket identification number
  \param[in]     ip       Pointer to local IP address
  \param[in]     ip_len   Length of 'ip' address in bytes
  \param[in]     port     Local port number
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (address or socket already bound)
                   - \ref ARM_SOCKET_EADDRINUSE        : Address already in use
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketListen (int32_t socket, int32_t backlog)
  \brief         Listen for socket connections.
  \param[in]     socket   Socket identification number
  \param[in]     backlog  Number of connection requests that can be queued
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (socket not bound)
                   - \ref ARM_SOCKET_ENOTSUP           : Operation not supported
                   - \ref ARM_SOCKET_EISCONN           : Socket is already connected
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketAccept (int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
  \brief         Accept a new connection on a socket.
  \param[in]     socket   Socket identification number
  \param[out]    ip       Pointer to buffer where address of connecting socket shall be returned (NULL for none)
  \param[in,out] ip_len   Pointer to length of 'ip' (or NULL if 'ip' is NULL)
                   - length of supplied 'ip' on input
                   - length of stored 'ip' on output
  \param[out]    port     Pointer to buffer where port of connecting socket shall be returned (NULL for none)
  \return        status information
                   - socket identification number of accepted socket (>=0)
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (socket not in listen mode)
                   - \ref ARM_SOCKET_ENOTSUP           : Operation not supported (socket type does not support accepting connections)
                   - \ref ARM_SOCKET_ECONNRESET        : Connection reset by the peer
                   - \ref ARM_SOCKET_ECONNABORTED      : Connection aborted locally
                   - \ref ARM_SOCKET_EAGAIN            : Operation would block or timed out (may be called again)
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketConnect (int32_t socket, const uint8_t *ip, uint32_t ip_len, uint16_t port)
  \brief         Connect a socket to a remote host.
  \param[in]     socket   Socket identification number
  \param[in]     ip       Pointer to remote IP address
  \param[in]     ip_len   Length of 'ip' address in bytes
  \param[in]     port     Remote port number
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument
                   - \ref ARM_SOCKET_EALREADY          : Connection already in progress
                   - \ref ARM_SOCKET_EINPROGRESS       : Operation in progress
                   - \ref ARM_SOCKET_EISCONN           : Socket is connected
                   - \ref ARM_SOCKET_ECONNREFUSED      : Connection rejected by the peer
                   - \ref ARM_SOCKET_ECONNABORTED      : Connection aborted locally
                   - \ref ARM_SOCKET_EADDRINUSE        : Address already in use
                   - \ref ARM_SOCKET_ETIMEDOUT         : Operation timed out
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketRecv (int32_t socket, void *buf, uint32_t len)
  \brief         Receive data on a connected socket.
  \param[in]     socket   Socket identification number
  \param[out]    buf      Pointer to buffer where data should be stored
  \param[in]     len      Length of buffer (in bytes)
  \return        status information
                   - number of bytes received (>0)
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (pointer to buffer or length)
                   - \ref ARM_SOCKET_ENOTCONN          : Socket is not connected
                   - \ref ARM_SOCKET_ECONNRESET        : Connection reset by the peer
                   - \ref ARM_SOCKET_ECONNABORTED      : Connection aborted locally
                   - \ref ARM_SOCKET_EAGAIN            : Operation would block or timed out (may be called again)
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketRecvFrom (int32_t socket, void *buf, uint32_t len, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
  \brief         Receive data on a socket.
  \param[in]     socket   Socket identification number
  \param[out]    buf      Pointer to buffer where data should be stored
  \param[in]     len      Length of buffer (in bytes)
  \param[out]    ip       Pointer to buffer where remote source address shall be returned (NULL for none)
  \param[in,out] ip_len   Pointer to length of 'ip' (or NULL if 'ip' is NULL)
                   - length of supplied 'ip' on input
                   - length of stored 'ip' on output
  \param[out]    port     Pointer to buffer where remote source port shall be returned (NULL for none)
  \return        status information
                   - number of bytes received (>0)
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (pointer to buffer or length)
                   - \ref ARM_SOCKET_ENOTCONN          : Socket is not connected
                   - \ref ARM_SOCKET_ECONNRESET        : Connection reset by the peer
                   - \ref ARM_SOCKET_ECONNABORTED      : Connection aborted locally
                   - \ref ARM_SOCKET_EAGAIN            : Operation would block or timed out (may be called again)
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketSend (int32_t socket, const void *buf, uint32_t len)
  \brief         Send data on a connected socket.
  \param[in]     socket   Socket identification number
  \param[in]     buf      Pointer to buffer containing data to send
  \param[in]     len      Length of data (in bytes)
  \return        status information
                   - number of bytes sent (>0)
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (pointer to buffer or length)
                   - \ref ARM_SOCKET_ENOTCONN          : Socket is not connected
                   - \ref ARM_SOCKET_ECONNRESET        : Connection reset by the peer
                   - \ref ARM_SOCKET_ECONNABORTED      : Connection aborted locally
                   - \ref ARM_SOCKET_EAGAIN            : Operation would block or timed out (may be called again)
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketSendTo (int32_t socket, const void *buf, uint32_t len, const uint8_t *ip, uint32_t ip_len, uint16_t port)
  \brief         Send data on a socket.
  \param[in]     socket   Socket identification number
  \param[in]     buf      Pointer to buffer containing data to send
  \param[in]     len      Length of data (in bytes)
  \param[in]     ip       Pointer to remote destination IP address
  \param[in]     ip_len   Length of 'ip' address in bytes
  \param[in]     port     Remote destination port number
  \return        status information
                   - number of bytes sent (>0)
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (pointer to buffer or length)
                   - \ref ARM_SOCKET_ENOTCONN          : Socket is not connected
                   - \ref ARM_SOCKET_ECONNRESET        : Connection reset by the peer
                   - \ref ARM_SOCKET_ECONNABORTED      : Connection aborted locally
                   - \ref ARM_SOCKET_EAGAIN            : Operation would block or timed out (may be called again)
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketGetSockName (int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
  \brief         Retrieve local IP address and port of a socket.
  \param[in]     socket   Socket identification number
  \param[out]    ip       Pointer to buffer where local address shall be returned (NULL for none)
  \param[in,out] ip_len   Pointer to length of 'ip' (or NULL if 'ip' is NULL)
                   - length of supplied 'ip' on input
                   - length of stored 'ip' on output
  \param[out]    port     Pointer to buffer where local port shall be returned (NULL for none)
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (pointer to buffer or length)
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketGetPeerName (int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
  \brief         Retrieve remote IP address and port of a socket
  \param[in]     socket   Socket identification number
  \param[out]    ip       Pointer to buffer where remote address shall be returned (NULL for none)
  \param[in,out] ip_len   Pointer to length of 'ip' (or NULL if 'ip' is NULL)
                   - length of supplied 'ip' on input
                   - length of stored 'ip' on output
  \param[out]    port     Pointer to buffer where remote port shall be returned (NULL for none)
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument (pointer to buffer or length)
                   - \ref ARM_SOCKET_ENOTCONN          : Socket is not connected
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketGetOpt (int32_t socket, int32_t opt_id, void *opt_val, uint32_t *opt_len)
  \brief         Get socket option.
  \param[in]     socket   Socket identification number
  \param[in]     opt_id   Option identifier
  \param[out]    opt_val  Pointer to the buffer that will receive the option value
  \param[in,out] opt_len  Pointer to length of the option value
                   - length of buffer on input
                   - length of data on output
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument
                   - \ref ARM_SOCKET_ENOTSUP           : Operation not supported
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketSetOpt (int32_t socket, int32_t opt_id, const void *opt_val, uint32_t opt_len)
  \brief         Set socket option.
  \param[in]     socket   Socket identification number
  \param[in]     opt_id   Option identifier
  \param[in]     opt_val  Pointer to the option value
  \param[in]     opt_len  Length of the option value in bytes
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument
                   - \ref ARM_SOCKET_ENOTSUP           : Operation not supported
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketClose (int32_t socket)
  \brief         Close and release a socket.
  \param[in]     socket   Socket identification number
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_ESOCK             : Invalid socket
                   - \ref ARM_SOCKET_EAGAIN            : Operation would block (may be called again)
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_SocketGetHostByName (const char *name, int32_t af, uint8_t *ip, uint32_t *ip_len)
  \brief         Retrieve host IP address from host name.
  \param[in]     name     Host name
  \param[in]     af       Address family
  \param[out]    ip       Pointer to buffer where resolved IP address shall be returned
  \param[in,out] ip_len   Pointer to length of 'ip'
                   - length of supplied 'ip' on input
                   - length of stored 'ip' on output
  \return        status information
                   - 0                                 : Operation successful
                   - \ref ARM_SOCKET_EINVAL            : Invalid argument
                   - \ref ARM_SOCKET_ENOTSUP           : Operation not supported
                   - \ref ARM_SOCKET_ETIMEDOUT         : Operation timed out
                   - \ref ARM_SOCKET_EHOSTNOTFOUND     : Host not found
                   - \ref ARM_SOCKET_ERROR             : Unspecified error
*/
/**
  \fn            int32_t ARM_WIFI_Ping (const uint8_t *ip, uint32_t ip_len)
  \brief         Probe remote host with Ping command.
  \param[in]     ip       Pointer to remote host IP address
  \param[in]     ip_len   Length of 'ip' address in bytes
  \return        execution status
                   - \ref ARM_DRIVER_OK                : Operation successful
                   - \ref ARM_DRIVER_ERROR             : Operation failed
                   - \ref ARM_DRIVER_ERROR_TIMEOUT     : Timeout occurred
                   - \ref ARM_DRIVER_ERROR_UNSUPPORTED : Operation not supported
                   - \ref ARM_DRIVER_ERROR_PARAMETER   : Parameter error (NULL ip pointer or ip_len different than 4 or 16)
*/
/**
  \fn            void ARM_WIFI_SignalEvent (uint32_t event, void *arg)
  \brief         Signal WiFi Events.
  \param[in]     event    \ref wifi_event notification mask
  \param[in]     arg      Pointer to argument of signaled event
  \return        none
*/

typedef void (*ARM_WIFI_SignalEvent_t) (uint32_t event, void *arg); ///< Pointer to \ref ARM_WIFI_SignalEvent : Signal WiFi Event.


/**
\brief WiFi Driver Capabilities.
*/
typedef struct {
  uint32_t station               : 1;   ///< Station
  uint32_t ap                    : 1;   ///< Access Point
  uint32_t station_ap            : 1;   ///< Concurrent Station and Access Point
  uint32_t wps_station           : 1;   ///< WiFi Protected Setup (WPS) for Station
  uint32_t wps_ap                : 1;   ///< WiFi Protected Setup (WPS) for Access Point
  uint32_t event_ap_connect      : 1;   ///< Access Point: event generated on Station connect
  uint32_t event_ap_disconnect   : 1;   ///< Access Point: event generated on Station disconnect
  uint32_t event_eth_rx_frame    : 1;   ///< Event generated on Ethernet frame reception in bypass mode
  uint32_t bypass_mode           : 1;   ///< Bypass or pass-through mode (Ethernet interface)
  uint32_t ip                    : 1;   ///< IP (UDP/TCP) (Socket interface)
  uint32_t ip6                   : 1;   ///< IPv6 (Socket interface)
  uint32_t ping                  : 1;   ///< Ping (ICMP)
  uint32_t reserved              : 20;  ///< Reserved (must be zero)
} ARM_WIFI_CAPABILITIES;

/**
\brief Access structure of the WiFi Driver.
*/
typedef struct {
  ARM_DRIVER_VERSION    (*GetVersion)                  (void);
  ARM_WIFI_CAPABILITIES (*GetCapabilities)             (void);
  int32_t               (*Initialize)                  (ARM_WIFI_SignalEvent_t cb_event);
  int32_t               (*Uninitialize)                (void);
  int32_t               (*PowerControl)                (ARM_POWER_STATE state);
  int32_t               (*GetModuleInfo)               (char *module_info, uint32_t max_len);
  int32_t               (*SetOption)                   (uint32_t interface, uint32_t option, const void *data, uint32_t  len);
  int32_t               (*GetOption)                   (uint32_t interface, uint32_t option,       void *data, uint32_t *len);
  int32_t               (*Scan)                        (ARM_WIFI_SCAN_INFO_t scan_info[], uint32_t max_num);
  int32_t               (*Activate)                    (uint32_t interface, const ARM_WIFI_CONFIG_t *config);
  int32_t               (*Deactivate)                  (uint32_t interface);
  uint32_t              (*IsConnected)                 (void);
  int32_t               (*GetNetInfo)                  (ARM_WIFI_NET_INFO_t *net_info);
  int32_t               (*BypassControl)               (uint32_t interface, uint32_t mode);
  int32_t               (*EthSendFrame)                (uint32_t interface, const uint8_t *frame, uint32_t len);
  int32_t               (*EthReadFrame)                (uint32_t interface,       uint8_t *frame, uint32_t len);
  uint32_t              (*EthGetRxFrameSize)           (uint32_t interface);
  int32_t               (*SocketCreate)                (int32_t af, int32_t type, int32_t protocol);
  int32_t               (*SocketBind)                  (int32_t socket, const uint8_t *ip, uint32_t  ip_len, uint16_t  port);
  int32_t               (*SocketListen)                (int32_t socket, int32_t backlog);
  int32_t               (*SocketAccept)                (int32_t socket,       uint8_t *ip, uint32_t *ip_len, uint16_t *port);
  int32_t               (*SocketConnect)               (int32_t socket, const uint8_t *ip, uint32_t  ip_len, uint16_t  port);
  int32_t               (*SocketRecv)                  (int32_t socket, void *buf, uint32_t len);
  int32_t               (*SocketRecvFrom)              (int32_t socket, void *buf, uint32_t len, uint8_t *ip, uint32_t *ip_len, uint16_t *port);
  int32_t               (*SocketSend)                  (int32_t socket, const void *buf, uint32_t len);
  int32_t               (*SocketSendTo)                (int32_t socket, const void *buf, uint32_t len, const uint8_t *ip, uint32_t ip_len, uint16_t port);
  int32_t               (*SocketGetSockName)           (int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port);
  int32_t               (*SocketGetPeerName)           (int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port);
  int32_t               (*SocketGetOpt)                (int32_t socket, int32_t opt_id,       void *opt_val, uint32_t *opt_len);
  int32_t               (*SocketSetOpt)                (int32_t socket, int32_t opt_id, const void *opt_val, uint32_t  opt_len);
  int32_t               (*SocketClose)                 (int32_t socket);
  int32_t               (*SocketGetHostByName)         (const char *name, int32_t af, uint8_t *ip, uint32_t *ip_len);
  int32_t               (*Ping)                        (const uint8_t *ip, uint32_t ip_len);
} const ARM_DRIVER_WIFI;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_WIFI_H_ */
