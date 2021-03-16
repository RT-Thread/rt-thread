/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-04-17     Bernard      first version.
 * 2010-07-15     aozima       Modify read/write according new block driver interface.
 * 2012-02-01     aozima       use new RT-Thread SPI drivers.
 * 2012-04-11     aozima       get max. data transfer rate from CSD[TRAN_SPEED].
 * 2012-05-21     aozima       update MMC card support.
 * 2018-03-09     aozima       fixed CSD Version 2.0 sector count calc.
 */

#include <string.h>
#include "spi_msd.h"

//#define MSD_TRACE

#ifdef MSD_TRACE
    #define MSD_DEBUG(...)         rt_kprintf("[MSD] %d ", rt_tick_get()); rt_kprintf(__VA_ARGS__);
#else
    #define MSD_DEBUG(...)
#endif /* #ifdef MSD_TRACE */

#define DUMMY                 0xFF

#define CARD_NCR_MAX          9

#define CARD_NRC              1
#define CARD_NCR              1

static struct msd_device  _msd_device;

/* function define */
static rt_bool_t rt_tick_timeout(rt_tick_t tick_start, rt_tick_t tick_long);

static rt_err_t MSD_take_owner(struct rt_spi_device *spi_device);

static rt_err_t _wait_token(struct rt_spi_device *device, uint8_t token);
static rt_err_t _wait_ready(struct rt_spi_device *device);
static rt_err_t  rt_msd_init(rt_device_t dev);
static rt_err_t  rt_msd_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t  rt_msd_close(rt_device_t dev);
static rt_size_t rt_msd_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static rt_size_t rt_msd_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_size_t rt_msd_sdhc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_size_t rt_msd_sdhc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static rt_err_t rt_msd_control(rt_device_t dev, int cmd, void *args);

static rt_err_t MSD_take_owner(struct rt_spi_device *spi_device)
{
    rt_err_t result;

    result = rt_mutex_take(&(spi_device->bus->lock), RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        if (spi_device->bus->owner != spi_device)
        {
            /* not the same owner as current, re-configure SPI bus */
            result = spi_device->bus->ops->configure(spi_device, &spi_device->config);
            if (result == RT_EOK)
            {
                /* set SPI bus owner */
                spi_device->bus->owner = spi_device;
            }
        }
    }

    return result;
}

static rt_bool_t rt_tick_timeout(rt_tick_t tick_start, rt_tick_t tick_long)
{
    rt_tick_t tick_end = tick_start + tick_long;
    rt_tick_t tick_now = rt_tick_get();
    rt_bool_t result = RT_FALSE;

    if (tick_end >= tick_start)
    {
        if (tick_now >= tick_end)
        {
            result = RT_TRUE;
        }
        else
        {
            result = RT_FALSE;
        }
    }
    else
    {
        if ((tick_now < tick_start) && (tick_now >= tick_end))
        {
            result = RT_TRUE;
        }
        else
        {
            result = RT_FALSE;
        }
    }

    return result;
}

static uint8_t crc7(const uint8_t *buf, int len)
{
    unsigned char   i, j, crc, ch, ch2, ch3;

    crc = 0;

    for (i = 0; i < len; i ++)
    {
        ch = buf[i];

        for (j = 0; j < 8; j ++, ch <<= 1)
        {
            ch2 = (crc & 0x40) ? 1 : 0;
            ch3 = (ch & 0x80) ? 1 : 0;

            if (ch2 ^ ch3)
            {
                crc ^= 0x04;
                crc <<= 1;
                crc |= 0x01;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

static rt_err_t _send_cmd(
    struct rt_spi_device *device,
    uint8_t cmd,
    uint32_t arg,
    uint8_t crc,
    response_type type,
    uint8_t *response
)
{
    struct rt_spi_message message;
    uint8_t cmd_buffer[8];
    uint8_t recv_buffer[sizeof(cmd_buffer)];
    uint32_t i;

    cmd_buffer[0] = DUMMY;
    cmd_buffer[1] = (cmd | 0x40);
    cmd_buffer[2] = (uint8_t)(arg >> 24);
    cmd_buffer[3] = (uint8_t)(arg >> 16);
    cmd_buffer[4] = (uint8_t)(arg >> 8);
    cmd_buffer[5] = (uint8_t)(arg);

    if (crc == 0x00)
    {
        crc = crc7(&cmd_buffer[1], 5);
        crc = (crc << 1) | 0x01;
    }
    cmd_buffer[6] = (crc);

    cmd_buffer[7] = DUMMY;

    /* initial message */
    message.send_buf = cmd_buffer;
    message.recv_buf = recv_buffer;
    message.length = sizeof(cmd_buffer);
    message.cs_take = message.cs_release = 0;

    _wait_ready(device);

    /* transfer message */
    device->bus->ops->xfer(device, &message);

    for (i = CARD_NCR; i < (CARD_NCR_MAX + 1); i++)
    {
        uint8_t send = DUMMY;

        /* initial message */
        message.send_buf = &send;
        message.recv_buf = response;
        message.length = 1;
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);

        if (0 == (response[0] & 0x80))
        {
            break;
        }
    } /* wait response */

    if ((CARD_NCR_MAX + 1) == i)
    {
        return RT_ERROR;//fail
    }

    //recieve other byte
    if (type == response_r1)
    {
        return RT_EOK;
    }
    else if (type == response_r1b)
    {
        rt_tick_t tick_start = rt_tick_get();
        uint8_t recv;

        while (1)
        {
            /* initial message */
            message.send_buf = RT_NULL;
            message.recv_buf = &recv;
            message.length = 1;
            message.cs_take = message.cs_release = 0;

            /* transfer message */
            device->bus->ops->xfer(device, &message);

            if (recv == DUMMY)
            {
                return RT_EOK;
            }

            if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(2000)))
            {
                return RT_ETIMEOUT;
            }
        }
    }
    else if (type == response_r2)
    {
        /* initial message */
        /* Prevent non-aligned address access, use recv_buffer to receive data */
        message.send_buf = RT_NULL;
        message.recv_buf = recv_buffer;
        message.length = 1;
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);
        response[1] = recv_buffer[0];
    }
    else if ((type == response_r3) || (type == response_r7))
    {
        /* initial message */
        message.send_buf = RT_NULL;
        message.recv_buf = recv_buffer;
        message.length = 4;
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);
        response[1] = recv_buffer[0];
        response[2] = recv_buffer[1];
        response[3] = recv_buffer[2];
        response[4] = recv_buffer[3];
    }
    else
    {
        return RT_ERROR; // unknow type?
    }

    return RT_EOK;
}

