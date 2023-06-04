/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @defgroup BSP_IO BSP I/O access
 * @ingroup RENESAS_COMMON
 * @brief This module provides basic read/write access to port pins.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_IO_H
#define BSP_IO_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Private definition to set enumeration values. */
#define BSP_IO_PRV_PFS_PSEL_OFFSET    (24)
#define BSP_IO_PRV_8BIT_MASK          (0xFF)
#define BSP_IO_PWPR_B0WI_OFFSET       (7U)
#define BSP_IO_PWPR_PFSWE_OFFSET      (6U)
#define BSP_IO_PFS_PDR_OUTPUT         (4U)
#define BSP_IO_PRV_PIN_WRITE_MASK     (0xFFFE3FFE)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Levels that can be set and read for individual pins */
typedef enum e_bsp_io_level
{
    BSP_IO_LEVEL_LOW = 0,              ///< Low
    BSP_IO_LEVEL_HIGH                  ///< High
} bsp_io_level_t;

/** Direction of individual pins */
typedef enum e_bsp_io_dir
{
    BSP_IO_DIRECTION_INPUT = 0,        ///< Input
    BSP_IO_DIRECTION_OUTPUT            ///< Output
} bsp_io_direction_t;

/** Superset list of all possible IO ports. */
typedef enum e_bsp_io_port
{
    BSP_IO_PORT_00 = 0x0000,           ///< IO port 0
    BSP_IO_PORT_01 = 0x0100,           ///< IO port 1
    BSP_IO_PORT_02 = 0x0200,           ///< IO port 2
    BSP_IO_PORT_03 = 0x0300,           ///< IO port 3
    BSP_IO_PORT_04 = 0x0400,           ///< IO port 4
    BSP_IO_PORT_05 = 0x0500,           ///< IO port 5
    BSP_IO_PORT_06 = 0x0600,           ///< IO port 6
    BSP_IO_PORT_07 = 0x0700,           ///< IO port 7
    BSP_IO_PORT_08 = 0x0800,           ///< IO port 8
    BSP_IO_PORT_09 = 0x0900,           ///< IO port 9
    BSP_IO_PORT_10 = 0x0A00,           ///< IO port 10
    BSP_IO_PORT_11 = 0x0B00,           ///< IO port 11
    BSP_IO_PORT_12 = 0x0C00,           ///< IO port 12
    BSP_IO_PORT_13 = 0x0D00,           ///< IO port 13
    BSP_IO_PORT_14 = 0x0E00,           ///< IO port 14
} bsp_io_port_t;

