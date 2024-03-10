/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdk.h"
#include "camera/camera_def.h"
#include "registers/regsiomuxc.h"
#include "registers/regsccm.h"

#define CAMERA_I2C_PORT (1)

void camera_ipu1_iomux_config(void);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

uint8_t g_camera_i2c_port = CAMERA_I2C_PORT;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/* dummy empty function for camera_test
 * camera power is always on for MX6DQ SMD board*/
void camera_power_on(void)
{
}

/*IOMUX configuration for CSI port0*/
void csi_port0_iomux_config(void)
{
    camera_ipu1_iomux_config();

    /* set GPR1 to enable parallel interface
     * bit 19: 0 - Enable mipi to IPU1 CSI0, virtual channel is fixed to 0
     *         1 - Enable parallel interface to IPU CSI0
     * bit 20: 0 - Enable mipi to IPU2 CSI1, virtual channel is fixed to 3
     *         1 - Enable parallel interface to IPU2 CSI1
     * IPU1 CSI1 directly connect to mipi CSI2, virtual channel is fixed to 1
     * IPU2 CSI0 directly connect to mipi CSI2, virtual channel is fixed to 2
     */

#if defined(CHIP_MX6DQ)
    BW_IOMUXC_GPR1_MIPI_IPU1_MUX(1/*PARALLEL_INTERFACE*/);
#endif
#if defined(CHIP_MX6SDL)
    BW_IOMUXC_GPR13_IPU_CSI0_MUX(4/*IPU_CSI0*/);
#endif

}


//! @brief Function to configure IOMUXC for ipu1 module.
//! @todo Move this function to [chip]/[board]/iomuxc folders?
void camera_ipu1_iomux_config(void)
{
    // Config ipu1.IPU1_CSI0_DATA12 to pad CSI0_DATA12(M2)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA12_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA12(0x020E0288)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA12
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA08
    //     ALT3 (3) - Select instance: uart4 signal: UART4_TX_DATA
    //     ALT5 (5) - Select instance: gpio5 signal: GPIO5_IO30
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE09
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA12_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA12_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA12_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12(0x020E0658)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_DATA13 to pad CSI0_DATA13(L1)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA13_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA13(0x020E028C)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA13
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA09
    //     ALT3 (3) - Select instance: uart4 signal: UART4_RX_DATA
    //     ALT5 (5) - Select instance: gpio5 signal: GPIO5_IO31
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE10
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA13_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA13_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA13_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13(0x020E065C)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_DATA14 to pad CSI0_DATA14(M4)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA14_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA14(0x020E0290)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA14
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA10
    //     ALT3 (3) - Select instance: uart5 signal: UART5_TX_DATA
    //     ALT5 (5) - Select instance: gpio6 signal: GPIO6_IO00
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE11
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA14_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA14_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA14_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14(0x020E0660)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_DATA15 to pad CSI0_DATA15(M5)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA15_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA15(0x020E0294)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA15
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA11
    //     ALT3 (3) - Select instance: uart5 signal: UART5_RX_DATA
    //     ALT5 (5) - Select instance: gpio6 signal: GPIO6_IO01
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE12
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA15_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA15_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA15_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15(0x020E0664)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_DATA16 to pad CSI0_DATA16(L4)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA16_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA16(0x020E0298)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA16
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA12
    //     ALT3 (3) - Select instance: uart4 signal: UART4_RTS_B
    //     ALT5 (5) - Select instance: gpio6 signal: GPIO6_IO02
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE13
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA16_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA16_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA16_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16(0x020E0668)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_DATA17 to pad CSI0_DATA17(L3)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA17_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA17(0x020E029C)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA17
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA13
    //     ALT3 (3) - Select instance: uart4 signal: UART4_CTS_B
    //     ALT5 (5) - Select instance: gpio6 signal: GPIO6_IO03
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE14
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA17_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA17_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA17_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17(0x020E066C)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_DATA18 to pad CSI0_DATA18(M6)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA18_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA18(0x020E02A0)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA18
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA14
    //     ALT3 (3) - Select instance: uart5 signal: UART5_RTS_B
    //     ALT5 (5) - Select instance: gpio6 signal: GPIO6_IO04
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE15
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA18_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA18_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA18_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18(0x020E0670)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_DATA19 to pad CSI0_DATA19(L6)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA19_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA19(0x020E02A4)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_DATA19
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA15
    //     ALT3 (3) - Select instance: uart5 signal: UART5_CTS_B
    //     ALT5 (5) - Select instance: gpio6 signal: GPIO6_IO05
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA19_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA19_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA19_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19(0x020E0674)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_HSYNC to pad CSI0_HSYNC(P4)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC(0x020E025C)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_HSYNC
    //     ALT3 (3) - Select instance: ccm signal: CCM_CLKO1
    //     ALT5 (5) - Select instance: gpio5 signal: GPIO5_IO19
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE_CTL
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC(0x020E062C)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_PIXCLK to pad CSI0_PIXCLK(P1)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_PIXCLK_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_PIXCLK(0x020E0258)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_PIXCLK
    //     ALT5 (5) - Select instance: gpio5 signal: GPIO5_IO18
    //     ALT7 (7) - Select instance: arm signal: ARM_EVENTO
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_PIXCLK_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_PIXCLK_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_PIXCLK_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK(0x020E0628)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK_SRE_V(SLOW));

    // Config ipu1.IPU1_CSI0_VSYNC to pad CSI0_VSYNC(N2)
    // HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_VSYNC_WR(0x00000000);
    // HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_WR(0x000130B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_CSI0_VSYNC(0x020E0264)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_CSI0_VSYNC
    //     ALT1 (1) - Select instance: eim signal: EIM_DATA01
    //     ALT5 (5) - Select instance: gpio5 signal: GPIO5_IO21
    //     ALT7 (7) - Select instance: arm signal: ARM_TRACE00
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_VSYNC_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_VSYNC_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_VSYNC_MUX_MODE_V(ALT0));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC(0x020E0634)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     TBD (0) - TBD
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC_SRE_V(SLOW));
}

