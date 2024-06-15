/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __USB_FSDEV_REG_H__
#define __USB_FSDEV_REG_H__

#define     __IO    volatile             /*!< Defines 'read / write' permissions */
/**
  * @brief Universal Serial Bus Full Speed Device
  */

typedef struct
{
  __IO uint16_t EP0R;                 /*!< USB Endpoint 0 register,                   Address offset: 0x00 */
  __IO uint16_t RESERVED0;            /*!< Reserved */
  __IO uint16_t EP1R;                 /*!< USB Endpoint 1 register,                   Address offset: 0x04 */
  __IO uint16_t RESERVED1;            /*!< Reserved */
  __IO uint16_t EP2R;                 /*!< USB Endpoint 2 register,                   Address offset: 0x08 */
  __IO uint16_t RESERVED2;            /*!< Reserved */
  __IO uint16_t EP3R;                 /*!< USB Endpoint 3 register,                   Address offset: 0x0C */
  __IO uint16_t RESERVED3;            /*!< Reserved */
  __IO uint16_t EP4R;                 /*!< USB Endpoint 4 register,                   Address offset: 0x10 */
  __IO uint16_t RESERVED4;            /*!< Reserved */
  __IO uint16_t EP5R;                 /*!< USB Endpoint 5 register,                   Address offset: 0x14 */
  __IO uint16_t RESERVED5;            /*!< Reserved */
  __IO uint16_t EP6R;                 /*!< USB Endpoint 6 register,                   Address offset: 0x18 */
  __IO uint16_t RESERVED6;            /*!< Reserved */
  __IO uint16_t EP7R;                 /*!< USB Endpoint 7 register,                   Address offset: 0x1C */
  __IO uint16_t RESERVED7[17];        /*!< Reserved */
  __IO uint16_t CNTR;                 /*!< Control register,                          Address offset: 0x40 */
  __IO uint16_t RESERVED8;            /*!< Reserved */
  __IO uint16_t ISTR;                 /*!< Interrupt status register,                 Address offset: 0x44 */
  __IO uint16_t RESERVED9;            /*!< Reserved */
  __IO uint16_t FNR;                  /*!< Frame number register,                     Address offset: 0x48 */
  __IO uint16_t RESERVEDA;            /*!< Reserved */
  __IO uint16_t DADDR;                /*!< Device address register,                   Address offset: 0x4C */
  __IO uint16_t RESERVEDB;            /*!< Reserved */
  __IO uint16_t BTABLE;               /*!< Buffer Table address register,             Address offset: 0x50 */
  __IO uint16_t RESERVEDC;            /*!< Reserved */
  __IO uint16_t LPMCSR;               /*!< LPM Control and Status register,           Address offset: 0x54 */
  __IO uint16_t RESERVEDD;            /*!< Reserved */
  __IO uint16_t BCDR;                 /*!< Battery Charging detector register,        Address offset: 0x58 */
  __IO uint16_t RESERVEDE;            /*!< Reserved */
} USB_TypeDef;

/******************************************************************************/
/*                                                                            */
/*                                   USB Device FS                            */
/*                                                                            */
/******************************************************************************/

/*!< Endpoint-specific registers */
#define  USB_EP0R                            USB_BASE                      /*!< Endpoint 0 register address */
#define  USB_EP1R                            (USB_BASE + 0x00000004)       /*!< Endpoint 1 register address */
#define  USB_EP2R                            (USB_BASE + 0x00000008)       /*!< Endpoint 2 register address */
#define  USB_EP3R                            (USB_BASE + 0x0000000C)       /*!< Endpoint 3 register address */
#define  USB_EP4R                            (USB_BASE + 0x00000010)       /*!< Endpoint 4 register address */
#define  USB_EP5R                            (USB_BASE + 0x00000014)       /*!< Endpoint 5 register address */
#define  USB_EP6R                            (USB_BASE + 0x00000018)       /*!< Endpoint 6 register address */
#define  USB_EP7R                            (USB_BASE + 0x0000001C)       /*!< Endpoint 7 register address */

/* bit positions */
#define USB_EP_CTR_RX_Pos                       (15U)
#define USB_EP_CTR_RX_Msk                       (0x1UL << USB_EP_CTR_RX_Pos)    /*!< 0x00008000 */
#define USB_EP_CTR_RX                           USB_EP_CTR_RX_Msk              /*!< EndPoint Correct TRansfer RX */
#define USB_EP_DTOG_RX_Pos                      (14U)
#define USB_EP_DTOG_RX_Msk                      (0x1UL << USB_EP_DTOG_RX_Pos)   /*!< 0x00004000 */
#define USB_EP_DTOG_RX                          USB_EP_DTOG_RX_Msk             /*!< EndPoint Data TOGGLE RX */
#define USB_EPRX_STAT_Pos                       (12U)
#define USB_EPRX_STAT_Msk                       (0x3UL << USB_EPRX_STAT_Pos)    /*!< 0x00003000 */
#define USB_EPRX_STAT                           USB_EPRX_STAT_Msk              /*!< EndPoint RX STATus bit field */
#define USB_EP_SETUP_Pos                        (11U)
#define USB_EP_SETUP_Msk                        (0x1UL << USB_EP_SETUP_Pos)     /*!< 0x00000800 */
#define USB_EP_SETUP                            USB_EP_SETUP_Msk               /*!< EndPoint SETUP */
#define USB_EP_T_FIELD_Pos                      (9U)
#define USB_EP_T_FIELD_Msk                      (0x3UL << USB_EP_T_FIELD_Pos)   /*!< 0x00000600 */
#define USB_EP_T_FIELD                          USB_EP_T_FIELD_Msk             /*!< EndPoint TYPE */
#define USB_EP_KIND_Pos                         (8U)
#define USB_EP_KIND_Msk                         (0x1UL << USB_EP_KIND_Pos)      /*!< 0x00000100 */
#define USB_EP_KIND                             USB_EP_KIND_Msk                /*!< EndPoint KIND */
#define USB_EP_CTR_TX_Pos                       (7U)
#define USB_EP_CTR_TX_Msk                       (0x1UL << USB_EP_CTR_TX_Pos)    /*!< 0x00000080 */
#define USB_EP_CTR_TX                           USB_EP_CTR_TX_Msk              /*!< EndPoint Correct TRansfer TX */
#define USB_EP_DTOG_TX_Pos                      (6U)
#define USB_EP_DTOG_TX_Msk                      (0x1UL << USB_EP_DTOG_TX_Pos)   /*!< 0x00000040 */
#define USB_EP_DTOG_TX                          USB_EP_DTOG_TX_Msk             /*!< EndPoint Data TOGGLE TX */
#define USB_EPTX_STAT_Pos                       (4U)
#define USB_EPTX_STAT_Msk                       (0x3UL << USB_EPTX_STAT_Pos)    /*!< 0x00000030 */
#define USB_EPTX_STAT                           USB_EPTX_STAT_Msk              /*!< EndPoint TX STATus bit field */
#define USB_EPADDR_FIELD_Pos                    (0U)
#define USB_EPADDR_FIELD_Msk                    (0xFUL << USB_EPADDR_FIELD_Pos) /*!< 0x0000000F */
#define USB_EPADDR_FIELD                        USB_EPADDR_FIELD_Msk           /*!< EndPoint ADDRess FIELD */

/* EndPoint REGister MASK (no toggle fields) */
#define  USB_EPREG_MASK                      (USB_EP_CTR_RX|USB_EP_SETUP|USB_EP_T_FIELD|USB_EP_KIND|USB_EP_CTR_TX|USB_EPADDR_FIELD)
                                                                           /*!< EP_TYPE[1:0] EndPoint TYPE */
#define USB_EP_TYPE_MASK_Pos                    (9U)
#define USB_EP_TYPE_MASK_Msk                    (0x3UL << USB_EP_TYPE_MASK_Pos) /*!< 0x00000600 */
#define USB_EP_TYPE_MASK                        USB_EP_TYPE_MASK_Msk           /*!< EndPoint TYPE Mask */
#define USB_EP_BULK                             0x00000000U                    /*!< EndPoint BULK */
#define USB_EP_CONTROL                          0x00000200U                    /*!< EndPoint CONTROL */
#define USB_EP_ISOCHRONOUS                      0x00000400U                    /*!< EndPoint ISOCHRONOUS */
#define USB_EP_INTERRUPT                        0x00000600U                    /*!< EndPoint INTERRUPT */
#define  USB_EP_T_MASK                          (~USB_EP_T_FIELD & USB_EPREG_MASK)

#define  USB_EPKIND_MASK                        (~USB_EP_KIND & USB_EPREG_MASK)  /*!< EP_KIND EndPoint KIND */
                                                                               /*!< STAT_TX[1:0] STATus for TX transfer */
#define USB_EP_TX_DIS                           0x00000000U                    /*!< EndPoint TX DISabled */
#define USB_EP_TX_STALL                         0x00000010U                    /*!< EndPoint TX STALLed */
#define USB_EP_TX_NAK                           0x00000020U                    /*!< EndPoint TX NAKed */
#define USB_EP_TX_VALID                         0x00000030U                    /*!< EndPoint TX VALID */
#define USB_EPTX_DTOG1                          0x00000010U                    /*!< EndPoint TX Data TOGgle bit1 */
#define USB_EPTX_DTOG2                          0x00000020U                    /*!< EndPoint TX Data TOGgle bit2 */
#define  USB_EPTX_DTOGMASK  (USB_EPTX_STAT|USB_EPREG_MASK)
                                                                               /*!< STAT_RX[1:0] STATus for RX transfer */
#define USB_EP_RX_DIS                           0x00000000U                    /*!< EndPoint RX DISabled */
#define USB_EP_RX_STALL                         0x00001000U                    /*!< EndPoint RX STALLed */
#define USB_EP_RX_NAK                           0x00002000U                    /*!< EndPoint RX NAKed */
#define USB_EP_RX_VALID                         0x00003000U                    /*!< EndPoint RX VALID */
#define USB_EPRX_DTOG1                          0x00001000U                    /*!< EndPoint RX Data TOGgle bit1 */
#define USB_EPRX_DTOG2                          0x00002000U                    /*!< EndPoint RX Data TOGgle bit1 */
#define  USB_EPRX_DTOGMASK  (USB_EPRX_STAT|USB_EPREG_MASK)

/*******************  Bit definition for USB_EP0R register  *******************/
#define USB_EP0R_EA_Pos                         (0U)
#define USB_EP0R_EA_Msk                         (0xFUL << USB_EP0R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP0R_EA                             USB_EP0R_EA_Msk                /*!< Endpoint Address */

#define USB_EP0R_STAT_TX_Pos                    (4U)
#define USB_EP0R_STAT_TX_Msk                    (0x3UL << USB_EP0R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP0R_STAT_TX                        USB_EP0R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP0R_STAT_TX_0                      (0x1UL << USB_EP0R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP0R_STAT_TX_1                      (0x2UL << USB_EP0R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP0R_DTOG_TX_Pos                    (6U)
#define USB_EP0R_DTOG_TX_Msk                    (0x1UL << USB_EP0R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP0R_DTOG_TX                        USB_EP0R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP0R_CTR_TX_Pos                     (7U)
#define USB_EP0R_CTR_TX_Msk                     (0x1UL << USB_EP0R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP0R_CTR_TX                         USB_EP0R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP0R_EP_KIND_Pos                    (8U)
#define USB_EP0R_EP_KIND_Msk                    (0x1UL << USB_EP0R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP0R_EP_KIND                        USB_EP0R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP0R_EP_TYPE_Pos                    (9U)
#define USB_EP0R_EP_TYPE_Msk                    (0x3UL << USB_EP0R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP0R_EP_TYPE                        USB_EP0R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP0R_EP_TYPE_0                      (0x1UL << USB_EP0R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP0R_EP_TYPE_1                      (0x2UL << USB_EP0R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP0R_SETUP_Pos                      (11U)
#define USB_EP0R_SETUP_Msk                      (0x1UL << USB_EP0R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP0R_SETUP                          USB_EP0R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP0R_STAT_RX_Pos                    (12U)
#define USB_EP0R_STAT_RX_Msk                    (0x3UL << USB_EP0R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP0R_STAT_RX                        USB_EP0R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP0R_STAT_RX_0                      (0x1UL << USB_EP0R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP0R_STAT_RX_1                      (0x2UL << USB_EP0R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP0R_DTOG_RX_Pos                    (14U)
#define USB_EP0R_DTOG_RX_Msk                    (0x1UL << USB_EP0R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP0R_DTOG_RX                        USB_EP0R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP0R_CTR_RX_Pos                     (15U)
#define USB_EP0R_CTR_RX_Msk                     (0x1UL << USB_EP0R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP0R_CTR_RX                         USB_EP0R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP1R register  *******************/
#define USB_EP1R_EA_Pos                         (0U)
#define USB_EP1R_EA_Msk                         (0xFUL << USB_EP1R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP1R_EA                             USB_EP1R_EA_Msk                /*!< Endpoint Address */

