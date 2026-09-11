/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     SummerGift   first version
 * 2018-12-25     zylx         fix some bugs
 * 2019-06-10     SummerGift   optimize PHY state detection process
 * 2019-09-03     xiaofan      optimize link change detection process
 * 2020-07-17     wanghaijing  support h7
 * 2020-11-30     wanghaijing  add phy reset
 * 2026-08-30     CYFS         merge H750 driver and use the new HAL ETH API
 */

#include "drv_config.h"
#include "drv_eth.h"
#include <netif/ethernetif.h>
#include <lwipopts.h>

/*
 * Emac driver uses CubeMX tool to generate emac and PHY configuration.
 * The configuration files can be found in the CubeMX_Config folder.
 */

/* debug option */
/* #define ETH_RX_DUMP */
/* #define ETH_TX_DUMP */
/* #define DRV_DEBUG */
#define LOG_TAG             "drv.emac"
#include <drv_log.h>

#define MAX_ADDR_LEN        6U
#define ETH_RX_BUFFER_CNT   (ETH_RX_DESC_CNT * 2U)
#define ETH_CACHE_LINE_SIZE 32U
#define PHY_INVALID_ADDR    0xFFU
#define PHY_STATE_UNKNOWN   0xFFU

#if defined(ETH_DMACSR_AIS)
#define ETH_DMA_ABNORMAL_SUMMARY_FLAG ETH_DMACSR_AIS
#elif defined(ETH_DMASR_AIS)
#define ETH_DMA_ABNORMAL_SUMMARY_FLAG ETH_DMASR_AIS
#else
#define ETH_DMA_ABNORMAL_SUMMARY_FLAG 0U
#endif

struct rt_stm32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
    struct rt_mutex mac_lock;

    /* interface address info, hw address */
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    rt_uint32_t ETH_Speed;
    /* ETH_Duplex_Mode */
    rt_uint32_t ETH_Mode;
    rt_uint8_t phy_state;
    rt_bool_t mac_started;
};

struct rt_stm32_eth_rx_buffer
{
    rt_uint16_t length;
    rt_bool_t allocated;
    struct rt_stm32_eth_rx_buffer *next;
};

static ETH_HandleTypeDef EthHandle;
static ETH_TxPacketConfigTypeDef TxConfig;
static struct rt_stm32_eth stm32_eth_device;
static struct rt_stm32_eth_rx_buffer Rx_Buff_Info[ETH_RX_BUFFER_CNT];
static ETH_DMADescTypeDef *DMARxDscrTab;
static ETH_DMADescTypeDef *DMATxDscrTab;
static rt_uint8_t *Rx_Buff;
static rt_uint32_t rx_alloc_index;
static rt_uint8_t phy_addr = PHY_INVALID_ADDR;

#ifdef PHY_USING_INTERRUPT_MODE
static struct rt_semaphore phy_link_sem;
#endif

#ifdef ETH_RESET_PIN
static rt_base_t reset_pin = -1;
#endif

/* ART-Pi places all ETH DMA-owned memory in its non-cacheable D2 SRAM region. */
#ifdef BSP_USING_ETH_H750
#if defined(__ICCARM__)
#pragma location=0x30040000
static ETH_DMADescTypeDef DMARxDscrTab_Storage[ETH_RX_DESC_CNT];
#pragma location=0x30040060
static ETH_DMADescTypeDef DMATxDscrTab_Storage[ETH_TX_DESC_CNT];
#pragma location=0x30040200
static rt_uint8_t Rx_Buff_Storage[ETH_RX_BUFFER_CNT * ETH_MAX_PACKET_SIZE];
#elif defined(__CC_ARM)
static __attribute__((at(0x30040000))) ETH_DMADescTypeDef DMARxDscrTab_Storage[ETH_RX_DESC_CNT];
static __attribute__((at(0x30040060))) ETH_DMADescTypeDef DMATxDscrTab_Storage[ETH_TX_DESC_CNT];
static __attribute__((at(0x30040200))) rt_uint8_t Rx_Buff_Storage[ETH_RX_BUFFER_CNT * ETH_MAX_PACKET_SIZE];
#elif defined(__GNUC__)
static ETH_DMADescTypeDef DMARxDscrTab_Storage[ETH_RX_DESC_CNT]
        __attribute__((section(".RxDecripSection"), aligned(32)));
