/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_SDHCI__
#define __DRV_SDHCI__

#define false 0
#define true 1
#define SDEMMC0_BASE 0x91580000
#define SDEMMC1_BASE 0x91581000
#define IRQN_SD0 142
#define IRQN_SD1 144

/*
 * Controller registers
 */

#define SDHCI_DMA_ADDRESS 0x00
#define SDHCI_ARGUMENT2 SDHCI_DMA_ADDRESS
#define SDHCI_32BIT_BLK_CNT SDHCI_DMA_ADDRESS

#define SDHCI_BLOCK_SIZE 0x04
#define SDHCI_MAKE_BLKSZ(dma, blksz) (((dma & 0x7) << 12) | (blksz & 0xFFF))

#define SDHCI_BLOCK_COUNT 0x06

#define SDHCI_ARGUMENT 0x08

#define SDHCI_TRANSFER_MODE 0x0C
#define SDHCI_TRNS_DMA 0x01
#define SDHCI_TRNS_BLK_CNT_EN 0x02
#define SDHCI_TRNS_AUTO_CMD12 0x04
#define SDHCI_TRNS_AUTO_CMD23 0x08
#define SDHCI_TRNS_AUTO_SEL 0x0C
#define SDHCI_TRNS_READ 0x10
#define SDHCI_TRNS_MULTI 0x20

#define SDHCI_COMMAND 0x0E
#define SDHCI_CMD_RESP_MASK 0x03
#define SDHCI_CMD_CRC 0x08
#define SDHCI_CMD_INDEX 0x10
#define SDHCI_CMD_DATA 0x20
#define SDHCI_CMD_ABORTCMD 0xC0

#define SDHCI_CMD_RESP_NONE 0x00
#define SDHCI_CMD_RESP_LONG 0x01
#define SDHCI_CMD_RESP_SHORT 0x02
#define SDHCI_CMD_RESP_SHORT_BUSY 0x03

#define SDHCI_MAKE_CMD(c, f) (((c & 0xff) << 8) | (f & 0xff))
#define SDHCI_GET_CMD(c) ((c >> 8) & 0x3f)

#define SDHCI_RESPONSE 0x10

#define SDHCI_BUFFER 0x20

#define SDHCI_PRESENT_STATE 0x24
#define SDHCI_CMD_INHIBIT 0x00000001
#define SDHCI_DATA_INHIBIT 0x00000002
#define SDHCI_DOING_WRITE 0x00000100
#define SDHCI_DOING_READ 0x00000200
#define SDHCI_SPACE_AVAILABLE 0x00000400
#define SDHCI_DATA_AVAILABLE 0x00000800
#define SDHCI_CARD_PRESENT 0x00010000
#define SDHCI_CARD_PRES_SHIFT 16
#define SDHCI_CD_STABLE 0x00020000
#define SDHCI_CD_LVL 0x00040000
#define SDHCI_CD_LVL_SHIFT 18
#define SDHCI_WRITE_PROTECT 0x00080000
#define SDHCI_DATA_LVL_MASK 0x00F00000
#define SDHCI_DATA_LVL_SHIFT 20
#define SDHCI_DATA_0_LVL_MASK 0x00100000
#define SDHCI_CMD_LVL 0x01000000

#define SDHCI_HOST_CONTROL 0x28
#define SDHCI_CTRL_LED 0x01
#define SDHCI_CTRL_4BITBUS 0x02
#define SDHCI_CTRL_HISPD 0x04
#define SDHCI_CTRL_DMA_MASK 0x18
#define SDHCI_CTRL_SDMA 0x00
#define SDHCI_CTRL_ADMA1 0x08
#define SDHCI_CTRL_ADMA32 0x10
#define SDHCI_CTRL_ADMA64 0x18
#define SDHCI_CTRL_ADMA3 0x18
#define SDHCI_CTRL_8BITBUS 0x20
#define SDHCI_CTRL_CDTEST_INS 0x40
#define SDHCI_CTRL_CDTEST_EN 0x80

#define SDHCI_POWER_CONTROL 0x29
#define SDHCI_POWER_ON 0x01
#define SDHCI_POWER_180 0x0A
#define SDHCI_POWER_300 0x0C
#define SDHCI_POWER_330 0x0E

#define SDHCI_BLOCK_GAP_CONTROL 0x2A

#define SDHCI_WAKE_UP_CONTROL 0x2B
#define SDHCI_WAKE_ON_INT 0x01
#define SDHCI_WAKE_ON_INSERT 0x02
#define SDHCI_WAKE_ON_REMOVE 0x04