#define USB_EP1R_STAT_TX_Pos                    (4U)
#define USB_EP1R_STAT_TX_Msk                    (0x3UL << USB_EP1R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP1R_STAT_TX                        USB_EP1R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP1R_STAT_TX_0                      (0x1UL << USB_EP1R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP1R_STAT_TX_1                      (0x2UL << USB_EP1R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP1R_DTOG_TX_Pos                    (6U)
#define USB_EP1R_DTOG_TX_Msk                    (0x1UL << USB_EP1R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP1R_DTOG_TX                        USB_EP1R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP1R_CTR_TX_Pos                     (7U)
#define USB_EP1R_CTR_TX_Msk                     (0x1UL << USB_EP1R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP1R_CTR_TX                         USB_EP1R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP1R_EP_KIND_Pos                    (8U)
#define USB_EP1R_EP_KIND_Msk                    (0x1UL << USB_EP1R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP1R_EP_KIND                        USB_EP1R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP1R_EP_TYPE_Pos                    (9U)
#define USB_EP1R_EP_TYPE_Msk                    (0x3UL << USB_EP1R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP1R_EP_TYPE                        USB_EP1R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP1R_EP_TYPE_0                      (0x1UL << USB_EP1R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP1R_EP_TYPE_1                      (0x2UL << USB_EP1R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP1R_SETUP_Pos                      (11U)
#define USB_EP1R_SETUP_Msk                      (0x1UL << USB_EP1R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP1R_SETUP                          USB_EP1R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP1R_STAT_RX_Pos                    (12U)
#define USB_EP1R_STAT_RX_Msk                    (0x3UL << USB_EP1R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP1R_STAT_RX                        USB_EP1R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP1R_STAT_RX_0                      (0x1UL << USB_EP1R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP1R_STAT_RX_1                      (0x2UL << USB_EP1R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP1R_DTOG_RX_Pos                    (14U)
#define USB_EP1R_DTOG_RX_Msk                    (0x1UL << USB_EP1R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP1R_DTOG_RX                        USB_EP1R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP1R_CTR_RX_Pos                     (15U)
#define USB_EP1R_CTR_RX_Msk                     (0x1UL << USB_EP1R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP1R_CTR_RX                         USB_EP1R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP2R register  *******************/
#define USB_EP2R_EA_Pos                         (0U)
#define USB_EP2R_EA_Msk                         (0xFUL << USB_EP2R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP2R_EA                             USB_EP2R_EA_Msk                /*!< Endpoint Address */

#define USB_EP2R_STAT_TX_Pos                    (4U)
#define USB_EP2R_STAT_TX_Msk                    (0x3UL << USB_EP2R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP2R_STAT_TX                        USB_EP2R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP2R_STAT_TX_0                      (0x1UL << USB_EP2R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP2R_STAT_TX_1                      (0x2UL << USB_EP2R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP2R_DTOG_TX_Pos                    (6U)
#define USB_EP2R_DTOG_TX_Msk                    (0x1UL << USB_EP2R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP2R_DTOG_TX                        USB_EP2R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP2R_CTR_TX_Pos                     (7U)
#define USB_EP2R_CTR_TX_Msk                     (0x1UL << USB_EP2R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP2R_CTR_TX                         USB_EP2R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP2R_EP_KIND_Pos                    (8U)
#define USB_EP2R_EP_KIND_Msk                    (0x1UL << USB_EP2R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP2R_EP_KIND                        USB_EP2R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP2R_EP_TYPE_Pos                    (9U)
#define USB_EP2R_EP_TYPE_Msk                    (0x3UL << USB_EP2R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP2R_EP_TYPE                        USB_EP2R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP2R_EP_TYPE_0                      (0x1UL << USB_EP2R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP2R_EP_TYPE_1                      (0x2UL << USB_EP2R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP2R_SETUP_Pos                      (11U)
#define USB_EP2R_SETUP_Msk                      (0x1UL << USB_EP2R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP2R_SETUP                          USB_EP2R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP2R_STAT_RX_Pos                    (12U)
#define USB_EP2R_STAT_RX_Msk                    (0x3UL << USB_EP2R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP2R_STAT_RX                        USB_EP2R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP2R_STAT_RX_0                      (0x1UL << USB_EP2R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP2R_STAT_RX_1                      (0x2UL << USB_EP2R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP2R_DTOG_RX_Pos                    (14U)
#define USB_EP2R_DTOG_RX_Msk                    (0x1UL << USB_EP2R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP2R_DTOG_RX                        USB_EP2R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP2R_CTR_RX_Pos                     (15U)
#define USB_EP2R_CTR_RX_Msk                     (0x1UL << USB_EP2R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP2R_CTR_RX                         USB_EP2R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP3R register  *******************/
#define USB_EP3R_EA_Pos                         (0U)
#define USB_EP3R_EA_Msk                         (0xFUL << USB_EP3R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP3R_EA                             USB_EP3R_EA_Msk                /*!< Endpoint Address */

#define USB_EP3R_STAT_TX_Pos                    (4U)
#define USB_EP3R_STAT_TX_Msk                    (0x3UL << USB_EP3R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP3R_STAT_TX                        USB_EP3R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP3R_STAT_TX_0                      (0x1UL << USB_EP3R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP3R_STAT_TX_1                      (0x2UL << USB_EP3R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP3R_DTOG_TX_Pos                    (6U)
#define USB_EP3R_DTOG_TX_Msk                    (0x1UL << USB_EP3R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP3R_DTOG_TX                        USB_EP3R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP3R_CTR_TX_Pos                     (7U)
#define USB_EP3R_CTR_TX_Msk                     (0x1UL << USB_EP3R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP3R_CTR_TX                         USB_EP3R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP3R_EP_KIND_Pos                    (8U)
#define USB_EP3R_EP_KIND_Msk                    (0x1UL << USB_EP3R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP3R_EP_KIND                        USB_EP3R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP3R_EP_TYPE_Pos                    (9U)
#define USB_EP3R_EP_TYPE_Msk                    (0x3UL << USB_EP3R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP3R_EP_TYPE                        USB_EP3R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP3R_EP_TYPE_0                      (0x1UL << USB_EP3R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP3R_EP_TYPE_1                      (0x2UL << USB_EP3R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP3R_SETUP_Pos                      (11U)
#define USB_EP3R_SETUP_Msk                      (0x1UL << USB_EP3R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP3R_SETUP                          USB_EP3R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP3R_STAT_RX_Pos                    (12U)
#define USB_EP3R_STAT_RX_Msk                    (0x3UL << USB_EP3R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP3R_STAT_RX                        USB_EP3R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP3R_STAT_RX_0                      (0x1UL << USB_EP3R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP3R_STAT_RX_1                      (0x2UL << USB_EP3R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP3R_DTOG_RX_Pos                    (14U)
#define USB_EP3R_DTOG_RX_Msk                    (0x1UL << USB_EP3R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP3R_DTOG_RX                        USB_EP3R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP3R_CTR_RX_Pos                     (15U)
#define USB_EP3R_CTR_RX_Msk                     (0x1UL << USB_EP3R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP3R_CTR_RX                         USB_EP3R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP4R register  *******************/
#define USB_EP4R_EA_Pos                         (0U)
#define USB_EP4R_EA_Msk                         (0xFUL << USB_EP4R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP4R_EA                             USB_EP4R_EA_Msk                /*!< Endpoint Address */

#define USB_EP4R_STAT_TX_Pos                    (4U)
#define USB_EP4R_STAT_TX_Msk                    (0x3UL << USB_EP4R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP4R_STAT_TX                        USB_EP4R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP4R_STAT_TX_0                      (0x1UL << USB_EP4R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP4R_STAT_TX_1                      (0x2UL << USB_EP4R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP4R_DTOG_TX_Pos                    (6U)
#define USB_EP4R_DTOG_TX_Msk                    (0x1UL << USB_EP4R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP4R_DTOG_TX                        USB_EP4R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP4R_CTR_TX_Pos                     (7U)
#define USB_EP4R_CTR_TX_Msk                     (0x1UL << USB_EP4R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP4R_CTR_TX                         USB_EP4R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP4R_EP_KIND_Pos                    (8U)
#define USB_EP4R_EP_KIND_Msk                    (0x1UL << USB_EP4R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP4R_EP_KIND                        USB_EP4R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP4R_EP_TYPE_Pos                    (9U)
#define USB_EP4R_EP_TYPE_Msk                    (0x3UL << USB_EP4R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP4R_EP_TYPE                        USB_EP4R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP4R_EP_TYPE_0                      (0x1UL << USB_EP4R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP4R_EP_TYPE_1                      (0x2UL << USB_EP4R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP4R_SETUP_Pos                      (11U)
#define USB_EP4R_SETUP_Msk                      (0x1UL << USB_EP4R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP4R_SETUP                          USB_EP4R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP4R_STAT_RX_Pos                    (12U)
#define USB_EP4R_STAT_RX_Msk                    (0x3UL << USB_EP4R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP4R_STAT_RX                        USB_EP4R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP4R_STAT_RX_0                      (0x1UL << USB_EP4R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP4R_STAT_RX_1                      (0x2UL << USB_EP4R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP4R_DTOG_RX_Pos                    (14U)
#define USB_EP4R_DTOG_RX_Msk                    (0x1UL << USB_EP4R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP4R_DTOG_RX                        USB_EP4R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP4R_CTR_RX_Pos                     (15U)
#define USB_EP4R_CTR_RX_Msk                     (0x1UL << USB_EP4R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP4R_CTR_RX                         USB_EP4R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP5R register  *******************/
#define USB_EP5R_EA_Pos                         (0U)
#define USB_EP5R_EA_Msk                         (0xFUL << USB_EP5R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP5R_EA                             USB_EP5R_EA_Msk                /*!< Endpoint Address */

