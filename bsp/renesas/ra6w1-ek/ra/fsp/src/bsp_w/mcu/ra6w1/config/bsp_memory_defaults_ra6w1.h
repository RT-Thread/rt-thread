/**
 * \addtogroup BSP_MEMORY_DEFAULTS
 * \{
 *
 * \addtogroup MEMORY_LAYOUT_SETTINGS Memory Layout Configuration Settings
 *
 * \brief Memory Layout Configuration Settings
 * \{
 *
 */

/**
 ****************************************************************************************
 *
 * @file bsp_memory_defaults_ra6w1.h
 *
 * @brief Board Support Package. Device-specific system configuration default values.
 *
 * Copyright (c) 2023 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef __BSP_MEMORY_DEFAULTS_RA6W1_H__
#define __BSP_MEMORY_DEFAULTS_RA6W1_H__

#if (DEVICE_FAMILY == DA1640X)

//
// RTM Allocation v6
//

/// Booter Configuration: Base 0x08600000, 256 Bytes
 #define dg_configBOOTER_RTM_ADDR         (0x28600000) // == 0x08600000
 #define dg_configBOOTER_RTM_SIZE         (0x100)

/// Scheduler Configuration: Base 0x08600100, 512 Bytes
 #define dg_configSCHEDULER_RTM_ADDR      ((dg_configBOOTER_RTM_ADDR) + (dg_configBOOTER_RTM_SIZE))
 #define dg_configSCHEDULER_RTM_SIZE      (0x200)

/// MAC DPM Configuration: Base 0x08600300, 768 Bytes
 #define dg_configMAC_RTM_ADDR            ((dg_configSCHEDULER_RTM_ADDR) + (dg_configSCHEDULER_RTM_SIZE))
 #define dg_configMAC_RTM_SIZE            (0x300)

/// APP SUPP DPM Configuration: Base 0x08600600, 1968 Bytes
 #define dg_configAPPSUPP_RTM_ADDR        ((dg_configMAC_RTM_ADDR) + (dg_configMAC_RTM_SIZE))
 #define dg_configAPPSUPP_RTM_SIZE        (0x7b0)

/// PHY PARAM: Base 0x08600DB0, 100 Bytes
 #define dg_configPHYPARAM_RTM_ADDR       ((dg_configAPPSUPP_RTM_ADDR) + (dg_configAPPSUPP_RTM_SIZE))
 #define dg_configPHYPARAM_RTM_SIZE       (0x64)

/// FADC CAL: Base 0x08600E14, 80 Bytes
 #define dg_configFADCAL_RTM_ADDR         ((dg_configPHYPARAM_RTM_ADDR) + (dg_configPHYPARAM_RTM_SIZE))
 #define dg_configFADCAL_RTM_SIZE         (0x50)

/// TCS: Base 0x08600E64, 256 Bytes
 #define dg_configTCS_RTM_ADDR            ((dg_configFADCAL_RTM_ADDR) + (dg_configFADCAL_RTM_SIZE))
 #define dg_configTCS_RTM_SIZE            (0x100)

/// DPMST: Base 0x08600F64, 6432 Bytes
 #define dg_configDPMST_RTM_ADDR          ((dg_configTCS_RTM_ADDR) + (dg_configTCS_RTM_SIZE))
 #define dg_configDPMST_RTM_SIZE          (0x1920)

/// TCPKAT: Base 0x08602884, 48 Bytes
 #define dg_configTCPKAT_RTM_ADDR         ((dg_configDPMST_RTM_ADDR) + (dg_configDPMST_RTM_SIZE))
 #define dg_configTCPKAT_RTM_SIZE         (0x30)

/// PAD: Base 0x086028B4, 316 Bytes
 #define dg_configPAD_RTM_ADDR            ((dg_configTCPKAT_RTM_ADDR) + (dg_configTCPKAT_RTM_SIZE))
 #define dg_configPAD_RTM_SIZE            (0x13C)

/// PTIM Image Header: Base 0x086029F0, 16 Bytes
 #define dg_configPTIMG_HDR_ADDR          ((dg_configPAD_RTM_ADDR) + (dg_configPAD_RTM_SIZE))
 #define dg_configPTIMG_HDR_SIZE          (0x10)

/// The address to load the PTIM image into RTM: Base 0x08602A00, 41984 Bytes
 #define dg_configPTIMG_ADDR              ((dg_configPTIMG_HDR_ADDR) + (dg_configPTIMG_HDR_SIZE))
 #define dg_configPTIMG_SIZE              (0xA400)

/// TCP: Base 0x0860CE00, 2256 Bytes (Max TCP Session count : 8)
 #define dg_configTCP_RTM_ADDR            ((dg_configPTIMG_ADDR) + (dg_configPTIMG_SIZE))
 #define dg_configTCP_RTM_SIZE            (0x8d0)

/// APP SUPP DPM EXT Configuration: Base 0x08600D6D0, 384 Bytes
 #define dg_configAPPSUPP_EXT_RTM_ADDR    ((dg_configTCP_RTM_ADDR) + (dg_configTCP_RTM_SIZE))
 #define dg_configAPPSUPP_EXT_RTM_SIZE    (0x180)

/// User RTM Header: Base 0x0860D850, 64 Bytes
 #define dg_configUSERHDR_RTM_ADDR        ((dg_configAPPSUPP_EXT_RTM_ADDR) + (dg_configAPPSUPP_EXT_RTM_SIZE))
 #define dg_configUSERHDR_RTM_SIZE        (0x40)

/// User RTM: Base 0x0860D890, 10096 Bytes
 #define dg_configUSER_RTM_ADDR           ((dg_configUSERHDR_RTM_ADDR) + (dg_configUSERHDR_RTM_SIZE))
 #define dg_configUSER_RTM_SIZE           (0x2770)

/// RTM End: Base 0x08610000, 0 Bytes
 #define dg_configEND_RTM_ADDR            ((dg_configUSER_RTM_ADDR) + (dg_configUSER_RTM_SIZE))
 #define dg_configEND_RTM_SIZE            (0x0)

 #if ((dg_configEND_RTM_ADDR) > (0x28610000))
  #error RTM Memory Overflow!!!
 #endif

 #if ((dg_configPTIMG_ADDR) % 512)
  #error PTIM address not aligned!!!
 #endif

#endif                                 /* DA1640X */

#endif                                 /* __BSP_MEMORY_DEFAULTS_RA6W1_H__ */

/**
 * \}
 * \}
 */
