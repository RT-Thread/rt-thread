/**
  ******************************************************************************
  * @file    			ft32f4xx_hcd_fs.c
  * @author  			FMD XA
  * @brief   			This file provides firmware functions to manage the following 
  *          			functionalities of the USB Peripheral Controller:
  *           		+ Initialization/de-initialization functions
  *           		+ Peripheral Control functions
  *           		+ Peripheral State functions
  * @version 			V1.0.0           
  * @data		 			2025-05-28
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
  [..]
    (#)Declare a HCD_FS_HandleTypeDef handle structure, for example:
       HCD_FS_HandleTypeDef  hhcd;

    (#)Fill parameters of Init structure in HCD handle

    (#)Call HCD_FS_Init() API to initialize the HCD peripheral (Core, Host core, ...)

    (#)Initialize the HCD low level resources through the HCD_FS_MspInit() API:
        (##) Enable the HCD/USB Low Level interface clock using the following macros
        (##) Initialize the related GPIO clocks
        (##) Configure HCD pin-out
        (##) Configure HCD NVIC interrupt

    (#)Associate the Upper USB Host stack to the HCD Driver:
        (##) hhcd.pData = phost;

    (#)Enable HCD transmission and reception:
        (##) HCD_FS_Start();

  @endverbatim
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "ft32f4xx_hcd_fs.h"


#ifdef HCD_FS_MODULE_ENABLED
#if defined (USB_OTG_FS)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void HCD_FS_EP0_IRQHandler(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num);
static void HCD_FS_RXEP_IRQHandler(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num, uint8_t epnum);
static void HCD_FS_TXEP_IRQHandler(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num, uint8_t epnum);

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Initialize the host driver.
  * @param  hhcd HCD handle
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef HCD_FS_Init(HCD_FS_HandleTypeDef *hhcd)
{

  /* Check the HCD handle allocation */
  if (hhcd == NULL)
  {
    return USB_FS_ERROR;
  }

  if (hhcd->State == HCD_FS_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hhcd->Lock = USB_FS_UNLOCKED;


    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HCD_FS_MspInit(hhcd);
  }

  hhcd->State = HCD_FS_STATE_BUSY;

  /* Disable the Interrupts */
  USB_FS_SetUSBInt(0U);

  /* Init the Core (common init.) */
  if (USB_FS_CoreInit() != USB_FS_OK)
  {
    hhcd->State = HCD_FS_STATE_ERROR;
    return USB_FS_ERROR;
  }

  /* Init Host */
  if (USB_FS_HostInit(hhcd->Init) != USB_FS_OK)
  {
    hhcd->State = HCD_FS_STATE_ERROR;
    return USB_FS_ERROR;
  }

  hhcd->State = HCD_FS_STATE_READY;
  hhcd->cur_ep = 0U;

  return USB_FS_OK;
}

