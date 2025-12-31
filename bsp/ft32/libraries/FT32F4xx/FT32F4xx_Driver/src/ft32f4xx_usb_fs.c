/**
  ******************************************************************************
  * @file    			ft32f4xx_usb_fs.c
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
      (#) Fill parameters of Init structure in USB_OTG_CfgTypeDef structure.

      (#) Call USB_FS_CoreInit() API to initialize the USB Core peripheral.

      (#) The upper HCD/PCD driver will call the right routines for its internal processes.
  @endverbatim
******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
#include "ft32f4xx_rcc.h"
#include "ft32f4xx_usb_fs.h"

volatile uint32_t delayCount;

/** @addtogroup FT32F4xx_USB_FS_DRIVER
  * @{
  */

#if defined (PCD_FS_MODULE_ENABLED) || defined (HCD_FS_MODULE_ENABLED)
#if defined (USB_OTG_FS)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if defined (USB_OTG_FS)
static USB_FS_StatusTypeDef USB_FS_CoreReset(void);

/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_Exported_Functions USB OTG FS Low Layer Exported Functions
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

void USB_FS_Delayms(uint32_t num)
{
    if(SysTick_Config(SystemCoreClock/1000))
    {
        while (1);
    }
    uint32_t tickStart = delayCount;
    while ((delayCount - tickStart) < num);
}

/**
  * @brief  Initializes the USB OTG FS Core
  * @param  USB FS USB Instance
  * @param  cfg pointer to a USB_OTG_FS_CfgTypeDef structure that contains
  *         the configuration information for the specified USB_FS peripheral.
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_CoreInit(void)
{
    USB_FS_StatusTypeDef ret;


    /* Init the UTMI interface */

    /* Reset */
    ret = USB_FS_CoreReset();
    /* change srqxtune txvreftune otgtune compdistune */
    /* waiting for update                             */

    return ret;
}

/**
  * @brief  Reset the USB_FS Core
  * @param  USB_FS  Selected device
  * @retval USB_FS status
  */
static USB_FS_StatusTypeDef USB_FS_CoreReset(void)
{
    __IO uint32_t count = 0U;

    /* Core Soft Reset */
    count = 0U;
    RCC_AHB2PeriphResetCmd(RCC_AHB2PeriphRst_USBOTGFS, ENABLE);

    USB_FS_Delayms(5U);  /* update delay */

    RCC_AHB2PeriphResetCmd(RCC_AHB2PeriphRst_USBOTGFS, DISABLE);
    return USB_FS_OK;
}


/**
  * @brief  USB_FS_DevInit: Initializes the USB_OTG_FS controller registers
  *         for device mode
  * @param  USB_FS  Selected device
  * @param  cfg   pointer to a USB_OTG_FS_CfgTypeDef structure that contains
  *         the configuration information for the specified USB_FS peripheral.
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_DevInit(USB_OTG_FS_CfgTypeDef cfg)
{
    USB_FS_StatusTypeDef ret = USB_FS_OK ;
    uint32_t i;

    for (i = 1U; i < cfg.endpoints; i++)
    {
        USB_FS->INDEX = i;
        USB_FS->TXFIFO1 = 0U;
        USB_FS->TXFIFO2 = 0U;
        USB_FS->RXFIFO1 = 0U;
        USB_FS->RXFIFO2 = 0U;
    }

    /* initial ep0 */
    USB_FS_RstEP0Regs();

    /* reset all ep register include flush fifo*/
    for (i = 1U; i < cfg.endpoints; i++)
    {
        if (USB_FS_RstEPRegs(i) != USB_FS_OK)
        {
            ret = USB_FS_ERROR;
        }
    }

    /* Clear all pending Device Interrupts */
    USB_FS_ClrEPInt();
    USB_FS->INTRTX1E = 0U;
    USB_FS->INTRRX1E = 0U;

    USB_FS_ClrUSBInt();
    USB_FS->INTRUSBE = 0U;

    /* Enable the common interrupts */
    USB_FS_SetUSBInt(OTG_FS_INTRUSBE_SOFINTE  | OTG_FS_INTRUSBE_RSTINTE  |
                     OTG_FS_INTRUSBE_DISCINTE | OTG_FS_INTRUSBE_SREQINTE |
                     OTG_FS_INTRUSBE_VERRINTE);

    return ret;
}

/**
  * @brief  USB_FS_IndexSel : select a endpoint
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_IndexSel(uint8_t epnum)
{
    uint8_t reg;

    reg  = USB_FS->INDEX;

    if (reg != epnum)
    {
        USB_FS->INDEX = epnum;

        do
        {
            reg = USB_FS->INDEX;
        }
        while(reg != epnum);
    }

    return USB_FS_OK;
}

/**
  * @brief  USB_FS_RstEP0Regs : reset endpoint 0 registers
  * @param  none
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_RstEP0Regs(void)
{
    uint8_t reg;

    /* reset endpoint0 register */
    (void)USB_FS_FlushEp0Fifo();

    USB_FS->CSR0 = 0U;
    USB_FS->NAKLMT0 = 0U;

    return USB_FS_OK;
}

