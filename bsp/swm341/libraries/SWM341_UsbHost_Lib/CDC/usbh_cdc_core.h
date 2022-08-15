#ifndef __USBH_CDC_CORE_H__
#define __USBH_CDC_CORE_H__

#include <stdint.h>


typedef enum {
    USBH_CDC_SEND = 0,
    USBH_CDC_SEND_WAIT,
    USBH_CDC_READ,
    USBH_CDC_READ_WAIT,
    USBH_CDC_CTRL
} USBH_CDC_State;


typedef enum {
    CDC_SET_LINE_CODING = 0x20,
    CDC_GET_LINE_CODING,
    CDC_SET_CONTROL_LINE,
    CDC_CLR_STALL,
} USBH_CDC_ReqState;


typedef struct {
  void (*Send)(uint8_t  *);
  void (*Receive)(uint8_t *);
} USBH_CDC_cb_t;


typedef struct {
    uint8_t  InEp;
    uint8_t  OutEp;
    uint16_t InEpSize;
    uint16_t OutEpSize;
    uint8_t  InEpDATAX;
    uint8_t  OutEpDATAX;

    uint8_t  CtrlEp;
    uint16_t CtrlEpSize;
    uint8_t  CtrlEpDATAX;

    USBH_CDC_State    state;
    USBH_CDC_State    stateBkp;
    USBH_CDC_ReqState reqState;

    uint8_t  TxBuff[USBH_CDC_BUFF_SIZE];
    uint8_t  RxBuff[USBH_CDC_BUFF_SIZE];
    uint16_t TxWrPtr, TxRdPtr;
    uint16_t RxWrPtr, RxRdPtr;
    uint16_t TxFrameNbr;        // Frame Number
    uint16_t RxFrameNbr;

    USBH_CDC_cb_t    *cdc_cb;
} USBH_CDC_Info_t;


extern volatile USBH_CDC_Info_t USBH_CDC_Info;



extern USBH_Class_cb_t  USBH_CDC_cb;


USBH_Status USBH_CDC_Init(USBH_Info_t *phost);
void        USBH_CDC_DeInit(USBH_Info_t *phost);
USBH_Status USBH_CDC_Request(USBH_Info_t *phost);
USBH_Status USBH_CDC_Process(USBH_Info_t *phost);


uint32_t USBH_CDC_Send(uint8_t *data, uint16_t size);
uint32_t USBH_CDC_Read(uint8_t *buff, uint16_t size);


#endif // __USBH_CDC_CORE_H__
