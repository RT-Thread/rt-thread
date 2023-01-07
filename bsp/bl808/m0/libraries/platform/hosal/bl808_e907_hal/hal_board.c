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
#include <stdint.h>
#include <stdio.h>
#include <bl_efuse.h>
#include <bl_wifi.h>
#include <hal_boot2.h>
#include <hal_sys.h>

#include <libfdt.h>

#include <blog.h>
BLOG_DECLARE(dts);
#include <utils_log.h>

#define USER_UNUSED(a) ((void)(a))

#define BL_FDT32_TO_U8(addr, byte_offset)   ((uint8_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))
#define BL_FDT32_TO_U16(addr, byte_offset)  ((uint16_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))
#define BL_FDT32_TO_U32(addr, byte_offset)  ((uint32_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))

static uint32_t factory_addr = 0;

//#ifndef FEATURE_WIFI_DISABLE
//#include <bl60x_fw_api.h>
//#include <bl_phy_api.h>

#ifdef CFG_BLE_ENABLE
#include "ble_lib_api.h"
#endif
static int update_mac_config_get_mac_from_dtb(const void *fdt, int offset1, uint8_t mac_addr[6])
{
    int lentmp;
    const uint8_t *addr_prop = 0;

    /* set sta_mac_addr ap_mac_addr */
    addr_prop = fdt_getprop(fdt, offset1, "sta_mac_addr", &lentmp);
    if (6 == lentmp) {

        memcpy(mac_addr, addr_prop, 6);
        blog_info("sta_mac_addr :\r\n");
        blog_buf(mac_addr, 6);

        bl_wifi_sta_mac_addr_set(mac_addr);
    } else {
        blog_error("sta_mac_addr NULL.\r\n");
        return -1;
    }

    addr_prop = fdt_getprop(fdt, offset1, "ap_mac_addr", &lentmp);
    if (6 == lentmp) {

        memcpy(mac_addr, addr_prop, 6);
        blog_info("ap_mac_addr :\r\n");
        blog_buf(mac_addr, 6);

        bl_wifi_ap_mac_addr_set(mac_addr);
    } else {
        blog_error("ap_mac_addr NULL.\r\n");
        return -1;
    }
    blog_info("return 0000 \r\n");

    return 0;
}

static int update_mac_config_get_mac_from_efuse(uint8_t mac_addr[6])
{
    uint8_t result_or, result_and;

    bl_efuse_read_mac(mac_addr);
    result_or = mac_addr[0] | mac_addr[1] | mac_addr[2] | mac_addr[3] | mac_addr[4] | mac_addr[5];
    result_and = mac_addr[0] & mac_addr[1] & mac_addr[2] & mac_addr[3] & mac_addr[4] & mac_addr[5];

    if (0 == result_or || 1 == result_and) {
        /*all zero or one found in efuse*/
        return -1;
    }
    return 0;
}

static int update_mac_config_get_mac_from_factory(uint8_t mac_addr[6])
{
    uint8_t result_or, result_and;

    if (bl_efuse_read_mac_factory(mac_addr)) {
        return -1;
    }
    result_or = mac_addr[0] | mac_addr[1] | mac_addr[2] | mac_addr[3] | mac_addr[4] | mac_addr[5];
    result_and = mac_addr[0] & mac_addr[1] & mac_addr[2] & mac_addr[3] & mac_addr[4] & mac_addr[5];
    if (0 == result_or || 1 == result_and) {
        /*all zero or one found in efuse*/
        return -1;
    }
    return 0;
}

/*
 * Update MAC address according to order string
 * BFM:
 *  'B' for EFUSE built-in MAC address
 *  'F' for Flash built-in MAC address
 *  'M' for manufacutre configured EFUSE built-in MAC address
 * */
#define MAC_ORDER_ADDR_LEN_MAX      (3)
static void update_mac_config_with_order(const void *fdt, int offset1, const char *order)
{
    int i, set, len;
    uint8_t mac_addr[6];
    static const uint8_t mac_default[] = {0x18, 0xB9, 0x05, 0x88, 0x88, 0x88};

    set = 0;
    len = strlen(order);
    for (i = 0; i < MAC_ORDER_ADDR_LEN_MAX && i < len; i++) {
        switch (order[i]) {
            case 'B':
            {
                if (0 == update_mac_config_get_mac_from_efuse(mac_addr)) {
                    set = 1;
                    blog_info("get MAC from B ready\r\n");
                    goto break_scan;
                } else {
                    blog_info("get MAC from B failed\r\n");
                }
            }
            break;
            case 'F':
            {
                if (0 == update_mac_config_get_mac_from_dtb(fdt, offset1, mac_addr)) {
                    set = 1;
                    printf("get MAC from F ready\r\n");
                    goto break_scan;
                } else {
                    printf("get MAC from F failed\r\n");
                }
            }
            break;
            case 'M':
            {
                if (0 == update_mac_config_get_mac_from_factory(mac_addr)) {
                    set = 1;
                    blog_info("get MAC from M ready\r\n");
                    goto break_scan;
                } else {
                    blog_info("get MAC from M failed\r\n");
                }
            }
            break;
            default:
            {
                BL_ASSERT(0);
            }
        }
    }
break_scan:
    if (0 == set) {
        blog_info("Using Default MAC address\r\n");
        memcpy(mac_addr, mac_default, 6);
    }
    //FIXME maybe we should set a different MAC address
    blog_info("Set MAC addrress %02X:%02X:%02X:%02X:%02X:%02X\r\n",
            mac_addr[0],
            mac_addr[1],
            mac_addr[2],
            mac_addr[3],
            mac_addr[4],
            mac_addr[5]
    );
    bl_wifi_ap_mac_addr_set(mac_addr);
    bl_wifi_sta_mac_addr_set(mac_addr);
}

static void update_mac_config(const void *fdt, int offset1)
{
    int countindex = 0, lentmp = 0;
    const char *result = 0;
    char mac_mode[4];

    countindex = fdt_stringlist_count(fdt, offset1, "mode");
    if (1 == countindex) {
        result = fdt_stringlist_get(fdt, offset1, "mode", 0, &lentmp);
        blog_info_user(dts, "MAC address mode length %d\r\n", lentmp);
        if (lentmp <= MAC_ORDER_ADDR_LEN_MAX) {
            memcpy(mac_mode, result, lentmp);
            mac_mode[3] = '\0';
            blog_info_user(dts, "MAC address mode is %s\r\n", mac_mode);
            update_mac_config_with_order(fdt, offset1, mac_mode);
        }
    }
}


