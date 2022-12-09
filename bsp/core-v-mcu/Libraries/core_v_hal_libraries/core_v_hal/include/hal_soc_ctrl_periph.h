/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna
 * and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HAL_INCLUDE_HAL_SOC_CTRL_PERIPH_H_
#define HAL_INCLUDE_HAL_SOC_CTRL_PERIPH_H_

/* ----------------------------------------------------------------------------
   -- SOC_CTRL Peripheral Access Layer --
   ---------------------------------------------------------------------------- */

/** SOC_CTRL_Type Register Layout Typedef */
typedef struct
{
    volatile uint32_t info; /**< Core information register. */
    volatile uint32_t _reserved_0[2]; /**< Reserved/Unused. */
    volatile uint32_t cl_isolate; /**< Isolate cluster register. */
    volatile uint32_t _reserved_1[23]; /**< Reserved/Unused. */
    volatile uint32_t cl_busy; /**< Cluster busy register. */
    volatile uint32_t cl_bypass; /**< Cluster PMU bypass configuration register. */
    volatile uint32_t jtagreg; /**< JTAG external register. */
    volatile uint32_t l2_sleep; /**< L2 sleep configuration register. */
    volatile uint32_t sleep_ctrl; /**< Alias for SAFE_PMU_SLEEPCTRL. */
    volatile uint32_t _reserved_2[8]; /**< Reserved/Unused. */
    volatile uint32_t corestatus; /**< EOC and chip status register. */
    volatile uint32_t _reserved_30[7]; /**< Reserved/Unused. */
    volatile uint32_t corestatus_ro; /**< EOC and chip status register read mirror. */
    volatile uint32_t _reserved_3[15]; /**< Reserved/Unused. */
    volatile uint32_t safe_pmu_rar; /**< DC/DC configuration register. */
    volatile uint32_t safe_pmu_sleepctrl; /**< Sleep modes configuration register. */
    volatile uint32_t safe_pmu_force; /**< L2 rententive state configuration. */
    volatile uint32_t _reserved_4[13]; /**< Reserved/Unused. */
    volatile uint32_t safe_padfun[4]; /**< Mux config register : pad 0-15, 16-31, 32-47, 48-63. */
    volatile uint32_t safe_sleeppadcfg[4]; /**< Sleep config register : pad 0-15, 16-31, 32-47, 48-63. */
    volatile uint32_t safe_padsleep; /**< Enable Sleep mode for pads. */
    volatile uint32_t _reserved_5[7]; /**< Reserved/Unused. */
    volatile uint32_t safe_padcfg[16]; /**< Function register : pad 0-3, 4-7, 8-11,..., 56-59, 60-63. */
    volatile uint32_t reg_gpio_iso; /**< GPIO power domain pad input isolation register. */
    volatile uint32_t reg_cam_iso; /**< CAM power domain pad input isolation register. */
    volatile uint32_t reg_lvds_iso; /**< LVDS power domain pad input isolation register. */
} soc_ctrl_t;


/* ----------------------------------------------------------------------------
   -- SOC_CTRL Register Bitfield Access --
   ---------------------------------------------------------------------------- */

/*! @name INFO */
/* Number of clusters */
#define SOC_CTRL_INFO_NB_CL_MASK                                     (0xffff)
#define SOC_CTRL_INFO_NB_CL_SHIFT                                    (0)
#define SOC_CTRL_INFO_NB_CL(val)                                     (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_INFO_NB_CL_SHIFT)) & SOC_CTRL_INFO_NB_CL_MASK)

/* Number of cores */
#define SOC_CTRL_INFO_NB_CORES_MASK                                  (0xffff0000)
#define SOC_CTRL_INFO_NB_CORES_SHIFT                                 (16)
#define SOC_CTRL_INFO_NB_CORES(val)                                  (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_INFO_NB_CORES_SHIFT)) & SOC_CTRL_INFO_NB_CORES_MASK)


/*! @name CL_ISOLATE */
/* Isolate cluster. Inhibits AXI transactions from cluster to SoC:
  - 1'b0:  Disable
  - 1'b1: Enable */
#define SOC_CTRL_CL_ISOLATE_EN_MASK                                  (0x1)
#define SOC_CTRL_CL_ISOLATE_EN_SHIFT                                 (0)
#define SOC_CTRL_CL_ISOLATE_EN(val)                                  (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_ISOLATE_EN_SHIFT)) & SOC_CTRL_CL_ISOLATE_EN_MASK)


/*! @name CL_BUSY */
/* Cluster busy flag (i.e. It's 1 if there is at least 1 active block in the cluster) */
#define SOC_CTRL_CL_BUSY_BUSY_MASK                                   (0x1)
#define SOC_CTRL_CL_BUSY_BUSY_SHIFT                                  (0)
#define SOC_CTRL_CL_BUSY_BUSY(val)                                   (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BUSY_BUSY_SHIFT)) & SOC_CTRL_CL_BUSY_BUSY_MASK)


/*! @name CL_BYPASS */
/* Bypass Maestro PMU controller configuration bitfield:
  - 1’b0: disabled
  - 1’b1: enabled */
#define SOC_CTRL_CL_BYPASS_BYP_POW_MASK                              (0x1)
#define SOC_CTRL_CL_BYPASS_BYP_POW_SHIFT                             (0)
#define SOC_CTRL_CL_BYPASS_BYP_POW(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_BYP_POW_SHIFT)) & SOC_CTRL_CL_BYPASS_BYP_POW_MASK)

/* Bypass Maestro PMU configuration selection configuration bitfield:
  - 1’b0: use default
  - 1’b1: use user configuration (bitfields from bits 3 to 15 of CL_BYPASS register) */
