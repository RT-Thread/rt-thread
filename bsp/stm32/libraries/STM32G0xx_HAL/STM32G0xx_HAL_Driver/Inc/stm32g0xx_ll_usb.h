/**
  ******************************************************************************
  * @file    stm32g0xx_ll_usb.h
  * @author  MCD Application Team
  * @brief   Header file of USB Low Layer HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G0xx_LL_USB_H
#define STM32G0xx_LL_USB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_def.h"

#if defined (USB_DRD_FS)
/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @addtogroup USB_LL
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  USB Mode definition
  */


typedef enum
{
  USB_DEVICE_MODE  = 0,
  USB_HOST_MODE    = 1
} USB_DRD_ModeTypeDef;

/**
  * @brief  URB States definition
  */
typedef enum
{
  URB_IDLE = 0,
  URB_DONE,
  URB_NOTREADY,
  URB_NYET,
  URB_ERROR,
  URB_STALL
} USB_DRD_URBStateTypeDef;

/**
  * @brief  Host channel States  definition
  */
typedef enum
{
  HC_IDLE = 0,
  HC_XFRC,
  HC_HALTED,
  HC_NAK,
  HC_NYET,
  HC_STALL,
  HC_XACTERR,
  HC_BBLERR,
  HC_DATATGLERR,
  HC_ACK
} USB_DRD_HCStateTypeDef;

/**
  * USB HOST Double buffer Isochronous State
  */
typedef enum
{
  USB_PMABUF_EMPTY = 0U,
  USB_PMABUF_NOT_EMPTY = 1U
} USB_BuffStateTypedDef;

/**
  * @brief  USB Instance Initialization Structure definition
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
                                         This parameter can be any value of @ref USB_Core_Speed                 */

  uint32_t ep0_mps;                 /*!< Set the Endpoint 0 Max Packet size.                                    */

  uint32_t phy_itface;              /*!< Select the used PHY interface.
                                         This parameter can be any value of @ref USB_Core_PHY                   */

  uint32_t Sof_enable;              /*!< Enable or disable the output of the SOF signal.                        */

  uint32_t low_power_enable;        /*!< Enable or disable the low power mode.                                  */

  uint32_t lpm_enable;              /*!< Enable or disable Link Power Management.                               */

  uint32_t battery_charging_enable; /*!< Enable or disable Battery charging.                                    */

  uint32_t vbus_sensing_enable;     /*!< Enable or disable the VBUS Sensing feature.                            */

  uint32_t bulk_doublebuffer_enable;  /*!< Enable or disable the double buffer mode on bulk EP                  */

  uint32_t iso_singlebuffer_enable;   /*!< Enable or disable the Single buffer mode on Isochronous  EP          */
} USB_DRD_CfgTypeDef;

typedef struct
{
  uint8_t   num;                  /*!< Endpoint number
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 15   */

  uint8_t   is_in;                /*!< Endpoint direction
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint8_t   is_stall;             /*!< Endpoint stall condition
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint8_t   type;                 /*!< Endpoint type
                                       This parameter can be any value of @ref USB_EP_Type_                     */

  uint16_t  pmaadress;            /*!< PMA Address
                                       This parameter can be any value between Min_addr = 0 and Max_addr = 1K    */

  uint16_t  pmaaddr0;             /*!< PMA Address0
                                       This parameter can be any value between Min_addr = 0 and Max_addr = 1K    */

  uint16_t  pmaaddr1;             /*!< PMA Address1
                                       This parameter can be any value between Min_addr = 0 and Max_addr = 1K    */

  uint8_t   doublebuffer;         /*!< Double buffer enable
                                       This parameter can be 0 or 1                                              */

  uint8_t   data_pid_start;       /*!< Initial data PID
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 1    */

  uint16_t  tx_fifo_num;          /*!< Transmission FIFO number
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 15   */

  uint32_t  maxpacket;            /*!< Endpoint Max packet size
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 64KB */

  uint8_t   *xfer_buff;           /*!< Pointer to transfer buffer                                               */

  uint32_t  xfer_len;             /*!< Current transfer length                                                  */

  uint32_t  xfer_count;           /*!< Partial transfer length in case of multi packet transfer                 */

  uint32_t  xfer_len_db;          /*!< double buffer transfer length used with bulk double buffer in            */

  uint8_t   xfer_fill_db;         /*!< double buffer Need to Fill new buffer  used with bulk_in                 */
} USB_DRD_EPTypeDef;

