/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_QSPI_W_H
#define R_QSPI_W_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_qspi_w_cfg.h"
#include "r_spi_flash_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup QSPI_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define QSPI_W_DEVICE_START_ADDRESS         (BSP_FEATURE_QSPI_DEVICE_START_ADDRESS)
#define QSPI_W_DEVICE_START_ADDRESS_DATA    (BSP_FEATURE_QSPI_DEVICE_START_ADDRESS_DATA)

/* If Code Flash programming is enabled, then all API functions must execute out of RAM. */
#define PLACE_IN_RAM_SECTION

/* TODO: This needs to be added in r_spi_flash_api.h in the next FSP API Release */
#define SPI_FLASH_DUMMY_CLOCKS_32    (32) ///< 32 dummy clocks

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Cache control. */
typedef enum e_qspi_w_dcache
{
    QSPI_W_DCACHE_DISABLE,             ///< Disable dcache.
    QSPI_W_DCACHE_ENABLE,              ///< Enable dcache.
} qspi_w_dcache_t;

/** QSPI_W memory access mode. */
typedef enum e_qspi_w_access_mode
{
    QSPI_W_ACCESS_MODE_MANUAL = 0,     ///< Direct register access using the QSPI_W register file.
    QSPI_W_ACCESS_MODE_AUTO   = 1,     ///< Up to 32 MB memory-mapped access with 3- and 4-byte addressing modes.
} qspi_w_access_mode_t;

/** QSPI_W Bus mode. */
typedef enum e_qspi_w_bus_mode
{
    QSPI_W_BUS_MODE_SINGLE,            ///< Bus mode in single mode.
    QSPI_W_BUS_MODE_DUAL,              ///< Bus mode in dual mode.
    QSPI_W_BUS_MODE_QUAD,              ///< Bus mode in quad mode.
} qspi_w_bus_mode_t;

/** QSPCLK divider. */
typedef enum e_qspi_w_qspclk_div
{
    QSPI_W_QSPCLK_DIV_1 = 0x0,         ///< QSPI_CLK = SYS_CLK / 1
    QSPI_W_QSPCLK_DIV_2 = 0x1,         ///< QSPI_CLK = SYS_CLK / 2
#if defined(BSP_MCU_GROUP_RA6W1)
    QSPI_W_QSPCLK_DIV_4 = 0x2,         ///< QSPI_CLK = SYS_CLK / 4
    QSPI_W_QSPCLK_DIV_8 = 0x3,         ///< QSPI_CLK = SYS_CLK / 8
#endif
} qspi_w_qspclk_div_t;

/** The progress of sector/block erasing. */
typedef enum e_qspi_w_ers
{
    QSPI_W_ERS_NO        = 0,          ///< No erase.
    QSPI_W_ERS_PENDING   = 1,          ///< Pending erase request.
    QSPI_W_ERS_RUNNING   = 2,          ///< Erase procedure is running.
    QSPI_W_ERS_SUSPENDED = 3,          ///< Suspended erase procedure.
    QSPI_W_ERS_FINISHING = 4,          ///< Finishing the erase procedure.
} qspi_w_ers_t;

/** QSPI clock mode. */
typedef enum e_qspi_w_clk_mode
{
    QSPI_W_CLK_MODE_LOW  = 0,          ///< Mode 0: QSPI_SCK is low when QSPI_CS is high.
    QSPI_W_CLK_MODE_HIGH = 1,          ///< Mode 3: QSPI_SCK is high when QSPI_CS is high.
} qspi_w_clk_mode_t;

