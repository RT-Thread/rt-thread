/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __USB_MUSB_REG_H__
#define __USB_MUSB_REG_H__

#define	__I	volatile const	/* defines 'read only' permissions */
#define __O	volatile	/* defines 'write only' permissions */
#define __IO	volatile	/* defines 'read / write' permissions */

/**
  * @brief Register map for USB0 peripheral (USB0)
  */
#ifdef CONFIG_USB_MUSB_SUNXI
#if 0
typedef __PACKED_STRUCT {                                    /*!< USB0 Structure                                                        */
  union {
    __IO uint8_t   FIFO0_BYTE;                      /*!< USB FIFO Endpoint 0                                                   */
    __IO uint16_t  FIFO0_HALF;                      /*!< USB FIFO Endpoint 0                                                   */
    __IO uint32_t  FIFO0_WORD;                      /*!< USB FIFO Endpoint 0                                                   */
  } FIFO0;
  union {
    __IO uint8_t   FIFO1_BYTE;                      /*!< USB FIFO Endpoint 1                                                   */
    __IO uint16_t  FIFO1_HALF;                      /*!< USB FIFO Endpoint 1                                                   */
    __IO uint32_t  FIFO1_WORD;                      /*!< USB FIFO Endpoint 1                                                   */
  } FIFO1;
  union {
    __IO uint8_t   FIFO2_BYTE;                      /*!< USB FIFO Endpoint 2                                                   */
    __IO uint16_t  FIFO2_HALF;                      /*!< USB FIFO Endpoint 2                                                   */
    __IO uint32_t  FIFO2_WORD;                      /*!< USB FIFO Endpoint 2                                                   */
  } FIFO2;
  union {
    __IO uint8_t   FIFO3_BYTE;                      /*!< USB FIFO Endpoint 3                                                   */
    __IO uint16_t  FIFO3_HALF;                      /*!< USB FIFO Endpoint 3                                                   */
    __IO uint32_t  FIFO3_WORD;                      /*!< USB FIFO Endpoint 3                                                   */
  } FIFO3;
  union {
    __IO uint8_t   FIFO4_BYTE;                      /*!< USB FIFO Endpoint 4                                                   */
    __IO uint16_t  FIFO4_HALF;                      /*!< USB FIFO Endpoint 4                                                   */
    __IO uint32_t  FIFO4_WORD;                      /*!< USB FIFO Endpoint 4                                                   */
  } FIFO4;
  union {
    __IO uint8_t   FIFO5_BYTE;                      /*!< USB FIFO Endpoint 5                                                   */
    __IO uint16_t  FIFO5_HALF;                      /*!< USB FIFO Endpoint 5                                                   */
    __IO uint32_t  FIFO5_WORD;                      /*!< USB FIFO Endpoint 5                                                   */
  } FIFO5;
  union {
    __IO uint8_t   FIFO6_BYTE;                      /*!< USB FIFO Endpoint 6                                                   */
    __IO uint16_t  FIFO6_HALF;                      /*!< USB FIFO Endpoint 6                                                   */
    __IO uint32_t  FIFO6_WORD;                      /*!< USB FIFO Endpoint 6                                                   */
  } FIFO6;
  union {
    __IO uint8_t   FIFO7_BYTE;                      /*!< USB FIFO Endpoint 7                                                   */
    __IO uint16_t  FIFO7_HALF;                      /*!< USB FIFO Endpoint 7                                                   */
    __IO uint32_t  FIFO7_WORD;                      /*!< USB FIFO Endpoint 7                                                   */
  } FIFO7;
  union {
    __IO uint8_t   FIFO_BYTE;                      /*!< USB FIFO Endpoint 7                                                   */
    __IO uint16_t  FIFO_HALF;                      /*!< USB FIFO Endpoint 7                                                   */
    __IO uint32_t  FIFO_WORD;                      /*!< USB FIFO Endpoint 7                                                   */
  } FIFO_RESERVED[8];

    // 0x40
  __IO uint8_t   POWER;                             /*!< USB Power                                                             */
  __IO uint8_t   DEVCTL;                            /*!< USB Device Control                                                    */
  __IO uint8_t   EPIDX;                             /*!< USB Endpoint Index                                                    */
  __IO uint8_t   VEND0;
// 0x44
  __IO uint16_t  TXIS;                              /*!< USB Transmit Interrupt Status                                         */
  __IO uint16_t  RXIS;                              /*!< USB Receive Interrupt Status                                          */
  // 0x48
  __IO uint16_t  TXIE;                              /*!< USB Transmit Interrupt Enable                                         */
  __IO uint16_t  RXIE;                              /*!< USB Receive Interrupt Enable                                          */
// 0x4c
  __IO uint8_t   IS;                                /*!< USB General Interrupt Status                                          */
  __I uint8_t   IS_RESERVED[3];

  __IO  uint8_t   IE;                                /*!< USB Interrupt Enable                                                  */
  __I  uint8_t   IE_RESERVED[3];

  __IO uint16_t  FRAME;                             /*!< USB Frame Value                                                       */
  __I  uint8_t   FRAME_RESERVED[34];

  __IO uint8_t   EPINFO;                            /*!< USB Endpoint Information                                              */
  __IO uint8_t   RAMINFO;                           /*!< USB RAM Information                                                   */
  __IO uint8_t   LINKINFO;
  __IO uint8_t   VPLEN;                             /*!< USB OTG VBUS Pulse Timing                                             */
// 0x7c
  __IO uint8_t   HSEOF;                             /*!< USB High-Speed Last Transaction to End of Frame Timing                */
  __IO uint8_t   FSEOF;                             /*!< USB Full-Speed Last Transaction to End of Frame Timing                */
  __IO uint8_t   LSEOF;                             /*!< USB Low-Speed Last Transaction to End of Frame Timing                 */
  __I  uint8_t   RESERVED7F;

// 0x80
  __IO uint16_t  TXMAXP1;                           /*!< USB Maximum Transmit Data Endpoint 1                                  */
  __PACKED_UNION
  {
    __IO uint8_t   CSRL0;
    __IO uint8_t   TXCSRL1;                           /*!< USB Transmit Control and Status Endpoint 1 Low                        */
  } ;

  __PACKED_UNION
  {
    __O  uint8_t   CSRH0;                             /*!< USB Control and Status Endpoint 0 High                                */
    __IO uint8_t   TXCSRH1;                           /*!< USB Transmit Control and Status Endpoint 1 High                       */
  } ;
// 0x84
  __IO uint16_t  RXMAXP1;                           /*!< USB Maximum Receive Data Endpoint 1                                   */
  __IO uint8_t   RXCSRL1;                           /*!< USB Receive Control and Status Endpoint 1 Low                         */
  __IO uint8_t   RXCSRH1;                           /*!< USB Receive Control and Status Endpoint 1 High                        */

  __PACKED_UNION
  {
    __IO uint16_t  COUNT0;
    __IO uint16_t  RXCOUNT1;                          /*!< USB Receive Byte Count Endpoint 1                                     */
  } ;
  // 0x8A
  __IO uint8_t   TYPE0;                             /*!< USB Type Endpoint 0                                                   */
  __IO uint8_t   NAKLMT;                            /*!< USB NAK Limit                                                         */
  // 0x8C
  __IO uint8_t   TXTYPE1;                           /*!< USB Host Transmit Configure Type Endpoint 1                           */
  __IO uint8_t   TXINTERVAL1;                       /*!< USB Host Transmit Interval Endpoint 1                                 */
  __IO uint8_t   RXTYPE1;                           /*!< USB Host Configure Receive Type Endpoint 1                            */
  __IO uint8_t   RXINTERVAL1;                       /*!< USB Host Receive Polling Interval Endpoint 1                          */
// 0x90
  __IO uint8_t   TXFIFOSZ;                          /*!< USB Transmit Dynamic FIFO Sizing                                      */
  __I  uint8_t   RESERVED91;
  __IO uint16_t  TXFIFOADD;                         /*!< USB Transmit FIFO Start Address                                       */
// 0x94
  __IO uint8_t   RXFIFOSZ;                          /*!< USB Receive Dynamic FIFO Sizing                                       */
  __I  uint8_t   RESERVED95;
  __IO uint16_t  RXFIFOADD;                         /*!< USB Receive FIFO Start Address                                        */

/* "bus control"/target registers, for host side multipoint (external hubs) */
// 0x98
  __PACKED_UNION
  {
    __IO  uint8_t   FADDR;
    __IO  uint8_t   TXFUNCADDR0;
  };

  __I uint8_t    RESERVERD99;
// 0x9A
  __IO uint8_t TXHUBADDR0;
  __IO uint8_t TXHUBPORT0;
// 0x9c
  __IO uint8_t RXFUNCADDR0;
  __I uint8_t RESERVED9d;
  __IO uint8_t RXHUBADDR0;
  __IO uint8_t RXHUBPORT0;
} USB0_Type;
#endif
#else
#if 0
typedef struct {                                    /*!< USB0 Structure                                                        */
  __IO uint8_t   FADDR;                             /*!< USB Device Functional Address                                         */
  __IO uint8_t   POWER;                             /*!< USB Power                                                             */
  __IO uint16_t  TXIS;                              /*!< USB Transmit Interrupt Status                                         */
  __IO uint16_t  RXIS;                              /*!< USB Receive Interrupt Status                                          */
  __IO uint16_t  TXIE;                              /*!< USB Transmit Interrupt Enable                                         */
  __IO uint16_t  RXIE;                              /*!< USB Receive Interrupt Enable                                          */
  __IO uint8_t   IS;                                /*!< USB General Interrupt Status                                          */
  __IO uint8_t   IE;                                /*!< USB Interrupt Enable                                                  */
  __IO uint16_t  FRAME;                             /*!< USB Frame Value                                                       */
  __IO uint8_t   EPIDX;                             /*!< USB Endpoint Index                                                    */
  __IO uint8_t   TEST;                              /*!< USB Test Mode                                                         */
  __I  uint32_t  RESERVED0[4];
 union {
    __IO uint8_t   FIFO0_BYTE;                      /*!< USB FIFO Endpoint 0                                                   */
    __IO uint16_t  FIFO0_HALF;                      /*!< USB FIFO Endpoint 0                                                   */
    __IO uint32_t  FIFO0_WORD;                      /*!< USB FIFO Endpoint 0                                                   */
  } FIFO0;
  union {
    __IO uint8_t   FIFO1_BYTE;                      /*!< USB FIFO Endpoint 1                                                   */
    __IO uint16_t  FIFO1_HALF;                      /*!< USB FIFO Endpoint 1                                                   */
    __IO uint32_t  FIFO1_WORD;                      /*!< USB FIFO Endpoint 1                                                   */
  } FIFO1;
  union {
    __IO uint8_t   FIFO2_BYTE;                      /*!< USB FIFO Endpoint 2                                                   */
    __IO uint16_t  FIFO2_HALF;                      /*!< USB FIFO Endpoint 2                                                   */
    __IO uint32_t  FIFO2_WORD;                      /*!< USB FIFO Endpoint 2                                                   */
  } FIFO2;
  union {
    __IO uint8_t   FIFO3_BYTE;                      /*!< USB FIFO Endpoint 3                                                   */
    __IO uint16_t  FIFO3_HALF;                      /*!< USB FIFO Endpoint 3                                                   */
    __IO uint32_t  FIFO3_WORD;                      /*!< USB FIFO Endpoint 3                                                   */
  } FIFO3;
  union {
    __IO uint8_t   FIFO4_BYTE;                      /*!< USB FIFO Endpoint 4                                                   */
    __IO uint16_t  FIFO4_HALF;                      /*!< USB FIFO Endpoint 4                                                   */
    __IO uint32_t  FIFO4_WORD;                      /*!< USB FIFO Endpoint 4                                                   */
  } FIFO4;
  union {
    __IO uint8_t   FIFO5_BYTE;                      /*!< USB FIFO Endpoint 5                                                   */
    __IO uint16_t  FIFO5_HALF;                      /*!< USB FIFO Endpoint 5                                                   */
    __IO uint32_t  FIFO5_WORD;                      /*!< USB FIFO Endpoint 5                                                   */
  } FIFO5;
  union {
    __IO uint8_t   FIFO6_BYTE;                      /*!< USB FIFO Endpoint 6                                                   */
    __IO uint16_t  FIFO6_HALF;                      /*!< USB FIFO Endpoint 6                                                   */
    __IO uint32_t  FIFO6_WORD;                      /*!< USB FIFO Endpoint 6                                                   */
  } FIFO6;
  union {
    __IO uint8_t   FIFO7_BYTE;                      /*!< USB FIFO Endpoint 7                                                   */
    __IO uint16_t  FIFO7_HALF;                      /*!< USB FIFO Endpoint 7                                                   */
    __IO uint32_t  FIFO7_WORD;                      /*!< USB FIFO Endpoint 7                                                   */
  } FIFO7;
  __I  uint32_t  RESERVED1[8];
  __IO uint8_t   DEVCTL;                            /*!< USB Device Control                                                    */
  __IO uint8_t   CCONF;                             /*!< USB Common Configuration                                              */
  __IO uint8_t   TXFIFOSZ;                          /*!< USB Transmit Dynamic FIFO Sizing                                      */
  __IO uint8_t   RXFIFOSZ;                          /*!< USB Receive Dynamic FIFO Sizing                                       */
  __IO uint16_t  TXFIFOADD;                         /*!< USB Transmit FIFO Start Address                                       */
  __IO uint16_t  RXFIFOADD;                         /*!< USB Receive FIFO Start Address                                        */
  __I  uint32_t  RESERVED2[2];
  __IO uint8_t   ULPIVBUSCTL;                       /*!< USB ULPI VBUS Control                                                 */
  __I  uint8_t   RESERVED3[3];
  __IO uint8_t   ULPIREGDATA;                       /*!< USB ULPI Register Data                                                */
  __IO uint8_t   ULPIREGADDR;                       /*!< USB ULPI Register Address                                             */
  __IO uint8_t   ULPIREGCTL;                        /*!< USB ULPI Register Control                                             */
  __I  uint8_t   RESERVED4;
  __IO uint8_t   EPINFO;                            /*!< USB Endpoint Information                                              */
  __IO uint8_t   RAMINFO;                           /*!< USB RAM Information                                                   */
  __IO uint8_t   CONTIM;                            /*!< USB Connect Timing                                                    */
  __IO uint8_t   VPLEN;                             /*!< USB OTG VBUS Pulse Timing                                             */
  __IO uint8_t   HSEOF;                             /*!< USB High-Speed Last Transaction to End of Frame Timing                */
  __IO uint8_t   FSEOF;                             /*!< USB Full-Speed Last Transaction to End of Frame Timing                */
  __IO uint8_t   LSEOF;                             /*!< USB Low-Speed Last Transaction to End of Frame Timing                 */
  __I  uint8_t   RESERVED5;
  __IO uint8_t   TXFUNCADDR0;                       /*!< USB Transmit Functional Address Endpoint 0                            */
  __I  uint8_t   RESERVED6;
  __IO uint8_t   TXHUBADDR0;                        /*!< USB Transmit Hub Address Endpoint 0                                   */
  __IO uint8_t   TXHUBPORT0;                        /*!< USB Transmit Hub Port Endpoint 0                                      */
  __I  uint32_t  RESERVED7;
  __IO uint8_t   TXFUNCADDR1;                       /*!< USB Transmit Functional Address Endpoint 1                            */
  __I  uint8_t   RESERVED8;
  __IO uint8_t   TXHUBADDR1;                        /*!< USB Transmit Hub Address Endpoint 1                                   */
  __IO uint8_t   TXHUBPORT1;                        /*!< USB Transmit Hub Port Endpoint 1                                      */
  __IO uint8_t   RXFUNCADDR1;                       /*!< USB Receive Functional Address Endpoint 1                             */
  __I  uint8_t   RESERVED9;
  __IO uint8_t   RXHUBADDR1;                        /*!< USB Receive Hub Address Endpoint 1                                    */
  __IO uint8_t   RXHUBPORT1;                        /*!< USB Receive Hub Port Endpoint 1                                       */
  __IO uint8_t   TXFUNCADDR2;                       /*!< USB Transmit Functional Address Endpoint 2                            */
  __I  uint8_t   RESERVED10;
  __IO uint8_t   TXHUBADDR2;                        /*!< USB Transmit Hub Address Endpoint 2                                   */
  __IO uint8_t   TXHUBPORT2;                        /*!< USB Transmit Hub Port Endpoint 2                                      */
  __IO uint8_t   RXFUNCADDR2;                       /*!< USB Receive Functional Address Endpoint 2                             */
  __I  uint8_t   RESERVED11;
  __IO uint8_t   RXHUBADDR2;                        /*!< USB Receive Hub Address Endpoint 2                                    */
  __IO uint8_t   RXHUBPORT2;                        /*!< USB Receive Hub Port Endpoint 2                                       */
  __IO uint8_t   TXFUNCADDR3;                       /*!< USB Transmit Functional Address Endpoint 3                            */
  __I  uint8_t   RESERVED12;
  __IO uint8_t   TXHUBADDR3;                        /*!< USB Transmit Hub Address Endpoint 3                                   */
  __IO uint8_t   TXHUBPORT3;                        /*!< USB Transmit Hub Port Endpoint 3                                      */
  __IO uint8_t   RXFUNCADDR3;                       /*!< USB Receive Functional Address Endpoint 3                             */
  __I  uint8_t   RESERVED13;
  __IO uint8_t   RXHUBADDR3;                        /*!< USB Receive Hub Address Endpoint 3                                    */
  __IO uint8_t   RXHUBPORT3;                        /*!< USB Receive Hub Port Endpoint 3                                       */
  __IO uint8_t   TXFUNCADDR4;                       /*!< USB Transmit Functional Address Endpoint 4                            */
  __I  uint8_t   RESERVED14;
  __IO uint8_t   TXHUBADDR4;                        /*!< USB Transmit Hub Address Endpoint 4                                   */
  __IO uint8_t   TXHUBPORT4;                        /*!< USB Transmit Hub Port Endpoint 4                                      */
  __IO uint8_t   RXFUNCADDR4;                       /*!< USB Receive Functional Address Endpoint 4                             */
  __I  uint8_t   RESERVED15;
  __IO uint8_t   RXHUBADDR4;                        /*!< USB Receive Hub Address Endpoint 4                                    */
  __IO uint8_t   RXHUBPORT4;                        /*!< USB Receive Hub Port Endpoint 4                                       */
  __IO uint8_t   TXFUNCADDR5;                       /*!< USB Transmit Functional Address Endpoint 5                            */
  __I  uint8_t   RESERVED16;
  __IO uint8_t   TXHUBADDR5;                        /*!< USB Transmit Hub Address Endpoint 5                                   */
  __IO uint8_t   TXHUBPORT5;                        /*!< USB Transmit Hub Port Endpoint 5                                      */
  __IO uint8_t   RXFUNCADDR5;                       /*!< USB Receive Functional Address Endpoint 5                             */
  __I  uint8_t   RESERVED17;
  __IO uint8_t   RXHUBADDR5;                        /*!< USB Receive Hub Address Endpoint 5                                    */
  __IO uint8_t   RXHUBPORT5;                        /*!< USB Receive Hub Port Endpoint 5                                       */
  __IO uint8_t   TXFUNCADDR6;                       /*!< USB Transmit Functional Address Endpoint 6                            */
  __I  uint8_t   RESERVED18;
  __IO uint8_t   TXHUBADDR6;                        /*!< USB Transmit Hub Address Endpoint 6                                   */
  __IO uint8_t   TXHUBPORT6;                        /*!< USB Transmit Hub Port Endpoint 6                                      */
  __IO uint8_t   RXFUNCADDR6;                       /*!< USB Receive Functional Address Endpoint 6                             */
  __I  uint8_t   RESERVED19;
  __IO uint8_t   RXHUBADDR6;                        /*!< USB Receive Hub Address Endpoint 6                                    */
  __IO uint8_t   RXHUBPORT6;                        /*!< USB Receive Hub Port Endpoint 6                                       */
  __IO uint8_t   TXFUNCADDR7;                       /*!< USB Transmit Functional Address Endpoint 7                            */
  __I  uint8_t   RESERVED20;
  __IO uint8_t   TXHUBADDR7;                        /*!< USB Transmit Hub Address Endpoint 7                                   */
  __IO uint8_t   TXHUBPORT7;                        /*!< USB Transmit Hub Port Endpoint 7                                      */
  __IO uint8_t   RXFUNCADDR7;                       /*!< USB Receive Functional Address Endpoint 7                             */
  __I  uint8_t   RESERVED21;
  __IO uint8_t   RXHUBADDR7;                        /*!< USB Receive Hub Address Endpoint 7                                    */
  __IO uint8_t   RXHUBPORT7;                        /*!< USB Receive Hub Port Endpoint 7                                       */
  __I  uint32_t  RESERVED22[16];
  __I  uint16_t  RESERVED23;
  __O  uint8_t   CSRL0;                             /*!< USB Control and Status Endpoint 0 Low                                 */
  __O  uint8_t   CSRH0;                             /*!< USB Control and Status Endpoint 0 High                                */
  __I  uint16_t  RESERVED24[2];
  __IO uint8_t   COUNT0;                            /*!< USB Receive Byte Count Endpoint 0                                     */
  __I  uint8_t   RESERVED25;
  __IO uint8_t   TYPE0;                             /*!< USB Type Endpoint 0                                                   */
  __IO uint8_t   NAKLMT;                            /*!< USB NAK Limit                                                         */
  __I  uint32_t  RESERVED26;
  __IO uint16_t  TXMAXP1;                           /*!< USB Maximum Transmit Data Endpoint 1                                  */
  __IO uint8_t   TXCSRL1;                           /*!< USB Transmit Control and Status Endpoint 1 Low                        */
  __IO uint8_t   TXCSRH1;                           /*!< USB Transmit Control and Status Endpoint 1 High                       */
  __IO uint16_t  RXMAXP1;                           /*!< USB Maximum Receive Data Endpoint 1                                   */
  __IO uint8_t   RXCSRL1;                           /*!< USB Receive Control and Status Endpoint 1 Low                         */
  __IO uint8_t   RXCSRH1;                           /*!< USB Receive Control and Status Endpoint 1 High                        */
  __IO uint16_t  RXCOUNT1;                          /*!< USB Receive Byte Count Endpoint 1                                     */
  __IO uint8_t   TXTYPE1;                           /*!< USB Host Transmit Configure Type Endpoint 1                           */
  __IO uint8_t   TXINTERVAL1;                       /*!< USB Host Transmit Interval Endpoint 1                                 */
  __IO uint8_t   RXTYPE1;                           /*!< USB Host Configure Receive Type Endpoint 1                            */
  __IO uint8_t   RXINTERVAL1;                       /*!< USB Host Receive Polling Interval Endpoint 1                          */
  __I  uint16_t  RESERVED27;
  __IO uint16_t  TXMAXP2;                           /*!< USB Maximum Transmit Data Endpoint 2                                  */
  __IO uint8_t   TXCSRL2;                           /*!< USB Transmit Control and Status Endpoint 2 Low                        */
  __IO uint8_t   TXCSRH2;                           /*!< USB Transmit Control and Status Endpoint 2 High                       */
  __IO uint16_t  RXMAXP2;                           /*!< USB Maximum Receive Data Endpoint 2                                   */
  __IO uint8_t   RXCSRL2;                           /*!< USB Receive Control and Status Endpoint 2 Low                         */
  __IO uint8_t   RXCSRH2;                           /*!< USB Receive Control and Status Endpoint 2 High                        */
  __IO uint16_t  RXCOUNT2;                          /*!< USB Receive Byte Count Endpoint 2                                     */
  __IO uint8_t   TXTYPE2;                           /*!< USB Host Transmit Configure Type Endpoint 2                           */
  __IO uint8_t   TXINTERVAL2;                       /*!< USB Host Transmit Interval Endpoint 2                                 */
  __IO uint8_t   RXTYPE2;                           /*!< USB Host Configure Receive Type Endpoint 2                            */
  __IO uint8_t   RXINTERVAL2;                       /*!< USB Host Receive Polling Interval Endpoint 2                          */
  __I  uint16_t  RESERVED28;
  __IO uint16_t  TXMAXP3;                           /*!< USB Maximum Transmit Data Endpoint 3                                  */
  __IO uint8_t   TXCSRL3;                           /*!< USB Transmit Control and Status Endpoint 3 Low                        */
  __IO uint8_t   TXCSRH3;                           /*!< USB Transmit Control and Status Endpoint 3 High                       */
  __IO uint16_t  RXMAXP3;                           /*!< USB Maximum Receive Data Endpoint 3                                   */
  __IO uint8_t   RXCSRL3;                           /*!< USB Receive Control and Status Endpoint 3 Low                         */
  __IO uint8_t   RXCSRH3;                           /*!< USB Receive Control and Status Endpoint 3 High                        */
  __IO uint16_t  RXCOUNT3;                          /*!< USB Receive Byte Count Endpoint 3                                     */
  __IO uint8_t   TXTYPE3;                           /*!< USB Host Transmit Configure Type Endpoint 3                           */
  __IO uint8_t   TXINTERVAL3;                       /*!< USB Host Transmit Interval Endpoint 3                                 */
  __IO uint8_t   RXTYPE3;                           /*!< USB Host Configure Receive Type Endpoint 3                            */
  __IO uint8_t   RXINTERVAL3;                       /*!< USB Host Receive Polling Interval Endpoint 3                          */
  __I  uint16_t  RESERVED29;
  __IO uint16_t  TXMAXP4;                           /*!< USB Maximum Transmit Data Endpoint 4                                  */
  __IO uint8_t   TXCSRL4;                           /*!< USB Transmit Control and Status Endpoint 4 Low                        */
  __IO uint8_t   TXCSRH4;                           /*!< USB Transmit Control and Status Endpoint 4 High                       */
  __IO uint16_t  RXMAXP4;                           /*!< USB Maximum Receive Data Endpoint 4                                   */
  __IO uint8_t   RXCSRL4;                           /*!< USB Receive Control and Status Endpoint 4 Low                         */
  __IO uint8_t   RXCSRH4;                           /*!< USB Receive Control and Status Endpoint 4 High                        */
  __IO uint16_t  RXCOUNT4;                          /*!< USB Receive Byte Count Endpoint 4                                     */
  __IO uint8_t   TXTYPE4;                           /*!< USB Host Transmit Configure Type Endpoint 4                           */
  __IO uint8_t   TXINTERVAL4;                       /*!< USB Host Transmit Interval Endpoint 4                                 */
  __IO uint8_t   RXTYPE4;                           /*!< USB Host Configure Receive Type Endpoint 4                            */
  __IO uint8_t   RXINTERVAL4;                       /*!< USB Host Receive Polling Interval Endpoint 4                          */
  __I  uint16_t  RESERVED30;
  __IO uint16_t  TXMAXP5;                           /*!< USB Maximum Transmit Data Endpoint 5                                  */
  __IO uint8_t   TXCSRL5;                           /*!< USB Transmit Control and Status Endpoint 5 Low                        */
  __IO uint8_t   TXCSRH5;                           /*!< USB Transmit Control and Status Endpoint 5 High                       */
  __IO uint16_t  RXMAXP5;                           /*!< USB Maximum Receive Data Endpoint 5                                   */
  __IO uint8_t   RXCSRL5;                           /*!< USB Receive Control and Status Endpoint 5 Low                         */
  __IO uint8_t   RXCSRH5;                           /*!< USB Receive Control and Status Endpoint 5 High                        */
  __IO uint16_t  RXCOUNT5;                          /*!< USB Receive Byte Count Endpoint 5                                     */
  __IO uint8_t   TXTYPE5;                           /*!< USB Host Transmit Configure Type Endpoint 5                           */
  __IO uint8_t   TXINTERVAL5;                       /*!< USB Host Transmit Interval Endpoint 5                                 */
  __IO uint8_t   RXTYPE5;                           /*!< USB Host Configure Receive Type Endpoint 5                            */
  __IO uint8_t   RXINTERVAL5;                       /*!< USB Host Receive Polling Interval Endpoint 5                          */
  __I  uint16_t  RESERVED31;
  __IO uint16_t  TXMAXP6;                           /*!< USB Maximum Transmit Data Endpoint 6                                  */
  __IO uint8_t   TXCSRL6;                           /*!< USB Transmit Control and Status Endpoint 6 Low                        */
  __IO uint8_t   TXCSRH6;                           /*!< USB Transmit Control and Status Endpoint 6 High                       */
  __IO uint16_t  RXMAXP6;                           /*!< USB Maximum Receive Data Endpoint 6                                   */
  __IO uint8_t   RXCSRL6;                           /*!< USB Receive Control and Status Endpoint 6 Low                         */
  __IO uint8_t   RXCSRH6;                           /*!< USB Receive Control and Status Endpoint 6 High                        */
  __IO uint16_t  RXCOUNT6;                          /*!< USB Receive Byte Count Endpoint 6                                     */
  __IO uint8_t   TXTYPE6;                           /*!< USB Host Transmit Configure Type Endpoint 6                           */
  __IO uint8_t   TXINTERVAL6;                       /*!< USB Host Transmit Interval Endpoint 6                                 */
  __IO uint8_t   RXTYPE6;                           /*!< USB Host Configure Receive Type Endpoint 6                            */
  __IO uint8_t   RXINTERVAL6;                       /*!< USB Host Receive Polling Interval Endpoint 6                          */
  __I  uint16_t  RESERVED32;
  __IO uint16_t  TXMAXP7;                           /*!< USB Maximum Transmit Data Endpoint 7                                  */
  __IO uint8_t   TXCSRL7;                           /*!< USB Transmit Control and Status Endpoint 7 Low                        */
  __IO uint8_t   TXCSRH7;                           /*!< USB Transmit Control and Status Endpoint 7 High                       */
  __IO uint16_t  RXMAXP7;                           /*!< USB Maximum Receive Data Endpoint 7                                   */
  __IO uint8_t   RXCSRL7;                           /*!< USB Receive Control and Status Endpoint 7 Low                         */
  __IO uint8_t   RXCSRH7;                           /*!< USB Receive Control and Status Endpoint 7 High                        */
  __IO uint16_t  RXCOUNT7;                          /*!< USB Receive Byte Count Endpoint 7                                     */
  __IO uint8_t   TXTYPE7;                           /*!< USB Host Transmit Configure Type Endpoint 7                           */
  __IO uint8_t   TXINTERVAL7;                       /*!< USB Host Transmit Interval Endpoint 7                                 */
  __IO uint8_t   RXTYPE7;                           /*!< USB Host Configure Receive Type Endpoint 7                            */
  __IO uint8_t   RXINTERVAL7;                       /*!< USB Host Receive Polling Interval Endpoint 7                          */
  __I  uint16_t  RESERVED33[65];
  __IO uint8_t   DMAINTR;                           /*!< USB DMA Interrupt                                                     */
  __I  uint8_t   RESERVED34[3];
  __IO uint16_t  DMACTL0;                           /*!< USB DMA Control 0                                                     */
  __I  uint16_t  RESERVED35;
  __IO uint32_t  DMAADDR0;                          /*!< USB DMA Address 0                                                     */
  __IO uint32_t  DMACOUNT0;                         /*!< USB DMA Count 0                                                       */
  __I  uint32_t  RESERVED36;
  __IO uint16_t  DMACTL1;                           /*!< USB DMA Control 1                                                     */
  __I  uint16_t  RESERVED37;
  __IO uint32_t  DMAADDR1;                          /*!< USB DMA Address 1                                                     */
  __IO uint32_t  DMACOUNT1;                         /*!< USB DMA Count 1                                                       */
  __I  uint32_t  RESERVED38;
  __IO uint16_t  DMACTL2;                           /*!< USB DMA Control 2                                                     */
  __I  uint16_t  RESERVED39;
  __IO uint32_t  DMAADDR2;                          /*!< USB DMA Address 2                                                     */
  __IO uint32_t  DMACOUNT2;                         /*!< USB DMA Count 2                                                       */
  __I  uint32_t  RESERVED40;
  __IO uint16_t  DMACTL3;                           /*!< USB DMA Control 3                                                     */
  __I  uint16_t  RESERVED41;
  __IO uint32_t  DMAADDR3;                          /*!< USB DMA Address 3                                                     */
  __IO uint32_t  DMACOUNT3;                         /*!< USB DMA Count 3                                                       */
  __I  uint32_t  RESERVED42;
  __IO uint16_t  DMACTL4;                           /*!< USB DMA Control 4                                                     */
  __I  uint16_t  RESERVED43;
  __IO uint32_t  DMAADDR4;                          /*!< USB DMA Address 4                                                     */
  __IO uint32_t  DMACOUNT4;                         /*!< USB DMA Count 4                                                       */
  __I  uint32_t  RESERVED44;
  __IO uint16_t  DMACTL5;                           /*!< USB DMA Control 5                                                     */
  __I  uint16_t  RESERVED45;
  __IO uint32_t  DMAADDR5;                          /*!< USB DMA Address 5                                                     */
  __IO uint32_t  DMACOUNT5;                         /*!< USB DMA Count 5                                                       */
  __I  uint32_t  RESERVED46;
  __IO uint16_t  DMACTL6;                           /*!< USB DMA Control 6                                                     */
  __I  uint16_t  RESERVED47;
  __IO uint32_t  DMAADDR6;                          /*!< USB DMA Address 6                                                     */
  __IO uint32_t  DMACOUNT6;                         /*!< USB DMA Count 6                                                       */
  __I  uint32_t  RESERVED48;
  __IO uint16_t  DMACTL7;                           /*!< USB DMA Control 7                                                     */
  __I  uint16_t  RESERVED49;
  __IO uint32_t  DMAADDR7;                          /*!< USB DMA Address 7                                                     */
  __IO uint32_t  DMACOUNT7;                         /*!< USB DMA Count 7                                                       */
  __I  uint32_t  RESERVED50[33];
  __IO uint16_t  RQPKTCOUNT1;                       /*!< USB Request Packet Count in Block Transfer Endpoint 1                 */
  __I  uint16_t  RESERVED51;
  __IO uint16_t  RQPKTCOUNT2;                       /*!< USB Request Packet Count in Block Transfer Endpoint 2                 */
  __I  uint16_t  RESERVED52;
  __IO uint16_t  RQPKTCOUNT3;                       /*!< USB Request Packet Count in Block Transfer Endpoint 3                 */
  __I  uint16_t  RESERVED53;
  __IO uint16_t  RQPKTCOUNT4;                       /*!< USB Request Packet Count in Block Transfer Endpoint 4                 */
  __I  uint16_t  RESERVED54;
  __IO uint16_t  RQPKTCOUNT5;                       /*!< USB Request Packet Count in Block Transfer Endpoint 5                 */
  __I  uint16_t  RESERVED55;
  __IO uint16_t  RQPKTCOUNT6;                       /*!< USB Request Packet Count in Block Transfer Endpoint 6                 */
  __I  uint16_t  RESERVED56;
  __IO uint16_t  RQPKTCOUNT7;                       /*!< USB Request Packet Count in Block Transfer Endpoint 7                 */
  __I  uint16_t  RESERVED57[17];
  __IO uint16_t  RXDPKTBUFDIS;                      /*!< USB Receive Double Packet Buffer Disable                              */
  __IO uint16_t  TXDPKTBUFDIS;                      /*!< USB Transmit Double Packet Buffer Disable                             */
  __IO uint16_t  CTO;                               /*!< USB Chirp Timeout                                                     */
  __IO uint16_t  HHSRTN;                            /*!< USB High Speed to UTM Operating Delay                                 */
  __IO uint16_t  HSBT;                              /*!< USB High Speed Time-out Adder                                         */
  __I  uint16_t  RESERVED58[11];
  __IO uint16_t  LPMATTR;                           /*!< USB LPM Attributes                                                    */
  __IO uint8_t   LPMCNTRL;                          /*!< USB LPM Control                                                       */
  __IO uint8_t   LPMIM;                             /*!< USB LPM Interrupt Mask                                                */
  __IO uint8_t   LPMRIS;                            /*!< USB LPM Raw Interrupt Status                                          */
  __IO uint8_t   LPMFADDR;                          /*!< USB LPM Function Address                                              */
  __I  uint16_t  RESERVED59[77];
  __IO uint32_t  EPC;                               /*!< USB External Power Control                                            */
  __IO uint32_t  EPCRIS;                            /*!< USB External Power Control Raw Interrupt Status                       */
  __IO uint32_t  EPCIM;                             /*!< USB External Power Control Interrupt Mask                             */
  __IO uint32_t  EPCISC;                            /*!< USB External Power Control Interrupt Status and Clear                 */
  __IO uint32_t  DRRIS;                             /*!< USB Device RESUME Raw Interrupt Status                                */
  __IO uint32_t  DRIM;                              /*!< USB Device RESUME Interrupt Mask                                      */
  __O  uint32_t  DRISC;                             /*!< USB Device RESUME Interrupt Status and Clear                          */
  __IO uint32_t  GPCS;                              /*!< USB General-Purpose Control and Status                                */
  __I  uint32_t  RESERVED60[4];
  __IO uint32_t  VDC;                               /*!< USB VBUS Droop Control                                                */
  __IO uint32_t  VDCRIS;                            /*!< USB VBUS Droop Control Raw Interrupt Status                           */
  __IO uint32_t  VDCIM;                             /*!< USB VBUS Droop Control Interrupt Mask                                 */
  __IO uint32_t  VDCISC;                            /*!< USB VBUS Droop Control Interrupt Status and Clear                     */
  __I  uint32_t  RESERVED61[736];
  __IO uint32_t  PP;                                /*!< USB Peripheral Properties                                             */
  __IO uint32_t  PC;                                /*!< USB Peripheral Configuration                                          */
  __IO uint32_t  CC;                                /*!< USB Clock Configuration                                               */
} USB0_Type;
#endif
#endif // CONFIG_USB_MUSB_SUNXI

