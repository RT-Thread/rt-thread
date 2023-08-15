/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ROMAPI_XPI_NOR_DEF_H
#define HPM_ROMAPI_XPI_NOR_DEF_H

/**
 * @brief XPI NOR ROM APIs
 * @defgroup xpi_nor_interface XPI NOR driver APIs
 * @ingroup romapi_interfaces
 * @{
 */


#include "hpm_common.h"
#include "hpm_romapi_xpi_def.h"

#define XPI_NOR_CFG_TAG 0x524f4E58U /**< ASCII: "XNOR" */

/**
 * @brief XPI NOR properties
 */
enum {
    xpi_nor_property_total_size,                            /**< Total size in bytes */
    xpi_nor_property_page_size,                             /**< Page size in bytes */
    xpi_nor_property_sector_size,                           /**<sector size in bytes */
    xpi_nor_property_block_size,                            /**< block size in bytes */
    xpi_nor_property_max = xpi_nor_property_block_size,
};


/**
 * @brief XPI NOR safe frequency option
 */
enum {
    xpi_nor_clk_safe_clk_freq = 1,
};

/**
 * @brief XPI NOR miscellaneous options
 */
enum {
    xpi_nor_option_misc_spi_only = 1,           /**< SPI only */
    xpi_nor_option_misc_internal_loopback = 2,  /**< Internal loopback mode */
    xpi_nor_option_misc_ext_dqs = 3,            /**< External DQS pin */
};

/**
 * @brief XPI NOR connection option
 */
enum {
    xpi_nor_connection_sel_chna_cs0,               /**< Channel A, CS0 */
    xpi_nor_connection_sel_chnb_cs0,               /**< Channel B, CS0 */
    xpi_nor_connection_sel_chna_cs0_chnb_cs0,     /**< Channel A + Channel B, CS0 */
    xpi_nor_connection_sel_chna_cs0_cs1,           /**< Channel A, CS0 + CS1 */
    xpi_nor_connection_sel_chnb_cs0_cs1            /**< Channel B, CS0 + CS1 */
};

/**
 * @brief QE bit enable sequence option
 */
typedef enum {
    xpi_nor_quad_en_auto_or_ignore = 0U,                        /**< Auto enable or ignore */
    xpi_nor_quad_en_set_bit6_in_status_reg1 = 1U,               /**< QE bit is at bit6 in Status register 1 */
    xpi_nor_quad_en_set_bit1_in_status_reg2 = 2U,               /**< QE bit is at bit1 in Status register 2 register 2 */
    xpi_nor_quad_en_set_bit7_in_status_reg2 = 3U,               /**< QE bit is at bit7 in Status register 2 */
    xpi_nor_quad_en_set_bi1_in_status_reg2_via_0x31_cmd = 4U,   /**< QE bit is in status register 2 and configured by CMD 0x31 */
} xpi_nor_quad_enable_seq_t;

/**
 * @brief XPI working mode
 */
typedef enum {
    xpi_working_mode_extend_spi,    /**< XPI works in extended SPI mode, including 1-1-1, 1-2-2, 1-4-4, 1-8-8 */
    xpi_working_mode_xpi,           /**< XPI works in XPI mode, including, 1-1-1, 2-2-2, 4-4-4, 8-8-8 */
    xpi_working_mode_hyperbus,      /**< XPI works in HyperBus mode */
} xpi_working_mode_t;


/**
 * @brief XPI NOR configuration command type
 */
typedef enum {
    xpi_nor_cfg_cmd_type_no_cfg = 0U,   /**< No configuration */
    xpi_nor_cfg_cmd_type_generic = 1U,  /**< Generic configuration */
    xpi_nor_cfg_cmd_type_spi2xpi = 2U,  /**< SPI to XPI mode */
    xpi_nor_cfg_cmd_type_xpi2spi = 3U,  /**< XPI to SPI mode */
} xpi_nor_cfg_cmd_type_t;

/**
 * @brief XPI NOR probe options
 */