/**
  * @brief  USB_FS_RstEPRegs : reset endpoint registers
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_RstEPRegs(uint8_t epnum)
{
    uint8_t reg;

    //USB_FS_IndexSel(epnum);
    /* reset tx register */
    /* flush tx fifo */
    USB_FS_FlushTxFifo(epnum);
    /* reset the data tog to 0 */
    USB_FS->TXCSR1 |= OTG_FS_TXCSR1_CLRDT;
    /* clear autoset, iso, mode, frcdatatog */
    USB_FS->TXCSR2  = OTG_FS_TXCSR2_MODE;
    /* config max tx endpoint data packet size */
    USB_FS->TXMAXP  = USB_OTG_FS_MAX_PACKET_SIZE / 8;

    /* flush tx fifo */
    USB_FS_FlushRxFifo(epnum);
    /* reset the data tog to 0 */
    USB_FS->RXCSR1 |= OTG_FS_RXCSR1_CLRDT;
    /* clear autoclr, iso, autoreq */
    USB_FS->RXCSR2  = 0U;
    /* config max rx endpoint data packet size */
    USB_FS->RXMAXP  = USB_OTG_FS_MAX_PACKET_SIZE / 8;


    return USB_FS_OK;
}
/**
  * @brief  USB_FS_Get_VBusStatus :
  *         get vbus stattus
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
  * @retval USB_FS VBus status
  */
uint32_t USB_FS_Get_VBusStatus(void)
{
    uint8_t power;

    power = USB_FS->POWER;

    switch ((power & VBUS_MASK) >> 4)
    {
        case 0:
            return VBUS_BELOW_SESSION_END;

        case 1:
            return VBUS_ABOVE_SESSION_END;

        case 3:
            return VBUS_ABOVE_AVALID;

        case 7:
            return VBUS_ABOVE_VBUS_VALID;
    }

    return (VBUS_ERROR);
}

/**
  * @brief  USB_FS_Read_RxCount
  *         get received data size
  * @param  none
  * @retval data size
  */
uint16_t USB_FS_Read_RxCount(void)
{
    uint16_t count = 0;
    uint16_t count1 = 0;
    uint16_t count2 = 0;

    count1 = USB_FS->RXCOUNT1;
    count2 = USB_FS->RXCOUNT2;

    count = ((count2 << 8) | count1);

    return count;
}

/**
  * @brief  USB_FS_Read_Count0
  *         get received data size of endpoint0
  * @param  none
    @retval endpoint0 received data size
  */
uint8_t USB_FS_Read_Count0(void)
{
    uint8_t count = 0;

    count = USB_FS->COUNT0;

    return count;
}



/**
  * @brief  USB_FS_GetCurrentFrame
  *         Return Host Current Frame number
  * @param  USB_FS  Selected device
  * @retval current frame number
  */
uint32_t USB_FS_GetCurrentFrame(void)
{
    uint32_t framel = 0U;
    uint32_t frameh = 0U;
    uint32_t frame  = 0U;

    framel = USB_FS->FRAME1;
    frameh = ((USB_FS->FRAME2) << 8);
    frame  = (framel | frameh);

    return frame;
}

/**
  * @brief  USB_FS_Enable_EP
  *         enable endpoint transfer
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval none
  */
/*
 *  MGC_Enable_EP_DRC:
 *      Following a successful "SetConfig" operation, use MGC_Enable_EP_DRC
 *  to enable the endpoint registers in the DRC previosly bound by a
 *  ReturnEPMatch/SelectEP operation.  Following this operation, live
 *  traffic can occur on the endpoint. Note that this can be called prior
 *  to "SetConfig".  Either way, if SetConfig fails, the EPs previously
 *  bound must be released.
 */
void USB_FS_Enable_HEP(USB_OTG_FS_HEPTypeDef *hep)
{
    uint8_t epnum = (uint8_t)hep->epnum;
    USB_FS_IndexSel(epnum);

    if (hep->ep_is_in == 1U)
    {
        if ((USB_FS->RXCSR1 & OTG_FS_RXCSR1_REQPKT) == 0U)
        {
            USB_FS->RXTYPE = (hep->epnum & 0x0f) | ((hep->ep_type & 0x03) << 4);  /* set this endpoint */
            USB_FS->RXMAXP = (hep->max_packet / 8);
            USB_FS->RXCSR1 = OTG_FS_RXCSR1_CLRDT;
        }
    }
    else
    {
        if ((USB_FS->TXCSR1 & OTG_FS_TXCSR1_TXPKTRDY) == 0U)
        {
            USB_FS->TXTYPE = (hep->epnum & 0x0f) | ((hep->ep_type & 0x03) << 4);  /* set this endpoint */
            USB_FS->TXMAXP = (hep->max_packet / 8);
            USB_FS->TXCSR2 = OTG_FS_TXCSR2_MODE;
            USB_FS->TXCSR1 = OTG_FS_TXCSR1_FFIFO;
            USB_FS->TXCSR1 = OTG_FS_TXCSR1_FFIFO;
            USB_FS->TXCSR1 = OTG_FS_TXCSR1_CLRDT;
        }
    }
}


