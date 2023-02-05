/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-05-13   onelife     Initial creation for using EFM32 USART module
 * 2011-07-07   onelife     Modify initialization function to return error code
 * 2011-12-08   onelife     Add giant gecko development kit support
 * 2011-12-15   onelife     Move MicroSD enabling routine to driver
 *                            initialization function (board.c)
 * 2011-12-21   onelife     Modify code due to SPI write format changed
 */

/***************************************************************************//**
 * @addtogroup efm32_dk
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_usart.h"
#include "drv_sdcard.h"

#if defined(EFM32_USING_SPISD)
#include <dfs_fs.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef EFM32_SDCARD_DEBUG
#define sdcard_debug(format,args...)        rt_kprintf(format, ##args)
#else
#define sdcard_debug(format,args...)
#endif

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static struct rt_device     sd_device;
static struct dfs_partition sdPart;
static rt_device_t          spi             = RT_NULL;
static rt_uint16_t          sdType;
static rt_bool_t            sdAutoCs        = true;
static rt_timer_t           sdTimer         = RT_NULL;
static volatile rt_bool_t   sdInTime        = true;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Memory device timeout interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] parameter
 *  Parameter
 ******************************************************************************/
static void efm_spiSd_timer(void* parameter)
{
    sdInTime = false;
}

/***************************************************************************//**
 * @brief
 *   Set/Clear chip select
 *
 * @details
 *
 * @note
 *
 * @param[in] enable
 *  Chip select pin setting
 ******************************************************************************/
static void efm_spiSd_cs(rt_uint8_t enable)
{
    if (!sdAutoCs)
    {
        if (enable)
        {
            GPIO_PinOutClear(SD_CS_PORT, SD_CS_PIN);
        }
        else
        {
            GPIO_PinOutSet(SD_CS_PORT, SD_CS_PIN);
        }
    }
}

/***************************************************************************//**
 * @brief
 *   Set operation speed level
 *
 * @details
 *
 * @note
 *
 * @param[in] level
 *  Set SD speed level
 ******************************************************************************/
static void efm_spiSd_speed(rt_uint8_t level)
{
    RT_ASSERT(spi != RT_NULL);

    struct efm32_usart_device_t *usart;
    rt_uint32_t baudrate;

    usart = (struct efm32_usart_device_t *)(spi->user_data);
    if (level == SD_SPEED_HIGH)
    {
        baudrate = EFM32_SDCLK_HIGH;
    }
    else
    {
        baudrate = EFM32_SDCLK_LOW;
    }
    USART_BaudrateSyncSet(usart->usart_device, 0, baudrate);
}

/***************************************************************************//**
 * @brief
 *   Read raw data from memory device
 *
 * @details
 *
 * @note
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Number of read bytes
 ******************************************************************************/
static rt_ssize_t efm_spiSd_read(void *buffer, rt_size_t size)
{
    RT_ASSERT(spi != RT_NULL);

    rt_uint8_t buf_read[5], ret;

    /* Build instruction buffer */
    buf_read[0] = 0x00;
    *(rt_uint8_t **)(&buf_read[1]) = buffer;
    /* Read data */
    efm_spiSd_cs(1);
    if ((ret = spi->read(spi, EFM32_NO_DATA, buf_read, size)) == 0)
    {
        sdcard_debug("SPISD: Read failed!\n");
    }
    efm_spiSd_cs(0);

    return ret;
}

/***************************************************************************//**
 * @brief
 *   Send command to memory device
 *
 * @details
 *
 * @note
 *
 * @param[in] cmd
 *   Command index
 *
 * @param[in] arg
 *   Argument
 *
 * @param[in] trail
 *   Pointer to the buffer to store trailing data
 *
 * @return
 *   Command response
 ******************************************************************************/
