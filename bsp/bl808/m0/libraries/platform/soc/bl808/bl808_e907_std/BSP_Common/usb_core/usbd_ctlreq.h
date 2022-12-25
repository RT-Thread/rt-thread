#ifndef __USB_REQUEST_H
#define __USB_REQUEST_H

#include "bflb_bsp_driver_glue.h"
#include "usb_def.h"
#include  "usbd_def.h"

USBD_StatusTypeDef  USBD_StdDevReq (USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef  *req);
USBD_StatusTypeDef  USBD_StdItfReq (USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef  *req);
USBD_StatusTypeDef  USBD_StdEPReq  (USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef  *req);


void USBD_CtlError(USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef *req);
void USBD_ParseSetupRequest(USBD_SetupReqTypedef *req, uint8_t *pdata);
void USBD_GetString(uint8_t *desc, uint8_t *unicode, uint16_t *len);


#endif /* __USB_REQUEST_H */

