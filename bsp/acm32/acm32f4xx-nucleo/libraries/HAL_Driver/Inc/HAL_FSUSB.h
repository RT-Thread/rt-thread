/*
  ******************************************************************************
  * @file    HAL_Uart.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of UART HAL module.
  ******************************************************************************
*/
#ifndef __HAL_FSUSB_H__
#define __HAL_FSUSB_H__  

#include "ACM32Fxx_HAL.h"


#define     HIGH_SPEED     1 
#define     FULL_SPEED     0 

#define     USB_EP0        0
#define     USB_EP1        1        
#define     USB_EP2        2      
#define     USB_EP3        3        
#define     USB_EP4        4   

#define     USB_EP_IN      USB_EP1
#define     USB_EP_OUT     USB_EP1

#define     EP_DIR_IN      0x80  
#define     EP_DIR_OUT     0x00   

#define 	HID_REPORT_SIZE         1024

#define     EP0_MAX_PACKET_SIZE     64
#define     EPX_MAX_PACKET_SIZE     64
//#define     EPX_MAX_PACKET_SIZE_HS     512
//#define     EPX_MAX_PACKET_SIZE_FS     64

#define     MASK_EPX_IN(x)		(1<<(6+3*x))   
#define     MASK_EPX_OUT(x)     (1<<(7+3*x))   
#define     MASK_EPX_ACK(x)     (1<<(8+3*x)) 
#define     MASK_EPX_TIMEOUT(x) (1<< (25+x))

typedef __PACKED_STRUCT _device_request
{
	uint8_t  bmRequestType;
	uint8_t  bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} DEVICE_REQUEST;



#define USB_BUS_RESET         	0x01
#define USB_SUSPEND           	0x02
#define USB_RESUME           	0x04
#define USB_SOF            		0x08
#define USB_SETUPTOK         	0x10
#define USB_EP0_SETUP_PACKET  	0x20
#define USB_EP0_IN		  		0x40
#define USB_EP0_OUT_PACKET 		0x80
#define USB_EP0_ACK  			0x100
#define USB_EP1_IN		  		0x200
#define USB_EP1_OUT_PACKET    	0x400
#define USB_EP1_ACK		    	0x800
#define USB_EP2_IN		  		0x1000
#define USB_EP2_OUT_PACKET    	0x2000
#define USB_EP2_ACK		    	0x4000
#define USB_EP3_IN		  		0x8000
#define USB_EP3_OUT_PACKET    	0x10000
#define USB_EP3_ACK		    	0x20000
#define USB_EP4_IN		  		0x40000
#define USB_EP4_OUT_PACKET    	0x80000
#define USB_EP4_ACK		    	0x100000
#define USB_IN_TIMEOUT	    	0x200000
#define USB_SETADDR		    	0x400000
#define USB_CRC_ERR 	    	0x800000
#define USB_MORETHAN_64     	0x1000000
#define USB_EP0_IN_ERR      	0x2000000
#define USB_EP1_IN_ERR      	0x4000000
#define USB_EP2_IN_ERR      	0x8000000
#define USB_EP3_IN_ERR      	0x10000000
#define USB_EP4_IN_ERR      	0x20000000
#define USB_NOEOP_ERR      		0x40000000
#define USB_TOGGLE_ERR      	0x80000000



#define ERROR_OUT_OUT            4  // received a same out packet 
#define ERROR_IN_OUT             2  // received a pakcet when try to send packet   



uint32_t HAL_FSUSB_Init(void);     
void HAL_FSUSB_Read_EP_MEM8(uint8_t *dst, uint32_t length, uint32_t fifo_offset, uint8_t ep_index);  
uint8_t HAL_FSUSB_Send_Data(uint8_t *buffer,uint32_t length,uint8_t ep_index);   
void HAL_FSUSB_Receive_Data(uint8_t *buffer,uint32_t length,uint8_t ep_index);  
uint16_t HAL_USB_Get_Stall_Status(uint8_t ep_index, uint8_t ep_dir);  
void HAL_FSUSB_EP0_Send_Empty_Packet(void);  
void HAL_FSUSB_EP0_Send_Stall(void);    
void usb_clear_stall(uint8_t ep_index, uint8_t ep_dir);  
void usb_send_stall(uint8_t ep_index, uint8_t ep_dir);
uint16_t HAL_FSUSB_Get_FIFO_Length(uint8_t ep_index);      

#endif  