typedef struct
{
  uint8_t   dev_addr;           /*!< USB device address.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 255    */

  uint8_t   phy_ch_num;         /*!< Host channel number.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 15     */

  uint8_t   ep_num;             /*!< Endpoint number.
                                     This parameter must be a number between Min_Data = 1 and Max_Data = 15     */

  uint8_t   ch_dir;             /*!< channel direction
                                     This parameter store the physical channel direction IN/OUT/BIDIR           */

  uint8_t   speed;              /*!< USB Host speed.
                                     This parameter can be any value of @ref USB_Core_Speed_                    */

  uint8_t   ep_type;            /*!< Endpoint Type.
                                     This parameter can be any value of @ref USB_EP_Type_                       */

  uint16_t  max_packet;         /*!< Endpoint Max packet size.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 64KB   */

  uint8_t   data_pid;           /*!< Initial data PID.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   *xfer_buff;         /*!< Pointer to transfer buffer.                                                */

  uint32_t  xfer_len;           /*!< Current transfer length.                                                   */

  uint32_t  xfer_len_db;        /*!< Current transfer length used in double buffer mode.                        */

  uint32_t  xfer_count;         /*!< Partial transfer length in case of multi packet transfer.                  */

  uint8_t   toggle_in;          /*!< IN transfer current toggle flag.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint8_t   toggle_out;         /*!< OUT transfer current toggle flag
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  uint32_t  ErrCnt;             /*!< Host channel error count.                                                 */

  uint16_t  pmaadress;          /*!< PMA Address
                                     This parameter can be any value between Min_addr = 0 and Max_addr = 1K    */

  uint16_t  pmaaddr0;           /*!< PMA Address0
                                     This parameter can be any value between Min_addr = 0 and Max_addr = 1K    */

  uint16_t  pmaaddr1;           /*!< PMA Address1
                                     This parameter can be any value between Min_addr = 0 and Max_addr = 1K    */

  uint8_t   doublebuffer;       /*!< Double buffer enable
                                     This parameter can be 0 or 1                                              */

  USB_BuffStateTypedDef  pmabuff0_state;   /*!< PMA Buffer0 State empty / notEmpty : used in double buffer OUT isochronous */

  USB_BuffStateTypedDef  pmabuff1_state;   /*!< PMA Buffer1 State empty / notEmpty : used in double buffer OUT isochronous */

  USB_DRD_URBStateTypeDef urb_state;  /*!< URB state.
                                            This parameter can be any value of @ref USB_OTG_URBStateTypeDef */

  USB_DRD_HCStateTypeDef state;       /*!< Host Channel state.
                                            This parameter can be any value of @ref USB_OTG_HCStateTypeDef  */
} USB_DRD_HCTypeDef;



/* Exported constants --------------------------------------------------------*/

/** @defgroup PCD_Exported_Constants PCD Exported Constants
  * @{
  */


/** @defgroup USB_LL_EP0_MPS USB Low Layer EP0 MPS
  * @{
  */
#define EP_MPS_64                              0U
#define EP_MPS_32                              1U
#define EP_MPS_16                              2U
#define EP_MPS_8                               3U
/**
  * @}
  */

/** @defgroup USB_LL_EP_Type USB Low Layer EP Type
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

/** @defgroup USB_LL Device Speed
  * @{
  */
