/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup OSPI_W
 * @{
 **********************************************************************************************************************/

#ifndef R_OSPI_W_H
#define R_OSPI_W_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_ospi_w_cfg.h"
#include "r_spi_flash_api.h"

#include "../../src/bsp/mcu/ra6w1/sdk_defs.h"
#if OSPI_W_CFG_DMAC_SUPPORT_ENABLE
 #include "r_transfer_api.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define OSPI_W_STATREG_PR_CMD                 0x01
#define OSPI_W_READ_CMD                       0x03
#define OSPI_W_PAGEPR_CMD                     0x02
#define OSPI_W_STATREG_R_CMD                  0x05
#define OSPI_W_WREN_CMD                       0x06
#define OSPI_W_SECTOR_ERASE_CMD               0x20
#define OSPI_W_RESET_EN_CMD                   0x66
#define OSPI_W_RESET_CMD                      0x99
#define OSPI_W_EXIT_DPD_CMD                   0xAB
#define OSPI_W_EXIT_DPD_CMD_INV               0x54
#define OSPI_W_DUMMY_CMD                      0x00
#define OSPI_W_QUAD_PAGEPR_CMD                0x33
#define OSPI_W_QUAD_PAGEPR_CMD_2              0x38
#define OSPI_W_SINGLE_ADDR_QUAD_PAGEPR_CMD    0x32

#define OSPI_W_AUTOMODE_BASE_ADD              BSP_FEATURE_OSPI_W_DEVICE_0_START_ADDRESS // (0x2A000000)

#define SPI_READ_STATUS_REG_CMD               0x05
#define OSPI_WRITE_ENABLE_CMD                 0x06
#define OSPI_FAST_READ3B_CMD                  0x0B
#define OSPI_FAST_READ4B_CMD                  0x0C
#define OSPI_EXIT_CONTINUOUS_MODE_CMD         (0xFF)

#define OSPI_FLASH_PAGE_SIZE                  (0x100)
#define OSPI_FLASH_SECTOR_LENGTH              (0x1000)
#define ON_STACK_BUFFER_SIZE                  256

typedef union
{
    __IO uint32_t data32;
    __IO uint16_t data16;
    __IO uint8_t  data8;
} ospi_w_data_t;

typedef struct                         /*!< (@ 0x36000000) OQSPIF Structure */
{
    __IOM uint32_t      ospi_reserved0;
    __IOM uint32_t      ospi_reserved1;
    __IOM uint32_t      ospi_reserved2;
    __IOM uint32_t      ospi_reserved3;
    __IOM uint32_t      ospi_reserved4;
    __IOM uint32_t      ospi_reserved5;
    __IOM ospi_w_data_t OQSPIF_WRITEDATA_REG;
    __IOM ospi_w_data_t OQSPIF_READDATA_REG;
    __IOM ospi_w_data_t OQSPIF_DUMMYDATA_REG;
} ospi_w_regs_t;

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* OQSPI Bus status */
typedef enum
{
    OSPI_W_DEVICE_BUS_STATUS_IDLE   = 0, /* The SPI Bus is idle */
    OSPI_W_DEVICE_BUS_STATUS_ACTIVE = 1, /* The SPI Bus is active. Read data, write data
                                          * or dummy data activity is in progress.*/
} ospi_w_device_bus_status;

/** OSPI_W clock divider */
typedef enum
{
    OSPI_W_DEVICE_CLK_DIV_1 = 0,       /**< divide by 1 */
    OSPI_W_DEVICE_CLK_DIV_2 = 1,       /**< divide by 2 */
    OSPI_W_DEVICE_CLK_DIV_4 = 2,       /**< divide by 4 */
    OSPI_W_DEVICE_CLK_DIV_8 = 3        /**< divide by 8 */
} ospi_w_device_clk_div;

/** OSPI_W bus mode */
typedef enum
{
    OSPI_W_DEVICE_BUS_MODE_NOT_SET = -1, /**< Bus mode not set */
    OSPI_W_DEVICE_BUS_MODE_SINGLE  = 0,  /**< Bus mode in single mode */
    OSPI_W_DEVICE_BUS_MODE_DUAL    = 1,  /**< Bus mode in dual mode */
    OSPI_W_DEVICE_BUS_MODE_QUAD    = 2,  /**< Bus mode in quad mode */
    OSPI_W_DEVICE_BUS_MODE_OCTA    = 3   /**< Bus mode in octa mode */
} ospi_w_device_bus_mode;

/** OSPI_W memory access mode */
typedef enum
{
    OSPI_W_DEVICE_ACCESS_MODE_MANUAL = 0, /**< Manual Mode is selected */
    OSPI_W_DEVICE_ACCESS_MODE_AUTO   = 1  /**< Auto Mode is selected */
} ospi_w_device_access_mode;

/** OSPI_W clock mode */
typedef enum
{
    OSPI_W_DEVICE_CLK_MODE_LOW  = 0,   /**< Mode 0: OSPI_SCK is low when OSPI_CS is high. */
    OSPI_W_DEVICE_CLK_MODE_HIGH = 1    /**< Mode 3: OSPI_SCK is high when OSPI_CS is high. */
} ospi_w_device_clk_mode;

/** OSPI_W pad direction */
typedef enum
{
    OSPI_W_DEVICE_IO_DIR_AUTO_SEL = 0, /**< The OQSPI pad is determined by the controller. */
    OSPI_W_DEVICE_IO_DIR_OUTPUT   = 1  /**< The OQSPI pad is output */
} ospi_w_device_io_dir;

/** OSPI_W IO2/IO3 pad value */
typedef enum
{
    OSPI_W_DEVICE_IO_VALUE_LOW  = 0,
    OSPI_W_DEVICE_IO_VALUE_HIGH = 1,
} ospi_w_device_io_value;

/** OSPI_W IO4-7 pads values */
typedef enum
{
    OSPI_W_DEVICE_IO4_7_VALUE_0000 = 0,
    OSPI_W_DEVICE_IO4_7_VALUE_1111 = 0xF,
} ospi_w_device_io4_7_value;

/** OSPI_W HREADY signal mode when accessing the WRITEDATA, READDATA and DUMMYDATA registers */
typedef enum
{
    OSPI_W_DEVICE_HREADY_MODE_WAIT    = 0, /**< Adds wait states via hready signal when an
                                            * accessing the OSPIC_WRITEDATA, OSPIC_READDATA
                                            * and OSPIC_DUMMYDATA registers. */
    OSPI_W_DEVICE_HREADY_MODE_NO_WAIT = 1  /**< Don't add wait states via the HREADY signal */
} ospi_w_device_hready_mode;

/** OSPI_W clock edge setting for the sampling of the incoming data when the read pipe is disabled */
typedef enum
{
    OSPI_W_DEVICE_SAMPLING_EDGE_POS = 0, /**< The incoming data sampling is triggered by the
                                          * positive edge of OSPI_W clock signal */
    OSPI_W_DEVICE_SAMPLING_EDGE_NEG = 1  /**< The incoming data sampling is triggered by the
                                          * negative edge of OSPI_W clock signal */
} ospi_w_device_sampling_edge;

/** OSPI_W read pipe setting
 *  When read pipe is disabled the sampling clock is determined by @ref ospi_w_device_sampling_edge
 *       while when is enabled by @ref ospi_w_device_read_pipe_delay. In ASIC is always recommended to
 *       enable read pipe and set the @ref ospi_w_device_read_pipe_delay to the optimal value.
 */
typedef enum
{
    OSPI_W_DEVICE_READ_PIPE_DISABLE = 0,
    OSPI_W_DEVICE_READ_PIPE_ENABLE  = 1,
} ospi_w_device_read_pipe;

/** OSPI_W Read pipe clock delay in relation to the falling edge of OSPI_SCK */
typedef enum
{
    OSPI_W_DEVICE_READ_PIPE_DELAY_0 = 0,
    OSPI_W_DEVICE_READ_PIPE_DELAY_1 = 1,
    OSPI_W_DEVICE_READ_PIPE_DELAY_2 = 2,
    OSPI_W_DEVICE_READ_PIPE_DELAY_3 = 3,
    OSPI_W_DEVICE_READ_PIPE_DELAY_4 = 4,
    OSPI_W_DEVICE_READ_PIPE_DELAY_5 = 5,
    OSPI_W_DEVICE_READ_PIPE_DELAY_6 = 6,
    OSPI_W_DEVICE_READ_PIPE_DELAY_7 = 7,
} ospi_w_device_read_pipe_delay;

/*
 * OSPI_W behavior in auto mode when the internal buffer is full and there are more data to be retrieved for the current burst
 */
typedef enum
{
    OSPI_W_DEVICE_FULL_BUFFER_MODE_BLOCK     = 0, /* The access in the flash device is not
                                                   * terminated when the internal buffer has
                                                   * no empty space. In this case the OSPI_W
                                                   * clock is blocked until there is free
                                                   * space */
    OSPI_W_DEVICE_FULL_BUFFER_MODE_TERMINATE = 1, /* The access in the flash device is
                                                   * terminated when the internal buffer has
                                                   * no empty space. A new access in the
                                                   * flash device will be initiated when
                                                   * the requested addresses are not present
                                                   * in the internal buffer */
} ospi_w_device_full_buffer_mode;

/** OSPI_W memory address size */
typedef enum
{
    OSPI_W_DEVICE_ADDR_SIZE_24 = 0,    /**< 24 bits address */
    OSPI_W_DEVICE_ADDR_SIZE_32 = 1     /**< 32 bits address */
} ospi_w_device_addr_size;

/** OSPI_W number of bytes of the instruction code in automode */
typedef enum
{
    OSPI_W_DEVICE_INSTRUCT_SZ_1_BYTE  = 0, /**< The instruction code is one byte */
    OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES = 1, /**< The instruction code is two bytes. The second
                                            * byte equals to the inverse value of the first
                                            * byte */
} ospi_w_device_instruct_sz;

/** OSPI_W clock cycle where the bus switches to Hi-Z during the transmission of dummy bytes */
typedef enum
{
    OSPI_W_DEVICE_DUMMY_MODE_LAST_CLK   = 0, /**< Switch to Hi-Z on the last clock */
    OSPI_W_DEVICE_DUMMY_MODE_LAST_2_CLK = 1, /**< Switch to  Hi-Z on the last two clocks */
} ospi_w_device_dummy_mode;

/*
 * OSPI_W direction change method in manual mode
 */
typedef enum
{
    OSPI_W_DEVICE_DIR_CHANGE_MODE_EACH_ACCESS  = 0, /* The bus direction switches to input
                                                     * after each access */
    OSPI_W_DEVICE_DIR_CHANGE_MODE_DUMMY_ACCESS = 1, /* The bus direction switches to input
                                                     * only after a dummy access */
} ospi_w_device_dir_change_mode;

/*
 * OSPI_W AHB bus error response when a read is performed in the address space where the
 *        flash device is mapped and the Auto mode is not enabled
 */
typedef enum
{
    OSPI_W_DEVICE_MAPPED_ADDR_RD_ACC_RESPONSE_IGNORE    = 0, /* The read access is ignored and
                                                              * there is no error due to the read
                                                              * access */
    OSPI_W_DEVICE_MAPPED_ADDR_RD_ACC_RESPONSE_AHB_ERROR = 1, /* Respond with an AHB bus error */
} ospi_w_device_mapped_addr_rd_acc_response;

/*
 * OSPI_W burst length in automode when the read access in the AHB bus is an incremental
 *        burst of unspecified length
 *
 *   This setting is useful in case that the masters that make use of the incremental burst
 *        of unspecified length, require no more than 8 bytes. Set this setting to @ref
 *        OSPI_W_DEVICE_BURST_LEN_LIMIT_8_BYTES in order to optimize the cache controller read access
 *        performance.
 */
typedef enum
{
    OSPI_W_DEVICE_BURST_LEN_LIMIT_UNSPECIFIED = 0, /* Unspecified length of the burst */
    OSPI_W_DEVICE_BURST_LEN_LIMIT_8_BYTES     = 1, /* The length of the burst is considered
                                                    * as equal to 8 bytes. The access in the
                                                    * flash device will be implemented by the
                                                    * controller as one or more different
                                                    * bursts, until the AHB bus access to be
                                                    * completed. Each burst in the flash
                                                    * device will have maximum length of 8
                                                    * bytes */
} ospi_w_device_burst_len_limit;

/** OSPI_W pads slew rate control */
typedef enum
{
    OSPI_W_DEVICE_SLEW_RATE_0 = 0,     /**< Rise = 1.7 V/ns, Fall = 1.9 V/ns (weak) */
    OSPI_W_DEVICE_SLEW_RATE_1 = 1,     /**< Rise = 2.0 V/ns, Fall = 2.3 V/ns */
    OSPI_W_DEVICE_SLEW_RATE_2 = 2,     /**< Rise = 2.3 V/ns, Fall = 2.6 V/ns */
    OSPI_W_DEVICE_SLEW_RATE_3 = 3      /**< Rise = 2.4 V/ns, Fall = 2.7 V/ns (strong) */
} ospi_w_device_slew_rate;

/**  OSPI_W pads drive current */
typedef enum
{
    OSPI_W_DEVICE_DRIVE_CURRENT_4  = 0, /**< 4 mA */
    OSPI_W_DEVICE_DRIVE_CURRENT_8  = 1, /**< 8 mA */
    OSPI_W_DEVICE_DRIVE_CURRENT_12 = 2, /**< 12 mA */
    OSPI_W_DEVICE_DRIVE_CURRENT_16 = 3, /**< 16 mA */
} ospi_w_device_drive_current;

/** OSPI_W extra byte setting in auto access mode */
typedef enum
{
    OSPI_W_DEVICE_EXTRA_BYTE_DISABLE = 0, /**< Don't send the extra byte */
    OSPI_W_DEVICE_EXTRA_BYTE_ENABLE  = 1, /**< Send the extra byte */
} ospi_w_device_extra_byte;

/*
 * OSPI_W extra byte half setting in auto access mode
 *
 * This setting is out of scope if the extra byte is disabled or transferred in Octal mode.
 *        Especially in the latter case keep this setting disabled.
 */
typedef enum
{
    OSPI_W_DEVICE_EXTRA_BYTE_HALF_DISABLE = 0, /* Transmit the complete extra byte */
    OSPI_W_DEVICE_EXTRA_BYTE_HALF_ENABLE  = 1, /* The output switches to Hi-Z during the
                                                * transmission of bits [3:0] of the extra byte */
} ospi_w_device_extra_byte_half;

/** OSPI_W Instruction mode in auto access mode */
typedef enum
{
    OSPI_W_DEVICE_INSTR_MODE_SEND_ANYTIME = 0, /**< Transmit instruction at any burst access */
    OSPI_W_DEVICE_INSTR_MODE_SEND_ONCE    = 1  /**< Transmit instruction only in the first access
                                                * after the selection of Auto Mode */
} ospi_w_device_instr_mode;

/*
 * OSPI_W wrapping burst mode in auto access mode
 */
typedef enum
{
    OSPI_W_DEVICE_WRAP_MODE_INSTR      = 0, /* The OSPIC_INST is the selected instruction at any
                                             * access */
    OSPI_W_DEVICE_WRAP_MODE_INSTR_WRAP = 1, /*  The OSPIC_INST_WB is the selected instruction at
                                             * any wrapping burst access */
} ospi_w_device_wrap_mode;

/*
 * OSPI_W data length of a wrapping burst in auto access mode
 */
typedef enum
{
    OSPI_W_DEVICE_WRAP_LEN_4BEAT  = 0, /* 4 beat wrapping burst */
    OSPI_W_DEVICE_WRAP_LEN_8BEAT  = 1, /* 8 beat wrapping burst */
    OSPI_W_DEVICE_WRAP_LEN_16BEAT = 2, /* 16 beat wrapping burst */
} ospi_w_device_wrap_len;

/*
 * OSPI_W data size of a wrapping burst in auto access mode
 */
typedef enum
{
    OSPI_W_DEVICE_WRAP_SIZE_8BITS  = 0, /* Byte access (8-bits) */
    OSPI_W_DEVICE_WRAP_SIZE_16BITS = 1, /* Half word access (16-bits) */
    OSPI_W_DEVICE_WRAP_SIZE_32BITS = 2, /* Word access (32-bits) */
} ospi_w_device_wrap_size;

/*
 * OSPI_W bus idle state (OSPI_CS high) duration (in OSPI_SCK clock cycles) between two
 *        consecutive instructions
 */
typedef enum
{
    OSPI_W_DEVICE_IDLE_STATE_DURATION_0 = 0,
    OSPI_W_DEVICE_IDLE_STATE_DURATION_1 = 1,
    OSPI_W_DEVICE_IDLE_STATE_DURATION_2 = 2,
    OSPI_W_DEVICE_IDLE_STATE_DURATION_3 = 3,
} ospi_w_device_idle_state_duration;

/*
 * OSPI_W device busy status setting
 */
typedef enum
{
    OSPI_W_DEVICE_BUSY_LOW  = 0,       /* The OQSPI device is busy when the corresponding bit is 0 */
    OSPI_W_DEVICE_BUSY_HIGH = 1        /* The OQSPI device is busy when the corresponding bit is 1 */
} ospi_w_device_busy;

/*
 * Select OSPI_W counter for counting a delay between device Status Register read instruction
 *        and erase or erase/resume instruction
 */
typedef enum
{
    OSPI_W_DEVICE_READ_STATUS_REG_CNT_RESSTS = 0, /* The counter value is determined by the field
                                                   * OSPIC_RESSTS_DLY and is clocked by OSPI_CLK */
    OSPI_W_DEVICE_READ_STATUS_REG_CNT_RESSUS = 1  /* The counter value is determined by the field
                                                   * OSPIC_RESSUS_DLY field and is clocked by a
                                                   * 222 kHz clock */
} ospi_w_device_read_status_reg_cnt;

/*
 * Defines the value that is transferred on the OSPI bus during the phase of the dummy bytes
 */
typedef enum
{
    OSPI_W_DEVICE_READ_STATUS_DUMMY_VAL_UNCHANGED   = 0, /* The controller keeps the data in the bus
                                                          * unchanged, until the bus direction
                                                          * changes to input mode */
    OSPI_W_DEVICE_READ_STATUS_DUMMY_VAL_FORCED_ZERO = 1, /* Forces the dummy bytes to get the zero
                                                          * value as long as the bus direction is
                                                          * not in input mode. Only IO pins which
                                                          * are relevant with the transfer mode of
                                                          * the dummy bytes get the zero value
                                                          * (according to bus mode of the dummy
                                                          * phase). */
} ospi_w_device_read_status_dummy_val;

/*
 * The status of sector/block erasing
 */
typedef enum
{
    OSPI_W_DEVICE_ERS_NO        = 0,   /* no erase                           */
    OSPI_W_DEVICE_ERS_PENDING   = 1,   /* pending erase request              */
    OSPI_W_DEVICE_ERS_RUNNING   = 2,   /* erase procedure is running         */
    OSPI_W_DEVICE_ERS_SUSPENDED = 3,   /* suspended erase procedure          */
    OSPI_W_DEVICE_ERS_FINISHING = 4    /* finishing the erase procedure      */
} ospi_w_device_ers;

/*
 *  OSPI_W manual mode configuration structure
 */
typedef struct
{
    ospi_w_device_dir_change_mode             dir_change_mode             : 1;
    ospi_w_device_mapped_addr_rd_acc_response mapped_addr_rd_acc_response : 1;
} ospi_w_device_manualmode_config_t;

/*
 *  OSPI_W automode configuration structure
 */
typedef struct
{
    ospi_w_device_full_buffer_mode full_buffer_mode : 1;
    ospi_w_device_instruct_sz      instruct_size    : 1;
    ospi_w_device_burst_len_limit  burst_len_limit  : 1;
} ospi_w_device_automode_config_t;

/** OSPI_W configuration structure */
typedef struct
{
    ospi_w_device_clk_div             clk_div         : 2; ///< Clock divider value
    ospi_w_device_bus_mode            bus_mode        : 3; ///< Read bus mode.
    ospi_w_device_access_mode         access_mode     : 1; ///< Access mode.
    ospi_w_device_clk_mode            clock_mode      : 1; ///< Clock mode
    ospi_w_device_io_dir              io2_dir         : 1; ///< IO2 direction.
    ospi_w_device_io_value            io2_value       : 1; ///< IO2 value.
    ospi_w_device_io_dir              io3_dir         : 1; ///< IO3 direction.
    ospi_w_device_io_value            io3_value       : 1; ///< IO3 value.
    ospi_w_device_io_dir              io4_7_dir       : 1; ///< IO4-7 direction.
    ospi_w_device_io4_7_value         io4_7_value     : 4; ///< IO4-7 value.
    ospi_w_device_hready_mode         hready_mode     : 1; ///< HREADY mode.
    ospi_w_device_sampling_edge       sampling_edge   : 1; ///< Sampling_edge.
    ospi_w_device_read_pipe           read_pipe       : 1; ///< Read pipe setting.
    ospi_w_device_read_pipe_delay     read_pipe_delay : 3; ///< Read pipe delay value.
    ospi_w_device_addr_size           address_size    : 1; ///< Flash address size.
    ospi_w_device_dummy_mode          dummy_mode      : 1; ///< Dummy mode.
    ospi_w_device_slew_rate           slew_rate       : 2; ///< Slew rate
    ospi_w_device_drive_current       drive_current   : 2; ///< Drive current
    ospi_w_device_manualmode_config_t manualmode_config;
    ospi_w_device_automode_config_t   automode_config;
} ospi_w_device_config_t;

/** OSPI_W read instruction configuration structure (auto access mode) */
typedef struct
{
    bool    enable;                                    /**< Enable read instruction */
    uint8_t instr;                                     /**< Instruction code for Incremental
                                                        *   Burst or Single read access.
                                                        *   Also used when wrapping burst
                                                        *   is not supported. */
    uint8_t instr_extra_byte;                          /**< Extra byte instruction. Usually
                                                        *   the Mode Bits in Dual/Quad/
                                                        *   Octal SPI I/O instructions */
    ospi_w_device_bus_mode        instr_bus_mode;      /**< Bus mode during the instruction phase */
    ospi_w_device_bus_mode        addr_bus_mode;       /**< Bus mode during the address phase */
    ospi_w_device_bus_mode        extra_byte_bus_mode; /**< Bus mode during the extra byte phase */
    ospi_w_device_bus_mode        dummy_bus_mode;      /**< Bus mode during the dummy phase */
    ospi_w_device_bus_mode        data_bus_mode;       /**< Bus mode during the data phase */
    ospi_w_device_extra_byte      extra_byte_cfg;      /**< Extra byte enable/disable */
    ospi_w_device_extra_byte_half extra_byte_half_cfg; /**< Enable/disable of extra byte half setting */
    uint8_t dummy_bytes;                               /**< The number of dummy bytes (0..32) */
    ospi_w_device_instr_mode          instr_mode;
    ospi_w_device_idle_state_duration idle_state_duration;
} ospi_w_device_read_instr_config_t;

/*
 * OSPI_W wrapping burst instruction configuration structure (auto access mode)
 */
typedef struct
{
    bool                    enable;    /* Enable wrapping burst instruction */
    uint8_t                 instr;     /* Wrapping burst instruction code */
    ospi_w_device_wrap_mode mode;      /* Wrapping burst mode */
    ospi_w_device_wrap_len  len;       /* Wrapping burst length */
    ospi_w_device_wrap_size size;      /* Wrapping burst size */
} ospi_w_device_wrap_burst_instr_config_t;

/** OSPI_W erase instruction configuration structure (auto access mode) */
typedef struct
{
    bool                   enable;         /**< Enable erase instruction */
    uint8_t                instr;          /**< Erase instruction code */
    ospi_w_device_bus_mode instr_bus_mode; /**< Bus mode during the instruction phase */
    ospi_w_device_bus_mode addr_bus_mode;  /**< Bus mode during the address phase */
    uint8_t                hclk_cycles;    /**< The number of AMBA AHB hclk cycles
                                            *   (0..15) without memory read requests
                                            *   before the controller can execute
                                            *   erase or erase resume instructions */
    uint8_t cs_hi_cycles;                  /**< The minimum number of QSPI bus clock
                                            *   cycles (0..31) that OSPI_CS remains
                                            *   high after the execution of write
                                            *   enable, erase, erase suspend and
                                            *   erase resume instructions. */
} ospi_w_device_erase_instr_config_t;

/** OSPI_W read status instruction configuration structure (auto access mode) */
typedef struct
{
    bool                   enable;                 /**< Enable read status instruction */
    uint8_t                instr;                  /**< Read status instruction code */
    ospi_w_device_bus_mode instr_bus_mode;         /**< Bus mode during the instruction phase */
    ospi_w_device_bus_mode receive_bus_mode;       /**< Bus mode during the receive status phase */
    ospi_w_device_bus_mode dummy_bus_mode;         /**< Bus mode during the dummy bytes phase */
    uint8_t                busy_pos;               /**< The position of the Busy bit in the
                                                    *   status register (0 - 7) */
    ospi_w_device_busy busy_val;                   /**< Busy status setting */
    uint8_t            read_stat_del;              /**< The minimum time distance between the
                                                    *   read status instruction and previous
                                                    *   erase or erase/resume instructions.
                                                    *   0: don't wait. The controller can read
                                                    *   the memory status register immediately.
                                                    *   1..63 - the controller waits at least
                                                    *   this number of QSPI_CLK cycles before
                                                    *   reading the memory status register
                                                    *   following the end of a previous erase
                                                    *   or erase resume */
    ospi_w_device_read_status_reg_cnt read_stat_reg_cnt;
    uint8_t dummy_bytes;                           /**< The number of dummy bytes (0..16) */
    ospi_w_device_read_status_dummy_val dummy_val; /**< Dummy bytes value */
} ospi_w_device_read_status_config_t;

/** OSPI_W write enable instruction configuration structure (auto access mode) */
typedef struct
{
    bool                   enable;         /**< Enable write enable instruction */
    uint8_t                instr;          /**< Write enable instruction code */
    ospi_w_device_bus_mode instr_bus_mode; /**< Bus mode during the instruction phase */
} ospi_w_device_write_enable_instr_config_t;

/** OSPI_W erase suspend/resume instruction structure */
typedef struct
{
    bool                   enable;           /**< Enable erase suspend/resume instruction */
    uint8_t                suspend_instr;    /**< Erase suspend instruction code */
    uint8_t                resume_instr;     /**< Erase resume instruction code */
    ospi_w_device_bus_mode suspend_bus_mode; /**< Bus mode during the erase suspend
                                              *   instruction phase */
    ospi_w_device_bus_mode resume_bus_mode;  /**< Bus mode during the erase resume
                                              *   instruction phase */
    uint8_t read_stat_del;                   /**< The minimum time distance between the
                                              *   read status instruction and the previous
                                              *   erase or erase/resume instructions.
                                              *   0: don't wait. The controller can read
                                              *   the memory status register immediately.
                                              *   1..255 - the controller waits at least
                                              *   this number of OSPI_CLK cycles before
                                              *   reading the memory status register */
} ospi_w_device_suspend_resume_instr_config_t;

/*
 * OSPI_W instructions configuration structure in auto access mode
 */
typedef struct
{
    ospi_w_device_read_instr_config_t           read_instr_cfg;
    ospi_w_device_wrap_burst_instr_config_t     wrap_burst_instr_cfg;
    ospi_w_device_erase_instr_config_t          erase_instr_cfg;
    ospi_w_device_read_status_config_t          read_status_instr_cfg;
    ospi_w_device_write_enable_instr_config_t   write_enable_instr_cfg;
    ospi_w_device_suspend_resume_instr_config_t suspend_resume_instr_cfg;
} ospi_w_device_instr_config_t;

/*
 * OSPI_W AES-CTR decryption configuration structure
 */
typedef struct
{
    uint8_t  nonce[8];                 /*!< AES-CTR decryption nonce value */
    uint8_t  key[32];                  /*!< AES-CTR decryption key value */
    uint32_t start_addr;               /*!< AES-CTR decryption start address */
    uint32_t end_addr;                 /*!< AES-CTR decryption end address */
} ospi_w_device_aes_ctr_config_t;

/*
 * Size of Burst Break Sequence
 *
 */
typedef enum
{
    OSPI_W_DEVICE_BREAK_SEQ_SIZE_1B = 0, /* One byte */
    OSPI_W_DEVICE_BREAK_SEQ_SIZE_2B = 1  /* Two bytes */
} ospi_w_device_break_seq_size;

/*
 * Type of QSPI_CLK edge producing the QSPI_CS signal
 *
 */
typedef enum
{
    OSPI_W_DEVICE_CS_MODE_RISING  = 0, /* The QSPI_CS is produced with the rising edge of the QSPI_SCK */
    OSPI_W_DEVICE_CS_MODE_FALLING = 1  /* The QSPI_CS is produced with the falling edge of the QSPI_SCK */
} ospi_w_device_cs_mode;

/* OSPI Flash chip select */
typedef enum e_ospi_w_chip_select
{
    OSPI_W_DEVICE_NUMBER_0 = 0U,       ///< Device connected to Chip-Select 0
} ospi_w_device_number_t;

/* OSPI flash number of command code bytes. */
typedef enum e_ospi_w_command_bytes
{
    OSPI_W_COMMAND_BYTES_1 = 1U,       ///< Command codes are 1 byte long.
    OSPI_W_COMMAND_BYTES_2 = 2U,       ///< Command codes are 2 bytes long.
} ospi_w_command_bytes_t;

/* OSPI frame to frame interval */
typedef enum e_ospi_w_frame_interval_clocks
{
    OSPI_W_COMMAND_INTERVAL_CLOCKS_1 = 0U, ///< 1 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_2,      ///< 2 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_3,      ///< 3 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_4,      ///< 4 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_5,      ///< 5 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_6,      ///< 6 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_7,      ///< 7 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_8,      ///< 8 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_9,      ///< 9 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_10,     ///< 10 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_11,     ///< 11 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_12,     ///< 12 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_13,     ///< 13 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_14,     ///< 14 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_15,     ///< 15 interval clocks
    OSPI_W_COMMAND_INTERVAL_CLOCKS_16,     ///< 16 interval clocks
} ospi_w_command_interval_clocks_t;

/* OSPI chip select de-assertion duration */
typedef enum e_ospi_w_cs_pullup_clocks
{
    OSPI_W_COMMAND_CS_PULLUP_CLOCKS_NO_EXTENSION = 0U, ///< CS asserting No extension
    OSPI_W_COMMAND_CS_PULLUP_CLOCKS_1,                 ///< CS asserting Extend 1 cycle
} ospi_w_command_cs_pullup_clocks_t;

/* OSPI chip select assertion duration */
typedef enum e_ospi_w_cs_pulldown_clocks
{
    OSPI_W_COMMAND_CS_PULLDOWN_CLOCKS_NO_EXTENSION = 0U, ///< CS negating No extension
    OSPI_W_COMMAND_CS_PULLDOWN_CLOCKS_1,                 ///< CS negating Extend 1 cycle
} ospi_w_command_cs_pulldown_clocks_t;

/* Prefetch function settings */
typedef enum e_ospi_w_prefetch_function
{
    OSPI_W_PREFETCH_FUNCTION_DISABLE = 0x00, // Prefetch function disable
    OSPI_W_PREFETCH_FUNCTION_ENABLE  = 0x01, // Prefetch function enable
} ospi_w_prefetch_function_t;

/* Combination function settings */
typedef enum e_ospi_w_combination_function
{
    OSPI_W_COMBINATION_FUNCTION_DISABLE = 0x00,  // Combination function disable
    OSPI_W_COMBINATION_FUNCTION_4BYTE   = 0x01,  // Combine up to 4 bytes
    OSPI_W_COMBINATION_FUNCTION_8BYTE   = 0x03,  // Combine up to 8 bytes
    OSPI_W_COMBINATION_FUNCTION_12BYTE  = 0x05,  // Combine up to 12 bytes
    OSPI_W_COMBINATION_FUNCTION_16BYTE  = 0x07,  // Combine up to 16 bytes
    OSPI_W_COMBINATION_FUNCTION_20BYTE  = 0x09,  // Combine up to 20 bytes
    OSPI_W_COMBINATION_FUNCTION_24BYTE  = 0x0B,  // Combine up to 24 bytes
    OSPI_W_COMBINATION_FUNCTION_28BYTE  = 0x0D,  // Combine up to 28 bytes
    OSPI_W_COMBINATION_FUNCTION_32BYTE  = 0x0F,  // Combine up to 32 bytes
    OSPI_W_COMBINATION_FUNCTION_36BYTE  = 0x11,  // Combine up to 36 bytes
    OSPI_W_COMBINATION_FUNCTION_40BYTE  = 0x13,  // Combine up to 40 bytes
    OSPI_W_COMBINATION_FUNCTION_44BYTE  = 0x15,  // Combine up to 44 bytes
    OSPI_W_COMBINATION_FUNCTION_48BYTE  = 0x17,  // Combine up to 48 bytes
    OSPI_W_COMBINATION_FUNCTION_52BYTE  = 0x19,  // Combine up to 52 bytes
    OSPI_W_COMBINATION_FUNCTION_56BYTE  = 0x1B,  // Combine up to 56 bytes
    OSPI_W_COMBINATION_FUNCTION_60BYTE  = 0x1D,  // Combine up to 60 bytes
    OSPI_W_COMBINATION_FUNCTION_64BYTE  = 0x1F,  // Combine up to 64 bytes
    OSPI_W_COMBINATION_FUNCTION_2BYTE   = 0x1FF, // Combine up to 2 bytes
} ospi_w_combination_function_t;

/* Memory mapped timing */
typedef struct st_ospi_w_timing_setting
{
    ospi_w_command_interval_clocks_t    command_to_command_interval; // Interval between 2 consecutive commands
    ospi_w_command_cs_pullup_clocks_t   cs_pullup_lag;               // Duration to de-assert CS line after the last command
    ospi_w_command_cs_pulldown_clocks_t cs_pulldown_lead;            // Duration to assert CS line before the first command
} ospi_w_timing_setting_t;

/** Command set used for a protocol mode other than normal (1S-1S-1S) SPI. */
typedef struct st_ospi_w_xspi_command_set
{
    spi_flash_protocol_t              protocol;                  ///< Protocol mode associated with this command set.
    ospi_w_command_bytes_t            command_bytes;             ///< Number of command bytes for each command code.
    uint16_t                          read_command;              ///< Read command.
    uint16_t                          page_program_command;      ///< Page program/write command.
    uint16_t                          write_enable_command;      ///< Command to enable write or erase, set to 0x00 to ignore.
    uint16_t                          status_command;            ///< Command to read the write status, set to 0x00 to ignore.
    uint8_t                           read_dummy_cycles;         ///< Dummy cycles to be inserted for read commands.
    uint8_t                           program_dummy_cycles;      ///< Dummy cycles to be inserted for page program commands.
    uint8_t                           status_dummy_cycles;       ///< Dummy cycles to be inserted for status read commands.
    uint8_t                           erase_command_list_length; ///< Length of erase command list
    spi_flash_erase_command_t const * p_erase_command_list;      ///< List of all erase commands and associated sizes
} ospi_w_xspi_command_set_t;

/** OSPI_W Extended configuration. */
typedef struct st_ospi_w_extended_cfg
{
    ospi_w_device_number_t            channel;                                ///< Device number to be used for memory device
    ospi_w_timing_setting_t const   * p_timing_settings;                      ///< Memory-mapped timing settings.
    ospi_w_xspi_command_set_t const * p_xspi_command_set_list;                ///< Additional protocol command sets; if additional protocol commands set are not used set this to NULL.
    uint8_t   xspi_command_set_list_length;                                   ///< Number of additional protocol command set defined.
    uint8_t * p_autocalibration_preamble_pattern_addr;                        ///< OctaFlash memory address holding the preamble pattern
    uint8_t   data_latch_delay_clocks;                                        ///< Specify delay between OM_DQS and OM_DQS Strobe. Set to 0 to auto-calibrate. Typical value is 0x80.
#if OSPI_W_CFG_DMAC_SUPPORT_ENABLE
    transfer_instance_t const * p_lower_lvl_transfer;                         ///< DMA Transfer instance used for data transmission
#endif
    ospi_w_device_config_t                      * p_ospi_w_device_cfg;        ///< OSPI_W HW configuration.
    ospi_w_device_read_instr_config_t           * p_read_instr_cfg;           ///< Automode read instruction configuration.
    ospi_w_device_wrap_burst_instr_config_t     * p_wrap_burst_instr_cfg;     ///< Wrap burst instruction configuration.
    ospi_w_device_read_status_config_t          * p_read_status_instr_cfg;    ///< Automode read status instruction configuration.
    ospi_w_device_erase_instr_config_t          * p_erase_instr_cfg;          ///< Automode erase instruction configuration.
    ospi_w_device_write_enable_instr_config_t   * p_write_enable_instr_cfg;   ///< Automode write enable instruction configuration.
    ospi_w_device_suspend_resume_instr_config_t * p_suspend_resume_instr_cfg; ///< Automode suspend and resume instruction configuration.
} ospi_w_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_flash_api_t::open is called */
typedef struct st_ospi_w_instance_ctrl
{
    spi_flash_cfg_t const           * p_cfg;        ///< Pointer to initial configuration
    uint32_t                          open;         ///< Whether or not driver is open
    spi_flash_protocol_t              spi_protocol; ///< Current OSPI protocol selected
    ospi_w_device_number_t            channel;      ///< Device number to be used for memory device
    ospi_w_xspi_command_set_t const * p_cmd_set;    ///< Command set for the active protocol mode.
} ospi_w_instance_ctrl_t;

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define IS_OSPI_W_DEVICE_BUS_MODE(x)                 (((x) == OSPI_W_DEVICE_BUS_MODE_SINGLE) || \
                                                      ((x) == OSPI_W_DEVICE_BUS_MODE_DUAL) ||   \
                                                      ((x) == OSPI_W_DEVICE_BUS_MODE_QUAD) ||   \
                                                      ((x) == OSPI_W_DEVICE_BUS_MODE_OCTA))

#define IS_OSPI_W_DEVICE_EXTRA_BYTE(x)               (((x) == OSPI_W_DEVICE_EXTRA_BYTE_DISABLE) || \
                                                      ((x) == OSPI_W_DEVICE_EXTRA_BYTE_ENABLE))

