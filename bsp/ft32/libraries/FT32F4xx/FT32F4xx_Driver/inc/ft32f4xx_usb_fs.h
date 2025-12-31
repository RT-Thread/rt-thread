/**
  ******************************************************************************
  * @file    			ft32f4xx_usb_fs.h
  * @author  			FMD XA
  * @brief   			This file contains all the functions prototypes for the USB_OTG_FS
  *          >>->-and USB_OTG_FS firmware library.
  * @version 			V1.0.0           
  * @data		 			2025-05-28
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_USB_FS_H
#define __FT32F4XX_USB_FS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

#if defined (USB_OTG_FS)


/* Exported types ------------------------------------------------------------*/

#ifndef BYTE
    typedef unsigned char BYTE;
#endif
#ifndef WORD
    typedef unsigned short WORD;
#endif

/**
  * @brief Register read/write macros
  */

#define READ_BYTE(addr) *((BYTE *)(addr))
#define WRITE_BYTE(addr,data) *((BYTE *)(addr)) = data


#if !defined(UNUSED)
#define UNUSED(x) (void)x     /* to avoid gcc/g++ warnings */
#endif  /* UNUSED */


/**
  * @brief  USB Mode definition
  */

typedef enum
{
  USB_FS_DEVICE_MODE  = 0,
  USB_FS_HOST_MODE    = 1,
  USB_FS_DRD_MODE     = 2
} USB_FS_ModeTypeDef;

/**
  * @brief  URB States definition
  * URB : USB Request Block
  */
typedef enum
{
  URB_IDLE = 0,
  URB_DONE,
  URB_NOTREADY,
  URB_ERROR,
  URB_STALL
} USB_OTG_FS_URBStateTypeDef;

/**
  * @brief  host endpoint state definition
  */
typedef enum
{
  EP_IDLE = 0,
  EP_XFRC,
  EP_HALTED,
  EP_ACK,
  EP_NAK,
  EP_NYET,
  EP_STALL,
  EP_XACTERR,
  EP_BBLERR,
  EP_DATATGLERR
} USB_OTG_FS_HEPStateTypeDef;

/**
  * @brief  host endpoint control state definition
  */
typedef enum
{
  CTRL_SETUP_P = 0,
  CTRL_DATA,
  CTRL_STATUS,
} USB_OTG_FS_CtlStateTypeDef;

/**
  * @brief  USB OTG Initialization Structure definition
  */
typedef struct
{
  uint32_t endpoints;               /*!< Endpoints number.
                                         This parameter depends on the used USB core.
                                         This parameter must be a number between Min_Data = 1 and Max_Data = 15 */

  uint32_t Host_eps;                /*!< Host Channels number.
                                         This parameter Depends on the used USB core.
                                         This parameter must be a number between Min_Data = 1 and Max_Data = 15 */

  uint32_t speed;                   /*!< USB Core speed.
                                         This parameter can be any value of @ref USB_Core_Speed_                */

  uint32_t ep0_mps;                 /*!< Set the Endpoint 0 Max Packet size.                                    */

  uint8_t  OTGState;                /*!< OTG State.                                                             */

} USB_OTG_FS_CfgTypeDef;

typedef struct
{
  uint8_t   dev_addr;           /*!< USB device address.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 255    */

  uint8_t   ep_num;             /*!< Host channel number.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 15     */

  uint8_t   epnum;              /*!< Endpoint number. index register value
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 15     */

  uint8_t   ep_is_in;           /*!< Endpoint direction
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   speed;              /*!< USB Host Channel speed.
                                     This parameter can be any value of @ref USB_Core_Speed_                    */

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

  uint32_t  ErrCnt;             /*!< Host channel error count.                                                  */

  uint8_t   interval;           /* host tx or rx interval/nakmit*/

  USB_OTG_FS_URBStateTypeDef urb_state;  /*!< URB state.
                                            This parameter can be any value of @ref USB_OTG_URBStateTypeDef     */

  USB_OTG_FS_HEPStateTypeDef state;       /*!< Host endpoint state.
                                            This parameter can be any value of @ref USB_OTG_HEPStateTypeDef      */
  USB_OTG_FS_CtlStateTypeDef ctrl_state;  /*control state
                                            this parameter can be any value of @ref USB_OTG_CtlStateTypeDef     */
} USB_OTG_FS_HEPTypeDef;

typedef struct
{
  uint8_t   dev_addr;           /*!< USB device address.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 255    */

  uint8_t   num;                /*!< Endpoint number.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 15     */

  uint8_t   is_in;              /*!< Endpoint direction
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   is_stall;           /*!< Endpoint stall condition
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   speed;              /*!< USB Host Channel speed.
                                     This parameter can be any value of @ref USB_Core_Speed_                    */

  uint8_t   type;               /*!< Endpoint Type.
                                     This parameter can be any value of @ref USB_EP_Type                        */

  uint16_t  maxpacket;          /*!< Endpoint Max packet size.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 64KB   */

  uint16_t  tx_fifo_num;          /*!< Transmission FIFO number
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 15   */

  uint8_t   data_pid_start;     /*!< Initial data PID.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   *xfer_buff;         /*!< Pointer to transfer buffer.                                                */

  uint32_t  xfer_size;           /*!< OTG endpoint transfer size.                                                 */

  uint32_t  xfer_len;           /*!< Current transfer length.                                                   */

  uint32_t  xfer_count;         /*!< Partial transfer length in case of multi packet transfer.                  */
} USB_OTG_FS_DEPTypeDef;

