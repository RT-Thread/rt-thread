/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_adb.h"

#define ADB_OUT_EP_IDX        0
#define ADB_IN_EP_IDX         1

#define ADB_STATE_READ_MSG    0
#define ADB_STATE_READ_DATA   1
#define ADB_STATE_WRITE_MSG   2
#define ADB_STATE_WRITE_DATA  3
#define ADB_STATE_AWRITE_MSG  4
#define ADB_STATE_AWRITE_DATA 5

#define MAX_PAYLOAD_V1        (4 * 1024)
#define MAX_PAYLOAD_V2        (256 * 1024)
#define MAX_PAYLOAD           MAX_PAYLOAD_V1
#define A_VERSION             0x01000000

#define A_SYNC                0x434e5953
#define A_CNXN                0x4e584e43
#define A_OPEN                0x4e45504f
#define A_OKAY                0x59414b4f
#define A_CLSE                0x45534c43
#define A_WRTE                0x45545257
#define A_AUTH                0x48545541

struct adb_msg {
    uint32_t command;     /* command identifier constant (A_CNXN, ...) */
    uint32_t arg0;        /* first argument                            */
    uint32_t arg1;        /* second argument                           */
    uint32_t data_length; /* length of payload (0 is allowed)          */
    uint32_t data_crc32;  /* crc32 of data payload                     */
    uint32_t magic;       /* command ^ 0xffffffff */
};

struct adb_packet {
    struct adb_msg msg;
    uint8_t payload[MAX_PAYLOAD];
};

struct usbd_adb {
    uint8_t state;
    uint8_t common_state;
    uint8_t write_state;
    bool writable;
    uint32_t localid;
    uint32_t shell_remoteid;
    uint32_t file_remoteid;
} adb_client;

static struct usbd_endpoint adb_ep_data[2];

USB_NOCACHE_RAM_SECTION struct adb_packet tx_packet;
USB_NOCACHE_RAM_SECTION struct adb_packet rx_packet;

static inline uint32_t adb_packet_checksum(struct adb_packet *packet)
{
    uint32_t sum = 0;
    uint32_t i;

    for (i = 0; i < packet->msg.data_length; ++i) {
        sum += (uint32_t)(packet->payload[i]);
    }

    return sum;
}

static uint32_t usbd_adb_get_remoteid(uint32_t localid)
{
    if (localid == ADB_SHELL_LOALID) {
        return adb_client.shell_remoteid;
    } else {
        return adb_client.file_remoteid;
    }
}

static void adb_send_msg(struct adb_packet *packet)
{
    adb_client.common_state = ADB_STATE_WRITE_MSG;

    packet->msg.data_crc32 = adb_packet_checksum(packet);
    packet->msg.magic = packet->msg.command ^ 0xffffffff;

    usbd_ep_start_write(0, adb_ep_data[ADB_IN_EP_IDX].ep_addr, (uint8_t *)&packet->msg, sizeof(struct adb_msg));
}

static void adb_send_okay(struct adb_packet *packet, uint32_t localid)
{
    packet->msg.command = A_OKAY;
    packet->msg.arg0 = localid;
    packet->msg.arg1 = usbd_adb_get_remoteid(localid);
    packet->msg.data_length = 0;

    adb_send_msg(&tx_packet);
}

static void adb_send_close(struct adb_packet *packet, uint32_t localid, uint32_t remoteid)
{
    packet->msg.command = A_CLSE;
    packet->msg.arg0 = localid;
    packet->msg.arg1 = remoteid;
    packet->msg.data_length = 0;

    adb_send_msg(&tx_packet);
}

