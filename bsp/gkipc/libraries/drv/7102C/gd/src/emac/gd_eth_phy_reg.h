/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_phy_reg.h
**
** \version     $Id$
**
** \brief
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#ifndef _GD_ETH_PHY_REG_H_
#define _GD_ETH_PHY_REG_H_



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
/* ------------------------------------------------------------------------- */
/*  Register 00 Basic Mode Control Register                                  */
/*  ip101    lan8700    rtl8200                                              */
/*   YES       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG0_BMCR                (0x00)

#define PHY_REG0_sft_RESET           (15)  /*1bit*/    /* read/write 0 */
#define PHY_REG0_sft_LOOPBACK        (14)  /*1bit*/    /* read/write 0 */
#define PHY_REG0_sft_SPEEDSELECT     (13)  /*1bit*/    /* read/write 0 */
#define PHY_REG0_sft_AN_ENABLE       (12)  /*1bit*/    /* read/write 1 */
#define PHY_REG0_sft_POWER_DOWN      (11)  /*1bit*/    /* read/write 0 */
#define PHY_REG0_sft_ISOLATE         (10)  /*1bit*/    /* read/write 0 */
#define PHY_REG0_sft_RESTART_AN      ( 9)  /*1bit*/    /* read/write 0 */
#define PHY_REG0_sft_DUPLEX_MODE     ( 8)  /*1bit*/    /* read/write 0 */
#define PHY_REG0_sft_COLLISION_TEST  ( 7)  /*1bit*/    /* read/write 0 */   /* Collision test */
#define ETH_BMCR_sft_SPEED1000       ( 6)  /*1bit*/    /* read/write 0 */   /* MSB of Speed (1000) */

#define PHY_REG0_bit_RESET           (1)
#define PHY_REG0_bit_LOOPBACK        (1)
#define PHY_REG0_bit_SPEEDSELECT     (1)
#define PHY_REG0_bit_AN_ENABLE       (1)
#define PHY_REG0_bit_POWER_DOWN      (1)
#define PHY_REG0_bit_ISOLATE         (1)
#define PHY_REG0_bit_RESTART_AN      (1)
#define PHY_REG0_bit_DUPLEX_MODE     (1)
#define PHY_REG0_bit_COLLISION_TEST  (1)
#define PHY_REG0_bit_SPEED1000       (1)

#define PHY_REG0_val_RESET           ((1) << PHY_REG0_sft_RESET          )
#define PHY_REG0_val_LOOPBACK        ((1) << PHY_REG0_sft_LOOPBACK       )
#define PHY_REG0_val_100M            ((1) << PHY_REG0_sft_SPEEDSELECT    )
#define PHY_REG0_val_10M             ((0) << PHY_REG0_sft_SPEEDSELECT    )
#define PHY_REG0_val_AUTO_NEGO       ((1) << PHY_REG0_sft_AN_ENABLE      )
#define PHY_REG0_val_POWER_DOWN      ((1) << PHY_REG0_sft_POWER_DOWN     )
#define PHY_REG0_val_POWER_ON        ((0) << PHY_REG0_sft_POWER_DOWN     )
#define PHY_REG0_val_ISOLATE         ((1) << PHY_REG0_sft_ISOLATE        )
#define PHY_REG0_val_RESTART_AUTONEG ((1) << PHY_REG0_sft_RESTART_AN     )
#define PHY_REG0_val_DUPLEX_FULL     ((1) << PHY_REG0_sft_DUPLEX_MODE    )
#define PHY_REG0_val_DUPLEX_HALF     ((0) << PHY_REG0_sft_DUPLEX_MODE    )
#define PHY_REG0_val_COLLISION_TEST  ((1) << PHY_REG0_sft_COLLISION_TEST )
#define PHY_REG0_val_SPEED1000       ((1) << ETH_BMCR_sft_SPEED1000      )