static rt_err_t _wait_token(struct rt_spi_device *device, uint8_t token)
{
    struct rt_spi_message message;
    rt_tick_t tick_start;
    uint8_t send, recv;

    tick_start = rt_tick_get();

    /* wati token */
    /* initial message */
    send = DUMMY;
    message.send_buf = &send;
    message.recv_buf = &recv;
    message.length = 1;
    message.cs_take = message.cs_release = 0;

    while (1)
    {
        /* transfer message */
        device->bus->ops->xfer(device, &message);

        if (recv == token)
        {
            return RT_EOK;
        }

        if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(CARD_WAIT_TOKEN_TIMES)))
        {
            MSD_DEBUG("[err] wait data start token timeout!\r\n");
            return RT_ETIMEOUT;
        }
    } /* wati token */
}

static rt_err_t _wait_ready(struct rt_spi_device *device)
{
    struct rt_spi_message message;
    rt_tick_t tick_start;
    uint8_t send, recv;

    tick_start = rt_tick_get();

    send = DUMMY;
    /* initial message */
    message.send_buf = &send;
    message.recv_buf = &recv;
    message.length = 1;
    message.cs_take = message.cs_release = 0;

    while (1)
    {
        /* transfer message */
        device->bus->ops->xfer(device, &message);

        if (recv == DUMMY)
        {
            return RT_EOK;
        }

        if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(1000)))
        {
            MSD_DEBUG("[err] wait ready timeout!\r\n");
            return RT_ETIMEOUT;
        }
    }
}

static rt_err_t _read_block(struct rt_spi_device *device, void *buffer, uint32_t block_size)
{
    struct rt_spi_message message;
    rt_err_t result;

    /* wati token */
    result = _wait_token(device, MSD_TOKEN_READ_START);
    if (result != RT_EOK)
    {
        return result;
    }

    /* read data */
    {
        /* initial message */
        message.send_buf = RT_NULL;
        message.recv_buf = buffer;
        message.length = block_size;
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);
    } /* read data */

    /* get crc */
    {
        uint8_t recv_buffer[2];

        /* initial message */
        message.send_buf = RT_NULL;
        message.recv_buf = recv_buffer;
        message.length = 2;
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);
    } /* get crc */

    return RT_EOK;
}

static rt_err_t _write_block(struct rt_spi_device *device, const void *buffer, uint32_t block_size, uint8_t token)
{
    struct rt_spi_message message;
    uint8_t send_buffer[16];

    rt_memset(send_buffer, DUMMY, sizeof(send_buffer));
    send_buffer[sizeof(send_buffer) - 1] = token;

    /* send start block token */
    {
        /* initial message */
        message.send_buf = send_buffer;
        message.recv_buf = RT_NULL;
        message.length = sizeof(send_buffer);
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);
    }

    /* send data */
    {
        /* initial message */
        message.send_buf = buffer;
        message.recv_buf = RT_NULL;
        message.length = block_size;
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);
    }

    /* put crc and get data response */
    {
        uint8_t recv_buffer[3];
        uint8_t response;

        /* initial message */
        message.send_buf = send_buffer;
        message.recv_buf = recv_buffer;
        message.length = sizeof(recv_buffer);
        message.cs_take = message.cs_release = 0;

        /* transfer message */
        device->bus->ops->xfer(device, &message);

//        response = 0x0E & recv_buffer[2];
        response = MSD_GET_DATA_RESPONSE(recv_buffer[2]);
        if (response != MSD_DATA_OK)
        {
            MSD_DEBUG("[err] write block fail! data response : 0x%02X\r\n", response);
            return RT_ERROR;
        }
    }

    /* wati ready */
    return _wait_ready(device);
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops msd_ops =
{
    rt_msd_init,
    rt_msd_open,
    rt_msd_close,
    rt_msd_read,
    rt_msd_write,
    rt_msd_control
};

const static struct rt_device_ops msd_sdhc_ops =
{
    rt_msd_init,
    rt_msd_open,
    rt_msd_close,
    rt_msd_sdhc_read,
    rt_msd_sdhc_write,
    rt_msd_control
};
#endif