void usbd_adb_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)ep;

    if (adb_client.common_state == ADB_STATE_READ_MSG) {
        if (nbytes != sizeof(struct adb_msg)) {
            USB_LOG_ERR("invalid adb msg size:%d\r\n", nbytes);
            return;
        }

        USB_LOG_DBG("command:%x arg0:%x arg1:%x len:%d\r\n",
                     rx_packet.msg.command,
                     rx_packet.msg.arg0,
                     rx_packet.msg.arg1,
                     rx_packet.msg.data_length);

        if (rx_packet.msg.data_length) {
            /* setup next out ep read transfer */
            adb_client.common_state = ADB_STATE_READ_DATA;
            usbd_ep_start_read(busid, adb_ep_data[ADB_OUT_EP_IDX].ep_addr, rx_packet.payload, rx_packet.msg.data_length);
        } else {
            if (rx_packet.msg.command == A_CLSE) {
                adb_client.writable = false;
                usbd_adb_notify_write_done();
                USB_LOG_INFO("Close remoteid:%x\r\n", rx_packet.msg.arg0);
            }
            adb_client.common_state = ADB_STATE_READ_MSG;
            /* setup first out ep read transfer */
            usbd_ep_start_read(busid, adb_ep_data[ADB_OUT_EP_IDX].ep_addr, (uint8_t *)&rx_packet.msg, sizeof(struct adb_msg));
        }
    } else if (adb_client.common_state == ADB_STATE_READ_DATA) {
        switch (rx_packet.msg.command) {
            case A_SYNC:

                break;
            case A_CNXN: /* CONNECT(version, maxdata, "system-id-string") */
                char *support_feature = "device::"
                                        "ro.product.name=cherryadb;"
                                        "ro.product.model=cherrysh;"
                                        "ro.product.device=cherryadb;"
                                        "features=cmd,shell_v1";

                tx_packet.msg.command = A_CNXN;
                tx_packet.msg.arg0 = A_VERSION;
                tx_packet.msg.arg1 = MAX_PAYLOAD;
                tx_packet.msg.data_length = strlen(support_feature);
                memcpy(tx_packet.payload, support_feature, strlen(support_feature));

                adb_send_msg(&tx_packet);

                adb_client.writable = false;
                break;
            case A_OPEN: /* OPEN(local-id, 0, "destination") */
                rx_packet.payload[rx_packet.msg.data_length] = '\0';

                if (strncmp((const char *)rx_packet.payload, "shell:", 6) == 0) {
                    adb_client.localid = ADB_SHELL_LOALID;
                    adb_client.shell_remoteid = rx_packet.msg.arg0;
                    adb_send_okay(&tx_packet, ADB_SHELL_LOALID);

                    USB_LOG_INFO("Open shell service, remoteid:%x\r\n", rx_packet.msg.arg0);
                } else if (strncmp((const char *)rx_packet.payload, "sync:", 5) == 0) {
                    adb_client.localid = ADB_FILE_LOALID;
                    adb_client.file_remoteid = rx_packet.msg.arg0;
                    adb_send_okay(&tx_packet, ADB_FILE_LOALID);
                    USB_LOG_INFO("Open file service, remoteid:%x\r\n", rx_packet.msg.arg0);
                }
                break;
            case A_OKAY:

                break;
            case A_CLSE:

                break;
            case A_WRTE: /* WRITE(local-id, remote-id, "data") */
                if ((rx_packet.msg.arg0 == adb_client.shell_remoteid) && (rx_packet.msg.arg1 == ADB_SHELL_LOALID)) {
                    adb_send_okay(&tx_packet, rx_packet.msg.arg1);
                } else if ((rx_packet.msg.arg0 == adb_client.file_remoteid) && (rx_packet.msg.arg1 == ADB_FILE_LOALID)) {
                    adb_send_okay(&tx_packet, rx_packet.msg.arg1);
                } else {
                    adb_send_close(&tx_packet, 0, rx_packet.msg.arg0);
                }
                break;
            case A_AUTH:

                break;

            default:
                break;
        }
    }
}

