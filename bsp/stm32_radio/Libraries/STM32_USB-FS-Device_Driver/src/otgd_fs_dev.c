/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : otgd_fs_dev.c
* Author             : STMicroelectronics
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : High Layer device mode interface and wrapping layer.
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
#include "otgd_fs_dev.h"
#include "usb_regs.h"
#include "otgd_fs_cal.h"
#include "otgd_fs_pcd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : OTG_DEV_Init
* Description    : Initialize the OTG Device IP and EP0.
* Input          : None.
* Output         : None.
* Return         : None. 
*******************************************************************************/
void OTG_DEV_Init(void)
{
  EP_DESCRIPTOR ep_descriptor;
  USB_OTG_EP *ep;
  
  /* Set the OTG_USB base registers address */
  OTGD_FS_SetAddress(USB_OTG_FS1_BASE_ADDR);
  
  /* Disable all global interrupts */
  OTGD_FS_DisableGlobalInt();

  /*Init the Core (common init.) */
  OTGD_FS_CoreInit();

  /* Init Device */
  OTGD_FS_CoreInitDev();

  /* Init internal driver structure */
  OTGD_FS_PCD_Init();
  
  /* Configure and open the IN control EP0 */ 
  ep_descriptor.bEndpointAddress = 0x80;
  ep_descriptor.wMaxPacketSize = 64;  
  ep_descriptor.bmAttributes = USB_ENDPOINT_XFER_CONTROL; 
  OTGD_FS_PCD_EP_Open(&ep_descriptor);
  
  /* Configure and open the OUT control EP0 */ 
  ep_descriptor.bEndpointAddress = 0x00;
  OTGD_FS_PCD_EP_Open(&ep_descriptor);    


  ep = OTGD_FS_PCD_GetOutEP(0);
  OTGD_FS_EPStartXfer(ep);
  
  /* Enable EP0 to start receiving setup packets */  
  OTGD_FS_PCD_EP0_OutStart();  
  
  /* Enable USB Global interrupt */
  OTGD_FS_EnableGlobalInt();     
}


/*******************************************************************************
* Function Name  : OTG_DEV_EP_Init
* Description    : Initialize the selected endpoint parameters
* Input          : - bEpAdd: address of the endpoint (epnum|epdir) 
*                     expample: EP1 OUT -> 0x01 and EP1 IN 0x81.
*                  - bEpType: OTG_DEV_EP_TYPE_CONTROL, OTG_DEV_EP_TYPE_ISOC, 
*                     OTG_DEV_EP_TYPE_BULK, OTG_DEV_EP_TYPE_INT
*                  - wEpMaxPackSize: The EP max packet size.
* Output         : None.
* Return         : Status: New status to be set for the endpoint: 
*******************************************************************************/
void OTG_DEV_EP_Init(uint8_t bEpAdd, uint8_t bEpType, uint16_t wEpMaxPackSize)
{
  EP_DESCRIPTOR ep_descriptor;
  USB_OTG_EP *ep;
  
  /* Set the EP parameters in a structure */
  ep_descriptor.bEndpointAddress = bEpAdd;
  ep_descriptor.bmAttributes = bEpType; 
  ep_descriptor.wMaxPacketSize = wEpMaxPackSize;

  OTGD_FS_PCD_EP_Flush(bEpAdd);
  
  /* Open the EP with entered parameters */   
  OTGD_FS_PCD_EP_Open(&ep_descriptor); 
  
  /* Activate the EP if it is an OUT EP */
  if ((bEpAdd & 0x80) == 0)
  {
    ep = OTGD_FS_PCD_GetOutEP(bEpAdd & 0x7F);
    OTGD_FS_EPStartXfer(ep);
  } 
  else
  {
    ep = OTGD_FS_PCD_GetInEP(bEpAdd & 0x7F);
    ep->even_odd_frame = 0;    
    OTG_DEV_SetEPTxStatus(bEpAdd, DEV_EP_TX_NAK);
  }
  
}

/*******************************************************************************
* Function Name  : OTG_DEV_GetEPTxStatus
* Description    : Set the related endpoint status.
* Input          : Number of the endpoint.
* Output         : None.
* Return         : Status: New status to be set for the endpoint: 
*******************************************************************************/
uint32_t OTG_DEV_GetEPTxStatus(uint8_t bEpnum) 
{
  USB_OTG_EP *ep;
  uint32_t status = 0;
  
  ep = OTGD_FS_PCD_GetInEP(bEpnum & 0x7F); 
  
  status = OTGD_FS_Dev_GetEPStatus(ep); 
  
  return status; 
}

/*******************************************************************************
* Function Name  : OTG_DEV_GetEPRxStatus
* Description    : returns the related endpoint status.
* Input          : Number of the endpoint.
* Output         : None.
* Return         : Status: New status to be set for the endpoint: 
*******************************************************************************/
uint32_t OTG_DEV_GetEPRxStatus(uint8_t bEpnum)
{
  USB_OTG_EP *ep;
  uint32_t status = 0;
  
  ep = OTGD_FS_PCD_GetOutEP(bEpnum & 0x7F); 
  
  status = OTGD_FS_Dev_GetEPStatus(ep); 
  
  return status;
}

/*******************************************************************************
* Function Name  : OTG_DEV_SetEPTxStatus
* Description    : Sets the related endpoint status.
* Input          : - bEpnum: Number of the endpoint.
*                  - Status: New status to be set for the endpoint. It can be
*                    DEV_EP_TX_VALID, DEV_EP_TX_STALL, DEV_EP_TX_NAK or 
*                    DEV_EP_TX_DISABLE.
* Output         : None.
* Return         : None.
*******************************************************************************/
void OTG_DEV_SetEPTxStatus(uint8_t bEpnum, uint32_t Status) 
{
  USB_OTG_EP *ep;
   
  ep = OTGD_FS_PCD_GetInEP(bEpnum & 0x7F); 
  
  if ((bEpnum == 0x80) && (Status == DEV_EP_TX_STALL))
  {
    ep->is_in = 1;
  }
  
  OTGD_FS_Dev_SetEPStatus(ep, Status); 
}

