/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-03     tyx          the first version
 */

#ifndef __WLAN_DEVICE_H__
#define __WLAN_DEVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    RT_WLAN_NONE,
    RT_WLAN_STATION,
    RT_WLAN_AP,
    RT_WLAN_MODE_MAX
} rt_wlan_mode_t;

typedef enum
{
    RT_WLAN_CMD_MODE = 0x10,
    RT_WLAN_CMD_SCAN,              /* trigger scanning (list cells) */
    RT_WLAN_CMD_JOIN,
    RT_WLAN_CMD_SOFTAP,            /* start soft-AP */
    RT_WLAN_CMD_DISCONNECT,
    RT_WLAN_CMD_AP_STOP,           /* stop soft-AP */
    RT_WLAN_CMD_AP_DEAUTH,
    RT_WLAN_CMD_SCAN_STOP,
    RT_WLAN_CMD_GET_RSSI,          /* get sensitivity (dBm) */
    RT_WLAN_CMD_SET_POWERSAVE,
    RT_WLAN_CMD_GET_POWERSAVE,
    RT_WLAN_CMD_CFG_PROMISC,       /* start/stop minitor */
    RT_WLAN_CMD_CFG_FILTER,        /* start/stop frame filter */
    RT_WLAN_CMD_CFG_MGNT_FILTER,   /* start/stop management frame filter */
    RT_WLAN_CMD_SET_CHANNEL,
    RT_WLAN_CMD_GET_CHANNEL,
    RT_WLAN_CMD_SET_COUNTRY,
    RT_WLAN_CMD_GET_COUNTRY,
    RT_WLAN_CMD_SET_MAC,
    RT_WLAN_CMD_GET_MAC
} rt_wlan_cmd_t;

typedef enum
{
    RT_WLAN_DEV_EVT_INIT_DONE = 0,
    RT_WLAN_DEV_EVT_CONNECT,
    RT_WLAN_DEV_EVT_CONNECT_FAIL,
    RT_WLAN_DEV_EVT_DISCONNECT,
    RT_WLAN_DEV_EVT_AP_START,
    RT_WLAN_DEV_EVT_AP_STOP,
    RT_WLAN_DEV_EVT_AP_ASSOCIATED,
    RT_WLAN_DEV_EVT_AP_DISASSOCIATED,
    RT_WLAN_DEV_EVT_AP_ASSOCIATE_FAILED,
    RT_WLAN_DEV_EVT_SCAN_REPORT,
    RT_WLAN_DEV_EVT_SCAN_DONE,
    RT_WLAN_DEV_EVT_MAX,
} rt_wlan_dev_event_t;

#define SHARED_ENABLED  0x00008000
#define WPA_SECURITY    0x00200000
#define WPA2_SECURITY   0x00400000
#define WPS_ENABLED     0x10000000
#define WEP_ENABLED     0x0001
#define TKIP_ENABLED    0x0002
#define AES_ENABLED     0x0004
#define WSEC_SWFLAG     0x0008

#define RT_WLAN_FLAG_STA_ONLY    (0x1 << 0)
#define RT_WLAN_FLAG_AP_ONLY     (0x1 << 1)

#ifndef RT_WLAN_SSID_MAX_LENGTH
#define RT_WLAN_SSID_MAX_LENGTH  (32)   /* SSID MAX LEN */
#endif

#ifndef RT_WLAN_BSSID_MAX_LENGTH
#define RT_WLAN_BSSID_MAX_LENGTH (6)    /* BSSID MAX LEN (default is 6) */
#endif

#ifndef RT_WLAN_PASSWORD_MAX_LENGTH
#define RT_WLAN_PASSWORD_MAX_LENGTH   (32)   /* PASSWORD MAX LEN*/
#endif

#ifndef RT_WLAN_DEV_EVENT_NUM
#define RT_WLAN_DEV_EVENT_NUM  (2)   /* EVENT GROUP MAX NUM */
#endif

/**
 * Enumeration of Wi-Fi security modes
 */