//*****************************************************************************
//
// The following are defines for the Univeral Serial Bus register offsets.
//
//*****************************************************************************
#define USB_O_FADDR             0x00000000  // USB Device Functional Address
#define USB_O_POWER             0x00000001  // USB Power
#define USB_O_TXIS              0x00000002  // USB Transmit Interrupt Status
#define USB_O_RXIS              0x00000004  // USB Receive Interrupt Status
#define USB_O_TXIE              0x00000006  // USB Transmit Interrupt Enable
#define USB_O_RXIE              0x00000008  // USB Receive Interrupt Enable
#define USB_O_IS                0x0000000A  // USB General Interrupt Status
#define USB_O_IE                0x0000000B  // USB Interrupt Enable
#define USB_O_FRAME             0x0000000C  // USB Frame Value
#define USB_O_EPIDX             0x0000000E  // USB Endpoint Index
#define USB_O_TEST              0x0000000F  // USB Test Mode
#define USB_O_FIFO0             0x00000020  // USB FIFO Endpoint 0
#define USB_O_FIFO1             0x00000024  // USB FIFO Endpoint 1
#define USB_O_FIFO2             0x00000028  // USB FIFO Endpoint 2
#define USB_O_FIFO3             0x0000002C  // USB FIFO Endpoint 3
#define USB_O_FIFO4             0x00000030  // USB FIFO Endpoint 4
#define USB_O_FIFO5             0x00000034  // USB FIFO Endpoint 5
#define USB_O_FIFO6             0x00000038  // USB FIFO Endpoint 6
#define USB_O_FIFO7             0x0000003C  // USB FIFO Endpoint 7
#define USB_O_DEVCTL            0x00000060  // USB Device Control
#define USB_O_CCONF             0x00000061  // USB Common Configuration
#define USB_O_TXFIFOSZ          0x00000062  // USB Transmit Dynamic FIFO Sizing
#define USB_O_RXFIFOSZ          0x00000063  // USB Receive Dynamic FIFO Sizing
#define USB_O_TXFIFOADD         0x00000064  // USB Transmit FIFO Start Address
#define USB_O_RXFIFOADD         0x00000066  // USB Receive FIFO Start Address
#define USB_O_ULPIVBUSCTL       0x00000070  // USB ULPI VBUS Control
#define USB_O_ULPIREGDATA       0x00000074  // USB ULPI Register Data
#define USB_O_ULPIREGADDR       0x00000075  // USB ULPI Register Address
#define USB_O_ULPIREGCTL        0x00000076  // USB ULPI Register Control
#define USB_O_EPINFO            0x00000078  // USB Endpoint Information
#define USB_O_RAMINFO           0x00000079  // USB RAM Information
#define USB_O_CONTIM            0x0000007A  // USB Connect Timing
#define USB_O_VPLEN             0x0000007B  // USB OTG VBUS Pulse Timing
#define USB_O_HSEOF             0x0000007C  // USB High-Speed Last Transaction
                                            // to End of Frame Timing
