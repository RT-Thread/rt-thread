/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_IOMUXC_H_
#define _FSL_IOMUXC_H_

#include "fsl_common.h"

/*!
 * @addtogroup iomuxc_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iomuxc"
#endif

/*! @name Driver version */
/*@{*/
/*! @brief IOMUXC driver version 1.0.0. */
#define FSL_IOMUXC_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/*!
 * @name Pin function ID
 * The pin function ID is a tuple of \<muxRegister muxMode inputRegister inputDaisy configRegister\>
 *
 * @{
 */
#define IOMUXC_PAD_DAP_TDI__JTAG_MUX_TDI                                    0x543c0000, 0x00, 0x543c03d8, 0x00, 0x543c01b0
#define IOMUXC_PAD_DAP_TDI__MQS2_LEFT                                       0x543c0000, 0x01, 0x0, 0x00, 0x543c01b0
#define IOMUXC_PAD_DAP_TDI__CAN2_TX                                         0x543c0000, 0x03, 0x0, 0x00, 0x543c01b0
#define IOMUXC_PAD_DAP_TDI__FLEXIO2_FLEXIO30                                0x543c0000, 0x04, 0x0, 0x00, 0x543c01b0
#define IOMUXC_PAD_DAP_TDI__GPIO3_IO28                                      0x543c0000, 0x05, 0x0, 0x00, 0x543c01b0
#define IOMUXC_PAD_DAP_TDI__LPUART5_RX                                      0x543c0000, 0x06, 0x543c0488, 0x00, 0x543c01b0
#define IOMUXC_PAD_DAP_TMS_SWDIO__JTAG_MUX_TMS                              0x543c0004, 0x00, 0x543c03dc, 0x00, 0x543c01b4
#define IOMUXC_PAD_DAP_TMS_SWDIO__FLEXIO2_FLEXIO31                          0x543c0004, 0x04, 0x0, 0x00, 0x543c01b4
#define IOMUXC_PAD_DAP_TMS_SWDIO__GPIO3_IO29                                0x543c0004, 0x05, 0x0, 0x00, 0x543c01b4
#define IOMUXC_PAD_DAP_TMS_SWDIO__LPUART5_RTS_B                             0x543c0004, 0x06, 0x0, 0x00, 0x543c01b4
#define IOMUXC_PAD_DAP_TCLK_SWCLK__JTAG_MUX_TCK                             0x543c0008, 0x00, 0x543c03d4, 0x00, 0x543c01b8
#define IOMUXC_PAD_DAP_TCLK_SWCLK__FLEXIO1_FLEXIO30                         0x543c0008, 0x04, 0x0, 0x00, 0x543c01b8
#define IOMUXC_PAD_DAP_TCLK_SWCLK__GPIO3_IO30                               0x543c0008, 0x05, 0x0, 0x00, 0x543c01b8
#define IOMUXC_PAD_DAP_TCLK_SWCLK__LPUART5_CTS_B                            0x543c0008, 0x06, 0x543c0484, 0x00, 0x543c01b8
#define IOMUXC_PAD_DAP_TDO_TRACESWO__JTAG_MUX_TDO                           0x543c000c, 0x00, 0x0, 0x00, 0x543c01bc
#define IOMUXC_PAD_DAP_TDO_TRACESWO__MQS2_RIGHT                             0x543c000c, 0x01, 0x0, 0x00, 0x543c01bc
#define IOMUXC_PAD_DAP_TDO_TRACESWO__CAN2_RX                                0x543c000c, 0x03, 0x543c0364, 0x00, 0x543c01bc
#define IOMUXC_PAD_DAP_TDO_TRACESWO__FLEXIO1_FLEXIO31                       0x543c000c, 0x04, 0x0, 0x00, 0x543c01bc
#define IOMUXC_PAD_DAP_TDO_TRACESWO__GPIO3_IO31                             0x543c000c, 0x05, 0x0, 0x00, 0x543c01bc
#define IOMUXC_PAD_DAP_TDO_TRACESWO__LPUART5_TX                             0x543c000c, 0x06, 0x543c048c, 0x00, 0x543c01bc
#define IOMUXC_PAD_GPIO_IO00__GPIO2_IO0                                     0x543c0010, 0x00, 0x0, 0x00, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO00__LPI2C3_SDA                                    0x543c0010, 0x01, 0x543c03f4, 0x00, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO00__MEDIAMIX_CAM_CLK                              0x543c0010, 0x02, 0x543c04bc, 0x00, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO00__MEDIAMIX_DISP_CLK                             0x543c0010, 0x03, 0x0, 0x00, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO00__LPSPI6_PCS0                                   0x543c0010, 0x04, 0x0, 0x00, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO00__LPUART5_TX                                    0x543c0010, 0x05, 0x543c048c, 0x01, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO00__LPI2C5_SDA                                    0x543c0010, 0x06, 0x543c0404, 0x00, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO00__FLEXIO1_FLEXIO0                               0x543c0010, 0x07, 0x543c036c, 0x00, 0x543c01c0
#define IOMUXC_PAD_GPIO_IO01__GPIO2_IO1                                     0x543c0014, 0x00, 0x0, 0x00, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO01__LPI2C3_SCL                                    0x543c0014, 0x01, 0x543c03f0, 0x00, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO01__MEDIAMIX_CAM_DATA0                            0x543c0014, 0x02, 0x543c0490, 0x00, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO01__MEDIAMIX_DISP_DE                              0x543c0014, 0x03, 0x0, 0x00, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO01__LPSPI6_SIN                                    0x543c0014, 0x04, 0x0, 0x00, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO01__LPUART5_RX                                    0x543c0014, 0x05, 0x543c0488, 0x01, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO01__LPI2C5_SCL                                    0x543c0014, 0x06, 0x543c0400, 0x00, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO01__FLEXIO1_FLEXIO1                               0x543c0014, 0x07, 0x543c0370, 0x00, 0x543c01c4
#define IOMUXC_PAD_GPIO_IO02__GPIO2_IO3                                     0x543c0018, 0x00, 0x0, 0x00, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO02__LPI2C4_SDA                                    0x543c0018, 0x01, 0x543c03fc, 0x00, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO02__MEDIAMIX_CAM_VSYNC                            0x543c0018, 0x02, 0x543c04c0, 0x00, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO02__MEDIAMIX_DISP_VSYNC                           0x543c0018, 0x03, 0x0, 0x00, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO02__LPSPI6_SOUT                                   0x543c0018, 0x04, 0x0, 0x00, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO02__LPUART5_CTS_B                                 0x543c0018, 0x05, 0x543c0484, 0x01, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO02__LPI2C6_SDA                                    0x543c0018, 0x06, 0x543c040c, 0x00, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO02__FLEXIO1_FLEXIO3                               0x543c0018, 0x07, 0x543c0374, 0x00, 0x543c01c8
#define IOMUXC_PAD_GPIO_IO03__GPIO2_IO3                                     0x543c001c, 0x00, 0x0, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO03__LPI2C4_SCL                                    0x543c001c, 0x01, 0x543c03f8, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO03__MEDIAMIX_CAM_HSYNC                            0x543c001c, 0x02, 0x543c04b8, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO03__MEDIAMIX_DISP_HSYNC                           0x543c001c, 0x03, 0x0, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO03__LPSPI6_SCK                                    0x543c001c, 0x04, 0x0, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO03__LPUART5_RTS_B                                 0x543c001c, 0x05, 0x0, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO03__LPI2C6_SCL                                    0x543c001c, 0x06, 0x543c0408, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO03__FLEXIO1_FLEXIO3                               0x543c001c, 0x07, 0x543c0378, 0x00, 0x543c01cc
#define IOMUXC_PAD_GPIO_IO04__GPIO2_IO4                                     0x543c0020, 0x00, 0x0, 0x00, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO04__TPM3_CH0                                      0x543c0020, 0x01, 0x0, 0x00, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO04__PDM_CLK                                       0x543c0020, 0x02, 0x0, 0x00, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO04__MEDIAMIX_DISP_DATA0                           0x543c0020, 0x03, 0x0, 0x00, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO04__LPSPI7_PCS0                                   0x543c0020, 0x04, 0x0, 0x00, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO04__LPUART6_TX                                    0x543c0020, 0x05, 0x0, 0x00, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO04__LPI2C6_SDA                                    0x543c0020, 0x06, 0x543c040c, 0x01, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO04__FLEXIO1_FLEXIO4                               0x543c0020, 0x07, 0x543c037c, 0x00, 0x543c01d0
#define IOMUXC_PAD_GPIO_IO05__GPIO2_IO5                                     0x543c0024, 0x00, 0x0, 0x00, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO05__TPM4_CH0                                      0x543c0024, 0x01, 0x0, 0x00, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO05__PDM_BIT_STREAM0                               0x543c0024, 0x02, 0x543c04c4, 0x00, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO05__MEDIAMIX_DISP_DATA1                           0x543c0024, 0x03, 0x0, 0x00, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO05__LPSPI7_SIN                                    0x543c0024, 0x04, 0x0, 0x00, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO05__LPUART6_RX                                    0x543c0024, 0x05, 0x0, 0x00, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO05__LPI2C6_SCL                                    0x543c0024, 0x06, 0x543c0408, 0x01, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO05__FLEXIO1_FLEXIO5                               0x543c0024, 0x07, 0x543c0380, 0x00, 0x543c01d4
#define IOMUXC_PAD_GPIO_IO06__GPIO2_IO6                                     0x543c0028, 0x00, 0x0, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO06__TPM5_CH0                                      0x543c0028, 0x01, 0x0, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO06__PDM_BIT_STREAM1                               0x543c0028, 0x02, 0x543c04c8, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO06__MEDIAMIX_DISP_DATA2                           0x543c0028, 0x03, 0x0, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO06__LPSPI7_SOUT                                   0x543c0028, 0x04, 0x0, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO06__LPUART6_CTS_B                                 0x543c0028, 0x05, 0x0, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO06__LPI2C7_SDA                                    0x543c0028, 0x06, 0x543c0414, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO06__FLEXIO1_FLEXIO6                               0x543c0028, 0x07, 0x543c0384, 0x00, 0x543c01d8
#define IOMUXC_PAD_GPIO_IO07__GPIO2_IO7                                     0x543c002c, 0x00, 0x0, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO07__LPSPI3_PCS1                                   0x543c002c, 0x01, 0x0, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO07__MEDIAMIX_CAM_DATA1                            0x543c002c, 0x02, 0x543c0494, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO07__MEDIAMIX_DISP_DATA3                           0x543c002c, 0x03, 0x0, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO07__LPSPI7_SCK                                    0x543c002c, 0x04, 0x0, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO07__LPUART6_RTS_B                                 0x543c002c, 0x05, 0x0, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO07__LPI2C7_SCL                                    0x543c002c, 0x06, 0x543c0410, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO07__FLEXIO1_FLEXIO7                               0x543c002c, 0x07, 0x543c0388, 0x00, 0x543c01dc
#define IOMUXC_PAD_GPIO_IO08__GPIO2_IO8                                     0x543c0030, 0x00, 0x0, 0x00, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO08__LPSPI3_PCS0                                   0x543c0030, 0x01, 0x0, 0x00, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO08__MEDIAMIX_CAM_DATA2                            0x543c0030, 0x02, 0x543c0498, 0x00, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO08__MEDIAMIX_DISP_DATA4                           0x543c0030, 0x03, 0x0, 0x00, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO08__TPM6_CH0                                      0x543c0030, 0x04, 0x0, 0x00, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO08__LPUART7_TX                                    0x543c0030, 0x05, 0x0, 0x00, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO08__LPI2C7_SDA                                    0x543c0030, 0x06, 0x543c0414, 0x01, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO08__FLEXIO1_FLEXIO8                               0x543c0030, 0x07, 0x543c038c, 0x00, 0x543c01e0
#define IOMUXC_PAD_GPIO_IO09__GPIO2_IO9                                     0x543c0034, 0x00, 0x0, 0x00, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO09__LPSPI3_SIN                                    0x543c0034, 0x01, 0x0, 0x00, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO09__MEDIAMIX_CAM_DATA3                            0x543c0034, 0x02, 0x543c049c, 0x00, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO09__MEDIAMIX_DISP_DATA5                           0x543c0034, 0x03, 0x0, 0x00, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO09__TPM3_EXTCLK                                   0x543c0034, 0x04, 0x0, 0x00, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO09__LPUART7_RX                                    0x543c0034, 0x05, 0x0, 0x00, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO09__LPI2C7_SCL                                    0x543c0034, 0x06, 0x543c0410, 0x01, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO09__FLEXIO1_FLEXIO9                               0x543c0034, 0x07, 0x543c0390, 0x00, 0x543c01e4
#define IOMUXC_PAD_GPIO_IO10__GPIO2_IO10                                    0x543c0038, 0x00, 0x0, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO10__LPSPI3_SOUT                                   0x543c0038, 0x01, 0x0, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO10__MEDIAMIX_CAM_DATA4                            0x543c0038, 0x02, 0x543c04a0, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO10__MEDIAMIX_DISP_DATA6                           0x543c0038, 0x03, 0x0, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO10__TPM4_EXTCLK                                   0x543c0038, 0x04, 0x0, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO10__LPUART7_CTS_B                                 0x543c0038, 0x05, 0x0, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO10__LPI2C8_SDA                                    0x543c0038, 0x06, 0x543c041c, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO10__FLEXIO1_FLEXIO10                              0x543c0038, 0x07, 0x543c0394, 0x00, 0x543c01e8
#define IOMUXC_PAD_GPIO_IO11__GPIO2_IO11                                    0x543c003c, 0x00, 0x0, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO11__LPSPI3_SCK                                    0x543c003c, 0x01, 0x0, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO11__MEDIAMIX_CAM_DATA5                            0x543c003c, 0x02, 0x543c04a4, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO11__MEDIAMIX_DISP_DATA7                           0x543c003c, 0x03, 0x0, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO11__TPM5_EXTCLK                                   0x543c003c, 0x04, 0x0, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO11__LPUART7_RTS_B                                 0x543c003c, 0x05, 0x0, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO11__LPI2C8_SCL                                    0x543c003c, 0x06, 0x543c0418, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO11__FLEXIO1_FLEXIO11                              0x543c003c, 0x07, 0x543c0398, 0x00, 0x543c01ec
#define IOMUXC_PAD_GPIO_IO12__GPIO2_IO12                                    0x543c0040, 0x00, 0x0, 0x00, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO12__TPM3_CH2                                      0x543c0040, 0x01, 0x0, 0x00, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO12__PDM_BIT_STREAM2                               0x543c0040, 0x02, 0x543c04cc, 0x00, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO12__MEDIAMIX_DISP_DATA8                           0x543c0040, 0x03, 0x0, 0x00, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO12__LPSPI8_PCS0                                   0x543c0040, 0x04, 0x0, 0x00, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO12__LPUART8_TX                                    0x543c0040, 0x05, 0x0, 0x00, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO12__LPI2C8_SDA                                    0x543c0040, 0x06, 0x543c041c, 0x01, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO12__SAI3_RX_SYNC                                  0x543c0040, 0x07, 0x543c04dc, 0x00, 0x543c01f0
#define IOMUXC_PAD_GPIO_IO13__GPIO2_IO13                                    0x543c0044, 0x00, 0x0, 0x00, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO13__TPM4_CH2                                      0x543c0044, 0x01, 0x0, 0x00, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO13__PDM_BIT_STREAM3                               0x543c0044, 0x02, 0x543c04d0, 0x00, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO13__MEDIAMIX_DISP_DATA9                           0x543c0044, 0x03, 0x0, 0x00, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO13__LPSPI8_SIN                                    0x543c0044, 0x04, 0x0, 0x00, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO13__LPUART8_RX                                    0x543c0044, 0x05, 0x0, 0x00, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO13__LPI2C8_SCL                                    0x543c0044, 0x06, 0x543c0418, 0x01, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO13__FLEXIO1_FLEXIO13                              0x543c0044, 0x07, 0x543c039c, 0x00, 0x543c01f4
#define IOMUXC_PAD_GPIO_IO14__GPIO2_IO14                                    0x543c0048, 0x00, 0x0, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO14__LPUART3_TX                                    0x543c0048, 0x01, 0x543c0474, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO14__MEDIAMIX_CAM_DATA6                            0x543c0048, 0x02, 0x543c04a8, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO14__MEDIAMIX_DISP_DATA10                          0x543c0048, 0x03, 0x0, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO14__LPSPI8_SOUT                                   0x543c0048, 0x04, 0x0, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO14__LPUART8_CTS_B                                 0x543c0048, 0x05, 0x0, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO14__LPUART4_TX                                    0x543c0048, 0x06, 0x543c0480, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO14__FLEXIO1_FLEXIO14                              0x543c0048, 0x07, 0x543c03a0, 0x00, 0x543c01f8
#define IOMUXC_PAD_GPIO_IO15__GPIO2_IO15                                    0x543c004c, 0x00, 0x0, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO15__LPUART3_RX                                    0x543c004c, 0x01, 0x543c0470, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO15__MEDIAMIX_CAM_DATA7                            0x543c004c, 0x02, 0x543c04ac, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO15__MEDIAMIX_DISP_DATA11                          0x543c004c, 0x03, 0x0, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO15__LPSPI8_SCK                                    0x543c004c, 0x04, 0x0, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO15__LPUART8_RTS_B                                 0x543c004c, 0x05, 0x0, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO15__LPUART4_RX                                    0x543c004c, 0x06, 0x543c047c, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO15__FLEXIO1_FLEXIO15                              0x543c004c, 0x07, 0x543c03a4, 0x00, 0x543c01fc
#define IOMUXC_PAD_GPIO_IO16__GPIO2_IO16                                    0x543c0050, 0x00, 0x0, 0x00, 0x543c0200
#define IOMUXC_PAD_GPIO_IO16__SAI3_TX_BCLK                                  0x543c0050, 0x01, 0x0, 0x00, 0x543c0200
#define IOMUXC_PAD_GPIO_IO16__PDM_BIT_STREAM2                               0x543c0050, 0x02, 0x543c04cc, 0x01, 0x543c0200
#define IOMUXC_PAD_GPIO_IO16__MEDIAMIX_DISP_DATA12                          0x543c0050, 0x03, 0x0, 0x00, 0x543c0200
#define IOMUXC_PAD_GPIO_IO16__LPUART3_CTS_B                                 0x543c0050, 0x04, 0x543c046c, 0x00, 0x543c0200
#define IOMUXC_PAD_GPIO_IO16__LPSPI4_PCS2                                   0x543c0050, 0x05, 0x0, 0x00, 0x543c0200
#define IOMUXC_PAD_GPIO_IO16__LPUART4_CTS_B                                 0x543c0050, 0x06, 0x543c0478, 0x00, 0x543c0200
#define IOMUXC_PAD_GPIO_IO16__FLEXIO1_FLEXIO16                              0x543c0050, 0x07, 0x543c03a8, 0x00, 0x543c0200
#define IOMUXC_PAD_GPIO_IO17__GPIO2_IO17                                    0x543c0054, 0x00, 0x0, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO17__SAI3_MCLK                                     0x543c0054, 0x01, 0x0, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO17__MEDIAMIX_CAM_DATA8                            0x543c0054, 0x02, 0x543c04b0, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO17__MEDIAMIX_DISP_DATA13                          0x543c0054, 0x03, 0x0, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO17__LPUART3_RTS_B                                 0x543c0054, 0x04, 0x0, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO17__LPSPI4_PCS1                                   0x543c0054, 0x05, 0x0, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO17__LPUART4_RTS_B                                 0x543c0054, 0x06, 0x0, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO17__FLEXIO1_FLEXIO17                              0x543c0054, 0x07, 0x543c03ac, 0x00, 0x543c0204
#define IOMUXC_PAD_GPIO_IO18__GPIO2_IO18                                    0x543c0058, 0x00, 0x0, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO18__SAI3_RX_BCLK                                  0x543c0058, 0x01, 0x543c04d8, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO18__MEDIAMIX_CAM_DATA9                            0x543c0058, 0x02, 0x543c04b4, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO18__MEDIAMIX_DISP_DATA14                          0x543c0058, 0x03, 0x0, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO18__LPSPI5_PCS0                                   0x543c0058, 0x04, 0x0, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO18__LPSPI4_PCS0                                   0x543c0058, 0x05, 0x0, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO18__TPM5_CH2                                      0x543c0058, 0x06, 0x0, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO18__FLEXIO1_FLEXIO18                              0x543c0058, 0x07, 0x543c03b0, 0x00, 0x543c0208
#define IOMUXC_PAD_GPIO_IO19__GPIO2_IO19                                    0x543c005c, 0x00, 0x0, 0x00, 0x543c020c
#define IOMUXC_PAD_GPIO_IO19__SAI3_RX_SYNC                                  0x543c005c, 0x01, 0x543c04dc, 0x01, 0x543c020c
#define IOMUXC_PAD_GPIO_IO19__PDM_BIT_STREAM3                               0x543c005c, 0x02, 0x543c04d0, 0x01, 0x543c020c
#define IOMUXC_PAD_GPIO_IO19__MEDIAMIX_DISP_DATA15                          0x543c005c, 0x03, 0x0, 0x00, 0x543c020c
#define IOMUXC_PAD_GPIO_IO19__LPSPI5_SIN                                    0x543c005c, 0x04, 0x0, 0x00, 0x543c020c
#define IOMUXC_PAD_GPIO_IO19__LPSPI4_SIN                                    0x543c005c, 0x05, 0x0, 0x00, 0x543c020c
#define IOMUXC_PAD_GPIO_IO19__TPM6_CH2                                      0x543c005c, 0x06, 0x0, 0x00, 0x543c020c
#define IOMUXC_PAD_GPIO_IO19__SAI3_TX_DATA0                                 0x543c005c, 0x07, 0x0, 0x00, 0x543c020c
#define IOMUXC_PAD_GPIO_IO20__GPIO2_IO20                                    0x543c0060, 0x00, 0x0, 0x00, 0x543c0210
#define IOMUXC_PAD_GPIO_IO20__SAI3_RX_DATA0                                 0x543c0060, 0x01, 0x0, 0x00, 0x543c0210
#define IOMUXC_PAD_GPIO_IO20__PDM_BIT_STREAM0                               0x543c0060, 0x02, 0x543c04c4, 0x01, 0x543c0210
#define IOMUXC_PAD_GPIO_IO20__MEDIAMIX_DISP_DATA16                          0x543c0060, 0x03, 0x0, 0x00, 0x543c0210
#define IOMUXC_PAD_GPIO_IO20__LPSPI5_SOUT                                   0x543c0060, 0x04, 0x0, 0x00, 0x543c0210
#define IOMUXC_PAD_GPIO_IO20__LPSPI4_SOUT                                   0x543c0060, 0x05, 0x0, 0x00, 0x543c0210
#define IOMUXC_PAD_GPIO_IO20__TPM3_CH1                                      0x543c0060, 0x06, 0x0, 0x00, 0x543c0210
#define IOMUXC_PAD_GPIO_IO20__FLEXIO1_FLEXIO20                              0x543c0060, 0x07, 0x543c03b4, 0x00, 0x543c0210
#define IOMUXC_PAD_GPIO_IO21__GPIO2_IO21                                    0x543c0064, 0x00, 0x0, 0x00, 0x543c0214
#define IOMUXC_PAD_GPIO_IO21__SAI3_TX_DATA0                                 0x543c0064, 0x01, 0x0, 0x00, 0x543c0214
#define IOMUXC_PAD_GPIO_IO21__PDM_CLK                                       0x543c0064, 0x02, 0x0, 0x00, 0x543c0214
#define IOMUXC_PAD_GPIO_IO21__MEDIAMIX_DISP_DATA17                          0x543c0064, 0x03, 0x0, 0x00, 0x543c0214
#define IOMUXC_PAD_GPIO_IO21__LPSPI5_SCK                                    0x543c0064, 0x04, 0x0, 0x00, 0x543c0214
#define IOMUXC_PAD_GPIO_IO21__LPSPI4_SCK                                    0x543c0064, 0x05, 0x0, 0x00, 0x543c0214
#define IOMUXC_PAD_GPIO_IO21__TPM4_CH1                                      0x543c0064, 0x06, 0x0, 0x00, 0x543c0214
#define IOMUXC_PAD_GPIO_IO21__SAI3_RX_BCLK                                  0x543c0064, 0x07, 0x543c04d8, 0x01, 0x543c0214
#define IOMUXC_PAD_GPIO_IO22__GPIO2_IO22                                    0x543c0068, 0x00, 0x0, 0x00, 0x543c0218
#define IOMUXC_PAD_GPIO_IO22__USDHC3_CLK                                    0x543c0068, 0x01, 0x543c04e8, 0x00, 0x543c0218
#define IOMUXC_PAD_GPIO_IO22__SPDIF_IN                                      0x543c0068, 0x02, 0x543c04e4, 0x00, 0x543c0218
#define IOMUXC_PAD_GPIO_IO22__MEDIAMIX_DISP_DATA18                          0x543c0068, 0x03, 0x0, 0x00, 0x543c0218
#define IOMUXC_PAD_GPIO_IO22__TPM5_CH1                                      0x543c0068, 0x04, 0x0, 0x00, 0x543c0218
#define IOMUXC_PAD_GPIO_IO22__TPM6_EXTCLK                                   0x543c0068, 0x05, 0x0, 0x00, 0x543c0218
#define IOMUXC_PAD_GPIO_IO22__LPI2C5_SDA                                    0x543c0068, 0x06, 0x543c0404, 0x01, 0x543c0218
#define IOMUXC_PAD_GPIO_IO22__FLEXIO1_FLEXIO22                              0x543c0068, 0x07, 0x543c03b8, 0x00, 0x543c0218
#define IOMUXC_PAD_GPIO_IO23__GPIO2_IO23                                    0x543c006c, 0x00, 0x0, 0x00, 0x543c021c
#define IOMUXC_PAD_GPIO_IO23__USDHC3_CMD                                    0x543c006c, 0x01, 0x543c04ec, 0x00, 0x543c021c
#define IOMUXC_PAD_GPIO_IO23__SPDIF_OUT                                     0x543c006c, 0x02, 0x0, 0x00, 0x543c021c
#define IOMUXC_PAD_GPIO_IO23__MEDIAMIX_DISP_DATA19                          0x543c006c, 0x03, 0x0, 0x00, 0x543c021c
#define IOMUXC_PAD_GPIO_IO23__TPM6_CH1                                      0x543c006c, 0x04, 0x0, 0x00, 0x543c021c
#define IOMUXC_PAD_GPIO_IO23__LPI2C5_SCL                                    0x543c006c, 0x06, 0x543c0400, 0x01, 0x543c021c
#define IOMUXC_PAD_GPIO_IO23__FLEXIO1_FLEXIO23                              0x543c006c, 0x07, 0x543c03bc, 0x00, 0x543c021c
#define IOMUXC_PAD_GPIO_IO24__GPIO2_IO24                                    0x543c0070, 0x00, 0x0, 0x00, 0x543c0220
#define IOMUXC_PAD_GPIO_IO24__USDHC3_DATA0                                  0x543c0070, 0x01, 0x543c04f0, 0x00, 0x543c0220
#define IOMUXC_PAD_GPIO_IO24__MEDIAMIX_DISP_DATA20                          0x543c0070, 0x03, 0x0, 0x00, 0x543c0220
#define IOMUXC_PAD_GPIO_IO24__TPM3_CH3                                      0x543c0070, 0x04, 0x0, 0x00, 0x543c0220
#define IOMUXC_PAD_GPIO_IO24__JTAG_MUX_TDO                                  0x543c0070, 0x05, 0x0, 0x00, 0x543c0220
#define IOMUXC_PAD_GPIO_IO24__LPSPI6_PCS1                                   0x543c0070, 0x06, 0x0, 0x00, 0x543c0220
#define IOMUXC_PAD_GPIO_IO24__FLEXIO1_FLEXIO24                              0x543c0070, 0x07, 0x543c03c0, 0x00, 0x543c0220
#define IOMUXC_PAD_GPIO_IO25__GPIO2_IO25                                    0x543c0074, 0x00, 0x0, 0x00, 0x543c0224
#define IOMUXC_PAD_GPIO_IO25__USDHC3_DATA1                                  0x543c0074, 0x01, 0x543c04f4, 0x00, 0x543c0224
#define IOMUXC_PAD_GPIO_IO25__CAN2_TX                                       0x543c0074, 0x02, 0x0, 0x00, 0x543c0224
#define IOMUXC_PAD_GPIO_IO25__MEDIAMIX_DISP_DATA21                          0x543c0074, 0x03, 0x0, 0x00, 0x543c0224
#define IOMUXC_PAD_GPIO_IO25__TPM4_CH3                                      0x543c0074, 0x04, 0x0, 0x00, 0x543c0224
#define IOMUXC_PAD_GPIO_IO25__JTAG_MUX_TCK                                  0x543c0074, 0x05, 0x543c03d4, 0x01, 0x543c0224
#define IOMUXC_PAD_GPIO_IO25__LPSPI7_PCS1                                   0x543c0074, 0x06, 0x0, 0x00, 0x543c0224
#define IOMUXC_PAD_GPIO_IO25__FLEXIO1_FLEXIO25                              0x543c0074, 0x07, 0x543c03c4, 0x00, 0x543c0224
#define IOMUXC_PAD_GPIO_IO26__GPIO2_IO26                                    0x543c0078, 0x00, 0x0, 0x00, 0x543c0228
#define IOMUXC_PAD_GPIO_IO26__USDHC3_DATA2                                  0x543c0078, 0x01, 0x543c04f8, 0x00, 0x543c0228
#define IOMUXC_PAD_GPIO_IO26__PDM_BIT_STREAM1                               0x543c0078, 0x02, 0x543c04c8, 0x01, 0x543c0228
#define IOMUXC_PAD_GPIO_IO26__MEDIAMIX_DISP_DATA22                          0x543c0078, 0x03, 0x0, 0x00, 0x543c0228
#define IOMUXC_PAD_GPIO_IO26__TPM5_CH3                                      0x543c0078, 0x04, 0x0, 0x00, 0x543c0228
#define IOMUXC_PAD_GPIO_IO26__JTAG_MUX_TDI                                  0x543c0078, 0x05, 0x543c03d8, 0x01, 0x543c0228
#define IOMUXC_PAD_GPIO_IO26__LPSPI8_PCS1                                   0x543c0078, 0x06, 0x0, 0x00, 0x543c0228
#define IOMUXC_PAD_GPIO_IO26__SAI3_TX_SYNC                                  0x543c0078, 0x07, 0x543c04e0, 0x00, 0x543c0228
#define IOMUXC_PAD_GPIO_IO27__GPIO2_IO27                                    0x543c007c, 0x00, 0x0, 0x00, 0x543c022c
#define IOMUXC_PAD_GPIO_IO27__USDHC3_DATA3                                  0x543c007c, 0x01, 0x543c04fc, 0x00, 0x543c022c
#define IOMUXC_PAD_GPIO_IO27__CAN2_RX                                       0x543c007c, 0x02, 0x543c0364, 0x01, 0x543c022c
#define IOMUXC_PAD_GPIO_IO27__MEDIAMIX_DISP_DATA23                          0x543c007c, 0x03, 0x0, 0x00, 0x543c022c
#define IOMUXC_PAD_GPIO_IO27__TPM6_CH3                                      0x543c007c, 0x04, 0x0, 0x00, 0x543c022c
#define IOMUXC_PAD_GPIO_IO27__JTAG_MUX_TMS                                  0x543c007c, 0x05, 0x543c03dc, 0x01, 0x543c022c
#define IOMUXC_PAD_GPIO_IO27__LPSPI5_PCS1                                   0x543c007c, 0x06, 0x0, 0x00, 0x543c022c
#define IOMUXC_PAD_GPIO_IO27__FLEXIO1_FLEXIO27                              0x543c007c, 0x07, 0x543c03c8, 0x00, 0x543c022c
#define IOMUXC_PAD_GPIO_IO28__GPIO2_IO28                                    0x543c0080, 0x00, 0x0, 0x00, 0x543c0230
#define IOMUXC_PAD_GPIO_IO28__LPI2C3_SDA                                    0x543c0080, 0x01, 0x543c03f4, 0x01, 0x543c0230
#define IOMUXC_PAD_GPIO_IO28__CAN1_TX                                       0x543c0080, 0x02, 0x0, 0x00, 0x543c0230
#define IOMUXC_PAD_GPIO_IO28__FLEXIO1_FLEXIO28                              0x543c0080, 0x07, 0x0, 0x00, 0x543c0230
#define IOMUXC_PAD_GPIO_IO29__GPIO2_IO29                                    0x543c0084, 0x00, 0x0, 0x00, 0x543c0234
#define IOMUXC_PAD_GPIO_IO29__LPI2C3_SCL                                    0x543c0084, 0x01, 0x543c03f0, 0x01, 0x543c0234
#define IOMUXC_PAD_GPIO_IO29__CAN1_RX                                       0x543c0084, 0x02, 0x543c0360, 0x00, 0x543c0234
#define IOMUXC_PAD_GPIO_IO29__FLEXIO1_FLEXIO29                              0x543c0084, 0x07, 0x0, 0x00, 0x543c0234
#define IOMUXC_PAD_CCM_CLKO1__CCMSRCGPCMIX_CLKO1                            0x543c0088, 0x00, 0x0, 0x00, 0x543c0238
#define IOMUXC_PAD_CCM_CLKO1__FLEXIO1_FLEXIO26                              0x543c0088, 0x04, 0x0, 0x00, 0x543c0238
#define IOMUXC_PAD_CCM_CLKO1__GPIO3_IO26                                    0x543c0088, 0x05, 0x0, 0x00, 0x543c0238
#define IOMUXC_PAD_CCM_CLKO2__GPIO3_IO27                                    0x543c008c, 0x05, 0x0, 0x00, 0x543c023c
#define IOMUXC_PAD_CCM_CLKO2__CCMSRCGPCMIX_CLKO2                            0x543c008c, 0x00, 0x0, 0x00, 0x543c023c
#define IOMUXC_PAD_CCM_CLKO2__FLEXIO1_FLEXIO27                              0x543c008c, 0x04, 0x543c03c8, 0x01, 0x543c023c
#define IOMUXC_PAD_CCM_CLKO3__CCMSRCGPCMIX_CLKO3                            0x543c0090, 0x00, 0x0, 0x00, 0x543c0240
#define IOMUXC_PAD_CCM_CLKO3__FLEXIO2_FLEXIO28                              0x543c0090, 0x04, 0x0, 0x00, 0x543c0240
#define IOMUXC_PAD_CCM_CLKO3__GPIO4_IO28                                    0x543c0090, 0x05, 0x0, 0x00, 0x543c0240
#define IOMUXC_PAD_CCM_CLKO4__CCMSRCGPCMIX_CLKO4                            0x543c0094, 0x00, 0x0, 0x00, 0x543c0244
#define IOMUXC_PAD_CCM_CLKO4__FLEXIO2_FLEXIO29                              0x543c0094, 0x04, 0x0, 0x00, 0x543c0244
#define IOMUXC_PAD_CCM_CLKO4__GPIO4_IO29                                    0x543c0094, 0x05, 0x0, 0x00, 0x543c0244
#define IOMUXC_PAD_ENET1_MDC__ENET1_MDC                                     0x543c0098, 0x00, 0x0, 0x00, 0x543c0248
#define IOMUXC_PAD_ENET1_MDC__LPUART3_DCB_B                                 0x543c0098, 0x01, 0x0, 0x00, 0x543c0248
#define IOMUXC_PAD_ENET1_MDC__I3C2_SCL                                      0x543c0098, 0x02, 0x543c03cc, 0x00, 0x543c0248
#define IOMUXC_PAD_ENET1_MDC__HSIOMIX_OTG_ID1                               0x543c0098, 0x03, 0x0, 0x00, 0x543c0248
#define IOMUXC_PAD_ENET1_MDC__FLEXIO2_FLEXIO0                               0x543c0098, 0x04, 0x0, 0x00, 0x543c0248
#define IOMUXC_PAD_ENET1_MDC__GPIO4_IO0                                     0x543c0098, 0x05, 0x0, 0x00, 0x543c0248
#define IOMUXC_PAD_ENET1_MDC__LPI2C1_SCL                                    0x543c0098, 0x06, 0x543c03e0, 0x00, 0x543c0248
#define IOMUXC_PAD_ENET1_MDIO__ENET_QOS_MDIO                                0x543c009c, 0x00, 0x0, 0x00, 0x543c024c
#define IOMUXC_PAD_ENET1_MDIO__LPUART3_RIN_B                                0x543c009c, 0x01, 0x0, 0x00, 0x543c024c
#define IOMUXC_PAD_ENET1_MDIO__I3C2_SDA                                     0x543c009c, 0x02, 0x543c03d0, 0x00, 0x543c024c
#define IOMUXC_PAD_ENET1_MDIO__HSIOMIX_OTG_PWR1                             0x543c009c, 0x03, 0x0, 0x00, 0x543c024c
#define IOMUXC_PAD_ENET1_MDIO__FLEXIO2_FLEXIO1                              0x543c009c, 0x04, 0x0, 0x00, 0x543c024c
#define IOMUXC_PAD_ENET1_MDIO__GPIO4_IO1                                    0x543c009c, 0x05, 0x0, 0x00, 0x543c024c
#define IOMUXC_PAD_ENET1_MDIO__LPI2C1_SDA                                   0x543c009c, 0x06, 0x543c03e4, 0x00, 0x543c024c
#define IOMUXC_PAD_ENET1_TD3__ENET_QOS_RGMII_TD3                            0x543c00a0, 0x00, 0x0, 0x00, 0x543c0250
#define IOMUXC_PAD_ENET1_TD3__CAN2_TX                                       0x543c00a0, 0x02, 0x0, 0x00, 0x543c0250
#define IOMUXC_PAD_ENET1_TD3__HSIOMIX_OTG_ID2                               0x543c00a0, 0x03, 0x0, 0x00, 0x543c0250
#define IOMUXC_PAD_ENET1_TD3__FLEXIO2_FLEXIO2                               0x543c00a0, 0x04, 0x0, 0x00, 0x543c0250
#define IOMUXC_PAD_ENET1_TD3__GPIO4_IO3                                     0x543c00a0, 0x05, 0x0, 0x00, 0x543c0250
#define IOMUXC_PAD_ENET1_TD3__LPI2C1_SCL                                    0x543c00a0, 0x06, 0x543c03e8, 0x00, 0x543c0250
#define IOMUXC_PAD_ENET1_TD2__ENET_QOS_RGMII_TD2                            0x543c00a4, 0x00, 0x0, 0x00, 0x543c0254
#define IOMUXC_PAD_ENET1_TD2__ENET_QOS_CLOCK_GENERATE_CLK                   0x543c00a4, 0x01, 0x0, 0x00, 0x543c0254
#define IOMUXC_PAD_ENET1_TD2__CAN2_RX                                       0x543c00a4, 0x02, 0x543c0364, 0x02, 0x543c0254
#define IOMUXC_PAD_ENET1_TD2__HSIOMIX_OTG_OC2                               0x543c00a4, 0x03, 0x0, 0x00, 0x543c0254
#define IOMUXC_PAD_ENET1_TD2__FLEXIO2_FLEXIO3                               0x543c00a4, 0x04, 0x0, 0x00, 0x543c0254
#define IOMUXC_PAD_ENET1_TD2__GPIO4_IO3                                     0x543c00a4, 0x05, 0x0, 0x00, 0x543c0254
#define IOMUXC_PAD_ENET1_TD2__LPI2C2_SDA                                    0x543c00a4, 0x06, 0x543c03ec, 0x00, 0x543c0254
#define IOMUXC_PAD_ENET1_TD1__ENET1_RGMII_TD1                               0x543c00a8, 0x00, 0x0, 0x00, 0x543c0258
#define IOMUXC_PAD_ENET1_TD1__LPUART3_RTS_B                                 0x543c00a8, 0x01, 0x0, 0x00, 0x543c0258
#define IOMUXC_PAD_ENET1_TD1__I3C2_PUR                                      0x543c00a8, 0x02, 0x0, 0x00, 0x543c0258
#define IOMUXC_PAD_ENET1_TD1__HSIOMIX_OTG_OC1                               0x543c00a8, 0x03, 0x0, 0x00, 0x543c0258
#define IOMUXC_PAD_ENET1_TD1__FLEXIO2_FLEXIO4                               0x543c00a8, 0x04, 0x0, 0x00, 0x543c0258
#define IOMUXC_PAD_ENET1_TD1__GPIO4_IO4                                     0x543c00a8, 0x05, 0x0, 0x00, 0x543c0258
#define IOMUXC_PAD_ENET1_TD1__I3C2_PUR_B                                    0x543c00a8, 0x06, 0x0, 0x00, 0x543c0258
#define IOMUXC_PAD_ENET1_TD0__ENET_QOS_RGMII_TD0                            0x543c00ac, 0x00, 0x0, 0x00, 0x543c025c
#define IOMUXC_PAD_ENET1_TD0__LPUART3_TX                                    0x543c00ac, 0x01, 0x543c0474, 0x01, 0x543c025c
#define IOMUXC_PAD_ENET1_TD0__FLEXIO2_FLEXIO5                               0x543c00ac, 0x04, 0x0, 0x00, 0x543c025c
#define IOMUXC_PAD_ENET1_TD0__GPIO4_IO5                                     0x543c00ac, 0x05, 0x0, 0x00, 0x543c025c
#define IOMUXC_PAD_ENET1_TX_CTL__ENET_QOS_RGMII_TX_CTL                      0x543c00b0, 0x00, 0x0, 0x00, 0x543c0260
#define IOMUXC_PAD_ENET1_TX_CTL__LPUART3_DTR_B                              0x543c00b0, 0x01, 0x0, 0x00, 0x543c0260
#define IOMUXC_PAD_ENET1_TX_CTL__FLEXIO2_FLEXIO6                            0x543c00b0, 0x04, 0x0, 0x00, 0x543c0260
#define IOMUXC_PAD_ENET1_TX_CTL__GPIO4_IO6                                  0x543c00b0, 0x05, 0x0, 0x00, 0x543c0260
#define IOMUXC_PAD_ENET1_TX_CTL__LPSPI2_SCK                                 0x543c00b0, 0x02, 0x543c043c, 0x00, 0x543c0260
#define IOMUXC_PAD_ENET1_TXC__CCM_ENET_QOS_CLOCK_GENERATE_TX_CLK            0x543c00b4, 0x00, 0x0, 0x00, 0x543c0264
#define IOMUXC_PAD_ENET1_TXC__ENET_QOS_TX_ER                                0x543c00b4, 0x01, 0x0, 0x00, 0x543c0264
#define IOMUXC_PAD_ENET1_TXC__FLEXIO2_FLEXIO7                               0x543c00b4, 0x04, 0x0, 0x00, 0x543c0264
#define IOMUXC_PAD_ENET1_TXC__GPIO4_IO7                                     0x543c00b4, 0x05, 0x0, 0x00, 0x543c0264
#define IOMUXC_PAD_ENET1_TXC__LPSPI2_SIN                                    0x543c00b4, 0x02, 0x543c0440, 0x00, 0x543c0264
#define IOMUXC_PAD_ENET1_RX_CTL__ENET_QOS_RGMII_RX_CTL                      0x543c00b8, 0x00, 0x0, 0x00, 0x543c0268
#define IOMUXC_PAD_ENET1_RX_CTL__LPUART3_DSR_B                              0x543c00b8, 0x01, 0x0, 0x00, 0x543c0268
#define IOMUXC_PAD_ENET1_RX_CTL__HSIOMIX_OTG_PWR2                           0x543c00b8, 0x03, 0x0, 0x00, 0x543c0268
#define IOMUXC_PAD_ENET1_RX_CTL__FLEXIO2_FLEXIO8                            0x543c00b8, 0x04, 0x0, 0x00, 0x543c0268
#define IOMUXC_PAD_ENET1_RX_CTL__GPIO4_IO8                                  0x543c00b8, 0x05, 0x0, 0x00, 0x543c0268
#define IOMUXC_PAD_ENET1_RX_CTL__LPSPI2_PCS0                                0x543c00b8, 0x02, 0x543c0434, 0x00, 0x543c0268
#define IOMUXC_PAD_ENET1_RXC__ENET_QOS_RGMII_RXC                            0x543c00bc, 0x00, 0x0, 0x00, 0x543c026c
#define IOMUXC_PAD_ENET1_RXC__ENET_QOS_RX_ER                                0x543c00bc, 0x01, 0x0, 0x00, 0x543c026c
#define IOMUXC_PAD_ENET1_RXC__FLEXIO2_FLEXIO9                               0x543c00bc, 0x04, 0x0, 0x00, 0x543c026c
#define IOMUXC_PAD_ENET1_RXC__GPIO4_IO9                                     0x543c00bc, 0x05, 0x0, 0x00, 0x543c026c
#define IOMUXC_PAD_ENET1_RXC__LPSPI2_SOUT                                   0x543c00bc, 0x02, 0x543c0444, 0x00, 0x543c026c
#define IOMUXC_PAD_ENET1_RD0__ENET_QOS_RGMII_RD0                            0x543c00c0, 0x00, 0x0, 0x00, 0x543c0270
#define IOMUXC_PAD_ENET1_RD0__LPUART3_RX                                    0x543c00c0, 0x01, 0x543c0470, 0x01, 0x543c0270
#define IOMUXC_PAD_ENET1_RD0__FLEXIO2_FLEXIO10                              0x543c00c0, 0x04, 0x0, 0x00, 0x543c0270
#define IOMUXC_PAD_ENET1_RD0__GPIO4_IO10                                    0x543c00c0, 0x05, 0x0, 0x00, 0x543c0270
#define IOMUXC_PAD_ENET1_RD1__ENET_QOS_RGMII_RD1                            0x543c00c4, 0x00, 0x0, 0x00, 0x543c0274
#define IOMUXC_PAD_ENET1_RD1__LPUART3_CTS_B                                 0x543c00c4, 0x01, 0x543c046c, 0x01, 0x543c0274
#define IOMUXC_PAD_ENET1_RD1__LPTMR2_ALT1                                   0x543c00c4, 0x03, 0x543c0448, 0x00, 0x543c0274
#define IOMUXC_PAD_ENET1_RD1__FLEXIO2_FLEXIO11                              0x543c00c4, 0x04, 0x0, 0x00, 0x543c0274
#define IOMUXC_PAD_ENET1_RD1__GPIO4_IO11                                    0x543c00c4, 0x05, 0x0, 0x00, 0x543c0274
#define IOMUXC_PAD_ENET1_RD2__ENET_QOS_RGMII_RD2                            0x543c00c8, 0x00, 0x0, 0x00, 0x543c0278
#define IOMUXC_PAD_ENET1_RD2__LPTMR2_ALT2                                   0x543c00c8, 0x03, 0x543c044c, 0x00, 0x543c0278
#define IOMUXC_PAD_ENET1_RD2__FLEXIO2_FLEXIO12                              0x543c00c8, 0x04, 0x0, 0x00, 0x543c0278
#define IOMUXC_PAD_ENET1_RD2__GPIO4_IO12                                    0x543c00c8, 0x05, 0x0, 0x00, 0x543c0278
#define IOMUXC_PAD_ENET1_RD3__ENET_QOS_RGMII_RD3                            0x543c00cc, 0x00, 0x0, 0x00, 0x543c027c
#define IOMUXC_PAD_ENET1_RD3__FLEXSPI1_TESTER_TRIGGER                       0x543c00cc, 0x02, 0x0, 0x00, 0x543c027c
#define IOMUXC_PAD_ENET1_RD3__LPTMR2_ALT3                                   0x543c00cc, 0x03, 0x543c0450, 0x00, 0x543c027c
#define IOMUXC_PAD_ENET1_RD3__FLEXIO2_FLEXIO13                              0x543c00cc, 0x04, 0x0, 0x00, 0x543c027c
#define IOMUXC_PAD_ENET1_RD3__GPIO4_IO13                                    0x543c00cc, 0x05, 0x0, 0x00, 0x543c027c
#define IOMUXC_PAD_ENET2_MDC__ENET2_MDC                                     0x543c00d0, 0x00, 0x0, 0x00, 0x543c0280
#define IOMUXC_PAD_ENET2_MDC__LPUART4_DCB_B                                 0x543c00d0, 0x01, 0x0, 0x00, 0x543c0280
#define IOMUXC_PAD_ENET2_MDC__SAI2_RX_SYNC                                  0x543c00d0, 0x02, 0x0, 0x00, 0x543c0280
#define IOMUXC_PAD_ENET2_MDC__FLEXIO2_FLEXIO14                              0x543c00d0, 0x04, 0x0, 0x00, 0x543c0280
#define IOMUXC_PAD_ENET2_MDC__GPIO4_IO14                                    0x543c00d0, 0x05, 0x0, 0x00, 0x543c0280
#define IOMUXC_PAD_ENET2_MDC__MEDIAMIX_CAM_CLK                              0x543c00d0, 0x06, 0x543c04bc, 0x01, 0x543c0280
#define IOMUXC_PAD_ENET2_MDIO__ENET2_MDIO                                   0x543c00d4, 0x00, 0x0, 0x00, 0x543c0284
#define IOMUXC_PAD_ENET2_MDIO__LPUART4_RIN_B                                0x543c00d4, 0x01, 0x0, 0x00, 0x543c0284
#define IOMUXC_PAD_ENET2_MDIO__SAI2_RX_BCLK                                 0x543c00d4, 0x02, 0x0, 0x00, 0x543c0284
#define IOMUXC_PAD_ENET2_MDIO__FLEXIO2_FLEXIO15                             0x543c00d4, 0x04, 0x0, 0x00, 0x543c0284
#define IOMUXC_PAD_ENET2_MDIO__GPIO4_IO15                                   0x543c00d4, 0x05, 0x0, 0x00, 0x543c0284
#define IOMUXC_PAD_ENET2_MDIO__MEDIAMIX_CAM_DATA0                           0x543c00d4, 0x06, 0x543c0490, 0x01, 0x543c0284
#define IOMUXC_PAD_ENET2_TD3__SAI2_RX_DATA0                                 0x543c00d8, 0x02, 0x0, 0x00, 0x543c0288
#define IOMUXC_PAD_ENET2_TD3__FLEXIO2_FLEXIO16                              0x543c00d8, 0x04, 0x0, 0x00, 0x543c0288
#define IOMUXC_PAD_ENET2_TD3__GPIO4_IO16                                    0x543c00d8, 0x05, 0x0, 0x00, 0x543c0288
#define IOMUXC_PAD_ENET2_TD3__MEDIAMIX_CAM_VSYNC                            0x543c00d8, 0x06, 0x543c04c0, 0x01, 0x543c0288
#define IOMUXC_PAD_ENET2_TD3__ENET2_RGMII_TD3                               0x543c00d8, 0x00, 0x0, 0x00, 0x543c0288
#define IOMUXC_PAD_ENET2_TD2__ENET2_RGMII_TD2                               0x543c00dc, 0x00, 0x0, 0x00, 0x543c028c
#define IOMUXC_PAD_ENET2_TD2__ENET2_TX_CLK2                                 0x543c00dc, 0x01, 0x0, 0x00, 0x543c028c
#define IOMUXC_PAD_ENET2_TD2__FLEXIO2_FLEXIO17                              0x543c00dc, 0x04, 0x0, 0x00, 0x543c028c
#define IOMUXC_PAD_ENET2_TD2__GPIO4_IO17                                    0x543c00dc, 0x05, 0x0, 0x00, 0x543c028c
#define IOMUXC_PAD_ENET2_TD2__MEDIAMIX_CAM_HSYNC                            0x543c00dc, 0x06, 0x543c04b8, 0x01, 0x543c028c
#define IOMUXC_PAD_ENET2_TD1__ENET2_RGMII_TD1                               0x543c00e0, 0x00, 0x0, 0x00, 0x543c0290
#define IOMUXC_PAD_ENET2_TD1__LPUART4_RTS_B                                 0x543c00e0, 0x01, 0x0, 0x00, 0x543c0290
#define IOMUXC_PAD_ENET2_TD1__FLEXIO2_FLEXIO18                              0x543c00e0, 0x04, 0x0, 0x00, 0x543c0290
#define IOMUXC_PAD_ENET2_TD1__GPIO4_IO18                                    0x543c00e0, 0x05, 0x0, 0x00, 0x543c0290
#define IOMUXC_PAD_ENET2_TD1__MEDIAMIX_CAM_DATA1                            0x543c00e0, 0x06, 0x543c0494, 0x01, 0x543c0290
#define IOMUXC_PAD_ENET2_TD0__ENET2_RGMII_TD0                               0x543c00e4, 0x00, 0x0, 0x00, 0x543c0294
#define IOMUXC_PAD_ENET2_TD0__LPUART4_TX                                    0x543c00e4, 0x01, 0x543c0480, 0x01, 0x543c0294
#define IOMUXC_PAD_ENET2_TD0__FLEXIO2_FLEXIO19                              0x543c00e4, 0x04, 0x0, 0x00, 0x543c0294
#define IOMUXC_PAD_ENET2_TD0__GPIO4_IO19                                    0x543c00e4, 0x05, 0x0, 0x00, 0x543c0294
#define IOMUXC_PAD_ENET2_TD0__MEDIAMIX_CAM_DATA2                            0x543c00e4, 0x06, 0x543c0498, 0x01, 0x543c0294
#define IOMUXC_PAD_ENET2_TX_CTL__ENET2_RGMII_TX_CTL                         0x543c00e8, 0x00, 0x0, 0x00, 0x543c0298
#define IOMUXC_PAD_ENET2_TX_CTL__LPUART4_DTR_B                              0x543c00e8, 0x01, 0x0, 0x00, 0x543c0298
#define IOMUXC_PAD_ENET2_TX_CTL__SAI2_TX_SYNC                               0x543c00e8, 0x02, 0x0, 0x00, 0x543c0298
#define IOMUXC_PAD_ENET2_TX_CTL__FLEXIO2_FLEXIO20                           0x543c00e8, 0x04, 0x0, 0x00, 0x543c0298
#define IOMUXC_PAD_ENET2_TX_CTL__GPIO4_IO20                                 0x543c00e8, 0x05, 0x0, 0x00, 0x543c0298
#define IOMUXC_PAD_ENET2_TX_CTL__MEDIAMIX_CAM_DATA3                         0x543c00e8, 0x06, 0x543c049c, 0x01, 0x543c0298
#define IOMUXC_PAD_ENET2_TXC__ENET2_RGMII_TXC                               0x543c00ec, 0x00, 0x0, 0x00, 0x543c029c
#define IOMUXC_PAD_ENET2_TXC__ENET2_TX_ER                                   0x543c00ec, 0x01, 0x0, 0x00, 0x543c029c
#define IOMUXC_PAD_ENET2_TXC__SAI2_TX_BCLK                                  0x543c00ec, 0x02, 0x0, 0x00, 0x543c029c
#define IOMUXC_PAD_ENET2_TXC__FLEXIO2_FLEXIO21                              0x543c00ec, 0x04, 0x0, 0x00, 0x543c029c
#define IOMUXC_PAD_ENET2_TXC__GPIO4_IO21                                    0x543c00ec, 0x05, 0x0, 0x00, 0x543c029c
#define IOMUXC_PAD_ENET2_TXC__MEDIAMIX_CAM_DATA4                            0x543c00ec, 0x06, 0x543c04a0, 0x01, 0x543c029c
#define IOMUXC_PAD_ENET2_RX_CTL__ENET2_RGMII_RX_CTL                         0x543c00f0, 0x00, 0x0, 0x00, 0x543c02a0
#define IOMUXC_PAD_ENET2_RX_CTL__LPUART4_DSR_B                              0x543c00f0, 0x01, 0x0, 0x00, 0x543c02a0
#define IOMUXC_PAD_ENET2_RX_CTL__SAI2_TX_DATA0                              0x543c00f0, 0x02, 0x0, 0x00, 0x543c02a0
#define IOMUXC_PAD_ENET2_RX_CTL__FLEXIO2_FLEXIO22                           0x543c00f0, 0x04, 0x0, 0x00, 0x543c02a0
#define IOMUXC_PAD_ENET2_RX_CTL__GPIO4_IO22                                 0x543c00f0, 0x05, 0x0, 0x00, 0x543c02a0
#define IOMUXC_PAD_ENET2_RX_CTL__MEDIAMIX_CAM_DATA5                         0x543c00f0, 0x06, 0x543c04a4, 0x01, 0x543c02a0
#define IOMUXC_PAD_ENET2_RXC__ENET2_RGMII_RXC                               0x543c00f4, 0x00, 0x0, 0x00, 0x543c02a4
#define IOMUXC_PAD_ENET2_RXC__ENET2_RX_ER                                   0x543c00f4, 0x01, 0x0, 0x00, 0x543c02a4
#define IOMUXC_PAD_ENET2_RXC__FLEXIO2_FLEXIO23                              0x543c00f4, 0x04, 0x0, 0x00, 0x543c02a4
#define IOMUXC_PAD_ENET2_RXC__GPIO4_IO23                                    0x543c00f4, 0x05, 0x0, 0x00, 0x543c02a4
#define IOMUXC_PAD_ENET2_RXC__MEDIAMIX_CAM_DATA6                            0x543c00f4, 0x06, 0x543c04a8, 0x01, 0x543c02a4
#define IOMUXC_PAD_ENET2_RD0__ENET2_RGMII_RD0                               0x543c00f8, 0x00, 0x0, 0x00, 0x543c02a8
#define IOMUXC_PAD_ENET2_RD0__LPUART4_RX                                    0x543c00f8, 0x01, 0x543c047c, 0x01, 0x543c02a8
#define IOMUXC_PAD_ENET2_RD0__FLEXIO2_FLEXIO24                              0x543c00f8, 0x04, 0x0, 0x00, 0x543c02a8
#define IOMUXC_PAD_ENET2_RD0__GPIO4_IO24                                    0x543c00f8, 0x05, 0x0, 0x00, 0x543c02a8
#define IOMUXC_PAD_ENET2_RD0__MEDIAMIX_CAM_DATA7                            0x543c00f8, 0x06, 0x543c04ac, 0x01, 0x543c02a8
#define IOMUXC_PAD_ENET2_RD1__ENET2_RGMII_RD1                               0x543c00fc, 0x00, 0x0, 0x00, 0x543c02ac
#define IOMUXC_PAD_ENET2_RD1__SPDIF_IN                                      0x543c00fc, 0x01, 0x543c04e4, 0x01, 0x543c02ac
#define IOMUXC_PAD_ENET2_RD1__FLEXIO2_FLEXIO25                              0x543c00fc, 0x04, 0x0, 0x00, 0x543c02ac
#define IOMUXC_PAD_ENET2_RD1__GPIO4_IO25                                    0x543c00fc, 0x05, 0x0, 0x00, 0x543c02ac
#define IOMUXC_PAD_ENET2_RD1__MEDIAMIX_CAM_DATA8                            0x543c00fc, 0x06, 0x543c04b0, 0x01, 0x543c02ac
#define IOMUXC_PAD_ENET2_RD2__ENET2_RGMII_RD2                               0x543c0100, 0x00, 0x0, 0x00, 0x543c02b0
#define IOMUXC_PAD_ENET2_RD2__LPUART4_CTS_B                                 0x543c0100, 0x01, 0x543c0478, 0x01, 0x543c02b0
#define IOMUXC_PAD_ENET2_RD2__SAI2_MCLK                                     0x543c0100, 0x02, 0x0, 0x00, 0x543c02b0
#define IOMUXC_PAD_ENET2_RD2__MQS2_RIGHT                                    0x543c0100, 0x03, 0x0, 0x00, 0x543c02b0
#define IOMUXC_PAD_ENET2_RD2__FLEXIO2_FLEXIO26                              0x543c0100, 0x04, 0x0, 0x00, 0x543c02b0
#define IOMUXC_PAD_ENET2_RD2__GPIO4_IO26                                    0x543c0100, 0x05, 0x0, 0x00, 0x543c02b0
#define IOMUXC_PAD_ENET2_RD2__MEDIAMIX_CAM_DATA9                            0x543c0100, 0x06, 0x543c04b4, 0x01, 0x543c02b0
#define IOMUXC_PAD_ENET2_RD3__ENET2_RGMII_RD3                               0x543c0104, 0x00, 0x0, 0x00, 0x543c02b4
#define IOMUXC_PAD_ENET2_RD3__SPDIF_OUT                                     0x543c0104, 0x01, 0x0, 0x00, 0x543c02b4
#define IOMUXC_PAD_ENET2_RD3__SPDIF_IN                                      0x543c0104, 0x02, 0x543c04e4, 0x02, 0x543c02b4
#define IOMUXC_PAD_ENET2_RD3__MQS2_LEFT                                     0x543c0104, 0x03, 0x0, 0x00, 0x543c02b4
#define IOMUXC_PAD_ENET2_RD3__FLEXIO2_FLEXIO27                              0x543c0104, 0x04, 0x0, 0x00, 0x543c02b4
#define IOMUXC_PAD_ENET2_RD3__GPIO4_IO27                                    0x543c0104, 0x05, 0x0, 0x00, 0x543c02b4
#define IOMUXC_PAD_SD1_CLK__FLEXIO1_FLEXIO8                                 0x543c0108, 0x04, 0x543c038c, 0x01, 0x543c02b8
#define IOMUXC_PAD_SD1_CLK__GPIO3_IO8                                       0x543c0108, 0x05, 0x0, 0x00, 0x543c02b8
#define IOMUXC_PAD_SD1_CLK__USDHC1_CLK                                      0x543c0108, 0x00, 0x0, 0x00, 0x543c02b8
#define IOMUXC_PAD_SD1_CLK__LPSPI2_SCK                                      0x543c0108, 0x03, 0x543c043c, 0x01, 0x543c02b8
#define IOMUXC_PAD_SD1_CMD__USDHC1_CMD                                      0x543c010c, 0x00, 0x0, 0x00, 0x543c02bc
#define IOMUXC_PAD_SD1_CMD__FLEXIO1_FLEXIO9                                 0x543c010c, 0x04, 0x543c0390, 0x01, 0x543c02bc
#define IOMUXC_PAD_SD1_CMD__GPIO3_IO9                                       0x543c010c, 0x05, 0x0, 0x00, 0x543c02bc
#define IOMUXC_PAD_SD1_CMD__LPSPI2_SIN                                      0x543c010c, 0x03, 0x543c0440, 0x01, 0x543c02bc
#define IOMUXC_PAD_SD1_DATA0__USDHC1_DATA0                                  0x543c0110, 0x00, 0x0, 0x00, 0x543c02c0
#define IOMUXC_PAD_SD1_DATA0__FLEXIO1_FLEXIO10                              0x543c0110, 0x04, 0x543c0394, 0x01, 0x543c02c0
#define IOMUXC_PAD_SD1_DATA0__GPIO3_IO10                                    0x543c0110, 0x05, 0x0, 0x00, 0x543c02c0
#define IOMUXC_PAD_SD1_DATA0__LPSPI2_PCS0                                   0x543c0110, 0x03, 0x543c0434, 0x01, 0x543c02c0
#define IOMUXC_PAD_SD1_DATA1__USDHC1_DATA1                                  0x543c0114, 0x00, 0x0, 0x00, 0x543c02c4
#define IOMUXC_PAD_SD1_DATA1__FLEXIO1_FLEXIO11                              0x543c0114, 0x04, 0x543c0398, 0x01, 0x543c02c4
#define IOMUXC_PAD_SD1_DATA1__GPIO3_IO11                                    0x543c0114, 0x05, 0x0, 0x00, 0x543c02c4
#define IOMUXC_PAD_SD1_DATA1__CCMSRCGPCMIX_INT_BOOT                         0x543c0114, 0x06, 0x0, 0x00, 0x543c02c4
#define IOMUXC_PAD_SD1_DATA1__LPSPI2_SOUT                                   0x543c0114, 0x03, 0x543c0444, 0x01, 0x543c02c4
#define IOMUXC_PAD_SD1_DATA2__USDHC1_DATA2                                  0x543c0118, 0x00, 0x0, 0x00, 0x543c02c8
#define IOMUXC_PAD_SD1_DATA2__FLEXIO1_FLEXIO12                              0x543c0118, 0x04, 0x0, 0x00, 0x543c02c8
#define IOMUXC_PAD_SD1_DATA2__GPIO3_IO12                                    0x543c0118, 0x05, 0x0, 0x00, 0x543c02c8
#define IOMUXC_PAD_SD1_DATA2__CCMSRCGPCMIX_PMIC_READY                       0x543c0118, 0x06, 0x0, 0x00, 0x543c02c8
#define IOMUXC_PAD_SD1_DATA2__LPSPI2_PCS1                                   0x543c0118, 0x03, 0x543c0438, 0x00, 0x543c02c8
#define IOMUXC_PAD_SD1_DATA3__USDHC1_DATA3                                  0x543c011c, 0x00, 0x0, 0x00, 0x543c02cc
#define IOMUXC_PAD_SD1_DATA3__FLEXSPI1_A_SS1_B                              0x543c011c, 0x01, 0x0, 0x00, 0x543c02cc
#define IOMUXC_PAD_SD1_DATA3__FLEXIO1_FLEXIO13                              0x543c011c, 0x04, 0x543c039c, 0x01, 0x543c02cc
#define IOMUXC_PAD_SD1_DATA3__GPIO3_IO13                                    0x543c011c, 0x05, 0x0, 0x00, 0x543c02cc
#define IOMUXC_PAD_SD1_DATA3__LPSPI1_PCS1                                   0x543c011c, 0x03, 0x543c0424, 0x00, 0x543c02cc
#define IOMUXC_PAD_SD1_DATA4__USDHC1_DATA4                                  0x543c0120, 0x00, 0x0, 0x00, 0x543c02d0
#define IOMUXC_PAD_SD1_DATA4__FLEXSPI1_A_DATA4                              0x543c0120, 0x01, 0x0, 0x00, 0x543c02d0
#define IOMUXC_PAD_SD1_DATA4__FLEXIO1_FLEXIO14                              0x543c0120, 0x04, 0x543c03a0, 0x01, 0x543c02d0
#define IOMUXC_PAD_SD1_DATA4__GPIO3_IO14                                    0x543c0120, 0x05, 0x0, 0x00, 0x543c02d0
#define IOMUXC_PAD_SD1_DATA4__LPSPI1_PCS0                                   0x543c0120, 0x03, 0x543c0420, 0x00, 0x543c02d0
#define IOMUXC_PAD_SD1_DATA5__USDHC1_DATA5                                  0x543c0124, 0x00, 0x0, 0x00, 0x543c02d4
#define IOMUXC_PAD_SD1_DATA5__FLEXSPI1_A_DATA5                              0x543c0124, 0x01, 0x0, 0x00, 0x543c02d4
#define IOMUXC_PAD_SD1_DATA5__USDHC1_RESET_B                                0x543c0124, 0x02, 0x0, 0x00, 0x543c02d4
#define IOMUXC_PAD_SD1_DATA5__FLEXIO1_FLEXIO15                              0x543c0124, 0x04, 0x543c03a4, 0x01, 0x543c02d4
#define IOMUXC_PAD_SD1_DATA5__GPIO3_IO15                                    0x543c0124, 0x05, 0x0, 0x00, 0x543c02d4
#define IOMUXC_PAD_SD1_DATA5__LPSPI1_SIN                                    0x543c0124, 0x03, 0x543c042c, 0x00, 0x543c02d4
#define IOMUXC_PAD_SD1_DATA6__USDHC1_DATA6                                  0x543c0128, 0x00, 0x0, 0x00, 0x543c02d8
#define IOMUXC_PAD_SD1_DATA6__FLEXSPI1_A_DATA6                              0x543c0128, 0x01, 0x0, 0x00, 0x543c02d8
#define IOMUXC_PAD_SD1_DATA6__USDHC1_CD_B                                   0x543c0128, 0x02, 0x0, 0x00, 0x543c02d8
#define IOMUXC_PAD_SD1_DATA6__FLEXIO1_FLEXIO16                              0x543c0128, 0x04, 0x543c03a8, 0x01, 0x543c02d8
#define IOMUXC_PAD_SD1_DATA6__GPIO3_IO16                                    0x543c0128, 0x05, 0x0, 0x00, 0x543c02d8
#define IOMUXC_PAD_SD1_DATA6__LPSPI1_SCK                                    0x543c0128, 0x03, 0x543c0428, 0x00, 0x543c02d8
#define IOMUXC_PAD_SD1_DATA7__USDHC1_DATA7                                  0x543c012c, 0x00, 0x0, 0x00, 0x543c02dc
#define IOMUXC_PAD_SD1_DATA7__FLEXSPI1_A_DATA7                              0x543c012c, 0x01, 0x0, 0x00, 0x543c02dc
#define IOMUXC_PAD_SD1_DATA7__USDHC1_WP                                     0x543c012c, 0x02, 0x0, 0x00, 0x543c02dc
#define IOMUXC_PAD_SD1_DATA7__FLEXIO1_FLEXIO17                              0x543c012c, 0x04, 0x543c03ac, 0x01, 0x543c02dc
#define IOMUXC_PAD_SD1_DATA7__GPIO3_IO17                                    0x543c012c, 0x05, 0x0, 0x00, 0x543c02dc
#define IOMUXC_PAD_SD1_DATA7__LPSPI1_SOUT                                   0x543c012c, 0x03, 0x543c0430, 0x00, 0x543c02dc
#define IOMUXC_PAD_SD1_STROBE__USDHC1_STROBE                                0x543c0130, 0x00, 0x0, 0x00, 0x543c02e0
#define IOMUXC_PAD_SD1_STROBE__FLEXSPI1_A_DQS                               0x543c0130, 0x01, 0x0, 0x00, 0x543c02e0
#define IOMUXC_PAD_SD1_STROBE__FLEXIO1_FLEXIO18                             0x543c0130, 0x04, 0x543c03b0, 0x01, 0x543c02e0
#define IOMUXC_PAD_SD1_STROBE__GPIO3_IO18                                   0x543c0130, 0x05, 0x0, 0x00, 0x543c02e0
#define IOMUXC_PAD_SD2_VSELECT__USDHC2_VSELECT                              0x543c0134, 0x00, 0x0, 0x00, 0x543c02e4
#define IOMUXC_PAD_SD2_VSELECT__USDHC2_WP                                   0x543c0134, 0x01, 0x0, 0x00, 0x543c02e4
#define IOMUXC_PAD_SD2_VSELECT__LPTMR2_ALT3                                 0x543c0134, 0x02, 0x543c0450, 0x01, 0x543c02e4
#define IOMUXC_PAD_SD2_VSELECT__FLEXIO1_FLEXIO19                            0x543c0134, 0x04, 0x0, 0x00, 0x543c02e4
#define IOMUXC_PAD_SD2_VSELECT__GPIO3_IO19                                  0x543c0134, 0x05, 0x0, 0x00, 0x543c02e4
#define IOMUXC_PAD_SD2_VSELECT__CCMSRCGPCMIX_EXT_CLK1                       0x543c0134, 0x06, 0x543c0368, 0x00, 0x543c02e4
#define IOMUXC_PAD_SD3_CLK__USDHC3_CLK                                      0x543c0138, 0x00, 0x543c04e8, 0x01, 0x543c02e8
#define IOMUXC_PAD_SD3_CLK__FLEXSPI1_A_SCLK                                 0x543c0138, 0x01, 0x0, 0x00, 0x543c02e8
#define IOMUXC_PAD_SD3_CLK__LPUART1_CTS_B                                   0x543c0138, 0x02, 0x543c0454, 0x00, 0x543c02e8
#define IOMUXC_PAD_SD3_CLK__FLEXIO1_FLEXIO20                                0x543c0138, 0x04, 0x543c03b4, 0x01, 0x543c02e8
#define IOMUXC_PAD_SD3_CLK__GPIO3_IO20                                      0x543c0138, 0x05, 0x0, 0x00, 0x543c02e8
#define IOMUXC_PAD_SD3_CMD__USDHC3_CMD                                      0x543c013c, 0x00, 0x543c04ec, 0x01, 0x543c02ec
#define IOMUXC_PAD_SD3_CMD__FLEXSPI1_A_SS0_B                                0x543c013c, 0x01, 0x0, 0x00, 0x543c02ec
#define IOMUXC_PAD_SD3_CMD__LPUART1_RTS_B                                   0x543c013c, 0x02, 0x0, 0x00, 0x543c02ec
#define IOMUXC_PAD_SD3_CMD__FLEXIO1_FLEXIO21                                0x543c013c, 0x04, 0x0, 0x00, 0x543c02ec
#define IOMUXC_PAD_SD3_CMD__GPIO3_IO21                                      0x543c013c, 0x05, 0x0, 0x00, 0x543c02ec
#define IOMUXC_PAD_SD3_DATA0__USDHC3_DATA0                                  0x543c0140, 0x00, 0x543c04f0, 0x01, 0x543c02f0
#define IOMUXC_PAD_SD3_DATA0__FLEXSPI1_A_DATA0                              0x543c0140, 0x01, 0x0, 0x00, 0x543c02f0
#define IOMUXC_PAD_SD3_DATA0__LPUART2_CTS_B                                 0x543c0140, 0x02, 0x543c0460, 0x00, 0x543c02f0
#define IOMUXC_PAD_SD3_DATA0__FLEXIO1_FLEXIO22                              0x543c0140, 0x04, 0x543c03b8, 0x01, 0x543c02f0
#define IOMUXC_PAD_SD3_DATA0__GPIO3_IO22                                    0x543c0140, 0x05, 0x0, 0x00, 0x543c02f0
#define IOMUXC_PAD_SD3_DATA1__USDHC3_DATA1                                  0x543c0144, 0x00, 0x543c04f4, 0x01, 0x543c02f4
#define IOMUXC_PAD_SD3_DATA1__FLEXSPI1_A_DATA1                              0x543c0144, 0x01, 0x0, 0x00, 0x543c02f4
#define IOMUXC_PAD_SD3_DATA1__LPUART2_RTS_B                                 0x543c0144, 0x02, 0x0, 0x00, 0x543c02f4
#define IOMUXC_PAD_SD3_DATA1__FLEXIO1_FLEXIO23                              0x543c0144, 0x04, 0x543c03bc, 0x01, 0x543c02f4
#define IOMUXC_PAD_SD3_DATA1__GPIO3_IO23                                    0x543c0144, 0x05, 0x0, 0x00, 0x543c02f4
#define IOMUXC_PAD_SD3_DATA2__USDHC3_DATA2                                  0x543c0148, 0x00, 0x543c04f8, 0x01, 0x543c02f8
#define IOMUXC_PAD_SD3_DATA2__LPI2C4_SDA                                    0x543c0148, 0x02, 0x543c03fc, 0x01, 0x543c02f8
#define IOMUXC_PAD_SD3_DATA2__FLEXSPI1_A_DATA2                              0x543c0148, 0x01, 0x0, 0x00, 0x543c02f8
#define IOMUXC_PAD_SD3_DATA2__FLEXIO1_FLEXIO24                              0x543c0148, 0x04, 0x543c03c0, 0x01, 0x543c02f8
#define IOMUXC_PAD_SD3_DATA2__GPIO3_IO24                                    0x543c0148, 0x05, 0x0, 0x00, 0x543c02f8
#define IOMUXC_PAD_SD3_DATA3__USDHC3_DATA3                                  0x543c014c, 0x00, 0x543c04fc, 0x01, 0x543c02fc
#define IOMUXC_PAD_SD3_DATA3__FLEXSPI1_A_DATA3                              0x543c014c, 0x01, 0x0, 0x00, 0x543c02fc
#define IOMUXC_PAD_SD3_DATA3__LPI2C4_SCL                                    0x543c014c, 0x02, 0x543c03f8, 0x01, 0x543c02fc
#define IOMUXC_PAD_SD3_DATA3__FLEXIO1_FLEXIO25                              0x543c014c, 0x04, 0x543c03c4, 0x01, 0x543c02fc
#define IOMUXC_PAD_SD3_DATA3__GPIO3_IO25                                    0x543c014c, 0x05, 0x0, 0x00, 0x543c02fc
#define IOMUXC_PAD_SD2_CD_B__USDHC2_CD_B                                    0x543c0150, 0x00, 0x0, 0x00, 0x543c0300
#define IOMUXC_PAD_SD2_CD_B__ENET_QOS_1588_EVENT0_IN                        0x543c0150, 0x01, 0x0, 0x00, 0x543c0300
#define IOMUXC_PAD_SD2_CD_B__I3C2_SCL                                       0x543c0150, 0x02, 0x543c03cc, 0x01, 0x543c0300
#define IOMUXC_PAD_SD2_CD_B__FLEXIO1_FLEXIO0                                0x543c0150, 0x04, 0x543c036c, 0x01, 0x543c0300
#define IOMUXC_PAD_SD2_CD_B__GPIO3_IO0                                      0x543c0150, 0x05, 0x0, 0x00, 0x543c0300
#define IOMUXC_PAD_SD2_CD_B__LPI2C1_SCL                                     0x543c0150, 0x03, 0x0, 0x00, 0x543c0300
#define IOMUXC_PAD_SD2_CLK__USDHC2_CLK                                      0x543c0154, 0x00, 0x0, 0x00, 0x543c0304
#define IOMUXC_PAD_SD2_CLK__ENET_QOS_1588_EVENT0_OUT                        0x543c0154, 0x01, 0x0, 0x00, 0x543c0304
#define IOMUXC_PAD_SD2_CLK__I2C1_SDA                                        0x543c0154, 0x03, 0x0, 0x00, 0x543c0304
#define IOMUXC_PAD_SD2_CLK__I3C2_SDA                                        0x543c0154, 0x02, 0x543c03d0, 0x01, 0x543c0304
#define IOMUXC_PAD_SD2_CLK__FLEXIO1_FLEXIO1                                 0x543c0154, 0x04, 0x543c0370, 0x01, 0x543c0304
#define IOMUXC_PAD_SD2_CLK__GPIO3_IO1                                       0x543c0154, 0x05, 0x0, 0x00, 0x543c0304
#define IOMUXC_PAD_SD2_CLK__CCMSRCGPCMIX_OBSERVE0                           0x543c0154, 0x06, 0x0, 0x00, 0x543c0304
#define IOMUXC_PAD_SD2_CLK__LPI2C1_SDA                                      0x543c0154, 0x03, 0x543c03e4, 0x01, 0x543c0304
#define IOMUXC_PAD_SD2_CMD__USDHC2_CMD                                      0x543c0158, 0x00, 0x0, 0x00, 0x543c0308
#define IOMUXC_PAD_SD2_CMD__ENET2_1588_EVENT0_IN                            0x543c0158, 0x01, 0x0, 0x00, 0x543c0308
#define IOMUXC_PAD_SD2_CMD__I3C2_PUR                                        0x543c0158, 0x02, 0x0, 0x00, 0x543c0308
#define IOMUXC_PAD_SD2_CMD__I3C2_PUR_B                                      0x543c0158, 0x03, 0x0, 0x00, 0x543c0308
#define IOMUXC_PAD_SD2_CMD__FLEXIO1_FLEXIO2                                 0x543c0158, 0x04, 0x543c0374, 0x01, 0x543c0308
#define IOMUXC_PAD_SD2_CMD__GPIO3_IO2                                       0x543c0158, 0x05, 0x0, 0x00, 0x543c0308
#define IOMUXC_PAD_SD2_CMD__CCMSRCGPCMIX_OBSERVE1                           0x543c0158, 0x06, 0x0, 0x00, 0x543c0308
#define IOMUXC_PAD_SD2_DATA0__USDHC2_DATA0                                  0x543c015c, 0x00, 0x0, 0x00, 0x543c030c
#define IOMUXC_PAD_SD2_DATA0__ENET2_1588_EVENT0_OUT                         0x543c015c, 0x01, 0x0, 0x00, 0x543c030c
#define IOMUXC_PAD_SD2_DATA0__CAN2_TX                                       0x543c015c, 0x02, 0x0, 0x00, 0x543c030c
#define IOMUXC_PAD_SD2_DATA0__FLEXIO1_FLEXIO3                               0x543c015c, 0x04, 0x543c0378, 0x01, 0x543c030c
#define IOMUXC_PAD_SD2_DATA0__GPIO3_IO3                                     0x543c015c, 0x05, 0x0, 0x00, 0x543c030c
#define IOMUXC_PAD_SD2_DATA0__LPUART1_TX                                    0x543c015c, 0x03, 0x543c045c, 0x00, 0x543c030c
#define IOMUXC_PAD_SD2_DATA0__CCMSRCGPCMIX_OBSERVE2                         0x543c015c, 0x06, 0x0, 0x00, 0x543c030c
#define IOMUXC_PAD_SD2_DATA1__USDHC2_DATA1                                  0x543c0160, 0x00, 0x0, 0x00, 0x543c0310
#define IOMUXC_PAD_SD2_DATA1__ENET2_1588_EVENT1_IN                          0x543c0160, 0x01, 0x0, 0x00, 0x543c0310
#define IOMUXC_PAD_SD2_DATA1__CAN2_RX                                       0x543c0160, 0x02, 0x543c0364, 0x03, 0x543c0310
#define IOMUXC_PAD_SD2_DATA1__FLEXIO1_FLEXIO4                               0x543c0160, 0x04, 0x543c037c, 0x01, 0x543c0310
#define IOMUXC_PAD_SD2_DATA1__GPIO3_IO4                                     0x543c0160, 0x05, 0x0, 0x00, 0x543c0310
#define IOMUXC_PAD_SD2_DATA1__LPUART1_RX                                    0x543c0160, 0x03, 0x543c0458, 0x00, 0x543c0310
#define IOMUXC_PAD_SD2_DATA1__CCMSRCGPCMIX_WAIT                             0x543c0160, 0x06, 0x0, 0x00, 0x543c0310
#define IOMUXC_PAD_SD2_DATA2__USDHC2_DATA2                                  0x543c0164, 0x00, 0x0, 0x00, 0x543c0314
#define IOMUXC_PAD_SD2_DATA2__ENET2_1588_EVENT1_OUT                         0x543c0164, 0x01, 0x0, 0x00, 0x543c0314
#define IOMUXC_PAD_SD2_DATA2__MQS2_RIGHT                                    0x543c0164, 0x02, 0x0, 0x00, 0x543c0314
#define IOMUXC_PAD_SD2_DATA2__FLEXIO1_FLEXIO5                               0x543c0164, 0x04, 0x543c0380, 0x01, 0x543c0314
#define IOMUXC_PAD_SD2_DATA2__GPIO3_IO5                                     0x543c0164, 0x05, 0x0, 0x00, 0x543c0314
#define IOMUXC_PAD_SD2_DATA2__LPUART2_TX                                    0x543c0164, 0x03, 0x543c0468, 0x00, 0x543c0314
#define IOMUXC_PAD_SD2_DATA2__CCMSRCGPCMIX_STOP                             0x543c0164, 0x06, 0x0, 0x00, 0x543c0314
#define IOMUXC_PAD_SD2_DATA3__USDHC2_DATA3                                  0x543c0168, 0x00, 0x0, 0x00, 0x543c0318
#define IOMUXC_PAD_SD2_DATA3__LPTMR2_ALT1                                   0x543c0168, 0x01, 0x543c0448, 0x01, 0x543c0318
#define IOMUXC_PAD_SD2_DATA3__MQS2_LEFT                                     0x543c0168, 0x02, 0x0, 0x00, 0x543c0318
#define IOMUXC_PAD_SD2_DATA3__FLEXIO1_FLEXIO6                               0x543c0168, 0x04, 0x543c0384, 0x01, 0x543c0318
#define IOMUXC_PAD_SD2_DATA3__GPIO3_IO6                                     0x543c0168, 0x05, 0x0, 0x00, 0x543c0318
#define IOMUXC_PAD_SD2_DATA3__LPUART2_RX                                    0x543c0168, 0x03, 0x543c0464, 0x00, 0x543c0318
#define IOMUXC_PAD_SD2_DATA3__CCMSRCGPCMIX_EARLY_RESET                      0x543c0168, 0x06, 0x0, 0x00, 0x543c0318
#define IOMUXC_PAD_SD2_RESET_B__USDHC2_RESET_B                              0x543c016c, 0x00, 0x0, 0x00, 0x543c031c
#define IOMUXC_PAD_SD2_RESET_B__LPTMR2_ALT2                                 0x543c016c, 0x01, 0x543c044c, 0x01, 0x543c031c
#define IOMUXC_PAD_SD2_RESET_B__FLEXIO1_FLEXIO7                             0x543c016c, 0x04, 0x543c0388, 0x01, 0x543c031c
#define IOMUXC_PAD_SD2_RESET_B__GPIO3_IO7                                   0x543c016c, 0x05, 0x0, 0x00, 0x543c031c
#define IOMUXC_PAD_SD2_RESET_B__CCMSRCGPCMIX_SYSTEM_RESET                   0x543c016c, 0x06, 0x0, 0x00, 0x543c031c
#define IOMUXC_PAD_I2C1_SCL__LPI2C1_SCL                                     0x543c0170, 0x00, 0x543c03e0, 0x02, 0x543c0320
#define IOMUXC_PAD_I2C1_SCL__I3C1_SCL                                       0x543c0170, 0x01, 0x0, 0x00, 0x543c0320
#define IOMUXC_PAD_I2C1_SCL__LPUART1_DCB_B                                  0x543c0170, 0x02, 0x0, 0x00, 0x543c0320
#define IOMUXC_PAD_I2C1_SCL__TPM2_CH0                                       0x543c0170, 0x03, 0x0, 0x00, 0x543c0320
#define IOMUXC_PAD_I2C1_SCL__GPIO1_IO0                                      0x543c0170, 0x05, 0x0, 0x00, 0x543c0320
#define IOMUXC_PAD_I2C1_SDA__LPI2C1_SDA                                     0x543c0174, 0x00, 0x543c03e4, 0x02, 0x543c0324
#define IOMUXC_PAD_I2C1_SDA__I3C1_SDA                                       0x543c0174, 0x01, 0x0, 0x00, 0x543c0324
#define IOMUXC_PAD_I2C1_SDA__LPUART1_RIN_B                                  0x543c0174, 0x02, 0x0, 0x00, 0x543c0324
#define IOMUXC_PAD_I2C1_SDA__TPM2_CH1                                       0x543c0174, 0x03, 0x0, 0x00, 0x543c0324
#define IOMUXC_PAD_I2C1_SDA__GPIO1_IO1                                      0x543c0174, 0x05, 0x0, 0x00, 0x543c0324
#define IOMUXC_PAD_I2C2_SCL__LPI2C2_SCL                                     0x543c0178, 0x00, 0x543c03e8, 0x01, 0x543c0328
#define IOMUXC_PAD_I2C2_SCL__I3C1_PUR                                       0x543c0178, 0x01, 0x0, 0x00, 0x543c0328
#define IOMUXC_PAD_I2C2_SCL__LPUART2_DCB_B                                  0x543c0178, 0x02, 0x0, 0x00, 0x543c0328
#define IOMUXC_PAD_I2C2_SCL__TPM2_CH2                                       0x543c0178, 0x03, 0x0, 0x00, 0x543c0328
#define IOMUXC_PAD_I2C2_SCL__SAI1_RX_SYNC                                   0x543c0178, 0x04, 0x0, 0x00, 0x543c0328
#define IOMUXC_PAD_I2C2_SCL__GPIO1_IO3                                      0x543c0178, 0x05, 0x0, 0x00, 0x543c0328
#define IOMUXC_PAD_I2C2_SCL__I3C1_PUR_B                                     0x543c0178, 0x06, 0x0, 0x00, 0x543c0328
#define IOMUXC_PAD_I2C2_SDA__LPI2C2_SDA                                     0x543c017c, 0x00, 0x543c03ec, 0x01, 0x543c032c
#define IOMUXC_PAD_I2C2_SDA__LPUART2_RIN_B                                  0x543c017c, 0x02, 0x0, 0x00, 0x543c032c
#define IOMUXC_PAD_I2C2_SDA__TPM2_CH3                                       0x543c017c, 0x03, 0x0, 0x00, 0x543c032c
#define IOMUXC_PAD_I2C2_SDA__SAI1_RX_BCLK                                   0x543c017c, 0x04, 0x0, 0x00, 0x543c032c
#define IOMUXC_PAD_I2C2_SDA__GPIO1_IO3                                      0x543c017c, 0x05, 0x0, 0x00, 0x543c032c
#define IOMUXC_PAD_UART1_RXD__LPUART1_RX                                    0x543c0180, 0x00, 0x543c0458, 0x01, 0x543c0330
#define IOMUXC_PAD_UART1_RXD__ELE_UART_RX                                   0x543c0180, 0x01, 0x0, 0x00, 0x543c0330
#define IOMUXC_PAD_UART1_RXD__LPSPI2_SIN                                    0x543c0180, 0x02, 0x543c0440, 0x02, 0x543c0330
#define IOMUXC_PAD_UART1_RXD__TPM1_CH0                                      0x543c0180, 0x03, 0x0, 0x00, 0x543c0330
#define IOMUXC_PAD_UART1_RXD__GPIO1_IO4                                     0x543c0180, 0x05, 0x0, 0x00, 0x543c0330
#define IOMUXC_PAD_UART1_TXD__LPUART1_TX                                    0x543c0184, 0x00, 0x543c045c, 0x01, 0x543c0334
#define IOMUXC_PAD_UART1_TXD__ELE_UART_TX                                   0x543c0184, 0x01, 0x0, 0x00, 0x543c0334
#define IOMUXC_PAD_UART1_TXD__LPSPI2_PCS0                                   0x543c0184, 0x02, 0x543c0434, 0x02, 0x543c0334
#define IOMUXC_PAD_UART1_TXD__TPM1_CH1                                      0x543c0184, 0x03, 0x0, 0x00, 0x543c0334
#define IOMUXC_PAD_UART1_TXD__GPIO1_IO5                                     0x543c0184, 0x05, 0x0, 0x00, 0x543c0334
#define IOMUXC_PAD_UART2_RXD__LPUART2_RX                                    0x543c0188, 0x00, 0x543c0464, 0x01, 0x543c0338
#define IOMUXC_PAD_UART2_RXD__LPUART1_CTS_B                                 0x543c0188, 0x01, 0x543c0454, 0x01, 0x543c0338
#define IOMUXC_PAD_UART2_RXD__LPSPI2_SOUT                                   0x543c0188, 0x02, 0x543c0444, 0x02, 0x543c0338
#define IOMUXC_PAD_UART2_RXD__TPM1_CH2                                      0x543c0188, 0x03, 0x0, 0x00, 0x543c0338
#define IOMUXC_PAD_UART2_RXD__SAI1_MCLK                                     0x543c0188, 0x04, 0x543c04d4, 0x00, 0x543c0338
#define IOMUXC_PAD_UART2_RXD__GPIO1_IO6                                     0x543c0188, 0x05, 0x0, 0x00, 0x543c0338
#define IOMUXC_PAD_UART2_TXD__LPUART2_TX                                    0x543c018c, 0x00, 0x543c0468, 0x01, 0x543c033c
#define IOMUXC_PAD_UART2_TXD__LPUART1_RTS_B                                 0x543c018c, 0x01, 0x0, 0x00, 0x543c033c
#define IOMUXC_PAD_UART2_TXD__LPSPI2_SCK                                    0x543c018c, 0x02, 0x543c043c, 0x02, 0x543c033c
#define IOMUXC_PAD_UART2_TXD__TPM1_CH3                                      0x543c018c, 0x03, 0x0, 0x00, 0x543c033c
#define IOMUXC_PAD_UART2_TXD__GPIO1_IO7                                     0x543c018c, 0x05, 0x0, 0x00, 0x543c033c
#define IOMUXC_PAD_UART2_TXD__SAI3_TX_SYNC                                  0x543c018c, 0x07, 0x543c04e0, 0x02, 0x543c033c
#define IOMUXC_PAD_PDM_CLK__PDM_CLK                                         0x543c0190, 0x00, 0x0, 0x00, 0x543c0340
#define IOMUXC_PAD_PDM_CLK__MQS1_LEFT                                       0x543c0190, 0x01, 0x0, 0x00, 0x543c0340
#define IOMUXC_PAD_PDM_CLK__LPTMR1_ALT1                                     0x543c0190, 0x04, 0x0, 0x00, 0x543c0340
#define IOMUXC_PAD_PDM_CLK__GPIO1_IO8                                       0x543c0190, 0x05, 0x0, 0x00, 0x543c0340
#define IOMUXC_PAD_PDM_CLK__CAN1_TX                                         0x543c0190, 0x06, 0x0, 0x00, 0x543c0340
#define IOMUXC_PAD_PDM_BIT_STREAM0__PDM_BIT_STREAM0                         0x543c0194, 0x00, 0x543c04c4, 0x02, 0x543c0344
#define IOMUXC_PAD_PDM_BIT_STREAM0__MQS1_RIGHT                              0x543c0194, 0x01, 0x0, 0x00, 0x543c0344
#define IOMUXC_PAD_PDM_BIT_STREAM0__LPSPI1_PCS1                             0x543c0194, 0x02, 0x543c0424, 0x01, 0x543c0344
#define IOMUXC_PAD_PDM_BIT_STREAM0__TPM1_EXTCLK                             0x543c0194, 0x03, 0x0, 0x00, 0x543c0344
#define IOMUXC_PAD_PDM_BIT_STREAM0__LPTMR1_ALT2                             0x543c0194, 0x04, 0x0, 0x00, 0x543c0344
#define IOMUXC_PAD_PDM_BIT_STREAM0__GPIO1_IO9                               0x543c0194, 0x05, 0x0, 0x00, 0x543c0344
#define IOMUXC_PAD_PDM_BIT_STREAM0__CAN1_RX                                 0x543c0194, 0x06, 0x543c0360, 0x01, 0x543c0344
#define IOMUXC_PAD_PDM_BIT_STREAM1__PDM_BIT_STREAM1                         0x543c0198, 0x00, 0x543c04c8, 0x02, 0x543c0348
#define IOMUXC_PAD_PDM_BIT_STREAM1__LPSPI2_PCS1                             0x543c0198, 0x02, 0x543c0438, 0x01, 0x543c0348
#define IOMUXC_PAD_PDM_BIT_STREAM1__TPM2_EXTCLK                             0x543c0198, 0x03, 0x0, 0x00, 0x543c0348
#define IOMUXC_PAD_PDM_BIT_STREAM1__LPTMR1_ALT3                             0x543c0198, 0x04, 0x0, 0x00, 0x543c0348
#define IOMUXC_PAD_PDM_BIT_STREAM1__GPIO1_IO10                              0x543c0198, 0x05, 0x0, 0x00, 0x543c0348
#define IOMUXC_PAD_PDM_BIT_STREAM1__CCMSRCGPCMIX_EXT_CLK1                   0x543c0198, 0x06, 0x543c0368, 0x01, 0x543c0348
#define IOMUXC_PAD_SAI1_TXFS__SAI1_TX_SYNC                                  0x543c019c, 0x00, 0x0, 0x00, 0x543c034c
#define IOMUXC_PAD_SAI1_TXFS__SAI1_TX_DATA1                                 0x543c019c, 0x01, 0x0, 0x00, 0x543c034c
#define IOMUXC_PAD_SAI1_TXFS__LPSPI1_PCS0                                   0x543c019c, 0x02, 0x543c0420, 0x01, 0x543c034c
#define IOMUXC_PAD_SAI1_TXFS__LPUART2_DTR_B                                 0x543c019c, 0x03, 0x0, 0x00, 0x543c034c
#define IOMUXC_PAD_SAI1_TXFS__MQS1_LEFT                                     0x543c019c, 0x04, 0x0, 0x00, 0x543c034c
#define IOMUXC_PAD_SAI1_TXFS__GPIO1_IO11                                    0x543c019c, 0x05, 0x0, 0x00, 0x543c034c
#define IOMUXC_PAD_SAI1_TXC__SAI1_TX_BCLK                                   0x543c01a0, 0x00, 0x0, 0x00, 0x543c0350
#define IOMUXC_PAD_SAI1_TXC__LPUART2_CTS_B                                  0x543c01a0, 0x01, 0x543c0460, 0x01, 0x543c0350
#define IOMUXC_PAD_SAI1_TXC__LPSPI1_SIN                                     0x543c01a0, 0x02, 0x543c042c, 0x01, 0x543c0350
#define IOMUXC_PAD_SAI1_TXC__LPUART1_DSR_B                                  0x543c01a0, 0x03, 0x0, 0x00, 0x543c0350
#define IOMUXC_PAD_SAI1_TXC__CAN1_RX                                        0x543c01a0, 0x04, 0x543c0360, 0x02, 0x543c0350
#define IOMUXC_PAD_SAI1_TXC__GPIO1_IO12                                     0x543c01a0, 0x05, 0x0, 0x00, 0x543c0350
#define IOMUXC_PAD_SAI1_TXD0__SAI1_TX_DATA0                                 0x543c01a4, 0x00, 0x0, 0x00, 0x543c0354
#define IOMUXC_PAD_SAI1_TXD0__LPUART2_RTS_B                                 0x543c01a4, 0x01, 0x0, 0x00, 0x543c0354
#define IOMUXC_PAD_SAI1_TXD0__LPSPI1_SCK                                    0x543c01a4, 0x02, 0x543c0428, 0x01, 0x543c0354
#define IOMUXC_PAD_SAI1_TXD0__LPUART1_DTR_B                                 0x543c01a4, 0x03, 0x0, 0x00, 0x543c0354
#define IOMUXC_PAD_SAI1_TXD0__CAN1_TX                                       0x543c01a4, 0x04, 0x0, 0x00, 0x543c0354
#define IOMUXC_PAD_SAI1_TXD0__GPIO1_IO13                                    0x543c01a4, 0x05, 0x0, 0x00, 0x543c0354
#define IOMUXC_PAD_SAI1_TXD0__SAI1_MCLK                                     0x543c01a4, 0x06, 0x543c04d4, 0x01, 0x543c0354
#define IOMUXC_PAD_SAI1_RXD0__SAI1_RX_DATA0                                 0x543c01a8, 0x00, 0x0, 0x00, 0x543c0358
#define IOMUXC_PAD_SAI1_RXD0__SAI1_MCLK                                     0x543c01a8, 0x01, 0x543c04d4, 0x02, 0x543c0358
#define IOMUXC_PAD_SAI1_RXD0__LPSPI1_SOUT                                   0x543c01a8, 0x02, 0x543c0430, 0x01, 0x543c0358
#define IOMUXC_PAD_SAI1_RXD0__LPUART2_DSR_B                                 0x543c01a8, 0x03, 0x0, 0x00, 0x543c0358
#define IOMUXC_PAD_SAI1_RXD0__MQS1_RIGHT                                    0x543c01a8, 0x04, 0x0, 0x00, 0x543c0358
#define IOMUXC_PAD_SAI1_RXD0__GPIO1_IO14                                    0x543c01a8, 0x05, 0x0, 0x00, 0x543c0358
#define IOMUXC_PAD_WDOG_ANY__WDOG1_WDOG_ANY                                 0x543c01ac, 0x00, 0x0, 0x00, 0x543c035c
#define IOMUXC_PAD_WDOG_ANY__GPIO1_IO15                                     0x543c01ac, 0x05, 0x0, 0x00, 0x543c035c
/*@}*/

#define IOMUXC_PAD_MUX_MODE_MASK  (0x7U)
#define IOMUXC_PAD_MUX_MODE_SHIFT (0U)
#define IOMUXC_PAD_MUX_MODE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_MUX_MODE_SHIFT)) & IOMUXC_PAD_MUX_MODE_MASK)
#define IOMUXC_PAD_SION_MASK      (0x10U)
#define IOMUXC_PAD_SION_SHIFT     (4U)
#define IOMUXC_PAD_SION(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_SION_SHIFT)) & IOMUXC_PAD_SION_MASK)

#define IOMUXC_PAD_DSE_MASK       (0x7EU)
#define IOMUXC_PAD_DSE_SHIFT      (1U)
#define IOMUXC_PAD_DSE(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_DSE_SHIFT)) & IOMUXC_PAD_DSE_MASK)
#define IOMUXC_PAD_FSEL1_MASK     (0x180U)
#define IOMUXC_PAD_FSEL1_SHIFT    (7U)
#define IOMUXC_PAD_FSEL1(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_FSEL1_SHIFT)) & IOMUXC_PAD_FSEL1_MASK)
#define IOMUXC_PAD_PU_MASK        (0x200U)
#define IOMUXC_PAD_PU_SHIFT       (9U)
#define IOMUXC_PAD_PU(x)          (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_PU_SHIFT)) & IOMUXC_PAD_PU_MASK)
#define IOMUXC_PAD_PD_MASK        (0x400U)
#define IOMUXC_PAD_PD_SHIFT       (10U)
#define IOMUXC_PAD_PD(x)          (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_PD_SHIFT)) & IOMUXC_PAD_PD_MASK)
#define IOMUXC_PAD_OD_MASK        (0x800U)
#define IOMUXC_PAD_OD_SHIFT       (11U)
#define IOMUXC_PAD_OD(x)          (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_OD_SHIFT)) & IOMUXC_PAD_OD_MASK)
#define IOMUXC_PAD_HYS_MASK       (0x1000U)
#define IOMUXC_PAD_HYS_SHIFT      (11U)
#define IOMUXC_PAD_HYS(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_HYS_SHIFT)) & IOMUXC_PAD_HYS_MASK)
#define IOMUXC_PAD_APC_MASK       (0xFF000000U)
#define IOMUXC_PAD_APC_SHIFT      (24U)
#define IOMUXC_PAD_APC(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_PAD_APC_SHIFT)) & IOMUXC_PAD_APC_MASK)

#define SECURE_ADDR_MASK          (0x10000000U)
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
#define IOMUXC_REG_ADDR(x)        (x)
#else
#define IOMUXC_REG_ADDR(x)        ((x) & (~SECURE_ADDR_MASK))
#endif

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

/*! @name Configuration */
/*@{*/

/*!
 * @brief Sets the IOMUXC pin mux mode.
 * @note The first five parameters can be filled with the pin function ID macros.
 *
 * @param muxRegister    The pin mux register
 * @param muxMode        The pin mux mode
 * @param inputRegister  The select input register
 * @param inputDaisy     The input daisy
 * @param configRegister The config register
 * @param inputOn        The software input on
 */
static inline void IOMUXC_SetPinMux(uint32_t muxRegister,
                                    uint32_t muxMode,
                                    uint32_t inputRegister,
                                    uint32_t inputDaisy,
                                    uint32_t configRegister,
                                    uint32_t inputOnfield)
{
    if (muxRegister != 0U)
    {
        *((volatile uint32_t *)(uintptr_t)IOMUXC_REG_ADDR(muxRegister)) =
            IOMUXC_PAD_MUX_MODE(muxMode) | IOMUXC_PAD_SION(inputOnfield);
    }

    if (inputRegister != 0U)
    {
        *((volatile uint32_t *)(uintptr_t)IOMUXC_REG_ADDR(inputRegister)) = inputDaisy;
    }
}
/*!
 * @brief Sets the IOMUXC pin configuration.
 * @note The previous five parameters can be filled with the pin function ID macros.
 *
 * @param muxRegister    The pin mux register
 * @param muxMode        The pin mux mode
 * @param inputRegister  The select input register
 * @param inputDaisy     The input daisy
 * @param configRegister The config register
 * @param configValue    The pin config value
 */
static inline void IOMUXC_SetPinConfig(uint32_t muxRegister,
                                       uint32_t muxMode,
                                       uint32_t inputRegister,
                                       uint32_t inputDaisy,
                                       uint32_t configRegister,
                                       uint32_t configValue)
{
    if (configRegister != 0U)
    {
        *((volatile uint32_t *)(uintptr_t)IOMUXC_REG_ADDR(configRegister)) = configValue;
    }
}
/*@}*/

#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @}*/

#endif /* _FSL_IOMUXC_H_ */
