/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-05-06   onelife     Initial creation by using USART module
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_usart.h"
#include "dev_sflash.h"

#if defined(EFM32_USING_SFLASH)
/* Private typedef -------------------------------------------------------------*/
typedef struct
{
    rt_uint8_t code;
    rt_uint32_t address:24;
    rt_uint32_t dummy:8;
} sflash_instruction;

/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
#ifdef EFM32_SFLASH_DEBUG
#define sflash_debug(format,args...)        rt_kprintf(format, ##args)
#else
#define sflash_debug(format,args...)
#endif

/* Private constants -----------------------------------------------------------*/
static rt_uint8_t sflash_inst_code_tbl[] =
{
    /* Instruction only */
    SFLASH_INST_CODE_WREN,
    SFLASH_INST_CODE_WRDI,
    SFLASH_INST_CODE_RDID_L,
    SFLASH_INST_CODE_RDID_S,
    SFLASH_INST_CODE_RDSR,
    SFLASH_INST_CODE_WRSR,
    SFLASH_INST_CODE_BE,
    SFLASH_INST_CODE_DP,
    SFLASH_INST_CODE_RDP,
    /* Instruction and address */
    SFLASH_INST_CODE_WRLR,
    SFLASH_INST_CODE_RDLR,
    SFLASH_INST_CODE_READ,
    SFLASH_INST_CODE_POTP,
    SFLASH_INST_CODE_PP,
    SFLASH_INST_CODE_DIFP,
    SFLASH_INST_CODE_SSE,
    SFLASH_INST_CODE_SE,
    /* Instruction, address and dummy read */
    SFLASH_INST_CODE_READ_F,
    SFLASH_INST_CODE_DOFR,
    SFLASH_INST_CODE_ROTP
};
static rt_uint16_t sflash_data_len_tbl[] =
{
    /* Instruction only */
    SFLASH_REPLY_LEN_WREN,
    SFLASH_REPLY_LEN_WRDI,
    SFLASH_REPLY_LEN_RDID_L,
    SFLASH_REPLY_LEN_RDID_S,
    SFLASH_REPLY_LEN_RDSR,
    SFLASH_REPLY_LEN_WRSR,
    SFLASH_REPLY_LEN_BE,
    SFLASH_REPLY_LEN_DP,
    SFLASH_REPLY_LEN_RDP,
    /* Instruction and address */
    SFLASH_REPLY_LEN_WRLR,
    SFLASH_REPLY_LEN_RDLR,
    SFLASH_REPLY_LEN_READ,
    SFLASH_REPLY_LEN_POTP,
    SFLASH_REPLY_LEN_PP,
    SFLASH_REPLY_LEN_DIFP,
    SFLASH_REPLY_LEN_SSE,
    SFLASH_REPLY_LEN_SE,
    /* Instruction, address and dummy read */
    SFLASH_REPLY_LEN_READ_F,
    SFLASH_REPLY_LEN_DOFR,
    SFLASH_REPLY_LEN_ROTP
};
static rt_bool_t sflash_read_inst_tbl[] =
{
    /* Instruction only */
    false,
    false,
    true,
    true,
    true,
    false,
    false,
    false,
    false,
    /* Instruction and address */
    false,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    /* Instruction, address and dummy read */
    true,
    true,
    true
};

/* Private variables ------------------------------------------------------------*/
static rt_device_t  sFlash                  = RT_NULL;
static rt_bool_t    sFlashAutoCs            = true;

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Initialize the SPI Flash
 *
 * @details
 *
 * @note
 *
 * @return
 *   Error code
 *********************************************************************/
