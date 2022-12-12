/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DM9000_H__
#define __DM9000_H__

/*MACRO DEFINATIONS*/


 #define SEP4020_ID_EMAC   ((unsigned int) 28) // Ethernet Mac
 /* Davicom 9161 PHY */
 #define MII_DM9161_ID   0x0181b880
 #define MII_DM9161A_ID  0x0181b8a0

 /* Davicom specific registers */
 #define MII_DSCR_REG    16
 #define MII_DSCSR_REG   17
 #define MII_DSINTR_REG  21

  /* Intel LXT971A PHY */
 #define MII_LXT971A_ID  0x001378E0

  /* Intel specific registers */
 #define MII_ISINTE_REG  18
 #define MII_ISINTS_REG  19
 #define MII_LEDCTRL_REG 20

 /* Realtek RTL8201 PHY */
 #define MII_RTL8201_ID  0x00008200

 /* Broadcom BCM5221 PHY */
 #define MII_BCM5221_ID  0x004061e0

 /* Broadcom specific registers */
 #define MII_BCMINTR_REG 26

  /* National Semiconductor DP83847 */
 #define MII_DP83847_ID  0x20005c30

  /* Altima AC101L PHY */
 #define MII_AC101L_ID   0x00225520

 /* Micrel KS8721 PHY */
 #define MII_KS8721_ID   0x00221610

 /* ........................................................................ */

 #define MAX_RBUFF_SZ    0x600           /* 1518 rounded up */
 #define MAX_RX_DESCR    20           /* max number of receive buffers */

 #define MAX_TBUFF_SZ    0x600           /* 1518 rounded up */
 #define MAX_TX_DESCR    20               /* max number of receive buffers */

 #define EMAC_DESC_DONE  0x00000001      /* bit for if DMA is done */
 #define EMAC_DESC_WRAP  0x00000002      /* bit for wrap */

 #define EMAC_BROADCAST  0x80000000      /* broadcast address */
 #define EMAC_MULTICAST  0x40000000      /* multicast address */
 #define EMAC_UNICAST    0x20000000      /* unicast address */

#define DM9161_inb(r)       (*(volatile rt_uint8_t  *)r)
#define DM9161_outb(r, d)   (*(volatile rt_uint8_t  *)r = d)
#define DM9161_inw(r)       (*(volatile rt_uint16_t *)r)
#define DM9161_outw(r, d)   (*(volatile rt_uint16_t *)r = d)

void rt_hw_dm9616_init(void);

#endif
