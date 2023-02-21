/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/timeouts.h"
#include "lwip/netif.h"
#define LWIP_DHCP 0
#if LWIP_DHCP
#include "lwip/dhcp.h"
#endif
#include "netif/etharp.h"
#include "ethernetif.h"
#include <string.h>
#include "hal_emac.h"
#include <FreeRTOS.h>
#include "semphr.h"
#include "bflb_platform.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Network interface name */
#define IFNAME0 'b'
#define IFNAME1 'l'

#define ETH_DMA_TRANSMIT_TIMEOUT (20U)

#define BL702_EMAC  0
#define EMAC_OUTPUT BL702_EMAC

#if LWIP_DHCP
#define MAX_DHCP_TRIES 4
uint32_t DHCPfineTimer = 0;
uint8_t DHCP_state = DHCP_OFF;
#else
/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0      (uint8_t)10
#define IP_ADDR1      (uint8_t)28
#define IP_ADDR2      (uint8_t)30
#define IP_ADDR3      (uint8_t)221

/*NETMASK*/
#define NETMASK_ADDR0 (uint8_t)255
#define NETMASK_ADDR1 (uint8_t)255
#define NETMASK_ADDR2 (uint8_t)255
#define NETMASK_ADDR3 (uint8_t)0

/*Gateway Address*/
#define GW_ADDR0      (uint8_t)10
#define GW_ADDR1      (uint8_t)28
#define GW_ADDR2      (uint8_t)30
#define GW_ADDR3      (uint8_t)1
#endif

/* Private function prototypes -----------------------------------------------*/
void pbuf_free_custom(struct pbuf *p);
void ethernetif_input(void *argument);
SemaphoreHandle_t emac_rx_sem = NULL;
static StackType_t emac_rx_stack[256];
static StaticTask_t emac_rx_handle;
#if LWIP_DHCP
static StackType_t emac_dhcp_stack[256];
static StaticTask_t emac_dhcp_handle;
#endif
static uint8_t emac_rx_buffer[ETH_RX_BUFFER_SIZE] __attribute__((aligned(16))) = { 0 };

LWIP_MEMPOOL_DECLARE(RX_POOL, 10, sizeof(struct pbuf_custom), "Zero-copy RX PBUF pool");

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
                       LL Driver Interface ( LwIP stack --> ETH)
*******************************************************************************/
/**
  * @brief In this function, the hardware should be initialized.
  * Called from ethernetif_init().
  *
  * @param netif the already initialized lwip network interface structure
  *        for this ethernetif
  */
extern void emac_init_txrx_buffer(void);
extern int emac_phy_init(emac_phy_cfg_t *cfg);

