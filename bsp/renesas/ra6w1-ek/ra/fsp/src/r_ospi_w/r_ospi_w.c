/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ospi_w.h"

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM static void r_ospi_w_wait_while_busy(void);
BSP_PLACE_CODE_IN_RAM static void r_ospi_w_write_enable(void);
BSP_PLACE_CODE_IN_RAM void        ospi_w_set_bus_mode(ospi_w_device_bus_mode bus_mode);
BSP_PLACE_CODE_IN_RAM void        ospi_w_flash_sector_erase(uint8_t                 se_cmd,
                                                            ospi_w_device_addr_size mode,
                                                            uint32_t                addr);
BSP_PLACE_CODE_IN_RAM static uint32_t r_ospi_w_flash_write_page(spi_flash_ctrl_t * const p_ctrl,
                                                                uint32_t                 addr,
                                                                const uint8_t          * buf,
                                                                uint32_t                 size);
BSP_PLACE_CODE_IN_RAM static uint32_t r_ospi_w_flash_write_page_safe(spi_flash_ctrl_t * const p_ctrl,
                                                                     uint32_t                 addr,
                                                                     const uint8_t          * buf,
                                                                     uint32_t                 size);
BSP_PLACE_CODE_IN_RAM uint8_t r_ospi_flash_read_register(uint8_t                cmd,
                                                         uint8_t                mask,
                                                         ospi_w_device_bus_mode bus_mode);
BSP_PLACE_CODE_IN_RAM bool r_ospi_flash_is_busy(spi_flash_ctrl_t * const p_ctrl);
BSP_PLACE_CODE_IN_RAM void r_ospi_w_memcpy(void * dest, const void * src, size_t count);

void r_ospi_w_flash_rd_buf(uint8_t * rd_buf, size_t rd_buf_size);
void r_ospi_w_flash_cfg_read(uint8_t rd_cmd, uint32_t address);
void r_ospi_w_reset();

spi_flash_api_t g_ospi_w_on_spi_flash =
{
    .open           = R_OSPI_W_Open,
    .directWrite    = R_OSPI_W_DirectWrite,
    .directRead     = R_OSPI_W_DirectRead,
    .directTransfer = R_OSPI_W_DirectTransfer,
    .spiProtocolSet = R_OSPI_W_SpiProtocolSet,
    .write          = R_OSPI_W_Write,
    .erase          = R_OSPI_W_Erase,
    .statusGet      = R_OSPI_W_StatusGet,
    .xipEnter       = R_OSPI_W_XipEnter,
    .xipExit        = R_OSPI_W_XipExit,
    .bankSet        = R_OSPI_W_BankSet,
    .autoCalibrate  = R_OSPI_W_AutoCalibrate,
    .close          = R_OSPI_W_Close,
};

