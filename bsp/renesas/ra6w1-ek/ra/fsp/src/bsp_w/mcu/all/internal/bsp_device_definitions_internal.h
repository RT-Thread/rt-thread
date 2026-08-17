/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_DEVICE_DEFINITIONS_INTERNAL_H
#define BSP_DEVICE_DEFINITIONS_INTERNAL_H

/*
 * All device information attributes are OR'ed in a 32-bit value, as indicated below:
 *
 *  31               21 20                      17 16       13      12      11       9 8          4 3          0
 *  +------------------+--------------------------+-----------+------------+----------+------------+-----------+
 *  |                  |                          |           |            |              Version              |
 *  |------------------|--------------------------|-----------|------------+----------+------------+-----------+
 *  |      Family      |         Chip ID          |  Variant  |    FPGA    |   REV_x  |    SWC_x   |  STEP_x   |
 *  |------------------+--------------------------+-----------+------------+----------+------------+-----------|
 *  |                  |     680 69X 59X 70X      |           |            |          |            |           |
 *  |------------------+--------------------------+-----------+------------+----------+------------+-----------|
 *  | 00000000000: INV | 0000: INV INV  INV  INV  | 0000: INV | 0: Silicon | 000: INV | 00000: INV | 0000: INV |
 *  | 00000000001: 680 | 0001: 680 3080 3107 2634 | 0001: 0   | 1: FPGA    | 001: D/C | 00001: D/C | 0001: D/C |
 *  | 00000000010: 69x | 0010: INV 2522 2798 INV  | 0010: 1   |            | 010: A   | 00010: 0   | 0010: A   |
 *  | 00000000011: 59x |                          | 0011: 2   |            | 011: B   | 00011: 1   | 0011: B   |
 *  | 00000000100: 70x |                          | 0100: 3   |            | 100: C   | 00100: 2   | 0100: C   |
 *  | 00000001000: 310x|                          | 0101: 4   |            | 101: D   | 00101: 3   | 0101: D   |
 *  |                  |                          | 0111: 5   |            |          | 00111: 4   | 0111: E   |
 *  |                  |                          | 1000: 6   |            |          | 01000: 5   | 1000: F   |
 *  |                  |                          | 1001: 7   |            |          | 01001: 6   | 1001: G   |
 *  |                  |                          | 1010: 8   |            |          | 01010: 7   | 1010: H   |
 *  |                  |                          | 1011: 9   |            |          | 01011: 8   |           |
 *  |                  |                          |           |            |          | 01100: 9   |           |
 *  |                  |                          |           |            |          | 01101: 11  |           |
 *  |                  |                          |           |            |          | 01110: 12  |           |
 *  |                  |                          |           |            |          | 01111: 13  |           |
 *  |                  |                          |           |            |          | 10000: 14  |           |
 *  |                  |                          |           |            |          | 10001: 15  |           |
 *  +------------------+--------------------------+-----------+------------+----------+------------+-----------+
 *
 *  INV: Invalid setting. None of the attributes should be 0, apart from the FPGA.
 *  D/C: Don't care
 *  RES: Reserved
 */

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Make numerical value */
#define _DEVICE_MK_NUM_VAL(field, value)    (((value) << _DEVICE_ ## field ## _POS) & _DEVICE_ ## field ## _MASK)

/* Device family definitions */
#define _DEVICE_FAMILY_MASK       0xFFE00000 // 11 bits length
#define _DEVICE_FAMILY_POS        21
#define _DEVICE_FAMILY_680        1
#define _DEVICE_FAMILY_690        2
#define _DEVICE_FAMILY_590        3
#define _DEVICE_FAMILY_700        4
#define _DEVICE_FAMILY_3100       5
#define _DEVICE_FAMILY_W300       6
#define _DEVICE_FAMILY_3333       7
#define _DEVICE_MK_FAMILY(x)    _DEVICE_MK_NUM_VAL(FAMILY, _DEVICE_FAMILY_ ## x)

/* Device Chip ID definitions */
#define _DEVICE_CHIP_ID_MASK      0x001E0000 // 4 bits length
#define _DEVICE_CHIP_ID_POS       17
#define _DEVICE_CHIP_ID_680       1
#define _DEVICE_CHIP_ID_3080      1
#define _DEVICE_CHIP_ID_2522      2
#define _DEVICE_CHIP_ID_2634      1
#define _DEVICE_CHIP_ID_3107      1
#define _DEVICE_CHIP_ID_2798      2
#define _DEVICE_CHIP_ID_3108      1
#define _DEVICE_CHIP_ID_3333      1
#define _DEVICE_MK_CHIP_ID(x)    _DEVICE_MK_NUM_VAL(CHIP_ID, _DEVICE_CHIP_ID_ ## x)

