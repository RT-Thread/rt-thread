/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @defgroup BSP_IO BSP I/O access
 * @ingroup RENESAS_COMMON
 * @brief This module provides basic read/write/toggle access to port pins and read/write access to port.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_IO_H
#define BSP_IO_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Private definition to set enumeration values. */
#define BSP_IO_PRV_8BIT_MASK          (0xFF)
#define BSP_IO_PM_OUTPUT              (3U)

/* Key code for writing PRCR register. */
#define BSP_IO_PRV_PRCR_KEY           (0xA500U)
#define BSP_IO_REG_PROTECT_GPIO       (0x0004U)

/* Difference between safety and non safety I/O port region addresses. */
#define BSP_IO_REGION_ADDRESS_DIFF    (R_PORT_SR_BASE - R_PORT_NSR_BASE)

/* Shift to get port in bsp_io_port_t and bsp_io_port_pin_t enums. */
#define BSP_IO_PRV_PORT_OFFSET        (8U)

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
    BSP_IO_PORT_15 = 0x0F00,           ///< IO port 15
    BSP_IO_PORT_16 = 0x1000,           ///< IO port 16
    BSP_IO_PORT_17 = 0x1100,           ///< IO port 17
    BSP_IO_PORT_18 = 0x1200,           ///< IO port 18
    BSP_IO_PORT_19 = 0x1300,           ///< IO port 19
    BSP_IO_PORT_20 = 0x1400,           ///< IO port 20
    BSP_IO_PORT_21 = 0x1500,           ///< IO port 21
    BSP_IO_PORT_22 = 0x1600,           ///< IO port 22
    BSP_IO_PORT_23 = 0x1700,           ///< IO port 23
    BSP_IO_PORT_24 = 0x1800,           ///< IO port 24
} bsp_io_port_t;