/*******************************************************************************************************************//**
 * Open the OSPI driver module. After the driver is open, the OSPI can be accessed like internal flash memory.
 *
 * Implements @ref spi_flash_api_t::open.
 *
 * Example:
 * @snippet r_ospi_w_example.c R_OSPI_W_Open
 *
 * @retval FSP_SUCCESS              Configuration was successful.
 * @retval FSP_ERR_ASSERTION        The parameter p_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_ALREADY_OPEN     Driver has already been opened with the same p_ctrl.
 * @retval FSP_ERR_INVALID_ARGUMENT Attempting to open the driver with an invalid SPI protocol for OctaRAM.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_Open (spi_flash_ctrl_t * const p_ctrl, spi_flash_cfg_t const * const p_cfg)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;

    // ospi_w_device_config_t * p_ospi_config;

#if OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
#endif

    ospi_w_extended_cfg_t * p_cfg_extend = (ospi_w_extended_cfg_t *) p_cfg->p_extend;
    FSP_CRITICAL_SECTION_DEFINE;

    /* Initialize control block. */
    p_instance_ctrl->p_cfg        = p_cfg;
    p_instance_ctrl->channel      = p_cfg_extend->channel;
    p_instance_ctrl->p_cmd_set    = p_cfg_extend->p_xspi_command_set_list;
    p_instance_ctrl->spi_protocol = p_cfg->spi_protocol;

    if (p_cfg_extend == NULL)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if (p_cfg_extend->p_ospi_w_device_cfg != NULL)
    {
        r_ospi_w_device_init(p_cfg_extend->p_ospi_w_device_cfg);
    }

    if (p_instance_ctrl->open == 0)
    {
        FSP_CRITICAL_SECTION_ENTER;
        r_ospi_w_device_set_access_mode(OSPI_W_DEVICE_ACCESS_MODE_MANUAL);
        if ((p_cfg_extend->p_read_instr_cfg != NULL) && (p_cfg_extend->p_read_instr_cfg->enable))
        {
            r_ospi_w_device_read_instr_init(p_cfg_extend->p_read_instr_cfg);

            /* settings for automode erase */
            if (p_cfg_extend->p_read_instr_cfg->instr_mode == OSPI_W_DEVICE_INSTR_MODE_SEND_ONCE)
            {
                OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_WRD   = 0xffff;
                OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_SZ    = 3; // 4byte
                OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_TX_MD = OSPI_W_DEVICE_BUS_MODE_SINGLE;
                OQSPIF->OQSPIF_BURSTBRK_REG_b.OSPIC_BRK_EN    = 1;
            }
        }

        if ((p_cfg_extend->p_wrap_burst_instr_cfg != NULL) && (p_cfg_extend->p_wrap_burst_instr_cfg->enable))
        {
            r_ospi_w_device_wrap_burst_instr_init(p_cfg_extend->p_wrap_burst_instr_cfg);
        }

        if ((p_cfg_extend->p_erase_instr_cfg != NULL) && (p_cfg_extend->p_erase_instr_cfg->enable))
        {
            r_ospi_w_device_erase_instr_init(p_cfg_extend->p_erase_instr_cfg);
        }

        if ((p_cfg_extend->p_read_status_instr_cfg != NULL) && (p_cfg_extend->p_read_status_instr_cfg->enable))
        {
            r_ospi_w_device_read_status_instr_init(p_cfg_extend->p_read_status_instr_cfg);
        }

        if ((p_cfg_extend->p_write_enable_instr_cfg != NULL) && (p_cfg_extend->p_write_enable_instr_cfg->enable))
        {
            r_ospi_w_device_write_enable_instr_init(p_cfg_extend->p_write_enable_instr_cfg);
        }

        if ((p_cfg_extend->p_suspend_resume_instr_cfg != NULL) && (p_cfg_extend->p_suspend_resume_instr_cfg->enable))
        {
            r_ospi_w_device_suspend_resume_instr_init(p_cfg_extend->p_suspend_resume_instr_cfg);
        }

        CRG_TOP->SYS_CTRL_REG_b.CACHERAM_MUX = 0;
        do
        {
            OQSPIF->OQSPIF_CTRLMODE_REG_b.OSPIC_AUTO_MD = 0; // switch off and on automode in order to trigger re-sending the read command.
            OQSPIF->OQSPIF_CTRLMODE_REG_b.OSPIC_AUTO_MD = 1;

            if ((*(volatile uint32_t *) 0x0a000000 & 0x0000FFFF) == 0x00007050)
            {
                break;                 // if "Pp" was found, we assume the flash is ready to be used in automode.
            }
        } while (1);

        CRG_TOP->SYS_CTRL_REG_b.CACHERAM_MUX = 1;
        FSP_CRITICAL_SECTION_EXIT;
    }

    p_instance_ctrl->open++;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close the OSPI driver module.
 *
 * Implements @ref spi_flash_api_t::close.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_Close (spi_flash_ctrl_t * const p_ctrl)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;

    if (p_instance_ctrl->open == 0)
    {
        return FSP_ERR_NOT_OPEN;
    }

    p_instance_ctrl->open--;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes raw data directly to the OctaFlash. API not supported. Use R_OSPI_W_DirectTransfer
 *
 * Implements @ref spi_flash_api_t::directWrite.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_DirectWrite (spi_flash_ctrl_t * const p_ctrl,
                                                      uint8_t const * const    p_src,
                                                      uint32_t const           bytes,
                                                      bool const               read_after_write)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(bytes);
    FSP_PARAMETER_NOT_USED(read_after_write);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Reads raw data directly from the OctaFlash. API not supported. Use R_OSPI_W_DirectTransfer.
 *
 * Implements @ref spi_flash_api_t::directRead.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_DirectRead (spi_flash_ctrl_t * const p_ctrl,
                                                     uint8_t * const          p_dest,
                                                     uint32_t const           bytes)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(bytes);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Read/Write raw data directly with the OctaFlash.
 *
 * Implements @ref spi_flash_api_t::directTransfer.
 *
 * Example:
 * @snippet r_ospi_w_example.c OSPI_W_Read_chip_ID
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    The parameters are wrong.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_DirectTransfer (spi_flash_ctrl_t * const            p_ctrl,
                                                         spi_flash_direct_transfer_t * const p_transfer,
                                                         spi_flash_direct_transfer_dir_t     direction)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;
    uint8_t                 read_cmd         = (uint8_t) p_transfer->command;
    uint8_t                 pp_cmd           = (uint8_t) p_transfer->command;
    uint32_t                addr             = p_transfer->address;
    uint8_t                 addr_len         = p_transfer->address_length;
    uint8_t               * buf_rd           = (uint8_t *) (&(p_transfer->data));
    uint8_t               * buf              = (uint8_t *) (&(p_transfer->data));
    uint32_t                bytes            = p_transfer->data_length;
    uint32_t                automode_backup  = 0;
    ospi_w_extended_cfg_t * p_extended       = (ospi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (!(p_instance_ctrl->open))
    {
        return FSP_ERR_NOT_OPEN;
    }

    if (bytes > 8)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if (direction == SPI_FLASH_DIRECT_TRANSFER_DIR_READ)
    {
        /* Check now in automode */
        if (r_ospi_w_device_get_access_mode() == OSPI_W_DEVICE_ACCESS_MODE_AUTO)
        {
            memcpy((void *) buf_rd, (void *) (addr | OSPI_W_AUTOMODE_BASE_ADD), bytes);
        }
        else
        {
            r_ospi_w_device_cs_enable();
            r_ospi_w_device_write8(read_cmd);
            if (p_extended->p_ospi_w_device_cfg->automode_config.instruct_size == OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES)
            {
                r_ospi_w_device_write8(~read_cmd);
            }

            if (addr_len == SPI_FLASH_ADDRESS_BYTES_4)
            {
                r_ospi_w_device_write32(addr);
            }
            else if (addr_len == SPI_FLASH_ADDRESS_BYTES_3)
            {
                r_ospi_w_device_write8((uint8_t) (addr >> 16));
                r_ospi_w_device_write8((uint8_t) (addr >> 8));
                r_ospi_w_device_write8((uint8_t) (addr >> 0));
            }
            else
            {
                /* special case such like READ ID */
            }

            if ((read_cmd == OSPI_FAST_READ3B_CMD) || (read_cmd == OSPI_FAST_READ4B_CMD))
            {
                r_ospi_w_device_dummy8();
            }

            /* Send dummy cycle */
            if (p_transfer->dummy_cycles)
            {
                for (uint32_t dummy_cnt = 0; dummy_cnt < (p_transfer->dummy_cycles); dummy_cnt++)
                {
                    r_ospi_w_device_dummy8();
                }
            }

            for (uint32_t i = 0; i < bytes; ++i)
            {
                buf_rd[i] = r_ospi_w_device_read8();
            }

            r_ospi_w_device_cs_disable();
        }
    }
    else if (direction == SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE)
    {
        if (r_ospi_w_device_get_access_mode() == OSPI_W_DEVICE_ACCESS_MODE_AUTO)
        {
            /* turn off auto mode first */
            automode_backup = 1;
            r_ospi_w_device_set_access_mode(OSPI_W_DEVICE_ACCESS_MODE_MANUAL);
        }

        r_ospi_w_write_enable();
        r_ospi_w_device_cs_enable();
        r_ospi_w_device_write8((uint8_t) pp_cmd);
        if (addr_len == SPI_FLASH_ADDRESS_BYTES_4)
        {
            r_ospi_w_device_write32(addr);
        }
        else
        {
            r_ospi_w_device_write8((uint8_t) (addr >> 16));
            r_ospi_w_device_write8((uint8_t) (addr >> 8));
            r_ospi_w_device_write8((uint8_t) (addr >> 0));
        }

        for (uint32_t i = 0; i < bytes; ++i)
        {
            r_ospi_w_device_write8(buf[i]);
        }

        r_ospi_w_device_cs_disable();

        r_ospi_w_wait_while_busy();
        if (automode_backup)
        {
            r_ospi_w_device_set_access_mode(OSPI_W_DEVICE_ACCESS_MODE_AUTO);
        }
    }
    else
    {
        return FSP_ERR_INVALID_DATA;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the SPI protocol.
 *
 * Implements @ref spi_flash_api_t::spiProtocolSet.
 *
 * @retval FSP_ERR_UNSUPPORTED        API not supported by OSPI. Once the RA6W1/RA6W2 is running, it already be in automode by Booter.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_SpiProtocolSet (spi_flash_ctrl_t * const p_ctrl,
                                                         spi_flash_protocol_t     spi_protocol)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(spi_protocol);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Enters XIP (execute in place) mode.
 * @note It need to enable the interrupt if it is disabled before.
 *
 * Implements @ref spi_flash_api_t::xipEnter.
 *
 * @retval FSP_SUCCESS                 XiP mode was entered successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         XiP support is not enabled.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_XipEnter (spi_flash_ctrl_t * const p_ctrl)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;

    ospi_w_device_bus_mode bus_mode = OSPI_W_DEVICE_BUS_MODE_QUAD;

    if (!(p_instance_ctrl->open))
    {
        return FSP_ERR_NOT_OPEN;
    }

    switch (p_instance_ctrl->p_cmd_set->protocol)
    {
        case SPI_FLASH_PROTOCOL_1S_1S_1S:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE;
            break;
        }

        case SPI_FLASH_PROTOCOL_1S_4S_4S:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_QUAD;
            break;
        }

        case SPI_FLASH_PROTOCOL_8D_8D_8D:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_OCTA;
            break;
        }

        default:
        {
            return FSP_ERR_INVALID_MODE;
            break;
        }
    }

    ospi_w_set_bus_mode(bus_mode);

    r_ospi_w_device_set_access_mode(OSPI_W_DEVICE_ACCESS_MODE_AUTO);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Exits XIP (execute in place) mode.
 * @note Once R_OSPI_W_XipExit called, it cannot excute the ISR code on the flash.
 *       So, it need to disable all interrupt right before this function.
 *
 * Implements @ref spi_flash_api_t::xipExit.
 *
 * @retval FSP_SUCCESS                 XiP mode was entered successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         XiP support is not enabled.
 * @retval FSP_ERR_INVALID_MODE        Unsupport flash mode.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_XipExit (spi_flash_ctrl_t * const p_ctrl)
{
    uint8_t exit_continuous_seq_bytes        = 4;
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;

    ospi_w_extended_cfg_t * p_cfg_extend = (ospi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (!(p_instance_ctrl->open))
    {
        return FSP_ERR_NOT_OPEN;
    }

    /* Turn off auto mode to allow command entry mode */
    r_ospi_w_device_set_access_mode(OSPI_W_DEVICE_ACCESS_MODE_MANUAL);

    if (p_cfg_extend->p_read_instr_cfg->instr_mode == OSPI_W_DEVICE_INSTR_MODE_SEND_ONCE)
    {
        r_ospi_w_device_cs_enable();
        for (uint8_t i = 0; i < exit_continuous_seq_bytes; ++i)
        {
            r_ospi_w_device_write8(OSPI_EXIT_CONTINUOUS_MODE_CMD);
        }

        r_ospi_w_device_cs_disable();
    }

    ospi_w_set_bus_mode(p_cfg_extend->p_read_instr_cfg->instr_bus_mode);

    return FSP_SUCCESS;
}

BSP_PLACE_CODE_IN_RAM void r_ospi_w_memcpy (void * dest, const void * src, size_t count)
{
    char       * tmp = dest;
    const char * s   = src;

    while (count--)
    {
        *tmp++ = *s++;
    }
}

/*******************************************************************************************************************//**
 * Program a page of data to the flash.
 *
 * Implements @ref spi_flash_api_t::write.
 *
 * Example:
 * @snippet r_ospi_w_example.c OSPI_W_Write
 *  *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl, p_dest or p_src is NULL, or byte_count crosses a page boundary.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_SIZE        Insufficient space remaining in page or write length is not a multiple of CPU access size when not using the DMAC.
 * @retval FSP_ERR_DEVICE_BUSY         Another Write/Erase transaction is in progress.
 * @retval FSP_ERR_WRITE_FAILED        Write operation failed.
 * @retval FSP_ERR_INVALID_ADDRESS     Destination or source is not aligned to CPU access alignment when not using the DMAC.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_Write (spi_flash_ctrl_t * const p_ctrl,
                                                uint8_t const * const    p_src,
                                                uint8_t * const          p_dest,
                                                uint32_t                 byte_count)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;
    uint32_t                 addr            = (uint32_t) p_dest;
    uint8_t  buf[ON_STACK_BUFFER_SIZE];
    uint32_t size     = byte_count;
    uint32_t offset   = 0;
    uint32_t automode = 0;

    FSP_CRITICAL_SECTION_DEFINE;

    if (!(p_instance_ctrl->open))
    {
        return FSP_ERR_NOT_OPEN;
    }

    if (p_instance_ctrl->p_cfg->page_size_bytes > ON_STACK_BUFFER_SIZE)
    {
        return FSP_ERR_INVALID_SIZE;
    }

    /* set address to physical address */
    addr &= 0xFFFFFF;

    FSP_CRITICAL_SECTION_ENTER;
    if (r_ospi_w_device_get_access_mode() != OSPI_W_DEVICE_ACCESS_MODE_MANUAL)
    {
        // for convenience it call xip exit.
        R_OSPI_W_XipExit(p_ctrl);
        automode = 1;
    }

    while (offset < size)
    {
        size_t chunk = sizeof(buf) > size - offset ? size - offset : sizeof(buf);
        r_ospi_w_memcpy(buf, p_src + offset, chunk);

        size_t written = r_ospi_w_flash_write_page_safe(p_ctrl, addr + offset, buf, chunk);
        offset += written;
    }

    if (automode)
    {
        R_OSPI_W_XipEnter(p_ctrl);
    }

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erase a block or sector of flash.  The byte_count must exactly match one of the erase sizes defined in spi_flash_cfg_t.
 * For chip erase, byte_count must be SPI_FLASH_ERASE_SIZE_CHIP_ERASE.
 * If it was opened with auto-erase configuration, it could be called without XIP_Exit() function.
 * Implements @ref spi_flash_api_t::erase.
 *
 * Example:
 * @snippet r_ospi_w_example.c OSPI_W_Erase
 * @snippet r_ospi_w_example.c OSPI_W_Erase_Auto
 *
 * @retval FSP_SUCCESS                 The command to erase the flash was executed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_device_address is NULL, byte_count doesn't match an erase
 *                                     size defined in spi_flash_cfg_t, or byte_count is set to 0.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 * @retval FSP_ERR_WRITE_FAILED        Write operation failed.
 * @retval FSP_ERR_INVALID_ARGUMENT    The parameters are wrong.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_Erase (spi_flash_ctrl_t * const p_ctrl,
                                                uint8_t * const          p_device_address,
                                                uint32_t                 byte_count)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;
    uint8_t                 se_cmd           = 0;
    uint32_t                addr             = (uint32_t) p_device_address;
    uint8_t                 addr_len         = p_instance_ctrl->p_cfg->address_bytes;
    ospi_w_device_addr_size mode;
    uint32_t                automode = 0;

    ospi_w_extended_cfg_t * p_cfg_extend = (ospi_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    FSP_CRITICAL_SECTION_DEFINE;

    mode = (addr_len == SPI_FLASH_ADDRESS_BYTES_3) ? OSPI_W_DEVICE_ADDR_SIZE_24 : OSPI_W_DEVICE_ADDR_SIZE_32;

    if (!(p_instance_ctrl->open))
    {
        return FSP_ERR_NOT_OPEN;
    }

    if (p_instance_ctrl->p_cfg->erase_command_list_length == 0)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    /* set address to physical address */
    addr &= 0xFFFFFF;

    /* filter out unsupport erase byte_count */
    if (byte_count < p_instance_ctrl->p_cfg->p_erase_command_list[0].size)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    for (uint32_t index = 0; index < p_instance_ctrl->p_cfg->erase_command_list_length; index++)
    {
        /* If requested byte_count is supported by underlying flash, store the command. */
        if (byte_count == p_instance_ctrl->p_cfg->p_erase_command_list[index].size)
        {
            se_cmd = (uint8_t) p_instance_ctrl->p_cfg->p_erase_command_list[index].command;
            break;
        }

        if (byte_count > p_instance_ctrl->p_cfg->p_erase_command_list[0].size)
        {
            if ((byte_count % p_instance_ctrl->p_cfg->p_erase_command_list[0].size) == 0)
            {
                se_cmd = (uint8_t) p_instance_ctrl->p_cfg->p_erase_command_list[0].command;
            }
        }
    }

#if OSPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(0U != se_cmd);
#endif
    if (se_cmd == 0)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    /* Try auto mode erase first */
    if (r_ospi_w_device_get_access_mode() == OSPI_W_DEVICE_ACCESS_MODE_AUTO)
    {
        if ((p_cfg_extend != NULL) && (p_cfg_extend->p_erase_instr_cfg != NULL) &&
            (p_cfg_extend->p_erase_instr_cfg->enable == 1))
        {
            uint32_t flash_offset;
            flash_offset = addr;

            while (flash_offset < addr + byte_count)
            {
                r_ospi_w_device_erase_block(flash_offset);
                while (r_ospi_w_device_get_erase_status() != OSPI_W_DEVICE_ERS_NO)
                {
                }

                flash_offset += OSPI_FLASH_SECTOR_LENGTH;
            }

            return FSP_SUCCESS;
        }
        else                           /* it does not support automode erase */
        {
            goto R_OSPI_W_ERASE_MANUAL;
        }
    }
    else                               /* Already xip exit called. */
    {
R_OSPI_W_ERASE_MANUAL:
        FSP_CRITICAL_SECTION_ENTER;
        if (r_ospi_w_device_get_access_mode() != OSPI_W_DEVICE_ACCESS_MODE_MANUAL)
        {
            // for convenience it call xip exit.
            R_OSPI_W_XipExit(p_ctrl);
            automode = 1;
        }

        if (se_cmd == p_instance_ctrl->p_cfg->p_erase_command_list[0].command)
        {
            if (byte_count > OSPI_FLASH_SECTOR_LENGTH)
            {
                uint32_t cnt = byte_count / OSPI_FLASH_SECTOR_LENGTH;
                cnt = cnt + ((byte_count & 0xFFF) ? 1 : 0);

                for (uint32_t i = 0; i < cnt; i++)
                {
                    ospi_w_flash_sector_erase(se_cmd, mode, addr + (i * OSPI_FLASH_SECTOR_LENGTH));
                }
            }
            else
            {
                ospi_w_flash_sector_erase(se_cmd, mode, addr);
            }
        }
        else
        {
            ospi_w_flash_sector_erase(se_cmd, mode, addr);
        }

        if (automode)
        {
            R_OSPI_W_XipEnter(p_ctrl);
        }

        FSP_CRITICAL_SECTION_EXIT;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets the write or erase status of the flash.
 *
 * Implements @ref spi_flash_api_t::statusGet.
 *
 * @retval FSP_SUCCESS                 The write status is in p_status.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_status is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_StatusGet (spi_flash_ctrl_t * const   p_ctrl,
                                                    spi_flash_status_t * const p_status)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;
    uint32_t                 automode        = 0;

    if (!(p_instance_ctrl->open))
    {
        return FSP_ERR_NOT_OPEN;
    }

    if (r_ospi_w_device_get_access_mode() != OSPI_W_DEVICE_ACCESS_MODE_MANUAL)
    {
        // for convenience it call xip exit.
        R_OSPI_W_XipExit(p_ctrl);
        automode = 1;
    }

    p_status->write_in_progress = r_ospi_flash_is_busy(p_ctrl);

    if (automode)
    {
        R_OSPI_W_XipEnter(p_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Selects the bank to access. Use ospi_w_bank_select_t as the bank value.
 *
 * Implements @ref spi_flash_api_t::bankSet.
 *
 * @retval FSP_ERR_UNSUPPORTED           This function is unsupported.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_BankSet (spi_flash_ctrl_t * const p_ctrl, uint32_t bank)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(bank);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * AutoCalibrate the OSPI_W DS signal.
 *
 * Implements @ref spi_flash_api_t::autoCalibrate.
 *
 * @retval FSP_ERR_UNSUPPORTED         Autocalibration support is not enabled.
 **********************************************************************************************************************/
BSP_PLACE_CODE_IN_RAM fsp_err_t R_OSPI_W_AutoCalibrate (spi_flash_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_init (const ospi_w_device_config_t * cfg)
{
#if ((dg_configCODE_LOCATION == NON_VOLATILE_IS_OCTA_FLASH) && (dg_configEXEC_MODE == MODE_IS_CACHED))
    FSP_ASSERT(REG_GETF(CACHE, CACHE_CTRL2_REG, CACHE_LEN) != 0 ||
               REG_GETF(CRG_TOP, SYS_CTRL_REG, CACHERAM_MUX) == 1)
#endif

    if (cfg)
    {
        r_ospi_w_device_set_div(cfg->clk_div);
        r_ospi_w_device_clock_enable();
        r_ospi_w_device_set_clock_mode(cfg->clock_mode);
        r_ospi_w_device_set_access_mode(cfg->access_mode);
        r_ospi_w_device_set_bus_mode(cfg->bus_mode);
        r_ospi_w_device_set_io2_direction(cfg->io2_dir);
        r_ospi_w_device_set_io3_direction(cfg->io3_dir);
        r_ospi_w_device_set_io4_7_direction(cfg->io4_7_dir);

        if (cfg->io2_dir == OSPI_W_DEVICE_IO_DIR_OUTPUT)
        {
            r_ospi_w_device_set_io2_value(cfg->io2_value);
        }

        if (cfg->io3_dir == OSPI_W_DEVICE_IO_DIR_OUTPUT)
        {
            r_ospi_w_device_set_io3_value(cfg->io3_value);
        }

        if (cfg->io4_7_dir == OSPI_W_DEVICE_IO_DIR_OUTPUT)
        {
            r_ospi_w_device_set_io4_7_value(cfg->io4_7_value);
        }

        r_ospi_w_device_set_hready_mode(cfg->hready_mode);
        r_ospi_w_device_set_read_sampling_edge(cfg->sampling_edge);
        r_ospi_w_device_set_read_pipe(cfg->read_pipe);
        r_ospi_w_device_set_read_pipe_clock_delay(cfg->read_pipe_delay);
        r_ospi_w_device_set_address_size(cfg->address_size);
        r_ospi_w_device_set_dummy_mode(cfg->dummy_mode);

        r_ospi_w_device_set_slew_rate(cfg->slew_rate);
        r_ospi_w_device_set_drive_current(cfg->drive_current);

        r_ospi_w_device_set_dir_change_mode(cfg->manualmode_config.dir_change_mode);
        r_ospi_w_device_set_mapped_addr_read_access_response(cfg->manualmode_config.mapped_addr_rd_acc_response);

        r_ospi_w_device_set_full_buffer_mode(cfg->automode_config.full_buffer_mode);
        r_ospi_w_device_set_instruction_size(cfg->automode_config.instruct_size);
        r_ospi_w_device_set_burst_len_limit(cfg->automode_config.burst_len_limit);
    }
}

static void r_ospi_w_device_flash_wr (uint8_t wr_data)
{
    *(volatile uint8_t *) &OQSPIF->OQSPIF_WRITEDATA_REG = wr_data; // QSPIC transmits 8 bits
    while (REG_GETF(OQSPIF, OQSPIF_STATUS_REG, OSPIC_BUSY) == 1)
    {
        ;
    }
}

static uint8_t r_ospi_w_device_flash_rd (void)
{
    uint8_t rd_data;
    __UNUSED volatile uint8_t dummy;

    dummy = *((volatile uint8_t *) &(OQSPIF->OQSPIF_READDATA_REG));

    while (REG_GETF(OQSPIF, OQSPIF_STATUS_REG, OSPIC_BUSY) == 1)
    {
        ;
    }

    rd_data = *((volatile uint8_t *) &(OQSPIF->OQSPIF_RECVDATA_REG));

    return rd_data;
}

void r_ospi_w_flash_rd_buf (uint8_t * rd_buf, size_t rd_buf_size)
{
    size_t i;
    for (i = 0; i < rd_buf_size; i++)
    {
        rd_buf[i] = r_ospi_w_device_flash_rd();
    }
}

void r_ospi_w_flash_cfg_read (uint8_t rd_cmd, uint32_t address)
{
    r_ospi_w_device_flash_wr((uint8_t) rd_cmd);       /* Write Read Opcode */
    r_ospi_w_device_flash_wr((address >> 16) & 0xff); /* addr2  */
    r_ospi_w_device_flash_wr((address >> 8) & 0xff);  /* addr1  */
    r_ospi_w_device_flash_wr(address & 0xff);         /* addr0  */
}

void r_ospi_w_reset ()
{
    volatile int i;

    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_AUTO_MD, 0);

    if (1)
    {
        OQSPIF->OQSPIF_CTRLBUS_REG = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_SINGLE_Msk;

        // First cs toggle to wake up MX devices
        r_ospi_w_device_cs_enable();
        for (i = 0; i < 800; i++)
        {
            __asm__ ("mov r0,r0");
        }

        r_ospi_w_device_cs_disable();
        for (i = 0; i < 800; i++)
        {
            __asm__ ("mov r0,r0");
        }

        // Wake up from the "Deep Power Down Mode" for other devices in single spi
        r_ospi_w_device_cs_enable();
        r_ospi_w_device_flash_wr(OSPI_W_EXIT_DPD_CMD);
        r_ospi_w_device_cs_disable();  // Leave CSn asserted for the next steps !
        for (i = 0; i < 400; i++)      // wait at least 30us to exit from the "Deep Power Down Mode"
        {
            __asm__ ("mov r0,r0");
        }

        // Wake up from the "Deep Power Down Mode" for other devices in QPI mode
        OQSPIF->OQSPIF_CTRLBUS_REG = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_QUAD_Msk;
        REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO2_OEN, 0);
        REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO3_OEN, 0);
        r_ospi_w_device_cs_enable();
        r_ospi_w_device_flash_wr(OSPI_W_EXIT_DPD_CMD);
        r_ospi_w_device_cs_disable();  // Leave CSn asserted for the next steps !
        for (i = 0; i < 400; i++)      // wait at least 30us to exit from the "Deep Power Down Mode"
        {
            __asm__ ("mov r0,r0");
        }

        // Wake up from the "Deep Power Down Mode" for other devices in OCTA mode
        OQSPIF->OQSPIF_CTRLBUS_REG = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_OCTAL_Msk;
        REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_OEN, 0);
        r_ospi_w_device_cs_enable();
        r_ospi_w_device_flash_wr(OSPI_W_EXIT_DPD_CMD);
        r_ospi_w_device_cs_disable();  // Leave CSn asserted for the next steps !
        for (i = 0; i < 400; i++)      // wait at least 30us to exit from the "Deep Power Down Mode"
        {
            __asm__ ("mov r0,r0");
        }

        r_ospi_w_device_cs_enable();
        r_ospi_w_device_flash_wr(OSPI_W_EXIT_DPD_CMD);
        r_ospi_w_device_flash_wr(OSPI_W_EXIT_DPD_CMD_INV);
        r_ospi_w_device_cs_disable();  // Leave CSn asserted for the next steps !
        for (i = 0; i < 400; i++)      // wait at least 30us to exit from the "Deep Power Down Mode"
        {
            __asm__ ("mov r0,r0");
        }
    }

    // First make sure the device exits continuous read mode by sending 5 dummy bytes in Quad mode
    OQSPIF->OQSPIF_CTRLBUS_REG = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_QUAD_Msk;
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO2_OEN, 0);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO3_OEN, 0);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_OEN, 1);
    r_ospi_w_device_cs_enable();
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_cs_disable();

    // First make sure the device exits continuous read mode by sending 5 dummy bytes in OCTA mode
    OQSPIF->OQSPIF_CTRLBUS_REG = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_OCTAL_Msk;
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_OEN, 0);
    r_ospi_w_device_cs_enable();
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_flash_wr(OSPI_W_DUMMY_CMD);
    r_ospi_w_device_cs_disable();

    // switch back to single mode
    OQSPIF->OQSPIF_CTRLBUS_REG  = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_SINGLE_Msk;
    OQSPIF->OQSPIF_CTRLMODE_REG = (OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_CLK_MD_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_RXD_NEG_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO3_DAT_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO2_DAT_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO_UH_DAT_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO3_OEN_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO2_OEN_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO_UH_OEN_Msk);

    // send reset in single SPI mode
    r_ospi_w_device_cs_enable();

    // Device reset in single mode
    r_ospi_w_device_flash_wr(OSPI_W_RESET_EN_CMD); // MX25U, W25Q16DW Reset Enable (MX)
    r_ospi_w_device_cs_toggle();
    r_ospi_w_device_flash_wr(OSPI_W_RESET_CMD);    // Reset Memory
    r_ospi_w_device_cs_disable();
    for (i = 0; i < 400; i++)                      // MX Read, Write recover time > 20 us = 77us@10MHz, 39us@20MHz
    {
        __asm__ ("mov r0,r0");
    }

    // Device reset in QPI mode
    OQSPIF->OQSPIF_CTRLBUS_REG = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_QUAD_Msk;
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO2_OEN, 0);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO3_OEN, 0);

    r_ospi_w_device_cs_enable();
    r_ospi_w_device_flash_wr(OSPI_W_RESET_EN_CMD); // MX25U, W25Q16DW Reset Enable (MX)
    r_ospi_w_device_cs_toggle();
    r_ospi_w_device_flash_wr(OSPI_W_RESET_CMD);    // Reset Memory
    r_ospi_w_device_cs_disable();
    for (i = 0; i < 400; i++)                      // MX Read, Write recover time > 20 us = 77us@10MHz, 39us@20MHz
    {
        __asm__ ("mov r0,r0");
    }

    // Device reset in OCTA mode double command mode
    OQSPIF->OQSPIF_CTRLBUS_REG = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_OCTAL_Msk;
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_IO_UH_OEN, 0);
    r_ospi_w_device_cs_enable();
    r_ospi_w_device_flash_wr(OSPI_W_RESET_EN_CMD); // MX25U, W25Q16DW Reset Enable (MX)
    r_ospi_w_device_flash_wr(OSPI_W_RESET_CMD);    // Reset Memory
    r_ospi_w_device_cs_toggle();
    r_ospi_w_device_flash_wr(OSPI_W_RESET_CMD);    // Reset Memory
    r_ospi_w_device_flash_wr(OSPI_W_RESET_EN_CMD); // MX25U, W25Q16DW Reset Enable (MX)
    r_ospi_w_device_cs_disable();
    for (i = 0; i < 400; i++)                      // MX Read, Write recover time > 20 us = 77us@10MHz, 39us@20MHz
    {
        __asm__ ("mov r0,r0");
    }

    // Device reset in OCTA mode single command mode
    r_ospi_w_device_cs_enable();
    r_ospi_w_device_flash_wr(OSPI_W_RESET_EN_CMD);
    r_ospi_w_device_cs_toggle();
    r_ospi_w_device_flash_wr(OSPI_W_RESET_EN_CMD);
    r_ospi_w_device_cs_disable();
    for (i = 0; i < 400; i++)          // MX Read, Write recover time > 20 us = 77us@10MHz, 39us@20MHz
    {
        __asm__ ("mov r0,r0");
    }

    OQSPIF->OQSPIF_CTRLBUS_REG  = OQSPIF_OQSPIF_CTRLBUS_REG_OSPIC_SET_SINGLE_Msk;
    OQSPIF->OQSPIF_CTRLMODE_REG = (OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_CLK_MD_Msk |

                                       // OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_RXD_NEG_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_RPIPE_EN_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO3_DAT_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO2_DAT_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO_UH_DAT_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO3_OEN_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO2_OEN_Msk |
                                   OQSPIF_OQSPIF_CTRLMODE_REG_OSPIC_IO_UH_OEN_Msk);

