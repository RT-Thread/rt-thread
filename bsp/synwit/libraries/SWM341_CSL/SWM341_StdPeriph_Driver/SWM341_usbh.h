#ifndef __SWM341_USBH_H__
#define __SWM341_USBH_H__

#include <stdint.h>


typedef enum {
    USBR_ACK = 0,
    USBR_ERR_CRC,
    USBR_ERR_STUFF,
    USBR_ERR_TOGGLE,
    USBR_STALL,
    USBR_TIMEOUT,
    USBR_ERR_PID,           // PID CHECK FAILED
    USBR_UNEXPECTED_PID,
    USBR_DATA_OVERRUN,
    USBR_DATA_UNDERRUN,
    USBR_NAK,
    USBR_FRAME_OVERRUN,
    USBR_BUFFER_OVERRUN,
    USBR_BUFFER_UNDERRUN,
    USBR_ERROR = 0xFE,
    USBR_NO = 0xFF          // 还未收到设备响应
} USBH_Resp;


void USBH_HW_Init(void);
void USBH_ResetPort(void);
uint32_t USBH_IsDeviceConnected(void);
uint32_t USBH_IsPortEnabled(void);
uint32_t USBH_GetDeviceSpeed(void);

USBH_Resp USBH_State(void);

uint32_t USBH_SendSetupPacket(uint8_t addr, uint8_t *data, uint16_t size);
uint32_t USBH_SendOutPacket(uint8_t addr, uint8_t endp, uint8_t DATAx, uint8_t *data, uint16_t size);
uint32_t USBH_SendInPacket(uint8_t addr, uint8_t endp, uint8_t DATAx, uint16_t size);

uint32_t USBH_ReadRxBuffer(uint8_t *buff, uint32_t size);


#endif // __SWM341_USBH_H__
