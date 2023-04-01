/***********************************************************************
 * Filename    : hal_lpuart.c
 * Description : lpuart driver source file
 * Author(s)   : xwl  
 * version     : V1.0
 * Modify date : 2019-11-19
 ***********************************************************************/
#include "ACM32Fxx_HAL.h"  

static uint16_t ep1_stall[2]= {0};    // EP1 stall״̬
static uint16_t ep2_stall[2]= {0};    // EP2 stall״̬
static uint16_t ep3_stall[2]= {0};    // EP3 stall״̬
static uint16_t ep4_stall[2]= {0};    // EP3 stall״̬     

uint32_t HAL_FSUSB_MSP_Init(void)  
{
    GPIO_InitTypeDef    GPIO_init_para;  

    System_Module_Reset(RST_USB); 
    System_Module_Enable(EN_USB);  
           
    if( HAL_OK != System_USB_PHY_Config())
    {
        return HAL_ERROR;    
    } 
    
    SCU->PABADS = (SCU->PABADS | ( (0x3 << 11)) );       
//    GPIO_init_para.Pin       = GPIO_PIN_11 | GPIO_PIN_12;
//    GPIO_init_para.Mode      = GPIO_MODE_ANALOG;
//    GPIO_init_para.Pull      = GPIO_NOPULL;
//    GPIO_init_para.Alternate = GPIO_FUNCTION_0; 
//    HAL_GPIO_Init(GPIOA, &GPIO_init_para);  
    
    NVIC_ClearPendingIRQ(USB_IRQn);  
	NVIC_EnableIRQ(USB_IRQn); 
    
    return HAL_OK;    
}   

uint32_t HAL_FSUSB_Init(void)  
{
    if (HAL_OK != HAL_FSUSB_MSP_Init())
    {
       return HAL_ERROR;    
    }
    
    System_Delay(10);    
    
    USBCTRL->WORKING_MODE = 0x04;  //disconnect usb/ reset USBC    
	System_Delay(3000);   
	USBCTRL->WORKING_MODE = 0x09 ;  //auto reset, fullspeed  
    
    USBCTRL->EPxCSR[0] |= 1<<8;	//enable EP0  
    USBCTRL->EPxCSR[1] |= 1<<8;	//enable EP1  
    USBCTRL->EPxCSR[2] |= 1<<8;	//enable EP2  
    USBCTRL->EPxCSR[3] |= 1<<8;	//enable EP3  
    USBCTRL->EPxCSR[4] |= 1<<8;	//enable EP4  
    USBCTRL->EPADDR_CFG = 0x4321;  
    
    USBINT->INT_EN = 0x92427;   // enable Reset,Resume,Suspend,setup, EP1/2/3/4 OUT interrupt	  
     
	USBCTRL->WORKING_MODE  |= (1<<6)|(1<<4);	//connect   
    
    return HAL_OK;   
}  

uint16_t HAL_FSUSB_Get_FIFO_Length(uint8_t ep_index)
{
	return USBCTRL->EPxCSR[ep_index]&0xff;             	
}

void HAL_USB_Clear_FIFO(uint8_t ep_index, uint8_t ep_dir)  
{
	USBCTRL->EPxCSR[ep_index] |= 1<<9;	  
} 

uint16_t HAL_USB_Get_Stall_Status(uint8_t ep_index, uint8_t ep_dir) 
{
	switch(ep_index)
	{
		case USB_EP1: 
		{    
			if(ep_dir == EP_DIR_IN)		return ep1_stall[0];	  //in
			else			  			return ep1_stall[1];	  //out	    
		}
		case USB_EP2: 
		{    
			if(ep_dir == EP_DIR_IN)		return ep2_stall[0];	  //in
			else			  			return ep2_stall[1];	  //out	    
		}
		case USB_EP3: 
		{    
			if(ep_dir == EP_DIR_IN)	  	return ep3_stall[0];	  //in
			else			  			return ep3_stall[1];	  //out	    
		}
		case USB_EP4: 
		{    
			if(ep_dir == EP_DIR_IN)	  	return ep4_stall[0];	  //in
			else			  			return ep4_stall[1];	  //out	    
		}

		default:    	 	  return 0xff;
	}	
}