#define USBD_FS_SPEED                          2U
#define USBH_FSLS_SPEED                        1U
/**
  * @}
  */

#define BTABLE_ADDRESS                         0x000U

#define EP_ADDR_MSK                            0x7U

/*!< USB Speed */
#define USB_DRD_SPEED_FS                       1U
#define USB_DRD_SPEED_LS                       2U
#define USB_DRD_SPEED_LSFS                     3U

/*!< PID */
#define HC_PID_DATA0                           0U
#define HC_PID_DATA2                           1U
#define HC_PID_DATA1                           2U
#define HC_PID_SETUP                           3U

/*!< Channel Direction  */
#define CH_IN_DIR                              1U
#define CH_OUT_DIR                             0U

/*!< Number of used channels in the Application */
#ifndef USB_DRD_USED_CHANNELS
#define USB_DRD_USED_CHANNELS                  8U
#endif /* USB_DRD_USED_CHANNELS */

/* First available address in PMA */
#define PMA_START_ADDR          (0x10U + (8U *(USB_DRD_USED_CHANNELS - 2U)))
#define PMA_END_ADDR             USB_DRD_PMA_SIZE


/**
  * used for USB_HC_DoubleBuffer API
  */
#define USB_DRD_DBUFF_ENBALE                   1U
#define USB_DRD_DBUFF_DISABLE                  2U


/* Exported macro ------------------------------------------------------------*/
/**
  * @}
  */
/********************  Bit definition for USB_COUNTn_RX register  *************/
#define USB_CNTRX_NBLK_MSK                    (0x1FU << 26)
#define USB_CNTRX_BLSIZE                      (0x1U << 31)


/*Set Channel/Endpoint to the USB Register */
#define USB_DRD_SET_CHEP(USBx, bEpChNum, wRegValue)  (*(__IO uint32_t *)(&(USBx)->CHEP0R + (bEpChNum)) = (uint32_t)(wRegValue))

/*Get Channel/Endpoint from the USB Register */
#define USB_DRD_GET_CHEP(USBx, bEpChNum)             (*(__IO uint32_t *)(&(USBx)->CHEP0R + (bEpChNum)))


/**
  * @brief free buffer used from the application realizing it to the line
  *         toggles bit SW_BUF in the double buffered endpoint register
  * @param USBx USB device.
  * @param   bEpChNum, bDir
  * @retval None
  */
#define USB_DRD_FreeUserBuffer(USBx, bEpChNum, bDir) \
  do { \
    if ((bDir) == 0U) \
    { \
      /* OUT double buffered endpoint */ \
      USB_DRD_TX_DTOG((USBx), (bEpChNum)); \
    } \
    else if ((bDir) == 1U) \
    { \
      /* IN double buffered endpoint */ \
      USB_DRD_RX_DTOG((USBx), (bEpChNum)); \
    } \
  } while(0)


/**
  * @brief Set the Setup bit in the corresponding channel, when a Setup
     transaction is needed.
  * @param USBx USB device.
  * @param   bEpChNum
  * @retval None
  */
#define USB_DRD_CHEP_TX_SETUP(USBx, bEpChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) ; \
    \
    /*Set Setup bit*/ \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_SETUP)); \
  } while(0)


/**
  * @brief  Clears bit ERR_RX in the Channel register
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_CLEAR_CHEP_RX_ERR(USBx, bChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bChNum)); \
    _wRegVal = (_wRegVal & USB_CHEP_REG_MASK & (~USB_CHEP_ERRRX) & (~USB_CHEP_VTRX)) | \
               (USB_CHEP_VTTX | USB_CHEP_ERRTX); \
    \
    USB_DRD_SET_CHEP((USBx), (bChNum), _wRegVal); \
  } while(0) /* USB_DRD_CLEAR_CHEP_RX_ERR */


