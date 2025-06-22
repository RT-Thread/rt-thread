/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_DCACHE_H
#define USB_DCACHE_H

#ifdef CONFIG_USB_DCACHE_ENABLE
#if CONFIG_USB_ALIGN_SIZE % 32
#error "CONFIG_USB_ALIGN_SIZE must be multiple of 32"
#endif
void usb_dcache_clean(uintptr_t addr, size_t size);
void usb_dcache_invalidate(uintptr_t addr, size_t size);
void usb_dcache_flush(uintptr_t addr, size_t size);
#else
#define usb_dcache_clean(addr, size)
#define usb_dcache_invalidate(addr, size)
#define usb_dcache_flush(addr, size)
#endif

#endif /* USB_DCACHE_H */
