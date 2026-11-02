/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-08-22     Emuzit            first version
 */
#ifndef __CH56X_USBHS_H__
#define __CH56X_USBHS_H__

#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOC_SERIES_CH569
#define UEP_ADDRESS_MAX     7
#define UEP_RT_DMA_MASK     0x1fff0
#else
#define UEP_ADDRESS_MAX     4
#define UEP_RT_DMA_MASK     0x0fffc
#endif

union _usb_ctrl
{
    uint8_t reg;
    struct
    {
        uint8_t dma_en      : 1;  // RW, USB DMA and DMA interrupt enable bit
        uint8_t clr_all     : 1;  // RW, Empty USB interrupt flag and FIFO
        uint8_t reset_sie   : 1;  // RW, Forcibly reset the USB SIE
        uint8_t int_busy    : 1;  // RW, Auto pause enable bit @ RB_USB_IF_TRANSFER
        uint8_t pu_en       : 1;  // RW, device & pull-up-R enable, DEVICE mode
        uint8_t sptp_mask   : 2;  // RW, USB bus signal transfer rate selection bit
        uint8_t mode        : 1;  // RW, USB working mode selection bit
    };
};
#define RB_USB_DMA_EN       0x01
#define RB_USB_CLR_ALL      0x02
#define RB_USB_RESET_SIE    0x04
#define RB_USB_INT_BUSY     0x08
#define RB_DEV_PU_EN        0x10
#define RB_USB_SPTP_MASK    0x60
#define RB_USB_MODE         0x80

#define USBHS_FULL_SPEED    0
#define USBHS_HIGH_SPEED    1
#define USBHS_LOW_SPEED     2

#define USBHS_DEVICE_MODE   0
#define USBHS_HOST_MODE     1

#define RB_SPTP_FULL_SPEED  (USBHS_FULL_SPEED  << 5)
#define RB_SPTP_HIGH_SPEED  (USBHS_HIGH_SPEED  << 5)
#define RB_SPTP_LOW_SPEED   (USBHS_LOW_SPEED   << 5)

#define RB_USB_DEVICE_MODE  (USBHS_DEVICE_MODE << 7)
#define RB_USB_HOST_MODE    (USBHS_HOST_MODE   << 7)

union _usb_int_en
{
    uint8_t reg;
    struct
    {
        uint8_t busrst      : 1;  // RW, USB bus reset event IE, DEVICE mode
        uint8_t trans       : 1;  // RW, USB transfer complete interrupt enable
        uint8_t suspend     : 1;  // RW, USB bus suspend/wake-up event IE
        uint8_t sof         : 1;  // RW, SOF packet/timing interrupt enable
        uint8_t fifoov      : 1;  // RW, Internal FIFO overflow interrupt enable
#ifdef SOC_SERIES_CH569
        uint8_t setupact    : 1;  // RW, SETUP transaction complete interrupt
        uint8_t isoact      : 1;  // RW, ISOchronous token received IE
        uint8_t dev_nak     : 1;  // RW, NAK interrupt enable, DEVICE mode
#else
        uint8_t resv_5      : 1;
        uint8_t dev_nak     : 1;  // RW, NAK interrupt enable, DEVICE mode
        uint8_t dev_sof     : 1;  // RW, SOF packet received IE, DEVICE mode
#endif
    };
    struct
    {
        uint8_t detect      : 1;  // RW, USB device connect/disconnect IE, HOST mode
        uint8_t stuff_1     : 7;
    };
};
#define RB_USB_IE_BUSRST    0x01
#define RB_USB_IE_DETECT    0x01
#define RB_USB_IE_TRANS     0x02
#define RB_USB_IE_SUSPEND   0x04
#define RB_USB_IE_SOF       0x08
#define RB_USB_IE_FIFOOV    0x10

#ifdef SOC_SERIES_CH569
#define RB_USB_IE_SETUPACT  0x20
#define RB_USB_IE_ISOACT    0x40
#define RB_USB_IE_DEV_NAK   0x80
#else
#define RB_USB_IE_DEV_NAK   0x40
#define RB_USB_IE_DEV_SOF   0x80
#endif

