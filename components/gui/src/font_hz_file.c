/*
 * Cached HZ font engine
 */
#include <rtgui/dc.h>
#include <rtgui/font.h>
#include <rtgui/tree.h>
#include <rtgui/rtgui_system.h>

#ifdef RTGUI_USING_HZ_FILE
#ifdef _WIN32_NATIVE
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#define open    _open
#define close   _close
#define read    _read
#define write   _write
#define unlink  _unlink
#else
#include <dfs_posix.h>
#endif

#define HZ_CACHE_MAX    64

static int _font_cache_compare(struct hz_cache *node1, struct hz_cache *node2);

static void rtgui_hz_file_font_load(struct rtgui_font *font);
static void rtgui_hz_file_font_draw_text(struct rtgui_font *font, struct rtgui_dc *dc, const char *text, rt_ubase_t len, struct rtgui_rect *rect);
static void rtgui_hz_file_font_get_metrics(struct rtgui_font *font, const char *text, rtgui_rect_t *rect);
const struct rtgui_font_engine rtgui_hz_file_font_engine =
{
    RT_NULL,
    rtgui_hz_file_font_load,
    rtgui_hz_file_font_draw_text,
    rtgui_hz_file_font_get_metrics
};

SPLAY_PROTOTYPE(cache_tree, hz_cache, hz_node, _font_cache_compare);
SPLAY_GENERATE(cache_tree, hz_cache, hz_node, _font_cache_compare);

static int _font_cache_compare(struct hz_cache *cache_1, struct hz_cache *cache_2)
{
    if (cache_1->hz_id > cache_2->hz_id) return 1;
    if (cache_1->hz_id < cache_2->hz_id) return -1;

    return 0;
}

static rt_uint8_t *_font_cache_get(struct rtgui_hz_file_font *font, rt_uint16_t hz_id)
{
    rt_uint32_t seek;
    struct hz_cache *cache, search;

    search.hz_id = hz_id;

    /* enter critical */
    rtgui_enter_critical();

    cache = SPLAY_FIND(cache_tree, &(font->cache_root), &search);
    if (cache != RT_NULL)
    {
        /* exit critical */
        rtgui_exit_critical();

        /* found it */
        return (rt_uint8_t *)(cache + 1);
    }

    /* exit critical */
    rtgui_exit_critical();

    /* can not find it, load to cache */
    cache = (struct hz_cache *) rtgui_malloc(sizeof(struct hz_cache) + font->font_data_size);
    if (cache == RT_NULL)
        return RT_NULL; /* no memory yet */

    cache->hz_id = hz_id;
    seek = 94 * (((hz_id & 0xff) - 0xA0) - 1) + ((hz_id >> 8) - 0xA0) - 1;
    seek *= font->font_data_size;

    /* read hz font data */
    if ((lseek(font->fd, seek, SEEK_SET) < 0) ||
            read(font->fd, (char *)(cache + 1), font->font_data_size) !=
            font->font_data_size)
    {
        rtgui_free(cache);
        return RT_NULL;
    }

    /* enter critical */
    rtgui_enter_critical();

    if (font->cache_size >= HZ_CACHE_MAX)
    {
        /* remove a cache */
        struct hz_cache *left;
        left = font->cache_root.sph_root;
        while (SPLAY_LEFT(left, hz_node) != RT_NULL) left = SPLAY_LEFT(left, hz_node);

        /* remove the left node */
        SPLAY_REMOVE(cache_tree, &(font->cache_root), left);
        rtgui_free(left);
        font->cache_size --;
    }

    /* insert to cache */
    SPLAY_INSERT(cache_tree, &(font->cache_root), cache);
    font->cache_size ++;

    /* exit critical */
    rtgui_exit_critical();

    return (rt_uint8_t *)(cache + 1);
}

