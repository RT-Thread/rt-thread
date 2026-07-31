/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_tcs.h"
#include "config/bsp_memory_defaults_ra6w1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define OTP_CS_END                      (0x0000C0 * 4)
#define OTP_CS_SIZE                     (640)

#define CS_START_CMD                    0xA5A5A5A5
#define CS_BOOTER_VAL                   0xE6000000

#define CS_DATA_TYPE_MASK               0xFF000000
#define CS_DATA_TYPE_FILED              0x80000000

#define CS_DATA_VAL                     0xE1000000
#define CS_SDK_VAL                      0xE9000000
#define CS_STX_CONFIG                   0xE8000000 // 2 bytes of data follow
#define CS_HW_CFG_VAL                   0xEC000000 // 1 byte of data follow
#define CS_MIN_FW_VAL                   0xEB000000
#define CS_DELAYCMD                     0xED000000 // 1 byte of data follow
#define CS_CRC_SKIP                     0xEE000000 // 1 byte of data follow
#define CS_STOP_CMD                     0x00000000
#define CS_EMPTY_VAL                    0xFFFFFFFF

#define CS_SDK_VAL_GID_MASK             0x000000FF
#define CS_SDK_VAL_LEN_MASK             0x0000FF00
#define CS_SDK_VAL_SETID_MASK           0x00FF0000

#define OTP_CS_ADDRESS                  0x00000100
#define CS_MAX_SIZE                     (TCS_DATA_SIZE * 4) // 256 entries of 4 bytes

/* 0x50060F9C value used in booter code */
#define MAX_REG_ADDR                    0x5100155C

#define EMPTY                           0xFF
#define NOT_RETAINED                    0
#define RETAINED                        1

#define MAX_ATTRIBUTE                   20
#define MAX_DATA_SIZE                   100
#define HEADER_SIZE                     0x60
#define HEADER_STRUCT_SIZE              0x10
#define SIZE_RETAINED_TCS_ATTRIBUTES    (0xFF - HEADER_SIZE)

#define CS_VALID_PATTERN                0xA5A5

#define XTAL_REG                        0x400C0204
#define TCS_TAG_MAC_ADDR                0xe9000221
#define RENESAS_MAC_UAP_LOWER_MASK      0xff000000

#define T2_NULL_DATA_SIZE               0x7
#define T2_PROGRAM_VER_START            0x21U
#define T2_PROGRAM_VER_END              0x23U

/**
 * The TCS data placed in shared memory
 */
#define SYS_TCS_SHARED                  (shared_tcs.sys_tcs_shared)
#define SYS_TCS_RETAINED                (retained_tcs->sys_tcs_shared)
#define SYS_TCS                         (current_tcs->sys_tcs_shared)

/* For fixing T2 production */
#define TCS_PATCH_BASE                  0x75
#define TCS_PROD_MAC                    0xe9000221
#define TCS_PROD_VER                    0xe90001c3

#if TCS_INFO
 #define INFO_PRINTF(...)    printf(__VA_ARGS__)
#else
 #define INFO_PRINTF(...)
#endif

#define SOURCE_DATA_INIT(base, sections)                 \
    {                                                    \
        .base_address      = base,                       \
        .num_sections      = FSP_ARRAY_LENGTH(sections), \
        .section_addresses = sections,                   \
    }

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct
{
    uint32_t reg_address;
    bool     trimmed;
} reg_trimmed_t;

typedef struct
{
    bsp_tcs_shared_t sys_tcs_shared;
} tcs_t;

typedef struct
{
    uint32_t         base_address;
    uint8_t          num_sections;
    const uint32_t * section_addresses;
} source_data_t;

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
static const uint32_t renesas_oui_list[] = {0x749050, 0x7c152d};

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
tcs_t          * current_tcs;
tcs_t          * retained_tcs            = (tcs_t *) dg_configTCS_RTM_ADDR;
bsp_tcs_attr_t * retained_tcs_attributes = (bsp_tcs_attr_t *) (dg_configTCS_RTM_ADDR + HEADER_STRUCT_SIZE);
uint32_t       * retained_tcs_buffer     = (uint32_t *) (dg_configTCS_RTM_ADDR + HEADER_SIZE);

/**
 * Pointer to the TCS data as parser by the TCS parser
 * \note This variable is initialized to a value other than zero
 *       so to be placed in the .data section
 */
uint32_t       * tcs_data   = (uint32_t *) 0xFFFFFFFF;
bsp_tcs_source_t tcs_source = EMPTY;

#if BSP_FEATURE_TCS_SYS_RAM
tcs_t          shared_tcs;
bsp_tcs_attr_t tcs_attributes[MAX_ATTRIBUTE];
uint32_t       tcs_buffer[MAX_DATA_SIZE];

static const uint32_t default_section[] = {0};
static const uint32_t otp_sections[]    = {0, 0x300};
#endif

/* Max of array is 52 bytes, current it's 52 bytes (row is 4 bytes, current 13) */
static const bsp_tcs_attr_t based_on_tcs_attributes[MAX_ATTRIBUTE] =
{
    {BSP_TCS_GROUP_MAC_ADDR,            BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_NA,
     NOT_RETAINED, EMPTY, 0},
    {BSP_TCS_GROUP_SKIP,                BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_PD_SYS,
     NOT_RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_PD_SYS,              BSP_TCS_TYPE_REG_PAIR,                                 BSP_TCS_DOMAIN_PD_SYS,
     NOT_RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_PD_ADC,              BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_PD_COM,
     NOT_RETAINED, EMPTY,
     0},

    {BSP_TCS_GROUP_PD_WIFI_TRIM_RF_HPI, BSP_TCS_TYPE_REG_PAIR,                                 BSP_TCS_DOMAIN_PD_RAD,
     RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_PD_WIFI_TRIM_LUT,    BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_PD_RAD,
     RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_PD_WIFI_TRIM_XTAL,   BSP_TCS_TYPE_REG_PAIR,                                 BSP_TCS_DOMAIN_PD_RAD,
     RETAINED, EMPTY,
     0},

    /* Production Test Section */
    {BSP_TCS_GROUP_CHIP_ID,             BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_NA,
     NOT_RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_PROD_INFO,           BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_NA,
     NOT_RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_PROD_WAFER,          BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_NA,
     NOT_RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_TESTPROGRAM_VERSION, BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_NA,
     NOT_RETAINED, EMPTY,
     0},
    {BSP_TCS_GROUP_PROD_SW_IP,          BSP_TCS_TYPE_TRIM_VAL,                                 BSP_TCS_DOMAIN_NA,
     NOT_RETAINED, EMPTY,
     0},
    {0,                                 BSP_TCS_TYPE_RESERVED,                                 0,
     0, 0,
     0}
};                                     /* GID 18 */

#if BSP_FEATURE_TCS_SYS_RAM
static const bsp_tcs_source_t tcs_parsing_order[] =
{
    BSP_TCS_OTP,
    BSP_TCS_OQSPI,
 #if (USE_TCS_NVMS == 1)
  #ifdef MEMORY_NVMS_OTP_ADDRESS
    BSP_TCS_NVMS,
  #endif                               /* MEMORY_NVMS_OTP_ADDRESS */
 #endif                                /* USE_TCS_NVMS == 1*/
};

