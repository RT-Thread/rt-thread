#ifndef _WLAN_DEBUG_H
#define _WLAN_DEBUG_H

#define WLAN_DEBUG_LEVEL_3
#ifdef WLAN_DEBUG_LEVEL_0
#define wlan_debug1(...)
#define wlan_debug2(...)
#define wlan_debug3(...) 
#endif
#ifdef  WLAN_DEBUG_LEVEL_1
#define wlan_debug1(a...) rt_kprintf(a)
#define wlan_debug2(...)
#define wlan_debug3(...) 
#endif

#ifdef  WLAN_DEBUG_LEVEL_2
#define wlan_debug1(a...) rt_kprintf(a)
#define wlan_debug2(a...) rt_kprintf(a)
#define wlan_debug3(...) 
#endif

#ifdef  WLAN_DEBUG_LEVEL_3
#define wlan_debug1(a...) rt_kprintf(a)
#define wlan_debug2(a...) rt_kprintf(a)
#define wlan_debug3(a...) rt_kprintf(a)
#endif

#define WLANEPARAMETER 101;
#endif
