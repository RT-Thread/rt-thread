/**
  ******************************************************************************
  * @file    stm32g0xx_ll_usb.c
  * @author  MCD Application Team
  * @brief   USB Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Fill parameters of Init structure in USB_OTG_CfgTypeDef structure.

      (#) Call USB_CoreInit() API to initialize the USB Core peripheral.

      (#) The upper HAL HCD/PCD driver will call the right routines for its internal processes.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
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

/** @addtogroup STM32G0xx_LL_USB_DRIVER
  * @{
  */

#if defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED)
#if defined (USB_DRD_FS)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


static HAL_StatusTypeDef USB_CoreReset(USB_DRD_TypeDef *USBx);
static HAL_StatusTypeDef USB_HC_BULK_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                  USB_DRD_HCTypeDef *hc,
                                                  uint32_t ch_reg,
                                                  uint32_t *len);

static HAL_StatusTypeDef USB_HC_ISO_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                 USB_DRD_HCTypeDef *hc,
                                                 uint32_t len);

/**
  * @brief  Reset the USB Core (needed after USB clock settings change)
  * @param  USBx Selected device
  * @retval HAL status
  */
static HAL_StatusTypeDef USB_CoreReset(USB_DRD_TypeDef *USBx)
{
  /* Disable Host Mode */
  USBx->CNTR &= ~USB_CNTR_HOST;

  /* Force Reset IP */
  USBx->CNTR |= USB_CNTR_USBRST;

  return HAL_OK;
}

/**
  * @brief  Initializes the USB Core
  * @param  USBx USB Instance
  * @param  cfg pointer to a USB_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_CoreInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg)
{
  UNUSED(cfg);
  HAL_StatusTypeDef state;

  /* Reset after a PHY select */
  state = USB_CoreReset(USBx);

  /* Clear pending interrupts */
  USBx->ISTR = 0U;

  return state;
}

/**
  * @brief  USB_EnableGlobalInt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EnableGlobalInt(USB_DRD_TypeDef *USBx)
{
  uint32_t winterruptmask;

  /* Clear pending interrupts */
  USBx->ISTR = 0U;

  /* Set winterruptmask variable */
  winterruptmask = USB_CNTR_CTRM  | USB_CNTR_WKUPM |
                   USB_CNTR_SUSPM | USB_CNTR_ERRM |
                   USB_CNTR_SOFM | USB_CNTR_ESOFM |
                   USB_CNTR_RESETM | USB_CNTR_L1REQM;

  /* Set interrupt mask */
  USBx->CNTR = winterruptmask;

  return HAL_OK;
}

/**
  * @brief  USB_DisableGlobalInt
  *         Disable the controller's Global Int in the AHB Config reg
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DisableGlobalInt(USB_DRD_TypeDef *USBx)
{
  uint32_t winterruptmask;

  /* Set winterruptmask variable */
  winterruptmask = USB_CNTR_CTRM  | USB_CNTR_WKUPM |
                   USB_CNTR_SUSPM | USB_CNTR_ERRM |
                   USB_CNTR_SOFM | USB_CNTR_ESOFM |
                   USB_CNTR_RESETM | USB_CNTR_L1REQM;

  /* Clear interrupt mask */
  USBx->CNTR &= ~winterruptmask;

  return HAL_OK;
}

/**
  * @brief  USB_SetCurrentMode Set functional mode
  * @param  USBx Selected device
  * @param  mode current core mode
  *          This parameter can be one of the these values:
  *            @arg USB_DEVICE_MODE Peripheral mode
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetCurrentMode(USB_DRD_TypeDef *USBx, USB_DRD_ModeTypeDef mode)
{
  if (mode == USB_DEVICE_MODE)
  {
    USBx->CNTR &= ~USB_CNTR_HOST;
  }
  else
  {
    USBx->CNTR |= USB_CNTR_HOST;
  }

  return HAL_OK;
}

/**
  * @brief  USB_DevInit Initializes the USB controller registers
  *         for device mode
  * @param  USBx Selected device
  * @param  cfg  pointer to a USB_DRD_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(cfg);
  /* Force Reset */
  USBx->CNTR = USB_CNTR_USBRST;

  /* Release Reset */
  USBx->CNTR &= ~USB_CNTR_USBRST;

  /* Set the Device Mode */
  (void)USB_SetCurrentMode(USBx, USB_DEVICE_MODE);

  /* Clear pending interrupts */
  USBx->ISTR = 0U;

  return HAL_OK;
}

