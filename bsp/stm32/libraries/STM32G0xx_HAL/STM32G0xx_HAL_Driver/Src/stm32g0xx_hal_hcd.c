/**
  ******************************************************************************
  * @file    stm32g0xx_hal_hcd.c
  * @author  MCD Application Team
  * @brief   HCD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
  [..]
    (#)Declare a HCD_HandleTypeDef handle structure, for example:
       HCD_HandleTypeDef  hhcd;

    (#)Fill parameters of Init structure in HCD handle

    (#)Call HAL_HCD_Init() API to initialize the HCD peripheral (Core, Host core, ...)

    (#)Initialize the HCD low level resources through the HAL_HCD_MspInit() API:
        (##) Enable the HCD/USB Low Level interface clock using the following macros
             (+++) __HAL_RCC_USB_CLK_ENABLE();
        (##) Initialize the related GPIO clocks
        (##) Configure HCD pin-out
        (##) Configure HCD NVIC interrupt

    (#)Associate the Upper USB Host stack to the HAL HCD Driver:
        (##) hhcd.pData = phost;

    (#)Enable HCD transmission and reception:
        (##) HAL_HCD_Start();

  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

#ifdef HAL_HCD_MODULE_ENABLED



/** @defgroup HCD HCD
  * @brief HCD HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/** @defgroup HCD_Private_Functions HCD Private Functions
  * @{
  */
static void HCD_HC_IN_IRQHandler(HCD_HandleTypeDef *hhcd, uint8_t chnum);
static void HCD_HC_OUT_IRQHandler(HCD_HandleTypeDef *hhcd, uint8_t chnum);
static void HCD_Port_IRQHandler(HCD_HandleTypeDef *hhcd);
static void HAL_HCD_ClearPhyChannel(HCD_HandleTypeDef *hhcd);
static uint8_t HAL_HCD_GetLogical_Channel(HCD_HandleTypeDef *hhcd, uint8_t phy_chnum, uint8_t dir);
static uint8_t HAL_HCD_Check_usedChannel(HCD_HandleTypeDef *hhcd, uint8_t ch_num);
static uint8_t HAL_HCD_Get_FreePhyChannel(HCD_HandleTypeDef *hhcd, uint8_t ch_num, uint8_t epnum, uint8_t ep_type);

static void HCD_HC_IN_BulkDb(HCD_HandleTypeDef *hhcd, uint8_t ch_num, uint8_t phy_chnum, uint32_t regvalue);
static void HCD_HC_OUT_BulkDb(HCD_HandleTypeDef *hhcd, uint8_t ch_num, uint8_t phy_chnum, uint32_t regvalue);
static uint16_t HAL_HCD_GetFreePMA(HCD_HandleTypeDef *hhcd, uint16_t mps);
static HAL_StatusTypeDef  HAL_HCD_PMAFree(HCD_HandleTypeDef *hhcd, uint32_t pma_base, uint16_t mps);
static void inline HCD_HC_IN_ISO(HCD_HandleTypeDef *hhcd, uint8_t ch_num, uint8_t phy_chnum, uint32_t regvalue);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HCD_Exported_Functions HCD Exported Functions
  * @{
  */

/** @defgroup HCD_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
===============================================================================
##### Initialization and de-initialization functions #####
===============================================================================
[..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_Init(HCD_HandleTypeDef *hhcd)
{
  /* Check the HCD handle allocation */
  if (hhcd == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_HCD_ALL_INSTANCE(hhcd->Instance));

  if (hhcd->State == HAL_HCD_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hhcd->Lock = HAL_UNLOCKED;

#if (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->SOFCallback = HAL_HCD_SOF_Callback;
    hhcd->ConnectCallback = HAL_HCD_Connect_Callback;
    hhcd->DisconnectCallback = HAL_HCD_Disconnect_Callback;
    hhcd->PortEnabledCallback = HAL_HCD_PortEnabled_Callback;
    hhcd->PortDisabledCallback = HAL_HCD_PortDisabled_Callback;
    hhcd->HC_NotifyURBChangeCallback = HAL_HCD_HC_NotifyURBChange_Callback;

    if (hhcd->MspInitCallback == NULL)
    {
      hhcd->MspInitCallback = HAL_HCD_MspInit;
    }

    /* Init the low level hardware */
    hhcd->MspInitCallback(hhcd);
#else
    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_HCD_MspInit(hhcd);
#endif /* (USE_HAL_HCD_REGISTER_CALLBACKS) */
  }
  hhcd->State = HAL_HCD_STATE_BUSY;

  /* Disable the Interrupts */
  (void)__HAL_HCD_DISABLE(hhcd);

  /*Init the Core (common init.) */
  (void)USB_CoreInit(hhcd->Instance, hhcd->Init);

  /* Force Host Mode*/
  (void)USB_SetCurrentMode(hhcd->Instance, USB_HOST_MODE);

  /* Init Host */
  (void)USB_HostInit(hhcd->Instance, hhcd->Init);

  /* Deactivate the power down*/
  hhcd->Instance->CNTR  &= ~USB_CNTR_PDWN;

  hhcd->State = HAL_HCD_STATE_READY;

  /*Host Port State*/
  hhcd->HostState = HCD_HCD_STATE_DISCONNECTED;

  /*Init PMA Address */
  (void)HAL_HCD_PMAReset(hhcd);

  hhcd->State = HAL_HCD_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Initialize a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  epnum Endpoint number.
  *          This parameter can be a value from 1 to 15
  * @param  dev_address Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed Current device speed.
  *          This parameter can be one of these values:
  *            HCD_SPEED_HIGH High speed mode,
  *            HCD_SPEED_FULL Full speed mode,
  *            HCD_SPEED_LOW Low speed mode
  * @param  ep_type Endpoint Type.
  *          This parameter can be one of these values:
  *            USBH_EP_CONTROL Control type,
  *            USBH_EP_ISO Isochronous type,
  *            USBH_EP_BULK Bulk type,
  *            USBH_EP_INTERRUPT Interrupt type
  * @param  mps Max Packet Size.
  *          This parameter can be a value from 0 to32K
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_HC_Init(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                  uint8_t epnum, uint8_t dev_address,
                                  uint8_t speed, uint8_t ep_type, uint16_t mps)
{
  HAL_StatusTypeDef status;
  uint8_t used_channel;

  __HAL_LOCK(hhcd);

  /* Check if the logical channel are already allocated */
  used_channel = HAL_HCD_Check_usedChannel(hhcd, ch_num);

  /*Check if the channel is not already opened */
  if (used_channel == 0U)
  {
    /*Allocate New Physical channel */
    hhcd->hc[ch_num & 0xFU].phy_ch_num = HAL_HCD_Get_FreePhyChannel(hhcd, ch_num, epnum, ep_type);

    /*if it is not able to allocate channel  */
    if (hhcd->hc[ch_num & 0xFU].phy_ch_num == HCD_FREE_CH_NOT_FOUND)
    {
      return HAL_ERROR;
    }
  }
  /* Channel already opened */
  else
  {
    /*Get Physical Channel number */
    hhcd->hc[ch_num & 0xFU].phy_ch_num = (used_channel & 0xF0U) >> 4U;
  }

  if ((epnum & 0x80U) != 0U)
  {
    hhcd->hc[ch_num & 0xFU].ch_dir = CH_IN_DIR;
  }
  else
  {
    hhcd->hc[ch_num & 0xFU].ch_dir = CH_OUT_DIR;
  }

  hhcd->hc[ch_num & 0xFU].dev_addr   = dev_address;
  hhcd->hc[ch_num & 0xFU].max_packet = mps;
  hhcd->hc[ch_num & 0xFU].ep_type    = ep_type;
  hhcd->hc[ch_num & 0xFU].ep_num     = epnum & 0x7FU;
  hhcd->hc[ch_num & 0xFU].speed      = speed;

  /*Check if the channel is not already opened */
  if (used_channel == 0U)
  {
    if (((ep_type == EP_TYPE_ISOC) && (hhcd->Init.iso_singlebuffer_enable == 0U)) ||
        ((ep_type == EP_TYPE_BULK) && (hhcd->Init.bulk_doublebuffer_enable == 1U)))
    {
      /* PMA Dynamic Allocation */
      status = HAL_HCD_PMAlloc(hhcd, ch_num, HCD_DBL_BUF, mps);
      if (status == HAL_ERROR)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* PMA Dynamic Allocation */
      status = HAL_HCD_PMAlloc(hhcd, ch_num, HCD_SNG_BUF, mps);
      if (status == HAL_ERROR)
      {
        return HAL_ERROR;
      }
    }
  }

  /* Init the USB Channel CHEPRx */
  status =  USB_HC_Init(hhcd->Instance, hhcd->hc[ch_num & 0xFU].phy_ch_num,
                        epnum, dev_address, speed, ep_type, mps);

  /* check single buffer for isochronous channel */
  if (ep_type == EP_TYPE_ISOC)
  {
    if (hhcd->Init.iso_singlebuffer_enable == 1U)
    {
      (void)USB_HC_DoubleBuffer(hhcd->Instance, hhcd->hc[ch_num & 0xFU].phy_ch_num, USB_DRD_DBUFF_ENBALE);
    }
    /*Init Buffer State */
    hhcd->hc[ch_num & 0xFU].pmabuff0_state = USB_PMABUF_EMPTY;
    hhcd->hc[ch_num & 0xFU].pmabuff1_state = USB_PMABUF_EMPTY;
  }

  /* Bulk double buffer check */
  if (ep_type == EP_TYPE_BULK)
  {
    if (hhcd->Init.bulk_doublebuffer_enable == 1U)
    {
      (void)USB_HC_DoubleBuffer(hhcd->Instance, hhcd->hc[ch_num & 0xFU].phy_ch_num, USB_DRD_DBUFF_ENBALE);
    }
  }
  __HAL_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  HAL_HCD_HC_Close Pipe
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_HC_Close(HCD_HandleTypeDef *hhcd, uint8_t ch_num)
{
  /* Stop the channel */
  (void) HAL_HCD_HC_Halt(hhcd, ch_num);

  HAL_Delay(3U);

  if (hhcd->hc[ch_num & 0xFU].ch_dir == CH_IN_DIR)
  {
    /* Free Allocated Channel */
    hhcd->phy_chin_state[hhcd->hc[ch_num & 0xFU].phy_ch_num] = 0U;
  }
  else
  {
    /* Free Allocated Channel */
    hhcd->phy_chout_state[hhcd->hc[ch_num & 0xFU].phy_ch_num] = 0U;
  }

  /* Reset PMA Channel_Allocation */
  (void)HAL_HCD_PMADeAlloc(hhcd, ch_num);

  return HAL_OK;
}

/**
  * @brief  Halt a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_HC_Halt(HCD_HandleTypeDef *hhcd, uint8_t ch_num)
{
  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(hhcd);
  if (hhcd->hc[ch_num & 0xFU].ch_dir == CH_IN_DIR)
  {
    (void)USB_HC_IN_Halt(hhcd->Instance, (uint8_t) hhcd->hc[ch_num & 0xFU].phy_ch_num);
  }
  else
  {
    (void)USB_HC_OUT_Halt(hhcd->Instance, (uint8_t) hhcd->hc[ch_num & 0xFU].phy_ch_num);
  }
  __HAL_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  DeInitialize the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_DeInit(HCD_HandleTypeDef *hhcd)
{
  uint8_t idx;

  /* Host Port State */
  hhcd->HostState = HCD_HCD_STATE_DISCONNECTED;

  /* Reset PMA Address */
  (void)HAL_HCD_PMAReset(hhcd);

  for (idx = 0U; idx < hhcd->Init.Host_channels; idx++)
  {
    hhcd->phy_chin_state[idx] = 0U;
    hhcd->phy_chout_state[idx] = 0U;
  }

  return HAL_OK;
}

/**
  * @brief  Initialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void  HAL_HCD_MspInit(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_MspInit could be implemented in the user file
  */
}

