#ifndef __RTGUI_BLIT_H__
#define __RTGUI_BLIT_H__

#include <rtgui/rtgui.h>

typedef void (*rtgui_blit_line_func)(rt_uint8_t* dst, rt_uint8_t* src, int line);
rtgui_blit_line_func rtgui_blit_line_get(int dst_bpp, int src_bpp);

#endif
