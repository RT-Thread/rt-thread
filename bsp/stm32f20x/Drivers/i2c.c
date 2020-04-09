/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-21     JoyChen      First version, support I2C1
 */

#include <rtthread.h>
#include "i2c.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_i2c.h"
#include "stm32f2xx_dma.h"

#define EV_SB		1
#define EV_ADDR		(1<<1)
#define EV_STOPF	(1<<2)
#define EV_BTF		(1<<3)
#define ERR_ARLO	(1<<4)
#define ERR_AF		(1<<5)
#define ERR_OVR		(1<<6)
#define ERR_PECERR	(1<<7)
#define ERR_BERR	(1<<8)
#define I2C_COMPLETE (1<<9)

#define I2C_BUSY  1
#define I2C_FREE  2

#define I2C_WRITE 0
#define I2C_READ_DMA 1
#define I2C_READ_POLLING 2
#define I2C_READ_INTERRUPT 3

#define I2C_TRACE(...)

enum i2c_state {S1=0, S2, S2_1, S2_2, S3, S4, S5, S6, S_STOP};



extern void rt_hw_led_on(rt_uint32_t n);
extern void rt_hw_led_off(rt_uint32_t n);

DMA_InitTypeDef  I2CDMA_InitStructure;
uint32_t I2CDirection = I2C_DIRECTION_TX;
uint32_t i2cErrorNo = 0;

struct rt_event i2c_event;
static rt_mutex_t i2c_mux;

__IO uint8_t DevAddr;
static uint8_t* i2c_buf, *MemAddr, i2cStatus, i2cFlag, i2cPhase, memtype, i2c1_init_flag = 0;
static uint32_t BufSize;

I2C_ProgrammingModel I2CMode = DMA;


Status I2C_Free_Bus(I2C_TypeDef* I2Cx, u32 timeout );
void I2C_DMAConfig(I2C_TypeDef* I2Cx, uint8_t* pBuffer, uint32_t BufferSize, uint32_t Direction);

void dump_i2c_register(I2C_TypeDef* I2Cx)
{
    if(I2Cx == I2C1 )
        I2C_TRACE("======I2C1======\n");
    else
        I2C_TRACE("======I2C2======\n");
    I2C_TRACE("CR1: 0x%x\tCR2: 0x%x\n", I2Cx->CR1, I2Cx->CR2);
	I2C_TRACE("SR1: 0x%x\tSR2: 0x%x\n", I2Cx->SR1, I2Cx->SR2);

}

/*TODO: If your device need more time to initialize I2C bus or waiting memory write, you can use I2C_AcknowledgePolling avoid I2C bus lose.*/
Status I2C_AcknowledgePolling(I2C_TypeDef* I2Cx ,uint8_t Addr)
{
    uint32_t timeout = 0xFFFF, ret;
    uint16_t tmp;
	ret = rt_mutex_take(i2c_mux, RT_WAITING_FOREVER );
	
	if( ret == RT_EOK )
	{
	    do{
	        if( timeout-- <= 0 )
	        {
	            I2C_ClearFlag(I2Cx,I2C_FLAG_AF);
	            I2Cx->CR1 |= CR1_STOP_Set;
				rt_mutex_release(i2c_mux);
	            return Error;
	        }
	
	        I2Cx->CR1 |= CR1_START_Set;
	        tmp = I2Cx->SR1;//MSB
	        I2Cx->DR = Addr;
	        
	    }while((I2Cx->SR1&0x0002) != 0x0002);
	  
	    I2C_ClearFlag(I2Cx,I2C_FLAG_AF);
	    I2Cx->CR1 |= CR1_STOP_Set;
	    while ((I2Cx->CR1&0x200) == 0x200);
		rt_kprintf( "AcknowledgePolling OK\n");
		rt_mutex_release(i2c_mux);
		return Success; 
	}
	else
		return Error;
} 

