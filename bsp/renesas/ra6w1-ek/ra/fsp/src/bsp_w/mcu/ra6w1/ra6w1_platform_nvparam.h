/**
 * \addtogroup MID_SYS_ADAPTERS
 * \{
 * \addtogroup ADAPTER_CONFIGURATION
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file ra6w1_platform_nvparam.h
 *
 * @brief Configuration of non-volatile parameters on platform
 *
 * Copyright (c) 2024 Renesas Electronics. All rights reserved.
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

#ifndef PLATFORM_NVPARAM_H_

// Do NOT modify this Definition Directive !!
#define PLATFORM_NVPARAM_H_

#undef CONFIG_UNUSED

#include "ad_nvparam_defs.h"
#include "common_def.h"

#if (dg_configNVPARAM_ADAPTERv2 == 1)

/*
 * Parameters length need to include 2 extra bytes for parameter header.
 * Variable-length parameters length need to include 4 extra bytes for parameter header and length.
 */
 #define NVPARAM_HEAD_SIZE    2
 #define STR_END              1
 #define PARAM_STR_EXTRA      (NVPARAM_HEAD_SIZE + STR_END)
 #define PARAM_IPADDR_LEN     (16 + PARAM_STR_EXTRA)
 #define PARAM_IP6ADDR_LEN    (40 + PARAM_STR_EXTRA)
 #define UINT32_LEN           4
 #define INT32_LEN            4
 #define UINT16_LEN           2
 #define UINT8_LEN            1

 #define STR_INT32_LEN        (11 + PARAM_STR_EXTRA)
 #define STR_INT16_LEN        (7 + PARAM_STR_EXTRA)
 #define STR_INT8_LEN         (4 + PARAM_STR_EXTRA)

 #define NPRO_0               "N0_"
 #define NPRO_1               "N1_"

/// List of NVEE lengths

// bootcfg
//= =============================================================================
 #define NVEE_LEN_BOOT_CHIP              9 + PARAM_STR_EXTRA
 #define NVEE_LEN_BOOT_PLATFORM          13 + PARAM_STR_EXTRA
 #define NVEE_LEN_BOOT_CLK_CPU           UINT32_LEN
 #define NVEE_LEN_BOOT_CLK_BUS           UINT32_LEN
 #define NVEE_LEN_BOOT_BAUD              UINT32_LEN
 #define NVEE_LEN_BOOT_BIT               UINT32_LEN
 #define NVEE_LEN_BOOT_STOP              UINT8_LEN

// devcfg
//= =============================================================================

 #define NVEE_LEN_WLANMAC                (12 + PARAM_STR_EXTRA)
 #define NVEE_LEN_ATCMD_UART_BAUDRATE    (UINT32_LEN)
 #define NVEE_LEN_ATCMD_UART_BITS        (UINT32_LEN)
 #define NVEE_LEN_ATCMD_UART_PARITY      (UINT32_LEN)
 #define NVEE_LEN_ATCMD_UART_STOPBIT     (UINT32_LEN)
 #define NVEE_LEN_ATCMD_UART_FLOWCTRL    (UINT32_LEN)

// wificfg
//= =============================================================================

// Supplicant Global Config
 #define NVEE_LEN_uuid                                (40 + PARAM_STR_EXTRA)
 #define NVEE_LEN_auto_uuid                           STR_INT32_LEN

/**
 * device_name - Device Name (WPS)
 * User-friendly description of device; up to 32 octets encoded in
 * UTF-8
 */
 #define NVEE_LEN_device_name                         (32 + PARAM_STR_EXTRA)

/**
 * manufacturer - Manufacturer (WPS)
 * The manufacturer of the device (up to 64 ASCII characters)
 */
 #define NVEE_LEN_manufacturer                        64

/**
 * model_name - Model Name (WPS)
 * Model of the device (up to 32 ASCII characters)
 */
 #define NVEE_LEN_model_name                          (32 + PARAM_STR_EXTRA)

/**
 * model_number - Model Number (WPS)
 * Additional device description (up to 32 ASCII characters)
 */
 #define NVEE_LEN_model_number                        (32 + PARAM_STR_EXTRA)

/**
 * serial_number - Serial Number (WPS)
 * Serial number of the device (up to 32 characters)
 */
 #define NVEE_LEN_serial_number                       (32 + PARAM_STR_EXTRA)

/**
 * device_type - Primary Device Type (WPS)
 */
 #define NVEE_LEN_device_type                         (21 + PARAM_STR_EXTRA) /* WPS_DEV_TYPE_BUFSIZE */

/**
 * config_methods - Config Methods
 *
 * This is a space-separated list of supported WPS configuration
 * methods. For example
 #define "label virtual_display virtual_push_button
 * keypad".
 * Available methods: usba ethernet label display ext_nfc_token
 * int_nfc_token nfc_interface push_button keypad
 * virtual_display physical_display
 * virtual_push_button physical_push_button.
 */
 #define NVEE_LEN_config_methods                      (256 + PARAM_STR_EXTRA)
 #define NVEE_LEN_p2p_ssid_postfix                    (23 + PARAM_STR_EXTRA) // SSID_MAX_LEN-(DIRECT-xx) = 32-9 = 23
 #define NVEE_LEN_p2p_group_idle                      STR_INT32_LEN
 #define NVEE_LEN_p2p_listen_channel                  STR_INT32_LEN
 #define NVEE_LEN_p2p_oper_channel                    STR_INT32_LEN
 #define NVEE_LEN_p2p_find_timeout                    STR_INT32_LEN
 #define NVEE_LEN_p2p_go_intent                       STR_INT32_LEN
 #define NVEE_LEN_wmm_enabled                         STR_INT32_LEN
 #define NVEE_LEN_wmm_ps_enabled                      STR_INT32_LEN
 #define NVEE_LEN_ap_max_inactivity                   STR_INT32_LEN
 #define NVEE_LEN_ap_send_ka                          STR_INT32_LEN
 #define NVEE_LEN_bss_max_count                       STR_INT32_LEN
 #define NVEE_LEN_bss_expiration_age                  STR_INT32_LEN
 #define NVEE_LEN_bss_expiration_scan_count           STR_INT32_LEN
 #define NVEE_LEN_filter_ssids                        STR_INT32_LEN
 #define NVEE_LEN_filter_rssi                         STR_INT32_LEN
 #define NVEE_LEN_max_num_sta                         STR_INT32_LEN
 #define NVEE_LEN_ap_isolate                          STR_INT32_LEN
 #define NVEE_LEN_disassoc_low_ack                    STR_INT32_LEN
 #define NVEE_LEN_hs20                                STR_INT32_LEN
 #define NVEE_LEN_interworking                        STR_INT32_LEN
 #define NVEE_LEN_hessid                              (6 + PARAM_STR_EXTRA) // ETH_ALEN   6       /* Octets in one ethernet addr   */
 #define NVEE_LEN_access_network_type                 STR_INT32_LEN
 #define NVEE_LEN_go_interworking                     STR_INT32_LEN
 #define NVEE_LEN_go_access_network_type              STR_INT32_LEN
 #define NVEE_LEN_go_internet                         STR_INT32_LEN
 #define NVEE_LEN_go_venue_group                      STR_INT32_LEN
 #define NVEE_LEN_go_venue_type                       STR_INT32_LEN
 #define NVEE_LEN_pbc_in_m1                           STR_INT32_LEN
 #define NVEE_LEN_wps_nfc_dev_pw_id                   STR_INT32_LEN
 #define NVEE_LEN_ext_password_backend                (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_p2p_go_max_inactivity               STR_INT32_LEN
 #define NVEE_LEN_auto_interworking                   STR_INT32_LEN
 #define NVEE_LEN_okc                                 STR_INT32_LEN
 #define NVEE_LEN_pmf                                 STR_INT32_LEN
 #define NVEE_LEN_dtim_period                         STR_INT32_LEN
 #define NVEE_LEN_beacon_int                          STR_INT32_LEN
 #define NVEE_LEN_sae_groups                          (18 + PARAM_STR_EXTRA) // 3*MAX_SAE_GROUPS
 #define NVEE_LEN_ignore_old_scan_res                 STR_INT32_LEN
 #define NVEE_LEN_scan_cur_freq                       STR_INT32_LEN
 #define NVEE_LEN_sched_scan_interval                 STR_INT32_LEN
 #define NVEE_LEN_sched_scan_start_delay              STR_INT32_LEN
 #define NVEE_LEN_external_sim                        STR_INT32_LEN
 #define NVEE_LEN_tdls_external_control               STR_INT32_LEN

/**
 * wowlan_triggers - Wake-on-WLAN triggers
 *
 * If set, these wowlan triggers will be configured.
 */
 #define NVEE_LEN_wowlan_triggers                     (32 + PARAM_STR_EXTRA)

/**
 * bgscan - Background scan and roaming parameters or %NULL if none
 *
 * This is an optional set of parameters for background scanning and
 * roaming within a network (ESS). For more detailed information see
 * ssid block documentation.
 *
 * The variable defines default bgscan behavior for all BSS station
 * networks except for those which have their own bgscan configuration.
 */
 #define NVEE_LEN_bgscan                              (32 + PARAM_STR_EXTRA)

/**
 * autoscan - Automatic scan parameters or %NULL if none
 *
 * This is an optional set of parameters for automatic scanning
 * within an interface in following format:
 * <autoscan module name>:<module parameters>
 */
 #define NVEE_LEN_autoscan                            (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_p2p_search_delay                    STR_INT32_LEN
 #define NVEE_LEN_mac_addr                            (6 + PARAM_STR_EXTRA)
 #define NVEE_LEN_rand_addr_lifetime                  STR_INT32_LEN
 #define NVEE_LEN_preassoc_mac_addr                   STR_INT32_LEN
 #define NVEE_LEN_key_mgmt_offload                    STR_INT32_LEN
 #define NVEE_LEN_user_mpm                            STR_INT32_LEN
 #define NVEE_LEN_max_peer_links                      STR_INT32_LEN
 #define NVEE_LEN_cert_in_cb                          STR_INT32_LEN
 #define NVEE_LEN_mesh_max_inactivity                 STR_INT32_LEN
 #define NVEE_LEN_dot11RSNASAERetransPeriod           STR_INT32_LEN
 #define NVEE_LEN_reassoc_same_bss_optim              STR_INT32_LEN
 #define NVEE_LEN_wps_priority                        STR_INT32_LEN
 #define NVEE_LEN_wpa_rsc_relaxation                  STR_INT32_LEN

/**
 * sched_scan_plans - Scan plans for scheduled scan
 *
 * Each scan plan specifies the interval between scans and the number of
 * iterations. The last scan plan only specifies the scan interval and
 * will be run infinitely.
 *
 * format: <interval:iterations> <interval2:iterations2> ... <interval>
 */
 #define NVEE_LEN_sched_scan_plans                    (32 + PARAM_STR_EXTRA)

/**
 * non_pref_chan - Non-preferred channels list
 #define separated by spaces.
 *
 * format: op_class:chan:preference:reason<:detail>
 * Detail is optional.
 */
 #define NVEE_LEN_non_pref_chan                       (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_mbo_cell_capa                       STR_INT32_LEN
 #define NVEE_LEN_disassoc_imminent_rssi_threshold    STR_INT32_LEN
 #define NVEE_LEN_oce                                 STR_INT32_LEN
 #define NVEE_LEN_gas_address3                        STR_INT32_LEN
 #define NVEE_LEN_ftm_responder                       STR_INT32_LEN
 #define NVEE_LEN_ftm_initiator                       STR_INT32_LEN

/**
 * osu_dir - OSU provider information directory
 *
 * If set
 #define allow FETCH_OSU control interface command to be used to fetch
 * OSU provider information into all APs and store the results in this
 * directory.
 */
 #define NVEE_LEN_osu_dir                             STR_INT32_LEN
 #define NVEE_LEN_fst_group_id                        (16 + PARAM_STR_EXTRA) // FST_MAX_GROUP_ID_LEN (IFNAMSIZ)
 #define NVEE_LEN_fst_priority                        STR_INT32_LEN
 #define NVEE_LEN_fst_llt                             STR_INT32_LEN
 #define NVEE_LEN_gas_rand_addr_lifetime              STR_INT32_LEN
 #define NVEE_LEN_gas_rand_mac_addr                   STR_INT32_LEN
 #define NVEE_LEN_dpp_config_processing               STR_INT32_LEN
 #define NVEE_LEN_STA_roam                            STR_INT32_LEN
 #define NVEE_LEN_STA_roam_thold                      STR_INT32_LEN
 #define NVEE_LEN_greenfield                          STR_INT32_LEN
 #define NVEE_LEN_ht_protection                       STR_INT32_LEN
 #define NVEE_LEN_rts_threshold                       STR_INT32_LEN
 #define NVEE_LEN_acl_cmd                             STR_INT32_LEN
 #define NVEE_LEN_country_code                        (3 + PARAM_STR_EXTRA)
 #define NVEE_LEN_tls_ver                             STR_INT32_LEN
 #define NVEE_LEN_rootca_chk                          STR_INT32_LEN
 #define NVEE_LEN_peap_ver                            STR_INT32_LEN
 #define NVEE_LEN_supp_log_mask                       STR_INT32_LEN
 #define NVEE_LEN_supp_wpa_log_mask                   STR_INT32_LEN
 #define NVEE_LEN_setband                             STR_INT32_LEN
 #define NVEE_LEN_p2p_ps                              STR_INT32_LEN
 #define NVEE_LEN_TEMP_PIN                            STR_INT32_LEN
 #define NVEE_LEN_fast_reauth                         STR_INT32_LEN
 #define NVEE_LEN_fast_pac                            (512 + PARAM_STR_EXTRA)
 #define NVEE_LEN_fast_pac_len                        STR_INT32_LEN

// =============================================================================
// Supplicant Network Profile 0
// =============================================================================
 #define NVEE_LEN_N0_profile                          STR_INT32_LEN
 #define NVEE_LEN_N0_ssid                             (32 * 2 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N0_scan_ssid                        STR_INT32_LEN
 #define NVEE_LEN_N0_bssid                            (17 + PARAM_STR_EXTRA) // MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
 #define NVEE_LEN_N0_bssid_hint                       STR_INT32_LEN
 #define NVEE_LEN_N0_bssid_blacklist                  STR_INT32_LEN
 #define NVEE_LEN_N0_bssid_whitelist                  STR_INT32_LEN
 #define NVEE_LEN_N0_psk                              (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N0_psk_raw                          (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N0_mem_only_psk                     STR_INT32_LEN

/**
 * sae_password - SAE password
 *
 * This parameter can be used to set a password for SAE. By default, the
 * passphrase value is used if this separate parameter is not used, but
 * passphrase follows the WPA-PSK constraints (8..63 characters) even
 * though SAE passwords do not have such constraints.
 */
 #define NVEE_LEN_N0_sae_password                     (128 + 2 + PARAM_STR_EXTRA)

/**
 * sae_password_id - SAE password identifier
 *
 * This parameter can be used to identify a specific SAE password. If
 * not included, the default SAE password is used instead.
 */
 #define NVEE_LEN_N0_sae_password_id                  (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N0_proto                            (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N0_key_mgmt                         (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N0_bg_scan_period                   STR_INT32_LEN
 #define NVEE_LEN_N0_pairwise                         (50 + PARAM_STR_EXTRA) // wpa_config_write_cipher
// wpa_config_write_cipher
 #define NVEE_LEN_N0_group                            (50 + PARAM_STR_EXTRA) // wpa_config_write_cipher
 #define NVEE_LEN_N0_group_mgmt                       (50 + PARAM_STR_EXTRA) // wpa_config_write_cipher
// wpa_config_write_cipher
 #define NVEE_LEN_N0_auth_alg                         (30 + PARAM_STR_EXTRA)

/**
 * bgscan - Background scan and roaming parameters or %NULL if none
 *
 * This is an optional set of parameters for background scanning and
 * roaming within a network (ESS) in following format:
 * <bgscan module name>:<module parameters>
 */
 #define NVEE_LEN_N0_bgscan                           (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N0_autoscan                         (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)

/**
 * scan_freq - Array of frequencies to scan or %NULL for all
 *
 * This is an optional zero-terminated array of frequencies in
 * megahertz (MHz) to include in scan requests when searching for this
 * network. This can be used to speed up scanning when the network is
 * known to not use all possible channels.
 */
 #define NVEE_LEN_N0_scan_freq                        (640 + PARAM_STR_EXTRA) // Unknown Size (expected size: channel count * 5, 2Ghz + 5Ghz) // 56 EA : 56(CH)*10(int)+56(space)+24(Margin)
 #define NVEE_LEN_N0_freq_list                        (640 + PARAM_STR_EXTRA) // Unknown Size (expected size: channel count * 5, 2Ghz + 5Ghz) // 56 EA : 56(CH)*10(int)+56(space)+24(Margin)
 #define NVEE_LEN_N0_eap                              (100 + PARAM_STR_EXTRA) // wpa_config_write_eap
 #define NVEE_LEN_N0_identity                         (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N0_anonymous_identity               (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)

 #define NVEE_LEN_N0_imsi_identity                    (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N0_password                         (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N0_phase1                           (20 + PARAM_STR_EXTRA)  // Unknown Size (expected size: aboud: 20)
 #define NVEE_LEN_N0_phase2                           (20 + PARAM_STR_EXTRA)  // Unknown Size (expected size: aboud: 20)
 #define NVEE_LEN_N0_eapol_flags                      STR_INT32_LEN
 #define NVEE_LEN_N0_wep_key0                         (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N0_wep_key1                         (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N0_wep_key2                         (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N0_wep_key3                         (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N0_priority                         STR_INT32_LEN
 #define NVEE_LEN_N0_eap_workaround                   STR_INT32_LEN
 #define NVEE_LEN_N0_pac_file                         (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N0_fragment_size                    STR_INT32_LEN
 #define NVEE_LEN_N0_ocsp                             STR_INT32_LEN
 #define NVEE_LEN_N0_sim_num                          STR_INT32_LEN
 #define NVEE_LEN_N0_mode                             STR_INT32_LEN
 #define NVEE_LEN_N0_no_auto_peer                     STR_INT32_LEN
 #define NVEE_LEN_N0_frequency                        STR_INT32_LEN
 #define NVEE_LEN_N0_fixed_freq                       STR_INT32_LEN
 #define NVEE_LEN_N0_acs                              STR_INT32_LEN
 #define NVEE_LEN_N0_proactive_key_caching            STR_INT32_LEN
 #define NVEE_LEN_N0_disabled                         STR_INT32_LEN
 #define NVEE_LEN_N0_pbss                             STR_INT32_LEN
 #define NVEE_LEN_N0_wps_disabled                     STR_INT32_LEN
 #define NVEE_LEN_N0_fils_dh_group                    STR_INT32_LEN
 #define NVEE_LEN_N0_ieee80211w                       STR_INT32_LEN
 #define NVEE_LEN_N0_id_str                           (256 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N0_ignore_broadcast_ssid            STR_INT32_LEN
 #define NVEE_LEN_N0_dtim_period                      STR_INT32_LEN
 #define NVEE_LEN_N0_beacon_int                       STR_INT32_LEN
 #define NVEE_LEN_N0_isolate                          STR_INT32_LEN
 #define NVEE_LEN_N0_ap_max_inactivity                STR_INT32_LEN
 #define NVEE_LEN_N0_ap_power                         (8 + PARAM_STR_EXTRA)  // auto, ...
 #define NVEE_LEN_N0_update_identifier                STR_INT32_LEN
 #define NVEE_LEN_N0_roaming_consortium_selection     (15 + PARAM_STR_EXTRA) // MAX_ROAMING_CONS_OI_LEN