/**
  * @brief  DeInitialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void  HAL_HCD_MspDeInit(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_MspDeInit could be implemented in the user file
  */
}

__weak void HAL_HCD_SuspendCallback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_SuspendCallback could be implemented in the user file
  */

}

__weak void HAL_HCD_ResumeCallback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_ResumeCallback could be implemented in the user file
  */
}

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   HCD IO operation functions
  *
@verbatim
===============================================================================
##### IO operation functions #####
===============================================================================
[..] This subsection provides a set of functions allowing to manage the USB Host Data
Transfer

@endverbatim
  * @{
  */

/**
  * @brief  Submit a new URB for processing.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  direction Channel number.
  *          This parameter can be one of these values:
  *           0 : Output / 1 : Input
  * @param  ep_type Endpoint Type.
  *          This parameter can be one of these values:
  *            USBH_EP_CONTROL   : Control type/
  *            USBH_EP_ISO       : Isochronous type/
  *            USBH_EP_BULK      : Bulk type/
  *            USBH_EP_INTERRUPT : Interrupt type/
  * @param  token Endpoint Type.
  *          This parameter can be one of these values:
  *            0: HC_PID_SETUP / 1: HC_PID_DATA1
  * @param  pbuff pointer to URB data
  * @param  length Length of URB data
  * @param  do_ping activate do ping protocol (for high speed only).
  *          This parameter can be one of these values:
  *           0 : do ping inactive / 1 : do ping active
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_HC_SubmitRequest(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                           uint8_t direction, uint8_t ep_type,
                                           uint8_t token, uint8_t *pbuff,
                                           uint16_t length, uint8_t do_ping)
{
  UNUSED(do_ping);

  if (token == 0U)
  {
    hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_SETUP;
  }
  else
  {
    hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA1;
  }

  /* Manage Data Toggle */
  switch (ep_type)
  {
    case EP_TYPE_CTRL:
      if ((token == 1U) && (direction == 0U)) /* send data */
      {
        if (length == 0U)
        {
          /* For Status OUT stage, Length==0, Status Out PID = 1 */
          hhcd->hc[ch_num & 0xFU].toggle_out = 1U;
        }

        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->hc[ch_num & 0xFU].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA1;
        }
      }
      break;

    case EP_TYPE_BULK:
      if (direction == 0U)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->hc[ch_num & 0xFU].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->hc[ch_num & 0xFU].toggle_in == 0U)
        {
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA0;
        }
        else
        {
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA1;
        }
      }
      break;

    case EP_TYPE_INTR:
      if (direction == 0U)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->hc[ch_num & 0xFU].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->hc[ch_num & 0xFU].toggle_in == 0U)
        {
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA0;
        }
        else
        {
          hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA1;
        }
      }
      break;

    case EP_TYPE_ISOC:
      hhcd->hc[ch_num & 0xFU].data_pid = HC_PID_DATA0;
      break;

    default:
      break;
  }

  hhcd->hc[ch_num & 0xFU].xfer_buff = pbuff;
  hhcd->hc[ch_num & 0xFU].xfer_len  = length;
  hhcd->hc[ch_num & 0xFU].xfer_len_db  = length;
  hhcd->hc[ch_num & 0xFU].urb_state = URB_IDLE;
  hhcd->hc[ch_num & 0xFU].xfer_count = 0U;
  hhcd->hc[ch_num & 0xFU].state = HC_IDLE;

  return USB_HC_StartXfer(hhcd->Instance, &hhcd->hc[ch_num & 0xFU]);
}
/**
  * @brief  Handle HCD interrupt request.
  * @param  hhcd HCD handle
  * @retval None
  */
void HAL_HCD_IRQHandler(HCD_HandleTypeDef *hhcd)
{
  uint8_t phy_chnum;
  uint8_t chnum;
  uint32_t epch_reg;

  /* Port Change Detected (Connection/Disconnection) */
  if (__HAL_HCD_GET_FLAG(hhcd, USB_ISTR_DCON))
  {
    /* Clear Flag */
    __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_DCON);

    /* Call Port IRQHandler */
    HCD_Port_IRQHandler(hhcd);
  }

  /* Correct Transaction Detected -------*/
  if (__HAL_HCD_GET_FLAG(hhcd, USB_ISTR_CTR))
  {
    /* Handle Host channel Interrupt */
    for (phy_chnum = 0U; phy_chnum < hhcd->Init.Host_channels; phy_chnum++)
    {
      if ((HCD_GET_CHANNEL(hhcd->Instance, phy_chnum)  &USB_CH_VTRX) != 0U)
      {
        /* Get Logical channel to check if the channel is already opened */
        chnum = HAL_HCD_GetLogical_Channel(hhcd, phy_chnum, 1U);

        if (chnum != HCD_LOGICAL_CH_NOT_OPENED)
        {
          /* Call Channel_IN_IRQ() */
          HCD_HC_IN_IRQHandler(hhcd, chnum);
        }
        else
        {
          /*Channel was not closed correctly still have interrupt */
          epch_reg = HCD_GET_CHANNEL(hhcd->Instance, phy_chnum);
          epch_reg = (epch_reg & (USB_CHEP_REG_MASK & (~USB_CH_ERRRX) & (~USB_CH_VTRX))) |
                     (USB_CH_VTTX | USB_CH_ERRTX);

          HCD_SET_CHANNEL(hhcd->Instance, phy_chnum, epch_reg);
        }
      }

      if ((HCD_GET_CHANNEL(hhcd->Instance, phy_chnum)  &USB_CH_VTTX) != 0U)
      {
        /*Get Logical channel to check if the channel is already opened*/
        chnum = HAL_HCD_GetLogical_Channel(hhcd, phy_chnum, 0U);

        if (chnum != HCD_LOGICAL_CH_NOT_OPENED)
        {
          /*Call Channel_OUT_IRQ()*/
          HCD_HC_OUT_IRQHandler(hhcd, chnum);
        }
        else
        {
          /*Clear Error & unwanted VTTX or Channel was not closed correctly */
          epch_reg = HCD_GET_CHANNEL(hhcd->Instance, phy_chnum);
          epch_reg = (epch_reg & (USB_CHEP_REG_MASK & (~USB_CH_ERRTX) & (~USB_CH_VTTX))) |
                     (USB_CH_VTRX | USB_CH_ERRRX);

          HCD_SET_CHANNEL(hhcd->Instance, phy_chnum, epch_reg);
        }
      }
    }

    /* Clear Correct Transfer */
    __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_CTR);

  }

  /* Wakeup Flag Detected */
  if (__HAL_HCD_GET_FLAG(hhcd, USB_ISTR_WKUP))
  {
    if (hhcd->HostState == HCD_HCD_STATE_SUSPEND)
    {
      /* Set The L2Resume bit */
      hhcd->Instance->CNTR |= USB_CNTR_L2RES;

      /* Clear the wake-up flag */
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_WKUP);

      /* Update the USB Software state machine */
      HAL_HCD_ResumeCallback(hhcd);
      hhcd->HostState = HCD_HCD_STATE_RESUME;
    }
    else
    {
      /*Clear the wake-up flag*/
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_WKUP);
    }
  }

  /*Global Error Flag Detected */
  if (__HAL_HCD_GET_FLAG(hhcd, USB_ISTR_ERR))
  {
    __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_ERR);
  }

  /* PMA Overrun detected */
  if (__HAL_HCD_GET_FLAG(hhcd, USB_ISTR_PMAOVR))
  {
    __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_PMAOVR);
  }

  /* Suspend Detected */
  if (__HAL_HCD_GET_FLAG(hhcd, USB_ISTR_SUSP))
  {
    /*Set HAL State to Suspend */
    hhcd->HostState = HCD_HCD_STATE_SUSPEND;

    /* Force low-power mode in the macrocell */
    hhcd->Instance->CNTR |= USB_CNTR_SUSPEN;

    /* clear of the ISTR bit must be done after setting of CNTR_FSUSP */
    __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_SUSP);

    /*Call suspend Callback*/
    HAL_HCD_SuspendCallback(hhcd);
  }

  /*Start Of Frame Detected */
  if (__HAL_HCD_GET_FLAG(hhcd, USB_ISTR_SOF))
  {
#if (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->SOFCallback(hhcd);
#else
    HAL_HCD_SOF_Callback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    __HAL_HCD_CLEAR_FLAG(hhcd, USB_ISTR_SOF);

    /* when first SOF is detected after USB_RESET is asserted */
    if (hhcd->HostState == HCD_HCD_STATE_RESETED)
    {
      /* HAL State */
      hhcd->HostState = HCD_HCD_STATE_RUN;
      HAL_HCD_PortEnabled_Callback(hhcd);
    }
  }
}

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_SOF_Callback could be implemented in the user file
  */
}