#define SDHCI_CLOCK_CONTROL 0x2C
#define SDHCI_DIVIDER_SHIFT 8
#define SDHCI_DIVIDER_HI_SHIFT 6
#define SDHCI_DIV_MASK 0xFF
#define SDHCI_DIV_MASK_LEN 8
#define SDHCI_DIV_HI_MASK 0x300
#define SDHCI_PROG_CLOCK_MODE 0x0020
#define SDHCI_CLOCK_CARD_EN 0x0004
#define SDHCI_CLOCK_PLL_EN 0x0008
#define SDHCI_CLOCK_INT_STABLE 0x0002
#define SDHCI_CLOCK_INT_EN 0x0001

#define SDHCI_TIMEOUT_CONTROL 0x2E

#define SDHCI_SOFTWARE_RESET 0x2F
#define SDHCI_RESET_ALL 0x01
#define SDHCI_RESET_CMD 0x02
#define SDHCI_RESET_DATA 0x04

#define SDHCI_INT_STATUS 0x30
#define SDHCI_INT_ENABLE 0x34
#define SDHCI_SIGNAL_ENABLE 0x38
#define SDHCI_INT_RESPONSE 0x00000001
#define SDHCI_INT_DATA_END 0x00000002
#define SDHCI_INT_BLK_GAP 0x00000004
#define SDHCI_INT_DMA_END 0x00000008
#define SDHCI_INT_SPACE_AVAIL 0x00000010
#define SDHCI_INT_DATA_AVAIL 0x00000020
#define SDHCI_INT_CARD_INSERT 0x00000040
#define SDHCI_INT_CARD_REMOVE 0x00000080
#define SDHCI_INT_CARD_INT 0x00000100
#define SDHCI_INT_RETUNE 0x00001000
#define SDHCI_INT_CQE 0x00004000
#define SDHCI_INT_ERROR 0x00008000
#define SDHCI_INT_TIMEOUT 0x00010000
#define SDHCI_INT_CRC 0x00020000
#define SDHCI_INT_END_BIT 0x00040000
#define SDHCI_INT_INDEX 0x00080000
#define SDHCI_INT_DATA_TIMEOUT 0x00100000
#define SDHCI_INT_DATA_CRC 0x00200000
#define SDHCI_INT_DATA_END_BIT 0x00400000
#define SDHCI_INT_BUS_POWER 0x00800000
#define SDHCI_INT_AUTO_CMD_ERR 0x01000000
#define SDHCI_INT_ADMA_ERROR 0x02000000

#define SDHCI_INT_NORMAL_MASK 0x00007FFF
#define SDHCI_INT_ERROR_MASK 0xFFFF8000

#define SDHCI_INT_CMD_MASK (SDHCI_INT_RESPONSE | SDHCI_INT_TIMEOUT | SDHCI_INT_CRC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX | SDHCI_INT_AUTO_CMD_ERR)
#define SDHCI_INT_DATA_MASK (SDHCI_INT_DATA_END | SDHCI_INT_DMA_END | SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_END_BIT | SDHCI_INT_ADMA_ERROR | SDHCI_INT_BLK_GAP)
#define SDHCI_INT_ALL_MASK ((unsigned int)-1)

#define SDHCI_CQE_INT_ERR_MASK ( \
    SDHCI_INT_ADMA_ERROR | SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT | SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC | SDHCI_INT_TIMEOUT)

#define SDHCI_CQE_INT_MASK (SDHCI_CQE_INT_ERR_MASK | SDHCI_INT_CQE)

#define SDHCI_AUTO_CMD_STATUS 0x3C
#define SDHCI_AUTO_CMD_TIMEOUT 0x00000002
#define SDHCI_AUTO_CMD_CRC 0x00000004
#define SDHCI_AUTO_CMD_END_BIT 0x00000008
#define SDHCI_AUTO_CMD_INDEX 0x00000010

