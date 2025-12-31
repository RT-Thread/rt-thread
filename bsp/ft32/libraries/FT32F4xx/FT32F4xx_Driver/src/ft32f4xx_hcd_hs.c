/**
  ******************************************************************************
  * @file    			ft32f4xx_hcd_hs.c
  * @author  			FMD XA
  * @brief   			This file provides firmware functions to manage the following 
  *          			functionalities of the USB Peripheral Controller:
  *           		+ Initialization/de-initialization functions
  *           		+ Peripheral Control functions
  *           		+ Peripheral State functions
  * @version 			V1.0.0           
  * @data		 			2025-03-26
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
  [..]
    (#)Declare a HCD_HS_HandleTypeDef handle structure, for example:
       HCD_HS_HandleTypeDef  hhcd;

    (#)Fill parameters of Init structure in HCD handle

    (#)Call HCD_HS_Init() API to initialize the HCD peripheral (Core, Host core, ...)

    (#)Initialize the HCD low level resources through the HCD_HS_MspInit() API:
        (##) Enable the HCD/USB Low Level interface clock using the following macros
        (##) Initialize the related GPIO clocks
        (##) Configure HCD pin-out
        (##) Configure HCD NVIC interrupt

    (#)Associate the Upper USB Host stack to the HCD Driver:
        (##) hhcd.pData = phost;

    (#)Enable HCD transmission and reception:
        (##) HCD_HS_Start();

  @endverbatim
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "ft32f4xx_hcd_hs.h"
#include "ft32f4xx_rcc.h"


/** @addtogroup FT32F4xx_DRIVER
  * @{
  */

#ifdef HCD_MODULE_ENABLED
#if defined (USB_OTG_HS)
/** @defgroup HCD_HS HCD
  * @brief HCD HS module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup HCD_HS_Private_Functions HCD Private Functions
  * @{
  */
static void HCD_HS_HC_IN_IRQHandler(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum);
static void HCD_HS_HC_OUT_IRQHandler(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum);
static void HCD_HS_RXQLVL_IRQHandler(HCD_HS_HandleTypeDef *hhcd);
static void HCD_HS_Port_IRQHandler(HCD_HS_HandleTypeDef *hhcd);
/**
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HCD_HS_Exported_Functions HCD Exported Functions
  * @{
  */

