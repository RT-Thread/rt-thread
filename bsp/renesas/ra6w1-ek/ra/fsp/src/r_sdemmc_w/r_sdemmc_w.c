/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "r_sdemmc_w.h"
#include "r_sdemmc_w_private.h"
#include "r_sdemmc_w_cfg.h"

#if (CFG_PMGR == 1) && (SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE == 1)
 #include "rm_pmgr_w_instance.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "SDHI" in ASCII, used to determine if channel is open. */
#define SDEMMC_W_PRV_OPEN                 (0x53444849U)
#define SDEMMC_W_PRV_SLEEP                (0xAAAAAAAAU)

/* Create a bitmask of access errors. */
/* Command error */
#define SDEMMC_W_PRV_CARD_CMD_ERR         (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CommandIndexError_Msk)

/* CRC error */
#define SDEMMC_W_PRV_CARD_CRC_ERR         (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CommandCRCError_Msk)

/* End bit error */
#define SDEMMC_W_PRV_CARD_END_ERR         (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CommandEndBitError_Msk)

/* Data Timeout */
#define SDEMMC_W_PRV_CARD_DTO             (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_DataTimeoutError_Msk)

/* Error Interrupt */
#define SDEMMC_W_PRV_CARD_ERR_INT         (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_ErrorInterrupt_Msk)

/* Timeout */
#define SDEMMC_W_PRV_CARD_CTO             (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CommandTimeoutError_Msk)

/* Data CRC error */
#define SDEMMC_W_PRV_CARD_D_CRC_ERR       (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_DataCRCError_Msk)

/* Data End bit error */
#define SDEMMC_W_PRV_CARD_D_END_ERR       (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_DataEndBitError_Msk)

/* Current Limit error */
#define SDEMMC_W_PRV_CARD_CUR_LMT         (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CurrentLimitError_Msk)

/* Auto Command error */
#define SDEMMC_W_PRV_CARD_AUTO_ERR        (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_AutoCMDError_Msk)

/* ADMA error */
#define SDEMMC_W_PRV_CARD_ADMA_ERR        (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_ADMAError_Msk)

/* Tuning error */
#define SDEMMC_W_PRV_CARD_TUNE_ERR        (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_TuningError_Msk)

#define SDEMMC_W_PRV_ACCESS_ERROR_MASK    (SDEMMC_W_PRV_CARD_CMD_ERR | SDEMMC_W_PRV_CARD_CRC_ERR |     \
                                           SDEMMC_W_PRV_CARD_END_ERR | SDEMMC_W_PRV_CARD_DTO |         \
                                           SDEMMC_W_PRV_CARD_ERR_INT | SDEMMC_W_PRV_CARD_CTO |         \
                                           SDEMMC_W_PRV_CARD_D_CRC_ERR | SDEMMC_W_PRV_CARD_D_END_ERR | \
                                           SDEMMC_W_PRV_CARD_CUR_LMT | SDEMMC_W_PRV_CARD_AUTO_ERR |    \
                                           SDEMMC_W_PRV_CARD_ADMA_ERR | SDEMMC_W_PRV_CARD_TUNE_ERR)

/* The clock register can be accessed 8 SD clock cycles after the last command completes. */

/* SDEMMC_NORMAL_ITNR_STATUS_REG */
/* Response End */
#define SDEMMC_W_PRV_SDHI_INFO1_RESPONSE_END           (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CommandComplete_Msk)

/* Access End */
#define SDEMMC_W_PRV_SDHI_INFO1_ACCESS_END             (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_TransferComplete_Msk)

/* Card Removed */
#define SDEMMC_W_PRV_SDHI_INFO1_CARD_REMOVED           (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CardRemoval_Msk)

/* Card Inserted */
#define SDEMMC_W_PRV_SDHI_INFO1_CARD_INSERTED          (SDEMMC_SDEMMC_NORMAL_ITNR_STATUS_REG_CardInsertion_Msk)

#define SDEMMC_W_PRV_SDHI_INFO1_ACCESS_MASK            ((SDEMMC_W_PRV_SDHI_INFO1_RESPONSE_END | \
                                                         SDEMMC_W_PRV_SDHI_INFO1_ACCESS_END))
#define SDEMMC_W_PRV_SDHI_INFO1_CARD_MASK              ((SDEMMC_W_PRV_SDHI_INFO1_CARD_REMOVED | \
                                                         SDEMMC_W_PRV_SDHI_INFO1_CARD_INSERTED))

/* The relationship of the SD Clock Control Register SDCLKFrequencySelect to the division of the source PERI_CLK
 * div 0   -> 40Mhz             == 40Mhz
 * div 1   -> 40Mhz / (1 * 2)   == 20Mhz
 * div 2   -> 40Mhz / (2 * 2)   == 10Mhz
 * div 4   -> 40Mhz / (4 * 2)   == 5Mhz
 * div 8   -> 40Mhz / (8 * 2)   == 2.5Mhz
 * div 16  -> 40Mhz / (16 * 2)  == 1.25Mhz
 * div 32  -> 40Mhz / (32 * 2)  == 625k
 * div 64  -> 40Mhz / (64 * 2)  == 312.5k
 * div 128 -> 40Mhz / (128 * 2) == 156.25k
 * div 256 -> 40Mhz / (256 * 2) == 78.125k
 * Other settings are prohibited.
 */
#define SDEMMC_W_PRV_CLK_CTRL_DIV_INVALID              (0xFFU)

/* Delay up to 10 ms before timing out waiting for response or response timeout flag. */
#define SDEMMC_W_PRV_RESPONSE_TIMEOUT_US               (10000U)

/* Delay up to 5 seconds before timing out waiting for busy after updating bus width or high speed status for eMMC. */
#define SDEMMC_W_PRV_BUSY_TIMEOUT_US                   (5000000U)

/* Delay up to 500 ms before timing out waiting for data or data timeout flag. */
#define SDEMMC_W_PRV_DATA_TIMEOUT_US                   (500000U)

/* Delay up to 100 ms before timing out waiting for access end flag after receiving data during initialization. */
#define SDEMMC_W_PRV_ACCESS_TIMEOUT_US                 (100000U)

/* 400 kHz maximum clock required for initialization. */
#define SDEMMC_W_PRV_INIT_MAX_CLOCK_RATE_HZ            (400000U)
#define SDEMMC_W_PRV_BITS_PER_COMMAD                   (48U)
#define SDEMMC_W_PRV_BITS_PER_RESPONSE                 (48U)
#define SDEMMC_W_PRV_CLOCKS_BETWEEN_COMMANDS           (8U)
#define SDEMMC_W_PRV_MIN_CYCLES_PER_COMMAND_RESPONSE \
    ((SDEMMC_W_PRV_BITS_PER_COMMAD +                 \
      SDEMMC_W_PRV_BITS_PER_RESPONSE) +              \
     SDEMMC_W_PRV_CLOCKS_BETWEEN_COMMANDS)
#define SDEMMC_W_PRV_INIT_ONE_SECOND_TIMEOUT_ITERATIONS \
    (SDEMMC_W_PRV_INIT_MAX_CLOCK_RATE_HZ /              \
     SDEMMC_W_PRV_MIN_CYCLES_PER_COMMAND_RESPONSE)

/* CCCR function address */
#define SDEMMC_W_SDIO_CCCR_CCCR                        (0x00)
#define SDEMMC_W_SDIO_CCCR_IOEX                        (0x02)
#define SDEMMC_W_SDIO_CCCR_IORX                        (0x03)
#define SDEMMC_W_SDIO_CCCR_IOASX_RESET                 (0x06)
#define SDEMMC_W_SDIO_CCCR_BUS_INTERFACE_CONTROL       (0x07)
#define SDEMMC_W_SDIO_CCCR_BUS_WIDTH_MASK              (0x03)
#define SDEMMC_W_SDIO_CCCR_BUS_WIDTH_BIT_4BIT          (1U << 1)  /* Enable 4bit bit of SDIO bus interface control register */
#define SDEMMC_W_SDIO_CCCR_CAPS                        (0x08)
#define SDEMMC_W_SDIO_CCCR_POWER                       (0x12)
#define SDEMMC_W_SDIO_CCCR_SPEED                       (0x13)
#define SDEMMC_W_PRV_SDIO_REG_HIGH_SPEED               (0x13U)    /* SDIO High Speed register address */
#define SDEMMC_W_PRV_SDIO_REG_HIGH_SPEED_BIT_EHS       (1U << 1)  /* Enable high speed bit of SDIO high speed register */
#define SDEMMC_W_PRV_SDIO_REG_HIGH_SPEED_BIT_SHS       (1U << 0)  /* Support high speed bit of SDIO high speed register */
#define SDEMMC_W_PRV_CSD_REG_CCC_CLASS_10_BIT          (1U << 10) /* CCC_CLASS bit is set if the card supports high speed */

/* SDIO maximum bytes allows in writeIoExt() and readIoExt(). */
#define SDEMMC_W_PRV_SDIO_EXT_MAX_BYTES                (512U)

/* SDIO maximum blocks allows in writeIoExt() and readIoExt(). */
#define SDEMMC_W_PRV_SDIO_EXT_MAX_BLOCKS               (511U)

/* Masks for CMD53 argument. */
#define SDEMMC_W_PRV_SDIO_CMD52_CMD53_COUNT_MASK       (0x1FFU)
#define SDEMMC_W_PRV_SDIO_CMD52_CMD53_FUNCTION_MASK    (0x7U)
#define SDEMMC_W_PRV_SDIO_CMD52_CMD53_ADDRESS_MASK     (0x1FFFFU)

/* Device bus width is 1, 4 or 8 bits wide. */
#define SDEMMC_W_SDEMMC_DT_WIDTH_1BIT                  (0)
#define SDEMMC_W_SDEMMC_DT_WIDTH_4BIT                  (1)
#define SDEMMC_W_SDEMMC_DT_WIDTH_8BIT                  (2)

#define SDEMMC_W_PRV_SDIO_INFO1_IRQ_CLEAR              (0x00000000U)
#define SDEMMC_W_PRV_SDIO_INFO1_FN0_INT_TO_ARM_MASK    (0x00000001U)
#define SDEMMC_W_PRV_SDIO_INFO1_FN1_INT_TO_ARM_MASK    (0x00000002U)
#define SDEMMC_W_PRV_SDIO_INFO1_VALUE_GLB_INT_ENA      (0x3U)
#define SDEMMC_W_ATTRIBUTE                             (0x23)
#define SDEMMC_W_ATTRIBUTE_DUMMY_DESC                  (0x21)
#define SDEMMC_W_ATTRIBUTE_TRANS_ERROR                 (0x02)
#define SDEMMC_W_BLKSIZE_MASK                          (0xFFF)
#define SDEMMC_W_B_BLK_CNT_MASK                        (0x1FF)
#define SDEMMC_W_1BIT_MASK                             (0x01)
#define SDEMMC_W_2BIT_MASK                             (0x03)
#define SDEMMC_W_12BIT_MASK                            (0xFFF)
#define SDEMMC_W_MUL_BLK_SHIFT                         (12)
#define SDEMMC_W_FN_NO_SHIFT                           (28)
#define SDEMMC_W_VALUE_IO_ACC_MODE                     (0x7F)
#define SDEMMC_W_AHBSOFT_RST                           (0x1)
#define SDEMMC_W_VOLT_SWITCH_CMD                       (0x2)
#define SDEMMC_W_CARD_VOLT_ACCEPT                      (0x4)
#define SDEMMC_W_SD_CLK_LINE_SWCH                      (0x8)
#define SDEMMC_W_SD_CMD_LINE_SWCH                      (0x10)
#define SDEMMC_W_VALUE_SOFT_RST_AHB                    (0x1)

/* interrupt field */
#define SDEMMC_W_FN1_WR_OVR                            (0x1)
#define SDEMMC_W_FN1_RD_OVR                            (0x2)
#define SDEMMC_W_FN1_RD_ERROR                          (0x4)
#define SDEMMC_W_FN1_RST                               (0x8)
#define SDEMMC_W_FN1_MSG_RDY                           (0x10)
#define SDEMMC_W_FN1_ACK_TO_ARM                        (0x20)
#define SDEMMC_W_FN1_SDIO_RD_STRT                      (0x40)
#define SDEMMC_W_FN1_SDIO_WR_STRT                      (0x80)
#define SDEMMC_W_FN1_ADMA_END                          (0x100)
#define SDEMMC_W_FN1_SUSPEND                           (0x200)
#define SDEMMC_W_FN1_RESUME                            (0x400)
#define SDEMMC_W_FN1_ADMA_INT                          (0x800)
#define SDEMMC_W_FN1_ADMA_ERR                          (0x1000)
#define SDEMMC_W_FN1_READY                             (0x2000)
#define SDEMMC_W_PRV_BYTES_PER_KILOBYTE                (1024)
#define SDEMMC_W_PRV_SECTOR_COUNT_IN_EXT_CSD           (0xFFFU)
#define SDEMMC_W_PRV_SD_CLK_CTRL_DEFAULT               (200U)

#define SDEMMC_W_PRV_ACCESS_BIT                        (2U)
#define SDEMMC_W_PRV_RESPONSE_BIT                      (0U)

#define SDEMMC_W_PRV_CIS_NAME                          "CIS"
#define SDEMMC_W_PRV_CISTPL_FUNC_NAME                  "CISTPL_FUNCE"

#define SDEMMC_W_CIS0_AHB_ADDR                         (0x200afc00) /* Physical fixed address of CIS0 */
#define SDEMMC_W_CIS1_AHB_ADDR                         (0x200afd00) /* physical fixed address of CIS1 */

#define SDEMMC_W_CCCR_REV                              (0x2)
#define SDEMMC_W_SDIO_REV                              (0x3)
#define SDEMMC_W_SD_PHY_SPEC                           (0x2)
#define SDEMMC_W_SCSI                                  (0x1)
#define SDEMMC_W_SDC                                   (0x1)
#define SDEMMC_W_SMB                                   (0x1)
#define SDEMMC_W_SRW                                   (0x1)
#define SDEMMC_W_SBS                                   (0x1)
#define SDEMMC_W_S4MI                                  (0x1)
#define SDEMMC_W_LSC                                   (0x0)
#define SDEMMC_W_BLS                                   (0x0)
#define SDEMMC_W_SMPC                                  (0x1)
#define SDEMMC_W_SHS                                   (0x1)

#define SDEMMC_W_VALUE_OCR                             (0xFF8000)
#define SDEMMC_W_VALUE_GLB_INT_ENA                     (0x3)
#define SDEMMC_W_VALUE_AHB_FN0_INT_ENA                 (0xF)
#define SDEMMC_W_VALUE_AHB_FN1_INT_ENA                 (0x3fff) /* 0x3FFF 0x2000 func 1 enable interrupt */
#define SDEMMC_W_VALUE_FBR                             (0x2017)
#define SDEMMC_W_VALUE_IOR                             (0x1)
#define SDEMMC_W_VALUE_FUNRDY                          (0x1)
#define SDEMMC_W_VALUE_INT_COND                        (0x3)

#define SDEMMC_W_FN1_RD_DAT_RDY                        (0x1)

#define SDEMMC_W_SDIO_FBR_BLKSZ                        (0x10)

#define SDEMMC_W_DUMMY_DESC_LEN                        (0x4)

#define SDEMMC_W_R5_OUT_OF_RANGE                       (1 << 8)
#define SDEMMC_W_R5_FUNC_NO                            (1 << 9)
#define SDEMMC_W_R5_ERROR                              (1 << 11)

#define SDEMMC_W_SDIO_NO_RESPONSE                      (0)
#define SDEMMC_W_SDIO_R3_RESPONSE                      (2)
#define SDEMMC_W_SDIO_SHORT_RESPONSE                   (2) /* (48bits) */
#define SDEMMC_W_SDIO_LONG_RESPONSE                    (1) /* (136bits) */
#define SDEMMC_W_GET_CMD_RESP_TYPE(x)    ((SDEMMC_W_PRV_CMD_ALL_SEND_CID == x) ? SDEMMC_W_SDIO_LONG_RESPONSE :  \
                                          (SDEMMC_W_PRV_CMD_SEND_CSD == x) ? SDEMMC_W_SDIO_LONG_RESPONSE :      \
                                          (SDEMMC_W_PRV_CMD_SEND_CID == x) ? SDEMMC_W_SDIO_LONG_RESPONSE :      \
                                          (SDEMMC_W_PRV_CMD_SD_SEND_OP_COND == x) ? SDEMMC_W_SDIO_R3_RESPONSE : \
                                          (SDEMMC_W_PRV_CMD_IF_COND == x) ? SDEMMC_W_SDIO_SHORT_RESPONSE :      \
                                          (SDEMMC_W_PRV_CMD_APP_CMD == x) ? SDEMMC_W_SDIO_SHORT_RESPONSE :      \
                                          SDEMMC_W_SDIO_SHORT_RESPONSE)

#ifndef SDEMMC_W_NTOH32
 #define SDEMMC_W_NTOH32(x)              (((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >> 8) | \
                                          ((x & 0x0000ff00) << 8) | ((x & 0x000000ff) << 24))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if (CFG_PMGR == 1) && (SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE == 1)

/* SDEMMC sleep context required by PMGR */

typedef struct st_sdemmc_pmgr_state
{
    uint32_t SDIO_CCCR_REG;
    uint32_t SDIO_OCR_REG;
    uint32_t SDIO_GLB_INT_ENA_REG;
    uint32_t SDIO_AHB_FN0_INT_ENABLE_REG;
    uint32_t SDIO_AHB_FN0_INT_REG;
    uint32_t SDIO_AHB_FN1_INT_ENABLE_REG;
    uint32_t SDIO_AHB_FN1_INT_REG;
    uint32_t SDIO_FBR_REG;
    uint32_t SDIO_IOR_REG;
    uint32_t SDIO_GLB_INT_STS_REG;
    uint32_t SDIO_FUNRDY_REG;
    uint32_t GPIO_SDIO_MODE_REG;
} sdemmc_w_pmgr_state_t;

typedef struct st_sdemmc_w_pmgr_context
{
    pmgr_instance_info_t       pmgr_info;
    pmgr_callback_args_t       clbk_args;
    pmgr_w_notifier_extend_t   pmgr_notifier_ext;
    sdemmc_w_instance_ctrl_t * p_ctrl;
    sdemmc_w_pmgr_state_t      state;
} sdemmc_w_pmgr_context_t;
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_sdemmc_open_param_check(sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_cfg_t const * const p_cfg);

#endif
static fsp_err_t r_sdemmc_erase_error_check(sdemmc_w_instance_ctrl_t * const p_ctrl,
                                            uint32_t const                   start_sector,
                                            uint32_t const                   sector_count);

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE
static fsp_err_t r_sdemmc_csd_save(sdemmc_w_instance_ctrl_t * const p_ctrl,
                                   uint32_t                         rca,
                                   sdmmc_priv_csd_reg_t * const     p_csd_reg,
                                   uint32_t                         send_flag);
static void      r_sdemmc_write_protect_get(sdemmc_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t r_sdemmc_command_send(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument);
static fsp_err_t r_sdemmc_wait_for_event(sdemmc_w_instance_ctrl_t * const p_ctrl, uint32_t bit, uint32_t timeout);
static fsp_err_t r_sdemmc_wait_for_device(sdemmc_w_instance_ctrl_t * const p_ctrl);
static void      r_sdemmc_command_send_no_wait(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument);

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

static fsp_err_t r_sdemmc_common_error_check(sdemmc_w_instance_ctrl_t * const p_ctrl);

static void r_sdemmc_irq_enable(IRQn_Type irq, uint8_t priority, void * p_context);
static void r_sdemmc_irq_disable(IRQn_Type irq);

static void r_sdemmc_access_irq_process(sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args);

static void r_sdemmc_call_callback(sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args);

void sdhimmc_accs_isr(void);

void sdhimmc_sdio_isr(void);

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
static void r_sdemmc_handle_interrupt_fn0(sdemmc_w_instance_ctrl_t * p_ctrl);

static void r_sdemmc_handle_interrupt_fn1(sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args);

static void r_sdemmc_adma_dummy(sdemmc_w_instance_ctrl_t * p_ctrl);

static void r_sdemmc_host_read(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t length);

static void r_sdemmc_host_write(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t length);

#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

static void r_sdemmc_hw_sdemmc_renable_prepare(sdemmc_w_instance_ctrl_t * p_ctrl);
static void r_sdemmc_hw_sdemmc_renable(sdemmc_w_instance_ctrl_t * p_ctrl);

static void r_sdemmc_hw_sdemmc_enable(sdemmc_w_instance_ctrl_t * p_ctrl);

static void r_sdemmc_hw_sdemmc_disable(sdemmc_w_instance_ctrl_t * p_ctrl);

static void r_sdemmc_sdemmc_interrupt_enable(sdemmc_w_instance_ctrl_t * p_ctrl);

static fsp_err_t r_sdemmc_sdemmc_wait_for_complete_interrupt(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t * resp);

static fsp_err_t r_sdemmc_emmc_cmd_with_res(sdemmc_w_instance_ctrl_t * p_ctrl,
                                            uint32_t                   cmd,
                                            uint32_t                   cmd_arg,
                                            uint32_t                 * p_rsp);

static fsp_err_t r_sdemmc_sdemmc_wait_for_transfer_interrupt(sdemmc_w_instance_ctrl_t * p_ctrl);
static fsp_err_t r_sdemmc_sdemmc_wait_write_done(sdemmc_w_instance_ctrl_t * p_ctrl);

#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)
static void      r_sdemmc_emmc_cmd_without_res(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t cmd, uint32_t cmd_arg);
static fsp_err_t r_sdemmc_emmc_single_read_data_with_wait(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                          uint32_t                   cmd,
                                                          uint32_t                   cmd_arg,
                                                          uint32_t                   blk_size,
                                                          uint32_t                 * p_rsp,
                                                          uint8_t                  * p_buf);
static fsp_err_t r_sdemmc_emmc_single_read_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                uint32_t                   cmd,
                                                uint32_t                   cmd_arg,
                                                uint32_t                   blk_size,
                                                uint32_t                 * p_rsp,
                                                uint8_t                  * p_buf);
static fsp_err_t r_sdemmc_emmc_multi_read_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                               uint32_t                   cmd,
                                               uint32_t                   cmd_arg,
                                               uint32_t                 * p_rsp,
                                               uint8_t                  * p_buf,
                                               uint32_t                   block_count);
static fsp_err_t r_sdemmc_emmc_block_read_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                               uint32_t                   cmd,
                                               uint32_t                   cmd_arg,
                                               uint32_t                 * p_rsp,
                                               uint8_t                  * p_buf,
                                               uint32_t                   block_count);
static fsp_err_t r_sdemmc_emmc_single_write_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                 uint32_t                   cmd,
                                                 uint32_t                   cmd_arg,
                                                 uint32_t                   blk_size,
                                                 uint32_t                 * p_rsp,
                                                 uint8_t                  * p_buf);
static fsp_err_t r_sdemmc_emmc_multi_write_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                uint32_t                   cmd,
                                                uint32_t                   cmd_arg,
                                                uint32_t                 * p_rsp,
                                                uint8_t                  * p_buf,
                                                uint32_t                   block_count);
static fsp_err_t r_sdemmc_emmc_block_write_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                uint32_t                   cmd,
                                                uint32_t                   cmd_arg,
                                                uint32_t                 * p_rsp,
                                                uint8_t                  * p_buf,
                                                uint32_t                   block_count);

#endif                                 /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */

static inline uint32_t BITS_FOR_UNSTUFF(uint32_t * p_resp, uint32_t start, uint32_t size);

