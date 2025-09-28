/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include <string.h>

#include "r_flash_lp.h"

/* Configuration for this package. */
#include "r_flash_lp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "OPEN" in ASCII, used to avoid multiple open. */
#define FLASH_HP_OPEN                                 (0x4f50454eULL)

#define FLASH_HP_MINIMUM_SUPPORTED_FCLK_FREQ          (4000000U) /// Minimum FCLK for Flash Operations in Hz

/* The number of CPU cycles per each timeout loop. */
#ifndef FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP
 #if defined(__GNUC__)
  #define FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP    (6U)
 #elif defined(__ICCARM__)
  #define FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP    (6U)
 #endif
#endif

#define FLASH_LP_HZ_IN_MHZ                            (1000000U)

#if defined(__ICCARM__)
 #define BSP_ATTRIBUTE_STACKLESS                      __stackless
#elif defined(__GNUC__)

 #define BSP_ATTRIBUTE_STACKLESS                      __attribute__((naked))
#endif

/* Roughly 4 cycles per loop */
#define FLASH_LP_DELAY_LOOP_CYCLES                    4U

/*  flash mode definition (FENTRYR Register setting)*/
#define FLASH_LP_FENTRYR_DATAFLASH_PE_MODE            (0xAA80U)
#define FLASH_LP_FENTRYR_CODEFLASH_PE_MODE            (0xAA01U)
#define FLASH_LP_FENTRYR_READ_MODE                    (0xAA00U)

/*  flash mode definition (FPMCR Register setting)*/
#define FLASH_LP_DATAFLASH_PE_MODE                    (0x10U)
#define FLASH_LP_READ_MODE                            (0x08U)
#define FLASH_LP_LVPE_MODE                            (0x40U)
#define FLASH_LP_DISCHARGE_1                          (0x12U)
#define FLASH_LP_DISCHARGE_2                          (0x92U)
#define FLASH_LP_CODEFLASH_PE_MODE                    (0x82U)

/*  operation definition (FCR Register setting)*/
#define FLASH_LP_FCR_WRITE                            (0x81U)
#define FLASH_LP_FCR_ERASE                            (0x84U)
#define FLASH_LP_FCR_BLANKCHECK                       (0x83U)
#define FLASH_LP_FCR_CLEAR                            (0x00U)

/*  operation definition (FEXCR Register setting)*/
#define FLASH_LP_FEXCR_STARTUP                        (0x81U)
#define FLASH_LP_FEXCR_AW                             (0x82U)
#define FLASH_LP_FEXCR_OCDID1                         (0x83U)
#define FLASH_LP_FEXCR_OCDID2                         (0x84U)
#define FLASH_LP_FEXCR_OCDID3                         (0x85U)
#define FLASH_LP_FEXCR_OCDID4                         (0x86U)
#define FLASH_LP_FEXCR_CLEAR                          (0x00U)
#define FLASH_LP_FEXCR_MF4_CONTROL                    (0x81U)
#define FLASH_LP_FEXCR_MF4_AW_STARTUP                 (0x82U)

/* Wait Process definition */
#define FLASH_LP_WAIT_TDIS                            (3U)
#if (BSP_FEATURE_FLASH_LP_VERSION == 4)
 #define FLASH_LP_WAIT_TMS_HIGH                       (16U) // "Flash memory mode transition wait time 2" in the "Code Flash Memory Characteristics" subsection of the hardware manual
#else
 #define FLASH_LP_WAIT_TMS_HIGH                       (6U)  // tMS wait time on flash version 3
#endif
#define FLASH_LP_WAIT_TMS_MID                         (4U)
#define FLASH_LP_WAIT_TDSTOP                          (6U)

/* Flash information */
/* Used for DataFlash */
#define FLASH_LP_DATAFLASH_READ_BASE_ADDR             (0x40100000U)
#define FLASH_LP_DATAFLASH_WRITE_BASE_ADDR            (0xFE000000U)
#define FLASH_LP_DATAFLASH_ADDR_OFFSET                (FLASH_LP_DATAFLASH_WRITE_BASE_ADDR - \
                                                       FLASH_LP_DATAFLASH_READ_BASE_ADDR)

#define FLASH_LP_FENTRYR_DF_PE_MODE                   (0x0080U)
#define FLASH_LP_FENTRYR_CF_PE_MODE                   (0x0001U)
#define FLASH_LP_FENTRYR_PE_MODE_BITS                 (FLASH_LP_FENTRYR_DF_PE_MODE | FLASH_LP_FENTRYR_CF_PE_MODE)

#if BSP_FEATURE_FLASH_LP_VERSION == 4
 #define FLASH_LP_PRV_FENTRYR                         R_FACI_LP->FENTRYR_MF4
#else
 #define FLASH_LP_PRV_FENTRYR                         R_FACI_LP->FENTRYR
#endif

#define FLASH_LP_FSCMR_FSPR_AND_UNUSED_BITS           (0xFEFFU)

#define FLASH_LP_MF4_FAWEMR_STARTUP_AREA_MASK         (0x8000U)

#define FLASH_LP_FCR_PROCESSING_MASK                  (0x80U)
#define FLASH_LP_FEXCR_PROCESSING_MASK                (0x80U)

#define FLASH_LP_MAX_WRITE_CF_TIME_US                 (1411)
#define FLASH_LP_MAX_WRITE_DF_TIME_US                 (886)
#define FLASH_LP_MAX_BLANK_CHECK_TIME_US              (88)
#define FLASH_LP_MAX_ERASE_CF_BLOCK_TIME_US           (355000)
#define FLASH_LP_MAX_ERASE_DF_BLOCK_TIME_US           (504000)
#define FLASH_LP_MAX_WRITE_EXTRA_AREA_TIME_US         (2289000)

#define FLASH_LP_FSTATR2_ILLEGAL_ERROR_BITS           (0x10)
#define FLASH_LP_FSTATR2_ERASE_ERROR_BITS             (0x11)
#define FLASH_LP_FSTATR2_WRITE_ERROR_BITS             0x12

#define FLASH_LP_FISR_INCREASE_PCKA_EVERY_2MHZ        (32)

#define FLASH_LP_3BIT_MASK                            (0x7U)
#define FLASH_LP_6BIT_MASK                            (0x3FU)
#define FLASH_LP_5BIT_MASK                            (0x1FU)

#define FLASH_LP_DF_START_ADDRESS                     (0x40100000)

#define FLASH_LP_FPR_UNLOCK                           (0xA5U)

#define FLASH_LP_BANK_PROGRAMMING_EXIT                (0x6D00)
#define FLASH_LP_BANK_PROGRAMMING_ENTER               (0x6D01)

#define FLASH_LP_BANK_SWAP_UPDATE_ENABLE              (0xC301)
#define FLASH_LP_BANK_SWAP_UPDATE_DISABLE             (0xC300)
#define FLASH_LP_EXTRA_AREA_FCTLF_ADDRESS             (0x01010008)

/** The maximum timeout for commands is 100usec when FCLK is 16 MHz i.e. 1600 FCLK cycles.
 * Assuming worst case of ICLK at 240 MHz and FCLK at 4 MHz, and optimization set to max such that
 * each count decrement loop takes only 5 cycles, then ((240/4)*1600)/5 = 19200 */
#define FLASH_LP_FRDY_CMD_TIMEOUT                     (19200)

#define FLASH_LP_REGISTER_WAIT_TIMEOUT(val, reg, timeout, err) \
    while (val != reg)                                         \
    {                                                          \
        if (0 == timeout)                                      \
        {                                                      \
            return err;                                        \
        }                                                      \
        timeout--;                                             \
    }

/** Flash P/E related functions are not required to be in RAM when using Bank Programming. */
#if (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 0)
 #define FLASH_PE_PLACE_IN_RAM_SECTION    PLACE_IN_RAM_SECTION
#else
 #define FLASH_PE_PLACE_IN_RAM_SECTION
#endif

/******************************************************************************
 * Typedef definitions
 ******************************************************************************/

/**
 * @struct r_dataflash_data_t
 * DATAFLASH information values
 */
typedef struct r_dataflash_data_t
{
    uint32_t start_addr;               /* start address (Erase) or Ram Source for Write, Dest for read */
    uint32_t end_addr;                 /* end address (Erase), or Flash Start address which will be read/written */
    uint32_t write_cnt;                /* bytes remaining to do */
} r_dataflash_data_t;

typedef struct r_dataflash_erase_t
{
    uint32_t start_addr;               /* start address (Erase) or Ram Source for Write, Dest for read */
    uint32_t end_addr;                 /* end address (Erase), or Flash Start address which will be read/written */
    uint32_t write_cnt;                /* bytes remaining to do */
} r_dataflash_erase_t;

/**   FLASH operation command values */
typedef enum e_flash_command
{
    FLASH_COMMAND_ACCESSWINDOW,        /**< Flash access window command */
    FLASH_COMMAND_STARTUPAREA          /**< Flash change startup area command */
} r_flash_command_t;

/******************************************************************************
 * Exported global variables
 ******************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_flash_lp_init(flash_lp_instance_ctrl_t * p_ctrl);

static void r_flash_lp_df_enter_pe_mode(flash_lp_instance_ctrl_t * const p_ctrl);

#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)

static void r_flash_lp_df_write_operation(flash_lp_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_flash_lp_df_blankcheck(flash_lp_instance_ctrl_t * const p_ctrl,
                                          uint32_t                         start_address,
                                          uint32_t                         num_bytes,
                                          flash_result_t                 * result);

static fsp_err_t r_flash_lp_df_erase(flash_lp_instance_ctrl_t * const p_ctrl,
                                     uint32_t                         block_address,
                                     uint32_t                         num_blocks);

#endif

static fsp_err_t r_flash_lp_set_fisr(flash_lp_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_flash_lp_setup(flash_lp_instance_ctrl_t * p_ctrl);

static void r_flash_lp_process_command(const uint32_t start_addr, uint32_t num_bytes,
                                       uint32_t command) FLASH_PE_PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_command_finish(uint32_t timeout) FLASH_PE_PLACE_IN_RAM_SECTION;

static void r_flash_lp_reset(flash_lp_instance_ctrl_t * const p_ctrl) PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_wait_for_ready(flash_lp_instance_ctrl_t * const p_ctrl,
                                           uint32_t                         timeout,
                                           uint32_t                         error_bits,
                                           fsp_err_t                        return_code) FLASH_PE_PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_write(flash_lp_instance_ctrl_t * const p_ctrl) FLASH_PE_PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_pe_mode_exit(flash_lp_instance_ctrl_t * const p_ctrl) PLACE_IN_RAM_SECTION;

static void r_flash_lp_delay_us(uint32_t us, uint32_t mhz) PLACE_IN_RAM_SECTION __attribute__((noinline));

static void r_flash_lp_write_fpmcr(uint8_t value) PLACE_IN_RAM_SECTION;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
static void r_flash_lp_memcpy(uint8_t * const dest, uint8_t * const src, uint32_t len) FLASH_PE_PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_extra_command_finish(uint32_t timeout) PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_cf_blankcheck(flash_lp_instance_ctrl_t * const p_ctrl,
                                          uint32_t                         start_address,
                                          uint32_t                         num_bytes,
                                          flash_result_t                 * result) FLASH_PE_PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_cf_erase(flash_lp_instance_ctrl_t * const p_ctrl,
                                     uint32_t                         block_address,
                                     uint32_t                         num_blocks,
                                     uint32_t                         block_size) FLASH_PE_PLACE_IN_RAM_SECTION;

static void r_flash_lp_cf_write_operation(flash_lp_instance_ctrl_t * const p_ctrl) FLASH_PE_PLACE_IN_RAM_SECTION;

static void r_flash_lp_cf_enter_pe_mode(flash_lp_instance_ctrl_t * const p_ctrl, bool bank_programming)
PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_extra_check(flash_lp_instance_ctrl_t * const p_ctrl) PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_set_startup_area_boot(flash_lp_instance_ctrl_t * const p_ctrl,
                                                  flash_startup_area_swap_t        swap_type,
                                                  bool                             temporary)
PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_access_window_set(flash_lp_instance_ctrl_t * const p_ctrl,
                                              uint32_t const                   start_addr,
                                              uint32_t const                   end_addr) PLACE_IN_RAM_SECTION;

static fsp_err_t r_flash_lp_set_id_code(flash_lp_instance_ctrl_t * const p_ctrl,
                                        uint8_t const * const            p_id_code,
                                        flash_id_code_mode_t             mode) PLACE_IN_RAM_SECTION;

static void r_flash_lp_extra_operation(const uint32_t    start_addr_startup_value,
                                       const uint32_t    end_addr,
                                       r_flash_command_t command) PLACE_IN_RAM_SECTION;

 #if (BSP_FEATURE_FLASH_LP_SUPPORTS_DUAL_BANK == 1)
static fsp_err_t r_flash_lp_bank_swap(flash_lp_instance_ctrl_t * const p_ctrl) PLACE_IN_RAM_SECTION;

 #endif

#endif

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)

static fsp_err_t r_flash_lp_common_parameter_checking(flash_lp_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_flash_lp_write_read_bc_parameter_checking(flash_lp_instance_ctrl_t * const p_ctrl,
                                                             uint32_t                         flash_address,
                                                             uint32_t const                   num_bytes,
                                                             bool                             check_write);

#endif

/** FRDY ISR is only used for DataFlash operations and Code flash operations when Bank Programming is supported.
 *  Other Code flash operations are blocking. Therefore ISR does not need to be located in RAM.
 */