/* RT-Thread Device Driver Interface */
static rt_err_t rt_msd_init(rt_device_t dev)
{
    struct msd_device *msd = (struct msd_device *)dev;
    uint8_t response[MSD_RESPONSE_MAX_LEN];
    rt_err_t result = RT_EOK;
    rt_tick_t tick_start;
    uint32_t OCR;

    if (msd->spi_device == RT_NULL)
    {
        MSD_DEBUG("[err] the SPI SD device has no SPI!\r\n");
        return RT_EIO;
    }

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible Modes 0 */
        cfg.max_hz = 1000 * 400; /* 400kbit/s */
        rt_spi_configure(msd->spi_device, &cfg);
    } /* config spi */

    /* init SD card */
    {
        struct rt_spi_message message;

        result = MSD_take_owner(msd->spi_device);

        if (result != RT_EOK)
        {
            goto _exit;
        }

        rt_spi_release(msd->spi_device);

        /* The host shall supply power to the card so that the voltage is reached to Vdd_min within 250ms and
           start to supply at least 74 SD clocks to the SD card with keeping CMD line to high.
           In case of SPI mode, CS shall be held to high during 74 clock cycles. */
        {
            uint8_t send_buffer[100]; /* 100byte > 74 clock */

            /* initial message */
            memset(send_buffer, DUMMY, sizeof(send_buffer));
            message.send_buf = send_buffer;
            message.recv_buf = RT_NULL;
            message.length = sizeof(send_buffer);
            message.cs_take = message.cs_release = 0;

            /* transfer message */
            msd->spi_device->bus->ops->xfer(msd->spi_device, &message);
        } /* send 74 clock */

        /* Send CMD0 (GO_IDLE_STATE) to put MSD in SPI mode */
        {
            tick_start = rt_tick_get();

            while (1)
            {
                rt_spi_take(msd->spi_device);
                result = _send_cmd(msd->spi_device, GO_IDLE_STATE, 0x00, 0x95, response_r1, response);
                rt_spi_release(msd->spi_device);

                if ((result == RT_EOK) && (response[0] == MSD_IN_IDLE_STATE))
                {
                    break;
                }

                if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(CARD_TRY_TIMES)))
                {
                    MSD_DEBUG("[err] SD card goto IDLE mode timeout!\r\n");
                    result = RT_ETIMEOUT;
                    goto _exit;
                }
            }

            MSD_DEBUG("[info] SD card goto IDLE mode OK!\r\n");
        } /* Send CMD0 (GO_IDLE_STATE) to put MSD in SPI mode */

        /* CMD8 */
        {
            tick_start = rt_tick_get();

            do
            {
                rt_spi_take(msd->spi_device);
                result = _send_cmd(msd->spi_device, SEND_IF_COND, 0x01AA, 0x87, response_r7, response);
                rt_spi_release(msd->spi_device);

                if (result == RT_EOK)
                {
                    MSD_DEBUG("[info] CMD8 response : 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
                              response[0], response[1], response[2], response[3], response[4]);

                    if (response[0] & (1 << 2))
                    {
                        /* illegal command, SD V1.x or MMC card */
                        MSD_DEBUG("[info] CMD8 is illegal command.\r\n");
                        MSD_DEBUG("[info] maybe Ver1.X SD Memory Card or MMC card!\r\n");
                        msd->card_type = MSD_CARD_TYPE_SD_V1_X;
                        break;
                    }
                    else
                    {
                        /* SD V2.0 or later or SDHC or SDXC memory card! */
                        MSD_DEBUG("[info] Ver2.00 or later or SDHC or SDXC memory card!\r\n");
                        msd->card_type = MSD_CARD_TYPE_SD_V2_X;
                    }

                    if ((0xAA == response[4]) && (0x00 == response[3]))
                    {
                        /* SD2.0 not support current voltage */
                        MSD_DEBUG("[err] VCA = 0, SD2.0 not surpport current operation voltage range\r\n");
                        result = RT_ERROR;
                        goto _exit;
                    }
                }
                else
                {
                    if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(200)))
                    {
                        MSD_DEBUG("[err] CMD8 SEND_IF_COND timeout!\r\n");
                        result = RT_ETIMEOUT;
                        goto _exit;
                    }
                }
            }
            while (0xAA != response[4]);
        } /* CMD8 */

        /* Ver1.X SD Memory Card or MMC card */
        if (msd->card_type == MSD_CARD_TYPE_SD_V1_X)
        {
            rt_bool_t is_sd_v1_x = RT_FALSE;
            rt_tick_t tick_start;

            /* try SD Ver1.x */
            while (1)
            {
                rt_spi_take(msd->spi_device);

                result = _send_cmd(msd->spi_device, READ_OCR, 0x00, 0x00, response_r3, response);
                if (result != RT_EOK)
                {
                    rt_spi_release(msd->spi_device);
                    MSD_DEBUG("[info] It maybe SD1.x or MMC But it is Not response to CMD58!\r\n");
                    goto _exit;
                }

                if (0 != (response[0] & 0xFE))
                {
                    rt_spi_release(msd->spi_device);
                    MSD_DEBUG("[info] It look CMD58 as illegal command so it is not SD card!\r\n");
                    break;
                }
                rt_spi_release(msd->spi_device);

                OCR = response[1];
                OCR = (OCR << 8) + response[2];
                OCR = (OCR << 8) + response[3];
                OCR = (OCR << 8) + response[4];
                MSD_DEBUG("[info] OCR is 0x%08X\r\n", OCR);

                if (0 == (OCR & (0x1 << 15)))
                {
                    MSD_DEBUG(("[err] SD 1.x But not surpport current voltage\r\n"));
                    result = RT_ERROR;
                    goto _exit;
                }

                /* --Send ACMD41 to make card ready */
                tick_start = rt_tick_get();

                /* try CMD55 + ACMD41 */
                while (1)
                {
                    if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(CARD_TRY_TIMES_ACMD41)))
                    {
                        rt_spi_release(msd->spi_device);
                        MSD_DEBUG("[info] try CMD55 + ACMD41 timeout! mabey MMC card!\r\n");
                        break;
                    }

                    rt_spi_take(msd->spi_device);

                    /* CMD55 APP_CMD */
                    result = _send_cmd(msd->spi_device, APP_CMD, 0x00, 0x00, response_r1, response);
                    if (result != RT_EOK)
                    {
                        rt_spi_release(msd->spi_device);
                        continue;
                    }

                    if (0 != (response[0] & 0xFE))
                    {
                        rt_spi_release(msd->spi_device);
                        MSD_DEBUG("[info] Not SD card2 , may be MMC\r\n");
                        break;
                    }

                    /* ACMD41 SD_SEND_OP_COND */
                    result = _send_cmd(msd->spi_device, SD_SEND_OP_COND, 0x00, 0x00, response_r1, response);
                    if (result != RT_EOK)
                    {
                        rt_spi_release(msd->spi_device);
                        continue;
                    }

                    if (0 != (response[0] & 0xFE))
                    {
                        rt_spi_release(msd->spi_device);
                        MSD_DEBUG("[info] Not SD card4 , may be MMC\r\n");
                        break;
                    }

                    if (0 == (response[0] & 0xFF))
                    {
                        rt_spi_release(msd->spi_device);
                        is_sd_v1_x = RT_TRUE;
                        MSD_DEBUG("[info] It is Ver1.X SD Memory Card!!!\r\n");
                        break;
                    }
                } /* try CMD55 + ACMD41 */

                break;
            } /* try SD Ver1.x */

            /* try MMC */
            if (is_sd_v1_x != RT_TRUE)
            {
                uint32_t i;

                MSD_DEBUG("[info] try MMC card!\r\n");
                rt_spi_release(msd->spi_device);

                /* send dummy clock */
                {
                    uint8_t send_buffer[100];

                    /* initial message */
                    memset(send_buffer, DUMMY, sizeof(send_buffer));
                    message.send_buf = send_buffer;
                    message.recv_buf = RT_NULL;
                    message.length = sizeof(send_buffer);
                    message.cs_take = message.cs_release = 0;

                    for (i = 0; i < 10; i++)
                    {
                        /* transfer message */
                        msd->spi_device->bus->ops->xfer(msd->spi_device, &message);
                    }
                } /* send dummy clock */

                /* send CMD0 goto IDLE state */
                tick_start = rt_tick_get();
                while (1)
                {
                    rt_spi_take(msd->spi_device);
                    result = _send_cmd(msd->spi_device, GO_IDLE_STATE, 0x00, 0x95, response_r1, response);
                    rt_spi_release(msd->spi_device);

                    if ((result == RT_EOK) && (response[0] == MSD_IN_IDLE_STATE))
                    {
                        break;
                    }

                    if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(CARD_TRY_TIMES)))
                    {
                        MSD_DEBUG("[err] SD card goto IDLE mode timeout!\r\n");
                        result = RT_ETIMEOUT;
                        goto _exit;
                    }
                } /* send CMD0 goto IDLE stat */

                /* send CMD1 */
                tick_start = rt_tick_get();
                while (1)
                {
                    rt_spi_take(msd->spi_device);
                    result = _send_cmd(msd->spi_device, SEND_OP_COND, 0x00, 0x00, response_r1, response);
                    rt_spi_release(msd->spi_device);

                    if ((result == RT_EOK) && (response[0] == MSD_RESPONSE_NO_ERROR))
                    {
                        MSD_DEBUG("[info] It is MMC card!!!\r\n");
                        msd->card_type = MSD_CARD_TYPE_MMC;
                        break;
                    }

                    if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(CARD_TRY_TIMES)))
                    {
                        MSD_DEBUG("[err] SD card goto IDLE mode timeout!\r\n");
                        result = RT_ETIMEOUT;
                        goto _exit;
                    }
                } /* send CMD1 */
            } /* try MMC */
        }
        else if (msd->card_type == MSD_CARD_TYPE_SD_V2_X)
        {
            rt_spi_take(msd->spi_device);

            result = _send_cmd(msd->spi_device, READ_OCR, 0x00, 0x00, response_r3, response);
            if (result != RT_EOK)
            {
                rt_spi_release(msd->spi_device);
                MSD_DEBUG("[err] It maybe SD2.0 But it is Not response to CMD58!\r\n");
                goto _exit;
            }

            if ((response[0] & 0xFE) != 0)
            {
                rt_spi_release(msd->spi_device);
                MSD_DEBUG("[err] It look CMD58 as illegal command so it is not SD card!\r\n");
                result = RT_ERROR;
                goto _exit;
            }

            rt_spi_release(msd->spi_device);

            OCR = response[1];
            OCR = (OCR << 8) + response[2];
            OCR = (OCR << 8) + response[3];
            OCR = (OCR << 8) + response[4];
            MSD_DEBUG("[info] OCR is 0x%08X\r\n", OCR);

            if (0 == (OCR & (0x1 << 15)))
            {
                MSD_DEBUG(("[err] SD 1.x But not surpport current voltage\r\n"));
                result = RT_ERROR;
                goto _exit;
            }

            /* --Send ACMD41 to make card ready */
            tick_start = rt_tick_get();

            /* try CMD55 + ACMD41 */
            do
            {
                rt_spi_take(msd->spi_device);
                if (rt_tick_timeout(tick_start, rt_tick_from_millisecond(CARD_TRY_TIMES_ACMD41)))
                {
                    rt_spi_release(msd->spi_device);
                    MSD_DEBUG("[err] SD Ver2.x or later try CMD55 + ACMD41 timeout!\r\n");
                    result = RT_ERROR;
                    goto _exit;
                }

                /* CMD55 APP_CMD */
                result = _send_cmd(msd->spi_device, APP_CMD, 0x00, 0x65, response_r1, response);
//                if((result != RT_EOK) || (response[0] == 0x01))
                if (result != RT_EOK)
                {
                    rt_spi_release(msd->spi_device);
                    continue;
                }

                if ((response[0] & 0xFE) != 0)
                {
                    rt_spi_release(msd->spi_device);
                    MSD_DEBUG("[err] Not SD ready!\r\n");
                    result = RT_ERROR;
                    goto _exit;
                }

                /* ACMD41 SD_SEND_OP_COND */
                result = _send_cmd(msd->spi_device, SD_SEND_OP_COND, 0x40000000, 0x77, response_r1, response);
                if (result != RT_EOK)
                {
                    rt_spi_release(msd->spi_device);
                    MSD_DEBUG("[err] ACMD41 fail!\r\n");
                    result = RT_ERROR;
                    goto _exit;
                }

                if ((response[0] & 0xFE) != 0)
                {
                    rt_spi_release(msd->spi_device);
                    MSD_DEBUG("[info] Not SD card4 , response : 0x%02X\r\n", response[0]);
//                    break;
                }
            }
            while (response[0] != MSD_RESPONSE_NO_ERROR);
            rt_spi_release(msd->spi_device);
            /* try CMD55 + ACMD41 */

            /* --Read OCR again */
            rt_spi_take(msd->spi_device);
            result = _send_cmd(msd->spi_device, READ_OCR, 0x00, 0x00, response_r3, response);
            if (result != RT_EOK)
            {
                rt_spi_release(msd->spi_device);
                MSD_DEBUG("[err] It maybe SD2.0 But it is Not response to 2nd CMD58!\r\n");
                goto _exit;
            }

            if ((response[0] & 0xFE) != 0)
            {
                rt_spi_release(msd->spi_device);
                MSD_DEBUG("[err] It look 2nd CMD58 as illegal command so it is not SD card!\r\n");
                result = RT_ERROR;
                goto _exit;
            }
            rt_spi_release(msd->spi_device);

            OCR = response[1];
            OCR = (OCR << 8) + response[2];
            OCR = (OCR << 8) + response[3];
            OCR = (OCR << 8) + response[4];
            MSD_DEBUG("[info] OCR 2nd read is 0x%08X\r\n", OCR);

            if ((OCR & 0x40000000) != 0)
            {
                MSD_DEBUG("[info] It is SD2.0 SDHC Card!!!\r\n");
                msd->card_type = MSD_CARD_TYPE_SD_SDHC;
            }
            else
            {
                MSD_DEBUG("[info] It is SD2.0 standard capacity Card!!!\r\n");
            }
        } /* MSD_CARD_TYPE_SD_V2_X */
        else
        {
            MSD_DEBUG("[err] SD card type unkonw!\r\n");
            result = RT_ERROR;
            goto _exit;
        }
    } /* init SD card */

    if (msd->card_type == MSD_CARD_TYPE_SD_SDHC)
    {
#ifdef RT_USING_DEVICE_OPS
        dev->ops   = &msd_sdhc_ops;
#else
        dev->read  = rt_msd_sdhc_read;
        dev->write = rt_msd_sdhc_write;
#endif
    }
    else
    {
#ifdef RT_USING_DEVICE_OPS
        dev->ops   = &msd_ops;
#else
        dev->read  = rt_msd_read;
        dev->write = rt_msd_write;
#endif
    }

    /* set CRC */
    {
        rt_spi_release(msd->spi_device);
        rt_spi_take(msd->spi_device);
#ifdef MSD_USE_CRC
        result = _send_cmd(msd->spi_device, CRC_ON_OFF, 0x01, 0x83, response_r1, response);
#else
        result = _send_cmd(msd->spi_device, CRC_ON_OFF, 0x00, 0x91, response_r1, response);
#endif
        rt_spi_release(msd->spi_device);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] CMD59 CRC_ON_OFF fail! response : 0x%02X\r\n", response[0]);
            result = RT_ERROR;
            goto _exit;
        }
    } /* set CRC */

    /* CMD16 SET_BLOCKLEN */
    {
        rt_spi_release(msd->spi_device);
        rt_spi_take(msd->spi_device);
        result = _send_cmd(msd->spi_device, SET_BLOCKLEN, SECTOR_SIZE, 0x00, response_r1, response);
        rt_spi_release(msd->spi_device);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] CMD16 SET_BLOCKLEN fail! response : 0x%02X\r\n", response[0]);
            result = RT_ERROR;
            goto _exit;
        }
        msd->geometry.block_size = SECTOR_SIZE;
        msd->geometry.bytes_per_sector = SECTOR_SIZE;
    }

    /* read CSD */
    {
        uint8_t CSD_buffer[MSD_CSD_LEN];

        rt_spi_take(msd->spi_device);
//        result = _send_cmd(msd->spi_device, SEND_CSD, 0x00, 0xAF, response_r1, response);
        result = _send_cmd(msd->spi_device, SEND_CSD, 0x00, 0x00, response_r1, response);

        if (result != RT_EOK)
        {
            rt_spi_release(msd->spi_device);
            MSD_DEBUG("[err] CMD9 SEND_CSD timeout!\r\n");
            goto _exit;
        }

        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            rt_spi_release(msd->spi_device);
            MSD_DEBUG("[err] CMD9 SEND_CSD fail! response : 0x%02X\r\n", response[0]);
            result = RT_ERROR;
            goto _exit;
        }

        result = _read_block(msd->spi_device, CSD_buffer, MSD_CSD_LEN);
        rt_spi_release(msd->spi_device);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[err] read CSD fail!\r\n");
            goto _exit;
        }

        /* Analyze CSD */
        {
            uint8_t  CSD_STRUCTURE;
            uint32_t C_SIZE;
            uint32_t card_capacity;

            uint8_t  tmp8;
            uint16_t tmp16;
            uint32_t tmp32;

            /* get CSD_STRUCTURE */
            tmp8 = CSD_buffer[0] & 0xC0; /* 0b11000000 */
            CSD_STRUCTURE = tmp8 >> 6;

            /* MMC CSD Analyze. */
            if (msd->card_type == MSD_CARD_TYPE_MMC)
            {
                uint8_t C_SIZE_MULT;
                uint8_t READ_BL_LEN;

                if (CSD_STRUCTURE > 2)
                {
                    MSD_DEBUG("[err] bad CSD Version : %d\r\n", CSD_STRUCTURE);
                    result = RT_ERROR;
                    goto _exit;
                }

                if (CSD_STRUCTURE == 0)
                {
                    MSD_DEBUG("[info] CSD version No. 1.0\r\n");
                }
                else if (CSD_STRUCTURE == 1)
                {
                    MSD_DEBUG("[info] CSD version No. 1.1\r\n");
                }
                else if (CSD_STRUCTURE == 2)
                {
                    MSD_DEBUG("[info] CSD version No. 1.2\r\n");
                }

                /* get TRAN_SPEED 8bit [103:96] */
                tmp8 = CSD_buffer[3];
                tmp8 &= 0x03; /* [2:0] transfer rate unit.*/
                if (tmp8 == 0)
                {
                    msd->max_clock = 100 * 1000; /* 0=100kbit/s. */
                }
                else if (tmp8 == 1)
                {
                    msd->max_clock = 1 * 1000 * 1000; /* 1=1Mbit/s. */
                }
                else if (tmp8 == 2)
                {
                    msd->max_clock = 10 * 1000 * 1000; /* 2=10Mbit/s. */
                }
                else if (tmp8 == 3)
                {
                    msd->max_clock = 100 * 1000 * 1000; /* 3=100Mbit/s. */
                }
                if (tmp8 == 0)
                {
                    MSD_DEBUG("[info] TRAN_SPEED: 0x%02X, %dkbit/s.\r\n", tmp8, msd->max_clock / 1000);
                }
                else
                {
                    MSD_DEBUG("[info] TRAN_SPEED: 0x%02X, %dMbit/s.\r\n", tmp8, msd->max_clock / 1000 / 1000);
                }

                /* get READ_BL_LEN 4bit [83:80] */
                tmp8 = CSD_buffer[5] & 0x0F; /* 0b00001111; */
                READ_BL_LEN = tmp8;          /* 4 bit */
                MSD_DEBUG("[info] CSD : READ_BL_LEN : %d %dbyte\r\n", READ_BL_LEN, (1 << READ_BL_LEN));

                /* get C_SIZE 12bit [73:62] */
                tmp16 = CSD_buffer[6] & 0x03; /* get [73:72] 0b00000011 */
                tmp16 = tmp16 << 8;
                tmp16 += CSD_buffer[7];       /* get [71:64] */
                tmp16 = tmp16 << 2;
                tmp8 = CSD_buffer[8] & 0xC0;  /* get [63:62] 0b11000000 */
                tmp8 = tmp8 >> 6;
                tmp16 = tmp16 + tmp8;
                C_SIZE = tmp16;             //12 bit
                MSD_DEBUG("[info] CSD : C_SIZE : %d\r\n", C_SIZE);

                /* get C_SIZE_MULT 3bit [49:47] */
                tmp8 = CSD_buffer[9] & 0x03;//0b00000011;
                tmp8 = tmp8 << 1;
                tmp8 = tmp8 + ((CSD_buffer[10] & 0x80/*0b10000000*/) >> 7);
                C_SIZE_MULT = tmp8;         // 3 bit
                MSD_DEBUG("[info] CSD : C_SIZE_MULT : %d\r\n", C_SIZE_MULT);

                /* memory capacity = BLOCKNR * BLOCK_LEN */
                /* BLOCKNR = (C_SIZE+1) * MULT */
                /* MULT = 2^(C_SIZE_MULT+2) */
                /* BLOCK_LEN = 2^READ_BL_LEN */
                card_capacity = (1 << READ_BL_LEN) * ((C_SIZE + 1) * (1 << (C_SIZE_MULT + 2)));
                msd->geometry.sector_count = card_capacity / msd->geometry.bytes_per_sector;
                MSD_DEBUG("[info] card capacity : %d Mbyte\r\n", card_capacity / (1024 * 1024));
            }
            else /* SD CSD Analyze. */
            {
                if (CSD_STRUCTURE == 0)
                {
                    uint8_t C_SIZE_MULT;
                    uint8_t READ_BL_LEN;

                    MSD_DEBUG("[info] CSD Version 1.0\r\n");

                    /* get TRAN_SPEED 8bit [103:96] */
                    tmp8 = CSD_buffer[3];
                    if (tmp8 == 0x32)
                    {
                        msd->max_clock = 1000 * 1000 * 10; /* 10Mbit/s. */
                    }
                    else if (tmp8 == 0x5A)
                    {
                        msd->max_clock = 1000 * 1000 * 50; /* 50Mbit/s. */
                    }
                    else
                    {
                        msd->max_clock = 1000 * 1000 * 1; /* 1Mbit/s default. */
                    }
                    MSD_DEBUG("[info] TRAN_SPEED: 0x%02X, %dMbit/s.\r\n", tmp8, msd->max_clock / 1000 / 1000);

                    /* get READ_BL_LEN 4bit [83:80] */
                    tmp8 = CSD_buffer[5] & 0x0F; /* 0b00001111; */
                    READ_BL_LEN = tmp8;          /* 4 bit */
                    MSD_DEBUG("[info] CSD : READ_BL_LEN : %d %dbyte\r\n", READ_BL_LEN, (1 << READ_BL_LEN));

                    /* get C_SIZE 12bit [73:62] */
                    tmp16 = CSD_buffer[6] & 0x03; /* get [73:72] 0b00000011 */
                    tmp16 = tmp16 << 8;
                    tmp16 += CSD_buffer[7];       /* get [71:64] */
                    tmp16 = tmp16 << 2;
                    tmp8 = CSD_buffer[8] & 0xC0;  /* get [63:62] 0b11000000 */
                    tmp8 = tmp8 >> 6;
                    tmp16 = tmp16 + tmp8;
                    C_SIZE = tmp16;             //12 bit
                    MSD_DEBUG("[info] CSD : C_SIZE : %d\r\n", C_SIZE);

                    /* get C_SIZE_MULT 3bit [49:47] */
                    tmp8 = CSD_buffer[9] & 0x03;//0b00000011;
                    tmp8 = tmp8 << 1;
                    tmp8 = tmp8 + ((CSD_buffer[10] & 0x80/*0b10000000*/) >> 7);
                    C_SIZE_MULT = tmp8;         // 3 bit
                    MSD_DEBUG("[info] CSD : C_SIZE_MULT : %d\r\n", C_SIZE_MULT);

                    /* memory capacity = BLOCKNR * BLOCK_LEN */
                    /* BLOCKNR = (C_SIZE+1) * MULT */
                    /* MULT = 2^(C_SIZE_MULT+2) */
                    /* BLOCK_LEN = 2^READ_BL_LEN */
                    card_capacity = (1 << READ_BL_LEN) * ((C_SIZE + 1) * (1 << (C_SIZE_MULT + 2)));
                    msd->geometry.sector_count = card_capacity / msd->geometry.bytes_per_sector;
                    MSD_DEBUG("[info] card capacity : %d Mbyte\r\n", card_capacity / (1024 * 1024));
                }
                else if (CSD_STRUCTURE == 1)
                {
                    MSD_DEBUG("[info] CSD Version 2.0\r\n");

                    /* get TRAN_SPEED 8bit [103:96] */
                    tmp8 = CSD_buffer[3];
                    if (tmp8 == 0x32)
                    {
                        msd->max_clock = 1000 * 1000 * 10; /* 10Mbit/s. */
                    }
                    else if (tmp8 == 0x5A)
                    {
                        msd->max_clock = 1000 * 1000 * 50; /* 50Mbit/s. */
                    }
                    else if (tmp8 == 0x0B)
                    {
                        msd->max_clock = 1000 * 1000 * 100; /* 100Mbit/s. */
                        /* UHS50 Card sets TRAN_SPEED to 0Bh (100Mbit/sec), */
                        /* for both SDR50 and DDR50 modes. */
                    }
                    else if (tmp8 == 0x2B)
                    {
                        msd->max_clock = 1000 * 1000 * 200; /* 200Mbit/s. */
                        /* UHS104 Card sets TRAN_SPEED to 2Bh (200Mbit/sec). */
                    }
                    else
                    {
                        msd->max_clock = 1000 * 1000 * 1; /* 1Mbit/s default. */
                    }
                    MSD_DEBUG("[info] TRAN_SPEED: 0x%02X, %dMbit/s.\r\n", tmp8, msd->max_clock / 1000 / 1000);

                    /* get C_SIZE 22bit [69:48] */
                    tmp32 = CSD_buffer[7] & 0x3F; /* 0b00111111 */
                    tmp32 = tmp32 << 8;
                    tmp32 += CSD_buffer[8];
                    tmp32 = tmp32 << 8;
                    tmp32 += CSD_buffer[9];
                    C_SIZE = tmp32;
                    MSD_DEBUG("[info] CSD : C_SIZE : %d\r\n", C_SIZE);

                    /* memory capacity = (C_SIZE+1) * 512K byte */
                    card_capacity = (C_SIZE + 1) / 2; /* unit : Mbyte */
                    msd->geometry.sector_count = (C_SIZE + 1) * 1024; /* 512KB = 1024sector */
                    MSD_DEBUG("[info] card capacity : %d.%d Gbyte\r\n", card_capacity / 1024, (card_capacity % 1024) * 100 / 1024);
                    MSD_DEBUG("[info] sector_count : %d\r\n", msd->geometry.sector_count);
                }
                else
                {
                    MSD_DEBUG("[err] bad CSD Version : %d\r\n", CSD_STRUCTURE);
                    result = RT_ERROR;
                    goto _exit;
                }
            } /* SD CSD Analyze. */
        } /* Analyze CSD */

    } /* read CSD */

    /* config spi to high speed */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible Modes 0 */
        cfg.max_hz = msd->max_clock;
        rt_spi_configure(msd->spi_device, &cfg);
    } /* config spi */

