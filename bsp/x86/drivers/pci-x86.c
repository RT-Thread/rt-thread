/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifdef USE_PCI
/* ============================ [ INCLUDES  ] ====================================================== */
#include "pci_core.h"
/* ============================ [ MACROS    ] ====================================================== */
#define     CONFIG_ADDRESS_REG          0x0cf8
#define     CONFIG_DATA_REG             0x0cfc
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
/* Lunatic */
uint32 pci_read_config_reg32(pci_reg *reg, uint8 offset)
{
    uint32 value, orig;
    uint32 ret;

    value = 0x80000000UL;
    value |= (offset & 0xfc);
    value |= reg->fn << 8;
    value |= reg->dev << 11;
    value |= reg->bus << 16;

    orig = inl(CONFIG_ADDRESS_REG);
    outl(CONFIG_ADDRESS_REG, value);

    ret = inl(CONFIG_DATA_REG);
    outl(CONFIG_ADDRESS_REG, orig);

    return ret;
}

uint16 pci_read_config_reg16(pci_reg *reg, uint8 offset)
{
    uint32 value, orig;
    uint16  ret;

    value = 0x80000000UL;
    value |= (offset & 0xfc);
    value |= reg->fn << 8;
    value |= reg->dev << 11;
    value |= reg->bus << 16;

    orig = inl(CONFIG_ADDRESS_REG);
    outl(CONFIG_ADDRESS_REG, value);

    ret = inw(CONFIG_DATA_REG);
    outl(CONFIG_ADDRESS_REG, orig);

    return ret;
}

uint8 pci_read_config_reg8(pci_reg *reg, uint8 offset)
{
    uint32 value, orig;
    uint8  ret;

    value = 0x80000000UL;
    value |= (offset & 0xfc);
    value |= reg->fn << 8;
    value |= reg->dev << 11;
    value |= reg->bus << 16;

    orig = inl(CONFIG_ADDRESS_REG);
    outl(CONFIG_ADDRESS_REG, value);

    ret = inb(CONFIG_DATA_REG);
    outl(CONFIG_ADDRESS_REG, orig);

    return ret;
}

void pci_write_config_reg32(pci_reg *reg, uint8 offset, const uint32 value)
{
    uint32 tmp_reg, orig;

    tmp_reg = 0x80000000UL;
    tmp_reg |= (offset & 0xfc);
    tmp_reg |= reg->fn << 8;
    tmp_reg |= reg->dev << 11;
    tmp_reg |= reg->bus << 16;

    orig = inl(CONFIG_ADDRESS_REG);

    outl(CONFIG_ADDRESS_REG, tmp_reg);
    outl(CONFIG_DATA_REG, value);
    outl(CONFIG_ADDRESS_REG, orig);
}

void pci_write_config_reg16(pci_reg *reg, uint8 offset ,const uint16 value)
{
    uint32  tmp_reg, orig;

    tmp_reg = 0x80000000UL;
    tmp_reg |= (offset & 0xfc);
    tmp_reg |= reg->fn << 8;
    tmp_reg |= reg->dev << 11;
    tmp_reg |= reg->bus << 16;

    orig = inl(CONFIG_ADDRESS_REG);

    outl(CONFIG_ADDRESS_REG, tmp_reg);
    outw(CONFIG_DATA_REG, value);
    outl(CONFIG_ADDRESS_REG, orig);
}

void pci_write_config_reg8(pci_reg *reg, uint8 offset, const uint8 value)
{
    uint32 tmp_reg, orig;

    tmp_reg = 0x80000000UL;
    tmp_reg |= (offset & 0xfc);
    tmp_reg |= reg->fn << 8;
    tmp_reg |= reg->dev << 11;
    tmp_reg |= reg->bus << 16;

    orig = inl(CONFIG_ADDRESS_REG);

    outl(CONFIG_ADDRESS_REG, tmp_reg);
    outb(CONFIG_DATA_REG, value);
    outl(CONFIG_ADDRESS_REG, orig);
}

void pci_init(void)
{

}

int pci_disable_IRQ_line(uint32 irq) { rt_hw_interrupt_mask(irq); return 0; }
int pci_enable_IRQ_line(uint32 irq)  { rt_hw_interrupt_umask(irq); return 0; }
int pci_sys_set_irq_handle(uint32 irq, void(*handle)(void)) { return rt_hw_interrupt_install(irq,handle,NULL,"PCI-ISR"); }
int pci_sys_irq_set_level_trigger(uint32 irq) { return 1; }
int pci_sys_irq_set_edge_trigger(uint32 irq)  { return 1; }
#endif
