/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
/* reference document 
 * http://tic-le-polard.blogspot.com/2015/01/emulate-pci-device-with-qemu.html
 *   https://github.com/grandemk/qemu_devices/blob/master/hello_tic.c
 *   https://github.com/grandemk/qemu_devices/blob/master/driver_pci.c
 * https://www.mindshare.com/files/ebooks/PCI%20System%20Architecture%20(4th%20Edition).pdf
 * http://nairobi-embedded.org/linux_pci_device_driver.html
 * https://en.wikipedia.org/wiki/PCI_configuration_space
 * http://wiki.osdev.org/PCI
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "pci_core.h"
#include "asdebug.h"
#include <rtthread.h>
#define AS_LOG_PCI 1
/* sys API wrapper */
#define _sys_printf    rt_kprintf
#define _sys_kmalloc   rt_malloc
#define _sys_memset32  memset
#define _sys_memcpy    memcpy
#define _sys_putchar(c)  rt_kprintf("%c",c)

#define     MAX_DEVICE                  256

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
static void do_pci_search_all_device(void);
static pci_vendor_info *search_vendor_info(uint16 vendor_id, uint16 device_id);
static int insert_new_pcidev(pci_dev *pci);
static void print_device_type(pci_dev *device);
static int check_multiple(pci_dev *device);
static void get_pci_resouce(pci_dev *device);
static void pciDecodeBar(pci_dev *device, uint8 offset, uint32 *base_addr,
		uint32 *addr_size, int *prefetch);

extern void __putchar(char ch);
extern void *asmalloc(size_t xWantedSize);

extern int pci_disable_IRQ_line(uint32 irq);
extern int pci_enable_IRQ_line(uint32 irq);
extern int pci_sys_set_irq_handle(uint32 irq, void (*handle)(void));
extern int pci_sys_irq_set_level_trigger(uint32 irq);
extern int pci_sys_irq_set_edge_trigger(uint32 irq);

/* ============================ [ DATAS     ] ====================================================== */
static pci_dev *pci_root = NULL;
/* ============================ [ LOCALS    ] ====================================================== */
static int disable_IRQ_line(uint32 irq) {
	return pci_disable_IRQ_line(irq);
}
static int enable_IRQ_line(uint32 irq) {
	return pci_enable_IRQ_line(irq);
}
static int _sys_set_irq_handle(uint32 irq, void (*handle)(void)) {
	return pci_sys_set_irq_handle(irq, handle);
}
static int _sys_irq_set_level_trigger(uint32 irq) {
	return pci_sys_irq_set_level_trigger(irq);
}
static int _sys_irq_set_edge_trigger(uint32 irq) {
	return pci_sys_irq_set_edge_trigger(irq);
}

/*
 バイナリーサーチで、デバイスを探す
 */
static pci_vendor_info *search_vendor_info(uint16 vendor_id, uint16 device_id) {
	int min, max;
	int median;
	int tmp;

	min = 0;
	max = (sizeof(pci_vendor_list) / sizeof(pci_vendor_info)) - 1;

	while (min <= max) {
		median = min + ((max - min) >> 1);
		tmp = pci_vendor_list[median].vendor_id - vendor_id;

		if (tmp == 0) {
			/* vendorは等しいようです */
			tmp = pci_vendor_list[median].device_id - device_id;
		}

		if (tmp < 0) {
			/* vendor_idの方が大きい */
			min = median + 1;
		} else if (tmp > 0) {
			/* vendor_idのほうが小さい */
			max = median - 1;
		} else {
			/* hit! */
			return &(pci_vendor_list[median]);
		}
	}
	return NULL;
}