union _usb_suspend
{
    uint8_t reg;
    struct
    {
        uint8_t resv_0      : 1;
        uint8_t dev_wakeup  : 1;  // RW, Remote wake-up control bit
        uint8_t resv_2      : 6;
    };
};
#define RB_DEV_WAKEUP      0x02

union _usb_spd_type
{
    uint8_t reg;
    struct
    {
        uint8_t speed_mask  : 2;  // RO, Actual transfer speed
        uint8_t resv_2      : 6;
    };
};
#define RB_USBSPEED_MASK    0x03  // same USBHS_FULL_SPEED...

union _usb_mis_st
{
    uint8_t reg;
    struct
    {
        uint8_t split_en    : 1;  // RO, SPLIT packet transmission enabled, HOST mode
        uint8_t attach      : 1;  // RO, USB device connection status bit, HOST mode
        uint8_t bus_suspend : 1;  // RO, USB suspend status bit
        uint8_t bus_reset   : 1;  // RO, USB bus reset status bit
        uint8_t fifo_rdy    : 1;  // RO, USB receive FIFO data ready status bit
        uint8_t sie_free    : 1;  // RO, Free status bit of USB protocol processor
        uint8_t sof_act     : 1;  // RO, SOF packet transfer status bit, HOST mode
        uint8_t sof_pres    : 1;  // RO, SOF packet presage status bit, HOST mode
    };
};
#define RB_HOST_SPLIT_EN    0x01
#define RB_USB_ATTACH       0x02
#define RB_USBBUS_SUSPEND   0x04
#define RB_USBBUS_RESET     0x08
#define RB_USB_FIFO_RDY     0x10
#define RB_USB_SIE_FREE     0x20
#define RB_USB_SOF_ACT      0x40
#define RB_USB_SOF_PRES     0x80

union _usb_int_fg
{
    uint8_t reg;
    struct
    {
        uint8_t busrst      : 1;  // RW1, USB bus reset event IF, DEVICE mode
        uint8_t transfer    : 1;  // RW1, USB transmission complete interrupt flag
        uint8_t suspend     : 1;  // RW1, USB bus suspend/wake-up event IF
        uint8_t hst_sof     : 1;  // RW1, SOF timing interrupt flag bit, HOST mode
        uint8_t fifoov      : 1;  // RW1, USB FIFO overflow interrupt flag
        uint8_t setupact    : 1;  // RW1, SETUP transaction complete IF (CH569)
        uint8_t isoact      : 1;  // RW1, ISOchronous token received IF (CH569)
        uint8_t resv_7      : 1;
    };
    struct
    {
        uint8_t detect      : 1;  // RW1, USB device connect/disconnect IF, HOST mode
        uint8_t stuff_1     : 7;
    };
};
#define RB_USB_IF_BUSRST    0x01
#define RB_USB_IF_DETECT    0x01
#define RB_USB_IF_TRANSFER  0x02
#define RB_USB_IF_SUSPEND   0x04
#define RB_USB_IF_HST_SOF   0x08
#define RB_USB_IF_FIFOOV    0x10
#define RB_USB_IF_SETUPACT  0x20
#define RB_USB_IF_ISOACT    0x40

union _usb_int_st
{
    uint8_t reg;
    struct
    {
        uint8_t host_res_mask   : 4;  // RO, Current response PID, HOST mode
        uint8_t dev_token_mask  : 2;  // RO, Current token PID, DEVICE mode
        uint8_t st_togok        : 1;  // RO, Current transmit DATA0/1 sync state
        uint8_t st_nak          : 1;  // RO, NAK response status bit, DEVICE mode
    };
    struct
    {
        uint8_t dev_endp_mask   : 4;  // RO, Current endpoint number, DEVICE mode
        uint8_t stuff_4         : 4;
    };
};
#define RB_HOST_RES_MASK    0x0f
#define RB_DEV_ENDP_MASK    0x0f
#define RB_DEV_TOKEN_MASK   0x30
#define RB_USB_ST_TOGOK     0x40
#define RB_USB_ST_NAK       0x80