rt_err_t efm_spiFlash_init(void)
{
    struct efm32_usart_device_t *usart;

    usart = (struct efm32_usart_device_t *)(sFlash->user_data);

#if defined(EFM32_GXXX_DK)
    /* Enable SPI access to Flash */
    DVK_writeRegister(BC_SPI_CFG, 0);
#endif

    do
    {
        /* Find SPI device */
        sFlash = rt_device_find(SFLASH_USING_DEVICE_NAME);
        if (sFlash == RT_NULL)
        {
            sflash_debug("SFLASH: Can't find device %s!\n",
                SFLASH_USING_DEVICE_NAME);
            break;
        }
        sflash_debug("SFLASH: Find device %s\n", SFLASH_USING_DEVICE_NAME);

        /* Config chip slect pin */
        if (!(usart->state & USART_STATE_AUTOCS))
        {
            GPIO_PinModeSet(SFLASH_CS_PORT, SFLASH_CS_PIN, gpioModePushPull, 1);
            sFlashAutoCs = false;
        }

        /* Open SPI device */
        if (sFlash->open(sFlash, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
        {
            break;
        }

        return RT_EOK;
    } while(0);

    sflash_debug("SFLASH: Init failed!\n");
    return -RT_ERROR;
}

/******************************************************************//**
 * @brief
 *   De-initialize the SPI Flash
 *
 * @details
 *
 * @note
 *
 * @return
 *   Error code
 *********************************************************************/
rt_err_t efm_spiFlash_deinit(void)
{
    do
    {
        if (sFlash == RT_NULL)
        {
            sflash_debug("SFLASH: Already deinit!\n");
            break;
        }

        /* Close SPI device */
        if (sFlash->close(sFlash) != RT_EOK)
        {
            break;
        }
        sFlash = RT_NULL;
        sflash_debug("SFLASH: Close device %s\n", SFLASH_USING_DEVICE_NAME);

        return RT_EOK;
    } while(0);

    sflash_debug("SFLASH: Deinit failed!\n");
    return -RT_ERROR;
}

/******************************************************************//**
 * @brief
 *   Set/Clear chip select
 *
 * @details
 *
 * @note
 *
 * @param[in] enable
 *  Chip select pin setting
 *********************************************************************/
static void efm_spiFlash_cs(rt_uint8_t enable)
{
    if (!sFlashAutoCs)
    {
        if (enable)
        {
            GPIO_PinOutClear(SFLASH_CS_PORT, SFLASH_CS_PIN);
        }
        else
        {
            GPIO_PinOutSet(SFLASH_CS_PORT, SFLASH_CS_PIN);
        }
    }
}

/******************************************************************//**
 * @brief
 *   Execute a command
 *
 * @details
 *
 * @note
 *
 * @param[in] command
 *  SPI Flash instruction
 *
 * @param[in] address
 *   Memory address
 *
 * @param[in] buffer
 *   Poniter to the read/write buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Number of read/written bytes
 *********************************************************************/
rt_uint32_t efm_spiFlash_cmd(
    enum sflash_inst_type_t command,
    rt_uint32_t address,
    rt_uint8_t *buffer,
    rt_uint32_t size)
{
    RT_ASSERT(sFlash != RT_NULL);

    sflash_instruction *inst;
    rt_uint8_t *inst_buf;
    rt_uint8_t inst_len, head_len;
    rt_uint32_t data_len;

    sflash_debug("SFLASH: Inst %x\n", sflash_inst_code_tbl[command]);
    if (sflash_data_len_tbl[command] && !size)
    {
        sflash_debug("SFLASH: No data!\n");
        return 0x00;
    }

    data_len = (sflash_data_len_tbl[command] < size)? \
                sflash_data_len_tbl[command] : size;
    if (data_len && (buffer == RT_NULL))
    {
        sflash_debug("SFLASH: No buffer specified!\n");
        return 0x00;
    }

    /* Allocate memory for write buffer */
    if (sflash_read_inst_tbl[command])
    {
        inst_buf = rt_malloc(6 + 4);
        inst = (sflash_instruction *)(inst_buf + 1);
        head_len = 1;
    }
    else
    {
        inst_buf = rt_malloc(5 + data_len);
        inst = (sflash_instruction *)inst_buf;
        head_len = 0;
    }

    /* Fill in instruction */
    inst->code = sflash_inst_code_tbl[command];
    if (command >= sflash_inst_wrlr)
    {
        /* MSB first */
        inst->address = ((address & 0x000000FF) << 16) | \
                        (address & 0x0000FF00) | \
                        ((address & 0x00FF0000) >> 16);
        if (command >= sflash_inst_read_f)
        {
            inst->dummy = 0x00;
            inst_len = 5;
        }
        else
        {
            inst_len = 4;
        }
    }
    else
    {
        inst_len = 1;
    }
    head_len += inst_len;

    /* Fill in data and send the buffer */
    if (sflash_read_inst_tbl[command])
    {
        rt_off_t skip;

        inst_buf[0] = inst_len;
        *(rt_uint8_t **)(inst_buf + head_len) = buffer;
        if (command == sflash_inst_read)
        {
            skip = SFLASH_SPI_READ_SKIP;
        }
        else
        {
            skip = SFLASH_SPI_COMMAND_SKIP;
        }

        efm_spiFlash_cs(1);
        if (sFlash->read(sFlash, skip, inst_buf, \
            (data_len == size)? data_len - 1 : data_len) == 0)
        {
            sflash_debug("SFLASH: Read failed!\n");
            return 0x00;
        }
        efm_spiFlash_cs(0);
        buffer[data_len] = 0x00;
        sflash_debug("SFLASH: Read %d bytes data to 0x%x\n", data_len, buffer);
    }
    else
    {
        if (data_len)
        {
            rt_memcpy((inst_buf + head_len), buffer, data_len);
        }

        efm_spiFlash_cs(1);
        if (sFlash->write(sFlash, EFM32_NO_DATA, inst_buf, \
            head_len + data_len) == 0)
        {
            sflash_debug("SFLASH: Write failed!\n");
            return 0x00;
        }
        efm_spiFlash_cs(0);
        sflash_debug("SFLASH: Write %d/%d bytes data\n", data_len, \
            head_len + data_len);
    }

    /* Free the buffer */
    rt_free(inst_buf);
    return data_len;
}

/*********************************************************************
*   Export to FINSH
*********************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void list_sflash(void)
{
    rt_uint8_t buf[4];

    efm_spiFlash_cmd(sflash_inst_rdid_s, EFM32_NO_DATA, buf, sizeof(buf));

    rt_kprintf("    spi flash on %s\n", SFLASH_USING_DEVICE_NAME);
    rt_kprintf(" ------------------------------\n");
    rt_kprintf(" Manufacturer ID:\t%x\n", buf[0]);
    rt_kprintf(" Memory type:\t\t%x\n", buf[1]);
    rt_kprintf(" Memory capacity:\t%x\n", buf[2]);
}
FINSH_FUNCTION_EXPORT(list_sflash, list the SPI Flash.)
#endif

#endif /* defined(EFM32_USING_SFLASH) */

/******************************************************************//**
 * @}
*********************************************************************/
