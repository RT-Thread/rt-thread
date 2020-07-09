/*
 * File      : gt9xx.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey      first version
 */
#ifndef _GT9XX_H_
#define _GT9XX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <rtdevice.h>
#include <rtthread.h>

#define GT910_ADDR_BABBH
//#define GT910_ADDR_2829H

#ifdef GT910_ADDR_BABBH
#define GT910_IIC_ADDR         0x14//0x14//0x5D//
//#define GT910_IIC_RADDR         0x29
//#define GT910_IIC_WADDR         0x28
#else
#define GT910_IIC_RADDR         0x29
#define GT910_IIC_WADDR         0x28
#endif

extern uint16_t show_len;
extern uint16_t total_len;
extern uint8_t gtp_rawdiff_mode;

extern int tpd_halt;
extern int gtp_send_cfg(struct rt_i2c_bus_device *i2c);
extern void gtp_reset_guitar(struct rt_i2c_bus_device *i2c, int ms);
extern void gtp_int_sync(int ms);
extern uint8_t gup_init_update_proc(struct rt_i2c_bus_device *i2c);
extern uint8_t gup_init_fw_proc(struct rt_i2c_bus_device *i2c);

extern int gtp_i2c_read(struct rt_i2c_bus_device *i2c, uint8_t *buf, int len);
extern int gtp_i2c_write(struct rt_i2c_bus_device *i2c,uint8_t *buf,int len);
extern int i2c_write_bytes(struct rt_i2c_bus_device *i2c, uint16_t addr, uint8_t *txbuf, int len);
extern int i2c_read_bytes(struct rt_i2c_bus_device *i2c, uint16_t addr, uint8_t *rxbuf, int len);
extern int i2c_read_dbl_check(struct rt_i2c_bus_device *i2c, uint16_t addr, uint8_t *rxbuf, int len);
extern int gtp_i2c_read_dbl_check(struct rt_i2c_bus_device *i2c, uint16_t addr, uint8_t *rxbuf, int len);

extern void mt65xx_eint_unmask(uint32_t line);
extern void mt65xx_eint_mask(uint32_t line);

#ifdef __cplusplus
}
#endif

#endif /* _GT9XX_H_ */
