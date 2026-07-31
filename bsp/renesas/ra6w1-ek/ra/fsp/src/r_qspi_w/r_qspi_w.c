/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_qspi_w.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define QSPI_W_PRV_OPEN                        (0x51535049U) // ASCII characters "QSPI"
#define QSPI_W_PRV_TIMEOUT_US                  (500000U)

#if defined(BSP_MCU_GROUP_RA6W1)
 #define QSPI_W_DEVICE_END_ADDRESS             (0x28000000U)
 #define QSPI_W_MEMORY_QSPID_SIZE              (QSPI_W_DEVICE_END_ADDRESS - QSPI_W_DEVICE_START_ADDRESS)
 #define QSPI_W_DCACHE_CACHEABLE_RESOLUTION    (0x400U)
 #define QSPI_W_DCACHE_CACHEABLE_LEN_MAX       (QSPI_W_MEMORY_QSPID_SIZE / QSPI_W_DCACHE_CACHEABLE_RESOLUTION)

/* Read pipe delay based on voltage level of power rail. */
 #define QSPI_W_READ_PIPE_DELAY                (QSPI_W_READ_PIPE_DELAY_3)
#else

/* Read pipe delay based on voltage level of power rail. */
 #define QSPI_W_READ_PIPE_DELAY                (QSPI_W_READ_PIPE_DELAY_2) /* 0V9 */
#endif

/* Sector size. */
#define QSPI_W_FLASH_SECTOR_SIZE               (0x1000U)
#define QSPI_W_MAN_DIRCHG_MD_DEFAULT           (1U) // The bus direction goes to input only after a dummy access (Manual Mode).

/* Number of dummy bytes. */
#define QSPI_W_DUMMY_BYTES_FORCED              (3U)

#define QSPI_W_FLASH_PAGE_SIZE                 (0XFFU)

/* QSPI_W base register access macro. */
#define QSPI_REG(channel)    ((QSPIC_Type *) ((uint32_t) QSPIC - ((uint32_t) QSPIC) * (channel)))