#define SOC_CTRL_CL_BYPASS_BYP_CFG_MASK                              (0x2)
#define SOC_CTRL_CL_BYPASS_BYP_CFG_SHIFT                             (1)
#define SOC_CTRL_CL_BYPASS_BYP_CFG(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_BYP_CFG_SHIFT)) & SOC_CTRL_CL_BYPASS_BYP_CFG_MASK)

/* Cluster state configuration and status bitfield:
  - 1’b0: off
  - 1’b1: on
  Status information is correct only when bypass mode is enabled. */
#define SOC_CTRL_CL_BYPASS_CL_STATE_MASK                             (0x8)
#define SOC_CTRL_CL_BYPASS_CL_STATE_SHIFT                            (3)
#define SOC_CTRL_CL_BYPASS_CL_STATE(val)                             (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_CL_STATE_SHIFT)) & SOC_CTRL_CL_BYPASS_CL_STATE_MASK)

/* Max current allowed on cluster TRC configuration bitfield. */
#define SOC_CTRL_CL_BYPASS_CURRSET_MASK                              (0x70)
#define SOC_CTRL_CL_BYPASS_CURRSET_SHIFT                             (4)
#define SOC_CTRL_CL_BYPASS_CURRSET(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_CURRSET_SHIFT)) & SOC_CTRL_CL_BYPASS_CURRSET_MASK)

/* Number of REFCLK 32kHz after cluster power ok has arised to release TR isolation configuration bitfield. */
#define SOC_CTRL_CL_BYPASS_PROG_DEL_MASK                             (0x180)
#define SOC_CTRL_CL_BYPASS_PROG_DEL_SHIFT                            (7)
#define SOC_CTRL_CL_BYPASS_PROG_DEL(val)                             (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_PROG_DEL_SHIFT)) & SOC_CTRL_CL_BYPASS_PROG_DEL_MASK)

/* Bypass cluster clock and reset control by Maestro PMU configuration bitfield:
  - 1’b0: disabled
  - 1’b1: enabled */
#define SOC_CTRL_CL_BYPASS_BYP_CLK_MASK                              (0x200)
#define SOC_CTRL_CL_BYPASS_BYP_CLK_SHIFT                             (9)
#define SOC_CTRL_CL_BYPASS_BYP_CLK(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_BYP_CLK_SHIFT)) & SOC_CTRL_CL_BYPASS_BYP_CLK_MASK)

/* Cluster clock gate configuration bitfield:
  - 1’b0: disabled
  - 1’b1: enabled
  It should always be used before switching cluster FLL to shutdown or retentive mode. */
#define SOC_CTRL_CL_BYPASS_CG_MASK                                   (0x400)
#define SOC_CTRL_CL_BYPASS_CG_SHIFT                                  (10)
#define SOC_CTRL_CL_BYPASS_CG(val)                                   (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_CG_SHIFT)) & SOC_CTRL_CL_BYPASS_CG_MASK)
#define READ_SOC_CTRL_CL_BYPASS_CG(val)                              (((uint32_t)(((uint32_t)(val)) & SOC_CTRL_CL_BYPASS_CG_MASK)) >> SOC_CTRL_CL_BYPASS_CG_SHIFT)

/* Cluster FLL shutdown configuration bitfield:
  - 1’b0: FLL on
  - 1’b1: FLL shutdown mode */
#define SOC_CTRL_CL_BYPASS_FLL_PWD_MASK                              (0x800)
#define SOC_CTRL_CL_BYPASS_FLL_PWD_SHIFT                             (11)
#define SOC_CTRL_CL_BYPASS_FLL_PWD(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_FLL_PWD_SHIFT)) & SOC_CTRL_CL_BYPASS_FLL_PWD_MASK)

/* Cluster FLL retentive configuration bitfield:
  - 1’b0: FLL on
  - 1’b1: FLL retentive mode */
#define SOC_CTRL_CL_BYPASS_FLL_RET_MASK                              (0x1000)
#define SOC_CTRL_CL_BYPASS_FLL_RET_SHIFT                             (12)
#define SOC_CTRL_CL_BYPASS_FLL_RET(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_FLL_RET_SHIFT)) & SOC_CTRL_CL_BYPASS_FLL_RET_MASK)

/* Cluster reset configuration bitfield:
  - 1’b0: nothing
  - 1’b1: reset the cluster */
#define SOC_CTRL_CL_BYPASS_RST_MASK                                  (0x2000)
#define SOC_CTRL_CL_BYPASS_RST_SHIFT                                 (13)
#define SOC_CTRL_CL_BYPASS_RST(val)                                  (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_RST_SHIFT)) & SOC_CTRL_CL_BYPASS_RST_MASK)

/* ? */
#define SOC_CTRL_CL_BYPASS_BYP_ISO_MASK                              (0x4000)
#define SOC_CTRL_CL_BYPASS_BYP_ISO_SHIFT                             (14)
#define SOC_CTRL_CL_BYPASS_BYP_ISO(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_BYP_ISO_SHIFT)) & SOC_CTRL_CL_BYPASS_BYP_ISO_MASK)

/* ? */
#define SOC_CTRL_CL_BYPASS_PWISO_MASK                                (0x8000)
#define SOC_CTRL_CL_BYPASS_PWISO_SHIFT                               (15)
#define SOC_CTRL_CL_BYPASS_PWISO(val)                                (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_PWISO_SHIFT)) & SOC_CTRL_CL_BYPASS_PWISO_MASK)
#define READ_SOC_CTRL_CL_BYPASS_PWISO(val)                           (((uint32_t)(((uint32_t)(val)) & SOC_CTRL_CL_BYPASS_PWISO_MASK)) >> SOC_CTRL_CL_BYPASS_PWISO_SHIFT)