/** Superset list of all possible IO port pins. */
typedef enum e_bsp_io_port_pin_t
{
    BSP_IO_PORT_00_PIN_00 = 0x0000,    ///< IO port 0 pin 0
    BSP_IO_PORT_00_PIN_01 = 0x0001,    ///< IO port 0 pin 1
    BSP_IO_PORT_00_PIN_02 = 0x0002,    ///< IO port 0 pin 2
    BSP_IO_PORT_00_PIN_03 = 0x0003,    ///< IO port 0 pin 3
    BSP_IO_PORT_00_PIN_04 = 0x0004,    ///< IO port 0 pin 4
    BSP_IO_PORT_00_PIN_05 = 0x0005,    ///< IO port 0 pin 5
    BSP_IO_PORT_00_PIN_06 = 0x0006,    ///< IO port 0 pin 6
    BSP_IO_PORT_00_PIN_07 = 0x0007,    ///< IO port 0 pin 7
    BSP_IO_PORT_00_PIN_08 = 0x0008,    ///< IO port 0 pin 8
    BSP_IO_PORT_00_PIN_09 = 0x0009,    ///< IO port 0 pin 9
    BSP_IO_PORT_00_PIN_10 = 0x000A,    ///< IO port 0 pin 10
    BSP_IO_PORT_00_PIN_11 = 0x000B,    ///< IO port 0 pin 11
    BSP_IO_PORT_00_PIN_12 = 0x000C,    ///< IO port 0 pin 12
    BSP_IO_PORT_00_PIN_13 = 0x000D,    ///< IO port 0 pin 13
    BSP_IO_PORT_00_PIN_14 = 0x000E,    ///< IO port 0 pin 14
    BSP_IO_PORT_00_PIN_15 = 0x000F,    ///< IO port 0 pin 15

    BSP_IO_PORT_01_PIN_00 = 0x0100,    ///< IO port 1 pin 0
    BSP_IO_PORT_01_PIN_01 = 0x0101,    ///< IO port 1 pin 1
    BSP_IO_PORT_01_PIN_02 = 0x0102,    ///< IO port 1 pin 2
    BSP_IO_PORT_01_PIN_03 = 0x0103,    ///< IO port 1 pin 3
    BSP_IO_PORT_01_PIN_04 = 0x0104,    ///< IO port 1 pin 4
    BSP_IO_PORT_01_PIN_05 = 0x0105,    ///< IO port 1 pin 5
    BSP_IO_PORT_01_PIN_06 = 0x0106,    ///< IO port 1 pin 6
    BSP_IO_PORT_01_PIN_07 = 0x0107,    ///< IO port 1 pin 7
    BSP_IO_PORT_01_PIN_08 = 0x0108,    ///< IO port 1 pin 8
    BSP_IO_PORT_01_PIN_09 = 0x0109,    ///< IO port 1 pin 9
    BSP_IO_PORT_01_PIN_10 = 0x010A,    ///< IO port 1 pin 10
    BSP_IO_PORT_01_PIN_11 = 0x010B,    ///< IO port 1 pin 11
    BSP_IO_PORT_01_PIN_12 = 0x010C,    ///< IO port 1 pin 12
    BSP_IO_PORT_01_PIN_13 = 0x010D,    ///< IO port 1 pin 13
    BSP_IO_PORT_01_PIN_14 = 0x010E,    ///< IO port 1 pin 14
    BSP_IO_PORT_01_PIN_15 = 0x010F,    ///< IO port 1 pin 15

    BSP_IO_PORT_02_PIN_00 = 0x0200,    ///< IO port 2 pin 0
    BSP_IO_PORT_02_PIN_01 = 0x0201,    ///< IO port 2 pin 1
    BSP_IO_PORT_02_PIN_02 = 0x0202,    ///< IO port 2 pin 2
    BSP_IO_PORT_02_PIN_03 = 0x0203,    ///< IO port 2 pin 3
    BSP_IO_PORT_02_PIN_04 = 0x0204,    ///< IO port 2 pin 4
    BSP_IO_PORT_02_PIN_05 = 0x0205,    ///< IO port 2 pin 5
    BSP_IO_PORT_02_PIN_06 = 0x0206,    ///< IO port 2 pin 6
    BSP_IO_PORT_02_PIN_07 = 0x0207,    ///< IO port 2 pin 7
    BSP_IO_PORT_02_PIN_08 = 0x0208,    ///< IO port 2 pin 8
    BSP_IO_PORT_02_PIN_09 = 0x0209,    ///< IO port 2 pin 9
    BSP_IO_PORT_02_PIN_10 = 0x020A,    ///< IO port 2 pin 10
    BSP_IO_PORT_02_PIN_11 = 0x020B,    ///< IO port 2 pin 11
    BSP_IO_PORT_02_PIN_12 = 0x020C,    ///< IO port 2 pin 12
    BSP_IO_PORT_02_PIN_13 = 0x020D,    ///< IO port 2 pin 13
    BSP_IO_PORT_02_PIN_14 = 0x020E,    ///< IO port 2 pin 14
    BSP_IO_PORT_02_PIN_15 = 0x020F,    ///< IO port 2 pin 15

    BSP_IO_PORT_03_PIN_00 = 0x0300,    ///< IO port 3 pin 0
    BSP_IO_PORT_03_PIN_01 = 0x0301,    ///< IO port 3 pin 1
    BSP_IO_PORT_03_PIN_02 = 0x0302,    ///< IO port 3 pin 2
    BSP_IO_PORT_03_PIN_03 = 0x0303,    ///< IO port 3 pin 3
    BSP_IO_PORT_03_PIN_04 = 0x0304,    ///< IO port 3 pin 4
    BSP_IO_PORT_03_PIN_05 = 0x0305,    ///< IO port 3 pin 5
    BSP_IO_PORT_03_PIN_06 = 0x0306,    ///< IO port 3 pin 6
    BSP_IO_PORT_03_PIN_07 = 0x0307,    ///< IO port 3 pin 7
    BSP_IO_PORT_03_PIN_08 = 0x0308,    ///< IO port 3 pin 8
    BSP_IO_PORT_03_PIN_09 = 0x0309,    ///< IO port 3 pin 9
    BSP_IO_PORT_03_PIN_10 = 0x030A,    ///< IO port 3 pin 10
    BSP_IO_PORT_03_PIN_11 = 0x030B,    ///< IO port 3 pin 11
    BSP_IO_PORT_03_PIN_12 = 0x030C,    ///< IO port 3 pin 12
    BSP_IO_PORT_03_PIN_13 = 0x030D,    ///< IO port 3 pin 13
    BSP_IO_PORT_03_PIN_14 = 0x030E,    ///< IO port 3 pin 14
    BSP_IO_PORT_03_PIN_15 = 0x030F,    ///< IO port 3 pin 15

    BSP_IO_PORT_04_PIN_00 = 0x0400,    ///< IO port 4 pin 0
    BSP_IO_PORT_04_PIN_01 = 0x0401,    ///< IO port 4 pin 1
    BSP_IO_PORT_04_PIN_02 = 0x0402,    ///< IO port 4 pin 2
    BSP_IO_PORT_04_PIN_03 = 0x0403,    ///< IO port 4 pin 3
    BSP_IO_PORT_04_PIN_04 = 0x0404,    ///< IO port 4 pin 4
    BSP_IO_PORT_04_PIN_05 = 0x0405,    ///< IO port 4 pin 5
    BSP_IO_PORT_04_PIN_06 = 0x0406,    ///< IO port 4 pin 6
    BSP_IO_PORT_04_PIN_07 = 0x0407,    ///< IO port 4 pin 7
    BSP_IO_PORT_04_PIN_08 = 0x0408,    ///< IO port 4 pin 8
    BSP_IO_PORT_04_PIN_09 = 0x0409,    ///< IO port 4 pin 9
    BSP_IO_PORT_04_PIN_10 = 0x040A,    ///< IO port 4 pin 10
    BSP_IO_PORT_04_PIN_11 = 0x040B,    ///< IO port 4 pin 11
    BSP_IO_PORT_04_PIN_12 = 0x040C,    ///< IO port 4 pin 12
    BSP_IO_PORT_04_PIN_13 = 0x040D,    ///< IO port 4 pin 13
    BSP_IO_PORT_04_PIN_14 = 0x040E,    ///< IO port 4 pin 14
    BSP_IO_PORT_04_PIN_15 = 0x040F,    ///< IO port 4 pin 15

    BSP_IO_PORT_05_PIN_00 = 0x0500,    ///< IO port 5 pin 0
    BSP_IO_PORT_05_PIN_01 = 0x0501,    ///< IO port 5 pin 1
    BSP_IO_PORT_05_PIN_02 = 0x0502,    ///< IO port 5 pin 2
    BSP_IO_PORT_05_PIN_03 = 0x0503,    ///< IO port 5 pin 3
    BSP_IO_PORT_05_PIN_04 = 0x0504,    ///< IO port 5 pin 4
    BSP_IO_PORT_05_PIN_05 = 0x0505,    ///< IO port 5 pin 5
    BSP_IO_PORT_05_PIN_06 = 0x0506,    ///< IO port 5 pin 6
    BSP_IO_PORT_05_PIN_07 = 0x0507,    ///< IO port 5 pin 7
    BSP_IO_PORT_05_PIN_08 = 0x0508,    ///< IO port 5 pin 8
    BSP_IO_PORT_05_PIN_09 = 0x0509,    ///< IO port 5 pin 9
    BSP_IO_PORT_05_PIN_10 = 0x050A,    ///< IO port 5 pin 10
    BSP_IO_PORT_05_PIN_11 = 0x050B,    ///< IO port 5 pin 11
    BSP_IO_PORT_05_PIN_12 = 0x050C,    ///< IO port 5 pin 12
    BSP_IO_PORT_05_PIN_13 = 0x050D,    ///< IO port 5 pin 13
    BSP_IO_PORT_05_PIN_14 = 0x050E,    ///< IO port 5 pin 14
    BSP_IO_PORT_05_PIN_15 = 0x050F,    ///< IO port 5 pin 15

    BSP_IO_PORT_06_PIN_00 = 0x0600,    ///< IO port 6 pin 0
    BSP_IO_PORT_06_PIN_01 = 0x0601,    ///< IO port 6 pin 1
    BSP_IO_PORT_06_PIN_02 = 0x0602,    ///< IO port 6 pin 2
    BSP_IO_PORT_06_PIN_03 = 0x0603,    ///< IO port 6 pin 3
    BSP_IO_PORT_06_PIN_04 = 0x0604,    ///< IO port 6 pin 4
    BSP_IO_PORT_06_PIN_05 = 0x0605,    ///< IO port 6 pin 5
    BSP_IO_PORT_06_PIN_06 = 0x0606,    ///< IO port 6 pin 6
    BSP_IO_PORT_06_PIN_07 = 0x0607,    ///< IO port 6 pin 7
    BSP_IO_PORT_06_PIN_08 = 0x0608,    ///< IO port 6 pin 8
    BSP_IO_PORT_06_PIN_09 = 0x0609,    ///< IO port 6 pin 9
    BSP_IO_PORT_06_PIN_10 = 0x060A,    ///< IO port 6 pin 10
    BSP_IO_PORT_06_PIN_11 = 0x060B,    ///< IO port 6 pin 11
    BSP_IO_PORT_06_PIN_12 = 0x060C,    ///< IO port 6 pin 12
    BSP_IO_PORT_06_PIN_13 = 0x060D,    ///< IO port 6 pin 13
    BSP_IO_PORT_06_PIN_14 = 0x060E,    ///< IO port 6 pin 14
    BSP_IO_PORT_06_PIN_15 = 0x060F,    ///< IO port 6 pin 15

    BSP_IO_PORT_07_PIN_00 = 0x0700,    ///< IO port 7 pin 0
    BSP_IO_PORT_07_PIN_01 = 0x0701,    ///< IO port 7 pin 1
    BSP_IO_PORT_07_PIN_02 = 0x0702,    ///< IO port 7 pin 2
    BSP_IO_PORT_07_PIN_03 = 0x0703,    ///< IO port 7 pin 3
    BSP_IO_PORT_07_PIN_04 = 0x0704,    ///< IO port 7 pin 4
    BSP_IO_PORT_07_PIN_05 = 0x0705,    ///< IO port 7 pin 5
    BSP_IO_PORT_07_PIN_06 = 0x0706,    ///< IO port 7 pin 6
    BSP_IO_PORT_07_PIN_07 = 0x0707,    ///< IO port 7 pin 7
    BSP_IO_PORT_07_PIN_08 = 0x0708,    ///< IO port 7 pin 8
    BSP_IO_PORT_07_PIN_09 = 0x0709,    ///< IO port 7 pin 9
    BSP_IO_PORT_07_PIN_10 = 0x070A,    ///< IO port 7 pin 10
    BSP_IO_PORT_07_PIN_11 = 0x070B,    ///< IO port 7 pin 11
    BSP_IO_PORT_07_PIN_12 = 0x070C,    ///< IO port 7 pin 12
    BSP_IO_PORT_07_PIN_13 = 0x070D,    ///< IO port 7 pin 13
    BSP_IO_PORT_07_PIN_14 = 0x070E,    ///< IO port 7 pin 14
    BSP_IO_PORT_07_PIN_15 = 0x070F,    ///< IO port 7 pin 15

    BSP_IO_PORT_08_PIN_00 = 0x0800,    ///< IO port 8 pin 0
    BSP_IO_PORT_08_PIN_01 = 0x0801,    ///< IO port 8 pin 1
    BSP_IO_PORT_08_PIN_02 = 0x0802,    ///< IO port 8 pin 2
    BSP_IO_PORT_08_PIN_03 = 0x0803,    ///< IO port 8 pin 3
    BSP_IO_PORT_08_PIN_04 = 0x0804,    ///< IO port 8 pin 4
    BSP_IO_PORT_08_PIN_05 = 0x0805,    ///< IO port 8 pin 5
    BSP_IO_PORT_08_PIN_06 = 0x0806,    ///< IO port 8 pin 6
    BSP_IO_PORT_08_PIN_07 = 0x0807,    ///< IO port 8 pin 7
    BSP_IO_PORT_08_PIN_08 = 0x0808,    ///< IO port 8 pin 8
    BSP_IO_PORT_08_PIN_09 = 0x0809,    ///< IO port 8 pin 9
    BSP_IO_PORT_08_PIN_10 = 0x080A,    ///< IO port 8 pin 10
    BSP_IO_PORT_08_PIN_11 = 0x080B,    ///< IO port 8 pin 11
    BSP_IO_PORT_08_PIN_12 = 0x080C,    ///< IO port 8 pin 12
    BSP_IO_PORT_08_PIN_13 = 0x080D,    ///< IO port 8 pin 13
    BSP_IO_PORT_08_PIN_14 = 0x080E,    ///< IO port 8 pin 14
    BSP_IO_PORT_08_PIN_15 = 0x080F,    ///< IO port 8 pin 15

    BSP_IO_PORT_09_PIN_00 = 0x0900,    ///< IO port 9 pin 0
    BSP_IO_PORT_09_PIN_01 = 0x0901,    ///< IO port 9 pin 1
    BSP_IO_PORT_09_PIN_02 = 0x0902,    ///< IO port 9 pin 2
    BSP_IO_PORT_09_PIN_03 = 0x0903,    ///< IO port 9 pin 3
    BSP_IO_PORT_09_PIN_04 = 0x0904,    ///< IO port 9 pin 4
    BSP_IO_PORT_09_PIN_05 = 0x0905,    ///< IO port 9 pin 5
    BSP_IO_PORT_09_PIN_06 = 0x0906,    ///< IO port 9 pin 6
    BSP_IO_PORT_09_PIN_07 = 0x0907,    ///< IO port 9 pin 7
    BSP_IO_PORT_09_PIN_08 = 0x0908,    ///< IO port 9 pin 8
    BSP_IO_PORT_09_PIN_09 = 0x0909,    ///< IO port 9 pin 9
    BSP_IO_PORT_09_PIN_10 = 0x090A,    ///< IO port 9 pin 10
    BSP_IO_PORT_09_PIN_11 = 0x090B,    ///< IO port 9 pin 11
    BSP_IO_PORT_09_PIN_12 = 0x090C,    ///< IO port 9 pin 12
    BSP_IO_PORT_09_PIN_13 = 0x090D,    ///< IO port 9 pin 13
    BSP_IO_PORT_09_PIN_14 = 0x090E,    ///< IO port 9 pin 14
    BSP_IO_PORT_09_PIN_15 = 0x090F,    ///< IO port 9 pin 15

    BSP_IO_PORT_10_PIN_00 = 0x0A00,    ///< IO port 10 pin 0
    BSP_IO_PORT_10_PIN_01 = 0x0A01,    ///< IO port 10 pin 1
    BSP_IO_PORT_10_PIN_02 = 0x0A02,    ///< IO port 10 pin 2
    BSP_IO_PORT_10_PIN_03 = 0x0A03,    ///< IO port 10 pin 3
    BSP_IO_PORT_10_PIN_04 = 0x0A04,    ///< IO port 10 pin 4
    BSP_IO_PORT_10_PIN_05 = 0x0A05,    ///< IO port 10 pin 5
    BSP_IO_PORT_10_PIN_06 = 0x0A06,    ///< IO port 10 pin 6
    BSP_IO_PORT_10_PIN_07 = 0x0A07,    ///< IO port 10 pin 7
    BSP_IO_PORT_10_PIN_08 = 0x0A08,    ///< IO port 10 pin 8
    BSP_IO_PORT_10_PIN_09 = 0x0A09,    ///< IO port 10 pin 9
    BSP_IO_PORT_10_PIN_10 = 0x0A0A,    ///< IO port 10 pin 10
    BSP_IO_PORT_10_PIN_11 = 0x0A0B,    ///< IO port 10 pin 11
    BSP_IO_PORT_10_PIN_12 = 0x0A0C,    ///< IO port 10 pin 12
    BSP_IO_PORT_10_PIN_13 = 0x0A0D,    ///< IO port 10 pin 13
    BSP_IO_PORT_10_PIN_14 = 0x0A0E,    ///< IO port 10 pin 14
    BSP_IO_PORT_10_PIN_15 = 0x0A0F,    ///< IO port 10 pin 15

    BSP_IO_PORT_11_PIN_00 = 0x0B00,    ///< IO port 11 pin 0
    BSP_IO_PORT_11_PIN_01 = 0x0B01,    ///< IO port 11 pin 1
    BSP_IO_PORT_11_PIN_02 = 0x0B02,    ///< IO port 11 pin 2
    BSP_IO_PORT_11_PIN_03 = 0x0B03,    ///< IO port 11 pin 3
    BSP_IO_PORT_11_PIN_04 = 0x0B04,    ///< IO port 11 pin 4
    BSP_IO_PORT_11_PIN_05 = 0x0B05,    ///< IO port 11 pin 5
    BSP_IO_PORT_11_PIN_06 = 0x0B06,    ///< IO port 11 pin 6
    BSP_IO_PORT_11_PIN_07 = 0x0B07,    ///< IO port 11 pin 7
    BSP_IO_PORT_11_PIN_08 = 0x0B08,    ///< IO port 11 pin 8
    BSP_IO_PORT_11_PIN_09 = 0x0B09,    ///< IO port 11 pin 9
    BSP_IO_PORT_11_PIN_10 = 0x0B0A,    ///< IO port 11 pin 10
    BSP_IO_PORT_11_PIN_11 = 0x0B0B,    ///< IO port 11 pin 11
    BSP_IO_PORT_11_PIN_12 = 0x0B0C,    ///< IO port 11 pin 12
    BSP_IO_PORT_11_PIN_13 = 0x0B0D,    ///< IO port 11 pin 13
    BSP_IO_PORT_11_PIN_14 = 0x0B0E,    ///< IO port 11 pin 14
    BSP_IO_PORT_11_PIN_15 = 0x0B0F,    ///< IO port 11 pin 15

    BSP_IO_PORT_12_PIN_00 = 0x0C00,    ///< IO port 12 pin 0
    BSP_IO_PORT_12_PIN_01 = 0x0C01,    ///< IO port 12 pin 1
    BSP_IO_PORT_12_PIN_02 = 0x0C02,    ///< IO port 12 pin 2
    BSP_IO_PORT_12_PIN_03 = 0x0C03,    ///< IO port 12 pin 3
    BSP_IO_PORT_12_PIN_04 = 0x0C04,    ///< IO port 12 pin 4
    BSP_IO_PORT_12_PIN_05 = 0x0C05,    ///< IO port 12 pin 5
    BSP_IO_PORT_12_PIN_06 = 0x0C06,    ///< IO port 12 pin 6
    BSP_IO_PORT_12_PIN_07 = 0x0C07,    ///< IO port 12 pin 7
    BSP_IO_PORT_12_PIN_08 = 0x0C08,    ///< IO port 12 pin 8
    BSP_IO_PORT_12_PIN_09 = 0x0C09,    ///< IO port 12 pin 9
    BSP_IO_PORT_12_PIN_10 = 0x0C0A,    ///< IO port 12 pin 10
    BSP_IO_PORT_12_PIN_11 = 0x0C0B,    ///< IO port 12 pin 11
    BSP_IO_PORT_12_PIN_12 = 0x0C0C,    ///< IO port 12 pin 12
    BSP_IO_PORT_12_PIN_13 = 0x0C0D,    ///< IO port 12 pin 13
    BSP_IO_PORT_12_PIN_14 = 0x0C0E,    ///< IO port 12 pin 14
    BSP_IO_PORT_12_PIN_15 = 0x0C0F,    ///< IO port 12 pin 15

    BSP_IO_PORT_13_PIN_00 = 0x0D00,    ///< IO port 13 pin 0
    BSP_IO_PORT_13_PIN_01 = 0x0D01,    ///< IO port 13 pin 1
    BSP_IO_PORT_13_PIN_02 = 0x0D02,    ///< IO port 13 pin 2
    BSP_IO_PORT_13_PIN_03 = 0x0D03,    ///< IO port 13 pin 3
    BSP_IO_PORT_13_PIN_04 = 0x0D04,    ///< IO port 13 pin 4
    BSP_IO_PORT_13_PIN_05 = 0x0D05,    ///< IO port 13 pin 5
    BSP_IO_PORT_13_PIN_06 = 0x0D06,    ///< IO port 13 pin 6
    BSP_IO_PORT_13_PIN_07 = 0x0D07,    ///< IO port 13 pin 7
    BSP_IO_PORT_13_PIN_08 = 0x0D08,    ///< IO port 13 pin 8
    BSP_IO_PORT_13_PIN_09 = 0x0D09,    ///< IO port 13 pin 9
    BSP_IO_PORT_13_PIN_10 = 0x0D0A,    ///< IO port 13 pin 10
    BSP_IO_PORT_13_PIN_11 = 0x0D0B,    ///< IO port 13 pin 11
    BSP_IO_PORT_13_PIN_12 = 0x0D0C,    ///< IO port 13 pin 12
    BSP_IO_PORT_13_PIN_13 = 0x0D0D,    ///< IO port 13 pin 13
    BSP_IO_PORT_13_PIN_14 = 0x0D0E,    ///< IO port 13 pin 14
    BSP_IO_PORT_13_PIN_15 = 0x0D0F,    ///< IO port 13 pin 15

    BSP_IO_PORT_14_PIN_00 = 0x0E00,    ///< IO port 14 pin 0
    BSP_IO_PORT_14_PIN_01 = 0x0E01,    ///< IO port 14 pin 1
    BSP_IO_PORT_14_PIN_02 = 0x0E02,    ///< IO port 14 pin 2
    BSP_IO_PORT_14_PIN_03 = 0x0E03,    ///< IO port 14 pin 3
    BSP_IO_PORT_14_PIN_04 = 0x0E04,    ///< IO port 14 pin 4
    BSP_IO_PORT_14_PIN_05 = 0x0E05,    ///< IO port 14 pin 5
    BSP_IO_PORT_14_PIN_06 = 0x0E06,    ///< IO port 14 pin 6
    BSP_IO_PORT_14_PIN_07 = 0x0E07,    ///< IO port 14 pin 7
    BSP_IO_PORT_14_PIN_08 = 0x0E08,    ///< IO port 14 pin 8
    BSP_IO_PORT_14_PIN_09 = 0x0E09,    ///< IO port 14 pin 9
    BSP_IO_PORT_14_PIN_10 = 0x0E0A,    ///< IO port 14 pin 10
    BSP_IO_PORT_14_PIN_11 = 0x0E0B,    ///< IO port 14 pin 11
    BSP_IO_PORT_14_PIN_12 = 0x0E0C,    ///< IO port 14 pin 12
    BSP_IO_PORT_14_PIN_13 = 0x0E0D,    ///< IO port 14 pin 13
    BSP_IO_PORT_14_PIN_14 = 0x0E0E,    ///< IO port 14 pin 14
    BSP_IO_PORT_14_PIN_15 = 0x0E0F,    ///< IO port 14 pin 15
} bsp_io_port_pin_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern volatile uint32_t g_protect_pfswe_counter;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Read the current input level of the pin.
 *
 * @param[in]  pin             The pin
 *
 * @retval     Current input level
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_PinRead (bsp_io_port_pin_t pin)
{
    /* Read pin level. */
    return R_PFS->PORT[pin >> 8].PIN[pin & BSP_IO_PRV_8BIT_MASK].PmnPFS_b.PIDR;
}

