/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-08     tanek        first implementation
 */
#include <rtthread.h>
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "board.h"
#include "drv_pcf8574.h"
#include <rtdevice.h>
#include <finsh.h>

/* debug option */
//#define DEBUG
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP

#ifdef DEBUG
#define STM32_ETH_PRINTF          rt_kprintf
#else
#define STM32_ETH_PRINTF(...)
#endif

/*网络引脚设置 RMII接口 
    ETH_MDIO -------------------------> PA2
    ETH_MDC --------------------------> PC1
    ETH_RMII_REF_CLK------------------> PA1
    ETH_RMII_CRS_DV ------------------> PA7
    ETH_RMII_RXD0 --------------------> PC4
    ETH_RMII_RXD1 --------------------> PC5
    ETH_RMII_TX_EN -------------------> PB11
    ETH_RMII_TXD0 --------------------> PG13
    ETH_RMII_TXD1 --------------------> PG14
    ETH_RESET-------------------------> PCF8574扩展IO
*/
#define ETH_MDIO_PORN 					GPIOA
#define ETH_MDIO_PIN 					GPIO_PIN_2
#define ETH_MDC_PORN 					GPIOC
#define ETH_MDC_PIN 					GPIO_PIN_1
#define ETH_RMII_REF_CLK_PORN 			GPIOA
#define ETH_RMII_REF_CLK_PIN 			GPIO_PIN_1
#define ETH_RMII_CRS_DV_PORN 			GPIOA
#define ETH_RMII_CRS_DV_PIN 			GPIO_PIN_7
#define ETH_RMII_RXD0_PORN 				GPIOC
#define ETH_RMII_RXD0_PIN 				GPIO_PIN_4
#define ETH_RMII_RXD1_PORN 				GPIOC
#define ETH_RMII_RXD1_PIN 				GPIO_PIN_5
#define ETH_RMII_TX_EN_PORN 			GPIOB
#define ETH_RMII_TX_EN_PIN 				GPIO_PIN_11
#define ETH_RMII_TXD0_PORN 				GPIOG
#define ETH_RMII_TXD0_PIN 				GPIO_PIN_13
#define ETH_RMII_TXD1_PORN 				GPIOG
#define ETH_RMII_TXD1_PIN 				GPIO_PIN_14

#define LAN8742A_PHY_ADDRESS 0x00

#define MAX_ADDR_LEN 6
struct rt_stm32_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/

	uint32_t    ETH_Speed; /*!< @ref ETH_Speed */
	uint32_t    ETH_Mode;  /*!< @ref ETH_Duplex_Mode */
};


static ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];
static rt_uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];
static rt_bool_t tx_is_waiting = RT_FALSE;
static  ETH_HandleTypeDef EthHandle;
static struct rt_stm32_eth stm32_eth_device;
static struct rt_semaphore tx_wait;

/* interrupt service routine */
void ETH_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    
    HAL_ETH_IRQHandler(&EthHandle);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
{
    if (tx_is_waiting == RT_TRUE)
    {
        tx_is_waiting = RT_FALSE;
        rt_sem_release(&tx_wait);
    }
}

void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
    rt_err_t result;
    result = eth_device_ready(&(stm32_eth_device.parent));
    if( result != RT_EOK )
        rt_kprintf("RX err =%d\n", result );
}

void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    rt_kprintf("eth err\n");
}

static void phy_pin_reset(void)
{
	rt_pcf8574_write_bit(ETH_RESET_IO, 1);
	rt_thread_delay(RT_TICK_PER_SECOND / 10);
    
	rt_pcf8574_write_bit(ETH_RESET_IO, 0);
	rt_thread_delay(RT_TICK_PER_SECOND / 10);
}
#ifdef DEBUG
FINSH_FUNCTION_EXPORT(phy_pin_reset, phy hardware reset);
#endif