typedef enum
{
    SECURITY_OPEN           = 0,                                                /* Open security                           */
    SECURITY_WEP_PSK        = WEP_ENABLED,                                      /* WEP Security with open authentication   */
    SECURITY_WEP_SHARED     = (WEP_ENABLED | SHARED_ENABLED),                   /* WEP Security with shared authentication */
    SECURITY_WPA_TKIP_PSK   = (WPA_SECURITY  | TKIP_ENABLED),                   /* WPA Security with TKIP                  */
    SECURITY_WPA_AES_PSK    = (WPA_SECURITY  | AES_ENABLED),                    /* WPA Security with AES                   */
    SECURITY_WPA2_AES_PSK   = (WPA2_SECURITY | AES_ENABLED),                    /* WPA2 Security with AES                  */
    SECURITY_WPA2_TKIP_PSK  = (WPA2_SECURITY | TKIP_ENABLED),                   /* WPA2 Security with TKIP                 */
    SECURITY_WPA2_MIXED_PSK = (WPA2_SECURITY | AES_ENABLED | TKIP_ENABLED),     /* WPA2 Security with AES & TKIP           */
    SECURITY_WPS_OPEN       = WPS_ENABLED,                                      /* WPS with open security                  */
    SECURITY_WPS_SECURE     = (WPS_ENABLED | AES_ENABLED),                      /* WPS with AES security                   */
    SECURITY_UNKNOWN        = -1,                                               /* May be returned by scan function if security is unknown.
                                                                                    Do not pass this to the join function! */
} rt_wlan_security_t;

typedef enum
{
    RT_802_11_BAND_5GHZ  =  0,             /* Denotes 5GHz radio band   */
    RT_802_11_BAND_2_4GHZ =  1,            /* Denotes 2.4GHz radio band */
    RT_802_11_BAND_UNKNOWN = 0x7fffffff,   /* unknown */
} rt_802_11_band_t;

