#ifndef __RTGUI_FONT_TTF_H__
#define __RTGUI_FONT_TTF_H__

#include <rtgui/dc.h>
#include <rtgui/font.h>

#ifdef __cplusplus
extern "C" {
#endif

rtgui_font_t *rtgui_freetype_font_create(const char *filename, int bold, int italic, rt_size_t size);
void rtgui_freetype_font_destroy(rtgui_font_t *font);

#ifdef __cplusplus
}
#endif

#endif
