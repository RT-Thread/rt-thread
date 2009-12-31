/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_desc.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Descriptors for Mass Storage Device
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_desc.h"

const uint8_t MASS_DeviceDescriptor[MASS_SIZ_DEVICE_DESC] =
{
    0x12,   /* bLength  */
    0x01,   /* bDescriptorType */
    0x00,   /* bcdUSB, version 2.00 */
    0x02,
    0x00,   /* bDeviceClass : each interface define the device class */
    0x00,   /* bDeviceSubClass */
    0x00,   /* bDeviceProtocol */
    0x40,   /* bMaxPacketSize0 0x40 = 64 */
    0x83,   /* idVendor     (0483) */
    0x04,
    0x20,   /* idProduct */
    0x57,
    0x00,   /* bcdDevice 2.00*/
    0x02,
    1,              /* index of string Manufacturer  */
    /**/
    2,              /* index of string descriptor of product*/
    /* */
    3,              /* */
    /* */
    /* */
    0x01    /*bNumConfigurations */
};

const uint8_t MASS_ConfigDescriptor[MASS_SIZ_CONFIG_DESC] =
{

    0x09,   /* bLength: Configuation Descriptor size */
    0x02,   /* bDescriptorType: Configuration */
    MASS_SIZ_CONFIG_DESC,

    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    /*      Configuration value */
    0x00,   /* iConfiguration: */
    /*      Index of string descriptor */
    /*      describing the configuration */
    0xC0,   /* bmAttributes: */
    /*      bus powered */
    100,   /* MaxPower 100 mA */

    /*****************接口描述符*******************/
//bLength字段。接口描述符的长度为9字节。
    0x09,

//bDescriptorType字段。接口描述符的编号为0x04。
    0x04,

//bInterfaceNumber字段。该接口的编号，第一个接口，编号为0。
    0x00,

//bAlternateSetting字段。该接口的备用编号，为0。
    0x00,

//bNumEndpoints字段。非0端点的数目。该接口有2个批量端点
    0x02,

//bInterfaceClass字段。该接口所使用的类。大容量存储设备接口类的代码为0x08。
    0x08,

//bInterfaceSubClass字段。该接口所使用的子类。SCSI透明命令集的子类代码为0x06。
    0x06,

//bInterfaceProtocol字段。协议为仅批量传输，代码为0x50。
    0x50,

//iConfiguration字段。该接口的字符串索引值。
    4,          /* iInterface: */

    /*************标准批量数据输入端点描述符****************/
    /* 18 */
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type *///bDescriptorType字段。端点描述符编号为0x05。

//bEndpointAddress字段。端点的地址。我们使用D12的输入端点2。
//D7位表示数据方向，输入端点D7为1。所以输入端点2的地址为0x82。
    0x81,   /*Endpoint address (IN, address 1) */

    //bmAttributes字段。D1~D0为端点传输类型选择。
//该端点为批端点。批量端点的编号为2。其它位保留为0。
    0x02,   /*Bulk endpoint type */

    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00,   /*Polling interval in milliseconds */

    /*************标准批量数据输出端点描述符****************/
    /* 25 */
    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    0x02,   /*Endpoint address (OUT, address 2) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00     /*Polling interval in milliseconds*/
    /*32*/
};
const uint8_t MASS_StringLangID[MASS_SIZ_STRING_LANGID] =
{
    MASS_SIZ_STRING_LANGID,
    0x03,
    0x09,
    0x04
}
;      /* LangID = 0x0409: U.S. English */
const uint8_t MASS_StringVendor[MASS_SIZ_STRING_VENDOR] =
{
    MASS_SIZ_STRING_VENDOR, /* Size of manufaturer string */
    0x03,           /* bDescriptorType = String descriptor */
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
};
const uint8_t MASS_StringProduct[MASS_SIZ_STRING_PRODUCT] =
{
    MASS_SIZ_STRING_PRODUCT,
    0x03,
    /* Product name: "STM32F10x:USB Mass Storage" */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'M', 0, 'a', 0, 's', 0,
    's', 0, ' ', 0, 'S', 0, 't', 0, 'o', 0, 'r', 0, 'a', 0, 'g', 0, 'e', 0

};

uint8_t MASS_StringSerial[MASS_SIZ_STRING_SERIAL] =
{
    MASS_SIZ_STRING_SERIAL,
    0x03,
    /* STM3210 */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, '1', 0, '0', 0
};
const uint8_t MASS_StringInterface[MASS_SIZ_STRING_INTERFACE] =
{
    MASS_SIZ_STRING_INTERFACE,
    0x03,
    /* Interface 0: "ST Mass" */
    'S', 0, 'T', 0, ' ', 0, 'M', 0, 'a', 0, 's', 0, 's', 0
};

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
