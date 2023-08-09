#include <rtthread.h>
#include <rtdbg.h>
#ifdef BSP_USING_CYW43012_WIFI
#include <rtdevice.h>

int wifi_cyw43012_device_init(void)
{
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);

    return 0;
}
INIT_APP_EXPORT(wifi_cyw43012_device_init);


#endif /* BSP_USING_CYW43012_WIFI */