/* Cluster power ok from cluster TRC status bitfield */
#define SOC_CTRL_CL_BYPASS_TRCPOWOK_MASK                             (0x10000)
#define SOC_CTRL_CL_BYPASS_TRCPOWOK_SHIFT                            (16)
#define SOC_CTRL_CL_BYPASS_TRCPOWOK(val)                             (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_TRCPOWOK_SHIFT)) & SOC_CTRL_CL_BYPASS_TRCPOWOK_MASK)

/* Cluster power down from Maestro PMU status bitfield. */
#define SOC_CTRL_CL_BYPASS_PMUPOWDOWN_MASK                           (0x20000)
#define SOC_CTRL_CL_BYPASS_PMUPOWDOWN_SHIFT                          (17)
#define SOC_CTRL_CL_BYPASS_PMUPOWDOWN(val)                           (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CL_BYPASS_PMUPOWDOWN_SHIFT)) & SOC_CTRL_CL_BYPASS_PMUPOWDOWN_MASK)


/*! @name JTAGREG */
/* JTAG internal register used for synchronisation from external debugger */
#define SOC_CTRL_JTAGREG_INT_SYNC_MASK                               (0x1)
#define SOC_CTRL_JTAGREG_INT_SYNC_SHIFT                              (0)
#define SOC_CTRL_JTAGREG_INT_SYNC(val)                               (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_JTAGREG_INT_SYNC_SHIFT)) & SOC_CTRL_JTAGREG_INT_SYNC_MASK)
#define READ_SOC_CTRL_JTAGREG_INT_SYNC(val)                          (((uint32_t)(((uint32_t)(val)) & SOC_CTRL_JTAGREG_INT_SYNC_MASK)) >> SOC_CTRL_JTAGREG_INT_SYNC_SHIFT)

/* JTAG internal register used for selecting boot mode configuration from external debugger */
#define SOC_CTRL_JTAGREG_INT_BT_MD_MASK                              (0xe)
#define SOC_CTRL_JTAGREG_INT_BT_MD_SHIFT                             (1)
#define SOC_CTRL_JTAGREG_INT_BT_MD(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_JTAGREG_INT_BT_MD_SHIFT)) & SOC_CTRL_JTAGREG_INT_BT_MD_MASK)
#define READ_SOC_CTRL_JTAGREG_INT_BT_MD(val)                         (((uint32_t)(((uint32_t)(val)) & SOC_CTRL_JTAGREG_INT_BT_MD_MASK)) >> SOC_CTRL_JTAGREG_INT_BT_MD_SHIFT)

/* JTAG external register used for synchronisation from external debugger */
#define SOC_CTRL_JTAGREG_EXT_SYNC_MASK                               (0x100)
#define SOC_CTRL_JTAGREG_EXT_SYNC_SHIFT                              (8)
#define SOC_CTRL_JTAGREG_EXT_SYNC(val)                               (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_JTAGREG_EXT_SYNC_SHIFT)) & SOC_CTRL_JTAGREG_EXT_SYNC_MASK)
#define READ_SOC_CTRL_JTAGREG_EXT_SYNC(val)                          (((uint32_t)(((uint32_t)(val)) & SOC_CTRL_JTAGREG_EXT_SYNC_MASK)) >> SOC_CTRL_JTAGREG_EXT_SYNC_SHIFT)

/* JTAG external register used for selecting boot mode configuration from external debugger */
#define SOC_CTRL_JTAGREG_EXT_BT_MD_MASK                              (0xe00)
#define SOC_CTRL_JTAGREG_EXT_BT_MD_SHIFT                             (9)
#define SOC_CTRL_JTAGREG_EXT_BT_MD(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_JTAGREG_EXT_BT_MD_SHIFT)) & SOC_CTRL_JTAGREG_EXT_BT_MD_MASK)
#define READ_SOC_CTRL_JTAGREG_EXT_BT_MD(val)                         (((uint32_t)(((uint32_t)(val)) & SOC_CTRL_JTAGREG_EXT_BT_MD_MASK)) >> SOC_CTRL_JTAGREG_EXT_BT_MD_SHIFT)


/*! @name L2_SLEEP */
/* L2 memory sleep configuration */
#define SOC_CTRL_L2_SLEEP_L2_SLEEP_MASK                              (0x1)
#define SOC_CTRL_L2_SLEEP_L2_SLEEP_SHIFT                             (0)
#define SOC_CTRL_L2_SLEEP_L2_SLEEP(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_L2_SLEEP_L2_SLEEP_SHIFT)) & SOC_CTRL_L2_SLEEP_L2_SLEEP_MASK)


/*! @name SLEEP_CTRL */
/* Alias for SAFE_PMU_SLEEPCTRL(i.e. will be accessible in 1 clock cycle) */
#define SOC_CTRL_SLEEP_CTRL_SLEEP_CTRL_MASK                          (0xffffffff)
#define SOC_CTRL_SLEEP_CTRL_SLEEP_CTRL_SHIFT                         (0)
#define SOC_CTRL_SLEEP_CTRL_SLEEP_CTRL(val)                          (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SLEEP_CTRL_SLEEP_CTRL_SHIFT)) & SOC_CTRL_SLEEP_CTRL_SLEEP_CTRL_MASK)


/*! @name CORESTATUS */
/* EOC and chip status register */
#define SOC_CTRL_CORESTATUS_STATUS_MASK                              (0xffffffff)
#define SOC_CTRL_CORESTATUS_STATUS_SHIFT                             (0)
#define SOC_CTRL_CORESTATUS_STATUS(val)                              (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CORESTATUS_STATUS_SHIFT)) & SOC_CTRL_CORESTATUS_STATUS_MASK)


