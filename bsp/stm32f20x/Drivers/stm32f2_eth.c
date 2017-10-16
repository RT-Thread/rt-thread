/*
 * STM32 Eth Driver for RT-Thread
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-05     Bernard      eth interface driver for STM32F107 CL
 */
#include <rtthread.h>
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "stm32f2x7_eth.h"
#include "stm32f2x7_eth_conf.h"

#define STM32_ETH_DEBUG		0
//#define CHECKSUM_BY_HARDWARE /* don't ues hardware checksum. */

/* MII and RMII mode selection, for STM322xG-EVAL Board(MB786) RevB ***********/
//#define MII_MODE       

#define RMII_MODE  // In this case the System clock frequency is configured
                     // to 100 MHz, for more details refer to system_stm32f2xx.c 

#define DP83848_PHY_ADDRESS       0x01 /* Relative to STM322xG-EVAL Board */

#define netifGUARD_BLOCK_TIME 250

/* Ethernet Rx & Tx DMA Descriptors */
extern ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];

/* Ethernet Receive buffers  */
extern uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE]; 

/* Ethernet Transmit buffers */
extern uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE]; 

/* Global pointers to track current transmit and receive descriptors */
extern ETH_DMADESCTypeDef  *DMATxDescToSet;
extern ETH_DMADESCTypeDef  *DMARxDescToGet;

/* Global pointer for last received frame infos */
extern ETH_DMA_Rx_Frame_infos *DMA_RX_FRAME_infos;

#define MAX_ADDR_LEN 6
struct rt_stm32_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/
};
static struct rt_stm32_eth stm32_eth_device;
static struct rt_semaphore tx_wait;
static rt_bool_t tx_is_waiting = RT_FALSE;

static void ETH_MACDMA_Config(void);

static struct rt_semaphore tx_wait;

/* interrupt service routine */
void ETH_IRQHandler(void)
{
   rt_uint32_t status;

	status = ETH->DMASR;

	/* Frame received */
	if ( ETH_GetDMAFlagStatus(ETH_DMA_FLAG_R) == SET) 
	{
		rt_err_t result;
		//rt_kprintf("Frame comming\n");
		/* Clear the interrupt flags. */
		/* Clear the Eth DMA Rx IT pending bits */  
		ETH_DMAClearITPendingBit(ETH_DMA_IT_R);

		/* a frame has been received */
		result = eth_device_ready(&(stm32_eth_device.parent));
		if( result != RT_EOK ) rt_kprintf("RX err =%d\n", result );
		//RT_ASSERT(result == RT_EOK); 
	}
	if (ETH_GetDMAITStatus(ETH_DMA_IT_T) == SET) /* packet transmission */
	{
		ETH_DMAClearITPendingBit(ETH_DMA_IT_T);
	}
	
	ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
//	

}

/* RT-Thread Device Interface */
/* initialize the interface */
static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{
	int i;

	/* MAC address configuration */
	ETH_MACAddressConfig(ETH_MAC_Address0, (u8*)&stm32_eth_device.dev_addr[0]);
	
	/* Initialize Tx Descriptors list: Chain Mode */
	ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
	/* Initialize Rx Descriptors list: Chain Mode  */
	ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

	 /* Enable Ethernet Rx interrrupt */
	{ 
		for(i=0; i<ETH_RXBUFNB; i++)
		{
		  ETH_DMARxDescReceiveITConfig(&DMARxDscrTab[i], ENABLE);
		}
	}
	
	#ifdef CHECKSUM_BY_HARDWARE
	/* Enable the checksum insertion for the Tx frames */
	{
		for(i=0; i<ETH_TXBUFNB; i++)
		{
		  ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
		}
	} 
	#endif

	{
		uint16_t tmp, i=10000;

		tmp = ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_CR);
		ETH_WritePHYRegister(DP83848_PHY_ADDRESS, PHY_CDCTRL1, BIST_CONT_MODE );
		ETH_WritePHYRegister(DP83848_PHY_ADDRESS, PHY_CR, tmp | BIST_START );//BIST_START

		while(i--);

		//tmp =  ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_CR);

		if( ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_CR) & BIST_STATUS == BIST_STATUS )
		{
			rt_kprintf("BIST pass\n");
		}
		else
		{
			uint16_t ctrl;

			ctrl = ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_CDCTRL1);
			rt_kprintf("BIST faild count =%d\n", BIST_ERROR_COUNT(ctrl) );
		}
		tmp &= ~BIST_START; //Stop BIST 
		ETH_WritePHYRegister(DP83848_PHY_ADDRESS, PHY_CR, tmp);


	} 

	/* Enable MAC and DMA transmission and reception */
	ETH_Start();

	//rt_kprintf("DMASR = 0x%X\n", ETH->DMASR );
