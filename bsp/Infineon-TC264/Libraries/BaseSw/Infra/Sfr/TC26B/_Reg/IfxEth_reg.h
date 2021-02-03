/**
 * \file IfxEth_reg.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Eth_Cfg Eth address
 * \ingroup IfxLld_Eth
 * 
 * \defgroup IfxLld_Eth_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Eth_Cfg
 * 
 * \defgroup IfxLld_Eth_Cfg_Eth 2-ETH
 * \ingroup IfxLld_Eth_Cfg
 * 
 */
#ifndef IFXETH_REG_H
#define IFXETH_REG_H 1
/******************************************************************************/
#include "IfxEth_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Eth_Cfg_BaseAddress
 * \{  */

/** \brief  ETH object */
#define MODULE_ETH /*lint --e(923)*/ (*(Ifx_ETH*)0xF001D000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Eth_Cfg_Eth
 * \{  */

/** \brief  C, Access Enable Register 0 */
#define ETH_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_ETH_ACCEN0*)0xF001D00Cu)

/** \brief  10, Access Enable Register 1 */
#define ETH_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_ETH_ACCEN1*)0xF001D010u)

/** \brief  202C, Register 11 - AHB or AXI Status Register */
#define ETH_AHB_OR_AXI_STATUS /*lint --e(923)*/ (*(volatile Ifx_ETH_AHB_OR_AXI_STATUS*)0xF001F02Cu)

/** \brief  2000, Register 0 - Bus Mode Register */
#define ETH_BUS_MODE /*lint --e(923)*/ (*(volatile Ifx_ETH_BUS_MODE*)0xF001F000u)

/** \brief  0, Clock Control Register */
#define ETH_CLC /*lint --e(923)*/ (*(volatile Ifx_ETH_CLC*)0xF001D000u)

/** \brief  2054, Register 21 - Current Host Receive Buffer Address Register */
#define ETH_CURRENT_HOST_RECEIVE_BUFFER_ADDRESS /*lint --e(923)*/ (*(volatile Ifx_ETH_CURRENT_HOST_RECEIVE_BUFFER_ADDRESS*)0xF001F054u)

/** \brief  204C, Register 19 - Current Host Receive Descriptor Register */
#define ETH_CURRENT_HOST_RECEIVE_DESCRIPTOR /*lint --e(923)*/ (*(volatile Ifx_ETH_CURRENT_HOST_RECEIVE_DESCRIPTOR*)0xF001F04Cu)

/** \brief  2050, Register 20 - Current Host Transmit Buffer Address Register */
#define ETH_CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS /*lint --e(923)*/ (*(volatile Ifx_ETH_CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS*)0xF001F050u)

/** \brief  2048, Register 18 - Current Host Transmit Descriptor Register */
#define ETH_CURRENT_HOST_TRANSMIT_DESCRIPTOR /*lint --e(923)*/ (*(volatile Ifx_ETH_CURRENT_HOST_TRANSMIT_DESCRIPTOR*)0xF001F048u)

/** \brief  1024, Register 9 - Debug Register */
#define ETH_DEBUG /*lint --e(923)*/ (*(volatile Ifx_ETH_DEBUG*)0xF001E024u)

/** \brief  1018, Register 6 - Flow Control Register */
#define ETH_FLOW_CONTROL /*lint --e(923)*/ (*(volatile Ifx_ETH_FLOW_CONTROL*)0xF001E018u)

/** \brief  1010, Register 4 - GMII Address Register */
#define ETH_GMII_ADDRESS /*lint --e(923)*/ (*(volatile Ifx_ETH_GMII_ADDRESS*)0xF001E010u)

/** \brief  1014, Register 5 - GMII Data Register */
#define ETH_GMII_DATA /*lint --e(923)*/ (*(volatile Ifx_ETH_GMII_DATA*)0xF001E014u)

/** \brief  8, Input and Output Control Register */
#define ETH_GPCTL /*lint --e(923)*/ (*(volatile Ifx_ETH_GPCTL*)0xF001D008u)

/** \brief  1008, Register 2 - Hash Table High Register */
#define ETH_HASH_TABLE_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_HASH_TABLE_HIGH*)0xF001E008u)

/** \brief  100C, Register 3 - Hash Table Low Register */
#define ETH_HASH_TABLE_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_HASH_TABLE_LOW*)0xF001E00Cu)

/** \brief  2058, Register 22 - HW Feature Register */
#define ETH_HW_FEATURE /*lint --e(923)*/ (*(volatile Ifx_ETH_HW_FEATURE*)0xF001F058u)

/** \brief  4, Module Identification Register */
#define ETH_ID /*lint --e(923)*/ (*(volatile Ifx_ETH_ID*)0xF001D004u)

/** \brief  201C, Register 7 - Interrupt Enable Register */
#define ETH_INTERRUPT_ENABLE /*lint --e(923)*/ (*(volatile Ifx_ETH_INTERRUPT_ENABLE*)0xF001F01Cu)

/** \brief  103C, Register 15 - Interrupt Mask Register */
#define ETH_INTERRUPT_MASK /*lint --e(923)*/ (*(volatile Ifx_ETH_INTERRUPT_MASK*)0xF001E03Cu)

/** \brief  1038, Register 14 - Interrupt Register */
#define ETH_INTERRUPT_STATUS /*lint --e(923)*/ (*(volatile Ifx_ETH_INTERRUPT_STATUS*)0xF001E038u)

/** \brief  14, Kernel Reset Register 0 */
#define ETH_KRST0 /*lint --e(923)*/ (*(volatile Ifx_ETH_KRST0*)0xF001D014u)

/** \brief  18, Kernel Reset Register 1 */
#define ETH_KRST1 /*lint --e(923)*/ (*(volatile Ifx_ETH_KRST1*)0xF001D018u)

/** \brief  1C, Kernel Reset Status Clear Register */
#define ETH_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_ETH_KRSTCLR*)0xF001D01Cu)

/** \brief  1040, MAC Address High Register */
#define ETH_MAC_ADDRESS_G00_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E040u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G00_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G00_HIGH.
*/
#define	ETH_MAC_ADDRESS0_HIGH	(ETH_MAC_ADDRESS_G00_HIGH)

/** \brief  1044, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G00_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E044u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G00_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G00_LOW.
*/
#define	ETH_MAC_ADDRESS0_LOW	(ETH_MAC_ADDRESS_G00_LOW)

/** \brief  1090, MAC Address High Register */
#define ETH_MAC_ADDRESS_G010_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E090u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G010_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G010_HIGH.
*/
#define	ETH_MAC_ADDRESS10_HIGH	(ETH_MAC_ADDRESS_G010_HIGH)

/** \brief  1094, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G010_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E094u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G010_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G010_LOW.
*/
#define	ETH_MAC_ADDRESS10_LOW	(ETH_MAC_ADDRESS_G010_LOW)

/** \brief  1098, MAC Address High Register */
#define ETH_MAC_ADDRESS_G011_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E098u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G011_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G011_HIGH.
*/
#define	ETH_MAC_ADDRESS11_HIGH	(ETH_MAC_ADDRESS_G011_HIGH)

/** \brief  109C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G011_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E09Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G011_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G011_LOW.
*/
#define	ETH_MAC_ADDRESS11_LOW	(ETH_MAC_ADDRESS_G011_LOW)

/** \brief  10A0, MAC Address High Register */
#define ETH_MAC_ADDRESS_G012_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E0A0u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G012_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G012_HIGH.
*/
#define	ETH_MAC_ADDRESS12_HIGH	(ETH_MAC_ADDRESS_G012_HIGH)

/** \brief  10A4, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G012_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E0A4u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G012_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G012_LOW.
*/
#define	ETH_MAC_ADDRESS12_LOW	(ETH_MAC_ADDRESS_G012_LOW)

/** \brief  10A8, MAC Address High Register */
#define ETH_MAC_ADDRESS_G013_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E0A8u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G013_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G013_HIGH.
*/
#define	ETH_MAC_ADDRESS13_HIGH	(ETH_MAC_ADDRESS_G013_HIGH)

/** \brief  10AC, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G013_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E0ACu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G013_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G013_LOW.
*/
#define	ETH_MAC_ADDRESS13_LOW	(ETH_MAC_ADDRESS_G013_LOW)

/** \brief  10B0, MAC Address High Register */
#define ETH_MAC_ADDRESS_G014_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E0B0u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G014_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G014_HIGH.
*/
#define	ETH_MAC_ADDRESS14_HIGH	(ETH_MAC_ADDRESS_G014_HIGH)

/** \brief  10B4, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G014_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E0B4u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G014_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G014_LOW.
*/
#define	ETH_MAC_ADDRESS14_LOW	(ETH_MAC_ADDRESS_G014_LOW)

/** \brief  10B8, MAC Address High Register */
#define ETH_MAC_ADDRESS_G015_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E0B8u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G015_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G015_HIGH.
*/
#define	ETH_MAC_ADDRESS15_HIGH	(ETH_MAC_ADDRESS_G015_HIGH)

/** \brief  10BC, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G015_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E0BCu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G015_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G015_LOW.
*/
#define	ETH_MAC_ADDRESS15_LOW	(ETH_MAC_ADDRESS_G015_LOW)

/** \brief  1048, MAC Address High Register */
#define ETH_MAC_ADDRESS_G01_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E048u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G01_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G01_HIGH.
*/
#define	ETH_MAC_ADDRESS1_HIGH	(ETH_MAC_ADDRESS_G01_HIGH)

/** \brief  104C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G01_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E04Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G01_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G01_LOW.
*/
#define	ETH_MAC_ADDRESS1_LOW	(ETH_MAC_ADDRESS_G01_LOW)

/** \brief  1050, MAC Address High Register */
#define ETH_MAC_ADDRESS_G02_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E050u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G02_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G02_HIGH.
*/
#define	ETH_MAC_ADDRESS2_HIGH	(ETH_MAC_ADDRESS_G02_HIGH)

/** \brief  1054, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G02_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E054u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G02_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G02_LOW.
*/
#define	ETH_MAC_ADDRESS2_LOW	(ETH_MAC_ADDRESS_G02_LOW)

/** \brief  1058, MAC Address High Register */
#define ETH_MAC_ADDRESS_G03_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E058u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G03_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G03_HIGH.
*/
#define	ETH_MAC_ADDRESS3_HIGH	(ETH_MAC_ADDRESS_G03_HIGH)

/** \brief  105C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G03_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E05Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G03_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G03_LOW.
*/
#define	ETH_MAC_ADDRESS3_LOW	(ETH_MAC_ADDRESS_G03_LOW)

/** \brief  1060, MAC Address High Register */
#define ETH_MAC_ADDRESS_G04_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E060u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G04_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G04_HIGH.
*/
#define	ETH_MAC_ADDRESS4_HIGH	(ETH_MAC_ADDRESS_G04_HIGH)

/** \brief  1064, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G04_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E064u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G04_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G04_LOW.
*/
#define	ETH_MAC_ADDRESS4_LOW	(ETH_MAC_ADDRESS_G04_LOW)

/** \brief  1068, MAC Address High Register */
#define ETH_MAC_ADDRESS_G05_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E068u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G05_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G05_HIGH.
*/
#define	ETH_MAC_ADDRESS5_HIGH	(ETH_MAC_ADDRESS_G05_HIGH)

/** \brief  106C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G05_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E06Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G05_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G05_LOW.
*/
#define	ETH_MAC_ADDRESS5_LOW	(ETH_MAC_ADDRESS_G05_LOW)

/** \brief  1070, MAC Address High Register */
#define ETH_MAC_ADDRESS_G06_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E070u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G06_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G06_HIGH.
*/
#define	ETH_MAC_ADDRESS6_HIGH	(ETH_MAC_ADDRESS_G06_HIGH)

/** \brief  1074, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G06_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E074u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G06_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G06_LOW.
*/
#define	ETH_MAC_ADDRESS6_LOW	(ETH_MAC_ADDRESS_G06_LOW)

/** \brief  1078, MAC Address High Register */
#define ETH_MAC_ADDRESS_G07_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E078u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G07_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G07_HIGH.
*/
#define	ETH_MAC_ADDRESS7_HIGH	(ETH_MAC_ADDRESS_G07_HIGH)

/** \brief  107C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G07_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E07Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G07_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G07_LOW.
*/
#define	ETH_MAC_ADDRESS7_LOW	(ETH_MAC_ADDRESS_G07_LOW)

/** \brief  1080, MAC Address High Register */
#define ETH_MAC_ADDRESS_G08_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E080u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G08_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G08_HIGH.
*/
#define	ETH_MAC_ADDRESS8_HIGH	(ETH_MAC_ADDRESS_G08_HIGH)

/** \brief  1084, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G08_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E084u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G08_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G08_LOW.
*/
#define	ETH_MAC_ADDRESS8_LOW	(ETH_MAC_ADDRESS_G08_LOW)

/** \brief  1088, MAC Address High Register */
#define ETH_MAC_ADDRESS_G09_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E088u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G09_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G09_HIGH.
*/
#define	ETH_MAC_ADDRESS9_HIGH	(ETH_MAC_ADDRESS_G09_HIGH)

/** \brief  108C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G09_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E08Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G09_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G09_LOW.
*/
#define	ETH_MAC_ADDRESS9_LOW	(ETH_MAC_ADDRESS_G09_LOW)

/** \brief  1800, MAC Address High Register */
#define ETH_MAC_ADDRESS_G10_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E800u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G10_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G10_HIGH.
*/
#define	ETH_MAC_ADDRESS16_HIGH	(ETH_MAC_ADDRESS_G10_HIGH)

/** \brief  1804, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G10_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E804u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G10_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G10_LOW.
*/
#define	ETH_MAC_ADDRESS16_LOW	(ETH_MAC_ADDRESS_G10_LOW)

/** \brief  1850, MAC Address High Register */
#define ETH_MAC_ADDRESS_G110_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E850u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G110_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G110_HIGH.
*/
#define	ETH_MAC_ADDRESS26_HIGH	(ETH_MAC_ADDRESS_G110_HIGH)

/** \brief  1854, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G110_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E854u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G110_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G110_LOW.
*/
#define	ETH_MAC_ADDRESS26_LOW	(ETH_MAC_ADDRESS_G110_LOW)

/** \brief  1858, MAC Address High Register */
#define ETH_MAC_ADDRESS_G111_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E858u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G111_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G111_HIGH.
*/
#define	ETH_MAC_ADDRESS27_HIGH	(ETH_MAC_ADDRESS_G111_HIGH)

/** \brief  185C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G111_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E85Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G111_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G111_LOW.
*/
#define	ETH_MAC_ADDRESS27_LOW	(ETH_MAC_ADDRESS_G111_LOW)

/** \brief  1860, MAC Address High Register */
#define ETH_MAC_ADDRESS_G112_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E860u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G112_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G112_HIGH.
*/
#define	ETH_MAC_ADDRESS28_HIGH	(ETH_MAC_ADDRESS_G112_HIGH)

/** \brief  1864, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G112_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E864u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G112_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G112_LOW.
*/
#define	ETH_MAC_ADDRESS28_LOW	(ETH_MAC_ADDRESS_G112_LOW)

/** \brief  1868, MAC Address High Register */
#define ETH_MAC_ADDRESS_G113_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E868u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G113_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G113_HIGH.
*/
#define	ETH_MAC_ADDRESS29_HIGH	(ETH_MAC_ADDRESS_G113_HIGH)

/** \brief  186C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G113_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E86Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G113_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G113_LOW.
*/
#define	ETH_MAC_ADDRESS29_LOW	(ETH_MAC_ADDRESS_G113_LOW)

/** \brief  1870, MAC Address High Register */
#define ETH_MAC_ADDRESS_G114_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E870u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G114_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G114_HIGH.
*/
#define	ETH_MAC_ADDRESS30_HIGH	(ETH_MAC_ADDRESS_G114_HIGH)

/** \brief  1874, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G114_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E874u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G114_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G114_LOW.
*/
#define	ETH_MAC_ADDRESS30_LOW	(ETH_MAC_ADDRESS_G114_LOW)

/** \brief  1878, MAC Address High Register */
#define ETH_MAC_ADDRESS_G115_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E878u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G115_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G115_HIGH.
*/
#define	ETH_MAC_ADDRESS31_HIGH	(ETH_MAC_ADDRESS_G115_HIGH)

/** \brief  187C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G115_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E87Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G115_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G115_LOW.
*/
#define	ETH_MAC_ADDRESS31_LOW	(ETH_MAC_ADDRESS_G115_LOW)

/** \brief  1808, MAC Address High Register */
#define ETH_MAC_ADDRESS_G11_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E808u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G11_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G11_HIGH.
*/
#define	ETH_MAC_ADDRESS17_HIGH	(ETH_MAC_ADDRESS_G11_HIGH)

/** \brief  180C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G11_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E80Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G11_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G11_LOW.
*/
#define	ETH_MAC_ADDRESS17_LOW	(ETH_MAC_ADDRESS_G11_LOW)

/** \brief  1810, MAC Address High Register */
#define ETH_MAC_ADDRESS_G12_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E810u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G12_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G12_HIGH.
*/
#define	ETH_MAC_ADDRESS18_HIGH	(ETH_MAC_ADDRESS_G12_HIGH)

/** \brief  1814, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G12_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E814u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G12_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G12_LOW.
*/
#define	ETH_MAC_ADDRESS18_LOW	(ETH_MAC_ADDRESS_G12_LOW)

/** \brief  1818, MAC Address High Register */
#define ETH_MAC_ADDRESS_G13_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E818u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G13_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G13_HIGH.
*/
#define	ETH_MAC_ADDRESS19_HIGH	(ETH_MAC_ADDRESS_G13_HIGH)

/** \brief  181C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G13_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E81Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G13_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G13_LOW.
*/
#define	ETH_MAC_ADDRESS19_LOW	(ETH_MAC_ADDRESS_G13_LOW)

/** \brief  1820, MAC Address High Register */
#define ETH_MAC_ADDRESS_G14_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E820u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G14_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G14_HIGH.
*/
#define	ETH_MAC_ADDRESS20_HIGH	(ETH_MAC_ADDRESS_G14_HIGH)

/** \brief  1824, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G14_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E824u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G14_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G14_LOW.
*/
#define	ETH_MAC_ADDRESS20_LOW	(ETH_MAC_ADDRESS_G14_LOW)

/** \brief  1828, MAC Address High Register */
#define ETH_MAC_ADDRESS_G15_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E828u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G15_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G15_HIGH.
*/
#define	ETH_MAC_ADDRESS21_HIGH	(ETH_MAC_ADDRESS_G15_HIGH)

/** \brief  182C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G15_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E82Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G15_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G15_LOW.
*/
#define	ETH_MAC_ADDRESS21_LOW	(ETH_MAC_ADDRESS_G15_LOW)

/** \brief  1830, MAC Address High Register */
#define ETH_MAC_ADDRESS_G16_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E830u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G16_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G16_HIGH.
*/
#define	ETH_MAC_ADDRESS22_HIGH	(ETH_MAC_ADDRESS_G16_HIGH)

/** \brief  1834, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G16_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E834u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G16_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G16_LOW.
*/
#define	ETH_MAC_ADDRESS22_LOW	(ETH_MAC_ADDRESS_G16_LOW)

/** \brief  1838, MAC Address High Register */
#define ETH_MAC_ADDRESS_G17_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E838u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G17_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G17_HIGH.
*/
#define	ETH_MAC_ADDRESS23_HIGH	(ETH_MAC_ADDRESS_G17_HIGH)

/** \brief  183C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G17_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E83Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G17_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G17_LOW.
*/
#define	ETH_MAC_ADDRESS23_LOW	(ETH_MAC_ADDRESS_G17_LOW)

/** \brief  1840, MAC Address High Register */
#define ETH_MAC_ADDRESS_G18_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E840u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G18_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G18_HIGH.
*/
#define	ETH_MAC_ADDRESS24_HIGH	(ETH_MAC_ADDRESS_G18_HIGH)

/** \brief  1844, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G18_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E844u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G18_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G18_LOW.
*/
#define	ETH_MAC_ADDRESS24_LOW	(ETH_MAC_ADDRESS_G18_LOW)

/** \brief  1848, MAC Address High Register */
#define ETH_MAC_ADDRESS_G19_HIGH /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_HIGH*)0xF001E848u)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G19_HIGH.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G19_HIGH.
*/
#define	ETH_MAC_ADDRESS25_HIGH	(ETH_MAC_ADDRESS_G19_HIGH)

/** \brief  184C, MAC Address Low Register */
#define ETH_MAC_ADDRESS_G19_LOW /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_ADDRESS_LOW*)0xF001E84Cu)

/** Alias (User Manual Name) for ETH_MAC_ADDRESS_G19_LOW.
* To use register names with standard convension, please use ETH_MAC_ADDRESS_G19_LOW.
*/
#define	ETH_MAC_ADDRESS25_LOW	(ETH_MAC_ADDRESS_G19_LOW)

/** \brief  1000, Register 0 - MAC Configuration Register */
#define ETH_MAC_CONFIGURATION /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_CONFIGURATION*)0xF001E000u)

/** \brief  1004, Register 1 - MAC Frame Filter */
#define ETH_MAC_FRAME_FILTER /*lint --e(923)*/ (*(volatile Ifx_ETH_MAC_FRAME_FILTER*)0xF001E004u)

/** \brief  2020, Register 8 - Missed Frame and Buffer Overflow Counter Register */
#define ETH_MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER /*lint --e(923)*/ (*(volatile Ifx_ETH_MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER*)0xF001F020u)

/** \brief  1100, Register 64 - MMC Control Register */
#define ETH_MMC_CONTROL /*lint --e(923)*/ (*(volatile Ifx_ETH_MMC_CONTROL*)0xF001E100u)

/** \brief  1208, Register 130 - MMC Receive Checksum Offload Interrupt Register */
#define ETH_MMC_IPC_RECEIVE_INTERRUPT /*lint --e(923)*/ (*(volatile Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT*)0xF001E208u)

/** \brief  1200, Register 128 - MMC Receive Checksum Offload Interrupt Mask
 * Register */
#define ETH_MMC_IPC_RECEIVE_INTERRUPT_MASK /*lint --e(923)*/ (*(volatile Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_MASK*)0xF001E200u)

/** \brief  1104, Register 65 - MMC Receive Interrupt Register */
#define ETH_MMC_RECEIVE_INTERRUPT /*lint --e(923)*/ (*(volatile Ifx_ETH_MMC_RECEIVE_INTERRUPT*)0xF001E104u)

/** \brief  110C, - */
#define ETH_MMC_RECEIVE_INTERRUPT_MASK /*lint --e(923)*/ (*(volatile Ifx_ETH_MMC_RECEIVE_INTERRUPT_MASK*)0xF001E10Cu)

/** \brief  1108, Register 66 - MMC Transmit Interrupt Register */
#define ETH_MMC_TRANSMIT_INTERRUPT /*lint --e(923)*/ (*(volatile Ifx_ETH_MMC_TRANSMIT_INTERRUPT*)0xF001E108u)

/** \brief  1110, Register 68 - MMC Transmit Interrupt Mask Register */
#define ETH_MMC_TRANSMIT_INTERRUPT_MASK /*lint --e(923)*/ (*(volatile Ifx_ETH_MMC_TRANSMIT_INTERRUPT_MASK*)0xF001E110u)

/** \brief  2018, Register 6 - Operation Mode Register */
#define ETH_OPERATION_MODE /*lint --e(923)*/ (*(volatile Ifx_ETH_OPERATION_MODE*)0xF001F018u)

/** \brief  102C, Register 11 - PMT Control and Status Register */
#define ETH_PMT_CONTROL_STATUS /*lint --e(923)*/ (*(volatile Ifx_ETH_PMT_CONTROL_STATUS*)0xF001E02Cu)

/** \brief  172C, Register 459 - PPS Control Register */
#define ETH_PPS_CONTROL /*lint --e(923)*/ (*(volatile Ifx_ETH_PPS_CONTROL*)0xF001E72Cu)

/** \brief  200C, Register 3 - Receive Descriptor List Address Register */
#define ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS /*lint --e(923)*/ (*(volatile Ifx_ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS*)0xF001F00Cu)

/** \brief  2024, Register 9 - Receive Interrupt Watchdog Timer Register */
#define ETH_RECEIVE_INTERRUPT_WATCHDOG_TIMER /*lint --e(923)*/ (*(volatile Ifx_ETH_RECEIVE_INTERRUPT_WATCHDOG_TIMER*)0xF001F024u)

/** \brief  2008, Register 2 - Receive Poll Demand Register */
#define ETH_RECEIVE_POLL_DEMAND /*lint --e(923)*/ (*(volatile Ifx_ETH_RECEIVE_POLL_DEMAND*)0xF001F008u)

/** \brief  1028, Register 10 - Remote Wake-Up Frame Filter Register */
#define ETH_REMOTE_WAKE_UP_FRAME_FILTER /*lint --e(923)*/ (*(volatile Ifx_ETH_REMOTE_WAKE_UP_FRAME_FILTER*)0xF001E028u)

/** \brief  11C0, Register 112 - Receive Frame Count for Good and Bad 1,024 to
 * Maxsize Bytes Frames */
#define ETH_RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD*)0xF001E1C0u)

/** \brief  11B4, Register 109 - Receive Frame Count for Good and Bad 128 to 255
 * Bytes Frames */
#define ETH_RX_128TO255OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_128TO255OCTETS_FRAMES_GOOD_BAD*)0xF001E1B4u)

/** \brief  11B8, Register 110 - Receive Frame Count for Good and Bad 256 to 511
 * Bytes Frames */
#define ETH_RX_256TO511OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_256TO511OCTETS_FRAMES_GOOD_BAD*)0xF001E1B8u)

/** \brief  11BC, Register 111 - Receive Frame Count for Good and Bad 512 to
 * 1,023 Bytes Frames */
#define ETH_RX_512TO1023OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_512TO1023OCTETS_FRAMES_GOOD_BAD*)0xF001E1BCu)

/** \brief  11AC, Register 107 - Receive Frame Count for Good and Bad 64 Byte
 * Frames */
#define ETH_RX_64OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_64OCTETS_FRAMES_GOOD_BAD*)0xF001E1ACu)

/** \brief  11B0, Register 108 - Receive Frame Count for Good and Bad 65 to 127
 * Bytes Frames */
#define ETH_RX_65TO127OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_65TO127OCTETS_FRAMES_GOOD_BAD*)0xF001E1B0u)

/** \brief  1198, Register 102 - Receive Frame Count for Alignment Error Frames */
#define ETH_RX_ALIGNMENT_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_ALIGNMENT_ERROR_FRAMES*)0xF001E198u)

/** \brief  118C, Register 99 - Receive Frame Count for Good Broadcast Frames */
#define ETH_RX_BROADCAST_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_BROADCAST_FRAMES_GOOD*)0xF001E18Cu)

/** \brief  11E4, Register 121 - Receive Frame Count for Good Control Frames
 * Frames */
#define ETH_RX_CONTROL_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_CONTROL_FRAMES_GOOD*)0xF001E1E4u)

/** \brief  1194, Register 101 - Receive Frame Count for CRC Error Frames */
#define ETH_RX_CRC_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_CRC_ERROR_FRAMES*)0xF001E194u)

/** \brief  11D4, Register 117 - Receive Frame Count for FIFO Overflow Frames */
#define ETH_RX_FIFO_OVERFLOW_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_FIFO_OVERFLOW_FRAMES*)0xF001E1D4u)

/** \brief  1180, Register 96 - Receive Frame Count for Good and Bad Frames */
#define ETH_RX_FRAMES_COUNT_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_FRAMES_COUNT_GOOD_BAD*)0xF001E180u)

/** \brief  11A0, Register 104 - Receive Frame Count for Jabber Error Frames */
#define ETH_RX_JABBER_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_JABBER_ERROR_FRAMES*)0xF001E1A0u)

/** \brief  11C8, Register 114 - Receive Frame Count for Length Error Frames */
#define ETH_RX_LENGTH_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_LENGTH_ERROR_FRAMES*)0xF001E1C8u)

/** \brief  1190, Register 100 - Receive Frame Count for Good Multicast Frames */
#define ETH_RX_MULTICAST_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_MULTICAST_FRAMES_GOOD*)0xF001E190u)

/** \brief  1188, Register 98 - Receive Octet Count for Good Frames */
#define ETH_RX_OCTET_COUNT_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_OCTET_COUNT_GOOD*)0xF001E188u)

/** \brief  1184, Register 97 - Receive Octet Count for Good and Bad Frames */
#define ETH_RX_OCTET_COUNT_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_OCTET_COUNT_GOOD_BAD*)0xF001E184u)

/** \brief  11CC, Register 115 - Receive Frame Count for Out of Range Frames */
#define ETH_RX_OUT_OF_RANGE_TYPE_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_OUT_OF_RANGE_TYPE_FRAMES*)0xF001E1CCu)

/** \brief  11A8, Register 106 - Receive Frame Count for Oversize Frames */
#define ETH_RX_OVERSIZE_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_OVERSIZE_FRAMES_GOOD*)0xF001E1A8u)

/** \brief  11D0, Register 116 - Receive Frame Count for PAUSE Frames */
#define ETH_RX_PAUSE_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_PAUSE_FRAMES*)0xF001E1D0u)

/** \brief  11E0, Register 120 - Receive Frame Count for Receive Error Frames */
#define ETH_RX_RECEIVE_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_RECEIVE_ERROR_FRAMES*)0xF001E1E0u)

/** \brief  119C, Register 103 - Receive Frame Count for Runt Error Frames */
#define ETH_RX_RUNT_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_RUNT_ERROR_FRAMES*)0xF001E19Cu)

/** \brief  11A4, Register 105 - Receive Frame Count for Undersize Frames */
#define ETH_RX_UNDERSIZE_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_UNDERSIZE_FRAMES_GOOD*)0xF001E1A4u)

/** \brief  11C4, Register 113 - Receive Frame Count for Good Unicast Frames */
#define ETH_RX_UNICAST_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_UNICAST_FRAMES_GOOD*)0xF001E1C4u)

/** \brief  11D8, Register 118 - Receive Frame Count for Good and Bad VLAN
 * Frames */
#define ETH_RX_VLAN_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_VLAN_FRAMES_GOOD_BAD*)0xF001E1D8u)

/** \brief  11DC, Register 119 - Receive Frame Count for Watchdog Error Frames */
#define ETH_RX_WATCHDOG_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RX_WATCHDOG_ERROR_FRAMES*)0xF001E1DCu)

/** \brief  1244, Register 145 - Receive ICMP Error Frame Counter Register */
#define ETH_RXICMP_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXICMP_ERROR_FRAMES*)0xF001E244u)

/** \brief  1284, Register 161 - Receive ICMP Error Octet Counter Register */
#define ETH_RXICMP_ERROR_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXICMP_ERROR_OCTETS*)0xF001E284u)

/** \brief  1240, Register 144 - Receive ICMP Good Frame Counter Register */
#define ETH_RXICMP_GOOD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXICMP_GOOD_FRAMES*)0xF001E240u)

/** \brief  1280, Register 160 - Receive ICMP Good Octet Counter Register */
#define ETH_RXICMP_GOOD_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXICMP_GOOD_OCTETS*)0xF001E280u)

/** \brief  121C, Register 135 - Receive IPV4 Fragmented Frame Counter Register */
#define ETH_RXIPV4_FRAGMENTED_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_FRAGMENTED_FRAMES*)0xF001E21Cu)

/** \brief  125C, Register 151 - Receive IPV4 Fragmented Octet Counter Register */
#define ETH_RXIPV4_FRAGMENTED_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_FRAGMENTED_OCTETS*)0xF001E25Cu)

/** \brief  1210, Register 132 - Receive IPV4 Good Frame Counter Register */
#define ETH_RXIPV4_GOOD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_GOOD_FRAMES*)0xF001E210u)

/** \brief  1250, Register 148 - Receive IPV4 Good Octet Counter Register */
#define ETH_RXIPV4_GOOD_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_GOOD_OCTETS*)0xF001E250u)

/** \brief  1214, Register 133 - Receive IPV4 Header Error Frame Counter
 * Register */
#define ETH_RXIPV4_HEADER_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_HEADER_ERROR_FRAMES*)0xF001E214u)

/** \brief  1254, Register 149 - Receive IPV4 Header Error Octet Counter
 * Register */
#define ETH_RXIPV4_HEADER_ERROR_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_HEADER_ERROR_OCTETS*)0xF001E254u)

/** \brief  1218, Register 134 - Receive IPV4 No Payload Frame Counter Register */
#define ETH_RXIPV4_NO_PAYLOAD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_NO_PAYLOAD_FRAMES*)0xF001E218u)

/** \brief  1258, Register 150 - Receive IPV4 No Payload Octet Counter Register */
#define ETH_RXIPV4_NO_PAYLOAD_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_NO_PAYLOAD_OCTETS*)0xF001E258u)

/** \brief  1260, Register 152 - Receive IPV4 Fragmented Octet Counter Register */
#define ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS*)0xF001E260u)

/** \brief  1220, Register 136 - Receive IPV4 UDP Checksum Disabled Frame
 * Counter Register */
#define ETH_RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES*)0xF001E220u)

/** \brief  1224, Register 137 - Receive IPV6 Good Frame Counter Register */
#define ETH_RXIPV6_GOOD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV6_GOOD_FRAMES*)0xF001E224u)

/** \brief  1264, Register 153 - Receive IPV6 Good Octet Counter Register */
#define ETH_RXIPV6_GOOD_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV6_GOOD_OCTETS*)0xF001E264u)

/** \brief  1228, Register 138 - Receive IPV6 Header Error Frame Counter
 * Register */
#define ETH_RXIPV6_HEADER_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV6_HEADER_ERROR_FRAMES*)0xF001E228u)

/** \brief  1268, Register 154 - Receive IPV6 Header Error Octet Counter
 * Register */
#define ETH_RXIPV6_HEADER_ERROR_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV6_HEADER_ERROR_OCTETS*)0xF001E268u)

/** \brief  122C, Register 139 - Receive IPV6 No Payload Frame Counter Register */
#define ETH_RXIPV6_NO_PAYLOAD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV6_NO_PAYLOAD_FRAMES*)0xF001E22Cu)

/** \brief  126C, Register 155 - Receive IPV6 No Payload Octet Counter Register */
#define ETH_RXIPV6_NO_PAYLOAD_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXIPV6_NO_PAYLOAD_OCTETS*)0xF001E26Cu)

/** \brief  123C, Register 143 - Receive TCP Error Frame Counter Register */
#define ETH_RXTCP_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXTCP_ERROR_FRAMES*)0xF001E23Cu)

/** \brief  127C, Register 159 - Receive TCP Error Octet Counter Register */
#define ETH_RXTCP_ERROR_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXTCP_ERROR_OCTETS*)0xF001E27Cu)

/** \brief  1238, Register 142 - Receive TCP Good Frame Counter Register */
#define ETH_RXTCP_GOOD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXTCP_GOOD_FRAMES*)0xF001E238u)

/** \brief  1278, Register 158 - Receive TCP Good Octet Counter Register */
#define ETH_RXTCP_GOOD_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXTCP_GOOD_OCTETS*)0xF001E278u)

/** \brief  1234, Register 141 - Receive UDP Error Frame Counter Register */
#define ETH_RXUDP_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXUDP_ERROR_FRAMES*)0xF001E234u)

/** \brief  1274, Register 157 - Receive UDP Error Octet Counter Register */
#define ETH_RXUDP_ERROR_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXUDP_ERROR_OCTETS*)0xF001E274u)

/** \brief  1230, Register 140 - Receive UDP Good Frame Counter Register */
#define ETH_RXUDP_GOOD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_RXUDP_GOOD_FRAMES*)0xF001E230u)

/** \brief  1270, Register 156 - Receive UDP Good Octet Counter Register */
#define ETH_RXUDP_GOOD_OCTETS /*lint --e(923)*/ (*(volatile Ifx_ETH_RXUDP_GOOD_OCTETS*)0xF001E270u)

/** \brief  2014, Register 5 - Status Register */
#define ETH_STATUS /*lint --e(923)*/ (*(volatile Ifx_ETH_STATUS*)0xF001F014u)

/** \brief  1704, Register 449 - Sub-Second Increment Register */
#define ETH_SUB_SECOND_INCREMENT /*lint --e(923)*/ (*(volatile Ifx_ETH_SUB_SECOND_INCREMENT*)0xF001E704u)

/** \brief  1724, Register 457 - System Time - Higher Word Seconds Register */
#define ETH_SYSTEM_TIME_HIGHER_WORD_SECONDS /*lint --e(923)*/ (*(volatile Ifx_ETH_SYSTEM_TIME_HIGHER_WORD_SECONDS*)0xF001E724u)

/** \brief  170C, Register 451 - System Time - Nanoseconds Register */
#define ETH_SYSTEM_TIME_NANOSECONDS /*lint --e(923)*/ (*(volatile Ifx_ETH_SYSTEM_TIME_NANOSECONDS*)0xF001E70Cu)

/** \brief  1714, Register 453 - System Time - Nanoseconds Update Register */
#define ETH_SYSTEM_TIME_NANOSECONDS_UPDATE /*lint --e(923)*/ (*(volatile Ifx_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE*)0xF001E714u)

/** \brief  1708, Register 450 - System Time - Seconds Register */
#define ETH_SYSTEM_TIME_SECONDS /*lint --e(923)*/ (*(volatile Ifx_ETH_SYSTEM_TIME_SECONDS*)0xF001E708u)

/** \brief  1710, Register 452 - System Time - Seconds Update Register */
#define ETH_SYSTEM_TIME_SECONDS_UPDATE /*lint --e(923)*/ (*(volatile Ifx_ETH_SYSTEM_TIME_SECONDS_UPDATE*)0xF001E710u)

/** \brief  1720, Register 456 - Target Time Nanoseconds Register */
#define ETH_TARGET_TIME_NANOSECONDS /*lint --e(923)*/ (*(volatile Ifx_ETH_TARGET_TIME_NANOSECONDS*)0xF001E720u)

/** \brief  171C, Register 455 - Target Time Seconds Register */
#define ETH_TARGET_TIME_SECONDS /*lint --e(923)*/ (*(volatile Ifx_ETH_TARGET_TIME_SECONDS*)0xF001E71Cu)

/** \brief  1718, Register 454 - Timestamp Addend Register */
#define ETH_TIMESTAMP_ADDEND /*lint --e(923)*/ (*(volatile Ifx_ETH_TIMESTAMP_ADDEND*)0xF001E718u)

/** \brief  1700, Register 448 - Timestamp Control Register */
#define ETH_TIMESTAMP_CONTROL /*lint --e(923)*/ (*(volatile Ifx_ETH_TIMESTAMP_CONTROL*)0xF001E700u)

/** \brief  1728, Register 458 - Timestamp Status Register */
#define ETH_TIMESTAMP_STATUS /*lint --e(923)*/ (*(volatile Ifx_ETH_TIMESTAMP_STATUS*)0xF001E728u)

/** \brief  2010, Register 4 - Transmit Descriptor List Address Register */
#define ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS /*lint --e(923)*/ (*(volatile Ifx_ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS*)0xF001F010u)

/** \brief  2004, Register 1 - Transmit Poll Demand Register */
#define ETH_TRANSMIT_POLL_DEMAND /*lint --e(923)*/ (*(volatile Ifx_ETH_TRANSMIT_POLL_DEMAND*)0xF001F004u)

/** \brief  1138, Register 78 - Transmit Octet Count for Good and Bad 1024 to
 * Maxsize Bytes Frames */
#define ETH_TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD*)0xF001E138u)

/** \brief  112C, Register 75 - Transmit Octet Count for Good and Bad 128 to 255
 * Bytes Frames */
#define ETH_TX_128TO255OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_128TO255OCTETS_FRAMES_GOOD_BAD*)0xF001E12Cu)

/** \brief  1130, Register 76 - Transmit Octet Count for Good and Bad 256 to 511
 * Bytes Frames */
#define ETH_TX_256TO511OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_256TO511OCTETS_FRAMES_GOOD_BAD*)0xF001E130u)

/** \brief  1134, Register 77 - Transmit Octet Count for Good and Bad 512 to
 * 1023 Bytes Frames */
#define ETH_TX_512TO1023OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_512TO1023OCTETS_FRAMES_GOOD_BAD*)0xF001E134u)

/** \brief  1124, Register 73 - Transmit Octet Count for Good and Bad 64 Byte
 * Frames */
#define ETH_TX_64OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_64OCTETS_FRAMES_GOOD_BAD*)0xF001E124u)

/** \brief  1128, Register 74 - Transmit Octet Count for Good and Bad 65 to 127
 * Bytes Frames */
#define ETH_TX_65TO127OCTETS_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_65TO127OCTETS_FRAMES_GOOD_BAD*)0xF001E128u)

/** \brief  111C, Register 71 - Transmit Frame Count for Good Broadcast Frames */
#define ETH_TX_BROADCAST_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_BROADCAST_FRAMES_GOOD*)0xF001E11Cu)

/** \brief  1144, Register 81 - Transmit Frame Count for Good and Bad Broadcast
 * Frames */
#define ETH_TX_BROADCAST_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_BAD*)0xF001E144u)

/** \brief  1160, Register 88 - Transmit Frame Count for Carrier Sense Error
 * Frames */
#define ETH_TX_CARRIER_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_CARRIER_ERROR_FRAMES*)0xF001E160u)

/** \brief  1154, Register 85 - Transmit Frame Count for Deferred Frames */
#define ETH_TX_DEFERRED_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_DEFERRED_FRAMES*)0xF001E154u)

/** \brief  115C, Register 87 - Transmit Frame Count for Excessive Collision
 * Error Frames */
#define ETH_TX_EXCESSIVE_COLLISION_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_EXCESSIVE_COLLISION_FRAMES*)0xF001E15Cu)

/** \brief  116C, Register 91 - Transmit Frame Count for Excessive Deferral
 * Error Frames */
#define ETH_TX_EXCESSIVE_DEFERRAL_ERROR /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_EXCESSIVE_DEFERRAL_ERROR*)0xF001E16Cu)

/** \brief  1168, Register 90 - Transmit Frame Count for Good Frames */
#define ETH_TX_FRAME_COUNT_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_FRAME_COUNT_GOOD*)0xF001E168u)

/** \brief  1118, Register 70 - Transmit Frame Count for Good and Bad Frames */
#define ETH_TX_FRAME_COUNT_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_FRAME_COUNT_GOOD_BAD*)0xF001E118u)

/** \brief  1158, Register 86 - Transmit Frame Count for Late Collision Error
 * Frames */
#define ETH_TX_LATE_COLLISION_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_LATE_COLLISION_FRAMES*)0xF001E158u)

/** \brief  1120, Register 72 - Transmit Frame Count for Good Multicast Frames */
#define ETH_TX_MULTICAST_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_MULTICAST_FRAMES_GOOD*)0xF001E120u)

/** \brief  1140, Register 80 - Transmit Frame Count for Good and Bad Multicast
 * Frames */
#define ETH_TX_MULTICAST_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_BAD*)0xF001E140u)

/** \brief  1150, Register 84 - Transmit Frame Count for Frames Transmitted
 * after Multiple Collision */
#define ETH_TX_MULTIPLE_COLLISION_GOOD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_MULTIPLE_COLLISION_GOOD_FRAMES*)0xF001E150u)

/** \brief  1164, Register 89 - Transmit Octet Count for Good Frames */
#define ETH_TX_OCTET_COUNT_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_OCTET_COUNT_GOOD*)0xF001E164u)

/** \brief  1114, Register 69 - Transmit Octet Count for Good and Bad Frames */
#define ETH_TX_OCTET_COUNT_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_OCTET_COUNT_GOOD_BAD*)0xF001E114u)

/** \brief  1178, Register 94 - Transmit Frame Count for Good Oversize Frames */
#define ETH_TX_OSIZE_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_OSIZE_FRAMES_GOOD*)0xF001E178u)

/** \brief  1170, Register 92 - Transmit Frame Count for Good PAUSE Frames */
#define ETH_TX_PAUSE_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_PAUSE_FRAMES*)0xF001E170u)

/** \brief  114C, Register 83 - Transmit Frame Count for Frames Transmitted
 * after Single Collision */
#define ETH_TX_SINGLE_COLLISION_GOOD_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_SINGLE_COLLISION_GOOD_FRAMES*)0xF001E14Cu)

/** \brief  1148, Register 82 - Transmit Frame Count for Underflow Error Frames */
#define ETH_TX_UNDERFLOW_ERROR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_UNDERFLOW_ERROR_FRAMES*)0xF001E148u)

/** \brief  113C, Register 79 - Transmit Frame Count for Good and Bad Unicast
 * Frames */
#define ETH_TX_UNICAST_FRAMES_GOOD_BAD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_UNICAST_FRAMES_GOOD_BAD*)0xF001E13Cu)

/** \brief  1174, Register 93 - Transmit Frame Count for Good VLAN Frames */
#define ETH_TX_VLAN_FRAMES_GOOD /*lint --e(923)*/ (*(volatile Ifx_ETH_TX_VLAN_FRAMES_GOOD*)0xF001E174u)

/** \brief  1020, Register 8 - Version Register */
#define ETH_VERSION /*lint --e(923)*/ (*(volatile Ifx_ETH_VERSION*)0xF001E020u)

/** \brief  101C, Register 7 - VLAN Tag Register */
#define ETH_VLAN_TAG /*lint --e(923)*/ (*(volatile Ifx_ETH_VLAN_TAG*)0xF001E01Cu)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXETH_REG_H */