#define USB_O_FSEOF             0x0000007D  // USB Full-Speed Last Transaction
                                            // to End of Frame Timing
#define USB_O_LSEOF             0x0000007E  // USB Low-Speed Last Transaction
                                            // to End of Frame Timing
#define USB_O_TXFUNCADDR0       0x00000080  // USB Transmit Functional Address
                                            // Endpoint 0
#define USB_O_TXHUBADDR0        0x00000082  // USB Transmit Hub Address
                                            // Endpoint 0
#define USB_O_TXHUBPORT0        0x00000083  // USB Transmit Hub Port Endpoint 0
#define USB_O_TXFUNCADDR1       0x00000088  // USB Transmit Functional Address
                                            // Endpoint 1
#define USB_O_TXHUBADDR1        0x0000008A  // USB Transmit Hub Address
                                            // Endpoint 1
#define USB_O_TXHUBPORT1        0x0000008B  // USB Transmit Hub Port Endpoint 1
#define USB_O_RXFUNCADDR1       0x0000008C  // USB Receive Functional Address
                                            // Endpoint 1
#define USB_O_RXHUBADDR1        0x0000008E  // USB Receive Hub Address Endpoint
                                            // 1
#define USB_O_RXHUBPORT1        0x0000008F  // USB Receive Hub Port Endpoint 1
#define USB_O_TXFUNCADDR2       0x00000090  // USB Transmit Functional Address
                                            // Endpoint 2
#define USB_O_TXHUBADDR2        0x00000092  // USB Transmit Hub Address
                                            // Endpoint 2
#define USB_O_TXHUBPORT2        0x00000093  // USB Transmit Hub Port Endpoint 2
#define USB_O_RXFUNCADDR2       0x00000094  // USB Receive Functional Address
                                            // Endpoint 2
#define USB_O_RXHUBADDR2        0x00000096  // USB Receive Hub Address Endpoint
                                            // 2
#define USB_O_RXHUBPORT2        0x00000097  // USB Receive Hub Port Endpoint 2
#define USB_O_TXFUNCADDR3       0x00000098  // USB Transmit Functional Address
                                            // Endpoint 3
#define USB_O_TXHUBADDR3        0x0000009A  // USB Transmit Hub Address
                                            // Endpoint 3
#define USB_O_TXHUBPORT3        0x0000009B  // USB Transmit Hub Port Endpoint 3
#define USB_O_RXFUNCADDR3       0x0000009C  // USB Receive Functional Address
                                            // Endpoint 3
#define USB_O_RXHUBADDR3        0x0000009E  // USB Receive Hub Address Endpoint
                                            // 3
#define USB_O_RXHUBPORT3        0x0000009F  // USB Receive Hub Port Endpoint 3
#define USB_O_TXFUNCADDR4       0x000000A0  // USB Transmit Functional Address
                                            // Endpoint 4
#define USB_O_TXHUBADDR4        0x000000A2  // USB Transmit Hub Address
                                            // Endpoint 4
#define USB_O_TXHUBPORT4        0x000000A3  // USB Transmit Hub Port Endpoint 4
#define USB_O_RXFUNCADDR4       0x000000A4  // USB Receive Functional Address
                                            // Endpoint 4
#define USB_O_RXHUBADDR4        0x000000A6  // USB Receive Hub Address Endpoint
                                            // 4
#define USB_O_RXHUBPORT4        0x000000A7  // USB Receive Hub Port Endpoint 4
#define USB_O_TXFUNCADDR5       0x000000A8  // USB Transmit Functional Address
                                            // Endpoint 5
#define USB_O_TXHUBADDR5        0x000000AA  // USB Transmit Hub Address
                                            // Endpoint 5
#define USB_O_TXHUBPORT5        0x000000AB  // USB Transmit Hub Port Endpoint 5
#define USB_O_RXFUNCADDR5       0x000000AC  // USB Receive Functional Address
                                            // Endpoint 5
#define USB_O_RXHUBADDR5        0x000000AE  // USB Receive Hub Address Endpoint
                                            // 5
#define USB_O_RXHUBPORT5        0x000000AF  // USB Receive Hub Port Endpoint 5
#define USB_O_TXFUNCADDR6       0x000000B0  // USB Transmit Functional Address
                                            // Endpoint 6
#define USB_O_TXHUBADDR6        0x000000B2  // USB Transmit Hub Address
                                            // Endpoint 6
#define USB_O_TXHUBPORT6        0x000000B3  // USB Transmit Hub Port Endpoint 6
#define USB_O_RXFUNCADDR6       0x000000B4  // USB Receive Functional Address
                                            // Endpoint 6
#define USB_O_RXHUBADDR6        0x000000B6  // USB Receive Hub Address Endpoint
                                            // 6
#define USB_O_RXHUBPORT6        0x000000B7  // USB Receive Hub Port Endpoint 6
#define USB_O_TXFUNCADDR7       0x000000B8  // USB Transmit Functional Address
                                            // Endpoint 7
#define USB_O_TXHUBADDR7        0x000000BA  // USB Transmit Hub Address
                                            // Endpoint 7
#define USB_O_TXHUBPORT7        0x000000BB  // USB Transmit Hub Port Endpoint 7
#define USB_O_RXFUNCADDR7       0x000000BC  // USB Receive Functional Address
                                            // Endpoint 7
#define USB_O_RXHUBADDR7        0x000000BE  // USB Receive Hub Address Endpoint
                                            // 7
#define USB_O_RXHUBPORT7        0x000000BF  // USB Receive Hub Port Endpoint 7
#define USB_O_CSRL0             0x00000102  // USB Control and Status Endpoint
                                            // 0 Low
#define USB_O_CSRH0             0x00000103  // USB Control and Status Endpoint
                                            // 0 High
#define USB_O_COUNT0            0x00000108  // USB Receive Byte Count Endpoint
                                            // 0
#define USB_O_TYPE0             0x0000010A  // USB Type Endpoint 0
#define USB_O_NAKLMT            0x0000010B  // USB NAK Limit
#define USB_O_TXMAXP1           0x00000110  // USB Maximum Transmit Data
                                            // Endpoint 1
#define USB_O_TXCSRL1           0x00000112  // USB Transmit Control and Status
                                            // Endpoint 1 Low
#define USB_O_TXCSRH1           0x00000113  // USB Transmit Control and Status
                                            // Endpoint 1 High
#define USB_O_RXMAXP1           0x00000114  // USB Maximum Receive Data
                                            // Endpoint 1
#define USB_O_RXCSRL1           0x00000116  // USB Receive Control and Status
                                            // Endpoint 1 Low
#define USB_O_RXCSRH1           0x00000117  // USB Receive Control and Status
                                            // Endpoint 1 High
#define USB_O_RXCOUNT1          0x00000118  // USB Receive Byte Count Endpoint
                                            // 1
#define USB_O_TXTYPE1           0x0000011A  // USB Host Transmit Configure Type
                                            // Endpoint 1
#define USB_O_TXINTERVAL1       0x0000011B  // USB Host Transmit Interval
                                            // Endpoint 1
#define USB_O_RXTYPE1           0x0000011C  // USB Host Configure Receive Type
                                            // Endpoint 1
#define USB_O_RXINTERVAL1       0x0000011D  // USB Host Receive Polling
                                            // Interval Endpoint 1
#define USB_O_TXMAXP2           0x00000120  // USB Maximum Transmit Data
                                            // Endpoint 2
#define USB_O_TXCSRL2           0x00000122  // USB Transmit Control and Status
                                            // Endpoint 2 Low