/**
  * @brief  Initialize a host endpoint.
  * @param  hhcd HCD handle
  * @param  epnum Endpoint number.
  *          This parameter can be a value from 1 to 15
  * @param  dev_address Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed Current device speed.
  *          This parameter can be one of these values:
  *            HCD_DEVICE_SPEED_FULL: Full speed mode,
  *            HCD_DEVICE_SPEED_LOW: Low speed mode
  * @param  ep_type Endpoint Type.
  *          This parameter can be one of these values:
  *            EP_TYPE_CTRL: Control type,
  *            EP_TYPE_ISOC: Isochronous type,
  *            EP_TYPE_BULK: Bulk type,
  *            EP_TYPE_INTR: Interrupt type
  * @param  mps Max Packet Size.
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef HCD_FS_EP_Init(HCD_FS_HandleTypeDef *hhcd,
                                    uint8_t ep_num,
                                    uint8_t epnum,
                                    uint8_t dev_address,
                                    uint8_t speed,
                                    uint8_t ep_type,
                                    uint16_t mps)
{
  USB_FS_StatusTypeDef status;
  uint32_t HostCoreSpeed;
  uint8_t ep_dir;
  uint8_t interval;

  __USB_FS_LOCK(hhcd);
  hhcd->cur_ep = ep_num;

  hhcd->ep[ep_num].dev_addr = dev_address;
  hhcd->ep[ep_num].ep_type = ep_type;
  hhcd->ep[ep_num].ep_num = ep_num;
  hhcd->ep[ep_num].epnum = epnum & 0xFU;

  if ((epnum & 0x80U) == 0x80U)
  {
    hhcd->ep[ep_num].ep_is_in = 1U;
  }
  else
  {
    hhcd->ep[ep_num].ep_is_in = 0U;
  }

  ep_dir = hhcd->ep[ep_num].ep_is_in;
  interval = hhcd->ep[ep_num].interval;
  HostCoreSpeed = USB_FS_GetSpeed();

  hhcd->ep[ep_num].speed = speed;
  hhcd->ep[ep_num].max_packet = (uint16_t)mps;

  status = USB_FS_HEP_Init(epnum,
                           dev_address,
                           ep_type,
                           interval,
                           mps);
  __USB_FS_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  DeInitialize the host driver.
  * @param  hhcd HCD handle
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef HCD_FS_DeInit(HCD_FS_HandleTypeDef *hhcd)
{
  /* Check the HCD handle allocation */
  if (hhcd == NULL)
  {
    return USB_FS_ERROR;
  }

  hhcd->State = HCD_FS_STATE_BUSY;

  USB_FS_SetUSBInt(0U);

  hhcd->State = HCD_FS_STATE_RESET;
  hhcd->cur_ep = 0U;

  /* DeInit the low level hardware: CLOCK, NVIC.*/
  HCD_FS_MspDeInit(hhcd);

  return USB_FS_OK;
}

/**
  * @brief  Initialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_MspInit(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_MspInit could be implemented in the user file
   */


}

/**
  * @brief  DeInitialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_MspDeInit(HCD_FS_HandleTypeDef *hhcd)
{
   /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_MspDeInit could be implemented in the user file
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
  * @param  ep_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  epnum endpoint number
  * @param  direction endpoint number.
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
  */

void HCD_FS_EP_SubmitRequest(HCD_FS_HandleTypeDef *hhcd,
                             uint8_t ep_num, uint8_t direction,
                             uint8_t ep_type, uint8_t token,
                             uint8_t *pbuff, uint16_t length,
                             uint8_t ctl_state)
{
  hhcd->cur_ep = ep_num;
  hhcd->ep[ep_num].ep_is_in = direction;
  hhcd->ep[ep_num].ep_type  = ep_type;

  if (token == 0U)
  {
    hhcd->ep[ep_num].data_pid = EP_PID_SETUP;
  }
  else
  {
    hhcd->ep[ep_num].data_pid = EP_PID_DATA1;
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
            hhcd->ep[ep_num].toggle_out = 1U;
          }
          /* Set the Data Toggle bit as per the Flag */
          if (hhcd->ep[ep_num].toggle_out == 0U)
          {
            /* Put the PID 0 */
            hhcd->ep[ep_num].data_pid = EP_PID_DATA0;
          }
          else
          {
            /* Put the PID 1 */
            hhcd->ep[ep_num].data_pid = EP_PID_DATA1;
          }
        }
        else
        {
          /*...*/
        }
      }
      break;

    case EP_TYPE_BULK:
      if (direction == 0U)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->ep[ep_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->ep[ep_num].data_pid = EP_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->ep[ep_num].data_pid = EP_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->ep[ep_num].toggle_in == 0U)
        {
          hhcd->ep[ep_num].data_pid = EP_PID_DATA0;
        }
        else
        {
          hhcd->ep[ep_num].data_pid = EP_PID_DATA1;
        }
      }
      break;

    case EP_TYPE_INTR:
      if (direction == 0U)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->ep[ep_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->ep[ep_num].data_pid = EP_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->ep[ep_num].data_pid = EP_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->ep[ep_num].toggle_in == 0U)
        {
          hhcd->ep[ep_num].data_pid = EP_PID_DATA0;
        }
        else
        {
          hhcd->ep[ep_num].data_pid = EP_PID_DATA1;
        }
      }
      break;

    case EP_TYPE_ISOC:
      hhcd->ep[ep_num].data_pid = EP_PID_DATA0;
      break;

    default:
      break;
  }

  hhcd->ep[ep_num].xfer_buff = pbuff;
  hhcd->ep[ep_num].xfer_len  = length;
  hhcd->ep[ep_num].XferSize = 0U;
  hhcd->ep[ep_num].urb_state = URB_IDLE;
  hhcd->ep[ep_num].xfer_count = 0U;
  hhcd->ep[ep_num].ep_num = ep_num;
  hhcd->ep[ep_num].state = EP_IDLE;
  if (ep_num <= 1U)
  {
    USB_FS_HEP0_StartXfer(&hhcd->ep[ep_num], ctl_state);
  }
  else
  {
    USB_FS_HEP_StartXfer(&hhcd->ep[ep_num]);
  }
}