#if defined(QSPIC_QSPIC_STATUSCMDA_REG_QSPIC_BUSY_VAL_Msk)
 #define QSPI_W_STATUSCMDA_REG    QSPIC_STATUSCMDA_REG
 #define QSPI_W_STATUSCMDA_REG_FIELD_SET(field, var, val)                            \
    var = (((unsigned) var & ~((QSPIC_QSPIC_STATUSCMDA_REG_ ## field ## _Msk))) |    \
           ((((unsigned) (val)) << (QSPIC_QSPIC_STATUSCMDA_REG_ ## field ## _Pos)) & \
            (QSPIC_QSPIC_STATUSCMDA_REG_ ## field ## _Msk)))
#elif defined(QSPIC_QSPIC_STATUSCMD_REG_QSPIC_BUSY_VAL_Msk)
 #define QSPI_W_STATUSCMDA_REG    QSPIC_STATUSCMD_REG
 #define QSPI_W_STATUSCMDA_REG_FIELD_SET(field, var, val)                           \
    var = (((unsigned) var & ~((QSPIC_QSPIC_STATUSCMD_REG_ ## field ## _Msk))) |    \
           ((((unsigned) (val)) << (QSPIC_QSPIC_STATUSCMD_REG_ ## field ## _Pos)) & \
            (QSPIC_QSPIC_STATUSCMD_REG_ ## field ## _Msk)))
#endif

#if defined(QSPIC_QSPIC_AWRITECMDA_REG_QSPIC_WR_INST_Msk)
 #define QSPI_W_AWRITECMDA_REG    QSPIC_AWRITECMDA_REG
 #define QSPI_W_AWRITECMDA_REG_FIELD_SET(field, var, val)                            \
    var = (((unsigned) var & ~((QSPIC_QSPIC_AWRITECMDA_REG_ ## field ## _Msk))) |    \
           ((((unsigned) (val)) << (QSPIC_QSPIC_AWRITECMDA_REG_ ## field ## _Pos)) & \
            (QSPIC_QSPIC_AWRITECMDA_REG_ ## field ## _Msk)))
#elif defined(QSPIC_QSPIC_AWRITECMD_REG_QSPIC_WR_INST_Msk)
 #define QSPI_W_AWRITECMDA_REG    QSPIC_AWRITECMD_REG
 #define QSPI_W_AWRITECMDA_REG_FIELD_SET(field, var, val)                           \
    var = (((unsigned) var & ~((QSPIC_QSPIC_AWRITECMD_REG_ ## field ## _Msk))) |    \
           ((((unsigned) (val)) << (QSPIC_QSPIC_AWRITECMD_REG_ ## field ## _Pos)) & \
            (QSPIC_QSPIC_AWRITECMD_REG_ ## field ## _Msk)))
#endif

#if defined(CRG_TOP_CLK_AMBA_REG_QSPI2_ENABLE_Msk)
 #define QSPI_W_CLK_AMBA_REG_FIELD_SET(field, var, val)                              \
    var = (((unsigned) var & ~((CRG_TOP_CLK_AMBA_REG_QSPI2_ ## field ## _Msk))) |    \
           ((((unsigned) (val)) << (CRG_TOP_CLK_AMBA_REG_QSPI2_ ## field ## _Pos)) & \
            (CRG_TOP_CLK_AMBA_REG_QSPI2_ ## field ## _Msk)))
#elif defined(CRG_TOP_CLK_AMBA_REG_QSPI_ENABLE_Msk)
 #define QSPI_W_CLK_AMBA_REG_FIELD_SET(field, var, val)                             \
    var = (((unsigned) var & ~((CRG_TOP_CLK_AMBA_REG_QSPI_ ## field ## _Msk))) |    \
           ((((unsigned) (val)) << (CRG_TOP_CLK_AMBA_REG_QSPI_ ## field ## _Pos)) & \
            (CRG_TOP_CLK_AMBA_REG_QSPI_ ## field ## _Msk)))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Index of bus mode. */
typedef enum e_qspi_w_idx_bus_mode
{
    QSPI_W_IDX_INSTR_BUS_MODE,         // Index of instruction bus mode.
    QSPI_W_IDX_NON_INSTR_BUS_MODE,     // Index of non-instruction bus mode (address/extra/dummy/data bus modes).
} qspi_w_idx_bus_mode_t;

/*
 * Union used in order to allow different size access when reading/writing to
 * QSPIC_READDATA_REG, QSPIC_WRITEDATA_REG, QSPIC_DUMMYDATA_REG.
 */
typedef union u_qspi_w_data
{
    __IO uint32_t data32;
    __IO uint16_t data16;
    __IO uint8_t  data8;
} qspi_w_data_t;

/***********************************************************************************************************************
 * Private global variables and functions.
 **********************************************************************************************************************/

__STATIC_FORCEINLINE void r_qspi_w_set_io(uint8_t channel, qspi_w_bus_mode_t bus_mode);
__STATIC_FORCEINLINE void r_qspi_w_write32(uint8_t channel, uint32_t data);
__STATIC_FORCEINLINE void r_qspi_w_write8(uint8_t channel, uint8_t data);
__STATIC_FORCEINLINE void r_qspi_w_read_status_instr_init(uint8_t                                channel,
                                                          const qspi_w_read_status_instr_cfg_t * p_read_status_instr_cfg);
__STATIC_FORCEINLINE void r_qspi_w_write_enable_instr_init(uint8_t                                 channel,
                                                           const qspi_w_write_enable_instr_cfg_t * p_wrt_enble_instr_cfg);
__STATIC_FORCEINLINE void r_qspi_w_erase_instr_init(uint8_t                          channel,
                                                    const qspi_w_erase_instr_cfg_t * p_erase_instr_cfg);
__STATIC_FORCEINLINE void r_qspi_w_suspend_resume_instr_init(uint8_t                                   channel,
                                                             const qspi_w_suspend_resume_instr_cfg_t * p_sus_res_instr_cfg);
__STATIC_FORCEINLINE void r_qspi_w_write_instr_init(uint8_t                          channel,
                                                    const qspi_w_write_instr_cfg_t * p_wrt_instr_cfg);
__STATIC_FORCEINLINE void r_qspi_w_break_instr_init(uint8_t                          channel,
                                                    const qspi_w_break_instr_cfg_t * p_break_instr_cfg);
__STATIC_FORCEINLINE void         r_qspi_w_memblen_init(uint8_t channel, const qspi_w_memblen_cfg_t * p_memblen_cfg);
__STATIC_FORCEINLINE qspi_w_ers_t r_qspi_w_get_erase_status(uint8_t channel);
__STATIC_FORCEINLINE uint8_t      r_qspi_w_read8(uint8_t channel);
__STATIC_FORCEINLINE void         r_qspi_w_fast_write_to_fifo32(uint32_t start, uint32_t end, uint32_t dest);
__STATIC_FORCEINLINE void         r_qspi_w_enter_manual_access_mode(qspi_w_instance_ctrl_t * p_instance_ctrl);

PLACE_IN_RAM_SECTION static void r_qspi_w_direct_write_sub(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                           uint8_t const * const    p_src,
                                                           uint32_t const           bytes,
                                                           bool const               read_after_write);
PLACE_IN_RAM_SECTION static void r_qspi_w_direct_read_sub(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                          uint8_t * const          p_dest,
                                                          uint32_t const           bytes);
PLACE_IN_RAM_SECTION static fsp_err_t r_qspi_w_xip(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                   uint8_t                  code,
                                                   bool                     enter_mode);
PLACE_IN_RAM_SECTION static void     r_qspi_w_manual_access_bus_mode_set(uint8_t channel, qspi_w_bus_mode_t bus_mode);
PLACE_IN_RAM_SECTION static void     r_qspi_w_enter_auto_access_mode(qspi_w_extended_cfg_t * p_inst_extend);
PLACE_IN_RAM_SECTION static uint32_t r_qspi_w_flash_write_page(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                               uint32_t                 addr,
                                                               const uint8_t          * p_buf,
                                                               uint32_t                 size);
PLACE_IN_RAM_SECTION static uint32_t  r_qspi_w_get_chip_address(uint8_t * const p_addr);
PLACE_IN_RAM_SECTION static void      r_qspi_w_erase_block(uint8_t channel, uint32_t addr);
PLACE_IN_RAM_SECTION static fsp_err_t r_qspi_w_erase_flash_sector(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                                  uint32_t                 addr);
PLACE_IN_RAM_SECTION static uint16_t r_qspi_w_get_erase_opcode(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                               uint32_t                 byte_count);
PLACE_IN_RAM_SECTION static void r_qspi_w_erase_chip(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                     uint8_t                  erase_command);

PLACE_IN_RAM_SECTION static void r_qspi_w_instructions_init(qspi_w_instance_ctrl_t * p_instance_ctrl);
PLACE_IN_RAM_SECTION static void r_qspi_w_controller_init(qspi_w_instance_ctrl_t * p_instance_ctrl);
PLACE_IN_RAM_SECTION static void r_qspi_w_get_bus_mode(spi_flash_protocol_t spi_protocol,
                                                       qspi_w_bus_mode_t  * p_bus_mode);

PLACE_IN_RAM_SECTION static bool r_qspi_w_flash_is_writable(qspi_w_instance_ctrl_t * p_instance_ctrl);
PLACE_IN_RAM_SECTION static void r_qspi_w_flash_cmd(uint8_t channel, const uint8_t opcode);
PLACE_IN_RAM_SECTION static void r_qspi_w_flash_write_enable(qspi_w_instance_ctrl_t * p_instance_ctrl);
PLACE_IN_RAM_SECTION static bool r_qspi_w_flash_is_busy(qspi_w_instance_ctrl_t * p_instance_ctrl);

PLACE_IN_RAM_SECTION static void r_qspi_w_set_extra_byte(uint8_t                         channel,
                                                         uint8_t                         extra_byte,
                                                         qspi_w_read_instr_cfg_t const * p_qspi_cfg);
PLACE_IN_RAM_SECTION static void r_qspi_w_read_instr_init(uint8_t                         channel,
                                                          const qspi_w_read_instr_cfg_t * p_read_instr_cfg);
PLACE_IN_RAM_SECTION static void r_qspi_w_transact(qspi_w_extended_cfg_t * p_inst_extend,
                                                   const uint8_t         * p_wbuf,
                                                   uint32_t                wlen,
                                                   uint8_t               * p_rbuf,
                                                   uint32_t                rlen);
PLACE_IN_RAM_SECTION static uint8_t r_qspi_w_read_status_register(qspi_w_instance_ctrl_t * p_instance_ctrl);

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
PLACE_IN_RAM_SECTION static fsp_err_t r_qspi_w_param_checking_dcom(qspi_w_instance_ctrl_t * p_instance_ctrl);
PLACE_IN_RAM_SECTION static fsp_err_t r_qspi_w_program_param_check(qspi_w_instance_ctrl_t * p_instance_ctrl,
                                                                   uint8_t const * const    p_src,
                                                                   uint8_t * const          p_dest,
                                                                   uint32_t                 byte_count);

#endif
#if defined(BSP_MCU_GROUP_RA6W1)
static void      r_qspi_w_dcache_enable(void);
static void      r_qspi_w_dcache_set_cacheable_base(void);
static fsp_err_t r_qspi_w_dcache_disable(void);
static fsp_err_t r_qspi_w_dcache_init(void);
static fsp_err_t r_qspi_w_dcache_set_cacheable_len(uint32_t len);

#endif

static qspi_w_bus_mode_t g_manual_access_bus_mode = QSPI_W_BUS_MODE_SINGLE;

/*******************************************************************************************************************//**
 * @addtogroup QSPI_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const spi_flash_api_t g_spi_flash_on_qspi_w =
{
    .open           = R_QSPI_W_Open,
    .directWrite    = R_QSPI_W_DirectWrite,
    .directRead     = R_QSPI_W_DirectRead,
    .directTransfer = R_QSPI_W_DirectTransfer,
    .spiProtocolSet = R_QSPI_W_SpiProtocolSet,
    .write          = R_QSPI_W_Write,
    .erase          = R_QSPI_W_Erase,
    .statusGet      = R_QSPI_W_StatusGet,
    .xipEnter       = R_QSPI_W_XipEnter,
    .xipExit        = R_QSPI_W_XipExit,
    .bankSet        = R_QSPI_W_BankSet,
    .autoCalibrate  = R_QSPI_W_AutoCalibrate,
    .close          = R_QSPI_W_Close,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Open the QSPI_W driver module. After the driver is open, the QSPI_W can be accessed like internal flash memory
 * starting at address 0x16000000/0x36000000.
 *
 * QSPI_W is configured to operate in AUTO MODE after the driver is open.
 *
 * QSPI_W memory is expected to be in single SPI mode before calling open.
 *
 * Implements @ref spi_flash_api_t::open.
 *
 * @param[in] p_ctrl                        Pointer to the instance control structure.
 * @param[in] p_cfg                         Configuration structure which contains all the user provided configurations.
 *
 * @retval FSP_SUCCESS                      Configuration was successful.
 * @retval FSP_ERR_ASSERTION                The pointer parameters are NULL.
 * @retval FSP_ERR_ALREADY_OPEN             Driver has already been opened with the same p_instance_ctrl.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT   The channel number is invalid.
 * @retval FSP_ERR_INVALID_HW_CONDITION     Invalid power rail condition.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_Open (spi_flash_ctrl_t * p_ctrl, spi_flash_cfg_t const * const p_cfg)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    qspi_w_extended_cfg_t * p_cfg_extend;

    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    p_cfg_extend = (qspi_w_extended_cfg_t *) p_cfg->p_extend;
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg_extend);
    FSP_ERROR_RETURN(BSP_FEATURE_QSPI_MAX_CHANNEL > p_cfg_extend->channel, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #if defined(BSP_MCU_GROUP_RA6B1) || defined(BSP_MCU_GROUP_RA6U1)
    FSP_ERROR_RETURN(1 == PMU_ANA->POWER_CTRL_REG_b.V18EXT_ENABLE, FSP_ERR_INVALID_HW_CONDITION);
 #endif
#endif

    p_instance_ctrl->p_cfg = p_cfg;

#if defined(BSP_MCU_GROUP_RA6W1)
 #if !QSPI_W_CFG_PARAM_CHECKING_ENABLE
    qspi_w_extended_cfg_t * p_cfg_extend = (qspi_w_extended_cfg_t *) p_cfg->p_extend;
 #endif

    /* Data cache setting. */
    if (QSPI_W_DCACHE_ENABLE == p_cfg_extend->qspi_dcache)
    {
        r_qspi_w_dcache_enable();
        FSP_ERROR_RETURN(FSP_SUCCESS == r_qspi_w_dcache_init(), FSP_ERR_TIMEOUT);
        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         r_qspi_w_dcache_set_cacheable_len(QSPI_W_DCACHE_CACHEABLE_LEN_MAX),
                         FSP_ERR_TIMEOUT);
        r_qspi_w_dcache_set_cacheable_base();
    }
#endif
    r_qspi_w_controller_init(p_instance_ctrl);

    r_qspi_w_instructions_init(p_instance_ctrl);

    /* The memory size is read from the device if needed. */
    p_instance_ctrl->total_size_bytes = 0U;

    p_instance_ctrl->open = QSPI_W_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes raw data directly to the QSPI_W.
 *
 * @note Use R_QSPI_W_SpiProtocolSet before a direct write to set the bus mode in the appropriate manual mode.
 *
 * Implements @ref spi_flash_api_t::directWrite.
 *
 * @param[in] p_ctrl                   Pointer to the instance control structure.
 * @param[in] p_src                    Pointer to the data to write.
 * @param[in] bytes                    Number of bytes to write.
 * @param[in] read_after_write         Whether or not to close the SPI bus cycle.
 *
 * @retval FSP_SUCCESS                 Directly write raw data successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XiP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_DirectWrite (spi_flash_ctrl_t    * p_ctrl,
                                uint8_t const * const p_src,
                                uint32_t const        bytes,
                                bool const            read_after_write)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_qspi_w_param_checking_dcom(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(bytes > 0);
#endif

    /* Write data to QSPI_W. */
    r_qspi_w_direct_write_sub(p_instance_ctrl, p_src, bytes, read_after_write);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads raw data directly from the QSPI_W. This API can only be called after R_QSPI_W_DirectWrite with read_after_write
 * set to true.
 *
 * Implements @ref spi_flash_api_t::directRead.
 *
 * @param[in]  p_ctrl                   Pointer to the instance control structure.
 * @param[out] p_dest                   Pointer to the destination buffer.
 * @param[in]  bytes                    Number of bytes to read.
 *
 * @retval FSP_SUCCESS                  Directly read raw data successfully.
 * @retval FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN             Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE         This function must be called after R_QSPI_W_DirectWrite with read_after_write set
 *                                      to true.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_DirectRead (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(bytes > 0);
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* This API can only be called after R_QSPI_W_DirectWrite with the read_after_write parameter set to true. The QSPI_W
     * peripheral must already be in direct communications mode. */
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;
    FSP_ERROR_RETURN(0U == QSPI_REG(channel)->QSPIC_CTRLMODE_REG_b.QSPIC_AUTO_MD, FSP_ERR_INVALID_MODE);
#endif

    /* Read data from QSPI_W. */
    r_qspi_w_direct_read_sub(p_instance_ctrl, p_dest, bytes);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read/Write raw data directly with the OctaFlash/OctaRAM device. Unsupported by QSPI_W.
 *
 * Implements @ref spi_flash_api_t::directTransfer.
 *
 * @param[in] p_ctrl                   Pointer to the instance control structure.
 * @param[in] p_transfer               Pointer to @ref spi_flash_direct_transfer_t.
 * @param[in] direction                Direct read or write direction.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by QSPI_W.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_DirectTransfer (spi_flash_ctrl_t                  * p_ctrl,
                                   spi_flash_direct_transfer_t * const p_transfer,
                                   spi_flash_direct_transfer_dir_t     direction)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_transfer);
    FSP_PARAMETER_NOT_USED(direction);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Enters XiP (execute in place) mode.
 *
 * @note XiP mode refers to random access read mode, also known as Fast Read Quad I/O (EBh),
 *       4READ: 4 x I/O READ (EBh), etc.
 *
 * Implements @ref spi_flash_api_t::xipEnter.
 *
 * @param[in] p_ctrl                   Pointer to the instance control structure.
 *
 * @retval    FSP_SUCCESS              The flash enters XiP mode successfully.
 * @retval    FSP_ERR_ASSERTION        A required pointer is NULL.
 * @retval    FSP_ERR_NOT_OPEN         Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_XipEnter (spi_flash_ctrl_t * p_ctrl)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    fsp_err_t err =
        r_qspi_w_xip(p_instance_ctrl, p_instance_ctrl->p_cfg->xip_enter_command, true);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Exits XiP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipExit.
 *
 * @param[in] p_ctrl                   Pointer to the instance control structure.
 *
 * @retval FSP_SUCCESS                 The flash exits XiP mode successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_XipExit (spi_flash_ctrl_t * p_ctrl)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    fsp_err_t err =
        r_qspi_w_xip(p_instance_ctrl, p_instance_ctrl->p_cfg->xip_exit_command, false);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Program a page of data to the flash.
 *
 * Implements @ref spi_flash_api_t::write.
 *
 * @param[in]  p_ctrl                   Pointer to the instance control structure.
 * @param[in]  p_src                    Pointer to the source data.
 * @param[out] p_dest                   Pointer to the destination.
 * @param[in]  byte_count               Number of bytes to write.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl, p_dest or p_src is NULL, or byte_count crosses a page boundary.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XiP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_Write (spi_flash_ctrl_t    * p_ctrl,
                          uint8_t const * const p_src,
                          uint8_t * const       p_dest,
                          uint32_t              byte_count)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_qspi_w_program_param_check(p_instance_ctrl, p_src, p_dest, byte_count);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    qspi_w_bus_mode_t busy_bus_mode =
        p_inst_extend->p_qspi_flash_cfg->p_read_status_instr_cfg->opcode_bus_mode;

    /* Disable the interrupts as long as the QSPIC remains in manual access mode. */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Wait until the flash memory is ready. */
    r_qspi_w_enter_manual_access_mode(p_instance_ctrl);
    r_qspi_w_manual_access_bus_mode_set(channel, busy_bus_mode);
    while (r_qspi_w_flash_is_busy(p_instance_ctrl))
    {
        /* No messages to process */
        ;
    }

    r_qspi_w_flash_write_page(p_instance_ctrl, r_qspi_w_get_chip_address(p_dest), p_src, byte_count);

    r_qspi_w_manual_access_bus_mode_set(channel, busy_bus_mode);

    r_qspi_w_enter_auto_access_mode(p_inst_extend);

    /* Re-enable the interrupts since the QSPIC switched back to auto access mode. */
    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erase a block or sector of flash. The byte_count must exactly match one of the erase sizes defined in spi_flash_cfg_t.
 * For chip erase, byte_count must be SPI_FLASH_ERASE_SIZE_CHIP_ERASE.
 *
 * Implements @ref spi_flash_api_t::erase.
 *
 * @param[in] p_ctrl                   Pointer to the instance control structure.
 * @param[in] p_device_address         Pointer to the device address.
 * @param[in] byte_count               Number of bytes to be erased.
 *
 * @retval FSP_SUCCESS                 The command to erase the flash was executed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_device_address is NULL, or byte_count doesn't match an erase
 *                                     size defined in spi_flash_cfg_t, or device is in XiP mode.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XiP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 * @retval FSP_ERR_TIMEOUT             The erase operation timed out.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_Erase (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_device_address, uint32_t byte_count)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_qspi_w_param_checking_dcom(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_device_address);
#endif

    uint8_t erase_command = (uint8_t) r_qspi_w_get_erase_opcode(p_instance_ctrl, byte_count);

    if (SPI_FLASH_ERASE_SIZE_CHIP_ERASE == byte_count)
    {
        /* MANUAL MODE chip erase. */
        r_qspi_w_erase_chip(p_instance_ctrl, erase_command);
    }
    else
    {
        qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
        uint8_t                 channel       = p_inst_extend->channel;

        /* AUTO MODE block erase. */

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
        FSP_ASSERT(0U != erase_command);
#endif
        QSPI_REG(channel)->QSPIC_ERASECMDA_REG_b.QSPIC_ERS_INST = erase_command;

        return r_qspi_w_erase_flash_sector(p_instance_ctrl, r_qspi_w_get_chip_address(p_device_address));
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets the write or erase status of the flash.
 *
 * Implements @ref spi_flash_api_t::statusGet.
 *
 * @param[in]  p_ctrl                   Pointer to the instance control structure.
 * @param[out] p_status                 Pointer to the status @ref spi_flash_status_t.
 *
 * @retval FSP_SUCCESS                  The write status is in p_status.
 * @retval FSP_ERR_ASSERTION            p_instance_ctrl or p_status is NULL.
 * @retval FSP_ERR_NOT_OPEN             Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE         This function can't be called when XiP mode is enabled.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_StatusGet (spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Do not enter direct communication mode from XiP mode. */
    FSP_ERROR_RETURN(false == p_instance_ctrl->xip_mode_is_enabled, FSP_ERR_INVALID_MODE);
#endif

    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    /* Read device status. */
    if (QSPI_W_ERS_NO != r_qspi_w_get_erase_status(channel))
    {
        p_status->write_in_progress = true;
    }
    else
    {
        p_status->write_in_progress = !(r_qspi_w_flash_is_writable(p_instance_ctrl));
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Selects the bank to access.
 *
 * Implements @ref spi_flash_api_t::bankSet.
 *
 * @param[in] p_ctrl                   Pointer to the instance control structure.
 * @param[in] bank                     The bank which need to access.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by QSPI_W.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_BankSet (spi_flash_ctrl_t * p_ctrl, uint32_t bank)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(bank);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Sets the SPI protocol.
 *
 * @note Updates QSPI_W manual mode bus mode registers.
 *
 * Implements @ref spi_flash_api_t::spiProtocolSet.
 *
 * @param[in] p_ctrl                   Pointer to the instance control structure.
 * @param[in] spi_protocol             The type of SPI Flash protocol.
 *
 * @retval FSP_SUCCESS                 SPI protocol registers updated successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    Invalid SPI protocol requested.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_SpiProtocolSet (spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(spi_protocol != SPI_FLASH_PROTOCOL_SOPI &&
                     spi_protocol != SPI_FLASH_PROTOCOL_DOPI &&
                     spi_protocol != SPI_FLASH_PROTOCOL_8D_8D_8D,
                     FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Update the SPI protocol. */
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;
    qspi_w_bus_mode_t       bus_mode[2]   = {QSPI_W_BUS_MODE_SINGLE};

    r_qspi_w_get_bus_mode(spi_protocol, bus_mode);

    r_qspi_w_enter_manual_access_mode(p_instance_ctrl);

    r_qspi_w_manual_access_bus_mode_set(channel, bus_mode[QSPI_W_IDX_INSTR_BUS_MODE]);

    r_qspi_w_enter_auto_access_mode(p_inst_extend);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Auto-calibrate the OctaRAM device using the preamble pattern.
 * Implements @ref spi_flash_api_t::autoCalibrate.
 *
 * @param[in] p_ctrl              Pointer to the instance control structure.
 *
 * @retval FSP_ERR_UNSUPPORTED    API not supported by QSPI_W.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_AutoCalibrate (spi_flash_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Close the QSPI_W driver module.
 *
 * Implements @ref spi_flash_api_t::close.
 *
 * @param[in] p_ctrl            Pointer to the instance control structure.
 *
 * @retval FSP_SUCCESS          Close module successfully.
 * @retval FSP_ERR_ASSERTION    p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN     Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_W_Close (spi_flash_ctrl_t * p_ctrl)
{
    qspi_w_instance_ctrl_t * p_instance_ctrl = (qspi_w_instance_ctrl_t *) p_ctrl;

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->open = 0U;

    /* Disable clock to the QSPI_W block. */
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

#if defined(BSP_MCU_GROUP_RA6W1)

    /* Data cache disable setting */
    if (QSPI_W_DCACHE_ENABLE == p_inst_extend->qspi_dcache)
    {
        FSP_ERROR_RETURN(FSP_SUCCESS == r_qspi_w_dcache_set_cacheable_len(0), FSP_ERR_TIMEOUT);
        FSP_ERROR_RETURN(FSP_SUCCESS == r_qspi_w_dcache_disable(), FSP_ERR_TIMEOUT);
    }
#endif

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if (0 == channel)
    {
#if defined(CRG_TOP_CLK_AMBA_REG_QSPI2_ENABLE_Msk)
        CRG_TOP->CLK_AMBA_REG_b.QSPI2_ENABLE = 0;
#else
        CRG_TOP->CLK_AMBA_REG_b.QSPI_ENABLE = 0;
#endif
    }

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup QSPI_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Set the direction and the level of QSPIC IOs based on the Bus Mode.
 *
 * @param[in] channel     QSPI controller id.
 * @param[in] bus_mode    The QSPIC Bus Mode.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_set_io (uint8_t channel, qspi_w_bus_mode_t bus_mode)
{
    uint32_t ctrlmode_reg = QSPI_REG(channel)->QSPIC_CTRLMODE_REG;

    switch (bus_mode)
    {
        case QSPI_W_BUS_MODE_QUAD:
        {
            FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO2_OEN, ctrlmode_reg, 0);
            FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO3_OEN, ctrlmode_reg, 0);
            break;
        }

        default:
        {
            /* QSPI_BUS_MODE_SINGLE or QSPI_BUS_MODE_DUAL. */
            FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO2_OEN, ctrlmode_reg, 1);
            FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO2_DAT, ctrlmode_reg, 1);
            FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO3_OEN, ctrlmode_reg, 1);
            FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO3_DAT, ctrlmode_reg, 1);
            break;
        }
    }

    QSPI_REG(channel)->QSPIC_CTRLMODE_REG = ctrlmode_reg;
}

/*******************************************************************************************************************//**
 * Generate 32 bits data transfer from the QSPIC to the external device (manual mode).
 *
 * @param[in] channel    QSPI controller id.
 * @param[in] data       32 bits value to be written on the device.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_write32 (uint8_t channel, uint32_t data)
{
    volatile qspi_w_data_t * p_tmp = (volatile qspi_w_data_t *) &(QSPI_REG(channel)->QSPIC_WRITEDATA_REG);

    p_tmp->data32 = FSP_SWAP32(data);
}

/*******************************************************************************************************************//**
 * Generate 8 bits data transfer from the QSPIC to the external device (manual mode).
 *
 * @param[in] channel    QSPI controller id.
 * @param[in] data       8 bits value to be written on the device.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_write8 (uint8_t channel, uint8_t data)
{
    volatile qspi_w_data_t * p_tmp = (volatile qspi_w_data_t *) &(QSPI_REG(channel)->QSPIC_WRITEDATA_REG);

    p_tmp->data8 = data;
}

/*******************************************************************************************************************//**
 * Initialize the read status register instruction of the QSPIC.
 *
 * @param[in] channel                    QSPI controller id.
 * @param[in] p_read_status_instr_cfg    Pointer to configuration structure of the read status register
 *                                       instruction.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_read_status_instr_init (uint8_t                                channel,
                                                           const qspi_w_read_status_instr_cfg_t * p_read_status_instr_cfg)
{
    if (p_read_status_instr_cfg)
    {
        uint32_t statuscmd_reg = QSPI_REG(channel)->QSPI_W_STATUSCMDA_REG;

        QSPI_W_STATUSCMDA_REG_FIELD_SET(QSPIC_BUSY_VAL, statuscmd_reg, p_read_status_instr_cfg->busy_level);
        QSPI_W_STATUSCMDA_REG_FIELD_SET(QSPIC_STSDLY_SEL, statuscmd_reg, p_read_status_instr_cfg->stsdly_sel);
        QSPI_W_STATUSCMDA_REG_FIELD_SET(QSPIC_RESSTS_DLY, statuscmd_reg, p_read_status_instr_cfg->delay_cycles);
        QSPI_W_STATUSCMDA_REG_FIELD_SET(QSPIC_BUSY_POS, statuscmd_reg, p_read_status_instr_cfg->busy_pos);
        QSPI_W_STATUSCMDA_REG_FIELD_SET(QSPIC_RSTAT_RX_MD, statuscmd_reg, p_read_status_instr_cfg->receive_bus_mode);
        QSPI_W_STATUSCMDA_REG_FIELD_SET(QSPIC_RSTAT_TX_MD, statuscmd_reg, p_read_status_instr_cfg->opcode_bus_mode);
        QSPI_W_STATUSCMDA_REG_FIELD_SET(QSPIC_RSTAT_INST, statuscmd_reg, p_read_status_instr_cfg->opcode);

        QSPI_REG(channel)->QSPI_W_STATUSCMDA_REG = statuscmd_reg;

#if defined(QSPIC_QSPIC_STATUSCMDB_REG_QSPIC_RSTAT_REQ_Msk)
        statuscmd_reg = QSPI_REG(channel)->QSPIC_STATUSCMDB_REG;
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_STATUSCMDB_REG,
                              QSPIC_RSTAT_REQ,
                              statuscmd_reg,
                              p_read_status_instr_cfg->rstat_req);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_STATUSCMDB_REG,
                              QSPIC_RSTAT_SPLIT_EN,
                              statuscmd_reg,
                              p_read_status_instr_cfg->rstat_split_en);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_STATUSCMDB_REG,
                              QSPIC_RSTAT_RDB_EN,
                              statuscmd_reg,
                              p_read_status_instr_cfg->rstat_rdb_en);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_STATUSCMDB_REG,
                              QSPIC_RSTAT_DMY_EN,
                              statuscmd_reg,
                              p_read_status_instr_cfg->rstat_dmy_en);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_STATUSCMDB_REG,
                              QSPIC_RSTAT_DMY_ZERO,
                              statuscmd_reg,
                              p_read_status_instr_cfg->dummy_value);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_STATUSCMDB_REG,
                              QSPIC_RSTAT_DMY_TX_MD,
                              statuscmd_reg,
                              p_read_status_instr_cfg->dummy_bus_mode);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_STATUSCMDB_REG,
                              QSPIC_RSTAT_DMY_NUM,
                              statuscmd_reg,
                              p_read_status_instr_cfg->rstat_dmy_num);

        QSPI_REG(channel)->QSPIC_STATUSCMDB_REG = statuscmd_reg;
#endif
    }
}

/*******************************************************************************************************************//**
 * Initialize the write enable instruction of the QSPIC.
 *
 * @param[in] channel                  QSPI controller id.
 * @param[in] p_wrt_enble_instr_cfg    Pointer to configuration structure of the write enable instruction.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_write_enable_instr_init (uint8_t                                 channel,
                                                            const qspi_w_write_enable_instr_cfg_t * p_wrt_enble_instr_cfg)
{
    if (p_wrt_enble_instr_cfg)
    {
        QSPI_REG(channel)->QSPIC_ERASECMDA_REG_b.QSPIC_WEN_INST  = p_wrt_enble_instr_cfg->opcode;
        QSPI_REG(channel)->QSPIC_ERASECMDB_REG_b.QSPIC_WEN_TX_MD = p_wrt_enble_instr_cfg->opcode_bus_mode;
    }
}

/*******************************************************************************************************************//**
 * Initialize the erase instruction of the QSPIC.
 *
 * @param[in] channel              QSPI controller id.
 * @param[in] p_erase_instr_cfg    Pointer to configuration structure of the erase instruction.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_erase_instr_init (uint8_t                          channel,
                                                     const qspi_w_erase_instr_cfg_t * p_erase_instr_cfg)
{
    if (p_erase_instr_cfg)
    {
        QSPI_REG(channel)->QSPIC_ERASECMDA_REG_b.QSPIC_ERS_INST = p_erase_instr_cfg->opcode;

        uint32_t erasecmdb_reg = QSPI_REG(channel)->QSPIC_ERASECMDB_REG;

        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDB_REG,
                              QSPIC_ERS_TX_MD,
                              erasecmdb_reg,
                              p_erase_instr_cfg->opcode_bus_mode);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDB_REG,
                              QSPIC_EAD_TX_MD,
                              erasecmdb_reg,
                              p_erase_instr_cfg->addr_bus_mode);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDB_REG,
                              QSPIC_ERSRES_HLD,
                              erasecmdb_reg,
                              p_erase_instr_cfg->hclk_cycles);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDB_REG,
                              QSPIC_ERS_CS_HI,
                              erasecmdb_reg,
                              p_erase_instr_cfg->cs_idle_delay_cycles);

        QSPI_REG(channel)->QSPIC_ERASECMDB_REG = erasecmdb_reg;
    }
}

/*******************************************************************************************************************//**
 * Initialize the program and erase suspend/resume instruction of the QSPIC.
 *
 * @param[in] channel                QSPI controller id.
 * @param[in] p_sus_res_instr_cfg    Pointer to configuration structure of the program and erase suspend/resume
 *                                   instruction.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_suspend_resume_instr_init (uint8_t                                   channel,
                                                              const qspi_w_suspend_resume_instr_cfg_t * p_sus_res_instr_cfg)
{
    if (p_sus_res_instr_cfg)
    {
        uint32_t erasecmda_reg = QSPI_REG(channel)->QSPIC_ERASECMDA_REG;
        uint32_t erasecmdb_reg = QSPI_REG(channel)->QSPIC_ERASECMDB_REG;

        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDA_REG,
                              QSPIC_SUS_INST,
                              erasecmda_reg,
                              p_sus_res_instr_cfg->suspend_opcode);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDA_REG,
                              QSPIC_RES_INST,
                              erasecmda_reg,
                              p_sus_res_instr_cfg->resume_opcode);

        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDB_REG,
                              QSPIC_SUS_TX_MD,
                              erasecmdb_reg,
                              p_sus_res_instr_cfg->suspend_bus_mode);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDB_REG,
                              QSPIC_RES_TX_MD,
                              erasecmdb_reg,
                              p_sus_res_instr_cfg->resume_bus_mode);
        FSP_REG_VAR_FIELD_SET(QSPIC,
                              QSPIC_ERASECMDB_REG,
                              QSPIC_RESSUS_DLY,
                              erasecmdb_reg,
                              p_sus_res_instr_cfg->res_sus_latency_clk_cycles);

        QSPI_REG(channel)->QSPIC_ERASECMDA_REG = erasecmda_reg;
        QSPI_REG(channel)->QSPIC_ERASECMDB_REG = erasecmdb_reg;

#if defined(QSPIC_QSPIC_ERASECMDC_REG_QSPIC_SUSSTS_DLY_Msk)
        QSPIC->QSPIC_ERASECMDC_REG_b.QSPIC_SUSSTS_DLY = p_sus_res_instr_cfg->sussts_dly;
#endif
    }
}

/*******************************************************************************************************************//**
 * Initialize the write instruction of the QSPIC in auto mode when device is PSRAM.
 *
 * @param[in] channel            QSPI controller id.
 * @param[in] p_wrt_instr_cfg    Pointer to configuration structure of the write instruction (PSRAM, auto mode).
 *
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_write_instr_init (uint8_t channel, const qspi_w_write_instr_cfg_t * p_wrt_instr_cfg)
{
#if defined(QSPIC_QSPIC_AWRITECMDB_REG_QSPIC_WR_CS_HIGH_MIN_Msk)
    uint32_t reg_val = QSPI_REG(channel)->QSPIC_AWRITECMDB_REG;

    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_AWRITECMDB_REG, QSPIC_SEND_WEN_REQ, reg_val, p_wrt_instr_cfg->send_wen_req);
    FSP_REG_VAR_FIELD_SET(QSPIC,
                          QSPIC_AWRITECMDB_REG,
                          QSPIC_WR_CS_HIGH_MIN,
                          reg_val,
                          p_wrt_instr_cfg->cs_hi_min_clk_cycles);

    QSPI_REG(channel)->QSPIC_AWRITECMDB_REG = reg_val;

    reg_val = QSPI_REG(channel)->QSPI_W_AWRITECMDA_REG;
#else
    uint32_t reg_val = QSPI_REG(channel)->QSPI_W_AWRITECMDA_REG;
#endif

    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_INST, reg_val, p_wrt_instr_cfg->write_opcode);
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_INST_TX_MD, reg_val, p_wrt_instr_cfg->opcode_bus_mode);
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_ADR_TX_MD, reg_val, p_wrt_instr_cfg->addr_bus_mode);
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_DAT_TX_MD, reg_val, p_wrt_instr_cfg->data_bus_mode);
#if !defined(BSP_MCU_GROUP_RA6W1)
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_INST_WB, reg_val, p_wrt_instr_cfg->write_opcode_wb);
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_DMY_TX_MD, reg_val, p_wrt_instr_cfg->dummy_bus_mode);
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_DMY_EN, reg_val, p_wrt_instr_cfg->dummy_en);
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_DMY_NUM, reg_val, p_wrt_instr_cfg->dummy_bytes);
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_WDEX_EN, reg_val, p_wrt_instr_cfg->wdex_en);
#else
    QSPI_W_AWRITECMDA_REG_FIELD_SET(QSPIC_WR_CS_HIGH_MIN, reg_val, p_wrt_instr_cfg->cs_hi_min_clk_cycles);
#endif
    QSPI_REG(channel)->QSPI_W_AWRITECMDA_REG = reg_val;
}

/*******************************************************************************************************************//**
 * Initialize the burst break instruction of the QSPIC.
 *
 * @param[in] channel              QSPI controller id.
 * @param[in] p_break_instr_cfg    Pointer to configuration structure of Burst break instruction.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_break_instr_init (uint8_t                          channel,
                                                     const qspi_w_break_instr_cfg_t * p_break_instr_cfg)
{
    QSPI_REG(channel)->QSPIC_BURSTBRK_REG =
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_SEC_HF_DS, p_break_instr_cfg->break_sec_hf) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_SZ, p_break_instr_cfg->break_sz) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_TX_MD, p_break_instr_cfg->break_tx_md) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_EN, p_break_instr_cfg->break_en) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_WRD, p_break_instr_cfg->break_opcode);
}

/*******************************************************************************************************************//**
 * Initialize the External memory burst of the QSPIC.
 *
 * @param[in] channel          QSPI controller id.
 * @param[in] p_memblen_cfg    Pointer to configuration structure of External memory burst.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_memblen_init (uint8_t channel, const qspi_w_memblen_cfg_t * p_memblen_cfg)
{
    QSPI_REG(channel)->QSPIC_MEMBLEN_REG =
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_MEMBLEN, p_memblen_cfg->memblen) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_T_CEM_EN, p_memblen_cfg->tcem_en) |
#if defined(BSP_MCU_GROUP_RA6W1)
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_T_CEM_CC, p_memblen_cfg->tcem_cc);
#else
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_T_CEM_CC, p_memblen_cfg->tcem_cc) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_RD_LIN_EN, p_memblen_cfg->rd_lin_en) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_KEEP_ACTIVE, p_memblen_cfg->keep_active) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_WCMD_HYBRID, p_memblen_cfg->wcmd_hybrid) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_DIELEN, p_memblen_cfg->dielen) |
        FSP_REG_FIELD_SET_BITS32(QSPIC, QSPIC_MEMBLEN_REG, QSPIC_ACTIVE_THR, p_memblen_cfg->active_thr);
#endif
}

/*******************************************************************************************************************//**
 * Get erase status.
 *
 * @param[in] channel             QSPI controller id.
 *
 * @retval    QSPI_W_ERS_NO         No erase
 * @retval    QSPI_W_ERS_PENDING    Pending erase request.
 * @retval    QSPI_W_ERS_RUNNING    Erase procedure is running.
 * @retval    QSPI_W_ERS_SUSPENDED  Suspended erase procedure.
 * @retval    QSPI_W_ERS_FINISHING  Finishing the erase procedure.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE qspi_w_ers_t r_qspi_w_get_erase_status (uint8_t channel)
{
    QSPI_REG(channel)->QSPIC_CHCKERASE_REG = 0;

    return (qspi_w_ers_t) (QSPI_REG(channel)->QSPIC_ERASECTRL_REG_b.QSPIC_ERS_STATE);
}

/*******************************************************************************************************************//**
 * Generate 8 bits data transfer from the external device to the QSPIC (manual mode).
 *
 * @param[in] channel    QSPI controller id.
 *
 * @return    uint8_t    8 bits value read from the bus.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE uint8_t r_qspi_w_read8 (uint8_t channel)
{
    volatile qspi_w_data_t * p_tmp = (volatile qspi_w_data_t *) &(QSPI_REG(channel)->QSPIC_READDATA_REG);

    return p_tmp->data8;
}

/*******************************************************************************************************************//**
 * Fast copy of a buffer to a FIFO.
 *
 * @details Implementation of a fast copy of the contents of a buffer to a FIFO in assembly.
 *          All addresses are word aligned.
 *
 * @param[in]  start    Pointer to the beginning of the buffer.
 * @param[in]  end      Pointer to the end of the buffer.
 * @param[out] dest     Pointer to the FIFO.
 *
 * @warning No validity checks are made! It is the responsibility of the caller to make sure that
 *          sane values are passed to this function.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_fast_write_to_fifo32 (uint32_t start, uint32_t end, uint32_t dest)
{
    __asm volatile ("copy:                                  \n"
                    "       ldmia %[start]!, {r3}           \n"
                    "       str r3, [%[dest]]               \n"
                    "       cmp %[start], %[end]            \n"
                    "       blt copy                        \n"
                    :
                    :                                                         /* output */
                    [start] "l" (start), [end] "r" (end), [dest] "l" (dest) : /* inputs (%0, %1, %2) */
                    "r3");                                                    /* registers that are destroyed. */
}

/*******************************************************************************************************************//**
 * Enter Manual Access Mode.
 *
 * @note This function does not turn the QSPI Flash memory out of the XiP Mode of operation, if enabled.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 **********************************************************************************************************************/
__STATIC_FORCEINLINE void r_qspi_w_enter_manual_access_mode (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    if (QSPI_W_ACCESS_MODE_AUTO == QSPI_REG(channel)->QSPIC_CTRLMODE_REG_b.QSPIC_AUTO_MD)
    {
        QSPI_REG(channel)->QSPIC_CTRLMODE_REG_b.QSPIC_AUTO_MD = QSPI_W_ACCESS_MODE_MANUAL;
    }
}

/*******************************************************************************************************************//**
 * Writes raw data to QSPI_W.
 *
 * @param[in] p_instance_ctrl     Pointer to a driver handle.
 * @param[in] p_src               Pointer to data to write.
 * @param[in] bytes               Number of bytes to write.
 * @param[in] read_after_write    Whether or not to close SPI bus cycle.
 **********************************************************************************************************************/
static void r_qspi_w_direct_write_sub (qspi_w_instance_ctrl_t * p_instance_ctrl,
                                       uint8_t const * const    p_src,
                                       uint32_t const           bytes,
                                       bool const               read_after_write)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    /* Enter direct communication mode. */
    r_qspi_w_enter_manual_access_mode(p_instance_ctrl);

    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_EN_CS_Msk;

    /* Write data to QSPI_W. */
    for (uint32_t i = 0; i < bytes; i++)
    {
        r_qspi_w_write8(channel, p_src[i]);
    }

    if (!read_after_write)
    {
        /* Close the SPI bus cycle. */
        QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_DIS_CS_Msk;

        /* Return to ROM access mode. */
        r_qspi_w_enter_auto_access_mode(p_inst_extend);
    }
}

/*******************************************************************************************************************//**
 * Reads raw data from QSPI_W.
 *
 * @param[in]  p_instance_ctrl    Pointer to a driver handle.
 * @param[out] p_dest             Pointer to store data.
 * @param[in]  bytes              Number of bytes to read.
 **********************************************************************************************************************/
static void r_qspi_w_direct_read_sub (qspi_w_instance_ctrl_t * p_instance_ctrl,
                                      uint8_t * const          p_dest,
                                      uint32_t const           bytes)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    /* Read data from QSPI_W. */
    for (uint32_t i = 0; i < bytes; i++)
    {
        p_dest[i] = r_qspi_w_read8(channel);
    }

    /* Close the SPI bus cycle. */
    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_DIS_CS_Msk;

    /* Return to ROM access mode. */
    r_qspi_w_enter_auto_access_mode(p_inst_extend);
}

/*******************************************************************************************************************//**
 * Enters or exits XiP (execute in place) mode.
 *
 * @note Quad SPI instructions require the non-volatile Quad Enable bit (QE) in Status Register-2 to be set.
 * This is a user task.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 * @param[in] code               Code to place in M7-M0.
 * @param[in] enter_mode         True to enter, false to exit.
 *
 * @retval    FSP_SUCCESS        Enter/Exit XiP mode successfully.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_w_xip (qspi_w_instance_ctrl_t * p_instance_ctrl, uint8_t code, bool enter_mode)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    if (enter_mode)
    {
        QSPI_REG(channel)->QSPIC_BURSTCMDB_REG_b.QSPIC_INST_MD = QSPI_W_INSTR_MD_TX_ONLY_IN_FIRST_ACCESS;
        r_qspi_w_set_extra_byte(channel, code, p_inst_extend->p_qspi_flash_cfg->p_read_instr_cfg);
    }
    else
    {
        QSPI_REG(channel)->QSPIC_BURSTCMDB_REG_b.QSPIC_INST_MD = QSPI_W_INSTR_MD_TX_AT_ANY_BURST_ACCESS;

        /* Exit XiP mode. */
        volatile uint8_t dummy = 0;
        FSP_PARAMETER_NOT_USED(dummy);

        r_qspi_w_set_extra_byte(channel, code, p_inst_extend->p_qspi_flash_cfg->p_read_instr_cfg);

        /* Read from QSPI_W (preferably non-cached access) to send
         * the XiP exit request (i.e. code - extra byte - mode bits). */
        dummy = *(volatile uint8_t *) QSPI_W_DEVICE_START_ADDRESS_DATA;
    }

    p_instance_ctrl->xip_mode_is_enabled = enter_mode;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set QSPIC bus mode.
 *
 * @param[in] channel     QSPI controller id.
 * @param[in] bus_mode    The QSPIC Bus Mode.
 **********************************************************************************************************************/
static void r_qspi_w_manual_access_bus_mode_set (uint8_t channel, qspi_w_bus_mode_t bus_mode)
{
    if (g_manual_access_bus_mode != bus_mode)
    {
        QSPI_REG(channel)->QSPIC_CTRLBUS_REG = 1U << bus_mode;
        r_qspi_w_set_io(channel, bus_mode);
        g_manual_access_bus_mode = bus_mode;
    }
}

/*******************************************************************************************************************//**
 * Set device to auto mode.
 *
 * @param[in] p_inst_extend    Pointer to a driver extended handle.
 **********************************************************************************************************************/
static void r_qspi_w_enter_auto_access_mode (qspi_w_extended_cfg_t * p_inst_extend)
{
    uint8_t channel = p_inst_extend->channel;

    /*
     * Before switching to Auto Access Mode set the direction of all QSPIC IOs so that they are
     * selected by the controller.
     */
    qspi_w_bus_mode_t bus_mode = p_inst_extend->p_qspi_flash_cfg->p_read_instr_cfg->data_bus_mode;

    r_qspi_w_set_io(channel, bus_mode);
    QSPI_REG(channel)->QSPIC_CTRLMODE_REG_b.QSPIC_AUTO_MD = QSPI_W_ACCESS_MODE_AUTO;
}

/*******************************************************************************************************************//**
 * Write data to flash memory.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 * @param[in] addr               Zero based address of the flash memory, where the
 *                               content of the p_buf is to be written.
 * @param[in] p_buf              Pointer to the source data.
 * @param[in] size               Number of bytes to write.
 *
 * @return    Number of written bytes by the function call.
 *
 * @warning   This function switches and leaves the QSPIC to manual access mode. Therefore, it must
 *            be called with disabled interrupts. It's up to the caller to switch the QSPIC back to
 *            auto access mode, in order to re-enable XiP.
 *
 * @warning   The write operation will not exceed the page boundary. Thus, It's up to the caller to
 *            issue another call of the function, in order to write the remaining data to the next page.
 **********************************************************************************************************************/
static uint32_t r_qspi_w_flash_write_page (qspi_w_instance_ctrl_t * p_instance_ctrl,
                                           uint32_t                 addr,
                                           const uint8_t          * p_buf,
                                           uint32_t                 size)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    uint32_t written_bytes        = 0;
    uint32_t addr_unaligned_bytes = 0;
    uint32_t bytes_aligned32      = 0;
    uint32_t page_boundary;
    uint8_t  opcode =
        p_inst_extend->p_qspi_flash_cfg->p_write_instr_cfg->write_opcode;
    qspi_w_bus_mode_t write_enable_bus_mode =
        p_inst_extend->p_qspi_flash_cfg->p_write_enable_instr_cfg->opcode_bus_mode;
    qspi_w_bus_mode_t opcode_bus_mode =
        p_inst_extend->p_qspi_flash_cfg->p_write_instr_cfg->opcode_bus_mode;
    qspi_w_bus_mode_t addr_bus_mode =
        p_inst_extend->p_qspi_flash_cfg->p_write_instr_cfg->addr_bus_mode;
    qspi_w_bus_mode_t data_bus_mode =
        p_inst_extend->p_qspi_flash_cfg->p_write_instr_cfg->data_bus_mode;
    spi_flash_address_bytes_t addr_bytes = p_instance_ctrl->p_cfg->address_bytes;

    /* Reduce max write size, that can reduce interrupt latency time. */
    if (size > p_instance_ctrl->p_cfg->page_size_bytes)
    {
        size = p_instance_ctrl->p_cfg->page_size_bytes;
    }

    /* Make sure write will not cross page boundary. */
    page_boundary = p_instance_ctrl->p_cfg->page_size_bytes - (addr & QSPI_W_FLASH_PAGE_SIZE);
    if (size > page_boundary)
    {
        size = page_boundary;
    }

    r_qspi_w_enter_manual_access_mode(p_instance_ctrl);
    r_qspi_w_manual_access_bus_mode_set(channel, write_enable_bus_mode);
    r_qspi_w_flash_write_enable(p_instance_ctrl);

    r_qspi_w_manual_access_bus_mode_set(channel, opcode_bus_mode);

    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_EN_CS_Msk;
    r_qspi_w_write8(channel, opcode);

    r_qspi_w_manual_access_bus_mode_set(channel, addr_bus_mode);

    if (SPI_FLASH_ADDRESS_BYTES_4 == addr_bytes)
    {
        r_qspi_w_write32(channel, addr);
    }
    else
    {
        r_qspi_w_write8(channel, (uint8_t) ((addr >> 16U) & 0xFF));
        r_qspi_w_write8(channel, (uint8_t) ((addr >> 8U) & 0xFF));
        r_qspi_w_write8(channel, (uint8_t) (addr & 0xFF));
    }

    r_qspi_w_manual_access_bus_mode_set(channel, data_bus_mode);

    /* Write address-unaligned data byte-per-byte */
    addr_unaligned_bytes = 4 - (((uint32_t) p_buf) & 3);
    for (written_bytes = 0; written_bytes < addr_unaligned_bytes && written_bytes < size; ++written_bytes)
    {
        r_qspi_w_write8(channel, p_buf[written_bytes]);
    }

    /* Write size-aligned data word-per-word */
    bytes_aligned32 = ((size - written_bytes) & 0xFFFFFFFCUL);
    if (bytes_aligned32)
    {
        r_qspi_w_fast_write_to_fifo32((uint32_t) (p_buf + written_bytes),
                                      (uint32_t) (p_buf + written_bytes + bytes_aligned32),
                                      (uint32_t) &((QSPI_REG(channel))->QSPIC_WRITEDATA_REG));
        written_bytes += bytes_aligned32;
    }

    /* Write size-unaligned data byte-per-byte */
    for ( ; written_bytes < size; ++written_bytes)
    {
        r_qspi_w_write8(channel, p_buf[written_bytes]);
    }

    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_DIS_CS_Msk;

    return written_bytes;
}

/*******************************************************************************************************************//**
 * Return the zero-based chip address from the memory mapped address.
 *
 * @param[in] p_addr    Pointer to memory mapped address.
 *
 * @return    uint32_t  Zero-based chip address.
 **********************************************************************************************************************/
static uint32_t r_qspi_w_get_chip_address (uint8_t * const p_addr)
{
    if ((uint32_t) p_addr >= QSPI_W_DEVICE_START_ADDRESS_DATA)
    {
        return (uint32_t) p_addr - QSPI_W_DEVICE_START_ADDRESS_DATA;
    }
    else
    {
        return (uint32_t) p_addr - QSPI_W_DEVICE_START_ADDRESS;
    }
}

/*******************************************************************************************************************//**
 * Erase block/sector of flash memory.
 *
 * @note        Before erasing the flash memory, it is mandatory to set up the erase instructions
 *              first by calling r_qspi_w_erase_instr_init().
 *
 * @note        Call r_qspi_w_get_erase_status() to check whether the erase operation has finished.
 *
 * @note        Before switching the QSPI controller to manual mode check that
 *              r_qspi_w_get_erase_status() == QSPI_W_ERASE_STATUS_NO.
 *
 * @param[in]  channel    QSPI controller id.
 * @param[in]  addr       Memory address of the block/sector to be erased.
 **********************************************************************************************************************/
static void r_qspi_w_erase_block (uint8_t channel, uint32_t addr)
{
    uint32_t block_sector = addr / QSPI_W_FLASH_SECTOR_SIZE;

    /* Wait for previous erase to end. */
    while (QSPI_W_ERS_NO != r_qspi_w_get_erase_status(channel))
    {
        /* No messages to process. */
        ;
    }

    if (QSPI_W_ACCESS_MODE_AUTO != QSPI_REG(channel)->QSPIC_CTRLMODE_REG_b.QSPIC_AUTO_MD)
    {
        QSPI_REG(channel)->QSPIC_CTRLMODE_REG_b.QSPIC_AUTO_MD = QSPI_W_ACCESS_MODE_AUTO;
    }

    /*
     * In order to calculate the sector number and set the proper value for the QSPIC_ERS_ADDR
     * field in the QSPIC_ERASECTRL_REG, the given address needs to be divided by the sector size.
     * However, when using 24 bits addressing size, the sector number needs to be stored in the
     * higher 12 bits of the field, as the remaining bits are disregarded. As a result, the sector
     * number must be shifted left by 8 bits to account for this.
     *
     *                          QSPIC_ERASECTRL_REG[QSPIC_ERS_ADDR]
     *     =====================================================================
     *              19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
     *     =====================================================================
     *     24 bits:  v  v  v  v  v  v  v  v  v  v  v  v  x  x  x  x  x  x  x  x
     *     32 bits:  v  v  v  v  v  v  v  v  v  v  v  v  v  v  v  v  v  v  v  v
     */
    if (0 == QSPI_REG(channel)->QSPIC_CTRLMODE_REG_b.QSPIC_USE_32BA)
    {
        block_sector <<= 8U;
    }

    uint32_t erasectrl_reg = QSPI_REG(channel)->QSPIC_ERASECTRL_REG;

    /* Setup erase block page. */
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_ERASECTRL_REG, QSPIC_ERS_ADDR, erasectrl_reg, block_sector);

    /* Trigger erase. */
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_ERASECTRL_REG, QSPIC_ERASE_EN, erasectrl_reg, 1);

    QSPI_REG(channel)->QSPIC_ERASECTRL_REG = erasectrl_reg;
}

/*******************************************************************************************************************//**
 * Erase sector of flash memory.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 * @param[in] addr               Memory address of the sector to be erased.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_w_erase_flash_sector (qspi_w_instance_ctrl_t * p_instance_ctrl, uint32_t addr)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;
    uint32_t                timeout       = QSPI_W_PRV_TIMEOUT_US;

    while (!r_qspi_w_flash_is_writable(p_instance_ctrl))
    {
        /* No messages to process. */
        ;
    }

    r_qspi_w_erase_block(channel, addr);

    /* Ensure erase block has started. QSPI_W_ERS_NO will occur later when erase will be finished. User has to monitor when erase is done. */
    while (QSPI_W_ERS_NO == r_qspi_w_get_erase_status(channel) && timeout)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;
    }

    FSP_ERROR_RETURN(0U < timeout, FSP_ERR_TIMEOUT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get erase instruction code.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 * @param[in] byte_count         Number of bytes to be erased.
 *
 * @return    uint16_t           Erase instruction code.
 **********************************************************************************************************************/
static uint16_t r_qspi_w_get_erase_opcode (qspi_w_instance_ctrl_t * p_instance_ctrl, uint32_t byte_count)
{
    uint16_t erase_command = 0;

    for (uint32_t idx = 0; idx < p_instance_ctrl->p_cfg->erase_command_list_length; idx++)
    {
        /* If requested byte_count is supported by underlying flash, store the command. */
        if (byte_count == p_instance_ctrl->p_cfg->p_erase_command_list[idx].size)
        {
            erase_command = p_instance_ctrl->p_cfg->p_erase_command_list[idx].command;
            break;
        }
    }

    return erase_command;
}

/*******************************************************************************************************************//**
 * Erase chip.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 * @param[in] erase_command      Erase instruction code.
 **********************************************************************************************************************/
static void r_qspi_w_erase_chip (qspi_w_instance_ctrl_t * p_instance_ctrl, uint8_t erase_command)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    /* Disable the interrupts as long as the QSPIC remains in manual access mode. */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    r_qspi_w_enter_manual_access_mode(p_instance_ctrl);
    r_qspi_w_flash_write_enable(p_instance_ctrl);
    r_qspi_w_flash_cmd(channel, erase_command);
    while (r_qspi_w_flash_is_busy(p_instance_ctrl))
    {
        /* No messages to process. */
        ;
    }

    r_qspi_w_enter_auto_access_mode(p_inst_extend);

    /* Re-enable the interrupts since the QSPIC switched back to auto access mode. */
    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 * Initialize the QSPI controller instruction registers.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 **********************************************************************************************************************/
static void r_qspi_w_instructions_init (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    r_qspi_w_read_instr_init(channel, p_inst_extend->p_qspi_flash_cfg->p_read_instr_cfg);
    r_qspi_w_break_instr_init(channel, p_inst_extend->p_qspi_flash_cfg->p_break_instr_cfg);
    r_qspi_w_memblen_init(channel, p_inst_extend->p_qspi_flash_cfg->p_memblen_cfg);
    r_qspi_w_write_instr_init(channel, p_inst_extend->p_qspi_flash_cfg->p_write_instr_cfg);
    r_qspi_w_read_status_instr_init(channel, p_inst_extend->p_qspi_flash_cfg->p_read_status_instr_cfg);
    r_qspi_w_erase_instr_init(channel, p_inst_extend->p_qspi_flash_cfg->p_erase_instr_cfg);
    r_qspi_w_suspend_resume_instr_init(channel, p_inst_extend->p_qspi_flash_cfg->p_suspend_resume_instr_cfg);
    r_qspi_w_write_enable_instr_init(channel, p_inst_extend->p_qspi_flash_cfg->p_write_enable_instr_cfg);
#if BSP_FEATURE_QSPI_HAS_DDR_SUPPORT
    if (p_inst_extend->p_qspi_flash_cfg->p_ctrl_ddr)
    {
        QSPI_REG(channel)->QSPIC_CTRLDDRA_REG = p_inst_extend->p_qspi_flash_cfg->p_ctrl_ddr->ctrl_ddra;
        QSPI_REG(channel)->QSPIC_CTRLDDRB_REG = p_inst_extend->p_qspi_flash_cfg->p_ctrl_ddr->ctrl_ddrb;
    }

    if (p_inst_extend->p_qspi_flash_cfg->p_extra_regs)
    {
        QSPI_REG(channel)->QSPIC_CTRLMR_REG   = p_inst_extend->p_qspi_flash_cfg->p_extra_regs->ctrl_mr_reg;
        QSPI_REG(channel)->QSPIC_DRST_CMD_REG = p_inst_extend->p_qspi_flash_cfg->p_extra_regs->drst_cmd_reg;
    }
#endif
}

/*******************************************************************************************************************//**
 * Initialize the QSPI controller based on the QSPI_W flash driver.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 **********************************************************************************************************************/
static void r_qspi_w_controller_init (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
    uint32_t clkamba_reg = CRG_TOP->CLK_AMBA_REG;

#if BSP_FEATURE_QSPI_HAS_DDR_SUPPORT
    QSPI_W_CLK_AMBA_REG_FIELD_SET(SDR_DIV2, clkamba_reg, p_inst_extend->qspclk_div);
    QSPI_W_CLK_AMBA_REG_FIELD_SET(SDR_MODE, clkamba_reg, p_inst_extend->qspi_mode);
#else
    QSPI_W_CLK_AMBA_REG_FIELD_SET(DIV, clkamba_reg, p_inst_extend->qspclk_div);
#endif
    QSPI_W_CLK_AMBA_REG_FIELD_SET(ENABLE, clkamba_reg, 1);

    CRG_TOP->CLK_AMBA_REG = clkamba_reg;

    /* CLK_AMBA_REG is in APB (PCLK might be slower than HCLK). */
    FSP_HARDWARE_REGISTER_WAIT(CRG_TOP->CLK_AMBA_REG, clkamba_reg);

    FSP_CRITICAL_SECTION_EXIT;
    uint32_t ctrlmode_reg = QSPI_REG(channel)->QSPIC_CTRLMODE_REG;
    uint32_t gp_reg       = QSPI_REG(channel)->QSPIC_GP_REG;

    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_USE_32BA, ctrlmode_reg,
                          p_instance_ctrl->p_cfg->address_bytes);

    FSP_REG_VAR_FIELD_SET(QSPIC,
                          QSPIC_CTRLMODE_REG,
                          QSPIC_CLK_MD,
                          ctrlmode_reg,
                          p_inst_extend->p_qspi_flash_cfg->clk_mode);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_RXD_NEG, ctrlmode_reg, QSPI_W_SAMPLING_EDGE_POS);

    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_RPIPE_EN, ctrlmode_reg, QSPI_W_READ_PIPE_ENABLE);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_PCLK_MD, ctrlmode_reg, QSPI_W_READ_PIPE_DELAY);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_HRDY_MD, ctrlmode_reg, QSPI_W_HREADY_MODE_WAIT);
#if !defined(BSP_MCU_GROUP_RA6W1)
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_MAN_DIRCHG_MD, ctrlmode_reg, 1);
#endif

    if (p_inst_extend->p_qspi_flash_cfg->is_ram)
    {
        FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_SRAM_EN, ctrlmode_reg, 1);
        FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_CS_MD, ctrlmode_reg, 1);
        FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_CLK_FREE_EN, ctrlmode_reg, 1);

        QSPI_REG(channel)->QSPIC_CTRLMODE_REG = ctrlmode_reg;

        for (uint32_t i = 0; i < 10; i++)
        {
            __NOP();
        }

        QSPIC->QSPIC_CTRLMODE_REG_b.QSPIC_CLK_FREE_EN = 0;
    }
    else
    {
        QSPI_REG(channel)->QSPIC_CTRLMODE_REG = ctrlmode_reg;
    }

    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_GP_REG, QSPIC_PADS_DRV, gp_reg, p_inst_extend->qspi_drive_current);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_GP_REG, QSPIC_PADS_SLEW, gp_reg, p_inst_extend->qspi_slew_rate);

    QSPI_REG(channel)->QSPIC_GP_REG = gp_reg;

    r_qspi_w_enter_auto_access_mode(p_inst_extend);
}

/*******************************************************************************************************************//**
 * Based on the requested protocol, return the bus mode of the instruction (or opcode) and addr/extra/dummy/data bus.
 *
 * @note The protocol mode xS-xS-xS means that the bus (opcode, address and data) is in Single Data Rate.
 *       The protocol mode xD-xD-xD means that the bus (opcode, address and data) is in Double Data Rate.
 *
 * @param[in]  spi_protocol     Requested protocol.
 * @param[out] p_bus_mode       Pointer to store data.
 **********************************************************************************************************************/
static void r_qspi_w_get_bus_mode (spi_flash_protocol_t spi_protocol, qspi_w_bus_mode_t * p_bus_mode)
{
    switch (spi_protocol)
    {
        case SPI_FLASH_PROTOCOL_EXTENDED_SPI: // SPI_FLASH_PROTOCOL_1S_1S_1S is the same enum value.
        {
            p_bus_mode[QSPI_W_IDX_INSTR_BUS_MODE]     = QSPI_W_BUS_MODE_SINGLE;
            p_bus_mode[QSPI_W_IDX_NON_INSTR_BUS_MODE] = QSPI_W_BUS_MODE_SINGLE;
            break;
        }

        case SPI_FLASH_PROTOCOL_1S_2S_2S:
        {
            p_bus_mode[QSPI_W_IDX_INSTR_BUS_MODE]     = QSPI_W_BUS_MODE_SINGLE;
            p_bus_mode[QSPI_W_IDX_NON_INSTR_BUS_MODE] = QSPI_W_BUS_MODE_DUAL;
            break;
        }

        case SPI_FLASH_PROTOCOL_1S_4S_4S:
        {
            p_bus_mode[QSPI_W_IDX_INSTR_BUS_MODE]     = QSPI_W_BUS_MODE_SINGLE;
            p_bus_mode[QSPI_W_IDX_NON_INSTR_BUS_MODE] = QSPI_W_BUS_MODE_QUAD;
            break;
        }

        case SPI_FLASH_PROTOCOL_2S_2S_2S:
        {
            p_bus_mode[QSPI_W_IDX_INSTR_BUS_MODE]     = QSPI_W_BUS_MODE_DUAL;
            p_bus_mode[QSPI_W_IDX_NON_INSTR_BUS_MODE] = QSPI_W_BUS_MODE_DUAL;
            break;
        }

        /* The below protocols transmit both the instruction and non instruction bytes using QUAD bus mode */
        case SPI_FLASH_PROTOCOL_QPI:
        case SPI_FLASH_PROTOCOL_4S_4S_4S:
        case SPI_FLASH_PROTOCOL_4S_4D_4D:
        {
            p_bus_mode[QSPI_W_IDX_INSTR_BUS_MODE]     = QSPI_W_BUS_MODE_QUAD;
            p_bus_mode[QSPI_W_IDX_NON_INSTR_BUS_MODE] = QSPI_W_BUS_MODE_QUAD;
            break;
        }

        default:
        {
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Check if the Flash can accept commands.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 *
 * @return    bool               True if the Flash is not busy else false.
 **********************************************************************************************************************/
static bool r_qspi_w_flash_is_writable (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    bool writable;

    /* Disable the interrupts as long as the QSPIC remains in manual access mode. */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    r_qspi_w_enter_manual_access_mode(p_instance_ctrl);

    /* Check if flash is ready. */
    writable = !(r_qspi_w_flash_is_busy(p_instance_ctrl));

    r_qspi_w_enter_auto_access_mode(p_inst_extend);

    /* Re-enable the interrupts since the QSPIC switched back to auto access mode. */
    FSP_CRITICAL_SECTION_EXIT;

    return writable;
}

/*******************************************************************************************************************//**
 * Send flash command.
 *
 * @param[in]  channel    QSPI controller id.
 * @param[in]  opcode     Command code to be send to the flash device.
 **********************************************************************************************************************/
static void r_qspi_w_flash_cmd (uint8_t channel, const uint8_t opcode)
{
    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_EN_CS_Msk;
    r_qspi_w_write8(channel, opcode);
    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_DIS_CS_Msk;
}

/*******************************************************************************************************************//**
 * Set WEL (Write Enable Latch) bit of the Status Register of the Flash.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 *
 * @details The WEL bit must be set prior to every Page Program, Quad Page Program, Sector Erase,
 *          Block Erase, Chip Erase, Write Status Register and Erase/Program Security Registers
 *          instruction. In the case of Write Status Register command, any status bits will be written
 *          as non-volatile bits.
 *
 * @note    This function blocks until the Flash has processed the command and it will be repeated if,
 *          for any reason, the command was not successfully executed by the Flash.
 **********************************************************************************************************************/
static void r_qspi_w_flash_write_enable (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                 channel       = p_inst_extend->channel;

    uint8_t status;
    uint8_t opcode = p_inst_extend->p_qspi_flash_cfg->p_write_enable_instr_cfg->opcode;

    /* Wait till the Write enable bit in the flash device status register is set. */
    do
    {
        r_qspi_w_flash_cmd(channel, opcode);

        /* Wait till the WIP(Write in progress bit) in the flash device status register is cleared. */
        do
        {
            status = r_qspi_w_read_status_register(p_instance_ctrl);
        } while (status & (1U << p_instance_ctrl->p_cfg->write_status_bit));
    } while (!(status & (1U << p_instance_ctrl->p_cfg->write_enable_bit)));
}

/*******************************************************************************************************************//**
 * Check if the device is busy.
 *
 * @param[in] p_instance_ctrl    Pointer to a driver handle.
 *
 * @return    bool               True if the BUSY bit is set else false.
 *
 * @warning This function checks the value of the BUSY bit in the Status Register 1 of the Flash. It
 *          is the responsibility of the caller to call the function in the right context. The
 *          function must be called with interrupts disabled.
 **********************************************************************************************************************/
static bool r_qspi_w_flash_is_busy (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    uint8_t status_reg = r_qspi_w_read_status_register(p_instance_ctrl);
    bool    status_wip = (status_reg >> p_instance_ctrl->p_cfg->write_status_bit) & 1;

    return status_wip;
}

/*******************************************************************************************************************//**
 * Set an extra byte to use with read instructions, used to enter/stay/exit XiP mode.
 *
 * @param[in] channel       QSPI controller id.
 * @param[in] extra_byte    An extra byte transferred after the address asking memory to
 *                          stay in XiP mode or wait for a normal instruction
 *                          after CS goes inactive.
 * @param[in] p_qspi_cfg    Pointer to configuration structure of the read instruction.
 **********************************************************************************************************************/
static void r_qspi_w_set_extra_byte (uint8_t channel, uint8_t extra_byte, qspi_w_read_instr_cfg_t const * p_qspi_cfg)
{
    QSPI_REG(channel)->QSPIC_BURSTCMDA_REG = (QSPI_REG(channel)->QSPIC_BURSTCMDA_REG &
                                              ~(FSP_REG_MSK(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_EXT_BYTE) |
                                                FSP_REG_MSK(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_EXT_TX_MD))) |
                                             FSP_REG_FIELD_SET_BITS32(QSPIC,
                                                                      QSPIC_BURSTCMDA_REG,
                                                                      QSPIC_EXT_BYTE,
                                                                      extra_byte) |
                                             FSP_REG_FIELD_SET_BITS32(QSPIC,
                                                                      QSPIC_BURSTCMDA_REG,
                                                                      QSPIC_EXT_TX_MD,
                                                                      p_qspi_cfg->extra_byte_bus_mode);

    QSPI_REG(channel)->QSPIC_BURSTCMDB_REG = (QSPI_REG(channel)->QSPIC_BURSTCMDB_REG &
                                              ~(FSP_REG_MSK(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_EXT_BYTE_EN) |
                                                FSP_REG_MSK(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_EXT_HF_DS))) |
                                             FSP_REG_FIELD_SET_BITS32(QSPIC,
                                                                      QSPIC_BURSTCMDB_REG,
                                                                      QSPIC_EXT_BYTE_EN,
                                                                      p_qspi_cfg->extra_byte_en) |
                                             FSP_REG_FIELD_SET_BITS32(QSPIC,
                                                                      QSPIC_BURSTCMDB_REG,
                                                                      QSPIC_EXT_HF_DS,
                                                                      p_qspi_cfg->extra_byte_half_cfg);
}

/*******************************************************************************************************************//**
 * Initialize the read instruction of the QSPIC.
 *
 * @param[in] channel             QSPI controller id.
 * @param[in] p_read_instr_cfg    Pointer to configuration structure of the read instruction.
 **********************************************************************************************************************/
static void r_qspi_w_read_instr_init (uint8_t channel, const qspi_w_read_instr_cfg_t * p_read_instr_cfg)
{
    uint32_t burstcmda_reg = QSPI_REG(channel)->QSPIC_BURSTCMDA_REG;
    uint32_t burstcmdb_reg = QSPI_REG(channel)->QSPIC_BURSTCMDB_REG;

    /* QSPIC_BURSTCMDA_REG. */
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_INST, burstcmda_reg, p_read_instr_cfg->opcode);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_INST_WB, burstcmda_reg, p_read_instr_cfg->opcode_wb);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_EXT_BYTE, burstcmda_reg,
                          p_read_instr_cfg->extra_byte_value);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_INST_TX_MD, burstcmda_reg,
                          p_read_instr_cfg->opcode_bus_mode);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_ADR_TX_MD, burstcmda_reg, p_read_instr_cfg->addr_bus_mode);
    FSP_REG_VAR_FIELD_SET(QSPIC,
                          QSPIC_BURSTCMDA_REG,
                          QSPIC_EXT_TX_MD,
                          burstcmda_reg,
                          p_read_instr_cfg->extra_byte_bus_mode);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_DMY_TX_MD, burstcmda_reg, p_read_instr_cfg->dummy_bus_mode);

    /* QSPIC_BURSTCMDB_REG. */
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_DAT_RX_MD, burstcmdb_reg, p_read_instr_cfg->data_bus_mode);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_EXT_BYTE_EN, burstcmdb_reg,
                          p_read_instr_cfg->extra_byte_en);
    FSP_REG_VAR_FIELD_SET(QSPIC,
                          QSPIC_BURSTCMDB_REG,
                          QSPIC_EXT_HF_DS,
                          burstcmdb_reg,
                          p_read_instr_cfg->extra_byte_half_cfg);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_INST_MD, burstcmdb_reg, p_read_instr_cfg->instr_md);
#if !defined(BSP_MCU_GROUP_RA6W1)
    FSP_REG_VAR_FIELD_SET(QSPIC,
                          QSPIC_BURSTCMDB_REG,
                          QSPIC_DMY_NUM,
                          burstcmdb_reg,
                          (0 ==
                           p_read_instr_cfg->dummy_bytes) ? p_read_instr_cfg->dummy_bytes : p_read_instr_cfg->dummy_bytes -
                          1);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_DMY_EN, burstcmdb_reg, p_read_instr_cfg->dummy_en);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_WRAP_BLEN, burstcmdb_reg, p_read_instr_cfg->wrap_blen);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_WRAP_WR_EN, burstcmdb_reg, p_read_instr_cfg->wrap_wr_en);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_RD_BEND_MD, burstcmdb_reg, p_read_instr_cfg->rd_bend_md);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_RD_RDB_EN, burstcmdb_reg, p_read_instr_cfg->rd_rdb_en);
#else
    FSP_REG_VAR_FIELD_SET(QSPIC,
                          QSPIC_BURSTCMDB_REG,
                          QSPIC_DMY_NUM,
                          burstcmdb_reg,
                          (4U <= p_read_instr_cfg->dummy_bytes) ? 3U : p_read_instr_cfg->dummy_bytes);
#endif
    FSP_REG_VAR_FIELD_SET(QSPIC,
                          QSPIC_BURSTCMDB_REG,
                          QSPIC_CS_HIGH_MIN,
                          burstcmdb_reg,
                          p_read_instr_cfg->cs_high_min_cycles);
    FSP_REG_VAR_FIELD_SET(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_WRAP_MD, burstcmdb_reg, p_read_instr_cfg->wrap_md);

    QSPI_REG(channel)->QSPIC_BURSTCMDA_REG = burstcmda_reg;
    QSPI_REG(channel)->QSPIC_BURSTCMDB_REG = burstcmdb_reg;
}

/*******************************************************************************************************************//**
 * Write an arbitrary number of bytes to the Flash and then read an arbitrary number of bytes
 * from the Flash in one transaction.
 *
 * @param[in]  p_inst_extend    Pointer to a driver extended handle.
 * @param[in]  p_wbuf           Pointer to the beginning of the buffer that contains the data to be written.
 * @param[in]  wlen             The number of bytes to be written.
 * @param[out] p_rbuf           Pointer to the beginning of the buffer that the read data are stored.
 * @param[in]  rlen             The number of bytes to be read.
 *
 * @note The data are transferred as bytes (8 bits wide). No optimization is done in trying to use
 *       faster access methods (i.e. transfer words instead of bytes whenever it is possible).
 **********************************************************************************************************************/
static void r_qspi_w_transact (qspi_w_extended_cfg_t * p_inst_extend,
                               const uint8_t         * p_wbuf,
                               uint32_t                wlen,
                               uint8_t               * p_rbuf,
                               uint32_t                rlen)
{
    uint8_t channel = p_inst_extend->channel;

    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_EN_CS_Msk;

    for (uint32_t i = 0; i < wlen; ++i)
    {
        r_qspi_w_write8(channel, p_wbuf[i]);
    }

    for (uint32_t i = 0; i < rlen; ++i)
    {
        p_rbuf[i] = r_qspi_w_read8(channel);
    }

    QSPI_REG(channel)->QSPIC_CTRLBUS_REG = QSPIC_QSPIC_CTRLBUS_REG_QSPIC_DIS_CS_Msk;
}

/*******************************************************************************************************************//**
 * Read the Status Register of the Flash.
 *
 * @param[in]  p_instance_ctrl    Pointer to a driver handle.
 *
 * @return     uint8_t            The value of the Status Register of the Flash.
 **********************************************************************************************************************/
static uint8_t r_qspi_w_read_status_register (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint8_t status;
    uint8_t cmd[] = {p_instance_ctrl->p_cfg->status_command};

    r_qspi_w_transact(p_inst_extend, cmd, 1, &status, 1);

    return status;
}

#if QSPI_W_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Ensures that the parameters are valid and also that there is no write or erase operation inprogress.
 *
 * @param[in]  p_instance_ctrl     Pointer to a driver handle.
 *
 * @retval FSP_SUCCESS             Parameters are valid.
 * @retval FSP_ERR_ASSERTION       A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 * @retval FSP_ERR_DEVICE_BUSY     The device is busy.
 * @retval FSP_ERR_INVALID_MODE    This function can't be called when XiP mode is enabled.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_w_param_checking_dcom (qspi_w_instance_ctrl_t * p_instance_ctrl)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_W_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Do not enter direct communication mode from XiP mode. */
    qspi_w_extended_cfg_t * p_inst_extend = (qspi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    FSP_ERROR_RETURN(false == p_instance_ctrl->xip_mode_is_enabled, FSP_ERR_INVALID_MODE);

    /* Verify device is not busy. */
    if (!p_inst_extend->p_qspi_flash_cfg->is_ram)
    {
        FSP_ERROR_RETURN(r_qspi_w_flash_is_writable(p_instance_ctrl), FSP_ERR_DEVICE_BUSY);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter checking for R_QSPI_W_Write.
 *
 * @param[in] p_instance_ctrl      Pointer to a driver handle.
 * @param[in] p_src                The source of the data to write to QSPI_W.
 * @param[in] p_dest               The address in QSPI_W to write to.
 * @param[in] byte_count           The number of bytes to write.
 *
 * @retval FSP_SUCCESS             Parameters are valid.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl,p_src or p_dest is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE    This function can't be called when XiP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY     The device is busy.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_w_program_param_check (qspi_w_instance_ctrl_t * p_instance_ctrl,
                                               uint8_t const * const    p_src,
                                               uint8_t * const          p_dest,
                                               uint32_t                 byte_count)
{
    fsp_err_t err = r_qspi_w_param_checking_dcom(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);

    /* Check if byte_count is valid. */
    uint32_t page_size_bytes    = p_instance_ctrl->p_cfg->page_size_bytes;
    uint32_t bytes_left_in_page = page_size_bytes - ((uint32_t) p_dest % page_size_bytes);
    FSP_ASSERT(byte_count > 0);
    FSP_ASSERT(byte_count <= bytes_left_in_page);

    return FSP_SUCCESS;
}

#endif

#if defined(BSP_MCU_GROUP_RA6W1)

/*******************************************************************************************************************//**
 * Enables the dCache Controller.
 **********************************************************************************************************************/
static void r_qspi_w_dcache_enable (void)
{
    DCACHE->DCACHE_CTRL_REG_b.DCACHE_ENABLE = 1U;
}

/*******************************************************************************************************************//**
 * Disables the dCache Controller.
 *
 * @retval  FSP_SUCCESS        dCache disabling successfully.
 * @retval  FSP_ERR_TIMEOUT    dCache disabling timeout.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_w_dcache_disable (void)
{
    uint32_t timeout = QSPI_W_PRV_TIMEOUT_US;

    if (1U == DCACHE->DCACHE_CTRL_REG_b.DCACHE_ENABLE)
    {
        DCACHE->DCACHE_CTRL_REG_b.DCACHE_WFLUSH = 1U;

        /* Wait until the write flushing process is complete. */
        while (1U != DCACHE->DCACHE_CTRL_REG_b.DCACHE_WFLUSHED)
        {
            R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
            timeout--;
            FSP_ERROR_RETURN(0U < timeout, FSP_ERR_TIMEOUT);
        }

        /* Clear the completion indication to be ready for the next invocation */
        DCACHE->DCACHE_CTRL_REG_b.DCACHE_WFLUSHED = 0U;
        DCACHE->DCACHE_CTRL_REG_b.DCACHE_ENABLE   = 0U;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the dCache Controller.
 *
 * @retval  FSP_SUCCESS        dCache initializing successfully.
 * @retval  FSP_ERR_TIMEOUT    dCache initializing timeout.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_w_dcache_init (void)
{
    uint32_t timeout = QSPI_W_PRV_TIMEOUT_US;

    /* initialization of cache. */
    DCACHE->DCACHE_CTRL_REG_b.DCACHE_INIT = 1U;

    while (1U != DCACHE->DCACHE_CTRL_REG_b.DCACHE_READY)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;
        FSP_ERROR_RETURN(0U < timeout, FSP_ERR_TIMEOUT);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the target data memory cacheable area length and jointly the operational mode.
 *
 * @param[in]  len             The cacheable area length
 *
 * @retval  FSP_SUCCESS        Cachable length setting successfully.
 * @retval  FSP_ERR_TIMEOUT    Cachable length setting timeout.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_w_dcache_set_cacheable_len (uint32_t len)
{
    uint32_t timeout = QSPI_W_PRV_TIMEOUT_US;

    /* set cacheable length process. */
    if ((0U < DCACHE->DCACHE_CTRL_REG_b.DCACHE_LEN) && (0U == len))
    {
        DCACHE->DCACHE_CTRL_REG_b.DCACHE_WFLUSH = 1U;

        /* Wait until the write flushing process is complete. */
        while (1U != DCACHE->DCACHE_CTRL_REG_b.DCACHE_WFLUSHED)
        {
            R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
            timeout--;
            FSP_ERROR_RETURN(0U < timeout, FSP_ERR_TIMEOUT);
        }

        /* Clear the completion indication to be ready for the next invocation. */
        DCACHE->DCACHE_CTRL_REG_b.DCACHE_WFLUSHED = 0U;
    }

    DCACHE->DCACHE_CTRL_REG_b.DCACHE_LEN = len & 0x3FFFFU;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the base address of the cacheable area for the target data memory.
 **********************************************************************************************************************/
static void r_qspi_w_dcache_set_cacheable_base (void)
{
    DCACHE->DCACHE_BASE_ADDR_REG_b.DCACHE_BASE_ADDR = 0U;
}

#endif
