/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : otgd_fs_cal.c
* Author             : STMicroelectronics
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : OTG FS Device Core Access Layer interface.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifdef STM32F10X_CL

/* Includes ------------------------------------------------------------------*/
#include "otgd_fs_cal.h"
#include "usb_conf.h"
#include "otgd_fs_regs.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

USB_OTG_CORE_REGS     core_regs;

/* Private function prototypes -----------------------------------------------*/
static uint32_t GetMode(void);
static void EnableCommonInt(void);
static USB_OTG_Status SetID(void);
static USB_OTG_Status OTGD_FS_CoreReset(void);

extern uint32_t STM32_USBH_OTG_ISR_Handler  (void);
extern uint32_t STM32_PCD_OTG_ISR_Handler (void);
extern uint32_t STM32_USBO_OTG_ISR_Handler (void);

#ifdef HOST_MODE_ENABLED
static void InitFSLSPClkSel(void);
#endif


/******************************************************************************/
/*                           Common Core Layer                                */
/******************************************************************************/

/*******************************************************************************
* Function Name  : OTGD_FS_PhyInit
* Description    : Initialize the phy
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_PhyInit(void)
{
  USB_OTG_gpio_data    gpioctl;
  USB_OTG_usb_cfg_data usbcfg;
  USB_OTG_Status status = USB_OTG_OK;

  /* Enable the I2C interface and deactivate the power down*/
  gpioctl.d32 = 0;
  gpioctl.b.vbussensingB = 1;
  gpioctl.b.pwdn = 1;
  gpioctl.b.i2cifen = 0;
  WRITE_REG32 (&core_regs.common_regs->gpio, gpioctl.d32);
  mDELAY(200);

  /* Program GUSBCFG.OtgUtmifsSel to I2C*/
  usbcfg.d32 = READ_REG32(&core_regs.common_regs->usb_cfg);
  usbcfg.b.otgutmifssel = 0;
  WRITE_REG32 (&core_regs.common_regs->usb_cfg, usbcfg.d32);

  return status;
}
/*******************************************************************************
* Function Name  : OTGD_FS_WritePacket
* Description    : Writes a packet into the Tx FIFO associated with the EP
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_WritePacket(uint8_t *src, uint8_t ch_ep_num, uint16_t bytes)
{
  USB_OTG_Status status = USB_OTG_OK;
  uint32_t dword_count , i;
  __IO uint32_t *fifo;

  /* Find the DWORD length, padded by extra bytes as neccessary if MPS
   * is not a multiple of DWORD */
  dword_count =  (bytes + 3) / 4;

  fifo = core_regs.data_fifo[ch_ep_num];

  for (i = 0; i < dword_count; i++, src += 4)
  {
    WRITE_REG32( fifo, *((__packed uint32_t *)src) );
  }

  return status;
}
/*******************************************************************************
* Function Name  : OTGD_FS_ReadPacket
* Description    : Reads a packet from the Rx FIFO
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
void* OTGD_FS_ReadPacket(uint8_t *dest, uint16_t bytes)
{
  uint32_t i;
  uint32_t word_count = (bytes + 3) / 4;

  __IO uint32_t *fifo = core_regs.data_fifo[0];
  uint32_t *data_buff = (uint32_t *)dest;

  for (i = 0; i < word_count; i++, data_buff++)
  {
    *data_buff = READ_REG32(fifo);
  }

  /* Return the buffer pointer because if the transfer is composed of several packets,
     the data of the next packet must be stored following the previous packet's data         */
  return ((void *)data_buff);
}
/*******************************************************************************
* Function Name  : EnableCommonInt
* Description    : initializes the commmon interrupts, used in both device and
                   host modes
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void EnableCommonInt(void)
{

  USB_OTG_int_msk_data int_mask;
  int_mask.d32 = 0;

  /* Clear any pending USB_OTG Interrupts */
  WRITE_REG32( &core_regs.common_regs->otg_int, 0xFFFFFFFF);

  /* Clear any pending common interrupts */
  WRITE_REG32( &core_regs.common_regs->int_sts, 0xFFFFFFFF);

  WRITE_REG32( &core_regs.common_regs->int_msk, int_mask.d32);
}
/*******************************************************************************
* Function Name  : OTGD_FS_SetAddress
* Description    : Initialize core registers addresses.
* Input          : BaseAddress
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_Status OTGD_FS_SetAddress(uint32_t BaseAddress)
{
  uint32_t i = 0;
  USB_OTG_Status status = USB_OTG_OK;
  core_regs.common_regs = (USB_OTG_common_regs *)(BaseAddress + USB_OTG_CORE_GLOBAL_REGS_OFFSET);
  core_regs.dev_regs =  (USB_OTG_dev_regs  *)  (BaseAddress + USB_OTG_DEV_GLOBAL_REG_OFFSET);

  for (i = 0; i < MAX_EPS_CHANNELS; i++)
  {
    core_regs.inep_regs[i]  = (USB_OTG_dev_in_ep_regs *)  (BaseAddress + USB_OTG_DEV_IN_EP_REG_OFFSET + (i * USB_OTG_EP_REG_OFFSET));
    core_regs.outep_regs[i] = (USB_OTG_dev_out_ep_regs *) (BaseAddress + USB_OTG_DEV_OUT_EP_REG_OFFSET + (i * USB_OTG_EP_REG_OFFSET));
  }

  core_regs.host_regs = (USB_OTG_host_regs *)(BaseAddress + USB_OTG_HOST_GLOBAL_REG_OFFSET);
  core_regs.hprt0 = (uint32_t *)(BaseAddress + USB_OTG_HOST_PORT_REGS_OFFSET);

  for (i = 0; i < MAX_EPS_CHANNELS; i++)
  {
    core_regs.hc_regs[i] = (USB_OTG_hc_regs *)(BaseAddress + USB_OTG_HOST_CHAN_REGS_OFFSET + (i * USB_OTG_CHAN_REGS_OFFSET));
  }


  for (i = 0; i < MAX_EPS_CHANNELS; i++)
  {
    core_regs.data_fifo[i] = (uint32_t *)(BaseAddress + USB_OTG_DATA_FIFO_OFFSET + (i * USB_OTG_DATA_FIFO_SIZE));
  }

  core_regs.pcgcctl = (uint32_t *)(BaseAddress + USB_OTG_PCGCCTL_OFFSET);

  return status;
}
/*******************************************************************************
* Function Name  : OTGD_FS_CoreInit
* Description    : Initialize the USB_OTG controller registers and prepares the core
                   for device mode or host mode operation.
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_CoreInit(void)
{
  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_usb_cfg_data usbcfg;

  usbcfg.d32 = 0;

  /* Reset the Controller */
  OTGD_FS_CoreReset();

  usbcfg.d32 = READ_REG32(&core_regs.common_regs->usb_cfg);
  usbcfg.b.physel = 1;
  WRITE_REG32 (&core_regs.common_regs->usb_cfg, usbcfg.d32);

  /* init and configure the phy */
  OTGD_FS_PhyInit();

  /* Reset after a PHY select and set Host mode */
  OTGD_FS_CoreReset();

  /* Set Host or Device Mode */
  SetID();

  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_CoreReset