static rt_uint16_t efm_spiSd_cmd(
    rt_uint8_t cmd,
    rt_uint32_t arg,
    rt_uint8_t *trail)
{
    RT_ASSERT(spi != RT_NULL);

    rt_uint8_t buf_ins[11];
    rt_uint8_t buf_res[32];     /* Expect (x+1+4) bytes for CRC, (x+1+19) for CSD/CID */
    rt_uint8_t len_trl, i, j;
    rt_uint16_t ret;
    rt_bool_t skip;

    ret = 0xffff;
    rt_memset(buf_res, 0xff, sizeof(buf_res));

    sdcard_debug("SPISD: Send command %d(%x)\n", cmd, arg);
    do
    {
        /* Build instruction buffer */
        buf_ins[0] = 6;                             /* Instruction length */
        buf_ins[1] = 0x40 | cmd;                    /* Command index */
        buf_ins[2] = (arg >> 24) & 0x000000ff;      /* Argument: MSB first */
        buf_ins[3] = (arg >> 16) & 0x000000ff;
        buf_ins[4] = (arg >> 8) & 0x000000ff;
        buf_ins[5] = arg & 0x000000ff;
        if (cmd == CMD0)
        {
            buf_ins[6] = 0x95;                      /* Valid CRC for CMD0(0) */
        }
        else if (cmd == CMD8)
        {
            buf_ins[6] = 0x87;                      /* Valid CRC for CMD8(0x1AA) */
        }
        else if (cmd == CMD58)
        {
            buf_ins[6] = 0x01;                      /* Dummy CRC + Stop */
        }
        else
        {
            buf_ins[6] = 0x01;                      /* Dummy CRC + Stop */
        }
        *(rt_uint8_t **)(&buf_ins[7]) = buf_res;    /* Pointer to RX buffer */

        /* Set trail length */
        if (cmd == CMD8)
        {
            len_trl = 4;                            /* R7 response */
        }
        else if (cmd == CMD9)
        {
            len_trl = SD_BLOCK_SIZE_CSD;
        }
        else if (cmd == CMD10)
        {
            len_trl = SD_BLOCK_SIZE_CID;
        }
        else if (cmd == CMD58)
        {
            len_trl = SD_BLOCK_SIZE_OCR;            /* R3 response */
        }
        else
        {
            len_trl = 0;
        }

        /* Send command and get response */
        efm_spiSd_cs(1);
        if (spi->read(spi, EFM32_NO_DATA, buf_ins, sizeof(buf_res)) == 0)
        {
            sdcard_debug("SPISD: Send command failed!\n");
            break;
        }
        efm_spiSd_cs(0);

        /* Skip a stuff byte when stop reading */
        if (cmd == CMD12)
        {
            skip = true;
        }
        else
        {
            skip = false;
        }
        /* Find valid response: The response is sent back within command response time
            (NCR), 0 to 8 bytes for SDC, 1 to 8 bytes for MMC */
        for (i = 0; i < sizeof(buf_res); i++)
        {
            if (buf_res[i] != 0xff)
            {
                if (skip)
                {
                    skip = false;
                    sdcard_debug("SPISD: Skip %x (at %d)\n", buf_res[i], i);
                    continue;
                }

                if (cmd == ACMD13 & 0x7f)
                {
                    ret = (rt_uint16_t)buf_res[i];  /* R2 response */
                }
                else
                {
                    ret = (rt_uint8_t)buf_res[i];
                }
                break;
            }
        }
        sdcard_debug("SPISD: Response %x (at %d)\n", ret, i);
        i++;
        /* Copy the trailing data */
        if ((ret != 0xffff) && len_trl && trail)
        {
            if (cmd == CMD9 || cmd == CMD10)
            {
                /* Wait for data block */
                for (; i < sizeof(buf_res); i++)
                {
                    if (buf_res[i] == 0xfe)
                    {
                        break;
                    }
                }
                /* Check if valid */
                if (i >= sizeof(buf_res))
                {
                    sdcard_debug("SPISD: Token is not found!\n");
                    ret = 0xffff;
                    break;
                }
                i++;
            }
            /* Copy the data */
            for (j = 0; j < len_trl; j++)
            {
                trail[j] = buf_res[i + j];
            }
        }
    } while(0);

    return ret;
}

