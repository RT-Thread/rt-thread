/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH          the first version
 */

#include "board.h"
#include <rtdevice.h>


#ifdef BSP_USING_ETH
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include <drv_eth.h>

#define LOG_TAG              "drv.eth"
#include <drv_log.h>

#define MAX_ADDR_LEN 6
#define  ETH_DMARxDesc_FrameLengthShift           16

#define define_O(a,b) \
GPIO_InitStructure.GPIO_Pin = b;\
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;\
GPIO_Init(a, &GPIO_InitStructure)

#define define_I(a,b) \
GPIO_InitStructure.GPIO_Pin = b;\
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;\
GPIO_Init(a, &GPIO_InitStructure)


/* globe variable */
extern ETH_DMADESCTypeDef  *DMATxDescToSet;   //set tx Desc then send it
extern ETH_DMADESCTypeDef  *DMARxDescToGet;   //current rx Desc


/* rt-thread eth */
struct rt_ch32_eth
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

static ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];
static rt_uint8_t  Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE],Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];
struct rt_ch32_eth  ch32v30x_eth_device;


//#define ETH_RX_DUMP
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
        rt_kprintf("\r\n");
    }
}
#endif


/* received data */
FrameTypeDef ETH_RxPkt_ChainMode(void)
{
    u32 framelength = 0;
    FrameTypeDef frame = {0,0,NULL};

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (u32)RESET)
    {
        frame.length = ETH_ERROR;
        if ((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)
        {
            /* Clear RBUS ETHERNET DMA flag */
            ETH->DMASR = ETH_DMASR_RBUS;
            /* Resume DMA reception */
            ETH->DMARPDR = 0;
        }
        LOG_E("Error:ETH_DMARxDesc_OWN.\r\n");
    /* Return error: OWN bit set */
    return frame;
    }

    if(
        ((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (u32)RESET) &&
        ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (u32)RESET) &&
        ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (u32)RESET))
    {
        /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
        framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARxDesc_FrameLengthShift) - 4;

        /* Get the addrees of the actual buffer */
        frame.buffer = DMARxDescToGet->Buffer1Addr;
    }
    else
    {
        /* Return ERROR */
        framelength = ETH_ERROR;
        rt_kprintf("Error:recv error frame,status:0x%08x.\r\n",DMARxDescToGet->Status);
    }
    DMARxDescToGet->Status|=ETH_DMARxDesc_OWN;
    frame.length = framelength;
    frame.descriptor = DMARxDescToGet;

    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    /* Selects the next DMA Rx descriptor list for next buffer to read */
    DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);
    /* Return Frame */
    return (frame);
}



/*******************************************************************************
* Function Name  : GETH_pin_init
* Description    : PHY RGMII interface GPIO initialization.
* Input          : None.
* Return         : None.
*******************************************************************************/
void GETH_pin_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* PB12/13 set AF_PP_OUT */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
    GPIOB->CFGHR&=~(0xff<<16);
    GPIOB->CFGHR|= (0xbb<<16);
    GPIOB->CFGLR&=~(0xff<<4);

    define_O(GPIOA,GPIO_Pin_2);
    define_O(GPIOA,GPIO_Pin_3);
    define_O(GPIOA,GPIO_Pin_7);
    define_O(GPIOC,GPIO_Pin_4);
    define_O(GPIOC,GPIO_Pin_5);
    define_O(GPIOB,GPIO_Pin_0);

    define_I(GPIOC,GPIO_Pin_0);
    define_I(GPIOC,GPIO_Pin_1);
    define_I(GPIOC,GPIO_Pin_2);
    define_I(GPIOC,GPIO_Pin_3);
    define_I(GPIOA,GPIO_Pin_0);
    define_I(GPIOA,GPIO_Pin_1);

    define_I(GPIOB,GPIO_Pin_1);/* 125m in */
}


/*******************************************************************************
* Function Name  : GETH_pin_init
* Description    : PHY MII/RMII interface GPIO initialization.
* Input          : None.
* Return         : None.
*******************************************************************************/
void FETH_pin_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