static fsp_err_t r_sdemmc_sdio_init_card(sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config,
                                         uint32_t ocr);
static fsp_err_t r_sdemmc_sd_init_card(sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config, uint32_t ocr);
static fsp_err_t r_sdemmc_emmc_init_card(sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config,
                                         uint32_t ocr);

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
static fsp_err_t r_sdemmc_sdio_block_read_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                               uint32_t                   cmd,
                                               uint32_t                   cmd_arg,
                                               uint32_t                 * p_rsp,
                                               uint8_t                  * p_buf,
                                               uint32_t                   block_size,
                                               uint32_t                   block_count);
static fsp_err_t r_sdemmc_sdio_multi_write_data(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                uint32_t                   cmd,
                                                uint32_t                   cmd_arg,
                                                uint32_t                 * p_rsp,
                                                uint8_t                  * p_buf,
                                                uint32_t                   block_size,
                                                uint32_t                   block_count);
static fsp_err_t r_sdemmc_sdio_io_rw_direct(sdemmc_w_instance_ctrl_t * p_ctrl,
                                            uint8_t                    write,
                                            uint8_t                    fn,
                                            uint32_t                   addr,
                                            uint8_t                    in,
                                            uint8_t                  * p_value);
static fsp_err_t r_sdemmc_sdio_io_rw_extended(sdemmc_w_instance_ctrl_t * p_ctrl,
                                              uint8_t                    write,
                                              uint8_t                    fn,
                                              uint32_t                   addr,
                                              uint32_t                   incr_addr,
                                              uint8_t                  * p_buf,
                                              uint32_t                   block_count,
                                              uint32_t                   blksz);
static void      r_sdemmc_hw_sdio_device_init(sdemmc_w_instance_ctrl_t * p_ctrl);
static uint32_t  r_sdemmc_hw_sdio_device_rx(sdemmc_w_instance_ctrl_t * p_ctrl, uint8_t * p_data, uint32_t length);
static uint32_t  r_sdemmc_hw_sdio_device_tx(sdemmc_w_instance_ctrl_t * p_ctrl, const uint8_t * p_data, uint32_t length);
static void      r_sdemmc_hw_sdio_device_deinit(sdemmc_w_instance_ctrl_t * p_ctrl);
static fsp_err_t r_sdemmc_common_fne_for_cistpl(st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size);
static fsp_err_t r_sdemmc_fn_fne_for_cistpl(st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size);
static fsp_err_t r_sdemmc_version_1_for_cistpl(st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size);
static fsp_err_t r_sdemmc_man_fid_for_cistpl(st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size);
static fsp_err_t r_sdemmc_local_cistpl_fn(st_sdemmc_config_t * p_config, uint8_t * p_buffer, uint32_t sz);
static fsp_err_t r_sdemmc_sdio_cis_tpl_parse(st_sdemmc_config_t * p_config,
                                             uint8_t            * p_data,
                                             uint8_t              tpl_code,
                                             uint8_t              tpl_link);
static fsp_err_t r_sdemmc_parse_for_cis_tuple(st_sdemmc_config_t          * p_config,
                                              uint8_t                     * p_tpl_descr,
                                              const struct tuples_for_cis * p_tpl,
                                              int32_t                       tpl_count,
                                              uint8_t                       code,
                                              uint8_t                     * p_buf,
                                              uint32_t                      size);
static fsp_err_t r_sdemmc_hw_sdemmc_sdio_func_enable(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                     st_sdemmc_config_t       * p_config,
                                                     uint32_t                   func_num);
static fsp_err_t r_sdemmc_hw_sdemmc_sdio_set_block_size(sdemmc_w_instance_ctrl_t * p_ctrl,
                                                        uint32_t                   func_num,
                                                        uint32_t                   blk_size);

#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE
static fsp_err_t r_sdemmc_mmc_decode_scr(st_sdemmc_config_t * p_config);
static fsp_err_t r_sdemmc_sd_decode_csd(sdemmc_w_instance_ctrl_t * const p_ctrl, st_sdemmc_config_t * p_config);
static fsp_err_t r_sdemmc_sd_decode_cid(st_sdemmc_config_t * p_config);
static fsp_err_t r_sdemmc_mmd_decode_ssr(st_sdemmc_config_t * p_config);
static uint32_t  r_sdemmc_sd_make_switch_arg(int32_t mode, int32_t group, int32_t value);

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE
static fsp_err_t r_sdemmc_emmc_wait_ready(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t * p_rocr);
static fsp_err_t r_sdemmc_emmc_decode_csd(sdemmc_w_instance_ctrl_t * const p_ctrl, st_sdemmc_config_t * p_config);
static fsp_err_t r_sdemmc_emmc_decode_ext_csd(sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config);
static fsp_err_t r_sdemmc_emmc_decode_cid(st_sdemmc_config_t * p_config);
static uint32_t  r_sdemmc_emmc_make_switch_arg(uint8_t set, uint8_t index, uint8_t value);
static fsp_err_t r_sdemmc_emmc_send_op_cond(sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t ocr, uint32_t * p_rocr);

#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if (CFG_PMGR == 1) && (SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE == 1)
static fsp_err_t r_sdemmc_w_enter_sleep(sdemmc_w_pmgr_context_t * p_context);
static fsp_err_t r_sdemmc_w_wakeup(sdemmc_w_pmgr_context_t * p_context);
static void      r_sdemmc_w_pmgr_callback(pmgr_callback_args_t * args);
static fsp_err_t r_sdemmc_w_subscribe_for_pmgr_notifications(sdemmc_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t r_sdemmc_w_unsubscribe_from_pmgr_notifications(sdemmc_w_instance_ctrl_t * const p_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
static const st_tuples_for_cis_t gs_func_list_for_cis_tpl[] =
{
    {0, 4, r_sdemmc_common_fne_for_cistpl},
    {1, 0, r_sdemmc_fn_fne_for_cistpl    },
    {4, 8, NULL                          },
};

/* Known TPL_CODEs table for CIS tuples */
static const st_tuples_for_cis_t gs_list_cis_tpl[] =
{
    {21, 3, r_sdemmc_version_1_for_cistpl},
    {32, 4, r_sdemmc_man_fid_for_cistpl  },
    {33, 2, NULL                         },
    {34, 0, r_sdemmc_local_cistpl_fn     },
};

static const uint8_t gs_speed_val[16] =
{
    0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80
};

static const uint32_t gs_speed_unit[8] =
{
    10000, 100000, 1000000, 10000000, 0, 0, 0, 0
};

/* Default value supplied by Renesas for CSI0 */
static const uint8_t gs_sdio_b_cis0_data[] =
{
    0x21,                              /* TPL_CODE_CISTPL_FUNCID */
    0x02,                              /* Link to next tuple */
    0x0C,                              /* Card function code */
    0x00,                              /* Not used */
    0x22,                              /* TPL_CODE_CISTPL_FUNCE */
    0x04,                              /* Link to next tuple */
    0x00,                              /* Extended data */
    0x00,                              /* Only block size function 0 can support (2048 = 0x0800) was 0x08 */
    0x08,                              /* Together with previous byte was 0x00 */
    0x0A,                              /* Transfer rate (25 Mbit/sec)    0x32-> 50Mhz 0x0A -> 10Mhz 0x09 -> 1Mhz 0x48 -> 400k */
    0x20,                              /* TPL_CODE_CISTPL_MANFID */
    0x04,                              /* Link to next tuple */
    0x45,                              /* SDIO manufacturer code 0x0296 */
    0x52,                              /* Used with previous byte */
    0x54,                              /* Part number/revision number OEM ID = 0x5347 */
    0x41,                              /* Used with previous byte */
    0xFF
};                                     /* End of tuple chain */

/* Default value supplied by Arasan for CSI1 */
static const uint8_t gs_sdio_b_cis1_data[] =
{
    0x21,                              /* TPL_CODE_CISTPL_FUNCID */
    0x02,                              /* Link to next tuple */
    0x0C,                              /* Card function type */
    0x00,                              /* Not used */
    0x22,                              /* TPL_CODE_CISTPL_FUNCE */
    0x2A,                              /* Link to next tuple was 0x1c it should be 42byte */
    0x01,                              /* Type of extended data */
    0x01,                              /* Wakeup support */
    0x11,                              /* X.Y revision was 0x00 */
    0x00,                              /* No serial number */
    0x00,                              /* No serial number */
    0x00,                              /* No serial number */
    0x00,                              /* No serial number */
    0x00,                              /* Size of the CSA space available for this function in bytes (0) */
    0x00,                              /* Used with previous */
    0x02,                              /* Used with previous was 0x00 */
    0x00,                              /* Used with previous */
    0x03,                              /* CSA property: Bit 0 - 0 implies R/W capability in CSA */

    /* Bit 1 - 0 implies the Host may reformat the file system */
    0x00,                              /* Maximum block size (256 bytes) was 0x80 */
    0x08,                              /* Used with previous was 0x00 */
    0x00,                              /* OCR value of the function was 0x08 */
    0x08,                              /* Used with previous was 0x01 */
    0xFF,                              /* Used with previous was 0xff */
    0x00,                              /* Used with previous */
    0x08,                              /* Minimum power required by this function (8 mA) */

    0x0a,                              /* ADDED=>Average power required by this function when operating(10 mA) */
    0x0f,                              /* ADDED=>Maximum power required by this function when operating(15 mA) */

    0x01,                              /* Stand by is not supported was 0x00 */
    0x01,                              /* Used with previous was 0x00 */
    0x01,                              /* Used with previous was 0x00 */

    0x00,                              /* Minimum BW */
    0x00,                              /* Used with previous */
    0x00,                              /* Optional BW */
    0x00,                              /* Used with previous */

    /* ADDED -> */
    0x00,                              /* Card required no timeout */
    0x00,
    0x00,
    0x00,

    0x00,                              /* High power mode - average power */
    0x00,                              /* High power function is not supported */
    0x00,
    0x00,

    0x00,                              /* High power mode - peak power */
    0x00,                              /* High power function is not supported */
    0x00,
    0x00,

    0x00,
    0x00,

    0x91,                              /* TPL_CODE_CISTPL_SDIO_STD */
    0x03,                              /* TPL_LINK */
    0x07,                              /* SDIO Standard I/O device type */
    0x00,                              /* Format and type of data */

    0x00,
    0xFF
};                                     /* End of tuple */

#endif /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)
static const uint32_t gs_tran_exp[] =
{
    10000, 100000, 1000000, 10000000, 0, 0, 0, 0
};

static const uint8_t gs_tran_mant[] =
{
    0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80,
};

static const uint32_t gs_tacc_exp[] =
{
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
};

static const uint32_t gs_tacc_mant[] =
{
    0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80,
};
#endif                                 /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */

static st_sdemmc_config_t gs_body;
static uint32_t           g_DataTransferWidth;
static uint32_t           g_ExtendedDataTransferWidth;
static uint32_t           g_SDCLKFrequencySelect;
static uint32_t           g_DriveStrengthSelect;
static uint32_t           g_BlockCountForCurrentTransfer;

#if (CFG_PMGR == 1) && (SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE == 1)
 #ifdef BSP_FEATURE_SDHI_VALID_CHANNEL_MASK
  #define R_SDEMMC_W_MAX_CHANNELS    __builtin_popcount(BSP_FEATURE_SDHI_VALID_CHANNEL_MASK)
 #else
  #define R_SDEMMC_W_MAX_CHANNELS    (1)
 #endif
static sdemmc_w_pmgr_context_t g_sdemmc_pmgr_context[R_SDEMMC_W_MAX_CHANNELS];
#endif

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** SDMMC function pointers   */
const sdmmc_api_t g_sdmmc_on_sdemmc_w =
{
    .open        = R_SDEMMC_W_Open,
    .mediaInit   = R_SDEMMC_W_MediaInit,
    .read        = R_SDEMMC_W_Read,
    .write       = R_SDEMMC_W_Write,
    .readIo      = R_SDEMMC_W_ReadIo,
    .writeIo     = R_SDEMMC_W_WriteIo,
    .readIoExt   = R_SDEMMC_W_ReadIoExt,
    .writeIoExt  = R_SDEMMC_W_WriteIoExt,
    .ioIntEnable = R_SDEMMC_W_IoIntEnable,
    .statusGet   = R_SDEMMC_W_StatusGet,
    .erase       = R_SDEMMC_W_Erase,
    .callbackSet = R_SDEMMC_W_CallbackSet,
    .close       = R_SDEMMC_W_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup SDEMMC_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the driver.  Resets SDEMMC_W, and enables card detection interrupts if card detection is enabled.
 * @ref R_SDEMMC_W_MediaInit must be called after this function before any other functions can be used.
 *
 * Implements @ref sdmmc_api_t::open().
 *
 * Example:
 * @snippet r_sdemmc_w_example.c R_SDEMMC_W_Open
 *
 * @retval     FSP_SUCCESS                     Module is now open.
 * @retval     FSP_ERR_ASSERTION               Null Pointer or block size is not in the valid range of 1-512. Block size
 *                                             must be 512 bytes for SD cards and eMMC devices.  It is configurable for
 *                                             SDIO only.
 * @retval     FSP_ERR_ALREADY_OPEN            Driver has already been opened with this instance of the control
 *                                             structure.
 * @retval     FSP_ERR_IRQ_BSP_DISABLED        Access interrupt is not enabled.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel does not exist on this MCU.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_Open (sdmmc_ctrl_t * const p_api_ctrl, sdmmc_cfg_t const * const p_cfg)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = FSP_SUCCESS;
    err = r_sdemmc_open_param_check(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Initialize control block. */
    memset(p_ctrl, 0, sizeof(*p_ctrl));
    p_ctrl->p_reg     = SDIO;
    p_ctrl->p_reg_mmc = SDEMMC;
    p_ctrl->p_cfg     = p_cfg;

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

    /* SDIO Device only. */
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        /* Set SDIO_MODE_REG */
        GPIO->SDIO_MODE_REG_b.SDIO_PAD_ENABLE = 1U;
        GPIO->SDIO_MODE_REG_b.SDIO_PORT_SEL   =
            (uint32_t) (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->device_port_sel) & 1;

        if (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->device_pull_en_cfg == 0)
        {
            GPIO->SDIO_MODE_REG_b.SDIO_PULL_EN = 0U;
        }
        else
        {
            GPIO->SDIO_MODE_REG_b.SDIO_PULL_EN = 0x3EU;
        }

        if (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->device_pull_sel_cfg == 0)
        {
            GPIO->SDIO_MODE_REG_b.SDIO_PULL_SEL = 0U;
        }
        else
        {
            GPIO->SDIO_MODE_REG_b.SDIO_PULL_SEL = 0x3EU;
        }

        /* Reset SDIO. */
        r_sdemmc_hw_sdio_device_init(p_ctrl);
    }
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE || SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

    /* SD/MMC/SDIO Host only. */
    if (SDEMMC_W_ROLE_HOST == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        /* Set EMMC_MODE_REG */
        GPIO->EMMC_MODE_REG_b.EMMC_ENABLE   = 1U;
        GPIO->EMMC_MODE_REG_b.EMMC_PORT_SEL =
            (uint32_t) (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->host_port_sel) & 1;
        GPIO->EMMC_MODE_REG_b.EMMC_CLKIN_SEL =
            (uint32_t) (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->host_rxclk_in_sel) & 1;

        if (p_ctrl->p_cfg->bus_width == SDMMC_BUS_WIDTH_8_BITS)
        {
            GPIO->EMMC_MODE_REG_b.EMMC_OCTA_MODE = 1U;
        }
        else
        {
            GPIO->EMMC_MODE_REG_b.EMMC_OCTA_MODE = 0U;
        }

        if (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->host_pull_en_cfg == 0)
        {
            GPIO->EMMC_MODE_REG_b.EMMC_PULL_EN = 0U;
        }
        else
        {
            if (p_ctrl->p_cfg->bus_width == SDMMC_BUS_WIDTH_8_BITS)
            {
                GPIO->EMMC_MODE_REG_b.EMMC_PULL_EN = 0x3FEU;
            }
            else
            {
                GPIO->EMMC_MODE_REG_b.EMMC_PULL_EN = 0x3EU;
            }
        }

        if (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->host_pull_sel_cfg == 0)
        {
            GPIO->EMMC_MODE_REG_b.EMMC_PULL_SEL = 0U;
        }
        else
        {
            if (p_ctrl->p_cfg->bus_width == SDMMC_BUS_WIDTH_8_BITS)
            {
                GPIO->EMMC_MODE_REG_b.EMMC_PULL_SEL = 0x3FEU;
            }
            else
            {
                GPIO->EMMC_MODE_REG_b.EMMC_PULL_SEL = 0x3EU;
            }
        }

        /* Reset stale interrupt flags */
        r_sdemmc_hw_sdemmc_enable(p_ctrl);
        r_sdemmc_sdemmc_interrupt_enable(p_ctrl);
    }
#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE || SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

    /* Set callback and context pointers, if configured */
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Configure and enable interrupts. */
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        r_sdemmc_irq_enable(p_cfg->sdio_irq, p_cfg->sdio_ipl, p_ctrl);
    }
    else
    {
        r_sdemmc_irq_enable(p_cfg->access_irq, p_cfg->access_ipl, p_ctrl);
    }

#if (CFG_PMGR == 1) && (SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE == 1)
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        r_sdemmc_w_subscribe_for_pmgr_notifications((sdemmc_w_instance_ctrl_t *) p_ctrl);
    }
#endif

    p_ctrl->initialized = false;
    p_ctrl->open        = SDEMMC_W_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the SDEMMC_W hardware and completes identification and configuration for the SD or eMMC or SDIO device.
 * This procedure requires several sequential commands.  This function blocks until all identification and configuration
 * commands are complete.
 *
 * Implements @ref sdmmc_api_t::mediaInit().
 *
 * Example:
 * @snippet r_sdemmc_w_example.c R_SDEMMC_W_MediaInit
 *
 * @retval     FSP_SUCCESS               Module is now ready for read/write access.
 * @retval     FSP_ERR_ASSERTION         Null Pointer or block size is not in the valid range of 1-512. Block size must
 *                                       be 512 bytes for SD cards and eMMC devices.  It is configurable for SDIO only.
 * @retval     FSP_ERR_NOT_OPEN          Driver has not been initialized.
 * @retval     FSP_ERR_TIMEOUT           Device did not respond.
 * @retval     FSP_ERR_INVALID_DATA      Unrecognized structure version.
 * @retval     FSP_ERR_UNSUPPORTED       Unsupported device.
 * @retval     FSP_ERR_INVALID_STATE     Sending command retry failure.
 * @retval     FSP_ERR_OUT_OF_MEMORY     There is no more memory available.
 * @retval     FSP_ERR_NOT_FOUND         Card not exist.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_MediaInit (sdmmc_ctrl_t * const p_api_ctrl, sdmmc_device_t * const p_device)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    uint8_t reg = 0;
#endif
#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)
    uint32_t rsp = 0;
#endif

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Device is not initialized until this function completes. */
    p_ctrl->initialized      = false;
    p_ctrl->device.card_type = 0xFF;

    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        /* Return device information to user. */
        p_ctrl->device.sector_size_bytes = p_ctrl->p_cfg->block_size;

        if (NULL != p_device)
        {
            *p_device = p_ctrl->device;
        }

        p_ctrl->initialized = true;

        return FSP_SUCCESS;
    }

    err = r_sdemmc_sdio_init_card(p_ctrl, &gs_body, gs_body.ocr);

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    if (!err)
    {
        /* the inserted card is sdio card */
        p_ctrl->device.card_type = SDMMC_CARD_TYPE_SDIO;
        gs_body.card_type        = SDMMC_PRIV_CT_SDIO_CARD;

        if (SDMMC_BUS_WIDTH_1_BIT == p_ctrl->p_cfg->bus_width)
        {
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth = SDEMMC_W_SDEMMC_DT_WIDTH_1BIT;
            err = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                             SDEMMC_W_PRV_SDIO_CMD52_READ,
                                             0,
                                             SDEMMC_W_SDIO_CCCR_BUS_INTERFACE_CONTROL,
                                             0,
                                             &reg);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
            reg = (uint8_t) (reg & ~SDEMMC_W_SDIO_CCCR_BUS_WIDTH_MASK);
            err = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                             SDEMMC_W_PRV_SDIO_CMD52_WRITE,
                                             0,
                                             SDEMMC_W_SDIO_CCCR_BUS_INTERFACE_CONTROL,
                                             reg,
                                             NULL);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }
        else
        {
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth = SDEMMC_W_SDEMMC_DT_WIDTH_4BIT;
            err = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                             SDEMMC_W_PRV_SDIO_CMD52_READ,
                                             0,
                                             SDEMMC_W_SDIO_CCCR_BUS_INTERFACE_CONTROL,
                                             0,
                                             &reg);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
            reg =
                (uint8_t) ((uint8_t) (reg & ~SDEMMC_W_SDIO_CCCR_BUS_WIDTH_MASK) |
                           SDEMMC_W_SDIO_CCCR_BUS_WIDTH_BIT_4BIT);
            err = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                             SDEMMC_W_PRV_SDIO_CMD52_WRITE,
                                             0,
                                             SDEMMC_W_SDIO_CCCR_BUS_INTERFACE_CONTROL,
                                             reg,
                                             NULL);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }

        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
        err = r_sdemmc_hw_sdemmc_sdio_func_enable(p_ctrl, &gs_body, 1);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Return device information to user. */
        p_ctrl->device.sector_size_bytes = p_ctrl->p_cfg->block_size;

        if (NULL != p_device)
        {
            *p_device = p_ctrl->device;
        }

        /* Check block size, 512 bytes is the maximum block size the peripheral supports */
        FSP_ASSERT(0U != p_ctrl->p_cfg->block_size);
        FSP_ASSERT(p_ctrl->p_cfg->block_size <= SDEMMC_W_MAX_BLOCK_SIZE);
        err = r_sdemmc_hw_sdemmc_sdio_set_block_size(p_ctrl, 1, p_ctrl->p_cfg->block_size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDCLKFrequencySelect =
            ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clk_div;
        p_ctrl->initialized = true;

        return FSP_SUCCESS;
    }
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);

    err = r_sdemmc_sd_init_card(p_ctrl, &gs_body, gs_body.ocr);

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE
    if (!err)
    {
        /* the inserted card is sd card */
        p_ctrl->device.card_type = SDMMC_CARD_TYPE_SD;

        if (SDMMC_BUS_WIDTH_1_BIT == p_ctrl->p_cfg->bus_width)
        {
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth = SDEMMC_W_SDEMMC_DT_WIDTH_1BIT;
        }
        else
        {
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth = SDEMMC_W_SDEMMC_DT_WIDTH_4BIT;
            err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_APP_CMD, ((gs_body.rca << 16) | 0xffff), &rsp);
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
            err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SET_BUS_WIDTH, SDEMMC_W_PRV_SD_BUS_WIDTH_4, &rsp);
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
        }

        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);

        /* Check to see if the card is write protected. */
        r_sdemmc_write_protect_get(p_ctrl);

        /* Return device information to user. */
        p_ctrl->device.sector_size_bytes = p_ctrl->p_cfg->block_size;

        if (NULL != p_device)
        {
            *p_device = p_ctrl->device;
        }

        /* SD and eMMC cards only support block size of 512 bytes on the SDEMMC_W hardware. */
        /* This can't be checked until we know it's not an SDIO card if SDIO is enabled. */
        FSP_ASSERT(SDEMMC_W_MAX_BLOCK_SIZE == p_ctrl->p_cfg->block_size);

        p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDCLKFrequencySelect =
            ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clk_div;
        p_ctrl->initialized = true;

        return FSP_SUCCESS;
    }