static ETH_DMADescTypeDef DMATxDscrTab_Storage[ETH_TX_DESC_CNT]
        __attribute__((section(".TxDecripSection"), aligned(32)));
static rt_uint8_t Rx_Buff_Storage[ETH_RX_BUFFER_CNT * ETH_MAX_PACKET_SIZE]
        __attribute__((section(".RxArraySection"), aligned(32)));
#else
static ETH_DMADescTypeDef DMARxDscrTab_Storage[ETH_RX_DESC_CNT] __ALIGNED(32);
static ETH_DMADescTypeDef DMATxDscrTab_Storage[ETH_TX_DESC_CNT] __ALIGNED(32);
static rt_uint8_t Rx_Buff_Storage[ETH_RX_BUFFER_CNT * ETH_MAX_PACKET_SIZE] __ALIGNED(32);
#endif
#endif /* BSP_USING_ETH_H750 */

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127U - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    const unsigned char *buf = (const unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                rt_kprintf("%02X ", buf[i + j]);
            }
            else
            {
                rt_kprintf("   ");
            }
        }

        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }

        rt_kprintf("\n");
    }
}
#endif

rt_weak void phy_reset(void)
{
}

static void phy_hardware_reset(void)
{
#ifdef ETH_RESET_PIN
    if (reset_pin >= 0)
    {
        rt_pin_write(reset_pin, PIN_LOW);
        rt_thread_mdelay(50);
        rt_pin_write(reset_pin, PIN_HIGH);
        return;
    }
#endif

    phy_reset();
}

static rt_uint8_t *eth_rx_buffer_at(rt_uint32_t index)
{
    return Rx_Buff + (index * ETH_MAX_PACKET_SIZE);
}

void HAL_ETH_RxAllocateCallback(uint8_t **buff)
{
    rt_uint32_t index;

    *buff = RT_NULL;

    for (index = 0; index < ETH_RX_BUFFER_CNT; index++)
    {
        rt_uint32_t current = (rx_alloc_index + index) % ETH_RX_BUFFER_CNT;

        if (Rx_Buff_Info[current].allocated == RT_FALSE)
        {
            Rx_Buff_Info[current].allocated = RT_TRUE;
            Rx_Buff_Info[current].length = 0;
            Rx_Buff_Info[current].next = RT_NULL;
            rx_alloc_index = (current + 1U) % ETH_RX_BUFFER_CNT;
            *buff = eth_rx_buffer_at(current);
            break;
        }
    }
}

void HAL_ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t length)
{
    struct rt_stm32_eth_rx_buffer *rx_buffer = RT_NULL;
    rt_uint32_t index;

    for (index = 0; index < ETH_RX_BUFFER_CNT; index++)
    {
        if (buff == eth_rx_buffer_at(index))
        {
            rx_buffer = &Rx_Buff_Info[index];
            break;
        }
    }

    if (rx_buffer == RT_NULL)
    {
        return;
    }

    rx_buffer->length = length;
    rx_buffer->next = RT_NULL;

    if (*pStart == RT_NULL)
    {
        *pStart = rx_buffer;
    }
    else
    {
        ((struct rt_stm32_eth_rx_buffer *)(*pEnd))->next = rx_buffer;
    }

    *pEnd = rx_buffer;
}

static void eth_rx_release_buffers(struct rt_stm32_eth_rx_buffer *rx_buffer)
{
    while (rx_buffer != RT_NULL)
    {
        struct rt_stm32_eth_rx_buffer *next = rx_buffer->next;

        rx_buffer->length = 0;
        rx_buffer->next = RT_NULL;
        rx_buffer->allocated = RT_FALSE;
        rx_buffer = next;
    }
}

