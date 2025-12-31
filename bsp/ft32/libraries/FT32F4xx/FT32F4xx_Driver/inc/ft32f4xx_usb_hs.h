/**
  ******************************************************************************
  * @file    			ft32f4xx_usb_hs.h
  * @author  			FMD XA
  * @brief   			This file contains all the functions prototypes for the USB_OTG_FS
  *          >>->-and USB_OTG_HS firmware library.
  * @version 			V1.0.0           
  * @data		 			2025-03-20
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_USB_HS_H
#define __FT32F4XX_USB_HS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

#if defined (USB_OTG_HS)
/** @addtogroup ft32f4xx  Drive
  * @
  */

/** @addtogroup USB_OTG_HS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
#ifndef USB_TIMEOUT
#define USB_TIMEOUT                                0xF000000U
#endif /* define USB_TIMEOUT */

#ifndef USB_HS_CURRENT_MODE_MAX_DELAY_MS
#define USB_HS_CURRENT_MODE_MAX_DELAY_MS              200U
#endif /* define USB_HS_CURRENT_MODE_MAX_DELAY_MS */


/* compile define */
//struct __attribute__((packed)) T_UINT32_READ{
//  uint32_t v;
//};
//#define __UNALIGNED_UINT32_READ(addr) (((const struct T_UINT32_READ *)(const void *)(addr))->v)

//struct __attribute__((packed)) T_UINT32_WRITE{
//  uint32_t v;
//};
//#define __UNALIGNED_UINT32_WRITE(addr, val) (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))

#if !defined(UNUSED)
#define UNUSED(x) (void)x     /* to avoid gcc/g++ warnings */
#endif  /* UNUSED */

/**
  * @brief  USB Mode definition
  */

typedef enum
{
  USB_DEVICE_MODE  = 0,
  USB_HOST_MODE    = 1,
  USB_DRD_MODE     = 2
} USB_ModeTypeDef;

/**
  * @brief  URB States definition
  * URB : USB Request Block
  */
typedef enum
{
  URB_IDLE = 0,
  URB_DONE,
  URB_NOTREADY,
  URB_NYET,
  URB_ERROR,
  URB_STALL
} USB_OTG_HS_URBStateTypeDef;

/**
  * @brief  Host channel States  definition
  */
typedef enum
{
  HC_IDLE = 0,
  HC_XFRC,
  HC_HALTED,
  HC_ACK,
  HC_NAK,
  HC_NYET,
  HC_STALL,
  HC_XACTERR,
  HC_BBLERR,
  HC_DATATGLERR
} USB_OTG_HS_HCStateTypeDef;

/**
  * @brief  USB OTG Initialization Structure definition
  */
typedef struct
{
  uint32_t dev_endpoints;           /*!< Device Endpoints number.
                                         This parameter depends on the used USB core.
                                         This parameter must be a number between Min_Data = 1 and Max_Data = 15 */

  uint32_t Host_channels;           /*!< Host Channels number.
                                         This parameter Depends on the used USB core.
                                         This parameter must be a number between Min_Data = 1 and Max_Data = 15 */

  uint32_t speed;                   /*!< USB Core speed.
                                         This parameter can be any value of @ref USB_Core_Speed_                */

  uint32_t dma_enable;              /*!< Enable or disable of the USB embedded DMA used only for OTG HS.        */

  uint32_t ep0_mps;                 /*!< Set the Endpoint 0 Max Packet size.                                    */

  uint32_t low_power_enable;        /*!< Enable or disable the low power mode.                                  */

  uint32_t bvalid_override_enable;  /*!< Enable or disable the bvalid value override feature.                   */

  uint32_t use_dedicated_ep1;       /*!< Enable or disable the use of the dedicated EP1 interrupt.              */

} USB_OTG_HS_CfgTypeDef;

typedef struct
{
  uint8_t   num;                  /*!< Endpoint number
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 15   */

  uint8_t   is_in;                /*!< Endpoint direction
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint8_t   is_stall;             /*!< Endpoint stall condition
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint8_t   is_iso_incomplete;    /*!< Endpoint isoc condition
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint8_t   type;                 /*!< Endpoint type
                                       This parameter can be any value of @ref USB_LL_EP_Type                   */

  uint8_t   data_pid_start;       /*!< Initial data PID
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint8_t   even_odd_frame;       /*!< IFrame parity
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint16_t  tx_fifo_num;          /*!< Transmission FIFO number
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 15   */

  uint32_t  maxpacket;            /*!< Endpoint Max packet size
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 64KB */

  uint8_t   *xfer_buff;           /*!< Pointer to transfer buffer                                               */

  uint32_t  dma_addr;             /*!< 32 bits aligned transfer buffer address                                  */

  uint32_t  xfer_len;             /*!< Current transfer length                                                  */

  uint32_t  xfer_count;           /*!< Partial transfer length in case of multi packet transfer                 */

  uint32_t  xfer_size;            /*!< Requested transfer size                                                  */
} USB_OTG_HS_EPTypeDef;

