#ifndef __USBH_MSC_SCSI_H__
#define __USBH_MSC_SCSI_H__

#include <stdint.h>


typedef enum {
    USBH_MSC_OK = 0,
    USBH_MSC_FAIL,
    USBH_MSC_PHASE_ERROR,
    USBH_MSC_BUSY = 0xFF,
} USBH_MSC_Status;  // 见 CSW.bCSWStatus 取值


USBH_MSC_Status USBH_MSC_TestUnitReady(void);
USBH_MSC_Status USBH_MSC_ReadCapacity10(void);
USBH_MSC_Status USBH_MSC_ModeSense6(void);
USBH_MSC_Status USBH_MSC_RequestSense(void);
USBH_MSC_Status USBH_MSC_Read10(uint8_t *buffer, uint32_t address, uint32_t nbOfbytes);
USBH_MSC_Status USBH_MSC_Write10(uint8_t *buffer, uint32_t address, uint32_t nbOfbytes);


#endif //__USBH_MSC_SCSI_H__