/* initialize the interface */
static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{
    STM32_ETH_PRINTF("rt_stm32_eth_init...\n");
	
	__HAL_RCC_ETH_CLK_ENABLE();
	
    rt_pcf8574_init();
	phy_pin_reset();

    /* ETHERNET Configuration --------------------------------------------------*/
	EthHandle.Instance = ETH;  
	EthHandle.Init.MACAddr = (rt_uint8_t*)&stm32_eth_device.dev_addr[0];
	EthHandle.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
	EthHandle.Init.Speed = ETH_SPEED_100M;
	EthHandle.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
	EthHandle.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
	EthHandle.Init.RxMode = ETH_RXINTERRUPT_MODE;
	EthHandle.Init.ChecksumMode = ETH_CHECKSUM_BY_SOFTWARE;
    //EthHandle.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
	EthHandle.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
	
	HAL_ETH_DeInit(&EthHandle);
	
	/* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
	if (HAL_ETH_Init(&EthHandle) == HAL_OK)
	{
		STM32_ETH_PRINTF("eth hardware init sucess...\n");
	}
    else
    {
		STM32_ETH_PRINTF("eth hardware init faild...\n");
    }

	/* Initialize Tx Descriptors list: Chain Mode */
	HAL_ETH_DMATxDescListInit(&EthHandle, DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
	 
	/* Initialize Rx Descriptors list: Chain Mode  */
	HAL_ETH_DMARxDescListInit(&EthHandle, DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

    /* Enable MAC and DMA transmission and reception */    
    if (HAL_ETH_Start(&EthHandle) == HAL_OK)
	{
		STM32_ETH_PRINTF("eth hardware start success...\n");
	}
    else
    {
		STM32_ETH_PRINTF("eth hardware start faild...\n");
    }
    
    //phy_monitor_thread_entry(NULL);

    return RT_EOK;
}

static rt_err_t rt_stm32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    STM32_ETH_PRINTF("rt_stm32_eth_open...\n");
	return RT_EOK;
}

static rt_err_t rt_stm32_eth_close(rt_device_t dev)
{
    STM32_ETH_PRINTF("rt_stm32_eth_close...\n");
	return RT_EOK;
}

static rt_size_t rt_stm32_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    STM32_ETH_PRINTF("rt_stm32_eth_read...\n");
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_stm32_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    STM32_ETH_PRINTF("rt_stm32_eth_write...\n");
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_stm32_eth_control(rt_device_t dev, int cmd, void *args)
{
    STM32_ETH_PRINTF("rt_stm32_eth_control...\n");
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

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_stm32_eth_tx( rt_device_t dev, struct pbuf* p)
{
    rt_err_t ret = RT_ERROR;
    HAL_StatusTypeDef state;
    struct pbuf *q;
    uint8_t *buffer = (uint8_t *)(EthHandle.TxDesc->Buffer1Addr);
    __IO ETH_DMADescTypeDef *DmaTxDesc;
    uint32_t framelength = 0;
    uint32_t bufferoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t payloadoffset = 0;
        
    DmaTxDesc = EthHandle.TxDesc;
    bufferoffset = 0;
    
    STM32_ETH_PRINTF("rt_stm32_eth_tx...\n");
   
    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    while ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
    {
        rt_err_t result;
        rt_uint32_t level;

        level = rt_hw_interrupt_disable();
        tx_is_waiting = RT_TRUE;
        rt_hw_interrupt_enable(level);

        /* it's own bit set, wait it */
        result = rt_sem_take(&tx_wait, RT_WAITING_FOREVER);
        if (result == RT_EOK) break;
        if (result == -RT_ERROR) return -RT_ERROR;
    }
    
    /* copy frame from pbufs to driver buffers */
    for(q = p; q != NULL; q = q->next)
    {
        /* Is this buffer available? If not, goto error */
        if((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
        {
            STM32_ETH_PRINTF("buffer not valid ...\n");
            ret = ERR_USE;
            goto error;
        }
        
        STM32_ETH_PRINTF("copy one frame\n");
        
        /* Get bytes in current lwIP buffer */
        byteslefttocopy = q->len;
        payloadoffset = 0;

        /* Check if the length of data to copy is bigger than Tx buffer size*/
        while( (byteslefttocopy + bufferoffset) > ETH_TX_BUF_SIZE )
        {
            /* Copy data to Tx buffer*/
            memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), (ETH_TX_BUF_SIZE - bufferoffset) );

            /* Point to next descriptor */
            DmaTxDesc = (ETH_DMADescTypeDef *)(DmaTxDesc->Buffer2NextDescAddr);

            /* Check if the buffer is available */
            if((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
            {
                STM32_ETH_PRINTF("dmatxdesc buffer not valid ...\n");
                ret = ERR_USE;
                goto error;
            }

            buffer = (uint8_t *)(DmaTxDesc->Buffer1Addr);

            byteslefttocopy = byteslefttocopy - (ETH_TX_BUF_SIZE - bufferoffset);
            payloadoffset = payloadoffset + (ETH_TX_BUF_SIZE - bufferoffset);
            framelength = framelength + (ETH_TX_BUF_SIZE - bufferoffset);
            bufferoffset = 0;
        }

        /* Copy the remaining bytes */
        memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), byteslefttocopy );
        bufferoffset = bufferoffset + byteslefttocopy;
        framelength = framelength + byteslefttocopy;
    }
    
#ifdef ETH_TX_DUMP
    {
        rt_uint32_t i;
        rt_uint8_t *ptr = buffer;

        STM32_ETH_PRINTF("tx_dump, len:%d\r\n", p->tot_len);
        for(i=0; i<p->tot_len; i++)
        {
            STM32_ETH_PRINTF("%02x ",*ptr);
            ptr++;

            if(((i+1)%8) == 0)
            {
                STM32_ETH_PRINTF("  ");
            }
            if(((i+1)%16) == 0)
            {
                STM32_ETH_PRINTF("\r\n");
            }
        }
        STM32_ETH_PRINTF("\r\ndump done!\r\n");
    }
#endif

    /* Prepare transmit descriptors to give to DMA */ 
    STM32_ETH_PRINTF("transmit frame, length: %d\n", framelength);
    state = HAL_ETH_TransmitFrame(&EthHandle, framelength);
    if (state != HAL_OK)
    {
        STM32_ETH_PRINTF("eth transmit frame faild: %d\n", state);
    }

    ret = ERR_OK;
  
error:
  
    /* When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission */
    if ((EthHandle.Instance->DMASR & ETH_DMASR_TUS) != (uint32_t)RESET)
    {
        /* Clear TUS ETHERNET DMA flag */
        EthHandle.Instance->DMASR = ETH_DMASR_TUS;

        /* Resume DMA transmission*/
        EthHandle.Instance->DMATPDR = 0;
    }
        
    return ret;
}

/* reception packet. */
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
    
    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    HAL_StatusTypeDef state;
    uint16_t len = 0;
    uint8_t *buffer;
    __IO ETH_DMADescTypeDef *dmarxdesc;
    uint32_t bufferoffset = 0;
    uint32_t payloadoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t i=0;
	
    STM32_ETH_PRINTF("rt_stm32_eth_rx\n");

	/* Get received frame */
    state = HAL_ETH_GetReceivedFrame_IT(&EthHandle);
	if (state != HAL_OK)
    {
        STM32_ETH_PRINTF("receive frame faild\n");
        return NULL;
    }
    
    /* Obtain the size of the packet and put it into the "len" variable. */
    len = EthHandle.RxFrameInfos.length;
    buffer = (uint8_t *)EthHandle.RxFrameInfos.buffer;

	STM32_ETH_PRINTF("receive frame len : %d\n", len);

    if (len > 0)
    {
        /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }

#ifdef ETH_RX_DUMP
	{
		rt_uint32_t i;
		rt_uint8_t *ptr = buffer;

		STM32_ETH_PRINTF("rx_dump, len:%d\r\n", p->tot_len);
		for (i = 0; i < len; i++)
		{
			STM32_ETH_PRINTF("%02x ", *ptr);
			ptr++;

			if (((i + 1) % 8) == 0)
			{
				STM32_ETH_PRINTF("  ");
			}
			if (((i + 1) % 16) == 0)
			{
				STM32_ETH_PRINTF("\r\n");
			}
		}
		STM32_ETH_PRINTF("\r\ndump done!\r\n");
	}
#endif
    
    if (p != NULL)
    {
        dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;
        bufferoffset = 0;
        for(q = p; q != NULL; q = q->next)
        {
            byteslefttocopy = q->len;
            payloadoffset = 0;

            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size*/
            while( (byteslefttocopy + bufferoffset) > ETH_RX_BUF_SIZE )
            {
                /* Copy data to pbuf */
                memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), (ETH_RX_BUF_SIZE - bufferoffset));

                /* Point to next descriptor */
                dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
                buffer = (uint8_t *)(dmarxdesc->Buffer1Addr);

                byteslefttocopy = byteslefttocopy - (ETH_RX_BUF_SIZE - bufferoffset);
                payloadoffset = payloadoffset + (ETH_RX_BUF_SIZE - bufferoffset);
                bufferoffset = 0;
            }
            /* Copy remaining data in pbuf */
            memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), byteslefttocopy);
            bufferoffset = bufferoffset + byteslefttocopy;
        }
    }  
  
    /* Release descriptors to DMA */
    /* Point to first descriptor */
    dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;
    /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
    for (i=0; i< EthHandle.RxFrameInfos.SegCount; i++)
    {  
        dmarxdesc->Status |= ETH_DMARXDESC_OWN;
        dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
    }
    
    /* Clear Segment_Count */
    EthHandle.RxFrameInfos.SegCount =0;  
  
    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((EthHandle.Instance->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)  
    {
        /* Clear RBUS ETHERNET DMA flag */
        EthHandle.Instance->DMASR = ETH_DMASR_RBUS;
        /* Resume DMA reception */
        EthHandle.Instance->DMARPDR = 0;
    }

    return p;
}