/*! @name CORESTATUS_RO */
/* EOC and chip status register */
#define SOC_CTRL_CORESTATUS_RO_STATUS_MASK                           (0xffffffff)
#define SOC_CTRL_CORESTATUS_RO_STATUS_SHIFT                          (0)
#define SOC_CTRL_CORESTATUS_RO_STATUS(val)                           (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_CORESTATUS_RO_STATUS_SHIFT)) & SOC_CTRL_CORESTATUS_RO_STATUS_MASK)


/*! @name SAFE_PMU_RAR */
/* DC/DC Nominal Voltage setting */
#define SOC_CTRL_SAFE_PMU_RAR_NV_VOLT_MASK                           (0x1f)
#define SOC_CTRL_SAFE_PMU_RAR_NV_VOLT_SHIFT                          (0)
#define SOC_CTRL_SAFE_PMU_RAR_NV_VOLT(val)                           (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_RAR_NV_VOLT_SHIFT)) & SOC_CTRL_SAFE_PMU_RAR_NV_VOLT_MASK)

/* DC/DC Medium Voltage setting (not used) */
#define SOC_CTRL_SAFE_PMU_RAR_MV_VOLT_MASK                           (0x1f00)
#define SOC_CTRL_SAFE_PMU_RAR_MV_VOLT_SHIFT                          (8)
#define SOC_CTRL_SAFE_PMU_RAR_MV_VOLT(val)                           (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_RAR_MV_VOLT_SHIFT)) & SOC_CTRL_SAFE_PMU_RAR_MV_VOLT_MASK)

/* DC/DC Low Voltage setting */
#define SOC_CTRL_SAFE_PMU_RAR_LV_VOLT_MASK                           (0x1f0000)
#define SOC_CTRL_SAFE_PMU_RAR_LV_VOLT_SHIFT                          (16)
#define SOC_CTRL_SAFE_PMU_RAR_LV_VOLT(val)                           (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_RAR_LV_VOLT_SHIFT)) & SOC_CTRL_SAFE_PMU_RAR_LV_VOLT_MASK)

/* DC/DC Retentive Voltage setting */
#define SOC_CTRL_SAFE_PMU_RAR_RV_VOLT_MASK                           (0x1f000000)
#define SOC_CTRL_SAFE_PMU_RAR_RV_VOLT_SHIFT                          (24)
#define SOC_CTRL_SAFE_PMU_RAR_RV_VOLT(val)                           (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_RAR_RV_VOLT_SHIFT)) & SOC_CTRL_SAFE_PMU_RAR_RV_VOLT_MASK)


/*! @name SAFE_PMU_SLEEPCTRL */
/* Configure retention mode for region 0 of L2 memory:
  - 1'b0: Non retentive
  - 1'b1: Retentive */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R0_MASK                       (0x1)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R0_SHIFT                      (0)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R0(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R0_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R0_MASK)

/* Configure retention mode for region 1 of L2 memory:
  - 1'b0: Non retentive
  - 1'b1: Retentive */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R1_MASK                       (0x2)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R1_SHIFT                      (1)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R1(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R1_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R1_MASK)

/* Configure retention mode for region 2 of L2 memory:
  - 1'b0: Non retentive
  - 1'b1: Retentive */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R2_MASK                       (0x4)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R2_SHIFT                      (2)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R2(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R2_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R2_MASK)

/* Configure retention mode for region 3 of L2 memory:
  - 1'b0: Non retentive
  - 1'b1: Retentive */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R3_MASK                       (0x8)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R3_SHIFT                      (3)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R3(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R3_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_L2_R3_MASK)

/* Configure retention mode for SoC FLL:
  - 1'b0: Non retentive
  - 1'b1: Retentive */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_SOC_FLL_MASK                     (0x10)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_SOC_FLL_SHIFT                    (4)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_SOC_FLL(val)                     (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_SOC_FLL_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_SOC_FLL_MASK)

/* Configure retention mode for cluster FLL:
  - 1'b0: Non retentive
  - 1'b1: Retentive */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_FLL_MASK                      (0x20)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_FLL_SHIFT                     (5)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_FLL(val)                      (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_FLL_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_FLL_MASK)

/* Select external wake-up source (GPIO ID):
  - 5'b00000: GPIO 0
  - 5'b00001: GPIO 1
  - 5'b00010: GPIO 2
  - 5'b00011: GPIO 3
  - 5'b00100: GPIO 4
  - 5'b00101: GPIO 5
  - 5'b00110: GPIO 6
  - 5'b00111: GPIO 7
  - 5'b01000: GPIO 8
  - 5'b01001: GPIO 9
  - 5'b01010: GPIO 10
  - 5'b01011: GPIO 11
  - 5'b01100: GPIO 12
  - 5'b01101: GPIO 13
  - 5'b01110: GPIO 14
  - 5'b01111: GPIO 15
  - 5'b10000: GPIO 16
  - 5'b10001: GPIO 17
  - 5'b10010: GPIO 18
  - 5'b10011: GPIO 19
  - 5'b10100: GPIO 20
  - 5'b10101: GPIO 21
  - 5'b10110: GPIO 22
  - 5'b10111: GPIO 23
  - 5'b11000: GPIO 24
  - 5'b11001: GPIO 25
  - 5'b11010: GPIO 26
  - 5'b11011: GPIO 27
  - 5'b11100: GPIO 28
  - 5'b11101: GPIO 29
  - 5'b11110: GPIO 30
  - 5'b11111: GPIO 31 */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_SRC_MASK                 (0x7c0)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_SRC_SHIFT                (6)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_SRC(val)                 (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_SRC_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_SRC_MASK)