static rt_err_t eth_rx_copy(struct pbuf *p, struct rt_stm32_eth_rx_buffer *rx_buffer)
{
    struct pbuf *q = p;
    rt_size_t q_offset = 0;

    while (rx_buffer != RT_NULL)
    {
        rt_uint32_t index = (rt_uint32_t)(rx_buffer - Rx_Buff_Info);
        rt_size_t rx_offset = 0;

        while (rx_offset < rx_buffer->length)
        {
            rt_size_t copy_length;
            rt_size_t rx_remaining;
            rt_size_t q_remaining;

            while ((q != RT_NULL) && (q_offset == q->len))
            {
                q = q->next;
                q_offset = 0;
            }

            if (q == RT_NULL)
            {
                return -RT_ERROR;
            }

            rx_remaining = (rt_size_t)rx_buffer->length - rx_offset;
            q_remaining = (rt_size_t)q->len - q_offset;
            copy_length = rx_remaining < q_remaining ? rx_remaining : q_remaining;
            rt_memcpy((rt_uint8_t *)q->payload + q_offset,
                      eth_rx_buffer_at(index) + rx_offset, copy_length);
            rx_offset += copy_length;
            q_offset += copy_length;
        }

        rx_buffer = rx_buffer->next;
    }

    return RT_EOK;
}

static void eth_clean_cache(const void *buffer, rt_size_t length)
{
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    rt_uintptr_t start;
    rt_uintptr_t end;

    if ((SCB->CCR & SCB_CCR_DC_Msk) == 0U)
    {
        return;
    }

    start = RT_ALIGN_DOWN((rt_uintptr_t)buffer, ETH_CACHE_LINE_SIZE);
    end = RT_ALIGN((rt_uintptr_t)buffer + length, ETH_CACHE_LINE_SIZE);
    SCB_CleanDCache_by_Addr((uint32_t *)start, (int32_t)(end - start));
#else
    RT_UNUSED(buffer);
    RT_UNUSED(length);
#endif
}

static void eth_invalidate_cache(const void *buffer, rt_size_t length)
{
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    rt_uintptr_t start;
    rt_uintptr_t end;

    if ((SCB->CCR & SCB_CCR_DC_Msk) == 0U)
    {
        return;
    }

    start = RT_ALIGN_DOWN((rt_uintptr_t)buffer, ETH_CACHE_LINE_SIZE);
    end = RT_ALIGN((rt_uintptr_t)buffer + length, ETH_CACHE_LINE_SIZE);
    SCB_InvalidateDCache_by_Addr((uint32_t *)start, (int32_t)(end - start));
#else
    RT_UNUSED(buffer);
    RT_UNUSED(length);
#endif
}

static rt_err_t phy_find(void)
{
    uint32_t address;

    for (address = 0; address <= 0x1FU; address++)
    {
        uint32_t id = 0xFFFFU;

        if (HAL_ETH_ReadPHYRegister(&EthHandle, address, PHY_ID1_REG, &id) != HAL_OK)
        {
            continue;
        }

#ifdef PHY_USING_YT8512C
        if (id != 0xFFFFU)
#else
        if ((id != 0xFFFFU) && (id != 0x0000U))
#endif
        {
            phy_addr = (rt_uint8_t)address;
            LOG_D("Found a phy, address:0x%02X", phy_addr);
            return RT_EOK;
        }
    }

    LOG_E("No PHY device was detected, please check hardware!");
    return -RT_ERROR;
}

static rt_err_t phy_start_auto_negotiation(void)
{
    uint32_t control;
    uint32_t timeout;

    if (HAL_ETH_WritePHYRegister(&EthHandle, phy_addr, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK) != HAL_OK)
    {
        return -RT_ERROR;
    }

    for (timeout = 0; timeout < 500U; timeout++)
    {
        if (HAL_ETH_ReadPHYRegister(&EthHandle, phy_addr, PHY_BASIC_CONTROL_REG, &control) != HAL_OK)
        {
            return -RT_ERROR;
        }

        if ((control & PHY_RESET_MASK) == 0U)
        {
            break;
        }

        rt_thread_mdelay(1);
    }

    if (timeout == 500U)
    {
        return -RT_ETIMEOUT;
    }

    control |= PHY_AUTO_NEGOTIATION_MASK;
    if (HAL_ETH_WritePHYRegister(&EthHandle, phy_addr, PHY_BASIC_CONTROL_REG, control) != HAL_OK)
    {
        return -RT_ERROR;
    }

    rt_thread_mdelay(2000);
    return RT_EOK;
}

