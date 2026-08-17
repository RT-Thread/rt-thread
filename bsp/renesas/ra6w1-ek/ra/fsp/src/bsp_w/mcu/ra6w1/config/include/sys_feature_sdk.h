/**
 ****************************************************************************************
 *
 * @file sys_feature_sdk.h
 *
 * @brief Define for common system features
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

#ifndef __SYS_COMMON_FEATURES_H__
#define __SYS_COMMON_FEATURES_H__

#if CFG_WIFI
// Wi-Fi configuration features
#include "ra6w1_wifi_features.h"
#endif /* CFG_WIFI */

// Console Prompt
#define PROMPT        "/" CHIPSET_NAME

///////////////////////////////////////////////////////////////////////
//
// Main features for customer SDK
//
///////////////////////////////////////////////////////////////////////

//
// System features ...................................................
//

// wifi re-connect stops when wifi conn fail by wrong key
#undef  __WIFI_CONN_RETRY_STOP_AT_WK_CONN_FAIL__

// Log message for Code run-time
#undef  __RUNTIME_CALCULATION__

// SIGMA Throughput Test for Wi-Fi Certification
#undef  __SUPPORT_SIGMA_TEST__


///////////////////////////////////////////////////////////////////////
//
// Sub features
//
///////////////////////////////////////////////////////////////////////

#if defined (__WIFI_CONN_RETRY_STOP_AT_WK_CONN_FAIL__)
    #undef  __DPM_ABN_SLEEP1_BY_WK_CONN_FAIL__       // optional: dpm abnormal sleep1 when wifi conn fail by wrong key
#endif // __WIFI_CONN_RETRY_STOP_AT_WK_CONN_FAIL__

// Wi-Fi Certification features
#if defined ( __SUPPORT_SIGMA_TEST__ )
    #define __SUPPORT_SIGMA_THROUGHPUT__
    #define __SUPPORT_SIGMA_UAPSD__
#endif // __SUPPORT_SIGMA_TEST__

///////////////////////////////////////////////////////////////////////
//
// Dependent features for customer SDK
//
///////////////////////////////////////////////////////////////////////

// Wi-Fi Certification features
#if defined ( __SUPPORT_SIGMA_TEST__ )
    #undef  __SUPPORT_WPS_BTN__

    #define __SUPPORT_UART2__
    #undef  __SUPPORT_ATCMD__

    #define __SUPPORT_IEEE80211W__            // IEEE 802.11W(PMF)
#endif // __SUPPORT_SIGMA_TEST__

#if defined ( __ENABLE_UMAC_CMD__ )
    #define __ENABLE_LMAC_TX_CMD__
#endif // __ENABLE_UMAC_CMD__

#if defined (__SUPPORT_WPS_BTN__) || defined (__SUPPORT_FACTORY_RESET_BTN__)
#include "sdk_defs.h"
#endif // __SUPPORT_WPS_BTN__ || __SUPPORT_FACTORY_RESET_BTN__

#endif    // __SYS_COMMON_FEATURES_H__

/* EOF */