/**
  * @brief Connection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_Connect_Callback could be implemented in the user file
  */
}

/**
  * @brief  Disconnection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_Disconnect_Callback could be implemented in the user file
  */
}
/**
  * @brief  Port Enabled  Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_Disconnect_Callback could be implemented in the user file
   */
}
/**
  * @brief  Port Disabled  Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_Disconnect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Notify URB state change callback.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  urb_state
  *          This parameter can be one of these values:
  *            URB_IDLE/
  *            URB_DONE/
  *            URB_NOTREADY/
  *            URB_NYET/
  *            URB_ERROR/
  *            URB_STALL/
  * @retval None
  */
__weak void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd,
                                                uint8_t chnum, HCD_URBStateTypeDef urb_state)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);
  UNUSED(chnum);
  UNUSED(urb_state);

  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_HCD_HC_NotifyURBChange_Callback could be implemented in the user file
  */
}
#if (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User USB HCD Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_HCD_SOF_CB_ID USB HCD SOF callback ID
  *          @arg @ref HAL_HCD_CONNECT_CB_ID USB HCD Connect callback ID
  *          @arg @ref HAL_HCD_DISCONNECT_CB_ID HCD Disconnect callback ID
  *          @arg @ref HAL_HCD_PORT_ENABLED_CB_ID USB HCD Port Enable callback ID
  *          @arg @ref HAL_HCD_PORT_DISABLED_CB_ID USB HCD Port Disable callback ID
  *          @arg @ref HAL_HCD_MSPINIT_CB_ID MspDeInit callback ID
  *          @arg @ref HAL_HCD_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_RegisterCallback(HCD_HandleTypeDef *hhcd,
                                           HAL_HCD_CallbackIDTypeDef CallbackID,
                                           pHCD_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hhcd);

  if (hhcd->State == HAL_HCD_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_HCD_SOF_CB_ID :
        hhcd->SOFCallback = pCallback;
        break;

      case HAL_HCD_CONNECT_CB_ID :
        hhcd->ConnectCallback = pCallback;
        break;

      case HAL_HCD_DISCONNECT_CB_ID :
        hhcd->DisconnectCallback = pCallback;
        break;

      case HAL_HCD_PORT_ENABLED_CB_ID :
        hhcd->PortEnabledCallback = pCallback;
        break;

      case HAL_HCD_PORT_DISABLED_CB_ID :
        hhcd->PortDisabledCallback = pCallback;
        break;

      case HAL_HCD_MSPINIT_CB_ID :
        hhcd->MspInitCallback = pCallback;
        break;

      case HAL_HCD_MSPDEINIT_CB_ID :
        hhcd->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hhcd->State == HAL_HCD_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_HCD_MSPINIT_CB_ID :
        hhcd->MspInitCallback = pCallback;
        break;

      case HAL_HCD_MSPDEINIT_CB_ID :
        hhcd->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hhcd);
  return status;
}

/**
  * @brief  Unregister an USB HCD Callback
  *         USB HCD callback is redirected to the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_HCD_SOF_CB_ID USB HCD SOF callback ID
  *          @arg @ref HAL_HCD_CONNECT_CB_ID USB HCD Connect callback ID
  *          @arg @ref HAL_HCD_DISCONNECT_CB_ID DRD HCD Disconnect callback ID
  *          @arg @ref HAL_HCD_PORT_ENABLED_CB_ID USB HCD Port Enabled callback ID
  *          @arg @ref HAL_HCD_PORT_DISABLED_CB_ID USB HCD Port Disabled callback ID
  *          @arg @ref HAL_HCD_MSPINIT_CB_ID MspDeInit callback ID
  *          @arg @ref HAL_HCD_MSPDEINIT_CB_ID MspDeInit callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_UnRegisterCallback(HCD_HandleTypeDef *hhcd,
                                             HAL_HCD_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hhcd);

  /* Setup Legacy weak Callbacks  */
  if (hhcd->State == HAL_HCD_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_HCD_SOF_CB_ID :
        hhcd->SOFCallback = HAL_HCD_SOF_Callback;
        break;

      case HAL_HCD_CONNECT_CB_ID :
        hhcd->ConnectCallback = HAL_HCD_Connect_Callback;
        break;

      case HAL_HCD_DISCONNECT_CB_ID :
        hhcd->DisconnectCallback = HAL_HCD_Disconnect_Callback;
        break;

      case HAL_HCD_PORT_ENABLED_CB_ID :
        hhcd->PortEnabledCallback = HAL_HCD_PortEnabled_Callback;
        break;

      case HAL_HCD_PORT_DISABLED_CB_ID :
        hhcd->PortDisabledCallback = HAL_HCD_PortDisabled_Callback;
        break;

      case HAL_HCD_MSPINIT_CB_ID :
        hhcd->MspInitCallback = HAL_HCD_MspInit;
        break;

      case HAL_HCD_MSPDEINIT_CB_ID :
        hhcd->MspDeInitCallback = HAL_HCD_MspDeInit;
        break;

      default :
        /* Update the error code */
        hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hhcd->State == HAL_HCD_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_HCD_MSPINIT_CB_ID :
        hhcd->MspInitCallback = HAL_HCD_MspInit;
        break;

      case HAL_HCD_MSPDEINIT_CB_ID :
        hhcd->MspDeInitCallback = HAL_HCD_MspDeInit;
        break;

      default :
        /* Update the error code */
        hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hhcd);
  return status;
}

/**
  * @brief  Register USB HCD Host Channel Notify URB Change Callback
  *         To be used instead of the weak HAL_HCD_HC_NotifyURBChange_Callback() predefined callback
  * @param  hhcd HCD handle
  * @param  pCallback pointer to the USB HCD Host Channel Notify URB Change Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_RegisterHC_NotifyURBChangeCallback(HCD_HandleTypeDef *hhcd,
                                                             pHCD_HC_NotifyURBChangeCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hhcd);

  if (hhcd->State == HAL_HCD_STATE_READY)
  {
    hhcd->HC_NotifyURBChangeCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status = HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  Unregister the USB HCD Host Channel Notify URB Change Callback
  *         USB HCD Host Channel Notify URB Change Callback is redirected
  *         to the weak HAL_HCD_HC_NotifyURBChange_Callback() predefined callback
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_UnRegisterHC_NotifyURBChangeCallback(HCD_HandleTypeDef *hhcd)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hhcd);

  if (hhcd->State == HAL_HCD_STATE_READY)
  {
    hhcd->HC_NotifyURBChangeCallback = HAL_HCD_HC_NotifyURBChange_Callback; /* Legacy weak DataOutStageCallback */
  }
  else
  {
    /* Update the error code */
    hhcd->ErrorCode |= HAL_HCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hhcd);

  return status;
}
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */


/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   Management functions
  *
@verbatim
===============================================================================
##### Peripheral Control functions #####
===============================================================================
[..]
This subsection provides a set of functions allowing to control the HCD data
transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_Start(HCD_HandleTypeDef *hhcd)
{
  __HAL_LOCK(hhcd);

  /*Set the PullDown on the PHY */
  hhcd->Instance->BCDR |= USB_BCDR_DPPD;

  /* Clear Reset  */
  hhcd->Instance->CNTR &= ~USB_CNTR_USBRST;

  /*Remove PowerDown */
  hhcd->Instance->CNTR &= ~USB_CNTR_PDWN;

  __HAL_UNLOCK(hhcd);

  return HAL_OK;
}

/**
  * @brief  Stop the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_Stop(HCD_HandleTypeDef *hhcd)
{
  __HAL_LOCK(hhcd);
  /*Stop the Host IP: setting powerdown  */
  (void)USB_StopHost(hhcd->Instance);

  /* clear all allocated virtual channel */
  HAL_HCD_ClearPhyChannel(hhcd);

  /* Reset the PMA current pointer */
  (void)HAL_HCD_PMAReset(hhcd);

  __HAL_UNLOCK(hhcd);
  return HAL_OK;
}

