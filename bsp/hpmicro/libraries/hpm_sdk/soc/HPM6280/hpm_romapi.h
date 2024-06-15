/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ROMAPI_H
#define HPM_ROMAPI_H

/**
 * @brief ROM APIs
 * @defgroup romapi_interface ROM APIs
 * @{
 */

#include "hpm_common.h"
#include "hpm_otp_drv.h"
#include "hpm_romapi_xpi_def.h"
#include "hpm_romapi_xpi_soc_def.h"
#include "hpm_romapi_xpi_nor_def.h"
#include "hpm_romapi_xpi_ram_def.h"
#include "hpm_sdp_drv.h"

/* XPI0 base address */
#define HPM_XPI0_BASE (0xF3040000UL)                /**< XPI0 Base address */
/* XPI0 base pointer */
#define HPM_XPI0 ((XPI_Type *) HPM_XPI0_BASE)       /**< XPI0 Base pointer */


/***********************************************************************************************************************
 *
 *
 *      Definitions
 *
 *
 **********************************************************************************************************************/
/**
 * @brief Enter Bootloader API argument
 */
typedef union {
    uint32_t U;
    struct {
        uint32_t index: 8;          /**< Image index */
        uint32_t peripheral: 8;     /**< Boot peripheral */
        uint32_t src: 8;            /**< Boot source */
        uint32_t tag: 8;            /**< ROM API parameter tag, must be 0xEB */
    };
} api_boot_arg_t;

/*EXiP Region Parameter */
typedef struct {
    uint32_t start;             /**< Start address, must be 4KB aligned */
    uint32_t len;               /**< Must be 4KB aligned */
    uint8_t key[16];            /**< AES Key */
    uint8_t ctr[8];             /**< Initial Vector/Counter */
} exip_region_param_t;

#define API_BOOT_TAG  (0xEBU)                           /**< ROM API parameter tag */
#define API_BOOT_SRC_OTP (0U)                           /**< Boot source: OTP */
#define API_BOOT_SRC_PRIMARY (1U)                       /**< Boot source: Primary */
#define API_BOOT_SRC_SERIAL_BOOT (2U)                   /**< Boot source: Serial Boot */
#define API_BOOT_SRC_ISP (3U)                           /**< Boot source: ISP */
#define API_BOOT_PERIPH_AUTO (0U)                       /**< Boot peripheral: Auto detected */
#define API_BOOT_PERIPH_UART (1U)                       /**< Boot peripheral: UART */
#define API_BOOT_PERIPH_USBHID (2U)                     /**< Boot Peripheral: USB-HID */

/**
 * @brief OTP driver interface
 */
typedef struct {
    /**< OTP driver interface version */
    uint32_t version;
    /**< OTP driver interface: init */
    void (*init)(void);
    /**< OTP driver interface: deinit */
    void (*deinit)(void);
    /**< OTP driver interface: read from shadow */
    uint32_t (*read_from_shadow)(uint32_t addr);
    /**< OTP driver interface: read from ip */
    uint32_t (*read_from_ip)(uint32_t addr);
    /**< OTP driver interface: program */
    hpm_stat_t (*program)(uint32_t addr, const uint32_t *src, uint32_t num_of_words);
    /**< OTP driver interface: reload */
    hpm_stat_t (*reload)(otp_region_t region);
    /**< OTP driver interface: lock */
    hpm_stat_t (*lock)(uint32_t addr, otp_lock_option_t lock_option);
    /**< OTP driver interface: lock_shadow */
    hpm_stat_t (*lock_shadow)(uint32_t addr, otp_lock_option_t lock_option);
    /**< OTP driver interface: set_configurable_region */
    hpm_stat_t (*set_configurable_region)(uint32_t start, uint32_t num_of_words);
    /**< OTP driver interface: write_shadow_register */
    hpm_stat_t (*write_shadow_register)(uint32_t addr, uint32_t data);
} otp_driver_interface_t;

/**
 * @brief XPI driver interface
 */