/**
  * @brief  Clears bit ERR_TX in the Channel register
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_CLEAR_CHEP_TX_ERR(USBx, bChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bChNum)); \
    _wRegVal = (_wRegVal & USB_CHEP_REG_MASK & (~USB_CHEP_ERRTX) & (~USB_CHEP_VTTX)) | \
               (USB_CHEP_VTRX|USB_CHEP_ERRRX); \
    \
    USB_DRD_SET_CHEP((USBx), (bChNum), _wRegVal); \
  } while(0) /* USB_DRD_CLEAR_CHEP_TX_ERR */


/**
  * @brief  sets the status for tx transfer (bits STAT_TX[1:0]).
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @param  wState new state
  * @retval None
  */
#define USB_DRD_SET_CHEP_TX_STATUS(USBx, bEpChNum, wState) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_CHEP_TX_DTOGMASK; \
    /* toggle first bit ? */ \
    if ((USB_CHEP_TX_DTOG1 & (wState)) != 0U) \
    { \
      _wRegVal ^= USB_CHEP_TX_DTOG1; \
    } \
    /* toggle second bit ?  */ \
    if ((USB_CHEP_TX_DTOG2 & (wState)) != 0U) \
    { \
      _wRegVal ^= USB_CHEP_TX_DTOG2; \
    } \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_VTRX| USB_CHEP_VTTX)); \
  } while(0) /* USB_DRD_SET_CHEP_TX_STATUS */


/**
  * @brief  sets the status for rx transfer (bits STAT_TX[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @param  wState new state
  * @retval None
  */
#define USB_DRD_SET_CHEP_RX_STATUS(USBx, bEpChNum, wState) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_CHEP_RX_DTOGMASK; \
    /* toggle first bit ? */ \
    if ((USB_CHEP_RX_DTOG1 & (wState)) != 0U) \
    { \
      _wRegVal ^= USB_CHEP_RX_DTOG1; \
    } \
    /* toggle second bit ? */ \
    if ((USB_CHEP_RX_DTOG2 & (wState)) != 0U) \
    { \
      _wRegVal ^= USB_CHEP_RX_DTOG2; \
    } \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_VTRX | USB_CHEP_VTTX)); \
  } while(0) /* USB_DRD_SET_CHEP_RX_STATUS */


/**
  * @brief  gets the status for tx/rx transfer (bits STAT_TX[1:0]
  *         /STAT_RX[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval status
  */
#define USB_DRD_GET_CHEP_TX_STATUS(USBx, bEpChNum)     ((uint16_t)USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_DRD_CHEP_TX_STTX)
#define USB_DRD_GET_CHEP_RX_STATUS(USBx, bEpChNum)     ((uint16_t)USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_DRD_CHEP_RX_STRX)


/**
  * @brief  set  EP_KIND bit.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_SET_CHEP_KIND(USBx, bEpChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_CHEP_REG_MASK; \
    \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_VTRX | USB_CHEP_VTTX | USB_CHEP_KIND)); \
  } while(0) /* USB_DRD_SET_CHEP_KIND */


/**
  * @brief  clear EP_KIND bit.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_CLEAR_CHEP_KIND(USBx, bEpChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_EP_KIND_MASK; \
    \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_VTRX | USB_CHEP_VTTX)); \
  } while(0) /* USB_DRD_CLEAR_CHEP_KIND */


/**
  * @brief  Clears bit CTR_RX / CTR_TX in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_CLEAR_RX_CHEP_CTR(USBx, bEpChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & (0xFFFF7FFFU & USB_CHEP_REG_MASK); \
    \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_VTTX)); \
  } while(0) /* USB_CLEAR_RX_CHEP_CTR */

#define USB_DRD_CLEAR_TX_CHEP_CTR(USBx, bEpChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & (0xFFFFFF7FU & USB_CHEP_REG_MASK); \
    \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_VTRX)); \
  } while(0) /* USB_CLEAR_TX_CHEP_CTR */