#define SDHCI_HOST_CONTROL2 0x3E
#define SDHCI_CTRL_UHS_MASK 0x0007
#define SDHCI_CTRL_UHS_SDR12 0x0000
#define SDHCI_CTRL_UHS_SDR25 0x0001
#define SDHCI_CTRL_UHS_SDR50 0x0002
#define SDHCI_CTRL_UHS_SDR104 0x0003
#define SDHCI_CTRL_UHS_DDR50 0x0004
#define SDHCI_CTRL_HS400 0x0005 /* Non-standard */
#define SDHCI_CTRL_VDD_180 0x0008
#define SDHCI_CTRL_DRV_TYPE_MASK 0x0030
#define SDHCI_CTRL_DRV_TYPE_B 0x0000
#define SDHCI_CTRL_DRV_TYPE_A 0x0010
#define SDHCI_CTRL_DRV_TYPE_C 0x0020
#define SDHCI_CTRL_DRV_TYPE_D 0x0030
#define SDHCI_CTRL_EXEC_TUNING 0x0040
#define SDHCI_CTRL_TUNED_CLK 0x0080
#define SDHCI_CMD23_ENABLE 0x0800
#define SDHCI_CTRL_V4_MODE 0x1000
#define SDHCI_CTRL_64BIT_ADDR 0x2000
#define SDHCI_CTRL_PRESET_VAL_ENABLE 0x8000

#define SDHCI_CAPABILITIES 0x40
#define SDHCI_TIMEOUT_CLK_MASK GENMASK(5, 0)
#define SDHCI_TIMEOUT_CLK_UNIT 0x00000080
#define SDHCI_CLOCK_BASE_MASK GENMASK(13, 8)
#define SDHCI_CLOCK_V3_BASE_MASK GENMASK(15, 8)
#define SDHCI_MAX_BLOCK_MASK 0x00030000
#define SDHCI_MAX_BLOCK_SHIFT 16
#define SDHCI_CAN_DO_8BIT 0x00040000
#define SDHCI_CAN_DO_ADMA2 0x00080000
#define SDHCI_CAN_DO_ADMA1 0x00100000
#define SDHCI_CAN_DO_HISPD 0x00200000
#define SDHCI_CAN_DO_SDMA 0x00400000
#define SDHCI_CAN_DO_SUSPEND 0x00800000
#define SDHCI_CAN_VDD_330 0x01000000
#define SDHCI_CAN_VDD_300 0x02000000
#define SDHCI_CAN_VDD_180 0x04000000
#define SDHCI_CAN_64BIT_V4 0x08000000
#define SDHCI_CAN_64BIT 0x10000000

#define SDHCI_CAPABILITIES_1 0x44
#define SDHCI_SUPPORT_SDR50 0x00000001
#define SDHCI_SUPPORT_SDR104 0x00000002
#define SDHCI_SUPPORT_DDR50 0x00000004
#define SDHCI_DRIVER_TYPE_A 0x00000010
#define SDHCI_DRIVER_TYPE_C 0x00000020
#define SDHCI_DRIVER_TYPE_D 0x00000040
#define SDHCI_RETUNING_TIMER_COUNT_MASK GENMASK(11, 8)
#define SDHCI_USE_SDR50_TUNING 0x00002000
#define SDHCI_RETUNING_MODE_MASK GENMASK(15, 14)
#define SDHCI_CLOCK_MUL_MASK GENMASK(23, 16)
#define SDHCI_CAN_DO_ADMA3 0x08000000
#define SDHCI_SUPPORT_HS400 0x80000000 /* Non-standard */

#define SDHCI_MAX_CURRENT 0x48
#define SDHCI_MAX_CURRENT_LIMIT GENMASK(7, 0)
#define SDHCI_MAX_CURRENT_330_MASK GENMASK(7, 0)
#define SDHCI_MAX_CURRENT_300_MASK GENMASK(15, 8)
#define SDHCI_MAX_CURRENT_180_MASK GENMASK(23, 16)
#define SDHCI_MAX_CURRENT_MULTIPLIER 4

/* 4C-4F reserved for more max current */

#define SDHCI_SET_ACMD12_ERROR 0x50
#define SDHCI_SET_INT_ERROR 0x52

#define SDHCI_ADMA_ERROR 0x54

/* 55-57 reserved */

#define SDHCI_ADMA_ADDRESS 0x58
#define SDHCI_ADMA_ADDRESS_HI 0x5C

/* 60-FB reserved */

#define SDHCI_PRESET_FOR_HIGH_SPEED 0x64
#define SDHCI_PRESET_FOR_SDR12 0x66
#define SDHCI_PRESET_FOR_SDR25 0x68
#define SDHCI_PRESET_FOR_SDR50 0x6A
#define SDHCI_PRESET_FOR_SDR104 0x6C
#define SDHCI_PRESET_FOR_DDR50 0x6E
#define SDHCI_PRESET_FOR_HS400 0x74 /* Non-standard */
#define SDHCI_PRESET_DRV_MASK GENMASK(15, 14)
#define SDHCI_PRESET_CLKGEN_SEL BIT(10)
#define SDHCI_PRESET_SDCLK_FREQ_MASK GENMASK(9, 0)

