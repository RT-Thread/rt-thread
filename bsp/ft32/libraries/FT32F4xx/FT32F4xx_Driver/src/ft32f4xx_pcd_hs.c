/**
  ******************************************************************************
  * @file    			ft32f4xx_pcd_hs.c
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
    (#)Declare a PCD_HS_HandleTypeDef handle structure, for example:
       PCD_HS_HandleTypeDef  hpcd;

    (#)Fill parameters of Init structure in PCD handle

    (#)Call PCD_HS_Init() API to initialize the PCD peripheral (Core, Host core, ...)

    (#)Initialize the PCD low level resources through the PCD_HS_MspInit() API:
        (##) Enable the PCD/USB Low Level interface clock using the following macros
        (##) Initialize the related GPIO clocks
        (##) Configure PCD NVIC interrupt

    (#)Associate the Upper USB Host stack to the PCD Driver:
        (##) hpcd.pData = pdev;

    (#)Enable PCD transmission and reception:
        (##) PCD_HS_Start();

  @endverbatim
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "ft32f4xx_rcc.h"
#include "ft32f4xx_pcd_hs.h"

/** @addtogroup FT32F4xx_DRIVER
  * @{
  */

#ifdef PCD_MODULE_ENABLED
#if defined (USB_OTG_HS)
/** @defgroup PCD_HS PCD
  * @brief PCD HS module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup PCD_HS_Private_Macros PCD Private Functions
  * @{
  */
#define PCD_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PCD_MAX(a,b) (((a) > (b)) ? (a) : (b))
/**
  * @{
  */

/** @defgroup PCD_HS_Private_Functions PCD Private Functions
  * @{
  */

static USB_HS_StatusTypeDef PCD_HS_WriteEmptyTxFifo(PCD_HS_HandleTypeDef *hpcd, uint32_t epnum);
static void PCD_HS_EP_OutXfrComplete_int(PCD_HS_HandleTypeDef *hpcd, uint32_t epnum);
static void PCD_HS_EP_OutSetupPacket_int(PCD_HS_HandleTypeDef *hpcd, uint32_t epnum);
/**
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PCD_HS_Exported_Functions PCD Exported Functions
  * @{
  */

/** @defgroup PCD_HS_Exported_Functions_Group1 Initialization and de-initialization functions
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
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_Init(PCD_HS_HandleTypeDef *hpcd)
{

  uint8_t i;

  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return USB_HS_ERROR;
  }

  if (hpcd->State == PCD_HS_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hpcd->Lock = USB_HS_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    PCD_HS_MspInit(hpcd);
  }

  hpcd->State = PCD_HS_STATE_BUSY;

  /* Disable the Interrupts */
  __PCD_HS_DISABLE();

  /*Init the Core (common init.) */
  if (USB_HS_CoreInit(hpcd->Init) != USB_HS_OK)
  {
    hpcd->State = PCD_HS_STATE_ERROR;
    return USB_HS_ERROR;
  }

  /* Init endpoints structures */
  for (i = 0U; i < hpcd->Init.dev_endpoints; i++)
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

  for (i = 0U; i < hpcd->Init.dev_endpoints; i++)
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
  if (USB_HS_DevInit(hpcd->Init) != USB_HS_OK)
  {
    hpcd->State = PCD_HS_STATE_ERROR;
    return USB_HS_ERROR;
  }

  hpcd->USB_Address = 0U;
  hpcd->State = PCD_HS_STATE_READY;

  USB_HS_DevDisconnect();

  return USB_HS_OK;
}

