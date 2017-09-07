/*
 * File      : image_xpm.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#include <stdio.h>
#include <string.h>

#include <rtgui/filerw.h>
#include <rtgui/image_xpm.h>
#include <rtgui/rtgui_system.h>

#ifdef RTGUI_IMAGE_XPM
#define XPM_MAGIC_LEN       9

static rt_bool_t rtgui_image_xpm_check(struct rtgui_filerw *file);
static rt_bool_t rtgui_image_xpm_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
static void rtgui_image_xpm_unload(struct rtgui_image *image);
static void rtgui_image_xpm_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);

struct rtgui_image_engine rtgui_image_xpm_engine =
{
    "xpm",
    {RT_NULL},
    rtgui_image_xpm_check,
    rtgui_image_xpm_load,
    rtgui_image_xpm_unload,
    rtgui_image_xpm_blit,
};

struct rgb_item
{
    char *name;
    rt_uint8_t r;
    rt_uint8_t g;
    rt_uint8_t b;
};

const struct rgb_item rgbRecord[234] =
{
    {"AliceBlue", 240, 248, 255},
    {"AntiqueWhite", 250, 235, 215},
    {"Aquamarine", 50, 191, 193},
    {"Azure", 240, 255, 255},
    {"Beige", 245, 245, 220},
    {"Bisque", 255, 228, 196},
    {"Black", 0, 0, 0},
    {"BlanchedAlmond", 255, 235, 205},
    {"Blue", 0, 0, 255},
    {"BlueViolet", 138, 43, 226},
    {"Brown", 165, 42, 42},
    {"burlywood", 222, 184, 135},
    {"CadetBlue", 95, 146, 158},
    {"chartreuse", 127, 255, 0},
    {"chocolate", 210, 105, 30},
    {"Coral", 255, 114, 86},
    {"CornflowerBlue", 34, 34, 152},
    {"cornsilk", 255, 248, 220},
    {"Cyan", 0, 255, 255},
    {"DarkGoldenrod", 184, 134, 11},
    {"DarkGreen", 0, 86, 45},
    {"DarkKhaki", 189, 183, 107},
    {"DarkOliveGreen", 85, 86, 47},
    {"DarkOrange", 255, 140, 0},
    {"DarkOrchid", 139, 32, 139},
    {"DarkSalmon", 233, 150, 122},
    {"DarkSeaGreen", 143, 188, 143},
    {"DarkSlateBlue", 56, 75, 102},
    {"DarkSlateGray", 47, 79, 79},
    {"DarkTurquoise", 0, 166, 166},
    {"DarkViolet", 148, 0, 211},
    {"DeepPink", 255, 20, 147},
    {"DeepSkyBlue", 0, 191, 255},
    {"DimGray", 84, 84, 84},
    {"DodgerBlue", 30, 144, 255},
    {"Firebrick", 142, 35, 35},
    {"FloralWhite", 255, 250, 240},
    {"ForestGreen", 80, 159, 105},
    {"gainsboro", 220, 220, 220},
    {"GhostWhite", 248, 248, 255},
    {"Gold", 218, 170, 0},
    {"Goldenrod", 239, 223, 132},
    {"Gray", 126, 126, 126},
    {"Gray0", 0, 0, 0},
    {"Gray1", 3, 3, 3},
    {"Gray10", 26, 26, 26},
    {"Gray100", 255, 255, 255},
    {"Gray11", 28, 28, 28},
    {"Gray12", 31, 31, 31},
    {"Gray13", 33, 33, 33},
    {"Gray14", 36, 36, 36},
    {"Gray15", 38, 38, 38},
    {"Gray16", 41, 41, 41},
    {"Gray17", 43, 43, 43},
    {"Gray18", 46, 46, 46},
    {"Gray19", 48, 48, 48},
    {"Gray2", 5, 5, 5},
    {"Gray20", 51, 51, 51},
    {"Gray21", 54, 54, 54},
    {"Gray22", 56, 56, 56},
    {"Gray23", 59, 59, 59},
    {"Gray24", 61, 61, 61},
    {"Gray25", 64, 64, 64},
    {"Gray26", 66, 66, 66},
    {"Gray27", 69, 69, 69},
    {"Gray28", 71, 71, 71},
    {"Gray29", 74, 74, 74},
    {"Gray3", 8, 8, 8},
    {"Gray30", 77, 77, 77},
    {"Gray31", 79, 79, 79},
    {"Gray32", 82, 82, 82},
    {"Gray33", 84, 84, 84},
    {"Gray34", 87, 87, 87},
    {"Gray35", 89, 89, 89},
    {"Gray36", 92, 92, 92},
    {"Gray37", 94, 94, 94},
    {"Gray38", 97, 97, 97},
    {"Gray39", 99, 99, 99},
    {"Gray4", 10, 10, 10},
    {"Gray40", 102, 102, 102},
    {"Gray41", 105, 105, 105},
    {"Gray42", 107, 107, 107},
    {"Gray43", 110, 110, 110},
    {"Gray44", 112, 112, 112},
    {"Gray45", 115, 115, 115},
    {"Gray46", 117, 117, 117},
    {"Gray47", 120, 120, 120},
    {"Gray48", 122, 122, 122},
    {"Gray49", 125, 125, 125},
    {"Gray5", 13, 13, 13},
    {"Gray50", 127, 127, 127},
    {"Gray51", 130, 130, 130},
    {"Gray52", 133, 133, 133},
    {"Gray53", 135, 135, 135},
    {"Gray54", 138, 138, 138},
    {"Gray55", 140, 140, 140},
    {"Gray56", 143, 143, 143},
    {"Gray57", 145, 145, 145},
    {"Gray58", 148, 148, 148},
    {"Gray59", 150, 150, 150},
    {"Gray6", 15, 15, 15},
    {"Gray60", 153, 153, 153},
    {"Gray61", 156, 156, 156},
    {"Gray62", 158, 158, 158},
    {"Gray63", 161, 161, 161},
    {"Gray64", 163, 163, 163},
    {"Gray65", 166, 166, 166},
    {"Gray66", 168, 168, 168},
    {"Gray67", 171, 171, 171},
    {"Gray68", 173, 173, 173},
    {"Gray69", 176, 176, 176},
    {"Gray7", 18, 18, 18},
    {"Gray70", 179, 179, 179},
    {"Gray71", 181, 181, 181},
    {"Gray72", 184, 184, 184},
    {"Gray73", 186, 186, 186},
    {"Gray74", 189, 189, 189},
    {"Gray75", 191, 191, 191},
    {"Gray76", 194, 194, 194},
    {"Gray77", 196, 196, 196},
    {"Gray78", 199, 199, 199},
    {"Gray79", 201, 201, 201},
    {"Gray8", 20, 20, 20},
    {"Gray80", 204, 204, 204},
    {"Gray81", 207, 207, 207},
    {"Gray82", 209, 209, 209},
    {"Gray83", 212, 212, 212},
    {"Gray84", 214, 214, 214},
    {"Gray85", 217, 217, 217},
    {"Gray86", 219, 219, 219},
    {"Gray87", 222, 222, 222},
    {"Gray88", 224, 224, 224},
    {"Gray89", 227, 227, 227},
    {"Gray9", 23, 23, 23},
    {"Gray90", 229, 229, 229},
    {"Gray91", 232, 232, 232},
    {"Gray92", 235, 235, 235},
    {"Gray93", 237, 237, 237},
    {"Gray94", 240, 240, 240},
    {"Gray95", 242, 242, 242},
    {"Gray96", 245, 245, 245},
    {"Gray97", 247, 247, 247},
    {"Gray98", 250, 250, 250},
    {"Gray99", 252, 252, 252},
    {"Green", 0, 255, 0},
    {"GreenYellow", 173, 255, 47},
    {"honeydew", 240, 255, 240},
    {"HotPink", 255, 105, 180},
    {"IndianRed", 107, 57, 57},
    {"ivory", 255, 255, 240},
    {"Khaki", 179, 179, 126},
    {"lavender", 230, 230, 250},
    {"LavenderBlush", 255, 240, 245},
    {"LawnGreen", 124, 252, 0},
    {"LemonChiffon", 255, 250, 205},
    {"LightBlue", 176, 226, 255},
    {"LightCoral", 240, 128, 128},
    {"LightCyan", 224, 255, 255},
    {"LightGoldenrod", 238, 221, 130},
    {"LightGoldenrodYellow", 250, 250, 210},
    {"LightGray", 168, 168, 168},
    {"LightPink", 255, 182, 193},
    {"LightSalmon", 255, 160, 122},
    {"LightSeaGreen", 32, 178, 170},
    {"LightSkyBlue", 135, 206, 250},
    {"LightSlateBlue", 132, 112, 255},
    {"LightSlateGray", 119, 136, 153},
    {"LightSteelBlue", 124, 152, 211},
    {"LightYellow", 255, 255, 224},
    {"LimeGreen", 0, 175, 20},
    {"linen", 250, 240, 230},
    {"Magenta", 255, 0, 255},
    {"Maroon", 143, 0, 82},
    {"MediumAquamarine", 0, 147, 143},
    {"MediumBlue", 50, 50, 204},
    {"MediumForestGreen", 50, 129, 75},
    {"MediumGoldenrod", 209, 193, 102},
    {"MediumOrchid", 189, 82, 189},
    {"MediumPurple", 147, 112, 219},
    {"MediumSeaGreen", 52, 119, 102},
    {"MediumSlateBlue", 106, 106, 141},
    {"MediumSpringGreen", 35, 142, 35},
    {"MediumTurquoise", 0, 210, 210},
    {"MediumVioletRed", 213, 32, 121},
    {"MidnightBlue", 47, 47, 100},
    {"MintCream", 245, 255, 250},
    {"MistyRose", 255, 228, 225},
    {"moccasin", 255, 228, 181},
    {"NavajoWhite", 255, 222, 173},
    {"Navy", 35, 35, 117},
    {"NavyBlue", 35, 35, 117},
    {"OldLace", 253, 245, 230},
    {"OliveDrab", 107, 142, 35},
    {"Orange", 255, 135, 0},
    {"OrangeRed", 255, 69, 0},
    {"Orchid", 239, 132, 239},
    {"PaleGoldenrod", 238, 232, 170},
    {"PaleGreen", 115, 222, 120},
    {"PaleTurquoise", 175, 238, 238},
    {"PaleVioletRed", 219, 112, 147},
    {"PapayaWhip", 255, 239, 213},
    {"PeachPuff", 255, 218, 185},
    {"peru", 205, 133, 63},
    {"Pink", 255, 181, 197},
    {"Plum", 197, 72, 155},
    {"PowderBlue", 176, 224, 230},
    {"purple", 160, 32, 240},
    {"Red", 255, 0, 0},
    {"RosyBrown", 188, 143, 143},
    {"RoyalBlue", 65, 105, 225},
    {"SaddleBrown", 139, 69, 19},
    {"Salmon", 233, 150, 122},
    {"SandyBrown", 244, 164, 96},
    {"SeaGreen", 82, 149, 132},
    {"seashell", 255, 245, 238},
    {"Sienna", 150, 82, 45},
    {"SkyBlue", 114, 159, 255},
    {"SlateBlue", 126, 136, 171},
    {"SlateGray", 112, 128, 144},
    {"snow", 255, 250, 250},
    {"SpringGreen", 65, 172, 65},
    {"SteelBlue", 84, 112, 170},
    {"Tan", 222, 184, 135},
    {"Thistle", 216, 191, 216},
    {"tomato", 255, 99, 71},
    {"Transparent", 0, 0, 1},
    {"Turquoise", 25, 204, 223},
    {"Violet", 156, 62, 206},
    {"VioletRed", 243, 62, 150},
    {"Wheat", 245, 222, 179},
    {"White", 255, 255, 255},
    {"WhiteSmoke", 245, 245, 245},
    {"Yellow", 255, 255, 0},
    {"YellowGreen", 50, 216, 56}
};
/* Hash table to look up colors from pixel strings */
#define STARTING_HASH_SIZE 256