/*******************************************************************************************************************//**
 * Set a pin to output and set the output level to the level provided. If PFS protection is enabled, disable PFS
 * protection using R_BSP_PinAccessEnable() before calling this function.
 *
 * @param[in]  pin      The pin
 * @param[in]  level    The level
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinWrite (bsp_io_port_pin_t pin, bsp_io_level_t level)
{
    /* Clear PMR, ASEL, ISEL and PODR bits. */
    uint32_t pfs_bits = R_PFS->PORT[pin >> 8].PIN[pin & BSP_IO_PRV_8BIT_MASK].PmnPFS;
    pfs_bits &= BSP_IO_PRV_PIN_WRITE_MASK;

    /* Set output level and pin direction to output. */
    uint32_t lvl = ((uint32_t) level | pfs_bits);
    R_PFS->PORT[pin >> 8].PIN[pin & BSP_IO_PRV_8BIT_MASK].PmnPFS = (BSP_IO_PFS_PDR_OUTPUT | lvl);
}

/*******************************************************************************************************************//**
 * Configure a pin. If PFS protection is enabled, disable PFS protection using R_BSP_PinAccessEnable() before calling
 * this function.
 *
 * @param[in]  pin      The pin
 * @param[in]  cfg      Configuration for the pin (PmnPFS register setting)
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinCfg (bsp_io_port_pin_t pin, uint32_t cfg)
{
    /* Configure a pin. */
    R_PFS->PORT[pin >> 8].PIN[pin & BSP_IO_PRV_8BIT_MASK].PmnPFS = cfg;
}