static int update_xtal_config_get_mac_from_factory(uint32_t capcode[5])
{
    uint8_t capcode_efuse = 0;

    if (bl_efuse_read_capcode(&capcode_efuse)) {
        return -1;
    }
    /*efuse only have one capcode entry, so we fill the left with hardcode*/
    capcode[0] = capcode_efuse;
    capcode[1] = capcode_efuse;
    capcode[2] = 1;
    capcode[3] = 60;
    capcode[4] = 60;

    return 0;
}

static int update_xtal_config_get_mac_from_dtb(const void *fdt, int offset1, uint32_t capcode[5])
{
    const uint8_t *addr_prop = 0;
    int lentmp = 0;

    addr_prop = fdt_getprop(fdt, offset1, "xtal", &lentmp);

    if (5*4 == lentmp) {
        blog_info(
            "xtal dtb in DEC :%u %u %u %u %u\r\n",
            BL_FDT32_TO_U8(addr_prop, 4*0),
            BL_FDT32_TO_U8(addr_prop, 4*1),
            BL_FDT32_TO_U8(addr_prop, 4*2),
            BL_FDT32_TO_U8(addr_prop, 4*3),
            BL_FDT32_TO_U8(addr_prop, 4*4)
        );
        capcode[0] = BL_FDT32_TO_U8(addr_prop, 4*0);
        capcode[1] = BL_FDT32_TO_U8(addr_prop, 4*1);
        capcode[2] = BL_FDT32_TO_U8(addr_prop, 4*2);
        capcode[3] = BL_FDT32_TO_U8(addr_prop, 4*3);
        capcode[4] = BL_FDT32_TO_U8(addr_prop, 4*4);
    } else {
        blog_error("xtal dtb NULL.");
        return -1;
    }
    return 0;
}

#define XTAL_ORDER_ADDR_LEN_MAX      (2)
static void update_xtal_config_with_order(const void *fdt, int offset1, const char *order)
{
    int i, set, len;
    uint32_t capcode[5];

    set = 0;
    len = strlen(order);
    for (i = 0; i < XTAL_ORDER_ADDR_LEN_MAX && i < len; i++) {
        switch (order[i]) {
            case 'F':
            {
                if (0 == update_xtal_config_get_mac_from_dtb(fdt, offset1, capcode)) {
                    set = 1;
                    blog_info("get xtal from F ready\r\n");
                    goto break_scan;
                } else {
                    blog_info("get xtal from F failed\r\n");
                }
            }
            break;
            case 'M':
            {
                if (0 == update_xtal_config_get_mac_from_factory(capcode)) {
                    set = 1;
                    blog_info("get xtal from M ready\r\n");
                    goto break_scan;
                } else {
                    blog_info("get xtal from M failed\r\n");
                }
            }
            break;
            default:
            {
                BL_ASSERT(0);
            }
        }
    }
break_scan:
    if (0 == set) {
        blog_info("Using Default xtal\r\n");
        capcode[0] = 50;
        capcode[1] = 50;
        capcode[2] = 1;
        capcode[3] = 60;
        capcode[4] = 60;
    }
    hal_sys_capcode_update(capcode[0], capcode[1]);
}

static void update_xtal_config(const void *fdt, int offset1)
{
    int lentmp = 0, countindex;
    char xtal_mode[3];
    const char *result = 0;

    countindex = fdt_stringlist_count(fdt, offset1, "xtal_mode");
    if (1 == countindex) {
        result = fdt_stringlist_get(fdt, offset1, "xtal_mode", 0, &lentmp);
        blog_info("xtal_mode length %d\r\n", lentmp);
        if (lentmp <= XTAL_ORDER_ADDR_LEN_MAX) {
            memcpy(xtal_mode, result, lentmp);
            xtal_mode[sizeof(xtal_mode) - 1] = '\0';
            blog_info("xtal_mode is %s\r\n", xtal_mode);
            update_xtal_config_with_order(fdt, offset1, xtal_mode);
        }
    }
}
#if 0
static void update_xtal_config_rftv(uint32_t tlv_addr)
{
    int i, set, len;
    uint8_t buffer[20] = {0};
    uint32_t capcode[5] = {0};
    char xtal_mode[3] = {0};
    
    if (rftlv_get(tlv_addr, RFTLV_API_TYPE_XTAL_MODE, 3, xtal_mode) > 0) {
        xtal_mode[sizeof(xtal_mode) - 1] = '\0';
        blog_info("xtal_mode is %s\r\n", xtal_mode);
    }

    set = 0;
    len = strlen(xtal_mode);
    for (i = 0; i < XTAL_ORDER_ADDR_LEN_MAX && i < len; i++) {
        switch (xtal_mode[i]) {
            case 'F':
            {
                if (rftlv_get(tlv_addr, RFTLV_API_TYPE_XTAL, sizeof(buffer), buffer) > 0) {
                    capcode[0] = *(uint32_t *)buffer;
                    capcode[1] = *(uint32_t *)(buffer + 4);
                    capcode[2] = *(uint32_t *)(buffer + 8);
                    capcode[3] = *(uint32_t *)(buffer + 12);
                    capcode[4] = *(uint32_t *)(buffer + 16);
                    set = 1;
                    blog_info("get xtal from F ready %d %d %d %d %d\r\n",
                            capcode[0],
                            capcode[1],
                            capcode[2],
                            capcode[3],
                            capcode[4]);
                    goto break_scan;
                } else {
                    blog_info("get xtal from F failed\r\n");
                }
            }
            break;
            case 'M':
            {
                if (0 == update_xtal_config_get_mac_from_factory(capcode)) {
                    set = 1;
                    blog_info("get xtal from M ready %d %d %d %d %d\r\n",
                            capcode[0],
                            capcode[1],
                            capcode[2],
                            capcode[3],
                            capcode[4]);
                    goto break_scan;
                } else {
                    blog_info("get xtal from M failed\r\n");
                }
            }
            break;
            default:
            {
                BL_ASSERT(0);
            }
        }
    }
break_scan:
    if (0 == set) {
        blog_info("Using Default xtal\r\n");
        capcode[0] = 50;
        capcode[1] = 50;
        capcode[2] = 1;
        capcode[3] = 60;
        capcode[4] = 60;
    }
    hal_sys_capcode_update(capcode[0], capcode[1]);
}
#endif
static int update_poweroffset_config_get_mac_from_dtb(const void *fdt, int offset1, int8_t poweroffset[14])
{
    int lentmp = 0, i;
    const uint8_t *addr_prop = 0;

#define PWR_OFFSET_BASE (10)
    addr_prop = fdt_getprop(fdt, offset1, "pwr_offset", &lentmp);
    if (14*4 == lentmp) {
        for (i = 0; i < 14; i++) {
            poweroffset[i] = BL_FDT32_TO_U32(addr_prop, 4*i);
        }
        blog_info("pwr_offset from dtb:\r\n");
        blog_buf(poweroffset, 14);
        for (i = 0; i < 14; i++) {
            poweroffset[i] -= PWR_OFFSET_BASE;
            poweroffset[i] = poweroffset[i] * 4;
        }
        blog_info("pwr_offset from dtb (rebase on %d):\r\n", PWR_OFFSET_BASE);
        //TODO FIXME log buffer
        //blog_buf_int8(poweroffset, 14);
    }  else {
        blog_error("pwr_offset NULL. lentmp = %d\r\n", lentmp);
        return -1;
    }
    return 0;
}