#define USB_EP5R_STAT_TX_Pos                    (4U)
#define USB_EP5R_STAT_TX_Msk                    (0x3UL << USB_EP5R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP5R_STAT_TX                        USB_EP5R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP5R_STAT_TX_0                      (0x1UL << USB_EP5R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP5R_STAT_TX_1                      (0x2UL << USB_EP5R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP5R_DTOG_TX_Pos                    (6U)
#define USB_EP5R_DTOG_TX_Msk                    (0x1UL << USB_EP5R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP5R_DTOG_TX                        USB_EP5R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP5R_CTR_TX_Pos                     (7U)
#define USB_EP5R_CTR_TX_Msk                     (0x1UL << USB_EP5R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP5R_CTR_TX                         USB_EP5R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP5R_EP_KIND_Pos                    (8U)
#define USB_EP5R_EP_KIND_Msk                    (0x1UL << USB_EP5R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP5R_EP_KIND                        USB_EP5R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP5R_EP_TYPE_Pos                    (9U)
#define USB_EP5R_EP_TYPE_Msk                    (0x3UL << USB_EP5R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP5R_EP_TYPE                        USB_EP5R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP5R_EP_TYPE_0                      (0x1UL << USB_EP5R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP5R_EP_TYPE_1                      (0x2UL << USB_EP5R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP5R_SETUP_Pos                      (11U)
#define USB_EP5R_SETUP_Msk                      (0x1UL << USB_EP5R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP5R_SETUP                          USB_EP5R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP5R_STAT_RX_Pos                    (12U)
#define USB_EP5R_STAT_RX_Msk                    (0x3UL << USB_EP5R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP5R_STAT_RX                        USB_EP5R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP5R_STAT_RX_0                      (0x1UL << USB_EP5R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP5R_STAT_RX_1                      (0x2UL << USB_EP5R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP5R_DTOG_RX_Pos                    (14U)
#define USB_EP5R_DTOG_RX_Msk                    (0x1UL << USB_EP5R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP5R_DTOG_RX                        USB_EP5R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP5R_CTR_RX_Pos                     (15U)
#define USB_EP5R_CTR_RX_Msk                     (0x1UL << USB_EP5R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP5R_CTR_RX                         USB_EP5R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP6R register  *******************/
#define USB_EP6R_EA_Pos                         (0U)
#define USB_EP6R_EA_Msk                         (0xFUL << USB_EP6R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP6R_EA                             USB_EP6R_EA_Msk                /*!< Endpoint Address */

#define USB_EP6R_STAT_TX_Pos                    (4U)
#define USB_EP6R_STAT_TX_Msk                    (0x3UL << USB_EP6R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP6R_STAT_TX                        USB_EP6R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP6R_STAT_TX_0                      (0x1UL << USB_EP6R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP6R_STAT_TX_1                      (0x2UL << USB_EP6R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP6R_DTOG_TX_Pos                    (6U)
#define USB_EP6R_DTOG_TX_Msk                    (0x1UL << USB_EP6R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP6R_DTOG_TX                        USB_EP6R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP6R_CTR_TX_Pos                     (7U)
#define USB_EP6R_CTR_TX_Msk                     (0x1UL << USB_EP6R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP6R_CTR_TX                         USB_EP6R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP6R_EP_KIND_Pos                    (8U)
#define USB_EP6R_EP_KIND_Msk                    (0x1UL << USB_EP6R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP6R_EP_KIND                        USB_EP6R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP6R_EP_TYPE_Pos                    (9U)
#define USB_EP6R_EP_TYPE_Msk                    (0x3UL << USB_EP6R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP6R_EP_TYPE                        USB_EP6R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP6R_EP_TYPE_0                      (0x1UL << USB_EP6R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP6R_EP_TYPE_1                      (0x2UL << USB_EP6R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP6R_SETUP_Pos                      (11U)
#define USB_EP6R_SETUP_Msk                      (0x1UL << USB_EP6R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP6R_SETUP                          USB_EP6R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP6R_STAT_RX_Pos                    (12U)
#define USB_EP6R_STAT_RX_Msk                    (0x3UL << USB_EP6R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP6R_STAT_RX                        USB_EP6R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP6R_STAT_RX_0                      (0x1UL << USB_EP6R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP6R_STAT_RX_1                      (0x2UL << USB_EP6R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP6R_DTOG_RX_Pos                    (14U)
#define USB_EP6R_DTOG_RX_Msk                    (0x1UL << USB_EP6R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP6R_DTOG_RX                        USB_EP6R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP6R_CTR_RX_Pos                     (15U)
#define USB_EP6R_CTR_RX_Msk                     (0x1UL << USB_EP6R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP6R_CTR_RX                         USB_EP6R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*******************  Bit definition for USB_EP7R register  *******************/
#define USB_EP7R_EA_Pos                         (0U)
#define USB_EP7R_EA_Msk                         (0xFUL << USB_EP7R_EA_Pos)      /*!< 0x0000000F */
#define USB_EP7R_EA                             USB_EP7R_EA_Msk                /*!< Endpoint Address */

#define USB_EP7R_STAT_TX_Pos                    (4U)
#define USB_EP7R_STAT_TX_Msk                    (0x3UL << USB_EP7R_STAT_TX_Pos) /*!< 0x00000030 */
#define USB_EP7R_STAT_TX                        USB_EP7R_STAT_TX_Msk           /*!< STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP7R_STAT_TX_0                      (0x1UL << USB_EP7R_STAT_TX_Pos) /*!< 0x00000010 */
#define USB_EP7R_STAT_TX_1                      (0x2UL << USB_EP7R_STAT_TX_Pos) /*!< 0x00000020 */

#define USB_EP7R_DTOG_TX_Pos                    (6U)
#define USB_EP7R_DTOG_TX_Msk                    (0x1UL << USB_EP7R_DTOG_TX_Pos) /*!< 0x00000040 */
#define USB_EP7R_DTOG_TX                        USB_EP7R_DTOG_TX_Msk           /*!< Data Toggle, for transmission transfers */
#define USB_EP7R_CTR_TX_Pos                     (7U)
#define USB_EP7R_CTR_TX_Msk                     (0x1UL << USB_EP7R_CTR_TX_Pos)  /*!< 0x00000080 */
#define USB_EP7R_CTR_TX                         USB_EP7R_CTR_TX_Msk            /*!< Correct Transfer for transmission */
#define USB_EP7R_EP_KIND_Pos                    (8U)
#define USB_EP7R_EP_KIND_Msk                    (0x1UL << USB_EP7R_EP_KIND_Pos) /*!< 0x00000100 */
#define USB_EP7R_EP_KIND                        USB_EP7R_EP_KIND_Msk           /*!< Endpoint Kind */

#define USB_EP7R_EP_TYPE_Pos                    (9U)
#define USB_EP7R_EP_TYPE_Msk                    (0x3UL << USB_EP7R_EP_TYPE_Pos) /*!< 0x00000600 */
#define USB_EP7R_EP_TYPE                        USB_EP7R_EP_TYPE_Msk           /*!< EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP7R_EP_TYPE_0                      (0x1UL << USB_EP7R_EP_TYPE_Pos) /*!< 0x00000200 */
#define USB_EP7R_EP_TYPE_1                      (0x2UL << USB_EP7R_EP_TYPE_Pos) /*!< 0x00000400 */

#define USB_EP7R_SETUP_Pos                      (11U)
#define USB_EP7R_SETUP_Msk                      (0x1UL << USB_EP7R_SETUP_Pos)   /*!< 0x00000800 */
#define USB_EP7R_SETUP                          USB_EP7R_SETUP_Msk             /*!< Setup transaction completed */

#define USB_EP7R_STAT_RX_Pos                    (12U)
#define USB_EP7R_STAT_RX_Msk                    (0x3UL << USB_EP7R_STAT_RX_Pos) /*!< 0x00003000 */
#define USB_EP7R_STAT_RX                        USB_EP7R_STAT_RX_Msk           /*!< STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP7R_STAT_RX_0                      (0x1UL << USB_EP7R_STAT_RX_Pos) /*!< 0x00001000 */
#define USB_EP7R_STAT_RX_1                      (0x2UL << USB_EP7R_STAT_RX_Pos) /*!< 0x00002000 */

#define USB_EP7R_DTOG_RX_Pos                    (14U)
#define USB_EP7R_DTOG_RX_Msk                    (0x1UL << USB_EP7R_DTOG_RX_Pos) /*!< 0x00004000 */
#define USB_EP7R_DTOG_RX                        USB_EP7R_DTOG_RX_Msk           /*!< Data Toggle, for reception transfers */
#define USB_EP7R_CTR_RX_Pos                     (15U)
#define USB_EP7R_CTR_RX_Msk                     (0x1UL << USB_EP7R_CTR_RX_Pos)  /*!< 0x00008000 */
#define USB_EP7R_CTR_RX                         USB_EP7R_CTR_RX_Msk            /*!< Correct Transfer for reception */

/*!< Common registers */
/*******************  Bit definition for USB_CNTR register  *******************/
#define USB_CNTR_FRES_Pos                       (0U)
#define USB_CNTR_FRES_Msk                       (0x1UL << USB_CNTR_FRES_Pos)    /*!< 0x00000001 */
#define USB_CNTR_FRES                           USB_CNTR_FRES_Msk              /*!< Force USB Reset */
#define USB_CNTR_PDWN_Pos                       (1U)
#define USB_CNTR_PDWN_Msk                       (0x1UL << USB_CNTR_PDWN_Pos)    /*!< 0x00000002 */
#define USB_CNTR_PDWN                           USB_CNTR_PDWN_Msk              /*!< Power down */
#define USB_CNTR_LP_MODE_Pos                    (2U)
#define USB_CNTR_LP_MODE_Msk                    (0x1UL << USB_CNTR_LP_MODE_Pos) /*!< 0x00000004 */
#define USB_CNTR_LP_MODE                        USB_CNTR_LP_MODE_Msk           /*!< Low-power mode */
#define USB_CNTR_FSUSP_Pos                      (3U)
#define USB_CNTR_FSUSP_Msk                      (0x1UL << USB_CNTR_FSUSP_Pos)   /*!< 0x00000008 */
#define USB_CNTR_FSUSP                          USB_CNTR_FSUSP_Msk             /*!< Force suspend */
#define USB_CNTR_RESUME_Pos                     (4U)
#define USB_CNTR_RESUME_Msk                     (0x1UL << USB_CNTR_RESUME_Pos)  /*!< 0x00000010 */
#define USB_CNTR_RESUME                         USB_CNTR_RESUME_Msk            /*!< Resume request */
#define USB_CNTR_ESOFM_Pos                      (8U)
#define USB_CNTR_ESOFM_Msk                      (0x1UL << USB_CNTR_ESOFM_Pos)   /*!< 0x00000100 */
#define USB_CNTR_ESOFM                          USB_CNTR_ESOFM_Msk             /*!< Expected Start Of Frame Interrupt Mask */
#define USB_CNTR_SOFM_Pos                       (9U)
#define USB_CNTR_SOFM_Msk                       (0x1UL << USB_CNTR_SOFM_Pos)    /*!< 0x00000200 */
#define USB_CNTR_SOFM                           USB_CNTR_SOFM_Msk              /*!< Start Of Frame Interrupt Mask */
#define USB_CNTR_RESETM_Pos                     (10U)
#define USB_CNTR_RESETM_Msk                     (0x1UL << USB_CNTR_RESETM_Pos)  /*!< 0x00000400 */
#define USB_CNTR_RESETM                         USB_CNTR_RESETM_Msk            /*!< RESET Interrupt Mask */
#define USB_CNTR_SUSPM_Pos                      (11U)
#define USB_CNTR_SUSPM_Msk                      (0x1UL << USB_CNTR_SUSPM_Pos)   /*!< 0x00000800 */
#define USB_CNTR_SUSPM                          USB_CNTR_SUSPM_Msk             /*!< Suspend mode Interrupt Mask */
#define USB_CNTR_WKUPM_Pos                      (12U)
#define USB_CNTR_WKUPM_Msk                      (0x1UL << USB_CNTR_WKUPM_Pos)   /*!< 0x00001000 */
#define USB_CNTR_WKUPM                          USB_CNTR_WKUPM_Msk             /*!< Wakeup Interrupt Mask */
#define USB_CNTR_ERRM_Pos                       (13U)
#define USB_CNTR_ERRM_Msk                       (0x1UL << USB_CNTR_ERRM_Pos)    /*!< 0x00002000 */
#define USB_CNTR_ERRM                           USB_CNTR_ERRM_Msk              /*!< Error Interrupt Mask */
#define USB_CNTR_PMAOVRM_Pos                    (14U)
#define USB_CNTR_PMAOVRM_Msk                    (0x1UL << USB_CNTR_PMAOVRM_Pos) /*!< 0x00004000 */
#define USB_CNTR_PMAOVRM                        USB_CNTR_PMAOVRM_Msk           /*!< Packet Memory Area Over / Underrun Interrupt Mask */
#define USB_CNTR_CTRM_Pos                       (15U)
#define USB_CNTR_CTRM_Msk                       (0x1UL << USB_CNTR_CTRM_Pos)    /*!< 0x00008000 */
#define USB_CNTR_CTRM                           USB_CNTR_CTRM_Msk              /*!< Correct Transfer Interrupt Mask */

