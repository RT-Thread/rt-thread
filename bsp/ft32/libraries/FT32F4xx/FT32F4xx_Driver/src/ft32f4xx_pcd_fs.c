/**
  ******************************************************************************
  * @file    			ft32f4xx_pcd_fs.c
  * @author  			FMD XA
  * @brief   			This file provides firmware functions to manage the following 
  *          			functionalities of the USB Peripheral Controller:
  *           		+ Initialization/de-initialization functions
  *           		+ Peripheral Control functions
  *           		+ Peripheral State functions
  * @version 			V1.0.0           
  * @data		 			2025-05-30
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
  [..]
    (#)Declare a PCD_FS_HandleTypeDef handle structure, for example:
       PCD_FS_HandleTypeDef  hpcd;

    (#)Fill parameters of Init structure in PCD handle

    (#)Call PCD_FS_Init() API to initialize the PCD peripheral (Core, Host core, ...)

    (#)Initialize the PCD low level resources through the PCD_FS_MspInit() API:
        (##) Enable the PCD/USB Low Level interface clock using the following macros
        (##) Initialize the related GPIO clocks
        (##) Configure PCD NVIC interrupt

    (#)Associate the Upper USB Host stack to the PCD Driver:
        (##) hpcd.pData = pdev;

    (#)Enable PCD transmission and reception:
        (##) PCD_FS_Start();

  @endverbatim
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "ft32f4xx_pcd_fs.h"
#include "ft32f4xx_rcc.h"
#include "usbd_core.h"

/** @addtogroup FT32F4xx_DRIVER
  * @{
  */

#ifdef PCD_FS_MODULE_ENABLED
#if defined (USB_OTG_FS)
/** @defgroup PCD_FS PCD
  * @brief PCD FS module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup PCD_FS_Private_Macros PCD Private Functions
  * @{
  */
#define PCD_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PCD_MAX(a,b) (((a) > (b)) ? (a) : (b))
/**
  * @{
  */

/** @defgroup PCD_FS_Private_Functions PCD Private Functions
  * @{
  */

static USB_FS_StatusTypeDef PCD_FS_WriteEmptyTxFifo(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum);
static void PCD_FS_EP_OutXferComplete_int(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum);
static void PCD_FS_EP_OutSetupPacket_int(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum);
/**
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PCD_FS_Exported_Functions PCD Exported Functions
  * @{
  */

/** @defgroup PCD_FS_Exported_Functions_Group1 Initialization and de-initialization functions
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
  * @brief  Initializes the PCD according to the specified
  *         parameters in the PCD_InitTypeDef and initialize the associated handle.
  * @param  hpcd PCD handle
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_Init(PCD_FS_HandleTypeDef *hpcd)
{

  uint8_t i;

  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return USB_FS_ERROR;
  }

  if (hpcd->State == PCD_FS_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hpcd->Lock = USB_FS_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    PCD_FS_MspInit(hpcd);
  }

  hpcd->State = PCD_FS_STATE_BUSY;

  /* Disable the Interrupts */
  USB_FS_SetUSBInt(0U);
	USB_FS_SetEPInt(0U);
  /*Init the Core (common init.) */
//  if (USB_FS_CoreInit() != USB_FS_OK)
//  {
//    hpcd->State = PCD_FS_STATE_ERROR;
//    return USB_FS_ERROR;
//  }

  /* Init endpoints structures */
  for (i = 0U; i < hpcd->Init.endpoints; i++)
  {
    /* Init ep structure */
    hpcd->IN_ep[i].is_in = 1U;
    hpcd->IN_ep[i].num = i;
    hpcd->IN_ep[i].tx_fifo_num = i;
    /* Control until ep is activated */
    hpcd->IN_ep[i].type = EP_TYPE_CTRL;
    hpcd->IN_ep[i].maxpacket = 0U;
    hpcd->IN_ep[i].xfer_buff = 0U;
    hpcd->IN_ep[i].xfer_len = 0U;
  }

  for (i = 0U; i < hpcd->Init.endpoints; i++)
  {
    hpcd->OUT_ep[i].is_in = 0U;
    hpcd->OUT_ep[i].num = i;
    /* Control until ep is activated */
    hpcd->OUT_ep[i].type = EP_TYPE_CTRL;
    hpcd->OUT_ep[i].maxpacket = 0U;
    hpcd->OUT_ep[i].xfer_buff = 0U;
    hpcd->OUT_ep[i].xfer_len = 0U;
  }

  /* Init Device */
  if (USB_FS_DevInit(hpcd->Init) != USB_FS_OK)
  {
    hpcd->State = PCD_FS_STATE_ERROR;
    return USB_FS_ERROR;
  }

  hpcd->USB_Address = 0U;
  hpcd->State = PCD_FS_STATE_READY;
  hpcd->ctrl_state = CTRL_SETUP_P;