void USB_FS_Enable_DEP(USB_OTG_FS_DEPTypeDef *dep)
{
    uint8_t epnum = (uint8_t)dep->num;
    USB_FS_IndexSel(epnum);

    if (dep->is_in == 0U)
    {
        if ((USB_FS->RXCSR1 & OTG_FS_RXCSR1_REQPKT) == 0U)
        {
            USB_FS->RXTYPE = (dep->num & 0x0f) | ((dep->type & 0x03) << 4);  /* set this endpoint */
            USB_FS->RXMAXP = (dep->maxpacket / 8);

            if (dep->type == EP_TYPE_ISOC)
            {
                USB_FS->RXCSR2 = OTG_FS_RXCSR2_AUTOCLR | OTG_FS_RXCSR2_ISO;
            }

            USB_FS->RXCSR1 = OTG_FS_RXCSR1_CLRDT;
        }
    }
    else
    {
        if ((USB_FS->TXCSR1 & OTG_FS_TXCSR1_TXPKTRDY) == 0U)
        {
            USB_FS->TXTYPE = (dep->num & 0x0f) | ((dep->type & 0x03) << 4);  /* set this endpoint */
            USB_FS->RXMAXP = (dep->maxpacket / 8);

            if (dep->type == EP_TYPE_ISOC)
            {
                USB_FS->TXCSR2 = OTG_FS_TXCSR2_MODE | OTG_FS_TXCSR2_ISO;
            }
            else
            {
                USB_FS->TXCSR2 = OTG_FS_TXCSR2_MODE;
            }

            USB_FS->TXCSR1 = OTG_FS_TXCSR1_FFIFO;
            USB_FS->TXCSR1 = OTG_FS_TXCSR1_FFIFO;
            USB_FS->TXCSR1 = OTG_FS_TXCSR1_CLRDT;
        }
    }
}



/**
  * @brief  USB_FS_DEPStartXfer : setup and starts a transfer over an EP
  * @param  ep pointer to endpoint structure
  * @retval none
  */
void USB_FS_DEPStartXfer(USB_OTG_FS_DEPTypeDef *dep)
{
    uint8_t epnum = (uint8_t)dep->num;
    uint16_t pktcnt;
    static uint8_t current_pid = 0; 
    USB_FS_IndexSel(epnum);

    /* tx endpoint */
    if (dep->is_in == 1U)
    {
        /* Zero Length Packet? */
        if (dep->xfer_len == 0U)
        {
            USB_FS->TXMAXP &= (~OTG_FS_TXMAXP_TXMAXPKT);
        }
        else
        {
            USB_FS->TXMAXP &= (~OTG_FS_TXMAXP_TXMAXPKT);

            USB_FS->TXMAXP = (OTG_FS_TXMAXP_TXMAXPKT & dep->xfer_len);
        }

        if (current_pid == 0)
        {
            USB_FS->TXCSR1 = OTG_FS_TXCSR1_CLRDT;
            current_pid = 1;
        }
        else
        {
            current_pid = 0;
        }

        USB_FS_FIFOWrite(dep->xfer_buff, dep->num, (uint16_t)dep->xfer_len);
        USB_FS->TXCSR1 = OTG_FS_TXCSR1_TXPKTRDY;
    }
    else /* rx endpoint */
    {
        USB_FS->RXMAXP &= (~OTG_FS_RXMAXP_RXMAXPKT);

        if (dep->xfer_len > 0U)
        {
            dep->xfer_size = dep->xfer_len;
            USB_FS->RXMAXP = (OTG_FS_RXMAXP_RXMAXPKT & dep->xfer_size);
        }

        USB_FS->RXCSR1 = OTG_FS_RXCSR1_CLRDT;
    }
}
/**
  * @brief  USB_FS_DEP0StartXfer : setup and starts a transfer over EP0
  * @param  ep pointer to endpoint structure
  * @retval none
  */
void USB_FS_DEP0StartXfer(USB_OTG_FS_DEPTypeDef *dep)
{
    USB_FS_IndexSel(0U);
    uint32_t len = 0;

    /* tx endpoint */
    if (dep->is_in == 1U)
    {
        if (dep->xfer_len > dep->maxpacket)
        {
            dep->xfer_len = dep->maxpacket;
        }
        USB_FS_FIFOWrite(dep->xfer_buff, dep->num, (uint16_t)dep->xfer_len);
        USB_FS->CSR0 |= OTG_FS_CSR0_TXPKTRDY;

      if (dep->xfer_len < 0x40U)
      {
         USB_FS->CSR0 |= OTG_FS_CSR0_DATAEND;
      }
      dep->xfer_buff  += dep->xfer_len;
      dep->xfer_count += dep->xfer_len;
    }
    else
    {
        dep->xfer_count = 0;
    }
}


/**
  * @brief  USB_FS_FIFORead
  *         read receive fifo
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval none
  */

/*
 *  Fifo_Read uses the endpoint object to ensure sole access to FIFO,
 *  then updates the object with # of bytes read.  ***IMPORTANT***, we
 *  assume only thread of execution is BGD interrupt process, which has
 *  preselected the INDEX reg.  eP->FifoRemain always represents the
 *  number of remaining bytes in the fifo following a recv packet interrupt.
 *  eP->BytesRequested - eP->BytesProcessed always represents the remaining
 *  bytes to fill from the APP (EP0 or user).  We use the smaller of those
 *  two and move the bytes, updating all relevant counters.  A new recv
 *  packet operation won't be initiated by the DRC until the fifo count
 *  has gone to 0.
 */
void USB_FS_FIFORead(uint8_t *dst, uint8_t ep_num, uint16_t len)
{
    uint16_t readcount;
    uint32_t fifo_addr;
    /*  Take the smaller of what's requested versus what's in the fifo */
    readcount = len;
    //MIN((eP->BytesRequested - eP->BytesProcessed), eP->FifoRemain);

    if (readcount <= 0)            /* if none to read or blown tracking ... */
    {
        return;
    }

//  dst += eP->BytesProcessed;         /* user buffer offset for current rd*/
//  eP->BytesProcessed += readcount;    /* apps & stack can monitor progress */
//  eP->FifoRemain -= readcount;
    fifo_addr = ADDR_FIFO_EP0 + (ep_num << 2); /* blds absolute fifo addrs */
//  fifo_addr = ADDR_FIFO_EP0 + ep_num; /* blds absolute fifo addrs */

    while (readcount != 0U)
    {
        *dst++ = *((uint8_t *)fifo_addr);
        readcount = readcount - 1U;
    }

}