/* ------------------------------------------------------------------------- */
/*  Register 01 Basic Mode Status Register (RO)                              */
/*  ip101    lan8700    rtl8200                                              */
/*   YES       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG1_BMSR                (0x01)

#define PHY_REG1_sft_100T4           (15)  /*1bit*/    /* read 0 */
#define PHY_REG1_sft_100TX_FULL      (14)  /*1bit*/    /* read 1 */
#define PHY_REG1_sft_100TX_HALF      (13)  /*1bit*/    /* read 1 */
#define PHY_REG1_sft_10_FULL         (12)  /*1bit*/    /* read 1 */
#define PHY_REG1_sft_10_HALF         (11)  /*1bit*/    /* read 1 */
#define PHY_REG1_sft_100_FULL2       (10)  /*1bit*/    /* read 1 */     /* Can do 100BASE-T2 FDX */
#define PHY_REG1_sft_100_HALF2       ( 9)  /*1bit*/    /* read 1 */     /* Can do 100BASE-T2 HDX */
#define PHY_REG1_sft_ESTATEN         ( 8)  /*1bit*/    /* read 1 */     /* Extended Status in R15 */
#define PHY_REG1_sft_PRE_SUPPRESSION ( 6)  /*1bit*/    /* read 1 */
#define PHY_REG1_sft_AN_COMPLETE     ( 5)  /*1bit*/    /* read 0 */
#define PHY_REG1_sft_REMOTE_FAULT    ( 4)  /*1bit*/    /* read 0 */
#define PHY_REG1_sft_AN_ABILITY      ( 3)  /*1bit*/    /* read 0 */    /* Able to do auto-negotiation */
#define PHY_REG1_sft_LINK_STAT       ( 2)  /*1bit*/    /* read 0 */
#define PHY_REG1_sft_EXT_CAPABLE     ( 1)  /*1bit*/    /* read 0 */
#define PHY_REG1_sft_JABBER_DETECT   ( 1)  /*1bit*/    /* read 0 */     /* Jabber detected */
#define PHY_REG1_sft_ERCAP           ( 0)  /*1bit*/    /* read 0 */     /* Ext-reg capability */

#define PHY_REG1_bit_100T4           (1)
#define PHY_REG1_bit_100TX_FULL      (1)
#define PHY_REG1_bit_100TX_HALF      (1)
#define PHY_REG1_bit_10_FULL         (1)
#define PHY_REG1_bit_10_HALF         (1)
#define PHY_REG1_bit_PRE_SUPPRESSION (1)
#define PHY_REG1_bit_AN_COMPLETE     (1)
#define PHY_REG1_bit_REMOTE_FAULT    (1)
#define PHY_REG1_bit_AN_ABILITY      (1)
#define PHY_REG1_bit_LINK_STAT       (1)
#define PHY_REG1_bit_EXT_CAPABLE     (1)
#define PHY_REG1_bit_JABBER_DETECT   (1)

#define PHY_REG1_val_100T4           ((1) << PHY_REG1_sft_100T4          )
#define PHY_REG1_val_100TX_FULL      ((1) << PHY_REG1_sft_100TX_FULL     )
#define PHY_REG1_val_100TX_HALF      ((1) << PHY_REG1_sft_100TX_HALF     )
#define PHY_REG1_val_10_FULL         ((1) << PHY_REG1_sft_10_FULL        )
#define PHY_REG1_val_10_HALF         ((1) << PHY_REG1_sft_10_HALF        )
#define PHY_REG1_val_100_FULL2       ((1) << PHY_REG1_sft_100_FULL2      )
#define PHY_REG1_val_100_HALF2       ((1) << PHY_REG1_sft_100_HALF2      )
#define PHY_REG1_val_ESTATEN         ((1) << PHY_REG1_sft_ESTATEN        )
#define PHY_REG1_val_PRE_SUPPRESSION ((1) << PHY_REG1_sft_PRE_SUPPRESSION)
#define PHY_REG1_val_AN_COMPLETE     ((1) << PHY_REG1_sft_AN_COMPLETE    )
#define PHY_REG1_val_REMOTE_FAULT    ((1) << PHY_REG1_sft_REMOTE_FAULT   )
#define PHY_REG1_val_AN_ABILITY      ((1) << PHY_REG1_sft_AN_ABILITY     )
#define PHY_REG1_val_LINK_STAT       ((1) << PHY_REG1_sft_LINK_STAT      )
#define PHY_REG1_val_EXT_CAPABLE     ((1) << PHY_REG1_sft_EXT_CAPABLE    )
#define PHY_REG1_val_JABBER_DETECT   ((0) << PHY_REG1_sft_JABBER_DETECT  )
#define PHY_REG1_val_ERCAP           ((1) << PHY_REG1_sft_ERCAP          )


/* ------------------------------------------------------------------------- */
/*  Register 02 PHY Identifier Register 1 - PHY_REG1_ID_MSB                  */
/*  ip101    lan8700    rtl8200                                              */
/*    NO       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG2_ID1                 (0x02)
// ID_BIT[18:3]/* Mask for PHY_REG2_ID_MSB */

#define PHY_REG2_sft_OUTI_MSB        (0)  /*16bit*/    /* read 0x001C */

#define PHY_REG2_bit_OUTI_MSB        (0xFFFF)

#define PHY_REG2_val_OUTI_MSB        ((0x001C) << PHY_REG2_sft_OUTI_MSB)


