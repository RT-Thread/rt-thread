/**
 * @file - cpswif.c
 * lwIP Ethernet interface for CPSW port
 *
 */

/**
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

/**
 * Copyright (c) 2010 Texas Instruments Incorporated
 *
 * This file is dervied from the "ethernetif.c" skeleton Ethernet network
 * interface driver for lwIP.
 */
#include "src/include/lwip/opt.h"
#include "src/include/lwip/def.h"
#include "src/include/lwip/mem.h"
#include "src/include/lwip/pbuf.h"
#include "src/include/lwip/sys.h"
#include "src/include/lwip/stats.h"
#include "src/include/lwip/snmp.h"
#include "src/include/netif/etharp.h"
#include "src/include/netif/ppp_oe.h"
#include "src/include/lwip/err.h"
#include "ports/cpsw/include/netif/cpswif.h"
#include "ports/cpsw/include/arch/cc.h"

/* DriverLib Header Files required for this interface driver. */
#include "cpsw.h"
#include "mdio.h"
#include "interrupt.h"
#include "delay.h"
#include "phy.h" 
#include "cache.h"

/* CPPI RAM size in bytes */
#ifndef SIZE_CPPI_RAM
#define SIZE_CPPI_RAM                            0x2000
#endif
 
#define PORT_1                                   0x0
#define PORT_2                                   0x1
#define PORT_0_MASK                              0x1
#define PORT_1_MASK                              0x2
#define PORT_2_MASK                              0x4
#define HOST_PORT_MASK                           PORT_0_MASK
#define SLAVE_PORT_MASK(slv_port_num)            (1 << slv_port_num)
#define PORT_MASK                                (0x7)
#define INDV_PORT_MASK(slv_port_num)             (1 << slv_port_num)

#define ENTRY_TYPE                               0x30
#define ENTRY_TYPE_IDX                           7
#define ENTRY_FREE                               0

/* MDIO input and output frequencies in Hz */
#define MDIO_FREQ_INPUT                          125000000
#define MDIO_FREQ_OUTPUT                         1000000

#define CPDMA_BUF_DESC_OWNER                     0x20000000
#define CPDMA_BUF_DESC_SOP                       0x80000000
#define CPDMA_BUF_DESC_EOP                       0x40000000
#define CPDMA_BUF_DESC_EOQ                       0x10000000
#define CPDMA_BUF_DESC_FROM_PORT                 0x70000
#define CPDMA_BUF_DESC_FROM_PORT_SHIFT           16
#define CPDMA_BUF_DESC_TO_PORT(port)             ((port << 16) | 0x100000)
#define CPDMA_BD_LEN_MASK                        0xFFFF
#define CPDMA_BD_PKTLEN_MASK                     0xFFFF

#define MAX_TRANSFER_UNIT                        1500
#define PBUF_LEN_MAX                             1520

#define MIN_PKT_LEN                              60

/* Define those to better describe the network interface. */
#define IFNAME0                                  'e'
#define IFNAME1                                  'n'

#define MASK_LOWER_4BITS_BYTE                    (0x0F)
#define MASK UPPER_4BITS_BYTE                    (0xF0)

#define MASK_BROADCAST_ADDR                      (0xFF)
#define MASK_MULTICAST_ADDR                      (0x01)

#define ALE_ENTRY_VLAN                           0x20
#define ALE_ENTRY_VLANUCAST                      0x30
#define ALE_ENTRY_UCAST                          0x10
#define ALE_ENTRY_MCAST                          0xD0
#define ALE_ENTRY_OUI                            (0x80)
#define ALE_ENTRY_ADDR                           (0x10)
#define ALE_ENTRY_VLAN_ADDR                      (0x30)
#define ALE_VLAN_ENTRY_MEMBER_LIST               0
#define ALE_VLAN_ENTRY_FRC_UNTAG_EGR             3
#define ALE_VLAN_ENTRY_MCAST_UNREG               (1)
#define ALE_VLAN_ENTRY_MCAST_REG                 (2)
#define ALE_VLAN_ENTRY_ID                        (3)
#define ALE_VLAN_ID_MASK                         (0x0FFF)
#define ALE_VLAN_ENTRY_ID_BIT0_BIT7              6
#define ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11        7
#define ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11_ALIGN  (0x08)
#define ALE_VLANUCAST_ENTRY_ID_BIT0_BIT7         6
#define ALE_VLANUCAST_ENTRY_TYPE_ID_BIT8_BIT11   7     
#define ALE_UCAST_ENTRY_TYPE                     7
#define ALE_UCAST_TYPE_MASK                      (0xC0)
#define ALE_UCAST_TYPE_SHIFT                     (6)
#define ALE_UCAST_TYPE_PERSISTANT                (0x00)
#define ALE_UCAST_TYPE_UNTOUCHED                 (0x40)
#define ALE_UCAST_TYPE_OUI                       (0x80)
#define ALE_UCAST_TYPE_TOUCHED                   (0xC0)
#define ALE_UCAST_ENTRY_DLR_PORT_BLK_SEC         8
#define ALE_UCAST_ENTRY_DLR_BLK_SEC_MASK         (0x03)
#define ALE_UCAST_ENTRY_PORT_SHIFT               2
#define ALE_MCAST_ENTRY_TYPE_FWD_STATE           7
#define ALE_MCAST_ENTRY_TYPE_FWD_STATE_SHIFT     (6)
#define ALE_MCAST_ENTRY_PORTMASK_SUP             8
#define ALE_MCAST_ENTRY_SUPER_MASK               (0x02)
#define ALE_MCAST_ENTRY_SUPER_SHIFT              (1)
#define ALE_MCAST_ENTRY_PORT_MASK                (0x1C)
#define ALE_MCAST_ENTRY_PORTMASK_SHIFT           2

#define SELECT_10_HALF                          (1 << 0)
#define SELECT_10_FULL                          (1 << 1)
#define SELECT_100_HALF                         (1 << 2)
#define SELECT_100_FULL                         (1 << 3)
#define SELECT_1000_HALF                        (1 << 4)
#define SELECT_1000_FULL                        (1 << 5)

#define SELECT_SPEED_10                         (0)
#define SELECT_SPEED_100                        (1)
#define SELECT_SPEED_1000                       (2)

#define SELECT_FORCED                           (0)
#define SELECT_AUTONEG                          (1)
#define SELECT_BOTH                             (2)

#define SELECT_HALF_DUPLEX                      (0)
#define SELECT_FULL_DUPLEX                      (1)

/* TX Buffer descriptor data structure */
struct cpdma_tx_bd {
  volatile struct cpdma_tx_bd *next;
  volatile u32_t bufptr;
  volatile u32_t bufoff_len;
  volatile u32_t flags_pktlen;
  
  /* helper to know which pbuf this tx bd corresponds to */
  volatile struct pbuf *pbuf;
}cpdma_tx_bd;

/* RX Buffer descriptor data structure */
struct cpdma_rx_bd {
  volatile struct cpdma_rx_bd *next;
  volatile u32_t bufptr;
  volatile u32_t bufoff_len;
  volatile u32_t flags_pktlen;

  /* helper to know which pbuf this rx bd corresponds to */
  volatile struct pbuf *pbuf;
}cpdma_rx_bd;

/**
 * Helper struct to hold the data used to operate on the receive 
 * buffer descriptor ring
 */
struct rxch {
  /* The head of the bd chain which can be allocated for reception*/
  volatile struct cpdma_rx_bd *free_head;

  /* The head of the bd chain which is receiving data */
  volatile struct cpdma_rx_bd *recv_head;

  /* The tail of the bd chain which is receiving data */
  volatile struct cpdma_rx_bd *recv_tail;

  /* The number of free bd's, which can be allocated for reception */
  volatile u32_t free_num;
}rxch;

/**
 * Helper struct to hold the data used to operate on the transmit 
 * buffer descriptor ring 
 */
struct txch {
  /* The bd which is free to send */
  volatile struct cpdma_tx_bd *free_head;
  
  /* The head of the bd chain, being sent */
  volatile struct cpdma_tx_bd *send_head;

  /* The tail of the bd chain, being sent */
  volatile struct cpdma_tx_bd *send_tail;

  /* The number of free bd's, which can be sent */
  volatile u32_t free_num;
}txch;

volatile struct cpdma_tx_bd *free_head;

/**
 * Slave port information
 */
struct cpswport{ 
  u32_t port_base;
  u32_t sliver_base;
  u32_t phy_addr;
  
  /* The PHY is capable of GitaBit or Not */
  u32_t phy_gbps;
}cpswport;

/** 
 * CPSW instance information 
 */
struct cpswinst{
  /* Base addresses */
  u32_t ss_base;
  u32_t mdio_base;
  u32_t wrpr_base;
  u32_t ale_base;
  u32_t cpdma_base;
  u32_t cppi_ram_base;
  u32_t host_port_base;

  /* Slave port information */ 
  struct cpswport port[MAX_SLAVEPORT_PER_INST];

  /* The tx/rx channels for the interface */
  struct txch txch;
  struct rxch rxch;
}cpswinst;

/* Defining set of CPSW base addresses for all the instances */
static struct cpswinst cpsw_inst_data[MAX_CPSW_INST];
 
/**
* Function to setup the instance parameters inside the interface
* @param  cpswif  The interface structure pointer
* @return None. 
*/
static void 
cpswif_inst_config(struct cpswportif *cpswif) {
  u32_t inst_num = cpswif->inst_num;
  struct cpswinst *cpswinst = &cpsw_inst_data[inst_num];

  /**
   * Code is added for only instance 0. If more instances
   * are there, assign base addresses and phy info here
   */
  if(0 == inst_num) {
    cpswinst->ss_base = CPSW0_SS_REGS;
    cpswinst->mdio_base = CPSW0_MDIO_REGS;
    cpswinst->wrpr_base = CPSW0_WR_REGS;
    cpswinst->cpdma_base = CPSW0_CPDMA_REGS;
    cpswinst->ale_base = CPSW0_ALE_REGS;
    cpswinst->cppi_ram_base = CPSW0_CPPI_RAM_REGS;
    cpswinst->host_port_base = CPSW0_PORT_0_REGS;
    cpswinst->port[PORT_1].port_base = CPSW0_PORT_1_REGS;
    cpswinst->port[PORT_1].sliver_base = CPSW0_SLIVER_1_REGS;
#ifdef CPSW0_PORT_1_PHY_ADDR
    cpswinst->port[PORT_1].phy_addr = CPSW0_PORT_1_PHY_ADDR;
    cpswinst->port[PORT_1].phy_gbps = CPSW0_PORT_1_PHY_GIGABIT;
#endif
    cpswinst->port[PORT_2].port_base = CPSW0_PORT_2_REGS;
    cpswinst->port[PORT_2].sliver_base = CPSW0_SLIVER_2_REGS;
#ifdef CPSW0_PORT_2_PHY_ADDR
    cpswinst->port[PORT_2].phy_addr = CPSW0_PORT_2_PHY_ADDR;
    cpswinst->port[PORT_2].phy_gbps = CPSW0_PORT_2_PHY_GIGABIT;
#endif
  }
}

/**
 * Gives the index of the ALE entry which is free
 * @param  cpswinst  The CPSW instance structure pointer
 *
 * @return index of the ALE entry which is free
 *         ERR_VAL if entry not found
 */
static err_t
cpswif_ale_entry_match_free(struct cpswinst *cpswinst) {
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS];
  s32_t idx;

  /* Check which ALE entry is free starting from 0th entry */
  for (idx = 0; idx < MAX_ALE_ENTRIES; idx++) {
    CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_entry);

    /* Break if the table entry is free */
    if (((*(((u8_t *)ale_entry) + ENTRY_TYPE_IDX))
         & ENTRY_TYPE) == ENTRY_FREE) {
       return idx;
    }
  }

  return ERR_VAL;
}

#ifdef CPSW_DUAL_MAC_MODE
/**
 * Sets the VLAN and VLAN/UCAST entries in ALE table for Dual Mac mode
 * @param cpswinst   The CPSW instance structure pointer
 * @param port_num   The slave port number
 * @param eth_addr   Ethernet address
 *
 * @return None
 */