/**
  * @brief  Put the Device in suspend mode
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_Suspend(HCD_HandleTypeDef *hhcd)
{
  uint32_t count = 0U;

  /* Set Suspend Mode */
  hhcd->Instance->CNTR |= USB_CNTR_SUSPEN;

  /* wait for Suspend Ready */
  while ((hhcd->Instance->CNTR & USB_CNTR_SUSPRDY) == 0U)
  {
    if (++count > 0xFFFFFFU)
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Resume host port
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_Resume(HCD_HandleTypeDef *hhcd)
{
  /* Set Resume bit */
  hhcd->Instance->CNTR |= USB_CNTR_L2RES;

  return HAL_OK;
}

/**
  * @brief  Reset the host port.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_ResetPort(HCD_HandleTypeDef *hhcd)
{
  __HAL_LOCK(hhcd);

  /* Reset the USB Port by inserting an SE0 on the bus */
  (void)USB_ResetPort(hhcd->Instance);

  if (hhcd->HostState == HCD_HCD_STATE_CONNECTED)
  {
    hhcd->HostState = HCD_HCD_STATE_RESETED;
  }
  __HAL_UNLOCK(hhcd);

  return HAL_OK;
}

/**
  * @brief  Resme the host port.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_ResumePort(HCD_HandleTypeDef *hhcd)
{
  /* Set Resume bit */
  hhcd->Instance->CNTR |= USB_CNTR_L2RES;
  HAL_Delay(30U);

  /* Clear Resume bit */
  hhcd->Instance->CNTR &= ~USB_CNTR_L2RES;

  return HAL_OK;
}


/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions
  *
@verbatim
===============================================================================
##### Peripheral State functions #####
===============================================================================
[..]
This subsection permits to get in run-time the status of the peripheral
and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the HCD handle state.
  * @param  hhcd HCD handle
  * @retval HAL state
  */
HCD_StateTypeDef HAL_HCD_GetState(HCD_HandleTypeDef *hhcd)
{
  return hhcd->State;
}

/**
  * @brief  Return  URB state for a channel.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval URB state.
  *          This parameter can be one of these values:
  *            URB_IDLE/
  *            URB_DONE/
  *            URB_NOTREADY/
  *            URB_NYET/
  *            URB_ERROR/
  *            URB_STALL
  */
HCD_URBStateTypeDef HAL_HCD_HC_GetURBState(HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  return hhcd->hc[chnum].urb_state;
}


/**
  * @brief  Return the last host transfer size.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval last transfer size in byte
  */
uint32_t HAL_HCD_HC_GetXferCount(HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  return hhcd->hc[chnum].xfer_count;
}

/**
  * @brief  Return the Host Channel state.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval Host channel state
  *          This parameter can be one of these values:
  *            HC_IDLE/
  *            HC_XFRC/
  *            HC_HALTED/
  *            HC_NYET/
  *            HC_NAK/
  *            HC_STALL/
  *            HC_XACTERR/
  *            HC_BBLERR/
  *            HC_DATATGLERR
  */
HCD_HCStateTypeDef  HAL_HCD_HC_GetState(HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  return hhcd->hc[chnum].state;
}

/**
  * @brief  Return the current Host frame number.
  * @param  hhcd HCD handle
  * @retval Current Host frame number
  */
uint32_t HAL_HCD_GetCurrentFrame(HCD_HandleTypeDef *hhcd)
{
  return (USB_GetCurrentFrame(hhcd->Instance));
}

/**
  * @brief  Return the Host enumeration speed.
  * @param  hhcd HCD handle
  * @retval Enumeration speed
  */
uint32_t HAL_HCD_GetCurrentSpeed(HCD_HandleTypeDef *hhcd)
{
  return (USB_GetHostSpeed(hhcd->Instance));
}

/**
  * @brief  Handle Host Channel OUT Double Buffer Bulk requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number This parameter can be a value from 1 to 15
  * @param  phy_chnum Physical Channel number [0..7]
  * @param  regvalue contain Snapshot of the EPCHn register when ISR is detected
  * @retval none
  */
static void HCD_HC_OUT_BulkDb(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                              uint8_t phy_chnum, uint32_t regvalue)
{
  uint16_t data_xfr;
  uint16_t len;

  /* Send Buffer0 */
  if ((regvalue & USB_CH_DTOG_TX) != 0U)
  {
    data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + phy_chnum)->TXBD & 0x03FF0000U) >> 16U);

    if (hhcd->hc[ch_num & 0xFU].xfer_len >= data_xfr)
    {
      hhcd->hc[ch_num & 0xFU].xfer_len -= data_xfr;
    }
    else
    {
      hhcd->hc[ch_num & 0xFU].xfer_len = 0U;
    }

    /* Transfer no yet finished only one packet of mps is transferred and ACKed from device */
    if (hhcd->hc[ch_num & 0xFU].xfer_len != 0U)
    {
      /* manage multiple Xfer */
      hhcd->hc[ch_num & 0xFU].xfer_count  += data_xfr;

      /* check if we need to free user buffer */
      if ((regvalue & USB_CH_DTOG_RX) != 0U)
      {
        /* Toggle SwBuff */
        HCD_FreeUserBuffer(hhcd->Instance, phy_chnum, 1U);
      }

      /* hhcd->hc[ch_num&0xFU].xfer_len_db==0 ==> when all data are written in the PMA to yet transferred */
      if (hhcd->hc[ch_num & 0xFU].xfer_len_db > 0U) /* Still data to fill in the buffer */
      {
        hhcd->hc[ch_num & 0xFU].xfer_buff += data_xfr;

        /* calculate len of new buffer to fill */
        if (hhcd->hc[ch_num & 0xFU].xfer_len_db > hhcd->hc[ch_num & 0xFU].max_packet)
        {
          len = (uint16_t)hhcd->hc[ch_num & 0xFU].max_packet;
          hhcd->hc[ch_num & 0xFU].xfer_len_db -= len;
        }
        else
        {
          len = (uint16_t)hhcd->hc[ch_num & 0xFU].xfer_len_db;
          hhcd->hc[ch_num & 0xFU].xfer_len_db = 0U; /* end of fill buffer */
        }

        /* Write remaining data to Buffer0 */
        HCD_SET_CH_TX_CNT(hhcd->Instance, phy_chnum, (uint16_t)len);
        USB_WritePMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                     hhcd->hc[ch_num & 0xFU].pmaaddr0, (uint16_t)len);
      }
      /* start a new transfer */
      HCD_SET_CH_TX_STATUS(hhcd->Instance, phy_chnum, USB_CH_TX_VALID);
    }
    else
    {
      /* Transfer complete state */
      hhcd->hc[ch_num & 0xFU].xfer_count  += data_xfr;
      hhcd->hc[ch_num & 0xFU].state = HC_XFRC;
      hhcd->hc[ch_num & 0xFU].urb_state  = URB_DONE;
      hhcd->hc[ch_num & 0xFU].toggle_out ^= 1U;
      /* Close the Channel */
      HCD_SET_CH_TX_STATUS(hhcd->Instance, phy_chnum, USB_CH_TX_DIS);
    }
  }
  else
  {
    /* Send Buffer1 */
    data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + phy_chnum)->RXBD & 0x03FF0000U) >> 16U);

    if (hhcd->hc[ch_num & 0xFU].xfer_len >= data_xfr) /* updated */
    {
      hhcd->hc[ch_num & 0xFU].xfer_len -= data_xfr;
    }

    /* Transfer no yet finished only one packet of mps is transferred and ACKed from device */
    if (hhcd->hc[ch_num & 0xFU].xfer_len != 0U)
    {
      /* manage multiple Xfer */
      hhcd->hc[ch_num & 0xFU].xfer_count  += data_xfr;

      /* check if we need to free user buffer */
      if ((regvalue & USB_CH_DTOG_RX) == 0U)
      {
        /* Toggle SwBuff */
        HCD_FreeUserBuffer(hhcd->Instance, phy_chnum, 1U);
      }

      /* hhcd->hc[ch_num&0xFU].xfer_len_db==0 ==> when all data are written in the PMA to yet transferred */
      if (hhcd->hc[ch_num & 0xFU].xfer_len_db > 0U) /* Still data to fill in the buffer */
      {
        hhcd->hc[ch_num & 0xFU].xfer_buff += data_xfr;

        /* calculate len of new buffer to fill */
        if (hhcd->hc[ch_num & 0xFU].xfer_len_db > hhcd->hc[ch_num & 0xFU].max_packet)
        {
          len = hhcd->hc[ch_num & 0xFU].max_packet;
          hhcd->hc[ch_num & 0xFU].xfer_len_db -= len;
        }
        else
        {
          len = (uint16_t)hhcd->hc[ch_num & 0xFU].xfer_len_db;
          hhcd->hc[ch_num & 0xFU].xfer_len_db = 0U; /* end of fill buffer */
        }

        /* Write remaining data to Buffer0 */
        HCD_SET_CH_DBUF1_CNT(hhcd->Instance, phy_chnum, 0U, (uint16_t)len);

        USB_WritePMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                     hhcd->hc[ch_num & 0xFU].pmaaddr1, (uint16_t)len);
      }
      /* start a new transfer */
      HCD_SET_CH_TX_STATUS(hhcd->Instance, phy_chnum, USB_CH_TX_VALID);
    }
    else
    {
      /* Transfer complete state */
      hhcd->hc[ch_num & 0xFU].xfer_count  += data_xfr;
      hhcd->hc[ch_num & 0xFU].state = HC_XFRC;
      hhcd->hc[ch_num & 0xFU].urb_state  = URB_DONE;
      hhcd->hc[ch_num & 0xFU].toggle_out ^= 1U;
      /* Close the channel */
      HCD_SET_CH_TX_STATUS(hhcd->Instance, phy_chnum, USB_CH_TX_DIS);
    }
  }
}


