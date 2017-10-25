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
 * 
 * This is copied from [tinyos](https://github.com/ddk50/tinyos) pci-main
 */
#ifndef _PCI_CORE_H_
#define _PCI_CORE_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "pci_ids.h"
#include "pci.h"

/* ============================ [ MACROS    ] ====================================================== */
#define     PCI_DEVICE(vid, did, name)                              \
	{PCI_VENDOR_ID_##vid, PCI_DEVICE_ID_##did, (name), 0xff, mmiocfg_##vid##_##did}

#define     PCI_BRIDGE(vid, did, name, bridge)                          \
	{PCI_VENDOR_ID_##vid, PCI_DEVICE_ID_##did, (name), (bridge), NULL}

/* linux compatible version API */
#define pci_bus_read_config_byte(pdev,offset)     pci_read_config_reg8(&(pdev->dev),offset)
#define pci_bus_read_config_word(pdev,offset)     pci_read_config_reg16(&(pdev->dev),offset)
#define pci_bus_read_config_dword(pdev,offset)    pci_read_config_reg32(&(pdev->dev),offset)
#define pci_bus_write_config_byte(pdev,offset,v)  pci_write_config_reg8(&(pdev->dev),offset,v)
#define pci_bus_write_config_word(pdev,offset,v)  pci_write_config_reg16(&(pdev->dev),offset,v)
#define pci_bus_write_config_dword(pdev,offset,v) pci_write_config_reg32(&(pdev->dev),offset,v)
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	uint32					mem_addr[6];
	uint32					mem_size[6];
	uint16					io_addr[6];
	uint16					io_size[6];
} pci_mmio_cfg;
typedef struct __pci_vendor_info {
	uint16			vendor_id;			/* vendor id */
	uint16			device_id;			/* device id */
	const char		*name;			/* device name */
	uint8			bridge_type;	/* bridge type or 0xff */
	const pci_mmio_cfg* mmio_cfg;
} pci_vendor_info;

typedef struct __pci_device_info {
	pci_vendor_info		info;
	uint32				base_addr;
	uint8				base_class;
	uint8				sub_class;
} pci_device_info;

typedef struct __pci_res {
	uint8		bus;		/* バス番号 */
	uint8		dev;		/* デバイス番号 */
	uint8		fn;			/* 機能番号 */
} pci_reg;

typedef struct __pci_dev {
	int						pci_num;
	struct __pci_dev		*next;
	uint32					mem_addr[6];
	uint32					mem_size[6];
	uint16					io_addr[6];
	uint16					io_size[6];
	uint8					irq_num;
	uint8					intr_num;
	uint16					vendor_id;
	uint16					device_id;
	uint16					subsys_id;
	pci_vendor_info			*vendor;
	pci_reg					dev;
	void*					priv;
} pci_dev;


#include "pci_cfg.h"
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int pci_generic_config_write(unsigned int busnr, unsigned int devfn,
							 int where, int size, u32 val);
int pci_generic_config_read(unsigned int busnr, unsigned int devfn,
							int where, int size, u32 *val);

uint8 pci_read_config_reg8(pci_reg*, uint8);
uint16 pci_read_config_reg16(pci_reg*, uint8);
uint32 pci_read_config_reg32(pci_reg*, uint8);

void pci_write_config_reg8(pci_reg*, uint8, const uint8);
void pci_write_config_reg16(pci_reg*, uint8, const uint16);
void pci_write_config_reg32(pci_reg*, uint8, const uint32);

void disable_pci_resource(pci_dev*);
void enable_pci_resource(pci_dev*);

void enable_pci_interrupt(pci_dev*);
void disable_pci_interrupt(pci_dev*);

int pci_register_irq(uint32 irq_num, void (*handler)());
int pci_unregister_irq(uint32 irq_num);

pci_dev *find_pci_dev_from_reg(pci_reg *reg);
pci_dev *find_pci_dev_from_id(uint32 vendor_id, uint32 device_id);

void pci_search_all_device(void);
#endif /* _PCI_CORE_H_ */