static const source_data_t source_data[] =
{
    /* TCS_OTP */
    SOURCE_DATA_INIT(MEMORY_OTP_BASE + OTP_CS_ADDRESS, otp_sections),

    /* TCS_OQSPI */
    SOURCE_DATA_INIT(MEMORY_OQSPIC_S_BASE,             default_section),
};

static const uint32_t zero_parttern[7] = {0, };
#endif

/***********************************************************************************************************************
 * Private functions
 **********************************************************************************************************************/
static uint32_t bsp_mac_reverse (register uint32_t x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));

    return ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
}

static bool bsp_mac_is_renesas_oui (uint32_t upper_mac, uint32_t lower_mac)
{
    uint8_t idx = 0;

    for (idx = 0; idx < sizeof(renesas_oui_list) / sizeof(renesas_oui_list[0]); ++idx)
    {
        uint32_t rev_oui = bsp_mac_reverse(renesas_oui_list[idx]);

        if ((upper_mac == (rev_oui >> 8)) &&
            ((lower_mac & RENESAS_MAC_UAP_LOWER_MASK) >> 24 == (rev_oui & 0xFF)))
        {
            return true;
        }
    }

    return false;
}

static uint16_t bsp_based_attributes_size (void)
{
    return sizeof(based_on_tcs_attributes) / sizeof(based_on_tcs_attributes[0]);
}

static uint16_t bsp_based_gid_to_idx (uint16_t gid)
{
    uint16_t i;
    for (i = 0; i < sizeof(based_on_tcs_attributes) / sizeof(based_on_tcs_attributes[0]); i++)
    {
        if (gid == based_on_tcs_attributes[i].value_gid)
        {
            return i;
        }
    }

    return --i;
}

static uint16_t bsp_tcs_gid_to_idx (uint16_t gid)
{
    uint16_t i;
    for (i = 0; i < SYS_TCS.tcs_attributes_size; i++)
    {
        if (gid == SYS_TCS.tcs_attributes[i].value_gid)
        {
            return i;
        }
    }

    return --i;
}

#if BSP_FEATURE_TCS_SYS_RAM
static uint16_t bsp_retained_gid_to_idx (uint16_t gid)
{
    uint16_t i;
    for (i = 0; i < SYS_TCS_RETAINED.tcs_attributes_size; i++)
    {
        if (gid == SYS_TCS_RETAINED.tcs_attributes[i].value_gid)
        {
            return i;
        }
    }

    return --i;
}

static bsp_tcs_type_t bsp_tcs_get_value_type (bsp_tcs_gid_t gid)
{
    BSP_CHECK_DEBUG(gid < BSP_TCS_GROUP_MAX);

    if (bsp_tcs_gid_to_idx(gid) == (SYS_TCS.tcs_attributes_size - 1))
    {
        return BSP_TCS_TYPE_RESERVED;
    }

    return SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].value_type;
}

static bool bsp_tcs_set_tcs (bsp_tcs_gid_t gid, uint32_t is_set)
{
    if (is_set)
    {
        if (bsp_based_gid_to_idx(gid) == (bsp_based_attributes_size() - 1))
        {
            current_tcs = &shared_tcs;

            return false;
        }

        if (based_on_tcs_attributes[bsp_based_gid_to_idx(gid)].is_retained == false)
        {
 #if BSP_FEATURE_TCS_SYS_RAM
            current_tcs = &shared_tcs;
 #else
            current_tcs = retained_tcs;
 #endif
        }
        else
        {
            current_tcs = retained_tcs;
        }
    }
    else
    {
 #if BSP_FEATURE_TCS_SYS_RAM
        current_tcs = &shared_tcs;
        tcs_data    = SYS_TCS_SHARED.tcs_data;
 #endif
    }

    if (SYS_TCS.cs_valid != CS_VALID_PATTERN)
    {
        return false;
    }

    return true;
}

static void init_tcs_attributes_array (void)
{
    memset(tcs_buffer, 0, sizeof(tcs_buffer));

    memcpy(tcs_attributes, based_on_tcs_attributes, sizeof(based_on_tcs_attributes));
    SYS_TCS_SHARED.tcs_data       = tcs_buffer;
    SYS_TCS_SHARED.tcs_attributes = tcs_attributes;

    memset(retained_tcs_buffer, 0, SIZE_RETAINED_TCS_ATTRIBUTES);

    SYS_TCS_RETAINED.tcs_data       = retained_tcs_buffer;
    SYS_TCS_RETAINED.tcs_attributes = retained_tcs_attributes;
}

static uint32_t fetch_tcs_entry (bsp_tcs_source_t source, uint32_t address)
{
    uint32_t cs_value = CS_EMPTY_VAL;

    if (source < FSP_ARRAY_LENGTH(source_data))
    {
        cs_value = *((uint32_t *) ((uint32_t) source_data[source].base_address + address));
    }

    return cs_value;
}

#endif

static void store_tcs (uint32_t address, uint8_t gid_len, bsp_tcs_source_t source, bool reverse)
{
    int      i = 0;
    uint16_t index;
    BSP_CHECK_DEBUG(tcs_data);

    /* Address --> GID header */
    uint32_t      value = fetch_tcs_entry(source, address);
    bsp_tcs_gid_t gid   = (uint8_t) (value & CS_SDK_VAL_GID_MASK);

    if (gid >= BSP_TCS_GROUP_MAX)
    {
        return;
    }

    if (bsp_tcs_gid_to_idx(gid) == (SYS_TCS.tcs_attributes_size - 1))
    {
        return;
    }

    bsp_tcs_type_t type = bsp_tcs_get_value_type(gid);

    if (type == BSP_TCS_TYPE_TRIM_VAL)
    {
        /* BSP_TCS_TYPE_TRIM_VAL could have different sizes during parsing
         * it is acceptable multiple instances with same GID to have different sizes,
         * only the newest will be finally stored. We cannot identify the newest but
         * at least the ones that fit will be stored until the newest is parsed
         */
        if (gid_len != SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size)
        {
            return;
        }
    }

    /* Start of storing TCS entries */
    index = SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].start;

    /* For BSP_TCS_TYPE_REG_PAIR search tcs_data to find empty slot
     * For BSP_TCS_TYPE_TRIM_VAL fragmentation is not supported and always the newest entries are stored
     */
    if (type == BSP_TCS_TYPE_REG_PAIR)
    {
        uint16_t gid_start = index;
        uint8_t  gid_size  = SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size;

        /* Search tcs_data to find empty slot */
        while (tcs_data[index] != 0)
        {
            /* Check if the index is inside the allocated space in tcs_data[] for this GID */
            BSP_CHECK_DEBUG(index < (gid_start + gid_size));
            if (index >= (gid_start + gid_size))
            {
                return;
            }

            /* Go to next register address */
            index += 2;
        }
    }

    while (i < gid_len)                /* 4 bytes entries */
    {
        address += 4;
        if (reverse == true)
        {
            tcs_data[index] = bsp_mac_reverse(fetch_tcs_entry(source, address));
        }
        else
        {
            tcs_data[index] = fetch_tcs_entry(source, address);
        }

        index++;
        i++;
    }
}