void usb_clear_stall(uint8_t ep_index, uint8_t ep_dir)
{
	switch(ep_index)
	{
		case USB_EP1: 
		{    
			if(ep_dir == EP_DIR_IN)	 	ep1_stall[0]=0x0000;	  //in
			else			  			ep1_stall[1]=0x0000;	  //out	
			break;  
		}
		case USB_EP2: 
		{    
			if(ep_dir == EP_DIR_IN)	  	ep2_stall[0]=0x0000;	  //in
			else			  			ep2_stall[1]=0x0000;	  //out				  
			break;   
		}
		case USB_EP3: 
		{    
			if(ep_dir == EP_DIR_IN)	  	ep3_stall[0]=0x0000;	  //in
			else			  			ep3_stall[1]=0x0000;	  //out		  
			break;   
		}
		case USB_EP4: 
		{    
			if(ep_dir == EP_DIR_IN)	  	ep4_stall[0]=0x0000;	  //in
			else			  			ep4_stall[1]=0x0000;	  //out					  
			break;    
		}

		default: return;
	}

	USBCTRL->EPxCSR[ep_index] = 0x02100;		   //clear in/out toggle,stall,stall status
	USBCTRL->EPxCSR[ep_index] |= (1<<18)|(1<<15);  //enable change
//	flag_clear_stall=0;  		 
}



void usb_send_stall(uint8_t ep_index, uint8_t ep_dir)
{
	switch(ep_index)
	{
		case USB_EP1: 
		{    
			if(ep_dir == EP_DIR_IN)	 	ep1_stall[0]=0x0001;	  //in
			else			  			ep1_stall[1]=0x0001;	  //out	
			break;  
		}
		case USB_EP2: 
		{    
			if(ep_dir == EP_DIR_IN)	  	ep2_stall[0]=0x0001;	  //in
			else			  			ep2_stall[1]=0x0001;	  //out				  
			break;   
		}
		case USB_EP3: 
		{    
			if(ep_dir == EP_DIR_IN)	  	ep3_stall[0]=0x0001;	  //in
			else			  			ep3_stall[1]=0x0001;	  //out		  
			break;   
		}
		case USB_EP4: 
		{    
			if(ep_dir == EP_DIR_IN)	  	ep4_stall[0]=0x0001;	  //in
			else			  			ep4_stall[1]=0x0001;	  //out					  
			break;    
		}

		default: return;
	}

	USBCTRL->EPxCSR[ep_index] |= (1<<12);    
}


void HAL_FSUSB_Read_EP_MEM8(uint8_t *dst, uint32_t length, uint32_t fifo_offset, uint8_t ep_index)
{
	uint8_t *src;

	src = (uint8_t *)(USB_BASE+0x200+(ep_index<<6)+fifo_offset);       
	while(length--)
	{
		*dst++ = *src++;
	}		 
}
 
void HAL_FSUSB_Write_EP_MEM8(uint8_t *src, uint32_t length, uint32_t fifo_offset, uint8_t ep_index)
{

	uint8_t *dst;

	dst = (uint8_t *)(USB_BASE+0x200+(ep_index<<6)+fifo_offset); 

	while(length--)
	{
		*dst++ = *src++;
	}
}