#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE */

    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);

    err = r_sdemmc_emmc_init_card(p_ctrl, &gs_body, gs_body.ocr);

#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE
    if (!err)
    {
        /* the inserted card is emmc card */
        gs_body.card_type        = SDMMC_PRIV_CT_MMC_CARD;
        p_ctrl->device.card_type = SDMMC_CARD_TYPE_MMC;

        if (SDMMC_BUS_WIDTH_1_BIT == p_ctrl->p_cfg->bus_width)
        {
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth = SDEMMC_W_SDEMMC_DT_WIDTH_1BIT;
        }
        else if ((SDMMC_BUS_WIDTH_8_BITS == p_ctrl->p_cfg->bus_width) &&
                 (1 == p_ctrl->p_reg_mmc->SDEMMC_CAPABILITIES0_REG_b.SupportforEmbeddedDevice8bit))
        {
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.ExtendedDataTransferWidth = 1;
            err =
                r_sdemmc_emmc_cmd_with_res(p_ctrl,
                                           SDEMMC_W_PRV_CMD_SWITCH,
                                           r_sdemmc_emmc_make_switch_arg(SDEMMC_W_PRV_E_CSD_CMD_SET_NORMAL,
                                                                         SDEMMC_W_PRV_E_CSD_BUS_WIDTH,
                                                                         SDEMMC_W_SDEMMC_DT_WIDTH_8BIT),
                                           &rsp);
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
        }
        else
        {
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth = SDEMMC_W_SDEMMC_DT_WIDTH_4BIT;
            err =
                r_sdemmc_emmc_cmd_with_res(p_ctrl,
                                           SDEMMC_W_PRV_CMD_SWITCH,
                                           r_sdemmc_emmc_make_switch_arg(SDEMMC_W_PRV_E_CSD_CMD_SET_NORMAL,
                                                                         SDEMMC_W_PRV_E_CSD_BUS_WIDTH,
                                                                         SDEMMC_W_SDEMMC_DT_WIDTH_4BIT),
                                           &rsp);
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
        }

        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);

        /* Check to see if the card is write protected. */
        r_sdemmc_write_protect_get(p_ctrl);

        /* Return device information to user. */
        p_ctrl->device.sector_size_bytes = p_ctrl->p_cfg->block_size;

        if (NULL != p_device)
        {
            *p_device = p_ctrl->device;
        }

        /* SD and eMMC cards only support block size of 512 bytes on the SDEMMC_W hardware. */
        /* This can't be checked until we know it's not an SDIO card if SDIO is enabled. */
        FSP_ASSERT(SDEMMC_W_MAX_BLOCK_SIZE == p_ctrl->p_cfg->block_size);

        p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDCLKFrequencySelect =
            ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clk_div;
        p_ctrl->initialized = true;

        return FSP_SUCCESS;
    }
#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

    FSP_ERROR_RETURN(FSP_ERR_UNSUPPORTED != err, FSP_ERR_UNSUPPORTED);

    FSP_RETURN(FSP_ERR_NOT_FOUND);
}

/*******************************************************************************************************************//**
 * Reads data from an SD or eMMC device.  Up to 0x10000 sectors can be read at a time.
 * Implements @ref sdmmc_api_t::read().
 *
 * A callback with the event SDMMC_EVENT_TRANSFER_COMPLETE is called when the read data is available.
 *
 * Example:
 * @snippet r_sdemmc_w_example.c R_SDEMMC_W_Read
 *
 * @retval     FSP_SUCCESS                   Data read successfully.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 * @retval     FSP_ERR_UNSUPPORTED           SD and eMMC support disabled in SDEMMC_W_CFG_SD_SUPPORT_ENABLE and
 *                                           SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_Read (sdmmc_ctrl_t * const p_api_ctrl,
                           uint8_t * const      p_dest,
                           uint32_t const       start_sector,
                           uint32_t const       sector_count)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(sector_count <= (UINT16_MAX + 1));
#endif
    err = r_sdemmc_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)
    uint32_t rsp      = 0;
    uint32_t argument = start_sector;

    if (!p_ctrl->sector_addressing)
    {
        /* Standard capacity SD cards and some eMMC devices use byte addressing. */
        argument *= p_ctrl->p_cfg->block_size;
    }

    if (sector_count > 1)
    {
        if (SDMMC_CARD_TYPE_MMC != p_ctrl->device.card_type)
        {
            if (gs_body.scr.sd_cmds & SDEMMC_W_PRV_SCR_CMD23_SUPPORT) /* closed */
            {
                /* read multi block */
                err =
                    r_sdemmc_emmc_block_read_data(p_ctrl, SDEMMC_W_PRV_CMD_READ_MULTIPLE_BLOCK, argument, &rsp,
                                                  (uint8_t *) p_dest, sector_count);
            }
            else
            {
                /* read open mode */
                err =
                    r_sdemmc_emmc_multi_read_data(p_ctrl, SDEMMC_W_PRV_CMD_READ_MULTIPLE_BLOCK, argument, &rsp,
                                                  (uint8_t *) p_dest, sector_count);
            }
        }
        else
        {
            /* read multi block */
            err = r_sdemmc_emmc_block_read_data(p_ctrl,
                                                SDEMMC_W_PRV_CMD_READ_MULTIPLE_BLOCK,
                                                argument,
                                                &rsp,
                                                (uint8_t *) p_dest,
                                                sector_count);
        }
    }
    else
    {
        /* read single block */
        err = r_sdemmc_emmc_single_read_data(p_ctrl,
                                             SDEMMC_W_PRV_CMD_READ_SINGLE_BLOCK,
                                             argument,
                                             512,
                                             &rsp,
                                             (uint8_t *) p_dest);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else                                  /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(start_sector);
    FSP_PARAMETER_NOT_USED(sector_count);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */
}

/*******************************************************************************************************************//**
 * Writes data to an SD or eMMC device. Up to 0x10000 sectors can be written at a time.
 * Implements @ref sdmmc_api_t::write().
 *
 * A callback with the event SDMMC_EVENT_TRANSFER_COMPLETE is called when the all data has been written and the device
 * is no longer holding DAT0 low to indicate it is busy.
 *
 * Example:
 * @snippet r_sdemmc_w_example.c R_SDEMMC_W_Write
 *
 * @retval     FSP_SUCCESS                   Card write finished successfully.
 * @retval     FSP_ERR_ASSERTION             Handle or Source address is NULL.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 * @retval     FSP_ERR_CARD_WRITE_PROTECTED  SD card is Write Protected.
 * @retval     FSP_ERR_WRITE_FAILED          Write operation failed.
 * @retval     FSP_ERR_UNSUPPORTED           SD and eMMC support disabled in SDEMMC_W_CFG_SD_SUPPORT_ENABLE and
 *                                           SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_Write (sdmmc_ctrl_t * const  p_api_ctrl,
                            uint8_t const * const p_source,
                            uint32_t const        start_sector,
                            uint32_t const        sector_count)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_source);
    FSP_ASSERT(sector_count <= (UINT16_MAX + 1));
#endif
    err = r_sdemmc_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)
    uint32_t rsp = 0;

    /* Check for write protection */
    FSP_ERROR_RETURN(false == p_ctrl->device.write_protected, FSP_ERR_CARD_WRITE_PROTECTED);

    /* Call SDMMC protocol write function */
    uint32_t argument = start_sector;

    if (!p_ctrl->sector_addressing)
    {
        /* Standard capacity SD cards and some eMMC devices use byte addressing. */
        argument *= p_ctrl->p_cfg->block_size;
    }

    if (sector_count > 1)
    {
        if (SDMMC_CARD_TYPE_MMC != p_ctrl->device.card_type)
        {
            if (gs_body.scr.sd_cmds & SDEMMC_W_PRV_SCR_CMD23_SUPPORT)
            {
                err =
                    r_sdemmc_emmc_block_write_data(p_ctrl, SDEMMC_W_PRV_CMD_WRITE_MULTIPLE_BLOCK, argument, &rsp,
                                                   (uint8_t *) p_source, sector_count);
            }
            else
            {
                err =
                    r_sdemmc_emmc_multi_write_data(p_ctrl, SDEMMC_W_PRV_CMD_WRITE_MULTIPLE_BLOCK, argument, &rsp,
                                                   (uint8_t *) p_source, sector_count);
            }
        }
        else
        {
            err =
                r_sdemmc_emmc_block_write_data(p_ctrl,
                                               SDEMMC_W_PRV_CMD_WRITE_MULTIPLE_BLOCK,
                                               argument,
                                               &rsp,
                                               (uint8_t *) p_source,
                                               sector_count);
        }
    }
    else
    {
        /* write single block */
        err =
            r_sdemmc_emmc_single_write_data(p_ctrl,
                                            SDEMMC_W_PRV_CMD_WRITE_SINGLE_BLOCK,
                                            argument,
                                            512,
                                            &rsp,
                                            (uint8_t *) p_source);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else                                  /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_source);
    FSP_PARAMETER_NOT_USED(start_sector);
    FSP_PARAMETER_NOT_USED(sector_count);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */
}

/*******************************************************************************************************************//**
 * The Read function reads a one byte register from an SDIO card.  Implements @ref sdmmc_api_t::readIo().
 *
 * This function blocks until the command is sent and the response is received.  p_data contains the register value read
 * when this function returns.
 *
 * @retval     FSP_SUCCESS                   Data read successfully.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_UNSUPPORTED           SDIO support disabled in SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY           Device is holding DAT0 low (device is busy) or another operation is
 *                                           ongoing.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_ReadIo (sdmmc_ctrl_t * const p_api_ctrl,
                             uint8_t * const      p_data,
                             uint32_t const       function,
                             uint32_t const       address)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_data);
#endif
    err = r_sdemmc_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        err = r_sdemmc_hw_sdio_device_rx(p_ctrl, p_data, 1);
    }
    else
    {
        /* Call SDMMC protocol read function */
        *p_data = 0U;
        err     = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                             SDEMMC_W_PRV_SDIO_CMD52_READ,
                                             (uint8_t) function,
                                             address,
                                             0,
                                             p_data);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_data);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
}

/*******************************************************************************************************************//**
 * Writes a one byte register to an SDIO card.  Implements @ref sdmmc_api_t::writeIo().
 *
 * This function blocks until the command is sent and the response is received.  The register has been written when this
 * function returns.  If read_after_write is true, p_data contains the register value read when this function returns.
 *
 * @retval     FSP_SUCCESS                   Card write finished successfully.
 * @retval     FSP_ERR_ASSERTION             Handle or Source address is NULL.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_WRITE_FAILED          Write operation failed.
 * @retval     FSP_ERR_UNSUPPORTED           SDIO support disabled in SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY           Device is holding DAT0 low (device is busy) or another operation is
 *                                           ongoing.
 * @retval     FSP_ERR_UNSUPPORTED           SDIO support disabled in SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_WriteIo (sdmmc_ctrl_t * const        p_api_ctrl,
                              uint8_t * const             p_data,
                              uint32_t const              function,
                              uint32_t const              address,
                              sdmmc_io_write_mode_t const read_after_write)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_data);
#endif
    err = r_sdemmc_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        err = r_sdemmc_hw_sdio_device_tx(p_ctrl, p_data, 1);
    }
    else
    {
        err = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                         SDEMMC_W_PRV_SDIO_CMD52_WRITE,
                                         (uint8_t) function,
                                         address,
                                         *p_data,
                                         NULL);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WRITE_FAILED);

        if (SDMMC_IO_WRITE_READ_AFTER_WRITE == read_after_write)
        {
            /* Call SDMMC protocol read function */
            *p_data = 0U;
            err     = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                                 SDEMMC_W_PRV_SDIO_CMD52_READ,
                                                 (uint8_t) function,
                                                 address,
                                                 0,
                                                 p_data);
        }
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_data);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);
    FSP_PARAMETER_NOT_USED(read_after_write);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
}

/*******************************************************************************************************************//**
 * Reads data from an SDIO card function.  Implements @ref sdmmc_api_t::readIoExt().
 *
 * This function blocks until the command is sent and the response is received.  A callback with the event
 * SDMMC_EVENT_TRANSFER_COMPLETE is called when the read data is available.
 *
 * @retval     FSP_SUCCESS                   Data read successfully.
 * @retval     FSP_ERR_ASSERTION             NULL pointer, or count is not in the valid range of 1-512 for byte mode or
 *                                           1-511 for block mode.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 * @retval     FSP_ERR_INVALID_ARGUMENT      Parameter passed into function was invalid.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 * @retval     FSP_ERR_UNSUPPORTED           SDIO support disabled in SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_ReadIoExt (sdmmc_ctrl_t * const     p_api_ctrl,
                                uint8_t * const          p_dest,
                                uint32_t const           function,
                                uint32_t const           address,
                                uint32_t * const         count,
                                sdmmc_io_transfer_mode_t transfer_mode,
                                sdmmc_io_address_mode_t  address_mode)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(NULL != count);
    FSP_ASSERT(0U != (*count));
#endif
    err = r_sdemmc_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        if (SDMMC_IO_MODE_TRANSFER_BLOCK == transfer_mode)
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT((*count) <= SDEMMC_W_PRV_SDIO_EXT_MAX_BLOCKS);
 #endif
            err = r_sdemmc_hw_sdio_device_rx(p_ctrl, p_dest, *count * p_ctrl->p_cfg->block_size);
        }
        else
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT((*count) <= SDEMMC_W_PRV_SDIO_EXT_MAX_BYTES);
 #endif
            err = r_sdemmc_hw_sdio_device_rx(p_ctrl, p_dest, *count);
        }
    }
    else
    {
        if (SDMMC_IO_MODE_TRANSFER_BLOCK == transfer_mode)
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT((*count) <= SDEMMC_W_PRV_SDIO_EXT_MAX_BLOCKS);
 #endif
            err = r_sdemmc_sdio_io_rw_extended(p_ctrl,
                                               SDEMMC_W_PRV_SDIO_CMD52_READ,
                                               (uint8_t) function,
                                               address,
                                               address_mode,
                                               p_dest,
                                               *count,
                                               p_ctrl->p_cfg->block_size);
        }
        else
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT((*count) <= SDEMMC_W_PRV_SDIO_EXT_MAX_BYTES);
 #endif
            err = r_sdemmc_sdio_io_rw_extended(p_ctrl,
                                               SDEMMC_W_PRV_SDIO_CMD52_READ,
                                               (uint8_t) function,
                                               address,
                                               address_mode,
                                               p_dest,
                                               *count,
                                               1);
        }
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);
    FSP_PARAMETER_NOT_USED(count);
    FSP_PARAMETER_NOT_USED(transfer_mode);
    FSP_PARAMETER_NOT_USED(address_mode);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
}

/*******************************************************************************************************************//**
 * Writes data to an SDIO card function.  Implements @ref sdmmc_api_t::writeIoExt().
 *
 * This function blocks until the command is sent and the response is received.  A callback with the event
 * SDMMC_EVENT_TRANSFER_COMPLETE is called when the all data has been written.
 *
 * @retval     FSP_SUCCESS                   Card write finished successfully.
 * @retval     FSP_ERR_ASSERTION             NULL pointer, or count is not in the valid range of 1-512 for byte mode or
 *                                           1-511 for block mode.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 * @retval     FSP_ERR_INVALID_ARGUMENT      Parameter passed into function was invalid.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 * @retval     FSP_ERR_UNSUPPORTED           SDIO support disabled in SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_WriteIoExt (sdmmc_ctrl_t * const     p_api_ctrl,
                                 uint8_t const * const    p_source,
                                 uint32_t const           function,
                                 uint32_t const           address,
                                 uint32_t const           count,
                                 sdmmc_io_transfer_mode_t transfer_mode,
                                 sdmmc_io_address_mode_t  address_mode)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_source);
    FSP_ASSERT(0U != count);
#endif
    err = r_sdemmc_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        if (SDMMC_IO_MODE_TRANSFER_BLOCK == transfer_mode)
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(count <= SDEMMC_W_PRV_SDIO_EXT_MAX_BLOCKS);
 #endif
            err = r_sdemmc_hw_sdio_device_tx(p_ctrl, p_source, count * p_ctrl->p_cfg->block_size);
        }
        else
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(count <= SDEMMC_W_PRV_SDIO_EXT_MAX_BYTES);
 #endif
            err = r_sdemmc_hw_sdio_device_tx(p_ctrl, p_source, count);
        }
    }
    else
    {
        if (SDMMC_IO_MODE_TRANSFER_BLOCK == transfer_mode)
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(count <= SDEMMC_W_PRV_SDIO_EXT_MAX_BLOCKS);
 #endif
            err = r_sdemmc_sdio_io_rw_extended(p_ctrl,
                                               SDEMMC_W_PRV_SDIO_CMD52_WRITE,
                                               (uint8_t) function,
                                               address,
                                               address_mode,
                                               (uint8_t *) p_source,
                                               count,
                                               p_ctrl->p_cfg->block_size);
        }
        else
        {
 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(count <= SDEMMC_W_PRV_SDIO_EXT_MAX_BYTES);
 #endif
            err = r_sdemmc_sdio_io_rw_extended(p_ctrl,
                                               SDEMMC_W_PRV_SDIO_CMD52_WRITE,
                                               (uint8_t) function,
                                               address,
                                               address_mode,
                                               (uint8_t *) p_source,
                                               count,
                                               1);
        }
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_source);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);
    FSP_PARAMETER_NOT_USED(count);
    FSP_PARAMETER_NOT_USED(transfer_mode);
    FSP_PARAMETER_NOT_USED(address_mode);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
}

/*******************************************************************************************************************//**
 * Enables or disables the SDIO Interrupt.  Implements @ref sdmmc_api_t::ioIntEnable().
 *
 * @retval     FSP_SUCCESS          Card enabled or disabled SDIO interrupts successfully.
 * @retval     FSP_ERR_NOT_OPEN     Driver has not been initialized.
 * @retval     FSP_ERR_ASSERTION    NULL pointer.
 * @retval     FSP_ERR_DEVICE_BUSY  Driver is busy with a previous operation.
 * @retval     FSP_ERR_UNSUPPORTED  SDIO support disabled in SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_IoIntEnable (sdmmc_ctrl_t * const p_api_ctrl, bool enable)
{
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

 #if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);

    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        /* Make sure the device is not busy. */
        FSP_ERROR_RETURN((0x1 == p_ctrl->p_reg->SDIO_CARDRDY_REG_b.CARD_RDY), FSP_ERR_DEVICE_BUSY);

        /* Enable or disable interrupt. */
        if (enable)
        {
            NVIC_EnableIRQ(SDIO_IRQn);  /* Enable interrupt */
        }
        else
        {
            NVIC_DisableIRQ(SDIO_IRQn); /* Disable interrupt */
        }
    }
    else
    {
        /* Make sure the card is not busy. */
        FSP_ERROR_RETURN((0xF == p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.DAT3TO0LineSignalLevel),
                         FSP_ERR_DEVICE_BUSY);

        /* Enable or disable interrupt. */
        if (enable)
        {
            NVIC_EnableIRQ(SDEMMC_IRQn);  /* Enable interrupt */
        }
        else
        {
            NVIC_DisableIRQ(SDEMMC_IRQn); /* Disable interrupt */
        }
    }

    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(enable);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
}

/*******************************************************************************************************************//**
 * Provides driver status.  Implements @ref sdmmc_api_t::statusGet().
 *
 * @retval     FSP_SUCCESS        Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION  NULL pointer.
 * @retval     FSP_ERR_NOT_OPEN   Driver has not been initialized.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_StatusGet (sdmmc_ctrl_t * const p_api_ctrl, sdmmc_status_t * const p_status)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE

    /* Check pointers for NULL values */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);

    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check CD pin. */
    if (SDEMMC_W_ROLE_HOST == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        if (SDMMC_CARD_DETECT_CD == p_ctrl->p_cfg->card_detect)
        {
            p_status->card_inserted = p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.CardInserted;
        }
        else
        {
            p_status->card_inserted = true;
        }
    }

    /* Whether or not the media is initialized. */
    p_status->initialized = p_ctrl->initialized;

    /* Check if the card is busy. */
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        p_status->transfer_in_progress =
            (0x1 != p_ctrl->p_reg->SDIO_CARDRDY_REG_b.CARD_RDY);
    }
    else
    {
        p_status->transfer_in_progress =
            (0xF != p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.DAT3TO0LineSignalLevel);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erases sectors of an SD card or eMMC device.  Implements @ref sdmmc_api_t::erase().
 *
 * Poll the status to determine when erase is complete.
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             A required pointer is NULL or an argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_CARD_WRITE_PROTECTED  SD card is Write Protected.
 * @retval     FSP_ERR_RESPONSE              Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 * @retval     FSP_ERR_UNSUPPORTED           SD and eMMC support disabled in SDEMMC_W_CFG_SD_SUPPORT_ENABLE and
 *                                           SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE.
 * @retval     FSP_ERR_DEVICE_BUSY           Device is holding DAT0 low (device is busy) or another operation is
 *                                           ongoing.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_Erase (sdmmc_ctrl_t * const p_api_ctrl, uint32_t const start_sector, uint32_t const sector_count)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

    err = r_sdemmc_erase_error_check(p_ctrl, start_sector, sector_count);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)
    uint32_t start_address = 0;
    uint32_t end_address   = 0;
    uint32_t start_command = 0;
    uint32_t end_command   = 0;
    uint32_t argument      = 0;
    uint32_t transfer_reg  = 0;

    /*  SDHC, SDXC and eMMC high capacity media use block addressing. */
    if (true == p_ctrl->sector_addressing)
    {
        start_address = start_sector;
        end_address   = ((start_sector + sector_count) - 1);
    }
    else
    {
        start_address = (start_sector * p_ctrl->p_cfg->block_size);
        end_address   = ((start_sector + sector_count) * p_ctrl->p_cfg->block_size) - 1U;
    }

 #if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE
    if (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type)
    {
        start_command = SDEMMC_W_PRV_CMD_TAG_ERASE_GROUP_START;
        end_command   = SDEMMC_W_PRV_CMD_TAG_ERASE_GROUP_END;
        argument      = SDEMMC_W_PRV_EMMC_ERASE_ARGUMENT_TRIM;
    }
    else
 #endif
    {
        start_command = SDEMMC_W_PRV_CMD_ERASE_WR_BLK_START;
        end_command   = SDEMMC_W_PRV_CMD_ERASE_WR_BLK_END;
        argument      = 0U;            /* Argument unused for SD */
    }

    /* Send command to set start erase address (CMD35 for eMMC, CMD32 for SD). */
    err = r_sdemmc_command_send(p_ctrl, start_command, start_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Send command to set end erase address (CMD36 for eMMC, CMD33 for SD). */
    err = r_sdemmc_command_send(p_ctrl, end_command, end_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Send erase command (CMD38). */
    transfer_reg = SDEMMC_W_PRV_CMD_ERASE << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_W_GET_CMD_RESP_TYPE(SDEMMC_W_PRV_CMD_ERASE) <<
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    r_sdemmc_command_send_no_wait(p_ctrl, transfer_reg, argument);

    return FSP_SUCCESS;
#else                                  /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(start_sector);
    FSP_PARAMETER_NOT_USED(sector_count);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref sdmmc_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_CallbackSet (sdmmc_ctrl_t * const          p_api_ctrl,
                                  void (                      * p_callback)(sdmmc_callback_args_t *),
                                  void * const                  p_context,
                                  sdmmc_callback_args_t * const p_callback_memory)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback        = p_callback;
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the SDEMMC transfer result.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @note    This function should only be called from an ISR or within a critical section to ensure
 *          the result reflects the current transfer and not a subsequent one.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_ResultGet (sdmmc_ctrl_t * const p_api_ctrl, sdemmc_w_transfer_result_t * p_result)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_result);
    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    memcpy(p_result, &p_ctrl->result, sizeof(sdemmc_w_transfer_result_t));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes an open SD/MMC device.  Implements @ref sdmmc_api_t::close().
 *
 * @retval     FSP_SUCCESS               Successful close.
 * @retval     FSP_ERR_ASSERTION         The parameter p_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN          Driver has not been initialized.
 * @retval     FSP_ERR_TIMEOUT           Device did not respond.
 **********************************************************************************************************************/
fsp_err_t R_SDEMMC_W_Close (sdmmc_ctrl_t * const p_api_ctrl)
{
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) p_api_ctrl;
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    fsp_err_t err = FSP_SUCCESS;
    uint8_t   reg = 0;
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);

    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (SDEMMC_W_ROLE_HOST == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

        /* For SDIO, follow the procedure in Figure 3-2 "Card Initialization Flow in SD mode (SDIO Aware Host)" in SDIO
         * Specification Version 2.00. */

        /* Reset I/O: In order to reset an I/O only card or the I/O portion of a combo card, use CMD52 to set the RES bit
         * in the CCCR (bit 3 of register 6). Reference Table 6-2 "CCCR bit definitions" in SDIO Specification
         * Version 2.00. */
        if (SDMMC_CARD_TYPE_SDIO == p_ctrl->device.card_type)
        {
            reg = 1U << 3;
            err = r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                             SDEMMC_W_PRV_SDIO_CMD52_WRITE,
                                             0,
                                             SDEMMC_W_SDIO_CCCR_IOASX_RESET,
                                             reg,
                                             NULL);

            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
        }
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE
        if ((SDMMC_CARD_TYPE_SD == p_ctrl->device.card_type) || (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type))
        {
            /* Put the card in idle state (CMD0). */
            r_sdemmc_emmc_cmd_without_res(p_ctrl, SDEMMC_W_PRV_CMD_GO_IDLE_STATE, 0);
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
        }
