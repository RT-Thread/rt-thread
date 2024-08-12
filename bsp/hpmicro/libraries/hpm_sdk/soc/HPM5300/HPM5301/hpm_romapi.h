/*
 * Copyright (c) 2023 HPMicro
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
#include "hpm_soc_feature.h"

/* XPI0 base address */
#define HPM_XPI0_BASE (0xF3000000UL)                /**< XPI0 Base address */
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

typedef struct {
    uint32_t region_start;
    uint32_t region_end;
    uint8_t aes_key[16];
    uint8_t nonce[8];
    uint8_t index;
    bool enable;
    bool valid;
    bool lock;
} exip_region_context_t;

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
 * @brief EXIP driver interface
 */
typedef struct {
    uint32_t version;
    hpm_stat_t (*enable)(XPI_Type *base);
    hpm_stat_t (*disable)(XPI_Type *base);
    hpm_stat_t (*lock_reg_access)(XPI_Type *base);
    hpm_stat_t (*configure_region)(XPI_Type *base, const exip_region_context_t *ctx);

    bool (*remap_config)(XPI_Type *base, uint32_t start, uint32_t len, uint32_t offset);
    bool (*remap_enabled)(XPI_Type *base);
    void (*remap_disable)(XPI_Type *base);
    bool (*exip_region_config)(XPI_Type *base, uint32_t index, exip_region_param_t *param);
    void (*exip_region_disable)(XPI_Type *base, uint32_t index);
} exip_driver_interface_t;

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
    const uint32_t reserved0;
    const uint32_t reserved[4];
    const exip_driver_interface_t *exip_api_if;
    const uint32_t family_id;
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
    hpm_stat_t status = ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase(base, channel, nor_config, start, length);
    fencei();
    return status;
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
    hpm_stat_t status = ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_sector(base, channel, nor_config, start);
    fencei();
    return status;
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
    hpm_stat_t status = ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_block(base, channel, nor_config, start);
    fencei();
    return status;
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
    hpm_stat_t status = ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_chip_nonblocking(base, channel, nor_config);
    fencei();
    return status;
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
    hpm_stat_t status = ROM_API_TABLE_ROOT->xpi_nor_driver_if->program(base, channel, nor_config, src, dst_addr, length);
    fencei();
    return status;
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
static inline hpm_stat_t rom_xpi_nor_get_status(XPI_Type *base,
                                                xpi_xfer_channel_t channel,
                                                const xpi_nor_config_t *nor_config,
                                                uint32_t addr,
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
    return ROM_API_TABLE_ROOT->exip_api_if->remap_config(base, start, len, offset);
}

/**
 * @brief Disable XPI Remapping logic
 * @param [in] base XPI base address
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_remap_disable(XPI_Type *base)
{
    ROM_API_TABLE_ROOT->exip_api_if->remap_disable(base);
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
    return ROM_API_TABLE_ROOT->exip_api_if->remap_enabled(base);
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
    bool result = ROM_API_TABLE_ROOT->exip_api_if->exip_region_config(base, index, param);
    ROM_API_TABLE_ROOT->xpi_driver_if->software_reset(base);
    fencei();
    return result;
}

/**
 * @brief Disable EXiP Feature on specified EXiP Region
 * @param [in] base XPI base address
 * @param [in] index EXiP Region index
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_exip_region_disable(XPI_Type *base, uint32_t index)
{
    ROM_API_TABLE_ROOT->exip_api_if->exip_region_disable(base, index);
    fencei();
}

/**
 * @brief Enable global EXiP logic
 * @param [in] base XPI base address
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_exip_enable(XPI_Type *base)
{
    ROM_API_TABLE_ROOT->exip_api_if->enable(base);
    fencei();
}

/**
 * @brief Disable global EXiP logic
 * @param [in] base XPI base address
 */
ATTR_RAMFUNC
static inline void rom_xpi_nor_exip_disable(XPI_Type *base)
{
    ROM_API_TABLE_ROOT->exip_api_if->disable(base);
    fencei();
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */


#endif /* HPM_ROMAPI_H */