#define SDHCI_SLOT_INT_STATUS 0xFC

#define SDHCI_HOST_VERSION 0xFE
#define SDHCI_VENDOR_VER_MASK 0xFF00
#define SDHCI_VENDOR_VER_SHIFT 8
#define SDHCI_SPEC_VER_MASK 0x00FF
#define SDHCI_SPEC_VER_SHIFT 0
#define SDHCI_SPEC_100 0
#define SDHCI_SPEC_200 1
#define SDHCI_SPEC_300 2
#define SDHCI_SPEC_400 3
#define SDHCI_SPEC_410 4
#define SDHCI_SPEC_420 5

/*
 * End of controller registers.
 */
#define SDHCI_MAX_DIV_SPEC_300	2046
/*! @brief Transfer flag mask */
enum sdhci_transfer_mode
{
    sdhci_enable_dma_flag = SDHCI_TRNS_DMA, /*!< Enable DMA */

    sdhci_enable_block_count_flag = SDHCI_TRNS_BLK_CNT_EN,      /*!< Enable block count */
    sdhci_enable_auto_command12_flag = SDHCI_TRNS_AUTO_CMD12, /*!< Enable auto CMD12 */
    sdhci_data_read_flag = SDHCI_TRNS_READ,            /*!< Enable data read */
    sdhci_multiple_block_flag = SDHCI_TRNS_MULTI,       /*!< Multiple block data read/write */
    sdhci_enable_auto_command23_flag = SDHCI_TRNS_AUTO_CMD23, /*!< Enable auto CMD23 */
    sdhci_enable_auto_commamd_sel_flag = SDHCI_TRNS_AUTO_SEL, /* Enable auto command sel*/
};

enum sdhci_command_flag
{
    sdhci_cmd_resp_nono = SDHCI_CMD_RESP_NONE,
    sdhci_cmd_resp_long = SDHCI_CMD_RESP_LONG,
    sdhci_cmd_resp_short = SDHCI_CMD_RESP_SHORT,
    sdhci_cmd_resp_short_busy = SDHCI_CMD_RESP_SHORT_BUSY,

    sdhci_enable_cmd_crc_flag = SDHCI_CMD_CRC,
    sdhci_enable_cmd_index_chk_flag = SDHCI_CMD_INDEX,
    sdhci_enable_cmd_data_present_flag = SDHCI_CMD_DATA,

    sdhci_enable_command_type_normal = 0x00,
    sdhci_enable_command_type_suspend = 0x40,
    sdhci_enable_command_type_resume = 0x80,
    sdhci_enable_command_type_abort = 0xc0,
};

/*! @brief Present status flag mask */
enum sdhci_present_status_flag
{
    sdhci_command_inhibit_flag = 0x1,     /*!< Command inhibit */
    sdhci_data_inhibit_flag = 0x2,       /*!< Data inhibit */
    sdhci_data_line_active_flag = 0x4,      /*!< Data line active */
    sdhci_write_transfer_active_flag = 0x100, /*!< Write transfer active */
    sdhci_read_transfer_active_flag = 0x200,  /*!< Read transfer active */
    sdhci_buffer_write_enable_flag = 0x400,  /*!< Buffer write enable */
    sdhci_buffer_read_enable_flag = 0x800,   /*!< Buffer read enable */

    sdhci_card_insert_flag = 0x10000,    /*!< Card inserted */
    sdhci_sd_clock_stable_flag = 0x20000,     /*!< SD bus clock stable */
    sdhci_card_detect_pin_level_flag = 0x40000, /*!< card detect pin level */
    sdhci_write_protect_switch_pin_level_flag = 0x80000, /*<write protect switch pin level>*/

    sdhci_data0_line_level_flag = (1U << 20),        /*!< Data0 line signal level */
    sdhci_data1_line_level_flag = (1U << (20 + 1U)), /*!< Data1 line signal level */
    sdhci_data2_line_level_flag = (1U << (20 + 2U)), /*!< Data2 line signal level */
    sdhci_data3_line_level_flag = (1U << (20 + 3U)), /*!< Data3 line signal level */
    sdhci_data4_line_level_flag = (1U << (4 + 0U)), /*!< Data4 line signal level */
    sdhci_data5_line_level_flag = (1U << (4 + 1U)), /*!< Data5 line signal level */
    sdhci_data6_line_level_flag = (1U << (4 + 2U)), /*!< Data6 line signal level */
    sdhci_data7_line_level_flag = (1U << (4 + 3U)), /*!< Data7 line signal level */