#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */
    }

    p_ctrl->open = 0U;

#if (CFG_PMGR == 1) && (SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE == 1)
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        r_sdemmc_w_unsubscribe_from_pmgr_notifications((sdemmc_w_instance_ctrl_t *) p_ctrl);
    }
#endif

    /* Deinitialize callback and context. */
    p_ctrl->p_callback        = NULL;
    p_ctrl->p_context         = NULL;
    p_ctrl->p_callback_memory = NULL;

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE
    if ((SDMMC_CARD_TYPE_SD == p_ctrl->device.card_type) || (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type))
    {
        /* Put the card in idle state (CMD0). */
        r_sdemmc_emmc_cmd_without_res(p_ctrl, SDEMMC_W_PRV_CMD_GO_IDLE_STATE, 0);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
    }
#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

    /* Disable SDEMMC_W interrupts. */
    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        r_sdemmc_irq_disable(p_ctrl->p_cfg->sdio_irq);
    }
    else
    {
        r_sdemmc_irq_disable(p_ctrl->p_cfg->access_irq);
    }

    if (SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
        r_sdemmc_hw_sdio_device_deinit(p_ctrl);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
        /* Reset SDIO_MODE_REG */
        GPIO->SDIO_MODE_REG_b.SDIO_PAD_ENABLE = 0;
        GPIO->SDIO_MODE_REG_b.SDIO_PULL_EN    = 0;
        GPIO->SDIO_MODE_REG_b.SDIO_PULL_SEL   = 0;
    }
    else
    {
        r_sdemmc_hw_sdemmc_disable(p_ctrl);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

        /* Reset EMMC_MODE_REG */
        GPIO->EMMC_MODE_REG_b.EMMC_ENABLE    = 0;
        GPIO->EMMC_MODE_REG_b.EMMC_CLKIN_SEL = 0;
        GPIO->EMMC_MODE_REG_b.EMMC_OCTA_MODE = 0;
        GPIO->EMMC_MODE_REG_b.EMMC_PULL_EN   = 0;
        GPIO->EMMC_MODE_REG_b.EMMC_PULL_SEL  = 0;
    }

    /* Do not set the module stop bit since the CMD0 may not be complete yet. Do not wait for CMD0 to complete because
     * the card could be unplugged and waiting for the response timeout in this function is not desirable. */

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SDEMMC_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking for the open function.
 *
 * @param[in]  p_ctrl                          Pointer to the instance control block.
 * @param[in]  p_cfg                           Pointer to the instance configuration structure.
 *
 * @retval     FSP_SUCCESS                     Parameters to open() are in the valid range.
 * @retval     FSP_ERR_ASSERTION               A required input pointer is NULL.
 * @retval     FSP_ERR_ALREADY_OPEN            Driver has already been opened with this instance of the control
 *                                             structure.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel does not exist on this MCU.
 * @retval     FSP_ERR_IRQ_BSP_DISABLED        Access interrupt is not enabled.
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_open_param_check (sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

 #ifdef BSP_FEATURE_SDHI_VALID_CHANNEL_MASK

    /* Verify the requested channel exists on the MCU. */
    FSP_ERROR_RETURN(0U != ((1U << p_cfg->channel) & BSP_FEATURE_SDHI_VALID_CHANNEL_MASK),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #else                                 /* BSP_FEATURE_SDHI_VALID_CHANNEL_MASK */
    /* Verify the requested channel exists on the MCU. */
    FSP_ERROR_RETURN(0U == p_cfg->channel, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #endif /* BSP_FEATURE_SDHI_VALID_CHANNEL_MASK */

    /* SD/MMC/SDIO Host only. */
    if (SDEMMC_W_ROLE_HOST == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role)
    {
        /* Access interrupt is required. */
        FSP_ERROR_RETURN(p_cfg->access_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Parameter checking for erase.
 *
 * @param[in]  p_ctrl                        Pointer to the instance control block.
 * @param[in]  start_sector                  First sector to erase
 * @param[in]  sector_count                  Number of sectors to erase
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             A required pointer is NULL or an argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 * @retval     FSP_ERR_CARD_WRITE_PROTECTED  SD card is Write Protected.
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_erase_error_check (sdemmc_w_instance_ctrl_t * const p_ctrl,
                                             uint32_t const                   start_sector,
                                             uint32_t const                   sector_count)
{
    fsp_err_t err = r_sdemmc_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    FSP_PARAMETER_NOT_USED(start_sector);
    FSP_PARAMETER_NOT_USED(sector_count);

    /* Check for write protection */
    FSP_ERROR_RETURN(false == p_ctrl->device.write_protected, FSP_ERR_CARD_WRITE_PROTECTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter checking for runtime APIs.
 *
 * @param[in]  p_ctrl                        Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS                   Device is ready to be accessed.
 * @retval     FSP_ERR_ASSERTION             A required pointer is NULL.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_common_error_check (sdemmc_w_instance_ctrl_t * const p_ctrl)
{
#if SDEMMC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SDEMMC_W_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type)
    {
        /* Because the default card_type value is 0, if mediaInit has not yet been called,
         * return FSP_ERR_CARD_NOT_INITIALIZED.*/
        FSP_ERROR_RETURN(p_ctrl->initialized, FSP_ERR_CARD_NOT_INITIALIZED);

        /* To verify no command sequence is in progress in SDEMMC_W, verify SD_INFO2.CBSY is not set.
         * To verify the card has completed the requested operation, verify SD_INFO2.SDD0MON is set. */
        FSP_ERROR_RETURN((0xF == p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.DAT3TO0LineSignalLevel),
                         FSP_ERR_DEVICE_BUSY);
    }
    else if (SDMMC_CARD_TYPE_SD == p_ctrl->device.card_type)
    {
        /* Verify the card has not been removed since the last card initialization. */
        FSP_ERROR_RETURN(p_ctrl->initialized, FSP_ERR_CARD_NOT_INITIALIZED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures and enables an interrupt.
 *
 * @param[in]  irq             Interrupt number.
 * @param[in]  priority        NVIC priority of the interrupt
 * @param[in]  p_context       Pointer to data required in the ISR.
 **********************************************************************************************************************/
static void r_sdemmc_irq_enable (IRQn_Type irq, uint8_t priority, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, priority, p_context);
    }
}

/*******************************************************************************************************************//**
 * Disables an interrupt.
 *
 * @param[in]  irq             Interrupt to disable.
 **********************************************************************************************************************/
static void r_sdemmc_irq_disable (IRQn_Type irq)
{
    if (irq >= 0)
    {
        /* Disables interrupts in the NVIC. */
        R_BSP_IrqDisable(irq);

        /* Clears the control block from the vector information array. */
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Stores access interrupt flags in the control block and calls the callback.
 *
 * @param[in]  p_ctrl          Pointer to the instance control block.
 * @param[in]  p_args          Pointer to SDMMC callback arguments.
 **********************************************************************************************************************/
static void r_sdemmc_access_irq_process (sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args)
{
    sdemmc_w_event_t flags;

    /* Read interrupt flag registers. */
    flags.word = p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_REG;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_REG = 0;

    if (flags.bit.response_end)
    {
        p_args->event |= SDMMC_EVENT_RESPONSE;

        p_args->response.status = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE0_REG;

        if (SDEMMC_W_PRV_CMD_ERASE == p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG_b.CommandIndex)
        {
            /* Determine if erase is complete or not based on DAT0. Access interrupt is not required for erase. */
            if (0xF == p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.DAT3TO0LineSignalLevel)
            {
                p_args->event |= SDMMC_EVENT_ERASE_COMPLETE;

                /* Disable response end interrupt */
                p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb = 0;
                p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb = 0;
                p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForDATLine            = 1;
                R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
            }
            else
            {
                p_args->event |= SDMMC_EVENT_ERASE_BUSY;
            }
        }
        else
        {
            /* Disable response end interrupt */
            p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb = 0;
            p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb = 0;
        }
    }

    if (flags.bit.access_end)
    {
        p_ctrl->result.sdio_blk_or_byte =
            (p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG & 0x08000000) ? 1 : 0;
        p_ctrl->result.sdio_blk_size =
            p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize;
        p_ctrl->result.sdio_blk_count = g_BlockCountForCurrentTransfer;

        p_args->event |= SDMMC_EVENT_TRANSFER_COMPLETE;

        /* Disable access end interrupt */
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 0;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 0;
    }

    if (flags.bit.card_removed)
    {
        p_args->event |= SDMMC_EVENT_CARD_REMOVED;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardRemovalSignalEnb   = 0;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardRemovalStatusEnb   = 0;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardInsertionSignalEnb = 1;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardInsertionStatusEnb = 1;
    }

    if (flags.bit.card_inserted)
    {
        p_args->event |= SDMMC_EVENT_CARD_INSERTED;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardInsertionSignalEnb = 0;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardInsertionStatusEnb = 0;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardRemovalSignalEnb   = 1;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardRemovalStatusEnb   = 1;
    }

    if (flags.bit.CardInterrupt)
    {
        /* card interrupt should be disabled during ISR operation. */
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardInterruptSignalEnb = 0;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardInterruptStatusEnb = 0;
    }

    /* Check for errors */
    if (flags.word & SDEMMC_W_PRV_ACCESS_ERROR_MASK)
    {
        flags.bit.ErrorInterrupt = 1U;
        p_args->event           |= SDMMC_EVENT_TRANSFER_ERROR;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG             = 0;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG             = 0;
        p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.InternalClockEnable = 0;
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);
        p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.InternalClockEnable = 1;
    }

    /* Combine all events for each command because this flag is polled in some functions. */
    p_ctrl->sdemmc_w_event.word |= flags.word;
}

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Send a command to the SD, eMMC, or SDIO device.
 *
 * @param[in]  p_ctrl          Pointer to the instance control block.
 * @param[in]  command         Command to send.
 * @param[in]  argument        Argument to send with the command.
 **********************************************************************************************************************/
static void r_sdemmc_command_send_no_wait (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument)
{
    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;
    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = 0;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = 0;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = 0;
    g_BlockCountForCurrentTransfer = 0;

    /* Enable response end interrupt. */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb = 1;

    /* Write argument, then command to the SDEMMC_W peripheral. */
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG              = argument;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = command;

    /* Enable Clock */
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Send a command to the SD, eMMC, or SDIO device and wait for response
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[in]  command              Command to send.
 * @param[in]  argument             Argument to send with the command.
 *
 * @retval     FSP_SUCCESS          Command sent and response received, no errors in response.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_command_send (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument)
{
    uint32_t transfer_reg = 0;

    /* Verify the device is not busy. */
    r_sdemmc_wait_for_device(p_ctrl);

    /* Send the command. */
    transfer_reg = command << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(command) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    r_sdemmc_command_send_no_wait(p_ctrl, transfer_reg, argument);

    /* Wait for end of response, error or timeout */
    return r_sdemmc_wait_for_event(p_ctrl, SDEMMC_W_PRV_RESPONSE_BIT, SDEMMC_W_PRV_RESPONSE_TIMEOUT_US);
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Update write protection status in control block.
 *
 * @param[in]  p_ctrl          Pointer to the instance control block.
 **********************************************************************************************************************/
static void r_sdemmc_write_protect_get (sdemmc_w_instance_ctrl_t * const p_ctrl)
{
    /* Update write protection status in the control block if the device is a card. */
    if (p_ctrl->p_cfg->write_protect)
    {
        p_ctrl->device.write_protected =
            (0 == p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.WriteProtectSwitchPinLevel);
    }
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Wait for the device.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS          Previous operation is complete, and SDEMMC_W is ready for the next operation.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_wait_for_device (sdemmc_w_instance_ctrl_t * const p_ctrl)
{
    /* Wait for the device to stop holding DAT0 low. */
    uint32_t timeout = SDEMMC_W_PRV_BUSY_TIMEOUT_US;

    while (0xF != p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.DAT3TO0LineSignalLevel)
    {
        FSP_ERROR_RETURN(timeout > 0, FSP_ERR_DEVICE_BUSY);

        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;
    }

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Waits for the access end interrupt.
 *
 * @param[in]  p_ctrl            Pointer to the instance control block.
 * @param[in]  bit               Bit to check in p_ctrl->sdemmc_w_event
 * @param[in]  timeout_us        Number of loops to check bit (at least 1 us per loop).
 *
 * @retval     FSP_SUCCESS       Requested bit (access end or response end) is set.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_wait_for_event (sdemmc_w_instance_ctrl_t * const p_ctrl, uint32_t bit, uint32_t timeout_us)
{
    /* The event status is updated in the access interrupt.  Use a local copy of the event status to make sure
     * it isn't updated during the loop. */
    volatile sdemmc_w_event_t event;

    while (true)
    {
        /* Check for updates to the event status. */
        event.word = p_ctrl->sdemmc_w_event.word;

        /* Return an error if a hardware error occurred. */
        if (event.bit.ErrorInterrupt)
        {
            r_sdemmc_hw_sdemmc_renable_prepare(p_ctrl);
            p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 1;
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst         = 1;
            p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.InternalClockEnable = 0;
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);
            r_sdemmc_hw_sdemmc_renable(p_ctrl);
            r_sdemmc_sdemmc_interrupt_enable(p_ctrl);
            FSP_RETURN(FSP_ERR_RESPONSE);
        }

        /* If the requested bit is set, return success. */
        if (event.word & (1U << bit))
        {
            return FSP_SUCCESS;
        }

        /* Check for timeout. */
        timeout_us--;

        if (0U == timeout_us)
        {
            FSP_RETURN(FSP_ERR_TIMEOUT);
        }

        /* Wait 1 us for consistent loop timing. */
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
    }
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Save Card Specific Data.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[in]  rca                  Relative card address
 * @param[out] p_csd_reg            Pointer to card specific data.
 *
 * @retval     FSP_SUCCESS          Card specific data stored in provided pointer.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_csd_save (sdemmc_w_instance_ctrl_t * const p_ctrl,
                                    uint32_t                         rca,
                                    sdmmc_priv_csd_reg_t * const     p_csd_reg,
                                    uint32_t                         send_flag)
{
    if (true == send_flag)
    {
        /* Send CMD9 to get CSD */
        fsp_err_t err = r_sdemmc_command_send(p_ctrl, SDEMMC_W_PRV_CMD_SEND_CSD, (rca << 16));
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* SDResponseR2 are bits from 8-127, first 8 MSBs are reserved */
    p_csd_reg->reg.sdrsp10 = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE0_REG;
    p_csd_reg->reg.sdrsp32 = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE1_REG;
    p_csd_reg->reg.sdrsp54 = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE2_REG;
    p_csd_reg->reg.sdrsp76 = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE3_REG;

    /* Get the CSD version. */
    uint32_t csd_version = p_csd_reg->csd_v1_b.csd_structure;

    /* Save sector count (total number of sectors on device) and erase sector count (minimum erasable unit in
     * sectors). */
    uint32_t mult = 0;

    if ((SDEMMC_W_PRV_CSD_VERSION_1_0 == csd_version) || (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type))
    {
        mult = (1U << (p_csd_reg->csd_v1_b.c_size_mult + 2));
        p_ctrl->device.sector_count = ((p_csd_reg->csd_v1_b.c_size + 1U) * mult);

        /* Scale the sector count by the actual block size. */
        uint32_t read_sector_size = 1U << p_csd_reg->csd_v1_b.read_bl_len;
        p_ctrl->device.sector_count = p_ctrl->device.sector_count * (read_sector_size / SDEMMC_W_MAX_BLOCK_SIZE);

        if (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type)
        {
            /* If c_size is 0xFFF, then sector_count should be obtained from the extended CSD.
             * Set it to 0 to indicate it should come from the extended CSD later. */
            if (SDEMMC_W_PRV_SECTOR_COUNT_IN_EXT_CSD == p_csd_reg->csd_v1_b.c_size)
            {
                p_ctrl->device.sector_count = 0U;
            }
        }
    }

 #if SDEMMC_W_CFG_SD_SUPPORT_ENABLE
    else if (SDEMMC_W_PRV_CSD_VERSION_2_0 == csd_version)
    {
        p_ctrl->device.sector_count = (p_csd_reg->csd_v2_b.c_size + 1U) * SDEMMC_W_PRV_BYTES_PER_KILOBYTE;
    }
    else
    {
        /* Do Nothing */
    }

    if (SDEMMC_W_PRV_CSD_VERSION_1_0 == csd_version)
    {
        /* Get the minimum erasable unit (in 512 byte sectors). */
        p_ctrl->device.erase_sector_count = p_csd_reg->csd_v1_b.sector_size + 1U;
    }
    else
 #endif
    {
        /* For SDHC and SDXC cards, there are no erase group restrictions.
         * Using the eMMC TRIM operation, there are no erase group restrictions. */
        p_ctrl->device.erase_sector_count = 1U;
    }

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE || SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

/*******************************************************************************************************************//**
 * Calls user callback
 *
 * @param[in]     p_ctrl    Pointer to the instance control block.
 * @param[in]     p_args    Pointer to callback arguments with event and response set.
 **********************************************************************************************************************/
static void r_sdemmc_call_callback (sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args)
{
    /* Call user callback if provided, if an event was determined, and if the driver is initialized. */
    if (NULL != p_ctrl->p_callback)
    {
        sdmmc_callback_args_t args;

        /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
         * stored in non-secure memory so they can be accessed by a non-secure callback function. */
        sdmmc_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;

        if (NULL == p_args_memory)
        {
            /* Use provided args struct on stack */
            p_args_memory = p_args;
        }
        else
        {
            /* Save current arguments on the stack in case this is a nested interrupt. */
            args = *p_args_memory;

            /* Copy the stacked args to callback memory */
            *p_args_memory = *p_args;
        }

        p_args_memory->p_context = p_ctrl->p_context;

        /* If the project is not Trustzone Secure,
         * then it will never need to change security state in order to call the callback. */
        p_ctrl->p_callback(p_args_memory);

        if (NULL != p_ctrl->p_callback_memory)
        {
            /* Restore callback memory in case this is a nested interrupt. */
            *p_ctrl->p_callback_memory = args;
        }
    }
}

/*******************************************************************************************************************//**
 * Calls user callback after response or data transfer complete.
 **********************************************************************************************************************/
void sdhimmc_accs_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    sdmmc_callback_args_t args;
    memset(&args, 0U, sizeof(args));
    r_sdemmc_access_irq_process(p_ctrl, &args);

    /* Call user callback */
    if (((p_ctrl->initialized) && (0U != args.event)) ||
        (0U != (args.event & (SDMMC_EVENT_CARD_INSERTED | SDMMC_EVENT_CARD_REMOVED))))
    {
        r_sdemmc_call_callback(p_ctrl, &args);
    }

    if (0 != (args.event & SDMMC_EVENT_CARD_REMOVED))
    {
        p_ctrl->initialized = false;
    }

#if BSP_FEATURE_BSP_HAS_ICU

    /* Clear the IR flag in the ICU */
    /* Clearing the IR bit must be done after clearing the interrupt source in the the peripheral */
    R_BSP_IrqStatusClear(irq);
#endif                                 /* BSP_FEATURE_BSP_HAS_ICU */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Calls callback and clears interrupt flags.
 **********************************************************************************************************************/
void sdhimmc_sdio_isr (void)
{
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    sdemmc_w_instance_ctrl_t * p_ctrl = (sdemmc_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Determine the source of the interrupt. */
    sdmmc_callback_args_t args;
    memset(&args, 0U, sizeof(args));
    uint32_t info1 = p_ctrl->p_reg->SDIO_GLB_INT_STS_REG;

    if (info1 & SDEMMC_W_PRV_SDIO_INFO1_FN0_INT_TO_ARM_MASK)
    {
        /* Disable the GLB_INT_ENA Register */
        p_ctrl->p_reg->SDIO_GLB_INT_ENA_REG = (~SDEMMC_W_PRV_SDIO_INFO1_VALUE_GLB_INT_ENA & 0x3);

        /* Clear the Global INT STS Register Value */
        p_ctrl->p_reg->SDIO_GLB_INT_STS_REG = SDEMMC_W_PRV_SDIO_INFO1_FN0_INT_TO_ARM_MASK;
        r_sdemmc_handle_interrupt_fn0(p_ctrl);

        /* Enable the GLB INT ENA Register */
        p_ctrl->p_reg->SDIO_GLB_INT_ENA_REG = (SDEMMC_W_PRV_SDIO_INFO1_VALUE_GLB_INT_ENA & 0x3);
    }

    if (info1 & SDEMMC_W_PRV_SDIO_INFO1_FN1_INT_TO_ARM_MASK)
    {
        /* Disable the GLB_INT_ENA Register */
        p_ctrl->p_reg->SDIO_GLB_INT_ENA_REG = (~SDEMMC_W_PRV_SDIO_INFO1_VALUE_GLB_INT_ENA & 0x3);

        /* Clear the Global INT STS Register Value */
        p_ctrl->p_reg->SDIO_GLB_INT_STS_REG = SDEMMC_W_PRV_SDIO_INFO1_FN1_INT_TO_ARM_MASK;
        r_sdemmc_handle_interrupt_fn1(p_ctrl, &args);

        /* Enable the GLB INT ENA Register */
        p_ctrl->p_reg->SDIO_GLB_INT_ENA_REG = (SDEMMC_W_PRV_SDIO_INFO1_VALUE_GLB_INT_ENA & 0x3);
    }

    /* I/O interrupt requested by device. */
    args.event |= SDMMC_EVENT_SDIO;

    /* Call user callback */
    if (p_ctrl->initialized)
    {
        r_sdemmc_call_callback(p_ctrl, &args);
    }

    /* Clear interrupt flags */
    p_ctrl->p_reg->SDIO_GLB_INT_STS_REG = SDEMMC_W_PRV_SDIO_INFO1_IRQ_CLEAR;

 #if BSP_FEATURE_BSP_HAS_ICU

    /* Clear the IR flag in the ICU */
    /* Clearing the IR bit must be done after clearing the interrupt source in the the peripheral */
    R_BSP_IrqStatusClear(irq);
 #endif                                /* BSP_FEATURE_BSP_HAS_ICU */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
}

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

static void r_sdemmc_handle_interrupt_fn0 (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    uint32_t status = 0;
    uint32_t mask   = 0;

    /* Read the AHB FN0 INT Register */
    status = p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG;

    if (SDEMMC_W_AHBSOFT_RST == (status & SDEMMC_W_AHBSOFT_RST)) /* Check soft reset interrupt */
    {
        /* Clear the AHBSOFT_RST INTerrupt. Write 1 to clear the INTerrupt */
        status = p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG;
        p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG  = (status | SDEMMC_W_AHBSOFT_RST);
        p_ctrl->p_reg->SDIO_SOFT_RST_AHB_REG = (SDEMMC_W_VALUE_SOFT_RST_AHB & 0x1);
    }

    if (SDEMMC_W_VOLT_SWITCH_CMD == (status & SDEMMC_W_VOLT_SWITCH_CMD)) /* Check volt switch cmd interrupt */
    {
        mask = p_ctrl->p_reg->SDIO_UHS_SUPPORT_REG;
        mask = mask | (SDEMMC_W_CARD_VOLT_ACCEPT);
        p_ctrl->p_reg->SDIO_UHS_SUPPORT_REG = mask;

        /* Clear the VOLT_SWITCH_CMD INTerrupt. Write 1 to clear the INTerrupt */
        status = p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG;
        p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG = (status | SDEMMC_W_VOLT_SWITCH_CMD);
    }
}

static void r_sdemmc_handle_interrupt_fn1 (sdemmc_w_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args)
{
    uint32_t status    = 0;
    uint32_t mask      = 0;
    uint32_t blksize   = 0;
    uint32_t mul_blk   = 0;
    uint32_t b_blk_cnt = 0;
    uint32_t length    = 0;

    /* Read the AHB FN1 INT Register */
    status = p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG;

    if (SDEMMC_W_FN1_WR_OVR == (status & SDEMMC_W_FN1_WR_OVR)) /* Check for fn1 wr over interrupt */
    {
        p_ctrl->result.sdio_blk_or_byte =
            p_ctrl->p_reg->SDIO_BLKSIZE_REG_b.SIN_MUL_BLK;
        p_ctrl->result.sdio_blk_size =
            p_ctrl->p_reg->SDIO_BLKSIZE_REG_b.BLK_SIZE;
        p_ctrl->result.sdio_blk_count =
            p_ctrl->p_reg->SDIO_WRBLKCNT_REG_b.WR_BLK_CNT;

        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_WR_OVR);
        p_ctrl->p_reg->SDIO_WRBLKCNT_REG    = 0;
        p_args->event |= SDEMMC_W_PRIV_EVENT_SDIO_FN1_WR_OVR;
    }

    if (SDEMMC_W_FN1_RD_OVR == (status & SDEMMC_W_FN1_RD_OVR)) /* Check for fn1 rd over interrupt */
    {
        p_ctrl->result.sdio_blk_or_byte =
            p_ctrl->p_reg->SDIO_BLKSIZE_REG_b.SIN_MUL_BLK;
        p_ctrl->result.sdio_blk_size =
            p_ctrl->p_reg->SDIO_BLKSIZE_REG_b.BLK_SIZE;
        p_ctrl->result.sdio_blk_count =
            p_ctrl->p_reg->SDIO_RDBLKCNT_REG_b.RD_BLK_CNT;

        /* Clear the fn1_rd_ovr INTerrupt. Write 1 to clear the INTerrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_RD_OVR);
        p_ctrl->p_reg->SDIO_RDBLKCNT_REG    = 0;
        p_args->event |= SDEMMC_W_PRIV_EVENT_SDIO_FN1_RD_OVR;
    }

    if (SDEMMC_W_FN1_RD_ERROR == (status & SDEMMC_W_FN1_RD_ERROR))
    {
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_RD_ERROR);
    }

    if (SDEMMC_W_FN1_RST == (status & SDEMMC_W_FN1_RST))
    {
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_RST);
    }

    if (SDEMMC_W_FN1_MSG_RDY == (status & SDEMMC_W_FN1_MSG_RDY)) /* Check for sd host fn1 msg ready interrupt */
    {
        /* Read the sd host general purpose register */
        mask = p_ctrl->p_reg->SDIO_SD_HOST_GP_REG;

        /* Clear the sdhost fn1 msg ready interrupt. Write 1 to clear the interrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_MSG_RDY);
        p_args->event |= SDEMMC_W_PRIV_EVENT_SDIO_FN1_MSG_RDY;
    }

    if (SDEMMC_W_FN1_ACK_TO_ARM == (status & SDEMMC_W_FN1_ACK_TO_ARM))
    {
        /* Clear the fn1 ack to arm interrupt. Write 1 to clear the interrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_ACK_TO_ARM);
        p_args->event |= SDEMMC_W_PRIV_EVENT_SDIO_FN1_ACK_TO_ARM;
    }

    if (SDEMMC_W_FN1_SDIO_RD_STRT == (status & SDEMMC_W_FN1_SDIO_RD_STRT)) /* Check fn1 sdio rd start interrupt */
    {
        /* Reading blksize Register */
        mask    = p_ctrl->p_reg->SDIO_BLKSIZE_REG;
        blksize = (mask & SDEMMC_W_BLKSIZE_MASK);
        mul_blk = (mask >> SDEMMC_W_MUL_BLK_SHIFT);

        /* Reading Argument Register */
        mask      = p_ctrl->p_reg->SDIO_ARGUMENT_REG;
        b_blk_cnt = (mask & SDEMMC_W_B_BLK_CNT_MASK);

        /* Calculating the data length */
        if (1 == mul_blk)
        {
            length = b_blk_cnt * blksize;
        }
        else
        {
            if (0 == b_blk_cnt)
            {
                b_blk_cnt = SDEMMC_W_PRV_SDIO_EXT_MAX_BYTES;
            }

            length = b_blk_cnt;
        }

        r_sdemmc_host_read(p_ctrl, length);

        /* Clear the fn1_sdio_rd_strt INTerrupt. Write 1 to clear the INTerrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_SDIO_RD_STRT);
    }

    if (SDEMMC_W_FN1_SDIO_WR_STRT == (status & SDEMMC_W_FN1_SDIO_WR_STRT)) /* Check for fn1 wr strt interrupt */
    {
        /* Reading Blksize Register */
        mask    = p_ctrl->p_reg->SDIO_BLKSIZE_REG;
        blksize = (mask & SDEMMC_W_BLKSIZE_MASK);
        mul_blk = (mask >> SDEMMC_W_MUL_BLK_SHIFT);

        /* Reading Argument Register */
        mask      = p_ctrl->p_reg->SDIO_ARGUMENT_REG;
        b_blk_cnt = (mask & SDEMMC_W_B_BLK_CNT_MASK);

        /* Calculating the data length */
        if (mul_blk == 1)
        {
            length = b_blk_cnt * blksize;
        }
        else
        {
            if (0 == b_blk_cnt)
            {
                b_blk_cnt = SDEMMC_W_PRV_SDIO_EXT_MAX_BYTES;
            }

            length = b_blk_cnt;
        }

        r_sdemmc_host_write(p_ctrl, length);

        /* Clear the fn1_sdio_wr_strt INTerrupt. Write 1 to clear the interrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_SDIO_WR_STRT);
    }

    if (SDEMMC_W_FN1_ADMA_END == (status & SDEMMC_W_FN1_ADMA_END)) /* Check for fn1_adma_end_bit interrupt */
    {
        /* Update the new System Address */
        /* sets the dummy descriptor */
        r_sdemmc_adma_dummy(p_ctrl);

        /* Clear the fn1_adma_end INTerrupt. Write 1 to clear the INTerrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_ADMA_END);
    }

    if (SDEMMC_W_FN1_SUSPEND == (status & SDEMMC_W_FN1_SUSPEND))
    {
        /* Clear the fn1 ack to arm interrupt. Write 1 to clear the interrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_SUSPEND);
    }

    if (SDEMMC_W_FN1_RESUME == (status & SDEMMC_W_FN1_RESUME))
    {
        /* Clear the fn1 ack to arm interrupt. Write 1 to clear the interrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_RESUME);
    }

    if (SDEMMC_W_FN1_ADMA_INT == (status & SDEMMC_W_FN1_ADMA_INT))
    {
        /* Clear the fn1 ack to arm interrupt. Write 1 to clear the interrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_ADMA_INT);
    }

    if (SDEMMC_W_FN1_ADMA_ERR == (status & SDEMMC_W_FN1_ADMA_ERR))
    {
        r_sdemmc_adma_dummy(p_ctrl);
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_ADMA_ERR);
    }

    if (SDEMMC_W_FN1_READY == (status & SDEMMC_W_FN1_READY))
    {
        /* Clear the fn1 ack to arm interrupt. Write 1 to clear the interrupt */
        p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_FN1_READY);
    }
}

/* this function is called after ADMA done */
static void r_sdemmc_adma_dummy (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    volatile sdio_device_dma_config dummy_dma_config;
    dummy_dma_config.sdio_dma_length = (SDEMMC_W_DUMMY_DESC_LEN << 16) | SDEMMC_W_ATTRIBUTE_DUMMY_DESC;

    /* Update the fetch address in ADMA System Address register */
    p_ctrl->p_reg->SDIO_ADMA_SYSTEM_ADDRESS_REG = (uint32_t) (&dummy_dma_config) | 0x20000000;
}

static void r_sdemmc_host_read (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t host_length)
{
    uint32_t device_length;
    uint32_t attribute = SDEMMC_W_ATTRIBUTE;

    device_length = (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_tx.sdio_dma_length >> 16) &
                    0x0000FFFF;
    if (host_length <= device_length)
    {
        device_length = host_length;
    }
    else
    {
        attribute = SDEMMC_W_ATTRIBUTE_TRANS_ERROR;
    }

    ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_tx.sdio_dma_length = (device_length << 16) |
                                                                                           attribute;
    p_ctrl->p_reg->SDIO_AHB_TRANSCOUNT_REG = device_length;

    /* Update the fetch address in ADMA System Address register */
    p_ctrl->p_reg->SDIO_ADMA_SYSTEM_ADDRESS_REG =
        (uint32_t) (&((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_tx) | 0x20000000;

    if (attribute == SDEMMC_W_ATTRIBUTE_TRANS_ERROR)
    {
        r_sdemmc_adma_dummy(p_ctrl);
    }
}

static void r_sdemmc_host_write (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t host_length)
{
    uint32_t device_length;
    uint32_t attribute = SDEMMC_W_ATTRIBUTE;

    device_length =
        (uint16_t) (((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_rx.sdio_dma_length >> 16);
    if (host_length <= device_length)
    {
        device_length = host_length;
    }
    else
    {
        attribute = SDEMMC_W_ATTRIBUTE_TRANS_ERROR;
    }

    ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_rx.sdio_dma_length = (device_length << 16) |
                                                                                           attribute;

    /* Update the fetch address in ADMA System Address register */
    p_ctrl->p_reg->SDIO_ADMA_SYSTEM_ADDRESS_REG =
        (uint32_t) (&((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_rx) | 0x20000000;
}

#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

static void r_sdemmc_hw_sdemmc_renable_prepare (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    g_DataTransferWidth         = p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth;
    g_ExtendedDataTransferWidth = p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.ExtendedDataTransferWidth;
    g_SDCLKFrequencySelect      = p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDCLKFrequencySelect;
    g_DriveStrengthSelect       = p_ctrl->p_reg_mmc->SDEMMC_AUTOCMDERRORSTATUS_REG_b.DriveStrengthSelect;
}

static void r_sdemmc_hw_sdemmc_renable (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    volatile uint8_t rdata = 0;

    CRG_PER->SET_CLK_COM_REG_b.SDEMMC_ENABLE = 1U;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 1;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 0;

    while (0x0F00 != (p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG & 0xF00))
    {
        p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG |= 0x0F00;
    }

    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst = 1;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst = 0;

    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.SpiMode = 0;

    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.LEDControl        = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth = (g_DataTransferWidth &
                                                                     SDEMMC_W_1BIT_MASK);
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HighSpeedEnable           = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DMASelect                 = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.ExtendedDataTransferWidth = (g_ExtendedDataTransferWidth &
                                                                             SDEMMC_W_1BIT_MASK);
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.CardDetectTestLevel       = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.CardDetectSignalSelection = 0;

    p_ctrl->p_reg_mmc->SDEMMC_VENDOR_REG_b.AutoGateSDCLK = 1;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.InternalClockEnable             = 1;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDCLKFrequencySelect            = (uint8_t) g_SDCLKFrequencySelect;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.UpperBitsofSDCLKFrequencySelect = 0;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.ClockGeneratorSelect            = 1;

    /* increase drive strength to 12mA */
    p_ctrl->p_reg_mmc->SDEMMC_AUTOCMDERRORSTATUS_REG_b.DriveStrengthSelect = (g_DriveStrengthSelect &
                                                                              SDEMMC_W_2BIT_MASK);

    do
    {
        rdata = p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.InternalClockStable;
    } while (0 == rdata);
}

static void r_sdemmc_hw_sdemmc_enable (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    uint8_t rdata = 0;

    CRG_PER->SET_CLK_COM_REG_b.SDEMMC_ENABLE = 1U;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 1;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 0;

    while (0x0F00 != (p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG & 0xF00))
    {
        p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG |= 0x0F00;
    }

    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst = 1;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst = 0;

    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.SpiMode = 0;

    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.LEDControl                = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DataTransferWidth         = SDEMMC_W_SDEMMC_DT_WIDTH_1BIT;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HighSpeedEnable           = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.DMASelect                 = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.ExtendedDataTransferWidth = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.CardDetectTestLevel       = 0;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.CardDetectSignalSelection = 0;

    p_ctrl->p_reg_mmc->SDEMMC_VENDOR_REG_b.AutoGateSDCLK = 1;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.InternalClockEnable             = 1;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDCLKFrequencySelect            = SDEMMC_W_PRV_SD_CLK_CTRL_DEFAULT;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.UpperBitsofSDCLKFrequencySelect = 0;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.ClockGeneratorSelect            = 1;

    /* increase drive strength to 12mA */
    p_ctrl->p_reg_mmc->SDEMMC_AUTOCMDERRORSTATUS_REG_b.DriveStrengthSelect = 0;

    do
    {
        rdata = p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.InternalClockStable;
    } while (0 == rdata);
}

static void r_sdemmc_hw_sdemmc_disable (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    CRG_PER->SET_CLK_COM_REG_b.SDEMMC_ENABLE = 1U;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 1;
    p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst         = 1;
}

static void r_sdemmc_sdemmc_interrupt_enable (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    while (1 != p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb)
    {
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb = 1;
    }

    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.DataTimeoutErrorSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.DataTimeoutErrorStatusEnb = 1;

    /* Configure card detection. */
    if (SDMMC_CARD_DETECT_CD == p_ctrl->p_cfg->card_detect)
    {
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardInterruptSignalEnb = 1;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardInterruptStatusEnb = 1;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardInsertionSignalEnb = 1;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardInsertionStatusEnb = 1;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CardRemovalSignalEnb   = 1;
        p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CardRemovalStatusEnb   = 1;
    }

    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCRCErrorSignalEnb     = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCRCErrorStatusEnb     = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandTimeoutErrorSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandTimeoutErrorStatusEnb = 1;
}

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

static void r_sdemmc_hw_sdio_device_init (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    GPIO->SDIO_MODE_REG_b.CFG_DRV          = ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->drive_current;
    CRG_PER->SET_CLK_COM_REG_b.SDIO_ENABLE = 1U;
    memcpy((void *) SDEMMC_W_CIS0_AHB_ADDR, (const void *) gs_sdio_b_cis0_data, sizeof(gs_sdio_b_cis0_data));
    memcpy((void *) SDEMMC_W_CIS1_AHB_ADDR, (const void *) gs_sdio_b_cis1_data, sizeof(gs_sdio_b_cis1_data));

    p_ctrl->p_reg->SDIO_SOFT_RST_AHB_REG_b.AHBSOFT_VALID = 0x1U;
    p_ctrl->p_reg->SDIO_SOFT_RST_AHB_REG_b.AHBSOFT_VALID = 0x0U;

    /* Program the CCCR Register */
    p_ctrl->p_reg->SDIO_CCCR_REG = (((SDEMMC_W_SHS & 0x1) << 21) | ((SDEMMC_W_SMPC & 0x1) << 20) |
                                    ((SDEMMC_W_BLS & 0x1) << 19) | ((SDEMMC_W_LSC & 0x1) << 18) |
                                    ((SDEMMC_W_S4MI & 0x1) << 17) | ((SDEMMC_W_SBS & 0x1) << 16) |
                                    ((SDEMMC_W_SRW & 0x1) << 15) | ((SDEMMC_W_SMB & 0x1) << 14) |
                                    ((SDEMMC_W_SDC & 0x1) << 13) | ((SDEMMC_W_SCSI & 0x1) << 12) |
                                    (((SDEMMC_W_SD_PHY_SPEC) & 0xF) << 8) |
                                    (((SDEMMC_W_SDIO_REV) & 0xF) << 4) | ((SDEMMC_W_CCCR_REV) & 0xF));

    /* Program the OCR(For Function1) Register */
    p_ctrl->p_reg->SDIO_OCR_REG = (SDEMMC_W_VALUE_OCR & 0xFFFFFF);

    /* Program the GLB_INT_ENA Register */
    p_ctrl->p_reg->SDIO_GLB_INT_ENA_REG = (SDEMMC_W_VALUE_GLB_INT_ENA & 0x3);

    /* Program the AHB_FN0_INT_ENABLE */
    p_ctrl->p_reg->SDIO_AHB_FN0_INT_ENABLE_REG = (SDEMMC_W_VALUE_AHB_FN0_INT_ENA & 0x0003);

    /* Program the AHB_FN0_INT_STS_ENABLE */
    p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG = (SDEMMC_W_VALUE_AHB_FN0_INT_ENA & 0x0003);

    /* Program the AHB_FN1_INT_ENABLE */
    p_ctrl->p_reg->SDIO_AHB_FN1_INT_ENABLE_REG = (SDEMMC_W_VALUE_AHB_FN1_INT_ENA & 0x11C3);

    /* Program the AHB_FN1_INT_STS_ENABLE */
    p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG = (SDEMMC_W_VALUE_AHB_FN1_INT_ENA & 0x11C3);

    /* Program the FBR Register - For Function1 */
    p_ctrl->p_reg->SDIO_FBR_REG = (SDEMMC_W_VALUE_FBR & 0x3FFF);

    /* Program the IOR Register - For Function1 */
    p_ctrl->p_reg->SDIO_IOR_REG = (SDEMMC_W_VALUE_IOR & 0x1);

    /* Program the GLB_INT_STS Register - For Function0/1 */
    p_ctrl->p_reg->SDIO_GLB_INT_STS_REG = (SDEMMC_W_VALUE_INT_COND & 0x3);

    /* Program the FUNRDY - to indicate card is readt to operate */
    p_ctrl->p_reg->SDIO_FUNRDY_REG = (SDEMMC_W_VALUE_FUNRDY & 0x1);
}

static uint32_t r_sdemmc_hw_sdio_device_rx (sdemmc_w_instance_ctrl_t * p_ctrl, uint8_t * data, uint32_t length)
{
    ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_rx.sdio_dma_length =
        (length << 16) | SDEMMC_W_ATTRIBUTE;
    ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_rx.sdio_dma_buf_address = (uint32_t) data;

    return FSP_SUCCESS;
}

static uint32_t r_sdemmc_hw_sdio_device_tx (sdemmc_w_instance_ctrl_t * p_ctrl, const uint8_t * data, uint32_t length)
{
    /* Program the AHB transfer count register */
    p_ctrl->p_reg->SDIO_AHB_TRANSCOUNT_REG = (length & 0x1FFFFF);

    /* Program the Read data ready register */
    p_ctrl->p_reg->SDIO_RDDATRDY_REG = SDEMMC_W_FN1_RD_DAT_RDY;

    ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_tx.sdio_dma_length =
        (length << 16) | SDEMMC_W_ATTRIBUTE;
    ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->dma_config_tx.sdio_dma_buf_address = (uint32_t) data;

    return FSP_SUCCESS;
}

static void r_sdemmc_hw_sdio_device_deinit (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    CRG_PER->SET_CLK_COM_REG_b.SDIO_ENABLE               = 1U;
    p_ctrl->p_reg->SDIO_SOFT_RST_AHB_REG_b.AHBSOFT_VALID = 0x1U;
    p_ctrl->p_reg->SDIO_SOFT_RST_AHB_REG_b.AHBSOFT_VALID = 0x0U;
}

#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

static fsp_err_t r_sdemmc_sdemmc_wait_for_complete_interrupt (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t * resp)
{
    uint32_t timeout = UINT16_MAX;

    while ((0 == p_ctrl->sdemmc_w_event.bit.response_end) &&
           (0 == p_ctrl->sdemmc_w_event.bit.CommandTimeoutError) &&
           (0 == p_ctrl->sdemmc_w_event.bit.crc_err))
    {
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;

        if ((0 == timeout) || (p_ctrl->sdemmc_w_event.bit.CommandTimeoutError) || (p_ctrl->sdemmc_w_event.bit.crc_err))
        {
            r_sdemmc_hw_sdemmc_renable_prepare(p_ctrl);
            CRG_PER->SET_CLK_COM_REG_b.SDEMMC_ENABLE = 1U;
            p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 1;
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst         = 1;
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);
            r_sdemmc_hw_sdemmc_renable(p_ctrl);
            r_sdemmc_sdemmc_interrupt_enable(p_ctrl);

            FSP_RETURN(FSP_ERR_TIMEOUT);
        }
    }

    if (NULL != resp)
    {
        *resp = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE0_REG;
    }

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_sdemmc_wait_for_transfer_interrupt (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    uint32_t timeout = UINT16_MAX;

    while ((0 == p_ctrl->sdemmc_w_event.bit.access_end) &&
           (0 == p_ctrl->sdemmc_w_event.bit.dto) &&
           (0 == p_ctrl->sdemmc_w_event.bit.CommandTimeoutError) &&
           (0 == p_ctrl->sdemmc_w_event.bit.crc_err))
    {
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;

        if (0 == timeout)
        {
            r_sdemmc_hw_sdemmc_renable_prepare(p_ctrl);
            CRG_PER->SET_CLK_COM_REG_b.SDEMMC_ENABLE = 1U;
            p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 1;
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst         = 1;
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);
            r_sdemmc_hw_sdemmc_renable(p_ctrl);
            r_sdemmc_sdemmc_interrupt_enable(p_ctrl);

            FSP_RETURN(FSP_ERR_TIMEOUT);
        }
    }

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_sdemmc_wait_write_done (sdemmc_w_instance_ctrl_t * p_ctrl)
{
    uint32_t timeout = UINT16_MAX;

    while (0xF != p_ctrl->p_reg_mmc->SDEMMC_PRESENTSTATE_REG_b.DAT3TO0LineSignalLevel)
    {
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;

        if (0 == timeout)
        {
            r_sdemmc_hw_sdemmc_renable_prepare(p_ctrl);
            CRG_PER->SET_CLK_COM_REG_b.SDEMMC_ENABLE = 1U;
            p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SoftwareResetForAll = 1;
            p_ctrl->p_reg_mmc->SDEMMC_HOST_CTRL_1_REG_b.HardwareRst         = 1;
            R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);
            r_sdemmc_hw_sdemmc_renable(p_ctrl);
            r_sdemmc_sdemmc_interrupt_enable(p_ctrl);

            FSP_RETURN(FSP_ERR_TIMEOUT);
        }
    }

    return FSP_SUCCESS;
}

#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)

static void r_sdemmc_emmc_cmd_without_res (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t cmd, uint32_t cmd_arg)
{
    uint32_t transfer_reg = 0;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;
    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = 0;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = 0;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = 0;
    g_BlockCountForCurrentTransfer        = 0;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;

    r_sdemmc_sdemmc_wait_for_complete_interrupt(p_ctrl, NULL);
}

#endif                                 /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */

static fsp_err_t r_sdemmc_emmc_cmd_with_res (sdemmc_w_instance_ctrl_t * p_ctrl,
                                             uint32_t                   cmd,
                                             uint32_t                   cmd_arg,
                                             uint32_t                 * rsp)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint32_t  transfer_reg = 0;
    uint32_t  check_option = 0;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;
    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = 0;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = 0;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = 0;
    g_BlockCountForCurrentTransfer        = 0;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb = 1;

    switch (SDEMMC_W_GET_CMD_RESP_TYPE(cmd))
    {
        case SDEMMC_W_SDIO_NO_RESPONSE:
        case SDEMMC_W_SDIO_SHORT_RESPONSE:
        {
            check_option = 0;
            break;
        }

        case SDEMMC_W_SDIO_LONG_RESPONSE:
        {
            check_option = SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk;
            break;
        }

        case 3:
        case 4:
        {
            check_option = SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                           SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk;
            break;
        }

        default:
        {
            FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
        }
    }

    transfer_reg = (uint32_t) (cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos) |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   check_option;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG        = transfer_reg;
    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;

    err = r_sdemmc_sdemmc_wait_for_complete_interrupt(p_ctrl, rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (SDEMMC_W_SDIO_LONG_RESPONSE == SDEMMC_W_GET_CMD_RESP_TYPE(cmd))
    {
        uint32_t temp_rsp[4];
        temp_rsp[0] = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE3_REG;
        temp_rsp[1] = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE2_REG;
        temp_rsp[2] = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE1_REG;
        temp_rsp[3] = p_ctrl->p_reg_mmc->SDEMMC_RESPONSE0_REG;
        rsp[0]      = temp_rsp[0] << 8 | ((temp_rsp[1] & 0xff000000) >> 24);
        rsp[1]      = temp_rsp[1] << 8 | ((temp_rsp[2] & 0xff000000) >> 24);
        rsp[2]      = temp_rsp[2] << 8 | ((temp_rsp[3] & 0xff000000) >> 24);
        rsp[3]      = temp_rsp[3] << 8;
    }

    return FSP_SUCCESS;
}

#if (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE)

static fsp_err_t r_sdemmc_emmc_single_read_data_with_wait (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                           uint32_t                   cmd,
                                                           uint32_t                   cmd_arg,
                                                           uint32_t                   blk_size,
                                                           uint32_t                 * p_rsp,
                                                           uint8_t                  * p_buf)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint32_t  transfer_reg = 0;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG     = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize = blk_size & SDEMMC_W_12BIT_MASK;

    /*
     *  000b - 4KB(Detects A11 Carry out)
     *  001b - 8KB(Detects A12 Carry out)
     *  010b - 16KB(Detects A13 Carry out)
     *  011b - 32KB(Detects A14 Carry out)
     *  100b - 64KB(Detects A15 Carry out)
     *  101b - 128KB(Detects A16 Carry out)
     *  110b - 256KB(Detects A17 Carry out)
     *  111b - 512KB(Detects A18 Carry out)
     */
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = 1;
    g_BlockCountForCurrentTransfer        = 1;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt and access end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataTransferDirectionSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;
    err = r_sdemmc_sdemmc_wait_for_complete_interrupt(p_ctrl, p_rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdemmc_wait_for_transfer_interrupt(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdemmc_wait_write_done(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_emmc_single_read_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                 uint32_t                   cmd,
                                                 uint32_t                   cmd_arg,
                                                 uint32_t                   blk_size,
                                                 uint32_t                 * p_rsp,
                                                 uint8_t                  * p_buf)
{
    FSP_PARAMETER_NOT_USED(p_rsp);
    uint32_t transfer_reg = 0;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG     = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize = blk_size & SDEMMC_W_12BIT_MASK;

    /*
     *  000b - 4KB(Detects A11 Carry out)
     *  001b - 8KB(Detects A12 Carry out)
     *  010b - 16KB(Detects A13 Carry out)
     *  011b - 32KB(Detects A14 Carry out)
     *  100b - 64KB(Detects A15 Carry out)
     *  101b - 128KB(Detects A16 Carry out)
     *  110b - 256KB(Detects A17 Carry out)
     *  111b - 512KB(Detects A18 Carry out)
     */
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = 1;
    g_BlockCountForCurrentTransfer        = 1;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt and access end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataTransferDirectionSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_emmc_multi_read_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                uint32_t                   cmd,
                                                uint32_t                   cmd_arg,
                                                uint32_t                 * p_rsp,
                                                uint8_t                  * p_buf,
                                                uint32_t                   block_count)
{
    uint32_t  ret_rsp      = 0;
    uint32_t  transfer_reg = 0;
    fsp_err_t err          = FSP_SUCCESS;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = 512;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = (uint16_t) block_count;
    g_BlockCountForCurrentTransfer = block_count;

    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt and access end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_MultiSingleBlockSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataTransferDirectionSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_BlockCountEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;
    err = r_sdemmc_sdemmc_wait_for_complete_interrupt(p_ctrl, p_rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdemmc_wait_for_transfer_interrupt(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_STOP_TRANSM, 0, &ret_rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_emmc_block_read_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                uint32_t                   cmd,
                                                uint32_t                   cmd_arg,
                                                uint32_t                 * p_rsp,
                                                uint8_t                  * p_buf,
                                                uint32_t                   block_count)
{
    FSP_PARAMETER_NOT_USED(p_rsp);
    uint32_t  ret_rsp      = 0;
    uint32_t  transfer_reg = 0;
    fsp_err_t err          = FSP_SUCCESS;
    int32_t   i            = 0;

    /* send CMD23 */
    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SET_BLK_CNT, (block_count & 0x0000ffff), &ret_rsp);

        if ((!err) && !(ret_rsp & 0xfff80000))
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_WRITE_FAILED);
    }

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = 512;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = (uint16_t) block_count;
    g_BlockCountForCurrentTransfer        = block_count;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt and access end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_MultiSingleBlockSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataTransferDirectionSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_BlockCountEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_emmc_single_write_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                  uint32_t                   cmd,
                                                  uint32_t                   cmd_arg,
                                                  uint32_t                   blk_size,
                                                  uint32_t                 * p_rsp,
                                                  uint8_t                  * p_buf)
{
    FSP_PARAMETER_NOT_USED(p_rsp);
    uint32_t transfer_reg = 0;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG     = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize = blk_size & SDEMMC_W_12BIT_MASK;

    /*
     *  000b - 4KB(Detects A11 Carry out)
     *  001b - 8KB(Detects A12 Carry out)
     *  010b - 16KB(Detects A13 Carry out)
     *  011b - 32KB(Detects A14 Carry out)
     *  100b - 64KB(Detects A15 Carry out)
     *  101b -128KB(Detects A16 Carry out)
     *  110b - 256KB(Detects A17 Carry out)
     *  111b - 512KB(Detects A18 Carry out)
     */
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry = 7;

    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = 1;
    g_BlockCountForCurrentTransfer        = 1;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    SDEMMC->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_emmc_multi_write_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                 uint32_t                   cmd,
                                                 uint32_t                   cmd_arg,
                                                 uint32_t                 * p_rsp,
                                                 uint8_t                  * p_buf,
                                                 uint32_t                   block_count)
{
    uint32_t  ret_rsp      = 0;
    uint32_t  transfer_reg = 0;
    fsp_err_t err          = FSP_SUCCESS;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = 512;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = (uint16_t) block_count;
    g_BlockCountForCurrentTransfer = block_count;

    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_MultiSingleBlockSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_BlockCountEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;
    err = r_sdemmc_sdemmc_wait_for_complete_interrupt(p_ctrl, p_rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdemmc_wait_for_transfer_interrupt(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_STOP_TRANSM, 0, &ret_rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdemmc_wait_write_done(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_emmc_block_write_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                 uint32_t                   cmd,
                                                 uint32_t                   cmd_arg,
                                                 uint32_t                 * p_rsp,
                                                 uint8_t                  * p_buf,
                                                 uint32_t                   block_count)
{
    FSP_PARAMETER_NOT_USED(p_rsp);
    uint32_t  ret_rsp      = 0;
    uint32_t  transfer_reg = 0;
    fsp_err_t err          = FSP_SUCCESS;
    int32_t   i            = 0;

    /* send CMD23 */
    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SET_BLK_CNT, (block_count & 0x0000ffff), &ret_rsp);

        if ((!err) && !(ret_rsp & 0xfff80000))
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_WRITE_FAILED);
    }

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = 512;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = (uint16_t) block_count;
    g_BlockCountForCurrentTransfer        = block_count;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_MultiSingleBlockSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_BlockCountEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;

    return FSP_SUCCESS;
}

#endif                                 /* (SDEMMC_W_CFG_SD_SUPPORT_ENABLE | SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE) */

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_sdio_block_read_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                uint32_t                   cmd,
                                                uint32_t                   cmd_arg,
                                                uint32_t                 * p_rsp,
                                                uint8_t                  * p_buf,
                                                uint32_t                   block_size,
                                                uint32_t                   block_count)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint32_t  transfer_reg = 0;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = (block_size & SDEMMC_W_12BIT_MASK);
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = (uint16_t) block_count;
    g_BlockCountForCurrentTransfer        = block_count;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt and access end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_MultiSingleBlockSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataTransferDirectionSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_BlockCountEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;
    err = r_sdemmc_sdemmc_wait_for_complete_interrupt(p_ctrl, p_rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdemmc_wait_for_transfer_interrupt(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_sdio_multi_write_data (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                 uint32_t                   cmd,
                                                 uint32_t                   cmd_arg,
                                                 uint32_t                 * p_rsp,
                                                 uint8_t                  * p_buf,
                                                 uint32_t                   block_size,
                                                 uint32_t                   block_count)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint32_t  transfer_reg = 0;

    /* Clear Status */
    p_ctrl->sdemmc_w_event.word = 0U;

    p_ctrl->p_reg_mmc->SDEMMC_SDMA_SYS_ADDR__ARGU_2_REG                = (uint32_t) p_buf;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.TransferBlockSize            = (block_size & SDEMMC_W_12BIT_MASK);
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.HostSDMABufferBoundry        = 7;
    p_ctrl->p_reg_mmc->SDEMMC_BLOCK_REG_b.BlockCountForCurrentTransfer = (uint16_t) block_count;
    g_BlockCountForCurrentTransfer        = block_count;
    p_ctrl->p_reg_mmc->SDEMMC__ARGU_1_REG = cmd_arg;

    /* Enable response end interrupt and access end interrupt */
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.CommandCompleteSignalEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.CommandCompleteStatusEnb  = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_SIGNAL_EN_REG_b.TransferCompleteSignalEnb = 1;
    p_ctrl->p_reg_mmc->SDEMMC_NORMAL_ITNR_STATUS_EN_REG_b.TransferCompleteStatusEnb = 1;

    transfer_reg = cmd << SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndex_Pos |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DataPresentSelect_Msk |
                   (uint32_t) (SDEMMC_W_GET_CMD_RESP_TYPE(cmd) <<
                               SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_ResponseTypeSelect_Pos) |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandIndexCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_CommandCRCCheckEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_MultiSingleBlockSelect_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_BlockCountEnable_Msk |
                   SDEMMC_SDEMMC_TRANSFERMODE_COMMAND_REG_DMAEnable_Msk;
    p_ctrl->p_reg_mmc->SDEMMC_TRANSFERMODE_COMMAND_REG = transfer_reg;

    p_ctrl->p_reg_mmc->SDEMMC__CLK__CTRL__REG_b.SDClockEnable = 1;
    err = r_sdemmc_sdemmc_wait_for_complete_interrupt(p_ctrl, p_rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    *p_rsp = (*p_rsp >> 8) & 0xFF;
    err    = r_sdemmc_sdemmc_wait_for_transfer_interrupt(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdemmc_wait_write_done(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_sdio_io_rw_direct (sdemmc_w_instance_ctrl_t * p_ctrl,
                                             uint8_t                    write,
                                             uint8_t                    fn,
                                             uint32_t                   addr,
                                             uint8_t                    in,
                                             uint8_t                  * p_value)
{
    uint32_t  arg = 0;
    uint32_t  rsp = 0;
    fsp_err_t err = FSP_SUCCESS;

    arg  = (1 == write) ? 0x80000000 : 0x00000000;
    arg |= fn << 28;
    arg |= addr << 9;
    arg |= in;

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_IO_RW_DIRECT, arg, &rsp);

    if (!write)
    {
        *p_value = (uint8_t) (rsp & 0xff);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_sdio_io_rw_extended (sdemmc_w_instance_ctrl_t * p_ctrl,
                                               uint8_t                    write,
                                               uint8_t                    fn,
                                               uint32_t                   addr,
                                               uint32_t                   incr_addr,
                                               uint8_t                  * p_buf,
                                               uint32_t                   block_count,
                                               uint32_t                   blksz)
{
    uint32_t arg = 0;
    uint32_t rsp = 0;

    if (addr & (uint32_t) ~0x1FFFF)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    arg  = write ? 0x80000000 : 0x00000000;
    arg |= fn << 28;
    arg |= incr_addr ? 0x04000000 : 0x00000000;
    arg |= addr << 9;

    if ((1 == blksz) && (block_count <= 512))
    {
        arg |= block_count;
    }
    else
    {
        arg |= 0x08000000 | block_count;
    }

    if (write)
    {
        if (arg & 0x08000000)
        {
            r_sdemmc_sdio_multi_write_data(p_ctrl, SDEMMC_W_PRV_CMD_IO_RW_EXTENDED, arg, &rsp, p_buf, blksz,
                                           block_count);
        }
        else
        {
            r_sdemmc_sdio_multi_write_data(p_ctrl, SDEMMC_W_PRV_CMD_IO_RW_EXTENDED, arg, &rsp, p_buf, block_count,
                                           blksz);
        }
    }
    else
    {
        if (arg & 0x08000000)
        {
            r_sdemmc_sdio_block_read_data(p_ctrl, SDEMMC_W_PRV_CMD_IO_RW_EXTENDED, arg, &rsp, p_buf, blksz,
                                          block_count);
        }
        else
        {
            r_sdemmc_sdio_block_read_data(p_ctrl, SDEMMC_W_PRV_CMD_IO_RW_EXTENDED, arg, &rsp, p_buf, block_count,
                                          blksz);
        }
    }

    if (rsp & SDEMMC_W_R5_ERROR)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    if (rsp & SDEMMC_W_R5_FUNC_NO)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    if (rsp & SDEMMC_W_R5_OUT_OF_RANGE)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_version_1_for_cistpl (st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size)
{
    uint32_t   nr_strings = 0;
    uint8_t ** buffer;
    uint8_t  * string;

    p_buf += 2;
    size  -= 2;

    uint32_t i;
    for (i = 0; i < size; i++)
    {
        if (0xff == p_buf[i])
        {
            break;
        }

        if (0 == p_buf[i])
        {
            nr_strings++;
        }
    }

    if (0 == nr_strings)
    {
        return FSP_SUCCESS;
    }

    size = i;

    buffer = (uint8_t **) malloc(sizeof(char *) * nr_strings + size);

    if (!buffer)
    {
        FSP_RETURN(FSP_ERR_OUT_OF_MEMORY);
    }

    string = (uint8_t *) (buffer + nr_strings);

    for (i = 0; i < nr_strings; i++)
    {
        buffer[i] = string;
        strcpy((char *) string, (char const *) p_buf);
        string += strlen((char const *) string) + 1;
        p_buf  += strlen((char const *) p_buf) + 1;
    }

    p_config->sdio_num_info = nr_strings;
    p_config->psdio_info    = buffer;

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_man_fid_for_cistpl (st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size)
{
    uint32_t vendor = 0;
    uint32_t device = 0;
    FSP_PARAMETER_NOT_USED(size);

    /* TPLMID_MANF */
    vendor = (uint32_t) (p_buf[0] | (p_buf[1] << 8));

    /* TPLMID_CARD */
    device = (uint32_t) (p_buf[2] | (p_buf[3] << 8));

    p_config->cis.vendor = (uint16_t) vendor;
    p_config->cis.device = (uint16_t) device;

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_parse_for_cis_tuple (st_sdemmc_config_t          * p_config,
                                               uint8_t                     * p_tpl_descr,
                                               const struct tuples_for_cis * p_tpl,
                                               int32_t                       tpl_count,
                                               uint8_t                       code,
                                               uint8_t                     * p_buf,
                                               uint32_t                      size)
{
    fsp_err_t err = FSP_SUCCESS;
    int32_t   i;
    FSP_PARAMETER_NOT_USED(p_tpl_descr);

    /* look for a matching code in the table */
    for (i = 0; i < tpl_count; i++)
    {
        if (p_tpl->code == code)
        {
            break;
        }

        p_tpl++;
    }

    if (i < tpl_count)
    {
        if (size >= p_tpl->min_size)
        {
            if (p_tpl->parse)
            {
                err = p_tpl->parse(p_config, p_buf, size);
            }
            else
            {
                err = FSP_SUCCESS;     /* known tuple, not parsed */
            }
        }
        else
        {
            /* invalid tuple */
            err = FSP_ERR_INVALID_DATA;
        }
    }
    else
    {
        /* unknown tuple */
        err = FSP_ERR_UNSUPPORTED;
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_common_fne_for_cistpl (st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size)
{
    FSP_PARAMETER_NOT_USED(size);

    /* TPLFE_FN0_BLK_SIZE */
    p_config->cis.blksize = (uint16_t) (p_buf[1] | (p_buf[2] << 8));

    /* TPLFE_MAX_TRAN_SPEED */
    p_config->cis.max_dtr = gs_speed_val[(p_buf[3] >> 3) & 15] * gs_speed_unit[p_buf[3] & 7];

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_fn_fne_for_cistpl (st_sdemmc_config_t * p_config, uint8_t * p_buf, uint32_t size)
{
    uint32_t vsn      = 0;
    uint32_t min_size = 0;

    /*
     * This tuple has a different length depending on the SDIO spec
     * version.
     */
    vsn      = p_config->cccr.sdio_vsn;
    min_size = (vsn == SDEMMC_W_PRV_SDIO_SDIO_R_1_00) ? 28 : 42;

    if (size < min_size)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    /* TPLFE_MAX_BLK_SIZE */
    p_config->max_blk_size = (uint32_t) (p_buf[12] | (p_buf[13] << 8));

    /* TPLFE_ENABLE_TIMEOUT_VAL, present in ver 1.1 and above */
    if (vsn > SDEMMC_W_PRV_SDIO_SDIO_R_1_00)
    {
        p_config->cis.enable_timeout = (uint32_t) ((p_buf[28] | (p_buf[29] << 8)) * 10);
    }

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_local_cistpl_fn (st_sdemmc_config_t * p_config, uint8_t * p_buffer, uint32_t sz)
{
    if (sz < 1)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    return r_sdemmc_parse_for_cis_tuple(p_config,
                                        (uint8_t *) SDEMMC_W_PRV_CISTPL_FUNC_NAME,
                                        gs_func_list_for_cis_tpl,
                                        SDEMMC_W_ARRAY_SIZE(gs_func_list_for_cis_tpl),
                                        p_buffer[0],
                                        p_buffer,
                                        sz);
}

static fsp_err_t r_sdemmc_sdio_cis_tpl_parse (st_sdemmc_config_t * p_config,
                                              uint8_t            * p_data,
                                              uint8_t              tpl_code,
                                              uint8_t              tpl_link)
{
    fsp_err_t err = FSP_SUCCESS;

    err = r_sdemmc_parse_for_cis_tuple(p_config,
                                       (uint8_t *) SDEMMC_W_PRV_CIS_NAME,
                                       gs_list_cis_tpl,
                                       SDEMMC_W_ARRAY_SIZE(gs_list_cis_tpl),
                                       tpl_code,
                                       p_data,
                                       (uint32_t) tpl_link);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

static inline uint32_t BITS_FOR_UNSTUFF (uint32_t * p_resp, uint32_t start, uint32_t size)
{
    int32_t  isize = (int32_t) size;
    uint32_t mask  = (uint32_t) ((isize < 32 ? 1 << isize : 0) - 1);
    int32_t  off   = (int32_t) (3 - ((start) / 32));
    int32_t  shift = (start) & 31;
    uint32_t res;

    res = p_resp[off] >> shift;

    if (isize + shift > 32)
    {
        res |= p_resp[off - 1] << ((32 - shift) % 32);
    }

    return res & mask;
}

#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_emmc_decode_csd (sdemmc_w_instance_ctrl_t * const p_ctrl, st_sdemmc_config_t * p_config)
{
    st_mmc_csd_t       * tmp_mmc_csd = &(p_config->csd);
    uint32_t             e           = 0;
    uint32_t             m           = 0;
    uint32_t             a           = 0;
    uint32_t             b           = 0;
    uint32_t           * decode_rsp  = p_config->raw_csd;
    sdmmc_priv_csd_reg_t csd_reg;

    p_ctrl->device.card_type = SDMMC_CARD_TYPE_MMC;
    r_sdemmc_csd_save(p_ctrl, p_config->rca, &csd_reg, false);

    tmp_mmc_csd->mmc_struct = (uint8_t) BITS_FOR_UNSTUFF(decode_rsp, 126, 2);

    if (0 == tmp_mmc_csd->mmc_struct)
    {
        FSP_RETURN(FSP_ERR_INVALID_DATA);
    }

    tmp_mmc_csd->mmca_vsn = (uint8_t) BITS_FOR_UNSTUFF(decode_rsp, 122, 4);
    m = BITS_FOR_UNSTUFF(decode_rsp, 115, 4);
    e = BITS_FOR_UNSTUFF(decode_rsp, 112, 3);
    tmp_mmc_csd->ns_for_tacc   = (gs_tacc_exp[e] * gs_tacc_mant[m] + 9) / 10;
    tmp_mmc_csd->clks_for_tacc = (uint16_t) (BITS_FOR_UNSTUFF(decode_rsp, 104, 8) * 100);

    m = BITS_FOR_UNSTUFF(decode_rsp, 99, 4);
    e = BITS_FOR_UNSTUFF(decode_rsp, 96, 3);
    tmp_mmc_csd->max_dtr       = gs_tran_exp[e] * gs_tran_mant[m];
    tmp_mmc_csd->command_class = (uint16_t) BITS_FOR_UNSTUFF(decode_rsp, 84, 12);

    e = BITS_FOR_UNSTUFF(decode_rsp, 47, 3);
    m = BITS_FOR_UNSTUFF(decode_rsp, 62, 12);
    tmp_mmc_csd->capa_size = (1 + m) << (e + 2);

    tmp_mmc_csd->rd_bits_for_blk  = BITS_FOR_UNSTUFF(decode_rsp, 80, 4);
    tmp_mmc_csd->rd_part          = BITS_FOR_UNSTUFF(decode_rsp, 79, 1) & SDEMMC_W_1BIT_MASK;
    tmp_mmc_csd->wr_misalign_flag = BITS_FOR_UNSTUFF(decode_rsp, 78, 1) & SDEMMC_W_1BIT_MASK;
    tmp_mmc_csd->rd_misalign_flag = BITS_FOR_UNSTUFF(decode_rsp, 77, 1) & SDEMMC_W_1BIT_MASK;
    tmp_mmc_csd->factor_for_r2w   = BITS_FOR_UNSTUFF(decode_rsp, 26, 3);
    tmp_mmc_csd->wr_bits_for_blk  = BITS_FOR_UNSTUFF(decode_rsp, 22, 4);
    tmp_mmc_csd->wr_part          = BITS_FOR_UNSTUFF(decode_rsp, 21, 1) & SDEMMC_W_1BIT_MASK;

    if (tmp_mmc_csd->wr_bits_for_blk >= 9)
    {
        a = BITS_FOR_UNSTUFF(decode_rsp, 42, 5);
        b = BITS_FOR_UNSTUFF(decode_rsp, 37, 5);
        tmp_mmc_csd->sz_for_erase   = (a + 1) * (b + 1);
        tmp_mmc_csd->sz_for_erase <<= tmp_mmc_csd->wr_bits_for_blk - 9;
    }

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_emmc_decode_ext_csd (sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config)
{
    p_config->ext_csd.raw_ext_csd_structure = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_STRUCTURE];

    if (3 == p_config->csd.mmc_struct)
    {
        if (p_config->ext_csd.raw_ext_csd_structure > 2)
        {
            FSP_RETURN(FSP_ERR_INVALID_DATA);
        }
    }

    p_config->ext_csd.rev = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_REV];

    p_config->ext_csd.raw_sectors[0] = p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 0];
    p_config->ext_csd.raw_sectors[1] = p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 1];
    p_config->ext_csd.raw_sectors[2] = p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 2];
    p_config->ext_csd.raw_sectors[3] = p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 3];

    if (p_config->ext_csd.rev >= 2)
    {
        p_config->ext_csd.sectors =
            (uint32_t) (p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 0] << 0) |
            (uint32_t) (p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 1] << 8) |
            (uint32_t) (p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 2] << 16) |
            (uint32_t) (p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET + 3] << 24);
        p_ctrl->device.sector_count = p_config->ext_csd.sectors;
    }

    p_config->ext_csd.raw_card_type = p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_DEVICE_TYPE_OFFSET];

    switch (p_config->pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_DEVICE_TYPE_OFFSET] & SDEMMC_W_PRV_E_CSD_CD_TYPE_MASK)
    {
        case SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_52 | SDEMMC_W_PRV_E_CSD_CD_TYPE_52 | SDEMMC_W_PRV_E_CSD_CD_TYPE_26:
        {
            p_config->ext_csd.hs_max_dtr = 52000000;
            p_config->ext_csd.card_type  = SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_52;
            break;
        }

        case SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_2V | SDEMMC_W_PRV_E_CSD_CD_TYPE_52 | SDEMMC_W_PRV_E_CSD_CD_TYPE_26:
        {
            p_config->ext_csd.hs_max_dtr = 52000000;
            p_config->ext_csd.card_type  = SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_2V;
            break;
        }

        case SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_8V | SDEMMC_W_PRV_E_CSD_CD_TYPE_52 | SDEMMC_W_PRV_E_CSD_CD_TYPE_26:
        {
            p_config->ext_csd.hs_max_dtr = 52000000;
            p_config->ext_csd.card_type  = SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_8V;
            break;
        }

        case SDEMMC_W_PRV_E_CSD_CD_TYPE_52 | SDEMMC_W_PRV_E_CSD_CD_TYPE_26:
        {
            p_config->ext_csd.hs_max_dtr = 52000000;
            break;
        }

        case SDEMMC_W_PRV_E_CSD_CD_TYPE_26:
        {
            p_config->ext_csd.hs_max_dtr = 26000000;
            break;
        }

        default:
        {
            /* MMC v4 spec says this cannot happen */
            break;
        }
    }

    p_config->ext_csd.raw_s_a_timeout        = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_S_A_TIMEOUT];
    p_config->ext_csd.raw_erase_timeout_mult = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_ER_TO_MULT];
    p_config->ext_csd.raw_hc_erase_grp_size  = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_HC_ERASE_GRP_SIZE];

    if (p_config->ext_csd.rev >= 3)
    {
        uint8_t sa_shift = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_S_A_TIMEOUT];
        p_config->ext_csd.part_config = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_PART_CFG];

        /* EXT_CSD value is in units of 10ms, but we store in ms */
        p_config->ext_csd.part_time = 10 * p_config->pext_csd[SDEMMC_W_PRV_E_CSD_PART_SWCH_TM];

        /* Sleep / awake timeout in 100ns units */

        if ((sa_shift > 0) && (sa_shift <= 0x17))
        {
            p_config->ext_csd.sa_timeout = 1 << p_config->pext_csd[SDEMMC_W_PRV_E_CSD_S_A_TIMEOUT];
        }

        p_config->ext_csd.erase_group_def  = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_ER_GRP_DEF];
        p_config->ext_csd.hc_erase_timeout = 300 * p_config->pext_csd[SDEMMC_W_PRV_E_CSD_ER_TO_MULT];
        p_config->ext_csd.hc_erase_size    = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_HC_ERASE_GRP_SIZE] << 10;

        p_config->ext_csd.rel_sectors = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_REL_WR_SEC_C];

        /*
         * There are two boot regions of equal size, defined in
         * multiples of 128K.
         */
        p_config->ext_csd.boot_size = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_BOOT_MULT] << 17;
    }

    p_config->ext_csd.raw_hc_erase_gap_size   = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_PART_ATTR];
    p_config->ext_csd.raw_sec_trim_mult       = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_SEC_TRIM_MULT];
    p_config->ext_csd.raw_sec_erase_mult      = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_SEC_ERASE_MULT];
    p_config->ext_csd.raw_sec_feature_support = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_SEC_FT_SUPP];
    p_config->ext_csd.raw_trim_mult           = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_TRIM_MULT];

    if (p_config->ext_csd.rev >= 4)
    {
        /*
         * Enhanced area feature support -- check whether the eMMC
         * emmc has the Enhanced area enabled.  If so, export enhanced
         * area offset and size to user by adding sysfs interface.
         */
        p_config->ext_csd.raw_partition_support = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_PART_SUPP];

        if ((p_config->pext_csd[SDEMMC_W_PRV_E_CSD_PART_SUPP] & 0x2) &&
            (p_config->pext_csd[SDEMMC_W_PRV_E_CSD_PART_ATTR] & 0x1))
        {
            uint8_t hc_erase_grp_sz = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_HC_ERASE_GRP_SIZE];
            uint8_t hc_wp_grp_sz    = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_HC_WP_GRP_SIZE];

            p_config->ext_csd.enhanced_area_en = 1;

            /* calculate the enhanced data area offset, in bytes */
            p_config->ext_csd.enhanced_area_offset = (uint64_t) ((p_config->pext_csd[139] << 24) +
                                                                 (p_config->pext_csd[138] << 16) +
                                                                 (p_config->pext_csd[137] << 8) +
                                                                 p_config->pext_csd[136]);

            /* calculate the enhanced data area size, in kilobytes */
            p_config->ext_csd.enhanced_area_size = (uint32_t) ((p_config->pext_csd[142] << 16) +
                                                               (p_config->pext_csd[141] << 8) +
                                                               p_config->pext_csd[140]);
            p_config->ext_csd.enhanced_area_size  *= (size_t) (hc_erase_grp_sz * hc_wp_grp_sz);
            p_config->ext_csd.enhanced_area_size <<= 9;
        }
        else
        {
            /*
             * If the enhanced area is not enabled, disable these
             * device attributes.
             */
            p_config->ext_csd.enhanced_area_offset = 0xFFFFFFFFFFFFFFFF;
            p_config->ext_csd.enhanced_area_size   = 0xFFFFFFFF;
        }

        p_config->ext_csd.sec_trim_mult       = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_SEC_TRIM_MULT];
        p_config->ext_csd.sec_erase_mult      = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_SEC_ERASE_MULT];
        p_config->ext_csd.sec_feature_support = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_SEC_FT_SUPP];
        p_config->ext_csd.trim_timeout        = 300 * p_config->pext_csd[SDEMMC_W_PRV_E_CSD_TRIM_MULT];
    }

    p_config->ext_csd.raw_erased_mem_count = p_config->pext_csd[SDEMMC_W_PRV_E_CSD_ERASED_MEM_CONT];

    if (p_config->pext_csd[SDEMMC_W_PRV_E_CSD_ERASED_MEM_CONT])
    {
        p_config->erased_byte = 0xFF;
    }
    else
    {
        p_config->erased_byte = 0x0;
    }

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_sd_decode_csd (sdemmc_w_instance_ctrl_t * const p_ctrl, st_sdemmc_config_t * p_config)
{
    st_mmc_csd_t       * csd  = &(p_config->csd);
    uint32_t             e    = 0;
    uint32_t             m    = 0;
    uint32_t           * resp = p_config->raw_csd;
    sdmmc_priv_csd_reg_t csd_reg;

    r_sdemmc_csd_save(p_ctrl, p_config->rca, &csd_reg, false);

    csd->mmc_struct = (uint8_t) BITS_FOR_UNSTUFF(resp, 126, 2);

    switch (csd->mmc_struct)
    {
        case 0:
        {
            m                  = BITS_FOR_UNSTUFF(resp, 115, 4);
            e                  = BITS_FOR_UNSTUFF(resp, 112, 3);
            csd->ns_for_tacc   = (gs_tacc_exp[e] * gs_tacc_mant[m] + 9) / 10;
            csd->clks_for_tacc = (uint16_t) (BITS_FOR_UNSTUFF(resp, 104, 8) * 100);

            m                  = BITS_FOR_UNSTUFF(resp, 99, 4);
            e                  = BITS_FOR_UNSTUFF(resp, 96, 3);
            csd->max_dtr       = gs_tran_exp[e] * gs_tran_mant[m];
            csd->command_class = (uint16_t) BITS_FOR_UNSTUFF(resp, 84, 12);

            e              = BITS_FOR_UNSTUFF(resp, 47, 3);
            m              = BITS_FOR_UNSTUFF(resp, 62, 12);
            csd->capa_size = (1 + m) << (e + 2);

            csd->rd_bits_for_blk  = BITS_FOR_UNSTUFF(resp, 80, 4);
            csd->rd_part          = BITS_FOR_UNSTUFF(resp, 79, 1) & SDEMMC_W_1BIT_MASK;
            csd->wr_misalign_flag = BITS_FOR_UNSTUFF(resp, 78, 1) & SDEMMC_W_1BIT_MASK;
            csd->rd_misalign_flag = BITS_FOR_UNSTUFF(resp, 77, 1) & SDEMMC_W_1BIT_MASK;
            csd->factor_for_r2w   = BITS_FOR_UNSTUFF(resp, 26, 3);
            csd->wr_bits_for_blk  = BITS_FOR_UNSTUFF(resp, 22, 4);
            csd->wr_part          = BITS_FOR_UNSTUFF(resp, 21, 1) & SDEMMC_W_1BIT_MASK;

            if (BITS_FOR_UNSTUFF(resp, 46, 1))
            {
                csd->sz_for_erase = 1;
            }
            else if (csd->wr_bits_for_blk >= 9)
            {
                csd->sz_for_erase   = BITS_FOR_UNSTUFF(resp, 39, 7) + 1;
                csd->sz_for_erase <<= csd->wr_bits_for_blk - 9;
            }

            break;
        }

        case 1:
        {
            csd->ns_for_tacc   = 0;    /* Unused */
            csd->clks_for_tacc = 0;    /* Unused */

            m                  = BITS_FOR_UNSTUFF(resp, 99, 4);
            e                  = BITS_FOR_UNSTUFF(resp, 96, 3);
            csd->max_dtr       = gs_tran_exp[e] * gs_tran_mant[m];
            csd->command_class = (uint16_t) BITS_FOR_UNSTUFF(resp, 84, 12);
            csd->c_sz          = BITS_FOR_UNSTUFF(resp, 48, 22);

            /* SDXC emmcs have a minimum C_SIZE of 0x00FFFF */
            m              = BITS_FOR_UNSTUFF(resp, 48, 22);
            csd->capa_size = (1 + m) << 10;

            csd->rd_bits_for_blk  = 9;
            csd->rd_part          = 0;
            csd->wr_misalign_flag = 0;
            csd->rd_misalign_flag = 0;
            csd->factor_for_r2w   = 4; /* Unused */
            csd->wr_bits_for_blk  = 9;
            csd->wr_part          = 0;
            csd->sz_for_erase     = 1;
            break;
        }

        default:
        {
            FSP_RETURN(FSP_ERR_INVALID_DATA);
        }
    }

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_emmc_decode_cid (st_sdemmc_config_t * p_config)
{
    uint32_t * resp = p_config->raw_cid;

    switch (p_config->csd.mmca_vsn)
    {
        case 0:                        /* MMC v1.0 - v1.2 */
        case 1:                        /* MMC v1.4 */
        {
            p_config->cid.manfid       = BITS_FOR_UNSTUFF(resp, 104, 24);
            p_config->cid.prod_name[0] = (int8_t) BITS_FOR_UNSTUFF(resp, 96, 8);
            p_config->cid.prod_name[1] = (int8_t) BITS_FOR_UNSTUFF(resp, 88, 8);
            p_config->cid.prod_name[2] = (int8_t) BITS_FOR_UNSTUFF(resp, 80, 8);
            p_config->cid.prod_name[3] = (int8_t) BITS_FOR_UNSTUFF(resp, 72, 8);
            p_config->cid.prod_name[4] = (int8_t) BITS_FOR_UNSTUFF(resp, 64, 8);
            p_config->cid.prod_name[5] = (int8_t) BITS_FOR_UNSTUFF(resp, 56, 8);
            p_config->cid.prod_name[6] = (int8_t) BITS_FOR_UNSTUFF(resp, 48, 8);
            p_config->cid.hwrev        = (uint8_t) BITS_FOR_UNSTUFF(resp, 44, 4);
            p_config->cid.fwrev        = (uint8_t) BITS_FOR_UNSTUFF(resp, 40, 4);
            p_config->cid.serial       = BITS_FOR_UNSTUFF(resp, 16, 24);
            p_config->cid.month        = (uint8_t) BITS_FOR_UNSTUFF(resp, 12, 4);
            p_config->cid.year         = (uint16_t) (BITS_FOR_UNSTUFF(resp, 8, 4) + 1997);
            break;
        }

        case 2:                        /* MMC v2.0 - v2.2 */
        case 3:                        /* MMC v3.1 - v3.3 */
        case 4:                        /* MMC v4 */
        {
            p_config->cid.manfid       = BITS_FOR_UNSTUFF(resp, 120, 8);
            p_config->cid.oemid        = (uint16_t) BITS_FOR_UNSTUFF(resp, 104, 16);
            p_config->cid.prod_name[0] = (int8_t) BITS_FOR_UNSTUFF(resp, 96, 8);
            p_config->cid.prod_name[1] = (int8_t) BITS_FOR_UNSTUFF(resp, 88, 8);
            p_config->cid.prod_name[2] = (int8_t) BITS_FOR_UNSTUFF(resp, 80, 8);
            p_config->cid.prod_name[3] = (int8_t) BITS_FOR_UNSTUFF(resp, 72, 8);
            p_config->cid.prod_name[4] = (int8_t) BITS_FOR_UNSTUFF(resp, 64, 8);
            p_config->cid.prod_name[5] = (int8_t) BITS_FOR_UNSTUFF(resp, 56, 8);
            p_config->cid.serial       = BITS_FOR_UNSTUFF(resp, 16, 32);
            p_config->cid.month        = (uint8_t) BITS_FOR_UNSTUFF(resp, 12, 4);
            p_config->cid.year         = (uint16_t) (BITS_FOR_UNSTUFF(resp, 8, 4) + 1997);
            break;
        }

        default:
        {
            FSP_RETURN(FSP_ERR_INVALID_DATA);
        }
    }

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_sd_decode_cid (st_sdemmc_config_t * p_config)
{
    uint32_t * resp = p_config->raw_cid;

    p_config->cid.manfid       = BITS_FOR_UNSTUFF(resp, 120, 8);
    p_config->cid.oemid        = (uint16_t) BITS_FOR_UNSTUFF(resp, 104, 16);
    p_config->cid.prod_name[0] = (int8_t) BITS_FOR_UNSTUFF(resp, 96, 8);
    p_config->cid.prod_name[1] = (int8_t) BITS_FOR_UNSTUFF(resp, 88, 8);
    p_config->cid.prod_name[2] = (int8_t) BITS_FOR_UNSTUFF(resp, 80, 8);
    p_config->cid.prod_name[3] = (int8_t) BITS_FOR_UNSTUFF(resp, 72, 8);
    p_config->cid.prod_name[4] = (int8_t) BITS_FOR_UNSTUFF(resp, 64, 8);
    p_config->cid.hwrev        = (uint8_t) BITS_FOR_UNSTUFF(resp, 60, 4);
    p_config->cid.fwrev        = (uint8_t) BITS_FOR_UNSTUFF(resp, 56, 4);
    p_config->cid.serial       = BITS_FOR_UNSTUFF(resp, 24, 32);
    p_config->cid.year         = (uint16_t) BITS_FOR_UNSTUFF(resp, 12, 8);
    p_config->cid.month        = (uint8_t) BITS_FOR_UNSTUFF(resp, 8, 4);

    p_config->cid.year += 2000;        /* SD year offset */

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_mmc_decode_scr (st_sdemmc_config_t * p_config)
{
    st_sd_scr_t * scr        = &(p_config->scr);
    uint32_t      scr_struct = 0;
    uint32_t      resp[4];

    resp[3] = SDEMMC_W_NTOH32(p_config->raw_scr[1]);
    resp[2] = SDEMMC_W_NTOH32(p_config->raw_scr[0]);
    resp[1] = 0;
    resp[0] = 0;

    scr_struct = BITS_FOR_UNSTUFF(resp, 60, 4);

    if (0 != scr_struct)
    {
        FSP_RETURN(FSP_ERR_INVALID_DATA);
    }

    scr->sda_vsn = (uint8_t) BITS_FOR_UNSTUFF(resp, 56, 4);
    scr->bus_wid = (uint8_t) BITS_FOR_UNSTUFF(resp, 48, 4);

    if (SDEMMC_W_PRV_SCR_SPEC_VER_2 == scr->sda_vsn)
    {
        /* Check if Physical Layer Spec v3.0 is supported */
        scr->sda_spec3 = (uint8_t) BITS_FOR_UNSTUFF(resp, 47, 1);
    }

    if (scr->sda_spec3)
    {
        scr->sd_cmds = (uint8_t) BITS_FOR_UNSTUFF(resp, 32, 2);
    }

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_mmd_decode_ssr (st_sdemmc_config_t * p_config)
{
    st_sd_ssr_t * ssr             = &(p_config->ssr);
    uint32_t      allocation_unit = 0;
    uint32_t      erase_size      = 0;
    uint32_t      erase_timeout   = 0;
    uint32_t      erase_offset    = 0;
    uint32_t    * resp;
    uint32_t      i;

    for (i = 0; i < 16; i++)
    {
        p_config->raw_ssr[i] = SDEMMC_W_NTOH32(p_config->raw_ssr[i]);
    }

    resp = p_config->raw_ssr;

    ssr->bus_width      = BITS_FOR_UNSTUFF(resp, (510 - 384), 2);
    ssr->cd_type        = (uint16_t) BITS_FOR_UNSTUFF(resp, (480 - 384), 16);
    ssr->area_protected = BITS_FOR_UNSTUFF(resp, (448 - 384), 32);
    ssr->spd_class      = BITS_FOR_UNSTUFF(resp, (440 - 384), 8);
    ssr->perf_mv        = (uint8_t) BITS_FOR_UNSTUFF(resp, (432 - 384), 8);
    allocation_unit     = BITS_FOR_UNSTUFF(resp, (428 - 384), 4);
    ssr->au             = 1 << (allocation_unit + 4);
    erase_size          = BITS_FOR_UNSTUFF(resp, (408 - 384), 16);
    erase_timeout       = BITS_FOR_UNSTUFF(resp, (402 - 384), 6);
    erase_offset        = BITS_FOR_UNSTUFF(resp, (400 - 384), 2);

    if (erase_size && erase_timeout)
    {
        ssr->erase_to  = (erase_timeout * 1000) / erase_size; /* In milliseconds */
        ssr->erase_off = erase_offset * 1000;                 /* In milliseconds */
    }

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_emmc_wait_ready (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t * p_rocr)
{
    FSP_PARAMETER_NOT_USED(p_rocr);
    uint32_t rsp       = 0;
    uint32_t try_count = 100;
    uint32_t i;

    for (i = 0; i < try_count; i++)
    {
        r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEND_OP_COND, (0x40ff8080 | (0x01 << 30)), &rsp);

        if ((0x80ff8080 == rsp) || (0xc0ff8080 == rsp))
        {
            return FSP_SUCCESS;
        }

        rsp = 0;
        R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MICROSECONDS);
    }

    FSP_RETURN(FSP_ERR_INVALID_STATE);
}

#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

static uint32_t r_sdemmc_emmc_make_switch_arg (uint8_t set, uint8_t index, uint8_t value)
{
    return (uint32_t) (SDEMMC_W_PRV_MMC_SWITCH_MODE_WRITE_BYTE << 24) |
           (uint32_t) (index << 16) | (uint32_t) (value << 8) |
           (uint32_t) set;
}

#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE

static uint32_t r_sdemmc_sd_make_switch_arg (int32_t mode, int32_t group, int32_t value)
{
    uint32_t arg = 0;

    arg  = (uint32_t) (mode << 31 | 0x00FFFFFF);
    arg &= (uint32_t) ~(0xF << (group * 4));
    arg |= (uint32_t) (value << (group * 4));

    return arg;
}

#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE */

#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_emmc_send_op_cond (sdemmc_w_instance_ctrl_t * p_ctrl, uint32_t ocr, uint32_t * p_rocr)
{
    FSP_PARAMETER_NOT_USED(ocr);
    uint32_t  rsp = 0;
    fsp_err_t err = FSP_SUCCESS;

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEND_OP_COND, 0, &rsp);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (0x00ff8080 == rsp)
    {
        /* device capacity is less than or to 2GB */
        err = r_sdemmc_emmc_wait_ready(p_ctrl, &rsp);
    }
    else if (0x40ff8080 == rsp)
    {
        err = r_sdemmc_emmc_wait_ready(p_ctrl, &rsp);
    }
    else
    {
        err = r_sdemmc_emmc_wait_ready(p_ctrl, &rsp);
    }

    *p_rocr = rsp;

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */

static fsp_err_t r_sdemmc_sdio_init_card (sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config,
                                          uint32_t ocr)
{
#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE
    uint32_t  rocr     = 0;
    uint32_t  rsp      = 0;
    uint32_t  cis_ptr  = 0;
    uint8_t   data     = 0;
    uint8_t   cccr_vsn = 0;
    fsp_err_t err      = FSP_SUCCESS;
    uint32_t  i;
    FSP_PARAMETER_NOT_USED(ocr);

    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_SDIO_SEND_OP_COND, rocr, &rocr);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (0 == rocr)
        {
            FSP_RETURN(FSP_ERR_INVALID_DATA);
        }

        if (0 == (rocr & SDEMMC_W_PRV_SUPPORT_VOLTAGE))
        {
            FSP_RETURN(FSP_ERR_UNSUPPORTED);
        }

        if (rocr & SDEMMC_W_PRV_CARD_READY)
        {
            break;
        }

        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_INVALID_STATE);
    }

    p_config->ocr = rocr & SDEMMC_W_PRV_SUPPORT_VOLTAGE;

    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_SDIO_SEND_OP_COND, p_config->ocr, &rocr);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (0 == rocr)
        {
            FSP_RETURN(FSP_ERR_INVALID_DATA);
        }

        if (rocr & SDEMMC_W_PRV_CARD_READY)
        {
            break;
        }

        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_INVALID_STATE);
    }

    if (p_config->ocr & SDEMMC_W_PRV_R4_MEM_PR)
    {
        FSP_RETURN(FSP_ERR_UNSUPPORTED);
    }

    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEND_RELATIVE_ADDR, 0, &rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_config->rca = rsp >> 16;
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEL_DES_CARD, (p_config->rca << 16), &rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, SDEMMC_W_PRV_SDIO_CCCR_CCCR, 0, &data);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    cccr_vsn                = data & 0x0f;
    p_config->cccr.sdio_vsn = (data & 0xf0) >> 4;

    err = r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, SDEMMC_W_PRV_SDIO_CCCR_CAPS, 0, &data);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (data & SDEMMC_W_PRV_SDIO_CCCR_CAP_SMB)
    {
        p_config->cccr.multi_block = 1;
        p_config->cccr.wide_bus    = 1;
    }

    if (data & SDEMMC_W_PRV_SDIO_CCCR_CAP_LSC)
    {
        p_config->cccr.low_speed = 1;

        if (data & SDEMMC_W_PRV_SDIO_CCCR_CAP_4BLS)
        {
            p_config->cccr.wide_bus = 1;
        }
    }

    if (cccr_vsn >= SDEMMC_W_PRV_SDIO_CCCR_R_1_10)
    {
        err =
            r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, SDEMMC_W_PRV_SDIO_CCCR_POWER, 0, &data);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (data & SDEMMC_W_PRV_SDIO_PWR_SMPC)
        {
            p_config->cccr.high_power = 1;
        }
    }

    if (cccr_vsn >= SDEMMC_W_PRV_SDIO_CCCR_R_1_20)
    {
        err =
            r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, SDEMMC_W_PRV_SDIO_CCCR_SPEED, 0, &data);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (data & SDEMMC_W_PRV_SDIO_SPEED_SHS)
        {
            p_config->cccr.high_speed = 1;
        }
    }

    for (i = 0; i < 3; i++)
    {
        err =
            r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0,
                                       (SDEMMC_W_PRV_SDIO_FBR_BASE(0) + SDEMMC_W_PRV_SDIO_FBR_CIS + i), 0, &data);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        cis_ptr |= data << (i * 8);
    }

    do
    {
        uint8_t tpl_code;
        uint8_t tpl_link;

        err = r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, cis_ptr++, 0, &tpl_code);

        if (err)
        {
            break;
        }

        if (0xff == tpl_code)
        {
            break;
        }

        if (0x00 == tpl_code)
        {
            continue;
        }

        err = r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, cis_ptr++, 0, &tpl_link);

        if (err)
        {
            break;
        }

        if (0xff == tpl_link)
        {
            break;
        }

        p_config->psdio_cis = (uint8_t *) malloc(tpl_link);

        if (!(p_config->psdio_cis))
        {
            FSP_RETURN(FSP_ERR_OUT_OF_MEMORY);
        }

        for (i = 0; i < tpl_link; i++)
        {
            err =
                r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, (cis_ptr + i), 0,
                                           &(p_config->psdio_cis[i]));

            if (err)
            {
                free(p_config->psdio_cis);
                FSP_RETURN(err);
            }
        }

        err = r_sdemmc_sdio_cis_tpl_parse(p_config, p_config->psdio_cis, tpl_code, tpl_link);
        free((void *) p_config->psdio_cis);
        p_config->psdio_cis = NULL;

        if (err)
        {
            break;
        }

        cis_ptr += tpl_link;
    } while (!err);

    cis_ptr = 0;

    for (i = 0; i < 3; i++)
    {
        err =
            r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0,
                                       (SDEMMC_W_PRV_SDIO_FBR_BASE(1) + SDEMMC_W_PRV_SDIO_FBR_CIS + i), 0, &data);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        cis_ptr |= data << (i * 8);
    }

    /* 4bit, push_pull up */
    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_config);
    FSP_PARAMETER_NOT_USED(ocr);
    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */
}