typedef struct
{
  uint8_t   dev_addr;           /*!< USB device address.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 255    */

  uint8_t   ch_num;             /*!< Host channel number.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 15     */

  uint8_t   ep_num;             /*!< Endpoint number.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 15     */

  uint8_t   ep_is_in;           /*!< Endpoint direction
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   speed;              /*!< USB Host Channel speed.
                                     This parameter can be any value of @ref USB_Core_Speed_                    */

  uint8_t   do_ping;            /*!< Enable or disable the use of the PING protocol for HS mode.                */
  uint8_t   do_ssplit;          /*!< Enable start split transaction in HS mode.                                 */
  uint8_t   do_csplit;          /*!< Enable complete split transaction in HS mode.                              */
  uint8_t   ep_ss_schedule;     /*!< Enable periodic endpoint start split schedule.                             */
  uint8_t   iso_splt_xactPos;   /*!< iso split transfer transaction position.                                   */

  uint8_t   hub_port_nbr;       /*!< USB HUB port number                                                        */
  uint8_t   hub_addr;           /*!< USB HUB address                                                            */

  uint8_t   ep_type;            /*!< Endpoint Type.
                                     This parameter can be any value of @ref USB_EP_Type                        */

  uint16_t  max_packet;         /*!< Endpoint Max packet size.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 64KB   */

  uint8_t   data_pid;           /*!< Initial data PID.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   *xfer_buff;         /*!< Pointer to transfer buffer.                                                */

  uint32_t  XferSize;           /*!< OTG Channel transfer size.                                                 */

  uint32_t  xfer_len;           /*!< Current transfer length.                                                   */

  uint32_t  xfer_count;         /*!< Partial transfer length in case of multi packet transfer.                  */

  uint8_t   toggle_in;          /*!< IN transfer current toggle flag.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   toggle_out;         /*!< OUT transfer current toggle flag
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint32_t  dma_addr;           /*!< 32 bits aligned transfer buffer address.                                   */

  uint32_t  ErrCnt;             /*!< Host channel error count.                                                  */
  uint32_t  NyetErrCnt;         /*!< Complete split NYET Host channel error count.                              */

  USB_OTG_HS_URBStateTypeDef urb_state;  /*!< URB state.
                                            This parameter can be any value of @ref USB_OTG_URBStateTypeDef     */

  USB_OTG_HS_HCStateTypeDef state;       /*!< Host Channel state.
                                            This parameter can be any value of @ref USB_OTG_HCStateTypeDef      */
} USB_OTG_HS_HCTypeDef;


/**
  *@brief USB_HS status structures definition
  */
typedef enum
{
  USB_HS_OK       = 0x00U,
  USB_HS_ERROR    = 0x01U,
  USB_HS_BUSY     = 0x02U,
  USB_HS_TIMEOUT  = 0x03U
} USB_HS_StatusTypeDef;

/**
  *@brief USB_HS lock status structures definition
  */
