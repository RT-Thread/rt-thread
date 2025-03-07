/*
 * Copyright (c) 2022, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __USB_DC_AIC_REG_H__
#define __USB_DC_AIC_REG_H__

#define __IO volatile               /*!< Defines 'read / write' permissions */

typedef struct {
    __IO uint32_t ahbbasic;         /* 0x0000: AHBBASIC */
    __IO uint32_t usbdevinit;       /* 0x0004: USBDEVINIT */
    __IO uint32_t usbphyif;         /* 0x0008: USBPHYIF */
    __IO uint32_t usbulpiphy;       /* 0x000C: USBULPIPHY */
    __IO uint32_t usbintsts;        /* 0x0010: USBINTSTS */
    __IO uint32_t usbintmsk;        /* 0x0014: USBINTMSK */
    __IO uint32_t rxfifosiz;        /* 0x0018: RXFIFOSIZ */
    __IO uint32_t rxfifosts_pop;    /* 0x001C: RXFIFOSTS pop */
    __IO uint32_t nptxfifosiz;      /* 0x0020: NPTXFIFOSIZ */
    __IO uint32_t nptxfifosts;      /* 0x0024: NPTXFIFOSTS */
    __IO uint32_t txfifosiz[2];     /* 0x0028 - 0x002C: TXFIFOSIZ() */
    __IO uint32_t rxfifosts_dbg;    /* 0x0030: RXFIFOSTS_DBG */
    uint8_t  res0[0x1cc];
    __IO uint32_t usbdevconf;       /* 0x0200: USBDEVCONF */
    __IO uint32_t usbdevfunc;       /* 0x0204: USBDEVFUNC */
    __IO uint32_t usblinests;       /* 0x0208: USBLINESTS */
    __IO uint32_t inepintmsk;       /* 0x020C: INEPINTMSK */
    __IO uint32_t outepintmsk;      /* 0x0210: OUTEPINTMSK */
    __IO uint32_t usbepint;         /* 0x0214: USBEPINT */
    __IO uint32_t usbepintmsk;      /* 0x0218: USBEPINTMSK */
    uint8_t  res1[4];
    __IO uint32_t inepcfg[5];       /* 0x0220 - 0x0230: INEPCFG() */
    uint8_t  res2[0xc];
    __IO uint32_t outepcfg[5];      /* 0x0240 - 0x0250: OUTEPCFG() */
    uint8_t  res3[0xc];
    __IO uint32_t inepint[5];       /* 0x0260 - 0x0270: INEPINT() */
    uint8_t  res4[0xc];
    __IO uint32_t outepint[5];      /* 0x0280 - 0x0290: OUTEPINT() */
    uint8_t  res5[0xc];
    __IO uint32_t ineptsfsiz[5];    /* 0x02A0 - 0x02B0: INEPTSFSIZ() */
    uint8_t  res6[0xc];
    __IO uint32_t outeptsfsiz[5];   /* 0x02C0 - 0x02D0: OUTEPTSFSIZ() */
    uint8_t  res7[0x2c];
    __IO uint32_t inepdmaaddr[5];   /* 0x0300 - 0x0310: INEPDMAADDR() */
    uint8_t  res8[0xc];
    __IO uint32_t outepdmaaddr[5];  /* 0x0320 - 0x0330: OUTEPDMAADDR() */
    uint8_t  res9[0xc];
    __IO uint32_t ineptxsts[5];     /* 0x0340 - 0x0350: INEPTXSTS() */
    uint8_t  res10[0xc];
    __IO uint32_t dtknqr1;          /* 0x0360: DTKNQR1 */
    __IO uint32_t dtknqr2;          /* 0x0364: DTKNQR2 */
    __IO uint32_t dtknqr3;          /* 0x0368: DTKNQR3 */
    __IO uint32_t dtknqr4;          /* 0x036C: DTKNQR4 */
}AIC_UDC_RegDef;

/*===================================================================== */
/*definitions related to CSR setting */

