#ifndef _FSL_SDIF_REGS_
#define _FSL_SDIF_REGS_

#ifdef __cplusplus
extern "C" {
#endif


#define FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE 4096

/* ----------------------------------------------------------------------------
   -- SDIF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDIF_Register_Masks SDIF Register Masks
 * @{
 */

/*! @name CTRL - Control register */
/*! @{ */
#define SDIF_CTRL_CONTROLLER_RESET_MASK          (0x1U)
#define SDIF_CTRL_CONTROLLER_RESET_SHIFT         (0U)
#define SDIF_CTRL_CONTROLLER_RESET(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CONTROLLER_RESET_SHIFT)) & SDIF_CTRL_CONTROLLER_RESET_MASK)
#define SDIF_CTRL_FIFO_RESET_MASK                (0x2U)
#define SDIF_CTRL_FIFO_RESET_SHIFT               (1U)
#define SDIF_CTRL_FIFO_RESET(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_FIFO_RESET_SHIFT)) & SDIF_CTRL_FIFO_RESET_MASK)
#define SDIF_CTRL_DMA_RESET_MASK                 (0x4U)
#define SDIF_CTRL_DMA_RESET_SHIFT                (2U)
#define SDIF_CTRL_DMA_RESET(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_DMA_RESET_SHIFT)) & SDIF_CTRL_DMA_RESET_MASK)
#define SDIF_CTRL_INT_ENABLE_MASK                (0x10U)
#define SDIF_CTRL_INT_ENABLE_SHIFT               (4U)
#define SDIF_CTRL_INT_ENABLE(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_INT_ENABLE_SHIFT)) & SDIF_CTRL_INT_ENABLE_MASK)
#define SDIF_CTRL_READ_WAIT_MASK                 (0x40U)
#define SDIF_CTRL_READ_WAIT_SHIFT                (6U)
#define SDIF_CTRL_READ_WAIT(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_READ_WAIT_SHIFT)) & SDIF_CTRL_READ_WAIT_MASK)
#define SDIF_CTRL_SEND_IRQ_RESPONSE_MASK         (0x80U)
#define SDIF_CTRL_SEND_IRQ_RESPONSE_SHIFT        (7U)
#define SDIF_CTRL_SEND_IRQ_RESPONSE(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_SEND_IRQ_RESPONSE_SHIFT)) & SDIF_CTRL_SEND_IRQ_RESPONSE_MASK)
#define SDIF_CTRL_ABORT_READ_DATA_MASK           (0x100U)
#define SDIF_CTRL_ABORT_READ_DATA_SHIFT          (8U)
#define SDIF_CTRL_ABORT_READ_DATA(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_ABORT_READ_DATA_SHIFT)) & SDIF_CTRL_ABORT_READ_DATA_MASK)
#define SDIF_CTRL_SEND_CCSD_MASK                 (0x200U)
#define SDIF_CTRL_SEND_CCSD_SHIFT                (9U)
#define SDIF_CTRL_SEND_CCSD(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_SEND_CCSD_SHIFT)) & SDIF_CTRL_SEND_CCSD_MASK)
#define SDIF_CTRL_SEND_AUTO_STOP_CCSD_MASK       (0x400U)
#define SDIF_CTRL_SEND_AUTO_STOP_CCSD_SHIFT      (10U)
#define SDIF_CTRL_SEND_AUTO_STOP_CCSD(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_SEND_AUTO_STOP_CCSD_SHIFT)) & SDIF_CTRL_SEND_AUTO_STOP_CCSD_MASK)
#define SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_MASK (0x800U)
#define SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_SHIFT (11U)
#define SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_SHIFT)) & SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_MASK)
#define SDIF_CTRL_CARD_VOLTAGE_A0_MASK           (0x10000U)
#define SDIF_CTRL_CARD_VOLTAGE_A0_SHIFT          (16U)
#define SDIF_CTRL_CARD_VOLTAGE_A0(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CARD_VOLTAGE_A0_SHIFT)) & SDIF_CTRL_CARD_VOLTAGE_A0_MASK)
#define SDIF_CTRL_CARD_VOLTAGE_A1_MASK           (0x20000U)
#define SDIF_CTRL_CARD_VOLTAGE_A1_SHIFT          (17U)
#define SDIF_CTRL_CARD_VOLTAGE_A1(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CARD_VOLTAGE_A1_SHIFT)) & SDIF_CTRL_CARD_VOLTAGE_A1_MASK)
#define SDIF_CTRL_CARD_VOLTAGE_A2_MASK           (0x40000U)
#define SDIF_CTRL_CARD_VOLTAGE_A2_SHIFT          (18U)
#define SDIF_CTRL_CARD_VOLTAGE_A2(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CARD_VOLTAGE_A2_SHIFT)) & SDIF_CTRL_CARD_VOLTAGE_A2_MASK)
#define SDIF_CTRL_USE_INTERNAL_DMAC_MASK         (0x2000000U)
#define SDIF_CTRL_USE_INTERNAL_DMAC_SHIFT        (25U)
#define SDIF_CTRL_USE_INTERNAL_DMAC(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_USE_INTERNAL_DMAC_SHIFT)) & SDIF_CTRL_USE_INTERNAL_DMAC_MASK)
/*! @} */

/*! @name PWREN - Power Enable register */
/*! @{ */
#define SDIF_PWREN_POWER_ENABLE_MASK             (0x1U)
#define SDIF_PWREN_POWER_ENABLE_SHIFT            (0U)
#define SDIF_PWREN_POWER_ENABLE(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_PWREN_POWER_ENABLE_SHIFT)) & SDIF_PWREN_POWER_ENABLE_MASK)
/*! @} */

/*! @name CLKDIV - Clock Divider register */
/*! @{ */
#define SDIF_CLKDIV_CLK_DIVIDER0_MASK            (0xFFU)
#define SDIF_CLKDIV_CLK_DIVIDER0_SHIFT           (0U)
#define SDIF_CLKDIV_CLK_DIVIDER0(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CLKDIV_CLK_DIVIDER0_SHIFT)) & SDIF_CLKDIV_CLK_DIVIDER0_MASK)
/*! @} */

/*! @name CLKENA - Clock Enable register */
/*! @{ */
#define SDIF_CLKENA_CCLK_ENABLE_MASK             (0x1U)
#define SDIF_CLKENA_CCLK_ENABLE_SHIFT            (0U)
#define SDIF_CLKENA_CCLK_ENABLE(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_CLKENA_CCLK_ENABLE_SHIFT)) & SDIF_CLKENA_CCLK_ENABLE_MASK)
#define SDIF_CLKENA_CCLK_LOW_POWER_MASK          (0x10000U)
#define SDIF_CLKENA_CCLK_LOW_POWER_SHIFT         (16U)
#define SDIF_CLKENA_CCLK_LOW_POWER(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_CLKENA_CCLK_LOW_POWER_SHIFT)) & SDIF_CLKENA_CCLK_LOW_POWER_MASK)
/*! @} */

/*! @name TMOUT - Time-out register */
/*! @{ */
#define SDIF_TMOUT_RESPONSE_TIMEOUT_MASK         (0xFFU)
#define SDIF_TMOUT_RESPONSE_TIMEOUT_SHIFT        (0U)
#define SDIF_TMOUT_RESPONSE_TIMEOUT(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_TMOUT_RESPONSE_TIMEOUT_SHIFT)) & SDIF_TMOUT_RESPONSE_TIMEOUT_MASK)
#define SDIF_TMOUT_DATA_TIMEOUT_MASK             (0xFFFFFF00U)
#define SDIF_TMOUT_DATA_TIMEOUT_SHIFT            (8U)
#define SDIF_TMOUT_DATA_TIMEOUT(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_TMOUT_DATA_TIMEOUT_SHIFT)) & SDIF_TMOUT_DATA_TIMEOUT_MASK)
/*! @} */

/*! @name CTYPE - Card Type register */
/*! @{ */
#define SDIF_CTYPE_CARD_WIDTH0_MASK              (0x1U)
#define SDIF_CTYPE_CARD_WIDTH0_SHIFT             (0U)
#define SDIF_CTYPE_CARD_WIDTH0(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CTYPE_CARD_WIDTH0_SHIFT)) & SDIF_CTYPE_CARD_WIDTH0_MASK)
#define SDIF_CTYPE_CARD_WIDTH1_MASK              (0x10000U)
#define SDIF_CTYPE_CARD_WIDTH1_SHIFT             (16U)
#define SDIF_CTYPE_CARD_WIDTH1(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CTYPE_CARD_WIDTH1_SHIFT)) & SDIF_CTYPE_CARD_WIDTH1_MASK)
/*! @} */

/*! @name BLKSIZ - Block Size register */
/*! @{ */
#define SDIF_BLKSIZ_BLOCK_SIZE_MASK              (0xFFFFU)
#define SDIF_BLKSIZ_BLOCK_SIZE_SHIFT             (0U)
#define SDIF_BLKSIZ_BLOCK_SIZE(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_BLKSIZ_BLOCK_SIZE_SHIFT)) & SDIF_BLKSIZ_BLOCK_SIZE_MASK)
/*! @} */

/*! @name BYTCNT - Byte Count register */
/*! @{ */
#define SDIF_BYTCNT_BYTE_COUNT_MASK              (0xFFFFFFFFU)
#define SDIF_BYTCNT_BYTE_COUNT_SHIFT             (0U)
#define SDIF_BYTCNT_BYTE_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_BYTCNT_BYTE_COUNT_SHIFT)) & SDIF_BYTCNT_BYTE_COUNT_MASK)
/*! @} */

/*! @name INTMASK - Interrupt Mask register */
/*! @{ */
#define SDIF_INTMASK_CDET_MASK                   (0x1U)
#define SDIF_INTMASK_CDET_SHIFT                  (0U)
#define SDIF_INTMASK_CDET(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_CDET_SHIFT)) & SDIF_INTMASK_CDET_MASK)
#define SDIF_INTMASK_RE_MASK                     (0x2U)
#define SDIF_INTMASK_RE_SHIFT                    (1U)
#define SDIF_INTMASK_RE(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RE_SHIFT)) & SDIF_INTMASK_RE_MASK)
#define SDIF_INTMASK_CDONE_MASK                  (0x4U)
#define SDIF_INTMASK_CDONE_SHIFT                 (2U)
#define SDIF_INTMASK_CDONE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_CDONE_SHIFT)) & SDIF_INTMASK_CDONE_MASK)
#define SDIF_INTMASK_DTO_MASK                    (0x8U)
#define SDIF_INTMASK_DTO_SHIFT                   (3U)
#define SDIF_INTMASK_DTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_DTO_SHIFT)) & SDIF_INTMASK_DTO_MASK)
#define SDIF_INTMASK_TXDR_MASK                   (0x10U)
#define SDIF_INTMASK_TXDR_SHIFT                  (4U)
#define SDIF_INTMASK_TXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_TXDR_SHIFT)) & SDIF_INTMASK_TXDR_MASK)
#define SDIF_INTMASK_RXDR_MASK                   (0x20U)
#define SDIF_INTMASK_RXDR_SHIFT                  (5U)
#define SDIF_INTMASK_RXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RXDR_SHIFT)) & SDIF_INTMASK_RXDR_MASK)
#define SDIF_INTMASK_RCRC_MASK                   (0x40U)
#define SDIF_INTMASK_RCRC_SHIFT                  (6U)
#define SDIF_INTMASK_RCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RCRC_SHIFT)) & SDIF_INTMASK_RCRC_MASK)
#define SDIF_INTMASK_DCRC_MASK                   (0x80U)
#define SDIF_INTMASK_DCRC_SHIFT                  (7U)
#define SDIF_INTMASK_DCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_DCRC_SHIFT)) & SDIF_INTMASK_DCRC_MASK)
#define SDIF_INTMASK_RTO_MASK                    (0x100U)
#define SDIF_INTMASK_RTO_SHIFT                   (8U)
#define SDIF_INTMASK_RTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RTO_SHIFT)) & SDIF_INTMASK_RTO_MASK)
#define SDIF_INTMASK_DRTO_MASK                   (0x200U)
#define SDIF_INTMASK_DRTO_SHIFT                  (9U)
#define SDIF_INTMASK_DRTO(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_DRTO_SHIFT)) & SDIF_INTMASK_DRTO_MASK)
#define SDIF_INTMASK_HTO_MASK                    (0x400U)
#define SDIF_INTMASK_HTO_SHIFT                   (10U)
#define SDIF_INTMASK_HTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_HTO_SHIFT)) & SDIF_INTMASK_HTO_MASK)
#define SDIF_INTMASK_FRUN_MASK                   (0x800U)
#define SDIF_INTMASK_FRUN_SHIFT                  (11U)
#define SDIF_INTMASK_FRUN(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_FRUN_SHIFT)) & SDIF_INTMASK_FRUN_MASK)
#define SDIF_INTMASK_HLE_MASK                    (0x1000U)
#define SDIF_INTMASK_HLE_SHIFT                   (12U)
#define SDIF_INTMASK_HLE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_HLE_SHIFT)) & SDIF_INTMASK_HLE_MASK)
#define SDIF_INTMASK_SBE_MASK                    (0x2000U)
#define SDIF_INTMASK_SBE_SHIFT                   (13U)
#define SDIF_INTMASK_SBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_SBE_SHIFT)) & SDIF_INTMASK_SBE_MASK)
#define SDIF_INTMASK_ACD_MASK                    (0x4000U)
#define SDIF_INTMASK_ACD_SHIFT                   (14U)
#define SDIF_INTMASK_ACD(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_ACD_SHIFT)) & SDIF_INTMASK_ACD_MASK)
#define SDIF_INTMASK_EBE_MASK                    (0x8000U)
#define SDIF_INTMASK_EBE_SHIFT                   (15U)
#define SDIF_INTMASK_EBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_EBE_SHIFT)) & SDIF_INTMASK_EBE_MASK)
#define SDIF_INTMASK_SDIO_INT_MASK_MASK          (0x10000U)
#define SDIF_INTMASK_SDIO_INT_MASK_SHIFT         (16U)
#define SDIF_INTMASK_SDIO_INT_MASK(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_SDIO_INT_MASK_SHIFT)) & SDIF_INTMASK_SDIO_INT_MASK_MASK)
/*! @} */

/*! @name CMDARG - Command Argument register */
/*! @{ */
#define SDIF_CMDARG_CMD_ARG_MASK                 (0xFFFFFFFFU)
#define SDIF_CMDARG_CMD_ARG_SHIFT                (0U)
#define SDIF_CMDARG_CMD_ARG(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CMDARG_CMD_ARG_SHIFT)) & SDIF_CMDARG_CMD_ARG_MASK)
/*! @} */

/*! @name CMD - Command register */
/*! @{ */
#define SDIF_CMD_CMD_INDEX_MASK                  (0x3FU)
#define SDIF_CMD_CMD_INDEX_SHIFT                 (0U)
#define SDIF_CMD_CMD_INDEX(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_CMD_INDEX_SHIFT)) & SDIF_CMD_CMD_INDEX_MASK)
#define SDIF_CMD_RESPONSE_EXPECT_MASK            (0x40U)
#define SDIF_CMD_RESPONSE_EXPECT_SHIFT           (6U)
#define SDIF_CMD_RESPONSE_EXPECT(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_RESPONSE_EXPECT_SHIFT)) & SDIF_CMD_RESPONSE_EXPECT_MASK)
#define SDIF_CMD_RESPONSE_LENGTH_MASK            (0x80U)
#define SDIF_CMD_RESPONSE_LENGTH_SHIFT           (7U)
#define SDIF_CMD_RESPONSE_LENGTH(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_RESPONSE_LENGTH_SHIFT)) & SDIF_CMD_RESPONSE_LENGTH_MASK)
#define SDIF_CMD_CHECK_RESPONSE_CRC_MASK         (0x100U)
#define SDIF_CMD_CHECK_RESPONSE_CRC_SHIFT        (8U)
#define SDIF_CMD_CHECK_RESPONSE_CRC(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_CHECK_RESPONSE_CRC_SHIFT)) & SDIF_CMD_CHECK_RESPONSE_CRC_MASK)
#define SDIF_CMD_DATA_EXPECTED_MASK              (0x200U)
#define SDIF_CMD_DATA_EXPECTED_SHIFT             (9U)
#define SDIF_CMD_DATA_EXPECTED(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_DATA_EXPECTED_SHIFT)) & SDIF_CMD_DATA_EXPECTED_MASK)
#define SDIF_CMD_READ_WRITE_MASK                 (0x400U)
#define SDIF_CMD_READ_WRITE_SHIFT                (10U)
#define SDIF_CMD_READ_WRITE(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_READ_WRITE_SHIFT)) & SDIF_CMD_READ_WRITE_MASK)
#define SDIF_CMD_TRANSFER_MODE_MASK              (0x800U)
#define SDIF_CMD_TRANSFER_MODE_SHIFT             (11U)
#define SDIF_CMD_TRANSFER_MODE(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_TRANSFER_MODE_SHIFT)) & SDIF_CMD_TRANSFER_MODE_MASK)
#define SDIF_CMD_SEND_AUTO_STOP_MASK             (0x1000U)
#define SDIF_CMD_SEND_AUTO_STOP_SHIFT            (12U)
#define SDIF_CMD_SEND_AUTO_STOP(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_SEND_AUTO_STOP_SHIFT)) & SDIF_CMD_SEND_AUTO_STOP_MASK)
#define SDIF_CMD_WAIT_PRVDATA_COMPLETE_MASK      (0x2000U)
#define SDIF_CMD_WAIT_PRVDATA_COMPLETE_SHIFT     (13U)
#define SDIF_CMD_WAIT_PRVDATA_COMPLETE(x)        (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_WAIT_PRVDATA_COMPLETE_SHIFT)) & SDIF_CMD_WAIT_PRVDATA_COMPLETE_MASK)
#define SDIF_CMD_STOP_ABORT_CMD_MASK             (0x4000U)
#define SDIF_CMD_STOP_ABORT_CMD_SHIFT            (14U)
#define SDIF_CMD_STOP_ABORT_CMD(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_STOP_ABORT_CMD_SHIFT)) & SDIF_CMD_STOP_ABORT_CMD_MASK)
#define SDIF_CMD_SEND_INITIALIZATION_MASK        (0x8000U)
#define SDIF_CMD_SEND_INITIALIZATION_SHIFT       (15U)
#define SDIF_CMD_SEND_INITIALIZATION(x)          (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_SEND_INITIALIZATION_SHIFT)) & SDIF_CMD_SEND_INITIALIZATION_MASK)
#define SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_MASK (0x200000U)
#define SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_SHIFT (21U)
#define SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY(x)  (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_SHIFT)) & SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_MASK)
#define SDIF_CMD_READ_CEATA_DEVICE_MASK          (0x400000U)
#define SDIF_CMD_READ_CEATA_DEVICE_SHIFT         (22U)
#define SDIF_CMD_READ_CEATA_DEVICE(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_READ_CEATA_DEVICE_SHIFT)) & SDIF_CMD_READ_CEATA_DEVICE_MASK)
#define SDIF_CMD_CCS_EXPECTED_MASK               (0x800000U)
#define SDIF_CMD_CCS_EXPECTED_SHIFT              (23U)
#define SDIF_CMD_CCS_EXPECTED(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_CCS_EXPECTED_SHIFT)) & SDIF_CMD_CCS_EXPECTED_MASK)
#define SDIF_CMD_ENABLE_BOOT_MASK                (0x1000000U)
#define SDIF_CMD_ENABLE_BOOT_SHIFT               (24U)
#define SDIF_CMD_ENABLE_BOOT(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_ENABLE_BOOT_SHIFT)) & SDIF_CMD_ENABLE_BOOT_MASK)
#define SDIF_CMD_EXPECT_BOOT_ACK_MASK            (0x2000000U)
#define SDIF_CMD_EXPECT_BOOT_ACK_SHIFT           (25U)
#define SDIF_CMD_EXPECT_BOOT_ACK(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_EXPECT_BOOT_ACK_SHIFT)) & SDIF_CMD_EXPECT_BOOT_ACK_MASK)
#define SDIF_CMD_DISABLE_BOOT_MASK               (0x4000000U)
#define SDIF_CMD_DISABLE_BOOT_SHIFT              (26U)
#define SDIF_CMD_DISABLE_BOOT(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_DISABLE_BOOT_SHIFT)) & SDIF_CMD_DISABLE_BOOT_MASK)
#define SDIF_CMD_BOOT_MODE_MASK                  (0x8000000U)
#define SDIF_CMD_BOOT_MODE_SHIFT                 (27U)
#define SDIF_CMD_BOOT_MODE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_BOOT_MODE_SHIFT)) & SDIF_CMD_BOOT_MODE_MASK)
#define SDIF_CMD_VOLT_SWITCH_MASK                (0x10000000U)
#define SDIF_CMD_VOLT_SWITCH_SHIFT               (28U)
#define SDIF_CMD_VOLT_SWITCH(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_VOLT_SWITCH_SHIFT)) & SDIF_CMD_VOLT_SWITCH_MASK)
#define SDIF_CMD_USE_HOLD_REG_MASK               (0x20000000U)
#define SDIF_CMD_USE_HOLD_REG_SHIFT              (29U)
#define SDIF_CMD_USE_HOLD_REG(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_USE_HOLD_REG_SHIFT)) & SDIF_CMD_USE_HOLD_REG_MASK)
#define SDIF_CMD_START_CMD_MASK                  (0x80000000U)
#define SDIF_CMD_START_CMD_SHIFT                 (31U)
#define SDIF_CMD_START_CMD(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_START_CMD_SHIFT)) & SDIF_CMD_START_CMD_MASK)
/*! @} */

/*! @name RESP - Response register */
/*! @{ */
#define SDIF_RESP_RESPONSE_MASK                  (0xFFFFFFFFU)
#define SDIF_RESP_RESPONSE_SHIFT                 (0U)
#define SDIF_RESP_RESPONSE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_RESP_RESPONSE_SHIFT)) & SDIF_RESP_RESPONSE_MASK)
/*! @} */

/* The count of SDIF_RESP */
#define SDIF_RESP_COUNT                          (4U)

/*! @name MINTSTS - Masked Interrupt Status register */
/*! @{ */
#define SDIF_MINTSTS_CDET_MASK                   (0x1U)
#define SDIF_MINTSTS_CDET_SHIFT                  (0U)
#define SDIF_MINTSTS_CDET(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_CDET_SHIFT)) & SDIF_MINTSTS_CDET_MASK)
#define SDIF_MINTSTS_RE_MASK                     (0x2U)
#define SDIF_MINTSTS_RE_SHIFT                    (1U)
#define SDIF_MINTSTS_RE(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RE_SHIFT)) & SDIF_MINTSTS_RE_MASK)
#define SDIF_MINTSTS_CDONE_MASK                  (0x4U)
#define SDIF_MINTSTS_CDONE_SHIFT                 (2U)
#define SDIF_MINTSTS_CDONE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_CDONE_SHIFT)) & SDIF_MINTSTS_CDONE_MASK)
#define SDIF_MINTSTS_DTO_MASK                    (0x8U)
#define SDIF_MINTSTS_DTO_SHIFT                   (3U)
#define SDIF_MINTSTS_DTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_DTO_SHIFT)) & SDIF_MINTSTS_DTO_MASK)
#define SDIF_MINTSTS_TXDR_MASK                   (0x10U)
#define SDIF_MINTSTS_TXDR_SHIFT                  (4U)
#define SDIF_MINTSTS_TXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_TXDR_SHIFT)) & SDIF_MINTSTS_TXDR_MASK)
#define SDIF_MINTSTS_RXDR_MASK                   (0x20U)
#define SDIF_MINTSTS_RXDR_SHIFT                  (5U)
#define SDIF_MINTSTS_RXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RXDR_SHIFT)) & SDIF_MINTSTS_RXDR_MASK)
#define SDIF_MINTSTS_RCRC_MASK                   (0x40U)
#define SDIF_MINTSTS_RCRC_SHIFT                  (6U)
#define SDIF_MINTSTS_RCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RCRC_SHIFT)) & SDIF_MINTSTS_RCRC_MASK)
#define SDIF_MINTSTS_DCRC_MASK                   (0x80U)
#define SDIF_MINTSTS_DCRC_SHIFT                  (7U)
#define SDIF_MINTSTS_DCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_DCRC_SHIFT)) & SDIF_MINTSTS_DCRC_MASK)
#define SDIF_MINTSTS_RTO_MASK                    (0x100U)
#define SDIF_MINTSTS_RTO_SHIFT                   (8U)
#define SDIF_MINTSTS_RTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RTO_SHIFT)) & SDIF_MINTSTS_RTO_MASK)
#define SDIF_MINTSTS_DRTO_MASK                   (0x200U)
#define SDIF_MINTSTS_DRTO_SHIFT                  (9U)
#define SDIF_MINTSTS_DRTO(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_DRTO_SHIFT)) & SDIF_MINTSTS_DRTO_MASK)
#define SDIF_MINTSTS_HTO_MASK                    (0x400U)
#define SDIF_MINTSTS_HTO_SHIFT                   (10U)
#define SDIF_MINTSTS_HTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_HTO_SHIFT)) & SDIF_MINTSTS_HTO_MASK)
#define SDIF_MINTSTS_FRUN_MASK                   (0x800U)
#define SDIF_MINTSTS_FRUN_SHIFT                  (11U)
#define SDIF_MINTSTS_FRUN(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_FRUN_SHIFT)) & SDIF_MINTSTS_FRUN_MASK)
#define SDIF_MINTSTS_HLE_MASK                    (0x1000U)
#define SDIF_MINTSTS_HLE_SHIFT                   (12U)
#define SDIF_MINTSTS_HLE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_HLE_SHIFT)) & SDIF_MINTSTS_HLE_MASK)
#define SDIF_MINTSTS_SBE_MASK                    (0x2000U)
#define SDIF_MINTSTS_SBE_SHIFT                   (13U)
#define SDIF_MINTSTS_SBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_SBE_SHIFT)) & SDIF_MINTSTS_SBE_MASK)
#define SDIF_MINTSTS_ACD_MASK                    (0x4000U)
#define SDIF_MINTSTS_ACD_SHIFT                   (14U)
#define SDIF_MINTSTS_ACD(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_ACD_SHIFT)) & SDIF_MINTSTS_ACD_MASK)
#define SDIF_MINTSTS_EBE_MASK                    (0x8000U)
#define SDIF_MINTSTS_EBE_SHIFT                   (15U)
#define SDIF_MINTSTS_EBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_EBE_SHIFT)) & SDIF_MINTSTS_EBE_MASK)
#define SDIF_MINTSTS_SDIO_INTERRUPT_MASK         (0x10000U)
#define SDIF_MINTSTS_SDIO_INTERRUPT_SHIFT        (16U)
#define SDIF_MINTSTS_SDIO_INTERRUPT(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_SDIO_INTERRUPT_SHIFT)) & SDIF_MINTSTS_SDIO_INTERRUPT_MASK)
/*! @} */

/*! @name RINTSTS - Raw Interrupt Status register */
/*! @{ */
#define SDIF_RINTSTS_CDET_MASK                   (0x1U)
#define SDIF_RINTSTS_CDET_SHIFT                  (0U)
#define SDIF_RINTSTS_CDET(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_CDET_SHIFT)) & SDIF_RINTSTS_CDET_MASK)
#define SDIF_RINTSTS_RE_MASK                     (0x2U)
#define SDIF_RINTSTS_RE_SHIFT                    (1U)
#define SDIF_RINTSTS_RE(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RE_SHIFT)) & SDIF_RINTSTS_RE_MASK)
#define SDIF_RINTSTS_CDONE_MASK                  (0x4U)
#define SDIF_RINTSTS_CDONE_SHIFT                 (2U)
#define SDIF_RINTSTS_CDONE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_CDONE_SHIFT)) & SDIF_RINTSTS_CDONE_MASK)
#define SDIF_RINTSTS_DTO_MASK                    (0x8U)
#define SDIF_RINTSTS_DTO_SHIFT                   (3U)
#define SDIF_RINTSTS_DTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_DTO_SHIFT)) & SDIF_RINTSTS_DTO_MASK)
#define SDIF_RINTSTS_TXDR_MASK                   (0x10U)
#define SDIF_RINTSTS_TXDR_SHIFT                  (4U)
#define SDIF_RINTSTS_TXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_TXDR_SHIFT)) & SDIF_RINTSTS_TXDR_MASK)
#define SDIF_RINTSTS_RXDR_MASK                   (0x20U)
#define SDIF_RINTSTS_RXDR_SHIFT                  (5U)
#define SDIF_RINTSTS_RXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RXDR_SHIFT)) & SDIF_RINTSTS_RXDR_MASK)
#define SDIF_RINTSTS_RCRC_MASK                   (0x40U)
#define SDIF_RINTSTS_RCRC_SHIFT                  (6U)
#define SDIF_RINTSTS_RCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RCRC_SHIFT)) & SDIF_RINTSTS_RCRC_MASK)
#define SDIF_RINTSTS_DCRC_MASK                   (0x80U)
#define SDIF_RINTSTS_DCRC_SHIFT                  (7U)
#define SDIF_RINTSTS_DCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_DCRC_SHIFT)) & SDIF_RINTSTS_DCRC_MASK)
#define SDIF_RINTSTS_RTO_BAR_MASK                (0x100U)
#define SDIF_RINTSTS_RTO_BAR_SHIFT               (8U)
#define SDIF_RINTSTS_RTO_BAR(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RTO_BAR_SHIFT)) & SDIF_RINTSTS_RTO_BAR_MASK)
#define SDIF_RINTSTS_DRTO_BDS_MASK               (0x200U)
#define SDIF_RINTSTS_DRTO_BDS_SHIFT              (9U)
#define SDIF_RINTSTS_DRTO_BDS(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_DRTO_BDS_SHIFT)) & SDIF_RINTSTS_DRTO_BDS_MASK)
#define SDIF_RINTSTS_HTO_MASK                    (0x400U)
#define SDIF_RINTSTS_HTO_SHIFT                   (10U)
#define SDIF_RINTSTS_HTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_HTO_SHIFT)) & SDIF_RINTSTS_HTO_MASK)
#define SDIF_RINTSTS_FRUN_MASK                   (0x800U)
#define SDIF_RINTSTS_FRUN_SHIFT                  (11U)
#define SDIF_RINTSTS_FRUN(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_FRUN_SHIFT)) & SDIF_RINTSTS_FRUN_MASK)
#define SDIF_RINTSTS_HLE_MASK                    (0x1000U)
#define SDIF_RINTSTS_HLE_SHIFT                   (12U)
#define SDIF_RINTSTS_HLE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_HLE_SHIFT)) & SDIF_RINTSTS_HLE_MASK)
#define SDIF_RINTSTS_SBE_MASK                    (0x2000U)
#define SDIF_RINTSTS_SBE_SHIFT                   (13U)
#define SDIF_RINTSTS_SBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_SBE_SHIFT)) & SDIF_RINTSTS_SBE_MASK)
#define SDIF_RINTSTS_ACD_MASK                    (0x4000U)
#define SDIF_RINTSTS_ACD_SHIFT                   (14U)
#define SDIF_RINTSTS_ACD(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_ACD_SHIFT)) & SDIF_RINTSTS_ACD_MASK)
#define SDIF_RINTSTS_EBE_MASK                    (0x8000U)
#define SDIF_RINTSTS_EBE_SHIFT                   (15U)
#define SDIF_RINTSTS_EBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_EBE_SHIFT)) & SDIF_RINTSTS_EBE_MASK)
#define SDIF_RINTSTS_SDIO_INTERRUPT_MASK         (0x10000U)
#define SDIF_RINTSTS_SDIO_INTERRUPT_SHIFT        (16U)
#define SDIF_RINTSTS_SDIO_INTERRUPT(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_SDIO_INTERRUPT_SHIFT)) & SDIF_RINTSTS_SDIO_INTERRUPT_MASK)
/*! @} */

/*! @name STATUS - Status register */
/*! @{ */
#define SDIF_STATUS_FIFO_RX_WATERMARK_MASK       (0x1U)
#define SDIF_STATUS_FIFO_RX_WATERMARK_SHIFT      (0U)
#define SDIF_STATUS_FIFO_RX_WATERMARK(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_RX_WATERMARK_SHIFT)) & SDIF_STATUS_FIFO_RX_WATERMARK_MASK)
#define SDIF_STATUS_FIFO_TX_WATERMARK_MASK       (0x2U)
#define SDIF_STATUS_FIFO_TX_WATERMARK_SHIFT      (1U)
#define SDIF_STATUS_FIFO_TX_WATERMARK(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_TX_WATERMARK_SHIFT)) & SDIF_STATUS_FIFO_TX_WATERMARK_MASK)
#define SDIF_STATUS_FIFO_EMPTY_MASK              (0x4U)
#define SDIF_STATUS_FIFO_EMPTY_SHIFT             (2U)
#define SDIF_STATUS_FIFO_EMPTY(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_EMPTY_SHIFT)) & SDIF_STATUS_FIFO_EMPTY_MASK)
#define SDIF_STATUS_FIFO_FULL_MASK               (0x8U)
#define SDIF_STATUS_FIFO_FULL_SHIFT              (3U)
#define SDIF_STATUS_FIFO_FULL(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_FULL_SHIFT)) & SDIF_STATUS_FIFO_FULL_MASK)
#define SDIF_STATUS_CMDFSMSTATES_MASK            (0xF0U)
#define SDIF_STATUS_CMDFSMSTATES_SHIFT           (4U)
#define SDIF_STATUS_CMDFSMSTATES(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_CMDFSMSTATES_SHIFT)) & SDIF_STATUS_CMDFSMSTATES_MASK)
#define SDIF_STATUS_DATA_3_STATUS_MASK           (0x100U)
#define SDIF_STATUS_DATA_3_STATUS_SHIFT          (8U)
#define SDIF_STATUS_DATA_3_STATUS(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DATA_3_STATUS_SHIFT)) & SDIF_STATUS_DATA_3_STATUS_MASK)
#define SDIF_STATUS_DATA_BUSY_MASK               (0x200U)
#define SDIF_STATUS_DATA_BUSY_SHIFT              (9U)
#define SDIF_STATUS_DATA_BUSY(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DATA_BUSY_SHIFT)) & SDIF_STATUS_DATA_BUSY_MASK)
#define SDIF_STATUS_DATA_STATE_MC_BUSY_MASK      (0x400U)
#define SDIF_STATUS_DATA_STATE_MC_BUSY_SHIFT     (10U)
#define SDIF_STATUS_DATA_STATE_MC_BUSY(x)        (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DATA_STATE_MC_BUSY_SHIFT)) & SDIF_STATUS_DATA_STATE_MC_BUSY_MASK)
#define SDIF_STATUS_RESPONSE_INDEX_MASK          (0x1F800U)
#define SDIF_STATUS_RESPONSE_INDEX_SHIFT         (11U)
#define SDIF_STATUS_RESPONSE_INDEX(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_RESPONSE_INDEX_SHIFT)) & SDIF_STATUS_RESPONSE_INDEX_MASK)
#define SDIF_STATUS_FIFO_COUNT_MASK              (0x3FFE0000U)
#define SDIF_STATUS_FIFO_COUNT_SHIFT             (17U)
#define SDIF_STATUS_FIFO_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_COUNT_SHIFT)) & SDIF_STATUS_FIFO_COUNT_MASK)
#define SDIF_STATUS_DMA_ACK_MASK                 (0x40000000U)
#define SDIF_STATUS_DMA_ACK_SHIFT                (30U)
#define SDIF_STATUS_DMA_ACK(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DMA_ACK_SHIFT)) & SDIF_STATUS_DMA_ACK_MASK)
#define SDIF_STATUS_DMA_REQ_MASK                 (0x80000000U)
#define SDIF_STATUS_DMA_REQ_SHIFT                (31U)
#define SDIF_STATUS_DMA_REQ(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DMA_REQ_SHIFT)) & SDIF_STATUS_DMA_REQ_MASK)
/*! @} */

/*! @name FIFOTH - FIFO Threshold Watermark register */
/*! @{ */
#define SDIF_FIFOTH_TX_WMARK_MASK                (0xFFFU)
#define SDIF_FIFOTH_TX_WMARK_SHIFT               (0U)
#define SDIF_FIFOTH_TX_WMARK(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_FIFOTH_TX_WMARK_SHIFT)) & SDIF_FIFOTH_TX_WMARK_MASK)
#define SDIF_FIFOTH_RX_WMARK_MASK                (0xFFF0000U)
#define SDIF_FIFOTH_RX_WMARK_SHIFT               (16U)
#define SDIF_FIFOTH_RX_WMARK(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_FIFOTH_RX_WMARK_SHIFT)) & SDIF_FIFOTH_RX_WMARK_MASK)
#define SDIF_FIFOTH_DMA_MTS_MASK                 (0x70000000U)
#define SDIF_FIFOTH_DMA_MTS_SHIFT                (28U)
#define SDIF_FIFOTH_DMA_MTS(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_FIFOTH_DMA_MTS_SHIFT)) & SDIF_FIFOTH_DMA_MTS_MASK)
/*! @} */

/*! @name CDETECT - Card Detect register */
/*! @{ */
#define SDIF_CDETECT_CARD_DETECT_MASK            (0x200U)
#define SDIF_CDETECT_CARD_DETECT_SHIFT           (0U)
#define SDIF_CDETECT_CARD_DETECT(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CDETECT_CARD_DETECT_SHIFT)) & SDIF_CDETECT_CARD_DETECT_MASK)
/*! @} */

/*! @name WRTPRT - Write Protect register */
/*! @{ */
#define SDIF_WRTPRT_WRITE_PROTECT_MASK           (0x1U)
#define SDIF_WRTPRT_WRITE_PROTECT_SHIFT          (0U)
#define SDIF_WRTPRT_WRITE_PROTECT(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_WRTPRT_WRITE_PROTECT_SHIFT)) & SDIF_WRTPRT_WRITE_PROTECT_MASK)
/*! @} */

/*! @name TCBCNT - Transferred CIU Card Byte Count register */
/*! @{ */
#define SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_MASK   (0xFFFFFFFFU)
#define SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_SHIFT  (0U)
#define SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT(x)     (((uint32_t)(((uint32_t)(x)) << SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_SHIFT)) & SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_MASK)
/*! @} */

/*! @name TBBCNT - Transferred Host to BIU-FIFO Byte Count register */
/*! @{ */
#define SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_MASK   (0xFFFFFFFFU)
#define SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_SHIFT  (0U)
#define SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT(x)     (((uint32_t)(((uint32_t)(x)) << SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_SHIFT)) & SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_MASK)
/*! @} */

/*! @name DEBNCE - Debounce Count register */
/*! @{ */
#define SDIF_DEBNCE_DEBOUNCE_COUNT_MASK          (0xFFFFFFU)
#define SDIF_DEBNCE_DEBOUNCE_COUNT_SHIFT         (0U)
#define SDIF_DEBNCE_DEBOUNCE_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_DEBNCE_DEBOUNCE_COUNT_SHIFT)) & SDIF_DEBNCE_DEBOUNCE_COUNT_MASK)
/*! @} */

/*! @name RST_N - Hardware Reset */
/*! @{ */
#define SDIF_RST_N_CARD_RESET_MASK               (0x1U)
#define SDIF_RST_N_CARD_RESET_SHIFT              (0U)
#define SDIF_RST_N_CARD_RESET(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_RST_N_CARD_RESET_SHIFT)) & SDIF_RST_N_CARD_RESET_MASK)
/*! @} */

/*! @name BMOD - Bus Mode register */
/*! @{ */
#define SDIF_BMOD_SWR_MASK                       (0x1U)
#define SDIF_BMOD_SWR_SHIFT                      (0U)
#define SDIF_BMOD_SWR(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_SWR_SHIFT)) & SDIF_BMOD_SWR_MASK)
#define SDIF_BMOD_FB_MASK                        (0x2U)
#define SDIF_BMOD_FB_SHIFT                       (1U)
#define SDIF_BMOD_FB(x)                          (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_FB_SHIFT)) & SDIF_BMOD_FB_MASK)
#define SDIF_BMOD_DSL_MASK                       (0x7CU)
#define SDIF_BMOD_DSL_SHIFT                      (2U)
#define SDIF_BMOD_DSL(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_DSL_SHIFT)) & SDIF_BMOD_DSL_MASK)
#define SDIF_BMOD_DE_MASK                        (0x80U)
#define SDIF_BMOD_DE_SHIFT                       (7U)
#define SDIF_BMOD_DE(x)                          (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_DE_SHIFT)) & SDIF_BMOD_DE_MASK)
#define SDIF_BMOD_PBL_MASK                       (0x700U)
#define SDIF_BMOD_PBL_SHIFT                      (8U)
#define SDIF_BMOD_PBL(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_PBL_SHIFT)) & SDIF_BMOD_PBL_MASK)
/*! @} */

/*! @name PLDMND - Poll Demand register */
/*! @{ */
#define SDIF_PLDMND_PD_MASK                      (0xFFFFFFFFU)
#define SDIF_PLDMND_PD_SHIFT                     (0U)
#define SDIF_PLDMND_PD(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_PLDMND_PD_SHIFT)) & SDIF_PLDMND_PD_MASK)
/*! @} */

/*! @name DBADDR - Descriptor List Base Address register */
/*! @{ */
#define SDIF_DBADDR_SDL_MASK                     (0xFFFFFFFFU)
#define SDIF_DBADDR_SDL_SHIFT                    (0U)
#define SDIF_DBADDR_SDL(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_DBADDR_SDL_SHIFT)) & SDIF_DBADDR_SDL_MASK)
/*! @} */

/*! @name IDSTS - Internal DMAC Status register */
/*! @{ */
#define SDIF_IDSTS_TI_MASK                       (0x1U)
#define SDIF_IDSTS_TI_SHIFT                      (0U)
#define SDIF_IDSTS_TI(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_TI_SHIFT)) & SDIF_IDSTS_TI_MASK)
#define SDIF_IDSTS_RI_MASK                       (0x2U)
#define SDIF_IDSTS_RI_SHIFT                      (1U)
#define SDIF_IDSTS_RI(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_RI_SHIFT)) & SDIF_IDSTS_RI_MASK)
#define SDIF_IDSTS_FBE_MASK                      (0x4U)
#define SDIF_IDSTS_FBE_SHIFT                     (2U)
#define SDIF_IDSTS_FBE(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_FBE_SHIFT)) & SDIF_IDSTS_FBE_MASK)
#define SDIF_IDSTS_DU_MASK                       (0x10U)
#define SDIF_IDSTS_DU_SHIFT                      (4U)
#define SDIF_IDSTS_DU(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_DU_SHIFT)) & SDIF_IDSTS_DU_MASK)
#define SDIF_IDSTS_CES_MASK                      (0x20U)
#define SDIF_IDSTS_CES_SHIFT                     (5U)
#define SDIF_IDSTS_CES(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_CES_SHIFT)) & SDIF_IDSTS_CES_MASK)
#define SDIF_IDSTS_NIS_MASK                      (0x100U)
#define SDIF_IDSTS_NIS_SHIFT                     (8U)
#define SDIF_IDSTS_NIS(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_NIS_SHIFT)) & SDIF_IDSTS_NIS_MASK)
#define SDIF_IDSTS_AIS_MASK                      (0x200U)
#define SDIF_IDSTS_AIS_SHIFT                     (9U)
#define SDIF_IDSTS_AIS(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_AIS_SHIFT)) & SDIF_IDSTS_AIS_MASK)
#define SDIF_IDSTS_EB_MASK                       (0x1C00U)
#define SDIF_IDSTS_EB_SHIFT                      (10U)
#define SDIF_IDSTS_EB(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_EB_SHIFT)) & SDIF_IDSTS_EB_MASK)
#define SDIF_IDSTS_FSM_MASK                      (0x1E000U)
#define SDIF_IDSTS_FSM_SHIFT                     (13U)
#define SDIF_IDSTS_FSM(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_FSM_SHIFT)) & SDIF_IDSTS_FSM_MASK)
/*! @} */

/*! @name IDINTEN - Internal DMAC Interrupt Enable register */
/*! @{ */
#define SDIF_IDINTEN_TI_MASK                     (0x1U)
#define SDIF_IDINTEN_TI_SHIFT                    (0U)
#define SDIF_IDINTEN_TI(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_TI_SHIFT)) & SDIF_IDINTEN_TI_MASK)
#define SDIF_IDINTEN_RI_MASK                     (0x2U)
#define SDIF_IDINTEN_RI_SHIFT                    (1U)
#define SDIF_IDINTEN_RI(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_RI_SHIFT)) & SDIF_IDINTEN_RI_MASK)
#define SDIF_IDINTEN_FBE_MASK                    (0x4U)
#define SDIF_IDINTEN_FBE_SHIFT                   (2U)
#define SDIF_IDINTEN_FBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_FBE_SHIFT)) & SDIF_IDINTEN_FBE_MASK)
#define SDIF_IDINTEN_DU_MASK                     (0x10U)
#define SDIF_IDINTEN_DU_SHIFT                    (4U)
#define SDIF_IDINTEN_DU(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_DU_SHIFT)) & SDIF_IDINTEN_DU_MASK)
#define SDIF_IDINTEN_CES_MASK                    (0x20U)
#define SDIF_IDINTEN_CES_SHIFT                   (5U)
#define SDIF_IDINTEN_CES(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_CES_SHIFT)) & SDIF_IDINTEN_CES_MASK)
#define SDIF_IDINTEN_NIS_MASK                    (0x100U)
#define SDIF_IDINTEN_NIS_SHIFT                   (8U)
#define SDIF_IDINTEN_NIS(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_NIS_SHIFT)) & SDIF_IDINTEN_NIS_MASK)
#define SDIF_IDINTEN_AIS_MASK                    (0x200U)
#define SDIF_IDINTEN_AIS_SHIFT                   (9U)
#define SDIF_IDINTEN_AIS(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_AIS_SHIFT)) & SDIF_IDINTEN_AIS_MASK)
/*! @} */

/*! @name DSCADDR - Current Host Descriptor Address register */
/*! @{ */
#define SDIF_DSCADDR_HDA_MASK                    (0xFFFFFFFFU)
#define SDIF_DSCADDR_HDA_SHIFT                   (0U)
#define SDIF_DSCADDR_HDA(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_DSCADDR_HDA_SHIFT)) & SDIF_DSCADDR_HDA_MASK)
/*! @} */

/*! @name BUFADDR - Current Buffer Descriptor Address register */
/*! @{ */
#define SDIF_BUFADDR_HBA_MASK                    (0xFFFFFFFFU)
#define SDIF_BUFADDR_HBA_SHIFT                   (0U)
#define SDIF_BUFADDR_HBA(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_BUFADDR_HBA_SHIFT)) & SDIF_BUFADDR_HBA_MASK)
/*! @} */

/*! @name UHS_REG_EXT - UHS register */
/*! @{ */
#define SDIF_UHS_REG_EXT_MMC_VOLT_MASK           (0xFFFFU)
#define SDIF_UHS_REG_EXT_MMC_VOLT_SHIFT          (0U)
#define SDIF_UHS_REG_EXT_MMC_VOLT(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_UHS_REG_EXT_MMC_VOLT_SHIFT)) & SDIF_UHS_REG_EXT_MMC_VOLT_MASK)
#define SDIF_UHS_REG_EXT_CLK_SMPL_PHASE_MASK     (0x30000U)
#define SDIF_UHS_REG_EXT_CLK_SMPL_PHASE_SHIFT    (16U)
#define SDIF_UHS_REG_EXT_CLK_SMPL_PHASE(x)       (((uint32_t)(((uint32_t)(x)) << SDIF_UHS_REG_EXT_CLK_SMPL_PHASE_SHIFT)) & SDIF_UHS_REG_EXT_CLK_SMPL_PHASE_MASK)
#define SDIF_UHS_REG_EXT_CLK_SMPL_DLY_MASK       (0x700000U)
#define SDIF_UHS_REG_EXT_CLK_SMPL_DLY_SHIFT      (20U)
#define SDIF_UHS_REG_EXT_CLK_SMPL_DLY(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_UHS_REG_EXT_CLK_SMPL_DLY_SHIFT)) & SDIF_UHS_REG_EXT_CLK_SMPL_DLY_MASK)
#define SDIF_UHS_REG_EXT_CLK_DRV_PHASE_MASK      (0x1800000U)
#define SDIF_UHS_REG_EXT_CLK_DRV_PHASE_SHIFT     (23U)
#define SDIF_UHS_REG_EXT_CLK_DRV_PHASE(x)        (((uint32_t)(((uint32_t)(x)) << SDIF_UHS_REG_EXT_CLK_DRV_PHASE_SHIFT)) & SDIF_UHS_REG_EXT_CLK_DRV_PHASE_MASK)
#define SDIF_UHS_REG_EXT_CLK_DRV_DLY_MASK        (0x38000000U)
#define SDIF_UHS_REG_EXT_CLK_DRV_DLY_SHIFT       (27U)
#define SDIF_UHS_REG_EXT_CLK_DRV_DLY(x)          (((uint32_t)(((uint32_t)(x)) << SDIF_UHS_REG_EXT_CLK_DRV_DLY_SHIFT)) & SDIF_UHS_REG_EXT_CLK_DRV_DLY_MASK)
#define SDIF_UHS_REG_EXT_EXT_CLK_MUX_MASK        (0xC0000000U)
#define SDIF_UHS_REG_EXT_EXT_CLK_MUX_SHIFT       (30U)
#define SDIF_UHS_REG_EXT_EXT_CLK_MUX(x)          (((uint32_t)(((uint32_t)(x)) << SDIF_UHS_REG_EXT_EXT_CLK_MUX_SHIFT)) & SDIF_UHS_REG_EXT_EXT_CLK_MUX_MASK)
/*! @} */

/*! @name CARDTHRCTL - Card Threshold Control */
/*! @{ */
#define SDIF_CARDTHRCTL_CARDRDTHREN_MASK         (0x1U)
#define SDIF_CARDTHRCTL_CARDRDTHREN_SHIFT        (0U)
#define SDIF_CARDTHRCTL_CARDRDTHREN(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CARDTHRCTL_CARDRDTHREN_SHIFT)) & SDIF_CARDTHRCTL_CARDRDTHREN_MASK)
#define SDIF_CARDTHRCTL_BSYCLRINTEN_MASK         (0x2U)
#define SDIF_CARDTHRCTL_BSYCLRINTEN_SHIFT        (1U)
#define SDIF_CARDTHRCTL_BSYCLRINTEN(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CARDTHRCTL_BSYCLRINTEN_SHIFT)) & SDIF_CARDTHRCTL_BSYCLRINTEN_MASK)
#define SDIF_CARDTHRCTL_CARDTHRESHOLD_MASK       (0xFF0000U)
#define SDIF_CARDTHRCTL_CARDTHRESHOLD_SHIFT      (16U)
#define SDIF_CARDTHRCTL_CARDTHRESHOLD(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_CARDTHRCTL_CARDTHRESHOLD_SHIFT)) & SDIF_CARDTHRCTL_CARDTHRESHOLD_MASK)
/*! @} */

/*! @name BACKENDPWR - Power control */
/*! @{ */
#define SDIF_BACKENDPWR_BACKENDPWR_MASK          (0x1U)
#define SDIF_BACKENDPWR_BACKENDPWR_SHIFT         (0U)
#define SDIF_BACKENDPWR_BACKENDPWR(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_BACKENDPWR_BACKENDPWR_SHIFT)) & SDIF_BACKENDPWR_BACKENDPWR_MASK)
/*! @} */

/*! @name FIFO - SDIF FIFO */
/*! @{ */
#define SDIF_FIFO_DATA_MASK                      (0xFFFFFFFFU)
#define SDIF_FIFO_DATA_SHIFT                     (0U)
#define SDIF_FIFO_DATA(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_FIFO_DATA_SHIFT)) & SDIF_FIFO_DATA_MASK)
/*! @} */

/* The count of SDIF_FIFO */
#define SDIF_FIFO_COUNT                          (32U)


/*!
 * @}
 */ /* end of group SDIF_Register_Masks */


/*!
 * @}
 */ /* end of group SDIF_Peripheral_Access_Layer */

#ifdef __cplusplus
}
#endif

#endif