void fcu_frdyi_isr(void);

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
const flash_api_t g_flash_on_flash_lp =
{
    .open                         = R_FLASH_LP_Open,
    .close                        = R_FLASH_LP_Close,
    .write                        = R_FLASH_LP_Write,
    .erase                        = R_FLASH_LP_Erase,
    .blankCheck                   = R_FLASH_LP_BlankCheck,
    .statusGet                    = R_FLASH_LP_StatusGet,
    .infoGet                      = R_FLASH_LP_InfoGet,
    .accessWindowSet              = R_FLASH_LP_AccessWindowSet,
    .accessWindowClear            = R_FLASH_LP_AccessWindowClear,
    .idCodeSet                    = R_FLASH_LP_IdCodeSet,
    .reset                        = R_FLASH_LP_Reset,
    .startupAreaSelect            = R_FLASH_LP_StartUpAreaSelect,
    .bankSwap                     = R_FLASH_LP_BankSwap,
    .updateFlashClockFreq         = R_FLASH_LP_UpdateFlashClockFreq,
    .callbackSet                  = R_FLASH_LP_CallbackSet,
    .antiRollbackCounterIncrement = R_FLASH_LP_AntiRollbackCounterIncrement,
    .antiRollbackCounterRefresh   = R_FLASH_LP_AntiRollbackCounterRefresh,
    .antiRollbackCounterRead      = R_FLASH_LP_AntiRollbackCounterRead,
    .userLockableAreaWrite        = R_FLASH_LP_UserLockableAreaWrite,
};

const flash_block_info_t g_code_flash_macro_info =
{
    .block_section_st_addr  = 0,
    .block_section_end_addr = BSP_ROM_SIZE_BYTES - 1,
    .block_size             = BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE,
    .block_size_write       = BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE
};

static flash_regions_t g_flash_code_region =
{
    .num_regions   = 1,
    .p_block_array = &g_code_flash_macro_info
};

const flash_block_info_t g_data_flash_macro_info =
{
    .block_section_st_addr  = FLASH_LP_DF_START_ADDRESS,
    .block_section_end_addr = FLASH_LP_DF_START_ADDRESS + BSP_DATA_FLASH_SIZE_BYTES - 1,
    .block_size             = BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE,
    .block_size_write       = BSP_FEATURE_FLASH_LP_DF_WRITE_SIZE
};

static flash_regions_t g_flash_data_region =
{
    .num_regions   = 1,
    .p_block_array = &g_data_flash_macro_info
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup FLASH_LP
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the Low Power flash peripheral. Implements @ref flash_api_t::open.
 *
 * The Open function initializes the Flash.
 *
 * This function must be called once prior to calling any other FLASH API functions. If a user supplied callback
 * function is supplied, then the Flash Ready interrupt will be configured to call the users callback routine with an
 * Event type describing the source of the interrupt for Data Flash operations.
 *
 * Example:
 * @snippet r_flash_lp_example.c R_FLASH_LP_Open
 *
 * @note       Providing a callback function in the supplied p_cfg->callback field automatically configures the Flash
 *             for Data Flash to operate in non-blocking background operation (BGO) mode.
 *
 * @retval     FSP_SUCCESS               Initialization was successful and timer has started.
 * @retval     FSP_ERR_ASSERTION         NULL provided for p_ctrl, p_cfg or p_callback if BGO is enabled.
 * @retval     FSP_ERR_IRQ_BSP_DISABLED  Caller is requesting BGO but the Flash interrupts are not enabled.
 * @retval     FSP_ERR_FCLK              FCLK must be a minimum of 4 MHz for Flash operations.
 * @retval     FSP_ERR_ALREADY_OPEN      Flash Open() has already been called.
 * @retval     FSP_ERR_TIMEOUT           Failed to exit P/E mode after configuring flash.
 * @retval     FSP_ERR_INVALID_STATE     The system is not running from the required clock or the required clock is not running and stable.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_Open (flash_ctrl_t * const p_api_ctrl, flash_cfg_t const * const p_cfg)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

    /* If null pointers return error. */
#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);

    /* If open return error. */
    FSP_ERROR_RETURN((FLASH_HP_OPEN != p_ctrl->opened), FSP_ERR_ALREADY_OPEN);
 #if BSP_FEATURE_FLASH_LP_VERSION == 4

    /* MF4 devices must have HOCO running and stable in order to program and erase flash. */
  #if BSP_FEATURE_CGC_REGISTER_SET_B

    /* HOCO is selected when ICLK source is FMAIN, FMAIN source is FOCO, and FOCO source is HOCO. */
    FSP_ERROR_RETURN((0U == R_SYSTEM->ICLKSCR_b.CKST) &&
                     (0U == R_SYSTEM->FMAINSCR_b.CKST) &&
                     (0U == R_SYSTEM->FOCOSCR_b.CKST),
                     FSP_ERR_INVALID_STATE);
  #else

    /* If HOCO is not operating, return error */
    FSP_ERROR_RETURN(0U == R_SYSTEM->HOCOCR_b.HCSTP, FSP_ERR_INVALID_STATE);

    /* If HOCO is not stable, return error */
    FSP_ERROR_RETURN(1U == R_SYSTEM->OSCSF_b.HOCOSF, FSP_ERR_INVALID_STATE);
  #endif
 #endif

 #if FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1 || FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1

    /* Background operations are enabled but the flash interrupt is disabled. */
    if (p_cfg->data_flash_bgo || (1U == FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE))
    {
        FSP_ERROR_RETURN(p_cfg->irq >= (IRQn_Type) 0, FSP_ERR_IRQ_BSP_DISABLED);
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }
 #endif
#endif
    p_ctrl->p_cfg = p_cfg;

#if FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1 || FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1
    if (p_cfg->data_flash_bgo || (1U == FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE))
    {
        R_BSP_IrqCfg(p_cfg->irq, p_cfg->ipl, p_ctrl);
    }
#endif

    p_ctrl->current_operation = FLASH_OPERATION_NON_BGO;

    /* Check FCLK, calculate timeout values. */
    err = r_flash_lp_setup(p_ctrl);
    FSP_ERROR_RETURN((err == FSP_SUCCESS), err);

    /* Set the FlashIF peripheral clock frequency. */
    err = r_flash_lp_set_fisr(p_ctrl);
    FSP_ERROR_RETURN((err == FSP_SUCCESS), err);

    p_ctrl->opened = FLASH_HP_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Write to the specified Code or Data Flash memory area. Implements @ref flash_api_t::write.
 *
 * Example:
 * @snippet r_flash_lp_example.c R_FLASH_LP_Write
 *
 * @retval     FSP_SUCCESS               Operation successful. If BGO is enabled this means the operation was started
 *                                       successfully.
 * @retval     FSP_ERR_IN_USE            The Flash peripheral is busy with a prior on-going transaction.
 * @retval     FSP_ERR_NOT_OPEN          The Flash API is not Open.
 * @retval     FSP_ERR_WRITE_FAILED      Status is indicating a Programming error for the requested operation. This may
 *                                       be returned if the requested Flash area is not blank.
 * @retval     FSP_ERR_TIMEOUT           Timed out waiting for FCU operation to complete.
 * @retval     FSP_ERR_INVALID_SIZE      Number of bytes provided was not a multiple of the programming size or exceeded
 *                                       the maximum range.
 * @retval     FSP_ERR_INVALID_ADDRESS   Invalid address was input or address not on programming boundary.
 * @retval     FSP_ERR_ASSERTION         NULL provided for p_ctrl.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_Write (flash_ctrl_t * const p_api_ctrl,
                            uint32_t const       src_address,
                            uint32_t             flash_address,
                            uint32_t const       num_bytes)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)

    /* Check parameters. If failure return error */
    err = r_flash_lp_write_read_bc_parameter_checking(p_ctrl, flash_address, num_bytes, true);
    FSP_ERROR_RETURN((err == FSP_SUCCESS), err);
#endif

    p_ctrl->current_operation = FLASH_OPERATION_NON_BGO;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1) && (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)
    if (flash_address < BSP_ROM_SIZE_BYTES)
    {
 #if FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1

        /* Verify the source address is not in BANK1 of code flash. It will not be available in P/E mode. */
        FSP_ERROR_RETURN((src_address > BSP_ROM_SIZE_BYTES) || ((src_address + num_bytes) < (BSP_ROM_SIZE_BYTES / 2)),
                         FSP_ERR_INVALID_ADDRESS);

        /* The target flash area must be in Bank1 when using Bank Programming. */
        FSP_ERROR_RETURN(flash_address >= (BSP_FEATURE_FLASH_CODE_FLASH_START + (BSP_ROM_SIZE_BYTES / 2)),
                         FSP_ERR_INVALID_ADDRESS);
 #else

        /* Verify the source address is not in code flash. It will not be available in P/E mode. */
        FSP_ASSERT(src_address > BSP_ROM_SIZE_BYTES);
 #endif
    }
#endif

    p_ctrl->dest_end_address     = flash_address;
    p_ctrl->source_start_address = src_address;
    p_ctrl->operations_remaining = num_bytes;

    err = r_flash_lp_write(p_ctrl);

    /* Return status. */
    return err;
}

/*******************************************************************************************************************//**
 * Erase the specified Code or Data Flash blocks. Implements @ref flash_api_t::erase.
 *
 * Example:
 * @snippet r_flash_lp_example.c R_FLASH_LP_Erase
 *
 * @retval     FSP_SUCCESS               Successful open.
 * @retval     FSP_ERR_INVALID_BLOCKS    Invalid number of blocks specified
 * @retval     FSP_ERR_INVALID_ADDRESS   Invalid address specified
 * @retval     FSP_ERR_IN_USE            Other flash operation in progress, or API not initialized
 * @retval     FSP_ERR_ASSERTION         NULL provided for p_ctrl
 * @retval     FSP_ERR_NOT_OPEN          The Flash API is not Open.
 * @retval     FSP_ERR_TIMEOUT           Timed out waiting for FCU to be ready.
 * @retval     FSP_ERR_ERASE_FAILED      Status is indicating a Erase error.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_Erase (flash_ctrl_t * const p_api_ctrl, uint32_t const address, uint32_t const num_blocks)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)

    /* Verify the control block is not null and is opened. */
    err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If invalid number of blocks return error. */
    FSP_ERROR_RETURN(num_blocks != 0U, FSP_ERR_INVALID_BLOCKS);
#endif

    p_ctrl->current_operation = FLASH_OPERATION_NON_BGO;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

    /* Configure the current parameters based on if the operation is for code flash or data flash. */
    if (address < BSP_ROM_SIZE_BYTES)
    {
        uint32_t start_address = address & ~(BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE - 1);

 #if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)
        uint32_t num_bytes = num_blocks * BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE;

  #if FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1

        /* Verify start address is in BANK1 */
        FSP_ERROR_RETURN(start_address >= (BSP_FEATURE_FLASH_CODE_FLASH_START + (BSP_ROM_SIZE_BYTES / 2)),
                         FSP_ERR_INVALID_ADDRESS);
  #endif

        /* Verify erase will not write past end of code flash */
        FSP_ERROR_RETURN((start_address + num_bytes) <= (BSP_FEATURE_FLASH_CODE_FLASH_START + BSP_ROM_SIZE_BYTES),
                         FSP_ERR_INVALID_BLOCKS);
 #endif

        err = r_flash_lp_cf_erase(p_ctrl, start_address, num_blocks, BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE);
    }
    else
#endif
    {
#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)
        uint32_t start_address = address & ~(BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE - 1);

 #if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)
        uint32_t num_bytes = num_blocks * BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE;

        FSP_ERROR_RETURN((start_address >= (FLASH_LP_DF_START_ADDRESS)) &&
                         (start_address < (FLASH_LP_DF_START_ADDRESS + BSP_DATA_FLASH_SIZE_BYTES)),
                         FSP_ERR_INVALID_ADDRESS);

        FSP_ERROR_RETURN(start_address + num_bytes <= (FLASH_LP_DF_START_ADDRESS + BSP_DATA_FLASH_SIZE_BYTES),
                         FSP_ERR_INVALID_BLOCKS);
 #endif

        /* Initiate the flash erase. */
        err = r_flash_lp_df_erase(p_ctrl, start_address, num_blocks);
#else

        return FSP_ERR_INVALID_ADDRESS;
#endif
    }

    return err;
}

