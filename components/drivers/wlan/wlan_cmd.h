#ifndef WLAN_CMD_H__
#define WLAN_CMD_H__

struct netif;

int wifi_get_mode(void);
int wifi_set_mode(int mode);

/* do the wifi default action: read wifi setting and then join or start soft-AP */
int wifi_default(void);
/* setup netif for soft-ap */
int wifi_softap_setup_netif(struct netif *netif);

int wifi_set_setting(const char* ssid, const char* pwd);

#ifdef PKG_USING_CJSON
int wifi_read_cfg(const char* filename);
int wifi_save_cfg(const char* filename);
#endif
/* save wifi setting with default storage file */
int wifi_save_setting(void);

extern struct rt_wlan_info info;

#endif