#ifdef FPGA_DEBUG
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_PCLK_MD, 7);
    REG_SETF(OQSPIF, OQSPIF_CTRLMODE_REG, OSPIC_RPIPE_EN, 1);
#endif
}

BSP_PLACE_CODE_IN_RAM void ospi_w_flash_sector_erase (uint8_t se_cmd, ospi_w_device_addr_size mode, uint32_t addr)
{
    r_ospi_w_wait_while_busy();

    r_ospi_w_write_enable();
    r_ospi_w_device_cs_enable();
    r_ospi_w_device_write8((uint8_t) se_cmd);
    if (r_ospi_w_device_get_instruction_size() == OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES)
    {
        r_ospi_w_device_write8(~se_cmd);
    }

    if (mode == OSPI_W_DEVICE_ADDR_SIZE_32)
    {
        r_ospi_w_device_write32(addr);
    }
    else
    {
        r_ospi_w_device_write8((uint8_t) (addr >> 16));
        r_ospi_w_device_write8((uint8_t) (addr >> 8));
        r_ospi_w_device_write8((uint8_t) (addr >> 0));
    }

    r_ospi_w_device_cs_disable();

    r_ospi_w_wait_while_busy();
}

BSP_PLACE_CODE_IN_RAM static void r_ospi_w_write_enable (void)
{
    r_ospi_w_device_cs_enable();
    r_ospi_w_device_write8(OSPI_WRITE_ENABLE_CMD);
    if (r_ospi_w_device_get_instruction_size() == OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES)
    {
        r_ospi_w_device_write8((uint8_t) ~OSPI_WRITE_ENABLE_CMD);
    }

    r_ospi_w_device_cs_disable();
}

