/**
 * *****************************************************************************
 * @file hal_boot2_custom.h
 * @version 0.1
 * @date 2021-07-17
 * @brief
 * *****************************************************************************
 * @attention
 *
 *  <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *    3. Neither the name of Bouffalo Lab nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * *****************************************************************************
 */
#ifndef __HAL_BOOT2_H__
#define __HAL_BOOT2_H__

#include "hal_common.h"
#include "bl808_sflash.h"
#include "bl808_glb.h"

#define HAL_PLL_CFG_MAGICCODE "PCFG"

#define HAL_BOOT2_PK_HASH_SIZE  256 / 8
#define HAL_BOOT2_IMG_HASH_SIZE 256 / 8
#define HAL_BOOT2_ECC_KEYXSIZE  256 / 8
#define HAL_BOOT2_ECC_KEYYSIZE  256 / 8
#define HAL_BOOT2_SIGN_MAXSIZE  (2048 / 8)
#define HAL_BOOT2_DEADBEEF_VAL  0xdeadbeef
#define HAL_BOOT2_CPU0_MAGIC    "BFNP"
#define HAL_BOOT2_CPU1_MAGIC    "BFAP"
#define HAL_BOOT2_CP_FLAG       0x02
#define HAL_BOOT2_MP_FLAG       0x01
#define HAL_BOOT2_SP_FLAG       0x00

#define HAL_BOOT2_SUPPORT_DECOMPRESS          1 /* 1 support decompress, 0 not support */
#define HAL_BOOT2_SUPPORT_USB_IAP             0 /* 1 support IAP, 0 not support */
#define HAL_BOOT2_SUPPORT_EFLASH_LOADER_RAM   0 /* 1 support eflash loader ram, 0 not support */
#define HAL_BOOT2_SUPPORT_EFLASH_LOADER_FLASH 0 /* 1 support eflash loader flash, 0 not support */
#define HAL_BOOT2_SUPPORT_SIGN_ENCRYPT        1 /* 1 support sign and encrypt, 0 not support */

#define HAL_BOOT2_CPU_GROUP_MAX     1
#define HAL_BOOT2_CPU_MAX           3
#define HAL_BOOT2_RAM_IMG_COUNT_MAX 5

#define HAL_BOOT2_FW_IMG_OFFSET_AFTER_HEADER 4 * 1024
#define HAL_BOOT2_MFG_START_REQUEST_OFFSET   8 * 1024

#define HAL_BOOT2_PSRAM_INFO_MASK (0xff0000)
#define HAL_BOOT2_PSRAM_INFO_POS  (16)

struct __attribute__((packed, aligned(4))) boot_efuse_sw_cfg0_t {
    uint32_t bootrom_protect  : 1; /* ef_sw_usage_0 bit [0] */
    uint32_t uart_log_disable : 1; /* ef_sw_usage_0 bit [1] */
    uint32_t boot_pin_cfg     : 1; /* ef_sw_usage_0 bit [2] */
    //uint32_t dbg_pin_cfg            : 1; /* ef_sw_usage_0 bit [3] */
    uint32_t uart_download_cfg : 1; /* ef_sw_usage_0 bit [3] */

    uint32_t mediaboot_disable : 1; /* ef_sw_usage_0 bit [4] */
    uint32_t uartboot_disable  : 1; /* ef_sw_usage_0 bit [5] */
    uint32_t usbboot_enable    : 1; /* ef_sw_usage_0 bit [6] */
    uint32_t uart_log_reopen   : 1; /* ef_sw_usage_1 bit [7] */

    uint32_t sign_cfg       : 1; /* ef_sw_usage_0 bit [8] */
    uint32_t dcache_disable : 1; /* ef_sw_usage_0 bit [9] */
    uint32_t jtag_cfg       : 2; /* ef_sw_usage_0 bit [11:10] */

    uint32_t fix_key_sel : 1; /* ef_sw_usage_0 bit [12] */

