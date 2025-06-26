#include "rtthread.h"
#include "usb_config.h"

#if defined(PKG_CHERRYUSB_HOST) || defined(RT_CHERRYUSB_HOST)

#ifndef RT_USING_TIMER_SOFT
#error must enable RT_USING_TIMER_SOFT to support timer callback in thread
#endif

#if RT_TIMER_THREAD_STACK_SIZE < 2048
#error "RT_TIMER_THREAD_STACK_SIZE must be >= 2048"
#endif

#endif

#if defined(ARCH_ARM_CORTEX_M7) ||                                          \
    defined(SOC_HPM6000) || defined(SOC_HPM6E00) || defined(SOC_HPM6P00) || \
    defined(BSP_USING_BL61X) || defined(BSP_USING_BL808)
#ifndef RT_USING_CACHE
#error RT_USING_CACHE must be enabled in this chip
#endif
#endif

#ifdef RT_USING_CACHE
#ifndef CONFIG_USB_DCACHE_ENABLE
#error CONFIG_USB_DCACHE_ENABLE must be enabled
#endif
#if RT_ALIGN_SIZE != 32 && RT_ALIGN_SIZE != 64
#error RT_ALIGN_SIZE must be cacheline to 32 or 64
#endif
#endif
