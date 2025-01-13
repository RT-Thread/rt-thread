/*********************************************************************************************************//**
 * @file    CAN/Send_DATA/ht32_can_config.h
 * @version $Rev:: 8164         $
 * @date    $Date:: 2024-09-20 #$
 * @brief   The header file of CAN baudrate configuration.
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
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_CAN_CONFIG_H
#define __HT32_CAN_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif


//  <q0> Enable CAN Config Check
//     <i> Display related setting by printf().
#define HTCFG_CAN_CONF_CHECK_ENABLE               (0)

//  <h> Core Clock Setting
//  </h>
//  <o0> -- Core Clock Calculation Setting
//     <i> HTCFG_CAN_CORECLKSEL
//     <i> Define the Core Clock by default maximum clock setting or manual input.
//     <i> 0 = Default Maximum (LIBCFG_MAX_SPEED)
//     <i> 1 = Manual Input (HTCFG_CAN_CORECLK_MANUAL)
//       <0=> Default Maximum (LIBCFG_MAX_SPEED)
//       <1=> Manual Input (HTCFG_CAN_CORECLK_MANUAL)
//     <i> Note: CK_CAN = (Core Clock) / (CAN Peripheral Clock Prescaler)
//  <o1> -- Core Clock Manual Input (Hz)
//     <i> HTCFG_CAN_CORECLK_MANUAL
//     <i> Only meaningful when HTCFG_CAN_CLKSEL = 1 (Manual Input)
#define HTCFG_CAN_CORECLKSEL                      (0)         // 0 = Default Maximum (LIBCFG_MAX_SPEED), 1 = Manual Input (HTCFG_CAN_CORECLK_MANUAL)
#define HTCFG_CAN_CORECLK_MANUAL                  (8000000)  // Only meaningful when HTCFG_CAN_CORECLKSEL = 1 (Manual Input)

//  <h> ------------------------------------------
//  </h>

//  <h> CAN Config 0 Setting
//  </h>
//  <o0> CAN Peripheral Clock Selection (CANnPCLK)
//     <i> HTCFG_CAN_CLK_PRESCALER
//       <0=> Div 1
//       <1=> Div 2
//       <2=> Div 4
//       <3=> Div 8
#define HTCFG_CAN_CF0_CLK_DIV                     (0)         // 0 = /1, 1 = /2, 2 = /4, 3 = /8

/*
//  <o> CAN Baudrate
//    <i> HTCFG_CAN_BAUDRATE
//      <1000000=> 1000 kbps
//      <800000=>   800 kbps
//      <500000=>   500 kbps
//      <250000=>   250 kbps
//      <125000=>   125 kbps
//      <100000=>   100 kbps
//      <50000=>     50 kbps
//      <20000=>     20 kbps
//      <10000=>     10 kbps
//      <5000=>       5 kbps
//    <i> The CAN baudrate specifies the frequency of transitions occurring per second.
*/
#define HTCFG_CAN_CF0_BAUDRATE                    (500000)

/*
//  <o> CAN Sample Point Target (%) <50-90:1>
//    <i> HTCFG_CAN_SAMPLE_POINT
//    <i> The Sample Point is the specific location within each bit period where the CAN_Core samples the CAN bus's state (dominant or recessive).
//    <i> Notice: The real calculation result may small than the HTCFG_CAN_SAMPLE_POINT setting.
*/
#define HTCFG_CAN_CF0_SAMPLE_POINT                (70)

//  <o> CAN SJW (Synchronisation Jump Width)
//    <i> HTCFG_CAN_BIT_TIME_SJW
//    <i> The (Re-)Synchronisation Jump Width.
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
#define HTCFG_CAN_CF0_BIT_TIME_SJW                (1)       // 1 ~ 4

#include "ht32_can_config0_calc.h"


#ifdef __cplusplus
}
#endif

#endif