/* Select external wake-up  mode:
  - 2'b00: rise event
  - 2'b01: fall event
  - 2'b10: high level
  - 2'b11: low level */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_TYPE_MASK                (0x1800)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_TYPE_SHIFT               (11)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_TYPE(val)                (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_TYPE_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_TYPE_MASK)

/* Enable external wake-up;
  - 1'b0; external wake-up disabled
  - 1'b1: external wake-up enabled */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_EN_MASK                  (0x2000)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_EN_SHIFT                 (13)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_EN(val)                  (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_EN_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTWAKE_EN_MASK)

/* Power state to restore after warm boot
  - 1'b0: SoC_LV
  - 1'b1: SoC_HV */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_WAKESTATE_MASK                   (0x4000)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_WAKESTATE_SHIFT                  (14)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_WAKESTATE(val)                   (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_WAKESTATE_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_WAKESTATE_MASK)

/* Warm bootmode:
  - 1'b0: Boot from ROM
  - 1'b1: Boot from L2 */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTDEV_MASK                       (0x10000)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTDEV_SHIFT                      (16)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTDEV(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTDEV_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTDEV_MASK)

/* External wake-up interrupt status (automatically resetted after read)
  - 1'b0: wake-up triggered by RTC
  - 1'b1: wake-up triggered by external event */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTINT_MASK                      (0x20000)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTINT_SHIFT                     (17)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTINT(val)                      (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTINT_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_EXTINT_MASK)

/* Select boot type:
  - 2'b00: cold boot
  - 2'b01: deep sleep
  - 2'b10: retentive deep sleep */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTTYPE_MASK                      (0xc0000)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTTYPE_SHIFT                     (18)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTTYPE(val)                      (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTTYPE_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_BTTYPE_MASK)

/* Cluster state to restore after warm boot:
  - 1’b0: off
  - 1’b1: on */
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_WAKE_MASK                     (0x100000)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_WAKE_SHIFT                    (20)
#define SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_WAKE(val)                     (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_WAKE_SHIFT)) & SOC_CTRL_SAFE_PMU_SLEEPCTRL_CL_WAKE_MASK)


/*! @name SAFE_PMU_FORCE */
/* Force retentive state on region 0 of L2 memory:
  1'b0: not state retentive
  1'b1: state retentive */
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R0_MASK                       (0x1)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R0_SHIFT                      (0)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R0(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R0_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R0_MASK)

/* Force retentive state on region 1 of L2 memory:
  1'b0: not state retentive
  1'b1: state retentive */
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R1_MASK                       (0x2)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R1_SHIFT                      (1)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R1(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R1_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R1_MASK)

/* Force retentive state on region 2 of L2 memory:
  1'b0: not state retentive
  1'b1: state retentive */
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R2_MASK                       (0x4)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R2_SHIFT                      (2)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R2(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R2_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R2_MASK)

/* Force retentive state on region 3 of L2 memory:
  1'b0: not state retentive
  1'b1: state retentive */
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R3_MASK                       (0x8)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R3_SHIFT                      (3)
#define SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R3(val)                       (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R3_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_RET_L2_R3_MASK)

/* Force power down on region 0 of L2 memory:
  1'b0: power up
  1'b1: power down */
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R0_MASK                        (0x10)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R0_SHIFT                       (4)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R0(val)                        (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R0_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R0_MASK)

/* Force power down on region 1 of L2 memory:
  1'b0: power up
  1'b1: power down */
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R1_MASK                        (0x20)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R1_SHIFT                       (5)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R1(val)                        (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R1_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R1_MASK)

/* Force power down on region 2 of L2 memory:
  1'b0: power up
  1'b1: power down */
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R2_MASK                        (0x40)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R2_SHIFT                       (6)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R2(val)                        (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R2_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R2_MASK)

/* Force power down on region 3 of L2 memory:
  1'b0: power up
  1'b1: power down */
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R3_MASK                        (0x80)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R3_SHIFT                       (7)
#define SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R3(val)                        (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R3_SHIFT)) & SOC_CTRL_SAFE_PMU_FORCE_PD_L2_R3_MASK)


/*! @name SAFE_PADFUN */
/* Configure pad's functionnality :
  2'b00: Alternate 0, default.
  2'b01: Alternate 1, GPIO.
  2'b10: Alternate 2.
  2'b11: Alternate 3. */
/* Shift by 2 to the left the position to get to right pad config. */
#define SOC_CTRL_SAFE_PADFUN_FUNC_MASK                               (0xffffffff)
#define SOC_CTRL_SAFE_PADFUN_FUNC_SHIFT                              (0)
#define SOC_CTRL_SAFE_PADFUN_FUNC(val)                               (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PADFUN_FUNC_SHIFT)) & SOC_CTRL_SAFE_PADFUN_FUNC_MASK)


/*! @name SAFE_SLEEPPADCFG */
/* Configure pad's sleep state & direction.
  Pos & 0x1 = State:
  1'b0: input or output low.
  1'b1: input or output high.
  Pos & 0x0 = Direction:
  1'b0: input.
  1'b1: output. */
#define SOC_CTRL_SAFE_SLEEPPADCFG_DIR_MASK                           (0x1)
#define SOC_CTRL_SAFE_SLEEPPADCFG_DIR_SHIFT                          (0)
#define SOC_CTRL_SAFE_SLEEPPADCFG_DIR(val)                           (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_SLEEPPADCFG_DIR_SHIFT)) & SOC_CTRL_SAFE_SLEEPPADCFG_DIR_MASK)

#define SOC_CTRL_SAFE_SLEEPPADCFG_STATE_MASK                         (0x2)
#define SOC_CTRL_SAFE_SLEEPPADCFG_STATE_SHIFT                        (1)
#define SOC_CTRL_SAFE_SLEEPPADCFG_STATE(val)                         (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_SLEEPPADCFG_STATE_SHIFT)) & SOC_CTRL_SAFE_SLEEPPADCFG_STATE_MASK)


