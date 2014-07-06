/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_endp.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Endpoint routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "toCOM/usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"
#include <rtthread.h>
#include "serial.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern  uint8_t USART_Rx_Buffer[];
extern uint32_t USART_Rx_ptr_out,USART_Rx_ptr_in;
extern uint32_t USART_Rx_length;
extern uint8_t  USB_Tx_State;
extern rt_mutex_t  tx_mutex;
extern rt_thread_t Thread_usb;

u8 Receive_Buffer[64];
u8 Transi_Buffer[64];
u8 USB_ReceiveFlg = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback (void)				//USB发送完回调函数
{
  uint16_t USB_Tx_ptr;
  uint16_t USB_Tx_length;
  if (USB_Tx_State == 1)
  {
    if (USART_Rx_length == 0) 
    {
      USB_Tx_State = 0;
//		rt_mutex_release(tx_mutex);
//		rt_thread_resume(Thread_usb);
    }
    else 
    {
      if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE){
        USB_Tx_ptr = USART_Rx_ptr_out;
        USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;      
        USART_Rx_ptr_out += VIRTUAL_COM_PORT_DATA_SIZE;
        USART_Rx_length -= VIRTUAL_COM_PORT_DATA_SIZE;    
      }
      else 
      {
        USB_Tx_ptr = USART_Rx_ptr_out;
        USB_Tx_length = USART_Rx_length;
        
        USART_Rx_ptr_out += USART_Rx_length;
        USART_Rx_length = 0;
      }
//       if(USART_Rx_ptr_out+USB_Tx_length>USART_RX_DATA_SIZE)
// 			{
// 				 
//          if(USART_Rx_ptr_out!=USART_RX_DATA_SIZE)
// 				 {
// 					
// 				 USART_Rx_length+=USB_Tx_length-(USART_RX_DATA_SIZE-USART_Rx_ptr_out);
//  				 USB_Tx_length=USART_RX_DATA_SIZE-USART_Rx_ptr_out;
//          }
// 				 USART_Rx_ptr_out=0; 					 
//       }
#ifdef USE_STM3210C_EVAL
      USB_SIL_Write(EP1_IN, &USART_Rx_Buffer[USB_Tx_ptr], USB_Tx_length);  
#else
      UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
      SetEPTxCount(ENDP1, USB_Tx_length);
      SetEPTxValid(ENDP1); 
#endif  
    }
  }
}

/*******************************************************************************
* Function Name  : EP3_OUT_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
#include "ToCOM\usb.h"
extern rt_sem_t  usb_sem;
extern rt_sem_t  rx_sem,usb_sem_rx;
extern struct stm32_serial_int_rx  usb_rx;
extern struct rt_device  usb_device;
void EP3_OUT_Callback(void)	  //EP3 OUT的回调函数，当EP3接收到数据时候中断调用该函数
{
   uint16_t USB_Rx_Cnt;
 #ifdef	RT_USING_DEVICE
	 int i;
	 struct stm32_serial_int_rx* P_usb_rx,*int_rx;
	 struct rt_device *device=&usb_device;
	 P_usb_rx = &usb_rx;
	 int_rx=P_usb_rx;
#endif
     USB_ReceiveFlg = 1; 
  /* Get the received data buffer and update the counter */
  USB_Rx_Cnt = USB_SIL_Read(EP3_OUT, Receive_Buffer); 
  /* USB data will be immediately processed, this allow next USB traffic beeing 
  NAKed till the end of the USART Xfet */ 
#ifdef	RT_USING_DEVICE
	 i = 0;
	 while(i<USB_Rx_Cnt)
	 {	
// 		if(Receive_Buffer[i]==0)
// 			break;
	 	P_usb_rx->rx_buffer[P_usb_rx->save_index] = Receive_Buffer[i++];
		P_usb_rx->save_index++;
		if(P_usb_rx->save_index >= USB_BUFFER_SIZE)
			P_usb_rx->save_index = 0;
		/* if the next position is read index, discard this 'read char' */
		if (P_usb_rx->save_index == P_usb_rx->read_index)
		{
			P_usb_rx->read_index ++;
			if (P_usb_rx->read_index >= USB_BUFFER_SIZE)
				P_usb_rx->read_index = 0;
		}	
	 }

	 if (device->rx_indicate != RT_NULL)
		{
			  rt_size_t rx_length;
			  /* get rx length */
			  rx_length = int_rx->read_index > int_rx->save_index ?
				UART_RX_BUFFER_SIZE - int_rx->read_index + int_rx->save_index :
				int_rx->save_index - int_rx->read_index;
			  device->rx_indicate(device, rx_length);
		}
	 
	 
	 //rt_sem_release(usb_sem);
	 rt_sem_release(usb_sem_rx);
#endif

  
#ifndef STM32F10X_CL
  /* Enable the receive of data on EP3 */
  SetEPRxValid(ENDP3);
#endif /* STM32F10X_CL */
}


/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
#ifdef STM32F10X_CL
void INTR_SOFINTR_Callback(void)
#else
void SOF_Callback(void)
#endif /* STM32F10X_CL */
{
  static uint32_t FrameCount = 0;
  if(bDeviceState == CONFIGURED)
  {
    if (FrameCount++ == 5)
    {
      /* Reset the frame counter */
      FrameCount = 0;
      
      /* Check the data to be sent through IN pipe */
      Handle_USBAsynchXfer();
    }
  }  
}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

