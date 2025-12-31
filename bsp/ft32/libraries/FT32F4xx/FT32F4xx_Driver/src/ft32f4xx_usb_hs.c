/**
  ******************************************************************************
  * @file    			ft32f4xx_usb_hs.c
  * @author  			FMD XA
  * @brief   			This file provides firmware functions to manage the following 
  *          			functionalities of the USB Peripheral Controller:
  *           		+ Initialization/de-initialization functions
  *           		+ Peripheral Control functions
  *           		+ Peripheral State functions
  * @version 			V1.0.0           
  * @data		 			2025-03-20
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Fill parameters of Init structure in USB_OTG_CfgTypeDef structure.

      (#) Call USB_HS_CoreInit() API to initialize the USB Core peripheral.

      (#) The upper HCD/PCD driver will call the right routines for its internal processes.
  @endverbatim
******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "system_ft32f4xx.h"
#include "ft32f4xx_misc.h"
#include "ft32f4xx_usb_hs.h"

/** @addtogroup FT32F4xx_USB_HS_DRIVER
  * @{
  */

#if defined (PCD_MODULE_ENABLED) || defined (HCD_MODULE_ENABLED)
#if defined (USB_OTG_HS)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if defined (USB_OTG_HS)
static USB_HS_StatusTypeDef USB_HS_CoreReset();

volatile uint32_t delayCount_hs_ms;

/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_Exported_Functions USB OTG HS Low Layer Exported Functions
  * @{
  */

/** @defgroup USB_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
                      ##### Initialization/de-initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */
void USB_HS_Delayms (uint32_t num)
{
    if(SysTick_Config(SystemCoreClock/1000))
    {
        while (1);
    }
    uint32_t tickStart = delayCount_hs_ms;
    while ((delayCount_hs_ms - tickStart) < num);
}
/**
  * @brief  Initializes the USB OTG HS Core
  * @param  USB HS USB Instance
  * @param  cfg pointer to a USB_OTG_HS_CfgTypeDef structure that contains
  *         the configuration information for the specified USB_HS peripheral.
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_CoreInit(USB_OTG_HS_CfgTypeDef cfg)
{
  USB_HS_StatusTypeDef ret;
  #define W32_TRIM(ADDRESS) (*((volatile unsigned int *)(ADDRESS)))
  uint32_t read_trim;
  uint32_t otgtune;  
  uint32_t comptune;
  uint32_t sqrxtune; 
  uint32_t txhstune;
  uint32_t vregtune;  
  uint32_t txfslstune;
  uint32_t txvreftune;   
  uint32_t txrisetune;
  uint32_t txpretune;  

  read_trim = W32_TRIM(0x1FFF0A24);

  otgtune      = ((read_trim & 0x00000007) << 3);  // bit5:3 
  comptune     = ((read_trim & 0x00000070) << 2);  // bit8:6
  sqrxtune     = ((read_trim & 0x00000700) << 1);  // bit11:9 
  txhstune     = ((read_trim & 0x00003000)     );  // bit13:12
  vregtune     = ((read_trim & 0x00004000)     );  // bit14
  txfslstune   = ((read_trim & 0x000F0000) >> 1);  // bit18:15
  txvreftune   = ((read_trim & 0x00F00000) >> 1);  // bit 22:19 
  txrisetune   = ((read_trim & 0x01000000) >> 1);  // bit23
  txpretune    = ((read_trim & 0x02000000) >> 1);  // bit24

  /* Init the UTMI interface */
  USB_HS->GUSBCFG &= ~(OTG_HS_GUSBCFG_TSDPS);

  /* Reset */
  ret = USB_HS_CoreReset();
  /* change srqxtune txvreftune otgtune compdistune */
  /* waiting for update                             */
  USB_HS_PKEY = 0x5057 ;
  USB_HS_PKEY = 0x5948 ;

//USB_HS_PREG = 0x0041B723;
  USB_HS_PREG = (otgtune    | comptune   | sqrxtune   |
                 txhstune   | vregtune   | txfslstune |
                 txvreftune | txrisetune | txpretune  |
                 0x03);
                 
  *(uint32_t*)(0x40040E1C) |= 0x2000000;

  USB_HS_PKEY = 0x0;


  if (cfg.dma_enable == 1U)
  {
    USB_HS->GAHBCFG |= OTG_HS_GAHBCFG_HBSTLEN_2 ;  // INCR4
    USB_HS->GAHBCFG |= OTG_HS_GAHBCFG_DMAEN ;      // enable dma mode
  }
  return ret;
}


/**
  * @brief  Set the USB turnaround time
  * @param  USB HS Instance
  * @param  hlck: AHB clock frequency
  * @retval USB HS turnaround time in PHY clock number
  */

void USB_HS_SetTurnaroundTime(uint32_t hclk, uint8_t speed)
{
  uint32_t UsbTrd;

  /* The USBTRD is configured according to the tables below, depending on AHB frequency
  used by application. In the low AHB frequency range it is used to stretch enough the USB response
  time to IN tokens, the USB turnaround time, so to compensate for the longer AHB read access
  latency to the Data FIFO */
  if (speed == USBD_FS_SPEED)
  {
    if ((hclk >= 14200000U) && (hclk < 15000000U))
    {
      /* hclk Clock Range between 14.2-15 MHz */
      UsbTrd = 0xFU;
    }
    else if ((hclk >= 15000000U) && (hclk < 16000000U))
    {
      /* hclk Clock Range between 15-16 MHz */
      UsbTrd = 0xEU;
    }
    else if ((hclk >= 16000000U) && (hclk < 17200000U))
    {
      /* hclk Clock Range between 16-17.2 MHz */
      UsbTrd = 0xDU;
    }
    else if ((hclk >= 17200000U) && (hclk < 18500000U))
    {
      /* hclk Clock Range between 17.2-18.5 MHz */
      UsbTrd = 0xCU;
    }
    else if ((hclk >= 18500000U) && (hclk < 20000000U))
    {
      /* hclk Clock Range between 18.5-20 MHz */
      UsbTrd = 0xBU;
    }
    else if ((hclk >= 20000000U) && (hclk < 21800000U))
    {
      /* hclk Clock Range between 20-21.8 MHz */
      UsbTrd = 0xAU;
    }
    else if ((hclk >= 21800000U) && (hclk < 24000000U))
    {
      /* hclk Clock Range between 21.8-24 MHz */
      UsbTrd = 0x9U;
    }
    else if ((hclk >= 24000000U) && (hclk < 27700000U))
    {
      /* hclk Clock Range between 24-27.7 MHz */
      UsbTrd = 0x8U;
    }
    else if ((hclk >= 27700000U) && (hclk < 32000000U))
    {
      /* hclk Clock Range between 27.7-32 MHz */
      UsbTrd = 0x7U;
    }
    else /* if(hclk >= 32000000) */
    {
      /* hclk Clock Range between 32-200 MHz */
      UsbTrd = 0x6U;
    }
  }
  else if (speed == USBD_HS_SPEED)
  {
    UsbTrd = USBD_HS_TRDT_VALUE;
  }
  else
  {
    UsbTrd = USBD_DEFAULT_TRDT_VALUE;
  }

  USB_HS->GUSBCFG &= ~OTG_HS_GUSBCFG_TRDT;
  USB_HS->GUSBCFG |= (uint32_t)((UsbTrd << 10) & OTG_HS_GUSBCFG_TRDT);

}


/**
  * @brief  USB_HS_EnableGlobalInt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  USB_HS  Selected device
  */
void USB_HS_EnableGlobalInt(void)
{
  USB_HS->GAHBCFG |= OTG_HS_GAHBCFG_GINT;
}

/**
  * @brief  USB_HS_DisableGlobalInt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  USB_HS  Selected device
  */
void USB_HS_DisableGlobalInt(void)
{
  USB_HS->GAHBCFG &= ~OTG_HS_GAHBCFG_GINT;
}

