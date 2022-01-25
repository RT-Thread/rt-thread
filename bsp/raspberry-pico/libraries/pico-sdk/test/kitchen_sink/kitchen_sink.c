/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/dma.h"
#include "pico/bit_ops.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "hardware/pio.h"
#include "hardware/irq.h"
#include "hardware/timer.h"
#include "pico/divider.h"
#include "pico/critical_section.h"
#include "pico/binary_info.h"

bi_decl(bi_block_device(
                           BINARY_INFO_MAKE_TAG('K', 'S'),
                           "foo",
                           0x80000,
                           0x40000,
                           NULL,
                           BINARY_INFO_BLOCK_DEV_FLAG_READ | BINARY_INFO_BLOCK_DEV_FLAG_WRITE |
                                   BINARY_INFO_BLOCK_DEV_FLAG_PT_UNKNOWN));

void my_timer(uint i) {
    puts("XXXX timer");
}

//#pragma GCC push_options
//#pragma GCC optimize ("O3")

uint32_t *foo = (uint32_t *) 200;

uint32_t dma_to = 0;
uint32_t dma_from = 0xaaaa5555;

void spiggle() {
    dma_channel_config c = dma_channel_get_default_config(1);
    channel_config_set_bswap(&c, true);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
    channel_config_set_ring(&c, true, 13);
    dma_channel_set_config(1, &c, false);
    dma_channel_transfer_from_buffer_now(1, foo, 23);
}

void __isr dma_handler_a() {
    printf("HELLO A\n");
    if (dma_hw->ints1 & 1) {
        dma_hw->ints1 = 1;
        printf("A WINS DMA_TO %08x\n", (uint) dma_to);
        irq_remove_handler(DMA_IRQ_1, dma_handler_a);
    }
}

void __isr dma_handler_b() {
    printf("HELLO B\n");
    if (dma_hw->ints1 & 1) {
        dma_hw->ints1 = 1;
        printf("B WINS DNA_TO %08x\n", (uint) dma_to);
//        irq_remove_handler(DMA_IRQ_1, dma_handler_b);
    }
}

//#pragma GCC pop_options

int main() {
    spiggle();

    stdio_init_all();

    printf("HI %d\n", (int)time_us_32());
    puts("Hello Everything!");
    puts("Hello Everything2!");

    irq_add_shared_handler(DMA_IRQ_1, dma_handler_a, 0x80);
    irq_add_shared_handler(DMA_IRQ_1, dma_handler_b, 0xC0);

    dma_channel_config config = dma_channel_get_default_config(0);
//    set_exclusive_irq_handler(DMA_IRQ_1, dma_handler_a);
    dma_channel_set_irq1_enabled(0, true);
    irq_set_enabled(DMA_IRQ_1, true);
    dma_channel_configure(0, &config, &dma_to, &dma_from, 1, true);
    dma_channel_set_config(0, &config, false);

//    timer_start_ms(2, 2000, my_timer);
    for (int i = 0; i < 20; i++) {
        puts("sleepy");
        sleep_ms(1000);
        dma_channel_configure(0, &config, &dma_to, &dma_from, 1, true);
        if (i==3) {
            irq_remove_handler(DMA_IRQ_1, dma_handler_a);
        }
        if (i==2) {
            irq_remove_handler(DMA_IRQ_1, dma_handler_b);
        }
    }
}