typedef struct {
    /**< XPI driver interface: version */
    uint32_t version;
    /**< XPI driver interface: get default configuration */
    hpm_stat_t (*get_default_config)(xpi_config_t *xpi_config);
    /**< XPI driver interface: get default device configuration */
    hpm_stat_t (*get_default_device_config)(xpi_device_config_t *dev_config);
    /**< XPI driver interface: initialize the XPI using xpi_config */
    hpm_stat_t (*init)(XPI_Type *base, xpi_config_t *xpi_config);
    /**< XPI driver interface: configure the AHB buffer */
    hpm_stat_t (*config_ahb_buffer)(XPI_Type *base, xpi_ahb_buffer_cfg_t *ahb_buf_cfg);
    /**< XPI driver interface: configure the device */
    hpm_stat_t (*config_device)(XPI_Type *base, xpi_device_config_t *dev_cfg, xpi_channel_t channel);
    /**< XPI driver interface: update instruction talbe */
    hpm_stat_t (*update_instr_table)(XPI_Type *base, const uint32_t *inst_base, uint32_t seq_idx, uint32_t num);
    /**< XPI driver interface: transfer command/data using block interface */
    hpm_stat_t (*transfer_blocking)(XPI_Type *base, xpi_xfer_ctx_t *xfer);
    /**< Software reset the XPI controller */
    void (*software_reset)(XPI_Type *base);
    /**< XPI driver interface: Check whether IP is idle */
    bool (*is_idle)(XPI_Type *base);
    /**< XPI driver interface: update delay line setting */
    void (*update_dllcr)(XPI_Type *base,
                         uint32_t serial_root_clk_freq,
                         uint32_t data_valid_time,
                         xpi_channel_t channel,
                         uint32_t dly_target);
    /**< XPI driver interface: Get absolute address for APB transfer */
    hpm_stat_t
    (*get_abs_apb_xfer_addr)(XPI_Type *base, xpi_xfer_channel_t channel, uint32_t in_addr, uint32_t *out_addr);
} xpi_driver_interface_t;

/**
 * @brief XPI NOR driver interface
 */
typedef struct {
    /**< XPI NOR driver interface: API version */
    uint32_t version;
    /**< XPI NOR driver interface: Get FLASH configuration */
    hpm_stat_t (*get_config)(XPI_Type *base, xpi_nor_config_t *nor_cfg, xpi_nor_config_option_t *cfg_option);
    /**< XPI NOR driver interface: initialize FLASH */
    hpm_stat_t (*init)(XPI_Type *base, xpi_nor_config_t *nor_config);
    /**< XPI NOR driver interface: Enable write access to FLASH */
    hpm_stat_t
    (*enable_write)(XPI_Type *base, xpi_xfer_channel_t channel, const xpi_nor_config_t *nor_config, uint32_t addr);
    /**< XPI NOR driver interface: Get FLASH status register */
    hpm_stat_t (*get_status)(XPI_Type *base,
                             xpi_xfer_channel_t channel,
                             const xpi_nor_config_t *nor_config,
                             uint32_t addr,
                             uint16_t *out_status);
    /**< XPI NOR driver interface: Wait when FLASH is still busy */
    hpm_stat_t
    (*wait_busy)(XPI_Type *base, xpi_xfer_channel_t channel, const xpi_nor_config_t *nor_config, uint32_t addr);
    /**< XPI NOR driver interface: erase a specified FLASH region */
    hpm_stat_t (*erase)(XPI_Type *base,
                        xpi_xfer_channel_t channel,
                        const xpi_nor_config_t *nor_config,
                        uint32_t start,
                        uint32_t length);
    /**< XPI NOR driver interface: Erase the whole FLASH */
    hpm_stat_t (*erase_chip)(XPI_Type *base, xpi_xfer_channel_t channel, const xpi_nor_config_t *nor_config);
    /**< XPI NOR driver interface: Erase specified FLASH sector */
    hpm_stat_t
    (*erase_sector)(XPI_Type *base, xpi_xfer_channel_t channel, const xpi_nor_config_t *nor_config, uint32_t addr);
    /**< XPI NOR driver interface: Erase specified FLASH block */
    hpm_stat_t
    (*erase_block)(XPI_Type *base, xpi_xfer_channel_t channel, const xpi_nor_config_t *nor_config, uint32_t addr);
    /**< XPI NOR driver interface: Program data to specified FLASH address */
    hpm_stat_t (*program)(XPI_Type *base,
                          xpi_xfer_channel_t channel,
                          const xpi_nor_config_t *nor_config,
                          const uint32_t *src,
                          uint32_t dst_addr,
                          uint32_t length);
    /**< XPI NOR driver interface: read data from specified FLASH address */
    hpm_stat_t (*read)(XPI_Type *base,
                       xpi_xfer_channel_t channel,
                       const xpi_nor_config_t *nor_config,
                       uint32_t *dst,
                       uint32_t start,
                       uint32_t length);
    /**< XPI NOR driver interface: program FLASH page using nonblocking interface */
    hpm_stat_t (*page_program_nonblocking)(XPI_Type *base,
                                           xpi_xfer_channel_t channel,
                                           const xpi_nor_config_t *nor_config,
                                           const uint32_t *src,
                                           uint32_t dst_addr,
                                           uint32_t length);
    /**< XPI NOR driver interface: erase FLASH sector using nonblocking interface */
    hpm_stat_t (*erase_sector_nonblocking)(XPI_Type *base,
                                           xpi_xfer_channel_t channel,
                                           const xpi_nor_config_t *nor_config,
                                           uint32_t addr);
    /**< XPI NOR driver interface: erase FLASH block using nonblocking interface */
    hpm_stat_t (*erase_block_nonblocking)(XPI_Type *base,
                                          xpi_xfer_channel_t channel,
                                          const xpi_nor_config_t *nor_config,
                                          uint32_t addr);
    /**< XPI NOR driver interface: erase the whole FLASh using nonblocking interface */
    hpm_stat_t
    (*erase_chip_nonblocking)(XPI_Type *base, xpi_xfer_channel_t channel, const xpi_nor_config_t *nor_config);

    uint32_t reserved0[3];

    /**< XPI NOR driver interface: automatically configuration flash based on the cfg_option setting */
    hpm_stat_t (*auto_config)(XPI_Type *base, xpi_nor_config_t *nor_cfg, xpi_nor_config_option_t *cfg_option);

    /**< XPI NOR driver interface: Get FLASH properties */
    hpm_stat_t (*get_property)(XPI_Type *base, xpi_nor_config_t *nor_cfg, uint32_t property_id, uint32_t *value);

} xpi_nor_driver_interface_t;