typedef enum
{
  USB_HS_UNLOCKED  = 0x00U,
  USB_HS_LOCKED    = 0x01U,
} USB_HS_LockTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup PCD_Exported_Constants PCD Exported Constants
  * @{
  */

#if defined (USB_OTG_HS)

/** @defgroup USB Core Mode
  * @{
  */
#define USB_OTG_MODE_DEVICE                    0U
#define USB_OTG_MODE_HOST                      1U
#define USB_OTG_MODE_DRD                       2U
/**
  * @}
  */

/** @defgroup USB Device Speed
  * @{
  */
#define USBD_HS_SPEED                          0U
#define USBD_HSINFS_SPEED                      1U
#define USBH_HS_SPEED                          0U
#define USBD_FS_SPEED                          2U
#define USBH_FSLS_SPEED                        1U
/**
  * @}
  */

/** @defgroup USB_Core_Speed USB Low Layer Core Speed
  * @{
  */
#define USB_OTG_SPEED_HIGH                     0U
#define USB_OTG_SPEED_HIGH_IN_FULL             1U
/**
  * @}
  */

#if !defined (USB_HS_PHYC_TUNE_VALUE)
#define USB_HS_PHYC_TUNE_VALUE                 0x00000F13U  /* value of USB HS PHY Tune  waiting for update */
#endif  /* USB_HS_PHYC_TUNE_VALUE */

/** @defgroup USB_Turnaround_Timeout Turnaround Timeout Value
  * @{
  */
#ifndef USBD_HS_TRDT_VALUE
#define USBD_HS_TRDT_VALUE                     9U
#endif /* USBD_HS_TRDT_VALUE */
#ifndef USBD_FS_TRDT_VALUE
#define USBD_FS_TRDT_VALUE                     5U
#define USBD_DEFAULT_TRDT_VALUE                9U
#endif /* USBD_HS_TRDT_VALUE */
/**
  * @}
  */

/** @defgroup USB_Core_MPS USB Low Layer Core MPS
  * @{
  */
#define USB_OTG_HS_MAX_PACKET_SIZE           512U
#define USB_OTG_FS_MAX_PACKET_SIZE            64U
#define USB_OTG_MAX_EP0_SIZE                  64U
/**
  * @}
  */

/** @defgroup USB_Core_PHY_Frequency USB Low Layer Core PHY Frequency
  * @{
  */
#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ     (0U << 1)
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ     (1U << 1)
/**
  * @}
  */

/** @defgroup USB_CORE_Frame_Interval USB Low Layer Core Frame Interval
  * @{
  */
#define DCFG_FRAME_INTERVAL_80                 0U
#define DCFG_FRAME_INTERVAL_85                 1U
#define DCFG_FRAME_INTERVAL_90                 2U
#define DCFG_FRAME_INTERVAL_95                 3U
/**
  * @}
  */
#endif  /* USB_OTG_HS */
/** @defgroup USB_EP0_MPS USB Low Layer EP0 MPS
  * @{
  */
#define EP_MPS_64                        0U
#define EP_MPS_32                        1U
#define EP_MPS_16                        2U
#define EP_MPS_8                         3U
/**
  * @}
  */

/** @defgroup USB_EP_Speed USB Low Layer EP Speed
  * @{
  */
#define EP_SPEED_LOW                           0U
#define EP_SPEED_FULL                          1U
#define EP_SPEED_HIGH                          2U
/**
  * @}
  */

/** @defgroup USB_EP_Type USB Low Layer EP Type
  * @{
  */
#define EP_TYPE_CTRL                           0U
#define EP_TYPE_ISOC                           1U
#define EP_TYPE_BULK                           2U
#define EP_TYPE_INTR                           3U
#define EP_TYPE_MSK                            3U
/**
  * @}
  */
#if defined (USB_OTG_HS)
/** @defgroup USB_STS_Defines USB Low Layer STS Defines
  * @{
  */
#define STS_GOUT_NAK                           1U
#define STS_DATA_UPDT                          2U
#define STS_XFER_COMP                          3U
#define STS_SETUP_COMP                         4U
#define STS_SETUP_UPDT                         6U
/**
  * @}
  */

/** @defgroup USB_HCFG_SPEED_Defines USB Low Layer HCFG Speed Defines
  * @{
  */
#define HCFG_30_60_MHZ                         0U
#define HCFG_48_MHZ                            1U
#define HCFG_6_MHZ                             2U
/**
  * @}
  */

/** @defgroup USB_HFIR_Defines USB Low Layer frame interval Defines
  * @{
  */
#define HFIR_60_MHZ                            60000U
#define HFIR_48_MHZ                            48000U
#define HFIR_6_MHZ                             6000U
/**
  * @}
  */

/** @defgroup USB_HPRT0_PRTSPD_SPEED_Defines USB Low Layer HPRT0 PRTSPD Speed Defines
  * @{
  */
#define HPRT0_PRTSPD_HIGH_SPEED                0U
#define HPRT0_PRTSPD_FULL_SPEED                1U
#define HPRT0_PRTSPD_LOW_SPEED                 2U
/**
  * @}
  */

#define HCCHAR_CTRL                            0U
#define HCCHAR_ISOC                            1U
#define HCCHAR_BULK                            2U
#define HCCHAR_INTR                            3U

#define HC_PID_DATA0                           0U
#define HC_PID_DATA2                           1U
#define HC_PID_DATA1                           2U
#define HC_PID_SETUP                           3U

#define GRXSTS_PKTSTS_IN                       2U
#define GRXSTS_PKTSTS_IN_XFER_COMP             3U
#define GRXSTS_PKTSTS_DATA_TOGGLE_ERR          5U
#define GRXSTS_PKTSTS_CH_HALTED                7U

#define CLEAR_INTERRUPT_MASK                   0xFFFFFFFFU
#define HC_MAX_PKT_CNT                         256U
#define ISO_SPLT_MPS                           188U

#define HCSPLT_BEGIN                          1U
#define HCSPLT_MIDDLE                         2U
#define HCSPLT_END                            3U
#define HCSPLT_FULL                           4U

#define TEST_J                                 1U
#define TEST_K                                 2U
#define TEST_SE0_NAK                           3U
#define TEST_PACKET                            4U
#define TEST_FORCE_EN                          5U

#define USB_HS_PCGCCTL    *(__IO uint32_t *)((uint32_t)OTG_HS_BASE + USB_OTG_HS_PCGCCTL_BASE)
#define USB_HS_HPRT0      *(__IO uint32_t *)((uint32_t)OTG_HS_BASE + USB_OTG_HS_HOST_PORT_BASE)

#define USB_HS_DEVICE     ((USB_OTG_HS_DeviceTypeDef *)(OTG_HS_BASE + USB_OTG_HS_DEVICE_BASE))
#define USB_HS_INEP(i)    ((USB_OTG_HS_INEndpointTypeDef *)(OTG_HS_BASE + USB_OTG_HS_IN_ENDPOINT_BASE\
                                                          + ((i) * USB_OTG_HS_EP_REG_SIZE)))