//  USB_FS_DrvSess(0U);

  return USB_FS_OK;
}

/**
  * @brief  DeInitializes the PCD peripheral.
  * @param  hpcd PCD handle
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_DeInit(PCD_FS_HandleTypeDef *hpcd)
{
  uint32_t i;
  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return USB_FS_ERROR;
  }

  hpcd->State = PCD_FS_STATE_BUSY;

  /* Stop Device */
  USB_FS_SetUSBInt(0U);
  USB_FS_SetEPInt(0U);

  if (USB_FS_RstEP0Regs() != USB_FS_OK)
  {
    return USB_FS_ERROR;
  }
  for (i = 1U; i < hpcd->Init.endpoints; i++)
  {
    if (USB_FS_RstEPRegs(i) != USB_FS_OK)
    {
      return USB_FS_ERROR;
    }
  }
  /* DeInit the low level hardware: CLOCK, NVIC.*/
  PCD_FS_MspDeInit(hpcd);

  hpcd->State = PCD_FS_STATE_RESET;

  return USB_FS_OK;
}

/**
  * @brief  set iso mode.
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_FS_SetISO(uint8_t ep_num, uint8_t state)
{
  USB_FS_IndexSel(ep_num);
  if (state != 0U)
  {
    USB_FS->TXCSR2 |= OTG_FS_TXCSR2_ISO ;
    USB_FS->RXCSR2 |= OTG_FS_RXCSR2_ISO ;
  }
  else
  {
    USB_FS->TXCSR2 &= ~OTG_FS_TXCSR2_ISO ;
    USB_FS->RXCSR2 &= ~OTG_FS_RXCSR2_ISO ;
  }
}

/**
  * @brief  set maxpacket.
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_FS_SetMaxPkt(uint8_t ep_num, uint16_t size)
{
  uint16_t maxpkt;
  maxpkt = (size + 7U) / 8U ;
  USB_FS_IndexSel(ep_num);

  USB_FS->TXMAXP = maxpkt;
  USB_FS->RXMAXP = maxpkt;
}

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_FS_MspInit(PCD_FS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_FS_MspDeInit(PCD_FS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_MspDeInit could be implemented in the user file
   */
}


/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   Data transfers functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the PCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the USB device
  * @param  hpcd PCD handle
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_Start(PCD_FS_HandleTypeDef *hpcd)
{
  __USB_FS_LOCK(hpcd);

//  USB_FS_SetUSBInt(OTG_FS_INTRUSBE_SOFINTE  | OTG_FS_INTRUSBE_RSTINTE  |
//                   OTG_FS_INTRUSBE_DISCINTE | OTG_FS_INTRUSBE_SREQINTE |
//                   OTG_FS_INTRUSBE_VERRINTE);

  USB_FS_DrvSess(1U);

  __USB_FS_UNLOCK(hpcd);

  return USB_FS_OK;
}