/**
 * @brief XPI RAM driver interface
 */
typedef struct {
    /**< XPI RAM driver interface: API version */
    uint32_t version;

    /**< Get XPI RAM configuration based on cfg_option */
    hpm_stat_t (*get_config)(XPI_Type *base, xpi_ram_config_t *ram_cfg, xpi_ram_config_option_t *cfg_option);

    /**< XPI RAM driver interface: Initialize XPI RAM */
    hpm_stat_t (*init)(XPI_Type *base, xpi_ram_config_t *ram_cfg);
} xpi_ram_driver_interface_t;

/**
 * @brief SDP API interface
 */
typedef struct {
    /**< SDP API interface: API version */
    uint32_t version;
    /**< SDP API interface: Initialize IP */
    hpm_stat_t (*sdp_ip_init)(void);
    /**< SDP API interface: Deinitialize IP */
    hpm_stat_t (*sdp_ip_deinit)(void);
    /**< SDP API interface: Set AES key */
    hpm_stat_t (*aes_set_key)(sdp_aes_ctx_t *aes_ctx, const uint8_t *key, sdp_aes_key_bits_t keybits, uint32_t key_idx);
    /**< SDP API interface: AES ECB crypto operation */
    hpm_stat_t (*aes_crypt_ecb)(sdp_aes_ctx_t *aes_ctx, sdp_aes_op_t op, uint32_t len, const uint8_t *in, uint8_t *out);
    /**< SDP API interface: AES CBC crypto operation */
    hpm_stat_t (*aes_crypt_cbc)(sdp_aes_ctx_t *aes_ctx,
                                sdp_aes_op_t op,
                                uint32_t length,
                                uint8_t iv[16],
                                const uint8_t *input,
                                uint8_t *output);
    /**< SDP API interface: AES CTR crypto operation */
    hpm_stat_t
    (*aes_crypt_ctr)(sdp_aes_ctx_t *aes_ctx, uint8_t *nonce_ctr, uint8_t *input, uint8_t *output, uint32_t length);
    /**< SDP API interface: AES CCM encryption */
    hpm_stat_t (*aes_ccm_gen_enc)(sdp_aes_ctx_t *aes_ctx,
                                  uint32_t input_len,
                                  const uint8_t *nonce,
                                  uint32_t nonce_len,
                                  const uint8_t *aad,
                                  uint32_t aad_len,
                                  const uint8_t *input,
                                  uint8_t *output,
                                  uint8_t *tag,
                                  uint32_t tag_len);
    /**< SDP API interface: AES CCM Decrypt and verify */
    hpm_stat_t (*aes_ccm_dec_verify)(sdp_aes_ctx_t *aes_ctx,
                                     uint32_t input_len,
                                     const uint8_t *nonce,
                                     uint32_t nonce_len,
                                     const uint8_t *aad,
                                     uint32_t aad_len,
                                     const uint8_t *input,
                                     uint8_t *output,
                                     const uint8_t *tag,
                                     uint32_t tag_len);
    /**< SDP API interface: memcpy */
    hpm_stat_t (*memcpy)(sdp_dma_ctx_t *dma_ctx, void *dst, const void *src, uint32_t length);
    /**< SDP API interface: memset */
    hpm_stat_t (*memset)(sdp_dma_ctx_t *dma_ctx, void *dst, uint8_t pattern, uint32_t length);
    /**< SDP API interface: HASH initialization */
    hpm_stat_t (*hash_init)(sdp_hash_ctx_t *hash_ctx, sdp_hash_alg_t alg);
    /**< SDP API interface: HASH update */
    hpm_stat_t (*hash_update)(sdp_hash_ctx_t *hash_ctx, const uint8_t *data, uint32_t length);
    /**< SDP API interface: HASH finish */
    hpm_stat_t (*hash_finish)(sdp_hash_ctx_t *hash_ctx, uint8_t *digest);
    /**< SDP API interface: Set SM4 Key */
    hpm_stat_t (*sm4_set_key)(sdp_sm4_ctx_t *sm4_ctx, const uint8_t *key, sdp_sm4_key_bits_t keybits, uint32_t key_idx);
    /**< SDP API interface: SM4 Crypto ECB mode */
    hpm_stat_t (*sm4_crypt_ecb)(sdp_sm4_ctx_t *sm4_ctx, sdp_sm4_op_t op, uint32_t len, const uint8_t *in, uint8_t *out);
    /**< SDP API Interface: SM4 Crypto CBC mode*/
    hpm_stat_t (*sm4_crypt_cbc)(sdp_sm4_ctx_t *sm4_ctx,
                                sdp_sm4_op_t op,
                                uint32_t length,
                                uint8_t iv[16],
                                const uint8_t *input,
                                uint8_t *output);
    /**< SDP API Interface: SM4 CTR mode */
    hpm_stat_t
    (*sm4_crypt_ctr)(sdp_sm4_ctx_t *sm4_ctx, uint8_t *nonce_ctr, uint8_t *input, uint8_t *output, uint32_t length);
    /**< SDP API Interface: SM4 CCM Encryption */
    hpm_stat_t (*sm4_ccm_gen_enc)(sdp_sm4_ctx_t *sm4_ctx,
                                  uint32_t input_len,
                                  const uint8_t *nonce,
                                  uint32_t nonce_len,
                                  const uint8_t *aad,
                                  uint32_t aad_len,
                                  const uint8_t *input,
                                  uint8_t *output,
                                  uint8_t *tag,
                                  uint32_t tag_len);
    /**< SDP API Interface: SM4 CCM Decrypt and Verify */
    hpm_stat_t (*sm4_ccm_dec_verify)(sdp_sm4_ctx_t *sm4_ctx,
                                     uint32_t input_len,
                                     const uint8_t *nonce,
                                     uint32_t nonce_len,
                                     const uint8_t *aad,
                                     uint32_t aad_len,
                                     const uint8_t *input,
                                     uint8_t *output,
                                     const uint8_t *tag,
                                     uint32_t tag_len);
} sdp_driver_interface_t;

