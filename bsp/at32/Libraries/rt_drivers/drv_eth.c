/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-19     Joe          first version
 */

#include "at32f4xx_eth.h"
#include "board.h"
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "drv_eth.h"
#include <drv_log.h>

/* EMAC Interface */
#define PHY_ADDRESS         0x00  /* Relative to AT32F407-EVAL Board */
//#define MII_MODE                  /* MII mode for AT32F407-EVAL Board (MB784) (check jumpers setting) */
#define RMII_MODE                 /* RMII mode for AT32F407-EVAL Board (MB784) (check jumpers setting) */
//#define CRYSTAL_ON_PHY
#define MII_RX_REMAP        1

/* debug option */
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
//#define DRV_DEBUG
#define LOG_TAG             "drv.emac"

#define ETH_RXBUFNB        	4
#define ETH_TXBUFNB        	2

#define LINK_THREAD_STACK_SIZE   256
#define LINK_THREAD_PREORITY     21

extern ETH_DMADESCTypeDef  *DMATxDescToSet;
extern ETH_DMADESCTypeDef  *DMARxDescToGet;
extern ETH_DMADESCTypeDef  *DMAPTPTxDescToSet;
extern ETH_DMADESCTypeDef  *DMAPTPRxDescToGet;

static ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];
static rt_uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];
static struct rt_thread eth_link_thread;
static rt_uint8_t eth_link_stack[LINK_THREAD_STACK_SIZE];

#define MAX_ADDR_LEN        6
/* Gloable variables ---------------------------------------------------------*/
void static Reset_Phy(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

struct rt_at32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif

    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    uint32_t    ETH_Speed;
    /* ETH_Duplex_Mode */
    uint32_t    ETH_Mode;
};

static ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];                     /* Ethernet Rx & Tx DMA Descriptors */
static uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE]; /* Ethernet buffers */
//static  ETH_HandleTypeDef EthHandle;
static struct rt_at32_eth at32_eth_device;
static struct rt_semaphore tx_wait;
static rt_bool_t tx_is_waiting = RT_FALSE;

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%02X ", buf[i + j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        rt_kprintf("\n");
    }
}
#endif

/**
  * @brief  reset the phy
  * @param  None
  * @retval None
  */
void static Reset_Phy(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOC, GPIO_Pins_8);
    rt_thread_mdelay(2);
    GPIO_SetBits(GPIOC, GPIO_Pins_8);
    rt_thread_mdelay(2000);
}

/**
  * @brief  Configure NVIC for ISR
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
    NVIC_InitType   NVIC_InitStructure;

    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 

    /* Enable the Ethernet global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
}

/**
  * @brief  Configure GPIO for ethernet
  * @param  None
  * @retval None
  */

void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

#if MII_RX_REMAP
    GPIO_PinsRemapConfig(GPIO_Remap_ETH, ENABLE);
#endif
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA | RCC_APB2PERIPH_GPIOB | RCC_APB2PERIPH_GPIOC |
                           RCC_APB2PERIPH_GPIOD | RCC_APB2PERIPH_GPIOE | RCC_APB2PERIPH_AFIO, ENABLE);
    /* ETHERNET pins configuration */
    /* AF Output Push Pull:
    ETH_MII_MDIO / ETH_RMII_MDIO: PA2
    ETH_MII_MDC  / ETH_RMII_MDC: PC1
    */
    /* Configure PA2 as alternate function push-pull MDIO*/
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_2;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*PC1-->MDC*/
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_1;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	/*MII Mode GPIO configuration*/
#ifdef MII_MODE
/**********************MII Tx Pin Define****************************/
    /*
    ETH_MII_TX0-->PB12 AF-PP
    ETH_MII_TX1-->PB13 AF-PP
    ETH_MII_TX2-->PC2  AF-PP
    ETH_MII_TX3-->PB8  AF-PP
    ETH_MII_TX_EN-->PB11 AF-PP
    ETH_MII_TX_CLK-->PC3
    */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8 | GPIO_Pins_11 | GPIO_Pins_12 | GPIO_Pins_13;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_2 | GPIO_Pins_3;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	/**********************MII Rx Pin Define****************************/
