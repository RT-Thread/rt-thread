/**************************************************************************//**
 * @file     ehci.h
 * @version  V1.00
 * @brief    USB EHCI host controller driver header file.
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef _USBH_EHCI_H_
#define _USBH_EHCI_H_

/// @cond HIDDEN_SYMBOLS

struct utr_t;
struct udev_t;
struct qh_t;
struct iso_ep_t;
struct ep_info_t;

/*----------------------------------------------------------------------------------------*/
/*  Periodic Frame List Size (256, 512, or 1024)                                          */
/*----------------------------------------------------------------------------------------*/
#define FL_SIZE              1024            /* frame list size can be 256, 512, or 1024   */
#define NUM_IQH              11              /* depends on FL_SIZE, 256:9, 512:10, 1024:11 */


/*----------------------------------------------------------------------------------------*/
/*  Interrupt Threshold Control (1, 2, 4, 6, .. 64)                                       */
/*----------------------------------------------------------------------------------------*/
#define UCMDR_INT_THR_CTRL     (0x1<<HSUSBH_UCMDR_ITC_Pos)     /* 1 micro-frames          */


/*----------------------------------------------------------------------------------------*/
/*  Queue Element Transfer Descriptor (qTD)                                               */
/*----------------------------------------------------------------------------------------*/
typedef struct qTD_t
{
    uint32_t      Next_qTD;                 /* Next qTD Pointer                           */
    uint32_t      Alt_Next_qTD;             /* Alternate Next qTD Pointer                 */
    uint32_t      Token;                    /* qTD Token                                  */
    uint32_t      Bptr[5];                  /* qTD Buffer Page Pointer List               */
    /*
     * The following members are used by USB Host libary.
     */
    struct utr_t  *utr;                     /* associated UTR                             */
    uint32_t      xfer_len;                 /* assigned transfer transfer length          */
    struct qh_t   *qh;                      /* The QH that this qTD belong to.            */
    struct qTD_t  *next;                    /* link for <qtd_list> of QH                  */
}  qTD_T;


#define QTD_LIST_END              0x1       /* Indicate the terminate of qTD list.        */
#define QTD_PTR(x)                ((qTD_T *)((uint32_t)(x) & ~0x1F))

/*
 *  Status: qTD Token[7:0]
 */
#define QTD_STS_PS_OUT            (0<<0)    /* directs the HC to issue an OUT PID         */
#define QTD_STS_PS_PING           (1<<0)    /* directs the HC to issue an PING PID        */
#define QTD_STS_SPLIT_STRAT       (0<<1)    /* directs the HC to issue an Start split     */
#define QTD_STS_SPLIT_COMPLETE    (1<<1)    /* directs the HC to issue an Complete split  */
#define QTD_STS_MISS_MF           (1<<2)    /* miss a required complete-split transaction */
#define QTD_STS_XactErr           (1<<3)    /* Transaction Error occurred                 */
#define QTD_STS_BABBLE            (1<<4)    /* Babble Detected                            */
#define QTD_STS_DATA_BUFF_ERR     (1<<5)    /* Data Buffer Error                          */
#define QTD_STS_HALT              (1<<6)    /* Halted                                     */
#define QTD_STS_ACTIVE            (1<<7)    /* Active                                     */

/*
 *  PID: qTD Token[9:8]
 */
#define QTD_PID_Msk              (0x3<<8)
#define QTD_PID_OUT               (0<<8)    /* generates token (E1H)                      */
#define QTD_PID_IN                (1<<8)    /* generates token (69H)                      */
#define QTD_PID_SETUP             (2<<8)    /* generates token (2DH)                      */

#define QTD_ERR_COUNTER           (3<<10)   /* Token[11:10]                               */
#define QTD_IOC                   (1<<15)   /* Token[15] - Interrupt On Complete          */
#define QTD_TODO_LEN_Pos          16        /* Token[31:16] - Total Bytes to Transfer     */
#define QTD_TODO_LEN(x)           (((x)>>16) & 0x7FFF)
#define QTD_DT                    (1UL<<31) /* Token[31] - Data Toggle                    */

/*----------------------------------------------------------------------------------------*/
/*  Queue Head (QH)                                                                       */
/*----------------------------------------------------------------------------------------*/
typedef struct qh_t
{
    /* OHCI spec. Endpoint descriptor  */
    uint32_t    HLink;                      /* Queue Head Horizontal Link Pointer         */
    uint32_t    Chrst;                      /* Endpoint Characteristics: QH DWord 1       */
    uint32_t    Cap;                        /* Endpoint Capabilities: QH DWord 2          */
    uint32_t    Curr_qTD;                   /* Current qTD Pointer                        */
    /*
     * The followings are qTD Transfer Overlay
     */
    uint32_t    OL_Next_qTD;                /* Next qTD Pointer                           */
    uint32_t    OL_Alt_Next_qTD;            /* Alternate Next qTD Pointer                 */
    uint32_t    OL_Token;                   /* qTD Token                                  */
    uint32_t    OL_Bptr[5];                 /* qTD Buffer Page Pointer List               */
    /*
     * The following members are used by USB Host libary.
     */
    qTD_T       *qtd_list;                  /* currently linked qTD transfers             */
    qTD_T       *done_list;                 /* currently linked qTD transfers             */
    struct qh_t *next;                      /* point to the next QH in remove list        */
}  QH_T;