/**
  * @brief  DeInitializes the PCD peripheral.
  * @param  hpcd PCD handle
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_DeInit(PCD_HS_HandleTypeDef *hpcd)
{
  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return USB_HS_ERROR;
  }

  hpcd->State = PCD_HS_STATE_BUSY;

  /* Stop Device */
  if (USB_HS_StopDevice() != USB_HS_OK)
  {
    return USB_HS_ERROR;
  }

  /* DeInit the low level hardware: CLOCK, NVIC.*/
  PCD_HS_MspDeInit(hpcd);

  hpcd->State = PCD_HS_STATE_RESET;

  return USB_HS_OK;
}

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_MspInit(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_MspDeInit(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_MspDeInit could be implemented in the user file
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
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_Start(PCD_HS_HandleTypeDef *hpcd)
{
  __USB_HS_LOCK(hpcd);
  __PCD_HS_ENABLE();

  USB_HS_DevConnect();
  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}

/**
  * @brief  Stop the USB device.
  * @param  hpcd PCD handle
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_Stop(PCD_HS_HandleTypeDef *hpcd)
{
  __USB_HS_LOCK(hpcd);
  __PCD_HS_DISABLE();

  USB_HS_DevDisconnect();

  (void)USB_HS_FlushTxFifo(0x10U);

  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}

#if defined (USB_OTG_HS)
/**
  * @brief  Handles PCD interrupt request.
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_HS_IRQHandler(PCD_HS_HandleTypeDef *hpcd)
{
  USB_OTG_HS_EPTypeDef *ep;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  uint32_t AHBCLK;
  uint32_t i;
  uint32_t ep_intr;
  uint32_t epint;
  uint32_t epnum;
  uint32_t fifoemptymsk;
  uint32_t RegVal;

  /* ensure that we are in device mode */
  if (USB_HS_GetMode() == USB_OTG_MODE_DEVICE)
  {
    /* avoid spurious interrupt */
    if (__PCD_HS_IS_INVALID_INTERRUPT())
    {
      return;
    }

    /* store current frame number */
    hpcd->FrameNumber = (USB_HS_DEVICE->DSTS & OTG_HS_DSTS_FNSOF_Msk) >> OTG_HS_DSTS_FNSOF_Pos;

    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_MMIS))
    {
      /* incorrect mode, acknowledge the interrupt */
      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_MMIS);
    }

    /* Handle RxQLevel Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_RXFLVL))
    {
      USB_HS_MASK_INTERRUPT(OTG_HS_GINTSTS_RXFLVL);

      RegVal = USB_HS->GRXSTSP;

      ep = &hpcd->OUT_ep[RegVal & OTG_HS_GRXSTSP_EPNUM];

      if (((RegVal & OTG_HS_GRXSTSP_PKTSTS) >> 17) ==  STS_DATA_UPDT)
      {
        if ((RegVal & OTG_HS_GRXSTSP_BCNT) != 0U)
        {
          (void)USB_HS_ReadPacket(ep->xfer_buff, (uint16_t)((RegVal & OTG_HS_GRXSTSP_BCNT) >> 4));

          ep->xfer_buff += (RegVal & OTG_HS_GRXSTSP_BCNT) >> 4;
          ep->xfer_count += (RegVal & OTG_HS_GRXSTSP_BCNT) >> 4;
        }
      }
      else if (((RegVal & OTG_HS_GRXSTSP_PKTSTS) >> 17) ==  STS_SETUP_UPDT)
      {
        (void)USB_HS_ReadPacket((uint8_t *)hpcd->Setup, 8U);
        ep->xfer_count += (RegVal & OTG_HS_GRXSTSP_BCNT) >> 4;
      }
      else
      {
        /* ... */
      }
      USB_HS_UNMASK_INTERRUPT(OTG_HS_GINTSTS_RXFLVL);
    }
    /* USB_HS->GINTSTS  OEPINT(OUT POINT)*/
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_OEPINT))
    {
      epnum = 0U;

      /* Read in the device interrupt bits */
      ep_intr = USB_HS_ReadDevAllOutEpInterrupt();

      while (ep_intr != 0U)
      {
        if ((ep_intr & 0x1U) != 0U)
        {
          epint = USB_HS_ReadDevOutEPInterrupt((uint8_t)epnum);
//          if(epnum == 0)USBD_SET_ADDR_Callback(hpcd);
          if ((epint & OTG_HS_DOEPINT_XFRC) == OTG_HS_DOEPINT_XFRC)
          {
            CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_XFRC);
            (void)PCD_HS_EP_OutXfrComplete_int(hpcd, epnum);
          }

          if ((epint & OTG_HS_DOEPINT_STUPD) == OTG_HS_DOEPINT_STUPD)
          {
            CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_STUPD);
            /* Class B setup phase done for previous decoded setup */
            (void)PCD_HS_EP_OutSetupPacket_int(hpcd, epnum);
          }

          if ((epint & OTG_HS_DOEPINT_OTKNEPDIS) ==OTG_HS_DOEPINT_OTKNEPDIS)
          {
            CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_OTKNEPDIS);
          }

          /* Clear OUT Endpoint disable interrupt */
          if ((epint & OTG_HS_DOEPINT_EPDISD) == OTG_HS_DOEPINT_EPDISD)
          {
            if ((USB_HS->GINTSTS & OTG_HS_GINTSTS_GONAKEFF) == OTG_HS_GINTSTS_GONAKEFF)
            {
              USB_HS_DEVICE->DCTL |= OTG_HS_DCTL_CGONAK ;
            }

            ep = &hpcd->OUT_ep[epnum];
            if (ep->is_iso_incomplete == 1U)
            {
              ep->is_iso_incomplete = 0U;

              PCD_HS_ISOOUTIncompleteCallback(hpcd, (uint8_t)epnum);
            }
            CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_EPDISD);
          }

          /* Clear Status Phase Received interrupt */
          if ((epint & OTG_HS_DOEPINT_OTEPSPR) == OTG_HS_DOEPINT_OTEPSPR)
          {
            CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_OTEPSPR);
          }

          /* Clear OUT NAK interrupt */
          if ((epint & OTG_HS_DOEPINT_NAKINT) == OTG_HS_DOEPINT_NAKINT)
          {
            CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_NAKINT);
          }
        }
        epnum++;
        ep_intr >>= 1U;
      }
    }

    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_IEPINT))
    {
      /* Read in the device interrupt bits */
      ep_intr = USB_HS_ReadDevAllInEpInterrupt();

      epnum = 0U;

      while (ep_intr != 0U)
      {
        if ((ep_intr & 0x1U) != 0U) /* In ITR */
        {
          epint = USB_HS_ReadDevInEPInterrupt((uint8_t)epnum);
          
          if ((epint & OTG_HS_DIEPINT_XFRC) == OTG_HS_DIEPINT_XFRC)
          {
            fifoemptymsk = (uint32_t)(0x1UL << (epnum & EP_ADDR_MSK));
            USB_HS_DEVICE->DIEPEMPMSK &= ~fifoemptymsk;

            CLEAR_IN_EP_INTR(epnum, OTG_HS_DIEPINT_XFRC);

            PCD_HS_DataInStageCallback(hpcd, (uint8_t)epnum);
          }
          if ((epint & OTG_HS_DIEPINT_TOC) == OTG_HS_DIEPINT_TOC)
          {
            CLEAR_IN_EP_INTR(epnum, OTG_HS_DIEPINT_TOC);
          }
          if ((epint & OTG_HS_DIEPINT_ITTXFE) == OTG_HS_DIEPINT_ITTXFE)
          {
            CLEAR_IN_EP_INTR(epnum, OTG_HS_DIEPINT_ITTXFE);
          }
          if ((epint & OTG_HS_DIEPINT_INEPNE) == OTG_HS_DIEPINT_INEPNE)
          {
            CLEAR_IN_EP_INTR(epnum, OTG_HS_DIEPINT_INEPNE);
          }
          if ((epint & OTG_HS_DIEPINT_EPDISD) == OTG_HS_DIEPINT_EPDISD)
          {
            (void)USB_HS_FlushTxFifo(epnum);

            ep = &hpcd->IN_ep[epnum];
            if (ep->is_iso_incomplete == 1U)
            {
              ep->is_iso_incomplete = 0U;

              PCD_HS_ISOINIncompleteCallback(hpcd, (uint8_t)epnum);
            }

            CLEAR_IN_EP_INTR(epnum, OTG_HS_DIEPINT_EPDISD);
          }
          if ((epint & OTG_HS_DIEPINT_TXFE) == OTG_HS_DIEPINT_TXFE)
          {
            (void)PCD_HS_WriteEmptyTxFifo(hpcd, epnum);
          }
        }
        epnum++;
        ep_intr >>= 1U;
      }
    }

    /* Handle Resume Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_WKUPINT))
    {
      /* Clear the Remote Wake-up Signaling */
      USB_HS_DEVICE->DCTL &= ~OTG_HS_DCTL_RWUSIG;

      PCD_HS_ResumeCallback(hpcd);

      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_WKUPINT);
    }

    /* Handle Suspend Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_USBSUSP))
    {
      if ((USB_HS_DEVICE->DSTS & OTG_HS_DSTS_SUSPSTS) == OTG_HS_DSTS_SUSPSTS)
      {

//        PCD_HS_SuspendCallback(hpcd);
      }
      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_USBSUSP);
    }
    /* Handle Reset Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_USBRST))
    {
      USB_HS_DEVICE->DCTL &= ~OTG_HS_DCTL_RWUSIG;
      (void)USB_HS_FlushTxFifo(0x10U);

      for (i = 0U; i < hpcd->Init.dev_endpoints; i++)
      {
        USB_HS_INEP(i)->DIEPINT = 0xFB7FU;
        USB_HS_INEP(i)->DIEPCTL &= ~OTG_HS_DIEPCTL_STALL;
        USB_HS_OUTEP(i)->DOEPINT = 0xFB7FU;
        USB_HS_OUTEP(i)->DOEPCTL &= ~OTG_HS_DOEPCTL_STALL;
        USB_HS_OUTEP(i)->DOEPCTL |= OTG_HS_DOEPCTL_SNAK;
      }
      USB_HS_DEVICE->DAINTMSK |= 0x10001U;

      if (hpcd->Init.use_dedicated_ep1 != 0U)
      {
        USB_HS_DEVICE->DOUTEP1MSK |= OTG_HS_DOEPMSK_STUPM |
                                     OTG_HS_DOEPMSK_XFRCM |
                                     OTG_HS_DOEPMSK_EPDM;

        USB_HS_DEVICE->DINEP1MSK |= OTG_HS_DIEPMSK_TOM   |
                                    OTG_HS_DIEPMSK_XFRCM |
                                    OTG_HS_DIEPMSK_EPDM;
      }
      else
      {
        USB_HS_DEVICE->DOEPMSK |= OTG_HS_DOEPMSK_STUPM |
                                  OTG_HS_DOEPMSK_XFRCM |
                                  OTG_HS_DOEPMSK_EPDM  |
                                  OTG_HS_DOEPMSK_OTEPSPRM |
                                  OTG_HS_DOEPMSK_NAKM;

        USB_HS_DEVICE->DIEPMSK |= OTG_HS_DIEPMSK_TOM   |
                                  OTG_HS_DIEPMSK_XFRCM |
                                  OTG_HS_DIEPMSK_EPDM  ;
      }

      /* Set Default Address to 0 */
      USB_HS_DEVICE->DCFG &= ~OTG_HS_DCFG_DAD; 
      
      /* setup EP0 to receive SETUP packets */
      (void)USB_HS_EP0_OutStart((uint8_t)hpcd->Init.dma_enable, (uint8_t *)hpcd->Setup);

      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_USBRST);
    }

    /* Handle Enumeration done Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_ENUMDNE))
    {
      (void)USB_HS_ActivateSetup();
      hpcd->Init.speed = USB_HS_GetDevSpeed();

      /* Set USB Turnaround time */
      /* RCC_GetClocksFreq wait for update */
      RCC_GetClocksFreq(&RCC_ClocksStatus);
      AHBCLK = RCC_ClocksStatus.HCLK_Frequency;
      (void)USB_HS_SetTurnaroundTime(AHBCLK, (uint8_t)hpcd->Init.speed);

      PCD_HS_ResetCallback(hpcd);

      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_ENUMDNE);
    }

    /* Handle SOF Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_SOF))
    {
      PCD_HS_SOFCallback(hpcd);

      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_SOF);
    }

    /* Handle Global OUT NAK effective Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_GONAKEFF))
    {
      USB_HS->GINTMSK &= ~OTG_HS_GINTMSK_GONAKEFM;
      for (epnum = 1U; epnum < hpcd->Init.dev_endpoints; epnum++)
      {
        if (hpcd->OUT_ep[epnum].is_iso_incomplete == 1U)
        {
          /* abort current transaction and disable the EP */
          (void)PCD_HS_EP_Abort(hpcd, (uint8_t)epnum);
        }
      }
    }
    /* Handle Incomplete ISO IN Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_IISOIXFR))
    {
      for (epnum = 1U; epnum < hpcd->Init.dev_endpoints; epnum++)
      {
        RegVal = USB_HS_INEP(epnum)->DIEPCTL;

        if ((hpcd->IN_ep[epnum].type == EP_TYPE_ISOC) & ((RegVal & OTG_HS_DIEPCTL_EPENA) == OTG_HS_DIEPCTL_EPENA))
        {
          hpcd->IN_ep[epnum].is_iso_incomplete = 1U;

          /* Abort current transaction and disable the EP */
          (void)PCD_HS_EP_Abort(hpcd, (uint8_t)(epnum | 0x80U));
        }
      }

      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_IISOIXFR);
    }

    /* Handle Incomplete ISO OUT Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_IPXFR_INCOMPISOOUT))
    {
      for (epnum = 1U; epnum < hpcd->Init.dev_endpoints; epnum++)
      {
        RegVal = USB_HS_OUTEP(epnum)->DOEPCTL;

        if ((hpcd->OUT_ep[epnum].type == EP_TYPE_ISOC) & ((RegVal & OTG_HS_DOEPCTL_EPENA) == OTG_HS_DIEPCTL_EPENA) 
             & (((RegVal & (0x1U << 16U)) >> 16U) == (hpcd->FrameNumber & 0x1U)))
        {
          hpcd->OUT_ep[epnum].is_iso_incomplete = 1U;
          USB_HS->GINTMSK |= OTG_HS_GINTMSK_GONAKEFM;

          if ((USB_HS->GINTSTS & OTG_HS_GINTSTS_GONAKEFF) == 0U)
          {
            USB_HS_DEVICE->DCTL |= OTG_HS_DCTL_SGONAK;
            break;
          }
        }
      }

      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_IPXFR_INCOMPISOOUT);
    }

    /* Handle Connection event Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_SRQINT))
    {
      PCD_HS_ConnectCallback(hpcd);

      __PCD_HS_CLEAR_FLAG(OTG_HS_GINTSTS_SRQINT);
    }

    /* Handle Disconnection event Interrupt */
    if (__PCD_HS_GET_FLAG(OTG_HS_GINTSTS_OTGINT))
    {
      RegVal = USB_HS->GOTGINT;

      if ((RegVal & OTG_HS_GOTGINT_SEDET) == OTG_HS_GOTGINT_SEDET)
      {

        PCD_HS_DisconnectCallback(hpcd);
      }
      USB_HS->GOTGINT |= RegVal;
    }
  }
}

