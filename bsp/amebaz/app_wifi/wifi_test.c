/*
 * File      : wifi_connect.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-01     flyingcys    add realtek ameba
 */

#include <rtthread.h>

#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "drv_wifi.h"

#include "wifi_structures.h"
#include "wireless.h"
#include "platform_opts.h"

/* fastconnect use wifi AT command. Not init_wifi_struct when log service disabled
 * static initialize all values for using fastconnect when log service disabled
 */
static rtw_network_info_t wifi = {
    {0},    // ssid
    {0},    // bssid
    0,      // security
    NULL,   // password
    0,      // password len
    -1      // key id
};

static rtw_ap_info_t ap = {0};
static unsigned char password[65] = {0};

static void init_wifi_struct(void)
{
    memset(wifi.ssid.val, 0, sizeof(wifi.ssid.val));
    memset(wifi.bssid.octet, 0, 6);  
    memset(password, 0, sizeof(password));
    wifi.ssid.len = 0;
    wifi.password = NULL;
    wifi.password_len = 0;
    wifi.key_id = -1;
    memset(ap.ssid.val, 0, sizeof(ap.ssid.val));
    ap.ssid.len = 0;
    ap.password = NULL;
    ap.password_len = 0;
    ap.channel = 1;
}

void wifi_start(void)
{
    init_wifi_struct();
    
    wifi_on(RTW_MODE_STA);
    wifi_set_autoreconnect(1);
}




void fATWC(void){
	int mode, ret;
	unsigned long tick1 = xTaskGetTickCount();
	unsigned long tick2, tick3;
	char empty_bssid[6] = {0}, assoc_by_bssid = 0;	
	
	printf("[ATWC]: _AT_WLAN_JOIN_NET_\n\r"); 
	if(memcmp (wifi.bssid.octet, empty_bssid, 6))
		assoc_by_bssid = 1;
	else if(wifi.ssid.val[0] == 0){
		printf("[ATWC]Error: SSID can't be empty\n\r");
		ret = RTW_BADARG;
		goto EXIT;
	}
	if(wifi.password != NULL){
		if((wifi.key_id >= 0)&&(wifi.key_id <= 3)) {
			wifi.security_type = RTW_SECURITY_WEP_PSK;
		}
		else{
			wifi.security_type = RTW_SECURITY_WPA2_AES_PSK;
		}
	}
	else{
		wifi.security_type = RTW_SECURITY_OPEN;
	}
	//Check if in AP mode
	wext_get_mode(WLAN0_NAME, &mode);
	if(mode == IW_MODE_MASTER) {
        #if 0
#if CONFIG_LWIP_LAYER
		dhcps_deinit();
#endif
		wifi_off();
		vTaskDelay(20);
		if (wifi_on(RTW_MODE_STA) < 0){
			printf("\n\rERROR: Wifi on failed!");
                        ret = RTW_ERROR;
			goto EXIT;
		}
        #endif
	}

#if CONFIG_INIC_EN //get security mode from scan list
	u8 connect_channel;
	u8 pscan_config;
	//the keyID may be not set for WEP which may be confued with WPA2 
	if((wifi.security_type == RTW_SECURITY_UNKNOWN)||(wifi.security_type == RTW_SECURITY_WPA2_AES_PSK))
	{
		int security_retry_count = 0;
		while (1) {
			if (_get_ap_security_mode((char*)wifi.ssid.val, &wifi.security_type, &connect_channel))
				break;
			security_retry_count++;
			if(security_retry_count >= 3){
				printf("Can't get AP security mode and channel.\n");
				ret = RTW_NOTFOUND;
				goto EXIT;
			}
		}
		if(wifi.security_type == RTW_SECURITY_WEP_PSK || wifi.security_type == RTW_SECURITY_WEP_SHARED)
			wifi.key_id = (wifi.key_id <0 || wifi.key_id >3)?0:wifi.key_id;
#if 0 //implemented in wifi_connect()
		//hex to ascii conversion
		if(wifi.security_type == RTW_SECURITY_WEP_PSK)
		{
			if(wifi.password_len == 10)
			{
				u32 p[5];
				u8 pwd[6], i = 0; 
				sscanf((const char*)wifi.password, "%02x%02x%02x%02x%02x", &p[0], &p[1], &p[2], &p[3], &p[4]);
				for(i=0; i< 5; i++)
					pwd[i] = (u8)p[i];
				pwd[5] = '\0';
				memset(wifi.password, 0, 65);
				strcpy((char*)wifi.password, (char*)pwd);
				wifi.password_len = 5;
			}else if(wifi.password_len == 26){
				u32 p[13];
				u8 pwd[14], i = 0;
				sscanf((const char*)wifi.password, "%02x%02x%02x%02x%02x%02x%02x"\
				"%02x%02x%02x%02x%02x%02x", &p[0], &p[1], &p[2], &p[3], &p[4],\
				&p[5], &p[6], &p[7], &p[8], &p[9], &p[10], &p[11], &p[12]);
				for(i=0; i< 13; i++)
					pwd[i] = (u8)p[i];
				pwd[13] = '\0';
				memset(wifi.password, 0, 65);
				strcpy((char*)wifi.password, (char*)pwd);
				wifi.password_len = 13;
			}
		}
#endif
	}
	pscan_config = PSCAN_ENABLE;
	if(connect_channel > 0 && connect_channel < 14)
		wifi_set_pscan_chan(&connect_channel, &pscan_config, 1);
#endif

	if(assoc_by_bssid){
//		printf("\n\rJoining BSS by BSSID \"MAC_FMT\" ...\n\r", MAC_ARG(wifi.bssid.octet));
		ret = wifi_connect_bssid(wifi.bssid.octet, (char*)wifi.ssid.val, wifi.security_type, (char*)wifi.password, 
						ETH_ALEN, wifi.ssid.len, wifi.password_len, wifi.key_id, NULL);		
	} else {
		printf("\n\rJoining BSS by SSID %s...\n\r", (char*)wifi.ssid.val);
		ret = wifi_connect((char*)wifi.ssid.val, wifi.security_type, (char*)wifi.password, wifi.ssid.len,
						wifi.password_len, wifi.key_id, NULL);
	}
	
	if(ret!= RTW_SUCCESS){
		if(ret == RTW_INVALID_KEY)
			printf("\n\rERROR:Invalid Key ");
		
		printf("\n\rERROR: Can't connect to AP");
		goto EXIT;
	}
	tick2 = xTaskGetTickCount();
	printf("\r\nConnected after %dms.\n", (tick2-tick1));
    
#if CONFIG_LWIP_LAYER
    netif_set_connected(1);
    dhcp_start(netif_default);
	tick3 = xTaskGetTickCount();
	printf("\r\n\nGot IP after %dms.\n", (tick3-tick1));
#endif
	printf("\n\r");
EXIT:

	init_wifi_struct( );
}

void connect(int argc, char *argv[])
{
    memset((char *)wifi.ssid.val, 0, sizeof((char *)wifi.ssid.val));
	strcpy((char *)wifi.ssid.val, WIFI_SSID);
	wifi.ssid.len = strlen((char *)wifi.ssid.val);

    //
    wifi.password = WIFI_PASSWORD;
    wifi.password_len = strlen((char*)wifi.password);

    rt_kprintf("ssid: %s password:%s\n", wifi.ssid.val, wifi.password);

    fATWC();

}
MSH_CMD_EXPORT(connect, wifi_connect);