/* EMAC initialization function */
static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{
    rt_err_t status;

    RT_UNUSED(dev);

#ifdef BSP_USING_ETH_H750
    __HAL_RCC_D2SRAM3_CLK_ENABLE();
#endif

    phy_hardware_reset();

    EthHandle.Instance = ETH;
    EthHandle.Init.MACAddr = (rt_uint8_t *)&stm32_eth_device.dev_addr[0];
    EthHandle.Init.MediaInterface = HAL_ETH_RMII_MODE;
    EthHandle.Init.TxDesc = DMATxDscrTab;
    EthHandle.Init.RxDesc = DMARxDscrTab;
    EthHandle.Init.RxBuffLen = ETH_MAX_PACKET_SIZE;

    HAL_ETH_DeInit(&EthHandle);
    rt_memset(Rx_Buff_Info, 0, sizeof(Rx_Buff_Info));
    rx_alloc_index = 0;
    phy_addr = PHY_INVALID_ADDR;
    stm32_eth_device.phy_state = PHY_STATE_UNKNOWN;
    stm32_eth_device.mac_started = RT_FALSE;

    if (HAL_ETH_Init(&EthHandle) != HAL_OK)
    {
        LOG_E("eth hardware init failed");
        return -RT_ERROR;
    }

    rt_memset(&TxConfig, 0, sizeof(TxConfig));
    TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
#ifdef RT_LWIP_USING_HW_CHECKSUM
    TxConfig.Attributes |= ETH_TX_PACKETS_FEATURES_CSUM;
    TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
#else
    TxConfig.ChecksumCtrl = ETH_CHECKSUM_DISABLE;
#endif

    HAL_ETH_SetMDIOClockRange(&EthHandle);

    status = phy_find();
    if (status != RT_EOK)
    {
        return status;
    }

    status = phy_start_auto_negotiation();
    if (status != RT_EOK)
    {
        LOG_E("PHY auto negotiation failed: %d", status);
        return status;
    }

    HAL_NVIC_EnableIRQ(ETH_IRQn);

    LOG_D("eth hardware init success");
    return RT_EOK;
}

