/**************************************************************************//**
 * @file     config.h
 * @version  V1.00
 * @brief    This header file defines the configuration of USB Host library.
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2019-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef  _USBH_CONFIG_H_
#define  _USBH_CONFIG_H_

/// @cond HIDDEN_SYMBOLS

#include <rtconfig.h>
#include <rtdevice.h>
/*----------------------------------------------------------------------------------------*/
/*   Hardware settings                                                                    */
/*----------------------------------------------------------------------------------------*/
#define HCLK_MHZ               192          /* used for loop-delay. must be larger than
                                               true HCLK clock MHz                        */

#define ENABLE_OHCI_IRQ()      NVIC_EnableIRQ(USBH_IRQn)
#define DISABLE_OHCI_IRQ()     NVIC_DisableIRQ(USBH_IRQn)

#define ENABLE_OHCI                         /* Enable OHCI host controller                */

#define OHCI_ISO_DELAY         4            /* preserved number frames while scheduling
                                               OHCI isochronous transfer                  */

#define MAX_DESC_BUFF_SIZE     512          /* To hold the configuration descriptor, USB
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
#define MAX_ALT_PER_IFACE      8       /*!< maximum number of alternative interfaces per interface    */
#define MAX_EP_PER_IFACE       6       /*!< maximum number of endpoints per interface                 */
#define MAX_HUB_DEVICE         8       /*!< Maximum number of hub devices                             */

/* Host controller hardware transfer descriptors memory pool. ED/TD/ITD of OHCI and QH/QTD of EHCI
   are all allocated from this pool. Allocated unit size is determined by MEM_POOL_UNIT_SIZE.
   May allocate one or more units depend on hardware descriptor type.                                 */

#define MEM_POOL_UNIT_SIZE     64      /*!< A fixed hard coding setting. Do not change it!            */
#define MEM_POOL_UNIT_NUM     256      /*!< Increase this or heap size if memory allocate failed.     */

/*----------------------------------------------------------------------------------------*/
/*   Re-defined staff for various compiler                                                */
/*----------------------------------------------------------------------------------------*/
#ifdef __ICCARM__
    #define   __inline    inline
#endif


/*----------------------------------------------------------------------------------------*/
/*   Debug settings                                                                       */
/*----------------------------------------------------------------------------------------*/
#define ENABLE_ERROR_MSG                    /* enable debug messages                      */
#define ENABLE_DEBUG_MSG                    /* enable debug messages                      */
//#define ENABLE_VERBOSE_DEBUG              /* verbos debug messages                      */
//#define DUMP_DESCRIPTOR                     /* dump descriptors                           */

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


/// @endcond HIDDEN_SYMBOLS

#endif  /* _USBH_CONFIG_H_ */

/*** (C) COPYRIGHT 2019-2020 Nuvoton Technology Corp. ***/