/**
  * @brief  USB_FS_FIFOWrite
  *         write data to tx fifo
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval USB_FS VBus status
  */
/*
 *  MGC_DRC_Fifo_Write uses the endpoint object to ensure sole access to FIFO,
 *  then updates the object with # of bytes written.  MaxEPSize used to
 *  limit the write.  MaxEPSize shall never be larger than the size of the
 *  configured fifo.
 *
 *  20-May-03: Setting eP->LastPacket universally for transmits.  If
 *  a requested transmission is a multiple of the Max EP Size, then a 0-len
 *  packet is owed following the data packets.  Otherwise, when processed
 *  = requested, we have a last-packet condition.
 */
void USB_FS_FIFOWrite(uint8_t *src, uint8_t ep_num, uint16_t len)
{
    uint16_t writecount;
    uint32_t fifo_addr;

    writecount = len;
    //MIN(eP->MaxEPSize, (eP->BytesRequested - eP->BytesProcessed));

// src += eP->BytesProcessed;         /* user offset */
// eP->BytesProcessed += writecount;   /* apps & stack can monitor progress */

// if ((eP->BytesProcessed == eP->BytesRequested) &
//    ((eP->BytesProcessed % eP->MaxEPSize) /* can't be a multiple */
//    || usb_pipebulk(eP->URBP->pipe) ||
//    (eP->Attr == 3) || (eP->Attr == 1)))
// {
//   eP->LastPacket = 1;
// }
    fifo_addr = ADDR_FIFO_EP0 + (ep_num << 2); /* blds absolute fifo addrs */
//  fifo_addr = ADDR_FIFO_EP0 + ep_num; /* blds absolute fifo addrs */

    while (writecount)
    {
        *((uint8_t *)fifo_addr) = *src++;
        writecount--;
    }
}



/**
  * @brief  USB_FS_SetEPInt
  *         unmask or mask endpoint interrupt
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
  * @retval USB_FS status
  */
void USB_FS_SetEPInt(uint8_t cfg)
{
    uint8_t reg;

    /* Set INT enable registers */
    reg = cfg & 0xff;           /* endpoints 0 .. 7 */
    USB_FS->INTRTX1E |= reg;
    USB_FS->INTRRX1E |= reg;
}

/**
  * @brief  USB_FS_SetUSBInt
  *         unmask or mask usb interrupt
  * @param  none
  * @retval USB_FS status
  */
void USB_FS_SetUSBInt(uint8_t cfg)
{
    uint8_t reg;

    /* Set INT enable registers */
    reg = cfg & 0xff;
    USB_FS->INTRUSBE = reg;
}
/**
  * @brief  USB_FS_ClrUSBInt
  *         clear usb interrupts
  * @retval none
  */

void USB_FS_ClrUSBInt(void)
{
    uint8_t temp;

    /*  flush pending interrupts */
    temp = USB_FS->INTRUSB;
}
/**
  * @brief  USB_FS_ClrEPInt
  *         clear endpoint interrupts
  * @retval none
  */

void USB_FS_ClrEPInt(void)
{
    uint8_t temp;

    /*  flush pending interrupts */
    temp = USB_FS->INTRTX1;
    temp = USB_FS->INTRRX1;
}

/**
  * @brief  Activate EP0 for Setup transactions
  * @param  USB_FS  Selected device
  */
void  USB_FS_ActivateSetup(void)
{
    /* Set the MPS of the IN EP0 to 64 bytes */
    USB_FS->CSR0 |= (OTG_FS_CSR0_SETUPPKT | OTG_FS_TXCSR1_TXPKTRDY);
}


/**
  * @brief  Initialize a host transfer
  * @param  epnum  Endpoint number
  *          This parameter can be a value from 1 to 15
  * @param  dev_address  Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed  Current device speed
  * @param  interval : for iso/interrupt interval
  *                    for bulk: nakmit
  * @param  ep_type  Endpoint Type
  *          This parameter can be one of these values:
  *            @arg EP_TYPE_CTRL: Control type
  *            @arg EP_TYPE_ISOC: Isochronous type
  *            @arg EP_TYPE_BULK: Bulk type
  *            @arg EP_TYPE_INTR: Interrupt type
  * @param  mps  Max Packet Size
  * @retval USB_FS state
  */
USB_FS_StatusTypeDef USB_FS_HEP_Init(uint8_t epnum, uint8_t dev_address,
                                     uint8_t ep_type, uint8_t interval,
                                     uint16_t xfersize)
{
    USB_FS_StatusTypeDef ret = USB_FS_OK;
    uint8_t HostCoreSpeed;
    uint8_t ep_num;
    uint8_t ep_dir;

    ep_num = epnum & 0x7FU;

    ret = USB_FS_IndexSel(ep_num);
    /* Clear old interrupt conditions for this host channel. */
    USB_FS_ClrUSBInt();
    USB_FS_ClrEPInt();
    USB_FS_SetEPInt(1 << ep_num);

    HostCoreSpeed = USB_FS_GetSpeed();

    USB_FS_SetAddress(dev_address);

    if (ep_num != 0U)
    {
        if ((epnum & 0x80U) == 0x80U)  /* in rx */
        {
            USB_FS->RXTYPE = (ep_num | (ep_type << 4));
            USB_FS->RXINTERVAL = interval;
            USB_FS->RXMAXP = (xfersize / 8);
        }
        else
        {
            USB_FS->TXTYPE = (ep_num | (ep_type << 4));
            USB_FS->TXINTERVAL = interval;
            USB_FS->TXMAXP = (xfersize / 8);
        }
    }

    return ret;
}