static void
cpswif_port_to_host_vlan_cfg(struct cpswinst *cpswinst, u32_t port_num,
                             u8_t *eth_addr)
{
  s32_t idx;
  u32_t cnt;
  u32_t ale_v_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};
  u32_t ale_vu_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_free(cpswinst);

  if(MAX_ALE_ENTRIES == idx) {
    return;
  }

  /* Set up the VLAN Entry */
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_MEMBER_LIST) = 
                                   HOST_PORT_MASK | SLAVE_PORT_MASK(port_num); 

  /**
   * Set the bit fields for entry type and VLAN ID. Set the port
   * number as VLAN ID. So only lsb 2 bits of VLAN_ID field will be used.
   */
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_ID_BIT0_BIT7) = port_num;
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11) = ALE_ENTRY_VLAN;

  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_FRC_UNTAG_EGR) = 
                                   HOST_PORT_MASK | SLAVE_PORT_MASK(port_num); 
 
  /* Set the VLAN entry in the ALE table */ 
  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_v_entry);

  idx = cpswif_ale_entry_match_free(cpswinst);

  if(MAX_ALE_ENTRIES == idx) {
    return;
  }

  /* Set up the VLAN/Unicast Entry */
  for(cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
    *(((u8_t *)ale_vu_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
  }

  *(((u8_t *)ale_vu_entry) + ALE_VLANUCAST_ENTRY_TYPE_ID_BIT8_BIT11) = 
                                                           ALE_ENTRY_VLANUCAST;
  *(((u8_t *)ale_vu_entry) + ALE_VLANUCAST_ENTRY_ID_BIT0_BIT7) = port_num;

  /* Set the VLAN/Unicast entry in the ALE table */
  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_vu_entry);
}

#else /* CPSW_DUAL_MAC_MODE */

/**
 * Sets a unicast entry in the ALE table.
 * @param cpswinst   The CPSW instance structure pointer
 * @param port_num   The slave port number
 * @param eth_addr   Ethernet address
 *
 * @return None
 */
static void
cpswif_ale_unicastentry_set(struct cpswinst *cpswinst, u32_t port_num,
                            u8_t *eth_addr) {
  volatile u32_t cnt;
  volatile s32_t idx;
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  for(cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
    *(((u8_t *)ale_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
  }

  *(((u8_t *)ale_entry) + ALE_UCAST_ENTRY_TYPE) = ALE_ENTRY_UCAST;
  *(((u8_t *)ale_entry) + ALE_UCAST_ENTRY_DLR_PORT_BLK_SEC) =
                                   (port_num << ALE_UCAST_ENTRY_PORT_SHIFT);

  idx = cpswif_ale_entry_match_free(cpswinst);

  if (idx < MAX_ALE_ENTRIES ) {
    CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_entry);
  }
}

/**
 * Sets a multicast entry in the ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param portmask   The port mask for the port number
 * @param eth_addr   Ethernet Address
 *
 * @return index of the ALE entry added
 *         ERR_VAL if table entry is not free
 */
static void
cpswif_ale_multicastentry_set(struct cpswinst *cpswinst, u32_t portmask,
                              u8_t *eth_addr)
{
  volatile u32_t cnt;
  volatile s32_t idx;
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_free(cpswinst);
  if (idx < MAX_ALE_ENTRIES ) {
    for (cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
      *(((u8_t *)ale_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
    }

    *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_TYPE_FWD_STATE) = ALE_ENTRY_MCAST;
    *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) |=
                                (portmask << ALE_MCAST_ENTRY_PORTMASK_SHIFT);

    CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_entry);
  }
}
#endif /* CPSW_DUAL_MAC_MODE */

#ifdef CPSW_SWITCH_CONFIG
/**
 * Checks the address is value for given type
 *
 * @param   eth_addr   Ethernet Address
 * @param   addr_type  Type of address (Unicast, Multicast, Broadcast)
 *
 * @return  the status
 */
static u32_t
check_valid_addr(u8_t *eth_addr, u32_t addr_type) {
  u32_t cnt = 0;

  if (!addr_type)
    return TRUE;

  for (cnt = 0; cnt < LEN_MAC_ADDRESS; cnt++)
    if ((eth_addr[cnt] & MASK_BROADCAST_ADDR) != MASK_BROADCAST_ADDR)
      break;

  if ((cnt == LEN_MAC_ADDRESS) && (addr_type == ADDR_TYPE_BROADCAST))
    return TRUE;
  else if (cnt == LEN_MAC_ADDRESS)
    return FALSE;
  else if (addr_type == ADDR_TYPE_BROADCAST)
    return FALSE;

  if (addr_type == ADDR_TYPE_MULTICAST) {
    if ((eth_addr[0] & MASK_MULTICAST_ADDR) == MASK_MULTICAST_ADDR)
      return TRUE;
  } else if (addr_type == ADDR_TYPE_UNICAST) {
    if ((eth_addr[0] & MASK_MULTICAST_ADDR) != MASK_MULTICAST_ADDR)
      return TRUE;
  }

  return FALSE;
}

/**
 * Gives the index of the ALE entry which is untouched ageable
 * @param  cpswinst  The CPSW instance structure pointer
 *
 * @return index of the ALE entry which is free
 *         ERR_VAL if entry not found
 */
static err_t
cpswif_ale_entry_match_ageable(struct cpswinst *cpswinst) {
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS];
  u32_t type;
  s32_t idx;

  /* Check which ALE entry is free starting from 0th entry */
  for (idx = 0; idx < MAX_ALE_ENTRIES; idx++) {
    CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_entry);

    type = *(((u8_t *)ale_entry) + ENTRY_TYPE_IDX) & ENTRY_TYPE;

    /* Goto next entry if the ale entry is not valid address */
    if ((type != ALE_ENTRY_ADDR) && (type != ALE_ENTRY_VLAN_ADDR))
      continue;

    if (check_valid_addr((u8_t *)ale_entry, ADDR_TYPE_MULTICAST))
      continue;

    type = *(((u8_t *)ale_entry) + ALE_UCAST_ENTRY_TYPE) & ALE_UCAST_TYPE_MASK;

    if ((type != ALE_UCAST_TYPE_PERSISTANT) && (type != ALE_UCAST_TYPE_OUI))
       return idx;
    }

  return ERR_VAL;
}

/**
 * Configure the rate limit for packets transmit of ports
 * @param  cpswinst    The CPSW instance
 * @param  enable      Enable Rate Limit
 * @param  direction   Select TX or RX mode
 * @param  port_num    Port Number
 * @param  addr_type   Type of Address (Broadcast or Multicast)
 * @param  limit       Vale of rate limit to be set
 *
 * @return  None
 *
 **/
static void
cpswif_rate_limit(struct cpswinst *cpswinst, u32_t enable, u32_t direction,
                  u32_t port_num, u32_t addr_type, u32_t limit) {
  if (!enable) {
    CPSWALERateLimitDisable(cpswinst->ale_base);
  }

  if (addr_type == ADDR_TYPE_BROADCAST) {
    CPSWALEBroadcastRateLimitSet(cpswinst->ale_base, port_num, limit);
  } else if (addr_type == ADDR_TYPE_MULTICAST) {
    CPSWALEMulticastRateLimitSet(cpswinst->ale_base, port_num, limit);
  }

  if (port_num == 0) {
    if (direction) {
      CPSWALERateLimitTXMode(cpswinst->ale_base);
    } else {
      CPSWALERateLimitRXMode(cpswinst->ale_base);
    }
  } else {
    if (direction) {
      CPSWALERateLimitRXMode(cpswinst->ale_base);
    } else {
      CPSWALERateLimitTXMode(cpswinst->ale_base);
    }
  }

  CPSWALERateLimitEnable(cpswinst->ale_base);
}

/**
 * Gives the index of the ALE entry which match address of VLAN
 * @param  cpswinst  The CPSW instance structure pointer
 * @param  eth_addr  Ethernet address
 * @param  vid       VLAN ID
 *
 * @return index of the ALE entry which match address of VLAN
 *         ERR_VAL if entry not found
 */
static err_t
cpswif_ale_entry_match_addr(struct cpswinst *cpswinst, u8_t *eth_addr,
                            u32_t vid) {
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS];
  u32_t type, cnt;
  s32_t idx;

  /* Check which ALE entry is free starting from 0th entry */
  for (idx = 0; idx < MAX_ALE_ENTRIES; idx++) {
    CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_entry);

    type = *(((u8_t *)ale_entry) + ENTRY_TYPE_IDX) & ENTRY_TYPE;

    /* Goto next entry if the ale entry is not valid address */
    if ((type != ALE_ENTRY_ADDR) && (type != ALE_ENTRY_VLAN_ADDR))
      continue;

    if ((*(((u16_t *)ale_entry) + ALE_VLAN_ENTRY_ID) & ALE_VLAN_ID_MASK) != vid)
      continue;

    for (cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
      if (*(((u8_t *)ale_entry) + cnt) != eth_addr[ETHARP_HWADDR_LEN - cnt -1])
        break;

      if (ETHARP_HWADDR_LEN == (cnt + 1))
        return idx;
    }
  }

  return ERR_VAL;
}

/**
 * Gives the index of the ALE entry which match vlan
 * @param  cpswinst  The CPSW instance structure pointer
 * @param  vid  VLAN ID
 *
 * @return index of the ALE entry which match vlan
 *         ERR_VAL if entry not found
 */
static err_t
cpswif_ale_entry_match_vlan(struct cpswinst *cpswinst, u32_t vid) {
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS];
  u32_t type;
  s32_t idx;

  /* Check which ALE entry is free starting from 0th entry */
  for (idx = 0; idx < MAX_ALE_ENTRIES; idx++) {
    CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_entry);

    type = *(((u8_t *)ale_entry) + ENTRY_TYPE_IDX) & ENTRY_TYPE;

    /* Goto next entry if the ale entry is not valid vlan */
    if (type != ALE_ENTRY_VLAN)
      continue;

    if ((*(((u16_t *)ale_entry) + ALE_VLAN_ENTRY_ID) & ALE_VLAN_ID_MASK) == vid)
      return idx;
  }

  return ERR_VAL;
}

/**
 * Adds an unicast entry in the ALE table.
 * @param cpswinst   The CPSW instance structure pointer
 * @param port_num   The slave port number
 * @param eth_addr   Ethernet address
 * @param flags      Flags Settings
 *                   0x1 - Secure
 *                   0x2 - Block
 *
 * @return index of the ALE entry added
 *         ERR_VAL if table entry is not free
 */
static err_t
cpswif_ale_unicastentry_add(struct cpswinst *cpswinst, u32_t port_num,
                            u8_t *eth_addr, u32_t flags, u32_t ucast_type) {
  volatile u32_t cnt;
  volatile s32_t idx;
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, 0);

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_free(cpswinst);

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_ageable(cpswinst);

  if (ERR_VAL == idx)
    return ERR_VAL;

  for(cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
    *(((u8_t *)ale_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
  }

  *(((u8_t *)ale_entry) + ALE_UCAST_ENTRY_TYPE) = ALE_ENTRY_ADDR |
                                           (ucast_type << ALE_UCAST_TYPE_SHIFT);
  *(((u8_t *)ale_entry) + ALE_UCAST_ENTRY_DLR_PORT_BLK_SEC) =
                                  (port_num << ALE_UCAST_ENTRY_PORT_SHIFT) |
                                   (flags & ALE_UCAST_ENTRY_DLR_BLK_SEC_MASK);

  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_entry);

  return idx;
}

/**
 * Adds an OUI entry in the ALE table.
 * @param cpswinst   The CPSW instance structure pointer
 * @param eth_addr   Ethernet address
 *
 * @return index of the ALE entry added
 *         ERR_VAL if table entry is not free
 */
static err_t
cpswif_ale_OUI_add(struct cpswinst *cpswinst, u8_t *eth_addr) {
  volatile u32_t cnt;
  volatile s32_t idx;
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, 0);

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_free(cpswinst);

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_ageable(cpswinst);

  if (ERR_VAL == idx)
    return ERR_VAL;

  for(cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
    *(((u8_t *)ale_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
  }

  *(((u8_t *)ale_entry) + ALE_UCAST_ENTRY_TYPE) = ALE_ENTRY_ADDR | ALE_ENTRY_OUI;

  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_entry);

  return idx;
}