/**
  * @brief  Stop the USB device.
  * @param  hpcd PCD handle
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_Stop(PCD_FS_HandleTypeDef *hpcd)
{
  uint32_t i;
  __USB_FS_LOCK(hpcd);

  USB_FS_SetUSBInt(0U);

  USB_FS_DrvSess(0U);
  if (USB_FS_FlushEp0Fifo() != USB_FS_OK)
  {
    return USB_FS_ERROR;
  }
  for (i = 1U; i < hpcd->Init.endpoints; i++)
  {
    if (USB_FS_FlushTxFifo(i) != USB_FS_OK)
    {
      return USB_FS_ERROR;
    }
    if (USB_FS_FlushRxFifo(i) != USB_FS_OK)
    {
      return USB_FS_ERROR;
    }
  }
  __USB_FS_UNLOCK(hpcd);

  return USB_FS_OK;
}

#if defined (USB_OTG_FS)
/**
  * @brief  Handles PCD interrupt request.
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_FS_IRQHandler(PCD_FS_HandleTypeDef *hpcd)
{
  uint32_t i;
  uint32_t ep_intr;
  uint32_t epint;
  uint32_t epnum;
  uint32_t fifoemptymsk;
  uint32_t RegVal;
  uint32_t reg_int;
  uint32_t tx_int;
  uint32_t rx_int;
  uint8_t  reg_power;

  reg_int = USB_FS_ReadInterrupts();
  /* ensure that we are in device mode */
  if ((USB_FS_GetMode() & USB_OTG_MODE_DEVICE) == USB_OTG_MODE_DEVICE)
  {
    /* avoid spurious interrupt */
    if (reg_int == 0U)
    {
      return;
    }

    /* store current frame number */
    hpcd->FrameNumber = USB_FS_GetCurrentFrame();

    /* Handle vbus error Interrupts */
    if ((reg_int & 0xFFU) != 0U)
    {
      if ((reg_int & OTG_FS_INTRUSB_VERRINT) == OTG_FS_INTRUSB_VERRINT)
      {
        PCD_FS_VBusErrCallback(hpcd);
      }

      /* Handle session request Interrupts */
      if ((reg_int & OTG_FS_INTRUSB_SREQINT) == OTG_FS_INTRUSB_SREQINT)
      {
        PCD_FS_SessionCallback(hpcd);
      }

      /* Handle Host Disconnect Interrupts */
      if ((reg_int & OTG_FS_INTRUSB_DISCINT) == OTG_FS_INTRUSB_DISCINT)
      {
        /* Handle Host Port Disconnect Interrupt */
        PCD_FS_DisconnectCallback(hpcd);
      }

      /* Handle Host Connect Interrupts */
//      if ((reg_int & OTG_FS_INTRUSB_CONNINT) == OTG_FS_INTRUSB_CONNINT)
//      {
//        /* Handle Host Port Connect Interrupt */
//        PCD_FS_ConnectCallback(hpcd);
//      }

      /* Handle Host SOF Interrupt */
      if ((reg_int & OTG_FS_INTRUSB_SOFINT) == OTG_FS_INTRUSB_SOFINT)
      {
        PCD_FS_SOFCallback(hpcd);
      }
      /* Handle Host reset Interrupt */
      if ((reg_int & OTG_FS_INTRUSB_RSTINT) == OTG_FS_INTRUSB_RSTINT)
      {
        USB_FS->CSR0 |= (OTG_FS_CSR0_SSETUPEND | OTG_FS_CSR0_SRXPKTRDY);
        USB_FS_RstEP0Regs();
        for (i = 1U; i < hpcd->Init.endpoints; i++)
        {
          USB_FS->TXCSR1 = 0U;
          USB_FS->RXCSR1 = 0U;
          (void)USB_FS_ReadInterrupts();
          USB_FS_RstEPRegs(i);
        }

        USB_FS_SetEPInt(0x0FU);

        USB_FS_SetAddress(0U);

        PCD_FS_ResetCallback(hpcd);
      }
      /* Handle resume Interrupt */
      if ((reg_int & OTG_FS_INTRUSB_RESINT) == OTG_FS_INTRUSB_RESINT)
      {
        PCD_FS_ResumeCallback(hpcd);
      }
      /* Handle suspend Interrupt */
      if ((reg_int & OTG_FS_INTRUSB_SUSPINT) == OTG_FS_INTRUSB_SUSPINT)
      {
        reg_power = USB_FS_GetPower();
        if ((reg_power & OTG_FS_POWER_SUSPEND) != 0U)
        {
          PCD_FS_SuspendCallback(hpcd);
        }
      }
    }
    /* Handle EP0 endpoint Interrupt */
    tx_int = ((reg_int >> 8) & 0xFU);
    if ((tx_int & OTG_FS_INTRTX1_EP0INF) == OTG_FS_INTRTX1_EP0INF)
    {
      (void)USB_FS_IndexSel(0U);
      USBD_SET_ADDR(hpcd->pData);  
      PCD_FS_EP0_IRQHandler(hpcd);
    }
    
    /* Handle Tx endpoint Interrupt */
    if (((reg_int >> 8) & 0xEU) != 0U)
    {
      for (i = 1U; i < hpcd->Init.endpoints; i++)
      {
        if (((tx_int >> i) & 0x01U) != 0U)
        {
          (void)USB_FS_IndexSel((uint8_t)i);
          PCD_FS_TXEP_IRQHandler(hpcd, (uint8_t)i);
        }
      }
    }

    /* Handle Rx endpoint Interrupt */
    if (((reg_int >> 16) & 0xFU) != 0U)
    {
      rx_int = ((reg_int >> 16) & 0xFU);
      for (i = 1U; i < hpcd->Init.endpoints; i++)
      {
        if (((rx_int >> i) & 0x01U) != 0U)
        {
          (void)USB_FS_IndexSel((uint8_t)i);
          PCD_FS_RXEP_IRQHandler(hpcd, (uint8_t)i);
        }
      }
    }
  }
}