    uint32_t sdh_en            : 1; /* ef_sw_usage_1 bit [13] */
    uint32_t sf_pin_cfg        : 5; /* ef_sw_usage_0 bit [18:14] */
    uint32_t boot_level_revert : 1; /* ef_sw_usage_0 bit [19] */

    uint32_t boot_pin_dly    : 2; /* ef_sw_usage_0 bit [21:20] */
    uint32_t ldo_trim_enable : 1; /* ef_sw_usage_0 bit [22] */
    uint32_t trim_enable     : 1; /* ef_sw_usage_0 bit [23] */

    uint32_t no_hd_boot_en     : 1; /* ef_sw_usage_0 bit [24] */
    uint32_t flash_power_delay : 2; /* ef_sw_usage_0 bit [26:25] */
    uint32_t tz_boot           : 1; /* ef_sw_usage_0 bit [27] */

    uint32_t encrypted_tz_boot    : 1; /* ef_sw_usage_0 bit [28] */
    uint32_t hbn_check_sign       : 1; /* ef_sw_usage_0 bit [29] */
    uint32_t keep_dbg_port_closed : 1; /* ef_sw_usage_0 bit [30] */
    uint32_t hbn_jump_disable     : 1; /* ef_sw_usage_0 bit [31] */
};

struct __attribute__((packed, aligned(4))) boot_efuse_sw_cfg1_t {
    uint32_t xtal_type  : 3; /* ef_sw_usage_1 bit [2:0] */
    uint32_t wifipll_pu : 1; /* ef_sw_usage_1 bit [3] */

    uint32_t aupll_pu   : 1; /* ef_sw_usage_1 bit [4] */
    uint32_t cpupll_pu  : 1; /* ef_sw_usage_1 bit [5] */
    uint32_t mipipll_pu : 1; /* ef_sw_usage_1 bit [6] */
    uint32_t uhspll_pu  : 1; /* ef_sw_usage_1 bit [7] */

    uint32_t mcu_clk     : 3; /* ef_sw_usage_1 bit [10:8] */
    uint32_t mcu_clk_div : 1; /* ef_sw_usage_1 bit [11] */

    uint32_t mcu_pbclk_div : 2; /* ef_sw_usage_1 bit [13:12] */
    uint32_t lp_div        : 1; /* ef_sw_usage_1 bit [14] */
    uint32_t dsp_clk       : 2; /* ef_sw_usage_1 bit [16:15] */
    uint32_t dsp_clk_div   : 1; /* ef_sw_usage_1 bit [17] */
    uint32_t dsp_pbclk     : 2; /* ef_sw_usage_1 bit [19:18] */

    uint32_t emi_clk               : 2; /* ef_sw_usage_1 bit [21:20] */
    uint32_t emi_clk_div           : 1; /* ef_sw_usage_1 bit [22] */
    uint32_t flash_clk_type        : 3; /* ef_sw_usage_1 bit [25:23] */
    uint32_t flash_clk_div         : 1; /* ef_sw_usage_1 bit [26] */
    uint32_t ldo18flash_bypass_cfg : 1; /* ef_sw_usage_1 bit [27] */
    uint32_t bootlog_pin_cfg       : 1; /* ef_sw_usage_1 bit [28] */

    uint32_t abt_offset         : 1; /* ef_sw_usage_1 bit [29] */
    uint32_t boot_pull_cfg      : 1; /* ef_sw_usage_1 bit [30] */
    uint32_t usb_if_int_disable : 1; /* ef_sw_usage_1 bit [31] */
};

typedef struct
{
    uint8_t encrypted[HAL_BOOT2_CPU_GROUP_MAX];
    uint8_t sign[HAL_BOOT2_CPU_GROUP_MAX];
    uint8_t hbn_check_sign;
    uint8_t rsvd[3];
    uint8_t chip_id[8];
    uint8_t pk_hash_cpu0[HAL_BOOT2_PK_HASH_SIZE];
    uint8_t pk_hash_cpu1[HAL_BOOT2_PK_HASH_SIZE];
    uint8_t uart_download_cfg;
    uint8_t sf_pin_cfg;
    uint8_t keep_dbg_port_closed;
    uint8_t boot_pin_cfg;
    uint32_t dev_info;
} boot2_efuse_hw_config;