typedef enum
{
    RT_COUNTRY_AFGHANISTAN,
    RT_COUNTRY_ALBANIA,
    RT_COUNTRY_ALGERIA,
    RT_COUNTRY_AMERICAN_SAMOA,
    RT_COUNTRY_ANGOLA,
    RT_COUNTRY_ANGUILLA,
    RT_COUNTRY_ANTIGUA_AND_BARBUDA,
    RT_COUNTRY_ARGENTINA,
    RT_COUNTRY_ARMENIA,
    RT_COUNTRY_ARUBA,
    RT_COUNTRY_AUSTRALIA,
    RT_COUNTRY_AUSTRIA,
    RT_COUNTRY_AZERBAIJAN,
    RT_COUNTRY_BAHAMAS,
    RT_COUNTRY_BAHRAIN,
    RT_COUNTRY_BAKER_ISLAND,
    RT_COUNTRY_BANGLADESH,
    RT_COUNTRY_BARBADOS,
    RT_COUNTRY_BELARUS,
    RT_COUNTRY_BELGIUM,
    RT_COUNTRY_BELIZE,
    RT_COUNTRY_BENIN,
    RT_COUNTRY_BERMUDA,
    RT_COUNTRY_BHUTAN,
    RT_COUNTRY_BOLIVIA,
    RT_COUNTRY_BOSNIA_AND_HERZEGOVINA,
    RT_COUNTRY_BOTSWANA,
    RT_COUNTRY_BRAZIL,
    RT_COUNTRY_BRITISH_INDIAN_OCEAN_TERRITORY,
    RT_COUNTRY_BRUNEI_DARUSSALAM,
    RT_COUNTRY_BULGARIA,
    RT_COUNTRY_BURKINA_FASO,
    RT_COUNTRY_BURUNDI,
    RT_COUNTRY_CAMBODIA,
    RT_COUNTRY_CAMEROON,
    RT_COUNTRY_CANADA,
    RT_COUNTRY_CAPE_VERDE,
    RT_COUNTRY_CAYMAN_ISLANDS,
    RT_COUNTRY_CENTRAL_AFRICAN_REPUBLIC,
    RT_COUNTRY_CHAD,
    RT_COUNTRY_CHILE,
    RT_COUNTRY_CHINA,
    RT_COUNTRY_CHRISTMAS_ISLAND,
    RT_COUNTRY_COLOMBIA,
    RT_COUNTRY_COMOROS,
    RT_COUNTRY_CONGO,
    RT_COUNTRY_CONGO_THE_DEMOCRATIC_REPUBLIC_OF_THE,
    RT_COUNTRY_COSTA_RICA,
    RT_COUNTRY_COTE_DIVOIRE,
    RT_COUNTRY_CROATIA,
    RT_COUNTRY_CUBA,
    RT_COUNTRY_CYPRUS,
    RT_COUNTRY_CZECH_REPUBLIC,
    RT_COUNTRY_DENMARK,
    RT_COUNTRY_DJIBOUTI,
    RT_COUNTRY_DOMINICA,
    RT_COUNTRY_DOMINICAN_REPUBLIC,
    RT_COUNTRY_DOWN_UNDER,
    RT_COUNTRY_ECUADOR,
    RT_COUNTRY_EGYPT,
    RT_COUNTRY_EL_SALVADOR,
    RT_COUNTRY_EQUATORIAL_GUINEA,
    RT_COUNTRY_ERITREA,
    RT_COUNTRY_ESTONIA,
    RT_COUNTRY_ETHIOPIA,
    RT_COUNTRY_FALKLAND_ISLANDS_MALVINAS,
    RT_COUNTRY_FAROE_ISLANDS,
    RT_COUNTRY_FIJI,
    RT_COUNTRY_FINLAND,
    RT_COUNTRY_FRANCE,
    RT_COUNTRY_FRENCH_GUINA,
    RT_COUNTRY_FRENCH_POLYNESIA,
    RT_COUNTRY_FRENCH_SOUTHERN_TERRITORIES,
    RT_COUNTRY_GABON,
    RT_COUNTRY_GAMBIA,
    RT_COUNTRY_GEORGIA,
    RT_COUNTRY_GERMANY,
    RT_COUNTRY_GHANA,
    RT_COUNTRY_GIBRALTAR,
    RT_COUNTRY_GREECE,
    RT_COUNTRY_GRENADA,
    RT_COUNTRY_GUADELOUPE,
    RT_COUNTRY_GUAM,
    RT_COUNTRY_GUATEMALA,
    RT_COUNTRY_GUERNSEY,
    RT_COUNTRY_GUINEA,
    RT_COUNTRY_GUINEA_BISSAU,
    RT_COUNTRY_GUYANA,
    RT_COUNTRY_HAITI,
    RT_COUNTRY_HOLY_SEE_VATICAN_CITY_STATE,
    RT_COUNTRY_HONDURAS,
    RT_COUNTRY_HONG_KONG,
    RT_COUNTRY_HUNGARY,
    RT_COUNTRY_ICELAND,
    RT_COUNTRY_INDIA,
    RT_COUNTRY_INDONESIA,
    RT_COUNTRY_IRAN_ISLAMIC_REPUBLIC_OF,
    RT_COUNTRY_IRAQ,
    RT_COUNTRY_IRELAND,
    RT_COUNTRY_ISRAEL,
    RT_COUNTRY_ITALY,
    RT_COUNTRY_JAMAICA,
    RT_COUNTRY_JAPAN,
    RT_COUNTRY_JERSEY,
    RT_COUNTRY_JORDAN,
    RT_COUNTRY_KAZAKHSTAN,
    RT_COUNTRY_KENYA,
    RT_COUNTRY_KIRIBATI,
    RT_COUNTRY_KOREA_REPUBLIC_OF,
    RT_COUNTRY_KOSOVO,
    RT_COUNTRY_KUWAIT,
    RT_COUNTRY_KYRGYZSTAN,
    RT_COUNTRY_LAO_PEOPLES_DEMOCRATIC_REPUBIC,
    RT_COUNTRY_LATVIA,
    RT_COUNTRY_LEBANON,
    RT_COUNTRY_LESOTHO,
    RT_COUNTRY_LIBERIA,
    RT_COUNTRY_LIBYAN_ARAB_JAMAHIRIYA,
    RT_COUNTRY_LIECHTENSTEIN,
    RT_COUNTRY_LITHUANIA,
    RT_COUNTRY_LUXEMBOURG,
    RT_COUNTRY_MACAO,
    RT_COUNTRY_MACEDONIA_FORMER_YUGOSLAV_REPUBLIC_OF,
    RT_COUNTRY_MADAGASCAR,
    RT_COUNTRY_MALAWI,
    RT_COUNTRY_MALAYSIA,
    RT_COUNTRY_MALDIVES,
    RT_COUNTRY_MALI,
    RT_COUNTRY_MALTA,
    RT_COUNTRY_MAN_ISLE_OF,
    RT_COUNTRY_MARTINIQUE,
    RT_COUNTRY_MAURITANIA,
    RT_COUNTRY_MAURITIUS,
    RT_COUNTRY_MAYOTTE,
    RT_COUNTRY_MEXICO,
    RT_COUNTRY_MICRONESIA_FEDERATED_STATES_OF,
    RT_COUNTRY_MOLDOVA_REPUBLIC_OF,
    RT_COUNTRY_MONACO,
    RT_COUNTRY_MONGOLIA,
    RT_COUNTRY_MONTENEGRO,
    RT_COUNTRY_MONTSERRAT,
    RT_COUNTRY_MOROCCO,
    RT_COUNTRY_MOZAMBIQUE,
    RT_COUNTRY_MYANMAR,
    RT_COUNTRY_NAMIBIA,
    RT_COUNTRY_NAURU,
    RT_COUNTRY_NEPAL,
    RT_COUNTRY_NETHERLANDS,
    RT_COUNTRY_NETHERLANDS_ANTILLES,
    RT_COUNTRY_NEW_CALEDONIA,
    RT_COUNTRY_NEW_ZEALAND,
    RT_COUNTRY_NICARAGUA,
    RT_COUNTRY_NIGER,
    RT_COUNTRY_NIGERIA,
    RT_COUNTRY_NORFOLK_ISLAND,
    RT_COUNTRY_NORTHERN_MARIANA_ISLANDS,
    RT_COUNTRY_NORWAY,
    RT_COUNTRY_OMAN,
    RT_COUNTRY_PAKISTAN,
    RT_COUNTRY_PALAU,
    RT_COUNTRY_PANAMA,
    RT_COUNTRY_PAPUA_NEW_GUINEA,
    RT_COUNTRY_PARAGUAY,
    RT_COUNTRY_PERU,
    RT_COUNTRY_PHILIPPINES,
    RT_COUNTRY_POLAND,
    RT_COUNTRY_PORTUGAL,
    RT_COUNTRY_PUETO_RICO,
    RT_COUNTRY_QATAR,
    RT_COUNTRY_REUNION,
    RT_COUNTRY_ROMANIA,
    RT_COUNTRY_RUSSIAN_FEDERATION,
    RT_COUNTRY_RWANDA,
    RT_COUNTRY_SAINT_KITTS_AND_NEVIS,
    RT_COUNTRY_SAINT_LUCIA,
    RT_COUNTRY_SAINT_PIERRE_AND_MIQUELON,
    RT_COUNTRY_SAINT_VINCENT_AND_THE_GRENADINES,
    RT_COUNTRY_SAMOA,
    RT_COUNTRY_SANIT_MARTIN_SINT_MARTEEN,
    RT_COUNTRY_SAO_TOME_AND_PRINCIPE,
    RT_COUNTRY_SAUDI_ARABIA,
    RT_COUNTRY_SENEGAL,
    RT_COUNTRY_SERBIA,
    RT_COUNTRY_SEYCHELLES,
    RT_COUNTRY_SIERRA_LEONE,
    RT_COUNTRY_SINGAPORE,
    RT_COUNTRY_SLOVAKIA,
    RT_COUNTRY_SLOVENIA,
    RT_COUNTRY_SOLOMON_ISLANDS,
    RT_COUNTRY_SOMALIA,
    RT_COUNTRY_SOUTH_AFRICA,
    RT_COUNTRY_SPAIN,
    RT_COUNTRY_SRI_LANKA,
    RT_COUNTRY_SURINAME,
    RT_COUNTRY_SWAZILAND,
    RT_COUNTRY_SWEDEN,
    RT_COUNTRY_SWITZERLAND,
    RT_COUNTRY_SYRIAN_ARAB_REPUBLIC,
    RT_COUNTRY_TAIWAN_PROVINCE_OF_CHINA,
    RT_COUNTRY_TAJIKISTAN,
    RT_COUNTRY_TANZANIA_UNITED_REPUBLIC_OF,
    RT_COUNTRY_THAILAND,
    RT_COUNTRY_TOGO,
    RT_COUNTRY_TONGA,
    RT_COUNTRY_TRINIDAD_AND_TOBAGO,
    RT_COUNTRY_TUNISIA,
    RT_COUNTRY_TURKEY,
    RT_COUNTRY_TURKMENISTAN,
    RT_COUNTRY_TURKS_AND_CAICOS_ISLANDS,
    RT_COUNTRY_TUVALU,
    RT_COUNTRY_UGANDA,
    RT_COUNTRY_UKRAINE,
    RT_COUNTRY_UNITED_ARAB_EMIRATES,
    RT_COUNTRY_UNITED_KINGDOM,
    RT_COUNTRY_UNITED_STATES,
    RT_COUNTRY_UNITED_STATES_REV4,
    RT_COUNTRY_UNITED_STATES_NO_DFS,
    RT_COUNTRY_UNITED_STATES_MINOR_OUTLYING_ISLANDS,
    RT_COUNTRY_URUGUAY,
    RT_COUNTRY_UZBEKISTAN,
    RT_COUNTRY_VANUATU,
    RT_COUNTRY_VENEZUELA,
    RT_COUNTRY_VIET_NAM,
    RT_COUNTRY_VIRGIN_ISLANDS_BRITISH,
    RT_COUNTRY_VIRGIN_ISLANDS_US,
    RT_COUNTRY_WALLIS_AND_FUTUNA,
    RT_COUNTRY_WEST_BANK,
    RT_COUNTRY_WESTERN_SAHARA,
    RT_COUNTRY_WORLD_WIDE_XX,
    RT_COUNTRY_YEMEN,
    RT_COUNTRY_ZAMBIA,
    RT_COUNTRY_ZIMBABWE,
    RT_COUNTRY_UNKNOWN
} rt_country_code_t;