/**
 * mac_addr - MAC address policy
 *
 * 0 = use permanent MAC address
 * 1 = use random MAC address for each ESS connection
 * 2 = like 1, but maintain OUI (with local admin bit set)
 *
 * Internally, special value -1 is used to indicate that the parameter
 * was not specified in the configuration (i.e., default behavior is
 * followed).
 */
 #define NVEE_LEN_N0_mac_addr                         STR_INT32_LEN
 #define NVEE_LEN_N0_mesh_basic_rates                 (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N0_dot11MeshMaxRetries              STR_INT32_LEN
 #define NVEE_LEN_N0_dot11MeshRetryTimeout            STR_INT32_LEN
 #define NVEE_LEN_N0_dot11MeshConfirmTimeout          STR_INT32_LEN
 #define NVEE_LEN_N0_dot11MeshHoldingTimeout          STR_INT32_LEN
 #define NVEE_LEN_N0_mesh_rssi_threshold              STR_INT32_LEN          // -255 ~1
 #define NVEE_LEN_N0_wpa_ptk_rekey                    STR_INT32_LEN
 #define NVEE_LEN_N0_wpa_deny_ptk0_rekey              STR_INT32_LEN
 #define NVEE_LEN_N0_group_rekey                      STR_INT32_LEN
 #define NVEE_LEN_N0_dpp_connector                    (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N0_dpp_netaccesskey                 (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N0_dpp_netaccesskey_expiry          STR_INT32_LEN
 #define NVEE_LEN_N0_dpp_csign                        (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N0_owe_group                        STR_INT32_LEN
 #define NVEE_LEN_N0_owe_only                         STR_INT32_LEN
 #define NVEE_LEN_N0_owe_ptk_workaround               STR_INT32_LEN
 #define NVEE_LEN_N0_multi_ap_backhaul_sta            STR_INT32_LEN
 #define NVEE_LEN_N0_ft_eap_pmksa_caching             STR_INT32_LEN
 #define NVEE_LEN_N0_beacon_prot                      STR_INT32_LEN
 #define NVEE_LEN_N0_transition_disable               STR_INT32_LEN
 #define NVEE_LEN_N0_sae_pk                           STR_INT32_LEN
 #define NVEE_LEN_N0_wifi_mode                        STR_INT32_LEN

/**
 * mixed_cell - Whether mixed cells are allowed
 *
 * This option can be used to configure whether so called mixed cells,
 * i.e., networks that use both plaintext and encryption in the same
 * SSID, are allowed. This is disabled (0) by default. Enable by
 * setting this to 1.
 */
 #define NVEE_LEN_N0_mixed_cell                       STR_INT32_LEN
 #define NVEE_LEN_N0_ht                               STR_INT32_LEN
 #define NVEE_LEN_N0_ht40                             STR_INT32_LEN
 #define NVEE_LEN_N0_disable_ht                       STR_INT32_LEN
 #define NVEE_LEN_N0_disable_ht40                     STR_INT32_LEN
 #define NVEE_LEN_N0_disable_sgi                      STR_INT32_LEN
 #define NVEE_LEN_N0_disable_ldpc                     STR_INT32_LEN
 #define NVEE_LEN_N0_ht40_intolerant                  STR_INT32_LEN
 #define NVEE_LEN_N0_tx_stbc                          STR_INT32_LEN
 #define NVEE_LEN_N0_rx_stbc                          STR_INT32_LEN
 #define NVEE_LEN_N0_disable_max_amsdu                STR_INT32_LEN
 #define NVEE_LEN_N0_ampdu_factor                     STR_INT32_LEN
 #define NVEE_LEN_N0_ampdu_density                    STR_INT32_LEN
 #define NVEE_LEN_N0_ht_mcs                           (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N0_max_oper_chwidth                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_center_freq1                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_center_freq2                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht                              STR_INT32_LEN
 #define NVEE_LEN_N0_disable_vht                      STR_INT32_LEN
 #define NVEE_LEN_N0_vht_capa                         STR_INT32_LEN
 #define NVEE_LEN_N0_vht_capa_mask                    STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_1                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_2                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_3                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_4                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_5                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_6                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_7                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_rx_mcs_nss_8                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_1                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_2                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_3                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_4                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_5                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_6                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_7                 STR_INT32_LEN
 #define NVEE_LEN_N0_vht_tx_mcs_nss_8                 STR_INT32_LEN
 #define NVEE_LEN_N0_ca_cert                          STR_INT32_LEN
 #define NVEE_LEN_N0_ca_path                          STR_INT32_LEN
 #define NVEE_LEN_N0_client_cert                      STR_INT32_LEN
 #define NVEE_LEN_N0_private_key                      STR_INT32_LEN
 #define NVEE_LEN_N0_private_key_passwd               STR_INT32_LEN
 #define NVEE_LEN_N0_dh_file                          STR_INT32_LEN
 #define NVEE_LEN_N0_subject_match                    STR_INT32_LEN
 #define NVEE_LEN_N0_altsubject_match                 STR_INT32_LEN
 #define NVEE_LEN_N0_domain_suffix_match              STR_INT32_LEN
 #define NVEE_LEN_N0_domain_match                     STR_INT32_LEN
 #define NVEE_LEN_N0_ca_cert2                         STR_INT32_LEN
 #define NVEE_LEN_N0_ca_path2                         STR_INT32_LEN
 #define NVEE_LEN_N0_client_cert2                     STR_INT32_LEN
 #define NVEE_LEN_N0_private_key2                     STR_INT32_LEN
 #define NVEE_LEN_N0_private_key2_passwd              STR_INT32_LEN
 #define NVEE_LEN_N0_dh_file2                         STR_INT32_LEN
 #define NVEE_LEN_N0_subject_match2                   STR_INT32_LEN
 #define NVEE_LEN_N0_altsubject_match2                STR_INT32_LEN
 #define NVEE_LEN_N0_domain_suffix_match2             STR_INT32_LEN
 #define NVEE_LEN_N0_domain_match2                    STR_INT32_LEN
 #define NVEE_LEN_N0_pcsc                             (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N0_pin                              STR_INT32_LEN
 #define NVEE_LEN_N0_engine_id                        STR_INT32_LEN
 #define NVEE_LEN_N0_key_id                           STR_INT32_LEN
 #define NVEE_LEN_N0_cert_id                          STR_INT32_LEN
 #define NVEE_LEN_N0_ca_cert_id                       STR_INT32_LEN
 #define NVEE_LEN_N0_key2_id                          STR_INT32_LEN
 #define NVEE_LEN_N0_pin2                             STR_INT32_LEN
 #define NVEE_LEN_N0_engine2_id                       STR_INT32_LEN
 #define NVEE_LEN_N0_cert2_id                         STR_INT32_LEN
 #define NVEE_LEN_N0_ca_cert2_id                      STR_INT32_LEN
 #define NVEE_LEN_N0_engine                           STR_INT32_LEN
 #define NVEE_LEN_N0_engine2                          STR_INT32_LEN
 #define NVEE_LEN_N0_openssl_ciphers                  STR_INT32_LEN
 #define NVEE_LEN_N0_erp                              STR_INT32_LEN
 #define NVEE_LEN_N0_erp                              STR_INT32_LEN
 #define NVEE_LEN_N0_FST_CONNECT                      STR_INT32_LEN
 #define NVEE_LEN_N0_ASSOC_CH                         STR_INT32_LEN
 #if 0                                 // def CONFIG_MACSEC
  #define NVEE_LEN_N0_macsec_policy                   STR_INT32_LEN
  #define NVEE_LEN_N0_macsec_integ_only               STR_INT32_LEN
  #define NVEE_LEN_N0_macsec_port                     STR_INT32_LEN
  #define NVEE_LEN_N0_mka_priority                    STR_INT32_LEN
 #endif                                /* CONFIG_MACSEC */

// =============================================================================

// =============================================================================
// Supplicant Network Profile 1
// =============================================================================
 #define NVEE_LEN_N1_profile                                   STR_INT32_LEN
 #define NVEE_LEN_N1_ssid                                      (32 * 2 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N1_scan_ssid                                 STR_INT32_LEN
 #define NVEE_LEN_N1_bssid                                     (17 + PARAM_STR_EXTRA) // MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
 #define NVEE_LEN_N1_bssid_hint                                STR_INT32_LEN
 #define NVEE_LEN_N1_bssid_blacklist                           STR_INT32_LEN
 #define NVEE_LEN_N1_bssid_whitelist                           STR_INT32_LEN
 #define NVEE_LEN_N1_psk                                       (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N1_mem_only_psk                              STR_INT32_LEN

/**
 * sae_password - SAE password
 *
 * This parameter can be used to set a password for SAE. By default, the
 * passphrase value is used if this separate parameter is not used, but
 * passphrase follows the WPA-PSK constraints (8..63 characters) even
 * though SAE passwords do not have such constraints.
 */
 #define NVEE_LEN_N1_sae_password                              (128 + 2 + PARAM_STR_EXTRA)

/**
 * sae_password_id - SAE password identifier
 *
 * This parameter can be used to identify a specific SAE password. If
 * not included, the default SAE password is used instead.
 */
 #define NVEE_LEN_N1_sae_password_id                           (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N1_proto                                     (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N1_key_mgmt                                  (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N1_bg_scan_period                            STR_INT32_LEN
 #define NVEE_LEN_N1_pairwise                                  (50 + PARAM_STR_EXTRA)  // wpa_config_write_cipher
// wpa_config_write_cipher
 #define NVEE_LEN_N1_group                                     (50 + PARAM_STR_EXTRA)  // wpa_config_write_cipher
// wpa_config_write_cipher
 #define NVEE_LEN_N1_group_mgmt                                (50 + PARAM_STR_EXTRA)  // wpa_config_write_cipher
 #define NVEE_LEN_N1_auth_alg                                  (30 + PARAM_STR_EXTRA)

/**
 * bgscan - Background scan and roaming parameters or %NULL if none
 *
 * This is an optional set of parameters for background scanning and
 * roaming within a network (ESS) in following format:
 * <bgscan module name>:<module parameters>
 */
 #define NVEE_LEN_N1_bgscan                                    (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N1_autoscan                                  (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)

/**
 * scan_freq - Array of frequencies to scan or %NULL for all
 *
 * This is an optional zero-terminated array of frequencies in
 * megahertz (MHz) to include in scan requests when searching for this
 * network. This can be used to speed up scanning when the network is
 * known to not use all possible channels.
 */
 #define NVEE_LEN_N1_scan_freq                                 (640 + PARAM_STR_EXTRA) // Unknown Size (expected size: channel count * 5, 2Ghz + 5Ghz) // 56 EA : 56(CH)*10(int)+56(space)+24(Margin)
 #define NVEE_LEN_N1_freq_list                                 (640 + PARAM_STR_EXTRA) // Unknown Size (expected size: channel count * 5, 2Ghz + 5Ghz) // 56 EA : 56(CH)*10(int)+56(space)+24(Margin)
 #define NVEE_LEN_N1_eap                                       (100 + PARAM_STR_EXTRA) // wpa_config_write_eap
 #define NVEE_LEN_N1_identity                                  (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N1_anonymous_identity                        (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N1_imsi_identity                             (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N1_password                                  (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N1_phase1                                    (20 + PARAM_STR_EXTRA)  // Unknown Size (expected size: aboud: 20)
 #define NVEE_LEN_N1_phase2                                    (20 + PARAM_STR_EXTRA)  // Unknown Size (expected size: aboud: 20)
 #define NVEE_LEN_N1_eapol_flags                               STR_INT32_LEN
 #define NVEE_LEN_N1_wep_key0                                  (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N1_wep_key1                                  (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N1_wep_key2                                  (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N1_wep_key3                                  (26 + PARAM_STR_EXTRA)  // MAX_WEP_KEY_LEN
 #define NVEE_LEN_N1_wep_tx_keyidx                             STR_INT32_LEN
 #define NVEE_LEN_N1_priority                                  STR_INT32_LEN
 #define NVEE_LEN_N1_eap_workaround                            STR_INT32_LEN
 #define NVEE_LEN_N1_pac_file                                  (32 + PARAM_STR_EXTRA)  // Unknown Size (expected size)
 #define NVEE_LEN_N1_fragment_size                             STR_INT32_LEN
 #define NVEE_LEN_N1_ocsp                                      STR_INT32_LEN
 #define NVEE_LEN_N1_sim_num                                   STR_INT32_LEN
 #define NVEE_LEN_N1_mode                                      STR_INT32_LEN
 #define NVEE_LEN_N1_no_auto_peer                              STR_INT32_LEN
 #define NVEE_LEN_N1_frequency                                 STR_INT32_LEN
 #define NVEE_LEN_N1_fixed_freq                                STR_INT32_LEN
 #define NVEE_LEN_N1_acs                                       STR_INT32_LEN
 #define NVEE_LEN_N1_proactive_key_caching                     STR_INT32_LEN
 #define NVEE_LEN_N1_disabled                                  STR_INT32_LEN
 #define NVEE_LEN_N1_pbss                                      STR_INT32_LEN
 #define NVEE_LEN_N1_wps_disabled                              STR_INT32_LEN
 #define NVEE_LEN_N1_fils_dh_group                             STR_INT32_LEN
 #define NVEE_LEN_N1_ieee80211w                                STR_INT32_LEN
 #define NVEE_LEN_N1_id_str                                    (256 + PARAM_STR_EXTRA)
 #define NVEE_LEN_N1_ignore_broadcast_ssid                     STR_INT32_LEN
 #define NVEE_LEN_N1_dtim_period                               STR_INT32_LEN
 #define NVEE_LEN_N1_beacon_int                                STR_INT32_LEN
 #define NVEE_LEN_N1_isolate                                   STR_INT32_LEN
 #define NVEE_LEN_N1_ap_max_inactivity                         STR_INT32_LEN
 #define NVEE_LEN_N1_ap_power                                  (8 + PARAM_STR_EXTRA)  // auto, ...
 #define NVEE_LEN_N1_update_identifier                         STR_INT32_LEN
 #define NVEE_LEN_N1_roaming_consortium_selection              (15 + PARAM_STR_EXTRA) // MAX_ROAMING_CONS_OI_LEN

/**
 * mac_addr - MAC address policy
 *
 * 0 = use permanent MAC address
 * 1 = use random MAC address for each ESS connection
 * 2 = like 1, but maintain OUI (with local admin bit set)
 *
 * Internally, special value -1 is used to indicate that the parameter
 * was not specified in the configuration (i.e., default behavior is
 * followed).
 */
 #define NVEE_LEN_N1_mac_addr                                  STR_INT32_LEN
 #define NVEE_LEN_N1_mesh_basic_rates                          (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N1_dot11MeshMaxRetries                       STR_INT32_LEN
 #define NVEE_LEN_N1_dot11MeshRetryTimeout                     STR_INT32_LEN
 #define NVEE_LEN_N1_dot11MeshConfirmTimeout                   STR_INT32_LEN
 #define NVEE_LEN_N1_dot11MeshHoldingTimeout                   STR_INT32_LEN
 #define NVEE_LEN_N1_mesh_rssi_threshold                       STR_INT32_LEN          // -255 ~1
 #define NVEE_LEN_N1_wpa_ptk_rekey                             STR_INT32_LEN
 #define NVEE_LEN_N1_wpa_deny_ptk0_rekey                       STR_INT32_LEN
 #define NVEE_LEN_N1_group_rekey                               STR_INT32_LEN
 #define NVEE_LEN_N1_dpp_connector                             (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N1_dpp_netaccesskey                          (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N1_dpp_netaccesskey_expiry                   STR_INT32_LEN
 #define NVEE_LEN_N1_dpp_csign                                 (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N1_owe_group                                 STR_INT32_LEN
 #define NVEE_LEN_N1_owe_only                                  STR_INT32_LEN
 #define NVEE_LEN_N1_owe_ptk_workaround                        STR_INT32_LEN
 #define NVEE_LEN_N1_multi_ap_backhaul_sta                     STR_INT32_LEN
 #define NVEE_LEN_N1_ft_eap_pmksa_caching                      STR_INT32_LEN
 #define NVEE_LEN_N1_beacon_prot                               STR_INT32_LEN
 #define NVEE_LEN_N1_transition_disable                        STR_INT32_LEN
 #define NVEE_LEN_N1_sae_pk                                    STR_INT32_LEN
 #define NVEE_LEN_N1_wifi_mode                                 STR_INT32_LEN