BSP_PLACE_CODE_IN_RAM static void r_ospi_w_wait_while_busy (void)
{
    uint8_t dummy_cycle;
    r_ospi_w_device_cs_enable();
    r_ospi_w_device_write8(SPI_READ_STATUS_REG_CMD);
    if (r_ospi_w_device_get_instruction_size() == OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES)
    {
        r_ospi_w_device_write8((uint8_t) ~SPI_READ_STATUS_REG_CMD);
    }

    /* Send dummy bytes for octa flash */
    dummy_cycle = REG_GETF(OQSPIF, OQSPIF_STATUSCMD_REG, OSPIC_RSTAT_DMY_NUM);
    if (dummy_cycle > 0)
    {
        dummy_cycle += 1;
        for (uint8_t dummy = 0; dummy < dummy_cycle; dummy++)
        {
            r_ospi_w_device_dummy8();
        }
    }

    /* Busy bit in status register */
    while (r_ospi_w_device_read8() & 1)
    {
        ;
    }

    r_ospi_w_device_cs_disable();
}

BSP_PLACE_CODE_IN_RAM void ospi_w_set_bus_mode (ospi_w_device_bus_mode bus_mode)
{
    switch (bus_mode)
    {
        case OSPI_W_DEVICE_BUS_MODE_SINGLE:
        {
            r_ospi_w_device_set_io2_direction(OSPI_W_DEVICE_IO_DIR_OUTPUT);
            r_ospi_w_device_set_io2_value(OSPI_W_DEVICE_IO_VALUE_HIGH);
            r_ospi_w_device_set_io3_direction(OSPI_W_DEVICE_IO_DIR_OUTPUT);
            r_ospi_w_device_set_io3_value(OSPI_W_DEVICE_IO_VALUE_HIGH);
            break;
        }

        /* Octa mode needs one more settings from Quad mode. */
        case OSPI_W_DEVICE_BUS_MODE_OCTA:
        {
            r_ospi_w_device_set_io4_7_direction(OSPI_W_DEVICE_IO_DIR_AUTO_SEL);
            [[fallthrough]];           /* Fall through */
            /* Dual and Quad mode uses same config. */
        }

        case OSPI_W_DEVICE_BUS_MODE_DUAL:
        case OSPI_W_DEVICE_BUS_MODE_QUAD:
        {
            r_ospi_w_device_set_io2_direction(OSPI_W_DEVICE_IO_DIR_AUTO_SEL);
            r_ospi_w_device_set_io3_direction(OSPI_W_DEVICE_IO_DIR_AUTO_SEL);
        }

        default:
        {
            break;
        }
    }

    r_ospi_w_device_set_bus_mode(bus_mode);
}