static fsp_err_t r_sdemmc_sd_init_card (sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config, uint32_t ocr)
{
#if SDEMMC_W_CFG_SD_SUPPORT_ENABLE
    FSP_PARAMETER_NOT_USED(ocr);
    uint32_t  rocr = 0;
    uint32_t  rsp  = 0;
    uint8_t   buf[64];
    fsp_err_t err = FSP_SUCCESS;

    r_sdemmc_emmc_cmd_without_res(p_ctrl, SDEMMC_W_PRV_CMD_GO_IDLE_STATE, 0x12345678);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    r_sdemmc_emmc_cmd_without_res(p_ctrl, SDEMMC_W_PRV_CMD_GO_IDLE_STATE, 0xffffffff);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_IF_COND, 0x15a, &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_APP_CMD, 0xffff, &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SD_SEND_OP_COND, 0, &rocr);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    int32_t i;
    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_APP_CMD, 0xffff, &rsp);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SD_SEND_OP_COND, 0x40ff0000, &rocr);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (rocr & SDEMMC_W_PRV_CARD_READY)
        {
            break;
        }

        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_INVALID_STATE);
    }

    p_config->ocr = rocr;

    sdmmc_response_t response;
    response.status = rocr;

    if (response.r3.power_up_status)
    {
        /* High capacity card ? */
        /*  0 = SDSC, 1 = SDHC or SDXC */
        p_ctrl->sector_addressing = (response.r3.card_capacity_status > 0U);
    }

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_ALL_SEND_CID, 0xffffffff, p_config->raw_cid);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    r_sdemmc_sd_decode_cid(p_config);

    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEND_RELATIVE_ADDR, 0, &rsp);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_config->rca = rsp >> 16;
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEND_CSD, (p_config->rca << 16), p_config->raw_csd);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_sd_decode_csd(p_ctrl, p_config);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEL_DES_CARD, (p_config->rca << 16), &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_SD_APP_SD_STS, (p_config->rca << 16), &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_APP_CMD, (p_config->rca << 16), &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
    err = r_sdemmc_emmc_single_read_data_with_wait(p_ctrl,
                                                   SDEMMC_W_PRV_SD_APP_SEND_SCR,
                                                   0,
                                                   8,
                                                   &rsp,
                                                   (uint8_t *) p_config->raw_scr);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_mmc_decode_scr(p_config);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_APP_CMD, (p_config->rca << 16), &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
    err = r_sdemmc_emmc_single_read_data_with_wait(p_ctrl,
                                                   SDEMMC_W_PRV_SD_APP_SD_STS,
                                                   0,
                                                   64,
                                                   &rsp,
                                                   (uint8_t *) p_config->raw_ssr);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_mmd_decode_ssr(p_config);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err =
        r_sdemmc_emmc_single_read_data_with_wait(p_ctrl, SDEMMC_W_PRV_CMD_SET_BUS_WIDTH,
                                                 r_sdemmc_sd_make_switch_arg(0, 0, 1), 64, &rsp, (uint8_t *) buf);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_INVALID_STATE);

    /* check data group1 high speed  */
    if (buf[13] & 0x02)
    {
        p_config->caps.hs_max_dtr = 25000000;

        err = r_sdemmc_emmc_single_read_data_with_wait(p_ctrl,
                                                       SDEMMC_W_PRV_CMD_SET_BUS_WIDTH,
                                                       r_sdemmc_sd_make_switch_arg(1, 0, 1),
                                                       64,
                                                       &rsp,
                                                       (uint8_t *) buf);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_INVALID_STATE);

        /* set again */
        err = r_sdemmc_emmc_single_read_data_with_wait(p_ctrl,
                                                       SDEMMC_W_PRV_CMD_SET_BUS_WIDTH,
                                                       r_sdemmc_sd_make_switch_arg(1, 0, 1),
                                                       64,
                                                       &rsp,
                                                       (uint8_t *) buf);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_INVALID_STATE);

        if (1 != (buf[16] & 0x0f))
        {
            FSP_RETURN(FSP_ERR_INVALID_STATE);
        }
    }

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_APP_CMD, ((p_config->rca << 16) | 0xffff), &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10, BSP_DELAY_UNITS_MICROSECONDS);
    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SET_BUS_WIDTH, SDEMMC_W_PRV_SD_BUS_WIDTH_1, &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* 4bit, high speed, push_pull up */

    if (p_config->csd.capa_size < 2048000)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SET_BLOCKLEN, 512, &rsp);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        p_config->card_type = SDMMC_PRIV_CT_SD_CARD_1_1;
    }
    else
    {
        p_config->card_type = SDMMC_PRIV_CT_SD_CARD;
    }

    err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_SD_APP_SD_STS, ((p_config->rca << 16) | 0xffff), &rsp);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_config);
    FSP_PARAMETER_NOT_USED(ocr);
    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_SD_SUPPORT_ENABLE */
}

