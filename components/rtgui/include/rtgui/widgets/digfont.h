#ifndef DIG_FONT_H
#define DIG_FONT_H

struct rtgui_digitfont_data
{
    rt_uint16_t x;
    rt_uint16_t y;
    rt_uint16_t len;
    rt_uint16_t type; //水平和垂直
};

struct rtgui_digitfont
{
    int seg1_len;
    int seg1_hspace;
    int seg1_vspace;
    int seg1_nr; //9

    int seg2_len;

    int seg3_len;
    struct rtgui_digitfont_data *data;
};


typedef struct rtgui_digitfont rtgui_digitfont_t;

extern struct rtgui_digitfont digitfont_40;
extern const char digtube_code_table[];

int rtgui_digitfont_create(struct rtgui_digitfont *font);
int rtgui_dc_draw_digitfont(struct rtgui_dc *dc, struct rtgui_digitfont *font, rtgui_rect_t *rect);
int rtgui_get_digfont_metrics(struct rtgui_digitfont * font, rtgui_rect_t * rect);
int rtgui_dc_draw_digitfont_code(struct rtgui_dc *dc, struct rtgui_digitfont * font, rtgui_rect_t * rect, char code);

#endif