#if defined (HAL_PCD_MODULE_ENABLED)
/**
  * @brief  Activate and configure an endpoint
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateEndpoint(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t wEpRegVal;

  wEpRegVal = PCD_GET_ENDPOINT(USBx, ep->num) & USB_EP_T_MASK;

  /* initialize Endpoint */
  switch (ep->type)
  {
    case EP_TYPE_CTRL:
      wEpRegVal |= USB_EP_CONTROL;
      break;

    case EP_TYPE_BULK:
      wEpRegVal |= USB_EP_BULK;
      break;

    case EP_TYPE_INTR:
      wEpRegVal |= USB_EP_INTERRUPT;
      break;

    case EP_TYPE_ISOC:
      wEpRegVal |= USB_EP_ISOCHRONOUS;
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  PCD_SET_ENDPOINT(USBx, ep->num, (wEpRegVal | USB_EP_VTRX | USB_EP_VTTX));

  PCD_SET_EP_ADDRESS(USBx, ep->num, ep->num);

  if (ep->doublebuffer == 0U)
  {
    if (ep->is_in != 0U)
    {
      /*Set the endpoint Transmit buffer address */
      PCD_SET_EP_TX_ADDRESS(USBx, ep->num, ep->pmaadress);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      if (ep->type != EP_TYPE_ISOC)
      {
        /* Configure NAK status for the Endpoint */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
      }
    }
    else
    {
      /*Set the endpoint Receive buffer address */
      PCD_SET_EP_RX_ADDRESS(USBx, ep->num, ep->pmaadress);

      /*Set the endpoint Receive buffer counter*/
      PCD_SET_EP_RX_CNT(USBx, ep->num, ep->maxpacket);
      PCD_CLEAR_RX_DTOG(USBx, ep->num);

      /* Configure VALID status for the Endpoint*/
      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
    }
  }
  /*Double Buffer*/
  else
  {
    /* Set the endpoint as double buffered */
    PCD_SET_EP_DBUF(USBx, ep->num);

    /* Set buffer address for double buffered mode */
    PCD_SET_EP_DBUF_ADDR(USBx, ep->num, ep->pmaaddr0, ep->pmaaddr1);

    if (ep->is_in == 0U)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      if (ep->type != EP_TYPE_ISOC)
      {
        /* Configure NAK status for the Endpoint */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
      }

      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
    }
  }

  return ret;
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeactivateEndpoint(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  if (ep->doublebuffer == 0U)
  {
    if (ep->is_in != 0U)
    {
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
    }
    else
    {
      PCD_CLEAR_RX_DTOG(USBx, ep->num);

      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
    }
  }
  /*Double Buffer*/
  else
  {
    if (ep->is_in == 0U)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      /* Reset value of the data toggle bits for the endpoint out*/
      PCD_TX_DTOG(USBx, ep->num);

      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);
      PCD_RX_DTOG(USBx, ep->num);

      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
    }
  }

  return HAL_OK;
}