/*******************************************************************************
* Function Name  : OTG_DEV_SetEPRxStatus
* Description    : Sets the related endpoint status.
* Input          : - bEpnum: Number of the endpoint.
*                  - Status: New status to be set for the endpoint. It can be
*                    DEV_EP_RX_VALID, DEV_EP_RX_STALL, DEV_EP_RX_NAK or 
*                    DEV_EP_RX_DISABLE.
* Output         : None.
* Return         : None.
*******************************************************************************/
void OTG_DEV_SetEPRxStatus(uint8_t bEpnum, uint32_t Status)                           
{
  USB_OTG_EP *ep;
 
  ep = OTGD_FS_PCD_GetOutEP(bEpnum & 0x7F); 
  
  OTGD_FS_Dev_SetEPStatus(ep, Status); 
}

/*******************************************************************************
* Function Name  : USB_DevDisconnect
* Description    : Disconnect the Pullup resist.
* Input          : bEpNum: Endpoint Number. 
*                  wState: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_DevDisconnect(void)
{
  OTGD_FS_PCD_DevDisconnect();
}

/*******************************************************************************
* Function Name  : USB_DevConnect
* Description    : Disconnect the .
* Input          : bEpNum: Endpoint Number. 
*                  wState: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_DevConnect(void)
{
  OTGD_FS_PCD_DevConnect();
}

/*-*-*-*-*-*-*-*-*-* Replace the usb_regs.h defines -*-*-*-*-*-*-*-*-*-*-*-*-*/

/*******************************************************************************
* Function Name  : SetEPTxStatus
* Description    : Set the status of Tx endpoint.
* Input          : bEpNum: Endpoint Number. 
*                  wState: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPTxStatus(uint8_t bEpNum, uint16_t wState)
{
  _SetEPTxStatus(bEpNum, wState);
}

/*******************************************************************************
* Function Name  : SetEPRxStatus
* Description    : Set the status of Rx endpoint.
* Input          : bEpNum: Endpoint Number. 
*                  wState: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPRxStatus(uint8_t bEpNum, uint16_t wState)
{
  _SetEPRxStatus(bEpNum, wState);
}

/*******************************************************************************
* Function Name  : GetEPTxStatus
* Description    : Returns the endpoint Tx status.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : Endpoint TX Status
*******************************************************************************/
uint16_t GetEPTxStatus(uint8_t bEpNum) 
{
  return(_GetEPTxStatus(bEpNum));
}

/*******************************************************************************
* Function Name  : GetEPRxStatus
* Description    : Returns the endpoint Rx status.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : Endpoint RX Status
*******************************************************************************/
uint16_t GetEPRxStatus(uint8_t bEpNum) 
{
  return(_GetEPRxStatus(bEpNum));
}

/*******************************************************************************
* Function Name  : SetEPTxValid
* Description    : Valid the endpoint Tx Status.
* Input          : bEpNum: Endpoint Number.  
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPTxValid(uint8_t bEpNum)
{
  _SetEPTxStatus(bEpNum, EP_TX_VALID);
}

/*******************************************************************************
* Function Name  : SetEPRxValid
* Description    : Valid the endpoint Rx Status.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPRxValid(uint8_t bEpNum)
{
  _SetEPRxStatus(bEpNum, EP_RX_VALID);
}

/*******************************************************************************
* Function Name  : GetTxStallStatus
* Description    : Returns the Stall status of the Tx endpoint.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : Tx Stall status.
*******************************************************************************/
uint16_t GetTxStallStatus(uint8_t bEpNum)
{
  return(_GetTxStallStatus(bEpNum));
}

/*******************************************************************************
* Function Name  : GetRxStallStatus
* Description    : Returns the Stall status of the Rx endpoint. 
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : Rx Stall status.
*******************************************************************************/
uint16_t GetRxStallStatus(uint8_t bEpNum)
{
  return(_GetRxStallStatus(bEpNum));
}

/*******************************************************************************
* Function Name  : SetEPTxCount.
* Description    : Set the Tx count.
* Input          : bEpNum: Endpoint Number.
*                  wCount: new count value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPTxCount(uint8_t bEpNum, uint16_t wCount)
{
}

/*******************************************************************************
* Function Name  : SetEPRxCount
* Description    : Set the Rx count.
* Input          : bEpNum: Endpoint Number. 
*                  wCount: the new count value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPRxCount(uint8_t bEpNum, uint16_t wCount)
{ 
}

/*******************************************************************************
* Function Name  : ToWord
* Description    : merge two byte in a word.
* Input          : bh: byte high, bl: bytes low.
* Output         : None.
* Return         : resulted word.
*******************************************************************************/
uint16_t ToWord(uint8_t bh, uint8_t bl)
{
  uint16_t wRet;
  wRet = (uint16_t)bl | ((uint16_t)bh << 8);
  return(wRet);
}

/*******************************************************************************
* Function Name  : ByteSwap
* Description    : Swap two byte in a word.
* Input          : wSwW: word to Swap.
* Output         : None.
* Return         : resulted word.
*******************************************************************************/
uint16_t ByteSwap(uint16_t wSwW)
{
  uint8_t bTemp;
  uint16_t wRet;
  bTemp = (uint8_t)(wSwW & 0xff);
  wRet =  (wSwW >> 8) | ((uint16_t)bTemp << 8);
  return(wRet);
}

#endif /* STM32F10X_CL */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