/* ------------------------------------------------------------------------- */
/*  Register 03 PHY Identifier Register 2 - PHY_REG3_ID_LSB                  */
/*  ip101    lan8700    rtl8200                                              */
/*    NO       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG3_ID2                 (0x03)
// ID_BIT[24:19]/* Mask for PHY_REG2_ID_LSB */

#define PHY_REG3_sft_OUTI_LSB        (10)  /*6bit*/    /* read 110010 */
#define PHY_REG3_sft_OUTI_MOD        (4)   /*6bit*/    /* read 000001 */
#define PHY_REG3_sft_OUTI_REV        (0)   /*4bit*/    /* read 0101 */

#define PHY_REG3_bit_OUTI_LSB        (0x3F)
#define PHY_REG3_bit_OUTI_MOD        (0x3F)
#define PHY_REG3_bit_OUTI_REV        (0x0F)

#define PHY_REG3_val_OUTI_LSB        ((0xC8) << PHY_REG3_sft_OUTI_LSB)
#define PHY_REG3_val_OUTI_MOD        ((1)    << PHY_REG3_sft_OUTI_MOD)
#define PHY_REG3_val_OUTI_REV        ((5)    << PHY_REG3_sft_OUTI_REV)


/* ------------------------------------------------------------------------- */
/*  Register 04 Auto-Negotiation Advertisement Register(ANAR)                */
/*  ip101    lan8700    rtl8200                                              */
/*   YES       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG4_ANAR                (0x04)

#define PHY_REG4_sft_ANG_NP          (15)  /*1bit*/    /* read 0 */             /* NP */
#define PHY_REG4_sft_ANG_ACK         (14)  /*1bit*/    /* read 0 */             /* ACK */
#define PHY_REG4_sft_ANG_RF          (13)  /*1bit*/    /* read/write 0 */       /* RF */
#define PHY_REG4_sft_ANG_TXFC        (11)  /*1bit*/    /* read 0 */             /* Try for asymetric pause */
#define PHY_REG4_sft_ANG_RXFC        (10)  /*1bit*/    /* read/write 0 */       /* Try for pause */ /* RXFC */
#define PHY_REG4_sft_ANG_100T4       (9)   /*1bit*/    /* read 0 */             /* T4 *//* Try for 100mbps 4k packets */
#define PHY_REG4_sft_ANG_100TXFD     (8)   /*1bit*/    /* read/write 1 */       /* TXFD */
#define PHY_REG4_sft_ANG_100TX       (7)   /*1bit*/    /* read/write 1 */       /* TX */
#define PHY_REG4_sft_ANG_10FD        (6)   /*1bit*/    /* read/write 1 */       /* 10FD */
#define PHY_REG4_sft_ANG_10T         (5)   /*1bit*/    /* read/write 1 */       /* 10 */
#define PHY_REG4_sft_ANG_SELECTOR    (0)   /*5bit*/    /* read/write 00001 */   /* Only selector supported */

#define PHY_REG4_bit_ANG_NP          (1)
#define PHY_REG4_bit_ANG_ACK         (1)
#define PHY_REG4_bit_ANG_RF          (1)
#define PHY_REG4_bit_ANG_TXFC        (1)
#define PHY_REG4_bit_ANG_RXFC        (1)
#define PHY_REG4_bit_ANG_100T4       (1)
#define PHY_REG4_bit_ANG_100TXFD     (1)
#define PHY_REG4_bit_ANG_100TX       (1)
#define PHY_REG4_bit_ANG_10FD        (1)
#define PHY_REG4_bit_ANG_10T         (1)
#define PHY_REG4_bit_ANG_SELECTOR    (0x1F)

#define PHY_REG4_val_ANG_NP          ((1)    << PHY_REG4_sft_ANG_NP      )
#define PHY_REG4_val_ANG_ACK         ((1)    << PHY_REG4_sft_ANG_ACK     )
#define PHY_REG4_val_ANG_RF          ((1)    << PHY_REG4_sft_ANG_RF      )
#define PHY_REG4_val_ANG_TXFC        ((1)    << PHY_REG4_sft_ANG_TXFC    )
#define PHY_REG4_val_ANG_RXFC        ((1)    << PHY_REG4_sft_ANG_RXFC    )
#define PHY_REG4_val_ANG_100T4       ((1)    << PHY_REG4_sft_ANG_100T4   )
#define PHY_REG4_val_ANG_100TXFD     ((1)    << PHY_REG4_sft_ANG_100TXFD )
#define PHY_REG4_val_ANG_100TX       ((1)    << PHY_REG4_sft_ANG_100TX   )
#define PHY_REG4_val_ANG_10FD        ((1)    << PHY_REG4_sft_ANG_10FD    )
#define PHY_REG4_val_ANG_10T         ((1)    << PHY_REG4_sft_ANG_10T     )
#define PHY_REG4_val_ANG_SELECTOR    ((0x1F) << PHY_REG4_sft_ANG_SELECTOR)
#define PHY_REG4_val_ANG_CSMA        ((1)    << PHY_REG4_sft_ANG_SELECTOR)
#define PHY_REG4_val_ANG_ALL         (PHY_REG4_val_ANG_100TXFD|PHY_REG4_val_ANG_10FD|PHY_REG4_val_ANG_CSMA)
#define PHY_REG4_val_ANG_FULL        (PHY_REG4_val_ANG_10T|PHY_REG4_val_ANG_10FD|PHY_REG4_val_ANG_100TX|PHY_REG4_val_ANG_100TXFD)