/**
  * @brief  Start a transfer over a host endpoint
  * @param  endpoint  pointer to host endpoint structure
  * @retval none
  */
void USB_FS_HEP_StartXfer(USB_OTG_FS_HEPTypeDef *hep)
{
    uint8_t ep_num = (uint32_t)hep->epnum;
    __IO uint32_t tmpreg;
    uint16_t maxpacket = 0U;

    (void)USB_FS_IndexSel(ep_num);

    switch (hep->ep_type)
    {
        case EP_TYPE_BULK:
            maxpacket = USB_OTG_FS_MAX_BULK_PACKET_SIZE;
            break;

        case EP_TYPE_INTR:
            if ((USB_FS->DEVCTL & 0x40U) != 0)
            {
                maxpacket = USB_OTG_FS_MAX_INTR_PACKET_SIZE;
            }
            else
            {
                maxpacket = USB_OTG_LS_MAX_INTR_PACKET_SIZE;
            }

            break;

        case EP_TYPE_ISOC:
            maxpacket = USB_OTG_FS_MAX_ISOC_PACKET_SIZE;
            break;

        default:
            break;
    }

    if (hep->xfer_len > maxpacket)
    {
        hep->XferSize = maxpacket;
    }
    else
    {
        hep->XferSize = hep->xfer_len;
    }

    if (hep->ep_is_in == 1U)  /* in rx */
    {
        USB_FS->RXTYPE = (ep_num | (hep->ep_type << 4));
        USB_FS->RXMAXP = ((maxpacket + 7U) / 8U);
        USB_FS->RXCSR1 |= OTG_FS_RXCSR1_CLRDT;
        USB_FS->RXCSR1 |= OTG_FS_RXCSR1_REQPKT;
    }
    else
    {
        USB_FS->TXTYPE = (ep_num | (hep->ep_type << 4));
        USB_FS->TXMAXP = ((maxpacket + 7U) / 8U);;
        USB_FS->TXCSR1 |= OTG_FS_TXCSR1_CLRDT;
        USB_FS->TXCSR2 |= OTG_FS_TXCSR2_MODE;
    }

    if ((hep->ep_is_in == 0U) & (hep->xfer_len > 0U))
    {
        /* Write packet into the Tx FIFO. */
        (void)USB_FS_FIFOWrite(hep->xfer_buff, ep_num, (uint16_t)hep->XferSize);
        USB_FS->TXCSR1 = OTG_FS_TXCSR1_TXPKTRDY;
    }
}

/**
  * @brief  Start a transfer over a host endpoint 0
  * @param  endpoint  pointer to host endpoint structure
  * @retval none
  */
void USB_FS_HEP0_StartXfer(USB_OTG_FS_HEPTypeDef *hep, uint8_t ctl_state)
{
    uint8_t ep_num = 0U;

    (void)USB_FS_IndexSel(ep_num);

    if (hep->data_pid == EP_PID_SETUP)
    {
        /* Write packet into the Tx FIFO. */
        (void)USB_FS_FIFOWrite(hep->xfer_buff, ep_num, (uint16_t)hep->xfer_len);
        USB_FS->CSR0 = OTG_FS_CSR0_TXPKTRDY | OTG_FS_CSR0_SETUPPKT;
    }
    else if (ctl_state == CTRL_STATUS)
    {
        if (hep->ep_is_in == 0U)
        {
            USB_FS->CSR0 = OTG_FS_CSR0_TXPKTRDY | OTG_FS_CSR0_STATUSPKT;
        }
        else
        {
            USB_FS->CSR0 = OTG_FS_CSR0_REQPKT | OTG_FS_CSR0_STATUSPKT;
        }
    }
    else if (ctl_state == CTRL_DATA)
    {
        if (hep->ep_is_in == 0U)
        {
            if (hep->xfer_len > 0U)
            {
                (void)USB_FS_FIFOWrite(hep->xfer_buff, ep_num, (uint16_t)hep->xfer_len);
            }

            USB_FS->CSR0 = OTG_FS_CSR0_TXPKTRDY;
        }
        else
        {
            USB_FS->CSR0 = OTG_FS_CSR0_REQPKT;
        }
    }
    else
    {
        /*...*/
    }
}


/**
  * @brief  USB_FS_FlushEp0Fifo : Flush EP0 FIFO
  * @param  none
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_FlushEp0Fifo(void)
{

    /* Flush EP0 fifo */
    USB_FS->INDEX = 0U;
    USB_FS->CSR02 = OTG_FS_CSR02_FFIFO;


    return USB_FS_OK;
}

/**
  * @brief  USB_FS_FlushTxFifo : Flush a Tx FIFO
  * @param  epnum  endpoint number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_FlushTxFifo(uint8_t epnum)
{

    /* Flush TX fifo */
    USB_FS->INDEX = epnum;
    USB_FS->TXCSR1 |= OTG_FS_TXCSR1_FFIFO;


    return USB_FS_OK;
}