/**
  * @brief  Toggles DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_RX_DTOG(USBx, bEpChNum) \
  do { \
    uint32_t _wEPVal; \
    \
    _wEPVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_CHEP_REG_MASK; \
    \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wEPVal | USB_CHEP_VTRX | USB_CHEP_VTTX | USB_CHEP_DTOG_RX)); \
  } while(0) /* USB_DRD_RX_DTOG */

#define USB_DRD_TX_DTOG(USBx, bEpChNum) \
  do { \
    uint32_t _wEPVal; \
    \
    _wEPVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_CHEP_REG_MASK; \
    \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wEPVal | USB_CHEP_VTRX | USB_CHEP_VTTX | USB_CHEP_DTOG_TX)); \
  } while(0) /* USB_TX_DTOG */


/**
  * @brief  Clears DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_CLEAR_RX_DTOG(USBx, bEpChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)); \
    \
    if ((_wRegVal & USB_CHEP_DTOG_RX) != 0U) \
    { \
      USB_DRD_RX_DTOG((USBx), (bEpChNum)); \
    } \
  } while(0) /* USB_DRD_CLEAR_RX_DTOG */

#define USB_DRD_CLEAR_TX_DTOG(USBx, bEpChNum) \
  do { \
    uint32_t _wRegVal; \
    \
    _wRegVal = USB_DRD_GET_CHEP((USBx), (bEpChNum)); \
    \
    if ((_wRegVal & USB_CHEP_DTOG_TX) != 0U) \
    { \
      USB_DRD_TX_DTOG((USBx), (bEpChNum)); \
    } \
  } while(0) /* USB_DRD_CLEAR_TX_DTOG */


/**
  * @brief  Sets address in an endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @param  bAddr Address.
  * @retval None
  */
#define USB_DRD_SET_CHEP_ADDRESS(USBx, bEpChNum, bAddr) \
  do { \
    uint32_t _wRegVal; \
    \
    /*Read the USB->CHEPx into _wRegVal, Reset(DTOGRX/STRX/DTOGTX/STTX) and set the EpAddress*/ \
    _wRegVal = (USB_DRD_GET_CHEP((USBx), (bEpChNum)) & USB_CHEP_REG_MASK) | (bAddr); \
    \
    /*Set _wRegVal in USB->CHEPx and set Transmit/Receive Valid Transfer  (x=bEpChNum)*/ \
    USB_DRD_SET_CHEP((USBx), (bEpChNum), (_wRegVal | USB_CHEP_VTRX | USB_CHEP_VTTX)); \
  } while(0) /* USB_DRD_SET_CHEP_ADDRESS */


/* PMA API Buffer Descriptor Management ------------------------------------------------------------*/
/* Buffer Descriptor Table   TXBD0/RXBD0 --- > TXBD7/RXBD7  8 possible descriptor
* The buffer descriptor is located inside the packet buffer memory (USB_PMA_BUFF)
*          TXBD    [Reserve         |Countx| Address_Tx]
*          RXBD    [BLSIEZ|NUM_Block |CounRx| Address_Rx] */

/* Set TX Buffer Descriptor Address Field */
#define USB_DRD_SET_CHEP_TX_ADDRESS(USBx, bEpChNum, wAddr) \
  do { \
    /* Reset old Address */ \
    (USB_DRD_PMA_BUFF + (bEpChNum))->TXBD &= USB_PMA_TXBD_ADDMSK; \
    \
    /* Bit0 & Bit1 should be =0 PMA must be Word aligned */ \
    (USB_DRD_PMA_BUFF + (bEpChNum))->TXBD |= (uint32_t)(((uint32_t)(wAddr) >> 2U) << 2U); \
  } while(0) /* USB_DRD_SET_CHEP_TX_ADDRESS */