_exit:
    rt_spi_release(msd->spi_device);
    rt_mutex_release(&(msd->spi_device->bus->lock));
    return result;
}

static rt_err_t rt_msd_open(rt_device_t dev, rt_uint16_t oflag)
{
//    struct msd_device * msd = (struct msd_device *)dev;
    return RT_EOK;
}

static rt_err_t rt_msd_close(rt_device_t dev)
{
//    struct msd_device * msd = (struct msd_device *)dev;
    return RT_EOK;
}

static rt_size_t rt_msd_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct msd_device *msd = (struct msd_device *)dev;
    uint8_t response[MSD_RESPONSE_MAX_LEN];
    rt_err_t result = RT_EOK;

    result = MSD_take_owner(msd->spi_device);

    if (result != RT_EOK)
    {
        goto _exit;
    }

    /* SINGLE_BLOCK? */
    if (size == 1)
    {
        rt_spi_take(msd->spi_device);

        result = _send_cmd(msd->spi_device, READ_SINGLE_BLOCK, pos * msd->geometry.bytes_per_sector, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] read SINGLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
            goto _exit;
        }

        result = _read_block(msd->spi_device, buffer, msd->geometry.bytes_per_sector);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[err] read SINGLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
        }
    }
    else if (size > 1)
    {
        uint32_t i;

        rt_spi_take(msd->spi_device);

        result = _send_cmd(msd->spi_device, READ_MULTIPLE_BLOCK, pos * msd->geometry.bytes_per_sector, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] read READ_MULTIPLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
            goto _exit;
        }

        for (i = 0; i < size; i++)
        {
            result = _read_block(msd->spi_device,
                                 (uint8_t *)buffer + msd->geometry.bytes_per_sector * i,
                                 msd->geometry.bytes_per_sector);
            if (result != RT_EOK)
            {
                MSD_DEBUG("[err] read READ_MULTIPLE_BLOCK #%d fail!\r\n", pos);
                size = i;
                break;
            }
        }

        /* send CMD12 stop transfer */
        result = _send_cmd(msd->spi_device, STOP_TRANSMISSION, 0x00, 0x00, response_r1b, response);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[err] read READ_MULTIPLE_BLOCK, send stop token fail!\r\n");
        }
    } /* READ_MULTIPLE_BLOCK */

