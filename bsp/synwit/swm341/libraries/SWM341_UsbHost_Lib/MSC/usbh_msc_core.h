#ifndef __USBH_MSC_CORE_H__
#define __USBH_MSC_CORE_H__

#include <stdint.h>
#include "usbh_core.h"


typedef enum {
    USBH_MSC_GET_MAXLUN = 0,
    USBH_MSC_TEST_UNIT_READY,
    USBH_MSC_READ_CAPACITY10,
    USBH_MSC_MODE_SENSE6,
    USBH_MSC_REQUEST_SENSE,
    USBH_MSC_BOT_TRANSFER,
    USBH_MSC_DEFAULT_APP,
    USBH_MSC_CLEAR_STALL,
    USBH_MSC_UNRECOVERED_STATE
} USBH_MSC_State;


typedef struct {
    uint8_t  InEp;
    uint8_t  OutEp;
    uint16_t InEpSize;
    uint16_t OutEpSize;
    uint8_t  InEpDATAX;
    uint8_t  OutEpDATAX;

    uint8_t  Ready;
    uint8_t  MaxLUN;        // Max Logic Unit Number
    uint32_t Capacity;
    uint16_t PageSize;
    uint8_t  WProtect;      // Write Protect
    uint32_t SenseKey;
} USBH_MSC_Info_t;


typedef struct {
    uint8_t  MSCState;
    uint8_t  MSCStateBkp;
    uint8_t  BOTState;
    uint8_t  BOTStateBkp;
    uint8_t  bCSWStatus;    // CSW.bCSWStatus
    uint8_t *pDataBuffer;
    uint8_t  UDiskReady;
} USBH_BOTXfer_t;


extern volatile USBH_MSC_Info_t USBH_MSC_Info;
extern volatile USBH_BOTXfer_t  USBH_BOTXfer;


extern USBH_Class_cb_t USBH_MSC_cb;


USBH_Status USBH_MSC_Init(USBH_Info_t *phost);
void        USBH_MSC_DeInit(USBH_Info_t *phost);
USBH_Status USBH_MSC_Request(USBH_Info_t *phost);
USBH_Status USBH_MSC_Process(USBH_Info_t *phost);

USBH_Status USBH_MSC_getMaxLUN(USBH_Info_t *phost);
void USBH_MSC_ErrorHandle(uint8_t status);


#endif // __USBH_MSC_CORE_H__