struct rt_wlan_device;
struct rt_wlan_buff;

typedef void (*rt_wlan_dev_event_handler)(struct rt_wlan_device *device, rt_wlan_dev_event_t event, struct rt_wlan_buff *buff, void *parameter);

typedef void (*rt_wlan_pormisc_callback_t)(struct rt_wlan_device *device, void *data, int len);

typedef void (*rt_wlan_mgnt_filter_callback_t)(struct rt_wlan_device *device, void *data, int len);

struct rt_wlan_ssid
{
    rt_uint8_t len;
    rt_uint8_t val[RT_WLAN_SSID_MAX_LENGTH + 1];
};
typedef struct rt_wlan_ssid rt_wlan_ssid_t;

struct rt_wlan_key
{
    rt_uint8_t len;
    rt_uint8_t val[RT_WLAN_PASSWORD_MAX_LENGTH + 1];
};
typedef struct rt_wlan_key rt_wlan_key_t;

#define INVALID_INFO(_info)       do {    \
                                        rt_memset((_info), 0, sizeof(struct rt_wlan_info)); \
                                        (_info)->band = RT_802_11_BAND_UNKNOWN; \
                                        (_info)->security = SECURITY_UNKNOWN; \
                                        (_info)->channel = -1; \
                                    } while(0)

