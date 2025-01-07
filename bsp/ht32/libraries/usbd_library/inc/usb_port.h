
#ifndef _USB_PORT_H
#define _USB_PORT_H

#include "ht32.h"
//#include "ht32_usbd_core.h"
#include "usbd_code.h"


#define HT32F_DVB_USBConnect()      USBD_DPpullupCmd(ENABLE)
#define HT32F_DVB_USBDisConnect()   USBD_DPpullupCmd(DISABLE)


/* º¯ÊýÉùÃ÷ */
void usbd_sof_callback(USBDCore_TypeDef *pCore);
void usbd_reset_callback(USBDCore_TypeDef *pCore);
void usbd_suspend_callback(USBDCore_TypeDef *pCore);
void usbd_resume_callback(USBDCore_TypeDef *pCore);

void usbd_setup_callback(USBDCore_TypeDef *pCore);
void usbd_ep0_in_callback(USBDCore_TypeDef *pCore);
void usbd_ep0_out_callback(USBDCore_TypeDef *pCore);

void usbd_ep_in_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn);
void usbd_ep_out_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn);

void USB_Configuration(USBDCore_TypeDef *pCore);

#endif /* _USB_PORT_H */