#define DEV_TOKEN_OUT       0
#define DEV_TOKEN_SOF       1
#define DEV_TOKEN_IN        2
#define DEV_TOKEN_SETUP     3  // CH567/CH568

#define RB_DEV_TOKEN_OUT    (DEV_TOKEN_OUT << 4)
#define RB_DEV_TOKEN_SOF    (DEV_TOKEN_SOF << 4)
#define RB_DEV_TOKEN_IN     (DEV_TOKEN_IN  << 4)

/*
 * RB_UEPn_  RB_UEPn_  RB_UEPn_     R32_UEPn_DMA as starting address, low to high
 *  RX_EN     TX_EN    BUF_MOD
 *    0         0         x         Endpoint is disabled, UEPn_DMA not used
 *    1         0         0         1st address of RX (OUT) buffer is R32_UEPn_RX_DMA
 *    1         0         1         RB_UEP_R_TOG_MASK=0, use R32_UEPn_RX_DMA
 *                                  RB_UEP_R_TOG_MASK=1, use R32_UEPn_TX_DMA
 *    0         1         0         1st address of TX (IN) buffer is R32_UEPn_TX_DMA
 *    0         1         1         RB_UEP_T_TOG_MASK=0, use R32_UEPn_TX_DMA
 *                                  RB_UEP_T_TOG_MASK=1, use R32_UEPn_RX_DMA
 */
#define RB_UEP_BUF_MOD      0x01
#define RB_UEP_TX_EN        0x04
#define RB_UEP_RX_EN        0x08

/* UEP_MOD offset 0 */
#define RB_UEP4_BUF_MOD     0x01
#define RB_UEP4_TX_EN       0x04
#define RB_UEP4_RX_EN       0x08
#define RB_UEP1_BUF_MOD     0x10
#define RB_UEP1_TX_EN       0x40
#define RB_UEP1_RX_EN       0x80

/* UEP_MOD offset 1 */
#define RB_UEP2_BUF_MOD     0x01
#define RB_UEP2_TX_EN       0x04
#define RB_UEP2_RX_EN       0x08
#define RB_UEP3_BUF_MOD     0x10
#define RB_UEP3_TX_EN       0x40
#define RB_UEP3_RX_EN       0x80

/* UEP_MOD offset 2 */
#define RB_UEP5_BUF_MOD     0x01
#define RB_UEP5_TX_EN       0x04
#define RB_UEP5_RX_EN       0x08
#define RB_UEP6_BUF_MOD     0x10
#define RB_UEP6_TX_EN       0x40
#define RB_UEP6_RX_EN       0x80

/* UEP_MOD offset 3 */
#define RB_UEP7_BUF_MOD     0x01
#define RB_UEP7_TX_EN       0x04
#define RB_UEP7_RX_EN       0x08

/* each nibble is an ep index map : {hi_lo_nibble(1), reg_offset(3)} */
#define UEP_MOD_MAP         0x3a209180
#define uep_mod_offset(ep)  (((UEP_MOD_MAP >> (ep * 4)) & 3))
#define uep_mod_shift(ep)   (((UEP_MOD_MAP >> (ep * 4)) & 8) ? 4 : 0)

union _uep_rt_ctrl
{
    uint8_t reg;
    struct
    {
        uint8_t res_mask    : 2;  // RW, response control bits
        uint8_t res_no      : 1;  // RW, not expecting response
        uint8_t tog_mask    : 2;  // RW, transmit/expect DATAx
        uint8_t autotog     : 1;  // RW, auto DATAx toggle (not for EP0)
        uint8_t resv_6      : 2;
    };
};
#define RB_UEP_RES_MASK     0x03
#define RB_UEP_RES_NO       0x04
#define RB_UEP_TOG_MASK     0x18
#define RB_UEP_AUTOTOG      0x20

#define UEP_RES_ACK         0
#define UEP_RES_NYET        1
#define UEP_RES_NAK         2
#define UEP_RES_STALL       3

