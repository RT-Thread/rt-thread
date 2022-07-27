#ifndef __BASE_ADDRESSES_H
#define __BASE_ADDRESSES_H

#if 33U == __CORTEX_M                  // NOLINT(readability-magic-numbers)

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripheralAddr
 * @{
 */

 #define R_ACMPHS0_BASE         0x400F4000
 #define R_ACMPHS1_BASE         0x400F4100
 #define R_ACMPHS2_BASE         0x400F4200
 #define R_ACMPHS3_BASE         0x400F4300
 #define R_MPU_BASE             0x40000000
 #define R_TZF_BASE             0x40000E00
 #define R_SRAM_BASE            0x40002000
 #define R_BUS_BASE             0x40003000
 #define R_DMAC0_BASE           0x40005000
 #define R_DMAC1_BASE           0x40005040
 #define R_DMAC2_BASE           0x40005080
 #define R_DMAC3_BASE           0x400050C0
 #define R_DMAC4_BASE           0x40005100
 #define R_DMAC5_BASE           0x40005140
 #define R_DMAC6_BASE           0x40005180
 #define R_DMAC7_BASE           0x400051C0
 #define R_DMA_BASE             0x40005200
 #define R_DTC_BASE             0x40005400
 #define R_ICU_BASE             0x40006000
 #define R_CACHE_BASE           0x40007000
 #define R_CPSCU_BASE           0x40008000
 #define R_DBG_BASE             0x4001B000
 #define R_FCACHE_BASE          0x4001C000
 #define R_SYSC_BASE            0x4001E000
 #define R_TSN_CAL_BASE         0x407FB17C
 #define R_TSN_CTRL_BASE        0x400F3000
 #define R_ELC_BASE             0x40082000
 #define R_TC_BASE              0x40083000
 #define R_IWDT_BASE            0x40083200
 #define R_WDT_BASE             0x40083400
 #define R_CAC_BASE             0x40083600
 #define R_MSTP_BASE            0x40084000
 #define R_KINT_BASE            0x40085000
 #define R_POEG_BASE            0x4008A000
 #define R_USB_FS0_BASE         0x40090000
 #define R_USB_HS0_BASE         0x40111000
 #define R_SDHI0_BASE           0x40092000
 #define R_SSI0_BASE            0x4009D000
 #define R_IIC0_BASE            0x4009F000
 #define R_IIC0WU_BASE          0x4009F014
 #define R_IIC1_BASE            0x4009F100
 #define R_OSPI_BASE            0x400A6000
 #define R_CAN0_BASE            0x400A8000
 #define R_CAN1_BASE            0x400A9000
 #define R_CEC_BASE             0x400AC000
 #define R_CANFD_BASE           0x400B0000
 #define R_CTSU_BASE            0x400D0000
 #define R_PSCU_BASE            0x400E0000
 #define R_AGT0_BASE            0x400E8000
 #define R_AGT1_BASE            0x400E8100
 #define R_AGT2_BASE            0x400E8200
 #define R_AGT3_BASE            0x400E8300
 #define R_AGT4_BASE            0x400E8400
 #define R_AGT5_BASE            0x400E8500
 #define R_AGTW0_BASE           0x400E8000
 #define R_AGTW1_BASE           0x400E8100
 #define R_TSN_CTRL_BASE        0x400F3000
 #define R_CRC_BASE             0x40108000
 #define R_DOC_BASE             0x40109000
 #define R_ETHERC_EDMAC_BASE    0x40114000
 #define R_ETHERC0_BASE         0x40114100
 #define R_SCI0_BASE            0x40118000
 #define R_SCI1_BASE            0x40118100
 #define R_SCI2_BASE            0x40118200
 #define R_SCI3_BASE            0x40118300
 #define R_SCI4_BASE            0x40118400
 #define R_SCI5_BASE            0x40118500
 #define R_SCI6_BASE            0x40118600
 #define R_SCI7_BASE            0x40118700
 #define R_SCI8_BASE            0x40118800
 #define R_SCI9_BASE            0x40118900
 #define R_SPI0_BASE            0x4011A000
 #define R_SPI1_BASE            0x4011A100
 #define R_SPI_B0_BASE          0x4011A000
 #define R_SPI_B1_BASE          0x4011A100
 #define R_GPT320_BASE          0x40169000
 #define R_GPT321_BASE          0x40169100
 #define R_GPT322_BASE          0x40169200
 #define R_GPT323_BASE          0x40169300
 #define R_GPT164_BASE          0x40169400
 #define R_GPT165_BASE          0x40169500
 #define R_GPT166_BASE          0x40169600
 #define R_GPT167_BASE          0x40169700
 #define R_GPT168_BASE          0x40169800
 #define R_GPT169_BASE          0x40169900
 #define R_GPT_OPS_BASE         0x40169A00
 #define R_GPT_ODC_BASE         0x4016A000
 #define R_GPT_GTCLK_BASE       0x40169B00
 #define R_ADC120_BASE          0x40170000
 #define R_ADC121_BASE          0x40170200

/* Not included in SVD */
 #if (BSP_FEATURE_DAC_MAX_CHANNELS > 2U)
  #define R_DAC120_BASE         0x40172000
  #define R_DAC121_BASE         0x40172100
 #else
  #define R_DAC12_BASE          0x40171000
 #endif
 #define R_FLAD_BASE            0x407FC000
 #define R_FACI_HP_CMD_BASE     0x407E0000
 #define R_FACI_HP_BASE         0x407FE000
 #define R_QSPI_BASE            0x64000000
 #define R_TFU_BASE             0x40021000

/* Not included in SVD */
 #if (2U == BSP_FEATURE_IOPORT_VERSION)
  #define R_PORT0_BASE          0x4001F000
  #define R_PORT1_BASE          0x4001F020
  #define R_PORT2_BASE          0x4001F040
  #define R_PORT10_BASE         0x4001F140
  #define R_PORT11_BASE         0x4001F160
  #define R_PORT12_BASE         0x4001F180
  #define R_PORT13_BASE         0x4001F1A0
  #define R_PORT14_BASE         0x4001F1C0
  #define R_PFS_BASE            0x4001F800
  #define R_PMISC_BASE          0x4001FD00
 #else
  #define R_PORT0_BASE          0x40080000
  #define R_PORT1_BASE          0x40080020
  #define R_PORT2_BASE          0x40080040
  #define R_PORT3_BASE          0x40080060
  #define R_PORT4_BASE          0x40080080
  #define R_PORT5_BASE          0x400800A0
  #define R_PORT6_BASE          0x400800C0
  #define R_PORT7_BASE          0x400800E0
  #define R_PORT8_BASE          0x40080100
  #define R_PORT9_BASE          0x40080120
  #define R_PORT10_BASE         0x40080140
  #define R_PORT11_BASE         0x40080160
  #define R_PFS_BASE            0x40080800
  #define R_PMISC_BASE          0x40080D00 // does not exist but FSP will not build without this
 #endif
 #define R_GPT_POEG0_BASE       0x4008A000
 #define R_GPT_POEG1_BASE       0x4008A100
 #define R_GPT_POEG2_BASE       0x4008A200
 #define R_GPT_POEG3_BASE       0x4008A300

 #define R_RTC_BASE             0x40083000

 #define R_I3C0_BASE            0x4011F000
 #define R_I3C1_BASE            0x4011F400

/** @} */ /* End of group Device_Peripheral_peripheralAddr */

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
 * @{
 */

// #define R_MPU ((R_MPU_Type *) R_MPU_BASE)
 #define R_ACMPHS0         ((R_ACMPHS0_Type *) R_ACMPHS0_BASE)
 #define R_ACMPHS1         ((R_ACMPHS0_Type *) R_ACMPHS1_BASE)
 #define R_ACMPHS2         ((R_ACMPHS0_Type *) R_ACMPHS2_BASE)
 #define R_ACMPHS3         ((R_ACMPHS0_Type *) R_ACMPHS3_BASE)
 #define R_ACMPHS4         ((R_ACMPHS0_Type *) R_ACMPHS4_BASE)
 #define R_ACMPHS5         ((R_ACMPHS0_Type *) R_ACMPHS5_BASE)
 #define R_TZF             ((R_TZF_Type *) R_TZF_BASE)
 #define R_SRAM            ((R_SRAM_Type *) R_SRAM_BASE)
 #define R_BUS             ((R_BUS_B_Type *) R_BUS_BASE)
 #define R_DMAC0           ((R_DMAC0_Type *) R_DMAC0_BASE)
 #define R_DMAC1           ((R_DMAC0_Type *) R_DMAC1_BASE)
 #define R_DMAC2           ((R_DMAC0_Type *) R_DMAC2_BASE)
 #define R_DMAC3           ((R_DMAC0_Type *) R_DMAC3_BASE)
 #define R_DMAC4           ((R_DMAC0_Type *) R_DMAC4_BASE)
 #define R_DMAC5           ((R_DMAC0_Type *) R_DMAC5_BASE)
 #define R_DMAC6           ((R_DMAC0_Type *) R_DMAC6_BASE)
 #define R_DMAC7           ((R_DMAC0_Type *) R_DMAC7_BASE)
 #define R_DMA             ((R_DMA_Type *) R_DMA_BASE)
 #define R_DTC             ((R_DTC_Type *) R_DTC_BASE)
 #define R_ICU             ((R_ICU_Type *) R_ICU_BASE)
 #define R_CACHE           ((R_CACHE_Type *) R_CACHE_BASE)
 #define R_CPSCU           ((R_CPSCU_Type *) R_CPSCU_BASE)
 #define R_DEBUG           ((R_DEBUG_Type *) R_DBG_BASE)
 #define R_FCACHE          ((R_FCACHE_Type *) R_FCACHE_BASE)
 #define R_SYSTEM          ((R_SYSTEM_Type *) R_SYSC_BASE)
 #define R_TSN_CAL         ((R_TSN_CAL_Type *) R_TSN_CAL_BASE)
 #define R_TSN_CTRL        ((R_TSN_CTRL_Type *) R_TSN_CTRL_BASE)
 #define R_PFS             ((R_PFS_Type *) R_PFS_BASE)
 #define R_ELC             ((R_ELC_Type *) R_ELC_BASE)
 #define R_TC              ((R_TC_Type *) R_TC_BASE)
 #define R_IWDT            ((R_IWDT_Type *) R_IWDT_BASE)
 #define R_KINT            ((R_KINT_Type *) R_KINT_BASE)
 #define R_WDT             ((R_WDT_Type *) R_WDT_BASE)
 #define R_CAC             ((R_CAC_Type *) R_CAC_BASE)
 #define R_MSTP            ((R_MSTP_Type *) R_MSTP_BASE)
 #define R_POEG            ((R_POEG_Type *) R_POEG_BASE)
 #define R_USB_FS0         ((R_USB_FS0_Type *) R_USB_FS0_BASE)
 #define R_USB_HS0         ((R_USB_HS0_Type *) R_USB_HS0_BASE)
 #define R_SDHI0           ((R_SDHI0_Type *) R_SDHI0_BASE)
 #define R_SSI0            ((R_SSI0_Type *) R_SSI0_BASE)
 #define R_IIC0            ((R_IIC0_Type *) R_IIC0_BASE)
 #define R_IIC0WU          ((R_IIC0WU_Type *) R_IIC0WU_BASE)
 #define R_IIC1            ((R_IIC0_Type *) R_IIC1_BASE)
 #define R_OSPI            ((R_OSPI_Type *) R_OSPI_BASE)
 #define R_CAN0            ((R_CAN0_Type *) R_CAN0_BASE)
 #define R_CAN1            ((R_CAN0_Type *) R_CAN1_BASE)
 #define R_CEC             ((R_CEC_Type *) R_CEC_BASE)
 #if BSP_FEATURE_CANFD_LITE
  #define R_CANFD          ((R_CANFDL_Type *) R_CANFD_BASE)
 #else
  #define R_CANFD          ((R_CANFD_Type *) R_CANFD_BASE)
 #endif
 #define R_CTSU            ((R_CTSU_Type *) R_CTSU_BASE)
 #define R_PSCU            ((R_PSCU_Type *) R_PSCU_BASE)
 #if BSP_FEATURE_AGT_HAS_AGTW
  #define R_AGT0           ((R_AGTW0_Type *) R_AGT0_BASE)
  #define R_AGT1           ((R_AGTW0_Type *) R_AGT1_BASE)
  #define R_AGT2           ((R_AGTW0_Type *) R_AGT2_BASE)
  #define R_AGT3           ((R_AGTW0_Type *) R_AGT3_BASE)
  #define R_AGT4           ((R_AGTW0_Type *) R_AGT4_BASE)
  #define R_AGT5           ((R_AGTW0_Type *) R_AGT5_BASE)
 #else
  #define R_AGT0           ((R_AGT0_Type *) R_AGT0_BASE)
  #define R_AGT1           ((R_AGT0_Type *) R_AGT1_BASE)
  #define R_AGT2           ((R_AGT0_Type *) R_AGT2_BASE)
  #define R_AGT3           ((R_AGT0_Type *) R_AGT3_BASE)
  #define R_AGT4           ((R_AGT0_Type *) R_AGT4_BASE)
  #define R_AGT5           ((R_AGT0_Type *) R_AGT5_BASE)
 #endif
 #define R_AGTW0           ((R_AGTW0_Type *) R_AGTW0_BASE)
 #define R_AGTW1           ((R_AGTW0_Type *) R_AGTW1_BASE)
 #define R_TSN_CTRL        ((R_TSN_CTRL_Type *) R_TSN_CTRL_BASE)
 #define R_CRC             ((R_CRC_Type *) R_CRC_BASE)
 #if (2U == BSP_FEATURE_DOC_VERSION)
  #define R_DOC_B          ((R_DOC_B_Type *) R_DOC_BASE)
 #else
  #define R_DOC            ((R_DOC_Type *) R_DOC_BASE)
 #endif
 #define R_ETHERC_EDMAC    ((R_ETHERC_EDMAC_Type *) R_ETHERC_EDMAC_BASE)
 #define R_ETHERC0         ((R_ETHERC0_Type *) R_ETHERC0_BASE)
 #if (2U == BSP_FEATURE_SCI_VERSION)
  #define R_SCI0           ((R_SCI_B0_Type *) R_SCI0_BASE)
  #define R_SCI1           ((R_SCI_B0_Type *) R_SCI1_BASE)
  #define R_SCI2           ((R_SCI_B0_Type *) R_SCI2_BASE)
  #define R_SCI3           ((R_SCI_B0_Type *) R_SCI3_BASE)
  #define R_SCI4           ((R_SCI_B0_Type *) R_SCI4_BASE)
  #define R_SCI9           ((R_SCI_B0_Type *) R_SCI9_BASE)
 #else
  #define R_SCI0           ((R_SCI0_Type *) R_SCI0_BASE)
  #define R_SCI1           ((R_SCI0_Type *) R_SCI1_BASE)
  #define R_SCI2           ((R_SCI0_Type *) R_SCI2_BASE)
  #define R_SCI3           ((R_SCI0_Type *) R_SCI3_BASE)
  #define R_SCI4           ((R_SCI0_Type *) R_SCI4_BASE)
  #define R_SCI5           ((R_SCI0_Type *) R_SCI5_BASE)
  #define R_SCI6           ((R_SCI0_Type *) R_SCI6_BASE)
  #define R_SCI7           ((R_SCI0_Type *) R_SCI7_BASE)
  #define R_SCI8           ((R_SCI0_Type *) R_SCI8_BASE)
  #define R_SCI9           ((R_SCI0_Type *) R_SCI9_BASE)
 #endif
 #define R_SPI0            ((R_SPI0_Type *) R_SPI0_BASE)
 #define R_SPI1            ((R_SPI0_Type *) R_SPI1_BASE)
 #define R_SPI_B0          ((R_SPI_B0_Type *) R_SPI_B0_BASE)
 #define R_SPI_B1          ((R_SPI_B0_Type *) R_SPI_B1_BASE)
 #define R_GPT0            ((R_GPT0_Type *) R_GPT320_BASE)
 #define R_GPT1            ((R_GPT0_Type *) R_GPT321_BASE)
 #define R_GPT2            ((R_GPT0_Type *) R_GPT322_BASE)
 #define R_GPT3            ((R_GPT0_Type *) R_GPT323_BASE)
 #define R_GPT4            ((R_GPT0_Type *) R_GPT164_BASE)
 #define R_GPT5            ((R_GPT0_Type *) R_GPT165_BASE)
 #define R_GPT6            ((R_GPT0_Type *) R_GPT166_BASE)
 #define R_GPT7            ((R_GPT0_Type *) R_GPT167_BASE)
 #define R_GPT8            ((R_GPT0_Type *) R_GPT168_BASE)
 #define R_GPT9            ((R_GPT0_Type *) R_GPT169_BASE)
 #define R_GPT_ODC         ((R_GPT_ODC_Type *) R_GPT_ODC_BASE)
 #define R_GPT_OPS         ((R_GPT_OPS_Type *) R_GPT_OPS_BASE)
 #define R_GPT_GTCLK       ((R_GPT_GTCLK_Type *) R_GPT_GTCLK_BASE)
 #define R_ADC0            ((R_ADC0_Type *) R_ADC120_BASE)
 #define R_ADC1            ((R_ADC0_Type *) R_ADC121_BASE)
 #define R_ADC_B           ((R_ADC_B0_Type *) R_ADC120_BASE)
 #if (BSP_FEATURE_DAC_MAX_CHANNELS > 2U)
  #define R_DAC0           ((R_DAC_Type *) R_DAC120_BASE)
  #define R_DAC1           ((R_DAC_Type *) R_DAC121_BASE)
 #else
  #define R_DAC            ((R_DAC_Type *) R_DAC12_BASE)
 #endif
 #define R_FLAD            ((R_FLAD_Type *) R_FLAD_BASE)
 #define R_FACI_HP_CMD     ((R_FACI_HP_CMD_Type *) R_FACI_HP_CMD_BASE)
 #define R_FACI_HP         ((R_FACI_HP_Type *) R_FACI_HP_BASE)
 #define R_QSPI            ((R_QSPI_Type *) R_QSPI_BASE)
 #define R_TFU             ((R_TFU_Type *) R_TFU_BASE)
 #define R_I3C0            ((R_I3C0_Type *) R_I3C0_BASE)
 #define R_I3C1            ((R_I3C0_Type *) R_I3C1_BASE)

/* Not in SVD. */

 #define R_PORT0           ((R_PORT0_Type *) R_PORT0_BASE)
 #define R_PORT1           ((R_PORT0_Type *) R_PORT1_BASE)
 #define R_PORT2           ((R_PORT0_Type *) R_PORT2_BASE)
 #define R_PORT3           ((R_PORT0_Type *) R_PORT3_BASE)
 #define R_PORT4           ((R_PORT0_Type *) R_PORT4_BASE)
 #define R_PORT5           ((R_PORT0_Type *) R_PORT5_BASE)
 #define R_PORT6           ((R_PORT0_Type *) R_PORT6_BASE)
 #define R_PORT7           ((R_PORT0_Type *) R_PORT7_BASE)
 #define R_PORT8           ((R_PORT0_Type *) R_PORT8_BASE)
 #define R_PORT9           ((R_PORT0_Type *) R_PORT9_BASE)
 #define R_PORT10          ((R_PORT0_Type *) R_PORT10_BASE)
 #if (2U == BSP_FEATURE_IOPORT_VERSION)
  #define R_PORT11         ((R_PORT0_Type *) R_PORT11_BASE)
  #define R_PORT12         ((R_PORT0_Type *) R_PORT12_BASE)
  #define R_PORT13         ((R_PORT0_Type *) R_PORT13_BASE)
  #define R_PORT14         ((R_PORT0_Type *) R_PORT14_BASE)
 #endif
 #define R_PFS             ((R_PFS_Type *) R_PFS_BASE)
 #define R_PMISC           ((R_PMISC_Type *) R_PMISC_BASE)

 #define R_GPT_POEG0       ((R_GPT_POEG0_Type *) R_GPT_POEG0_BASE)
 #define R_GPT_POEG1       ((R_GPT_POEG0_Type *) R_GPT_POEG1_BASE)
 #define R_GPT_POEG2       ((R_GPT_POEG0_Type *) R_GPT_POEG2_BASE)
 #define R_GPT_POEG3       ((R_GPT_POEG0_Type *) R_GPT_POEG3_BASE)

 #define R_RTC             ((R_RTC_Type *) R_RTC_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */

#else

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripheralAddr
 * @{
 */

 #define R_ACMPHS0_BASE                0x40085000
 #define R_ACMPHS1_BASE                0x40085100
 #define R_ACMPHS2_BASE                0x40085200
 #define R_ACMPHS3_BASE                0x40085300
 #define R_ACMPHS4_BASE                0x40085400
 #define R_ACMPHS5_BASE                0x40085500
 #define R_ACMPLP_BASE                 0x40085E00
 #define R_ADC0_BASE                   0x4005C000
 #define R_ADC1_BASE                   0x4005C200
 #define R_AGT0_BASE                   0x40084000
 #define R_AGT1_BASE                   0x40084100
 #define R_AGTW0_BASE                  0x40084000
 #define R_AGTW1_BASE                  0x40084100
 #define R_BUS_BASE                    0x40003000
 #define R_CAC_BASE                    0x40044600
 #define R_CAN0_BASE                   0x40050000
 #define R_CAN1_BASE                   0x40051000
 #define R_CRC_BASE                    0x40074000
 #define R_CTSU_BASE                   0x40081000
 #define R_CTSU2_BASE                  0x40082000
 #define R_DAC_BASE                    0x4005E000
 #define R_DAC8_BASE                   0x4009E000
 #define R_DALI0_BASE                  0x4008F000
 #define R_DEBUG_BASE                  0x4001B000
 #define R_DMA_BASE                    0x40005200
 #define R_DMAC0_BASE                  0x40005000
 #define R_DMAC1_BASE                  0x40005040
 #define R_DMAC2_BASE                  0x40005080
 #define R_DMAC3_BASE                  0x400050C0
 #define R_DMAC4_BASE                  0x40005100
 #define R_DMAC5_BASE                  0x40005140
 #define R_DMAC6_BASE                  0x40005180
 #define R_DMAC7_BASE                  0x400051C0
 #define R_DOC_BASE                    0x40054100
 #define R_DRW_BASE                    0x400E4000
 #define R_DTC_BASE                    0x40005400
 #define R_ELC_BASE                    0x40041000
 #define R_ETHERC0_BASE                0x40064100
 #define R_ETHERC_EDMAC_BASE           0x40064000
 #define R_PTP_EDMAC_BASE              0x40064400
 #define R_ETHERC_EPTPC_BASE           0x40065800
 #define R_ETHERC_EPTPC1_BASE          0x40065C00
 #define R_ETHERC_EPTPC_CFG_BASE       0x40064500
 #define R_ETHERC_EPTPC_COMMON_BASE    0x40065000
 #define R_FACI_HP_CMD_BASE            0x407E0000
 #define R_FACI_HP_BASE                0x407FE000
 #define R_FACI_LP_BASE                0x407EC000
 #define R_CTSUTRIM_BASE               0x407EC000
 #define R_FCACHE_BASE                 0x4001C000
 #define R_GLCDC_BASE                  0x400E0000
 #define R_GPT0_BASE                   0x40078000
 #define R_GPT1_BASE                   0x40078100
 #define R_GPT2_BASE                   0x40078200
 #define R_GPT3_BASE                   0x40078300
 #define R_GPT4_BASE                   0x40078400
 #define R_GPT5_BASE                   0x40078500
 #define R_GPT6_BASE                   0x40078600
 #define R_GPT7_BASE                   0x40078700
 #define R_GPT8_BASE                   0x40078800
 #define R_GPT9_BASE                   0x40078900
 #define R_GPT10_BASE                  0x40078A00
 #define R_GPT11_BASE                  0x40078B00
 #define R_GPT12_BASE                  0x40078C00
 #define R_GPT13_BASE                  0x40078D00
 #define R_GPT_ODC_BASE                0x4007B000
 #define R_GPT_OPS_BASE                0x40078FF0
 #define R_GPT_POEG0_BASE              0x40042000
 #define R_GPT_POEG1_BASE              0x40042100
 #define R_GPT_POEG2_BASE              0x40042200
 #define R_GPT_POEG3_BASE              0x40042300
 #define R_I3C0_BASE                   0x40083000
 #define R_ICU_BASE                    0x40006000
 #define R_IIC0_BASE                   0x40053000
 #define R_IIC1_BASE                   0x40053100
 #define R_IIC2_BASE                   0x40053200
 #define R_IRDA_BASE                   0x40070F00
 #define R_IWDT_BASE                   0x40044400
 #define R_JPEG_BASE                   0x400E6000
 #define R_KINT_BASE                   0x40080000
 #define R_MMF_BASE                    0x40001000
 #define R_MPU_MMPU_BASE               0x40000000
 #define R_MPU_SMPU_BASE               0x40000C00
 #define R_MPU_SPMON_BASE              0x40000D00
 #define R_MSTP_BASE                   (0x40047000 - 4U) /* MSTPCRA is not located in R_MSTP so the base address must be moved so that MSTPCRB is located at 0x40047000. */
 #define R_OPAMP_BASE                  0x40086000
 #define R_OPAMP2_BASE                 0x400867F8
 #define R_PDC_BASE                    0x40094000
 #define R_PORT0_BASE                  0x40040000
 #define R_PORT1_BASE                  0x40040020
 #define R_PORT2_BASE                  0x40040040
 #define R_PORT3_BASE                  0x40040060
 #define R_PORT4_BASE                  0x40040080
 #define R_PORT5_BASE                  0x400400A0
 #define R_PORT6_BASE                  0x400400C0
 #define R_PORT7_BASE                  0x400400E0
 #define R_PORT8_BASE                  0x40040100
 #define R_PORT9_BASE                  0x40040120
 #define R_PORT10_BASE                 0x40040140
 #define R_PORT11_BASE                 0x40040160
 #define R_PFS_BASE                    0x40040800
 #define R_PMISC_BASE                  0x40040D00
 #define R_QSPI_BASE                   0x64000000
 #define R_RTC_BASE                    0x40044000
 #define R_SCI0_BASE                   0x40070000
 #define R_SCI1_BASE                   0x40070020
 #define R_SCI2_BASE                   0x40070040
 #define R_SCI3_BASE                   0x40070060
 #define R_SCI4_BASE                   0x40070080
 #define R_SCI5_BASE                   0x400700A0
 #define R_SCI6_BASE                   0x400700C0
 #define R_SCI7_BASE                   0x400700E0
 #define R_SCI8_BASE                   0x40070100
 #define R_SCI9_BASE                   0x40070120
 #define R_SDADC0_BASE                 0x4009C000
 #define R_SDHI0_BASE                  0x40062000
 #define R_SDHI1_BASE                  0x40062400
 #define R_SLCDC_BASE                  0x40082000
 #define R_SPI0_BASE                   0x40072000
 #define R_SPI1_BASE                   0x40072100
 #define R_SRAM_BASE                   0x40002000
 #define R_SRC_BASE                    0x40048000
 #define R_SSI0_BASE                   0x4004E000
 #define R_SSI1_BASE                   0x4004E100
 #define R_SYSTEM_BASE                 0x4001E000
 #define R_TSN_BASE                    0x407EC000
 #define R_TSN_CAL_BASE                0x407FB17C
 #define R_TSN_CTRL_BASE               0x4005D000
 #define R_USB_FS0_BASE                0x40090000
 #define R_USB_HS0_BASE                0x40060000
 #define R_WDT_BASE                    0x40044200

/** @} */ /* End of group Device_Peripheral_peripheralAddr */

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
 * @{
 */

 #define R_ACMPHS0                ((R_ACMPHS0_Type *) R_ACMPHS0_BASE)
 #define R_ACMPHS1                ((R_ACMPHS0_Type *) R_ACMPHS1_BASE)
 #define R_ACMPHS2                ((R_ACMPHS0_Type *) R_ACMPHS2_BASE)
 #define R_ACMPHS3                ((R_ACMPHS0_Type *) R_ACMPHS3_BASE)
 #define R_ACMPHS4                ((R_ACMPHS0_Type *) R_ACMPHS4_BASE)
 #define R_ACMPHS5                ((R_ACMPHS0_Type *) R_ACMPHS5_BASE)
 #define R_ACMPLP                 ((R_ACMPLP_Type *) R_ACMPLP_BASE)
 #define R_ADC0                   ((R_ADC0_Type *) R_ADC0_BASE)
 #define R_ADC1                   ((R_ADC0_Type *) R_ADC1_BASE)
 #define R_AGT0                   ((R_AGT0_Type *) R_AGT0_BASE)
 #define R_AGT1                   ((R_AGT0_Type *) R_AGT1_BASE)
 #define R_AGTW0                  ((R_AGTW0_Type *) R_AGTW0_BASE)
 #define R_AGTW1                  ((R_AGTW0_Type *) R_AGTW1_BASE)
 #define R_BUS                    ((R_BUS_Type *) R_BUS_BASE)
 #define R_CAC                    ((R_CAC_Type *) R_CAC_BASE)
 #define R_CAN0                   ((R_CAN0_Type *) R_CAN0_BASE)
 #define R_CAN1                   ((R_CAN0_Type *) R_CAN1_BASE)
 #define R_CRC                    ((R_CRC_Type *) R_CRC_BASE)
 #if (2U == BSP_FEATURE_CTSU_VERSION)
  #define R_CTSU                  ((R_CTSU2_Type *) R_CTSU2_BASE)
 #else
  #define R_CTSU                  ((R_CTSU_Type *) R_CTSU_BASE)
 #endif
 #define R_DAC                    ((R_DAC_Type *) R_DAC_BASE)
 #define R_DAC8                   ((R_DAC8_Type *) R_DAC8_BASE)
 #define R_DALI0                  ((R_DALI0_Type *) R_DALI0_BASE)
 #define R_DEBUG                  ((R_DEBUG_Type *) R_DEBUG_BASE)
 #define R_DMA                    ((R_DMA_Type *) R_DMA_BASE)
 #define R_DMAC0                  ((R_DMAC0_Type *) R_DMAC0_BASE)
 #define R_DMAC1                  ((R_DMAC0_Type *) R_DMAC1_BASE)
 #define R_DMAC2                  ((R_DMAC0_Type *) R_DMAC2_BASE)
 #define R_DMAC3                  ((R_DMAC0_Type *) R_DMAC3_BASE)
 #define R_DMAC4                  ((R_DMAC0_Type *) R_DMAC4_BASE)
 #define R_DMAC5                  ((R_DMAC0_Type *) R_DMAC5_BASE)
 #define R_DMAC6                  ((R_DMAC0_Type *) R_DMAC6_BASE)
 #define R_DMAC7                  ((R_DMAC0_Type *) R_DMAC7_BASE)
 #define R_DOC                    ((R_DOC_Type *) R_DOC_BASE)
 #define R_DRW                    ((R_DRW_Type *) R_DRW_BASE)
 #define R_DTC                    ((R_DTC_Type *) R_DTC_BASE)
 #define R_ELC                    ((R_ELC_Type *) R_ELC_BASE)
 #define R_ETHERC0                ((R_ETHERC0_Type *) R_ETHERC0_BASE)
 #define R_ETHERC_EDMAC           ((R_ETHERC_EDMAC_Type *) R_ETHERC_EDMAC_BASE)
 #define R_PTP_EDMAC              ((R_ETHERC_EDMAC_Type *) R_PTP_EDMAC_BASE)
 #define R_ETHERC_EPTPC           ((R_ETHERC_EPTPC_Type *) R_ETHERC_EPTPC_BASE)
 #define R_ETHERC_EPTPC1          ((R_ETHERC_EPTPC0_Type *) R_ETHERC_EPTPC1_BASE)
 #define R_ETHERC_EPTPC_CFG       ((R_ETHERC_EPTPC_CFG_Type *) R_ETHERC_EPTPC_CFG_BASE)
 #define R_ETHERC_EPTPC_COMMON    ((R_ETHERC_EPTPC_COMMON_Type *) R_ETHERC_EPTPC_COMMON_BASE)
 #define R_FACI_HP_CMD            ((R_FACI_HP_CMD_Type *) R_FACI_HP_CMD_BASE)
 #define R_FACI_HP                ((R_FACI_HP_Type *) R_FACI_HP_BASE)
 #define R_FACI_LP                ((R_FACI_LP_Type *) R_FACI_LP_BASE)
 #define R_CTSUTRIM               ((R_CTSUTRIM_Type *) R_CTSUTRIM_BASE)
 #define R_FCACHE                 ((R_FCACHE_Type *) R_FCACHE_BASE)
 #define R_GLCDC                  ((R_GLCDC_Type *) R_GLCDC_BASE)
 #define R_GPT0                   ((R_GPT0_Type *) R_GPT0_BASE)
 #define R_GPT1                   ((R_GPT0_Type *) R_GPT1_BASE)
 #define R_GPT2                   ((R_GPT0_Type *) R_GPT2_BASE)
 #define R_GPT3                   ((R_GPT0_Type *) R_GPT3_BASE)
 #define R_GPT4                   ((R_GPT0_Type *) R_GPT4_BASE)
 #define R_GPT5                   ((R_GPT0_Type *) R_GPT5_BASE)
 #define R_GPT6                   ((R_GPT0_Type *) R_GPT6_BASE)
 #define R_GPT7                   ((R_GPT0_Type *) R_GPT7_BASE)
 #define R_GPT8                   ((R_GPT0_Type *) R_GPT8_BASE)
 #define R_GPT9                   ((R_GPT0_Type *) R_GPT9_BASE)
 #define R_GPT10                  ((R_GPT0_Type *) R_GPT10_BASE)
 #define R_GPT11                  ((R_GPT0_Type *) R_GPT11_BASE)
 #define R_GPT12                  ((R_GPT0_Type *) R_GPT12_BASE)
 #define R_GPT13                  ((R_GPT0_Type *) R_GPT13_BASE)
 #define R_GPT_ODC                ((R_GPT_ODC_Type *) R_GPT_ODC_BASE)
 #define R_GPT_OPS                ((R_GPT_OPS_Type *) R_GPT_OPS_BASE)
 #define R_GPT_POEG0              ((R_GPT_POEG0_Type *) R_GPT_POEG0_BASE)
 #define R_GPT_POEG1              ((R_GPT_POEG0_Type *) R_GPT_POEG1_BASE)
 #define R_GPT_POEG2              ((R_GPT_POEG0_Type *) R_GPT_POEG2_BASE)
 #define R_GPT_POEG3              ((R_GPT_POEG0_Type *) R_GPT_POEG3_BASE)
 #define R_I3C0                   ((R_I3C0_Type *) R_I3C0_BASE)
 #define R_ICU                    ((R_ICU_Type *) R_ICU_BASE)
 #define R_IIC0                   ((R_IIC0_Type *) R_IIC0_BASE)
 #define R_IIC1                   ((R_IIC0_Type *) R_IIC1_BASE)
 #define R_IIC2                   ((R_IIC0_Type *) R_IIC2_BASE)
 #define R_IRDA                   ((R_IRDA_Type *) R_IRDA_BASE)
 #define R_IWDT                   ((R_IWDT_Type *) R_IWDT_BASE)
 #define R_JPEG                   ((R_JPEG_Type *) R_JPEG_BASE)
 #define R_KINT                   ((R_KINT_Type *) R_KINT_BASE)
 #define R_MMF                    ((R_MMF_Type *) R_MMF_BASE)
 #define R_MPU_MMPU               ((R_MPU_MMPU_Type *) R_MPU_MMPU_BASE)
 #define R_MPU_SMPU               ((R_MPU_SMPU_Type *) R_MPU_SMPU_BASE)
 #define R_MPU_SPMON              ((R_MPU_SPMON_Type *) R_MPU_SPMON_BASE)
 #define R_MSTP                   ((R_MSTP_Type *) R_MSTP_BASE)
 #if (2U == BSP_FEATURE_OPAMP_BASE_ADDRESS)
  #define R_OPAMP                 ((R_OPAMP_Type *) R_OPAMP2_BASE)
 #else
  #define R_OPAMP                 ((R_OPAMP_Type *) R_OPAMP_BASE)
 #endif
 #define R_PDC                    ((R_PDC_Type *) R_PDC_BASE)
 #define R_PORT0                  ((R_PORT0_Type *) R_PORT0_BASE)
 #define R_PORT1                  ((R_PORT0_Type *) R_PORT1_BASE)
 #define R_PORT2                  ((R_PORT0_Type *) R_PORT2_BASE)
 #define R_PORT3                  ((R_PORT0_Type *) R_PORT3_BASE)
 #define R_PORT4                  ((R_PORT0_Type *) R_PORT4_BASE)
 #define R_PORT5                  ((R_PORT0_Type *) R_PORT5_BASE)
 #define R_PORT6                  ((R_PORT0_Type *) R_PORT6_BASE)
 #define R_PORT7                  ((R_PORT0_Type *) R_PORT7_BASE)
 #define R_PORT8                  ((R_PORT0_Type *) R_PORT8_BASE)
 #define R_PORT9                  ((R_PORT0_Type *) R_PORT9_BASE)
 #define R_PORT10                 ((R_PORT0_Type *) R_PORT10_BASE)
 #define R_PORT11                 ((R_PORT0_Type *) R_PORT11_BASE)
 #define R_PFS                    ((R_PFS_Type *) R_PFS_BASE)
 #define R_PMISC                  ((R_PMISC_Type *) R_PMISC_BASE)
 #define R_QSPI                   ((R_QSPI_Type *) R_QSPI_BASE)
 #define R_RTC                    ((R_RTC_Type *) R_RTC_BASE)
 #define R_SCI0                   ((R_SCI0_Type *) R_SCI0_BASE)
 #define R_SCI1                   ((R_SCI0_Type *) R_SCI1_BASE)
 #define R_SCI2                   ((R_SCI0_Type *) R_SCI2_BASE)
 #define R_SCI3                   ((R_SCI0_Type *) R_SCI3_BASE)
 #define R_SCI4                   ((R_SCI0_Type *) R_SCI4_BASE)
 #define R_SCI5                   ((R_SCI0_Type *) R_SCI5_BASE)
 #define R_SCI6                   ((R_SCI0_Type *) R_SCI6_BASE)
 #define R_SCI7                   ((R_SCI0_Type *) R_SCI7_BASE)
 #define R_SCI8                   ((R_SCI0_Type *) R_SCI8_BASE)
 #define R_SCI9                   ((R_SCI0_Type *) R_SCI9_BASE)
 #define R_SDADC0                 ((R_SDADC0_Type *) R_SDADC0_BASE)
 #define R_SDHI0                  ((R_SDHI0_Type *) R_SDHI0_BASE)
 #define R_SDHI1                  ((R_SDHI0_Type *) R_SDHI1_BASE)
 #define R_SLCDC                  ((R_SLCDC_Type *) R_SLCDC_BASE)
 #define R_SPI0                   ((R_SPI0_Type *) R_SPI0_BASE)
 #define R_SPI1                   ((R_SPI0_Type *) R_SPI1_BASE)
 #define R_SRAM                   ((R_SRAM_Type *) R_SRAM_BASE)
 #define R_SRC                    ((R_SRC_Type *) R_SRC_BASE)
 #define R_SSI0                   ((R_SSI0_Type *) R_SSI0_BASE)
 #define R_SSI1                   ((R_SSI0_Type *) R_SSI1_BASE)
 #define R_SYSTEM                 ((R_SYSTEM_Type *) R_SYSTEM_BASE)
 #define R_TSN                    ((R_TSN_Type *) R_TSN_BASE)
 #define R_TSN_CAL                ((R_TSN_CAL_Type *) R_TSN_CAL_BASE)
 #define R_TSN_CTRL               ((R_TSN_CTRL_Type *) R_TSN_CTRL_BASE)
 #define R_USB_FS0                ((R_USB_FS0_Type *) R_USB_FS0_BASE)
 #define R_USB_HS0                ((R_USB_HS0_Type *) R_USB_HS0_BASE)
 #define R_WDT                    ((R_WDT_Type *) R_WDT_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */

#endif

#endif