/** @defgroup HCD_HS_Exported_Functions_Group1 Initialization and de-initialization functions
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
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef HCD_HS_Init(HCD_HS_HandleTypeDef *hhcd)
{

  /* Check the HCD handle allocation */
  if (hhcd == NULL)
  {
    return USB_HS_ERROR;
  }

  if (hhcd->State == HCD_HS_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hhcd->Lock = USB_HS_UNLOCKED;


    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HCD_HS_MspInit(hhcd);
  }

  hhcd->State = HCD_HS_STATE_BUSY;

  /* Disable the Interrupts */
  __HCD_HS_DISABLE();

  /* Init the Core (common init.) */
  if (USB_HS_CoreInit(hhcd->Init) != USB_HS_OK)
  {
    hhcd->State = HCD_HS_STATE_ERROR;
    return USB_HS_ERROR;
  }

  /* Init Host */
  if (USB_HS_HostInit(hhcd->Init) != USB_HS_OK)
  {
    hhcd->State = HCD_HS_STATE_ERROR;
    return USB_HS_ERROR;
  }

  hhcd->State = HCD_HS_STATE_READY;

  return USB_HS_OK;
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
  *            HCD_DEVICE_SPEED_HIGH: high speed mode,
  *            HCD_DEVICE_SPEED_FULL: Full speed mode,
  *            HCD_DEVICE_SPEED_LOW: Low speed mode
  * @param  ep_type Endpoint Type.
  *          This parameter can be one of these values:
  *            EP_TYPE_CTRL: Control type,
  *            EP_TYPE_ISOC: Isochronous type,
  *            EP_TYPE_BULK: Bulk type,
  *            EP_TYPE_INTR: Interrupt type
  * @param  mps Max Packet Size.
  *          This parameter can be a value from 0 to32K
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef HCD_HS_HC_Init(HCD_HS_HandleTypeDef *hhcd,
                                  uint8_t ch_num,
                                  uint8_t epnum,
                                  uint8_t dev_address,
                                  uint8_t speed,
                                  uint8_t ep_type,
                                  uint16_t mps)
{
  USB_HS_StatusTypeDef status;
  uint32_t HostCoreSpeed;
  uint32_t HCcharMps = mps;

  __USB_HS_LOCK(hhcd);
  hhcd->hc[ch_num].do_ping = 0U;
  hhcd->hc[ch_num].dev_addr = dev_address;
  hhcd->hc[ch_num].ch_num = ch_num;
  hhcd->hc[ch_num].ep_type = ep_type;
  hhcd->hc[ch_num].ep_num = epnum & 0x7FU;

  HCD_HS_HC_ClearHubInfo(hhcd, ch_num);

  if ((epnum & 0x80U) == 0x80U)
  {
    hhcd->hc[ch_num].ep_is_in = 1U;
  }
  else
  {
    hhcd->hc[ch_num].ep_is_in = 0U;
  }

  HostCoreSpeed = USB_HS_GetHostSpeed();

  if (ep_type == EP_TYPE_ISOC)
  {
    /* FS device plugged to HS HUB */
    if ((speed == HCD_DEVICE_SPEED_FULL) && (HostCoreSpeed == HPRT0_PRTSPD_HIGH_SPEED))
    {
      if (HCcharMps > ISO_SPLT_MPS)
      {
        /* ISO Max Packet Size for Split mode */
        HCcharMps = ISO_SPLT_MPS;
      }
    }
  }

  hhcd->hc[ch_num].speed = speed;
  hhcd->hc[ch_num].max_packet = (uint16_t)HCcharMps;

  status =  USB_HS_HC_Init(ch_num,
                           epnum,
                           dev_address,
                           speed,
                           ep_type,
                           (uint16_t)HCcharMps);
  __USB_HS_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  Halt a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef HCD_HS_HC_Halt(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num)
{
  USB_HS_StatusTypeDef status = USB_HS_OK;

  __USB_HS_LOCK(hhcd);
  (void)USB_HS_HC_Halt(ch_num);
  __USB_HS_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  DeInitialize the host driver.
  * @param  hhcd HCD handle
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef HCD_HS_DeInit(HCD_HS_HandleTypeDef *hhcd)
{
  /* Check the HCD handle allocation */
  if (hhcd == NULL)
  {
    return USB_HS_ERROR;
  }

  hhcd->State = HCD_HS_STATE_BUSY;

  __HCD_HS_DISABLE();

  hhcd->State = HCD_HS_STATE_RESET;

  /* DeInit the low level hardware: CLOCK, NVIC.*/
  HCD_HS_MspDeInit(hhcd);

  return USB_HS_OK;
}

/**
  * @brief  Initialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_HS_MspInit(HCD_HS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_MspInit could be implemented in the user file
   */


}

/**
  * @brief  DeInitialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_HS_MspDeInit(HCD_HS_HandleTypeDef *hhcd)
{
   /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_MspDeInit could be implemented in the user file
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
  *            EP_TYPE_CTRL: Control type/
  *            EP_TYPE_ISOC: Isochronous type/
  *            EP_TYPE_BULK: Bulk type/
  *            EP_TYPE_INTR: Interrupt type/
  * @param  token Endpoint Type.
  *          This parameter can be one of these values:
  *            0: HC_PID_SETUP / 1: HC_PID_DATA1
  * @param  pbuff pointer to URB data
  * @param  length Length of URB data
  * @param  do_ping activate do ping protocol (for high speed only).
  *          This parameter can be one of these values:
  *           0 : do ping inactive / 1 : do ping active
  */
void HCD_HS_HC_SubmitRequest(HCD_HS_HandleTypeDef *hhcd,
                                           uint8_t ch_num,
                                           uint8_t direction,
                                           uint8_t ep_type,
                                           uint8_t token,
                                           uint8_t *pbuff,
                                           uint16_t length,
                                           uint8_t do_ping)
{
  hhcd->hc[ch_num].ep_is_in = direction;
  hhcd->hc[ch_num].ep_type  = ep_type;

  if (token == 0U)
  {
    hhcd->hc[ch_num].data_pid = HC_PID_SETUP;
    hhcd->hc[ch_num].do_ping = do_ping;
  }
  else
  {
    hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
  }

  /* Manage Data Toggle */
  switch (ep_type)
  {
    case EP_TYPE_CTRL:
      if (token == 1U)  /* out send data */
      {
        if (direction == 0U)
        {
          if (length == 0U)
          {
            /* For Status OUT stage, Length==0, Status Out PID = 1 */
            hhcd->hc[ch_num].toggle_out = 1U;
          }
          /* Set the Data Toggle bit as per the Flag */
          if (hhcd->hc[ch_num].toggle_out == 0U)
          {
            /* Put the PID 0 */
            hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
          }
          else
          {
            /* Put the PID 1 */
            hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
          }
        }
        else
        {
          if (hhcd->hc[ch_num].do_ssplit == 1U)
          {
            if (hhcd->hc[ch_num].toggle_in == 0U)
            {
              hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
            }
            else
            {
              hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
            }
          }
        }
      }
      break;

    case EP_TYPE_BULK:
      if (direction == 0U)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->hc[ch_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->hc[ch_num].toggle_in == 0U)
        {
          hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
        }
        else
        {
          hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
        }
      }

      break;

    case EP_TYPE_INTR:
      if (direction == 0U)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->hc[ch_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->hc[ch_num].toggle_in == 0U)
        {
          hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
        }
        else
        {
          hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
        }
      }
      break;

    case EP_TYPE_ISOC:
      hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
      break;

    default:
      break;
  }

  hhcd->hc[ch_num].xfer_buff = pbuff;
  hhcd->hc[ch_num].xfer_len  = length;
  hhcd->hc[ch_num].urb_state = URB_IDLE;
  hhcd->hc[ch_num].xfer_count = 0U;
  hhcd->hc[ch_num].ch_num = ch_num;
  hhcd->hc[ch_num].state = HC_IDLE;

  USB_HS_HC_StartXfer(&hhcd->hc[ch_num], (uint8_t)hhcd->Init.dma_enable);
}