#define USB_HS_OUTEP(i)   ((USB_OTG_HS_OUTEndpointTypeDef *)(OTG_HS_BASE + USB_OTG_HS_OUT_ENDPOINT_BASE\
                                                          + ((i) * USB_OTG_HS_EP_REG_SIZE)))
#define USB_HS_DFIFO(i)   *(__IO uint32_t *)(OTG_HS_BASE + USB_OTG_HS_FIFO_BASE + ((i) * USB_OTG_HS_FIFO_SIZE))

#define USB_HS_HOST       ((USB_OTG_HS_HostTypeDef *)(OTG_HS_BASE + USB_OTG_HS_HOST_BASE))
#define USB_HS_HC(i)      ((USB_OTG_HS_HostChannelTypeDef *)(OTG_HS_BASE + USB_OTG_HS_HOST_CHANNEL_BASE \
                                                          + ((i) * USB_OTG_HS_HOST_CHANNEL_SIZE)))


#define USB_HS_PKEY       *(__IO uint32_t *)((uint32_t)OTG_HS_BASE + USB_OTG_HS_PKEY_BASE)
#define USB_HS_PREG       *(__IO uint32_t *)((uint32_t)OTG_HS_BASE + USB_OTG_HS_PREG_BASE)


#endif /* defined (USB_OTG_HS) */