/**
  * @brief  USB_HS_SetCurrentMode Set functional mode
  * @param  USB_HS  Selected device
  * @param  mode  current core mode
  *          This parameter can be one of these values:
  *            @arg USB_DEVICE_MODE Peripheral mode
  *            @arg USB_HOST_MODE Host mode
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_SetCurrentMode(USB_ModeTypeDef mode)
{
  uint32_t ms = 0U;

  USB_HS->GUSBCFG &= ~(OTG_HS_GUSBCFG_FHMOD | OTG_HS_GUSBCFG_FDMOD);

  if (mode == USB_HOST_MODE)
  {
    USB_HS->GUSBCFG |= OTG_HS_GUSBCFG_FHMOD;
    do
    {
      USB_HS_Delayms(10U);
      ms += 10U;
    }while ((USB_HS_GetMode() != (uint32_t)USB_HOST_MODE) && (ms < USB_HS_CURRENT_MODE_MAX_DELAY_MS));
  }
  else if (mode == USB_DEVICE_MODE)
  {
    USB_HS->GUSBCFG |= OTG_HS_GUSBCFG_FDMOD;
    do
    {
      USB_HS_Delayms(10U);
      ms += 10U;
    }while ((USB_HS_GetMode() != (uint32_t)USB_DEVICE_MODE) && (ms < USB_HS_CURRENT_MODE_MAX_DELAY_MS));
  }
  else
  {
    return USB_HS_ERROR;
  }
  if (ms == USB_HS_CURRENT_MODE_MAX_DELAY_MS)
  {
    return USB_HS_ERROR;
  }
  return USB_HS_OK ;
}


/**
  * @brief  USB_HS_DevInit Initializes the USB_OTG_HS controller registers
  *         for device mode
  * @param  USB_HS  Selected device
  * @param  cfg   pointer to a USB_OTG_HS_CfgTypeDef structure that contains
  *         the configuration information for the specified USB_HS peripheral.
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_DevInit(USB_OTG_HS_CfgTypeDef cfg)
{
  USB_HS_StatusTypeDef ret = USB_HS_OK ;
  uint32_t i;

  /* Device InEndpoint FIFO size Iintialize    */
  for (i = 0U; i < 15U; i++)
  {
    USB_HS->DIEPTXF[i] = 0U;
  }

  /* VBUS sensing setup */
  if (cfg.bvalid_override_enable == 1U)
  {
    USB_HS_DEVICE->DCTL |= OTG_HS_DCTL_SDIS;

    /* B-peripheral session valid override enable */
    USB_HS->GOTGCTL |= OTG_HS_GOTGCTL_BOVALEN;
    USB_HS->GOTGCTL |= OTG_HS_GOTGCTL_BOVAL;
  }
  else
  {
    /* ... */
  }

  /* Restart the Phy Clock */
  USB_HS_PCGCCTL = 0U;

  /* Device mode configuration */
  USB_HS_DEVICE->DCFG |= DCFG_FRAME_INTERVAL_80;

  if(cfg.speed == USBD_HS_SPEED)
  {
    /* Set Core speed to High speed mode */
    (void)USB_HS_SetDevSpeed(USB_OTG_SPEED_HIGH);
  }
  else
  {
    /* Set Core speed to Full speed mode */
    (void)USB_HS_SetDevSpeed(USB_OTG_SPEED_HIGH_IN_FULL);
  }

  /* Flush the FIFOs */
  if (USB_HS_FlushTxFifo(0x10U) != USB_HS_OK) /* all Tx FIFOs */
  {
    ret = USB_HS_ERROR;
  }

  if (USB_HS_FlushRxFifo() != USB_HS_OK)
  {
    ret = USB_HS_ERROR;
  }

  /* Clear all pending Device Interrupts */
  USB_HS_DEVICE->DIEPMSK = 0U;
  USB_HS_DEVICE->DOEPMSK = 0U;
  USB_HS_DEVICE->DAINTMSK = 0U;

  for (i = 0U; i < cfg.dev_endpoints; i++)
  {
    if ((USB_HS_INEP(i)->DIEPCTL & OTG_HS_DIEPCTL_EPENA) == OTG_HS_DIEPCTL_EPENA)
    {
      if (i == 0U)
      {
        USB_HS_INEP(i)->DIEPCTL = OTG_HS_DIEPCTL_SNAK;
      }
      else
      {
        USB_HS_INEP(i)->DIEPCTL = OTG_HS_DIEPCTL_EPDIS | OTG_HS_DIEPCTL_SNAK;
      }
    }
    else
    {
      USB_HS_INEP(i)->DIEPCTL = 0U;
    }

    USB_HS_INEP(i)->DIEPTSIZ = 0U;
    USB_HS_INEP(i)->DIEPINT  = 0xFB7FU;
  }

  for (i = 0U; i < cfg.dev_endpoints; i++)
  {
    if ((USB_HS_OUTEP(i)->DOEPCTL & OTG_HS_DOEPCTL_EPENA) == OTG_HS_DOEPCTL_EPENA)
    {
      if (i == 0U)
      {
        USB_HS_OUTEP(i)->DOEPCTL = OTG_HS_DOEPCTL_SNAK;
      }
      else
      {
        USB_HS_OUTEP(i)->DOEPCTL = OTG_HS_DOEPCTL_EPDIS | OTG_HS_DOEPCTL_SNAK;
      }
    }
    else
    {
      USB_HS_OUTEP(i)->DOEPCTL = 0U;
    }

    USB_HS_OUTEP(i)->DOEPTSIZ = 0U;
    USB_HS_OUTEP(i)->DOEPINT  = 0xFB7FU;
  }

  USB_HS_DEVICE->DIEPMSK &= ~(OTG_HS_DIEPMSK_TXFURM);

  /* Disable all interrupts. */
  USB_HS->GINTMSK = 0U;

  /* Clear any pending interrupts */
  USB_HS->GINTSTS = 0xBFFFFFFFU;

  /* Enable the common interrupts */
  if (cfg.dma_enable == 0U)
  {
    USB_HS->GINTMSK |= OTG_HS_GINTMSK_RXFLVLM;
  }
  /* Enable interrupts matching to the Device mode ONLY */
  USB_HS->GINTMSK |= OTG_HS_GINTMSK_USBSUSPM        | OTG_HS_GINTMSK_USBRSTM    |
                     OTG_HS_GINTMSK_ENDNEM          | OTG_HS_GINTMSK_IEPINTM    |
                     OTG_HS_GINTMSK_OEPINTM         | OTG_HS_GINTMSK_IISOIXFRM  |
                     OTG_HS_GINTMSK_PXFRM_IISOOXFRM | OTG_HS_GINTMSK_WUIM       |
                     OTG_HS_GINTMSK_SOFM            | OTG_HS_GINTMSK_OTGINTM    |
                     OTG_HS_GINTMSK_SRQIM           ;

  return ret;
}

/**
  * @brief  USB_HS_FlushTxFifo : Flush a Tx FIFO
  * @param  USB_HS  Selected device
  * @param  num  FIFO number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_FlushTxFifo(uint32_t num)
{
  __IO uint32_t count = 0U;

  /* wait for AHB master IDLE state */
  do
  {
    count++;
    if (count > USB_TIMEOUT)
    {
      return USB_HS_TIMEOUT;
    }
  } while ((USB_HS->GRSTCTL & OTG_HS_GRSTCTL_AHBIDL) == 0U);

  /* Flush TX fifo */
  count = 0U;
  USB_HS->GRSTCTL = (OTG_HS_GRSTCTL_TXFFLSH | (num << 6));

  do
  {
    count++;
    if (count > USB_TIMEOUT)
    {
      return USB_HS_TIMEOUT;
    }
  } while ((USB_HS->GRSTCTL & OTG_HS_GRSTCTL_TXFFLSH) == OTG_HS_GRSTCTL_TXFFLSH);

  return USB_HS_OK;
}

/**
  * @brief  USB_HS_FlushRxFifo : Flush Rx FIFO
  * @param  USB_HS Selected device
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_FlushRxFifo(void)
{
  __IO uint32_t count = 0U;
  /* wait for AHB master IDLE state */
  do
  {
    count++;
    if (count > USB_TIMEOUT)
    {
      return USB_HS_TIMEOUT;
    }
  } while ((USB_HS->GRSTCTL & OTG_HS_GRSTCTL_AHBIDL) == 0U);

  /* Flush RX fifo */
  count = 0U;
  USB_HS->GRSTCTL = OTG_HS_GRSTCTL_RXFFLSH ;

  do
  {
    count++;
    if (count > USB_TIMEOUT)
    {
      return USB_HS_TIMEOUT;
    }
  } while ((USB_HS->GRSTCTL & OTG_HS_GRSTCTL_RXFFLSH) == OTG_HS_GRSTCTL_RXFFLSH);

  return USB_HS_OK;
}


/**
  * @brief  USB_HS_SetDevSpeed  Initializes the DevSpd field of DCFG register
  *         depending the PHY type and the enumeration speed of the device.
  * @param  USB_HS  Selected device
  * @param  speed  device speed
  *          This parameter can be one of these values:
  *            @arg USB_OTG_SPEED_HIGH: High speed mode
  *            @arg USB_OTG_SPEED_HIGH_IN_FULL: High speed core in Full speed mode
  */
void USB_HS_SetDevSpeed(uint8_t speed)
{
  USB_HS_DEVICE->DCFG |= speed;
}

/**
  * @brief  USB_HS_GetDevSpeed  Return the Dev Speed
  * @param  USB_HS  Selected device
  * @retval speed  device speed
  *          This parameter can be one of these values:
  *            @arg PCD_SPEED_HIGH: High speed mode
  *            @arg PCD_SPEED_FULL: Full speed mode
  */
uint8_t USB_HS_GetDevSpeed(void)
{
  uint8_t speed;
  uint32_t DevEnumSpeed = USB_HS_DEVICE->DSTS & OTG_HS_DSTS_ENUMSPD;

  if (DevEnumSpeed == DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ)
  {
    speed = USBD_HS_SPEED;
  }
  else if (DevEnumSpeed == DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ)
  {
    speed = USBD_FS_SPEED;
  }
  else
  {
    speed = 0xFU;
  }

  return speed;
}


/**
  * @brief  Activate and configure an endpoint
  * @param  USB_HS  Selected device
  * @param  ep pointer to endpoint structure
  */
void USB_HS_ActivateEndpoint(USB_OTG_HS_EPTypeDef *ep)
{
  uint32_t epnum = (uint32_t)ep->num;
  /* read DI/OEPCTLn register */
  if (ep->is_in == 1U)
  {
    USB_HS_DEVICE->DAINTMSK |= OTG_HS_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK));

    if ((USB_HS_INEP(epnum)->DIEPCTL & OTG_HS_DIEPCTL_USBAEP) == 0U)
    {
      USB_HS_INEP(epnum)->DIEPCTL |= (ep->maxpacket & OTG_HS_DIEPCTL_MPSIZ) |
                                   ((uint32_t)ep->type << 18) | (epnum << 22) |
                                   OTG_HS_DIEPCTL_SD0PID_SEVNFRM |
                                   OTG_HS_DIEPCTL_USBAEP;
    }
  }
  else
  {
    USB_HS_DEVICE->DAINTMSK |= OTG_HS_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16);

    if (((USB_HS_OUTEP(epnum)->DOEPCTL) & OTG_HS_DOEPCTL_USBAEP) == 0U)
    {
      USB_HS_OUTEP(epnum)->DOEPCTL |= (ep->maxpacket & OTG_HS_DOEPCTL_MPSIZ) |
                                    ((uint32_t)ep->type << 18) |
                                    OTG_HS_DOEPCTL_SD0PID_SEVNFRM |
                                    OTG_HS_DOEPCTL_USBAEP;
    }
  }
}


