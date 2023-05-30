/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */

#include <string.h>
#include <board.h>

#include "drv_sd.h"


static struct mci_device *_mci_device;
static uint8_t sdio_buffer[1024];

static rt_err_t rt_mci_init(rt_device_t dev)
{
    rt_err_t result = RT_EOK;

    return result;
}

static rt_err_t rt_mci_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_mci_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_mci_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint8_t status = kStatus_Success;
    struct mci_device *mci = (struct mci_device *)dev;

    rt_mutex_take(&mci->lock, RT_WAITING_FOREVER);

    {
        /* non-aligned. */
        uint32_t i;
        rt_size_t sector_adr;
        uint8_t* copy_buffer;

        sector_adr = pos;
        copy_buffer = (uint8_t*)buffer;

        for(i=0; i<size; i++)
        {
            status=SD_ReadBlocks(&mci->card, sdio_buffer, sector_adr, 1);

            memcpy(copy_buffer, sdio_buffer, mci->card.blockSize);
            sector_adr ++;
            copy_buffer += mci->card.blockSize;
        }
    }

    rt_mutex_release(&_mci_device->lock);

    if (status == kStatus_Success) return size;

    return 0;
}

static rt_size_t rt_mci_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_uint8_t status = kStatus_Success;
    struct mci_device *mci = (struct mci_device *)dev;

    rt_mutex_take(&mci->lock, RT_WAITING_FOREVER);

    {
        /* non-aligned. */
        uint32_t i;
        rt_size_t sector_adr;
        uint8_t* copy_buffer;

        sector_adr = pos;
        copy_buffer = (uint8_t*)buffer;

        for(i = 0; i < size; i++)
        {
            memcpy(sdio_buffer, copy_buffer, mci->card.blockSize);

            status = SD_WriteBlocks(&mci->card, sdio_buffer, sector_adr, 1);

            sector_adr ++;
            copy_buffer += mci->card.blockSize;

        }
    }

    /* release and exit */
    rt_mutex_release(&_mci_device->lock);

    if (status == kStatus_Success) return size;

    return 0;
}

static rt_err_t rt_mci_control(rt_device_t dev, int cmd, void *args)
{
    struct mci_device *mci = (struct mci_device *)dev;

    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = mci->card.blockSize;
        geometry->block_size = mci->card.csd.eraseSectorSize;
        geometry->sector_count = mci->card.blockCount;
    }

    return RT_EOK;
}