/* Device variants definitions */
#define _DEVICE_VARIANT_MASK      0x0001E000 // 4 bits length
#define _DEVICE_VARIANT_POS       13
#define _DEVICE_VARIANT_XX0       1
#define _DEVICE_VARIANT_XX1       2
#define _DEVICE_VARIANT_XX2       3
#define _DEVICE_VARIANT_XX3       4
#define _DEVICE_VARIANT_XX4       5
#define _DEVICE_VARIANT_XX5       6
#define _DEVICE_VARIANT_XX6       7
#define _DEVICE_VARIANT_XX7       8
#define _DEVICE_VARIANT_XX8       9
#define _DEVICE_VARIANT_XX9       10
#define _DEVICE_MK_VARIANT(x)              _DEVICE_MK_NUM_VAL(VARIANT, _DEVICE_VARIANT_XX ## x)
#define _DEVICE_MK_VARIANT_NUMERICAL(n)    _DEVICE_MK_NUM_VAL(VARIANT, _DEVICE_VARIANT_XX0 + (n))

/* FPGA definitions */
#define _DEVICE_FPGA_MASK         0x00001000 // 1 bit length
#define _DEVICE_FPGA_POS          12

#define _DEVICE_FPGA_VER_MASK     0x00000FFF // 12 bits length
#define _DEVICE_FPGA_VER_POS      0
#define _DEVICE_MK_FPGA_VER(n)    _DEVICE_MK_NUM_VAL(FPGA_VER, (n))

/* Device stepping major sub-revisions (I) */
#define _DEVICE_REV_MASK          0x00000E00 // 3 bits length
#define _DEVICE_REV_POS           9
#define _DEVICE_REV_DONT_CARE     1
#define _DEVICE_REV_A             2
#define _DEVICE_REV_B             3
#define _DEVICE_REV_C             4
#define _DEVICE_REV_D             5
#define _DEVICE_MK_REV(x)              _DEVICE_MK_NUM_VAL(REV, _DEVICE_REV_ ## x)
#define _DEVICE_MK_REV_NUMERICAL(n)    _DEVICE_MK_NUM_VAL(REV, ((_DEVICE_REV_DONT_CARE) + (n) + 1))

/* Device SW Compatibility code (I) */
#define _DEVICE_SWC_MASK          0x000001F0 // 5 bits length
#define _DEVICE_SWC_POS           4
#define _DEVICE_SWC_DONT_CARE     1
#define _DEVICE_SWC_0             2
#define _DEVICE_SWC_1             3
#define _DEVICE_SWC_2             4
#define _DEVICE_SWC_3             5
#define _DEVICE_SWC_4             6
#define _DEVICE_SWC_5             7
#define _DEVICE_SWC_6             8
#define _DEVICE_SWC_7             9
#define _DEVICE_SWC_8             10
#define _DEVICE_SWC_9             11
#define _DEVICE_SWC_10            12
#define _DEVICE_SWC_11            13
#define _DEVICE_SWC_12            14
#define _DEVICE_SWC_13            15
#define _DEVICE_SWC_14            16
#define _DEVICE_SWC_15            17
#define _DEVICE_MK_SWC(n)              _DEVICE_MK_NUM_VAL(SWC, _DEVICE_SWC_ ## n)
#define _DEVICE_MK_SWC_NUMERICAL(n)    _DEVICE_MK_NUM_VAL(SWC, ((_DEVICE_SWC_DONT_CARE) + (n) + 1))

/* Device stepping minor subrevisions (I) */
#define _DEVICE_STEP_MASK         0x0000000F // 4 bits length
#define _DEVICE_STEP_POS          0
#define _DEVICE_STEP_DONT_CARE    1
#define _DEVICE_STEP_A            2
#define _DEVICE_STEP_B            3
#define _DEVICE_STEP_C            4
#define _DEVICE_STEP_D            5
#define _DEVICE_STEP_E            6
#define _DEVICE_STEP_F            7
#define _DEVICE_STEP_G            8
#define _DEVICE_STEP_H            9
#define _DEVICE_MK_STEP(y)              _DEVICE_MK_NUM_VAL(STEP, _DEVICE_STEP_ ## y)
#define _DEVICE_MK_STEP_NUMERICAL(n)    _DEVICE_MK_NUM_VAL(STEP, ((_DEVICE_STEP_DONT_CARE) + (n) + 1))

