/*********************************************************************************************************//**
 * @file    ht32f1xxxx_usbdchk.h
 * @version $Rev:: 122          $
 * @date    $Date:: 2017-06-13 #$
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
#ifndef __HT32F1XXXX_USBDCHK_H
#define __HT32F1XXXX_USBDCHK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup USBDevice
  * @{
  */


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint 0 ~ 7 and checking                                                                              */
/* !!! DO NOT MODIFY !!!                                                                                    */
/*----------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint0 checking                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP0LEN != 8 && _EP0LEN != 16 && _EP0LEN != 32 && _EP0LEN != 64)
  #error "USB Buffer Length (EPLEN) of Control Endpoint0 must be 8, 16, 32, or 64 bytes."
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint1 Configuration and checking                                                                     */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP1_ENABLE == 1)
  #if (_EP1_TYPR == EP_TYPE_BULK)
    #if (_EP1LEN != 8 && _EP1LEN != 16 && _EP1LEN != 32 && _EP1LEN != 64)
      #error "USB Buffer Length (EPLEN) of Endpoint1 must be 8, 16, 32, or 64 bytes under Bulk transfer."
    #endif
  #endif
  #if (_EP1LEN > 64)
    #error "USB Buffer Length (EPLEN) of Endpoint1 must be less than 64 bytes."
  #endif
  #if (_EP1LEN == 0)
    #error "USB Buffer Length (EPLEN) of Endpoint1 cannot be 0 byte."
  #endif
  #if ((_EP1LEN & 0x3) != 0x0)
    #error "USB Buffer Length (EPLEN) of Endpoint1 must be a multiple of 4 (word-aligned)."
  #endif
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint2 checking                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP2_ENABLE == 1)
  #if (_EP2_TYPR == EP_TYPE_BULK)
    #if (_EP2LEN != 8 && _EP2LEN != 16 && _EP2LEN != 32 && _EP2LEN != 64)
      #error "USB Buffer Length (EPLEN) of Endpoint2 must be 8, 16, 32, or 64 bytes under Bulk transfer."
    #endif
  #endif
  #if (_EP2LEN > 64)
    #error "USB Buffer Length (EPLEN) of Endpoint2 must be less than 64 bytes."
  #endif
  #if (_EP2LEN == 0)
    #error "USB Buffer Length (EPLEN) of Endpoint2 cannot be 0 byte."
  #endif
  #if ((_EP2LEN & 0x3) != 0x0)
    #error "USB Buffer Length (EPLEN) of Endpoint2 must be a multiple of 4 (word-aligned)."
  #endif
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint3 checking                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP3_ENABLE == 1)
  #if (_EP3_TYPR == EP_TYPE_BULK)
    #if (_EP3LEN != 8 && _EP3LEN != 16 && _EP3LEN != 32 && _EP3LEN != 64)
      #error "USB Buffer Length (EPLEN) of Endpoint3 must be 8, 16, 32, or 64 bytes under Bulk transfer."
    #endif
  #endif
  #if (_EP3LEN > 64)
    #error "USB Buffer Length (EPLEN) of Endpoint3 must be less than 64 bytes."
  #endif
  #if (_EP3LEN == 0)
    #error "USB Buffer Length (EPLEN) of Endpoint3 cannot be 0 byte."
  #endif
  #if ((_EP3LEN & 0x3) != 0x0)
    #error "USB Buffer Length (EPLEN) of Endpoint3 must be a multiple of 4 (word-aligned)."
  #endif
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint4 checking                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP4_ENABLE == 1)
  #if (_EP4_TYPR == EP_TYPE_BULK)
    #if (_EP4LEN != 8 && _EP4LEN != 16 && _EP4LEN != 32 && _EP4LEN != 64)
      #error "USB Buffer Length (EPLEN) of Endpoint4 must be 8, 16, 32, or 64 bytes under Bulk transfer."
    #endif
  #endif
  #if (_EP4_TYPR == EP_TYPE_INT)
    #if (_EP4LEN > 64)
      #error "USB Buffer Length (EPLEN) of Endpoint4 must be less than 64 bytes under Interrupt transfer."
    #endif
  #endif
  #if (_EP4_TYPR == EP_TYPE_ISO)
    #if (_EP4LEN > 1023)
      #error "USB Buffer Length (EPLEN) of Endpoint4 must be less than 1023 bytes under Isochronous transfer."
    #endif
  #endif
  #if (_EP4LEN == 0)
    #error "USB Buffer Length (EPLEN) of Endpoint4 cannot be 0 byte."
  #endif
  #if ((_EP4LEN & 0x3) != 0x0)
    #error "USB Buffer Length (EPLEN) of Endpoint4 must be a multiple of 4 (word-aligned)."
  #endif
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint5 checking                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP5_ENABLE == 1)
  #if (_EP5_TYPR == EP_TYPE_BULK)
    #if (_EP5LEN != 8 && _EP5LEN != 16 && _EP5LEN != 32 && _EP5LEN != 64)
      #error "USB Buffer Length (EPLEN) of Endpoint5 must be 8, 16, 32, or 64 bytes under Bulk transfer."
    #endif
  #endif
  #if (_EP5_TYPR == EP_TYPE_INT)
    #if (_EP5LEN > 64)
      #error "USB Buffer Length (EPLEN) of Endpoint5 must be less than 64 bytes under Interrupt transfer."
    #endif
  #endif
  #if (_EP5_TYPR == EP_TYPE_ISO)
    #if (_EP5LEN > 1023)
      #error "USB Buffer Length (EPLEN) of Endpoint5 must be less than 1023 bytes under Isochronous transfer."
    #endif
  #endif
  #if (_EP5LEN == 0)
    #error "USB Buffer Length (EPLEN) of Endpoint5 cannot be 0 byte."
  #endif
  #if ((_EP5LEN & 0x3) != 0x0)
    #error "USB Buffer Length (EPLEN) of Endpoint5 must be a multiple of 4 (word-aligned)."
  #endif
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint6 checking                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP6_ENABLE == 1)
  #if (_EP6_TYPR == EP_TYPE_BULK)
    #if (_EP6LEN != 8 && _EP6LEN != 16 && _EP6LEN != 32 && _EP6LEN != 64)
      #error "USB Buffer Length (EPLEN) of Endpoint6 must be 8, 16, 32, or 64 bytes under Bulk transfer."
    #endif
  #endif
  #if (_EP6_TYPR == EP_TYPE_INT)
    #if (_EP6LEN > 64)
      #error "USB Buffer Length (EPLEN) of Endpoint6 must be less than 64 bytes under Interrupt transfer."
    #endif
  #endif
  #if (_EP6_TYPR == EP_TYPE_ISO)
    #if (_EP6LEN > 1023)
      #error "USB Buffer Length (EPLEN) of Endpoint6 must be less than 1023 bytes under Isochronous transfer."
    #endif
  #endif
  #if (_EP6LEN == 0)
    #error "USB Buffer Length (EPLEN) of Endpoint6 cannot be 0 byte."
  #endif
  #if ((_EP6LEN & 0x3) != 0x0)
    #error "USB Buffer Length (EPLEN) of Endpoint6 must be a multiple of 4 (word-aligned)."
  #endif
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint7 checking                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP7_ENABLE == 1)
  #if (_EP7_TYPR == EP_TYPE_BULK)
    #if (_EP7LEN != 8 && _EP7LEN != 16 && _EP7LEN != 32 && _EP7LEN != 64)
      #error "USB Buffer Length (EPLEN) of Endpoint7 must be 8, 16, 32, or 64 bytes under Bulk transfer."
    #endif
  #endif
  #if (_EP7_TYPR == EP_TYPE_INT)
    #if (_EP7LEN > 64)
      #error "USB Buffer Length (EPLEN) of Endpoint7 must be less than 64 bytes under Interrupt transfer."
    #endif
  #endif
  #if (_EP7_TYPR == EP_TYPE_ISO)
    #if (_EP7LEN > 1023)
      #error "USB Buffer Length (EPLEN) of Endpoint7 must be less than 1023 bytes under Isochronous transfer."
    #endif
  #endif
  #if (_EP7LEN == 0)
    #error "USB Buffer Length (EPLEN) of Endpoint7 cannot be 0 byte."
  #endif
  #if ((_EP7LEN & 0x3) != 0x0)
    #error "USB Buffer Length (EPLEN) of Endpoint7 must be a multiple of 4 (word-aligned)."
  #endif