/**
  * @brief  Handles PCD Wakeup interrupt request.
  * @param  hpcd PCD handle
  * @retval none status
  */
void PCD_HS_WKUP_IRQHandler()
{
  /* Clear EXTI pending Bit */
  __USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG();
}
#endif /* defined (USB_OTG_HS) */


/**
  * @brief  Data OUT stage callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
void __attribute__((weak)) PCD_HS_DataOutStageCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_DataOutStageCallback could be implemented in the user file
   */
}

/**
  * @brief  Data IN stage callback
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
void __attribute__((weak)) PCD_HS_DataInStageCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_DataInStageCallback could be implemented in the user file
   */
}
/**
  * @brief  Setup stage callback
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_SetupStageCallback(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_SetupStageCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_SOFCallback(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_SOFCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Reset callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_ResetCallback(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_ResetCallback could be implemented in the user file
   */
}
void __attribute__((weak)) USBD_SET_ADDR_Callback(PCD_HS_HandleTypeDef *hpcd)
{
    UNUSED(hpcd);
}
/**
  * @brief  Suspend event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_SuspendCallback(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_SuspendCallback could be implemented in the user file
   */
}

/**
  * @brief  Resume event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_ResumeCallback(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_ResumeCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO OUT callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
void __attribute__((weak)) PCD_HS_ISOOUTIncompleteCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_ISOOUTIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO IN callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
void __attribute__((weak)) PCD_HS_ISOINIncompleteCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_ISOINIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Connection event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_ConnectCallback(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_ConnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
void __attribute__((weak)) PCD_HS_DisconnectCallback(PCD_HS_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the PCD_HS_DisconnectCallback could be implemented in the user file
   */
}

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