/**
 * mixed_cell - Whether mixed cells are allowed
 *
 * This option can be used to configure whether so called mixed cells,
 * i.e., networks that use both plaintext and encryption in the same
 * SSID, are allowed. This is disabled (0) by default. Enable by
 * setting this to 1.
 */
 #define NVEE_LEN_N1_mixed_cell                                STR_INT32_LEN
 #define NVEE_LEN_N1_ht                                        STR_INT32_LEN
 #define NVEE_LEN_N1_ht40                                      STR_INT32_LEN
 #define NVEE_LEN_N1_disable_ht                                STR_INT32_LEN
 #define NVEE_LEN_N1_disable_ht40                              STR_INT32_LEN
 #define NVEE_LEN_N1_disable_sgi                               STR_INT32_LEN
 #define NVEE_LEN_N1_disable_ldpc                              STR_INT32_LEN
 #define NVEE_LEN_N1_ht40_intolerant                           STR_INT32_LEN
 #define NVEE_LEN_N1_tx_stbc                                   STR_INT32_LEN
 #define NVEE_LEN_N1_rx_stbc                                   STR_INT32_LEN
 #define NVEE_LEN_N1_disable_max_amsdu                         STR_INT32_LEN
 #define NVEE_LEN_N1_ampdu_factor                              STR_INT32_LEN
 #define NVEE_LEN_N1_ampdu_density                             STR_INT32_LEN
 #define NVEE_LEN_N1_ht_mcs                                    (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N1_max_oper_chwidth                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_center_freq1                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_center_freq2                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht                                       STR_INT32_LEN
 #define NVEE_LEN_N1_disable_vht                               STR_INT32_LEN
 #define NVEE_LEN_N1_vht_capa                                  STR_INT32_LEN
 #define NVEE_LEN_N1_vht_capa_mask                             STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_1                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_2                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_3                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_4                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_5                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_6                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_7                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_rx_mcs_nss_8                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_1                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_2                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_3                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_4                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_5                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_6                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_7                          STR_INT32_LEN
 #define NVEE_LEN_N1_vht_tx_mcs_nss_8                          STR_INT32_LEN
 #define NVEE_LEN_N1_ca_cert                                   STR_INT32_LEN
 #define NVEE_LEN_N1_ca_path                                   STR_INT32_LEN
 #define NVEE_LEN_N1_client_cert                               STR_INT32_LEN
 #define NVEE_LEN_N1_private_key                               STR_INT32_LEN
 #define NVEE_LEN_N1_private_key_passwd                        STR_INT32_LEN
 #define NVEE_LEN_N1_dh_file                                   STR_INT32_LEN
 #define NVEE_LEN_N1_subject_match                             STR_INT32_LEN
 #define NVEE_LEN_N1_altsubject_match                          STR_INT32_LEN
 #define NVEE_LEN_N1_domain_suffix_match                       STR_INT32_LEN
 #define NVEE_LEN_N1_domain_match                              STR_INT32_LEN
 #define NVEE_LEN_N1_ca_cert2                                  STR_INT32_LEN
 #define NVEE_LEN_N1_ca_path2                                  STR_INT32_LEN
 #define NVEE_LEN_N1_client_cert2                              STR_INT32_LEN
 #define NVEE_LEN_N1_private_key2                              STR_INT32_LEN
 #define NVEE_LEN_N1_private_key2_passwd                       STR_INT32_LEN
 #define NVEE_LEN_N1_dh_file2                                  STR_INT32_LEN
 #define NVEE_LEN_N1_subject_match2                            STR_INT32_LEN
 #define NVEE_LEN_N1_altsubject_match2                         STR_INT32_LEN
 #define NVEE_LEN_N1_domain_suffix_match2                      STR_INT32_LEN
 #define NVEE_LEN_N1_domain_match2                             STR_INT32_LEN
 #define NVEE_LEN_N1_pcsc                                      (32 + PARAM_STR_EXTRA) // Unknown Size (expected size)
 #define NVEE_LEN_N1_pin                                       STR_INT32_LEN
 #define NVEE_LEN_N1_engine_id                                 STR_INT32_LEN
 #define NVEE_LEN_N1_key_id                                    STR_INT32_LEN
 #define NVEE_LEN_N1_cert_id                                   STR_INT32_LEN
 #define NVEE_LEN_N1_ca_cert_id                                STR_INT32_LEN
 #define NVEE_LEN_N1_key2_id                                   STR_INT32_LEN
 #define NVEE_LEN_N1_pin2                                      STR_INT32_LEN
 #define NVEE_LEN_N1_engine2_id                                STR_INT32_LEN
 #define NVEE_LEN_N1_cert2_id                                  STR_INT32_LEN
 #define NVEE_LEN_N1_ca_cert2_id                               STR_INT32_LEN
 #define NVEE_LEN_N1_engine                                    STR_INT32_LEN
 #define NVEE_LEN_N1_engine2                                   STR_INT32_LEN
 #define NVEE_LEN_N1_openssl_ciphers                           STR_INT32_LEN
 #define NVEE_LEN_N1_erp                                       STR_INT32_LEN
 #if 0                                 // def CONFIG_MACSEC
  #define NVEE_LEN_N1_macsec_policy                            STR_INT32_LEN
  #define NVEE_LEN_N1_macsec_integ_only                        STR_INT32_LEN
  #define NVEE_LEN_N1_macsec_port                              STR_INT32_LEN
  #define NVEE_LEN_N1_mka_priority                             STR_INT32_LEN
 #endif                                /* CONFIG_MACSEC */
 #define NVEE_LEN_sleep_mgmt_mode                              STR_INT32_LEN
 #define NVEE_LEN_sleep_mgmt_ddps                              STR_INT32_LEN
 #define NVEE_LEN_sleep_mgmt_ab_wf_conn_retry                  STR_INT32_LEN
 #define NVEE_LEN_sleep_mgmt_abnorm_stop                       STR_INT32_LEN
 #define NVEE_LEN_sleep_mgmt_ip_condition                      STR_INT32_LEN
 #define NVEE_LEN_abn_chk_conn_wait_name                       STR_INT32_LEN

 #define NVEE_LEN_abn_chk_dhcp_rsp_wait_name                   STR_INT32_LEN
 #define NVEE_LEN_abn_chk_arp_rsp_wait_name                    STR_INT32_LEN
 #define NVEE_LEN_abn_chk_fail_wait_name                       STR_INT32_LEN
 #define NVEE_LEN_abn_chk_conn_retry_cnt_name                  STR_INT32_LEN

// syscfg
//= =============================================================================
 #define HOSTNAME_MAX_LEN                                      32
 #define DHCPC_HOSTNAME_MAX_LEN                                HOSTNAME_MAX_LEN
 #define SNTP_SERVER_DOMAIN_MAX_LEN                            HOSTNAME_MAX_LEN
 #define TAG_DBG_TXPWR_2G                                      28
 #define TAG_DBG_TXPWR_5G                                      56
 #define TAG_DBG_TXPWR_5G_FLG                                  28

 #define NVEE_LEN_INITWLAN                                     STR_INT32_LEN
 #define NVEE_LEN_SYSMODE                                      STR_INT32_LEN
 #define NVEE_LEN_SWITCH_SYSMODE                               STR_INT32_LEN
 #define NVEE_LEN_0_MAC_SP                                     (12 + PARAM_STR_EXTRA)
 #define NVEE_LEN_0_NETMODE                                    STR_INT32_LEN
 #define NVEE_LEN_0_IP_Address                                 PARAM_IPADDR_LEN
 #define NVEE_LEN_0_NETMASK                                    PARAM_IPADDR_LEN
 #define NVEE_LEN_0_GATEWAY                                    PARAM_IPADDR_LEN
 #define NVEE_LEN_0_DNSSVR                                     PARAM_IPADDR_LEN
 #define NVEE_LEN_0_DNSSVR2                                    PARAM_IPADDR_LEN
 #define NVEE_LEN_0_TEMP_STATIC_IP                             STR_INT32_LEN

//= ===========

 #define NVEE_LEN_1_NETMODE                                    STR_INT32_LEN
 #define NVEE_LEN_1_IP_Address                                 PARAM_IPADDR_LEN
 #define NVEE_LEN_1_NETMASK                                    PARAM_IPADDR_LEN
 #define NVEE_LEN_1_GATEWAY                                    PARAM_IPADDR_LEN
 #define NVEE_LEN_1_DNSSVR                                     PARAM_IPADDR_LEN
 #define NVEE_LEN_1_DNSSVR2                                    PARAM_IPADDR_LEN

/* DHCP Server (IPv4) */
 #define NVEE_LEN_1_DHCP_SERVER_RUN                            STR_INT32_LEN
 #define NVEE_LEN_1_DHCP_SERVER_START_IP                       PARAM_IPADDR_LEN
 #define NVEE_LEN_1_DHCP_SERVER_END_IP                         PARAM_IPADDR_LEN
 #define NVEE_LEN_1_DHCP_SERVER_LEASE_TIME                     STR_INT32_LEN
 #define NVEE_LEN_1_DHCP_SERVER_DNS                            PARAM_IPADDR_LEN

/* IPv6 */
 #define NVEE_LEN_1_IPV6_ADDRESS                               PARAM_IP6ADDR_LEN

/* DHCP Server (IPv6) */
 #define NVEE_LEN_1_DHCPV6_SERVER_START_IP                     PARAM_IP6ADDR_LEN
 #define NVEE_LEN_1_DHCPV6_SERVER_END_IP                       PARAM_IP6ADDR_LEN
 #define NVEE_LEN_1_DHCPV6_SERVER_DNS                          PARAM_IP6ADDR_LEN
 #define NVEE_LEN_1_DHCPV6_SERVER_LEASE_TIME                   STR_INT32_LEN

/* Timezone */
 #define NVEE_LEN_TIMEZONE                                     STR_INT32_LEN

/* DHCP Client hostname */
 #define NVEE_LEN_DHCPC_HOSTNAME                               (DHCPC_HOSTNAME_MAX_LEN + PARAM_STR_EXTRA)

/* SNTP Server */
 #define NVEE_LEN_SNTP_SERVER_DOMAIN                           (SNTP_SERVER_DOMAIN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_SNTP_SERVER1_DOMAIN                          (SNTP_SERVER_DOMAIN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_SNTP_SERVER2_DOMAIN                          (SNTP_SERVER_DOMAIN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_SNTP_SYNC_PERIOD                             STR_INT32_LEN
 #define NVEE_LEN_SNTP_RUN_FLAG                                STR_INT32_LEN
 #define NVEE_LEN_DBG_TXPWR_2G_OFDM                            (TAG_DBG_TXPWR_2G + PARAM_STR_EXTRA)
 #define NVEE_LEN_DBG_TXPWR_2G_DSSS                            (TAG_DBG_TXPWR_2G + PARAM_STR_EXTRA)
 #define NVEE_LEN_DBG_TXPWR_5G                                 (TAG_DBG_TXPWR_5G + PARAM_STR_EXTRA)
 #define NVEE_LEN_DBG_TXPWR_5G_FLG                             (TAG_DBG_TXPWR_5G_FLG + PARAM_STR_EXTRA)

/* UART Config */
/* UART2 */
 #define NVEE_LEN_UART2_BAUDRATE                               (STR_INT32_LEN)
 #define NVEE_LEN_UART2_BITS                                   (STR_INT32_LEN)
 #define NVEE_LEN_UART2_PARITY                                 (STR_INT32_LEN)
 #define NVEE_LEN_UART2_STOPBIT                                (STR_INT32_LEN)
 #define NVEE_LEN_UART2_FLOWCTRL                               (STR_INT32_LEN)

/* UART3 */
 #define NVEE_LEN_UART3_BAUDRATE                               (STR_INT32_LEN)
 #define NVEE_LEN_UART3_BITS                                   (STR_INT32_LEN)
 #define NVEE_LEN_UART3_PARITY                                 (STR_INT32_LEN)
 #define NVEE_LEN_UART3_STOPBIT                                (STR_INT32_LEN)
 #define NVEE_LEN_UART3_FLOWCTRL                               (STR_INT32_LEN)

// appcfg
//= =============================================================================
 #define MATT_CLIENT_ID_MAX_LEN                                40
 #define MATT_TLS_ALPN_MAX_LEN                                 24
 #define MATT_TLS_SNI_MAX_LEN                                  64
 #define MATT_TLS_CSUIT_MAX_LEN                                84

 #define NVEE_LEN_MQTT_BROKER                                  (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_QOS                                     STR_INT32_LEN
 #define NVEE_LEN_MQTT_SUB_TOPIC                               (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_SUB_TOPIC0                              (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_SUB_TOPIC1                              (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_SUB_TOPIC2                              (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_SUB_TOPIC3                              (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_SUB_TOPIC_NUM                           STR_INT32_LEN
 #define NVEE_LEN_MQTT_PUB_TOPIC                               (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_TLS                                     STR_INT32_LEN
 #define NVEE_LEN_MQTT_USERNAME                                (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_PASSWORD                                (160 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_WILL_TOPIC                              (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_WILL_MSG                                (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_SUB_CID                                 (MATT_CLIENT_ID_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_PUB_CID                                 (MATT_CLIENT_ID_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_TLS_ALPN0                               (MATT_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_TLS_ALPN1                               (MATT_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_TLS_ALPN2                               (MATT_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_TLS_SNI                                 (MATT_TLS_SNI_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_MQTT_TLS_CSUIT_NUM                           STR_INT32_LEN
 #define NVEE_LEN_MQTT_TLS_CSUIT                               (MATT_TLS_CSUIT_MAX_LEN + PARAM_STR_EXTRA)

/* HTTP Client */
 #define HTTPC_TLS_ALPN_MAX_NUM                                3
 #define HTTPC_TLS_ALPN_MAX_LEN                                24
 #define HTTPC_TLS_SNI_MAX_LEN                                 64

 #define NVEE_LEN_HTTPC_TLS_ALPN0                              (HTTPC_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_HTTPC_TLS_ALPN1                              (HTTPC_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_HTTPC_TLS_ALPN2                              (HTTPC_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_HTTPC_TLS_SNI                                (HTTPC_TLS_SNI_MAX_LEN + PARAM_STR_EXTRA)

/* OTA update */
 #define OTA_TLS_ALPN_MAX_NUM                                  3
 #define OTA_TLS_ALPN_MAX_LEN                                  24
 #define OTA_TLS_SNI_MAX_LEN                                   64

 #define NVEE_LEN_OTA_TLS_ALPN0                                (OTA_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_OTA_TLS_ALPN1                                (OTA_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_OTA_TLS_ALPN2                                (OTA_TLS_ALPN_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_OTA_TLS_SNI                                  (OTA_TLS_SNI_MAX_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_URL                                          (256 + PARAM_STR_EXTRA)

/* ATCMD: TCP Server, Client, and UDP Session */
 #define NW_TR_PIPADDR_LEN                                     (46 + PARAM_STR_EXTRA)
 #define NVEE_LEN_ATC_NW_TR_PIPADDR                            NW_TR_PIPADDR_LEN

/* ATCMD: TLS Client */
 #define NW_TLSC_CA_CERT_NAME_LEN                              32
 #define NW_TLSC_CERT_NAME_LEN                                 32
 #define NW_TLSC_HOST_NAME_LEN                                 64
 #define NW_TLSC_PEER_IPADDR_LEN                               64
 #define NVEE_LEN_ATC_NW_TLSC_CA_CERT_NAME                     (NW_TLSC_CA_CERT_NAME_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_ATC_NW_TLSC_CERT_NAME                        (NW_TLSC_CERT_NAME_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_ATC_NW_TLSC_HOST_NAME                        (NW_TLSC_HOST_NAME_LEN + PARAM_STR_EXTRA)
 #define NVEE_LEN_ATC_NW_TLSC_PIPADDR                          (NW_TLSC_PEER_IPADDR_LEN + PARAM_STR_EXTRA)

/* BLE-COMBO : BLE Provisioning - provisioning status  */
 #define NVEE_LEN_BLE_COMBO_PROVISIONED                        (STR_INT32_LEN)
 #define NVEE_LEN_BLE_COMBO_PROV_SRV_IP                        (PARAM_IPADDR_LEN)
 #define NVEE_LEN_BLE_COMBO_PROV_SRV_PORT                      (STR_INT32_LEN)

/* BLE-COMBO : For Gas Leak sensor sample  */
 #define NVEE_LEN_BLE_COMBO_SENSOR_STARTED                     (STR_INT32_LEN)

/* BLE-COMBO : For Sensor gateway sample  */
 #define NVEE_LEN_BLE_COMBO_SENSOR_GW_UDP_SVR_IP               (PARAM_IPADDR_LEN)
 #define NVEE_LEN_BLE_COMBO_SENSOR_GW_UDP_SVR_PORT             (STR_INT32_LEN)

/* BLE-COMBO : For TCPC DPM sample  */
 #define NVEE_LEN_BLE_COMBO_TCPC_SVR_IP                        (PARAM_IPADDR_LEN)
 #define NVEE_LEN_BLE_COMBO_TCPC_SVR_PORT                      (STR_INT32_LEN)

/* BLE-COMBO : For OTA  */
 #define OTA_HTTP_URL_LENGTH                                   256
 #define NVEE_LEN_BLE_COMBO_OTA_URI_RTOS                       (OTA_HTTP_URL_LENGTH)
 #define NVEE_LEN_BLE_COMBO_OTA_URI_BLE                        (OTA_HTTP_URL_LENGTH)
 #define NVEE_LEN_DPM_REG_NAME_TIMER                           (STR_INT32_LEN)
 #define NVEE_LEN_DPM_MNG_UDPC_SVR_IP                          (PARAM_IPADDR_LEN)
 #define NVEE_LEN_DPM_MNG_UDPC_SVR_PORT                        (STR_INT32_LEN)

/* Apps WiFi Provisioning for Mobile App */
 #define NVEE_LEN_APP_APPTHINGNAME                             (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_APP_SETSLEEPMODE                             STR_INT32_LEN
 #define NVEE_LEN_APP_SLEEPMODERTCTIME                         STR_INT32_LEN
 #define NVEE_LEN_APP_SETUSEDPM                                STR_INT32_LEN

/* TCP Client application */
 #define NVEE_LEN_APP_TCPC_ACTIVE                              (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_PEER_IP_ADDR                        (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_APP_TCPC_PEER_PORT                           (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_SEND_PERIOD                         (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_SEND_DATA_SIZE                      (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_AUTO_RESTART_AT_EXIT                (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_KA_ENABLE                           (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_KA_IDLE_TIME                        (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_KA_INTVL_TIME                       (UINT32_LEN)
 #define NVEE_LEN_APP_TCPC_KA_MAX_PROBES                       (UINT32_LEN)

// blecfg

/* BD address is saved in next format: aa:bb:cc:dd:ee:ff */
 #define NVEE_LEN_BLECFG_BD_ADDR                               (17 + PARAM_STR_EXTRA)