/**
  * @brief  Activate and configure a dedicated endpoint
  * @param  USB_HS  Selected device
  * @param  ep pointer to endpoint structure
  */
void USB_HS_ActivateDedicatedEndpoint(USB_OTG_HS_EPTypeDef *ep)
{
  uint32_t epnum = (uint32_t)ep->num;
  /* read DI/OEPCTLn register */
  if (ep->is_in == 1U)
  {
    if ((USB_HS_INEP(epnum)->DIEPCTL & OTG_HS_DIEPCTL_USBAEP) == 0U)
    {
      USB_HS_INEP(epnum)->DIEPCTL |= (ep->maxpacket & OTG_HS_DIEPCTL_MPSIZ) |
                                     ((uint32_t)ep->type << 18) | (epnum << 22) |
                                     OTG_HS_DIEPCTL_SD0PID_SEVNFRM |
                                     OTG_HS_DIEPCTL_USBAEP;
    }
    USB_HS_DEVICE->DEACHMSK |= OTG_HS_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK));
  }
  else
  {
    if (((USB_HS_OUTEP(epnum)->DOEPCTL) & OTG_HS_DOEPCTL_USBAEP) == 0U)
    {
      USB_HS_OUTEP(epnum)->DOEPCTL |= (ep->maxpacket & OTG_HS_DOEPCTL_MPSIZ) |
                                    ((uint32_t)ep->type << 18) |
                                    OTG_HS_DOEPCTL_SD0PID_SEVNFRM |
                                    OTG_HS_DOEPCTL_USBAEP;
    }
    USB_HS_DEVICE->DEACHMSK |= OTG_HS_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16 );
  }
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  USB_HS  Selected device
  * @param  ep pointer to endpoint structure
  */