void usbd_adb_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)ep;
    (void)nbytes;

    if (adb_client.common_state == ADB_STATE_WRITE_MSG) {
        if (tx_packet.msg.data_length) {
            adb_client.common_state = ADB_STATE_WRITE_DATA;
            usbd_ep_start_write(busid, adb_ep_data[ADB_IN_EP_IDX].ep_addr, tx_packet.payload, tx_packet.msg.data_length);
        } else {
            if (rx_packet.msg.command == A_WRTE) {
                adb_client.writable = true;
                if (adb_client.localid == ADB_SHELL_LOALID) {
                    usbd_adb_notify_shell_read(rx_packet.payload, rx_packet.msg.data_length);
                } else {
                }
            }
            adb_client.common_state = ADB_STATE_READ_MSG;
            /* setup first out ep read transfer */
            usbd_ep_start_read(busid, adb_ep_data[ADB_OUT_EP_IDX].ep_addr, (uint8_t *)&rx_packet.msg, sizeof(struct adb_msg));
        }
    } else if (adb_client.common_state == ADB_STATE_WRITE_DATA) {
        adb_client.common_state = ADB_STATE_READ_MSG;
        /* setup first out ep read transfer */
        usbd_ep_start_read(busid, adb_ep_data[ADB_OUT_EP_IDX].ep_addr, (uint8_t *)&rx_packet.msg, sizeof(struct adb_msg));
    } else if (adb_client.write_state == ADB_STATE_AWRITE_MSG) {
        if (tx_packet.msg.data_length) {
            adb_client.write_state = ADB_STATE_AWRITE_DATA;
            usbd_ep_start_write(busid, adb_ep_data[ADB_IN_EP_IDX].ep_addr, tx_packet.payload, tx_packet.msg.data_length);
        } else {
        }
    } else if (adb_client.write_state == ADB_STATE_AWRITE_DATA) {
        usbd_adb_notify_write_done();
    }
}

void adb_notify_handler(uint8_t busid, uint8_t event, void *arg)
{
    (void)arg;

    switch (event) {
        case USBD_EVENT_INIT:
            break;
        case USBD_EVENT_DEINIT:
            break;
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONFIGURED:
            adb_client.common_state = ADB_STATE_READ_MSG;
            /* setup first out ep read transfer */
            usbd_ep_start_read(busid, adb_ep_data[ADB_OUT_EP_IDX].ep_addr, (uint8_t *)&rx_packet.msg, sizeof(struct adb_msg));
            break;

        default:
            break;
    }
}

struct usbd_interface *usbd_adb_init_intf(uint8_t busid, struct usbd_interface *intf, uint8_t in_ep, uint8_t out_ep)
{
    (void)busid;

    intf->class_interface_handler = NULL;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = NULL;
    intf->notify_handler = adb_notify_handler;

    adb_ep_data[ADB_OUT_EP_IDX].ep_addr = out_ep;
    adb_ep_data[ADB_OUT_EP_IDX].ep_cb = usbd_adb_bulk_out;
    adb_ep_data[ADB_IN_EP_IDX].ep_addr = in_ep;
    adb_ep_data[ADB_IN_EP_IDX].ep_cb = usbd_adb_bulk_in;

    usbd_add_endpoint(busid, &adb_ep_data[ADB_OUT_EP_IDX]);
    usbd_add_endpoint(busid, &adb_ep_data[ADB_IN_EP_IDX]);

    return intf;
}

bool usbd_adb_can_write(void)
{
    return adb_client.writable;
}

int usbd_abd_write(uint32_t localid, const uint8_t *data, uint32_t len)
{
    struct adb_packet *packet;

    packet = &tx_packet;
    packet->msg.command = A_WRTE;
    packet->msg.arg0 = localid;
    packet->msg.arg1 = usbd_adb_get_remoteid(localid);
    packet->msg.data_length = len;
    memcpy(packet->payload, data, len);

    packet->msg.data_crc32 = adb_packet_checksum(packet);
    packet->msg.magic = packet->msg.command ^ 0xffffffff;

    adb_client.write_state = ADB_STATE_AWRITE_MSG;
    usbd_ep_start_write(0, adb_ep_data[ADB_IN_EP_IDX].ep_addr, (uint8_t *)&packet->msg, sizeof(struct adb_msg));
    return 0;
}

void usbd_adb_close(uint32_t localid)
{
    adb_send_close(&tx_packet, 0, usbd_adb_get_remoteid(localid));
}