struct __attribute__((packed, aligned(4))) hal_flash_config {
    uint32_t magicCode; /*'FCFG'*/
    SPI_Flash_Cfg_Type cfg;
    uint32_t crc32;
};

struct __attribute__((packed, aligned(4))) hal_sys_clk_config {
    uint8_t xtal_type;
    uint8_t mcu_clk;
    uint8_t mcu_clk_div;
    uint8_t mcu_bclk_div;

    uint8_t mcu_pbclk_div;
    uint8_t lp_div;
    uint8_t dsp_clk;
    uint8_t dsp_clk_div;

    uint8_t dsp_bclk_div;
    uint8_t dsp_pbclk;
    uint8_t dsp_pbclk_div;
    uint8_t emi_clk;

    uint8_t emi_clk_div;
    uint8_t flash_clk_type;
    uint8_t flash_clk_div;
    uint8_t wifipll_pu;

    uint8_t aupll_pu;
    uint8_t cpupll_pu;
    uint8_t mipipll_pu;
    uint8_t uhspll_pu;
};

typedef struct {
    uint32_t magiccode;
    struct hal_sys_clk_config cfg;
    uint32_t crc32;
} hal_pll_config;

struct __attribute__((packed, aligned(4))) hal_basic_cfg_t {
    uint32_t sign_type          : 2; /* [1: 0]   for sign */
    uint32_t encrypt_type       : 2; /* [3: 2]   for encrypt */
    uint32_t key_sel            : 2; /* [5: 4]   key slot */
    uint32_t xts_mode           : 1; /* [6]      for xts mode */
    uint32_t aes_region_lock    : 1; /* [7]      rsvd */
    uint32_t no_segment         : 1; /* [8]      no segment info */
    uint32_t boot2_enable       : 1; /* [9]      boot2 enable */
    uint32_t boot2_rollback     : 1; /* [10]     boot2 rollback */
    uint32_t cpu_master_id      : 4; /* [14: 11] master id */
    uint32_t notload_in_bootrom : 1; /* [15]     notload in bootrom */
    uint32_t crc_ignore         : 1; /* [16]     ignore crc */
    uint32_t hash_ignore        : 1; /* [17]     hash ignore */
    uint32_t power_on_mm        : 1; /* [18]     power on mm */
    uint32_t em_sel             : 3; /* [21: 19] em_sel */
    uint32_t cmds_en            : 1; /* [22]     command spliter enable */
    uint32_t cmds_wrap_mode     : 2; /* [24: 23] cmds wrap mode */
    uint32_t cmds_wrap_len      : 4; /* [28: 25] cmds wrap len */
    uint32_t icache_invalid     : 1; /* [29] icache invalid */
    uint32_t dcache_invalid     : 1; /* [30] dcache invalid */
    uint32_t fpga_halt_release  : 1; /* [31] FPGA halt release function */

    uint32_t group_image_offset; /* flash controller offset */
    uint32_t aes_region_len;     /* aes region length */

    uint32_t img_len_cnt; /* image length or segment count */
    uint32_t hash[8];     /* hash of the image */
};

struct __attribute__((packed, aligned(4))) hal_cpu_cfg_t {
    uint8_t config_enable;     /* coinfig this cpu */
    uint8_t halt_cpu;          /* halt this cpu */
    uint8_t cache_enable  : 1; /* cache setting */
    uint8_t cache_wa      : 1; /* cache setting */
    uint8_t cache_wb      : 1; /* cache setting */
    uint8_t cache_wt      : 1; /* cache setting */
    uint8_t cache_way_dis : 4; /* cache setting */
    uint8_t rsvd;

    uint32_t cache_range_h; /* cache range high */
    uint32_t cache_range_l; /* cache range low */

    uint32_t image_address_offset; /* image address on flash */ /*image_address_offset*/
    uint32_t boot_entry;                                        /* entry point of the m0 image */
    uint32_t msp_val;                                           /* msp value */
};