#define IS_OSPI_W_DEVICE_EXTRA_BYTE_HALF(x)          (((x) == OSPI_W_DEVICE_EXTRA_BYTE_HALF_DISABLE) || \
                                                      ((x) == OSPI_W_DEVICE_EXTRA_BYTE_HALF_ENABLE))

#define IS_OSPI_W_DEVICE_INSTR_MODE_SEND(x)          (((x) == OSPI_W_DEVICE_INSTR_MODE_SEND_ANYTIME) || \
                                                      ((x) == OSPI_W_DEVICE_INSTR_MODE_SEND_ONCE))

#define IS_OSPI_W_DEVICE_IDLE_STATE_DURATION(x)      (((x) == OSPI_W_DEVICE_IDLE_STATE_DURATION_0) || \
                                                      ((x) == OSPI_W_DEVICE_IDLE_STATE_DURATION_1) || \
                                                      ((x) == OSPI_W_DEVICE_IDLE_STATE_DURATION_2) || \
                                                      ((x) == OSPI_W_DEVICE_IDLE_STATE_DURATION_3))

#define IS_OSPI_W_DEVICE_WRAP_MODE(x)                (((x) == OSPI_W_DEVICE_WRAP_MODE_INSTR) || \
                                                      ((x) == OSPI_W_DEVICE_WRAP_MODE_INSTR_WRAP))