//void HCD_FS_ResetCore(HCD_FS_CoreTypeDef  *cP, uint8_t state)
//{
//  HCD_FS_EPTypeDef  *eP;
//  HCD_FS_CoreTypeDef  *cP;
//  
//  cP->Resetting = 1U;
//  cP->OTGState = 0U;
//
//  /* Clear all pending Device Interrupts */
//  USB_FS_ClrEPInt(void);
//  USB_FS->INTRTX1E = 0U;
//  USB_FS->INTRRX1E = 0U;
//
//  USB_FS_ClrUSBInt(void);
//  USB_FS->INTRUSBE = 0U;
//
//  USB_FS_SetAddress(0U); /* clear host address reg */
//
//  USB_FS_RstEP0Regs(void);
//  for (i = 0; i < cP->NumEPDefs; i++)
//  {
//    eP = cP->EPA + i;
//    USB_FS_RstEPRegs(eP->BltEP);
//    HCD_FS_RstEPVars(eP);
//  }
//  USB_FS_SetUSBInt((~OTG_FS_INTRUSBE_SOFINTE));
//  USB_FS_SetEPInt(cP->IntEMask);
//  USB_FS_ClrUSBInt(void);
//  USB_FS_ClrEPInt(void);
//
//
//DBGVAR(DRCDBG_ENUM, "\n\r*ES*=", TRACE_B(state));
//    eP = cP->EPA;
////    MGC_SWOP_Setup(&cP->EP0Setup);  /* order bytes for USB output */
//    cP->EP0State = state;
//    if  (!USB_Submit_URB(cP->EP0URB))   /* 0 on return is good to go */
//        return;
//    MGC_Reset_DRC_Core(CRST_ENUM_FAILED, cP->CoreID);/* endpoints get reset*/
//    return;
//}
//
//
//
///*
// *  MGC_Reset_EP_IO_Vars used to reset the soft I/O state variables for a
// *  DRC endpoint object.
// */
//void HCD_FS_RstEPVars(HCD_FS_EPTypeDef *eP)
//{
//  eP->IOState = 0;        /* TX, no status phase is default */
//
//  if(eP->BltEP)
//  {
//    eP->URBP = (struct urb *)NULL;
//  }
//  eP->MaxEPSize = eP->FIFOSize;   /* until negotiated differently */
//  eP->FifoRemain = 0;
//  eP->BytesRequested = 0;
//  eP->BytesProcessed = 0;
//  eP->DRCInterval = 0;
//  eP->intr_flag = 0;
//  eP->TgtEP = 0;
//  eP->Allocated = 0;         
//  eP->LastPacket = 0;
//  eP->URBRestart = 0;
//  eP->Halted = 0;
//
//}   /* MGC_Reset_EP_IO_Vars */




/**
  * @brief  Handle HCD interrupt request.
  * @param  hhcd HCD handle
  * @retval None
  */
