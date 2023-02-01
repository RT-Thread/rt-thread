/**************************************************************************//**
 * @file     config.h
 * @version  V1.00
 * @brief    This header file defines the configuration of USB Host library.
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef  _USBH_CONFIG_H_
#define  _USBH_CONFIG_H_


/// @cond HIDDEN_SYMBOLS

#include <rtthread.h>
#include "NuMicro.h"
#include "nu_sys.h"
#include "drv_sys.h"


/*----------------------------------------------------------------------------------------*/
/*   Hardware settings                                                                    */
/*----------------------------------------------------------------------------------------*/
#define HCLK_MHZ               700          /* used for loop-delay. must be larger than
                                               true HCLK clock MHz                        */

static __inline void ENABLE_OHCI_IRQ(void)
{
    rt_hw_interrupt_umask(USBH0_IRQn);
    rt_hw_interrupt_umask(USBH1_IRQn);
}
static __inline void DISABLE_OHCI_IRQ(void)
{
    rt_hw_interrupt_mask(USBH0_IRQn);
    rt_hw_interrupt_mask(USBH1_IRQn);
}
static __inline void ENABLE_EHCI_IRQ(void)
{
    rt_hw_interrupt_umask(HSUSBH0_IRQn);
    rt_hw_interrupt_umask(HSUSBH1_IRQn);
}
static __inline void DISABLE_EHCI_IRQ(void)
{
    rt_hw_interrupt_mask(HSUSBH0_IRQn);
    rt_hw_interrupt_mask(HSUSBH1_IRQn);
}


#if defined(BSP_USING_HSUSBH0)
    #define ENABLE_EHCI0
    #define ENABLE_OHCI0
#endif

#if defined(BSP_USING_HSUSBH1)
    #define ENABLE_EHCI1
    #define ENABLE_OHCI1
#endif

#define EHCI_PORT_CNT          1            /* Number of EHCI roothub ports               */
#define OHCI_PORT_CNT          1            /* Number of OHCI roothub ports               */
#define OHCI_PER_PORT_POWER                 /* OHCI root hub per port powered             */

#define OHCI_ISO_DELAY         4            /* preserved number frames while scheduling
                                               OHCI isochronous transfer                  */

#define EHCI_ISO_DELAY         2            /* preserved number of frames while
                                               scheduling EHCI isochronous transfer       */

#define EHCI_ISO_RCLM_RANGE    32           /* When inspecting activated iTD/siTD,
                                               unconditionally reclaim iTD/isTD scheduled
                                               in just elapsed EHCI_ISO_RCLM_RANGE ms.    */

#define MAX_DESC_BUFF_SIZE     4096         /* To hold the configuration descriptor, USB
                                               core will allocate a buffer with this size
                                               for each connected device. USB core does
                                               not release it until device disconnected.  */

/*----------------------------------------------------------------------------------------*/
/*   Memory allocation settings                                                           */
/*----------------------------------------------------------------------------------------*/

#define STATIC_MEMORY_ALLOC    0       /* pre-allocate static memory blocks. No dynamic memory aloocation.
                                          But the maximum number of connected devices and transfers are
                                          limited.  */

#define MAX_UDEV_DRIVER        8       /*!< Maximum number of registered drivers                      */
#define MAX_ALT_PER_IFACE     32       /*!< maximum number of alternative interfaces per interface    */
#define MAX_EP_PER_IFACE       6       /*!< maximum number of endpoints per interface                 */
#define MAX_HUB_DEVICE         8       /*!< Maximum number of hub devices                             */

/* Host controller hardware transfer descriptors memory pool. ED/TD/ITD of OHCI and QH/QTD of EHCI
   are all allocated from this pool. Allocated unit size is determined by MEM_POOL_UNIT_SIZE.
   May allocate one or more units depend on hardware descriptor type.                                 */

#define MEM_POOL_UNIT_SIZE    256      /*!< A fixed hard coding setting. Do not change it!            */
#define MEM_POOL_UNIT_NUM     64      /*!< Increase this or heap size if memory allocate failed.     */

/*----------------------------------------------------------------------------------------*/
/*   Re-defined staff for various compiler                                                */
/*----------------------------------------------------------------------------------------*/
#ifdef __ICCARM__
    #define   __inline    inline
#endif


/*----------------------------------------------------------------------------------------*/
/*   Debug settings                                                                       */
/*----------------------------------------------------------------------------------------*/
//#define ENABLE_ERROR_MSG                    /* enable debug messages                      */
//#define ENABLE_DEBUG_MSG                    /* enable debug messages                      */
//#define ENABLE_VERBOSE_DEBUG              /* verbos debug messages                      */
//#define DUMP_DESCRIPTOR                   /* dump descriptors                           */

#ifdef ENABLE_ERROR_MSG
    #define USB_error            rt_kprintf
#else
    #define USB_error(...)
#endif

#ifdef ENABLE_DEBUG_MSG
    #define USB_debug            rt_kprintf
    #ifdef ENABLE_VERBOSE_DEBUG
        #define USB_vdebug          rt_kprintf
    #else
        #define USB_vdebug(...)
    #endif
#else
    #define USB_debug(...)
    #define USB_vdebug(...)
#endif
#define ptr_to_u32(x)       ((uint32_t)(x))


/// @endcond HIDDEN_SYMBOLS

#endif  /* _USBH_CONFIG_H_ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

