/*********************************************************************************************************//**
 * @file    ht32_retarget_usbdconf.h
 * @version $Rev:: 1958         $
 * @date    $Date:: 2019-12-27 #$
 * @brief   The USB Device configuration of retarget
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
#ifndef __HT32_RETARGET_USBDCONF_H
#define __HT32_RETARGET_USBDCONF_H

/* Settings ------------------------------------------------------------------------------------------------*/
#define RETARGET_INF           (0)
#define RETARGET_DLEN          (0)

#if (_RETARGET == 1)

  #ifdef RETARGET_IS_USB

    #undef RETARGET_INF
    #undef RETARGET_DLEN
    #define RETARGET_INF           (2)
    #define RETARGET_DLEN          (8 + DESC_LEN_INF * 2 + 5 + 4 + 5 + 5 + DESC_LEN_EPT * 3)

    #if (_EP1_ENABLE == 0 && _EP2_ENABLE == 0 && _EP3_ENABLE == 0 && _EP4_ENABLE == 0 && \
    _EP5_ENABLE == 0 && _EP6_ENABLE == 0 && _EP7_ENABLE == 0)
      #define NON_USB_IN_APP
      #undef _UIER
      #undef _EP0LEN
      #undef _EP0_IER
      #define _EP0LEN   (64)
      #define _EP0_IER  (0x212)
      #define _UIER     (0x011D)
    #endif

    #define _UIER_ALL (_UIER | (EP0IE << RETARGET_RX_EPT) | (EP0IE << RETARGET_TX_EPT))

    #if (RETARGET_RX_EPT == 1 || RETARGET_TX_EPT == 1 || RETARGET_CTRL_EPT == 1)
      #if (_EP1_ENABLE == 1)
        #define _RERATGET1_ERR
      #else
        #undef _EP1_ENABLE
        #undef _EP1_CFG_EPADR
        #undef _EP1_CFG_EPEN_TMP
        #undef _EP1_TYPR
        #undef _EP1_CFG_EPDIR
        #undef _EP1LEN_TMP
        #undef _EP1_IER

        #define _EP1_ENABLE         (1)
        #define _EP1_CFG_EPADR      (1)
        #define _EP1_CFG_EPEN_TMP   (1)
        #if (RETARGET_RX_EPT == 1)
          #define _EP1_TYPR           (2)
          #define _EP1_CFG_EPDIR      (0)
          #define _EP1LEN_TMP         (RETARGET_RX_EPTLEN)
          #define _EP1_IER            (0x02)
          #define RETARGET_RX_LEN     (_EP1LEN)
        #elif (RETARGET_TX_EPT == 1)
          #define _EP1_TYPR           (2)
          #define _EP1_CFG_EPDIR      (1)
          #define _EP1LEN_TMP         (RETARGET_TX_EPTLEN)
          #define _EP1_IER            (0x10)
          #define RETARGET_TX_LEN     (_EP1LEN)
        #elif (RETARGET_CTRL_EPT == 1)
          #define _EP1_TYPR           (3)
          #define _EP1_CFG_EPDIR      (1)
          #define _EP1LEN_TMP         (RETARGET_CTRL_EPTLEN)
          #define _EP1_IER            (0x10)
          #define RETARGET_CTRL_LEN   (_EP1LEN)
        #endif
      #endif
    #endif

    #if (RETARGET_RX_EPT == 2 || RETARGET_TX_EPT == 2 || RETARGET_CTRL_EPT == 2)
      #if (_EP2_ENABLE == 1)
        #define _RERATGET2_ERR
      #else
        #undef _EP2_ENABLE
        #undef _EP2_CFG_EPADR
        #undef _EP2_CFG_EPEN_TMP
        #undef _EP2_TYPR
        #undef _EP2_CFG_EPDIR
        #undef _EP2LEN_TMP
        #undef _EP2_IER

        #define _EP2_ENABLE         (1)
        #define _EP2_CFG_EPADR      (2)
        #define _EP2_CFG_EPEN_TMP   (1)
        #if (RETARGET_RX_EPT == 2)
          #define _EP2_TYPR           (2)
          #define _EP2_CFG_EPDIR      (0)
          #define _EP2LEN_TMP         (RETARGET_RX_EPTLEN)
          #define _EP2_IER            (0x02)
          #define RETARGET_RX_LEN     (_EP2LEN)
        #elif (RETARGET_TX_EPT == 2)
          #define _EP2_TYPR           (2)
          #define _EP2_CFG_EPDIR      (1)
          #define _EP2LEN_TMP         (RETARGET_TX_EPTLEN)
          #define _EP2_IER            (0x10)
          #define RETARGET_TX_LEN     (_EP2LEN)
        #elif (RETARGET_CTRL_EPT == 2)
          #define _EP2_TYPR           (3)
          #define _EP2_CFG_EPDIR      (1)
          #define _EP2LEN_TMP         (RETARGET_CTRL_EPTLEN)
          #define _EP2_IER            (0x10)
          #define RETARGET_CTRL_LEN   (_EP2LEN)
        #endif
      #endif
    #endif

    #if (RETARGET_RX_EPT == 3 || RETARGET_TX_EPT == 3 || RETARGET_CTRL_EPT == 3)
      #if (_EP3_ENABLE == 1)
        #define _RERATGET3_ERR
      #else
        #undef _EP3_ENABLE
        #undef _EP3_CFG_EPADR
        #undef _EP3_CFG_EPEN_TMP
        #undef _EP3_TYPR
        #undef _EP3_CFG_EPDIR
        #undef _EP3LEN_TMP
        #undef _EP3_IER

        #define _EP3_ENABLE         (1)
        #define _EP3_CFG_EPADR      (3)
        #define _EP3_CFG_EPEN_TMP   (1)
        #if (RETARGET_RX_EPT == 3)
          #define _EP3_TYPR           (2)
          #define _EP3_CFG_EPDIR      (0)
          #define _EP3LEN_TMP         (RETARGET_RX_EPTLEN)
          #define _EP3_IER            (0x02)
          #define RETARGET_RX_LEN     (_EP3LEN)
        #elif (RETARGET_TX_EPT == 3)
          #define _EP3_TYPR           (2)
          #define _EP3_CFG_EPDIR      (1)
          #define _EP3LEN_TMP         (RETARGET_TX_EPTLEN)
          #define _EP3_IER            (0x10)
          #define RETARGET_TX_LEN     (_EP3LEN)
        #elif (RETARGET_CTRL_EPT == 3)
          #define _EP3_TYPR           (3)
          #define _EP3_CFG_EPDIR      (1)
          #define _EP3LEN_TMP         (RETARGET_CTRL_EPTLEN)
          #define _EP3_IER            (0x10)
          #define RETARGET_CTRL_LEN   (_EP3LEN)
        #endif
      #endif
    #endif

    #if (RETARGET_RX_EPT == 4 || RETARGET_TX_EPT == 4 || RETARGET_CTRL_EPT == 4)
      #if (_EP4_ENABLE == 1)
        #define _RERATGET4_ERR
      #else
        #undef _EP4_ENABLE
        #undef _EP4_CFG_EPADR
        #undef _EP4_CFG_EPEN_TMP
        #undef _EP4_TYPR
        #undef _EP4_CFG_EPDIR
        #undef _EP4LEN_TMP
        #undef _EP4_IER

        #define _EP4_ENABLE         (1)
        #define _EP4_CFG_EPADR      (4)
        #define _EP4_CFG_EPEN_TMP   (1)
        #if (RETARGET_RX_EPT == 4)
          #define _EP4_TYPR           (2)
          #define _EP4_CFG_EPDIR      (0)
          #define _EP4LEN_TMP         (RETARGET_RX_EPTLEN)
          #define _EP4_IER            (0x02)
          #define RETARGET_RX_LEN     (_EP4LEN)
        #elif (RETARGET_TX_EPT == 4)
          #define _EP4_TYPR           (2)
          #define _EP4_CFG_EPDIR      (1)
          #define _EP4LEN_TMP         (RETARGET_TX_EPTLEN)
          #define _EP4_IER            (0x10)
          #define RETARGET_TX_LEN     (_EP4LEN)
        #elif (RETARGET_CTRL_EPT == 4)
          #define _EP4_TYPR           (3)
          #define _EP4_CFG_EPDIR      (1)
          #define _EP4LEN_TMP         (RETARGET_CTRL_EPTLEN)
          #define _EP4_IER            (0x10)
          #define RETARGET_CTRL_LEN   (_EP4LEN)
        #endif
      #endif
    #endif

    #if (RETARGET_RX_EPT == 5 || RETARGET_TX_EPT == 5 || RETARGET_CTRL_EPT == 5)
      #if (_EP5_ENABLE == 1)
        #define _RERATGET5_ERR
      #else
        #undef _EP5_ENABLE
        #undef _EP5_CFG_EPADR
        #undef _EP5_CFG_EPEN_TMP
        #undef _EP5_TYPR
        #undef _EP5_CFG_EPDIR
        #undef _EP5LEN_TMP
        #undef _EP5_IER

        #define _EP5_ENABLE         (1)
        #define _EP5_CFG_EPADR      (5)
        #define _EP5_CFG_EPEN_TMP   (1)
        #if (RETARGET_RX_EPT == 5)
          #define _EP5_TYPR           (2)
          #define _EP5_CFG_EPDIR      (0)
          #define _EP5LEN_TMP         (RETARGET_RX_EPTLEN)
          #define _EP5_IER            (0x02)
          #define RETARGET_RX_LEN     (_EP5LEN)
        #elif (RETARGET_TX_EPT == 5)
          #define _EP5_TYPR           (2)
          #define _EP5_CFG_EPDIR      (1)
          #define _EP5LEN_TMP         (RETARGET_TX_EPTLEN)
          #define _EP5_IER            (0x10)
          #define RETARGET_TX_LEN     (_EP5LEN)
        #elif (RETARGET_CTRL_EPT == 5)
          #define _EP5_TYPR           (3)
          #define _EP5_CFG_EPDIR      (1)
          #define _EP5LEN_TMP         (RETARGET_CTRL_EPTLEN)
          #define _EP5_IER            (0x10)
          #define RETARGET_CTRL_LEN   (_EP5LEN)
        #endif
      #endif
    #endif

    #if (RETARGET_RX_EPT == 6 || RETARGET_TX_EPT == 6 || RETARGET_CTRL_EPT == 6)
      #if (_EP6_ENABLE == 1)
        #define _RERATGET6_ERR
      #else
        #undef _EP6_ENABLE
        #undef _EP6_CFG_EPADR
        #undef _EP6_CFG_EPEN_TMP
        #undef _EP6_TYPR
        #undef _EP6_CFG_EPDIR
        #undef _EP6LEN_TMP
        #undef _EP6_IER

        #define _EP6_ENABLE         (1)
        #define _EP6_CFG_EPADR      (6)
        #define _EP6_CFG_EPEN_TMP   (1)
        #if (RETARGET_RX_EPT == 6)
          #define _EP6_TYPR           (2)
          #define _EP6_CFG_EPDIR      (0)
          #define _EP6LEN_TMP         (RETARGET_RX_EPTLEN)
          #define _EP6_IER            (0x02)
          #define RETARGET_RX_LEN     (_EP6LEN)
        #elif (RETARGET_TX_EPT == 6)
          #define _EP6_TYPR           (2)
          #define _EP6_CFG_EPDIR      (1)
          #define _EP6LEN_TMP         (RETARGET_TX_EPTLEN)
          #define _EP6_IER            (0x10)
          #define RETARGET_TX_LEN     (_EP6LEN)
        #elif (RETARGET_CTRL_EPT == 6)
          #define _EP6_TYPR           (3)
          #define _EP6_CFG_EPDIR      (1)
          #define _EP6LEN_TMP         (RETARGET_CTRL_EPTLEN)
          #define _EP6_IER            (0x10)
          #define RETARGET_CTRL_LEN   (_EP6LEN)
        #endif
      #endif
    #endif

    #if (RETARGET_RX_EPT == 7 || RETARGET_TX_EPT == 7 || RETARGET_CTRL_EPT == 7)
      #if (_EP7_ENABLE == 1)
        #define _RERATGET7_ERR
      #else
        #undef _EP7_ENABLE
        #undef _EP7_CFG_EPADR
        #undef _EP7_CFG_EPEN_TMP
        #undef _EP7_TYPR
        #undef _EP7_CFG_EPDIR
        #undef _EP7LEN_TMP
        #undef _EP7_IER

        #define _EP7_ENABLE         (1)
        #define _EP7_CFG_EPADR      (7)
        #define _EP7_CFG_EPEN_TMP   (1)
        #if (RETARGET_RX_EPT == 7)
          #define _EP7_TYPR           (2)
          #define _EP7_CFG_EPDIR      (0)
          #define _EP7LEN_TMP         (RETARGET_RX_EPTLEN)
          #define _EP7_IER            (0x02)
          #define RETARGET_RX_LEN     (_EP7LEN)
        #elif (RETARGET_TX_EPT == 7)
          #define _EP7_TYPR           (2)
          #define _EP7_CFG_EPDIR      (1)
          #define _EP7LEN_TMP         (RETARGET_TX_EPTLEN)
          #define _EP7_IER            (0x10)
          #define RETARGET_TX_LEN     (_EP7LEN)
        #elif (RETARGET_CTRL_EPT == 7)
          #define _EP7_TYPR           (3)
          #define _EP7_CFG_EPDIR      (1)
          #define _EP7LEN_TMP         (RETARGET_CTRL_EPTLEN)
          #define _EP7_IER            (0x10)
          #define RETARGET_CTRL_LEN   (_EP7LEN)
        #endif
      #endif
    #endif

  #endif /*   #ifdef RETARGET_IS_USB                                                                        */

#endif /* #if (_RETARGET == 1)                                                                              */

#endif /* __HT32_RETARGET_USBDCONF_H -----------------------------------------------------------------------*/