/** QSPIC pads drive current strength. */
typedef enum e_qspi_w_drive_current
{
#if defined(BSP_MCU_GROUP_RA6W1)
    QSPI_W_DRIVE_CURRENT_2  = 0,       ///< 2 mA.
    QSPI_W_DRIVE_CURRENT_4  = 1,       ///< 4 mA.
    QSPI_W_DRIVE_CURRENT_8  = 2,       ///< 8 mA.
    QSPI_W_DRIVE_CURRENT_14 = 3,       ///< 14 mA.
#else
    QSPI_W_DRIVE_CURRENT_4  = 0,       ///< 4 mA.
    QSPI_W_DRIVE_CURRENT_8  = 1,       ///< 8 mA.
    QSPI_W_DRIVE_CURRENT_12 = 2,       ///< 12 mA.
    QSPI_W_DRIVE_CURRENT_16 = 3,       ///< 16 mA.
#endif
} qspi_w_drive_current_t;

/**
 * QSPIC read pipe setting.
 *
 * When read pipe is disabled the sampling clock is determined by QSPI_W_SAMPLING_EDGE
 * otherwise by QSPI_W_READ_PIPE_DELAY.
 */
typedef enum e_qspi_w_read_pipe
{
    QSPI_W_READ_PIPE_DISABLE = 0,      ///< Disable read pipe delay.
    QSPI_W_READ_PIPE_ENABLE  = 1,      ///< Enable read pipe delay.
} qspi_w_read_pipe_t;

/**
 * QSPIC Read pipe clock delay in relation to the falling edge of QSPI_SCK.
 *
 * The read pipe delay should be set based on the voltage level of the power rail V12.
 */
typedef enum e_qspi_w_read_pipe_delay
{
    QSPI_W_READ_PIPE_DELAY_0 = 0,      ///< Set read pipe delay to 0.
    QSPI_W_READ_PIPE_DELAY_1 = 1,      ///< Set read pipe delay to 1.
    QSPI_W_READ_PIPE_DELAY_2 = 2,      ///< Set read pipe delay to 2.
    QSPI_W_READ_PIPE_DELAY_3 = 3,      ///< Set read pipe delay to 3.
    QSPI_W_READ_PIPE_DELAY_4 = 4,      ///< Set read pipe delay to 4.
    QSPI_W_READ_PIPE_DELAY_5 = 5,      ///< Set read pipe delay to 5.
    QSPI_W_READ_PIPE_DELAY_6 = 6,      ///< Set read pipe delay to 6.
    QSPI_W_READ_PIPE_DELAY_7 = 7,      ///< Set read pipe delay to 7.
} qspi_w_read_pipe_delay_t;

/** QSPIC pads slew rate. */
typedef enum e_qspi_w_slew_rate
{
#if defined(BSP_MCU_GROUP_RA6W3)
    QSPI_W_SLEW_RATE_0 = 0,            ///< Rise = 1.7 V/ns, Fall = 1.9 V/ns (weak).
    QSPI_W_SLEW_RATE_1 = 1,            ///< Rise = 2.0 V/ns, Fall = 2.3 V/ns.
    QSPI_W_SLEW_RATE_2 = 2,            ///< Rise = 2.3 V/ns, Fall = 2.6 V.
    QSPI_W_SLEW_RATE_3 = 3,            ///< Rise = 2.4 V/ns, Fall = 2.7 V/ns (strong)
#else
    QSPI_W_SLEW_RATE_FAST = 0,         ///< Fast Slew Rate.
    QSPI_W_SLEW_RATE_SLOW = 1,         ///< Slower Slew Rate.
#endif
} qspi_w_slew_rate_t;

/**
 * QSPIC HREADY signal mode when accessing the WRITEDATA, READDATA and DUMMYDATA registers.
 *
 * This configuration is useful when the frequency of the QSPI clock is much lower than
 * the clock of the AMBA bus, in order to avoid locking the AMBA bus for a long time.
 * When is set to QSPI_W_HREADY_MODE_WAIT there is no need to check the QSPIC_BUSY
 * for detecting completion of the requested access.
 */
typedef enum e_qspi_w_hready_mode
{
    QSPI_W_HREADY_MODE_WAIT    = 0,    ///< Adds wait states via hready signal when accessing the QSPIC_WRITEDATA, QSPIC_READDATA and QSPIC_DUMMYDATA registers.
    QSPI_W_HREADY_MODE_NO_WAIT = 1,    ///< Don't add wait states via the HREADY signal.
} qspi_w_hready_mode_t;