/* 
	Only 1 byte READ using Interrupt or Polling otherwise using DMA
*/
void I2C1_EV_IRQHandler()
{
	__IO uint16_t regSR1, regSR2;
	__IO uint32_t regSR;
	int i=10;

	rt_interrupt_enter();
	//rt_hw_led_on(10);
	regSR1 = I2C1->SR1;
	regSR2 = I2C1->SR2;
	regSR =  (regSR2 << 16) | regSR1;
	//rt_kprintf("EV=> SR1: 0x%x\tSR2: 0x%x\tSR: 0x%x status: %d\n", regSR1, regSR2, regSR, i2cStatus);
 
	if( (regSR & I2C_EVENT_MASTER_MODE_SELECT) == I2C_EVENT_MASTER_MODE_SELECT)	//EV5
	{

		if( i2cStatus == S1 ) //Send TX Command
		{
			I2C1->DR = DevAddr & 0xFE;
			i2cStatus = S2;
		}
		else if( i2cStatus == S4 ) //Send RX Command
		{
			I2C1->DR = DevAddr | 0x01;
			i2cStatus = S5;
		}


		regSR1 = 0;
		regSR2 = 0;

	}
	if( (regSR & I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)== I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED )			//EV6
	{
		switch( i2cStatus )
		{
			case S2: //Send 1st memory address phase
			{
				//I2C_DMACmd(I2C1, ENABLE);
				I2C1->DR = MemAddr[0];
				if( memtype == I2C_MEM_1Byte ) 
					i2cStatus = S2_2;
				else if( memtype == I2C_MEM_2Bytes )
					i2cStatus = S2_1;
			}
			break;
			case S5: //Set RX buffer phase
			{
				if( i2cFlag == I2C_READ_DMA )
				{
					I2C_DMAConfig(I2C1, i2c_buf, BufSize, I2C_DIRECTION_RX);
					I2C1->CR2 |= CR2_LAST_Set | CR2_DMAEN_Set;
					DMA_ITConfig( I2C1_DMA_CHANNEL_RX, DMA_IT_TC, ENABLE);
				}
				else if( i2cFlag == I2C_READ_INTERRUPT )
				{ 
					I2C1->CR2 |= I2C_IT_BUF;
					I2C1->CR1 &= CR1_ACK_Reset;
	                /* Program the STOP */
	                I2C1->CR1 |= CR1_STOP_Set;
				}
				i2cStatus = S6;
			}
			break;
		}
		
		regSR1 = 0;
		regSR2 = 0;
		//dump_i2c_register(I2C1);
	}
	if((regSR & I2C_EVENT_MASTER_BYTE_RECEIVED) == I2C_EVENT_MASTER_BYTE_RECEIVED) //EV7
	{
		//Interrupt RX complete phase
		if( i2cStatus == S6	&& i2cFlag == I2C_READ_INTERRUPT )
		{
			*i2c_buf = I2C1->DR;
			i2cStatus = S_STOP;
			rt_event_send(&i2c_event, I2C_COMPLETE);
		}
	} 
	if( (regSR & I2C_EVENT_MASTER_BYTE_TRANSMITTED) == I2C_EVENT_MASTER_BYTE_TRANSMITTED ) //EV8_2
	{
		//Start TX/RX phase
		if(i2cStatus == S3)
		{
			DMA_ClearFlag(I2C1_DMA_CHANNEL_TX, DMA_FLAG_TCIF6 );
			DMA_Cmd(I2C1_DMA_CHANNEL_TX, DISABLE);
			switch (i2cFlag)
			{
				case I2C_WRITE:
					i2cStatus = S_STOP;
					I2C1->CR1 |= CR1_STOP_Set;
					rt_event_send(&i2c_event, I2C_COMPLETE);					
				break;

				case I2C_READ_DMA:
					i2cStatus = S4;
					I2C1->CR1 |= CR1_START_Set;
				break;

				case I2C_READ_POLLING:
					i2cStatus = S_STOP;
					rt_event_send(&i2c_event, I2C_COMPLETE);
					I2C1->CR2 &= ~(CR2_LAST_Set | I2C_IT_EVT | CR2_DMAEN_Set);
					I2C1->CR1 |= CR1_START_Set;
				break;

				case I2C_READ_INTERRUPT:
					i2cStatus = S4;
					I2C1->CR1 |= CR1_START_Set;
				break;
			}
		}
		if( i2cStatus == S2_1 ) //Send 2nd memory address
		{
			if( memtype == I2C_MEM_2Bytes ) //memory address has 2 bytes
			{
				I2C1->DR = MemAddr[1];
				i2cStatus = S2_2;
			}
			if( i2cFlag == I2C_READ_POLLING || i2cFlag == I2C_READ_DMA || i2cFlag == I2C_READ_INTERRUPT)
			{
				i2cStatus = S3;
			}
		}
		if( i2cStatus == S2_2 ) //Set TX DAM phase
		{
			I2C_DMAConfig(I2C1, i2c_buf, BufSize, I2C_DIRECTION_TX);
			I2C1->CR2 |= CR2_DMAEN_Set;
			i2cStatus = S3;
		}			   
	} 

	rt_interrupt_leave();

}

