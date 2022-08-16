#ifndef __USBH_STDREQ_H__
#define __USBH_STDREQ_H__

#include <stdint.h>
#include "usbh_core.h"


USBH_Status USBH_GetDescriptor(USBH_Info_t *phost, uint8_t type, uint8_t index, uint8_t *buff, int size);
USBH_Status USBH_GetDescriptorEx(USBH_Info_t *phost, uint8_t reqType, uint8_t reqTarget, uint8_t type, uint8_t index, uint16_t wIndex, uint8_t *buff, int size);

USBH_Status USBH_SetAddress(USBH_Info_t *phost, uint8_t addr);
USBH_Status USBH_SetConfiguration(USBH_Info_t *phost, uint8_t cfg);
USBH_Status USBH_SetInterface(USBH_Info_t *phost, uint8_t intf, uint8_t altSetting);
USBH_Status USBH_ClrFeature(USBH_Info_t *phost, uint8_t ep);

USBH_Status USBH_ParseCfgDesc(USBH_Info_t *phost, uint8_t *buff, uint16_t size);

#endif
