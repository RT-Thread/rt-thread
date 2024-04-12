/*********************************************************************************************************//**
 * @file    ht32_retarget_desc.c
 * @version $Rev:: 783          $
 * @date    $Date:: 2016-06-10 #$
 * @brief   The The USB Descriptor of retarget.
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/

#define DESC_LEN_CONFN_T          (u16)(DESC_LEN_CONFN)

/*----------------------------------------------------------------------------------------------------------*/
/* USB Device descriptor setting                                                                            */
/*----------------------------------------------------------------------------------------------------------*/
// <h> USB Device descriptor setting
//   <o0> USB Specification Release number (bcdUSB)
//      <0x0200=> USB 2.0
//      <0x0110=> USB 1.1
//      <0x0100=> USB 1.0
//   <o1> USB Class code (assigned by the USB-IF)
//      <0x00=> Use class information in the Interface Descriptors (0x00)
//      <0x02=> Communications and CDC Control (CDC, 0x02)
//      <0xDC=> Diagnostic Device (0xDC)
//      <0xEF=> Miscellaneous (0xEF)
//      <0xFF=> Vendor Specific (0xFF)
//   <o2> USB Subclass code (assigned by the USB-IF) <0x0-0xFF:1>
//   <o3> USB Protocol code (assigned by the USB-IF) <0x0-0xFF:1>
//   <o4> USB Vendor ID <0x0-0xFFFF:1>
//   <o5> USB Product ID <0x0-0xFFFF:1>
//   <o6> USB Device Version <0x0-0xFFFF:1>
//   <o7.0> USB String descriptor - Manufacturer
//   <o8.0> USB String descriptor - Product
//   <o9.0> USB String descriptor - Device serial number
//   <o10> USB Number of possible configurations <0-255:1>
#define DESC_BCDUSB               (0x0110)
#define DESC_BDEVCLASS            (0x00)
#define DESC_BDEVSUBCLASS         (0x00)
#define DESC_BDEVPROTOCOL         (0x00)
#define DESC_IDVENDOR             (0x04D9)
#define DESC_IDPRODUCT            (0x8008)
#define DESC_BCDDEVICE            (0x0100)
#define DESC_IMANUFACTURE         (1)
#define DESC_IPRODUCT             (1)
#define DESC_ISERIALNUM           (1)
#define DESC_INUMCONFN            (1)
// </h>

/*----------------------------------------------------------------------------------------------------------*/
/* USB Device Descriptor definition. DO NOT MODIFY.                                                         */
/*----------------------------------------------------------------------------------------------------------*/
#if (DESC_BDEVCLASS == 0x0 & DESC_BDEVSUBCLASS != 0x0)
#error "DESC_BDEVSUBCLASS must be reset to zero when the DESC_BDEVCLASS is equal to zero."
#endif
#define DESC_WMAXPACKETSIZE0      (_EP0LEN)
#define DESC_STR_MAN              (1 * DESC_IMANUFACTURE)
#define DESC_STR_PRD              (2 * DESC_IPRODUCT)
#define DESC_STR_SER              (3 * DESC_ISERIALNUM)
#define DESC_NUM_STRING           (1 + 3)

/*----------------------------------------------------------------------------------------------------------*/
/* USB Device descriptor                                                                                    */
/*----------------------------------------------------------------------------------------------------------*/
__ALIGN4 static uc8 guUSB_DeviceDesc[] =
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Device descriptor                                                                                      */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_LEN_DEV,               // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_01_DEV,           // bDescriptorType     1 DEVICE Descriptor Type
  DESC_H2B(DESC_BCDUSB),      // bcdUSB              2 USB Specification Release Number
  DESC_BDEVCLASS,             // bDeviceClass        1 Class code (assigned by the USB-IF)
  DESC_BDEVSUBCLASS,          // bDeviceSubClass     1 Subclass code (assigned by the USB-IF)
  DESC_BDEVPROTOCOL,          // bDeviceProtocol     1 Protocol code (assigned by the USB-IF)
  DESC_WMAXPACKETSIZE0,       // wMaxPacketSize0     1 Maximum packet size for endpoint zero
  DESC_H2B(DESC_IDVENDOR),    // idVendor            2 Vendor ID (assigned by USB-IF)
  DESC_H2B(DESC_IDPRODUCT),   // idProduct           2 Product ID (assigned by manufacturer)
  DESC_H2B(DESC_BCDDEVICE),   // bcdDevice           2 Device release number
  DESC_STR_MAN,               // iManufacturer       1 Index of string descriptor (Manufacturer)
  DESC_STR_PRD,               // iProduct            1 Index of string descriptor (Product)
  DESC_STR_SER,               // iSerialNumber       1 Index of string descriptor (Serial Number)
  DESC_INUMCONFN,             // iNumConfigurations  1 Number of possible configuration
};


/*----------------------------------------------------------------------------------------------------------*/
/* USB Configuration descriptor setting                                                                     */
/*----------------------------------------------------------------------------------------------------------*/
// <h> USB Configuration descriptor setting
//   <o0.0> Self-powered
//     <i> Bit 6 of bmAttributes
//   <o1.0> Remote Wakeup
//     <i> Bit 5 of bmAttributes
//   <o2> USB Device maximum power (mA) < 2-512:2>
#define DESC_BMATTR_SELF_POWER        (0)
#define DESC_BMATTR_REMOTE_WAKEUP     (0)
#define DESC_BMAXPOWER                (100)
// </h>