void HCD_FS_IRQHandler(HCD_FS_HandleTypeDef *hhcd)
{
  uint32_t i;
  uint8_t  tx_int;
  uint8_t  rx_int;
  uint32_t reg_int;

  reg_int = USB_FS_ReadInterrupts();

  tx_int = ((reg_int >> 8) & 0xFU);
  rx_int = ((reg_int >> 16) & 0xFU);

  /* Ensure that we are in host mode */
  if ((USB_FS_GetMode() & USB_OTG_MODE_HOST) == USB_OTG_MODE_HOST)
  {
    /* Avoid spurious interrupt */
    if (reg_int == 0U)
    {
      return;
    }

    /* Handle vbus error Interrupts */
    if ((reg_int & OTG_FS_INTRUSB_VERRINT) == OTG_FS_INTRUSB_VERRINT)
    {
      HCD_FS_VBusErr_Callback(hhcd);
    }

    /* Handle session request Interrupts */
    if ((reg_int & OTG_FS_INTRUSB_SREQINT) == OTG_FS_INTRUSB_SREQINT)
    {
      HCD_FS_Session_Callback(hhcd);
    }

    /* Handle Host Disconnect Interrupts */
    if ((reg_int & OTG_FS_INTRUSB_DISCINT) == OTG_FS_INTRUSB_DISCINT)
    {
      /* Handle Host Port Disconnect Interrupt */
      HCD_FS_Disconnect_Callback(hhcd);
    }

    /* Handle Host Connect Interrupts */
    if ((reg_int & OTG_FS_INTRUSB_CONNINT) == OTG_FS_INTRUSB_CONNINT)
    {
      /* Handle Host Port Connect Interrupt */
      HCD_FS_Connect_Callback(hhcd);
    }

    /* Handle Host SOF Interrupt */
    if ((reg_int & OTG_FS_INTRUSB_SOFINT) == OTG_FS_INTRUSB_SOFINT)
    {
      HCD_FS_SOF_Callback(hhcd);
    }
    /* Handle Host babble Interrupt */
    if ((reg_int & OTG_FS_INTRUSB_BABBINT) == OTG_FS_INTRUSB_BABBINT)
    {
      HCD_FS_Babble_Callback(hhcd);
    }
    /* Handle resume Interrupt */
    if ((reg_int & OTG_FS_INTRUSB_RESINT) == OTG_FS_INTRUSB_RESINT)
    {
      HCD_FS_Resume_Callback(hhcd);
    }

    if ((tx_int & OTG_FS_INTRTX1_EP0INF) == OTG_FS_INTRTX1_EP0INF)
    {
      (void)USB_FS_IndexSel(0U);
      HCD_FS_EP0_IRQHandler(hhcd, hhcd->cur_ep);
    }

    /* Handle Tx endpoint Interrupt */
    for (i = 1U; i < hhcd->Init.endpoints; i++)
    {
      if (((tx_int >> i) & 0x01U) != 0U)
      {
        (void)USB_FS_IndexSel((uint8_t)i);
        HCD_FS_TXEP_IRQHandler(hhcd, hhcd->cur_ep, (uint8_t)i);
      }
    }

    /* Handle Rx endpoint Interrupt */
    for (i = 1U; i < hhcd->Init.endpoints; i++)
    {
      if (((rx_int >> i) & 0x01U) != 0U)
      {
        (void)USB_FS_IndexSel((uint8_t)i);
        HCD_FS_RXEP_IRQHandler(hhcd, hhcd->cur_ep, (uint8_t)i);
      }
    }
  }
}


/**
  * @brief  Handles HCD Wakeup interrupt request.
  * @param  hhcd HCD handle
  * @retval status
  */
void HCD_FS_WKUP_IRQHandler(HCD_FS_HandleTypeDef *hhcd)
{
  UNUSED(hhcd);
}


/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_SOF_Callback(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_SOF_Callback could be implemented in the user file
   */
}

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_VBusErr_Callback(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_SOF_Callback could be implemented in the user file
   */
}

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_Session_Callback(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_SOF_Callback could be implemented in the user file
   */
}

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_Babble_Callback(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_SOF_Callback could be implemented in the user file
   */
}

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_Resume_Callback(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_SOF_Callback could be implemented in the user file
   */
}