#define USB_O_TXCSRH2           0x00000123  // USB Transmit Control and Status
                                            // Endpoint 2 High
#define USB_O_RXMAXP2           0x00000124  // USB Maximum Receive Data
                                            // Endpoint 2
#define USB_O_RXCSRL2           0x00000126  // USB Receive Control and Status
                                            // Endpoint 2 Low
#define USB_O_RXCSRH2           0x00000127  // USB Receive Control and Status
                                            // Endpoint 2 High
#define USB_O_RXCOUNT2          0x00000128  // USB Receive Byte Count Endpoint
                                            // 2
#define USB_O_TXTYPE2           0x0000012A  // USB Host Transmit Configure Type
                                            // Endpoint 2
#define USB_O_TXINTERVAL2       0x0000012B  // USB Host Transmit Interval
                                            // Endpoint 2
#define USB_O_RXTYPE2           0x0000012C  // USB Host Configure Receive Type
                                            // Endpoint 2
#define USB_O_RXINTERVAL2       0x0000012D  // USB Host Receive Polling
                                            // Interval Endpoint 2
#define USB_O_TXMAXP3           0x00000130  // USB Maximum Transmit Data
                                            // Endpoint 3
#define USB_O_TXCSRL3           0x00000132  // USB Transmit Control and Status
                                            // Endpoint 3 Low
#define USB_O_TXCSRH3           0x00000133  // USB Transmit Control and Status
                                            // Endpoint 3 High
#define USB_O_RXMAXP3           0x00000134  // USB Maximum Receive Data
                                            // Endpoint 3
#define USB_O_RXCSRL3           0x00000136  // USB Receive Control and Status
                                            // Endpoint 3 Low
#define USB_O_RXCSRH3           0x00000137  // USB Receive Control and Status
                                            // Endpoint 3 High
#define USB_O_RXCOUNT3          0x00000138  // USB Receive Byte Count Endpoint
                                            // 3
#define USB_O_TXTYPE3           0x0000013A  // USB Host Transmit Configure Type
                                            // Endpoint 3
#define USB_O_TXINTERVAL3       0x0000013B  // USB Host Transmit Interval
                                            // Endpoint 3
#define USB_O_RXTYPE3           0x0000013C  // USB Host Configure Receive Type
                                            // Endpoint 3
#define USB_O_RXINTERVAL3       0x0000013D  // USB Host Receive Polling
                                            // Interval Endpoint 3
#define USB_O_TXMAXP4           0x00000140  // USB Maximum Transmit Data
                                            // Endpoint 4
#define USB_O_TXCSRL4           0x00000142  // USB Transmit Control and Status
                                            // Endpoint 4 Low
#define USB_O_TXCSRH4           0x00000143  // USB Transmit Control and Status
                                            // Endpoint 4 High
#define USB_O_RXMAXP4           0x00000144  // USB Maximum Receive Data
                                            // Endpoint 4
#define USB_O_RXCSRL4           0x00000146  // USB Receive Control and Status
                                            // Endpoint 4 Low
#define USB_O_RXCSRH4           0x00000147  // USB Receive Control and Status
                                            // Endpoint 4 High
#define USB_O_RXCOUNT4          0x00000148  // USB Receive Byte Count Endpoint
                                            // 4
#define USB_O_TXTYPE4           0x0000014A  // USB Host Transmit Configure Type
                                            // Endpoint 4
#define USB_O_TXINTERVAL4       0x0000014B  // USB Host Transmit Interval
                                            // Endpoint 4
#define USB_O_RXTYPE4           0x0000014C  // USB Host Configure Receive Type
                                            // Endpoint 4
#define USB_O_RXINTERVAL4       0x0000014D  // USB Host Receive Polling
                                            // Interval Endpoint 4
#define USB_O_TXMAXP5           0x00000150  // USB Maximum Transmit Data
                                            // Endpoint 5
#define USB_O_TXCSRL5           0x00000152  // USB Transmit Control and Status
                                            // Endpoint 5 Low
#define USB_O_TXCSRH5           0x00000153  // USB Transmit Control and Status
                                            // Endpoint 5 High
#define USB_O_RXMAXP5           0x00000154  // USB Maximum Receive Data
                                            // Endpoint 5
#define USB_O_RXCSRL5           0x00000156  // USB Receive Control and Status
                                            // Endpoint 5 Low
#define USB_O_RXCSRH5           0x00000157  // USB Receive Control and Status
                                            // Endpoint 5 High
#define USB_O_RXCOUNT5          0x00000158  // USB Receive Byte Count Endpoint
                                            // 5
#define USB_O_TXTYPE5           0x0000015A  // USB Host Transmit Configure Type
                                            // Endpoint 5
#define USB_O_TXINTERVAL5       0x0000015B  // USB Host Transmit Interval
                                            // Endpoint 5
#define USB_O_RXTYPE5           0x0000015C  // USB Host Configure Receive Type
                                            // Endpoint 5
#define USB_O_RXINTERVAL5       0x0000015D  // USB Host Receive Polling
                                            // Interval Endpoint 5
#define USB_O_TXMAXP6           0x00000160  // USB Maximum Transmit Data
                                            // Endpoint 6
#define USB_O_TXCSRL6           0x00000162  // USB Transmit Control and Status
                                            // Endpoint 6 Low
#define USB_O_TXCSRH6           0x00000163  // USB Transmit Control and Status
                                            // Endpoint 6 High
#define USB_O_RXMAXP6           0x00000164  // USB Maximum Receive Data
                                            // Endpoint 6
#define USB_O_RXCSRL6           0x00000166  // USB Receive Control and Status
                                            // Endpoint 6 Low
#define USB_O_RXCSRH6           0x00000167  // USB Receive Control and Status
                                            // Endpoint 6 High
#define USB_O_RXCOUNT6          0x00000168  // USB Receive Byte Count Endpoint
                                            // 6
#define USB_O_TXTYPE6           0x0000016A  // USB Host Transmit Configure Type
                                            // Endpoint 6
#define USB_O_TXINTERVAL6       0x0000016B  // USB Host Transmit Interval
                                            // Endpoint 6
#define USB_O_RXTYPE6           0x0000016C  // USB Host Configure Receive Type
                                            // Endpoint 6
#define USB_O_RXINTERVAL6       0x0000016D  // USB Host Receive Polling
                                            // Interval Endpoint 6
#define USB_O_TXMAXP7           0x00000170  // USB Maximum Transmit Data
                                            // Endpoint 7
#define USB_O_TXCSRL7           0x00000172  // USB Transmit Control and Status
                                            // Endpoint 7 Low
#define USB_O_TXCSRH7           0x00000173  // USB Transmit Control and Status
                                            // Endpoint 7 High
#define USB_O_RXMAXP7           0x00000174  // USB Maximum Receive Data
                                            // Endpoint 7
#define USB_O_RXCSRL7           0x00000176  // USB Receive Control and Status
                                            // Endpoint 7 Low
#define USB_O_RXCSRH7           0x00000177  // USB Receive Control and Status
                                            // Endpoint 7 High
#define USB_O_RXCOUNT7          0x00000178  // USB Receive Byte Count Endpoint
                                            // 7
#define USB_O_TXTYPE7           0x0000017A  // USB Host Transmit Configure Type
                                            // Endpoint 7
#define USB_O_TXINTERVAL7       0x0000017B  // USB Host Transmit Interval
                                            // Endpoint 7
#define USB_O_RXTYPE7           0x0000017C  // USB Host Configure Receive Type
                                            // Endpoint 7
#define USB_O_RXINTERVAL7       0x0000017D  // USB Host Receive Polling
                                            // Interval Endpoint 7
#define USB_O_DMAINTR           0x00000200  // USB DMA Interrupt
#define USB_O_DMACTL0           0x00000204  // USB DMA Control 0
#define USB_O_DMAADDR0          0x00000208  // USB DMA Address 0
#define USB_O_DMACOUNT0         0x0000020C  // USB DMA Count 0
#define USB_O_DMACTL1           0x00000214  // USB DMA Control 1
#define USB_O_DMAADDR1          0x00000218  // USB DMA Address 1
#define USB_O_DMACOUNT1         0x0000021C  // USB DMA Count 1
#define USB_O_DMACTL2           0x00000224  // USB DMA Control 2
#define USB_O_DMAADDR2          0x00000228  // USB DMA Address 2
#define USB_O_DMACOUNT2         0x0000022C  // USB DMA Count 2
#define USB_O_DMACTL3           0x00000234  // USB DMA Control 3
#define USB_O_DMAADDR3          0x00000238  // USB DMA Address 3
#define USB_O_DMACOUNT3         0x0000023C  // USB DMA Count 3
#define USB_O_DMACTL4           0x00000244  // USB DMA Control 4
#define USB_O_DMAADDR4          0x00000248  // USB DMA Address 4
#define USB_O_DMACOUNT4         0x0000024C  // USB DMA Count 4
#define USB_O_DMACTL5           0x00000254  // USB DMA Control 5
#define USB_O_DMAADDR5          0x00000258  // USB DMA Address 5
#define USB_O_DMACOUNT5         0x0000025C  // USB DMA Count 5
#define USB_O_DMACTL6           0x00000264  // USB DMA Control 6
#define USB_O_DMAADDR6          0x00000268  // USB DMA Address 6
#define USB_O_DMACOUNT6         0x0000026C  // USB DMA Count 6
#define USB_O_DMACTL7           0x00000274  // USB DMA Control 7
#define USB_O_DMAADDR7          0x00000278  // USB DMA Address 7
#define USB_O_DMACOUNT7         0x0000027C  // USB DMA Count 7
#define USB_O_RQPKTCOUNT1       0x00000304  // USB Request Packet Count in
                                            // Block Transfer Endpoint 1
#define USB_O_RQPKTCOUNT2       0x00000308  // USB Request Packet Count in
                                            // Block Transfer Endpoint 2
#define USB_O_RQPKTCOUNT3       0x0000030C  // USB Request Packet Count in
                                            // Block Transfer Endpoint 3
#define USB_O_RQPKTCOUNT4       0x00000310  // USB Request Packet Count in
                                            // Block Transfer Endpoint 4
#define USB_O_RQPKTCOUNT5       0x00000314  // USB Request Packet Count in
                                            // Block Transfer Endpoint 5
#define USB_O_RQPKTCOUNT6       0x00000318  // USB Request Packet Count in
                                            // Block Transfer Endpoint 6
#define USB_O_RQPKTCOUNT7       0x0000031C  // USB Request Packet Count in
                                            // Block Transfer Endpoint 7
#define USB_O_RXDPKTBUFDIS      0x00000340  // USB Receive Double Packet Buffer
                                            // Disable
#define USB_O_TXDPKTBUFDIS      0x00000342  // USB Transmit Double Packet
                                            // Buffer Disable
#define USB_O_CTO               0x00000344  // USB Chirp Timeout
#define USB_O_HHSRTN            0x00000346  // USB High Speed to UTM Operating
                                            // Delay
#define USB_O_HSBT              0x00000348  // USB High Speed Time-out Adder
#define USB_O_LPMATTR           0x00000360  // USB LPM Attributes
#define USB_O_LPMCNTRL          0x00000362  // USB LPM Control
#define USB_O_LPMIM             0x00000363  // USB LPM Interrupt Mask
#define USB_O_LPMRIS            0x00000364  // USB LPM Raw Interrupt Status
#define USB_O_LPMFADDR          0x00000365  // USB LPM Function Address
#define USB_O_EPC               0x00000400  // USB External Power Control
#define USB_O_EPCRIS            0x00000404  // USB External Power Control Raw
                                            // Interrupt Status
#define USB_O_EPCIM             0x00000408  // USB External Power Control
                                            // Interrupt Mask
#define USB_O_EPCISC            0x0000040C  // USB External Power Control
                                            // Interrupt Status and Clear
#define USB_O_DRRIS             0x00000410  // USB Device RESUME Raw Interrupt
                                            // Status
#define USB_O_DRIM              0x00000414  // USB Device RESUME Interrupt Mask
#define USB_O_DRISC             0x00000418  // USB Device RESUME Interrupt
                                            // Status and Clear
#define USB_O_GPCS              0x0000041C  // USB General-Purpose Control and
                                            // Status
#define USB_O_VDC               0x00000430  // USB VBUS Droop Control
#define USB_O_VDCRIS            0x00000434  // USB VBUS Droop Control Raw
                                            // Interrupt Status
#define USB_O_VDCIM             0x00000438  // USB VBUS Droop Control Interrupt
                                            // Mask
#define USB_O_VDCISC            0x0000043C  // USB VBUS Droop Control Interrupt
                                            // Status and Clear
#define USB_O_IDVRIS            0x00000444  // USB ID Valid Detect Raw
                                            // Interrupt Status
#define USB_O_IDVIM             0x00000448  // USB ID Valid Detect Interrupt
                                            // Mask
#define USB_O_IDVISC            0x0000044C  // USB ID Valid Detect Interrupt
                                            // Status and Clear
#define USB_O_PP                0x00000FC0  // USB Peripheral Properties
#define USB_O_PC                0x00000FC4  // USB Peripheral Configuration
#define USB_O_CC                0x00000FC8  // USB Clock Configuration

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FADDR register.
//
//*****************************************************************************
#define USB_FADDR_M             0x0000007F  // Function Address
#define USB_FADDR_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_POWER register.
//
//*****************************************************************************
#define USB_POWER_ISOUP         0x00000080  // Isochronous Update
#define USB_POWER_SOFTCONN      0x00000040  // Soft Connect/Disconnect
#define USB_POWER_HSENAB        0x00000020  // High Speed Enable
#define USB_POWER_HSMODE        0x00000010  // High Speed Enable
#define USB_POWER_RESET         0x00000008  // RESET Signaling
#define USB_POWER_RESUME        0x00000004  // RESUME Signaling
#define USB_POWER_SUSPEND       0x00000002  // SUSPEND Mode
#define USB_POWER_PWRDNPHY      0x00000001  // Power Down PHY

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXIS register.
//
//*****************************************************************************
#define USB_TXIS_EP7            0x00000080  // TX Endpoint 7 Interrupt
#define USB_TXIS_EP6            0x00000040  // TX Endpoint 6 Interrupt
#define USB_TXIS_EP5            0x00000020  // TX Endpoint 5 Interrupt
#define USB_TXIS_EP4            0x00000010  // TX Endpoint 4 Interrupt
#define USB_TXIS_EP3            0x00000008  // TX Endpoint 3 Interrupt
#define USB_TXIS_EP2            0x00000004  // TX Endpoint 2 Interrupt
#define USB_TXIS_EP1            0x00000002  // TX Endpoint 1 Interrupt
#define USB_TXIS_EP0            0x00000001  // TX and RX Endpoint 0 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXIS register.
//
//*****************************************************************************
#define USB_RXIS_EP7            0x00000080  // RX Endpoint 7 Interrupt
#define USB_RXIS_EP6            0x00000040  // RX Endpoint 6 Interrupt
#define USB_RXIS_EP5            0x00000020  // RX Endpoint 5 Interrupt
#define USB_RXIS_EP4            0x00000010  // RX Endpoint 4 Interrupt
#define USB_RXIS_EP3            0x00000008  // RX Endpoint 3 Interrupt
#define USB_RXIS_EP2            0x00000004  // RX Endpoint 2 Interrupt
#define USB_RXIS_EP1            0x00000002  // RX Endpoint 1 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXIE register.
//
//*****************************************************************************
#define USB_TXIE_EP7            0x00000080  // TX Endpoint 7 Interrupt Enable
#define USB_TXIE_EP6            0x00000040  // TX Endpoint 6 Interrupt Enable
#define USB_TXIE_EP5            0x00000020  // TX Endpoint 5 Interrupt Enable
#define USB_TXIE_EP4            0x00000010  // TX Endpoint 4 Interrupt Enable
#define USB_TXIE_EP3            0x00000008  // TX Endpoint 3 Interrupt Enable
#define USB_TXIE_EP2            0x00000004  // TX Endpoint 2 Interrupt Enable
#define USB_TXIE_EP1            0x00000002  // TX Endpoint 1 Interrupt Enable
#define USB_TXIE_EP0            0x00000001  // TX and RX Endpoint 0 Interrupt
                                            // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXIE register.