struct hash_entry
{
    char key[10];
    rtgui_color_t color;
    struct hash_entry *next;
};

struct color_hash
{
    struct hash_entry **table;
    struct hash_entry *entries; /* array of all entries */
    struct hash_entry *next_free;

    int size;
    int maxnum;
};

static int hash_key(const char *key, int cpp, int size)
{
    int hash;

    hash = 0;
    while (cpp-- > 0)
    {
        hash = hash * 33 + *key++;
    }
    return hash & (size - 1);
}

static struct color_hash *create_colorhash(int maxnum)
{
    int bytes, s;
    struct color_hash *hash;

    /* we know how many entries we need, so we can allocate
       everything here */
    hash = rtgui_malloc(sizeof *hash);
    if (!hash) return RT_NULL;

    /* use power-of-2 sized hash table for decoding speed */
    for (s = STARTING_HASH_SIZE; s < maxnum; s <<= 1) ;
    hash->size = s;
    hash->maxnum = maxnum;
    bytes = hash->size *sizeof(struct hash_entry **);
    hash->entries = RT_NULL;    /* in case rt_malloc fails */
    hash->table = rtgui_malloc(bytes);
    if (!hash->table) return RT_NULL;

    rt_memset(hash->table, 0, bytes);
    hash->entries = rtgui_malloc(maxnum *sizeof(struct hash_entry));
    if (!hash->entries) return RT_NULL;