/*! @name SAFE_PADSLEEP */
/* Enable pad sleep mode:
  1'b0: disable
  1'b1: enable */
#define SOC_CTRL_SAFE_PADSLEEP_EN_MASK                               (0x1)
#define SOC_CTRL_SAFE_PADSLEEP_EN_SHIFT                              (0)
#define SOC_CTRL_SAFE_PADSLEEP_EN(val)                               (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PADSLEEP_EN_SHIFT)) & SOC_CTRL_SAFE_PADSLEEP_EN_MASK)


/*! @name SAFE_PADCFG */
/* Set pull activation.
  1'b0: pull disabled.
  1'b1: pull enabled. */
#define SOC_CTRL_SAFE_PADCFG_PULL_EN_MASK                            (0x1)
#define SOC_CTRL_SAFE_PADCFG_PULL_EN_SHIFT                           (0)
#define SOC_CTRL_SAFE_PADCFG_PULL_EN(val)                            (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PADCFG_PULL_EN_SHIFT)) & SOC_CTRL_SAFE_PADCFG_PULL_EN_MASK)

/* Set drive strength.
  1'b0: low drive strength.
  1'b1: high drive strength. */
#define SOC_CTRL_SAFE_PADCFG_DRIVE_STRENGTH_MASK                     (0x2)
#define SOC_CTRL_SAFE_PADCFG_DRIVE_STRENGTH_SHIFT                    (1)
#define SOC_CTRL_SAFE_PADCFG_DRIVE_STRENGTH(val)                     (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_SAFE_PADCFG_DRIVE_STRENGTH_SHIFT)) & SOC_CTRL_SAFE_PADCFG_DRIVE_STRENGTH_MASK)


/*! @name REG_GPIO_ISO */
/* Configuration of GPIO domain pads isolation:
  - 1'b0: not isolated
  - 1'b1: isolated */
#define SOC_CTRL_REG_GPIO_ISO_ISO_MASK                               (0x1)
#define SOC_CTRL_REG_GPIO_ISO_ISO_SHIFT                              (0)
#define SOC_CTRL_REG_GPIO_ISO_ISO(val)                               (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_REG_GPIO_ISO_ISO_SHIFT)) & SOC_CTRL_REG_GPIO_ISO_ISO_MASK)


/*! @name REG_CAM_ISO */
/* Configuration of CAM domain pads isolation:
  - 1'b0: not isolated
  - 1'b1: isolated */
#define SOC_CTRL_REG_CAM_ISO_ISO_MASK                                (0x1)
#define SOC_CTRL_REG_CAM_ISO_ISO_SHIFT                               (0)
#define SOC_CTRL_REG_CAM_ISO_ISO(val)                                (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_REG_CAM_ISO_ISO_SHIFT)) & SOC_CTRL_REG_CAM_ISO_ISO_MASK)


/*! @name REG_LVDS_ISO */
/* Configuration of LVDS domain pads isolation:
  - 1'b0: not isolated
  - 1'b1: isolated */
#define SOC_CTRL_REG_LVDS_ISO_ISO_MASK                               (0x1)
#define SOC_CTRL_REG_LVDS_ISO_ISO_SHIFT                              (0)
#define SOC_CTRL_REG_LVDS_ISO_ISO(val)                               (((uint32_t)(((uint32_t)(val)) << SOC_CTRL_REG_LVDS_ISO_ISO_SHIFT)) & SOC_CTRL_REG_LVDS_ISO_ISO_MASK)


/*! @name INFO */
typedef union
{
    struct
    {
        /* Number of clusters */
        uint32_t nb_cl:16;
        /* Number of cores */
        uint32_t nb_cores:16;
    } field;
    uint32_t word;
} soc_ctrl_info_t;

/*! @name NOTUSED0 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_notused0_t;

/*! @name NOTUSED1 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_notused1_t;

/*! @name CL_ISOLATE */
typedef union
{
    struct
    {
        /* Isolate cluster. Inhibits AXI transactions from cluster to SoC:
        - 1'b0:  Disable
        - 1'b1: Enable */
        uint32_t en:1;
    } field;
    uint32_t word;
} soc_ctrl_cl_isolate_t;

/*! @name CL_BUSY */
typedef union
{
    struct
    {
        /* Cluster busy flag (i.e. It's 1 if there is at least 1 active block in the cluster) */
        uint32_t busy:1;
    } field;
    uint32_t word;
} soc_ctrl_cl_busy_t;