#ifdef USE_RMII
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_ETH_MediaInterfaceConfig(GPIO_ETH_MediaInterface_RMII);
    define_O(GPIOA,GPIO_Pin_2);/* MDC */
    define_O(GPIOC,GPIO_Pin_1);/* MDIO */

    define_O(GPIOB,GPIO_Pin_11);//txen
    define_O(GPIOB,GPIO_Pin_12);//txd0
    define_O(GPIOB,GPIO_Pin_13);//txd1

    define_I(GPIOA,GPIO_Pin_1);/* PA1 REFCLK */
    define_I(GPIOA,GPIO_Pin_7);/* PA7 CRSDV */
    define_I(GPIOC,GPIO_Pin_4);/* RXD0 */
    define_I(GPIOC,GPIO_Pin_5);/* RXD1 */

#else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
    /* tx */
    define_O(GPIOA,GPIO_Pin_2);/* MDC */
    define_O(GPIOC,GPIO_Pin_1);/* MDIO */

    define_I(GPIOC,GPIO_Pin_3);//txclk
    define_O(GPIOB,GPIO_Pin_11);//txen
    define_O(GPIOB,GPIO_Pin_12);//txd0
    define_O(GPIOB,GPIO_Pin_13);//txd1
    define_O(GPIOC,GPIO_Pin_2); //txd2
    define_O(GPIOB,GPIO_Pin_8);//txd3
    /* tx */
    define_I(GPIOA,GPIO_Pin_1);/* PA1 RXC */
    define_I(GPIOA,GPIO_Pin_7);/* PA7 RXDV */
    define_I(GPIOC,GPIO_Pin_4);/* RXD0 */
    define_I(GPIOC,GPIO_Pin_5);/* RXD1 */
    define_I(GPIOB,GPIO_Pin_0);/* RXD2 */
    define_I(GPIOB,GPIO_Pin_1);/* RXD3 */
    define_I(GPIOB,GPIO_Pin_10);/* RXER */

    define_O(GPIOA,GPIO_Pin_0);/* PA0 */
    define_O(GPIOA,GPIO_Pin_3);/* PA3 */
#endif
}