static void update_poweroffset_config_with_order(const void *fdt, int offset1, const char *order)
{
    int i, set, len, j;
    int8_t poweroffset[14], poweroffset_tmp[14];

    memset(poweroffset, 0, sizeof(poweroffset));
    memset(poweroffset_tmp, 0, sizeof(poweroffset_tmp));
    set = 0;
    len = strlen(order);
    for (i = 0; i < XTAL_ORDER_ADDR_LEN_MAX && i < len; i++) {
        switch (order[i]) {
            case 'B':
            case 'b':
            {
                if (0 == bl_efuse_read_pwroft(poweroffset_tmp)) {
                    set = 1;
                    blog_info("get pwr offset from B(b) ready\r\n");
                    log_buf_int8(poweroffset_tmp, sizeof(poweroffset_tmp));
                    if ('B' == order[i]) {
                        /*non-incremental mode*/
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] = poweroffset_tmp[j];
                        }
                        blog_info("Use pwr offset from B only\r\n");
                        goto break_scan;
                    } else {
                        /*incremental mode*/
                        blog_info("Use pwr offset from b in incremental mode\r\n");
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] += poweroffset_tmp[j];
                        }
                    }
                } else {
                    blog_info("get pwr offset from B(b) failed\r\n");
                }
            }
            break;
            case 'F':
            case 'f':
            {
                if (0 == update_poweroffset_config_get_mac_from_dtb(fdt, offset1, poweroffset_tmp)) {
                    set = 1;
                    blog_info("get pwr offset from F(f) ready\r\n");
                    if ('B' == order[i]) {
                        /*non-incremental mode*/
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] = poweroffset_tmp[j];
                        }
                        blog_info("Use pwr offset from F only\r\n");
                        goto break_scan;
                    } else {
                        /*incremental mode*/
                        blog_info("Use pwr offset from f in incremental mode\r\n");
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] += poweroffset_tmp[j];
                        }
                    }
                    goto break_scan;
                } else {
                    blog_info("get pwr offset from F(f) failed\r\n");
                }
            }
            break;
            default:
            {
                BL_ASSERT(0);
            }
        }
    }
break_scan:
    if (0 == set) {
        blog_info("Using Default pwr offset\r\n");//all zeros actually
    }
    log_buf_int8(poweroffset, sizeof(poweroffset));
#ifdef CFG_BLE_ENABLE
    extern void ble_rf_set_pwr_offset_table(int8_t *poweroffset_table);
	ble_rf_set_pwr_offset_table(poweroffset);
#endif
   //zys phy_powroffset_set(poweroffset);
}


#define PWR_OFFSET_ORDER_ADDR_LEN_MAX      (2)
static void update_poweroffset_config(const void *fdt, int offset1)
{
    int lentmp = 0, countindex;
    char pwr_mode[3];
    const char *result = 0;

    countindex = fdt_stringlist_count(fdt, offset1, "pwr_mode");
    if (1 == countindex) {
        result = fdt_stringlist_get(fdt, offset1, "pwr_mode", 0, &lentmp);
        blog_info("pwr_mode length %d\r\n", lentmp);
        if (lentmp <= PWR_OFFSET_ORDER_ADDR_LEN_MAX) {
            memcpy(pwr_mode, result, lentmp);
            pwr_mode[sizeof(pwr_mode) - 1] = '\0';
            blog_info("pwr_mode is %s\r\n", pwr_mode);
            update_poweroffset_config_with_order(fdt, offset1, pwr_mode);
        }
    }
}
#if 0
zys
static void update_poweroffset_config_rftv(uint32_t tlv_addr, const char *pw_mode)
{
    int i, set, len, j;
    int8_t poweroffset[14], poweroffset_tmp[14];

    memset(poweroffset, 0, sizeof(poweroffset));
    memset(poweroffset_tmp, 0, sizeof(poweroffset_tmp));
    set = 0;
    len = strlen(pw_mode);
    for (i = 0; i < XTAL_ORDER_ADDR_LEN_MAX && i < len; i++) {
        switch (pw_mode[i]) {
            case 'B':
            case 'b':
            {
                if (0 == bl_efuse_read_pwroft(poweroffset_tmp)) {
                    set = 1;
                    blog_info("get pwr offset from B(b) ready\r\n");
                    log_buf_int8(poweroffset_tmp, sizeof(poweroffset_tmp));
                    if ('B' == pw_mode[i]) {
                        /*non-incremental mode*/
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] = poweroffset_tmp[j];
                        }
                        blog_info("Use pwr offset from B only\r\n");
                        goto break_scan;
                    } else {
                        /*incremental mode*/
                        blog_info("Use pwr offset from b in incremental mode\r\n");
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] += poweroffset_tmp[j];
                        }
                    }
                } else {
                    blog_info("get pwr offset from B(b) failed\r\n");
                }
            }
            break;
            case 'F':
            case 'f':
            {
                if (rftlv_get(tlv_addr, RFTLV_TYPE_PWR_OFFSET, sizeof(poweroffset_tmp), poweroffset_tmp) > 0) {
                    set = 1;
                    blog_info("get pwr offset from F(f) ready\r\n");
                    if ('F' == pw_mode[i]) {
                        /*non-incremental mode*/
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] = (poweroffset_tmp[j] - 10)*4;
                        }
                        blog_info("Use pwr offset from F only\r\n");
                        goto break_scan;
                    } else {
                        /*incremental mode*/
                        blog_info("Use pwr offset from f in incremental mode\r\n");
                        for (j = 0; j < sizeof(poweroffset); j++) {
                            poweroffset[j] = (poweroffset_tmp[j] - 10)*4;
                        }
                    }
                    goto break_scan;
                } else {
                    blog_info("get pwr offset from F(f) failed\r\n");
                }
            }
            break;
            default:
            {
                BL_ASSERT(0);
            }
        }
    }