/**
  *@brief USB_FS status structures definition
  */
typedef enum
{
  USB_FS_OK       = 0x00U,
  USB_FS_ERROR    = 0x01U,
  USB_FS_BUSY     = 0x02U,
} USB_FS_StatusTypeDef;

/**
  *@brief USB_FS lock status structures definition
  */
typedef enum
{
  USB_FS_UNLOCKED  = 0x00U,
  USB_FS_LOCKED    = 0x01U,
} USB_FS_LockTypeDef;


/* Exported constants --------------------------------------------------------*/

#if defined (USB_OTG_FS)

#define VBUS_MASK                              0x70U

#define ADDR_FIFO_EP0                          OTG_FS_BASE + 0x20U

#define VBUS_BELOW_SESSION_END                 0
#define VBUS_ABOVE_SESSION_END                 1
#define VBUS_ABOVE_AVALID                      2
#define VBUS_ABOVE_VBUS_VALID                  3
#define VBUS_ERROR                             256

#define USB_FS_EPNUM                           4U  /* ep0 + ep1~3 */
#define EP0_SIZE                               64



#define AB_IDLE                                0x00
#define WAIT_VRISE                             0x01

#define A_PERIPHERAL                           0x21
#define A_WAIT_BCON                            0x22
#define A_HOST                                 0x23
#define A_SUSPEND                              0x24

#define B_PERIPHERAL                           0x11
#define B_WAIT_ACON                            0x12
#define B_HOST                                 0x13
#define B_SRP_INIT                             0x14

#define S_TRANSITION                           0x30

/* Using bitstuffing of (7/6) * 8 * bytecount : Sec 5.11.3 */
#define BitTransferTime(byte_count)            (7 * 8 * byte_count / 6)
#define USB_DELAY                              (1000L)    /* Temp : Info from HW Team reqd */
#define USB_LS_SETUP_TIME                      (1000L)    /* Temp : Info from HW Team reqd */

/* Low Speed : 1.5 MBPS -> 1 Frame = 1 msec Hence 1.5 * 1000 * 1000 / 1000 */
#define USB_LS_FRAME_BITS                      1500L

/* Full Speed : 12 MBPS -> 1 Frame = 1 msec. Hence 12 * 1000 * 1000 / 1000 */
#define USB_FS_FRAME_BITS                      12000L

/* Frame Time in Micro Sec : Max is 90 % for Low and Full SPeed 
 * 1 Frame = 1 msec = 1000 micro Sec
 * 90 % of it is    = 90 * 1000 / 100 = 900 micro sec
 */
#define USB_FRAME_MAX_USECS_ALLOC              (900L)

#define FRAME_OFFSET                           (1)
#define MAX_POLLING_INTERVAL                   (255)



/** @defgroup USB Core Mode
  * @{
  */
#define USB_OTG_MODE_DEVICE                    0U
#define USB_OTG_MODE_HOST                      4U



/** @defgroup USB Device Speed
  * @{
  */
#define USB_FS_SPEED                          0U
#define USB_LS_SPEED                          1U
/**
  * @}
  */

/** @defgroup USB_Core_Speed USB Low Layer Core Speed
  * @{
  */
#define USB_OTG_SPEED_FULL                     0U
#define USB_OTG_SPEED_LOW                      1U

#define FIFO_TX                                0U
#define FIFO_RX                                1U

/**
  * @}
  */

/** @defgroup USB_Core_MPS USB Low Layer Core MPS
  * @{
  */
#define USB_OTG_FS_MAX_PACKET_SIZE            64U
#define USB_OTG_FS_MAX_BULK_PACKET_SIZE       64U
#define USB_OTG_FS_MAX_INTR_PACKET_SIZE       64U
#define USB_OTG_LS_MAX_INTR_PACKET_SIZE       8U
#define USB_OTG_FS_MAX_ISOC_PACKET_SIZE       1023U
/**
  * @}
  */


#endif  /* USB_OTG_FS */


/** @defgroup USB_EP_Speed USB Low Layer EP Speed
  * @{
  */
#define EP_SPEED_LOW                           0U
#define EP_SPEED_FULL                          1U
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


#define EP_PID_DATA0                           0U
#define EP_PID_DATA2                           1U
#define EP_PID_DATA1                           2U
#define EP_PID_SETUP                           3U

/**
  * @}
  */