    hash->next_free = hash->entries;
    return hash;
}

static int add_colorhash(struct color_hash *hash,
                         char *key, int cpp, rtgui_color_t *color)
{
    int index = hash_key(key, cpp, hash->size);
    struct hash_entry *e = hash->next_free++;

    e->color = *color;
    rt_memset(e->key, 0, sizeof(e->key));
    rt_strncpy(e->key, key, cpp);
    e->next = hash->table[index];
    hash->table[index] = e;

    return 1;
}

static void get_colorhash(struct color_hash *hash, const char *key, int cpp, rtgui_color_t *c)
{
    struct hash_entry *entry = hash->table[hash_key(key, cpp, hash->size)];
    while (entry)
    {
        if (rt_memcmp(key, entry->key, cpp) == 0)
        {
            *c = entry->color;

            return;
        }

        entry = entry->next;
    }

    return ;        /* garbage in - garbage out */
}

static void free_colorhash(struct color_hash *hash)
{
    if (hash && hash->table)
    {
        rtgui_free(hash->table);
        rtgui_free(hash->entries);
        rtgui_free(hash);
    }
}

#if defined(_MSC_VER) || defined(__CC_ARM)
int strcasecmp(const char *s1, const char *s2)
{
    register unsigned int  x2;
    register unsigned int  x1;

    while (1)
    {
        x2 = *s2 - 'A';
        if (x2 < 26u) x2 += 32;
        x1 = *s1 - 'A';
        if (x1 < 26u) x1 += 32;
        s1++;
        s2++;
        if (x2 != x1)
            break;
        if (x1 == (unsigned int) - 'A')
            break;
    }

    return x1 - x2;
}
#endif