/*******************  Bit definition for USB_ISTR register  *******************/
#define USB_ISTR_EP_ID_Pos                      (0U)
#define USB_ISTR_EP_ID_Msk                      (0xFUL << USB_ISTR_EP_ID_Pos)   /*!< 0x0000000F */
#define USB_ISTR_EP_ID                          USB_ISTR_EP_ID_Msk             /*!< Endpoint Identifier */
#define USB_ISTR_DIR_Pos                        (4U)
#define USB_ISTR_DIR_Msk                        (0x1UL << USB_ISTR_DIR_Pos)     /*!< 0x00000010 */
#define USB_ISTR_DIR                            USB_ISTR_DIR_Msk               /*!< Direction of transaction */
#define USB_ISTR_ESOF_Pos                       (8U)
#define USB_ISTR_ESOF_Msk                       (0x1UL << USB_ISTR_ESOF_Pos)    /*!< 0x00000100 */
#define USB_ISTR_ESOF                           USB_ISTR_ESOF_Msk              /*!< Expected Start Of Frame */
#define USB_ISTR_SOF_Pos                        (9U)
#define USB_ISTR_SOF_Msk                        (0x1UL << USB_ISTR_SOF_Pos)     /*!< 0x00000200 */
#define USB_ISTR_SOF                            USB_ISTR_SOF_Msk               /*!< Start Of Frame */
#define USB_ISTR_RESET_Pos                      (10U)
#define USB_ISTR_RESET_Msk                      (0x1UL << USB_ISTR_RESET_Pos)   /*!< 0x00000400 */
#define USB_ISTR_RESET                          USB_ISTR_RESET_Msk             /*!< USB RESET request */
#define USB_ISTR_SUSP_Pos                       (11U)
#define USB_ISTR_SUSP_Msk                       (0x1UL << USB_ISTR_SUSP_Pos)    /*!< 0x00000800 */
#define USB_ISTR_SUSP                           USB_ISTR_SUSP_Msk              /*!< Suspend mode request */
#define USB_ISTR_WKUP_Pos                       (12U)
#define USB_ISTR_WKUP_Msk                       (0x1UL << USB_ISTR_WKUP_Pos)    /*!< 0x00001000 */
#define USB_ISTR_WKUP                           USB_ISTR_WKUP_Msk              /*!< Wake up */
#define USB_ISTR_ERR_Pos                        (13U)
#define USB_ISTR_ERR_Msk                        (0x1UL << USB_ISTR_ERR_Pos)     /*!< 0x00002000 */
#define USB_ISTR_ERR                            USB_ISTR_ERR_Msk               /*!< Error */
#define USB_ISTR_PMAOVR_Pos                     (14U)
#define USB_ISTR_PMAOVR_Msk                     (0x1UL << USB_ISTR_PMAOVR_Pos)  /*!< 0x00004000 */
#define USB_ISTR_PMAOVR                         USB_ISTR_PMAOVR_Msk            /*!< Packet Memory Area Over / Underrun */
#define USB_ISTR_CTR_Pos                        (15U)
#define USB_ISTR_CTR_Msk                        (0x1UL << USB_ISTR_CTR_Pos)     /*!< 0x00008000 */
#define USB_ISTR_CTR                            USB_ISTR_CTR_Msk               /*!< Correct Transfer */

/*******************  Bit definition for USB_FNR register  ********************/
#define USB_FNR_FN_Pos                          (0U)
#define USB_FNR_FN_Msk                          (0x7FFUL << USB_FNR_FN_Pos)     /*!< 0x000007FF */
#define USB_FNR_FN                              USB_FNR_FN_Msk                 /*!< Frame Number */
#define USB_FNR_LSOF_Pos                        (11U)
#define USB_FNR_LSOF_Msk                        (0x3UL << USB_FNR_LSOF_Pos)     /*!< 0x00001800 */
#define USB_FNR_LSOF                            USB_FNR_LSOF_Msk               /*!< Lost SOF */
#define USB_FNR_LCK_Pos                         (13U)
#define USB_FNR_LCK_Msk                         (0x1UL << USB_FNR_LCK_Pos)      /*!< 0x00002000 */
#define USB_FNR_LCK                             USB_FNR_LCK_Msk                /*!< Locked */
#define USB_FNR_RXDM_Pos                        (14U)
#define USB_FNR_RXDM_Msk                        (0x1UL << USB_FNR_RXDM_Pos)     /*!< 0x00004000 */
#define USB_FNR_RXDM                            USB_FNR_RXDM_Msk               /*!< Receive Data - Line Status */
#define USB_FNR_RXDP_Pos                        (15U)
#define USB_FNR_RXDP_Msk                        (0x1UL << USB_FNR_RXDP_Pos)     /*!< 0x00008000 */
#define USB_FNR_RXDP                            USB_FNR_RXDP_Msk               /*!< Receive Data + Line Status */

/******************  Bit definition for USB_DADDR register  *******************/
#define USB_DADDR_ADD_Pos                       (0U)
#define USB_DADDR_ADD_Msk                       (0x7FUL << USB_DADDR_ADD_Pos)   /*!< 0x0000007F */
#define USB_DADDR_ADD                           USB_DADDR_ADD_Msk              /*!< ADD[6:0] bits (Device Address) */
#define USB_DADDR_ADD0_Pos                      (0U)
#define USB_DADDR_ADD0_Msk                      (0x1UL << USB_DADDR_ADD0_Pos)   /*!< 0x00000001 */
#define USB_DADDR_ADD0                          USB_DADDR_ADD0_Msk             /*!< Bit 0 */
#define USB_DADDR_ADD1_Pos                      (1U)
#define USB_DADDR_ADD1_Msk                      (0x1UL << USB_DADDR_ADD1_Pos)   /*!< 0x00000002 */
#define USB_DADDR_ADD1                          USB_DADDR_ADD1_Msk             /*!< Bit 1 */
#define USB_DADDR_ADD2_Pos                      (2U)
#define USB_DADDR_ADD2_Msk                      (0x1UL << USB_DADDR_ADD2_Pos)   /*!< 0x00000004 */
#define USB_DADDR_ADD2                          USB_DADDR_ADD2_Msk             /*!< Bit 2 */
#define USB_DADDR_ADD3_Pos                      (3U)
#define USB_DADDR_ADD3_Msk                      (0x1UL << USB_DADDR_ADD3_Pos)   /*!< 0x00000008 */
#define USB_DADDR_ADD3                          USB_DADDR_ADD3_Msk             /*!< Bit 3 */
#define USB_DADDR_ADD4_Pos                      (4U)
#define USB_DADDR_ADD4_Msk                      (0x1UL << USB_DADDR_ADD4_Pos)   /*!< 0x00000010 */
#define USB_DADDR_ADD4                          USB_DADDR_ADD4_Msk             /*!< Bit 4 */
#define USB_DADDR_ADD5_Pos                      (5U)
#define USB_DADDR_ADD5_Msk                      (0x1UL << USB_DADDR_ADD5_Pos)   /*!< 0x00000020 */
#define USB_DADDR_ADD5                          USB_DADDR_ADD5_Msk             /*!< Bit 5 */
#define USB_DADDR_ADD6_Pos                      (6U)
#define USB_DADDR_ADD6_Msk                      (0x1UL << USB_DADDR_ADD6_Pos)   /*!< 0x00000040 */
#define USB_DADDR_ADD6                          USB_DADDR_ADD6_Msk             /*!< Bit 6 */

#define USB_DADDR_EF_Pos                        (7U)
#define USB_DADDR_EF_Msk                        (0x1UL << USB_DADDR_EF_Pos)     /*!< 0x00000080 */
#define USB_DADDR_EF                            USB_DADDR_EF_Msk               /*!< Enable Function */

/******************  Bit definition for USB_BTABLE register  ******************/
#define USB_BTABLE_BTABLE_Pos                   (3U)
#define USB_BTABLE_BTABLE_Msk                   (0x1FFFUL << USB_BTABLE_BTABLE_Pos) /*!< 0x0000FFF8 */
#define USB_BTABLE_BTABLE                       USB_BTABLE_BTABLE_Msk          /*!< Buffer Table */

/******************  Bits definition for USB_BCDR register  *******************/
#define USB_BCDR_BCDEN                           ((uint16_t)0x0001U)           /*!< Battery charging detector (BCD) enable */
#define USB_BCDR_DCDEN                           ((uint16_t)0x0002U)           /*!< Data contact detection (DCD) mode enable */
#define USB_BCDR_PDEN                            ((uint16_t)0x0004U)           /*!< Primary detection (PD) mode enable */
#define USB_BCDR_SDEN                            ((uint16_t)0x0008U)           /*!< Secondary detection (SD) mode enable */
#define USB_BCDR_DCDET                           ((uint16_t)0x0010U)           /*!< Data contact detection (DCD) status */
#define USB_BCDR_PDET                            ((uint16_t)0x0020U)           /*!< Primary detection (PD) status */
#define USB_BCDR_SDET                            ((uint16_t)0x0040U)           /*!< Secondary detection (SD) status */
#define USB_BCDR_PS2DET                          ((uint16_t)0x0080U)           /*!< PS2 port or proprietary charger detected */
#define USB_BCDR_DPPU                            ((uint16_t)0x8000U)           /*!< DP Pull-up Enable */

/*******************  Bit definition for LPMCSR register  *********************/
#define USB_LPMCSR_LMPEN                         ((uint16_t)0x0001U)           /*!< LPM support enable  */
#define USB_LPMCSR_LPMACK                        ((uint16_t)0x0002U)           /*!< LPM Token acknowledge enable*/
#define USB_LPMCSR_REMWAKE                       ((uint16_t)0x0008U)           /*!< bRemoteWake value received with last ACKed LPM Token */
#define USB_LPMCSR_BESL                          ((uint16_t)0x00F0U)           /*!< BESL value received with last ACKed LPM Token  */

/*!< Buffer descriptor table */
/*****************  Bit definition for USB_ADDR0_TX register  *****************/
#define USB_ADDR0_TX_ADDR0_TX_Pos               (1U)
#define USB_ADDR0_TX_ADDR0_TX_Msk               (0x7FFFUL << USB_ADDR0_TX_ADDR0_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR0_TX_ADDR0_TX                   USB_ADDR0_TX_ADDR0_TX_Msk      /*!< Transmission Buffer Address 0 */

/*****************  Bit definition for USB_ADDR1_TX register  *****************/
#define USB_ADDR1_TX_ADDR1_TX_Pos               (1U)
#define USB_ADDR1_TX_ADDR1_TX_Msk               (0x7FFFUL << USB_ADDR1_TX_ADDR1_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR1_TX_ADDR1_TX                   USB_ADDR1_TX_ADDR1_TX_Msk      /*!< Transmission Buffer Address 1 */

/*****************  Bit definition for USB_ADDR2_TX register  *****************/
#define USB_ADDR2_TX_ADDR2_TX_Pos               (1U)
#define USB_ADDR2_TX_ADDR2_TX_Msk               (0x7FFFUL << USB_ADDR2_TX_ADDR2_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR2_TX_ADDR2_TX                   USB_ADDR2_TX_ADDR2_TX_Msk      /*!< Transmission Buffer Address 2 */