/**
  * @brief  Handles PCD Wakeup interrupt request.
  * @param  hpcd PCD handle
  * @retval none status
  */
void PCD_FS_WKUP_IRQHandler(void)
{
  /* Clear EXTI pending Bit */
  __USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG();
}
#endif /* defined (USB_OTG_FS) */


/**
  * @brief  Data OUT stage callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
//void __attribute__((weak)) PCD_FS_DataOutStageCallback(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//  UNUSED(epnum);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_DataOutStageCallback could be implemented in the user file
//   */
//}
//
///**
//  * @brief  Data IN stage callback
//  * @param  hpcd PCD handle
//  * @param  epnum endpoint number
//  * @retval None
//  */
//void __attribute__((weak)) PCD_FS_DataInStageCallback(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//  UNUSED(epnum);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_DataInStageCallback could be implemented in the user file
//   */
//}
///**
//  * @brief  Setup stage callback
//  * @param  hpcd PCD handle
//  * @retval None
//  */
//void __attribute__((weak)) PCD_FS_SetupStageCallback(PCD_FS_HandleTypeDef *hpcd)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_SetupStageCallback could be implemented in the user file
//   */
//}
//
///**
//  * @brief  USB Start Of Frame callback.
//  * @param  hpcd PCD handle
//  * @retval None
//  */
//void __attribute__((weak)) PCD_FS_SOFCallback(PCD_FS_HandleTypeDef *hpcd)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_SOFCallback could be implemented in the user file
//   */
//}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_FS_SessionCallback(PCD_FS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_SOFCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_FS_VBusErrCallback(PCD_FS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_SOFCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_FS_OVERRUNCallback(PCD_FS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_SOFCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_FS_UNDERRUNCallback(PCD_FS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_SOFCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_FS_DERRCallback(PCD_FS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_FS_SOFCallback could be implemented in the user file
   */
}
/**
  * @brief  USB Reset callback.
  * @param  hpcd PCD handle
  * @retval None
  */
//void __attribute__((weak)) PCD_FS_ResetCallback(PCD_FS_HandleTypeDef *hpcd)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_ResetCallback could be implemented in the user file
//   */
//}
//
///**
//  * @brief  Suspend event callback.
//  * @param  hpcd PCD handle
//  * @retval None
//  */
//void __attribute__((weak)) PCD_FS_SuspendCallback(PCD_FS_HandleTypeDef *hpcd)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_SuspendCallback could be implemented in the user file
//   */
//}
//
///**
//  * @brief  Resume event callback.
//  * @param  hpcd PCD handle
//  * @retval None
//  */
//void __attribute__((weak)) PCD_FS_ResumeCallback(PCD_FS_HandleTypeDef *hpcd)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_ResumeCallback could be implemented in the user file
//   */
//}
//
//
///**
//  * @brief  Connection event callback.
//  * @param  hpcd PCD handle
//  * @retval None
//  */
//void __attribute__((weak)) PCD_FS_ConnectCallback(PCD_FS_HandleTypeDef *hpcd)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_ConnectCallback could be implemented in the user file
//   */
//}
//
///**
//  * @brief  Disconnection event callback.
//  * @param  hpcd PCD handle
//  * @retval None
//  */
//void __attribute__((weak)) PCD_FS_DisconnectCallback(PCD_FS_HandleTypeDef *hpcd)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hpcd);
//
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the PCD_FS_DisconnectCallback could be implemented in the user file
//   */
//}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   management functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the PCD data
    transfers.