* Description    : Soft reset of the core
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
static USB_OTG_Status OTGD_FS_CoreReset(void)
{
  USB_OTG_Status status = USB_OTG_OK;
  __IO USB_OTG_rst_ctl_data greset;
  uint32_t count = 0;
  greset.d32 = 0;

  /* Wait for AHB master IDLE state. */
  do
  {
    uDELAY(3);
    greset.d32 = READ_REG32(&core_regs.common_regs->rst_ctl);
    if (++count > 200000)
    {
      return USB_OTG_OK;
    }
  }
  while (greset.b.ahbidle == 0);

  /* Core Soft Reset */
  count = 0;
  greset.b.csftrst = 1;
  WRITE_REG32(&core_regs.common_regs->rst_ctl, greset.d32 );
  do
  {
    greset.d32 = READ_REG32(&core_regs.common_regs->rst_ctl);
    if (++count > 200000)
    {
      break;
    }
  }
  while (greset.b.csftrst == 1);

  /* Wait for 3 PHY Clocks*/
  uDELAY(10);
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_EnableGlobalInt
* Description    : Enables the controller's Global Int in the AHB Config reg
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_EnableGlobalInt(void)
{
  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_ahb_cfg_data ahb_cfg;

  ahb_cfg.d32 = 0;
  ahb_cfg.b.glblintrmsk = 1; /* Enable interrupts */
  MODIFY_REG32(&core_regs.common_regs->ahb_cfg, 0, ahb_cfg.d32);
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_DisableGlobalInt
* Description    : Disables the controller's Global Int in the AHB Config reg
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_DisableGlobalInt(void)
{
  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_ahb_cfg_data ahbcfg;

  ahbcfg.d32 = 0;
  ahbcfg.b.glblintrmsk = 1; /* Enable interrupts */
  MODIFY_REG32(&core_regs.common_regs->ahb_cfg, ahbcfg.d32, 0);
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_FlushTxFifo
* Description    : Flush a Tx FIFO
* Input          : FIFO num
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_Status OTGD_FS_FlushTxFifo (uint32_t num )
{

  USB_OTG_Status status = USB_OTG_OK;
  __IO USB_OTG_rst_ctl_data greset;
  int count = 0;

  greset.d32 = 0;
  greset.b.txfflsh = 1;
  greset.b.txfnum  = num;
  WRITE_REG32( &core_regs.common_regs->rst_ctl, greset.d32 );

  do
  {
    greset.d32 = READ_REG32( &core_regs.common_regs->rst_ctl);
    if (++count > 200000)
    {
      break;
    }
  }
  while (greset.b.txfflsh == 1);

  /* Wait for 3 PHY Clocks*/
  uDELAY(3);

  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_FlushRxFifo
* Description    : Flush a Rx FIFO
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_Status OTGD_FS_FlushRxFifo( void )
{
  USB_OTG_Status status = USB_OTG_OK;
  __IO USB_OTG_rst_ctl_data greset;
  int count = 0;

  greset.d32 = 0;
  greset.b.rxfflsh = 1;
  WRITE_REG32( &core_regs.common_regs->rst_ctl, greset.d32 );

  do
  {
    greset.d32 = READ_REG32( &core_regs.common_regs->rst_ctl);
    if (++count > 200000)
    {
      break;
    }
  }
  while (greset.b.rxfflsh == 1);

  /* Wait for 3 PHY Clocks*/
  uDELAY(3);

  return status;
}

/*******************************************************************************
* Function Name  : SetID
* Description    : Set ID line
* Input          : None
* Output         : None
* Return         : num_in_ep
*******************************************************************************/
USB_OTG_Status SetID(void)
{

  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_usb_cfg_data usbcfg;

  usbcfg.d32 = READ_REG32(&core_regs.common_regs->usb_cfg);

  usbcfg.b.force_dev = 1;

  WRITE_REG32(&core_regs.common_regs->usb_cfg, usbcfg.d32);

  mDELAY(50);

  return status;
}

/*******************************************************************************
* Function Name  : GetMode
* Description    : Get current mode
* Input          : None
* Output         : None
* Return         : current mode
*******************************************************************************/
static uint32_t GetMode(void)
{
  return (READ_REG32(&core_regs.common_regs->int_sts ) & 0x1);
}

/*******************************************************************************
* Function Name  : IsDeviceMode
* Description    : Check if it is device mode
* Input          : None
* Output         : None
* Return         : num_in_ep
*******************************************************************************/
uint8_t IsDeviceMode(void)
{
  return (GetMode() != HOST_MODE);
}

/*******************************************************************************
* Function Name  : IsHostMode
* Description    : Check if it is host mode
* Input          : None
* Output         : None
* Return         : num_in_ep
*******************************************************************************/
uint8_t IsHostMode(void)
{
  return (GetMode() == HOST_MODE);
}

/*******************************************************************************
* Function Name  : OTGD_FS_ReadCoreItr
* Description    : returns the Core Interrupt register
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t OTGD_FS_ReadCoreItr(void)
{
  uint32_t v;

  v = READ_REG32(&core_regs.common_regs->int_sts);
  v &= READ_REG32(&core_regs.common_regs->int_msk);

  return v;
}

/*******************************************************************************
* Function Name  : OTGD_FS_ReadOtgItr
* Description    : returns the USB_OTG Interrupt register
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t OTGD_FS_ReadOtgItr (void)
{
  return (READ_REG32 (&core_regs.common_regs->otg_int));
}

/******************************************************************************/
/*                           PCD Core Layer                                   */
/******************************************************************************/

/*******************************************************************************
* Function Name  : InitDevSpeed
* Description    : Initializes the DevSpd field of the DCFG register depending
                   on the PHY type and the enumeration speed of the device.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void InitDevSpeed(void)
{
  USB_OTG_dev_cfg_data  dcfg;

  dcfg.d32 = READ_REG32(&core_regs.dev_regs->dev_cfg);
  dcfg.b.devspd = 0x3;  /* Full speed PHY */
  WRITE_REG32(&core_regs.dev_regs->dev_cfg, dcfg.d32);
}
/*******************************************************************************
* Function Name  : OTGD_FS_CoreInitDev
* Description    : Initialize the USB_OTG controller registers for device mode
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_CoreInitDev (void)
{
  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_dev_ep_ctl_data   depctl;
  uint32_t i;

  USB_OTG_dev_cfg_data   dcfg;
  USB_OTG_fifo_size_data nptxfifosize;
  USB_OTG_fifo_size_data txfifosize;
  USB_OTG_dev_in_ep_msk_data msk;

  dcfg.d32 = 0;

  /* Set device speed */
  InitDevSpeed ();

  /* Restart the Phy Clock */
  WRITE_REG32(core_regs.pcgcctl, 0);

  /* Device configuration register */
  dcfg.d32 = READ_REG32( &core_regs.dev_regs->dev_cfg);
  dcfg.b.perfrint = DCFG_FRAME_INTERVAL_80;
  WRITE_REG32( &core_regs.dev_regs->dev_cfg, dcfg.d32 );

  /* set Rx FIFO size */
  WRITE_REG32( &core_regs.common_regs->rx_fifo_siz, RX_FIFO_SIZE);

  /* Non-periodic Tx FIFO */
  nptxfifosize.b.depth     = DEV_NP_TX_FIFO_SIZE;
  nptxfifosize.b.startaddr = RX_FIFO_SIZE;

  WRITE_REG32( &core_regs.common_regs->np_tx_fifo_siz, nptxfifosize.d32 );

  txfifosize.b.depth = DEV_NP_TX_FIFO_SIZE;
  WRITE_REG32( &core_regs.common_regs->dev_p_tx_fsiz_dieptxf[0], txfifosize.d32 );
  txfifosize.b.startaddr += txfifosize.b.depth;
  txfifosize.b.startaddr = nptxfifosize.b.startaddr + nptxfifosize.b.depth;
  
  /* Flush the FIFOs */
  OTGD_FS_FlushTxFifo(0x10); /* all Tx FIFOs */
  OTGD_FS_FlushRxFifo();

  /* Clear all pending Device Interrupts */
  WRITE_REG32( &core_regs.dev_regs->dev_in_ep_msk, 0 );
  WRITE_REG32( &core_regs.dev_regs->dev_out_ep_msk, 0 );
  WRITE_REG32( &core_regs.dev_regs->dev_all_int, 0xFFFFFFFF );
  WRITE_REG32( &core_regs.dev_regs->dev_all_int_msk, 0 );

  for (i = 0; i <= MAX_TX_FIFOS; i++)
  {
    depctl.d32 = READ_REG32(&core_regs.inep_regs[i]->dev_in_ep_ctl);
    if (depctl.b.epena)
    {
      depctl.d32 = 0;
      depctl.b.epdis = 1;
      depctl.b.snak = 1;
    }
    else
    {
      depctl.d32 = 0;
    }

    WRITE_REG32( &core_regs.inep_regs[i]->dev_in_ep_ctl, depctl.d32);


    WRITE_REG32( &core_regs.inep_regs[i]->dev_in_ep_txfer_siz, 0);
    WRITE_REG32( &core_regs.inep_regs[i]->dev_in_ep_int, 0xFF);
  }

  for (i = 0; i < 1/* NUM_OUT_EPS*/; i++)
  {
    depctl.d32 = READ_REG32(&core_regs.outep_regs[i]->dev_out_ep_ctl);
    if (depctl.b.epena)
    {
      depctl.d32 = 0;
      depctl.b.epdis = 1;
      depctl.b.snak = 1;
    }
    else
    {
      depctl.d32 = 0;
    }

    WRITE_REG32( &core_regs.outep_regs[i]->dev_out_ep_ctl, depctl.d32);

    WRITE_REG32( &core_regs.outep_regs[i]->dev_out_ep_txfer_siz, 0);
    WRITE_REG32( &core_regs.outep_regs[i]->dev_out_ep_int, 0xFF);
  }

  msk.d32 = 0;
  msk.b.txfifoundrn = 1;
  MODIFY_REG32(&core_regs.dev_regs->dev_in_ep_msk, msk.d32, msk.d32);

  OTGD_FS_EnableDevInt();

  return status;
}
/*******************************************************************************
* Function Name  : OTGD_FS_EnableDevInt
* Description    : Enables the Device mode interrupts
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_Status OTGD_FS_EnableDevInt(void)
{

  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_int_msk_data intr_mask;

  intr_mask.d32 = 0;

  /* Disable all interrupts. */
  WRITE_REG32( &core_regs.common_regs->int_msk, 0);

  /* Clear any pending interrupts */
  WRITE_REG32( &core_regs.common_regs->int_sts, 0xFFFFFFFF);

  /* Enable the common interrupts */
  EnableCommonInt();
  
  /* Enable the defined interrupts*/
#ifdef INTR_MODEMISMATCH
  intr_mask.b.modemismatch = 1;
#endif /* INTR_MODEMISMATCH */
#ifdef INTR_SOFINTR
  intr_mask.b.sofintr = 1;
#endif /* INTR_SOFINTR */
#ifdef INTR_RXSTSQLVL
  intr_mask.b.rxstsqlvl = 1;
#endif /* INTR_RXSTSQLVL */
#ifdef INTR_NPTXFEMPTY
  intr_mask.b.nptxfempty = 1;
#endif /* INTR_NPTXFEMPTY */
#ifdef INTR_GINNAKEFF
  intr_mask.b.ginnakeff = 1;
#endif /* INTR_GINNAKEFF */
#ifdef INTR_GOUTNAKEFF
  intr_mask.b.goutnakeff = 1;
#endif /* INTR_GOUTNAKEFF */
#ifdef INTR_ERLYSUSPEND
  intr_mask.b.erlysuspend = 1;
#endif /* INTR_ERLYSUSPEND */
#ifdef INTR_USBSUSPEND
  intr_mask.b.usbsuspend = 1;
#endif /* INTR_USBSUSPEND */
#ifdef INTR_USBRESET
  intr_mask.b.usbreset = 1;
#endif /* INTR_USBRESET */
#ifdef INTR_ENUMDONE
  intr_mask.b.enumdone = 1;
#endif /* INTR_ENUMDONE */
#ifdef INTR_ISOOUTDROP
  intr_mask.b.isooutdrop = 1;
#endif /* INTR_ISOOUTDROP */
#ifdef INTR_EOPFRAME
  intr_mask.b.eopframe = 1;
#endif /* INTR_EOPFRAME */
#ifdef INTR_EPMISMATCH
  intr_mask.b.epmismatch = 1;
#endif /* INTR_EPMISMATCH */
#ifdef INTR_INEPINTR
  intr_mask.b.inepintr = 1;
#endif /* INTR_INEPINTR */
#ifdef INTR_OUTEPINTR
  intr_mask.b.outepintr = 1;
#endif /* INTR_OUTEPINTR */
#ifdef INTR_INCOMPLISOIN
  intr_mask.b.incomplisoin = 1;
#endif /* INTR_INCOMPLISOIN */
#ifdef INTR_INCOMPLISOOUT
  intr_mask.b.incomplisoout = 1;
#endif /* INTR_INCOMPLISOOUT */
#ifdef INTR_DISCONNECT
  intr_mask.b.disconnect = 1;
#endif /* INTR_DISCONNECT */
#ifdef INTR_WKUPINTR
  intr_mask.b.wkupintr = 1;
#endif /* INTR_WKUPINTR */

  MODIFY_REG32( &core_regs.common_regs->int_msk, intr_mask.d32, intr_mask.d32);
  return status;
  
}
/*******************************************************************************
* Function Name  : OTGD_FS_EP0Activate
* Description    : enables EP0 OUT to receive SETUP packets and configures EP0
                   IN for transmitting packets
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_Status  OTGD_FS_EP0Activate(void)
{
  USB_OTG_Status          status = USB_OTG_OK;
  USB_OTG_dev_sts_data    dsts;
  USB_OTG_dev_ep_ctl_data diepctl;
  USB_OTG_dev_ctl_data    dctl;

  dctl.d32 = 0;
  /* Read the Device Status and Endpoint 0 Control registers */
  dsts.d32 = READ_REG32(&core_regs.dev_regs->dev_sts);
  diepctl.d32 = READ_REG32(&core_regs.inep_regs[0]->dev_in_ep_ctl);

  /* Set the MPS of the IN EP based on the enumeration speed */
  switch (dsts.b.enumspd)
  {
    case DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
    case DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
    case DSTS_ENUMSPD_FS_PHY_48MHZ:
      diepctl.b.mps = DEP0CTL_MPS_64;
      break;
    case DSTS_ENUMSPD_LS_PHY_6MHZ:
      diepctl.b.mps = DEP0CTL_MPS_8;
      break;
  }

  WRITE_REG32(&core_regs.inep_regs[0]->dev_in_ep_ctl, diepctl.d32);
  dctl.b.cgnpinnak = 1;
  MODIFY_REG32(&core_regs.dev_regs->dev_ctl, dctl.d32, dctl.d32);
  return status;
}
/*******************************************************************************
* Function Name  : OTGD_FS_EPActivate
* Description    : Activates an EP
* Input          : ep
* Output         : None
* Return         : num_in_ep
*******************************************************************************/
USB_OTG_Status OTGD_FS_EPActivate(USB_OTG_EP *ep)
{

  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_dev_ep_ctl_data depctl;
  __IO uint32_t *addr;
  USB_OTG_dev_all_int_data daintmsk;
  daintmsk.d32 = 0;

  /* Read DEPCTLn register */
  if (ep->is_in == 1)
  {
    addr = &core_regs.inep_regs[ep->num]->dev_in_ep_ctl;
    daintmsk.ep.in = 1 << ep->num;
  }
  else
  {
    addr = &core_regs.outep_regs[ep->num]->dev_out_ep_ctl;
    daintmsk.ep.out = 1 << ep->num;
  }

  /* If the EP is already active don't change the EP Control
   * register. */
  depctl.d32 = READ_REG32(addr);
  if (!depctl.b.usbactep)
  {
    depctl.b.mps    = ep->maxpacket;
    depctl.b.eptype = ep->type;
    depctl.b.txfnum = ep->tx_fifo_num;
    depctl.b.setd0pid = 1;
    depctl.b.usbactep = 1;
    WRITE_REG32(addr, depctl.d32);
  }

  /* Enable the Interrupt for this EP */
  MODIFY_REG32(&core_regs.dev_regs->dev_all_int_msk, 0, daintmsk.d32);
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_EPDeactivate
* Description    : Deactivates an EP
* Input          : ep
* Output         : None
* Return         : num_in_ep
*******************************************************************************/
USB_OTG_Status OTGD_FS_EPDeactivate(USB_OTG_EP *ep)
{

  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_dev_ep_ctl_data depctl;
  __IO uint32_t *addr;
  USB_OTG_dev_all_int_data daintmsk;
  depctl.d32 = 0;
  daintmsk.d32 = 0;

  /* Read DEPCTLn register */
  if (ep->is_in == 1)
  {
    addr = &core_regs.inep_regs[ep->num]->dev_in_ep_ctl;
    daintmsk.ep.in = 1 << ep->num;
  }
  else
  {
    addr = &core_regs.outep_regs[ep->num]->dev_out_ep_ctl;
    daintmsk.ep.out = 1 << ep->num;
  }

  depctl.b.usbactep = 0;
  WRITE_REG32(addr, depctl.d32);

  /* Disable the Interrupt for this EP */
  MODIFY_REG32(&core_regs.dev_regs->dev_all_int_msk, daintmsk.d32, 0);
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_EPStartXfer
* Description    : Handle the setup for data xfer for an EP and starts the xfer
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_Status OTGD_FS_EPStartXfer(USB_OTG_EP *ep)
{

  USB_OTG_Status status = USB_OTG_OK;
  __IO USB_OTG_dev_ep_ctl_data depctl;
  USB_OTG_dev_ep_txfer_siz_data deptsiz;

  /* IN endpoint */
  if (ep->is_in == 1)
  {

    depctl.d32  = READ_REG32(&(core_regs.inep_regs[ep->num]->dev_in_ep_ctl));
    deptsiz.d32 = READ_REG32(&(core_regs.inep_regs[ep->num]->dev_in_ep_txfer_siz));

    /* Zero Length Packet? */
    if (ep->xfer_len == 0)
    {
      deptsiz.b.xfersize = 0;
      deptsiz.b.pktcnt = 1;

    }
    else
    {
      /* Program the transfer size and packet count
       * as follows: xfersize = N * maxpacket +
       * short_packet pktcnt = N + (short_packet
       * exist ? 1 : 0)
       */
      deptsiz.b.xfersize = ep->xfer_len;
      deptsiz.b.pktcnt = (ep->xfer_len - 1 + ep->maxpacket) / ep->maxpacket;
    }
    WRITE_REG32(&core_regs.inep_regs[ep->num]->dev_in_ep_txfer_siz, deptsiz.d32);

    if (ep->type != EP_TYPE_ISOC)
    {
      /* Enable the Tx FIFO Empty Interrupt for this EP */
      uint32_t fifoemptymsk = 0;
      fifoemptymsk = 1 << ep->num;
      MODIFY_REG32(&core_regs.dev_regs->dev_fifo_empty_msk, 0, fifoemptymsk);
    }
   
    /* EP enable, IN data in FIFO */
    depctl.b.cnak = 1;
    depctl.b.epena = 1;
    WRITE_REG32(&core_regs.inep_regs[ep->num]->dev_in_ep_ctl, depctl.d32);
    
    depctl.d32 = READ_REG32 (&core_regs.inep_regs[0]->dev_in_ep_ctl);
    depctl.b.nextep = ep->num;
    WRITE_REG32 (&core_regs.inep_regs[0]->dev_in_ep_ctl, depctl.d32);    
  }
  else
  {
    /* OUT endpoint */
    depctl.d32  = READ_REG32(&(core_regs.outep_regs[ep->num]->dev_out_ep_ctl));
    deptsiz.d32 = READ_REG32(&(core_regs.outep_regs[ep->num]->dev_out_ep_txfer_siz));

    /* Program the transfer size and packet count as follows:
     * pktcnt = N
     * xfersize = N * maxpacket
     */
    if (ep->xfer_len == 0)
    {
      deptsiz.b.xfersize = ep->maxpacket;
      deptsiz.b.pktcnt = 1;
    }
    else
    {
      deptsiz.b.pktcnt = (ep->xfer_len + (ep->maxpacket - 1)) / ep->maxpacket;
      deptsiz.b.xfersize = deptsiz.b.pktcnt * ep->maxpacket;
    }
    WRITE_REG32(&core_regs.outep_regs[ep->num]->dev_out_ep_txfer_siz, deptsiz.d32);

    if (ep->type == EP_TYPE_ISOC)
    {

      if (ep->even_odd_frame)
      {
        depctl.b.setd1pid = 1;
      }
      else
      {
        depctl.b.setd0pid = 1;
      }
    }

    /* EP enable */
    depctl.b.cnak = 1;
    depctl.b.epena = 1;

    WRITE_REG32(&core_regs.outep_regs[ep->num]->dev_out_ep_ctl, depctl.d32);

  }
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_EP0StartXfer
* Description    : Handle the setup for a data xfer for EP0 and starts the xfer
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_Status OTGD_FS_EP0StartXfer(USB_OTG_EP *ep)
{

  USB_OTG_Status                    status = USB_OTG_OK;
  uint32_t                               fifoemptymsk = 0;
  USB_OTG_dev_ep_ctl_data           depctl;
  USB_OTG_dev_ep_txfer_size0_data   deptsiz;
  USB_OTG_dev_in_ep_regs            *in_regs ;

  /* IN endpoint */
  if (ep->is_in == 1)
  {
    in_regs = core_regs.inep_regs[0];
    depctl.d32  = READ_REG32(&in_regs->dev_in_ep_ctl);
    deptsiz.d32 = READ_REG32(&in_regs->dev_in_ep_txfer_siz);

    /* Zero Length Packet? */
    if (ep->xfer_len == 0)
    {
      deptsiz.b.xfersize = 0;
      deptsiz.b.pktcnt = 1;
    }
    else
    {
      if (ep->xfer_len > ep->maxpacket)
      {
        ep->xfer_len = ep->maxpacket;
        deptsiz.b.xfersize = ep->maxpacket;
      }
      else
      {
        deptsiz.b.xfersize = ep->xfer_len;
      }
      deptsiz.b.pktcnt = 1;

    }
    WRITE_REG32(&in_regs->dev_in_ep_txfer_siz, deptsiz.d32);

    /* EP enable, IN data in FIFO */
    depctl.b.cnak = 1;
    depctl.b.epena = 1;
    WRITE_REG32(&in_regs->dev_in_ep_ctl, depctl.d32);

    /* Enable the Tx FIFO Empty Interrupt for this EP */
    if (ep->xfer_len > 0)
    {
      fifoemptymsk |= 1 << ep->num;
      MODIFY_REG32(&core_regs.dev_regs->dev_fifo_empty_msk, 0, fifoemptymsk);
    }
  }
  else
  {
    /* OUT endpoint */
    depctl.d32  = READ_REG32(&core_regs.outep_regs[ep->num]->dev_out_ep_ctl);
    deptsiz.d32 = READ_REG32(&core_regs.outep_regs[ep->num]->dev_out_ep_txfer_siz);

    /* Program the transfer size and packet count as follows:
     * xfersize = N * (maxpacket + 4 - (maxpacket % 4))
     * pktcnt = N           */
    if (ep->xfer_len == 0)
    {
      deptsiz.b.xfersize = ep->maxpacket;
      deptsiz.b.pktcnt = 1;
    }
    else
    {
      deptsiz.b.pktcnt = (ep->xfer_len + (ep->maxpacket - 1)) / ep->maxpacket;
      deptsiz.b.xfersize = deptsiz.b.pktcnt * ep->maxpacket;
    }

    WRITE_REG32(&core_regs.outep_regs[ep->num]->dev_out_ep_txfer_siz, deptsiz.d32);

    /* EP enable */
    depctl.b.cnak = 1;
    depctl.b.epena = 1;
    WRITE_REG32 (&(core_regs.outep_regs[ep->num]->dev_out_ep_ctl), depctl.d32);
  }
  return status;
}
/*******************************************************************************
* Function Name  : OTGD_FS_EPSetStall
* Description    : Set the EP STALL
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_EPSetStall(USB_OTG_EP *ep)
{
  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_dev_ep_ctl_data depctl; 
  __IO uint32_t *depctl_addr;

  if (ep->is_in == 1)
  {
    depctl_addr = &(core_regs.inep_regs[ep->num]->dev_in_ep_ctl);
    depctl.d32 = READ_REG32(depctl_addr);

    /* set the disable and stall bits */
    if (depctl.b.epena)
    {
      depctl.b.epdis = 1;
    }
    depctl.b.stall = 1;
    WRITE_REG32(depctl_addr, depctl.d32);
  }
  else
  {
    depctl_addr = &(core_regs.outep_regs[ep->num]->dev_out_ep_ctl);
    depctl.d32 = READ_REG32(depctl_addr);

    /* set the stall bit */
    depctl.b.stall = 1;
    WRITE_REG32(depctl_addr, depctl.d32);
  }
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_EPClearStall
* Description    : Clear the EP STALL
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
USB_OTG_Status OTGD_FS_EPClearStall(USB_OTG_EP *ep)
{
  USB_OTG_Status status = USB_OTG_OK;
  USB_OTG_dev_ep_ctl_data depctl;
  __IO uint32_t *depctl_addr;

  if (ep->is_in == 1)
  {
    depctl_addr = &(core_regs.inep_regs[ep->num]->dev_in_ep_ctl);
  }
  else
  {
    depctl_addr = &(core_regs.outep_regs[ep->num]->dev_out_ep_ctl);
  }

  
  depctl.d32 = READ_REG32(depctl_addr);
   
  /* clear the stall bits */
  depctl.b.stall = 0;

  if (ep->type == EP_TYPE_INTR || ep->type == EP_TYPE_BULK)
  {
    depctl.b.setd0pid = 1; /* DATA0 */
  }

  WRITE_REG32(depctl_addr, depctl.d32);
  return status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_ReadDevAllOutEp_itr
* Description    : returns the OUT endpoint interrupt bits
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t OTGD_FS_ReadDevAllOutEp_itr(void)
{
  uint32_t v;
  v  = READ_REG32(&core_regs.dev_regs->dev_all_int);
  v &= READ_REG32(&core_regs.dev_regs->dev_all_int_msk);
  return ((v & 0xffff0000) >> 16);
}

/*******************************************************************************
* Function Name  : OTGD_FS_ReadDevOutEP_itr
* Description    : returns the Device OUT EP Interrupt register
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t OTGD_FS_ReadDevOutEP_itr(USB_OTG_EP *ep)
{
  uint32_t v;
  v  = READ_REG32(&core_regs.outep_regs[ep->num]->dev_out_ep_int);
  v &= READ_REG32(&core_regs.dev_regs->dev_out_ep_msk);
  return v;
}
/*******************************************************************************
* Function Name  : OTGD_FS_ReadDevAllInEPItr
* Description    : Get int status register
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t OTGD_FS_ReadDevAllInEPItr(void)
{
  uint32_t v;
  v = READ_REG32(&core_regs.dev_regs->dev_all_int);
  v &= READ_REG32(&core_regs.dev_regs->dev_all_int_msk);
  return (v & 0xffff);
}

/*******************************************************************************
* Function Name  : OTGD_FS_Dev_GetEPStatus
* Description    : returns the EP Status 
* Input          : - ep: pointer to the EP structure
* Output         : None
* Return         : status: DEV_EP_TX_STALL, DEV_EP_TX_VALID, DEV_EP_TX_NAK, 
*                  DEV_EP_RX_STALL, DEV_EP_RX_VALID or DEV_EP_RX_NAK,
*******************************************************************************/
uint32_t OTGD_FS_Dev_GetEPStatus(USB_OTG_EP *ep)
{
  USB_OTG_dev_ep_ctl_data depctl;
  __IO uint32_t *depctl_addr;
  uint32_t Status = 0;

  if (ep->is_in == 1)
  {
    depctl_addr = &(core_regs.inep_regs[ep->num]->dev_in_ep_ctl);
  }
  else
  {
    depctl_addr = &(core_regs.outep_regs[ep->num]->dev_out_ep_ctl);
  }

  depctl.d32 = READ_REG32(depctl_addr);

  /* Process for IN endpoint */
  if (ep->is_in == 1)
  {
    if (depctl.b.stall == 1)  
      Status = DEV_EP_TX_STALL;
    else if (depctl.b.naksts == 1)
      Status = DEV_EP_TX_NAK;
    else 
      Status = DEV_EP_TX_VALID; 
  } 
  /* Process for OUT endpoint */
  else 
  {
    if (depctl.b.stall == 1)  
      Status = DEV_EP_RX_STALL;
    else if (depctl.b.naksts == 1)
      Status = DEV_EP_RX_NAK;
    else 
      Status = DEV_EP_RX_VALID; 
  }
  
  /* Return the current status */
  return Status;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Dev_SetEPStatus
* Description    : Sets the EP Status 
* Input          : - ep: pointer to the EP structure
*                  - Status: new status to be set
* Output         : None
* Return         : None
*******************************************************************************/
void OTGD_FS_Dev_SetEPStatus(USB_OTG_EP *ep, uint32_t Status)
{
  USB_OTG_dev_ep_ctl_data depctl;
  __IO uint32_t *depctl_addr;

  if (ep->is_in == 1)
  {
    depctl_addr = &(core_regs.inep_regs[ep->num]->dev_in_ep_ctl);
  }
  else
  {
    depctl_addr = &(core_regs.outep_regs[ep->num]->dev_out_ep_ctl);
  }

  depctl.d32 = READ_REG32(depctl_addr);

  /* Process for IN endpoint */
  if (ep->is_in == 1)
  {
    if (Status == DEV_EP_TX_STALL)  
    {
      OTGD_FS_EPSetStall(ep); return;
    }
    else if (Status == DEV_EP_TX_NAK)
      depctl.b.snak = 1;
    else if (Status == DEV_EP_TX_VALID)
    {
      if (depctl.b.stall == 1)
      {  
        ep->even_odd_frame = 0;
        OTGD_FS_EPClearStall(ep);
        return;
      }      
      depctl.b.cnak = 1;
      depctl.b.usbactep = 1; 
      depctl.b.epena = 1;
    }
    else if (Status == DEV_EP_TX_DIS)
      depctl.b.usbactep = 0;
  } 
  else /* Process for OUT endpoint */
  {
    if (Status == DEV_EP_RX_STALL)  
      depctl.b.stall = 1;
    else if (Status == DEV_EP_RX_NAK)
      depctl.b.snak = 1;
    else if (Status == DEV_EP_RX_VALID)
    {
      if (depctl.b.stall == 1)
      {  
        ep->even_odd_frame = 0;
        OTGD_FS_EPClearStall(ep);
        return;
      }  
      depctl.b.cnak = 1;
      depctl.b.usbactep = 1;    
      depctl.b.epena = 1;
    }
    else if (Status == DEV_EP_RX_DIS)
    {
      depctl.b.usbactep = 0;    
    }
  }

  if (ep->type == EP_TYPE_INTR || ep->type == EP_TYPE_BULK)
  {
    depctl.b.setd0pid = 1; /* DATA0 */
  }

  WRITE_REG32(depctl_addr, depctl.d32); 
}

/*******************************************************************************
* Function Name  : OTGD_FS_Dev_SetRemoteWakeup
* Description    : Enable Remote wakeup signaling
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
void OTGD_FS_Dev_SetRemoteWakeup()
{
 USB_OTG_dev_ctl_data devctl;
 __IO uint32_t *dctl_addr;
 
 dctl_addr = &(core_regs.dev_regs->dev_ctl);
 
 devctl.d32 = READ_REG32( dctl_addr);
 
 /* Enable the Remote Wakeup signal */
 devctl.b.rmtwkupsig = 1;
 
 WRITE_REG32(dctl_addr, devctl.d32);
}

/*******************************************************************************
* Function Name  : OTGD_FS_Dev_ResetRemoteWakeup
* Description    : Disable Remote wakeup signaling
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
void OTGD_FS_Dev_ResetRemoteWakeup()
{
 USB_OTG_dev_ctl_data devctl;
 __IO uint32_t *dctl_addr;
 
 dctl_addr = &(core_regs.dev_regs->dev_ctl);
 
 devctl.d32 = READ_REG32( dctl_addr);
 
 /* Disable the Remote Wakeup signal */
 devctl.b.rmtwkupsig = 0;
 
 
 WRITE_REG32(dctl_addr, devctl.d32);
}
#endif /* STM32F10X_CL */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