void DMA1_Stream6_IRQHandler(void) //I2C1 TX
{
	rt_interrupt_enter();
	if (DMA_GetITStatus(I2C1_DMA_CHANNEL_TX, DMA_IT_TCIF6))
    {
		I2C_TRACE("TXTC\n");
		DMA_ClearFlag(I2C1_DMA_CHANNEL_TX, DMA_FLAG_TCIF6 );
		
    }
	rt_interrupt_leave();	
}

void DMA1_Stream0_IRQHandler(void) //I2C1 RX
{

	rt_interrupt_enter();

	if (DMA_GetITStatus(I2C1_DMA_CHANNEL_RX, DMA_IT_TCIF0))
    {
	   I2C_TRACE("RXTC\n");
	   /* clear DMA flag */
		DMA_ClearFlag(I2C1_DMA_CHANNEL_RX, DMA_FLAG_TCIF0 );
		DMA_ITConfig( I2C1_DMA_CHANNEL_RX, DMA_IT_TC, DISABLE);
		DMA_Cmd(I2C1_DMA_CHANNEL_RX, DISABLE);
		if( i2cStatus == S6 )
		{
			i2cStatus = S_STOP;
			I2C1->CR1 |= CR1_STOP_Set;
			rt_event_send(&i2c_event, I2C_COMPLETE);
		}
    }
	if (DMA_GetITStatus(I2C1_DMA_CHANNEL_RX, DMA_IT_HTIF0))
	{
		I2C_TRACE("RXHT\n");
		DMA_ClearFlag(I2C1_DMA_CHANNEL_RX, DMA_FLAG_HTIF0 );
	}
	if (DMA_GetITStatus(I2C1_DMA_CHANNEL_RX, DMA_IT_TEIF0))
	{
		I2C_TRACE("RXTE\n");
		DMA_ClearFlag(I2C1_DMA_CHANNEL_RX, DMA_FLAG_TEIF0 );
	}
	if (DMA_GetITStatus(I2C1_DMA_CHANNEL_RX, DMA_IT_FEIF0))
	{
		I2C_TRACE("RXFE\n");
		DMA_ClearFlag(I2C1_DMA_CHANNEL_RX, DMA_FLAG_FEIF0 );
	}
	if (DMA_GetITStatus(I2C1_DMA_CHANNEL_RX, DMA_IT_DMEIF0))
	{
		I2C_TRACE("RXDME\n");
		DMA_ClearFlag(I2C1_DMA_CHANNEL_RX, DMA_FLAG_DMEIF0 );
	}

	rt_interrupt_leave();	
}