#define IS_OSPI_W_DEVICE_WRAP_LEN(x)                 (((x) == OSPI_W_DEVICE_WRAP_LEN_4BEAT) || \
                                                      ((x) == OSPI_W_DEVICE_WRAP_LEN_8BEAT) || \
                                                      ((x) == OSPI_W_DEVICE_WRAP_LEN_16BEAT))

#define IS_OSPI_W_DEVICE_WRAP_SIZE(x)                (((x) == OSPI_W_DEVICE_WRAP_SIZE_8BITS) ||  \
                                                      ((x) == OSPI_W_DEVICE_WRAP_SIZE_16BITS) || \
                                                      ((x) == OSPI_W_DEVICE_WRAP_SIZE_32BITS))

#define IS_OSPI_W_DEVICE_BUSY(x)                     (((x) == OSPI_W_DEVICE_BUSY_LOW) || \
                                                      ((x) == OSPI_W_DEVICE_BUSY_HIGH))

#define IS_OSPI_W_DEVICE_READ_STATUS_REG_CNT(x)      (((x) == OSPI_W_DEVICE_READ_STATUS_REG_CNT_RESSTS) || \
                                                      ((x) == OSPI_W_DEVICE_READ_STATUS_REG_CNT_RESSUS))

#define IS_OSPI_W_DEVICE_READ_STATUS_DUMMY_VAL(x)    (((x) == OSPI_W_DEVICE_READ_STATUS_DUMMY_VAL_UNCHANGED) || \
                                                      ((x) == OSPI_W_DEVICE_READ_STATUS_DUMMY_VAL_FORCED_ZERO))

