/**
 * \file
 *
 * \brief Missing Toolchain Definition for UC3 D header files
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 * 
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _UC3D_DEFINES_FIX_
#define _UC3D_DEFINES_FIX_

#include <parts.h>

#if (UC3D)

//  These defines are missing from or wrong in the toolchain header file ip_xxx.h or part.h
#ifndef AVR32_SCIF_GC_NO_DIV_CLOCK
#define AVR32_SCIF_GC_NO_DIV_CLOCK           0
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GC_NO_DIV_CLOCK

#ifndef AVR32_SCIF_GCLK_ADCIFD
#define AVR32_SCIF_GCLK_ADCIFD               8
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_ADCIFD

#ifndef AVR32_SCIF_GCLK_AST
#define AVR32_SCIF_GCLK_AST                  6
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_AST

#ifndef AVR32_SCIF_GCLK_GLOC
#define AVR32_SCIF_GCLK_GLOC                 0
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_GLOC

#ifndef AVR32_SCIF_GCLK_IISC
#define AVR32_SCIF_GCLK_IISC                 5
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_IISC

#ifndef AVR32_SCIF_GCLK_PWMA
#define AVR32_SCIF_GCLK_PWMA                 4
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_PWMA

#ifndef AVR32_SCIF_GCLK_USBC
#define AVR32_SCIF_GCLK_USBC                 3
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_USBC

#ifndef AVR32_PM_CPU_MAX_FREQ
#define AVR32_PM_CPU_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_CPU_MAX_FREQ

#ifndef AVR32_PM_HSB_MAX_FREQ
#define AVR32_PM_HSB_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_HSB_MAX_FREQ

#ifndef AVR32_PM_PBA_MAX_FREQ
#define AVR32_PM_PBA_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_PBA_MAX_FREQ

#ifndef AVR32_PM_PBB_MAX_FREQ
#define AVR32_PM_PBB_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif  // AVR32_PM_PBB_MAX_FREQ

#endif // end UC3D

#endif  // _UC3D_DEFINES_FIX