#if MII_RX_REMAP  /*IO PIN remaped*/
    /*
    ETH_MII_RX_DV-->PD8
    ETH_MII_RXD0-->PD9
    ETH_MII_RXD1-->PD10
    ETH_MII_RXD2-->PD11
    ETH_MII_RXD3-->PD12
    ETH_MII_RXCLK-->PA1
    ETH_MII_CRS-->PA0
    ETH_MII_COL-->PA3
    ETH_MII_RX_ER-->PB10
    */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8 | GPIO_Pins_9 | GPIO_Pins_10 | GPIO_Pins_11 | GPIO_Pins_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_0 | GPIO_Pins_1 | GPIO_Pins_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#else
    /*
    ETH_MII_RX_DV-->PA7
    ETH_MII_RXD0-->PC4
    ETH_MII_RXD1-->PC5
    ETH_MII_RXD2-->PB0
    ETH_MII_RXD3-->PB1
    ETH_MII_RXCLK-->PA1
    ETH_MII_CRS-->PA0
    ETH_MII_COL-->PA3
    ETH_MII_RX_ER-->PB10
    */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_0 | GPIO_Pins_1 | GPIO_Pins_3 | GPIO_Pins_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_4 | GPIO_Pins_5;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_0 | GPIO_Pins_1 | GPIO_Pins_10;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

#endif  //End MII RX REMAP
#endif //End MII mode

#ifdef RMII_MODE
/**********************RMII Tx Pin Define****************************/
    /*
    ETH_RMII_TX0-->PB12 AF-PP
    ETH_RMII_TX1-->PB13 AF-PP
    ETH_RMII_TX_EN-->PB11 AF-PP
    */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_11 | GPIO_Pins_12 | GPIO_Pins_13;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/**********************RMII Rx Pin Define****************************/
#if MII_RX_REMAP  /*IO PIN remaped*/
    /*
    ETH_RMII_RX_DV-->PD8
    ETH_RMII_RXD0-->PD9
    ETH_RMII_RXD1-->PD10
    ETH_RMII_REF_CLK-->PA1
    */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8 | GPIO_Pins_9 | GPIO_Pins_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pins =  GPIO_Pins_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#else
    /*
    ETH_RMII_RX_DV-->PA7
    ETH_RMII_RXD0-->PC4
    ETH_RMII_RXD1-->PC5
    ETH_RMII_REF_CLK-->PA1
    */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_1 | GPIO_Pins_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_4 | GPIO_Pins_5;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

#endif //End RMII RX REMAP
#endif //End RMII mode

    /* ADC Channel4 config --------------------------------------------------------*/
    /* Configure PA4(ADC Channel4) as analog input -------------------------*/
    #ifdef ADC_NECESSARY
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_ANALOG;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    #endif

    /* MCO pin configuration------------------------------------------------- */
    /* Configure MCO (PA8) as alternate function push-pull */
    #ifndef CRYSTAL_ON_PHY
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    #endif
}

/* EMAC initialization function */
static rt_err_t rt_at32_eth_init(rt_device_t dev)
{
    ETH_InitType ETH_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_ETHMAC | RCC_AHBPERIPH_ETHMACTX |
                          RCC_AHBPERIPH_ETHMACRX, ENABLE);
    
    /* MII/RMII Media interface selection ------------------------------------------*/
#ifdef MII_MODE /* Mode MII with AT32F407-EVAL  */
    GPIO_ETH_MediaInterfaceConfig(GPIO_ETH_MediaInterface_MII);

    /* Get 25MHz from system clock 200MHz on PA8 pin (MCO) */
    #ifndef CRYSTAL_ON_PHY
    RCC_CLKOUTConfig(RCC_CLKOUT_SYSCLK, RCC_MCOPRE_8);
    #endif

#elif defined RMII_MODE  /* Mode RMII with AT32F407-EVAL */
    GPIO_ETH_MediaInterfaceConfig(GPIO_ETH_MediaInterface_RMII);
    #ifndef CRYSTAL_ON_PHY
    RCC_CLKOUTConfig(RCC_CLKOUT_SYSCLK, RCC_MCOPRE_8); /*25M to RMII Mode*/
    #endif