_exit:
    /* release and exit */
    rt_spi_release(msd->spi_device);
    rt_mutex_release(&(msd->spi_device->bus->lock));

    return size;
}

static rt_size_t rt_msd_sdhc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct msd_device *msd = (struct msd_device *)dev;
    uint8_t response[MSD_RESPONSE_MAX_LEN];
    rt_err_t result = RT_EOK;

    result = MSD_take_owner(msd->spi_device);

    if (result != RT_EOK)
    {
        goto _exit;
    }

    /* SINGLE_BLOCK? */
    if (size == 1)
    {
        rt_spi_take(msd->spi_device);

        result = _send_cmd(msd->spi_device, READ_SINGLE_BLOCK, pos, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] read SINGLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
            goto _exit;
        }

        result = _read_block(msd->spi_device, buffer, msd->geometry.bytes_per_sector);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[err] read SINGLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
        }
    }
    else if (size > 1)
    {
        uint32_t i;

        rt_spi_take(msd->spi_device);

        result = _send_cmd(msd->spi_device, READ_MULTIPLE_BLOCK, pos, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] read READ_MULTIPLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
            goto _exit;
        }

        for (i = 0; i < size; i++)
        {
            result = _read_block(msd->spi_device,
                                 (uint8_t *)buffer + msd->geometry.bytes_per_sector * i,
                                 msd->geometry.bytes_per_sector);
            if (result != RT_EOK)
            {
                MSD_DEBUG("[err] read READ_MULTIPLE_BLOCK #%d fail!\r\n", pos);
                size = i;
                break;
            }
        }

        /* send CMD12 stop transfer */
        result = _send_cmd(msd->spi_device, STOP_TRANSMISSION, 0x00, 0x00, response_r1b, response);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[err] read READ_MULTIPLE_BLOCK, send stop token fail!\r\n");
        }
    } /* READ_MULTIPLE_BLOCK */