static int hex2int(const char *str)
{
    int i = 0;
    int r = 0;

    for (i = 0; i < 2; i++)
    {
        if (str[i] >= '0' && str[i] <= '9') r += str[i] - '0';
        else if (str[i] >= 'a' && str[i] <= 'f') r += str[i] - 'a' + 10;
        else if (str[i] >= 'A' && str[i] <= 'F') r += str[i] - 'A' + 10;

        if (!i) r *= 16;
    }

    return r;
}

void rtgui_image_xpm_init()
{
    /* register xpm engine */
    rtgui_image_register_engine(&rtgui_image_xpm_engine);
}

static rt_bool_t rtgui_image_xpm_check(struct rtgui_filerw *file)
{
#if 0
    rt_uint8_t buffer[XPM_MAGIC_LEN];
    rt_size_t start;
    rt_bool_t result;

    result = RT_FALSE;

    start = rtgui_filerw_tell(file);

    /* seek to the begining of file */
    if (start != 0) rtgui_filerw_seek(file, 0, SEEK_SET);
    rtgui_filerw_read(file, &buffer[0], XPM_MAGIC_LEN, 1);

    if (rt_memcmp(buffer, "/* XPM */", (rt_ubase_t)XPM_MAGIC_LEN) == 0)
        result = RT_TRUE;

    rtgui_filerw_seek(file, start, SEEK_SET);

    return result;
#else
    /* we can not check image type for memory file */
    return RT_TRUE;
#endif
}