/* ------------------------------------------------------------------------- */
/*  Register 05 Auto-Negotiation Link Partner Ability Register(ANLPAR)       */
/*  ip101    lan8700    rtl8200                                              */
/*    NO        NO        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG5_ANLPAR              (0x05)

#define PHY_REG5_sft_LPA_NP          (15)  /*1bit*/    /* read 0 */             /* Next page bit               */
#define PHY_REG5_sft_LPA_ACK         (14)  /*1bit*/    /* read 0 */             /* Link partner acked us       */
#define PHY_REG5_sft_LPA_RF          (13)  /*1bit*/    /* read 0 */             /* Link partner faulted        */
#define PHY_REG5_sft_LPA_TXFC        (11)  /*1bit*/    /* read 0 */             /* TX Flow Control Can pause asymetrically     */
#define PHY_REG5_sft_LPA_RXFC        (10)  /*1bit*/    /* read 0 */             /* RX Flow Control Can pause               */
#define PHY_REG5_sft_LPA_100T4       (9)   /*1bit*/    /* read 0 */             /* Can do 100mbps 4k packets   */
#define PHY_REG5_sft_LPA_1000XP_ASYM (8)   /*1bit*/    /* read 0 */             /* Can do 1000BASE-X pause asym*/
#define PHY_REG5_sft_LPA_100TXFD     (8)   /*1bit*/    /* read 0 */             /* Can do 100mbps full-duplex*/
#define PHY_REG5_sft_LPA_100TX       (7)   /*1bit*/    /* read 0 */             /* Can do 100mbps half-duplex     */
#define PHY_REG5_sft_LPA_1000XHD     (6)   /*1bit*/    /* read 0 */             /* Can do 1000BASE-X half-duplex */
#define PHY_REG5_sft_LPA_10FD        (6)   /*1bit*/    /* read 0 */             /* Can do 10mbps full-duplex   */
#define PHY_REG5_sft_LPA_1000XFD     (5)   /*1bit*/    /* read 0 */             /* Can do 1000BASE-X full-duplex */
#define PHY_REG5_sft_LPA_10T         (5)   /*1bit*/    /* read 0 */             /* Can do 10mbps half-duplex   */
#define PHY_REG5_sft_LPA_SELECTOR    (0)   /*5bit*/    /* read/write 00000 */   /* Only selector supported     */

#define PHY_REG5_bit_LPA_NP          (1)
#define PHY_REG5_bit_LPA_ACK         (1)
#define PHY_REG5_bit_LPA_RF          (1)
#define PHY_REG5_bit_LPA_TXFC        (1)
#define PHY_REG5_bit_LPA_RXFC        (1)
#define PHY_REG5_bit_LPA_100T4       (1)
#define PHY_REG5_bit_LPA_100TXFD     (1)
#define PHY_REG5_bit_LPA_100TX       (1)
#define PHY_REG5_bit_LPA_10FD        (1)
#define PHY_REG5_bit_LPA_10T         (1)
#define PHY_REG5_bit_LPA_SELECTOR    (0x1F)