#define UEP_TOG_DATA0       0
#define UEP_TOG_DATA1       1
#define UEP_TOG_DATA2       2
#define UEP_TOG_MDATA       3

#define RB_UEP_RES_ACK      (UEP_RES_ACK   << 0)
#define RB_UEP_RES_NYET     (UEP_RES_NYET  << 0)
#define RB_UEP_RES_NAK      (UEP_RES_NAK   << 0)
#define RB_UEP_RES_STALL    (UEP_RES_STALL << 0)

#define RB_UEP_TOG_DATA0    (UEP_TOG_DATA0 << 3)
#define RB_UEP_TOG_DATA1    (UEP_TOG_DATA1 << 3)
#define RB_UEP_TOG_DATA2    (UEP_TOG_DATA2 << 3)
#define RB_UEP_TOG_MDATA    (UEP_TOG_MDATA << 3)

union _uh_rt_ctrl
{
    uint8_t reg;
    struct
    {
        uint8_t res_mask    : 2;  // RW, response control bits
        uint8_t res_no      : 1;  // RW, not expecting response
        uint8_t tog_mask    : 2;  // RW, expected DATAx
        uint8_t autotog     : 1;  // RW, auto DATAx toggle
        uint8_t data_no     : 1;  // RW, not expecting data
        uint8_t resv_7      : 1;
    };
};
#define RB_UH_RES_MASK      0x03
#define RB_UH_RES_NO        0x04
#define RB_UH_TOG_MASK      0x18
#define RB_UH_AUTOTOG       0x20
#define RB_UH_DATA_NO       0x40

#define UH_RES_ACK          0
#define UH_RES_NYET         1
#define UH_RES_NAK          2
#define UH_RES_STALL        3

#define UH_TOG_DATA0        0
#define UH_TOG_DATA1        1
#define UH_TOG_DATA2        2
#define UH_TOG_MDATA        3

#define RB_UH_RES_ACK       (UH_RES_ACK   << 0)
#define RB_UH_RES_NYET      (UH_RES_NYET  << 0)
#define RB_UH_RES_NAK       (UH_RES_NAK   << 0)
#define RB_UH_RES_STALL     (UH_RES_STALL << 0)

#define RB_UH_TOG_DATA0     (UH_TOG_DATA0 << 3)
#define RB_UH_TOG_DATA1     (UH_TOG_DATA1 << 3)
#define RB_UH_TOG_DATA2     (UH_TOG_DATA2 << 3)
#define RB_UH_TOG_MDATA     (UH_TOG_MDATA << 3)

union _uhost_ctrl
{
    uint8_t reg;
    struct
    {
        uint8_t bus_reset   : 1;  // RW, USB host transmit bus reset signal
        uint8_t bus_suspend : 1;  // RW, USB host transmit suspend signal
        uint8_t bus_resume  : 1;  // RW, wake up device when bus suspended
        uint8_t resv_3      : 4;
        uint8_t autosof_en  : 1;  // RW, Auto generate SOF packet enable (CH569)
    };
};
#define RB_UH_BUS_RESET     0x01
#define RB_UH_BUS_SUSPEND   0x02
#define RB_UH_BUS_RESUME    0x04
#define RB_UH_AUTOSOF_EN    0x80

union _uh_ep_mod
{
    uint8_t reg;
    struct
    {
        uint8_t rbuf_mod    : 1;  // RW, CH567/CH568 only
        uint8_t resv_1      : 2;
        uint8_t rx_en       : 1;  // RW, enable HOST receiver (IN)
        uint8_t tbuf_mod    : 1;  // RW, CH567/CH568 only
        uint8_t resv_5      : 1;
        uint8_t tx_en       : 1;  // RW, enable HOST transmitter (SETUP/OUT)
        uint8_t resv_7      : 1;
    };
};
#define RB_UH_RBUF_MOD      0x01
#define RB_UH_RX_EN         0x08
#define RB_UH_TBUF_MOD      0x10
#define RB_UH_TX_EN         0x40