/**
  * @brief  Handle Host Channel IN Isochronous Transaction
  * @param  hhcd HCD handle
  * @param  ch_num Channel number: This parameter can be a value from 1 to 15
  * @param  phy_chnum Physical Channel number [0..7]
  * @param  regvalue contain Snapshot of the EPCHn register when ISR is detected
  * @retval none
  */
static void inline HCD_HC_IN_ISO(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                 uint8_t phy_chnum, uint32_t regvalue)
{
  /* Check if Double buffer isochronous */
  if ((regvalue & USB_CH_KIND) == 0U)
  {
    /* Read from Buffer0 */
    if ((regvalue & USB_CH_DTOG_RX) != 0U)
    {
      /* Get number of Received byte in buffer0 */
      hhcd->hc[ch_num & 0xFU].xfer_count = HCD_GET_CH_DBUF0_CNT(hhcd->Instance, phy_chnum);

      if (hhcd->hc[ch_num & 0xFU].xfer_count != 0U)
      {
        /* Read from Buffer0 */
        USB_ReadPMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                    hhcd->hc[ch_num & 0xFU].pmaaddr0,
                    (uint16_t)hhcd->hc[ch_num & 0xFU].xfer_count);

        hhcd->hc[ch_num & 0xFU].urb_state  = URB_DONE;
      }
    }
    else
    {
      /* Get number of Received byte in buffer1 */
      hhcd->hc[ch_num & 0xFU].xfer_count = HCD_GET_CH_DBUF1_CNT(hhcd->Instance, phy_chnum);

      if (hhcd->hc[ch_num & 0xFU].xfer_count != 0U)
      {
        /* Read from Buffer1 */
        USB_ReadPMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                    hhcd->hc[ch_num & 0xFU].pmaaddr1,
                    (uint16_t)hhcd->hc[ch_num & 0xFU].xfer_count);

        hhcd->hc[ch_num & 0xFU].urb_state = URB_DONE;
      }
    }
  }
  else  /* single buffer isochronous */
  {
    /* Get Control Data OUT Packet*/
    hhcd->hc[ch_num & 0xFU].xfer_count = HCD_GET_CH_RX_CNT(hhcd->Instance, phy_chnum);
    if (hhcd->hc[ch_num & 0xFU].xfer_count != 0U)
    {
      USB_ReadPMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                  hhcd->hc[ch_num & 0xFU].pmaadress,
                  (uint16_t)hhcd->hc[ch_num & 0xFU].xfer_count);

      hhcd->hc[ch_num & 0xFU].urb_state = URB_DONE;
    }
  }

  /* Transfer complete state */
  hhcd->hc[ch_num & 0xFU].state = HC_XFRC;

  /* Clear VTRX */
  HCD_CLEAR_RX_CH_CTR(hhcd->Instance, phy_chnum);

}
/**
  * @brief  Handle Host Channel IN Double Buffer Bulk requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number: This parameter can be a value from 1 to 15
  * @param  phy_chnum Physical Channel number [0..7]
  * @param  regvalue contain Snapshot of the EPCHn register when ISR is detected
  * @retval none
  */
static void HCD_HC_IN_BulkDb(HCD_HandleTypeDef *hhcd,
                             uint8_t ch_num, uint8_t phy_chnum, uint32_t regvalue)
{
  uint16_t received_bytes;

  /* Read from Buffer 0 */
  if ((regvalue & USB_CH_DTOG_RX) != 0U)
  {
    received_bytes = (uint16_t)HCD_GET_CH_DBUF0_CNT(hhcd->Instance, phy_chnum);

    if (hhcd->hc[ch_num & 0xFU].xfer_len <= received_bytes)
    {
      hhcd->hc[ch_num & 0xFU].xfer_len = 0U;
    }
    else
    {
      hhcd->hc[ch_num & 0xFU].xfer_len -= received_bytes;
    }
    /* Check if we Need to free the other buffer for the IP */
    if ((hhcd->hc[ch_num & 0xFU].xfer_len != 0U) && ((regvalue & USB_CH_DTOG_TX) != 0U))
    {
      /* Toggle SwBuff */
      HCD_FreeUserBuffer(hhcd->Instance, phy_chnum, 0U);/* Allow the IP to submit a new IN */
    }
    /* Read the byte from PMA to user Buffer(System Memory) */
    USB_ReadPMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                hhcd->hc[ch_num & 0xFU].pmaaddr0, (uint16_t)received_bytes);
  }
  else
  {
    /* Read from Buffer 1 */
    received_bytes = (uint16_t) HCD_GET_CH_DBUF1_CNT(hhcd->Instance, phy_chnum);

    if (hhcd->hc[ch_num & 0xFU].xfer_len <= received_bytes)
    {
      hhcd->hc[ch_num & 0xFU].xfer_len = 0U;
    }
    else
    {
      hhcd->hc[ch_num & 0xFU].xfer_len -= received_bytes;
    }

    /* Check if we Need to free the other buffer for the IP */
    if ((hhcd->hc[ch_num & 0xFU].xfer_len != 0U) && ((regvalue & USB_CH_DTOG_TX) == 0U))
    {
      /* Toggle SwBuff */
      HCD_FreeUserBuffer(hhcd->Instance, phy_chnum, 0U);
    }

    /* Read the byte from PMA to user Buffer(System Memory) */
    USB_ReadPMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                hhcd->hc[ch_num & 0xFU].pmaaddr1, (uint16_t)received_bytes);
  }

  /* update the global number of all received bytes */
  hhcd->hc[ch_num & 0xFU].xfer_count += received_bytes;

  /* Transfer complete state */
  hhcd->hc[ch_num & 0xFU].state = HC_ACK;
  hhcd->hc[ch_num & 0xFU].ErrCnt = 0U;

  if ((hhcd->hc[ch_num & 0xFU].xfer_len == 0U) ||
      ((received_bytes < hhcd->hc[ch_num & 0xFU].max_packet)))
  {
    hhcd->hc[ch_num & 0xFU].urb_state  = URB_DONE;
    hhcd->hc[ch_num & 0xFU].state  = HC_XFRC;

    /* disable channel */
    HCD_SET_CH_RX_STATUS(hhcd->Instance, phy_chnum, USB_CH_RX_DIS);
  }
  else
  {
    hhcd->hc[ch_num & 0xFU].xfer_buff += received_bytes;

    /* Reactivate the Channel Submit an other URB since the Transfer is not yet completed */
    HCD_SET_CH_RX_STATUS(hhcd->Instance, phy_chnum, USB_CH_RX_STRX);
  }
}