typedef enum {
    xpi_nor_probe_sfdp_sdr = 0U,    /**< Probe FLASH using SFDP and set FLASH to SDR mode */
    xpi_nor_probe_sfdp_ddr = 1U,    /**< Probe FLASH using SDP and set FLASH to DDR mode */
    xpi_nor_quad_read_0xeb = 2U,    /**< Set FLASH to default Quad I/O read in SDR mode */
    xpi_nor_dual_read_0xbb = 3U,    /**< Set FLASH to default Dual I/O read in SDR mode */
    xpi_nor_hyperbus_1v8 = 4U,      /**< Probe FLASH using HyperBus in 1.8V voltage */
    xpi_nor_hyperbus_3v0 = 5U,      /**< Probe FLASH using HyperBus in 3.0V voltage */
    xpi_nor_octabus_ddr = 6U,       /**< Probe FLASH using Macronix OctaBus and configure FLASH to OPI DDR mode */
    xpi_nor_octabus_sdr = 7U,       /**< Probe FLASH using Macronix OctaBus and configure FLASH to OPI SDR mode */
    xpi_nor_xccela_ddr = 8U,        /**< Probe FLASH using Xccela Protocol and configure FLASH to OPI DDR mode */
    xpi_nor_xccela_sdr = 9U,        /**< Probe FLASH using Xccela Protocol and configure FLASH to SDR mode */
    xpi_nor_ecoxip_ddr = 10U,       /**< Probe FLASH using EcoXiP Protocol and configure FLASH to OPI DDR mode */
    xpi_nor_ecoxip_sdr = 11U,       /**< Probe FLASH using EcoXiP Protocol and configure FLASH to SDR mode */
} xpi_nor_probe_t;

/**
 * @brief Standard XPI NOR seuqnce index definitions
 */
typedef enum {
    xpi_std_nor_seq_idx_read = 0U,                     /**< 0 - Read */
    xpi_std_nor_seq_idx_page_program = 1U,             /**< 1 - Page Program */
    xpi_std_nor_seq_idx_read_status = 2U,              /**< 2 - Read Status */
    xpi_std_nor_seq_idx_read_status_xpi = 3U,          /**< 3 - Read Status in xSPI mode */
    xpi_std_nor_seq_idx_write_enable = 4U,             /**< 4 - Write Enable */
    xpi_std_nor_seq_idx_write_enable_xpi = 5U,         /**< 5 - Write Enable in xSPI mode */
    xpi_std_nor_seq_idx_erase_sector = 6U,             /**< 6 - Erase sector */
    xpi_std_nor_seq_idx_erase_block = 7U,              /**< 7 - Erase block */
    xpi_std_nor_seq_idx_erase_chip = 8U,               /**< 8 - Erase full chip */
    xpi_std_nor_seq_idx_max = 9,                       /**< 9 */
} xpi_std_nor_instr_idx_t;

/**
 * @brief XPI NOR option tag
 */
#define XPI_NOR_CFG_OPTION_TAG (0xfcf90U)

/**
 * @brief XPI NOR configuration option
 *        The ROM SW can detect the FLASH configuration based on the following structure specified by the end-user
 */