/**
  * @brief  Handle HCD interrupt request.
  * @param  hhcd HCD handle
  * @retval None
  */
void HCD_HS_IRQHandler(HCD_HS_HandleTypeDef *hhcd)
{
  uint32_t i;
  uint32_t interrupt;

  /* Ensure that we are in device mode */
  if (USB_HS_GetMode() == USB_OTG_MODE_HOST)
  {
    /* Avoid spurious interrupt */
    if (__HCD_HS_IS_INVALID_INTERRUPT())
    {
      return;
    }

    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_IPXFR_INCOMPISOOUT))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_IPXFR_INCOMPISOOUT);
    }

    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_IISOIXFR))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_IISOIXFR);
    }

    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_PTXFE))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_PTXFE);
    }

    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_MMIS))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_MMIS);
    }

    /* Handle Host Disconnect Interrupts */
    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_DISCINT))
    {
      __HCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_DISCINT);

      if ((USB_HS_HPRT0 & OTG_HS_HPRT_PCSTS) == 0U)
      {
        /* Handle Host Port Disconnect Interrupt */
        HCD_HS_Disconnect_Callback(hhcd);

      }
    }

    /* Handle Host Port Interrupts */
    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_HPRTINT))
    {
      HCD_HS_Port_IRQHandler(hhcd);
    }

    /* Handle Host SOF Interrupt */
    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_SOF))
    {
      HCD_HS_SOF_Callback(hhcd);

      __HCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_SOF);
    }

    /* Handle Host channel Interrupt */
    if (__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_HCINT))
    {
      interrupt = USB_HS_HC_ReadInterrupt();
      for (i = 0U; i < hhcd->Init.Host_channels; i++)
      {
        if ((interrupt & (1UL << (i & 0xFU))) != 0U)
        {
          if ((USB_HS_HC(i)->HCCHAR & OTG_HS_HCCHAR_EPDIR) == OTG_HS_HCCHAR_EPDIR)
          {
            HCD_HS_HC_IN_IRQHandler(hhcd, (uint8_t)i);
          }
          else
          {
            HCD_HS_HC_OUT_IRQHandler(hhcd, (uint8_t)i);
          }
        }
      }
      __HCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_HCINT);
    }

    /* Handle Rx Queue Level Interrupts */
    if ((__HCD_HS_GET_FLAG(OTG_HS_GINTSTS_RXFLVL)) != 0U)
    {
      USB_HS_MASK_INTERRUPT(OTG_HS_GINTSTS_RXFLVL);

      HCD_HS_RXQLVL_IRQHandler(hhcd);

      USB_HS_UNMASK_INTERRUPT(OTG_HS_GINTSTS_RXFLVL);
    }
  }
}


/**
  * @brief  Handles HCD Wakeup interrupt request.
  * @param  hhcd HCD handle
  * @retval status
  */
void HCD_HS_WKUP_IRQHandler(HCD_HS_HandleTypeDef *hhcd)
{
  UNUSED(hhcd);
}


/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__attribute__((weak)) void HCD_HS_SOF_Callback(HCD_HS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_SOF_Callback could be implemented in the user file
   */
}

/**
  * @brief Connection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_HS_Connect_Callback(HCD_HS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_Connect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_HS_Disconnect_Callback(HCD_HS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_Disconnect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Port Enabled  Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_HS_PortEnabled_Callback(HCD_HS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_Disconnect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Port Disabled  Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_HS_PortDisabled_Callback(HCD_HS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_Disconnect_Callback could be implemented in the user file
   */
}


/**
  * @brief  Notify URB state change callback.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  urb_state:
  *          This parameter can be one of these values:
  *            URB_IDLE/
  *            URB_DONE/
  *            URB_NOTREADY/
  *            URB_NYET/
  *            URB_ERROR/
  *            URB_STALL/
  * @retval None
  */
void __attribute__((weak)) HCD_HS_HC_NotifyURBChange_Callback(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum, HCD_HS_URBStateTypeDef urb_state)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);
  UNUSED(chnum);
  UNUSED(urb_state);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_HS_HC_NotifyURBChange_Callback could be implemented in the user file
   */
}


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
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef HCD_HS_Start(HCD_HS_HandleTypeDef *hhcd)
{
  __USB_HS_LOCK(hhcd);
  /* Enable port power */
  USB_HS_DriveVbus(1U);

  /* Enable global interrupt */
  __HCD_HS_ENABLE();
  __USB_HS_UNLOCK(hhcd);

  return USB_HS_OK;
}