/*******************************************************************************
* Function Name  : ETH_Init
* Description    : ETH initialization.
* Input          : ETH_InitStruct:initialization struct.
*                  PHYAddress:PHY address.
* Return         : Initialization status.
*******************************************************************************/
uint32_t ETH_Init(ETH_InitTypeDef* ETH_InitStruct, uint16_t PHYAddress)
{
    uint32_t tmpreg = 0;
    uint16_t RegValue = 0;
    uint32_t tickstart=0;
    /* config phy */
    tmpreg = ETH->MACMIIAR;
    tmpreg &= MACMIIAR_CR_MASK;
    /* set SMI clock */
    tmpreg |= (uint32_t)ETH_MACMIIAR_CR_Div42;
    ETH->MACMIIAR = (uint32_t)tmpreg;
    /* reset phy */
    ETH_WritePHYRegister(PHYAddress, PHY_BCR, PHY_Reset);
    tickstart= rt_tick_get_millisecond();
    do{
        asm("nop");      /* waiting for finish */
    }while((rt_tick_get_millisecond()-tickstart)<1000);


    tickstart= rt_tick_get_millisecond();
    RegValue = 0;
    while( (RegValue&(PHY_Reset)) )
    {
        RegValue = ETH_ReadPHYRegister(PHYAddress, PHY_BCR);
        if((rt_tick_get_millisecond()-tickstart)>10000)
        {
            LOG_E("Error:Wait phy reset timeout!\r\n");
            while(1);
        }
    }

    /* waiting for link up */
    tickstart= rt_tick_get_millisecond();
    RegValue = 0;
    while((RegValue&(PHY_Linked_Status)) == 0)
    {
       RegValue = ETH_ReadPHYRegister(PHYAddress, PHY_BSR);
       if((rt_tick_get_millisecond()-tickstart)>10000)
       {
           LOG_E("Error:Wait phy linking timeout!\r\n");
           while(1);
       }
    }

    /* waiting for auto-negotiation */
    tickstart= rt_tick_get_millisecond();
    RegValue = 0;
    while((RegValue&PHY_AutoNego_Complete) == 0)
    {
        RegValue = ETH_ReadPHYRegister(PHYAddress, PHY_BSR);
        if((rt_tick_get_millisecond()-tickstart)>10000)
        {
            LOG_E("Error:Wait phy auto-negotiation complete timeout!\r\n");
            while(1);
        }
    }

#ifdef USE10BASE_T
    RegValue = ETH_ReadPHYRegister(PHYAddress, PHY_BMCR);
    LOG_D("PHY_BMCR:%d,value:%04x.\n",PHY_BMCR,RegValue);
    if((RegValue & (1<<8)) != (uint32_t)RESET)
    {
      ETH_InitStruct->ETH_Mode = ETH_Mode_FullDuplex;
      ch32v30x_eth_device.ETH_Mode=ETH_Mode_FullDuplex;
      LOG_D("Full-Duplex.\n");
    }
    else
    {
      ETH_InitStruct->ETH_Mode = ETH_Mode_HalfDuplex;
      ch32v30x_eth_device.ETH_Mode=ETH_Mode_HalfDuplex;
      LOG_D("Half-Duplex.\n");
    }
    if(RegValue & (1<<13))
    {
      ETH_InitStruct->ETH_Speed = ETH_Speed_100M;
      ch32v30x_eth_device.ETH_Speed=ETH_Speed_100M;
      /* send link up. */
      eth_device_linkchange(&ch32v30x_eth_device.parent, RT_TRUE);
      LOG_D("Link speed:100M.\n");
    }
    else
    {
      ETH_InitStruct->ETH_Speed = ETH_Speed_10M;
      ch32v30x_eth_device.ETH_Speed=ETH_Speed_10M;
      /* send link up. */
      eth_device_linkchange(&ch32v30x_eth_device.parent, RT_TRUE);
      LOG_D("Link speed:10M.\n");
    }
#endif

#ifdef USE_FAST_MAC
    /* 100M MAC,RMII */
    RegValue = ETH_ReadPHYRegister(PHYAddress, PHY_BMCR);
    LOG_D("PHY_BMCR:%d,value:%04x.\n",PHY_BMCR,RegValue);
    if((RegValue & (1<<8)) != (uint32_t)RESET)
    {
      ETH_InitStruct->ETH_Mode = ETH_Mode_FullDuplex;
      ch32v30x_eth_device.ETH_Mode = ETH_Mode_FullDuplex;
      LOG_D("Full-Duplex.\n");
    }
    else
    {
      ETH_InitStruct->ETH_Mode = ETH_Mode_HalfDuplex;
      ch32v30x_eth_device.ETH_Mode = ETH_Mode_HalfDuplex;
      LOG_D("Half-Duplex.\n");
    }
    if(RegValue & (1<<13))
    {
      ETH_InitStruct->ETH_Speed = ETH_Speed_100M;
      ch32v30x_eth_device.ETH_Speed=ETH_Speed_100M;
      /* send link up. */
      eth_device_linkchange(&ch32v30x_eth_device.parent, RT_TRUE);
      LOG_D("Link speed:100M.\n");
    }
    else
    {
      ETH_InitStruct->ETH_Speed = ETH_Speed_10M;
      ch32v30x_eth_device.ETH_Speed=ETH_Speed_10M;
      /* send link up. */
      eth_device_linkchange(&ch32v30x_eth_device.parent, RT_TRUE);
      LOG_D("Link speed:10M.\n");
    }
#endif

#ifdef USE_GIGA_MAC
    /* GMAC,RGMI */
    ETH_WritePHYRegister(PHYAddress, 31,0x0a43 );
    RegValue = ETH_ReadPHYRegister(PHYAddress, 26);
    if( RegValue & 0x0008 )
    {
        ETH_InitStruct->ETH_Mode     = ETH_Mode_FullDuplex;
        ch32v30x_eth_device.ETH_Mode = ETH_Mode_FullDuplex;
        LOG_D("full duplex.\n");
    }
    else
    {
        ETH_InitStruct->ETH_Mode     = ETH_Mode_HalfDuplex;
        ch32v30x_eth_device.ETH_Mode = ETH_Mode_HalfDuplex;
        LOG_D("half duplex!\n");
    }
    if(( RegValue & 0x0030 ) == 0x0000)
    {
        ETH_InitStruct->ETH_Speed    = ETH_Speed_10M;
        ch32v30x_eth_device.ETH_Speed= ETH_Speed_10M;
        eth_device_linkchange(&ch32v30x_eth_device.parent, RT_TRUE);
        LOG_D("Link speed:10Mbps.\n");
    }
    else if(( RegValue & 0x0030 ) == 0x0010)
    {
        ETH_InitStruct->ETH_Speed    = ETH_Speed_100M;
        ch32v30x_eth_device.ETH_Speed= ETH_Speed_100M;
        eth_device_linkchange(&ch32v30x_eth_device.parent, RT_TRUE);
        LOG_D("Link speed:100Mbps.\n");
    }
    else if(( RegValue & 0x0030 ) == 0x0020)
    {
        ETH_InitStruct->ETH_Speed    = ETH_Speed_1000M;
        ch32v30x_eth_device.ETH_Speed= ETH_Speed_1000M;
        eth_device_linkchange(&ch32v30x_eth_device.parent, RT_TRUE);
        LOG_D("Link speed:1000Mbps.\n");
    }
#endif

    tickstart= rt_tick_get_millisecond();
    do{
        asm("nop");
    }while((rt_tick_get_millisecond()-tickstart)<1000);


    /*  MAC config  */
    /* if use RGMII,should config RGMII clock delay register */
    tmpreg = ETH->MACCR;
    tmpreg &= MACCR_CLEAR_MASK;
    tmpreg |= (uint32_t)(ETH_InitStruct->ETH_Watchdog |
                  ETH_InitStruct->ETH_Jabber |
                  ETH_InitStruct->ETH_InterFrameGap |
                  ETH_InitStruct->ETH_CarrierSense |
                  ETH_InitStruct->ETH_Speed |
                  ETH_InitStruct->ETH_ReceiveOwn |
                  ETH_InitStruct->ETH_LoopbackMode |
                  ETH_InitStruct->ETH_Mode |
                  ETH_InitStruct->ETH_ChecksumOffload |
                  ETH_InitStruct->ETH_RetryTransmission |
                  ETH_InitStruct->ETH_AutomaticPadCRCStrip |
                  ETH_InitStruct->ETH_BackOffLimit |
                  ETH_InitStruct->ETH_DeferralCheck);
    ETH->MACCR = (uint32_t)tmpreg;
#ifdef USE10BASE_T
    /* enable internal pull up resistance,50Î© */
    ETH->MACCR|=ETH_Internal_Pull_Up_Res_Enable;
#endif
    ETH->MACFFR = (uint32_t)(ETH_InitStruct->ETH_ReceiveAll |
                          ETH_InitStruct->ETH_SourceAddrFilter |
                          ETH_InitStruct->ETH_PassControlFrames |
                          ETH_InitStruct->ETH_BroadcastFramesReception |
                          ETH_InitStruct->ETH_DestinationAddrFilter |
                          ETH_InitStruct->ETH_PromiscuousMode |
                          ETH_InitStruct->ETH_MulticastFramesFilter |
                          ETH_InitStruct->ETH_UnicastFramesFilter);
    /* Write to ETHERNET MACHTHR */
    ETH->MACHTHR = (uint32_t)ETH_InitStruct->ETH_HashTableHigh;
    /* Write to ETHERNET MACHTLR */
    ETH->MACHTLR = (uint32_t)ETH_InitStruct->ETH_HashTableLow;
    /* Get the ETHERNET MACFCR value */
    tmpreg = ETH->MACFCR;
    /* Clear xx bits */
    tmpreg &= MACFCR_CLEAR_MASK;

    tmpreg |= (uint32_t)((ETH_InitStruct->ETH_PauseTime << 16) |
                   ETH_InitStruct->ETH_ZeroQuantaPause |
                   ETH_InitStruct->ETH_PauseLowThreshold |
                   ETH_InitStruct->ETH_UnicastPauseFrameDetect |
                   ETH_InitStruct->ETH_ReceiveFlowControl |
                   ETH_InitStruct->ETH_TransmitFlowControl);
    ETH->MACFCR = (uint32_t)tmpreg;

    ETH->MACVLANTR = (uint32_t)(ETH_InitStruct->ETH_VLANTagComparison |
                             ETH_InitStruct->ETH_VLANTagIdentifier);

    tmpreg = ETH->DMAOMR;
    /* Clear xx bits */
    tmpreg &= DMAOMR_CLEAR_MASK;

    tmpreg |= (uint32_t)(ETH_InitStruct->ETH_DropTCPIPChecksumErrorFrame |
                  ETH_InitStruct->ETH_ReceiveStoreForward |
                  ETH_InitStruct->ETH_FlushReceivedFrame |
                  ETH_InitStruct->ETH_TransmitStoreForward |
                  ETH_InitStruct->ETH_TransmitThresholdControl |
                  ETH_InitStruct->ETH_ForwardErrorFrames |
                  ETH_InitStruct->ETH_ForwardUndersizedGoodFrames |
                  ETH_InitStruct->ETH_ReceiveThresholdControl |
                  ETH_InitStruct->ETH_SecondFrameOperate);
    ETH->DMAOMR = (uint32_t)tmpreg;

    ETH->DMABMR = (uint32_t)(ETH_InitStruct->ETH_AddressAlignedBeats |
                          ETH_InitStruct->ETH_FixedBurst |
                          ETH_InitStruct->ETH_RxDMABurstLength | /* !! if 4xPBL is selected for Tx or Rx it is applied for the other */
                          ETH_InitStruct->ETH_TxDMABurstLength |
                         (ETH_InitStruct->ETH_DescriptorSkipLength << 2) |
                          ETH_InitStruct->ETH_DMAArbitration |
                          ETH_DMABMR_USP);

    return ETH_SUCCESS;
}

