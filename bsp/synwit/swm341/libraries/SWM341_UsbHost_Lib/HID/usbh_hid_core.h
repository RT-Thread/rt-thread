#ifndef __USBH_HID_CORE_H__
#define __USBH_HID_CORE_H__

#include "usbh_core.h"
#include "usbh_stdreq.h"


typedef enum {
    USBH_HID_IDLE = 0,
    USBH_HID_SYNC,
    USBH_HID_READ,
    USBH_HID_READ_WAIT,
    USBH_HID_SEND,
    USBH_HID_SEND_WAIT,
    USBH_HID_ERROR,
    USBH_HID_STALL_IN,
    USBH_HID_STALL_OUT
} USBH_HID_State;


typedef enum {
    USBH_HID_REQ_IDLE = 0,
    USBH_HID_REQ_GET_REPORT_DESC,
    USBH_HID_REQ_SET_IDLE,
    USBH_HID_REQ_SET_PROTOCOL,
    USBH_HID_REQ_SET_REPORT,
} USBH_HID_ReqState;


typedef struct {
  void (*Init)(void);
  void (*Decode)(uint8_t *data);
} USBH_HID_cb_t;


typedef struct {
    uint8_t  InEp;
    uint8_t  OutEp;
    uint16_t InEpSize;
    uint16_t OutEpSize;
    uint8_t  InEpDATAX;
    uint8_t  OutEpDATAX;

    uint8_t  InEpInterval;
    uint16_t InEpFrameNbr;
    uint8_t  OutEpInterval;
    uint16_t OutEpFrameNbr;

    USBH_HID_State    state;
    USBH_HID_State    stateBkp;
    USBH_HID_ReqState reqState;

    USBH_HID_cb_t    *hid_cb;
} USBH_HID_Info_t;


extern volatile USBH_HID_Info_t USBH_HID_Info;

extern USBH_Class_cb_t USBH_HID_cb;

USBH_Status USBH_HID_Init(USBH_Info_t *phost);
void        USBH_HID_DeInit(USBH_Info_t *phost);
USBH_Status USBH_HID_Request(USBH_Info_t *phost);
USBH_Status USBH_HID_Process(USBH_Info_t *phost);


USBH_Status USBH_Set_Idle(USBH_Info_t *phost, uint8_t interface, uint8_t reportId, uint8_t duration);
USBH_Status USBH_Set_Report(USBH_Info_t *phost, uint8_t interface, uint8_t reportId, uint8_t reportType, uint8_t * reportData, uint16_t reportLen);
USBH_Status USBH_Set_Protocol(USBH_Info_t *phost, uint8_t interface, uint8_t protocol);


#endif // __USBH_HID_CORE_H__