static int insert_new_pcidev(pci_dev *pci) {
	pci_dev *ptr, *new_ptr;
	int i = 0;

	new_ptr = (pci_dev*) _sys_kmalloc(sizeof(pci_dev));

	if (new_ptr == NULL) {
		_sys_printf("pci malloc error!\n");
		return i;
	}

	_sys_memcpy((void*) new_ptr, (void*) pci, sizeof(pci_dev));

	new_ptr->next = NULL;
	ptr = pci_root;

	if (ptr != NULL) {
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = new_ptr;
		++i;
	} else {
		pci_root = new_ptr;
		++i;
	}
	return i;
}

static int traverse_pci_dev(void) {
	pci_dev *p;
	int i;
	char *intr_pin[] = { "INTA#", "INTB#", "INTC#", "INTD#" };

	for (p = pci_root; (p != NULL); p = p->next) {
		if (p->vendor != NULL) {
			_sys_printf(" pci%d: vendor:%x device:%x (%s)\n", p->pci_num,
					p->vendor->vendor_id, p->vendor->device_id,
					p->vendor->name);
		} else {
			_sys_printf(" pci%d: vendor:%x device:%x\n", p->pci_num,
					p->vendor_id, p->device_id);
		}

		_sys_printf(" Bus:%d Dev:%d Fnc:%d MultiFunction:", p->dev.bus,
				p->dev.dev, p->dev.fn);

		if (check_multiple(p)) {
			_sys_printf("Yes");
		} else {
			_sys_printf("No");
		}

		_sys_putchar('\n');

		if (p->intr_num != 0) {
			_sys_printf(" IRQ:%d(%s)\n", p->irq_num, intr_pin[p->intr_num - 1]);
		}

		for (i = 0; i < 6; i++) {
			if (p->mem_addr[i] != 0 && p->mem_size[i] != 0) {
				_sys_printf(" mem[%d]: %x..%x\n", i, p->mem_addr[i],
						p->mem_addr[i] + p->mem_size[i]);
			}
		}

		for (i = 0; i < 6; i++) {
			if (p->io_addr[i] != 0) {
				_sys_printf(" i/o[%d]: %x..%x\n", i, p->io_addr[i],
						p->io_addr[i] + p->io_size[i]);
			}
		}
		_sys_putchar('\n');
	}
	return 1;
}

static void do_pci_search_all_device(void) {
	pci_dev device;
	uint32 tmp;
	int i = 0;
	uint32 bus_id, device_num, function_num;

	for (bus_id = 0; bus_id <= 255; bus_id++) {
		for (device_num = 0; device_num <= 31; device_num++) {
			for (function_num = 0; function_num <= 7; function_num++) {
				_sys_memset32((void*) &device, 0, sizeof(pci_dev));

				device.dev.fn = function_num;
				device.dev.bus = bus_id;
				device.dev.dev = device_num;

				if ((pci_read_config_reg16(&device.dev, 0x0)) == 0xFFFF) {
					break;
				} else {
					pci_vendor_info *vendor;

					tmp = pci_read_config_reg32(&device.dev, 0x0);

					device.vendor_id = (uint32) tmp;
					device.device_id = (uint32) (tmp >> 16);
					device.pci_num = i;

					device.irq_num = (uint8) (pci_read_config_reg16(&device.dev,
							0x3c) & 0xff);
					device.intr_num = (uint8) ((pci_read_config_reg16(
							&device.dev, 0x3c) >> 8) & 0xff);

					device.dev.bus = bus_id;
					device.dev.dev = device_num;
					device.dev.fn = function_num;

					device.vendor = search_vendor_info(device.vendor_id,
							device.device_id);

					get_pci_resouce(&device);

					insert_new_pcidev(&device);

					i++;
				}

				disable_pci_resource(&device);
			}
		}
	}

	if (i == 0) {
		_sys_printf(" pci device not find\n");
	} else {
		traverse_pci_dev();
	}
}

static int check_multiple(pci_dev *device) {
	uint32 value;
	value = pci_read_config_reg32(&device->dev, 0x0c);
	if ((uint8) (value >> 16) & 0x80) {
		return 1;
	} else {
		return 0;
	}
}