//
//*****************************************************************************
#define USB_RXIE_EP7            0x00000080  // RX Endpoint 7 Interrupt Enable
#define USB_RXIE_EP6            0x00000040  // RX Endpoint 6 Interrupt Enable
#define USB_RXIE_EP5            0x00000020  // RX Endpoint 5 Interrupt Enable
#define USB_RXIE_EP4            0x00000010  // RX Endpoint 4 Interrupt Enable
#define USB_RXIE_EP3            0x00000008  // RX Endpoint 3 Interrupt Enable
#define USB_RXIE_EP2            0x00000004  // RX Endpoint 2 Interrupt Enable
#define USB_RXIE_EP1            0x00000002  // RX Endpoint 1 Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_IS register.
//
//*****************************************************************************
#define USB_IS_VBUSERR          0x00000080  // VBUS Error (OTG only)
#define USB_IS_SESREQ           0x00000040  // SESSION REQUEST (OTG only)
#define USB_IS_DISCON           0x00000020  // Session Disconnect (OTG only)
#define USB_IS_CONN             0x00000010  // Session Connect
#define USB_IS_SOF              0x00000008  // Start of Frame
#define USB_IS_BABBLE           0x00000004  // Babble Detected
#define USB_IS_RESET            0x00000004  // RESET Signaling Detected
#define USB_IS_RESUME           0x00000002  // RESUME Signaling Detected
#define USB_IS_SUSPEND          0x00000001  // SUSPEND Signaling Detected

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_IE register.
//
//*****************************************************************************
#define USB_IE_VBUSERR          0x00000080  // Enable VBUS Error Interrupt (OTG
                                            // only)
#define USB_IE_SESREQ           0x00000040  // Enable Session Request (OTG
                                            // only)
#define USB_IE_DISCON           0x00000020  // Enable Disconnect Interrupt
#define USB_IE_CONN             0x00000010  // Enable Connect Interrupt
#define USB_IE_SOF              0x00000008  // Enable Start-of-Frame Interrupt
#define USB_IE_BABBLE           0x00000004  // Enable Babble Interrupt
#define USB_IE_RESET            0x00000004  // Enable RESET Interrupt
#define USB_IE_RESUME           0x00000002  // Enable RESUME Interrupt
#define USB_IE_SUSPND           0x00000001  // Enable SUSPEND Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FRAME register.
//
//*****************************************************************************
#define USB_FRAME_M             0x000007FF  // Frame Number
#define USB_FRAME_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPIDX register.
//
//*****************************************************************************
#define USB_EPIDX_EPIDX_M       0x0000000F  // Endpoint Index
#define USB_EPIDX_EPIDX_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TEST register.
//
//*****************************************************************************
#define USB_TEST_FORCEH         0x00000080  // Force Host Mode
#define USB_TEST_FIFOACC        0x00000040  // FIFO Access
#define USB_TEST_FORCEFS        0x00000020  // Force Full-Speed Mode
#define USB_TEST_FORCEHS        0x00000010  // Force High-Speed Mode
#define USB_TEST_TESTPKT        0x00000008  // Test Packet Mode Enable
#define USB_TEST_TESTK          0x00000004  // Test_K Mode Enable
#define USB_TEST_TESTJ          0x00000002  // Test_J Mode Enable
#define USB_TEST_TESTSE0NAK     0x00000001  // Test_SE0_NAK Test Mode Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO0 register.
//
//*****************************************************************************
#define USB_FIFO0_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO0_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO1 register.
//
//*****************************************************************************
#define USB_FIFO1_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO1_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO2 register.
//
//*****************************************************************************
#define USB_FIFO2_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO2_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO3 register.
//
//*****************************************************************************
#define USB_FIFO3_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO3_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO4 register.
//
//*****************************************************************************
#define USB_FIFO4_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO4_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO5 register.
//
//*****************************************************************************
#define USB_FIFO5_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO5_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO6 register.
//
//*****************************************************************************
#define USB_FIFO6_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO6_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO7 register.
//
//*****************************************************************************
#define USB_FIFO7_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO7_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DEVCTL register.
//
//*****************************************************************************
#define USB_DEVCTL_DEV          0x00000080  // Device Mode (OTG only)
#define USB_DEVCTL_FSDEV        0x00000040  // Full-Speed Device Detected
#define USB_DEVCTL_LSDEV        0x00000020  // Low-Speed Device Detected
#define USB_DEVCTL_VBUS_M       0x00000018  // VBUS Level (OTG only)
#define USB_DEVCTL_VBUS_NONE    0x00000000  // Below SessionEnd
#define USB_DEVCTL_VBUS_SEND    0x00000008  // Above SessionEnd, below AValid
#define USB_DEVCTL_VBUS_AVALID  0x00000010  // Above AValid, below VBUSValid
#define USB_DEVCTL_VBUS_VALID   0x00000018  // Above VBUSValid
#define USB_DEVCTL_HOST         0x00000004  // Host Mode
#define USB_DEVCTL_HOSTREQ      0x00000002  // Host Request (OTG only)
#define USB_DEVCTL_SESSION      0x00000001  // Session Start/End (OTG only)

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CCONF register.
//
//*****************************************************************************
#define USB_CCONF_TXEDMA        0x00000002  // TX Early DMA Enable
#define USB_CCONF_RXEDMA        0x00000001  // TX Early DMA Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFIFOSZ register.
//
//*****************************************************************************
#define USB_TXFIFOSZ_DPB        0x00000010  // Double Packet Buffer Support
#define USB_TXFIFOSZ_SIZE_M     0x0000000F  // Max Packet Size
#define USB_TXFIFOSZ_SIZE_8     0x00000000  // 8
#define USB_TXFIFOSZ_SIZE_16    0x00000001  // 16
#define USB_TXFIFOSZ_SIZE_32    0x00000002  // 32
#define USB_TXFIFOSZ_SIZE_64    0x00000003  // 64
#define USB_TXFIFOSZ_SIZE_128   0x00000004  // 128
#define USB_TXFIFOSZ_SIZE_256   0x00000005  // 256
#define USB_TXFIFOSZ_SIZE_512   0x00000006  // 512
#define USB_TXFIFOSZ_SIZE_1024  0x00000007  // 1024
#define USB_TXFIFOSZ_SIZE_2048  0x00000008  // 2048

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFIFOSZ register.
//
//*****************************************************************************
#define USB_RXFIFOSZ_DPB        0x00000010  // Double Packet Buffer Support
#define USB_RXFIFOSZ_SIZE_M     0x0000000F  // Max Packet Size
#define USB_RXFIFOSZ_SIZE_8     0x00000000  // 8
#define USB_RXFIFOSZ_SIZE_16    0x00000001  // 16
#define USB_RXFIFOSZ_SIZE_32    0x00000002  // 32
#define USB_RXFIFOSZ_SIZE_64    0x00000003  // 64
#define USB_RXFIFOSZ_SIZE_128   0x00000004  // 128
#define USB_RXFIFOSZ_SIZE_256   0x00000005  // 256
#define USB_RXFIFOSZ_SIZE_512   0x00000006  // 512
#define USB_RXFIFOSZ_SIZE_1024  0x00000007  // 1024
#define USB_RXFIFOSZ_SIZE_2048  0x00000008  // 2048

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFIFOADD
// register.
//
//*****************************************************************************
#define USB_TXFIFOADD_ADDR_M    0x000001FF  // Transmit/Receive Start Address
#define USB_TXFIFOADD_ADDR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFIFOADD
// register.
//
//*****************************************************************************
#define USB_RXFIFOADD_ADDR_M    0x000001FF  // Transmit/Receive Start Address
#define USB_RXFIFOADD_ADDR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIVBUSCTL
// register.
//
//*****************************************************************************
#define USB_ULPIVBUSCTL_USEEXTVBUSIND                                         \
                                0x00000002  // Use External VBUS Indicator
#define USB_ULPIVBUSCTL_USEEXTVBUS                                            \
                                0x00000001  // Use External VBUS

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIREGDATA
// register.
//
//*****************************************************************************
#define USB_ULPIREGDATA_REGDATA_M                                             \
                                0x000000FF  // Register Data
#define USB_ULPIREGDATA_REGDATA_S                                             \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIREGADDR
// register.
//
//*****************************************************************************
#define USB_ULPIREGADDR_ADDR_M  0x000000FF  // Register Address
#define USB_ULPIREGADDR_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIREGCTL
// register.
//
//*****************************************************************************
#define USB_ULPIREGCTL_RDWR     0x00000004  // Read/Write Control
#define USB_ULPIREGCTL_REGCMPLT 0x00000002  // Register Access Complete
#define USB_ULPIREGCTL_REGACC   0x00000001  // Initiate Register Access

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPINFO register.
//
//*****************************************************************************
#define USB_EPINFO_RXEP_M       0x000000F0  // RX Endpoints
#define USB_EPINFO_TXEP_M       0x0000000F  // TX Endpoints
#define USB_EPINFO_RXEP_S       4
#define USB_EPINFO_TXEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RAMINFO register.
//
//*****************************************************************************
#define USB_RAMINFO_DMACHAN_M   0x000000F0  // DMA Channels
#define USB_RAMINFO_RAMBITS_M   0x0000000F  // RAM Address Bus Width
#define USB_RAMINFO_DMACHAN_S   4
#define USB_RAMINFO_RAMBITS_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CONTIM register.
//
//*****************************************************************************
#define USB_CONTIM_WTCON_M      0x000000F0  // Connect Wait
#define USB_CONTIM_WTID_M       0x0000000F  // Wait ID
#define USB_CONTIM_WTCON_S      4
#define USB_CONTIM_WTID_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VPLEN register.
//
//*****************************************************************************
#define USB_VPLEN_VPLEN_M       0x000000FF  // VBUS Pulse Length
#define USB_VPLEN_VPLEN_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_HSEOF register.
//
//*****************************************************************************
#define USB_HSEOF_HSEOFG_M      0x000000FF  // HIgh-Speed End-of-Frame Gap
#define USB_HSEOF_HSEOFG_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FSEOF register.
//
//*****************************************************************************
#define USB_FSEOF_FSEOFG_M      0x000000FF  // Full-Speed End-of-Frame Gap
#define USB_FSEOF_FSEOFG_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LSEOF register.
//
//*****************************************************************************
#define USB_LSEOF_LSEOFG_M      0x000000FF  // Low-Speed End-of-Frame Gap
#define USB_LSEOF_LSEOFG_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR0
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR0_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR0_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR0
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR0_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR0_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT0
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT0_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT0_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR1
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR1_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR1_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR1
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR1_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR1_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT1
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT1_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT1_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR1
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR1_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR1_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR1
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR1_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR1_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT1
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT1_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT1_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR2
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR2_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR2_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR2
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR2_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR2_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT2
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT2_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT2_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR2
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR2_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR2_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR2
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR2_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR2_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT2
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT2_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT2_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR3
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR3_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR3_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR3
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR3_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR3_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT3
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT3_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT3_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR3
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR3_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR3_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR3
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR3_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR3_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT3
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT3_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT3_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR4
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR4_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR4_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR4
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR4_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR4_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT4
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT4_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT4_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR4
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR4_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR4_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR4
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR4_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR4_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT4
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT4_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT4_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR5
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR5_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR5_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR5
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR5_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR5_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT5
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT5_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT5_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR5
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR5_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR5_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR5
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR5_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR5_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT5
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT5_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT5_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR6
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR6_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR6_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR6
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR6_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR6_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT6
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT6_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT6_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR6
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR6_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR6_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR6
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR6_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR6_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT6
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT6_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT6_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR7
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR7_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR7_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR7
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR7_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR7_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT7
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT7_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT7_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR7
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR7_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR7_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR7
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR7_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR7_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT7
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT7_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT7_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CSRL0 register.
//
//*****************************************************************************
#define USB_CSRL0_NAKTO         0x00000080  // NAK Timeout
#define USB_CSRL0_SETENDC       0x00000080  // Setup End Clear
#define USB_CSRL0_STATUS        0x00000040  // STATUS Packet
#define USB_CSRL0_RXRDYC        0x00000040  // RXRDY Clear
#define USB_CSRL0_REQPKT        0x00000020  // Request Packet
#define USB_CSRL0_STALL         0x00000020  // Send Stall
#define USB_CSRL0_SETEND        0x00000010  // Setup End
#define USB_CSRL0_ERROR         0x00000010  // Error
#define USB_CSRL0_DATAEND       0x00000008  // Data End
#define USB_CSRL0_SETUP         0x00000008  // Setup Packet
#define USB_CSRL0_STALLED       0x00000004  // Endpoint Stalled
#define USB_CSRL0_TXRDY         0x00000002  // Transmit Packet Ready
#define USB_CSRL0_RXRDY         0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CSRH0 register.
//
//*****************************************************************************
#define USB_CSRH0_DISPING       0x00000008  // PING Disable
#define USB_CSRH0_DTWE          0x00000004  // Data Toggle Write Enable
#define USB_CSRH0_DT            0x00000002  // Data Toggle
#define USB_CSRH0_FLUSH         0x00000001  // Flush FIFO

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_COUNT0 register.
//
//*****************************************************************************
#define USB_COUNT0_COUNT_M      0x0000007F  // FIFO Count
#define USB_COUNT0_COUNT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TYPE0 register.
//
//*****************************************************************************
#define USB_TYPE0_SPEED_M       0x000000C0  // Operating Speed
#define USB_TYPE0_SPEED_HIGH    0x00000040  // High
#define USB_TYPE0_SPEED_FULL    0x00000080  // Full
#define USB_TYPE0_SPEED_LOW     0x000000C0  // Low

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_NAKLMT register.
//
//*****************************************************************************
#define USB_NAKLMT_NAKLMT_M     0x0000001F  // EP0 NAK Limit
#define USB_NAKLMT_NAKLMT_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP1 register.
//
//*****************************************************************************
#define USB_TXMAXP1_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP1_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL1 register.
//
//*****************************************************************************
#define USB_TXCSRL1_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL1_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL1_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL1_STALL       0x00000010  // Send STALL
#define USB_TXCSRL1_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL1_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL1_ERROR       0x00000004  // Error
#define USB_TXCSRL1_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL1_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL1_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH1 register.
//
//*****************************************************************************
#define USB_TXCSRH1_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH1_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH1_MODE        0x00000020  // Mode
#define USB_TXCSRH1_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH1_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH1_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH1_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH1_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP1 register.
//
//*****************************************************************************
#define USB_RXMAXP1_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP1_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL1 register.
//
//*****************************************************************************
#define USB_RXCSRL1_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL1_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL1_STALL       0x00000020  // Send STALL
#define USB_RXCSRL1_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL1_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL1_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL1_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL1_OVER        0x00000004  // Overrun
#define USB_RXCSRL1_ERROR       0x00000004  // Error
#define USB_RXCSRL1_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL1_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH1 register.
//
//*****************************************************************************
#define USB_RXCSRH1_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH1_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH1_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH1_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH1_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH1_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH1_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH1_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH1_DT          0x00000002  // Data Toggle
#define USB_RXCSRH1_INCOMPRX    0x00000001  // Incomplete RX Transmission
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT1 register.
//
//*****************************************************************************
#define USB_RXCOUNT1_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT1_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE1 register.
//
//*****************************************************************************
#define USB_TXTYPE1_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE1_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE1_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE1_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE1_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE1_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE1_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE1_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE1_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE1_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE1_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE1_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL1
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL1_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL1_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL1_TXPOLL_S                                              \
                                0
