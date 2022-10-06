/**
*  \file lwiplib.h
*
*  \brief lwip abstraction layer related declarations
*/
/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
*/

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef __LWIPLIB_H__
#define __LWIPLIB_H__

#include "src/include/lwip/opt.h"

/* Ensure that AUTOIP COOP option is configured correctly.*/
#undef LWIP_DHCP_AUTOIP_COOP
#define LWIP_DHCP_AUTOIP_COOP   ((LWIP_DHCP) && (LWIP_AUTOIP))

#include "src/include/lwip/api.h"
#include "src/include/lwip/netifapi.h"
#include "src/include/lwip/tcp.h"
#include "src/include/lwip/udp.h"
#include "src/include/lwip/tcpip.h"
#include "src/include/lwip/sockets.h"
#include "src/include/lwip/mem.h"
#include "src/include/lwip/stats.h"

/******************************************************************************
**                            Macro Definitions
******************************************************************************/
#define IPADDR_USE_STATIC                  (0)
#define IPADDR_USE_DHCP                    (1)
#define IPADDR_USE_AUTOIP                  (2)

#ifndef LEN_MAC_ADDRESS
#define LEN_MAC_ADDRESS                    (6)
#endif

#define MAX_ALE_ENTRIES                    (1024)
#define ALE_ENTRY_NUM_WORDS                (3)

#define ERR_PASS                           (0)
#define ERR_FAIL                           (-1)
#define ERR_INVAL                          (-2)

#define MIN_SLV_PORT                       (1)
#define MIN_AUTONEG                        (0)
#define MIN_PHY_CONFIG                     (1)
#define MIN_SPEED                          (0)
#define MIN_DUPLEX                         (0)

#define MAX_SLV_PORT                       (2)
#define MAX_AUTONEG                        (1)
#define MAX_PHY_CONFIG                     (0x3F)
#define MAX_SPEED                          (2)
#define MAX_DUPLEX                         (1)

#define ERR_SLV_PORT                       (-25)
#define ERR_AUTONEG                        (-26)
#define ERR_PHY_CONFIG                     (-27)
#define ERR_SPEED                          (-28)
#define ERR_DUPLEX                         (-29)

#ifdef CPSW_SWITCH_CONFIG
#define MIN_VLANAWARE                      (0)
#define MIN_ALE_VLANAWARE                  (0)
#define MIN_ALE_ENTRY_IDX                  (0)
#define MIN_VLAN_UNTAG                     (0)
#define MIN_VLAN_MCAST_UNREG               (0)
#define MIN_VLAN_MCAST_REG                 (0)
#define MIN_MCAST_FWD_STATE                (0)
#define MIN_SUPER                          (0)
#define MIN_PORT_MASK                      (0)
#define MIN_UCAST_FLAGS                    (0)
#define MIN_PORT                           (0)
#define MIN_VLANID                         (0)
#define MIN_CFI                            (0)
#define MIN_PRI                            (0)
#define MIN_UNKNOWN_VLAN_TYPE              (1)
#define MIN_PORT_STATE                     (0)
#define MIN_ADDR_TYPE                      (1)
#define MIN_ENABLE                         (0)
#define MIN_DIRECTION                      (0)
#define MIN_LIMIT                          (0)
#define MIN_UNKNOWN_VLAN                   (1)
#define MIN_MAC_AUTH                       (0)

#define MAX_VLANAWARE                      (1)
#define MAX_ALE_VLANAWARE                  (1)
#define MAX_ALE_ENTRY_IDX                  (1023)
#define MAX_VLAN_UNTAG                     (7)
#define MAX_VLAN_MCAST_UNREG               (7)
#define MAX_VLAN_MCAST_REG                 (7)
#define MAX_MCAST_FWD_STATE                (3)
#define MAX_SUPER                          (1)
#define MAX_PORT_MASK                      (7)
#define MAX_UCAST_FLAGS                    (3)
#define MAX_PORT                           (2)
#define MAX_VLANID                         (4095)
#define MAX_CFI                            (1)
#define MAX_PRI                            (7)
#define MAX_UNKNOWN_VLAN_TYPE              (4)
#define MAX_PORT_STATE                     (3)
#define MAX_ADDR_TYPE                      (3)
#define MAX_ENABLE                         (1)
#define MAX_DIRECTION                      (1)
#define MAX_LIMIT                          (255)
#define MAX_UNKNOWN_VLAN                   (4)
#define MAX_MAC_AUTH                       (1)

#define ERR_ADDR                           (-3)
#define ERR_VLANID                         (-4)
#define ERR_PORT_MASK                      (-5)
#define ERR_SUPER                          (-6)
#define ERR_MCAST_FWD_STATE                (-7)
#define ERR_PORT                           (-8)
#define ERR_UCAST_FLAGS                    (-9)
#define ERR_VLAN_MCAST_REG                 (-10)
#define ERR_VLAN_MCAST_UNREG               (-11)
#define ERR_VLAN_MCAST_UNTAG               (-12)
#define ERR_ALE_ENTRY_IDX                  (-13)
#define ERR_VLANAWARE                      (-14)
#define ERR_ALE_VLANAWARE                  (-15)
#define ERR_CFI                            (-16)
#define ERR_PRI                            (-17)
#define ERR_ENABLE                         (-18)
#define ERR_DIRECTION                      (-19)
#define ERR_LIMIT                          (-20)
#define ERR_UNKNOWN_VLAN                   (-21)
#define ERR_MAC_AUTH                       (-22)
#define ERR_ADDR_TYPE                      (-23)
#define ERR_PORT_STATE                     (-24)
#endif