BSP_PLACE_CODE_IN_RAM static uint32_t r_ospi_w_flash_write_page_safe (spi_flash_ctrl_t * const p_ctrl,
                                                                      uint32_t                 addr,
                                                                      const uint8_t          * buf,
                                                                      uint32_t                 size)
{
    uint32_t written;
    FSP_CRITICAL_SECTION_DEFINE;

    /*
     * From now on OQSPI may not be available, turn off interrupts.
     */
    FSP_CRITICAL_SECTION_ENTER;

    /*
     * Write data into the page of the Flash.
     */
    written = r_ospi_w_flash_write_page(p_ctrl, addr, buf, size);

    /* Wait for the Flash to process the command */
    while (r_ospi_flash_is_busy(p_ctrl))
    {
        ;
    }

    /*
     * Let other code to be executed including OQSPI one.
     */
    FSP_CRITICAL_SECTION_EXIT;

    return written;
}

BSP_PLACE_CODE_IN_RAM static uint32_t r_ospi_w_flash_write_page (spi_flash_ctrl_t * const p_ctrl,
                                                                 uint32_t                 addr,
                                                                 const uint8_t          * buf,
                                                                 uint32_t                 size)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;
    uint8_t                 pp_cmd           = p_instance_ctrl->p_cfg->page_program_command;
    uint8_t                 addr_len         = p_instance_ctrl->p_cfg->address_bytes;
    const spi_flash_cfg_t * p_cfg            = p_instance_ctrl->p_cfg;
    ospi_w_extended_cfg_t * p_extended       = (ospi_w_extended_cfg_t *) p_cfg->p_extend;

    ospi_w_device_bus_mode instr_bus_mode;
    ospi_w_device_bus_mode bus_mode;

    uint32_t i   = 0;
    uint32_t odd = ((uint32_t) buf) & 3;
    uint32_t size_aligned32;
    uint32_t tmp;

    switch (p_instance_ctrl->p_cfg->spi_protocol)
    {
        case SPI_FLASH_PROTOCOL_1S_1S_1S:
        {
            instr_bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE;
            break;
        }

        case SPI_FLASH_PROTOCOL_1S_4S_4S:
        {
            instr_bus_mode = OSPI_W_DEVICE_BUS_MODE_QUAD;
            break;
        }

        case SPI_FLASH_PROTOCOL_8D_8D_8D:
        {
            instr_bus_mode = OSPI_W_DEVICE_BUS_MODE_OCTA;
            break;
        }

        default:
        {
            return FSP_ERR_INVALID_MODE;
            break;
        }
    }

    switch (p_instance_ctrl->p_cmd_set->protocol)
    {
        case SPI_FLASH_PROTOCOL_1S_1S_1S:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE;
            break;
        }

        case SPI_FLASH_PROTOCOL_1S_4S_4S:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_QUAD;
            break;
        }

        case SPI_FLASH_PROTOCOL_8D_8D_8D:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_OCTA;
            break;
        }

        default:
        {
            return FSP_ERR_INVALID_MODE;
            break;
        }
    }

    ospi_w_set_bus_mode(instr_bus_mode);
    r_ospi_w_write_enable();

    /* Make sure write will not cross page boundary */
    tmp = OSPI_FLASH_PAGE_SIZE - (addr & 0xFF);
    if (size > tmp)
    {
        size = tmp;
    }

    r_ospi_w_device_cs_enable();

    r_ospi_w_device_write8(pp_cmd);

    if (p_extended->p_ospi_w_device_cfg->automode_config.instruct_size == OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES)
    {
        r_ospi_w_device_write8(~pp_cmd);
    }

    if ((pp_cmd == OSPI_W_QUAD_PAGEPR_CMD) || (pp_cmd == OSPI_W_QUAD_PAGEPR_CMD_2)) /* 4PP command */
    {
        ospi_w_set_bus_mode(bus_mode);
    }

    if (addr_len == SPI_FLASH_ADDRESS_BYTES_4)
    {
        r_ospi_w_device_write32(addr);
    }
    else
    {
        r_ospi_w_device_write8((uint8_t) ((addr >> 16) & 0xFF));
        r_ospi_w_device_write8((uint8_t) ((addr >> 8) & 0xFF));
        r_ospi_w_device_write8((uint8_t) (addr & 0xFF));
    }

    if (pp_cmd == OSPI_W_SINGLE_ADDR_QUAD_PAGEPR_CMD) /* 1-1-4 page program command */
    {
        ospi_w_set_bus_mode(bus_mode);
    }

    if (odd)
    {
        odd = 4 - odd;
        for (i = 0; i < odd && i < size; ++i)
        {
            r_ospi_w_device_write8(buf[i]);
        }
    }

    size_aligned32 = ((size - i) & (uint32_t) ~0x3);

    if (size_aligned32)
    {
        fast_write_to_fifo32((uint32_t) (buf + i), (uint32_t) (buf + i + size_aligned32),
                             (uint32_t) &(OQSPIF->OQSPIF_WRITEDATA_REG));
        i += size_aligned32;
    }

    for ( ; i < size; ++i)
    {
        r_ospi_w_device_write8(buf[i]);
    }

    r_ospi_w_device_cs_disable();

    ospi_w_set_bus_mode(instr_bus_mode);

    return i;
}