static fsp_err_t r_sdemmc_emmc_init_card (sdemmc_w_instance_ctrl_t * p_ctrl, st_sdemmc_config_t * p_config,
                                          uint32_t ocr)
{
#if SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE
    FSP_PARAMETER_NOT_USED(ocr);
    uint32_t  rocr = 0;
    uint32_t  rsp  = 0;
    fsp_err_t err  = FSP_SUCCESS;
    int32_t   i    = 0;

    r_sdemmc_emmc_cmd_without_res(p_ctrl, SDEMMC_W_PRV_CMD_GO_IDLE_STATE, 0);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
    err = r_sdemmc_emmc_send_op_cond(p_ctrl, 0, &rocr);
    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_UNSUPPORTED);

    p_config->ocr = rocr;

    /* get response of CMD1  */
    sdmmc_response_t response;
    response.status = rocr;

    /* High capacity card ? */
    p_ctrl->sector_addressing = (response.r3.card_capacity_status > 0U);

    /* send cid */
    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_ALL_SEND_CID, 0, p_config->raw_cid);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

        if (!err)
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_INVALID_STATE);
    }

    p_config->rca = 1;
    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEND_RELATIVE_ADDR, (p_config->rca << 16), &rsp);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

        if (!err)
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(err);
    }

    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEND_CSD, (p_config->rca << 16), p_config->raw_csd);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

        if (!err)
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_INVALID_STATE);
    }

    err = r_sdemmc_emmc_decode_csd(p_ctrl, p_config);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sdemmc_emmc_decode_cid(p_config);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_INVALID_STATE);

    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_cmd_with_res(p_ctrl, SDEMMC_W_PRV_CMD_SEL_DES_CARD, (p_config->rca << 16), &rsp);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

        if (!err)
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(err);
    }

    if (p_config->csd.mmca_vsn < 4)
    {
        FSP_RETURN(FSP_ERR_UNSUPPORTED);
    }

    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err = r_sdemmc_emmc_single_read_data_with_wait(p_ctrl,
                                                       SDEMMC_W_PRV_CMD_IF_COND,
                                                       0,
                                                       SDEMMC_W_PRV_EMMC_EXT_CSD_SIZE,
                                                       &rsp,
                                                       (uint8_t *) &p_config->pext_csd);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_10000, BSP_DELAY_UNITS_MICROSECONDS);

        if (err)
        {
            continue;
        }

        err = r_sdemmc_emmc_decode_ext_csd(p_ctrl, p_config);

        if (!err)
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(err);
    }

    if (0 != p_config->ext_csd.hs_max_dtr)
    {
        err =
            r_sdemmc_emmc_cmd_with_res(p_ctrl,
                                       SDEMMC_W_PRV_CMD_SWITCH,
                                       r_sdemmc_emmc_make_switch_arg(SDEMMC_W_PRV_E_CSD_CMD_SET_NORMAL,
                                                                     SDEMMC_W_PRV_EMMC_EXT_CSD_HS_TIMING_OFFSET, 1),
                                       &rsp);

        if (err)
        {
            err = FSP_SUCCESS;
        }
    }

    R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

    for (i = 0; i < SDEMMC_W_PRV_MMC_RETRY_COUNT; i++)
    {
        err =
            r_sdemmc_emmc_cmd_with_res(p_ctrl,
                                       SDEMMC_W_PRV_CMD_SWITCH,
                                       r_sdemmc_emmc_make_switch_arg(SDEMMC_W_PRV_E_CSD_CMD_SET_NORMAL,
                                                                     SDEMMC_W_PRV_E_CSD_BUS_WIDTH,
                                                                     SDEMMC_W_SDEMMC_DT_WIDTH_1BIT),
                                       &rsp);
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);

        if (!err)
        {
            break;
        }
    }

    if (SDEMMC_W_PRV_MMC_RETRY_COUNT == i)
    {
        FSP_RETURN(err);
    }

    p_config->card_type = SDMMC_PRIV_CT_MMC_CARD;

    return FSP_SUCCESS;