static int _str2int(const char *str, int strlen, int *p)
{
    int i;

    *p = 0;
    /* Skip the leading chars. */
    for (i = 0; i < strlen; i++)
    {
        if ('0' <= str[i] && str[i] <= '9')
            break;
    }

    for (; i < strlen; i++)
    {
        if (str[i] < '0' || '9' < str[i])
            break;
        *p = (*p) * 10 + str[i] - '0';
    }
    return i;
}

static rt_bool_t rtgui_image_xpm_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load)
{
    const char **xpm;
    const char *buf;
    const char *buf_tmp;

    int w, h;
    int colors = 0;
    int colors_pp = 0;

    int i, j;

    /* color hash table */
    struct color_hash *colors_table = RT_NULL;

    if (image == RT_NULL) return RT_FALSE;

    xpm = (const char **)rtgui_filerw_mem_getdata(file);
    if (xpm == RT_NULL) return RT_FALSE;

    /* set image engine */
    image->engine = &rtgui_image_xpm_engine;

    /* parse xpm image */
    i = rt_strlen(xpm[0]);
    /* Add one for the space. */
    j = _str2int(xpm[0], i, &w) + 1;
    j += _str2int(xpm[0] + j, i - j, &h) + 1;
    j += _str2int(xpm[0] + j, i - j, &colors) + 1;
    j += _str2int(xpm[0] + j, i - j, &colors_pp) + 1;
    image->w = w;
    image->h = h;

    /* build color table */
    colors_table = create_colorhash(colors);
    if (!colors_table)
    {
        return RT_FALSE;
    }

    for (i = 0; i < colors; i++)
    {
        char color_name[10];
        rtgui_color_t c = 0;

        buf = xpm[i + 1];

        for (j = 0; j < colors_pp; j++)
        {
            color_name[j] = buf[j];
        }
        color_name[j] = '\0';

        /* build rtgui_color */
        if ((buf_tmp = strstr(buf, "c #")) != RT_NULL)
        {
            c = RTGUI_ARGB(0, hex2int(buf_tmp + 3),
                           hex2int(buf_tmp + 5),
                           hex2int(buf_tmp + 7));
        }
        else if ((buf_tmp = strstr(buf, "c ")) != RT_NULL)
        {
            int k;

            if (strcasecmp(buf_tmp + 2, "None") == 0)
            {
                goto color_none;
            }

            for (k = 0; k < 234; k++)
            {
                if (strcasecmp(buf_tmp + 2, rgbRecord[k].name) == 0)
                {
                    c = RTGUI_ARGB(0, rgbRecord[k].r,
                                   rgbRecord[k].g,
                                   rgbRecord[k].b);
                    break;
                }
            }
        }
        else
        {
color_none:
            c = RTGUI_RGB(0, 0, 0);
        }

        /* add to color hash table */
        add_colorhash(colors_table, color_name, colors_pp, &c);
    }

    /* build rgb pixel data */
    image->data = (rt_uint8_t *) rtgui_malloc(image->w * image->h * sizeof(rtgui_color_t));
    memset(image->data, 0, image->w * image->h * sizeof(rtgui_color_t));

    {
        rtgui_color_t *ptr = (rtgui_color_t *) image->data;

        for (h = 0; h < image->h; h++)
        {
            buf = xpm[colors + 1 + h];
            for (w = 0; w < image->w; w++, buf += colors_pp)
            {
                get_colorhash(colors_table, buf, colors_pp, ptr);

                ptr ++;
            }
        }
    }

    free_colorhash(colors_table);
    rtgui_filerw_close(file);

    return RT_TRUE;
}

static void rtgui_image_xpm_unload(struct rtgui_image *image)
{
    if (image != RT_NULL)
    {
        /* release data */
        rtgui_free(image->data);
        image->data = RT_NULL;
    }
}

static void rtgui_image_xpm_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect)
{
    rt_uint16_t x, y;
    rtgui_color_t *ptr;

    RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);
    RT_ASSERT(image->data != RT_NULL);

    ptr = (rtgui_color_t *) image->data;

    /* draw each point within dc */
    for (y = 0; y < image->h; y ++)
    {
        for (x = 0; x < image->w; x++)
        {
            /* not alpha */
            if ((*ptr >> 24) != 255)
            {
                rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1, *ptr);
            }

            /* move to next color buffer */
            ptr ++;
        }
    }
}
#endif