/*******************************************************************************************************************//**
 * Perform a blank check on the specified address area. Implements @ref flash_api_t::blankCheck.
 *
 * Example:
 * @snippet r_flash_lp_example.c R_FLASH_LP_BlankCheck
 *
 * @retval     FSP_SUCCESS                 Blankcheck operation completed with result in p_blank_check_result, or
 *                                         blankcheck started and in-progess (BGO mode).
 * @retval     FSP_ERR_INVALID_ADDRESS     Invalid data flash address was input
 * @retval     FSP_ERR_INVALID_SIZE        'num_bytes' was either too large or not aligned for the CF/DF boundary size.
 * @retval     FSP_ERR_IN_USE              Flash is busy with an on-going operation.
 * @retval     FSP_ERR_ASSERTION           NULL provided for p_ctrl
 * @retval     FSP_ERR_NOT_OPEN            Flash API has not yet been opened.
 * @retval     FSP_ERR_TIMEOUT             Timed out waiting for the FCU to become ready.
 * @retval     FSP_ERR_BLANK_CHECK_FAILED  An error occurred during blank checking.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_BlankCheck (flash_ctrl_t * const p_api_ctrl,
                                 uint32_t const       address,
                                 uint32_t             num_bytes,
                                 flash_result_t     * p_blank_check_result)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)

    /* Check parameters. If failure return error */
    err = r_flash_lp_write_read_bc_parameter_checking(p_ctrl, address, num_bytes, false);
    FSP_ERROR_RETURN((err == FSP_SUCCESS), err);
#endif

    p_ctrl->current_operation = FLASH_OPERATION_NON_BGO;

    /* Initiate the Blank Check operation */
    /* Configure the current operation and wait count based on the number of bytes and if it's a data flash or code flash operation. */
    /* Is this a request to Blank check Code Flash? */
#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
    if (address < BSP_ROM_SIZE_BYTES)
    {
        /* This is a request to Blank check Code Flash */
        err = r_flash_lp_cf_blankcheck(p_ctrl, address, num_bytes, p_blank_check_result);
    }
    else