/* For emac tx and rx,we put here to make controlling it's size easy */
#define ETH_RXBUFNB 5
#define ETH_TXBUFNB 5
#define ATTR_NOCACHE_RAM_SECTION   __attribute__((section(".nocache_ram")))
ATTR_NOCACHE_RAM_SECTION ATTR_EALIGN(4) uint8_t ethRxBuff[ETH_RXBUFNB][ETH_RX_BUFFER_SIZE] ATTR_EALIGN(4) = { 0 }; /* Ethernet Receive Buffers */
ATTR_NOCACHE_RAM_SECTION ATTR_EALIGN(4) uint8_t ethTxBuff[ETH_TXBUFNB][ETH_TX_BUFFER_SIZE] ATTR_EALIGN(4);         /* Ethernet Transmit Buffers */
void emac_init_txrx_buffer(void)
{
    emac_bd_init((uint8_t *)ethTxBuff, ETH_TXBUFNB, (uint8_t *)ethRxBuff, ETH_RXBUFNB);

}
void dhcp_thread(void const *argument);
void low_level_init(struct netif *netif)
{
    int ret = 0;

    emac_device_t emac_cfg = {
        .mac_addr[0] = 0x18,
        .mac_addr[1] = 0xB9,
        .mac_addr[2] = 0x05,
        .mac_addr[3] = 0x12,
        .mac_addr[4] = 0x34,
        .mac_addr[5] = 0x56,
    };

    /* set phy cfg */
    emac_phy_cfg_t phy_cfg = {
        .auto_negotiation = 1, /*!< Speed and mode auto negotiation */
        .full_duplex = 0,      /*!< Duplex mode */
        .speed = 0,            /*!< Speed mode */
        .phy_address = 1,      /*!< PHY address */
        .phy_id = 0x7c0f0,     /*!< PHY OUI, masked */
        .phy_state = PHY_STATE_DOWN,
    };

    /* set MAC hardware address length */
    netif->hwaddr_len = ETH_HWADDR_LEN;

    /* set MAC hardware address */
    netif->hwaddr[0] = emac_cfg.mac_addr[0];
    netif->hwaddr[1] = emac_cfg.mac_addr[1];
    netif->hwaddr[2] = emac_cfg.mac_addr[2];
    netif->hwaddr[3] = emac_cfg.mac_addr[3];
    netif->hwaddr[4] = emac_cfg.mac_addr[4];
    netif->hwaddr[5] = emac_cfg.mac_addr[5];

    /* maximum transfer unit */
    netif->mtu = 1500;

    /* emac init,configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
    MSG("emac_init\r\n");
    emac_init(&emac_cfg);

    ret = emac_phy_init(&phy_cfg);
    if (PHY_STATE_UP == phy_cfg.phy_state) {
        MSG("PHY[%x] @%d ready on %dMbps, %s duplex\n\r", (int)phy_cfg.phy_id, (int)phy_cfg.phy_address,
            (int)phy_cfg.speed,
            phy_cfg.full_duplex ? "full" : "half");
    } else {
        MSG("PHY Init fail\n\r");
        BL_CASE_FAIL;
        while (1)
            ;
    }
    emac_init_txrx_buffer();
    emac_start();
    // emac_start_tx();

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

    /* Initialize the RX POOL */
    LWIP_MEMPOOL_INIT(RX_POOL);

    /* create a binary semaphore used for informing ethernetif of frame reception */
    //vSemaphoreCreateBinary(emac_rx_sem);
    emac_rx_sem = xSemaphoreCreateBinary();

    /* create the task that handles the ETH_MAC */
    MSG("[OS] Starting emac rx task...\r\n");
    xTaskCreateStatic(ethernetif_input, (char *)"emac_rx_task", sizeof(emac_rx_stack) / 4, netif, 16, emac_rx_stack, &emac_rx_handle);
#if LWIP_DHCP
    MSG("[OS] Starting emac dhcp task...\r\n");
    xTaskCreateStatic(dhcp_thread, (char *)"emac_dhcp_task", sizeof(emac_dhcp_stack) / 4, netif, 16, emac_dhcp_stack, &emac_dhcp_handle);
#endif

    if (ret == 0) {
        MSG("[OS] %s Netif is up\r\n", netif->name);
        netif_set_up(netif);
        netif_set_link_up(netif);
    }
}

void emac_tx_error_callback_app()
{
    MSG("EMAC tx error callback\r\n");
}

void emac_rx_error_callback_app()
{
    MSG("EMAC rx error callback\r\n");
    // MSG("EMAC tx bd num 0x%x\r\n", BL_RD_WORD(0x4000D020));
    // MSG("EMAC rx bd description0 0x%x\r\n", BL_RD_WORD(0x4000D400 + ((5 + 5) * 8)));
    // MSG("EMAC rx bd description1 0x%x\r\n", BL_RD_WORD(0x4000D400 + ((5 + 5) * 8) + 0x4));
}
/**
  * @brief This function should do the actual transmission of the packet. The packet is
  * contained in the pbuf that is passed to the function. This pbuf
  * might be chained.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
  * @return ERR_OK if the packet could be sent
  *         an err_t value if the packet couldn't be sent
  *
  * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
  *       strange results. You might consider waiting for space in the DMA queue
  *       to become available since the stack doesn't retry to send a packet
  *       dropped because of memory failure (except for the TCP timers).
  */

static unsigned char emac_send_buf[1514];
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    err_t errval = ERR_OK;
    struct pbuf *q;

    if (!emac_bd_fragment_support()){

        uint32_t byteslefttocopy = 0;
        // uint32_t payloadoffset = 0;
        // uint32_t bufferoffset = 0;
        uint32_t framelength = 0;
        uint32_t flags = (EMAC_NORMAL_PACKET);

        for (q = p; q != NULL; q = q->next) {
            // MSG("p->tot_len:%d,q->len:%d, q->next:%d,f:%d\r\n", q->tot_len, q->len, q->next, framelength);

            byteslefttocopy = q->len;
            // payloadoffset = 0;

            // check is copy data is larger than emac tx buf
            while ((byteslefttocopy + framelength) > ETH_TX_BUFFER_SIZE) {
                // copy data to tx buf
                MSG("tx buf is too larger!\r\n");
                flags = EMAC_FRAGMENT_PACKET;
                // ARCH_MemCpy_Fast(&emac_send_buf[framelength + bufferoffset], q->payload + payloadoffset, (ETH_TX_BUFFER_SIZE - bufferoffset));
            }
            ARCH_MemCpy_Fast(&emac_send_buf[framelength], q->payload, byteslefttocopy);
            // bufferoffset = bufferoffset + byteslefttocopy;
            framelength = framelength + byteslefttocopy;
        }

        if (0 != emac_bd_tx_enqueue(flags, framelength, emac_send_buf)) {
            MSG("emac_bd_tx_enqueue error!\r\n");
            return ERR_IF;
        }

    }else{
        for (q = p; q != NULL; q = q->next) {
            //MSG("p->tot_len:%d,q->len:%d, q->next:%d\r\n", q->tot_len, q->len, q->next);
            if (q->len == q->tot_len) {
                if (0 != emac_bd_tx_enqueue(EMAC_NORMAL_PACKET, q->len, q->payload)) {
                    MSG("emac_bd_tx_enqueue error!\r\n");
                    return ERR_IF;
                }
            } else if (q->len < q->tot_len) {
                if (0 != emac_bd_tx_enqueue(EMAC_FRAGMENT_PACKET, q->len, q->payload)) {
                    MSG("emac_bd_tx_enqueue error!\r\n");
                    return ERR_IF;
                }
            } else {
                MSG("low_level_output error! Wrong packet!\r\n");
            }
        }
    }

    return errval;
}