/**
  * @brief  USB_FS_FlushRxFifo : Flush Rx FIFO
  * @param  USB_FS Selected device
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_FlushRxFifo(uint8_t epnum)
{

    /* Flush RX fifo */
    USB_FS->INDEX = epnum;
    USB_FS->RXCSR1 |= OTG_FS_RXCSR1_FFIFO;

    return USB_FS_OK;
}


/**
  * @brief  Set Tx FIFO
  * @param  fifo The number of Tx fifo
  * @param  size Fifo size
  * @retval none
  */
void USB_FS_SetTxFiFo(uint8_t epnum, uint8_t size, uint8_t address, uint8_t dpb)
{
    uint8_t fifo1, fifo2;

    /*
     *  usb_fs ram 1024bytes
     *  size and address are in the unit of 8 bytes
     *  max fifo size, 1024 bytes / 8 = 128
     *  max address, 0x7ff8 / 8 = 0xfff  (0x400-8) / 8 = 0x7F
     */
    if ((size > 128) || (address > 0x7F))
    {
        return;
    }

    fifo1 = address;
    fifo2 = ((dpb << 4 ) & (OTG_FS_TXFIFO2_TXDPB));
    fifo2 |= (usb_log2(size)) << 5;

    USB_FS->INDEX   = (0x0F & epnum);
    USB_FS->TXFIFO1 = fifo1;
    USB_FS->TXFIFO2 = fifo2;

}

/**
  * @brief  Set Rx FIFO
  * @param  size Size of Rx fifo
  * @retval none
  */
void USB_FS_SetRxFiFo(uint8_t epnum, uint8_t size, uint8_t address, uint8_t dpb)
{
    uint8_t fifo1, fifo2;

    /*
     *  usb_fs ram 1024bytes
     *  size and address are in the unit of 8 bytes
     *  max fifo size, 1024 bytes / 8 = 128
     *  max address, 0x7ff8 / 8 = 0xfff  (0x400-8) / 8 = 0x7F
     */
    if ((size > 128) || (address > 0x7F))
    {
        return;
    }

    fifo1 = address;
    fifo2 = ((dpb << 4 ) & (OTG_FS_TXFIFO2_TXDPB));
    fifo2 |= (usb_log2(size)) << 5;

    USB_FS->INDEX   = (0x0F & epnum);
    USB_FS->RXFIFO1 = fifo1;
    USB_FS->RXFIFO2 = fifo2;

}

/**
  * @brief  Returns USB_FS core mode
  * @param  USB_FS  Selected device
  * @retval return core mode : Host or Device
  *          This parameter can be one of these values:
  *           1 : Host
  *           0 : Device
  */
uint8_t USB_FS_GetMode(void)
{
    return ((USB_FS->DEVCTL) & 0x4U);
}

/**
  * @brief  Returns USB_FS core CID
  * @retval return core ID : A-device or B-device
  *          This parameter can be one of these values:
  *           0 : A-device
  *           1 : B-device
  */
uint8_t USB_FS_GetCID(void)
{
    return ((USB_FS->DEVCTL) & 0x80U);
}

/**
  * @brief  USB_FS_DrvSess : enabel or disable session
  * @param  state  session state
  *          This parameter can be one of these values:
  *           0 : disable session request
  *           1 : enable session request
  */
void USB_FS_DrvSess(uint8_t state)
{
    __IO uint8_t session = 0U;

    session = USB_FS->DEVCTL;

    if (((session & OTG_FS_DEVCTL_SESSION) == 0U) & (state == 1U))
    {
        USB_FS->DEVCTL = (OTG_FS_DEVCTL_SESSION | session);
    }

    if (((session & OTG_FS_DEVCTL_SESSION) == OTG_FS_DEVCTL_SESSION) & (state == 0U))
    {
        USB_FS->DEVCTL = ((~OTG_FS_DEVCTL_SESSION) & session);
    }
}

/**
  * @brief  Return Host Core speed
  * @retval speed : Host speed
  *          This parameter can be one of these values:
  *            @arg HCD_SPEED_FULL: Full speed mode
  *            @arg HCD_SPEED_LOW: Low speed mode
  */
uint32_t USB_FS_GetSpeed(void)
{
    __IO uint8_t spd = 0U;
    uint32_t speed;
    spd = USB_FS->DEVCTL;

    if ((spd & OTG_FS_DEVCTL_FSDEV) == OTG_FS_DEVCTL_FSDEV)
    {
        speed = USB_FS_SPEED;
    }
    else if ((spd & OTG_FS_DEVCTL_LSDEV) == OTG_FS_DEVCTL_LSDEV)
    {
        speed = USB_LS_SPEED;
    }
    else
    {
        speed = 0xFU;
    }

    return speed;
}

/**
  * @brief  USB_FS_Set_Polling_Interval
  *         set polling interval value for iso or interrupt transfer.
  * @param  epdir endpoint transfer tx or rx
  *         1: tx
  *         0: rx
  * @param  interval: polling interval value
  * @retval none
  */
void USB_FS_Set_Polling_Interval(uint8_t epdir, uint8_t interval)
{
    if ((epdir & 0x01) == FIFO_TX)
    {
        USB_FS->TXINTERVAL = (interval & 0xFF);
    }
    else
    {
        USB_FS->RXINTERVAL = (interval & 0xFF);
    }
}

/**
  * @brief  USB_FS_Set_NAKLMT
  *         set nak limit value
  * @param  epnum: endpoint number
  * @param  epdir endpoint transfer tx or rx
  *         1: tx
  *         0: rx
  * @param  interval: polling interval value
  * @retval none
  */
