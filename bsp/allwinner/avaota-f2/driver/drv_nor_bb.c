/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal SPI-NOR bring-up without the SPIF DMA engine: bit-bang JEDEC RDID
 * and a 16-byte READ on PC0..PC5 (SyterKit Avaota-F2 / sun252iw1 pinout).
 *
 *   PC0 = CLK, PC1 = CS#, PC2 = MOSI(IO0), PC3 = MISO(IO1),
 *   PC4 = WP#(IO2), PC5 = HOLD#(IO3)  — keep WP/HOLD high.
 */

#include <rthw.h>
#include <rtthread.h>

#include "drv_nor_bb.h"

#define SUNXI_GPIO_BASE        0x02000000U
#define SUNXI_GPIO_PORT_STRIDE 0x30U
#define PIO_PORT_C             2U

#define NOR_CMD_RDID 0x9FU
#define NOR_CMD_READ 0x03U

/* Puya PY25Q128 common JEDEC: mfr=0x85, type=0x20, cap=0x18 */
#define PY25_MFR 0x85U
#define PY25_CAP 0x18U

static void mmio_w(uint32_t addr, uint32_t val)
{
    *(volatile uint32_t *)addr = val;
}

static uint32_t mmio_r(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void busy_delay(volatile uint32_t n)
{
    while (n--)
    {
        __asm__ volatile("nop");
    }
}

static uint32_t bank_base(void)
{
    return SUNXI_GPIO_BASE + PIO_PORT_C * SUNXI_GPIO_PORT_STRIDE;
}

static void pc_set_func(uint32_t pin, uint32_t func)
{
    uint32_t cfg = bank_base() + (pin / 8U) * 4U;
    uint32_t shift = (pin % 8U) * 4U;
    uint32_t v = mmio_r(cfg);

    v = (v & ~(0xFU << shift)) | ((func & 0xFU) << shift);
    mmio_w(cfg, v);
}

static void pc_set_pull(uint32_t pin, uint32_t pull)
{
    uint32_t reg = bank_base() + 0x24U + (pin / 16U) * 4U;
    uint32_t shift = (pin % 16U) * 2U;
    uint32_t v = mmio_r(reg);

    v = (v & ~(0x3U << shift)) | ((pull & 0x3U) << shift);
    mmio_w(reg, v);
}

static void pc_dir_out(uint32_t pin)
{
    /* sunxi gpio-v2: data reg @+0x10 acts as level; cfg func=1 is output */
    pc_set_func(pin, 1U);
}

static void pc_dir_in(uint32_t pin)
{
    pc_set_func(pin, 0U); /* input */
    pc_set_pull(pin, 1U); /* pull-up */
}

static void pc_write(uint32_t pin, int high)
{
    uint32_t data = bank_base() + 0x10U;
    uint32_t v = mmio_r(data);

    if (high)
    {
        v |= (1U << pin);
    }
    else
    {
        v &= ~(1U << pin);
    }
    mmio_w(data, v);
}

static int pc_read(uint32_t pin)
{
    return (mmio_r(bank_base() + 0x10U) >> pin) & 1;
}

#define PIN_CLK  0U
#define PIN_CS   1U
#define PIN_MOSI 2U
#define PIN_MISO 3U
#define PIN_WP   4U
#define PIN_HOLD 5U

static void spi_idle(void)
{
    pc_write(PIN_CS, 1);
    pc_write(PIN_CLK, 0);
    pc_write(PIN_MOSI, 0);
    pc_write(PIN_WP, 1);
    pc_write(PIN_HOLD, 1);
}

static void spi_begin(void)
{
    pc_write(PIN_CS, 0);
    busy_delay(20U);
}

static void spi_end(void)
{
    pc_write(PIN_CS, 1);
    busy_delay(20U);
}

/* Mode 0: sample on rising edge, shift on falling. */
static uint8_t spi_xfer_byte(uint8_t out)
{
    uint8_t in = 0;
    int bit;

    for (bit = 7; bit >= 0; bit--)
    {
        pc_write(PIN_MOSI, (out >> bit) & 1);
        busy_delay(10U);
        pc_write(PIN_CLK, 1);
        busy_delay(10U);
        in = (uint8_t)((in << 1) | (pc_read(PIN_MISO) & 1));
        pc_write(PIN_CLK, 0);
        busy_delay(10U);
    }
    return in;
}

static void nor_pins_init(void)
{
    pc_dir_out(PIN_CLK);
    pc_dir_out(PIN_CS);
    pc_dir_out(PIN_MOSI);
    pc_dir_out(PIN_WP);
    pc_dir_out(PIN_HOLD);
    pc_dir_in(PIN_MISO);
    spi_idle();
    busy_delay(1000U);
}

static int nor_rdid(uint8_t id[3])
{
    spi_begin();
    (void)spi_xfer_byte(NOR_CMD_RDID);
    id[0] = spi_xfer_byte(0);
    id[1] = spi_xfer_byte(0);
    id[2] = spi_xfer_byte(0);
    spi_end();
    return 0;
}

static int nor_read(uint32_t addr, uint8_t *buf, uint32_t len)
{
    uint32_t i;

    spi_begin();
    (void)spi_xfer_byte(NOR_CMD_READ);
    (void)spi_xfer_byte((uint8_t)((addr >> 16) & 0xffU));
    (void)spi_xfer_byte((uint8_t)((addr >> 8) & 0xffU));
    (void)spi_xfer_byte((uint8_t)(addr & 0xffU));
    for (i = 0; i < len; i++)
    {
        buf[i] = spi_xfer_byte(0);
    }
    spi_end();
    return 0;
}

int rt_hw_nor_bb_probe(void)
{
    uint8_t id[3];
    uint8_t head[16];
    uint32_t i;

    rt_kprintf("DT: nor-bb PC0-5 bitbang probe\n");
    nor_pins_init();

    nor_rdid(id);
    rt_kprintf("DT: nor-bb RDID %02x %02x %02x\n", id[0], id[1], id[2]);

    if (id[0] == 0x00U || id[0] == 0xffU)
    {
        rt_kprintf("DT: nor-bb FAIL (no response)\n");
        return -1;
    }

    if (id[0] == PY25_MFR && id[2] == PY25_CAP)
    {
        rt_kprintf("DT: nor-bb OK PY25Q128-class\n");
    }
    else
    {
        rt_kprintf("DT: nor-bb OK (unknown JEDEC, still live)\n");
    }

    nor_read(0, head, sizeof(head));
    rt_kprintf("DT: nor-bb @0:");
    for (i = 0; i < sizeof(head); i++)
    {
        rt_kprintf(" %02x", head[i]);
    }
    rt_kprintf("\n");
    return 0;
}
