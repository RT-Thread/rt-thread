/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <FreeRTOS.h>
#include <semphr.h>
#include <bl_cam.h>
#include <bl808_glb.h>
#include <usbd_core.h>
#include <usbd_video.h>
#include "bl_usb_cam.h"

#define VIDEO_IN_EP 0x81

#ifdef CONFIG_USB_HS
#define MAX_PAYLOAD_SIZE  1024
#else
#define MAX_PAYLOAD_SIZE  1023
#endif
#define VIDEO_PACKET_SIZE (unsigned int)(((MAX_PAYLOAD_SIZE / 1)) | (0x00 << 11))

#define WIDTH  (unsigned int)(800)
#define HEIGHT (unsigned int)(600)

#define CAM_FPS        (30)
#define INTERVAL       (unsigned long)(10000000 / CAM_FPS)
#define MIN_BIT_RATE   (unsigned long)(WIDTH * HEIGHT * 16 * CAM_FPS) //16 bit
#define MAX_BIT_RATE   (unsigned long)(WIDTH * HEIGHT * 16 * CAM_FPS)
#define MAX_FRAME_SIZE (unsigned long)(WIDTH * HEIGHT * 2)

#define USB_VIDEO_DESC_SIZ (unsigned long)(9 +  \
                                           8 +  \
                                           9 +  \
                                           13 + \
                                           18 + \
                                           9 +  \
                                           12 + \
                                           9 +  \
                                           14 + \
                                           11 + \
                                           38 + \
                                           9 +  \
                                           7)

#define VC_TERMINAL_SIZ (unsigned int)(13 + 18 + 12 + 9)
#define VS_HEADER_SIZ   (unsigned int)(13 + 1 + 11 + 38)

#define USBD_VID           0xffff
#define USBD_PID           0xffff
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033
#define TASK_MAIN_PRIORITY 20
#define PER_FRAME_MJPEG     100*1024
#define USB_MAX_BUFFER      120*1024
#define MJPEG_DEFAULT_ADDR  0x80400000 //if mjpeg no init mjpeg addr reg default value