@endverbatim
  * @{
  */

///**
//  * @brief  Connect the USB device
//  * @param  hpcd PCD handle
//  * @retval USB_FS status
//  */
//USB_FS_StatusTypeDef PCD_FS_DevConnect(PCD_FS_HandleTypeDef *hpcd)
//{
//  __USB_FS_LOCK(hpcd);
//
//  USB_FS_DevConnect();
//  __USB_FS_UNLOCK(hpcd);
//
//  return USB_FS_OK;
//}

/**
  * @brief  Disconnect the USB device.
  * @param  hpcd PCD handle
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_DevDisconnect(PCD_FS_HandleTypeDef *hpcd)
{
  __USB_FS_LOCK(hpcd);

  USB_FS_DrvSess(0U);
  __USB_FS_UNLOCK(hpcd);

  return USB_FS_OK;
}

/**
  * @brief  Set the USB Device address.
  * @param  hpcd PCD handle
  * @param  address new device address
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_SetAddress(PCD_FS_HandleTypeDef *hpcd, uint8_t address)
{
  __USB_FS_LOCK(hpcd);
  hpcd->USB_Address = address;
  USB_FS_SetAddress(address);
  __USB_FS_UNLOCK(hpcd);

  return USB_FS_OK;
}
/**
  * @brief  Open and configure an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  ep_mps endpoint max packet size
  * @param  ep_type endpoint type
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_EP_Open(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr,
                                    uint16_t ep_mps, uint8_t ep_type)
{
  USB_FS_StatusTypeDef  ret = USB_FS_OK;
  PCD_FS_EPTypeDef *ep;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 0U;
  }

  ep->num = ep_addr & EP_ADDR_MSK;
  ep->maxpacket = ep_mps;
  ep->type = ep_type;

  if (ep->is_in != 0U)
  {
    /* Assign a Tx FIFO */
    ep->tx_fifo_num = ep->num;
  }
  /* Set initial data PID. */
  if (ep_type == EP_TYPE_BULK)
  {
    ep->data_pid_start = 0U;
  }

  __USB_FS_LOCK(hpcd);
  if (ep->num != 0U)
  {
    USB_FS_Enable_DEP(ep);
  }
  __USB_FS_UNLOCK(hpcd);

  return ret;
}

/**
  * @brief  Deactivate an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_EP_Close(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_FS_EPTypeDef *ep;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 0U;
  }
  ep->num = ep_addr & EP_ADDR_MSK;

  __USB_FS_LOCK(hpcd);
  if (USB_FS_SendStall(ep) != USB_FS_OK)
  {
    return USB_FS_ERROR;
  }
  __USB_FS_UNLOCK(hpcd);
  return USB_FS_OK;
}


/**
  * @brief  Receive an amount of data.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  pBuf pointer to the reception buffer
  * @param  len amount of data to be received
  * @retval none
  */
void PCD_FS_EP_Receive(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  PCD_FS_EPTypeDef *ep;

  ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];

  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;
  ep->xfer_len = len;
  ep->xfer_count = 0U;
  ep->is_in = 0U;
  ep->num = ep_addr & EP_ADDR_MSK;
  if (ep->num != 0U)
  {
    USB_FS_DEPStartXfer(ep);
  }
	else
	{
		USB_FS_DEP0StartXfer(ep);
	}
}

/**
  * @brief  Get Received Data Size
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval Data Size
  */
uint32_t PCD_FS_EP_GetRxCount(const PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  return hpcd->OUT_ep[ep_addr & EP_ADDR_MSK].xfer_count;
}
/**
  * @brief  Send an amount of data
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  pBuf pointer to the transmission buffer
  * @param  len amount of data to be sent
  * @retval none
  */
void PCD_FS_EP_Transmit(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  PCD_FS_EPTypeDef *ep;

  ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];

  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;
  ep->xfer_len = len;
  ep->xfer_count = 0U;
  ep->is_in = 1U;
  ep->num = ep_addr & EP_ADDR_MSK;
  ep->is_stall = 0U;

  if (ep->num != 0U)
  {
    USB_FS_DEPStartXfer(ep);
  }
  else
  {
    USB_FS_DEP0StartXfer(ep);
  }
}

