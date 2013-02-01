/*
 * File      : digfont.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-21     pife         first version
 */

#include <rtthread.h>
#include <rtgui/rtgui.h>
#include <rtgui/dc.h>
#include <rtgui/widgets/digfont.h>

#define DIGFONT_V  1
#define DIGFONT_H  0

int rtgui_digitfont_create(struct rtgui_digitfont * font)
{
    int i;
    int half;
    int space;
    int seg35_y;
    int hight;
    struct rtgui_digitfont_data * data, *databuf;
    struct rtgui_digitfont_data temp, temp2;;

    data= rt_malloc(sizeof(struct rtgui_digitfont_data) * 7 * font->seg1_nr);
    if (data== RT_NULL)
    {
        rt_kprintf("out of memory.\n");
        goto __err;
    }
    databuf = font->data = data;

    data = &temp;
    half = font->seg1_nr >> 1;
    space = font->seg1_hspace;
    seg35_y = font->seg1_vspace + font->seg2_len + (half<<1) - font->seg1_vspace;
    hight = (font->seg1_vspace << 1) + font->seg2_len + font->seg3_len + (half << 1) - 1;

    //seg 1
    data->type = DIGFONT_H;
    data->x =  font->seg1_hspace;
    data->y = 0;
    data->len = font->seg1_len;

    *databuf++ = *data;
    for(i=1; i<font->seg1_nr; i++)
    {
        data->len -= 2;
        data->x ++;
        data->y ++;
        *databuf++ = *data;
    }

    //seg 2
    data->type = DIGFONT_V;
    data->x =  (font->seg1_hspace << 1) + font->seg1_len -1;
    data->y = font->seg1_vspace ;
    data->len = font->seg2_len;
    *databuf++ = *data;
    for(i=1; i<font->seg1_nr; i++)
    {
        if (i >= half)
        {
            data->len -=  2;
        }
        data->x --;
        data->y ++;
        *databuf++ = *data;
    }

    //seg 3
    data->type = DIGFONT_V;
    data->x =  (font->seg1_hspace << 1) + font->seg1_len -1;
    data->y = seg35_y;
    data->len = font->seg3_len;
    *databuf++ = *data;
    temp2 = *data;
    for(i=1; i<font->seg1_nr; i++)
    {
        if (i < half)
            data->y --;
        else
        {
            data->len -=  2;
            data->y ++;
        }

        data->x --;
        *databuf++ = *data;
    }

    // seg4
    data->type = DIGFONT_H;
    data->x =  font->seg1_hspace;
    data->y = hight -1;
    data->len = font->seg1_len;
    *databuf++ = *data;
    for(i=1; i<font->seg1_nr; i++)
    {
        data->len -= 2;
        data->x ++;
        data->y --;
        *databuf++ = *data;
    }

    //seg5
    data->type = DIGFONT_V;
    data->x = 0;
    data->y = seg35_y;
    data->len = font->seg3_len;
    *databuf++ = *data;

    for(i=1; i<font->seg1_nr; i++)
    {
        if (i < half)
            data->y --;
        else
        {
            data->len -=  2;
            data->y ++;
        }

        data->x ++;
        *databuf++ = *data;
    }

    //seg 6
    data->type = DIGFONT_V;
    data->x = 0;
    data->y = font->seg1_vspace ;
    data->len = font->seg2_len;
    *databuf++ = *data;
    for(i=1; i<font->seg1_nr; i++)
    {
        if (i >= half)
        {
            data->len -=  2;
        }
        data->x ++;
        data->y ++;
        *databuf++ = *data;
    }

    //seg7
    data->type = DIGFONT_H;
    data->x = font->seg1_hspace + half - 1;
    data->y = font->seg1_vspace + font->seg2_len + half -1;
    data->len = (font->seg1_hspace << 1) + font->seg1_len - \
                ((font->seg1_hspace + half -1) << 1);
    *databuf++ = *data;
    temp2 = *data;
    for(i=0; i<half; i++)
    {
        data->x ++;
        data->y --;
        data->len -=  2;
        *databuf++ = *data;
    }

    *data = temp2;
    for (i=0; i<half; i++)
    {
        data->x ++;
        data->y ++;
        data->len -=  2;
        *databuf++ = *data;
    }

    return 0;

__err:
    return -1;
}