/* eth initialization function */
static rt_err_t rt_ch32_eth_init(rt_device_t dev)
{
    ETH_InitTypeDef ETH_InitStructure={0};
    RCC_PLL3Cmd(DISABLE);
    RCC_PREDIV2Config(RCC_PREDIV2_Div2);
    RCC_PLL3Config(RCC_PLL3Mul_15);
    RCC_PLL3Cmd(ENABLE);
    while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLL3RDY));
    LOG_D("PLL3 Init Finish\r\n");
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ETH_MAC|RCC_AHBPeriph_ETH_MAC_Tx|RCC_AHBPeriph_ETH_MAC_Rx,ENABLE);
#ifdef USE10BASE_T
    /* Enable internal 10BASE-T PHY*/
    EXTEN->EXTEN_CTR |=EXTEN_ETH_10M_EN;
#endif
#ifdef USE_GIGA_MAC
    /* Enable 1G MAC*/
    EXTEN->EXTEN_CTR |= EXTEN_ETH_RGMII_SEL;
    /* mac clock use external 125MHz,input from PB1 */
    RCC_ETH1GCLKConfig(RCC_ETH1GCLKSource_PB1_IN);
    RCC_ETH1G_125Mcmd(ENABLE);
    /*  Enable RGMII GPIO */
    GETH_pin_init();