void sdio_init_pins(void)
{
    const uint32_t port2_pin10_config = (
                                            IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_CARD_DET_N */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN10_IDX, port2_pin10_config); /* PORT2 PIN10 (coords: P1) is configured as SD_CARD_DET_N */
    const uint32_t port2_pin3_config = (
                                           IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_CLK */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN3_IDX, port2_pin3_config); /* PORT2 PIN3 (coords: B1) is configured as SD_CLK */
    const uint32_t port2_pin4_config = (
                                           IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_CMD */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN4_IDX, port2_pin4_config); /* PORT2 PIN4 (coords: D3) is configured as SD_CMD */
    const uint32_t port2_pin5_config = (
                                           IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_POW_EN */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN5_IDX, port2_pin5_config); /* PORT2 PIN5 (coords: C1) is configured as SD_POW_EN */
    const uint32_t port2_pin6_config = (
                                           IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_D(0) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN6_IDX, port2_pin6_config); /* PORT2 PIN6 (coords: F3) is configured as SD_D(0) */
    const uint32_t port2_pin7_config = (
                                           IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_D(1) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN7_IDX, port2_pin7_config); /* PORT2 PIN7 (coords: J2) is configured as SD_D(1) */
    const uint32_t port2_pin8_config = (
                                           IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_D(2) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN8_IDX, port2_pin8_config); /* PORT2 PIN8 (coords: F4) is configured as SD_D(2) */
    const uint32_t port2_pin9_config = (
                                           IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_D(3) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_FAST |                                    /* Fast mode, slew rate control is disabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN9_IDX, port2_pin9_config); /* PORT2 PIN9 (coords: K2) is configured as SD_D(3) */
    const uint32_t port3_pin15_config = (
                                            IOCON_PIO_FUNC2 |                                        /* Pin is configured as SD_WR_PRT */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN15_IDX, port3_pin15_config); /* PORT3 PIN15 (coords: D2) is configured as SD_WR_PRT */
}

sd_card_t g_sd;

/*! @brief Data written to the card */
uint8_t g_dataWrite[FSL_SDMMC_DEFAULT_BLOCK_SIZE * 5U];
/*! @brief Data read from the card */
uint8_t g_dataRead[FSL_SDMMC_DEFAULT_BLOCK_SIZE * 5U];

rt_err_t mci_hw_init(const char *device_name)
#if 0
{
    sd_card_t *card = &g_sd;
    bool isReadOnly;
    bool failedFlag = false;
    char ch = '0';

    /* attach main clock to SDIF */
    CLOCK_AttachClk(kMCLK_to_SDIO_CLK);
    /* need call this function to clear the halt bit in clock divider register */
    CLOCK_SetClkDiv(kCLOCK_DivSdioClk, 1U, true);

    sdio_init_pins();

    card->host.base = SDIF;
    card->host.sourceClock_Hz = CLOCK_GetFreq(kCLOCK_SDio);

    /* Init card. */
    if (SD_Init(card))
    {
        rt_kprintf("\r\nSD card init failed.\r\n");
        return -1;
    }

    rt_kprintf("\r\nRead/Write/Erase the card continuously until encounter error......\r\n");
    /* Check if card is readonly. */
    isReadOnly = SD_CheckReadOnly(card);
    if (isReadOnly)
    {
        //while (true)
        {
            /*if (failedFlag || (ch == 'q'))
            {
                break;
            }*/

            rt_kprintf("\r\nRead one data block......\r\n");
            if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, 2U, 1U))
            {
                rt_kprintf("Read one data block failed.\r\n");
                failedFlag = true;
                //continue;
            }

            rt_kprintf("Read multiple data blocks......\r\n");
            if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, 2U, 5U))
            {
                rt_kprintf("Read multiple data blocks failed.\r\n");
                failedFlag = true;
                //continue;
            }

            rt_kprintf(
                "\r\nInput 'q' to quit read process.\
                \r\nInput other char to read data blocks again.\r\n");
            //ch = GETCHAR();
            //PUTCHAR(ch);
        }
    }
    else
    {
        memset(g_dataWrite, 0x67U, sizeof(g_dataWrite));

        //while (true)
        {
            /*if (failedFlag || (ch == 'q'))
            {
                break;
            }*/

            rt_kprintf("\r\nWrite/read one data block......\r\n");
            if (kStatus_Success != SD_WriteBlocks(card, g_dataWrite, 2U, 1U))
            {
                rt_kprintf("Write one data block failed.\r\n");
                failedFlag = true;
                //continue;
            }

            memset(g_dataRead, 0U, sizeof(g_dataRead));
            if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, 2U, 1U))
            {
                rt_kprintf("Read one data block failed.\r\n");
                failedFlag = true;
                //continue;
            }

            rt_kprintf("Compare the read/write content......\r\n");
            if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
            {
                rt_kprintf("The read/write content isn't consistent.\r\n");
                failedFlag = true;
                //continue;
            }
            rt_kprintf("The read/write content is consistent.\r\n");

            rt_kprintf("Write/read multiple data blocks......\r\n");
            if (kStatus_Success != SD_WriteBlocks(card, g_dataWrite, 2U, 5U))
            {
                rt_kprintf("Write multiple data blocks failed.\r\n");
                failedFlag = true;
                //continue;
            }

            memset(g_dataRead, 0U, sizeof(g_dataRead));

            if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, 2U, 5U))
            {
                rt_kprintf("Read multiple data blocks failed.\r\n");
                failedFlag = true;
                //continue;
            }

            rt_kprintf("Compare the read/write content......\r\n");
            if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
            {
                rt_kprintf("The read/write content isn't consistent.\r\n");
                failedFlag = true;
                //continue;
            }
            rt_kprintf("The read/write content is consistent.\r\n");

            rt_kprintf("Erase multiple data blocks......\r\n");
            if (kStatus_Success != SD_EraseBlocks(card, 2U, 5U))
            {
                rt_kprintf("Erase multiple data blocks failed.\r\n");
                failedFlag = true;
                //continue;
            }

            rt_kprintf(
                "\r\nInput 'q' to quit read/write/erase process.\
                \r\nInput other char to read/write/erase data blocks again.\r\n");
            //ch = GETCHAR();
            //PUTCHAR(ch);
        }
    }
    rt_kprintf("\r\nThe example will not read/write data blocks again.\r\n");

    SD_Deinit(card);
}
#else
{
    _mci_device = (struct mci_device *)rt_malloc(sizeof(struct mci_device));
    if (_mci_device == RT_NULL)
    {
        rt_kprintf("mci_hw_init _mci_device rt_malloc failed!\n");
        return -RT_ERROR;
    }
    rt_memset(_mci_device, 0, sizeof(struct mci_device));

    /* attach main clock to SDIF */
    CLOCK_AttachClk(kMCLK_to_SDIO_CLK);
    /* need call this function to clear the halt bit in clock divider register */
    CLOCK_SetClkDiv(kCLOCK_DivSdioClk, 1U, true);

    sdio_init_pins();

    /* Save host information. */
    _mci_device->card.host.base = SDIF;
    _mci_device->card.host.sourceClock_Hz = CLOCK_GetFreq(kCLOCK_SDio);

    if (kStatus_Success != SD_Init(&_mci_device->card))
    {
        SD_Deinit(&_mci_device->card);
        memset(&_mci_device->card, 0U, sizeof(_mci_device->card));
        rt_kprintf("SD_Init failed!\n");
        return -RT_ERROR;
    }

    /*
    follow the page: https://community.nxp.com/thread/454769

    The issue concerns sdmmc library bug (I finally solved) in SD_Init() in the file sdmmc/src/fsl_sd.c:SD_SelectBusTiming()
    calls SD_SwitchFunction() which sets block size to 64bytes (512bits).Therefore SD_SetBlockSize(card, FSL_SDMMC_DEFAULT_BLOCK_SIZE)
    should be called again before SD_Init() exits.
    */

    if (kStatus_Success != SDMMC_SetBlockSize(_mci_device->card.host.base, _mci_device->card.host.transfer, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
    {
        SD_Deinit(&_mci_device->card);
        memset(&_mci_device->card, 0U, sizeof(_mci_device->card));
        rt_kprintf("SD_Init failed!\n");
        return -RT_ERROR;
    }

    /* initialize mutex lock */
    rt_mutex_init(&_mci_device->lock, device_name, RT_IPC_FLAG_FIFO);
    /* create finish event */
    _mci_device->finish_event = rt_event_create(device_name, RT_IPC_FLAG_FIFO);

    /* register sdcard device */
    _mci_device->parent.type    = RT_Device_Class_Block;

    _mci_device->geometry.bytes_per_sector = 0;
    _mci_device->geometry.sector_count = 0;
    _mci_device->geometry.block_size = 0;

    _mci_device->parent.init    = rt_mci_init;
    _mci_device->parent.open    = rt_mci_open;
    _mci_device->parent.close   = rt_mci_close;
    _mci_device->parent.read    = rt_mci_read;
    _mci_device->parent.write   = rt_mci_write;
    _mci_device->parent.control = rt_mci_control;

    /* no private, no callback */
    _mci_device->parent.user_data = RT_NULL;
    _mci_device->parent.rx_indicate = RT_NULL;
    _mci_device->parent.tx_complete = RT_NULL;

    rt_device_register(&_mci_device->parent, device_name,
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE );
    return RT_EOK;
}
#endif
