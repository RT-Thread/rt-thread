/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_CRC_DRV_H
#define HPM_CRC_DRV_H

/**
 * @brief CRC APIs
 * @defgroup crc_interface CRC driver APIs
 * @ingroup crc_interfaces
 * @{
 */


#include "hpm_common.h"
#include "hpm_crc_regs.h"

/**
 * @brief CRC preset definitions
 */
typedef enum crc_preset_enum {
    crc_preset_none = 0,
    crc_preset_crc32,         /*!< Poly: 0x04C11DB7, Init: 0xFFFFFFFF, Refin:  True, Refout:  True, Xorout: 0xFFFFFFFF */
    crc_preset_crc32_autosar, /*!< Poly: 0xF4ACFB13, Init: 0xFFFFFFFF, Refin:  True, Refout:  True, Xorout: 0xFFFFFFFF */
    crc_preset_crc16_ccitt,   /*!< Poly:     0x1021, Init:     0x0000, Refin:  True, Refout:  True, Xorout:     0x0000 */
    crc_preset_crc16_xmodem,  /*!< Poly:     0x1021, Init:     0x0000, Refin: False, Refout: False, Xorout:     0x0000 */
    crc_preset_crc16_modbus,  /*!< Poly:     0x8005, Init:     0xFFFF, Refin:  True, Refout:  True, Xorout:     0x0000 */
    crc_preset_crc16_dnp,     /*!< Poly:     0x3D65, Init:     0x0000, Refin:  True, Refout:  True, Xorout:     0xFFFF */
    crc_preset_crc16_x25,     /*!< Poly:     0x1021, Init:     0xFFFF, Refin:  True, Refout:  True, Xorout:     0xFFFF */
    crc_preset_crc16_usb,     /*!< Poly:     0x8005, Init:     0xFFFF, Refin:  True, Refout:  True, Xorout:     0xFFFF */
    crc_preset_crc16_maxim,   /*!< Poly:     0x8005, Init:     0x0000, Refin:  True, Refout:  True, Xorout:     0xFFFF */
    crc_preset_crc16_ibm,     /*!< Poly:     0x8005, Init:     0x0000, Refin:  True, Refout:  True, Xorout:     0x0000 */
    crc_preset_crc8_maxim,    /*!< Poly:       0x31, Init:       0x00, Refin:  True, Refout:  True, Xorout:       0x00 */
    crc_preset_crc8_rohc,     /*!< Poly:       0x07, Init:       0xFF, Refin:  True, Refout:  True, Xorout:       0x00 */
    crc_preset_crc8_itu,      /*!< Poly:       0x07, Init:       0x00, Refin: False, Refout: False, Xorout:       0x55 */
    crc_preset_crc8,          /*!< Poly:       0x07, Init:       0x00, Refin: False, Refout: False, Xorout:       0x00 */
    crc_preset_crc5_usb,      /*!< Poly:       0x05, Init:       0x1F, Refin:  True, Refout:  True, Xorout:       0x1F */
} crc_preset_t;

/**
 * @brief CRC Refin definitions.
 */
typedef enum crc_refin_enum {
    crc_refin_false = 0, /*!< Do not manipulate input data stream. */
    crc_refin_true = 1,  /*!< Reflect each byte in the input stream bitwise. */
} crc_refin_t;

/**
 * @brief CRC Refout definitions.
 */
typedef enum crc_refout_enum {
    crc_refout_false = 0, /*!< Do not manipulate output data stream. */
    crc_refout_true = 1,  /*!< Reflect each byte in the output stream bitwise. */
} crc_refout_t;

/**
 * @brief crc input data stream byte order definitions.
 */
typedef enum crc_in_byte_order_enum {
    crc_in_byte_order_lsb = 0, /*!< Byte order of the CRC DATA LS Byte first. */
    crc_in_byte_order_msb = 1,  /*!< Byte order of the CRC DATA MS Byte first. */
} crc_in_byte_order_t;

#define CRC_POLY_WIDTH_4 (4U)
#define CRC_POLY_WIDTH_5 (5U)
#define CRC_POLY_WIDTH_6 (6U)
#define CRC_POLY_WIDTH_7 (7U)
#define CRC_POLY_WIDTH_8 (8U)
#define CRC_POLY_WIDTH_16 (16U)
#define CRC_POLY_WIDTH_24 (24U)
#define CRC_POLY_WIDTH_32 (32U)

/**
 * @brief Channel config
 */
