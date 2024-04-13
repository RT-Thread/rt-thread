#include "usbd_core.h"

#define MS_OS_20_DESCRIPTOR_LENGTH (0xB2)

#define WEBUSB_URL_STRINGS \
    'd', 'e', 'v', 'a', 'n', 'l', 'a', 'i', '.', 'g', 'i', 't', 'h', 'u', 'b', '.', 'i', 'o', '/', 'w', 'e', 'b', 'd', 'f', 'u', '/', 'd', 'f', 'u', '-', 'u', 't', 'i', 'l'

#define WL_REQUEST_WEBUSB (0x22)
#define WL_REQUEST_WINUSB (0x21)

#define URL_DESCRIPTOR_LENGTH 0x2C

// 描述符集信息
const uint8_t MS_OS_20_DESCRIPTOR_SET[MS_OS_20_DESCRIPTOR_LENGTH] = {
    // Microsoft OS 2.0 描述符集标头
    0x0A, 0x00,                       // Descriptor size (10 bytes)
    0x00, 0x00,                       // MS OS 2.0 descriptor set header
    0x00, 0x00, 0x03, 0x06,           // Windows version (8.1) (0x06030000)
    MS_OS_20_DESCRIPTOR_LENGTH, 0x00, // Size, MS OS 2.0 descriptor set

    // Microsoft OS 2.0 配置子集标头
    0x08, 0x00, // wLength
    0x01, 0x00, // wDescriptorType
    0x00,       // 适用于配置 1
    0x00,       // bReserved
    0XA8, 0X00, // Size, MS OS 2.0 configuration subset

    // Microsoft OS 2.0 功能子集头
    0x08, 0x00, // Descriptor size (8 bytes)
    0x02, 0x00, // MS OS 2.0 function subset header
    0x01,       // 第2个接口
    0x00,       // 必须设置为 0
    0xA0, 0x00,

    // Microsoft OS 2.0 兼容 ID 描述符
    // 兼容 ID 描述符告诉 Windows 此设备与 WinUSB 驱动程序兼容
    0x14, 0x00, // wLength  20
    0x03, 0x00, // MS_OS_20_FEATURE_COMPATIBLE_ID
    'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // Microsoft OS 2.0 注册表属性描述符
    // 注册表属性分配设备接口 GUID
    0x84, 0x00, //wLength: 132
    0x04, 0x00, // wDescriptorType: MS_OS_20_FEATURE_REG_PROPERTY: 0x04 (Table 9)
    0x07, 0x00, //wPropertyDataType: REG_MULTI_SZ (Table 15)
    0x2a, 0x00, //wPropertyNameLength:
    //bPropertyName: “DeviceInterfaceGUID”
    'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00, 'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00, 't', 0x00, 'e', 0x00,
    'r', 0x00, 'f', 0x00, 'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00, 'U', 0x00, 'I', 0x00, 'D', 0x00, 's', 0x00,
    0x00, 0x00,
    0x50, 0x00, // wPropertyDataLength
    //bPropertyData: “{975F44D9-0D08-43FD-8B3E-127CA8AFFF9D}”.
    '{', 0x00, '9', 0x00, 'd', 0x00, '7', 0x00, 'd', 0x00, 'e', 0x00, 'b', 0x00, 'b', 0x00, 'c', 0x00, '-', 0x00,
    'c', 0x00, '8', 0x00, '5', 0x00, 'd', 0x00, '-', 0x00, '1', 0x00, '1', 0x00, 'd', 0x00, '1', 0x00, '-', 0x00,
    '9', 0x00, 'e', 0x00, 'b', 0x00, '4', 0x00, '-', 0x00, '0', 0x00, '0', 0x00, '6', 0x00, '0', 0x00, '0', 0x00,
    '8', 0x00, 'c', 0x00, '3', 0x00, 'a', 0x00, '1', 0x00, '9', 0x00, 'a', 0x00, '}', 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t USBD_WebUSBURLDescriptor[URL_DESCRIPTOR_LENGTH] = {
    URL_DESCRIPTOR_LENGTH,
    WEBUSB_URL_TYPE,
    WEBUSB_URL_SCHEME_HTTPS,
    WEBUSB_URL_STRINGS
};

struct usb_webusb_url_ex_descriptor webusb_url_desc = {
    .vendor_code = WL_REQUEST_WEBUSB,
    .string = MS_OS_20_DESCRIPTOR_SET,
    .string_len = MS_OS_20_DESCRIPTOR_LENGTH
};