struct __attribute__((packed, aligned(4))) hal_patch_cfg_t {
    uint32_t addr;
    uint32_t value;
};

struct __attribute__((packed, aligned(4))) hal_bootheader_t {
    uint32_t magiccode;
    uint32_t rivison;

    struct hal_flash_config flashCfg;
    hal_pll_config clkCfg;

    struct hal_basic_cfg_t basic_cfg;

    struct hal_cpu_cfg_t cpu_cfg[HAL_BOOT2_CPU_MAX];

    uint32_t boot2_pt_table_0; /* address of partition table 0 */
    uint32_t boot2_pt_table_1; /* address of partition table 1 */

    uint32_t flashCfgTableAddr; /* address of flashcfg table list */
    uint32_t flashCfgTableLen;  /* flashcfg table list len */

    struct hal_patch_cfg_t patch_on_read[4]; /* do patch when read flash */
    struct hal_patch_cfg_t patch_on_jump[4]; /* do patch when jump */

    uint32_t rsvd[5];

    uint32_t crc32;
};

typedef struct
{
    uint8_t img_valid;
    uint8_t pk_src;
    uint8_t rsvd[2];

    struct hal_basic_cfg_t basic_cfg;

    struct hal_cpu_cfg_t cpu_cfg[HAL_BOOT2_CPU_MAX];

    uint8_t aes_iv[16 + 4]; //iv in boot header

    uint8_t eckye_x[HAL_BOOT2_ECC_KEYXSIZE];  //ec key in boot header
    uint8_t eckey_y[HAL_BOOT2_ECC_KEYYSIZE];  //ec key in boot header
    uint8_t eckey_x2[HAL_BOOT2_ECC_KEYXSIZE]; //ec key in boot header
    uint8_t eckey_y2[HAL_BOOT2_ECC_KEYYSIZE]; //ec key in boot header

    uint8_t signature[HAL_BOOT2_SIGN_MAXSIZE];  //signature in boot header
    uint8_t signature2[HAL_BOOT2_SIGN_MAXSIZE]; //signature in boot header

} boot2_image_config;

extern boot2_efuse_hw_config g_efuse_cfg;
extern uint8_t g_ps_mode;
extern uint32_t g_user_hash_ignored;
extern struct device *dev_check_hash;

void hal_boot2_init_clock(void);
uint32_t hal_boot2_custom(void *custom_param);
void hal_boot2_reset_sec_eng(void);
void hal_boot2_sw_system_reset(void);
void hal_boot2_set_psmode_status(uint32_t flag);
uint32_t hal_boot2_get_psmode_status(void);
uint32_t hal_boot2_get_user_fw(void);
void hal_boot2_clr_user_fw(void);
void hal_boot2_get_efuse_cfg(boot2_efuse_hw_config *efuse_cfg);
int32_t hal_boot2_get_clk_cfg(hal_pll_config *cfg);
void hal_boot2_sboot_finish(void);
void hal_boot2_uart_gpio_init(void);
void hal_boot2_debug_uart_gpio_init(void);
void hal_boot2_debug_uart_gpio_deinit(void);
int32_t hal_boot_parse_bootheader(boot2_image_config *boot_img_cfg, uint8_t *data);
void hal_boot2_clean_cache(void);
BL_Err_Type hal_boot2_set_cache(uint8_t cont_read, boot2_image_config *boot_img_cfg);
void hal_boot2_get_ram_img_cnt(char *img_name[], uint32_t *ram_img_cnt);
void hal_boot2_get_img_info(uint8_t *data, uint32_t *image_offset, uint32_t *img_len, uint8_t **hash);
void hal_boot2_release_cpu(uint32_t core, uint32_t boot_addr);
uint32_t hal_boot2_get_xip_addr(uint32_t flash_addr);
uint32_t hal_boot2_get_grp_count(void);
uint32_t hal_boot2_get_cpu_count(void);
uint32_t hal_boot2_get_feature_flag(void);
uint32_t hal_boot2_get_bootheader_offset(void);
#endif