typedef struct crc_channel_config {
    crc_preset_t preset;               /*!< Preset CRC. See "crc_preset_t". */
    uint32_t init;                     /*!< Initial value for CRC. */
    uint32_t poly;                     /*!< Poly for CRC. */
    uint32_t poly_width;               /*!< CRC poly width. See "CRC_POLY_WIDTH_x". */
    crc_in_byte_order_t in_byte_order; /*!< CRC intput byte order. See "crc_in_byte_order_t". */
    crc_refout_t refout;               /*!< CRC reflect output. See "crc_refout_t". */
    crc_refin_t refin;                 /*!< CRC reflect iutput. See "crc_refin_t". */
    uint32_t xorout;                   /*!< XOR mask for CRC result (for no mask, should be 0). */
} crc_channel_config_t;

#define CRC_REG_WRITE8(addr, data)\
{\
    uint32_t addr32 = (uint32_t)(addr);\
    (*(volatile uint8_t *)(addr32) = (data));\
}

#define CRC_REG_WRITE16(addr, data)\
{\
    uint32_t addr32 = (uint32_t)(addr);\
    (*(volatile uint16_t *)(addr32) = (data));\
}

#define CRC_REG_WRITE32(addr, data)\
{\
    uint32_t addr32 = (uint32_t)(addr);\
    (*(volatile uint32_t *)(addr32) = (data));\
}

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset CRC channel
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index Index of the channel to be reset
 *
 */
static inline void crc_reset(CRC_Type *ptr, uint32_t ch_index)
{
    ptr->CHN[ch_index].CLR |= CRC_CHN_CLR_CLR_MASK;
}

/**
 * @brief Get default channel config
 *
 * @param[in] ptr CRC base address
 * @param[in] cfg Channel config
 */
void crc_get_default_channel_config(crc_channel_config_t *cfg);

/**
 * @brief Setup CRC channel
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index Target channel index to be configured
 * @param[in] cfg Channel config
 *
 * @return  status_success if everything is okay
 */
hpm_stat_t crc_setup_channel_config(CRC_Type *ptr, uint32_t ch_index,
                            crc_channel_config_t *cfg);

/**
 * @brief Calculate one byte data crc
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index CRC channel index
 * @param[in] data Data that to be calculate
 */
static inline void crc_calc_byte(CRC_Type *ptr, uint32_t ch_index, uint8_t data)
{
    CRC_REG_WRITE8(&ptr->CHN[ch_index].DATA, data);
}

/**
 * @brief Calculate length bytes data block crc
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index CRC channel index
 * @param[in] pbuffer Data to be calculate buffer
 * @param[in] length Number of pbuffer, unit is byte
 */
void crc_calc_block_bytes(CRC_Type *ptr, uint32_t ch_index, uint8_t *pbuffer, uint32_t length);

/**
 * @brief Calculate half-word data crc
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index CRC channel index
 * @param[in] data Data that to be calculate
 */
static inline void crc_calc_half_word(CRC_Type *ptr, uint32_t ch_index, uint16_t data)
{
    CRC_REG_WRITE16(&ptr->CHN[ch_index].DATA, data);
}

/**
 * @brief Calculate length half-words data block crc
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index CRC channel index
 * @param[in] pbuffer Data to be calculate buffer
 * @param[in] length Number of pbuffer, unit is half word(2 bytes)
 */
void crc_calc_block_half_words(CRC_Type *ptr, uint32_t ch_index, uint16_t *pbuffer, uint32_t length);

/**
 * @brief Calculate word data crc
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index CRC channel index
 * @param[in] data Data that to be calculate
 */
static inline void crc_calc_word(CRC_Type *ptr, uint32_t ch_index, uint32_t data)
{
    CRC_REG_WRITE32(&ptr->CHN[ch_index].DATA, data);
}

/**
 * @brief Calculate length words data block crc
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index CRC channel index
 * @param[in] pbuffer Data to be calculate buffer
 * @param[in] length Number of pbuffer, unit is word(4 bytes)
 */
void crc_calc_block_words(CRC_Type *ptr, uint32_t ch_index, uint32_t *pbuffer, uint32_t length);

/**
 * @brief Fast calculate length bytes large data block crc
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index CRC channel index
 * @param[in] pbuffer Data to be calculate buffer
 * @param[in] length Number of pbuffer, unit is byte
 */
void crc_calc_large_block_fast(CRC_Type *ptr, uint32_t ch_index, uint8_t *pbuffer, uint32_t length);

/**
 * @brief   Get CRC result
 *
 * @param[in] ptr CRC base address
 * @param[in] ch_index Index of the channel to be get
 * @return CRC result
 */
static inline uint32_t crc_get_result(CRC_Type *ptr, uint32_t ch_index)
{
    return ptr->CHN[ch_index].RESULT;
}
#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HPM_CRC_DRV_H */
