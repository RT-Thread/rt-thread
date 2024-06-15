/*  */
/* Created by hpm15 on 3/11/21. */
/*  */

#ifndef SFDP_DEF_H
#define SFDP_DEF_H

#include <stdint.h>
#include "hpm_common.h"

/* ! @brief Commands for probing the FLASH device */
#define SERIAL_FLASH_READ_SFDP (0x5AU)
#define SERIAL_FLASH_READ_MANUFACTURE_ID (0x9FU)

/* !@brief SFDP related definitions */
#define SFDP_SIGNATURE (0x50444653UL) /* ASCII: SFDP */
#define SFDP_VERSION_MAJOR_1_0 (1U)
#define SFDP_VERSION_MINOR_0 (0U) /* JESD216 */
#define SFDP_VERSION_MINOR_A (5U) /* JESD216A */
#define SFDP_VERSION_MINOR_B (6U) /* JESD216B */
#define SFDP_VERSION_MINOR_C (7U) /* JESD216C */
#define SFDP_VERSION_MINOR_D (8U) /* JESD216D */
#define SFDP_BASIC_PROTOCOL_TABLE_SIZE_REV0 (36U)
#define SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVA (64U)
#define SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVB SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVA
#define SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVC (80U)
#define SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVD SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVC

typedef union _sfdp_header {
    uint32_t words[2];
    struct {
        uint32_t signature;
        uint8_t minor_rev;
        uint8_t major_rev;
        uint8_t param_hdr_num;
        uint8_t sfdp_access_protocol; /* Defined in JESD216C, reserved for older version */
    };

} sfdp_header_t;

/* !@brief SFDP parameter Type ID definitions */
#define PARAMETER_ID_BASIC_SPIPROTOCOL (0xFF00U)
/* New Table added in JESD216B */
#define PARAMETER_ID_SECTOR_MAP (0xFF81U)
#define PARAMETER_ID_4BYTEADDRESS_INSTRUCTION_TABLE (0xFF84U)
/* New Table added in JESD216C */
#define PARAMETER_ID_XSPIPROFILE1_0 (0xFF05U)
#define PARAMETER_ID_XSPIOROFILE2_0 (0xFF06U)
#define PARAMETER_ID_STACTRLCFGREGMAP (0xFF87U)
#define PARAMETER_ID_OPIENABLESEQ (0xFF09U)
#define PARAMETER_ID_CMDSEQ_CHANGE_TO_OCTAL_DDR (0xFF0AU)

#define NORFLASH_ADDRESSBITS_3B (0U)
#define NORFLASH_ADDRESSBITS_3B_4B (1U)
#define NORFLASH_ADDRESSBITS_4B (2U)

#define COMMAND_EXTENSION_SAME_AS_COMMAND (0U)
#define COMMAND_EXTENSION_INVERSE_OF_COMMAND (1U)
#define COMMAND_AND_COMMANDEXTENSION_16BITWORD (2U)

/* !@brief Supported methods to enter 8-8-8 mode from 1-1-1 mode, More details please refer to JESD216C/D */
#define ENTER_OCTAL_MODE_OPTION0 HPM_BITSMASK(1U, 1)
#define ENTER_OCTAL_MODE_OPTION1 HPM_BITSMASK(1U, 2)

/* !@brief SFDP Parameter Header, see JESD216D doc for more details */
typedef union _sfdp_parameter_header {
    uint32_t words[2];
    struct {
        uint8_t parameter_id_lsb;
        uint8_t minor_rev;
        uint8_t major_rev;
        uint8_t table_length_in_32bit;
        uint8_t parameter_table_pointer[3];
        uint8_t parameter_id_msb;
    };

} sfdp_parameter_header_t;