union _uh_ep_pid
{
    uint16_t reg;
    struct
    {
        uint8_t epnum_mask  : 4;  // RW, Set endpoint number of the target device
        uint8_t token_mask  : 4;  // RW, Set the token PID packet identification
        uint8_t resv;
    };
};
#define RB_UH_EPNUM_MASK    0x0f
#define RB_UH_TOKEN_MASK    0xf0

#ifndef SOC_SERIES_CH569
union _uh_setup
{
    uint8_t reg;
    struct
    {
        uint8_t resv_0      : 6;
        uint8_t sof_en      : 1;  // WO, Auto generate SOF packet enable
        uint8_t resv_7      : 1;
    };
};
#define RB_UH_SOF_EN        0x40
#endif

/*
 * USBHS Global Registers :
 *
 * 0x00  R8_USB_CTRL:       USB control register
 * 0x02  R8_USB_INT_EN:     USB interrupt enable register
 * 0x03  R8_USB_DEV_AD:     USB addresss register
 * 0x04  R16_USB_FRAME_NO:  USBHS frame number register
 * 0x06  R8_USB_SUSPEND:    USB suspend control register
 * 0x08  R8_USB_SPD_TYPE:   USB current speed type register
 * 0x09  R8_USB_MIS_ST:     USB miscellaneous status register
 * 0x0a  R8_USB_INT_FG:     USB interrupt flag register
 * 0x0b  R8_USB_INT_ST:     USB interrpt status register
 * 0x0c  R16_USB_RX_LEN:    USB reception length register
 */