#ifdef CPSW_SWITCH_CONFIG
enum {
  ADDR_TYPE_BROADCAST = 1,
  ADDR_TYPE_MULTICAST,
  ADDR_TYPE_UNICAST,
};

enum {
  ALE_PORT_UNTAGGED_EGRESS = 1,
  ALE_PORT_UNKNOWN_REG_MCAST_FLOOD,
  ALE_PORT_UNKNOWN_UNREG_MCAST_FLOOD,
  ALE_PORT_UNKNOWN_VLAN_MEMBER,
};
#endif

enum {
  CONFIG_SWITCH_INVALID = 0,
#ifdef CPSW_SWITCH_CONFIG
  CONFIG_SWITCH_ADD_MULTICAST,
  CONFIG_SWITCH_ADD_UNICAST,
  CONFIG_SWITCH_ADD_OUI,
  CONFIG_SWITCH_FIND_ADDR,
  CONFIG_SWITCH_DEL_MULTICAST,
  CONFIG_SWITCH_DEL_UNICAST,
  CONFIG_SWITCH_ADD_VLAN,
  CONFIG_SWITCH_FIND_VLAN,
  CONFIG_SWITCH_DEL_VLAN,
  CONFIG_SWITCH_PORT_VLAN_CONFIG,
  CONFIG_SWITCH_AGEOUT,
  CONFIG_SWITCH_DUMP,
  CONFIG_SWITCH_CONFIG_DUMP,
  CONFIG_SWITCH_VLANAWARE,
  CONFIG_SWITCH_RATELIMIT,
  CONFIG_SWITCH_VID_INGRESS_CHECK,
  CONFIG_SWITCH_ADD_UNKNOWN_VLAN_INFO,
  CONFIG_SWITCH_MACAUTH,
  CONFIG_SWITCH_PORT_STATE,
#endif
  CONFIG_SWITCH_SET_PORT_CONFIG,
};

#ifdef CPSW_SWITCH_CONFIG
typedef struct cpsw_switch_param {
  u32_t  port_num;
  u32_t  port_mask;
  u32_t  vid;        /* VLAN identifier */
  u32_t  prio_port;  /* port priority 0 -7 */
  u32_t  cfi_port;   /* port CFI  0 /1 */
  u32_t  unreg_multi;    /* unreg multicast Egress Ports */
  u32_t  reg_multi;  /* register multicast Egress ports */
  u32_t  untag_port; /* Untag ports */
  u8_t  addr[LEN_MAC_ADDRESS]; /* Ethernet Address */
  u32_t  super;
  u32_t  fwd_state;
  u32_t  ucast_flags;
  u32_t  ucast_type;
  u32_t  blocked;
  u32_t  secure;
  u32_t  ageable;
  u32_t  ale_tbl_index;    /* if 1 print ale table */
  u32_t  vlan_aware;
  u32_t  drop_packet;
  u32_t  direction;  /* Tx -1 / Rx - 0 */
  u32_t  addr_type;  /* Address type BroadMulti/Uni cast */
  u32_t  limit;      /* multicast/broadcast limit */
  u32_t  vlan_ingress_check;
  u32_t  port_state;
  u32_t  drop_untagged;
  u32_t  enable;     /* 1-enable/0-Disable */
  u32_t  unknown_vlan;
  u32_t  mac_auth;
}CPSW_SW_PARAM_IF;
#endif

typedef struct cpsw_phy_param {
  u32_t  slv_port_num;
  u32_t  autoneg;
  u32_t  config;
  u32_t  speed;
  u32_t  duplex;
}CPSW_PHY_PARAM_IF;

typedef struct cpsw_config {
  u32_t cmd;   /* API to be invoked by the kernel driver */
  u32_t cpsw_inst;
  struct cpsw_phy_param *phy_param;
#ifdef CPSW_SWITCH_CONFIG
  struct cpsw_switch_param *switch_param;
  u32_t  buf[MAX_ALE_ENTRIES][ALE_ENTRY_NUM_WORDS]; /* Buffer for Ale Dump */
  u32_t  ale_entry[ALE_ENTRY_NUM_WORDS];
#endif
  s32_t ret;   /* Return  Success/Failure */
}CPSW_CONF_IF;

typedef struct lwipIf
{
    unsigned int instNum;   /* Instance Number */
    unsigned int slvPortNum; /* CPSW Slave Port Number */
    unsigned int ipAddr; /* IP Address */
    unsigned int netMask; /* Net Mask */
    unsigned int gwAddr; /* Gate Way Address */
    unsigned int ipMode; /* IP Address mode  
                            IPADDR_USE_STATIC - force static IP 
                                                addressing to be used \n
                            IPADDR_USE_DHCP - force DHCP with fallback
                                              to Link Local \n
                            IPADDR_USE_AUTOIP */  
    unsigned char macArray[LEN_MAC_ADDRESS]; /* MAC Address to be used*/
}LWIP_IF;

/******************************************************************************
**                    lwIP Abstraction Layer API
******************************************************************************/
extern unsigned int lwIPLinkStatusGet(unsigned int instNum, 
                                      unsigned int slvPortNum);
extern unsigned int lwIPNetIfStatusGet(unsigned int instNum, 
                                       unsigned int slvPortNum);
extern unsigned int lwIPInit(LWIP_IF *lwipIf);
extern void lwIPRxIntHandler(unsigned int instNum);
extern void lwIPTxIntHandler(unsigned int instNum);
extern unsigned int lwIPDHCPStart(unsigned int instNum,
                                  unsigned int slvPortNum);
extern void cpsw_switch_configuration(struct cpsw_config  *cpsw_config);
#endif /* __LWIPLIB_H__ */
