/*
* Copyright (c) 2006-2024, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author        Notes
* 2024-5-25       IceBear003    the first version
*/

#include "board.h"
#include "drv_eth.h"
#include <netif/ethernetif.h>

#ifdef BSP_USING_ETH

#define LOG_TAG "drv.eth"
#include "drv_log.h"

static ETH_DMADESCTypeDef *dma_rx_desc_tab, *dma_tx_desc_tab;
static rt_uint8_t *rx_buffer, *tx_buffer;

static struct eth_device eth_device;

static rt_uint8_t eth_mac_addr[] = { 0x84, 0xc2, 0xe4, 0x01, 0x02, 0x03 };

uint32_t eth_reg_init(ETH_InitTypeDef* ETH_InitStruct, uint16_t phy_address)
{
    uint32_t tmpreg = 0;

    tmpreg = ETH->MACMIIAR;
    tmpreg &= MACMIIAR_CR_MASK;
    tmpreg |= (uint32_t)ETH_MACMIIAR_CR_Div42;
    ETH->MACMIIAR = (uint32_t)tmpreg;

    tmpreg = ETH->MACCR;
    tmpreg &= MACCR_CLEAR_MASK;
    tmpreg |= (uint32_t)(ETH_InitStruct->ETH_AutoNegotiation |
                  ETH_InitStruct->ETH_Watchdog |
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
    ETH->MACFFR = (uint32_t)(ETH_InitStruct->ETH_ReceiveAll |
                          ETH_InitStruct->ETH_SourceAddrFilter |
                          ETH_InitStruct->ETH_PassControlFrames |
                          ETH_InitStruct->ETH_BroadcastFramesReception |
                          ETH_InitStruct->ETH_DestinationAddrFilter |
                          ETH_InitStruct->ETH_PromiscuousMode |
                          ETH_InitStruct->ETH_MulticastFramesFilter |
                          ETH_InitStruct->ETH_UnicastFramesFilter);

    ETH->MACHTHR = (uint32_t)ETH_InitStruct->ETH_HashTableHigh;
    ETH->MACHTLR = (uint32_t)ETH_InitStruct->ETH_HashTableLow;

    tmpreg = ETH->MACFCR;
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

    ETH_WritePHYRegister(phy_address, PHY_BCR, PHY_Reset);
    return ETH_SUCCESS;
}

static rt_err_t eth_init(rt_device_t dev)
{
    //Set ETH Clock
    RCC_PLL3Cmd(DISABLE);
    RCC_PREDIV2Config(RCC_PREDIV2_Div2);
    RCC_PLL3Config(RCC_PLL3Mul_15);
    RCC_PLL3Cmd(ENABLE);
    while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLL3RDY));

    //Enable ETH MAC Clock
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ETH_MAC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ETH_MAC_Tx, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ETH_MAC_Rx, ENABLE);

    //ETH Reset
    ETH_DeInit();
    ETH_SoftwareReset();
    while(ETH->DMABMR & ETH_DMABMR_SR);

    /* ETH Config */
    ETH_InitTypeDef ETH_InitStructure;
    ETH_StructInit(&ETH_InitStructure);
    ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;
    ETH_InitStructure.ETH_Speed = ETH_Speed_100M;
    #if HARDWARE_CHECKSUM_CONFIG
    ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable;
    #endif
    ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;
    ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
    ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable;
    ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;
    ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;
    ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;
    ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;
    ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;
    ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;
    ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable;
    ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;
    ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;
    ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Enable;
    ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Enable;
    ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Disable;

    eth_reg_init( &ETH_InitStructure, 1);

    ETH->MACA0HR = (uint32_t)((eth_mac_addr[5]<<8) | eth_mac_addr[4]);
    ETH->MACA0LR = (uint32_t)(eth_mac_addr[0] | (eth_mac_addr[1]<<8) | (eth_mac_addr[2]<<16) | (eth_mac_addr[3]<<24));

    ETH->MMCTIMR = ETH_MMCTIMR_TGFM;
    ETH->MMCRIMR = ETH_MMCRIMR_RGUFM | ETH_MMCRIMR_RFCEM;

    ETH_DMAITConfig(ETH_DMA_IT_NIS | ETH_DMA_IT_R | ETH_DMA_IT_T | ETH_DMA_IT_AIS | ETH_DMA_IT_RBU, ENABLE);

    ETH_DMARxDescChainInit(dma_rx_desc_tab, rx_buffer, ETH_RX_BUF_COUNT);
    ETH_DMARxDescChainInit(dma_tx_desc_tab, tx_buffer, ETH_TX_BUF_COUNT);

    NVIC_SetPriority(ETH_IRQn, 1 << 4);
    NVIC_EnableIRQ(ETH_IRQn);

    return RT_EOK;
}