#endif

#ifdef USE_FAST_MAC
    /*  Enable MII or RMII GPIO */
    FETH_pin_init();
#endif
    /* Reset ETHERNET on AHB Bus */
    ETH_DeInit();
    /* Software reset */
    ETH_SoftwareReset();
    /* Wait for software reset */
    while(ETH->DMABMR & ETH_DMABMR_SR);
    LOG_D("ETH RST Finish\r\n");

    ETH_StructInit(&ETH_InitStructure);
    ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;
    ETH_InitStructure.ETH_Speed = ETH_Speed_1000M;
    ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable  ;
    ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
    ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable;
    ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;
    ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Enable;
    ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;
    ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Enable;
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
    ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Enable;
    ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Enable;
    ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Disable;
    ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;
    ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;
    ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;
    ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;
    ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_2_1;
    /* Configure Ethernet */
    ETH_Init(&ETH_InitStructure, PHY_ADDRESS);
    /* Enable the Ethernet Rx Interrupt */
    ETH_DMAITConfig(ETH_DMA_IT_NIS
                    | ETH_DMA_IT_R
                    | ETH_DMA_IT_T
                    ,ENABLE);
    NVIC_SetPriority(ETH_IRQn,1<<4);
    NVIC_EnableIRQ(ETH_IRQn);
    ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
    ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);
#ifdef USE_GIGA_MAC
    RGMII_TXC_Delay(0,2);
#endif
    ETH_Start();
    return RT_EOK;
}

static rt_err_t rt_ch32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("eth open\r\n");
    return RT_EOK;
}

static rt_err_t rt_ch32_eth_close(rt_device_t dev)
{
    LOG_D("eth close\r\n");
    return RT_EOK;
}

static rt_ssize_t rt_ch32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("eth read\r\n");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_ch32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("eth write\r\n");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}


static rt_err_t rt_ch32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, ch32v30x_eth_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

rt_err_t rt_ch32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t ret = RT_ERROR;
    struct pbuf *q;
    uint8_t *buffer = (uint8_t *)(DMATxDescToSet->Buffer1Addr);
    uint8_t *pdata;
    uint32_t framelength = 0,len=0;
    /* copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* Is this buffer available? If not, goto error */
        if ((DMATxDescToSet->Status & ETH_DMATxDesc_OWN) != (uint32_t)RESET)
        {
            LOG_E("buffer not valid\r\n");
            ret = ERR_USE;
            goto Tx_error;
        }

        pdata = q->payload;
        len = q->len;
        framelength += len;
        rt_memcpy(buffer,pdata,len);
        buffer += len;
    }

