/*********************************************************************************************************//**
 * @file    ht32f5xxxx_usbdinit.h
 * @version $Rev:: 5656         $
 * @date    $Date:: 2021-11-24 #$
 * @brief   The header file of the USB Device Driver.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_USBDINIT_H
#define __HT32F5XXXX_USBDINIT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32_retarget_usbdconf.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup USBDevice
  * @{
  */


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint 0 ~ 7 Configuration                                                                             */
/* !!! DO NOT MODIFY !!!                                                                                    */
/*----------------------------------------------------------------------------------------------------------*/

#define EP_TYPE_ISO         (1)
#define EP_TYPE_BULK        (2)
#define EP_TYPE_INT         (3)

#ifndef _UIER_ALL
  #define _UIER_ALL _UIER
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint0 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP0_CFG_EPEN       (1UL)
#define _EP0STADR           (HT_USB_SRAM_BASE + 0x8)
#define _EP0INTADR          (_EP0STADR)
#define _EP0OUTTADR         (_EP0STADR + _EP0LEN)
#define _EP0_CFG            ((_EP0_CFG_EPEN << 31) | \
                             (_EP0LEN       << 10) | \
                             (_EP0STADR & EPBUFA_MASK))
#define _EP0LEN_T           (_EP0LEN * 2)

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint1 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP1STADR           (_EP0STADR + (_EP0LEN * 2))

#if (_EP1_ENABLE == 1)
  #define _EP1LEN           (_EP1LEN_TMP)
#else
  #define _EP1LEN           (0)
#endif

#if (_EP1_CFG_EPEN_TMP == 1)
  #define _EP1_CFG_EPEN     (1UL)
#else
  #define _EP1_CFG_EPEN     (0UL)
#endif

#define _EP1_CFG            ((_EP1_CFG_EPEN  << 31) | \
                             (_EP1_CFG_EPDIR << 28) | \
                             (_EP1_CFG_EPADR << 24) | \
                             (_EP1LEN        << 10) | \
                             (_EP1STADR & EPBUFA_MASK))

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint2 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP2STADR           (_EP1STADR + _EP1LEN)

#if (_EP2_ENABLE == 1)
  #define _EP2LEN           (_EP2LEN_TMP)
#else
  #define _EP2LEN           (0)
#endif

#if (_EP2_CFG_EPEN_TMP == 1)
  #define _EP2_CFG_EPEN     (1UL)
#else
  #define _EP2_CFG_EPEN     (0UL)
#endif

#define _EP2_CFG            ((_EP2_CFG_EPEN  << 31) | \
                             (_EP2_CFG_EPDIR << 28) | \
                             (_EP2_CFG_EPADR << 24) | \
                             (_EP2LEN        << 10) | \
                             (_EP2STADR & EPBUFA_MASK))

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint3 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP3STADR           (_EP2STADR + _EP2LEN)

#if (_EP3_ENABLE == 1)
  #define _EP3LEN           (_EP3LEN_TMP)
#else
  #define _EP3LEN           (0)
#endif

#if (_EP3_CFG_EPEN_TMP == 1)
  #define _EP3_CFG_EPEN     (1UL)
#else
  #define _EP3_CFG_EPEN     (0UL)
#endif

#define _EP3_CFG            ((_EP3_CFG_EPEN  << 31) | \
                             (_EP3_CFG_EPDIR << 28) | \
                             (_EP3_CFG_EPADR << 24) | \
                             (_EP3LEN        << 10) | \
                             (_EP3STADR & EPBUFA_MASK))

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint4 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP4STADR           (_EP3STADR + _EP3LEN)

#if (_EP4_ENABLE == 1)
  #define _EP4LEN           (_EP4LEN_TMP)
  #define _EP4LEN_T         (_EP4LEN_TMP * (_EP4_CFG_SDBS + 1))
#else
  #define _EP4LEN           (0)
  #define _EP4LEN_T         (0)
#endif
#if (_EP4_TYPR == EP_TYPE_ISO)
  #define _EP4_CFG_EPTYPE   (1)
#else
  #define _EP4_CFG_EPTYPE   (0)
#endif

#if (_EP4_CFG_EPEN_TMP == 1)
  #define _EP4_CFG_EPEN     (1UL)
#else
  #define _EP4_CFG_EPEN     (0UL)
#endif

#define _EP4_CFG            ((_EP4_CFG_EPEN   << 31) | \
                             (_EP4_CFG_EPTYPE << 29) | \
                             (_EP4_CFG_EPDIR  << 28) | \
                             (_EP4_CFG_EPADR  << 24) | \
                             (_EP4_CFG_SDBS   << 23) | \
                             (_EP4LEN         << 10) | \
                             (_EP4STADR & EPBUFA_MASK))

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint5 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP5STADR           (_EP4STADR + _EP4LEN_T)

#if (_EP5_ENABLE == 1)
  #define _EP5LEN           (_EP5LEN_TMP)
  #define _EP5LEN_T         (_EP5LEN_TMP * (_EP5_CFG_SDBS + 1))