#define PHY_REG5_val_LPA_NP          ((1)    << PHY_REG5_sft_LPA_NP      )
#define PHY_REG5_val_LPA_ACK         ((1)    << PHY_REG5_sft_LPA_ACK     )
#define PHY_REG5_val_LPA_RF          ((1)    << PHY_REG5_sft_LPA_RF      )
#define PHY_REG5_val_LPA_TXFC        ((1)    << PHY_REG5_sft_LPA_TXFC    )
#define PHY_REG5_val_LPA_RXFC        ((1)    << PHY_REG5_sft_LPA_RXFC    )
#define PHY_REG5_val_LPA_100T4       ((1)    << PHY_REG5_sft_LPA_100T4   )
#define PHY_REG5_val_LPA_100TXFD     ((1)    << PHY_REG5_sft_LPA_100TXFD )
#define PHY_REG5_val_LPA_100TX       ((1)    << PHY_REG5_sft_LPA_100TX   )
#define PHY_REG5_val_LPA_10FD        ((1)    << PHY_REG5_sft_LPA_10FD    )
#define PHY_REG5_val_LPA_10T         ((1)    << PHY_REG5_sft_LPA_10T     )
#define PHY_REG5_val_LPA_SELECTOR    ((0x1F) << PHY_REG5_sft_LPA_SELECTOR)
#define PHY_REG5_val_LPA_CSMA        ((1)    << PHY_REG5_sft_LPA_SELECTOR)
#define PHY_REG5_val_ANLPAR_DUPLEX   (PHY_REG5_val_LPA_10FD|PHY_REG5_val_LPA_100TXFD)
#define PHY_REG5_val_ANLPAR_100      (PHY_REG5_val_LPA_100TX|PHY_REG5_val_LPA_100TXFD|PHY_REG5_val_LPA_100T4)


/* ------------------------------------------------------------------------- */
/*  Register 06 Auto-Negotiation Expansion Register(ANER)                    */
/*  ip101    lan8700    rtl8200                                              */
/*    NO        NO        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG6_ANER                (0x06)

#define PHY_REG6_sft_ANE_MLF         (4)  /*1bit*/    /* read 0 */  /* Multiple link faults detected    */
#define PHY_REG6_sft_ANE_LP_NP_ABLE  (3)  /*1bit*/    /* read 0 */  /* Link partner supports npage */
#define PHY_REG6_sft_ANE_NP_ABL      (2)  /*1bit*/    /* read 0 */  /* This enables npage words    */
#define PHY_REG6_sft_ANE_PAGE_RX     (1)  /*1bit*/    /* read 0 */  /* Got new RX page code word   */
#define PHY_REG6_sft_ANE_LP_NW_ABL   (0)  /*1bit*/    /* read 0 */  /* Can do N-way auto-nego      */

#define PHY_REG6_bit_ANE_MLF         (1)
#define PHY_REG6_bit_ANE_LP_NP_ABLE  (1)
#define PHY_REG6_bit_ANE_NP_ABL      (1)
#define PHY_REG6_bit_ANE_PAGE_RX     (1)
#define PHY_REG6_bit_ANE_LP_NW_ABL   (1)

#define PHY_REG6_val_ANE_MLF         ((1) << PHY_REG6_sft_ANE_MLF       )
#define PHY_REG6_val_ANE_LP_NP_ABLE  ((1) << PHY_REG6_sft_ANE_LP_NP_ABLE)
#define PHY_REG6_val_ANE_NP_ABL      ((1) << PHY_REG6_sft_ANE_NP_ABL    )
#define PHY_REG6_val_ANE_PAGE_RX     ((1) << PHY_REG6_sft_ANE_PAGE_RX   )
#define PHY_REG6_val_ANE_LP_NW_ABL   ((1) << PHY_REG6_sft_ANE_LP_NW_ABL )


/* ------------------------------------------------------------------------- */
/*  Register 16 NWay Setup Register(NSR)                                     */
/*  ip101    lan8700    rtl8200                                              */
/*    NO        NO        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG16_NSR                (0x10)

#define PHY_REG16_sft_NSR_TESTFUN    (10)  /*1bit*/    /* read/write 0 */
#define PHY_REG16_sft_NSR_NWLPBK     (9)   /*1bit*/    /* read/write 0 */
#define PHY_REG16_sft_NSR_FLAGABD    (2)   /*1bit*/    /* read 0 */
#define PHY_REG16_sft_NSR_FLAGFDF    (1)   /*1bit*/    /* read 0 */
#define PHY_REG16_sft_NSR_FLAGLSC    (0)   /*1bit*/    /* read 0 */

#define PHY_REG16_bit_NSR_TESTFUN    (1)
#define PHY_REG16_bit_NSR_NWLPBK     (1)
#define PHY_REG16_bit_NSR_FLAGABD    (1)
#define PHY_REG16_bit_NSR_FLAGFDF    (1)
#define PHY_REG16_bit_NSR_FLAGLSC    (1)

#define PHY_REG16_val_NSR_TESTFUN    ((1) << PHY_REG16_sft_NSR_TESTFUN)
#define PHY_REG16_val_NSR_NWLPBK     ((1) << PHY_REG16_sft_NSR_NWLPBK )
#define PHY_REG16_val_NSR_FLAGABD    ((1) << PHY_REG16_sft_NSR_FLAGABD)
#define PHY_REG16_val_NSR_FLAGFDF    ((1) << PHY_REG16_sft_NSR_FLAGFDF)
#define PHY_REG16_val_NSR_FLAGLSC    ((1) << PHY_REG16_sft_NSR_FLAGLSC)
#define PHY_REG16_val_NSR_RESV       (0xF800)