/* !@brief Basic Flash Parameter Table, see JESD216D doc for more details */
typedef union _jedec_flash_param_table {
    uint32_t words[20];
    struct {
        struct {
            uint32_t erase_size : 2;
            uint32_t write_granularity : 1;
            uint32_t reserved0 : 2;
            uint32_t unused0 : 3;
            uint32_t erase4k_inst : 8;
            uint32_t support_1_1_2_fast_read : 1;
            uint32_t address_bits : 2;
            uint32_t support_ddr_clocking : 1;
            uint32_t support_1_2_2_fast_read : 1;
            uint32_t supports_1_4_4_fast_read : 1;
            uint32_t support_1_1_4_fast_read : 1;
            uint32_t unused1 : 9;
        } misc;                 /* 1st word */
        uint32_t flash_density; /* 2nd word */
        struct {
            uint32_t dummy_clocks_1_4_4_read : 5;
            uint32_t mode_clocks_1_4_4_read : 3;
            uint32_t inst_1_4_4_read : 8;
            uint32_t dummy_clocks_1_1_4_read : 5;
            uint32_t mode_clocks_1_1_4_read : 3;
            uint32_t inst_1_1_4_read : 8;
        } read_1_4_info; /* 3rd word */
        struct {
            uint32_t dummy_clocks_1_1_2_read : 5;
            uint32_t mode_clocks_1_1_2_read : 3;
            uint32_t inst_1_1_2_read : 8;
            uint32_t dummy_clocks_1_2_2_read : 5;
            uint32_t mode_clocks_1_2_2_read : 3;
            uint32_t inst_1_2_2_read : 8;
        } read_1_2_info; /* 4th word */

        struct {
            uint32_t support_2_2_2_fast_read : 1;
            uint32_t reserved0 : 3;
            uint32_t support_4_4_4_fast_read : 1;
            uint32_t reserved1 : 27;
        } read_22_44_check; /* 5th word */

        struct {
            uint32_t reserved0 : 16;
            uint32_t dummy_clocks_2_2_2_read : 5;
            uint32_t mode_clocks_2_2_2_read : 3;
            uint32_t inst_2_2_2_read : 8;
        } read_2_2_info; /* 6th word */
        struct {
            uint32_t reserved0 : 16;
            uint32_t dummy_clocks_4_4_4_read : 5;
            uint32_t mode_clocks_4_4_4_read : 3;
            uint32_t inst_4_4_4_read : 8;
        } read_4_4_info; /* 7th word */

        struct {
            uint8_t size;
            uint8_t inst;
        } erase_info[4]; /* 8th,9th word */

        uint32_t erase_timing; /* 10th word */
        struct {
            uint32_t reserved0 : 4;
            uint32_t page_size : 4;
            uint32_t reserved1 : 24;
        } chip_erase_progrm_info; /* 11th word */

        struct {
            uint32_t suspend_resume_spec;
            uint32_t suspend_resume_inst;
        } suspend_resume_info; /* 12th, 13th word */

        struct {
            uint32_t reserved0 : 2;
            uint32_t busy_status_polling : 6;
            uint32_t reserved1 : 24;
        } busy_status_info; /* 14th word */

        struct {
            uint32_t mode_4_4_4_disable_seq : 4;
            uint32_t mode_4_4_4_enable_seq : 5;
            uint32_t support_mode_0_4_4 : 1;
            uint32_t mode_0_4_4_exit_method : 6;
            uint32_t mode_0_4_4_entry_method : 4;
            uint32_t quad_enable_requirement : 3;
            uint32_t hold_reset_disable : 1;
            uint32_t reserved0 : 8;
        } mode_4_4_info; /* 15th word */

        struct {
            uint32_t status_reg_write_enable : 7;
            uint32_t reserved0 : 1;
            uint32_t soft_reset_rescue_support : 6;
            uint32_t exit_4_byte_addressing : 10;
            uint32_t enter_4_byte_addrssing : 8;
        } mode_config_info; /* 16th word */

        struct {
            uint32_t dummy_clocks_1_8_8_read : 5;
            uint32_t mode_clocks_1_8_8_read : 3;
            uint32_t inst_1_8_8_read : 8;
            uint32_t dummy_clocks_1_1_8_read : 5;
            uint32_t mode_clocks_1_1_8_read : 3;
            uint32_t inst_1_1_8_read : 8;
        } read_1_8_info; /* 17th word */

        struct {
            uint32_t reserved : 18;
            uint32_t output_driver_strength : 5;
            uint32_t jedec_spi_protocol_reset : 1;
            uint32_t dqs_waveform_type_sdr : 2;
            uint32_t dqs_support_in_qpi_sdr : 1;
            uint32_t dqs_support_in_qpi_ddr : 1;
            uint32_t dqs_support_in_opi_str : 1;
            uint32_t cmd_and_extension_in_opi_ddr : 2;
            uint32_t byte_order_in_opi_ddr : 1;
        } xpi_misc_info; /* 18th word */

        struct {
            uint32_t opi_sdr_disable_seq : 4;
            uint32_t opi_sdr_enable_seq : 5;
            uint32_t support_mode_0_8_8 : 1;
            uint32_t mode_0_8_8_exit_method : 6;
            uint32_t mode_0_8_8_entry_method : 4;
            uint32_t octal_enable_requirement : 3;
            uint32_t reserved : 9;
        } mode_octal_info; /* 19th word */

        struct {
            uint32_t qpi_sdr_no_dqs : 4;
            uint32_t qpi_sdr_with_dqs : 4;
            uint32_t qpi_ddr_no_dqs : 4;
            uint32_t qpi_ddr_with_dqs : 4;
            uint32_t opi_sdr_no_dqs : 4;
            uint32_t opi_sdr_with_dqs : 4;
            uint32_t opi_ddr_no_dqs : 4;
            uint32_t opi_ddr_with_dqs : 4;
        } max_speed_info_xpi; /* 20th word */
    };

} jedec_flash_param_table_t;

