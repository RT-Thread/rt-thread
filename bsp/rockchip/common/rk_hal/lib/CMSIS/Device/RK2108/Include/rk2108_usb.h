/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#ifndef __RK2108_USB_H
#define __RK2108_USB_H
#ifdef __cplusplus
  extern "C" {
#endif
/****************************************************************************************/
/*                                                                                      */
/*                               Module Structure Section                               */
/*                                                                                      */
/****************************************************************************************/
#ifndef __ASSEMBLY__
/* USB_OTG_CORE Register Structure Define */
struct USB_GLOBAL_REG {
    __IO uint32_t GOTGCTL;                            /* Address Offset: 0x0000 */
    __IO uint32_t GOTGINT;                            /* Address Offset: 0x0004 */
    __IO uint32_t GAHBCFG;                            /* Address Offset: 0x0008 */
    __IO uint32_t GUSBCFG;                            /* Address Offset: 0x000C */
    __IO uint32_t GRSTCTL;                            /* Address Offset: 0x0010 */
    __IO uint32_t GINTSTS;                            /* Address Offset: 0x0014 */
    __IO uint32_t GINTMSK;                            /* Address Offset: 0x0018 */
    __IO uint32_t GRXSTSR;                            /* Address Offset: 0x001C */
    __IO uint32_t GRXSTSP;                            /* Address Offset: 0x0020 */
    __IO uint32_t GRXFSIZ;                            /* Address Offset: 0x0024 */
    __IO uint32_t DIEPTXF0_HNPTXFSIZ;                 /* Address Offset: 0x0028 */
    __IO uint32_t HNPTXSTS;                           /* Address Offset: 0x002C */
         uint32_t RESERVED0[2];                       /* Address Offset: 0x0030 */
    __IO uint32_t GGPIO;                              /* Address Offset: 0x0038 */
    __IO uint32_t GUID;                               /* Address Offset: 0x003C */
    __O  uint32_t GSNPSID;                            /* Address Offset: 0x0040 */
    __O  uint32_t GHWCFG1;                            /* Address Offset: 0x0044 */
    __O  uint32_t GHWCFG2;                            /* Address Offset: 0x0048 */
    __O  uint32_t GHWCFG3;                            /* Address Offset: 0x004C */
    __O  uint32_t GHWCFG4;                            /* Address Offset: 0x0050 */
    __IO uint32_t GLPMCFG;                            /* Address Offset: 0x0054 */
    __IO uint32_t GPWRDN;                             /* Address Offset: 0x0058 */
    __IO uint32_t GDFIFOCFG;                          /* Address Offset: 0x005C */
    __IO uint32_t GADPCTL;                            /* Address Offset: 0x0060 */
         uint32_t RESERVED1[39];                      /* Address Offset: 0x0064 */
    __IO uint32_t HPTXFSIZ;                           /* Address Offset: 0x0100 */
    __IO uint32_t DIEPTXF[0x0F];                      /* Address Offset: 0x0104 */
};
/* USB_OTG_DEV Register Structure Define */
struct USB_DEVICE_REG {
    __IO uint32_t DCFG;                               /* Address Offset: 0x0800 */
    __IO uint32_t DCTL;                               /* Address Offset: 0x0804 */
    __IO uint32_t DSTS;                               /* Address Offset: 0x0808 */
         uint32_t RESERVED0;                          /* Address Offset: 0x080C */
    __IO uint32_t DIEPMSK;                            /* Address Offset: 0x0810 */
    __IO uint32_t DOEPMSK;                            /* Address Offset: 0x0814 */
    __IO uint32_t DAINT;                              /* Address Offset: 0x0818 */
    __IO uint32_t DAINTMSK;                           /* Address Offset: 0x081C */
         uint32_t RESERVED1[2];                       /* Address Offset: 0x0820 */
    __IO uint32_t DVBUSDIS;                           /* Address Offset: 0x0828 */
    __IO uint32_t DVBUSPULSE;                         /* Address Offset: 0x082C */
    __IO uint32_t DTHRCTL;                            /* Address Offset: 0x0830 */
    __IO uint32_t DIEPEMPMSK;                         /* Address Offset: 0x0834 */
    __IO uint32_t DEACHINT;                           /* Address Offset: 0x0838 */
    __IO uint32_t DEACHMSK;                           /* Address Offset: 0x083C */
         uint32_t RESERVED2;                          /* Address Offset: 0x0840 */
    __IO uint32_t DINEP1MSK;                          /* Address Offset: 0x0844 */
         uint32_t RESERVED3[15];                      /* Address Offset: 0x0848 */
    __IO uint32_t DOUTEP1MSK;                         /* Address Offset: 0x0884 */
};
/* USB_OTG_DEV_IN_ENDPOINT Register Structure Define */
struct USB_IN_EP_REG {
    __IO uint32_t DIEPCTL;           /* Address Offset: 900h + (ep_num * 20h) + 00h */
         uint32_t RESERVED0;         /* Address Offset: 900h + (ep_num * 20h) + 04h */
    __IO uint32_t DIEPINT;           /* Address Offset: 900h + (ep_num * 20h) + 08h */
         uint32_t RESERVED1;         /* Address Offset: 900h + (ep_num * 20h) + 0Ch */
    __IO uint32_t DIEPTSIZ;          /* Address Offset: 900h + (ep_num * 20h) + 10h */
    __IO uint32_t DIEPDMA;           /* Address Offset: 900h + (ep_num * 20h) + 14h */
    __IO uint32_t DTXFSTS;           /* Address Offset: 900h + (ep_num * 20h) + 18h */
         uint32_t RESERVED2;         /* Address Offset: 900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch */
};
/* USB_OTG_DEV_OUT_ENDPOINT Register Structure Define */
struct USB_OUT_EP_REG {
    __IO uint32_t DOEPCTL;            /* Address Offset: B00h + (ep_num * 20h) + 00h */
         uint32_t RESERVED0;          /* Address Offset: B00h + (ep_num * 20h) + 04h */
    __IO uint32_t DOEPINT;            /* Address Offset: B00h + (ep_num * 20h) + 08h */
         uint32_t RESERVED1;          /* Address Offset: B00h + (ep_num * 20h) + 0Ch */
    __IO uint32_t DOEPTSIZ;           /* Address Offset: B00h + (ep_num * 20h) + 10h */
    __IO uint32_t DOEPDMA;            /* Address Offset: B00h + (ep_num * 20h) + 14h */
         uint32_t RESERVED2[2];       /* Address Offset: B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch */
};
/* USB_OTG_HOST Register Structure Define */
struct USB_HOST_REG {
    __IO uint32_t HCFG;                               /* Address Offset: 0x0400 */
    __IO uint32_t HFIR;                               /* Address Offset: 0x0404 */
    __IO uint32_t HFNUM;                              /* Address Offset: 0x0408 */
         uint32_t RESERVED0;                          /* Address Offset: 0x040C */
    __IO uint32_t HPTXSTS;                            /* Address Offset: 0x0410 */
    __IO uint32_t HAINT;                              /* Address Offset: 0x0414 */
    __IO uint32_t HAINTMSK;                           /* Address Offset: 0x0418 */
};
/* USB_OTG_HOST_CHANNEL Register Structure Define */
struct USB_HOST_CH_REG {
    __IO uint32_t HCCHAR;                             /* Address Offset: 0x0500 */
    __IO uint32_t HCSPLT;                             /* Address Offset: 0x0504 */
    __IO uint32_t HCINT;                              /* Address Offset: 0x0508 */
    __IO uint32_t HCINTMSK;                           /* Address Offset: 0x050C */
    __IO uint32_t HCTSIZ;                             /* Address Offset: 0x0510 */
    __IO uint32_t HCDMA;                              /* Address Offset: 0x0514 */
         uint32_t RESERVED0[2];                       /* Address Offset: 0x0518 */
};
#endif /* __ASSEMBLY__ */
/****************************************************************************************/
/*                                                                                      */
/*                               Module Variable Section                                */
/*                                                                                      */
/****************************************************************************************/
/* Module Variable Define */
#define USB                 ((struct USB_GLOBAL_REG *) USB_BASE)

#define IS_PCD_INSTANCE(instance) ((instance) == USB)
#define IS_HCD_INSTANCE(instance) ((instance) == USB)
/****************************************************************************************/
/*                                                                                      */
/*                               Register Bitmap Section                                */
/*                                                                                      */
/****************************************************************************************/
/***************************************USB_OTG_GOTGCTL*********************************/
#define USB_OTG_GOTGCTL_SRQSCS_SHIFT             (0U)
#define USB_OTG_GOTGCTL_SRQSCS_MASK              (0x1U << USB_OTG_GOTGCTL_SRQSCS_SHIFT) /* 0x00000001 */
#define USB_OTG_GOTGCTL_SRQSCS                   USB_OTG_GOTGCTL_SRQSCS_MASK    /* Session request success */
#define USB_OTG_GOTGCTL_SRQ_SHIFT                (1U)
#define USB_OTG_GOTGCTL_SRQ_MASK                 (0x1U << USB_OTG_GOTGCTL_SRQ_SHIFT) /* 0x00000002 */
#define USB_OTG_GOTGCTL_SRQ                      USB_OTG_GOTGCTL_SRQ_MASK       /* Session request */
#define USB_OTG_GOTGCTL_VBVALOEN_SHIFT           (2U)
#define USB_OTG_GOTGCTL_VBVALOEN_MASK            (0x1U << USB_OTG_GOTGCTL_VBVALOEN_SHIFT) /* 0x00000004 */
#define USB_OTG_GOTGCTL_VBVALOEN                 USB_OTG_GOTGCTL_VBVALOEN_MASK  /* VBUS valid override enable */
#define USB_OTG_GOTGCTL_VBVALOVAL_SHIFT          (3U)
#define USB_OTG_GOTGCTL_VBVALOVAL_MASK           (0x1U << USB_OTG_GOTGCTL_VBVALOVAL_SHIFT) /* 0x00000008 */
#define USB_OTG_GOTGCTL_VBVALOVAL                USB_OTG_GOTGCTL_VBVALOVAL_MASK /* VBUS valid override value */
#define USB_OTG_GOTGCTL_AVALOEN_SHIFT            (4U)
#define USB_OTG_GOTGCTL_AVALOEN_MASK             (0x1U << USB_OTG_GOTGCTL_AVALOEN_SHIFT) /* 0x00000010 */
#define USB_OTG_GOTGCTL_AVALOEN                  USB_OTG_GOTGCTL_AVALOEN_MASK   /* A-peripheral session valid override enable */
#define USB_OTG_GOTGCTL_AVALOVAL_SHIFT           (5U)
#define USB_OTG_GOTGCTL_AVALOVAL_MASK            (0x1U << USB_OTG_GOTGCTL_AVALOVAL_SHIFT) /* 0x00000020 */
#define USB_OTG_GOTGCTL_AVALOVAL                 USB_OTG_GOTGCTL_AVALOVAL_MASK  /* A-peripheral session valid override value */
#define USB_OTG_GOTGCTL_BVALOEN_SHIFT            (6U)
#define USB_OTG_GOTGCTL_BVALOEN_MASK             (0x1U << USB_OTG_GOTGCTL_BVALOEN_SHIFT) /* 0x00000040 */
#define USB_OTG_GOTGCTL_BVALOEN                  USB_OTG_GOTGCTL_BVALOEN_MASK   /* B-peripheral session valid override enable */
#define USB_OTG_GOTGCTL_BVALOVAL_SHIFT           (7U)
#define USB_OTG_GOTGCTL_BVALOVAL_MASK            (0x1U << USB_OTG_GOTGCTL_BVALOVAL_SHIFT) /* 0x00000080 */
#define USB_OTG_GOTGCTL_BVALOVAL                 USB_OTG_GOTGCTL_BVALOVAL_MASK  /* B-peripheral session valid override value */
#define USB_OTG_GOTGCTL_HNGSCS_SHIFT             (8U)
#define USB_OTG_GOTGCTL_HNGSCS_MASK              (0x1U << USB_OTG_GOTGCTL_HNGSCS_SHIFT) /* 0x00000100 */
#define USB_OTG_GOTGCTL_HNGSCS                   USB_OTG_GOTGCTL_HNGSCS_MASK    /* Host set HNP enable */
#define USB_OTG_GOTGCTL_HNPRQ_SHIFT              (9U)
#define USB_OTG_GOTGCTL_HNPRQ_MASK               (0x1U << USB_OTG_GOTGCTL_HNPRQ_SHIFT) /* 0x00000200 */
#define USB_OTG_GOTGCTL_HNPRQ                    USB_OTG_GOTGCTL_HNPRQ_MASK     /* HNP request */
#define USB_OTG_GOTGCTL_HSHNPEN_SHIFT            (10U)
#define USB_OTG_GOTGCTL_HSHNPEN_MASK             (0x1U << USB_OTG_GOTGCTL_HSHNPEN_SHIFT) /* 0x00000400 */
#define USB_OTG_GOTGCTL_HSHNPEN                  USB_OTG_GOTGCTL_HSHNPEN_MASK   /* Host set HNP enable */
#define USB_OTG_GOTGCTL_DHNPEN_SHIFT             (11U)
#define USB_OTG_GOTGCTL_DHNPEN_MASK              (0x1U << USB_OTG_GOTGCTL_DHNPEN_SHIFT) /* 0x00000800 */
#define USB_OTG_GOTGCTL_DHNPEN                   USB_OTG_GOTGCTL_DHNPEN_MASK    /* Device HNP enabled */
#define USB_OTG_GOTGCTL_EHEN_SHIFT               (12U)
#define USB_OTG_GOTGCTL_EHEN_MASK                (0x1U << USB_OTG_GOTGCTL_EHEN_SHIFT) /* 0x00001000 */
#define USB_OTG_GOTGCTL_EHEN                     USB_OTG_GOTGCTL_EHEN_MASK      /* Embedded host enable */
#define USB_OTG_GOTGCTL_CIDSTS_SHIFT             (16)
#define USB_OTG_GOTGCTL_CIDSTS_MASK              (0x1U << USB_OTG_GOTGCTL_CIDSTS_SHIFT) /* 0x00010000 */
#define USB_OTG_GOTGCTL_CIDSTS                   USB_OTG_GOTGCTL_CIDSTS_MASK    /* Connector ID status */
#define USB_OTG_GOTGCTL_DBCT_SHIFT               (17U)
#define USB_OTG_GOTGCTL_DBCT_MASK                (0x1U << USB_OTG_GOTGCTL_DBCT_SHIFT) /* 0x00020000 */
#define USB_OTG_GOTGCTL_DBCT                     USB_OTG_GOTGCTL_DBCT_MASK      /* Long/short debounce time */
#define USB_OTG_GOTGCTL_ASVLD_SHIFT              (18U)
#define USB_OTG_GOTGCTL_ASVLD_MASK               (0x1U << USB_OTG_GOTGCTL_ASVLD_SHIFT) /* 0x00040000 */
#define USB_OTG_GOTGCTL_ASVLD                    USB_OTG_GOTGCTL_ASVLD_MASK     /* A-session valid  */
#define USB_OTG_GOTGCTL_BSESVLD_SHIFT            (19U)
#define USB_OTG_GOTGCTL_BSESVLD_MASK             (0x1U << USB_OTG_GOTGCTL_BSESVLD_SHIFT) /* 0x00080000 */
#define USB_OTG_GOTGCTL_BSESVLD                  USB_OTG_GOTGCTL_BSESVLD_MASK   /* B-session valid */
#define USB_OTG_GOTGCTL_OTGVER_SHIFT             (20U)
#define USB_OTG_GOTGCTL_OTGVER_MASK              (0x1U << USB_OTG_GOTGCTL_OTGVER_SHIFT) /* 0x00100000 */
#define USB_OTG_GOTGCTL_OTGVER                   USB_OTG_GOTGCTL_OTGVER_MASK    /* OTG version  */
/********************  Bit definition for USB_OTG_GOTGINT register  ********************/
#define USB_OTG_GOTGINT_SEDET_SHIFT              (2U)
#define USB_OTG_GOTGINT_SEDET_MASK               (0x1U << USB_OTG_GOTGINT_SEDET_SHIFT) /* 0x00000004 */
#define USB_OTG_GOTGINT_SEDET                    USB_OTG_GOTGINT_SEDET_MASK     /* Session end detected */
#define USB_OTG_GOTGINT_SRSSCHG_SHIFT            (8U)
#define USB_OTG_GOTGINT_SRSSCHG_MASK             (0x1U << USB_OTG_GOTGINT_SRSSCHG_SHIFT) /* 0x00000100 */
#define USB_OTG_GOTGINT_SRSSCHG                  USB_OTG_GOTGINT_SRSSCHG_MASK   /* Session request success status change */
#define USB_OTG_GOTGINT_HNSSCHG_SHIFT            (9U)
#define USB_OTG_GOTGINT_HNSSCHG_MASK             (0x1U << USB_OTG_GOTGINT_HNSSCHG_SHIFT) /* 0x00000200 */
#define USB_OTG_GOTGINT_HNSSCHG                  USB_OTG_GOTGINT_HNSSCHG_MASK   /* Host negotiation success status change */
#define USB_OTG_GOTGINT_HNGDET_SHIFT             (17U)
#define USB_OTG_GOTGINT_HNGDET_MASK              (0x1U << USB_OTG_GOTGINT_HNGDET_SHIFT) /* 0x00020000 */
#define USB_OTG_GOTGINT_HNGDET                   USB_OTG_GOTGINT_HNGDET_MASK    /* Host negotiation detected */
#define USB_OTG_GOTGINT_ADTOCHG_SHIFT            (18U)
#define USB_OTG_GOTGINT_ADTOCHG_MASK             (0x1U << USB_OTG_GOTGINT_ADTOCHG_SHIFT) /* 0x00040000 */
#define USB_OTG_GOTGINT_ADTOCHG                  USB_OTG_GOTGINT_ADTOCHG_MASK   /* A-device timeout change */
#define USB_OTG_GOTGINT_DBCDNE_SHIFT             (19U)
#define USB_OTG_GOTGINT_DBCDNE_MASK              (0x1U << USB_OTG_GOTGINT_DBCDNE_SHIFT) /* 0x00080000 */
#define USB_OTG_GOTGINT_DBCDNE                   USB_OTG_GOTGINT_DBCDNE_MASK    /* Debounce done */
#define USB_OTG_GOTGINT_IDCHNG_SHIFT             (20U)
#define USB_OTG_GOTGINT_IDCHNG_MASK              (0x1U << USB_OTG_GOTGINT_IDCHNG_SHIFT) /* 0x00100000 */
#define USB_OTG_GOTGINT_IDCHNG                   USB_OTG_GOTGINT_IDCHNG_MASK    /* Change in ID pin input value */
/********************  Bit definition for USB_OTG_GAHBCFG register  ********************/
#define USB_OTG_GAHBCFG_GINT_SHIFT               (0U)
#define USB_OTG_GAHBCFG_GINT_MASK                (0x1U << USB_OTG_GAHBCFG_GINT_SHIFT) /* 0x00000001 */
#define USB_OTG_GAHBCFG_GINT                     USB_OTG_GAHBCFG_GINT_MASK      /* Global interrupt mask */
#define USB_OTG_GAHBCFG_HBSTLEN_SHIFT            (1U)
#define USB_OTG_GAHBCFG_HBSTLEN_MASK             (0xFU << USB_OTG_GAHBCFG_HBSTLEN_SHIFT) /* 0x0000001E */
#define USB_OTG_GAHBCFG_HBSTLEN                  USB_OTG_GAHBCFG_HBSTLEN_MASK   /* Burst length/type */
#define USB_OTG_GAHBCFG_HBSTLEN_0                (0x0U << USB_OTG_GAHBCFG_HBSTLEN_SHIFT) /* Single */
#define USB_OTG_GAHBCFG_HBSTLEN_1                (0x1U << USB_OTG_GAHBCFG_HBSTLEN_SHIFT) /* INCR */
#define USB_OTG_GAHBCFG_HBSTLEN_2                (0x3U << USB_OTG_GAHBCFG_HBSTLEN_SHIFT) /* INCR4 */
#define USB_OTG_GAHBCFG_HBSTLEN_3                (0x5U << USB_OTG_GAHBCFG_HBSTLEN_SHIFT) /* INCR8 */
#define USB_OTG_GAHBCFG_HBSTLEN_4                (0x7U << USB_OTG_GAHBCFG_HBSTLEN_SHIFT) /* INCR16 */
#define USB_OTG_GAHBCFG_DMAEN_SHIFT              (5U)
#define USB_OTG_GAHBCFG_DMAEN_MASK               (0x1U << USB_OTG_GAHBCFG_DMAEN_SHIFT) /* 0x00000020 */
#define USB_OTG_GAHBCFG_DMAEN                    USB_OTG_GAHBCFG_DMAEN_MASK     /* DMA enable */
#define USB_OTG_GAHBCFG_TXFELVL_SHIFT            (7U)
#define USB_OTG_GAHBCFG_TXFELVL_MASK             (0x1U << USB_OTG_GAHBCFG_TXFELVL_SHIFT) /* 0x00000080 */
#define USB_OTG_GAHBCFG_TXFELVL                  USB_OTG_GAHBCFG_TXFELVL_MASK   /* TxFIFO empty level */
#define USB_OTG_GAHBCFG_PTXFELVL_SHIFT           (8U)
#define USB_OTG_GAHBCFG_PTXFELVL_MASK            (0x1U << USB_OTG_GAHBCFG_PTXFELVL_SHIFT) /* 0x00000100 */
#define USB_OTG_GAHBCFG_PTXFELVL                 USB_OTG_GAHBCFG_PTXFELVL_MASK  /* Periodic TxFIFO empty level */
/********************  Bit definition for USB_OTG_GUSBCFG register  ********************/
#define USB_OTG_GUSBCFG_TOCAL_SHIFT              (0U)
#define USB_OTG_GUSBCFG_TOCAL_MASK               (0x7U << USB_OTG_GUSBCFG_TOCAL_SHIFT) /* 0x00000007 */
#define USB_OTG_GUSBCFG_TOCAL                    USB_OTG_GUSBCFG_TOCAL_MASK     /* FS timeout calibration */
#define USB_OTG_GUSBCFG_TOCAL_0                  (0x1U << USB_OTG_GUSBCFG_TOCAL_SHIFT) /* 0x00000001 */
#define USB_OTG_GUSBCFG_TOCAL_1                  (0x2U << USB_OTG_GUSBCFG_TOCAL_SHIFT) /* 0x00000002 */
#define USB_OTG_GUSBCFG_TOCAL_2                  (0x4U << USB_OTG_GUSBCFG_TOCAL_SHIFT) /* 0x00000004 */
#define USB_OTG_GUSBCFG_PHYIF_SHIFT              (3U)
#define USB_OTG_GUSBCFG_PHYIF_MASK               (0x1U << USB_OTG_GUSBCFG_PHYIF_SHIFT) /* 0x00000008 */
#define USB_OTG_GUSBCFG_PHYIF                    USB_OTG_GUSBCFG_PHYIF_MASK     /* PHY Interface (PHYIf) */
#define USB_OTG_GUSBCFG_ULPI_UTMI_SEL_SHIFT      (4U)
#define USB_OTG_GUSBCFG_ULPI_UTMI_SEL_MASK       (0x1U << USB_OTG_GUSBCFG_ULPI_UTMI_SEL_SHIFT) /* 0x00000010 */
#define USB_OTG_GUSBCFG_ULPI_UTMI_SEL            USB_OTG_GUSBCFG_ULPI_UTMI_SEL_MASK /* ULPI or UTMI+ Select (ULPI_UTMI_Sel) */
#define USB_OTG_GUSBCFG_PHYSEL_SHIFT             (6U)
#define USB_OTG_GUSBCFG_PHYSEL_MASK              (0x1U << USB_OTG_GUSBCFG_PHYSEL_SHIFT) /* 0x00000040 */
#define USB_OTG_GUSBCFG_PHYSEL                   USB_OTG_GUSBCFG_PHYSEL_MASK    /* USB 2.0 high-speed PHY or USB 1.1 full-speed serial transceiver select */
#define USB_OTG_GUSBCFG_SRPCAP_SHIFT             (8U)
#define USB_OTG_GUSBCFG_SRPCAP_MASK              (0x1U << USB_OTG_GUSBCFG_SRPCAP_SHIFT) /* 0x00000100 */
#define USB_OTG_GUSBCFG_SRPCAP                   USB_OTG_GUSBCFG_SRPCAP_MASK    /* SRP-capable */
#define USB_OTG_GUSBCFG_HNPCAP_SHIFT             (9U)
#define USB_OTG_GUSBCFG_HNPCAP_MASK              (0x1U << USB_OTG_GUSBCFG_HNPCAP_SHIFT) /* 0x00000200 */
#define USB_OTG_GUSBCFG_HNPCAP                   USB_OTG_GUSBCFG_HNPCAP_MASK    /* HNP-capable */
#define USB_OTG_GUSBCFG_TRDT_SHIFT               (10U)
#define USB_OTG_GUSBCFG_TRDT_MASK                (0xFU << USB_OTG_GUSBCFG_TRDT_SHIFT) /* 0x00003C00 */
#define USB_OTG_GUSBCFG_TRDT                     USB_OTG_GUSBCFG_TRDT_MASK      /* USB turnaround time */
#define USB_OTG_GUSBCFG_TRDT_0                   (0x1U << USB_OTG_GUSBCFG_TRDT_SHIFT) /* 0x00000400 */
#define USB_OTG_GUSBCFG_TRDT_1                   (0x2U << USB_OTG_GUSBCFG_TRDT_SHIFT) /* 0x00000800 */
#define USB_OTG_GUSBCFG_TRDT_2                   (0x4U << USB_OTG_GUSBCFG_TRDT_SHIFT) /* 0x00001000 */
#define USB_OTG_GUSBCFG_TRDT_3                   (0x8U << USB_OTG_GUSBCFG_TRDT_SHIFT) /* 0x00002000 */
#define USB_OTG_GUSBCFG_PHYLPCS_SHIFT            (15U)
#define USB_OTG_GUSBCFG_PHYLPCS_MASK             (0x1U << USB_OTG_GUSBCFG_PHYLPCS_SHIFT) /* 0x00008000 */
#define USB_OTG_GUSBCFG_PHYLPCS                  USB_OTG_GUSBCFG_PHYLPCS_MASK   /* PHY Low-power clock select */
#define USB_OTG_GUSBCFG_ULPIFSLS_SHIFT           (17U)
#define USB_OTG_GUSBCFG_ULPIFSLS_MASK            (0x1U << USB_OTG_GUSBCFG_ULPIFSLS_SHIFT) /* 0x00020000 */
#define USB_OTG_GUSBCFG_ULPIFSLS                 USB_OTG_GUSBCFG_ULPIFSLS_MASK  /* ULPI FS/LS select */
#define USB_OTG_GUSBCFG_ULPIAR_SHIFT             (18U)
#define USB_OTG_GUSBCFG_ULPIAR_MASK              (0x1U << USB_OTG_GUSBCFG_ULPIAR_SHIFT) /* 0x00040000 */
#define USB_OTG_GUSBCFG_ULPIAR                   USB_OTG_GUSBCFG_ULPIAR_MASK    /* ULPI Auto-resume */
#define USB_OTG_GUSBCFG_ULPICSM_SHIFT            (19U)
#define USB_OTG_GUSBCFG_ULPICSM_MASK             (0x1U << USB_OTG_GUSBCFG_ULPICSM_SHIFT) /* 0x00080000 */
#define USB_OTG_GUSBCFG_ULPICSM                  USB_OTG_GUSBCFG_ULPICSM_MASK   /* ULPI Clock SuspendM */
#define USB_OTG_GUSBCFG_ULPIEVBUSD_SHIFT         (20U)
#define USB_OTG_GUSBCFG_ULPIEVBUSD_MASK          (0x1U << USB_OTG_GUSBCFG_ULPIEVBUSD_SHIFT) /* 0x00100000 */
#define USB_OTG_GUSBCFG_ULPIEVBUSD               USB_OTG_GUSBCFG_ULPIEVBUSD_MASK /* ULPI External VBUS Drive */
#define USB_OTG_GUSBCFG_ULPIEVBUSI_SHIFT         (21U)
#define USB_OTG_GUSBCFG_ULPIEVBUSI_MASK          (0x1U << USB_OTG_GUSBCFG_ULPIEVBUSI_SHIFT) /* 0x00200000 */
#define USB_OTG_GUSBCFG_ULPIEVBUSI               USB_OTG_GUSBCFG_ULPIEVBUSI_MASK /* ULPI external VBUS indicator */
#define USB_OTG_GUSBCFG_TSDPS_SHIFT              (22U)
#define USB_OTG_GUSBCFG_TSDPS_MASK               (0x1U << USB_OTG_GUSBCFG_TSDPS_SHIFT) /* 0x00400000 */
#define USB_OTG_GUSBCFG_TSDPS                    USB_OTG_GUSBCFG_TSDPS_MASK     /* TermSel DLine pulsing selection */
#define USB_OTG_GUSBCFG_PCCI_SHIFT               (23U)
#define USB_OTG_GUSBCFG_PCCI_MASK                (0x1U << USB_OTG_GUSBCFG_PCCI_SHIFT) /* 0x00800000 */
#define USB_OTG_GUSBCFG_PCCI                     USB_OTG_GUSBCFG_PCCI_MASK      /* Indicator complement */
#define USB_OTG_GUSBCFG_PTCI_SHIFT               (24U)
#define USB_OTG_GUSBCFG_PTCI_MASK                (0x1U << USB_OTG_GUSBCFG_PTCI_SHIFT) /* 0x01000000 */
#define USB_OTG_GUSBCFG_PTCI                     USB_OTG_GUSBCFG_PTCI_MASK      /* Indicator pass through */
#define USB_OTG_GUSBCFG_ULPIIPD_SHIFT            (25U)
#define USB_OTG_GUSBCFG_ULPIIPD_MASK             (0x1U << USB_OTG_GUSBCFG_ULPIIPD_SHIFT) /* 0x02000000 */
#define USB_OTG_GUSBCFG_ULPIIPD                  USB_OTG_GUSBCFG_ULPIIPD_MASK   /* ULPI interface protect disable */
#define USB_OTG_GUSBCFG_FHMOD_SHIFT              (29U)
#define USB_OTG_GUSBCFG_FHMOD_MASK               (0x1U << USB_OTG_GUSBCFG_FHMOD_SHIFT) /* 0x20000000 */
#define USB_OTG_GUSBCFG_FHMOD                    USB_OTG_GUSBCFG_FHMOD_MASK     /* Forced host mode */
#define USB_OTG_GUSBCFG_FDMOD_SHIFT              (30U)
#define USB_OTG_GUSBCFG_FDMOD_MASK               (0x1U << USB_OTG_GUSBCFG_FDMOD_SHIFT) /* 0x40000000 */
#define USB_OTG_GUSBCFG_FDMOD                    USB_OTG_GUSBCFG_FDMOD_MASK     /* Forced peripheral mode */
#define USB_OTG_GUSBCFG_CTXPKT_SHIFT             (31U)
#define USB_OTG_GUSBCFG_CTXPKT_MASK              (0x1U << USB_OTG_GUSBCFG_CTXPKT_SHIFT) /* 0x80000000 */
#define USB_OTG_GUSBCFG_CTXPKT                   USB_OTG_GUSBCFG_CTXPKT_MASK    /* Corrupt Tx packet */
/********************  Bit definition for USB_OTG_GRSTCTL register  ********************/
#define USB_OTG_GRSTCTL_CSRST_SHIFT              (0U)
#define USB_OTG_GRSTCTL_CSRST_MASK               (0x1U << USB_OTG_GRSTCTL_CSRST_SHIFT) /* 0x00000001 */
#define USB_OTG_GRSTCTL_CSRST                    USB_OTG_GRSTCTL_CSRST_MASK     /* Core soft reset */
#define USB_OTG_GRSTCTL_HSRST_SHIFT              (1U)
#define USB_OTG_GRSTCTL_HSRST_MASK               (0x1U << USB_OTG_GRSTCTL_HSRST_SHIFT) /* 0x00000002 */
#define USB_OTG_GRSTCTL_HSRST                    USB_OTG_GRSTCTL_HSRST_MASK     /* HCLK soft reset */
#define USB_OTG_GRSTCTL_FCRST_SHIFT              (2U)
#define USB_OTG_GRSTCTL_FCRST_MASK               (0x1U << USB_OTG_GRSTCTL_FCRST_SHIFT) /* 0x00000004 */
#define USB_OTG_GRSTCTL_FCRST                    USB_OTG_GRSTCTL_FCRST_MASK     /* Host frame counter reset */
#define USB_OTG_GRSTCTL_INTKNQFLSH_SHIFT         (3U)
#define USB_OTG_GRSTCTL_INTKNQFLSH_MASK          (0x1U << USB_OTG_GRSTCTL_INTKNQFLSH_SHIFT) /* 0x00000080 */
#define USB_OTG_GRSTCTL_INTKNQFLSH               USB_OTG_GRSTCTL_INTKNQFLSH_MASK   /* INTknQ flush */
#define USB_OTG_GRSTCTL_RXFFLSH_SHIFT            (4U)
#define USB_OTG_GRSTCTL_RXFFLSH_MASK             (0x1U << USB_OTG_GRSTCTL_RXFFLSH_SHIFT) /* 0x00000010 */
#define USB_OTG_GRSTCTL_RXFFLSH                  USB_OTG_GRSTCTL_RXFFLSH_MASK   /* RxFIFO flush */
#define USB_OTG_GRSTCTL_TXFFLSH_SHIFT            (5U)
#define USB_OTG_GRSTCTL_TXFFLSH_MASK             (0x1U << USB_OTG_GRSTCTL_TXFFLSH_SHIFT) /* 0x00000020 */
#define USB_OTG_GRSTCTL_TXFFLSH                  USB_OTG_GRSTCTL_TXFFLSH_MASK   /* TxFIFO flush */
#define USB_OTG_GRSTCTL_TXFNUM_SHIFT             (6U)
#define USB_OTG_GRSTCTL_TXFNUM_MASK              (0x1FU << USB_OTG_GRSTCTL_TXFNUM_SHIFT) /* 0x000007C0 */
#define USB_OTG_GRSTCTL_TXFNUM                   USB_OTG_GRSTCTL_TXFNUM_MASK    /* TxFIFO number */
#define USB_OTG_GRSTCTL_TXFNUM_0                 (0x01U << USB_OTG_GRSTCTL_TXFNUM_SHIFT) /* 0x00000040 */
#define USB_OTG_GRSTCTL_TXFNUM_1                 (0x02U << USB_OTG_GRSTCTL_TXFNUM_SHIFT) /* 0x00000080 */
#define USB_OTG_GRSTCTL_TXFNUM_2                 (0x04U << USB_OTG_GRSTCTL_TXFNUM_SHIFT) /* 0x00000100 */
#define USB_OTG_GRSTCTL_TXFNUM_3                 (0x08U << USB_OTG_GRSTCTL_TXFNUM_SHIFT) /* 0x00000200 */
#define USB_OTG_GRSTCTL_TXFNUM_4                 (0x10U << USB_OTG_GRSTCTL_TXFNUM_SHIFT) /* 0x00000400 */
#define USB_OTG_GRSTCTL_DMAREQ_SHIFT             (30U)
#define USB_OTG_GRSTCTL_DMAREQ_MASK              (0x1U << USB_OTG_GRSTCTL_DMAREQ_SHIFT) /* 0x40000000 */
#define USB_OTG_GRSTCTL_DMAREQ                   USB_OTG_GRSTCTL_DMAREQ_MASK    /* DMA request signal */
#define USB_OTG_GRSTCTL_AHBIDL_SHIFT             (31U)
#define USB_OTG_GRSTCTL_AHBIDL_MASK              (0x1U << USB_OTG_GRSTCTL_AHBIDL_SHIFT) /* 0x80000000 */
#define USB_OTG_GRSTCTL_AHBIDL                   USB_OTG_GRSTCTL_AHBIDL_MASK    /* AHB master idle */
/********************  Bit definition for USB_OTG_GINTSTS register  ********************/
#define USB_OTG_GINTSTS_CMOD_SHIFT               (0U)
#define USB_OTG_GINTSTS_CMOD_MASK                (0x1U << USB_OTG_GINTSTS_CMOD_SHIFT) /* 0x00000001 */
#define USB_OTG_GINTSTS_CMOD                     USB_OTG_GINTSTS_CMOD_MASK      /* Current mode of operation */
#define USB_OTG_GINTSTS_MMIS_SHIFT               (1U)
#define USB_OTG_GINTSTS_MMIS_MASK                (0x1U << USB_OTG_GINTSTS_MMIS_SHIFT) /* 0x00000002 */
#define USB_OTG_GINTSTS_MMIS                     USB_OTG_GINTSTS_MMIS_MASK      /* Mode mismatch interrupt */
#define USB_OTG_GINTSTS_OTGINT_SHIFT             (2U)
#define USB_OTG_GINTSTS_OTGINT_MASK              (0x1U << USB_OTG_GINTSTS_OTGINT_SHIFT) /* 0x00000004 */
#define USB_OTG_GINTSTS_OTGINT                   USB_OTG_GINTSTS_OTGINT_MASK    /* OTG interrupt */
#define USB_OTG_GINTSTS_SOF_SHIFT                (3U)
#define USB_OTG_GINTSTS_SOF_MASK                 (0x1U << USB_OTG_GINTSTS_SOF_SHIFT) /* 0x00000008 */
#define USB_OTG_GINTSTS_SOF                      USB_OTG_GINTSTS_SOF_MASK       /* Start of frame */
#define USB_OTG_GINTSTS_RXFLVL_SHIFT             (4U)
#define USB_OTG_GINTSTS_RXFLVL_MASK              (0x1U << USB_OTG_GINTSTS_RXFLVL_SHIFT) /* 0x00000010 */
#define USB_OTG_GINTSTS_RXFLVL                   USB_OTG_GINTSTS_RXFLVL_MASK    /* RxFIFO nonempty */
#define USB_OTG_GINTSTS_NPTXFE_SHIFT             (5U)
#define USB_OTG_GINTSTS_NPTXFE_MASK              (0x1U << USB_OTG_GINTSTS_NPTXFE_SHIFT) /* 0x00000020 */
#define USB_OTG_GINTSTS_NPTXFE                   USB_OTG_GINTSTS_NPTXFE_MASK    /* Nonperiodic TxFIFO empty */
#define USB_OTG_GINTSTS_GINAKEFF_SHIFT           (6U)
#define USB_OTG_GINTSTS_GINAKEFF_MASK            (0x1U << USB_OTG_GINTSTS_GINAKEFF_SHIFT) /* 0x00000040 */
#define USB_OTG_GINTSTS_GINAKEFF                 USB_OTG_GINTSTS_GINAKEFF_MASK  /* Global IN nonperiodic NAK effective */
#define USB_OTG_GINTSTS_BOUTNAKEFF_SHIFT         (7U)
#define USB_OTG_GINTSTS_BOUTNAKEFF_MASK          (0x1U << USB_OTG_GINTSTS_BOUTNAKEFF_SHIFT) /* 0x00000080 */
#define USB_OTG_GINTSTS_BOUTNAKEFF               USB_OTG_GINTSTS_BOUTNAKEFF_MASK /* Global OUT NAK effective */
#define USB_OTG_GINTSTS_ESUSP_SHIFT              (10U)
#define USB_OTG_GINTSTS_ESUSP_MASK               (0x1U << USB_OTG_GINTSTS_ESUSP_SHIFT) /* 0x00000400 */
#define USB_OTG_GINTSTS_ESUSP                    USB_OTG_GINTSTS_ESUSP_MASK     /* Early suspend */
#define USB_OTG_GINTSTS_USBSUSP_SHIFT            (11U)
#define USB_OTG_GINTSTS_USBSUSP_MASK             (0x1U << USB_OTG_GINTSTS_USBSUSP_SHIFT) /* 0x00000800 */
#define USB_OTG_GINTSTS_USBSUSP                  USB_OTG_GINTSTS_USBSUSP_MASK   /* USB suspend */
#define USB_OTG_GINTSTS_USBRST_SHIFT             (12U)
#define USB_OTG_GINTSTS_USBRST_MASK              (0x1U << USB_OTG_GINTSTS_USBRST_SHIFT) /* 0x00001000 */
#define USB_OTG_GINTSTS_USBRST                   USB_OTG_GINTSTS_USBRST_MASK    /* USB reset */
#define USB_OTG_GINTSTS_ENUMDNE_SHIFT            (13U)
#define USB_OTG_GINTSTS_ENUMDNE_MASK             (0x1U << USB_OTG_GINTSTS_ENUMDNE_SHIFT) /* 0x00002000 */
#define USB_OTG_GINTSTS_ENUMDNE                  USB_OTG_GINTSTS_ENUMDNE_MASK   /* Enumeration done */
#define USB_OTG_GINTSTS_ISOODRP_SHIFT            (14U)
#define USB_OTG_GINTSTS_ISOODRP_MASK             (0x1U << USB_OTG_GINTSTS_ISOODRP_SHIFT) /* 0x00004000 */
#define USB_OTG_GINTSTS_ISOODRP                  USB_OTG_GINTSTS_ISOODRP_MASK   /* Isochronous OUT packet dropped interrupt */
#define USB_OTG_GINTSTS_EOPF_SHIFT               (15U)
#define USB_OTG_GINTSTS_EOPF_MASK                (0x1U << USB_OTG_GINTSTS_EOPF_SHIFT) /* 0x00008000 */
#define USB_OTG_GINTSTS_EOPF                     USB_OTG_GINTSTS_EOPF_MASK      /* End of periodic frame interrupt */
#define USB_OTG_GINTSTS_IEPINT_SHIFT             (18U)
#define USB_OTG_GINTSTS_IEPINT_MASK              (0x1U << USB_OTG_GINTSTS_IEPINT_SHIFT) /* 0x00040000 */
#define USB_OTG_GINTSTS_IEPINT                   USB_OTG_GINTSTS_IEPINT_MASK    /* IN endpoint interrupt */
#define USB_OTG_GINTSTS_OEPINT_SHIFT             (19U)
#define USB_OTG_GINTSTS_OEPINT_MASK              (0x1U << USB_OTG_GINTSTS_OEPINT_SHIFT) /* 0x00080000 */
#define USB_OTG_GINTSTS_OEPINT                   USB_OTG_GINTSTS_OEPINT_MASK    /* OUT endpoint interrupt */
#define USB_OTG_GINTSTS_IISOIXFR_SHIFT           (20U)
#define USB_OTG_GINTSTS_IISOIXFR_MASK            (0x1U << USB_OTG_GINTSTS_IISOIXFR_SHIFT) /* 0x00100000 */
#define USB_OTG_GINTSTS_IISOIXFR                 USB_OTG_GINTSTS_IISOIXFR_MASK  /* Incomplete isochronous IN transfer */
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_SHIFT  (21U)
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_MASK   (0x1U << USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_SHIFT) /* 0x00200000 */
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT        USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_MASK /* Incomplete periodic transfer */
#define USB_OTG_GINTSTS_DATAFSUSP_SHIFT          (22U)
#define USB_OTG_GINTSTS_DATAFSUSP_MASK           (0x1U << USB_OTG_GINTSTS_DATAFSUSP_SHIFT) /* 0x00400000 */
#define USB_OTG_GINTSTS_DATAFSUSP                USB_OTG_GINTSTS_DATAFSUSP_MASK /* Data fetch suspended */
#define USB_OTG_GINTSTS_RSTDET_SHIFT             (23U)
#define USB_OTG_GINTSTS_RSTDET_MASK              (0x1U << USB_OTG_GINTSTS_RSTDET_SHIFT) /* 0x00800000 */
#define USB_OTG_GINTSTS_RSTDET                   USB_OTG_GINTSTS_RSTDET_MASK    /* Reset detected interrupt */
#define USB_OTG_GINTSTS_HPRTINT_SHIFT            (24U)
#define USB_OTG_GINTSTS_HPRTINT_MASK             (0x1U << USB_OTG_GINTSTS_HPRTINT_SHIFT) /* 0x01000000 */
#define USB_OTG_GINTSTS_HPRTINT                  USB_OTG_GINTSTS_HPRTINT_MASK   /* Host port interrupt */
#define USB_OTG_GINTSTS_HCINT_SHIFT              (25U)
#define USB_OTG_GINTSTS_HCINT_MASK               (0x1U << USB_OTG_GINTSTS_HCINT_SHIFT) /* 0x02000000 */
#define USB_OTG_GINTSTS_HCINT                    USB_OTG_GINTSTS_HCINT_MASK     /* Host channels interrupt */
#define USB_OTG_GINTSTS_PTXFE_SHIFT              (26U)
#define USB_OTG_GINTSTS_PTXFE_MASK               (0x1U << USB_OTG_GINTSTS_PTXFE_SHIFT) /* 0x04000000 */
#define USB_OTG_GINTSTS_PTXFE                    USB_OTG_GINTSTS_PTXFE_MASK     /* Periodic TxFIFO empty */
#define USB_OTG_GINTSTS_LPMINT_SHIFT             (27U)
#define USB_OTG_GINTSTS_LPMINT_MASK              (0x1U << USB_OTG_GINTSTS_LPMINT_SHIFT) /* 0x08000000 */
#define USB_OTG_GINTSTS_LPMINT                   USB_OTG_GINTSTS_LPMINT_MASK    /* LPM interrupt */
#define USB_OTG_GINTSTS_CIDSCHG_SHIFT            (28U)
#define USB_OTG_GINTSTS_CIDSCHG_MASK             (0x1U << USB_OTG_GINTSTS_CIDSCHG_SHIFT) /* 0x10000000 */
#define USB_OTG_GINTSTS_CIDSCHG                  USB_OTG_GINTSTS_CIDSCHG_MASK   /* Connector ID status change */
#define USB_OTG_GINTSTS_DISCINT_SHIFT            (29U)
#define USB_OTG_GINTSTS_DISCINT_MASK             (0x1U << USB_OTG_GINTSTS_DISCINT_SHIFT) /* 0x20000000 */
#define USB_OTG_GINTSTS_DISCINT                  USB_OTG_GINTSTS_DISCINT_MASK   /* Disconnect detected interrupt */
#define USB_OTG_GINTSTS_SRQINT_SHIFT             (30U)
#define USB_OTG_GINTSTS_SRQINT_MASK              (0x1U << USB_OTG_GINTSTS_SRQINT_SHIFT) /* 0x40000000 */
#define USB_OTG_GINTSTS_SRQINT                   USB_OTG_GINTSTS_SRQINT_MASK    /* Session request/new session detected interrupt */
#define USB_OTG_GINTSTS_WKUINT_SHIFT             (31U)
#define USB_OTG_GINTSTS_WKUINT_MASK              (0x1U << USB_OTG_GINTSTS_WKUINT_SHIFT) /* 0x80000000 */
#define USB_OTG_GINTSTS_WKUINT                   USB_OTG_GINTSTS_WKUINT_MASK    /* Resume/remote wakeup detected interrupt */
/********************  Bit definition for USB_OTG_GINTMSK register  ********************/
#define USB_OTG_GINTMSK_MMISM_SHIFT              (1U)
#define USB_OTG_GINTMSK_MMISM_MASK               (0x1U << USB_OTG_GINTMSK_MMISM_SHIFT) /* 0x00000002 */
#define USB_OTG_GINTMSK_MMISM                    USB_OTG_GINTMSK_MMISM_MASK     /* Mode mismatch interrupt mask */
#define USB_OTG_GINTMSK_OTGINT_SHIFT             (2U)
#define USB_OTG_GINTMSK_OTGINT_MASK              (0x1U << USB_OTG_GINTMSK_OTGINT_SHIFT) /* 0x00000004 */
#define USB_OTG_GINTMSK_OTGINT                   USB_OTG_GINTMSK_OTGINT_MASK    /* OTG interrupt mask */
#define USB_OTG_GINTMSK_SOFM_SHIFT               (3U)
#define USB_OTG_GINTMSK_SOFM_MASK                (0x1U << USB_OTG_GINTMSK_SOFM_SHIFT) /* 0x00000008 */
#define USB_OTG_GINTMSK_SOFM                     USB_OTG_GINTMSK_SOFM_MASK      /* Start of frame mask */
#define USB_OTG_GINTMSK_RXFLVLM_SHIFT            (4U)
#define USB_OTG_GINTMSK_RXFLVLM_MASK             (0x1U << USB_OTG_GINTMSK_RXFLVLM_SHIFT) /* 0x00000010 */
#define USB_OTG_GINTMSK_RXFLVLM                  USB_OTG_GINTMSK_RXFLVLM_MASK   /* Receive FIFO nonempty mask */
#define USB_OTG_GINTMSK_NPTXFEM_SHIFT            (5U)
#define USB_OTG_GINTMSK_NPTXFEM_MASK             (0x1U << USB_OTG_GINTMSK_NPTXFEM_SHIFT) /* 0x00000020 */
#define USB_OTG_GINTMSK_NPTXFEM                  USB_OTG_GINTMSK_NPTXFEM_MASK   /* Nonperiodic TxFIFO empty mask */
#define USB_OTG_GINTMSK_GINAKEFFM_SHIFT          (6U)
#define USB_OTG_GINTMSK_GINAKEFFM_MASK           (0x1U << USB_OTG_GINTMSK_GINAKEFFM_SHIFT) /* 0x00000040 */
#define USB_OTG_GINTMSK_GINAKEFFM                USB_OTG_GINTMSK_GINAKEFFM_MASK /* Global nonperiodic IN NAK effective mask */
#define USB_OTG_GINTMSK_GONAKEFFM_SHIFT          (7U)
#define USB_OTG_GINTMSK_GONAKEFFM_MASK           (0x1U << USB_OTG_GINTMSK_GONAKEFFM_SHIFT) /* 0x00000080 */
#define USB_OTG_GINTMSK_GONAKEFFM                USB_OTG_GINTMSK_GONAKEFFM_MASK /* Global OUT NAK effective mask */
#define USB_OTG_GINTMSK_ESUSPM_SHIFT             (10U)
#define USB_OTG_GINTMSK_ESUSPM_MASK              (0x1U << USB_OTG_GINTMSK_ESUSPM_SHIFT) /* 0x00000400 */
#define USB_OTG_GINTMSK_ESUSPM                   USB_OTG_GINTMSK_ESUSPM_MASK    /* Early suspend mask */
#define USB_OTG_GINTMSK_USBSUSPM_SHIFT           (11U)
#define USB_OTG_GINTMSK_USBSUSPM_MASK            (0x1U << USB_OTG_GINTMSK_USBSUSPM_SHIFT) /* 0x00000800 */
#define USB_OTG_GINTMSK_USBSUSPM                 USB_OTG_GINTMSK_USBSUSPM_MASK  /* USB suspend mask */
#define USB_OTG_GINTMSK_USBRST_SHIFT             (12U)
#define USB_OTG_GINTMSK_USBRST_MASK              (0x1U << USB_OTG_GINTMSK_USBRST_SHIFT) /* 0x00001000 */
#define USB_OTG_GINTMSK_USBRST                   USB_OTG_GINTMSK_USBRST_MASK    /* USB reset mask */
#define USB_OTG_GINTMSK_ENUMDNEM_SHIFT           (13U)
#define USB_OTG_GINTMSK_ENUMDNEM_MASK            (0x1U << USB_OTG_GINTMSK_ENUMDNEM_SHIFT) /* 0x00002000 */
#define USB_OTG_GINTMSK_ENUMDNEM                 USB_OTG_GINTMSK_ENUMDNEM_MASK  /* Enumeration done mask */
#define USB_OTG_GINTMSK_ISOODRPM_SHIFT           (14U)
#define USB_OTG_GINTMSK_ISOODRPM_MASK            (0x1U << USB_OTG_GINTMSK_ISOODRPM_SHIFT) /* 0x00004000 */
#define USB_OTG_GINTMSK_ISOODRPM                 USB_OTG_GINTMSK_ISOODRPM_MASK  /* Isochronous OUT packet dropped interrupt mask */
#define USB_OTG_GINTMSK_EOPFM_SHIFT              (15U)
#define USB_OTG_GINTMSK_EOPFM_MASK               (0x1U << USB_OTG_GINTMSK_EOPFM_SHIFT) /* 0x00008000 */
#define USB_OTG_GINTMSK_EOPFM                    USB_OTG_GINTMSK_EOPFM_MASK     /* End of periodic frame interrupt mask */
#define USB_OTG_GINTMSK_EPMISM_SHIFT             (17U)
#define USB_OTG_GINTMSK_EPMISM_MASK              (0x1U << USB_OTG_GINTMSK_EPMISM_SHIFT) /* 0x00020000 */
#define USB_OTG_GINTMSK_EPMISM                   USB_OTG_GINTMSK_EPMISM_MASK    /* Endpoint mismatch interrupt mask */
#define USB_OTG_GINTMSK_IEPINT_SHIFT             (18U)
#define USB_OTG_GINTMSK_IEPINT_MASK              (0x1U << USB_OTG_GINTMSK_IEPINT_SHIFT) /* 0x00040000 */
#define USB_OTG_GINTMSK_IEPINT                   USB_OTG_GINTMSK_IEPINT_MASK    /* IN endpoints interrupt mask */
#define USB_OTG_GINTMSK_OEPINT_SHIFT             (19U)
#define USB_OTG_GINTMSK_OEPINT_MASK              (0x1U << USB_OTG_GINTMSK_OEPINT_SHIFT) /* 0x00080000 */
#define USB_OTG_GINTMSK_OEPINT                   USB_OTG_GINTMSK_OEPINT_MASK    /* OUT endpoints interrupt mask */
#define USB_OTG_GINTMSK_IISOIXFRM_SHIFT          (20U)
#define USB_OTG_GINTMSK_IISOIXFRM_MASK           (0x1U << USB_OTG_GINTMSK_IISOIXFRM_SHIFT) /* 0x00100000 */
#define USB_OTG_GINTMSK_IISOIXFRM                USB_OTG_GINTMSK_IISOIXFRM_MASK /* Incomplete isochronous IN transfer mask */
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM_SHIFT    (21U)
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM_MASK     (0x1U << USB_OTG_GINTMSK_PXFRM_IISOOXFRM_SHIFT) /* 0x00200000 */
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM          USB_OTG_GINTMSK_PXFRM_IISOOXFRM_MASK /* Incomplete periodic transfer mask */
#define USB_OTG_GINTMSK_FSUSPM_SHIFT             (22U)
#define USB_OTG_GINTMSK_FSUSPM_MASK              (0x1U << USB_OTG_GINTMSK_FSUSPM_SHIFT) /* 0x00400000 */
#define USB_OTG_GINTMSK_FSUSPM                   USB_OTG_GINTMSK_FSUSPM_MASK    /* Data fetch suspended mask */
#define USB_OTG_GINTMSK_RSTDEM_SHIFT             (23U)
#define USB_OTG_GINTMSK_RSTDEM_MASK              (0x1U << USB_OTG_GINTMSK_RSTDEM_SHIFT) /* 0x00800000 */
#define USB_OTG_GINTMSK_RSTDEM                   USB_OTG_GINTMSK_RSTDEM_MASK    /* Reset detected interrupt mask */
#define USB_OTG_GINTMSK_PRTIM_SHIFT              (24U)
#define USB_OTG_GINTMSK_PRTIM_MASK               (0x1U << USB_OTG_GINTMSK_PRTIM_SHIFT) /* 0x01000000 */
#define USB_OTG_GINTMSK_PRTIM                    USB_OTG_GINTMSK_PRTIM_MASK     /* Host port interrupt mask */
#define USB_OTG_GINTMSK_HCIM_SHIFT               (25U)
#define USB_OTG_GINTMSK_HCIM_MASK                (0x1U << USB_OTG_GINTMSK_HCIM_SHIFT) /* 0x02000000 */
#define USB_OTG_GINTMSK_HCIM                     USB_OTG_GINTMSK_HCIM_MASK      /* Host channels interrupt mask */
#define USB_OTG_GINTMSK_PTXFEM_SHIFT             (26U)
#define USB_OTG_GINTMSK_PTXFEM_MASK              (0x1U << USB_OTG_GINTMSK_PTXFEM_SHIFT) /* 0x04000000 */
#define USB_OTG_GINTMSK_PTXFEM                   USB_OTG_GINTMSK_PTXFEM_MASK    /* Periodic TxFIFO empty mask */
#define USB_OTG_GINTMSK_LPMINTM_SHIFT            (27U)
#define USB_OTG_GINTMSK_LPMINTM_MASK             (0x1U << USB_OTG_GINTMSK_LPMINTM_SHIFT) /* 0x08000000 */
#define USB_OTG_GINTMSK_LPMINTM                  USB_OTG_GINTMSK_LPMINTM_MASK   /* LPM interrupt Mask */
#define USB_OTG_GINTMSK_CIDSCHGM_SHIFT           (28U)
#define USB_OTG_GINTMSK_CIDSCHGM_MASK            (0x1U << USB_OTG_GINTMSK_CIDSCHGM_SHIFT) /* 0x10000000 */
#define USB_OTG_GINTMSK_CIDSCHGM                 USB_OTG_GINTMSK_CIDSCHGM_MASK  /* Connector ID status change mask */
#define USB_OTG_GINTMSK_DISCINT_SHIFT            (29U)
#define USB_OTG_GINTMSK_DISCINT_MASK             (0x1U << USB_OTG_GINTMSK_DISCINT_SHIFT) /* 0x20000000 */
#define USB_OTG_GINTMSK_DISCINT                  USB_OTG_GINTMSK_DISCINT_MASK   /* Disconnect detected interrupt mask */
#define USB_OTG_GINTMSK_SRQIM_SHIFT              (30U)
#define USB_OTG_GINTMSK_SRQIM_MASK               (0x1U << USB_OTG_GINTMSK_SRQIM_SHIFT) /* 0x40000000 */
#define USB_OTG_GINTMSK_SRQIM                    USB_OTG_GINTMSK_SRQIM_MASK     /* Session request/new session detected interrupt mask */
#define USB_OTG_GINTMSK_WUIM_SHIFT               (31U)
#define USB_OTG_GINTMSK_WUIM_MASK                (0x1U << USB_OTG_GINTMSK_WUIM_SHIFT) /* 0x80000000 */
#define USB_OTG_GINTMSK_WUIM                     USB_OTG_GINTMSK_WUIM_MASK      /* Resume/remote wakeup detected interrupt mask */
/********************  Bit definition for USB_OTG_GRXSTSP register  ********************/
#define USB_OTG_GRXSTSP_EPNUM_SHIFT              (0U)
#define USB_OTG_GRXSTSP_EPNUM_MASK               (0xFU << USB_OTG_GRXSTSP_EPNUM_SHIFT) /* 0x0000000F */
#define USB_OTG_GRXSTSP_EPNUM                    USB_OTG_GRXSTSP_EPNUM_MASK     /* IN EP interrupt mask bits */
#define USB_OTG_GRXSTSP_BCNT_SHIFT               (4U)
#define USB_OTG_GRXSTSP_BCNT_MASK                (0x7FFU << USB_OTG_GRXSTSP_BCNT_SHIFT) /* 0x00007FF0 */
#define USB_OTG_GRXSTSP_BCNT                     USB_OTG_GRXSTSP_BCNT_MASK      /* OUT EP interrupt mask bits */
#define USB_OTG_GRXSTSP_DPID_SHIFT               (15U)
#define USB_OTG_GRXSTSP_DPID_MASK                (0x3U << USB_OTG_GRXSTSP_DPID_SHIFT) /* 0x00018000 */
#define USB_OTG_GRXSTSP_DPID                     USB_OTG_GRXSTSP_DPID_MASK      /* OUT EP interrupt mask bits */
#define USB_OTG_GRXSTSP_PKTSTS_SHIFT             (17U)
#define USB_OTG_GRXSTSP_PKTSTS_MASK              (0xFU << USB_OTG_GRXSTSP_PKTSTS_SHIFT) /* 0x001E0000 */
#define USB_OTG_GRXSTSP_PKTSTS                   USB_OTG_GRXSTSP_PKTSTS_MASK    /* OUT EP interrupt mask bits */
/********************  Bit definition for USB_OTG_GRXFSIZ register  ********************/
#define USB_OTG_GRXFSIZ_RXFD_SHIFT               (0U)
#define USB_OTG_GRXFSIZ_RXFD_MASK                (0xFFFFU << USB_OTG_GRXFSIZ_RXFD_SHIFT) /* 0x0000FFFF */
#define USB_OTG_GRXFSIZ_RXFD                     USB_OTG_GRXFSIZ_RXFD_MASK      /* RxFIFO depth */
/********************  Bit definition for USB_OTG_GNPTXFSIZ register  *******************/
#define USB_OTG_GNPTXFSIZ_NPTXFSA_SHIFT          (0U)
#define USB_OTG_GNPTXFSIZ_NPTXFSA_MASK           (0xFFFFU << USB_OTG_GNPTXFSIZ_NPTXFSA_SHIFT) /* 0x0000FFFF */
#define USB_OTG_GNPTXFSIZ_NPTXFSA                USB_OTG_GNPTXFSIZ_NPTXFSA_MASK /* Nonperiodic transmit RAM start address */
#define USB_OTG_GNPTXFSIZ_NPTXFD_SHIFT           (16U)
#define USB_OTG_GNPTXFSIZ_NPTXFD_MASK            (0xFFFFU << USB_OTG_GNPTXFSIZ_NPTXFD_SHIFT) /* 0xFFFF0000 */
#define USB_OTG_GNPTXFSIZ_NPTXFD                 USB_OTG_GNPTXFSIZ_NPTXFD_MASK  /* Nonperiodic TxFIFO depth */
#define USB_OTG_GNPTXFSIZ_TXF0SA_SHIFT           (0U)
#define USB_OTG_GNPTXFSIZ_TXF0SA_MASK            (0xFFFFU << USB_OTG_GNPTXFSIZ_TXF0SA_SHIFT) /* 0x0000FFFF */
#define USB_OTG_GNPTXFSIZ_TXF0SA                 USB_OTG_GNPTXFSIZ_TXF0SA_MASK  /* Endpoint 0 transmit RAM start address */
#define USB_OTG_GNPTXFSIZ_TXF0D_SHIFT            (16U)
#define USB_OTG_GNPTXFSIZ_TXF0D_MASK             (0xFFFFU << USB_OTG_GNPTXFSIZ_TXF0D_SHIFT) /* 0xFFFF0000 */
#define USB_OTG_GNPTXFSIZ_TXF0D                  USB_OTG_GNPTXFSIZ_TXF0D_MASK   /* Endpoint 0 TxFIFO depth */
/********************  Bit definition for USB_OTG_GNPTXSTS register  ********************/
#define USB_OTG_GNPTXSTS_NPTXFSAV_SHIFT          (0U)
#define USB_OTG_GNPTXSTS_NPTXFSAV_MASK           (0xFFFFU << USB_OTG_GNPTXSTS_NPTXFSAV_SHIFT) /* 0x0000FFFF */
#define USB_OTG_GNPTXSTS_NPTXFSAV                USB_OTG_GNPTXSTS_NPTXFSAV_MASK /* Nonperiodic TxFIFO space available */
#define USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT          (16U)
#define USB_OTG_GNPTXSTS_NPTQXSAV_MASK           (0xFFU << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00FF0000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV                USB_OTG_GNPTXSTS_NPTQXSAV_MASK /* Nonperiodic transmit request queue space available */
#define USB_OTG_GNPTXSTS_NPTQXSAV_0              (0x01U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00010000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_1              (0x02U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00020000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_2              (0x04U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00040000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_3              (0x08U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00080000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_4              (0x10U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00100000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_5              (0x20U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00200000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_6              (0x40U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00400000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_7              (0x80U << USB_OTG_GNPTXSTS_NPTQXSAV_SHIFT) /* 0x00800000 */

#define USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT          (24U)
#define USB_OTG_GNPTXSTS_NPTXQTOP_MASK           (0x7FU << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x7F000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP                USB_OTG_GNPTXSTS_NPTXQTOP_MASK /* Top of the nonperiodic transmit request queue */
#define USB_OTG_GNPTXSTS_NPTXQTOP_0              (0x01U << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x01000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_1              (0x02U << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x02000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_2              (0x04U << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x04000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_3              (0x08U << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x08000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_4              (0x10U << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x10000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_5              (0x20U << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x20000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_6              (0x40U << USB_OTG_GNPTXSTS_NPTXQTOP_SHIFT) /* 0x40000000 */
/********************  Bit definition for USB_OTG_GHWCFG2 register  ********************/
#define USB_OTG_GHWCFG2_DYNFIFOSIZING_SHIFT      (19U)
#define USB_OTG_GHWCFG2_DYNFIFOSIZING_MASK       (0x1U << USB_OTG_GHWCFG2_DYNFIFOSIZING_SHIFT) /* 0x00080000 */
#define USB_OTG_GHWCFG2_DYNFIFOSIZING            USB_OTG_GHWCFG2_DYNFIFOSIZING_MASK     /* Dynamic FIFO Sizing enabled */
/********************  Bit definition for USB_OTG_GHWCFG4 register  ********************/
#define USB_OTG_GHWCFG4_DEDFIFOMODE_SHIFT        (25U)
#define USB_OTG_GHWCFG4_DEDFIFOMODE_MASK         (0x1U << USB_OTG_GHWCFG4_DEDFIFOMODE_SHIFT)   /* 0x00080000 */
#define USB_OTG_GHWCFG4_DEDFIFOMODE              USB_OTG_GHWCFG4_DEDFIFOMODE_MASK       /* Dedicated FIFO enabled */
/********************  Bit definition for USB_OTG_GLPMCFG register  ********************/
#define USB_OTG_GLPMCFG_LPMEN_SHIFT              (0U)
#define USB_OTG_GLPMCFG_LPMEN_MASK               (0x1U << USB_OTG_GLPMCFG_LPMEN_SHIFT) /* 0x00000001 */
#define USB_OTG_GLPMCFG_LPMEN                    USB_OTG_GLPMCFG_LPMEN_MASK     /* LPM support enable */
#define USB_OTG_GLPMCFG_LPMACK_SHIFT             (1U)
#define USB_OTG_GLPMCFG_LPMACK_MASK              (0x1U << USB_OTG_GLPMCFG_LPMACK_SHIFT) /* 0x00000002 */
#define USB_OTG_GLPMCFG_LPMACK                   USB_OTG_GLPMCFG_LPMACK_MASK    /* LPM Token acknowledge enable */
#define USB_OTG_GLPMCFG_BESL_SHIFT               (2U)
#define USB_OTG_GLPMCFG_BESL_MASK                (0xFU << USB_OTG_GLPMCFG_BESL_SHIFT) /* 0x0000003C */
#define USB_OTG_GLPMCFG_BESL                     USB_OTG_GLPMCFG_BESL_MASK      /* BESL value received with last ACKed LPM Token */
#define USB_OTG_GLPMCFG_REMWAKE_SHIFT            (6U)
#define USB_OTG_GLPMCFG_REMWAKE_MASK             (0x1U << USB_OTG_GLPMCFG_REMWAKE_SHIFT) /* 0x00000040 */
#define USB_OTG_GLPMCFG_REMWAKE                  USB_OTG_GLPMCFG_REMWAKE_MASK   /* bRemoteWake value received with last ACKed LPM Token */
#define USB_OTG_GLPMCFG_L1SSEN_SHIFT             (7U)
#define USB_OTG_GLPMCFG_L1SSEN_MASK              (0x1U << USB_OTG_GLPMCFG_L1SSEN_SHIFT) /* 0x00000080 */
#define USB_OTG_GLPMCFG_L1SSEN                   USB_OTG_GLPMCFG_L1SSEN_MASK    /* L1 shallow sleep enable */
#define USB_OTG_GLPMCFG_BESLTHRS_SHIFT           (8U)
#define USB_OTG_GLPMCFG_BESLTHRS_MASK            (0xFU << USB_OTG_GLPMCFG_BESLTHRS_SHIFT) /* 0x00000F00 */
#define USB_OTG_GLPMCFG_BESLTHRS                 USB_OTG_GLPMCFG_BESLTHRS_MASK  /* BESL threshold */
#define USB_OTG_GLPMCFG_L1DSEN_SHIFT             (12U)
#define USB_OTG_GLPMCFG_L1DSEN_MASK              (0x1U << USB_OTG_GLPMCFG_L1DSEN_SHIFT) /* 0x00001000 */
#define USB_OTG_GLPMCFG_L1DSEN                   USB_OTG_GLPMCFG_L1DSEN_MASK    /* L1 deep sleep enable */
#define USB_OTG_GLPMCFG_LPMRSP_SHIFT             (13U)
#define USB_OTG_GLPMCFG_LPMRSP_MASK              (0x3U << USB_OTG_GLPMCFG_LPMRSP_SHIFT) /* 0x00006000 */
#define USB_OTG_GLPMCFG_LPMRSP                   USB_OTG_GLPMCFG_LPMRSP_MASK    /* LPM response */
#define USB_OTG_GLPMCFG_SLPSTS_SHIFT             (15U)
#define USB_OTG_GLPMCFG_SLPSTS_MASK              (0x1U << USB_OTG_GLPMCFG_SLPSTS_SHIFT) /* 0x00008000 */
#define USB_OTG_GLPMCFG_SLPSTS                   USB_OTG_GLPMCFG_SLPSTS_MASK    /* Port sleep status */
#define USB_OTG_GLPMCFG_L1RSMOK_SHIFT            (16U)
#define USB_OTG_GLPMCFG_L1RSMOK_MASK             (0x1U << USB_OTG_GLPMCFG_L1RSMOK_SHIFT) /* 0x00010000 */
#define USB_OTG_GLPMCFG_L1RSMOK                  USB_OTG_GLPMCFG_L1RSMOK_MASK   /* Sleep State Resume OK */
#define USB_OTG_GLPMCFG_LPMCHIDX_SHIFT           (17U)
#define USB_OTG_GLPMCFG_LPMCHIDX_MASK            (0xFU << USB_OTG_GLPMCFG_LPMCHIDX_SHIFT) /* 0x001E0000 */
#define USB_OTG_GLPMCFG_LPMCHIDX                 USB_OTG_GLPMCFG_LPMCHIDX_MASK  /* LPM Channel Index */
#define USB_OTG_GLPMCFG_LPMRCNT_SHIFT            (21U)
#define USB_OTG_GLPMCFG_LPMRCNT_MASK             (0x7U << USB_OTG_GLPMCFG_LPMRCNT_SHIFT) /* 0x00E00000 */
#define USB_OTG_GLPMCFG_LPMRCNT                  USB_OTG_GLPMCFG_LPMRCNT_MASK   /* LPM retry count */
#define USB_OTG_GLPMCFG_SNDLPM_SHIFT             (24U)
#define USB_OTG_GLPMCFG_SNDLPM_MASK              (0x1U << USB_OTG_GLPMCFG_SNDLPM_SHIFT) /* 0x01000000 */
#define USB_OTG_GLPMCFG_SNDLPM                   USB_OTG_GLPMCFG_SNDLPM_MASK    /* Send LPM transaction */
#define USB_OTG_GLPMCFG_LPMRCNTSTS_SHIFT         (25U)
#define USB_OTG_GLPMCFG_LPMRCNTSTS_MASK          (0x7U << USB_OTG_GLPMCFG_LPMRCNTSTS_SHIFT) /* 0x0E000000 */
#define USB_OTG_GLPMCFG_LPMRCNTSTS               USB_OTG_GLPMCFG_LPMRCNTSTS_MASK /* LPM retry count status */
#define USB_OTG_GLPMCFG_ENBESL_SHIFT             (28U)
#define USB_OTG_GLPMCFG_ENBESL_MASK              (0x1U << USB_OTG_GLPMCFG_ENBESL_SHIFT) /* 0x10000000 */
#define USB_OTG_GLPMCFG_ENBESL                   USB_OTG_GLPMCFG_ENBESL_MASK    /* Enable best effort service latency */
/********************  Bit definition for USB_OTG_HPTXFSIZ register  ********************/
#define USB_OTG_HPTXFSIZ_PTXSA_SHIFT             (0U)
#define USB_OTG_HPTXFSIZ_PTXSA_MASK              (0xFFFFU << USB_OTG_HPTXFSIZ_PTXSA_SHIFT) /* 0x0000FFFF */
#define USB_OTG_HPTXFSIZ_PTXSA                   USB_OTG_HPTXFSIZ_PTXSA_MASK    /* Host periodic TxFIFO start address */
#define USB_OTG_HPTXFSIZ_PTXFD_SHIFT             (16U)
#define USB_OTG_HPTXFSIZ_PTXFD_MASK              (0xFFFFU << USB_OTG_HPTXFSIZ_PTXFD_SHIFT) /* 0xFFFF0000 */
#define USB_OTG_HPTXFSIZ_PTXFD                   USB_OTG_HPTXFSIZ_PTXFD_MASK    /* Host periodic TxFIFO depth */
/********************  Bit definition for USB_OTG_DIEPTXF register  ********************/
#define USB_OTG_DIEPTXF_INEPTXSA_SHIFT           (0U)
#define USB_OTG_DIEPTXF_INEPTXSA_MASK            (0xFFFFU << USB_OTG_DIEPTXF_INEPTXSA_SHIFT) /* 0x0000FFFF */
#define USB_OTG_DIEPTXF_INEPTXSA                 USB_OTG_DIEPTXF_INEPTXSA_MASK  /* IN endpoint FIFOx transmit RAM start address */
#define USB_OTG_DIEPTXF_INEPTXFD_SHIFT           (16U)
#define USB_OTG_DIEPTXF_INEPTXFD_MASK            (0xFFFFU << USB_OTG_DIEPTXF_INEPTXFD_SHIFT) /* 0xFFFF0000 */
#define USB_OTG_DIEPTXF_INEPTXFD                 USB_OTG_DIEPTXF_INEPTXFD_MASK  /* IN endpoint TxFIFO depth */
/********************  Bit definition for USB_OTG_HCFG register  ********************/
#define USB_OTG_HCFG_FSLSPCS_SHIFT               (0U)
#define USB_OTG_HCFG_FSLSPCS_MASK                (0x3U << USB_OTG_HCFG_FSLSPCS_SHIFT) /* 0x00000003 */
#define USB_OTG_HCFG_FSLSPCS                     USB_OTG_HCFG_FSLSPCS_MASK      /* FS/LS PHY clock select */
#define USB_OTG_HCFG_FSLSPCS_0                   (0x1U << USB_OTG_HCFG_FSLSPCS_SHIFT) /* 0x00000001 */
#define USB_OTG_HCFG_FSLSPCS_1                   (0x2U << USB_OTG_HCFG_FSLSPCS_SHIFT) /* 0x00000002 */
#define USB_OTG_HCFG_FSLSS_SHIFT                 (2U)
#define USB_OTG_HCFG_FSLSS_MASK                  (0x1U << USB_OTG_HCFG_FSLSS_SHIFT) /* 0x00000004 */
#define USB_OTG_HCFG_FSLSS                       USB_OTG_HCFG_FSLSS_MASK        /* FS- and LS-only support */
/********************  Bit definition for USB_OTG_HFIR register  ********************/
#define USB_OTG_HFIR_FRIVL_SHIFT                 (0U)
#define USB_OTG_HFIR_FRIVL_MASK                  (0xFFFFU << USB_OTG_HFIR_FRIVL_SHIFT) /* 0x0000FFFF */
#define USB_OTG_HFIR_FRIVL                       USB_OTG_HFIR_FRIVL_MASK        /* Frame interval */
/********************  Bit definition for USB_OTG_HFNUM register  ********************/
#define USB_OTG_HFNUM_FRNUM_SHIFT                (0U)
#define USB_OTG_HFNUM_FRNUM_MASK                 (0xFFFFU << USB_OTG_HFNUM_FRNUM_SHIFT) /* 0x0000FFFF */
#define USB_OTG_HFNUM_FRNUM                      USB_OTG_HFNUM_FRNUM_MASK       /* Frame number */
#define USB_OTG_HFNUM_FTREM_SHIFT                (16U)
#define USB_OTG_HFNUM_FTREM_MASK                 (0xFFFFU << USB_OTG_HFNUM_FTREM_SHIFT) /* 0xFFFF0000 */
#define USB_OTG_HFNUM_FTREM                      USB_OTG_HFNUM_FTREM_MASK       /* Frame time remaining */
/********************  Bit definition for USB_OTG_HPTXSTS register  ********************/
#define USB_OTG_HPTXSTS_PTXFSAVL_SHIFT           (0U)
#define USB_OTG_HPTXSTS_PTXFSAVL_MASK            (0xFFFFU << USB_OTG_HPTXSTS_PTXFSAVL_SHIFT) /* 0x0000FFFF */
#define USB_OTG_HPTXSTS_PTXFSAVL                 USB_OTG_HPTXSTS_PTXFSAVL_MASK  /* Periodic transmit data FIFO space available */
#define USB_OTG_HPTXSTS_PTXQSAV_SHIFT            (16U)
#define USB_OTG_HPTXSTS_PTXQSAV_MASK             (0xFFU << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00FF0000 */
#define USB_OTG_HPTXSTS_PTXQSAV                  USB_OTG_HPTXSTS_PTXQSAV_MASK   /* Periodic transmit request queue space available */
#define USB_OTG_HPTXSTS_PTXQSAV_0                (0x01U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00010000 */
#define USB_OTG_HPTXSTS_PTXQSAV_1                (0x02U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00020000 */
#define USB_OTG_HPTXSTS_PTXQSAV_2                (0x04U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00040000 */
#define USB_OTG_HPTXSTS_PTXQSAV_3                (0x08U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00080000 */
#define USB_OTG_HPTXSTS_PTXQSAV_4                (0x10U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00100000 */
#define USB_OTG_HPTXSTS_PTXQSAV_5                (0x20U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00200000 */
#define USB_OTG_HPTXSTS_PTXQSAV_6                (0x40U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00400000 */
#define USB_OTG_HPTXSTS_PTXQSAV_7                (0x80U << USB_OTG_HPTXSTS_PTXQSAV_SHIFT) /* 0x00800000 */
#define USB_OTG_HPTXSTS_PTXQTOP_SHIFT            (24U)
#define USB_OTG_HPTXSTS_PTXQTOP_MASK             (0xFFU << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0xFF000000 */
#define USB_OTG_HPTXSTS_PTXQTOP                  USB_OTG_HPTXSTS_PTXQTOP_MASK   /* Top of the periodic transmit request queue */
#define USB_OTG_HPTXSTS_PTXQTOP_0                (0x01U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x01000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_1                (0x02U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x02000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_2                (0x04U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x04000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_3                (0x08U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x08000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_4                (0x10U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x10000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_5                (0x20U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x20000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_6                (0x40U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x40000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_7                (0x80U << USB_OTG_HPTXSTS_PTXQTOP_SHIFT) /* 0x80000000 */
/********************  Bit definition for USB_OTG_HAINT register  ********************/
#define USB_OTG_HAINT_HAINT_SHIFT                (0U)
#define USB_OTG_HAINT_HAINT_MASK                 (0xFFFFU << USB_OTG_HAINT_HAINT_SHIFT) /* 0x0000FFFF */
#define USB_OTG_HAINT_HAINT                      USB_OTG_HAINT_HAINT_MASK       /* Channel interrupts */
/********************  Bit definition for USB_OTG_HAINTMSK register  ********************/
#define USB_OTG_HAINTMSK_HAINTM_SHIFT            (0U)
#define USB_OTG_HAINTMSK_HAINTM_MASK             (0xFFFFU << USB_OTG_HAINTMSK_HAINTM_SHIFT) /* 0x0000FFFF */
#define USB_OTG_HAINTMSK_HAINTM                  USB_OTG_HAINTMSK_HAINTM_MASK   /* Channel interrupt mask */
/********************  Bit definition for USB_OTG_HPRT register  ********************/
#define USB_OTG_HPRT_PCSTS_SHIFT                 (0U)
#define USB_OTG_HPRT_PCSTS_MASK                  (0x1U << USB_OTG_HPRT_PCSTS_SHIFT) /* 0x00000001 */
#define USB_OTG_HPRT_PCSTS                       USB_OTG_HPRT_PCSTS_MASK        /* Port connect status */
#define USB_OTG_HPRT_PCDET_SHIFT                 (1U)
#define USB_OTG_HPRT_PCDET_MASK                  (0x1U << USB_OTG_HPRT_PCDET_SHIFT) /* 0x00000002 */
#define USB_OTG_HPRT_PCDET                       USB_OTG_HPRT_PCDET_MASK        /* Port connect detected */
#define USB_OTG_HPRT_PENA_SHIFT                  (2U)
#define USB_OTG_HPRT_PENA_MASK                   (0x1U << USB_OTG_HPRT_PENA_SHIFT) /* 0x00000004 */
#define USB_OTG_HPRT_PENA                        USB_OTG_HPRT_PENA_MASK         /* Port enable */
#define USB_OTG_HPRT_PENCHNG_SHIFT               (3U)
#define USB_OTG_HPRT_PENCHNG_MASK                (0x1U << USB_OTG_HPRT_PENCHNG_SHIFT) /* 0x00000008 */
#define USB_OTG_HPRT_PENCHNG                     USB_OTG_HPRT_PENCHNG_MASK      /* Port enable/disable change */
#define USB_OTG_HPRT_POCA_SHIFT                  (4U)
#define USB_OTG_HPRT_POCA_MASK                   (0x1U << USB_OTG_HPRT_POCA_SHIFT) /* 0x00000010 */
#define USB_OTG_HPRT_POCA                        USB_OTG_HPRT_POCA_MASK         /* Port overcurrent active */
#define USB_OTG_HPRT_POCCHNG_SHIFT               (5U)
#define USB_OTG_HPRT_POCCHNG_MASK                (0x1U << USB_OTG_HPRT_POCCHNG_SHIFT) /* 0x00000020 */
#define USB_OTG_HPRT_POCCHNG                     USB_OTG_HPRT_POCCHNG_MASK      /* Port overcurrent change */
#define USB_OTG_HPRT_PRES_SHIFT                  (6U)
#define USB_OTG_HPRT_PRES_MASK                   (0x1U << USB_OTG_HPRT_PRES_SHIFT) /* 0x00000040 */
#define USB_OTG_HPRT_PRES                        USB_OTG_HPRT_PRES_MASK         /* Port resume */
#define USB_OTG_HPRT_PSUSP_SHIFT                 (7U)
#define USB_OTG_HPRT_PSUSP_MASK                  (0x1U << USB_OTG_HPRT_PSUSP_SHIFT) /* 0x00000080 */
#define USB_OTG_HPRT_PSUSP                       USB_OTG_HPRT_PSUSP_MASK        /* Port suspend */
#define USB_OTG_HPRT_PRST_SHIFT                  (8U)
#define USB_OTG_HPRT_PRST_MASK                   (0x1U << USB_OTG_HPRT_PRST_SHIFT) /* 0x00000100 */
#define USB_OTG_HPRT_PRST                        USB_OTG_HPRT_PRST_MASK         /* Port reset */
#define USB_OTG_HPRT_PLSTS_SHIFT                 (10U)
#define USB_OTG_HPRT_PLSTS_MASK                  (0x3U << USB_OTG_HPRT_PLSTS_SHIFT) /* 0x00000C00 */
#define USB_OTG_HPRT_PLSTS                       USB_OTG_HPRT_PLSTS_MASK        /* Port line status */
#define USB_OTG_HPRT_PLSTS_0                     (0x1U << USB_OTG_HPRT_PLSTS_SHIFT) /* 0x00000400 */
#define USB_OTG_HPRT_PLSTS_1                     (0x2U << USB_OTG_HPRT_PLSTS_SHIFT) /* 0x00000800 */
#define USB_OTG_HPRT_PPWR_SHIFT                  (12U)
#define USB_OTG_HPRT_PPWR_MASK                   (0x1U << USB_OTG_HPRT_PPWR_SHIFT) /* 0x00001000 */
#define USB_OTG_HPRT_PPWR                        USB_OTG_HPRT_PPWR_MASK           /* Port power */
#define USB_OTG_HPRT_PTCTL_SHIFT                 (13U)
#define USB_OTG_HPRT_PTCTL_MASK                  (0xFU << USB_OTG_HPRT_PTCTL_SHIFT) /* 0x0001E000 */
#define USB_OTG_HPRT_PTCTL                       USB_OTG_HPRT_PTCTL_MASK           /* Port test control */
#define USB_OTG_HPRT_PTCTL_0                     (0x1U << USB_OTG_HPRT_PTCTL_SHIFT) /* 0x00002000 */
#define USB_OTG_HPRT_PTCTL_1                     (0x2U << USB_OTG_HPRT_PTCTL_SHIFT) /* 0x00004000 */
#define USB_OTG_HPRT_PTCTL_2                     (0x4U << USB_OTG_HPRT_PTCTL_SHIFT) /* 0x00008000 */
#define USB_OTG_HPRT_PTCTL_3                     (0x8U << USB_OTG_HPRT_PTCTL_SHIFT) /* 0x00010000 */
#define USB_OTG_HPRT_PSPD_SHIFT                  (17U)
#define USB_OTG_HPRT_PSPD_MASK                   (0x3U << USB_OTG_HPRT_PSPD_SHIFT) /* 0x00060000 */
#define USB_OTG_HPRT_PSPD                        USB_OTG_HPRT_PSPD_MASK           /* Port speed */
#define USB_OTG_HPRT_PSPD_0                      (0x1U << USB_OTG_HPRT_PSPD_SHIFT) /* 0x00020000 */
#define USB_OTG_HPRT_PSPD_1                      (0x2U << USB_OTG_HPRT_PSPD_SHIFT) /* 0x00040000 */
/********************  Bit definition for USB_OTG_HCCHAR register  ********************/
#define USB_OTG_HCCHAR_MPSIZ_SHIFT               (0U)
#define USB_OTG_HCCHAR_MPSIZ_MASK                (0x7FFU << USB_OTG_HCCHAR_MPSIZ_SHIFT) /* 0x000007FF */
#define USB_OTG_HCCHAR_MPSIZ                     USB_OTG_HCCHAR_MPSIZ_MASK      /* Maximum packet size */
#define USB_OTG_HCCHAR_EPNUM_SHIFT               (11U)
#define USB_OTG_HCCHAR_EPNUM_MASK                (0xFU << USB_OTG_HCCHAR_EPNUM_SHIFT) /* 0x00007800 */
#define USB_OTG_HCCHAR_EPNUM                     USB_OTG_HCCHAR_EPNUM_MASK      /* Endpoint number */
#define USB_OTG_HCCHAR_EPNUM_0                   (0x1U << USB_OTG_HCCHAR_EPNUM_SHIFT) /* 0x00000800 */
#define USB_OTG_HCCHAR_EPNUM_1                   (0x2U << USB_OTG_HCCHAR_EPNUM_SHIFT) /* 0x00001000 */
#define USB_OTG_HCCHAR_EPNUM_2                   (0x4U << USB_OTG_HCCHAR_EPNUM_SHIFT) /* 0x00002000 */
#define USB_OTG_HCCHAR_EPNUM_3                   (0x8U << USB_OTG_HCCHAR_EPNUM_SHIFT) /* 0x00004000 */
#define USB_OTG_HCCHAR_EPDIR_SHIFT               (15U)
#define USB_OTG_HCCHAR_EPDIR_MASK                (0x1U << USB_OTG_HCCHAR_EPDIR_SHIFT) /* 0x00008000 */
#define USB_OTG_HCCHAR_EPDIR                     USB_OTG_HCCHAR_EPDIR_MASK      /* Endpoint direction */
#define USB_OTG_HCCHAR_LSDEV_SHIFT               (17U)
#define USB_OTG_HCCHAR_LSDEV_MASK                (0x1U << USB_OTG_HCCHAR_LSDEV_SHIFT) /* 0x00020000 */
#define USB_OTG_HCCHAR_LSDEV                     USB_OTG_HCCHAR_LSDEV_MASK      /* Low-speed device */
#define USB_OTG_HCCHAR_EPTYP_SHIFT               (18U)
#define USB_OTG_HCCHAR_EPTYP_MASK                (0x3U << USB_OTG_HCCHAR_EPTYP_SHIFT) /* 0x000C0000 */
#define USB_OTG_HCCHAR_EPTYP                     USB_OTG_HCCHAR_EPTYP_MASK      /* Endpoint type */
#define USB_OTG_HCCHAR_EPTYP_0                   (0x1U << USB_OTG_HCCHAR_EPTYP_SHIFT) /* 0x00040000 */
#define USB_OTG_HCCHAR_EPTYP_1                   (0x2U << USB_OTG_HCCHAR_EPTYP_SHIFT) /* 0x00080000 */
#define USB_OTG_HCCHAR_MC_SHIFT                  (20U)
#define USB_OTG_HCCHAR_MC_MASK                   (0x3U << USB_OTG_HCCHAR_MC_SHIFT) /* 0x00300000 */
#define USB_OTG_HCCHAR_MC                        USB_OTG_HCCHAR_MC_MASK         /* Multi Count (MC) / Error Count (EC) */
#define USB_OTG_HCCHAR_MC_0                      (0x1U << USB_OTG_HCCHAR_MC_SHIFT) /* 0x00100000 */
#define USB_OTG_HCCHAR_MC_1                      (0x2U << USB_OTG_HCCHAR_MC_SHIFT) /* 0x00200000 */
#define USB_OTG_HCCHAR_DAD_SHIFT                 (22U)
#define USB_OTG_HCCHAR_DAD_MASK                  (0x7FU << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x1FC00000 */
#define USB_OTG_HCCHAR_DAD                       USB_OTG_HCCHAR_DAD_MASK        /* Device address */
#define USB_OTG_HCCHAR_DAD_0                     (0x01U << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x00400000 */
#define USB_OTG_HCCHAR_DAD_1                     (0x02U << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x00800000 */
#define USB_OTG_HCCHAR_DAD_2                     (0x04U << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x01000000 */
#define USB_OTG_HCCHAR_DAD_3                     (0x08U << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x02000000 */
#define USB_OTG_HCCHAR_DAD_4                     (0x10U << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x04000000 */
#define USB_OTG_HCCHAR_DAD_5                     (0x20U << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x08000000 */
#define USB_OTG_HCCHAR_DAD_6                     (0x40U << USB_OTG_HCCHAR_DAD_SHIFT) /* 0x10000000 */
#define USB_OTG_HCCHAR_ODDFRM_SHIFT              (29U)
#define USB_OTG_HCCHAR_ODDFRM_MASK               (0x1U << USB_OTG_HCCHAR_ODDFRM_SHIFT) /* 0x20000000 */
#define USB_OTG_HCCHAR_ODDFRM                    USB_OTG_HCCHAR_ODDFRM_MASK     /* Odd frame */
#define USB_OTG_HCCHAR_CHDIS_SHIFT               (30U)
#define USB_OTG_HCCHAR_CHDIS_MASK                (0x1U << USB_OTG_HCCHAR_CHDIS_SHIFT) /* 0x40000000 */
#define USB_OTG_HCCHAR_CHDIS                     USB_OTG_HCCHAR_CHDIS_MASK      /* Channel disable */
#define USB_OTG_HCCHAR_CHENA_SHIFT               (31U)
#define USB_OTG_HCCHAR_CHENA_MASK                (0x1U << USB_OTG_HCCHAR_CHENA_SHIFT) /* 0x80000000 */
#define USB_OTG_HCCHAR_CHENA                     USB_OTG_HCCHAR_CHENA_MASK      /* Channel enable */
/********************  Bit definition for USB_OTG_HCSPLT register  ********************/
#define USB_OTG_HCSPLT_PRTADDR_SHIFT             (0U)
#define USB_OTG_HCSPLT_PRTADDR_MASK              (0x7FU << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x0000007F */
#define USB_OTG_HCSPLT_PRTADDR                   USB_OTG_HCSPLT_PRTADDR_MASK    /* Port address */
#define USB_OTG_HCSPLT_PRTADDR_0                 (0x01U << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x00000001 */
#define USB_OTG_HCSPLT_PRTADDR_1                 (0x02U << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x00000002 */
#define USB_OTG_HCSPLT_PRTADDR_2                 (0x04U << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x00000004 */
#define USB_OTG_HCSPLT_PRTADDR_3                 (0x08U << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x00000008 */
#define USB_OTG_HCSPLT_PRTADDR_4                 (0x10U << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x00000010 */
#define USB_OTG_HCSPLT_PRTADDR_5                 (0x20U << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x00000020 */
#define USB_OTG_HCSPLT_PRTADDR_6                 (0x40U << USB_OTG_HCSPLT_PRTADDR_SHIFT) /* 0x00000040 */
#define USB_OTG_HCSPLT_HUBADDR_SHIFT             (7U)
#define USB_OTG_HCSPLT_HUBADDR_MASK              (0x7FU << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00003F80 */
#define USB_OTG_HCSPLT_HUBADDR                   USB_OTG_HCSPLT_HUBADDR_MASK    /* Hub address */
#define USB_OTG_HCSPLT_HUBADDR_0                 (0x01U << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00000080 */
#define USB_OTG_HCSPLT_HUBADDR_1                 (0x02U << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00000100 */
#define USB_OTG_HCSPLT_HUBADDR_2                 (0x04U << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00000200 */
#define USB_OTG_HCSPLT_HUBADDR_3                 (0x08U << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00000400 */
#define USB_OTG_HCSPLT_HUBADDR_4                 (0x10U << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00000800 */
#define USB_OTG_HCSPLT_HUBADDR_5                 (0x20U << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00001000 */
#define USB_OTG_HCSPLT_HUBADDR_6                 (0x40U << USB_OTG_HCSPLT_HUBADDR_SHIFT) /* 0x00002000 */
#define USB_OTG_HCSPLT_XACTPOS_SHIFT             (14U)
#define USB_OTG_HCSPLT_XACTPOS_MASK              (0x3U << USB_OTG_HCSPLT_XACTPOS_SHIFT) /* 0x0000C000 */
#define USB_OTG_HCSPLT_XACTPOS                   USB_OTG_HCSPLT_XACTPOS_MASK    /* XACTPOS */
#define USB_OTG_HCSPLT_XACTPOS_0                 (0x1U << USB_OTG_HCSPLT_XACTPOS_SHIFT) /* 0x00004000 */
#define USB_OTG_HCSPLT_XACTPOS_1                 (0x2U << USB_OTG_HCSPLT_XACTPOS_SHIFT) /* 0x00008000 */
#define USB_OTG_HCSPLT_COMPLSPLT_SHIFT           (16U)
#define USB_OTG_HCSPLT_COMPLSPLT_MASK            (0x1U << USB_OTG_HCSPLT_COMPLSPLT_SHIFT) /* 0x00010000 */
#define USB_OTG_HCSPLT_COMPLSPLT                 USB_OTG_HCSPLT_COMPLSPLT_MASK  /* Do complete split */
#define USB_OTG_HCSPLT_SPLITEN_SHIFT             (31U)
#define USB_OTG_HCSPLT_SPLITEN_MASK              (0x1U << USB_OTG_HCSPLT_SPLITEN_SHIFT) /* 0x80000000 */
#define USB_OTG_HCSPLT_SPLITEN                   USB_OTG_HCSPLT_SPLITEN_MASK    /* Split enable */
/********************  Bit definition for USB_OTG_HCINT register  ********************/
#define USB_OTG_HCINT_XFRC_SHIFT                 (0U)
#define USB_OTG_HCINT_XFRC_MASK                  (0x1U << USB_OTG_HCINT_XFRC_SHIFT) /* 0x00000001 */
#define USB_OTG_HCINT_XFRC                       USB_OTG_HCINT_XFRC_MASK        /* Transfer completed */
#define USB_OTG_HCINT_CHH_SHIFT                  (1U)
#define USB_OTG_HCINT_CHH_MASK                   (0x1U << USB_OTG_HCINT_CHH_SHIFT) /* 0x00000002 */
#define USB_OTG_HCINT_CHH                        USB_OTG_HCINT_CHH_MASK         /* Channel halted */
#define USB_OTG_HCINT_AHBERR_SHIFT               (2U)
#define USB_OTG_HCINT_AHBERR_MASK                (0x1U << USB_OTG_HCINT_AHBERR_SHIFT) /* 0x00000004 */
#define USB_OTG_HCINT_AHBERR                     USB_OTG_HCINT_AHBERR_MASK      /* AHB error */
#define USB_OTG_HCINT_STALL_SHIFT                (3U)
#define USB_OTG_HCINT_STALL_MASK                 (0x1U << USB_OTG_HCINT_STALL_SHIFT) /* 0x00000008 */
#define USB_OTG_HCINT_STALL                      USB_OTG_HCINT_STALL_MASK       /* STALL response received interrupt */
#define USB_OTG_HCINT_NAK_SHIFT                  (4U)
#define USB_OTG_HCINT_NAK_MASK                   (0x1U << USB_OTG_HCINT_NAK_SHIFT) /* 0x00000010 */
#define USB_OTG_HCINT_NAK                        USB_OTG_HCINT_NAK_MASK         /* NAK response received interrupt */
#define USB_OTG_HCINT_ACK_SHIFT                  (5U)
#define USB_OTG_HCINT_ACK_MASK                   (0x1U << USB_OTG_HCINT_ACK_SHIFT) /* 0x00000020 */
#define USB_OTG_HCINT_ACK                        USB_OTG_HCINT_ACK_MASK         /* ACK response received/transmitted interrupt */
#define USB_OTG_HCINT_NYET_SHIFT                 (6U)
#define USB_OTG_HCINT_NYET_MASK                  (0x1U << USB_OTG_HCINT_NYET_SHIFT) /* 0x00000040 */
#define USB_OTG_HCINT_NYET                       USB_OTG_HCINT_NYET_MASK        /* Response received interrupt */
#define USB_OTG_HCINT_TXERR_SHIFT                (7U)
#define USB_OTG_HCINT_TXERR_MASK                 (0x1U << USB_OTG_HCINT_TXERR_SHIFT) /* 0x00000080 */
#define USB_OTG_HCINT_TXERR                      USB_OTG_HCINT_TXERR_MASK       /* Transaction error */
#define USB_OTG_HCINT_BBERR_SHIFT                (8U)
#define USB_OTG_HCINT_BBERR_MASK                 (0x1U << USB_OTG_HCINT_BBERR_SHIFT) /* 0x00000100 */
#define USB_OTG_HCINT_BBERR                      USB_OTG_HCINT_BBERR_MASK       /* Babble error */
#define USB_OTG_HCINT_FRMOR_SHIFT                (9U)
#define USB_OTG_HCINT_FRMOR_MASK                 (0x1U << USB_OTG_HCINT_FRMOR_SHIFT) /* 0x00000200 */
#define USB_OTG_HCINT_FRMOR                      USB_OTG_HCINT_FRMOR_MASK       /* Frame overrun */
#define USB_OTG_HCINT_DTERR_SHIFT                (10U)
#define USB_OTG_HCINT_DTERR_MASK                 (0x1U << USB_OTG_HCINT_DTERR_SHIFT) /* 0x00000400 */
#define USB_OTG_HCINT_DTERR                      USB_OTG_HCINT_DTERR_MASK       /* Data toggle error */
/********************  Bit definition for USB_OTG_HCINTMSK register  ********************/
#define USB_OTG_HCINTMSK_XFRCM_SHIFT             (0U)
#define USB_OTG_HCINTMSK_XFRCM_MASK              (0x1U << USB_OTG_HCINTMSK_XFRCM_SHIFT) /* 0x00000001 */
#define USB_OTG_HCINTMSK_XFRCM                   USB_OTG_HCINTMSK_XFRCM_MASK    /* Transfer completed mask */
#define USB_OTG_HCINTMSK_CHHM_SHIFT              (1U)
#define USB_OTG_HCINTMSK_CHHM_MASK               (0x1U << USB_OTG_HCINTMSK_CHHM_SHIFT) /* 0x00000002 */
#define USB_OTG_HCINTMSK_CHHM                    USB_OTG_HCINTMSK_CHHM_MASK     /* Channel halted mask */
#define USB_OTG_HCINTMSK_AHBERR_SHIFT            (2U)
#define USB_OTG_HCINTMSK_AHBERR_MASK             (0x1U << USB_OTG_HCINTMSK_AHBERR_SHIFT) /* 0x00000004 */
#define USB_OTG_HCINTMSK_AHBERR                  USB_OTG_HCINTMSK_AHBERR_MASK   /* AHB error */
#define USB_OTG_HCINTMSK_STALLM_SHIFT            (3U)
#define USB_OTG_HCINTMSK_STALLM_MASK             (0x1U << USB_OTG_HCINTMSK_STALLM_SHIFT) /* 0x00000008 */
#define USB_OTG_HCINTMSK_STALLM                  USB_OTG_HCINTMSK_STALLM_MASK   /* STALL response received interrupt mask */
#define USB_OTG_HCINTMSK_NAKM_SHIFT              (4U)
#define USB_OTG_HCINTMSK_NAKM_MASK               (0x1U << USB_OTG_HCINTMSK_NAKM_SHIFT) /* 0x00000010 */
#define USB_OTG_HCINTMSK_NAKM                    USB_OTG_HCINTMSK_NAKM_MASK     /* NAK response received interrupt mask */
#define USB_OTG_HCINTMSK_ACKM_SHIFT              (5U)
#define USB_OTG_HCINTMSK_ACKM_MASK               (0x1U << USB_OTG_HCINTMSK_ACKM_SHIFT) /* 0x00000020 */
#define USB_OTG_HCINTMSK_ACKM                    USB_OTG_HCINTMSK_ACKM_MASK     /* ACK response received/transmitted interrupt mask */
#define USB_OTG_HCINTMSK_NYET_SHIFT              (6U)
#define USB_OTG_HCINTMSK_NYET_MASK               (0x1U << USB_OTG_HCINTMSK_NYET_SHIFT) /* 0x00000040 */
#define USB_OTG_HCINTMSK_NYET                    USB_OTG_HCINTMSK_NYET_MASK     /* response received interrupt mask */
#define USB_OTG_HCINTMSK_TXERRM_SHIFT            (7U)
#define USB_OTG_HCINTMSK_TXERRM_MASK             (0x1U << USB_OTG_HCINTMSK_TXERRM_SHIFT) /* 0x00000080 */
#define USB_OTG_HCINTMSK_TXERRM                  USB_OTG_HCINTMSK_TXERRM_MASK   /* Transaction error mask */
#define USB_OTG_HCINTMSK_BBERRM_SHIFT            (8U)
#define USB_OTG_HCINTMSK_BBERRM_MASK             (0x1U << USB_OTG_HCINTMSK_BBERRM_SHIFT) /* 0x00000100 */
#define USB_OTG_HCINTMSK_BBERRM                  USB_OTG_HCINTMSK_BBERRM_MASK   /* Babble error mask */
#define USB_OTG_HCINTMSK_FRMORM_SHIFT            (9U)
#define USB_OTG_HCINTMSK_FRMORM_MASK             (0x1U << USB_OTG_HCINTMSK_FRMORM_SHIFT) /* 0x00000200 */
#define USB_OTG_HCINTMSK_FRMORM                  USB_OTG_HCINTMSK_FRMORM_MASK   /* Frame overrun mask */
#define USB_OTG_HCINTMSK_DTERRM_SHIFT            (10U)
#define USB_OTG_HCINTMSK_DTERRM_MASK             (0x1U << USB_OTG_HCINTMSK_DTERRM_SHIFT) /* 0x00000400 */
#define USB_OTG_HCINTMSK_DTERRM                  USB_OTG_HCINTMSK_DTERRM_MASK   /* Data toggle error mask */
/********************  Bit definition for USB_OTG_HCTSIZ register  ********************/
#define USB_OTG_HCTSIZ_XFRSIZ_SHIFT              (0U)
#define USB_OTG_HCTSIZ_XFRSIZ_MASK               (0x7FFFFU << USB_OTG_HCTSIZ_XFRSIZ_SHIFT) /* 0x0007FFFF */
#define USB_OTG_HCTSIZ_XFRSIZ                    USB_OTG_HCTSIZ_XFRSIZ_MASK     /* Transfer size */
#define USB_OTG_HCTSIZ_PKTCNT_SHIFT              (19U)
#define USB_OTG_HCTSIZ_PKTCNT_MASK               (0x3FFU << USB_OTG_HCTSIZ_PKTCNT_SHIFT) /* 0x1FF80000 */
#define USB_OTG_HCTSIZ_PKTCNT                    USB_OTG_HCTSIZ_PKTCNT_MASK     /* Packet count */
#define USB_OTG_HCTSIZ_DOPING_SHIFT              (31U)
#define USB_OTG_HCTSIZ_DOPING_MASK               (0x1U << USB_OTG_HCTSIZ_DOPING_SHIFT) /* 0x80000000 */
#define USB_OTG_HCTSIZ_DOPING                    USB_OTG_HCTSIZ_DOPING_MASK     /* Do PING */
#define USB_OTG_HCTSIZ_DPID_SHIFT                (29U)
#define USB_OTG_HCTSIZ_DPID_MASK                 (0x3U << USB_OTG_HCTSIZ_DPID_SHIFT) /* 0x60000000 */
#define USB_OTG_HCTSIZ_DPID                      USB_OTG_HCTSIZ_DPID_MASK       /* Data PID */
#define USB_OTG_HCTSIZ_DPID_0                    (0x1U << USB_OTG_HCTSIZ_DPID_SHIFT) /* 0x20000000 */
#define USB_OTG_HCTSIZ_DPID_1                    (0x2U << USB_OTG_HCTSIZ_DPID_SHIFT) /* 0x40000000 */
/********************  Bit definition for USB_OTG_HCDMA register  ********************/
#define USB_OTG_HCDMA_DMAADDR_SHIFT              (0U)
#define USB_OTG_HCDMA_DMAADDR_MASK               (0xFFFFFFFFU << USB_OTG_HCDMA_DMAADDR_SHIFT) /* 0xFFFFFFFF */
#define USB_OTG_HCDMA_DMAADDR                    USB_OTG_HCDMA_DMAADDR_MASK     /* DMA address */
/********************  Bit definition for USB_OTG_DCFG register  ********************/
#define USB_OTG_DCFG_DSPD_SHIFT                  (0U)
#define USB_OTG_DCFG_DSPD_MASK                   (0x3U << USB_OTG_DCFG_DSPD_SHIFT) /* 0x00000003 */
#define USB_OTG_DCFG_DSPD                        USB_OTG_DCFG_DSPD_MASK         /* Device speed */
#define USB_OTG_DCFG_DSPD_0                      (0x1U << USB_OTG_DCFG_DSPD_SHIFT) /* 0x00000001 */
#define USB_OTG_DCFG_DSPD_1                      (0x2U << USB_OTG_DCFG_DSPD_SHIFT) /* 0x00000002 */
#define USB_OTG_DCFG_NZLSOHSK_SHIFT              (2U)
#define USB_OTG_DCFG_NZLSOHSK_MASK               (0x1U << USB_OTG_DCFG_NZLSOHSK_SHIFT) /* 0x00000004 */
#define USB_OTG_DCFG_NZLSOHSK                    USB_OTG_DCFG_NZLSOHSK_MASK     /* Nonzero-length status OUT handshake */
#define USB_OTG_DCFG_DAD_SHIFT                   (4U)
#define USB_OTG_DCFG_DAD_MASK                    (0x7FU << USB_OTG_DCFG_DAD_SHIFT) /* 0x000007F0 */
#define USB_OTG_DCFG_DAD                         USB_OTG_DCFG_DAD_MASK          /* Device address */
#define USB_OTG_DCFG_DAD_0                       (0x01U << USB_OTG_DCFG_DAD_SHIFT) /* 0x00000010 */
#define USB_OTG_DCFG_DAD_1                       (0x02U << USB_OTG_DCFG_DAD_SHIFT) /* 0x00000020 */
#define USB_OTG_DCFG_DAD_2                       (0x04U << USB_OTG_DCFG_DAD_SHIFT) /* 0x00000040 */
#define USB_OTG_DCFG_DAD_3                       (0x08U << USB_OTG_DCFG_DAD_SHIFT) /* 0x00000080 */
#define USB_OTG_DCFG_DAD_4                       (0x10U << USB_OTG_DCFG_DAD_SHIFT) /* 0x00000100 */
#define USB_OTG_DCFG_DAD_5                       (0x20U << USB_OTG_DCFG_DAD_SHIFT) /* 0x00000200 */
#define USB_OTG_DCFG_DAD_6                       (0x40U << USB_OTG_DCFG_DAD_SHIFT) /* 0x00000400 */
#define USB_OTG_DCFG_PFIVL_SHIFT                 (11U)
#define USB_OTG_DCFG_PFIVL_MASK                  (0x3U << USB_OTG_DCFG_PFIVL_SHIFT) /* 0x00001800 */
#define USB_OTG_DCFG_PFIVL                       USB_OTG_DCFG_PFIVL_MASK        /* Periodic (micro)frame interval */
#define USB_OTG_DCFG_PFIVL_0                     (0x1U << USB_OTG_DCFG_PFIVL_SHIFT) /* 0x00000800 */
#define USB_OTG_DCFG_PFIVL_1                     (0x2U << USB_OTG_DCFG_PFIVL_SHIFT) /* 0x00001000 */
#define USB_OTG_DCFG_PERSCHIVL_SHIFT             (24U)
#define USB_OTG_DCFG_PERSCHIVL_MASK              (0x3U << USB_OTG_DCFG_PERSCHIVL_SHIFT) /* 0x03000000 */
#define USB_OTG_DCFG_PERSCHIVL                   USB_OTG_DCFG_PERSCHIVL_MASK    /* Periodic scheduling interval */
#define USB_OTG_DCFG_PERSCHIVL_0                 (0x1U << USB_OTG_DCFG_PERSCHIVL_SHIFT) /* 0x01000000 */
#define USB_OTG_DCFG_PERSCHIVL_1                 (0x2U << USB_OTG_DCFG_PERSCHIVL_SHIFT) /* 0x02000000 */
/********************  Bit definition for USB_OTG_DCTL register  ********************/
#define USB_OTG_DCTL_RWUSIG_SHIFT                (0U)
#define USB_OTG_DCTL_RWUSIG_MASK                 (0x1U << USB_OTG_DCTL_RWUSIG_SHIFT) /* 0x00000001 */
#define USB_OTG_DCTL_RWUSIG                      USB_OTG_DCTL_RWUSIG_MASK       /* Remote wakeup signaling */
#define USB_OTG_DCTL_SDIS_SHIFT                  (1U)
#define USB_OTG_DCTL_SDIS_MASK                   (0x1U << USB_OTG_DCTL_SDIS_SHIFT) /* 0x00000002 */
#define USB_OTG_DCTL_SDIS                        USB_OTG_DCTL_SDIS_MASK         /* Soft disconnect */
#define USB_OTG_DCTL_GINSTS_SHIFT                (2U)
#define USB_OTG_DCTL_GINSTS_MASK                 (0x1U << USB_OTG_DCTL_GINSTS_SHIFT) /* 0x00000004 */
#define USB_OTG_DCTL_GINSTS                      USB_OTG_DCTL_GINSTS_MASK       /* Global IN NAK status */
#define USB_OTG_DCTL_GONSTS_SHIFT                (3U)
#define USB_OTG_DCTL_GONSTS_MASK                 (0x1U << USB_OTG_DCTL_GONSTS_SHIFT) /* 0x00000008 */
#define USB_OTG_DCTL_GONSTS                      USB_OTG_DCTL_GONSTS_MASK       /* Global OUT NAK status */
#define USB_OTG_DCTL_TCTL_SHIFT                  (4U)
#define USB_OTG_DCTL_TCTL_MASK                   (0x7U << USB_OTG_DCTL_TCTL_SHIFT) /* 0x00000070 */
#define USB_OTG_DCTL_TCTL                        USB_OTG_DCTL_TCTL_MASK         /* Test control */
#define USB_OTG_DCTL_TCTL_0                      (0x1U << USB_OTG_DCTL_TCTL_SHIFT) /* 0x00000010 */
#define USB_OTG_DCTL_TCTL_1                      (0x2U << USB_OTG_DCTL_TCTL_SHIFT) /* 0x00000020 */
#define USB_OTG_DCTL_TCTL_2                      (0x4U << USB_OTG_DCTL_TCTL_SHIFT) /* 0x00000040 */
#define USB_OTG_DCTL_SGINAK_SHIFT                (7U)
#define USB_OTG_DCTL_SGINAK_MASK                 (0x1U << USB_OTG_DCTL_SGINAK_SHIFT) /* 0x00000080 */
#define USB_OTG_DCTL_SGINAK                      USB_OTG_DCTL_SGINAK_MASK       /* Set global IN NAK */
#define USB_OTG_DCTL_CGINAK_SHIFT                (8U)
#define USB_OTG_DCTL_CGINAK_MASK                 (0x1U << USB_OTG_DCTL_CGINAK_SHIFT) /* 0x00000100 */
#define USB_OTG_DCTL_CGINAK                      USB_OTG_DCTL_CGINAK_MASK       /* Clear global IN NAK */
#define USB_OTG_DCTL_SGONAK_SHIFT                (9U)
#define USB_OTG_DCTL_SGONAK_MASK                 (0x1U << USB_OTG_DCTL_SGONAK_SHIFT) /* 0x00000200 */
#define USB_OTG_DCTL_SGONAK                      USB_OTG_DCTL_SGONAK_MASK       /* Set global OUT NAK */
#define USB_OTG_DCTL_CGONAK_SHIFT                (10U)
#define USB_OTG_DCTL_CGONAK_MASK                 (0x1U << USB_OTG_DCTL_CGONAK_SHIFT) /* 0x00000400 */
#define USB_OTG_DCTL_CGONAK                      USB_OTG_DCTL_CGONAK_MASK       /* Clear global OUT NAK */
#define USB_OTG_DCTL_POPRGDNE_SHIFT              (11U)
#define USB_OTG_DCTL_POPRGDNE_MASK               (0x1U << USB_OTG_DCTL_POPRGDNE_SHIFT) /* 0x00000800 */
#define USB_OTG_DCTL_POPRGDNE                    USB_OTG_DCTL_POPRGDNE_MASK     /* Power-on programming done */
/********************  Bit definition for USB_OTG_DSTS register  ********************/
#define USB_OTG_DSTS_SUSPSTS_SHIFT               (0U)
#define USB_OTG_DSTS_SUSPSTS_MASK                (0x1U << USB_OTG_DSTS_SUSPSTS_SHIFT) /* 0x00000001 */
#define USB_OTG_DSTS_SUSPSTS                     USB_OTG_DSTS_SUSPSTS_MASK      /* Suspend status */
#define USB_OTG_DSTS_ENUMSPD_SHIFT               (1U)
#define USB_OTG_DSTS_ENUMSPD_MASK                (0x3U << USB_OTG_DSTS_ENUMSPD_SHIFT) /* 0x00000006 */
#define USB_OTG_DSTS_ENUMSPD                     USB_OTG_DSTS_ENUMSPD_MASK      /* Enumerated speed */
#define USB_OTG_DSTS_ENUMSPD_0                   (0x1U << USB_OTG_DSTS_ENUMSPD_SHIFT) /* 0x00000002 */
#define USB_OTG_DSTS_ENUMSPD_1                   (0x2U << USB_OTG_DSTS_ENUMSPD_SHIFT) /* 0x00000004 */
#define USB_OTG_DSTS_EERR_SHIFT                  (3U)
#define USB_OTG_DSTS_EERR_MASK                   (0x1U << USB_OTG_DSTS_EERR_SHIFT) /* 0x00000008 */
#define USB_OTG_DSTS_EERR                        USB_OTG_DSTS_EERR_MASK         /* Erratic error */
#define USB_OTG_DSTS_FNSOF_SHIFT                 (8U)
#define USB_OTG_DSTS_FNSOF_MASK                  (0x3FFFU << USB_OTG_DSTS_FNSOF_SHIFT) /* 0x003FFF00 */
#define USB_OTG_DSTS_FNSOF                       USB_OTG_DSTS_FNSOF_MASK        /* Frame number of the received SOF */
/********************  Bit definition for USB_OTG_DIEPMSK register  ********************/
#define USB_OTG_DIEPMSK_XFRCM_SHIFT              (0U)
#define USB_OTG_DIEPMSK_XFRCM_MASK               (0x1U << USB_OTG_DIEPMSK_XFRCM_SHIFT) /* 0x00000001 */
#define USB_OTG_DIEPMSK_XFRCM                    USB_OTG_DIEPMSK_XFRCM_MASK     /* Transfer completed interrupt mask */
#define USB_OTG_DIEPMSK_EPDM_SHIFT               (1U)
#define USB_OTG_DIEPMSK_EPDM_MASK                (0x1U << USB_OTG_DIEPMSK_EPDM_SHIFT) /* 0x00000002 */
#define USB_OTG_DIEPMSK_EPDM                     USB_OTG_DIEPMSK_EPDM_MASK      /* Endpoint disabled interrupt mask */
#define USB_OTG_DIEPMSK_TOM_SHIFT                (3U)
#define USB_OTG_DIEPMSK_TOM_MASK                 (0x1U << USB_OTG_DIEPMSK_TOM_SHIFT) /* 0x00000008 */
#define USB_OTG_DIEPMSK_TOM                      USB_OTG_DIEPMSK_TOM_MASK       /* Timeout condition mask (nonisochronous endpoints) */
#define USB_OTG_DIEPMSK_ITTXFEMSK_SHIFT          (4U)
#define USB_OTG_DIEPMSK_ITTXFEMSK_MASK           (0x1U << USB_OTG_DIEPMSK_ITTXFEMSK_SHIFT) /* 0x00000010 */
#define USB_OTG_DIEPMSK_ITTXFEMSK                USB_OTG_DIEPMSK_ITTXFEMSK_MASK /* IN token received when TxFIFO empty mask */
#define USB_OTG_DIEPMSK_INEPNMM_SHIFT            (5U)
#define USB_OTG_DIEPMSK_INEPNMM_MASK             (0x1U << USB_OTG_DIEPMSK_INEPNMM_SHIFT) /* 0x00000020 */
#define USB_OTG_DIEPMSK_INEPNMM                  USB_OTG_DIEPMSK_INEPNMM_MASK   /* IN token received with EP mismatch mask */
#define USB_OTG_DIEPMSK_INEPNEM_SHIFT            (6U)
#define USB_OTG_DIEPMSK_INEPNEM_MASK             (0x1U << USB_OTG_DIEPMSK_INEPNEM_SHIFT) /* 0x00000040 */
#define USB_OTG_DIEPMSK_INEPNEM                  USB_OTG_DIEPMSK_INEPNEM_MASK   /* IN endpoint NAK effective mask */
#define USB_OTG_DIEPMSK_TXFURM_SHIFT             (8U)
#define USB_OTG_DIEPMSK_TXFURM_MASK              (0x1U << USB_OTG_DIEPMSK_TXFURM_SHIFT) /* 0x00000100 */
#define USB_OTG_DIEPMSK_TXFURM                   USB_OTG_DIEPMSK_TXFURM_MASK    /* FIFO underrun mask */
#define USB_OTG_DIEPMSK_BIM_SHIFT                (9U)
#define USB_OTG_DIEPMSK_BIM_MASK                 (0x1U << USB_OTG_DIEPMSK_BIM_SHIFT) /* 0x00000200 */
#define USB_OTG_DIEPMSK_BIM                      USB_OTG_DIEPMSK_BIM_MASK       /* BNA interrupt mask */
/********************  Bit definition for USB_OTG_DOEPMSK register  ********************/
#define USB_OTG_DOEPMSK_XFRCM_SHIFT              (0U)
#define USB_OTG_DOEPMSK_XFRCM_MASK               (0x1U << USB_OTG_DOEPMSK_XFRCM_SHIFT) /* 0x00000001 */
#define USB_OTG_DOEPMSK_XFRCM                    USB_OTG_DOEPMSK_XFRCM_MASK     /* Transfer completed interrupt mask */
#define USB_OTG_DOEPMSK_EPDM_SHIFT               (1U)
#define USB_OTG_DOEPMSK_EPDM_MASK                (0x1U << USB_OTG_DOEPMSK_EPDM_SHIFT) /* 0x00000002 */
#define USB_OTG_DOEPMSK_EPDM                     USB_OTG_DOEPMSK_EPDM_MASK      /* Endpoint disabled interrupt mask */
#define USB_OTG_DOEPMSK_STUPM_SHIFT              (3U)
#define USB_OTG_DOEPMSK_STUPM_MASK               (0x1U << USB_OTG_DOEPMSK_STUPM_SHIFT) /* 0x00000008 */
#define USB_OTG_DOEPMSK_STUPM                    USB_OTG_DOEPMSK_STUPM_MASK     /* SETUP phase done mask */
#define USB_OTG_DOEPMSK_OTEPDM_SHIFT             (4U)
#define USB_OTG_DOEPMSK_OTEPDM_MASK              (0x1U << USB_OTG_DOEPMSK_OTEPDM_SHIFT) /* 0x00000010 */
#define USB_OTG_DOEPMSK_OTEPDM                   USB_OTG_DOEPMSK_OTEPDM_MASK    /* OUT token received when endpoint disabled mask */
#define USB_OTG_DOEPMSK_OTEPSPRM_SHIFT           (5U)
#define USB_OTG_DOEPMSK_OTEPSPRM_MASK            (0x1U << USB_OTG_DOEPMSK_OTEPSPRM_SHIFT) /* 0x00000020 */
#define USB_OTG_DOEPMSK_OTEPSPRM                 USB_OTG_DOEPMSK_OTEPSPRM_MASK  /* Status Phase Received mask */
#define USB_OTG_DOEPMSK_B2BSTUP_SHIFT            (6U)
#define USB_OTG_DOEPMSK_B2BSTUP_MASK             (0x1U << USB_OTG_DOEPMSK_B2BSTUP_SHIFT) /* 0x00000040 */
#define USB_OTG_DOEPMSK_B2BSTUP                  USB_OTG_DOEPMSK_B2BSTUP_MASK   /* Back-to-back SETUP packets received mask */
#define USB_OTG_DOEPMSK_OPEM_SHIFT               (8U)
#define USB_OTG_DOEPMSK_OPEM_MASK                (0x1U << USB_OTG_DOEPMSK_OPEM_SHIFT) /* 0x00000100 */
#define USB_OTG_DOEPMSK_OPEM                     USB_OTG_DOEPMSK_OPEM_MASK      /* OUT packet error mask */
#define USB_OTG_DOEPMSK_BOIM_SHIFT               (9U)
#define USB_OTG_DOEPMSK_BOIM_MASK                (0x1U << USB_OTG_DOEPMSK_BOIM_SHIFT) /* 0x00000200 */
#define USB_OTG_DOEPMSK_BOIM                     USB_OTG_DOEPMSK_BOIM_MASK      /* BNA interrupt mask */
/********************  Bit definition for USB_OTG_DAINT register  ********************/
#define USB_OTG_DAINT_IEPINT_SHIFT               (0U)
#define USB_OTG_DAINT_IEPINT_MASK                (0xFFFFU << USB_OTG_DAINT_IEPINT_SHIFT) /* 0x0000FFFF */
#define USB_OTG_DAINT_IEPINT                     USB_OTG_DAINT_IEPINT_MASK      /* IN endpoint interrupt bits */
#define USB_OTG_DAINT_OEPINT_SHIFT               (16U)
#define USB_OTG_DAINT_OEPINT_MASK                (0xFFFFU << USB_OTG_DAINT_OEPINT_SHIFT) /* 0xFFFF0000 */
#define USB_OTG_DAINT_OEPINT                     USB_OTG_DAINT_OEPINT_MASK      /* OUT endpoint interrupt bits */
/********************  Bit definition for USB_OTG_DAINTMSK register  ********************/
#define USB_OTG_DAINTMSK_IEPM_SHIFT              (0U)
#define USB_OTG_DAINTMSK_IEPM_MASK               (0xFFFFU << USB_OTG_DAINTMSK_IEPM_SHIFT) /* 0x0000FFFF */
#define USB_OTG_DAINTMSK_IEPM                    USB_OTG_DAINTMSK_IEPM_MASK     /* IN EP interrupt mask bits */
#define USB_OTG_DAINTMSK_OEPM_SHIFT              (16U)
#define USB_OTG_DAINTMSK_OEPM_MASK               (0xFFFFU << USB_OTG_DAINTMSK_OEPM_SHIFT) /* 0xFFFF0000 */
#define USB_OTG_DAINTMSK_OEPM                    USB_OTG_DAINTMSK_OEPM_MASK     /* OUT EP interrupt mask bits */
/********************  Bit definition for USB_OTG_DTHRCTL register  ********************/
#define USB_OTG_DTHRCTL_NONISOTHREN_SHIFT        (0U)
#define USB_OTG_DTHRCTL_NONISOTHREN_MASK         (0x1U << USB_OTG_DTHRCTL_NONISOTHREN_SHIFT) /* 0x00000001 */
#define USB_OTG_DTHRCTL_NONISOTHREN              USB_OTG_DTHRCTL_NONISOTHREN_MASK /* Nonisochronous IN endpoints threshold enable */
#define USB_OTG_DTHRCTL_ISOTHREN_SHIFT           (1U)
#define USB_OTG_DTHRCTL_ISOTHREN_MASK            (0x1U << USB_OTG_DTHRCTL_ISOTHREN_SHIFT) /* 0x00000002 */
#define USB_OTG_DTHRCTL_ISOTHREN                 USB_OTG_DTHRCTL_ISOTHREN_MASK  /* ISO IN endpoint threshold enable */

#define USB_OTG_DTHRCTL_TXTHRLEN_SHIFT           (2U)
#define USB_OTG_DTHRCTL_TXTHRLEN_MASK            (0x1FFU << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x000007FC */
#define USB_OTG_DTHRCTL_TXTHRLEN                 USB_OTG_DTHRCTL_TXTHRLEN_MASK  /* Transmit threshold length */
#define USB_OTG_DTHRCTL_TXTHRLEN_0               (0x001U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000004 */
#define USB_OTG_DTHRCTL_TXTHRLEN_1               (0x002U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000008 */
#define USB_OTG_DTHRCTL_TXTHRLEN_2               (0x004U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000010 */
#define USB_OTG_DTHRCTL_TXTHRLEN_3               (0x008U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000020 */
#define USB_OTG_DTHRCTL_TXTHRLEN_4               (0x010U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000040 */
#define USB_OTG_DTHRCTL_TXTHRLEN_5               (0x020U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000080 */
#define USB_OTG_DTHRCTL_TXTHRLEN_6               (0x040U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000100 */
#define USB_OTG_DTHRCTL_TXTHRLEN_7               (0x080U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000200 */
#define USB_OTG_DTHRCTL_TXTHRLEN_8               (0x100U << USB_OTG_DTHRCTL_TXTHRLEN_SHIFT) /* 0x00000400 */
#define USB_OTG_DTHRCTL_RXTHREN_SHIFT            (16U)
#define USB_OTG_DTHRCTL_RXTHREN_MASK             (0x1U << USB_OTG_DTHRCTL_RXTHREN_SHIFT) /* 0x00010000 */
#define USB_OTG_DTHRCTL_RXTHREN                  USB_OTG_DTHRCTL_RXTHREN_MASK   /* Receive threshold enable */

#define USB_OTG_DTHRCTL_RXTHRLEN_SHIFT           (17U)
#define USB_OTG_DTHRCTL_RXTHRLEN_MASK            (0x1FFU << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x03FE0000 */
#define USB_OTG_DTHRCTL_RXTHRLEN                 USB_OTG_DTHRCTL_RXTHRLEN_MASK  /* Receive threshold length */
#define USB_OTG_DTHRCTL_RXTHRLEN_0               (0x001U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x00020000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_1               (0x002U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x00040000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_2               (0x004U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x00080000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_3               (0x008U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x00100000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_4               (0x010U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x00200000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_5               (0x020U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x00400000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_6               (0x040U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x00800000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_7               (0x080U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x01000000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_8               (0x100U << USB_OTG_DTHRCTL_RXTHRLEN_SHIFT) /* 0x02000000 */
#define USB_OTG_DTHRCTL_ARPEN_SHIFT              (27U)
#define USB_OTG_DTHRCTL_ARPEN_MASK               (0x1U << USB_OTG_DTHRCTL_ARPEN_SHIFT) /* 0x08000000 */
#define USB_OTG_DTHRCTL_ARPEN                    USB_OTG_DTHRCTL_ARPEN_MASK     /* Arbiter parking enable */
/********************  Bit definition for USB_OTG_DIEPEMPMSK register  ********************/
#define USB_OTG_DIEPEMPMSK_INEPTXFEM_SHIFT       (0U)
#define USB_OTG_DIEPEMPMSK_INEPTXFEM_MASK        (0xFFFFU << USB_OTG_DIEPEMPMSK_INEPTXFEM_SHIFT) /* 0x0000FFFF */
#define USB_OTG_DIEPEMPMSK_INEPTXFEM             USB_OTG_DIEPEMPMSK_INEPTXFEM_MASK /* IN EP Tx FIFO empty interrupt mask bits */
/********************  Bit definition for USB_OTG_DEACHINT register  ********************/
#define USB_OTG_DEACHINT_IEP1INT_SHIFT           (1U)
#define USB_OTG_DEACHINT_IEP1INT_MASK            (0x1U << USB_OTG_DEACHINT_IEP1INT_SHIFT) /* 0x00000002 */
#define USB_OTG_DEACHINT_IEP1INT                 USB_OTG_DEACHINT_IEP1INT_MASK  /* IN endpoint 1interrupt bit */
#define USB_OTG_DEACHINT_OEP1INT_SHIFT           (17U)
#define USB_OTG_DEACHINT_OEP1INT_MASK            (0x1U << USB_OTG_DEACHINT_OEP1INT_SHIFT) /* 0x00020000 */
#define USB_OTG_DEACHINT_OEP1INT                 USB_OTG_DEACHINT_OEP1INT_MASK  /* OUT endpoint 1 interrupt bit */
/********************  Bit definition for USB_OTG_DEACHINTMSK register  ********************/
#define USB_OTG_DEACHINTMSK_IEP1INTM_SHIFT       (1U)
#define USB_OTG_DEACHINTMSK_IEP1INTM_MASK        (0x1U << USB_OTG_DEACHINTMSK_IEP1INTM_SHIFT) /* 0x00000002 */
#define USB_OTG_DEACHINTMSK_IEP1INTM             USB_OTG_DEACHINTMSK_IEP1INTM_MASK /* IN Endpoint 1 interrupt mask bit */
#define USB_OTG_DEACHINTMSK_OEP1INTM_SHIFT       (17U)
#define USB_OTG_DEACHINTMSK_OEP1INTM_MASK        (0x1U << USB_OTG_DEACHINTMSK_OEP1INTM_SHIFT) /* 0x00020000 */
#define USB_OTG_DEACHINTMSK_OEP1INTM             USB_OTG_DEACHINTMSK_OEP1INTM_MASK /* OUT Endpoint 1 interrupt mask bit */
/********************  Bit definition for USB_OTG_DIEPEACHMSK1 register  ********************/
#define USB_OTG_DIEPEACHMSK1_XFRCM_SHIFT         (0U)
#define USB_OTG_DIEPEACHMSK1_XFRCM_MASK          (0x1U << USB_OTG_DIEPEACHMSK1_XFRCM_SHIFT) /* 0x00000001 */
#define USB_OTG_DIEPEACHMSK1_XFRCM               USB_OTG_DIEPEACHMSK1_XFRCM_MASK /* Transfer completed interrupt mask */
#define USB_OTG_DIEPEACHMSK1_EPDM_SHIFT          (1U)
#define USB_OTG_DIEPEACHMSK1_EPDM_MASK           (0x1U << USB_OTG_DIEPEACHMSK1_EPDM_SHIFT) /* 0x00000002 */
#define USB_OTG_DIEPEACHMSK1_EPDM                USB_OTG_DIEPEACHMSK1_EPDM_MASK /* Endpoint disabled interrupt mask */
#define USB_OTG_DIEPEACHMSK1_TOM_SHIFT           (3U)
#define USB_OTG_DIEPEACHMSK1_TOM_MASK            (0x1U << USB_OTG_DIEPEACHMSK1_TOM_SHIFT) /* 0x00000008 */
#define USB_OTG_DIEPEACHMSK1_TOM                 USB_OTG_DIEPEACHMSK1_TOM_MASK  /* Timeout condition mask (nonisochronous endpoints) */
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK_SHIFT     (4U)
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK_MASK      (0x1U << USB_OTG_DIEPEACHMSK1_ITTXFEMSK_SHIFT) /* 0x00000010 */
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK           USB_OTG_DIEPEACHMSK1_ITTXFEMSK_MASK /* IN token received when TxFIFO empty mask */
#define USB_OTG_DIEPEACHMSK1_INEPNMM_SHIFT       (5U)
#define USB_OTG_DIEPEACHMSK1_INEPNMM_MASK        (0x1U << USB_OTG_DIEPEACHMSK1_INEPNMM_SHIFT) /* 0x00000020 */
#define USB_OTG_DIEPEACHMSK1_INEPNMM             USB_OTG_DIEPEACHMSK1_INEPNMM_MASK /* IN token received with EP mismatch mask */
#define USB_OTG_DIEPEACHMSK1_INEPNEM_SHIFT       (6U)
#define USB_OTG_DIEPEACHMSK1_INEPNEM_MASK        (0x1U << USB_OTG_DIEPEACHMSK1_INEPNEM_SHIFT) /* 0x00000040 */
#define USB_OTG_DIEPEACHMSK1_INEPNEM             USB_OTG_DIEPEACHMSK1_INEPNEM_MASK /* IN endpoint NAK effective mask */
#define USB_OTG_DIEPEACHMSK1_TXFURM_SHIFT        (8U)
#define USB_OTG_DIEPEACHMSK1_TXFURM_MASK         (0x1U << USB_OTG_DIEPEACHMSK1_TXFURM_SHIFT) /* 0x00000100 */
#define USB_OTG_DIEPEACHMSK1_TXFURM              USB_OTG_DIEPEACHMSK1_TXFURM_MASK /* FIFO underrun mask */
#define USB_OTG_DIEPEACHMSK1_BIM_SHIFT           (9U)
#define USB_OTG_DIEPEACHMSK1_BIM_MASK            (0x1U << USB_OTG_DIEPEACHMSK1_BIM_SHIFT) /* 0x00000200 */
#define USB_OTG_DIEPEACHMSK1_BIM                 USB_OTG_DIEPEACHMSK1_BIM_MASK  /* BNA interrupt mask */
#define USB_OTG_DIEPEACHMSK1_NAKM_SHIFT          (13U)
#define USB_OTG_DIEPEACHMSK1_NAKM_MASK           (0x1U << USB_OTG_DIEPEACHMSK1_NAKM_SHIFT) /* 0x00002000 */
#define USB_OTG_DIEPEACHMSK1_NAKM                USB_OTG_DIEPEACHMSK1_NAKM_MASK /* NAK interrupt mask */
/********************  Bit definition for USB_OTG_DOEPEACHMSK1 register  ********************/
#define USB_OTG_DOEPEACHMSK1_XFRCM_SHIFT         (0U)
#define USB_OTG_DOEPEACHMSK1_XFRCM_MASK          (0x1U << USB_OTG_DOEPEACHMSK1_XFRCM_SHIFT) /* 0x00000001 */
#define USB_OTG_DOEPEACHMSK1_XFRCM               USB_OTG_DOEPEACHMSK1_XFRCM_MASK /* Transfer completed interrupt mask */
#define USB_OTG_DOEPEACHMSK1_EPDM_SHIFT          (1U)
#define USB_OTG_DOEPEACHMSK1_EPDM_MASK           (0x1U << USB_OTG_DOEPEACHMSK1_EPDM_SHIFT) /* 0x00000002 */
#define USB_OTG_DOEPEACHMSK1_EPDM                USB_OTG_DOEPEACHMSK1_EPDM_MASK /* Endpoint disabled interrupt mask */
#define USB_OTG_DOEPEACHMSK1_TOM_SHIFT           (3U)
#define USB_OTG_DOEPEACHMSK1_TOM_MASK            (0x1U << USB_OTG_DOEPEACHMSK1_TOM_SHIFT) /* 0x00000008 */
#define USB_OTG_DOEPEACHMSK1_TOM                 USB_OTG_DOEPEACHMSK1_TOM_MASK  /* Timeout condition mask */
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK_SHIFT     (4U)
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK_MASK      (0x1U << USB_OTG_DOEPEACHMSK1_ITTXFEMSK_SHIFT) /* 0x00000010 */
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK           USB_OTG_DOEPEACHMSK1_ITTXFEMSK_MASK /* IN token received when TxFIFO empty mask  */
#define USB_OTG_DOEPEACHMSK1_INEPNMM_SHIFT       (5U)
#define USB_OTG_DOEPEACHMSK1_INEPNMM_MASK        (0x1U << USB_OTG_DOEPEACHMSK1_INEPNMM_SHIFT) /* 0x00000020 */
#define USB_OTG_DOEPEACHMSK1_INEPNMM             USB_OTG_DOEPEACHMSK1_INEPNMM_MASK /* IN token received with EP mismatch mask */
#define USB_OTG_DOEPEACHMSK1_INEPNEM_SHIFT       (6U)
#define USB_OTG_DOEPEACHMSK1_INEPNEM_MASK        (0x1U << USB_OTG_DOEPEACHMSK1_INEPNEM_SHIFT) /* 0x00000040 */
#define USB_OTG_DOEPEACHMSK1_INEPNEM             USB_OTG_DOEPEACHMSK1_INEPNEM_MASK /* IN endpoint NAK effective mask */
#define USB_OTG_DOEPEACHMSK1_TXFURM_SHIFT        (8U)
#define USB_OTG_DOEPEACHMSK1_TXFURM_MASK         (0x1U << USB_OTG_DOEPEACHMSK1_TXFURM_SHIFT) /* 0x00000100 */
#define USB_OTG_DOEPEACHMSK1_TXFURM              USB_OTG_DOEPEACHMSK1_TXFURM_MASK /* OUT packet error mask */
#define USB_OTG_DOEPEACHMSK1_BIM_SHIFT           (9U)
#define USB_OTG_DOEPEACHMSK1_BIM_MASK            (0x1U << USB_OTG_DOEPEACHMSK1_BIM_SHIFT) /* 0x00000200 */
#define USB_OTG_DOEPEACHMSK1_BIM                 USB_OTG_DOEPEACHMSK1_BIM_MASK  /* BNA interrupt mask */
#define USB_OTG_DOEPEACHMSK1_BERRM_SHIFT         (12U)
#define USB_OTG_DOEPEACHMSK1_BERRM_MASK          (0x1U << USB_OTG_DOEPEACHMSK1_BERRM_SHIFT) /* 0x00001000 */
#define USB_OTG_DOEPEACHMSK1_BERRM               USB_OTG_DOEPEACHMSK1_BERRM_MASK /* Bubble error interrupt mask */
#define USB_OTG_DOEPEACHMSK1_NAKM_SHIFT          (13U)
#define USB_OTG_DOEPEACHMSK1_NAKM_MASK           (0x1U << USB_OTG_DOEPEACHMSK1_NAKM_SHIFT) /* 0x00002000 */
#define USB_OTG_DOEPEACHMSK1_NAKM                USB_OTG_DOEPEACHMSK1_NAKM_MASK /* NAK interrupt mask */
#define USB_OTG_DOEPEACHMSK1_NYETM_SHIFT         (14U)
#define USB_OTG_DOEPEACHMSK1_NYETM_MASK          (0x1U << USB_OTG_DOEPEACHMSK1_NYETM_SHIFT) /* 0x00004000 */
#define USB_OTG_DOEPEACHMSK1_NYETM               USB_OTG_DOEPEACHMSK1_NYETM_MASK /* NYET interrupt mask */
/********************  Bit definition for USB_OTG_DIEPCTL register  ********************/
#define USB_OTG_DIEPCTL_MPSIZ_SHIFT              (0U)
#define USB_OTG_DIEPCTL_MPSIZ_MASK               (0x7FFU << USB_OTG_DIEPCTL_MPSIZ_SHIFT) /* 0x000007FF */
#define USB_OTG_DIEPCTL_MPSIZ                    USB_OTG_DIEPCTL_MPSIZ_MASK     /* Maximum packet size */
#define USB_OTG_DIEPCTL_USBAEP_SHIFT             (15U)
#define USB_OTG_DIEPCTL_USBAEP_MASK              (0x1U << USB_OTG_DIEPCTL_USBAEP_SHIFT) /* 0x00008000 */
#define USB_OTG_DIEPCTL_USBAEP                   USB_OTG_DIEPCTL_USBAEP_MASK    /* USB active endpoint */
#define USB_OTG_DIEPCTL_EONUM_DPID_SHIFT         (16U)
#define USB_OTG_DIEPCTL_EONUM_DPID_MASK          (0x1U << USB_OTG_DIEPCTL_EONUM_DPID_SHIFT) /* 0x00010000 */
#define USB_OTG_DIEPCTL_EONUM_DPID               USB_OTG_DIEPCTL_EONUM_DPID_MASK /* Even/odd frame */
#define USB_OTG_DIEPCTL_NAKSTS_SHIFT             (17U)
#define USB_OTG_DIEPCTL_NAKSTS_MASK              (0x1U << USB_OTG_DIEPCTL_NAKSTS_SHIFT) /* 0x00020000 */
#define USB_OTG_DIEPCTL_NAKSTS                   USB_OTG_DIEPCTL_NAKSTS_MASK    /* NAK status */
#define USB_OTG_DIEPCTL_EPTYP_SHIFT              (18U)
#define USB_OTG_DIEPCTL_EPTYP_MASK               (0x3U << USB_OTG_DIEPCTL_EPTYP_SHIFT) /* 0x000C0000 */
#define USB_OTG_DIEPCTL_EPTYP                    USB_OTG_DIEPCTL_EPTYP_MASK     /* Endpoint type */
#define USB_OTG_DIEPCTL_EPTYP_0                  (0x1U << USB_OTG_DIEPCTL_EPTYP_SHIFT) /* 0x00040000 */
#define USB_OTG_DIEPCTL_EPTYP_1                  (0x2U << USB_OTG_DIEPCTL_EPTYP_SHIFT) /* 0x00080000 */
#define USB_OTG_DIEPCTL_STALL_SHIFT              (21U)
#define USB_OTG_DIEPCTL_STALL_MASK               (0x1U << USB_OTG_DIEPCTL_STALL_SHIFT) /* 0x00200000 */
#define USB_OTG_DIEPCTL_STALL                    USB_OTG_DIEPCTL_STALL_MASK     /* STALL handshake */
#define USB_OTG_DIEPCTL_TXFNUM_SHIFT             (22U)
#define USB_OTG_DIEPCTL_TXFNUM_MASK              (0xFU << USB_OTG_DIEPCTL_TXFNUM_SHIFT) /* 0x03C00000 */
#define USB_OTG_DIEPCTL_TXFNUM                   USB_OTG_DIEPCTL_TXFNUM_MASK    /* TxFIFO number */
#define USB_OTG_DIEPCTL_TXFNUM_0                 (0x1U << USB_OTG_DIEPCTL_TXFNUM_SHIFT) /* 0x00400000 */
#define USB_OTG_DIEPCTL_TXFNUM_1                 (0x2U << USB_OTG_DIEPCTL_TXFNUM_SHIFT) /* 0x00800000 */
#define USB_OTG_DIEPCTL_TXFNUM_2                 (0x4U << USB_OTG_DIEPCTL_TXFNUM_SHIFT) /* 0x01000000 */
#define USB_OTG_DIEPCTL_TXFNUM_3                 (0x8U << USB_OTG_DIEPCTL_TXFNUM_SHIFT) /* 0x02000000 */
#define USB_OTG_DIEPCTL_CNAK_SHIFT               (26U)
#define USB_OTG_DIEPCTL_CNAK_MASK                (0x1U << USB_OTG_DIEPCTL_CNAK_SHIFT) /* 0x04000000 */
#define USB_OTG_DIEPCTL_CNAK                     USB_OTG_DIEPCTL_CNAK_MASK      /* Clear NAK */
#define USB_OTG_DIEPCTL_SNAK_SHIFT               (27U)
#define USB_OTG_DIEPCTL_SNAK_MASK                (0x1U << USB_OTG_DIEPCTL_SNAK_SHIFT) /* 0x08000000 */
#define USB_OTG_DIEPCTL_SNAK                     USB_OTG_DIEPCTL_SNAK_MASK      /* Set NAK */
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM_SHIFT     (28U)
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM_MASK      (0x1U << USB_OTG_DIEPCTL_SD0PID_SEVNFRM_SHIFT) /* 0x10000000 */
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM           USB_OTG_DIEPCTL_SD0PID_SEVNFRM_MASK /* Set DATA0 PID */
#define USB_OTG_DIEPCTL_SODDFRM_SHIFT            (29U)
#define USB_OTG_DIEPCTL_SODDFRM_MASK             (0x1U << USB_OTG_DIEPCTL_SODDFRM_SHIFT) /* 0x20000000 */
#define USB_OTG_DIEPCTL_SODDFRM                  USB_OTG_DIEPCTL_SODDFRM_MASK   /* Set odd frame */
#define USB_OTG_DIEPCTL_EPDIS_SHIFT              (30U)
#define USB_OTG_DIEPCTL_EPDIS_MASK               (0x1U << USB_OTG_DIEPCTL_EPDIS_SHIFT) /* 0x40000000 */
#define USB_OTG_DIEPCTL_EPDIS                    USB_OTG_DIEPCTL_EPDIS_MASK     /* Endpoint disable */
#define USB_OTG_DIEPCTL_EPENA_SHIFT              (31U)
#define USB_OTG_DIEPCTL_EPENA_MASK               (0x1U << USB_OTG_DIEPCTL_EPENA_SHIFT) /* 0x80000000 */
#define USB_OTG_DIEPCTL_EPENA                    USB_OTG_DIEPCTL_EPENA_MASK     /* Endpoint enable */
/********************  Bit definition for USB_OTG_DIEPINT register  ********************/
#define USB_OTG_DIEPINT_XFRC_SHIFT               (0U)
#define USB_OTG_DIEPINT_XFRC_MASK                (0x1U << USB_OTG_DIEPINT_XFRC_SHIFT) /* 0x00000001 */
#define USB_OTG_DIEPINT_XFRC                     USB_OTG_DIEPINT_XFRC_MASK      /* Transfer completed interrupt */
#define USB_OTG_DIEPINT_EPDISD_SHIFT             (1U)
#define USB_OTG_DIEPINT_EPDISD_MASK              (0x1U << USB_OTG_DIEPINT_EPDISD_SHIFT) /* 0x00000002 */
#define USB_OTG_DIEPINT_EPDISD                   USB_OTG_DIEPINT_EPDISD_MASK    /* Endpoint disabled interrupt */
#define USB_OTG_DIEPINT_TOC_SHIFT                (3U)
#define USB_OTG_DIEPINT_TOC_MASK                 (0x1U << USB_OTG_DIEPINT_TOC_SHIFT) /* 0x00000008 */
#define USB_OTG_DIEPINT_TOC                      USB_OTG_DIEPINT_TOC_MASK       /* Timeout condition */
#define USB_OTG_DIEPINT_ITTXFE_SHIFT             (4U)
#define USB_OTG_DIEPINT_ITTXFE_MASK              (0x1U << USB_OTG_DIEPINT_ITTXFE_SHIFT) /* 0x00000010 */
#define USB_OTG_DIEPINT_ITTXFE                   USB_OTG_DIEPINT_ITTXFE_MASK    /* IN token received when TxFIFO is empty */
#define USB_OTG_DIEPINT_INEPNE_SHIFT             (6U)
#define USB_OTG_DIEPINT_INEPNE_MASK              (0x1U << USB_OTG_DIEPINT_INEPNE_SHIFT) /* 0x00000040 */
#define USB_OTG_DIEPINT_INEPNE                   USB_OTG_DIEPINT_INEPNE_MASK    /* IN endpoint NAK effective */
#define USB_OTG_DIEPINT_TXFE_SHIFT               (7U)
#define USB_OTG_DIEPINT_TXFE_MASK                (0x1U << USB_OTG_DIEPINT_TXFE_SHIFT) /* 0x00000080 */
#define USB_OTG_DIEPINT_TXFE                     USB_OTG_DIEPINT_TXFE_MASK      /* Transmit FIFO empty */
#define USB_OTG_DIEPINT_TXFIFOUDRN_SHIFT         (8U)
#define USB_OTG_DIEPINT_TXFIFOUDRN_MASK          (0x1U << USB_OTG_DIEPINT_TXFIFOUDRN_SHIFT) /* 0x00000100 */
#define USB_OTG_DIEPINT_TXFIFOUDRN               USB_OTG_DIEPINT_TXFIFOUDRN_MASK /* Transmit Fifo Underrun */
#define USB_OTG_DIEPINT_BNA_SHIFT                (9U)
#define USB_OTG_DIEPINT_BNA_MASK                 (0x1U << USB_OTG_DIEPINT_BNA_SHIFT) /* 0x00000200 */
#define USB_OTG_DIEPINT_BNA                      USB_OTG_DIEPINT_BNA_MASK       /* Buffer not available interrupt */
#define USB_OTG_DIEPINT_PKTDRPSTS_SHIFT          (11U)
#define USB_OTG_DIEPINT_PKTDRPSTS_MASK           (0x1U << USB_OTG_DIEPINT_PKTDRPSTS_SHIFT) /* 0x00000800 */
#define USB_OTG_DIEPINT_PKTDRPSTS                USB_OTG_DIEPINT_PKTDRPSTS_MASK /* Packet dropped status */
#define USB_OTG_DIEPINT_BERR_SHIFT               (12U)
#define USB_OTG_DIEPINT_BERR_MASK                (0x1U << USB_OTG_DIEPINT_BERR_SHIFT) /* 0x00001000 */
#define USB_OTG_DIEPINT_BERR                     USB_OTG_DIEPINT_BERR_MASK      /* Babble error interrupt */
#define USB_OTG_DIEPINT_NAK_SHIFT                (13U)
#define USB_OTG_DIEPINT_NAK_MASK                 (0x1U << USB_OTG_DIEPINT_NAK_SHIFT) /* 0x00002000 */
#define USB_OTG_DIEPINT_NAK                      USB_OTG_DIEPINT_NAK_MASK       /* NAK interrupt */
/********************  Bit definition for USB_OTG_DIEPTSIZ register  ********************/
#define USB_OTG_DIEPTSIZ_XFRSIZ_SHIFT            (0U)
#define USB_OTG_DIEPTSIZ_XFRSIZ_MASK             (0x7FFFFU << USB_OTG_DIEPTSIZ_XFRSIZ_SHIFT) /* 0x0007FFFF */
#define USB_OTG_DIEPTSIZ_XFRSIZ                  USB_OTG_DIEPTSIZ_XFRSIZ_MASK   /* Transfer size */
#define USB_OTG_DIEPTSIZ_PKTCNT_SHIFT            (19U)
#define USB_OTG_DIEPTSIZ_PKTCNT_MASK             (0x3FFU << USB_OTG_DIEPTSIZ_PKTCNT_SHIFT) /* 0x1FF80000 */
#define USB_OTG_DIEPTSIZ_PKTCNT                  USB_OTG_DIEPTSIZ_PKTCNT_MASK   /* Packet count */
#define USB_OTG_DIEPTSIZ_MULCNT_SHIFT            (29U)
#define USB_OTG_DIEPTSIZ_MULCNT_MASK             (0x3U << USB_OTG_DIEPTSIZ_MULCNT_SHIFT) /* 0x60000000 */
#define USB_OTG_DIEPTSIZ_MULCNT                  USB_OTG_DIEPTSIZ_MULCNT_MASK   /* Packet count */
/********************  Bit definition for USB_OTG_DIEPDMA register  ********************/
#define USB_OTG_DIEPDMA_DMAADDR_SHIFT            (0U)
#define USB_OTG_DIEPDMA_DMAADDR_MASK             (0xFFFFFFFFU << USB_OTG_DIEPDMA_DMAADDR_SHIFT) /* 0xFFFFFFFF */
#define USB_OTG_DIEPDMA_DMAADDR                  USB_OTG_DIEPDMA_DMAADDR_MASK   /* DMA address */
/********************  Bit definition for USB_OTG_DTXFSTS register  ********************/
#define USB_OTG_DTXFSTS_INEPTFSAV_SHIFT          (0U)
#define USB_OTG_DTXFSTS_INEPTFSAV_MASK           (0xFFFFU << USB_OTG_DTXFSTS_INEPTFSAV_SHIFT) /* 0x0000FFFF */
#define USB_OTG_DTXFSTS_INEPTFSAV                USB_OTG_DTXFSTS_INEPTFSAV_MASK /* IN endpoint TxFIFO space available */
/********************  Bit definition for USB_OTG_DOEPCTL register  ********************/
#define USB_OTG_DOEPCTL_MPSIZ_SHIFT              (0U)
#define USB_OTG_DOEPCTL_MPSIZ_MASK               (0x7FFU << USB_OTG_DOEPCTL_MPSIZ_SHIFT) /* 0x000007FF */
#define USB_OTG_DOEPCTL_MPSIZ                    USB_OTG_DOEPCTL_MPSIZ_MASK     /* Maximum packet size */
#define USB_OTG_DOEPCTL_USBAEP_SHIFT             (15U)
#define USB_OTG_DOEPCTL_USBAEP_MASK              (0x1U << USB_OTG_DOEPCTL_USBAEP_SHIFT) /* 0x00008000 */
#define USB_OTG_DOEPCTL_USBAEP                   USB_OTG_DOEPCTL_USBAEP_MASK    /* USB active endpoint */
#define USB_OTG_DOEPCTL_NAKSTS_SHIFT             (17U)
#define USB_OTG_DOEPCTL_NAKSTS_MASK              (0x1U << USB_OTG_DOEPCTL_NAKSTS_SHIFT) /* 0x00020000 */
#define USB_OTG_DOEPCTL_NAKSTS                   USB_OTG_DOEPCTL_NAKSTS_MASK    /* NAK status */
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM_SHIFT     (28U)
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM_MASK      (0x1U << USB_OTG_DOEPCTL_SD0PID_SEVNFRM_SHIFT) /* 0x10000000 */
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM           USB_OTG_DOEPCTL_SD0PID_SEVNFRM_MASK /* Set DATA0 PID */
#define USB_OTG_DOEPCTL_SODDFRM_SHIFT            (29U)
#define USB_OTG_DOEPCTL_SODDFRM_MASK             (0x1U << USB_OTG_DOEPCTL_SODDFRM_SHIFT) /* 0x20000000 */
#define USB_OTG_DOEPCTL_SODDFRM                  USB_OTG_DOEPCTL_SODDFRM_MASK   /* Set odd frame */
#define USB_OTG_DOEPCTL_EPTYP_SHIFT              (18U)
#define USB_OTG_DOEPCTL_EPTYP_MASK               (0x3U << USB_OTG_DOEPCTL_EPTYP_SHIFT) /* 0x000C0000 */
#define USB_OTG_DOEPCTL_EPTYP                    USB_OTG_DOEPCTL_EPTYP_MASK     /* Endpoint type */
#define USB_OTG_DOEPCTL_EPTYP_0                  (0x1U << USB_OTG_DOEPCTL_EPTYP_SHIFT) /* 0x00040000 */
#define USB_OTG_DOEPCTL_EPTYP_1                  (0x2U << USB_OTG_DOEPCTL_EPTYP_SHIFT) /* 0x00080000 */
#define USB_OTG_DOEPCTL_SNPM_SHIFT               (20U)
#define USB_OTG_DOEPCTL_SNPM_MASK                (0x1U << USB_OTG_DOEPCTL_SNPM_SHIFT) /* 0x00100000 */
#define USB_OTG_DOEPCTL_SNPM                     USB_OTG_DOEPCTL_SNPM_MASK      /* Snoop mode */
#define USB_OTG_DOEPCTL_STALL_SHIFT              (21U)
#define USB_OTG_DOEPCTL_STALL_MASK               (0x1U << USB_OTG_DOEPCTL_STALL_SHIFT) /* 0x00200000 */
#define USB_OTG_DOEPCTL_STALL                    USB_OTG_DOEPCTL_STALL_MASK     /* STALL handshake */
#define USB_OTG_DOEPCTL_CNAK_SHIFT               (26U)
#define USB_OTG_DOEPCTL_CNAK_MASK                (0x1U << USB_OTG_DOEPCTL_CNAK_SHIFT) /* 0x04000000 */
#define USB_OTG_DOEPCTL_CNAK                     USB_OTG_DOEPCTL_CNAK_MASK      /* Clear NAK */
#define USB_OTG_DOEPCTL_SNAK_SHIFT               (27U)
#define USB_OTG_DOEPCTL_SNAK_MASK                (0x1U << USB_OTG_DOEPCTL_SNAK_SHIFT) /* 0x08000000 */
#define USB_OTG_DOEPCTL_SNAK                     USB_OTG_DOEPCTL_SNAK_MASK      /* Set NAK */
#define USB_OTG_DOEPCTL_EPDIS_SHIFT              (30U)
#define USB_OTG_DOEPCTL_EPDIS_MASK               (0x1U << USB_OTG_DOEPCTL_EPDIS_SHIFT) /* 0x40000000 */
#define USB_OTG_DOEPCTL_EPDIS                    USB_OTG_DOEPCTL_EPDIS_MASK     /* Endpoint disable */
#define USB_OTG_DOEPCTL_EPENA_SHIFT              (31U)
#define USB_OTG_DOEPCTL_EPENA_MASK               (0x1U << USB_OTG_DOEPCTL_EPENA_SHIFT) /* 0x80000000 */
#define USB_OTG_DOEPCTL_EPENA                    USB_OTG_DOEPCTL_EPENA_MASK     /* Endpoint enable */
/********************  Bit definition for USB_OTG_DOEPINT register  ********************/
#define USB_OTG_DOEPINT_XFRC_SHIFT               (0U)
#define USB_OTG_DOEPINT_XFRC_MASK                (0x1U << USB_OTG_DOEPINT_XFRC_SHIFT) /* 0x00000001 */
#define USB_OTG_DOEPINT_XFRC                     USB_OTG_DOEPINT_XFRC_MASK      /* Transfer completed interrupt */
#define USB_OTG_DOEPINT_EPDISD_SHIFT             (1U)
#define USB_OTG_DOEPINT_EPDISD_MASK              (0x1U << USB_OTG_DOEPINT_EPDISD_SHIFT) /* 0x00000002 */
#define USB_OTG_DOEPINT_EPDISD                   USB_OTG_DOEPINT_EPDISD_MASK    /* Endpoint disabled interrupt */
#define USB_OTG_DOEPINT_STUP_SHIFT               (3U)
#define USB_OTG_DOEPINT_STUP_MASK                (0x1U << USB_OTG_DOEPINT_STUP_SHIFT) /* 0x00000008 */
#define USB_OTG_DOEPINT_STUP                     USB_OTG_DOEPINT_STUP_MASK      /* SETUP phase done */
#define USB_OTG_DOEPINT_OTEPDIS_SHIFT            (4U)
#define USB_OTG_DOEPINT_OTEPDIS_MASK             (0x1U << USB_OTG_DOEPINT_OTEPDIS_SHIFT) /* 0x00000010 */
#define USB_OTG_DOEPINT_OTEPDIS                  USB_OTG_DOEPINT_OTEPDIS_MASK   /* OUT token received when endpoint disabled */
#define USB_OTG_DOEPINT_OTEPSPR_SHIFT            (5U)
#define USB_OTG_DOEPINT_OTEPSPR_MASK             (0x1U << USB_OTG_DOEPINT_OTEPSPR_SHIFT) /* 0x00000020 */
#define USB_OTG_DOEPINT_OTEPSPR                  USB_OTG_DOEPINT_OTEPSPR_MASK   /* Status Phase Received For Control Write */
#define USB_OTG_DOEPINT_B2BSTUP_SHIFT            (6U)
#define USB_OTG_DOEPINT_B2BSTUP_MASK             (0x1U << USB_OTG_DOEPINT_B2BSTUP_SHIFT) /* 0x00000040 */
#define USB_OTG_DOEPINT_B2BSTUP                  USB_OTG_DOEPINT_B2BSTUP_MASK   /* Back-to-back SETUP packets received */
#define USB_OTG_DOEPINT_NYET_SHIFT               (14U)
#define USB_OTG_DOEPINT_NYET_MASK                (0x1U << USB_OTG_DOEPINT_NYET_SHIFT) /* 0x00004000 */
#define USB_OTG_DOEPINT_NYET                     USB_OTG_DOEPINT_NYET_MASK      /* NYET interrupt */
#define USB_OTG_DOEPINT_STUPPKTRCVD_SHIFT        (15U)
#define USB_OTG_DOEPINT_STUPPKTRCVD_MASK         (0x1U << USB_OTG_DOEPINT_STUPPKTRCVD_SHIFT) /* 0x00008000 */
#define USB_OTG_DOEPINT_STUPPKTRCVD              USB_OTG_DOEPINT_STUPPKTRCVD_MASK   /* STUPPKTRCVD interrupt */
/********************  Bit definition for USB_OTG_DOEPTSIZ register  ********************/
#define USB_OTG_DOEPTSIZ_XFRSIZ_SHIFT            (0U)
#define USB_OTG_DOEPTSIZ_XFRSIZ_MASK             (0x7FFFFU << USB_OTG_DOEPTSIZ_XFRSIZ_SHIFT) /* 0x0007FFFF */
#define USB_OTG_DOEPTSIZ_XFRSIZ                  USB_OTG_DOEPTSIZ_XFRSIZ_MASK   /* Transfer size */
#define USB_OTG_DOEPTSIZ_PKTCNT_SHIFT            (19U)
#define USB_OTG_DOEPTSIZ_PKTCNT_MASK             (0x3FFU << USB_OTG_DOEPTSIZ_PKTCNT_SHIFT) /* 0x1FF80000 */
#define USB_OTG_DOEPTSIZ_PKTCNT                  USB_OTG_DOEPTSIZ_PKTCNT_MASK   /* Packet count */
#define USB_OTG_DOEPTSIZ_STUPCNT_SHIFT           (29U)
#define USB_OTG_DOEPTSIZ_STUPCNT_MASK            (0x3U << USB_OTG_DOEPTSIZ_STUPCNT_SHIFT) /* 0x60000000 */
#define USB_OTG_DOEPTSIZ_STUPCNT                 USB_OTG_DOEPTSIZ_STUPCNT_MASK  /* SETUP packet count */
#define USB_OTG_DOEPTSIZ_STUPCNT_0               (0x1U << USB_OTG_DOEPTSIZ_STUPCNT_SHIFT) /* 0x20000000 */
#define USB_OTG_DOEPTSIZ_STUPCNT_1               (0x2U << USB_OTG_DOEPTSIZ_STUPCNT_SHIFT) /* 0x40000000 */
/********************  Bit definition for PCGCCTL register  ********************/
#define USB_OTG_PCGCCTL_STOPCLK_SHIFT            (0U)
#define USB_OTG_PCGCCTL_STOPCLK_MASK             (0x1U << USB_OTG_PCGCCTL_STOPCLK_SHIFT) /* 0x00000001 */
#define USB_OTG_PCGCCTL_STOPCLK                  USB_OTG_PCGCCTL_STOPCLK_MASK   /* SETUP packet count */
#define USB_OTG_PCGCCTL_GATECLK_SHIFT            (1U)
#define USB_OTG_PCGCCTL_GATECLK_MASK             (0x1U << USB_OTG_PCGCCTL_GATECLK_SHIFT) /* 0x00000002 */
#define USB_OTG_PCGCCTL_GATECLK                  USB_OTG_PCGCCTL_GATECLK_MASK   /* Gate Hclk */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __RK2108_USB_H */
