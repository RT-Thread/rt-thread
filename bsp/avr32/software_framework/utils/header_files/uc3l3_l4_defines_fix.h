/**
 * \file
 *
 * \brief Missing Toolchain Definition for UC3 L3 and UC3 L4 header files
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _UCL3_L4_DEFINES_FIX_
#define _UCL3_L4_DEFINES_FIX_

#include <parts.h>

#if (UC3L3_L4)

//  These defines are missing from or wrong in the toolchain header file ip_xxx.h or part.h
#ifndef AVR32_PM_CPU_MAX_FREQ
#define AVR32_PM_CPU_MAX_FREQ              50000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_CPU_MAX_FREQ

#ifndef AVR32_PM_HSB_MAX_FREQ
#define AVR32_PM_HSB_MAX_FREQ              50000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_HSB_MAX_FREQ

#ifndef AVR32_PM_PBA_MAX_FREQ
#define AVR32_PM_PBA_MAX_FREQ              50000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_PBA_MAX_FREQ

#ifndef AVR32_PM_PBB_MAX_FREQ
#define AVR32_PM_PBB_MAX_FREQ              50000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif  // AVR32_PM_PBB_MAX_FREQ

#ifndef AVR32_PM_MCSEL_SLOW
#define AVR32_PM_MCSEL_SLOW 0
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_MCSEL_SLOW

#ifndef AVR32_PM_MCSEL_OSC0
#define AVR32_PM_MCSEL_OSC0 1
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif  // AVR32_PM_MCSEL_OSC0

#ifndef AVR32_PM_MCSEL_DFLL0
#define AVR32_PM_MCSEL_DFLL0 2
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif  // AVR32_PM_MCSEL_DFLL0

#ifndef AVR32_PM_MCSEL_RC120M
#define AVR32_PM_MCSEL_RC120M 3
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif  // AVR32_PM_MCSEL_RC120M

#ifndef AVR32_PM_MCSEL_PLL0
#define AVR32_PM_MCSEL_PLL0 5
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_MCSEL_PLL0

#ifndef AVR32_CORE_COMPARE_IRQ
#define AVR32_CORE_COMPARE_IRQ 0
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_CORE_COMPARE_IRQ

#endif // end UC3L3_L4

#endif // _UCL3_L4_DEFINES_FIX