#endif
    {
#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)

        /* This is a request to Blank check Data Flash */
        err = r_flash_lp_df_blankcheck(p_ctrl, address, num_bytes, p_blank_check_result);
#endif
    }

    /* If failure reset the flash. */
    if (FSP_SUCCESS != err)
    {
        /* This will clear error flags and exit the P/E mode*/
        r_flash_lp_reset(p_ctrl);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Query the FLASH for its status. Implements @ref flash_api_t::statusGet.
 *
 * Example:
 * @snippet r_flash_lp_example.c R_FLASH_LP_StatusGet
 *
 * @retval     FSP_SUCCESS        Flash is ready and available to accept commands.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_ctrl
 * @retval     FSP_ERR_NOT_OPEN   Flash API has not yet been opened.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_StatusGet (flash_ctrl_t * const p_api_ctrl, flash_status_t * const p_status)
{
    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    /* If null control block return error. */
    FSP_ASSERT(NULL != p_ctrl);

    /* If null status pointer return error. */
    FSP_ASSERT(NULL != p_status);

    /* If control block is not open return error. */
    FSP_ERROR_RETURN((FLASH_HP_OPEN == p_ctrl->opened), FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    /* Return flash status */
    if ((FLASH_LP_PRV_FENTRYR & FLASH_LP_FENTRYR_PE_MODE_BITS) == 0x0000U)
    {
        *p_status = FLASH_STATUS_IDLE;
    }
    else
    {
        *p_status = FLASH_STATUS_BUSY;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Configure an access window for the Code Flash memory. Implements @ref flash_api_t::accessWindowSet.
 *
 * An access window defines a contiguous area in Code Flash for which programming/erase is enabled. This area is on
 * block boundaries. The block containing start_addr is the first block. The block containing end_addr is the last
 * block. The access window then becomes first block (inclusive) --> last block (exclusive). Anything outside this range
 * of Code Flash is then write protected. As an example, if you wanted to place an accesswindow on Code Flash Blocks 0
 * and 1, such that only those two blocks were writable, you would need to specify (address in block 0, address in block
 * 2) as the respective start and end address.
 * @note       If the start address and end address are set to the same value, then the access window is effectively
 *             removed. This accomplishes the same functionality as R_FLASH_LP_AccessWindowClear().
 *
 * The invalid address and programming boundaries supported and enforced by this function are dependent on the MCU in
 * use as well as the part package size. Please see the User manual and/or requirements document for additional
 * information.
 *
 * @param      p_api_ctrl                The p api control
 * @param[in]  start_addr                The start address
 * @param[in]  end_addr                  The end address
 *
 * @retval     FSP_SUCCESS               Access window successfully configured.
 * @retval     FSP_ERR_INVALID_ADDRESS   Invalid settings for start_addr and/or end_addr.
 * @retval     FSP_ERR_IN_USE            FLASH peripheral is busy with a prior operation.
 * @retval     FSP_ERR_ASSERTION         NULL provided for p_ctrl.
 * @retval     FSP_ERR_UNSUPPORTED       Code Flash Programming is not enabled.
 * @retval     FSP_ERR_NOT_OPEN          Flash API has not yet been opened.
 * @retval     FSP_ERR_TIMEOUT           Timed out waiting for the FCU to become ready.
 * @retval     FSP_ERR_WRITE_FAILED      Status is indicating a Programming error for the requested operation.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_AccessWindowSet (flash_ctrl_t * const p_api_ctrl,
                                      uint32_t const       start_addr,
                                      uint32_t const       end_addr)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
 #if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the control block is not null and is opened. */
    err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Note that the end_addr indicates the address up to, but not including the block that contains that address. */
    /* Therefore to allow the very last Block to be included in the access window we must allow for FLASH_CF_BLOCK_END+1 */
    /* If the start or end addresses are invalid return error. */
    FSP_ERROR_RETURN((start_addr <= end_addr) && (end_addr <= BSP_ROM_SIZE_BYTES), FSP_ERR_INVALID_ADDRESS);
 #endif

    /* Set the access window. */
    err = r_flash_lp_access_window_set(p_ctrl, start_addr, end_addr);
#else

    /* Remove warnings generated when Code Flash code is DISABLED. */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(start_addr);
    FSP_PARAMETER_NOT_USED(end_addr);

    /* If not code flash return error. */
    err = FSP_ERR_UNSUPPORTED;         // For consistency with _LP API we return error if Code Flash not enabled
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Remove any access window that is configured in the Code Flash. Implements @ref flash_api_t::accessWindowClear. On
 * successful return from this call all Code Flash is writable.
 *
 * @retval     FSP_SUCCESS               Access window successfully removed.
 * @retval     FSP_ERR_IN_USE            FLASH peripheral is busy with a prior operation.
 * @retval     FSP_ERR_ASSERTION         NULL provided for p_ctrl.
 * @retval     FSP_ERR_UNSUPPORTED       Code Flash Programming is not enabled.
 * @retval     FSP_ERR_NOT_OPEN          Flash API has not yet been opened.
 * @retval     FSP_ERR_TIMEOUT           Timed out waiting for the FCU to become ready.
 * @retval     FSP_ERR_WRITE_FAILED      Status is indicating a Programming error for the requested operation.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_AccessWindowClear (flash_ctrl_t * const p_api_ctrl)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    /* Eliminate warning if parameter checking is disabled. */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
 #if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the control block is not null and is opened. */
    err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif

    /* If successful clear the access window. When the start address and end address are set to the same value,
     * then the access window is effectively removed.  */
    err = r_flash_lp_access_window_set(p_ctrl, 0, 0);
#else

    /* Return error if Code Flash not enabled. */
    err = FSP_ERR_UNSUPPORTED;
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Write the ID code provided to the id code registers. Implements @ref flash_api_t::idCodeSet.
 *
 * @retval     FSP_SUCCESS               ID code successfully configured.
 * @retval     FSP_ERR_IN_USE            FLASH peripheral is busy with a prior operation.
 * @retval     FSP_ERR_ASSERTION         NULL provided for p_ctrl.
 * @retval     FSP_ERR_UNSUPPORTED       Code Flash Programming is not enabled.
 * @retval     FSP_ERR_NOT_OPEN          Flash API has not yet been opened.
 * @retval     FSP_ERR_TIMEOUT           Timed out waiting for completion of extra command.
 * @retval     FSP_ERR_WRITE_FAILED      Status is indicating a Programming error for the requested operation.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_IdCodeSet (flash_ctrl_t * const  p_api_ctrl,
                                uint8_t const * const p_id_code,
                                flash_id_code_mode_t  mode)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
 #if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the control block is not null and is opened. */
    err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Verify the id bytes are not in code flash. They will not be available in P/E mode. */
    FSP_ASSERT(((uint32_t) p_id_code) > BSP_ROM_SIZE_BYTES);
 #endif

    /* Set the id code. */
    err = r_flash_lp_set_id_code(p_ctrl, p_id_code, mode);
#else

    /* Eliminate warning if code flash programming is disabled. */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_id_code);
    FSP_PARAMETER_NOT_USED(mode);

    err = FSP_ERR_UNSUPPORTED;         // For consistency with _LP API we return error if Code Flash not enabled
#endif

    /* Return status. */
    return err;
}

/*******************************************************************************************************************//**
 * Reset the FLASH peripheral. Implements @ref flash_api_t::reset.
 *
 * No attempt is made to check if the flash is busy before executing the reset since the assumption is that a reset
 * will terminate any existing operation.
 * @retval     FSP_SUCCESS        Flash circuit successfully reset.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_ctrl
 * @retval     FSP_ERR_NOT_OPEN   Flash API has not yet been opened.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_Reset (flash_ctrl_t * const p_api_ctrl)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)

    /* If null control block return error. */
    FSP_ASSERT(NULL != p_ctrl);

    /* If control block is not open return error. */
    FSP_ERROR_RETURN((FLASH_HP_OPEN == p_ctrl->opened), FSP_ERR_NOT_OPEN);
#endif

    /* Reset the flash. */
    r_flash_lp_reset(p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * Select which block is used as the startup area block. Implements @ref flash_api_t::startupAreaSelect.
 *
 * Selects which block - Default (Block 0) or Alternate (Block 1) is used as the startup area block. The provided
 * parameters determine which block will become the active startup block and whether that action will be immediate (but
 * temporary), or permanent subsequent to the next reset. Doing a temporary switch might appear to have limited
 * usefulness. If there is an access window in place such that Block 0 is write protected, then one could do a temporary
 * switch, update the block and switch them back without having to touch the access window.
 *
 * @retval     FSP_SUCCESS               Start-up area successfully toggled.
 * @retval     FSP_ERR_IN_USE            Flash is busy with an on-going operation.
 * @retval     FSP_ERR_ASSERTION         NULL provided for p_ctrl
 * @retval     FSP_ERR_NOT_OPEN          Flash API has not yet been opened.
 * @retval     FSP_ERR_WRITE_FAILED      Status is indicating a Programming error for the requested operation.
 * @retval     FSP_ERR_TIMEOUT           Timed out waiting for the FCU to become ready.
 * @retval     FSP_ERR_UNSUPPORTED       Code Flash Programming is not enabled. Cannot set FLASH_STARTUP_AREA_BTFLG
 *                                       when the temporary flag is false.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_StartUpAreaSelect (flash_ctrl_t * const      p_api_ctrl,
                                        flash_startup_area_swap_t swap_type,
                                        bool                      is_temporary)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
 #if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the control block is not null and is opened. */
    err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif

    /* If the swap type is BTFLG and the operation is temporary there's nothing to do. */
    FSP_ASSERT(!((swap_type == FLASH_STARTUP_AREA_BTFLG) && (is_temporary == false)));

    err = r_flash_lp_set_startup_area_boot(p_ctrl, swap_type, is_temporary);
#else

    /* Eliminate warning if code flash programming is disabled. */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(swap_type);
    FSP_PARAMETER_NOT_USED(is_temporary);

    err = FSP_ERR_UNSUPPORTED;         // For consistency with _LP API we return error if Code Flash not enabled
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Swap the Code Flash bank to update new program. Implement @ref flash_api_t::bankSwap.
 *
 * Swap the flash bank located at address 0x00000000 and address 0x00040000. After a bank swap is done the MCU will
 * need to be reset for the changes to take place unless instant swap is enabled.
 *
 * To use this API, Code Flash Programming in the FSP Configuration Tool under Stack Properties must be enabled.
 *
 * @note This function only available on MCUs which support bank swap feature.
 *
 * @note When active bank is bank 1, startup program protection function is invalid.
 *
 * @param[in]   p_api_ctrl              The api control instance.
 *
 * @retval      FSP_SUCCESS             Banks were swapped.
 * @retval      FSP_ERR_UNSUPPORTED     Module does not support Bank Swap.
 * @retval      FSP_ERR_ASSERTION       NULL provided for p_ctrl.
 * @retval      FSP_ERR_NOT_OPEN        The control block is not open.
 * @retval      FSP_ERR_IN_USE          Extra area is being used by other command.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_BankSwap (flash_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1) && (BSP_FEATURE_FLASH_LP_SUPPORTS_DUAL_BANK == 1)
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

 #if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the control block is not null and is opened. */
    err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif

    err = r_flash_lp_bank_swap(p_ctrl);
#else

    /* Eliminate unused warning. */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    err = FSP_ERR_UNSUPPORTED;
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Indicate to the already open Flash API that the FCLK has changed. Implements flash_api_t::updateFlashClockFreq.
 *
 * This could be the case if the application has changed the system clock, and therefore the FCLK. Failure to call this
 * function subsequent to changing the FCLK could result in damage to the flash macro.
 *
 * @retval     FSP_SUCCESS        Start-up area successfully toggled.
 * @retval     FSP_ERR_IN_USE     Flash is busy with an on-going operation.
 * @retval     FSP_ERR_FCLK       Invalid flash clock source frequency.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_ctrl
 * @retval     FSP_ERR_NOT_OPEN   Flash API has not yet been opened.
 * @retval     FSP_ERR_TIMEOUT    Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_UpdateFlashClockFreq (flash_ctrl_t * const p_api_ctrl)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the control block is not null and is opened. */
    err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Check FCLK, calculate timeout values. */
    err = r_flash_lp_setup(p_ctrl);
    FSP_ERROR_RETURN((err == FSP_SUCCESS), err);

    /* Set the FlashIF peripheral clock frequency. */
    err = r_flash_lp_set_fisr(p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * Returns the information about the flash regions. Implements @ref flash_api_t::infoGet.
 *
 * @retval     FSP_SUCCESS        Successful retrieved the request information.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_ctrl or p_info.
 * @retval     FSP_ERR_NOT_OPEN   The flash is not open.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_InfoGet (flash_ctrl_t * const p_api_ctrl, flash_info_t * const p_info)
{
#if FLASH_LP_CFG_PARAM_CHECKING_ENABLE
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

    /* If null control block return error. */
    FSP_ASSERT(NULL != p_ctrl);

    /* If control block is not open return error. */
    FSP_ERROR_RETURN((FLASH_HP_OPEN == p_ctrl->opened), FSP_ERR_NOT_OPEN);

    FSP_ASSERT(NULL != p_info);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    /* Copy the region data to the info structure. */
    p_info->code_flash = g_flash_code_region;
    p_info->data_flash = g_flash_data_region;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Release any resources that were allocated by the Flash API. Implements @ref flash_api_t::close.
 *
 * @retval     FSP_SUCCESS        Successful close.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_ctrl or p_cfg.
 * @retval     FSP_ERR_NOT_OPEN   Flash API has not yet been opened.
 * @retval     FSP_ERR_IN_USE     The flash is currently in P/E mode.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_Close (flash_ctrl_t * const p_api_ctrl)
{
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) p_api_ctrl;

#if FLASH_LP_CFG_PARAM_CHECKING_ENABLE

    /* Verify the control block is not null and is opened. */
    fsp_err_t err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Mark the control block as closed. */
    p_ctrl->opened = 0;

#if FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1

    /* Disable the flash interrupt. */
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->irq)
    {
        /* Disable interrupt in ICU*/
        R_BSP_IrqDisable(p_ctrl->p_cfg->irq);
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stub function
 * Implements @ref flash_api_t::callbackSet.
 *
 * @retval  FSP_ERR_UNSUPPORTED          Function has not been implemented.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_CallbackSet (flash_ctrl_t * const          p_api_ctrl,
                                  void (                      * p_callback)(flash_callback_args_t *),
                                  void * const                  p_context,
                                  flash_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);
    FSP_PARAMETER_NOT_USED(p_callback_memory);
    FSP_PARAMETER_NOT_USED(p_context);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stub function
 * Implements @ref flash_api_t::antiRollbackCounterIncrement.
 *
 * @retval  FSP_ERR_UNSUPPORTED          Function has not been implemented.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_AntiRollbackCounterIncrement (flash_ctrl_t * const p_api_ctrl, flash_arc_t counter)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(counter);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stub function
 * Implements @ref flash_api_t::antiRollbackCounterRefresh.
 *
 * @retval  FSP_ERR_UNSUPPORTED          Function has not been implemented.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_AntiRollbackCounterRefresh (flash_ctrl_t * const p_api_ctrl, flash_arc_t counter)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(counter);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stub function
 * Implements @ref flash_api_t::antiRollbackCounterRead.
 *
 * @retval  FSP_ERR_UNSUPPORTED          Function has not been implemented.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_AntiRollbackCounterRead (flash_ctrl_t * const p_api_ctrl,
                                              flash_arc_t          counter,
                                              uint32_t * const     p_count)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(counter);
    FSP_PARAMETER_NOT_USED(p_count);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stub function
 * Implements @ref flash_api_t::userLockableAreaWrite.
 *
 * @retval  FSP_ERR_UNSUPPORTED          Function has not been implemented.
 **********************************************************************************************************************/
fsp_err_t R_FLASH_LP_UserLockableAreaWrite (flash_ctrl_t * const p_api_ctrl,
                                            uint32_t const       src_address,
                                            uint32_t             flash_address,
                                            uint32_t const       num_bytes)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(src_address);
    FSP_PARAMETER_NOT_USED(flash_address);
    FSP_PARAMETER_NOT_USED(num_bytes);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup FLASH_LP)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This function verifies that FCLK falls within the allowable range and calculates the timeout values based on the
 * current FCLK frequency.
 * @param      p_ctrl        The p control
 * @retval     FSP_SUCCESS   Success
 * @retval     FSP_ERR_FCLK  FCLK must be 1 MHz, 2 MHz, 3 MHz or a minimum of 4 MHz.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_setup (flash_lp_instance_ctrl_t * p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Get the frequency of the clock driving the flash. */
    p_ctrl->flash_clock_frequency = R_FSP_SystemClockHzGet(BSP_FEATURE_FLASH_LP_FLASH_CLOCK_SRC);

    /* FCLK must be 1 MHz, 2 MHz, 3 MHz or a minimum of 4 MHz for Flash operations. If not return error. */
    if (p_ctrl->flash_clock_frequency < FLASH_HP_MINIMUM_SUPPORTED_FCLK_FREQ)
    {
        FSP_ERROR_RETURN((p_ctrl->flash_clock_frequency == (1 * FLASH_LP_HZ_IN_MHZ)) ||
                         (p_ctrl->flash_clock_frequency == (2 * FLASH_LP_HZ_IN_MHZ)) ||
                         (p_ctrl->flash_clock_frequency == (3 * FLASH_LP_HZ_IN_MHZ)),
                         FSP_ERR_FCLK);
    }

    /* Get the frequency of the system clock. */
    p_ctrl->system_clock_frequency = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK);

    /* Initialize the flash timeout calculations and transfer global parameters to code and data flash layers. */
    r_flash_lp_init(p_ctrl);

    /* Enable the DataFlash if not already enabled */
    if (1U != R_FACI_LP->DFLCTL)
    {
        R_FACI_LP->DFLCTL = 1U;

        /* Wait for (tDSTOP) before reading from data flash. */
        r_flash_lp_delay_us(FLASH_LP_WAIT_TDSTOP, p_ctrl->system_clock_frequency);
    }

    return err;
}

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)

/*******************************************************************************************************************//**
 * This function performs the parameter checking required by Write, Read and BlankCheck functions.
 *
 * @param      p_ctrl                   Pointer to the control block
 * @param[in]  flash_address            The flash address
 * @param[in]  num_bytes                The number bytes
 * @param[in]  check_write              Check parameters for writing.
 *
 * @retval     FSP_SUCCESS              Parameter checking completed without error.
 * @retval     FSP_ERR_NOT_OPEN         The Flash API is not Open.
 * @retval     FSP_ERR_ASSERTION        Null pointer
 * @retval     FSP_ERR_INVALID_SIZE     Number of bytes provided was not a multiple of the programming size or exceeded
 *                                      the maximum range.
 * @retval     FSP_ERR_INVALID_ADDRESS  Invalid address was input or address not on programming boundary.
 * @retval     FSP_ERR_IN_USE           The flash is currently in P/E mode.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_write_read_bc_parameter_checking (flash_lp_instance_ctrl_t * const p_ctrl,
                                                              uint32_t                         flash_address,
                                                              uint32_t const                   num_bytes,
                                                              bool                             check_write)
{
    /* Verify the control block is not null and is opened. */
    fsp_err_t err = r_flash_lp_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If invalid address or number of bytes return error. */
 #if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 0)
    FSP_PARAMETER_NOT_USED(check_write);
 #else
    if (flash_address < BSP_ROM_SIZE_BYTES)
    {
        /* If the start address is in code flash verify the end address is in code flash. */
        FSP_ERROR_RETURN(flash_address + num_bytes <= BSP_ROM_SIZE_BYTES, FSP_ERR_INVALID_SIZE);

        if (check_write)
        {
            FSP_ERROR_RETURN(!(flash_address & (BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE - 1U)), FSP_ERR_INVALID_ADDRESS);
            FSP_ERROR_RETURN(!(num_bytes & (BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE - 1U)), FSP_ERR_INVALID_SIZE);
        }
    }
    else
 #endif
    {
 #if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)
        FSP_ERROR_RETURN((flash_address >= (FLASH_LP_DF_START_ADDRESS)) &&
                         (flash_address < (FLASH_LP_DF_START_ADDRESS + BSP_DATA_FLASH_SIZE_BYTES)),
                         FSP_ERR_INVALID_ADDRESS);
        FSP_ERROR_RETURN((flash_address + num_bytes <= (FLASH_LP_DF_START_ADDRESS + BSP_DATA_FLASH_SIZE_BYTES)),
                         FSP_ERR_INVALID_SIZE);
 #else

        return FSP_ERR_INVALID_ADDRESS;
 #endif
    }

    /* If invalid number of bytes return error. */
    FSP_ERROR_RETURN((0 != num_bytes), FSP_ERR_INVALID_SIZE);

    return FSP_SUCCESS;
}

#endif

#if (FLASH_LP_CFG_PARAM_CHECKING_ENABLE == 1)

/*******************************************************************************************************************//**
 * This function performs the parameter checking required by the R_FLASH_LP_Write() function.
 * @param      p_ctrl             Pointer to the control block
 *
 * @retval     FSP_SUCCESS        Parameter checking completed without error.
 * @retval     FSP_ERR_ASSERTION  Null pointer
 * @retval     FSP_ERR_NOT_OPEN   The flash module is not open.
 * @retval     FSP_ERR_IN_USE     The flash is currently in P/E mode.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_common_parameter_checking (flash_lp_instance_ctrl_t * const p_ctrl)
{
    /* If null control block return error. */
    FSP_ASSERT(NULL != p_ctrl);

    /* If control block is not open return error. */
    FSP_ERROR_RETURN((FLASH_HP_OPEN == p_ctrl->opened), FSP_ERR_NOT_OPEN);

    /* If the API is not ready return error. */
    FSP_ERROR_RETURN((FLASH_LP_PRV_FENTRYR & FLASH_LP_FENTRYR_PE_MODE_BITS) == 0x0000U, FSP_ERR_IN_USE);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * This function will calculate the timeout values for various operations.
 * @param[in]  p_ctrl          Pointer to the Flash control block
 **********************************************************************************************************************/
void r_flash_lp_init (flash_lp_instance_ctrl_t * p_ctrl)
{
    /* Round up the frequency to a whole number. */
    p_ctrl->flash_clock_frequency = (p_ctrl->flash_clock_frequency + (FLASH_LP_HZ_IN_MHZ - 1)) /
                                    FLASH_LP_HZ_IN_MHZ;

    /* If the frequency is over 32MHz round up to an even number. */
#if BSP_FEATURE_FLASH_LP_VERSION == 4
    if ((p_ctrl->flash_clock_frequency > FLASH_LP_FISR_INCREASE_PCKA_EVERY_2MHZ) &&
        (1 == p_ctrl->flash_clock_frequency % 2))
    {
        p_ctrl->flash_clock_frequency++;
    }
#endif

    p_ctrl->system_clock_frequency = (p_ctrl->system_clock_frequency + (FLASH_LP_HZ_IN_MHZ - 1)) /
                                     FLASH_LP_HZ_IN_MHZ;

    /*  According to HW Manual the Max Programming Time for 4 bytes(RA2L1) or 8 bytes(RA2A1/RA4M1)(ROM)
     *  is 1411us.  This is with a FCLK of 1MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    p_ctrl->timeout_write_cf =
        (uint32_t) (FLASH_LP_MAX_WRITE_CF_TIME_US * p_ctrl->system_clock_frequency) /
        FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Programming Time for 1 byte
     *  (Data Flash) is 886us.  This is with a FCLK of 4MHz. The calculation
     *  below calculates the number of ICLK ticks needed for the timeout delay.
     */
    p_ctrl->timeout_write_df =
        (uint32_t) (FLASH_LP_MAX_WRITE_DF_TIME_US * p_ctrl->system_clock_frequency) /
        FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Blank Check time for 2 bytes (S12*) or 8 bytes (RA2A1/RA4M1)
     *  (Code Flash) is 87.7 usec.  This is with a FCLK of 1MHz. The calculation
     *  below calculates the number of ICLK ticks needed for the timeout delay.
     */
    p_ctrl->timeout_blank_check =
        (uint32_t) (FLASH_LP_MAX_BLANK_CHECK_TIME_US * p_ctrl->system_clock_frequency) /
        FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Erasure Time for a 1KB block (S12*) or 2KB bytes (RA2A1/RA4M1) is
     *  around 289ms.  This is with a FCLK of 1MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    p_ctrl->timeout_erase_cf_block =
        (uint32_t) (FLASH_LP_MAX_ERASE_CF_BLOCK_TIME_US * p_ctrl->system_clock_frequency) /
        FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Erasure Time for a 1KB Data Flash block is
     *  around 299ms.  This is with a FCLK of 4MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    p_ctrl->timeout_erase_df_block =
        (uint32_t) (FLASH_LP_MAX_ERASE_DF_BLOCK_TIME_US * p_ctrl->system_clock_frequency) /
        FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Erasure Time for writing to the extra area is
     *  around 585ms. This is with a FCLK of 1MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    p_ctrl->timeout_write_extra_area =
        (uint32_t) (FLASH_LP_MAX_WRITE_EXTRA_AREA_TIME_US * p_ctrl->system_clock_frequency) /
        FLASH_LP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;
}

#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * This function erases a specified number of Code or Data Flash blocks
 *
 * @param[in]  p_ctrl                Pointer to the Flash control block
 * @param[in]  block_address         The starting address of the first block to erase.
 * @param[in]  num_blocks            The number of blocks to erase.
 *
 * @retval     FSP_SUCCESS           Successfully erased (non-BGO) mode or operation successfully started (BGO).
 * @retval     FSP_ERR_ERASE_FAILED  Erase failed. Flash could be locked or address could be under access window
 *                                   control.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_df_erase (flash_lp_instance_ctrl_t * const p_ctrl,
                                      uint32_t                         block_address,
                                      uint32_t                         num_blocks)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Enter data flash P/E mode. */
    r_flash_lp_df_enter_pe_mode(p_ctrl);

    /* Save the current operation parameters. */
    p_ctrl->source_start_address = block_address + FLASH_LP_DATAFLASH_ADDR_OFFSET;
    p_ctrl->operations_remaining = num_blocks;

    /* Start the code flash erase operation. */
    r_flash_lp_process_command(p_ctrl->source_start_address,
                               num_blocks * BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE,
                               FLASH_LP_FCR_ERASE);

    /* If configured for Blocking mode then don't return until the entire operation is complete */
 #if (FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1)
    if (!p_ctrl->p_cfg->data_flash_bgo)
 #endif
    {
        /* Waits for the erase commands to be completed and verifies the result of the command execution. */
        err = r_flash_lp_wait_for_ready(p_ctrl,
                                        p_ctrl->timeout_erase_df_block * num_blocks,
                                        FLASH_LP_FSTATR2_ERASE_ERROR_BITS,
                                        FSP_ERR_ERASE_FAILED);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Disable P/E mode for data flash. */
        r_flash_lp_pe_mode_exit(p_ctrl);
    }

 #if (FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1)
    else
    {
        p_ctrl->current_operation = FLASH_OPERATION_BGO_ERASE;
        p_ctrl->flash_status_mask = FLASH_LP_FSTATR2_ERASE_ERROR_BITS;
        p_ctrl->timeout           = p_ctrl->timeout_erase_df_block;
    }
 #endif

    return err;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * This function erases a specified number of Code Flash blocks
 *
 * @param[in]  p_ctrl                Pointer to the Flash control block
 * @param[in]  block_address         The starting address of the first block to erase.
 * @param[in]  num_blocks            The number of blocks to erase.
 * @param[in]  block_size            The Flash block size.
 *
 * @retval     FSP_SUCCESS           Successfully erased (non-BGO) mode or operation successfully started (BGO).
 * @retval     FSP_ERR_ERASE_FAILED  Status is indicating a Erase error.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_cf_erase (flash_lp_instance_ctrl_t * const p_ctrl,
                                      uint32_t                         block_address,
                                      uint32_t                         num_blocks,
                                      uint32_t                         block_size)
{
    fsp_err_t err = FSP_SUCCESS;

    r_flash_lp_cf_enter_pe_mode(p_ctrl, (bool) FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE);

    /* Start the code flash erase operation. */
    r_flash_lp_process_command(block_address, num_blocks * block_size, FLASH_LP_FCR_ERASE);

 #if (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
    p_ctrl->current_operation = FLASH_OPERATION_BGO_ERASE;
    p_ctrl->flash_status_mask = FLASH_LP_FSTATR2_ERASE_ERROR_BITS;
    p_ctrl->timeout           = p_ctrl->timeout_erase_cf_block;

    return err;
 #else

    /* Wait for the operation to complete. */
    err = r_flash_lp_wait_for_ready(p_ctrl,
                                    p_ctrl->timeout_erase_cf_block * num_blocks,
                                    FLASH_LP_FSTATR2_ERASE_ERROR_BITS,
                                    FSP_ERR_ERASE_FAILED);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return r_flash_lp_pe_mode_exit(p_ctrl);
 #endif
}

#endif

/*******************************************************************************************************************//**
 * This function writes a specified number of bytes to Code or Data Flash.
 *
 * @param[in]  p_ctrl                Pointer to the Flash control block
 *
 * @retval     FSP_SUCCESS           Data successfully written (non-BGO) mode or operation successfully started (BGO).
 * @retval     FSP_ERR_IN_USE        Command still executing.
 * @retval     FSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation. This may be
 *                                   returned if the requested Flash area is not blank.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for the Flash sequencer to become ready.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_write (flash_lp_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1) || (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
    bool bgo = false;
#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
    if (p_ctrl->dest_end_address < BSP_ROM_SIZE_BYTES)
    {
 #if (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
        p_ctrl->current_operation = FLASH_OPERATION_CF_BGO_WRITE;
        bgo = true;
 #endif

        p_ctrl->timeout              = p_ctrl->timeout_write_cf;
        p_ctrl->operations_remaining = p_ctrl->operations_remaining / BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE;
        r_flash_lp_cf_enter_pe_mode(p_ctrl, (bool) FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE);
    }
    else
#endif
    {
#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)
        if (p_ctrl->p_cfg->data_flash_bgo)
        {
            p_ctrl->current_operation = FLASH_OPERATION_DF_BGO_WRITE;
            bgo = true;
        }

        p_ctrl->timeout = p_ctrl->timeout_write_df;

        /* Enter data flash P/E mode. */
        r_flash_lp_df_enter_pe_mode(p_ctrl);
#endif
    }

    /* Select user area. */
    R_FACI_LP->FASR = 0U;

    while (p_ctrl->operations_remaining && (FSP_SUCCESS == err))
    {
#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)
        if (p_ctrl->dest_end_address < BSP_ROM_SIZE_BYTES)
        {
            /* Initiate the code flash write operation. */
            r_flash_lp_cf_write_operation(p_ctrl);
        }
        else
#endif
        {
#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)

            /* Initiate the data flash write operation. */
            r_flash_lp_df_write_operation(p_ctrl);
#endif
        }

#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1) || (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
        if (bgo)
        {
            p_ctrl->flash_status_mask = FLASH_LP_FSTATR2_WRITE_ERROR_BITS;

            return err;
        }
#endif

        err =
            r_flash_lp_wait_for_ready(p_ctrl, p_ctrl->timeout, FLASH_LP_FSTATR2_WRITE_ERROR_BITS, FSP_ERR_WRITE_FAILED);
    }

    /* If successful exit P/E mode. */
    if (FSP_SUCCESS == err)
    {
        r_flash_lp_pe_mode_exit(p_ctrl);
    }

    return err;
}