#endif

    /*Reset phy*/
    Reset_Phy();
    /* Reset ETHERNET on AHB Bus */
    ETH_DeInit();

    /* Software reset */
    ETH_SoftwareReset();

    /* Wait for software reset */
    while (ETH_GetSoftwareResetStatus() == SET);

    /* ETHERNET Configuration ------------------------------------------------------*/
    /* Call ETH_StructInit if you don't like to configure all ETH_InitStructure parameter */
    ETH_StructInit(&ETH_InitStructure);

    /* Fill ETH_InitStructure parametrs */
    /*------------------------   MAC   -----------------------------------*/
    ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;//ETH_AutoNegotiation_Enable  ;
    ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
    ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Enable;
    ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;
    ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;
    ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;
    ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;
    ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;//ETH_MulticastFramesFilter_Perfect;
    ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;
#ifdef CHECKSUM_BY_HARDWARE
    ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable;
#endif

    /*------------------------   DMA   -----------------------------------*/  

    /* When we use the Checksum offload feature, we need to enable the Store and Forward mode: 
    the store and forward guarantee that a whole frame is stored in the FIFO, so the MAC can insert/verify the checksum, 
    if the checksum is OK the DMA can handle the frame otherwise the frame is dropped */
    ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable;//ETH_DropTCPIPChecksumErrorFrame_Enable; 
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

    /* Configure Ethernet, check error */
    if(ETH_Init(&ETH_InitStructure, PHY_ADDRESS) == ((uint32_t)0)) {
        return RT_ERROR;
    }    

    /* Enable DMA Receive interrupt (need to enable in this case Normal interrupt) */
    ETH_DMAITConfig(ETH_DMA_INT_NIS | ETH_DMA_INT_R, ENABLE);  

    /* Initialize Tx Descriptors list: Chain Mode */
    ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
    /* Initialize Rx Descriptors list: Chain Mode  */
    ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

    /* MAC address configuration */
    ETH_MACAddressConfig(ETH_MAC_Address0, (u8*)&at32_eth_device.dev_addr[0]);

    /* Enable ETH transmition and recetion */
    ETH_Start();    

    return RT_EOK;
}

static rt_err_t rt_at32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_at32_eth_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_size_t rt_at32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_at32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_at32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, at32_eth_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit data*/
rt_err_t rt_at32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct pbuf* q;
    rt_uint32_t offset;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    while ((DMATxDescToSet->Status & ETH_DMATxDesc_OWN) != (uint32_t)RESET)
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

    offset = 0;
    for (q = p; q != NULL; q = q->next)
    {
        uint8_t *to;

        /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
        to = (uint8_t*)((DMATxDescToSet->Buffer1Addr) + offset);
        memcpy(to, q->payload, q->len);
        offset += q->len;
    }
#ifdef ETH_TX_DUMP
    {
        rt_uint32_t i;
        rt_uint8_t *ptr = (rt_uint8_t*)(DMATxDescToSet->Buffer1Addr);

        AT32_ETH_PRINTF("tx_dump, len:%d\r\n", p->tot_len);
        for(i=0; i<p->tot_len; i++)
        {
            AT32_ETH_PRINTF("%02x ",*ptr);
            ptr++;

            if(((i+1)%8) == 0)
            {
                AT32_ETH_PRINTF("  ");
            }
            if(((i+1)%16) == 0)
            {
                AT32_ETH_PRINTF("\r\n");
            }
        }
        AT32_ETH_PRINTF("\r\ndump done!\r\n");
    }
#endif

    /* Setting the Frame Length: bits[12:0] */
    DMATxDescToSet->ControlBufferSize = (p->tot_len & ETH_DMATxDesc_TBS1);
    /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */
    DMATxDescToSet->Status |= ETH_DMATxDesc_LS | ETH_DMATxDesc_FS;
    /* Enable TX Completion Interrupt */
    DMATxDescToSet->Status |= ETH_DMATxDesc_IC;
#ifdef CHECKSUM_BY_HARDWARE
    DMATxDescToSet->Status |= ETH_DMATxDesc_ChecksumTCPUDPICMPFull;
    /* clean ICMP checksum STM32F need */
    {
        struct eth_hdr *ethhdr = (struct eth_hdr *)(DMATxDescToSet->Buffer1Addr);
        /* is IP ? */
        if( ethhdr->type == htons(ETHTYPE_IP) )
        {
            struct ip_hdr *iphdr = (struct ip_hdr *)(DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR);
            /* is ICMP ? */
            if( IPH_PROTO(iphdr) == IP_PROTO_ICMP )
            {
                struct icmp_echo_hdr *iecho = (struct icmp_echo_hdr *)(DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR + sizeof(struct ip_hdr) );
                iecho->chksum = 0;
            }
        }
    }