// blesec

 #define NVEE_LEN_BLESEC_BOOT_DATA                             (48)
 #define NVEE_LEN_BLESEC_BONDING_DATA                          (80 + 16) // BOND DATA + IV

 #define AWSIOT_CFG_THINGNAME                                  "thingname"
 #define AWSIOT_CFG_USE_FLEET_PROVISION                        "use_fp"
 #define AWSIOT_CFG_FLEET_PROVISIONING_DEVICE_ID               "fp_dev_id"
 #define AWSIOT_CFG_FLEET_PROVISIONING_TEMPLATE_NAME           "fp_tmpl_name"
 #define AWSIOT_CFG_BROKER_URL                                 "broker_url"
 #define AWSIOT_CFG_BOARD_FEATURE                              "board_feature"
 #define AWSIOT_CFG_LPORT                                      "lport"
 #define AWSIOT_CFG_PORT                                       "port"
 #define AWSIOT_CFG_STOPIC                                     "stopic"
 #define AWSIOT_CFG_PTOPIC                                     "ptopic"
 #define AWSIOT_CFG_DPM_SLEEP_MODE                             "sleepmode"
 #define AWSIOT_CFG_USE_DPM                                    "usedpm"
 #define AWSIOT_CFG_RTC_TIME                                   "rtc_time"
 #define AWSIOT_CFG_DPM_KEEP_ALIVE_TIME                        "keepalive_time"
 #define AWSIOT_CFG_USER_WAKE_UP_TIME                          "usr_wakeup_time"
 #define AWSIOT_CFG_TIM_WAKE_UP_TIME                           "tim_wakeup_time"
 #define AWSIOT_CFG_MCU_WAKEUP_PORT                            "mcu_wu_port"
 #define AWSIOT_CFG_MCU_WAKEUP_PIN                             "mcu_wu_pin"
 #define AWSIOT_CFG_SAVED_IP_ADDRESS                           "ipaddr"
 #define AWSIOT_CFG_OTA_URL                                    "ota_url"
 #define AWSIOT_CFG_OTA_STATE                                  "ota_state"
 #define AWSIOT_CFG_OTA_RESULT                                 "ota_result"
 #define AWSIOT_CFG_OTA_FLAG                                   "ota_flag"
 #define AWSIOT_CFG_SLEEP_MODE2_RTC_TIME                       "sleep2rtc"
 #define AWSIOT_CFG_FIRST_SNTP_TIME                            "sntp_time"
 #define AWSIOT_CFG_SNTP_SUCCESS_FLAG                          "sntp_success"
 #define AWSIOT_CFG_PING_CHECK                                 "ping_check"
 #define AWSIOT_CFG_DPM_AUTO                                   "dpm_auto"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_0                         "T_att0"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_1                         "T_att1"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_2                         "T_att2"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_3                         "T_att3"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_4                         "T_att4"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_5                         "T_att5"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_6                         "T_att6"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_7                         "T_att7"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_8                         "T_att8"
 #define AWSIOT_CFG_THING_ATTIRIBUTE_9                         "T_att9"

 #define NVEE_LEN_AWSIOT_CFG_THINGNAME                         (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_FLEET_PROVISIONING_DEVICE_ID                 (44 + PARAM_STR_EXTRA)
 #define NVEE_LEN_AWSIOT_CFG_FLEET_PROV_TEMPLATE_NAME          (64 + PARAM_STR_EXTRA)

 #define NVEE_LEN_BROKER_URL                                   NVEE_LEN_URL
 #define NVEE_LEN_BOARD_FEATURE                                32
 #define NVEE_LEN_AWSIOT_CFG_OTA_URL                           NVEE_LEN_URL
 #define NVEE_LEN_AWSIOT_CFG_SAVED_IP_ADDRESS                  PARAM_IPADDR_LEN
 #define NVEE_LEN_FIRST_SNTP_TIME                              STR_INT32_LEN
 #define NVEE_LEN_STOPIC                                       (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_PTOPIC                                       (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_MCU_WAKEUP_PORT                              12
 #define NVEE_LEN_MCU_WAKEUP_PIN                               12
 #define NVEE_LEN_THING_ATTRIBUTE                              32
 #define MAX_THING_ATT                                         10

 #define APP_NVRAM_CONFIG_DEV_PRIMARY_KEY                      "dev_prim_key"
 #define APP_NVRAM_CONFIG_HOST_NAME                            "host_name"
 #define APP_NVRAM_CONFIG_IOTHUB_CONN_STRING                   "iothub_conn_str"
 #define APP_NVRAM_CONFIG_THINGNAME                            "thingname"
 #define APP_NVRAM_DEVICE_CONNECTION_STRING                    "device_conn_str"
 #define AZURE_NVRAM_CONFIG_CURRENT_OTA_VERSION                "current_ota_ver"
 #define AZURE_NVRAM_CONFIG_CURRENT_MCUOTA_VERSION             "current_mcuota_ver"
 #define AZURE_NVRAM_CONFIG_OTA_URL                            "ota_url"
 #define AZURE_NVRAM_CONFIG_OTA_VERSION                        "ota_ver"
 #define AZURE_NVRAM_CONFIG_MCUOTA_VERSION                     "mcuota_ver"
 #define AZURE_NVRAM_CONFIG_PORT                               "az_port"
 #define AZURE_NVRAM_CONFIG_OTA_FLAG                           "ota_flag"
 #define AZURE_NVRAM_CONFIG_OTA_STATE                          "ota_state"
 #define AZURE_NVRAM_CONFIG_OTA_RESULT                         "ota_result"

 #define NVEE_LEN_APP_NVRAM_CONFIG_DEV_PRIMARY_KEY             (256 + PARAM_STR_EXTRA)
 #define NVEE_LEN_APP_NVRAM_CONFIG_HOST_NAME                   (64 + PARAM_STR_EXTRA)
 #define NVEE_LEN_APP_NVRAM_CONFIG_IOTHUB_CONN_STRING          (512 + PARAM_STR_EXTRA)
 #define NVEE_LEN_APP_NVRAM_CONFIG_THINGNAME                   (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_APP_NVRAM_DEVICE_CONNECTION_STRING           (512 + PARAM_STR_EXTRA)
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_CURRENT_OTA_VERSION       (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_CURRENT_MCUOTA_VERSION    (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_URL                   (256 + PARAM_STR_EXTRA)
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_VERSION               (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_MCUOTA_VERSION            (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_PORT                      STR_INT32_LEN
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_FLAG                  STR_INT32_LEN
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_STATE                 STR_INT32_LEN
 #define NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_RESULT                STR_INT32_LEN

 #define WIFI_PROFILE_COMPLETE                                 "profile_complete"
 #define WIFI_PROFILE_COUNTRY_CODE                             "country_code"
 #define WIFI_PROFILE_SYS_MODE                                 "sysmode"
 #define WIFI_PROFILE_BAND                                     "band"
 #define WIFI_PROFILE_CHANNEL                                  "channel"
 #define WIFI_PROFILE_WIFI_MODE                                "wifi_mode"
 #define WIFI_PROFILE_PMF                                      "pmf"
 #define WIFI_PROFILE_ENABLE_DPM                               "enable_dpm"
 #define WIFI_PROFILE_DPM_DEBUG_RUNTIME_FLAG                   "dpm_debug_enable"
 #define WIFI_PROFILE_DPM_DPM_KEEPALIVE_TIME                   "dpm_keepalive_time"
 #define WIFI_PROFILE_DPM_USER_WAKEUP_TIME                     "dpm_user_wakeup_time"
 #define WIFI_PROFILE_DPM_TIM_WAKEUP_COUNT                     "dpm_TIM_wakeup_count"
 #define WIFI_PROFILE_DPM_BLE_HIBERNATE                        "dpm_ble_hibernate"
 #define WIFI_PROFILE_SSID_0                                   "ssid_0"
 #define WIFI_PROFILE_SSID_1                                   "ssid_1"
 #define WIFI_PROFILE_HIDDEN_SSID                              "hidden_ssid"
 #define WIFI_PROFILE_PMF_0                                    "pmf_0"
 #define WIFI_PROFILE_PMF_1                                    "pmf_1"
 #define WIFI_PROFILE_SECURITY_0                               "security_0"
 #define WIFI_PROFILE_SECURITY_1                               "security_1"
 #define WIFI_PROFILE_ENCKEY_0                                 "password_0"
 #define WIFI_PROFILE_ENCKEY_1                                 "password_1"
 #define WIFI_PROFILE_WEPKEY0_0                                "wep_key"
 #define WIFI_PROFILE_WEPINDEX_0                               "wep_key_idx"
 #define WIFI_PROFILE_WEPTYPE_0                                "wep_key_type"
 #define WIFI_PROFILE_SAE_GROUPS_0                             "sae_groups_0"
 #define WIFI_PROFILE_SAE_GROUPS_1                             "sae_groups_1"
 #define WIFI_PROFILE_EAP_AUTH_MODE                            "eap_auth_mode"
 #define WIFI_PROFILE_EAP_PHASE2                               "eap_phase2"
 #define WIFI_PROFILE_EAP_ID                                   "eap_id"
 #define WIFI_PROFILE_EAP_PW                                   "eap_pw"
 #define WIFI_PROFILE_P2P_SSID_POSTFIX                         "p2p_ssid_postfix"
 #define WIFI_PROFILE_P2P_GROUP_IDLE                           "p2p_group_idle"
 #define WIFI_PROFILE_P2P_LISTEN_CH                            "p2p_listen_chan"
 #define WIFI_PROFILE_P2P_FIND_TIMEOUT                         "p2p_find_timeout"
 #define WIFI_PROFILE_P2P_GO_INTENT                            "p2p_go_intent"
 #define WIFI_PROFILE_NETMODE_0                                "netmode_0"
 #define WIFI_PROFILE_NETMODE_1                                "netmode_1"
 #define WIFI_PROFILE_IPADDR_0                                 "ipaddress_0"
 #define WIFI_PROFILE_IPADDR_1                                 "ipaddress_1"
 #define WIFI_PROFILE_NETMASK_0                                "subnetmask_0"
 #define WIFI_PROFILE_NETMASK_1                                "subnetmask_1"
 #define WIFI_PROFILE_GATEWAY_0                                "gateway_0"
 #define WIFI_PROFILE_GATEWAY_1                                "gateway_1"
 #define WIFI_PROFILE_DNSSVR_0                                 "dns_0"
 #define WIFI_PROFILE_DNSSVR_1                                 "dns_1"
 #define WIFI_PROFILE_DNSSVR_2ND_0                             "dns_2nd_0"
 #define WIFI_PROFILE_DNSSVR_2ND_1                             "dns_2nd_1"
 #define WIFI_PROFILE_AP_MAX_INACTIVITY_1                      "ap_max_inactivity_1"
 #define WIFI_PROFILE_AP_WMM_PS_1                              "ap_wmm_ps_1"
 #define WIFI_PROFILE_AP_WMM_1                                 "ap_wmm_1"
 #define WIFI_PROFILE_SCAN_CHAN_NUM                            "scan_channel_number"
 #define WIFI_PROFILE_SCAN_CHAN_LIST                           "scan_channel_list"
 #define WIFI_PROFILE_AP_ENC_MODE_1                            "ap_enc_1"

 #define NVEE_LEN_WIFI_country_code                            (3 + PARAM_STR_EXTRA)
 #define NVEE_LEN_WIFI_sysmode                                 STR_INT32_LEN
 #define NVEE_LEN_WIFI_band                                    STR_INT32_LEN
 #define NVEE_LEN_WIFI_channel                                 STR_INT32_LEN
 #define NVEE_LEN_WIFI_wifi_mode                               STR_INT32_LEN
 #define NVEE_LEN_WIFI_pmf                                     STR_INT32_LEN
 #define NVEE_LEN_WIFI_enable_dpm                              STR_INT32_LEN
 #define NVEE_LEN_WIFI_dpm_debug_runtime_flag                  STR_INT32_LEN
 #define NVEE_LEN_WIFI_dpm_keepalive_time                      STR_INT32_LEN
 #define NVEE_LEN_WIFI_dpm_user_wakeup_time                    STR_INT32_LEN
 #define NVEE_LEN_WIFI_dpm_TIM_wakeup_count                    STR_INT32_LEN
 #define NVEE_LEN_WIFI_dpm_ble_hibernate                       STR_INT32_LEN
 #define NVEE_LEN_WIFI_ssid_0                                  (32 * 2 + PARAM_STR_EXTRA)
 #define NVEE_LEN_WIFI_ssid_1                                  (32 * 2 + PARAM_STR_EXTRA)
 #define NVEE_LEN_WIFI_hidden_ssid                             STR_INT8_LEN
 #define NVEE_LEN_WIFI_password_0                              (32 * 2 + PARAM_STR_EXTRA)
 #define NVEE_LEN_WIFI_password_1                              (32 * 2 + PARAM_STR_EXTRA)
 #define NVEE_LEN_WIFI_security_0                              STR_INT32_LEN
 #define NVEE_LEN_WIFI_security_1                              STR_INT32_LEN
 #define NVEE_LEN_WIFI_wep_key                                 (26 + PARAM_STR_EXTRA)
 #define NVEE_LEN_WIFI_wep_key_idx                             STR_INT32_LEN
 #define NVEE_LEN_WIFI_wep_key_type                            STR_INT32_LEN
 #define NVEE_LEN_WIFI_eap_auth_mode                           STR_INT32_LEN
 #define NVEE_LEN_WIFI_eap_phase2                              STR_INT32_LEN
 #define NVEE_LEN_WIFI_eap_id                                  (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN_WIFI_eap_pw                                  (32 + PARAM_STR_EXTRA)
 #define NVEE_LEN__WIFI_p2p_ssid_postfix                       (23 + PARAM_STR_EXTRA)
 #define NVEE_LEN__WIFI_p2p_group_idle                         STR_INT32_LEN
 #define NVEE_LEN_WIFI_p2p_listen_chan                         STR_INT32_LEN
 #define NVEE_LEN_WIFI_p2p_go_intent                           STR_INT32_LEN
 #define NVEE_LEN_WIFI_p2p_find_timeout                        STR_INT32_LEN
 #define NVEE_LEN_WIFI_netmode_0                               STR_INT32_LEN
 #define NVEE_LEN_WIFI_netmode_1                               STR_INT32_LEN
 #define NVEE_LEN_WIFI_ipaddress_0                             PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_ipaddress_1                             PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_subnetmask_0                            PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_subnetmask_1                            PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_gateway_0                               PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_gateway_1                               PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_dns_0                                   PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_dns_1                                   PARAM_IPADDR_LEN
 #define NVEE_LEN_WIFI_ap_max_inactivity_1                     STR_INT32_LEN
 #define NVEE_LEN_WIFI_profile_complete                        STR_INT32_LEN
 #define NVEE_LEN_WIFI_chan_list                               (128 + PARAM_STR_EXTRA)

//= =============================================================================
// boocfg
//= =============================================================================
NVPARAM_AREA(bootcfg, NVMS_GENERIC_PART)

// TAG-NAME, MAX-LENGTH
NVPARAM_VARPARAM("chip", NVEE_LEN_BOOT_CHIP)
NVPARAM_VARPARAM("platform", NVEE_LEN_BOOT_PLATFORM)
NVPARAM_PARAM("clk.cpu", NVEE_LEN_BOOT_CLK_CPU)
NVPARAM_PARAM("clk.bus", NVEE_LEN_BOOT_CLK_BUS)
NVPARAM_PARAM("con.baud", NVEE_LEN_BOOT_BAUD)
NVPARAM_PARAM("con.bit", NVEE_LEN_BOOT_BIT)
NVPARAM_PARAM("con.stop", NVEE_LEN_BOOT_STOP)
NVPARAM_AREA_END()

//= =============================================================================
// devcfg
//= =============================================================================
NVPARAM_AREA(devcfg, NVMS_GENERIC_PART)

// TAG-NAME, MAX-LENGTH
NVPARAM_VARPARAM("WLANMAC", NVEE_LEN_WLANMAC)
NVPARAM_PARAM("ATCMD_UART_BAUDRATE", NVEE_LEN_ATCMD_UART_BAUDRATE)
NVPARAM_PARAM("ATCMD_UART_BITS", NVEE_LEN_ATCMD_UART_BITS)
NVPARAM_PARAM("ATCMD_UART_PARITY", NVEE_LEN_ATCMD_UART_PARITY)
NVPARAM_PARAM("ATCMD_UART_STOPBIT", NVEE_LEN_ATCMD_UART_STOPBIT)
NVPARAM_PARAM("ATCMD_UART_FLOWCTRL", NVEE_LEN_ATCMD_UART_FLOWCTRL)
NVPARAM_AREA_END()

//= =============================================================================
// wificfg
//= =============================================================================
NVPARAM_AREA(wificfg, NVMS_GENERIC_PART)

// TAG-NAME, MAX-LENGTH
//= ============================================================================

/* wpa_config_global */

//= ============================================================================
NVPARAM_VARPARAM("uuid", NVEE_LEN_uuid)
NVPARAM_VARPARAM("auto_uuid", NVEE_LEN_auto_uuid)
NVPARAM_VARPARAM("device_name", NVEE_LEN_device_name)
NVPARAM_VARPARAM("manufacturer", NVEE_LEN_manufacturer)
NVPARAM_VARPARAM("model_name", NVEE_LEN_model_name)
NVPARAM_VARPARAM("model_number", NVEE_LEN_model_number)
NVPARAM_VARPARAM("serial_number", NVEE_LEN_serial_number)
NVPARAM_VARPARAM("device_type", NVEE_LEN_device_type) /* WPS_DEV_TYPE_LEN */
NVPARAM_VARPARAM("config_methods", NVEE_LEN_config_methods)
NVPARAM_VARPARAM("p2p_ssid_postfix", NVEE_LEN_p2p_ssid_postfix)
NVPARAM_VARPARAM("p2p_group_idle", NVEE_LEN_p2p_group_idle)
NVPARAM_PARAM("p2p_listen_channel", INT32_LEN)
NVPARAM_PARAM("p2p_oper_channel", INT32_LEN)
NVPARAM_PARAM("p2p_find_timeout", INT32_LEN)
NVPARAM_PARAM("p2p_go_intent", INT32_LEN)
NVPARAM_PARAM("wmm_enabled", INT32_LEN)
NVPARAM_PARAM("wmm_ps_enabled", INT32_LEN)
NVPARAM_VARPARAM("ap_max_inactivity", NVEE_LEN_ap_max_inactivity)
NVPARAM_VARPARAM("ap_send_ka", NVEE_LEN_ap_send_ka)
NVPARAM_VARPARAM("bss_max_count", NVEE_LEN_bss_max_count)
NVPARAM_VARPARAM("bss_expiration_age", NVEE_LEN_bss_expiration_age)
NVPARAM_VARPARAM("bss_expiration_scan_count", NVEE_LEN_bss_expiration_scan_count)
NVPARAM_VARPARAM("filter_ssids", NVEE_LEN_filter_ssids)
NVPARAM_VARPARAM("filter_rssi", NVEE_LEN_filter_rssi)
NVPARAM_VARPARAM("max_num_sta", NVEE_LEN_max_num_sta)
NVPARAM_VARPARAM("ap_isolate", NVEE_LEN_ap_isolate)
NVPARAM_VARPARAM("disassoc_low_ack", NVEE_LEN_disassoc_low_ack)
NVPARAM_VARPARAM("hs20", NVEE_LEN_hs20)
NVPARAM_VARPARAM("interworking", NVEE_LEN_interworking)
NVPARAM_VARPARAM("hessid", NVEE_LEN_hessid)
NVPARAM_VARPARAM("access_network_type", NVEE_LEN_access_network_type)
NVPARAM_VARPARAM("go_interworking", NVEE_LEN_go_interworking)
NVPARAM_VARPARAM("go_access_network_type", NVEE_LEN_go_access_network_type)
NVPARAM_VARPARAM("go_internet", NVEE_LEN_go_internet)
NVPARAM_VARPARAM("go_venue_group", NVEE_LEN_go_venue_group)
NVPARAM_VARPARAM("go_venue_type", NVEE_LEN_go_venue_type)
NVPARAM_VARPARAM("pbc_in_m1", NVEE_LEN_pbc_in_m1)
NVPARAM_VARPARAM("wps_nfc_dev_pw_id", NVEE_LEN_wps_nfc_dev_pw_id)
NVPARAM_VARPARAM("ext_password_backend", NVEE_LEN_ext_password_backend)
NVPARAM_VARPARAM("p2p_go_max_inactivity", NVEE_LEN_p2p_go_max_inactivity)
NVPARAM_VARPARAM("auto_interworking", NVEE_LEN_auto_interworking)
NVPARAM_VARPARAM("okc", NVEE_LEN_okc)
NVPARAM_VARPARAM("pmf", NVEE_LEN_pmf)
NVPARAM_VARPARAM("dtim_period", NVEE_LEN_dtim_period)
NVPARAM_VARPARAM("beacon_int", NVEE_LEN_beacon_int)
NVPARAM_VARPARAM("sae_groups", NVEE_LEN_sae_groups)
NVPARAM_VARPARAM("ignore_old_scan_res", NVEE_LEN_ignore_old_scan_res)
NVPARAM_VARPARAM("scan_cur_freq", NVEE_LEN_scan_cur_freq)
NVPARAM_VARPARAM("sched_scan_interval", NVEE_LEN_sched_scan_interval)
NVPARAM_VARPARAM("sched_scan_start_delay", NVEE_LEN_sched_scan_start_delay)
NVPARAM_VARPARAM("external_sim", NVEE_LEN_external_sim)
NVPARAM_VARPARAM("tdls_external_control", NVEE_LEN_tdls_external_control)
NVPARAM_VARPARAM("wowlan_triggers", NVEE_LEN_wowlan_triggers)
NVPARAM_VARPARAM("bgscan", NVEE_LEN_bgscan)
NVPARAM_VARPARAM("autoscan", NVEE_LEN_autoscan)
NVPARAM_VARPARAM("p2p_search_delay", NVEE_LEN_p2p_search_delay)
NVPARAM_VARPARAM("mac_addr", NVEE_LEN_mac_addr)
NVPARAM_VARPARAM("rand_addr_lifetime", NVEE_LEN_rand_addr_lifetime)
NVPARAM_VARPARAM("preassoc_mac_addr", NVEE_LEN_preassoc_mac_addr)
NVPARAM_VARPARAM("key_mgmt_offload", NVEE_LEN_key_mgmt_offload)
NVPARAM_VARPARAM("user_mpm", NVEE_LEN_user_mpm)
NVPARAM_VARPARAM("max_peer_links", NVEE_LEN_max_peer_links)
NVPARAM_VARPARAM("cert_in_cb", NVEE_LEN_cert_in_cb)
NVPARAM_VARPARAM("mesh_max_inactivity", NVEE_LEN_mesh_max_inactivity)
NVPARAM_VARPARAM("dot11RSNASAERetransPeriod", NVEE_LEN_dot11RSNASAERetransPeriod)

NVPARAM_VARPARAM("reassoc_same_bss_optim", NVEE_LEN_reassoc_same_bss_optim)
NVPARAM_VARPARAM("wps_priority", NVEE_LEN_wps_priority)
NVPARAM_VARPARAM("wpa_rsc_relaxation", NVEE_LEN_wpa_rsc_relaxation)

NVPARAM_VARPARAM("sched_scan_plans", NVEE_LEN_sched_scan_plans)

NVPARAM_VARPARAM("non_pref_chan", NVEE_LEN_non_pref_chan)
NVPARAM_VARPARAM("mbo_cell_capa", NVEE_LEN_mbo_cell_capa)
NVPARAM_VARPARAM("disassoc_imminent_rssi_threshold", NVEE_LEN_disassoc_imminent_rssi_threshold)
NVPARAM_VARPARAM("oce", NVEE_LEN_oce)

NVPARAM_VARPARAM("gas_address3", NVEE_LEN_gas_address3)
NVPARAM_VARPARAM("ftm_responder", NVEE_LEN_ftm_responder)
NVPARAM_VARPARAM("ftm_initiator", NVEE_LEN_ftm_initiator)
NVPARAM_VARPARAM("osu_dir", NVEE_LEN_osu_dir)
NVPARAM_VARPARAM("fst_group_id", NVEE_LEN_fst_group_id)
NVPARAM_VARPARAM("fst_priority", NVEE_LEN_fst_priority)
NVPARAM_VARPARAM("fst_llt", NVEE_LEN_fst_llt)
NVPARAM_VARPARAM("gas_rand_addr_lifetime", NVEE_LEN_gas_rand_addr_lifetime)
NVPARAM_VARPARAM("gas_rand_mac_addr", NVEE_LEN_gas_rand_mac_addr)
NVPARAM_VARPARAM("dpp_config_processing", NVEE_LEN_dpp_config_processing)
NVPARAM_PARAM("STA_roam", INT32_LEN)
NVPARAM_PARAM("STA_roam_thold", INT32_LEN)
NVPARAM_VARPARAM("greenfield", NVEE_LEN_greenfield)
NVPARAM_VARPARAM("ht_protection", NVEE_LEN_ht_protection)
NVPARAM_PARAM("rts_threshold", INT32_LEN)

NVPARAM_VARPARAM("acl_cmd", NVEE_LEN_acl_cmd)
NVPARAM_VARPARAM("country_code", NVEE_LEN_country_code)
NVPARAM_VARPARAM("tls_ver", NVEE_LEN_tls_ver)
NVPARAM_PARAM("rootca_chk", INT32_LEN)
NVPARAM_PARAM("peap_ver", INT32_LEN)
NVPARAM_VARPARAM("supp_log_mask", NVEE_LEN_supp_log_mask)
NVPARAM_VARPARAM("supp_wpa_log_mask", NVEE_LEN_supp_wpa_log_mask)
NVPARAM_VARPARAM("setband", NVEE_LEN_setband)
NVPARAM_VARPARAM("p2p_ps", NVEE_LEN_p2p_ps)
NVPARAM_VARPARAM("TEMP_PIN", NVEE_LEN_TEMP_PIN)
NVPARAM_VARPARAM("fast_reauth", NVEE_LEN_fast_reauth)
NVPARAM_VARPARAM("fast_pac", NVEE_LEN_fast_pac)
NVPARAM_VARPARAM("fast_pac_len", NVEE_LEN_fast_pac_len)

// Supplicant Network Profiles (N0_ ~ N1_ : STA, SOFTAP, P2P, MESH)
//= ============================================================================
// Supplicant Network Profiles (N0_ : STA)
//= ============================================================================
NVPARAM_PARAM(NPRO_0 "Profile", INT32_LEN)
NVPARAM_VARPARAM(NPRO_0 "ssid", NVEE_LEN_N0_ssid)
NVPARAM_PARAM(NPRO_0 "scan_ssid", INT32_LEN)
NVPARAM_VARPARAM(NPRO_0 "bssid", NVEE_LEN_N0_bssid)
NVPARAM_VARPARAM(NPRO_0 "bssid_hint", NVEE_LEN_N0_bssid_hint)
NVPARAM_VARPARAM(NPRO_0 "bssid_blacklist", NVEE_LEN_N0_bssid_blacklist)
NVPARAM_VARPARAM(NPRO_0 "bssid_whitelist", NVEE_LEN_N0_bssid_whitelist)
NVPARAM_VARPARAM(NPRO_0 "psk", NVEE_LEN_N0_psk)
NVPARAM_VARPARAM(NPRO_0 "PSK_RAW_KEY", NVEE_LEN_N0_psk_raw)

NVPARAM_VARPARAM(NPRO_0 "mem_only_psk", NVEE_LEN_N0_mem_only_psk)
NVPARAM_VARPARAM(NPRO_0 "sae_password", NVEE_LEN_N0_sae_password)
NVPARAM_VARPARAM(NPRO_0 "sae_password_id", NVEE_LEN_N0_sae_password_id)
NVPARAM_VARPARAM(NPRO_0 "proto", NVEE_LEN_N0_proto)
NVPARAM_VARPARAM(NPRO_0 "key_mgmt", NVEE_LEN_N0_key_mgmt)
NVPARAM_VARPARAM(NPRO_0 "bg_scan_period", NVEE_LEN_N0_bg_scan_period)
NVPARAM_VARPARAM(NPRO_0 "pairwise", NVEE_LEN_N0_pairwise)
NVPARAM_VARPARAM(NPRO_0 "group", NVEE_LEN_N0_group)
NVPARAM_VARPARAM(NPRO_0 "group_mgmt", NVEE_LEN_N0_group_mgmt)
NVPARAM_VARPARAM(NPRO_0 "auth_alg", NVEE_LEN_N0_auth_alg)
NVPARAM_VARPARAM(NPRO_0 "bgscan", NVEE_LEN_N0_bgscan)
NVPARAM_VARPARAM(NPRO_0 "autoscan", NVEE_LEN_N0_autoscan)
NVPARAM_VARPARAM(NPRO_0 "scan_freq", NVEE_LEN_N0_scan_freq)
NVPARAM_VARPARAM(NPRO_0 "freq_list", NVEE_LEN_N0_freq_list)

NVPARAM_VARPARAM(NPRO_0 "eap", NVEE_LEN_N0_eap)
NVPARAM_VARPARAM(NPRO_0 "identity", NVEE_LEN_N0_identity)
NVPARAM_VARPARAM(NPRO_0 "anonymous_identity", NVEE_LEN_N0_anonymous_identity)
NVPARAM_VARPARAM(NPRO_0 "imsi_identity", NVEE_LEN_N0_imsi_identity)
NVPARAM_VARPARAM(NPRO_0 "password", NVEE_LEN_N0_password)
NVPARAM_VARPARAM(NPRO_0 "phase1", NVEE_LEN_N0_phase1)
NVPARAM_VARPARAM(NPRO_0 "phase2", NVEE_LEN_N0_phase2)
NVPARAM_VARPARAM(NPRO_0 "eapol_flags", NVEE_LEN_N0_eapol_flags)
NVPARAM_VARPARAM(NPRO_0 "wep_key0", NVEE_LEN_N0_wep_key0)
NVPARAM_VARPARAM(NPRO_0 "wep_key1", NVEE_LEN_N0_wep_key1)
NVPARAM_VARPARAM(NPRO_0 "wep_key2", NVEE_LEN_N0_wep_key2)
NVPARAM_VARPARAM(NPRO_0 "wep_key3", NVEE_LEN_N0_wep_key3)
NVPARAM_PARAM(NPRO_0 "wep_tx_keyidx", INT32_LEN)
NVPARAM_VARPARAM(NPRO_0 "priority", NVEE_LEN_N0_priority)
NVPARAM_VARPARAM(NPRO_0 "eap_workaround", NVEE_LEN_N0_eap_workaround)
NVPARAM_VARPARAM(NPRO_0 "pac_file", NVEE_LEN_N0_pac_file)
NVPARAM_VARPARAM(NPRO_0 "fragment_size", NVEE_LEN_N0_fragment_size)
NVPARAM_VARPARAM(NPRO_0 "ocsp", NVEE_LEN_N0_ocsp)
NVPARAM_VARPARAM(NPRO_0 "sim_num", NVEE_LEN_N0_sim_num)
NVPARAM_VARPARAM(NPRO_0 "mode", NVEE_LEN_N0_mode)
NVPARAM_VARPARAM(NPRO_0 "no_auto_peer", NVEE_LEN_N0_no_auto_peer)
NVPARAM_VARPARAM(NPRO_0 "frequency", NVEE_LEN_N0_frequency)
NVPARAM_VARPARAM(NPRO_0 "fixed_freq", NVEE_LEN_N0_fixed_freq)
NVPARAM_VARPARAM(NPRO_0 "acs", NVEE_LEN_N0_acs)
NVPARAM_VARPARAM(NPRO_0 "proactive_key_caching", NVEE_LEN_N0_proactive_key_caching)
NVPARAM_PARAM(NPRO_0 "disabled", INT32_LEN)
NVPARAM_VARPARAM(NPRO_0 "pbss", NVEE_LEN_N0_pbss)
NVPARAM_VARPARAM(NPRO_0 "wps_disabled", NVEE_LEN_N0_wps_disabled)
NVPARAM_VARPARAM(NPRO_0 "fils_dh_group", NVEE_LEN_N0_fils_dh_group)
NVPARAM_VARPARAM(NPRO_0 "ieee80211w", NVEE_LEN_N0_ieee80211w)
NVPARAM_VARPARAM(NPRO_0 "id_str", NVEE_LEN_N0_id_str)
NVPARAM_VARPARAM(NPRO_0 "ignore_broadcast_ssid", NVEE_LEN_N0_ignore_broadcast_ssid)
NVPARAM_VARPARAM(NPRO_0 "dtim_period", NVEE_LEN_N0_dtim_period)
NVPARAM_VARPARAM(NPRO_0 "beacon_int", NVEE_LEN_N0_beacon_int)
NVPARAM_VARPARAM(NPRO_0 "isolate", NVEE_LEN_N0_isolate)
NVPARAM_VARPARAM(NPRO_0 "ap_max_inactivity", NVEE_LEN_N0_ap_max_inactivity)
NVPARAM_VARPARAM(NPRO_0 "ap_power", NVEE_LEN_N0_ap_power)                                         // auto, ...
NVPARAM_VARPARAM(NPRO_0 "update_identifier", NVEE_LEN_N0_update_identifier)
NVPARAM_VARPARAM(NPRO_0 "roaming_consortium_selection", NVEE_LEN_N0_roaming_consortium_selection) // MAX_ROAMING_CONS_OI_LEN
NVPARAM_VARPARAM(NPRO_0 "mac_addr", NVEE_LEN_N0_mac_addr)
NVPARAM_VARPARAM(NPRO_0 "mesh_basic_rates", NVEE_LEN_N0_mesh_basic_rates)
NVPARAM_VARPARAM(NPRO_0 "dot11MeshMaxRetries", NVEE_LEN_N0_dot11MeshMaxRetries)
NVPARAM_VARPARAM(NPRO_0 "dot11MeshRetryTimeout", NVEE_LEN_N0_dot11MeshRetryTimeout)
NVPARAM_VARPARAM(NPRO_0 "dot11MeshConfirmTimeout", NVEE_LEN_N0_dot11MeshConfirmTimeout)
NVPARAM_VARPARAM(NPRO_0 "dot11MeshHoldingTimeout", NVEE_LEN_N0_dot11MeshHoldingTimeout)
NVPARAM_VARPARAM(NPRO_0 "mesh_rssi_threshold", NVEE_LEN_N0_mesh_rssi_threshold)
NVPARAM_VARPARAM(NPRO_0 "wpa_ptk_rekey", NVEE_LEN_N0_wpa_ptk_rekey)
NVPARAM_VARPARAM(NPRO_0 "wpa_deny_ptk0_rekey", NVEE_LEN_N0_wpa_deny_ptk0_rekey)
NVPARAM_VARPARAM(NPRO_0 "group_rekey", NVEE_LEN_N0_group_rekey)
NVPARAM_VARPARAM(NPRO_0 "dpp_connector", NVEE_LEN_N0_dpp_connector)
NVPARAM_VARPARAM(NPRO_0 "dpp_netaccesskey", NVEE_LEN_N0_dpp_netaccesskey)
NVPARAM_VARPARAM(NPRO_0 "dpp_netaccesskey_expiry", NVEE_LEN_N0_dpp_netaccesskey_expiry)
NVPARAM_VARPARAM(NPRO_0 "dpp_csign", NVEE_LEN_N0_dpp_csign)
NVPARAM_VARPARAM(NPRO_0 "owe_group", NVEE_LEN_N0_owe_group)
NVPARAM_VARPARAM(NPRO_0 "owe_only", NVEE_LEN_N0_owe_only)
NVPARAM_VARPARAM(NPRO_0 "owe_ptk_workaround", NVEE_LEN_N0_owe_ptk_workaround)

NVPARAM_VARPARAM(NPRO_0 "multi_ap_backhaul_sta", NVEE_LEN_N0_multi_ap_backhaul_sta)
NVPARAM_VARPARAM(NPRO_0 "ft_eap_pmksa_caching", NVEE_LEN_N0_ft_eap_pmksa_caching)
NVPARAM_VARPARAM(NPRO_0 "beacon_prot", NVEE_LEN_N0_beacon_prot)
NVPARAM_VARPARAM(NPRO_0 "transition_disable", NVEE_LEN_N0_transition_disable)
NVPARAM_VARPARAM(NPRO_0 "sae_pk", NVEE_LEN_N0_sae_pk)
NVPARAM_VARPARAM(NPRO_0 "wifi_mode", NVEE_LEN_N0_wifi_mode)
NVPARAM_VARPARAM(NPRO_0 "mixed_cell", NVEE_LEN_N0_mixed_cell)
NVPARAM_VARPARAM(NPRO_0 "ht", NVEE_LEN_N0_ht)
NVPARAM_VARPARAM(NPRO_0 "ht40", NVEE_LEN_N0_ht40)
NVPARAM_VARPARAM(NPRO_0 "disable_ht", NVEE_LEN_N0_disable_ht)
NVPARAM_VARPARAM(NPRO_0 "disable_ht40", NVEE_LEN_N0_disable_ht40)
NVPARAM_VARPARAM(NPRO_0 "disable_sgi", NVEE_LEN_N0_disable_sgi)
NVPARAM_VARPARAM(NPRO_0 "disable_ldpc", NVEE_LEN_N0_disable_ldpc)
NVPARAM_VARPARAM(NPRO_0 "ht40_intolerant", NVEE_LEN_N0_ht40_intolerant)
NVPARAM_VARPARAM(NPRO_0 "tx_stbc", NVEE_LEN_N0_tx_stbc)
NVPARAM_VARPARAM(NPRO_0 "rx_stbc", NVEE_LEN_N0_rx_stbc)
NVPARAM_VARPARAM(NPRO_0 "disable_max_amsdu", NVEE_LEN_N0_disable_max_amsdu)
NVPARAM_VARPARAM(NPRO_0 "ampdu_factor", NVEE_LEN_N0_ampdu_factor)
NVPARAM_VARPARAM(NPRO_0 "ampdu_density", NVEE_LEN_N0_ampdu_density)
NVPARAM_VARPARAM(NPRO_0 "ht_mcs", NVEE_LEN_N0_ht_mcs)

NVPARAM_VARPARAM(NPRO_0 "max_oper_chwidth", NVEE_LEN_N0_max_oper_chwidth)
NVPARAM_VARPARAM(NPRO_0 "vht_center_freq1", NVEE_LEN_N0_vht_center_freq1)
NVPARAM_VARPARAM(NPRO_0 "vht_center_freq2", NVEE_LEN_N0_vht_center_freq2)

NVPARAM_VARPARAM(NPRO_0 "vht", NVEE_LEN_N0_vht)
NVPARAM_VARPARAM(NPRO_0 "disable_vht", NVEE_LEN_N0_disable_vht)
NVPARAM_VARPARAM(NPRO_0 "vht_capa", NVEE_LEN_N0_vht_capa)
NVPARAM_VARPARAM(NPRO_0 "vht_capa_mask", NVEE_LEN_N0_vht_capa_mask)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_1", NVEE_LEN_N0_vht_rx_mcs_nss_1)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_2", NVEE_LEN_N0_vht_rx_mcs_nss_2)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_3", NVEE_LEN_N0_vht_rx_mcs_nss_3)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_4", NVEE_LEN_N0_vht_rx_mcs_nss_4)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_5", NVEE_LEN_N0_vht_rx_mcs_nss_5)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_6", NVEE_LEN_N0_vht_rx_mcs_nss_6)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_7", NVEE_LEN_N0_vht_rx_mcs_nss_7)
NVPARAM_VARPARAM(NPRO_0 "vht_rx_mcs_nss_8", NVEE_LEN_N0_vht_rx_mcs_nss_8)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_1", NVEE_LEN_N0_vht_tx_mcs_nss_1)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_2", NVEE_LEN_N0_vht_tx_mcs_nss_2)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_3", NVEE_LEN_N0_vht_tx_mcs_nss_3)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_4", NVEE_LEN_N0_vht_tx_mcs_nss_4)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_5", NVEE_LEN_N0_vht_tx_mcs_nss_5)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_6", NVEE_LEN_N0_vht_tx_mcs_nss_6)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_7", NVEE_LEN_N0_vht_tx_mcs_nss_7)
NVPARAM_VARPARAM(NPRO_0 "vht_tx_mcs_nss_8", NVEE_LEN_N0_vht_tx_mcs_nss_8)

