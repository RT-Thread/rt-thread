/**
 ****************************************************************************************
 *
 * @file iface_defs.h
 *
 * @brief Featrue define
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

#ifndef __IFACE_DEFS_H__
#define __IFACE_DEFS_H__

/*
 * Interface definitions
 */

/* NVRAM KEYWORD START */

#define NETMODE                       "NETMODE"
#define NETMODE_WIFI_PROFILE          "netmode"

#define WIFI_PROFILE_DNSSVR_0         "dns_0"
#define WIFI_PROFILE_DNSSVR_1         "dns_1"
#define WIFI_PROFILE_DNSSVR_2ND_0     "dns_2nd_0"
#define WIFI_PROFILE_DNSSVR_2ND_1     "dns_2nd_1"
#define STATIC_IP_ADDRESS             "ipaddress"
#define STATIC_IP_NETMASK             "subnetmask"
#define STATIC_IP_GATEWAY             "gateway"
#define STATIC_IPV6_ADDRESS           "IPV6ADDR"

/* DHCP Server */
#define DHCP_SERVER_START_IP          "1:DHCPD_S_IP"
#define DHCP_SERVER_END_IP            "1:DHCPD_E_IP"
#define DHCP_SERVER_LEASE_TIME        "1:DHCPD_TIME"
#define DHCP_SERVER_DNS               "1:DHCPD_DNS"
#define DHCP_SERVER_RESPONSE_DELAY    "1:DHCPD_RESP_DELAY"

#define DHCPV6_SERVER_START_IP        "DHCPV6D_S_IP"
#define DHCPV6_SERVER_END_IP          "DHCPV6D_E_IP"
#define DHCPV6_SERVER_DNS             "DHCPV6D_DNS"
#define DHCPV6_SERVER_LEASE_TIME      "DHCPV6D_TIME"

#define ENV_SYS_MODE                  "SYSMODE"
#define ENV_SWITCH_SYSMODE            "SWITCH_SYSMODE"
#define ENV_KEY_TEMP_STATIC_IP        "0:TEMP_STATIC_IP" // Temporarily use a static IPaddress.

/* NVRAM KEYWORD END */

/* NETWORK Define */
#define NETMODE_DHCPCLIENT            "dhcp"
#define IPADDR_LEN                    16
#define IP6ADDR_LEN                   40
#define DHCPCLIENT                    1
#define STATIC_IP                     2

#define WLAN0_IFACE                   0
#define WLAN1_IFACE                   1
#define ETH0_IFACE                    2
#define NONE_IFACE                    9

#define IFACE_UP                      1
#define IFACE_DOWN                    0

#define GET_MACADDR                   0
#define GET_IPADDR                    1
#define GET_SUBNET                    2
#define GET_GATEWAY                   3
#define GET_MTU                       4
#define GET_DNS                       5
#define GET_DNS_2ND                   6
#define GET_IPV6                      7

/* #################################################### */

enum dhcp_client_state
{
    DHCP_CLIENT_CREATE,
    DHCP_CLIENT_INFO,
    DHCP_CLIENT_STOP,
    DHCP_CLIENT_START,
    DHCP_CLIENT_FORCING_RENEW,
    DHCP_CLIENT_RELEASE,
    DHCP_CLIENT_STATUS                 /* add by sj.lee 21060721 */
};

enum dhcp_server_state
{
    DHCP_SERVER_STATE_STATUS,
    DHCP_SERVER_STATE_START,
    DHCP_SERVER_STATE_STOP,
    DHCP_SERVER_STATE_RANGE,
    DHCP_SERVER_STATE_LEASE_TIME,
    DHCP_SERVER_STATE_LEASE_TABLE,
    DHCP_SERVER_STATE_DNS,
    DHCP_SERVER_STATE_RESPONSE_DELAY,
    DHCP_SERVER_STATE_DEBUG,
    DHCP_SERVER_STATE_HELP,
    DHCP_SERVER_STATE_STATUS_AT        /* add by sj.lee for AT_CMD */
};

enum network_state
{
    P2P_NET_GO,
    P2P_NET_CLIENT,
    P2P_NET_DEVICE,
    INF_NET_STATION
};

/* DEFALUT VALUE */
/* HTTP Server */
#define DEFAULT_HTTP_SERVER_PORT          80

#define DEFAULT_IPADDR_WLAN0              "172.16.0.100"
#define DEFAULT_SUBNET_WLAN0              "255.255.255.0"
#define DEFAULT_GATEWAY_WLAN0             "172.16.0.1"
#define DEFAULT_DNS_WLAN0                 "8.8.8.8"        /* Google DNS */
#define DEFAULT_DNS_2ND                   "208.67.222.222" /* OpenDNS */

#define DEFAULT_IPADDR_WLAN1              "10.0.0.1"
#define DEFAULT_SUBNET_WLAN1              "255.255.255.0"
#define DEFAULT_GATEWAY_WLAN1             "10.0.0.1"
#define DEFAULT_DNS_WLAN1                 "8.8.8.8" /* Google DNS */

#define DEFAULT_NETMODE_WLAN0             DHCPCLIENT
#define DEFAULT_NETMODE_WLAN1             STATIC_IP

/* DHCP Server */
#define MAX_DHCP_LEASE_COUNT              10
#define DEFAULT_DHCP_LEASE_COUNT          10
#define MAX_DHCP_SERVER_LEASE_TIME        3600 * 24
#define MIN_DHCP_SERVER_LEASE_TIME        60
#define DEFAULT_DHCP_SERVER_LEASE_TIME    1800

#define P2P_GO_IP_ADDR                    "192.168.20.1"
#define P2P_GO_NETMASK                    "255.255.255.0"
#define P2P_GO_IP_DHCP_START              "192.168.20.2"
#define P2P_GO_IP_DHCP_END                "192.168.20.11"
#define P2P_GO_DNS_IP                     "8.8.8.8"

#define IPADDR_ANY_STR                    "0.0.0.0"

#endif                                 /* __IFACE_DEFS_H__ */

/* EOF */