/**
  * @brief Connection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_Connect_Callback(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_Connect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void __attribute__((weak)) HCD_FS_Disconnect_Callback(HCD_FS_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_Disconnect_Callback could be implemented in the user file
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
  *            URB_ERROR/
  *            URB_STALL/
  * @retval None
  */
void __attribute__((weak)) HCD_FS_EP_NotifyURBChange_Callback(HCD_FS_HandleTypeDef *hhcd, uint8_t epnum, HCD_FS_URBStateTypeDef urb_state)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);
  UNUSED(epnum);
  UNUSED(urb_state);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HCD_FS_HC_NotifyURBChange_Callback could be implemented in the user file
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
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef HCD_FS_Start(HCD_FS_HandleTypeDef *hhcd)
{
  __USB_FS_LOCK(hhcd);
  /* Enable port power */
  USB_FS_DrvSess(1U);

  /* Enable connect interrupt */
  USB_FS_SetUSBInt(OTG_FS_INTRUSBE_CONNINTE | OTG_FS_INTRUSBE_SOFINTE | OTG_FS_INTRUSBE_BABBINTE | OTG_FS_INTRUSBE_DISCINTE | OTG_FS_INTRUSBE_RESINTE);
  __USB_FS_UNLOCK(hhcd);

  return USB_FS_OK;
}

/**
  * @brief  Stop the host driver.
  * @param  hhcd HCD handle
  * @retval USB_FS status
  */

USB_FS_StatusTypeDef HCD_FS_Stop(HCD_FS_HandleTypeDef *hhcd)
{
  __USB_FS_LOCK(hhcd);
  USB_FS_DrvSess(0U);
  __USB_FS_UNLOCK(hhcd);

  return USB_FS_OK;
}

/**
  * @brief  Reset the host port.
  * @param  hhcd HCD handle
  * @retval none
  */