/*
 * CH565/CH569 USBHS DEVICE Related Registers :
 *
 * 0x10  R8_UEP4_1_MOD:     Endpoint 1(9) / 4(8/12) mode control register
 * 0x11  R8_UEP2_3_MOD:     Endpoint 2(10) / 3(11) mode control register
 * 0x12  R8_UEP5_6_MOD:     Endpoint 5(13) / 6(14) mode control register
 * 0x13  R8_UEP7_MOD:       Endpoint 7(15) mode control register
 * 0x14  R32_UEP0_RT_DMA:   Start address of endpoint0 buffer
 * 0x18  R32_UEP1_RX_DMA:   Start address of endpoint 1(9) receive buffer
 * 0x1c  R32_UEP2_RX_DMA:   Start address of endpoint 2(10) receive buffer
 * 0x20  R32_UEP3_RX_DMA:   Start address of endpoint 3(11) receive buffer
 * 0x24  R32_UEP4_RX_DMA:   Start address of endpoint 4(8/12) receive buffer
 * 0x28  R32_UEP5_RX_DMA:   Start address of endpoint 5(13) receive buffer
 * 0x2c  R32_UEP6_RX_DMA:   Start address of endpoint 6(14) receive buffer
 * 0x30  R32_UEP7_RX_DMA:   Start address of endpoint 7(15) receive buffer
 * 0x34  R32_UEP1_TX_DMA:   Start address of endpoint 1(9) transmit buffer
 * 0x38  R32_UEP2_TX_DMA:   Start address of endpoint 2(10) transmit buffer
 * 0x3c  R32_UEP3_TX_DMA:   Start address of endpoint 3(11) transmit buffer
 * 0x40  R32_UEP4_TX_DMA:   Start address of endpoint 4(8/12) transmit buffer
 * 0x44  R32_UEP5_TX_DMA:   Start address of endpoint 5(13) transmit buffer
 * 0x48  R32_UEP6_TX_DMA:   Start address of endpoint 6(14) transmit buffer
 * 0x4c  R32_UEP7_TX_DMA:   Start address of endpoint 7(15) transmit buffer
 * 0x50  R16_UEP0_MAX_LEN:  Endpoint 0 receive maximum length packet register
 * 0x54  R16_UEP1_MAX_LEN:  Endpoint 1(9) receive maximum length packet register
 * 0x58  R16_UEP2_MAX_LEN:  Endpoint 2(10) receive maximum length packet register
 * 0x5c  R16_UEP3_MAX_LEN:  Endpoint 3(11) receive maximum length packet register
 * 0x60  R16_UEP4_MAX_LEN:  Endpoint 4(8/12) receive maximum length packet register
 * 0x64  R16_UEP5_MAX_LEN:  Endpoint 5(13) receive maximum length packet register
 * 0x68  R16_UEP6_MAX_LEN:  Endpoint 6(14) receive maximum length packet register
 * 0x6c  R16_UEP7_MAX_LEN:  Endpoint 7(15) receive maximum length packet register
 * 0x70  R16_UEP0_T_LEN:    Endpoint 0 transmission length register
 * 0x72  R8_UEP0_TX_CTRL:   Endpoint 0 transmit control register
 * 0x73  R8_UEP0_RX_CTRL:   Endpoint 0 receive control register
 * 0x74  R16_UEP1_T_LEN:    Endpoint 1(9) transmission length register
 * 0x76  R8_UEP1_TX_CTRL:   Endpoint 1(9) transmit control register
 * 0x77  R8_UEP1_RX_CTRL:   Endpoint 1(9) receive control register
 * 0x78  R16_UEP2_T_LEN:    Endpoint 2(10) transmission length register
 * 0x7a  R8_UEP2_TX_CTRL:   Endpoint 2(10) transmit control register
 * 0x7b  R8_UEP2_RX_CTRL:   Endpoint 2(10) receive control register
 * 0x7c  R16_UEP3_T_LEN:    Endpoint 3(11) transmission length register
 * 0x7e  R8_UEP3_TX_CTRL:   Endpoint 3(11) transmit control register
 * 0x7f  R8_UEP3_RX_CTRL:   Endpoint 3(11) receive control register
 * 0x80  R16_UEP4_T_LEN:    Endpoint 4(8/12) transmission length register
 * 0x82  R8_UEP4_TX_CTRL:   Endpoint 4(8/12) transmit control register
 * 0x83  R8_UEP4_RX_CTRL:   Endpoint 4(8/12) receive control register
 * 0x84  R16_UEP5_T_LEN:    Endpoint 5(13) transmission length register
 * 0x86  R8_UEP5_TX_CTRL:   Endpoint 5(13) transmit control register
 * 0x87  R8_UEP5_RX_CTRL:   Endpoint 5(13) receive control register
 * 0x88  R16_UEP6_T_LEN:    Endpoint 6(14) transmission length register
 * 0x8a  R8_UEP6_TX_CTRL:   Endpoint 6(14) transmit control register
 * 0x8b  R8_UEP6_RX_CTRL:   Endpoint 6(14) receive control register
 * 0x8c  R16_UEP7_T_LEN:    Endpoint 7(15) transmission length register
 * 0x8e  R8_UEP7_TX_CTRL:   Endpoint 7(15) transmit control register
 * 0x8f  R8_UEP7_RX_CTRL:   Endpoint 7(15) receive control register
 *
 * CH567/CH568 USBHS DEVICE Related Registers :
 *
 * 0x10  UEP4_1_MOD:        Endpoint 1/4 mode control register
 * 0x11  UEP2_3_MOD:        Endpoint 2/3 mode control register
 * 0x14  UEP0_DMA:          Endpoint 0 DMA buffer start address
 * 0x18  UEP1_DMA:          Endpoint 1 DMA buffer start address
 * 0x1c  UEP2_DMA:          Endpoint 2 DMA buffer start address
 * 0x20  UEP3_DMA:          Endpoint 3 DMA buffer start address
 * 0x24  UEP0_MAX_LEN:      Endpoint 0 receive maximum length packet register
 * 0x28  UEP1_MAX_LEN:      Endpoint 1 receive maximum length packet register
 * 0x2c  UEP2_MAX_LEN:      Endpoint 2 receive maximum length packet register
 * 0x30  UEP3_MAX_LEN:      Endpoint 3 receive maximum length packet register
 * 0x34  UEP4_MAX_LEN:      Endpoint 4 receive maximum length packet register
 * 0x38  UEP0_T_LEN:        Endpoint 0 transmission length register
 * 0x3a  UEP0_TX_CTRL:      Endpoint 0 transmit control register
 * 0x3b  UEP0_RX_CTRL:      Endpoint 0 receive control register
 * 0x3c  UEP1_T_LEN:        Endpoint 1 transmission length register
 * 0x3e  UEP1_TX_CTRL:      Endpoint 1 transmit control register
 * 0x3f  UEP1_RX_CTRL:      Endpoint 1 receive control register
 * 0x40  UEP2_T_LEN:        Endpoint 2 transmission length register
 * 0x42  UEP2_TX_CTRL:      Endpoint 2 transmit control register
 * 0x43  UEP2_RX_CTRL:      Endpoint 2 receive control register
 * 0x44  UEP2_T_LEN:        Endpoint 3 transmission length register
 * 0x46  UEP2_TX_CTRL:      Endpoint 3 transmit control register
 * 0x47  UEP2_RX_CTRL:      Endpoint 3 receive control register
 * 0x48  UEP4_T_LEN:        Endpoint 4 transmission length register
 * 0x4a  UEP4_TX_CTRL:      Endpoint 4 transmit control register
 * 0x4b  UEP4_RX_CTRL:      Endpoint 4 receive control register
 */