/* Set RX Buffer Descriptor Address Field */
#define USB_DRD_SET_CHEP_RX_ADDRESS(USBx, bEpChNum, wAddr) \
  do { \
    /* Reset old Address */ \
    (USB_DRD_PMA_BUFF + (bEpChNum))->RXBD &= USB_PMA_RXBD_ADDMSK; \
    \
    /* Bit0 & Bit1 should be =0 PMA must be Word aligned */ \
    (USB_DRD_PMA_BUFF + (bEpChNum))->RXBD |= (uint32_t)(((uint32_t)(wAddr) >> 2U) << 2U); \
  } while(0) /* USB_SET_CHEP_RX_ADDRESS */


/**
  * @brief  Sets counter of rx buffer with no. of blocks.
  * @param  pdwReg Register pointer
  * @param  wCount Counter.
  * @param  wNBlocks no. of Blocks.
  * @retval None
  */
#define USB_DRD_CALC_BLK32(pdwReg, wCount, wNBlocks) \
  do { \
    /* Divide PacketSize by 32 to calculate the Nb of Block32 */ \
    (wNBlocks) =((uint32_t)(wCount) >> 5U); \
    if (((uint32_t)(wCount) % 32U) == 0U)  \
    { \
      (wNBlocks)--; \
    } \
    \
    (pdwReg)|= (uint32_t)((((wNBlocks) << 26U)) | USB_CNTRX_BLSIZE); \
  } while(0) /* USB_DRD_CALC_BLK32 */

#define USB_DRD_CALC_BLK2(pdwReg, wCount, wNBlocks) \
  do { \
    /* Divide PacketSize by 32 to calculate the Nb of Block32 */ \
    (wNBlocks) = (uint32_t)((uint32_t)(wCount) >> 1U); \
    if (((wCount) & 0x1U) != 0U) \
    { \
      (wNBlocks)++; \
    } \
    (pdwReg) |= (uint32_t)((wNBlocks) << 26U); \
  } while(0) /* USB_DRD_CALC_BLK2 */

#define USB_DRD_SET_CHEP_CNT_RX_REG(pdwReg, wCount) \
  do { \
    uint32_t wNBlocks; \
    \
    (pdwReg) &= USB_PMA_RXBD_COUNTMSK; \
    if ((wCount) == 0U) \
    { \
      (pdwReg) &= (uint32_t)~USB_CNTRX_NBLK_MSK; \
      (pdwReg) |= USB_CNTRX_BLSIZE; \
    } \
    else if((wCount) <= 62U) \
    { \
      USB_DRD_CALC_BLK2((pdwReg), (wCount), wNBlocks); \
    } \
    else \
    { \
      USB_DRD_CALC_BLK32((pdwReg), (wCount), wNBlocks); \
    } \
  } while(0) /* USB_DRD_SET_CHEP_CNT_RX_REG */


/**
  * @brief  sets counter for the tx/rx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @param  wCount Counter value.
  * @retval None
  */
#define USB_DRD_SET_CHEP_TX_CNT(USBx,bEpChNum, wCount) \
  do { \
    /* Reset old TX_Count value */ \
    (USB_DRD_PMA_BUFF + (bEpChNum))->TXBD &= USB_PMA_TXBD_COUNTMSK; \
    \
    /* Set the wCount in the dedicated EP_TXBuffer */ \
    (USB_DRD_PMA_BUFF + (bEpChNum))->TXBD |= (uint32_t)((uint32_t)(wCount) << 16U); \
  } while(0)


#define USB_DRD_SET_CHEP_RX_DBUF0_CNT(USBx, bEpChNum, wCount)      USB_DRD_SET_CHEP_CNT_RX_REG(((USB_DRD_PMA_BUFF + (bEpChNum))->TXBD), (wCount))
#define USB_DRD_SET_CHEP_RX_CNT(USBx, bEpChNum, wCount)            USB_DRD_SET_CHEP_CNT_RX_REG(((USB_DRD_PMA_BUFF + (bEpChNum))->RXBD), (wCount))


/**
  * @brief  gets counter of the tx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval Counter value
  */