_exit:
    /* release and exit */
    rt_spi_release(msd->spi_device);
    rt_mutex_release(&(msd->spi_device->bus->lock));

    return size;
}

static rt_size_t rt_msd_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct msd_device *msd = (struct msd_device *)dev;
    uint8_t response[MSD_RESPONSE_MAX_LEN];
    rt_err_t result;

    result = MSD_take_owner(msd->spi_device);

    if (result != RT_EOK)
    {
        MSD_DEBUG("[err] get SPI owner fail!\r\n");
        goto _exit;
    }


    /* SINGLE_BLOCK? */
    if (size == 1)
    {
        rt_spi_take(msd->spi_device);
        result = _send_cmd(msd->spi_device, WRITE_BLOCK, pos * msd->geometry.bytes_per_sector, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] CMD WRITE_BLOCK fail!\r\n");
            size = 0;
            goto _exit;
        }

        result = _write_block(msd->spi_device, buffer, msd->geometry.bytes_per_sector, MSD_TOKEN_WRITE_SINGLE_START);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[err] write SINGLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
        }
    }
    else if (size > 1)
    {
        struct rt_spi_message message;
        uint32_t i;

        rt_spi_take(msd->spi_device);

#ifdef MSD_USE_PRE_ERASED
        if (msd->card_type != MSD_CARD_TYPE_MMC)
        {
            /* CMD55 APP_CMD */
            result = _send_cmd(msd->spi_device, APP_CMD, 0x00, 0x00, response_r1, response);
            if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
            {
                MSD_DEBUG("[err] CMD55 APP_CMD fail!\r\n");
                size = 0;
                goto _exit;
            }

            /* ACMD23 Pre-erased */
            result = _send_cmd(msd->spi_device, SET_WR_BLK_ERASE_COUNT, size, 0x00, response_r1, response);
            if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
            {
                MSD_DEBUG("[err] ACMD23 SET_BLOCK_COUNT fail!\r\n");
                size = 0;
                goto _exit;
            }
        }
#endif

        result = _send_cmd(msd->spi_device, WRITE_MULTIPLE_BLOCK, pos * msd->geometry.bytes_per_sector, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] CMD WRITE_MULTIPLE_BLOCK fail!\r\n");
            size = 0;
            goto _exit;
        }

        /* write all block */
        for (i = 0; i < size; i++)
        {
            result = _write_block(msd->spi_device,
                                  (const uint8_t *)buffer + msd->geometry.bytes_per_sector * i,
                                  msd->geometry.bytes_per_sector,
                                  MSD_TOKEN_WRITE_MULTIPLE_START);
            if (result != RT_EOK)
            {
                MSD_DEBUG("[err] write SINGLE_BLOCK #%d fail!\r\n", pos);
                size = i;
                break;
            }
        } /* write all block */

        /* send stop token */
        {
            uint8_t send_buffer[18];

            rt_memset(send_buffer, DUMMY, sizeof(send_buffer));
            send_buffer[sizeof(send_buffer) - 1] = MSD_TOKEN_WRITE_MULTIPLE_STOP;

            /* initial message */
            message.send_buf = send_buffer;
            message.recv_buf = RT_NULL;
            message.length = sizeof(send_buffer);
            message.cs_take = message.cs_release = 0;

            /* transfer message */
            msd->spi_device->bus->ops->xfer(msd->spi_device, &message);
        }

        /* wait ready */
        result = _wait_ready(msd->spi_device);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[warning] wait WRITE_MULTIPLE_BLOCK stop token ready timeout!\r\n");
        }
    } /* size > 1 */

