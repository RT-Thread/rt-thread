/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BL_WIFI_H__
#define __BL_WIFI_H__
typedef struct bl_wifi_ap_info {
    uint8_t ssid[33];
    uint8_t psk[65];
    uint8_t chan;
} bl_wifi_ap_info_t;


int bl_wifi_enable_irq(void);
int bl_wifi_clock_enable(void);
int bl_wifi_sta_mac_addr_set(uint8_t mac[6]);
int bl_wifi_ap_mac_addr_set(uint8_t mac[6]);
int bl_wifi_mac_addr_set(uint8_t mac[6]);
int bl_wifi_country_code_set(uint8_t country_code);
int bl_wifi_ap_info_set(uint8_t* ssid, uint8_t ssid_len, 
                      uint8_t* psk, uint8_t psk_len,
                      uint8_t chan);
int bl_wifi_mac_addr_get(uint8_t mac[6]);
int bl_wifi_ap_info_get(bl_wifi_ap_info_t* ap_info);
int bl_wifi_sta_info_set(uint8_t* ssid, uint8_t ssid_len, uint8_t* psk, uint8_t psk_len, int autoconnect);
int bl_wifi_sta_info_get(bl_wifi_ap_info_t* sta_info);
#endif