/*! @name CL_BYPASS */
typedef union
{
    struct
    {
        /* Bypass Maestro PMU controller configuration bitfield:
        - 1’b0: disabled
        - 1’b1: enabled */
        uint32_t byp_pow:1;
        /* Bypass Maestro PMU configuration selection configuration bitfield:
        - 1’b0: use default
        - 1’b1: use user configuration (bitfields from bits 3 to 15 of CL_BYPASS register) */
        uint32_t byp_cfg:1;
        uint32_t reserved_0:1;
        /* Cluster state configuration and status bitfield:
        - 1’b0: off
        - 1’b1: on
        Status information is correct only when bypass mode is enabled. */
        uint32_t cl_state:1;
        /* Max current allowed on cluster TRC configuration bitfield. */
        uint32_t currset:3;
        /* Number of REFCLK 32kHz after cluster power ok has arised to release TR isolation configuration bitfield. */
        uint32_t prog_del:2;
        /* Bypass cluster clock and reset control by Maestro PMU configuration bitfield:
        - 1’b0: disabled
        - 1’b1: enabled */
        uint32_t byp_clk:1;
        /* Cluster clock gate configuration bitfield:
        - 1’b0: disabled
        - 1’b1: enabled
        It should always be used before switching cluster FLL to shutdown or retentive mode. */
        uint32_t cg:1;
        /* Cluster FLL shutdown configuration bitfield:
        - 1’b0: FLL on
        - 1’b1: FLL shutdown mode */
        uint32_t fll_pwd:1;
        /* Cluster FLL retentive configuration bitfield:
        - 1’b0: FLL on
        - 1’b1: FLL retentive mode */
        uint32_t fll_ret:1;
        /* Cluster reset configuration bitfield:
        - 1’b0: nothing
        - 1’b1: reset the cluster */
        uint32_t rst:1;
        /* ? */
        uint32_t byp_iso:1;
        /* ? */
        uint32_t pwiso:1;
        /* Cluster power ok from cluster TRC status bitfield */
        uint32_t trcpowok:1;
        /* Cluster power down from Maestro PMU status bitfield. */
        uint32_t pmupowdown:1;
    } field;
    uint32_t word;
} soc_ctrl_cl_bypass_t;

/*! @name JTAGREG */
typedef union
{
    struct
    {
        /* JTAG internal register used for synchronisation from external debugger */
        uint32_t int_sync:1;
        /* JTAG internal register used for selecting boot mode configuration from external debugger */
        uint32_t int_bt_md:3;
        uint32_t reserved_0:4;
        /* JTAG external register used for synchronisation from external debugger */
        uint32_t ext_sync:1;
        /* JTAG external register used for selecting boot mode configuration from external debugger */
        uint32_t ext_bt_md:3;
    } field;
    uint32_t word;
} soc_ctrl_jtagreg_t;

/*! @name L2_SLEEP */
typedef union
{
    struct
    {
        /* L2 memory sleep configuration */
        uint32_t l2_sleep:1;
    } field;
    uint32_t word;
} soc_ctrl_l2_sleep_t;

/*! @name SLEEP_CTRL */
typedef union
{
    struct
    {
        /* Alias for SAFE_PMU_SLEEPCTRL(i.e. will be accessible in 1 clock cycle) */
        uint32_t sleep_ctrl:32;
    } field;
    uint32_t word;
} soc_ctrl_sleep_ctrl_t;

/*! @name CORESTATUS */
typedef union
{
    struct
    {
        /* EOC and chip status register */
        uint32_t status:32;
    } field;
    uint32_t word;
} soc_ctrl_corestatus_t;

/*! @name CORESTATUS_RO */
typedef union
{
    struct
    {
        /* EOC and chip status register */
        uint32_t status:32;
    } field;
    uint32_t word;
} soc_ctrl_corestatus_ro_t;

/*! @name SAFE_PMU_RAR */
typedef union
{
    struct
    {
        /* DC/DC Nominal Voltage setting */
        uint32_t nv_volt:5;
        uint32_t reserved_0:3;
        /* DC/DC Medium Voltage setting (not used) */
        uint32_t mv_volt:5;
        uint32_t reserved_1:3;
        /* DC/DC Low Voltage setting */
        uint32_t lv_volt:5;
        uint32_t reserved_2:3;
        /* DC/DC Retentive Voltage setting */
        uint32_t rv_volt:5;
    } field;
    uint32_t word;
} soc_ctrl_safe_pmu_rar_t;

/*! @name SAFE_PMU_SLEEPCTRL */
typedef union
{
    struct
    {
        /* Configure retention mode for region 0 of L2 memory:
        - 1'b0: Non retentive
        - 1'b1: Retentive */
        uint32_t l2_r0:1;
        /* Configure retention mode for region 1 of L2 memory:
        - 1'b0: Non retentive
        - 1'b1: Retentive */
        uint32_t l2_r1:1;
        /* Configure retention mode for region 2 of L2 memory:
        - 1'b0: Non retentive
        - 1'b1: Retentive */
        uint32_t l2_r2:1;
        /* Configure retention mode for region 3 of L2 memory:
        - 1'b0: Non retentive
        - 1'b1: Retentive */
        uint32_t l2_r3:1;
        /* Configure retention mode for SoC FLL:
        - 1'b0: Non retentive
        - 1'b1: Retentive */
        uint32_t soc_fll:1;
        /* Configure retention mode for cluster FLL:
        - 1'b0: Non retentive
        - 1'b1: Retentive */
        uint32_t cl_fll:1;
        /* Select external wake-up source (GPIO ID):
        - 5'b00000: GPIO 0
        - 5'b00001: GPIO 1
        - 5'b00010: GPIO 2
        - 5'b00011: GPIO 3
        - 5'b00100: GPIO 4
        - 5'b00101: GPIO 5
        - 5'b00110: GPIO 6
        - 5'b00111: GPIO 7
        - 5'b01000: GPIO 8
        - 5'b01001: GPIO 9
        - 5'b01010: GPIO 10
        - 5'b01011: GPIO 11
        - 5'b01100: GPIO 12
        - 5'b01101: GPIO 13
        - 5'b01110: GPIO 14
        - 5'b01111: GPIO 15
        - 5'b10000: GPIO 16
        - 5'b10001: GPIO 17
        - 5'b10010: GPIO 18
        - 5'b10011: GPIO 19
        - 5'b10100: GPIO 20
        - 5'b10101: GPIO 21
        - 5'b10110: GPIO 22
        - 5'b10111: GPIO 23
        - 5'b11000: GPIO 24
        - 5'b11001: GPIO 25
        - 5'b11010: GPIO 26
        - 5'b11011: GPIO 27
        - 5'b11100: GPIO 28
        - 5'b11101: GPIO 29
        - 5'b11110: GPIO 30
        - 5'b11111: GPIO 31 */
        uint32_t extwake_src:5;
        /* Select external wake-up  mode:
        - 2'b00: rise event
        - 2'b01: fall event
        - 2'b10: high level
        - 2'b11: low level */
        uint32_t extwake_type:2;
        /* Enable external wake-up;
        - 1'b0; external wake-up disabled
        - 1'b1: external wake-up enabled */
        uint32_t extwake_en:1;
        uint32_t reserved_0:1;
        /* - */
        uint32_t wakestate:1;
        /* Warm bootmode:
        - 1'b0: Boot from ROM
        - 1'b1: Boot from L2 */
        uint32_t btdev:1;
        /* External wake-up interrupt status (automatically resetted after read)
        - 1'b0: wake-up triggered by RTC
        - 1'b1: wake-up triggered by external event */
        uint32_t extint:1;
        /* Select boot type:
        - 2'b00: cold boot
        - 2'b01: deep sleep
        - 2'b10: retentive deep sleep */
        uint32_t bttype:2;
        /* Cluster state to restore after warm boot:
        - 1’b0: off
        - 1’b1: on */
        uint32_t cl_wake:1;
    } field;
    uint32_t word;
} soc_ctrl_safe_pmu_sleepctrl_t;