/* !@brief 4Byte Addressing Instruction Table, see JESD216D doc for more details */
typedef union _jedec_4byte_addressing_inst_table {
    uint32_t words[2];
    struct {
        struct {
            uint32_t support_1_1_1_read : 1;
            uint32_t support_1_1_1_fast_read : 1;
            uint32_t support_1_1_2_fast_read : 1;
            uint32_t support_1_2_2_fast_read : 1;
            uint32_t support_1_1_4_fast_read : 1;
            uint32_t support_1_4_4_fast_read : 1;
            uint32_t support_1_1_1_page_program : 1;
            uint32_t support_1_1_4_page_program : 1;
            uint32_t support_1_4_4_page_program : 1;
            uint32_t support_erase_type1_size : 1;
            uint32_t support_erase_type2_size : 1;
            uint32_t support_erase_type3_size : 1;
            uint32_t support_erase_type4_size : 1;
            uint32_t support_1_1_1_dtr_read : 1;
            uint32_t support_1_2_2_dtr_read : 1;
            uint32_t support_1_4_4_dtr_read : 1;
            uint32_t support_volatile_sector_lock_read_cmd : 1;
            uint32_t support_volatile_sector_lock_write_cmd : 1;
            uint32_t support_nonvolatile_sector_lock_read_cmd : 1;
            uint32_t support_nonvolatile_sector_lock_write_cmd : 1;
            uint32_t reserved : 12;
        } cmd_4byte_support_info;

        struct {
            uint8_t erase_inst[4];
        } erase_inst_info;
    };
} jedec_4byte_addressing_inst_table_t;

typedef union _jedec_cmd_sequence_change_to_octal_mode {
    uint32_t words[8];

    struct {
        struct {
            uint32_t byte3_of_1st_command_seq : 8;
            uint32_t byte2_of_1st_command_seq : 8;
            uint32_t byte1_of_1st_command_seq : 8;
            uint32_t length_of_1st_command_seq : 8;
        } first_command_sequence_low; /* 1st command sequence */

        struct {
            uint32_t byte7_of_first_command_seq : 8;
            uint32_t byte6_of_first_command_seq : 8;
            uint32_t byte5_of_first_command_seq : 8;
            uint32_t byte4_of_first_command_seq : 8;
        } first_command_sequence_high; /* 1st command sequence */

        struct {
            uint32_t byte3_of_2nd_command_seq : 8;
            uint32_t byte2_of_2nd_command_seq : 8;
            uint32_t byte1_of_2nd_command_seq : 8;
            uint32_t length_of_2nd_command_seq : 8;
        } second_command_sequence_low; /* 2nd command sequence */

        struct {
            uint32_t byte7_of_2nd_command_seq : 8;
            uint32_t byte6_of_2nd_command_seq : 8;
            uint32_t byte5_of_2nd_command_seq : 8;
            uint32_t byte4_of_2md_command_seq : 8;
        } second_command_sequence_high; /* 2nd command sequence */

        struct {
            uint32_t byte3_of_3rd_command_seq : 8;
            uint32_t byte2_of_3rd_command_seq : 8;
            uint32_t byte1_of_3rd_command_seq : 8;
            uint32_t length_of_3rd_command_seq : 8;
        } third_command_sequence_low; /* 3rd command sequence */

        struct {
            uint32_t byte7_of_3rd_command_seq : 8;
            uint32_t byte6_of_3rd_command_seq : 8;
            uint32_t byte5_of_3rd_command_seq : 8;
            uint32_t byte4_of_3rd_command_seq : 8;
        } third_command_sequence_high; /* 3rd command sequence */

        struct {
            uint32_t byte3_of_4th_command_seq : 8;
            uint32_t byte2_of_4th_command_seq : 8;
            uint32_t byte1_of_4th_command_seq : 8;
            uint32_t length_of_4th_command_seq : 8;
        } fourth_command_sequence_low; /* 4th command sequence */

        struct {
            uint32_t byte7_of_4th_command_seq : 8;
            uint32_t byte6_of_4th_command_seq : 8;
            uint32_t byte5_of_4th_command_seq : 8;
            uint32_t byte4_of_4th_command_seq : 8;
        } fourth_command_sequence_high; /* 4th command sequence */
    };

} jedec_cmd_sequence_change_to_octal_mode_t;