/*******************************************************************************************************************//**
 * Enable access to the PFS registers. Uses a reference counter to protect against interrupts that could occur
 * via multiple threads or an ISR re-entering this code.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinAccessEnable (void)
{
#if BSP_CFG_PFS_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /** If this is first entry then allow writing of PFS. */
    if (0 == g_protect_pfswe_counter)
    {
 #if BSP_TZ_SECURE_BUILD || (BSP_CFG_MCU_PART_SERIES == 8)
        R_PMISC->PWPRS = 0;                              ///< Clear BOWI bit - writing to PFSWE bit enabled
        R_PMISC->PWPRS = 1U << BSP_IO_PWPR_PFSWE_OFFSET; ///< Set PFSWE bit - writing to PFS register enabled
 #else
        R_PMISC->PWPR = 0;                               ///< Clear BOWI bit - writing to PFSWE bit enabled
        R_PMISC->PWPR = 1U << BSP_IO_PWPR_PFSWE_OFFSET;  ///< Set PFSWE bit - writing to PFS register enabled
 #endif
    }

    /** Increment the protect counter */
    g_protect_pfswe_counter++;

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

/*******************************************************************************************************************//**
 * Disable access to the PFS registers. Uses a reference counter to protect against interrupts that could occur via
 * multiple threads or an ISR re-entering this code.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinAccessDisable (void)
{
#if BSP_CFG_PFS_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /** Is it safe to disable PFS register? */
    if (0 != g_protect_pfswe_counter)
    {
        /* Decrement the protect counter */
        g_protect_pfswe_counter--;
    }

    /** Is it safe to disable writing of PFS? */
    if (0 == g_protect_pfswe_counter)
    {
 #if BSP_TZ_SECURE_BUILD || (BSP_CFG_MCU_PART_SERIES == 8)
        R_PMISC->PWPRS = 0;                             ///< Clear PFSWE bit - writing to PFSWE bit enabled
        R_PMISC->PWPRS = 1U << BSP_IO_PWPR_B0WI_OFFSET; ///< Set BOWI bit - writing to PFS register enabled
 #else
        R_PMISC->PWPR = 0;                              ///< Clear PFSWE bit - writing to PFS register disabled
        R_PMISC->PWPR = 1U << BSP_IO_PWPR_B0WI_OFFSET;  ///< Set BOWI bit - writing to PFSWE bit disabled
 #endif
    }

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

/** @} (end addtogroup BSP_IO) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