//RTT函数实现
struct pbuf *eth_rx(rt_device_t dev)
{
    ETH_DMADESCTypeDef *dma_rx_desc = (ETH_DMADESCTypeDef *)ETH->DMARDLAR;
    uint8_t *ppkt = (uint8_t *)(dma_rx_desc->Buffer1Addr);
    uint8_t *buffer = (uint8_t *)(dma_rx_desc->Buffer1Addr);

    uint32_t bytes_rx = 0;
    uint32_t bytes_left = 0;
    uint32_t payload_bytes_rx = 0;

    uint32_t len = ETH_HandleRxPkt(ppkt);

    struct pbuf *p = NULL;
    struct pbuf *q = NULL;

    if(len > 0)
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

    if(p != NULL)
    {
        dma_rx_desc->Status |= ETH_DMARxDesc_OWN;
        for(q = p; q != NULL; q = q->next)
        {
            bytes_left = q->len;
            payload_bytes_rx = 0;
            while((bytes_rx + bytes_left) > ETH_MAX_PACKET_SIZE)
            {
                rt_memcpy((uint8_t *)(uint8_t *)q->payload + payload_bytes_rx,
                         (uint8_t *)(uint8_t *)buffer + bytes_rx,
                         (ETH_MAX_PACKET_SIZE - bytes_rx));

                dma_rx_desc = (ETH_DMADESCTypeDef *)(dma_rx_desc->Buffer2NextDescAddr);
                dma_rx_desc->Status |= ETH_DMARxDesc_OWN;
                buffer = (uint8_t *)(dma_rx_desc->Buffer1Addr);

                bytes_rx = 0;
                bytes_left -= (ETH_MAX_PACKET_SIZE - bytes_rx);
                payload_bytes_rx += (ETH_MAX_PACKET_SIZE - bytes_rx);
            }

            rt_memcpy((uint8_t *)(uint8_t *)q->payload + payload_bytes_rx,
                     (uint8_t *)(uint8_t *)buffer + bytes_rx,
                     bytes_left);

            bytes_rx += bytes_left;
        }
    }