_exit:
    /* release and exit */
    rt_spi_release(msd->spi_device);
    rt_mutex_release(&(msd->spi_device->bus->lock));

    return size;
}

static rt_size_t rt_msd_sdhc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct msd_device *msd = (struct msd_device *)dev;
    uint8_t response[MSD_RESPONSE_MAX_LEN];
    rt_err_t result;

    result = MSD_take_owner(msd->spi_device);

    if (result != RT_EOK)
    {
        goto _exit;
    }

    /* SINGLE_BLOCK? */
    if (size == 1)
    {
        rt_spi_take(msd->spi_device);
        result = _send_cmd(msd->spi_device, WRITE_BLOCK, pos, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] CMD WRITE_BLOCK fail!\r\n");
            size = 0;
            goto _exit;
        }

        result = _write_block(msd->spi_device, buffer, msd->geometry.bytes_per_sector, MSD_TOKEN_WRITE_SINGLE_START);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[err] write SINGLE_BLOCK #%d fail!\r\n", pos);
            size = 0;
        }
    }
    else if (size > 1)
    {
        struct rt_spi_message message;
        uint32_t i;

        rt_spi_take(msd->spi_device);

#ifdef MSD_USE_PRE_ERASED
        /* CMD55 APP_CMD */
        result = _send_cmd(msd->spi_device, APP_CMD, 0x00, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] CMD55 APP_CMD fail!\r\n");
            size = 0;
            goto _exit;
        }

        /* ACMD23 Pre-erased */
        result = _send_cmd(msd->spi_device, SET_WR_BLK_ERASE_COUNT, size, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] ACMD23 SET_BLOCK_COUNT fail!\r\n");
            size = 0;
            goto _exit;
        }