uint8_t HAL_FSUSB_Start_EP_Transfer(uint32_t length,uint8_t ep_index)
{
	uint8_t intoken_cnt;
	
	USBCTRL->EPxSENDBN[ep_index]= length;
	
	while(1)
	{
		// if a new out data packet received, return error to caller  
	    if( (USBINT->INT_STAT_RAW & MASK_EPX_OUT(ep_index)) && (USBINT->INT_STAT_RAW & MASK_EPX_ACK(ep_index)) )
		{
		    USBINT->INT_CLR  = MASK_EPX_OUT(ep_index);	
	        USBINT->INT_CLR  = MASK_EPX_ACK(ep_index);
			return ERROR_OUT_OUT;
		}
		// wait for IN token to start transfer 
        if(USBINT->INT_STAT_RAW & MASK_EPX_IN(ep_index) )
        {
		    USBINT->INT_CLR  = MASK_EPX_IN(ep_index);
			USBCTRL->WORKING_MODE  |= (1<<11);//return NAK when timeout
			USBCTRL->EPxCSR[ep_index] |= (1<<10);//data is ready for tx
			break;
        }			
	}
	

	while(1)
	{
		if( USBCTRL->EPxCSR[ep_index]&0x1000000 ) //received ACK from host 
		{
			USBINT->INT_CLR  = MASK_EPX_ACK(ep_index);
			USBINT->INT_CLR  = MASK_EPX_IN(ep_index);
			return 0;//pass
		}
		
		if(USBINT->INT_STAT_RAW & (1<<21) ) // timeout occurs when wait ACK 
		{
            USBINT->INT_CLR  = (1<<21);
			intoken_cnt = 4;
			while(intoken_cnt) // wait 3 SOF frame for bad signal, during this time, device will send NACK when IN token received  
			{               
                if(USBINT->INT_STAT_RAW & (1<<3))				
				{
				    intoken_cnt --;
					USBINT->INT_CLR  = (1<<3);
				}
			}
			USBINT->INT_CLR  = MASK_EPX_TIMEOUT(ep_index); // device recover to send data packet after IN token received  		
		}	
		
		if(USBINT->INT_STAT_RAW & MASK_EPX_OUT(ep_index))
		{
			return ERROR_IN_OUT; 
		}		
	}	
}

   
uint8_t HAL_FSUSB_Send_Data(uint8_t *buffer,uint32_t length,uint8_t ep_index)
{
	uint8_t ret;
	
	while(length>=EPX_MAX_PACKET_SIZE)
	{    		
		HAL_FSUSB_Write_EP_MEM8(buffer,EPX_MAX_PACKET_SIZE,0, ep_index);  		   
		ret = HAL_FSUSB_Start_EP_Transfer(EPX_MAX_PACKET_SIZE, ep_index);
		if(ret == ERROR_OUT_OUT)
		{
		    if( USBCTRL->EPxCSR[ep_index] & ( 1<< 19) )//Toggle error
		    {
		        USBCTRL->EPxCSR[ep_index] ^= (1<<17);  //out toggle want
			    USBCTRL->EPxCSR[ep_index] |= (1<<18);  //update want toggle;			 			             			
		    }
			USBCTRL->EPxCSR[ep_index] |= 1<<11; //set rx ready  	
            continue;	// received a same packet, has processed this packet, just fill respoonse to fifo and send it to host 		
		}
		else if(ret != 0)
		{
			return 1; // send data fail, exit with error code to let caller know 
		}
	 	length -= EPX_MAX_PACKET_SIZE;
	  	buffer += EPX_MAX_PACKET_SIZE;		
	}
	// remaining data, less than EPX_MAX_PACKET_SIZE  
	while(length>0)  
	{
		HAL_FSUSB_Write_EP_MEM8(buffer,length,0,ep_index);  	     
		ret = HAL_FSUSB_Start_EP_Transfer(length,ep_index);
		if(ret == ERROR_OUT_OUT)
		{
		    if( USBCTRL->EPxCSR[ep_index] & ( 1<< 19) )//Toggle error
		    {
		        USBCTRL->EPxCSR[ep_index] ^= (1<<17); //out toggle want
			    USBCTRL->EPxCSR[ep_index] |= (1<<18); //update want toggle;			 			             			
		    }
			USBCTRL->EPxCSR[ep_index] |= 1<<11; //set rx ready  
            continue;				
		}
		else if(ret != 0)
		{
			return 1; // send data fail, exit with error code to let caller know   
		}
	 	length -= length;
	  	buffer += length;
	}
	
	return 0;  
}


void HAL_FSUSB_Receive_Data(uint8_t *buffer,uint32_t length,uint8_t ep_index)  
{
	uint32_t len;

	while(length>0)	
	{			
		while(1)
		{
			// wait an out data packet and device has sent an ACK to HOST  
			if( (USBINT->INT_STAT_RAW & MASK_EPX_OUT(ep_index)) && (USBINT->INT_STAT_RAW & MASK_EPX_ACK(ep_index)) )
			{
				break;
			}
		}		
		USBINT->INT_CLR  = MASK_EPX_OUT(ep_index);	
	    USBINT->INT_CLR  = MASK_EPX_ACK(ep_index);		
		
		if( USBCTRL->EPxCSR[ep_index] & ( 1<< 19) )//Toggle error 
		{
		    USBCTRL->EPxCSR[ep_index] ^= (1<<17); //out toggle want
			USBCTRL->EPxCSR[ep_index] |= (1<<18); //update want toggle; 
			USBCTRL->EPxCSR[ep_index] |= 1<<11;   //set rx ready, wait for a new packet 
			continue;  //discard this packet          			
		}		
	
		len	=HAL_FSUSB_Get_FIFO_Length(ep_index);
		HAL_FSUSB_Read_EP_MEM8(buffer,len,0,ep_index);	
		USBCTRL->EPxCSR[ep_index] |= 1<<11; //set rx ready to wait next packet 

		length -= len;
		buffer += len;
	}		
} 


//ep_index表示的是菜单
void HAL_FSUSB_EP0_Send_Empty_Packet(void)
{
	HAL_FSUSB_Start_EP_Transfer(0,USB_EP0);    
} 
  
void HAL_FSUSB_EP0_Send_Stall(void)
{
	USBCTRL->EPxCSR[0] |= 1<<12;
	while(!(USBCTRL->EPxCSR[0] &0x2000));
	USBCTRL->EPxCSR[0] |= 0x2000;    
}         










