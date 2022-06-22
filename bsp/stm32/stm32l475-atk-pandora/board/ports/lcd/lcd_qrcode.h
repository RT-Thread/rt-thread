#ifndef __LCD_QRCODE_H__
#define __LCD_QRCODE_H__

#include <rtconfig.h>

#ifdef BSP_USING_LCD_QRCODE
#include <rtdef.h>
#include <qrcode.h>

rt_err_t lcd_show_qrcode(rt_uint16_t x, rt_uint16_t y, rt_uint8_t version, rt_uint8_t ecc, const char *data, rt_uint8_t enlargement);
#endif /* BSP_USING_LCD_QRCODE */

#endif