NVPARAM_VARPARAM(NPRO_0 "ca_cert", NVEE_LEN_N0_ca_cert)
NVPARAM_VARPARAM(NPRO_0 "ca_path", NVEE_LEN_N0_ca_path)
NVPARAM_VARPARAM(NPRO_0 "client_cert", NVEE_LEN_N0_client_cert)
NVPARAM_VARPARAM(NPRO_0 "private_key", NVEE_LEN_N0_private_key)
NVPARAM_VARPARAM(NPRO_0 "private_key_passwd", NVEE_LEN_N0_private_key_passwd)

NVPARAM_VARPARAM(NPRO_0 "dh_file", NVEE_LEN_N0_dh_file)
NVPARAM_VARPARAM(NPRO_0 "subject_match", NVEE_LEN_N0_subject_match)
NVPARAM_VARPARAM(NPRO_0 "altsubject_match", NVEE_LEN_N0_altsubject_match)
NVPARAM_VARPARAM(NPRO_0 "domain_suffix_match", NVEE_LEN_N0_domain_suffix_match)
NVPARAM_VARPARAM(NPRO_0 "domain_match", NVEE_LEN_N0_domain_match)
NVPARAM_VARPARAM(NPRO_0 "ca_cert2", NVEE_LEN_N0_ca_cert2)
NVPARAM_VARPARAM(NPRO_0 "ca_path2", NVEE_LEN_N0_ca_path2)
NVPARAM_VARPARAM(NPRO_0 "client_cert2", NVEE_LEN_N0_client_cert2)
NVPARAM_VARPARAM(NPRO_0 "private_key2", NVEE_LEN_N0_private_key2)
NVPARAM_VARPARAM(NPRO_0 "private_key2_passwd", NVEE_LEN_N0_private_key2_passwd)
NVPARAM_VARPARAM(NPRO_0 "dh_file2", NVEE_LEN_N0_dh_file2)
NVPARAM_VARPARAM(NPRO_0 "subject_match2", NVEE_LEN_N0_subject_match2)
NVPARAM_VARPARAM(NPRO_0 "altsubject_match2", NVEE_LEN_N0_altsubject_match2)
NVPARAM_VARPARAM(NPRO_0 "domain_suffix_match2", NVEE_LEN_N0_domain_suffix_match2)
NVPARAM_VARPARAM(NPRO_0 "domain_match2", NVEE_LEN_N0_domain_match2)