/**
  * @brief Should allocate a pbuf and transfer the bytes of the incoming
  * packet from the interface into the pbuf.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return a pbuf filled with the received packet (including MAC header)
  *         NULL on memory error
  */
static struct pbuf *low_level_input(struct netif *netif)
{
    uint32_t rx_len = 0;
    struct pbuf *p = NULL, *q;

    emac_bd_rx_dequeue(-1, &rx_len, emac_rx_buffer);

    if (rx_len <= 0) {
        //MSG("Recv Null Data\r\n");
        return NULL;
    }

    //MSG("Recv full Data\r\n");

    p = pbuf_alloc(PBUF_RAW, rx_len, PBUF_POOL);

    if (p != NULL) {
        for (q = p; q != NULL; q = q->next) {
            memcpy(q->payload, emac_rx_buffer + rx_len - q->tot_len, q->len);
        }
    }

    return p;
}

void emac_rx_done_callback_app(void)
{
    BaseType_t xHigherPriorityTaskWoken;

    /* Is it time for vATask() to run? */
    xHigherPriorityTaskWoken = pdFALSE;
    //MSG("emac_rx_done_callback_app\r\n");
    //low_level_input(NULL);
    xSemaphoreGiveFromISR(emac_rx_sem, &xHigherPriorityTaskWoken);
    /* If xHigherPriorityTaskWoken was set to true you
    we should yield.  The actual macro used here is
    port specific. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
/**
  * @brief This function is the ethernetif_input task, it is processed when a packet
  * is ready to be read from the interface. It uses the function low_level_input()
  * that should handle the actual reception of bytes from the network
  * interface. Then the type of the received packet is determined and
  * the appropriate input function is called.
  *
  * @param netif the lwip network interface structure for this ethernetif
  */
void ethernetif_input(void *argument)
{
    struct pbuf *p = NULL;
    struct netif *netif = (struct netif *)argument;

    for (;;) {
        if (xSemaphoreTake(emac_rx_sem, portMAX_DELAY) == pdTRUE) {
            do {
                //MSG("ethernetif_input\r\n");
                p = low_level_input(netif);

                if (p != NULL) {
                    if (netif->input(p, netif) != ERR_OK) {
                        pbuf_free(p);
                    }
                }
            } while (p != NULL);
        }
    }
}

/**
  * @brief Should be called at the beginning of the program to set up the
  * network interface. It calls the function low_level_init() to do the
  * actual setup of the hardware.
  *
  * This function should be passed as a parameter to netif_add().
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return ERR_OK if the loopif is initialized
  *         ERR_MEM if private data couldn't be allocated
  *         any other err_t on error
  */
err_t ethernetif_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

    /* initialize the hardware */
    low_level_init(netif);

    return ERR_OK;
}

/**
  * @brief  Custom Rx pbuf free callback
  * @param  pbuf: pbuf to be freed
  * @retval None
  */
void pbuf_free_custom(struct pbuf *p)
{
    struct pbuf_custom *custom_pbuf = (struct pbuf_custom *)p;
    LWIP_MEMPOOL_FREE(RX_POOL, custom_pbuf);
}

static void ethernet_set_static_ip(struct netif *netif)
{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
    netif_set_addr(netif, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gw));
}

/**
  * @brief  Notify the User about the network interface config status
  * @param  netif: the network interface
  * @retval None
  */