/**
 * @brief Bootloader API table
 */
typedef struct {
    /**< Bootloader API table: version */
    const uint32_t version;
    /**< Bootloader API table: copyright string address */
    const char *copyright;
    /**< Bootloader API table: run_bootloader API */
    hpm_stat_t (*run_bootloader)(void *arg);
    /**< Bootloader API table: otp driver interface address */
    const otp_driver_interface_t *otp_driver_if;
    /**< Bootloader API table: xpi driver interface address */
    const xpi_driver_interface_t *xpi_driver_if;
    /**< Bootloader API table: xpi nor driver interface address */
    const xpi_nor_driver_interface_t *xpi_nor_driver_if;
    /**< Bootloader API table: xpi ram driver interface address */
    const xpi_ram_driver_interface_t *xpi_ram_driver_if;
    /**< Bootloader API table: sdp driver interface address */
    const sdp_driver_interface_t *sdp_driver_if;
} bootloader_api_table_t;

/**< Bootloader API table Root */
#define ROM_API_TABLE_ROOT ((const bootloader_api_table_t *)0x2001FF00U)


#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
 *
 *
 *      Enter bootloader Wrapper
 *
 *
 **********************************************************************************************************************/

/**
 * @brief Eneter specified Boot mode
 * @param [in] ctx Enter bootloader context
 * @retval status_invalid  Invalid parameters were deteced
 */
static inline hpm_stat_t rom_enter_bootloader(void *ctx)
{
    return ROM_API_TABLE_ROOT->run_bootloader(ctx);
}

/***********************************************************************************************************************
 *
 *
 *      XPI NOR Driver Wrapper
 *
 *
 **********************************************************************************************************************/

/**
 * @brief Setup API Runtime environment on demand
 */
static inline void rom_xpi_nor_api_setup(void)
{
    static const uint32_t s_setup_code[] = {
        0x300027f3, 0xf6b36719, 0xe68100e7, 0x90738fd9, 0x80823007,
    };
    if (ROM_API_TABLE_ROOT->version == 0x56010000UL) {
        typedef union {
             void (*callback)(void);
             const uint32_t *buffer;
        } api_setup_entry_t;
        volatile api_setup_entry_t entry;
        entry.buffer = &s_setup_code[0];
        entry.callback();
    }
}