#define _DEVICE_MK_VER(x, n, y)         (_DEVICE_MK_REV(x) | _DEVICE_MK_SWC(n) | _DEVICE_MK_STEP(y))

#define _DEVICE_MASK             (_DEVICE_FAMILY_MASK | _DEVICE_CHIP_ID_MASK | \
                                  _DEVICE_VARIANT_MASK | _DEVICE_FPGA_MASK)

/* Public definitions */

/* RRQ431xx Device Variants */
#define RRQ43103                 (_DEVICE_MK_FAMILY(3100) | _DEVICE_MK_VARIANT(3))
#define RRQ43107                 (_DEVICE_MK_FAMILY(3100) | _DEVICE_MK_VARIANT(7))
#define RRQ43108                 (_DEVICE_MK_FAMILY(3100) | _DEVICE_MK_VARIANT(8))

/* FPGA Device */
#define D3108                    (_DEVICE_MK_FAMILY(3100) | DEVICE_CHIP_ID_3108 | \
                                  _DEVICE_FPGA_MASK | DEVICE_REV_A)

/* Family Wildcard */
#define RRQ431XX                 (_DEVICE_MK_FAMILY(3100))

/* RA6B2XX Device Variants */
/* Family Wildcard */
#define RA6B2XX                  (_DEVICE_MK_FAMILY(3333))


/* RA6W3xx Device Variants */
/* Family Wildcard */
#define RA6W3XX                  (_DEVICE_MK_FAMILY(W300))

/* DA1469X Device Variants */
#define DA14691                  (_DEVICE_MK_FAMILY(690) | _DEVICE_MK_VARIANT(1))
#define DA14693                  (_DEVICE_MK_FAMILY(690) | _DEVICE_MK_VARIANT(3))
#define DA14695                  (_DEVICE_MK_FAMILY(690) | _DEVICE_MK_VARIANT(5))
#define DA14697                  (_DEVICE_MK_FAMILY(690) | _DEVICE_MK_VARIANT(7))
#define DA14699                  (_DEVICE_MK_FAMILY(690) | _DEVICE_MK_VARIANT(9))

/* FPGA Device */
#define D2522                    (_DEVICE_MK_FAMILY(690) | DEVICE_CHIP_ID_2522 | \
                                  _DEVICE_FPGA_MASK | DEVICE_REV_A)

/* Family Wildcard */
#define DA1469X                  (_DEVICE_MK_FAMILY(690))

/* Device Chip ID */
#define DEVICE_CHIP_ID_3108      (_DEVICE_MK_CHIP_ID(3108))
#define DEVICE_CHIP_ID_3080      (_DEVICE_MK_CHIP_ID(3080))
#define DEVICE_CHIP_ID_2522      (_DEVICE_MK_CHIP_ID(2522))
#define DEVICE_CHIP_ID_3333      (_DEVICE_MK_CHIP_ID(3333))

/* Device Revision */
#define DEVICE_REV_A             (_DEVICE_MK_REV(A))
#define DEVICE_REV_B             (_DEVICE_MK_REV(B))

/* Define SWC */
#define DEVICE_SWC_DONT_CARE     (_DEVICE_MK_SWC(DONT_CARE))
#define DEVICE_SWC_0             (_DEVICE_MK_SWC(0))
#define DEVICE_SWC_1             (_DEVICE_MK_SWC(1))
#define DEVICE_SWC_2             (_DEVICE_MK_SWC(2))
#define DEVICE_SWC_3             (_DEVICE_MK_SWC(3))
#define DEVICE_SWC_4             (_DEVICE_MK_SWC(4))
#define DEVICE_SWC_5             (_DEVICE_MK_SWC(5))
#define DEVICE_SWC_6             (_DEVICE_MK_SWC(6))
#define DEVICE_SWC_7             (_DEVICE_MK_SWC(7))
#define DEVICE_SWC_8             (_DEVICE_MK_SWC(8))
#define DEVICE_SWC_9             (_DEVICE_MK_SWC(9))
#define DEVICE_SWC_10            (_DEVICE_MK_SWC(10))
#define DEVICE_SWC_11            (_DEVICE_MK_SWC(11))
#define DEVICE_SWC_12            (_DEVICE_MK_SWC(12))
#define DEVICE_SWC_13            (_DEVICE_MK_SWC(13))
#define DEVICE_SWC_14            (_DEVICE_MK_SWC(14))
#define DEVICE_SWC_15            (_DEVICE_MK_SWC(15))

