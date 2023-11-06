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
 * @addtogroup IOPORT
 * @{
 **********************************************************************************************************************/

#ifndef R_IOPORT_H
#define R_IOPORT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#include "r_ioport_api.h"
#if __has_include("r_ioport_cfg.h")
 #include "r_ioport_cfg.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Private definition to set enumeration values. */
#define IOPORT_PRV_PFS_PSEL_OFFSET    (24)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IOPORT private control block. DO NOT MODIFY. Initialization occurs when R_IOPORT_Open() is called. */
typedef struct st_ioport_instance_ctrl
{
    uint32_t     open;
    void const * p_context;
} ioport_instance_ctrl_t;

/* This typedef is here temporarily. See SWFLEX-144 for details. */
/** Superset list of all possible IO port pins. */
typedef enum e_ioport_port_pin_t
{
    IOPORT_PORT_00_PIN_00 = 0x0000,    ///< IO port 0 pin 0
    IOPORT_PORT_00_PIN_01 = 0x0001,    ///< IO port 0 pin 1
    IOPORT_PORT_00_PIN_02 = 0x0002,    ///< IO port 0 pin 2
    IOPORT_PORT_00_PIN_03 = 0x0003,    ///< IO port 0 pin 3
    IOPORT_PORT_00_PIN_04 = 0x0004,    ///< IO port 0 pin 4
    IOPORT_PORT_00_PIN_05 = 0x0005,    ///< IO port 0 pin 5
    IOPORT_PORT_00_PIN_06 = 0x0006,    ///< IO port 0 pin 6
    IOPORT_PORT_00_PIN_07 = 0x0007,    ///< IO port 0 pin 7
    IOPORT_PORT_00_PIN_08 = 0x0008,    ///< IO port 0 pin 8
    IOPORT_PORT_00_PIN_09 = 0x0009,    ///< IO port 0 pin 9
    IOPORT_PORT_00_PIN_10 = 0x000A,    ///< IO port 0 pin 10
    IOPORT_PORT_00_PIN_11 = 0x000B,    ///< IO port 0 pin 11
    IOPORT_PORT_00_PIN_12 = 0x000C,    ///< IO port 0 pin 12
    IOPORT_PORT_00_PIN_13 = 0x000D,    ///< IO port 0 pin 13
    IOPORT_PORT_00_PIN_14 = 0x000E,    ///< IO port 0 pin 14
    IOPORT_PORT_00_PIN_15 = 0x000F,    ///< IO port 0 pin 15

    IOPORT_PORT_01_PIN_00 = 0x0100,    ///< IO port 1 pin 0
    IOPORT_PORT_01_PIN_01 = 0x0101,    ///< IO port 1 pin 1
    IOPORT_PORT_01_PIN_02 = 0x0102,    ///< IO port 1 pin 2
    IOPORT_PORT_01_PIN_03 = 0x0103,    ///< IO port 1 pin 3
    IOPORT_PORT_01_PIN_04 = 0x0104,    ///< IO port 1 pin 4
    IOPORT_PORT_01_PIN_05 = 0x0105,    ///< IO port 1 pin 5
    IOPORT_PORT_01_PIN_06 = 0x0106,    ///< IO port 1 pin 6
    IOPORT_PORT_01_PIN_07 = 0x0107,    ///< IO port 1 pin 7
    IOPORT_PORT_01_PIN_08 = 0x0108,    ///< IO port 1 pin 8
    IOPORT_PORT_01_PIN_09 = 0x0109,    ///< IO port 1 pin 9
    IOPORT_PORT_01_PIN_10 = 0x010A,    ///< IO port 1 pin 10
    IOPORT_PORT_01_PIN_11 = 0x010B,    ///< IO port 1 pin 11
    IOPORT_PORT_01_PIN_12 = 0x010C,    ///< IO port 1 pin 12
    IOPORT_PORT_01_PIN_13 = 0x010D,    ///< IO port 1 pin 13
    IOPORT_PORT_01_PIN_14 = 0x010E,    ///< IO port 1 pin 14
    IOPORT_PORT_01_PIN_15 = 0x010F,    ///< IO port 1 pin 15

    IOPORT_PORT_02_PIN_00 = 0x0200,    ///< IO port 2 pin 0
    IOPORT_PORT_02_PIN_01 = 0x0201,    ///< IO port 2 pin 1
    IOPORT_PORT_02_PIN_02 = 0x0202,    ///< IO port 2 pin 2
    IOPORT_PORT_02_PIN_03 = 0x0203,    ///< IO port 2 pin 3
    IOPORT_PORT_02_PIN_04 = 0x0204,    ///< IO port 2 pin 4
    IOPORT_PORT_02_PIN_05 = 0x0205,    ///< IO port 2 pin 5
    IOPORT_PORT_02_PIN_06 = 0x0206,    ///< IO port 2 pin 6
    IOPORT_PORT_02_PIN_07 = 0x0207,    ///< IO port 2 pin 7
    IOPORT_PORT_02_PIN_08 = 0x0208,    ///< IO port 2 pin 8
    IOPORT_PORT_02_PIN_09 = 0x0209,    ///< IO port 2 pin 9
    IOPORT_PORT_02_PIN_10 = 0x020A,    ///< IO port 2 pin 10
    IOPORT_PORT_02_PIN_11 = 0x020B,    ///< IO port 2 pin 11
    IOPORT_PORT_02_PIN_12 = 0x020C,    ///< IO port 2 pin 12
    IOPORT_PORT_02_PIN_13 = 0x020D,    ///< IO port 2 pin 13
    IOPORT_PORT_02_PIN_14 = 0x020E,    ///< IO port 2 pin 14
    IOPORT_PORT_02_PIN_15 = 0x020F,    ///< IO port 2 pin 15

    IOPORT_PORT_03_PIN_00 = 0x0300,    ///< IO port 3 pin 0
    IOPORT_PORT_03_PIN_01 = 0x0301,    ///< IO port 3 pin 1
    IOPORT_PORT_03_PIN_02 = 0x0302,    ///< IO port 3 pin 2
    IOPORT_PORT_03_PIN_03 = 0x0303,    ///< IO port 3 pin 3
    IOPORT_PORT_03_PIN_04 = 0x0304,    ///< IO port 3 pin 4
    IOPORT_PORT_03_PIN_05 = 0x0305,    ///< IO port 3 pin 5
    IOPORT_PORT_03_PIN_06 = 0x0306,    ///< IO port 3 pin 6
    IOPORT_PORT_03_PIN_07 = 0x0307,    ///< IO port 3 pin 7
    IOPORT_PORT_03_PIN_08 = 0x0308,    ///< IO port 3 pin 8
    IOPORT_PORT_03_PIN_09 = 0x0309,    ///< IO port 3 pin 9
    IOPORT_PORT_03_PIN_10 = 0x030A,    ///< IO port 3 pin 10
    IOPORT_PORT_03_PIN_11 = 0x030B,    ///< IO port 3 pin 11
    IOPORT_PORT_03_PIN_12 = 0x030C,    ///< IO port 3 pin 12
    IOPORT_PORT_03_PIN_13 = 0x030D,    ///< IO port 3 pin 13
    IOPORT_PORT_03_PIN_14 = 0x030E,    ///< IO port 3 pin 14
    IOPORT_PORT_03_PIN_15 = 0x030F,    ///< IO port 3 pin 15

    IOPORT_PORT_04_PIN_00 = 0x0400,    ///< IO port 4 pin 0
    IOPORT_PORT_04_PIN_01 = 0x0401,    ///< IO port 4 pin 1
    IOPORT_PORT_04_PIN_02 = 0x0402,    ///< IO port 4 pin 2
    IOPORT_PORT_04_PIN_03 = 0x0403,    ///< IO port 4 pin 3
    IOPORT_PORT_04_PIN_04 = 0x0404,    ///< IO port 4 pin 4
    IOPORT_PORT_04_PIN_05 = 0x0405,    ///< IO port 4 pin 5
    IOPORT_PORT_04_PIN_06 = 0x0406,    ///< IO port 4 pin 6
    IOPORT_PORT_04_PIN_07 = 0x0407,    ///< IO port 4 pin 7
    IOPORT_PORT_04_PIN_08 = 0x0408,    ///< IO port 4 pin 8
    IOPORT_PORT_04_PIN_09 = 0x0409,    ///< IO port 4 pin 9
    IOPORT_PORT_04_PIN_10 = 0x040A,    ///< IO port 4 pin 10
    IOPORT_PORT_04_PIN_11 = 0x040B,    ///< IO port 4 pin 11
    IOPORT_PORT_04_PIN_12 = 0x040C,    ///< IO port 4 pin 12
    IOPORT_PORT_04_PIN_13 = 0x040D,    ///< IO port 4 pin 13
    IOPORT_PORT_04_PIN_14 = 0x040E,    ///< IO port 4 pin 14
    IOPORT_PORT_04_PIN_15 = 0x040F,    ///< IO port 4 pin 15

    IOPORT_PORT_05_PIN_00 = 0x0500,    ///< IO port 5 pin 0
    IOPORT_PORT_05_PIN_01 = 0x0501,    ///< IO port 5 pin 1
    IOPORT_PORT_05_PIN_02 = 0x0502,    ///< IO port 5 pin 2
    IOPORT_PORT_05_PIN_03 = 0x0503,    ///< IO port 5 pin 3
    IOPORT_PORT_05_PIN_04 = 0x0504,    ///< IO port 5 pin 4
    IOPORT_PORT_05_PIN_05 = 0x0505,    ///< IO port 5 pin 5
    IOPORT_PORT_05_PIN_06 = 0x0506,    ///< IO port 5 pin 6
    IOPORT_PORT_05_PIN_07 = 0x0507,    ///< IO port 5 pin 7
    IOPORT_PORT_05_PIN_08 = 0x0508,    ///< IO port 5 pin 8
    IOPORT_PORT_05_PIN_09 = 0x0509,    ///< IO port 5 pin 9
    IOPORT_PORT_05_PIN_10 = 0x050A,    ///< IO port 5 pin 10
    IOPORT_PORT_05_PIN_11 = 0x050B,    ///< IO port 5 pin 11
    IOPORT_PORT_05_PIN_12 = 0x050C,    ///< IO port 5 pin 12
    IOPORT_PORT_05_PIN_13 = 0x050D,    ///< IO port 5 pin 13
    IOPORT_PORT_05_PIN_14 = 0x050E,    ///< IO port 5 pin 14
    IOPORT_PORT_05_PIN_15 = 0x050F,    ///< IO port 5 pin 15

    IOPORT_PORT_06_PIN_00 = 0x0600,    ///< IO port 6 pin 0
    IOPORT_PORT_06_PIN_01 = 0x0601,    ///< IO port 6 pin 1
    IOPORT_PORT_06_PIN_02 = 0x0602,    ///< IO port 6 pin 2
    IOPORT_PORT_06_PIN_03 = 0x0603,    ///< IO port 6 pin 3
    IOPORT_PORT_06_PIN_04 = 0x0604,    ///< IO port 6 pin 4
    IOPORT_PORT_06_PIN_05 = 0x0605,    ///< IO port 6 pin 5
    IOPORT_PORT_06_PIN_06 = 0x0606,    ///< IO port 6 pin 6
    IOPORT_PORT_06_PIN_07 = 0x0607,    ///< IO port 6 pin 7
    IOPORT_PORT_06_PIN_08 = 0x0608,    ///< IO port 6 pin 8
    IOPORT_PORT_06_PIN_09 = 0x0609,    ///< IO port 6 pin 9
    IOPORT_PORT_06_PIN_10 = 0x060A,    ///< IO port 6 pin 10
    IOPORT_PORT_06_PIN_11 = 0x060B,    ///< IO port 6 pin 11
    IOPORT_PORT_06_PIN_12 = 0x060C,    ///< IO port 6 pin 12
    IOPORT_PORT_06_PIN_13 = 0x060D,    ///< IO port 6 pin 13
    IOPORT_PORT_06_PIN_14 = 0x060E,    ///< IO port 6 pin 14
    IOPORT_PORT_06_PIN_15 = 0x060F,    ///< IO port 6 pin 15

    IOPORT_PORT_07_PIN_00 = 0x0700,    ///< IO port 7 pin 0
    IOPORT_PORT_07_PIN_01 = 0x0701,    ///< IO port 7 pin 1
    IOPORT_PORT_07_PIN_02 = 0x0702,    ///< IO port 7 pin 2
    IOPORT_PORT_07_PIN_03 = 0x0703,    ///< IO port 7 pin 3
    IOPORT_PORT_07_PIN_04 = 0x0704,    ///< IO port 7 pin 4
    IOPORT_PORT_07_PIN_05 = 0x0705,    ///< IO port 7 pin 5
    IOPORT_PORT_07_PIN_06 = 0x0706,    ///< IO port 7 pin 6
    IOPORT_PORT_07_PIN_07 = 0x0707,    ///< IO port 7 pin 7
    IOPORT_PORT_07_PIN_08 = 0x0708,    ///< IO port 7 pin 8
    IOPORT_PORT_07_PIN_09 = 0x0709,    ///< IO port 7 pin 9
    IOPORT_PORT_07_PIN_10 = 0x070A,    ///< IO port 7 pin 10
    IOPORT_PORT_07_PIN_11 = 0x070B,    ///< IO port 7 pin 11
    IOPORT_PORT_07_PIN_12 = 0x070C,    ///< IO port 7 pin 12
    IOPORT_PORT_07_PIN_13 = 0x070D,    ///< IO port 7 pin 13
    IOPORT_PORT_07_PIN_14 = 0x070E,    ///< IO port 7 pin 14
    IOPORT_PORT_07_PIN_15 = 0x070F,    ///< IO port 7 pin 15

    IOPORT_PORT_08_PIN_00 = 0x0800,    ///< IO port 8 pin 0
    IOPORT_PORT_08_PIN_01 = 0x0801,    ///< IO port 8 pin 1
    IOPORT_PORT_08_PIN_02 = 0x0802,    ///< IO port 8 pin 2
    IOPORT_PORT_08_PIN_03 = 0x0803,    ///< IO port 8 pin 3
    IOPORT_PORT_08_PIN_04 = 0x0804,    ///< IO port 8 pin 4
    IOPORT_PORT_08_PIN_05 = 0x0805,    ///< IO port 8 pin 5
    IOPORT_PORT_08_PIN_06 = 0x0806,    ///< IO port 8 pin 6
    IOPORT_PORT_08_PIN_07 = 0x0807,    ///< IO port 8 pin 7
    IOPORT_PORT_08_PIN_08 = 0x0808,    ///< IO port 8 pin 8
    IOPORT_PORT_08_PIN_09 = 0x0809,    ///< IO port 8 pin 9
    IOPORT_PORT_08_PIN_10 = 0x080A,    ///< IO port 8 pin 10
    IOPORT_PORT_08_PIN_11 = 0x080B,    ///< IO port 8 pin 11
    IOPORT_PORT_08_PIN_12 = 0x080C,    ///< IO port 8 pin 12
    IOPORT_PORT_08_PIN_13 = 0x080D,    ///< IO port 8 pin 13
    IOPORT_PORT_08_PIN_14 = 0x080E,    ///< IO port 8 pin 14
    IOPORT_PORT_08_PIN_15 = 0x080F,    ///< IO port 8 pin 15

    IOPORT_PORT_09_PIN_00 = 0x0900,    ///< IO port 9 pin 0
    IOPORT_PORT_09_PIN_01 = 0x0901,    ///< IO port 9 pin 1
    IOPORT_PORT_09_PIN_02 = 0x0902,    ///< IO port 9 pin 2
    IOPORT_PORT_09_PIN_03 = 0x0903,    ///< IO port 9 pin 3
    IOPORT_PORT_09_PIN_04 = 0x0904,    ///< IO port 9 pin 4
    IOPORT_PORT_09_PIN_05 = 0x0905,    ///< IO port 9 pin 5
    IOPORT_PORT_09_PIN_06 = 0x0906,    ///< IO port 9 pin 6
    IOPORT_PORT_09_PIN_07 = 0x0907,    ///< IO port 9 pin 7
    IOPORT_PORT_09_PIN_08 = 0x0908,    ///< IO port 9 pin 8
    IOPORT_PORT_09_PIN_09 = 0x0909,    ///< IO port 9 pin 9
    IOPORT_PORT_09_PIN_10 = 0x090A,    ///< IO port 9 pin 10
    IOPORT_PORT_09_PIN_11 = 0x090B,    ///< IO port 9 pin 11
    IOPORT_PORT_09_PIN_12 = 0x090C,    ///< IO port 9 pin 12
    IOPORT_PORT_09_PIN_13 = 0x090D,    ///< IO port 9 pin 13
    IOPORT_PORT_09_PIN_14 = 0x090E,    ///< IO port 9 pin 14
    IOPORT_PORT_09_PIN_15 = 0x090F,    ///< IO port 9 pin 15

    IOPORT_PORT_10_PIN_00 = 0x0A00,    ///< IO port 10 pin 0
    IOPORT_PORT_10_PIN_01 = 0x0A01,    ///< IO port 10 pin 1
    IOPORT_PORT_10_PIN_02 = 0x0A02,    ///< IO port 10 pin 2
    IOPORT_PORT_10_PIN_03 = 0x0A03,    ///< IO port 10 pin 3
    IOPORT_PORT_10_PIN_04 = 0x0A04,    ///< IO port 10 pin 4
    IOPORT_PORT_10_PIN_05 = 0x0A05,    ///< IO port 10 pin 5
    IOPORT_PORT_10_PIN_06 = 0x0A06,    ///< IO port 10 pin 6
    IOPORT_PORT_10_PIN_07 = 0x0A07,    ///< IO port 10 pin 7
    IOPORT_PORT_10_PIN_08 = 0x0A08,    ///< IO port 10 pin 8
    IOPORT_PORT_10_PIN_09 = 0x0A09,    ///< IO port 10 pin 9
    IOPORT_PORT_10_PIN_10 = 0x0A0A,    ///< IO port 10 pin 10
    IOPORT_PORT_10_PIN_11 = 0x0A0B,    ///< IO port 10 pin 11
    IOPORT_PORT_10_PIN_12 = 0x0A0C,    ///< IO port 10 pin 12
    IOPORT_PORT_10_PIN_13 = 0x0A0D,    ///< IO port 10 pin 13
    IOPORT_PORT_10_PIN_14 = 0x0A0E,    ///< IO port 10 pin 14
    IOPORT_PORT_10_PIN_15 = 0x0A0F,    ///< IO port 10 pin 15

    IOPORT_PORT_11_PIN_00 = 0x0B00,    ///< IO port 11 pin 0
    IOPORT_PORT_11_PIN_01 = 0x0B01,    ///< IO port 11 pin 1
    IOPORT_PORT_11_PIN_02 = 0x0B02,    ///< IO port 11 pin 2
    IOPORT_PORT_11_PIN_03 = 0x0B03,    ///< IO port 11 pin 3
    IOPORT_PORT_11_PIN_04 = 0x0B04,    ///< IO port 11 pin 4
    IOPORT_PORT_11_PIN_05 = 0x0B05,    ///< IO port 11 pin 5
    IOPORT_PORT_11_PIN_06 = 0x0B06,    ///< IO port 11 pin 6
    IOPORT_PORT_11_PIN_07 = 0x0B07,    ///< IO port 11 pin 7
    IOPORT_PORT_11_PIN_08 = 0x0B08,    ///< IO port 11 pin 8
    IOPORT_PORT_11_PIN_09 = 0x0B09,    ///< IO port 11 pin 9
    IOPORT_PORT_11_PIN_10 = 0x0B0A,    ///< IO port 11 pin 10
    IOPORT_PORT_11_PIN_11 = 0x0B0B,    ///< IO port 11 pin 11
    IOPORT_PORT_11_PIN_12 = 0x0B0C,    ///< IO port 11 pin 12
    IOPORT_PORT_11_PIN_13 = 0x0B0D,    ///< IO port 11 pin 13
    IOPORT_PORT_11_PIN_14 = 0x0B0E,    ///< IO port 11 pin 14
    IOPORT_PORT_11_PIN_15 = 0x0B0F,    ///< IO port 11 pin 15

    IOPORT_PORT_12_PIN_00 = 0x0C00,    ///< IO port 12 pin 0
    IOPORT_PORT_12_PIN_01 = 0x0C01,    ///< IO port 12 pin 1
    IOPORT_PORT_12_PIN_02 = 0x0C02,    ///< IO port 12 pin 2
    IOPORT_PORT_12_PIN_03 = 0x0C03,    ///< IO port 12 pin 3
    IOPORT_PORT_12_PIN_04 = 0x0C04,    ///< IO port 12 pin 4
    IOPORT_PORT_12_PIN_05 = 0x0C05,    ///< IO port 12 pin 5
    IOPORT_PORT_12_PIN_06 = 0x0C06,    ///< IO port 12 pin 6
    IOPORT_PORT_12_PIN_07 = 0x0C07,    ///< IO port 12 pin 7
    IOPORT_PORT_12_PIN_08 = 0x0C08,    ///< IO port 12 pin 8
    IOPORT_PORT_12_PIN_09 = 0x0C09,    ///< IO port 12 pin 9
    IOPORT_PORT_12_PIN_10 = 0x0C0A,    ///< IO port 12 pin 10
    IOPORT_PORT_12_PIN_11 = 0x0C0B,    ///< IO port 12 pin 11
    IOPORT_PORT_12_PIN_12 = 0x0C0C,    ///< IO port 12 pin 12
    IOPORT_PORT_12_PIN_13 = 0x0C0D,    ///< IO port 12 pin 13
    IOPORT_PORT_12_PIN_14 = 0x0C0E,    ///< IO port 12 pin 14
    IOPORT_PORT_12_PIN_15 = 0x0C0F,    ///< IO port 12 pin 15

    IOPORT_PORT_13_PIN_00 = 0x0D00,    ///< IO port 13 pin 0
    IOPORT_PORT_13_PIN_01 = 0x0D01,    ///< IO port 13 pin 1
    IOPORT_PORT_13_PIN_02 = 0x0D02,    ///< IO port 13 pin 2
    IOPORT_PORT_13_PIN_03 = 0x0D03,    ///< IO port 13 pin 3
    IOPORT_PORT_13_PIN_04 = 0x0D04,    ///< IO port 13 pin 4
    IOPORT_PORT_13_PIN_05 = 0x0D05,    ///< IO port 13 pin 5
    IOPORT_PORT_13_PIN_06 = 0x0D06,    ///< IO port 13 pin 6
    IOPORT_PORT_13_PIN_07 = 0x0D07,    ///< IO port 13 pin 7
    IOPORT_PORT_13_PIN_08 = 0x0D08,    ///< IO port 13 pin 8
    IOPORT_PORT_13_PIN_09 = 0x0D09,    ///< IO port 13 pin 9
    IOPORT_PORT_13_PIN_10 = 0x0D0A,    ///< IO port 13 pin 10
    IOPORT_PORT_13_PIN_11 = 0x0D0B,    ///< IO port 13 pin 11
    IOPORT_PORT_13_PIN_12 = 0x0D0C,    ///< IO port 13 pin 12
    IOPORT_PORT_13_PIN_13 = 0x0D0D,    ///< IO port 13 pin 13
    IOPORT_PORT_13_PIN_14 = 0x0D0E,    ///< IO port 13 pin 14
    IOPORT_PORT_13_PIN_15 = 0x0D0F,    ///< IO port 13 pin 15

    IOPORT_PORT_14_PIN_00 = 0x0E00,    ///< IO port 14 pin 0
    IOPORT_PORT_14_PIN_01 = 0x0E01,    ///< IO port 14 pin 1
    IOPORT_PORT_14_PIN_02 = 0x0E02,    ///< IO port 14 pin 2
    IOPORT_PORT_14_PIN_03 = 0x0E03,    ///< IO port 14 pin 3
    IOPORT_PORT_14_PIN_04 = 0x0E04,    ///< IO port 14 pin 4
    IOPORT_PORT_14_PIN_05 = 0x0E05,    ///< IO port 14 pin 5
    IOPORT_PORT_14_PIN_06 = 0x0E06,    ///< IO port 14 pin 6
    IOPORT_PORT_14_PIN_07 = 0x0E07,    ///< IO port 14 pin 7
    IOPORT_PORT_14_PIN_08 = 0x0E08,    ///< IO port 14 pin 8
    IOPORT_PORT_14_PIN_09 = 0x0E09,    ///< IO port 14 pin 9
    IOPORT_PORT_14_PIN_10 = 0x0E0A,    ///< IO port 14 pin 10
    IOPORT_PORT_14_PIN_11 = 0x0E0B,    ///< IO port 14 pin 11
    IOPORT_PORT_14_PIN_12 = 0x0E0C,    ///< IO port 14 pin 12
    IOPORT_PORT_14_PIN_13 = 0x0E0D,    ///< IO port 14 pin 13
    IOPORT_PORT_14_PIN_14 = 0x0E0E,    ///< IO port 14 pin 14
    IOPORT_PORT_14_PIN_15 = 0x0E0F,    ///< IO port 14 pin 15
} ioport_port_pin_t;

/** Superset of all peripheral functions.  */
typedef enum e_ioport_peripheral
{
    /** Pin will functions as an IO pin */
    IOPORT_PERIPHERAL_IO = 0x00,

    /** Pin will function as a DEBUG pin */
    IOPORT_PERIPHERAL_DEBUG = (0x00UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGT = (0x01UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGTW = (0x01UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGT1 = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT0 = (0x02UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT1 = (0x03UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI0_2_4_6_8 = (0x04UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI1_3_5_7_9 = (0x05UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a SPI peripheral pin */
    IOPORT_PERIPHERAL_SPI = (0x06UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a IIC peripheral pin */
    IOPORT_PERIPHERAL_IIC = (0x07UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a KEY peripheral pin */
    IOPORT_PERIPHERAL_KEY = (0x08UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a clock/comparator/RTC peripheral pin */
    IOPORT_PERIPHERAL_CLKOUT_COMP_RTC = (0x09UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC/ADC peripheral pin */
    IOPORT_PERIPHERAL_CAC_AD = (0x0AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a BUS peripheral pin */
    IOPORT_PERIPHERAL_BUS = (0x0BUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CTSU peripheral pin */
    IOPORT_PERIPHERAL_CTSU = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CMPHS peripheral pin */
    IOPORT_PERIPHERAL_ACMPHS = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a segment LCD peripheral pin */
    IOPORT_PERIPHERAL_LCDC = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

#if BSP_FEATURE_SCI_UART_DE_IS_INVERTED

    /** Pin will function as an SCI peripheral DEn pin */
    IOPORT_PERIPHERAL_DE_SCI1_3_5_7_9 = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI DEn peripheral pin */
    IOPORT_PERIPHERAL_DE_SCI0_2_4_6_8 = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),
#else

    /** Pin will function as an SCI peripheral DEn pin */
    IOPORT_PERIPHERAL_DE_SCI0_2_4_6_8 = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI DEn peripheral pin */
    IOPORT_PERIPHERAL_DE_SCI1_3_5_7_9 = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),
#endif

    /** Pin will function as a DALI peripheral pin */
    IOPORT_PERIPHERAL_DALI = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CEU peripheral pin */
    IOPORT_PERIPHERAL_CEU = (0x0FUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAN peripheral pin */
    IOPORT_PERIPHERAL_CAN = (0x10UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a QSPI peripheral pin */
    IOPORT_PERIPHERAL_QSPI = (0x11UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SSI peripheral pin */
    IOPORT_PERIPHERAL_SSI = (0x12UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB full speed peripheral pin */
    IOPORT_PERIPHERAL_USB_FS = (0x13UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB high speed peripheral pin */
    IOPORT_PERIPHERAL_USB_HS = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT2 = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SD/MMC peripheral pin */
    IOPORT_PERIPHERAL_SDHI_MMC = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT3 = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet MMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_MII = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT4 = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet RMMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_RMII = (0x17UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PDC peripheral pin */
    IOPORT_PERIPHERAL_PDC = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a graphics LCD peripheral pin */
    IOPORT_PERIPHERAL_LCD_GRAPHICS = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC peripheral pin */
    IOPORT_PERIPHERAL_CAC = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a debug trace peripheral pin */
    IOPORT_PERIPHERAL_TRACE = (0x1AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a OSPI peripheral pin */
    IOPORT_PERIPHERAL_OSPI = (0x1CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CEC peripheral pin */
    IOPORT_PERIPHERAL_CEC = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT0 = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT1 = (0x1EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a ULPT peripheral pin */
    IOPORT_PERIPHERAL_ULPT = (0x1EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a MIPI DSI peripheral pin */
    IOPORT_PERIPHERAL_MIPI = (0x1FUL << IOPORT_PRV_PFS_PSEL_OFFSET),
} ioport_peripheral_t;

/** Options to configure pin functions  */
typedef enum e_ioport_cfg_options
{
    IOPORT_CFG_PORT_DIRECTION_INPUT  = 0x00000000, ///< Sets the pin direction to input (default)
    IOPORT_CFG_PORT_DIRECTION_OUTPUT = 0x00000004, ///< Sets the pin direction to output
    IOPORT_CFG_PORT_OUTPUT_LOW       = 0x00000000, ///< Sets the pin level to low
    IOPORT_CFG_PORT_OUTPUT_HIGH      = 0x00000001, ///< Sets the pin level to high
    IOPORT_CFG_PULLUP_ENABLE         = 0x00000010, ///< Enables the pin's internal pull-up
    IOPORT_CFG_PIM_TTL               = 0x00000020, ///< Enables the pin's input mode
    IOPORT_CFG_NMOS_ENABLE           = 0x00000040, ///< Enables the pin's NMOS open-drain output
    IOPORT_CFG_PMOS_ENABLE           = 0x00000080, ///< Enables the pin's PMOS open-drain ouput
    IOPORT_CFG_DRIVE_MID             = 0x00000400, ///< Sets pin drive output to medium
    IOPORT_CFG_DRIVE_HS_HIGH         = 0x00000800, ///< Sets pin drive output to high along with supporting high speed
    IOPORT_CFG_DRIVE_MID_IIC         = 0x00000C00, ///< Sets pin to drive output needed for IIC on a 20mA port
    IOPORT_CFG_DRIVE_HIGH            = 0x00000C00, ///< Sets pin drive output to high
    IOPORT_CFG_EVENT_RISING_EDGE     = 0x00001000, ///< Sets pin event trigger to rising edge
    IOPORT_CFG_EVENT_FALLING_EDGE    = 0x00002000, ///< Sets pin event trigger to falling edge
    IOPORT_CFG_EVENT_BOTH_EDGES      = 0x00003000, ///< Sets pin event trigger to both edges
    IOPORT_CFG_IRQ_ENABLE            = 0x00004000, ///< Sets pin as an IRQ pin
    IOPORT_CFG_ANALOG_ENABLE         = 0x00008000, ///< Enables pin to operate as an analog pin
    IOPORT_CFG_PERIPHERAL_PIN        = 0x00010000  ///< Enables pin to operate as a peripheral pin
} ioport_cfg_options_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ioport_api_t g_ioport_on_ioport;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_IOPORT_Open(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_IOPORT_Close(ioport_ctrl_t * const p_ctrl);
fsp_err_t R_IOPORT_PinsCfg(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_IOPORT_PinCfg(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);
fsp_err_t R_IOPORT_PinEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event);
fsp_err_t R_IOPORT_PinEventOutputWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value);
fsp_err_t R_IOPORT_PinRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);
fsp_err_t R_IOPORT_PinWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level);
fsp_err_t R_IOPORT_PortDirectionSet(ioport_ctrl_t * const p_ctrl,
                                    bsp_io_port_t         port,
                                    ioport_size_t         direction_values,
                                    ioport_size_t         mask);
fsp_err_t R_IOPORT_PortEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * event_data);
fsp_err_t R_IOPORT_PortEventOutputWrite(ioport_ctrl_t * const p_ctrl,
                                        bsp_io_port_t         port,
                                        ioport_size_t         event_data,
                                        ioport_size_t         mask_value);
fsp_err_t R_IOPORT_PortRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value);
fsp_err_t R_IOPORT_PortWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask);

/*******************************************************************************************************************//**
 * @} (end defgroup IOPORT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IOPORT_H