break_scan:
    if (0 == set) {
        blog_info("Using Default pwr offset\r\n");//all zeros actually
    }
    log_buf_int8(poweroffset, sizeof(poweroffset));
#ifdef CFG_BLE_ENABLE
    extern void ble_rf_set_pwr_offset_table(int8_t *poweroffset_table);
	ble_rf_set_pwr_offset_table(poweroffset);
#endif
  //zys phy_powroffset_set(poweroffset);
}
#endif
static int update_sta_field(const void *fdt, int wifi_offset, const char *name)
{
    int offset1 = 0;        /* subnode offset1 */
    int countindex = 0, lentmp = 0;
    const char *result = 0;
    const uint8_t *addr_prop = 0;
    int auto_connect_enable;

    /* set ssid pwd */
    uint8_t ap_ssid[32];
    uint8_t ap_ssid_len = 0;
    uint8_t ap_psk[64];
    uint8_t ap_psk_len = 0;

    offset1 = fdt_subnode_offset(fdt, wifi_offset, name);
    if (offset1 > 0) {

        countindex = fdt_stringlist_count(fdt, offset1, "ssid");
        if (1 == countindex) {
            result = fdt_stringlist_get(fdt, offset1, "ssid", 0, &lentmp);
            if ((lentmp > 0) &&(lentmp<32)) {/* !NULL */
                blog_info("[STA] ap_ssid string[%d] = %s, ap_ssid_len = %d\r\n", 0, result, lentmp);
                memcpy(ap_ssid, result, lentmp);
                ap_ssid[lentmp] = '\0';
                ap_ssid_len = lentmp;
            }
        }

        countindex = fdt_stringlist_count(fdt, offset1, "pwd");
        if (1 == countindex) {
            result = fdt_stringlist_get(fdt, offset1, "pwd", 0, &lentmp);
            if ((lentmp > 0) &&(lentmp<32)) {/* !NULL */
                blog_info("[STA] ap_psk string[%d] = %s, ap_psk_len = %d\r\n", 0, result, lentmp);
                memcpy(ap_psk, result, lentmp);
                ap_psk[lentmp] = '\0';
                ap_psk_len = lentmp;
            }
        }
        addr_prop = fdt_getprop(fdt, offset1, "auto_connect_enable", &lentmp);
        if (addr_prop) {
            blog_info("auto_connect_enable = %ld\r\n", BL_FDT32_TO_U32(addr_prop, 0));

            auto_connect_enable = BL_FDT32_TO_U32(addr_prop, 0);
        } else {
            auto_connect_enable = 0;
        }

        bl_wifi_sta_info_set(ap_ssid, ap_ssid_len, ap_psk, ap_psk_len, auto_connect_enable);
    }
    return offset1;
}

static int update_ap_field(const void *fdt, int wifi_offset, const char *name)
{
    int offset1 = 0;        /* subnode offset1 */
    int countindex = 0, lentmp = 0;
    const char *result = 0;
    const uint8_t *addr_prop = 0;
     
    /* set ssid pwd */
    uint8_t ap_ssid[32];
    uint8_t ap_ssid_len = 0;
    uint8_t ap_psk[64];
    uint8_t ap_psk_len = 0;
    uint8_t ap_channel = 0;

    offset1 = fdt_subnode_offset(fdt, wifi_offset, "ap");
    if (offset1 > 0)
    {
        countindex = fdt_stringlist_count(fdt, offset1, "ssid");
        if (1 == countindex) {
            result = fdt_stringlist_get(fdt, offset1, "ssid", 0, &lentmp);
            if ((lentmp > 0) &&(lentmp<32)) {/* !NULL */
                blog_info("ap_ssid string[%d] = %s, ap_ssid_len = %d\r\n", 0, result, lentmp);
                memcpy(ap_ssid, result, lentmp);
                ap_ssid[lentmp] = '\0';
                ap_ssid_len = lentmp;
            }
        }

        countindex = fdt_stringlist_count(fdt, offset1, "pwd");
        if (1 == countindex) {
            result = fdt_stringlist_get(fdt, offset1, "pwd", 0, &lentmp);
            if ((lentmp > 0) &&(lentmp<32)) {/* !NULL */
                blog_info("ap_psk string[%d] = %s, ap_psk_len = %d\r\n", 0, result, lentmp);
                memcpy(ap_psk, result, lentmp);
                ap_psk[lentmp] = '\0';
                ap_psk_len = lentmp;
            }
        }

        addr_prop = fdt_getprop(fdt, offset1, "ap_channel", &lentmp);
        if (addr_prop) {
            blog_info("ap_channel = %ld\r\n", BL_FDT32_TO_U32(addr_prop, 0));

            ap_channel = BL_FDT32_TO_U32(addr_prop, 0);
        } else {
            blog_error("ap_channel NULL.\r\n");
        }

        bl_wifi_ap_info_set(ap_ssid, ap_ssid_len,
                            ap_psk, ap_psk_len,
                            ap_channel);
    }
    return offset1;
}