/* Enable OQSPI controller clock */
__STATIC_FORCEINLINE void r_ospi_w_device_clock_enable (void)
{
    GLOBAL_INT_DISABLE();
    REG_SET_BIT(CRG_TOP, CLK_AMBA_REG, OQSPIF_ENABLE);
    GLOBAL_INT_RESTORE();
}

/*
 * Disable OQSPI controller clock
 */
__STATIC_FORCEINLINE void r_ospi_w_device_clock_disable (void)
{
    GLOBAL_INT_DISABLE();
    REG_CLR_BIT(CRG_TOP, CLK_AMBA_REG, OQSPIF_ENABLE);
    GLOBAL_INT_RESTORE();
}

/*
 * Enable CS on OQSPI bus in manual access mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_cs_enable (void)
{
    REG_SET_BIT(OQSPIF, OQSPIF_CTRLBUS_REG, OSPIC_EN_CS);
}

/*
 * Disable CS on OQSPI bus in manual access mode.
 */
__STATIC_FORCEINLINE void r_ospi_w_device_cs_disable (void)
{
    REG_SET_BIT(OQSPIF, OQSPIF_CTRLBUS_REG, OSPIC_DIS_CS);
}

/*
 * Disable CS on OQSPI bus in manual access mode.
 */
__STATIC_FORCEINLINE void r_ospi_w_device_cs_toggle (void)
{
    REG_SET_BIT(OQSPIF, OQSPIF_CTRLBUS_REG, OSPIC_DIS_CS);
    REG_SET_BIT(OQSPIF, OQSPIF_CTRLBUS_REG, OSPIC_EN_CS);
}

