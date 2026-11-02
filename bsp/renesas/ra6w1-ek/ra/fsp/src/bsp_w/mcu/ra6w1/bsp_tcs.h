/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_TCS_RA6W1_H
#define BSP_TCS_RA6W1_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define TCS_ATTRIBUTE_SIZE               20
#define TCS_DATA_SIZE                    200 /**< max number of entries in words (4 bytes). */
#define GID_EMPTY                        0x1FF

/*
 * Reset values of trimmed registers
 */
#define DEFAULT_CHARGER_TEST_CTRL_REG    0x00001F28

/*
 * OTP Memory
 */
#define MEMORY_OTP_BASE                  0x400F2000UL
#define MEMORY_OTP_END                   0x400F2800UL

/*
 * OQSPI AHB-C(ode) bus (cached). Accesses through this bus
 * are restricted according to CACHE_FLASH_REG.
 */
#define MEMORY_OQSPIC_BASE               (0x0A000000) // before (0x19000000UL)
#define MEMORY_OQSPIC_END                (0x0DFFFFFF) // before (0x1D000000UL)

#define MEMORY_OQSPIC_SIZE               (MEMORY_OQSPIC_END - MEMORY_OQSPIC_BASE)

/*
 * OQSPI AHB-S(ystem) bus (Not cached). Accesses through this bus
 * are not affected by CACHE_FLASH_REG.
 */
#define MEMORY_OQSPIC_S_BASE             (0x2A000000) // before (0x3A000000UL)
#define MEMORY_OQSPIC_S_END              (0x2DFFFFFF) // before (0x3E000000UL)

/*
 * QSPI AHB-C(ode) bus (cached). Accesses through this bus
 * are restricted according to CACHE_FLASH_REG.
 */
#define  MEMORY_QSPIF_BASE               (0x24000000UL)
#define  MEMORY_QSPIF_END                (MEMORY_QSPIF_BASE + 0x4000000UL)

/*
 * QSPI Data
 */
#define MEMORY_QSPID_BASE                (0x24000000UL)
#define MEMORY_QSPID_END                 (0x28000000UL)
#define MEMORY_QSPID_SIZE                (MEMORY_QSPID_END - MEMORY_QSPID_BASE)

/*
 * DCACHE controller
 */
#define MEMORY_DCACHE_BASE               (0x21014000UL)
#define MEMORY_DCACHE_SIZE               (0x2000UL)
#define MEMORY_DCACHE_END                (MEMORY_DCACHE_BASE + MEMORY_DCACHE_SIZE)

#define TCS_INFO                         1

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**
 * @enum  bsp_tcs_type_t
 * @brief custom TCS value type.
 */
typedef enum
{
    BSP_TCS_TYPE_TRIM_VAL     = 0,     /**< trimmed value */
    BSP_TCS_TYPE_REG_PAIR     = 1,     /**< register pair value */
    BSP_TCS_TYPE_HPI_REG_PAIR = 2,
    BSP_TCS_TYPE_RESERVED     = 3,
} bsp_tcs_type_t;

/**
 * @enum  bsp_tcs_domain_t
 * @brief power domain of each TCS group.
 */
typedef enum
{
    BSP_TCS_DOMAIN_PD_SYS = 0,         /**< System power domain */
    BSP_TCS_DOMAIN_PD_COM,             /**< Communication power domain */
    BSP_TCS_DOMAIN_PD_MEM,             /**< Memory power domain */
    BSP_TCS_DOMAIN_PD_TMR,             /**< Timers power domain */
    BSP_TCS_DOMAIN_PD_PER,             /**< Peripherals power domain */
    BSP_TCS_DOMAIN_PD_RAD,             /**< Radio power domain */
    BSP_TCS_DOMAIN_PD_SYNTH,           /**< Synth power domain */
    BSP_TCS_DOMAIN_NA                  /**< No power domain */
} bsp_tcs_domain_t;

/**
 * @enum  bsp_tcs_gid_t
 * @brief the configured group ids.
 */