/**
 * Deletes an unicast entry in the ALE table.
 * @param cpswinst   The CPSW instance structure pointer
 * @param port_num   The slave port number
 * @param eth_addr   Ethernet address
 *
 * @return index of the ALE entry deleted
 *         ERR_VAL if table entry is not present
 */
static err_t
cpswif_ale_unicastentry_del(struct cpswinst *cpswinst, u32_t port_num,
                            u8_t *eth_addr) {
  volatile s32_t idx;
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  *(((u8_t *)ale_entry) + ALE_UCAST_ENTRY_TYPE) = ENTRY_FREE;

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, 0);

  if (ERR_VAL == idx)
    return ERR_VAL;

  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_entry);

  return idx;
}

/**
 * Adds a multicast entry in the ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param portmask   The port mask for the port number
 * @param eth_addr   Ethernet Address
 * @param super      Supervisory Packet
 * @param mcast_st   Multicast Forward State
 *
 * @return index of the ALE entry added
 *         ERR_VAL if table entry is not free
 */
static err_t
cpswif_ale_multicastentry_add(struct cpswinst *cpswinst, u32_t portmask,
                              u8_t *eth_addr, u32_t super, u32_t mcast_st) {
  volatile s32_t idx;
  volatile u32_t cnt;
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, 0);

  if (ERR_VAL == idx) {
    idx = cpswif_ale_entry_match_free(cpswinst);
  } else {
    /* Get the entry in the ALE table */
    CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_entry);
  }

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_ageable(cpswinst);

  if (ERR_VAL == idx)
    return ERR_VAL;

  for (cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
    *(((u8_t *)ale_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
  }

  portmask |= (*(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) &
                                        ALE_MCAST_ENTRY_PORT_MASK);

  *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_TYPE_FWD_STATE) =
                          (ALE_ENTRY_ADDR |
                           (mcast_st << ALE_MCAST_ENTRY_TYPE_FWD_STATE_SHIFT));
  *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) &=
                           ~(PORT_MASK << ALE_MCAST_ENTRY_PORTMASK_SHIFT);
  *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) |=
                           (portmask << ALE_MCAST_ENTRY_PORTMASK_SHIFT) |
                            ((super << ALE_MCAST_ENTRY_SUPER_SHIFT) &
                             ALE_MCAST_ENTRY_SUPER_MASK);

  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_entry);

  return idx;
}

/**
 * Deletes a multicast entry in the ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param portmask   The port mask for the port number
 * @param eth_addr   Ethernet Address
 *
 * @return index of the ALE entry deleted
 *         ERR_VAL if table entry is not present
 */
static err_t
cpswif_ale_multicastentry_del(struct cpswinst *cpswinst, u32_t portmask,
                              u8_t *eth_addr) {
  volatile s32_t idx;
  u32_t ale_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, 0);

  if (ERR_VAL == idx)
    return ERR_VAL;

  CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_entry);

  if (portmask) {
    *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) &=
                             ~(PORT_MASK << ALE_MCAST_ENTRY_PORTMASK_SHIFT);
    *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) =
                             (portmask << ALE_MCAST_ENTRY_PORTMASK_SHIFT);
  } else {
    *(((u8_t *)ale_entry) + ALE_MCAST_ENTRY_TYPE_FWD_STATE) = ENTRY_FREE;
  }

  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_entry);

  return idx;
}

/**
 * Adds the VLAN entry in ALE table
 * @param cpswinst    The CPSW instance structure pointer
 * @param vid         VLAN ID
 * @param port_num    The slave port number
 * @param untag       The force untagged egress
 * @param reg_mcast   The registered MCAST Flood Mask
 * @param unreg_mcast The unregistered MCAST Flood Mask
 *
 * @return index of the ALE entry added
 *         ERR_VAL if table entry is not free
 */
static err_t
cpswif_ale_vlan_add(struct cpswinst *cpswinst, u32_t vid, u32_t port_num,
                             u32_t untag, u32_t reg_mcast, u32_t unreg_mcast) {
  s32_t idx;
  u32_t ale_v_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_vlan(cpswinst, vid);

  if (ERR_VAL == idx) {
    idx = cpswif_ale_entry_match_free(cpswinst);
  } else {
    /* Get the entry in the ALE table */
    CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_v_entry);
  }

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_ageable(cpswinst);

  if (ERR_VAL == idx)
    return ERR_VAL;

  /**
   * Set the bit fields for entry type and VLAN ID.
   */
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_ID_BIT0_BIT7) = vid;
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11) =
                            ((vid >> ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11_ALIGN) &
                              MASK_LOWER_4BITS_BYTE) | ALE_ENTRY_VLAN;
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_FRC_UNTAG_EGR) = untag;
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_MCAST_UNREG) = unreg_mcast;
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_MCAST_REG) = reg_mcast;
  *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_MEMBER_LIST) |=
                                   PORT_MASK & INDV_PORT_MASK(port_num);

  /* Set the VLAN entry in the ALE table */
  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_v_entry);

  return idx;
}

/**
 * Dlelete the VLAN entry in ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param vid        VLAN ID
 * @param port_num   The slave port number
 *
 * @return index of the ALE entry deleted
 *         ERR_VAL if table entry is not present
 */
static err_t
cpswif_ale_vlan_del(struct cpswinst *cpswinst, u32_t vid, u32_t port_num) {
  s32_t idx;
  u32_t mask;
  u32_t ale_v_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_vlan(cpswinst, vid);

  if (ERR_VAL == idx)
    return ERR_VAL;

  CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_v_entry);

  /* Set up the VLAN Entry */
  mask = *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_MEMBER_LIST) | PORT_MASK;
  mask &= INDV_PORT_MASK(port_num);

  if (0 == mask)
    return ERR_VAL;

  if (1 == mask) {
      *(((u8_t *)ale_v_entry) + ALE_MCAST_ENTRY_TYPE_FWD_STATE) = ENTRY_FREE;
  } else {
    /* Set up the VLAN Entry */
    *(((u8_t *)ale_v_entry) + ALE_VLAN_ENTRY_MEMBER_LIST) &=
                              ~INDV_PORT_MASK(port_num);
  }

  /* Set the VLAN/Unicast entry in the ALE table */
  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_v_entry);

  return idx;
}

/**
 * Add the VLAN/UCAST entries in ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param vid        VLAN ID
 * @param port_num   The slave port number
 * @param eth_addr   Ethernet address
 * @param flags      Flags Settings
 *                   0x1 - Secure
 *                   0x2 - Block
 *
 * @return index of the ALE entry added
 *         ERR_VAL if table entry is not free
 */
static err_t
cpswif_ale_vlan_add_ucast(struct cpswinst *cpswinst, u32_t vid, u32_t port_num,
                             u8_t *eth_addr, u32_t flags, u32_t ucast_type) {
  s32_t idx;
  u32_t cnt;
  u32_t ale_vu_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, vid);

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_free(cpswinst);

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_ageable(cpswinst);

  if (ERR_VAL == idx)
    return ERR_VAL;

  /**
   * Set the bit fields for entry type and VLAN ID.
   */
  *(((u8_t *)ale_vu_entry) + ALE_VLAN_ENTRY_ID_BIT0_BIT7) = vid;
  *(((u8_t *)ale_vu_entry) + ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11) =
                            ((vid >> ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11_ALIGN) &
                              MASK_LOWER_4BITS_BYTE) | ALE_ENTRY_VLAN_ADDR |
                              (ucast_type << ALE_UCAST_TYPE_SHIFT);

  for (cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
    *(((u8_t *)ale_vu_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
  }

  *(((u8_t *)ale_vu_entry) + ALE_UCAST_ENTRY_DLR_PORT_BLK_SEC) =
                                  (port_num << ALE_UCAST_ENTRY_PORT_SHIFT) |
                                   (flags & ALE_UCAST_ENTRY_DLR_BLK_SEC_MASK);

  /* Set the VLAN entry in the ALE table */
  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_vu_entry);

  return idx;
}

/**
 * Dlelete the VLAN/UCAST entry in ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param vid        VLAN ID
 * @param port_num   The slave port number
 *
 * @return index of the ALE entry deleted
 *         ERR_VAL if table entry is not present
 */
static err_t
cpswif_ale_vlan_del_ucast(struct cpswinst *cpswinst, u32_t vid, u32_t port_num,
                             u8_t *eth_addr) {
  volatile s32_t idx;
  u32_t ale_vu_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  *(((u8_t *)ale_vu_entry) + ALE_UCAST_ENTRY_TYPE) = ENTRY_FREE;

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, vid);

  if (ERR_VAL == idx)
    return ERR_VAL;

  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_vu_entry);

  return idx;
}

/**
 * Add the VLAN/MCAST entries in ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param vid        VLAN ID
 * @param port_num   The slave port number
 * @param eth_addr   Ethernet address
 * @param super      Supervisory Packet
 * @param mcast_st   Multicast Forward State
 *
 * @return index of the ALE entry added
 *         ERR_VAL if table entry is not free
 */