/*
 * Get OSPI_W Bus status
 *
 * see also ospi_w_device_BUS_STATUS
 */
__STATIC_FORCEINLINE ospi_w_device_bus_status r_ospi_w_device_get_bus_status (void)
{
    return (ospi_w_device_bus_status) REG_GETF(OQSPIF, OQSPIF_STATUS_REG, OSPIC_BUSY);
}

/*
 * Set OSPI_W clock divider
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_div (ospi_w_device_clk_div div)
{
    GLOBAL_INT_DISABLE();
    CRG_TOP->CLK_AMBA_REG_b.OQSPIF_DIV = div;
    GLOBAL_INT_RESTORE();
}

/*
 * Get OSPI_W clock divider
 */
__STATIC_FORCEINLINE ospi_w_device_clk_div r_ospi_w_device_get_div (void)
{
    return (ospi_w_device_clk_div) REG_GETF(CRG_TOP, CLK_AMBA_REG, OQSPIF_DIV);
}

/*
 * Set OSPI_W bus mode in manual mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_bus_mode (ospi_w_device_bus_mode bus_mode)
{
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(bus_mode));
    OQSPIF->OQSPIF_CTRLBUS_REG = 1 << bus_mode;
}

/*
 * Get OSPI_W bus mode in manual mode
 */
__STATIC_FORCEINLINE ospi_w_device_bus_mode r_ospi_w_device_get_bus_mode (void)
{
    ospi_w_device_bus_mode ret_bus_mode;
    uint32_t               bus_mode_reg = OQSPIF->OQSPIF_CTRLBUS_REG;
    ret_bus_mode =
        (bus_mode_reg ==
         (0x01 <<
            OSPI_W_DEVICE_BUS_MODE_OCTA)) ? OSPI_W_DEVICE_BUS_MODE_OCTA : (ospi_w_device_bus_mode) (bus_mode_reg >> 1);

    return ret_bus_mode;
}

/*
 * Set OSPI_W access mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_access_mode (ospi_w_device_access_mode access_mode)
{
    OQSPIF->OQSPIF_CTRLMODE_REG_b.OSPIC_AUTO_MD = access_mode;
}

/*
 * Get OSPI_W access mode
 */
__STATIC_FORCEINLINE ospi_w_device_access_mode r_ospi_w_device_get_access_mode (void)
{
    return (ospi_w_device_access_mode) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_AUTO_MD);
}

/*
 * Set OSPI_W clock mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_clock_mode (ospi_w_device_clk_mode clk_mode)
{
    ASSERT_WARNING(clk_mode == OSPI_W_DEVICE_CLK_MODE_LOW || clk_mode == OSPI_W_DEVICE_CLK_MODE_HIGH);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_CLK_MD, clk_mode);
}

/*
 * Get OSPI_W clock mode
 */
__STATIC_FORCEINLINE ospi_w_device_clk_mode r_ospi_w_device_get_clock_mode (void)
{
    return (ospi_w_device_clk_mode) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_CLK_MD);
}

/*
 * Set OSPI_IO2 direction
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_io2_direction (ospi_w_device_io_dir dir)
{
    ASSERT_WARNING(dir == OSPI_W_DEVICE_IO_DIR_AUTO_SEL || dir == OSPI_W_DEVICE_IO_DIR_OUTPUT);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO2_OEN, dir);
}

/*
 * Get OSPI_IO2 direction
 */
__STATIC_FORCEINLINE ospi_w_device_io_dir r_ospi_w_device_get_io2_direction (void)
{
    return (ospi_w_device_io_dir) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO2_OEN);
}

/*
 * Set OSPI_IO3 direction
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_io3_direction (ospi_w_device_io_dir dir)
{
    ASSERT_WARNING(dir == OSPI_W_DEVICE_IO_DIR_AUTO_SEL || dir == OSPI_W_DEVICE_IO_DIR_OUTPUT);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO3_OEN, dir);
}

/*
 * Get OSPI_IO3 direction
 */
__STATIC_FORCEINLINE ospi_w_device_io_dir r_ospi_w_device_get_io3_direction (void)
{
    return (ospi_w_device_io_dir) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO3_OEN);
}

/*
 * Set OSPI_IO4 - OSPI_IO7 direction
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_io4_7_direction (ospi_w_device_io_dir dir)
{
    ASSERT_WARNING(dir == OSPI_W_DEVICE_IO_DIR_AUTO_SEL || dir == OSPI_W_DEVICE_IO_DIR_OUTPUT);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_OEN, dir);
}

/*
 * Get OSPI_IO4 - OSPI_IO7 direction
 */
__STATIC_FORCEINLINE ospi_w_device_io_dir r_ospi_w_device_get_io4_7_direction (void)
{
    return (ospi_w_device_io_dir) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_OEN);
}

/*
 * Set the value of OSPI_IO2 pad when OSPI_IO2 direction is output
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_io2_value (ospi_w_device_io_value value)
{
    ASSERT_WARNING(value == OSPI_W_DEVICE_IO_VALUE_LOW || value == OSPI_W_DEVICE_IO_VALUE_HIGH);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO2_DAT, (uint32_t) value);
}

/*
 * Get the value of OSPI_IO2 pad when OSPI_IO2 direction is output
 */
__STATIC_FORCEINLINE ospi_w_device_io_value r_ospi_w_device_get_io2_value (void)
{
    return (ospi_w_device_io_value) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO2_DAT);
}

/*
 * Set the value of OSPI_IO3 pad when OSPI_IO3 direction is output
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_io3_value (ospi_w_device_io_value value)
{
    ASSERT_WARNING(value == OSPI_W_DEVICE_IO_VALUE_LOW || value == OSPI_W_DEVICE_IO_VALUE_HIGH);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO3_DAT, (uint32_t) value);
}

/*
 * Get the value of OSPI_IO3 pad when OSPI_IO3 direction is output
 */
__STATIC_FORCEINLINE ospi_w_device_io_value r_ospi_w_device_get_io3_value (void)
{
    return (ospi_w_device_io_value) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO3_DAT);
}

/*
 * Set the value of OSPI_IO4-7 pads when OSPI_IO4-7 direction is output
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_io4_7_value (ospi_w_device_io4_7_value value)
{
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_DAT, (uint32_t) value);
}

/*
 * Get the value of OSPI_IO4-7 pad when OSPI_IO4-7 direction is output
 */
