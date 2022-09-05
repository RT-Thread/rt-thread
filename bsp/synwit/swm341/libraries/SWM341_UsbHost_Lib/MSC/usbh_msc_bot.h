#ifndef __USBH_MSC_BOT_H__
#define __USBH_MSC_BOT_H__

#include <stdint.h>


typedef enum {
    USBH_MSC_BOT_CBW = 0,
    USBH_MSC_BOT_CBW_WAIT,
    USBH_MSC_BOT_DIN,
    USBH_MSC_BOT_DIN_WAIT,
    USBH_MSC_BOT_DOUT,
    USBH_MSC_BOT_DOUT_WAIT,
    USBH_MSC_BOT_CSW,
    USBH_MSC_BOT_CSW_WAIT,
    USBH_MSC_BOT_HANDLE_ERROR,
    USBH_MSC_BOT_HANDLE_STALL_IN,
    USBH_MSC_BOT_HANDLE_STALL_OUT,
} USBH_MSC_BOT_State;


typedef struct __attribute__((packed)) {
    uint32_t CBWSignature;
    uint32_t CBWTag;
    uint32_t CBWTransferLength;
    uint8_t  CBWFlags;
    uint8_t  CBWLUN;
    uint8_t  CBWCBLength;
    uint8_t  CBWCB[16];
} USBH_CBWPkt_t;


typedef struct __attribute__((packed)) {
    uint32_t CSWSignature;
    uint32_t CSWTag;
    uint32_t CSWDataResidue;
    uint8_t  CSWStatus;
} USBH_CSWPkt_t;


extern USBH_CBWPkt_t USBH_CBWData;
extern USBH_CSWPkt_t USBH_CSWData;


void USBH_MSC_BOT_Init(void);
void USBH_MSC_BOT_Process(USBH_Info_t *phost);
uint8_t USBH_MSC_BOT_DecodeCSW(USBH_Info_t *phost);


#endif // __USBH_MSC_BOT_H__