static void NVIC_Configuration(void)
{	
	/* Enable the Ethernet global Interrupt */
	HAL_NVIC_SetPriority(ETH_IRQn, 0x7, 0);
	HAL_NVIC_EnableIRQ(ETH_IRQn);
}

/*
 * GPIO Configuration for ETH
 */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    STM32_ETH_PRINTF("GPIO_Configuration...\n");
    
    /* Enable SYSCFG clock */
    __HAL_RCC_ETH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Alternate = GPIO_AF11_ETH;
    GPIO_InitStructure.Pull  = GPIO_NOPULL;

	GPIO_InitStructure.Pin = ETH_MDIO_PIN;
	HAL_GPIO_Init(ETH_MDIO_PORN,&GPIO_InitStructure);
	GPIO_InitStructure.Pin = ETH_MDC_PIN;
	HAL_GPIO_Init(ETH_MDC_PORN,&GPIO_InitStructure);

	GPIO_InitStructure.Pin = ETH_RMII_REF_CLK_PIN;
	HAL_GPIO_Init(ETH_RMII_REF_CLK_PORN,&GPIO_InitStructure);
	GPIO_InitStructure.Pin = ETH_RMII_CRS_DV_PIN;
	HAL_GPIO_Init(ETH_RMII_CRS_DV_PORN,&GPIO_InitStructure);

	GPIO_InitStructure.Pin = ETH_RMII_REF_CLK_PIN;
	HAL_GPIO_Init(ETH_RMII_REF_CLK_PORN,&GPIO_InitStructure);
	GPIO_InitStructure.Pin = ETH_RMII_CRS_DV_PIN;
	HAL_GPIO_Init(ETH_RMII_CRS_DV_PORN,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = ETH_RMII_RXD0_PIN;
	HAL_GPIO_Init(ETH_RMII_RXD0_PORN,&GPIO_InitStructure);
	GPIO_InitStructure.Pin = ETH_RMII_RXD1_PIN;
	HAL_GPIO_Init(ETH_RMII_RXD1_PORN,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = ETH_RMII_TX_EN_PIN;
	HAL_GPIO_Init(ETH_RMII_TX_EN_PORN,&GPIO_InitStructure);
	GPIO_InitStructure.Pin = ETH_RMII_TXD0_PIN;
	HAL_GPIO_Init(ETH_RMII_TXD0_PORN,&GPIO_InitStructure);
	GPIO_InitStructure.Pin = ETH_RMII_TXD1_PIN;
	HAL_GPIO_Init(ETH_RMII_TXD1_PORN,&GPIO_InitStructure);
	
    HAL_NVIC_SetPriority(ETH_IRQn,1,0);
    HAL_NVIC_EnableIRQ(ETH_IRQn);
}


void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
    GPIO_Configuration();
    NVIC_Configuration();
}