void USB_HS_DeactivateEndpoint(USB_OTG_HS_EPTypeDef *ep)
{
  uint32_t epnum = (uint32_t)ep->num;

  /* Read DI/OEPCTLn register */
  if (ep->is_in == 1U)
  {
    if ((USB_HS_INEP(epnum)->DIEPCTL & OTG_HS_DIEPCTL_EPENA) == OTG_HS_DIEPCTL_EPENA)
    {
      USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_SNAK;
      USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_EPDIS;
    }

    USB_HS_DEVICE->DEACHMSK &= ~(OTG_HS_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
    USB_HS_DEVICE->DAINTMSK &= ~(OTG_HS_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
    USB_HS_INEP(epnum)->DIEPCTL &= ~(OTG_HS_DIEPCTL_USBAEP |
                                    OTG_HS_DIEPCTL_MPSIZ |
                                    OTG_HS_DIEPCTL_TXFNUM |
                                    OTG_HS_DIEPCTL_SD0PID_SEVNFRM |
                                    OTG_HS_DIEPCTL_EPTYP);
  }
  else
  {
    if ((USB_HS_OUTEP(epnum)->DOEPCTL & OTG_HS_DOEPCTL_EPENA) == OTG_HS_DOEPCTL_EPENA)
    {
      USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_SNAK;
      USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_EPDIS;
    }

    USB_HS_DEVICE->DEACHMSK &= ~(OTG_HS_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
    USB_HS_DEVICE->DAINTMSK &= ~(OTG_HS_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
    USB_HS_OUTEP(epnum)->DOEPCTL &= ~(OTG_HS_DOEPCTL_USBAEP |
                                      OTG_HS_DOEPCTL_MPSIZ |
                                      OTG_HS_DOEPCTL_SD0PID_SEVNFRM |
                                      OTG_HS_DOEPCTL_EPTYP);
  }
}

/**
  * @brief  De-activate and de-initialize a dedicated endpoint
  * @param  USB_HS  Selected device
  * @param  ep pointer to endpoint structure
  */
void USB_HS_DeactivateDedicatedEndpoint(USB_OTG_HS_EPTypeDef *ep)
{
  uint32_t epnum = (uint32_t)ep->num;

  /* Read DI/OEPCTLn register */
  if (ep->is_in == 1U)
  {
    if ((USB_HS_INEP(epnum)->DIEPCTL & OTG_HS_DIEPCTL_EPENA) == OTG_HS_DIEPCTL_EPENA)
    {
      USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_SNAK;
      USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_EPDIS;
    }

    USB_HS_INEP(epnum)->DIEPCTL &= ~OTG_HS_DIEPCTL_USBAEP ;
    USB_HS_DEVICE->DAINTMSK &= ~(OTG_HS_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
  }
  else
  {
    if ((USB_HS_OUTEP(epnum)->DOEPCTL & OTG_HS_DOEPCTL_EPENA) == OTG_HS_DOEPCTL_EPENA)
    {
      USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_SNAK;
      USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_EPDIS;
    }

    USB_HS_OUTEP(epnum)->DOEPCTL &= ~OTG_HS_DOEPCTL_USBAEP ;
    USB_HS_DEVICE->DAINTMSK &= ~(OTG_HS_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
  }
}


/**
  * @brief  USB_HS_EPStartXfer : setup and starts a transfer over an EP
  * @param  USB_HS  Selected device
  * @param  ep pointer ro endpoint structure
  * @param  dma USB_HS enable or disable
  *         This parameter can be one of these values:
  *         0 : DMA feature not used
  *         1 : DMA feature used
  */
void USB_HS_EPStartXfer(USB_OTG_HS_EPTypeDef *ep, uint8_t dma)
{
  uint32_t epnum = (uint32_t)ep->num;
  uint16_t pktcnt;

  /* IN endpoint */
  if (ep->is_in == 1U)
  {
    /* Zero Length Packet? */
    if (ep->xfer_len == 0U)
    {
      USB_HS_INEP(epnum)->DIEPTSIZ &= ~(OTG_HS_DIEPTSIZ_PKTCNT);
      USB_HS_INEP(epnum)->DIEPTSIZ |= (OTG_HS_DIEPTSIZ_PKTCNT & (1U << 19));
      USB_HS_INEP(epnum)->DIEPTSIZ &= ~(OTG_HS_DIEPTSIZ_XFRSIZ);
    }
    else
    {
      /* Program the transfer size and packet count
      * as follows: xfersize = N * maxpacket +
      * short_packet pktcnt = N + (short_packet
      * exist ? 1 : 0)
      */
      USB_HS_INEP(epnum)->DIEPTSIZ &= ~(OTG_HS_DIEPTSIZ_XFRSIZ);
      USB_HS_INEP(epnum)->DIEPTSIZ &= ~(OTG_HS_DIEPTSIZ_PKTCNT);

      if (epnum == 0U)
      {
        if (ep->xfer_len > ep->maxpacket)
        {
          ep->xfer_len = ep->maxpacket;
        }

        USB_HS_INEP(epnum)->DIEPTSIZ |= (OTG_HS_DIEPTSIZ_PKTCNT & (1U << 19));
      }
      else
      {
        USB_HS_INEP(epnum)->DIEPTSIZ |= (OTG_HS_DIEPTSIZ_PKTCNT &
                                     (((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket) << 19));
      }

      USB_HS_INEP(epnum)->DIEPTSIZ |= (OTG_HS_DIEPTSIZ_XFRSIZ & ep->xfer_len);

      if (ep->type == EP_TYPE_ISOC)
      {
        USB_HS_INEP(epnum)->DIEPTSIZ &= ~(OTG_HS_DIEPTSIZ_MULCNT);
        USB_HS_INEP(epnum)->DIEPTSIZ |= (OTG_HS_DIEPTSIZ_MULCNT & (1U << 29));
      }
    }
    if (dma == 1U)
    {
      if ((uint32_t)ep->dma_addr != 0U)
      {
        USB_HS_INEP(epnum)->DIEPDMA = (uint32_t)(ep->dma_addr);
      }
      if (ep->type == EP_TYPE_ISOC)
      {
        /* SOF frame is odd or even */
        if ((USB_HS_DEVICE->DSTS & (1U << 8)) == 0U)
        {
          USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_SODDFRM;
        }
        else
        {
          USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_SD0PID_SEVNFRM;
        }
      }
      /* EP enable, IN data in FIFO */
      USB_HS_INEP(epnum)->DIEPCTL |= (OTG_HS_DIEPCTL_CNAK | OTG_HS_DIEPCTL_EPENA);
    }
    else
    {
      /* EP enable, IN data in FIFO */
      USB_HS_INEP(epnum)->DIEPCTL |= (OTG_HS_DIEPCTL_CNAK | OTG_HS_DIEPCTL_EPENA);

      if (ep->type != EP_TYPE_ISOC)
      {
        /* Enable the Tx FIFO Empty Interrupt for this EP */
        if (ep->xfer_len > 0U)
        {
          USB_HS_DEVICE->DIEPEMPMSK |= 1UL << (ep->num & EP_ADDR_MSK);
        }
      }
      else
      {
        if ((USB_HS_DEVICE->DSTS & (1U << 8)) == 0U)
        {
          USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_SODDFRM;
        }
        else
        {
          USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_SD0PID_SEVNFRM;
        }
        USB_HS_WritePacket(ep->xfer_buff, ep->num, (uint16_t)ep->xfer_len, dma);
      }
    }
  }
  else /* OUT endpoint */
  {
    /* Program the transfer size and packet count as follows:
    * pktcnt = N
    * xfersize = N * maxpacket
    */
    USB_HS_OUTEP(epnum)->DOEPTSIZ &= ~(OTG_HS_DOEPTSIZ_XFRSIZ);
    USB_HS_OUTEP(epnum)->DOEPTSIZ &= ~(OTG_HS_DOEPTSIZ_PKTCNT);

    if (epnum == 0U)
    {
      if (ep->xfer_len > 0U)
      {
        ep->xfer_len = ep->maxpacket;
      }

      /* store transfer size, for EP0 this is equal to endpoint max packet size */
      ep->xfer_size = ep->maxpacket;

      USB_HS_OUTEP(epnum)->DOEPTSIZ |= (OTG_HS_DOEPTSIZ_XFRSIZ & ep->xfer_size);
      USB_HS_OUTEP(epnum)->DOEPTSIZ |= (OTG_HS_DOEPTSIZ_PKTCNT & (1U << 19));
    }
    else
    {
      if (ep->xfer_len == 0U)
      {
        USB_HS_OUTEP(epnum)->DOEPTSIZ |= (OTG_HS_DOEPTSIZ_XFRSIZ & ep->maxpacket);
        USB_HS_OUTEP(epnum)->DOEPTSIZ |= (OTG_HS_DOEPTSIZ_PKTCNT & (1U << 19));
      }
      else
      {
        pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
        ep->xfer_size = ep->maxpacket * pktcnt;

        USB_HS_OUTEP(epnum)->DOEPTSIZ |= OTG_HS_DOEPTSIZ_PKTCNT & ((uint32_t)pktcnt << 19);
        USB_HS_OUTEP(epnum)->DOEPTSIZ |= OTG_HS_DOEPTSIZ_XFRSIZ & (ep->xfer_size);
      }
    }

    if (dma == 1U)
    {
      if ((uint32_t)ep->xfer_buff != 0U)
      {
        USB_HS_OUTEP(epnum)->DOEPDMA = (uint32_t)(ep->xfer_buff);
      }
    }
    if (ep->type == EP_TYPE_ISOC)
    {
      /* SOF frame is odd or even */
      if ((USB_HS_DEVICE->DSTS & (1U << 8)) == 0U)
      {
        USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_SODDFRM;
      }
      else
      {
        USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_SD0PID_SEVNFRM;
      }
    }
    /* EP enable */
    USB_HS_OUTEP(epnum)->DOEPCTL |= (OTG_HS_DOEPCTL_CNAK | OTG_HS_DOEPCTL_EPENA);
  }
}

/**
  * @brief  USB_HS_EPStopXfer : Stop transfer on an EP
  * @param  USB_HS  Selected device
  * @param  ep pointer to endpoint structure
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_EPStopXfer(USB_OTG_HS_EPTypeDef *ep)
{
  __IO uint32_t count = 0U;
  USB_HS_StatusTypeDef ret = USB_HS_OK;

  /* IN endpoint */
  if (ep->is_in == 1U)
  {
    /* EP enable, IN data in FIFO */
    if (((USB_HS_INEP(ep->num)->DIEPCTL) & OTG_HS_DIEPCTL_EPENA) == OTG_HS_DIEPCTL_EPENA)
    {
      USB_HS_INEP(ep->num)->DIEPCTL |= (OTG_HS_DIEPCTL_SNAK);
      USB_HS_INEP(ep->num)->DIEPCTL |= (OTG_HS_DIEPCTL_EPDIS);

      do
      {
        count++;
        if (count > 10000U)
        {
          ret = USB_HS_ERROR;
          break;
        }
      }while (((USB_HS_INEP(ep->num)->DIEPCTL) & OTG_HS_DIEPCTL_EPENA) == OTG_HS_DIEPCTL_EPENA);
    }
  }
  else /* OUT endpoint */
  {
    if (((USB_HS_OUTEP(ep->num)->DOEPCTL) & OTG_HS_DOEPCTL_EPENA) == OTG_HS_DOEPCTL_EPENA)
    {
      USB_HS_OUTEP(ep->num)->DOEPCTL |= (OTG_HS_DOEPCTL_SNAK);
      USB_HS_OUTEP(ep->num)->DOEPCTL |= (OTG_HS_DOEPCTL_EPDIS);

      do
      {
        count++;
        if (count > 10000U)
        {
          ret = USB_HS_ERROR;
          break;
        }
      }while (((USB_HS_OUTEP(ep->num)->DOEPCTL) & OTG_HS_DOEPCTL_EPENA) == OTG_HS_DOEPCTL_EPENA);
    }
  }
  return ret;
}

/**
  * @brief  USB_HS_WritePacket : Writes a packet into the Tx FIFO associated
  *         with the EP/channel
  * @param  USB_HS  Selected device
  * @param  src   pointer to source buffer
  * @param  ch_ep_num  endpoint or host channel number
  * @param  len  Number of bytes to write
  * @param  dma USB dma enabled or disabled
  *         This parameter can be one of thes values:
  *         0 : DMA feature not used
  *         1 : DMA feature used
  */
void USB_HS_WritePacket(uint8_t *src, uint8_t ch_ep_num, uint16_t len, uint8_t dma)
{
  uint8_t *pSrc = src;
  uint32_t count32b;
  uint32_t i;

  if (dma == 0U)
  {
    count32b = ((uint32_t)len + 3U) / 4U;
    for (i = 0U; i < count32b; i++)
    {
      USB_HS_DFIFO((uint32_t)ch_ep_num) = __UNALIGNED_UINT32_READ(pSrc);
      pSrc++;
      pSrc++;
      pSrc++;
      pSrc++;
    }
  }
}


/**
  * @brief  USB_HS_ReadPacket : read a packet from the RX FIFO
  * @param  USB_HS  Selected device
  * @param  dest  source pointer
  * @param  len  Number of bytes to read
  * @retval pointer to destination buffer
  */
void *USB_HS_ReadPacket(uint8_t *dest, uint16_t len)
{
  uint8_t *pDest = dest;
  uint32_t pData;
  uint32_t i;
  uint32_t count32b = (uint32_t)len >> 2U;
  uint16_t remaining_bytes = len % 4U;

  for (i = 0U; i < count32b; i++)
  {
    __UNALIGNED_UINT32_WRITE(pDest, USB_HS_DFIFO(0U));
    pDest++;
    pDest++;
    pDest++;
    pDest++;
  }
  /* when number of data is not word aligned, read the remaining byte */
  if (remaining_bytes != 0U)
  {
    i = 0U;
    __UNALIGNED_UINT32_WRITE(&pData, USB_HS_DFIFO(0U));

    do
    {
       *(uint8_t *)pDest = (uint8_t)(pData >> (8U * (uint8_t)(i)));
      i++;
      pDest++;
      remaining_bytes--;
    }while (remaining_bytes != 0U);
  }
  return ((void *)pDest);
}


/**
  * @brief  USB_HS_EPSetStall : set a stall condition over an EP
  * @param  USB_HS  Selected device
  * @param  ep pointer to endpoint structure
  */
void USB_HS_EPSetStall(USB_OTG_HS_EPTypeDef *ep)
{
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    if (((USB_HS_INEP(epnum)->DIEPCTL & OTG_HS_DIEPCTL_EPENA) == 0U) && (epnum != 0U))
    {
      USB_HS_INEP(epnum)->DIEPCTL &= ~(OTG_HS_DIEPCTL_EPDIS);
    }
    USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_STALL;
  }
  else
  {
    if (((USB_HS_OUTEP(epnum)->DOEPCTL & OTG_HS_DOEPCTL_EPENA) == 0U) && (epnum != 0U))
    {
      USB_HS_OUTEP(epnum)->DOEPCTL &= ~(OTG_HS_DOEPCTL_EPDIS);
    }
    USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_STALL;
  }
}

/**
  * @brief  USB_HS_EPClearStall : Clear a stall condition over an EP
  * @param  USB_HS  Selected device
  * @param  ep pointer to endpoint structure
  */
void USB_HS_EPClearStall(USB_OTG_HS_EPTypeDef *ep)
{
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    USB_HS_INEP(epnum)->DIEPCTL &= ~OTG_HS_DIEPCTL_STALL;
    if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
    {
      USB_HS_INEP(epnum)->DIEPCTL |= OTG_HS_DIEPCTL_SD0PID_SEVNFRM; /* DATA0 */
    }
  }
  else
  {
    USB_HS_OUTEP(epnum)->DOEPCTL &= ~OTG_HS_DOEPCTL_STALL;
    if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
    {
      USB_HS_OUTEP(epnum)->DOEPCTL |= OTG_HS_DOEPCTL_SD0PID_SEVNFRM; /* DATA0 */
    }
  }
}


/**
  * @brief  USB_HS_StopDevice : Stop the usb device mode
  * @param  USB_HS  Selected device
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_StopDevice(void)
{
  USB_HS_StatusTypeDef ret;
  uint32_t i;

  /* Clear Pending interrupt */
  for (i = 0U; i < 15U; i++)
  {
    USB_HS_INEP(i)->DIEPINT = 0xFB7FU;
    USB_HS_OUTEP(i)->DOEPINT = 0xFB7FU;
  }

  /* Clear interrupt masks */
  USB_HS_DEVICE->DIEPMSK  = 0U;
  USB_HS_DEVICE->DOEPMSK  = 0U;
  USB_HS_DEVICE->DAINTMSK = 0U;

  /* Flush the FIFO */
  ret = USB_HS_FlushRxFifo();
  if (ret != USB_HS_OK)
  {
    return ret;
  }

  ret = USB_HS_FlushTxFifo(0x10U);
  if (ret != USB_HS_OK)
  {
    return ret;
  }

  return ret;
}

/**
  * @brief  USB_HS_SetDevAddress : set device address
  * @param  USB_HS  Selected device
  * @param  address  new device address to be assigned
  *          This parameter can be a value from 0 to 255
  */
void  USB_HS_SetDevAddress(uint8_t address)
{
  USB_HS_DEVICE->DCFG &= ~(OTG_HS_DCFG_DAD);
  USB_HS_DEVICE->DCFG |= ((uint32_t)address << 4) & OTG_HS_DCFG_DAD;
}

/**
  * @brief  USB_HS_DevConnect : Connect the USB device by enabling Rpu
  * @param  USB_HS  Selected device
  */
void  USB_HS_DevConnect(void)
{
  /* In case phy is stopped, ensure to ungate and restore the phy CLK */
  USB_HS_PCGCCTL &= ~(OTG_HS_PCGCCTL_STOPCLK | OTG_HS_PCGCCTL_GATECLK);

  /* disable software disconnect */
  USB_HS_DEVICE->DCTL &= ~OTG_HS_DCTL_SDIS;

}


/**
  * @brief  USB_HS_DevDisconnect : Disconnect the USB device by disabling Rpu
  * @param  USB_HS  Selected device
  * @retval none
  */
void  USB_HS_DevDisconnect(void)
{
  /* In case phy is stopped, ensure to ungate and restore the phy CLK */
  USB_HS_PCGCCTL &= ~(OTG_HS_PCGCCTL_STOPCLK | OTG_HS_PCGCCTL_GATECLK);
  /* enable software disconnect */
  USB_HS_DEVICE->DCTL |= OTG_HS_DCTL_SDIS;

}

/**
  * @brief  USB_HS_ReadInterrupts: return the global USB interrupt status
  * @param  USB_HS  Selected device
  * @retval global interrupt register
  */
uint32_t  USB_HS_ReadInterrupts(void)
{
  uint32_t tmpreg;

  tmpreg = USB_HS->GINTSTS;
  tmpreg &= USB_HS->GINTMSK;

  return tmpreg;
}

/**
  * @brief  USB_HS_ReadChInterrupts: return the USB channel interrupt status
  * @param  USB_HS  Selected device
  * @param  chnum channel number
  * @retval USB HS Channel interrupt register
  */
uint32_t  USB_HS_ReadChInterrupts(uint8_t chnum)
{
  uint32_t tmpreg;

  tmpreg = USB_HS_HC(chnum)->HCINT;
  tmpreg &= USB_HS_HC(chnum)->HCINTMSK;

  return tmpreg;
}


/**
  * @brief  USB_HS_ReadDevAllOutEpInterrupt: return the USB device OUT endpoints interrupt status
  * @param  USB_HS  Selected device
  * @retval USB Device OUT EP interrupt status
  */
uint32_t USB_HS_ReadDevAllOutEpInterrupt(void)
{
  uint32_t tmpreg;

  tmpreg  = USB_HS_DEVICE->DAINT;
  tmpreg &= USB_HS_DEVICE->DAINTMSK;

  return ((tmpreg & 0xffff0000U) >> 16);
}

/**
  * @brief  USB_HS_ReadDevAllInEpInterrupt: return the USB device IN endpoints interrupt status
  * @param  USB_HS  Selected device
  * @retval USB Device IN EP interrupt status
  */
uint32_t USB_HS_ReadDevAllInEpInterrupt(void)
{
  uint32_t tmpreg;

  tmpreg  = USB_HS_DEVICE->DAINT;
  tmpreg &= USB_HS_DEVICE->DAINTMSK;

  return ((tmpreg & 0xFFFFU));
}

/**
  * @brief  Returns Device OUT EP Interrupt register
  * @param  USB_HS  Selected device
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device OUT EP Interrupt register
  */
uint32_t USB_HS_ReadDevOutEPInterrupt(uint8_t epnum)
{
  uint32_t tmpreg;

  tmpreg  = USB_HS_OUTEP((uint32_t)epnum)->DOEPINT;
  tmpreg &= USB_HS_DEVICE->DOEPMSK;

  return tmpreg;
}

/**
  * @brief  Returns Device IN EP Interrupt register
  * @param  USB_HS  Selected device
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device IN EP Interrupt register
  */
uint32_t USB_HS_ReadDevInEPInterrupt(uint8_t epnum)
{
  uint32_t tmpreg;
  uint32_t msk;
  uint32_t emp;

  msk = USB_HS_DEVICE->DIEPMSK;
  emp = USB_HS_DEVICE->DIEPEMPMSK;
  msk |= ((emp >> (epnum & EP_ADDR_MSK)) & 0x1U) << 7;
  tmpreg = USB_HS_INEP((uint32_t)epnum)->DIEPINT & msk;

  return tmpreg;
}

/**
  * @brief  USB_HS_ClearInterrupts: clear a USB interrupt
  * @param  USB_HS  Selected device
  * @param  interrupt  flag
  * @retval None
  */
void  USB_HS_ClearInterrupts(uint32_t interrupt)
{
  USB_HS->GINTSTS &= interrupt;
}

/**
  * @brief  Returns USB_HS core mode
  * @param  USB_HS  Selected device
  * @retval return core mode : Host or Device
  *          This parameter can be one of these values:
  *           0 : Host
  *           1 : Device
  */
uint32_t USB_HS_GetMode(void)
{
  return ((USB_HS->GINTSTS) & 0x1U);
}

/**
  * @brief  Activate EP0 for Setup transactions
  * @param  USB_HS  Selected device
  */
void  USB_HS_ActivateSetup(void)
{

  /* Set the MPS of the IN EP0 to 64 bytes */
  USB_HS_INEP(0U)->DIEPCTL &= ~OTG_HS_DIEPCTL_MPSIZ;

  USB_HS_DEVICE->DCTL |= OTG_HS_DCTL_CGINAK;

}

/**
  * @brief  Prepare the EP0 to start the first control setup
  * @param  USB_HS  Selected device
  * @param  dma USB_HS enabled or disabled
  *         This parameter can be one of these values:
  *         0 : DMA feature not used
  *         1 : DMA deature used
  * @param  psetup  pointer to setup packet
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_EP0_OutStart(uint8_t dma, uint8_t *psetup)
{
  if ((USB_HS_OUTEP(0U)->DOEPCTL & OTG_HS_DOEPCTL_EPENA) == OTG_HS_DOEPCTL_EPENA)
  {
    return USB_HS_OK;
  }

  USB_HS_OUTEP(0U)->DOEPTSIZ = 0U;
  USB_HS_OUTEP(0U)->DOEPTSIZ |= (OTG_HS_DOEPTSIZ_PKTCNT & (1U << 19));
  USB_HS_OUTEP(0U)->DOEPTSIZ |= (3U * 8U);
  USB_HS_OUTEP(0U)->DOEPTSIZ |=  OTG_HS_DOEPTSIZ_STUPCNT;

  if (dma == 1U)
  {
    USB_HS_OUTEP(0U)->DOEPDMA = (uint32_t)psetup;
    /* EP enable */
    USB_HS_OUTEP(0U)->DOEPCTL |= (OTG_HS_DOEPCTL_EPENA | OTG_HS_DOEPCTL_USBAEP);
  }

  return USB_HS_OK;
}

/**
  * @brief  Reset the USB_HS Core (needed after USB clock settings change)
  * @param  USB_HS  Selected device
  * @retval USB_HS status
  */
static USB_HS_StatusTypeDef USB_HS_CoreReset(void)
{
  __IO uint32_t count = 0U;

  /* Wait for AHB master IDLE state. */
  do
  {
    count++;

    if (count > USB_TIMEOUT)
    {
      return USB_HS_TIMEOUT;
    }
  } while ((USB_HS->GRSTCTL & OTG_HS_GRSTCTL_AHBIDL) == 0U);

  /* Core Soft Reset */
  count = 0U;
  USB_HS->GRSTCTL |= OTG_HS_GRSTCTL_CSRST;

  do
  {
    count++;

    if (count > USB_TIMEOUT)
    {
      return USB_HS_TIMEOUT;
    }
  } while ((USB_HS->GRSTCTL & OTG_HS_GRSTCTL_CSRST) == OTG_HS_GRSTCTL_CSRST);

  return USB_HS_OK;
}

/**
  * @brief  USB_HS_HostInit : Initializes the USB OTG controller registers
  *         for Host mode
  * @param  USB_HS  Selected device
  * @param  cfg   pointer to a USB_OTG_HS_CfgTypeDef structure that contains
  *         the configuration information for the specified USB_HS peripheral.
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_HostInit(USB_OTG_HS_CfgTypeDef cfg)
{
  USB_HS_StatusTypeDef ret = USB_HS_OK;
  uint32_t i;

  /* Restart the Phy Clock */
  USB_HS_PCGCCTL = 0U;

  if ((USB_HS->GUSBCFG & OTG_HS_GUSBCFG_PHSEL) == 0U)
  {
    if (cfg.speed == USBH_FSLS_SPEED)
    {
      /* Force device enumeration to FS/LS mode only */
      USB_HS_HOST->HCFG |= OTG_HS_HCFG_FSLSS;
    }
    else
    {
      /* Set default Max speed support */
      USB_HS_HOST->HCFG &= ~(OTG_HS_HCFG_FSLSS);
    }
  }
  else
  {
    ret = USB_HS_ERROR;
  }

  /* Make sure the FIFOs are flushed. */
  if (USB_HS_FlushTxFifo(0x10U) != USB_HS_OK)  /* all Tx FIFOs */
  {
    ret = USB_HS_ERROR ;
  }
  if (USB_HS_FlushRxFifo() != USB_HS_OK)  /* Rx FIFO */
  {
    ret = USB_HS_ERROR ;
  }

  /* Clear all pending HC Interrupts */
  for (i = 0U; i < cfg.Host_channels; i++)
  {
    USB_HS_HC(i)->HCINT = CLEAR_INTERRUPT_MASK;
    USB_HS_HC(i)->HCINTMSK = 0U;
  }

  /* Enable VBUS driving */
//  (void)USB_HS_DriveVbus(1U);
//  USB_HS_Delayms(200U);

  /* Disable all interrupts. */
  USB_HS->GINTMSK = 0U;

  /* Clear any pending interrupts */
  USB_HS->GINTSTS = CLEAR_INTERRUPT_MASK;

  /* set Rx FIFO size */
  USB_HS->GRXFSIZ  = 0x200U;
  USB_HS->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x100U << 16) & OTG_HS_HNPTXFSIZ_NPTXFD) | 0x200U);
  USB_HS->HPTXFSIZ = (uint32_t)(((0xE0U << 16)& OTG_HS_HPTXFSIZ_PTXFD) | 0x300U);

  /* Enable the common interrupts */
  if (cfg.dma_enable == 0U)
  {
    USB_HS->GINTMSK |= OTG_HS_GINTMSK_RXFLVLM;
  }
  /* Enable interrupts matching to the Host mode ONLY */
  USB_HS->GINTMSK |= (OTG_HS_GINTMSK_PRTIM            | OTG_HS_GINTMSK_HCIM     | \
                      OTG_HS_GINTMSK_SOFM             | OTG_HS_GINTMSK_DISCINTM | \
                      OTG_HS_GINTMSK_PXFRM_IISOOXFRM  | OTG_HS_GINTMSK_WUIM     );

  return ret;
}