/* ------------------------------------------------------------------------- */
/*  Register 17 Loopback, Bypass, Receiver Error Mask Register(LBREMR)       */
/*  ip101    lan8700    rtl8200                                              */
/*    NO        NO        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG17_LBREMR             (0x11)

#define PHY_REG17_sft_EMR_RPTR       (15)  /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_BP_4B5B    (14)  /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_BP_SCR     (13)  /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_LPDS       (12)  /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_ANALOGOFF  (11)  /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_BMODE_EN   (10)  /*1bit*/    /* read/write 1 */
#define PHY_REG17_sft_EMR_DIGILBK    (9)   /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_FLINK_10   (8)   /*1bit*/    /* read/write 1 */
#define PHY_REG17_sft_EMR_FLINK_100  (7)   /*1bit*/    /* read/write 1 */
#define PHY_REG17_sft_EMR_JBEN       (6)   /*1bit*/    /* read/write 1 */
#define PHY_REG17_sft_EMR_CODE_ERR   (5)   /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_PME_ERR    (4)   /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_LINK_ERR   (3)   /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_PKT_ERR    (2)   /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_FXMODE     (1)   /*1bit*/    /* read/write 0 */
#define PHY_REG17_sft_EMR_SNIMODE    (0)   /*1bit*/    /* read/write 0 */

#define PHY_REG17_bit_EMR_RPTR       (1)
#define PHY_REG17_bit_EMR_BP_4B5B    (1)
#define PHY_REG17_bit_EMR_BP_SCR     (1)
#define PHY_REG17_bit_EMR_LPDS       (1)
#define PHY_REG17_bit_EMR_ANALOGOFF  (1)
#define PHY_REG17_bit_EMR_BMODE_EN   (1)
#define PHY_REG17_bit_EMR_DIGILBK    (1)
#define PHY_REG17_bit_EMR_FLINK_10   (1)
#define PHY_REG17_bit_EMR_FLINK_100  (1)
#define PHY_REG17_bit_EMR_JBEN       (1)
#define PHY_REG17_bit_EMR_CODE_ERR   (1)
#define PHY_REG17_bit_EMR_PME_ERR    (1)
#define PHY_REG17_bit_EMR_LINK_ERR   (1)
#define PHY_REG17_bit_EMR_PKT_ERR    (1)
#define PHY_REG17_bit_EMR_FXMODE     (1)
#define PHY_REG17_bit_EMR_SNIMODE    (1)

#define PHY_REG17_val_EMR_RPTR       ((1) << PHY_REG17_sft_EMR_RPTR     )
#define PHY_REG17_val_EMR_BP_4B5B    ((1) << PHY_REG17_sft_EMR_BP_4B5B  )
#define PHY_REG17_val_EMR_BP_SCR     ((1) << PHY_REG17_sft_EMR_BP_SCR   )
#define PHY_REG17_val_EMR_LPDS       ((1) << PHY_REG17_sft_EMR_LPDS     )
#define PHY_REG17_val_EMR_ANALOGOFF  ((1) << PHY_REG17_sft_EMR_ANALOGOFF)
#define PHY_REG17_val_EMR_BMODE_EN   ((1) << PHY_REG17_sft_EMR_BMODE_EN )
#define PHY_REG17_val_EMR_DIGILBK    ((1) << PHY_REG17_sft_EMR_DIGILBK  )
#define PHY_REG17_val_EMR_FLINK_10   ((1) << PHY_REG17_sft_EMR_FLINK_10 )
#define PHY_REG17_val_EMR_FLINK_100  ((1) << PHY_REG17_sft_EMR_FLINK_100)
#define PHY_REG17_val_EMR_JBEN       ((1) << PHY_REG17_sft_EMR_JBEN     )
#define PHY_REG17_val_EMR_CODE_ERR   ((1) << PHY_REG17_sft_EMR_CODE_ERR )
#define PHY_REG17_val_EMR_PME_ERR    ((1) << PHY_REG17_sft_EMR_PME_ERR  )
#define PHY_REG17_val_EMR_LINK_ERR   ((1) << PHY_REG17_sft_EMR_LINK_ERR )
#define PHY_REG17_val_EMR_PKT_ERR    ((1) << PHY_REG17_sft_EMR_PKT_ERR  )
#define PHY_REG17_val_EMR_FXMODE     ((1) << PHY_REG17_sft_EMR_FXMODE   )
#define PHY_REG17_val_EMR_SNIMODE    ((1) << PHY_REG17_sft_EMR_SNIMODE  )