/**
 * @brief Get XPI NOR configuration via cfg_option
 * @param [in] base XPI base address
 * @param [out] nor_cfg XPI NOR configuration structure
 * @param [in] cfg_option XPI NOR configuration option
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_get_config(XPI_Type *base,
                                                xpi_nor_config_t *nor_cfg,
                                                xpi_nor_config_option_t *cfg_option)
{
    rom_xpi_nor_api_setup();
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->get_config(base, nor_cfg, cfg_option);
}

/**
 * @brief Initialize XPI NOR based on nor_config
 * @param [in] base XPI base address
 * @param[in] nor_config XPI NOR configuration
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_init(XPI_Type *base, xpi_nor_config_t *nor_config)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->init(base, nor_config);
}

/**
 * @brief Erase specified FLASH region
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI nOR configuration
 * @param[in] start Erase address start address
 * @param[in] length Region size to be erased
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_erase(XPI_Type *base,
                                           xpi_xfer_channel_t channel,
                                           const xpi_nor_config_t *nor_config,
                                           uint32_t start,
                                           uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase(base, channel, nor_config, start, length);
}

/**
 * @brief Erase specified FLASH sector in blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @param[in] start Sector address
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_erase_sector(XPI_Type *base,
                                                  xpi_xfer_channel_t channel,
                                                  const xpi_nor_config_t *nor_config,
                                                  uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_sector(base, channel, nor_config, start);
}

/**
 * @brief Erase specified FLASH sector in non-blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @param[in] start Sector address
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_erase_sector_nonblocking(XPI_Type *base,
                                                              xpi_xfer_channel_t channel,
                                                              const xpi_nor_config_t *nor_config,
                                                              uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_sector_nonblocking(base, channel, nor_config, start);
}

/**
 * @brief Erase specified FLASH blcok in blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @param[in] start Block address
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_erase_block(XPI_Type *base,
                                                 xpi_xfer_channel_t channel,
                                                 const xpi_nor_config_t *nor_config,
                                                 uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_block(base, channel, nor_config, start);
}

/**
 * @brief Erase specified FLASH blcok in non-blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @param[in] start Block address
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_erase_block_nonblocking(XPI_Type *base,
                                                             xpi_xfer_channel_t channel,
                                                             const xpi_nor_config_t *nor_config,
                                                             uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_block_nonblocking(base, channel, nor_config, start);
}

/**
 * @brief Erase the whole FLASH in blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_erase_chip(XPI_Type *base,
                                                xpi_xfer_channel_t channel,
                                                const xpi_nor_config_t *nor_config)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_chip(base, channel, nor_config);
}

/**
 * @brief Erase the whole FLASH in non-blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_erase_chip_nonblocking(XPI_Type *base,
                                                            xpi_xfer_channel_t channel,
                                                            const xpi_nor_config_t *nor_config)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_chip_nonblocking(base, channel, nor_config);
}

/**
 * @brief Program data to specified FLASH address in blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @param[in] src data source address
 * @param[in] dst_addr Destination FLASH address
 * @param[in] length length of data to be programmed
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_program(XPI_Type *base,
                                             xpi_xfer_channel_t channel,
                                             const xpi_nor_config_t *nor_config,
                                             const uint32_t *src,
                                             uint32_t dst_addr,
                                             uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->program(base, channel, nor_config, src, dst_addr, length);
}

/**
 * @brief Page-Program data to specified FLASH address in non-blocking way
 * @param[in] base XPI base address
 * @param[in] channel XPI transfer channel
 * @param[in] nor_config XPI NOR configuration
 * @param[in] src data source address
 * @param[in] dst_addr Destination FLASH address
 * @param[in] length length of data to be programmed
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_page_program_nonblocking(XPI_Type *base,
                                                              xpi_xfer_channel_t channel,
                                                              const xpi_nor_config_t *nor_config,
                                                              const uint32_t *src,
                                                              uint32_t dst_addr,
                                                              uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if
        ->page_program_nonblocking(base, channel, nor_config, src, dst_addr, length);
}

/**
 * @brief Read data from specified FLASH address
 * @param [in] base XPI base address
 * @param [in] channel XPI transfer channel
 * @param [in] nor_config XPI NOR configuration
 * @param [in] dst Memory start address to store the data read out from FLASH
 * @param [in] start FLASH address for data read
 * @param [in] length length of data to be read out
 * @return API execution address
 */
static inline hpm_stat_t rom_xpi_nor_read(XPI_Type *base,
                                          xpi_xfer_channel_t channel,
                                          const xpi_nor_config_t *nor_config,
                                          uint32_t *dst,
                                          uint32_t start,
                                          uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->read(base, channel, nor_config, dst, start, length);
}