/** Superset list of all possible IO port pins. */
typedef enum e_bsp_io_port_pin
{
    BSP_IO_PORT_00_PIN_0 = 0x0000,     ///< IO port 0 pin 0
    BSP_IO_PORT_00_PIN_1 = 0x0001,     ///< IO port 0 pin 1
    BSP_IO_PORT_00_PIN_2 = 0x0002,     ///< IO port 0 pin 2
    BSP_IO_PORT_00_PIN_3 = 0x0003,     ///< IO port 0 pin 3
    BSP_IO_PORT_00_PIN_4 = 0x0004,     ///< IO port 0 pin 4
    BSP_IO_PORT_00_PIN_5 = 0x0005,     ///< IO port 0 pin 5
    BSP_IO_PORT_00_PIN_6 = 0x0006,     ///< IO port 0 pin 6
    BSP_IO_PORT_00_PIN_7 = 0x0007,     ///< IO port 0 pin 7

    BSP_IO_PORT_01_PIN_0 = 0x0100,     ///< IO port 1 pin 0
    BSP_IO_PORT_01_PIN_1 = 0x0101,     ///< IO port 1 pin 1
    BSP_IO_PORT_01_PIN_2 = 0x0102,     ///< IO port 1 pin 2
    BSP_IO_PORT_01_PIN_3 = 0x0103,     ///< IO port 1 pin 3
    BSP_IO_PORT_01_PIN_4 = 0x0104,     ///< IO port 1 pin 4
    BSP_IO_PORT_01_PIN_5 = 0x0105,     ///< IO port 1 pin 5
    BSP_IO_PORT_01_PIN_6 = 0x0106,     ///< IO port 1 pin 6
    BSP_IO_PORT_01_PIN_7 = 0x0107,     ///< IO port 1 pin 7

    BSP_IO_PORT_02_PIN_0 = 0x0200,     ///< IO port 2 pin 0
    BSP_IO_PORT_02_PIN_1 = 0x0201,     ///< IO port 2 pin 1
    BSP_IO_PORT_02_PIN_2 = 0x0202,     ///< IO port 2 pin 2
    BSP_IO_PORT_02_PIN_3 = 0x0203,     ///< IO port 2 pin 3
    BSP_IO_PORT_02_PIN_4 = 0x0204,     ///< IO port 2 pin 4
    BSP_IO_PORT_02_PIN_5 = 0x0205,     ///< IO port 2 pin 5
    BSP_IO_PORT_02_PIN_6 = 0x0206,     ///< IO port 2 pin 6
    BSP_IO_PORT_02_PIN_7 = 0x0207,     ///< IO port 2 pin 7

    BSP_IO_PORT_03_PIN_0 = 0x0300,     ///< IO port 3 pin 0
    BSP_IO_PORT_03_PIN_1 = 0x0301,     ///< IO port 3 pin 1
    BSP_IO_PORT_03_PIN_2 = 0x0302,     ///< IO port 3 pin 2
    BSP_IO_PORT_03_PIN_3 = 0x0303,     ///< IO port 3 pin 3
    BSP_IO_PORT_03_PIN_4 = 0x0304,     ///< IO port 3 pin 4
    BSP_IO_PORT_03_PIN_5 = 0x0305,     ///< IO port 3 pin 5
    BSP_IO_PORT_03_PIN_6 = 0x0306,     ///< IO port 3 pin 6
    BSP_IO_PORT_03_PIN_7 = 0x0307,     ///< IO port 3 pin 7

    BSP_IO_PORT_04_PIN_0 = 0x0400,     ///< IO port 4 pin 0
    BSP_IO_PORT_04_PIN_1 = 0x0401,     ///< IO port 4 pin 1
    BSP_IO_PORT_04_PIN_2 = 0x0402,     ///< IO port 4 pin 2
    BSP_IO_PORT_04_PIN_3 = 0x0403,     ///< IO port 4 pin 3
    BSP_IO_PORT_04_PIN_4 = 0x0404,     ///< IO port 4 pin 4
    BSP_IO_PORT_04_PIN_5 = 0x0405,     ///< IO port 4 pin 5
    BSP_IO_PORT_04_PIN_6 = 0x0406,     ///< IO port 4 pin 6
    BSP_IO_PORT_04_PIN_7 = 0x0407,     ///< IO port 4 pin 7

    BSP_IO_PORT_05_PIN_0 = 0x0500,     ///< IO port 5 pin 0
    BSP_IO_PORT_05_PIN_1 = 0x0501,     ///< IO port 5 pin 1
    BSP_IO_PORT_05_PIN_2 = 0x0502,     ///< IO port 5 pin 2
    BSP_IO_PORT_05_PIN_3 = 0x0503,     ///< IO port 5 pin 3
    BSP_IO_PORT_05_PIN_4 = 0x0504,     ///< IO port 5 pin 4
    BSP_IO_PORT_05_PIN_5 = 0x0505,     ///< IO port 5 pin 5
    BSP_IO_PORT_05_PIN_6 = 0x0506,     ///< IO port 5 pin 6
    BSP_IO_PORT_05_PIN_7 = 0x0507,     ///< IO port 5 pin 7

    BSP_IO_PORT_06_PIN_0 = 0x0600,     ///< IO port 6 pin 0
    BSP_IO_PORT_06_PIN_1 = 0x0601,     ///< IO port 6 pin 1
    BSP_IO_PORT_06_PIN_2 = 0x0602,     ///< IO port 6 pin 2
    BSP_IO_PORT_06_PIN_3 = 0x0603,     ///< IO port 6 pin 3
    BSP_IO_PORT_06_PIN_4 = 0x0604,     ///< IO port 6 pin 4
    BSP_IO_PORT_06_PIN_5 = 0x0605,     ///< IO port 6 pin 5
    BSP_IO_PORT_06_PIN_6 = 0x0606,     ///< IO port 6 pin 6
    BSP_IO_PORT_06_PIN_7 = 0x0607,     ///< IO port 6 pin 7

    BSP_IO_PORT_07_PIN_0 = 0x0700,     ///< IO port 7 pin 0
    BSP_IO_PORT_07_PIN_1 = 0x0701,     ///< IO port 7 pin 1
    BSP_IO_PORT_07_PIN_2 = 0x0702,     ///< IO port 7 pin 2
    BSP_IO_PORT_07_PIN_3 = 0x0703,     ///< IO port 7 pin 3
    BSP_IO_PORT_07_PIN_4 = 0x0704,     ///< IO port 7 pin 4
    BSP_IO_PORT_07_PIN_5 = 0x0705,     ///< IO port 7 pin 5
    BSP_IO_PORT_07_PIN_6 = 0x0706,     ///< IO port 7 pin 6
    BSP_IO_PORT_07_PIN_7 = 0x0707,     ///< IO port 7 pin 7

    BSP_IO_PORT_08_PIN_0 = 0x0800,     ///< IO port 8 pin 0
    BSP_IO_PORT_08_PIN_1 = 0x0801,     ///< IO port 8 pin 1
    BSP_IO_PORT_08_PIN_2 = 0x0802,     ///< IO port 8 pin 2
    BSP_IO_PORT_08_PIN_3 = 0x0803,     ///< IO port 8 pin 3
    BSP_IO_PORT_08_PIN_4 = 0x0804,     ///< IO port 8 pin 4
    BSP_IO_PORT_08_PIN_5 = 0x0805,     ///< IO port 8 pin 5
    BSP_IO_PORT_08_PIN_6 = 0x0806,     ///< IO port 8 pin 6
    BSP_IO_PORT_08_PIN_7 = 0x0807,     ///< IO port 8 pin 7

    BSP_IO_PORT_09_PIN_0 = 0x0900,     ///< IO port 9 pin 0
    BSP_IO_PORT_09_PIN_1 = 0x0901,     ///< IO port 9 pin 1
    BSP_IO_PORT_09_PIN_2 = 0x0902,     ///< IO port 9 pin 2
    BSP_IO_PORT_09_PIN_3 = 0x0903,     ///< IO port 9 pin 3
    BSP_IO_PORT_09_PIN_4 = 0x0904,     ///< IO port 9 pin 4
    BSP_IO_PORT_09_PIN_5 = 0x0905,     ///< IO port 9 pin 5
    BSP_IO_PORT_09_PIN_6 = 0x0906,     ///< IO port 9 pin 6
    BSP_IO_PORT_09_PIN_7 = 0x0907,     ///< IO port 9 pin 7

    BSP_IO_PORT_10_PIN_0 = 0x0A00,     ///< IO port 10 pin 0
    BSP_IO_PORT_10_PIN_1 = 0x0A01,     ///< IO port 10 pin 1
    BSP_IO_PORT_10_PIN_2 = 0x0A02,     ///< IO port 10 pin 2
    BSP_IO_PORT_10_PIN_3 = 0x0A03,     ///< IO port 10 pin 3
    BSP_IO_PORT_10_PIN_4 = 0x0A04,     ///< IO port 10 pin 4
    BSP_IO_PORT_10_PIN_5 = 0x0A05,     ///< IO port 10 pin 5
    BSP_IO_PORT_10_PIN_6 = 0x0A06,     ///< IO port 10 pin 6
    BSP_IO_PORT_10_PIN_7 = 0x0A07,     ///< IO port 10 pin 7

    BSP_IO_PORT_11_PIN_0 = 0x0B00,     ///< IO port 11 pin 0
    BSP_IO_PORT_11_PIN_1 = 0x0B01,     ///< IO port 11 pin 1
    BSP_IO_PORT_11_PIN_2 = 0x0B02,     ///< IO port 11 pin 2
    BSP_IO_PORT_11_PIN_3 = 0x0B03,     ///< IO port 11 pin 3
    BSP_IO_PORT_11_PIN_4 = 0x0B04,     ///< IO port 11 pin 4
    BSP_IO_PORT_11_PIN_5 = 0x0B05,     ///< IO port 11 pin 5
    BSP_IO_PORT_11_PIN_6 = 0x0B06,     ///< IO port 11 pin 6
    BSP_IO_PORT_11_PIN_7 = 0x0B07,     ///< IO port 11 pin 7

    BSP_IO_PORT_12_PIN_0 = 0x0C00,     ///< IO port 12 pin 0
    BSP_IO_PORT_12_PIN_1 = 0x0C01,     ///< IO port 12 pin 1
    BSP_IO_PORT_12_PIN_2 = 0x0C02,     ///< IO port 12 pin 2
    BSP_IO_PORT_12_PIN_3 = 0x0C03,     ///< IO port 12 pin 3
    BSP_IO_PORT_12_PIN_4 = 0x0C04,     ///< IO port 12 pin 4
    BSP_IO_PORT_12_PIN_5 = 0x0C05,     ///< IO port 12 pin 5
    BSP_IO_PORT_12_PIN_6 = 0x0C06,     ///< IO port 12 pin 6
    BSP_IO_PORT_12_PIN_7 = 0x0C07,     ///< IO port 12 pin 7

    BSP_IO_PORT_13_PIN_0 = 0x0D00,     ///< IO port 13 pin 0
    BSP_IO_PORT_13_PIN_1 = 0x0D01,     ///< IO port 13 pin 1
    BSP_IO_PORT_13_PIN_2 = 0x0D02,     ///< IO port 13 pin 2
    BSP_IO_PORT_13_PIN_3 = 0x0D03,     ///< IO port 13 pin 3
    BSP_IO_PORT_13_PIN_4 = 0x0D04,     ///< IO port 13 pin 4
    BSP_IO_PORT_13_PIN_5 = 0x0D05,     ///< IO port 13 pin 5
    BSP_IO_PORT_13_PIN_6 = 0x0D06,     ///< IO port 13 pin 6
    BSP_IO_PORT_13_PIN_7 = 0x0D07,     ///< IO port 13 pin 7

    BSP_IO_PORT_14_PIN_0 = 0x0E00,     ///< IO port 14 pin 0
    BSP_IO_PORT_14_PIN_1 = 0x0E01,     ///< IO port 14 pin 1
    BSP_IO_PORT_14_PIN_2 = 0x0E02,     ///< IO port 14 pin 2
    BSP_IO_PORT_14_PIN_3 = 0x0E03,     ///< IO port 14 pin 3
    BSP_IO_PORT_14_PIN_4 = 0x0E04,     ///< IO port 14 pin 4
    BSP_IO_PORT_14_PIN_5 = 0x0E05,     ///< IO port 14 pin 5
    BSP_IO_PORT_14_PIN_6 = 0x0E06,     ///< IO port 14 pin 6
    BSP_IO_PORT_14_PIN_7 = 0x0E07,     ///< IO port 14 pin 7

    BSP_IO_PORT_15_PIN_0 = 0x0F00,     ///< IO port 15 pin 0
    BSP_IO_PORT_15_PIN_1 = 0x0F01,     ///< IO port 15 pin 1
    BSP_IO_PORT_15_PIN_2 = 0x0F02,     ///< IO port 15 pin 2
    BSP_IO_PORT_15_PIN_3 = 0x0F03,     ///< IO port 15 pin 3
    BSP_IO_PORT_15_PIN_4 = 0x0F04,     ///< IO port 15 pin 4
    BSP_IO_PORT_15_PIN_5 = 0x0F05,     ///< IO port 15 pin 5
    BSP_IO_PORT_15_PIN_6 = 0x0F06,     ///< IO port 15 pin 6
    BSP_IO_PORT_15_PIN_7 = 0x0F07,     ///< IO port 15 pin 7

    BSP_IO_PORT_16_PIN_0 = 0x1000,     ///< IO port 16 pin 0
    BSP_IO_PORT_16_PIN_1 = 0x1001,     ///< IO port 16 pin 1
    BSP_IO_PORT_16_PIN_2 = 0x1002,     ///< IO port 16 pin 2
    BSP_IO_PORT_16_PIN_3 = 0x1003,     ///< IO port 16 pin 3
    BSP_IO_PORT_16_PIN_4 = 0x1004,     ///< IO port 16 pin 4
    BSP_IO_PORT_16_PIN_5 = 0x1005,     ///< IO port 16 pin 5
    BSP_IO_PORT_16_PIN_6 = 0x1006,     ///< IO port 16 pin 6
    BSP_IO_PORT_16_PIN_7 = 0x1007,     ///< IO port 16 pin 7

    BSP_IO_PORT_17_PIN_0 = 0x1100,     ///< IO port 17 pin 0
    BSP_IO_PORT_17_PIN_1 = 0x1101,     ///< IO port 17 pin 1
    BSP_IO_PORT_17_PIN_2 = 0x1102,     ///< IO port 17 pin 2
    BSP_IO_PORT_17_PIN_3 = 0x1103,     ///< IO port 17 pin 3
    BSP_IO_PORT_17_PIN_4 = 0x1104,     ///< IO port 17 pin 4
    BSP_IO_PORT_17_PIN_5 = 0x1105,     ///< IO port 17 pin 5
    BSP_IO_PORT_17_PIN_6 = 0x1106,     ///< IO port 17 pin 6
    BSP_IO_PORT_17_PIN_7 = 0x1107,     ///< IO port 17 pin 7

    BSP_IO_PORT_18_PIN_0 = 0x1200,     ///< IO port 18 pin 0
    BSP_IO_PORT_18_PIN_1 = 0x1201,     ///< IO port 18 pin 1
    BSP_IO_PORT_18_PIN_2 = 0x1202,     ///< IO port 18 pin 2
    BSP_IO_PORT_18_PIN_3 = 0x1203,     ///< IO port 18 pin 3
    BSP_IO_PORT_18_PIN_4 = 0x1204,     ///< IO port 18 pin 4
    BSP_IO_PORT_18_PIN_5 = 0x1205,     ///< IO port 18 pin 5
    BSP_IO_PORT_18_PIN_6 = 0x1206,     ///< IO port 18 pin 6
    BSP_IO_PORT_18_PIN_7 = 0x1207,     ///< IO port 18 pin 7

    BSP_IO_PORT_19_PIN_0 = 0x1300,     ///< IO port 19 pin 0
    BSP_IO_PORT_19_PIN_1 = 0x1301,     ///< IO port 19 pin 1
    BSP_IO_PORT_19_PIN_2 = 0x1302,     ///< IO port 19 pin 2
    BSP_IO_PORT_19_PIN_3 = 0x1303,     ///< IO port 19 pin 3
    BSP_IO_PORT_19_PIN_4 = 0x1304,     ///< IO port 19 pin 4
    BSP_IO_PORT_19_PIN_5 = 0x1305,     ///< IO port 19 pin 5
    BSP_IO_PORT_19_PIN_6 = 0x1306,     ///< IO port 19 pin 6
    BSP_IO_PORT_19_PIN_7 = 0x1307,     ///< IO port 19 pin 7

    BSP_IO_PORT_20_PIN_0 = 0x1400,     ///< IO port 20 pin 0
    BSP_IO_PORT_20_PIN_1 = 0x1401,     ///< IO port 20 pin 1
    BSP_IO_PORT_20_PIN_2 = 0x1402,     ///< IO port 20 pin 2
    BSP_IO_PORT_20_PIN_3 = 0x1403,     ///< IO port 20 pin 3
    BSP_IO_PORT_20_PIN_4 = 0x1404,     ///< IO port 20 pin 4
    BSP_IO_PORT_20_PIN_5 = 0x1405,     ///< IO port 20 pin 5
    BSP_IO_PORT_20_PIN_6 = 0x1406,     ///< IO port 20 pin 6
    BSP_IO_PORT_20_PIN_7 = 0x1407,     ///< IO port 20 pin 7

    BSP_IO_PORT_21_PIN_0 = 0x1500,     ///< IO port 21 pin 0
    BSP_IO_PORT_21_PIN_1 = 0x1501,     ///< IO port 21 pin 1
    BSP_IO_PORT_21_PIN_2 = 0x1502,     ///< IO port 21 pin 2
    BSP_IO_PORT_21_PIN_3 = 0x1503,     ///< IO port 21 pin 3
    BSP_IO_PORT_21_PIN_4 = 0x1504,     ///< IO port 21 pin 4
    BSP_IO_PORT_21_PIN_5 = 0x1505,     ///< IO port 21 pin 5
    BSP_IO_PORT_21_PIN_6 = 0x1506,     ///< IO port 21 pin 6
    BSP_IO_PORT_21_PIN_7 = 0x1507,     ///< IO port 21 pin 7

    BSP_IO_PORT_22_PIN_0 = 0x1600,     ///< IO port 22 pin 0
    BSP_IO_PORT_22_PIN_1 = 0x1601,     ///< IO port 22 pin 1
    BSP_IO_PORT_22_PIN_2 = 0x1602,     ///< IO port 22 pin 2
    BSP_IO_PORT_22_PIN_3 = 0x1603,     ///< IO port 22 pin 3
    BSP_IO_PORT_22_PIN_4 = 0x1604,     ///< IO port 22 pin 4
    BSP_IO_PORT_22_PIN_5 = 0x1605,     ///< IO port 22 pin 5
    BSP_IO_PORT_22_PIN_6 = 0x1606,     ///< IO port 22 pin 6
    BSP_IO_PORT_22_PIN_7 = 0x1607,     ///< IO port 22 pin 7

    BSP_IO_PORT_23_PIN_0 = 0x1700,     ///< IO port 23 pin 0
    BSP_IO_PORT_23_PIN_1 = 0x1701,     ///< IO port 23 pin 1
    BSP_IO_PORT_23_PIN_2 = 0x1702,     ///< IO port 23 pin 2
    BSP_IO_PORT_23_PIN_3 = 0x1703,     ///< IO port 23 pin 3
    BSP_IO_PORT_23_PIN_4 = 0x1704,     ///< IO port 23 pin 4
    BSP_IO_PORT_23_PIN_5 = 0x1705,     ///< IO port 23 pin 5
    BSP_IO_PORT_23_PIN_6 = 0x1706,     ///< IO port 23 pin 6
    BSP_IO_PORT_23_PIN_7 = 0x1707,     ///< IO port 23 pin 7

    BSP_IO_PORT_24_PIN_0 = 0x1800,     ///< IO port 24 pin 0
    BSP_IO_PORT_24_PIN_1 = 0x1801,     ///< IO port 24 pin 1
    BSP_IO_PORT_24_PIN_2 = 0x1802,     ///< IO port 24 pin 2
    BSP_IO_PORT_24_PIN_3 = 0x1803,     ///< IO port 24 pin 3
    BSP_IO_PORT_24_PIN_4 = 0x1804,     ///< IO port 24 pin 4
    BSP_IO_PORT_24_PIN_5 = 0x1805,     ///< IO port 24 pin 5
    BSP_IO_PORT_24_PIN_6 = 0x1806,     ///< IO port 24 pin 6
    BSP_IO_PORT_24_PIN_7 = 0x1807,     ///< IO port 24 pin 7
} bsp_io_port_pin_t;