__STATIC_FORCEINLINE ospi_w_device_io4_7_value r_ospi_w_device_get_io4_7_value (void)
{
    return (ospi_w_device_io4_7_value) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_DAT);
}

/*
 * Set OSPI_W HReady signal mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_hready_mode (ospi_w_device_hready_mode mode)
{
    ASSERT_WARNING(mode == OSPI_W_DEVICE_HREADY_MODE_WAIT || mode == OSPI_W_DEVICE_HREADY_MODE_NO_WAIT);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_HRDY_MD, mode);
}

/*
 * Get OSPI_W HReady signal mode
 */
__STATIC_FORCEINLINE ospi_w_device_hready_mode r_ospi_w_device_get_hready_mode (void)
{
    return (ospi_w_device_hready_mode) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_HRDY_MD);
}

/*
 * Set OSPI_W read sampling edge
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_read_sampling_edge (ospi_w_device_sampling_edge edge)
{
    ASSERT_WARNING(edge == OSPI_W_DEVICE_SAMPLING_EDGE_POS || edge == OSPI_W_DEVICE_SAMPLING_EDGE_NEG);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_RXD_NEG, edge);
}

/*
 * Get OSPI_W read sampling edge
 */
__STATIC_FORCEINLINE ospi_w_device_sampling_edge r_ospi_w_device_get_read_sampling_edge (void)
{
    return (ospi_w_device_sampling_edge) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_RXD_NEG);
}

/*
 * Set OSPI_W data read pipe status
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_read_pipe (ospi_w_device_read_pipe read_pipe)
{
    ASSERT_WARNING(read_pipe == OSPI_W_DEVICE_READ_PIPE_DISABLE ||
                   read_pipe == OSPI_W_DEVICE_READ_PIPE_ENABLE);

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_RPIPE_EN, read_pipe);
}

/*
 * Get OSPI_W read pipe status
 */
__STATIC_FORCEINLINE ospi_w_device_read_pipe r_ospi_w_device_get_read_pipe (void)
{
    return (ospi_w_device_read_pipe) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_RPIPE_EN);
}

/*
 * Set the OSPI_W read pipe clock delay
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_read_pipe_clock_delay (ospi_w_device_read_pipe_delay delay)
{
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_PCLK_MD, delay);
}

/*
 * Get OSPI_W read pipe clock delay
 */
__STATIC_FORCEINLINE ospi_w_device_read_pipe_delay r_ospi_w_device_get_read_pipe_clock_delay (void)
{
    return (ospi_w_device_read_pipe_delay) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_PCLK_MD);
}

/*
 * Set OSPI_W full buffer mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_full_buffer_mode (ospi_w_device_full_buffer_mode full_buffer_mode)
{
    ASSERT_WARNING(full_buffer_mode == OSPI_W_DEVICE_FULL_BUFFER_MODE_BLOCK ||
                   full_buffer_mode == OSPI_W_DEVICE_FULL_BUFFER_MODE_TERMINATE);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_BUF_LIM_EN, full_buffer_mode);
}

/*
 * Get OSPI_W full buffer mode
 */
__STATIC_FORCEINLINE ospi_w_device_full_buffer_mode r_ospi_w_device_get_full_buffer_mode (void)
{
    return (ospi_w_device_full_buffer_mode) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_BUF_LIM_EN);
}

/*
 * Set OSPI_W address size
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_address_size (ospi_w_device_addr_size size)
{
    ASSERT_WARNING(size == OSPI_W_DEVICE_ADDR_SIZE_24 || size == OSPI_W_DEVICE_ADDR_SIZE_32);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_USE_32BA, size);
}

/*
 * Get OSPI_W address size
 */
__STATIC_FORCEINLINE ospi_w_device_addr_size r_ospi_w_device_get_address_size (void)
{
    return (ospi_w_device_addr_size) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_USE_32BA);
}

/*
 * Set OSPI_W instruction size in auto mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_instruction_size (ospi_w_device_instruct_sz instruct_sz)
{
    ASSERT_WARNING(instruct_sz == OSPI_W_DEVICE_INSTRUCT_SZ_1_BYTE ||
                   instruct_sz == OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_CMD_X2_EN, instruct_sz);
}

/*
 * Get OSPI_W instruction size in auto mode
 */
__STATIC_FORCEINLINE ospi_w_device_instruct_sz r_ospi_w_device_get_instruction_size (void)
{
    return (ospi_w_device_instruct_sz) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_CMD_X2_EN);
}

/*
 * Set OSPI_W dummy mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_dummy_mode (ospi_w_device_dummy_mode dummy_mode)
{
    ASSERT_WARNING(dummy_mode == OSPI_W_DEVICE_DUMMY_MODE_LAST_CLK ||
                   dummy_mode == OSPI_W_DEVICE_DUMMY_MODE_LAST_2_CLK);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_DMY_MD, dummy_mode);
}

/*
 * Get OSPI_W dummy mode
 */
__STATIC_FORCEINLINE ospi_w_device_dummy_mode r_ospi_w_device_get_dummy_mode (void)
{
    return (ospi_w_device_dummy_mode) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_DMY_MD);
}

/*
 * Set OSPI_W direction change mode in manual access mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_dir_change_mode (ospi_w_device_dir_change_mode dir_change_mode)
{
    ASSERT_WARNING(dir_change_mode == OSPI_W_DEVICE_DIR_CHANGE_MODE_EACH_ACCESS ||
                   dir_change_mode == OSPI_W_DEVICE_DIR_CHANGE_MODE_DUMMY_ACCESS);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_MAN_DIRCHG_MD, dir_change_mode);
}

/*
 * Get OSPI_W direction change mode in manual access mode
 */
__STATIC_FORCEINLINE ospi_w_device_dir_change_mode r_ospi_w_device_get_dir_change_mode (void)
{
    return (ospi_w_device_dir_change_mode) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_MAN_DIRCHG_MD);
}

/*
 * Set OSPI_W AHB bus error response when a read is performed in the address space
 * where the flash device is mapped and the Auto mode is not enabled
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_mapped_addr_read_access_response (
    ospi_w_device_mapped_addr_rd_acc_response read_access_response)
{
    ASSERT_WARNING(read_access_response == OSPI_W_DEVICE_MAPPED_ADDR_RD_ACC_RESPONSE_IGNORE ||
                   read_access_response == OSPI_W_DEVICE_MAPPED_ADDR_RD_ACC_RESPONSE_AHB_ERROR);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_RD_ERR_EN, read_access_response);
}

/*
 * Get OSPI_W AHB bus error response when a read is performed in the address space
 * where the flash device is mapped and the Auto mode is not enabled
 */
__STATIC_FORCEINLINE ospi_w_device_mapped_addr_rd_acc_response r_ospi_w_device_get_mapped_addr_read_access_response (
    void)
{
    return (ospi_w_device_mapped_addr_rd_acc_response) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_RD_ERR_EN);
}

/*
 * Set OSPI_W burst length in auto mode when the read access in the AHB bus is an
 * incremental burst of unspecified length
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_burst_len_limit (ospi_w_device_burst_len_limit burst_len_limit)
{
    ASSERT_WARNING(burst_len_limit == OSPI_W_DEVICE_BURST_LEN_LIMIT_UNSPECIFIED ||
                   burst_len_limit == OSPI_W_DEVICE_BURST_LEN_LIMIT_8_BYTES);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_INC_LIM_EN, burst_len_limit);
}

/*
 * Get OSPI_W burst length in auto mode when the read access in the AHB bus is an
 * incremental burst of unspecified length
 */
__STATIC_FORCEINLINE ospi_w_device_burst_len_limit ospi_w_device_get_burst_len_limit (void)
{
    return (ospi_w_device_burst_len_limit) REG_GETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_INC_LIM_EN);
}

/*
 * Set slew rate of OSPI_W pads
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_slew_rate (ospi_w_device_slew_rate slew_rate)
{
    REG_SETF(OQSPIF, OQSPIF_GP_REG, OSPIC_PADS_SLEW, slew_rate);
}

/*
 * Get slew rate of OSPI_W pads
 */
__STATIC_FORCEINLINE ospi_w_device_slew_rate r_ospi_w_device_get_slew_rate (void)
{
    return (ospi_w_device_slew_rate) REG_GETF(OQSPIF, OQSPIF_GP_REG, OSPIC_PADS_SLEW);
}

/*
 * Set drive current of OSPI_W pads
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_drive_current (ospi_w_device_drive_current drive_current)
{
    REG_SETF(OQSPIF, OQSPIF_GP_REG, OSPIC_PADS_DRV, drive_current);
}

/*
 * Get drive current of OSPI_W pads
 */
__STATIC_FORCEINLINE ospi_w_device_drive_current r_ospi_w_device_get_drive_current (void)
{
    return (ospi_w_device_drive_current) REG_GETF(OQSPIF, OQSPIF_GP_REG, OSPIC_PADS_DRV);
}

/*
 * Set the number of dummy bytes in auto access mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_dummy_bytes (uint8_t dummy_bytes)
{
    ASSERT_WARNING(dummy_bytes <= 32);

    if (dummy_bytes == 0)
    {
        REG_CLR_BIT(OQSPIF, OQSPIF_BURSTCMDB_REG, OSPIC_DMY_EN);
    }
    else
    {
        REG_SETF(OQSPIF, OQSPIF_BURSTCMDB_REG, OSPIC_DMY_NUM, (uint32_t) (dummy_bytes - 1));
        REG_SET_BIT(OQSPIF, OQSPIF_BURSTCMDB_REG, OSPIC_DMY_EN);
    }
}

/*
 * Get the number of dummy bytes in auto access mode
 */
__STATIC_FORCEINLINE uint8_t r_ospi_w_device_get_dummy_bytes (void)
{
    if (REG_GETF(OQSPIF, OQSPIF_BURSTCMDB_REG, OSPIC_DMY_EN) == 0)
    {
        return 0;
    }
    else
    {
        return (uint8_t) (REG_GETF(OQSPIF, OQSPIF_BURSTCMDB_REG, OSPIC_DMY_NUM) + 1);
    }
}

