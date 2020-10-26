/**
  **************************************************************************************
  * @file    usb_lowlayer_api.h
  * @brief   USB library lower layer api
  * @data    11/9/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

/* Includes-------------------------------------------------------------------*/
#include "stdint.h"
#include <stdbool.h>

#ifndef __USB_LOWLAYER_API_H__
#define __USB_LOWLAYER_API_H__


/**
  * If building with a C++ compiler, make all of the definitions in this header
  * have a C binding.
  */
#ifdef __cplusplus
extern "C"
{
#endif

/* Public constants -----------------------------------------------------------*/

//*****************************************************************************
//
// The following are values that can be passed to md_usb_hosdev_int_enable() and
// md_usb_hosdev_int_disable() as the ui32Flags parameter, and are returned from
// md_usb_hosdev_int_status().
//
//*****************************************************************************
#define USB_INTCTRL_ALL         0x000003FF  // All control interrupt sources
#define USB_INTCTRL_STATUS      0x000000FF  // Status Interrupts
#define USB_INTCTRL_VBUS_ERR    0x00000080  // VBUS Error
#define USB_INTCTRL_SESSION     0x00000040  // Session Start Detected
#define USB_INTCTRL_SESSION_END 0x00000040  // Session End Detected
#define USB_INTCTRL_DISCONNECT  0x00000020  // Disconnect Detected
#define USB_INTCTRL_CONNECT     0x00000010  // Device Connect Detected
#define USB_INTCTRL_SOF         0x00000008  // Start of Frame Detected
#define USB_INTCTRL_BABBLE      0x00000004  // Babble signaled
#define USB_INTCTRL_RESET       0x00000004  // Reset signaled
#define USB_INTCTRL_RESUME      0x00000002  // Resume detected
#define USB_INTCTRL_SUSPEND     0x00000001  // Suspend detected
#define USB_INTCTRL_MODE_DETECT 0x00000200  // Mode value valid
#define USB_INTCTRL_POWER_FAULT 0x00000100  // Power Fault detected

//*****************************************************************************
//
// The following are values that can be passed to md_usb_hosdev_endpoint_int_enable()
// and md_usb_hosdev_endpoint_int_disable() as the ui32Flags parameter, and
// are returned from md_usb_hosdev_endpoint_int_status().
//
//*****************************************************************************
#define USB_INTEP_ALL           0xFFFFFFFF  // Host IN Interrupts
#define USB_INTEP_HOST_IN       0xFFFE0000  // Host IN Interrupts
#define USB_INTEP_HOST_IN_15    0x80000000  // Endpoint 15 Host IN Interrupt
#define USB_INTEP_HOST_IN_14    0x40000000  // Endpoint 14 Host IN Interrupt
#define USB_INTEP_HOST_IN_13    0x20000000  // Endpoint 13 Host IN Interrupt
#define USB_INTEP_HOST_IN_12    0x10000000  // Endpoint 12 Host IN Interrupt
#define USB_INTEP_HOST_IN_11    0x08000000  // Endpoint 11 Host IN Interrupt
#define USB_INTEP_HOST_IN_10    0x04000000  // Endpoint 10 Host IN Interrupt
#define USB_INTEP_HOST_IN_9     0x02000000  // Endpoint 9 Host IN Interrupt
#define USB_INTEP_HOST_IN_8     0x01000000  // Endpoint 8 Host IN Interrupt
#define USB_INTEP_HOST_IN_7     0x00800000  // Endpoint 7 Host IN Interrupt
#define USB_INTEP_HOST_IN_6     0x00400000  // Endpoint 6 Host IN Interrupt
#define USB_INTEP_HOST_IN_5     0x00200000  // Endpoint 5 Host IN Interrupt
#define USB_INTEP_HOST_IN_4     0x00100000  // Endpoint 4 Host IN Interrupt
#define USB_INTEP_HOST_IN_3     0x00080000  // Endpoint 3 Host IN Interrupt
#define USB_INTEP_HOST_IN_2     0x00040000  // Endpoint 2 Host IN Interrupt
#define USB_INTEP_HOST_IN_1     0x00020000  // Endpoint 1 Host IN Interrupt

#define USB_INTEP_DEV_OUT       0xFFFE0000  // Device OUT Interrupts
#define USB_INTEP_DEV_OUT_15    0x80000000  // Endpoint 15 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_14    0x40000000  // Endpoint 14 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_13    0x20000000  // Endpoint 13 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_12    0x10000000  // Endpoint 12 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_11    0x08000000  // Endpoint 11 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_10    0x04000000  // Endpoint 10 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_9     0x02000000  // Endpoint 9 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_8     0x01000000  // Endpoint 8 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_7     0x00800000  // Endpoint 7 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_6     0x00400000  // Endpoint 6 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_5     0x00200000  // Endpoint 5 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_4     0x00100000  // Endpoint 4 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_3     0x00080000  // Endpoint 3 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_2     0x00040000  // Endpoint 2 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_1     0x00020000  // Endpoint 1 Device OUT Interrupt

#define USB_INTEP_HOST_OUT      0x0000FFFE  // Host OUT Interrupts
#define USB_INTEP_HOST_OUT_15   0x00008000  // Endpoint 15 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_14   0x00004000  // Endpoint 14 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_13   0x00002000  // Endpoint 13 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_12   0x00001000  // Endpoint 12 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_11   0x00000800  // Endpoint 11 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_10   0x00000400  // Endpoint 10 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_9    0x00000200  // Endpoint 9 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_8    0x00000100  // Endpoint 8 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_7    0x00000080  // Endpoint 7 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_6    0x00000040  // Endpoint 6 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_5    0x00000020  // Endpoint 5 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_4    0x00000010  // Endpoint 4 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_3    0x00000008  // Endpoint 3 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_2    0x00000004  // Endpoint 2 Host OUT Interrupt
#define USB_INTEP_HOST_OUT_1    0x00000002  // Endpoint 1 Host OUT Interrupt

#define USB_INTEP_DEV_IN        0x0000FFFE  // Device IN Interrupts
#define USB_INTEP_DEV_IN_15     0x00008000  // Endpoint 15 Device IN Interrupt
#define USB_INTEP_DEV_IN_14     0x00004000  // Endpoint 14 Device IN Interrupt
#define USB_INTEP_DEV_IN_13     0x00002000  // Endpoint 13 Device IN Interrupt
#define USB_INTEP_DEV_IN_12     0x00001000  // Endpoint 12 Device IN Interrupt
#define USB_INTEP_DEV_IN_11     0x00000800  // Endpoint 11 Device IN Interrupt
#define USB_INTEP_DEV_IN_10     0x00000400  // Endpoint 10 Device IN Interrupt
#define USB_INTEP_DEV_IN_9      0x00000200  // Endpoint 9 Device IN Interrupt
#define USB_INTEP_DEV_IN_8      0x00000100  // Endpoint 8 Device IN Interrupt
#define USB_INTEP_DEV_IN_7      0x00000080  // Endpoint 7 Device IN Interrupt
#define USB_INTEP_DEV_IN_6      0x00000040  // Endpoint 6 Device IN Interrupt
#define USB_INTEP_DEV_IN_5      0x00000020  // Endpoint 5 Device IN Interrupt
#define USB_INTEP_DEV_IN_4      0x00000010  // Endpoint 4 Device IN Interrupt
#define USB_INTEP_DEV_IN_3      0x00000008  // Endpoint 3 Device IN Interrupt
#define USB_INTEP_DEV_IN_2      0x00000004  // Endpoint 2 Device IN Interrupt
#define USB_INTEP_DEV_IN_1      0x00000002  // Endpoint 1 Device IN Interrupt

#define USB_INTEP_0             0x00000001  // Endpoint 0 Interrupt

//*****************************************************************************
//
// The following are values that are returned from md_usb_hos_speed_get() 0r
// md_usb_dev_speed_get().
//
//*****************************************************************************
#define USB_UNDEF_SPEED         0x80000000  // Current speed is undefined
#define USB_HIGH_SPEED          0x00000002  // Current speed is High Speed
#define USB_FULL_SPEED          0x00000001  // Current speed is Full Speed
#define USB_LOW_SPEED           0x00000000  // Current speed is Low Speed

//*****************************************************************************
//
// The following are values that are returned from md_usb_hosdev_endpoint_status().  The
// USB_HOST_* values are used when the USB controller is in host mode and the
// USB_DEV_* values are used when the USB controller is in device mode.
//
//*****************************************************************************
#define USB_HOST_IN_STATUS      0x114F0000  // Mask of all host IN interrupts
#define USB_HOST_IN_PID_ERROR   0x10000000  // Stall on this endpoint received
#define USB_HOST_IN_NOT_COMP    0x01000000  // Device failed to respond
#define USB_HOST_IN_STALL       0x00400000  // Stall on this endpoint received
#define USB_HOST_IN_DATA_ERROR  0x00080000  // CRC or bit-stuff error
// (ISOC Mode)
#define USB_HOST_IN_NAK_TO      0x00080000  // NAK received for more than the
// specified timeout period
#define USB_HOST_IN_ERROR       0x00040000  // Failed to communicate with a
// device
#define USB_HOST_IN_FIFO_FULL   0x00020000  // RX FIFO full
#define USB_HOST_IN_PKTRDY      0x00010000  // Data packet ready
#define USB_HOST_OUT_STATUS     0x000000A7  // Mask of all host OUT interrupts
#define USB_HOST_OUT_NAK_TO     0x00000080  // NAK received for more than the
// specified timeout period
#define USB_HOST_OUT_NOT_COMP   0x00000080  // No response from device
// (ISOC mode)
#define USB_HOST_OUT_STALL      0x00000020  // Stall on this endpoint received
#define USB_HOST_OUT_ERROR      0x00000004  // Failed to communicate with a
// device
#define USB_HOST_OUT_FIFO_NE    0x00000002  // TX FIFO is not empty
#define USB_HOST_OUT_PKTPEND    0x00000001  // Transmit still being transmitted
#define USB_HOST_EP0_NAK_TO     0x00000080  // NAK received for more than the
// specified timeout period
#define USB_HOST_EP0_STATUS     0x00000040  // This was a status packet
#define USB_HOST_EP0_ERROR      0x00000010  // Failed to communicate with a
// device
#define USB_HOST_EP0_RX_STALL   0x00000004  // Stall on this endpoint received
#define USB_HOST_EP0_RXPKTRDY   0x00000001  // Receive data packet ready
#define USB_DEV_RX_PID_ERROR    0x01000000  // PID error in isochronous
// transfer
#define USB_DEV_RX_SENT_STALL   0x00400000  // Stall was sent on this endpoint
#define USB_DEV_RX_DATA_ERROR   0x00080000  // CRC error on the data
#define USB_DEV_RX_OVERRUN      0x00040000  // OUT packet was not loaded due to
// a full FIFO
#define USB_DEV_RX_FIFO_FULL    0x00020000  // RX FIFO full
#define USB_DEV_RX_PKT_RDY      0x00010000  // Data packet ready
#define USB_DEV_TX_NOT_COMP     0x00000080  // Large packet split up, more data
// to come
#define USB_DEV_TX_SENT_STALL   0x00000020  // Stall was sent on this endpoint
#define USB_DEV_TX_UNDERRUN     0x00000004  // IN received with no data ready
#define USB_DEV_TX_FIFO_NE      0x00000002  // The TX FIFO is not empty
#define USB_DEV_TX_TXPKTRDY     0x00000001  // Transmit still being transmitted
#define USB_DEV_EP0_SETUP_END   0x00000010  // Control transaction ended before
// Data End seen
#define USB_DEV_EP0_SENT_STALL  0x00000004  // Stall was sent on this endpoint
#define USB_DEV_EP0_IN_PKTPEND  0x00000002  // Transmit data packet pending
#define USB_DEV_EP0_OUT_PKTRDY  0x00000001  // Receive data packet ready

//*****************************************************************************
//
// The following are values that can be passed to md_usb_hos_endpoint_config_set() and
// md_usb_dev_endpoint_config_set() as the ui32Flags parameter.
//
//*****************************************************************************
#define USB_EP_AUTO_SET         0x00000001  // Auto set feature enabled
#define USB_EP_AUTO_REQUEST     0x00000002  // Auto request feature enabled
#define USB_EP_AUTO_CLEAR       0x00000004  // Auto clear feature enabled
#define USB_EP_DUAL_BUFFERING   0x00000008  // Dual buffering enabled
#define USB_EP_DMA_MODE_0       0x00000008  // Enable DMA access using mode 0
#define USB_EP_DMA_MODE_1       0x00000010  // Enable DMA access using mode 1
#define USB_EP_DIS_NYET         0x00000020  // Disable NYET response for
// high-speed Bulk and Interrupt
// endpoints in device mode.
#define USB_EP_MODE_ISOC        0x00000000  // Isochronous endpoint
#define USB_EP_MODE_BULK        0x00000100  // Bulk endpoint
#define USB_EP_MODE_INT         0x00000200  // Interrupt endpoint
#define USB_EP_MODE_CTRL        0x00000300  // Control endpoint
#define USB_EP_MODE_MASK        0x00000300  // Mode Mask
#define USB_EP_SPEED_LOW        0x00000000  // Low Speed
#define USB_EP_SPEED_FULL       0x00001000  // Full Speed
#define USB_EP_SPEED_HIGH       0x00004000  // High Speed
#define USB_EP_HOST_IN          0x00000000  // Host IN endpoint
#define USB_EP_HOST_OUT         0x00002000  // Host OUT endpoint
#define USB_EP_DEV_IN           0x00002000  // Device IN endpoint
#define USB_EP_DEV_OUT          0x00000000  // Device OUT endpoint

//*****************************************************************************
//
// The following are values that can be passed to md_usb_hos_pwr_config() as the
// ui32Flags parameter.
//
//*****************************************************************************
#define USB_HOST_PWRFLT_LOW     0x00000010
#define USB_HOST_PWRFLT_HIGH    0x00000030
#define USB_HOST_PWRFLT_EP_NONE 0x00000000
#define USB_HOST_PWRFLT_EP_TRI  0x00000140
#define USB_HOST_PWRFLT_EP_LOW  0x00000240
#define USB_HOST_PWRFLT_EP_HIGH 0x00000340
#define USB_HOST_PWREN_MAN_LOW  0x00000000
#define USB_HOST_PWREN_MAN_HIGH 0x00000001
#define USB_HOST_PWREN_AUTOLOW  0x00000002
#define USB_HOST_PWREN_AUTOHIGH 0x00000003
#define USB_HOST_PWREN_FILTER   0x00010000

//*****************************************************************************
//
// The following are the valid values that can be passed to the
// md_usb_hos_lpm_config() function in the ui32Config parameter.
//
//*****************************************************************************
#define USB_HOST_LPM_RMTWAKE    0x00000100
#define USB_HOST_LPM_L1         0x00000001

//*****************************************************************************
//
// The following are the valid values that can be passed to the
// md_usb_dev_lpm_config() function in the ui32Config parameter.
//
//*****************************************************************************
#define USB_DEV_LPM_NAK         0x00000010
#define USB_DEV_LPM_NONE        0x00000000
#define USB_DEV_LPM_EN          0x0000000c
#define USB_DEV_LPM_EXTONLY     0x00000004

//*****************************************************************************
//
// The following are the valid values that are returned from the
// md_usb_lpm_link_state_get() function.
//
//*****************************************************************************
#define USB_DEV_LPM_LS_RMTWAKE  0x00000100
#define USB_DEV_LPM_LS_L1       0x00000001

//*****************************************************************************
//
// The following are the valid values that are passed to the md_usb_lpm_int_enable()
// or md_usb_lpm_int_disable() functions or are returned from the md_usb_lpm_status()
// function.
//
//*****************************************************************************
#define USB_INTLPM_ERROR        0x00000020
#define USB_INTLPM_RESUME       0x00000010
#define USB_INTLPM_INCOMPLETE   0x00000008
#define USB_INTLPM_ACK          0x00000004
#define USB_INTLPM_NYET         0x00000002
#define USB_INTLPM_STALL        0x00000001

//*****************************************************************************
//
// The following are the valid values that are passed to the md_usb_clock_enable()
// functions.
//
//*****************************************************************************
#define USB_CLOCK_INTERNAL      0x00000200
#define USB_CLOCK_EXTERNAL      0x00000300

//*****************************************************************************
//
// The configuration options used with the md_usb_ulpi_config() API.
//
//*****************************************************************************
#define USB_ULPI_EXTVBUS        0x00000001
#define USB_ULPI_EXTVBUS_IND    0x00000002

//*****************************************************************************
//
// The following are special values that can be passed to
// md_usb_hos_endpoint_config_set() as the ui32NAKPollInterval parameter.
//
//*****************************************************************************
#define MAX_NAK_LIMIT           31          // Maximum NAK interval
#define DISABLE_NAK_LIMIT       0           // No NAK timeouts

//*****************************************************************************
//
// This value specifies the maximum size of transfers on endpoint 0 as 64
// bytes.  This value is fixed in hardware as the FIFO size for endpoint 0.
//
//*****************************************************************************
#define MAX_PACKET_SIZE_EP0     64

//*****************************************************************************
//
// These values are used to indicate which endpoint to access.
//
//*****************************************************************************
#define USB_EP_0                0x00000000  // Endpoint 0
#define USB_EP_1                0x00000010  // Endpoint 1
#define USB_EP_2                0x00000020  // Endpoint 2
#define USB_EP_3                0x00000030  // Endpoint 3
#define USB_EP_4                0x00000040  // Endpoint 4
#define USB_EP_5                0x00000050  // Endpoint 5
#define USB_EP_6                0x00000060  // Endpoint 6
#define USB_EP_7                0x00000070  // Endpoint 7
#define NUM_USB_EP              8           // Number of supported endpoints

//*****************************************************************************
//
// These macros allow conversion between 0-based endpoint indices and the
// USB_EP_x values required when calling various USB APIs.
//
//*****************************************************************************
#define IndexToUSBEP(x)         ((x) << 4)
#define USBEPToIndex(x)         ((x) >> 4)

//*****************************************************************************
//
// The following are values that can be passed to md_usb_hosdev_fifo_config_set() as the
// ui32FIFOSize parameter.
//
//*****************************************************************************
#define USB_FIFO_SZ_8           0x00000000  // 8 byte FIFO
#define USB_FIFO_SZ_16          0x00000001  // 16 byte FIFO
#define USB_FIFO_SZ_32          0x00000002  // 32 byte FIFO
#define USB_FIFO_SZ_64          0x00000003  // 64 byte FIFO
#define USB_FIFO_SZ_128         0x00000004  // 128 byte FIFO
#define USB_FIFO_SZ_256         0x00000005  // 256 byte FIFO
#define USB_FIFO_SZ_512         0x00000006  // 512 byte FIFO
#define USB_FIFO_SZ_1024        0x00000007  // 1024 byte FIFO
#define USB_FIFO_SZ_2048        0x00000008  // 2048 byte FIFO

//*****************************************************************************
//
// This macro allow conversion from a FIFO size label as defined above to
// a number of bytes
//
//*****************************************************************************
#define USBFIFOSizeToBytes(x)   (8 << (x))

//*****************************************************************************
//
// The following are values that can be passed to md_usb_hosdev_endpoint_data_send()
// as the ui32TransType parameter.
//
//*****************************************************************************
#define USB_TRANS_OUT           0x00000102  // Normal OUT transaction
#define USB_TRANS_IN            0x00000102  // Normal IN transaction
#define USB_TRANS_IN_LAST       0x0000010a  // Final IN transaction (for
// endpoint 0 in device mode)
#define USB_TRANS_SETUP         0x0000110a  // Setup transaction (for endpoint
// 0)
#define USB_TRANS_STATUS        0x00000142  // Status transaction (for endpoint
// 0)

//*****************************************************************************
//
// The following are values are returned by the md_usb_hosdev_mode_get() function.
//
//*****************************************************************************
#define USB_DUAL_MODE_HOST      0x00000001  // Dual mode controller is in Host
// mode.
#define USB_DUAL_MODE_DEVICE    0x00000081  // Dual mode controller is in
// Device mode.
#define USB_DUAL_MODE_NONE      0x00000080  // Dual mode controller mode is not
// set.
#define USB_OTG_MODE_ASIDE_HOST 0x0000001d  // OTG controller on the A side of
// the cable.
#define USB_OTG_MODE_ASIDE_NPWR 0x00000001  // OTG controller on the A side of
// the cable.
#define USB_OTG_MODE_ASIDE_SESS 0x00000009  // OTG controller on the A side of
// the cable Session Valid.
#define USB_OTG_MODE_ASIDE_AVAL 0x00000011  // OTG controller on the A side of
// the cable A valid.
#define USB_OTG_MODE_ASIDE_DEV  0x00000019  // OTG controller on the A side of
// the cable.
#define USB_OTG_MODE_BSIDE_HOST 0x0000009d  // OTG controller on the B side of
// the cable.
#define USB_OTG_MODE_BSIDE_DEV  0x00000099  // OTG controller on the B side of
// the cable.
#define USB_OTG_MODE_BSIDE_NPWR 0x00000081  // OTG controller on the B side of
// the cable.
#define USB_OTG_MODE_NONE       0x00000080  // OTG controller mode is not set.

//*****************************************************************************
//
// Channel configuration values.
//
//*****************************************************************************
#define DMA_DST_INC_8          0x00000000
#define DMA_DST_INC_16         0x40000000
#define DMA_DST_INC_32         0x80000000
#define DMA_DST_INC_NONE       0xc0000000
#define DMA_SRC_INC_8          0x00000000
#define DMA_SRC_INC_16         0x04000000
#define DMA_SRC_INC_32         0x08000000
#define DMA_SRC_INC_NONE       0x0c000000
#define DMA_SIZE_8             0x00000000
#define DMA_SIZE_16            0x11000000
#define DMA_SIZE_32            0x22000000
#define DMA_DST_PROT_PRIV      0x00200000
#define DMA_SRC_PROT_PRIV      0x00040000
#define DMA_ARB_1              0x00000000
#define DMA_ARB_2              0x00004000
#define DMA_ARB_4              0x00008000
#define DMA_ARB_8              0x0000c000
#define DMA_ARB_16             0x00010000
#define DMA_ARB_32             0x00014000
#define DMA_ARB_64             0x00018000
#define DMA_ARB_128            0x0001c000
#define DMA_ARB_256            0x00020000
#define DMA_ARB_512            0x00024000
#define DMA_ARB_1024           0x00028000
#define DMA_NEXT_USEBURST      0x00000008

//*****************************************************************************
//
// The values for the md_usb_dma_channel_int_enable() and md_usb_dma_channel_int_status()
// APIs.
//
//*****************************************************************************
#define USB_DMA_INT_CH8         0x00000080
#define USB_DMA_INT_CH7         0x00000040
#define USB_DMA_INT_CH6         0x00000020
#define USB_DMA_INT_CH5         0x00000010
#define USB_DMA_INT_CH4         0x00000008
#define USB_DMA_INT_CH3         0x00000004
#define USB_DMA_INT_CH2         0x00000002
#define USB_DMA_INT_CH1         0x00000001

//*****************************************************************************
//
// The values for the md_usb_dma_channel_status() API.
//
//*****************************************************************************
#define USB_DMA_STATUS_ERROR    0x00000100

//*****************************************************************************
//
// The valid return values for the USBDMAModeSet() and USBDMAModeGet() APIs or
// USBDMAChannelConfig().
//
//*****************************************************************************
#define USB_DMA_CFG_BURST_NONE  0x00000000
#define USB_DMA_CFG_BURST_4     0x00000200
#define USB_DMA_CFG_BURST_8     0x00000400
#define USB_DMA_CFG_BURST_16    0x00000600
#define USB_DMA_CFG_INT_EN      0x00000008
#define USB_DMA_CFG_MODE_0      0x00000000
#define USB_DMA_CFG_MODE_1      0x00000004
#define USB_DMA_CFG_DIR_RX      0x00000000
#define USB_DMA_CFG_DIR_TX      0x00000002
#define USB_DMA_CFG_EN          0x00000001

//*****************************************************************************
//
// The following are values that can be passed to md_usb_mode_config() as the
// ui3Mode parameter.
//
//*****************************************************************************
#define USB_MODE_HOST_VBUS      0x00000004
#define USB_MODE_HOST           0x00000002
#define USB_MODE_DEV_VBUS       0x00000005
#define USB_MODE_DEV            0x00000003
#define USB_MODE_OTG            0x00000000

//*****************************************************************************
//
// Flags that can be passed to DMAChannelAttributeEnable(),
// DMAChannelAttributeDisable(), and returned from DMAChannelAttributeGet().
//
//*****************************************************************************
#define DMA_ATTR_USEBURST      0x00000001
#define DMA_ATTR_ALTSELECT     0x00000002
#define DMA_ATTR_HIGH_PRIORITY 0x00000004
#define DMA_ATTR_REQMASK       0x00000008
#define DMA_ATTR_ALL           0x0000000F

/* Public functions -----------------------------------------------------------*/
/**
  * @{ SYSTEM API.
  */
extern void     md_usb_system_int_disable(void);
extern void     md_usb_system_int_enable(void);
extern void     md_usb_re_config(bool Device);  /* Weak defination */
extern void     md_usb_system_delayms(uint32_t delayms);  /* Weak defination */
extern void     md_usb_systic_disable(void);
extern void     md_usb_controller_reset(void);
extern void     md_usb_controller_enable(void);
extern void     md_usb_controller_disable(void);
extern void     md_usb_clk_phy_enable(void);
extern void     md_usb_clk_phy_disable(void);
extern uint32_t md_usb_nvic_number_get(void);
extern void     md_usb_nvic_config(uint32_t NvicNum);  /* Weak defination */
extern void     md_usb_nvic_enable(void);
extern void     md_usb_nvic_disable(void);
/**
  * @} SYSTEM API.
  */

/**
  * @{ USB basic API.
  */
/* Host Mode */
extern void     md_usb_hos_reset(bool bStart);
extern void     md_usb_hos_resume(bool bStart);
extern void     md_usb_hos_suspend(void);
extern void     md_usb_hos_request_status(void);
extern void     md_usb_hos_request_in(uint32_t ui32Endpoint);
extern void     md_usb_hos_request_in_clear(uint32_t ui32Endpoint);
extern uint32_t md_usb_hos_speed_get(void);
extern uint32_t md_usb_hos_addr_get(uint32_t ui32Endpoint, uint32_t ui32Flags);
extern void     md_usb_hos_addr_set(uint32_t ui32Endpoint,
                                    uint32_t ui32Addr,
                                    uint32_t ui32Flags);
extern uint32_t md_usb_hos_hub_addr_get(uint32_t ui32Endpoint,
                                        uint32_t ui32Flags);
extern void     md_usb_hos_hub_addr_set(uint32_t ui32Endpoint,
                                        uint32_t ui32Addr,
                                        uint32_t ui32Flags);
/* Device Mode */
extern void     md_usb_dev_addr_set(uint8_t ui32Address);
extern uint8_t  md_usb_dev_addr_get(void);
extern void     md_usb_dev_connect(void);
extern void     md_usb_dev_disconnect(void);
extern uint32_t md_usb_dev_speed_get(void);
/* Host/Device Mode */
extern uint32_t md_usb_hosdev_frame_get(void);
extern void     md_usb_hosdev_int_disable(uint32_t ui32IntFlags);
extern void     md_usb_hosdev_int_enable(uint32_t ui32IntFlags);
extern uint32_t md_usb_hosdev_int_status(void);
extern uint32_t md_usb_hosdev_mode_get(void);
/* otg Mode */
extern void     md_usb_otg_session_request(bool bStart);
extern void     md_usb_force_host_mode(void);
extern void     md_usb_force_device_mode(void);
extern void     md_usb_force_otg_mode(void);
extern void     md_usb_mode_config(uint32_t ui32Mode);
/**
  * @} USB basic API.
  */

/**
  * @{ USB endpoint API.
  */
/* Host Mode */
extern void     md_usb_hos_endpoint_config_set(uint32_t ui32Endpoint,
    uint32_t ui32MaxPacketSize,
    uint32_t ui32NAKPollInterval,
    uint32_t ui32TargetEndpoint,
    uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_data_ack(uint32_t ui32Endpoint);
extern void     md_usb_hos_endpoint_data_toggle(uint32_t ui32Endpoint,
    bool bDataToggle,
    uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_status_clear(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_speed(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_ping(uint32_t ui32Endpoint,
    bool bEnable);
/* Device Mode */
extern void     md_usb_dev_endpoint_config_set(uint32_t ui32Endpoint,
    uint32_t ui32MaxPacketSize,
    uint32_t ui32Flags);
extern void     md_usb_dev_endpoint_config_get(uint32_t ui32Endpoint,
    uint32_t *pui32MaxPacketSize,
    uint32_t *pui32Flags);
extern void     md_usb_dev_endpoint_ack(uint32_t ui32Endpoint,
                                        bool bIsLastPacket);
extern void     md_usb_dev_endpoint_stall(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
extern void     md_usb_dev_endpoint_stall_clear(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
extern void     md_usb_dev_endpoint_status_clear(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
/* Host/Device Mode */
extern uint32_t md_usb_hosdev_endpoint_datavai(uint32_t ui32Endpoint);
extern int32_t  md_usb_hosdev_endpoint_data_get(uint32_t ui32Endpoint,
    uint8_t *pui8Data, uint32_t *pui32Size);
extern int32_t  md_usb_hosdev_endpoint_data_put(uint32_t ui32Endpoint,
    uint8_t *pui8Data,
    uint32_t ui32Size);
extern int32_t  md_usb_hosdev_endpoint_data_send(uint32_t ui32Endpoint,
    uint32_t ui32TransType);
extern void     md_usb_hosdev_endpoint_data_togglec(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
extern void     md_usb_hosdev_endpoint_pkcount_set(uint32_t ui32Endpoint,
    uint32_t ui32Count);
extern uint32_t md_usb_hosdev_endpoint_status(uint32_t ui32Endpoint);
extern void     md_usb_hosdev_endpoint_int_disable(uint32_t ui32IntFlags);
extern void     md_usb_hosdev_endpoint_int_enable(uint32_t ui32IntFlags);
extern uint32_t md_usb_hosdev_endpoint_int_status(void);
extern uint32_t md_usb_endpoint_number_get(void);
/**
  * @} USB endpoint API.
  */

/**
  * @{ USB FIFO API.
  */
extern uint32_t md_usb_hosdev_fifo_addr_get(uint32_t ui32Endpoint);
extern void     md_usb_hosdev_fifo_config_get(uint32_t ui32Endpoint, uint32_t *pui32FIFOAddress,
    uint32_t *pui32FIFOSize, uint32_t ui32Flags);
extern void     md_usb_hosdev_fifo_config_set(uint32_t ui32Endpoint, uint32_t ui32FIFOAddress,
    uint32_t ui32FIFOSize, uint32_t ui32Flags);
extern void     md_usb_hosdev_fifo_flush(uint32_t ui32Endpoint, uint32_t ui32Flags);
/**
  * @} USB FIFO API.
  */

/**
  * @{ USB PWR API.it is not supported by es32f0271.
  */
extern void     md_usb_hos_pwr_disable(void);
extern void     md_usb_hos_pwr_enable(void);
extern void     md_usb_hos_pwr_config(uint32_t ui32Flags);
extern void     md_usb_hos_pwrfault_disable(void);
extern void     md_usb_hos_pwrfault_enable(void);
/**
  * @} USB PWR API.
  */

/**
  * @{  USB LPM API.it is not supported by es32f0271.
  */
extern void     md_usb_hos_lpm_send(uint32_t ui32Address,
                                    uint32_t uiEndpoint);
extern void     md_usb_hos_lpm_config(uint32_t ui32ResumeTime,
                                      uint32_t ui32Config);
extern bool     md_usb_lpm_remotewake_is_enabled(void);
extern void     md_usb_hos_lpm_resume(void);
extern void     md_usb_dev_lpm_remotewake(void);
extern void     md_usb_dev_lpm_config(uint32_t ui32Config);
extern void     md_usb_dev_lpm_enable(void);
extern void     md_usb_dev_lpm_disable(void);
extern uint32_t md_usb_lpm_link_state_get(void);
extern uint32_t md_usb_lpm_endpoint_get(void);
extern uint32_t md_usb_lpm_status(void);
extern void     md_usb_lpm_int_disable(uint32_t ui32Ints);
extern void     md_usb_lpm_int_enable(uint32_t ui32Ints);
/**
  * @} USB LPM API.
  */

/**
  * @{  USB ULPI API.it is not supported by es32f0271.
  */
extern void     md_usb_ulpi_config(uint32_t ui32Config);
extern void     md_usb_ulpi_enable(void);
extern void     md_usb_ulpi_disable(void);
extern uint8_t  md_usb_ulpi_reg_read(uint8_t ui8Reg);
extern void     md_usb_ulpi_reg_write(uint8_t ui8Reg,
                                      uint8_t ui8Data);
/**
  * @} USB ULPI API.
  */

/**
  * @{  USB DMA API.it is not supported by es32f0271.
  */
extern void     md_usb_dma_endpoint_channel_set(uint32_t ui32Endpoint,
    uint32_t ui32Channel);
extern void     md_usb_dma_endpoint_enable(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
extern void     md_usb_dma_endpoint_disable(uint32_t ui32Endpoint,
    uint32_t ui32Flags);
extern void     md_usb_dma_endpoint_config(uint32_t ui32Endpoint,
    uint32_t ui32Config);
extern void     md_usb_dma_channel_config(uint32_t ui32Channel,
    uint32_t ui32Endpoint,
    uint32_t ui32Config);
extern void     md_usb_dma_channel_address_set(uint32_t ui32Channel,
    void     *pvAddress);
extern void     *md_usb_dma_channel_address_get(uint32_t ui32Channel);
extern void     md_usb_dma_channel_count_set(uint32_t ui32Count,
    uint32_t ui32Channel);
extern uint32_t md_usb_dma_channel_count_get(uint32_t ui32Channel);
extern void     md_usb_dma_channel_int_enable(uint32_t ui32Channel);
extern void     md_usb_dma_channel_int_disable(uint32_t ui32Channel);
extern uint32_t md_usb_dma_channel_int_status(void);
extern void     md_usb_dma_channel_enable(uint32_t ui32Channel);
extern void     md_usb_dma_channel_disable(uint32_t ui32Channel);
extern uint32_t md_usb_dma_channel_isenabled(uint32_t ui32Channel);
extern uint32_t md_usb_dma_channel_status(uint32_t ui32Channel);
extern void     md_usb_dma_channel_status_clear(uint32_t ui32Channel,
    uint32_t ui32Status);
/**
  * @} USB DMA API.
  */

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics Co., Ltd. *** END OF FILE ****/
