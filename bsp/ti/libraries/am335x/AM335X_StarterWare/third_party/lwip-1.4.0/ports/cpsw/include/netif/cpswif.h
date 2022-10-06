/**
 * @file - cpswif.h
 * Prototypes for CPSW Ethernet interface.
 *
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

/*
 * Copyright (c) 2010 Texas Instruments Incorporated
 *
 */
#include "src/include/lwip/netif.h"

#ifndef __CPSWIF_H__
#define __CPSWIF_H__

/***************************************************************************/
/*
 * Configurations for AM335x
 */
#ifdef am335x
#include "soc_AM335x.h"

#define MAX_CPSW_INST                   1    
#define CPSW0_SS_REGS                   SOC_CPSW_SS_REGS
#define CPSW0_MDIO_REGS                 SOC_CPSW_MDIO_REGS
#define CPSW0_WR_REGS                   SOC_CPSW_WR_REGS
#define CPSW0_CPDMA_REGS                SOC_CPSW_CPDMA_REGS	
#define CPSW0_ALE_REGS                  SOC_CPSW_ALE_REGS
#define CPSW0_CPPI_RAM_REGS             SOC_CPSW_CPPI_RAM_REGS
#define CPSW0_PORT_0_REGS               SOC_CPSW_PORT_0_REGS
#define CPSW0_PORT_1_REGS               SOC_CPSW_PORT_1_REGS
#define CPSW0_SLIVER_1_REGS             SOC_CPSW_SLIVER_1_REGS
#define CPSW0_PORT_2_REGS               SOC_CPSW_PORT_2_REGS
#define CPSW0_SLIVER_2_REGS             SOC_CPSW_SLIVER_2_REGS

#ifdef evmAM335x
#define CPSW0_PORT_1_PHY_ADDR           0
#define CPSW0_PORT_1_PHY_GIGABIT        TRUE
 
#elif defined(beaglebone)
#define CPSW0_PORT_1_PHY_ADDR           0
#define CPSW0_PORT_1_PHY_GIGABIT        FALSE

#elif defined(evmskAM335x)
#define CPSW0_PORT_1_PHY_ADDR           0
#define CPSW0_PORT_2_PHY_ADDR           1
#define CPSW0_PORT_1_PHY_GIGABIT        TRUE
#define CPSW0_PORT_2_PHY_GIGABIT        TRUE
#endif

#include "consoleUtils.h"
#define LWIP_PRINTF                     ConsoleUtilsPrintf

#else
#error Unsupported EVM !!!
#endif

#define MAX_SLAVEPORT_PER_INST          2

/*****************************************************************************/
/**
 * Helper struct to hold private data used to operate the ethernet interface.
 */
struct cpswportif {
  /* CPSW instance number */
  u32_t inst_num;

  /* CPSW port number */
  u32_t port_num;

  u8_t eth_addr[6];
}cpswportif;

extern u32_t cpswif_netif_status(struct netif *netif);
extern u32_t cpswif_link_status(u32_t inst_num, u32_t slv_port_num);
extern err_t cpswif_init(struct netif *netif);
extern void cpswif_rx_inthandler(u32_t inst_num, struct netif * netif_arr); 
extern void cpswif_tx_inthandler(u32_t inst_num);

#endif /* _CPSWIF_H__ */