/**
  * @brief  Set a STALL condition over an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_EP_SetStall(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_FS_EPTypeDef *ep;

  if (((uint32_t)ep_addr & EP_ADDR_MSK) > hpcd->Init.endpoints)
  {
    return USB_FS_ERROR;
  }

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr];
    ep->is_in = 0U;
  }

  ep->is_stall = 1U;
  ep->num = ep_addr & EP_ADDR_MSK;

  __USB_FS_LOCK(hpcd);

  USB_FS_SendStall(ep);

  if ((ep_addr & EP_ADDR_MSK) == 0U)
  {
    (void)USB_FS_DEP0StartXfer(ep);
  }

  __USB_FS_UNLOCK(hpcd);

  return USB_FS_OK;
}

/**
  * @brief  Clear a STALL condition over in an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_EP_ClrStall(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_FS_EPTypeDef *ep;

  if (((uint32_t)ep_addr & 0x0FU) > hpcd->Init.endpoints)
  {
    return USB_FS_ERROR;
  }

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 0U;
  }

  ep->is_stall = 0U;
  ep->num = ep_addr & EP_ADDR_MSK;

  __USB_FS_LOCK(hpcd);
  USB_FS_ClrStall(ep);
  __USB_FS_UNLOCK(hpcd);

  return USB_FS_OK;
}

/**
  *
  * @brief  Abort an USB EP transaction
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_EP_Abort(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  USB_FS_StatusTypeDef ret;
  PCD_FS_EPTypeDef *ep;

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
  }

  /* Stop Xfer */
  if (ep->num == 0U)
  {
    ret = USB_FS_RstEP0Regs();
  }
  else
  {
    ret = USB_FS_RstEPRegs(ep->num);
  }

  return ret;
}

/**
  * @brief  Flush an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef PCD_FS_EP_Flush(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  __USB_FS_LOCK(hpcd);

  if ((ep_addr & 0x80U) == 0x80U)
  {
    (void)USB_FS_FlushTxFifo((uint32_t)ep_addr & EP_ADDR_MSK);
  }
  else
  {
    (void)USB_FS_FlushRxFifo((uint32_t)ep_addr & EP_ADDR_MSK);
  }

  __USB_FS_UNLOCK(hpcd);

  return USB_FS_OK;
}

/**
  * @brief  Activate remote wakeup signalling
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_FS_ActivateRemoteWakeup(void)
{
  USB_FS_Activate_Resume();
}

/**
  * @brief  De-activate remote wakeup signalling.
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_FS_DeActivateRemoteWakeup(void)
{
  USB_FS_DeActivate_Resume();
}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group4 Peripheral State functions
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
  * @brief  Return the PCD handle state.
  * @param  hpcd PCD handle
  * @retval hpcd state
  */