static rt_err_t rt_stm32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_UNUSED(dev);
    RT_UNUSED(oflag);
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_stm32_eth_close(rt_device_t dev)
{
    RT_UNUSED(dev);
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_stm32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_UNUSED(dev);
    RT_UNUSED(pos);
    RT_UNUSED(buffer);
    RT_UNUSED(size);
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_stm32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_UNUSED(dev);
    RT_UNUSED(pos);
    RT_UNUSED(buffer);
    RT_UNUSED(size);
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_stm32_eth_control(rt_device_t dev, int cmd, void *args)
{
    RT_UNUSED(dev);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args != RT_NULL)
        {
            rt_memcpy(args, stm32_eth_device.dev_addr, MAX_ADDR_LEN);
        }
        else
        {
            return -RT_ERROR;
        }
        break;

    default:
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit data */
rt_err_t rt_stm32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    HAL_StatusTypeDef state;
    ETH_BufferTypeDef tx_buffer[ETH_TX_DESC_CNT];
    struct pbuf *q;
    rt_uint32_t index = 0;
    rt_uint32_t frame_length = 0;

    RT_UNUSED(dev);

    if (!stm32_eth_device.parent.link_status)
    {
        LOG_D("skip transmit: link down");
        return ERR_IF;
    }

    rt_memset(tx_buffer, 0, sizeof(tx_buffer));

    for (q = p; q != RT_NULL; q = q->next)
    {
        if (index >= ETH_TX_DESC_CNT)
        {
            return ERR_IF;
        }

        tx_buffer[index].buffer = q->payload;
        tx_buffer[index].len = q->len;
        frame_length += q->len;

        if (index > 0U)
        {
            tx_buffer[index - 1U].next = &tx_buffer[index];
        }

        eth_clean_cache(q->payload, q->len);
        index++;
    }

#ifdef ETH_TX_DUMP
    for (q = p; q != RT_NULL; q = q->next)
    {
        dump_hex(q->payload, q->len);
    }
#endif

    if (rt_mutex_take(&stm32_eth_device.mac_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return ERR_IF;
    }

    if (!stm32_eth_device.parent.link_status || !stm32_eth_device.mac_started)
    {
        rt_mutex_release(&stm32_eth_device.mac_lock);
        return ERR_IF;
    }

    TxConfig.Length = frame_length;
    TxConfig.TxBuffer = tx_buffer;
    state = HAL_ETH_Transmit(&EthHandle, &TxConfig, 1000);
    rt_mutex_release(&stm32_eth_device.mac_lock);

    if (state != HAL_OK)
    {
        LOG_W("eth transmit frame failed: 0x%08X", EthHandle.ErrorCode);
        return ERR_IF;
    }

    return ERR_OK;
}

/* receive data */
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
    HAL_StatusTypeDef state;
    rt_uint32_t frame_length = 0;
    struct pbuf *p = RT_NULL;
    struct rt_stm32_eth_rx_buffer *rx_buffer = RT_NULL;
    struct rt_stm32_eth_rx_buffer *current;

    RT_UNUSED(dev);

    if (rt_mutex_take(&stm32_eth_device.mac_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return RT_NULL;
    }

    if (!stm32_eth_device.mac_started)
    {
        rt_mutex_release(&stm32_eth_device.mac_lock);
        return RT_NULL;
    }

    state = HAL_ETH_ReadData(&EthHandle, (void **)&rx_buffer);
    rt_mutex_release(&stm32_eth_device.mac_lock);

    if (state != HAL_OK)
    {
        return RT_NULL;
    }

    for (current = rx_buffer; current != RT_NULL; current = current->next)
    {
        rt_uint32_t index = (rt_uint32_t)(current - Rx_Buff_Info);

        frame_length += current->length;
        eth_invalidate_cache(eth_rx_buffer_at(index), current->length);
    }

#ifdef ETH_RX_DUMP
    for (current = rx_buffer; current != RT_NULL; current = current->next)
    {
        rt_uint32_t index = (rt_uint32_t)(current - Rx_Buff_Info);
        dump_hex(eth_rx_buffer_at(index), current->length);
    }
#endif

    p = pbuf_alloc(PBUF_RAW, frame_length, PBUF_RAM);
    if ((p != RT_NULL) && (eth_rx_copy(p, rx_buffer) != RT_EOK))
    {
        pbuf_free(p);
        p = RT_NULL;
    }

    eth_rx_release_buffers(rx_buffer);
    return p;
}

/* interrupt service routine */
void ETH_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_ETH_IRQHandler(&EthHandle);
    rt_interrupt_leave();
}

void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
    rt_err_t result;

    RT_UNUSED(heth);
    result = eth_device_ready(&(stm32_eth_device.parent));
    if (result != RT_EOK)
    {
        LOG_I("RxCpltCallback err = %d", result);
    }
}

void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    uint32_t error = HAL_ETH_GetError(heth);
    uint32_t dma_error = HAL_ETH_GetDMAError(heth);
    uint32_t mac_error = HAL_ETH_GetMACError(heth);

    if ((dma_error & ETH_DMA_RX_BUFFER_UNAVAILABLE_FLAG) != 0U)
    {
        /* HAL_ETH_ReadData() replenishes the descriptors and resumes Rx DMA. */
        (void)eth_device_ready(&(stm32_eth_device.parent));
        dma_error &= ~(ETH_DMA_RX_BUFFER_UNAVAILABLE_FLAG | ETH_DMA_ABNORMAL_SUMMARY_FLAG);
    }

    dma_error &= ~ETH_DMA_EARLY_TX_IT_FLAG;