static void print_device_type(pci_dev *device) {
	uint32 value;
	value = pci_read_config_reg32(&device->dev, 0xc);
	switch ((uint8) (value >> 16) & 0x7F) {
	case 0x0:
		_sys_printf(" (normal device)");
		break;
	case 0x1:
		_sys_printf(" (PCI-PCI bridge)");
		break;
	case 0x2:
		_sys_printf(" (Card Bus bridge)");
		break;
	}
}

static void get_pci_resouce(pci_dev *device) {
	uint32 offset;
	int i;
	uint32 base_addr, addr_size;
	int prefetch;

	for (i = 0; i < 6; i++) {
		device->mem_size[i] = device->io_size[i] = device->mem_addr[i] =
				device->io_addr[i] = 0x0;
	}

	for (offset = 0x10, i = 0; offset <= 0x24; offset += 0x4, i++) {
		pciDecodeBar(device, offset, &base_addr, &addr_size, &prefetch);
		if (prefetch == -1) {
			device->io_addr[i] = base_addr;
			device->io_size[i] = addr_size;
		} else {
			device->mem_addr[i] = base_addr;
			device->mem_size[i] = addr_size;
		}
	}

}

/* check http://wiki.osdev.org/PCI#Base_Address_Registers */
static void pciDecodeBar(pci_dev *device, uint8 offset, uint32 *base_addr,
		uint32 *addr_size, int *prefetch) {
	uint32 orig = pci_read_config_reg32(&device->dev, offset);
	uint32 type = orig & 0xf;
	uint32 addr;
	uint32 size;
	uint32 tmp;

	disable_pci_resource(device);
	pci_write_config_reg32(&device->dev, offset, 0xffffffff);

	*addr_size = *base_addr = 0;

	switch (type & 1) {
	case 0:
		/* mem */
		tmp = pci_read_config_reg32(&device->dev, offset) & ~0xf;

		addr = orig & ~0xf;
#ifdef __X86__
		if(addr <= 0){
			break;
		}
#endif
		switch (type & 6) {
		case 0:
		case 2:
			if (0x10 > tmp) {
				/* これは無効 */
				pci_write_config_reg32(&device->dev, offset, orig);
				return;
			} else if (0x10 <= tmp && 0xff >= tmp) {
				size = ((~tmp) & 0xff) + 1;
			} else if (0x100 <= tmp && 0xffff >= tmp) {
				size = ((~tmp) & 0xffff) + 1;
			} else if (0x10000 <= tmp && 0xffffff >= tmp) {
				size = ((~tmp) & 0xffffff) + 1;
			} else if (0x1000000 <= tmp && 0xffffffff >= tmp) {
				size = ((~tmp) & 0xffffffff) + 1;
			}
			break;
		case 4:
			/* 64bitだよ〜ん */
			break;
		}
#ifndef __X86__
		if((addr == 0) && (device->vendor != NULL) && (device->vendor->mmio_cfg != NULL))
		{
			addr = device->vendor->mmio_cfg->mem_addr[(offset-0x10)/4];
			asAssert(size == device->vendor->mmio_cfg->mem_size[(offset-0x10)/4]);
			asAssert((addr & 0x0f) == 0); /* 16-Byte Aligned Base Address */
			orig = (orig & ~0xf) | addr;
		}
		else
		{
			_sys_printf("Error: PCI device %04X:%04X need %s mmio with size 0x%08X for BAR%d\n", \
					device->vendor_id, device->device_id, \
					(type & 8)?"    prefetchable":"non-prefetchable", \
					size, (offset-0x10)/4);
		}
#endif
		*base_addr = addr;
		*addr_size = size;

		if (type & 8) {
			*prefetch = 1;
		} else {
			*prefetch = 0;
		}
		break;

	case 1:
		/* i/o */
		tmp = pci_read_config_reg32(&device->dev, offset) & ~0x3;
		addr = orig & ~0x3;
#ifdef __X86__
		if(addr <= 0){
			break;
		}
#endif
		if (0x4 > tmp) {
			/* これは無効 */
			break;
		} else if (0x4 <= tmp && 0xff >= tmp) {
			size = ((~tmp) & 0xff) + 1;
		} else if (0x100 <= tmp && 0xffff >= tmp) {
			size = ((~tmp) & 0xffff) + 1;
		} else if (0x10000 <= tmp && 0xffffff >= tmp) {
			size = ((~tmp) & 0xffffff) + 1;
		} else if (0x1000000 <= tmp && 0xffffffff >= tmp) {
			size = ((~tmp) & 0xffffffff) + 1;
		}
#ifndef __X86__
		if((addr == 0) && (device->vendor != NULL) && (device->vendor->mmio_cfg != NULL) \
				&& (size == device->vendor->mmio_cfg->io_size[(offset-0x10)/4]))
		{
			addr = device->vendor->mmio_cfg->io_addr[(offset-0x10)/4];
			asAssert((addr & 0x03) == 0); /* 4-Byte Aligned Base Address */
			orig = (orig & ~0x3) | addr;
		}
		else
		{
			_sys_printf("Error: PCI device %04X:%04X need port io with size 0x%08X for BAR%d\n", \
					device->vendor_id, device->device_id, \
					size, (offset-0x10)/4);
		}
#endif
		*base_addr = addr;
		*addr_size = size;

		/* type i/o */
		*prefetch = -1;

		break;

	}
	pci_write_config_reg32(&device->dev, offset, orig);
	enable_pci_resource(device);
}
/* ============================ [ FUNCTIONS ] ====================================================== */
int pci_register_irq(uint32 irq_num, void (*handler)()) {
	disable_IRQ_line(irq_num);
	if (_sys_irq_set_level_trigger(irq_num)) {
		_sys_set_irq_handle(irq_num, handler);
		enable_IRQ_line(irq_num);
		return 1;
	}
	return 0;
}