#endif


/*----------------------------------------------------------------------------------------------------------*/
/* Check the endpoint address                                                                               */
/*----------------------------------------------------------------------------------------------------------*/
#if (_EP1_ENABLE == 1)
  #if (_EP1_CFG_EPADR == 0)
    #error "The address of Endpoint1 (EPADR) cannot be 0."
  #endif
  #if (_EP2_ENABLE == 1)
    #if (_EP1_CFG_EPADR == _EP2_CFG_EPADR)
      #error "The address of Endpoint1 (EPADR) conflicts with Endpoint2."
    #endif
  #endif
  #if (_EP3_ENABLE == 1)
    #if (_EP1_CFG_EPADR == _EP3_CFG_EPADR)
      #error "The address of Endpoint1 (EPADR) conflicts with Endpoint3."
    #endif
  #endif
  #if (_EP4_ENABLE == 1)
    #if (_EP1_CFG_EPADR == _EP4_CFG_EPADR)
      #error "The address of Endpoint1 (EPADR) conflicts with Endpoint4."
    #endif
  #endif
  #if (_EP5_ENABLE == 1)
    #if (_EP1_CFG_EPADR == _EP5_CFG_EPADR)
      #error "The address of Endpoint1 (EPADR) conflicts with Endpoint5."
    #endif
  #endif
  #if (_EP6_ENABLE == 1)
    #if (_EP1_CFG_EPADR == _EP6_CFG_EPADR)
      #error "The address of Endpoint1 (EPADR) conflicts with Endpoint6."
    #endif
  #endif
  #if (_EP7_ENABLE == 1)
    #if (_EP1_CFG_EPADR == _EP7_CFG_EPADR)
      #error "The address of Endpoint1 (EPADR) conflicts with Endpoint7."
    #endif
  #endif