/** QSPIC instruction mode. */
typedef enum e_qspi_w_instr_md
{
    QSPI_W_INSTR_MD_TX_AT_ANY_BURST_ACCESS  = 0, ///< Transmit instruction at any burst access.
    QSPI_W_INSTR_MD_TX_ONLY_IN_FIRST_ACCESS = 1, ///< Transmit instruction only in the first access after the selection of Auto Mode.
} qspi_w_instr_md_t;

/** QSPIC wrap mode enable bit. */
typedef enum e_qspi_w_wrap_md
{
    QSPI_W_WRAP_MD_SEL_INSTR    = 0,   ///< The QSPIC_INST is the selected instruction at any read access.
    QSPI_W_WRAP_MD_SEL_INSTR_WB = 1,   ///< The QSPIC_INST_WB is the selected instruction at any read wrapping burst access.
} qspi_w_wrap_md_t;

/** QSPIC write wrapping burst will be implemented by using a special write instruction. */
typedef enum e_qspi_w_wrap_wr_en
{
    QSPI_W_WRAP_WR_EN_INST    = 0,     ///< Select QSPIC_WR_INST.
    QSPI_W_WRAP_WR_EN_INST_WB = 1,     ///< Select QSPIC_WR_INST_WB.
} qspi_w_wrap_wr_en_t;

/** QSPIC behavior when a read burst is terminated early in the AMBA bus. */
typedef enum e_qspi_w_rd_bend_md
{
    QSPI_W_RD_BEND_MD_TERMINATE_ASAP      = 0, ///< The corresponding read burst in the memory device will be terminated as soon as possible, based on the pipeline of the controller.
    QSPI_W_RD_BEND_MD_TERMINATE_WHEN_DONE = 1, ///< The read burst in the memory device will be terminated only after filling the last position of the current read buffer.
} qspi_w_rd_bend_md_t;

/** Set the read pipeline in burst mode while retrieving the data of the memory device. */
typedef enum e_qspi_w_rd_rdb_en
{
    QSPI_W_RD_RDB_EN_MIN_CLK_PULSES = 0, ///< The controller will provide the minimum required number of clock pulses in the interface during the reading of the data.
    QSPI_W_RD_RDB_EN_UNTIL_DONE     = 1, ///< Set the read pipeline in burst mode while the data are retrieved of the memory device.
} qspi_w_rd_rdb_en_t;

/** QSPIC extra byte setting in auto access mode. */
typedef enum e_qspi_w_extra_byte
{
    QSPI_W_EXTRA_BYTE_DISABLE = 0,     ///< Disable extra byte phase.
    QSPI_W_EXTRA_BYTE_ENABLE  = 1,     ///< Enable extra byte phase.
} qspi_w_extra_byte_t;

/**
 * QSPIC extra byte half setting in auto access mode.
 *
 * This setting is out of scope if the extra byte is disabled.
 */
typedef enum e_qspi_w_extra_byte_half
{
    QSPI_W_EXTRA_BYTE_HALF_DISABLE = 0, ///< Transmit the complete extra byte.
    QSPI_W_EXTRA_BYTE_HALF_ENABLE  = 1, ///< The output switches to Hi-Z during the transmission of the low nibble of the extra byte.
} qspi_w_extra_byte_half_t;

/** QSPIC break enable/disable. */
typedef enum e_qspi_w_break
{
    QSPI_W_BREAK_DISABLE = 0,          ///< Disable break command.
    QSPI_W_BREAK_ENABLE  = 1,          ///< Enable break command.
} qspi_w_break_t;

/**
 * QSPIC Disable output during the transmission of the second half (QSPIC_BRK_WRD[3:0]).
 *
 * Setting this bit is only useful if QSPIC_BRK_EN =1 and QSPIC_BRK_SZ= 1.
 */