void I2C1_ER_IRQHandler()
{
	__IO uint16_t regSR1, regSR2;
	
	i2cErrorNo = 0;
	regSR1 = I2C1->SR1;
	I2C_TRACE("I2C Error SR1= 0x%X CR1 = 0x%X\n" , regSR1, I2C1->CR1);
	if( (regSR1 &  SR1_AF_Set) ==  SR1_AF_Set)
	{
		I2C1->SR1 &= ~SR1_AF_Set;
		i2cErrorNo |= ERR_AF;
		I2C_TRACE("ACK failure\n");
	}
	if( (regSR1 & SR1_BERR_Set) ==  SR1_BERR_Set)
	{
		I2C1->SR1 &= ~SR1_BERR_Set;
		i2cErrorNo |= ERR_BERR;
		I2C_TRACE("Bus Error\n");
	}
	if( (regSR1 & SR1_ARLO_Set) ==  SR1_ARLO_Set)
	{
		I2C1->SR1 &= ~SR1_ARLO_Set;
		i2cErrorNo |= ERR_ARLO;
		I2C_TRACE("Arblitation lost\n");
	}
	//dump_i2c_register(I2C1);

}
Status I2C_Free_Bus(I2C_TypeDef* I2Cx, u32 timeout )
{
	/*u32 i = 0;
	u16 tmp = 0;
	GPIO_InitTypeDef  GPIO_InitStructure;

	tmp = I2Cx->SR2;

	while( tmp & SR2_BUSY )
	{
		if( i++ < timeout )
		{
			if( I2Cx == I2C1 )
			{
				//rt_kprintf("Free Bus!\n");
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		        GPIO_Init(GPIOB, &GPIO_InitStructure);

				GPIO_SetBits(GPIOB, GPIO_Pin_6);
				GPIO_SetBits(GPIOB, GPIO_Pin_7);
				
			}
			else if( I2Cx == I2C2 )
			{
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		        GPIO_Init(GPIOB, &GPIO_InitStructure);

				GPIO_ResetBits(GPIOB, GPIO_Pin_10);
			}
			rt_thread_delay(10);
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
		    GPIO_Init(GPIOB, &GPIO_InitStructure);
			I2C_Cmd(I2Cx, DISABLE);
        	I2C_Cmd(I2Cx, ENABLE);
		}
		else
			return Error;
		tmp = I2Cx->SR2;
	}	*/
	return Success;

}