/**
  * @brief  USB_HS_InitFSLSPClkSel : Initializes the FSLSPClkSel field of the
  *         HCFG register on the PHY type and set the right frame interval
  * @param  USB_HS  Selected device
  * @param  freq  clock frequency
  *          This parameter can be one of these values:
  *           HCFG_48_MHZ : Full Speed 48 MHz Clock
  *           HCFG_6_MHZ : Low Speed 6 MHz Clock
  * @retval USB_HS status
  */
USB_HS_StatusTypeDef USB_HS_InitFSLSPClkSel(uint8_t freq)
{

  USB_HS_HOST->HCFG &= ~(OTG_HS_HCFG_FSLSPCS);
  USB_HS_HOST->HCFG |= (uint32_t)freq & OTG_HS_HCFG_FSLSPCS;

  if (freq == HCFG_48_MHZ)
  {
    USB_HS_HOST->HFIR = 48000U;
  }
  else if (freq == HCFG_6_MHZ)
  {
    USB_HS_HOST->HFIR = 6000U;
  }
  else
  {
    return USB_HS_ERROR;
  }

  return USB_HS_OK;

}

/**
  * @brief  USB_OTG_ResetPort : Reset Host Port
  * @param  USB_HS  Selected device
  * @note (1)The application must wait at least 10 ms
  *   before clearing the reset bit.
  */
