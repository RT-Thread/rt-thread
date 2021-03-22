/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-17     supperthomas first version
 * 2021-03-22     dillon       add support for u-boot/kernel/rootfs install
 *                             jump to u-boot, load kernel
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <finsh.h>
#include <drv_common.h>
#include <ymodem.h>
#include <fal.h>
#include "stm32h7xx_hal.h"
#include "w25qxx.h"
/* defined the LED0 pin: PI8 */
#define LED0_PIN        GET_PIN(I, 8)
#define LED1_PIN        GET_PIN(C, 15)
#define UBOOT_ADDRESS   (uint32_t)0x90000000
#define KERNEL_ADDRESS  (uint32_t)0x90080000
#define TYPE_OTA_UBOOT  0x00
#define TYPE_OTA_KERNEL 0x01
#define TYPE_OTA_ROOT   0x02

static rt_uint8_t ota_type = TYPE_OTA_UBOOT;
static rt_uint32_t fal_partition_ofs = 0;
static fal_partition_t qspi_part = RT_NULL;
static rt_uint32_t down_addr = UBOOT_ADDRESS;

typedef void (*pFunction)(void);
pFunction JumpToApplication;
static rt_err_t rym_download_file(rt_device_t idev);

/* When rtt load other fw to running, which means
 * rtt working as bootloader.
 * MSP is what set from boot, thus it is natural
 * assumption that boot code would preserve that
 * illusion.
 * To make kernel happy, so switch back to msp.
 */
static void switch_back_to_msp()
{
    __asm volatile (
        "PUSH {r0, r1, lr} \n"
        "LDR r0, =#0x90000000 \n"
        "MSR msp, r0 \n"
        "MRS r0, control \n"
        "BICS r0, r0, #0x6 \n"
        "MSR control, r0 \n"
        "DSB \n"
        "ISB \n"
    );
}

/* jump to u-boot or other fw installed on qspi flash */
void jump(uint32_t addr)
{
    W25QXX_ExitQPIMode();
    W25QXX_Reset();
    W25QXX_Init();
    W25Q_Memory_Mapped_Enable();

    HAL_NVIC_DisableIRQ(UART4_IRQn);
    rt_hw_interrupt_disable();
    HAL_MPU_Disable();
    SCB_DisableICache();
    SCB_DisableDCache();
    SysTick->CTRL = 0;
    switch_back_to_msp();
    __set_MSP(*(__IO uint32_t *)addr);
    JumpToApplication = (pFunction)(*(__IO uint32_t *)(addr + 4));
    SCB->VTOR = addr;

    rt_kprintf("before jump, %x msp %x psp %x ctl %x\r\n",
    		    addr, __get_MSP(), __get_PSP(),
    		    __get_CONTROL());
    JumpToApplication();
}

/* to make download faster, use 2M uart baud */
void switch_baud_2m()
{
    rt_device_t serial = rt_console_get_device();

    if (serial != RT_NULL) {
        struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
        config.baud_rate = BAUD_RATE_2000000;
        rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
    }
}

int main(void)
{
    int count = 1;
    switch_baud_2m();
    rt_kprintf("BOOT\r\n"); 
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (count++) {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static void boot(uint8_t argc, char **argv)
{
    jump(UBOOT_ADDRESS);
}
FINSH_FUNCTION_EXPORT_ALIAS(boot, __cmd_boot, Jump to App);

struct custom_ctx
{
    struct rym_ctx parent;
    int fd;
    int flen;
    char fpath[256];
};

static enum rym_code _rym_recv_begin(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;
    rt_uint32_t file_len = 0;

    cctx->fpath[0] = '/';
    rt_strncpy(&(cctx->fpath[1]), (const char *)buf, len - 1);

    file_len = atoi(1 + (const char *)buf + rt_strnlen((const char *)buf,
                                            len - 1));
    if (file_len == 0)
        file_len = -1;

    fal_partition_ofs = 0;
    if (ota_type == TYPE_OTA_KERNEL)
        qspi_part = (fal_partition_t)fal_partition_find("linux");
    else if (ota_type == TYPE_OTA_UBOOT)
        qspi_part = (fal_partition_t)fal_partition_find("u-boot");
    else if (ota_type == TYPE_OTA_ROOT)
        qspi_part = (fal_partition_t)fal_partition_find("root");

    if (qspi_part == RT_NULL) {
        rt_kprintf("can't find qspi part %d\r\n", ota_type);
    } else {
        if ((fal_partition_erase(qspi_part, 0, file_len) < 0)) {
            rt_kprintf("erase qspi part failed\r\n");
            return RYM_ERR_FILE;
        }
    }

    return RYM_CODE_ACK;
}

static enum rym_code _rym_recv_data(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    uint8_t verify[1024] = {0};
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;

    if (fal_partition_write(qspi_part, fal_partition_ofs, buf, len) < 0) {
        rt_kprintf("write qspi flash %d failed\r\n", fal_partition_ofs);
    }

    if (fal_partition_read(qspi_part, fal_partition_ofs, verify, len) < 0) {
        rt_kprintf("read qspi flash %d failed\r\n", fal_partition_ofs);
    }

    if (memcmp(verify, buf, len) != 0) {
        rt_kprintf("write to %d, read back different\r\n", fal_partition_ofs);
        return RYM_ERR_FILE;
    }

    fal_partition_ofs += len;
    return RYM_CODE_ACK;
}

static enum rym_code _rym_recv_end(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;

    cctx->fd = -1;
    return RYM_CODE_ACK;
}

static rt_err_t rym_download_file(rt_device_t idev)
{
    rt_err_t res;
    struct custom_ctx *ctx = rt_calloc(1, sizeof(*ctx));

    if (!ctx) {
        rt_kprintf("rt_malloc failed\n");
        return RT_ENOMEM;
    }

    ctx->fd = -1;
    RT_ASSERT(idev);
    res = rym_recv_on_device(&ctx->parent, idev, RT_DEVICE_OFLAG_RDWR |
                                                 RT_DEVICE_FLAG_INT_RX,
                        _rym_recv_begin, _rym_recv_data, _rym_recv_end, 1000);
    rt_free(ctx);

    return res;
}

static rt_err_t ry(uint8_t argc, char **argv)
{
    rt_err_t res;
    rt_device_t dev;

    if (argc > 1 && strcmp(argv[1], "linux") == 0) {
        ota_type = TYPE_OTA_KERNEL;
        down_addr = KERNEL_ADDRESS;
    } else if (argc > 1 && strcmp(argv[1], "root") == 0) {
        ota_type = TYPE_OTA_ROOT;
        down_addr = UBOOT_ADDRESS;
    } else {
        ota_type = TYPE_OTA_UBOOT;
        down_addr = UBOOT_ADDRESS;
    }

    dev = rt_console_get_device();
    if (!dev) {
        rt_kprintf("could not find device.\n");
        return -RT_ERROR;
    }

    res = rym_download_file(dev);

    return res;
}
MSH_CMD_EXPORT(ry, YMODEM Receive e.g: ry);
#endif /* RT_USING_FINSH */
