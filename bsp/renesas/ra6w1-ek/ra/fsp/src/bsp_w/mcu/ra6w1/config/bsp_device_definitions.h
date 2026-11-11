/**
 * \addtogroup BSP_CONFIG_DEFINITIONS
 * \{
 * \addtogroup BSP_CFG_DEF_DEVICE_MAP Device-Map Definitions
 *
 * \brief Device-Map Definitions. Macros for all the devices supported by SDK10.
 *
 *\{
 */

/**
 ****************************************************************************************
 *
 * @file bsp_device_definitions.h
 *
 * @brief Board Support Package. Device-Map definitions.
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
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

#ifndef BSP_DEVICE_DEFINITIONS_H_
#define BSP_DEVICE_DEFINITIONS_H_

/*
 * Available public macros characterizing each product supported by SDK10.
 * The variable dg_configDEVICE *MUST* take one of the following values
 * i.e. dg_configDEVICE=DA14680_01
 * The variable *MUST* be visible to both the compiler and the assembler.
 */
#define DA14680_01          (DA14680 | _DEVICE_MK_IC_VER(A, E))
#define DA14681_01          (DA14681 | _DEVICE_MK_IC_VER(A, E))
#define DA14682_00          (DA14682 | _DEVICE_MK_IC_VER(B, B))
#define DA14683_00          (DA14683 | _DEVICE_MK_IC_VER(B, B))

#define DA14691_00          (DA14691 | _DEVICE_MK_IC_VER(A, B))
#define DA14693_00          (DA14693 | _DEVICE_MK_IC_VER(A, B))
#define DA14695_00          (DA14695 | _DEVICE_MK_IC_VER(A, B))
#define DA14697_00          (DA14697 | _DEVICE_MK_IC_VER(A, B))
#define DA14699_00          (DA14699 | _DEVICE_MK_IC_VER(A, B))

#define DA14870_00          (DA14870 | _DEVICE_MK_IC_VER(A, A))
#define DA14871_00          (DA14871 | _DEVICE_MK_IC_VER(A, A))
#define DA14872_00          (DA14872 | _DEVICE_MK_IC_VER(A, A))
#define DA14873_00          (DA14873 | _DEVICE_MK_IC_VER(A, A))

#define DA16400_00          (DA16400 | _DEVICE_MK_IC_VER(A, A))
#define DA16400_10          (DA16400 | _DEVICE_MK_IC_VER(B, A))

#define D3095_10            (D3095 | _DEVICE_MK_IC_VER(B, A))

#ifndef dg_configDEVICE
 #define dg_configDEVICE    DA16400_00
#endif

#include "bsp_device_definitions_internal.h"

/*
 * Backward compatibility macros.
 * Useful for applications developed with older SDK versions.
 * DEVICE_DA146XX can be assigned the desired device.
 */

/* DA14680 family substitution (with the exception of uartboot loader) */
#define DEVICE_DA14680    DA14683_00

/* DA14690 family substitution */
#define DEVICE_DA1469x    DA14699_00

#if 0

/*
 * Test Section.
 * Helpful when changing the macro functionality.
 */
 #if (DEVICE_FPGA)
  #pragma message "DEVICE_FPGA true"
 #elif !(DEVICE_FPGA) && !DEVICE_FPGA
  #pragma message "DEVICE_FPGA false"
 #endif

 #if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X)) && !(DEVICE_FAMILY != DA1469X)
  #pragma message "Family DA1469X"

  #if !(DEVICE_FPGA)
   #if (DEVICE_VARIANT == DA14699) && !(DEVICE_VARIANT != DA14699)
    #pragma message "Variant DA14699"
   #elif (DEVICE_VARIANT == DA14697) && !(DEVICE_VARIANT != DA14697)
    #pragma message "Variant DA14697"
   #elif (DEVICE_VARIANT == DA14695) && !(DEVICE_VARIANT != DA14695)
    #pragma message "Variant DA14695"
   #elif (DEVICE_VARIANT == DA14693) && !(DEVICE_VARIANT != DA14693)
    #pragma message "Variant DA14693"
   #elif (DEVICE_VARIANT == DA14691) && !(DEVICE_VARIANT != DA14691)
    #pragma message "Variant DA14691"
   #else
    #error "690 VARIANT ERROR!"
   #endif
  #endif                               /* !FPGA */

 #elif (DEVICE_FAMILY == DA1468X) && !(DEVICE_FAMILY != DA1468X)
  #pragma message "Family DA1468X"

  #if !(DEVICE_FPGA)
   #if (DEVICE_VARIANT == DA14680) && !(DEVICE_VARIANT != DA14680)
    #pragma message "Variant DA14680"
   #elif (DEVICE_VARIANT == DA14681) && !(DEVICE_VARIANT != DA14681)
    #pragma message "Variant DA14681"
   #elif (DEVICE_VARIANT == DA14682) && !(DEVICE_VARIANT != DA14682)
    #pragma message "Variant DA14682"
   #elif (DEVICE_VARIANT == DA14683) && !(DEVICE_VARIANT != DA14683)
    #pragma message "Variant DA14683"
   #else
    #error "680 VARIANT ERROR!"
   #endif
  #endif                               /* !FPGA */

 #else
  #error "FAMILY ERROR!"
 #endif

 #if !(DEVICE_FPGA)
  #if (DEVICE_REVISION == DEVICE_REV_A) && !(DEVICE_REVISION != DEVICE_REV_A)
   #pragma message "Revision A"
  #elif (DEVICE_REVISION == DEVICE_REV_B) && !(DEVICE_REVISION != DEVICE_REV_B)
   #pragma message "Revision B"
  #else
   #error "REVISION"
  #endif
 #endif

 #if !(DEVICE_FPGA)
  #if (DEVICE_VERSION == DEVICE_VER_AE) && !(DEVICE_VERSION != DEVICE_VER_AE)
   #pragma message "Revision A Step E"
  #elif (DEVICE_VERSION == DEVICE_VER_AB) && !(DEVICE_VERSION != DEVICE_VER_AB)
   #pragma message "Revision A Step B"
  #elif (DEVICE_VERSION == DEVICE_VER_BB) && !(DEVICE_VERSION != DEVICE_VER_BB)
   #pragma message "Revision B Step B"
  #else
   #error "VERSION"
  #endif
 #endif

#endif                                 /* Test section */

#endif                                 /* BSP_DEVICE_DEFINITIONS_H_ */

/**
 \}
 \}
 */