PCD_FS_StateTypeDef PCD_FS_GetState(PCD_FS_HandleTypeDef const *hpcd)
{
  return hpcd->State;
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup PCD_Private_Functions
  * @{
  */

#if defined (USB_OTG_FS)


/**
  * @brief  Check FIFO for the next packet to be loaded.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval USB_FS status
  */
static USB_FS_StatusTypeDef PCD_FS_WriteEmptyTxFifo(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum)
{
  PCD_FS_EPTypeDef *ep;
  uint32_t len;

  ep = &hpcd->IN_ep[epnum];

  if (ep->xfer_count > ep->xfer_len)
  {
    return USB_FS_ERROR;
  }

  len = ep->xfer_len - ep->xfer_count;

  if (len > ep->maxpacket)
  {
    len = ep->maxpacket;
  }

  while (((USB_FS->TXCSR1 & OTG_FS_TXCSR1_FIFONE) == 0U) &
         (ep->xfer_count < ep->xfer_len) & (ep->xfer_len != 0U))
  {
    /* Write the FIFO */
    len = ep->xfer_len - ep->xfer_count;

    if (len > ep->maxpacket)
    {
      len = ep->maxpacket;
    }

    USB_FS_FIFOWrite(ep->xfer_buff, (uint8_t)epnum, (uint16_t)len);

    ep->xfer_buff  += len;
    ep->xfer_count += len;
  }

  return USB_FS_OK;
}

/**
  * @brief  process EP OUT transfer complete interrupt.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval none
  * */
void PCD_FS_EP0_IRQHandler(PCD_FS_HandleTypeDef *hpcd)
{
  USB_OTG_FS_DEPTypeDef *ep;
  uint8_t tmpreg;
  uint8_t bytecount;
  tmpreg = USB_FS->CSR0;

  if ((tmpreg & OTG_FS_CSR0_RXPKTRDY) == OTG_FS_CSR0_RXPKTRDY)
  {
    bytecount = USB_FS_Read_Count0();
    ep = &hpcd->OUT_ep[0U];

    if (hpcd->ctrl_state == CTRL_SETUP_P)
    {
        hpcd->ctrl_state = CTRL_DATA;
        USB_FS_FIFORead((uint8_t *)hpcd->Setup, 0U, bytecount);
        USB_FS->CSR0 |= OTG_FS_CSR0_SRXPKTRDY;
        PCD_FS_SetupStageCallback(hpcd);
    }
    else
    {
      USB_FS_FIFORead(ep->xfer_buff, 0U, bytecount);

      ep->xfer_buff += bytecount;
      ep->xfer_count += bytecount;
        
      USB_FS->CSR0 |= OTG_FS_CSR0_SRXPKTRDY;
        
      if (ep->xfer_count >= ep->xfer_len || bytecount < ep->maxpacket)
      {
        hpcd->ctrl_state = CTRL_SETUP_P;
        PCD_FS_DataOutStageCallback(hpcd, 0U);
      }
    }
  }
  else if (tmpreg != 0U)
  {
    if ((tmpreg & OTG_FS_CSR0_SETUPEND) == OTG_FS_CSR0_SETUPEND)
    {
      USB_FS->CSR0 |= OTG_FS_CSR0_SSETUPEND;
      USB_FS_FlushEp0Fifo();
    }
    if ((tmpreg & OTG_FS_CSR0_STSTALL) == OTG_FS_CSR0_STSTALL)
    {
      hpcd->ctrl_state = CTRL_SETUP_P;
      USB_FS_FlushEp0Fifo();   /* flush fifo to halt transcation*/
      USB_FS->CSR0 &= (~(OTG_FS_CSR0_STSTALL | OTG_FS_CSR0_SDSTALL));
    }
  }
  else
  {
	PCD_FS_DataInStageCallback(hpcd, 0U); /* for packet split */
    hpcd->ctrl_state = CTRL_SETUP_P;/*...*/
  }

}

/**
  * @brief  process EP OUT transfer complete interrupt.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval none
  * */
void PCD_FS_TXEP_IRQHandler(PCD_FS_HandleTypeDef *hpcd, uint32_t epnum)
{
  uint8_t tmpreg;
  uint32_t num_packets;

  tmpreg = USB_FS->TXCSR1;

  if ((tmpreg & OTG_FS_TXCSR1_FIFONE) == 0U)
  {
      USB_FS_FlushTxFifo(epnum);
  }

  if ((tmpreg & OTG_FS_TXCSR1_STSTALL) == OTG_FS_TXCSR1_STSTALL)
  {
    (void)USB_FS_FlushTxFifo(epnum);   /* flush fifo to halt transcation*/
    USB_FS->TXCSR1 &= (~OTG_FS_TXCSR1_STSTALL);
  }
  else if ((tmpreg & OTG_FS_TXCSR1_UNDERRUN) == OTG_FS_TXCSR1_UNDERRUN)
  {
    USB_FS->TXCSR1 &= (~OTG_FS_TXCSR1_UNDERRUN);
    PCD_FS_UNDERRUNCallback(hpcd);
  }
  else
  {
    PCD_FS_DataInStageCallback(hpcd, (uint8_t)epnum);
  }
}

/**
  * @brief  process EP OUT transfer complete interrupt.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval none
  * */
void PCD_FS_RXEP_IRQHandler(PCD_FS_HandleTypeDef *hpcd, uint32_t epnum)
{
  uint8_t tmpreg;
  uint16_t byte_count;
  uint32_t num_packets;
  PCD_FS_EPTypeDef *ep;

  tmpreg = USB_FS->RXCSR1;

  if (((tmpreg & OTG_FS_RXCSR1_FIFOF) == OTG_FS_RXCSR1_FIFOF) &
      ((tmpreg & OTG_FS_RXCSR1_RXPKTRDY) != OTG_FS_RXCSR1_RXPKTRDY))
  {
    byte_count = USB_FS_Read_RxCount();
    USB_FS_FIFORead(ep->xfer_buff, epnum, byte_count);
 //   PCD_FS_FIFOFULLCallback(hpcd);
  }

  if ((tmpreg & OTG_FS_RXCSR1_STSTALL) == OTG_FS_RXCSR1_STSTALL)
  {
    (void)USB_FS_FlushRxFifo(epnum);   /* flush fifo to halt transcation*/
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_STSTALL);
  }
  else if ((tmpreg & OTG_FS_RXCSR1_OVERRUN) == OTG_FS_RXCSR1_OVERRUN)
  {
    USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_OVERRUN);
    PCD_FS_OVERRUNCallback(hpcd);
  }
  else if ((tmpreg & OTG_FS_RXCSR1_RXPKTRDY) == OTG_FS_RXCSR1_RXPKTRDY)
  {
    if ((tmpreg & OTG_FS_RXCSR1_DERR) == OTG_FS_RXCSR1_DERR)
    {
      PCD_FS_DERRCallback(hpcd);
    }
    else
    {
      byte_count = USB_FS_Read_RxCount();
      USB_FS_FIFORead(ep->xfer_buff, epnum, byte_count);
//      PCD_FS_DataInStageCallback(hpcd, (uint8_t)epnum, byte_count);
      USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_RXPKTRDY);
    }
  }
}


