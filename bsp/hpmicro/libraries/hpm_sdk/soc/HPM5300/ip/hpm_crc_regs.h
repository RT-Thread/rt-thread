/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_CRC_H
#define HPM_CRC_H

typedef struct {
    struct {
        __RW uint32_t PRE_SET;                 /* 0x0:  pre set for crc setting */
        __RW uint32_t CLR;                     /* 0x4: chn clear crc result and setting */
        __RW uint32_t POLY;                    /* 0x8: chn poly */
        __RW uint32_t INIT_DATA;               /* 0xC: chn init_data */
        __RW uint32_t XOROUT;                  /* 0x10: chn xorout */
        __RW uint32_t MISC_SETTING;            /* 0x14: chn misc_setting */
        __RW uint32_t DATA;                    /* 0x18: chn data */
        __RW uint32_t RESULT;                  /* 0x1C: chn result */
        __R  uint8_t  RESERVED0[32];           /* 0x20 - 0x3F: Reserved */
    } CHN[8];
} CRC_Type;


/* Bitfield definition for register of struct array CHN: PRE_SET */
/*
 * PRE_SET (RW)
 *
 * 0: no pre set
 * 1: CRC32
 * 2: CRC32-AUTOSAR
 * 3: CRC16-CCITT
 * 4: CRC16-XMODEM
 * 5: CRC16-MODBUS
 * 1: CRC32
 * 2: CRC32-autosar
 * 3: CRC16-ccitt
 * 4: CRC16-xmodem
 * 5: CRC16-modbus
 * 6: crc16_dnp
 * 7: crc16_x25
 * 8: crc16_usb
 * 9: crc16_maxim
 * 10: crc16_ibm
 * 11: crc8_maxim
 * 12: crc8_rohc
 * 13: crc8_itu
 * 14: crc8
 * 15: crc5_usb
 */
#define CRC_CHN_PRE_SET_PRE_SET_MASK (0xFFU)
#define CRC_CHN_PRE_SET_PRE_SET_SHIFT (0U)
#define CRC_CHN_PRE_SET_PRE_SET_SET(x) (((uint32_t)(x) << CRC_CHN_PRE_SET_PRE_SET_SHIFT) & CRC_CHN_PRE_SET_PRE_SET_MASK)
#define CRC_CHN_PRE_SET_PRE_SET_GET(x) (((uint32_t)(x) & CRC_CHN_PRE_SET_PRE_SET_MASK) >> CRC_CHN_PRE_SET_PRE_SET_SHIFT)

/* Bitfield definition for register of struct array CHN: CLR */
/*
 * CLR (RW)
 *
 * write 1 to clr crc setting and result for its channel.
 * always read 0.
 */
#define CRC_CHN_CLR_CLR_MASK (0x1U)
#define CRC_CHN_CLR_CLR_SHIFT (0U)
#define CRC_CHN_CLR_CLR_SET(x) (((uint32_t)(x) << CRC_CHN_CLR_CLR_SHIFT) & CRC_CHN_CLR_CLR_MASK)
#define CRC_CHN_CLR_CLR_GET(x) (((uint32_t)(x) & CRC_CHN_CLR_CLR_MASK) >> CRC_CHN_CLR_CLR_SHIFT)

/* Bitfield definition for register of struct array CHN: POLY */
/*
 * POLY (RW)
 *
 * poly setting
 */
#define CRC_CHN_POLY_POLY_MASK (0xFFFFFFFFUL)
#define CRC_CHN_POLY_POLY_SHIFT (0U)
#define CRC_CHN_POLY_POLY_SET(x) (((uint32_t)(x) << CRC_CHN_POLY_POLY_SHIFT) & CRC_CHN_POLY_POLY_MASK)
#define CRC_CHN_POLY_POLY_GET(x) (((uint32_t)(x) & CRC_CHN_POLY_POLY_MASK) >> CRC_CHN_POLY_POLY_SHIFT)

/* Bitfield definition for register of struct array CHN: INIT_DATA */
/*
 * INIT_DATA (RW)
 *
 * initial data of CRC
 */
#define CRC_CHN_INIT_DATA_INIT_DATA_MASK (0xFFFFFFFFUL)
#define CRC_CHN_INIT_DATA_INIT_DATA_SHIFT (0U)
#define CRC_CHN_INIT_DATA_INIT_DATA_SET(x) (((uint32_t)(x) << CRC_CHN_INIT_DATA_INIT_DATA_SHIFT) & CRC_CHN_INIT_DATA_INIT_DATA_MASK)
#define CRC_CHN_INIT_DATA_INIT_DATA_GET(x) (((uint32_t)(x) & CRC_CHN_INIT_DATA_INIT_DATA_MASK) >> CRC_CHN_INIT_DATA_INIT_DATA_SHIFT)

/* Bitfield definition for register of struct array CHN: XOROUT */
/*
 * XOROUT (RW)
 *
 * XOR for CRC result
 */
#define CRC_CHN_XOROUT_XOROUT_MASK (0xFFFFFFFFUL)
#define CRC_CHN_XOROUT_XOROUT_SHIFT (0U)
#define CRC_CHN_XOROUT_XOROUT_SET(x) (((uint32_t)(x) << CRC_CHN_XOROUT_XOROUT_SHIFT) & CRC_CHN_XOROUT_XOROUT_MASK)
#define CRC_CHN_XOROUT_XOROUT_GET(x) (((uint32_t)(x) & CRC_CHN_XOROUT_XOROUT_MASK) >> CRC_CHN_XOROUT_XOROUT_SHIFT)

