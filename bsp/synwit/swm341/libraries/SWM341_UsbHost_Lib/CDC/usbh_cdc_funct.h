#ifndef __USBH_CDC_FUNCT_H__
#define __USBH_CDC_FUNCT_H__

#include <stdint.h>


typedef struct __attribute__((packed)) {
    uint32_t dwDTERate;     // Data terminal rate, in bits per second
    uint8_t  bCharFormat;   // Stop bits, 0 - 1 Stop bit, 1 - 1.5 Stop bits, 2 - 2 Stop bits
    uint8_t  bParityType;   // Parity, 0 - None, 1 - Odd, 2 - Even, 3 - Mark, 4 - Space
    uint8_t  bDataBits;     // Data bits (5, 6, 7, 8 or 16)
} CDC_LineCoding_t;



USBH_Status USBH_CDC_GetLineCoding(USBH_Info_t *phost);
USBH_Status USBH_CDC_SetLineCoding(USBH_Info_t *phost);
USBH_Status USBH_CDC_SetControlLine(USBH_Info_t *phost);
void USBH_CDC_IssueSetLineCoding(USBH_Info_t *phost);
void USBH_CDC_IssueGetLineCoding(USBH_Info_t *phost);


#endif // __USBH_CDC_FUNCT_H__