#define EP_ADDR_MSK                          0xFU

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup USB_Exported_Macros USB Low Layer Exported Macros
  * @{
  */
#if defined (USB_OTG_HS)
#define USB_HS_MASK_INTERRUPT(__INTERRUPT__)     (USB_HS->GINTMSK &= ~(__INTERRUPT__))
#define USB_HS_UNMASK_INTERRUPT(__INTERRUPT__)   (USB_HS->GINTMSK |= (__INTERRUPT__))

#define CLEAR_IN_EP_INTR(__EPNUM__, __INTERRUPT__)          (USB_HS_INEP(__EPNUM__)->DIEPINT = (__INTERRUPT__))
#define CLEAR_OUT_EP_INTR(__EPNUM__, __INTERRUPT__)         (USB_HS_OUTEP(__EPNUM__)->DOEPINT = (__INTERRUPT__))

#define __USB_HS_LOCK(__HANDLE__)                                               \
                              do{                                             \
                                  if((__HANDLE__)->Lock == USB_HS_LOCKED)       \
                                  {                                           \
                                    return USB_HS_BUSY;                         \
                                  }                                           \
                                  else                                        \
                                  {                                           \
                                    (__HANDLE__)->Lock = USB_HS_LOCKED;         \
                                  }                                           \
                                }while (0U)

#define __USB_HS_UNLOCK(__HANDLE__)                                               \
                                do{                                             \
                                    (__HANDLE__)->Lock = USB_HS_UNLOCKED;         \
                                  }while (0U)

#endif /* defined (USB_OTG_HS) */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup USB_HS_Exported_Functions USB Low Layer Exported Functions
  * @{
  */
#if defined (USB_OTG_HS)
void USB_HS_Delayms(uint32_t num);
USB_HS_StatusTypeDef USB_HS_CoreInit(USB_OTG_HS_CfgTypeDef cfg);
USB_HS_StatusTypeDef USB_HS_DevInit(USB_OTG_HS_CfgTypeDef cfg);
void                 USB_HS_EnableGlobalInt(void);
void                 USB_HS_DisableGlobalInt(void);
void                 USB_HS_SetTurnaroundTime(uint32_t hclk, uint8_t speed);
USB_HS_StatusTypeDef USB_HS_SetCurrentMode(USB_ModeTypeDef mode);
void                 USB_HS_SetDevSpeed(uint8_t speed);
USB_HS_StatusTypeDef USB_HS_FlushRxFifo(void);
USB_HS_StatusTypeDef USB_HS_FlushTxFifo(uint32_t num);
void                 USB_HS_ActivateEndpoint(USB_OTG_HS_EPTypeDef *ep);
void                 USB_HS_DeactivateEndpoint(USB_OTG_HS_EPTypeDef *ep);
void                 USB_HS_ActivateDedicatedEndpoint(USB_OTG_HS_EPTypeDef *ep);
void                 USB_HS_DeactivateDedicatedEndpoint(USB_OTG_HS_EPTypeDef *ep);
void                 USB_HS_EPStartXfer(USB_OTG_HS_EPTypeDef *ep, uint8_t dma);
void                 USB_HS_WritePacket(uint8_t *src, uint8_t ch_ep_num, uint16_t len, uint8_t dma);
void                *USB_HS_ReadPacket(uint8_t *dest, uint16_t len);
void                 USB_HS_EPSetStall(USB_OTG_HS_EPTypeDef *ep);
void                 USB_HS_EPClearStall(USB_OTG_HS_EPTypeDef *ep);
USB_HS_StatusTypeDef USB_HS_EPStopXfer(USB_OTG_HS_EPTypeDef *ep);
void                 USB_HS_SetDevAddress(uint8_t address);
void                 USB_HS_DevConnect(void);
void                 USB_HS_DevDisconnect(void);
USB_HS_StatusTypeDef USB_HS_StopDevice(void);
void                 USB_HS_ActivateSetup(void);
USB_HS_StatusTypeDef USB_HS_EP0_OutStart(uint8_t dma, uint8_t *psetup);
uint8_t              USB_HS_GetDevSpeed(void);
uint32_t             USB_HS_GetMode(void);
uint32_t             USB_HS_ReadInterrupts(void);
uint32_t             USB_HS_ReadChInterrupts(uint8_t chnum);
uint32_t             USB_HS_ReadDevAllOutEpInterrupt(void);
uint32_t             USB_HS_ReadDevOutEPInterrupt(uint8_t epnum);
uint32_t             USB_HS_ReadDevAllInEpInterrupt(void);
uint32_t             USB_HS_ReadDevInEPInterrupt(uint8_t epnum);
void                 USB_HS_ClearInterrupts(uint32_t interrupt);

USB_HS_StatusTypeDef USB_HS_HostInit(USB_OTG_HS_CfgTypeDef cfg);
USB_HS_StatusTypeDef USB_HS_InitFSLSPClkSel(uint8_t freq);
void                 USB_HS_ResetPort(void);
void                 USB_HS_DriveVbus(uint8_t state);
uint32_t             USB_HS_GetHostSpeed(void);
uint32_t             USB_HS_GetCurrentFrame(void);
USB_HS_StatusTypeDef USB_HS_HC_Init(uint8_t ch_num, uint8_t epnum, uint8_t dev_address,
                                    uint8_t speed, uint8_t ep_type, uint16_t mps);
void                 USB_HS_HC_StartXfer(USB_OTG_HS_HCTypeDef *hc, uint8_t dma);
uint32_t             USB_HS_HC_ReadInterrupt(void);
void                 USB_HS_HC_Halt(uint8_t hc_num);
void                 USB_HS_DoPing(uint8_t ch_num);
USB_HS_StatusTypeDef USB_HS_StopHost(void);
void                 USB_HS_ActivateRemoteWakeup(void);
void                 USB_HS_DeActivateRemoteWakeup(void);
void                 USB_HS_DriveID(uint8_t state);
#endif /* defined (USB_OTG_HS) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (USB_OTG_HS) */

#ifdef __cplusplus
}
#endif


#endif /* FT32F4xx_USB_HS_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