#endif

#if (_EP2_ENABLE == 1)
  #if (_EP2_CFG_EPADR == 0)
    #error "The address of Endpoint2 (EPADR) cannot be 0."
  #endif
  #if (_EP1_ENABLE == 1)
    #if (_EP2_CFG_EPADR == _EP1_CFG_EPADR)
      #error "The address of Endpoint2 (EPADR) conflicts with Endpoint1."
    #endif
  #endif
  #if (_EP3_ENABLE == 1)
    #if (_EP2_CFG_EPADR == _EP3_CFG_EPADR)
      #error "The address of Endpoint2 (EPADR) conflicts with Endpoint3."
    #endif
  #endif
  #if (_EP4_ENABLE == 1)
    #if (_EP2_CFG_EPADR == _EP4_CFG_EPADR)
      #error "The address of Endpoint2 (EPADR) conflicts with Endpoint4."
    #endif
  #endif
  #if (_EP5_ENABLE == 1)
    #if (_EP2_CFG_EPADR == _EP5_CFG_EPADR)
      #error "The address of Endpoint2 (EPADR) conflicts with Endpoint5."
    #endif
  #endif
  #if (_EP6_ENABLE == 1)
    #if (_EP2_CFG_EPADR == _EP6_CFG_EPADR)
      #error "The address of Endpoint2 (EPADR) conflicts with Endpoint6."
    #endif
  #endif
  #if (_EP7_ENABLE == 1)
    #if (_EP2_CFG_EPADR == _EP7_CFG_EPADR)
      #error "The address of Endpoint2 (EPADR) conflicts with Endpoint7."
    #endif
  #endif
#endif