/** Offset for pin safety region access */
typedef enum e_bsp_io_region
{
    BSP_IO_REGION_NOT_SAFE = 0,                          ///< Non safety region
    BSP_IO_REGION_SAFE     = BSP_IO_REGION_ADDRESS_DIFF, ///< Safety region
} bsp_io_region_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern volatile uint32_t g_protect_port_counter;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Inline Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Set the output level of the pin in the specified region.
 *
 * @param[in]  region          The target IO region
 * @param[in]  pin             The pin
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinSet (bsp_io_region_t region, bsp_io_port_pin_t pin)
{
    /* Casting to a uint8_t type is valid because only the lower 8 bits of pin(uint16_t) are extracted by masking on
     * the right side. */
    ((R_PORT_COMMON_Type *) (R_PORT_NSR_BASE + region))->P[pin >>
                                                           BSP_IO_PRV_PORT_OFFSET] |=
        (uint8_t) (1UL << (pin & BSP_IO_PRV_8BIT_MASK));
}

/*******************************************************************************************************************//**
 * Clear the output level of the pin in the specified region.
 *
 * @param[in]  region          The target IO region
 * @param[in]  pin             The pin
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinClear (bsp_io_region_t region, bsp_io_port_pin_t pin)
{
    /* Casting to a uint8_t type is valid because only the lower 8 bits of pin(uint16_t) are extracted by masking on
     * the right side. */
    ((R_PORT_COMMON_Type *) (R_PORT_NSR_BASE + region))->P[pin >> BSP_IO_PRV_PORT_OFFSET] &=
        (uint8_t) (~(1UL << (pin & BSP_IO_PRV_8BIT_MASK)));
}