/* The calculated size in bytes, that is the number
 * of entries * sizeof(int)
 * returns the size in bytes
 */
static uint16_t get_size_of_cs (bsp_tcs_source_t source)
{
    uint32_t value    = 0;
    uint32_t address  = 0;
    uint16_t max_size = CS_MAX_SIZE;
    uint16_t size     = 0;
    uint32_t i;

    for (i = 0; i < source_data[source].num_sections; i++)
    {
        address = source_data[source].section_addresses[i];
        if ((value = fetch_tcs_entry(source, address)) != CS_START_CMD)
        {
            /* This section does not contain CS */
            continue;
        }

        /* Check next entry */
        address += 4;
        while (address < max_size)
        {
            value = fetch_tcs_entry(source, address);

            if ((value == CS_STOP_CMD) || (value == CS_EMPTY_VAL))
            {
                /* End of CS */
                break;
            }
            else if (value <= MAX_REG_ADDR)
            {
                /* Address value pair parsed by bootrom, skip this value */
                if (value == XTAL_REG)
                {
                    SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(BSP_TCS_GROUP_PD_WIFI_TRIM_XTAL)].size = 2;
                }

                address += 0x4;
            }
            else if (((value & CS_DATA_TYPE_MASK) > CS_DATA_TYPE_FILED) && ((value & CS_DATA_TYPE_MASK) < CS_DATA_VAL))
            {
                address += 0x4;
                address += 0x4;
            }
            else if (((value & CS_DATA_TYPE_MASK) == CS_BOOTER_VAL) || ((value & CS_DATA_TYPE_MASK) == CS_STX_CONFIG) ||
                     (value == CS_MIN_FW_VAL))
            {
                address += 0x4;
            }
            else if ((value & CS_DATA_TYPE_MASK) == CS_SDK_VAL)
            {
                /* SDK value */
                uint8_t       tcs_len = (value & CS_SDK_VAL_LEN_MASK) >> 8;
                bsp_tcs_gid_t gid     = (uint8_t) (value & CS_SDK_VAL_GID_MASK);
                uint8_t       setid   = (value & CS_SDK_VAL_SETID_MASK) >> 16;

                /* Skip next tcs values. */

                if ((gid >= BSP_TCS_GROUP_MAX) || (setid != 0x00))
                {
                    /* Skip this entry */
                    address += tcs_len * 4;
                    address += 0x4;
                    continue;
                }

                if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_TRIM_VAL)
                {
                    /*always keep the last found size */
                    if (SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size != tcs_len)
                    {
                        uint32_t tmp_dest[10];
                        for (i = 0; i < 10; i++)
                        {
                            tmp_dest[i] = fetch_tcs_entry(source, address + (i * 4));
                        }

                        if (((tmp_dest[1] >= T2_PROGRAM_VER_START)) && (tmp_dest[9] == TCS_TAG_MAC_ADDR))
                        {
                            /* H/W workaround T2 production */
                            if (tmp_dest[2] == XTAL_REG)
                            {
                                SYS_TCS_SHARED.tcs_attributes
                                [bsp_tcs_gid_to_idx(BSP_TCS_GROUP_PD_WIFI_TRIM_XTAL)].size = 2;
                            }

                            if (!memcmp(tmp_dest + 2, zero_parttern, 7 * sizeof(uint32_t)) ||
                                !memcmp(tmp_dest + 4, zero_parttern, 5 * sizeof(uint32_t)))
                            {
                                tcs_len += T2_NULL_DATA_SIZE;
                            }
                        }

                        /* Update with new size */
                        size -= (uint16_t) (4 * SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size);
                        size += (uint16_t) (4 + tcs_len);
                        SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size = tcs_len & 0xf;
                    }

                    address += tcs_len * 4; // Skip next tcs values.
                }
                else if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_REG_PAIR)
                {
                    /* Check that BSP_TCS_TYPE_REG_PAIR values are of an even number */
                    if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_REG_PAIR)
                    {
                        BSP_CHECK_DEBUG((tcs_len & 0x01) == 0);
                    }

                    /* Size should be in bytes */
                    size += (uint16_t) (4 * tcs_len);
                    SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size += tcs_len;
                    address += tcs_len * 4; // Skip next tcs values.
                }
                else if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_HPI_REG_PAIR)
                {
                    /* Size should be in bytes */
                    size += (uint16_t) (4 * tcs_len);
                    SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size += tcs_len;
                    address += tcs_len * 4; // Skip next tcs values.
                }
                else
                {
                    address += tcs_len * 4;
                }
            }

            /* Go to next word this value is not related to TCS */
            address += 0x4;
        }
    }

    return size;
}

static void store_cs_attributes (bsp_tcs_source_t source, uint16_t size)
{
    uint32_t value = 0;
    uint32_t index = 0;
    uint32_t address;
    uint32_t i;

    for (i = 0; i < source_data[source].num_sections; i++)
    {
        address = source_data[source].section_addresses[i];
        if ((value = fetch_tcs_entry(source, address)) != CS_START_CMD)
        {
            /* This section does not contain CS */
            continue;
        }

        address += 4;

        while (address < size)
        {
            value = fetch_tcs_entry(source, address);

            if ((value == CS_STOP_CMD) || (value == CS_EMPTY_VAL))
            {
                /* End of CS */
                break;
            }
            else if (value <= MAX_REG_ADDR)
            {
                /* Address - value pair */
                if (value == XTAL_REG)
                {
                    index =
                        SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(BSP_TCS_GROUP_PD_WIFI_TRIM_XTAL)].start;
                    tcs_data[index]     = fetch_tcs_entry(source, address);
                    tcs_data[index + 1] = fetch_tcs_entry(source, address + 4);
                }

                address += 0x4;
            }
            else if (((value & CS_DATA_TYPE_MASK) > CS_DATA_TYPE_FILED) && ((value & CS_DATA_TYPE_MASK) < CS_DATA_VAL))
            {
                address += 0x4;
                address += 0x4;
            }
            else if ((value == CS_BOOTER_VAL) || (value == CS_MIN_FW_VAL) ||
                     ((value & CS_DATA_TYPE_MASK) == CS_STX_CONFIG))
            {
                /* Skip booter value and minimun FW version value */
                address += 0x4;
            }
            else if ((value & CS_DATA_TYPE_MASK) == CS_SDK_VAL)
            {
                /* SDK value */
                uint8_t       gid_len = (value & CS_SDK_VAL_LEN_MASK) >> 8;
                uint8_t       setid   = (value & CS_SDK_VAL_SETID_MASK) >> 16;
                bsp_tcs_gid_t gid     = (uint8_t) (value & CS_SDK_VAL_GID_MASK);
                uint32_t      tmp_dest[10];
                uint32_t      tmp_address = address + 4;

                if (gid == BSP_TCS_GROUP_TESTPROGRAM_VERSION)
                {
                    for (i = 0; i < 10; i++)
                    {
                        tmp_dest[i] = fetch_tcs_entry(source, address + (i * 4));
                    }

                    if (((tmp_dest[1] >= T2_PROGRAM_VER_START)) && (tmp_dest[9] == TCS_TAG_MAC_ADDR))
                    {
                        /* H/W workaround T2 production */
                        if (tmp_dest[2] == XTAL_REG)
                        {
                            index =
                                SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(BSP_TCS_GROUP_PD_WIFI_TRIM_XTAL)].start;
                            tcs_data[index]     = tmp_dest[2];
                            tcs_data[index + 1] = tmp_dest[3];
                        }

                        if (!memcmp(tmp_dest + 2, zero_parttern, 7 * sizeof(uint32_t)) ||
                            !memcmp(tmp_dest + 4, zero_parttern, 5 * sizeof(uint32_t)))
                        {
                            gid_len += T2_NULL_DATA_SIZE;
                        }
                    }

                    store_tcs(address, gid_len, source, 0);
                }
                else if (gid == BSP_TCS_GROUP_MAC_ADDR)
                {
                    tmp_dest[0] = fetch_tcs_entry(source, tmp_address);
                    tmp_dest[1] = fetch_tcs_entry(source, tmp_address + 4);
                    if ((gid == BSP_TCS_GROUP_MAC_ADDR) && bsp_mac_is_renesas_oui(tmp_dest[1], tmp_dest[0]))
                    {
                        store_tcs(address, gid_len, source, 1);
                    }
                    else
                    {
                        store_tcs(address, gid_len, source, 0);
                    }
                }
                else if (setid == 0x00)
                {
                    /* store entries with SET ID 0x00 */
                    store_tcs(address, gid_len, source, 0);
                }

                /* Skip next tcs values. */
                address += gid_len * 4;
            }

            /* Advance address by 4 bytes */
            address += 0x4;
        }
    }
}