#if (_EP3_ENABLE == 1)
  #if (_EP3_CFG_EPADR == 0)
    #error "The address of Endpoint3 (EPADR) cannot be 0."
  #endif
  #if (_EP1_ENABLE == 1)
    #if (_EP3_CFG_EPADR == _EP1_CFG_EPADR)
      #error "The address of Endpoint3 (EPADR) conflicts with Endpoint1."
    #endif
  #endif
  #if (_EP2_ENABLE == 1)
    #if (_EP3_CFG_EPADR == _EP2_CFG_EPADR)
      #error "The address of Endpoint3 (EPADR) conflicts with Endpoint2."
    #endif
  #endif
  #if (_EP4_ENABLE == 1)
    #if (_EP3_CFG_EPADR == _EP4_CFG_EPADR)
      #error "The address of Endpoint3 (EPADR) conflicts with Endpoint4."
    #endif
  #endif
  #if (_EP5_ENABLE == 1)
    #if (_EP3_CFG_EPADR == _EP5_CFG_EPADR)
      #error "The address of Endpoint3 (EPADR) conflicts with Endpoint5."
    #endif
  #endif
  #if (_EP6_ENABLE == 1)
    #if (_EP3_CFG_EPADR == _EP6_CFG_EPADR)
      #error "The address of Endpoint3 (EPADR) conflicts with Endpoint6."
    #endif
  #endif
  #if (_EP7_ENABLE == 1)
    #if (_EP3_CFG_EPADR == _EP7_CFG_EPADR)
      #error "The address of Endpoint3 (EPADR) conflicts with Endpoint7."
    #endif
  #endif
#endif

#if (_EP4_ENABLE == 1)
  #if (_EP4_CFG_EPADR == 0)
    #error "The address of Endpoint4 (EPADR) cannot be 0."
  #endif
  #if (_EP1_ENABLE == 1)
    #if (_EP4_CFG_EPADR == _EP1_CFG_EPADR)
      #error "The address of Endpoint4 (EPADR) conflicts with Endpoint1."
    #endif
  #endif
  #if (_EP2_ENABLE == 1)
    #if (_EP4_CFG_EPADR == _EP2_CFG_EPADR)
      #error "The address of Endpoint4 (EPADR) conflicts with Endpoint2."
    #endif
  #endif
  #if (_EP3_ENABLE == 1)
    #if (_EP4_CFG_EPADR == _EP3_CFG_EPADR)
      #error "The address of Endpoint4 (EPADR) conflicts with Endpoint3."
    #endif
  #endif
  #if (_EP5_ENABLE == 1)
    #if (_EP4_CFG_EPADR == _EP5_CFG_EPADR)
      #error "The address of Endpoint4 (EPADR) conflicts with Endpoint5."
    #endif
  #endif
  #if (_EP6_ENABLE == 1)
    #if (_EP4_CFG_EPADR == _EP6_CFG_EPADR)
      #error "The address of Endpoint4 (EPADR) conflicts with Endpoint6."
    #endif
  #endif
  #if (_EP7_ENABLE == 1)
    #if (_EP4_CFG_EPADR == _EP7_CFG_EPADR)
      #error "The address of Endpoint4 (EPADR) conflicts with Endpoint7."
    #endif
  #endif
#endif

#if (_EP5_ENABLE == 1)
  #if (_EP5_CFG_EPADR == 0)
    #error "The address of Endpoint5 (EPADR) cannot be 0."
  #endif
  #if (_EP1_ENABLE == 1)
    #if (_EP5_CFG_EPADR == _EP1_CFG_EPADR)
      #error "The address of Endpoint5 (EPADR) conflicts with Endpoint1."
    #endif
  #endif
  #if (_EP2_ENABLE == 1)
    #if (_EP5_CFG_EPADR == _EP2_CFG_EPADR)
      #error "The address of Endpoint5 (EPADR) conflicts with Endpoint2."
    #endif
  #endif
  #if (_EP3_ENABLE == 1)
    #if (_EP5_CFG_EPADR == _EP3_CFG_EPADR)
      #error "The address of Endpoint5 (EPADR) conflicts with Endpoint3."
    #endif
  #endif
  #if (_EP4_ENABLE == 1)
    #if (_EP5_CFG_EPADR == _EP4_CFG_EPADR)
      #error "The address of Endpoint5 (EPADR) conflicts with Endpoint4."
    #endif
  #endif
  #if (_EP6_ENABLE == 1)
    #if (_EP5_CFG_EPADR == _EP6_CFG_EPADR)
      #error "The address of Endpoint5 (EPADR) conflicts with Endpoint6."
    #endif
  #endif
  #if (_EP7_ENABLE == 1)
    #if (_EP5_CFG_EPADR == _EP7_CFG_EPADR)
      #error "The address of Endpoint5 (EPADR) conflicts with Endpoint7."
    #endif
  #endif