int pci_unregister_irq(uint32 irq_num) {
	disable_IRQ_line(irq_num);
	return (_sys_irq_set_edge_trigger(irq_num));
}

void disable_pci_resource(pci_dev *device) {
	uint16 value;
	value = pci_read_config_reg16(&device->dev, 0x04);
	value &= ~0x103;
	pci_write_config_reg16(&device->dev, 0x04, value);
}

void enable_pci_resource(pci_dev *device) {
	uint16 value;
	value = pci_read_config_reg16(&device->dev, 0x04);
	value |= 0x103;
	pci_write_config_reg16(&device->dev, 0x04, value);
}

void enable_pci_interrupt(pci_dev *device) {
	uint16 value;
	value = pci_read_config_reg16(&device->dev, 0x04);
	value &= ~0x400;
	pci_write_config_reg16(&device->dev, 0x04, value);
}

void disable_pci_interrupt(pci_dev *device) {
	uint16 value;
	value = pci_read_config_reg16(&device->dev, 0x04);
	value |= 0x400;
	pci_write_config_reg16(&device->dev, 0x04, value);
}

pci_dev *find_pci_dev_from_id(uint32 vendor_id, uint32 device_id) {
	pci_dev *ptr;

	for (ptr = pci_root; !(ptr == NULL); ptr = ptr->next) {
		if (ptr->vendor_id == vendor_id && ptr->device_id == device_id) {
			return ptr;
		}
	}

	return NULL;

}

pci_dev *find_pci_dev_from_reg(pci_reg *reg) {
	pci_dev *p;
	/* たいした数じゃないし全数探査でよか */
	for (p = pci_root; !(p == NULL); p = p->next) {
		if ((p->dev.bus & p->dev.dev & p->dev.fn)
				== (reg->bus & reg->dev & reg->fn)) {
			return p;
		}
	}
	return NULL;
}

void pci_search_all_device(void) {
	do_pci_search_all_device();
}

#endif /* USE_PCI */
