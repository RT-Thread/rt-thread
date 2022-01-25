/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_usb.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : This file provides all the USB firmware functions.
*******************************************************************************/ 
#include "ch32f10x_usb.h"
#include "ch32f10x_rcc.h"

/******************************** USB DEVICE **********************************/

/* Endpoint address */
PUINT8  pEP0_RAM_Addr;
PUINT8  pEP1_RAM_Addr;
PUINT8  pEP2_RAM_Addr;
PUINT8  pEP3_RAM_Addr;

/*******************************************************************************
* Function Name  : DelsyUs
* Description    : Microsecond Delay Time.
* Input          : t：Microsecond number.
* Return         : None
*******************************************************************************/		 
void DelsyUs( UINT16 t )
{
	UINT16 j,i;

	for(j=0; j<t; j++)
	{
		 for(i=0; i<4; i++)
		{
			__nop();
			__nop();
		}
	}	
}

/*******************************************************************************
* Function Name  : DelsyMs
* Description    : Millisecond Delay Time.
* Input          : t：Millisecond number.
* Return         : None
*******************************************************************************/	
void DelsyMs( UINT16 t )
{
	UINT16 i;

  for(i=0; i<t; i++)
	{
		DelsyUs(1000);
	}
}

/*******************************************************************************
* Function Name  : USB_DeviceInit
* Description    : Initializes USB device.
* Input          : None			   				
* Return         : None
*******************************************************************************/
void USB_DeviceInit( void )                                    
{	
	R8_USB_CTRL = 0x00;				
	EXTEN_CTRL = USBHD_IO_EN ;//| USB_5V_SEL;  
	R8_UEP4_1_MOD = RB_UEP4_RX_EN|RB_UEP4_TX_EN|RB_UEP1_RX_EN|RB_UEP1_TX_EN;   
	R8_UEP2_3_MOD = RB_UEP2_RX_EN|RB_UEP2_TX_EN|RB_UEP3_RX_EN|RB_UEP3_TX_EN;   

	R16_UEP0_DMA = (UINT16)(UINT32)pEP0_RAM_Addr;
	R16_UEP1_DMA = (UINT16)(UINT32)pEP1_RAM_Addr;
	R16_UEP2_DMA = (UINT16)(UINT32)pEP2_RAM_Addr;
	R16_UEP3_DMA = (UINT16)(UINT32)pEP3_RAM_Addr;

	R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
	R8_UEP1_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
	R8_UEP2_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
	R8_UEP3_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
	R8_UEP4_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
															
	R8_USB_INT_FG = 0xFF;                                             
	R8_USB_INT_EN = RB_UIE_SUSPEND | RB_UIE_BUS_RST | RB_UIE_TRANSFER; 

	R8_USB_DEV_AD = 0x00;
	R8_USB_CTRL = RB_UC_DEV_PU_EN | RB_UC_INT_BUSY | RB_UC_DMA_EN;  
	R8_UDEV_CTRL = RB_UD_PD_DIS|RB_UD_PORT_EN; 					
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Set USB clock.
* Input          : None
* Return         : None
*******************************************************************************/
void Set_USBClock(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);             //USBclk=PLLclk/1.5=48Mhz			 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBHD,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);	
} 

/*******************************************************************************
* Function Name  : DevEP1_IN_Deal
* Description    : Device endpoint1 IN.
* Input          : l: IN length(<64B)			   				
* Return         : None
*******************************************************************************/
void DevEP1_IN_Deal( UINT8 l )
{
	R8_UEP1_T_LEN = l;
	R8_UEP1_CTRL = (R8_UEP1_CTRL & ~MASK_UEP_T_RES)| UEP_T_RES_ACK;
}

/*******************************************************************************
* Function Name  : DevEP2_IN_Deal
* Description    : Device endpoint2 IN.
* Input          : l: IN length(<64B)			   				
* Return         : None
*******************************************************************************/
void DevEP2_IN_Deal( UINT8 l )
{
	R8_UEP2_T_LEN = l;
	R8_UEP2_CTRL = (R8_UEP2_CTRL & ~MASK_UEP_T_RES)| UEP_T_RES_ACK;
}