static err_t
cpswif_ale_vlan_add_mcast(struct cpswinst *cpswinst, u32_t vid, u32_t portmask,
                             u8_t *eth_addr, u32_t super, u32_t mcast_st) {
  s32_t idx;
  u32_t cnt;
  u32_t ale_vm_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, vid);

  if (ERR_VAL == idx) {
    idx = cpswif_ale_entry_match_free(cpswinst);
  } else {
    /* Get the entry in the ALE table */
    CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_vm_entry);
  }

  if (ERR_VAL == idx)
    idx = cpswif_ale_entry_match_ageable(cpswinst);

  if (ERR_VAL == idx)
    return ERR_VAL;

  /**
   * Set the bit fields for entry type and VLAN ID.
   */
  *(((u8_t *)ale_vm_entry) + ALE_VLAN_ENTRY_ID_BIT0_BIT7) = vid;
  *(((u8_t *)ale_vm_entry) + ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11) =
                            ((vid >> ALE_VLAN_ENTRY_TYPE_ID_BIT8_BIT11_ALIGN) &
                              MASK_LOWER_4BITS_BYTE);

  for (cnt = 0; cnt < ETHARP_HWADDR_LEN; cnt++) {
    *(((u8_t *)ale_vm_entry) + cnt) = eth_addr[ETHARP_HWADDR_LEN - cnt -1];
  }

  portmask |= (*(((u8_t *)ale_vm_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) &
                                           ALE_MCAST_ENTRY_PORT_MASK);

  *(((u8_t *)ale_vm_entry) + ALE_MCAST_ENTRY_TYPE_FWD_STATE) |=
                          (ALE_ENTRY_VLAN_ADDR |
                           (mcast_st << ALE_MCAST_ENTRY_TYPE_FWD_STATE_SHIFT));
  *(((u8_t *)ale_vm_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) &=
                              ~(PORT_MASK << ALE_MCAST_ENTRY_PORTMASK_SHIFT);
  *(((u8_t *)ale_vm_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) |=
                             (portmask << ALE_MCAST_ENTRY_PORTMASK_SHIFT) |
                              ((super << ALE_MCAST_ENTRY_SUPER_SHIFT) &
                               ALE_MCAST_ENTRY_SUPER_MASK);

  /* Set the VLAN entry in the ALE table */
  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_vm_entry);

  return idx;
}

/**
 * Deletes a vlan multicast entry in the ALE table
 * @param cpswinst   The CPSW instance structure pointer
 * @param vid        VLAN ID
 * @param portmask   The port mask for the port number
 * @param eth_addr   Ethernet Address
 *
 * @return index of the ALE entry deleted
 *         ERR_VAL if table entry is not present
 */
static err_t
cpswif_ale_vlan_del_mcast(struct cpswinst *cpswinst, u32_t vid, u32_t portmask,
                              u8_t *eth_addr) {
  volatile s32_t idx;
  u32_t ale_vm_entry[ALE_ENTRY_NUM_WORDS] = {0, 0, 0};

  idx = cpswif_ale_entry_match_addr(cpswinst, eth_addr, vid);

  if (ERR_VAL == idx)
    return ERR_VAL;

  CPSWALETableEntryGet(cpswinst->ale_base, idx, ale_vm_entry);

  if (portmask) {
    *(((u8_t *)ale_vm_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) &=
                                ~(PORT_MASK << ALE_MCAST_ENTRY_PORTMASK_SHIFT);
    *(((u8_t *)ale_vm_entry) + ALE_MCAST_ENTRY_PORTMASK_SUP) =
                                (portmask << ALE_MCAST_ENTRY_PORTMASK_SHIFT);
  } else {
    *(((u8_t *)ale_vm_entry) + ALE_MCAST_ENTRY_TYPE_FWD_STATE) = ENTRY_FREE;
  }

  CPSWALETableEntrySet(cpswinst->ale_base, idx, ale_vm_entry);

  return idx;
}

#endif  /* CPSW_SWITCH_CONFIG */

/**
 * AutoNegotiates with phy for link, set it in silver and check for link status.
 * @param  cpswinst   The CPSW instance structure pointer
 * @param  port_num    The slave port number
 * @param  adv         Configuration for advertisement
 *                     SELECT_10_HALF - 10Base Half Duplex
 *                     SELECT_10_FULL - 10Base Full Duplex
 *                     SELECT_100_HALF - 100Base Half Duplex
 *                     SELECT_100_FULL - 100Base Full Duplex
 *                     SELECT_1000_HALF - 1000Base Half Duplex
 *                     SELECT_1000_FULL - 1000Base Full Duplex
 * @return ERR_OK      If link set up is successful
 *                     others if not successful
 */
static err_t
cpswif_phy_autoneg(struct cpswinst *cpswinst, u32_t port_num, u32_t adv) {
  err_t linkstat = ERR_CONN;
  u16_t adv_val = 0, partnr_ablty = 0, gbps_partnr_ablty = 0, gig_adv_val = 0;
  u32_t aut_neg_cnt = 200, auto_stat, transfer_mode = 0;

  /* Check if ethernet PHY is present or not */
  if (0 == (MDIOPhyAliveStatusGet(cpswinst->mdio_base)
            & (1 << cpswinst->port[port_num - 1].phy_addr))) {
    LWIP_PRINTF("\n\rNo PHY found at addr %d for Port %d of Instance %d.",
                cpswinst->port[port_num - 1].phy_addr,
                port_num, 0);
    return linkstat;
  }

  LWIP_PRINTF("\n\rPHY found at address %d for  Port %d of Instance %d.",
              cpswinst->port[port_num - 1].phy_addr,
              port_num, 0);

  if (SELECT_1000_HALF == adv) {
    LWIP_PRINTF("\n\rCPSW doesnot support Half Duplex for Gigabyte...");
    return linkstat;
  }

  /* We advertise for 10/100 Mbps both half and full duplex */
  if (adv & SELECT_10_HALF)
    adv_val |= PHY_10BT;
  if (adv & SELECT_10_FULL)
    adv_val |= PHY_10BT_FD;
  if (adv & SELECT_100_HALF)
    adv_val |= PHY_100BTX;
  if (adv & SELECT_100_FULL)
    adv_val |= PHY_100BTX_FD;

  gig_adv_val = 0;
  partnr_ablty = TRUE;
  gbps_partnr_ablty = FALSE;

  /**
   * Not all the PHYs can operate at 1000 Mbps. So advertise only
   * if the PHY is capable
   */
  if (cpswinst->port[port_num -1].phy_gbps) {
    LWIP_PRINTF("\n\rPhy supports Gigabyte...");
    if (adv & SELECT_1000_FULL) {
      gig_adv_val = PHY_1000BT_FD;
      partnr_ablty = TRUE;
      gbps_partnr_ablty = TRUE;
    }
    if (adv & SELECT_1000_HALF) {
      LWIP_PRINTF("\n\rCPSW doesnot support Half Duplex for Gigabyte...");
    }
  } else {
    LWIP_PRINTF("\n\rPhy doesnot support Gigabyte...");
  }

  LWIP_PRINTF("\n\rPerforming Auto-Negotiation...");

  /**
   * Now start Autonegotiation. PHY will talk to its partner
   * and give us what the partner can handle
   */
  if (PhyAutoNegotiate(cpswinst->mdio_base,
                       cpswinst->port[port_num -1].phy_addr,
                       &adv_val, &gig_adv_val) == TRUE) {
    while (aut_neg_cnt) {
      delay(50);
      auto_stat = PhyAutoNegStatusGet(cpswinst->mdio_base,
                                      cpswinst->port[port_num -1].phy_addr);
      if (TRUE == auto_stat) {
        break;
      }
      aut_neg_cnt--;
    }

    if (0 != aut_neg_cnt) {
      linkstat = ERR_OK;
      LWIP_PRINTF("\n\rAuto-Negotiation Successful.");
    } else {
      LWIP_PRINTF("\n\rAuto-Negotiation Not Successful.");
      return ERR_CONN;
    }

    /* Get what the partner supports */
    PhyPartnerAbilityGet(cpswinst->mdio_base,
                         cpswinst->port[port_num -1].phy_addr,
                         &partnr_ablty, &gbps_partnr_ablty);
    if (gbps_partnr_ablty & PHY_LINK_PARTNER_1000BT_FD) {
      LWIP_PRINTF("\n\rTransfer Mode : 1000 Mbps.");
      transfer_mode = CPSW_SLIVER_GIG_FULL_DUPLEX;
    } else {
      if ((adv_val & partnr_ablty) & PHY_100BTX_FD) {
        LWIP_PRINTF("\n\rTransfer Mode : 100 Mbps Full Duplex.");
        transfer_mode = CPSW_SLIVER_NON_GIG_FULL_DUPLEX;
      } else if ((adv_val & partnr_ablty) & PHY_100BTX) {
        LWIP_PRINTF("\n\rTransfer Mode : 100 Mbps Half Duplex.");
        transfer_mode = CPSW_SLIVER_NON_GIG_HALF_DUPLEX;
      } else if ((adv_val & partnr_ablty) & PHY_10BT_FD) {
        LWIP_PRINTF("\n\rTransfer Mode : 10 Mbps Full Duplex.");
        transfer_mode = CPSW_SLIVER_INBAND | CPSW_SLIVER_NON_GIG_FULL_DUPLEX;
      } else if ((adv_val & partnr_ablty) & PHY_10BT) {
        LWIP_PRINTF("\n\rTransfer Mode : 10 Mbps Half Duplex.");
        transfer_mode = CPSW_SLIVER_INBAND | CPSW_SLIVER_NON_GIG_HALF_DUPLEX;
      } else {
        LWIP_PRINTF("\n\rNo Valid Transfer Mode is detected.");
      }
    }
  } else {
    LWIP_PRINTF("\n\rAuto-Negotiation Not Successful.");
    linkstat = ERR_CONN;
  }

  /**
   * Set the Sliver with the negotiation results if autonegotiation
   * is successful
   */
  if (linkstat == ERR_OK) {
    CPSWSlTransferModeSet(cpswinst->port[port_num - 1].sliver_base,
                          transfer_mode);
  }

  /* Check if PHY link is there or not */
  if (FALSE == ((PhyLinkStatusGet(cpswinst->mdio_base,
                cpswinst->port[port_num - 1].phy_addr, 1000)))) {
    LWIP_PRINTF("\n\rPHY link connectivity failed for Port %d of Inst %d.",
                port_num, 0);
    return linkstat;
  }

  LWIP_PRINTF("\n\rPHY link verified for Port %d of Instance %d.",
              port_num, 0);

  CPSWSlRGMIIEnable(
                  cpswinst->port[port_num - 1].sliver_base);

  return linkstat;
}

/**
 * Manually configure phy, set it in silver and check for link status.
 * @param  cpswinst   The CPSW instance structure pointer
 * @param  port_num    The slave port number
 * @param  speed       Configuration for speed
 *                     SELECT_SPEED_1000 - 1000 Mbps
 *                     SELECT_SPEED_100 - 100 Mbps
 *                     SELECT_SPEED_10 - 10 Mbps
 * @param  duplex      Configuration for duplex
 *                     SELECT_HALF_DUPLEX - Half Duplex
 *                     SELECT_FULL_DUPLEX - Full Duplex
 * @return ERR_OK      If link set up is successful
 *                     others if not successful
 */
static err_t
cpswif_phy_forced(struct cpswinst *cpswinst, u32_t port_num, u32_t speed,
                  u32_t duplex) {
  err_t linkstat = ERR_CONN;
  u16_t speed_val = 0, duplex_val = 0;
  u32_t frc_stat_cnt = 200, frc_stat = FALSE, transfer_mode = 0;

  /* Check if ethernet PHY is present or not */
  if (0 == (MDIOPhyAliveStatusGet(cpswinst->mdio_base)
            & (1 << cpswinst->port[port_num - 1].phy_addr))){
    LWIP_PRINTF("\n\rNo PHY found at addr %d for Port %d of Instance %d.",
                cpswinst->port[port_num - 1].phy_addr,
                port_num, 0);
    return linkstat;
  }

  LWIP_PRINTF("\n\rPHY found at address %d for  Port %d of Instance %d.",
              cpswinst->port[port_num - 1].phy_addr,
              port_num, 0);

  /* configure control for speed and duples */
  if (SELECT_SPEED_1000 == speed)
    speed_val = PHY_SPEED_1000MBPS;
  else if (SELECT_SPEED_100 == speed)
    speed_val = PHY_SPEED_100MBPS;

  if (TRUE == duplex)
    duplex_val = PHY_FULL_DUPLEX;

  if (SELECT_SPEED_1000 == speed) {
    LWIP_PRINTF("\n\rManual Configuration not allowed for Gigabyte...");
    return linkstat;
  }

  if (FALSE == PhyReset(cpswinst->mdio_base,
                        cpswinst->port[port_num - 1].phy_addr)) {
    LWIP_PRINTF("\n\rPHY Reset Failed...");
    return linkstat;
  }

  if (TRUE == (PhyLinkStatusGet(cpswinst->mdio_base,
               cpswinst->port[port_num - 1].phy_addr, 1000))) {
   while (frc_stat_cnt) {
      delay(50);
      /* Check if PHY link is there or not */
      frc_stat = (PhyLinkStatusGet(cpswinst->mdio_base,
                  cpswinst->port[port_num - 1].phy_addr, 1000));

      if (TRUE == frc_stat) {
        LWIP_PRINTF("\n\rPHY Link is Down.");
        break;
      }
      frc_stat_cnt--;
    }
  }

  LWIP_PRINTF("\n\rPerforming Manual Configuration...");

  frc_stat_cnt = 200;
  frc_stat = FALSE;

  if (PhyConfigure(cpswinst->mdio_base, cpswinst->port[port_num -1].phy_addr,
                   speed_val, duplex_val)) {
    while (frc_stat_cnt) {
      delay(50);
      frc_stat = PhyLinkStatusGet(cpswinst->mdio_base,
                           cpswinst->port[port_num - 1].phy_addr, 1000);

      if (1 == frc_stat) {
        break;
      }
      frc_stat_cnt--;
    }

    if (0 != frc_stat_cnt) {
      linkstat = ERR_OK;
      LWIP_PRINTF("\n\rPhy Configuration Successful.");
      LWIP_PRINTF("\n\rPHY link verified for Port %d of Instance %d.",
                  port_num, 0);
    } else {
      LWIP_PRINTF("\n\rPhy Configuration Successful.");
      LWIP_PRINTF("\n\rPHY link connectivity failed for Port %d of Inst %d.",
                  port_num, 0);
      return ERR_CONN;
    }

    if (SELECT_SPEED_1000 == speed) {
      LWIP_PRINTF("\n\rTransfer Mode : 1000 Mbps.");
      transfer_mode = CPSW_SLIVER_GIG_FULL_DUPLEX;
    } else {
      if (SELECT_SPEED_10 == speed) {
        LWIP_PRINTF("\n\rTransfer Mode : 10 Mbps ");
        transfer_mode = CPSW_SLIVER_INBAND;
      } else {
        LWIP_PRINTF("\n\rTransfer Mode : 100 Mbps ");
      }
      if (TRUE == duplex) {
        LWIP_PRINTF("Full Duplex.");
        transfer_mode |= CPSW_SLIVER_NON_GIG_FULL_DUPLEX;
      } else {
        LWIP_PRINTF("Half Duplex.");
        transfer_mode |= CPSW_SLIVER_NON_GIG_HALF_DUPLEX;
      }
    }
  } else {
    LWIP_PRINTF("\n\rPhy Configuration Not Successful.");
    LWIP_PRINTF("\n\rPHY link connectivity failed for Port %d of Inst %d.",
                port_num, 0);
    linkstat = ERR_CONN;
  }

  /**
   * Set the Sliver with the forced phy configuration
   */
  CPSWSlTransferModeSet(cpswinst->port[port_num - 1].sliver_base,
                        transfer_mode);

  CPSWSlRGMIIEnable(cpswinst->port[port_num - 1].sliver_base);

  return linkstat;
}

/**
* Function to setup the link. AutoNegotiates with the phy for link
* setup and set the CPSW with the result of autonegotiation.
* @param  cpswportif  The cpsw port interface structure pointer
* @return ERR_OK      If link set up is successful
*                     others if not successful
*/
static err_t
cpswif_autoneg_config(u32_t inst_num, u32_t port_num) {
  struct cpswinst *cpswinst = &cpsw_inst_data[inst_num];
  err_t linkstat = ERR_CONN;
  u16_t adv_val, partnr_ablty, gbps_partnr_ablty, gig_adv_val;
  u32_t aut_neg_cnt = 200, auto_stat, transfer_mode = 0;

  /* We advertise for 10/100 Mbps both half and full duplex */
  adv_val = (PHY_100BTX | PHY_100BTX_FD | PHY_10BT | PHY_10BT_FD);

  /**
   * Not all the PHYs can operate at 1000 Mbps. So advertise only
   * if the PHY is capable
   */
  if(TRUE == cpswinst->port[port_num -1].phy_gbps) {
    gig_adv_val = PHY_1000BT_FD;
    partnr_ablty = TRUE;
    gbps_partnr_ablty = TRUE;
  } else {
    gig_adv_val = 0;
    partnr_ablty = TRUE;
    gbps_partnr_ablty = FALSE;
  }

  LWIP_PRINTF("\n\rPerforming Auto-Negotiation...");

  /**
   * Now start Autonegotiation. PHY will talk to its partner
   * and give us what the partner can handle
   */
  if(PhyAutoNegotiate(cpswinst->mdio_base,
                      cpswinst->port[port_num -1].phy_addr,
                      &adv_val, &gig_adv_val) == TRUE) {
    while(aut_neg_cnt) {
      delay(50);
      auto_stat = PhyAutoNegStatusGet(cpswinst->mdio_base,
                                      cpswinst->port[port_num -1].phy_addr);
      if(TRUE == auto_stat) {
        break;
      }
      aut_neg_cnt--;
    }

    if(0 != aut_neg_cnt) {
      linkstat = ERR_OK;
      LWIP_PRINTF("\n\rAuto-Negotiation Successful.");
    } else {
      LWIP_PRINTF("\n\rAuto-Negotiation Not Successful.");
      return ERR_CONN;
    }

    /* Get what the partner supports */
    PhyPartnerAbilityGet(cpswinst->mdio_base,
                         cpswinst->port[port_num -1].phy_addr,
                         &partnr_ablty, &gbps_partnr_ablty);
    if(gbps_partnr_ablty & PHY_LINK_PARTNER_1000BT_FD) {
      LWIP_PRINTF("\n\rTransfer Mode : 1000 Mbps.");
      transfer_mode = CPSW_SLIVER_GIG_FULL_DUPLEX;
    } else {
      if ((adv_val & partnr_ablty) & PHY_100BTX_FD) {
        LWIP_PRINTF("\n\rTransfer Mode : 100 Mbps Full Duplex.");
        transfer_mode = CPSW_SLIVER_NON_GIG_FULL_DUPLEX;
      } else if ((adv_val & partnr_ablty) & PHY_100BTX) {
        LWIP_PRINTF("\n\rTransfer Mode : 100 Mbps Half Duplex.");
        transfer_mode = CPSW_SLIVER_NON_GIG_HALF_DUPLEX;
      } else if ((adv_val & partnr_ablty) & PHY_10BT_FD) {
        LWIP_PRINTF("\n\rTransfer Mode : 10 Mbps Full Duplex.");
        transfer_mode = CPSW_SLIVER_INBAND | CPSW_SLIVER_NON_GIG_FULL_DUPLEX;
      } else if ((adv_val & partnr_ablty) & PHY_10BT) {
        LWIP_PRINTF("\n\rTransfer Mode : 10 Mbps Half Duplex.");
        transfer_mode = CPSW_SLIVER_INBAND | CPSW_SLIVER_NON_GIG_HALF_DUPLEX;
      } else {
        LWIP_PRINTF("\n\rNo Valid Transfer Mode is detected.");
      }
    }
  } else {
    LWIP_PRINTF("\n\rAuto-Negotiation Not Successful.");
    linkstat = ERR_CONN;
  }

  /**
   * Set the Sliver with the negotiation results if autonegotiation
   * is successful
   */
  if(linkstat == ERR_OK) {
    CPSWSlTransferModeSet(cpswinst->port[port_num - 1].sliver_base,
                          transfer_mode);
  }

  return linkstat;
}

/**
 * This function allocates the rx buffer descriptors ring. The function
 * internally calls pbuf_alloc() and allocates the pbufs to the rx buffer
 * descriptors.
 *
 * @param   cpswinst   The CPSW instance structure pointer
 * @return  None
 */
static void
cpswif_rxbd_alloc(struct cpswinst *cpswinst) {
  struct rxch *rxch = &(cpswinst->rxch);
  struct pbuf *p;
  volatile struct cpdma_rx_bd *curr_bd, *last_bd, *recv_tail, *recv_head;
  u32_t saved_free_num;

  /* Start from the free head of the chain */
  curr_bd = rxch->free_head;

  /* Note down the current positions */
  recv_head = rxch->free_head;
  recv_tail = rxch->recv_tail;
  saved_free_num = rxch->free_num;
  last_bd = rxch->recv_tail;

  while(rxch->free_num) {
    /**
     * Try to get a pbuf of max. length. This shall be cache line aligned if
     * cache is enabled.
     */
    p = pbuf_alloc(PBUF_RAW, PBUF_LEN_MAX, PBUF_POOL);

    /**
     * Allocate bd's if p is not NULL. This allocation doesnt support
     * pbuf chaining.
     */
    if(p != NULL) {
#ifdef LWIP_CACHE_ENABLED
      /**
       * Clean the pbuf structure info. This is needed to prevent losing
       * pbuf structure info when we invalidate the pbuf on rx interrupt
       */
      CacheDataCleanBuff((u32_t)(p), (u32_t)(SIZEOF_STRUCT_PBUF));
#endif
      curr_bd->bufptr = (u32_t)(p->payload);
      curr_bd->bufoff_len = p->len;
      curr_bd->flags_pktlen = CPDMA_BUF_DESC_OWNER;

      /* Save the pbuf */
      curr_bd->pbuf = p;
      last_bd = curr_bd;
      curr_bd = curr_bd->next;
      rxch->free_num--;
    } else {
      break;
    }
  }

  if(saved_free_num == rxch->free_num) {
    /* No bd's were allocated. Go back. */
    return;
  }

  rxch->recv_tail = last_bd;

  /**
   * If the entire ring is traversed, curr_bd will be NULL. In that case,
   * write the Rx HDP in order to continue reception
   */
  if(NULL != curr_bd) {
    rxch->free_head = curr_bd;
  } else {
    CPSWCPDMARxHdrDescPtrWrite(cpswinst->cpdma_base, (u32_t)(recv_head), 0);
  }

  recv_tail->next = recv_head;

  /* Close the ring to prevent overwriting of pbuf data */
  last_bd->next = NULL;

  /**
   * Check if the reception has ended. If the EOQ flag is set, the NULL
   * Pointer is  already taken by the DMA engine. So we need to write the
   * RX HDP with the next descriptor.
   */
  if(recv_tail->flags_pktlen & CPDMA_BUF_DESC_EOQ) {
    CPSWCPDMARxHdrDescPtrWrite(cpswinst->cpdma_base, (u32_t)(recv_head), 0);
  }
}

/**
 * This function does the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf might be
 * chained. That is, one pbuf can span more than one tx buffer descriptors
 *
 * @param netif    the network interface state for this ethernetif
 * @param pbuf     the pbuf which is to be sent over EMAC
 * @return status  ERR_OK, if transmit was successful
 *                 ERR_MEM, if no memory available
 */
static err_t
cpswif_transmit(struct netif *netif, struct pbuf *pbuf) {
  struct pbuf *q;
  struct txch *txch;
  volatile struct cpdma_tx_bd *curr_bd, *bd_to_send, *bd_end;
  struct cpswportif *cpswif = netif->state;
  u32_t inst_num = cpswif->inst_num;
  struct cpswinst *cpswinst = &cpsw_inst_data[inst_num];

#ifdef CPSW_DUAL_MAC_MODE
  u32_t port_num = cpswif->port_num;
#endif

  txch = &(cpswinst->txch);

  /* Do not send if there are no enough free bd's */
  if(pbuf_clen(pbuf) > txch->free_num) {
    return ERR_MEM;
  }

  /* Get the buffer descriptor which is free to transmit */
  curr_bd = txch->free_head;

  bd_to_send = txch->free_head;

  /* Update the total packet length */
  curr_bd->flags_pktlen = pbuf->tot_len;

  /* Indicate the start of the packet */
  curr_bd->flags_pktlen |= (CPDMA_BUF_DESC_SOP | CPDMA_BUF_DESC_OWNER);

#ifdef CPSW_DUAL_MAC_MODE
  /* Indicate to which port the packet has to be sent */
  curr_bd->flags_pktlen |= CPDMA_BUF_DESC_TO_PORT(port_num);
#endif

  /* Copy pbuf information into TX buffer descriptors */
  for(q = pbuf; q != NULL; q = q->next) {
#ifdef LWIP_CACHE_ENABLED
    /**
     * Make sure that the payload is written to memory. Clean
     * the portion of cache to make it coherent with the memory.
     */
    CacheDataCleanBuff((u32_t)(q->payload), (u32_t)(q->len));
#endif
    /* Intialize the buffer pointer and length */
    curr_bd->bufptr = (u32_t)(q->payload);
    curr_bd->bufoff_len = (q->len) & CPDMA_BD_LEN_MASK;
    bd_end = curr_bd;
    curr_bd->pbuf = pbuf;
    curr_bd = curr_bd->next;

    /* Decrement free bds, since one is consumed */
    txch->free_num--;
  }

  /* Indicate the end of the packet */
  bd_end->next = NULL;
  bd_end->flags_pktlen |= CPDMA_BUF_DESC_EOP;
  bd_end->flags_pktlen &= ~CPDMA_BUF_DESC_EOQ;

  txch->free_head = curr_bd;

  /* For the first time, write the HDP with the filled bd */
  if(txch->send_tail == NULL) {
    CPSWCPDMATxHdrDescPtrWrite(cpswinst->cpdma_base,
                               (u32_t)(bd_to_send), 0);
  } else {
    /**
     * Chain the bd's. If the DMA engine, already reached the end of the chain,
     * the EOQ will be set. In that case, the HDP shall be written again.
     */
    curr_bd = txch->send_tail;
    curr_bd->next = bd_to_send;

    if(curr_bd->flags_pktlen & CPDMA_BUF_DESC_EOQ) {
      /* Write the Header Descriptor Pointer and start DMA */
      CPSWCPDMATxHdrDescPtrWrite(cpswinst->cpdma_base,
                                 (u32_t)(bd_to_send), 0);
    }
  }

  txch->send_tail = bd_end;

  return ERR_OK;
}

/**
 * This function will send a packet through the emac if the channel is
 * available. Otherwise, the packet will be queued in a pbuf queue.
 *
 * @param netif   The lwip network interface structure for this ethernetif
 * @param p       The MAC packet to send (e.g. IP packet including
 *                MAC addresses and type)
 * @return        ERR_OK if the packet could be sent
 *                an err_t value if the packet couldn't be sent
 *
 */
static err_t
cpswif_output(struct netif *netif, struct pbuf *p) {
  err_t stat;
  SYS_ARCH_DECL_PROTECT(lev);

  /**
   * This entire function must run within a "critical section" to preserve
   * the integrity of the transmit pbuf queue.
   */
  SYS_ARCH_PROTECT(lev);

  /**
   * Adjust the packet length if less than minimum required.
   */
  if(p->tot_len < MIN_PKT_LEN) {
    p->tot_len = MIN_PKT_LEN;

    while(p->next != NULL) {
      p->next->tot_len = p->tot_len - p->len;
      p = p->next;
    }

    /* Adjust the length of the last pbuf. (contents - don't care) */
    p->len = p->tot_len;
  }

  /**
   * Bump the reference count on the pbuf to prevent it from being
   * freed till we are done with it.
   */
  pbuf_ref(p);

  /* call the actual transmit function */
  stat = cpswif_transmit(netif, p);

  /* Return to prior interrupt state and return. */
  SYS_ARCH_UNPROTECT(lev);

  return stat;
}

/**
 * Configures PHY link for a port
 * @param cpswif  The CPSW interface structure pointer
 * @param slv_port_num  The slave port number
 *
 * @return ERR_OK    if link configurations are successful
 *                   an error status if failed
 */
static err_t
cpswif_phylink_config(struct cpswportif * cpswif, u32_t slv_port_num) {
  struct cpswinst *cpswinst = &cpsw_inst_data[cpswif->inst_num];
  err_t err;

  /* Check if ethernet PHY is present or not */
  if(0 == (MDIOPhyAliveStatusGet(cpswinst->mdio_base)
        & (1 << cpswinst->port[slv_port_num - 1].phy_addr))){
    LWIP_PRINTF("\n\rNo PHY found at address %d for  Port %d of Instance %d.",
                cpswinst->port[slv_port_num - 1].phy_addr, slv_port_num,
                cpswif->inst_num);
    return ERR_CONN;
  }

  LWIP_PRINTF("\n\rPHY found at address %d for  Port %d of Instance %d.",
              cpswinst->port[slv_port_num - 1].phy_addr, slv_port_num,
              cpswif->inst_num);

  /**
   * PHY is alive. So autonegotiate and get the speed and duplex
   * parameters, set it in the sliver
   */
  err = (err_t)(cpswif_autoneg_config(cpswif->inst_num, slv_port_num));

  /* Check if PHY link is there or not */
  if(FALSE == ((PhyLinkStatusGet(cpswinst->mdio_base,
                           cpswinst->port[slv_port_num - 1].phy_addr, 1000)))) {
    LWIP_PRINTF("\n\rPHY link connectivity failed for Port %d of Instance %d.",
                slv_port_num, cpswif->inst_num);
    return ERR_CONN;
  }

  LWIP_PRINTF("\n\rPHY link verified for Port %d of Instance %d.",
              slv_port_num, cpswif->inst_num);

  CPSWSlRGMIIEnable(cpswinst->port[slv_port_num - 1].sliver_base);

  return err;
}

/**
 * Initializes the CPSW port
 * @param netif   The cpsw interface
 *
 * @return ERR_OK    if port initialization is successful
 *                   an error status if failed
 */
static err_t
cpswif_port_init(struct netif *netif) {
  struct cpswportif *cpswif = (struct cpswportif*)(netif->state);
  u32_t temp;
  err_t err;

#ifdef CPSW_DUAL_MAC_MODE
  struct cpswinst *cpswinst = &cpsw_inst_data[cpswif->inst_num];
  u32_t curr_port = cpswif->port_num;
#endif

  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  for(temp = 0; temp < ETHARP_HWADDR_LEN; temp++) {
    netif->hwaddr[temp] = cpswif->eth_addr[temp];
  }

  /* maximum transfer unit */
  netif->mtu = MAX_TRANSFER_UNIT;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

#ifdef CPSW_DUAL_MAC_MODE
  /* Set the ethernet address for the port */
  CPSWPortSrcAddrSet(cpswinst->port[curr_port - 1].port_base,
                    (u8_t *)(&(cpswif->eth_addr)));

  /**
   * For Dual Mac mode, configure port0 and port1 for one VLAN ID;
   * port0 and port2 for a different VLAN ID. Here we choose the
   * port number as VLAN ID.
   */
  CPSWPortVLANConfig(cpswinst->port[curr_port - 1].port_base, curr_port, 0, 0);

  cpswif_port_to_host_vlan_cfg(cpswinst, curr_port,
                               (u8_t *)(&(cpswif->eth_addr)));

  err = cpswif_phylink_config(cpswif, curr_port);

#else
  err = cpswif_phylink_config(cpswif, 1);
  err = err & (cpswif_phylink_config(cpswif, 2));

#endif

  return err;
}

/**
 * This function intializes the CPDMA.
 * The CPPI RAM will be initialized for transmit and receive
 * buffer descriptor rings.
 *
 * @param cpswinst   The CPSW instance structure pointer
 * @return None
 */
static void
cpswif_cpdma_init(struct cpswinst *cpswinst) {
  u32_t num_bd;
  volatile struct cpdma_tx_bd *curr_txbd, *last_txbd;
  volatile struct cpdma_rx_bd *curr_rxbd, *last_rxbd;
  struct txch *txch;
  struct rxch *rxch;

  txch = &(cpswinst->txch);

  /* Initialize the CPDMA memory. Only Channel 0 is supported */
  txch->free_head = (volatile struct cpdma_tx_bd*)(cpswinst->cppi_ram_base);
  txch->send_head = txch->free_head;
  txch->send_tail = NULL;

  /* Allocate half of the CPPI RAM for TX buffer descriptors */
  num_bd = (SIZE_CPPI_RAM >> 1) / sizeof(cpdma_tx_bd);

  /* All buffer descriptors are free to send */
  txch->free_num = num_bd;

  curr_txbd = txch->free_head;

  /* Initialize all the TX buffer descriptors ring */
  while(num_bd) {
    curr_txbd->next = curr_txbd + 1;
    curr_txbd->flags_pktlen = 0;
    last_txbd = curr_txbd;
    curr_txbd = curr_txbd->next;
    num_bd--;
  }
  last_txbd->next = txch->free_head;

  /* Initialize the descriptors for the RX channel */
  rxch = &(cpswinst->rxch);
  rxch->free_head = (volatile struct cpdma_rx_bd*)(cpswinst->cppi_ram_base +
                                                   (SIZE_CPPI_RAM >> 1));

  /* Allocate half of the CPPI RAM available for RX buffer dscriptors */
  num_bd = (SIZE_CPPI_RAM >> 1) / sizeof(cpdma_rx_bd);
  rxch->free_num = num_bd;

  curr_rxbd = rxch->free_head;

  /* Create the rx ring of buffer descriptors */
  while(num_bd) {
    curr_rxbd->next = curr_rxbd + 1;
    curr_rxbd->flags_pktlen = CPDMA_BUF_DESC_OWNER;
    last_rxbd = curr_rxbd;
    curr_rxbd = curr_rxbd->next;
    num_bd--;
  }

  last_rxbd->next = rxch->free_head;

  /* We are going to receive starting from the free head */
  rxch->recv_head = rxch->free_head;
  rxch->recv_tail = last_rxbd;
  cpswif_rxbd_alloc(cpswinst);

  /* close the ring */
  last_rxbd->next = NULL;

  CPSWCPDMARxHdrDescPtrWrite(cpswinst->cpdma_base, (u32_t)(rxch->recv_head), 0);
}

/**
 * In this function, the hardware should be initialized.
 * Called from cpswif_init().
 *
 * @param cpswportif  The CPSW port interface structure pointer
 * @return None
 */
static void
cpswif_inst_init(struct cpswportif *cpswif){
  u32_t inst_num = cpswif->inst_num;
  struct cpswinst *cpswinst = &cpsw_inst_data[inst_num];

  /* Reset the different modules */
  CPSWSSReset(cpswinst->ss_base);
  CPSWWrReset(cpswinst->wrpr_base);
  CPSWSlReset(cpswinst->port[PORT_1].sliver_base);
  CPSWSlReset(cpswinst->port[PORT_2].sliver_base);
  CPSWCPDMAReset(cpswinst->cpdma_base);

  /* Initialize MDIO */
  MDIOInit(cpswinst->mdio_base, MDIO_FREQ_INPUT, MDIO_FREQ_OUTPUT);
  delay(1);

  CPSWALEInit(cpswinst->ale_base);

  /* Set the port 0, 1 and 2 states to FORWARD */
  CPSWALEPortStateSet(cpswinst->ale_base, 0, CPSW_ALE_PORT_STATE_FWD);
  CPSWALEPortStateSet(cpswinst->ale_base, 1, CPSW_ALE_PORT_STATE_FWD);
  CPSWALEPortStateSet(cpswinst->ale_base, 2, CPSW_ALE_PORT_STATE_FWD);

#ifdef CPSW_DUAL_MAC_MODE
  /* For Dual Mac Mode, Configure for VLAN Aware Mode */
  CPSWALEVLANAwareSet(cpswinst->ale_base);
  CPSWHostPortDualMacModeSet(cpswinst->host_port_base);

#else  /*CPSW_DUAL_MAC_MODE */
  /* For normal CPSW switch mode, set multicast entry. */
  u8_t bcast_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  cpswif_ale_multicastentry_set(cpswinst,
                                PORT_0_MASK | PORT_1_MASK | PORT_2_MASK,
                                bcast_addr);
  cpswif_ale_unicastentry_set(cpswinst, 0,
                              (u8_t *)(&(cpswif->eth_addr)));

  /* Set the ethernet address for both the ports */
  CPSWPortSrcAddrSet(cpswinst->port[0].port_base,
                    (u8_t *)(&(cpswif->eth_addr)));
  CPSWPortSrcAddrSet(cpswinst->port[1].port_base,
                    (u8_t *)(&(cpswif->eth_addr)));

#endif /*CPSW_DUAL_MAC_MODE */

  /* Enable the statistics. Lets see in case we come across any issues */
  CPSWStatisticsEnable(cpswinst->ss_base);

  /* Initialize the buffer descriptors for CPDMA */
  cpswif_cpdma_init(cpswinst);

  /* Acknowledge receive and transmit interrupts for proper interrupt pulsing*/
  CPSWCPDMAEndOfIntVectorWrite(cpswinst->cpdma_base, CPSW_EOI_TX_PULSE);
  CPSWCPDMAEndOfIntVectorWrite(cpswinst->cpdma_base, CPSW_EOI_RX_PULSE);

  /* Enable the transmission and reception */
  CPSWCPDMATxEnable(cpswinst->cpdma_base);
  CPSWCPDMARxEnable(cpswinst->cpdma_base);

  /* Enable the interrupts for channel 0 and for control core 0 */
  CPSWCPDMATxIntEnable(cpswinst->cpdma_base, 0);
  CPSWWrCoreIntEnable(cpswinst->wrpr_base, 0, 0, CPSW_CORE_INT_TX_PULSE);

  CPSWCPDMARxIntEnable(cpswinst->cpdma_base, 0);
  CPSWWrCoreIntEnable(cpswinst->wrpr_base, 0, 0, CPSW_CORE_INT_RX_PULSE);
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the functions cpswif_inst_init() and
 * cpswif_port_init() to do low level initializations
 *
 * @param netif     The lwip network interface structure for this ethernetif
 * @return ERR_OK   If the interface is initialized
 *                  any other err_t on error
 */
err_t
cpswif_init(struct netif *netif)
{
  struct cpswportif *cpswif = (struct cpswportif*)(netif->state);
  static u32_t inst_init_flag = 0;
  u32_t inst_num = cpswif->inst_num;

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  /**
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 10000000);

  /* let us use the interface number to identify netif */
#ifdef CPSW_DUAL_MAC_MODE
  netif->num = (u8_t)(((cpswif->inst_num * MAX_SLAVEPORT_PER_INST)
                      + cpswif->port_num - 1) & 0xFF);
#else
  netif->num = (u8_t)(cpswif->inst_num);
#endif

  /**
   * We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...)
   */
  netif->output = etharp_output;
  netif->linkoutput = cpswif_output;

  /**
   * Initialize an instance only once. Port initialization will be
   * done separately.
   */
  if(((inst_init_flag >> inst_num) & 0x01) == 0) {
    cpswif_inst_config(cpswif);
    cpswif_inst_init(cpswif);
    inst_init_flag |= (1 << inst_num);
  }

  if(cpswif_port_init(netif) != ERR_OK) {
    return ERR_CONN;
  }

  return ERR_OK;
}

/**
 * Handler for Receive interrupt. Packet processing is done in this
 * interrupt handler itself.
 *
 * @param inst_num   the instance for which interrupt was generated
 * @param netif_arr  the address of the array of netifs
 * @return none
 */
void
cpswif_rx_inthandler(u32_t inst_num, struct netif * netif_arr) {
  struct cpswinst *cpswinst = &cpsw_inst_data[inst_num];
  struct rxch *rxch;
  volatile struct cpdma_rx_bd *curr_bd;
  volatile struct pbuf *pbuf;
  u32_t tot_len, if_num;

#ifdef CPSW_DUAL_MAC_MODE
  u32_t from_port;
#endif

  /* Get the rx channel pointer */
  rxch = &(cpswinst->rxch);

  /* Get the bd which contains the earliest filled data */
  curr_bd = rxch->recv_head;

  /**
   * Process the receive buffer descriptors. When the DMA completes
   * reception, OWNERSHIP flag will be cleared.
   */
  while((curr_bd->flags_pktlen & CPDMA_BUF_DESC_OWNER)
           != CPDMA_BUF_DESC_OWNER) {

#ifdef CPSW_DUAL_MAC_MODE
    /**
     * From which slave port the packet came from ?
     * We will use this to decide to which netif the packet
     * is to be forwarded to.
     */
    from_port = ((curr_bd->flags_pktlen) & CPDMA_BUF_DESC_FROM_PORT)
                 >> CPDMA_BUF_DESC_FROM_PORT_SHIFT;
#endif

    /* Get the total length of the packet */
    tot_len = (curr_bd->flags_pktlen) & CPDMA_BD_PKTLEN_MASK;

    /* Get the pbuf which is associated with the current bd */
    pbuf = curr_bd->pbuf;
#ifdef LWIP_CACHE_ENABLED
    /**
     * Invalidate the cache lines of the pbuf including payload. Because
     * the memory contents got changed by DMA.
     */
    CacheDataInvalidateBuff((u32_t)pbuf, (PBUF_LEN_MAX + SIZEOF_STRUCT_PBUF));
#endif

    /* Update the len and tot_len fields for the pbuf in the chain */
    pbuf->len = (u16_t)(tot_len);
    pbuf->tot_len = (u16_t)(tot_len);

    curr_bd->flags_pktlen = CPDMA_BUF_DESC_OWNER;

    /* Adjust the link statistics */
    LINK_STATS_INC(link.recv);

#ifdef CPSW_DUAL_MAC_MODE
    if_num = (inst_num * MAX_SLAVEPORT_PER_INST) + from_port - 1;
#else
    if_num = inst_num;
#endif

    /* Process the packet */
    if(ethernet_input((struct pbuf *)pbuf, netif_arr + if_num) != ERR_OK) {
      /* Adjust the link statistics */
      LINK_STATS_INC(link.memerr);
      LINK_STATS_INC(link.drop);
    }

    /* Acknowledge that this packet is processed */
    CPSWCPDMARxCPWrite(cpswinst->cpdma_base, 0, (unsigned int)curr_bd);

    curr_bd = curr_bd->next;

    /* One more buffer descriptor is free now */
    rxch->free_num++;

    /**
     * If the DMA engine took the NULL pointer, we dont have any bd to
     * process until new bd's are allocated.
     */
    if(curr_bd == NULL) {
      rxch->recv_head = rxch->free_head;
      break;
    }
    rxch->recv_head = curr_bd;
  }

  CPSWCPDMAEndOfIntVectorWrite(cpswinst->cpdma_base, CPSW_EOI_RX_PULSE);

  /* We got some bd's freed; Allocate them */
  cpswif_rxbd_alloc(cpswinst);
}

/**
 * Handler for CPSW Transmit interrupt
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return none
 */
void
cpswif_tx_inthandler(u32_t inst_num) {
  struct txch *txch;
  struct cpswinst *cpswinst = &cpsw_inst_data[inst_num];
  volatile struct cpdma_tx_bd *curr_bd, *send_head;
  volatile u32_t cnt = 0xFFFF;

  txch = &(cpswinst->txch);

  send_head = txch->send_head;

  curr_bd = send_head;

  /* Check for correct start of packet */
  while((curr_bd->flags_pktlen) & CPDMA_BUF_DESC_SOP) {

    /* Make sure that the transmission is over */
    while(((curr_bd->flags_pktlen & CPDMA_BUF_DESC_OWNER)
          == CPDMA_BUF_DESC_OWNER) && ((--cnt) != 0));

    /* If CPDMA failed to transmit, give it a chance once more */
    if(0 == cnt) {
      CPSWCPDMATxHdrDescPtrWrite(cpswinst->cpdma_base,
                                 (u32_t)(curr_bd), 0);
      return;
    }

    /* One buffer descriptor is free now */
    txch->free_num++;

    /* Traverse till the end of packet is reached */
    while(((curr_bd->flags_pktlen) & CPDMA_BUF_DESC_EOP) != CPDMA_BUF_DESC_EOP) {
      curr_bd = curr_bd->next;

      /* As this bd is not the end, its free now */
      txch->free_num++;

      if(txch->free_num == (SIZE_CPPI_RAM >> 1) / sizeof(cpdma_tx_bd)) {
        break;
      }
    }

    send_head->flags_pktlen &= ~(CPDMA_BUF_DESC_SOP);
    curr_bd->flags_pktlen &= ~(CPDMA_BUF_DESC_EOP);

    /**
     * If there are no more data transmitted, the next interrupt
     * shall happen with the pbuf associated with the free_head
     */
    if(curr_bd->next == NULL) {
      txch->send_head = txch->free_head;
    } else {
      txch->send_head = curr_bd->next;
    }

    /* Acknowledge CPSW and free the corresponding pbuf */
    CPSWCPDMATxCPWrite(cpswinst->cpdma_base, 0, (u32_t)curr_bd);

    pbuf_free((struct pbuf *)curr_bd->pbuf);

    LINK_STATS_INC(link.xmit);

    send_head = txch->send_head;
    curr_bd = send_head;
  }

  CPSWCPDMAEndOfIntVectorWrite(cpswinst->cpdma_base, CPSW_EOI_TX_PULSE);
  cpswif_rxbd_alloc(cpswinst);
}

/**
 * Gets the netif status
 *
 * @param   netif   The netif whoes status to be checked
 * @return  The netif status
 */
u32_t
cpswif_netif_status(struct netif *netif) {
  return ((u32_t)(netif_is_up(netif)));
}

/**
 * Returns the link status
 *
 * @param   inst_num      The instance number of the module
 * @param   slv_port_num  The slave port number for the module
 *
 * @return  the link status
 */
u32_t
cpswif_link_status(u32_t inst_num, u32_t slv_port_num) {

  struct cpswinst *cpswinst = &cpsw_inst_data[inst_num];

  return (PhyLinkStatusGet(cpswinst->mdio_base,
                           cpswinst->port[slv_port_num - 1].phy_addr, 3));
}

/**
 * Checks the value is in the range of min and max
 *
 * @param   vlaue      Value
 * @param   min        Minimum Value
 * @param   max        Maximum Value
 *
 * @return  the status
 */
static u32_t
check_valid(u32_t value, u32_t min, u32_t max) {
  if ((min <= value) && (value <= max))
    return TRUE;
  else
    return FALSE;
}

/*
 * Executes following CPSW Configutarions
 * Switch Configuration (CPSW_SWITCH_CONFIG has to be defined)
 *  1 - Add a multicast entry
 *  2 - Add a unicast entry
 *  3 - Add a OUI entry
 *  4 - Search address in entry list
 *  5 - Delete a multicast entry
 *  6 - Delete a unicast entry
 *  7 - Adds a vlan entry
 *  8 - Search vlan in entry list
 *  9 - Delete vlan
 * 10 - Configure Port Vlan (ID, CFI, PRI)
 * 11 - Age Out the Untouched entries of ALE Table
 * 12 - Print Dump of Switch
 * 13 - Print Dump of Switch Config
 * 14 - ALE VLAN Aware Config
 * 15 - Configure Rate Limit for TX or RX
 * 16 - Enable Engress Check
 * 17 - Set port unknown VLAN info
 * 18 - Enable MAC Auth
 * 19 - Configure Port State
 * Phy Configuration
 *  1 - Configure PHY of a port
 *
 * @param   cpsw_switch_config  parameters required for configuration
 *
 * @return  None
*/
void
cpsw_switch_configuration(struct cpsw_config *cpsw_config) {
  struct cpswinst *cpswinst = &cpsw_inst_data[cpsw_config->cpsw_inst];
  struct cpsw_phy_param *cpsw_phy_param = cpsw_config->phy_param;
#ifdef CPSW_SWITCH_CONFIG
  struct cpsw_switch_param *cpsw_switch_param = cpsw_config->switch_param;
  s32_t ret;
#endif /* CPSW_SWITCH_CONFIG */

  switch (cpsw_config->cmd) {
#ifdef CPSW_SWITCH_CONFIG
    case CONFIG_SWITCH_ADD_MULTICAST:
    {
      if (!check_valid_addr(cpsw_switch_param->addr, ADDR_TYPE_MULTICAST)) {
        cpsw_config->ret = ERR_ADDR;
        break;
      }

      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_mask, MIN_PORT_MASK,
                      MAX_PORT_MASK)) {
        cpsw_config->ret = ERR_PORT_MASK;
        break;
      }

      if (!check_valid(cpsw_switch_param->super, MIN_SUPER, MAX_SUPER)) {
        cpsw_config->ret = ERR_SUPER;
        break;
      }

      if (!check_valid(cpsw_switch_param->fwd_state, MIN_MCAST_FWD_STATE,
                      MAX_MCAST_FWD_STATE)) {
        cpsw_config->ret = ERR_MCAST_FWD_STATE;
        break;
      }

      if (cpsw_switch_param->vid == 0)
        ret = cpswif_ale_multicastentry_add(cpswinst,
                                            cpsw_switch_param->port_mask,
                                            cpsw_switch_param->addr,
                                            cpsw_switch_param->super,
                                            cpsw_switch_param->fwd_state);
      else
        ret = cpswif_ale_vlan_add_mcast(cpswinst, cpsw_switch_param->vid,
                                        cpsw_switch_param->port_mask,
                                        cpsw_switch_param->addr,
                                        cpsw_switch_param->super,
                                        cpsw_switch_param->fwd_state);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_ADD_UNICAST:
    {
      if (!check_valid_addr(cpsw_switch_param->addr, ADDR_TYPE_UNICAST)) {
        cpsw_config->ret = ERR_ADDR;
        break;
      }

      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      if (!check_valid(cpsw_switch_param->ucast_flags, MIN_UCAST_FLAGS,
                      MAX_UCAST_FLAGS)) {
        cpsw_config->ret = ERR_UCAST_FLAGS;
        break;
      }

      if (!check_valid(cpsw_switch_param->ucast_type, MIN_UCAST_FLAGS,
                      MAX_UCAST_FLAGS)) {
        cpsw_config->ret = ERR_UCAST_FLAGS;
        break;
      }

      if (cpsw_switch_param->vid == 0)
        ret = cpswif_ale_unicastentry_add(cpswinst, cpsw_switch_param->port_num,
                                          cpsw_switch_param->addr,
                                          cpsw_switch_param->ucast_flags,
                                          cpsw_switch_param->ucast_type);
      else
        ret = cpswif_ale_vlan_add_ucast(cpswinst, cpsw_switch_param->vid,
                                        cpsw_switch_param->port_num,
                                        cpsw_switch_param->addr,
                                        cpsw_switch_param->ucast_flags,
                                        cpsw_switch_param->ucast_type);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_ADD_OUI:
    {
      if (!check_valid_addr(cpsw_switch_param->addr, ADDR_TYPE_UNICAST)) {
        cpsw_config->ret = ERR_ADDR;
        break;
      }

      ret = cpswif_ale_OUI_add(cpswinst, cpsw_switch_param->addr);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_FIND_ADDR:
    {
      if (!check_valid_addr(cpsw_switch_param->addr, 0)) {
        cpsw_config->ret = ERR_ADDR;
        break;
      }

      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      ret = cpswif_ale_entry_match_addr(cpswinst, cpsw_switch_param->addr,
                                        cpsw_switch_param->vid);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_DEL_MULTICAST:
    {
      if (!check_valid_addr(cpsw_switch_param->addr, ADDR_TYPE_MULTICAST)) {
        cpsw_config->ret = ERR_ADDR;
        break;
      }

      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_mask, MIN_PORT_MASK,
                      MAX_PORT_MASK)) {
        cpsw_config->ret = ERR_PORT_MASK;
        break;
      }

      if (cpsw_switch_param->vid == 0)
        ret = cpswif_ale_multicastentry_del(cpswinst, cpsw_switch_param->port_mask,
                                            cpsw_switch_param->addr);
      else
        ret = cpswif_ale_vlan_del_mcast(cpswinst, cpsw_switch_param->vid,
                                        cpsw_switch_param->port_mask,
                                        cpsw_switch_param->addr);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_DEL_UNICAST:
    {
      if (!check_valid_addr(cpsw_switch_param->addr, ADDR_TYPE_UNICAST)) {
        cpsw_config->ret = ERR_ADDR;
        break;
      }

      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      if (cpsw_switch_param->vid == 0)
        ret = cpswif_ale_unicastentry_del(cpswinst, cpsw_switch_param->port_num,
                                          cpsw_switch_param->addr);
      else
        ret = cpswif_ale_vlan_del_ucast(cpswinst, cpsw_switch_param->vid,
                                        cpsw_switch_param->port_num,
                                        cpsw_switch_param->addr);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_ADD_VLAN:
    {
      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      if (!check_valid(cpsw_switch_param->reg_multi, MIN_VLAN_MCAST_REG,
                      MAX_VLAN_MCAST_REG)) {
        cpsw_config->ret = ERR_VLAN_MCAST_REG;
        break;
      }

      if (!check_valid(cpsw_switch_param->unreg_multi, MIN_VLAN_MCAST_UNREG,
                      MAX_VLAN_MCAST_UNREG)) {
        cpsw_config->ret = ERR_VLAN_MCAST_UNREG;
        break;
      }

      if (!check_valid(cpsw_switch_param->untag_port, MIN_VLAN_UNTAG,
                      MAX_VLAN_UNTAG)) {
        cpsw_config->ret = ERR_VLAN_MCAST_UNTAG;
        break;
      }

      ret = cpswif_ale_vlan_add(cpswinst, cpsw_switch_param->vid,
                                cpsw_switch_param->port_num,
                                cpsw_switch_param->untag_port,
                                cpsw_switch_param->reg_multi,
                                cpsw_switch_param->unreg_multi);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_FIND_VLAN:
    {
      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      ret = cpswif_ale_entry_match_vlan(cpswinst, cpsw_switch_param->vid);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_DEL_VLAN:
    {
      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      ret = cpswif_ale_vlan_del(cpswinst, cpsw_switch_param->vid,
                                cpsw_switch_param->port_num);

      if (ret == ERR_VAL)
        cpsw_config->ret = ERR_FAIL;
      else
        cpsw_config->ret = ret;

      break;
    }

    case CONFIG_SWITCH_PORT_VLAN_CONFIG:
    {
      if (!check_valid(cpsw_switch_param->vid, MIN_VLANID, MAX_VLANID)) {
        cpsw_config->ret = ERR_VLANID;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      if (!check_valid(cpsw_switch_param->cfi_port, MIN_CFI, MAX_CFI)) {
        cpsw_config->ret = ERR_CFI;
        break;
      }

      if (!check_valid(cpsw_switch_param->prio_port, MIN_PRI, MAX_PRI)) {
        cpsw_config->ret = ERR_PRI;
        break;
      }

      if (cpsw_switch_param->port_num == 0)
          CPSWPortVLANConfig(cpswinst->host_port_base, cpsw_switch_param->vid,
                             cpsw_switch_param->cfi_port,
                             cpsw_switch_param->prio_port);
      else if (cpsw_switch_param->port_num <= 2)
          CPSWPortVLANConfig(
                        cpswinst->port[cpsw_switch_param->port_num - 1].port_base,
                        cpsw_switch_param->vid,
                        cpsw_switch_param->cfi_port,
                        cpsw_switch_param->prio_port);

      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_AGEOUT:
    {
      CPSWALEAgeOut(cpswinst->ale_base);
      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_DUMP:
    {
      u32_t cnt = 0;

      for(cnt = 0; cnt <= MAX_ALE_ENTRIES; cnt++)
      {
        CPSWALETableEntryGet(cpswinst->ale_base, cnt,
                             cpsw_config->buf[cnt]);
      }

      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_CONFIG_DUMP:
    {

      if (!check_valid(cpsw_switch_param->ale_tbl_index, MIN_ALE_ENTRY_IDX,
                      MAX_ALE_ENTRY_IDX)) {
        cpsw_config->ret = ERR_ALE_ENTRY_IDX;
        break;
      }

      CPSWALETableEntryGet(cpswinst->ale_base, cpsw_switch_param->ale_tbl_index,
                           cpsw_config->ale_entry);
      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_VLANAWARE:
    {
      if (!check_valid(cpsw_switch_param->vlan_aware, MIN_VLANAWARE,
                      MAX_VLANAWARE)) {
        cpsw_config->ret = ERR_VLANAWARE;
        break;
      }

      if (!check_valid(cpsw_switch_param->drop_packet, MIN_ALE_VLANAWARE,
                      MAX_ALE_VLANAWARE)) {
        cpsw_config->ret = ERR_ALE_VLANAWARE;
        break;
      }

      if (!cpsw_switch_param->vlan_aware)
        CPSWVLANAwareDisable(cpswinst->ale_base);
      else
        CPSWVLANAwareEnable(cpswinst->ale_base);

      if (!cpsw_switch_param->drop_packet)
        CPSWALEVLANAwareClear(cpswinst->ale_base);
      else
        CPSWALEVLANAwareSet(cpswinst->ale_base);

      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_RATELIMIT:
    {
      if (!check_valid(cpsw_switch_param->enable, MIN_ENABLE, MAX_ENABLE)) {
        cpsw_config->ret = ERR_ENABLE;
        break;
      }

      if (!check_valid(cpsw_switch_param->direction, MIN_DIRECTION,
                       MAX_DIRECTION)) {
        cpsw_config->ret = ERR_DIRECTION;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      if (!check_valid(cpsw_switch_param->addr_type, MIN_ADDR_TYPE, MAX_ADDR_TYPE)) {
        cpsw_config->ret = ERR_ADDR_TYPE;
        break;
      }

      if (!check_valid(cpsw_switch_param->limit, MIN_LIMIT, MAX_LIMIT)) {
        cpsw_config->ret = ERR_LIMIT;
        break;
      }

      cpswif_rate_limit(cpswinst, cpsw_switch_param->enable,
                        cpsw_switch_param->direction,
                        cpsw_switch_param->port_num, cpsw_switch_param->addr_type,
                        cpsw_switch_param->limit);
      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_VID_INGRESS_CHECK:
    {
      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      CPSWALEVIDIngressCheckSet(cpswinst->ale_base, cpsw_switch_param->port_num);
      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_ADD_UNKNOWN_VLAN_INFO:
    {
      if (!check_valid(cpsw_switch_param->unknown_vlan, MIN_UNKNOWN_VLAN,
                      MAX_UNKNOWN_VLAN)) {
        cpsw_config->ret = ERR_UNKNOWN_VLAN;
        break;
      }

      if (cpsw_switch_param->unknown_vlan == ALE_PORT_UNTAGGED_EGRESS) {
        if (!check_valid(cpsw_switch_param->untag_port, MIN_VLAN_UNTAG,
                        MAX_VLAN_UNTAG)) {
          cpsw_config->ret = ERR_VLAN_MCAST_UNTAG;
          break;
        }

        CPSWALEUnknownUntaggedEgressSet(cpswinst->ale_base,
                                        cpsw_switch_param->untag_port);
      } else if (cpsw_switch_param->unknown_vlan ==
                 ALE_PORT_UNKNOWN_REG_MCAST_FLOOD) {
        if (!check_valid(cpsw_switch_param->reg_multi, MIN_VLAN_MCAST_REG,
                        MAX_VLAN_MCAST_REG)) {
          cpsw_config->ret = ERR_VLAN_MCAST_REG;
          break;
        }

        CPSWALEUnknownRegFloodMaskSet(cpswinst->ale_base,
                                      cpsw_switch_param->reg_multi);
      } else if (cpsw_switch_param->unknown_vlan ==
                 ALE_PORT_UNKNOWN_UNREG_MCAST_FLOOD) {
        if (!check_valid(cpsw_switch_param->unreg_multi, MIN_VLAN_MCAST_UNREG,
                        MAX_VLAN_MCAST_UNREG)) {
          cpsw_config->ret = ERR_VLAN_MCAST_UNREG;
          break;
        }

        CPSWALEUnknownUnRegFloodMaskSet(cpswinst->ale_base,
                                        cpsw_switch_param->unreg_multi);
      } else if (cpsw_switch_param->unknown_vlan ==
                 ALE_PORT_UNKNOWN_VLAN_MEMBER) {
        if (!check_valid(cpsw_switch_param->port_mask, MIN_PORT_MASK,
                        MIN_PORT_MASK)) {
          cpsw_config->ret = ERR_VLAN_MCAST_UNREG;
          break;
        }

        CPSWALEUnknownMemberListSet(cpswinst->ale_base,
                                    cpsw_switch_param->port_mask);
      }

      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_MACAUTH:
    {
      if (!check_valid(cpsw_switch_param->mac_auth, MIN_MAC_AUTH, MAX_MAC_AUTH)) {
        cpsw_config->ret = ERR_MAC_AUTH;
        break;
      }

      if (!cpsw_switch_param->mac_auth)
        CPSWALEAUTHModeClear(cpswinst->ale_base);
      else
        CPSWALEAUTHModeSet(cpswinst->ale_base);

      cpsw_config->ret = ERR_PASS;
      break;
    }

    case CONFIG_SWITCH_PORT_STATE:
    {
      if (!check_valid(cpsw_switch_param->port_num, MIN_PORT, MAX_PORT)) {
        cpsw_config->ret = ERR_PORT;
        break;
      }

      if (!check_valid(cpsw_switch_param->port_state, MIN_PORT_STATE,
                      MAX_PORT_STATE)) {
        cpsw_config->ret = ERR_PORT_STATE;
        break;
      }

      CPSWALEPortStateSet(cpswinst->ale_base, cpsw_switch_param->port_num,
                          cpsw_switch_param->port_state);
      cpsw_config->ret = ERR_PASS;
      break;
    }
#endif /* CPSW_SWITCH_CONFIG */

    case CONFIG_SWITCH_SET_PORT_CONFIG:
    {
      if (!check_valid(cpsw_phy_param->slv_port_num, MIN_SLV_PORT,
                       MAX_SLV_PORT)) {
        cpsw_config->ret = ERR_SLV_PORT;
        break;
      }

      if (!check_valid(cpsw_phy_param->autoneg, MIN_AUTONEG, MAX_AUTONEG)) {
        cpsw_config->ret = ERR_AUTONEG;
        break;
      }

      if (TRUE == cpsw_phy_param->autoneg) {
        if (!check_valid(cpsw_phy_param->config, MIN_PHY_CONFIG,
                         MAX_PHY_CONFIG)) {
          cpsw_config->ret = ERR_PHY_CONFIG;
          break;
        }
      } else {
        if (!check_valid(cpsw_phy_param->speed, MIN_SPEED, MAX_SPEED)) {
          cpsw_config->ret = ERR_SPEED;
          break;
        }

        if (!check_valid(cpsw_phy_param->duplex, MIN_DUPLEX, MAX_DUPLEX)) {
          cpsw_config->ret = ERR_DUPLEX;
          break;
        }
      }

      if (cpsw_phy_param->autoneg)
        cpswif_phy_autoneg(cpswinst, cpsw_phy_param->slv_port_num,
                                         cpsw_phy_param->config);
      else
        cpswif_phy_forced(cpswinst, cpsw_phy_param->slv_port_num,
                                        cpsw_phy_param->speed,
                                        cpsw_phy_param->duplex);

      cpsw_config->ret = ERR_PASS;
      break;
    }

    default:
      cpsw_config->ret = ERR_INVAL;
      break;
  }
}