static bool bsp_tcs_get_item_in_otp_cs (const uint32_t item, uint32_t * dest, uint16_t * size)
{
    volatile bsp_tcs_source_t source = BSP_TCS_OTP;
    volatile uint32_t         address, tmp_address;
    volatile uint32_t         value = 0;
    volatile uint16_t         max_size = CS_MAX_SIZE;
    volatile uint32_t         i, e;
    volatile bool             ret = false;

    *size = 0;
    for (i = 0; i < source_data[source].num_sections; i++)
    {
        address = source_data[source].section_addresses[i];
        value   = fetch_tcs_entry(source, address);
        if (value != CS_START_CMD)
        {
            continue;
        }

        address += 0x4;

        while (address < max_size)
        {
            value = fetch_tcs_entry(source, address);
            if ((value == CS_STOP_CMD) || (value == CS_EMPTY_VAL))
            {
                /* End of CS */
                break;
            }
            else if (value <= MAX_REG_ADDR)
            {
                /* Address - value pair */
                if (item == value)
                {
                    *dest = fetch_tcs_entry(source, address + 4);
                    *size = 1;
                }

                /* Skip value entry */
                address += 0x4;
            }
            else if (((value & CS_DATA_TYPE_MASK) > CS_DATA_TYPE_FILED) && ((value & CS_DATA_TYPE_MASK) < CS_DATA_VAL))
            {
                address += 0x4;
                address += 0x4;
            }
            else if (((value & CS_DATA_TYPE_MASK) == CS_BOOTER_VAL) || ((value & CS_DATA_TYPE_MASK) == CS_STX_CONFIG) ||
                     (value == CS_MIN_FW_VAL))
            {
                address += 0x4;
            }
            else if ((value & CS_DATA_TYPE_MASK) == CS_SDK_VAL)
            {
                uint8_t       tcs_len = (value & CS_SDK_VAL_LEN_MASK) >> 8;
                bsp_tcs_gid_t gid     = (uint8_t) (value & CS_SDK_VAL_GID_MASK);
                uint8_t       setid   = (value & CS_SDK_VAL_SETID_MASK) >> 16;
                uint32_t      tmp_dest[10];

                if ((item > MAX_REG_ADDR) && (gid == (item & CS_SDK_VAL_GID_MASK)))
                {
                    tmp_address = address + 4;
                    *size       = tcs_len;
                    if (gid == BSP_TCS_GROUP_MAC_ADDR)
                    {
                        tmp_dest[0] = fetch_tcs_entry(source, tmp_address);
                        tmp_dest[1] = fetch_tcs_entry(source, tmp_address + 4);
                        if (bsp_mac_is_renesas_oui(tmp_dest[1], tmp_dest[0]))
                        {
                            for (e = 0; e < tcs_len; e++)
                            {
                                dest[e] = bsp_mac_reverse(fetch_tcs_entry(source, tmp_address + e * 4));
                            }
                        }
                        else
                        {
                            for (e = 0; e < tcs_len; e++)
                            {
                                dest[e] = fetch_tcs_entry(source, tmp_address + e * 4);
                            }
                        }
                    }
                    else
                    {
                        for (e = 0; e < tcs_len; e++)
                        {
                            dest[e] = fetch_tcs_entry(source, tmp_address + e * 4);
                        }
                    }
                }

                if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_TRIM_VAL)
                {
                    if (gid == BSP_TCS_GROUP_TESTPROGRAM_VERSION)
                    {
                        for (i = 0; i < 10; i++)
                        {
                            tmp_dest[i] = fetch_tcs_entry(source, address + (i * 4));
                        }

                        if (((tmp_dest[1] >= T2_PROGRAM_VER_START)) && (tmp_dest[9] == TCS_TAG_MAC_ADDR))
                        {
                            /* H/W workaround T2 production */
                            if (tmp_dest[2] == XTAL_REG)
                            {
                                dest[0] = tmp_dest[3];
                            }

                            if (!memcmp(tmp_dest + 2, zero_parttern, 7 * sizeof(uint32_t)) ||
                                !memcmp(tmp_dest + 4, zero_parttern, 5 * sizeof(uint32_t)))
                            {
                                tcs_len += T2_NULL_DATA_SIZE;
                            }
                        }
                    }

                    address += tcs_len * 4; // Skip next tcs values
                }
                else if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_REG_PAIR)
                {
                    if ((item > MAX_REG_ADDR) && (gid == (item & CS_SDK_VAL_GID_MASK)))
                    {
                        address += tcs_len * 4; // Skip next tcs values.
                    }
                    else
                    {
                        tmp_address = address + 4;
                        for (e = 0; e < tcs_len / 2; e += 2)
                        {
                            value = fetch_tcs_entry(source, tmp_address + e * 4);
                            if (item == value)
                            {
                                *dest = fetch_tcs_entry(source, tmp_address + e * 4 + 1);
                                *size = 1;
                            }
                        }

                        address += tcs_len * 4; // Skip next tcs values.
                    }
                }
                else if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_HPI_REG_PAIR)
                {
                    address += tcs_len * 4; // Skip next tcs values.
                }
                else
                {
                    address += tcs_len * 4; // Skip next tcs values.
                }

                if ((gid >= BSP_TCS_GROUP_MAX) || (setid != 0x00))
                {
                    address += 0x4;    // Skip this entry
                    continue;
                }
            }

            address += 0x4;            // advance address by 4 bytes
        }

        ret = true;
    }

    return ret;
}