typedef struct{
    uint16_t Tchannels[5];
    int16_t Tchannel_os[5];
    int16_t Tchannel_os_low[5];
    int16_t Troom_os;
    uint8_t en_tcal;
    uint8_t linear_or_follow;
} tcal_param_struct;
extern tcal_param_struct* tcal_param;
enum {
    E_RF_TCAL_UPDATE_PARAM = 0,
};
void rf_pri_update_tcal_param(uint8_t operation);//FIXME
#define TCAL_PARA_CHANNELS          5

static int update_rf_temp_field(const void *fdt, int wifi_offset, const char *name)
{
    int lentmp, i;
    int offset1 = 0;
    const uint8_t *addr_prop = 0;
    uint32_t tmp[TCAL_PARA_CHANNELS];
    tcal_param_struct tcal_param_tmp;

    offset1 = fdt_subnode_offset(fdt, wifi_offset, name);
    if (offset1 > 0) {
        addr_prop = fdt_getprop(fdt, offset1, "Troom_os", &lentmp);
        if (addr_prop) {
            tcal_param_tmp.Troom_os=BL_FDT32_TO_U32(addr_prop, 0)-256;
            blog_info_user(dts, "Troom_os = %d, lentmp = %d\r\n", (int)tcal_param_tmp.Troom_os, lentmp);
        } else {
            blog_info_user(dts, "Troom_os NULL.\r\n");
            return -1;
        }

        addr_prop = fdt_getprop(fdt, offset1, "linear_or_follow", &lentmp);
        if (addr_prop) {
            tcal_param_tmp.linear_or_follow=BL_FDT32_TO_U32(addr_prop, 0);
            blog_info_user(dts, "linear_or_follow = %d, lentmp = %d\r\n", (int)tcal_param_tmp.linear_or_follow, lentmp);
        } else {
            blog_info_user(dts, "linear_or_follow NULL.\r\n");
            return -1;
        }

        addr_prop = fdt_getprop(fdt, offset1, "Tchannels", &lentmp);
        if (lentmp == TCAL_PARA_CHANNELS*4) {            
            memcpy(tmp, addr_prop, TCAL_PARA_CHANNELS*4);         
            blog_info_user(dts, "Tchannels:");
            for (i = 0; i < TCAL_PARA_CHANNELS; i++){
                tcal_param_tmp.Tchannels[i]=fdt32_to_cpu(tmp[i]);
                blog_info_user_raw(dts, "%d,", (int)tcal_param_tmp.Tchannels[i]);
            }
            blog_info_user_raw(dts, "\r\n");
        } else {
            blog_info_user(dts, "Tchannels NULL.\r\n");
            return -1;
        }

        addr_prop = fdt_getprop(fdt, offset1, "Tchannel_os", &lentmp);
        if (lentmp == TCAL_PARA_CHANNELS*4) {            
            memcpy(tmp, addr_prop, TCAL_PARA_CHANNELS*4);         
            blog_info_user(dts, "Tchannel_os:");
            for (i = 0; i < TCAL_PARA_CHANNELS; i++){
                tcal_param_tmp.Tchannel_os[i]=fdt32_to_cpu(tmp[i]);
                blog_info_user_raw(dts, "%d,", (int)tcal_param_tmp.Tchannel_os[i]);
            }
            blog_info_user_raw(dts, "\r\b");
        } else {
            blog_info_user(dts, "Tchannel_os NULL.\r\n");
            return -1;
        }

        addr_prop = fdt_getprop(fdt, offset1, "Tchannel_os_low", &lentmp);
        if (lentmp == TCAL_PARA_CHANNELS*4) {            
            memcpy(tmp, addr_prop, TCAL_PARA_CHANNELS*4);         
            blog_info_user(dts, "Tchannel_os_low:");
            for (i = 0; i < TCAL_PARA_CHANNELS; i++){
                tcal_param_tmp.Tchannel_os_low[i]=fdt32_to_cpu(tmp[i]);
                blog_info_user_raw(dts, "%d,", (int)tcal_param_tmp.Tchannel_os_low[i]);
            }
            blog_info_user_raw(dts, "\r\n");
        } else {
            blog_info_user(dts, "Tchannel_os_low NULL.\r\n");
            return -1;
        }
        addr_prop = fdt_getprop(fdt, offset1, "en_tcal", &lentmp);
        if (addr_prop) {
            tcal_param_tmp.en_tcal=BL_FDT32_TO_U32(addr_prop, 0);
            blog_info_user(dts, "en_tcal = %u, lentmp = %d\r\n", tcal_param_tmp.en_tcal, lentmp);
        } else {
            blog_info_user(dts, "en_tcal NULL.\r\n");
            return -1;
        }
    }
    memcpy(tcal_param, &tcal_param_tmp, sizeof(tcal_param_tmp));
    rf_pri_update_tcal_param(E_RF_TCAL_UPDATE_PARAM);

    return 0;
}
#if 0
static int hal_board_load_rftv_info(uint32_t rftlv_addr)
{
    int i;
    uint8_t *p_buffer;

    /* set tx_pwr_tbl */
    int8_t pwr_table[24];

    int pwr_table_ble = 0;
 
    if (!rftlv_valid(rftlv_addr)) {
        return -2;
    }

    p_buffer = pvPortMalloc(80);
    if (p_buffer == NULL) {
        return -1;
    }

    /* set xtal */
    update_xtal_config_rftv(rftlv_addr);

    if (rftlv_get(rftlv_addr, RFTLV_API_TYPE_PWR_TABLE_11B, 80, p_buffer) > 0) {
        for (i = 0; i < 4; i++) {
            pwr_table[i] = *(int8_t *)(p_buffer + i);
        }
        blog_info("pwr_table_11b :%u %u %u %u\r\n",
            pwr_table[0],
            pwr_table[1],
            pwr_table[2],
            pwr_table[3]
        );
        bl_tpc_update_power_rate_11b((int8_t*)pwr_table);
    } else {
        blog_error("RFTLV_TYPE_PWR_TABLE_11B NULL\r\n");
    }
    if (rftlv_get(rftlv_addr, RFTLV_API_TYPE_PWR_TABLE_11G, 80, p_buffer) > 0) {
        for (i = 0; i < 8; i++) {
            pwr_table[i] = *(int8_t *)(p_buffer + i);
        }
        blog_info("pwr_table_11g :%u %u %u %u %u %u %u %u\r\n",
            pwr_table[0],
            pwr_table[1],
            pwr_table[2],
            pwr_table[3],
            pwr_table[4],
            pwr_table[5],
            pwr_table[6],
            pwr_table[7]
        );
        bl_tpc_update_power_rate_11g((int8_t*)pwr_table);
    } else {
        blog_error("RFTLV_TYPE_PWR_TABLE_11G NULL\r\n");
    }
    if (rftlv_get(rftlv_addr, RFTLV_API_TYPE_PWR_TABLE_11N, 80, p_buffer) > 0) {
        for (i = 0; i < 8; i++) {
            pwr_table[i] = *(int8_t *)(p_buffer + i);
        }
        blog_info("pwr_table_11n :%u %u %u %u %u %u %u %u\r\n",
            pwr_table[0],
            pwr_table[1],
            pwr_table[2],
            pwr_table[3],
            pwr_table[4],
            pwr_table[5],
            pwr_table[6],
            pwr_table[7]
        );
        bl_tpc_update_power_rate_11n((int8_t*)pwr_table);
    } else {
        blog_error("RFTLV_TYPE_PWR_TABLE_11N NULL\r\n");
    }

    if (rftlv_get(rftlv_addr, RFTLV_API_TYPE_PWR_MODE, 80, p_buffer) > 0) {
        p_buffer[2] = '\0';
        update_poweroffset_config_rftv(rftlv_addr, (const char *)p_buffer);
    } else {
        blog_error("RFTLV_TYPE_PWR_MODE NULL\r\n");
    }

    if (rftlv_get(rftlv_addr, RFTLV_API_TYPE_PWR_TABLE_BLE, 80, p_buffer) > 0) {
        pwr_table_ble = *(int8_t *)p_buffer;
        blog_info("set pwr_table_ble = %ld in dts\r\n", pwr_table_ble);
    } else {
        blog_error("RFTLV_TYPE_PWR_TABLE_BLE NULL\r\n");
    }
#ifdef CFG_BLE_ENABLE
        ble_controller_set_tx_pwr(pwr_table_ble);
#endif

    vPortFree(p_buffer);
    
    return 0;
}
#endif
//static int __try_load_rftlv()
//{
//extern uint32_t _ld_symbol_rftlv_address;
//    return hal_board_load_rftv_info((uint32_t)&_ld_symbol_rftlv_address);
//zys}