#define USB_TXINTERVAL1_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE1 register.
//
//*****************************************************************************
#define USB_RXTYPE1_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE1_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE1_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE1_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE1_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE1_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE1_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE1_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE1_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE1_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE1_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE1_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL1
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL1_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL1_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL1_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL1_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP2 register.
//
//*****************************************************************************
#define USB_TXMAXP2_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP2_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL2 register.
//
//*****************************************************************************
#define USB_TXCSRL2_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL2_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL2_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL2_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL2_STALL       0x00000010  // Send STALL
#define USB_TXCSRL2_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL2_ERROR       0x00000004  // Error
#define USB_TXCSRL2_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL2_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL2_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH2 register.
//
//*****************************************************************************
#define USB_TXCSRH2_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH2_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH2_MODE        0x00000020  // Mode
#define USB_TXCSRH2_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH2_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH2_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH2_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH2_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP2 register.
//
//*****************************************************************************
#define USB_RXMAXP2_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP2_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL2 register.
//
//*****************************************************************************
#define USB_RXCSRL2_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL2_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL2_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL2_STALL       0x00000020  // Send STALL
#define USB_RXCSRL2_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL2_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL2_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL2_ERROR       0x00000004  // Error
#define USB_RXCSRL2_OVER        0x00000004  // Overrun
#define USB_RXCSRL2_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL2_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH2 register.
//
//*****************************************************************************
#define USB_RXCSRH2_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH2_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH2_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH2_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH2_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH2_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH2_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH2_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH2_DT          0x00000002  // Data Toggle
#define USB_RXCSRH2_INCOMPRX    0x00000001  // Incomplete RX Transmission
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT2 register.
//
//*****************************************************************************
#define USB_RXCOUNT2_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT2_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE2 register.
//
//*****************************************************************************
#define USB_TXTYPE2_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE2_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE2_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE2_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE2_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE2_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE2_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE2_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE2_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE2_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE2_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE2_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL2
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL2_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL2_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL2_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL2_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE2 register.
//
//*****************************************************************************
#define USB_RXTYPE2_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE2_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE2_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE2_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE2_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE2_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE2_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE2_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE2_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE2_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE2_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE2_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL2
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL2_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL2_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL2_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL2_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP3 register.
//
//*****************************************************************************
#define USB_TXMAXP3_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP3_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL3 register.
//
//*****************************************************************************
#define USB_TXCSRL3_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL3_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL3_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL3_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL3_STALL       0x00000010  // Send STALL
#define USB_TXCSRL3_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL3_ERROR       0x00000004  // Error
#define USB_TXCSRL3_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL3_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL3_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH3 register.
//
//*****************************************************************************
#define USB_TXCSRH3_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH3_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH3_MODE        0x00000020  // Mode
#define USB_TXCSRH3_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH3_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH3_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH3_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH3_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP3 register.
//
//*****************************************************************************
#define USB_RXMAXP3_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP3_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL3 register.
//
//*****************************************************************************
#define USB_RXCSRL3_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL3_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL3_STALL       0x00000020  // Send STALL
#define USB_RXCSRL3_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL3_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL3_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL3_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL3_ERROR       0x00000004  // Error
#define USB_RXCSRL3_OVER        0x00000004  // Overrun
#define USB_RXCSRL3_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL3_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH3 register.
//
//*****************************************************************************
#define USB_RXCSRH3_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH3_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH3_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH3_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH3_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH3_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH3_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH3_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH3_DT          0x00000002  // Data Toggle
#define USB_RXCSRH3_INCOMPRX    0x00000001  // Incomplete RX Transmission
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT3 register.
//
//*****************************************************************************
#define USB_RXCOUNT3_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT3_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE3 register.
//
//*****************************************************************************
#define USB_TXTYPE3_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE3_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE3_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE3_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE3_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE3_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE3_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE3_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE3_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE3_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE3_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE3_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL3
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL3_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL3_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL3_TXPOLL_S                                              \
                                0
#define USB_TXINTERVAL3_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE3 register.
//
//*****************************************************************************
#define USB_RXTYPE3_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE3_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE3_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE3_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE3_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE3_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE3_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE3_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE3_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE3_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE3_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE3_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL3
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL3_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL3_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL3_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL3_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP4 register.
//
//*****************************************************************************
#define USB_TXMAXP4_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP4_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL4 register.
//
//*****************************************************************************
#define USB_TXCSRL4_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL4_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL4_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL4_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL4_STALL       0x00000010  // Send STALL
#define USB_TXCSRL4_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL4_ERROR       0x00000004  // Error
#define USB_TXCSRL4_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL4_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL4_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH4 register.
//
//*****************************************************************************
#define USB_TXCSRH4_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH4_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH4_MODE        0x00000020  // Mode
#define USB_TXCSRH4_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH4_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH4_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH4_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH4_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP4 register.
//
//*****************************************************************************
#define USB_RXMAXP4_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP4_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL4 register.
//
//*****************************************************************************
#define USB_RXCSRL4_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL4_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL4_STALL       0x00000020  // Send STALL
#define USB_RXCSRL4_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL4_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL4_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL4_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL4_OVER        0x00000004  // Overrun
#define USB_RXCSRL4_ERROR       0x00000004  // Error
#define USB_RXCSRL4_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL4_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH4 register.
//
//*****************************************************************************
#define USB_RXCSRH4_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH4_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH4_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH4_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH4_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH4_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH4_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH4_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH4_DT          0x00000002  // Data Toggle
#define USB_RXCSRH4_INCOMPRX    0x00000001  // Incomplete RX Transmission
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT4 register.
//
//*****************************************************************************
#define USB_RXCOUNT4_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT4_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE4 register.
//
//*****************************************************************************
#define USB_TXTYPE4_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE4_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE4_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE4_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE4_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE4_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE4_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE4_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE4_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE4_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE4_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE4_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL4
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL4_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL4_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL4_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL4_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE4 register.
//
//*****************************************************************************
#define USB_RXTYPE4_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE4_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE4_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE4_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE4_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE4_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE4_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE4_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE4_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE4_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE4_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE4_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL4
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL4_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL4_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL4_NAKLMT_S                                              \
                                0
#define USB_RXINTERVAL4_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP5 register.
//
//*****************************************************************************
#define USB_TXMAXP5_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP5_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL5 register.
//
//*****************************************************************************
#define USB_TXCSRL5_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL5_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL5_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL5_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL5_STALL       0x00000010  // Send STALL
#define USB_TXCSRL5_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL5_ERROR       0x00000004  // Error
#define USB_TXCSRL5_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL5_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL5_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH5 register.
//
//*****************************************************************************
#define USB_TXCSRH5_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH5_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH5_MODE        0x00000020  // Mode
#define USB_TXCSRH5_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH5_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH5_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH5_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH5_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP5 register.
//
//*****************************************************************************
#define USB_RXMAXP5_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP5_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL5 register.
//
//*****************************************************************************
#define USB_RXCSRL5_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL5_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL5_STALL       0x00000020  // Send STALL
#define USB_RXCSRL5_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL5_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL5_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL5_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL5_ERROR       0x00000004  // Error
#define USB_RXCSRL5_OVER        0x00000004  // Overrun
#define USB_RXCSRL5_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL5_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH5 register.
//
//*****************************************************************************
#define USB_RXCSRH5_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH5_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH5_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH5_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH5_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH5_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH5_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH5_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH5_DT          0x00000002  // Data Toggle
#define USB_RXCSRH5_INCOMPRX    0x00000001  // Incomplete RX Transmission
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT5 register.
//
//*****************************************************************************
#define USB_RXCOUNT5_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT5_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE5 register.
//
//*****************************************************************************
#define USB_TXTYPE5_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE5_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE5_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE5_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE5_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE5_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE5_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE5_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE5_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE5_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE5_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE5_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL5
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL5_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL5_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL5_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL5_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE5 register.
//
//*****************************************************************************
#define USB_RXTYPE5_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE5_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE5_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE5_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE5_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE5_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE5_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE5_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE5_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE5_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE5_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE5_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL5
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL5_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL5_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL5_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL5_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP6 register.
//
//*****************************************************************************
#define USB_TXMAXP6_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP6_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL6 register.
//
//*****************************************************************************
#define USB_TXCSRL6_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL6_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL6_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL6_STALL       0x00000010  // Send STALL
#define USB_TXCSRL6_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL6_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL6_ERROR       0x00000004  // Error
#define USB_TXCSRL6_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL6_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL6_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH6 register.
//
//*****************************************************************************
#define USB_TXCSRH6_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH6_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH6_MODE        0x00000020  // Mode
#define USB_TXCSRH6_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH6_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH6_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH6_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH6_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP6 register.
//
//*****************************************************************************
#define USB_RXMAXP6_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP6_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL6 register.
//
//*****************************************************************************
#define USB_RXCSRL6_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL6_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL6_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL6_STALL       0x00000020  // Send STALL
#define USB_RXCSRL6_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL6_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL6_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL6_ERROR       0x00000004  // Error
#define USB_RXCSRL6_OVER        0x00000004  // Overrun
#define USB_RXCSRL6_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL6_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH6 register.
//
//*****************************************************************************
#define USB_RXCSRH6_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH6_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH6_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH6_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH6_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH6_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH6_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH6_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH6_DT          0x00000002  // Data Toggle
#define USB_RXCSRH6_INCOMPRX    0x00000001  // Incomplete RX Transmission
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT6 register.
//
//*****************************************************************************
#define USB_RXCOUNT6_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT6_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE6 register.
//
//*****************************************************************************
#define USB_TXTYPE6_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE6_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE6_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE6_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE6_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE6_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE6_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE6_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE6_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE6_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE6_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE6_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL6
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL6_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL6_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL6_TXPOLL_S                                              \
                                0
#define USB_TXINTERVAL6_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE6 register.
//
//*****************************************************************************
#define USB_RXTYPE6_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE6_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE6_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE6_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE6_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE6_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE6_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE6_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE6_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE6_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE6_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE6_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL6
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL6_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL6_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL6_NAKLMT_S                                              \
                                0
#define USB_RXINTERVAL6_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP7 register.
//
//*****************************************************************************
#define USB_TXMAXP7_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP7_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL7 register.
//
//*****************************************************************************
#define USB_TXCSRL7_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL7_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL7_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL7_STALL       0x00000010  // Send STALL
#define USB_TXCSRL7_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL7_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL7_ERROR       0x00000004  // Error
#define USB_TXCSRL7_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL7_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL7_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH7 register.
//
//*****************************************************************************
#define USB_TXCSRH7_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH7_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH7_MODE        0x00000020  // Mode
#define USB_TXCSRH7_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH7_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH7_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH7_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH7_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP7 register.
//
//*****************************************************************************
#define USB_RXMAXP7_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP7_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL7 register.
//
//*****************************************************************************
#define USB_RXCSRL7_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL7_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL7_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL7_STALL       0x00000020  // Send STALL
#define USB_RXCSRL7_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL7_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL7_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL7_ERROR       0x00000004  // Error
#define USB_RXCSRL7_OVER        0x00000004  // Overrun
#define USB_RXCSRL7_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL7_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH7 register.
//
//*****************************************************************************
#define USB_RXCSRH7_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH7_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH7_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH7_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH7_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH7_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH7_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH7_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH7_DT          0x00000002  // Data Toggle
#define USB_RXCSRH7_INCOMPRX    0x00000001  // Incomplete RX Transmission
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT7 register.
//
//*****************************************************************************
#define USB_RXCOUNT7_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT7_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE7 register.
//
//*****************************************************************************
#define USB_TXTYPE7_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE7_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE7_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE7_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE7_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE7_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE7_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE7_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE7_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE7_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE7_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE7_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL7
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL7_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL7_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL7_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL7_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE7 register.
//
//*****************************************************************************
#define USB_RXTYPE7_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE7_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE7_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE7_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE7_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE7_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE7_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE7_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE7_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE7_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE7_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE7_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL7
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL7_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL7_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL7_NAKLMT_S                                              \
                                0
#define USB_RXINTERVAL7_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAINTR register.
//
//*****************************************************************************
#define USB_DMAINTR_CH7         0x00000080  // Channel 7 DMA Interrupt
#define USB_DMAINTR_CH6         0x00000040  // Channel 6 DMA Interrupt
#define USB_DMAINTR_CH5         0x00000020  // Channel 5 DMA Interrupt
#define USB_DMAINTR_CH4         0x00000010  // Channel 4 DMA Interrupt
#define USB_DMAINTR_CH3         0x00000008  // Channel 3 DMA Interrupt
#define USB_DMAINTR_CH2         0x00000004  // Channel 2 DMA Interrupt
#define USB_DMAINTR_CH1         0x00000002  // Channel 1 DMA Interrupt
#define USB_DMAINTR_CH0         0x00000001  // Channel 0 DMA Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL0 register.
//
//*****************************************************************************
#define USB_DMACTL0_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL0_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL0_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL0_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL0_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL0_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL0_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL0_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL0_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL0_DIR         0x00000002  // DMA Direction
#define USB_DMACTL0_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL0_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR0 register.
//
//*****************************************************************************
#define USB_DMAADDR0_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR0_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT0
// register.
//
//*****************************************************************************
#define USB_DMACOUNT0_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT0_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL1 register.
//
//*****************************************************************************
#define USB_DMACTL1_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL1_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL1_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL1_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL1_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL1_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL1_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL1_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL1_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL1_DIR         0x00000002  // DMA Direction
#define USB_DMACTL1_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL1_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR1 register.
//
//*****************************************************************************
#define USB_DMAADDR1_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR1_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT1
// register.
//
//*****************************************************************************
#define USB_DMACOUNT1_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT1_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL2 register.
//
//*****************************************************************************
#define USB_DMACTL2_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL2_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL2_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL2_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL2_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL2_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL2_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL2_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL2_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL2_DIR         0x00000002  // DMA Direction
#define USB_DMACTL2_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL2_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR2 register.
//
//*****************************************************************************
#define USB_DMAADDR2_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR2_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT2
// register.
//
//*****************************************************************************
#define USB_DMACOUNT2_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT2_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL3 register.
//
//*****************************************************************************
#define USB_DMACTL3_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL3_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL3_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL3_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL3_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL3_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL3_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL3_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL3_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL3_DIR         0x00000002  // DMA Direction
#define USB_DMACTL3_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL3_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR3 register.
//
//*****************************************************************************
#define USB_DMAADDR3_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR3_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT3
// register.
//
//*****************************************************************************
#define USB_DMACOUNT3_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT3_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL4 register.
//
//*****************************************************************************
#define USB_DMACTL4_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL4_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL4_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL4_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL4_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL4_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL4_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL4_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL4_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL4_DIR         0x00000002  // DMA Direction
#define USB_DMACTL4_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL4_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR4 register.
//
//*****************************************************************************
#define USB_DMAADDR4_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR4_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT4
// register.
//
//*****************************************************************************
#define USB_DMACOUNT4_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT4_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL5 register.
//
//*****************************************************************************
#define USB_DMACTL5_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL5_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL5_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL5_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL5_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL5_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL5_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL5_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL5_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL5_DIR         0x00000002  // DMA Direction
#define USB_DMACTL5_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL5_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR5 register.
//
//*****************************************************************************
#define USB_DMAADDR5_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR5_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT5
// register.
//
//*****************************************************************************
#define USB_DMACOUNT5_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT5_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL6 register.
//
//*****************************************************************************
#define USB_DMACTL6_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL6_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL6_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL6_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL6_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL6_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL6_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL6_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL6_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL6_DIR         0x00000002  // DMA Direction
#define USB_DMACTL6_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL6_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR6 register.
//
//*****************************************************************************
#define USB_DMAADDR6_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR6_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT6
// register.
//
//*****************************************************************************
#define USB_DMACOUNT6_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT6_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL7 register.
//
//*****************************************************************************
#define USB_DMACTL7_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL7_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL7_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL7_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
                                            // length
#define USB_DMACTL7_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
                                            // unspecified length
#define USB_DMACTL7_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL7_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL7_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL7_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL7_DIR         0x00000002  // DMA Direction
#define USB_DMACTL7_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL7_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR7 register.
//
//*****************************************************************************
#define USB_DMAADDR7_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR7_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT7
// register.
//
//*****************************************************************************
#define USB_DMACOUNT7_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT7_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT1
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT1_M       0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT1_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT2
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT2_M       0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT2_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT3
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT3_M       0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT3_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT4
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT4_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT4_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT5
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT5_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT5_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT6
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT6_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT6_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT7
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT7_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT7_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXDPKTBUFDIS
// register.
//
//*****************************************************************************
#define USB_RXDPKTBUFDIS_EP7    0x00000080  // EP7 RX Double-Packet Buffer
                                            // Disable
#define USB_RXDPKTBUFDIS_EP6    0x00000040  // EP6 RX Double-Packet Buffer
                                            // Disable
#define USB_RXDPKTBUFDIS_EP5    0x00000020  // EP5 RX Double-Packet Buffer
                                            // Disable