static uint32_t bsp_tcs_get_otp_size (uint16_t * size, uint32_t item, uint16_t * item_count)
{
    uint32_t value    = 0;
    uint32_t address  = 0;
    uint32_t i        = 0;
    uint16_t max_size = CS_MAX_SIZE;

    *size       = 0;
    *item_count = 0;

    address = source_data[BSP_TCS_OTP].section_addresses[0];
    if ((value = fetch_tcs_entry(BSP_TCS_OTP, address)) != CS_START_CMD)
    {

        // This section does not contain CS
        return 0;
    }

    /* Check next entry */
    address += 4;
    while (address < max_size)
    {
        value = fetch_tcs_entry(BSP_TCS_OTP, address);

        if ((value == CS_STOP_CMD) || (value == CS_EMPTY_VAL))
        {
            /* End of CS */
            break;
        }

        if (value <= MAX_REG_ADDR)
        {
            /* Address-value pair parsed by bootrom, skip this value */
            address += 0x4;
            if (item == value)
            {
                (*item_count)++;
            }
        }
        else if (((value & CS_DATA_TYPE_MASK) > CS_DATA_TYPE_FILED) && ((value & CS_DATA_TYPE_MASK) < CS_DATA_VAL))
        {
            address += 0x4;
            address += 0x4;
        }
        else if (((value & CS_DATA_TYPE_MASK) == CS_BOOTER_VAL) || ((value & CS_DATA_TYPE_MASK) == CS_STX_CONFIG) ||
                 (value == CS_MIN_FW_VAL))
        {
            address += 0x4;
        }
        else if ((value & CS_DATA_TYPE_MASK) == CS_SDK_VAL)
        {
            uint8_t       tcs_len     = (value & CS_SDK_VAL_LEN_MASK) >> 8;
            bsp_tcs_gid_t gid         = (uint8_t) (value & CS_SDK_VAL_GID_MASK);
            uint8_t       setid       = (value & CS_SDK_VAL_SETID_MASK) >> 16;
            uint32_t      tmp_address = 0;
            uint32_t      e           = 0;

            if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_TRIM_VAL)
            {
                uint32_t tmp_dest[10];
                for (i = 0; i < 10; i++)
                {
                    tmp_dest[i] = fetch_tcs_entry(BSP_TCS_OTP, address + (i * 4));
                }

                if (((tmp_dest[1] >= T2_PROGRAM_VER_START)) && (tmp_dest[9] == TCS_TAG_MAC_ADDR))
                {
                    /* H/W workaround T2 production */
                    if (!memcmp(tmp_dest + 2, zero_parttern, 7 * sizeof(uint32_t)) ||
                        !memcmp(tmp_dest + 4, zero_parttern, 5 * sizeof(uint32_t)))
                    {
                        tcs_len += T2_NULL_DATA_SIZE;
                    }
                }

                address += tcs_len * 4; // Skip next tcs values.
            }
            else if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_REG_PAIR)
            {
                for (e = 0; e < tcs_len / 2; e += 2)
                {
                    value = fetch_tcs_entry(BSP_TCS_OTP, tmp_address + e * 4);
                    if (item == value)
                    {
                        fetch_tcs_entry(BSP_TCS_OTP, tmp_address + e * 4 + 1);
                        (*item_count)++;
                    }
                }

                address += tcs_len * 4; // Skip next tcs values.
            }
            else if (bsp_tcs_get_value_type(gid) == BSP_TCS_TYPE_HPI_REG_PAIR)
            {
                address += tcs_len * 4; // Skip next tcs values.
            }
            else
            {
                address += tcs_len * 4; // Skip next tcs values.
            }

            if ((item > MAX_REG_ADDR) && (gid == (item & CS_SDK_VAL_GID_MASK)))
            {
                (*item_count)++;
            }

            if ((gid >= BSP_TCS_GROUP_MAX) || (setid != 0x00))
            {
                address += 0x4;        // Skip this entry
                continue;
            }
        }

        /* Go to next word this value is not related to TCS */
        address += 0x4;
    }

    *size = (uint16_t) address;

    return true;
}

static bool t2_production_patch (void)
{
    uint32_t       src[15]       = {0, };
    uint32_t       result        = 0;
    const uint32_t fix_blank1[2] = {0xe9000602, 0x0};
    const uint32_t fix_blank2[2] = {0xe9000402, 0x0};

    /* Read OTP data */
    bsp_otp_init();
    bsp_otp_mode_set(BSP_OTP_MODE_READ);
    bsp_otp_read(src, TCS_PATCH_BASE, 15);

    /* Enter programming mode */
    bsp_otp_init();
    bsp_otp_mode_set(BSP_OTP_MODE_PROG);

    if ((src[9] != TCS_PROD_MAC) || (src[0] != TCS_PROD_VER))
    {
        goto exit;
    }

    /* Check conditions and apply patch */
    if (!memcmp(src + 2, zero_parttern, 7 * sizeof(uint32_t)))
    {
        bsp_otp_prog((uint32_t *) fix_blank1, TCS_PATCH_BASE + 2, 1);
        printf("-fix1 success\r\n");
    }
    else if (!memcmp(src + 4, zero_parttern, 5 * sizeof(uint32_t)))
    {
        bsp_otp_prog((uint32_t *) fix_blank2, TCS_PATCH_BASE + 4, 1);
        printf("-fix2 success\r\n");
    }
    else
    {
        result = false;
        printf("-fix fail\r\n");
    }

exit:
    bsp_otp_mode_set(BSP_OTP_MODE_READ);
    bsp_otp_close();

    return result;
}

