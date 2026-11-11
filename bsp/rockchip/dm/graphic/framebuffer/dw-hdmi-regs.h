/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __DW_HDMI_REGS_H__
#define __DW_HDMI_REGS_H__

/* Identification and interrupt registers. */
#define HDMI_CONFIG2_ID                                      0x0006
#define HDMI_DESIGN_ID                                       0x0000
#define HDMI_IH_PHY_STAT0                                    0x0104
#define HDMI_IH_I2CMPHY_STAT0                                0x0108
#define HDMI_IH_MUTE_FC_STAT2                                0x0182
#define HDMI_IH_MUTE                                         0x01ff

#define HDMI_IH_PHY_STAT0_HPD                                0x01
#define HDMI_IH_MUTE_FC_STAT2_OVERFLOW_MASK                  0x03
#define HDMI_IH_MUTE_MUTE_ALL_INTERRUPT                      0x01
#define HDMI_IH_MUTE_MUTE_WAKEUP_INTERRUPT                   0x02

/* Video sampler. */
#define HDMI_TX_INVID0                                       0x0200
#define HDMI_TX_INSTUFFING                                   0x0201
#define HDMI_TX_GYDATA0                                      0x0202
#define HDMI_TX_GYDATA1                                      0x0203
#define HDMI_TX_RCRDATA0                                     0x0204
#define HDMI_TX_RCRDATA1                                     0x0205
#define HDMI_TX_BCBDATA0                                     0x0206
#define HDMI_TX_BCBDATA1                                     0x0207

#define HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE         0x00
#define HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET                  0
#define HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE            0x01
#define HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE           0x02
#define HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE           0x04

/* Video packetizer. */
#define HDMI_VP_PR_CD                                        0x0801
#define HDMI_VP_STUFF                                        0x0802
#define HDMI_VP_REMAP                                        0x0803
#define HDMI_VP_CONF                                         0x0804

#define HDMI_VP_PR_CD_COLOR_DEPTH_MASK                       0xf0
#define HDMI_VP_PR_CD_COLOR_DEPTH_OFFSET                     4
#define HDMI_VP_PR_CD_DESIRED_PR_FACTOR_MASK                 0x0f
#define HDMI_VP_PR_CD_DESIRED_PR_FACTOR_OFFSET               0
#define HDMI_VP_STUFF_IDEFAULT_PHASE_MASK                    0x20
#define HDMI_VP_STUFF_PP_STUFFING_MASK                       0x02
#define HDMI_VP_STUFF_PP_STUFFING_STUFFING_MODE              0x02
#define HDMI_VP_STUFF_PR_STUFFING_MASK                       0x01
#define HDMI_VP_STUFF_PR_STUFFING_STUFFING_MODE              0x01
#define HDMI_VP_STUFF_YCC422_STUFFING_MASK                   0x04
#define HDMI_VP_STUFF_YCC422_STUFFING_STUFFING_MODE          0x04
#define HDMI_VP_CONF_BYPASS_EN_MASK                          0x40
#define HDMI_VP_CONF_BYPASS_EN_ENABLE                        0x40
#define HDMI_VP_CONF_PP_EN_ENMASK                            0x20
#define HDMI_VP_CONF_PP_EN_DISABLE                           0x00
#define HDMI_VP_CONF_PR_EN_MASK                              0x10
#define HDMI_VP_CONF_PR_EN_DISABLE                           0x00
#define HDMI_VP_CONF_YCC422_EN_MASK                          0x08
#define HDMI_VP_CONF_YCC422_EN_DISABLE                       0x00
#define HDMI_VP_CONF_BYPASS_SELECT_MASK                      0x04
#define HDMI_VP_CONF_BYPASS_SELECT_VID_PACKETIZER            0x04
#define HDMI_VP_CONF_OUTPUT_SELECTOR_MASK                    0x03
#define HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS                  0x03

/* Frame composer. */
#define HDMI_FC_INVIDCONF                                    0x1000
#define HDMI_FC_INHACTV0                                     0x1001
#define HDMI_FC_INHACTV1                                     0x1002
#define HDMI_FC_INHBLANK0                                    0x1003
#define HDMI_FC_INHBLANK1                                    0x1004
#define HDMI_FC_INVACTV0                                     0x1005
#define HDMI_FC_INVACTV1                                     0x1006
#define HDMI_FC_INVBLANK                                     0x1007
#define HDMI_FC_HSYNCINDELAY0                                0x1008
#define HDMI_FC_HSYNCINDELAY1                                0x1009
#define HDMI_FC_HSYNCINWIDTH0                                0x100a
#define HDMI_FC_HSYNCINWIDTH1                                0x100b
#define HDMI_FC_VSYNCINDELAY                                 0x100c
#define HDMI_FC_VSYNCINWIDTH                                 0x100d
#define HDMI_FC_CTRLDUR                                      0x1011
#define HDMI_FC_EXCTRLDUR                                    0x1012
#define HDMI_FC_EXCTRLSPAC                                   0x1013
#define HDMI_FC_CH0PREAM                                     0x1014
#define HDMI_FC_CH1PREAM                                     0x1015
#define HDMI_FC_CH2PREAM                                     0x1016
#define HDMI_FC_AUDICONF0                                    0x1025
#define HDMI_FC_AUDICONF1                                    0x1026
#define HDMI_FC_AUDICONF2                                    0x1027
#define HDMI_FC_AUDICONF3                                    0x1028
#define HDMI_FC_AUDSCONF                                     0x1063
#define HDMI_FC_AUDSCHNLS7                                   0x106e
#define HDMI_FC_AUDSCHNLS8                                   0x106f
#define HDMI_FC_DBGFORCE                                     0x1200
#define HDMI_FC_DBGTMDS0                                     0x1219
#define HDMI_FC_DBGTMDS1                                     0x121a
#define HDMI_FC_DBGTMDS2                                     0x121b

