/*
 * File      : amebaz_wlan.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * 2017-5-30      Bernard      the first version
 * 2018-6-12      flyingcys    add amebaz wlan interface
 */
#include <rtthread.h>
#include <netif/ethernetif.h>

#include "wifi_structures.h"
#include "wifi_constants.h"
#include <wifi/wifi_util.h>
#include <wifi/wifi_conf.h>


#define     PASSWD_LEN          65
#define     SCAN_WAIT_TIME      10000

typedef enum
{
    WIFI_NONE,
    WIFI_STATION,
    WIFI_AP,
} rt_wlan_mode_t;

struct rt_wlan_info
{
    rt_wlan_mode_t mode;   /* wifi mode */
    rtw_security_t security;

    char *ssid;
    uint8_t bssid[6];

    /* maximal data rate */
    uint32_t datarate;
    /* radio channel */
    uint16_t channel;
    /* signal strength */
    int16_t  rssi;
};

typedef struct rt_wlan_scan_result
{
    char ap_num;
    struct rt_wlan_info *ap_table;
} rt_wlan_scan_result_t;


static rtw_network_info_t wifi_info = {0};
static rtw_ap_info_t ap_info = {0};
static unsigned char wifi_password[65] = {0};
static unsigned char ap_password[PASSWD_LEN] = {0};
static rt_sem_t scan_done_sem = RT_NULL;
static char *scan_buf = RT_NULL;
static int ApNum = 0;

extern struct netif *rltk_wlan_get_netif(int idx);

static void LwIP_ReleaseIP(uint8_t idx)
{
	struct ip_addr ipaddr;
	struct ip_addr netmask;
	struct ip_addr gw;
	struct netif *pnetif = rltk_wlan_get_netif(idx);
	
	IP4_ADDR(&ipaddr, 0, 0, 0, 0);
	IP4_ADDR(&netmask, 255, 255, 255, 0);
	IP4_ADDR(&gw, 0, 0, 0, 0);
	
	netif_set_addr(pnetif, &ipaddr , &netmask, &gw);
}

static rtw_result_t amebaz_scan_result_handler( rtw_scan_handler_result_t* malloced_scan_result )
{
	if (malloced_scan_result->scan_complete != RTW_TRUE) {
		rtw_scan_result_t* record = &malloced_scan_result->ap_details;
		record->SSID.val[record->SSID.len] = 0; /* Ensure the SSID is null terminated */

        ++ ApNum;
        
		if(malloced_scan_result->user_data)
			memcpy((void *)((char *)malloced_scan_result->user_data+(ApNum-1)*sizeof(rtw_scan_result_t)), (char *)record, sizeof(rtw_scan_result_t));
	} 
    else
    {
        rt_kprintf("ap num:%d\n", ApNum);

        if(scan_done_sem)
        {
            rt_sem_release(scan_done_sem);
        }
    }
    
	return RTW_SUCCESS;
}


static int amebaz_wifi_do_scan(void)
{
    int ret = RTW_SUCCESS;

    rt_kprintf("wifi scan start...\n");

	scan_buf = malloc(65*sizeof(rtw_scan_result_t));
	if(scan_buf == NULL){
		ret = RTW_BUFFER_UNAVAILABLE_TEMPORARY;
		return -RT_ENOMEM;
	}
    
	memset(scan_buf, 0, 65 * sizeof(rtw_scan_result_t));

    if((ret = wifi_scan_networks(amebaz_scan_result_handler, scan_buf)) != RTW_SUCCESS){
        rt_kprintf("ERROR: wifi scan failed\n\r");

        return -RT_ERROR;
    }

    return RT_EOK;
}