    sdhci_command_line_signal_level_flag =0x1000000,
    sdhci_host_reg_voltage_stable_flag = 0x2000000,
    sdhci_command_not_issued_by_error_flag = 0x8000000,
    sdhci_sub_command_status_flag = 0x10000000,
    sdhci_in_dormant_status_flag = 0x20000000,
    sdhci_lane_synchronization_flag = 0x40000000,
    sdhci_uhs_ii_interface_detection_flag = 0x80000000,
};

/*! @brief Interrupt status flag mask */
enum sdhci_interrupt_status_flag
{
    sdhci_command_complete_flag = 0x1,   /*!< Command complete */
    sdhci_data_complete_flag = 0x2,      /*!< Data complete */
    sdhci_block_gap_event_flag = 0x4,    /*!< Block gap event */
    sdhci_dma_complete_flag = 0x8,     /*!< DMA interrupt */
    sdhci_buffer_write_ready_flag = 0x10, /*!< Buffer write ready */
    sdhci_buffer_read_ready_flag = 0x20,  /*!< Buffer read ready */
    sdhci_card_insertion_flag = 0x40,   /*!< Card inserted */
    sdhci_card_removal_flag = 0x80,      /*!< Card removed */
    sdhci_card_interrupt_flag = 0x100,   /*!< Card interrupt */

    sdhci_command_timeout_flag = 0x10000,      /*!< Command timeout error */
    sdhci_command_crc_error_flag = 0x20000,      /*!< Command CRC error */
    sdhci_command_end_bit_error_flag = 0x40000,  /*!< Command end bit error */
    sdhci_command_index_error_flag = 0x80000,    /*!< Command index error */
    sdhci_data_timeout_flag = 0x100000,         /*!< Data timeout error */
    sdhci_data_crc_error_flag = 0x200000,         /*!< Data CRC error */
    sdhci_data_end_bit_error_flag = 0x400000,     /*!< Data end bit error */
    sdhci_auto_command_error_flag = 0x1000000, /*!< Auto CMD error */
    sdhci_dma_error_flag = 0x2000000,            /*!< ADMA error */
    sdhci_tuning_error_flag = 0x4000000,        /* tuning err*/
    sdhci_response_err_flag = 0x8000000,        /*resp error*/

    sdhci_command_error_flag = (sdhci_command_timeout_flag | sdhci_command_crc_error_flag | sdhci_command_end_bit_error_flag |
                               sdhci_command_index_error_flag), /*!< Command error */
    sdhci_data_error_flag = (sdhci_data_timeout_flag | sdhci_data_crc_error_flag | sdhci_data_end_bit_error_flag |
                            sdhci_auto_command_error_flag),                                    /*!< Data error */
    sdhci_error_flag = (sdhci_command_error_flag | sdhci_data_error_flag | sdhci_dma_error_flag), /*!< All error */
    sdhci_data_flag = (sdhci_data_complete_flag | sdhci_dma_complete_flag | sdhci_buffer_write_ready_flag |
                       sdhci_buffer_read_ready_flag | sdhci_data_error_flag | sdhci_dma_error_flag), /*!< Data interrupts */
    sdhci_command_flag = (sdhci_command_error_flag | sdhci_command_complete_flag), /*!< Command interrupts */
    sdhci_card_detect_flag = (sdhci_card_insertion_flag | sdhci_card_removal_flag), /*!< Card detection interrupts */
    sdhci_sdr104_tuning_flag = (sdhci_tuning_error_flag),

    sdhci_all_interrupt_flags = (sdhci_block_gap_event_flag | sdhci_card_detect_flag | sdhci_command_flag |
                                sdhci_data_flag | sdhci_error_flag | sdhci_sdr104_tuning_flag), /*!< All flags mask */
};

/*! @brief USDHC status */
enum sdhci_status
{
    sdhci_status_busy_transferring = 65,            /*!< Transfer is on-going */
    sdhci_status_prepare_adma_descriptor_failed = 66, /*!< Set DMA descriptor failed */
    sdhci_status_send_command_failed = 67,           /*!< Send command failed */
    sdhci_status_transfer_data_failed = 68,          /*!< Transfer data failed */
    sdhci_status_dma_data_addr_no_align = 69,         /*!< data address not align */
    sdhci_status_retuning_request = 70,             /*!< re-tuning request */
    sdhci_status_tuning_error = 71,                 /*!< tuning error */

};