#define HDMI_FC_INVIDCONF_HDCP_KEEPOUT_ACTIVE                0x80
#define HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_HIGH      0x40
#define HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_LOW       0x00
#define HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_HIGH      0x20
#define HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_LOW       0x00
#define HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_HIGH         0x10
#define HDMI_FC_INVIDCONF_DVI_MODEZ_HDMI_MODE                0x08
#define HDMI_FC_INVIDCONF_DVI_MODEZ_DVI_MODE                 0x00
#define HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_LOW        0x00
#define HDMI_FC_INVIDCONF_IN_I_P_PROGRESSIVE                 0x00
#define HDMI_FC_AUDICONF0_CC_MASK                            0x70
#define HDMI_FC_AUDICONF0_CC_OFFSET                          4
#define HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_MASK              0x01
#define HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT0           0x00
#define HDMI_FC_DBGFORCE_FORCEVIDEO                          0x01

/* I2S audio sampler and audio clock regeneration. */
#define HDMI_AUD_CONF0                                       0x3100
#define HDMI_AUD_CONF1                                       0x3101
#define HDMI_AUD_CONF2                                       0x3103
#define HDMI_AUD_N1                                          0x3200
#define HDMI_AUD_N2                                          0x3201
#define HDMI_AUD_N3                                          0x3202
#define HDMI_AUD_CTS1                                        0x3203
#define HDMI_AUD_CTS2                                        0x3204
#define HDMI_AUD_CTS3                                        0x3205
#define HDMI_AUD_INPUTCLKFS                                  0x3206

#define HDMI_AUD_CONF0_SW_RESET                              0x80
#define HDMI_AUD_CONF0_I2S_SELECT                            0x20
#define HDMI_AUD_CONF0_I2S_EN0                               0x01
#define HDMI_AUD_CONF1_MODE_I2S                              0x00
#define HDMI_AUD_CONF1_WIDTH_16                              0x10
#define HDMI_AUD_CONF1_WIDTH_24                              0x18
#define HDMI_AUD_CONF2_INSERT_PCUV                           0x04
#define HDMI_AUD_CTS3_N_SHIFT_MASK                           0xe0
#define HDMI_AUD_CTS3_CTS_MANUAL                             0x10
#define HDMI_AUD_INPUTCLKFS_64FS                             0x04

/* PHY. */
#define HDMI_PHY_CONF0                                       0x3000
#define HDMI_PHY_TST0                                        0x3001
#define HDMI_PHY_STAT0                                       0x3004
#define HDMI_PHY_MASK0                                       0x3006

#define HDMI_PHY_CONF0_PDZ_MASK                              0x80
#define HDMI_PHY_CONF0_PDZ_OFFSET                            7
#define HDMI_PHY_CONF0_ENTMDS_MASK                           0x40
#define HDMI_PHY_CONF0_ENTMDS_OFFSET                         6
#define HDMI_PHY_CONF0_SVSRET_MASK                           0x20
#define HDMI_PHY_CONF0_SVSRET_OFFSET                         5
#define HDMI_PHY_CONF0_GEN2_PDDQ_MASK                        0x10
#define HDMI_PHY_CONF0_GEN2_PDDQ_OFFSET                      4
#define HDMI_PHY_CONF0_GEN2_TXPWRON_MASK                     0x08
#define HDMI_PHY_CONF0_GEN2_TXPWRON_OFFSET                   3
#define HDMI_PHY_CONF0_SELDATAENPOL_MASK                     0x02
#define HDMI_PHY_CONF0_SELDATAENPOL_OFFSET                   1
#define HDMI_PHY_CONF0_SELDIPIF_MASK                         0x01
#define HDMI_PHY_CONF0_SELDIPIF_OFFSET                       0
#define HDMI_PHY_TST0_TSTCLR_MASK                            0x20
#define HDMI_PHY_TST0_TSTCLR_OFFSET                          5
#define HDMI_PHY_HPD                                         0x02
#define HDMI_PHY_TX_PHY_LOCK                                 0x01

/* PHY I2C master. */
#define HDMI_PHY_I2CM_SLAVE_ADDR                             0x3020
#define HDMI_PHY_I2CM_ADDRESS_ADDR                           0x3021
#define HDMI_PHY_I2CM_DATAO_1_ADDR                           0x3022
#define HDMI_PHY_I2CM_DATAO_0_ADDR                           0x3023
#define HDMI_PHY_I2CM_OPERATION_ADDR                         0x3026
#define HDMI_PHY_I2CM_INT_ADDR                               0x3027
#define HDMI_PHY_I2CM_CTLINT_ADDR                            0x3028