/**
  * @brief  Stop the host driver.
  * @param  hhcd HCD handle
  * @retval USB_HS status
  */

USB_HS_StatusTypeDef HCD_HS_Stop(HCD_HS_HandleTypeDef *hhcd)
{
  __USB_HS_LOCK(hhcd);
  (void)USB_HS_StopHost();
  __USB_HS_UNLOCK(hhcd);

  return USB_HS_OK;
}

/**
  * @brief  Reset the host port.
  * @param  hhcd HCD handle
  * @retval none
  */
void HCD_HS_ResetPort(void)
{
  USB_HS_ResetPort();
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
  * @retval HCD state
  */
HCD_HS_StateTypeDef HCD_HS_GetState(HCD_HS_HandleTypeDef *hhcd)
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
  *            URB_IDLE
  *            URB_DONE
  *            URB_NOTREADY
  *            URB_NYET
  *            URB_ERROR
  *            URB_STALL
  */
HCD_HS_URBStateTypeDef HCD_HS_HC_GetURBState(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum)
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
uint32_t HCD_HS_HC_GetXferCount(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum)
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
HCD_HS_HCStateTypeDef  HCD_HS_HC_GetState(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum)
{
  return hhcd->hc[chnum].state;
}

/**
  * @brief  Return the current Host frame number.
  * @param  hhcd HCD handle
  * @retval Current Host frame number
  */
uint32_t HCD_HS_GetCurrentFrame()
{
  return (USB_HS_GetCurrentFrame());
}

/**
  * @brief  Return the Host enumeration speed.
  * @param  hhcd HCD handle
  * @retval Enumeration speed
  */
uint32_t HCD_HS_GetCurrentSpeed()
{
  return (USB_HS_GetHostSpeed());
}

/**
  * @brief  Set host channel Hub information
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  addr Hub address
  * @param  PortNbr Hub port number
  * @retval none
  */
void HCD_HS_HC_SetHubInfo(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num, uint8_t addr, uint8_t PortNbr)
{
  uint32_t HostCoreSpeed = USB_HS_GetHostSpeed();

  /* LS/FS device plugged to HS HUB */
  if ((hhcd->hc[ch_num].speed != HCD_DEVICE_SPEED_HIGH) && (HostCoreSpeed == HPRT0_PRTSPD_HIGH_SPEED))
  {
    hhcd->hc[ch_num].do_ssplit = 1U;

    if ((hhcd->hc[ch_num].ep_type == EP_TYPE_CTRL) && (hhcd->hc[ch_num].ep_is_in != 0U))
    {
      hhcd->hc[ch_num].toggle_in = 1U;
    }
  }

  hhcd->hc[ch_num].hub_addr = addr;
  hhcd->hc[ch_num].hub_port_nbr = PortNbr;

}

/**
  * @brief  Clear host channel Hub information
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
void HCD_HS_HC_ClearHubInfo(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num)
{

  hhcd->hc[ch_num].do_ssplit = 0U;
  hhcd->hc[ch_num].do_csplit = 0U;
  hhcd->hc[ch_num].hub_addr  = 0U;
  hhcd->hc[ch_num].hub_port_nbr = 0U;

}


/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup HCD_Private_Functions
  * @{
  */
/**
  * @brief  Handle Host Channel IN interrupt requests.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_HS_HC_IN_IRQHandler(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum)
{
  uint32_t tmpreg;

  if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_AHBERR))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_AHBERR);
    hhcd->hc[chnum].state = HC_XACTERR;
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_BBERR))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_BBERR);
    hhcd->hc[chnum].state = HC_BBLERR;
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_STALL))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_STALL);
    hhcd->hc[chnum].state = HC_STALL;
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_DTERR))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_DTERR);
    hhcd->hc[chnum].state = HC_DATATGLERR;
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_TXERR))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_TXERR);
    hhcd->hc[chnum].state = HC_XACTERR;
    USB_HS_HC_Halt(chnum);
  }
  else
  {
    /* ... */
  }

  if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_FRMOR))
  {
    USB_HS_HC_Halt(chnum);
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_FRMOR);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_XFRC))
  {
    /* clear any pending ACK IT */
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_ACK);

    if (hhcd->hc[chnum].do_csplit == 1U)
    {
      hhcd->hc[chnum].do_csplit = 0U;
      __HCD_HS_CLEAR_HC_CSPLT(chnum);
    }

    if (hhcd->Init.dma_enable != 0U)
    {
      hhcd->hc[chnum].xfer_count = hhcd->hc[chnum].XferSize - (USB_HS_HC(chnum)->HCTSIZ & OTG_HS_HCTSIZ_XFRSIZ);
    }

    hhcd->hc[chnum].state = HC_XFRC;
    hhcd->hc[chnum].ErrCnt = 0U;
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_XFRC);

    if ((hhcd->hc[chnum].ep_type == EP_TYPE_CTRL) ||
        (hhcd->hc[chnum].ep_type == EP_TYPE_BULK))
    {
      USB_HS_HC_Halt(chnum);
      __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_NAK);
    }
    else if ((hhcd->hc[chnum].ep_type == EP_TYPE_INTR) ||
             (hhcd->hc[chnum].ep_type == EP_TYPE_ISOC))
    {
      USB_HS_HC(chnum)->HCCHAR |= OTG_HS_HCCHAR_ODDFRM;
      hhcd->hc[chnum].urb_state = URB_DONE;

      HCD_HS_HC_NotifyURBChange_Callback(hhcd, chnum, hhcd->hc[chnum].urb_state);
    }

    else
    {
      /* ... */
    }

    if (hhcd->Init.dma_enable == 1U)
    {
      if ((((hhcd->hc[chnum].xfer_count + hhcd->hc[chnum].max_packet -1U) / hhcd->hc[chnum].max_packet) & 1U) != 0U)
      {
        hhcd->hc[chnum].toggle_in ^= 1U;
      }
    }
    else
    {
      hhcd->hc[chnum].toggle_in ^= 1U;
    }
  }

  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_ACK))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_ACK);
    if (hhcd->hc[chnum].do_ssplit == 1U)
    {
      hhcd->hc[chnum].do_csplit = 1U;
      hhcd->hc[chnum].state = HC_ACK;

      USB_HS_HC_Halt(chnum);
    }
  }

  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_CHH))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_CHH);

    if (hhcd->hc[chnum].state == HC_XFRC)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].urb_state = URB_DONE;
    }
    else if (hhcd->hc[chnum].state == HC_STALL)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].urb_state = URB_STALL;
    }
    else if ((hhcd->hc[chnum].state == HC_XACTERR) ||
             (hhcd->hc[chnum].state == HC_DATATGLERR))
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].ErrCnt++;
      if (hhcd->hc[chnum].ErrCnt > 2U)
      {
        hhcd->hc[chnum].ErrCnt = 0U;
        if (hhcd->hc[chnum].do_ssplit == 1U)
        {
          hhcd->hc[chnum].do_csplit = 0U;
          hhcd->hc[chnum].ep_ss_schedule = 0U;
          __HCD_HS_CLEAR_HC_CSPLT(chnum);
        }
        hhcd->hc[chnum].urb_state = URB_ERROR;
      }
      else
      {
        hhcd->hc[chnum].urb_state = URB_NOTREADY;
        if ((hhcd->hc[chnum].ep_type == EP_TYPE_CTRL) ||
            (hhcd->hc[chnum].ep_type == EP_TYPE_BULK))
        {
          /* re-activate the channel */
          tmpreg = USB_HS_HC(chnum)->HCCHAR;
          tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
          tmpreg |= OTG_HS_HCCHAR_CHENA;
          USB_HS_HC(chnum)->HCCHAR = tmpreg;
        }
      }
    }
    else if (hhcd->hc[chnum].state == HC_NYET)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      if (hhcd->hc[chnum].do_csplit == 1U)
      {
        if (hhcd->hc[chnum].ep_type == EP_TYPE_INTR)
        {
          hhcd->hc[chnum].NyetErrCnt++;
          if (hhcd->hc[chnum].NyetErrCnt > 2U)
          {
            hhcd->hc[chnum].NyetErrCnt = 0U;
            hhcd->hc[chnum].do_csplit = 0U;

            if (hhcd->hc[chnum].ErrCnt < 3U)
            {
              hhcd->hc[chnum].ep_ss_schedule = 1U;
            }
            __HCD_HS_CLEAR_HC_CSPLT(chnum);
            hhcd->hc[chnum].urb_state = URB_ERROR;
          }
          else
          {
            hhcd->hc[chnum].urb_state = URB_NOTREADY;
          }
        }
        else
        {
          hhcd->hc[chnum].urb_state = URB_NOTREADY;
        }

        if ((hhcd->hc[chnum].ep_type == EP_TYPE_CTRL) ||
            (hhcd->hc[chnum].ep_type == EP_TYPE_BULK))
        {
          /* re-activate the channel */
          tmpreg = USB_HS_HC(chnum)->HCCHAR;
          tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
          tmpreg |= OTG_HS_HCCHAR_CHENA;
          USB_HS_HC(chnum)->HCCHAR = tmpreg;
        }
      }
    }
    else if (hhcd->hc[chnum].state == HC_ACK)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      if (hhcd->hc[chnum].do_csplit == 1U)
      {
        hhcd->hc[chnum].urb_state = URB_NOTREADY;

        /* Set Complete split and re-active the channel */
        USB_HS_HC(chnum)->HCSPLT |= OTG_HS_HCSPLT_COMPLSPLT;
        USB_HS_HC(chnum)->HCINTMSK |= OTG_HS_HCINTMSK_NYETM;
        USB_HS_HC(chnum)->HCINTMSK &= ~OTG_HS_HCINTMSK_ACKM;

        if ((hhcd->hc[chnum].ep_type == EP_TYPE_CTRL) ||
            (hhcd->hc[chnum].ep_type == EP_TYPE_BULK))
        {
          /* re-activate the channel */
          tmpreg = USB_HS_HC(chnum)->HCCHAR;
          tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
          tmpreg |= OTG_HS_HCCHAR_CHENA;
          USB_HS_HC(chnum)->HCCHAR = tmpreg;
        }
      }
    }

    else if (hhcd->hc[chnum].state == HC_NAK)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].urb_state  = URB_NOTREADY;

      if ((hhcd->hc[chnum].ep_type == EP_TYPE_CTRL) ||
            (hhcd->hc[chnum].ep_type == EP_TYPE_BULK))
      {
        /* re-activate the channel */
        tmpreg = USB_HS_HC(chnum)->HCCHAR;
        tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
        tmpreg |= OTG_HS_HCCHAR_CHENA;
        USB_HS_HC(chnum)->HCCHAR = tmpreg;
      }
    }
    else if (hhcd->hc[chnum].state == HC_BBLERR)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].ErrCnt++;
      hhcd->hc[chnum].urb_state = URB_ERROR;
    }
    else
    {
      if (hhcd->hc[chnum].state == HC_HALTED)
      {
        return;
      }
    }

    HCD_HS_HC_NotifyURBChange_Callback(hhcd, chnum, hhcd->hc[chnum].urb_state);
  }

  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_NAK))
  {
    if (hhcd->hc[chnum].ep_type == EP_TYPE_INTR)
    {
      hhcd->hc[chnum].ErrCnt = 0U;
      hhcd->hc[chnum].state  = HC_NAK;
      USB_HS_HC_Halt(chnum);
    }
    else if ((hhcd->hc[chnum].ep_type == EP_TYPE_CTRL) ||
        (hhcd->hc[chnum].ep_type == EP_TYPE_BULK))
    {
      hhcd->hc[chnum].ErrCnt = 0U;

      if ((hhcd->Init.dma_enable == 0U) || (hhcd->hc[chnum].do_csplit == 1U))
      {
        hhcd->hc[chnum].state  = HC_NAK;
        USB_HS_HC_Halt(chnum);
      }
    }
    else
    {
      /*...*/
    }

    if (hhcd->hc[chnum].do_csplit == 1U)
    {
      hhcd->hc[chnum].do_csplit = 0U;
      __HCD_HS_CLEAR_HC_CSPLT(chnum);
      __HCD_HS_UNMASK_ACK_HC_INT(chnum);
    }
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_NAK);
  }
  else
  {
    /*...*/
  }

}