NVPARAM_VARPARAM(NPRO_0 "pcsc", NVEE_LEN_N0_pcsc)
NVPARAM_VARPARAM(NPRO_0 "pin", NVEE_LEN_N0_pin)
NVPARAM_VARPARAM(NPRO_0 "engine_id", NVEE_LEN_N0_engine_id)
NVPARAM_VARPARAM(NPRO_0 "key_id", NVEE_LEN_N0_key_id)
NVPARAM_VARPARAM(NPRO_0 "cert_id", NVEE_LEN_N0_cert_id)
NVPARAM_VARPARAM(NPRO_0 "ca_cert_id", NVEE_LEN_N0_ca_cert_id)
NVPARAM_VARPARAM(NPRO_0 "key2_id", NVEE_LEN_N0_key2_id)
NVPARAM_VARPARAM(NPRO_0 "pin2", NVEE_LEN_N0_pin2)
NVPARAM_VARPARAM(NPRO_0 "engine2_id", NVEE_LEN_N0_engine2_id)
NVPARAM_VARPARAM(NPRO_0 "cert2_id", NVEE_LEN_N0_cert2_id)
NVPARAM_VARPARAM(NPRO_0 "ca_cert2_id", NVEE_LEN_N0_ca_cert2_id)
NVPARAM_VARPARAM(NPRO_0 "engine", NVEE_LEN_N0_engine)
NVPARAM_VARPARAM(NPRO_0 "engine2", NVEE_LEN_N0_engine2)

NVPARAM_VARPARAM(NPRO_0 "openssl_ciphers", NVEE_LEN_N0_openssl_ciphers)
NVPARAM_VARPARAM(NPRO_0 "erp", NVEE_LEN_N0_erp)
NVPARAM_PARAM(NPRO_0 "FST_CONNECT", INT32_LEN)
NVPARAM_VARPARAM(NPRO_0 "ASSOC_CH", NVEE_LEN_N0_ASSOC_CH)

 #ifdef CONFIG_MACSEC
NVPARAM_VARPARAM(NPRO_0 "macsec_policy", NVEE_LEN_N0_macsec_policy)
NVPARAM_VARPARAM(NPRO_0 "macsec_integ_only", NVEE_LEN_N0_macsec_integ_only)
NVPARAM_VARPARAM(NPRO_0 "macsec_port", NVEE_LEN_N0_macsec_port)
NVPARAM_VARPARAM(NPRO_0 "mka_priority", NVEE_LEN_N0_mka_priority)
 #endif                                /* CONFIG_MACSEC */

//= ============================================================================
// Supplicant Network Profiles (N1_ : SOFTAP, P2P, MESH)
//= ============================================================================
NVPARAM_PARAM(NPRO_1 "Profile", INT32_LEN)
NVPARAM_VARPARAM(NPRO_1 "ssid", NVEE_LEN_N1_ssid)
NVPARAM_VARPARAM(NPRO_1 "scan_ssid", NVEE_LEN_N1_scan_ssid)
NVPARAM_VARPARAM(NPRO_1 "bssid", NVEE_LEN_N1_bssid)
NVPARAM_VARPARAM(NPRO_1 "bssid_hint", NVEE_LEN_N1_bssid_hint)
NVPARAM_VARPARAM(NPRO_1 "bssid_blacklist", NVEE_LEN_N1_bssid_blacklist)
NVPARAM_VARPARAM(NPRO_1 "bssid_whitelist", NVEE_LEN_N1_bssid_whitelist)
NVPARAM_VARPARAM(NPRO_1 "psk", NVEE_LEN_N1_psk)
NVPARAM_VARPARAM(NPRO_1 "mem_only_psk", NVEE_LEN_N1_mem_only_psk)
NVPARAM_VARPARAM(NPRO_1 "sae_password", NVEE_LEN_N1_sae_password)
NVPARAM_VARPARAM(NPRO_1 "sae_password_id", NVEE_LEN_N1_sae_password_id)
NVPARAM_VARPARAM(NPRO_1 "proto", NVEE_LEN_N1_proto)
NVPARAM_VARPARAM(NPRO_1 "key_mgmt", NVEE_LEN_N1_key_mgmt)
NVPARAM_VARPARAM(NPRO_1 "bg_scan_period", NVEE_LEN_N1_bg_scan_period)
NVPARAM_VARPARAM(NPRO_1 "pairwise", NVEE_LEN_N1_pairwise)
NVPARAM_VARPARAM(NPRO_1 "group", NVEE_LEN_N1_group)
NVPARAM_VARPARAM(NPRO_1 "group_mgmt", NVEE_LEN_N1_group_mgmt)
NVPARAM_VARPARAM(NPRO_1 "auth_alg", NVEE_LEN_N1_auth_alg)
NVPARAM_VARPARAM(NPRO_1 "bgscan", NVEE_LEN_N1_bgscan)
NVPARAM_VARPARAM(NPRO_1 "autoscan", NVEE_LEN_N1_autoscan)
NVPARAM_VARPARAM(NPRO_1 "scan_freq", NVEE_LEN_N1_scan_freq)
NVPARAM_VARPARAM(NPRO_1 "freq_list", NVEE_LEN_N1_freq_list)

NVPARAM_VARPARAM(NPRO_1 "eap", NVEE_LEN_N1_eap)
NVPARAM_VARPARAM(NPRO_1 "identity", NVEE_LEN_N1_identity)
NVPARAM_VARPARAM(NPRO_1 "anonymous_identity", NVEE_LEN_N1_anonymous_identity)
NVPARAM_VARPARAM(NPRO_1 "imsi_identity", NVEE_LEN_N1_imsi_identity)
NVPARAM_VARPARAM(NPRO_1 "password", NVEE_LEN_N1_password)
NVPARAM_VARPARAM(NPRO_1 "phase1", NVEE_LEN_N1_phase1)
NVPARAM_VARPARAM(NPRO_1 "phase2", NVEE_LEN_N1_phase2)
NVPARAM_VARPARAM(NPRO_1 "eapol_flags", NVEE_LEN_N1_eapol_flags)
NVPARAM_VARPARAM(NPRO_1 "wep_key0", NVEE_LEN_N1_wep_key0)
NVPARAM_VARPARAM(NPRO_1 "wep_key1", NVEE_LEN_N1_wep_key1)
NVPARAM_VARPARAM(NPRO_1 "wep_key2", NVEE_LEN_N1_wep_key2)
NVPARAM_VARPARAM(NPRO_1 "wep_key3", NVEE_LEN_N1_wep_key3)
NVPARAM_VARPARAM(NPRO_1 "wep_tx_keyidx", NVEE_LEN_N1_wep_tx_keyidx)
NVPARAM_VARPARAM(NPRO_1 "priority", NVEE_LEN_N1_priority)
NVPARAM_VARPARAM(NPRO_1 "eap_workaround", NVEE_LEN_N1_eap_workaround)
NVPARAM_VARPARAM(NPRO_1 "pac_file", NVEE_LEN_N1_pac_file)
NVPARAM_VARPARAM(NPRO_1 "fragment_size", NVEE_LEN_N1_fragment_size)
NVPARAM_VARPARAM(NPRO_1 "ocsp", NVEE_LEN_N1_ocsp)
NVPARAM_VARPARAM(NPRO_1 "sim_num", NVEE_LEN_N1_sim_num)
NVPARAM_PARAM(NPRO_1    "mode", INT32_LEN)
NVPARAM_VARPARAM(NPRO_1 "no_auto_peer", NVEE_LEN_N1_no_auto_peer)
NVPARAM_PARAM(NPRO_1    "frequency", INT32_LEN)
NVPARAM_VARPARAM(NPRO_1 "fixed_freq", NVEE_LEN_N1_fixed_freq)
NVPARAM_VARPARAM(NPRO_1 "acs", NVEE_LEN_N1_acs)
NVPARAM_VARPARAM(NPRO_1 "proactive_key_caching", NVEE_LEN_N1_proactive_key_caching)
NVPARAM_VARPARAM(NPRO_1 "disabled", NVEE_LEN_N1_disabled)
NVPARAM_VARPARAM(NPRO_1 "pbss", NVEE_LEN_N1_pbss)
NVPARAM_VARPARAM(NPRO_1 "wps_disabled", NVEE_LEN_N1_wps_disabled)
NVPARAM_VARPARAM(NPRO_1 "fils_dh_group", NVEE_LEN_N1_fils_dh_group)
NVPARAM_VARPARAM(NPRO_1 "ieee80211w", NVEE_LEN_N1_ieee80211w)
NVPARAM_VARPARAM(NPRO_1 "id_str", NVEE_LEN_N1_id_str)
NVPARAM_VARPARAM(NPRO_1 "ignore_broadcast_ssid", NVEE_LEN_N1_ignore_broadcast_ssid)
NVPARAM_VARPARAM(NPRO_1 "dtim_period", NVEE_LEN_N1_dtim_period)
NVPARAM_PARAM(NPRO_1 "beacon_int", INT32_LEN)
NVPARAM_VARPARAM(NPRO_1 "isolate", NVEE_LEN_N1_isolate)
NVPARAM_PARAM(NPRO_1 "ap_max_inactivity", INT32_LEN)
NVPARAM_VARPARAM(NPRO_1 "ap_power", NVEE_LEN_N1_ap_power)                                         // auto, ...
NVPARAM_VARPARAM(NPRO_1 "update_identifier", NVEE_LEN_N1_update_identifier)
NVPARAM_VARPARAM(NPRO_1 "roaming_consortium_selection", NVEE_LEN_N1_roaming_consortium_selection) // MAX_ROAMING_CONS_OI_LEN
NVPARAM_VARPARAM(NPRO_1 "mac_addr", NVEE_LEN_N1_mac_addr)
NVPARAM_VARPARAM(NPRO_1 "mesh_basic_rates", NVEE_LEN_N1_mesh_basic_rates)
NVPARAM_VARPARAM(NPRO_1 "dot11MeshMaxRetries", NVEE_LEN_N1_dot11MeshMaxRetries)
NVPARAM_VARPARAM(NPRO_1 "dot11MeshRetryTimeout", NVEE_LEN_N1_dot11MeshRetryTimeout)
NVPARAM_VARPARAM(NPRO_1 "dot11MeshConfirmTimeout", NVEE_LEN_N1_dot11MeshConfirmTimeout)
NVPARAM_VARPARAM(NPRO_1 "dot11MeshHoldingTimeout", NVEE_LEN_N1_dot11MeshHoldingTimeout)
NVPARAM_VARPARAM(NPRO_1 "mesh_rssi_threshold", NVEE_LEN_N1_mesh_rssi_threshold)
NVPARAM_VARPARAM(NPRO_1 "wpa_ptk_rekey", NVEE_LEN_N1_wpa_ptk_rekey)
NVPARAM_VARPARAM(NPRO_1 "wpa_deny_ptk0_rekey", NVEE_LEN_N1_wpa_deny_ptk0_rekey)

NVPARAM_VARPARAM(NPRO_1 "group_rekey", NVEE_LEN_N1_group_rekey)
NVPARAM_VARPARAM(NPRO_1 "dpp_connector", NVEE_LEN_N1_dpp_connector)
NVPARAM_VARPARAM(NPRO_1 "dpp_netaccesskey", NVEE_LEN_N1_dpp_netaccesskey)
NVPARAM_VARPARAM(NPRO_1 "dpp_netaccesskey_expiry", NVEE_LEN_N1_dpp_netaccesskey_expiry)
NVPARAM_VARPARAM(NPRO_1 "dpp_csign", NVEE_LEN_N1_dpp_csign)
NVPARAM_VARPARAM(NPRO_1 "owe_group", NVEE_LEN_N1_owe_group)
NVPARAM_VARPARAM(NPRO_1 "owe_only", NVEE_LEN_N1_owe_only)
NVPARAM_VARPARAM(NPRO_1 "owe_ptk_workaround", NVEE_LEN_N1_owe_ptk_workaround)
NVPARAM_VARPARAM(NPRO_1 "multi_ap_backhaul_sta", NVEE_LEN_N1_multi_ap_backhaul_sta)
NVPARAM_VARPARAM(NPRO_1 "ft_eap_pmksa_caching", NVEE_LEN_N1_ft_eap_pmksa_caching)
NVPARAM_VARPARAM(NPRO_1 "beacon_prot", NVEE_LEN_N1_beacon_prot)
NVPARAM_VARPARAM(NPRO_1 "transition_disable", NVEE_LEN_N1_transition_disable)
NVPARAM_VARPARAM(NPRO_1 "sae_pk", NVEE_LEN_N1_sae_pk)
NVPARAM_VARPARAM(NPRO_1 "wifi_mode", NVEE_LEN_N1_wifi_mode)
NVPARAM_VARPARAM(NPRO_1 "mixed_cell", NVEE_LEN_N1_mixed_cell)
NVPARAM_VARPARAM(NPRO_1 "ht", NVEE_LEN_N1_ht)
NVPARAM_VARPARAM(NPRO_1 "ht40", NVEE_LEN_N1_ht40)
NVPARAM_VARPARAM(NPRO_1 "disable_ht", NVEE_LEN_N1_disable_ht)
NVPARAM_VARPARAM(NPRO_1 "disable_ht40", NVEE_LEN_N1_disable_ht40)
NVPARAM_VARPARAM(NPRO_1 "disable_sgi", NVEE_LEN_N1_disable_sgi)
NVPARAM_VARPARAM(NPRO_1 "disable_ldpc", NVEE_LEN_N1_disable_ldpc)
NVPARAM_VARPARAM(NPRO_1 "ht40_intolerant", NVEE_LEN_N1_ht40_intolerant)
NVPARAM_VARPARAM(NPRO_1 "tx_stbc", NVEE_LEN_N1_tx_stbc)
NVPARAM_VARPARAM(NPRO_1 "rx_stbc", NVEE_LEN_N1_rx_stbc)
NVPARAM_VARPARAM(NPRO_1 "disable_max_amsdu", NVEE_LEN_N1_disable_max_amsdu)
NVPARAM_VARPARAM(NPRO_1 "ampdu_factor", NVEE_LEN_N1_ampdu_factor)
NVPARAM_VARPARAM(NPRO_1 "ampdu_density", NVEE_LEN_N1_ampdu_density)
NVPARAM_VARPARAM(NPRO_1 "ht_mcs", NVEE_LEN_N1_ht_mcs)

NVPARAM_VARPARAM(NPRO_1 "max_oper_chwidth", NVEE_LEN_N1_max_oper_chwidth)
NVPARAM_VARPARAM(NPRO_1 "vht_center_freq1", NVEE_LEN_N1_vht_center_freq1)
NVPARAM_VARPARAM(NPRO_1 "vht_center_freq2", NVEE_LEN_N1_vht_center_freq2)

NVPARAM_VARPARAM(NPRO_1 "vht", NVEE_LEN_N1_vht)
NVPARAM_VARPARAM(NPRO_1 "disable_vht", NVEE_LEN_N1_disable_vht)
NVPARAM_VARPARAM(NPRO_1 "vht_capa", NVEE_LEN_N1_vht_capa)
NVPARAM_VARPARAM(NPRO_1 "vht_capa_mask", NVEE_LEN_N1_vht_capa_mask)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_1", NVEE_LEN_N1_vht_rx_mcs_nss_1)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_2", NVEE_LEN_N1_vht_rx_mcs_nss_2)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_3", NVEE_LEN_N1_vht_rx_mcs_nss_3)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_4", NVEE_LEN_N1_vht_rx_mcs_nss_4)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_5", NVEE_LEN_N1_vht_rx_mcs_nss_5)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_6", NVEE_LEN_N1_vht_rx_mcs_nss_6)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_7", NVEE_LEN_N1_vht_rx_mcs_nss_7)
NVPARAM_VARPARAM(NPRO_1 "vht_rx_mcs_nss_8", NVEE_LEN_N1_vht_rx_mcs_nss_8)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_1", NVEE_LEN_N1_vht_tx_mcs_nss_1)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_2", NVEE_LEN_N1_vht_tx_mcs_nss_2)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_3", NVEE_LEN_N1_vht_tx_mcs_nss_3)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_4", NVEE_LEN_N1_vht_tx_mcs_nss_4)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_5", NVEE_LEN_N1_vht_tx_mcs_nss_5)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_6", NVEE_LEN_N1_vht_tx_mcs_nss_6)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_7", NVEE_LEN_N1_vht_tx_mcs_nss_7)
NVPARAM_VARPARAM(NPRO_1 "vht_tx_mcs_nss_8", NVEE_LEN_N1_vht_tx_mcs_nss_8)