#else                                  /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_config);
    FSP_PARAMETER_NOT_USED(ocr);
    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif                                 /* SDEMMC_W_CFG_EMMC_SUPPORT_ENABLE */
}

#if SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE

static fsp_err_t r_sdemmc_hw_sdemmc_sdio_func_enable (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                      st_sdemmc_config_t       * p_config,
                                                      uint32_t                   func_num)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t   reg = 0;
    FSP_PARAMETER_NOT_USED(p_config);

    err = r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, SDEMMC_W_PRV_SDIO_CCCR_IOEX, 0, &reg);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    reg |= (uint8_t) (1 << func_num);

    err = r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_WRITE, 0, SDEMMC_W_PRV_SDIO_CCCR_IOEX, reg, NULL);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    int32_t i;
    for (i = 0; i < SDEMMC_W_PRV_SDIO_CCR_IOR_RETRY_COUNT; i++)
    {
        err = r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_READ, 0, SDEMMC_W_PRV_SDIO_CCCR_IORX, 0, &reg);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (reg & (1 << func_num))
        {
            break;
        }

        err = FSP_ERR_TIMEOUT;
        R_BSP_SoftwareDelay(SDEMMC_W_PRV_EMMC_DELAY_100, BSP_DELAY_UNITS_MICROSECONDS);
    }

    if (SDEMMC_W_PRV_SDIO_CCR_IOR_RETRY_COUNT == i)
    {
        FSP_RETURN(FSP_ERR_TIMEOUT);
    }

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_hw_sdemmc_sdio_set_block_size (sdemmc_w_instance_ctrl_t * p_ctrl,
                                                         uint32_t                   func_num,
                                                         uint32_t                   blk_size)
{
    fsp_err_t err = FSP_SUCCESS;

    if (blk_size > SDEMMC_W_MAX_BLOCK_SIZE)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    if (0 == blk_size)
    {
        FSP_RETURN(FSP_ERR_INVALID_ARGUMENT);
    }

    err =
        r_sdemmc_sdio_io_rw_direct(p_ctrl,
                                   SDEMMC_W_PRV_SDIO_CMD52_WRITE,
                                   0,
                                   (SDEMMC_W_PRV_SDIO_FBR_BASE(func_num) + SDEMMC_W_SDIO_FBR_BLKSZ),
                                   (blk_size & 0xff),
                                   NULL);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err =
        r_sdemmc_sdio_io_rw_direct(p_ctrl, SDEMMC_W_PRV_SDIO_CMD52_WRITE, 0,
                                   (SDEMMC_W_PRV_SDIO_FBR_BASE(func_num) + SDEMMC_W_SDIO_FBR_BLKSZ + 1),
                                   ((blk_size >> 8) & 0xff), NULL);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif                                 /* SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE */

#if (CFG_PMGR == 1) && (SDEMMC_W_CFG_SDIO_SUPPORT_ENABLE == 1)

/*******************************************************************************************************************/ /**
 * Prepare SDIO for sleep mode 4/5
 *
 * @param[in] p_context Pointer to PMGR interface of SDIO instance
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_w_enter_sleep (sdemmc_w_pmgr_context_t * p_context)
{
    fsp_err_t err = FSP_SUCCESS;
 #if (SDEMMC_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_context);
 #endif

    sdemmc_w_instance_ctrl_t * p_ctrl = p_context->p_ctrl;
    FSP_ERROR_RETURN(p_ctrl->open == SDEMMC_W_PRV_OPEN, FSP_ERR_INVALID_MODE);

    /* Backup actual HW regs state */
    p_context->state.SDIO_CCCR_REG               = p_ctrl->p_reg->SDIO_CCCR_REG;
    p_context->state.SDIO_OCR_REG                = p_ctrl->p_reg->SDIO_OCR_REG;
    p_context->state.SDIO_GLB_INT_ENA_REG        = p_ctrl->p_reg->SDIO_GLB_INT_ENA_REG;
    p_context->state.SDIO_AHB_FN0_INT_ENABLE_REG = p_ctrl->p_reg->SDIO_AHB_FN0_INT_ENABLE_REG;
    p_context->state.SDIO_AHB_FN0_INT_REG        = p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG;
    p_context->state.SDIO_AHB_FN1_INT_ENABLE_REG = p_ctrl->p_reg->SDIO_AHB_FN1_INT_ENABLE_REG;
    p_context->state.SDIO_AHB_FN1_INT_REG        = p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG;
    p_context->state.SDIO_FBR_REG                = p_ctrl->p_reg->SDIO_FBR_REG;
    p_context->state.SDIO_IOR_REG                = p_ctrl->p_reg->SDIO_IOR_REG;
    p_context->state.SDIO_GLB_INT_STS_REG        = p_ctrl->p_reg->SDIO_GLB_INT_STS_REG;
    p_context->state.SDIO_FUNRDY_REG             = p_ctrl->p_reg->SDIO_FUNRDY_REG;

    p_context->state.GPIO_SDIO_MODE_REG = GPIO->SDIO_MODE_REG;

    p_ctrl->open = SDEMMC_W_PRV_SLEEP;

    return err;
}