/**
 * @brief Automatically configure XPI NOR based on cfg_option
 * @param [in] base XPI base address
 * @param [out] config XPI NOR configuration structure
 * @param [in] cfg_option XPI NOR configuration option
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_auto_config(XPI_Type *base,
                                                 xpi_nor_config_t *config,
                                                 xpi_nor_config_option_t *cfg_option)
{
    rom_xpi_nor_api_setup();
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->auto_config(base, config, cfg_option);
}

/**
 * @brief Get XPI NOR properties
 * @param [in] base XPI base address
 * @param [in] nor_cfg XPI NOR configuration structure
 * @param [in] property_id
 * @param [out] value property value retrieved by this API
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_get_property(XPI_Type *base,
                                                  xpi_nor_config_t *nor_cfg,
                                                  uint32_t property_id,
                                                  uint32_t *value)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->get_property(base, nor_cfg, property_id, value);
}

/**
 * @brief Return the status register value on XPI NOR FLASH
 *
 * @param [in] base XPI base address
 * @param [in] channel XPI transfer channel
 * @param [in] nor_config XPI NOR configuration
 * @param [in] addr FLASH address offset
 * @param [out] out_status FLASH status register value
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_nor_get_status(XPI_Type *base, xpi_xfer_channel_t channel,
                                                const xpi_nor_config_t *nor_config, uint32_t addr,
                                                uint16_t *out_status)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->get_status(base, channel, nor_config, addr, out_status);
}

/**
 * @brief Configure the XPI Address Remapping Logic
 * @param [in] base XPI base address
 * @param [in] start Start Address (memory mapped address)
 * @param [in] len Size for the remapping region
 * @param [in] offset Relative address based on parameter "start"
 * @retval true is all parameters are valid
 * @retval false if any parameter is invalid
 */
ATTR_RAMFUNC
static inline bool rom_xpi_nor_remap_config(XPI_Type *base, uint32_t start, uint32_t len, uint32_t offset)
{
    if ((base != HPM_XPI0) || ((start & 0xFFF) != 0) || ((len & 0xFFF) != 0)
        || ((offset & 0xFFF) != 0)) {
        return false;
    }
    static const uint8_t k_mc_xpi_remap_config[] = {
        0x2e, 0x96, 0x23, 0x22, 0xc5, 0x42, 0x23, 0x24,
        0xd5, 0x42, 0x93, 0xe5, 0x15, 0x00, 0x23, 0x20,
        0xb5, 0x42, 0x05, 0x45, 0x82, 0x80,
    };
    typedef bool (*remap_config_cb_t)(XPI_Type *, uint32_t, uint32_t, uint32_t);
    remap_config_cb_t cb = (remap_config_cb_t) &k_mc_xpi_remap_config;
    bool result = cb(base, start, len, offset);
    ROM_API_TABLE_ROOT->xpi_driver_if->software_reset(base);
    fencei();
    return result;
}

/**
 * @brief Disable XPI Remapping logic
 * @param [in] base XPI base address
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_remap_disable(XPI_Type *base)
{
    static const uint8_t k_mc_xpi_remap_disable[] = {
        0x83, 0x27, 0x05, 0x42, 0xf9, 0x9b, 0x23, 0x20,
        0xf5, 0x42, 0x82, 0x80,
    };
    typedef void (*remap_disable_cb_t)(XPI_Type *);
    remap_disable_cb_t cb = (remap_disable_cb_t) &k_mc_xpi_remap_disable;
    cb(base);
    fencei();
}

/**
 * @brief Check whether XPI Remapping is enabled
 * @param [in] base XPI base address
 *
 * @retval true Remapping logic is enabled
 * @retval false Remapping logic is disabled
 */
ATTR_RAMFUNC
static inline bool rom_xpi_nor_is_remap_enabled(XPI_Type *base)
{
    static const uint8_t k_mc_xpi_remap_enabled[] = {
        0x03, 0x25, 0x05, 0x42, 0x05, 0x89, 0x82, 0x80,
    };
    typedef bool (*remap_chk_cb_t)(XPI_Type *);
    remap_chk_cb_t chk_cb = (remap_chk_cb_t) &k_mc_xpi_remap_enabled;
    return chk_cb(base);
}

/**
 * @brief Configure Specified EXiP Region
 * @param [in] base XPI base address
 * @param [in] index EXiP Region index
 * @param [in] param ExiP Region Parameter
 * @retval true All parameters are valid
 * @retval false Any parameter is invalid
 */
ATTR_RAMFUNC
static inline bool rom_xpi_nor_exip_region_config(XPI_Type *base, uint32_t index, exip_region_param_t *param)
{
    if (base != HPM_XPI0) {
        return false;
    }
    static const uint8_t k_mc_exip_region_config[] = {
        0x18, 0x4a, 0x9a, 0x05, 0x2e, 0x95, 0x85, 0x67,
        0xaa, 0x97, 0x23, 0xa4, 0xe7, 0xd0, 0x4c, 0x4a,
        0x14, 0x42, 0x58, 0x42, 0x23, 0xa6, 0xb7, 0xd0,
        0x4c, 0x46, 0x36, 0x97, 0x13, 0x77, 0x07, 0xc0,
        0x23, 0xa2, 0xb7, 0xd0, 0x0c, 0x46, 0x13, 0x67,
        0x37, 0x00, 0x05, 0x45, 0x23, 0xa0, 0xb7, 0xd0,
        0x0c, 0x4e, 0x23, 0xaa, 0xb7, 0xd0, 0x50, 0x4e,
        0x23, 0xa8, 0xc7, 0xd0, 0x23, 0xac, 0xd7, 0xd0,
        0x23, 0xae, 0xe7, 0xd0, 0x82, 0x80,
    };
    typedef void (*exip_region_config_cb_t)(XPI_Type *, uint32_t, exip_region_param_t *);
    exip_region_config_cb_t cb = (exip_region_config_cb_t) &k_mc_exip_region_config;
    cb(base, index, param);
    ROM_API_TABLE_ROOT->xpi_driver_if->software_reset(base);
    fencei();
    return true;
}