/* Device Step */
#define DEVICE_STEP_DONT_CARE    (_DEVICE_MK_STEP(DONT_CARE))
#define DEVICE_STEP_A            (_DEVICE_MK_STEP(A))
#define DEVICE_STEP_B            (_DEVICE_MK_STEP(B))
#define DEVICE_STEP_C            (_DEVICE_MK_STEP(C))
#define DEVICE_STEP_D            (_DEVICE_MK_STEP(D))
#define DEVICE_STEP_E            (_DEVICE_MK_STEP(E))
#define DEVICE_STEP_F            (_DEVICE_MK_STEP(F))
#define DEVICE_STEP_G            (_DEVICE_MK_STEP(G))
#define DEVICE_STEP_H            (_DEVICE_MK_STEP(H))

/* Device Version */
#define DEVICE_VER_A0            (_DEVICE_MK_VER(A, 0, DONT_CARE))
#define DEVICE_VER_A1            (_DEVICE_MK_VER(A, 1, DONT_CARE))
#define DEVICE_VER_AA            (_DEVICE_MK_VER(A, DONT_CARE, A))
#define DEVICE_VER_AB            (_DEVICE_MK_VER(A, DONT_CARE, B))

/*
 * A generic FPGA check, available for any device family.
 */
#define DEVICE_FPGA              ((dg_configDEVICE & _DEVICE_FPGA_MASK) == _DEVICE_FPGA_MASK)

/*
 * Macros checking against specific device characteristics.
 * Examples:
 * #if (DEVICE_FAMILY == DA1468X)
 * #if (DEVICE_CHIP_ID == DEVICE_CHIP_ID_3080)
 * #if ((DEVICE_VARIANT == DA14695) || (DEVICE_VARIANT == DA14699))
 * #if (DEVICE_REVISION == DEVICE_REV_B)
 * #if ((DEVICE_VERSION == DEVICE_VER_AB) || (DEVICE_VERSION == DEVICE_VER_AE))
 */

/*
 * FIXME:
 * Unused macros copied from SDK10.
 * DEVICE_FAMILY commented-out because currently it has to be redefined in CMAC projects' CMakeLists
 */

// #define DEVICE_FAMILY            (dg_configDEVICE & _DEVICE_FAMILY_MASK)
#define DEVICE_CHIP_ID          (dg_configDEVICE & _DEVICE_CHIP_ID_MASK)
#define DEVICE_VARIANT          (dg_configDEVICE & (_DEVICE_FAMILY_MASK | _DEVICE_VARIANT_MASK))
#define DEVICE_REVISION         (dg_configDEVICE & _DEVICE_REV_MASK)
#define DEVICE_SWC              (dg_configDEVICE & _DEVICE_SWC_MASK)
#define DEVICE_STEP             (dg_configDEVICE & _DEVICE_STEP_MASK)
#define DEVICE_VERSION          (dg_configDEVICE & (_DEVICE_REV_MASK | _DEVICE_SWC_MASK | _DEVICE_STEP_MASK))

/*
 * Device information attributes masks
 */
#define DEVICE_FAMILY_MASK      (_DEVICE_FAMILY_MASK)
#define DEVICE_CHIP_ID_MASK     (_DEVICE_CHIP_ID_MASK)
#define DEVICE_VARIANT_MASK     (_DEVICE_VARIANT_MASK)
#define DEVICE_REVISION_MASK    (_DEVICE_REV_MASK)
#define DEVICE_SWC_MASK         (_DEVICE_SWC_MASK)
#define DEVICE_STEP_MASK        (_DEVICE_STEP_MASK)

/*
 * Use the next macros to get the minimum acceptable value of specific device information attribute
 */
#define DEVICE_INFO_ATTRIBUTE_MIN(mask)    (1 << __CLZ(__RBIT(mask)))
#define DEVICE_FAMILY_MIN       (1 << _DEVICE_FAMILY_POS)
#define DEVICE_CHIP_ID_MIN      (1 << _DEVICE_CHIP_ID_POS)
#define DEVICE_VARIANT_MIN      (1 << _DEVICE_VARIANT_POS)
#define DEVICE_REVISION_MIN     (1 << _DEVICE_REV_POS)
#define DEVICE_SWC_MIN          (1 << _DEVICE_SWC_POS)
#define DEVICE_STEP_MIN         (1 << _DEVICE_STEP_POS)