void HCD_FS_ResetPort(void)
{
  USB_FS_ResetPort();
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
HCD_FS_StateTypeDef HCD_FS_GetState(HCD_FS_HandleTypeDef *hhcd)
{
  return hhcd->State;
}

/**
  * @brief  Return  URB state for a channel.
  * @param  hhcd HCD handle
  * @param  epnum endpoint number.
  *         This parameter can be a value from 1 to 15
  * @retval URB state.
  *         This parameter can be one of these values:
  *         URB_IDLE/
  *         URB_DONE/
  *         URB_NOTREADY/
  *         URB_ERROR/
  *         URB_STALL
  */
HCD_FS_URBStateTypeDef HCD_FS_EP_GetURBState(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num)
{
  return hhcd->ep[ep_num].urb_state;
}


/**
  * @brief  Return the last host transfer size.
  * @param  hhcd HCD handle
  * @param  epnum endpoint number.
  *         This parameter can be a value from 1 to 15
  * @retval last transfer size in byte
  */
uint32_t HCD_FS_EP_GetXferCount(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num)
{
  return hhcd->ep[ep_num].xfer_count;
}

/**
  * @brief  Return the current endpoint pipe.
  * @param  hhcd HCD handle
  * @param  epnum endpoint number.
  *         This parameter can be a value from 1 to 15
  * @retval host transfer pieps
  */
uint32_t HCD_FS_GetCurrEp(HCD_FS_HandleTypeDef *hhcd)
{
  return hhcd->cur_ep;
}

/**
  * @brief  Return the Host Channel state.
  * @param  hhcd HCD handle
  * @param  epnum endpoint number.
  *         This parameter can be a value from 1 to 15
  * @retval host endpoint state
  *         This parameter can be one of these values:
  *         EP_IDLE/
  *         EP_XFRC/
  *         EP_HALTED/
  *         EP_NAK/
  *         EP_STALL/
  *         EP_XACTERR/
  *         EP_BBLERR/
  *         EP_DATATGLERR
  */
HCD_FS_EPStateTypeDef  HCD_FS_EP_GetState(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num)
{
  return hhcd->ep[ep_num].state;
}

/**
  * @brief  Return the current Host frame number.
  * @param  hhcd HCD handle
  * @retval Current Host frame number
  */
uint32_t HCD_FS_GetCurrentFrame(void)
{
  return (USB_FS_GetCurrentFrame());
}

/**
  * @brief  Return the Host enumeration speed.
  * @param  hhcd HCD handle
  * @retval Enumeration speed
  */
uint32_t HCD_FS_GetCurrentSpeed(void)
{
  return (USB_FS_GetSpeed());
}


/**
  * @}
  */

/** @addtogroup HCD_Private_Functions
  * @{
  */

/**
  * @brief  Handle Host endpoint0 interrupt requests.
  * @param  hhcd HCD handle
  * @param  epnum endpoint number.
  *         This parameter can be 0
  * @retval none
  */
static void HCD_FS_EP0_IRQHandler(HCD_FS_HandleTypeDef *hhcd, uint8_t epnum)
{
  uint8_t tmpreg;
  uint8_t bytecount;

  tmpreg = USB_FS->CSR0;

  if ((tmpreg & OTG_FS_CSR0_NAKTMO) == OTG_FS_CSR0_NAKTMO)
  {
    hhcd->ep[epnum].ErrCnt = 0U;
    hhcd->ep[epnum].state  = EP_NAK;
    if (hhcd->ep[epnum].ep_is_in == 0U)
    {
      USB_FS_FlushEp0Fifo();   /* flush fifo to halt transcation*/
    }
    else
    {
      USB_FS->CSR0 &= (~OTG_FS_CSR0_REQPKT); /* clear reqpkt halt transcation */
    }
    USB_FS->CSR0 &= (~OTG_FS_CSR0_NAKTMO);
  }
  else if ((tmpreg & OTG_FS_CSR0_RXSTALL) == OTG_FS_CSR0_RXSTALL)
  {
    hhcd->ep[epnum].state = EP_STALL;
    hhcd->ep[epnum].urb_state = URB_STALL;
    if ( hhcd->ep[epnum].ep_is_in == 0U)
    {
      USB_FS_FlushEp0Fifo();   /* flush fifo to halt transcation*/
    }
    else
    {
      USB_FS->CSR0 &= (~OTG_FS_CSR0_REQPKT); /* clear reqpkt halt transcation */
    }
    USB_FS->CSR0 &= (~OTG_FS_CSR0_RXSTALL);
    HCD_FS_EP_NotifyURBChange_Callback(hhcd, epnum, hhcd->ep[epnum].urb_state);
  }
  else if ((tmpreg & OTG_FS_CSR0_ERR) == OTG_FS_CSR0_ERR)
  {
    hhcd->ep[epnum].state = EP_XACTERR;
    hhcd->ep[epnum].urb_state = URB_ERROR;
    if ( hhcd->ep[epnum].ep_is_in == 0U)
    {
      USB_FS_FlushEp0Fifo();   /* flush fifo to halt transcation*/
    }
    else
    {
      USB_FS->CSR0 &= (~OTG_FS_CSR0_REQPKT); /* clear reqpkt halt transcation */
    }
    USB_FS->CSR0 &= (~OTG_FS_CSR0_RXSTALL);
    HCD_FS_EP_NotifyURBChange_Callback(hhcd, epnum, hhcd->ep[epnum].urb_state);
  }

  else if ((tmpreg & OTG_FS_CSR0_RXPKTRDY) == OTG_FS_CSR0_RXPKTRDY)
  {
    bytecount = USB_FS_Read_Count0();
    hhcd->ep[epnum].toggle_in ^= 1U;
    hhcd->ep[epnum].xfer_count = bytecount;
    hhcd->ep[epnum].XferSize = hhcd->ep[epnum].XferSize + bytecount ;
    hhcd->ep[epnum].ErrCnt = 0U;
    if ((bytecount > 0U) && (hhcd->ep[epnum].xfer_buff != (void *)0))
    {
      USB_FS_FIFORead(hhcd->ep[epnum].xfer_buff, 0U, bytecount);
    }
    if (bytecount == 0U)
    {
      hhcd->ep[epnum].state = EP_XFRC;
      hhcd->ep[epnum].urb_state = URB_DONE;
    }
    else if (bytecount < 0x40)
    {
      hhcd->ep[epnum].state = EP_XFRC;
      hhcd->ep[epnum].urb_state = URB_DONE;
    }
    else if (hhcd->ep[epnum].XferSize == hhcd->ep[epnum].xfer_len)
    {
      // if (hhcd->ep[epnum].xfer_len >= 0x40U)
      if (bytecount == 0x40U)
      {
         USB_FS_HEP0_StartXfer(&hhcd->ep[epnum], CTRL_DATA);
      }
      else
      {
        hhcd->ep[epnum].state = EP_XFRC;
        hhcd->ep[epnum].urb_state = URB_DONE;
      }
    }
    else
    {
      USB_FS_HEP0_StartXfer(&hhcd->ep[epnum], CTRL_DATA);
    }
    HCD_FS_EP_NotifyURBChange_Callback(hhcd, epnum, hhcd->ep[epnum].urb_state);
  }
  else
  {
    hhcd->ep[epnum].ErrCnt = 0U;
    hhcd->ep[epnum].toggle_out ^= 1U;
    hhcd->ep[epnum].state = EP_XFRC;
    hhcd->ep[epnum].urb_state = URB_DONE;
    HCD_FS_EP_NotifyURBChange_Callback(hhcd, epnum, hhcd->ep[epnum].urb_state);
  }
}

/**
  * @brief  Handle Host endpoint RX interrupt requests.
  * @param  hhcd HCD handle
  * @param  epnum endpoint number.
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_FS_RXEP_IRQHandler(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num, uint8_t epnum)
{
  uint8_t  tmpreg;
  uint16_t bytecount;
  uint32_t maxpacket;
  uint16_t fifo_size;

  tmpreg = USB_FS->RXCSR1;
  maxpacket = (USB_FS->RXMAXP) << 3U;

  if ((tmpreg & OTG_FS_RXCSR1_NAKTMO) == OTG_FS_RXCSR1_NAKTMO)
  {
    hhcd->ep[ep_num].ErrCnt = 0U;
    if ( hhcd->ep[epnum].ep_type == EP_TYPE_ISOC)
    {
      hhcd->ep[ep_num].state  = EP_XACTERR;
      USB_FS_FlushRxFifo(epnum);   /* flush fifo to halt transcation*/
    }
    else
    {
      hhcd->ep[ep_num].state  = EP_NAK;
    }
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_REQPKT); /* clear reqpkt halt transcation */
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_NAKTMO);
  }
  else if ((tmpreg & OTG_FS_RXCSR1_RXSTALL) == OTG_FS_RXCSR1_RXSTALL)
  {
    hhcd->ep[ep_num].state = EP_STALL;
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_REQPKT); /* clear reqpkt halt transcation */
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_RXSTALL);
  }
  else if ((tmpreg & OTG_FS_RXCSR1_ERR) == OTG_FS_RXCSR1_ERR)
  {
    hhcd->ep[ep_num].state = EP_XACTERR;
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_REQPKT); /* clear reqpkt halt transcation */
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_RXSTALL);
  }
  else if ((tmpreg & OTG_FS_RXCSR1_RXPKTRDY) == OTG_FS_RXCSR1_RXPKTRDY)
  {
    bytecount = USB_FS_Read_RxCount();
    hhcd->ep[ep_num].state = EP_XFRC;
    hhcd->ep[ep_num].ErrCnt = 0U;
    hhcd->ep[ep_num].toggle_in ^= 1U;
    hhcd->ep[ep_num].xfer_count = bytecount;
    if ((bytecount > 0U) && (hhcd->ep[ep_num].xfer_buff != (void *)0))
    {
      USB_FS_FIFORead(hhcd->ep[ep_num].xfer_buff, epnum, bytecount);
    }
    if (bytecount == 0U)
    {
      hhcd->ep[ep_num].state = EP_XFRC;
      hhcd->ep[ep_num].urb_state = URB_DONE;
      HCD_FS_EP_NotifyURBChange_Callback(hhcd, ep_num, hhcd->ep[ep_num].urb_state);
    }
    else if (hhcd->ep[ep_num].XferSize == hhcd->ep[ep_num].xfer_len)
    {
      if (bytecount == maxpacket)
      {
         USB_FS->RXCSR1 |= OTG_FS_RXCSR1_REQPKT;
      }
      else
      {
        hhcd->ep[ep_num].state = EP_XFRC;
        hhcd->ep[ep_num].urb_state = URB_DONE;
        HCD_FS_EP_NotifyURBChange_Callback(hhcd, epnum, hhcd->ep[ep_num].urb_state);
      }
    }
    else
    {
      hhcd->ep[ep_num].xfer_len = hhcd->ep[ep_num].xfer_len - maxpacket;
      hhcd->ep[ep_num].toggle_out ^= 1U;
      USB_FS_HEP_StartXfer(&hhcd->ep[epnum]);
    }
    USB_FS->RXCSR1 &= ~OTG_FS_RXCSR1_RXPKTRDY;
  }
  else
  {
    /*...*/
  }
}