/**
  * @brief  Handle Host Channel IN interrupt requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_HC_IN_IRQHandler(HCD_HandleTypeDef *hhcd, uint8_t ch_num)
{
  uint16_t received_bytes;
  uint8_t phy_chnum = (uint8_t)__HAL_HCD_GET_CHNUM(hhcd);

  /*Take a Flag snapshot from the CHEP register, due to STRX bits are used for both control and status */
  uint32_t ch_reg =  HCD_GET_CHANNEL(hhcd->Instance, phy_chnum);

  /* Manage Correct Transaction */
  if ((ch_reg & USB_CH_ERRRX) == 0U)
  {
    /* Isochronous Channel */
    if ((ch_reg & USB_CH_UTYPE) == USB_EP_ISOCHRONOUS)
    {
      HCD_HC_IN_ISO(hhcd, ch_num, phy_chnum, ch_reg);
    }
    else
    {
      /* manage ACK response single buffer */
      if (((ch_reg) & USB_CH_RX_STRX) == USB_CH_RX_ACK_SBUF)
      {
        /* Get Control Data OUT Packet */
        received_bytes = (uint16_t)HCD_GET_CH_RX_CNT(hhcd->Instance, phy_chnum);

        /* Read the byte from PMA to user Buffer(System Memory) */
        USB_ReadPMA(hhcd->Instance, hhcd->hc[ch_num & 0xFU].xfer_buff,
                    hhcd->hc[ch_num & 0xFU].pmaadress, (uint16_t)received_bytes);

        /* update the global number of all received bytes */
        hhcd->hc[ch_num & 0xFU].xfer_count += received_bytes;

        /* Transfer complete state */
        hhcd->hc[ch_num & 0xFU].state = HC_ACK;
        hhcd->hc[ch_num & 0xFU].ErrCnt = 0U;
        if (hhcd->hc[ch_num & 0xFU].xfer_len <= received_bytes)
        {
          hhcd->hc[ch_num & 0xFU].xfer_len = 0U;
        }
        else
        {
          hhcd->hc[ch_num & 0xFU].xfer_len -= received_bytes;
        }
        if ((hhcd->hc[ch_num & 0xFU].xfer_len == 0U) ||
            ((received_bytes < hhcd->hc[ch_num & 0xFU].max_packet)))
        {
          hhcd->hc[ch_num & 0xFU].urb_state  = URB_DONE;
          hhcd->hc[ch_num & 0xFU].state  = HC_XFRC;
        }
        else
        {
          hhcd->hc[ch_num & 0xFU].xfer_buff += received_bytes;

          /* Reactivate the Channel to Submit another URB since the Transfer is not yet completed */
          HCD_SET_CH_RX_STATUS(hhcd->Instance, phy_chnum, USB_CH_RX_STRX);
        }
        if ((hhcd->hc[ch_num & 0xFU].ep_type == EP_TYPE_BULK) ||
            (hhcd->hc[ch_num & 0xFU].ep_type == EP_TYPE_INTR))
        {
          hhcd->hc[ch_num & 0xFU].toggle_out ^= 1U;
        }
      }

      /* manage NACK Response */
      else if (((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_NAK)
               && (hhcd->hc[ch_num & 0xFU].urb_state != URB_DONE))
      {
        hhcd->hc[ch_num & 0xFU].urb_state = URB_NOTREADY;
        hhcd->hc[ch_num & 0xFU].ErrCnt = 0U;
        hhcd->hc[ch_num & 0xFU].state = HC_NAK;
      }

      /* manage STALL Response */
      else if ((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_STALL)
      {
        (void)HAL_HCD_HC_Halt(hhcd, (uint8_t)ch_num);
        hhcd->hc[ch_num & 0xFU].state = HC_STALL;
        hhcd->hc[ch_num & 0xFU].urb_state = URB_STALL;

        /* Close the channel */
        HCD_SET_CH_RX_STATUS(hhcd->Instance, phy_chnum, USB_CH_RX_DIS);
      }

      /* Double Buffer Management in case of Bulk Transaction */
      else  if (((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_ACK_DBUF)
                && ((ch_reg & USB_CH_KIND) != 0U))
      {
        /* Bulk IN Double Buffer ISR */
        HCD_HC_IN_BulkDb(hhcd, ch_num, phy_chnum, ch_reg);
      }
      else
      {
        /*....*/
        /* not defined state: STRX=11 in single buffer no iso is not defined */
      }
      HAL_HCD_HC_NotifyURBChange_Callback(hhcd, (uint8_t)ch_num,
                                          hhcd->hc[ch_num & 0xFU].urb_state);

      /*Clear VTRX */
      HCD_CLEAR_RX_CH_CTR(hhcd->Instance, phy_chnum);
    }
  }
  else   /* Error detected during last transaction */
  {
    /* Set URB Error State */
    hhcd->hc[ch_num & 0xFU].urb_state = URB_NOTREADY;
    hhcd->hc[ch_num & 0xFU].ErrCnt++;
    hhcd->hc[ch_num & 0xFU].state = HC_XACTERR;

    /* Clear VTTRX & ERR_RX */
    HCD_CLEAR_RX_CH_ERR(hhcd->Instance, phy_chnum);

    /* Check Error number */
    if (hhcd->hc[ch_num & 0xFU].ErrCnt > 3U)
    {
      hhcd->hc[ch_num & 0xFU].urb_state = URB_ERROR;
      HCD_SET_CH_RX_STATUS(hhcd->Instance, phy_chnum, USB_CH_RX_DIS);

      /* Clear pending err_tx */
      HCD_CLEAR_RX_CH_ERR(hhcd->Instance, phy_chnum);
    }
    HAL_HCD_HC_NotifyURBChange_Callback(hhcd, (uint8_t)ch_num,
                                        hhcd->hc[ch_num & 0xFU].urb_state);
  }
}


/**
  * @brief  Handle Host Channel OUT interrupt requests.
  * @param  hhcd  HCD handle
  * @param  chnum Channel number
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_HC_OUT_IRQHandler(HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  uint16_t data_xfr;

  /* Get Physical Channel number */
  uint32_t phy_chnum = (uint8_t)__HAL_HCD_GET_CHNUM(hhcd);

  /* Take a Flag snapshot from the CHEP register, due to STRX bits are used for both control &status */
  __IO uint32_t ch_reg =  *(__IO uint32_t *)(&(hhcd->Instance->CHEP0R) + phy_chnum);

  /*------ Manage Correct Transaction ------*/
  if ((ch_reg & USB_CH_ERRTX) == 0U)
  {
    /* Handle Isochronous channel */
    if ((ch_reg & USB_CH_UTYPE) == USB_EP_ISOCHRONOUS)
    {
      /* correct transaction */
      if ((hhcd->Instance->ISTR & USB_ISTR_ERR) == 0U)
      {
        /* Double buffer isochronous out*/
        if ((ch_reg & USB_CH_KIND) == 0U)
        {
          /* Odd Transaction */
          if ((ch_reg & USB_CH_DTOG_TX) != 0U)
          {
            hhcd->hc[chnum & 0xFU].pmabuff0_state = USB_PMABUF_EMPTY;
          }
          /* Even Transaction */
          else
          {
            hhcd->hc[chnum & 0xFU].pmabuff1_state = USB_PMABUF_EMPTY;
          }
        }
        else /* single buffer isochronous out */
        {
          HCD_SET_CH_TX_CNT(hhcd->Instance, phy_chnum, (uint16_t)0U);
        }

        /* Transfer complete state */
        hhcd->hc[chnum & 0xFU].state = HC_XFRC;
        hhcd->hc[chnum & 0xFU].urb_state = URB_DONE;
      }

      /*Clear Correct Transfer */
      HCD_CLEAR_TX_CH_CTR(hhcd->Instance, phy_chnum);
    }
    else /* Manage all Non Isochronous Transaction */
    {
      /* Check ACK response */
      if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_ACK_SBUF)
      {
        data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + phy_chnum)->TXBD & 0x03FF0000U) >> 16U);

        if (hhcd->hc[chnum & 0xFU].xfer_len >= data_xfr)
        {
          hhcd->hc[chnum & 0xFU].xfer_len -= data_xfr;
        }
        else
        {
          hhcd->hc[chnum & 0xFU].xfer_len = 0U;
        }

        /* Transfer no yet finished only one packet of mps is transferred and ACKed from device */
        if (hhcd->hc[chnum & 0xFU].xfer_len != 0U)
        {
          /* manage multiple Xfer */
          hhcd->hc[chnum & 0xFU].xfer_buff += data_xfr;
          hhcd->hc[chnum & 0xFU].xfer_count  += data_xfr;

          /* start a new transfer */
          (void) USB_HC_StartXfer(hhcd->Instance, &hhcd->hc[chnum & 0xFU]);
        }
        else
        {
          /* Transfer complete */
          hhcd->hc[chnum & 0xFU].xfer_count += data_xfr;
          hhcd->hc[chnum & 0xFU].state = HC_XFRC;
          hhcd->hc[chnum & 0xFU].urb_state = URB_DONE;
          if ((hhcd->hc[chnum & 0xFU].ep_type == EP_TYPE_BULK) ||
              (hhcd->hc[chnum & 0xFU].ep_type == EP_TYPE_INTR))
          {
            hhcd->hc[chnum & 0xFU].toggle_out ^= 1U;
          }
        }
      }

      /* Check NACK Response */
      else if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_NAK)
      {
        hhcd->hc[chnum & 0xFU].urb_state = URB_NOTREADY;
        hhcd->hc[chnum & 0xFU].ErrCnt = 0U;
        hhcd->hc[chnum & 0xFU].state = HC_NAK;
      }

      /*Check STALL Response*/
      else if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_STALL)
      {
        (void) HAL_HCD_HC_Halt(hhcd, (uint8_t)chnum);
        hhcd->hc[chnum & 0xFU].state = HC_STALL;
        hhcd->hc[chnum & 0xFU].urb_state = URB_STALL;
      }

      /*Check double buffer ACK in case of bulk transaction */
      else if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_ACK_DBUF)
      {
        /*Double buffer management Bulk Out*/
        (void) HCD_HC_OUT_BulkDb(hhcd, chnum, (uint8_t)phy_chnum, ch_reg);
      }
      else
      {
        /*...*/
      }

      HAL_HCD_HC_NotifyURBChange_Callback(hhcd, (uint8_t)chnum,
                                          hhcd->hc[chnum & 0xFU].urb_state);
      HCD_CLEAR_TX_CH_CTR(hhcd->Instance, phy_chnum);
    }  /* end no isochronous */
  }

  /*------ Manage Transaction Error------*/
  else
  {
    hhcd->hc[chnum & 0xFU].ErrCnt++;
    if (hhcd->hc[chnum & 0xFU].ErrCnt > 3U)
    {
      HCD_SET_CH_TX_STATUS(hhcd->Instance, phy_chnum, USB_CH_TX_DIS);
      hhcd->hc[chnum & 0xFU].urb_state = URB_ERROR;
    }
    else
    {
      hhcd->hc[chnum & 0xFU].urb_state = URB_NOTREADY;
    }

    hhcd->hc[chnum & 0xFU].state = HC_XACTERR;

    /*Clear ERR_TX*/
    HCD_CLEAR_TX_CH_ERR(hhcd->Instance, phy_chnum);
    HAL_HCD_HC_NotifyURBChange_Callback(hhcd, (uint8_t)chnum,
                                        hhcd->hc[chnum & 0xFU].urb_state);
  }
}


/**
  * @brief  Handle Host Port interrupt requests.
  * @param  hhcd  HCD handle
  * @retval None
  */