void USB_HS_ResetPort(void)
{

  __IO uint32_t hprt0 = 0U;
  __IO uint32_t num = 100;

  hprt0 = USB_HS_HPRT0;

  hprt0 &= ~(OTG_HS_HPRT_PENA | OTG_HS_HPRT_PCDET |
             OTG_HS_HPRT_PENCHNG | OTG_HS_HPRT_POCCHNG);
  
  USB_HS_HPRT0 = (OTG_HS_HPRT_PRST | hprt0);
  while(num--)  /* update delay 20ms */
  {
    SysTick->LOAD = SystemCoreClock / 1000;
    SysTick->VAL = 0x00;
    SysTick->CTRL = 0x00000005;

    while(!(SysTick->CTRL & 0x00010000));

    SysTick->CTRL = 0x00000004;
  }                                 /* See Note #1 */

  USB_HS_HPRT0 = ((~OTG_HS_HPRT_PRST) & hprt0);
  USB_HS_Delayms(10U);
    
}

/**
  * @brief  USB_HS_DriveVbus : activate or de-activate vbus
  * @param  state  VBUS state
  *          This parameter can be one of these values:
  *           0 : Deactivate VBUS
  *           1 : Activate VBUS
  */
void USB_HS_DriveVbus(uint8_t state)
{
  __IO uint32_t hprt0 = 0U;

  hprt0 = USB_HS_HPRT0;

  hprt0 &= ~(OTG_HS_HPRT_PENA | OTG_HS_HPRT_PCDET |
             OTG_HS_HPRT_PENCHNG | OTG_HS_HPRT_POCCHNG);

  if (((hprt0 & OTG_HS_HPRT_PPWR) == 0U) && (state == 1U))
  {
    USB_HS_HPRT0 = (OTG_HS_HPRT_PPWR | hprt0);
  }
  if (((hprt0 & OTG_HS_HPRT_PPWR) == OTG_HS_HPRT_PPWR) && (state == 0U))
  {
    USB_HS_HPRT0 = ((~OTG_HS_HPRT_PPWR) & hprt0);
  }
}

/**
  * @brief  USB_HS_DriveID : activate or de-activate id
  * @param  state  VBUS state
  *          This parameter can be one of these values:
  *           0 : Deactivate ID
  *           1 : Activate ID
  * @note   To use ID line detection, this function must be enabled; it is enabled by default. 
  *         This function is connected to pin PB12. If PB12 is to use normal GPIO functions, 
  *         this function must be disabled.
  */
void USB_HS_DriveID(uint8_t state)
{
  USB_HS_PKEY = 0x5057 ;
  USB_HS_PKEY = 0x5948 ;

  *(uint32_t*)(0x40040E1C) |= (state << 25);

  USB_HS_PKEY = 0x0;
}

/**
  * @brief  Return Host Core speed
  * @param  USB_HS  Selected device
  * @retval speed : Host speed
  *          This parameter can be one of these values:
  *            @arg HCD_SPEED_HIGH: Full speed mode
  *            @arg HCD_SPEED_FULL: Full speed mode
  *            @arg HCD_SPEED_LOW: Low speed mode
  */
uint32_t USB_HS_GetHostSpeed(void)
{
  __IO uint32_t hprt0 = 0U;

  hprt0 = USB_HS_HPRT0;
  return ((hprt0 & OTG_HS_HPRT_PSPD) >> 17);
}

/**
  * @brief  Return Host Current Frame number
  * @param  USB_HS  Selected device
  * @retval current frame number
  */
uint32_t USB_HS_GetCurrentFrame(void)
{
  return (USB_HS_HOST->HFNUM & OTG_HS_HFNUM_FRNUM);
}

/**
  * @brief  Initialize a host channel
  * @param  USB_HS  Selected device
  * @param  ch_num  Channel number
  *         This parameter can be a value from 1 to 15
  * @param  epnum  Endpoint number
  *          This parameter can be a value from 1 to 15
  * @param  dev_address  Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed  Current device speed
  *          This parameter can be one of these values:
  *            @arg USB_OTG_SPEED_FULL: HIGH speed mode
  *            @arg USB_OTG_SPEED_FULL: Full speed mode
  *            @arg USB_OTG_SPEED_LOW: Low speed mode
  * @param  ep_type  Endpoint Type
  *          This parameter can be one of these values:
  *            @arg EP_TYPE_CTRL: Control type
  *            @arg EP_TYPE_ISOC: Isochronous type
  *            @arg EP_TYPE_BULK: Bulk type
  *            @arg EP_TYPE_INTR: Interrupt type
  * @param  mps  Max Packet Size
  *          This parameter can be a value from 0 to 32K
  * @retval USB_HS state
  */