/***************************************************************************//**
 * @brief
 *   Read a block of data from memory device. This function is used to handle
 *  the responses of specified commands (e.g. ACMD13, CMD17 and CMD18)
 *
 * @details
 *
 * @note
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm_spiSd_readBlock(void *buffer, rt_size_t size)
{
    RT_ASSERT(spi != RT_NULL);

    rt_uint8_t buf_ins[5];
    rt_uint8_t buf_res[8];      /* Expect 2 bytes for CRC */
    rt_uint8_t i, len_copy;
    rt_bool_t start;

    start = false;
    do
    {
        /* Build instruction buffer */
        buf_ins[0] = 0;                             /* Instruction length */
        *(rt_uint8_t **)(&buf_ins[1]) = buf_res;    /* Pointer to RX buffer */

        while(1)
        {
            /* Send read command */
            efm_spiSd_cs(1);
            if (spi->read(spi, EFM32_NO_DATA, buf_ins, \
                sizeof(buf_res)) == 0)
            {
                sdcard_debug("SPISD: Get read command response failed!\n");
                break;
            }
            efm_spiSd_cs(0);
            /* Wait for data */
            for (i = 0; i < sizeof(buf_res); i++)
            {
                if (buf_res[i] != 0xff)
                {
                    start = true;
                    break;
                }
            }
            if (start)
            {
                break;
            }
        };

        /* Ckeck if valid */
        if (!start || (buf_res[i] != 0xfe))
        {
            sdcard_debug("SPISD: Token is invalid! (%x)\n", buf_res[i]);
            break;
        }
        /* Copy data to buffer and read the rest */
        len_copy = sizeof(buf_res) - i - 1;
        rt_memcpy(buffer, &buf_res[i + 1], len_copy);
        sdcard_debug("SPISD: Read block start at %d, copy %d bytes\n", i, \
            len_copy);

        /* Build instruction buffer */
        buf_ins[0] = 0;                             /* Instruction length */
        *(rt_uint8_t **)(&buf_ins[1]) = (rt_uint8_t *)buffer + len_copy;    /* Pointer to RX buffer */

        /* Send read command */
        efm_spiSd_cs(1);
        if (spi->read(spi, EFM32_NO_DATA, buf_ins, size - len_copy) == 0)
        {
            sdcard_debug("SPISD: Read data block failed!\n");
            break;
        }
        *(rt_uint8_t **)(&buf_ins[1]) = buf_res;    /* Pointer to RX buffer */
        if (spi->read(spi, EFM32_NO_DATA, buf_ins, sizeof(buf_res)) == 0)
        {
            sdcard_debug("SPISD: Read CRC failed!\n");
            break;
        }
        sdcard_debug("SPISD: Read CRC %x %x\n", buf_res[0], buf_res[1]);
        efm_spiSd_cs(0);

        return RT_EOK;
    } while(0);

    sdcard_debug("SPISD: Read block failed!\n");
    return -RT_ERROR;
}

/***************************************************************************//**
 * @brief
 *   Write a block of data to memory device. This function is used to send data
 *  and control tokens for block write commands (e.g. CMD24 and CMD25)
 *
 * @details
 *
 * @note
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] token
 *   Control token
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm_spiSd_writeBlock(void *buffer, rt_uint8_t token)
{
    RT_ASSERT(spi != RT_NULL);

    rt_err_t ret;
    rt_uint8_t buf_ins[11];
    rt_uint8_t buf_res[8];      /* Expect a byte for data response */
    rt_uint8_t i;

    ret = RT_ERROR;
    sdcard_debug("SPISD: Write block\n");
    do
    {
        /* Initialize timer */
        sdInTime = true;
        rt_timer_start(sdTimer);
        /* Wait for card ready */
        do
        {
            efm_spiSd_read(buf_res, sizeof(buf_res));
        } while (sdInTime && (buf_res[sizeof(buf_res) - 1] != 0xff));
        if (buf_res[sizeof(buf_res) - 1] != 0xff)
        {
            sdcard_debug("SPISD: Card is busy before writing! (%x)\n", \
                buf_res[sizeof(buf_res) - 1]);
            ret = -RT_EBUSY;
            break;
        }
        rt_timer_stop(sdTimer);

        /* Send data */
        sdcard_debug("SPISD: Send data, token %x\n", token);
        if (token != 0xfd)
        {
            /* Send token and data */
            buf_ins[0] = 1;                             /* Instruction length */
            buf_ins[1] = token;
            *(rt_uint8_t **)(&buf_ins[2]) = (rt_uint8_t *)buffer;   /* Pointer to TX buffer */
            efm_spiSd_cs(1);
            if (spi->write(spi, EFM32_NO_DATA, buf_ins, SD_SECTOR_SIZE) == 0)
            {
                sdcard_debug("SPISD: Write data failed!\n");
                break;
            }

            /* Build instruction buffer */
            buf_ins[0] = 2;                             /* Instruction length */
            buf_ins[1] = 0xff;                          /* CRC (Dummy) */
            buf_ins[2] = 0xff;
            *(rt_uint8_t **)(&buf_ins[3]) = buf_res;    /* Pointer to RX buffer */
            /* Send CRC and read a byte */
            if (spi->read(spi, EFM32_NO_DATA, buf_ins, sizeof(buf_res)) == 0)
            {
                sdcard_debug("SPISD: Write CRC failed!\n");
                break;
            }
            efm_spiSd_cs(0);

            /* Check if accepted */
            for (i = 0; i < sizeof(buf_res); i++)
            {
                if (buf_res[i] != 0xff)
                {
                    buf_res[i] &= 0x1f;
                    break;
                }
            }
            if (buf_res[i] != 0x05)
            {
                sdcard_debug("SPISD: Writing is not accepted! (%x at %d)\n", \
                    buf_res[i], i);
                break;
            }
        }
        else
        {
            /* Send token */
            buf_ins[0] = 1;                             /* Instruction length */
            buf_ins[1] = token;
            *(rt_uint8_t **)(&buf_ins[2]) = RT_NULL;    /* Pointer to TX buffer */
            efm_spiSd_cs(1);
            if (spi->write(spi, EFM32_NO_DATA, buf_ins, 0) != 0)
            {
                sdcard_debug("SPISD: Write token failed!\n");
                break;
            }

            /* Initialize timer */
            sdInTime = true;
            rt_timer_start(sdTimer);
            /* Wait for card ready */
            do
            {
                efm_spiSd_read(buf_res, sizeof(buf_res));
            } while (sdInTime && (buf_res[sizeof(buf_res) - 1] != 0xff));
            if (buf_res[sizeof(buf_res) - 1] != 0xff)
            {
                sdcard_debug("SPISD: Card is busy after writing! (%x)\n", \
                    buf_res[sizeof(buf_res) - 1] );
                ret = -RT_EBUSY;
                break;
            }
            rt_timer_stop(sdTimer);
        }

        return RT_EOK;
    } while(0);

    sdcard_debug("SPISD: Write block failed!\n");
    return ret;
}