/**
  * @brief  USB_EPStartXfer setup and starts a transfer over an EP
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPStartXfer(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  uint32_t len;
  uint16_t pmabuffer;
  uint16_t wEPVal;

  /* IN endpoint */
  if (ep->is_in == 1U)
  {
    /*Multi packet transfer*/
    if (ep->xfer_len > ep->maxpacket)
    {
      len = ep->maxpacket;
    }
    else
    {
      len = ep->xfer_len;
    }

    /* configure and validate Tx endpoint */
    if (ep->doublebuffer == 0U)
    {
      USB_WritePMA(USBx, ep->xfer_buff, ep->pmaadress, (uint16_t)len);
      PCD_SET_EP_TX_CNT(USBx, ep->num, len);
    }
    else
    {
      /* double buffer bulk management */
      if (ep->type == EP_TYPE_BULK)
      {
        if (ep->xfer_len_db > ep->maxpacket)
        {
          /* enable double buffer */
          PCD_SET_EP_DBUF(USBx, ep->num);

          /* each Time to write in PMA xfer_len_db will */
          ep->xfer_len_db -= len;

          /* Fill the two first buffer in the Buffer0 & Buffer1 */
          if ((PCD_GET_ENDPOINT(USBx, ep->num) & USB_EP_DTOG_TX) != 0U)
          {
            /* Set the Double buffer counter for pmabuffer1 */
            PCD_SET_EP_DBUF1_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr1;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
            ep->xfer_buff += len;

            if (ep->xfer_len_db > ep->maxpacket)
            {
              ep->xfer_len_db -= len;
            }
            else
            {
              len = ep->xfer_len_db;
              ep->xfer_len_db = 0U;
            }

            /* Set the Double buffer counter for pmabuffer0 */
            PCD_SET_EP_DBUF0_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr0;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          }
          else
          {
            /* Set the Double buffer counter for pmabuffer0 */
            PCD_SET_EP_DBUF0_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr0;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
            ep->xfer_buff += len;

            if (ep->xfer_len_db > ep->maxpacket)
            {
              ep->xfer_len_db -= len;
            }
            else
            {
              len = ep->xfer_len_db;
              ep->xfer_len_db = 0U;
            }

            /* Set the Double buffer counter for pmabuffer1 */
            PCD_SET_EP_DBUF1_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr1;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          }
        }
        /* auto Switch to single buffer mode when transfer <Mps no need to manage in double buffer */
        else
        {
          len = ep->xfer_len_db;

          /* disable double buffer mode */
          PCD_CLEAR_EP_DBUF(USBx, ep->num);

          /* Set Tx count with nbre of byte to be transmitted */
          PCD_SET_EP_TX_CNT(USBx, ep->num, len);
          pmabuffer = ep->pmaaddr0;

          /* Write the user buffer to USB PMA */
          USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
        }
      }/* end if bulk double buffer */

      /* manage isochronous double buffer IN mode */
      else
      {
        /* enable double buffer */
        PCD_SET_EP_DBUF(USBx, ep->num);

        /* each Time to write in PMA xfer_len_db will */
        ep->xfer_len_db -= len;

        /* Fill the data buffer */
        if ((PCD_GET_ENDPOINT(USBx, ep->num) & USB_EP_DTOG_TX) != 0U)
        {
          /* Set the Double buffer counter for pmabuffer1 */
          PCD_SET_EP_DBUF1_CNT(USBx, ep->num, ep->is_in, len);
          pmabuffer = ep->pmaaddr1;

          /* Write the user buffer to USB PMA */
          USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          ep->xfer_buff += len;

          if (ep->xfer_len_db > ep->maxpacket)
          {
            ep->xfer_len_db -= len;
          }
          else
          {
            len = ep->xfer_len_db;
            ep->xfer_len_db = 0U;
          }

          if (len > 0U)
          {
            /* Set the Double buffer counter for pmabuffer0 */
            PCD_SET_EP_DBUF0_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr0;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          }
        }
        else
        {
          /* Set the Double buffer counter for pmabuffer0 */
          PCD_SET_EP_DBUF0_CNT(USBx, ep->num, ep->is_in, len);
          pmabuffer = ep->pmaaddr0;

          /* Write the user buffer to USB PMA */
          USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          ep->xfer_buff += len;

          if (ep->xfer_len_db > ep->maxpacket)
          {
            ep->xfer_len_db -= len;
          }
          else
          {
            len = ep->xfer_len_db;
            ep->xfer_len_db = 0U;
          }

          if (len > 0U)
          {
            /* Set the Double buffer counter for pmabuffer1 */
            PCD_SET_EP_DBUF1_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr1;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          }
        }
      }
    }

    PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_VALID);
  }
  else /* OUT endpoint */
  {
    if (ep->doublebuffer == 0U)
    {
      /* Multi packet transfer */
      if (ep->xfer_len > ep->maxpacket)
      {
        len = ep->maxpacket;
        ep->xfer_len -= len;
      }
      else
      {
        len = ep->xfer_len;
        ep->xfer_len = 0U;
      }
      /* configure and validate Rx endpoint */
      PCD_SET_EP_RX_CNT(USBx, ep->num, len);
    }
    else
    {
      /* First Transfer Coming From HAL_PCD_EP_Receive & From ISR */
      /* Set the Double buffer counter */
      if (ep->type == EP_TYPE_BULK)
      {
        PCD_SET_EP_DBUF_CNT(USBx, ep->num, ep->is_in, ep->maxpacket);

        /* Coming from ISR */
        if (ep->xfer_count != 0U)
        {
          /* update last value to check if there is blocking state */
          wEPVal = (uint16_t)PCD_GET_ENDPOINT(USBx, ep->num);

          /*Blocking State */
          if ((((wEPVal & USB_EP_DTOG_RX) != 0U) && ((wEPVal & USB_EP_DTOG_TX) != 0U)) ||
              (((wEPVal & USB_EP_DTOG_RX) == 0U) && ((wEPVal & USB_EP_DTOG_TX) == 0U)))
          {
            PCD_FreeUserBuffer(USBx, ep->num, 0U);
          }
        }
      }
      /* iso out double */
      else if (ep->type == EP_TYPE_ISOC)
      {
        /* Multi packet transfer */
        if (ep->xfer_len > ep->maxpacket)
        {
          len = ep->maxpacket;
          ep->xfer_len -= len;
        }
        else
        {
          len = ep->xfer_len;
          ep->xfer_len = 0U;
        }
        PCD_SET_EP_DBUF_CNT(USBx, ep->num, ep->is_in, len);
      }
      else
      {
        return HAL_ERROR;
      }
    }

    PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
  }

  return HAL_OK;
}