typedef enum e_qspi_w_break_sec_hf
{
    QSPI_W_BREAK_SEC_HF_DRIVE = 0,     ///< The controller drives the SPI bus during the transmission of the QSPIC_BRK_WRD[3:0].
    QSPI_W_BREAK_SEC_HF_HIZ   = 1,     ///< The controller leaves the SPI bus in Hi-Z during the transmission of the QSPIC_BRK_WORD[3:0].
} qspi_w_break_sec_hf_t;

/** QSPIC tCEM enable/disable. */
typedef enum e_qspi_w_t_cem
{
    QSPI_W_T_CEM_DISABLE = 0,          ///< Disable tCEM control.
    QSPI_W_T_CEM_ENABLE  = 1,          ///< Enable tCEM control.
} qspi_w_t_cem_t;

/** Length of a burst operation for a QSPI RAM device. */
typedef enum e_qspi_w_memblen_burst
{
    QSPI_W_MEMBLEN_BURST_INCR_UNSPECIFIED = 0, ///< The external memory device implements incremental burst of unspecified length.
    QSPI_W_MEMBLEN_BURST_WRAP_4B,              ///< The external memory device implements a wrapping burst of length 4 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_8B,              ///< The external memory device implements a wrapping burst of length 8 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_16B,             ///< The external memory device implements a wrapping burst of length 16 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_32B,             ///< The external memory device implements a wrapping burst of length 32 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_64B,             ///< The external memory device implements a wrapping burst of length 64 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_128B,            ///< The external memory device implements a wrapping burst of length 128 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_256B,            ///< The external memory device implements a wrapping burst of length 256 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_512B,            ///< The external memory device implements a wrapping burst of length 512 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_1024B,           ///< The external memory device implements a wrapping burst of length 1024 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_2048B,           ///< The external memory device implements a wrapping burst of length 2048 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_4096B,           ///< The external memory device implements a wrapping burst of length 4096 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_8192B,           ///< The external memory device implements a wrapping burst of length 8192 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_16384B,          ///< The external memory device implements a wrapping burst of length 16384 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_32768B,          ///< The external memory device implements a wrapping burst of length 32768 bytes.
    QSPI_W_MEMBLEN_BURST_WRAP_65536B,          ///< The external memory device implements a wrapping burst of length 65536 bytes.
} qspi_w_memblen_burst_t;

/**
 * QSPI clock edge setting for the sampling of the incoming data when the read pipe is disabled.
 */
typedef enum e_qspi_w_sampling_edge
{
    QSPI_W_SAMPLING_EDGE_POS = 0,      ///< The incoming data sampling is triggered by the positive edge of QSPI clock signal.
    QSPI_W_SAMPLING_EDGE_NEG = 1,      ///< The incoming data sampling is triggered by the negative edge of QSPI clock signal.
} qspi_w_sampling_edge_t;

/** QSPI DDR or SDR mode. */
typedef enum e_qspi_w_mode
{
    QSPI_W_MODE_DDR = 0,               ///< QSPI DDR (double data rate) mode.
    QSPI_W_MODE_SDR = 1,               ///< QSPI SDR (single data rate) mode.
} qspi_w_mode_t;

/** QSPI device busy status setting. */
typedef enum e_qspi_w_busy_level
{
    QSPI_W_BUSY_LEVEL_LOW  = 0,        ///< The QSPI device is busy when the pin level bit is low.
    QSPI_W_BUSY_LEVEL_HIGH = 1,        ///< The QSPI device is busy when the pin level bit is high.
} qspi_w_busy_level_t;

/**
 * QSPIC timer which is used to count the delay that it has to wait before to read the Flash status register,
 * after an erase or an erase resume command.
 */
typedef enum e_qspi_w_stsdly_sel
{
    QSPI_W_STSDLY_SEL_RESSTS_DLY = 0,  ///< The delay is controlled by the QSPIC_RESSTS_DLY which counts on the QSPI_SCK clock.
    QSPI_W_STSDLY_SEL_RESSUS_DLY = 1,  ///< The delay is controlled by the QSPIC_RESSUS_DLY which counts on the 222 kHz clock.
} qspi_w_stsdly_sel_t;