/*****************  Bit definition for USB_ADDR3_TX register  *****************/
#define USB_ADDR3_TX_ADDR3_TX_Pos               (1U)
#define USB_ADDR3_TX_ADDR3_TX_Msk               (0x7FFFUL << USB_ADDR3_TX_ADDR3_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR3_TX_ADDR3_TX                   USB_ADDR3_TX_ADDR3_TX_Msk      /*!< Transmission Buffer Address 3 */

/*****************  Bit definition for USB_ADDR4_TX register  *****************/
#define USB_ADDR4_TX_ADDR4_TX_Pos               (1U)
#define USB_ADDR4_TX_ADDR4_TX_Msk               (0x7FFFUL << USB_ADDR4_TX_ADDR4_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR4_TX_ADDR4_TX                   USB_ADDR4_TX_ADDR4_TX_Msk      /*!< Transmission Buffer Address 4 */

/*****************  Bit definition for USB_ADDR5_TX register  *****************/
#define USB_ADDR5_TX_ADDR5_TX_Pos               (1U)
#define USB_ADDR5_TX_ADDR5_TX_Msk               (0x7FFFUL << USB_ADDR5_TX_ADDR5_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR5_TX_ADDR5_TX                   USB_ADDR5_TX_ADDR5_TX_Msk      /*!< Transmission Buffer Address 5 */

/*****************  Bit definition for USB_ADDR6_TX register  *****************/
#define USB_ADDR6_TX_ADDR6_TX_Pos               (1U)
#define USB_ADDR6_TX_ADDR6_TX_Msk               (0x7FFFUL << USB_ADDR6_TX_ADDR6_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR6_TX_ADDR6_TX                   USB_ADDR6_TX_ADDR6_TX_Msk      /*!< Transmission Buffer Address 6 */

/*****************  Bit definition for USB_ADDR7_TX register  *****************/
#define USB_ADDR7_TX_ADDR7_TX_Pos               (1U)
#define USB_ADDR7_TX_ADDR7_TX_Msk               (0x7FFFUL << USB_ADDR7_TX_ADDR7_TX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR7_TX_ADDR7_TX                   USB_ADDR7_TX_ADDR7_TX_Msk      /*!< Transmission Buffer Address 7 */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_COUNT0_TX register  ****************/
#define USB_COUNT0_TX_COUNT0_TX_Pos             (0U)
#define USB_COUNT0_TX_COUNT0_TX_Msk             (0x3FFUL << USB_COUNT0_TX_COUNT0_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT0_TX_COUNT0_TX                 USB_COUNT0_TX_COUNT0_TX_Msk    /*!< Transmission Byte Count 0 */

/*****************  Bit definition for USB_COUNT1_TX register  ****************/
#define USB_COUNT1_TX_COUNT1_TX_Pos             (0U)
#define USB_COUNT1_TX_COUNT1_TX_Msk             (0x3FFUL << USB_COUNT1_TX_COUNT1_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT1_TX_COUNT1_TX                 USB_COUNT1_TX_COUNT1_TX_Msk    /*!< Transmission Byte Count 1 */

/*****************  Bit definition for USB_COUNT2_TX register  ****************/
#define USB_COUNT2_TX_COUNT2_TX_Pos             (0U)
#define USB_COUNT2_TX_COUNT2_TX_Msk             (0x3FFUL << USB_COUNT2_TX_COUNT2_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT2_TX_COUNT2_TX                 USB_COUNT2_TX_COUNT2_TX_Msk    /*!< Transmission Byte Count 2 */

/*****************  Bit definition for USB_COUNT3_TX register  ****************/
#define USB_COUNT3_TX_COUNT3_TX_Pos             (0U)
#define USB_COUNT3_TX_COUNT3_TX_Msk             (0x3FFUL << USB_COUNT3_TX_COUNT3_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT3_TX_COUNT3_TX                 USB_COUNT3_TX_COUNT3_TX_Msk    /*!< Transmission Byte Count 3 */

/*****************  Bit definition for USB_COUNT4_TX register  ****************/
#define USB_COUNT4_TX_COUNT4_TX_Pos             (0U)
#define USB_COUNT4_TX_COUNT4_TX_Msk             (0x3FFUL << USB_COUNT4_TX_COUNT4_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT4_TX_COUNT4_TX                 USB_COUNT4_TX_COUNT4_TX_Msk    /*!< Transmission Byte Count 4 */

/*****************  Bit definition for USB_COUNT5_TX register  ****************/
#define USB_COUNT5_TX_COUNT5_TX_Pos             (0U)
#define USB_COUNT5_TX_COUNT5_TX_Msk             (0x3FFUL << USB_COUNT5_TX_COUNT5_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT5_TX_COUNT5_TX                 USB_COUNT5_TX_COUNT5_TX_Msk    /*!< Transmission Byte Count 5 */

/*****************  Bit definition for USB_COUNT6_TX register  ****************/
#define USB_COUNT6_TX_COUNT6_TX_Pos             (0U)
#define USB_COUNT6_TX_COUNT6_TX_Msk             (0x3FFUL << USB_COUNT6_TX_COUNT6_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT6_TX_COUNT6_TX                 USB_COUNT6_TX_COUNT6_TX_Msk    /*!< Transmission Byte Count 6 */

/*****************  Bit definition for USB_COUNT7_TX register  ****************/
#define USB_COUNT7_TX_COUNT7_TX_Pos             (0U)
#define USB_COUNT7_TX_COUNT7_TX_Msk             (0x3FFUL << USB_COUNT7_TX_COUNT7_TX_Pos) /*!< 0x000003FF */
#define USB_COUNT7_TX_COUNT7_TX                 USB_COUNT7_TX_COUNT7_TX_Msk    /*!< Transmission Byte Count 7 */

/*----------------------------------------------------------------------------*/

/****************  Bit definition for USB_COUNT0_TX_0 register  ***************/
#define USB_COUNT0_TX_0_COUNT0_TX_0             0x000003FFU         /*!< Transmission Byte Count 0 (low) */

/****************  Bit definition for USB_COUNT0_TX_1 register  ***************/
#define USB_COUNT0_TX_1_COUNT0_TX_1             0x03FF0000U         /*!< Transmission Byte Count 0 (high) */

/****************  Bit definition for USB_COUNT1_TX_0 register  ***************/
#define USB_COUNT1_TX_0_COUNT1_TX_0             0x000003FFU         /*!< Transmission Byte Count 1 (low) */

/****************  Bit definition for USB_COUNT1_TX_1 register  ***************/
#define USB_COUNT1_TX_1_COUNT1_TX_1             0x03FF0000U         /*!< Transmission Byte Count 1 (high) */

/****************  Bit definition for USB_COUNT2_TX_0 register  ***************/
#define USB_COUNT2_TX_0_COUNT2_TX_0             0x000003FFU         /*!< Transmission Byte Count 2 (low) */

/****************  Bit definition for USB_COUNT2_TX_1 register  ***************/
#define USB_COUNT2_TX_1_COUNT2_TX_1             0x03FF0000U         /*!< Transmission Byte Count 2 (high) */

/****************  Bit definition for USB_COUNT3_TX_0 register  ***************/
#define USB_COUNT3_TX_0_COUNT3_TX_0             0x000003FFU         /*!< Transmission Byte Count 3 (low) */

/****************  Bit definition for USB_COUNT3_TX_1 register  ***************/
#define USB_COUNT3_TX_1_COUNT3_TX_1             0x03FF0000U         /*!< Transmission Byte Count 3 (high) */

/****************  Bit definition for USB_COUNT4_TX_0 register  ***************/
#define USB_COUNT4_TX_0_COUNT4_TX_0             0x000003FFU         /*!< Transmission Byte Count 4 (low) */

/****************  Bit definition for USB_COUNT4_TX_1 register  ***************/
#define USB_COUNT4_TX_1_COUNT4_TX_1             0x03FF0000U         /*!< Transmission Byte Count 4 (high) */

/****************  Bit definition for USB_COUNT5_TX_0 register  ***************/
#define USB_COUNT5_TX_0_COUNT5_TX_0             0x000003FFU         /*!< Transmission Byte Count 5 (low) */

/****************  Bit definition for USB_COUNT5_TX_1 register  ***************/
#define USB_COUNT5_TX_1_COUNT5_TX_1             0x03FF0000U         /*!< Transmission Byte Count 5 (high) */

/****************  Bit definition for USB_COUNT6_TX_0 register  ***************/
#define USB_COUNT6_TX_0_COUNT6_TX_0             0x000003FFU         /*!< Transmission Byte Count 6 (low) */

/****************  Bit definition for USB_COUNT6_TX_1 register  ***************/
#define USB_COUNT6_TX_1_COUNT6_TX_1             0x03FF0000U         /*!< Transmission Byte Count 6 (high) */

/****************  Bit definition for USB_COUNT7_TX_0 register  ***************/
#define USB_COUNT7_TX_0_COUNT7_TX_0             0x000003FFU         /*!< Transmission Byte Count 7 (low) */

/****************  Bit definition for USB_COUNT7_TX_1 register  ***************/
#define USB_COUNT7_TX_1_COUNT7_TX_1             0x03FF0000U         /*!< Transmission Byte Count 7 (high) */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_ADDR0_RX register  *****************/
#define USB_ADDR0_RX_ADDR0_RX_Pos               (1U)
#define USB_ADDR0_RX_ADDR0_RX_Msk               (0x7FFFUL << USB_ADDR0_RX_ADDR0_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR0_RX_ADDR0_RX                   USB_ADDR0_RX_ADDR0_RX_Msk      /*!< Reception Buffer Address 0 */

/*****************  Bit definition for USB_ADDR1_RX register  *****************/
#define USB_ADDR1_RX_ADDR1_RX_Pos               (1U)
#define USB_ADDR1_RX_ADDR1_RX_Msk               (0x7FFFUL << USB_ADDR1_RX_ADDR1_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR1_RX_ADDR1_RX                   USB_ADDR1_RX_ADDR1_RX_Msk      /*!< Reception Buffer Address 1 */

/*****************  Bit definition for USB_ADDR2_RX register  *****************/
#define USB_ADDR2_RX_ADDR2_RX_Pos               (1U)
#define USB_ADDR2_RX_ADDR2_RX_Msk               (0x7FFFUL << USB_ADDR2_RX_ADDR2_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR2_RX_ADDR2_RX                   USB_ADDR2_RX_ADDR2_RX_Msk      /*!< Reception Buffer Address 2 */

/*****************  Bit definition for USB_ADDR3_RX register  *****************/
#define USB_ADDR3_RX_ADDR3_RX_Pos               (1U)
#define USB_ADDR3_RX_ADDR3_RX_Msk               (0x7FFFUL << USB_ADDR3_RX_ADDR3_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR3_RX_ADDR3_RX                   USB_ADDR3_RX_ADDR3_RX_Msk      /*!< Reception Buffer Address 3 */

/*****************  Bit definition for USB_ADDR4_RX register  *****************/
#define USB_ADDR4_RX_ADDR4_RX_Pos               (1U)
#define USB_ADDR4_RX_ADDR4_RX_Msk               (0x7FFFUL << USB_ADDR4_RX_ADDR4_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR4_RX_ADDR4_RX                   USB_ADDR4_RX_ADDR4_RX_Msk      /*!< Reception Buffer Address 4 */

/*****************  Bit definition for USB_ADDR5_RX register  *****************/
#define USB_ADDR5_RX_ADDR5_RX_Pos               (1U)
#define USB_ADDR5_RX_ADDR5_RX_Msk               (0x7FFFUL << USB_ADDR5_RX_ADDR5_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR5_RX_ADDR5_RX                   USB_ADDR5_RX_ADDR5_RX_Msk      /*!< Reception Buffer Address 5 */

/*****************  Bit definition for USB_ADDR6_RX register  *****************/
#define USB_ADDR6_RX_ADDR6_RX_Pos               (1U)
#define USB_ADDR6_RX_ADDR6_RX_Msk               (0x7FFFUL << USB_ADDR6_RX_ADDR6_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR6_RX_ADDR6_RX                   USB_ADDR6_RX_ADDR6_RX_Msk      /*!< Reception Buffer Address 6 */