#define USB_DRD_GET_CHEP_TX_CNT(USBx, bEpChNum)           (((USB_DRD_PMA_BUFF + (bEpChNum))->TXBD & 0x03FF0000U) >>16U)
#define USB_DRD_GET_CHEP_RX_CNT(USBx, bEpChNum)           (((USB_DRD_PMA_BUFF + (bEpChNum))->RXBD & 0x03FF0000U) >>16U)

#define USB_DRD_GET_EP_TX_CNT                             USB_GET_CHEP_TX_CNT
#define USB_DRD_GET_CH_TX_CNT                             USB_GET_CHEP_TX_CNT

#define USB_DRD_GET_EP_RX_CNT                             USB_DRD_GET_CHEP_RX_CNT
#define USB_DRD_GET_CH_RX_CNT                             USB_DRD_GET_CHEP_RX_CNT
/**
  * @brief  Sets buffer 0/1 address in a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @param  wBuf0Addr buffer 0 address.
  * @retval Counter value
  */
#define USB_DRD_SET_CHEP_DBUF0_ADDR(USBx, bEpChNum, wBuf0Addr)    USB_DRD_SET_CHEP_TX_ADDRESS((USBx), (bEpChNum), (wBuf0Addr))
#define USB_DRD_SET_CHEP_DBUF1_ADDR(USBx, bEpChNum, wBuf1Addr)    USB_DRD_SET_CHEP_RX_ADDRESS((USBx), (bEpChNum), (wBuf1Addr))


/**
  * @brief  Sets addresses in a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @param  wBuf0Addr: buffer 0 address.
  * @param  wBuf1Addr = buffer 1 address.
  * @retval None
  */
#define USB_DRD_SET_CHEP_DBUF_ADDR(USBx, bEpChNum, wBuf0Addr, wBuf1Addr) \
  do { \
    USB_DRD_SET_CHEP_DBUF0_ADDR((USBx), (bEpChNum), (wBuf0Addr)); \
    USB_DRD_SET_CHEP_DBUF1_ADDR((USBx), (bEpChNum), (wBuf1Addr)); \
  } while(0) /* USB_DRD_SET_CHEP_DBUF_ADDR */


/**
  * @brief  Gets buffer 0/1 address of a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @param  bDir endpoint dir  EP_DBUF_OUT = OUT
  *         EP_DBUF_IN  = IN
  * @param  wCount: Counter value
  * @retval None
  */
#define USB_DRD_SET_CHEP_DBUF0_CNT(USBx, bEpChNum, bDir, wCount) \
  do { \
    if ((bDir) == 0U) \
    { \
      /* OUT endpoint */ \
      USB_DRD_SET_CHEP_RX_DBUF0_CNT((USBx), (bEpChNum), (wCount)); \
    } \
    else \
    { \
      if ((bDir) == 1U) \
      { \
        /* IN endpoint */ \
        USB_DRD_SET_CHEP_TX_CNT((USBx), (bEpChNum), (wCount)); \
      } \
    } \
  } while(0) /* USB_DRD_SET_CHEP_DBUF0_CNT */

#define USB_DRD_SET_CHEP_DBUF1_CNT(USBx, bEpChNum, bDir, wCount) \
  do { \
    if ((bDir) == 0U) \
    { \
      /* OUT endpoint */ \
      USB_DRD_SET_CHEP_RX_CNT((USBx), (bEpChNum), (wCount)); \
    } \
    else \
    { \
      if ((bDir) == 1U) \
      { \
        /* IN endpoint */ \
        (USB_DRD_PMA_BUFF + (bEpChNum))->RXBD &= USB_PMA_TXBD_COUNTMSK; \
        (USB_DRD_PMA_BUFF + (bEpChNum))->RXBD |= (uint32_t)((uint32_t)(wCount) << 16U); \
      } \
    } \
  } while(0) /* USB_DRD_SET_CHEP_DBUF1_CNT */

