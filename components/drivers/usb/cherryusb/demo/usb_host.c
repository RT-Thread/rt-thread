/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_cdc_acm.h"
#include "usbh_hid.h"
#include "usbh_msc.h"
#include "usbh_video.h"
#include "usbh_audio.h"

#ifndef TEST_USBH_CDC_ACM
#define TEST_USBH_CDC_ACM 1
#endif
#ifndef TEST_USBH_CDC_SPEED
#define TEST_USBH_CDC_SPEED 0
#endif
#ifndef TEST_USBH_HID
#define TEST_USBH_HID 1
#endif
#ifndef TEST_USBH_MSC
#define TEST_USBH_MSC 1
#endif
#ifndef TEST_USBH_MSC_FATFS
#define TEST_USBH_MSC_FATFS 0
#endif
#ifndef TEST_USBH_AUDIO
#define TEST_USBH_AUDIO 0
#endif
#ifndef TEST_USBH_VIDEO
#define TEST_USBH_VIDEO 0
#endif

#if defined(TEST_USBH_CDC_ECM) || defined(TEST_USBH_CDC_RNDIS) || defined(TEST_USBH_ASIX) || defined(TEST_USBH_RTL8152)
#error we have move those class implements into platform/none/usbh_lwip.c, and you should call tcpip_init(NULL, NULL) in your app
#endif

#if TEST_USBH_CDC_ACM
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_buffer[4096];

#if TEST_USBH_CDC_SPEED
#define TEST_LEN   (16 * 1024)
#define TEST_COUNT (10240)

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_speed_buffer[TEST_LEN];
#endif

void usbh_cdc_acm_callback(void *arg, int nbytes)
{
    //struct usbh_cdc_acm *cdc_acm_class = (struct usbh_cdc_acm *)arg;

    if (nbytes > 0) {
        for (size_t i = 0; i < nbytes; i++) {
            USB_LOG_RAW("0x%02x ", cdc_buffer[i]);
        }
        USB_LOG_RAW("nbytes:%d\r\n", nbytes);
    }
}