/*! @name SAFE_PMU_FORCE */
typedef union
{
    struct
    {
        /* Force retentive state on region 0 of L2 memory:
        1'b0: not state retentive
        1'b1: state retentive */
        uint32_t ret_l2_r0:1;
        /* Force retentive state on region 1 of L2 memory:
        1'b0: not state retentive
        1'b1: state retentive */
        uint32_t ret_l2_r1:1;
        /* Force retentive state on region 2 of L2 memory:
        1'b0: not state retentive
        1'b1: state retentive */
        uint32_t ret_l2_r2:1;
        /* Force retentive state on region 3 of L2 memory:
        1'b0: not state retentive
        1'b1: state retentive */
        uint32_t ret_l2_r3:1;
        /* Force power down on region 0 of L2 memory:
        1'b0: power up
        1'b1: power down */
        uint32_t pd_l2_r0:1;
        /* Force power down on region 1 of L2 memory:
        1'b0: power up
        1'b1: power down */
        uint32_t pd_l2_r1:1;
        /* Force power down on region 2 of L2 memory:
        1'b0: power up
        1'b1: power down */
        uint32_t pd_l2_r2:1;
        /* Force power down on region 3 of L2 memory:
        1'b0: power up
        1'b1: power down */
        uint32_t pd_l2_r3:1;
    } field;
    uint32_t word;
} soc_ctrl_safe_pmu_force_t;

/*! @name SAFE_PADFUN0 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padfun0_t;

/*! @name SAFE_PADFUN1 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padfun1_t;

/*! @name SAFE_PADFUN2 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padfun2_t;

/*! @name SAFE_PADFUN3 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padfun3_t;

/*! @name SAFE_SLEEPPADCFG0 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_sleeppadcfg0_t;

/*! @name SAFE_SLEEPPADCFG1 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_sleeppadcfg1_t;

/*! @name SAFE_SLEEPPADCFG2 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_sleeppadcfg2_t;

/*! @name SAFE_SLEEPPADCFG3 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_sleeppadcfg3_t;

/*! @name SAFE_PADSLEEP */
typedef union
{
    struct
    {
        /* Enable pad sleep mode:
        1'b0: disable
        1'b1: enable */
        uint32_t en:1;
    } field;
    uint32_t word;
} soc_ctrl_safe_padsleep_t;

/*! @name SAFE_PADCFG0 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg0_t;

/*! @name SAFE_PADCFG1 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg1_t;

/*! @name SAFE_PADCFG2 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg2_t;

/*! @name SAFE_PADCFG3 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg3_t;

/*! @name SAFE_PADCFG4 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg4_t;

/*! @name SAFE_PADCFG5 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg5_t;

/*! @name SAFE_PADCFG6 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg6_t;

/*! @name SAFE_PADCFG7 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg7_t;

/*! @name SAFE_PADCFG8 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg8_t;

/*! @name SAFE_PADCFG9 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg9_t;

/*! @name SAFE_PADCFG10 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg10_t;

/*! @name SAFE_PADCFG11 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg11_t;

/*! @name SAFE_PADCFG12 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg12_t;

/*! @name SAFE_PADCFG13 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg13_t;

/*! @name SAFE_PADCFG14 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg14_t;

/*! @name SAFE_PADCFG15 */
typedef union
{
    struct
    {
    } field;
    uint32_t word;
} soc_ctrl_safe_padcfg15_t;

/*! @name REG_GPIO_ISO */
typedef union
{
    struct
    {
        /* Configuration of GPIO domain pads isolation:
        - 1'b0: not isolated
        - 1'b1: isolated */
        uint32_t iso:1;
    } field;
    uint32_t word;
} soc_ctrl_reg_gpio_iso_t;

/*! @name REG_CAM_ISO */
typedef union
{
    struct
    {
        /* Configuration of CAM domain pads isolation:
        - 1'b0: not isolated
        - 1'b1: isolated */
        uint32_t iso:1;
    } field;
    uint32_t word;
} soc_ctrl_reg_cam_iso_t;

/*! @name REG_LVDS_ISO */
typedef union
{
    struct
    {
        /* Configuration of LVDS domain pads isolation:
        - 1'b0: not isolated
        - 1'b1: isolated */
        uint32_t iso:1;
    } field;
    uint32_t word;
} soc_ctrl_reg_lvds_iso_t;


#endif /* HAL_INCLUDE_HAL_SOC_CTRL_PERIPH_H_ */
