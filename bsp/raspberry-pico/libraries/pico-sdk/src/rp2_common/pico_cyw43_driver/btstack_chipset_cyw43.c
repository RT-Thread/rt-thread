/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/btstack_chipset_cyw43.h"

static void chipset_set_bd_addr_command(bd_addr_t addr, uint8_t *hci_cmd_buffer) {
    hci_cmd_buffer[0] = 0x01;
    hci_cmd_buffer[1] = 0xfc;
    hci_cmd_buffer[2] = 0x06;
    reverse_bd_addr(addr, &hci_cmd_buffer[3]);
}

static const btstack_chipset_t btstack_chipset_cyw43 = {
    .name = "CYW43",
    .init = NULL,
    .next_command = NULL,
    .set_baudrate_command = NULL,
    .set_bd_addr_command = chipset_set_bd_addr_command,
};

const btstack_chipset_t * btstack_chipset_cyw43_instance(void) {
    return &btstack_chipset_cyw43;
}