/*
 * CH565/CH569 USBHS HOST Related Registers :
 *
 * 0x01  R8_UHOST_CTRL:     USB host control register
 * 0x11  R8_UH_EP_MOD:      USB host endpoint mode register
 * 0x1c  R32_UH_RX_DMA:     USB host receive buffer start address
 * 0x3c  R32_UH_TX_DMA:     USB host transmit buffer start address
 * 0x58  R16_UH_MAX_LEN:    USB host reception maximum length packet register
 * 0x78  R16_UH_EP_PID:     USB host token setting register
 * 0x7b  R8_UH_RX_CTRL:     USB host reception endpoint control register
 * 0x7c  R16_UH_TX_LEN:     USB host transmission length register
 * 0x7e  R8_UH_TX_CTRL:     USB host transmission endpoint control register
 * 0x80  R16_UH_SPLIT_DATA: USB host transmit SPLIT packet data
 *
 * CH567/CH568 USBHS HOST Related Registers :
 *
 * 0x01  UHOST_CTRL:        USB host control register
 * 0x11  UH_EP_MOD:         USB host endpoint mode register
 * 0x1c  UH_RX_DMA:         USB host receive buffer start address
 * 0x20  UH_TX_DMA:         USB host transmit buffer start address
 * 0x2c  UH_RX_MAX_LEN:     USB host reception maximum length packet register
 * 0x3e  UH_SETUP:          USB host aux config register
 * 0x40  UH_EP_PID:         USB host token setting register
 * 0x43  UH_RX_CTRL:        USB host reception endpoint control register
 * 0x44  UH_TX_LEN:         USB host transmission length register
 * 0x46  UH_TX_CTRL:        USB host transmission endpoint control register
 * 0x48  UH_SPLIT_DATA:     USB host transmit SPLIT packet data
 */
struct usbhs_registers
{
    union
    {
        /* USB Global Registers */
        struct
        {
            union _usb_ctrl         CTRL;
            uint8_t                 stuff_01;
            union _usb_int_en       INT_EN;
            uint8_t                 DEV_AD;
            uint16_t                FRAME_NO;
            union _usb_suspend      SUSPEND;
            uint8_t                 resv_07;
            union _usb_spd_type     SPD_TYPE;
            union _usb_mis_st       MIS_ST;
            union _usb_int_fg       INT_FG;
            union _usb_int_st       INT_ST;
            uint16_t                RX_LEN;
        };