/**
  * @brief  Connect the USB device
  * @param  hpcd PCD handle
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_DevConnect(PCD_HS_HandleTypeDef *hpcd)
{
  __USB_HS_LOCK(hpcd);

  USB_HS_DevConnect();
  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}

/**
  * @brief  Disconnect the USB device.
  * @param  hpcd PCD handle
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_DevDisconnect(PCD_HS_HandleTypeDef *hpcd)
{
  __USB_HS_LOCK(hpcd);

  USB_HS_DevDisconnect();
  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}

/**
  * @brief  Set the USB Device address.
  * @param  hpcd PCD handle
  * @param  address new device address
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_SetAddress(PCD_HS_HandleTypeDef *hpcd, uint8_t address)
{
  __USB_HS_LOCK(hpcd);
  hpcd->USB_Address = address;
  USB_HS_SetDevAddress(address);
  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}
/**
  * @brief  Open and configure an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  ep_mps endpoint max packet size
  * @param  ep_type endpoint type
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_EP_Open(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr,
                                  uint16_t ep_mps, uint8_t ep_type)
{
  USB_HS_StatusTypeDef  ret = USB_HS_OK;
  PCD_HS_EPTypeDef *ep;

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

  __USB_HS_LOCK(hpcd);
  USB_HS_ActivateEndpoint(ep);
  __USB_HS_UNLOCK(hpcd);

  return ret;
}

/**
  * @brief  Deactivate an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_EP_Close(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_HS_EPTypeDef *ep;

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

  __USB_HS_LOCK(hpcd);
  USB_HS_DeactivateEndpoint(ep);
  __USB_HS_UNLOCK(hpcd);
  return USB_HS_OK;
}


/**
  * @brief  Receive an amount of data.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  pBuf pointer to the reception buffer
  * @param  len amount of data to be received
  * @retval none
  */