NVPARAM_VARPARAM(NPRO_1 "ca_cert", NVEE_LEN_N1_ca_cert)
NVPARAM_VARPARAM(NPRO_1 "ca_path", NVEE_LEN_N1_ca_path)
NVPARAM_VARPARAM(NPRO_1 "client_cert", NVEE_LEN_N1_client_cert)
NVPARAM_VARPARAM(NPRO_1 "private_key", NVEE_LEN_N1_private_key)
NVPARAM_VARPARAM(NPRO_1 "private_key_passwd", NVEE_LEN_N1_private_key_passwd)

NVPARAM_VARPARAM(NPRO_1 "dh_file", NVEE_LEN_N1_dh_file)
NVPARAM_VARPARAM(NPRO_1 "subject_match", NVEE_LEN_N1_subject_match)
NVPARAM_VARPARAM(NPRO_1 "altsubject_match", NVEE_LEN_N1_altsubject_match)
NVPARAM_VARPARAM(NPRO_1 "domain_suffix_match", NVEE_LEN_N1_domain_suffix_match)
NVPARAM_VARPARAM(NPRO_1 "domain_match", NVEE_LEN_N1_domain_match)
NVPARAM_VARPARAM(NPRO_1 "ca_cert2", NVEE_LEN_N1_ca_cert2)
NVPARAM_VARPARAM(NPRO_1 "ca_path2", NVEE_LEN_N1_ca_path2)
NVPARAM_VARPARAM(NPRO_1 "client_cert2", NVEE_LEN_N1_client_cert2)
NVPARAM_VARPARAM(NPRO_1 "private_key2", NVEE_LEN_N1_private_key2)
NVPARAM_VARPARAM(NPRO_1 "private_key2_passwd", NVEE_LEN_N1_private_key2_passwd)
NVPARAM_VARPARAM(NPRO_1 "dh_file2", NVEE_LEN_N1_dh_file2)
NVPARAM_VARPARAM(NPRO_1 "subject_match2", NVEE_LEN_N1_subject_match2)
NVPARAM_VARPARAM(NPRO_1 "altsubject_match2", NVEE_LEN_N1_altsubject_match2)
NVPARAM_VARPARAM(NPRO_1 "domain_suffix_match2", NVEE_LEN_N1_domain_suffix_match2)
NVPARAM_VARPARAM(NPRO_1 "domain_match2", NVEE_LEN_N1_domain_match2)

NVPARAM_VARPARAM(NPRO_1 "pcsc", NVEE_LEN_N1_pcsc)
NVPARAM_VARPARAM(NPRO_1 "pin", NVEE_LEN_N1_pin)
NVPARAM_VARPARAM(NPRO_1 "engine_id", NVEE_LEN_N1_engine_id)
NVPARAM_VARPARAM(NPRO_1 "key_id", NVEE_LEN_N1_key_id)
NVPARAM_VARPARAM(NPRO_1 "cert_id", NVEE_LEN_N1_cert_id)
NVPARAM_VARPARAM(NPRO_1 "ca_cert_id", NVEE_LEN_N1_ca_cert_id)
NVPARAM_VARPARAM(NPRO_1 "key2_id", NVEE_LEN_N1_key2_id)
NVPARAM_VARPARAM(NPRO_1 "pin2", NVEE_LEN_N1_pin2)
NVPARAM_VARPARAM(NPRO_1 "engine2_id", NVEE_LEN_N1_engine2_id)
NVPARAM_VARPARAM(NPRO_1 "cert2_id", NVEE_LEN_N1_cert2_id)
NVPARAM_VARPARAM(NPRO_1 "ca_cert2_id", NVEE_LEN_N1_ca_cert2_id)
NVPARAM_VARPARAM(NPRO_1 "engine", NVEE_LEN_N1_engine)
NVPARAM_VARPARAM(NPRO_1 "engine2", NVEE_LEN_N1_engine2)

NVPARAM_VARPARAM(NPRO_1 "openssl_ciphers", NVEE_LEN_N1_openssl_ciphers)
NVPARAM_VARPARAM(NPRO_1 "erp", NVEE_LEN_N1_erp)

 #ifdef CONFIG_MACSEC
NVPARAM_VARPARAM(NPRO_1 "macsec_policy", NVEE_LEN_N1_macsec_policy)
NVPARAM_VARPARAM(NPRO_1 "macsec_integ_only", NVEE_LEN_N1_macsec_integ_only)
NVPARAM_VARPARAM(NPRO_1 "macsec_port", NVEE_LEN_N1_macsec_port)
NVPARAM_VARPARAM(NPRO_1 "mka_priority", NVEE_LEN_N1_mka_priority)
 #endif                                /* CONFIG_MACSEC */

//= ============================================================================
// Sleep Management(DPM) Profiles
//= ============================================================================
NVPARAM_PARAM(NVR_KEY_DPM_MODE, INT32_LEN)
NVPARAM_PARAM(NVR_KEY_DPM_KEEPALIVE_TIME, INT32_LEN)
NVPARAM_PARAM(NVR_KEY_DPM_USER_WAKEUP_TIME, INT32_LEN)
NVPARAM_PARAM(NVR_KEY_DPM_TIM_WAKEUP_TIME, INT32_LEN)
NVPARAM_PARAM(NVR_KEY_DPM_AB_WF_CONN_RETRY, INT32_LEN)
NVPARAM_PARAM(NVR_KEY_DPM_ABNORM_STOP, INT32_LEN)
NVPARAM_PARAM(NVR_KEY_DPM_IP_CONDITION, INT32_LEN)

NVPARAM_PARAM(WIFI_CONN_WAIT_NAME, INT32_LEN)
NVPARAM_PARAM(DHCP_RSP_WAIT_NAME, INT32_LEN)
NVPARAM_PARAM(ARP_RSP_WAIT_NAME, INT32_LEN)
NVPARAM_PARAM(UNKNOWN_DPM_FAIL_WAIT_NAME, INT32_LEN)

//= ============================================================================
// TWT (Target Wake Time) Profiles
//= ============================================================================
NVPARAM_PARAM("twt_auto_setup", UINT32_LEN)
NVPARAM_PARAM("twt_wake_int_mantissa", INT32_LEN)
NVPARAM_PARAM("twt_wake_int_exponent", INT32_LEN)
NVPARAM_PARAM("twt_wake_dur", UINT32_LEN)
NVPARAM_PARAM("twt_unannounced", UINT32_LEN)
NVPARAM_PARAM("twt_trigger_enable", UINT32_LEN)
NVPARAM_PARAM("twt_neg_type", UINT32_LEN)
NVPARAM_PARAM("twt_wake_dur_unit", UINT32_LEN)
NVPARAM_AREA_END()

// syscfg
//= ============================================================================
// syscfg : Network interface, etc
//= ============================================================================
NVPARAM_AREA(syscfg, NVMS_GENERIC_PART) // supplicant about 6332+a
// TAG-NAME,  MAX-LENGTH
NVPARAM_PARAM("INITWLAN", INT32_LEN)
NVPARAM_PARAM("SYSMODE", INT32_LEN)
NVPARAM_PARAM("SWITCH_SYSMODE", INT32_LEN)
NVPARAM_VARPARAM("0:MAC_SP", NVEE_LEN_0_MAC_SP)
NVPARAM_PARAM("0:NETMODE", INT32_LEN)
NVPARAM_VARPARAM("0:IP_Address", NVEE_LEN_0_IP_Address)
NVPARAM_VARPARAM("0:NETMASK", NVEE_LEN_0_NETMASK)
NVPARAM_VARPARAM("0:GATEWAY", NVEE_LEN_0_GATEWAY)
NVPARAM_VARPARAM("0:DNSSVR", NVEE_LEN_0_DNSSVR)
NVPARAM_VARPARAM("0:DNSSVR2", NVEE_LEN_0_DNSSVR2)
NVPARAM_PARAM("0:TEMP_STATIC_IP", INT32_LEN)

NVPARAM_PARAM("1:NETMODE", INT32_LEN)
NVPARAM_VARPARAM("1:IP_Address", NVEE_LEN_1_IP_Address)
NVPARAM_VARPARAM("1:NETMASK", NVEE_LEN_1_NETMASK)
NVPARAM_VARPARAM("1:GATEWAY", NVEE_LEN_1_GATEWAY)
NVPARAM_VARPARAM("1:DNSSVR", NVEE_LEN_1_DNSSVR)
NVPARAM_VARPARAM("1:DNSSVR2", NVEE_LEN_1_DNSSVR2)

/* DHCP Server */
NVPARAM_PARAM("USEDHCPD", INT32_LEN)
NVPARAM_VARPARAM("1:DHCPD_S_IP", NVEE_LEN_1_DHCP_SERVER_START_IP)
NVPARAM_VARPARAM("1:DHCPD_E_IP", NVEE_LEN_1_DHCP_SERVER_END_IP)
NVPARAM_PARAM("1:DHCPD_TIME", INT32_LEN)
NVPARAM_VARPARAM("1:DHCPD_DNS", NVEE_LEN_1_DHCP_SERVER_DNS)

NVPARAM_VARPARAM("1:DHCPV6D_S_IP", NVEE_LEN_1_DHCPV6_SERVER_START_IP)
NVPARAM_VARPARAM("1:DHCPV6D_E_IP", NVEE_LEN_1_DHCPV6_SERVER_END_IP)
NVPARAM_VARPARAM("1:DHCPV6D_DNS", NVEE_LEN_1_DHCPV6_SERVER_DNS)
NVPARAM_PARAM("1:DHCPV6D_TIME", INT32_LEN)

/* DHCP Client hostname */
NVPARAM_VARPARAM("DHCPC_HOSTNAME", NVEE_LEN_DHCPC_HOSTNAME)

/* Timezone */
NVPARAM_PARAM("TZONE", INT32_LEN)

/* SNTP Server */
NVPARAM_VARPARAM("SNTP_SVR", NVEE_LEN_SNTP_SERVER_DOMAIN)
NVPARAM_VARPARAM("SNTP_SVR_1", NVEE_LEN_SNTP_SERVER1_DOMAIN)
NVPARAM_VARPARAM("SNTP_SVR_2", NVEE_LEN_SNTP_SERVER2_DOMAIN)
NVPARAM_PARAM("SNTP_PERIOD", INT32_LEN)
NVPARAM_PARAM("SNTP_RUN_FLAG", INT32_LEN)

/* UART Config */
NVPARAM_PARAM("UART2_BAUDRATE", INT32_LEN)
NVPARAM_PARAM("UART2_BITS", INT32_LEN)
NVPARAM_PARAM("UART2_PARITY", INT32_LEN)
NVPARAM_PARAM("UART2_STOPBIT", INT32_LEN)
NVPARAM_PARAM("UART2_FLOWCTRL", INT32_LEN)

NVPARAM_PARAM("UART3_BAUDRATE", INT32_LEN)
NVPARAM_PARAM("UART3_BITS", INT32_LEN)
NVPARAM_PARAM("UART3_PARITY", INT32_LEN)
NVPARAM_PARAM("UART3_STOPBIT", INT32_LEN)
NVPARAM_VARPARAM("UART3_FLOWCTRL", NVEE_LEN_UART3_FLOWCTRL)
NVPARAM_AREA_END()

//= ============================================================================
// Applicantion
//= ============================================================================
NVPARAM_AREA(appcfg, NVMS_GENERIC_PART)

// TAG-NAME,  MAX-LENGTH
NVPARAM_PARAM("MQTT_TLS_NO_TIME_CHK", INT32_LEN)
NVPARAM_VARPARAM("MQTT_BROKER", NVEE_LEN_MQTT_BROKER)
NVPARAM_PARAM("MQTT_PORT", INT32_LEN)
NVPARAM_PARAM("MQTT_QOS", INT32_LEN)
NVPARAM_VARPARAM("MQTT_SUB_TOPIC", NVEE_LEN_MQTT_SUB_TOPIC)
NVPARAM_VARPARAM("MQTT_SUB_TOPIC0", NVEE_LEN_MQTT_SUB_TOPIC0)
NVPARAM_VARPARAM("MQTT_SUB_TOPIC1", NVEE_LEN_MQTT_SUB_TOPIC1)
NVPARAM_VARPARAM("MQTT_SUB_TOPIC2", NVEE_LEN_MQTT_SUB_TOPIC2)
NVPARAM_VARPARAM("MQTT_SUB_TOPIC3", NVEE_LEN_MQTT_SUB_TOPIC3)
NVPARAM_PARAM("MQTT_SUB_TOPIC_NUM", INT32_LEN)
NVPARAM_VARPARAM("MQTT_PUB_TOPIC", NVEE_LEN_MQTT_PUB_TOPIC)
NVPARAM_PARAM("MQTT_TLS", INT32_LEN)
NVPARAM_PARAM("MQTT_PING_PERIOD", INT32_LEN)
NVPARAM_PARAM("MQTT_AUTO", INT32_LEN)
NVPARAM_VARPARAM("MQTT_USERNAME", NVEE_LEN_MQTT_USERNAME)
NVPARAM_VARPARAM("MQTT_PASSWORD", NVEE_LEN_MQTT_PASSWORD)
NVPARAM_VARPARAM("MQTT_WILL_TOPIC", NVEE_LEN_MQTT_WILL_TOPIC)
NVPARAM_VARPARAM("MQTT_WILL_MSG", NVEE_LEN_MQTT_WILL_MSG)
NVPARAM_PARAM("MQTT_WILL_QOS", INT32_LEN)
NVPARAM_PARAM("MQTT_CLEAN_SESSION", INT32_LEN)
NVPARAM_PARAM("MQTT_VER311", INT32_LEN)
NVPARAM_VARPARAM("MQTT_SUB_CID", NVEE_LEN_MQTT_SUB_CID)
NVPARAM_VARPARAM("MQTT_PUB_CID", NVEE_LEN_MQTT_PUB_CID)
NVPARAM_PARAM("MQTT_TLS_ALPN_NUM", INT32_LEN)
NVPARAM_VARPARAM("MQTT_TLS_ALPN0", NVEE_LEN_MQTT_TLS_ALPN0)
NVPARAM_VARPARAM("MQTT_TLS_ALPN1", NVEE_LEN_MQTT_TLS_ALPN1)
NVPARAM_VARPARAM("MQTT_TLS_ALPN2", NVEE_LEN_MQTT_TLS_ALPN2)
NVPARAM_VARPARAM("MQTT_TLS_SNI", NVEE_LEN_MQTT_TLS_SNI)
NVPARAM_PARAM("MQTT_TLS_CSUIT_NUM", INT32_LEN)
NVPARAM_VARPARAM("MQTT_TLS_CSUIT", NVEE_LEN_MQTT_TLS_CSUIT)
NVPARAM_PARAM("MQTT_TLS_INCOMING", INT32_LEN)
NVPARAM_PARAM("MQTT_TLS_OUTGOING", INT32_LEN)
NVPARAM_PARAM("MQTT_TLS_AUTHMODE", INT32_LEN)
NVPARAM_PARAM("MQTT_TLS_VER", INT32_LEN)
NVPARAM_PARAM("MQTT_AT_MSG_FMT_VER", INT32_LEN)

/* HTTP Client */
NVPARAM_PARAM("HTTPC_TLS_VER", INT32_LEN)
NVPARAM_PARAM("HTTPC_TLS_AUTHMODE", INT32_LEN)
NVPARAM_PARAM("HTTPC_TLS_ALPN_NUM", INT32_LEN)
NVPARAM_VARPARAM("HTTPC_TLS_ALPN0", NVEE_LEN_HTTPC_TLS_ALPN0)
NVPARAM_VARPARAM("HTTPC_TLS_ALPN1", NVEE_LEN_HTTPC_TLS_ALPN1)
NVPARAM_VARPARAM("HTTPC_TLS_ALPN2", NVEE_LEN_HTTPC_TLS_ALPN2)
NVPARAM_VARPARAM("HTTPC_TLS_SNI", NVEE_LEN_HTTPC_TLS_SNI)

/* HTTP Server */
NVPARAM_PARAM("HTTPS_ENABLE", INT32_LEN)

/* OTA update */
NVPARAM_PARAM("OTA_TLS_VER", INT32_LEN)
NVPARAM_PARAM("OTA_TLS_AUTHMODE", INT32_LEN)
NVPARAM_PARAM("OTA_TLS_ALPN_NUM", INT32_LEN)
NVPARAM_VARPARAM("OTA_TLS_ALPN0", NVEE_LEN_OTA_TLS_ALPN0)
NVPARAM_VARPARAM("OTA_TLS_ALPN1", NVEE_LEN_OTA_TLS_ALPN1)
NVPARAM_VARPARAM("OTA_TLS_ALPN2", NVEE_LEN_OTA_TLS_ALPN2)
NVPARAM_VARPARAM("OTA_TLS_SNI", NVEE_LEN_OTA_TLS_SNI)
NVPARAM_PARAM("OTA_PROG_RTOS", INT32_LEN)
NVPARAM_PARAM("OTA_MODE", INT32_LEN)
NVPARAM_PARAM("OTA_EXPIRE", INT32_LEN)
NVPARAM_VARPARAM("OTA_URL", NVEE_LEN_URL)

/* BLE-COMBO : BLE Provisioning - provisioning status  */
NVPARAM_VARPARAM("provisioned", NVEE_LEN_BLE_COMBO_PROVISIONED)
NVPARAM_VARPARAM("SERVER_IP", NVEE_LEN_BLE_COMBO_PROV_SRV_IP)
NVPARAM_VARPARAM("SERVER_PORT", NVEE_LEN_BLE_COMBO_PROV_SRV_PORT)

/* BLE-COMBO : For Gas leak sample  */
NVPARAM_VARPARAM("sensor_started", NVEE_LEN_BLE_COMBO_SENSOR_STARTED)

/* BLE-COMBO : For Sensor gateway sample  */
NVPARAM_VARPARAM("UDP_SERVER_IP", NVEE_LEN_BLE_COMBO_SENSOR_GW_UDP_SVR_IP)
NVPARAM_VARPARAM("UDP_SERVER_PORT", NVEE_LEN_BLE_COMBO_SENSOR_GW_UDP_SVR_PORT)

/* BLE-COMBO : For TCPC DPM sample  */
NVPARAM_VARPARAM("TCPC_SERVER_IP", NVEE_LEN_BLE_COMBO_TCPC_SVR_IP)
NVPARAM_VARPARAM("TCPC_SERVER_PORT", NVEE_LEN_BLE_COMBO_TCPC_SVR_PORT)

/* BLE-COMBO : For OTA  */
NVPARAM_VARPARAM("URI_RTOS", NVEE_LEN_BLE_COMBO_OTA_URI_RTOS)
NVPARAM_VARPARAM("URI_BLE", NVEE_LEN_BLE_COMBO_OTA_URI_BLE)

