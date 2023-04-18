/*
 * COPYRIGHT (C) 2011-2023, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-31     aozima       the first version
 * 2014-09-18     aozima       update command & response.
 */

#ifndef SPI_WIFI_H_INCLUDED
#define SPI_WIFI_H_INCLUDED

#include <stdint.h>

// little-endian
struct spi_cmd_request
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
struct spi_response
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
#define SPI_MAX_DATA_LEN    1520
#define SPI_TX_POOL_SIZE    2
#define SPI_RX_POOL_SIZE    2

typedef enum
{
    data_type_eth_data = 0,
    data_type_cmd,
    data_type_resp,
    data_type_status,
}
app_data_type_typedef;

struct spi_data_packet
{
    uint32_t data_len;
    uint32_t data_type;
    char buffer[SPI_MAX_DATA_LEN];
};

/********************************* RW009 **************************************/

/* option */
#define RW009_CMD_TIMEOUT           (RT_TICK_PER_SECOND*3)
#define SSID_NAME_LENGTH_MAX        (32)
#define PASSWORD_LENGTH_MAX         (64)

typedef enum
{
    MODE_STATION=0,
    MODE_SOFTAP=1,
} wifi_mode_t;

typedef struct _rw009_ap_info
{
    char        ssid[SSID_NAME_LENGTH_MAX];
    uint8_t     bssid[8]; // 6byte + 2byte PAD.
    int         rssi;               /* Receive Signal Strength Indication in dBm. */
    uint32_t    max_data_rate;      /* Maximum data rate in kilobits/s */
    uint32_t    security;           /* Security type  */
    uint32_t    channel;            /* Radio channel that the AP beacon was received on   */
} rw009_ap_info;

typedef struct _rw009_cmd_init
{
    uint32_t mode;
} rw009_cmd_init;

typedef struct _rw009_resp_init
{
    uint8_t mac[8];     // 6byte + 2byte PAD.
    uint8_t sn[24];     // serial.
    char version[16];   // firmware version.
} rw009_resp_init;

typedef struct _rw009_cmd_easy_join
{
    char ssid[SSID_NAME_LENGTH_MAX];
    char passwd[PASSWORD_LENGTH_MAX];
} rw009_cmd_easy_join;

typedef struct _rw009_cmd_join
{
    uint8_t bssid[8]; // 6byte + 2byte PAD.
    char passwd[PASSWORD_LENGTH_MAX];
} rw009_cmd_join;

typedef struct _rw009_cmd_rssi
{
    uint8_t bssid[8]; // 6byte + 2byte PAD.
} rw009_cmd_rssi;

typedef struct _rw009_cmd_softap
{
    char ssid[SSID_NAME_LENGTH_MAX];
    char passwd[PASSWORD_LENGTH_MAX];

    uint32_t    security;           /* Security type. */
    uint32_t    channel;            /* Radio channel that the AP beacon was received on   */
} rw009_cmd_softap;

typedef struct _rw009_resp_join
{
    rw009_ap_info ap_info;
} rw009_resp_join;

struct rw009_cmd
{
    uint32_t cmd;
    uint32_t len;

    /** command body */
    union
    {
        rw009_cmd_init init;
        rw009_cmd_easy_join easy_join;
        rw009_cmd_join join;
        rw009_cmd_rssi rssi;
        rw009_cmd_softap softap;
    } params;
};

struct rw009_resp
{
    uint32_t cmd;
    uint32_t len;

    int32_t result; // result for CMD.

    /** resp Body */
    union
    {
        rw009_resp_init init;
        rw009_ap_info ap_info;
    } resp;
};

#define RW009_CMD_INIT              128
#define RW009_CMD_SCAN              129
#define RW009_CMD_JOIN              130
#define RW009_CMD_EASY_JOIN         131
#define RW009_CMD_RSSI              132
#define RW009_CMD_SOFTAP            133

/** cond !ADDTHIS*/
#define SHARED_ENABLED  0x00008000
#define WPA_SECURITY    0x00200000
#define WPA2_SECURITY   0x00400000
#define WPS_ENABLED     0x10000000
#define WEP_ENABLED        0x0001
#define TKIP_ENABLED        0x0002
#define AES_ENABLED        0x0004
#define WSEC_SWFLAG        0x0008
/** endcond */
/**
 * Enumeration of Wi-Fi security modes
 */
typedef enum
{
    SECURITY_OPEN           = 0,                                                /**< Open security                           */
    SECURITY_WEP_PSK        = WEP_ENABLED,                                      /**< WEP Security with open authentication   */
    SECURITY_WEP_SHARED     = ( WEP_ENABLED | SHARED_ENABLED ),                 /**< WEP Security with shared authentication */
    SECURITY_WPA_TKIP_PSK   = ( WPA_SECURITY  | TKIP_ENABLED ),                 /**< WPA Security with TKIP                  */
    SECURITY_WPA_AES_PSK    = ( WPA_SECURITY  | AES_ENABLED ),                  /**< WPA Security with AES                   */
    SECURITY_WPA2_AES_PSK   = ( WPA2_SECURITY | AES_ENABLED ),                  /**< WPA2 Security with AES                  */
    SECURITY_WPA2_TKIP_PSK  = ( WPA2_SECURITY | TKIP_ENABLED ),                 /**< WPA2 Security with TKIP                 */
    SECURITY_WPA2_MIXED_PSK = ( WPA2_SECURITY | AES_ENABLED | TKIP_ENABLED ),   /**< WPA2 Security with AES & TKIP           */

    SECURITY_WPS_OPEN       = WPS_ENABLED,                                      /**< WPS with open security                  */
    SECURITY_WPS_SECURE     = (WPS_ENABLED | AES_ENABLED),                      /**< WPS with AES security                   */

    SECURITY_UNKNOWN        = -1,                                               /**< May be returned by scan function if security is unknown. Do not pass this to the join function! */

    SECURITY_FORCE_32_BIT   = 0x7fffffff                                        /**< Exists only to force wiced_security_t type to 32 bits */
} security_t;

/* porting */
extern void spi_wifi_hw_init(void);
extern void spi_wifi_int_cmd(rt_bool_t cmd);
extern rt_bool_t spi_wifi_is_busy(void);

/* export API. */
extern rt_err_t rt_hw_wifi_init(const char *spi_device_name,wifi_mode_t mode);
extern int32_t rw009_rssi(void);
extern rt_err_t rw009_join(const char * SSID, const char * passwd);
extern rt_err_t rw009_softap(const char * SSID, const char * passwd,uint32_t security,uint32_t channel);

#endif // SPI_WIFI_H_INCLUDED