static void rtgui_hz_file_font_load(struct rtgui_font *font)
{
    struct rtgui_hz_file_font *hz_file_font = (struct rtgui_hz_file_font *)font->data;
    RT_ASSERT(hz_file_font != RT_NULL);

    hz_file_font->fd = open(hz_file_font->font_fn, O_RDONLY, 0);
    if (hz_file_font->fd < 0)
    {
        rt_kprintf("RTGUI: could not open the font file:%s\n", hz_file_font->font_fn);
        rt_kprintf("RTGUI: please mount the fs first and make sure the file is there\n");
    }
}

static void _rtgui_hz_file_font_draw_text(struct rtgui_hz_file_font *hz_file_font, struct rtgui_dc *dc, const char *text, rt_ubase_t len, struct rtgui_rect *rect)
{
    rt_uint8_t *str;
    rtgui_color_t bc;
    rt_uint16_t style;
    register rt_base_t h, word_bytes;

    /* get text style */
    style = rtgui_dc_get_gc(dc)->textstyle;
    bc = rtgui_dc_get_gc(dc)->background;

    /* drawing height */
    h = (hz_file_font->font_size + rect->y1 > rect->y2) ?
        rect->y2 - rect->y1 : hz_file_font->font_size;
    word_bytes = (hz_file_font->font_size + 7) / 8;

    str = (rt_uint8_t *)text;

    while (len > 0 && rect->x1 < rect->x2)
    {
        const rt_uint8_t *font_ptr;
        register rt_base_t i, j, k;

        /* get font pixel data */
        font_ptr = _font_cache_get(hz_file_font, *str | (*(str + 1) << 8));

        /* draw word */
        for (i = 0; i < h; i ++)
        {
            for (j = 0; j < word_bytes; j++)
                for (k = 0; k < 8; k++)
                {
                    if (((font_ptr[i * word_bytes + j] >> (7 - k)) & 0x01) != 0 &&
                            (rect->x1 + 8 * j + k < rect->x2))
                    {
                        rtgui_dc_draw_point(dc, rect->x1 + 8 * j + k, rect->y1 + i);
                    }
                    else if (style & RTGUI_TEXTSTYLE_DRAW_BACKGROUND)
                    {
                        rtgui_dc_draw_color_point(dc, rect->x1 + 8 * j + k, rect->y1 + i, bc);
                    }
                }
        }

        /* move x to next character */
        rect->x1 += hz_file_font->font_size;
        str += 2;
        len -= 2;
    }
}

static void rtgui_hz_file_font_draw_text(struct rtgui_font *font, struct rtgui_dc *dc, const char *text, rt_ubase_t length, struct rtgui_rect *rect)
{
    rt_uint32_t len;
    struct rtgui_font *efont;
    struct rtgui_hz_file_font *hz_file_font = (struct rtgui_hz_file_font *)font->data;

    RT_ASSERT(dc != RT_NULL);
    RT_ASSERT(hz_file_font != RT_NULL);

    /* get English font */
    efont = rtgui_font_refer("asc", hz_file_font->font_size);
    if (efont == RT_NULL) efont = rtgui_font_default(); /* use system default font */

    while (length > 0)
    {
        len = 0;
        while (((rt_uint8_t) * (text + len)) < 0x80 && *(text + len) && len < length) len ++;
        /* draw text with English font */
        if (len > 0)
        {
            rtgui_font_draw(efont, dc, text, len, rect);

            text += len;
            length -= len;
        }

        len = 0;
        while (((rt_uint8_t) * (text + len)) >= 0x80 && len < length) len ++;
        if (len > 0)
        {
            _rtgui_hz_file_font_draw_text(hz_file_font, dc, text, len, rect);

            text += len;
            length -= len;
        }
    }

    rtgui_font_derefer(efont);
}

static void rtgui_hz_file_font_get_metrics(struct rtgui_font *font, const char *text, rtgui_rect_t *rect)
{
    struct rtgui_hz_file_font *hz_file_font = (struct rtgui_hz_file_font *)font->data;
    RT_ASSERT(hz_file_font != RT_NULL);

    /* set metrics rect */
    rect->x1 = rect->y1 = 0;
    rect->x2 = (rt_int16_t)(hz_file_font->font_size / 2 * rt_strlen((const char *)text));
    rect->y2 = hz_file_font->font_size;
}
#endif