int amebaz_wifi_scan(struct rt_wlan_scan_result *dst)
{
    rt_uint32_t i;
    rt_uint32_t j = 0;
    
    scan_done_sem = rt_sem_create("scandone", 0, RT_IPC_FLAG_FIFO);
    if(scan_done_sem == RT_NULL)
        return -RT_ENOMEM;

    if(amebaz_wifi_do_scan() != RT_EOK)
    {
        rt_kprintf("amebaz_wifi_do_scan failed...\n");
        return -RT_ERROR;
    }

    if(rt_sem_take(scan_done_sem, rt_tick_from_millisecond(SCAN_WAIT_TIME)) != RT_EOK)
    {
        rt_kprintf("scan wait timeout...\n");
        return -RT_ETIMEOUT;
    } 

    if(scan_done_sem)
    {
        rt_sem_delete(scan_done_sem);
        scan_done_sem = RT_NULL;
    }

    rtw_scan_result_t *ptr = (rtw_scan_result_t *)scan_buf;
    dst->ap_num = ApNum;
    ApNum = 0;

    dst->ap_table = (struct rt_wlan_info *)rt_malloc(sizeof(struct rt_wlan_info) * dst->ap_num);
    if(dst->ap_table == RT_NULL)
    {
        rt_kprintf("rt_malloc for ap table failed...\n");
        goto __exit;
    }

    for(i = 0; i < dst->ap_num; i ++)
    {
        dst->ap_table[i].mode = 1;
        dst->ap_table[i].security = ptr->security;
        dst->ap_table[i].ssid = (char *)rt_malloc(33);
        if(dst->ap_table[i].ssid == RT_NULL)
        {
			rt_kprintf("rt_malloc for ssid Failed! times:%d,total:%d\n",i,ApNum);
            j = i;
            goto __exit;
        }

        memset(dst->ap_table[i].ssid, 0, 33);
        memcpy(dst->ap_table[i].ssid, ptr->SSID.val, ptr->SSID.len);
        memcpy(dst->ap_table[i].bssid, ptr->BSSID.octet, 6);
        dst->ap_table[i].datarate = 0;
        dst->ap_table[i].channel = ptr->channel;
        dst->ap_table[i].rssi = ptr->signal_strength;

        ptr ++;
    }

    if(scan_buf != RT_NULL)
    {
        rt_free(scan_buf);
        scan_buf = RT_NULL;
    }
    
    return RT_EOK;

__exit:
    
    if(scan_buf != RT_NULL)
    {
        rt_free(scan_buf);
        scan_buf = RT_NULL;
    }

    if(dst->ap_table)
    {
        for(i = 0; i < j; i ++)
            rt_free(dst->ap_table[i].ssid);
        rt_free(dst->ap_table);
        dst->ap_table = RT_NULL;
        dst->ap_num = 0;
    }

    return -RT_ERROR;
}

void amebaz_wifi_info_init(void)
{
    memset(wifi_info.ssid.val, 0, sizeof(wifi_info.ssid.val));
    memset(wifi_info.bssid.octet, 0, 6);  
    memset(wifi_password, 0, sizeof(wifi_password));
    wifi_info.ssid.len = 0;
    wifi_info.password = NULL;
    wifi_info.password_len = 0;
    wifi_info.key_id = -1;
    
    memset(ap_info.ssid.val, 0, sizeof(ap_info.ssid.val));
    ap_info.ssid.len = 0;
    ap_info.security_type = RTW_SECURITY_UNKNOWN;
    ap_info.password = NULL;
    ap_info.password_len = 0;
    ap_info.channel = 1;
}

static int amebaz_wifi_set_sta_info(char *ssid, char *passwd)
{
    if(ssid == RT_NULL || strlen(ssid) > 32)
    {
        rt_kprintf("Invalid argument...\n");
        return -RT_EINVAL;
    }

    strcpy(wifi_info.ssid.val, ssid);
    wifi_info.ssid.len = strlen(ssid);

    if(passwd != NULL)
    {
        if(strlen(passwd) > 64)
        {
            rt_kprintf("Invalid argument...\n");
            return -RT_EINVAL;
        }
        strcpy(wifi_password, passwd);
        wifi_info.password = wifi_password;
        wifi_info.password_len = strlen(passwd);
    }
    else
        wifi_info.password = RT_NULL;

    return RT_EOK;
}

static int amebaz_wifi_set_ap_info(char *ssid, char *passwd, int channel)
{
    if(ssid == RT_NULL || strlen(ssid) > 32)
    {
        rt_kprintf("Invalid argument...\n");
        return -RT_EINVAL;
    }

    strcpy(ap_info.ssid.val, ssid);
    ap_info.ssid.len = strlen(ssid);

    if(passwd != NULL)
    {
        if(strlen(passwd) > 64)
        {
            rt_kprintf("Invalid argument...\n");
            return -RT_EINVAL;
        }
        strcpy(ap_password, passwd);
        ap_info.password = ap_password;
        ap_info.password_len = strlen(passwd);
    }
    else
        ap_info.password = RT_NULL;

    ap_info.channel = channel;
    return RT_EOK;
}