static bool bsp_tcs_read_item (uint32_t item, uint32_t * dest)
{
    uint16_t item_size = 0;

    bsp_otp_init();
    bsp_otp_mode_set(BSP_OTP_MODE_READ);
    if (item > MAX_REG_ADDR)
    {
        bsp_tcs_get_item_in_otp_cs(item, dest, &item_size);

        if (item_size > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        bsp_tcs_get_item_in_otp_cs(item, dest, &item_size);
        if (item_size > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

static bool bsp_tcs_write_item (uint32_t item, uint32_t * dest, uint32_t word_size, check_option_t check_option)
{
    uint16_t otp_size = 0, size = 0;
    uint16_t item_write_count;
    uint32_t cs_start[2] = {CS_START_CMD, 0};
    uint32_t tmp_dest[30];
    uint32_t i;
    bool     ret = 0;

    if (word_size > 30)
    {
        return false;
    }

    bsp_otp_init();
    bsp_otp_mode_set(BSP_OTP_MODE_READ);

    switch (check_option)
    {
        case CHECK_OPTION_FORCE:
        {
            /* Force write */
            bsp_tcs_get_otp_size(&otp_size, item, &item_write_count);
            if (otp_size == 0)
            {
                bsp_otp_init();
                bsp_otp_mode_set(BSP_OTP_MODE_PROG);
                bsp_otp_prog(cs_start, (OTP_CS_ADDRESS / 4) + otp_size / 4, 1);
                bsp_otp_prog(&item, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 1, 1);
                bsp_otp_prog(dest, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 2, word_size);
                bsp_otp_mode_set(BSP_OTP_MODE_READ);
                bsp_otp_close();
                ret = true;
            }
            else if (otp_size < (OTP_CS_SIZE - ((word_size + 1) * 4)))
            {
                bsp_otp_init();
                bsp_otp_mode_set(BSP_OTP_MODE_PROG);
                bsp_otp_prog(&item, (OTP_CS_ADDRESS / 4) + otp_size / 4, 1);
                bsp_otp_prog(dest, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 1, word_size);
                bsp_otp_mode_set(BSP_OTP_MODE_READ);
                ret = true;
            }
            else
            {
                INFO_PRINTF("[TCS] Over size otp \r\n");
                ret = false;
            }

            break;
        }

        case CHECK_OPTION_EMPTY:
        {
            /* Write if only empty, success if write, */
            bsp_tcs_get_otp_size(&otp_size, item, &item_write_count);
            if (otp_size == 0)
            {
                bsp_otp_init();
                bsp_otp_mode_set(BSP_OTP_MODE_PROG);
                bsp_otp_prog(cs_start, (OTP_CS_ADDRESS / 4) + otp_size / 4, 1);
                bsp_otp_prog(&item, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 1, 1);
                bsp_otp_prog(dest, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 2, word_size);
                bsp_otp_mode_set(BSP_OTP_MODE_READ);
                bsp_otp_close();
                ret = true;
            }
            else if ((otp_size < (OTP_CS_SIZE - ((word_size + 1) * 4))) && (item_write_count == 0))
            {
                bsp_otp_init();
                bsp_otp_mode_set(BSP_OTP_MODE_PROG);
                bsp_otp_prog(&item, (OTP_CS_ADDRESS / 4) + otp_size / 4, 1);
                bsp_otp_prog(dest, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 1, word_size);
                bsp_otp_mode_set(BSP_OTP_MODE_READ);
                ret = true;
            }
            else
            {
                ret = false;
            }

            break;
        }

        case CHECK_OPTION_DIFFERENT:
        {
            /* Write if different success if write to compare between existing mac and new mac */
            bsp_tcs_get_otp_size(&otp_size, item, &item_write_count);
            bsp_tcs_get_item_in_otp_cs(item, tmp_dest, &size);
            if (otp_size == 0)
            {
                bsp_otp_init();
                bsp_otp_mode_set(BSP_OTP_MODE_PROG);
                bsp_otp_prog(cs_start, (OTP_CS_ADDRESS / 4) + otp_size / 4, 1);
                bsp_otp_prog(&item, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 1, 1);
                bsp_otp_prog(dest, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 2, word_size);
                bsp_otp_mode_set(BSP_OTP_MODE_READ);
                bsp_otp_close();
                ret = true;
            }
            else if (memcmp(tmp_dest, dest, word_size * 4) == 0)
            {
                ret = false;
            }
            else if ((otp_size < (OTP_CS_SIZE - ((word_size + 1) * 4))))
            {
                bsp_otp_init();
                bsp_otp_mode_set(BSP_OTP_MODE_PROG);
                bsp_otp_prog(&item, (OTP_CS_ADDRESS / 4) + otp_size / 4, 1);
                bsp_otp_prog(dest, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 1, word_size);
                bsp_otp_mode_set(BSP_OTP_MODE_READ);
                ret = true;
            }
            else
            {
                ret = false;
            }

            break;
        }

        case CHECK_OPTION_SKIP_EXISTS:
        {
            /* Skip if already written */
            bsp_tcs_get_otp_size(&otp_size, item, &item_write_count);
            if (otp_size == 0)
            {
                ret = false;
            }
            else if ((item_write_count > 0))
            {
                ret = true;
            }
            else if ((otp_size < (OTP_CS_SIZE - ((word_size + 1) * 4))) && (item_write_count == 0))
            {
                bsp_otp_init();
                bsp_otp_mode_set(BSP_OTP_MODE_PROG);
                bsp_otp_prog(&item, (OTP_CS_ADDRESS / 4) + otp_size / 4, 1);
                bsp_otp_prog(dest, (OTP_CS_ADDRESS / 4) + otp_size / 4 + 1, word_size);
                bsp_otp_mode_set(BSP_OTP_MODE_READ);
                ret = true;
            }
            else
            {
                ret = false;
            }

            break;
        }

        default:
        {
            /* For only test */
            bsp_tcs_get_otp_size(&otp_size, item, &item_write_count);
            bsp_tcs_get_item_in_otp_cs(item, tmp_dest, &size);
            INFO_PRINTF(
                "\t[TCS] -skip write item otp_size:%x(%d), item_write_count:%x, item:%lx, dest:%d, word_size:%lx\r\n",
                otp_size / 4,
                otp_size / 4,
                item_write_count,
                item,
                (int) dest,
                word_size);
            INFO_PRINTF("\t[TCS] read: tmp_data -");

            for (i = 0; i < word_size; i++)
            {
                INFO_PRINTF("%08lx,", tmp_dest[i]);
            }

            INFO_PRINTF("\r\n");

            ret = true;
            break;
        }
    }

    bsp_tcs_get_otp_size(&otp_size, item, &item_write_count);

    bsp_otp_close();

    return ret;
}

/***********************************************************************************************************************
 * Exported global functions
 **********************************************************************************************************************/
void bsp_tcs_get_trim_values_from_cs (void)
{
    uint16_t         size;
    bsp_tcs_source_t source;
    uint32_t         value = CS_STOP_CMD;
    uint8_t          count = 0;
    uint32_t         i, j;
    uint8_t          gid_offset = 0;
    uint16_t         gid        = 0;

#if (BSP_FEATURE_BSP_USE_TCS == 0)

    return;
#endif

    init_tcs_attributes_array();

    for (i = 0; i < FSP_ARRAY_LENGTH(tcs_parsing_order); i++)
    {
        source = tcs_parsing_order[i];

        for (j = 0; j < source_data[source].num_sections; j++)
        {
            uint32_t address = source_data[source].section_addresses[j];
            if ((value = fetch_tcs_entry(source, address)) != CS_START_CMD)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        if (value == CS_START_CMD)
        {
            break;
        }

        tcs_source = source;
    }

    if (value != CS_START_CMD)
    {

        /* No CS found */
        return;
    }

    current_tcs = &shared_tcs;
    SYS_TCS_SHARED.tcs_attributes_size = sizeof(based_on_tcs_attributes) / sizeof(based_on_tcs_attributes[0]);

    size = get_size_of_cs(source);

    /* The calculated size in bytes, taking into account that one entry is 4 bytes */
    BSP_CHECK_DEBUG(size < CS_MAX_SIZE);

    /* Static allocation for tcs_data */
    tcs_data = SYS_TCS_SHARED.tcs_data;

    /* Convert sizes to offsets in the tcs table and
     * set the sizes of the GID attributes */
    gid_offset = 0;
    for (gid = 0; gid < BSP_TCS_GROUP_MAX; gid++)
    {
        if (SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size != 0)
        {
            SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].start = gid_offset;
            gid_offset += SYS_TCS_SHARED.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size;
        }
    }

    /* store the tcs_data used size*/
    SYS_TCS_SHARED.tcs_data_size = gid_offset;
    store_cs_attributes(source, CS_MAX_SIZE);

    /* Static allocation for tcs_data */
    current_tcs = retained_tcs;
    tcs_data    = SYS_TCS_RETAINED.tcs_data;

    for (i = 0; i < SYS_TCS_SHARED.tcs_attributes_size; i++)
    {
        if (SYS_TCS_SHARED.tcs_attributes[i].is_retained == RETAINED)
        {
            memcpy(&SYS_TCS_RETAINED.tcs_attributes[count], &SYS_TCS_SHARED.tcs_attributes[i], sizeof(bsp_tcs_attr_t));
            count++;
        }
    }

    memset(&SYS_TCS_RETAINED.tcs_attributes[count], 0, sizeof(bsp_tcs_attr_t));
    SYS_TCS_RETAINED.tcs_attributes_size = count + 1;

    /* Convert sizes to offsets in the tcs table and
     * set the sizes of the GID attributes */
    gid_offset = 0;
    for (gid = 0; gid < BSP_TCS_GROUP_MAX; gid++)
    {
        if ((SYS_TCS_RETAINED.tcs_attributes[bsp_retained_gid_to_idx(gid)].is_retained == RETAINED) &&
            (SYS_TCS_RETAINED.tcs_attributes[bsp_retained_gid_to_idx(gid)].size != 0))
        {
            SYS_TCS_RETAINED.tcs_attributes[bsp_retained_gid_to_idx(gid)].start = gid_offset;
            gid_offset += SYS_TCS_RETAINED.tcs_attributes[bsp_retained_gid_to_idx(gid)].size;
        }
    }

    /* store the tcs_data used size*/
    SYS_TCS_RETAINED.tcs_data_size = gid_offset;
    store_cs_attributes(source, CS_MAX_SIZE);

    current_tcs               = &shared_tcs;
    tcs_data                  = SYS_TCS_SHARED.tcs_data;
    SYS_TCS_RETAINED.cs_valid = CS_VALID_PATTERN;
    SYS_TCS_SHARED.cs_valid   = CS_VALID_PATTERN;
}

void bsp_tcs_get_custom_values (bsp_tcs_gid_t gid, uint32_t ** values, uint8_t * size)
{
    if (bsp_based_gid_to_idx(gid) == (bsp_based_attributes_size() - 1))
    {
        return;
    }

    if (!bsp_tcs_set_tcs(gid, true))
    {
        return;
    }

    BSP_CHECK_DEBUG(gid < BSP_TCS_GROUP_MAX);
    BSP_CHECK_DEBUG(SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].value_type == BSP_TCS_TYPE_TRIM_VAL);

    if (SYS_TCS.tcs_data == NULL)
    {

        /* TCS is not initialize */
        return;
    }

    if (size == NULL)
    {

        /* size is mandatory */
        return;
    }

    *size = SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size;

    if (values)
    {
        if (*size == 0)
        {
            *values = NULL;
        }
        else
        {
            /* if size is not zero then start is different than EMPTY for this GID
             * so CS parsing for TCS data is done and TCS_DATA is valid */
            *values = &SYS_TCS.tcs_data[SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].start];
        }
    }

    bsp_tcs_set_tcs(gid, false);
}

bool bsp_tcs_apply_custom_values (bsp_tcs_gid_t gid, bsp_tcs_custom_values_cb cb, void * user_data)
{
    uint32_t * values = NULL;
    uint8_t    size   = 0;

    if (bsp_based_gid_to_idx(gid) == (bsp_based_attributes_size() - 1))
    {
        return false;
    }

    if (based_on_tcs_attributes[bsp_based_gid_to_idx(gid)].is_retained == false)
    {
        current_tcs = &shared_tcs;
    }
    else
    {
        current_tcs = retained_tcs;
    }

    if (SYS_TCS.cs_valid != CS_VALID_PATTERN)
    {
        return false;
    }

    if (SYS_TCS.tcs_data == NULL)
    {
        return false;
    }

    if (cb)
    {
        bsp_tcs_get_custom_values(gid, &values, &size);
        if (size != 0)
        {
            cb(gid, user_data, values, size);
        }
        else
        {
            return false;
        }
    }

    current_tcs = &shared_tcs;
    tcs_data    = SYS_TCS_SHARED.tcs_data;

    return true;
}

bool bsp_tcs_apply_reg_pairs (bsp_tcs_gid_t gid)
{
    if (bsp_based_gid_to_idx(gid) == bsp_based_attributes_size() - 1)
    {
        return false;
    }

    if (based_on_tcs_attributes[bsp_based_gid_to_idx(gid)].is_retained == false)
    {
        current_tcs = &shared_tcs;
    }
    else
    {
        current_tcs = retained_tcs;
    }

    if (SYS_TCS.cs_valid != CS_VALID_PATTERN)
    {
        return false;
    }

    if (SYS_TCS.tcs_data == NULL)
    {
        return false;
    }

    BSP_CHECK_DEBUG(gid < BSP_TCS_GROUP_MAX);
    BSP_CHECK_DEBUG(SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].value_type == BSP_TCS_TYPE_REG_PAIR ||
                    SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].value_type == BSP_TCS_TYPE_HPI_REG_PAIR);

    uint8_t start = SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].start;
    int     size  = (int) SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].size;

    if (size == 0)
    {
        return false;
    }

    if (SYS_TCS.tcs_attributes[bsp_tcs_gid_to_idx(gid)].value_type == BSP_TCS_TYPE_REG_PAIR)
    {
        while (size > 0)
        {
            if ((SYS_TCS.tcs_data[start]) != 0)
            {
                *(volatile uint32_t *) SYS_TCS.tcs_data[start] = SYS_TCS.tcs_data[start + 1];
            }

            size  -= 2;
            start += 2;
        }
    }

    current_tcs = &shared_tcs;
    tcs_data    = SYS_TCS_SHARED.tcs_data;

    return true;
}