/** QSPIC value that is transferred on the SPI bus during the phase of the dummy bytes. */
typedef enum e_qspi_w_dummy_value
{
    QSPI_W_RSTAT_DMY_ZERO_KEEP_UNCHANGED = 0, ///< The controller keeps the data in the bus unchanged, until to change the bus direction in input mode.
    QSPI_W_RSTAT_DMY_ZERO_FORCE_ZERO     = 1, ///< Forces the dummy bytes to get the zero value (only for the cycles that are not in input mode).
} qspi_w_dummy_value_t;

/** Read instruction configuration structure (auto access mode). */
typedef struct st_qspi_w_read_instr_cfg
{
    uint8_t           opcode;                         ///< Read command opcode for Incremental Burst or Single read access.
    uint8_t           opcode_wb;                      ///< Read command opcode for Wrapping Burst.
    uint8_t           extra_byte_value;               ///< Extra Byte value.
    qspi_w_bus_mode_t opcode_bus_mode     : 2;        ///< Bus mode of the opcode phase.
    qspi_w_bus_mode_t addr_bus_mode       : 2;        ///< Bus mode of the address phase.
    qspi_w_bus_mode_t extra_byte_bus_mode : 2;        ///< Bus mode of the extra byte phase.
    qspi_w_bus_mode_t dummy_bus_mode      : 2;        ///< Bus mode of the dummy phase.

    qspi_w_bus_mode_t        data_bus_mode       : 2; ///< Bus mode of the data phase.
    qspi_w_extra_byte_t      extra_byte_en       : 1; ///< Enable Extra Byte.
    qspi_w_extra_byte_half_t extra_byte_half_cfg : 1; ///< Enable Extra Byte Half.
    uint8_t             dummy_bytes              : 5; ///< The number of dummy bytes. Valid values are 0..31 i.e. 1..32 dummy bytes.
    bool                dummy_en;                     ///< Enable dummy bytes.
    bool                dummy_force;                  ///< On setting this bit the no: of dummy bytes is set to 3 always irrespective of value provided in dummy_bytes.
    qspi_w_instr_md_t   instr_md           : 1;       ///< Instruction mode.
    qspi_w_wrap_md_t    wrap_md            : 1;       ///< Wrap mode enable bit.
    uint8_t             wrap_blen          : 3;       ///< It describes the length in number of bytes of the selected wrapping burst(see also the register QSPIC_WRAP_MD).
    uint8_t             wrap_size          : 2;       ///< Selected data size of a wrapping burst.
    qspi_w_wrap_wr_en_t wrap_wr_en         : 1;       ///< By setting (1) this bit, any write wrapping burst will be implemented by using a special write instruction.
    uint8_t             cs_high_min_cycles : 5;       ///< The SPI bus stays in idle state (QSPI_CS high) for at least this number of QSPI_SCK clock cycles between two consecutive read commands.
    qspi_w_rd_bend_md_t rd_bend_md         : 1;       ///< Defines the behavior of the controller when a read burst is terminated early in the AMBA bus.
    qspi_w_rd_rdb_en_t  rd_rdb_en          : 1;       ///< Write 1 to set the read pipeline in burst mode while are retrieved the data of the memory device.
} qspi_w_read_instr_cfg_t;

