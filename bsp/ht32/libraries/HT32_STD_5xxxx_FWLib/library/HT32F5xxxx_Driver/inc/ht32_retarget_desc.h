/*********************************************************************************************************//**
 * @file    ht32_retarget_desc.h
 * @version $Rev:: 891          $
 * @date    $Date:: 2016-07-14 #$
 * @brief   The USB VCP descriptor file of retarget.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_RETARGET_DESC_H
#define __HT32_RETARGET_DESC_H

/* Exported constants --------------------------------------------------------------------------------------*/

  /*--------------------------------------------------------------------------------------------------------*/
  /* IAD to associate the two CDC interfaces                                                                */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
  8,                          // bLength             1 Size of this descriptor in bytes
  11,                         // bDescriptorType     1 Descriptor Type
  11,                         // bFirstInterface     1
  2,                          // bInterfaceCount     1
  2,                          // bFunctionClass      1
  2,                          // bFunctionSubClass   1
  0,                          // bFunctionProtocol   1
  0x00,                       // iFunction           1 Index of string descriptor describing this function.

  /*--------------------------------------------------------------------------------------------------------*/
  /* Interface descriptor                                                                                   */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_LEN_INF,               // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_04_INF,           // bDescriptorType     1 INTERFACE Descriptor Type
  11,                         // bInterfaceNumber    1 Number of this interface (Zero-based 0)
  0x00,                       // bAlternateSetting   1 Value used to select alternate setting
  1,                          // bNumEndpoints       1 Number of endpoints used by this interface
  DESC_CLASS_02_CDC_CTRL,     // bInterfaceClass     1 Class code (assigned by USB-IF)
  2,                          // bInterfaceSubClass  1 Subclass code (assigned by USB-IF)
  0,                          // bInterfaceProtocol  1 Protocol code (assigned by USB)
  0x00,                       // iInterface          1 Index of string descriptor describing this interface

  /*--------------------------------------------------------------------------------------------------------*/
  /* Header Functional descriptor                                                                           */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  5,                          // bFunctionLength     1 Size of this descriptor in bytes
  0x24,                       // bDescriptorType     1 CS_INTERFACE descriptor type
  0,                          // bDescriptorSubtype  1 header functional descriptor
  DESC_H2B(0x0110),           // bcdCDC              2 spec release number

  /*--------------------------------------------------------------------------------------------------------*/
  /* Abstract control management Functional                                                                 */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  4,                          // bFunctionLength     1 Size of this descriptor in bytes
  0x24,                       // bDescriptorType     1 CS_INTERFACE descriptor type
  2,                          // bDescriptorSubtype  1 Abstract Control Management Functional descriptor
  0x02,                       // bmCapabilities      1

  /*--------------------------------------------------------------------------------------------------------*/
  /* Union Functional                                                                                       */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  5,                          // bFunctionLength     1 Size of this descriptor in bytes
  0x24,                       // bDescriptorType     1 CS_INTERFACE descriptor type
  5,                          // bDescriptorSubtype  1 Union Functional descriptor
  0x00,                       // bMasterInterface    1 Communication class interface
  0x01,                       // bSlaveInterface0    1 Data Class Interface

  /*--------------------------------------------------------------------------------------------------------*/
  /* Call Management Functional                                                                             */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  5,                          // bFunctionLength     1 Size of this descriptor in bytes
  0x24,                       // bDescriptorType     1 CS_INTERFACE descriptor type
  1,                          // bDescriptorSubtype  1 Call Management Functional descriptor
  0x00,                       // bmCapabilities      1
  0x01,                       // bDataInterface      1 Interface number of Data

  /*--------------------------------------------------------------------------------------------------------*/
  /* Endpoint descriptor                                                                                    */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_LEN_EPT,               // bLengthE            1 Size of this descriptor in bytes
  DESC_TYPE_05_EPT,           // bDescriptorType     1 ENDPOINT Descriptor Type
  (0x80 | RETARGET_CTRL_EPT), // bEndpointAddress    1 The address of the endpoint
                              //                        Bit 3..0: The endpoint number
                              //                        Bit 6..4: Reserved
                              //                        Bit 7   : Direction (0 = Out/1 = In)
  0x03,                       // bmAttribute         1 Endpoint Attribute
                              //                        Bit 1..0: Transfer type
                              //                                  00 = Control
                              //                                  01 = Isochronous
                              //                                  10 = Bulk
                              //                                  11 = Interrupt
                              //                        All other reserved
  DESC_H2B(RETARGET_CTRL_LEN),// wMaxPacketSize      2 Maximum packet size
  0x00,                       // bInterval           1 Interval for polling endpoint

  /*--------------------------------------------------------------------------------------------------------*/
  /* Data class interface descriptor                                                                        */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_LEN_INF,               // bLength             1 Endpoint Descriptor size
  DESC_TYPE_04_INF,           // bDescriptorType     1
  12,                         // bInterfaceNumber    1 Number of Interface
  0x00,                       // bAlternateSetting   1 Alternate setting
  2,                          // bNumEndpoints       1 Two endpoints used
  DESC_CLASS_0A_CDC_DATA,     // bInterfaceClass     1
  0,                          // bInterfaceSubClass  1
  0,                          // bInterfaceProtocol  1
  0x00,                       // iInterface          1

  /*--------------------------------------------------------------------------------------------------------*/
  /* Endpoint n Out descriptor                                                                              */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_LEN_EPT,               // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_05_EPT,           // bDescriptorType     1 ENDPOINT Descriptor Type
  (0x00 | RETARGET_RX_EPT),   // bEndpointAddress    1 The address of the endpoint
                              //                        Bit 3..0: The endpoint number
                              //                        Bit 6..4: Reserved
                              //                        Bit 7   : Direction (0 = Out/1 = In)
  0x02,                       // bmAttribute         1 Endpoint Attribute
                              //                        Bit 1..0: Transfer type
                              //                                  00 = Control
                              //                                  01 = Isochronous
                              //                                  10 = Bulk
                              //                                  11 = Interrupt
                              //                        All other reserved
  DESC_H2B(RETARGET_RX_LEN),  // wMaxPacketSize      2 Maximum packet size
  0x00,                       // bInterval           1 Interval for polling endpoint

  /*--------------------------------------------------------------------------------------------------------*/
  /* Endpoint n In Descriptor                                                                               */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_LEN_EPT,               // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_05_EPT,           // bDescriptorType     1 ENDPOINT Descriptor Type
  (0x80 | RETARGET_TX_EPT),   // bEndpointAddress    1 The address of the endpoint
                              //                        Bit 3..0: The endpoint number
                              //                        Bit 6..4: Reserved
                              //                        Bit 7   : Direction (0 = Out/1 = In)
  0x02,                       // bmAttribute         1 Endpoint Attribute
                              //                        Bit 1..0: Transfer type
                              //                                  00 = Control
                              //                                  01 = Isochronous
                              //                                  10 = Bulk
                              //                                  11 = Interrupt
                              //                        All other reserved
  DESC_H2B(RETARGET_TX_LEN),  // wMaxPacketSize      2 Maximum packet size
  0x00,                       // bInterval           1 Interval for polling endpoint

#endif /* __HT32_RETARGET_DESC_H ---------------------------------------------------------------------------*/