#endif

#if (_EP6_ENABLE == 1)
  #if (_EP6_CFG_EPADR == 0)
    #error "The address of Endpoint6 (EPADR) cannot be 0."
  #endif
  #if (_EP1_ENABLE == 1)
    #if (_EP6_CFG_EPADR == _EP1_CFG_EPADR)
      #error "The address of Endpoint6 (EPADR) conflicts with Endpoint1."
    #endif
  #endif
  #if (_EP2_ENABLE == 1)
    #if (_EP6_CFG_EPADR == _EP2_CFG_EPADR)
      #error "The address of Endpoint6 (EPADR) conflicts with Endpoint2."
    #endif
  #endif
  #if (_EP3_ENABLE == 1)
    #if (_EP6_CFG_EPADR == _EP3_CFG_EPADR)
      #error "The address of Endpoint6 (EPADR) conflicts with Endpoint3."
    #endif
  #endif
  #if (_EP4_ENABLE == 1)
    #if (_EP6_CFG_EPADR == _EP4_CFG_EPADR)
      #error "The address of Endpoint6 (EPADR) conflicts with Endpoint4."
    #endif
  #endif
  #if (_EP5_ENABLE == 1)
    #if (_EP6_CFG_EPADR == _EP5_CFG_EPADR)
      #error "The address of Endpoint6 (EPADR) conflicts with Endpoint5."
    #endif
  #endif
  #if (_EP7_ENABLE == 1)
    #if (_EP6_CFG_EPADR == _EP7_CFG_EPADR)
      #error "The address of Endpoint6 (EPADR) conflicts with Endpoint7."
    #endif
  #endif
#endif

#if (_EP7_ENABLE == 1)
  #if (_EP7_CFG_EPADR == 0)
    #error "The address of Endpoint1 (EPADR) cannot be 0."
  #endif
  #if (_EP1_ENABLE == 1)
    #if (_EP7_CFG_EPADR == _EP1_CFG_EPADR)
      #error "The address of Endpoint7 (EPADR) conflicts with Endpoint1."
    #endif
  #endif
  #if (_EP2_ENABLE == 1)
    #if (_EP7_CFG_EPADR == _EP2_CFG_EPADR)
      #error "The address of Endpoint7 (EPADR) conflicts with Endpoint2."
    #endif
  #endif
  #if (_EP3_ENABLE == 1)
    #if (_EP7_CFG_EPADR == _EP3_CFG_EPADR)
      #error "The address of Endpoint7 (EPADR) conflicts with Endpoint3."
    #endif
  #endif
  #if (_EP4_ENABLE == 1)
    #if (_EP7_CFG_EPADR == _EP4_CFG_EPADR)
      #error "The address of Endpoint7 (EPADR) conflicts with Endpoint4."
    #endif
  #endif
  #if (_EP5_ENABLE == 1)
    #if (_EP7_CFG_EPADR == _EP5_CFG_EPADR)
      #error "The address of Endpoint7 (EPADR) conflicts with Endpoint5."
    #endif
  #endif
  #if (_EP6_ENABLE == 1)
    #if (_EP7_CFG_EPADR == _EP6_CFG_EPADR)
      #error "The address of Endpoint7 (EPADR) conflicts with Endpoint6."
    #endif
  #endif
#endif


/*----------------------------------------------------------------------------------------------------------*/
/* Check Buffer size                                                                                        */
/*----------------------------------------------------------------------------------------------------------*/
#if ((_EP0LEN_T + _EP1LEN + _EP2LEN + _EP3LEN + _EP4LEN_T + _EP5LEN_T + _EP6LEN_T + _EP7LEN_T) > 1024)
  #error "Total buffer size of Endpoint 0 ~ 7 must be less than 1024 bytes."
#endif


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