void PCD_HS_EP_Receive(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  PCD_HS_EPTypeDef *ep;

  ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];

  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;
  ep->xfer_len = len;
  ep->xfer_count = 0U;
  ep->is_in = 0U;
  ep->num = ep_addr & EP_ADDR_MSK;

  if (hpcd->Init.dma_enable == 1U)
  {
    ep->dma_addr = (uint32_t)pBuf;
  }

  USB_HS_EPStartXfer(ep, (uint8_t)hpcd->Init.dma_enable);

}

/**
  * @brief  Get Received Data Size
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval Data Size
  */
uint32_t PCD_HS_EP_GetRxCount(PCD_HS_HandleTypeDef const *hpcd, uint8_t ep_addr)
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
void PCD_HS_EP_Transmit(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  PCD_HS_EPTypeDef *ep;

  ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];

  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;
  ep->xfer_len = len;
  ep->xfer_count = 0U;
  ep->is_in = 1U;
  ep->num = ep_addr & EP_ADDR_MSK;

  if ((ep_addr & EP_ADDR_MSK) == 1U)
  {
    ep->dma_addr = (uint32_t)pBuf;
  }

  USB_HS_EPStartXfer(ep, (uint8_t)hpcd->Init.dma_enable);

}

/**
  * @brief  Set a STALL condition over an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_EP_SetStall(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_HS_EPTypeDef *ep;

  if (((uint32_t)ep_addr & EP_ADDR_MSK) > hpcd->Init.dev_endpoints)
  {
    return USB_HS_ERROR;
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

  __USB_HS_LOCK(hpcd);

  USB_HS_EPSetStall(ep);

  if ((ep_addr & EP_ADDR_MSK) == 0U)
  {
    (void)USB_HS_EP0_OutStart((uint8_t)hpcd->Init.dma_enable, (uint8_t *)hpcd->Setup);
  }

  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}

/**
  * @brief  Clear a STALL condition over in an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_EP_ClrStall(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_HS_EPTypeDef *ep;

  if (((uint32_t)ep_addr & 0x0FU) > hpcd->Init.dev_endpoints)
  {
    return USB_HS_ERROR;
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

  __USB_HS_LOCK(hpcd);
  USB_HS_EPClearStall(ep);
  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}

/**
  *
  * @brief  Abort an USB EP transaction
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_EP_Abort(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  USB_HS_StatusTypeDef ret;
  PCD_HS_EPTypeDef *ep;

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
  }

  /* Stop Xfer */
  ret = USB_HS_EPStopXfer(ep);

  return ret;
}

