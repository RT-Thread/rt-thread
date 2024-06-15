/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_cdc_ecm.h"

/*!< endpoint address */
#define CDC_IN_EP          0x81
#define CDC_OUT_EP         0x02
#define CDC_INT_EP         0x83

#define USBD_VID           0xFFFF
#define USBD_PID           0xFFFF
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

/*!< config descriptor size */
#define USB_CONFIG_SIZE    (9 + CDC_ECM_DESCRIPTOR_LEN)

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif

#define CDC_ECM_ETH_STATISTICS_BITMAP 0x00000000

/* str idx = 4 is for mac address: aa:bb:cc:dd:ee:ff*/
#define CDC_ECM_MAC_STRING_INDEX      4

/*!< global descriptor */
static const uint8_t cdc_ecm_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ECM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, CDC_MAX_MPS, CDC_ECM_ETH_STATISTICS_BITMAP, CONFIG_CDC_ECM_ETH_MAX_SEGSZE, 0, 0, CDC_ECM_MAC_STRING_INDEX),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x2E,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'C', 0x00,                  /* wcChar10 */
    'D', 0x00,                  /* wcChar11 */
    'C', 0x00,                  /* wcChar12 */
    ' ', 0x00,                  /* wcChar13 */
    'E', 0x00,                  /* wcChar14 */
    'C', 0x00,                  /* wcChar15 */
    'M', 0x00,                  /* wcChar16 */
    ' ', 0x00,                  /* wcChar17 */
    'D', 0x00,                  /* wcChar18 */
    'E', 0x00,                  /* wcChar19 */
    'M', 0x00,                  /* wcChar20 */
    'O', 0x00,                  /* wcChar21 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '2', 0x00,                  /* wcChar3 */
    '1', 0x00,                  /* wcChar4 */
    '2', 0x00,                  /* wcChar5 */
    '3', 0x00,                  /* wcChar6 */
    '4', 0x00,                  /* wcChar7 */
    '5', 0x00,                  /* wcChar8 */
    '6', 0x00,                  /* wcChar9 */
    ///////////////////////////////////////
    /// string4 descriptor
    ///////////////////////////////////////
    0x1A,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'a', 0x00,                  /* wcChar0 */
    'a', 0x00,                  /* wcChar1 */
    'b', 0x00,                  /* wcChar2 */
    'b', 0x00,                  /* wcChar3 */
    'c', 0x00,                  /* wcChar4 */
    'c', 0x00,                  /* wcChar5 */
    'd', 0x00,                  /* wcChar6 */
    'd', 0x00,                  /* wcChar7 */
    'e', 0x00,                  /* wcChar8 */
    'e', 0x00,                  /* wcChar9 */
    'f', 0x00,                  /* wcChar10 */
    'f', 0x00,                  /* wcChar11 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x02,
    0x02,
    0x01,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

const uint8_t mac[6] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0 (uint8_t)192
#define IP_ADDR1 (uint8_t)168
#define IP_ADDR2 (uint8_t)123
#define IP_ADDR3 (uint8_t)100

/*NETMASK*/
#define NETMASK_ADDR0 (uint8_t)255
#define NETMASK_ADDR1 (uint8_t)255
#define NETMASK_ADDR2 (uint8_t)255
#define NETMASK_ADDR3 (uint8_t)0

/*Gateway Address*/
#define GW_ADDR0 (uint8_t)192
#define GW_ADDR1 (uint8_t)168
#define GW_ADDR2 (uint8_t)123
#define GW_ADDR3 (uint8_t)1

#include "netif/etharp.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"

const ip_addr_t ipaddr = IPADDR4_INIT_BYTES(IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
const ip_addr_t netmask = IPADDR4_INIT_BYTES(NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
const ip_addr_t gateway = IPADDR4_INIT_BYTES(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);

static struct netif cdc_ecm_netif; //network interface

/* Network interface name */
#define IFNAME0 'E'
#define IFNAME1 'X'

static err_t linkoutput_fn(struct netif *netif, struct pbuf *p)
{
    static int ret;

    ret = usbd_cdc_ecm_eth_tx(p);
    if (ret == 0)
        return ERR_OK;
    else
        return ERR_BUF;
}

err_t cdc_ecm_if_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

    netif->mtu = 1500;
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP | NETIF_FLAG_UP;
    netif->state = NULL;
    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    netif->output = etharp_output;
    netif->linkoutput = linkoutput_fn;
    return ERR_OK;
}

err_t cdc_ecm_if_input(struct netif *netif)
{
    static err_t err;
    static struct pbuf *p;

    p = usbd_cdc_ecm_eth_rx();
    if (p != NULL) {
        err = netif->input(p, netif);
        if (err != ERR_OK) {
            pbuf_free(p);
        }
    } else {
        return ERR_BUF;
    }
    return err;
}

void cdc_ecm_lwip_init(void)
{
    struct netif *netif = &cdc_ecm_netif;

    lwip_init();

    netif->hwaddr_len = 6;
    memcpy(netif->hwaddr, mac, 6);

    netif = netif_add(netif, &ipaddr, &netmask, &gateway, NULL, cdc_ecm_if_init, netif_input);
    netif_set_default(netif);
    while (!netif_is_up(netif)) {
    }

    // while (dhserv_init(&dhcp_config)) {}

    // while (dnserv_init(&ipaddr, PORT_DNS, dns_query_proc)) {}
}

void usbd_cdc_ecm_data_recv_done(uint8_t *buf, uint32_t len)
{
}

void cdc_ecm_input_poll(void)
{
    cdc_ecm_if_input(&cdc_ecm_netif);
}

static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

struct usbd_interface intf0;
struct usbd_interface intf1;

/* ecm only supports in linux, and you should input the following command
 * 
 * sudo ifconfig enxaabbccddeeff up
 * sudo dhcpclient enxaabbccddeeff
*/
void cdc_ecm_init(uint8_t busid, uint32_t reg_base)
{
    cdc_ecm_lwip_init();
    
    usbd_desc_register(busid, cdc_ecm_descriptor);
    usbd_add_interface(busid, usbd_cdc_ecm_init_intf(&intf0, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP));
    usbd_add_interface(busid, usbd_cdc_ecm_init_intf(&intf1, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP));
    usbd_initialize(busid, reg_base, usbd_event_handler);
}