/**
  * @brief  USB_EPSetStall set a stall condition over an EP
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPSetStall(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  if (ep->is_in != 0U)
  {
    PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_STALL);
  }
  else
  {
    PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_STALL);
  }

  return HAL_OK;
}

/**
  * @brief  USB_EPClearStall Clear a stall condition over an EP
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPClearStall(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  if (ep->doublebuffer == 0U)
  {
    if (ep->is_in != 0U)
    {
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      if (ep->type != EP_TYPE_ISOC)
      {
        /* Configure NAK status for the Endpoint */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_NAK);
      }
    }
    else
    {
      PCD_CLEAR_RX_DTOG(USBx, ep->num);

      /* Configure VALID status for the Endpoint */
      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
    }
  }

  return HAL_OK;
}
#endif /* HAL_PCD_MODULE_ENABLED */

/**
  * @brief  USB_StopDevice Stop the usb device mode
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_StopDevice(USB_DRD_TypeDef *USBx)
{
  /* disable all interrupts and force USB reset */
  USBx->CNTR = USB_CNTR_USBRST;

  /* clear interrupt status register */
  USBx->ISTR = 0U;

  /* switch-off device */
  USBx->CNTR = (USB_CNTR_USBRST | USB_CNTR_PDWN);

  return HAL_OK;
}

/**
  * @brief  USB_SetDevAddress Stop the usb device mode
  * @param  USBx Selected device
  * @param  address new device address to be assigned
  *          This parameter can be a value from 0 to 255
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_SetDevAddress(USB_DRD_TypeDef *USBx, uint8_t address)
{
  if (address == 0U)
  {
    /* set device address and enable function */
    USBx->DADDR = USB_DADDR_EF;
  }

  return HAL_OK;
}

/**
  * @brief  USB_DevConnect Connect the USB device by enabling the pull-up/pull-down
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_DevConnect(USB_DRD_TypeDef *USBx)
{
  /* Enabling DP Pull-UP bit to Connect internal PU resistor on USB DP line */
  USBx->BCDR |= USB_BCDR_DPPU;

  return HAL_OK;
}

/**
  * @brief  USB_DevDisconnect Disconnect the USB device by disabling the pull-up/pull-down
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_DevDisconnect(USB_DRD_TypeDef *USBx)
{
  /* Disable DP Pull-Up bit to disconnect the Internal PU resistor on USB DP line */
  USBx->BCDR &= ~(USB_BCDR_DPPU);

  return HAL_OK;
}

/**
  * @brief  USB_ReadInterrupts return the global USB interrupt status
  * @param  USBx Selected device
  * @retval HAL status
  */
uint32_t  USB_ReadInterrupts(USB_DRD_TypeDef *USBx)
{
  uint32_t tmpreg;

  tmpreg = USBx->ISTR;
  return tmpreg;
}

/**
  * @brief  USB_ActivateRemoteWakeup : active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateRemoteWakeup(USB_DRD_TypeDef *USBx)
{
  USBx->CNTR |= USB_CNTR_L2RES;

  return HAL_OK;
}

/**
  * @brief  USB_DeActivateRemoteWakeup de-active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(USB_DRD_TypeDef *USBx)
{
  USBx->CNTR &= ~USB_CNTR_L2RES;

  return HAL_OK;
}

/**
  * @brief Copy a buffer from user memory area to packet memory area (PMA)
  * @param   USBx USB peripheral instance register address.
  * @param   pbUsrBuf pointer to user memory area.
  * @param   wPMABufAddr address into PMA.
  * @param   wNBytes no. of bytes to be copied.
  * @retval None
  */