/*****************  Bit definition for USB_ADDR7_RX register  *****************/
#define USB_ADDR7_RX_ADDR7_RX_Pos               (1U)
#define USB_ADDR7_RX_ADDR7_RX_Msk               (0x7FFFUL << USB_ADDR7_RX_ADDR7_RX_Pos) /*!< 0x0000FFFE */
#define USB_ADDR7_RX_ADDR7_RX                   USB_ADDR7_RX_ADDR7_RX_Msk      /*!< Reception Buffer Address 7 */

/*----------------------------------------------------------------------------*/

/*****************  Bit definition for USB_COUNT0_RX register  ****************/
#define USB_COUNT0_RX_COUNT0_RX_Pos             (0U)
#define USB_COUNT0_RX_COUNT0_RX_Msk             (0x3FFUL << USB_COUNT0_RX_COUNT0_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT0_RX_COUNT0_RX                 USB_COUNT0_RX_COUNT0_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT0_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT0_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT0_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT0_RX_NUM_BLOCK                 USB_COUNT0_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT0_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT0_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT0_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT0_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT0_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT0_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT0_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT0_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT0_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT0_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT0_RX_BLSIZE_Pos                (15U)
#define USB_COUNT0_RX_BLSIZE_Msk                (0x1UL << USB_COUNT0_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT0_RX_BLSIZE                    USB_COUNT0_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT1_RX register  ****************/
#define USB_COUNT1_RX_COUNT1_RX_Pos             (0U)
#define USB_COUNT1_RX_COUNT1_RX_Msk             (0x3FFUL << USB_COUNT1_RX_COUNT1_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT1_RX_COUNT1_RX                 USB_COUNT1_RX_COUNT1_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT1_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT1_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT1_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT1_RX_NUM_BLOCK                 USB_COUNT1_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT1_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT1_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT1_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT1_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT1_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT1_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT1_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT1_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT1_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT1_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT1_RX_BLSIZE_Pos                (15U)
#define USB_COUNT1_RX_BLSIZE_Msk                (0x1UL << USB_COUNT1_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT1_RX_BLSIZE                    USB_COUNT1_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT2_RX register  ****************/
#define USB_COUNT2_RX_COUNT2_RX_Pos             (0U)
#define USB_COUNT2_RX_COUNT2_RX_Msk             (0x3FFUL << USB_COUNT2_RX_COUNT2_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT2_RX_COUNT2_RX                 USB_COUNT2_RX_COUNT2_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT2_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT2_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT2_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT2_RX_NUM_BLOCK                 USB_COUNT2_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT2_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT2_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT2_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT2_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT2_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT2_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT2_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT2_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT2_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT2_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT2_RX_BLSIZE_Pos                (15U)
#define USB_COUNT2_RX_BLSIZE_Msk                (0x1UL << USB_COUNT2_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT2_RX_BLSIZE                    USB_COUNT2_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT3_RX register  ****************/
#define USB_COUNT3_RX_COUNT3_RX_Pos             (0U)
#define USB_COUNT3_RX_COUNT3_RX_Msk             (0x3FFUL << USB_COUNT3_RX_COUNT3_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT3_RX_COUNT3_RX                 USB_COUNT3_RX_COUNT3_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT3_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT3_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT3_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT3_RX_NUM_BLOCK                 USB_COUNT3_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT3_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT3_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT3_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT3_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT3_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT3_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT3_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT3_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT3_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT3_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT3_RX_BLSIZE_Pos                (15U)
#define USB_COUNT3_RX_BLSIZE_Msk                (0x1UL << USB_COUNT3_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT3_RX_BLSIZE                    USB_COUNT3_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT4_RX register  ****************/
#define USB_COUNT4_RX_COUNT4_RX_Pos             (0U)
#define USB_COUNT4_RX_COUNT4_RX_Msk             (0x3FFUL << USB_COUNT4_RX_COUNT4_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT4_RX_COUNT4_RX                 USB_COUNT4_RX_COUNT4_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT4_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT4_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT4_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT4_RX_NUM_BLOCK                 USB_COUNT4_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT4_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT4_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT4_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT4_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT4_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT4_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT4_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT4_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT4_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT4_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT4_RX_BLSIZE_Pos                (15U)
#define USB_COUNT4_RX_BLSIZE_Msk                (0x1UL << USB_COUNT4_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT4_RX_BLSIZE                    USB_COUNT4_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT5_RX register  ****************/
#define USB_COUNT5_RX_COUNT5_RX_Pos             (0U)
#define USB_COUNT5_RX_COUNT5_RX_Msk             (0x3FFUL << USB_COUNT5_RX_COUNT5_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT5_RX_COUNT5_RX                 USB_COUNT5_RX_COUNT5_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT5_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT5_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT5_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT5_RX_NUM_BLOCK                 USB_COUNT5_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT5_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT5_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT5_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT5_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT5_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT5_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT5_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT5_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT5_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT5_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT5_RX_BLSIZE_Pos                (15U)
#define USB_COUNT5_RX_BLSIZE_Msk                (0x1UL << USB_COUNT5_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT5_RX_BLSIZE                    USB_COUNT5_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT6_RX register  ****************/
#define USB_COUNT6_RX_COUNT6_RX_Pos             (0U)
#define USB_COUNT6_RX_COUNT6_RX_Msk             (0x3FFUL << USB_COUNT6_RX_COUNT6_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT6_RX_COUNT6_RX                 USB_COUNT6_RX_COUNT6_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT6_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT6_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT6_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT6_RX_NUM_BLOCK                 USB_COUNT6_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT6_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT6_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT6_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT6_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT6_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT6_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT6_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT6_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT6_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT6_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT6_RX_BLSIZE_Pos                (15U)
#define USB_COUNT6_RX_BLSIZE_Msk                (0x1UL << USB_COUNT6_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT6_RX_BLSIZE                    USB_COUNT6_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*****************  Bit definition for USB_COUNT7_RX register  ****************/
#define USB_COUNT7_RX_COUNT7_RX_Pos             (0U)
#define USB_COUNT7_RX_COUNT7_RX_Msk             (0x3FFUL << USB_COUNT7_RX_COUNT7_RX_Pos) /*!< 0x000003FF */
#define USB_COUNT7_RX_COUNT7_RX                 USB_COUNT7_RX_COUNT7_RX_Msk    /*!< Reception Byte Count */

#define USB_COUNT7_RX_NUM_BLOCK_Pos             (10U)
#define USB_COUNT7_RX_NUM_BLOCK_Msk             (0x1FUL << USB_COUNT7_RX_NUM_BLOCK_Pos) /*!< 0x00007C00 */
#define USB_COUNT7_RX_NUM_BLOCK                 USB_COUNT7_RX_NUM_BLOCK_Msk    /*!< NUM_BLOCK[4:0] bits (Number of blocks) */
#define USB_COUNT7_RX_NUM_BLOCK_0               (0x01UL << USB_COUNT7_RX_NUM_BLOCK_Pos) /*!< 0x00000400 */
#define USB_COUNT7_RX_NUM_BLOCK_1               (0x02UL << USB_COUNT7_RX_NUM_BLOCK_Pos) /*!< 0x00000800 */
#define USB_COUNT7_RX_NUM_BLOCK_2               (0x04UL << USB_COUNT7_RX_NUM_BLOCK_Pos) /*!< 0x00001000 */
#define USB_COUNT7_RX_NUM_BLOCK_3               (0x08UL << USB_COUNT7_RX_NUM_BLOCK_Pos) /*!< 0x00002000 */
#define USB_COUNT7_RX_NUM_BLOCK_4               (0x10UL << USB_COUNT7_RX_NUM_BLOCK_Pos) /*!< 0x00004000 */

#define USB_COUNT7_RX_BLSIZE_Pos                (15U)
#define USB_COUNT7_RX_BLSIZE_Msk                (0x1UL << USB_COUNT7_RX_BLSIZE_Pos) /*!< 0x00008000 */
#define USB_COUNT7_RX_BLSIZE                    USB_COUNT7_RX_BLSIZE_Msk       /*!< BLock SIZE */

/*----------------------------------------------------------------------------*/

/****************  Bit definition for USB_COUNT0_RX_0 register  ***************/
#define USB_COUNT0_RX_0_COUNT0_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT0_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT0_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT0_RX_1 register  ***************/
#define USB_COUNT0_RX_1_COUNT0_RX_1             0x03FF0000U                    /*!< Reception Byte Count (high) */

#define USB_COUNT0_RX_1_NUM_BLOCK_1             0x7C000000U                    /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_0           0x04000000U                    /*!< Bit 1 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_1           0x08000000U                    /*!< Bit 1 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_2           0x10000000U                    /*!< Bit 2 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_3           0x20000000U                    /*!< Bit 3 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_4           0x40000000U                    /*!< Bit 4 */

#define USB_COUNT0_RX_1_BLSIZE_1                0x80000000U                    /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT1_RX_0 register  ***************/
#define USB_COUNT1_RX_0_COUNT1_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT1_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT1_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT1_RX_1 register  ***************/
#define USB_COUNT1_RX_1_COUNT1_RX_1             0x03FF0000U                    /*!< Reception Byte Count (high) */

#define USB_COUNT1_RX_1_NUM_BLOCK_1             0x7C000000U                    /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_0           0x04000000U                    /*!< Bit 0 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_1           0x08000000U                    /*!< Bit 1 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_2           0x10000000U                    /*!< Bit 2 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_3           0x20000000U                    /*!< Bit 3 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_4           0x40000000U                    /*!< Bit 4 */

#define USB_COUNT1_RX_1_BLSIZE_1                0x80000000U                    /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT2_RX_0 register  ***************/
#define USB_COUNT2_RX_0_COUNT2_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT2_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT2_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT2_RX_1 register  ***************/
#define USB_COUNT2_RX_1_COUNT2_RX_1             0x03FF0000U                    /*!< Reception Byte Count (high) */

#define USB_COUNT2_RX_1_NUM_BLOCK_1             0x7C000000U                    /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_0           0x04000000U                    /*!< Bit 0 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_1           0x08000000U                    /*!< Bit 1 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_2           0x10000000U                    /*!< Bit 2 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_3           0x20000000U                    /*!< Bit 3 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_4           0x40000000U                    /*!< Bit 4 */

#define USB_COUNT2_RX_1_BLSIZE_1                0x80000000U                    /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT3_RX_0 register  ***************/
#define USB_COUNT3_RX_0_COUNT3_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT3_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT3_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT3_RX_1 register  ***************/
#define USB_COUNT3_RX_1_COUNT3_RX_1             0x03FF0000U                    /*!< Reception Byte Count (high) */

#define USB_COUNT3_RX_1_NUM_BLOCK_1             0x7C000000U                    /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_0           0x04000000U                    /*!< Bit 0 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_1           0x08000000U                    /*!< Bit 1 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_2           0x10000000U                    /*!< Bit 2 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_3           0x20000000U                    /*!< Bit 3 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_4           0x40000000U                    /*!< Bit 4 */

#define USB_COUNT3_RX_1_BLSIZE_1                0x80000000U                    /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT4_RX_0 register  ***************/
#define USB_COUNT4_RX_0_COUNT4_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT4_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT4_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT4_RX_1 register  ***************/
#define USB_COUNT4_RX_1_COUNT4_RX_1             0x03FF0000U                    /*!< Reception Byte Count (high) */

#define USB_COUNT4_RX_1_NUM_BLOCK_1             0x7C000000U                    /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_0           0x04000000U                    /*!< Bit 0 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_1           0x08000000U                    /*!< Bit 1 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_2           0x10000000U                    /*!< Bit 2 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_3           0x20000000U                    /*!< Bit 3 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_4           0x40000000U                    /*!< Bit 4 */