/* ------------------------------------------------------------------------- */
/*  Register 18 PHY Special Control/Status Register || RX_ER Counter(REC)    */
/*  ip101    lan8700    rtl8200                                              */
/*   YES       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG18_SCSR               (0x12)

// ip101/lan8700
#define PHY_REG18_sft_RPHY_MODE      (14)  /*1bit*/    /* read/write 0 */
// ip101
#define PHY_REG18_sft_RES_SPEED      (14)  /*1bit*/    /* read/write 0 */
#define PHY_REG18_sft_RES_DUPLEX     (13)  /*1bit*/    /* read/write 0 */
#define PHY_REG18_sft_RES_AN_DONE    (11)  /*1bit*/    /* read/write 0 */
#define PHY_REG18_sft_EMR_LPDS       (10)  /*1bit*/    /* read/write 0 */
// rtl8200
#define PHY_REG18_sft_RXERCNT        (0)   /*16bit*/   /* read/write 0 */

// ip101/lan8700
#define PHY_REG18_bit_RPHY_MODE      (1)
// ip101
#define PHY_REG18_bit_RES_SPEED      (1)
#define PHY_REG18_bit_RES_DUPLEX     (1)
#define PHY_REG18_bit_RES_AN_DONE    (1)
#define PHY_REG18_bit_EMR_LPDS       (1)
// rtl8200
#define PHY_REG18_bit_RXERCNT        (0xFFFF)

// ip101/lan8700
#define PHY_REG18_val_RPHY_RMII      ((1)      << PHY_REG18_sft_RPHY_MODE  )
#define PHY_REG18_val_RPHY_MII       ((0)      << PHY_REG18_sft_RPHY_MODE  )
// ip101
#define PHY_REG18_val_RES_SPEED      ((1)      << PHY_REG18_sft_RES_SPEED  )
#define PHY_REG18_val_RES_DUPLEX     ((1)      << PHY_REG18_sft_RES_DUPLEX )
#define PHY_REG18_val_RES_AN_DONE    ((1)      << PHY_REG18_sft_RES_AN_DONE)
#define PHY_REG18_val_EMR_LPDS       ((1)      << PHY_REG18_sft_EMR_LPDS   )
// rtl8200
#define PHY_REG18_val_RXERCNT        ((0xFFFF) << PHY_REG18_sft_RXERCNT    )


/* ------------------------------------------------------------------------- */
/*  Register 19 SNR Display Register                                         */
/*  ip101    lan8700    rtl8200                                              */
/*    NO        NO        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG19_SNR                (0x13)

// rtl8200
#define PHY_REG19_sft_SNR_0          (0)   /*4bit*/    /* read/write 0 */   /* Signal to Noise Ratio Value */

// rtl8200
#define PHY_REG19_bit_SNR_0          (0x0F)

// rtl8200
#define PHY_REG19_val_SNR_0          ((0x0F) << PHY_REG19_sft_SNR_0)


/* ------------------------------------------------------------------------- */
/*  Register 25 Test Register                                                */
/*  ip101    lan8700    rtl8200                                              */
/*   YES       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG25_TESTR              (0x19)

#define PHY_REG25_sft_PACKET_TYPE    (14)  /*1bit*/
#define PHY_REG25_sft_RPHY_RXD_TRIG  (13)  /*1bit*/
#define PHY_REG25_sft_RPHY_CLKIN     (11)  /*1bit*/
#define PHY_REG25_sft_RPHY_MODE      (10)  /*1bit*/
#define PHY_REG25_sft_RPHY_CRS_SEL   (9)   /*1bit*/
#define PHY_REG25_sft_PHY_AD         (8)   /*2bit*/
#define PHY_REG25_sft_LINK_10        (1)   /*1bit*/     /* 10T Link Established */
#define PHY_REG25_sft_LINK_100       (0)   /*1bit*/     /* 100FX/TX Link Established */

#define PHY_REG25_bit_PACKET_TYPE    (1)
#define PHY_REG25_bit_RPHY_RXD_TRIG  (1)
#define PHY_REG25_bit_RPHY_CLKIN     (1)
#define PHY_REG25_bit_RPHY_MODE      (1)
#define PHY_REG25_bit_RPHY_CRS_SEL   (1)
#define PHY_REG25_bit_PHY_AD         (3)
#define PHY_REG25_bit_LINK_10        (1)
#define PHY_REG25_bit_LINK_100       (1)