#ifdef ETH_TX_DUMP
    dump_hex(buffer, p->tot_len);
#endif

    DMATxDescToSet->ControlBufferSize = (framelength & ETH_DMATxDesc_TBS1);
    DMATxDescToSet->Status |= ETH_DMATxDesc_LS | ETH_DMATxDesc_FS;
    DMATxDescToSet->Status |= ETH_DMATxDesc_OWN;
    ret = ERR_OK;

    Tx_error:
    /* When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission */
    if ((ETH->DMASR & ETH_DMASR_TBUS) != (uint32_t)RESET)
    {
        /* Clear TUS ETHERNET DMA flag */
        ETH->DMASR = ETH_DMASR_TUS;
        /* Resume DMA transmission*/
        ETH->DMATPDR = 0;
    }

    DMATxDescToSet = (ETH_DMADESCTypeDef*) (DMATxDescToSet->Buffer2NextDescAddr);
    return ret;
}


volatile FrameTypeDef frame;
struct pbuf *rt_ch32_eth_rx(rt_device_t dev)
{
    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    uint16_t len = 0;
    uint8_t *buffer;
    uint8_t *pdata;

    if(!frame.length)
    {
        return NULL;
    }
    len=frame.length;
    frame.length=0;
    buffer=(uint8_t *)frame.buffer;
    if (len > 0)
    {
        /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }
#ifdef ETH_RX_DUMP
    dump_hex(buffer, p->tot_len);
#endif
    if (p != NULL)
    {
        for (q = p; q != NULL; q = q->next)
        {
            pdata = q->payload;
            rt_memcpy(pdata,buffer,q->len);
            pdata += (q->len);
            buffer += (q->len);
        }
     }
    else
    {
        LOG_E("p=null\r\n");
    }
    return p;
 }

/* interrupt service routine */
void ETH_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void ETH_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_err_t result;
    rt_interrupt_enter();
    if(ETH->DMASR&ETH_DMA_IT_R)
    {
        ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
        frame = ETH_RxPkt_ChainMode();
        result = eth_device_ready(&(ch32v30x_eth_device.parent));
        if (result != RT_EOK)
            rt_kprintf("RxCpltCallback err = %d\r\n", result);
    }
    if(ETH->DMASR&ETH_DMA_IT_T)
    {
        ETH_DMAClearITPendingBit(ETH_DMA_IT_T);
    }
    ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}


/* Register the EMAC device */
static int rt_hw_ch32_eth_init(void)
{
    rt_err_t state = RT_EOK;
    /* 84-c2-e4 WCH. */
    ch32v30x_eth_device.dev_addr[0] = 0x84;
    ch32v30x_eth_device.dev_addr[1] = 0xc2;
    ch32v30x_eth_device.dev_addr[2] = 0xe4;
    /* generate MAC (only for test). */
    ch32v30x_eth_device.dev_addr[3] = 0x1;
    ch32v30x_eth_device.dev_addr[4] = 0x2;
    ch32v30x_eth_device.dev_addr[5] = 0x3;

    ch32v30x_eth_device.parent.parent.init       = rt_ch32_eth_init;
    ch32v30x_eth_device.parent.parent.open       = rt_ch32_eth_open;
    ch32v30x_eth_device.parent.parent.close      = rt_ch32_eth_close;
    ch32v30x_eth_device.parent.parent.read       = rt_ch32_eth_read;
    ch32v30x_eth_device.parent.parent.write      = rt_ch32_eth_write;
    ch32v30x_eth_device.parent.parent.control    = rt_ch32_eth_control;
    ch32v30x_eth_device.parent.parent.user_data  = RT_NULL;

    ch32v30x_eth_device.parent.eth_rx     = rt_ch32_eth_rx;
    ch32v30x_eth_device.parent.eth_tx     = rt_ch32_eth_tx;

    /* register eth device */
    state = eth_device_init(&(ch32v30x_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        LOG_D("emac device init success");
    }
    else
    {
        LOG_E("emac device init faild: %d\r\n", state);
        state = -RT_ERROR;
    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_ch32_eth_init);

#endif /* BSP_USING_ETH */