BSP_PLACE_CODE_IN_RAM uint8_t r_ospi_flash_read_register (uint8_t cmd, uint8_t mask, ospi_w_device_bus_mode bus_mode)
{
    FSP_PARAMETER_NOT_USED(bus_mode);
    volatile uint8_t reg_val;
    uint8_t          dummy_cycle;

    r_ospi_w_device_cs_enable();
    r_ospi_w_device_write8(cmd);
    if (r_ospi_w_device_get_instruction_size() == OSPI_W_DEVICE_INSTRUCT_SZ_2_BYTES)
    {
        r_ospi_w_device_write8(~cmd);
    }

    /* Send dummy bytes for octa flash */
    dummy_cycle = REG_GETF(OQSPIF, OQSPIF_STATUSCMD_REG, OSPIC_RSTAT_DMY_NUM);
    if (dummy_cycle > 0)
    {
        dummy_cycle += 1;
        for (uint8_t dummy = 0; dummy < dummy_cycle; dummy++)
        {
            r_ospi_w_device_write8(0);
        }
    }

    reg_val = r_ospi_w_device_read8();
    r_ospi_w_device_cs_disable();

    return reg_val & mask;
}

BSP_PLACE_CODE_IN_RAM bool r_ospi_flash_is_busy (spi_flash_ctrl_t * const p_ctrl)
{
    ospi_w_instance_ctrl_t * p_instance_ctrl = (ospi_w_instance_ctrl_t *) p_ctrl;
    uint8_t                status_cmd        = p_instance_ctrl->p_cfg->status_command;
    uint8_t                busy_mask         = (0x01 << (p_instance_ctrl->p_cfg->write_status_bit));
    ospi_w_device_bus_mode bus_mode;

    switch (p_instance_ctrl->p_cfg->spi_protocol)
    {
        case SPI_FLASH_PROTOCOL_1S_1S_1S:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE;
            break;
        }

        case SPI_FLASH_PROTOCOL_1S_4S_4S:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_QUAD;
            break;
        }

        case SPI_FLASH_PROTOCOL_8D_8D_8D:
        {
            bus_mode = OSPI_W_DEVICE_BUS_MODE_OCTA;
            break;
        }

        default:
        {
            return FSP_ERR_INVALID_MODE;
            break;
        }
    }

    uint8_t is_busy;
    is_busy = r_ospi_flash_read_register(status_cmd, busy_mask, bus_mode);

    return is_busy ? true : false;
}