USB_HS_StatusTypeDef USB_HS_HC_Init(uint8_t ch_num, uint8_t epnum, uint8_t dev_address,
                                    uint8_t speed, uint8_t ep_type, uint16_t mps)
{
  USB_HS_StatusTypeDef ret = USB_HS_OK;
  uint32_t HCcharEpDir;
  uint32_t HCcharLowSpeed;
  uint32_t HostCoreSpeed;

  /* Clear old interrupt conditions for this host channel. */
  USB_HS_HC((uint32_t)ch_num)->HCINT = CLEAR_INTERRUPT_MASK;

  /* Enable channel interrupts required for this transfer. */
  switch (ep_type)
  {
    case EP_TYPE_CTRL:
    case EP_TYPE_BULK:
      USB_HS_HC((uint32_t)ch_num)->HCINTMSK = OTG_HS_HCINTMSK_XFRCM   |
                                              OTG_HS_HCINTMSK_STALLM  |
                                              OTG_HS_HCINTMSK_TXERRM  |
                                              OTG_HS_HCINTMSK_DTERRM  |
                                              OTG_HS_HCINTMSK_AHBERRM |
                                              OTG_HS_HCINTMSK_NAKM;

      if ((epnum & 0x80U) == 0x80U)
      {
        USB_HS_HC((uint32_t)ch_num)->HCINTMSK |= OTG_HS_HCINTMSK_BBERRM;
      }
      else
      {
        USB_HS_HC((uint32_t)ch_num)->HCINTMSK |= (OTG_HS_HCINTMSK_NYETM | OTG_HS_HCINTMSK_ACKM);
      }
      break;

    case EP_TYPE_INTR:
      USB_HS_HC((uint32_t)ch_num)->HCINTMSK = OTG_HS_HCINTMSK_XFRCM   |
                                              OTG_HS_HCINTMSK_STALLM  |
                                              OTG_HS_HCINTMSK_TXERRM  |
                                              OTG_HS_HCINTMSK_DTERRM  |
                                              OTG_HS_HCINTMSK_NAKM    |
                                              OTG_HS_HCINTMSK_AHBERRM |
                                              OTG_HS_HCINTMSK_FRMORM  ;

      if ((epnum & 0x80U) == 0x80U)
      {
        USB_HS_HC((uint32_t)ch_num)->HCINTMSK |= OTG_HS_HCINTMSK_BBERRM;
      }

      break;

    case EP_TYPE_ISOC:
      USB_HS_HC((uint32_t)ch_num)->HCINTMSK = OTG_HS_HCINTMSK_XFRCM   |
                                              OTG_HS_HCINTMSK_ACKM    |
                                              OTG_HS_HCINTMSK_AHBERRM |
                                              OTG_HS_HCINTMSK_FRMORM  ;

      if ((epnum & 0x80U) == 0x80U)
      {
        USB_HS_HC((uint32_t)ch_num)->HCINTMSK |= (OTG_HS_HCINTMSK_TXERRM | OTG_HS_HCINTMSK_BBERRM);
      }
      break;

    default:
      ret = USB_HS_ERROR;
      break;
  }

  /* Clear Hub Start Split transaction */
  USB_HS_HC((uint32_t)ch_num)->HCSPLT = 0U;

  /* Enable host channel Halt interrupt */
  USB_HS_HC((uint32_t)ch_num)->HCINTMSK |= OTG_HS_HCINTMSK_CHHM;

  /* Enable the top level host channel interrupt. */
  USB_HS_HOST->HAINTMSK |= 1UL << (ch_num & 0xFU);

  /* Make sure host channel interrupts are enabled. */
  USB_HS->GINTMSK |= OTG_HS_GINTMSK_HCIM;

  /* Program the HCCHAR register */
  if ((epnum & 0x80U) == 0x80U)
  {
    HCcharEpDir = (0x1U << 15) & OTG_HS_HCCHAR_EPDIR;
  }
  else
  {
    HCcharEpDir = 0U;
  }

  HostCoreSpeed = USB_HS_GetHostSpeed();

  /* LS device plugged to HUB */
  if ((speed == HPRT0_PRTSPD_LOW_SPEED) && (HostCoreSpeed != HPRT0_PRTSPD_LOW_SPEED))
  {
    HCcharLowSpeed = (0x1U << 17) & OTG_HS_HCCHAR_LSDEV;
  }
  else
  {
    HCcharLowSpeed = 0U;
  }

  USB_HS_HC((uint32_t)ch_num)->HCCHAR = (((uint32_t)dev_address << 22) & OTG_HS_HCCHAR_DAD) |
                                        ((((uint32_t)epnum & 0x7FU) << 11) & OTG_HS_HCCHAR_EPNUM) |
                                        (((uint32_t)ep_type << 18) & OTG_HS_HCCHAR_EPTYP) |
                                        ((uint32_t)mps & OTG_HS_HCCHAR_MPSIZ) | OTG_HS_HCCHAR_MEC_0 |
                                        HCcharEpDir | HCcharLowSpeed;

  if ((ep_type == EP_TYPE_INTR) || (ep_type == EP_TYPE_ISOC))
  {
    USB_HS_HC((uint32_t)ch_num)->HCCHAR |= OTG_HS_HCCHAR_ODDFRM ;
  }

  return ret;
}

/**
  * @brief  Start a transfer over a host channel
  * @param  USB_HS  Selected device
  * @param  hc  pointer to host channel structure
  * @param  dma USB_HS enable or disabled
  *         This parameter can be one of these values:
  *         0 : DMA feature not used
  *         1 : DMA feature used
  */
void USB_HS_HC_StartXfer(USB_OTG_HS_HCTypeDef *hc, uint8_t dma)
{
  uint32_t ch_num = (uint32_t)hc->ch_num;
  __IO uint32_t tmpreg;
  uint8_t  is_oddframe;
  uint16_t len_words;
  uint16_t num_packets;
  uint16_t max_hc_pkt_count = HC_MAX_PKT_CNT;

  if (dma == 1U)
  {
    if (((hc->ep_type == EP_TYPE_CTRL) || (hc->ep_type == EP_TYPE_BULK)) && (hc->do_ssplit == 0U))
    {
      USB_HS_HC((uint32_t)ch_num)->HCINTMSK &= ~( OTG_HS_HCINTMSK_NYETM |
                                                  OTG_HS_HCINTMSK_ACKM  |
                                                  OTG_HS_HCINTMSK_NAKM  );
    }
  }
  else
  {
    if ((hc->speed == USBH_HS_SPEED) && (hc->do_ping == 1U))
    {
      (void)USB_HS_DoPing(hc->ch_num);

    }
  }

  if (hc->do_ssplit == 1U)
  {
    /* Set number of packet to 1 for Split transaction */
    num_packets = 1U;
    if (hc->ep_is_in != 0U)
    {
      hc->XferSize = (uint32_t)num_packets * hc->max_packet;
    }
    else
    {
      if (hc->ep_type == EP_TYPE_ISOC)
      {
        if (hc->xfer_len > ISO_SPLT_MPS)
        {
          /* Isochrone Max Packet Size for Split mode */
          hc->XferSize = hc->max_packet;
          hc->xfer_len = hc->XferSize;

          if ((hc->iso_splt_xactPos == HCSPLT_BEGIN) || (hc->iso_splt_xactPos == HCSPLT_MIDDLE))
          {
            hc->iso_splt_xactPos = HCSPLT_MIDDLE;
          }
          else
          {
            hc->iso_splt_xactPos = HCSPLT_BEGIN;
          }
        }
        else
        {
          hc->XferSize = hc->xfer_len;

          if ((hc->iso_splt_xactPos != HCSPLT_BEGIN) && (hc->iso_splt_xactPos != HCSPLT_MIDDLE))
          {
            hc->iso_splt_xactPos = HCSPLT_FULL;
          }
          else
          {
            hc->iso_splt_xactPos = HCSPLT_END;
          }
        }
      }
      else
      {
        if ((dma == 1U) && (hc->xfer_len > hc->max_packet))
        {
          hc->XferSize = (uint32_t)num_packets * hc->max_packet;
        }
        else
        {
          hc->XferSize = hc->xfer_len;
        }
      }
    }
  }
  else
  {
    /* Compute the expected number of packets associated to the transfer */
    if (hc->xfer_len > 0U)
    {
      num_packets = (uint16_t)((hc->xfer_len + hc->max_packet - 1U) / hc->max_packet);

      if (num_packets > max_hc_pkt_count)
      {
        num_packets = max_hc_pkt_count;
        hc->XferSize = (uint32_t)num_packets * hc->max_packet;
      }
    }
    else
    {
      num_packets = 1U;
    }

    /*
     * For IN channel HCTSIZ.XferSize is expected to be an integer multiple of
     * max_packet size.
     */
    if (hc->ep_is_in != 0U)
    {
      hc->XferSize = (uint32_t)num_packets * hc->max_packet;
    }
    else
    {
      hc->XferSize = hc->xfer_len;
    }
  }

  /* Initialize the HCTSIZn register */
  USB_HS_HC(ch_num)->HCTSIZ = (hc->XferSize & OTG_HS_HCTSIZ_XFRSIZ) |
                              (((uint32_t)num_packets << 19) & OTG_HS_HCTSIZ_PKTCNT) |
                              (((uint32_t)hc->data_pid << 29) & OTG_HS_HCTSIZ_DPID);

  if (dma != 0U)
  {
    /* xfer_buff MUST be 32-bits aligned */
    USB_HS_HC(ch_num)->HCDMA = (uint32_t)hc->xfer_buff;
  }

  is_oddframe = (((uint32_t)USB_HS_HOST->HFNUM & 0x01U) != 0U) ? 0U : 1U;
  USB_HS_HC(ch_num)->HCCHAR &= ~OTG_HS_HCCHAR_ODDFRM;
  USB_HS_HC(ch_num)->HCCHAR |= (uint32_t)is_oddframe << 29;

  if (hc->do_ssplit == 1U)
  {
    /* Set Hub start Split transaction */
    USB_HS_HC((uint32_t)ch_num)->HCSPLT = ((uint32_t)hc->hub_addr << OTG_HS_HCSPLT_HUBADDR_Pos) |
                                            (uint32_t)hc->hub_port_nbr | OTG_HS_HCSPLT_SPLITEN;
    /* unmask ack & nyet for IN/OUT transactions */
    USB_HS_HC((uint32_t)ch_num)->HCINTMSK |= (OTG_HS_HCINTMSK_ACKM | OTG_HS_HCINTMSK_NYETM);

    if ((hc->do_csplit == 1U) && (hc->ep_is_in == 0U))
    {
      USB_HS_HC((uint32_t)ch_num)->HCSPLT |= OTG_HS_HCSPLT_COMPLSPLT;
      USB_HS_HC((uint32_t)ch_num)->HCINTMSK |= OTG_HS_HCINTMSK_NYETM;
    }

    if (((hc->ep_type == EP_TYPE_ISOC) || (hc->ep_type == EP_TYPE_INTR)) &&
         (hc->do_csplit == 1U) && (hc->ep_is_in == 1U))
    {
      USB_HS_HC((uint32_t)ch_num)->HCSPLT |= OTG_HS_HCSPLT_COMPLSPLT;
    }

    /* Position management for iso out transaction on split mode */
    if ((hc->ep_type == EP_TYPE_ISOC) && (hc->ep_is_in == 0U))
    {
      /* Set data payload position */
      switch(hc->iso_splt_xactPos)
      {
        case HCSPLT_BEGIN:
          /* First data payload for OUT Transaction */
          USB_HS_HC((uint32_t)ch_num)->HCSPLT |= OTG_HS_HCSPLT_XACTPOS_1;
          break;

        case HCSPLT_MIDDLE:
          /* Middle data payload for OUT Transaction */
          USB_HS_HC((uint32_t)ch_num)->HCSPLT |= OTG_HS_HCSPLT_XACTPOS_Pos;
          break;

        case HCSPLT_END:
          /* End data payload for OUT Transaction */
          USB_HS_HC((uint32_t)ch_num)->HCSPLT |= OTG_HS_HCSPLT_XACTPOS_0;
          break;

        case HCSPLT_FULL:
          /* Entire data payload for OUT Transaction */
          USB_HS_HC((uint32_t)ch_num)->HCSPLT |= OTG_HS_HCSPLT_XACTPOS;
          break;

        default:
          break;
      }
    }
  }
  else
  {
    /* Clear Hub Start Split transaction */
    USB_HS_HC((uint32_t)ch_num)->HCSPLT = 0U;
  }

  /* Set host channel enable */
  tmpreg = USB_HS_HC(ch_num)->HCCHAR;
  tmpreg &= ~OTG_HS_HCCHAR_CHDIS;

  /* make sure to set the correct ep direction */
  if (hc->ep_is_in != 0U)
  {
    tmpreg |= OTG_HS_HCCHAR_EPDIR;
  }
  else
  {
    tmpreg &= ~OTG_HS_HCCHAR_EPDIR;
  }

  tmpreg |= OTG_HS_HCCHAR_CHENA;
  USB_HS_HC(ch_num)->HCCHAR = tmpreg;

  if (dma != 0U) /*dma mode*/
  {
    return ;
  }

  if ((hc->ep_is_in == 0U) && (hc->xfer_len > 0U) && (hc->do_csplit == 0U))
  {
    switch (hc->ep_type)
    {
      /* Non periodic transfer */
      case EP_TYPE_CTRL:
      case EP_TYPE_BULK:

        len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);

        /* check if there is enough space in FIFO space */
        if (len_words > (USB_HS->HNPTXSTS & 0xFFFFU))
        {
          /* need to process data in nptxfempty interrupt */
          USB_HS->GINTMSK |= OTG_HS_GINTMSK_NPTXFEM;
        }
        break;

      /* Periodic transfer */
      case EP_TYPE_INTR:
      case EP_TYPE_ISOC:
        len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);
        /* check if there is enough space in FIFO space */
        if (len_words > (USB_HS_HOST->HPTXSTS & 0xFFFFU)) /* split the transfer */
        {
          /* need to process data in ptxfempty interrupt */
          USB_HS->GINTMSK |= OTG_HS_GINTMSK_PTXFEM;
        }
        break;

      default:
        break;
    }
  /* Write packet into the Tx FIFO. */
    (void)USB_HS_WritePacket(hc->xfer_buff, hc->ch_num, (uint16_t)hc->xfer_len, 0);
  }
}