int rtgui_dc_draw_digitfont(struct rtgui_dc *dc, struct rtgui_digitfont * font, rtgui_rect_t * rect)
{
    int i, size;
    struct rtgui_digitfont_data * data;

    size = font->seg1_nr * 7;
    data = font->data;

    for(i=0; i<size; i++)
    {
        if (data->type == DIGFONT_H)
            rtgui_dc_draw_hline(dc, rect->x1 + data->x, \
                                rect->x1 + data->x + data->len, rect->y1 + data->y);
        else
            rtgui_dc_draw_vline(dc, rect->x1 + data->x, rect->y1 + data->y, \
                                rect->y1 + data->y + data->len);

        data++;
    }
}

const char digtube_code_table[] =
{ 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,};

int rtgui_dc_draw_digitfont_code(struct rtgui_dc *dc, struct rtgui_digitfont * font, rtgui_rect_t * rect, char code)
{
	int i,j;
	struct rtgui_digitfont_data * data;
	rtgui_color_t color;

	data = font->data;
	
	color = RTGUI_DC_FC(dc);
	for(i=0; i<7; i++)
	{
		if (code & (1 << i))
			RTGUI_DC_FC(dc) = color;
		else
			RTGUI_DC_FC(dc) = RTGUI_DC_BC(dc);

		for (j=0; j<font->seg1_nr; j++)
		{
			if (data->type == DIGFONT_H)
				rtgui_dc_draw_hline(dc, rect->x1 + data->x, \
				rect->x1 + data->x + data->len, rect->y1 + data->y);
			else
				rtgui_dc_draw_vline(dc, rect->x1 + data->x, rect->y1 + data->y, \
				rect->y1 + data->y + data->len);

			data++;
		}	
	}
	RTGUI_DC_FC(dc) = color;

	return 0;
}

int rtgui_get_digfont_metrics(struct rtgui_digitfont * font, rtgui_rect_t * rect) 
{
	int half = font->seg1_nr >> 1;
	rect->x1 = 0;
	rect->y1 = 0;
	rect->x2 = (font->seg1_hspace << 1) + font->seg1_len;
	rect->y2 = (font->seg1_vspace << 1) + font->seg2_len + font->seg3_len + (half << 1) - 1;
	return 0;
}

/* debug */
struct rtgui_digitfont digitfont_40 =
{
	34,  //int seg1_len;
	3,   //int seg1_hspace;
	1,   //int seg1_vpace;
	9,   //int seg1_nr; //9
	30,  //int seg2_len;
	30,  //int seg3_len;
	RT_NULL,
};

#ifdef _WIN32
#include  <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char fontbuf[80];
int digfont_file(char * name, struct rtgui_digitfont * font)
{
    int i;
    int size;
    FILE * file;
    struct rtgui_digitfont_data * data;

    if (font->data == RT_NULL)
        rtgui_digitfont_create(font);

    /* create a file to store data */
    file = fopen(name, "wb + ");
    if (file == RT_NULL)
    {
        rt_kprintf("open < % s > failed.\n", name);
        return -1;
    }
    data = font->data;
    size = font->seg1_nr * 7;

    for( i=0; i<size; i++)
    {
        if ((i % (font->seg1_nr)) == 0)
        {
            sprintf(fontbuf, "\n/* seg <%d> */\n", i/font->seg1_nr + 1);
            fwrite(fontbuf, strlen(fontbuf), 1, file);
        }

        sprintf(fontbuf, " { % 2d, % 2d, % 2d, % 2d}, \n", data->x, data->y, data->len, data->type);
        fwrite(fontbuf, strlen(fontbuf), 1, file);
        data ++;
    }
    fclose(file);

    return 0;
}
#if defined(RT_USING_FINSH)
#include <finsh.h>
FINSH_FUNCTION_EXPORT(digfont_file, create the font file of digit font)
#endif

#endif