#define EP_ADDR_MSK                          0xFU

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup USB_Exported_Macros USB Low Layer Exported Macros
  * @{
  */


#define __USB_FS_LOCK(__HANDLE__)                                               \
                              do{                                             \
                                  if((__HANDLE__)->Lock == USB_FS_LOCKED)       \
                                  {                                           \
                                    return USB_FS_BUSY;                         \
                                  }                                           \
                                  else                                        \
                                  {                                           \
                                    (__HANDLE__)->Lock = USB_FS_LOCKED;         \
                                  }                                           \
                                }while (0U)

#define __USB_FS_UNLOCK(__HANDLE__)                                               \
                                do{                                             \
                                    (__HANDLE__)->Lock = USB_FS_UNLOCKED;         \
                                  }while (0U)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup USB_FS_Exported_Functions USB Low Layer Exported Functions
  * @{
  */
#if defined (USB_OTG_FS)

USB_FS_StatusTypeDef USB_FS_CoreInit(void);
USB_FS_StatusTypeDef USB_FS_DevInit(USB_OTG_FS_CfgTypeDef cfg);
USB_FS_StatusTypeDef USB_FS_HostInit(USB_OTG_FS_CfgTypeDef cfg);
USB_FS_StatusTypeDef USB_FS_IndexSel(uint8_t epnum);
USB_FS_StatusTypeDef USB_FS_RstEP0Regs(void);
USB_FS_StatusTypeDef USB_FS_RstEPRegs(uint8_t epnum);
USB_FS_StatusTypeDef USB_FS_FlushEp0Fifo(void);
USB_FS_StatusTypeDef USB_FS_FlushTxFifo(uint8_t epnum);
USB_FS_StatusTypeDef USB_FS_FlushRxFifo(uint8_t epnum);
USB_FS_StatusTypeDef USB_FS_SendStall(USB_OTG_FS_DEPTypeDef *dep);
USB_FS_StatusTypeDef USB_FS_ClrStall(USB_OTG_FS_DEPTypeDef *dep);
USB_FS_StatusTypeDef USB_FS_HEP_Init(uint8_t epnum, uint8_t dev_address,
                                     uint8_t ep_type, uint8_t interval,
                                     uint16_t xfersize);
int32_t usb_log2(int32_t x);
uint32_t USB_FS_Get_VBusStatus(void);
uint16_t USB_FS_Read_RxCount(void);
uint32_t USB_FS_GetCurrentFrame(void);
uint32_t USB_FS_GetSpeed(void);
uint8_t  USB_FS_Read_Count0(void);
uint8_t  USB_FS_GetMode(void);
uint8_t  USB_FS_GetCID(void);
uint8_t  USB_FS_GetAddress(void);
uint8_t  USB_FS_GetPower(void);
uint8_t  USB_FS_GetrDevctl(void);
int8_t   USB_FS_Exiting_Host(uint8_t toOTG, USB_OTG_FS_CfgTypeDef *cfg);
uint32_t USB_FS_ReadInterrupts(void);

void USB_FS_Enable_HEP(USB_OTG_FS_HEPTypeDef *hep);
void USB_FS_Enable_DEP(USB_OTG_FS_DEPTypeDef *dep);
void USB_FS_DEPStartXfer(USB_OTG_FS_DEPTypeDef *dep);
void USB_FS_DEP0StartXfer(USB_OTG_FS_DEPTypeDef *dep);
void USB_FS_HEP_StartXfer(USB_OTG_FS_HEPTypeDef *hep);
void USB_FS_HEP0_StartXfer(USB_OTG_FS_HEPTypeDef *hep, uint8_t ctl_state);
void USB_FS_FIFORead(uint8_t *dstP, uint8_t ep_num, uint16_t len);
void USB_FS_FIFOWrite(uint8_t *srcP, uint8_t ep_num, uint16_t len);
//void USB_FS_IntHandle(void);
void USB_FS_SetEPInt(uint8_t cfg);
void USB_FS_SetUSBInt(uint8_t cfg);
void USB_FS_ClrUSBInt(void);
void USB_FS_ClrEPInt(void);
void USB_FS_SetTxFiFo(uint8_t epnum, uint8_t size, uint8_t address, uint8_t dpb);
void USB_FS_SetRxFiFo(uint8_t epnum, uint8_t size, uint8_t address, uint8_t dpb);
void USB_FS_DrvSess(uint8_t state);
void USB_FS_Set_Polling_Interval(uint8_t epdir, uint8_t interval);
void USB_FS_Set_NAKLMT(uint8_t epnum, uint8_t epdir, uint8_t naklmt);
void USB_FS_SetAddress(uint8_t address);
void USB_FS_SetPower(uint8_t powercfg);
void USB_FS_ClrPower(uint8_t powercfg);
void USB_FS_SetDevctl(uint8_t cfg);
void USB_FS_ClrDevctl(uint8_t cfg);
void USB_FS_Activate_Resume(void);
void USB_FS_DeActivate_Resume(void);
void USB_FS_ResetPort(void);
void USB_FS_Enable_Suspend(void);
void USB_FS_Disable_Suspend(void);
void USB_FS_ActivateSetup(void);


#endif /* defined (USB_OTG_FS) */


#endif /* defined (USB_OTG_FS) */

#ifdef __cplusplus
}
#endif


#endif /* FT32F4xx_USB_FS_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