typedef enum
{
    BSP_TCS_GROUP_RESERVED = 0x0,
    BSP_TCS_GROUP_COMMON   = 0x1,
    BSP_TCS_GROUP_SKIP     = 0x2,

    /* Power Domains Section */
    BSP_TCS_GROUP_PD_SYS              = 0x20,
    BSP_TCS_GROUP_MAC_ADDR            = 0x21,
    BSP_TCS_GROUP_PD_ADC              = 0x22,
    BSP_TCS_GROUP_PD_WIFI_TRIM_RF_HPI = 0x81,
    BSP_TCS_GROUP_PD_WIFI_TRIM_TX_HPI = 0x82,
    BSP_TCS_GROUP_PD_WIFI_TRIM_DCORE  = 0x80,
    BSP_TCS_GROUP_PD_WIFI_TRIM_LUT    = 0x83,
    BSP_TCS_GROUP_PD_WIFI_TRIM_TXIQ   = 0x84,
    BSP_TCS_GROUP_PD_WIFI_TRIM_XTAL   = 0x90,

    /* System Section */
    BSP_TCS_GROUP_BD_ADDR = 0x20,             /**< BD_ADDR group id */

    /* Production Test Section */
    BSP_TCS_GROUP_CHIP_ID             = 0xC0, /**< CHIP_ID group id */
    BSP_TCS_GROUP_PROD_INFO           = 0xC1, /**< PROD_INFO group id */
    BSP_TCS_GROUP_PROD_WAFER          = 0xC2, /**< PROD_WAFER group id */
    BSP_TCS_GROUP_TESTPROGRAM_VERSION = 0xC3, /**< TESTPROGRAM_VERSION  group id */
    BSP_TCS_GROUP_PROD_SW_IP          = 0xC4, /**< PROD_SW_IP group id */

    BSP_TCS_GROUP_MAX = 0xE0                  /**< Maximum supported group id */
} bsp_tcs_gid_t;

/**
 * @struct bsp_tcs_source_t
 * @brief Parsing order for the configuration script
 */
typedef enum
{
    BSP_TCS_OTP = 0,                   /* CS in OTP */
    BSP_TCS_OQSPI,                     /* CS in Flash */
    BSP_TCS_QSPI,                      /* CS in QSPI Flash */
    BSP_TCS_NVMS,                      /* CS in NVMS */
} bsp_tcs_source_t;

typedef enum e_check_option
{
    CHECK_OPTION_FORCE       = 0,      ///< Force write
    CHECK_OPTION_EMPTY       = 1,      ///< Write if only empty item.
    CHECK_OPTION_DIFFERENT   = 2,      ///< Write if only different item.
    CHECK_OPTION_SKIP_EXISTS = 3,      ///< Skip if already written
} check_option_t;

/**
 * @struct bsp_tcs_attr_t
 * @brief attributes per custom value group id
 */
typedef struct
{
    uint32_t value_gid    : 8;         /* bsp_tcs_gid_t */
    uint32_t value_type   : 2;         /* bsp_tcs_type_t - < TCS entry type */
    uint32_t value_domain : 4;         /* bsp_tcs_domain_t */
    uint32_t is_retained  : 2;
    uint32_t start        : 8;         /* < TCS entry start position  */
    uint32_t size         : 8;         /* < TCS entry type size in words */
} bsp_tcs_attr_t;

/**
 * @struct bsp_tcs_shared_t
 * @brief This structure is used to hold the TCS shared-memory data in specific order
 * to prevent compiler optimization when building for both (SYSCPU and CMAC) CPUs.
 */
typedef struct
{
    uint32_t       * tcs_data;               /*!< The CS data as read by the TCS parser */
    uint8_t          tcs_data_size;          /*!< Number of words in the tcs_data */
    uint8_t          tcs_attributes_size;
    bsp_tcs_attr_t * tcs_attributes;         /*!< The TCS attributes */
    uint16_t         cs_otp_program_version; /*!< The version of the CS as described by the BSP_TCS_GROUP_TESTPROGRAM_VERSION attribute*/
    uint16_t         cs_valid;
} bsp_tcs_shared_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/**
 * @brief TCS custom trim values callback
 * @param[in] values_group the TCS group id custom trim values belong to
 * @param[in] user_data user specific data
 * @param[in] values custom trim values
 * @param[in] size the number of the custom trim values
 */
typedef void (* bsp_tcs_custom_values_cb)(bsp_tcs_gid_t values_group, void * user_data, uint32_t * values,
                                          uint8_t size);

/**
 * @brief retrieve the TCS values from CS located in OTP or flash and then store
 * TCS register pair address, value  and/or custom value custom_trim_value in the Global TCS array
 */
void bsp_tcs_get_trim_values_from_cs(void);

/**
 * @brief Reads the timestamp from the parsed CS
 *
 * @returns The timestamp value. The function returns 0 in case timestamp does not exist in the CS
 */
uint32_t bsp_tcs_read_timestamp(void);

/**
 * @brief Reads the program version from the parsed CS
 *
 * @returns The version number. The function returns 0 in case version does not exist in the CS\n
 *      <b>Example: 01000501</b> The program revision is 1.00.05.01
 */
