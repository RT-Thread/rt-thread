/*
 * File      : spi_wifi_rw009.h
 * This file is part of RT-Thread RTOS
 * Copyright by Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-31     aozima       the first version
 */

#ifndef SPI_WIFI_H_INCLUDED
#define SPI_WIFI_H_INCLUDED

#include <stdint.h>

// little-endian
struct cmd_request
{
    uint32_t flag;
    uint32_t M2S_len; // master to slave data len.
    uint32_t magic1;
    uint32_t magic2;
};

#define CMD_MAGIC1          (0x67452301)
#define CMD_MAGIC2          (0xEFCDAB89)

#define CMD_FLAG_MRDY       (0x01)

// little-endian
struct response
{
    uint32_t flag;
    uint32_t S2M_len; // slave to master data len.
    uint32_t magic1;
    uint32_t magic2;
};

#define RESP_FLAG_SRDY      (0x01)
#define RESP_MAGIC1         (0x98BADCFE)
#define RESP_MAGIC2         (0x10325476)

/* spi slave configure. */
#define MAX_DATA_LEN        1520
#define SPI_TX_POOL_SIZE    2

// align check
#if (MAX_DATA_LEN & 0x03) != 0
#error MAX_DATA_LEN must ALIGN to 4byte!
#endif

typedef enum
{
    data_type_eth_data = 0,
    data_type_cmd,
    data_type_resp,
}
app_data_type_typedef;

struct spi_data_packet
{
    uint32_t data_len;
    uint32_t data_type;
    char buffer[MAX_DATA_LEN];
};

struct spi_wifi_cmd
{
    uint32_t cmd;
    char buffer[128];
};

struct spi_wifi_resp
{
    uint32_t cmd;
    char buffer[128];
};

#define SPI_WIFI_CMD_INIT         128  //wait
#define SPI_WIFI_CMD_SCAN         129  //no wait
#define SPI_WIFI_CMD_JOIN         130  //no wait

/* porting */
extern void spi_wifi_hw_init(void);
extern void spi_wifi_int_cmd(rt_bool_t cmd);
extern rt_bool_t spi_wifi_is_busy(void);

/* tools */
#define node_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))
#define member_offset(type, member) \
    ((unsigned long)(&((type *)0)->member))

#define SSID_NAME_LENGTH_MAX        (32)
#define PASSWORD_LENGTH_MAX         (32)

struct cmd_join
{
    char ssid[SSID_NAME_LENGTH_MAX];
    char passwd[PASSWORD_LENGTH_MAX];

    uint8_t bssid[8]; // 6byte + 2byte PAD.

    uint32_t channel;
    uint32_t security;
};


#endif // SPI_WIFI_H_INCLUDED