void USB_FS_Set_NAKLMT(uint8_t epnum, uint8_t epdir, uint8_t naklmt)
{
    if (epnum != 0U)
    {
        if ((epdir & 0x01) == FIFO_TX)
        {
            USB_FS->TXINTERVAL = (naklmt & 0xFF);
        }
        else
        {
            USB_FS->RXINTERVAL = (naklmt & 0xFF);
        }
    }
    else
    {
        USB_FS->NAKLMT0 = naklmt;
    }
}

/**
  * @brief  USB_FS_SetAddress : set device address
  * @param  address  new device address to be assigned
  *          This parameter can be a value from 0 to 255
  * @retval none
  */
void USB_FS_SetAddress(uint8_t address)
{
    USB_FS->FADDR &= ~(OTG_FS_FADDR_FUNADDR);
    USB_FS->FADDR = (address & OTG_FS_FADDR_FUNADDR);
}

/**
  * @brief  USB_FS_GetAddress : get device address
  * @retval device address
  */
uint8_t USB_FS_GetAddress(void)
{
    uint8_t address;
    address = 0U;

    address = USB_FS->FADDR;
    return address;
}

/**
  * @brief  USB_FS_SetPower : Set power register
  * @param  configured value
  * @retval none  */
void USB_FS_SetPower(uint8_t powercfg)
{
    uint8_t reg_power;
    uint8_t temp;
    reg_power = USB_FS->POWER;
    temp = (reg_power | powercfg);

    USB_FS->POWER = temp;
}

/**
  * @brief  USB_FS_GetPower : get power register
  * @param  none
  * @retval power register value
  */
uint8_t USB_FS_GetPower(void)
{
    uint8_t reg_power;
    reg_power = USB_FS->POWER;

    return reg_power;
}

/**
  * @brief  USB_FS_ClrPower : Clear power register
  * @param  configured value
  * @retval none
  */
void USB_FS_ClrPower(uint8_t powercfg)
{
    uint8_t reg_power;
    uint8_t temp;
    reg_power = USB_FS->POWER;
    temp = (reg_power & (~powercfg));

    USB_FS->POWER = temp;
}

/**
  * @brief  USB_FS_SetDevctl : Set devctl register
  * @param  configured value
  * @retval none
  */
void USB_FS_SetDevctl(uint8_t cfg)
{
    uint8_t reg_devctl;
    uint8_t temp;
    reg_devctl = USB_FS->DEVCTL;
    temp = (reg_devctl | cfg);

    USB_FS->DEVCTL = temp;
}

/**
  * @brief  USB_FS_GetDevctl : get devctl register
  * @param  none
  * @retval Devctl register value
  */
uint8_t USB_FS_GetrDevctl(void)
{
    uint8_t reg_devctl;
    reg_devctl = USB_FS->DEVCTL;

    return reg_devctl;
}

/**
  * @brief  USB_FS_ClrDevctl : Clear devctl register
  * @param  configured value
  * @retval none
  */
void USB_FS_ClrDevctl(uint8_t cfg)
{
    uint8_t reg_devctl;
    uint8_t temp;
    reg_devctl = USB_FS->DEVCTL;
    temp = (reg_devctl & (~cfg));

    USB_FS->DEVCTL = temp;
}

/**
  * @brief  USB_FS_Exiting_Host : exit host mode
  * @param  toOTG cp
  * @retval status
  */
int8_t USB_FS_Exiting_Host(uint8_t toOTG, USB_OTG_FS_CfgTypeDef *cfg)
{
    if (toOTG == A_SUSPEND)    /* A_SUSPEND itself is not exiting host */
    {
        return(0);
    }
    else if (toOTG == A_PERIPHERAL) /* Only way here is from a host(suspend) */
    {
        return(1);
    }
    else if ((cfg->OTGState == A_HOST) || (cfg->OTGState == B_HOST))
    {
        return(1);
    }
    else
    {
        return(0);
    }
}
/**
  * @brief  USB_FS_Activate_Resume : set resume
  * @param  none
  * @retval none
  */
void USB_FS_Activate_Resume(void)
{
    if ((USB_FS_GetPower() & OTG_FS_POWER_SUSPEND) == OTG_FS_POWER_SUSPEND)
    {
        USB_FS_SetPower(OTG_FS_POWER_RESUME);  /* sets the RESUME bit */
    }
}

/**
  * @brief  USB_FS_DeActivate_Resume : exit host mode
  * @param  none
  * @retval none
  */
void USB_FS_DeActivate_Resume(void)
{
    USB_FS_ClrPower(OTG_FS_POWER_RESUME);  /* clear the RESUME bit */
}

/**
  * @brief  USB_FS_ResetPort : Reset Host Port
  * @param  USB_FS  Selected device
  * @note (1)The application must wait at least 20 ms
  *   before clearing the reset bit.
  */
void USB_FS_ResetPort(void)
{
    __IO uint8_t temp_reg = 0U;
    __IO uint32_t num = 20;

    temp_reg = USB_FS->POWER;

    temp_reg |= OTG_FS_POWER_RESET;
    USB_FS->POWER = temp_reg;

    while(num--)  /* update delay 20ms */
    {
        SysTick->LOAD = SystemCoreClock / 1000;
        SysTick->VAL = 0x00;
        SysTick->CTRL = 0x00000005;

        while(!(SysTick->CTRL & 0x00010000));

        SysTick->CTRL = 0x00000004;
    }
//    USB_FS_Delayms(20U);                          
    temp_reg &= (~OTG_FS_POWER_RESET);
    USB_FS->POWER = temp_reg;
}