#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Execute a single Write operation on the Low Power Data Flash data.
 * See Figure 37.21 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  p_ctrl                      Pointer to the Flash control block
 **********************************************************************************************************************/
static void r_flash_lp_df_write_operation (flash_lp_instance_ctrl_t * const p_ctrl)
{
    uint32_t dest_addr_idx = p_ctrl->dest_end_address + FLASH_LP_DATAFLASH_ADDR_OFFSET;

    /* Conversion to the P/E address from the read address */
    uint8_t * data8_ptr = (uint8_t *) p_ctrl->source_start_address;

    /* Increment the start/end addresses of the next write before the current write is executed. */
    p_ctrl->source_start_address += BSP_FEATURE_FLASH_LP_DF_WRITE_SIZE;
    p_ctrl->dest_end_address     += BSP_FEATURE_FLASH_LP_DF_WRITE_SIZE;
    p_ctrl->operations_remaining--;

    /* Write flash address setting */
    R_FACI_LP->FSARH = (uint16_t) ((dest_addr_idx >> 16));
    R_FACI_LP->FSARL = (uint16_t) (dest_addr_idx);

    /* Write data address setting */
    R_FACI_LP->FWBL0 = *data8_ptr;     // For data flash there are only 8 bits used of the 16 in the reg

    /* Execute Write command */
    R_FACI_LP->FCR = FLASH_LP_FCR_WRITE;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Execute a single Write operation on the Low Power Code Flash data.
 * See Figure 37.19 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  p_ctrl                      Pointer to the Flash control block
 **********************************************************************************************************************/
static void r_flash_lp_cf_write_operation (flash_lp_instance_ctrl_t * const p_ctrl)
{
    uint16_t data[BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE / 2];

    /* Write flash address setting */
    R_FACI_LP->FSARH = (uint16_t) ((p_ctrl->dest_end_address >> 16));
    R_FACI_LP->FSARL = (uint16_t) (p_ctrl->dest_end_address);

    /* Copy the data and write them to the flash write buffers. CM23 parts to not support unaligned access so this
     * must be done using byte access. */
    r_flash_lp_memcpy((uint8_t *) data, (uint8_t *) p_ctrl->source_start_address, BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE);

    /* If there is more data to write then write the next data. */
    p_ctrl->source_start_address += BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE;
    p_ctrl->dest_end_address     += BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE;
    p_ctrl->operations_remaining--;

    R_FACI_LP->FWBL0 = data[0];
    R_FACI_LP->FWBH0 = data[1];
 #if BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE == 8
    R_FACI_LP->FWBL1 = data[2];
    R_FACI_LP->FWBH1 = data[3];
 #endif

    /* Execute Write command */
    R_FACI_LP->FCR = FLASH_LP_FCR_WRITE;
}

#endif

#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * This function checks if the specified Data Flash address range is blank.
 *
 * @param[in]  p_ctrl                      Pointer to the Flash control block
 * @param[in]  start_address               The starting address of the Flash area to blank check.
 * @param[in]  num_bytes                   Specifies the number of bytes that need to be checked.
 * @param[out] result                      Pointer that will be populated by the API with the results of the blank check
 *                                         operation in non-BGO (blocking) mode. In this case the blank check operation
 *                                         completes here and the result is returned. In Data Flash BGO mode the blank
 *                                         check operation is only started here and the result obtained later when the
 *                                         supplied callback routine is called.
 *
 * @retval     FSP_SUCCESS                 Blankcheck operation completed with result in result, or blankcheck started
 *                                         and in-progess (BGO mode).
 * @retval     FSP_ERR_TIMEOUT             Timed out waiting for the FCU to become ready.
 * @retval     FSP_ERR_BLANK_CHECK_FAILED  An error occurred during blank checking.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_df_blankcheck (flash_lp_instance_ctrl_t * const p_ctrl,
                                           uint32_t                         start_address,
                                           uint32_t                         num_bytes,
                                           flash_result_t                 * result)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Enter data flash P/E mode. */
    r_flash_lp_df_enter_pe_mode(p_ctrl);

    /* Execute blank check command. */
    r_flash_lp_process_command(start_address + FLASH_LP_DATAFLASH_ADDR_OFFSET, num_bytes, FLASH_LP_FCR_BLANKCHECK);

 #if (FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1)

    /* If in DF BGO mode, exit here; remaining processing if any will be done in ISR */
    if (p_ctrl->p_cfg->data_flash_bgo)
    {
        p_ctrl->current_operation = FLASH_OPERATION_DF_BGO_BLANKCHECK;
        *result         = FLASH_RESULT_BGO_ACTIVE;
        p_ctrl->timeout = p_ctrl->timeout_blank_check;

        return err;
    }
 #endif

    /* p_ctrl->timeout_blank_check specifies the wait time for a 4 code flash byte blank check. This is the same as
     * the wait time for a 1 byte Data Flash blankcheck.*/
    err =
        r_flash_lp_wait_for_ready(p_ctrl,
                                  p_ctrl->timeout_blank_check * num_bytes,
                                  FLASH_LP_FSTATR2_ILLEGAL_ERROR_BITS,
                                  FSP_ERR_BLANK_CHECK_FAILED);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check the result of the blank check. */
    if (0U != R_FACI_LP->FSTATR00_b.BCERR0) // Tested Flash Area is not blank
    {
        *result = FLASH_RESULT_NOT_BLANK;
    }
    else
    {
        *result = FLASH_RESULT_BLANK;
    }

    /* Return the data flash to P/E mode. */
    r_flash_lp_pe_mode_exit(p_ctrl);

    /* Return status. Blank status is in result. */
    return err;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * This function checks if the specified Data Flash address range is blank.
 *
 * @param[in]  p_ctrl                      Pointer to the Flash control block
 * @param[in]  start_address               The starting address of the Flash area to blank check.
 * @param[in]  num_bytes                   Specifies the number of bytes that need to be checked.
 * @param[out] result                      Pointer that will be populated by the API with the results of the blank check
 *                                         operation in non-BGO (blocking) mode. In this case the blank check operation
 *                                         completes here and the result is returned. In Data Flash BGO mode the blank
 *                                         check operation is only started here and the result obtained later when the
 *                                         supplied callback routine is called.
 *
 * @retval     FSP_SUCCESS                 Blankcheck operation completed with result in result, or blankcheck started
 *                                         and in-progess (BGO mode).
 * @retval     FSP_ERR_TIMEOUT             Timed out waiting for the FCU to become ready.
 * @retval     FSP_ERR_BLANK_CHECK_FAILED  An error occurred during blank checking.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_cf_blankcheck (flash_lp_instance_ctrl_t * const p_ctrl,
                                           uint32_t                         start_address,
                                           uint32_t                         num_bytes,
                                           flash_result_t                 * result)
{
    fsp_err_t err = FSP_SUCCESS;

    r_flash_lp_cf_enter_pe_mode(p_ctrl, (bool) FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE);

    /* Give the blank check command to the FACI. */
    r_flash_lp_process_command(start_address, num_bytes, FLASH_LP_FCR_BLANKCHECK);

 #if (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
    *result = FLASH_RESULT_BGO_ACTIVE;

    p_ctrl->flash_status_mask = FLASH_LP_FSTATR2_ILLEGAL_ERROR_BITS;
    p_ctrl->timeout           = p_ctrl->timeout_blank_check;

    p_ctrl->current_operation = FLASH_OPERATION_DF_BGO_BLANKCHECK;

    return err;
 #else

    /* p_ctrl->timeout_blank_check specifies the wait time for a 4 code flash byte blank check.
     * num_bytes is divided by 4 and then multiplied to calculate the wait time for the entire operation */
    uint32_t wait_count = p_ctrl->timeout_blank_check * ((num_bytes + 3) / 4);

    /* Wait for the blank check to complete and return result in control block. */
    err =
        r_flash_lp_wait_for_ready(p_ctrl, wait_count, FLASH_LP_FSTATR2_ILLEGAL_ERROR_BITS, FSP_ERR_BLANK_CHECK_FAILED);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (0U != R_FACI_LP->FSTATR00_b.BCERR0) // Tested Flash Area is not blank
    {
        /* If the result is already NOT Blank there is no reason to continue with any subsequent checks, simply return */
        *result = FLASH_RESULT_NOT_BLANK;
    }
    else
    {
        *result = FLASH_RESULT_BLANK;
    }

    /* Return the flash to P/E mode. */
    err = r_flash_lp_pe_mode_exit(p_ctrl);

    /* Return status. Blank status is in result. */
    return err;
 #endif
}

#endif

/*******************************************************************************************************************//**
 * Initiates a flash command.
 * See Figures 37.23, 37.24, 37.26 and 37.27 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  start_addr      Start address of the operation.
 * @param[in]  num_bytes       Number of bytes beginning at start_addr.
 * @param[in]  command         The flash command
 **********************************************************************************************************************/
static void r_flash_lp_process_command (const uint32_t start_addr, uint32_t num_bytes, uint32_t command)
{
    uint32_t end_addr_idx = start_addr + (num_bytes - 1U);

    /* Select User Area */
    R_FACI_LP->FASR = 0U;

    /* BlankCheck start address setting */
    R_FACI_LP->FSARH = (uint16_t) ((start_addr >> 16));
    R_FACI_LP->FSARL = (uint16_t) (start_addr);

    /* BlankCheck end address setting */
    R_FACI_LP->FEARH = (uint16_t) ((end_addr_idx >> 16));
    R_FACI_LP->FEARL = (uint16_t) (end_addr_idx);

    /* Execute BlankCheck command */
    R_FACI_LP->FCR = (uint8_t) command;
}

/*******************************************************************************************************************//**
 * This function switches the peripheral from P/E mode for Code Flash or Data Flash to Read mode.
 * See Figures 37.17 and 37.18 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  p_ctrl                    Pointer to the Flash control block
 * @retval     FSP_SUCCESS               Successfully entered P/E mode.
 * @retval     FSP_ERR_TIMEOUT           Timed out waiting for confirmation of transition to read mode
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_pe_mode_exit (flash_lp_instance_ctrl_t * const p_ctrl)
{
#if FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE
    uint32_t flash_pe_mode = FLASH_LP_PRV_FENTRYR;
#endif

    /* Timeout counter. */
    volatile uint32_t wait_cnt = FLASH_LP_FRDY_CMD_TIMEOUT;

#if BSP_FEATURE_FLASH_LP_VERSION == 3 && FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE
    if (flash_pe_mode == FLASH_LP_FENTRYR_CF_PE_MODE)
    {
        r_flash_lp_write_fpmcr(FLASH_LP_DISCHARGE_2);

        /* Wait for 2us over (tDIS) */
        r_flash_lp_delay_us(FLASH_LP_WAIT_TDIS, p_ctrl->system_clock_frequency);

        r_flash_lp_write_fpmcr(FLASH_LP_DISCHARGE_1);
    }
#endif

    r_flash_lp_write_fpmcr(FLASH_LP_READ_MODE);

    /* Wait for flash mode transition complete. The value of tMS will depend on flash version */
    r_flash_lp_delay_us(FLASH_LP_WAIT_TMS_HIGH, p_ctrl->system_clock_frequency);

#if FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE && (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
    if ((flash_pe_mode == FLASH_LP_FENTRYR_CF_PE_MODE) && (0U != R_FACI_LP->FBKPGCR))
    {
        R_FACI_LP->FBKPGCR = FLASH_LP_BANK_PROGRAMMING_EXIT;
    }
#endif

    /* Clear the P/E mode register */
    FLASH_LP_PRV_FENTRYR = FLASH_LP_FENTRYR_READ_MODE;

    /* Loop until the Flash P/E mode entry register is cleared or a timeout occurs. If timeout occurs return error. */
    FLASH_LP_REGISTER_WAIT_TIMEOUT(0, FLASH_LP_PRV_FENTRYR, wait_cnt, FSP_ERR_TIMEOUT);

#if FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE
    if (flash_pe_mode == FLASH_LP_FENTRYR_CF_PE_MODE)
    {
 #if BSP_FEATURE_BSP_FLASH_CACHE
        R_BSP_FlashCacheEnable();
 #endif
 #if BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER
        R_FACI_LP->PFBER = 1;
 #endif
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function resets the Flash sequencer.
 * See Figure 37.19 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  p_ctrl          Pointer to the Flash control block
 **********************************************************************************************************************/
static void r_flash_lp_reset (flash_lp_instance_ctrl_t * const p_ctrl)
{
    /* Cancel any in progress BGO operation. */
    p_ctrl->current_operation = FLASH_OPERATION_NON_BGO;

    /* If not currently in PE mode then enter P/E mode. */
    if (FLASH_LP_PRV_FENTRYR == 0x0000UL)
    {
        /* Enter P/E mode so that we can execute some FACI commands. Either Code or Data Flash P/E mode would work
         * but Code Flash P/E mode requires FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE ==1, which may not be true */
        r_flash_lp_df_enter_pe_mode(p_ctrl);
    }

    /* Reset the flash. */
    R_FACI_LP->FRESETR = 1U;
    R_FACI_LP->FRESETR = 0U;

    /* Transition to Read mode */
    r_flash_lp_pe_mode_exit(p_ctrl);
}

/*******************************************************************************************************************//**
 * FLASH ready interrupt routine.
 *
 * This function implements the FLASH ready isr. The function clears the interrupt request source on entry populates the
 * callback structure with the relevant event, and providing a callback routine has been provided, calls the callback
 * function with the event.
 **********************************************************************************************************************/
void fcu_frdyi_isr (void)
{
#if (FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1) || (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
    FSP_CONTEXT_SAVE
    flash_callback_args_t cb_data;
    bool operation_completed = true;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

 #if BSP_FEATURE_ICU_HAS_IELSR

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);
 #endif

    /* Recover ISR context saved in open. */
    flash_lp_instance_ctrl_t * p_ctrl = (flash_lp_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* If an error occurs reset and return error. */
    if ((FSP_ERR_TIMEOUT == r_flash_lp_command_finish(p_ctrl->timeout)) ||
        (0U != (R_FACI_LP->FSTATR2 & p_ctrl->flash_status_mask)))
    {
        r_flash_lp_reset(p_ctrl);

        cb_data.event = FLASH_EVENT_ERR_FAILURE;
    }
    else
    {
        /* Continue the current operation. If unknown operation set callback event to failure. */
        if (FLASH_OPERATION_BGO_ERASE == p_ctrl->current_operation)
        {
            cb_data.event = FLASH_EVENT_ERASE_COMPLETE;
        }

 #if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1)
        else if (FLASH_OPERATION_DF_BGO_WRITE == p_ctrl->current_operation)
        {
            if (p_ctrl->operations_remaining)
            {
                operation_completed = false;
                r_flash_lp_df_write_operation(p_ctrl);
            }
            else
            {
                cb_data.event = FLASH_EVENT_WRITE_COMPLETE;
            }
        }
 #endif
 #if (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
        else if (FLASH_OPERATION_CF_BGO_WRITE == p_ctrl->current_operation)
        {
            if (p_ctrl->operations_remaining)
            {
                operation_completed = false;
                r_flash_lp_cf_write_operation(p_ctrl);
            }
            else
            {
                cb_data.event = FLASH_EVENT_WRITE_COMPLETE;
            }
        }
 #endif
        else
        {
            /* Check the result and return it */
            if (R_FACI_LP->FSTATR00_b.BCERR0 == 1U)
            {
                cb_data.event = FLASH_EVENT_NOT_BLANK;
            }
            else
            {
                cb_data.event = FLASH_EVENT_BLANK;
            }
        }
    }

    /* If the operation completed exit read mode, release the flash, and call the callback if available. */
    if (operation_completed == true)
    {
        /* finished current operation. Exit P/E mode*/
        r_flash_lp_pe_mode_exit(p_ctrl);

        if (NULL != p_ctrl->p_cfg->p_callback)
        {
            cb_data.p_context = p_ctrl->p_cfg->p_context;

            /* Set data to identify callback to user, then call user callback. */
            p_ctrl->p_cfg->p_callback(&cb_data);
        }
    }
    FSP_CONTEXT_RESTORE
#endif
}

/*******************************************************************************************************************//**
 * Delay for the given number of micro seconds at the given frequency
 *
 * @note This is used instead of R_BSP_SoftwareDelay because that may be linked in code flash.
 *
 * @param[in]  us              Number of microseconds to delay
 * @param[in]  mhz             The frequency of the system clock
 **********************************************************************************************************************/
static void r_flash_lp_delay_us (uint32_t us, uint32_t mhz)
{
    uint32_t loop_cnt;

    // @12 MHz, one loop is 332 ns. A delay of 5 us would require 15 loops. 15 * 332 = 4980 ns or ~ 5us

    /* Calculation of a loop count */
    loop_cnt = ((us * mhz) / FLASH_LP_DELAY_LOOP_CYCLES);

    if (loop_cnt > 0U)
    {
        __asm volatile ("delay_loop:\n"
#if defined(__ICCARM__) || defined(__ARMCC_VERSION) || (defined(__llvm__) && !defined(__CLANG_TIDY__))
                        "   subs %[loops_remaining], #1         \n"                 ///< 1 cycle
#elif defined(__GNUC__)
                        "   sub %[loops_remaining], %[loops_remaining], #1      \n" ///< 1 cycle
#endif
                        "cmp %[loops_remaining], #0\n"                              // 1 cycle

/* CM0 and CM23 have different instruction sets */
#if defined(__CORE_CM0PLUS_H_GENERIC) || defined(__CORE_CM23_H_GENERIC)
                        "   bne delay_loop   \n"                                    ///< 2 cycles
#else
                        "   bne.n delay_loop \n"                                    ///< 2 cycles
#endif
                        :                                                           // No outputs
                        :[loops_remaining] "r" (loop_cnt)
                        :                                                           // No clobbers
                        );
    }
}

/*******************************************************************************************************************//**
 * Transition to Data Flash P/E mode.
 * @param[in]  p_ctrl  Pointer to the Flash control block
 **********************************************************************************************************************/
void r_flash_lp_df_enter_pe_mode (flash_lp_instance_ctrl_t * const p_ctrl)
{
    FLASH_LP_PRV_FENTRYR = FLASH_LP_FENTRYR_DATAFLASH_PE_MODE;

    r_flash_lp_delay_us(FLASH_LP_WAIT_TDSTOP, p_ctrl->system_clock_frequency);

    /* See "Procedure for changing from the read mode to the data flash P/E mode": Figure 37.16 in Section 37.13.3
     * of the RA2L1 manual r01uh0853ej0100-ra2l1 */
#if BSP_FEATURE_FLASH_LP_VERSION == 3

    /* If the device is not in high speed mode enable LVPE mode as per the flash documentation. */
    if (R_SYSTEM->OPCCR_b.OPCM == 0U)
    {
        r_flash_lp_write_fpmcr(FLASH_LP_DATAFLASH_PE_MODE);
    }
    else
    {
        r_flash_lp_write_fpmcr((uint8_t) FLASH_LP_DATAFLASH_PE_MODE | (uint8_t) FLASH_LP_LVPE_MODE);
    }

#elif BSP_FEATURE_FLASH_LP_VERSION == 4
    r_flash_lp_write_fpmcr(FLASH_LP_DATAFLASH_PE_MODE);

    r_flash_lp_delay_us(FLASH_LP_WAIT_TDIS, p_ctrl->system_clock_frequency);
#endif

#if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1) && (FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1)

    /* If BGO mode is enabled and interrupts are being used then enable interrupts. */
    if (p_ctrl->p_cfg->data_flash_bgo == true)
    {
        /* We are supporting Flash Rdy interrupts for Data Flash operations. */
        R_BSP_IrqEnable(p_ctrl->p_cfg->irq);
    }
#endif
}

/*******************************************************************************************************************//**
 * Sets the FPMCR register, used to place the Flash sequencer in Code Flash P/E mode.
 * @param[in]  value   - 8 bit value to be written to the FPMCR register.
 **********************************************************************************************************************/
static void r_flash_lp_write_fpmcr (uint8_t value)
{
    /* The procedure for writing to FPMCR is documented in Section 37.3.4 of the RA2L1 manual r01uh0853ej0100-ra2l1 */
    R_FACI_LP->FPR = FLASH_LP_FPR_UNLOCK;

    R_FACI_LP->FPMCR = value;
    R_FACI_LP->FPMCR = (uint8_t) ~value;
    R_FACI_LP->FPMCR = value;

    if (value == R_FACI_LP->FPMCR)
    {
        __NOP();
    }
}

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Configure an access window for the Code Flash memory using the provided start and end address. An access window
 * defines a contiguous area in Code Flash for which programming/erase is enabled. This area is on block boundaries. The
 * block containing start_addr is the first block. The block containing end_addr is the last block. The access window
 * then becomes first block - last block inclusive. Anything outside this range of Code Flash is then write protected.
 * This command DOES modify the configuration via The Configuration Set command to update the FAWS and FAWE.
 *
 * @param[in]  p_ctrl                Pointer to the Flash control block
 * @param[in]  start_addr            Determines the Starting block for the Code Flash access window.
 * @param[in]  end_addr              Determines the Ending block for the Code Flash access window.
 *
 * @retval     FSP_SUCCESS           Access window successfully configured.
 * @retval     FSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_access_window_set (flash_lp_instance_ctrl_t * const p_ctrl,
                                               uint32_t const                   start_addr,
                                               uint32_t const                   end_addr)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Enter Code Flash P/E mode */
    r_flash_lp_cf_enter_pe_mode(p_ctrl, false);

    /* Select The Extra Area */
    R_FACI_LP->FASR = 1U;

    /* Set the access window. */
    r_flash_lp_extra_operation(start_addr, end_addr, FLASH_COMMAND_ACCESSWINDOW);

    /* Wait for the operation to complete or error. */
    err = r_flash_lp_extra_check(p_ctrl);

    /* Select User Area */
    R_FACI_LP->FASR = 0U;

    /* Return to read mode. */
    fsp_err_t temp_err = r_flash_lp_pe_mode_exit(p_ctrl);

    /* If the previous commands were successful return the result of P/E exit. */
    if (FSP_SUCCESS == err)
    {
        err = temp_err;
    }

    /* Return status. */
    return err;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Set the id code
 * See Figure 37.28 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param      p_ctrl                Pointer to the instance control block
 * @param      p_id_code             Pointer to the code to be written
 * @param[in]  mode                  The id code mode
 *
 * @retval     FSP_SUCCESS           The id code have been written.
 * @retval     FSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for completion of extra command.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_set_id_code (flash_lp_instance_ctrl_t * const p_ctrl,
                                         uint8_t const * const            p_id_code,
                                         flash_id_code_mode_t             mode)
{
    fsp_err_t err           = FSP_SUCCESS;
    uint32_t  fexcr_command = FLASH_LP_FEXCR_OCDID1;

    uint16_t mode_mask = (uint16_t) mode;

    /* Update Flash state and enter Code Flash P/E mode */
    r_flash_lp_cf_enter_pe_mode(p_ctrl, false);

    /* For each ID byte register */
    for (uint32_t i = 0U; i < 16U; i += 4U)
    {
        /* Select Extra Area */
        R_FACI_LP->FASR = 1U;

        /* Write the ID Bytes. If mode is unlocked write all 0xFF. Write the mode mask to the MSB. */
        if (FLASH_ID_CODE_MODE_UNLOCKED == mode)
        {
            R_FACI_LP->FWBL0 = UINT16_MAX;
            R_FACI_LP->FWBH0 = UINT16_MAX;
        }
        else
        {
            /* The id code array may be unaligned. Do not attempt to optimize this code to prevent unaligned access. */
            R_FACI_LP->FWBL0 = (uint16_t) (p_id_code[i] | (p_id_code[i + 1] << 8));
            if (12U == i)
            {
                R_FACI_LP->FWBH0 = (uint16_t) (p_id_code[i + 2] | (p_id_code[i + 3] << 8)) | mode_mask;
            }
            else
            {
                R_FACI_LP->FWBH0 = (uint16_t) (p_id_code[i + 2] | (p_id_code[i + 3] << 8));
            }
        }

        /* Execute OCDID command */
        R_FACI_LP->FEXCR = fexcr_command;

        /* Increment the command to write to the next OCDID bytes */
        fexcr_command++;

        /* Wait until the operation is complete or an error. */
        err = r_flash_lp_extra_check(p_ctrl);

        /* Select User Area */
        R_FACI_LP->FASR = 0U;

        /* If failure return error */
        if (FSP_SUCCESS != err)
        {
            break;
        }
    }

    /* Return to read mode. */
    fsp_err_t temp_err = r_flash_lp_pe_mode_exit(p_ctrl);

    /* If the previous commands were successful return the result of P/E exit. */
    if (FSP_SUCCESS == err)
    {
        err = temp_err;
    }

    return err;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Modifies the start-up program swap flag (BTFLG) based on the supplied parameters. These changes will take effect on
 * the next reset. This command DOES modify the configuration via The Configuration Set command to update the BTFLG.
 *
 * @param[in]  p_ctrl                Pointer to the Flash control block
 * @param[in]  swap_type             Specifies the startup area swap being requested.
 * @param[in]  temporary             Swap blocks temporarily.
 *
 * @retval     FSP_SUCCESS           Access window successfully removed.
 * @retval     FSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_set_startup_area_boot (flash_lp_instance_ctrl_t * const p_ctrl,
                                                   flash_startup_area_swap_t        swap_type,
                                                   bool                             temporary)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Update Flash state and enter Code Flash P/E mode */
    r_flash_lp_cf_enter_pe_mode(p_ctrl, false);

    if (temporary)
    {
        /* Set the Flash initial setting startup area select bit as requested. */
        R_FACI_LP->FISR_b.SAS = swap_type;
    }
    else
    {
        /* Sets the BTFLG flag where 1 selects block 0 and 0 selects block 1. */
 #if BSP_FEATURE_FLASH_LP_VERSION == 3
        uint32_t startup_area_mask = ((uint32_t) (~swap_type & 0x1) << 8);  // move selection to bit 8
 #elif BSP_FEATURE_FLASH_LP_VERSION == 4
        uint32_t startup_area_mask = ((uint32_t) (~swap_type & 0x1) << 15); // move selection to bit 15
 #endif

        /* Select Extra Area */
        R_FACI_LP->FASR = 1U;

        /* Call extra operation to set the startup area. */
        r_flash_lp_extra_operation(startup_area_mask, 0, FLASH_COMMAND_STARTUPAREA);

        /* Wait until the operation is complete or an error occurs. */
        err = r_flash_lp_extra_check(p_ctrl);

        /* Select User Area */
        R_FACI_LP->FASR = 0U;
    }

    /* Return to read mode. */
    fsp_err_t temp_err = r_flash_lp_pe_mode_exit(p_ctrl);

    /* If the previous commands were successful return the result of P/E exit. */
    if (FSP_SUCCESS == err)
    {
        err = temp_err;
    }

    return err;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Command processing for the extra area.
 * See Figure 37.28 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  start_addr_startup_value  Determines the Starting block for the Code Flash access window.
 * @param[in]  end_addr                  Determines the Ending block for the Code Flash access window.
 * @param[in]  command                   Select from R_FLASH_ACCESSWINDOW or R_FLASH_STARTUPAREA.
 **********************************************************************************************************************/
static void r_flash_lp_extra_operation (const uint32_t    start_addr_startup_value,
                                        const uint32_t    end_addr,
                                        r_flash_command_t command)
{
    /* Per the spec: */
    /* Setting data to the FWBL0 register, this command is allowed to select the start-up area from the */
    /* default area (blocks 0-3) to the alternative area (blocks 4-7) and set the security. */
    /* Bit 8 of the FWBL0 register is 0: the alternative area (blocks 4-7) are selected as the start-up area. */
    /* Bit 8 of the FWBL0 register is 1: the default area (blocks 0-3) are selected as the start-up area. */
    /* Bit 14 of the FWBL0 register MUST be 1! Setting this bit to zero will clear the FSPR register and lock the */
    /* FLASH!!! It is not be possible to unlock it. */
 #if BSP_FEATURE_FLASH_LP_VERSION == 3
    if (FLASH_COMMAND_ACCESSWINDOW == command)
    {
        /* Set the Access Window start and end addresses. */
        /* FWBL0 reg sets the Start Block address. FWBH0 reg sets the end address. */
        /* Convert the addresses to their respective block numbers */
        R_FACI_LP->FWBL0 = (uint16_t) ((start_addr_startup_value >> BSP_FEATURE_FLASH_LP_AWS_FAW_SHIFT));
        R_FACI_LP->FWBH0 = (uint16_t) ((end_addr >> BSP_FEATURE_FLASH_LP_AWS_FAW_SHIFT));

        /* Execute Access Window command */
        R_FACI_LP->FEXCR = FLASH_LP_FEXCR_AW;
    }
    else
    {
        /* Startup Area Flag value setting */
        R_FACI_LP->FWBH0 = UINT16_MAX;

        /* FSPR must be set. Unused bits write value should be 1. */
        R_FACI_LP->FWBL0 = (start_addr_startup_value | FLASH_LP_FSCMR_FSPR_AND_UNUSED_BITS);

        /* Execute Startup Area Flag command */
        R_FACI_LP->FEXCR = FLASH_LP_FEXCR_STARTUP;
    }

 #elif BSP_FEATURE_FLASH_LP_VERSION == 4
    if (FLASH_COMMAND_ACCESSWINDOW == command)
    {
        uint32_t fawsmr = R_FACI_LP->FAWSMR & ~BSP_FEATURE_FLASH_LP_AWS_FAW_MASK;
        uint32_t fawemr = R_FACI_LP->FAWEMR & ~BSP_FEATURE_FLASH_LP_AWS_FAW_MASK;

        /* Set the Access Window start and end addresses. */
        /* FWBL0 reg sets the Start Block address. FWBH0 reg sets the end address. */
        /* Convert the addresses to their respective block numbers */
        R_FACI_LP->FWBL0 = ((start_addr_startup_value >> BSP_FEATURE_FLASH_LP_AWS_FAW_SHIFT) | fawsmr);
        R_FACI_LP->FWBH0 = ((end_addr >> BSP_FEATURE_FLASH_LP_AWS_FAW_SHIFT) | fawemr);

        /* Execute Access Window command */
        R_FACI_LP->FEXCR = FLASH_LP_FEXCR_MF4_AW_STARTUP;
    }
    else
    {
        uint32_t fawsmr = R_FACI_LP->FAWSMR;
        uint32_t fawemr = R_FACI_LP->FAWEMR & ~FLASH_LP_MF4_FAWEMR_STARTUP_AREA_MASK;

        /* Set the Access Window start and end addresses. */
        /* FWBL0 reg sets the Start Block address. FWBH0 reg sets the end address. */
        /* Convert the addresses to their respective block numbers */

        /* Set the access window start address to what was in FAWSMR. */
        R_FACI_LP->FWBL0 = fawsmr;

        /* Set the access window end address to what was in FAWEMR. Set BTFLG according to user input. */
        R_FACI_LP->FWBH0 = (start_addr_startup_value | fawemr);

        /* Execute Startup Area Flag command */
        R_FACI_LP->FEXCR = FLASH_LP_FEXCR_MF4_AW_STARTUP;
    }
 #endif
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Wait for the current command to finish processing and clear the FCR register. If MF4 is used clear the processing
 * bit before clearing the rest of FCR.
 * See Figure 37.28 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  timeout         The timeout
 * @retval     FSP_SUCCESS     The command completed successfully.
 * @retval     FSP_ERR_TIMEOUT The command timed out.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_extra_command_finish (uint32_t timeout)
{
    /* Timeout counter. */
    volatile uint32_t wait_cnt = timeout;

    /* If the software command of the FEXCR register is not terminated return in use. */
    FLASH_LP_REGISTER_WAIT_TIMEOUT(1, R_FACI_LP->FSTATR1_b.EXRDY, wait_cnt, FSP_ERR_TIMEOUT);

 #if BSP_FEATURE_FLASH_LP_VERSION == 4

    /* Stop Processing */
    R_FACI_LP->FEXCR = R_FACI_LP->FEXCR & ((uint8_t) ~FLASH_LP_FEXCR_PROCESSING_MASK);
 #endif

    /* Clear the Flash Extra Area Control Register. */
    R_FACI_LP->FEXCR = FLASH_LP_FEXCR_CLEAR;

    wait_cnt = timeout;

    /* Wait until the command has completed or a timeout occurs. If timeout return error. */
    FLASH_LP_REGISTER_WAIT_TIMEOUT(0, R_FACI_LP->FSTATR1_b.EXRDY, wait_cnt, FSP_ERR_TIMEOUT);

    return FSP_SUCCESS;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Verifying the execution result for the extra area.
 * @param[in]  p_ctrl                Pointer to the Flash control block
 * @retval     FSP_SUCCESS           Access window successfully removed.
 * @retval     FSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for completion of extra command.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_extra_check (flash_lp_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = r_flash_lp_extra_command_finish(p_ctrl->timeout_write_extra_area);

    /* If a timeout occurs reset the flash and return error. */
    if (FSP_ERR_TIMEOUT == err)
    {
        r_flash_lp_reset(p_ctrl);

        return err;
    }

    /* If Extra Area Illegal Command Error Flag or Error during programming reset the flash and return error. */
    if (0 != (FLASH_LP_FSTATR2_WRITE_ERROR_BITS & R_FACI_LP->FSTATR2))
    {
        r_flash_lp_reset(p_ctrl);

        return FSP_ERR_WRITE_FAILED;
    }

    /* Return success. */
    return FSP_SUCCESS;
}

#endif

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Transition to Code Flash P/E mode.
 * @param[in]  p_ctrl            Pointer to the Flash control block
 * @param[in]  bank_programming  Put the flash into bank programming mode
 **********************************************************************************************************************/
void r_flash_lp_cf_enter_pe_mode (flash_lp_instance_ctrl_t * const p_ctrl, bool bank_programming)
{
    /* While the Flash API is in use we will disable the Flash Cache. */
 #if BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER
    R_FACI_LP->PFBER = 0;
 #endif
 #if BSP_FEATURE_BSP_FLASH_CACHE
    R_BSP_FlashCacheDisable();
 #endif

 #if (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
    if (bank_programming)
    {
        R_BSP_IrqEnable(p_ctrl->p_cfg->irq);
    }
    else
    {
        if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->irq)
        {
            R_BSP_IrqDisable(p_ctrl->p_cfg->irq); // We are not supporting Flash Rdy interrupts for Code Flash operations
        }
    }

 #else
    FSP_PARAMETER_NOT_USED(bank_programming);
  #if (FLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE == 1) && (FLASH_LP_CFG_DATA_FLASH_BGO_SUPPORT_ENABLE == 1)
    if (p_ctrl->p_cfg->data_flash_bgo)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->irq);
    }
  #endif
 #endif

    FLASH_LP_PRV_FENTRYR = FLASH_LP_FENTRYR_CODEFLASH_PE_MODE;

    /* See "Procedure for changing from read mode to code flash P/E mode": See Figure 37.15 in Section 37.13.3 of the
     * RA2L1 manual r01uh0853ej0100-ra2l1 */
 #if BSP_FEATURE_FLASH_LP_VERSION == 3
    r_flash_lp_write_fpmcr(FLASH_LP_DISCHARGE_1);

    /* Wait for 2us over (tDIS) */
    r_flash_lp_delay_us(FLASH_LP_WAIT_TDIS, p_ctrl->system_clock_frequency);

    uint32_t fpmcr_command1;
    uint32_t fpmcr_command2;
    uint32_t fpmcr_mode_setup_time;

    /* If the device is not in high speed mode enable LVPE mode as per the flash documentation. */
    if (R_SYSTEM->OPCCR_b.OPCM == 0U)
    {
        fpmcr_command1        = FLASH_LP_DISCHARGE_2;
        fpmcr_command2        = FLASH_LP_CODEFLASH_PE_MODE;
        fpmcr_mode_setup_time = FLASH_LP_WAIT_TMS_HIGH;
    }
    else
    {
        fpmcr_command1        = FLASH_LP_DISCHARGE_2 | FLASH_LP_LVPE_MODE;
        fpmcr_command2        = FLASH_LP_CODEFLASH_PE_MODE | FLASH_LP_LVPE_MODE;
        fpmcr_mode_setup_time = FLASH_LP_WAIT_TMS_MID;
    }

    r_flash_lp_write_fpmcr((uint8_t) fpmcr_command1);
    r_flash_lp_write_fpmcr((uint8_t) fpmcr_command2);

    /* Wait for 5us or 3us depending on current operating mode. (tMS) */
    r_flash_lp_delay_us(fpmcr_mode_setup_time, p_ctrl->system_clock_frequency);
 #elif BSP_FEATURE_FLASH_LP_VERSION == 4
  #if (FLASH_LP_CFG_CODE_FLASH_BANK_PROGRAMMING_ENABLE == 1)
    if (bank_programming)
    {
        R_FACI_LP->FBKPGCR = FLASH_LP_BANK_PROGRAMMING_ENTER;
    }
  #endif
    r_flash_lp_write_fpmcr(0x02);

    /* Wait for 2us over (tDIS) */
    r_flash_lp_delay_us(FLASH_LP_WAIT_TDIS, p_ctrl->system_clock_frequency);
 #endif
}

#endif

/*******************************************************************************************************************//**
 * Wait for the current command to finish processing and clear the FCR register. If MF4 is used clear the processing
 * bit before clearing the rest of FCR.
 * See Figure 37.19 in Section 37.13.3 of the RA2L1 manual r01uh0853ej0100-ra2l1
 *
 * @param[in]  timeout         The timeout
 * @retval     FSP_SUCCESS     The command completed successfully.
 * @retval     FSP_ERR_TIMEOUT The command timed out.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_command_finish (uint32_t timeout)
{
    /* Worst case timeout */
    volatile uint32_t wait = timeout;

    /* Check the Flash Ready Flag bit*/
    FLASH_LP_REGISTER_WAIT_TIMEOUT(1, R_FACI_LP->FSTATR1_b.FRDY, wait, FSP_ERR_TIMEOUT);

#if BSP_FEATURE_FLASH_LP_VERSION == 4

    /* Stop Processing */
    R_FACI_LP->FCR = R_FACI_LP->FCR & ((uint8_t) ~FLASH_LP_FCR_PROCESSING_MASK);
#endif

    /* Clear FCR register */
    R_FACI_LP->FCR = FLASH_LP_FCR_CLEAR;

    /* Worst case timeout */
    wait = timeout;

    /* Wait for the Flash Ready Flag bit to indicate ready or a timeout to occur. If timeout return error. */
    FLASH_LP_REGISTER_WAIT_TIMEOUT(0, R_FACI_LP->FSTATR1_b.FRDY, wait, FSP_ERR_TIMEOUT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Wait for the current command to finish processing and check for error.
 *
 * @param      p_ctrl                Pointer to the control block
 * @param[in]  timeout               The timeout
 * @param[in]  error_bits            The error bits related to the current command
 * @param[in]  return_code           The operation specific error code
 *
 * @retval     FSP_SUCCESS           Erase command successfully completed.
 * @retval     FSP_ERR_TIMEOUT       Timed out waiting for erase command completion.
 * @return     return_code           The operation specific error code.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_wait_for_ready (flash_lp_instance_ctrl_t * const p_ctrl,
                                            uint32_t                         timeout,
                                            uint32_t                         error_bits,
                                            fsp_err_t                        return_code)
{
    fsp_err_t err = r_flash_lp_command_finish(timeout);

    /* If a timeout occurs reset the flash and return error. */
    if (FSP_ERR_TIMEOUT == err)
    {
        r_flash_lp_reset(p_ctrl);

        return err;
    }

    /* If an error occurs reset and return error. */
    if (0U != (R_FACI_LP->FSTATR2 & error_bits))
    {
        r_flash_lp_reset(p_ctrl);

        return return_code;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the flash interface peripheral clock frequency
 * @param      p_ctrl           Pointer to the interface control block
 * @retval     FSP_SUCCESS      Flash interface clock frequency successfully configured.
 * @retval     FSP_ERR_TIMEOUT  Setting the flash interface clock frequency timed out.
 **********************************************************************************************************************/
fsp_err_t r_flash_lp_set_fisr (flash_lp_instance_ctrl_t * const p_ctrl)
{
    /* Enter data flash P/E mode to enable writing to FISR. */
    r_flash_lp_df_enter_pe_mode(p_ctrl);

#if BSP_FEATURE_FLASH_LP_VERSION == 4

    /* If the flash clock is larger than 32 increment FISR_b.PCKA by 1 for every 2MHZ. (See Section 37.3.7 "Flash
     * Internal Setting Register" of the RA2L1 manual r01uh0853ej0100-ra2l1 */
    if (p_ctrl->flash_clock_frequency >= FLASH_LP_FISR_INCREASE_PCKA_EVERY_2MHZ)
    {
        R_FACI_LP->FISR_b.PCKA =
            (0x1F + ((p_ctrl->flash_clock_frequency - FLASH_LP_FISR_INCREASE_PCKA_EVERY_2MHZ) >> 1)) &
            FLASH_LP_6BIT_MASK;
    }
    else
#endif
    {
        R_FACI_LP->FISR_b.PCKA = (p_ctrl->flash_clock_frequency - 1U) & FLASH_LP_5BIT_MASK;
    }

    return r_flash_lp_pe_mode_exit(p_ctrl);
}

#if (FLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Local memcpy function to prevent from using memcpy linked in code flash
 *
 * @param      dest            The destination
 * @param      src             The source
 * @param[in]  len             The length
 **********************************************************************************************************************/
void r_flash_lp_memcpy (uint8_t * const dest, uint8_t * const src, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
}

 #if (BSP_FEATURE_FLASH_LP_SUPPORTS_DUAL_BANK == 1)

/*******************************************************************************************************************//**
 * This function swaps which flash bank will be used to boot from after swapped and activated.
 *
 * @param[in]   p_ctrl                  Flash control block.
 *
 * @retval      FSP_SUCCESS             Banks were swapped.
 * @retval      FSP_ERR_IN_USE          Extra area is being used by other command.
 * @retval      FSP_ERR_WRITE_FAILED    Failed to write bank swap command into extra area.
 * @retval      FSP_ERR_TIMEOUT         Timed out waiting for completion of extra command or timed out waiting for
 *                                      confirmation of transition to read mode.
 **********************************************************************************************************************/
static fsp_err_t r_flash_lp_bank_swap (flash_lp_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t   cur_bank;

    /* Refer to the "Example of startup bank selection flow" flowchart in the relevant hardware manual */
    cur_bank = R_FACI_LP->FCTLFR_b.BANKSWP;

    r_flash_lp_cf_enter_pe_mode(p_ctrl, false);

    /* Select The Extra Area. Needed when using FEXCR register. */
    R_FACI_LP->FASR = 1U;

    /* Change the BANKSWP[2:0] of extra area  */
    R_FACI_LP->FWBL0_b.WDATA = ~cur_bank & FLASH_LP_3BIT_MASK;
    R_FACI_LP->FWBH0_b.WDATA = 0x0000U;
    R_FACI_LP->FEXCR         = FLASH_LP_FEXCR_MF4_CONTROL;

    err = r_flash_lp_extra_check(p_ctrl);

    /* Select User Area. Need to change back to User Area before return error. */
    R_FACI_LP->FASR = 0U;

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_flash_lp_pe_mode_exit(p_ctrl);

  #if FLASH_LP_CFG_DUAL_BANK_INSTANT_SWAP
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* See "Example of startup bank selection flow (2/4) (change the startup bank without reset)": Figure 35.14 in
     * Section 35.6.4 of the RA2A2 manual r01uh1005ej0110-ra2a2 */

    /* Enable writing to FCTLFR. */
    R_FACI_LP->FBKSWCR = FLASH_LP_BANK_SWAP_UPDATE_ENABLE;

    /* Read BANKSWP[2:0] from the extra area */
    (void) *(uint32_t *) FLASH_LP_EXTRA_AREA_FCTLF_ADDRESS;

    /* Update FCTLFR with the new bank value. */
    R_FACI_LP->FCTLFR = ~cur_bank & FLASH_LP_3BIT_MASK;

    /* Disable writing to FCTLFR. */
    R_FACI_LP->FBKSWCR = FLASH_LP_BANK_SWAP_UPDATE_DISABLE;
  #endif

    return err;
}

 #endif
#endif