/*
	I2Cx: I2C1 or I2C2 (Now it only support I2C1)
	pBuffer: Buffer point
	NumByteToRW: Number of bytes read/write
    memAddr: 1-2 bytes memory address
	SlaveAddress: device address
	MemType: 1 = memory address size 1 bytes, 2 = memory address size 2 bytes	
*/
Status I2C_IORW(I2C_TypeDef* I2Cx, uint8_t* pBuffer, uint32_t NumByteToRW, uint16_t memAddr, uint8_t SlaveAddress, uint8_t MemType )
{
	uint32_t ev, Timeout=0xFFFF;
    uint16_t temp, temp2;
	static uint32_t call_cnt = 0, i;
	Status ret;

	ret = rt_mutex_take(i2c_mux, RT_WAITING_FOREVER );
	if( ret == RT_EOK )
	{
		ret = Success;
		DevAddr = SlaveAddress;
		BufSize = NumByteToRW;
		i2c_buf = pBuffer;
		memtype = MemType;

		MemAddr = (uint8_t*)&memAddr;
		I2CDirection = I2C_DIRECTION_TX;
	
		I2CMode = DMA;
	
		i2cStatus = S1;
		if( SlaveAddress  & 0x01 )
		{
			if( BufSize == 1 )
				i2cFlag = I2C_READ_INTERRUPT; //I2C_READ_POLLING; 
			else
				i2cFlag = I2C_READ_DMA;
		}
		else 
			i2cFlag = I2C_WRITE;
		I2Cx->CR2 |= I2C_IT_ERR | I2C_IT_EVT;// | CR2_DMAEN_Set;
			
		I2Cx->CR1 |= CR1_START_Set;

		Timeout = 0xFFFF;
		if( rt_event_recv( &i2c_event, I2C_COMPLETE, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &ev ) != RT_EOK ) {ret = Error; goto i2cError;}
	
		if( i2cFlag == I2C_READ_POLLING )
		{
			while ((I2Cx->SR1&0x0001) != 0x0001)
			if (Timeout-- == 0)	{ret = Error; goto i2cError;}
			Timeout = 0xFFFF;
	        I2Cx->DR = DevAddr;
	        /* Wait until ADDR is set: EV6 */
	        while ((I2Cx->SR1&0x0002) != 0x0002)
	        {
	            if (Timeout-- == 0){ret = Error; goto i2cError;}
	        }
			/* Clear ACK bit */
	        I2Cx->CR1 &= CR1_ACK_Reset;
	        /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
	        software sequence must complete before the current byte end of transfer */
	        __disable_irq();
	        /* Clear ADDR flag */
	        temp = I2Cx->SR2;
	        /* Program the STOP */
	        I2Cx->CR1 |= CR1_STOP_Set;
	        /* Re-enable IRQs */
	        __enable_irq();
	        /* Wait until a data is received in DR register (RXNE = 1) EV7 */
	        while ((I2Cx->SR1 & 0x00040) != 0x000040)if (Timeout-- == 0){ret = Error; goto i2cError;}
	        /* Read the data */
	        *i2c_buf = I2Cx->DR;
	        /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
	        while ((I2Cx->CR1&0x200) == 0x200)if (Timeout-- == 0){ret = Error; goto i2cError;}
	        /* Enable Acknowledgement to be ready for another reception */
	        I2Cx->CR1 |= CR1_ACK_Set;
		}
		else
		{
			while ((I2Cx->CR1&0x200) == 0x200)
			{
				if (Timeout-- == 0) {ret = Error; break;}
			}
			if( i2cFlag == I2C_READ_INTERRUPT )
				I2Cx->CR1 |= CR1_ACK_Set; 
		}
	i2cError:
		if( ret == Error )
		{
			/* TODO: i2c error handler */
			/* Need check i2cErrorNo and Reset I2C bus */
		}
		I2Cx->CR2 &= ~CR2_FREQ_Reset;
		//dump_i2c_register(I2C1);
		rt_mutex_release(i2c_mux);
		return ret;
	}
	else
		return Error;

}