/** QSPIC read status instruction configuration structure (auto access mode). */
typedef struct st_qspi_w_read_status_instr_cfg
{
    uint8_t              opcode;               ///< Read Status command opcode.
    qspi_w_bus_mode_t    opcode_bus_mode  : 2; ///< The bus mode of the opcode phase.
    qspi_w_bus_mode_t    receive_bus_mode : 2; ///< The bus mode of the receive data phase.
    uint32_t             busy_pos         : 3; ///< The position of the Busy bit in the status register (0 - 7).
    uint8_t              delay_cycles     : 7; ///< The minimum delay in clock cycles between a Read Status command and the previous Erase command. Usually NOT needed thus is set equal to 0.
    qspi_w_stsdly_sel_t  stsdly_sel       : 1; ///< Select the timer which is used to count the delay before reading the flash status register, after an erase or an erase resume command.
    qspi_w_busy_level_t  busy_level       : 1; ///< Busy bit level.
    uint8_t              rstat_dmy_num    : 4; ///< Number of dummy bytes (minus 1).
    qspi_w_bus_mode_t    dummy_bus_mode   : 2; ///< The bus mode of the dummy data phase.
    qspi_w_dummy_value_t dummy_value      : 1; ///< Define the value that is transferred on the SPI bus during the phase of the dummy bytes.
    bool                 rstat_dmy_en;         ///< Enables the transmission of dummy bytes, immediately after the instruction code of the read status command.
    bool                 rstat_rdb_en;         ///< If enabled, sets the read pipeline in burst mode while is retrieved the status of the memory device.
    bool                 rstat_split_en;       ///< If enabled, a long sequence for the continuous reading of the status register will be divided into individual accesses.
    bool                 rstat_req;            ///< If enabled, the value of the status register of the memory device will be retrieved.
} qspi_w_read_status_instr_cfg_t;

/** QSPIC Erase instruction configuration structure (auto access mode). */
typedef struct st_qspi_w_erase_instr_cfg
{
    qspi_w_bus_mode_t opcode_bus_mode : 2;      ///< Bus mode of the opcode phase.
    qspi_w_bus_mode_t addr_bus_mode   : 2;      ///< Bus mode of the address phase.
    uint32_t          hclk_cycles     : 4;      ///< The number of AMBA AHB hclk cycles (0..15) without memory read requests before executing an erase or erase resume command. Use this setting to delay one of the aforementioned commands otherwise keep it 0.
    uint8_t           opcode;                   ///< Erase command opcode.
    uint8_t           cs_idle_delay_cycles : 5; ///< The minimum CS idle delay in clock cycles (< 32) between a Write Enable, Erase, Erase Suspend or Erase Resume command and the next consecutive command.
} qspi_w_erase_instr_cfg_t;

/** QSPIC Erase suspend/resume instruction structure (auto access mode). */
typedef struct st_qspi_w_suspend_resume_instr_cfg
{
    qspi_w_bus_mode_t suspend_bus_mode : 2;           ///< Bus mode during the erase suspend command phase.
    qspi_w_bus_mode_t resume_bus_mode  : 2;           ///< Bus mode during the erase resume command phase.
    uint8_t           suspend_opcode;                 ///< Erase suspend instruction code.
    uint8_t           resume_opcode;                  ///< Erase resume instruction code.
    uint8_t           res_sus_latency_clk_cycles : 6; ///< The minimum required latency (clock cycles) between an erase resume and the next consequent erase suspend command.
    uint8_t           sussts_dly                 : 6; ///< Defines a timer that counts the minimum allowed delay between an erase suspend command and the next read status command.
} qspi_w_suspend_resume_instr_cfg_t;

/** QSPIC Read break sequence structure (auto access mode). */
typedef struct st_qspi_w_break_instr_cfg
{
    uint16_t              break_opcode;     ///< The code value of the read break instruction.
    uint8_t               break_sz     : 4; ///< The size of Burst Break Sequence 1..16 bytes.
    qspi_w_bus_mode_t     break_tx_md  : 2; ///< The mode of the QSPI Bus during the transmission of the burst break sequence.
    qspi_w_break_sec_hf_t break_sec_hf : 1; ///< Disable output during the transmission of the second half.
    qspi_w_break_t        break_en     : 1; ///< Controls the application of a special command (read burst break sequence) that is used in order to force the device to abandon the continuous read mode.
} qspi_w_break_instr_cfg_t;