/* AHBBASIC */
#define AHBBASIC_NOTI_ALL_DMA_WRIT      (1 << 8)
#define AHBBASIC_REM_MEM_SUPP           (1 << 7)
#define AHBBASIC_INV_DESC_ENDIANNESS    (1 << 6)
#define AHBBASIC_AHB_SINGLE             (1 << 5)
#define AHBBASIC_TXENDDELAY             (1 << 3)
#define AHBBASIC_AHBIDLE                (1 << 2)
#define AHBBASIC_DMAREQ                 (1 << 1)

/* USBDEVINIT */
#define USBDEVINIT_HBSTLEN_MASK         (0xf << 12)
#define USBDEVINIT_HBSTLEN_SHIFT        12
#define USBDEVINIT_HBSTLEN_SINGLE       0
#define USBDEVINIT_HBSTLEN_INCR         1
#define USBDEVINIT_HBSTLEN_INCR4        3
#define USBDEVINIT_HBSTLEN_INCR8        5
#define USBDEVINIT_HBSTLEN_INCR16       7
#define USBDEVINIT_DMA_EN               (1 << 11)
#define USBDEVINIT_NP_TXF_EMP_LVL       (1 << 10)
#define USBDEVINIT_GLBL_INTR_EN         (1 << 9)
#define USBDEVINIT_CTRL_MASK            (USBDEVINIT_NP_TXF_EMP_LVL | \
                                         USBDEVINIT_DMA_EN | \
                                         USBDEVINIT_GLBL_INTR_EN)
#define USBDEVINIT_IN_TKNQ_FLSH         (1 << 8)
#define USBDEVINIT_TXFNUM_MASK          (0x1f << 3)
#define USBDEVINIT_TXFNUM_SHIFT         3
#define USBDEVINIT_TXFNUM_LIMIT         0x1f
#define USBDEVINIT_TXFNUM(_x)           ((_x) << 3)
#define USBDEVINIT_TXFFLSH              (1 << 2)
#define USBDEVINIT_RXFFLSH              (1 << 1)
#define USBDEVINIT_CSFTRST              (1 << 0)

/* USBPHYIF */
#define USBPHYIF_ULPI_CLK_SUSP_M        (1 << 19)
#define USBPHYIF_ULPI_AUTO_RES          (1 << 18)
#define USBPHYIF_PHY_LP_CLK_SEL         (1 << 15)
#define USBPHYIF_USBTRDTIM_MASK         (0xf << 10)
#define USBPHYIF_USBTRDTIM_SHIFT        10
#ifndef USBPHYIF_HS_TRDT_VALUE
#define USBPHYIF_HS_TRDT_VALUE          9U
#endif /* USBD_HS_TRDT_VALUE */
#ifndef USBPHYIF_FS_TRDT_VALUE
#define USBPHYIF_FS_TRDT_VALUE          5U
#define USBPHYIF_DEFAULT_TRDT_VALUE     9U
#endif /* USBD_HS_TRDT_VALUE */
#define USBPHYIF_DDRSEL                 (1 << 7)
#define USBPHYIF_ULPI_UTMI_SEL          (1 << 4)
#define USBPHYIF_PHYIF16                (1 << 3)
#define USBPHYIF_PHYIF8                 (0 << 3)
#define USBPHYIF_TOUTCAL_MASK           (0x7 << 0)
#define USBPHYIF_TOUTCAL_SHIFT          0
#define USBPHYIF_TOUTCAL_LIMIT          0x7
#define USBPHYIF_TOUTCAL(_x)            ((_x) << 0)