//	rt_kprintf("ETH Init\n");

  return RT_EOK;
}

static rt_err_t rt_stm32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_stm32_eth_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_stm32_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_stm32_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_stm32_eth_control(rt_device_t dev, int cmd, void *args)
{
	switch(cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if(args) rt_memcpy(args, stm32_eth_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

void show_frame(struct pbuf *q)
{
	int i = 0;
	int j = 0;
	char *ptr = q->payload;

	for( i = 0; i < q->len; i++ )
	rt_kprintf("0x%02X ", *(ptr++));
	rt_kprintf("\n");
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_stm32_eth_tx( rt_device_t dev, struct pbuf* p)
{
	rt_err_t ret;
	struct pbuf *q;
	uint32_t l = 0;
	u8 *buffer ;
	
	if (( ret = rt_sem_take(&tx_wait, netifGUARD_BLOCK_TIME) ) == RT_EOK)
	{
		buffer =  (u8 *)(DMATxDescToSet->Buffer1Addr);
		for(q = p; q != NULL; q = q->next) 
		{
			//show_frame(q);
			rt_memcpy((u8_t*)&buffer[l], q->payload, q->len);
			l = l + q->len;
		}
		if( ETH_Prepare_Transmit_Descriptors(l) == ETH_ERROR )
			rt_kprintf("Tx Error\n");
		//rt_sem_release(xTxSemaphore);
		rt_sem_release(&tx_wait);
		//rt_kprintf("Tx packet, len = %d\n", l);
	}
	else
	{
		rt_kprintf("Tx Timeout\n");
		return ret;
	}

	/* Return SUCCESS */
	return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
	struct pbuf *p, *q;
	u16_t len;
	uint32_t l=0,i =0;
	FrameTypeDef frame;
	static framecnt = 1;
	u8 *buffer;
	__IO ETH_DMADESCTypeDef *DMARxNextDesc;
	
	p = RT_NULL;
	
//	rt_kprintf("ETH rx\n");
	/* Get received frame */
	frame = ETH_Get_Received_Frame_interrupt();
	
	if( frame.length > 0 )
	{
		/* check that frame has no error */
		if ((frame.descriptor->Status & ETH_DMARxDesc_ES) == (uint32_t)RESET)
		{
			//rt_kprintf("Get a frame %d buf = 0x%X, len= %d\n", framecnt++, frame.buffer, frame.length);
			/* Obtain the size of the packet and put it into the "len" variable. */
			len = frame.length;
			buffer = (u8 *)frame.buffer;
			
			/* We allocate a pbuf chain of pbufs from the pool. */
			p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
			//p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);

			/* Copy received frame from ethernet driver buffer to stack buffer */
			if (p != NULL)
			{ 
			  for (q = p; q != NULL; q = q->next)
			  {
			    rt_memcpy((u8_t*)q->payload, (u8_t*)&buffer[l], q->len);
			    l = l + q->len;
			  } 
			}
		}
	
		/* Release descriptors to DMA */
		/* Check if received frame with multiple DMA buffer segments */
		if (DMA_RX_FRAME_infos->Seg_Count > 1)
		{
			DMARxNextDesc = DMA_RX_FRAME_infos->FS_Rx_Desc;
		}
		else
		{
			DMARxNextDesc = frame.descriptor;
		}
		
		/* Set Own bit in Rx descriptors: gives the buffers back to DMA */
		for (i=0; i<DMA_RX_FRAME_infos->Seg_Count; i++)
		{  
			DMARxNextDesc->Status = ETH_DMARxDesc_OWN;
			DMARxNextDesc = (ETH_DMADESCTypeDef *)(DMARxNextDesc->Buffer2NextDescAddr);
		}
		
		/* Clear Segment_Count */
		DMA_RX_FRAME_infos->Seg_Count =0;
		
		
		/* When Rx Buffer unavailable flag is set: clear it and resume reception */
		if ((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)  
		{
			/* Clear RBUS ETHERNET DMA flag */
			ETH->DMASR = ETH_DMASR_RBUS;
			  
			/* Resume DMA reception */
			ETH->DMARPDR = 0;
		}
	}
	return p;
}

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 2 bit for pre-emption priority, 2 bits for subpriority */
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* Enable the Ethernet global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
 * GPIO Configuration for ETH
 */
static void GPIO_Configuration(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOs clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
                         RCC_AHB1Periph_GPIOC
                         , ENABLE);

  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure MCO (PA8) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO );

#ifdef MII_MODE
  /* Output PLL clock divided by 2 (25MHz) on MCO pin (PA8) to clock the PHY */
  RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);

  SYSCFG_ETH_MediaInterfaceConfig(SYSCFG_ETH_MediaInterface_MII);
#elif defined RMII_MODE
  /* Output PLL clock divided by 2 (50MHz) on MCO pin (PA8) to clock the PHY */
  //RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_2);

  SYSCFG_ETH_MediaInterfaceConfig(SYSCFG_ETH_MediaInterface_RMII);
#endif

/* Ethernet pins configuration ************************************************/

   /*
        ETH_MDIO -------------------------> PA2
        ETH_MDC --------------------------> PC1
        ETH_MII_RX_CLK/ETH_RMII_REF_CLK---> PA1
        ETH_MII_RX_DV/ETH_RMII_CRS_DV ----> PA7
        ETH_MII_RXD0/ETH_RMII_RXD0 -------> PC4
        ETH_MII_RXD1/ETH_RMII_RXD1 -------> PC5
        ETH_MII_TX_EN/ETH_RMII_TX_EN -----> PB11
        ETH_MII_TXD0/ETH_RMII_TXD0 -------> PB12
        ETH_MII_TXD1/ETH_RMII_TXD1 -------> PB13

		**** Just for MII Mode ****
		ETH_MII_CRS ----------------------> PA0
		ETH_MII_COL ----------------------> PA3
		ETH_MII_TX_CLK -------------------> PC3
		ETH_MII_RX_ER --------------------> PB10
		ETH_MII_RXD2 ---------------------> PB0
		ETH_MII_RXD3 ---------------------> PB1
		ETH_MII_TXD2 ---------------------> PC2
		ETH_MII_TXD3 ---------------------> PB8
                                                  */
  /* Configure PC1, PC4 and PC5 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_ETH);

  /* Configure PB11, PB12 and PB13 */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_ETH);

  /* Configure PA1, PA2 and PA7 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_ETH);

#ifdef MII_MODE
  /* Configure PC2, PC3 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_ETH);

  /* Configure PB0, PB1, PB10 and PB8 */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1, GPIO_Pin_10 | GPIO_Pin_8;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_ETH);

  /* Configure PA0, PA3 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_ETH);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_ETH);
#endif


}

/**
  * @brief  Configures the Ethernet Interface
  * @param  None
  * @retval None
  */
static void ETH_MACDMA_Config(void)
{
  ETH_InitTypeDef ETH_InitStructure;

  /* Enable ETHERNET clock  */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC | RCC_AHB1Periph_ETH_MAC_Tx |
                         RCC_AHB1Periph_ETH_MAC_Rx, ENABLE);                                             

  /* Reset ETHERNET on AHB Bus */
  ETH_DeInit();

  /* Software reset */
  ETH_SoftwareReset();

  /* Wait for software reset */
  while (ETH_GetSoftwareResetStatus() == SET);

  /* ETHERNET Configuration --------------------------------------------------*/
  /* Call ETH_StructInit if you don't like to configure all ETH_InitStructure parameter */
  ETH_StructInit(&ETH_InitStructure);

  /* Fill ETH_InitStructure parametrs */
  /*------------------------   MAC   -----------------------------------*/
  ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;
  //ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Disable; 
  //  ETH_InitStructure.ETH_Speed = ETH_Speed_10M;
  //  ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;   

  ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
  ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable;
  ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;
  ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;
  ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;
  ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;
  ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;
  ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;
#ifdef CHECKSUM_BY_HARDWARE
  ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable;
#endif

  /*------------------------   DMA   -----------------------------------*/  
  
  /* When we use the Checksum offload feature, we need to enable the Store and Forward mode: 
  the store and forward guarantee that a whole frame is stored in the FIFO, so the MAC can insert/verify the checksum, 
  if the checksum is OK the DMA can handle the frame otherwise the frame is dropped */
  ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable; 
  ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;         
  ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;     
 
  ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;       
  ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;   
  ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Enable;
  ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;      
  ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;                
  ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;          
  ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;
  ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_2_1;

  /* Configure Ethernet */
  if( ETH_Init(&ETH_InitStructure, DP83848_PHY_ADDRESS) ==  ETH_ERROR )
  	rt_kprintf("ETH init error, may be no link\n");

  /* Enable the Ethernet Rx Interrupt */
  ETH_DMAITConfig(ETH_DMA_IT_NIS | ETH_DMA_IT_R , ENABLE);
}