void USB_WritePMA(USB_DRD_TypeDef *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  UNUSED(USBx);
  uint32_t count, tmp;
  __IO uint32_t *pdwVal;
  uint32_t NbWords = ((uint32_t)wNBytes + 3U) >> 2U;
  /* Due to the PMA access 32bit only so the last non word data should be processed alone */
  uint16_t remaining_bytes = wNBytes % 4U;
  uint8_t *pBuf = pbUsrBuf;

  /* Check if there is a remaining byte */
  if (remaining_bytes != 0U)
  {
    NbWords--;
  }

  /* Get the PMA Buffer pointer */
  pdwVal = (__IO uint32_t *)(USB_DRD_PMAADDR + (uint32_t)wPMABufAddr);

  /* Write the Calculated Word into the PMA related Buffer */
  for (count = NbWords; count != 0U; count--)
  {
    *pdwVal = __UNALIGNED_UINT32_READ(pBuf);
    pdwVal++;
    /* Increment pBuf 4 Time as Word Increment */
    pBuf++;
    pBuf++;
    pBuf++;
    pBuf++;
  }

  /* When Number of data is not word aligned, write the remaining Byte */
  if (remaining_bytes != 0U)
  {
    tmp = 0U;

    do
    {
      tmp = tmp | ((uint32_t)(*(uint8_t *)pBuf) << (8U * count));
      count++;
      pBuf++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);

    *pdwVal = tmp;
  }
}

/**
  * @brief Copy data from packet memory area (PMA) to user memory buffer
  * @param   USBx USB peripheral instance register address.
  * @param   pbUsrBuf pointer to user memory area.
  * @param   wPMABufAddr address into PMA.
  * @param   wNBytes no. of bytes to be copied.
  * @retval None
  */
void USB_ReadPMA(USB_DRD_TypeDef *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  UNUSED(USBx);
  uint32_t count, tmp;
  __IO uint32_t *pdwVal;
  uint32_t NbWords = ((uint32_t)wNBytes + 3U) >> 2U;
  /*Due to the PMA access 32bit only so the last non word data should be processed alone */
  uint16_t remaining_bytes = wNBytes % 4U;
  uint8_t *pBuf = pbUsrBuf;

  /* Get the PMA Buffer pointer */
  pdwVal = (__IO uint32_t *)(USB_DRD_PMAADDR + (uint32_t)wPMABufAddr);

  /* if nbre of byte is not word aligned decrement the nbre of word*/
  if (remaining_bytes != 0U)
  {
    NbWords--;
  }

  /*Read the Calculated Word From the PMA related Buffer*/
  for (count = NbWords; count != 0U; count--)
  {
    __UNALIGNED_UINT32_WRITE(pBuf, *pdwVal);

    pdwVal++;
    pBuf++;
    pBuf++;
    pBuf++;
    pBuf++;
  }

  /*When Number of data is not word aligned, read the remaining byte*/
  if (remaining_bytes != 0U)
  {
    tmp = *(__IO uint32_t *)pdwVal;
    do
    {
      *(uint8_t *)pBuf = (uint8_t)(tmp >> (8U * (uint8_t)(count)));
      count++;
      pBuf++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);
  }
}


/*------------------------------------------------------------------------*/
/*                                HOST API                                */
/*------------------------------------------------------------------------*/

/**
  * @brief  USB_HostInit Initializes the USB DRD controller registers
  *         for Host mode
  * @param  USBx Selected device
  * @param  cfg  pointer to a USB_DRD_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_HostInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg)
{
  UNUSED(cfg);

  /* Clear All Pending Interrupt */
  USBx->ISTR = 0U;

  /* Disable all interrupts */
  USBx->CNTR &= ~(USB_CNTR_CTRM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM |
                  USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_DCON |
                  USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_L1REQM);

  /* Clear All Pending Interrupt */
  USBx->ISTR = 0U;

  /* Enable Global interrupt */
  USBx->CNTR |= (USB_CNTR_CTRM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM |
                 USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_DCON |
                 USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_L1REQM);

  /* Remove Reset */
  USBx->CNTR &= ~USB_CNTR_USBRST;

  return HAL_OK;
}


/**
  * @brief  USB_DRD_ResetPort : Reset Host Port
  * @param  USBx Selected device
  * @retval HAL status
  * @note (1)The application must wait at least 10 ms
  *   before clearing the reset bit.
  */
HAL_StatusTypeDef USB_ResetPort(USB_DRD_TypeDef *USBx)
{
  /* Force USB Reset */
  USBx->CNTR |= USB_CNTR_USBRST;
  HAL_Delay(100);
  /* Release USB Reset */
  USBx->CNTR &= ~USB_CNTR_USBRST;
  HAL_Delay(30);

  return HAL_OK;
}