/**
 * @brief Disable EXiP Feature on specified EXiP Region
 * @param [in] base XPI base address
 * @param [in] index EXiP Region index
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_exip_region_disable(XPI_Type *base, uint32_t index)
{
    static const uint8_t k_mc_exip_region_disable[] = {
        0x9a, 0x05, 0x2e, 0x95, 0x85, 0x67, 0xaa, 0x97,
        0x03, 0xa7, 0xc7, 0xd1, 0x75, 0x9b, 0x23, 0xae,
        0xe7, 0xd0, 0x82, 0x80
    };
    typedef void (*exip_region_disable_cb_t)(XPI_Type *, uint32_t);
    exip_region_disable_cb_t cb = (exip_region_disable_cb_t) &k_mc_exip_region_disable;
    cb(base, index);
    ROM_API_TABLE_ROOT->xpi_driver_if->software_reset(base);
    fencei();
}

/**
 * @brief Enable global EXiP logic
 * @param [in] base XPI base address
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_exip_enable(XPI_Type *base)
{
    static const uint8_t k_mc_exip_enable[] = {
        0x85, 0x67, 0x3e, 0x95, 0x83, 0x27, 0x05, 0xc0,
        0x37, 0x07, 0x00, 0x80, 0xd9, 0x8f, 0x23, 0x20,
        0xf5, 0xc0, 0x82, 0x80
    };
    typedef void (*exip_enable_cb_t)(XPI_Type *);
    exip_enable_cb_t cb = (exip_enable_cb_t) &k_mc_exip_enable;
    cb(base);
}

/**
 * @brief Disable global EXiP logic
 * @param [in] base XPI base address
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_exip_disable(XPI_Type *base)
{
    static const uint8_t k_mc_exip_disable[] = {
        0x85, 0x67, 0x3e, 0x95, 0x83, 0x27, 0x05, 0xc0,
        0x86, 0x07, 0x85, 0x83, 0x23, 0x20, 0xf5, 0xc0,
        0x82, 0x80
    };
    typedef void (*exip_disable_cb_t)(XPI_Type *);
    exip_disable_cb_t cb = (exip_disable_cb_t) &k_mc_exip_disable;
    cb(base);
    ROM_API_TABLE_ROOT->xpi_driver_if->software_reset(base);
    fencei();
}

/***********************************************************************************************************************
 *
 *
 *      XPI RAM Driver Wrapper
 *
 *
 **********************************************************************************************************************/
/**
 * @brief Get XPI RAM configuration based on cfg_option
 * @param [in] base XPI base address
 * @param [out] ram_cfg XPI RAM configuration structure
 * @param [in] cfg_option XPI RAM configuration option
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_ram_get_config(XPI_Type *base,
                                                xpi_ram_config_t *ram_cfg,
                                                xpi_ram_config_option_t *cfg_option)
{
    return ROM_API_TABLE_ROOT->xpi_ram_driver_if->get_config(base, ram_cfg, cfg_option);
}

/**
 * @brief Initialize XPI RAM
 * @param [in] base XPI base address
 * @param [in] ram_cfg XPI ram configuration
 * @return API execution status
 */
static inline hpm_stat_t rom_xpi_ram_init(XPI_Type *base, xpi_ram_config_t *ram_cfg)
{
    return ROM_API_TABLE_ROOT->xpi_ram_driver_if->init(base, ram_cfg);
}

/***********************************************************************************************************************
 *
 *
 *      SDP Driver Wrapper
 *
 *
 **********************************************************************************************************************/
/**
 * @brief Initialize SDP IP
 */
static inline void rom_sdp_init(void)
{
    ROM_API_TABLE_ROOT->sdp_driver_if->sdp_ip_init();
}

/**
 * @brief De-initialize SDP IP
 */
static inline void rom_sdp_deinit(void)
{
    ROM_API_TABLE_ROOT->sdp_driver_if->sdp_ip_deinit();
}