static void usbh_cdc_acm_thread(void *argument)
{
    int ret;
    struct usbh_cdc_acm *cdc_acm_class = (struct usbh_cdc_acm *)argument;

    /* test with only one buffer, if you have more cdc acm class, modify by yourself */
#if TEST_USBH_CDC_SPEED
    const uint32_t test_len[] = { 512, 1 * 1024, 2 * 1024, 4 * 1024, 8 * 1024, 16 * 1024 };

    memset(cdc_speed_buffer, 0xAA, TEST_LEN);

    for (uint8_t j = 0; j < 6; j++) {
        uint32_t start_time = (uint32_t)xTaskGetTickCount();
        for (uint32_t i = 0; i < TEST_COUNT; i++) {
            usbh_bulk_urb_fill(&cdc_acm_class->bulkout_urb, cdc_acm_class->hport, cdc_acm_class->bulkout, cdc_speed_buffer, test_len[j], 0XFFFFFFF, NULL, NULL);
            ret = usbh_submit_urb(&cdc_acm_class->bulkout_urb);
            if (ret < 0) {
                USB_LOG_RAW("bulk out error,ret:%d\r\n", ret);
                while (1) {
                }
            } else {
            }
        }
        uint32_t time_ms = xTaskGetTickCount() - start_time;
        USB_LOG_RAW("per packet len:%d, out speed:%f MB/S\r\n", test_len[j], (test_len[j] * TEST_COUNT / 1024 / 1024) * 1000 / ((float)time_ms));
    }
#endif
    memset(cdc_buffer, 0x55, 4096);

    /* for common, we use timeout with 0xffffffff, this is just a test */
    usbh_bulk_urb_fill(&cdc_acm_class->bulkout_urb, cdc_acm_class->hport, cdc_acm_class->bulkout, cdc_buffer, sizeof(cdc_buffer), 3000, NULL, NULL);
    ret = usbh_submit_urb(&cdc_acm_class->bulkout_urb);
    if (ret < 0) {
        USB_LOG_RAW("bulk out error,ret:%d\r\n", ret);
        goto delete;
    } else {
        USB_LOG_RAW("send over:%d\r\n", cdc_acm_class->bulkout_urb.actual_length);
    }

    /* we can change cdc_acm_class->bulkin->wMaxPacketSize with 4096 for testing zlp, default is ep mps  */
    usbh_bulk_urb_fill(&cdc_acm_class->bulkin_urb, cdc_acm_class->hport, cdc_acm_class->bulkin, cdc_buffer, cdc_acm_class->bulkin->wMaxPacketSize, 0xffffffff, usbh_cdc_acm_callback, cdc_acm_class);
    ret = usbh_submit_urb(&cdc_acm_class->bulkin_urb);
    if (ret < 0) {
        USB_LOG_RAW("bulk in error,ret:%d\r\n", ret);
        goto delete;
    } else {
    }
    // clang-format off
delete:
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

#if TEST_USBH_HID
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_buffer[128];

void usbh_hid_callback(void *arg, int nbytes)
{
    struct usbh_hid *hid_class = (struct usbh_hid *)arg;

    if (nbytes > 0) {
        for (int i = 0; i < nbytes; i++) {
            USB_LOG_RAW("0x%02x ", hid_buffer[i]);
        }
        USB_LOG_RAW("nbytes:%d\r\n", nbytes);
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_buffer, hid_class->intin->wMaxPacketSize, 0, usbh_hid_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else if (nbytes == -USB_ERR_NAK) { /* only dwc2 should do this */
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_buffer, hid_class->intin->wMaxPacketSize, 0, usbh_hid_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else {
    }
}

static void usbh_hid_thread(void *argument)
{
    int ret;
    struct usbh_hid *hid_class = (struct usbh_hid *)argument;
    ;

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

#if TEST_USBH_MSC

#if TEST_USBH_MSC_FATFS
#include "ff.h"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_write_buffer[25 * 100];

USB_NOCACHE_RAM_SECTION FATFS fs;
USB_NOCACHE_RAM_SECTION FIL fnew;
UINT fnum;
FRESULT res_sd = 0;

int usb_msc_fatfs_test()
{
    const char *tmp_data = "cherryusb fatfs demo...\r\n";

    USB_LOG_RAW("data len:%d\r\n", strlen(tmp_data));
    for (uint32_t i = 0; i < 100; i++) {
        memcpy(&read_write_buffer[i * 25], tmp_data, strlen(tmp_data));
    }

    res_sd = f_mount(&fs, "2:", 1);
    if (res_sd != FR_OK) {
        USB_LOG_RAW("mount fail,res:%d\r\n", res_sd);
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
    f_mount(NULL, "2:", 1);
    return 0;
unmount:
    f_mount(NULL, "2:", 1);
    return -1;
}
#endif

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t partition_table[512];

static void usbh_msc_thread(void *argument)
{
    int ret;
    struct usbh_msc *msc_class = (struct usbh_msc *)argument;

    /* test with only one buffer, if you have more msc class, modify by yourself */
#if 1
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
#endif

#if TEST_USBH_MSC_FATFS
    usb_msc_fatfs_test();
#endif
    // clang-format off
delete:
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

void usbh_cdc_acm_run(struct usbh_cdc_acm *cdc_acm_class)
{
#if TEST_USBH_CDC_ACM
    usb_osal_thread_create("usbh_cdc", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_cdc_acm_thread, cdc_acm_class);
#endif
}

void usbh_cdc_acm_stop(struct usbh_cdc_acm *cdc_acm_class)
{
}

void usbh_hid_run(struct usbh_hid *hid_class)
{
#if TEST_USBH_HID
    usb_osal_thread_create("usbh_hid", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_hid_thread, hid_class);
#endif
}

void usbh_hid_stop(struct usbh_hid *hid_class)
{
}

void usbh_msc_run(struct usbh_msc *msc_class)
{
#if TEST_USBH_MSC
    usb_osal_thread_create("usbh_msc", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_msc_thread, msc_class);
#endif
}

void usbh_msc_stop(struct usbh_msc *msc_class)
{
}

#if TEST_USBH_AUDIO
#error "commercial charge"
#endif

#if TEST_USBH_VIDEO
#error "commercial charge"
#endif