#define USB_COUNT4_RX_1_BLSIZE_1                0x80000000U                    /*!< BLock SIZE (high) */

/****************  Bit definition for USB_COUNT5_RX_0 register  ***************/
#define USB_COUNT5_RX_0_COUNT5_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT5_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT5_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT5_RX_1 register  ***************/
#define USB_COUNT5_RX_1_COUNT5_RX_1             0x03FF0000U                    /*!< Reception Byte Count (high) */

#define USB_COUNT5_RX_1_NUM_BLOCK_1             0x7C000000U                    /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_0           0x04000000U                    /*!< Bit 0 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_1           0x08000000U                    /*!< Bit 1 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_2           0x10000000U                    /*!< Bit 2 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_3           0x20000000U                    /*!< Bit 3 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_4           0x40000000U                    /*!< Bit 4 */

#define USB_COUNT5_RX_1_BLSIZE_1                0x80000000U                    /*!< BLock SIZE (high) */

/***************  Bit definition for USB_COUNT6_RX_0  register  ***************/
#define USB_COUNT6_RX_0_COUNT6_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT6_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT6_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/****************  Bit definition for USB_COUNT6_RX_1 register  ***************/
#define USB_COUNT6_RX_1_COUNT6_RX_1             0x03FF0000U                   /*!< Reception Byte Count (high) */

#define USB_COUNT6_RX_1_NUM_BLOCK_1             0x7C000000U                   /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_0           0x04000000U                   /*!< Bit 0 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_1           0x08000000U                   /*!< Bit 1 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_2           0x10000000U                   /*!< Bit 2 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_3           0x20000000U                   /*!< Bit 3 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_4           0x40000000U                   /*!< Bit 4 */

#define USB_COUNT6_RX_1_BLSIZE_1                0x80000000U                   /*!< BLock SIZE (high) */

/***************  Bit definition for USB_COUNT7_RX_0 register  ****************/
#define USB_COUNT7_RX_0_COUNT7_RX_0             0x000003FFU                    /*!< Reception Byte Count (low) */

#define USB_COUNT7_RX_0_NUM_BLOCK_0             0x00007C00U                    /*!< NUM_BLOCK_0[4:0] bits (Number of blocks) (low) */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_0           0x00000400U                    /*!< Bit 0 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_1           0x00000800U                    /*!< Bit 1 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_2           0x00001000U                    /*!< Bit 2 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_3           0x00002000U                    /*!< Bit 3 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_4           0x00004000U                    /*!< Bit 4 */

#define USB_COUNT7_RX_0_BLSIZE_0                0x00008000U                    /*!< BLock SIZE (low) */

/***************  Bit definition for USB_COUNT7_RX_1 register  ****************/
#define USB_COUNT7_RX_1_COUNT7_RX_1             0x03FF0000U                    /*!< Reception Byte Count (high) */

#define USB_COUNT7_RX_1_NUM_BLOCK_1             0x7C000000U                    /*!< NUM_BLOCK_1[4:0] bits (Number of blocks) (high) */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_0           0x04000000U                    /*!< Bit 0 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_1           0x08000000U                    /*!< Bit 1 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_2           0x10000000U                    /*!< Bit 2 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_3           0x20000000U                    /*!< Bit 3 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_4           0x40000000U                    /*!< Bit 4 */

#define USB_COUNT7_RX_1_BLSIZE_1                0x80000000U                    /*!< BLock SIZE (high) */

/**
  * @}
  */

#define BTABLE_ADDRESS                         0x000U

#ifndef PMA_ACCESS
#define PMA_ACCESS                             2U
#endif
/********************  Bit definition for USB_COUNTn_RX register  *************/
#define USB_CNTRX_NBLK_MSK                    (0x1FU << 10)
#define USB_CNTRX_BLSIZE                      (0x1U << 15)

/* SetENDPOINT */
#define PCD_SET_ENDPOINT(USBx, bEpNum, wRegValue)  (*(__IO uint16_t *)(&(USBx)->EP0R + ((bEpNum) * 2U)) = (uint16_t)(wRegValue))

/* GetENDPOINT */
#define PCD_GET_ENDPOINT(USBx, bEpNum)             (*(__IO uint16_t *)(&(USBx)->EP0R + ((bEpNum) * 2U)))

/**
  * @brief  sets the type in the endpoint register(bits EP_TYPE[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wType Endpoint Type.
  * @retval None
  */
#define PCD_SET_EPTYPE(USBx, bEpNum, wType) (PCD_SET_ENDPOINT((USBx), (bEpNum), ((PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EP_T_MASK) | (wType) | USB_EP_CTR_TX | USB_EP_CTR_RX)))

/**
  * @brief  gets the type in the endpoint register(bits EP_TYPE[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval Endpoint Type
  */
#define PCD_GET_EPTYPE(USBx, bEpNum) (PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EP_T_FIELD)

/**
  * @brief free buffer used from the application realizing it to the line
  *         toggles bit SW_BUF in the double buffered endpoint register
  * @param USBx USB device.
  * @param   bEpNum, bDir
  * @retval None
  */
#define PCD_FreeUserBuffer(USBx, bEpNum, bDir) \
  do { \
    if ((bDir) == 0U) \
    { \
      /* OUT double buffered endpoint */ \
      PCD_TX_DTOG((USBx), (bEpNum)); \
    } \
    else if ((bDir) == 1U) \
    { \
      /* IN double buffered endpoint */ \
      PCD_RX_DTOG((USBx), (bEpNum)); \
    } \
  } while(0)

/**
  * @brief  sets the status for tx transfer (bits STAT_TX[1:0]).
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wState new state
  * @retval None
  */
#define PCD_SET_EP_TX_STATUS(USBx, bEpNum, wState) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPTX_DTOGMASK; \
    /* toggle first bit ? */ \
    if ((USB_EPTX_DTOG1 & (wState))!= 0U) \
    { \
      _wRegVal ^= USB_EPTX_DTOG1; \
    } \
    /* toggle second bit ?  */ \
    if ((USB_EPTX_DTOG2 & (wState))!= 0U) \
    { \
      _wRegVal ^= USB_EPTX_DTOG2; \
    } \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX | USB_EP_CTR_TX)); \
  } while(0) /* PCD_SET_EP_TX_STATUS */

/**
  * @brief  sets the status for rx transfer (bits STAT_TX[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wState new state
  * @retval None
  */
#define PCD_SET_EP_RX_STATUS(USBx, bEpNum,wState) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPRX_DTOGMASK; \
    /* toggle first bit ? */ \
    if ((USB_EPRX_DTOG1 & (wState))!= 0U) \
    { \
      _wRegVal ^= USB_EPRX_DTOG1; \
    } \
    /* toggle second bit ? */ \
    if ((USB_EPRX_DTOG2 & (wState))!= 0U) \
    { \
      _wRegVal ^= USB_EPRX_DTOG2; \
    } \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX | USB_EP_CTR_TX)); \
  } while(0) /* PCD_SET_EP_RX_STATUS */

/**
  * @brief  sets the status for rx & tx (bits STAT_TX[1:0] & STAT_RX[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wStaterx new state.
  * @param  wStatetx new state.
  * @retval None
  */
#define PCD_SET_EP_TXRX_STATUS(USBx, bEpNum, wStaterx, wStatetx) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & (USB_EPRX_DTOGMASK | USB_EPTX_STAT); \
    /* toggle first bit ? */ \
    if ((USB_EPRX_DTOG1 & (wStaterx))!= 0U) \
    { \
      _wRegVal ^= USB_EPRX_DTOG1; \
    } \
    /* toggle second bit ? */ \
    if ((USB_EPRX_DTOG2 & (wStaterx))!= 0U) \
    { \
      _wRegVal ^= USB_EPRX_DTOG2; \
    } \
    /* toggle first bit ? */ \
    if ((USB_EPTX_DTOG1 & (wStatetx))!= 0U) \
    { \
      _wRegVal ^= USB_EPTX_DTOG1; \
    } \
    /* toggle second bit ?  */ \
    if ((USB_EPTX_DTOG2 & (wStatetx))!= 0U) \
    { \
      _wRegVal ^= USB_EPTX_DTOG2; \
    } \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX | USB_EP_CTR_TX)); \
  } while(0) /* PCD_SET_EP_TXRX_STATUS */

/**
  * @brief  gets the status for tx/rx transfer (bits STAT_TX[1:0]
  *         /STAT_RX[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval status
  */
#define PCD_GET_EP_TX_STATUS(USBx, bEpNum)     ((uint16_t)PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPTX_STAT)
#define PCD_GET_EP_RX_STATUS(USBx, bEpNum)     ((uint16_t)PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPRX_STAT)

/**
  * @brief  sets directly the VALID tx/rx-status into the endpoint register
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_SET_EP_TX_VALID(USBx, bEpNum)      (PCD_SET_EP_TX_STATUS((USBx), (bEpNum), USB_EP_TX_VALID))
#define PCD_SET_EP_RX_VALID(USBx, bEpNum)      (PCD_SET_EP_RX_STATUS((USBx), (bEpNum), USB_EP_RX_VALID))

/**
  * @brief  checks stall condition in an endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval TRUE = endpoint in stall condition.
  */
#define PCD_GET_EP_TX_STALL_STATUS(USBx, bEpNum) (PCD_GET_EP_TX_STATUS((USBx), (bEpNum)) == USB_EP_TX_STALL)
#define PCD_GET_EP_RX_STALL_STATUS(USBx, bEpNum) (PCD_GET_EP_RX_STATUS((USBx), (bEpNum)) == USB_EP_RX_STALL)

/**
  * @brief  set & clear EP_KIND bit.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_SET_EP_KIND(USBx, bEpNum) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPREG_MASK; \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX | USB_EP_CTR_TX | USB_EP_KIND)); \
  } while(0) /* PCD_SET_EP_KIND */

#define PCD_CLEAR_EP_KIND(USBx, bEpNum) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPKIND_MASK; \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX | USB_EP_CTR_TX)); \
  } while(0) /* PCD_CLEAR_EP_KIND */

/**
  * @brief  Sets/clears directly STATUS_OUT bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_SET_OUT_STATUS(USBx, bEpNum)       PCD_SET_EP_KIND((USBx), (bEpNum))
#define PCD_CLEAR_OUT_STATUS(USBx, bEpNum)     PCD_CLEAR_EP_KIND((USBx), (bEpNum))

/**
  * @brief  Sets/clears directly EP_KIND bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_SET_EP_DBUF(USBx, bEpNum)          PCD_SET_EP_KIND((USBx), (bEpNum))
#define PCD_CLEAR_EP_DBUF(USBx, bEpNum)        PCD_CLEAR_EP_KIND((USBx), (bEpNum))

/**
  * @brief  Clears bit CTR_RX / CTR_TX in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_CLEAR_RX_EP_CTR(USBx, bEpNum) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & (0x7FFFU & USB_EPREG_MASK); \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_TX)); \
  } while(0) /* PCD_CLEAR_RX_EP_CTR */

#define PCD_CLEAR_TX_EP_CTR(USBx, bEpNum) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & (0xFF7FU & USB_EPREG_MASK); \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX)); \
  } while(0) /* PCD_CLEAR_TX_EP_CTR */

/**
  * @brief  Toggles DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_RX_DTOG(USBx, bEpNum) \
  do { \
    uint16_t _wEPVal; \
    \
    _wEPVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPREG_MASK; \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wEPVal | USB_EP_CTR_RX | USB_EP_CTR_TX | USB_EP_DTOG_RX)); \
  } while(0) /* PCD_RX_DTOG */

#define PCD_TX_DTOG(USBx, bEpNum) \
  do { \
    uint16_t _wEPVal; \
    \
    _wEPVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPREG_MASK; \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wEPVal | USB_EP_CTR_RX | USB_EP_CTR_TX | USB_EP_DTOG_TX)); \
  } while(0) /* PCD_TX_DTOG */