#endif
    /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMATxDescToSet->Status |= ETH_DMATxDesc_OWN;
    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if ((ETH->DMASTS & ETH_DMA_FLAG_TBU) != (uint32_t)RESET)
    {
        /* Clear TBUS ETHERNET DMA flag */
        ETH->DMASTS = ETH_DMA_FLAG_TBU;
        /* Transmit Poll Demand to resume DMA transmission*/
        ETH->DMATPD = 0;
    }

    /* Update the ETHERNET DMA global Tx descriptor with next Tx decriptor */
    /* Chained Mode */
    /* Selects the next DMA Tx descriptor list for next buffer to send */
    DMATxDescToSet = (ETH_DMADESCTypeDef*) (DMATxDescToSet->Buffer2NextDescAddr);

    /* Return SUCCESS */
    return RT_EOK;
}

/* receive data*/
struct pbuf *rt_at32_eth_rx(rt_device_t dev)
{
    struct pbuf* p;
    rt_uint32_t offset = 0, framelength = 0;

    /* init p pointer */
    p = RT_NULL;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if(((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (uint32_t)RESET))
        return p;

    if (((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (uint32_t)RESET) &&
      ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (uint32_t)RESET) &&
      ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (uint32_t)RESET))
    {
        /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
        framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> 16) - 4;

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, framelength, PBUF_RAM);
        if (p != RT_NULL)
        {
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                memcpy(q->payload, (uint8_t *)((DMARxDescToGet->Buffer1Addr) + offset), q->len);
                offset += q->len;
            }
  #ifdef ETH_RX_DUMP
            {
                rt_uint32_t i;
                rt_uint8_t *ptr = (rt_uint8_t*)(DMARxDescToGet->Buffer1Addr);
                
                AT32_ETH_PRINTF("rx_dump, len:%d\r\n", p->tot_len);
                for(i=0; i<p->tot_len; i++)
                {
                    AT32_ETH_PRINTF("%02x ", *ptr);
                    ptr++;

                    if(((i+1)%8) == 0)
                    {
                        AT32_ETH_PRINTF("  ");
                    }
                    if(((i+1)%16) == 0)
                    {
                        AT32_ETH_PRINTF("\r\n");
                    }
                }
                AT32_ETH_PRINTF("\r\ndump done!\r\n");
            }
  #endif
        }
    }

    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMARxDescToGet->Status = ETH_DMARxDesc_OWN;

    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((ETH->DMASTS & ETH_DMA_FLAG_RBU) != (uint32_t)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        ETH->DMASTS = ETH_DMA_FLAG_RBU;
        /* Resume DMA reception */
        ETH->DMARPD = 0;
    }

    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer to read */
        DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);
    }
    else /* Ring Mode */
    {
        if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RER) != (uint32_t)RESET)
        {
            /* Selects the first DMA Rx descriptor for next buffer to read: last Rx descriptor was used */
            DMARxDescToGet = (ETH_DMADESCTypeDef*) (ETH->DMARDLADDR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer to read */
            DMARxDescToGet = (ETH_DMADESCTypeDef*) ((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABM & 0x0000007C) >> 2));
        }
    }

    return p;
}

static void eth_link_thread_entry(void *paramter)
{
    uint8_t linked_down = 1;

    struct netif *pnetif = at32_eth_device.parent.netif;

    while(1){
        if((ETH_ReadPHYRegister(PHY_ADDRESS, PHY_BSR) & PHY_Linked_Status) && (linked_down == 1))
        {
            /* link up */
            linked_down = 0;
#ifndef RT_LWIP_DHCP
            pnetif->ip_addr = inet_addr(RT_LWIP_IPADDR);
            pnetif->gw = inet_addr(RT_LWIP_GWADDR);
            pnetif->netmask = inet_addr(RT_LWIP_MSKADDR);
#else
            IP4_ADDR(&(pnetif->ip_addr), 0, 0, 0, 0);
            IP4_ADDR(&(pnetif->netmask), 0, 0, 0, 0);
            IP4_ADDR(&(pnetif->gw), 0, 0, 0, 0);
#endif
            eth_device_linkchange(&(at32_eth_device.parent), RT_TRUE);
        }else if(!(ETH_ReadPHYRegister(PHY_ADDRESS, PHY_BSR) & PHY_Linked_Status) && (linked_down == 0))
        {
            /* link down */
            linked_down = 1;
            eth_device_linkchange(&(at32_eth_device.parent), RT_FALSE);
        }
        rt_thread_mdelay(500);
    }
}