/**
  * @brief  Handle Host endpoint TX interrupt requests.
  * @param  hhcd HCD handle
  * @param  epnum endpoint number.
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_FS_TXEP_IRQHandler(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num, uint8_t epnum)
{
  uint8_t tmpreg;
  uint32_t maxpacket;
  uint16_t fifo_size;

  tmpreg = USB_FS->TXCSR1;
  maxpacket = (USB_FS->TXMAXP) << 3U;

  if ((tmpreg & OTG_FS_TXCSR1_NAKTMO) == OTG_FS_TXCSR1_NAKTMO)
  {
    hhcd->ep[ep_num].ErrCnt = 0U;
    hhcd->ep[ep_num].state  = EP_NAK;
    (void)USB_FS_FlushTxFifo(epnum);
    (void)USB_FS_FlushTxFifo(epnum); /* flush txfifo to halt transcation */
    USB_FS->TXCSR1 &= (~OTG_FS_TXCSR1_NAKTMO);
  }
  else if ((tmpreg & OTG_FS_TXCSR1_RXSTALL) == OTG_FS_TXCSR1_RXSTALL)
  {
    hhcd->ep[ep_num].state = EP_STALL;
    (void)USB_FS_FlushTxFifo(epnum);
    (void)USB_FS_FlushTxFifo(epnum); /* flush txfifo to halt transcation */
    USB_FS->TXCSR1 &= (~OTG_FS_TXCSR1_RXSTALL);
  }
  else if ((tmpreg & OTG_FS_TXCSR1_ERR) == OTG_FS_TXCSR1_ERR)
  {
    hhcd->ep[ep_num].state = EP_XACTERR;
    (void)USB_FS_FlushTxFifo(epnum);
    (void)USB_FS_FlushTxFifo(epnum); /* flush txfifo to halt transcation */
    USB_FS->TXCSR1 &= (~OTG_FS_TXCSR1_RXSTALL);
  }
  else
  {
    hhcd->ep[ep_num].ErrCnt = 0U;
    if (hhcd->ep[ep_num].xfer_len == hhcd->ep[ep_num].XferSize)
    {
      if (hhcd->ep[ep_num].xfer_len == maxpacket)
      {
        hhcd->ep[ep_num].toggle_out ^= 1U;
        USB_FS->TXCSR1 = OTG_FS_TXCSR1_TXPKTRDY;
      }
      else
      {
        hhcd->ep[ep_num].state = EP_XFRC;
        hhcd->ep[ep_num].toggle_out ^= 1U;
        hhcd->ep[ep_num].urb_state = URB_DONE;
        HCD_FS_EP_NotifyURBChange_Callback(hhcd, ep_num, hhcd->ep[ep_num].urb_state);
      }
    }
    else
    {
      hhcd->ep[ep_num].xfer_len = hhcd->ep[ep_num].xfer_len - maxpacket;
      hhcd->ep[ep_num].toggle_out ^= 1U;
      USB_FS_HEP_StartXfer(&hhcd->ep[epnum]);
    }
  }
}

/**
  * @}
  */


#endif /* defined (USB_OTG_FS) */
#endif /* HCD_FS_MODULE_ENABLED */