/**
  * @brief  Clears DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_CLEAR_RX_DTOG(USBx, bEpNum) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)); \
    \
    if ((_wRegVal & USB_EP_DTOG_RX) != 0U)\
    { \
      PCD_RX_DTOG((USBx), (bEpNum)); \
    } \
  } while(0) /* PCD_CLEAR_RX_DTOG */

#define PCD_CLEAR_TX_DTOG(USBx, bEpNum) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)); \
    \
    if ((_wRegVal & USB_EP_DTOG_TX) != 0U)\
    { \
      PCD_TX_DTOG((USBx), (bEpNum)); \
    } \
  } while(0) /* PCD_CLEAR_TX_DTOG */

/**
  * @brief  Sets address in an endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  bAddr Address.
  * @retval None
  */
#define PCD_SET_EP_ADDRESS(USBx, bEpNum, bAddr) \
  do { \
    uint16_t _wRegVal; \
    \
    _wRegVal = (PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPREG_MASK) | (bAddr); \
    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX | USB_EP_CTR_TX)); \
  } while(0) /* PCD_SET_EP_ADDRESS */

/**
  * @brief  Gets address in an endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_GET_EP_ADDRESS(USBx, bEpNum) ((uint8_t)(PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPADDR_FIELD))

#define PCD_EP_TX_CNT(USBx, bEpNum) ((uint16_t *)((((uint32_t)(USBx)->BTABLE + ((uint32_t)(bEpNum) * 8U) + 2U) * PMA_ACCESS) + ((uint32_t)(USBx) + 0x400U)))
#define PCD_EP_RX_CNT(USBx, bEpNum) ((uint16_t *)((((uint32_t)(USBx)->BTABLE + ((uint32_t)(bEpNum) * 8U) + 6U) * PMA_ACCESS) + ((uint32_t)(USBx) + 0x400U)))

/**
  * @brief  sets address of the tx/rx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wAddr address to be set (must be word aligned).
  * @retval None
  */
#define PCD_SET_EP_TX_ADDRESS(USBx, bEpNum, wAddr) \
  do { \
    __IO uint16_t *_wRegVal; \
    uint32_t _wRegBase = (uint32_t)USBx; \
    \
    _wRegBase += (uint32_t)(USBx)->BTABLE; \
    _wRegVal = (__IO uint16_t *)(_wRegBase + 0x400U + (((uint32_t)(bEpNum) * 8U) * PMA_ACCESS)); \
    *_wRegVal = ((wAddr) >> 1) << 1; \
  } while(0) /* PCD_SET_EP_TX_ADDRESS */

#define PCD_SET_EP_RX_ADDRESS(USBx, bEpNum, wAddr) \
  do { \
    __IO uint16_t *_wRegVal; \
    uint32_t _wRegBase = (uint32_t)USBx; \
    \
    _wRegBase += (uint32_t)(USBx)->BTABLE; \
    _wRegVal = (__IO uint16_t *)(_wRegBase + 0x400U + ((((uint32_t)(bEpNum) * 8U) + 4U) * PMA_ACCESS)); \
    *_wRegVal = ((wAddr) >> 1) << 1; \
  } while(0) /* PCD_SET_EP_RX_ADDRESS */

/**
  * @brief  Gets address of the tx/rx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval address of the buffer.
  */
#define PCD_GET_EP_TX_ADDRESS(USBx, bEpNum) ((uint16_t)*PCD_EP_TX_ADDRESS((USBx), (bEpNum)))
#define PCD_GET_EP_RX_ADDRESS(USBx, bEpNum) ((uint16_t)*PCD_EP_RX_ADDRESS((USBx), (bEpNum)))

/**
  * @brief  Sets counter of rx buffer with no. of blocks.
  * @param  pdwReg Register pointer
  * @param  wCount Counter.
  * @param  wNBlocks no. of Blocks.
  * @retval None
  */
#define PCD_CALC_BLK32(pdwReg, wCount, wNBlocks) \
  do { \
    (wNBlocks) = (wCount) >> 5; \
    if (((wCount) & 0x1fU) == 0U) \
    { \
      (wNBlocks)--; \
    } \
    *(pdwReg) = (uint16_t)(((wNBlocks) << 10) | USB_CNTRX_BLSIZE); \
  } while(0) /* PCD_CALC_BLK32 */

#define PCD_CALC_BLK2(pdwReg, wCount, wNBlocks) \
  do { \
    (wNBlocks) = (wCount) >> 1; \
    if (((wCount) & 0x1U) != 0U) \
    { \
      (wNBlocks)++; \
    } \
    *(pdwReg) = (uint16_t)((wNBlocks) << 10); \
  } while(0) /* PCD_CALC_BLK2 */

#define PCD_SET_EP_CNT_RX_REG(pdwReg, wCount) \
  do { \
    uint32_t wNBlocks; \
    if ((wCount) == 0U) \
    { \
      *(pdwReg) &= (uint16_t)~USB_CNTRX_NBLK_MSK; \
      *(pdwReg) |= USB_CNTRX_BLSIZE; \
    } \
    else if((wCount) <= 62U) \
    { \
      PCD_CALC_BLK2((pdwReg), (wCount), wNBlocks); \
    } \
    else \
    { \
      PCD_CALC_BLK32((pdwReg), (wCount), wNBlocks); \
    } \
  } while(0) /* PCD_SET_EP_CNT_RX_REG */

#define PCD_SET_EP_RX_DBUF0_CNT(USBx, bEpNum, wCount) \
  do { \
    uint32_t _wRegBase = (uint32_t)(USBx); \
    __IO uint16_t *pdwReg; \
    \
    _wRegBase += (uint32_t)(USBx)->BTABLE; \
    pdwReg = (__IO uint16_t *)(_wRegBase + 0x400U + ((((uint32_t)(bEpNum) * 8U) + 2U) * PMA_ACCESS)); \
    PCD_SET_EP_CNT_RX_REG(pdwReg, (wCount)); \
  } while(0)

/**
  * @brief  sets counter for the tx/rx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wCount Counter value.
  * @retval None
  */
#define PCD_SET_EP_TX_CNT(USBx, bEpNum, wCount) \
  do { \
    uint32_t _wRegBase = (uint32_t)(USBx); \
    __IO uint16_t *_wRegVal; \
    \
    _wRegBase += (uint32_t)(USBx)->BTABLE; \
    _wRegVal = (__IO uint16_t *)(_wRegBase + 0x400U + ((((uint32_t)(bEpNum) * 8U) + 2U) * PMA_ACCESS)); \
    *_wRegVal = (uint16_t)(wCount); \
  } while(0)

#define PCD_SET_EP_RX_CNT(USBx, bEpNum, wCount) \
  do { \
    uint32_t _wRegBase = (uint32_t)(USBx); \
    __IO uint16_t *_wRegVal; \
    \
    _wRegBase += (uint32_t)(USBx)->BTABLE; \
    _wRegVal = (__IO uint16_t *)(_wRegBase + 0x400U + ((((uint32_t)(bEpNum) * 8U) + 6U) * PMA_ACCESS)); \
    PCD_SET_EP_CNT_RX_REG(_wRegVal, (wCount)); \
  } while(0)

/**
  * @brief  gets counter of the tx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval Counter value
  */
#define PCD_GET_EP_TX_CNT(USBx, bEpNum)        ((uint32_t)(*PCD_EP_TX_CNT((USBx), (bEpNum))) & 0x3ffU)
#define PCD_GET_EP_RX_CNT(USBx, bEpNum)        ((uint32_t)(*PCD_EP_RX_CNT((USBx), (bEpNum))) & 0x3ffU)

/**
  * @brief  Sets buffer 0/1 address in a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wBuf0Addr buffer 0 address.
  * @retval Counter value
  */
#define PCD_SET_EP_DBUF0_ADDR(USBx, bEpNum, wBuf0Addr) \
  do { \
    PCD_SET_EP_TX_ADDRESS((USBx), (bEpNum), (wBuf0Addr)); \
  } while(0) /* PCD_SET_EP_DBUF0_ADDR */

#define PCD_SET_EP_DBUF1_ADDR(USBx, bEpNum, wBuf1Addr) \
  do { \
    PCD_SET_EP_RX_ADDRESS((USBx), (bEpNum), (wBuf1Addr)); \
  } while(0) /* PCD_SET_EP_DBUF1_ADDR */

/**
  * @brief  Sets addresses in a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  wBuf0Addr: buffer 0 address.
  * @param  wBuf1Addr = buffer 1 address.
  * @retval None
  */
#define PCD_SET_EP_DBUF_ADDR(USBx, bEpNum, wBuf0Addr, wBuf1Addr) \
  do { \
    PCD_SET_EP_DBUF0_ADDR((USBx), (bEpNum), (wBuf0Addr)); \
    PCD_SET_EP_DBUF1_ADDR((USBx), (bEpNum), (wBuf1Addr)); \
  } while(0) /* PCD_SET_EP_DBUF_ADDR */

/**
  * @brief  Gets buffer 0/1 address of a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_GET_EP_DBUF0_ADDR(USBx, bEpNum)    (PCD_GET_EP_TX_ADDRESS((USBx), (bEpNum)))
#define PCD_GET_EP_DBUF1_ADDR(USBx, bEpNum)    (PCD_GET_EP_RX_ADDRESS((USBx), (bEpNum)))

/**
  * @brief  Gets buffer 0/1 address of a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @param  bDir endpoint dir  EP_DBUF_OUT = OUT
  *         EP_DBUF_IN  = IN
  * @param  wCount: Counter value
  * @retval None
  */
#define PCD_SET_EP_DBUF0_CNT(USBx, bEpNum, bDir, wCount) \
  do { \
    if ((bDir) == 0U) \
      /* OUT endpoint */ \
    { \
      PCD_SET_EP_RX_DBUF0_CNT((USBx), (bEpNum), (wCount)); \
    } \
    else \
    { \
      if ((bDir) == 1U) \
      { \
        /* IN endpoint */ \
        PCD_SET_EP_TX_CNT((USBx), (bEpNum), (wCount)); \
      } \
    } \
  } while(0) /* SetEPDblBuf0Count*/

#define PCD_SET_EP_DBUF1_CNT(USBx, bEpNum, bDir, wCount) \
  do { \
    uint32_t _wBase = (uint32_t)(USBx); \
    __IO uint16_t *_wEPRegVal; \
    \
    if ((bDir) == 0U) \
    { \
      /* OUT endpoint */ \
      PCD_SET_EP_RX_CNT((USBx), (bEpNum), (wCount)); \
    } \
    else \
    { \
      if ((bDir) == 1U) \
      { \
        /* IN endpoint */ \
        _wBase += (uint32_t)(USBx)->BTABLE; \
        _wEPRegVal = (__IO uint16_t *)(_wBase + 0x400U + ((((uint32_t)(bEpNum) * 8U) + 6U) * PMA_ACCESS)); \
        *_wEPRegVal = (uint16_t)(wCount); \
      } \
    } \
  } while(0) /* SetEPDblBuf1Count */

#define PCD_SET_EP_DBUF_CNT(USBx, bEpNum, bDir, wCount) \
  do { \
    PCD_SET_EP_DBUF0_CNT((USBx), (bEpNum), (bDir), (wCount)); \
    PCD_SET_EP_DBUF1_CNT((USBx), (bEpNum), (bDir), (wCount)); \
  } while(0) /* PCD_SET_EP_DBUF_CNT */

/**
  * @brief  Gets buffer 0/1 rx/tx counter for double buffering.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpNum Endpoint Number.
  * @retval None
  */
#define PCD_GET_EP_DBUF0_CNT(USBx, bEpNum)     (PCD_GET_EP_TX_CNT((USBx), (bEpNum)))
#define PCD_GET_EP_DBUF1_CNT(USBx, bEpNum)     (PCD_GET_EP_RX_CNT((USBx), (bEpNum)))

#endif