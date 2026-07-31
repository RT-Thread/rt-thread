/**
 ****************************************************************************************
 *
 * @file sys_feature.h
 *
 * @brief Definition for System features
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

#ifndef __SYS_FEATURE_H__
#define __SYS_FEATURE_H__

#define COUNTRY_CODE_DEFAULT          "KR"
#define CHANNEL_AUTO                  0
#define CHANNEL_DEFAULT               CHANNEL_AUTO
#define REPLY_FAIL                    "FAIL"

/* WiFi Direct */
#define WIFI_DIR_LISTEN_CH_DFLT       CHANNEL_AUTO
#define WIFI_DIR_OPERATION_CH_DFLT    CHANNEL_AUTO
#define WIFI_DIR_GO_INTENT_DFLT       3

enum E_AUTH_MODE
{
    E_AUTH_MODE_NONE = 1,
    E_AUTH_MODE_WEP,
    E_AUTH_MODE_WPA,
    E_AUTH_MODE_RSN,
    E_AUTH_MODE_WPA_RSN,
#ifdef __SUPPORT_WPA3_SAE__
    E_AUTH_MODE_SAE,
    E_AUTH_MODE_RSN_SAE,
#endif                                 /* __SUPPORT_WPA3_SAE__ */
#ifdef __SUPPORT_WPA3_OWE__
    E_AUTH_MODE_OWE,
#endif                                 /* __SUPPORT_WPA3_OWE__ */
#ifdef __SUPPORT_WPA_ENTERPRISE__
    E_AUTH_MODE_ENT,
 #ifdef __SUPPORT_WPA3_ENTERPRISE__
    E_AUTH_MODE_WPA2_WPA3_ENT,
    E_AUTH_MODE_WPA3_ENT,
  #ifdef __SUPPORT_WPA3_ENTERPRISE_192B__
    E_AUTH_MODE_WPA3_ENT_192B,
  #endif                               // __SUPPORT_WPA3_ENTERPRISE_192B__
 #endif                                // __SUPPORT_WPA3_ENTERPRISE__
#endif                                 // __SUPPORT_WPA_ENTERPRISE__
    E_AUTH_MODE_MAX
};

#ifdef __SUPPORT_WPA_ENTERPRISE__
enum E_EAP_AUTH_MODE
{
    E_EAP_AUTH_MODE_NONE = 0,
    E_EAP_AUTH_MODE_PEAP_TTLS_FAST,
    E_EAP_AUTH_MODE_PEAP,
    E_EAP_AUTH_MODE_TTLS,
    E_EAP_AUTH_MODE_FAST,
    E_EAP_AUTH_MODE_TLS,
    E_EAP_AUTH_MODE_MAX
};

enum E_EAP_PHASE2_MODE
{
    E_EAP_PHASE2_MODE_NONE,
    E_EAP_PHASE2_MODE_MSCHAPV2_N_GTC,
    E_EAP_PHASE2_MODE_MSCHAPV2,
    E_EAP_PHASE2_MODE_GTC,
    E_EAP_PHASE2_MODE_TLS,
    E_EAP_PHASE2_MODE_MAX
};

#endif                                 // __SUPPORT_WPA_ENTERPRISE__

enum E_ENCRYP_MODE
{
    E_ENCRYP_MODE_TKIP = 1,
    E_ENCRYP_MODE_CCMP,
    E_ENCRYP_MODE_TKIP_CCMP
#ifdef __SUPPORT_WPA3_ENTERPRISE_192B__
    ,
    E_ENCRYP_MODE_GCMP_256
#endif                                 // __SUPPORT_WPA3_ENTERPRISE_192B__
};

enum E_WEP_KEY_TYPE
{
    WEP_KEY_TYPE_ASCII = 1,
    WEP_KEY_TYPE_HEXA
};

enum E_WEP_KEY_IDX
{
    E_WEP_KEY_IDX_1 = 1,
    E_WEP_KEY_IDX_2,
    E_WEP_KEY_IDX_3,
    E_WEP_KEY_IDX_4,
};

enum E_WEP_KEY_BIT
{
    WEP_KEY_64BIT = 1,
    WEP_KEY_128BIT
};

/* NET MODE */
enum E_NETMODE
{
    E_NETMODE_DYNAMIC_IP = 1,
    E_NETMODE_STATIC_IP
};

/* PSK_KEY_TYPE */
enum E_PSK_KEY_TYPE
{
    E_PSK_KEY_ASCII = 1,
    E_PSK_KEY_HEXA
};

/* SNTP Client */
enum E_SNTP_CLIENT
{
    E_SNTP_CLIENT_STOP = 1,
    E_SNTP_CLIENT_START
};

enum E_CFG_ENABLE
{
    E_DISABLE,
    E_ENABLE
};

/* For Console Password ************************************/

#define NVR_KEY_PASSWORD        "PASSWORD"
#define NVR_KEY_PASSWORD_SVC    "PASSWORD_SVC"

/*** !!! Notice !!! ******/
/* Customer can change default Password ... */
#define DEFAULT_PASSWORD        "rrq61000"
#define PW_TIMEOUT              12000  /* tick : 2 min */
#define DFLT_PASSWORD_SVC       1

/***********************************************************/

/* External global functions */
extern void reboot_func(unsigned int flag);

#if CFG_PMGR
extern int RM_PMGR_W_dpm_is_wakeup(void);

#endif                                 /* CFG_PMGR */

#endif                                 /* __SYS_FEATURE_H__ */

/* EOF */