const uint8_t video_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0001, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_VIDEO_DESC_SIZ, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    VIDEO_VC_DESCRIPTOR_INIT(0x00, 0, 0x0100, VC_TERMINAL_SIZ, 48000000, 0x02),
    VIDEO_VS_DESCRIPTOR_INIT(0x01, 0x00, 0x00),
    VIDEO_VS_HEADER_DESCRIPTOR_INIT(0x01, VS_HEADER_SIZ, VIDEO_IN_EP, 1, 0x00),
    VIDEO_VS_FORMAT_MJPEG_DESCRIPTOR_INIT(0x01, 0x01),
    VIDEO_VS_FRAME_MJPEG_DESCRIPTOR_INIT(0x01, WIDTH, HEIGHT, MIN_BIT_RATE, MAX_BIT_RATE, MAX_FRAME_SIZE, INTERVAL, 0x00, DBVAL(INTERVAL), DBVAL(INTERVAL), DBVAL(0)),
    VIDEO_VS_DESCRIPTOR_INIT(0x01, 0x01, 0x01),
    /* 1.2.2.2 Standard VideoStream Isochronous Video Data Endpoint Descriptor */
    0x07,                         /* bLength */
    USB_DESCRIPTOR_TYPE_ENDPOINT, /* bDescriptorType: ENDPOINT */
    0x81,                         /* bEndpointAddress: IN endpoint 2 */
    0x01,                         /* bmAttributes: Isochronous transfer type. Asynchronous synchronization type. */
    WBVAL(VIDEO_PACKET_SIZE),     /* wMaxPacketSize */
    0x01,                         /* bInterval: One frame interval */

    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x12,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'B', 0x00,                  /* wcChar0 */
    'o', 0x00,                  /* wcChar1 */
    'u', 0x00,                  /* wcChar2 */
    'f', 0x00,                  /* wcChar3 */
    'f', 0x00,                  /* wcChar4 */
    'a', 0x00,                  /* wcChar5 */
    'l', 0x00,                  /* wcChar6 */
    'o', 0x00,                  /* wcChar7 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x28,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'B', 0x00,                  /* wcChar0 */
    'o', 0x00,                  /* wcChar1 */
    'u', 0x00,                  /* wcChar2 */
    'f', 0x00,                  /* wcChar3 */
    'f', 0x00,                  /* wcChar4 */
    'a', 0x00,                  /* wcChar5 */
    'l', 0x00,                  /* wcChar6 */
    'o', 0x00,                  /* wcChar7 */
    ' ', 0x00,                  /* wcChar8 */
    'V', 0x00,                  /* wcChar9 */
    'E', 0x00,                  /* wcChar10 */
    'D', 0x00,                  /* wcChar11 */
    'I', 0x00,                  /* wcChar12 */
    'O', 0x00,                  /* wcChar13 */
    ' ', 0x00,                  /* wcChar14 */
    'D', 0x00,                  /* wcChar15 */
    'E', 0x00,                  /* wcChar16 */
    'M', 0x00,                  /* wcChar17 */
    'O', 0x00,                  /* wcChar18 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '1', 0x00,                  /* wcChar3 */
    '0', 0x00,                  /* wcChar4 */
    '3', 0x00,                  /* wcChar5 */
    '1', 0x00,                  /* wcChar6 */
    '0', 0x00,                  /* wcChar7 */
    '0', 0x00,                  /* wcChar8 */
    '0', 0x00,                  /* wcChar9 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

static usbd_class_t video_class;
static usbd_interface_t video_control_intf;
static usbd_interface_t video_stream_intf;
#if defined NO_PSRAM_HEAP
#define CUSTOMER_SECTION    __attribute__((section(".custom_psram_bss")))
static uint8_t usb_buffer[USB_MAX_BUFFER]  CUSTOMER_SECTION;
static uint8_t mjpeg_swap_buffer[PER_FRAME_MJPEG] CUSTOMER_SECTION;
#else
static uint8_t *usb_buffer = NULL;
static uint8_t *mjpeg_swap_buffer = NULL;
#endif
static uint32_t mjpeg_start_addr, mjpeg_buffer_size;
SemaphoreHandle_t usb_cam_semap = NULL;

void usbd_video_iso_callback(uint8_t ep)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (usb_cam_semap) {
        xSemaphoreGiveFromISR(usb_cam_semap, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

static usbd_endpoint_t video_in_ep = {
    .ep_cb = usbd_video_iso_callback,
    .ep_addr = VIDEO_IN_EP
};

volatile bool tx_flag = 0;

void usbd_video_open(uint8_t intf)
{
    tx_flag = 1;
    printf("OPEN\r\n");
}
void usbd_video_close(uint8_t intf)
{
    printf("CLOSE\r\n");
    tx_flag = 0;
}

static void bl_usb_clock_init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpVal |= (1 << 13);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpVal);
    GLB_Set_USB_CLK_From_WIFIPLL(1);
}

int bl_usb_cam_init(void)
{
    int ret = 0;

    ret = bl_cam_mjpeg_buffer_info_get(&mjpeg_start_addr, &mjpeg_buffer_size);
    if (ret != 0) {
        printf("mjpeg not init\r\n");
        goto exit;
    }

    usb_cam_semap = xSemaphoreCreateBinary();
    if (NULL == usb_cam_semap) {
        printf("create usb_cam_semap fail\r\n");
        ret = -1;
        goto exit;
    }

#ifndef NO_PSRAM_HEAP
    usb_buffer = pvPortMalloc(USB_MAX_BUFFER);
    if (NULL == usb_buffer) {
        printf("malloc usb_buffer fail!\r\n");
        vSemaphoreDelete(usb_cam_semap);
        usb_cam_semap = NULL;
        ret = -1;
        goto exit;
    }

    mjpeg_swap_buffer = pvPortMalloc(PER_FRAME_MJPEG);
    if (NULL == mjpeg_swap_buffer) {
        printf("malloc mjpeg_swap_buffer fail!\r\n");
        vPortFree(usb_buffer);
        usb_buffer = NULL;
        vSemaphoreDelete(usb_cam_semap);
        usb_cam_semap = NULL;
        ret = -1;
        goto exit;
    }
#endif
    bl_usb_clock_init();
    usbd_desc_register(video_descriptor);
    usbd_video_add_interface(&video_class, &video_control_intf);
    usbd_video_add_interface(&video_class, &video_stream_intf);
    usbd_interface_add_endpoint(&video_stream_intf, &video_in_ep);

    usbd_video_probe_and_commit_controls_init(CAM_FPS, MAX_FRAME_SIZE, MAX_PAYLOAD_SIZE);
    usbd_initialize();

    xSemaphoreGive(usb_cam_semap);
exit:
    return ret;
}

int bl_usb_cam_transfer(void)
{
    int ret = 0;
    uint8_t *pic, *usb_ptr;
    uint32_t len, first_len, second_len, out_len;

    if (tx_flag) {
        ret = bl_cam_mjpeg_get(&pic, &len);
        if (ret == 0) {
            if (((uint32_t)(uintptr_t)pic + len) > (mjpeg_start_addr + mjpeg_buffer_size)) {
                /* if mjpeg store edge loop to start*/
                first_len = mjpeg_start_addr + mjpeg_buffer_size - (uint32_t)(uintptr_t)pic;
                second_len = len - first_len;
                csi_dcache_invalid_range((void *)pic, first_len);
                memcpy(mjpeg_swap_buffer, pic, first_len);
                csi_dcache_invalid_range((void *)mjpeg_start_addr, second_len);
                memcpy(mjpeg_swap_buffer + first_len, (void *)mjpeg_start_addr, second_len);
                usb_ptr = mjpeg_swap_buffer;
            } else {
                /*mjpeg data not cut*/
                usb_ptr = pic;
                csi_dcache_invalid_range((void *)usb_ptr, len);
            }

            if (NULL == usb_cam_semap) {
                ret = -1;
                goto exit;
            }
            if (len > USB_MAX_BUFFER) {
                ret = -1;
                printf("jpeg frame size is out of %dbytes\r\n", USB_MAX_BUFFER);
                goto exit;
            }
            xSemaphoreTake(usb_cam_semap, portMAX_DELAY);
            /*fill mjpeg in usb data struct*/
            usbd_video_mjpeg_payload_fill(usb_ptr, len, usb_buffer, &out_len);
            bl_cam_mjpeg_pop();

            /* send usb data async*/
            usbd_ep_write_async(VIDEO_IN_EP, usb_buffer, out_len);
        }
    }

exit:
    return ret;
}