BSP_PLACE_CODE_IN_RAM void r_ospi_w_device_erase_block (uint32_t addr)
{
    if (r_ospi_w_device_get_access_mode() != OSPI_W_DEVICE_ACCESS_MODE_AUTO)
    {
        r_ospi_w_device_set_access_mode(OSPI_W_DEVICE_ACCESS_MODE_AUTO);
    }

    // Wait for previous erase to end
    while (r_ospi_w_device_get_erase_status() != OSPI_W_DEVICE_ERS_NO)
    {
    }

    uint32_t block_sector = addr >> 12;
    switch (r_ospi_w_device_get_address_size())
    {
        case OSPI_W_DEVICE_ADDR_SIZE_24:
        {
            // FSP_ASSERT(addr <= 0x00FFFFFF);
            // OQSPIF_ERASECTRL_REG bits 23-12 determine the block/sector address bits (23-12)
            block_sector <<= 8;
            break;
        }

        case OSPI_W_DEVICE_ADDR_SIZE_32:
        {
            // FSP_ASSERT(addr < (MEMORY_OQSPIC_S_END - MEMORY_OQSPIC_S_BASE));
            // OQSPIF_ERASECTRL_REG bits 23-4 determine the block/sector address bits (31-12)
            break;
        }

        default:
        {
            // FSP_ASSERT(0);
            break;
        }
    }

    r_ospi_w_device_set_erase_address(block_sector);
    r_ospi_w_device_trigger_erase();
}