/**
  * @brief  Return Host Core speed
  * @param  USBx Selected device
  * @retval speed Host speed
  *          This parameter can be one of these values
  *            @arg USB_DRD_SPEED_FS Full speed mode
  *            @arg USB_DRD_SPEED_LS Low speed mode
  */
uint32_t USB_GetHostSpeed(USB_DRD_TypeDef *USBx)
{
  if ((USBx->ISTR & USB_ISTR_LS_DCONN) != 0U)
  {
    return USB_DRD_SPEED_LS;
  }
  else
  {
    return USB_DRD_SPEED_FS;
  }
}

/**
  * @brief  Return Host Current Frame number
  * @param  USBx Selected device
  * @retval current frame number
  */
uint32_t USB_GetCurrentFrame(USB_DRD_TypeDef *USBx)
{
  return USBx->FNR & 0x7FFU;
}

/**
  * @brief  Set the channel Kind (Single/double buffer mode)
  * @param  USBx Selected device
  * @param  phy_ch_num Selected device
  * @param  db_state double state can be USB_DRD_DBUFF_ENBALE/USB_DRD_DBUFF_DISABLE
  * @retval HAL status
  */
HAL_StatusTypeDef USB_HC_DoubleBuffer(USB_DRD_TypeDef *USBx,
                                      uint8_t phy_ch_num, uint8_t db_state)
{
  uint32_t tmp;

  if (db_state == USB_DRD_DBUFF_ENBALE)
  {
    tmp = (USB_DRD_GET_CHEP(USBx, phy_ch_num) | USB_CH_KIND) & USB_CHEP_DB_MSK;
  }
  else
  {
    tmp = USB_DRD_GET_CHEP(USBx, phy_ch_num) & (~USB_CH_KIND) & USB_CHEP_DB_MSK;
  }

  /* Set the device speed in case using HUB FS with device LS */
  USB_DRD_SET_CHEP(USBx, phy_ch_num, tmp);

  return HAL_OK;
}

/**
  * @brief  Initialize a host channel
  * @param  USBx Selected device
  * @param  phy_ch_num Channel number
  *         This parameter can be a value from 1 to 15
  * @param  epnum Endpoint number
  *          This parameter can be a value from 1 to 15
  * @param  dev_address Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed Current device speed
  *          This parameter can be one of these values:
  *          @arg USB_DRD_SPEED_FULL Full speed mode
  *          @arg USB_DRD_SPEED_LOW  Low speed mode
  * @param  ep_type Endpoint Type
  *          This parameter can be one of these values:
  *            @arg EP_TYPE_CTRL Control type
  *            @arg EP_TYPE_ISOC Isochronous type
  *            @arg EP_TYPE_BULK Bulk type
  *            @arg EP_TYPE_INTR Interrupt type
  * @param  mps Max Packet Size
  *          This parameter can be a value from 0 to 32K
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_Init(USB_DRD_TypeDef *USBx, uint8_t phy_ch_num,
                              uint8_t epnum, uint8_t dev_address, uint8_t speed,
                              uint8_t ep_type, uint16_t mps)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t wChRegVal;
  uint32_t HostCoreSpeed;

  wChRegVal = USB_DRD_GET_CHEP(USBx, phy_ch_num) & USB_CH_T_MASK;

  /* initialize host Channel */
  switch (ep_type)
  {
    case EP_TYPE_CTRL:
      wChRegVal |= USB_EP_CONTROL;
      break;

    case EP_TYPE_BULK:
      wChRegVal |= USB_EP_BULK;
      break;

    case EP_TYPE_INTR:
      wChRegVal |= USB_EP_INTERRUPT;
      break;

    case EP_TYPE_ISOC:
      wChRegVal |= USB_EP_ISOCHRONOUS;
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  wChRegVal &= ~USB_CHEP_DEVADDR;
  wChRegVal |= (((uint32_t)dev_address << USB_CHEP_DEVADDR_Pos) |
                ((uint32_t)epnum & 0x0FU));

   /* Get Host core Speed */
   HostCoreSpeed = USB_GetHostSpeed(USBx);

  /* Set the device speed in case using HUB FS with device LS */
  if ((speed == USB_DRD_SPEED_LS) && (HostCoreSpeed == USB_DRD_SPEED_FS))
  {
    wChRegVal |= USB_CHEP_LSEP;
  }

  /* Set the dev_address & ep type */
  USB_DRD_SET_CHEP(USBx, phy_ch_num, (wChRegVal | USB_CH_VTRX | USB_CH_VTTX));

  /* Set the Rx Count */
  USB_DRD_SET_CHEP_RX_CNT(USBx, phy_ch_num, mps);

  return ret;
}