/* ATCMD: TCP Server, Client, and UDP */
NVPARAM_PARAM("0:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("2:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("3:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("4:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("5:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("6:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("7:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("8:ATC_NW_TR_CID", INT32_LEN)
NVPARAM_PARAM("9:ATC_NW_TR_CID", INT32_LEN)

NVPARAM_PARAM("0:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("2:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("3:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("4:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("5:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("6:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("7:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("8:ATC_NW_TR_LPORT", INT32_LEN)
NVPARAM_PARAM("9:ATC_NW_TR_LPORT", INT32_LEN)

NVPARAM_PARAM("0:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("2:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("3:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("4:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("5:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("6:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("7:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("8:ATC_NW_TR_PPORT", INT32_LEN)
NVPARAM_PARAM("9:ATC_NW_TR_PPORT", INT32_LEN)

NVPARAM_PARAM("0:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("2:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("3:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("4:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("5:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("6:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("7:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("8:ATC_NW_TR_MAX_PEER", INT32_LEN)
NVPARAM_PARAM("9:ATC_NW_TR_MAX_PEER", INT32_LEN)

NVPARAM_VARPARAM("0:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("1:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("2:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("3:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("4:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("5:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("6:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("7:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("8:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)
NVPARAM_VARPARAM("9:ATC_NW_TR_PIPADDR", NVEE_LEN_ATC_NW_TR_PIPADDR)

NVPARAM_PARAM("0:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("2:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("3:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("4:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("5:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("6:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("7:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("8:ATC_NW_TR_IP_TYPE", INT32_LEN)
NVPARAM_PARAM("9:ATC_NW_TR_IP_TYPE", INT32_LEN)

/* ATCMD: TLS Client */
NVPARAM_PARAM("0:ATC_NW_TLS_CID", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLS_CID", INT32_LEN)
NVPARAM_PARAM("0:ATC_NW_TLS_ROLE", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLS_ROLE", INT32_LEN)
NVPARAM_PARAM("0:ATC_NW_TLS_PROFILE", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLS_PROFILE", INT32_LEN)
NVPARAM_VARPARAM("0:ATC_NW_TLSC_CA_NAME", NVEE_LEN_ATC_NW_TLSC_CA_CERT_NAME)
NVPARAM_VARPARAM("1:ATC_NW_TLSC_CA_NAME", NVEE_LEN_ATC_NW_TLSC_CA_CERT_NAME)
NVPARAM_VARPARAM("0:ATC_NW_TLSC_CERT_NAME", NVEE_LEN_ATC_NW_TLSC_CERT_NAME)
NVPARAM_VARPARAM("1:ATC_NW_TLSC_CERT_NAME", NVEE_LEN_ATC_NW_TLSC_CERT_NAME)
NVPARAM_VARPARAM("0:ATC_NW_TLSC_HOST_NAME", NVEE_LEN_ATC_NW_TLSC_HOST_NAME)
NVPARAM_VARPARAM("1:ATC_NW_TLSC_HOST_NAME", NVEE_LEN_ATC_NW_TLSC_HOST_NAME)
NVPARAM_PARAM("0:ATC_NW_TLSC_AUTH_MODE", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLSC_AUTH_MODE", INT32_LEN)
NVPARAM_PARAM("0:ATC_NW_TLSC_INCOMING", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLSC_INCOMING", INT32_LEN)
NVPARAM_PARAM("0:ATC_NW_TLSC_OUTGOING", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLSC_OUTGOING", INT32_LEN)
NVPARAM_PARAM("0:ATC_NW_TLSC_LPORT", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLSC_LPORT", INT32_LEN)
NVPARAM_PARAM("0:ATC_NW_TLSC_PPORT", INT32_LEN)
NVPARAM_PARAM("1:ATC_NW_TLSC_PPORT", INT32_LEN)
NVPARAM_VARPARAM("0:ATC_NW_TLSC_PIPADDR", NVEE_LEN_ATC_NW_TLSC_PIPADDR)
NVPARAM_VARPARAM("1:ATC_NW_TLSC_PIPADDR", NVEE_LEN_ATC_NW_TLSC_PIPADDR)

// Apps WiFi Provisioning for Mobile App.
NVPARAM_VARPARAM("APP_THINGNAME", NVEE_LEN_APP_APPTHINGNAME)

NVPARAM_PARAM("setsleepMode", INT32_LEN)
NVPARAM_PARAM("sleepmodertctime", INT32_LEN)

/* AWS IoT Application */
NVPARAM_VARPARAM(AWSIOT_CFG_THINGNAME, NVEE_LEN_AWSIOT_CFG_THINGNAME)
NVPARAM_VARPARAM(AWSIOT_CFG_FLEET_PROVISIONING_DEVICE_ID, NVEE_LEN_FLEET_PROVISIONING_DEVICE_ID)
NVPARAM_VARPARAM(AWSIOT_CFG_FLEET_PROVISIONING_TEMPLATE_NAME, NVEE_LEN_AWSIOT_CFG_FLEET_PROV_TEMPLATE_NAME)
NVPARAM_VARPARAM(AWSIOT_CFG_SAVED_IP_ADDRESS, NVEE_LEN_AWSIOT_CFG_SAVED_IP_ADDRESS)
NVPARAM_VARPARAM(AWSIOT_CFG_OTA_URL, NVEE_LEN_AWSIOT_CFG_OTA_URL)
NVPARAM_PARAM(AWSIOT_CFG_OTA_STATE, INT32_LEN)
NVPARAM_PARAM(AWSIOT_CFG_OTA_RESULT, INT32_LEN)
NVPARAM_PARAM(AWSIOT_CFG_OTA_FLAG, INT32_LEN)
NVPARAM_PARAM(AWSIOT_CFG_SLEEP_MODE2_RTC_TIME, INT32_LEN)
NVPARAM_VARPARAM(AWSIOT_CFG_FIRST_SNTP_TIME, NVEE_LEN_FIRST_SNTP_TIME)
NVPARAM_PARAM(AWSIOT_CFG_SNTP_SUCCESS_FLAG, UINT8_LEN)
NVPARAM_PARAM(AWSIOT_CFG_USE_FLEET_PROVISION, UINT8_LEN)
NVPARAM_VARPARAM(AWSIOT_CFG_BROKER_URL, NVEE_LEN_BROKER_URL)
NVPARAM_VARPARAM(AWSIOT_CFG_BOARD_FEATURE, NVEE_LEN_BOARD_FEATURE)
NVPARAM_PARAM(AWSIOT_CFG_LPORT, INT32_LEN)
NVPARAM_PARAM(AWSIOT_CFG_PORT, INT32_LEN)
NVPARAM_VARPARAM(AWSIOT_CFG_STOPIC, NVEE_LEN_STOPIC)
NVPARAM_VARPARAM(AWSIOT_CFG_PTOPIC, NVEE_LEN_PTOPIC)
NVPARAM_PARAM(AWSIOT_CFG_DPM_SLEEP_MODE, UINT8_LEN)
NVPARAM_PARAM(AWSIOT_CFG_USE_DPM, UINT8_LEN)
NVPARAM_PARAM(AWSIOT_CFG_RTC_TIME, INT32_LEN)
NVPARAM_PARAM(AWSIOT_CFG_DPM_KEEP_ALIVE_TIME, INT32_LEN)
NVPARAM_PARAM(AWSIOT_CFG_USER_WAKE_UP_TIME, INT32_LEN)
NVPARAM_PARAM(AWSIOT_CFG_TIM_WAKE_UP_TIME, INT32_LEN)
NVPARAM_VARPARAM(AWSIOT_CFG_MCU_WAKEUP_PORT, NVEE_LEN_MCU_WAKEUP_PORT)
NVPARAM_VARPARAM(AWSIOT_CFG_MCU_WAKEUP_PIN, NVEE_LEN_MCU_WAKEUP_PIN)
NVPARAM_PARAM(AWSIOT_CFG_PING_CHECK, UINT8_LEN)
NVPARAM_PARAM(AWSIOT_CFG_DPM_AUTO, UINT8_LEN)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_0, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_1, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_2, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_3, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_4, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_5, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_6, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_7, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_8, NVEE_LEN_THING_ATTRIBUTE)
NVPARAM_VARPARAM(AWSIOT_CFG_THING_ATTIRIBUTE_9, NVEE_LEN_THING_ATTRIBUTE)

/* Azure IOT Application */
NVPARAM_VARPARAM(APP_NVRAM_CONFIG_DEV_PRIMARY_KEY, NVEE_LEN_APP_NVRAM_CONFIG_DEV_PRIMARY_KEY)
NVPARAM_VARPARAM(APP_NVRAM_CONFIG_HOST_NAME, NVEE_LEN_APP_NVRAM_CONFIG_HOST_NAME)
NVPARAM_VARPARAM(APP_NVRAM_CONFIG_IOTHUB_CONN_STRING, NVEE_LEN_APP_NVRAM_CONFIG_IOTHUB_CONN_STRING)
NVPARAM_VARPARAM(APP_NVRAM_CONFIG_THINGNAME, NVEE_LEN_APP_NVRAM_CONFIG_THINGNAME)
NVPARAM_VARPARAM(APP_NVRAM_DEVICE_CONNECTION_STRING, NVEE_LEN_APP_NVRAM_DEVICE_CONNECTION_STRING)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_CURRENT_OTA_VERSION, NVEE_LEN_AZURE_NVRAM_CONFIG_CURRENT_OTA_VERSION)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_CURRENT_MCUOTA_VERSION, NVEE_LEN_AZURE_NVRAM_CONFIG_CURRENT_MCUOTA_VERSION)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_OTA_URL, NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_URL)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_OTA_VERSION, NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_VERSION)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_MCUOTA_VERSION, NVEE_LEN_AZURE_NVRAM_CONFIG_MCUOTA_VERSION)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_PORT, NVEE_LEN_AZURE_NVRAM_CONFIG_PORT)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_OTA_FLAG, NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_FLAG)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_OTA_STATE, NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_STATE)
NVPARAM_VARPARAM(AZURE_NVRAM_CONFIG_OTA_RESULT, NVEE_LEN_AZURE_NVRAM_CONFIG_OTA_RESULT)

/* TCP Client application */
NVPARAM_PARAM("TCPC_ACTIVE", NVEE_LEN_APP_TCPC_ACTIVE)
NVPARAM_VARPARAM("TCPC_PEER_IP_ADDR", NVEE_LEN_APP_TCPC_PEER_IP_ADDR)
NVPARAM_PARAM("TCPC_PEER_PORT", NVEE_LEN_APP_TCPC_PEER_PORT)
NVPARAM_PARAM("TCPC_SEND_PERIOD", NVEE_LEN_APP_TCPC_SEND_PERIOD)
NVPARAM_PARAM("TCPC_SEND_DATA_SIZE", NVEE_LEN_APP_TCPC_SEND_DATA_SIZE)
NVPARAM_PARAM("TCPC_AUTO_REST_EXIT", NVEE_LEN_APP_TCPC_AUTO_RESTART_AT_EXIT)
NVPARAM_PARAM("TCPC_KA_ENABLE", NVEE_LEN_APP_TCPC_KA_ENABLE)
NVPARAM_PARAM("TCPC_KA_IDLE_TIME", NVEE_LEN_APP_TCPC_KA_IDLE_TIME)
NVPARAM_PARAM("TCPC_KA_INTVL_TIME", NVEE_LEN_APP_TCPC_KA_INTVL_TIME)
NVPARAM_PARAM("TCPC_KA_MAX_PROBES", NVEE_LEN_APP_TCPC_KA_MAX_PROBES)

/* ATCMD: Wake up source status */
NVPARAM_PARAM("GPIO_WAKEUP_SOURCE_PIN", INT32_LEN)
NVPARAM_PARAM("GPIO_WAKEUP_SOURCE_EDGE_TYPE", INT32_LEN)
NVPARAM_AREA_END()

//= =============================================================================
// blecfg - for development BLE commands
//= =============================================================================
NVPARAM_AREA(blecfg, NVMS_GENERIC_PART)

/* Public BD address */
NVPARAM_VARPARAM("PUBLIC_BD_ADDR", NVEE_LEN_BLECFG_BD_ADDR)

NVPARAM_AREA_END()

//= =============================================================================
// blesec - for BLE Security
//= =============================================================================

NVPARAM_AREA(blesec, NVMS_GENERIC_PART)

/* Public BD address */
NVPARAM_PARAM("BOOT_DATA", NVEE_LEN_BLESEC_BOOT_DATA)
NVPARAM_PARAM("BONDING_DATA1", NVEE_LEN_BLESEC_BONDING_DATA)
NVPARAM_PARAM("BONDING_DATA2", NVEE_LEN_BLESEC_BONDING_DATA)
NVPARAM_PARAM("BONDING_DATA3", NVEE_LEN_BLESEC_BONDING_DATA)
NVPARAM_PARAM("BONDING_DATA4", NVEE_LEN_BLESEC_BONDING_DATA)
NVPARAM_PARAM("BONDING_DATA5", NVEE_LEN_BLESEC_BONDING_DATA)
NVPARAM_PARAM("BONDING_DATA6", NVEE_LEN_BLESEC_BONDING_DATA)
NVPARAM_PARAM("BONDING_DATA7", NVEE_LEN_BLESEC_BONDING_DATA)

// NVPARAM_PARAM("BDADDR2",                  NVEE_LEN_BLESEC_BONDING_DATA)
NVPARAM_AREA_END()

//= =============================================================================
// testcfg - for development test commands
//= =============================================================================
NVPARAM_AREA(testcfg, NVMS_GENERIC_PART)

// TAG-NAME, MAX-LENGTH

/* Tx Power debug */
NVPARAM_VARPARAM("DBG_TXPWR_L_2GO", NVEE_LEN_DBG_TXPWR_2G_OFDM)
NVPARAM_VARPARAM("DBG_TXPWR_L_2GD", NVEE_LEN_DBG_TXPWR_2G_DSSS)
NVPARAM_VARPARAM("DBG_TXPWR_L_5GP", NVEE_LEN_DBG_TXPWR_5G)
NVPARAM_VARPARAM("DBG_TXPWR_L_5GF", NVEE_LEN_DBG_TXPWR_5G_FLG)

NVPARAM_PARAM("ldpc", INT32_LEN)
NVPARAM_PARAM("stbc", INT32_LEN)

NVPARAM_VARPARAM("sku_id", STR_INT32_LEN)
NVPARAM_AREA_END()

NVPARAM_AREA(wifiprofile, NVMS_GENERIC_PART)
NVPARAM_VARPARAM(WIFI_PROFILE_COUNTRY_CODE, NVEE_LEN_WIFI_country_code)
NVPARAM_PARAM(WIFI_PROFILE_SYS_MODE, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_BAND, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_CHANNEL, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_WIFI_MODE, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_PMF, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_ENABLE_DPM, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_DPM_DEBUG_RUNTIME_FLAG, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_DPM_DPM_KEEPALIVE_TIME, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_DPM_USER_WAKEUP_TIME, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_DPM_TIM_WAKEUP_COUNT, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_DPM_BLE_HIBERNATE, INT32_LEN)
NVPARAM_VARPARAM(WIFI_PROFILE_SSID_0, NVEE_LEN_WIFI_ssid_0)
NVPARAM_VARPARAM(WIFI_PROFILE_SSID_1, NVEE_LEN_WIFI_ssid_1)
NVPARAM_PARAM(WIFI_PROFILE_HIDDEN_SSID, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_PMF_0, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_PMF_1, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_SECURITY_0, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_SECURITY_1, INT32_LEN)
NVPARAM_VARPARAM(WIFI_PROFILE_ENCKEY_0, NVEE_LEN_WIFI_password_0)
NVPARAM_VARPARAM(WIFI_PROFILE_ENCKEY_1, NVEE_LEN_WIFI_password_1)
NVPARAM_VARPARAM(WIFI_PROFILE_SAE_GROUPS_0, NVEE_LEN_sae_groups)
NVPARAM_VARPARAM(WIFI_PROFILE_SAE_GROUPS_1, NVEE_LEN_sae_groups)
NVPARAM_VARPARAM(WIFI_PROFILE_WEPKEY0_0, NVEE_LEN_WIFI_wep_key)
NVPARAM_PARAM(WIFI_PROFILE_WEPINDEX_0, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_WEPTYPE_0, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_EAP_AUTH_MODE, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_EAP_PHASE2, INT32_LEN)
NVPARAM_VARPARAM(WIFI_PROFILE_EAP_ID, NVEE_LEN_WIFI_eap_id)
NVPARAM_VARPARAM(WIFI_PROFILE_EAP_PW, NVEE_LEN_WIFI_eap_pw)
NVPARAM_PARAM(WIFI_PROFILE_P2P_SSID_POSTFIX, NVEE_LEN__WIFI_p2p_ssid_postfix)
NVPARAM_PARAM(WIFI_PROFILE_P2P_GROUP_IDLE, NVEE_LEN__WIFI_p2p_group_idle)
NVPARAM_PARAM(WIFI_PROFILE_P2P_LISTEN_CH, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_P2P_GO_INTENT, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_P2P_FIND_TIMEOUT, NVEE_LEN_WIFI_p2p_find_timeout)
NVPARAM_PARAM(WIFI_PROFILE_NETMODE_0, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_NETMODE_1, INT32_LEN)
NVPARAM_VARPARAM(WIFI_PROFILE_IPADDR_0, NVEE_LEN_WIFI_ipaddress_0)
NVPARAM_VARPARAM(WIFI_PROFILE_IPADDR_1, NVEE_LEN_WIFI_ipaddress_1)
NVPARAM_VARPARAM(WIFI_PROFILE_NETMASK_0, NVEE_LEN_WIFI_subnetmask_0)
NVPARAM_VARPARAM(WIFI_PROFILE_NETMASK_1, NVEE_LEN_WIFI_subnetmask_1)
NVPARAM_VARPARAM(WIFI_PROFILE_GATEWAY_0, NVEE_LEN_WIFI_gateway_0)
NVPARAM_VARPARAM(WIFI_PROFILE_GATEWAY_1, NVEE_LEN_WIFI_gateway_1)
NVPARAM_VARPARAM(WIFI_PROFILE_DNSSVR_0, NVEE_LEN_WIFI_dns_0)
NVPARAM_VARPARAM(WIFI_PROFILE_DNSSVR_1, NVEE_LEN_WIFI_dns_1)
NVPARAM_PARAM(WIFI_PROFILE_COMPLETE, INT32_LEN)
NVPARAM_VARPARAM(WIFI_PROFILE_DNSSVR_2ND_0, PARAM_IPADDR_LEN)
NVPARAM_VARPARAM(WIFI_PROFILE_DNSSVR_2ND_1, PARAM_IPADDR_LEN)
NVPARAM_PARAM(WIFI_PROFILE_AP_MAX_INACTIVITY_1, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_AP_WMM_PS_1, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_AP_WMM_1, INT32_LEN)
NVPARAM_PARAM(WIFI_PROFILE_SCAN_CHAN_NUM, INT32_LEN)
NVPARAM_VARPARAM(WIFI_PROFILE_SCAN_CHAN_LIST, NVEE_LEN_WIFI_chan_list)
NVPARAM_PARAM(WIFI_PROFILE_AP_ENC_MODE_1, INT32_LEN)
NVPARAM_AREA_END()
#endif                                 // (dg_configNVPARAM_ADAPTERv2 == 1)

#endif                                 /* PLATFORM_NVPARAM_H_ */

/**
 * \}
 * \}
 */