static int rt_hw_stm32_eth_init(void)
{
    rt_err_t state;
    
    stm32_eth_device.ETH_Speed = ETH_SPEED_100M;
    stm32_eth_device.ETH_Mode  = ETH_MODE_FULLDUPLEX;

    /* OUI 00-80-E1 STMICROELECTRONICS. */
    stm32_eth_device.dev_addr[0] = 0x00;
    stm32_eth_device.dev_addr[1] = 0x80;
    stm32_eth_device.dev_addr[2] = 0xE1;
    /* generate MAC addr from 96bit unique ID (only for test). */
    stm32_eth_device.dev_addr[3] = *(rt_uint8_t*)(UID_BASE+4);
    stm32_eth_device.dev_addr[4] = *(rt_uint8_t*)(UID_BASE+2);
    stm32_eth_device.dev_addr[5] = *(rt_uint8_t*)(UID_BASE+0);

    stm32_eth_device.parent.parent.init       = rt_stm32_eth_init;
    stm32_eth_device.parent.parent.open       = rt_stm32_eth_open;
    stm32_eth_device.parent.parent.close      = rt_stm32_eth_close;
    stm32_eth_device.parent.parent.read       = rt_stm32_eth_read;
    stm32_eth_device.parent.parent.write      = rt_stm32_eth_write;
    stm32_eth_device.parent.parent.control    = rt_stm32_eth_control;
    stm32_eth_device.parent.parent.user_data  = RT_NULL;

    stm32_eth_device.parent.eth_rx     = rt_stm32_eth_rx;
    stm32_eth_device.parent.eth_tx     = rt_stm32_eth_tx;

    STM32_ETH_PRINTF("sem init: tx_wait\r\n");
    /* init tx semaphore */
    rt_sem_init(&tx_wait, "tx_wait", 0, RT_IPC_FLAG_FIFO);

    /* register eth device */
    STM32_ETH_PRINTF("eth_device_init start\r\n");
    state = eth_device_init(&(stm32_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        STM32_ETH_PRINTF("eth_device_init success\r\n");
    }
    else
    {
        STM32_ETH_PRINTF("eth_device_init faild: %d\r\n", state);
    }
	
	eth_device_linkchange(&stm32_eth_device.parent, RT_TRUE);   //linkup the e0 for lwip to check
	
    return state;
}
INIT_APP_EXPORT(rt_hw_stm32_eth_init);