static int amebaz_wifi_do_connect(void)
{
    int mode, ret;
    char empty_bssid[6] = {0};
    char assoc_by_bssid = 0;  
        
    rt_kprintf("amebaz wifi do connect start...\n"); 
    if(memcmp (wifi_info.bssid.octet, empty_bssid, 6))
    {
        assoc_by_bssid = 1;
    }
    else if(wifi_info.ssid.val[0] == 0)
    {
        ret = RTW_BADARG;
        return -RT_ERROR;
    }
    
    if(wifi_info.password != RT_NULL)
    {
        if((wifi_info.key_id >= 0) && (wifi_info.key_id <= 3))
        {
            wifi_info.security_type = RTW_SECURITY_WEP_PSK;
        }
        else
        {
            wifi_info.security_type = RTW_SECURITY_WPA2_AES_PSK;
        }
    }
    else
    {
        wifi_info.security_type = RTW_SECURITY_OPEN;
    }
    
    //Check if in AP mode
    wext_get_mode(WLAN0_NAME, &mode);
    if(mode == IW_MODE_MASTER)
    {
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

    if(assoc_by_bssid)
    {
        rt_kprintf("Joining BSS by BSSID \"MAC_FMT\" ...\n", MAC_ARG(wifi_info.bssid.octet));
        ret = wifi_connect_bssid(wifi_info.bssid.octet, (char*)wifi_info.ssid.val, wifi_info.security_type, (char*)wifi_info.password, 
                        ETH_ALEN, wifi_info.ssid.len, wifi_info.password_len, wifi_info.key_id, NULL);     
    } 
    else 
    {
        rt_kprintf("\n\rJoining BSS by SSID %s...\n\r", (char*)wifi_info.ssid.val);
        ret = wifi_connect((char*)wifi_info.ssid.val, wifi_info.security_type, 
                        (char*)wifi_info.password, wifi_info.ssid.len,
                        wifi_info.password_len, wifi_info.key_id, NULL);
    }
    
    if(ret!= RTW_SUCCESS)
    {
        if(ret == RTW_INVALID_KEY)
            rt_kprintf("ERROR:Invalid Key\n");
        
        rt_kprintf("ERROR: Can't connect to AP\n");
        return -RT_ERROR;
    }

    rt_kprintf("now start dhcp...\n");
    netif_set_connected(1);
    dhcp_start(netif_default);
    rt_kprintf("dhcp success...\n");
    
    return RT_EOK;
}

int amebaz_wifi_connect(char *ssid, char *passwd)
{
    int ret;

    ret = amebaz_wifi_set_sta_info(ssid, passwd);
    if(ret != RT_EOK)
    {
        amebaz_wifi_info_init();
        return ret;
    }
    
    if(amebaz_wifi_do_connect() != RT_EOK)
    {
        amebaz_wifi_info_init();
        rt_kprintf("amebaz_wifi_do_connect failed...\n");
        return -RT_ERROR;
    }

    amebaz_wifi_info_init();
    
    return RT_EOK;
}

static int amebaz_wifi_do_disconnect(void)
{
	int timeout = 20;
	char essid[33];
	int ret = RTW_SUCCESS;

	if(wext_get_ssid(WLAN0_NAME, (unsigned char *) essid) < 0) 
    {
		rt_kprintf("\nWIFI disconnected!\n");
        return -RT_ERROR;
	}

	if((ret = wifi_disconnect()) < 0) 
    {
        return -RT_ERROR;
	}

	while(1) 
    {
		if(wext_get_ssid(WLAN0_NAME, (unsigned char *) essid) < 0)
        {
			rt_kprintf("\nWIFI disconnected!\n");
			break;
		}

		if(timeout == 0) 
        {
			rt_kprintf("ERROR: Deassoc timeout!\n\r");
			ret = RTW_TIMEOUT;
			break;
		}

		vTaskDelay(10);
		timeout --;
	}

	LwIP_ReleaseIP(WLAN0_IDX);
    
    if(ret != RTW_SUCCESS)
        return -RT_ERROR;

    rt_kprintf("amebaz wifi do disconnect success...\n");
    return RT_EOK;
}

int amebaz_wifi_disconnect(void)
{
    int ret = RT_EOK;

    ret = amebaz_wifi_do_disconnect();
    if(ret != RT_EOK)
        rt_kprintf("amebaz_wifi_do_disconnect failed...\n");
    
    amebaz_wifi_info_init();

    return ret;
}

static int amebaz_wifi_do_ap_start(void)
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;
    struct netif *pnetif = rltk_wlan_get_netif(1);

    int timeout = 20;
    int ret = RTW_SUCCESS;
    
    if(ap_info.ssid.val[0] == 0){
        rt_kprintf("ERROR: SSID can't be empty\n\r");
        return -RT_ERROR;
    }
    
    if(ap_info.password == NULL)
    {
        ap_info.security_type = RTW_SECURITY_OPEN;
    }
    else
    {
        if(ap_info.password_len <= RTW_MAX_PSK_LEN && ap_info.password_len >= RTW_MIN_PSK_LEN)
        { 
            ap_info.security_type = RTW_SECURITY_WPA2_AES_PSK;
        }
        else
        {
            rt_kprintf("ERROR: password length is between 8 to 64 \n");
            return -RT_ERROR;
        }
    }
    
//#if CONFIG_LWIP_LAYER
//    dhcps_deinit();
//    IP4_ADDR(&ipaddr, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
//    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
//    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
//    netif_set_addr(pnetif, &ipaddr, &netmask,&gw);
//#ifdef CONFIG_DONT_CARE_TP
//        pnetif->flags |= NETIF_FLAG_IPSWITCH;
//#endif
//#endif

    wifi_off();
    vTaskDelay(20);
    if (wifi_on(RTW_MODE_AP) < 0)
    {
        rt_kprintf("ERROR: Wifi on failed!\n");
        return -RT_ERROR;
    }
    rt_kprintf("Now start AP mode...\n");

    if((ret = wifi_start_ap((char*)ap_info.ssid.val, ap_info.security_type, (char*)ap_info.password, ap_info.ssid.len, ap_info.password_len, ap_info.channel) ) < 0) 
    {
        rt_kprintf("ERROR: Operation failed!");
        return -RT_ERROR;
    }
    
    while(1) 
    {
        char essid[33];

        if(wext_get_ssid(WLAN0_NAME, (unsigned char *) essid) > 0) 
        {
            if(strcmp((const char *) essid, (const char *)ap_info.ssid.val) == 0) 
            {
                rt_kprintf("AP %s started...\n", ap_info.ssid.val);
                ret = RTW_SUCCESS;
                break;
            }
        }

        if(timeout == 0) 
        {
            rt_kprintf("ERROR: Start AP timeout!");
            ret = RTW_TIMEOUT; 
            break;
        }

        vTaskDelay(10);
        timeout --;
    }

    if(ret != RTW_SUCCESS)
        return -RT_ERROR;

//#if CONFIG_LWIP_LAYER
    //LwIP_UseStaticIP(pnetif);
//    dhcps_init(pnetif);
//#endif

    return RT_EOK;
}