/* USBINTSTS/USBINTMSK interrupt register */
#define INT_RESUME                      (1u << 31)
#define INT_INCOMP_ISO_OUT_INT          (0x1 << 21)
#define INT_INCOMP_ISO_IN_INT           (0x1 << 20)
#define INT_OUT_EP                      (0x1 << 19)
#define INT_IN_EP                       (0x1 << 18)
#define INT_ENUMDONE                    (0x1 << 13)
#define INT_RESET                       (0x1 << 12)
#define INT_SUSPEND                     (0x1 << 11)
#define INT_EARLY_SUSPEND               (0x1 << 10)
#define INT_GOUTNAKEFF                  (0x1 << 7)
#define INT_GINNAKEFF                   (0x1 << 6)
#define INT_NP_TX_FIFO_EMPTY            (0x1 << 5)
#define INT_RX_FIFO_NOT_EMPTY           (0x1 << 4)
#define INT_SOF                         (0x1 << 3)

#define FULL_SPEED_CONTROL_PKT_SIZE     8
#define FULL_SPEED_BULK_PKT_SIZE        64

#define HIGH_SPEED_CONTROL_PKT_SIZE     64
#define HIGH_SPEED_BULK_PKT_SIZE        512

#define RX_FIFO_SIZE                    (1024)
#define NPTX_FIFO_SIZE                  (1024)
#define PTX_FIFO_SIZE                   (384)

/* fifo size configure */
#define EPS_NUM                         5
#define PERIOD_IN_EP_NUM                2
#define TOTAL_FIFO_SIZE                 0x3f6
#define AIC_RX_FIFO_SIZE                0x119
#define AIC_NP_TX_FIFO_SIZE             0x100
#define AIC_PERIOD_TX_FIFO1_SIZE        0x100
#define AIC_PERIOD_TX_FIFO2_SIZE        0xDD

#define DEPCTL_TXFNUM_0                 (0x0 << 22)
#define DEPCTL_TXFNUM_1                 (0x1 << 22)
#define DEPCTL_TXFNUM_2                 (0x2 << 22)
#define DEPCTL_TXFNUM_3                 (0x3 << 22)
#define DEPCTL_TXFNUM_4                 (0x4 << 22)

/* RXFIFOSTS */
#define RXFIFOSTS_EPNUM_MASK            (0xFU << 0)
#define RXFIFOSTS_BCNT_MASK             (0x7FFU << 4)
#define RXFIFOSTS_DPID_MASK             (0x3U << 15)
#define RXFIFOSTS_PKTSTS_SHIFT          (17)
#define RXFIFOSTS_PKTSTS_MASK           (0xFU << RXFIFOSTS_PKTSTS_SHIFT)
#define PKTSTS_GLOBAL_OUT_NAK           (0x1 << RXFIFOSTS_PKTSTS_SHIFT)
#define PKTSTS_OUT_DATA_PKT_REC         (0x2 << RXFIFOSTS_PKTSTS_SHIFT)
#define PKTSTS_OUT_TRANSFER_COMP        (0x3 << RXFIFOSTS_PKTSTS_SHIFT)
#define PKTSTS_SETUP_TRANSACTION_COMP   (0x4 << RXFIFOSTS_PKTSTS_SHIFT)
#define PKTSTS_SETUP_DATA_PKT_REC       (0x6 << RXFIFOSTS_PKTSTS_SHIFT)
#define RXFIFOSTS_FN_MASK               (0xFU << 21)

/* USBDEVCONF */
#define DEV_SPEED_HIGH_SPEED_20         (0x0 << 0)
#define DEV_SPEED_FULL_SPEED_20         (0x1 << 0)
#define DEV_SPEED_LOW_SPEED_11          (0x2 << 0)
#define DEV_SPEED_FULL_SPEED_11         (0x3 << 0)
#define EP_MISS_CNT(x)                  (x << 18)
#define DEVICE_ADDRESS_MASK             (0x7F << 4)
#define DEVICE_ADDRESS(x)               (x << 4)
#define PERIOD_FRAME_INTERVAL_80        (0 << 11)
#define PERIOD_FRAME_INTERVAL_85        (1 << 11)
#define PERIOD_FRAME_INTERVAL_90        (2 << 11)
#define PERIOD_FRAME_INTERVAL_95        (3 << 11)