#define PHY_REG25_val_PACKET_TYPE    ((1) << PHY_REG25_sft_PACKET_TYPE  )
#define PHY_REG25_val_RPHY_RXD_RISE  ((1) << PHY_REG25_sft_RPHY_RXD_TRIG)
#define PHY_REG25_val_RPHY_RXD_FALL  ((0) << PHY_REG25_sft_RPHY_RXD_TRIG)
#define PHY_REG25_val_RPHY_CLKIN     ((1) << PHY_REG25_sft_RPHY_CLKIN   )
#define PHY_REG25_val_RPHY_CLKOUT    ((0) << PHY_REG25_sft_RPHY_CLKIN   )
#define PHY_REG25_val_RPHY_RMII      ((1) << PHY_REG25_sft_RPHY_MODE    )
#define PHY_REG25_val_RPHY_MII       ((0) << PHY_REG25_sft_RPHY_MODE    )
#define PHY_REG25_val_RPHY_CRS_SEL   ((1) << PHY_REG25_sft_RPHY_CRS_SEL )
#define PHY_REG25_val_PHY_AD         ((1) << PHY_REG25_sft_PHY_AD       )
#define PHY_REG25_val_LINK_10        ((1) << PHY_REG25_sft_LINK_10      )
#define PHY_REG25_val_LINK_100       ((1) << PHY_REG25_sft_LINK_100     )


/* ------------------------------------------------------------------------- */
/*  Register 31 PHY Special Control/Status                                   */
/*  ip101    lan8700    rtl8200                                              */
/*   YES       YES        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_REG31_SCSR               (0x1F)

#define PHY_REG31_sft_AN_DONE        (12)  /*1bit*/
#define PHY_REG31_sft_GPO            (7)   /*2bit*/
#define PHY_REG31_sft_EN_4B5B        (6)   /*1bit*/
#define PHY_REG31_sft_SPEED          (2)   /*3bit*/
#define PHY_REG31_sft_DIS_SCRBL      (0)   /*1bit*/
// rtl8200
#define PHY_REG31_sft_PAGE_SEL       (0)   /*2bit*/


#define PHY_REG31_bit_AN_DONE        (1)
#define PHY_REG31_bit_GPO            (3)
#define PHY_REG31_bit_EN_4B5B        (1)
#define PHY_REG31_bit_SPEED          (7)
#define PHY_REG31_bit_DIS_SCRBL      (1)
// rtl8200
#define PHY_REG31_bit_PAGE_SEL       (3)

#define PHY_REG31_val_AN_DONE        ((1) << PHY_REG31_sft_AN_DONE  )
#define PHY_REG31_val_GPO            ((1) << PHY_REG31_sft_GPO      )
#define PHY_REG31_val_EN_4B5B        ((1) << PHY_REG31_sft_EN_4B5B  )
#define PHY_REG31_val_10M_HALF       ((1) << PHY_REG31_sft_SPEED    )
#define PHY_REG31_val_10M_FULL       ((5) << PHY_REG31_sft_SPEED    )
#define PHY_REG31_val_100M_HALF      ((2) << PHY_REG31_sft_SPEED    )
#define PHY_REG31_val_100M_FULL      ((6) << PHY_REG31_sft_SPEED    )
#define PHY_REG31_val_DIS_SCRBL      ((1) << PHY_REG31_sft_DIS_SCRBL)
// rtl8200
#define PHY_REG31_val_PAGE_0         ((0) << PHY_REG31_sft_PAGE_SEL )
#define PHY_REG31_val_PAGE_1         ((1) << PHY_REG31_sft_PAGE_SEL )
#define PHY_REG31_val_PAGE_2         ((2) << PHY_REG31_sft_PAGE_SEL )


/* ------------------------------------------------------------------------- */
/*  Page 1 Register 16 Interrupt Status Register                             */
/*  ip101    lan8700    rtl8200                                              */
/*    NO        NO        YES                                                */
/* ------------------------------------------------------------------------- */
#define PHY_P1_REG16_ISR             (0x10)

#define PHY_P1_REG16_sft_ANERR       (15)  /*1bit*/        /* read 0 */
#define PHY_P1_REG16_sft_LNKSTS      (14)  /*1bit*/        /* read 0 */
#define PHY_P1_REG16_sft_DUPLEX      (13)  /*1bit*/        /* read 0 */

#define PHY_P1_REG16_bit_ANERR       (1)
#define PHY_P1_REG16_bit_LNKSTS      (1)
#define PHY_P1_REG16_bit_DUPLEX      (1)

#define PHY_P1_REG16_val_ANERR       ((1) << PHY_P1_REG16_sft_ANERR )
#define PHY_P1_REG16_val_LNKSTS      ((1) << PHY_P1_REG16_sft_LNKSTS)
#define PHY_P1_REG16_val_DUPLEX      ((1) << PHY_P1_REG16_sft_DUPLEX)



//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif



#endif /* _GD_ETH_PHY_REG_H_ */