static int hal_board_load_fdt_info(const void *dtb)
{
    const void *fdt = (const void *)dtb;/* const */

    /* set tx_pwr_tbl */
    uint8_t pwr_table[24];

    uint32_t channel_div_table[15];
    uint16_t channel_cnt_table[14];
    uint16_t lo_fcal_div = 0;
    int pwr_table_ble = 0;

    int wifi_offset = 0, bt_offset = 0;    /* subnode wifi & bluetooth */
    int offset1 = 0, offset2 = 0;        /* subnode offset1 */
    const uint8_t *addr_prop = 0;

    int lentmp = 0;
    int i;

    wifi_offset = fdt_subnode_offset(fdt, 0, "wifi");
    if (!(wifi_offset > 0)) {
       blog_error("wifi NULL.\r\n");
    }

    offset1 = fdt_subnode_offset(fdt, wifi_offset, "mac");
    if (offset1 > 0) {
        update_mac_config(fdt, offset1);
    }

    offset1 = fdt_subnode_offset(fdt, wifi_offset, "region");
    if (offset1 > 0) {
        /* set country_code */
        addr_prop = fdt_getprop(fdt, offset1, "country_code", &lentmp);
        if (4 == lentmp) {
            blog_info("country_code : %d\r\n", BL_FDT32_TO_U8(addr_prop, 4*0));

            bl_wifi_country_code_set(BL_FDT32_TO_U8(addr_prop, 4*0));
        }  else {
            blog_error("country_code NULL.\r\n");
        }
    }

//zys    if (0 == __try_load_rftlv()) {

        /* load rf from tlv successful */
//        goto __exit;
//    }

    offset1 = fdt_subnode_offset(fdt, wifi_offset, "brd_rf");
    if (offset1 > 0)
    {

        USER_UNUSED(lo_fcal_div);
        USER_UNUSED(channel_div_table);
        USER_UNUSED(channel_cnt_table);

        /* set xtal */
        //update_xtal_config(fdt, offset1);

        /* set channel_div_table, channel_cnt_table, lo_fcal_div */
        addr_prop = fdt_getprop(fdt, offset1, "channel_div_table", &lentmp);
        if (15*4 == lentmp) {
            for (i = 0; i < 15; i++) {
                channel_div_table[i] = BL_FDT32_TO_U32(addr_prop, 4*i);
            }
            blog_info("channel_div_table :\r\n");
            blog_buf(channel_div_table, 15*4);
        }  else {
            blog_error("channel_div_table NULL.\r\n");
        }

        addr_prop = fdt_getprop(fdt, offset1, "channel_cnt_table", &lentmp);
        if (14*4 == lentmp) {
            for (i = 0; i < 14; i++) {
                channel_cnt_table[i] = BL_FDT32_TO_U16(addr_prop, 4*i);
            }
            blog_info("channel_cnt_table :\r\n");
            blog_buf(channel_cnt_table, 14*4);
        }  else {
            blog_error("channel_cnt_table NULL.\r\n");
        }

        addr_prop = fdt_getprop(fdt, offset1, "lo_fcal_div", &lentmp);
        if (4 == lentmp) {
            lo_fcal_div = BL_FDT32_TO_U16(addr_prop, 4*0);
            blog_info("lo_fcal_div : %d\r\n", lo_fcal_div);
        }  else {
            blog_error("lo_fcal_div NULL.\r\n");
        }

        //TODO FIXME POWER
        //bl60x_fw_rf_table_set(channel_div_table, channel_cnt_table, lo_fcal_div);

        USER_UNUSED(pwr_table);
        addr_prop = fdt_getprop(fdt, offset1, "pwr_table_11b", &lentmp);
        if (4*4 == lentmp) {
            for (i = 0; i < 4; i++) {
                pwr_table[i] = BL_FDT32_TO_U32(addr_prop, 4*i);
            }
            blog_info("pwr_table_11b :%u %u %u %u\r\n",
                pwr_table[0],
                pwr_table[1],
                pwr_table[2],
                pwr_table[3]
            );
           //bl_tpc_update_power_rate_11b((int8_t*)pwr_table);
        }  else {
            blog_error("pwr_table_11b NULL. lentmp = %d\r\n", lentmp);
        }

        addr_prop = fdt_getprop(fdt, offset1, "pwr_table_11g", &lentmp);
        if (8*4 == lentmp) {
            for (i = 0; i < 8; i++) {
                pwr_table[i] = BL_FDT32_TO_U32(addr_prop, 4*i);
            }
            blog_info("pwr_table_11g :%u %u %u %u %u %u %u %u\r\n",
                pwr_table[0],
                pwr_table[1],
                pwr_table[2],
                pwr_table[3],
                pwr_table[4],
                pwr_table[5],
                pwr_table[6],
                pwr_table[7]
            );
            //bl_tpc_update_power_rate_11g((int8_t*)pwr_table);
        } else {
            blog_error("pwr_table_11g NULL. lentmp = %d\r\n", lentmp);
        }

        addr_prop = fdt_getprop(fdt, offset1, "pwr_table_11n", &lentmp);
        if (8*4 == lentmp) {
            for (i = 0; i < 8; i++) {
                pwr_table[i] = BL_FDT32_TO_U32(addr_prop, 4*i);
            }
            blog_info("pwr_table_11n :%u %u %u %u %u %u %u %u\r\n",
                pwr_table[0],
                pwr_table[1],
                pwr_table[2],
                pwr_table[3],
                pwr_table[4],
                pwr_table[5],
                pwr_table[6],
                pwr_table[7]
            );
            //bl_tpc_update_power_rate_11n((int8_t*)pwr_table);
        }  else {
            blog_error("pwr_table_11n NULL. lentmp = %d\r\n", lentmp);
        }
        //update_poweroffset_config(fdt, offset1);
    }

    bt_offset = fdt_subnode_offset(fdt, 0, "bluetooth");
    if (!(bt_offset > 0)) {
       blog_error("bt NULL.\r\n");
    }

    offset2 = fdt_subnode_offset(fdt, bt_offset, "brd_rf");
    if (offset2 > 0) {
        addr_prop = fdt_getprop(fdt, offset2, "pwr_table_ble", &lentmp);
        if (addr_prop) {
            pwr_table_ble = (int8_t)BL_FDT32_TO_U32(addr_prop, 0);
        } else {
            pwr_table_ble = 0;
        }
        blog_info("set pwr_table_ble = %ld in dts\r\n", pwr_table_ble);
#ifdef CFG_BLE_ENABLE
        //ble_controller_set_tx_pwr(pwr_table_ble);
#endif
    }

//__exit:
    //offset1 = update_ap_field(fdt, wifi_offset, "ap");
    //offset1 = update_sta_field(fdt, wifi_offset, "sta");
//    offset1 = update_rf_temp_field(fdt, wifi_offset, "rf_temp");

    return 0;
}
//#endif

