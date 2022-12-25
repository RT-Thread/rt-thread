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
#include <libfdt.h>

#include <utils_log.h>
// #include "log/log.h"

#define TC_WIFI_DTB_LEN    (4779 + 4)
extern const uint8_t tc_wifi_dtb[];

static int tc_fdt_wifi_module(void)
{
    const void *fdt = (const void *)tc_wifi_dtb;/* const tc_wifi_dtb */

    int wifi_offset = 0;
    int offset1 = 0;

    const uint32_t *addr_prop = 0;
    const char *result = 0;
    int lentmp = 0;
    int countindex = 0;
    int i;

    /* get wifi offset */
    wifi_offset = fdt_subnode_offset(fdt, 0, "wifi");
    // wifi
    if (!(wifi_offset > 0)) {
        log_error("wifi NULL.\r\n");
        return -1;
    }

    // wifi->region->country_code = u32
    offset1 = fdt_subnode_offset(fdt, wifi_offset, "region");
    if (offset1 > 0) {
        addr_prop = fdt_getprop(fdt, offset1, "country_code", &lentmp);
        if (addr_prop) {
            log_info("value = %ld, lentmp = %d\r\n", fdt32_to_cpu(*addr_prop), lentmp);
        } else {
            log_error("country_code NULL.\r\n");
            return -1;
        }
    }
    // wifi->mac
    offset1 = fdt_subnode_offset(fdt, wifi_offset, "mac");
    if (offset1 > 0) {
        // wifi->mac->sta_mac_addr = hex dump
        addr_prop = fdt_getprop(fdt, offset1, "sta_mac_addr", &lentmp);
        if (lentmp == 6) {
            uint8_t sta_mac[6];

            memcpy(sta_mac, addr_prop, 6);
            log_info("sta_mac :\r\n");
            log_buf(sta_mac, 6);
        } else {
            log_error("sta_mac_addr NULL.\r\n");
            return -1;
        }

        // wifi->mac->ap_mac_addr = hex dump
        addr_prop = fdt_getprop(fdt, offset1, "ap_mac_addr", &lentmp);
        if (lentmp == 6) {
            uint8_t ap_mac[6];

            memcpy(ap_mac, addr_prop, 6);
            log_info("ap_mac :\r\n");
            log_buf(ap_mac, 6);
        }
    }

    // wifi -> ap
    offset1 = fdt_subnode_offset(fdt, wifi_offset, "ap");
    if (offset1 > 0) {
        // wifi->ap->ssid = string
        countindex = fdt_stringlist_count(fdt, offset1, "ssid");
        if (countindex > 0) {
            for (i = 0; i < countindex; i++) {
                result = fdt_stringlist_get(fdt, offset1, "ssid", i, &lentmp);
                if (lentmp > 0) {/* !NULL */
                    log_info("ap string[%d] = %s, lentmp = %d\r\n", i, result, lentmp);
                }
            }
        } else {
            log_error("ap NULL.\r\n");
            return -1;
        }

        // wifi->ap->pwd = string
        countindex = fdt_stringlist_count(fdt, offset1, "pwd");
        if (countindex > 0) {
            for (i = 0; i < countindex; i++) {
                result = fdt_stringlist_get(fdt, offset1, "pwd", i, &lentmp);
                if (lentmp > 0) {/* !NULL */

                    log_info("pwd string[%d] = %s, lentmp = %d\r\n", i, result, lentmp);
                }
            }
        } else {
            log_error("pwd NULL.\r\n");
            return -1;
        }

        // wifi->ap->ap_channel = u32
        addr_prop = fdt_getprop(fdt, offset1, "ap_channel", &lentmp);
        if (addr_prop) {
            log_info("ap_channel = %ld\r\n", fdt32_to_cpu(*addr_prop));
        } else {
            log_error("ap_channel NULL.\r\n");
            return -1;
        }

        // wifi->ap->auto_chan_detect = dis ? en
        countindex = fdt_stringlist_count(fdt, offset1, "auto_chan_detect");
        if (countindex > 0) {
            for (i = 0; i < countindex; i++) {
                result = fdt_stringlist_get(fdt, offset1, "auto_chan_detect", i, &lentmp);
                if (lentmp > 0) {/* !NULL */
                    log_info("auto_chan_detect string[%d] = %s, lentmp = %d\r\n", i, result, lentmp);
                }
            }
        } else {
            log_error("auto_chan_detect NULL.\r\n");
            return -1;
        }
    } else {
        log_error("ap NULL.\r\n");
        return -1;
    }

    // wifi -> brd_rf
    offset1 = fdt_subnode_offset(fdt, wifi_offset, "brd_rf");
    if (offset1 > 0) {
        // wifi->brd_rf->xtal = u32 []
        addr_prop = fdt_getprop(fdt, offset1, "xtal", &lentmp);
        if (lentmp == 5*4) {
            uint8_t xtal[5*4];

            memcpy(xtal, addr_prop, 5*4);
            log_info("xtal :\r\n");
            log_buf(xtal, 5*4);
        } else {
            log_error("xtal NULL.");
            return -1;
        }
        // wifi->brd_rf->pwr_table = u32 []
        addr_prop = fdt_getprop(fdt, offset1, "pwr_table", &lentmp);
        if (lentmp == 16*4*4) {
            uint8_t pwr_table[16*4*4];

            memcpy(pwr_table, addr_prop, 16*4*4);
            log_info("pwr_table :\r\n");
            log_buf(pwr_table, 16*4*4);
        } else {
            log_error("pwr_table NULL. lentmp = %d.\r\n", lentmp);
            return -1;
        }
        // wifi->brd_rf->channel_div_table = u32 []
        addr_prop = fdt_getprop(fdt, offset1, "channel_div_table", &lentmp);
        if (lentmp == 15*4) {
            uint8_t channel_div_table[15*4];

            memcpy(channel_div_table, addr_prop, 15*4);
            log_info("channel_div_table :\r\n");
            log_buf(channel_div_table, 15*4);
        }  else {
            log_error("channel_div_table NULL.\r\n");
            return -1;
        }
        // wifi->brd_rf->channel_cnt_table = u32 []
        addr_prop = fdt_getprop(fdt, offset1, "channel_cnt_table", &lentmp);
        if (lentmp == 14*4) {
            uint8_t channel_cnt_table[14*4];

            memcpy(channel_cnt_table, addr_prop, 14*4);
            log_info("channel_cnt_table :\r\n");
            log_buf(channel_cnt_table, 14*4);
        }  else {
            log_error("channel_cnt_table NULL.\r\n");
            return -1;
        }
        // wifi->brd_rf->lo_fcal_div = u32
        addr_prop = fdt_getprop(fdt, offset1, "lo_fcal_div", &lentmp);
        if (lentmp == 1*4) {
            uint8_t lo_fcal_div[1*4];

            memcpy(lo_fcal_div, addr_prop, 1*4);
            log_info("lo_fcal_div :\r\n");
            log_buf(lo_fcal_div, 1*4);
        }  else {
            log_error("lo_fcal_div NULL.\r\n");
            return -1;
        }
    } else {
        log_error("brd_rf NULL.\r\n");
        return -1;
    }
    
    return 0;
}

int tc_fdt_wifi(void)
{
    int result;
    result = tc_fdt_wifi_module();
    
    if (result) {
        printf("fdt wifi module failed\r\n");
    } else {
        printf("fdt wifi module successed\r\n");
    }
    
    return result;
}