typedef struct {
    union {
        struct {
            uint32_t words: 4;       /**< Option words, exclude the header itself */
            uint32_t reserved: 8;    /**< Reserved for future use */
            uint32_t tag: 20;        /**< Must be 0xfcf90 */
        };
        uint32_t U;
    } header;
    union {
        struct {
            uint32_t freq_opt: 4;                /**< 1 - 30MHz, others, SoC specific setting */
            uint32_t misc: 4;                    /**< Not used for now */
            uint32_t dummy_cycles: 8;            /**< 0 - Auto detected/ use predefined value, others - specified by end-user */
            uint32_t quad_enable_seq: 4;         /**< See the xpi_nor_quad_enable_seq_t definitions for more details */
            uint32_t cmd_pads_after_init: 4;     /**< See the xpi_data_pad_t definitions for more details */
            uint32_t cmd_pads_after_por: 4;      /**< See the xpi_data_pad_t definitions for more details */
            uint32_t probe_type: 4;              /**< See the xpi_nor_probe_t definitions for more details */
        };
        uint32_t U;
    } option0;
    union {
        struct {
            uint32_t drive_strength: 8;      /**< IO drive strength, 0 - pre-defined, Others - specified by end-user */
            uint32_t connection_sel: 4;      /**< Device connection selection: 0 - PORTA, 1 - PORTB, 2 - Parallel mode */
            uint32_t pin_group_sel: 4;       /**< Pin group selection, 0 - 1st group, 1 - 2nd group, by default, the pin group is 1st group */
            uint32_t io_voltage: 4;          /**< SoC pad voltage, 0 - 3.0V, 1-1.8V */
            uint32_t reserved: 12;           /**< Reserved for future use */
        };
        uint32_t U;
    } option1;
    union {
        struct {
            uint32_t flash_size_option:8;               /**< FLASH size option */
            uint32_t flash_sector_size_option:4;        /**< FLASH sector size option */
            uint32_t flash_sector_erase_cmd_option:4;   /**< Sector Erase command option */
            uint32_t reserved:20;
        };
        uint32_t U;
    } option2;
} xpi_nor_config_option_t;

/**
 * @brief Sector size options
 */
enum {
    serial_nor_sector_size_4kb,     /**< Sector size: 4KB */
    serial_nor_sector_size_32kb,    /**< Sector size: 32KB */
    serial_nor_sector_size_64kb,    /**< Sector size: 64KB */
    serial_nor_sector_size_256kb,   /**< Sector size: 256KB */
};

/**
 * @brief Sector erase command options
 */
enum  {
    serial_nor_erase_type_4kb,      /**< Sector erase command: 4KB Erase */
    serial_nor_erase_type_32kb,     /**< Sector erase command: 32KB Erase */
    serial_nor_erase_type_64kb,     /**< Sector erase command: 64KB Erase */
    serial_nor_erase_type_256kb,    /**< Sector erase command: 256KB Erase */
};

/**
 * @brief FLASH size options
 */
enum {
    flash_size_4mb,     /**< FLASH size: 4MB */
    flash_size_8mb,     /**< FLASH size: 8MB */
    flash_size_16mb,    /**< FLASH size: 16MB */
};

/**
 * @brief Device Mode confiuration structure
 */
typedef struct {
    uint8_t cfg_cmd_type;       /**< Configuration command type */
    uint8_t param_size;         /**< Size for parameter */
} device_mode_cfg_t;

/**
 * @brief Device mode parameter structure
 */
typedef struct {
    uint32_t instr_seq[4];  /**< Command Instruction sequence*/
    uint32_t param;         /**< Parameter */
} device_mode_param_t;

/**
 * @brief XPI NOR device information structure
 */
typedef struct {
    uint32_t size_in_kbytes;                /**< Device Size in Kilobytes, offset 0x00 */
    uint16_t page_size;                     /**< Page size, offset 0x04 */
    uint16_t sector_size_kbytes;            /**< Sector size in kilobytes, offset 0x06 */
    uint16_t block_size_kbytes;             /**< Block size in kilobytes, offset 0x08 */
    uint8_t busy_offset;                    /**< Busy offset, offset 0x0a */
    uint8_t busy_polarity;                  /**< Busy polarity, offset 0x0b */
    uint8_t data_pads;                      /**< Device Size in Kilobytes, offset 0x0c */
    uint8_t en_ddr_mode;                    /**< Enable DDR mode, offset 0x0d */
    uint8_t clk_freq_for_device_cfg;        /**< Clk frequency for device configuration offset 0x0e */
    uint8_t working_mode_por;               /**< Working mode after POR reset offset 0x0f */
    uint8_t working_mode;                   /**< The device working mode, offset 0x10 */
    uint8_t en_diff_clk;                    /**< Enable Differential clock, offset 0x11 */
    uint8_t data_valid_time;                /**< Data valid time, in 0.1ns, offset 0x12 */
    uint8_t en_half_clk_for_non_read_cmd;   /**< Enable half clock for non-read command, offset 0x13 */
    uint8_t clk_freq_for_non_read_cmd;      /**< Enable safe clock for non-read command, offset 0x14 */
    uint8_t dll_dly_target;                 /**< XPI DLL Delay Target, offset 0x15 */
    uint8_t io_voltage;                     /**< IO voltage, offset 0x16 */
    uint8_t reserved0;                      /**< Reserved for future use, offset 0x17 */
    uint8_t cs_hold_time;                   /**< CS hold time, 0 - default value, others - user specified value, offset 0x18 */
    uint8_t cs_setup_time;                  /**< CS setup time, 0 - default value, others - user specified value, offset 0x19 */
    uint8_t cs_interval;                    /**< CS interval, intervals between to CS active, offset 0x1a */
    uint8_t en_dev_mode_cfg;                /**< Enable device mode configuration, offset 0x1b */
    uint32_t flash_state_ctx;               /**< Flash state context, offset 0x1c  */
    device_mode_cfg_t mode_cfg_list[2];     /**< Mode configuration sequences, offset 0x20 */
    uint32_t mode_cfg_param[2];             /**< Mode configuration parameters, offset 0x24 */
    uint32_t reserved1;                     /**< Reserved for future use, offset 0x2C */
    struct {
        uint32_t entry[4];
    } cfg_instr_seq[2];                      /**< Mode Configuration Instruction sequence, offset 0x30 */
} xpi_device_info_t;