uint32_t bsp_tcs_read_program_version(void);

/**
 * @brief Reads the Wafer position from the parsed CS
 *
 * @returns The wafer position. The function returns 0 in case wafer does not exist in the CS\n
 *     B2: Wafer number B1: Y coord B0: X coord. if this is QFN or BGA, it is 0.
 */
uint32_t bsp_tcs_read_wafer(void);

/**
 * @brief Get register value pairs contained in a group id of the TCS array
 * @param[in] gid the group id
 * @param[out] values the pointer to the start of the register pair values
 * @param[out] size the number of the register pair values
 *
 * @warning if size is zero then values is not a valid pointer. size should have been
 * initialized to zero
 */
void bsp_tcs_get_reg_pairs(bsp_tcs_gid_t gid, uint32_t ** values, uint8_t * size);

/**
 * @brief Get the custom_trim_values per gid
 *
 * @param[in] gid the TCS group id of the requested custom trim values
 * @param[out] values the pointer to the start of the custom trim values
 * @param[out] size the number of the custom trim values
 *
 * @warning if size is zero then there are no custom trim values for this gid,
 *  values points to invalid data. size should have been initialized to zero
 */
void bsp_tcs_get_custom_values(bsp_tcs_gid_t gid, uint32_t ** values, uint8_t * size);

/**
 * @brief Apply the register value pairs contained in a group id of the TCS array.
 * @param [in] gid the group id
 */
bool bsp_tcs_apply_reg_pairs(bsp_tcs_gid_t gid);

/**
 * @brief handles the custom_trim_values per gid according to callback
 *
 * @param[in] gid the TCS group id of custom trim values to apply
 * @param[in] cb the callback that applies the custom trim values
 * @param[in] user_data the argument to callback function
 *
 * @warning callback is called only if custom trim values are configured
 */
bool bsp_tcs_apply_custom_values(bsp_tcs_gid_t gid, bsp_tcs_custom_values_cb cb, void * user_data);

/**
 * @brief Retrieve the configured group ids belong to a specific power domain
 *
 * @param[in] domain the power domain
 * @param[out] gids pointer to the array which will filled with the group ids.
 * @param[in] size the length of the gids
 * The last valid entry in the array is before BSP_TCS_GROUP_RESERVED which marks the end.
 */
void bsp_tcs_get_gid_per_domain(bsp_tcs_domain_t domain, uint8_t * gids, uint8_t size);

/**
 * @brief handles the custom_trim_values per gid according to callback
 *
 * @param[in] gid the TCS group id of custom trim values to apply
 * @param[in] user_data the argument to callback function
 * @param[in] val pointer to the returned values
 * @param[in] len size of returned values (bytes)
 *
 * @warning callback is called only if custom trim values are configured
 */
void bsp_tcs_custom_values_system_cb(bsp_tcs_gid_t gid, void * user_data, uint32_t * val, uint8_t len);

/**
 * @brief Read XTAL_REG value on TCS
 *
 * @param[out] dest     XTAL regiter value
 */
bool bsp_tcs_otp_read_xtal(uint32_t * dest);

/**
 * @brief Write XTAL_REG value on TCS
 *
 * @param[in] dest          XTAL regiter value
 * @param[in] check_option  TCS written check option
 */
bool bsp_tcs_otp_write_xtal(uint32_t * dest, check_option_t check_option);

/**
 * @brief Read MAC address on TCS
 *
 * @param[out] mac      MAC address array - uint32_t mac[2]
 */
bool bsp_tcs_otp_read_mac(uint32_t * mac);

/**
 * @brief Write MAC address on TCS
 *
 * @param[in] mac           MAC address array -uint32_t mac[2]
 * @param[in] check_option  TCS written check option
 */
bool bsp_tcs_otp_write_mac(uint32_t * mac, check_option_t check_option);

/**
 * @brief Read MAC written count on TCS
 *
 * @return the number of MAC written count
 */
uint16_t bsp_tcs_otp_mac_cnt(void);

/**
 * @brief Add data to TCS (Trim Calibration Section) on OTP
 *
 * @param[in] dest        Pointer to data array to be added to TCS
 * @param[in] word_size   Size of data in 32-bit words
 *
 * @return true if data was successfully added to TCS
 * @return false if addition failed
 *
 * @note This function adds the provided data to the TCS of OTP area.
 *       The data must be aligned to 32-bit words.
 */
bool bsp_tcs_otp_add(uint32_t * dest, uint32_t word_size);

#if TCS_INFO
void bsp_tcs_info_printf(bool match);

#endif
#endif