/**
  * @brief  Flush an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef PCD_HS_EP_Flush(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  __USB_HS_LOCK(hpcd);

  if ((ep_addr & 0x80U) == 0x80U)
  {
    (void)USB_HS_FlushTxFifo((uint32_t)ep_addr & EP_ADDR_MSK);
  }
  else
  {
    (void)USB_HS_FlushRxFifo();
  }

  __USB_HS_UNLOCK(hpcd);

  return USB_HS_OK;
}

/**
  * @brief  Activate remote wakeup signalling
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_HS_ActivateRemoteWakeup()
{
  USB_HS_ActivateRemoteWakeup();
}

/**
  * @brief  De-activate remote wakeup signalling.
  * @param  hpcd PCD handle
  * @retval none
  */
void PCD_HS_DeActivateRemoteWakeup()
{
  USB_HS_DeActivateRemoteWakeup();
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
PCD_HS_StateTypeDef PCD_HS_GetState(PCD_HS_HandleTypeDef const *hpcd)
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
#if defined (USB_OTG_HS)

/**
  * @brief  Set the USB Device high speed test mode
  * @param  hpcd PCD handle
  * @param  testmode USB Device high speed testmode
  * @retval none
  */
void PCD_HS_SetTestMode(uint8_t testmode)
{
  switch (testmode)
  {
    case TEST_J:
    case TEST_K:
    case TEST_SE0_NAK:
    case TEST_PACKET:
    case TEST_FORCE_EN:
      USB_HS_DEVICE->DCTL |= (uint32_t)testmode << 4;
      break;

    default:
      break;

  }
}
#endif /* defined (USB_OTG_HS) */


#if defined (USB_OTG_HS)


/**
  * @brief  Check FIFO for the next packet to be loaded.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval USBH status
  */
static USB_HS_StatusTypeDef PCD_HS_WriteEmptyTxFifo(PCD_HS_HandleTypeDef *hpcd, uint32_t epnum)
{
  USB_OTG_HS_EPTypeDef *ep;
  uint32_t len;
  uint32_t len32b;
  uint32_t fifoemptymsk;

  ep = &hpcd->IN_ep[epnum];

  if (ep->xfer_count > ep->xfer_len)
  {
    return USB_HS_ERROR;
  }

  len = ep->xfer_len - ep->xfer_count;

  if (len > ep->maxpacket)
  {
    len = ep->maxpacket;
  }

  len32b = (len + 3U) / 4U;

  while (((USB_HS_INEP(epnum)->DTXFSTS & OTG_HS_DTXFSTS_INEPTFSAV) >= len32b) &
         (ep->xfer_count < ep->xfer_len) & (ep->xfer_len != 0U))
  {
    /* Write the FIFO */
    len = ep->xfer_len - ep->xfer_count;

    if (len > ep->maxpacket)
    {
      len = ep->maxpacket;
    }
    len32b = (len + 3U) / 4U;

    USB_HS_WritePacket(ep->xfer_buff, (uint8_t)epnum, (uint16_t)len, (uint8_t)hpcd->Init.dma_enable);

    ep->xfer_buff  += len;
    ep->xfer_count += len;
  }

  if (ep->xfer_len <= ep->xfer_count)
  {
    fifoemptymsk = (uint32_t)(0x1UL << (epnum & EP_ADDR_MSK));
    USB_HS_DEVICE->DIEPEMPMSK &= ~fifoemptymsk;
  }

  return USB_HS_OK;
}


/**
  * @brief  process EP OUT transfer complete interrupt.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval none
  * */
void PCD_HS_EP_OutXfrComplete_int(PCD_HS_HandleTypeDef *hpcd, uint32_t epnum)
{
  USB_OTG_HS_EPTypeDef *ep;
  uint32_t DoepintReg = USB_HS_OUTEP(epnum)->DOEPINT;

  if (hpcd->Init.dma_enable == 1U)
  {
    if ((DoepintReg & OTG_HS_DOEPINT_STUPD) == OTG_HS_DOEPINT_STUPD) /* Class C */
    {
      /* StupPktRcvd = 1 this is a setup packet */
      if((DoepintReg & OTG_HS_DOEPINT_STPKRE) == OTG_HS_DOEPINT_STPKRE)
      {
        CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_STPKRE);
      }
    }
    else if ((DoepintReg & OTG_HS_DOEPINT_OTEPSPR) == OTG_HS_DOEPINT_OTEPSPR)
    {
      CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_OTEPSPR);
    }
    else if ((DoepintReg & (OTG_HS_DOEPINT_STUPD | OTG_HS_DOEPINT_OTEPSPR)) == 0U)
    {
      /* StupPktRcvd = 1 this is a setup packet */
      if((DoepintReg & OTG_HS_DOEPINT_STPKRE) == OTG_HS_DOEPINT_STPKRE)
      {
        CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_STPKRE);
      }
      else
      {
        ep = &hpcd->OUT_ep[epnum];
        /* out data packet received over EP */
        ep->xfer_count = ep->xfer_size - (USB_HS_OUTEP(epnum)->DOEPTSIZ & OTG_HS_DOEPTSIZ_XFRSIZ) ;

        if (epnum == 0U)
        {
          if (ep->xfer_len == 0U)
          {
            /* this is ZLP, so prepare EP0 for next setup */
            (void)USB_HS_EP0_OutStart(1U, (uint8_t *)hpcd->Setup);
          }
          else
          {
            ep->xfer_buff += ep->xfer_count;
          }
        }

        PCD_HS_DataOutStageCallback(hpcd, (uint8_t)epnum);
      }
    }
    else
    {
      /*...*/
    }
  }
  else
  {
    /* StupPktRcvd = 1 this is a setup packet */
    if ((DoepintReg & OTG_HS_DOEPINT_STPKRE) == OTG_HS_DOEPINT_STPKRE)
    {
      CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_STPKRE);
    }
    else
    {
      if ((DoepintReg & OTG_HS_DOEPINT_OTEPSPR) == OTG_HS_DOEPINT_OTEPSPR)
      {
        CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_OTEPSPR);
      }

      PCD_HS_DataOutStageCallback(hpcd, (uint8_t)epnum);
    }

  }

}


/**
  * @brief  process EP OUT setup packet received interrupt.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval none
  */
static void PCD_HS_EP_OutSetupPacket_int(PCD_HS_HandleTypeDef *hpcd, uint32_t epnum)
{
  uint32_t DoepintReg = USB_HS_OUTEP(epnum)->DOEPINT;

  if ((DoepintReg & OTG_HS_DOEPINT_STPKRE) == OTG_HS_DOEPINT_STPKRE)
  {
    CLEAR_OUT_EP_INTR(epnum, OTG_HS_DOEPINT_STPKRE);
  }

  /* Inform the upper layer that a setup packet is available */
  PCD_HS_SetupStageCallback(hpcd);

}
#endif /* defined (USB_OTG_HS) */

/**
  * @}
  */


#endif /* defined (USB_OTG_HS) */
#endif /* PCD_MODULE_ENABLED */