#if TCS_INFO
void bsp_tcs_info_printf (bool match)
{
    FSP_PARAMETER_NOT_USED(match);
    uint32_t            i, e, dest = 0;
    uint16_t            item_count = 0, size = 0, word_size = 0;
    static const char * tcs_type[] =
    {
        "TYPE_TRIM_VAL",
        "TYPE_REG_PAIR",
        "TYPE_HPI_REG_PAIR",
        "TYPE_RESERVE"
    };
    static const char * tcs_domain[] =
    {
        "SYS_TCS_DOMAIN_PD_SYS",
        "SYS_TCS_DOMAIN_PD_COM",
        "SYS_TCS_DOMAIN_PD_MEM",
        "SYS_TCS_DOMAIN_PD_TMR",
        "SYS_TCS_DOMAIN_PD_PER",
        "SYS_TCS_DOMAIN_PD_RAD",
        "SYS_TCS_DOMAIN_PD_SYN",
        "SYS_TCS_DOMAIN_NA"
    };

    bsp_otp_init();
    bsp_otp_mode_set(BSP_OTP_MODE_READ);
    bsp_tcs_get_trim_values_from_cs();
    current_tcs = &shared_tcs;
    for (i = 0; i < sizeof(based_on_tcs_attributes) / sizeof(based_on_tcs_attributes[0]); i++)
    {
        if (SYS_TCS.tcs_attributes[i].size > 0)
        {
            INFO_PRINTF("Group ID = %x, TYPE = %s, domain = %s, RETAINED %ud\r\n",
                        SYS_TCS.tcs_attributes[i].value_gid,
                        tcs_type[SYS_TCS.tcs_attributes[i].value_type],
                        tcs_domain[SYS_TCS.tcs_attributes[i].value_domain],
                        SYS_TCS.tcs_attributes[i].is_retained);
            if (SYS_TCS.tcs_attributes[i].value_type == BSP_TCS_TYPE_REG_PAIR)
            {
                for (e = 0; e < SYS_TCS.tcs_attributes[i].size; e += 2)
                {
                    INFO_PRINTF("%08lx - %08lx",
                                SYS_TCS.tcs_data[SYS_TCS.tcs_attributes[i].start + e],
                                SYS_TCS.tcs_data[SYS_TCS.tcs_attributes[i].start + e + 1]);
                    INFO_PRINTF(" : matched %d(%lx)\r\n",
                                *(volatile uint32_t *) SYS_TCS.tcs_data[SYS_TCS.tcs_attributes[i].start + e] ==
                                SYS_TCS.tcs_data[SYS_TCS.tcs_attributes[i].start + e + 1],
                                *(volatile uint32_t *) SYS_TCS.tcs_data[SYS_TCS.tcs_attributes[i].start + e]);
                }
            }
            else
            {
                for (e = 0; e < SYS_TCS.tcs_attributes[i].size; e++)
                {
                    INFO_PRINTF("%08lx\r\n", SYS_TCS.tcs_data[SYS_TCS.tcs_attributes[i].start + e]);
                }
            }
        }
    }

    INFO_PRINTF("\r\n - INFO \r\n");
    bsp_tcs_get_item_in_otp_cs(XTAL_REG, &dest, &word_size);
    INFO_PRINTF("XTAL40M_CTRL_REG(0x400c0204) = %lx\r\n", dest);
    bsp_tcs_get_otp_size(&size, XTAL_REG, &item_count);
    INFO_PRINTF("OTP Start Address: 0x400f2100, top =%x(%d), otp size = %x(%d), \r\n", (OTP_CS_ADDRESS + size) / 4,
                (OTP_CS_ADDRESS + size) / 4, size / 4, size / 4);

    INFO_PRINTF("\r\n - RAW DATA \r\n");
    for (i = 0; i < (uint32_t) (size / 4 + 1); i++)
    {
        INFO_PRINTF("%08lx, ", *(volatile uint32_t *) (MEMORY_OTP_BASE + OTP_CS_ADDRESS + i * 4));
        if ((i % 4 == 3) && (i != 0))
        {
            INFO_PRINTF("\r\n");
        }
    }

    INFO_PRINTF("\r\n");
}