/* ADMA2 data alignment */
#define SDHCI_ADMA2_ALIGN	4
#define SDHCI_ADMA2_MASK	(SDHCI_ADMA2_ALIGN - 1)

/*! @brief The bit shift for LENGTH field in ADMA2's descriptor */
#define SDHCI_ADMA2_DESCRIPTOR_LENGTH_SHIFT (16U)
/*! @brief The bit mask for LENGTH field in ADMA2's descriptor */
#define SDHCI_ADMA2_DESCRIPTOR_LENGTH_MASK (0xFFFFU)
/*! @brief The maximum value of LENGTH field in ADMA2's descriptor */
#define SDHCI_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY (SDHCI_ADMA2_DESCRIPTOR_LENGTH_MASK - 3U)

#define SDHCI_DESC_VALID (0x1U << 0)
#define SDHCI_DESC_END (0x1U << 1)
#define SDHCI_DESC_INT (0x1U << 2)
#define SDHCI_DESC_TRAN (0x2U << 4)
struct sdhci_64bit_adma2_descriptor
{
    uint32_t attribute;
    uint32_t address;
};

/*! @brief The command type */
enum sdhci_card_command_type
{
    card_command_type_normal = 0U,  /*!< Normal command */
    card_command_type_suspend = 1U, /*!< Suspend command */
    card_command_type_resume = 2U,  /*!< Resume command */
    card_command_type_abort = 3U,   /*!< Abort command */
};

/*!
 * @brief The command response type.
 *
 * Define the command response type from card to host controller.
 */
enum sdhci_card_response_type
{
    card_response_type_none = 0U, /*!< Response type: none */
    card_response_type_r1 = 1U,   /*!< Response type: R1 */
    card_response_type_r1b = 2U,  /*!< Response type: R1b */
    card_response_type_r2 = 3U,   /*!< Response type: R2 */
    card_response_type_r3 = 4U,   /*!< Response type: R3 */
    card_response_type_r4 = 5U,   /*!< Response type: R4 */
    card_response_type_r5 = 6U,   /*!< Response type: R5 */
    card_response_type_r5b = 7U,  /*!< Response type: R5b */
    card_response_type_r6 = 8U,   /*!< Response type: R6 */
    card_response_type_r7 = 9U,   /*!< Response type: R7 */
};

/*!
 * @brief Card data descriptor
 *
 * Defines a structure to contain data-related attribute. 'enableIgnoreError' is used for the case that upper card
 * driver
 * want to ignore the error event to read/write all the data not to stop read/write immediately when error event
 * happen for example bus testing procedure for MMC card.
 */
struct sdhci_data
{
    rt_bool_t enableAutoCommand12; /*!< Enable auto CMD12 */
    rt_bool_t enableAutoCommand23; /*!< Enable auto CMD23 */
    rt_bool_t enableIgnoreError;   /*!< Enable to ignore error event to read/write all the data */
    rt_bool_t executeTuning;       /*!< execute tuning flag */

    size_t blockSize;       /*!< Block size */
    uint32_t blockCount;    /*!< Block count */
    uint32_t *rxData;       /*!< Buffer to save data read */
    const uint32_t *txData; /*!< Data buffer to write */
};

/*!
 * @brief Card command descriptor
 *
 * Define card command-related attribute.
 */
struct sdhci_command
{
    uint32_t index;                          /*!< Command index */
    uint32_t argument;                       /*!< Command argument */
    enum sdhci_card_command_type type;          /*!< Command type */
    enum sdhci_card_response_type responseType; /*!< Command response type */
    uint32_t response[4U];                   /*!< Response for this command */
    uint32_t responseErrorFlags;             /*!< response error flag, the flag which need to check
                                                 the command reponse*/
    uint16_t flags;                          /*!< Cmd flags */
    uint16_t flags2;                           /*xfer mode*/
};

struct sdhci_host
{
    struct rt_mmcsd_host *host;
    void *mapbase;
    struct sdhci_data *sdhci_data;
    struct sdhci_command *sdhci_command;
    void *usdhc_adma2_table;
    struct rt_event event;
    uint16_t error_code;
    uint32_t max_clk;
    uint8_t index;
    uint8_t is_emmc_card;
    uint8_t io_fixed_1v8;
    uint8_t have_phy;
    uint8_t mshc_ctrl_r;
    uint32_t rx_delay_line;
    uint32_t tx_delay_line;
};

#endif /*__DRV_SDHCI__*/
