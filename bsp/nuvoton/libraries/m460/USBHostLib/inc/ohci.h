/**************************************************************************//**
 * @file     ohci.h
 * @version  V1.00
 * @brief    USB OHCI host controller driver header file.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef _USBH_OHCI_H_
#define _USBH_OHCI_H_

/// @cond HIDDEN_SYMBOLS

struct utr_t;
struct udev_t;

/* OHCI CONTROL AND STATUS REGISTER MASKS */

/*
 * Host controller functional state.
 * for HCFS(HcControl[7:6])
 */
#define HCFS_RESET                (0UL << USBH_HcControl_HCFS_Pos)
#define HCFS_RESUME               (1UL << USBH_HcControl_HCFS_Pos)
#define HCFS_OPER                 (2UL << USBH_HcControl_HCFS_Pos)
#define HCFS_SUSPEND              (3UL << USBH_HcControl_HCFS_Pos)


/*----------------------------------------------------------------------------------------*/
/*   Endpoint descriptor                                                                  */
/*----------------------------------------------------------------------------------------*/
typedef struct ed_t
{
    /* OHCI spec. Endpoint descriptor  */
    uint32_t    Info;
    uint32_t    TailP;
    uint32_t    HeadP;
    uint32_t    NextED;
    /* The following members are used by USB Host libary.   */
    uint8_t     bInterval;
    uint16_t    next_sf;          /* for isochronous transfer, recording the next SF      */
    struct ed_t *next;            /* point to the next ED in remove list                  */
} ED_T;

#define ED_CTRL_FA_Pos            0         /* Info[6:0]   - Function address             */
#define ED_CTRL_EN_Pos            7         /* Info[10:7]  - Endpoint number              */
#define ED_CTRL_DIR_Pos           11        /* Info[12:11] - Direction                    */
#define ED_CTRL_MPS_Pos           16        /* Info[26:16] - Maximum packet size          */

#define ED_FUNC_ADDR_Msk          (0x7f)
#define ED_EP_ADDR_Msk            (0xf<<7)
#define ED_DIR_Msk                (0x3<<11)
#define ED_SPEED_Msk              (1<<13)
#define ED_MAX_PK_SIZE_Msk        (0x7ff<<16)

#define ED_DIR_BY_TD              (0<<ED_CTRL_DIR_Pos)
#define ED_DIR_OUT                (1<<ED_CTRL_DIR_Pos)
#define ED_DIR_IN                 (2<<ED_CTRL_DIR_Pos)
#define ED_SPEED_FULL             (0<<13)   /* Info[13] - 0: is full speed device         */
#define ED_SPEED_LOW              (1<<13)   /* Info[13] - 1: is low speed device          */
#define ED_SKIP                   (1<<14)   /* Info[14] - 1: HC skip this ED              */
#define ED_FORMAT_GENERAL         (0<<15)   /* Info[15] - 0: is a general TD              */
#define ED_FORMAT_ISO             (1<<15)   /* Info[15] - 1: is an isochronous TD         */
#define ED_HEADP_HALT             (1<<0)    /* HeadP[0] - 1: Halt; 0: Not                 */


/*----------------------------------------------------------------------------------------*/
/*   Transfer descriptor                                                                  */
/*----------------------------------------------------------------------------------------*/
/* general transfer descriptor  */
typedef struct td_t
{
    uint32_t    Info;
    uint32_t    CBP;                        /* Current Buffer Pointer                     */
    uint32_t    NextTD;                     /* Next TD                                    */
    uint32_t    BE;                         /* Buffer End                                 */
    uint32_t    PSW[4];                     /* PSW 0~7                                    */
    /* The following members are used by USB Host libary.   */
    uint32_t    buff_start;                 /* Buffer Start                               */
    ED_T        *ed;                        /* The ED that this TD belong to.             */
    struct utr_t  *utr;                     /* associated UTR                             */
    struct td_t *next;                      /* point to next TD of the same UTR           */
} TD_T;

#define TD_ADDR_MASK              0xFFFFFFFC

/* Completion codes */
enum OCHI_CC_CODE
{
    /* mapping of the OHCI CC status to error codes */
    CC_NOERROR,                             /* No  Error                                  */
    CC_CRC,                                 /* CRC Error                                  */
    CC_BITSTUFF,                            /* Bit Stuff                                  */
    CC_DATA_TOGGLE,                         /* Data Toggle                                */
    CC_STALL,                               /* Stall                                      */
    CC_NOTRESPONSE,                         /* DevNotResp                                 */
    CC_PID_CHECK,                           /* PIDCheck                                   */
    CC_UNEXPECTED_PID,                      /* UnExpPID                                   */
    CC_DATA_OVERRUN,                        /* DataOver                                   */
    CC_DATA_UNDERRUN,                       /* DataUnder                                  */
    CC_RESERVED1,                           /* reserved                                   */
    CC_RESERVED2,                           /* reserved                                   */
    CC_BUFFER_OVERRUN,                      /* BufferOver                                 */
    CC_BUFFER_UNDERRUN,                     /* BuffUnder                                  */
    CC_NOT_ACCESS                           /* Not Access                                 */
};

/* TD control field */
#define TD_CC                     0xF0000000
#define TD_CC_GET(td)             ((td >>28) & 0x0F)
#define TD_CC_SET(td, cc)         (td) = ((td) & 0x0FFFFFFF) | (((cc) & 0x0F) << 28)
#define TD_T_DATA0                0x02000000
#define TD_T_DATA1                0x03000000
#define TD_R                      0x00040000
#define TD_DP                     0x00180000
#define TD_DP_IN                  0x00100000
#define TD_DP_OUT                 0x00080000
#define MAXPSW                    8
/* steel TD reserved bits to keep driver data */
#define TD_TYPE_Msk               (0x3<<16)
#define TD_TYPE_CTRL              (0x0<<16)
#define TD_TYPE_BULK              (0x1<<16)
#define TD_TYPE_INT               (0x2<<16)
#define TD_TYPE_ISO               (0x3<<16)
#define TD_CTRL_Msk               (0x7<<15)
#define TD_CTRL_DATA              (1<<15)


/*
 * The HCCA (Host Controller Communications Area) is a 256 byte
 * structure defined in the OHCI spec. that the host controller is
 * told the base address of.  It must be 256-byte aligned.
 */
typedef struct
{
    uint32_t   int_table[32];               /* Interrupt ED table                         */
    uint16_t   frame_no;                    /* current frame number                       */
    uint16_t   pad1;                        /* set to 0 on each frame_no change           */
    uint32_t   done_head;                   /* info returned for an interrupt             */
    uint8_t    reserved_for_hc[116];
} HCCA_T;


/// @endcond

#endif  /* _USBH_OHCI_H_ */