/*----------------------------------------------------------------------------------------------------------*/
/* USB Configuration Descriptor definition. DO NOT MODIFY.                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define DESC_BMATTRIBUTES        (0x80 | (DESC_BMATTR_SELF_POWER << 6) | (DESC_BMATTR_REMOTE_WAKEUP << 5))
#define DESC_TOTAL_LEN           DESC_H2B((DESC_LEN_CONFN_T + RETARGET_DLEN))

/*----------------------------------------------------------------------------------------------------------*/
/* USB Configuration Descriptor                                                                             */
/*----------------------------------------------------------------------------------------------------------*/
__ALIGN4 static uc8 guUSB_ConfnDesc[] =
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Configuration descriptor                                                                               */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_LEN_CONFN,             // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_02_CONFN,         // bDescriptorType     1 CONFIGURATION Descriptor Type
  DESC_TOTAL_LEN,             // wTotalLength        2 Total length of data returned for this configuration
  RETARGET_INF,               // bNumberInterface    1 Number of interfaces supported by this configuration
  0x01,                       // bConfigurationValue 1 Value to use as an argument to the SetConfiguration()
  0x00,                       // iConfiguration      1 Index of string descriptor describing this configuration
  DESC_BMATTRIBUTES,          // bmAttributes        1 Configuration characteristics
                              //                        D6: Self-powered, D5: RemoteWakeup
  DESC_POWER(DESC_BMAXPOWER), // bMaxPower           1 Maximum power consumption of the USB device (2 mA units)

  #ifdef RETARGET_IS_USB
    #include "ht32_retarget_desc.h"
  #endif

};

/*----------------------------------------------------------------------------------------------------------*/
/* USB String Descriptor                                                                                    */
/*----------------------------------------------------------------------------------------------------------*/
__ALIGN4 static uc8 guUSB_StringDescLANGID[] =
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* LANGID (Index = 0)                                                                                     */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_STRLEN(1),             // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_03_STR,           // bDescriptorType     1 STRING Descriptor Type
  DESC_H2B(0x0409),           // wLANGID[0]          2 LANGID code zero
};

#if (DESC_IMANUFACTURE == 1)
__ALIGN4 static uc8 guUSB_StringDescManufacture[] =
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Manufacture (Index = 1)                                                                                */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_STRLEN(6),             // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_03_STR,           // bDescriptorType     1 STRING Descriptor Type
  DESC_CHAR('H'),             // bString             N UNICODE encoded string
  DESC_CHAR('O'),
  DESC_CHAR('L'),
  DESC_CHAR('T'),
  DESC_CHAR('E'),
  DESC_CHAR('K'),
};
#endif

#if (DESC_IPRODUCT == 1)
__ALIGN4 static uc8 guUSB_StringDescProduct[] =
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Product (Index = 2)                                                                                    */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_STRLEN(7),             // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_03_STR,           // bDescriptorType     1 STRING Descriptor Type
  DESC_CHAR('U'),             // bString             N UNICODE encoded string
  DESC_CHAR('S'),
  DESC_CHAR('B'),
  DESC_CHAR('-'),
  DESC_CHAR('V'),
  DESC_CHAR('C'),
  DESC_CHAR('P'),
};
#endif


#if (DESC_ISERIALNUM == 1)
__ALIGN4 static uc8 guUSB_StringDescSerialNum[] =
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Serial Number (Index = 3)                                                                              */
  /*--------------------------------------------------------------------------------------------------------*/
                              /* Field            Size Description                                          */
                              /*----------------------------------------------------------------------------*/
  DESC_STRLEN(12),            // bLength             1 Size of this descriptor in bytes
  DESC_TYPE_03_STR,           // bDescriptorType     1 STRING Descriptor Type
  DESC_CHAR('S'),             // bString             N UNICODE encoded string
  DESC_CHAR('N'),
  DESC_CHAR('0'),
  DESC_CHAR('0'),
  DESC_CHAR('0'),
  DESC_CHAR('0'),
  DESC_CHAR('0'),
  DESC_CHAR('0'),
  DESC_CHAR('1'),
  DESC_CHAR('0'),
  DESC_CHAR('0'),
  DESC_CHAR('0'),
};
#endif

uc8 *gpStringDesc[DESC_NUM_STRING] =
{

  guUSB_StringDescLANGID,

  #if (DESC_IMANUFACTURE == 1)
  guUSB_StringDescManufacture,
  #else
  NULL,
  #endif

  #if (DESC_IPRODUCT == 1)
  guUSB_StringDescProduct,
  #else
  NULL,
  #endif

  #if (DESC_ISERIALNUM == 1)
  guUSB_StringDescSerialNum
  #else
  NULL,
  #endif

};

/*********************************************************************************************************//**
  * @brief  USB Descriptor pointer initialization.
  * @param  pDesc: pointer of USBDCore_Desc_TypeDef
  * @retval None
  ***********************************************************************************************************/
void USBDDesc_Init(USBDCore_Desc_TypeDef *pDesc)
{
  pDesc->pDeviceDesc = guUSB_DeviceDesc;
  pDesc->pConfnDesc = guUSB_ConfnDesc;
  pDesc->ppStringDesc = gpStringDesc;
  pDesc->uStringDescNumber = DESC_NUM_STRING;

  return;
}