#if defined(ETH_DMACSR_ETI)
    /* H7 reports ETI separately from the generic early transmit flag. */
    dma_error &= ~ETH_DMACSR_ETI;
#endif

    if ((dma_error != 0U) || ((error & HAL_ETH_ERROR_MAC) != 0U))
    {
        LOG_E("eth error: code=0x%08X dma=0x%08X mac=0x%08X",
              error, dma_error, mac_error);
    }
}

enum
{
    PHY_LINK        = (1 << 0),
    PHY_100M        = (1 << 1),
    PHY_FULL_DUPLEX = (1 << 2),
};

static rt_err_t eth_mac_stop(void)
{
    rt_err_t result = RT_EOK;

    if (rt_mutex_take(&stm32_eth_device.mac_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (stm32_eth_device.mac_started)
    {
        if (HAL_ETH_Stop_IT(&EthHandle) == HAL_OK)
        {
            stm32_eth_device.mac_started = RT_FALSE;
        }
        else
        {
            result = -RT_ERROR;
        }
    }

    rt_mutex_release(&stm32_eth_device.mac_lock);
    return result;
}

static rt_err_t eth_mac_configure_and_start(rt_uint32_t speed, rt_uint32_t duplex)
{
    ETH_MACConfigTypeDef mac_config;
    rt_err_t result = -RT_ERROR;

    if (rt_mutex_take(&stm32_eth_device.mac_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (stm32_eth_device.mac_started)
    {
        if (HAL_ETH_Stop_IT(&EthHandle) != HAL_OK)
        {
            goto __exit;
        }
        stm32_eth_device.mac_started = RT_FALSE;
    }

    if (HAL_ETH_GetMACConfig(&EthHandle, &mac_config) != HAL_OK)
    {
        goto __exit;
    }

    mac_config.Speed = speed;
    mac_config.DuplexMode = duplex;
    if (HAL_ETH_SetMACConfig(&EthHandle, &mac_config) != HAL_OK)
    {
        goto __exit;
    }

    if (HAL_ETH_Start_IT(&EthHandle) != HAL_OK)
    {
        goto __exit;
    }

    stm32_eth_device.mac_started = RT_TRUE;
    result = RT_EOK;

__exit:
    rt_mutex_release(&stm32_eth_device.mac_lock);
    return result;
}

static void phy_linkchange(void)
{
    rt_uint8_t phy_state_new = 0;
    uint32_t status = 0;

    if (phy_addr == PHY_INVALID_ADDR)
    {
        return;
    }

    /* Read twice because the link bit in BMSR can be latched low. */
    (void)HAL_ETH_ReadPHYRegister(&EthHandle, phy_addr, PHY_BASIC_STATUS_REG, &status);
    if (HAL_ETH_ReadPHYRegister(&EthHandle, phy_addr, PHY_BASIC_STATUS_REG, &status) != HAL_OK)
    {
        return;
    }

    LOG_D("phy basic status reg is 0x%X", status);
    if ((status & PHY_LINKED_STATUS_MASK) != 0U)
    {
        uint32_t phy_status = 0;

        if ((status & PHY_AUTONEGO_COMPLETE_MASK) == 0U)
        {
            return;
        }

        if (HAL_ETH_ReadPHYRegister(&EthHandle, phy_addr, PHY_Status_REG, &phy_status) != HAL_OK)
        {
            return;
        }

        LOG_D("phy control status reg is 0x%X", phy_status);
        phy_state_new |= PHY_LINK;
        if (PHY_Status_SPEED_100M(phy_status))
        {
            phy_state_new |= PHY_100M;
        }

        if (PHY_Status_FULL_DUPLEX(phy_status))
        {
            phy_state_new |= PHY_FULL_DUPLEX;
        }
    }

    if (stm32_eth_device.phy_state == phy_state_new)
    {
        return;
    }

    if ((phy_state_new & PHY_LINK) != 0U)
    {
        rt_uint32_t speed;
        rt_uint32_t duplex;

        if ((phy_state_new & PHY_100M) != 0U)
        {
            speed = ETH_SPEED_100M;
        }
        else
        {
            speed = ETH_SPEED_10M;
        }

        if ((phy_state_new & PHY_FULL_DUPLEX) != 0U)
        {
            duplex = ETH_FULLDUPLEX_MODE;
        }
        else
        {
            duplex = ETH_HALFDUPLEX_MODE;
        }

        if (eth_mac_configure_and_start(speed, duplex) != RT_EOK)
        {
            stm32_eth_device.phy_state = PHY_STATE_UNKNOWN;
            if (stm32_eth_device.parent.link_status)
            {
                eth_device_linkchange(&stm32_eth_device.parent, RT_FALSE);
            }
            LOG_E("configure and start MAC failed");
            return;
        }

        stm32_eth_device.ETH_Speed = speed;
        stm32_eth_device.ETH_Mode = duplex;
        stm32_eth_device.phy_state = phy_state_new;
        LOG_I("link up, %sMbps, %s-duplex",
              speed == ETH_SPEED_100M ? "100" : "10",
              duplex == ETH_FULLDUPLEX_MODE ? "full" : "half");

        if (!stm32_eth_device.parent.link_status)
        {
            eth_device_linkchange(&stm32_eth_device.parent, RT_TRUE);
        }
    }
    else
    {
        if (stm32_eth_device.parent.link_status)
        {
            eth_device_linkchange(&stm32_eth_device.parent, RT_FALSE);
        }

        if (eth_mac_stop() != RT_EOK)
        {
            stm32_eth_device.phy_state = PHY_STATE_UNKNOWN;
            LOG_E("stop MAC failed");
            return;
        }

        stm32_eth_device.phy_state = phy_state_new;
        LOG_I("link down");
    }
}

#ifdef PHY_USING_INTERRUPT_MODE
static void eth_phy_isr(void *args)
{
    RT_UNUSED(args);
    rt_sem_release(&phy_link_sem);
}
#endif /* PHY_USING_INTERRUPT_MODE */

static void phy_monitor_thread_entry(void *parameter)
{
    RT_UNUSED(parameter);

#ifdef PHY_USING_INTERRUPT_MODE
    uint32_t status = 0;

    if (rt_sem_init(&phy_link_sem, "phyirq", 0, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        LOG_E("initialize PHY interrupt semaphore failed");
        return;
    }

    rt_pin_mode(PHY_INT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(PHY_INT_PIN, PIN_IRQ_MODE_FALLING, eth_phy_isr, RT_NULL);

    (void)HAL_ETH_WritePHYRegister(&EthHandle, phy_addr, PHY_INTERRUPT_MASK_REG, PHY_INT_MASK);
#if defined(PHY_INTERRUPT_CTRL_REG)
    (void)HAL_ETH_WritePHYRegister(&EthHandle, phy_addr, PHY_INTERRUPT_CTRL_REG, PHY_INTERRUPT_EN);
#endif
    (void)HAL_ETH_ReadPHYRegister(&EthHandle, phy_addr, PHY_INTERRUPT_FLAG_REG, &status);
    rt_pin_irq_enable(PHY_INT_PIN, PIN_IRQ_ENABLE);

    phy_linkchange();
    while (1)
    {
        if (rt_sem_take(&phy_link_sem, RT_WAITING_FOREVER) == RT_EOK)
        {
            (void)HAL_ETH_ReadPHYRegister(&EthHandle, phy_addr, PHY_INTERRUPT_FLAG_REG, &status);
            LOG_D("phy interrupt status reg is 0x%X", status);
            phy_linkchange();
        }
    }
#else
    while (1)
    {
        phy_linkchange();
        rt_thread_mdelay(1000);
    }
#endif /* PHY_USING_INTERRUPT_MODE */
}

static rt_err_t eth_allocate_dma_memory(void)
{
#ifdef BSP_USING_ETH_H750
    DMARxDscrTab = DMARxDscrTab_Storage;
    DMATxDscrTab = DMATxDscrTab_Storage;
    Rx_Buff = Rx_Buff_Storage;
#else
    DMARxDscrTab = (ETH_DMADescTypeDef *)rt_calloc(ETH_RX_DESC_CNT, sizeof(ETH_DMADescTypeDef));
    DMATxDscrTab = (ETH_DMADescTypeDef *)rt_calloc(ETH_TX_DESC_CNT, sizeof(ETH_DMADescTypeDef));
    Rx_Buff = (rt_uint8_t *)rt_calloc(ETH_RX_BUFFER_CNT, ETH_MAX_PACKET_SIZE);

    if ((DMARxDscrTab == RT_NULL) || (DMATxDscrTab == RT_NULL) || (Rx_Buff == RT_NULL))
    {
        rt_free(DMARxDscrTab);
        rt_free(DMATxDscrTab);
        rt_free(Rx_Buff);
        DMARxDscrTab = RT_NULL;
        DMATxDscrTab = RT_NULL;
        Rx_Buff = RT_NULL;
        return -RT_ENOMEM;
    }
#endif

    return RT_EOK;
}

/* Register the EMAC device */
static int rt_hw_stm32_eth_init(void)
{
    rt_err_t state;
    rt_thread_t tid;

#ifdef ETH_RESET_PIN
    reset_pin = rt_pin_get(ETH_RESET_PIN);
    if (reset_pin < 0)
    {
        LOG_E("invalid ETH reset pin: %s", ETH_RESET_PIN);
        return -RT_ERROR;
    }
    rt_pin_mode(reset_pin, PIN_MODE_OUTPUT);
    rt_pin_write(reset_pin, PIN_HIGH);
#endif

    state = eth_allocate_dma_memory();
    if (state != RT_EOK)
    {
        LOG_E("No memory for ETH DMA");
        return state;
    }

    state = rt_mutex_init(&stm32_eth_device.mac_lock, "ethmac", RT_IPC_FLAG_PRIO);
    if (state != RT_EOK)
    {
        LOG_E("initialize MAC mutex failed: %d", state);
        return state;
    }

    stm32_eth_device.ETH_Speed = ETH_SPEED_100M;
    stm32_eth_device.ETH_Mode = ETH_FULLDUPLEX_MODE;

    /* OUI 00-80-E1 STMICROELECTRONICS. */
    stm32_eth_device.dev_addr[0] = 0x00;
    stm32_eth_device.dev_addr[1] = 0x80;
    stm32_eth_device.dev_addr[2] = 0xE1;
    /* Generate MAC addr from 96-bit unique ID (only for test). */
    stm32_eth_device.dev_addr[3] = *(rt_uint8_t *)(UID_BASE + 4);
    stm32_eth_device.dev_addr[4] = *(rt_uint8_t *)(UID_BASE + 2);
    stm32_eth_device.dev_addr[5] = *(rt_uint8_t *)(UID_BASE + 0);

    stm32_eth_device.parent.parent.init = rt_stm32_eth_init;
    stm32_eth_device.parent.parent.open = rt_stm32_eth_open;
    stm32_eth_device.parent.parent.close = rt_stm32_eth_close;
    stm32_eth_device.parent.parent.read = rt_stm32_eth_read;
    stm32_eth_device.parent.parent.write = rt_stm32_eth_write;
    stm32_eth_device.parent.parent.control = rt_stm32_eth_control;
    stm32_eth_device.parent.parent.user_data = RT_NULL;
    stm32_eth_device.parent.eth_rx = rt_stm32_eth_rx;
    stm32_eth_device.parent.eth_tx = rt_stm32_eth_tx;

    state = eth_device_init(&(stm32_eth_device.parent), "e0");
    if (state != RT_EOK)
    {
        LOG_E("emac device init failed: %d", state);
        return -RT_ERROR;
    }

    tid = rt_thread_create("phy",
                           phy_monitor_thread_entry,
                           RT_NULL,
                           1024,
                           RT_THREAD_PRIORITY_MAX - 2,
                           2);
    if (tid == RT_NULL)
    {
        return -RT_ERROR;
    }

    rt_thread_startup(tid);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_stm32_eth_init);