/**
  * @brief  Handle Host Channel OUT interrupt requests.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_HS_HC_OUT_IRQHandler(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum)
{
  uint32_t tmpreg;
  uint32_t num_packets;

    if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_AHBERR))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_AHBERR);
    hhcd->hc[chnum].state = HC_XACTERR;
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_ACK))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_ACK);
    if (hhcd->hc[chnum].do_ping == 1U)
    {
      hhcd->hc[chnum].do_ping = 0U;
      hhcd->hc[chnum].urb_state = URB_NOTREADY;
      hhcd->hc[chnum].state = HC_ACK;
      USB_HS_HC_Halt(chnum);
    }

    if ((hhcd->hc[chnum].do_ssplit == 1U) && (hhcd->hc[chnum].do_csplit == 0U))
    {
      if (hhcd->hc[chnum].ep_type != EP_TYPE_ISOC)
      {
        hhcd->hc[chnum].do_csplit = 1U;
      }
      hhcd->hc[chnum].state = HC_ACK;
      USB_HS_HC_Halt(chnum);

      /* reset error_count */
      hhcd->hc[chnum].ErrCnt = 0U;
    }
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_FRMOR))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_FRMOR);
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_XFRC))
  {
    hhcd->hc[chnum].ErrCnt = 0U;

    /* transaction completed with NYET state, update do ping state */
    if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_NYET))
    {
      hhcd->hc[chnum].do_ping = 1U;
      __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_NYET);
    }
    if (hhcd->hc[chnum].do_csplit != 0U)
    {
      hhcd->hc[chnum].do_csplit = 0U;
      __HCD_HS_CLEAR_HC_CSPLT(chnum);
    }

    /* clear any pending IT */
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_XFRC);
    hhcd->hc[chnum].state = HC_XFRC;
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_NYET))
  {
    hhcd->hc[chnum].state = HC_NYET;

    if (hhcd->hc[chnum].do_ssplit == 0U)
    {
      hhcd->hc[chnum].do_ping = 1U;
    }

    hhcd->hc[chnum].ErrCnt = 0U;
    USB_HS_HC_Halt(chnum);
    /* clear any pending IT */
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_NYET);
  }

  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_STALL))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_STALL);
    hhcd->hc[chnum].state = HC_STALL;
    USB_HS_HC_Halt(chnum);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_NAK))
  {
    hhcd->hc[chnum].ErrCnt = 0U;
    hhcd->hc[chnum].state = HC_NAK;

    if (hhcd->hc[chnum].do_ping == 0U)
    {
      if (hhcd->hc[chnum].speed == HCD_DEVICE_SPEED_HIGH)
      {
        hhcd->hc[chnum].do_ping = 1U;
      }
    }

    USB_HS_HC_Halt(chnum);
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_NAK);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_TXERR))
  {
    if (hhcd->Init.dma_enable == 0U)
    {
      hhcd->hc[chnum].state = HC_XACTERR;
      USB_HS_HC_Halt(chnum);
    }
    else
    {
      hhcd->hc[chnum].ErrCnt++;
      if (hhcd->hc[chnum].ErrCnt > 2U)
      {
        hhcd->hc[chnum].urb_state = URB_ERROR;

        HCD_HS_HC_NotifyURBChange_Callback(hhcd, chnum, hhcd->hc[chnum].urb_state);
      }
      else
      {
        hhcd->hc[chnum].urb_state = URB_NOTREADY;

        /* Re-activate the channel */
        tmpreg = USB_HS_HC(chnum)->HCCHAR;
        tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
        tmpreg |= OTG_HS_HCCHAR_CHENA;
        USB_HS_HC(chnum)->HCCHAR = tmpreg;
      }
    }
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_TXERR);
  }

  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_DTERR))
  {
    hhcd->hc[chnum].state = HC_DATATGLERR;
    USB_HS_HC_Halt(chnum);
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_DTERR);
  }
  else if (__HCD_HS_GET_CH_FLAG(chnum, OTG_HS_HCINT_CHH))
  {
    __HCD_HS_CLEAR_HC_INT(chnum, OTG_HS_HCINT_CHH);

    if (hhcd->hc[chnum].state == HC_XFRC)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].urb_state = URB_DONE;

      if ((hhcd->hc[chnum].ep_type == EP_TYPE_BULK) ||
          (hhcd->hc[chnum].ep_type == EP_TYPE_INTR))
      {
        if (hhcd->Init.dma_enable == 0U)
        {
          hhcd->hc[chnum].toggle_out ^= 1U;
        }
        if ((hhcd->Init.dma_enable == 1U) && (hhcd->hc[chnum].xfer_len > 0U))
        {
          num_packets = (hhcd->hc[chnum].xfer_len + hhcd->hc[chnum].max_packet - 1U) / hhcd->hc[chnum].max_packet;
          if ((num_packets & 1U) != 0U)
          {
            hhcd->hc[chnum].toggle_out ^= 1U;
          }
        }
      }
    }
    else if (hhcd->hc[chnum].state == HC_ACK)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      if (hhcd->hc[chnum].do_csplit == 1U)
      {
        hhcd->hc[chnum].urb_state = URB_NOTREADY;
      }
    }
    else if (hhcd->hc[chnum].state == HC_NAK)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].urb_state  = URB_NOTREADY;

      if (hhcd->hc[chnum].do_csplit == 1U)
      {
        hhcd->hc[chnum].do_csplit = 0U;
        __HCD_HS_CLEAR_HC_CSPLT(chnum);
      }
    }
    else if (hhcd->hc[chnum].state == HC_NYET)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].urb_state = URB_NOTREADY;
    }
    else if (hhcd->hc[chnum].state == HC_STALL)
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].urb_state = URB_STALL;
    }
    else if ((hhcd->hc[chnum].state == HC_XACTERR) ||
             (hhcd->hc[chnum].state == HC_DATATGLERR))
    {
      hhcd->hc[chnum].state = HC_HALTED;
      hhcd->hc[chnum].ErrCnt++;
      if (hhcd->hc[chnum].ErrCnt > 2U)
      {
        hhcd->hc[chnum].ErrCnt = 0U;
        hhcd->hc[chnum].urb_state = URB_ERROR;
      }
      else
      {
        hhcd->hc[chnum].urb_state = URB_NOTREADY;
        /* re-activate the channel */
        tmpreg = USB_HS_HC(chnum)->HCCHAR;
        tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
        tmpreg |= OTG_HS_HCCHAR_CHENA;
        USB_HS_HC(chnum)->HCCHAR = tmpreg;
      }
    }
    else
    {
      return;
    }

    HCD_HS_HC_NotifyURBChange_Callback(hhcd, chnum, hhcd->hc[chnum].urb_state);

  }

  else
  {
    return;
  }
}