#ifdef CONFIG_USER_DTS_INAPP
/*
 {
    model = "bl bl602 iot board";
    wifi {
        #address-cells = <1>;
        #size-cells = <1>;
        region {
            country_code = <86>;
        };
        mac {
            mode = "MBF";
            sta_mac_addr = [C8 43 57 82 73 40];
            ap_mac_addr = [C8 43 57 82 73 02];
        };
        ap {
            ssid = "bl_test_005";
            pwd = "12345678";
            ap_channel = <11>;
            auto_chan_detect = "disable";
        };
        brd_rf {
            xtal_mode = "MF";
            xtal = <36 36 0 60 60>;
            pwr_mode = "bf";
            pwr_table = <0x4 0x3 0x3 0xBA 0x4 0x3 0x4 0xB0 0x4 0x3 0x5 0xA7 0x3 0x3 0x0 0x9F 0x3 0x3 0x1 0x95 0x3 0x3 0x2 0x8C 0x3 0x3 0x3 0x81 0x3 0x3 0x4 0x77 0x3 0x3 0x5 0x6E 0x2 0x3 0x0 0x65 0x2 0x3 0x1 0x5B 0x2 0x3 0x2 0x52 0x2 0x3 0x3 0x48 0x2 0x3 0x4 0x3E 0x2 0x3 0x5 0x34 0x1 0x3 0x3 0xA>;
            pwr_offset = <10 10 10 10 10 10 10 10 10 10 10 10 10 10>;
            channel_div_table = <0x1EEC4EC4 0x1EFCB7CB 0x1F0D20D2 0x1F1D89D8 0x1F2DF2DF 0x1F3E5BE5 0x1F4EC4EC 0x1F5F2DF2 0x1F6F96F9 0x1F800000 0x1F906906 0x1FA0D20D 0x1FB13B13 0x1FD89D89 0x201F81F8>;
            channel_cnt_table = <0xA78A 0xA7E3 0xA83C 0xA895 0xA8ED 0xA946 0xA99F 0xA9F8 0xAA51 0xAAAA 0xAB03 0xAB5C 0xABB5 0xAC8A>;
            lo_fcal_div = <0x56B>;
        };
    };
};
*/
const uint8_t factory_dtb[] = {//1126
  0xd0, 0x0d, 0xfe, 0xed, 0x00, 0x00, 0x04, 0x66, 0x00, 0x00, 0x00, 0x38,
  0x00, 0x00, 0x03, 0x98, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x11,
  0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce,
  0x00, 0x00, 0x03, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x13,
  0x00, 0x00, 0x00, 0x00, 0x62, 0x6c, 0x20, 0x62, 0x6c, 0x36, 0x30, 0x32,
  0x20, 0x69, 0x6f, 0x74, 0x20, 0x62, 0x6f, 0x61, 0x72, 0x64, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x77, 0x69, 0x66, 0x69, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x06,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  0x72, 0x65, 0x67, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x56,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x6d, 0x61, 0x63, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x2e,
  0x4d, 0x42, 0x46, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06,
  0x00, 0x00, 0x00, 0x33, 0xc8, 0x43, 0x57, 0x82, 0x73, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x40,
  0xc8, 0x43, 0x57, 0x82, 0x73, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x01, 0x61, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x4c, 0x62, 0x6c, 0x5f, 0x74,
  0x65, 0x73, 0x74, 0x5f, 0x30, 0x30, 0x35, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x51, 0x31, 0x32, 0x33, 0x34,
  0x35, 0x36, 0x37, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x0b,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x60,
  0x64, 0x69, 0x73, 0x61, 0x62, 0x6c, 0x65, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x01, 0x62, 0x72, 0x64, 0x5f, 0x72, 0x66, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x71,
  0x4d, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x14,
  0x00, 0x00, 0x00, 0x7b, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x24,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3c,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x80,
  0x62, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xb0,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05,
  0x00, 0x00, 0x00, 0xa7, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x95,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x77,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05,
  0x00, 0x00, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5b,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x3e,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05,
  0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x0a,
  0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a,
  0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a,
  0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a,
  0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a,
  0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3c,
  0x00, 0x00, 0x00, 0x9e, 0x1e, 0xec, 0x4e, 0xc4, 0x1e, 0xfc, 0xb7, 0xcb,
  0x1f, 0x0d, 0x20, 0xd2, 0x1f, 0x1d, 0x89, 0xd8, 0x1f, 0x2d, 0xf2, 0xdf,
  0x1f, 0x3e, 0x5b, 0xe5, 0x1f, 0x4e, 0xc4, 0xec, 0x1f, 0x5f, 0x2d, 0xf2,
  0x1f, 0x6f, 0x96, 0xf9, 0x1f, 0x80, 0x00, 0x00, 0x1f, 0x90, 0x69, 0x06,
  0x1f, 0xa0, 0xd2, 0x0d, 0x1f, 0xb1, 0x3b, 0x13, 0x1f, 0xd8, 0x9d, 0x89,
  0x20, 0x1f, 0x81, 0xf8, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x38,
  0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0xa7, 0x8a, 0x00, 0x00, 0xa7, 0xe3,
  0x00, 0x00, 0xa8, 0x3c, 0x00, 0x00, 0xa8, 0x95, 0x00, 0x00, 0xa8, 0xed,
  0x00, 0x00, 0xa9, 0x46, 0x00, 0x00, 0xa9, 0x9f, 0x00, 0x00, 0xa9, 0xf8,
  0x00, 0x00, 0xaa, 0x51, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0xab, 0x03,
  0x00, 0x00, 0xab, 0x5c, 0x00, 0x00, 0xab, 0xb5, 0x00, 0x00, 0xac, 0x8a,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xc2,
  0x00, 0x00, 0x05, 0x6b, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x09, 0x6d, 0x6f, 0x64, 0x65,
  0x6c, 0x00, 0x23, 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x2d, 0x63,
  0x65, 0x6c, 0x6c, 0x73, 0x00, 0x23, 0x73, 0x69, 0x7a, 0x65, 0x2d, 0x63,
  0x65, 0x6c, 0x6c, 0x73, 0x00, 0x63, 0x6f, 0x75, 0x6e, 0x74, 0x72, 0x79,
  0x5f, 0x63, 0x6f, 0x64, 0x65, 0x00, 0x6d, 0x6f, 0x64, 0x65, 0x00, 0x73,
  0x74, 0x61, 0x5f, 0x6d, 0x61, 0x63, 0x5f, 0x61, 0x64, 0x64, 0x72, 0x00,
  0x61, 0x70, 0x5f, 0x6d, 0x61, 0x63, 0x5f, 0x61, 0x64, 0x64, 0x72, 0x00,
  0x73, 0x73, 0x69, 0x64, 0x00, 0x70, 0x77, 0x64, 0x00, 0x61, 0x70, 0x5f,
  0x63, 0x68, 0x61, 0x6e, 0x6e, 0x65, 0x6c, 0x00, 0x61, 0x75, 0x74, 0x6f,
  0x5f, 0x63, 0x68, 0x61, 0x6e, 0x5f, 0x64, 0x65, 0x74, 0x65, 0x63, 0x74,
  0x00, 0x78, 0x74, 0x61, 0x6c, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x00, 0x78,
  0x74, 0x61, 0x6c, 0x00, 0x70, 0x77, 0x72, 0x5f, 0x6d, 0x6f, 0x64, 0x65,
  0x00, 0x70, 0x77, 0x72, 0x5f, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x00, 0x70,
  0x77, 0x72, 0x5f, 0x6f, 0x66, 0x66, 0x73, 0x65, 0x74, 0x00, 0x63, 0x68,
  0x61, 0x6e, 0x6e, 0x65, 0x6c, 0x5f, 0x64, 0x69, 0x76, 0x5f, 0x74, 0x61,
  0x62, 0x6c, 0x65, 0x00, 0x63, 0x68, 0x61, 0x6e, 0x6e, 0x65, 0x6c, 0x5f,
  0x63, 0x6e, 0x74, 0x5f, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x00, 0x6c, 0x6f,
  0x5f, 0x66, 0x63, 0x61, 0x6c, 0x5f, 0x64, 0x69, 0x76, 0x00
};