#define   DevID_SNo0       (*((rt_uint32_t *)0x1FFF7A10));  
#define   DevID_SNo1       (*((rt_uint32_t *)0x1FFF7A10+32));  
#define   DevID_SNo2       (*((rt_uint32_t *)0x1FFF7A10+64));
void rt_hw_stm32_eth_init(void)
{
	GPIO_Configuration();
	NVIC_Configuration();
	ETH_MACDMA_Config();

    stm32_eth_device.dev_addr[0] = 0x00;
    stm32_eth_device.dev_addr[1] = 0x60;
    stm32_eth_device.dev_addr[2] = 0x6e;
	{
		uint32_t cpu_id[3] = {0};
		cpu_id[2] = DevID_SNo2; cpu_id[1] = DevID_SNo1; cpu_id[0] = DevID_SNo0;
		
		// generate MAC addr from 96bit unique ID (only for test)
		stm32_eth_device.dev_addr[3] = (uint8_t)((cpu_id[0]>>16)&0xFF);
	    stm32_eth_device.dev_addr[4] = (uint8_t)((cpu_id[0]>>8)&0xFF);
	    stm32_eth_device.dev_addr[5] = (uint8_t)(cpu_id[0]&0xFF);

//	    stm32_eth_device.dev_addr[3] = *(rt_uint8_t*)(0x1FFF7A10+7);
//	    stm32_eth_device.dev_addr[4] = *(rt_uint8_t*)(0x1FFF7A10+8);
//	    stm32_eth_device.dev_addr[5] = *(rt_uint8_t*)(0x1FFF7A10+9);
	}

	stm32_eth_device.parent.parent.init       = rt_stm32_eth_init;
	stm32_eth_device.parent.parent.open       = rt_stm32_eth_open;
	stm32_eth_device.parent.parent.close      = rt_stm32_eth_close;
	stm32_eth_device.parent.parent.read       = rt_stm32_eth_read;
	stm32_eth_device.parent.parent.write      = rt_stm32_eth_write;
	stm32_eth_device.parent.parent.control    = rt_stm32_eth_control;
	stm32_eth_device.parent.parent.user_data  = RT_NULL;

	stm32_eth_device.parent.eth_rx     = rt_stm32_eth_rx;
	stm32_eth_device.parent.eth_tx     = rt_stm32_eth_tx;

	/* init tx semaphore */
	rt_sem_init(&tx_wait, "tx_wait", 1, RT_IPC_FLAG_FIFO);

	/* register eth device */
	eth_device_init(&(stm32_eth_device.parent), "e0");
}
static char led = 0;

void dp83483()
{
	uint16_t bsr,sts, bcr, phycr;

	bsr = ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_BSR);
	sts = ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_SR);
	bcr = ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_BCR);
	phycr = ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_CR);	

	rt_kprintf("BCR = 0x%X\tBSR = 0x%X\tPHY_STS = 0x%X\tPHY_CR = 0x%X\n", bcr,bsr,sts, phycr);

	rt_kprintf("PHY_FCSCR = 0x%X\n", ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_FCSCR	) );
	rt_kprintf("PHY_MISR = 0x%X\n", ETH_ReadPHYRegister(DP83848_PHY_ADDRESS, PHY_MISR ) );

	rt_kprintf("DMASR = 0x%X\n", ETH->DMASR );

	//ETH_WritePHYRegister(DP83848_PHY_ADDRESS, PHY_LEDCR, (uint16_t)(0x38 | led));
	led = (led==7)?0:7;

}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(dp83483, Show PHY register.);
#endif