#define HDMI_PHY_I2CM_SLAVE_ADDR_PHY_GEN2                    0x69
#define HDMI_PHY_I2CM_OPERATION_ADDR_WRITE                   0x10
#define HDMI_PHY_I2CM_INT_ADDR_DONE_POL                      0x08
#define HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL            0x08
#define HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL                    0x80
#define HDMI_IH_I2CMPHY_STAT0_ERROR                          0x01
#define HDMI_IH_I2CMPHY_STAT0_DONE                           0x02

/* Main controller. */
#define HDMI_MC_CLKDIS                                       0x4001
#define HDMI_MC_SWRSTZ                                       0x4002
#define HDMI_MC_FLOWCTRL                                     0x4004
#define HDMI_MC_PHYRSTZ                                      0x4005
#define HDMI_MC_HEACPHY_RST                                  0x4007

#define HDMI_MC_CLKDIS_PIXELCLK_DISABLE                      0x01
#define HDMI_MC_CLKDIS_TMDSCLK_DISABLE                       0x02
#define HDMI_MC_CLKDIS_AUDCLK_DISABLE                        0x08
#define HDMI_MC_SWRSTZ_TMDSSWRST_REQ                         0x02
#define HDMI_MC_SWRSTZ_I2SSWRST_REQ                          0x08
#define HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS         0x00
#define HDMI_MC_PHYRSTZ_PHYRSTZ                              0x01
#define HDMI_MC_HEACPHY_RST_ASSERT                           0x01

/* Color space converter. */
#define HDMI_CSC_CFG                                         0x4100
#define HDMI_CSC_SCALE                                       0x4101
#define HDMI_CSC_COEF_A1_MSB                                 0x4102
#define HDMI_CSC_COEF_A1_LSB                                 0x4103
#define HDMI_CSC_COEF_B1_MSB                                 0x410a
#define HDMI_CSC_COEF_B1_LSB                                 0x410b
#define HDMI_CSC_COEF_C1_MSB                                 0x4112
#define HDMI_CSC_COEF_C1_LSB                                 0x4113

#define HDMI_CSC_CFG_INTMODE_DISABLE                         0x00
#define HDMI_CSC_CFG_DECMODE_DISABLE                         0x00
#define HDMI_CSC_SCALE_CSC_COLORDE_PTH_MASK                  0xf0
#define HDMI_CSC_SCALE_CSC_COLORDE_PTH_24BPP                 0x00
#define HDMI_CSC_SCALE_CSCSCALE_MASK                         0x03

/* HDCP polarity and HDMI/DVI selection. */
#define HDMI_A_HDCPCFG0                                      0x5000
#define HDMI_A_VIDPOLCFG                                     0x5009

#define HDMI_A_HDCPCFG0_AVMUTE_MASK                          0x08
#define HDMI_A_HDCPCFG0_AVMUTE_DISABLE                       0x00
#define HDMI_A_HDCPCFG0_HDMIDVI_MASK                         0x01
#define HDMI_A_HDCPCFG0_HDMIDVI_HDMI                         0x01
#define HDMI_A_HDCPCFG0_HDMIDVI_DVI                          0x00
#define HDMI_A_VIDPOLCFG_DATAENPOL_MASK                      0x10
#define HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_HIGH               0x10
#define HDMI_A_VIDPOLCFG_VSYNCPOL_MASK                       0x08
#define HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_HIGH                0x08
#define HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_LOW                 0x00
#define HDMI_A_VIDPOLCFG_HSYNCPOL_MASK                       0x02
#define HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_HIGH                0x02
#define HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_LOW                 0x00

/* DDC I2C interrupt control. */
#define HDMI_I2CM_INT                                        0x7e05
#define HDMI_I2CM_CTLINT                                     0x7e06
#define HDMI_I2CM_INT_DONE_MASK                              0x04
#define HDMI_I2CM_CTLINT_ARB_MASK                            0x04
#define HDMI_I2CM_CTLINT_NAC_MASK                            0x40

/* Synopsys Gen2 PHY internal register addresses. */
#define HDMI_3D_TX_PHY_CKCALCTRL                             0x05
#define HDMI_3D_TX_PHY_CPCE_CTRL                             0x06
#define HDMI_3D_TX_PHY_CKSYMTXCTRL                           0x09
#define HDMI_3D_TX_PHY_VLEVCTRL                              0x0e
#define HDMI_3D_TX_PHY_CURRCTRL                              0x10
#define HDMI_3D_TX_PHY_PLLPHBYCTRL                           0x13
#define HDMI_3D_TX_PHY_GMPCTRL                               0x15
#define HDMI_3D_TX_PHY_MSM_CTRL                              0x17
#define HDMI_3D_TX_PHY_TXTERM                                0x19
#define HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_FB_CLK               (3 << 1)

#endif /* __DW_HDMI_REGS_H__ */