#else
  #define _EP5LEN           (0)
  #define _EP5LEN_T         (0)
#endif
#if (_EP5_TYPR == EP_TYPE_ISO)
  #define _EP5_CFG_EPTYPE   (1)
#else
  #define _EP5_CFG_EPTYPE   (0)
#endif

#if (_EP5_CFG_EPEN_TMP == 1)
  #define _EP5_CFG_EPEN     (1UL)
#else
  #define _EP5_CFG_EPEN     (0UL)
#endif

#define _EP5_CFG            ((_EP5_CFG_EPEN   << 31) | \
                             (_EP5_CFG_EPTYPE << 29) | \
                             (_EP5_CFG_EPDIR  << 28) | \
                             (_EP5_CFG_EPADR  << 24) | \
                             (_EP5_CFG_SDBS   << 23) | \
                             (_EP5LEN         << 10) | \
                             (_EP5STADR & EPBUFA_MASK))

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint6 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP6STADR           (_EP5STADR + _EP5LEN_T)

#if (_EP6_ENABLE == 1)
  #define _EP6LEN           (_EP6LEN_TMP)
  #define _EP6LEN_T         (_EP6LEN_TMP * (_EP6_CFG_SDBS + 1))
#else
  #define _EP6LEN           (0)
  #define _EP6LEN_T         (0)
#endif
#if (_EP6_TYPR == EP_TYPE_ISO)
  #define _EP6_CFG_EPTYPE   (1)
#else
  #define _EP6_CFG_EPTYPE   (0)
#endif

#if (_EP6_CFG_EPEN_TMP == 1)
  #define _EP6_CFG_EPEN     (1UL)
#else
  #define _EP6_CFG_EPEN     (0UL)
#endif

#define _EP6_CFG            ((_EP6_CFG_EPEN   << 31) | \
                             (_EP6_CFG_EPTYPE << 29) | \
                             (_EP6_CFG_EPDIR  << 28) | \
                             (_EP6_CFG_EPADR  << 24) | \
                             (_EP6_CFG_SDBS   << 23) | \
                             (_EP6LEN         << 10) | \
                             (_EP6STADR & EPBUFA_MASK))

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint7 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP7STADR           (_EP6STADR + _EP6LEN_T)

#if (_EP7_ENABLE == 1)
  #define _EP7LEN           (_EP7LEN_TMP)
  #define _EP7LEN_T         (_EP7LEN_TMP * (_EP7_CFG_SDBS + 1))
#else
  #define _EP7LEN           (0)
  #define _EP7LEN_T         (0)
#endif
#if (_EP7_TYPR == EP_TYPE_ISO)
  #define _EP7_CFG_EPTYPE   (1)
#else
  #define _EP7_CFG_EPTYPE   (0)
#endif

#if (_EP7_CFG_EPEN_TMP == 1)
  #define _EP7_CFG_EPEN     (1UL)
#else
  #define _EP7_CFG_EPEN     (0UL)
#endif

#define _EP7_CFG            ((_EP7_CFG_EPEN   << 31) | \
                             (_EP7_CFG_EPTYPE << 29) | \
                             (_EP7_CFG_EPDIR  << 28) | \
                             (_EP7_CFG_EPADR  << 24) | \
                             (_EP7_CFG_SDBS   << 23) | \
                             (_EP7LEN         << 10) | \
                             (_EP7STADR & EPBUFA_MASK))

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint8 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP8STADR           (_EP7STADR + _EP7LEN_T)

#if (_EP8_ENABLE == 1)
  #define _EP8LEN           (_EP8LEN_TMP)
#else
  #define _EP8LEN           (0)
#endif

#if (_EP8_CFG_EPEN_TMP == 1)
  #define _EP8_CFG_EPEN     (1UL)
#else
  #define _EP8_CFG_EPEN     (0UL)
#endif

#define _EP8_CFG            ((_EP8_CFG_EPEN  << 31) | \
                             (_EP8_CFG_EPDIR << 28) | \
                             (_EP8_CFG_EPADR << 24) | \
                             (_EP8LEN        << 10) | \
                             (_EP8STADR & EPBUFA_MASK))


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint9 Configuration                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
#define _EP9STADR           (_EP8STADR + _EP8LEN)

#if (_EP9_ENABLE == 1)
  #define _EP9LEN           (_EP9LEN_TMP)
#else
  #define _EP9LEN           (0)
#endif

#if (_EP9_CFG_EPEN_TMP == 1)
  #define _EP9_CFG_EPEN     (1UL)
#else
  #define _EP9_CFG_EPEN     (0UL)
#endif

#define _EP9_CFG            ((_EP9_CFG_EPEN  << 31) | \
                             (_EP9_CFG_EPDIR << 28) | \
                             (_EP9_CFG_EPADR << 24) | \
                             (_EP9LEN        << 10) | \
                             (_EP9STADR & EPBUFA_MASK))


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