/** QSPIC External memory burst length configuration. */
typedef struct st_qspi_w_memblen_cfg
{
    qspi_w_memblen_burst_t memblen : 4;  ///< In this register is defined the expected behavior of the external memory device regarding the length of a burst operation.
    uint16_t               tcem_cc : 12; ///< Defines the maximum allowed time tCEM for which the QSPIC_CS can stay active (when tcem_en=1).
    qspi_w_t_cem_t         tcem_en : 1;  ///< This bit enables the controlling of the maximum time tCEM for which the QSPI_CS remains active (auto mode and PSRAM).
    bool    rd_lin_en              : 1;  ///< By setting (1) in this bit the access limits that are set with the QSPIC_MEMBLEN are ignored for the read operation.
    bool    keep_active            : 1;  ///< By setting (1) in this bit the controller will keep the access active in order to serve consecutive accesses, without toggling the chip select of the memory,when this is possible.
    bool    wcmd_hybrid            : 1;  ///< By setting (1) in this bit, the special commands that used during wrap bursts.
    uint8_t dielen                 : 4;  ///< The size of each die from which the memory device is consisted.
    uint8_t active_thr             : 4;  ///< Defines the maximum number of AHB clock cycles for which the memory should stay without access, before the active access to be aborted.
} qspi_w_memblen_cfg_t;

/** QSPIC Write instruction structure (manual & auto access mode). */
typedef struct st_qspi_w_write_instr_cfg
{
    uint8_t           write_opcode;             ///< The code value of the write instruction.
    uint8_t           write_opcode_wb;          ///< The code value of the write instruction in wrapping burst.
    qspi_w_bus_mode_t opcode_bus_mode : 2;      ///< Bus mode of the opcode phase.
    qspi_w_bus_mode_t addr_bus_mode   : 2;      ///< Bus mode of the address phase.
    qspi_w_bus_mode_t data_bus_mode   : 2;      ///< Bus mode of the data phase.
    qspi_w_bus_mode_t dummy_bus_mode  : 2;      ///< Bus mode of the dummy data phase.
    uint8_t           dummy_bytes     : 5;      ///< The number of dummy bytes. Valid values are 0..31 i.e. 1..32 dummy bytes.
    bool              dummy_en;                 ///< Enable dummy bytes.
    bool              wdex_en;                  ///< If enabled wait until the write data to be available before to start sending the write command sequence.
    uint8_t           cs_hi_min_clk_cycles : 5; ///< After the execution of the write command, the QSPI_CS remains high for at least this number of QSPI_SCK clock cycles.
    bool              send_wen_req;             ///< If enabled the controller will apply the write enable command.
} qspi_w_write_instr_cfg_t;

/** QSPIC write enable instruction configuration structure (auto access mode). */
typedef struct st_qspi_w_write_enable_instr_cfg
{
    qspi_w_bus_mode_t opcode_bus_mode : 2; ///< Bus mode of the opcode phase.
    uint8_t           opcode;              ///< Write Enable command opcode.
} qspi_w_write_enable_instr_cfg_t;

/** QSPIC Double Data Rate (DDR) configuration structure. */
typedef struct st_qspi_w_ctrl_ddr_cfg
{
    uint32_t ctrl_ddra;                ///< DDR Control register A.
    uint32_t ctrl_ddrb;                ///< DDR Control register B.
} qspi_w_ctrl_ddr_cfg_t;

/** QSPIC Double Data Rate (DDR) configuration structure. */
typedef struct st_qspi_w_extra_registers_cfg
{
    uint32_t ctrl_mr_reg;              ///< Control MR register.
    uint32_t drst_cmd_reg;             ///< DRST command register.
} qspi_w_extra_registers_cfg_t;

/**
 * QSPI memory configuration structure.
 *
 * This struct is used to define a driver for a specific QSPI memory.
 */