/*******************************************************************************************************************//**
 * Toggle the output level of the pin in the specified region.
 *
 * @param[in]  region          The target IO region
 * @param[in]  pin             The pin
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinToggle (bsp_io_region_t region, bsp_io_port_pin_t pin)
{
    /* Casting to a uint8_t type is valid because only the lower 8 bits of pin(uint16_t) are extracted by masking on
     * the right side. */
    ((R_PORT_COMMON_Type *) (R_PORT_NSR_BASE + region))->P[pin >>
                                                           BSP_IO_PRV_PORT_OFFSET] ^=
        (uint8_t) (1UL << (pin & BSP_IO_PRV_8BIT_MASK));
}

/*******************************************************************************************************************//**
 * Read the input level of the pin in the specified region.
 *
 * @param[in]  region          The target IO region
 * @param[in]  pin             The pin
 *
 * @retval     Current input level
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_FastPinRead (bsp_io_region_t region, bsp_io_port_pin_t pin)
{
    return (uint32_t) ((((R_PORT_COMMON_Type *) (R_PORT_NSR_BASE + region))->PIN[pin >> BSP_IO_PRV_PORT_OFFSET]) >>
                       (pin & BSP_IO_PRV_8BIT_MASK)) & 0x00000001UL;
}

/*******************************************************************************************************************//**
 * Set the output value of the port in the specified region. All pins in the port must be set to the same IO region to
 * use this function.
 *
 * @param[in]  region           The target IO region
 * @param[in]  port             The port
 * @param[in]  set_value        The setting value
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PortWrite (bsp_io_region_t region, bsp_io_port_t port, uint8_t set_value)
{
    ((R_PORT_COMMON_Type *) (R_PORT_NSR_BASE + region))->P[port >> BSP_IO_PRV_PORT_OFFSET] = set_value;
}

/*******************************************************************************************************************//**
 * Read the input value of the port in the specified region. All pins in the port must be set to the same IO region to
 * use this function.
 *
 * @param[in]  region           The target IO region
 * @param[in]  port             The port
 *
 * @retval     Current input value
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_PortRead (bsp_io_region_t region, bsp_io_port_t port)
{
    return (uint32_t) (((R_PORT_COMMON_Type *) (R_PORT_NSR_BASE + region))->PIN[port >> BSP_IO_PRV_PORT_OFFSET]);
}

/*******************************************************************************************************************//**
 * Enable access to the PFS registers. Uses a reference counter to protect against interrupts that could occur
 * via multiple threads or an ISR re-entering this code.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinAccessEnable (void)
{
#if BSP_CFG_PORT_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /** If this is first entry then allow writing of PFS. */
    if (0 == g_protect_port_counter)
    {
        /** Disable protection using PRCR register. */

        /** When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
         * disable writes. */
        R_RWP_NS->PRCRN = ((R_RWP_NS->PRCRN | BSP_IO_PRV_PRCR_KEY) | BSP_IO_REG_PROTECT_GPIO);
        R_RWP_S->PRCRS  = ((R_RWP_S->PRCRS | BSP_IO_PRV_PRCR_KEY) | BSP_IO_REG_PROTECT_GPIO);
    }

    /** Increment the protect counter */
    g_protect_port_counter++;

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
#if BSP_CFG_PORT_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /** Is it safe to disable PFS register? */
    if (0 != g_protect_port_counter)
    {
        /* Decrement the protect counter */
        g_protect_port_counter--;
    }

    /** Is it safe to disable writing of PFS? */
    if (0 == g_protect_port_counter)
    {
        /** Enable protection using PRCR register. */

        /** When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
         * disable writes. */
        R_RWP_NS->PRCRN = ((R_RWP_NS->PRCRN | BSP_IO_PRV_PRCR_KEY) & (uint16_t) (~BSP_IO_REG_PROTECT_GPIO));
        R_RWP_S->PRCRS  = ((R_RWP_S->PRCRS | BSP_IO_PRV_PRCR_KEY) & (uint16_t) (~BSP_IO_REG_PROTECT_GPIO));
    }

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