        /* USB DEVICE Related Registers */
        struct
        {
            uint32_t                stuff_gr[4];
            union
            {
                uint8_t             UEP_MOD[4];
                uint32_t            R32_UEP_MOD;
            };
#ifdef SOC_SERIES_CH569
            union
            {
                struct
                {
                    uint32_t        UEP0_RT_DMA;
                    uint32_t        stuff_rt[14];
                };
                struct
                {
                    uint32_t        UEP_RX_DMA[8];  // UEP_RX_DMA[0] NOT exist
                    uint32_t        stuff_rx[7];
                };
                struct
                {
                    uint32_t        stuff_tx[7];
                    uint32_t        UEP_TX_DMA[8];  // UEP_TX_DMA[0] NOT exist
                };
            };
#else
            struct
            {
                uint16_t            reg;
                uint16_t            resv;
            }                       UEP_DMA[4];
#endif
            struct
            {
                uint16_t            reg;
                uint16_t            resv;
            }                       UEP_MAX_LEN[UEP_ADDRESS_MAX + 1];
            struct
            {
                uint16_t            t_len;    // MSB 5 bits are fixed to 0
                union _uep_rt_ctrl  TX_CTRL;
                union _uep_rt_ctrl  RX_CTRL;
            }                       UEP_CTRL[UEP_ADDRESS_MAX + 1];
        };

        /* USB HOST Related Registers */
#ifdef SOC_SERIES_CH569
        struct
        {
            uint8_t                 stuff_00;
            union _uhost_ctrl       UHOST_CTRL;
            uint8_t                 stuff_02[15];
            union _uh_ep_mod        UH_EP_MOD;
            uint8_t                 stuff_12[10];
            uint32_t                UH_RX_DMA;
            uint32_t                stuff_20[7];
            uint32_t                UH_TX_DMA;
            uint32_t                stuff_40[6];
            uint16_t                UH_MAX_LEN;
            uint16_t                stuff_5a[15];
            union _uh_ep_pid        UH_EP_PID;
            uint8_t                 stuff_7a;
            union _uh_rt_ctrl       UH_RX_CTRL;
            uint16_t                UH_TX_LEN;
            union _uh_rt_ctrl       UH_TX_CTRL;
            uint8_t                 stuff_7f;
            uint16_t                UH_SPLIT_DATA;
            uint16_t                stuff_82[7];
        };
#else
        struct
        {
            uint8_t                 stuff_00;
            union _uhost_ctrl       UHOST_CTRL;
            uint8_t                 stuff_02[15];
            union _uh_ep_mod        UH_EP_MOD;
            uint8_t                 stuff_12[10];
            uint32_t                UH_RX_DMA;
            uint32_t                UH_TX_DMA;
            uint32_t                stuff_24[2];
            uint16_t                UH_MAX_LEN;
            uint16_t                stuff_2e[8];
            uint8_t                 UH_SETUP;
            uint8_t                 stuff_3f;
            union _uh_ep_pid        UH_EP_PID;
            uint8_t                 stuff_42;
            union _uh_rt_ctrl       UH_RX_CTRL;
            uint16_t                UH_TX_LEN;
            union _uh_rt_ctrl       UH_TX_CTRL;
            uint8_t                 stuff_47;
            uint16_t                UH_SPLIT_DATA;
            uint16_t                stuff_4a;
        };
#endif
    };
} __packed;

#ifdef SOC_SERIES_CH569
CHECK_STRUCT_SIZE(struct usbhs_registers, 0x90);
#else
CHECK_STRUCT_SIZE(struct usbhs_registers, 0x4c);
#endif

rt_inline void _uep_mod_set(volatile struct usbhs_registers *usbhs,
                            int ep_idx, uint8_t mod)
{
    int reg_n = uep_mod_offset(ep_idx);
    int shift = uep_mod_shift(ep_idx);
    int mask = 0x0f << shift;

    /* ep_idx must be 1 ~ UEP_ADDRESS_MAX */
    usbhs->UEP_MOD[reg_n] = (usbhs->UEP_MOD[reg_n] & ~mask) | (mod << shift);
}

rt_inline uint8_t _uep_mod_get(volatile struct usbhs_registers *usbhs, int ep_idx)
{
    int reg_n = uep_mod_offset(ep_idx);
    int shift = uep_mod_shift(ep_idx);

    /* ep_idx should be 1 ~ UEP_ADDRESS_MAX */
    return (usbhs->UEP_MOD[reg_n] >> shift) & 0x0f;
}

#ifdef __cplusplus
}
#endif

#endif
