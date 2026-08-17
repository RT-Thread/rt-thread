/**
 ****************************************************************************************
 *
 * @file sdk_ver.h
 *
 * @brief Configuration for SDK Version
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

#ifndef    __SDK_VER_H__
#define    __SDK_VER_H__

// SDK Version number
#undef  SDK_VER_PRODUCT_LINE
#undef  SDK_VER_MODE
#undef  SDK_VER_TARGET
#if (TIN_SKU_BUILD_ID == TIN_SKU_WIFI6_B24_5_BLE || (defined (BSP_MCU_RRQ61051_208) || defined (BSP_MCU_RRQ61051_408)))
    #define SDK_VER_PRODUCT_LINE    8                // SDK Product line number
    #define SDK_VER_MODE            0                // SDK Mode number (Standalone:0 / Linux Driver:1)
    #define SDK_VER_TARGET          3                // SDK Target release
    #define SDK_VER_BRANCH          0               // SDK Branch number
    #define SDK_VER_R               6               // SDK R&D build number
#else
    #define SDK_VER_PRODUCT_LINE    8                // SDK Product line number
    #define SDK_VER_MODE            0                // SDK Mode number (Standalone:0 / Linux Driver:1)
    #define SDK_VER_TARGET          3                // SDK Target release
    #define SDK_VER_BRANCH          0               // SDK Branch number
    #define SDK_VER_R               6               // SDK R&D build number
#endif /* TIN_SKU_BUILD_ID == TIN_SKU_WIFI6_B24_5_BLE || (BSP_MCU_RRQ61051_208 || BSP_MCU_RRQ61051_408) */

#ifdef SIGMA_TEST_ENABLE
#define t_XSTR(i) #i
#define t_STR(i) t_XSTR(i)
#define SIGMA_SDK_VERSION  (t_STR(SDK_VER_PRODUCT_LINE) "." \
                            t_STR(SDK_VER_MODE) "." \
                            t_STR(SDK_VER_TARGET) "." \
                            t_STR(SDK_VER_BRANCH) "." \
                            t_STR(SDK_VER_R))
#endif //SIGMA_TEST_ENABLE

#endif    // __SDK_VER_H__

/* EOF */