/***************************************************************************//**
 * @brief
 *   Wrapper function of send command to memory device
 *
 * @details
 *
 * @note
 *
 * @param[in] cmd
 *   Command index
 *
 * @param[in] arg
 *   Argument
 *
 * @param[in] trail
 *   Pointer to the buffer to store trailing data
 *
 * @return
 *   Command response
 ******************************************************************************/
rt_uint16_t efm_spiSd_sendCmd(
    rt_uint8_t cmd,
    rt_uint32_t arg,
    rt_uint8_t *trail)
{
    rt_uint16_t ret;

    /* ACMD<n> is the command sequense of CMD55-CMD<n> */
    if (cmd & 0x80)
    {
        cmd &= 0x7f;
        ret = efm_spiSd_cmd(CMD55, 0x00000000, EFM32_NO_POINTER);
        if (ret > 0x01)
        {
            return ret;
        }
    }

    return efm_spiSd_cmd(cmd, arg, trail);
}

/***************************************************************************//**
 * @brief
 *   Initialize memory card device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t rt_spiSd_init(rt_device_t dev)
{
    RT_ASSERT(spi != RT_NULL);

    rt_uint8_t type, cmd, tril[4];
    rt_uint8_t *buf_res;

    type = 0;
    buf_res = RT_NULL;

    do
    {
        /* Create and setup timer */
        if ((sdTimer = rt_timer_create(
            "sd_tmr",
            efm_spiSd_timer,
            RT_NULL,
            SD_WAIT_PERIOD,
            RT_TIMER_FLAG_ONE_SHOT)) == RT_NULL)
        {
            sdcard_debug("SPISD: Create timer failed!\n");
            break;
        }

        /* Open SPI device */
        if (spi->open(spi, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
        {
            break;
        }

        /* Switch to low speed */
        efm_spiSd_speed(SD_SPEED_LOW);

        /* 80 dummy clocks */
        efm_spiSd_read(RT_NULL, 80);
        /* Enter Idle state */
        if (efm_spiSd_sendCmd(CMD0, 0x00000000, EFM32_NO_POINTER) != 0x01)
        {
            break;
        }
        /* Check if SDv2 */
        if (efm_spiSd_sendCmd(CMD8, 0x000001AA, tril) == 0x01)
        {
            /* SDv2, Vdd: 2.7-3.6V */
            if (tril[2] == 0x01 && tril[3] == 0xAA)
            {
                /* Initialize timer */
                sdInTime = true;
                rt_timer_start(sdTimer);
                /* Wait for leaving idle state (ACMD41 with HCS bit) */
                while (efm_spiSd_sendCmd(ACMD41, 0x40000000, EFM32_NO_POINTER) \
                    && sdInTime);
                /* Check CCS bit (bit 30) in the OCR */
                if (sdInTime && efm_spiSd_sendCmd(CMD58, 0x00000000, tril) \
                    == 0x00)
                {
                    type = (tril[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;
                }
            }
        }
        else
        {
            if (efm_spiSd_sendCmd(ACMD41, 0x00000000, EFM32_NO_POINTER) <= 0x01)
            {
                /* SDv1 */
                type = CT_SD1;
                cmd = ACMD41;
            }
            else
            {
                /* MMCv3 */
                type = CT_MMC;
                cmd = CMD1;
            }
            /* Initialize timer */
            sdInTime = true;
            rt_timer_start(sdTimer);
            /* Wait for leaving idle state */
            while (efm_spiSd_sendCmd(cmd, 0x00000000, EFM32_NO_POINTER) && \
                sdInTime);
            /* Set read/write block length to SD_BLOCK_SIZE */
            if (!sdInTime || \
                (efm_spiSd_sendCmd(CMD16, SD_SECTOR_SIZE, EFM32_NO_POINTER) \
                != 0x00))
            {
                type = 0;
                break;
            }
        }
        rt_timer_stop(sdTimer);

        /* Check type */
        sdType = type;
        if (sdType)
        {
            /* Initialization succeded */
            efm_spiSd_speed(SD_SPEED_HIGH);
        }
        else
        {
            break;
        }

        /* Allocate buffer */
        if ((buf_res = rt_malloc(SD_SECTOR_SIZE)) == RT_NULL)
        {
            sdcard_debug("SPISD: No memory for sector buffer\n");
            break;
        }
        /* Read the first sector for partition table */
        if (dev->read(dev, 0, buf_res, 1) != 1)
        {
            sdcard_debug("SPISD: Read first sector failed!\n");
            break;
        }
        /* Fetch the partition table */
        if (dfs_filesystem_get_partition(&sdPart, buf_res, 0) != RT_EOK)
        {
            sdPart.offset = 0;
            sdPart.size = 0;
            sdcard_debug("SPISD: No partition table\n");
        }
        /* Release buffer */
        rt_free(buf_res);
        sdcard_debug("SPISD: Init OK, card type %x\n", sdType);
        return RT_EOK;
    } while (0);

    /* Release buffer */
    if (buf_res)
    {
        rt_free(buf_res);
    }
    efm_spiSd_deinit();
    rt_kprintf("SPISD: Init failed!\n");
    return -RT_ERROR;
}

/***************************************************************************//**
 * @brief
 *   Open memory card device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] oflag
 *   Device open flag
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t rt_spiSd_open(rt_device_t dev, rt_uint16_t oflag)
{
    sdcard_debug("SPISD: Open, flag %x\n", sd_device.flag);
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Close memory card device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t rt_spiSd_close(rt_device_t dev)
{
    sdcard_debug("SPISD: Close, flag %x\n", sd_device.flag);
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Read from memory card device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] sector
 *   Start sector number (LBA)
 *
 * @param[in] buffer
 *   Pointer to the buffer
 *
 * @param[in] count
 *   Sector count (1..255)
 *
 * @return
 *   Number of read sectors
 ******************************************************************************/
static rt_ssize_t rt_spiSd_read(
    rt_device_t     dev,
    rt_off_t        sector,
    void            *buffer,
    rt_size_t       count)
{
    rt_uint8_t buf_ins[11], buf_res[12];
    rt_uint8_t *ptr;
    rt_uint8_t cmd, i;
    rt_size_t cnt;

    ptr = (rt_uint8_t *)buffer;
    cnt = count;

    sdcard_debug("SPISD: ****** Read Data ******\n");
    if (!(sdType & CT_BLOCK))
    {
        /* Convert to byte address if needed */
        sector *= SD_SECTOR_SIZE;
    }

    do
    {
        if (cnt == 1)
        {
            /* Single block read */
            cmd = CMD17;
            sdcard_debug("SPISD: Read single block\n");
        }
        else
        {
            /* Multiple block read */
            cmd = CMD18;
            sdcard_debug("SPISD: Read multiple blocks\n");
        }

        if (efm_spiSd_sendCmd(cmd, sector, EFM32_NO_POINTER))
        {
            sdcard_debug("SPISD: Read command error!\n");
            break;
        }

        /* Read data */
        do
        {
            if (efm_spiSd_readBlock(ptr, SD_SECTOR_SIZE))
            {
                break;
            }
            ptr += SD_SECTOR_SIZE;
        } while(--cnt);

        /* Stop transmission */
        if (cmd == CMD18)
        {
            if (efm_spiSd_sendCmd(CMD12, 0x00000000, EFM32_NO_POINTER))
            {
                break;
            }
        }

        return (count);
    } while(0);

    return (0);
}

/***************************************************************************//**
 * @brief
 *   Write to memory card device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] sector
 *   Start sector number (LBA)
 *
 * @param[in] buffer
 *   Pointer to the buffer
 *
 * @param[in] count
 *   Sector count (1..255)
 *
 * @return
 *   Number of written sectors
 ******************************************************************************/
static rt_ssize_t rt_spiSd_write (
    rt_device_t     dev,
    rt_off_t        sector,
    const void      *buffer,
    rt_size_t       count)
{
    rt_uint8_t buf_ins[11], buf_res[12];
    rt_uint8_t *ptr;
    rt_uint8_t cmd, token, i;
    rt_size_t cnt;

    ptr = (rt_uint8_t *)buffer;
    cnt = count;

    sdcard_debug("SPISD: ****** Write Data ******\n");
    if (!(sdType & CT_BLOCK))
    {
        /* Convert to byte address if needed */
        sector *= SD_SECTOR_SIZE;
    }

    do
    {
        if (cnt == 1)
        {
            /* Single block write */
            cmd = CMD24;
            token = 0xfe;
            sdcard_debug("SPISD: Write single block\n");
        }
        else
        {
            /* Multiple block write */
            cmd = CMD25;
            token = 0xfc;
            sdcard_debug("SPISD: Write multiple blocks\n");
            if (sdType & CT_SDC)
            {
                if (efm_spiSd_sendCmd(ACMD23, count, EFM32_NO_POINTER))
                {
                    break;
                }
            }
        }

        if (efm_spiSd_sendCmd(cmd, sector, EFM32_NO_POINTER))
        {
            sdcard_debug("SPISD: Write command error!\n");
            break;
        }

        /* Write data */
        do
        {
            if (efm_spiSd_writeBlock(ptr, token))
            {
                break;
            }
            ptr += SD_SECTOR_SIZE;
        } while(--cnt);

        /* Stop transmission token */
        if (efm_spiSd_writeBlock(EFM32_NO_POINTER, 0xfd))
        {
            break;
        }

        return (count);
    } while(0);

    return (0);
}

/***************************************************************************//**
* @brief
*   Configure memory card device
*
* @details
*
* @note
*
* @param[in] dev
*   Pointer to device descriptor
*
* @param[in] ctrl
*   Memory card control command
*
* @param[in] buffer
*   Pointer to the buffer of in/out data
*
* @return
*   Error code
******************************************************************************/
static rt_err_t rt_spiSd_control (
    rt_device_t     dev,
    rt_uint8_t      ctrl,
    void            *buffer)
{
    rt_err_t ret;
    rt_uint32_t c_size;
    rt_uint8_t n;
    rt_uint8_t *buf_res;

    ret = -RT_ERROR;
    buf_res = RT_NULL;
    switch (ctrl)
    {
    case RT_DEVICE_CTRL_SD_SYNC:
        /* Flush dirty buffer if present */
        efm_spiSd_cs(1);
        efm_spiSd_cs(0);
        ret = RT_EOK;
        break;

    case RT_DEVICE_CTRL_SD_GET_SCOUNT:
        {
            /* Allocate buffer */
            if ((buf_res = rt_malloc(SD_BLOCK_SIZE_CSD)) == RT_NULL)
            {
                sdcard_debug("SPISD: No memory for RX buffer\n");
                break;
            }
            /* Get number of sectors on the disk (32 bits) */
            if (efm_spiSd_sendCmd(CMD9, 0x00000000, buf_res))
            {
                sdcard_debug("SPISD: Get CSD failed!\n");
                break;
            }

            if ((buf_res[0] >> 6) == 0x01)
            {
                /* SDv2 */
                /* C_SIZE: Bit 48~69 */
                c_size = ((rt_uint32_t)(buf_res[7] & 0x3f) << 16) + \
                    ((rt_uint32_t)buf_res[8] << 8) + buf_res[9] + 1;
                /* Result = Capacity / Sector Size */
                *(rt_uint32_t *)buffer = (rt_uint32_t)c_size << \
                    (19 - SD_SECTOR_SIZE_SHIFT);
            }
            else
            {
                /* SDv1 or MMC */
                /* C_SIZE: Bit 62~73 */
                c_size = ((rt_uint32_t)(buf_res[6] & 0x03) << 10) + \
                    ((rt_uint16_t)buf_res[7] << 2) + (buf_res[8] >> 6) + 1;
                /* READ_BL_LEN: Bit 80~83, C_SIZE_MULT: Bit 47~49 */
                n = ((buf_res[9] & 0x03) << 1) + ((buf_res[10] & 0x80) >> 7) + \
                    2 + (buf_res[5] & 0x0f);
                /* Result = Capacity / Sector Size */
                *(rt_uint32_t *)buffer = (rt_uint32_t)c_size << \
                    (n - SD_SECTOR_SIZE_SHIFT);
            }
            ret = RT_EOK;
            break;
        }

    case RT_DEVICE_CTRL_SD_GET_SSIZE:
        /* Get sectors on the disk (16 bits) */
        *(rt_uint16_t *)buffer = SD_SECTOR_SIZE;
        ret = RT_EOK;
        break;

    case RT_DEVICE_CTRL_SD_GET_BSIZE:
        /* Get erase block size in unit of sectors (32 bits) */
        if (sdType & CT_SD2)
        {
            /* Allocate buffer */
            if ((buf_res = rt_malloc(SD_BLOCK_SIZE_SDSTAT)) == RT_NULL)
            {
                sdcard_debug("SPISD: No memory for RX buffer\n");
                break;
            }
            /* SDv2 */
            if (efm_spiSd_sendCmd(ACMD13, 0x00000000, EFM32_NO_POINTER))
            {
                sdcard_debug("SPISD: Get SD status failed!\n");
                break;
            }
            if (efm_spiSd_readBlock(buf_res, SD_BLOCK_SIZE_SDSTAT))
            {
                sdcard_debug("SPISD: Read SD status failed!\n");
                break;
            }
            /* AU_SIZE: Bit 428~431 */
            *(rt_uint32_t *)buffer = 16UL << ((buf_res[10] >> 4) + 9 - \
                SD_SECTOR_SIZE_SHIFT);
        }
        else
        {
            /* Allocate buffer */
            if ((buf_res = rt_malloc(SD_BLOCK_SIZE_CSD)) == RT_NULL)
            {
                sdcard_debug("SPISD: No memory for RX buffer\n");
                break;
            }
            /* SDv1 or MMC */
            if (efm_spiSd_sendCmd(CMD9, 0x00000000, buf_res))
            {
                sdcard_debug("SPISD: Get CSD failed!\n");
                break;
            }

            if (sdType & CT_SD1)
            {
                /* SECTOR_SIZE: Bit 39~45, WRITE_BL_LEN: Bit 22~25 (9, 10 or 11) */
                *(rt_uint32_t *)buffer = (((buf_res[10] & 0x3f) << 1) + \
                    ((rt_uint32_t)(buf_res[11] & 0x80) >> 7) + 1) << \
                    (8 + (buf_res[13] >> 6) - SD_SECTOR_SIZE_SHIFT);
            }
            else
            {
                /* ERASE_GRP_SIZE: Bit 42~46, ERASE_GRP_MULT: Bit 37~41 */
                *(rt_uint32_t *)buffer = \
                    ((rt_uint16_t)((buf_res[10] & 0x7c) >> 2) + 1) * \
                    (((buf_res[10] & 0x03) << 3) + \
                    ((buf_res[11] & 0xe0) >> 5) + 1);
            }
        }
        ret = RT_EOK;
        break;

    case RT_DEVICE_CTRL_SD_GET_TYPE:
        /* Get card type flags (1 byte) */
        *(rt_uint8_t *)buffer = sdType;
        ret = RT_EOK;
        break;

    case RT_DEVICE_CTRL_SD_GET_CSD:
        /* Receive CSD as a data block (16 bytes) */
        if (efm_spiSd_sendCmd(CMD9, 0x00000000, buffer))
        {
            sdcard_debug("SPISD: Get CSD failed!\n");
            break;
        }
        ret = RT_EOK;
        break;

    case RT_DEVICE_CTRL_SD_GET_CID:
        /* Receive CID as a data block (16 bytes) */
        if (efm_spiSd_sendCmd(CMD10, 0x00000000, buffer))
        {
            sdcard_debug("SPISD: Get CID failed!\n");
            break;
        }
        ret = RT_EOK;
        break;

    case RT_DEVICE_CTRL_SD_GET_OCR:
        /* Receive OCR as an R3 resp (4 bytes) */
        if (efm_spiSd_sendCmd(CMD58, 0x00000000, buffer))
        {
            sdcard_debug("SPISD: Get OCR failed!\n");
            break;
        }
        ret = RT_EOK;
        break;

    case RT_DEVICE_CTRL_SD_GET_SDSTAT:
        /* Receive SD statsu as a data block (64 bytes) */
        if (efm_spiSd_sendCmd(ACMD13, 0x00000000, buffer))
        {
            sdcard_debug("SPISD: Get SD status failed!\n");
            break;
        }
        if (efm_spiSd_readBlock(buffer, SD_BLOCK_SIZE_SDSTAT))
        {
            sdcard_debug("SPISD: Read SD status failed!\n");
            break;
        }
        ret = RT_EOK;
        break;

    default:
        break;
    }

    if (buf_res)
    {
        rt_free(buf_res);
    }
    return ret;
}

/***************************************************************************//**
* @brief
*   Initialize all memory card related hardware and register the device to
*  kernel
*
* @details
*
* @note
*
* @return
*   Error code
******************************************************************************/
rt_err_t efm_spiSd_init(void)
{
    struct efm32_usart_device_t *usart;

    do
    {
        /* Find SPI device */
        spi = rt_device_find(SPISD_USING_DEVICE_NAME);
        if (spi == RT_NULL)
        {
            sdcard_debug("SPISD: Can't find device %s!\n",
                SPISD_USING_DEVICE_NAME);
            break;
        }
        sdcard_debug("SPISD: Find device %s\n", SPISD_USING_DEVICE_NAME);

        /* Config chip slect pin */
        usart = (struct efm32_usart_device_t *)(spi->user_data);
        if (!(usart->state & USART_STATE_AUTOCS))
        {
            GPIO_PinModeSet(SD_CS_PORT, SD_CS_PIN, gpioModePushPull, 1);
            sdAutoCs = false;
        }

        /* Register SPI SD device */
        sd_device.type      = RT_Device_Class_MTD;
        sd_device.init      = rt_spiSd_init;
        sd_device.open      = rt_spiSd_open;
        sd_device.close     = rt_spiSd_close;
        sd_device.read      = rt_spiSd_read;
        sd_device.write     = rt_spiSd_write;
        sd_device.control   = rt_spiSd_control;
        sd_device.user_data = RT_NULL;
        rt_device_register(
            &sd_device,
            SPISD_DEVICE_NAME,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

        sdcard_debug("SPISD: HW init OK, card type %x\n", sdType);
        return RT_EOK;
    } while (0);

    /* Release buffer */
    rt_kprintf("SPISD: HW init failed!\n");
    return -RT_ERROR;
}

/***************************************************************************//**
 * @brief
 *   De-initialize memory card device
 *
 * @details
 *
 * @note
 ******************************************************************************/
void efm_spiSd_deinit(void)
{
    /* Close SPI device */
    if (spi != RT_NULL)
    {
        spi->close(spi);
        spi = RT_NULL;
        sdcard_debug("SPISD: Close device %s\n", SPISD_USING_DEVICE_NAME);
    }
    /* Delete timer */
    if (sdTimer != RT_NULL)
    {
        rt_timer_delete(sdTimer);
        sdTimer = RT_NULL;
        sdcard_debug("SPISD: Delete timer\n");
    }

    sdcard_debug("SPISD: Deinit OK\n");
}

/*******************************************************************************
 *  Export to FINSH
 ******************************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void list_sd(void)
{
    rt_uint8_t buf_res[16];
    rt_uint32_t capacity, temp32;
    rt_uint16_t temp16;

    rt_kprintf("    SD Card on %s\n", SPISD_USING_DEVICE_NAME);
    rt_kprintf(" ------------------------------\n");
    sd_device.control(&sd_device, RT_DEVICE_CTRL_SD_GET_CID, buf_res);
    rt_kprintf(" Manufacturer ID:\t%x\n", buf_res[0]);
    rt_kprintf(" OEM/Application ID:\t%x%x\n", buf_res[1], buf_res[2]);
    rt_kprintf(" Product revision:\t%x\n", buf_res[8]);
    buf_res[8] = 0;
    rt_kprintf(" Product name:\t\t%s\n", &buf_res[3]);
    rt_kprintf(" Serial number:\t\t%x%x%x%x\n", \
        buf_res[9], buf_res[10], buf_res[11], buf_res[12]);
    rt_kprintf(" Manufacturing date:\t%d.%d\n", \
        2000 + ((buf_res[13] & 0x0F) << 4) + ((buf_res[14] & 0xF0) >> 4), \
        buf_res[14] & 0x0F);
    rt_kprintf(" Card type:\t\t");
    sd_device.control(&sd_device, RT_DEVICE_CTRL_SD_GET_TYPE, buf_res);
    if (buf_res[0] == CT_MMC)
    {
        rt_kprintf("%s\n", "MMC");
    }
    else if (buf_res[0] == CT_SDC)
    {
        rt_kprintf("%s\n", "SDXC");
    }
    else if (buf_res[0] == CT_SD1)
    {
        rt_kprintf("%s\n", "SDSC");
    }
    else if (buf_res[0] == CT_SD2)
    {
        rt_kprintf("%s\n", "SDHC");
    }
    sd_device.control(&sd_device, RT_DEVICE_CTRL_SD_GET_SSIZE, &temp16);
    sd_device.control(&sd_device, RT_DEVICE_CTRL_SD_GET_SCOUNT, &temp32);
    capacity = ((temp32 & 0x0000FFFF) * temp16) >> 16;
    capacity += ((temp32 >> 16) * temp16);
    capacity >>= 4;
    rt_kprintf(" Card capacity:\t\t%dMB\n", capacity);
}
FINSH_FUNCTION_EXPORT(list_sd, list the SD card.)
#endif

#endif /* defined(EFM32_USING_SPISD) */
/***************************************************************************//**
 * @}
 ******************************************************************************/