typedef union _jedec_x_spi_profile1_0_table_t {
    uint32_t words[5];

    struct {
        struct {
            uint32_t fast_read_wrapped_cmd : 8;
            uint32_t fast_read_cmd : 8;
            uint32_t reserved : 16;
        } table1;

        struct {
            uint32_t write_nv_register_cmd : 8;
            uint32_t write_v_register_cmd : 8;
            uint32_t reserved : 16;
        } table2;

        uint32_t unused_tables[3];
    };

} jedec_x_spi_profile1_0_table_t;

typedef union _jedec_status_control_configuration_reg_map {
    uint32_t words[28];
    struct {
        uint32_t unused_table[2];
        struct {
            uint32_t dummy_cycles_1s_1s_1s : 4;
            uint32_t reserved0 : 2;
            uint32_t dummy_cycles_8d_8d_8d : 4;
            uint32_t dummy_cycles_8s_8s_8s : 4;
            uint32_t dummy_cycles_4s_4d_4d : 4;
            uint32_t dummy_cycles_4s_4s_4s : 4;
            uint32_t dummy_cycles_2s_2s_2s : 4;
            uint32_t dummy_cycles_1s_1s_1s_select : 2;
            uint32_t addr_bytes_address_status_register : 2;
            uint32_t unused0 : 2;
        };
        uint32_t unused_table1[25];
    };
} jedec_status_control_configuration_reg_map_t;

typedef struct _jdec_query_table {
    uint32_t standard_version; /* JESD216 version */
    uint32_t flash_param_tbl_size;
    jedec_flash_param_table_t flash_param_tbl;
    bool has_4b_addressing_inst_table;
    jedec_4byte_addressing_inst_table_t flash_4b_inst_tbl;
    bool has_otcal_ddr_mode_enable_sequence_table;
    jedec_cmd_sequence_change_to_octal_mode_t otcal_ddr_mode_enable_sequence; /* JESD216C/D */
    jedec_x_spi_profile1_0_table_t profile1_0_table;
    bool has_spi_profile1_0_table;
    jedec_status_control_configuration_reg_map_t sccr_map;
    bool has_sccr_map;
} jedec_info_table_t;


/* !@brief Typical Serial NOR commands supported by most Serial NOR devices */
#define SERIALNOR_CMD_BASICREAD_3B (0x03U)
#define SERIALNOR_CMD_BASICREAD_4B (0x13U)
#define SERIALNOR_CMD_PAGEPROGRAM_1_1_1_3B (0x02U)
#define SERIALNOR_CMD_PAGEPROGRAM_1_1_1_4B (0x12U)
#define SERIALNOR_CMD_PAGEPROGRAM_1_4_4_4B (0x3EU)
#define SERIALNOR_CMD_PAGEPROGRAM_1_1_4_4B (0x34U)
#define SERIALNOR_CMD_READ_SDR_1_4_4_3B (0xEBU)
#define SERIALNOR_CMD_READ_DDR_1_4_4_3B (0xEDU)
#define SERIALNOR_CMD_READ_SDR_1_4_4_4B (0xECU)
#define SERIALNOR_CMD_READ_SDR_1_1_4_4B (0x6CU)
#define SERIALNOR_CMD_READ_DDR_1_4_4_4B (0xEEU)
#define SERIALNOR_CMD_CHIPERASE (0x60U)
#define SERIALNOR_CMD_WRITEENABLE (0x06U)
#define SERIALNOR_CMD_WRITE_STATUS_REG1 (0x01U)
#define SERIALNOR_CMD_READ_STATUS_REG1 (0x05U)
#define SERIALNOR_CMD_WRITE_STATUS_REG2 (0x3EU)
#define SERIALNOR_CMD_READ_STATUS_REG2 (0x3FU)
#define SERIALNOR_CMD_READ_FLAGREG (0x70U)
#define SERIALNOR_CMD_READID (0x9FU)
#define SERIALNOR_CMD_READ_DDR_4B (0x0CU)
#define SERIALNOR_CMD_READ_DDR_3B (0x0BU)
#define SERIALNOR_CMD_SE4K_3B (0x20U)
#define SERIALNOR_CMD_SE4K_4B (0x21U)
#define SERIALNOR_CMD_SE64K_3B (0xD8U)
#define SERIALNOR_CMD_SE64K_4B (0xDCU)

#endif