static void HCD_Port_IRQHandler(HCD_HandleTypeDef *hhcd)
{
  /* J-state detected & LastState=Disconnected   */
  if (((hhcd->Instance->FNR & USB_FNR_RXDP) != 0U) &&
      ((hhcd->HostState == HCD_HCD_STATE_DISCONNECTED) != 0U))
  {
    HAL_HCD_Connect_Callback(hhcd);
    hhcd->HostState = HCD_HCD_STATE_CONNECTED;
  }
  /* K-state detected & LastState=Disconnected  */
  else  if (((hhcd->Instance->ISTR & USB_ISTR_LS_DCONN) != 0U)
            && ((hhcd->HostState == HCD_HCD_STATE_DISCONNECTED) != 0U))
  {
    HAL_HCD_Connect_Callback(hhcd);
    hhcd->HostState = HCD_HCD_STATE_CONNECTED;
  }
  /* SE0 detected USB Disconnected state */
  else if ((hhcd->Instance->FNR & (USB_FNR_RXDP | USB_FNR_RXDM)) == 0U)
  {
    /*Host Port State*/
    hhcd->HostState = HCD_HCD_STATE_DISCONNECTED;
    /*Disconnection Callback */
    HAL_HCD_Disconnect_Callback(hhcd);
  }
  /* J-state detected & lastState=Connected: a Missing disconnection is detected */
  else if (((hhcd->Instance->FNR & USB_FNR_RXDP) != 0U) &&
           ((hhcd->HostState == HCD_HCD_STATE_CONNECTED) != 0U))
  {
    /*Disconnection Callback */
    HAL_HCD_Disconnect_Callback(hhcd);
    /*Host Port State*/
    hhcd->HostState = HCD_HCD_STATE_DISCONNECTED;
  }
  /* K-state detected & LastState=Disconnected: a Missing disconnection is detected */
  else if (((hhcd->Instance->ISTR & USB_ISTR_LS_DCONN) != 0U)
           && ((hhcd->HostState == HCD_HCD_STATE_CONNECTED) != 0U))
  {
    /*Disconnection Callback */
    HAL_HCD_Disconnect_Callback(hhcd);
    /*Host Port State*/
    hhcd->HostState = HCD_HCD_STATE_DISCONNECTED;
  }
  else
  {
    /* should not be here */
  }
}

/**
  * @brief  Check if the ch_num are already reserved to a physical channel
  * @param  hhcd  HCD handle
  * @param  ch_num  Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
static uint8_t HAL_HCD_Check_usedChannel(HCD_HandleTypeDef *hhcd, uint8_t ch_num)
{
  uint8_t idx;

  /* Check if the logical channel are already opened  */
  for (idx = 0U; idx < hhcd->Init.Host_channels; idx++)
  {
    if ((((hhcd->phy_chin_state[idx] & 0x00F0U) >> 4U) == ((uint16_t)ch_num + 1U)) && (hhcd->phy_chin_state[idx] != 0U))
    {
      return (1U | (idx << 4U));
    }
    if ((((hhcd->phy_chout_state[idx] & 0x00F0U) >> 4U) == ((uint16_t)ch_num + 1U)) && (hhcd->phy_chout_state[idx] != 0U))
    {
      return (1U | (idx << 4U));
    }
  }

  return 0U;
}

/**
  * @brief  Get a Logical Channel number from  physical Channel
  * @param  hhcd  HCD handle
  * @param  phy_chnum
  *         This parameter can be a value from 1 to 15
  * @param  dir  Channel direction
  *         -0 OUT_Channel
  *         -1 IN_Channel
  * @retval HAL status
  */
static uint8_t HAL_HCD_GetLogical_Channel(HCD_HandleTypeDef *hhcd,
                                          uint8_t phy_chnum, uint8_t dir)
{
  /* Out Channel Direction */
  if (dir == 0U)
  {
    if (((hhcd->phy_chout_state[phy_chnum & 0x7U] & 0x00F0U) >> 4U) != 0U)
    {
      return ((uint8_t)((hhcd->phy_chout_state[phy_chnum & 0x7U] & 0x00F0U) >> 4U) - 1U);
    }
    else
    {
      /*Channel not registered Error*/
      return HCD_LOGICAL_CH_NOT_OPENED;
    }
  }
  /* IN Channel Direction */
  else
  {
    if (((hhcd->phy_chin_state[phy_chnum & 0x7U] & 0x00F0U) >> 4U) != 0U)
    {
      return ((uint8_t)((hhcd->phy_chin_state[phy_chnum & 0x7U] & 0x00F0U) >> 4U) - 1U);
    }
    else
    {
      /*Channel not registered Error*/
      return HCD_LOGICAL_CH_NOT_OPENED;
    }
  }
}
/**
  * @brief  Get a free physical Channel number according to the direction
  * @param  hhcd HCD handle
  * @param  ch_num Channel number
  *         This parameter can be a value from 1 to 15
  * @param  epnum Endpoint number
  *          This parameter can be a value from 1 to 15
  * @param  ep_type Endpoint Type
  *          This parameter can be one of these values:
  *            EP_TYPE_CTRL Control type,
  *            EP_TYPE_ISOC Isochronous type,
  *            EP_TYPE_BULK Bulk type,
  *            EP_TYPE_INTR Interrupt type
  * @retval if physical channel is available return Phy_channel number
         else return HCD_FREE_CH_NOT_FOUND
  */
static uint8_t HAL_HCD_Get_FreePhyChannel(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                          uint8_t epnum, uint8_t ep_type)
{
  uint8_t idx;

  if ((epnum & 0x80U) != 0U)
  {
    /* Find a new available physical in channel */
    for (idx = 0U; idx < hhcd->Init.Host_channels; idx++)
    {
      if ((hhcd->phy_chin_state[idx] == 0U) &&   /* if PhysicalChannelx(EPCHidx) IN is Free */
          ((((hhcd->phy_chout_state[idx] & 0x000FU) == ((uint16_t)ep_type + 1U)) && /* if  the same (EPCHidx) Channelx OUT is already opened check if the same type is allocated */
            (((hhcd->phy_chout_state[idx] & 0x0F00U) == ((uint16_t)epnum & 0x0FU)))) || /* Check if the same Epnum is allocated then allocate the same physical channelOUT for IN Logical Channel */
           (hhcd->phy_chout_state[idx] == 0U))) /* OR if  physical Channel OUT (EPCHidx)is free */
      {
        /* chin_state will store the ep_type to be used for the same channel in out direction */
        hhcd->phy_chin_state[idx] = (((uint16_t)ch_num + 1U) << 4U) |
                                    ((uint16_t)ep_type + 1U) | /* ep_type(0/1/2/3) so adding + 1 to avoid having a 0 value */
                                    (((uint16_t)epnum & 0x0FU) << 8U);

        return idx;
      }
    }
  }
  else
  {
    /* Find a new available physical out channel */
    for (idx = 0U; idx < hhcd->Init.Host_channels; idx++)
    {
      /* if there is a free out channel and the same channel is used for the in direction then check if same ep_type used */
      if ((hhcd->phy_chout_state[idx] == 0U) &&
          ((((hhcd->phy_chin_state[idx] & 0x0FU) == ((uint16_t)ep_type + 1U)) &&
            ((hhcd->phy_chin_state[idx] & 0x0F00U) == ((uint16_t)epnum & 0x0FU))) ||
           (hhcd->phy_chin_state[idx] == 0U)))
      {
        /* chin_state will store the ep_type to be used for the same channel in out direction */
        hhcd->phy_chout_state[idx] = (((uint16_t)ch_num + 1U) << 4U) |
                                     ((uint16_t)ep_type + 1U) |  /* ep_type(0/1/2/3) so adding +1 to avoid having a 0 value */
                                     (((uint16_t)epnum & 0x0FU) << 8U);

        return idx;
      }
    }
  }

  /*in case of Error */
  return HCD_FREE_CH_NOT_FOUND;
}

/**
  * @brief  Free All Channel allocation
  * @param  hhcd HCD handle
  * @retval HAL status
  */
static void  HAL_HCD_ClearPhyChannel(HCD_HandleTypeDef *hhcd)
{
  uint8_t idx;

  for (idx = 0U; idx < hhcd->Init.Host_channels; idx++)
  {
    /*Reset channel allocation value */
    hhcd->phy_chout_state[idx] = 0U;
    hhcd->phy_chin_state[idx] = 0U;
  }
}

/*----------------------  PMA Allocation Section --------------------- */
/*
                __col31________________col0__   Column-- >
          lin0 | entry31.|.......  | entry0 |   Line
               |---------|---------|--------|    |
          line1| entry63.|.......  | entry32|    |
               |---------|---------|--------|   \|/
               | entry127|.......  | entry64|
               |---------|---------|--------|
               | entry256|......   |entry128|
                ----------------------------
           an allocation space of 64byte need 8 Free contiguous Entry in the Matrix
           - a Free Entry is a bit with 0 Value/  a busy entry is a bit with 1 value. */

/**
  * @brief  Fetch in the PMA_LockupTable free space of number of mps byte
  * @param  hhcd  Host instance
  * @param  mps  Channel Max Packet Size
  * @retval PMA_Address of the first free block containing mps byte
            0xFFFF in case of no space available
  */