void ethernet_link_status_updated(struct netif *netif)
{
    if (netif_is_link_up(netif)) {
#if LWIP_DHCP
        /* Update DHCP state machine */
        DHCP_state = DHCP_START;
        MSG("DHCP Start\n");
#else
        /* IP address default setting */
        ethernet_set_static_ip(netif);
        uint8_t iptxt[20];
        sprintf((char *)iptxt, "%s", ip4addr_ntoa(netif_ip4_addr(netif)));
        MSG("Static IP address: %s\n", iptxt);
#endif
    } else {
#if LWIP_DHCP
        /* Update DHCP state machine */
        DHCP_state = DHCP_LINK_DOWN;
#else
        MSG("The network cable is not connected \n");
#endif /* LWIP_DHCP */
    }
}

/**
  * @brief
  * @retval None
  */
void ethernet_link_check_state(struct netif *netif)
{
    emac_phy_status_t phy_state;

    uint32_t linkchanged = 0;
    // uint32_t speed = 0, duplex = 0;

    phy_state = ethernet_phy_status_get();

    if (netif_is_link_up(netif) && (phy_state <= EMAC_PHY_STAT_LINK_DOWN)) {
        MSG("Link Down\n");
        emac_stop();
        netif_set_down(netif);
        netif_set_link_down(netif);
    } else if (!netif_is_link_up(netif) && (phy_state <= EMAC_PHY_STAT_LINK_DOWN)) {
        MSG("Reinit\n");
        emac_phy_init(NULL);
    } else if (!netif_is_link_up(netif) && (phy_state > EMAC_PHY_STAT_LINK_UP)) {
        // switch (phy_state) {
        //     case EMAC_PHY_STAT_100MBITS_FULLDUPLEX:
        //         duplex = 1;
        //         speed = 100;
        //         linkchanged = 1;
        //         break;

        //     case EMAC_PHY_STAT_100MBITS_HALFDUPLEX:
        //         duplex = 0;
        //         speed = 100;
        //         linkchanged = 1;
        //         break;

        //     case EMAC_PHY_STAT_10MBITS_FULLDUPLEX:
        //         duplex = 1;
        //         speed = 10;
        //         linkchanged = 1;
        //         break;

        //     case EMAC_PHY_STAT_10MBITS_HALFDUPLEX:
        //         duplex = 0;
        //         speed = 10;
        //         linkchanged = 1;
        //         break;

        //     default:
        //         break;
        // }

        if (linkchanged) {
            /* Get MAC Config MAC */
            //HAL_ETH_GetMACConfig(&EthHandle, &MACConf);
            //MACConf.DuplexMode = duplex;
            //MACConf.Speed = speed;
            //HAL_ETH_SetMACConfig(&EthHandle, &MACConf);
            //HAL_ETH_Start(&EthHandle);
            netif_set_up(netif);
            netif_set_link_up(netif);
        }
    }
}

#if LWIP_DHCP
/**
  * @brief  DHCP Process
  * @param  argument: network interface
  * @retval None
  */
void dhcp_thread(void const *argument)
{
    struct netif *netif = (struct netif *)argument;
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;
    struct dhcp *dhcp;
    uint8_t iptxt[20];

    for (;;) {
        switch (DHCP_state) {
            case DHCP_START: {
                ip_addr_set_zero_ip4(&netif->ip_addr);
                ip_addr_set_zero_ip4(&netif->netmask);
                ip_addr_set_zero_ip4(&netif->gw);
                DHCP_state = DHCP_WAIT_ADDRESS;
                MSG("  State: Looking for DHCP server ...\n");
                dhcp_start(netif);
            } break;
            case DHCP_WAIT_ADDRESS: {
                if (dhcp_supplied_address(netif)) {
                    DHCP_state = DHCP_ADDRESS_ASSIGNED;
                    sprintf((char *)iptxt, "%s", ip4addr_ntoa(netif_ip4_addr(netif)));
                    MSG("IP address assigned by a DHCP server: %s\n", iptxt);
                } else {
                    dhcp = (struct dhcp *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

                    /* DHCP timeout */
                    if (dhcp->tries > MAX_DHCP_TRIES) {
                        DHCP_state = DHCP_TIMEOUT;

                        /* Static address used */
                        ethernet_set_static_ip(netif);
                        sprintf((char *)iptxt, "%s", ip4addr_ntoa(netif_ip4_addr(netif)));
                        MSG("DHCP Timeout !! \n");
                        MSG("Static IP address: %s\n", iptxt);
                    }
                }
            } break;
            case DHCP_LINK_DOWN: {
                DHCP_state = DHCP_OFF;
                MSG("The network cable is not connected \n");
            } break;
            default:
                break;
        }
        vTaskDelay(100);
    }
}
#endif /* LWIP_DHCP */