#define USB_RXDPKTBUFDIS_EP4    0x00000010  // EP4 RX Double-Packet Buffer
                                            // Disable
#define USB_RXDPKTBUFDIS_EP3    0x00000008  // EP3 RX Double-Packet Buffer
                                            // Disable
#define USB_RXDPKTBUFDIS_EP2    0x00000004  // EP2 RX Double-Packet Buffer
                                            // Disable
#define USB_RXDPKTBUFDIS_EP1    0x00000002  // EP1 RX Double-Packet Buffer
                                            // Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXDPKTBUFDIS
// register.
//
//*****************************************************************************
#define USB_TXDPKTBUFDIS_EP7    0x00000080  // EP7 TX Double-Packet Buffer
                                            // Disable
#define USB_TXDPKTBUFDIS_EP6    0x00000040  // EP6 TX Double-Packet Buffer
                                            // Disable
#define USB_TXDPKTBUFDIS_EP5    0x00000020  // EP5 TX Double-Packet Buffer
                                            // Disable
#define USB_TXDPKTBUFDIS_EP4    0x00000010  // EP4 TX Double-Packet Buffer
                                            // Disable
#define USB_TXDPKTBUFDIS_EP3    0x00000008  // EP3 TX Double-Packet Buffer
                                            // Disable
#define USB_TXDPKTBUFDIS_EP2    0x00000004  // EP2 TX Double-Packet Buffer
                                            // Disable
#define USB_TXDPKTBUFDIS_EP1    0x00000002  // EP1 TX Double-Packet Buffer
                                            // Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CTO register.
//
//*****************************************************************************
#define USB_CTO_CCTV_M          0x0000FFFF  // Configurable Chirp Timeout Value
#define USB_CTO_CCTV_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_HHSRTN register.
//
//*****************************************************************************
#define USB_HHSRTN_HHSRTN_M     0x0000FFFF  // HIgh Speed to UTM Operating
                                            // Delay
#define USB_HHSRTN_HHSRTN_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_HSBT register.
//
//*****************************************************************************
#define USB_HSBT_HSBT_M         0x0000000F  // High Speed Timeout Adder
#define USB_HSBT_HSBT_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMATTR register.
//
//*****************************************************************************
#define USB_LPMATTR_ENDPT_M     0x0000F000  // Endpoint
#define USB_LPMATTR_RMTWAK      0x00000100  // Remote Wake
#define USB_LPMATTR_HIRD_M      0x000000F0  // Host Initiated Resume Duration
#define USB_LPMATTR_LS_M        0x0000000F  // Link State
#define USB_LPMATTR_LS_L1       0x00000001  // Sleep State (L1)
#define USB_LPMATTR_ENDPT_S     12
#define USB_LPMATTR_HIRD_S      4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMCNTRL register.
//
//*****************************************************************************
#define USB_LPMCNTRL_NAK        0x00000010  // LPM NAK
#define USB_LPMCNTRL_EN_M       0x0000000C  // LPM Enable
#define USB_LPMCNTRL_EN_NONE    0x00000000  // LPM and Extended transactions
                                            // are not supported. In this case,
                                            // the USB does not respond to LPM
                                            // transactions and LPM
                                            // transactions cause a timeout
#define USB_LPMCNTRL_EN_EXT     0x00000004  // LPM is not supported but
                                            // extended transactions are
                                            // supported. In this case, the USB
                                            // does respond to an LPM
                                            // transaction with a STALL
#define USB_LPMCNTRL_EN_LPMEXT  0x0000000C  // The USB supports LPM extended
                                            // transactions. In this case, the
                                            // USB responds with a NYET or an
                                            // ACK as determined by the value
                                            // of TXLPM and other conditions
#define USB_LPMCNTRL_RES        0x00000002  // LPM Resume
#define USB_LPMCNTRL_TXLPM      0x00000001  // Transmit LPM Transaction Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMIM register.
//
//*****************************************************************************
#define USB_LPMIM_ERR           0x00000020  // LPM Error Interrupt Mask
#define USB_LPMIM_RES           0x00000010  // LPM Resume Interrupt Mask
#define USB_LPMIM_NC            0x00000008  // LPM NC Interrupt Mask
#define USB_LPMIM_ACK           0x00000004  // LPM ACK Interrupt Mask
#define USB_LPMIM_NY            0x00000002  // LPM NY Interrupt Mask
#define USB_LPMIM_STALL         0x00000001  // LPM STALL Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMRIS register.
//
//*****************************************************************************
#define USB_LPMRIS_ERR          0x00000020  // LPM Interrupt Status
#define USB_LPMRIS_RES          0x00000010  // LPM Resume Interrupt Status
#define USB_LPMRIS_NC           0x00000008  // LPM NC Interrupt Status
#define USB_LPMRIS_ACK          0x00000004  // LPM ACK Interrupt Status
#define USB_LPMRIS_NY           0x00000002  // LPM NY Interrupt Status
#define USB_LPMRIS_LPMST        0x00000001  // LPM STALL Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMFADDR register.
//
//*****************************************************************************
#define USB_LPMFADDR_ADDR_M     0x0000007F  // LPM Function Address
#define USB_LPMFADDR_ADDR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPC register.
//
//*****************************************************************************
#define USB_EPC_PFLTACT_M       0x00000300  // Power Fault Action
#define USB_EPC_PFLTACT_UNCHG   0x00000000  // Unchanged
#define USB_EPC_PFLTACT_TRIS    0x00000100  // Tristate
#define USB_EPC_PFLTACT_LOW     0x00000200  // Low
#define USB_EPC_PFLTACT_HIGH    0x00000300  // High
#define USB_EPC_PFLTAEN         0x00000040  // Power Fault Action Enable
#define USB_EPC_PFLTSEN_HIGH    0x00000020  // Power Fault Sense
#define USB_EPC_PFLTEN          0x00000010  // Power Fault Input Enable
#define USB_EPC_EPENDE          0x00000004  // EPEN Drive Enable
#define USB_EPC_EPEN_M          0x00000003  // External Power Supply Enable
                                            // Configuration
#define USB_EPC_EPEN_LOW        0x00000000  // Power Enable Active Low
#define USB_EPC_EPEN_HIGH       0x00000001  // Power Enable Active High
#define USB_EPC_EPEN_VBLOW      0x00000002  // Power Enable High if VBUS Low
                                            // (OTG only)
#define USB_EPC_EPEN_VBHIGH     0x00000003  // Power Enable High if VBUS High
                                            // (OTG only)

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPCRIS register.
//
//*****************************************************************************
#define USB_EPCRIS_PF           0x00000001  // USB Power Fault Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPCIM register.
//
//*****************************************************************************
#define USB_EPCIM_PF            0x00000001  // USB Power Fault Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPCISC register.
//
//*****************************************************************************
#define USB_EPCISC_PF           0x00000001  // USB Power Fault Interrupt Status
                                            // and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DRRIS register.
//
//*****************************************************************************
#define USB_DRRIS_RESUME        0x00000001  // RESUME Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DRIM register.
//
//*****************************************************************************
#define USB_DRIM_RESUME         0x00000001  // RESUME Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DRISC register.
//
//*****************************************************************************
#define USB_DRISC_RESUME        0x00000001  // RESUME Interrupt Status and
                                            // Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_GPCS register.
//
//*****************************************************************************
#define USB_GPCS_DEVMOD_M       0x00000007  // Device Mode
#define USB_GPCS_DEVMOD_OTG     0x00000000  // Use USB0VBUS and USB0ID pin
#define USB_GPCS_DEVMOD_HOST    0x00000002  // Force USB0VBUS and USB0ID low
#define USB_GPCS_DEVMOD_DEV     0x00000003  // Force USB0VBUS and USB0ID high
#define USB_GPCS_DEVMOD_HOSTVBUS                                              \
                                0x00000004  // Use USB0VBUS and force USB0ID
                                            // low
#define USB_GPCS_DEVMOD_DEVVBUS 0x00000005  // Use USB0VBUS and force USB0ID
                                            // high
#define USB_GPCS_DEVMODOTG      0x00000002  // Enable Device Mode
#define USB_GPCS_DEVMOD         0x00000001  // Device Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDC register.
//
//*****************************************************************************
#define USB_VDC_VBDEN           0x00000001  // VBUS Droop Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDCRIS register.
//
//*****************************************************************************
#define USB_VDCRIS_VD           0x00000001  // VBUS Droop Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDCIM register.
//
//*****************************************************************************
#define USB_VDCIM_VD            0x00000001  // VBUS Droop Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDCISC register.
//
//*****************************************************************************
#define USB_VDCISC_VD           0x00000001  // VBUS Droop Interrupt Status and
                                            // Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_IDVRIS register.
//
//*****************************************************************************
#define USB_IDVRIS_ID           0x00000001  // ID Valid Detect Raw Interrupt
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_IDVIM register.
//
//*****************************************************************************
#define USB_IDVIM_ID            0x00000001  // ID Valid Detect Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_IDVISC register.
//
//*****************************************************************************
#define USB_IDVISC_ID           0x00000001  // ID Valid Detect Interrupt Status
                                            // and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_PP register.
//
//*****************************************************************************
#define USB_PP_ECNT_M           0x0000FF00  // Endpoint Count
#define USB_PP_USB_M            0x000000C0  // USB Capability
#define USB_PP_USB_DEVICE       0x00000040  // DEVICE
#define USB_PP_USB_HOSTDEVICE   0x00000080  // HOST
#define USB_PP_USB_OTG          0x000000C0  // OTG
#define USB_PP_ULPI             0x00000020  // ULPI Present
#define USB_PP_PHY              0x00000010  // PHY Present

#define USB_PP_ECNT_S           8

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_PC register.
//
//*****************************************************************************
#define USB_PC_ULPIEN           0x00010000  // ULPI Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CC register.
//
//*****************************************************************************
#define USB_CC_CLKEN            0x00000200  // USB Clock Enable
#define USB_CC_CSD              0x00000100  // Clock Source/Direction
#define USB_CC_CLKDIV_M         0x0000000F  // PLL Clock Divisor
#define USB_CC_CLKDIV_S         0


//*****************************************************************************
//
// The following are values that can be passed to USBIntEnableControl() and
// USBIntDisableControl() as the ui32Flags parameter, and are returned from
// USBIntStatusControl().
//
//*****************************************************************************
#define USB_INTCTRL_ALL         0x000003FF  // All control interrupt sources
#define USB_INTCTRL_STATUS      0x000000FF  // Status Interrupts
#define USB_INTCTRL_VBUS_ERR    0x00000080  // VBUS Error
#define USB_INTCTRL_SESSION     0x00000040  // Session Start Detected
#define USB_INTCTRL_SESSION_END 0x00000040  // Session End Detected
#define USB_INTCTRL_DISCONNECT  0x00000020  // Disconnect Detected
#define USB_INTCTRL_CONNECT     0x00000010  // Device Connect Detected
#define USB_INTCTRL_SOF         0x00000008  // Start of Frame Detected
#define USB_INTCTRL_BABBLE      0x00000004  // Babble signaled
#define USB_INTCTRL_RESET       0x00000004  // Reset signaled
#define USB_INTCTRL_RESUME      0x00000002  // Resume detected
#define USB_INTCTRL_SUSPEND     0x00000001  // Suspend detected
#define USB_INTCTRL_MODE_DETECT 0x00000200  // Mode value valid
#define USB_INTCTRL_POWER_FAULT 0x00000100  // Power Fault detected

//*****************************************************************************
//
// The following are values that can be passed to USBIntEnableEndpoint() and
// USBIntDisableEndpoint() as the ui32Flags parameter, and are returned from
// USBIntStatusEndpoint().
//
//*****************************************************************************
#define USB_INTEP_ALL           0xFFFFFFFF  // Host IN Interrupts
#define USB_INTEP_HOST_IN       0xFFFE0000  // Host IN Interrupts
#define USB_INTEP_HOST_IN_15    0x80000000  // Endpoint 15 Host IN Interrupt
#define USB_INTEP_HOST_IN_14    0x40000000  // Endpoint 14 Host IN Interrupt
#define USB_INTEP_HOST_IN_13    0x20000000  // Endpoint 13 Host IN Interrupt
#define USB_INTEP_HOST_IN_12    0x10000000  // Endpoint 12 Host IN Interrupt
#define USB_INTEP_HOST_IN_11    0x08000000  // Endpoint 11 Host IN Interrupt
#define USB_INTEP_HOST_IN_10    0x04000000  // Endpoint 10 Host IN Interrupt
#define USB_INTEP_HOST_IN_9     0x02000000  // Endpoint 9 Host IN Interrupt
#define USB_INTEP_HOST_IN_8     0x01000000  // Endpoint 8 Host IN Interrupt
#define USB_INTEP_HOST_IN_7     0x00800000  // Endpoint 7 Host IN Interrupt
#define USB_INTEP_HOST_IN_6     0x00400000  // Endpoint 6 Host IN Interrupt
#define USB_INTEP_HOST_IN_5     0x00200000  // Endpoint 5 Host IN Interrupt
#define USB_INTEP_HOST_IN_4     0x00100000  // Endpoint 4 Host IN Interrupt
#define USB_INTEP_HOST_IN_3     0x00080000  // Endpoint 3 Host IN Interrupt
#define USB_INTEP_HOST_IN_2     0x00040000  // Endpoint 2 Host IN Interrupt
#define USB_INTEP_HOST_IN_1     0x00020000  // Endpoint 1 Host IN Interrupt

#define USB_INTEP_DEV_OUT       0xFFFE0000  // Device OUT Interrupts
#define USB_INTEP_DEV_OUT_15    0x80000000  // Endpoint 15 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_14    0x40000000  // Endpoint 14 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_13    0x20000000  // Endpoint 13 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_12    0x10000000  // Endpoint 12 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_11    0x08000000  // Endpoint 11 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_10    0x04000000  // Endpoint 10 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_9     0x02000000  // Endpoint 9 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_8     0x01000000  // Endpoint 8 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_7     0x00800000  // Endpoint 7 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_6     0x00400000  // Endpoint 6 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_5     0x00200000  // Endpoint 5 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_4     0x00100000  // Endpoint 4 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_3     0x00080000  // Endpoint 3 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_2     0x00040000  // Endpoint 2 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_1     0x00020000  // Endpoint 1 Device OUT Interrupt

#define USB_INTEP_HOST_OUT      0x0000FFFE  // Host OUT Interrupts
#define USB_INTEP_HOST_OUT_15   0x00008000  // Endpoint 15 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_14   0x00004000  // Endpoint 14 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_13   0x00002000  // Endpoint 13 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_12   0x00001000  // Endpoint 12 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_11   0x00000800  // Endpoint 11 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_10   0x00000400  // Endpoint 10 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_9    0x00000200  // Endpoint 9 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_8    0x00000100  // Endpoint 8 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_7    0x00000080  // Endpoint 7 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_6    0x00000040  // Endpoint 6 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_5    0x00000020  // Endpoint 5 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_4    0x00000010  // Endpoint 4 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_3    0x00000008  // Endpoint 3 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_2    0x00000004  // Endpoint 2 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_1    0x00000002  // Endpoint 1 Host OUT Interrupt

#define USB_INTEP_DEV_IN        0x0000FFFE  // Device IN Interrupts
#define USB_INTEP_DEV_IN_15     0x00008000  // Endpoint 15 Device IN Interrupt
#define USB_INTEP_DEV_IN_14     0x00004000  // Endpoint 14 Device IN Interrupt
#define USB_INTEP_DEV_IN_13     0x00002000  // Endpoint 13 Device IN Interrupt
#define USB_INTEP_DEV_IN_12     0x00001000  // Endpoint 12 Device IN Interrupt
#define USB_INTEP_DEV_IN_11     0x00000800  // Endpoint 11 Device IN Interrupt
#define USB_INTEP_DEV_IN_10     0x00000400  // Endpoint 10 Device IN Interrupt
#define USB_INTEP_DEV_IN_9      0x00000200  // Endpoint 9 Device IN Interrupt
#define USB_INTEP_DEV_IN_8      0x00000100  // Endpoint 8 Device IN Interrupt
#define USB_INTEP_DEV_IN_7      0x00000080  // Endpoint 7 Device IN Interrupt
#define USB_INTEP_DEV_IN_6      0x00000040  // Endpoint 6 Device IN Interrupt
#define USB_INTEP_DEV_IN_5      0x00000020  // Endpoint 5 Device IN Interrupt
#define USB_INTEP_DEV_IN_4      0x00000010  // Endpoint 4 Device IN Interrupt
#define USB_INTEP_DEV_IN_3      0x00000008  // Endpoint 3 Device IN Interrupt
#define USB_INTEP_DEV_IN_2      0x00000004  // Endpoint 2 Device IN Interrupt
#define USB_INTEP_DEV_IN_1      0x00000002  // Endpoint 1 Device IN Interrupt