/*******************************************************************************************************************//**
 * Read IO region of the pin.
 *
 * @param[in]  pin                   The pin
 *
 * @retval BSP_IO_REGION_SAFE        IO region of the pin is safety
 * @retval BSP_IO_REGION_NOT_SAFE    IO region of the pin is non-safety
 *
 * This function can be given as an argument to pin/port access functions described below. When used in a function
 * starting with R_BSP_Port, any one pin in the port should be given as an argument to this function.
 * R_BSP_PinSet(), R_BSP_PinClear(), R_BSP_PinToggle(), R_BSP_FastPinRead(), R_BSP_PortWrite(), R_BSP_PortRead()
 *
 * @note This function can be used to get the region of a specified pin, but the overhead should be considered if this
 *       function is executed each time the pin is accessed. When accessing the same pin repeatedly, it is recommended
 *       that the value obtained by this function be held in a variable beforehand, and the value of the variable be
 *       used as the region argument of the pin access function.
 **********************************************************************************************************************/
__STATIC_INLINE bsp_io_region_t R_BSP_IoRegionGet (bsp_io_port_pin_t pin)
{
    /* Casting to a uint32_t type is valid because the range of values represented by uint32_t is not over in the
     * calculation process of the right-hand side. */
    uint32_t aselp =
        ((uint32_t) ((R_PTADR->RSELP[pin >> BSP_IO_PRV_PORT_OFFSET]) >> (pin & BSP_IO_PRV_8BIT_MASK)) & 0x00000001UL);

    if (0U == aselp)
    {
        return BSP_IO_REGION_SAFE;
    }
    else
    {
        return BSP_IO_REGION_NOT_SAFE;
    }
}

/** @} (end addtogroup BSP_IO) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