/**
  * @brief  Handle Rx Queue Level interrupt requests.
  * @param  hhcd HCD handle
  * @retval none
  */
static void HCD_HS_RXQLVL_IRQHandler(HCD_HS_HandleTypeDef *hhcd)
{
  uint32_t pktsts;
  uint32_t pktcnt;
  uint32_t GrxstspReg;
  uint32_t xferSizePktCnt;
  uint32_t tmpreg;
  uint32_t chnum;

  GrxstspReg = USB_HS->GRXSTSP;
  chnum = GrxstspReg & OTG_HS_GRXSTSP_CHNUM;
  pktsts = (GrxstspReg & OTG_HS_GRXSTSP_PKTSTS) >> 17;
  pktcnt = (GrxstspReg & OTG_HS_GRXSTSP_BCNT) >> 4;

  switch (pktsts)
  {
    case GRXSTS_PKTSTS_IN:
      /* Read the data into the host buffer. */
      if ((pktcnt > 0U) && (hhcd->hc[chnum].xfer_buff != (void *)0))
      {
        if ((hhcd->hc[chnum].xfer_count + pktcnt) <= hhcd->hc[chnum].xfer_len)
        {
          USB_HS_ReadPacket(hhcd->hc[chnum].xfer_buff, (uint16_t)pktcnt);

          /* manage multiple Xfer */
          hhcd->hc[chnum].xfer_buff += pktcnt;
          hhcd->hc[chnum].xfer_count += pktcnt;

          /* get transfer size packet count */
          xferSizePktCnt = (USB_HS_HC(chnum)->HCTSIZ & OTG_HS_HCTSIZ_PKTCNT) >> 19;

          if ((hhcd->hc[chnum].max_packet == pktcnt) && (xferSizePktCnt > 0U))
          {
            /* re-activate the channel when more packets are expected */
            tmpreg = USB_HS_HC(chnum)->HCCHAR;
            tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
            tmpreg |= OTG_HS_HCCHAR_CHENA;
            USB_HS_HC(chnum)->HCCHAR = tmpreg;
            hhcd->hc[chnum].toggle_in ^= 1U;
          }
        }
        else
        {
          hhcd->hc[chnum].urb_state = URB_ERROR;
        }
      }
      break;

    case GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
      break;

    case GRXSTS_PKTSTS_IN_XFER_COMP:
    case GRXSTS_PKTSTS_CH_HALTED:
    default:
      break;
  }
}