#endif

bool bsp_tcs_otp_read_xtal (uint32_t * dest)
{
    return bsp_tcs_read_item(XTAL_REG, dest);
}

bool bsp_tcs_otp_write_xtal (uint32_t * dest, check_option_t check_option)
{
    *dest = ((*dest & 0xff0000) | 0x76f);

    return bsp_tcs_write_item(XTAL_REG, dest, 1, check_option);
}

bool bsp_tcs_otp_read_mac (uint32_t * mac)
{
    return bsp_tcs_read_item(BSP_TCS_GROUP_MAC_ADDR | (2 << 8) | (CS_SDK_VAL), mac);
}

bool bsp_tcs_otp_write_mac (uint32_t * mac, check_option_t check_option)
{
    return bsp_tcs_write_item(BSP_TCS_GROUP_MAC_ADDR | (2 << 8) | (CS_SDK_VAL), mac, 2, check_option);
}

uint16_t bsp_tcs_otp_mac_cnt (void)
{
    uint16_t otp_size = 0;
    uint16_t item_write_count;

    bsp_tcs_get_otp_size(&otp_size, BSP_TCS_GROUP_MAC_ADDR | (2 << 8) | (CS_SDK_VAL), &item_write_count);

    return item_write_count;
}

uint32_t bsp_tcs_read_timestamp (void)
{
    uint8_t    size;
    uint32_t * cs_timestamp_ptr = NULL;

    bsp_tcs_get_custom_values(BSP_TCS_GROUP_PROD_INFO, &cs_timestamp_ptr, &size);
    if (size == 0)
    {
        return 0;
    }

    return cs_timestamp_ptr[1];
}

uint32_t bsp_tcs_read_program_version (void)
{
    uint8_t    size;
    uint32_t * cs_program_version_ptr = NULL;

    bsp_tcs_get_custom_values(BSP_TCS_GROUP_TESTPROGRAM_VERSION, &cs_program_version_ptr, &size);
    if (size == 0)
    {
        return 0;
    }

    return *cs_program_version_ptr;
}

uint32_t bsp_tcs_read_wafer (void)
{
    uint8_t    size;
    uint32_t * cs_wafer_ptr = NULL;
    bsp_tcs_get_custom_values(BSP_TCS_GROUP_PROD_WAFER, &cs_wafer_ptr, &size);
    if (size == 0)
    {
        return 0;
    }

    return *cs_wafer_ptr;
}

bool bsp_tcs_otp_add (uint32_t * dest, uint32_t word_size)
{
    uint16_t otp_size = 0;
    uint16_t item_write_count;
    uint32_t cs_start[2] = {CS_START_CMD, 0};
    bool     ret         = 0;

    if (!dest || (word_size == 0) || (word_size > 30))
    {
        return false;
    }

    bsp_otp_init();
    bsp_otp_mode_set(BSP_OTP_MODE_READ);
    bsp_tcs_get_otp_size(&otp_size, 0, &item_write_count);

    if (otp_size == 0)
    {
        t2_production_patch();
        bsp_otp_mode_set(BSP_OTP_MODE_PROG);

        /* First write - need to write start pattern */
        uint32_t write_offset = (OTP_CS_ADDRESS / 4);
        bsp_otp_prog(cs_start, write_offset, 1);
        bsp_otp_prog(dest, write_offset + 1, word_size);

        ret = true;
    }
    else if (otp_size < (OTP_CS_SIZE - (word_size * 4)))
    {
        t2_production_patch();
        bsp_otp_mode_set(BSP_OTP_MODE_PROG);

        uint32_t write_offset = (OTP_CS_ADDRESS / 4) + otp_size / 4;;
        bsp_otp_prog(dest, write_offset, word_size);
        ret = true;
    }
    else
    {
        INFO_PRINTF("[TCS] Over size otp \r\n");
        ret = false;
    }

    bsp_otp_mode_set(BSP_OTP_MODE_READ);
    bsp_otp_close();

    return ret;
}

void bsp_tcs_custom_values_system_cb (bsp_tcs_gid_t gid, void * user_data, uint32_t * val, uint8_t len)
{
    FSP_PARAMETER_NOT_USED(gid);
    FSP_PARAMETER_NOT_USED(user_data);
    FSP_PARAMETER_NOT_USED(val);
    FSP_PARAMETER_NOT_USED(len);
}