/*
 * Set the number of dummy bytes during the read status instruction in auto access mode
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_read_status_dummy_bytes (uint8_t dummy_bytes)
{
    ASSERT_WARNING(dummy_bytes <= 16);

    if (dummy_bytes == 0)
    {
        REG_CLR_BIT(OQSPIF, OQSPIF_STATUSCMD_REG, OSPIC_RSTAT_DMY_EN);
    }
    else
    {
        REG_SETF(OQSPIF, OQSPIF_STATUSCMD_REG, OSPIC_RSTAT_DMY_NUM, (uint32_t) (dummy_bytes - 1));
        REG_SET_BIT(OQSPIF, OQSPIF_STATUSCMD_REG, OSPIC_RSTAT_DMY_EN);
    }
}

/*
 * Get the number of dummy bytes during the read status instruction in auto access mode
 */
__STATIC_FORCEINLINE uint8_t r_ospi_w_device_get_read_status_dummy_bytes (void)
{
    if (REG_GETF(OQSPIF, OQSPIF_STATUSCMD_REG, OSPIC_RSTAT_DMY_EN) == 0)
    {
        return 0;
    }
    else
    {
        return (uint8_t) (REG_GETF(OQSPIF, OQSPIF_STATUSCMD_REG, OSPIC_RSTAT_DMY_NUM) + 1);
    }
}

/*
 * Generate 32 bits data transfer from the external device to the OSPI_W (manual mode)
 */
__STATIC_FORCEINLINE uint32_t r_ospi_w_device_read32 (void)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);

    return ospi_w_regs->OQSPIF_READDATA_REG.data32;
}

/*
 * Generate 16 bits data transfer from the external device to the OSPI_W (manual mode)
 */
__STATIC_FORCEINLINE uint16_t r_ospi_w_device_read16 (void)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);

    return ospi_w_regs->OQSPIF_READDATA_REG.data16;
}

/*
 * Generate 8 bits data transfer from the external device to the OSPI_W (manual mode)
 */
__STATIC_FORCEINLINE uint8_t r_ospi_w_device_read8 (void)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);

    return ospi_w_regs->OQSPIF_READDATA_REG.data8;
}

/*
 * Generate 32 bits data transfer from the OSPI_W to the external device (manual mode)
 */
__STATIC_FORCEINLINE void r_ospi_w_device_write32 (uint32_t data)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);
    ospi_w_regs->OQSPIF_WRITEDATA_REG.data32 = SWAP32(data);
}

/*
 * Generate 16 bits data transfer from the OSPI_W to the external device (manual mode)
 */
__STATIC_FORCEINLINE void r_ospi_w_device_write16 (uint16_t data)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);
    ospi_w_regs->OQSPIF_WRITEDATA_REG.data32 = SWAP16(data);
}

/*
 * Generate 8 bits data transfer from the OSPI_W to the external device (manual mode)
 */
__STATIC_FORCEINLINE void r_ospi_w_device_write8 (uint8_t data)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);
    ospi_w_regs->OQSPIF_WRITEDATA_REG.data8 = data;
}

/*
 * Generate clock pulses on the SPI bus for a 32-bit transfer
 */
__STATIC_FORCEINLINE void r_ospi_w_device_dummy32 (void)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);
    ospi_w_regs->OQSPIF_DUMMYDATA_REG.data32 = 0;
}

/*
 * Generate clock pulses on the SPI bus for a 16-bit transfer
 */
__STATIC_FORCEINLINE void r_ospi_w_device_dummy16 (void)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);
    ospi_w_regs->OQSPIF_DUMMYDATA_REG.data16 = 0;
}

/*
 * Generate clock pulses on the SPI bus for an 8-bit transfer
 */
__STATIC_FORCEINLINE void r_ospi_w_device_dummy8 (void)
{
    ospi_w_regs_t * ospi_w_regs = (ospi_w_regs_t *) (OQSPIF_BASE);
    ospi_w_regs->OQSPIF_DUMMYDATA_REG.data8 = 0;
}

/*
 * OQSPI controller initialization function
 */
BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_init(const ospi_w_device_config_t * cfg);

/*
 * Read the OSPI_W registers and save the current controller's configuration
 */
BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_get_config(ospi_w_device_config_t * cfg);

__STATIC_FORCEINLINE void r_ospi_w_device_read_instr_init (const ospi_w_device_read_instr_config_t
                                                           * read_instr_cfg)
{
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_instr_cfg->instr_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_instr_cfg->addr_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_instr_cfg->extra_byte_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_instr_cfg->dummy_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_instr_cfg->data_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_EXTRA_BYTE(read_instr_cfg->extra_byte_cfg));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_EXTRA_BYTE_HALF(read_instr_cfg->extra_byte_half_cfg));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_INSTR_MODE_SEND(read_instr_cfg->instr_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_IDLE_STATE_DURATION(read_instr_cfg->idle_state_duration));

    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_INST        = read_instr_cfg->instr;
    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_EXT_BYTE    = read_instr_cfg->instr_extra_byte;
    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_INST_TX_MD  = read_instr_cfg->instr_bus_mode;
    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_ADR_TX_MD   = read_instr_cfg->addr_bus_mode;
    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_EXT_TX_MD   = read_instr_cfg->extra_byte_bus_mode;
    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_DMY_TX_MD   = read_instr_cfg->dummy_bus_mode;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_DAT_RX_MD   = read_instr_cfg->data_bus_mode;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_EXT_BYTE_EN = read_instr_cfg->extra_byte_cfg;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_EXT_HF_DS   = read_instr_cfg->extra_byte_half_cfg;
    r_ospi_w_device_set_dummy_bytes(read_instr_cfg->dummy_bytes);
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_INST_MD     = read_instr_cfg->instr_mode;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_CS_HIGH_MIN = read_instr_cfg->idle_state_duration;
}

__STATIC_FORCEINLINE void r_ospi_w_device_wrap_burst_instr_init (const ospi_w_device_wrap_burst_instr_config_t
                                                                 * wrap_burst_instr_cfg)
{
    ASSERT_WARNING(IS_OSPI_W_DEVICE_WRAP_MODE(wrap_burst_instr_cfg->mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_WRAP_LEN(wrap_burst_instr_cfg->len));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_WRAP_SIZE(wrap_burst_instr_cfg->size));

    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_INST_WB   = wrap_burst_instr_cfg->instr;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_WRAP_MD   = wrap_burst_instr_cfg->mode;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_WRAP_LEN  = wrap_burst_instr_cfg->len;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_WRAP_SIZE = wrap_burst_instr_cfg->size;
}

__STATIC_FORCEINLINE void r_ospi_w_device_erase_instr_init (const ospi_w_device_erase_instr_config_t
                                                            * erase_instr_cfg)
{
    OQSPIF->OQSPIF_ERASECMDA_REG_b.OSPIC_ERS_INST   = erase_instr_cfg->instr;
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_ERS_TX_MD  = erase_instr_cfg->instr_bus_mode;
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_EAD_TX_MD  = erase_instr_cfg->addr_bus_mode;
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_ERSRES_HLD = (uint32_t) (erase_instr_cfg->hclk_cycles & 0x0f);
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_ERS_CS_HI  = (uint32_t) (erase_instr_cfg->cs_hi_cycles & 0x1f);
}

__STATIC_FORCEINLINE void r_ospi_w_device_read_status_instr_init (const ospi_w_device_read_status_config_t
                                                                  * read_status_cfg)
{
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_status_cfg->instr_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_status_cfg->receive_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(read_status_cfg->dummy_bus_mode));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUSY(read_status_cfg->busy_val));
    ASSERT_WARNING(read_status_cfg->busy_pos < 8);
    ASSERT_WARNING(read_status_cfg->read_stat_del < 64);
    ASSERT_WARNING(IS_OSPI_W_DEVICE_READ_STATUS_REG_CNT(read_status_cfg->read_stat_reg_cnt));
    ASSERT_WARNING(IS_OSPI_W_DEVICE_READ_STATUS_DUMMY_VAL(read_status_cfg->dummy_val));

    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_RSTAT_INST      = read_status_cfg->instr;
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_RSTAT_TX_MD     = read_status_cfg->instr_bus_mode;
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_RSTAT_RX_MD     = read_status_cfg->receive_bus_mode;
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_RSTAT_DMY_TX_MD = read_status_cfg->dummy_bus_mode;
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_BUSY_POS        = (uint32_t) (read_status_cfg->busy_pos & 0x07);
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_BUSY_VAL        = read_status_cfg->busy_val;
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_RESSTS_DLY      = (uint32_t) (read_status_cfg->read_stat_del & 0x3F);
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_STSDLY_SEL      = (uint32_t) (read_status_cfg->read_stat_reg_cnt & 0x01);
    r_ospi_w_device_set_read_status_dummy_bytes(read_status_cfg->dummy_bytes);
    OQSPIF->OQSPIF_STATUSCMD_REG_b.OSPIC_RSTAT_DMY_ZERO = read_status_cfg->dummy_val;
}

__STATIC_FORCEINLINE void r_ospi_w_device_write_enable_instr_init (const ospi_w_device_write_enable_instr_config_t
                                                                   * write_enable_cfg)
{
    ASSERT_WARNING(IS_OSPI_W_DEVICE_BUS_MODE(write_enable_cfg->instr_bus_mode));

    OQSPIF->OQSPIF_ERASECMDA_REG_b.OSPIC_WEN_INST  = write_enable_cfg->instr;
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_WEN_TX_MD = write_enable_cfg->instr_bus_mode;
}