/*  HLink[0] T field of "Queue Head Horizontal Link Pointer" */
#define QH_HLNK_END               0x1

/*
 *  HLink[2:1] Typ field of "Queue Head Horizontal Link Pointer"
 */
#define QH_HLNK_ITD(x)            (((uint32_t)(x) & ~0x1F) | 0x0)
#define QH_HLNK_QH(x)             (((uint32_t)(x) & ~0x1F) | 0x2)
#define QH_HLNK_SITD(x)           (((uint32_t)(x) & ~0x1F) | 0x4)
#define QH_HLNK_FSTN(x)           (((uint32_t)(x) & ~0x1F) | 0x6)
#define QH_PTR(x)                 ((QH_T *)((uint32_t)(x) & ~0x1F))

/*
 *  Bit fields of "Endpoint Characteristics"
 */
#define QH_NAK_RL                 (4L<<28)  /* Chrst[31:28] - NAK Count Reload            */
#define QH_CTRL_EP_FLAG           (1<<27)   /* Chrst[27] - Control Endpoint Flag          */
#define QH_RCLM_LIST_HEAD         (1<<15)   /* Chrst[15] - Head of Reclamation List Flag  */
#define QH_DTC                    (1<<14)   /* Chrst[14] - Data Toggle Control            */
#define QH_EPS_FULL               (0<<12)   /* Chrst[13:12] - Endpoint Speed (Full)       */
#define QH_EPS_LOW                (1<<12)   /* Chrst[13:12] - Endpoint Speed (Low)        */
#define QH_EPS_HIGH               (2<<12)   /* Chrst[13:12] - Endpoint Speed (High)       */
#define QH_I_NEXT                 (1<<7)    /* Chrst[7] - Inactivate on Next Transaction  */

/*
 *  Bit fields of "Endpoint Capabilities"
 */
#define QH_MULT_Pos               30        /* Cap[31:30] - High-Bandwidth Pipe Multiplier */
#define QH_HUB_PORT_Pos           23        /* Cap[29:23] - Hub Port Number               */
#define QH_HUB_ADDR_Pos           16        /* Cap[22:16] - Hub Addr                      */
#define QH_C_MASK_Msk             0xFF00    /* Cap[15:8]  - uFrame C-mask                 */
#define QH_S_MASK_Msk             0x00FF    /* Cap[7:0]   - uFrame S-mask                 */


/*----------------------------------------------------------------------------------------*/
/*  Isochronous (High-Speed) Transfer Descriptor (iTD)                                    */
/*----------------------------------------------------------------------------------------*/
typedef struct itd_t
{
    uint32_t      Next_Link;                /* Next Link Pointer                          */
    uint32_t      Transaction[8];           /* Transaction Status and Control             */
    uint32_t      Bptr[7];                  /* Buffer Page Pointer List                   */
    /*
     * The following members are used by USB Host libary.
     */
    struct iso_ep_t *iso_ep;                /* associated isochronous information block   */
    struct utr_t  *utr;                     /* associated UTR                             */
    uint32_t      buff_base;                /* buffer base address                        */
    uint8_t       fidx;                     /* iTD's first index to UTR iso frames        */
    uint8_t       trans_mask;               /* mask of activated transactions in iTD      */
    uint32_t      sched_frnidx;             /* scheduled frame index                      */
    struct itd_t  *next;                    /* used by software to maintain iTD list      */
}  iTD_T;

/*
 *  Next_Link[2:1] Typ field of "Next Schedule Element Pointer"  Typ field
 */
#define ITD_HLNK_ITD(x)           (((uint32_t)(x) & ~0x1F) | 0x0)
#define ITD_HLNK_QH(x)            (((uint32_t)(x) & ~0x1F) | 0x2)
#define ITD_HLNK_SITD(x)          (((uint32_t)(x) & ~0x1F) | 0x4)
#define ITD_HLNK_FSTN(x)          (((uint32_t)(x) & ~0x1F) | 0x6)
#define ITD_PTR(x)                ((iTD_T *)((uint32_t)(x) & ~0x1F))

/*
 *  Transaction[8]
 */
#define ITD_STATUS(x)             (((x)>>28)&0xF)
#define ITD_STATUS_ACTIVE         (0x80000000UL)      /* Active                           */
#define ITD_STATUS_BUFF_ERR       (0x40000000UL)      /* Data Buffer Error                */
#define ITD_STATUS_BABBLE         (0x20000000UL)      /* Babble Detected                  */
#define ITD_STATUS_XACT_ERR       (0x10000000UL)      /* Transcation Error                */