/*!
 * reset camera sensor through GPIO on SMD board 
 *
 */
void sensor_reset(void)
{
    int32_t reset_occupy = 1000, reset_delay = 1000;

    sensor_standby(0);

    /* MX6DQ/SDL_SMART_DEVICE: camera reset through GPIO1_17 */
	BW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1_MUX_MODE__ALT5);
	gpio_set_direction(GPIO_PORT1, 17, GPIO_GDIR_OUTPUT);

	gpio_set_level(GPIO_PORT1, 17, GPIO_LOW_LEVEL);
    hal_delay_us(reset_occupy);

	gpio_set_level(GPIO_PORT1, 17, GPIO_HIGH_LEVEL);
    hal_delay_us(reset_delay);
}

/*!
 * set camera sensor to standby mode.
 *
 * @param	enable: specify whether set camera sensor to standby mode
 * 
 */
void sensor_standby(int32_t enable)
{
    /* MX6DQ/SDL_SMART_DEVICE: setting to gpio1_16, power down high active */
	BW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0_MUX_MODE__ALT5);
	gpio_set_direction(GPIO_PORT1, 16, GPIO_GDIR_OUTPUT);
    if (enable)
		gpio_set_level(GPIO_PORT1, 16, GPIO_HIGH_LEVEL);
    else
		gpio_set_level(GPIO_PORT1, 16, GPIO_LOW_LEVEL);
}

/*!
 * set camera sensor clock to 24MHz. 
 *
 */
void sensor_clock_setting(void)
{
    int32_t clock_delay = 1000;

    /*MX6DQ/SDL_SMART_DEVICE: config clko */
    /*config gpio_0 to be clko */
	BW_IOMUXC_SW_MUX_CTL_PAD_GPIO00_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO00_MUX_MODE__ALT0);

	BW_IOMUXC_SW_PAD_CTL_PAD_GPIO00_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_GPIO00_SRE__FAST);
	BW_IOMUXC_SW_PAD_CTL_PAD_GPIO00_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_GPIO00_DSE__80_OHM);

    /*select osc_clk 24MHz, CKO1 output drives cko2 clock */
	HW_CCM_CCOSR_WR(
			BF_CCM_CCOSR_CLKO2_EN(1) |
			BF_CCM_CCOSR_CLKO2_DIV(0) | /*div 1*/
			BF_CCM_CCOSR_CLKO2_SEL(0xe) | /*osc_clk*/
			BF_CCM_CCOSR_CLKO_SEL(1) |
			BF_CCM_CCOSR_CLKO1_EN(1) |
			BF_CCM_CCOSR_CLKO1_DIV(0)); /*div 1*/

    hal_delay_us(clock_delay);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