/*******************************************************************************
* Function Name  : DevEP3_IN_Deal
* Description    : Device endpoint3 IN.
* Input          : l: IN length(<64B)			   				
* Return         : None
*******************************************************************************/
void DevEP3_IN_Deal( UINT8 l )
{
	R8_UEP3_T_LEN = l;
	R8_UEP3_CTRL = (R8_UEP3_CTRL & ~MASK_UEP_T_RES)| UEP_T_RES_ACK;
}

/*******************************************************************************
* Function Name  : DevEP4_IN_Deal
* Description    : Device endpoint4 IN.
* Input          : l: IN length(<64B)				   				
* Return         : None
*******************************************************************************/
void DevEP4_IN_Deal( UINT8 l )
{
	R8_UEP4_T_LEN = l;
	R8_UEP4_CTRL = (R8_UEP4_CTRL & ~MASK_UEP_T_RES)| UEP_T_RES_ACK;
}


/******************************** HOST DEVICE **********************************/
UINT8  UsbDevEndp0Size;			
UINT8  FoundNewDev;
_RootHubDev   ThisUsbDev;             

PUINT8  pHOST_RX_RAM_Addr;
PUINT8  pHOST_TX_RAM_Addr;

__align(4) const UINT8  SetupGetDevDescr[] = { USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_DEVICE, 0x00, 0x00, sizeof( USB_DEV_DESCR ), 0x00 };

__align(4) const UINT8  SetupGetCfgDescr[] = { USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_CONFIG, 0x00, 0x00, 0x04, 0x00 };

__align(4) const UINT8  SetupSetUsbAddr[] = { USB_REQ_TYP_OUT, USB_SET_ADDRESS, USB_DEVICE_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00 };

