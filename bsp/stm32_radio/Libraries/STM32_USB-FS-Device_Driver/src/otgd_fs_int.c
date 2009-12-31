/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : otgd_fs_int.c
* Author             : MCD Application Team
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : Endpoint interrupt's service routines.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifdef STM32F10X_CL

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_type.h"
#include "otgd_fs_int.h"
#include "usb_lib.h"
#include "usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Max size of the received OUT Non periodic packet */
#define MAX_OUT_PKT_SIZE    160

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t USBD_Data_Buffer  [MAX_OUT_PKT_SIZE];
__IO uint8_t IsocBuff [(ISOC_BUFFER_SZE * NUM_SUB_BUFFERS)];
__IO uint32_t IsocBufferIdx = 0;

extern USB_OTG_CORE_REGS  core_regs;

__IO uint16_t SaveRState;
__IO uint16_t SaveTState;

/* Extern variables ----------------------------------------------------------*/
extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void);   /*  Handles OUT interrupts   */

/* Private function prototypes -----------------------------------------------*/
static uint32_t OTGD_FS_PCD_ReadDevInEP( USB_OTG_EP *ep);
static enum usb_device_speed OTGD_FS_PCD_GetDeviceSpeed(void);
static uint32_t OTGD_FS_PCD_WriteEmptyTxFifo(uint32_t epnum);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_ModeMismatch_ISR
* Description    : Handles the Mode Mismatch error interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_ModeMismatch_ISR(void)
{
  USB_OTG_int_sts_data gintsts;  
  
  INTR_MODEMISMATCH_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.modemismatch = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_Sof_ISR
* Description    : Handles the Start Of Frame detected interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_Sof_ISR(void)
{
  USB_OTG_int_sts_data int_sts;
  
  /* Call user function */
  INTR_SOFINTR_Callback();
    
  /* Clear interrupt */
  int_sts.d32 = 0;
  int_sts.b.sofintr = 1;
  WRITE_REG32 (&core_regs.common_regs->int_sts, int_sts.d32);

  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_RxStatusQueueLevel_ISR
* Description    : Handles the Rx Status Queue Level Interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_RxStatusQueueLevel_ISR(void)
{
  USB_OTG_int_msk_data int_mask;
  USB_OTG_dev_rx_sts_data status;
  /* USB_OTG_int_sts_data int_sts; */
  USB_OTG_EP *ep;

  /* Disable the Rx Status Queue Level interrupt */
  int_mask.b.rxstsqlvl = 1;
  MODIFY_REG32( &core_regs.common_regs->int_msk, int_mask.d32, 0);

  /* Get the Status from the top of the FIFO */
  status.d32 = READ_REG32( &core_regs.common_regs->rx_stsp );

  /* Get the related endpoint structure */
  ep = OTGD_FS_PCD_GetOutEP(status.b.epnum);

  switch (status.b.pktsts)
  {
    case STS_GOUT_NAK:
      break;
    case STS_DATA_UPDT:
      if (status.b.bcnt)
      {
        if (ep->type == EP_TYPE_ISOC)
        {
          /* Call user function */
          INTR_RXSTSQLVL_ISODU_Callback();         
          
          /* Copy the received buffer to the RAM */
          OTGD_FS_ReadPacket((uint8_t*)(IsocBuff + (ISOC_BUFFER_SZE * IsocBufferIdx)), status.b.bcnt);
          ep->xfer_buff = (uint8_t*)(IsocBuff + (ISOC_BUFFER_SZE * IsocBufferIdx));  
          
          /* Check if the end of the global buffer has been reached */
          if (IsocBufferIdx == (NUM_SUB_BUFFERS - 1))
          {
            /* Reset the buffer index */
            IsocBufferIdx = 0;                         
          }
          else
          {
            /* Increment the buffer index */
            IsocBufferIdx ++;
          }          
        }
        else
        {
          /* Copy the received buffer to the RAM */
          OTGD_FS_ReadPacket(USBD_Data_Buffer, status.b.bcnt);
          ep->xfer_buff = USBD_Data_Buffer;
        }
        
        /* Update the endpoint structure */
        ep->xfer_len  = status.b.bcnt;
        ep->xfer_count += status.b.bcnt;        
      }
      break;
    case STS_XFER_COMP:
      break;
    case STS_SETUP_COMP:
      break;
    case STS_SETUP_UPDT:
      /* Copy the setup packet received in Fifo into the setup buffer in RAM */
      OTGD_FS_ReadPacket(USBD_Data_Buffer, 8); 
      ep->xfer_buff = USBD_Data_Buffer;
      ep->xfer_count += status.b.bcnt;
      ep->xfer_len  = status.b.bcnt;
      break;
    default:
      break;
  }

  /* Call the user function */
  INTR_RXSTSQLVL_Callback();
  
  /* Enable the Rx Status Queue Level interrupt */
  MODIFY_REG32( &core_regs.common_regs->int_msk, 0, int_mask.d32);
  
  /* Clear interrupt: this is a read only bit, it cannot be cleared by register 
     access */
  /* int_sts.d32 = 0;
     int_sts.b.rxstsqlvl = 1;
     WRITE_REG32 (&core_regs.common_regs->int_sts, int_sts.d32);
  */

  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_NPTxFE_ISR
* Description    : Handles the Non Periodic Tx FIFO Empty interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_NPTxFE_ISR(void )
{
  /* USB_OTG_int_sts_data gintsts; */
  USB_OTG_int_msk_data gintmsk;
  gintmsk.d32 = 0;

  /* Call the user function */
  INTR_NPTXFEMPTY_Callback();
  
  gintmsk.b.nptxfempty = 1;
  MODIFY_REG32(&core_regs.common_regs->int_msk, gintmsk.d32, 0 );

  /* Clear interrupt: This bit is a read only bit, cannot be cleared 
     by register access */
  /* gintsts.d32 = 0;
     gintsts.b.nptxfempty = 1;
     WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
   */
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_GInNakEff_ISR
* Description    : Handles the Global IN Endpoints NAK Effective interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_GInNakEff_ISR(void)
{
  /* USB_OTG_int_sts_data gintsts; */
  
  /* Call user function */
  INTR_GINNAKEFF_Callback();
  
  /* Clear interrupt: This is a read only bit, it cannot be cleared by register 
     access */
  /* gintsts.d32 = 0;
     gintsts.b.ginnakeff = 1;
     WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  */  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_GOutNakEff_ISR
* Description    : Handles the Global OUT Endpoints NAK Effective interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_GOutNakEff_ISR(void)
{
  /* USB_OTG_int_sts_data gintsts; */
  
  /* Call user function */
  INTR_GOUTNAKEFF_Callback();  
  
  /* Clear interrupt: This is a read only bit, it cannot be cleared by register 
     access */
  /* gintsts.d32 = 0;
     gintsts.b.goutnakeff = 1;
     WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  */  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_EarlySuspend_ISR
* Description    : Handles the Early Suspend detected interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_EarlySuspend_ISR(void )
{
  USB_OTG_int_sts_data gintsts;
  USB_OTG_int_msk_data gintmsk;
  gintmsk.d32 = 0;

  /* Call user function */
  INTR_ERLYSUSPEND_Callback();  
  
  gintmsk.b.erlysuspend = 1;
  MODIFY_REG32(&core_regs.common_regs->int_msk, gintmsk.d32, 0 );

  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.erlysuspend = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_USBSuspend_ISR
* Description    : Handles the Suspend condition detected interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_USBSuspend_ISR(void)
{
  USB_OTG_int_sts_data gintsts;  
  
  /* Call user function */
  INTR_USBSUSPEND_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.usbsuspend = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_UsbReset_ISR
* Description    : This interrupt occurs when a USB Reset is detected.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_UsbReset_ISR(void)
{
  USB_OTG_dev_all_int_data daintmsk;
  USB_OTG_dev_out_ep_msk_data doepmsk;
  USB_OTG_dev_in_ep_msk_data diepmsk;
  USB_OTG_dev_cfg_data dcfg;
  USB_OTG_dev_ctl_data dctl;
  USB_OTG_int_sts_data gintsts;

  daintmsk.d32 = 0;
  doepmsk.d32 = 0;
  diepmsk.d32 = 0;
  dcfg.d32 = 0;
  dctl.d32 = 0;

  /* Clear the Remote Wakeup Signalling */
  dctl.b.rmtwkupsig = 1;
  MODIFY_REG32(&core_regs.dev_regs->dev_ctl, dctl.d32, 0 );

  /* Flush the NP Tx FIFO */
  OTGD_FS_FlushTxFifo( 0 );

  daintmsk.b.inep0 = 1;
  daintmsk.b.outep0 = 1;
  WRITE_REG32( &core_regs.dev_regs->dev_all_int_msk, daintmsk.d32 );

  doepmsk.b.setup = 1;
  doepmsk.b.xfercompl = 1;
  doepmsk.b.ahberr = 1;
  doepmsk.b.epdisabled = 1;
  WRITE_REG32( &core_regs.dev_regs->dev_out_ep_msk, doepmsk.d32 );

  diepmsk.b.xfercompl = 1;
  diepmsk.b.timeout = 1;
  diepmsk.b.epdisabled = 1;
  diepmsk.b.ahberr = 1;
  diepmsk.b.intknepmis = 1;
  WRITE_REG32( &core_regs.dev_regs->dev_in_ep_msk, diepmsk.d32 );

  /* Reset Device Address */
  dcfg.d32 = READ_REG32( &core_regs.dev_regs->dev_cfg);
  dcfg.b.devaddr = 0;
  WRITE_REG32( &core_regs.dev_regs->dev_cfg, dcfg.d32);


  /* setup EP0 to receive SETUP packets */
  OTGD_FS_PCD_EP0_OutStart();

  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.usbreset = 1;
  WRITE_REG32 (&core_regs.common_regs->int_sts, gintsts.d32);

  /* Call the user reset function */
  OTGD_FS_DEVICE_RESET; 
  
  /* Call user function */
  INTR_USBRESET_Callback();  
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_EnumDone_ISR
* Description    : Reads the device status register and set the device speed
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_EnumDone_ISR(void)
{
  USB_OTG_int_sts_data gintsts;
  USB_OTG_usb_cfg_data gusbcfg;

  OTGD_FS_EP0Activate();

  /* Set USB turnaround time based on device speed and PHY interface. */
  gusbcfg.d32 = READ_REG32(&core_regs.common_regs->usb_cfg);

  /* Full or low speed */
  if ( OTGD_FS_PCD_GetDeviceSpeed() == USB_SPEED_FULL)
  {
    gusbcfg.b.usbtrdtim = 9;
  }
  WRITE_REG32(&core_regs.common_regs->usb_cfg, gusbcfg.d32);

  /* Call user function */
  INTR_ENUMDONE_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.enumdone = 1;
  WRITE_REG32( &core_regs.common_regs->int_sts, gintsts.d32 );
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_IsoOutDrop_ISR
* Description    : Handles the Isochrounous Out packet Dropped interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_IsoOutDrop_ISR(void)
{
  USB_OTG_int_sts_data gintsts;  
  
  /* Call user function */
  INTR_ISOOUTDROP_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.isooutdrop = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_EOPF_ISR
* Description    : Handles the Expexted End Of Periodic Frame interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_EOPF_ISR(void )
{
  USB_OTG_int_sts_data gintsts;
  USB_OTG_int_msk_data gintmsk;
  gintmsk.d32 = 0;

  gintmsk.b.eopframe = 1;
  MODIFY_REG32(&core_regs.common_regs->int_msk, gintmsk.d32, 0 );

  /* Call user function */
  INTR_EOPFRAME_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.eopframe = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_EPMismatch_ISR
* Description    : Handles the Endpoint Mismatch error interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_EPMismatch_ISR(void)
{
  USB_OTG_int_sts_data gintsts;  
  
  /* Call user function */
  INTR_EPMISMATCH_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.epmismatch = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_InEP_ISR
* Description    : Handles all IN endpoints interrupts.
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_InEP_ISR(void)
{
  USB_OTG_dev_in_ep_int_data diepint;

  uint32_t ep_intr;
  uint32_t epnum = 0;
  USB_OTG_EP *ep;
  uint32_t fifoemptymsk;
  
  diepint.d32 = 0;
  ep_intr = OTGD_FS_ReadDevAllInEPItr();
  while ( ep_intr )
  {
    if (ep_intr&0x1) /* In ITR */
    {
      ep = OTGD_FS_PCD_GetInEP(epnum);
      diepint.d32 = OTGD_FS_PCD_ReadDevInEP(ep); /* Get In ITR status */
      if ( diepint.b.xfercompl )
      {
        fifoemptymsk = 0x1 << ep->num;
        MODIFY_REG32(&core_regs.dev_regs->dev_fifo_empty_msk, fifoemptymsk, 0);

        /* Clear the Interrupt flag */ 
        CLEAR_IN_EP_INTR(epnum, xfercompl);
        
        if (epnum == 0)  
        {        
          /* Call the core IN process for EP0 */ 
          In0_Process();
          
          /* before terminate set Tx & Rx status */
          OTG_DEV_SetEPRxStatus(epnum, SaveRState);
          OTG_DEV_SetEPTxStatus(epnum, SaveTState);
        }
        else
        {
          OTG_DEV_SetEPTxStatus(EP1_IN, DEV_EP_TX_NAK);

          (*pEpInt_IN[epnum -1])();
          
          /* Toggle Endpoint frame ID */
          if (ep->even_odd_frame == 0)
            ep->even_odd_frame = 1;
          else
            ep->even_odd_frame = 0;
        } 
      }
      if ( diepint.b.ahberr )
      {
        CLEAR_IN_EP_INTR(epnum, ahberr);
      }
      if ( diepint.b.timeout )
      {
        CLEAR_IN_EP_INTR(epnum, timeout);
      }
      if (diepint.b.intktxfemp)
      {
        CLEAR_IN_EP_INTR(epnum, intktxfemp);
      }
      if (diepint.b.intknepmis)
      {
        CLEAR_IN_EP_INTR(epnum, intknepmis);
      }
      if (diepint.b.inepnakeff)
      {
        CLEAR_IN_EP_INTR(epnum, inepnakeff);
      }
      if (diepint.b.emptyintr)
      {      
         if ((epnum == 0) || (OTG_DEV_GetEPTxStatus(epnum) == DEV_EP_TX_VALID))
        {
          OTGD_FS_PCD_WriteEmptyTxFifo(epnum);          
        }

        CLEAR_IN_EP_INTR(epnum, emptyintr);          
      }
      if ( diepint.b.epdisabled )
      { 
        /* Reset Endpoint Frame ID to 0 */
        ep->even_odd_frame = 0;

        CLEAR_IN_EP_INTR(epnum, epdisabled);
      }      
    }
    epnum++;
    ep_intr >>= 1;
  }

  /* Call user function */
  INTR_INEPINTR_Callback();
  
  return 1;
}


/*******************************************************************************
* Function Name  : OTGD_FS_Handle_OutEP_ISR
* Description    : Handles all OUT endpoints interrupts.
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
uint32_t OTGD_FS_Handle_OutEP_ISR(void)
{
  uint32_t ep_intr;
  USB_OTG_dev_out_ep_int_data doepint;
  uint32_t epnum = 0;
  USB_OTG_EP *ep;

  doepint.d32 = 0;

  /* Read in the device interrupt bits */
  ep_intr = OTGD_FS_ReadDevAllOutEp_itr();
  
  while ( ep_intr )
  {
    if (ep_intr&0x1)
    {
      /* Get EP pointer */
      ep = OTGD_FS_PCD_GetOutEP(epnum);
      doepint.d32 = OTGD_FS_ReadDevOutEP_itr(ep);

      /* Transfer complete */
      if ( doepint.b.xfercompl )
      {
        /* Clear the bit in DOEPINTn for this interrupt */
        CLEAR_OUT_EP_INTR(epnum, xfercompl);
        
        if (epnum == 0)  
        { 
          /* Call the OUT process for the EP0 */
          Out0_Process();
        }
        else
        {
          (*pEpInt_OUT[epnum-1])();
        }
      }
      /* Endpoint disable  */
      if ( doepint.b.epdisabled )
      {
        /* Clear the bit in DOEPINTn for this interrupt */
        CLEAR_OUT_EP_INTR(epnum, epdisabled);
      }
      /* AHB Error */
      if ( doepint.b.ahberr )
      {
        CLEAR_OUT_EP_INTR(epnum, ahberr);
      }
      /* Setup Phase Done (control EPs) */
      if ( doepint.b.setup )
      {
        if (epnum == 0)  
        {        
          /* Call the SETUP process for the EP0 */
          Setup0_Process();  

          /* Before exit, update the Tx status */
          OTG_DEV_SetEPTxStatus(0x80, SaveTState);  
        }
        else
        {
          /* Other control endpoints */
        }  
        
        /* Clear the EP Interrupt */
        CLEAR_OUT_EP_INTR(epnum, setup);
      }
    }
    epnum++;
    ep_intr >>= 1;
  }

  /* Call user function */
  INTR_OUTEPINTR_Callback();  
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_IncomplIsoIn_ISR
* Description    : Handles the Incomplete Isochrous IN tranfer error interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_IncomplIsoIn_ISR(void)
{
  USB_OTG_int_sts_data gintsts;  

  /* Call user function */
  INTR_INCOMPLISOIN_Callback(); 
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.incomplisoin = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_IncomplIsoOut_ISR
* Description    : Handles the Incomplete Isochrous OUT tranfer error interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_IncomplIsoOut_ISR(void)
{
  USB_OTG_int_sts_data gintsts;  

  /* Call user function */
  INTR_INCOMPLISOOUT_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.outepintr = 1;
  WRITE_REG32(&core_regs.common_regs->int_sts, gintsts.d32);
  
  return 1;
}

/*******************************************************************************
* Function Name  : OTGD_FS_Handle_Wakeup_ISR
* Description    : Handles the Wakeup or Remote Wakeup detected interrupt.
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_Handle_Wakeup_ISR(void)
{
  USB_OTG_int_sts_data gintsts;

  /* Call user function */
  INTR_WKUPINTR_Callback();
  
  /* Clear interrupt */
  gintsts.d32 = 0;
  gintsts.b.wkupintr = 1;
  WRITE_REG32 (&core_regs.common_regs->int_sts, gintsts.d32);

  return 1;
}



/*******************************************************************************
* Function Name  : OTGD_FS_PCD_GetDeviceSpeed
* Description    : Get the device speed from the device status register
* Input          : None
* Output         : None
* Return         : The Device speed value.
*******************************************************************************/
static enum usb_device_speed OTGD_FS_PCD_GetDeviceSpeed(void)
{
  USB_OTG_dev_sts_data dsts;
  enum usb_device_speed speed = USB_SPEED_UNKNOWN;
  dsts.d32 = READ_REG32(&core_regs.dev_regs->dev_sts);

  switch (dsts.b.enumspd)
  {
    case DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
      speed = USB_SPEED_HIGH;
      break;
    case DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
    case DSTS_ENUMSPD_FS_PHY_48MHZ:
      speed = USB_SPEED_FULL;
      break;

    case DSTS_ENUMSPD_LS_PHY_6MHZ:
      speed = USB_SPEED_LOW;
      break;
  }

  return speed;
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_ReadDevInEP
* Description    : Reads all the Endpoints flags.
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
static uint32_t OTGD_FS_PCD_ReadDevInEP( USB_OTG_EP *ep)
{
  uint32_t v, msk, emp;
  msk = READ_REG32(&core_regs.dev_regs->dev_in_ep_msk);
  emp = READ_REG32(&core_regs.dev_regs->dev_fifo_empty_msk);
  msk |= ((emp >> ep->num) & 0x1) << 7;
  v = READ_REG32(&core_regs.inep_regs[ep->num]->dev_in_ep_int) & msk;
  return v;
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_WriteEmptyTxFifo
* Description    : Checks Fifo for the next packet to be loaded.
* Input          : None
* Output         : None
* Return         : Status
*******************************************************************************/
static uint32_t OTGD_FS_PCD_WriteEmptyTxFifo(uint32_t epnum)
{
  USB_OTG_dev_tx_fifo_sts_data txstatus;
  USB_OTG_EP *ep;
  uint32_t len = 0;
  uint32_t dwords;
  USB_OTG_dev_ep_ctl_data  depctl;
  
  txstatus.d32 = 0;

  ep = OTGD_FS_PCD_GetInEP(epnum); 
  
  len = ep->xfer_len - ep->xfer_count;

  if (len > ep->maxpacket)
  {
    len = ep->maxpacket;
  }
  
  dwords = (len + 3) / 4;
  txstatus.d32 = READ_REG32( &core_regs.inep_regs[epnum]->dev_tx_fifo_sts);

  /* Manage the case of 0-length data packets toggling data PID */
  if ((ep->xfer_len == 0) && (ep->xfer_count == 0))
  {
    if (ep->num > 0)
    {
      depctl.d32 = READ_REG32( &core_regs.inep_regs[epnum]->dev_in_ep_ctl);      
      if (ep->even_odd_frame == 1)
      {
        depctl.b.setd0pid = 0;
        depctl.b.setd1pid = 1;
      }
      else
      {
        depctl.b.setd0pid = 1;
        depctl.b.setd1pid = 0;
      }      
      WRITE_REG32( &core_regs.inep_regs[epnum]->dev_in_ep_ctl, depctl.d32);           
    }
  }

  
  while  (txstatus.b.txfspcavail > dwords &&
          ep->xfer_count < ep->xfer_len &&
          ep->xfer_len != 0)
  {
    if (ep->num > 0)
    {
      depctl.d32 = READ_REG32( &core_regs.inep_regs[epnum]->dev_in_ep_ctl);      
      if (ep->even_odd_frame == 0)
      {
        depctl.b.setd0pid = 1;
        depctl.b.setd1pid = 0;
      }
      else
      {
        depctl.b.setd0pid = 0;
        depctl.b.setd1pid = 1;
      }      
      WRITE_REG32( &core_regs.inep_regs[epnum]->dev_in_ep_ctl, depctl.d32);           
    }
    
    /* Write the FIFO */
    len = ep->xfer_len - ep->xfer_count;

    if (len > ep->maxpacket)
    {
      len = ep->maxpacket;
    }
    dwords = (len + 3) / 4;

    OTGD_FS_WritePacket(ep->xfer_buff, epnum, len);    
    
    ep->xfer_count += len;

    txstatus.d32 = READ_REG32(&core_regs.inep_regs[epnum]->dev_tx_fifo_sts);   
  }
  
  return 1;
}
#endif  /* STM32F10X_CL */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