static uint16_t HAL_HCD_GetFreePMA(HCD_HandleTypeDef *hhcd, uint16_t mps)
{
  uint32_t Entry, FreeBlocks = 0U;
  uint8_t FirstFreeBlock_col = 0U, FirstFreeBlock_line = 0U;
  uint8_t ColIndex;
  uint16_t NbrReqBlocks;
  uint16_t mps_t = mps;

  /* since PMA buffer descriptor RXBD allocate address according to BLSIZE, BLSIZE=1==> mps>64
    allocation in PMA is done in 32Bytes each entry */
  if ((mps_t > 64U) && ((mps_t % 32U) != 0U))
  {
    /* Align the mps to 32byte block to match the allocation in PMA,
      check Definition of allocation buffer memory in usb user spec */
    mps_t = (uint16_t)(((mps_t / 32U) + 1U) * 32U);
  }

  /* calculate the number of block(8byte) to allocate */
  NbrReqBlocks = mps_t / 8U;

  /* check if we need remaining Block */
  if ((mps_t % 8U) != 0U)
  {
    NbrReqBlocks++;
  }

  /* Look For NbrReqBlocks * Empty Block */
  for (uint8_t i = 0U; ((i < PMA_BLOCKS) && (FreeBlocks != NbrReqBlocks)); i++)
  {
    Entry = hhcd->PMALookupTable[i];

    /* when parse is in progress, check the first col to look for a contiguous block */
    if ((FreeBlocks != 0U) && ((Entry & (uint32_t)1U) != 0U))
    {
      FreeBlocks = 0U;
    }
    uint8_t j = 0U;
    while ((j <= 31U) && (FreeBlocks != NbrReqBlocks))
    {
      /* check if block j is free */
      if ((Entry & ((uint32_t)1U << j)) == 0U)
      {
        if (FreeBlocks == 0U)
        {
          FirstFreeBlock_col = j;
          FirstFreeBlock_line = i;
          FreeBlocks++;
        }
        j++;

        /* Parse Column PMALockTable */
        while ((j <= 31U) && ((Entry & ((uint32_t)1U << j)) == 0U) && (FreeBlocks < NbrReqBlocks))
        {
          FreeBlocks++;
          j++;
        }

        /* Free contiguous Blocks not found */
        if (((FreeBlocks < NbrReqBlocks) && (j < 31U)) ||
            ((j == 31U) && ((Entry & ((uint32_t)1U << j)) != 0U)))
        {
          FreeBlocks = 0U;
        }
      }
      j++;
    } /* end for j */
  } /* end for i */

  /* Free block found */
  if (FreeBlocks >= NbrReqBlocks)
  {
    ColIndex = FirstFreeBlock_col;

    for (uint8_t i = FirstFreeBlock_line; ((i < PMA_BLOCKS) && (FreeBlocks > 0U)); i++)
    {
      for (uint8_t j = ColIndex; j <= 31U; j++)
      {
        hhcd->PMALookupTable[i] |= ((uint32_t)1U << j);
        if (--FreeBlocks == 0U)
        {
          break;
        }
      }
      ColIndex = 0U;
    }

    return (uint16_t)((FirstFreeBlock_line * (uint16_t)256U) + (FirstFreeBlock_col * (uint16_t)8U));
  }
  else
  {
    return 0xFFFFU;
  }
}

/**
  * @brief  Allocate PMA buffer for Channel
  *         This API will fetch a free space
  * @param  hhcd    Host instance
  * @param  ch_num  Channel number
  * @param  ch_kind endpoint Kind
  *                  USB_SNG_BUF Single Buffer used
  *                  USB_DBL_BUF Double Buffer used
  * @param  mps Channel Max Packet Size
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_HCD_PMAlloc(HCD_HandleTypeDef *hhcd, uint8_t  ch_num,
                                   uint16_t ch_kind, uint16_t mps)
{
  uint16_t pma_addr0;
  uint16_t pma_addr1; /* used for double buffer mode if enabled */

  /* Host Channel */
  HCD_HCTypeDef *hc = &(hhcd->hc[ch_num]);

  /* Get a FreePMA Address */
  pma_addr0 = HAL_HCD_GetFreePMA(hhcd, mps);

  /* if there is no free space to allocate */
  if (pma_addr0 == 0xFFFFU)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Here we check if the endpoint is single or double Buffer */
    if (ch_kind == HCD_SNG_BUF)
    {
      /* Single Buffer */
      hc->doublebuffer = 0U;

      /* Configure the PMA */
      if (hc->ch_dir == CH_IN_DIR)
      {
        (USB_DRD_PMA_BUFF + hc->phy_ch_num)->RXBD = pma_addr0;
      }
      else
      {
        (USB_DRD_PMA_BUFF + hc->phy_ch_num)->TXBD = pma_addr0;
      }

      /* Set the Pmaaddress */
      hc->pmaadress = pma_addr0;
    }
    else /* USB_DBL_BUF */
    {
      /* Double Buffer Endpoint */
      hc->doublebuffer = 1U;

      /* Get a FreePMA Address for buffer 2 */
      pma_addr1 = HAL_HCD_GetFreePMA(hhcd, mps);

      if (pma_addr1 == 0xFFFFU)
      {
        /* Free the first buffer */
        (void)HAL_HCD_PMAFree(hhcd, pma_addr0, mps);
        return HAL_ERROR;
      }
      else
      {
        /* Configure the PMA */
        hc->pmaaddr0 = (uint16_t)(pma_addr0);
        hc->pmaaddr1 = (uint16_t)(pma_addr1);

        /* Set Buffer0 pma address */
        (USB_DRD_PMA_BUFF + hc->phy_ch_num)->TXBD = pma_addr0;

        /* Set Buffer1 pma address */
        (USB_DRD_PMA_BUFF + hc->phy_ch_num)->RXBD = pma_addr1;

        /* Used for Bulk DB MPS < 64bytes */
        if (hc->ch_dir == CH_IN_DIR)
        {
          hc->pmaadress = hc->pmaaddr1;
        }
        else
        {
          hc->pmaadress = hc->pmaaddr0;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  PMA De-Allocation for Channel Free the reserved block in the PMA-LookupTable
  * @param  hhcd  Host instance
  * @param  ch_num Channel number
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_HCD_PMADeAlloc(HCD_HandleTypeDef *hhcd, uint8_t  ch_num)
{
  HAL_StatusTypeDef status;
  uint8_t Err = 0U;

  /* Host Channel */
  HCD_HCTypeDef *hc = &(hhcd->hc[ch_num]);

  /* Single Buffer */
  if (hc->doublebuffer == 0U)
  {
    status = HAL_HCD_PMAFree(hhcd, hc->pmaadress, hc->max_packet);
  }
  else   /* Double buffer */
  {
    status = HAL_HCD_PMAFree(hhcd, hc->pmaaddr0, hc->max_packet);
    if (status != HAL_OK)
    {
      Err++;
    }

    status = HAL_HCD_PMAFree(hhcd, hc->pmaaddr1, hc->max_packet);
    if (status != HAL_OK)
    {
      Err++;
    }

    if (Err != 0U)
    {
      return HAL_ERROR;
    }
  }

  return status;
}


/**
  * @brief  PMA Reset
  * @param  hhcd  Host instance
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_HCD_PMAReset(HCD_HandleTypeDef *hhcd)
{
  /* Reset All PMA Entry */
  for (uint8_t i = 0U; i < PMA_BLOCKS; i++)
  {
    hhcd->PMALookupTable[i] = 0U;
  }

  /* Allocate a Space for buffer descriptor table depending on the Host channel number */
  for (uint8_t i = 0U; i < hhcd->Init.Host_channels; i++)
  {
    hhcd->PMALookupTable[0] |= ((uint32_t)1U << i);
  }

  return HAL_OK;
}

/**
  * @brief  PMA FRee
  * @param  hhcd   Host instance
  * @param  pma_base PMA base offset stored in hhcd->hc.pmaaddr
  * @param  mps  Max Packet Size
  * @retval HAL status
  */
static HAL_StatusTypeDef  HAL_HCD_PMAFree(HCD_HandleTypeDef *hhcd, uint32_t pma_base, uint16_t mps)
{
  uint32_t block_nbr;
  uint8_t ColIndex;
  uint8_t LineIndex;
  uint16_t mps_t = mps;

  /* since PMA buffer descriptor RXBD allocate address according to BLSIZE, BLSIZE=1==> mps>64
    allocation in PMA is done in 32Bytes each entry */
  if ((mps_t > 64U) && ((mps_t % 32U) != 0U))
  {
    /* Align the mps to 32byte block to match the allocation in PMA,
      check Definition of allocation buffer memory in usb user spec */
    mps_t = (uint16_t)(((mps_t / 32U) + 1U) * 32U);
  }

  /* Calculate the number of needed block to Free */
  if ((mps_t / 8U) != 0U)
  {
    block_nbr = ((uint32_t)mps_t / 8U);

    if ((mps_t % 8U) != 0U)
    {
      block_nbr++;
    }
  }
  else
  {
    block_nbr = 1U;
  }

  /* Decode Col/Line of PMA_Base position in the PMA_LookupTable */
  if (pma_base > 256U)
  {
    LineIndex = (uint8_t)(pma_base / 256U);
    ColIndex = (uint8_t)((pma_base - ((uint32_t)LineIndex * 256U)) / 8U);
  }
  else
  {
    LineIndex = 0U;
    ColIndex = (uint8_t)(pma_base / 8U);
  }

  /* Reset the corresponding bit in the lookupTable */
  for (uint8_t i = LineIndex; ((i < PMA_BLOCKS) && (block_nbr > 0U)); i++)
  {
    for (uint8_t j = ColIndex; j <= 31U; j++)
    {
      /* Check if the block is not already reserved or it was already closed */
      if ((hhcd->PMALookupTable[i] & ((uint32_t)1U << j)) == 0U)
      {
        return HAL_ERROR;
      }
      /* Free the reserved block by resetting the corresponding bit */
      hhcd->PMALookupTable[i] &= ~(1U << j);

      if (--block_nbr == 0U)
      {
        break;
      }
    }
    ColIndex = 0U;
  }

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_HCD_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