/* Bitfield definition for register of struct array CHN: MISC_SETTING */
/*
 * BYTE_REV (RW)
 *
 * 0: no wrap input byte order
 * 1: wrap input byte order
 */
#define CRC_CHN_MISC_SETTING_BYTE_REV_MASK (0x1000000UL)
#define CRC_CHN_MISC_SETTING_BYTE_REV_SHIFT (24U)
#define CRC_CHN_MISC_SETTING_BYTE_REV_SET(x) (((uint32_t)(x) << CRC_CHN_MISC_SETTING_BYTE_REV_SHIFT) & CRC_CHN_MISC_SETTING_BYTE_REV_MASK)
#define CRC_CHN_MISC_SETTING_BYTE_REV_GET(x) (((uint32_t)(x) & CRC_CHN_MISC_SETTING_BYTE_REV_MASK) >> CRC_CHN_MISC_SETTING_BYTE_REV_SHIFT)

/*
 * REV_OUT (RW)
 *
 * 0: no wrap output bit order
 * 1: wrap output bit order
 */
#define CRC_CHN_MISC_SETTING_REV_OUT_MASK (0x10000UL)
#define CRC_CHN_MISC_SETTING_REV_OUT_SHIFT (16U)
#define CRC_CHN_MISC_SETTING_REV_OUT_SET(x) (((uint32_t)(x) << CRC_CHN_MISC_SETTING_REV_OUT_SHIFT) & CRC_CHN_MISC_SETTING_REV_OUT_MASK)
#define CRC_CHN_MISC_SETTING_REV_OUT_GET(x) (((uint32_t)(x) & CRC_CHN_MISC_SETTING_REV_OUT_MASK) >> CRC_CHN_MISC_SETTING_REV_OUT_SHIFT)

/*
 * REV_IN (RW)
 *
 * 0: no wrap input bit order
 * 1: wrap input bit order
 */
#define CRC_CHN_MISC_SETTING_REV_IN_MASK (0x100U)
#define CRC_CHN_MISC_SETTING_REV_IN_SHIFT (8U)
#define CRC_CHN_MISC_SETTING_REV_IN_SET(x) (((uint32_t)(x) << CRC_CHN_MISC_SETTING_REV_IN_SHIFT) & CRC_CHN_MISC_SETTING_REV_IN_MASK)
#define CRC_CHN_MISC_SETTING_REV_IN_GET(x) (((uint32_t)(x) & CRC_CHN_MISC_SETTING_REV_IN_MASK) >> CRC_CHN_MISC_SETTING_REV_IN_SHIFT)

/*
 * POLY_WIDTH (RW)
 *
 * crc data length
 */
#define CRC_CHN_MISC_SETTING_POLY_WIDTH_MASK (0x3FU)
#define CRC_CHN_MISC_SETTING_POLY_WIDTH_SHIFT (0U)
#define CRC_CHN_MISC_SETTING_POLY_WIDTH_SET(x) (((uint32_t)(x) << CRC_CHN_MISC_SETTING_POLY_WIDTH_SHIFT) & CRC_CHN_MISC_SETTING_POLY_WIDTH_MASK)
#define CRC_CHN_MISC_SETTING_POLY_WIDTH_GET(x) (((uint32_t)(x) & CRC_CHN_MISC_SETTING_POLY_WIDTH_MASK) >> CRC_CHN_MISC_SETTING_POLY_WIDTH_SHIFT)

/* Bitfield definition for register of struct array CHN: DATA */
/*
 * DATA (RW)
 *
 * data for crc
 */
#define CRC_CHN_DATA_DATA_MASK (0xFFFFFFFFUL)
#define CRC_CHN_DATA_DATA_SHIFT (0U)
#define CRC_CHN_DATA_DATA_SET(x) (((uint32_t)(x) << CRC_CHN_DATA_DATA_SHIFT) & CRC_CHN_DATA_DATA_MASK)
#define CRC_CHN_DATA_DATA_GET(x) (((uint32_t)(x) & CRC_CHN_DATA_DATA_MASK) >> CRC_CHN_DATA_DATA_SHIFT)

/* Bitfield definition for register of struct array CHN: RESULT */
/*
 * RESULT (RW)
 *
 * crc result
 */
#define CRC_CHN_RESULT_RESULT_MASK (0xFFFFFFFFUL)
#define CRC_CHN_RESULT_RESULT_SHIFT (0U)
#define CRC_CHN_RESULT_RESULT_SET(x) (((uint32_t)(x) << CRC_CHN_RESULT_RESULT_SHIFT) & CRC_CHN_RESULT_RESULT_MASK)
#define CRC_CHN_RESULT_RESULT_GET(x) (((uint32_t)(x) & CRC_CHN_RESULT_RESULT_MASK) >> CRC_CHN_RESULT_RESULT_SHIFT)



/* CHN register group index macro definition */
#define CRC_CHN_0 (0UL)
#define CRC_CHN_1 (1UL)
#define CRC_CHN_2 (2UL)
#define CRC_CHN_3 (3UL)
#define CRC_CHN_4 (4UL)
#define CRC_CHN_5 (5UL)
#define CRC_CHN_6 (6UL)
#define CRC_CHN_7 (7UL)


#endif /* HPM_CRC_H */