    if ((ETH->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
    {
        ETH->DMASR = ETH_DMASR_RBUS;
        ETH->DMARPDR = 0;
    }

    return p;
}

rt_err_t eth_tx(rt_device_t dev, struct pbuf* p)
{
    ETH_DMADESCTypeDef *dma_tx_desc = (ETH_DMADESCTypeDef *)ETH->DMATDLAR;
    uint8_t *ppkt = (uint8_t *)(dma_tx_desc->Buffer1Addr);
    uint8_t *buffer = (uint8_t *)(dma_tx_desc->Buffer1Addr);

    uint32_t frame_length = 0;
    uint32_t bytes_tx = 0; //已经传输的字节数
    uint32_t bytes_left = 0;  //lwIP数据包剩余字节数
    uint32_t payload_bytes_tx = 0;  //结点中已经传输的字节数

    uint32_t state = 0;

    struct pbuf *q;
    for(q = p; q != NULL; q = q->next)
    {
        if((dma_tx_desc->Status & ETH_DMATxDesc_OWN) != 0)
            goto error;

        bytes_left = q->len;
        payload_bytes_tx = 0;

        while((bytes_tx + bytes_left) > ETH_MAX_PACKET_SIZE)
        {
            rt_memcpy((uint8_t *)(uint8_t *)buffer + bytes_tx,
                     (uint8_t *)(uint8_t *)q->payload + payload_bytes_tx,
                     ETH_MAX_PACKET_SIZE - bytes_left);

            dma_tx_desc = (ETH_DMADESCTypeDef *)(dma_tx_desc->Buffer2NextDescAddr);
            if((dma_tx_desc->Status & ETH_DMATxDesc_OWN) != 0)
                goto error;
            buffer = (uint8_t *)(dma_tx_desc->Buffer1Addr);

            bytes_tx = 0;
            bytes_left -= ETH_MAX_PACKET_SIZE - bytes_left;
            payload_bytes_tx += ETH_MAX_PACKET_SIZE - bytes_left;
            frame_length += ETH_MAX_PACKET_SIZE - bytes_left;
        }

        rt_memcpy((uint8_t *)(uint8_t *)buffer + bytes_tx,
                 (uint8_t *)(uint8_t *)q->payload + payload_bytes_tx,
                 bytes_left);

        bytes_tx += bytes_left;
        frame_length += bytes_left;
    }

    state = ETH_HandleTxPkt(ppkt,frame_length);
    if(state == ETH_ERROR)
        return -RT_ERROR;

    return RT_EOK;

error:

    if ((ETH->DMASR & ETH_DMASR_TUS) != (uint32_t)RESET)
    {
        ETH->DMASR = ETH_DMASR_TUS;
        ETH->DMATPDR = 0;
    }

    return -RT_ERROR;
}

int read_eth_link_status()
{
    ETH->MACMIIAR |= 0x00000800;
    ETH->MACMIIAR &= 0xFFFFFFFD;

    if ((ETH->MACMIIDR & ETH_MACMIIDR_MD & 0x04) != 0)
        return 1;

    return 0;
}

void ETH_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void ETH_IRQHandler(void)
{
    rt_interrupt_enter();

    uint32_t int_sta;
    int_sta = ETH->DMASR;
    if (int_sta & ETH_DMA_IT_AIS)
    {
        if (int_sta & ETH_DMA_IT_RBU)
        {
            ((ETH_DMADESCTypeDef *)(((ETH_DMADESCTypeDef *)(ETH->DMACHRDR))->Buffer2NextDescAddr))->Status = ETH_DMARxDesc_OWN;
            ETH->DMARPDR = 0;
            ETH_DMAClearITPendingBit(ETH_DMA_IT_RBU);
        }
        ETH_DMAClearITPendingBit(ETH_DMA_IT_AIS);
    }

    if( int_sta & ETH_DMA_IT_NIS )
    {
        if(int_sta & ETH_DMA_IT_R)
            ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
        if(int_sta & ETH_DMA_IT_T)
            ETH_DMAClearITPendingBit(ETH_DMA_IT_T);
        if(int_sta & ETH_DMA_IT_PHYLINK)
        {
            ETH_DMAClearITPendingBit(ETH_DMA_IT_PHYLINK);
            if(read_eth_link_status())
            {
                eth_device_linkchange(&eth_device, RT_TRUE);
            }
            else
            {
                eth_device_linkchange(&eth_device, RT_FALSE);
            }
        }
        ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
    }

    rt_interrupt_leave();
}

int rt_hw_eth_init(void)
{
    rt_err_t state = RT_EOK;

    //分配内存
    rx_buffer = (rt_uint8_t *)rt_calloc(ETH_RX_BUF_COUNT, ETH_MAX_PACKET_SIZE);
    if(rx_buffer == NULL)
    {
        state = -RT_ENOMEM;
        goto exit;
    }
    dma_rx_desc_tab = (ETH_DMADESCTypeDef *)rt_calloc(ETH_RX_BUF_COUNT, sizeof(ETH_DMADESCTypeDef));
    if(dma_rx_desc_tab == NULL)
    {
        state = -RT_ENOMEM;
        goto exit;
    }
    tx_buffer = (rt_uint8_t *)rt_calloc(ETH_TX_BUF_COUNT, ETH_MAX_PACKET_SIZE);
    if(tx_buffer == NULL)
    {
        state = -RT_ENOMEM;
        goto exit;
    }
    dma_tx_desc_tab = (ETH_DMADESCTypeDef *)rt_calloc(ETH_TX_BUF_COUNT, sizeof(ETH_DMADESCTypeDef));
    if(dma_tx_desc_tab == NULL)
    {
        state = -RT_ENOMEM;
        goto exit;
    }

    eth_device.parent.init = eth_init;
    eth_device.eth_rx = eth_rx;
    eth_device.eth_tx = eth_tx;

    //没有意义，无需实现
    eth_device.parent.open = RT_NULL;
    eth_device.parent.close = RT_NULL;
    eth_device.parent.read = RT_NULL;
    eth_device.parent.write = RT_NULL;
    eth_device.parent.control = RT_NULL;
    eth_device.parent.user_data = RT_NULL;

    state = eth_device_init(&(eth_device), "e0");

exit:
    //释放已经分配的内存
    if(state != RT_EOK)
    {
        LOG_E("emac device init faild: %d", state);
        if(rx_buffer) rt_free(rx_buffer);
        if(dma_rx_desc_tab) rt_free(dma_rx_desc_tab);
        if(tx_buffer) rt_free(tx_buffer);
        if(dma_tx_desc_tab) rt_free(dma_tx_desc_tab);
    }
}

#endif //BSP_USING_ETH