#define USB_INTEP_0             0x00000001  // Endpoint 0 Interrupt

//*****************************************************************************
//
// The following are values that are returned from USBSpeedGet().
//
//*****************************************************************************
#define USB_UNDEF_SPEED         0x80000000  // Current speed is undefined
#define USB_HIGH_SPEED          0x00000002  // Current speed is High Speed
#define USB_FULL_SPEED          0x00000001  // Current speed is Full Speed
#define USB_LOW_SPEED           0x00000000  // Current speed is Low Speed

//*****************************************************************************
//
// The following are values that are returned from USBEndpointStatus().  The
// USB_HOST_* values are used when the USB controller is in host mode and the
// USB_DEV_* values are used when the USB controller is in device mode.
//
//*****************************************************************************
#define USB_HOST_IN_STATUS      0x114F0000  // Mask of all host IN interrupts
#define USB_HOST_IN_PID_ERROR   0x10000000  // Stall on this endpoint received
#define USB_HOST_IN_NOT_COMP    0x01000000  // Device failed to respond
#define USB_HOST_IN_STALL       0x00400000  // Stall on this endpoint received
#define USB_HOST_IN_DATA_ERROR  0x00080000  // CRC or bit-stuff error
                                            // (ISOC Mode)
#define USB_HOST_IN_NAK_TO      0x00080000  // NAK received for more than the
                                            // specified timeout period
#define USB_HOST_IN_ERROR       0x00040000  // Failed to communicate with a
                                            // device
#define USB_HOST_IN_FIFO_FULL   0x00020000  // RX FIFO full
#define USB_HOST_IN_PKTRDY      0x00010000  // Data packet ready
#define USB_HOST_OUT_STATUS     0x000000A7  // Mask of all host OUT interrupts
#define USB_HOST_OUT_NAK_TO     0x00000080  // NAK received for more than the
                                            // specified timeout period
#define USB_HOST_OUT_NOT_COMP   0x00000080  // No response from device
                                            // (ISOC mode)
#define USB_HOST_OUT_STALL      0x00000020  // Stall on this endpoint received
#define USB_HOST_OUT_ERROR      0x00000004  // Failed to communicate with a
                                            // device
#define USB_HOST_OUT_FIFO_NE    0x00000002  // TX FIFO is not empty
#define USB_HOST_OUT_PKTPEND    0x00000001  // Transmit still being transmitted
#define USB_HOST_EP0_NAK_TO     0x00000080  // NAK received for more than the
                                            // specified timeout period
#define USB_HOST_EP0_STATUS     0x00000040  // This was a status packet
#define USB_HOST_EP0_ERROR      0x00000010  // Failed to communicate with a
                                            // device
#define USB_HOST_EP0_RX_STALL   0x00000004  // Stall on this endpoint received
#define USB_HOST_EP0_RXPKTRDY   0x00000001  // Receive data packet ready
#define USB_DEV_RX_PID_ERROR    0x01000000  // PID error in isochronous
                                            // transfer
#define USB_DEV_RX_SENT_STALL   0x00400000  // Stall was sent on this endpoint
#define USB_DEV_RX_DATA_ERROR   0x00080000  // CRC error on the data
#define USB_DEV_RX_OVERRUN      0x00040000  // OUT packet was not loaded due to
                                            // a full FIFO
#define USB_DEV_RX_FIFO_FULL    0x00020000  // RX FIFO full
#define USB_DEV_RX_PKT_RDY      0x00010000  // Data packet ready
#define USB_DEV_TX_NOT_COMP     0x00000080  // Large packet split up, more data
                                            // to come
#define USB_DEV_TX_SENT_STALL   0x00000020  // Stall was sent on this endpoint
#define USB_DEV_TX_UNDERRUN     0x00000004  // IN received with no data ready
#define USB_DEV_TX_FIFO_NE      0x00000002  // The TX FIFO is not empty
#define USB_DEV_TX_TXPKTRDY     0x00000001  // Transmit still being transmitted
#define USB_DEV_EP0_SETUP_END   0x00000010  // Control transaction ended before
                                            // Data End seen
#define USB_DEV_EP0_SENT_STALL  0x00000004  // Stall was sent on this endpoint
#define USB_DEV_EP0_IN_PKTPEND  0x00000002  // Transmit data packet pending
#define USB_DEV_EP0_OUT_PKTRDY  0x00000001  // Receive data packet ready

//*****************************************************************************
//
// The following are values that can be passed to USBHostEndpointConfig() and
// USBDevEndpointConfigSet() as the ui32Flags parameter.
//
//*****************************************************************************
#define USB_EP_AUTO_SET         0x00000001  // Auto set feature enabled
#define USB_EP_AUTO_REQUEST     0x00000002  // Auto request feature enabled
#define USB_EP_AUTO_CLEAR       0x00000004  // Auto clear feature enabled
#define USB_EP_DMA_MODE_0       0x00000008  // Enable DMA access using mode 0
#define USB_EP_DMA_MODE_1       0x00000010  // Enable DMA access using mode 1
#define USB_EP_DIS_NYET         0x00000020  // Disable NYET response for
                                            // high-speed Bulk and Interrupt
                                            // endpoints in device mode.
#define USB_EP_MODE_ISOC        0x00000000  // Isochronous endpoint
#define USB_EP_MODE_BULK        0x00000100  // Bulk endpoint
#define USB_EP_MODE_INT         0x00000200  // Interrupt endpoint
#define USB_EP_MODE_CTRL        0x00000300  // Control endpoint
#define USB_EP_MODE_MASK        0x00000300  // Mode Mask
#define USB_EP_SPEED_LOW        0x00000000  // Low Speed
#define USB_EP_SPEED_FULL       0x00001000  // Full Speed
#define USB_EP_SPEED_HIGH       0x00004000  // High Speed
#define USB_EP_HOST_IN          0x00000000  // Host IN endpoint
#define USB_EP_HOST_OUT         0x00002000  // Host OUT endpoint
#define USB_EP_DEV_IN           0x00002000  // Device IN endpoint
#define USB_EP_DEV_OUT          0x00000000  // Device OUT endpoint

//*****************************************************************************
//
// The following are values that can be passed to USBHostPwrConfig() as the
// ui32Flags parameter.
//
//*****************************************************************************
#define USB_HOST_PWRFLT_LOW     0x00000010
#define USB_HOST_PWRFLT_HIGH    0x00000030
#define USB_HOST_PWRFLT_EP_NONE 0x00000000
#define USB_HOST_PWRFLT_EP_TRI  0x00000140
#define USB_HOST_PWRFLT_EP_LOW  0x00000240
#define USB_HOST_PWRFLT_EP_HIGH 0x00000340
#define USB_HOST_PWREN_MAN_LOW  0x00000000
#define USB_HOST_PWREN_MAN_HIGH 0x00000001
#define USB_HOST_PWREN_AUTOLOW  0x00000002
#define USB_HOST_PWREN_AUTOHIGH 0x00000003
#define USB_HOST_PWREN_FILTER   0x00010000

//*****************************************************************************
//
// The following are the valid values that can be passed to the
// USBHostLPMConfig() function in the ui32Config parameter.
//
//*****************************************************************************
#define USB_HOST_LPM_RMTWAKE    0x00000100
#define USB_HOST_LPM_L1         0x00000001

//*****************************************************************************
//
// The following are the valid values that can be passed to the
// USBDevLPMConfig() function in the ui32Config parameter.
//
//*****************************************************************************
#define USB_DEV_LPM_NAK         0x00000010
#define USB_DEV_LPM_NONE        0x00000000
#define USB_DEV_LPM_EN          0x0000000c
#define USB_DEV_LPM_EXTONLY     0x00000004

//*****************************************************************************
//
// The following are the valid values that are returned from the
// USBLPMLinkStateGet() function.
//
//*****************************************************************************
#define USB_DEV_LPM_LS_RMTWAKE  0x00000100
#define USB_DEV_LPM_LS_L1       0x00000001

//*****************************************************************************
//
// The following are the valid values that are passed to the USBLPMIntEnable()
// or USBLPMIntDisable() functions or are returned from the USBLPMIntStatus()
// function.
//
//*****************************************************************************
#define USB_INTLPM_ERROR        0x00000020
#define USB_INTLPM_RESUME       0x00000010
#define USB_INTLPM_INCOMPLETE   0x00000008
#define USB_INTLPM_ACK          0x00000004
#define USB_INTLPM_NYET         0x00000002
#define USB_INTLPM_STALL        0x00000001

//*****************************************************************************
//
// The following are the valid values that are passed to the USBClockEnable()
// functions.
//
//*****************************************************************************
#define USB_CLOCK_INTERNAL      0x00000200
#define USB_CLOCK_EXTERNAL      0x00000300

//*****************************************************************************
//
// The configuration options used with the USBULPIConfig() API.
//
//*****************************************************************************
#define USB_ULPI_EXTVBUS        0x00000001
#define USB_ULPI_EXTVBUS_IND    0x00000002

//*****************************************************************************
//
// The following are special values that can be passed to
// USBHostEndpointConfig() as the ui32NAKPollInterval parameter.
//
//*****************************************************************************
#define MAX_NAK_LIMIT           31          // Maximum NAK interval
#define DISABLE_NAK_LIMIT       0           // No NAK timeouts

//*****************************************************************************
//
// This value specifies the maximum size of transfers on endpoint 0 as 64
// bytes.  This value is fixed in hardware as the FIFO size for endpoint 0.
//
//*****************************************************************************
#define MAX_PACKET_SIZE_EP0     64

//*****************************************************************************
//
// These values are used to indicate which endpoint to access.
//
//*****************************************************************************
#define USB_EP_0                0x00000000  // Endpoint 0
#define USB_EP_1                0x00000010  // Endpoint 1
#define USB_EP_2                0x00000020  // Endpoint 2
#define USB_EP_3                0x00000030  // Endpoint 3
#define USB_EP_4                0x00000040  // Endpoint 4
#define USB_EP_5                0x00000050  // Endpoint 5
#define USB_EP_6                0x00000060  // Endpoint 6
#define USB_EP_7                0x00000070  // Endpoint 7
#define NUM_USB_EP              8           // Number of supported endpoints

//*****************************************************************************
//
// These macros allow conversion between 0-based endpoint indices and the
// USB_EP_x values required when calling various USB APIs.
//
//*****************************************************************************
#define IndexToUSBEP(x)         ((x) << 4)
#define USBEPToIndex(x)         ((x) >> 4)

//*****************************************************************************
//
// The following are values that can be passed to USBFIFOConfigSet() as the
// ui32FIFOSize parameter.
//
//*****************************************************************************
#define USB_FIFO_SZ_8           0x00000000  // 8 byte FIFO
#define USB_FIFO_SZ_16          0x00000001  // 16 byte FIFO
#define USB_FIFO_SZ_32          0x00000002  // 32 byte FIFO
#define USB_FIFO_SZ_64          0x00000003  // 64 byte FIFO
#define USB_FIFO_SZ_128         0x00000004  // 128 byte FIFO
#define USB_FIFO_SZ_256         0x00000005  // 256 byte FIFO
#define USB_FIFO_SZ_512         0x00000006  // 512 byte FIFO
#define USB_FIFO_SZ_1024        0x00000007  // 1024 byte FIFO
#define USB_FIFO_SZ_2048        0x00000008  // 2048 byte FIFO

//*****************************************************************************
//
// This macro allow conversion from a FIFO size label as defined above to
// a number of bytes
//
//*****************************************************************************
#define USBFIFOSizeToBytes(x)   (8 << (x))

//*****************************************************************************
//
// The following are values that can be passed to USBEndpointDataSend() as the
// ui32TransType parameter.
//
//*****************************************************************************
#define USB_TRANS_OUT           0x00000102  // Normal OUT transaction
#define USB_TRANS_IN            0x00000102  // Normal IN transaction
#define USB_TRANS_IN_LAST       0x0000010a  // Final IN transaction (for
                                            // endpoint 0 in device mode)
#define USB_TRANS_SETUP         0x0000110a  // Setup transaction (for endpoint
                                            // 0)
#define USB_TRANS_STATUS        0x00000142  // Status transaction (for endpoint
                                            // 0)

//*****************************************************************************
//
// The following are values are returned by the USBModeGet function.
//
//*****************************************************************************
#define USB_DUAL_MODE_HOST      0x00000001  // Dual mode controller is in Host
                                            // mode.
#define USB_DUAL_MODE_DEVICE    0x00000081  // Dual mode controller is in
                                            // Device mode.
#define USB_DUAL_MODE_NONE      0x00000080  // Dual mode controller mode is not
                                            // set.
#define USB_OTG_MODE_ASIDE_HOST 0x0000001d  // OTG controller on the A side of
                                            // the cable.
#define USB_OTG_MODE_ASIDE_NPWR 0x00000001  // OTG controller on the A side of
                                            // the cable.
#define USB_OTG_MODE_ASIDE_SESS 0x00000009  // OTG controller on the A side of
                                            // the cable Session Valid.
#define USB_OTG_MODE_ASIDE_AVAL 0x00000011  // OTG controller on the A side of
                                            // the cable A valid.
#define USB_OTG_MODE_ASIDE_DEV  0x00000019  // OTG controller on the A side of
                                            // the cable.
#define USB_OTG_MODE_BSIDE_HOST 0x0000009d  // OTG controller on the B side of
                                            // the cable.
#define USB_OTG_MODE_BSIDE_DEV  0x00000099  // OTG controller on the B side of
                                            // the cable.
#define USB_OTG_MODE_BSIDE_NPWR 0x00000081  // OTG controller on the B side of
                                            // the cable.
#define USB_OTG_MODE_NONE       0x00000080  // OTG controller mode is not set.

//*****************************************************************************
//
// The values for the USBDMAChannelIntEnable() and USBDMAChannelIntStatus()
// APIs.
//
//*****************************************************************************
#define USB_DMA_INT_CH8         0x00000080
#define USB_DMA_INT_CH7         0x00000040
#define USB_DMA_INT_CH6         0x00000020
#define USB_DMA_INT_CH5         0x00000010
#define USB_DMA_INT_CH4         0x00000008
#define USB_DMA_INT_CH3         0x00000004
#define USB_DMA_INT_CH2         0x00000002
#define USB_DMA_INT_CH1         0x00000001

//*****************************************************************************
//
// The values for the USBDMAChannelStatus() API.
//
//*****************************************************************************
#define USB_DMA_STATUS_ERROR    0x00000100

//*****************************************************************************
//
// The valid return values for the USBDMAModeSet() and USBDMAModeGet() APIs or
// USBDMAChannelConfig().
//
//*****************************************************************************
#define USB_DMA_CFG_BURST_NONE  0x00000000
#define USB_DMA_CFG_BURST_4     0x00000200
#define USB_DMA_CFG_BURST_8     0x00000400
#define USB_DMA_CFG_BURST_16    0x00000600
#define USB_DMA_CFG_INT_EN      0x00000008
#define USB_DMA_CFG_MODE_0      0x00000000
#define USB_DMA_CFG_MODE_1      0x00000004
#define USB_DMA_CFG_DIR_RX      0x00000000
#define USB_DMA_CFG_DIR_TX      0x00000002
#define USB_DMA_CFG_EN          0x00000001

//*****************************************************************************
//
// The following are values that can be passed to USBModeConfig() as the
// ui3Mode parameter.
//
//*****************************************************************************
#define USB_MODE_HOST_VBUS      0x00000004
#define USB_MODE_HOST           0x00000002
#define USB_MODE_DEV_VBUS       0x00000005
#define USB_MODE_DEV            0x00000003
#define USB_MODE_OTG            0x00000000

#endif