void I2C1_INIT()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;

	if( i2c1_init_flag == 0 )
	{
		/* Enable the I2C clock */
		RCC_APB1PeriphClockCmd(I2C1_CLK, ENABLE);
		/* GPIOB clock enable */
	    RCC_AHB1PeriphClockCmd(I2C1_GPIO_CLK, ENABLE);
		/* Enable the DMA1 clock */
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
		//Reset GPIO
		GPIO_InitStructure.GPIO_Pin =  I2C1_SDA_PIN | I2C1_SCL_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(I2C1_GPIO_PORT, &GPIO_InitStructure);
	
		/* Connect PXx to I2C_SCL*/
	 	GPIO_PinAFConfig(I2C1_GPIO_PORT, I2C1_SDA_SOURCE, GPIO_AF_I2C1);
	
	    /* Connect PXx to I2C_SDA*/
	  	GPIO_PinAFConfig(I2C1_GPIO_PORT, I2C1_SCL_SOURCE, GPIO_AF_I2C1); 		
	
	    /* Enable I2C1 reset state */
	    RCC_APB1PeriphResetCmd(I2C1_CLK, ENABLE);
	    /* Release I2C1 from reset state */
	    RCC_APB1PeriphResetCmd(I2C1_CLK, DISABLE);
	
		I2C_DeInit(I2C1);
		I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	    I2C_InitStructure.I2C_OwnAddress1 = OwnAddress1;
	    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	    I2C_InitStructure.I2C_ClockSpeed = ClockSpeed;
	    I2C_Init(I2C1, &I2C_InitStructure);	 
	
		I2C_Cmd(I2C1, ENABLE);
	
		/* Configure and enable I2C1 event interrupt -------------------------------*/
		NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* Configure and enable I2C1 DMA interrupt -------------------------------*/  
		NVIC_InitStructure.NVIC_IRQChannel = I2C1_DMA_TX_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	
		NVIC_InitStructure.NVIC_IRQChannel = I2C1_DMA_RX_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	
		/* Configure and enable I2C1 error interrupt -------------------------------*/  
		NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_Init(&NVIC_InitStructure);
	
		/* I2C1 TX DMA Channel configuration */
		DMA_Cmd(I2C1_DMA_CHANNEL_TX, DISABLE);
	    DMA_DeInit(I2C1_DMA_CHANNEL_TX);
		I2CDMA_InitStructure.DMA_Channel = DMA_Channel_1;
	    I2CDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)I2C1_DR_Address;
	    I2CDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)0;   /* This parameter will be configured durig communication */
	    I2CDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;    /* This parameter will be configured durig communication */
	    I2CDMA_InitStructure.DMA_BufferSize = 0xFFFF;            /* This parameter will be configured durig communication */
	    I2CDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	    I2CDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	    I2CDMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	
	    I2CDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	    I2CDMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	    I2CDMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	    //I2CDMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		I2CDMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
		I2CDMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
		I2CDMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		I2CDMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	    DMA_Init(I2C1_DMA_CHANNEL_TX, &I2CDMA_InitStructure);
	
	    /* I2C1 RX DMA Channel configuration */
		DMA_Cmd(I2C1_DMA_CHANNEL_RX, DISABLE);
	    DMA_DeInit(I2C1_DMA_CHANNEL_RX);
	    DMA_Init(I2C1_DMA_CHANNEL_RX, &I2CDMA_InitStructure); 
		
		//I2C_AcknowledgePolling(I2C1, 0x70);
	
		rt_event_init(&i2c_event, "i2c_event", RT_IPC_FLAG_FIFO );
		i2c_mux = rt_mutex_create("i2c_mux", RT_IPC_FLAG_FIFO );
		i2c1_init_flag = 1;
	}
}

void I2C_DMAConfig(I2C_TypeDef* I2Cx, uint8_t* pBuffer, uint32_t BufferSize, uint32_t Direction)
{
    
	I2CDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pBuffer;
	I2CDMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;
	/* Initialize the DMA with the new parameters */
    if (Direction == I2C_DIRECTION_TX)
    {
        /* Configure the DMA Tx Channel with the buffer address and the buffer size */
        I2CDMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;

        if (I2Cx == I2C1)
		{
            I2CDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)I2C1_DR_Address;
			//DMA_Cmd(I2C1_DMA_CHANNEL_TX, DISABLE);
	        DMA_Init(I2C1_DMA_CHANNEL_TX, &I2CDMA_InitStructure);
	        DMA_Cmd(I2C1_DMA_CHANNEL_TX, ENABLE);
		}
        else
		{
            I2CDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)I2C2_DR_Address;
			//DMA_Cmd(I2C2_DMA_CHANNEL_TX, DISABLE);
        	DMA_Init(I2C2_DMA_CHANNEL_TX, &I2CDMA_InitStructure);
        	DMA_Cmd(I2C2_DMA_CHANNEL_TX, ENABLE);
		}

    }
    else /* Reception */
    {
        /* Configure the DMA Rx Channel with the buffer address and the buffer size */
        I2CDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

        if (I2Cx == I2C1)
		{
            I2CDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)I2C1_DR_Address;
			//DMA_Cmd(I2C1_DMA_CHANNEL_RX, DISABLE);
	        DMA_Init(I2C1_DMA_CHANNEL_RX, &I2CDMA_InitStructure);
	        DMA_Cmd(I2C1_DMA_CHANNEL_RX, ENABLE);
		}
        else 
		{
            I2CDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)I2C2_DR_Address;
		//	DMA_Cmd(I2C2_DMA_CHANNEL_RX, DISABLE);
	        DMA_Init(I2C2_DMA_CHANNEL_RX, &I2CDMA_InitStructure);
	        DMA_Cmd(I2C2_DMA_CHANNEL_RX, ENABLE);
		}

    }
}