/**
  * @brief  Start a transfer over a host channel
  * @param  USBx Selected device
  * @param  hc pointer to host channel structure
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_StartXfer(USB_DRD_TypeDef *USBx,
                                   USB_DRD_HCTypeDef *hc)
{
  uint32_t len;
  uint32_t phy_ch_num = (uint32_t)hc->phy_ch_num;
  uint32_t ch_reg = USB_DRD_GET_CHEP(USBx, phy_ch_num);

  if (hc->ch_dir == CH_IN_DIR)  /* In Channel */
  {
    /* Multi packet transfer */
    if (hc->xfer_len > hc->max_packet)
    {
      len = hc->max_packet;
    }
    else
    {
      len = hc->xfer_len;
    }

    if (hc->doublebuffer == 0U)
    {
      /* Set RX buffer count */
      USB_DRD_SET_CHEP_RX_CNT(USBx, phy_ch_num, len);
    }
    else if (hc->ep_type == EP_TYPE_BULK)
    {
      /* Double buffer activated */
      if ((hc->xfer_len > hc->max_packet))
      {
        (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_DBUFF_ENBALE);

        /*Set the Double buffer counter*/
        USB_DRD_SET_CHEP_DBUF_CNT(USBx, phy_ch_num, hc->ch_dir, len);
      }
      else  /* switch to single buffer mode */
      {
        (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_DBUFF_DISABLE);

        /* Set RX buffer count */
        USB_DRD_SET_CHEP_RX_CNT(USBx, phy_ch_num, len);
      }
    }
    else  /* isochronous */
    {
      /*Set the Double buffer counter*/
      USB_DRD_SET_CHEP_DBUF_CNT(USBx, phy_ch_num, hc->ch_dir, len);
    }

    /*Enable host channel */
    USB_DRD_SET_CHEP_RX_STATUS(USBx, phy_ch_num, USB_CHEP_RX_STRX);
  }
  else   /* Out Channel */
  {
    /* Multi packet transfer*/
    if (hc->xfer_len > hc->max_packet)
    {
      len = hc->max_packet;
    }
    else
    {
      len = hc->xfer_len;
    }

    /* configure and validate Tx endpoint */
    if (hc->doublebuffer == 0U)
    {
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaadress, (uint16_t)len);
      USB_DRD_SET_CHEP_TX_CNT(USBx, phy_ch_num, (uint16_t)len);
      /*SET PID SETUP  */
      if ((hc->data_pid) == HC_PID_SETUP)
      {
        USB_DRD_CHEP_TX_SETUP(USBx,  phy_ch_num);
      }
    }
    else if (hc->ep_type == EP_TYPE_BULK)
    {
      (void)USB_HC_BULK_DB_StartXfer(USBx, hc, ch_reg, &len);
    }
    else
    {
      (void)USB_HC_ISO_DB_StartXfer(USBx, hc, len);
    }

    /* Enable host channel */
    USB_DRD_SET_CHEP_TX_STATUS(USBx, hc->phy_ch_num, USB_CH_TX_VALID);
  }

  return HAL_OK;
}
/**
  * @brief  Start Transfer of Channel isochronous out double buffer
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @param  len Transfer Length
  * @retval HAL state
  */
static HAL_StatusTypeDef USB_HC_ISO_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                 USB_DRD_HCTypeDef *hc,
                                                 uint32_t len)
{
  uint32_t phy_ch_num = (uint32_t)hc->phy_ch_num;

  /* check the DTOG_TX to determine in which buffer we should write */
  if ((USB_DRD_GET_CHEP(USBx, phy_ch_num) & USB_CH_DTOG_TX) != 0U)
  {
    if (hc->pmabuff1_state == USB_PMABUF_EMPTY)
    {
      /* Set the Double buffer counter for pmabuffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, hc->ch_dir, len);
      hc->pmabuff1_state = USB_PMABUF_NOT_EMPTY;
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr1, (uint16_t)len);

      if (hc->pmabuff0_state == USB_PMABUF_EMPTY)
      {
        hc->urb_state = URB_DONE;
      }
    }
    else if (hc->pmabuff0_state == USB_PMABUF_EMPTY)
    {
      /* Set the Double buffer counter for pmabuffer0 */
      USB_DRD_SET_CHEP_DBUF0_CNT(USBx, phy_ch_num, hc->ch_dir, len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)len);
      hc->pmabuff0_state = USB_PMABUF_NOT_EMPTY;
    }
    else
    {
      /* both buffer are not empty, should not be in this condition */
      /*...*/
    }
  }
  else
  {
    /* DTOGTX=0 */
    if (hc->pmabuff0_state == USB_PMABUF_EMPTY)
    {
      /* Set the Double buffer counter for pmabuffer0 */
      USB_DRD_SET_CHEP_DBUF0_CNT(USBx, phy_ch_num, hc->ch_dir, len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)len);
      hc->pmabuff0_state = USB_PMABUF_NOT_EMPTY;
      if (hc->pmabuff1_state == USB_PMABUF_EMPTY)
      {
        hc->urb_state = URB_DONE;
      }
    }
    else if (hc->pmabuff1_state == USB_PMABUF_EMPTY)
    {
      /* Set the Double buffer counter for pmabuffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, hc->ch_dir, len);
      hc->pmabuff1_state = USB_PMABUF_NOT_EMPTY;
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr1, (uint16_t)len);
    }
    else
    {
      /*...*/
    }
  }

  return HAL_OK;
}

