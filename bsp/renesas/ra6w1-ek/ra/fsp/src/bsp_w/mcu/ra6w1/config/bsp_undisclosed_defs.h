/**
 ****************************************************************************************
 *
 * @file bsp_undisclosed_defs.h
 *
 * @brief
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

#ifndef BSP_UNDISCLOSED_DEFS_H_
#define BSP_UNDISCLOSED_DEFS_H_

#ifdef BSP_UNDISCLOSED_SANITY_CHECK

/* Add more defs, if needed, above dg_configUNDISCLOSED_LAST_DEF */

 #if defined(dg_configUNDISCLOSED_HAPTIC_DIAGN_CONFIG) ||      \
    defined(dg_configUNDISCLOSED_UNSUPPORTED_FLASH_DEVICES) || \
    defined(dg_configUNDISCLOSED_LAST_DEF) ||                  \
    defined(dg_configAUTOTEST_ENABLE)

  #error "dg_configUNDISCLOSED_XXX cannot be defined!!!"
 #endif

#endif                                 /* BSP_UNDISCLOSED_SANITY_CHECK */

/* Enable Haptic diagnostic signals. */
#ifndef dg_configUNDISCLOSED_HAPTIC_DIAGN_CONFIG
 #define dg_configUNDISCLOSED_HAPTIC_DIAGN_CONFIG          (0)
#endif

/* Enable qspi-flash driver modules not supported officially by the SDK. */
#ifndef dg_configUNDISCLOSED_UNSUPPORTED_FLASH_DEVICES
 #define dg_configUNDISCLOSED_UNSUPPORTED_FLASH_DEVICES    (0)
#endif

/* Enable AUTOTEST. */
#ifndef dg_configAUTOTEST_ENABLE
 #define dg_configAUTOTEST_ENABLE                          (0)
#endif

#endif                                 /* BSP_UNDISCLOSED_DEFS_H_ */