/* USBDEVFUNC */
#define NORMAL_OPERATION                (0x1 << 0)
#define SOFT_DISCONNECT                 (0x1 << 1)
#define USBDEVFUNC_SERVICE_INTERVAL_SUPPORTED (1 << 19)
#define USBDEVFUNC_PWRONPRGDONE         (1 << 11)
#define USBDEVFUNC_CGOUTNAK             (1 << 10)
#define USBDEVFUNC_SGOUTNAK             (1 << 9)
#define USBDEVFUNC_CGNPINNAK            (1 << 8)
#define USBDEVFUNC_SGNPINNAK            (1 << 7)
#define USBDEVFUNC_TSTCTL_MASK          (0x7 << 4)
#define USBDEVFUNC_TSTCTL_SHIFT         (4)
#define USBDEVFUNC_GOUTNAKSTS           (1 << 3)
#define USBDEVFUNC_GNPINNAKSTS          (1 << 2)
#define USBDEVFUNC_SFTDISCON            (1 << 1)
#define USBDEVFUNC_RMTWKUPSIG           (1 << 0)

/* USBLINESTS: Enumeration speed */
#define USB_ENUM_SPEED_SHIFT            1
#define USB_ENUM_SPEED_MASK             (0x3 << USB_ENUM_SPEED_SHIFT)
#define USB_ENUM_SPEED_HIGH             0
#define USB_ENUM_SPEED_FULL             1
#define USB_HIGH_30_60MHZ               (0x0 << USB_ENUM_SPEED_SHIFT)
#define USB_FULL_30_60MHZ               (0x1 << USB_ENUM_SPEED_SHIFT)
#define USB_LOW_6MHZ                    (0x2 << USB_ENUM_SPEED_SHIFT)
#define USB_FULL_48MHZ                  (0x3 << USB_ENUM_SPEED_SHIFT)

/* USBEPINT endpoint interrupt register */
#define DAINT_OUT_BIT                   (16)
#define DAINT_IN_MASK                   (0xFFFF)
#define DAINT_OUT_MASK                  (0xFFFFU << DAINT_OUT_BIT)

/* INEPCFG()/OUTEPCFG()
 * devicecontrol IN/OUT endpoint 0 control register
 */
#define DEPCTL_EPENA                    (1u << 31)
#define DEPCTL_EPDIS                    (0x1 << 30)
#define DEPCTL_SETD1PID                 (0x1 << 29)
#define DEPCTL_SETD0PID                 (0x1 << 28)
#define DEPCTL_SNAK                     (0x1 << 27)
#define DEPCTL_CNAK                     (0x1 << 26)
#define DEPCTL_TXFIFONUM_SHIFT          22
#define DEPCTL_TXFIFONUM_MASK           (0xF << 22)
#define DEPCTL_STALL                    (0x1 << 21)
#define DEPCTL_TYPE_BIT                 (18)
#define DEPCTL_TYPE_MASK                (0x3 << 18)
#define DEPCTL_CTRL_TYPE                (0x0 << 18)
#define DEPCTL_ISO_TYPE                 (0x1 << 18)
#define DEPCTL_BULK_TYPE                (0x2 << 18)
#define DEPCTL_INTR_TYPE                (0x3 << 18)
#define DEPCTL_USBACTEP                 (0x1 << 15)
#define DEPCTL_NEXT_EP_BIT              (11)
#define DEPCTL_NEXT_EP_MASK             (0xFU << DEPCTL_NEXT_EP_BIT)
#define DEPCTL_MPS_BIT                  (0)
#define DEPCTL_MPS_MASK                 (0x7FF)

#define DEPCTL0_MPS_64                  (0x0 << 0)
#define DEPCTL0_MPS_32                  (0x1 << 0)
#define DEPCTL0_MPS_16                  (0x2 << 0)
#define DEPCTL0_MPS_8                   (0x3 << 0)
#define DEPCTL_MPS_BULK_512             (512 << 0)
#define DEPCTL_MPS_INT_MPS_16           (16 << 0)