#define SSID_SET(_info, _ssid)    do {    \
                                        rt_strncpy((char *)(_info)->ssid.val, (_ssid), RT_WLAN_SSID_MAX_LENGTH); \
                                        (_info)->ssid.len = rt_strlen((char *)(_info)->ssid.val); \
                                    } while(0)

struct rt_wlan_info
{
    /* security type */
    rt_wlan_security_t security;
    /* 2.4G/5G */
    rt_802_11_band_t band;
    /* maximal data rate */
    rt_uint32_t datarate;
    /* radio channel */
    rt_int16_t channel;
    /* signal strength */
    rt_int16_t  rssi;
    /* ssid */
    rt_wlan_ssid_t ssid;
    /* hwaddr */
    rt_uint8_t bssid[RT_WLAN_BSSID_MAX_LENGTH];
    rt_uint8_t hidden;
};

struct rt_wlan_buff
{
    void *data;
    rt_int32_t len;
};

struct rt_filter_pattern
{
    rt_uint16_t offset;     /* Offset in bytes to start filtering (referenced to the start of the ethernet packet) */
    rt_uint16_t mask_size;  /* Size of the mask in bytes */
    rt_uint8_t *mask;       /* Pattern mask bytes to be ANDed with the pattern eg. "\xff00" (must be in network byte order) */
    rt_uint8_t *pattern;    /* Pattern bytes used to filter eg. "\x0800"  (must be in network byte order) */
};