int32_t usb_log2(int32_t x)
{
    int32_t i;

    for (i = 0; x > 1; i++)
    {
        x = x / 2 ;
    }

    return i;
}

/**
  * @brief  USB_FS_HostInit : Initializes the USB controller registers
  *         for Host mode
  * @param  USB_FS  Selected device
  * @param  cfg   pointer to a USB_OTG_FS_CfgTypeDef structure that contains
  *         the configuration information for the specified USB_FS peripheral.
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_HostInit(USB_OTG_FS_CfgTypeDef cfg)
{
    USB_FS_StatusTypeDef ret = USB_FS_OK;
    uint32_t i;

    /* initial ep0 */
    (void)USB_FS_RstEP0Regs();

    /* reset all ep register include flush fifo*/
    for (i = 1U; i < cfg.endpoints; i++)
    {
        if (USB_FS_RstEPRegs(i) != USB_FS_OK)
        {
            ret = USB_FS_ERROR;
        }
    }

    /* Clear all pending Interrupts */
    USB_FS_ClrEPInt();
    OTG_FS->INTRTX1E = 0U;
    OTG_FS->INTRRX1E = 0U;

    USB_FS_ClrUSBInt();
    OTG_FS->INTRUSBE = 0U;

    /* Enable VBUS driving */
    USB_FS_SetUSBInt(OTG_FS_INTRUSBE_CONNINTE);
    (void)USB_FS_DrvSess(1U);
    USB_FS_Delayms(200U); /* update delay*/

    /* Enable the common interrupts */
    USB_FS_SetUSBInt(OTG_FS_INTRUSBE_SOFINTE  | OTG_FS_INTRUSBE_RSTINTE  |
                     OTG_FS_INTRUSBE_DISCINTE | OTG_FS_INTRUSBE_SREQINTE |
                     OTG_FS_INTRUSBE_VERRINTE);
    return ret;
}

/**
  * @brief  USB_FS_ReadInterrupts: return the USB interrupt status
  * @retval global interrupt register
  */
uint32_t  USB_FS_ReadInterrupts(void)
{
    uint32_t tmpreg  = 0;
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;
    uint32_t tmpreg3 = 0;

    tmpreg1 = USB_FS->INTRUSB;
    tmpreg1 &= USB_FS->INTRUSBE;

    tmpreg2 = USB_FS->INTRTX1;
    tmpreg2 &= USB_FS->INTRTX1E;

    tmpreg3 = USB_FS->INTRRX1;
    tmpreg3 &= USB_FS->INTRRX1E;

    tmpreg = ((tmpreg1) | (tmpreg2 << 8) | (tmpreg3 << 16));

    return tmpreg;
}

/**
  * @brief  USB_FS_SendStall: send STALL handshake to the endpoint
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_SendStall(USB_OTG_FS_DEPTypeDef *dep)
{
    if (dep->num == 0) /* endpoint0 */
    {
        USB_FS_IndexSel(0U);
        USB_FS->CSR0 |= OTG_FS_CSR0_SDSTALL;
    }
    else
    {
        USB_FS_IndexSel(dep->num);

        if (dep->is_in) /* tx */
        {
            USB_FS->TXCSR1 |= OTG_FS_TXCSR1_SDSTALL;
        }
        else    /* rx */
        {
            USB_FS->RXCSR1 |= OTG_FS_RXCSR1_SDSTALL;
        }
    }

    return USB_FS_OK;
}

/**
  * @brief  USB_FS_ClrStall: clear send STALL handshake to the endpoint
  * @retval USB_FS status
  */
USB_FS_StatusTypeDef USB_FS_ClrStall(USB_OTG_FS_DEPTypeDef *dep)
{
    USB_FS_IndexSel(dep->num);

    if (dep->is_in) /* tx */
    {
        USB_FS->TXCSR1 &= (~OTG_FS_TXCSR1_SDSTALL);
    }
    else    /* rx */
    {
        USB_FS->RXCSR1 &= (~OTG_FS_RXCSR1_SDSTALL);
    }

    return USB_FS_OK;
}
/**
  * @brief  USB_FS_Enable_Suspend: entry suspend mode
  * @retval none
  */
void USB_FS_Enable_Suspend(void)
{
    if ((USB_FS->DEVCTL & OTG_FS_DEVCTL_HSTMD) == OTG_FS_DEVCTL_HSTMD)
    {
        USB_FS_SetPower(OTG_FS_POWER_SUSPEND);
    }
    else
    {
        USB_FS_SetPower(OTG_FS_POWER_SUSPENDEN);
    }
}

/**
  * @brief  USB_FS_Disable_Suspend: exit suspend mode
  * @retval none
  */
void USB_FS_Disable_Suspend(void)
{
    if ((USB_FS->DEVCTL & OTG_FS_DEVCTL_HSTMD) == OTG_FS_DEVCTL_HSTMD)
    {
        USB_FS_ClrPower(OTG_FS_POWER_SUSPEND);
    }
    else
    {
        USB_FS_ClrPower(OTG_FS_POWER_SUSPENDEN);
    }
}


#endif /* defined (USB_OTG_FS) */

#endif /* defined (USB_OTG_FS) */


#endif /* defined (PCD_MODULE_ENABLED) || defined (HCD_MODULE_ENABLED) */