#endif

uint32_t hal_board_get_factory_addr(void)
{
    return factory_addr;
}

int hal_board_cfg(uint8_t board_code)
{
#ifdef CONFIG_USER_DTS_INAPP
    factory_addr = (uint32_t)factory_dtb;
#else
    int ret;
    uint32_t size;

    USER_UNUSED(ret);
    ret = hal_boot2_partition_addr_active("factory", &factory_addr, &size);
    blog_info("[MAIN] [BOARD] [FLASH] addr from partition is %08x, ret is %d\r\n", (unsigned int)factory_addr, ret);
    if (0 == factory_addr) {
        blog_error("[MAIN] [BOARD] [FLASH] Dead loop. Reason: NO valid Param Parition found\r\n");
        while (1) {
        }
    }

    ret = hal_boot2_partition_bus_addr_active("factory", &factory_addr, &size);
    blog_info("[MAIN] [BOARD] [XIP] addr from partition is %08x, ret is %d\r\n", (unsigned int)factory_addr, ret);
    if (0 == factory_addr) {
        blog_error("[MAIN] [BOARD] [XIP] Dead loop. Reason: NO valid Param Parition found\r\n");
        while (1) {
        }
    }
#endif

//#ifndef FEATURE_WIFI_DISABLE
    // printf("hal_board_load_fdt_info\n\r");
    hal_board_load_fdt_info((const void *)factory_addr);
//#endif

    return 0;
}