/*
 * Use the next macros to get the maximum acceptable value of specific device information attribute
 */
#define DEVICE_INFO_ATTRIBUTE_MAX(mask)    (mask)
#define DEVICE_FAMILY_MAX       _DEVICE_FAMILY_MASK
#define DEVICE_CHIP_ID_MAX      _DEVICE_CHIP_ID_MASK
#define DEVICE_VARIANT_MAX      _DEVICE_VARIANT_MASK
#define DEVICE_REVISION_MAX     _DEVICE_REV_MASK
#define DEVICE_SWC_MAX          _DEVICE_SWC_MASK
#define DEVICE_STEP_MAX         _DEVICE_STEP_MASK

/*
 * Use the next macros to convert (mask and shift) a specific device information attribute
 * extracted from the corresponding registers to bit-field.
 */

#define MAKE_DEVICE_FAMILY_ENCODING(family)      _DEVICE_MK_NUM_VAL(FAMILY, family)
#define MAKE_DEVICE_CHIP_ID_ENCODING(id)         _DEVICE_MK_NUM_VAL(CHIP_ID, id)
#define MAKE_DEVICE_VARIANT_ENCODING(variant)    _DEVICE_MK_VARIANT_NUMERICAL(variant)
#define MAKE_DEVICE_REVISION_ENCODING(rev)       _DEVICE_MK_REV_NUMERICAL(rev)
#define MAKE_DEVICE_SWC_ENCODING(swc)            _DEVICE_MK_SWC_NUMERICAL(swc)
#define MAKE_DEVICE_STEP_ENCODING(step)          _DEVICE_MK_STEP_NUMERICAL(step)

#define RRQ43103_3108_00    (RRQ43103 | _DEVICE_MK_CHIP_ID(3108) | DEVICE_VER_A0)
#define RRQ43107_3108_00    (RRQ43107 | _DEVICE_MK_CHIP_ID(3108) | DEVICE_VER_A0)
#define RRQ43108_3108_00    (RRQ43108 | _DEVICE_MK_CHIP_ID(3108) | DEVICE_VER_A0)

#define DA14691_2522_00     (DA14691 | _DEVICE_MK_CHIP_ID(2522) | _DEVICE_MK_VER(A, DONT_CARE, B))
#define DA14693_2522_00     (DA14693 | _DEVICE_MK_CHIP_ID(2522) | _DEVICE_MK_VER(A, DONT_CARE, B))
#define DA14695_2522_00     (DA14695 | _DEVICE_MK_CHIP_ID(2522) | _DEVICE_MK_VER(A, DONT_CARE, B))
#define DA14697_2522_00     (DA14697 | _DEVICE_MK_CHIP_ID(2522) | _DEVICE_MK_VER(A, DONT_CARE, B))
#define DA14699_2522_00     (DA14699 | _DEVICE_MK_CHIP_ID(2522) | _DEVICE_MK_VER(A, DONT_CARE, B))

#define DA14691_3080_00     (DA14691 | _DEVICE_MK_CHIP_ID(3080) | _DEVICE_MK_VER(A, DONT_CARE, A))
#define DA14693_3080_00     (DA14693 | _DEVICE_MK_CHIP_ID(3080) | _DEVICE_MK_VER(A, DONT_CARE, A))
#define DA14695_3080_00     (DA14695 | _DEVICE_MK_CHIP_ID(3080) | _DEVICE_MK_VER(A, DONT_CARE, A))
#define DA14697_3080_00     (DA14697 | _DEVICE_MK_CHIP_ID(3080) | _DEVICE_MK_VER(A, DONT_CARE, A))
#define DA14699_3080_00     (DA14699 | _DEVICE_MK_CHIP_ID(3080) | _DEVICE_MK_VER(A, DONT_CARE, A))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef union
{
    uint32_t value;

    struct
    {
        uint32_t step     :  4;
        uint32_t swc      :  5;
        uint32_t revision :  3;
        uint32_t is_fpga  :  1;
        uint32_t variant  :  4;
        uint32_t chip_id  :  4;
        uint32_t family   : 11;
    } bits;
} bsp_device_info_t;

#endif