/**
  * @brief  Start Transfer of Channel bulk out double buffer
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @param  ch_reg snapshot of the CHEPR register
  * @param  len Transfer Length
  * @retval HAL state
  */
static HAL_StatusTypeDef USB_HC_BULK_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                  USB_DRD_HCTypeDef *hc,
                                                  uint32_t ch_reg,
                                                  uint32_t *len)
{
  uint32_t phy_ch_num = (uint32_t)hc->phy_ch_num;

  /* -Double Buffer Mangement- */
  if (hc->xfer_len_db > hc->max_packet)
  {
    /* enable double buffer mode */
    (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_DBUFF_ENBALE);
    *len = hc->max_packet;
    hc->xfer_len_db -= *len;

    /* Prepare two buffer before enabling host */
    if ((ch_reg & USB_CH_DTOG_TX) == 0U)
    {
      /* Write Buffer0 */
      USB_DRD_SET_CHEP_TX_CNT(USBx, phy_ch_num, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)*len);
    }
    else
    {
      /* Write Buffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(USBx, (uint8_t) phy_ch_num, 0U, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr1, (uint16_t)*len);
    }

    hc->xfer_buff += *len;

    /* Multi packet transfer */
    if (hc->xfer_len_db > hc->max_packet)
    {
      hc->xfer_len_db -= *len;
    }
    else
    {
      *len = hc->xfer_len_db;
      hc->xfer_len_db = 0U;
    }

    if ((ch_reg & USB_CH_DTOG_TX) == 0U)
    {
      /* Write Buffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, 0U, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr1, (uint16_t)*len);
    }
    else
    {
      /* Write Buffer0 */
      USB_DRD_SET_CHEP_TX_CNT(USBx, phy_ch_num, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)*len);
    }
  }
  else
  {
    /* Disable double buffer mode */
    (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_DBUFF_DISABLE);

    USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)*len);
    USB_DRD_SET_CHEP_TX_CNT(USBx, phy_ch_num, (uint16_t)*len);
  }

  return HAL_OK;
}

/**
  * @brief  Halt a host channel in
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_IN_Halt(USB_DRD_TypeDef *USBx, uint8_t phy_ch)
{
  /* Set disable to Channel */
  USB_DRD_SET_CHEP_RX_STATUS(USBx, phy_ch, USB_CH_RX_DIS);

  return HAL_OK;
}
/**
  * @brief  Halt a host channel out
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_OUT_Halt(USB_DRD_TypeDef *USBx, uint8_t phy_ch)
{
  /* Set disable to Channel */
  USB_DRD_SET_CHEP_TX_STATUS(USBx, phy_ch, USB_CH_TX_DIS);

  return HAL_OK;
}

/**
  * @brief  Stop Host Core
  * @param  USBx Selected device
  * @retval HAL state
  */
HAL_StatusTypeDef USB_StopHost(USB_DRD_TypeDef *USBx)
{
  USBx->ISTR &= ~(USB_ISTR_DIR | USB_ISTR_L1REQ |
                  USB_ISTR_ESOF | USB_ISTR_SOF |
                  USB_ISTR_RESET | USB_ISTR_DCON |
                  USB_ISTR_SUSP | USB_ISTR_WKUP |
                  USB_ISTR_ERR | USB_ISTR_PMAOVR |
                  USB_ISTR_CTR);

  /* Set PowerDown */
  USBx->CNTR |= USB_CNTR_PDWN;

  /* Force a Reset */
  USBx->CNTR |= USB_CNTR_USBRST;

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (USB_DRD_FS) */
#endif /* defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED) */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