#endif /* defined (USB_OTG_FS) */


/**
  * @brief  Set Tx FIFO
  * @param  fifo The number of Tx fifo
  * @param  size Fifo size
  * @retval none
  */
void PCD_FS_SetTxFiFo(uint8_t fifo, uint16_t size, uint8_t dpb)
{
  uint8_t i;
  uint32_t Tx_Offset;
  uint8_t fifo_size;
  uint8_t dpb_cfg;

  dpb_cfg = dpb << 4 ;
  /*  TXn min size = 16 words. (n  : Transmit FIFO index)
      When a TxFIFO is not used, the Configuration should be as follows:
          case 1 :  n > m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txm can use the space allocated for Txn.
         case2  :  n < m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txn should be configured with the minimum space of 16 words
     The FIFO is used optimally when used TxFIFOs are allocated in the top
         of the FIFO.Ex: use EP1 and EP2 as IN instead of EP1 and EP3 as IN ones.
 */

  Tx_Offset = 0x08;
  if (fifo == 0U)
  {
    return;
  }
  else
  {
    for (i = 1U; i < fifo; i++)
    {
      USB_FS_IndexSel(i);
      fifo_size = USB_FS->TXFIFO2 >> 5 ;
      Tx_Offset += (0x01U << fifo_size);
    }
    USB_FS_IndexSel(fifo);
    USB_FS->TXFIFO1 = Tx_Offset;
    USB_FS->TXFIFO2 = ((usb_log2((size + 7U) / 8U) << 5) | dpb_cfg);
  }
}

/**
  * @brief  Set Rx FIFO
  * @param  size Size of Rx fifo
  * @retval none
  */
void PCD_FS_SetRxFiFo(uint8_t fifo, uint16_t size, uint8_t dpb)
{
  uint8_t i;
  uint32_t Rx_Offset;
  uint8_t fifo_size;
  uint8_t dpb_cfg;

  dpb_cfg = dpb << 4 ;
  Rx_Offset = 0x08;

  if (fifo == 0U)
  {
    return;
  }
  else
  {
    for (i = 1U; i < fifo; i++)
    {
      USB_FS_IndexSel(i);
      fifo_size = USB_FS->RXFIFO2 >> 5 ;
      Rx_Offset += (0x01U << fifo_size);
    }
    USB_FS_IndexSel(fifo);
    USB_FS->RXFIFO1 = Rx_Offset;
    USB_FS->RXFIFO2 = ((usb_log2((size + 7U) / 8U) << 5) | dpb_cfg);
  }
}

/**
  * @}
  */


#endif /* defined (USB_OTG_FS) */
#endif /* PCD_FS_MODULE_ENABLED */