/**
  * @brief Read all host channel interrupts status
  * @param  USB_HS  Selected device
  * @retval host channel interrupt state
  */
uint32_t USB_HS_HC_ReadInterrupt(void)
{
  return ((USB_HS_HOST->HAINT) & 0xFFFFU);
}

/**
  * @brief  Halt a host channel
  * @param  USB_HS  Selected device
  * @param  hc_num  Host Channel number
  *         This parameter can be a value from 1 to 15
  */
void USB_HS_HC_Halt(uint8_t hc_num)
{
  uint32_t hcnum = (uint32_t)hc_num;
  uint32_t count = 0U;
  uint32_t HcEpType = (USB_HS_HC(hcnum)->HCCHAR & OTG_HS_HCCHAR_EPTYP) >> 18;
  uint32_t ChannelEna = (USB_HS_HC(hcnum)->HCCHAR & OTG_HS_HCCHAR_CHENA) >> 31;
  uint32_t SplitEna = (USB_HS_HC(hcnum)->HCSPLT & OTG_HS_HCSPLT_SPLITEN) >> 31;

  if ((((USB_HS->GAHBCFG & OTG_HS_GAHBCFG_DMAEN) == OTG_HS_GAHBCFG_DMAEN) && (SplitEna == 0U)) && 
       ((ChannelEna == 0U) || (((HcEpType == HCCHAR_ISOC) || (HcEpType == HCCHAR_INTR)))))
  {
    return ;
  }

  /* Check for space in the request queue to issue the halt. */
  if ((HcEpType == HCCHAR_CTRL) || (HcEpType == HCCHAR_BULK))
  {
    USB_HS_HC(hcnum)->HCCHAR |= OTG_HS_HCCHAR_CHDIS;

    if ((USB_HS->GAHBCFG & OTG_HS_GAHBCFG_DMAEN) == 0U)
    {
      if ((USB_HS->HNPTXSTS & (0xFFU << 16)) == 0U)
      {
        USB_HS_HC(hcnum)->HCCHAR &= ~OTG_HS_HCCHAR_CHENA;
        USB_HS_HC(hcnum)->HCCHAR |=  OTG_HS_HCCHAR_CHENA;
        do
        {
          count++;
          if (count > 1000U)
          {
            break;
          }
        } while ((USB_HS_HC(hcnum)->HCCHAR & OTG_HS_HCCHAR_CHENA) == OTG_HS_HCCHAR_CHENA);
      }
      else
      {
        USB_HS_HC(hcnum)->HCCHAR |= OTG_HS_HCCHAR_CHENA;
      }
    }
    else
    {
      USB_HS_HC(hcnum)->HCCHAR |= OTG_HS_HCCHAR_CHENA;
    }
  }
  else
  {
    USB_HS_HC(hcnum)->HCCHAR |= OTG_HS_HCCHAR_CHDIS;

    if ((USB_HS_HOST->HPTXSTS & (0xFFU << 16)) == 0U)
    {
      USB_HS_HC(hcnum)->HCCHAR &= ~OTG_HS_HCCHAR_CHENA;
      USB_HS_HC(hcnum)->HCCHAR |=  OTG_HS_HCCHAR_CHENA;
      do
      {
        count++;
        if (count > 1000U)
        {
          break;
        }
      } while ((USB_HS_HC(hcnum)->HCCHAR & OTG_HS_HCCHAR_CHENA) == OTG_HS_HCCHAR_CHENA);
    }
    else
    {
      USB_HS_HC(hcnum)->HCCHAR |= OTG_HS_HCCHAR_CHENA;
    }
  }
}

/**
  * @brief  Initiate Do Ping protocol
  * @param  USB_HS  Selected device
  * @param  hc_num  Host Channel number
  *         This parameter can be a value from 1 to 15
  */
void USB_HS_DoPing(uint8_t ch_num)
{
  uint32_t chnum = (uint32_t)ch_num;
  uint32_t num_packets = 1U;
  uint32_t tmpreg;

  USB_HS_HC(chnum)->HCTSIZ = ((num_packets << 19) & OTG_HS_HCTSIZ_PKTCNT) | OTG_HS_HCTSIZ_DOPING;

  /* Set host channel enable */
  tmpreg = USB_HS_HC(chnum)->HCCHAR;
  tmpreg &= ~OTG_HS_HCCHAR_CHDIS;
  tmpreg |= OTG_HS_HCCHAR_CHENA;
  USB_HS_HC(chnum)->HCCHAR = tmpreg;

}

/**
  * @brief  Stop Host Core
  * @param  USB_HS Selected device
  * @retval USB_HS state
  */
USB_HS_StatusTypeDef USB_HS_StopHost(void)
{
  USB_HS_StatusTypeDef ret = USB_HS_OK;
  __IO uint32_t count = 0U;
  uint32_t value;
  uint32_t i;

  USB_HS_DisableGlobalInt();

  /* Flush FIFO */
  if (USB_HS_FlushTxFifo(0x10U) != USB_HS_OK)  /* all Tx FIFOs */
  {
    ret = USB_HS_ERROR;
  }
  if (USB_HS_FlushRxFifo() != USB_HS_OK)  /* Rx FIFOs */
  {
    ret = USB_HS_ERROR;
  }

  /* Flush out any leftover queued requests. */
  for (i = 0U; i <= 15U; i++)
  {
    value = USB_HS_HC(i)->HCCHAR;
    value |=  OTG_HS_HCCHAR_CHDIS;
    value &= ~OTG_HS_HCCHAR_CHENA;
    value &= ~OTG_HS_HCCHAR_EPDIR;
    USB_HS_HC(i)->HCCHAR = value;
  }

  /* Halt all channels to put them into a known state. */
  for (i = 0U; i <= 15U; i++)
  {
    value = USB_HS_HC(i)->HCCHAR;
    value |=  OTG_HS_HCCHAR_CHDIS;
    value |=  OTG_HS_HCCHAR_CHENA;
    value &= ~OTG_HS_HCCHAR_EPDIR;
    USB_HS_HC(i)->HCCHAR = value;

    do
    {
      count++;
      if (count > 1000U)
      {
        break;
      }
    } while ((USB_HS_HC(i)->HCCHAR & OTG_HS_HCCHAR_CHENA) == OTG_HS_HCCHAR_CHENA);
  }

  /* Clear any pending Host interrupts */
  USB_HS_HOST->HAINT = CLEAR_INTERRUPT_MASK;
  USB_HS->GINTSTS = CLEAR_INTERRUPT_MASK;

  (void)USB_HS_EnableGlobalInt();

  return ret;
}

/**
  * @brief  USB_HS_ActivateRemoteWakeup active remote wakeup signalling
  * @param  USB_HS Selected device
  */
void USB_HS_ActivateRemoteWakeup(void)
{

  if ((USB_HS_DEVICE->DSTS & OTG_HS_DSTS_SUSPSTS) == OTG_HS_DSTS_SUSPSTS)
  {
    /* active Remote wakeup signalling */
    USB_HS_DEVICE->DCTL |= OTG_HS_DCTL_RWUSIG;
  }

}

/**
  * @brief  USB_HS_DeActivateRemoteWakeup de-active remote wakeup signalling
  * @param  USB_HS Selected device
  */
void USB_HS_DeActivateRemoteWakeup(void)
{
  /* active Remote wakeup signalling */
  USB_HS_DEVICE->DCTL &= ~(OTG_HS_DCTL_RWUSIG);

}
#endif /* defined (USB_OTG_HS) */

#endif /* defined (USB_OTG_HS) */


#endif /* defined (PCD_MODULE_ENABLED) || defined (HCD_MODULE_ENABLED) */