#define USB_DRD_SET_CHEP_DBUF_CNT(USBx, bEpChNum, bDir, wCount) \
  do { \
    USB_DRD_SET_CHEP_DBUF0_CNT((USBx), (bEpChNum), (bDir), (wCount)); \
    USB_DRD_SET_CHEP_DBUF1_CNT((USBx), (bEpChNum), (bDir), (wCount)); \
  } while(0) /* USB_DRD_SET_EPCH_DBUF_CNT  */

/**
  * @brief  Gets buffer 0/1 rx/tx counter for double buffering.
  * @param  USBx USB peripheral instance register address.
  * @param  bEpChNum Endpoint Number.
  * @retval None
  */
#define USB_DRD_GET_CHEP_DBUF0_CNT(USBx, bEpChNum)     (USB_DRD_GET_CHEP_TX_CNT((USBx), (bEpChNum)))
#define USB_DRD_GET_CHEP_DBUF1_CNT(USBx, bEpChNum)     (USB_DRD_GET_CHEP_RX_CNT((USBx), (bEpChNum)))
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup USB_LL_Exported_Functions USB Low Layer Exported Functions
  * @{
  */


HAL_StatusTypeDef USB_CoreInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg);
HAL_StatusTypeDef USB_DevInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg);
HAL_StatusTypeDef USB_EnableGlobalInt(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_DisableGlobalInt(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_SetCurrentMode(USB_DRD_TypeDef *USBx, USB_DRD_ModeTypeDef mode);

#if defined (HAL_PCD_MODULE_ENABLED)
HAL_StatusTypeDef USB_ActivateEndpoint(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep);
HAL_StatusTypeDef USB_DeactivateEndpoint(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPStartXfer(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPSetStall(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPClearStall(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep);
#endif

HAL_StatusTypeDef USB_SetDevAddress(USB_DRD_TypeDef *USBx, uint8_t address);
HAL_StatusTypeDef USB_DevConnect(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_DevDisconnect(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_StopDevice(USB_DRD_TypeDef *USBx);
uint32_t          USB_ReadInterrupts(USB_DRD_TypeDef *USBx);

HAL_StatusTypeDef USB_ResetPort(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_HostInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg);
HAL_StatusTypeDef USB_HC_IN_Halt(USB_DRD_TypeDef *USBx, uint8_t phy_ch);
HAL_StatusTypeDef USB_HC_OUT_Halt(USB_DRD_TypeDef *USBx, uint8_t phy_ch);
HAL_StatusTypeDef USB_HC_StartXfer(USB_DRD_TypeDef *USBx, USB_DRD_HCTypeDef *hc);

uint32_t          USB_GetHostSpeed(USB_DRD_TypeDef *USBx);
uint32_t          USB_GetCurrentFrame(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_StopHost(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_HC_DoubleBuffer(USB_DRD_TypeDef *USBx, uint8_t phy_ch_num, uint8_t db_state);
HAL_StatusTypeDef USB_HC_Init(USB_DRD_TypeDef *USBx, uint8_t phy_ch_num, uint8_t epnum,
                              uint8_t dev_address, uint8_t speed, uint8_t ep_type, uint16_t mps);

HAL_StatusTypeDef USB_ActivateRemoteWakeup(USB_DRD_TypeDef *USBx);
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(USB_DRD_TypeDef *USBx);

void              USB_WritePMA(USB_DRD_TypeDef *USBx, uint8_t *pbUsrBuf,
                               uint16_t wPMABufAddr, uint16_t wNBytes);

void              USB_ReadPMA(USB_DRD_TypeDef *USBx, uint8_t *pbUsrBuf,
                              uint16_t wPMABufAddr, uint16_t wNBytes);

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
#endif /* defined (USB_DRD_FS) */

#ifdef __cplusplus
}
#endif


#endif /* STM32G0xx_LL_USB_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
