#ifndef __SWM341_USBD_H__
#define __SWM341_USBD_H__

#include <stdint.h>
#include <stdbool.h>

typedef void (*USBD_ClassRequest_Callback)(USB_Setup_Packet_t * pSetup);
typedef void (*USBD_VendorRequest_Callback)(USB_Setup_Packet_t * pSetup);

typedef struct {
    uint8_t  Mode;              // USBD_MODE_DEV、USBD_MODE_OTG
    uint8_t  Speed;             // USBD_SPEED_LS、USBD_SPEED_FS
    uint8_t  CtrlPkSiz;         // Control Endpoint Packet Size

    uint8_t  *DescDevice;
    uint8_t  *DescConfig;
    uint8_t **DescString;

    USBD_ClassRequest_Callback pClassRequest_Callback;
    USBD_VendorRequest_Callback pVendorRequest_Callback;

    uint8_t  *DescBOS;          // BOS descriptor

    /* HID */
    uint16_t *DescHIDOffset;    // HID描述符在DescConfig中的偏移
    uint8_t **DescHIDReport;    // HID报告描述符

    /* WINUSB */
    uint8_t  *DescOSString;     // Microsoft OS String Descriptor
} USBD_Info_t;

extern USBD_Info_t USBD_Info;


#define USBD_MODE_DEV   3       // Device only
#define USBD_MODE_OTG   0       // OTG, 主机模式还是从机模式由USB ID线决定

#define USBD_SPEED_LS   2
#define USBD_SPEED_FS   3


extern USB_Setup_Packet_t * pUSB_Setup;


static __INLINE void USBD_RxReady(uint8_t epnr)
{
    USBD->OUTEP[epnr].RXCR = USBD_RXCR_FLUSHFF_Msk;
    USBD->OUTEP[epnr].RXCR = USBD_RXCR_FFRDY_Msk;
}

static __INLINE void USBD_TxStall(uint8_t epnr)
{
    USBD->INEP[epnr &= 0x0F].TXCR |= (1 << USBD_TXCR_SNDSTALL_Pos);
}

static __INLINE void USBD_RxStall(uint8_t epnr)
{
    USBD->OUTEP[epnr &= 0x0F].RXCR |= (1 << USBD_RXCR_SNDSTALL_Pos);
}

static __INLINE void USBD_Stall0(void)
{
    USBD_TxStall(0);
    USBD_RxStall(0);
}

/* 注意：因为要读 TXSR.DATSNT 位，因此必须在 USBD_TxIntClr() 之前调用 */
static __INLINE bool USBD_TxSuccess(uint8_t epnr)
{
    uint32_t sr = USBD->INEP[epnr].TXSR;

    return (sr & USBD_TXSR_DATSNT_Msk) && (sr & USBD_TXSR_SUCC_Msk);
}

static __INLINE bool USBD_TxNAKSent(uint8_t epnr)
{
    return (USBD->INEP[epnr].TXSR & USBD_TXSR_NAKSNT_Msk);
}

static __INLINE void USBD_TxIntClr(uint8_t epnr)
{
    USBD->INEP[epnr].TXSR = USBD_TXSR_NAKSNT_Msk |
                            USBD_TXSR_DATSNT_Msk;
}

static __INLINE bool USBD_RxSuccess(void)
{
    return (USBD->RXSR & USBD_RXSR_SUCC_Msk);
}

static __INLINE void USBD_RxIntClr(void)
{
    USBD->RXSR = USBD_RXSR_DONE_Msk;
}


static __INLINE void USBD_PullUp_Enable(void)
{
    SYS->USBPHYCR &= ~SYS_USBPHYCR_OPMODE_Msk;
    SYS->USBPHYCR |= (0 << SYS_USBPHYCR_OPMODE_Pos);    //Normal Operation
}

static __INLINE void USBD_PullUp_Disable(void)
{
    SYS->USBPHYCR &= ~SYS_USBPHYCR_OPMODE_Msk;
    SYS->USBPHYCR |= (1 << SYS_USBPHYCR_OPMODE_Pos);    //Non-Driving, DP Pull-Up disable
}



void USBD_Init(void);
void USBD_Open(void);
void USBD_Close(void);
void USBD_ProcessSetupPacket(void);
void USBD_PrepareCtrlIn(uint8_t buf[], uint32_t size);
void USBD_CtrlIn(void);
void USBD_PrepareCtrlOut(uint8_t *buf, uint32_t size);
void USBD_CtrlOut(void);

void USBD_EPConfig(uint8_t ep_reg, uint8_t ep_nbr, uint8_t ep_dir, uint8_t ep_type, uint16_t ep_pksz, uint8_t cfg, uint8_t intf, uint8_t alt);

void USBD_TxWrite(uint8_t epnr, uint8_t *data, uint16_t size);
uint16_t USBD_RxRead(uint8_t *buff, uint16_t size);

void USBD_memcpy(uint8_t *destin, uint8_t *source, uint32_t nByte);

#endif //__SWM341_USBD_H__