/* interrupt service routine */
void ETH_IRQHandler(void)
{
    rt_uint32_t status;

    status = ETH->DMASTS;

    /* Clear received IT */
    if ((status & ETH_DMA_INT_NIS) != (u32)RESET)
        ETH->DMASTS = (u32)ETH_DMA_INT_NIS;
    if ((status & ETH_DMA_INT_AIS) != (u32)RESET)
        ETH->DMASTS = (u32)ETH_DMA_INT_AIS;
    if ((status & ETH_DMA_INT_RO) != (u32)RESET)
        ETH->DMASTS = (u32)ETH_DMA_INT_RO;
    if ((status & ETH_DMA_INT_RBU) != (u32)RESET)
        ETH->DMASTS = (u32)ETH_DMA_INT_RBU;

    if (ETH_GetDMAITStatus(ETH_DMA_INT_R) == SET) /* packet receiption */
    {
        /* a frame has been received */
        eth_device_ready(&(at32_eth_device.parent));

        ETH_DMAClearITPendingBit(ETH_DMA_INT_R);
    }

    if (ETH_GetDMAITStatus(ETH_DMA_INT_T) == SET) /* packet transmission */
    {
        if (tx_is_waiting == RT_TRUE)
        {
            tx_is_waiting = RT_FALSE;
            rt_sem_release(&tx_wait);
        }

        ETH_DMAClearITPendingBit(ETH_DMA_INT_T);
    }
}

enum {
    PHY_LINK        = (1 << 0),
    PHY_100M        = (1 << 1),
    PHY_FULL_DUPLEX = (1 << 2),
};

/* Register the EMAC device */
static int rt_hw_at32_eth_init(void)
{
    rt_err_t state = RT_EOK;

    Reset_Phy();

    GPIO_Configuration();
    NVIC_Configuration();

    at32_eth_device.dev_addr[0] = 0x00;
    at32_eth_device.dev_addr[1] = 0x80;
    at32_eth_device.dev_addr[2] = 0xE1;
    at32_eth_device.dev_addr[3] = 0x94;
    at32_eth_device.dev_addr[4] = 0x87;
    at32_eth_device.dev_addr[5] = 0x55;

    at32_eth_device.parent.parent.init       = rt_at32_eth_init;
    at32_eth_device.parent.parent.open       = rt_at32_eth_open;
    at32_eth_device.parent.parent.close      = rt_at32_eth_close;
    at32_eth_device.parent.parent.read       = rt_at32_eth_read;
    at32_eth_device.parent.parent.write      = rt_at32_eth_write;
    at32_eth_device.parent.parent.control    = rt_at32_eth_control;
    at32_eth_device.parent.parent.user_data  = RT_NULL;

    at32_eth_device.parent.eth_rx            = rt_at32_eth_rx;
    at32_eth_device.parent.eth_tx            = rt_at32_eth_tx;

    /* register eth device */
    state = eth_device_init(&(at32_eth_device.parent), "e0");

    if (RT_EOK == state)
    {
        LOG_D("emac device init success");

        state = rt_thread_init(&eth_link_thread, "eth_link_detect", eth_link_thread_entry, RT_NULL,
                     &eth_link_stack[0], LINK_THREAD_STACK_SIZE, LINK_THREAD_PREORITY, 20);
        if (state == RT_EOK)
        {
            rt_thread_startup(&eth_link_thread);
        }
    }
    else
    {
        LOG_E("emac device init faild: %d", state);
        state = -RT_ERROR;
    }
    /* start phy monitor */
    return state;
}

INIT_DEVICE_EXPORT(rt_hw_at32_eth_init);