#define ITD_XLEN_Pos              16
#define ITD_XFER_LEN(x)           (((x)>>16)&0xFFF)
#define ITD_IOC                   (1<<15)
#define ITD_PG_Pos                12
#define ITD_XFER_OFF_Msk          0xFFF

/*
 *  Bptr[7]
 */
#define ITD_BUFF_PAGE_Pos         12
/* Bptr[0] */
#define ITD_EP_NUM_Pos            8
#define ITD_EP_NUM(itd)           (((itd)->Bptr[0]>>8)&0xF)
#define ITD_DEV_ADDR_Pos          0
#define ITD_DEV_ADDR(itd)         ((itd)->Bptr[0]&0x7F)
/* Bptr[1] */
#define ITD_DIR_IN                (1<<11)
#define ITD_DIR_OUT               (0<<11)
#define ITD_MAX_PKTSZ_Pos         0
#define ITD_MAX_PKTSZ(itd)        ((itd)->Bptr[1]&0x7FF)

/*----------------------------------------------------------------------------------------*/
/*  Split Isochronous (Full-Speed) Transfer Descriptor (siTD)                             */
/*----------------------------------------------------------------------------------------*/
typedef struct sitd_t
{
    uint32_t      Next_Link;                /* Next Link Pointer                          */
    uint32_t      Chrst;                    /* Endpoint and Transaction Translator Characteristics */
    uint32_t      Sched;                    /* Micro-frame Schedule Control               */
    uint32_t      StsCtrl;                  /* siTD Transfer Status and Control           */
    uint32_t      Bptr[2];                  /* Buffer Page Pointer List                   */
    uint32_t      BackLink;                 /* siTD Back Link Pointer                     */
    /*
     * The following members are used by USB Host libary.
     */
    struct iso_ep_t *iso_ep;                /* associated isochronous information block   */
    struct utr_t  *utr;                     /* associated UTR                             */
    uint8_t       fidx;                     /* iTD's first index to UTR iso frames        */
    uint32_t      sched_frnidx;             /* scheduled frame index                      */
    struct sitd_t *next;                    /* used by software to maintain siTD list     */
}  siTD_T;

#define SITD_LIST_END              0x1      /* Indicate the terminate of siTD list.       */

#define SITD_XFER_IO_Msk           (1UL<<31)
#define SITD_XFER_IN               (1UL<<31)
#define SITD_XFER_OUT              (0UL<<31)

#define SITD_PORT_NUM_Pos          24
#define SITD_HUB_ADDR_Pos          16
#define SITD_EP_NUM_Pos            8
#define SITD_DEV_ADDR_Pos          0

#define SITD_IOC                   (1UL<<31)
#define SITD_XFER_CNT_Pos          16
#define SITD_XFER_CNT_Msk          (0x3FF<<SITD_XFER_CNT_Pos)

#define SITD_STATUS(x)             ((x)&0xFC)
#define SITD_STATUS_ACTIVE         0x80
#define SITD_STATUS_ERR            0x40
#define SITD_STATUS_BUFF_ERR       0x20
#define SITD_BABBLE_DETECTED       0x10
#define SITD_STATUS_XFER_ERR       0x08
#define SITD_STATUS_MISSED_MF      0x04
#define SITD_STATUS_ERROR_MASK     0x78


/*
 *  Next_Link[2:1] Typ field of "Next Schedule Element Pointer"  Typ field
 */
#define SITD_HLNK_ITD(x)          (((uint32_t)(x) & ~0x1F) | 0x0)
#define SITD_HLNK_QH(x)           (((uint32_t)(x) & ~0x1F) | 0x2)
#define SITD_HLNK_SITD(x)         (((uint32_t)(x) & ~0x1F) | 0x4)
#define SITD_HLNK_FSTN(x)         (((uint32_t)(x) & ~0x1F) | 0x6)
#define SITD_PTR(x)               ((siTD_T *)((uint32_t)(x) & ~0x1F))

#define HLINK_IS_TERMINATED(x)    (((uint32_t)(x) & 0x1) ? 1 : 0)
#define HLINK_IS_SITD(x)          ((((uint32_t)(x) & 0x6) == 0x4) ? 1 : 0)

/*----------------------------------------------------------------------------------------*/
/*  Isochronous endpoint transfer information block. (Software only)                      */
/*----------------------------------------------------------------------------------------*/
typedef struct iso_ep_t
{
    struct ep_info_t  *ep;
    uint32_t      next_frame;               /* frame number of next scheduling            */
    iTD_T         *itd_list;                /* Reference to a list of installed iTDs      */
    iTD_T         *itd_done_list;           /* Reference to a list of completed iTDs      */
    siTD_T        *sitd_list;               /* Reference to a list of installed siTDs     */
    siTD_T        *sitd_done_list;          /* Reference to a list of completed siTDs     */
    struct iso_ep_t  *next;                 /* used by software to maintain ISO EP list   */
} ISO_EP_T;

/// @endcond

#endif  /* _USBH_EHCI_H_ */