typedef enum
{
    RT_POSITIVE_MATCHING  = 0, /* Receive the data matching with this pattern and discard the other data  */
    RT_NEGATIVE_MATCHING  = 1  /* Discard the data matching with this pattern and receive the other data */
} rt_filter_rule_t;

struct rt_wlan_filter
{
    struct rt_filter_pattern patt;
    rt_filter_rule_t rule;
    rt_uint8_t enable;
};

struct rt_wlan_dev_event_desc
{
    rt_wlan_dev_event_handler handler;
    void *parameter;
};

struct rt_wlan_device
{
    struct rt_device device;
    rt_wlan_mode_t mode;
    struct rt_mutex lock;
    struct rt_wlan_dev_event_desc handler_table[RT_WLAN_DEV_EVT_MAX][RT_WLAN_DEV_EVENT_NUM];
    rt_wlan_pormisc_callback_t pormisc_callback;
    rt_wlan_mgnt_filter_callback_t mgnt_filter_callback;
    const struct rt_wlan_dev_ops *ops;
    rt_uint32_t flags;
    struct netdev *netdev;
    void *prot;
    void *user_data;
};

struct rt_sta_info
{
    rt_wlan_ssid_t ssid;
    rt_wlan_key_t key;
    rt_uint8_t bssid[6];
    rt_uint16_t channel;
    rt_wlan_security_t security;
};

struct rt_ap_info
{
    rt_wlan_ssid_t ssid;
    rt_wlan_key_t key;
    rt_bool_t hidden;
    rt_uint16_t channel;
    rt_wlan_security_t security;
};

struct rt_scan_info
{
    rt_wlan_ssid_t ssid;
    rt_uint8_t bssid[6];
    rt_int16_t channel_min;
    rt_int16_t channel_max;
    rt_bool_t passive;
};

struct rt_wlan_dev_ops
{
    rt_err_t (*wlan_init)(struct rt_wlan_device *wlan);
    rt_err_t (*wlan_mode)(struct rt_wlan_device *wlan, rt_wlan_mode_t mode);
    rt_err_t (*wlan_scan)(struct rt_wlan_device *wlan, struct rt_scan_info *scan_info);
    rt_err_t (*wlan_join)(struct rt_wlan_device *wlan, struct rt_sta_info *sta_info);
    rt_err_t (*wlan_softap)(struct rt_wlan_device *wlan, struct rt_ap_info *ap_info);
    rt_err_t (*wlan_disconnect)(struct rt_wlan_device *wlan);
    rt_err_t (*wlan_ap_stop)(struct rt_wlan_device *wlan);
    rt_err_t (*wlan_ap_deauth)(struct rt_wlan_device *wlan, rt_uint8_t mac[]);
    rt_err_t (*wlan_scan_stop)(struct rt_wlan_device *wlan);
    int (*wlan_get_rssi)(struct rt_wlan_device *wlan);
    rt_err_t (*wlan_set_powersave)(struct rt_wlan_device *wlan, int level);
    int (*wlan_get_powersave)(struct rt_wlan_device *wlan);
    rt_err_t (*wlan_cfg_promisc)(struct rt_wlan_device *wlan, rt_bool_t start);
    rt_err_t (*wlan_cfg_filter)(struct rt_wlan_device *wlan, struct rt_wlan_filter *filter);
    rt_err_t (*wlan_cfg_mgnt_filter)(struct rt_wlan_device *wlan, rt_bool_t start);
    rt_err_t (*wlan_set_channel)(struct rt_wlan_device *wlan, int channel);
    int (*wlan_get_channel)(struct rt_wlan_device *wlan);
    rt_err_t (*wlan_set_country)(struct rt_wlan_device *wlan, rt_country_code_t country_code);
    rt_country_code_t (*wlan_get_country)(struct rt_wlan_device *wlan);
    rt_err_t (*wlan_set_mac)(struct rt_wlan_device *wlan, rt_uint8_t mac[]);
    rt_err_t (*wlan_get_mac)(struct rt_wlan_device *wlan, rt_uint8_t mac[]);
    int (*wlan_recv)(struct rt_wlan_device *wlan, void *buff, int len);
    int (*wlan_send)(struct rt_wlan_device *wlan, void *buff, int len);
    int (*wlan_send_raw_frame)(struct rt_wlan_device *wlan, void *buff, int len);
};