__align(4) const UINT8  SetupSetUsbConfig[] = { USB_REQ_TYP_OUT, USB_SET_CONFIGURATION, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

__align(4) const UINT8  SetupSetUsbInterface[] = { USB_REQ_RECIP_INTERF, USB_SET_INTERFACE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

__align(4) const UINT8  SetupClrEndpStall[] = { USB_REQ_TYP_OUT | USB_REQ_RECIP_ENDP, USB_CLEAR_FEATURE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/*******************************************************************************
* Function Name  : DisableRootHubPort( )
* Description    : Disable root hub.
* Input          : None
* Return         : None
*******************************************************************************/
void DisableRootHubPort(void)          
{
#ifdef	FOR_ROOT_UDISK_ONLY
	CH579DiskStatus = DISK_DISCONNECT;
	
#endif
	
#ifndef	DISK_BASE_BUF_LEN
	ThisUsbDev.DeviceStatus = ROOT_DEV_DISCONNECT;
	ThisUsbDev.DeviceAddress = 0x00;
	
#endif
}

/*******************************************************************************
* Function Name  : AnalyzeRootHub
* Description    : Analyze root hub state.
* Input          : None
* Return         : Error
*******************************************************************************/
//extern __align(4) UINT8 LED_HOST_MODE;
UINT8 AnalyzeRootHub( void ) 
{ 
	UINT8	s;
	
	s = ERR_SUCCESS;
	
	if ( R8_USB_MIS_ST & RB_UMS_DEV_ATTACH ) {  
		
#ifdef DISK_BASE_BUF_LEN
		if ( CH579DiskStatus == DISK_DISCONNECT
			
#else
		if ( ThisUsbDev.DeviceStatus == ROOT_DEV_DISCONNECT 
			
#endif
				|| ( R8_UHOST_CTRL & RB_UH_PORT_EN ) == 0x00 ) {                     
				DisableRootHubPort( );  
					
#ifdef DISK_BASE_BUF_LEN
				CH579DiskStatus = DISK_CONNECT;
					
#else
        ThisUsbDev.DeviceSpeed = R8_USB_MIS_ST & RB_UMS_DM_LEVEL ? 0 : 1;
        ThisUsbDev.DeviceStatus = ROOT_DEV_CONNECTED; 
					
#endif
        PRINT( "USB dev in\n" );
        s = ERR_USB_CONNECT;
     }
  }
	
#ifdef DISK_BASE_BUF_LEN
  else if ( CH579DiskStatus >= DISK_CONNECT ) {
		
#else
  else if ( ThisUsbDev.DeviceStatus >= ROOT_DEV_CONNECTED ) {
		
#endif
		DisableRootHubPort( );                                                	
		PRINT( "USB dev out\n" );
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE); //时钟关闭使能
//	    LED_HOST_MODE = 0;
		if(s == ERR_SUCCESS) s = ERR_USB_DISCON;
  }
                                              
	return( s );
}

/*******************************************************************************
* Function Name  : SetHostUsbAddr
* Description    : Set USB host address. 
* Input          : addr; host address.
* Return         : None
*******************************************************************************/
void SetHostUsbAddr( UINT8 addr )
{
    R8_USB_DEV_AD = (R8_USB_DEV_AD&RB_UDA_GP_BIT) | (addr&MASK_USB_ADDR);
}

#ifndef	FOR_ROOT_UDISK_ONLY
/*******************************************************************************
* Function Name  : SetUsbSpeed
* Description    : Set USB speed.
* Input          : FullSpeed: USB speed.
* Return         : None
*******************************************************************************/
void SetUsbSpeed( UINT8 FullSpeed )  
{
	if ( FullSpeed )                                                       
	{
		R8_USB_CTRL &= ~ RB_UC_LOW_SPEED;                                     
		R8_UH_SETUP &= ~ RB_UH_PRE_PID_EN;                                         
	}
	else
	{
		R8_USB_CTRL |= RB_UC_LOW_SPEED;                                         
	}
}
#endif

/*******************************************************************************
* Function Name  : ResetRootHubPort( )
* Description    : Reset root hub.
* Input          : None  
* Return         : None
*******************************************************************************/
void ResetRootHubPort( void )
{
	UsbDevEndp0Size = DEFAULT_ENDP0_SIZE;                	
	SetHostUsbAddr( 0x00 );
	R8_UHOST_CTRL &= ~RB_UH_PORT_EN;                                          
	SetUsbSpeed( 1 );                                                           
	R8_UHOST_CTRL = (R8_UHOST_CTRL & ~RB_UH_LOW_SPEED) | RB_UH_BUS_RESET;      
	mDelaymS( 15 );                                                         
	R8_UHOST_CTRL = R8_UHOST_CTRL & ~ RB_UH_BUS_RESET;                       
	mDelayuS( 250 );
	R8_USB_INT_FG = RB_UIF_DETECT;                                          
}

/*******************************************************************************
* Function Name  : EnableRootHubPort( )
* Description    : Enable root hub.
* Input          : None
* Return         : ERROR
*******************************************************************************/
UINT8 EnableRootHubPort(void) 
{
#ifdef DISK_BASE_BUF_LEN
  if ( CH579DiskStatus < DISK_CONNECT ) CH579DiskStatus = DISK_CONNECT;
	
#else
  if ( ThisUsbDev.DeviceStatus < ROOT_DEV_CONNECTED ) ThisUsbDev.DeviceStatus = ROOT_DEV_CONNECTED;
	
#endif
  if ( R8_USB_MIS_ST & RB_UMS_DEV_ATTACH ) {                                     
#ifndef DISK_BASE_BUF_LEN
    if ( ( R8_UHOST_CTRL & RB_UH_PORT_EN ) == 0x00 ) {                            
			ThisUsbDev.DeviceSpeed = (R8_USB_MIS_ST & RB_UMS_DM_LEVEL) ? 0 : 1;
			if ( ThisUsbDev.DeviceSpeed == 0 ) R8_UHOST_CTRL |= RB_UH_LOW_SPEED;          
    }
		
#endif
    R8_UHOST_CTRL |= RB_UH_PORT_EN;                                              
    return( ERR_SUCCESS );
  }
	
  return( ERR_USB_DISCON );
}

/*******************************************************************************
* Function Name  : WaitUSB_Interrupt
* Description    : Wait USB Interrput.
* Input          : None
* Return         : EEROR
*******************************************************************************/
UINT8 WaitUSB_Interrupt( void )
{
	UINT16  i;
	
	for ( i = WAIT_USB_TOUT_200US; i != 0 && (R8_USB_INT_FG&RB_UIF_TRANSFER) == 0; i -- ){;}
	return( (R8_USB_INT_FG&RB_UIF_TRANSFER)  ? ERR_SUCCESS : ERR_USB_UNKNOWN );
}

/*******************************************************************************
* Function Name  : USBHostTransact
* Description    : USB host transport transaction.
* Input          : endp_pid: endpoint and PID. 
*                  tog: Synchronization flag.
*                  timeout: timeout times.
* Return         : EEROR:
*				   ERR_USB_UNKNOWN 
*                  ERR_USB_DISCON  
*                  ERR_USB_CONNECT
*                  ERR_SUCCESS    
*******************************************************************************/
UINT8 USBHostTransact( UINT8 endp_pid, UINT8 tog, UINT16 timeout )
{
	UINT8	TransRetry;
	UINT8	s, r;
	UINT16	i;

	R8_UH_RX_CTRL = R8_UH_TX_CTRL = tog;
	TransRetry = 0;

	do {
		R8_UH_EP_PID = endp_pid;                                           
		R8_USB_INT_FG = RB_UIF_TRANSFER;                                                       
		for ( i = WAIT_USB_TOUT_200US; i != 0 && (R8_USB_INT_FG&RB_UIF_TRANSFER) == 0; i -- );
		R8_UH_EP_PID = 0x00;                                                       
		if ( (R8_USB_INT_FG&RB_UIF_TRANSFER) == 0 )     {PRINT("1");return( ERR_USB_UNKNOWN );}

		if ( R8_USB_INT_FG & RB_UIF_DETECT ) {                                  
			R8_USB_INT_FG = RB_UIF_DETECT;                                                          
			s = AnalyzeRootHub( );                                              

			if ( s == ERR_USB_CONNECT ) 			FoundNewDev = 1;
			
#ifdef DISK_BASE_BUF_LEN
			if ( CH579DiskStatus == DISK_DISCONNECT ) return( ERR_USB_DISCON );      
			if ( CH579DiskStatus == DISK_CONNECT ) return( ERR_USB_CONNECT );
      
#else
			if ( ThisUsbDev.DeviceStatus == ROOT_DEV_DISCONNECT ) return( ERR_USB_DISCON );
			if ( ThisUsbDev.DeviceStatus == ROOT_DEV_CONNECTED ) return( ERR_USB_CONNECT );
			
#endif
			mDelayuS( 200 );  
		}

		if ( R8_USB_INT_FG & RB_UIF_TRANSFER ) 							
		{  
			if ( R8_USB_INT_ST & RB_UIS_TOG_OK ) return( ERR_SUCCESS );
			r = R8_USB_INT_ST & MASK_UIS_H_RES;  
			if ( r == USB_PID_STALL ) return( r | ERR_USB_TRANSFER );
			
			if ( r == USB_PID_NAK ) 
			{
				if ( timeout == 0 ) return( r | ERR_USB_TRANSFER );
				if ( timeout < 0xFFFF ) timeout --;
				-- TransRetry;
			}
			else switch ( endp_pid >> 4 ) {
				case USB_PID_SETUP:
					
				case USB_PID_OUT:
					if ( r ) return( r | ERR_USB_TRANSFER ); 
					break;  
				
				case USB_PID_IN:
					if ( r == USB_PID_DATA0 && r == USB_PID_DATA1 ) {  
					}  
					else if ( r ) return( r | ERR_USB_TRANSFER );  
					break;  
					
				default:
					return( ERR_USB_UNKNOWN );  
					break;
			}
		}
		else {  
			R8_USB_INT_FG = 0xFF; 
		}
		mDelayuS( 15 );	
	} while ( ++ TransRetry < 3 );
	
	return( ERR_USB_TRANSFER );  
}

/*******************************************************************************
* Function Name  : HostCtrlTransfer
* Description    : Host control transport.
* Input          : DataBuf : Receive or send data buffer.
*                  RetLen  : Data length.
* Return         : ERR_USB_BUF_OVER IN
*                  ERR_SUCCESS  
*******************************************************************************/
UINT8 HostCtrlTransfer( PUINT8 DataBuf, PUINT16 RetLen )  
{
	UINT16  RemLen  = 0;
	UINT8   s, RxLen, RxCnt, TxCnt;
	PUINT8  pBuf;
	PUINT16   pLen;

	pBuf = DataBuf;
	pLen = RetLen;
	mDelayuS( 200 );
	if ( pLen )	*pLen = 0;  		

	R8_UH_TX_LEN = sizeof( USB_SETUP_REQ );
	s = USBHostTransact( USB_PID_SETUP << 4 | 0x00, 0x00, 200000/20 );       
	if ( s != ERR_SUCCESS ) return( s );
	R8_UH_RX_CTRL = R8_UH_TX_CTRL = RB_UH_R_TOG | RB_UH_R_AUTO_TOG | RB_UH_T_TOG | RB_UH_T_AUTO_TOG;
	R8_UH_TX_LEN = 0x01;                                                    
	RemLen = pSetupReq -> wLength;
	
	if ( RemLen && pBuf )                                               
	{
		if ( pSetupReq -> bRequestType & USB_REQ_TYP_IN )                  
		{
			while ( RemLen )
			{
				mDelayuS( 200 );
				s = USBHostTransact( USB_PID_IN << 4 | 0x00, R8_UH_RX_CTRL, 200000/20 );
				if ( s != ERR_SUCCESS )         return( s );
				RxLen = R8_USB_RX_LEN < RemLen ? R8_USB_RX_LEN : RemLen;
				RemLen -= RxLen;
				if ( pLen ) *pLen += RxLen;  
				
				for ( RxCnt = 0; RxCnt != RxLen; RxCnt ++ )
				{
					*pBuf = pHOST_RX_RAM_Addr[ RxCnt ];
					pBuf ++;
				}
				
				if ( R8_USB_RX_LEN == 0 || ( R8_USB_RX_LEN & ( UsbDevEndp0Size - 1 ) ) ) break;   
			}
			R8_UH_TX_LEN = 0x00;                                                
		}
		else                                                              
		{
			while ( RemLen )
			{
				mDelayuS( 200 );
				R8_UH_TX_LEN = RemLen >= UsbDevEndp0Size ? UsbDevEndp0Size : RemLen;
				
				for ( TxCnt = 0; TxCnt != R8_UH_TX_LEN; TxCnt ++ )
				{
					pHOST_TX_RAM_Addr[ TxCnt ] = *pBuf;
					pBuf ++;
				}
				
				s = USBHostTransact( USB_PID_OUT << 4 | 0x00, R8_UH_TX_CTRL, 200000/20 );
				if ( s != ERR_SUCCESS ) return( s );
				RemLen -= R8_UH_TX_LEN;
				if ( pLen ) *pLen += R8_UH_TX_LEN;  
			}
		}
	}
	
	mDelayuS( 200 );
	s = USBHostTransact( ( R8_UH_TX_LEN ? USB_PID_IN << 4 | 0x00: USB_PID_OUT << 4 | 0x00 ), RB_UH_R_TOG | RB_UH_T_TOG, 200000/20 ); 
	if ( s != ERR_SUCCESS )         return( s );    
	if ( R8_UH_TX_LEN == 0 )        return( ERR_SUCCESS );     
	if ( R8_USB_RX_LEN == 0 )       return( ERR_SUCCESS );     
	
	return( ERR_USB_BUF_OVER );                                  	
}

/*******************************************************************************
* Function Name  : CopySetupReqPkg
* Description    : Copy setup request package.
* Input          : pReqPkt: setup request package address.
* Return         : None
*******************************************************************************/
void CopySetupReqPkg( const UINT8 *pReqPkt )          
{
	UINT8 i;
	
	for ( i = 0; i != sizeof( USB_SETUP_REQ ); i ++ )
	{
		((PUINT8)pSetupReq)[ i ] = *pReqPkt;
		pReqPkt++;
	}			
}

/*******************************************************************************
* Function Name  : CtrlGetDeviceDescr
* Description    : Get device descrptor
* Input          : DataBuf: Data buffer.
* Return         : ERR_USB_BUF_OVER
*                  ERR_SUCCESS      
*******************************************************************************/
UINT8 CtrlGetDeviceDescr( PUINT8 DataBuf )  
{
	UINT8   s;
	UINT16  len;

	UsbDevEndp0Size = DEFAULT_ENDP0_SIZE;
	CopySetupReqPkg( SetupGetDevDescr );
	s = HostCtrlTransfer( DataBuf, &len ); 
	
	if ( s != ERR_SUCCESS ) return( s );
	UsbDevEndp0Size = ( (PUSB_DEV_DESCR)DataBuf ) -> bMaxPacketSize0;       
	if ( len < ((PUSB_SETUP_REQ)SetupGetDevDescr)->wLength ) return( ERR_USB_BUF_OVER ); 
	
	return( ERR_SUCCESS );
}

/*******************************************************************************
* Function Name  : CtrlGetConfigDescr
* Description    : Get configration descrptor.
* Input          : DataBuf: Data buffer.
* Return         : ERR_USB_BUF_OVER 
*                  ERR_SUCCESS     
*******************************************************************************/
UINT8 CtrlGetConfigDescr( PUINT8 DataBuf )
{
	UINT8   s;
	UINT16  len;

	CopySetupReqPkg( SetupGetCfgDescr );
	s = HostCtrlTransfer( DataBuf, &len );                         
	if ( s != ERR_SUCCESS ) return( s );
	if ( len < ( (PUSB_SETUP_REQ)SetupGetCfgDescr ) -> wLength ) return( ERR_USB_BUF_OVER );  

	len = ( (PUSB_CFG_DESCR)DataBuf ) -> wTotalLength;	
	CopySetupReqPkg( SetupGetCfgDescr );
	pSetupReq ->wLength = len;                                              
	s = HostCtrlTransfer( DataBuf, &len );                         
	if ( s != ERR_SUCCESS ) return( s );
	
	return( ERR_SUCCESS );
}

/*******************************************************************************
* Function Name  : CtrlSetUsbAddress
* Description    : Set USB device address.
* Input          : addr: Device address.
* Return         : ERR_SUCCESS   
*******************************************************************************/
UINT8 CtrlSetUsbAddress( UINT8 addr ) 
{
	UINT8   s;

	CopySetupReqPkg( SetupSetUsbAddr );	
	pSetupReq -> wValue = addr;                                      
	s = HostCtrlTransfer( NULL, NULL );                            
	if ( s != ERR_SUCCESS ) return( s );
	SetHostUsbAddr( addr );                                                
	mDelaymS( 10 );   
	
	return( ERR_SUCCESS );
}

/*******************************************************************************
* Function Name  : CtrlSetUsbConfig
* Description    : Set usb configration.
* Input          : cfg: Configration Value.
* Return         : ERR_SUCCESS 
*******************************************************************************/
UINT8 CtrlSetUsbConfig( UINT8 cfg )                   
{
	CopySetupReqPkg( SetupSetUsbConfig );	
	pSetupReq -> wValue = cfg;                       
	return( HostCtrlTransfer( NULL, NULL ) );                      
}

/*******************************************************************************
* Function Name  : CtrlClearEndpStall
* Description    : Clear endpoint STALL.
* Input          : endp: Endpoint address.
* Return         : ERR_SUCCESS    
*******************************************************************************/
UINT8 CtrlClearEndpStall( UINT8 endp )  
{
	CopySetupReqPkg( SetupClrEndpStall );                        
	pSetupReq -> wIndex = endp;                                  
	return( HostCtrlTransfer( NULL, NULL ) );                      
}

/*******************************************************************************
* Function Name  : CtrlSetUsbIntercace
* Description    : Set USB Interface configration.
* Input          : cfg: Configration value.
* Return         : ERR_SUCCESS    
*******************************************************************************/
UINT8 CtrlSetUsbIntercace( UINT8 cfg )                   
{
	CopySetupReqPkg( SetupSetUsbInterface );		
	pSetupReq -> wValue = cfg;                         
	return( HostCtrlTransfer( NULL, NULL ) );               
}

/*******************************************************************************
* Function Name  : USB_HostInit
* Description    : Initializes USB host mode.
* Input          : None			   				
* Return         : None
*******************************************************************************/
void  USB_HostInit( void )
{	
	R8_USB_CTRL = RB_UC_HOST_MODE; 
	R8_UHOST_CTRL = 0;                           
	R8_USB_DEV_AD = 0x00;
	EXTEN_CTRL = USBHD_IO_EN|USBD_LOWSPEED|USBD_PU_EN;//| USB_5V_SEL; 
	R8_UH_EP_MOD = RB_UH_EP_TX_EN | RB_UH_EP_RX_EN;
	R16_UH_RX_DMA = (UINT16)(UINT32)pHOST_RX_RAM_Addr;
	R16_UH_TX_DMA = (UINT16)(UINT32)pHOST_TX_RAM_Addr;

	R8_UH_RX_CTRL = 0x00;
	R8_UH_TX_CTRL = 0x00;
	R8_USB_CTRL =  RB_UC_HOST_MODE | RB_UC_INT_BUSY | RB_UC_DMA_EN;
	R8_UH_SETUP = RB_UH_SOF_EN;	
	R8_USB_INT_FG = 0xFF;
	DisableRootHubPort( );
	R8_USB_INT_EN = RB_UIE_TRANSFER|RB_UIE_DETECT;	

	FoundNewDev = 0;
}

/*****************************************************************************
* Function Name  : InitRootDevice
* Description    : Initializes USB root hub.
* Input          : DataBuf: Data buffer.
* Return         : ERROR
*******************************************************************************/
UINT8 InitRootDevice( PUINT8 DataBuf ) 
{
	UINT8  i, s;
	UINT8  cfg, dv_cls, if_cls;

	PRINT( "Reset host port\n" );
	ResetRootHubPort( );  
	
	for ( i = 0, s = 0; i < 100; i ++ ) 
	{  				
		mDelaymS( 1 );
		if ( EnableRootHubPort( ) == ERR_SUCCESS ) {  
				i = 0;
				s ++;  					
				if ( s > 100 ) break;  	
		}
	}
	
	if ( i ) 
	{  										
		DisableRootHubPort( );
		PRINT( "Disable host port because of disconnect\n" );
		return( ERR_USB_DISCON );
	}
	
	SetUsbSpeed( ThisUsbDev.DeviceSpeed );  

	PRINT( "GetDevDescr: " );
	s = CtrlGetDeviceDescr( DataBuf );  
	
	if ( s == ERR_SUCCESS )
	{
		for ( i = 0; i < ((PUSB_SETUP_REQ)SetupGetDevDescr)->wLength; i ++ ) 		
		PRINT( "x%02X ", (UINT16)( DataBuf[i] ) );
	  PRINT( "\n" ); 

		ThisUsbDev.DeviceVID = ((PUSB_DEV_DESCR)DataBuf)->idVendor; 
		ThisUsbDev.DevicePID = ((PUSB_DEV_DESCR)DataBuf)->idProduct;
		dv_cls = ( (PUSB_DEV_DESCR)DataBuf ) -> bDeviceClass;

		s = CtrlSetUsbAddress( ((PUSB_SETUP_REQ)SetupSetUsbAddr)->wValue );  
		
		if ( s == ERR_SUCCESS )
		{
			ThisUsbDev.DeviceAddress = ( (PUSB_SETUP_REQ)SetupSetUsbAddr )->wValue;  

			PRINT( "GetCfgDescr: " );
		  s = CtrlGetConfigDescr( DataBuf );
			
			if ( s == ERR_SUCCESS ) 
			{
			  for ( i = 0; i < ( (PUSB_CFG_DESCR)DataBuf )->wTotalLength; i ++ ) 
				PRINT( "x%02X ", (UINT16)( DataBuf[i] ) );
				PRINT("\n");			
				cfg = ( (PUSB_CFG_DESCR)DataBuf )->bConfigurationValue;
			  if_cls = ( (PUSB_CFG_DESCR_LONG)DataBuf )->itf_descr.bInterfaceClass;  
														
			  if ( (dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_STORAGE)) {  
					
	#ifdef	FOR_ROOT_UDISK_ONLY
					 CH579DiskStatus = DISK_USB_ADDR;
					 return( ERR_SUCCESS );
				}
			  else 	return( ERR_USB_UNSUPPORT );
				
	#else
				s = CtrlSetUsbConfig( cfg ); 
				
				if ( s == ERR_SUCCESS )
			  {
					ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
					ThisUsbDev.DeviceType = USB_DEV_CLASS_STORAGE;
					PRINT( "USB-Disk Ready\n" );
					SetUsbSpeed( 1 );  
					return( ERR_SUCCESS );
			  }
			}
		  else if ( (dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_PRINTER) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass == 0x01 ) {  
			  s = CtrlSetUsbConfig( cfg ); 
				if ( s == ERR_SUCCESS ) {
					ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
					ThisUsbDev.DeviceType = USB_DEV_CLASS_PRINTER;
					PRINT( "USB-Print Ready\n" );
					SetUsbSpeed( 1 );    
					return( ERR_SUCCESS );
				}
			}
		  else if ( (dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_HID) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass <= 0x01 ) {  
				if_cls = ( (PUSB_CFG_DESCR_LONG)DataBuf ) -> itf_descr.bInterfaceProtocol;
			  s = CtrlSetUsbConfig( cfg ); 
				if ( s == ERR_SUCCESS ) {
					ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
					if ( if_cls == 1 ) {
						ThisUsbDev.DeviceType = DEV_TYPE_KEYBOARD;
						PRINT( "USB-Keyboard Ready\n" );
					  SetUsbSpeed( 1 );  
						return( ERR_SUCCESS );
					}
				  else if ( if_cls == 2 ) {
						ThisUsbDev.DeviceType = DEV_TYPE_MOUSE;
						PRINT( "USB-Mouse Ready\n" );
						SetUsbSpeed( 1 );  
					  return( ERR_SUCCESS );
				  }
				  s = ERR_USB_UNSUPPORT;
			  }
			}
			else {   
				s = CtrlSetUsbConfig( cfg );  
				if ( s == ERR_SUCCESS ) {
					ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
					ThisUsbDev.DeviceType = DEV_TYPE_UNKNOW;
					SetUsbSpeed( 1 );  
				  return( ERR_SUCCESS );  
			  }
			}
			
	#endif			
		  }
		}
	}

	PRINT( "InitRootDev Err = %02X\n", (UINT16)s );
	
#ifdef	FOR_ROOT_UDISK_ONLY
	CH579DiskStatus = DISK_CONNECT;
	
#else
	ThisUsbDev.DeviceStatus = ROOT_DEV_FAILED;
	
#endif
	
	SetUsbSpeed( 1 );  
	
	return( s );		
}