/**
  * @brief  Handle Host Port interrupt requests.
  * @param  hhcd HCD handle
  * @retval None
  */
static void HCD_HS_Port_IRQHandler(HCD_HS_HandleTypeDef *hhcd)
{
  __IO uint32_t hprt0;
  __IO uint32_t hprt0_dup;

  /* Handle Host Port Interrupts */
  hprt0 = USB_HS_HPRT0;
  hprt0_dup = USB_HS_HPRT0;

  hprt0_dup &= ~(OTG_HS_HPRT_PENA | OTG_HS_HPRT_PCDET | \
                 OTG_HS_HPRT_PENCHNG | OTG_HS_HPRT_POCCHNG);

  /* Check whether Port Connect detected */
  if ((hprt0 & OTG_HS_HPRT_PCDET) == OTG_HS_HPRT_PCDET)
  {
    if ((hprt0 & OTG_HS_HPRT_PCSTS) == OTG_HS_HPRT_PCSTS)
    {

      HCD_HS_Connect_Callback(hhcd);
    }
    hprt0_dup |= OTG_HS_HPRT_PCDET;
  }

  /* Check whether Port Enable Changed */
  if ((hprt0 & OTG_HS_HPRT_PENCHNG) == OTG_HS_HPRT_PENCHNG)
  {
    hprt0_dup |= OTG_HS_HPRT_PENCHNG;

    if ((hprt0 & OTG_HS_HPRT_PENA) == OTG_HS_HPRT_PENA)
    {
      if((hprt0 & OTG_HS_HPRT_PSPD) == (HPRT0_PRTSPD_HIGH_SPEED<<17))
      {
        USB_HS_HOST->HFIR = 0x1D4C;//HFIR_60_MHZ;
      }
      HCD_HS_PortEnabled_Callback(hhcd);
    }
    else
    {

      HCD_HS_PortDisabled_Callback(hhcd);
    }
  }

  /* Check for an overcurrent */
  if ((hprt0 & OTG_HS_HPRT_POCCHNG) == OTG_HS_HPRT_POCCHNG)
  {
    hprt0_dup |= OTG_HS_HPRT_POCCHNG;
  }

  /* Clear Port Interrupts */
  USB_HS_HPRT0 = hprt0_dup;
}

/**
  * @}
  */


#endif /* defined (USB_OTG_HS) */
#endif /* HCD_MODULE_ENABLED */