static int amebaz_wifi_do_ap_stop(void)
{
    return RT_EOK;
}

int amebaz_wifi_ap_start(char *ssid, char *passwd, int channel)
{
    int ret;

    ret = amebaz_wifi_set_ap_info(ssid, passwd, channel);
    if(ret != RT_EOK)
    {
        amebaz_wifi_info_init();
        return ret;
    }
    
    if(amebaz_wifi_do_ap_start() != RT_EOK)
    {
        amebaz_wifi_info_init();
        rt_kprintf("amebaz_wifi_ap_start failed...\n");
        return -RT_ERROR;
    }

    amebaz_wifi_info_init();
    return RT_EOK;
}

int amebaz_wifi_ap_stop(void)
{
    int ret;

    if(amebaz_wifi_do_ap_stop() != RT_EOK)
    {
        amebaz_wifi_info_init();
        rt_kprintf("amebaz_wifi_ap_stop failed...\n");
        return -RT_ERROR;
    }

    amebaz_wifi_info_init();
    return RT_EOK;
}

int amebaz_wifi_get_rssi(void)
{
	int rssi = 0;
    
	wifi_get_rssi(&rssi);
    
    return rssi;
}

void amebaz_wifi_set_channel(int channel)
{
    wifi_set_channel(channel);
}

int amebaz_wifi_get_channel(void)
{
    int channel;
    
    wifi_get_channel(&channel);
    
    return channel;
}

int amebaz_wifi_init(rt_wlan_mode_t mode)
{
    int ret;
    rtw_mode_t rtw_mode;

    if(mode == WIFI_STATION)
        rtw_mode = RTW_MODE_STA;
    else if(mode == WIFI_AP)
        rtw_mode = RTW_MODE_AP;
    
    if(wifi_on(mode) < 0)
        return -RT_ERROR;
    
    if(wifi_set_autoreconnect(1) < 0)
        return -RT_ERROR;

    return RT_EOK;
}