#define DIEPCTL0_NEXT_EP_BIT            (11)

/* INEPINT/OUTEPINT device IN/OUT endpoint interrupt register */
#define TXFIFO_EMP_INT                  (0x1 << 7)
#define INEP_NAKEFF                     (0x1 << 6)
#define BACK2BACK_SETUP_RECEIVED        (0x1 << 6)
#define INTKNEPMIS                      (0x1 << 5)
#define INTKN_TXFEMP                    (0x1 << 4)
#define NON_ISO_IN_EP_TIMEOUT           (0x1 << 3)
#define CTRL_OUT_EP_SETUP_PHASE_DONE    (0x1 << 3)
#define AHB_ERROR                       (0x1 << 2)
#define EPDISBLD                        (0x1 << 1)
#define TRANSFER_DONE                   (0x1 << 0)

/* Masks definitions */
#define GINTMSK_INIT                    (INT_OUT_EP | INT_IN_EP | INT_RESUME | INT_ENUMDONE\
                                        | INT_RESET | INT_SUSPEND)
#define DOEPMSK_INIT                    (CTRL_OUT_EP_SETUP_PHASE_DONE |\
                                        AHB_ERROR | TRANSFER_DONE)
#define DIEPMSK_INIT                    (NON_ISO_IN_EP_TIMEOUT | AHB_ERROR | TRANSFER_DONE)
#define GAHBCFG_INIT                    (USBDEVINIT_DMA_EN | USBDEVINIT_GLBL_INTR_EN\
                                        | (USBDEVINIT_HBSTLEN_INCR4 <<\
                                        USBDEVINIT_HBSTLEN_SHIFT))

/* INEPTSFSIZ/OUTEPTSFSIZ */
#define DXEPTSIZ_MULCNT_SHIFT           29
#define DXEPTSIZ_MULCNT_MASK            (0x3U << DXEPTSIZ_MULCNT_SHIFT)
#define DXEPTSIZ_PKT_CNT_SHIFT          19
#define DXEPTSIZ_PKT_CNT_MASK           (0x3FFU << DXEPTSIZ_PKT_CNT_SHIFT)
#define DXEPTSIZ_XFER_SIZE_SHIFT        0
#define DXEPTSIZ_XFER_SIZE_MASK         (0x7FFFFU << DXEPTSIZ_XFER_SIZE_SHIFT)

/* Device Endpoint X Transfer Size Register INEPTSFSIZ() */
#define DIEPT_SIZ_PKT_CNT(x)            (x << 19)
#define DIEPT_SIZ_XFER_SIZE(x)          (x << 0)

/* Device OUT Endpoint X Transfer Size Register OUTEPTSFSIZ() */
#define DOEPT_SIZ_PKT_CNT(x)            (x << 19)
#define DOEPT_SIZ_XFER_SIZE(x)          (x << 0)
#define DOEPT_SIZ_XFER_SIZE_MAX_EP0     (0x7F << 0)
#define DOEPT_SIZ_XFER_SIZE_MAX_EP      (0x7FFF << 0)

/* Device Endpoint-N Control Register INEPCFG()/OUTEPCFG() */
#define DIEPCTL_TX_FIFO_NUM(x)          (x << 22)
#define DIEPCTL_TX_FIFO_NUM_MASK        (~DIEPCTL_TX_FIFO_NUM(0xF))

/* Device ALL Endpoints Interrupt Register (USBEPINT) */
#define DAINT_IN_EP_INT(x)              (x << 0)
#define DAINT_OUT_EP_INT(x)             (x << 16)

#define AIC_EP_FIFO_BASE                0x1000UL
#define AIC_EP_FIFO_SIZE                0x1000UL

/* In EPn Txfifo Status (INEPTXSTS) */
#define INEPTXSTS_IN_EP_TXFIFO_STS      (0xFFFFU << 0)


#endif