/**
 * @brief Set AES key to SDP
 * @param [in] aes_ctx AES context
 * @param [in] key AES key buffer
 * @param [in] key_bits AES key-bit option
 * @param[in] key_idx AES key index
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_aes_set_key(sdp_aes_ctx_t *aes_ctx,
                                             const uint8_t *key,
                                             sdp_aes_key_bits_t key_bits,
                                             uint32_t key_idx)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->aes_set_key(aes_ctx, key, key_bits, key_idx);
}

/**
 * @brief SDP AES ECB crypto operation(Encrypt or Decrypt)
 * @param [in] aes_ctx AES context
 * @param [in] op AES operation: encrypt or decrypt
 * @param [in] len Data length for AES encryption/decryption
 * @param [in] in Input data
 * @param [out] out Output data
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_aes_crypt_ecb(sdp_aes_ctx_t *aes_ctx,
                                               sdp_aes_op_t op,
                                               uint32_t len,
                                               const uint8_t *in,
                                               uint8_t *out)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->aes_crypt_ecb(aes_ctx, op, len, in, out);
}

/**
 * @brief SDP AES CBC crypto operation(Encrypt or Decrypt)
 * @param [in] aes_ctx AES context
 * @param [in] op AES operation: encrypt or decrypt
 * @param [in] length Data length for AES encryption/decryption
 * @param [in] iv Initial vector/nonce
 * @param [in] in Input data
 * @param [out] out Output data
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_aes_crypt_cbc(sdp_aes_ctx_t *aes_ctx,
                                               sdp_aes_op_t op,
                                               uint32_t length,
                                               uint8_t iv[16],
                                               const uint8_t *in,
                                               uint8_t *out)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->aes_crypt_cbc(aes_ctx, op, length, iv, in, out);
}

/**
 * @brief Set SM4 key to SDP
 * @param [in] sm4_ctx SM4 context
 * @param [in] key SM4 key buffer
 * @param [in] key_bits SM4 key-bit option
 * @param[in] key_idx SM4 key index
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_sm4_set_key(sdp_sm4_ctx_t *sm4_ctx,
                                             const uint8_t *key,
                                             sdp_sm4_key_bits_t key_bits,
                                             uint32_t key_idx)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->sm4_set_key(sm4_ctx, key, key_bits, key_idx);
}

/**
 * @brief SDP SM4 ECB crypto operation(Encrypt or Decrypt)
 * @param [in] sm4_ctx SM4 context
 * @param [in] op SM4 operation: encrypt or decrypt
 * @param [in] len Data length for SM4 encryption/decryption
 * @param [in] in Input data
 * @param [out] out Output data
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_sm4_crypt_ecb(sdp_sm4_ctx_t *sm4_ctx,
                                               sdp_sm4_op_t op,
                                               uint32_t len,
                                               const uint8_t *in,
                                               uint8_t *out)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->sm4_crypt_ecb(sm4_ctx, op, len, in, out);
}

/**
 * @brief SDP SM4 CBC crypto operation(Encrypt or Decrypt)
 * @param [in] sm4_ctx SM4 context
 * @param [in] op SM4 operation: encrypt or decrypt
 * @param [in] length Data length for SM4 encryption/decryption
 * @param [in] iv Initial vector/nonce
 * @param [in] in Input data
 * @param [out] out Output data
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_sm4_crypt_cbc(sdp_sm4_ctx_t *sm4_ctx,
                                               sdp_sm4_op_t op,
                                               uint32_t length,
                                               uint8_t iv[16],
                                               const uint8_t *in,
                                               uint8_t *out)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->sm4_crypt_cbc(sm4_ctx, op, length, iv, in, out);
}

/**
 * @brief HASH initialization
 * @param [in] hash_ctx HASH context
 * @param [in] alg HASH algorithm
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_hash_init(sdp_hash_ctx_t *hash_ctx, sdp_hash_alg_t alg)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->hash_init(hash_ctx, alg);
}

/**
 * @brief HASH Update
 * @param [in] hash_ctx HASH context
 * @param [in] data Data for HASH operation
 * @param [in] length of the data for HASH operation
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_hash_update(sdp_hash_ctx_t *hash_ctx, const uint8_t *data, uint32_t length)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->hash_update(hash_ctx, data, length);
}

/**
 * @brief HASH finialize
 * @param [in] hash_ctx HASH context
 * @param [out] digest the output digest
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_hash_finish(sdp_hash_ctx_t *hash_ctx, uint8_t *digest)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->hash_finish(hash_ctx, digest);
}

/**
 * @brief SDP memcpy operation
 * @param [in] dma_ctx DMA context
 * @param [out] dst Destination address for memcpy
 * @param [in] src Source address for memcpy
 * @param [in] length Size of data for memcpy operation
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_memcpy(sdp_dma_ctx_t *dma_ctx, void *dst, const void *src, uint32_t length)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->memcpy(dma_ctx, dst, src, length);
}

/**
 * @brief SDP memset operation
 * @param [in] dma_ctx DMA context
 * @param [out] dst Destination address for memset
 * @param [in] pattern pattern for memset
 * @param [in] length Size of data for memset operation
 * @return API execution status
 */
static inline hpm_stat_t rom_sdp_memset(sdp_dma_ctx_t *dma_ctx, void *dst, uint8_t pattern, uint32_t length)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->memset(dma_ctx, dst, pattern, length);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */


#endif /* HPM_ROMAPI_H */