__STATIC_FORCEINLINE void r_ospi_w_device_suspend_resume_instr_init (const ospi_w_device_suspend_resume_instr_config_t
                                                                     * suspend_resume_cfg)
{
    OQSPIF->OQSPIF_ERASECMDA_REG_b.OSPIC_SUS_INST   = suspend_resume_cfg->suspend_instr;
    OQSPIF->OQSPIF_ERASECMDA_REG_b.OSPIC_RES_INST   = suspend_resume_cfg->resume_instr;
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_SUS_TX_MD  = suspend_resume_cfg->suspend_bus_mode;
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_RES_TX_MD  = suspend_resume_cfg->resume_bus_mode;
    OQSPIF->OQSPIF_ERASECMDB_REG_b.OSPIC_RESSUS_DLY = suspend_resume_cfg->read_stat_del;
}

/*
 * OSPI_W instructions initialization function (auto access mode)
 *
 * Use this function in order to initialize/setup the internal finite state machine
 * of the OSPI_W which is responsible for implementing the required protocol in auto
 * access mode. Instantiate a type ospi_w_device_instr_config_t struct, initialize it with
 * the desired OSPI_W settings and call this function passing the pointer of the
 * struct as input argument. Before calling this function the OSPI_W has to be
 * initialized in auto mode by calling the refer r_ospi_w_device_init.
 */
BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_instr_init(const ospi_w_device_instr_config_t * oqspi_instr_cfg);

/*
 * Set the address of the block/sector that is requested to be erased.
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_erase_address (uint32_t erase_addr)
{
    OQSPIF->OQSPIF_ERASECTRL_REG_b.OSPIC_ERS_ADDR = (uint32_t) (erase_addr & 0xFFFFF);
}

/*
 * Trigger erase block/sector
 */
__STATIC_FORCEINLINE void r_ospi_w_device_trigger_erase (void)
{
    OQSPIF->OQSPIF_ERASECTRL_REG_b.OSPIC_ERASE_EN = 1;
}

/*
 * Get erase status
 */
__STATIC_FORCEINLINE ospi_w_device_ers r_ospi_w_device_get_erase_status (void)
{
    // Dummy access to OQSPIF_CHCKERASE_REG in order to trigger a read status command
    OQSPIF->OQSPIF_CHCKERASE_REG_b.OSPIC_CHCKERASE = 0;

    return (ospi_w_device_ers) OQSPIF->OQSPIF_ERASECTRL_REG_b.OSPIC_ERS_STATE;
}

/*
 * Disable the erase resume procedure. The erase will not be resumed after the
 * expiration of the OSPIC_ERSRES_HLD unless re-enabling the corresponding setting by
 * calling r_ospi_w_device_enable_erase_resume().
 */
__STATIC_FORCEINLINE void r_ospi_w_device_disable_erase_resume (void)
{
    OQSPIF->OQSPIF_ERASECTRL_REG_b.OSPIC_ERS_RES_DIS = 1;
}

/*
 * Enable the erase resume procedure
 */
__STATIC_FORCEINLINE void r_ospi_w_device_enable_erase_resume (void)
{
    OQSPIF->OQSPIF_ERASECTRL_REG_b.OSPIC_ERS_RES_DIS = 0;
}

/*
 * Erase block/sector of flash memory
 *
 * Before erasing the flash memory, it is mandatory to set up the erase instructions
 * first by calling r_ospi_w_device_erase_instr_init().
 *
 * Call r_ospi_w_device_get_erase_status() to check whether the erase operation has finished.
 *
 * Before switching the OSPI controller to manual mode check that
 * r_ospi_w_device_get_erase_status() == ospi_w_device_ERS_NO.
 */
BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_erase_block(uint32_t addr);

/*
 * Enable the AES-CTR decryption
 */
__STATIC_FORCEINLINE void r_ospi_w_device_enable_aes_ctr (void)
{
    OQSPIF->OQSPIF_CTR_CTRL_REG_b.OSPIC_CTR_EN = 1;
    __ISB();
}

/*
 * Disable the AES-CTR decryption
 */
__STATIC_FORCEINLINE void r_ospi_w_device_disable_aes_ctr (void)
{
    OQSPIF->OQSPIF_CTR_CTRL_REG_b.OSPIC_CTR_EN = 0;
    __ISB();
}

/*
 * Set the nonce value used by AES-CTR decryption algorithm
 *
 * The OQSPI controller decrypts Flash contents on-the-fly using AES-CTR. AES-CTR uses
 * a 16-byte counter block (CTRB). The first 8 bytes of CTRB consist of the NONCE while
 * the other 8-bytes are produced automatically by the hardware.
 */
BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_set_aes_ctr_nonce(const uint8_t * nonce);

/*
 * Set the key for AES-CTR decryption
 */
BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_set_aes_ctr_key(const uint8_t * key);

/*
 * Set the OQSPI flash memory address range where its contents will be decrypted
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_aes_ctr_addr_range (uint32_t saddr, uint32_t eaddr)
{
    ASSERT_ERROR((eaddr > (saddr + 0x3FF)) || ((eaddr == 0x0) && (saddr == 0x0)));

    REG_SETF(OQSPIF, OQSPIF_CTR_SADDR_REG, OSPIC_CTR_SADDR, saddr >> 10);
    REG_SETF(OQSPIF, OQSPIF_CTR_EADDR_REG, OSPIC_CTR_EADDR, eaddr >> 10);
}

/*
 * OQSPI controller AES-CTR decryption initialization function
 */
BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_aes_ctr_init(const ospi_w_device_aes_ctr_config_t * cfg);

/*
 * Set an extra byte to use with read instructions
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_extra_byte (uint8_t                extra_byte,
                                                          ospi_w_device_bus_mode bus_mode,
                                                          bool                   half_disable_out)
{
    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_EXT_BYTE  = extra_byte;
    OQSPIF->OQSPIF_BURSTCMDA_REG_b.OSPIC_EXT_TX_MD = bus_mode;

    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_EXT_BYTE_EN = 1;
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_EXT_HF_DS   = half_disable_out;
}

/*
 * Set the number of clocks cycles that CS stays high between the transmissions of two
 * different instructions
 */
__STATIC_FORCEINLINE void r_ospi_w_device_set_min_cs_high (uint8_t clock_count)
{
    ASSERT_WARNING(clock_count < 8);
    OQSPIF->OQSPIF_BURSTCMDB_REG_b.OSPIC_CS_HIGH_MIN = (uint32_t) (clock_count & 0x07);
}

/*
 * Enable burst break sequence
 */
__STATIC_FORCEINLINE void r_ospi_w_device_burst_break_sequence_enable (uint16_t                     sequence,
                                                                       ospi_w_device_bus_mode       mode,
                                                                       ospi_w_device_break_seq_size size,
                                                                       bool                         dis_out)
{
    OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_SEC_HF_DS = dis_out;
    OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_SZ    = size;
    OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_TX_MD = mode;
    OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_EN    = 1;
    OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_WRD   = sequence;
}

/*
 * Disable burst break sequence
 *
 */
__STATIC_FORCEINLINE void r_ospi_w_device_burst_break_sequence_disable (void)
{
    OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_EN = 0;
}

/*
 * Defines the behavior of the controller when the internal buffer is full
 * and there are more data to be retrieved for the current burst.
 * It has meaning only for reads in auto mode.
 */
__STATIC_FORCEINLINE void r_ospi_w_device_buf_lim (bool enable)
{
    OQSPIF->OQSPIF_CTRLMODE_REG_b.OSPIC_BUF_LIM_EN = enable;
}

/*
 * Fast copy of a buffer to a FIFO
 * Implementation of a fast copy of the contents of a buffer to a FIFO in assembly. All
 * addresses are word aligned.
 */
__STATIC_FORCEINLINE void fast_write_to_fifo32 (uint32_t start, uint32_t end, uint32_t dest)
{
    __asm__ volatile (   "copy:                                  \n"
                     "       ldmia %[start]!, {r3}           \n"
                     "       str r3, [%[dest]]               \n"
                     "       cmp %[start], %[end]            \n"
                     "       blt copy                        \n"
                     :
                     :                                                         /* output */
                     [start] "l" (start), [end] "r" (end), [dest] "l" (dest) : /* inputs (%0, %1, %2) */
                     "r3");                                                 /* registers that are destroyed */
}

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern spi_flash_api_t g_ospi_w_on_spi_flash;

/** @endcond */
fsp_err_t R_OSPI_W_Open(spi_flash_ctrl_t * const p_ctrl, spi_flash_cfg_t const * const p_cfg);
fsp_err_t R_OSPI_W_Close(spi_flash_ctrl_t * const p_ctrl);
fsp_err_t R_OSPI_W_DirectWrite(spi_flash_ctrl_t * const p_ctrl,
                               uint8_t const * const    p_src,
                               uint32_t const           bytes,
                               bool const               read_after_write);
fsp_err_t R_OSPI_W_DirectRead(spi_flash_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_OSPI_W_DirectTransfer(spi_flash_ctrl_t * const            p_ctrl,
                                  spi_flash_direct_transfer_t * const p_transfer,
                                  spi_flash_direct_transfer_dir_t     direction);
fsp_err_t R_OSPI_W_SpiProtocolSet(spi_flash_ctrl_t * const p_ctrl, spi_flash_protocol_t spi_protocol);
fsp_err_t R_OSPI_W_XipEnter(spi_flash_ctrl_t * const p_ctrl);
fsp_err_t R_OSPI_W_XipExit(spi_flash_ctrl_t * const p_ctrl);
fsp_err_t R_OSPI_W_Write(spi_flash_ctrl_t * const p_ctrl,
                         uint8_t const * const    p_src,
                         uint8_t * const          p_dest,
                         uint32_t                 byte_count);
fsp_err_t R_OSPI_W_Erase(spi_flash_ctrl_t * const p_ctrl, uint8_t * const p_device_address, uint32_t byte_count);
fsp_err_t R_OSPI_W_StatusGet(spi_flash_ctrl_t * const p_ctrl, spi_flash_status_t * const p_status);
fsp_err_t R_OSPI_W_BankSet(spi_flash_ctrl_t * const _ctrl, uint32_t bank);
fsp_err_t R_OSPI_W_AutoCalibrate(spi_flash_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup OSPI_W)
 **********************************************************************************************************************/