typedef struct st_qspi_w_flash_cfg
{
    bool                                is_ram;                     ///< Is QSPIC interfaced with a PSRAM device.
    qspi_w_clk_mode_t                   clk_mode : 1;               ///< Clock Mode.
    qspi_w_read_instr_cfg_t           * p_read_instr_cfg;           ///< Read instruction configuration struct.
    qspi_w_erase_instr_cfg_t          * p_erase_instr_cfg;          ///< Erase instruction configuration struct.
    qspi_w_suspend_resume_instr_cfg_t * p_suspend_resume_instr_cfg; ///< Program and erase suspend/resume instruction
    ///< configuration struct.
    qspi_w_write_enable_instr_cfg_t * p_write_enable_instr_cfg;     ///< Write enable instruction configuration.
    qspi_w_read_status_instr_cfg_t  * p_read_status_instr_cfg;      ///< Read status register instruction
    ///< configuration struct.
    qspi_w_write_instr_cfg_t     * p_write_instr_cfg;               ///< Write instruction configuration struct.
    qspi_w_break_instr_cfg_t     * p_break_instr_cfg;               ///< Burst break instruction configuration struct.
    qspi_w_memblen_cfg_t         * p_memblen_cfg;                   ///< External memory burst length configuration struct.
    qspi_w_ctrl_ddr_cfg_t        * p_ctrl_ddr;                      ///< QSPI DDR Control registers configuration struct.
    qspi_w_extra_registers_cfg_t * p_extra_regs;                    ///< QSPI Extra registers configuration struct.
} qspi_w_flash_cfg_t;

/** Extended configuration for QSPIC. */
typedef struct st_qspi_w_extended_cfg
{
    uint8_t                    channel;            ///< Channel number to be used (0..1).
    qspi_w_mode_t              qspi_mode;          ///< QSPI DDR or SDR mode.
    qspi_w_qspclk_div_t        qspclk_div;         ///< QSPCLK divider.
    qspi_w_drive_current_t     qspi_drive_current; ///< Set the Drive Strength of the QSPI Controller.
    qspi_w_slew_rate_t         qspi_slew_rate;     ///< Set the Slew Rate of the QSPI Controller.
    qspi_w_flash_cfg_t const * p_qspi_flash_cfg;   ///< Pointer to qspi controller configuration struct.
    qspi_w_dcache_t            qspi_dcache;        ///< Data cache.
} qspi_w_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when spi_flash_api_t::open is called. */
typedef struct st_qspi_w_instance_ctrl
{
    spi_flash_cfg_t const * p_cfg;            ///< Pointer to initial configuration.
    spi_flash_data_lines_t  data_lines;       ///< Data lines.
    uint32_t                total_size_bytes; ///< Total size of the flash in bytes.
    uint32_t                open;             ///< Whether or not driver is open.
    bool xip_mode_is_enabled;                 ///< XiP mode is enabled or disabled.
} qspi_w_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_flash_api_t g_spi_flash_on_qspi_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_Open(spi_flash_ctrl_t * p_ctrl, spi_flash_cfg_t const * const p_cfg);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_Close(spi_flash_ctrl_t * p_ctrl);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_DirectWrite(spi_flash_ctrl_t    * p_ctrl,
                                                    uint8_t const * const p_src,
                                                    uint32_t const        bytes,
                                                    bool const            read_after_write);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_DirectRead(spi_flash_ctrl_t * p_ctrl,
                                                   uint8_t * const    p_dest,
                                                   uint32_t const     bytes);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_SpiProtocolSet(spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_XipEnter(spi_flash_ctrl_t * p_ctrl);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_XipExit(spi_flash_ctrl_t * p_ctrl);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_Write(spi_flash_ctrl_t    * p_ctrl,
                                              uint8_t const * const p_src,
                                              uint8_t * const       p_dest,
                                              uint32_t              byte_count);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_Erase(spi_flash_ctrl_t * p_ctrl,
                                              uint8_t * const    p_device_address,
                                              uint32_t           byte_count);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_StatusGet(spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_BankSet(spi_flash_ctrl_t * p_ctrl, uint32_t bank);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_DirectTransfer(spi_flash_ctrl_t                  * p_ctrl,
                                                       spi_flash_direct_transfer_t * const p_transfer,
                                                       spi_flash_direct_transfer_dir_t     direction);
PLACE_IN_RAM_SECTION fsp_err_t R_QSPI_W_AutoCalibrate(spi_flash_ctrl_t * p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup QSPI_W)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_QSPI_W_H */