/**
 * @brief XPI NOR configuration structure
 */
typedef struct {
    uint32_t tag;                         /**< Must be "XNOR", offset 0x000 */
    uint32_t reserved0;                   /**< Reserved for future use, offset 0x004 */
    uint8_t rxclk_src;                    /**< RXCLKSRC value, offset 0x008 */
    uint8_t clk_freq;                     /**< Clock frequency, offset 0x009 */
    uint8_t drive_strength;               /**< Drive strength, offset 0x0a */
    uint8_t column_addr_size;             /**< Column address size, offset 0x0b */
    uint8_t rxclk_src_for_init;           /**< RXCLKSRC during FLASH initialization, offset 0x0c */
    uint8_t config_in_progress;           /**< Indicate whether device configuration is in progress, offset: 0x0d */
    uint8_t reserved[2];                  /**< Reserved for future use, offset 0x00f */
    struct {
        uint8_t enable;                   /**<  Port enable flag, 0 - not enabled, 1 - enabled */
        uint8_t group;                    /**< 0 - 1st IO group, 1 - 2nd IO group */
        uint8_t reserved[2];
    } chn_info[4];                        /**< Device connection information */
    xpi_device_info_t device_info;       /**< Device info, offset 0x20 */
    xpi_instr_seq_t instr_set[xpi_std_nor_seq_idx_max];/**< Standard instruction sequence table, offset 0x70 */
} xpi_nor_config_t;

/**
 * @brief FLASH runtime context structure
 */
typedef union {
    struct {
        uint32_t wait_time: 7;              /**< Wait time */
        uint32_t wait_time_unit: 1;         /**< 0 - 10us, 1 - 1ms */
        uint32_t reset_gpio: 8;             /**<Reset GPIO */
        uint32_t restore_sequence: 4;       /**<Restore sequence */
        uint32_t exit_no_cmd_sequence: 4;   /**< Exit no-cmd sequence */
        uint32_t current_mode: 4;           /**< Current FLASH mode */
        uint32_t por_mode: 4;               /**< FLASH mode upon Power-on Reset */
    };
    uint32_t U;
} flash_run_context_t;

/**
 * @brief XPI NOR API error codes
 */
enum {
    status_xpi_nor_sfdp_not_found = MAKE_STATUS(status_group_xpi_nor, 0),                       /**<  SFDP table was not found */
    status_xpi_nor_ddr_read_dummy_cycle_probe_failed = MAKE_STATUS(status_group_xpi_nor, 1),    /**<  Probing Dummy cyles for DDR read failed */
    status_xpi_nor_flash_not_found = MAKE_STATUS(status_group_xpi_nor, 2),                      /**< FLASH was not detected */
};

/**
 * @}
 */

#endif /* HPM_ROMAPI_XPI_NOR_DEF_H */