#endif

        result = _send_cmd(msd->spi_device, WRITE_MULTIPLE_BLOCK, pos, 0x00, response_r1, response);
        if ((result != RT_EOK) || (response[0] != MSD_RESPONSE_NO_ERROR))
        {
            MSD_DEBUG("[err] CMD WRITE_MULTIPLE_BLOCK fail!\r\n");
            size = 0;
            goto _exit;
        }

        /* write all block */
        for (i = 0; i < size; i++)
        {
            result = _write_block(msd->spi_device,
                                  (const uint8_t *)buffer + msd->geometry.bytes_per_sector * i,
                                  msd->geometry.bytes_per_sector,
                                  MSD_TOKEN_WRITE_MULTIPLE_START);
            if (result != RT_EOK)
            {
                MSD_DEBUG("[err] write MULTIPLE_BLOCK #%d fail!\r\n", pos);
                size = i;
                break;
            }
        } /* write all block */

        /* send stop token */
        {
            uint8_t send_buffer[18];

            rt_memset(send_buffer, DUMMY, sizeof(send_buffer));
            send_buffer[sizeof(send_buffer) - 1] = MSD_TOKEN_WRITE_MULTIPLE_STOP;

            /* initial message */
            message.send_buf = send_buffer;
            message.recv_buf = RT_NULL;
            message.length = sizeof(send_buffer);
            message.cs_take = message.cs_release = 0;

            /* transfer message */
            msd->spi_device->bus->ops->xfer(msd->spi_device, &message);
        }

        result = _wait_ready(msd->spi_device);
        if (result != RT_EOK)
        {
            MSD_DEBUG("[warning] wait WRITE_MULTIPLE_BLOCK stop token ready timeout!\r\n");
        }
    } /* size > 1 */

_exit:
    /* release and exit */
    rt_spi_release(msd->spi_device);
    rt_mutex_release(&(msd->spi_device->bus->lock));

    return size;
}

static rt_err_t rt_msd_control(rt_device_t dev, int cmd, void *args)
{
    struct msd_device *msd = (struct msd_device *)dev;

    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = msd->geometry.bytes_per_sector;
        geometry->block_size = msd->geometry.block_size;
        geometry->sector_count = msd->geometry.sector_count;
    }

    return RT_EOK;
}

rt_err_t msd_init(const char *sd_device_name, const char *spi_device_name)
{
    rt_err_t result = RT_EOK;
    struct rt_spi_device *spi_device;

    spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);
    if (spi_device == RT_NULL)
    {
        MSD_DEBUG("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }
    rt_memset(&_msd_device, 0, sizeof(_msd_device));
    _msd_device.spi_device = spi_device;

    /* register sdcard device */
    _msd_device.parent.type    = RT_Device_Class_Block;

    _msd_device.geometry.bytes_per_sector = 0;
    _msd_device.geometry.sector_count = 0;
    _msd_device.geometry.block_size = 0;

#ifdef RT_USING_DEVICE_OPS
    _msd_device.parent.ops     = &msd_ops;
#else
    _msd_device.parent.init    = rt_msd_init;
    _msd_device.parent.open    = rt_msd_open;
    _msd_device.parent.close   = rt_msd_close;
    _msd_device.parent.read    = RT_NULL;
    _msd_device.parent.write   = RT_NULL;
    _msd_device.parent.control = rt_msd_control;
#endif

    /* no private, no callback */
    _msd_device.parent.user_data = RT_NULL;
    _msd_device.parent.rx_indicate = RT_NULL;
    _msd_device.parent.tx_complete = RT_NULL;

    result = rt_device_register(&_msd_device.parent, sd_device_name,
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    return result;
}