/*
 * wlan device init
 */
rt_err_t rt_wlan_dev_init(struct rt_wlan_device *device, rt_wlan_mode_t mode);

/*
 * wlan device station interface
 */
rt_err_t rt_wlan_dev_connect(struct rt_wlan_device *device, struct rt_wlan_info *info, const char *password, int password_len);
rt_err_t rt_wlan_dev_disconnect(struct rt_wlan_device *device);
int rt_wlan_dev_get_rssi(struct rt_wlan_device *device);

/*
 * wlan device ap interface
 */
rt_err_t rt_wlan_dev_ap_start(struct rt_wlan_device *device, struct rt_wlan_info *info, const char *password, int password_len);
rt_err_t rt_wlan_dev_ap_stop(struct rt_wlan_device *device);
rt_err_t rt_wlan_dev_ap_deauth(struct rt_wlan_device *device, rt_uint8_t mac[6]);

/*
 * wlan device scan interface
 */
rt_err_t rt_wlan_dev_scan(struct rt_wlan_device *device, struct rt_wlan_info *info);
rt_err_t rt_wlan_dev_scan_stop(struct rt_wlan_device *device);

/*
 * wlan device mac interface
 */
rt_err_t rt_wlan_dev_get_mac(struct rt_wlan_device *device, rt_uint8_t mac[6]);
rt_err_t rt_wlan_dev_set_mac(struct rt_wlan_device *device, rt_uint8_t mac[6]);

/*
 * wlan device powersave interface
 */
rt_err_t rt_wlan_dev_set_powersave(struct rt_wlan_device *device, int level);
int rt_wlan_dev_get_powersave(struct rt_wlan_device *device);

/*
 * wlan device event interface
 */
rt_err_t rt_wlan_dev_register_event_handler(struct rt_wlan_device *device, rt_wlan_dev_event_t event, rt_wlan_dev_event_handler handler, void *parameter);
rt_err_t rt_wlan_dev_unregister_event_handler(struct rt_wlan_device *device, rt_wlan_dev_event_t event, rt_wlan_dev_event_handler handler);
void rt_wlan_dev_indicate_event_handle(struct rt_wlan_device *device, rt_wlan_dev_event_t event, struct rt_wlan_buff *buff);

/*
 * wlan device promisc interface
 */
rt_err_t rt_wlan_dev_enter_promisc(struct rt_wlan_device *device);
rt_err_t rt_wlan_dev_exit_promisc(struct rt_wlan_device *device);
rt_err_t rt_wlan_dev_set_promisc_callback(struct rt_wlan_device *device, rt_wlan_pormisc_callback_t callback);
void rt_wlan_dev_promisc_handler(struct rt_wlan_device *device, void *data, int len);

/*
 * wlan device filter interface
 */
rt_err_t rt_wlan_dev_cfg_filter(struct rt_wlan_device *device, struct rt_wlan_filter *filter);

/*
 * wlan device channel interface
 */
rt_err_t rt_wlan_dev_set_channel(struct rt_wlan_device *device, int channel);
int rt_wlan_dev_get_channel(struct rt_wlan_device *device);

/*
 * wlan device country interface
 */
rt_err_t rt_wlan_dev_set_country(struct rt_wlan_device *device, rt_country_code_t country_code);
rt_country_code_t rt_wlan_dev_get_country(struct rt_wlan_device *device);

/*
 * wlan device datat transfer interface
 */
rt_err_t rt_wlan_dev_report_data(struct rt_wlan_device *device, void *buff, int len);
// void rt_wlan_dev_data_ready(struct rt_wlan_device *device, int len);

/*
 * wlan device register interface
 */
rt_err_t rt_wlan_dev_register(struct rt_wlan_device *wlan, const char *name,
    const struct rt_wlan_dev_ops *ops, rt_uint32_t flag, void *user_data);

#ifdef __cplusplus
}
#endif

#endif
