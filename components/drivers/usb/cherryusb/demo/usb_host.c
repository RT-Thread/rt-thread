/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"
#include "usbh_hid.h"
#include "usbh_msc.h"

// net class demos use socket api

#ifdef CONFIG_TEST_USBH_SERIAL
#define SERIAL_TEST_LEN (1 * 1024)

#if SERIAL_TEST_LEN >= CONFIG_USBHOST_SERIAL_RX_SIZE
#error SERIAL_TEST_LEN is larger than CONFIG_USBHOST_SERIAL_RX_SIZE, please reduce SERIAL_TEST_LEN or increase CONFIG_USBHOST_SERIAL_RX_SIZE
#endif

volatile uint32_t serial_tx_bytes = 0;
volatile uint32_t serial_rx_bytes = 0;
volatile bool serial_is_opened = false;

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t serial_tx_buffer[SERIAL_TEST_LEN];
uint8_t serial_rx_data[SERIAL_TEST_LEN];

#ifdef CONFIG_TEST_USBH_CDC_SPEED
#define TEST_LEN   (16 * 1024)
#define TEST_COUNT (10240)

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t serial_speed_buffer[TEST_LEN];
#endif

static void usbh_serial_thread(CONFIG_USB_OSAL_THREAD_SET_ARGV)
{
    int ret;
    struct usbh_serial *serial;
    bool serial_test_success = false;

    serial = usbh_serial_open("/dev/ttyACM0", USBH_SERIAL_O_RDWR | USBH_SERIAL_O_NONBLOCK);
    if (serial == NULL) {
        serial = usbh_serial_open("/dev/ttyUSB0", USBH_SERIAL_O_RDWR | USBH_SERIAL_O_NONBLOCK);
        if (serial == NULL) {
            USB_LOG_RAW("no serial device found\r\n");
            goto delete;
        }
    }

    struct usbh_serial_termios termios;

    memset(&termios, 0, sizeof(termios));
    termios.baudrate = 115200;
    termios.stopbits = 0;
    termios.parity = 0;
    termios.databits = 8;
    termios.rtscts = false;
    termios.rx_timeout = 0;
    ret = usbh_serial_control(serial, USBH_SERIAL_CMD_SET_ATTR, &termios);
    if (ret < 0) {
        USB_LOG_RAW("set serial attr error, ret:%d\r\n", ret);
        goto delete_with_close;
    }

    /* test with only one buffer, if you have more cdc acm class, modify by yourself */
#ifdef CONFIG_TEST_USBH_CDC_SPEED
    const uint32_t test_len[] = { 512, 1 * 1024, 2 * 1024, 4 * 1024, 8 * 1024, 16 * 1024 };

    memset(serial_speed_buffer, 0xAA, TEST_LEN);

    for (uint8_t j = 0; j < 6; j++) {
        uint32_t start_time = (uint32_t)xTaskGetTickCount();
        for (uint32_t i = 0; i < TEST_COUNT; i++) {
            usbh_serial_write(serial, serial_speed_buffer, test_len[j]);
            if (ret < 0) {
                USB_LOG_RAW("bulk out error,ret:%d\r\n", ret);
                while (1) {
                }
            } else {
            }
        }
        uint32_t time_ms = xTaskGetTickCount() - start_time;
        USB_LOG_RAW("per packet len:%d, out speed:%f MB/S\r\n", (unsigned int)test_len[j], (test_len[j] * TEST_COUNT / 1024 / 1024) * 1000 / ((float)time_ms));
    }
    usbh_serial_close(serial);
    goto delete;
#endif
    memset(serial_tx_buffer, 0xA5, sizeof(serial_tx_buffer));
    USB_LOG_RAW("start serial loopback test, len: %d\r\n", SERIAL_TEST_LEN);

    serial_tx_bytes = 0;
    while (1) {
        ret = usbh_serial_write(serial, serial_tx_buffer, sizeof(serial_tx_buffer));
        if (ret < 0) {
            USB_LOG_RAW("serial write error, ret:%d\r\n", ret);
            goto delete_with_close;
        } else {
            serial_tx_bytes += ret;

            if (serial_tx_bytes == SERIAL_TEST_LEN) {
                USB_LOG_RAW("send over\r\n");
                break;
            }
        }
    }

    volatile uint32_t wait_timeout = 0;
    serial_rx_bytes = 0;
    while (1) {
        ret = usbh_serial_read(serial, &serial_rx_data[serial_rx_bytes], SERIAL_TEST_LEN - serial_rx_bytes);
        if (ret < 0) {
            USB_LOG_RAW("serial read error, ret:%d\r\n", ret);
            goto delete_with_close;
        } else {
            serial_rx_bytes += ret;

            if (serial_rx_bytes == SERIAL_TEST_LEN) {
                USB_LOG_RAW("receive over\r\n");
                for (uint32_t i = 0; i < SERIAL_TEST_LEN; i++) {
                    if (serial_rx_data[i] != 0xa5) {
                        USB_LOG_RAW("serial loopback data error at index %d, data: 0x%02x\r\n", (unsigned int)i, serial_rx_data[i]);
                        goto delete_with_close;
                    }
                }
                serial_test_success = true;
                break;
            }
        }
        wait_timeout++;

        if (wait_timeout > 500) { // 5s
            USB_LOG_RAW("serial read timeout\r\n");
            goto delete_with_close;
        }

        usb_osal_msleep(10);
    }

    // clang-format off
delete_with_close:
    if (serial_test_success) {
        USB_LOG_RAW("serial loopback test success\r\n");
    } else {
        USB_LOG_RAW("serial loopback test failed\r\n");
    }
    usbh_serial_close(serial);
delete:
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

#ifdef CONFIG_TEST_USBH_HID
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_buffer[128];

void usbh_hid_callback(void *arg, int nbytes)
{
    struct usbh_hid *hid_class = (struct usbh_hid *)arg;

    if (nbytes > 0) {
        for (int i = 0; i < nbytes; i++) {
            USB_LOG_RAW("0x%02x ", hid_buffer[i]);
        }
        USB_LOG_RAW("nbytes:%d\r\n", (unsigned int)nbytes);
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_buffer, hid_class->intin->wMaxPacketSize, 0, usbh_hid_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else if (nbytes == -USB_ERR_NAK) { /* only dwc2 should do this */
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_buffer, hid_class->intin->wMaxPacketSize, 0, usbh_hid_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else {
    }
}

static void usbh_hid_thread(CONFIG_USB_OSAL_THREAD_SET_ARGV)
{
    int ret;
    struct usbh_hid *hid_class = (struct usbh_hid *)CONFIG_USB_OSAL_THREAD_GET_ARGV;

    /* test with only one buffer, if you have more hid class, modify by yourself */

    /* Suggest you to use timer for int transfer and use ep interval */
    usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_buffer, hid_class->intin->wMaxPacketSize, 0, usbh_hid_callback, hid_class);
    ret = usbh_submit_urb(&hid_class->intin_urb);
    if (ret < 0) {
        goto delete;
    }
    // clang-format off
delete:
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

#ifdef CONFIG_TEST_USBH_MSC

#ifdef CONFIG_TEST_USBH_MSC_FATFS
#include "ff.h"

#ifdef CONFIG_TEST_USBH_MSC_FATFS_SPEED
#define WRITE_SIZE_MB (128UL)
#define WRITE_SIZE    (1024UL * 1024UL * WRITE_SIZE_MB)
#define BUF_SIZE      (1024UL * 128UL)
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_write_buffer[BUF_SIZE];
#else
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_write_buffer[25 * 100];
#endif

USB_NOCACHE_RAM_SECTION FATFS fs;
USB_NOCACHE_RAM_SECTION FIL fnew;
UINT fnum;
FRESULT res_sd = 0;

int usb_msc_fatfs_test()
{
    const char *tmp_data = "cherryusb fatfs demo...\r\n";

    USB_LOG_RAW("data len:%d\r\n", (unsigned int)strlen(tmp_data));
    for (uint32_t i = 0; i < 100; i++) {
        memcpy(&read_write_buffer[i * 25], tmp_data, strlen(tmp_data));
    }

    res_sd = f_mount(&fs, "2:", 1);
    if (res_sd != FR_OK) {
        USB_LOG_RAW("mount fail,res:%d\r\n", (unsigned int)res_sd);
        return -1;
    }

    USB_LOG_RAW("test fatfs write\r\n");
    res_sd = f_open(&fnew, "2:test.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res_sd == FR_OK) {
        res_sd = f_write(&fnew, read_write_buffer, sizeof(read_write_buffer), &fnum);
        if (res_sd == FR_OK) {
            USB_LOG_RAW("write success, write len:%d\n", fnum);
        } else {
            USB_LOG_RAW("write fail\r\n");
            goto unmount;
        }
        f_close(&fnew);
    } else {
        USB_LOG_RAW("open fail\r\n");
        goto unmount;
    }
    USB_LOG_RAW("test fatfs read\r\n");

    res_sd = f_open(&fnew, "2:test.txt", FA_OPEN_EXISTING | FA_READ);
    if (res_sd == FR_OK) {
        res_sd = f_read(&fnew, read_write_buffer, sizeof(read_write_buffer), &fnum);
        if (res_sd == FR_OK) {
            USB_LOG_RAW("read success, read len:%d\n", fnum);
        } else {
            USB_LOG_RAW("read fail\r\n");
            goto unmount;
        }
        f_close(&fnew);
    } else {
        USB_LOG_RAW("open fail\r\n");
        goto unmount;
    }

#ifdef CONFIG_TEST_USBH_MSC_FATFS_SPEED
    for (uint32_t i = 0; i < BUF_SIZE; i++) {
        read_write_buffer[i] = i % 256;
    }

    USB_LOG_RAW("test fatfs write speed\r\n");
    res_sd = f_open(&fnew, "2:cherryusb_msc_test.bin", FA_OPEN_ALWAYS | FA_WRITE);
    if (res_sd == FR_OK) {
        uint32_t write_size = WRITE_SIZE;
        uint32_t start_time = (uint32_t)xTaskGetTickCount();
        while (write_size > 0) {
            res_sd = f_write(&fnew, read_write_buffer, BUF_SIZE, (UINT *)&fnum);
            if (res_sd != FR_OK) {
                USB_LOG_RAW("Write file failed, cause: %s\n", res_sd);
                goto unmount;
            }
            write_size -= BUF_SIZE;
        }
        if (res_sd == FR_OK) {
            uint32_t time_ms = xTaskGetTickCount() - start_time;
            USB_LOG_RAW("Fatfs write speed:%f MB/S\r\n", (WRITE_SIZE_MB * 1000 / (float)time_ms));
        } else {
            USB_LOG_RAW("write fail\r\n");
            goto unmount;
        }
        f_close(&fnew);
    } else {
        USB_LOG_RAW("open fail\r\n");
        goto unmount;
    }
    USB_LOG_RAW("test fatfs read speed\r\n");

    res_sd = f_open(&fnew, "2:cherryusb_msc_test.bin", FA_OPEN_EXISTING | FA_READ);
    if (res_sd == FR_OK) {
        uint32_t write_size = WRITE_SIZE;
        uint32_t start_time = (uint32_t)xTaskGetTickCount();
        while (write_size > 0) {
            res_sd = f_read(&fnew, read_write_buffer, BUF_SIZE, (UINT *)&fnum);
            if (res_sd != FR_OK) {
                USB_LOG_RAW("Read file failed, cause: %s\n", res_sd);
                goto unmount;
            }
            write_size -= BUF_SIZE;
        }
        if (res_sd == FR_OK) {
            uint32_t time_ms = xTaskGetTickCount() - start_time;
            USB_LOG_RAW("Fatfs read speed:%f MB/S\r\n", (WRITE_SIZE_MB * 1000 / (float)time_ms));
        } else {
            USB_LOG_RAW("read fail\r\n");
            goto unmount;
        }
        f_close(&fnew);
    } else {
        USB_LOG_RAW("open fail\r\n");
        goto unmount;
    }
#endif
    f_mount(NULL, "2:", 1);
    return 0;
unmount:
    f_mount(NULL, "2:", 1);
    return -1;
}
#endif

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t partition_table[512];

static void usbh_msc_thread(CONFIG_USB_OSAL_THREAD_SET_ARGV)
{
    int ret;
    struct usbh_msc *msc_class = (struct usbh_msc *)CONFIG_USB_OSAL_THREAD_GET_ARGV;

    (void)msc_class;

    /* test with only one buffer, if you have more msc class, modify by yourself */
#ifndef TEST_USBH_MSC_FATFS
    ret = usbh_msc_scsi_init(msc_class);
    if (ret < 0) {
        USB_LOG_RAW("scsi_init error,ret:%d\r\n", ret);
        goto delete;
    }
    /* get the partition table */
    ret = usbh_msc_scsi_read10(msc_class, 0, partition_table, 1);
    if (ret < 0) {
        USB_LOG_RAW("scsi_read10 error,ret:%d\r\n", ret);
        goto delete;
    }
    for (uint32_t i = 0; i < 512; i++) {
        if (i % 16 == 0) {
            USB_LOG_RAW("\r\n");
        }
        USB_LOG_RAW("%02x ", partition_table[i]);
    }
    USB_LOG_RAW("\r\n");
#else
    usb_msc_fatfs_test();
#endif

    // clang-format off
delete:
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

#ifdef CONFIG_TEST_USBH_SERIAL
void usbh_serial_run(struct usbh_serial *serial)
{
    if (serial_is_opened) {
        return;
    }
    serial_is_opened = true;
    usb_osal_thread_create("usbh_serial", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_serial_thread, serial);
}

void usbh_serial_stop(struct usbh_serial *serial)
{
    serial_is_opened = false;
}
#endif

#ifdef CONFIG_TEST_USBH_HID
void usbh_hid_run(struct usbh_hid *hid_class)
{
    usb_osal_thread_create("usbh_hid", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_hid_thread, hid_class);
}

void usbh_hid_stop(struct usbh_hid *hid_class)
{
}
#endif

#ifdef CONFIG_TEST_USBH_MSC
void usbh_msc_run(struct usbh_msc *msc_class)
{
    usb_osal_thread_create("usbh_msc", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_msc_thread, msc_class);
}

void usbh_msc_stop(struct usbh_msc *msc_class)
{
}
#endif

#if 0
#include "usbh_aoa.h"

static struct aoa_string_info deviceinfo = {
    .acc_manufacturer = "CherryUSB",
    .acc_model = "CherryUSB",
    .acc_description = "Android Open Accessory CherryUSB",
    .acc_version = "1.0",
    .acc_uri = "http://developer.android.com/tools/adk/index.html",
    .acc_serial = "CherryUSB"
};

int aoa_switch(int argc, char **argv)
{
    struct usbh_hubport *hport = usbh_find_hubport(0, 1, 1);

    usbh_aoa_switch(hport, &deviceinfo);
    return 0;
}

SHELL_CMD_EXPORT_ALIAS(aoa_switch, aoa_switch, aoa_switch);
#endif