/*******************************************************************************************************************/ /**
 * Restore SDIO from wakeup
 *
 * @param[in] p_context Pointer to PMGR interface of SDIO instance
 **********************************************************************************************************************/
static fsp_err_t r_sdemmc_w_wakeup (sdemmc_w_pmgr_context_t * p_context)
{
    fsp_err_t err = FSP_SUCCESS;
 #if (SDEMMC_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_context);
 #endif
    sdemmc_w_instance_ctrl_t * p_ctrl = p_context->p_ctrl;

    FSP_ERROR_RETURN(p_ctrl->open == SDEMMC_W_PRV_SLEEP, FSP_ERR_INVALID_MODE);
    FSP_ASSERT(SDEMMC_W_ROLE_DEVICE == ((sdemmc_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->sdemmc_w_role);

    /* Restore HW regs state */
    p_ctrl->p_reg->SDIO_CCCR_REG               = p_context->state.SDIO_CCCR_REG;
    p_ctrl->p_reg->SDIO_OCR_REG                = p_context->state.SDIO_OCR_REG;
    p_ctrl->p_reg->SDIO_GLB_INT_ENA_REG        = p_context->state.SDIO_GLB_INT_ENA_REG;
    p_ctrl->p_reg->SDIO_AHB_FN0_INT_ENABLE_REG = p_context->state.SDIO_AHB_FN0_INT_ENABLE_REG;
    p_ctrl->p_reg->SDIO_AHB_FN0_INT_REG        = p_context->state.SDIO_AHB_FN0_INT_REG;
    p_ctrl->p_reg->SDIO_AHB_FN1_INT_ENABLE_REG = p_context->state.SDIO_AHB_FN1_INT_ENABLE_REG;
    p_ctrl->p_reg->SDIO_AHB_FN1_INT_REG        = p_context->state.SDIO_AHB_FN1_INT_REG;
    p_ctrl->p_reg->SDIO_FBR_REG                = p_context->state.SDIO_FBR_REG;
    p_ctrl->p_reg->SDIO_IOR_REG                = p_context->state.SDIO_IOR_REG;
    p_ctrl->p_reg->SDIO_GLB_INT_STS_REG        = p_context->state.SDIO_GLB_INT_STS_REG;
    p_ctrl->p_reg->SDIO_FUNRDY_REG             = p_context->state.SDIO_FUNRDY_REG;

    // TODO: is here a right place for this?
    GPIO->SDIO_MODE_REG = p_context->state.GPIO_SDIO_MODE_REG;

    CRG_PER->SET_CLK_COM_REG_b.SDIO_ENABLE = 1U;

    /* Configure and enable interrupts. */
    r_sdemmc_irq_enable(p_ctrl->p_cfg->sdio_irq, p_ctrl->p_cfg->sdio_ipl, p_ctrl);

    p_ctrl->open = SDEMMC_W_PRV_OPEN;

    return err;
}

static void r_sdemmc_w_pmgr_callback (pmgr_callback_args_t * p_args)
{
    pmgr_instance_info_t * p_pmgr_info = (pmgr_instance_info_t *) p_args->p_instance_info;

    if (p_pmgr_info->power_mode == PMGR_LLD_POWER_MODE_SLEEP4)
    {
        if (p_args->event == PMGR_EVENT_ENTERING_SLEEP)
        {
            /* Entering sleep 4/5 - close UART */
            r_sdemmc_w_enter_sleep((sdemmc_w_pmgr_context_t *) p_args->p_context);
        }
        else if (p_args->event == PMGR_EVENT_EXITING_SLEEP)
        {
            /* Open UART with previous settings */
            r_sdemmc_w_wakeup((sdemmc_w_pmgr_context_t *) p_args->p_context);
        }
    }
}

static fsp_err_t r_sdemmc_w_subscribe_for_pmgr_notifications (sdemmc_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;

    sdemmc_w_pmgr_context_t * context = &g_sdemmc_pmgr_context[p_ctrl->p_cfg->channel];

    context->pmgr_info.power_mode    = PMGR_LLD_POWER_MODE_SLEEP4;
    context->pmgr_info.wake_source   = PMGR_WAKE_SOURCE_NONE,
    context->pmgr_notifier_ext.order = PMGR_W_NOTIFIER_ORDER_SYS_LOW;
    context->p_ctrl = p_ctrl;

    context->clbk_args.constraints     = PMGR_CONSTRAINT_NONE;
    context->clbk_args.event           = PMGR_EVENT_NOT_SET;
    context->clbk_args.p_context       = (void *) context;
    context->clbk_args.p_instance_info = (void *) &context->pmgr_info;

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(pmgr_ctrl != NULL);

    err = RM_PMGR_W_notifier_register(pmgr_ctrl,
                                      r_sdemmc_w_pmgr_callback,
                                      &context->clbk_args,
                                      &context->pmgr_notifier_ext);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

static fsp_err_t r_sdemmc_w_unsubscribe_from_pmgr_notifications (sdemmc_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(pmgr_ctrl != NULL);

    sdemmc_w_pmgr_context_t * context = &g_sdemmc_pmgr_context[p_ctrl->p_cfg->channel];
    err = RM_PMGR_W_notifier_unregister(pmgr_ctrl, context->pmgr_notifier_ext.notifier_id);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

#endif
