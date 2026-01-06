/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <dt-bindings/input/event-codes.h>

#define DBG_TAG "serial.virtual"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "render.h"

struct virtual_serial
{
    struct rt_serial_device parent;

    struct rt_device *fbdev;
    struct rt_thread *render_task;

    struct rt_device *idev;
    struct rt_input_handler input_handler;

    int param;
    rt_bool_t input_int;
    struct render_point start, end;

    struct rt_spinlock lock;

    rt_uint8_t in[RT_CONSOLEBUF_SIZE];
    rt_uint16_t in_head, in_tail;
    rt_bool_t shift, ctrl, alt, caps;
    rt_bool_t is_escape, is_bracket;
    rt_bool_t in_pending;

    rt_uint8_t out[RT_CONSOLEBUF_SIZE];
    rt_uint16_t out_head, out_tail;
    rt_bool_t out_pending;
};

#define raw_to_virtual_serial(raw)  rt_container_of(raw, struct virtual_serial, parent)

static rt_uint8_t virtual_font[] =
{
#include "psf.inc"
};

enum
{
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_LIGHT_GRAY,
    COLOR_DARK_GRAY,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_YELLOW,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_MAGENTA,
    COLOR_LIGHT_CYAN,
    COLOR_WHITE,
};

static struct render_color font_colors[] =
{                             /*  R    G    B    A */
    [COLOR_BLACK]           = {   0,   0,   0, 255 },
    [COLOR_RED]             = { 205,   0,   0, 255 },
    [COLOR_GREEN]           = {   0, 205,   0, 255 },
    [COLOR_YELLOW]          = { 205, 205,   0, 255 },
    [COLOR_BLUE]            = {   0,   0, 238, 255 },
    [COLOR_MAGENTA]         = { 205,   0, 205, 255 },
    [COLOR_CYAN]            = {   0, 205, 205, 255 },
    [COLOR_LIGHT_GRAY]      = { 229, 229, 229, 255 },
    [COLOR_DARK_GRAY]       = { 127, 127, 127, 255 },
    [COLOR_LIGHT_RED]       = { 255,   0,   0, 255 },
    [COLOR_LIGHT_GREEN]     = {   0, 255,   0, 255 },
    [COLOR_LIGHT_YELLOW]    = { 255, 255,   0, 255 },
    [COLOR_LIGHT_BLUE]      = {  92,  92, 255, 255 },
    [COLOR_LIGHT_MAGENTA]   = { 255,   0, 255, 255 },
    [COLOR_LIGHT_CYAN]      = {   0, 255, 255, 255 },
    [COLOR_WHITE]           = { 255, 255, 255, 255 },
};

static const rt_uint8_t unix_color_map[] =
{
    /* \033[Xm */
    [0]  = COLOR_WHITE,
    [30] = COLOR_BLACK,
    [31] = COLOR_RED,
    [32] = COLOR_GREEN,
    [33] = COLOR_YELLOW,
    [34] = COLOR_BLUE,
    [35] = COLOR_MAGENTA,
    [36] = COLOR_CYAN,
    [37] = COLOR_LIGHT_GRAY,
    [90] = COLOR_DARK_GRAY,
    [91] = COLOR_LIGHT_RED,
    [92] = COLOR_LIGHT_GREEN,
    [93] = COLOR_LIGHT_YELLOW,
    [94] = COLOR_LIGHT_BLUE,
    [95] = COLOR_LIGHT_MAGENTA,
    [96] = COLOR_LIGHT_CYAN,
    [97] = COLOR_WHITE,
};


static char key_map[] =
{
    [KEY_1] = '1',
    [KEY_2] = '2',
    [KEY_3] = '3',
    [KEY_4] = '4',
    [KEY_5] = '5',
    [KEY_6] = '6',
    [KEY_7] = '7',
    [KEY_8] = '8',
    [KEY_9] = '9',
    [KEY_0] = '0',
    [KEY_MINUS] = '-',
    [KEY_EQUAL] = '=',
    [KEY_Q] = 'q',
    [KEY_W] = 'w',
    [KEY_E] = 'e',
    [KEY_R] = 'r',
    [KEY_T] = 't',
    [KEY_Y] = 'y',
    [KEY_U] = 'u',
    [KEY_I] = 'i',
    [KEY_O] = 'o',
    [KEY_P] = 'p',
    [KEY_LEFTBRACE] = '[',
    [KEY_RIGHTBRACE] = ']',
    [KEY_A] = 'a',
    [KEY_S] = 's',
    [KEY_D] = 'd',
    [KEY_F] = 'f',
    [KEY_G] = 'g',
    [KEY_H] = 'h',
    [KEY_J] = 'j',
    [KEY_K] = 'k',
    [KEY_L] = 'l',
    [KEY_SEMICOLON] = ';',
    [KEY_APOSTROPHE] = '\'',
    [KEY_BACKSLASH] = '\\',
    [KEY_Z] = 'z',
    [KEY_X] = 'x',
    [KEY_C] = 'c',
    [KEY_V] = 'v',
    [KEY_B] = 'b',
    [KEY_N] = 'n',
    [KEY_M] = 'm',
    [KEY_COMMA] = ',',
    [KEY_DOT] = '.',
    [KEY_SLASH] = '/',
    [KEY_SPACE] = ' ',
};

static char key_shift_map[] =
{
    [KEY_1] = '!',
    [KEY_2] = '@',
    [KEY_3] = '#',
    [KEY_4] = '$',
    [KEY_5] = '%',
    [KEY_6] = '^',
    [KEY_7] = '&',
    [KEY_8] = '*',
    [KEY_9] = '(',
    [KEY_0] = ')',
    [KEY_MINUS] = '_',
    [KEY_EQUAL] = '+',
    [KEY_Q] = 'Q',
    [KEY_W] = 'W',
    [KEY_E] = 'E',
    [KEY_R] = 'R',
    [KEY_T] = 'T',
    [KEY_Y] = 'Y',
    [KEY_U] = 'U',
    [KEY_I] = 'I',
    [KEY_O] = 'O',
    [KEY_P] = 'P',
    [KEY_LEFTBRACE] = '{',
    [KEY_RIGHTBRACE] = '}',
    [KEY_A] = 'A',
    [KEY_S] = 'S',
    [KEY_D] = 'D',
    [KEY_F] = 'F',
    [KEY_G] = 'G',
    [KEY_H] = 'H',
    [KEY_J] = 'J',
    [KEY_K] = 'K',
    [KEY_L] = 'L',
    [KEY_SEMICOLON] = ':',
    [KEY_APOSTROPHE] = '\"',
    [KEY_BACKSLASH] = '|',
    [KEY_Z] = 'Z',
    [KEY_X] = 'X',
    [KEY_C] = 'C',
    [KEY_V] = 'V',
    [KEY_B] = 'B',
    [KEY_N] = 'N',
    [KEY_M] = 'M',
    [KEY_COMMA] = '<',
    [KEY_DOT] = '>',
    [KEY_SLASH] = '?',
    [KEY_SPACE] = ' ',
};

static enum cursor cursor_shape = CURSOR_BLOCK;

static struct virtual_serial _vs = {};

static void push_out_char(struct virtual_serial *vs, char c);
static void virtual_serial_render_char(struct virtual_serial *vs, char ch);
static int pop_in_char(struct virtual_serial *vs);

static rt_err_t virtual_serial_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t virtual_serial_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct virtual_serial *vs = raw_to_virtual_serial(serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
    case RT_DEVICE_CTRL_CLR_INT:
        vs->input_int = RT_FALSE;
        break;

    case RT_DEVICE_CTRL_RESUME:
    case RT_DEVICE_CTRL_SET_INT:
        vs->input_int = RT_TRUE;
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static int virtual_serial_putc(struct rt_serial_device *serial, char c)
{
    struct virtual_serial *vs = raw_to_virtual_serial(serial);

    rt_spin_lock(&vs->lock);

    if (!rt_critical_level())
    {
        virtual_serial_render_char(vs, c);
    }
    else
    {
        push_out_char(vs, c);
        rt_thread_resume(vs->render_task);
    }

    rt_spin_unlock(&vs->lock);

    return 1;
}

static int virtual_serial_getc(struct rt_serial_device *serial)
{
    struct virtual_serial *vs = raw_to_virtual_serial(serial);

    return pop_in_char(vs);
}

static const struct rt_uart_ops virtual_serial_ops =
{
    .configure = virtual_serial_configure,
    .control = virtual_serial_control,
    .putc = virtual_serial_putc,
    .getc = virtual_serial_getc,
};

static rt_bool_t parse_ctrl(struct virtual_serial *vs, char c)
{
    if (vs->is_bracket && c == 'm')
    {
        render_set_foreground(&font_colors[unix_color_map[vs->param]]);

        return RT_TRUE;
    }

    if (c == 'J' && vs->param == 2)
    {
        render_clear_display();

        return RT_TRUE;
    }

    if (c == 'K' && vs->param == 2)
    {
        rt_uint32_t old_col;
        struct render_point point;

        render_current_cursor(&point);
        old_col = point.col;

        for (int i = vs->start.col; i < old_col; ++i)
        {
            --point.col;
            render_move_cursor(&point);
            render_put_char(' ');
        }

        point.col = old_col;
        render_move_cursor(&point);

        return RT_TRUE;
    }

    if (c == 'H')
    {
        render_move_cursor(&vs->start);

        return RT_TRUE;
    }

    return RT_FALSE;
}

static void push_out_char(struct virtual_serial *vs, char c)
{
    rt_uint16_t next = (vs->out_head + 1) % sizeof(vs->out);

    if (next == vs->out_tail)
    {
        /* Full */
        return;
    }

    vs->out[vs->out_head] = c;
    vs->out_head = next;
    vs->out_pending = RT_TRUE;
}

static int pop_out_char(struct virtual_serial *vs)
{
    int c;

    if (vs->out_head == vs->out_tail)
    {
        return -1;
    }

    c = vs->out[vs->out_tail];
    vs->out_tail = (vs->out_tail + 1) % sizeof(vs->out);

    return c;
}

static void push_in_char(struct virtual_serial *vs, char c)
{
    rt_uint16_t next = (vs->in_head + 1) % sizeof(vs->in);

    if (next == vs->in_tail)
    {
        /* Full, drop */
        return;
    }

    vs->in[vs->in_head] = (rt_uint8_t)c;
    vs->in_head = next;
    vs->in_pending = RT_TRUE;
}

static int pop_in_char(struct virtual_serial *vs)
{
    int ch;

    if (vs->in_head == vs->in_tail)
    {
        return -1;
    }

    ch = vs->in[vs->in_tail];
    vs->in_tail = (vs->in_tail + 1) % sizeof(vs->in);

    return ch;
}

static char key_to_char(struct virtual_serial *vs, int code)
{
    char base, shiftc;

    base = key_map[code];
    shiftc = key_shift_map[code];

    if (!base && !shiftc)
    {
        return 0;
    }

    if (code >= KEY_A && code <= KEY_Z)
    {
        rt_bool_t upper = (vs->shift ^ vs->caps);

        return upper ? (shiftc ? shiftc : base - 'a' + 'A')
                     : (base   ? base   : shiftc + 'a' - 'A');
    }

    if (vs->shift && shiftc)
    {
        return shiftc;
    }

    return base;
}

static void virtual_serial_render_char(struct virtual_serial *vs, char ch)
{
    if (vs->is_escape)
    {
        if (ch == '[')
        {
            vs->param = 0;
            vs->is_bracket = RT_TRUE;
            return;
        }
        else if (vs->is_bracket && (ch >= '0' && ch <= '9'))
        {
            vs->param = vs->param * 10 + (ch - '0');
            return;
        }
        else
        {
            if (!parse_ctrl(vs, ch))
            {
                goto _render_char;
            }

            vs->is_bracket = RT_FALSE;
            vs->is_escape = RT_FALSE;
            return;
        }
    }

_render_char:
    if (ch >= ' ')
    {
        render_put_char(ch);
    }
    else
    {
        struct render_point point;

        switch (ch)
        {
        case '\n':
            render_return_cursor(RT_NULL);
            break;

        case '\033':
            vs->is_escape = RT_TRUE;
            break;

        case '\t':
            render_current_cursor(&point);
            point.col = (point.col / 4 + 1) * 4;
            if (point.col > vs->end.col)
            {
                point.col -= vs->end.col;
                point.row++;
            }
            render_move_cursor(&point);
            break;

        case '\r':
            render_reset_cursor(RT_NULL);
            break;

        case '\b':
            render_current_cursor(&point);
            if (point.col > 0)
            {
                point.col--;
                render_move_cursor(&point);
            }
            break;

        default:
            break;
        }
    }
}

static void virtual_serial_render_task(void *param)
{
    struct virtual_serial *vs = param;

    while (RT_TRUE)
    {
        rt_spin_lock(&vs->lock);

        if (vs->out_head == vs->out_tail)
        {
            rt_spin_unlock(&vs->lock);
            rt_thread_suspend(rt_thread_self());
            rt_schedule();

            continue;
        }

        virtual_serial_render_char(vs, pop_out_char(vs));

        rt_spin_unlock(&vs->lock);
    }
}

static rt_bool_t virtual_serial_input_test_cap(struct rt_input_handler *handler,
        struct rt_input_device *idev)
{
    return rt_bitmap_test_bit(idev->key_map, KEY_ENTER);
}

static rt_bool_t virtual_serial_input_callback(struct rt_input_handler *handler,
        struct rt_input_event *ev)
{
    char ch;
    struct virtual_serial *vs = handler->priv;

    if (ev->type == EV_KEY)
    {
        if (!vs->input_int)
        {
            return RT_TRUE;
        }

        if (ev->value == 0)
        {
            switch (ev->code)
            {
            case KEY_LEFTSHIFT:
            case KEY_RIGHTSHIFT:
                vs->shift = RT_FALSE;
                break;

            case KEY_LEFTCTRL:
            case KEY_RIGHTCTRL:
                vs->ctrl = RT_FALSE;
                break;

            case KEY_LEFTALT:
            case KEY_RIGHTALT:
                vs->alt = RT_FALSE;
                break;

            default:
                break;
            }

            return RT_TRUE;
        }

        if (ev->value != 1)
        {
            return RT_TRUE;
        }

        switch (ev->code)
        {
        case KEY_LEFTSHIFT:
        case KEY_RIGHTSHIFT:
            vs->shift = RT_TRUE;
            break;

        case KEY_LEFTCTRL:
        case KEY_RIGHTCTRL:
            vs->ctrl = RT_TRUE;
            break;

        case KEY_LEFTALT:
        case KEY_RIGHTALT:
            vs->alt = RT_TRUE;
            break;

        case KEY_CAPSLOCK:
            vs->caps = !vs->caps;
            break;

        case KEY_ENTER:
        case KEY_KPENTER:
            push_in_char(vs, '\r');
            break;

        case KEY_BACKSPACE:
            push_in_char(vs, '\b');
            break;

        case KEY_TAB:
            push_in_char(vs, '\t');
            break;

        case KEY_UP:
            push_in_char(vs, 0x1b);
            push_in_char(vs, '[');
            push_in_char(vs, 'A');
            break;

        case KEY_DOWN:
            push_in_char(vs, 0x1b);
            push_in_char(vs, '[');
            push_in_char(vs, 'B');
            break;

        case KEY_LEFT:
            push_in_char(vs, 0x1b);
            push_in_char(vs, '[');
            push_in_char(vs, 'D');
            break;

        case KEY_RIGHT:
            push_in_char(vs, 0x1b);
            push_in_char(vs, '[');
            push_in_char(vs, 'C');
            break;

        default:
            if ((ch = key_to_char(vs, ev->code)))
            {
                push_in_char(vs, ch);
            }
            break;
        }

        return RT_TRUE;
    }
    else if (ev->type == EV_SYN)
    {
        if (vs->input_int && vs->in_pending)
        {
            vs->in_pending = RT_FALSE;
            rt_hw_serial_isr(&vs->parent, RT_SERIAL_EVENT_RX_IND);
        }

        return RT_TRUE;
    }

    return RT_FALSE;
}

static int virtual_serial_setup(void)
{
    rt_err_t err;

    for (int id = 0; id < RT_DM_IDA_NUM; ++id)
    {
        if ((_vs.fbdev = rt_dm_device_find(MASTER_ID_GRAPHIC_FRAMEBUFFER, id)))
        {
            break;
        }
    }

    if (!_vs.fbdev)
    {
        return (int)-RT_ENOSYS;
    }

    _vs.input_handler.idev = RT_NULL;
    _vs.input_handler.identify = &virtual_serial_input_test_cap;
    _vs.input_handler.callback = &virtual_serial_input_callback;
    _vs.input_handler.priv = &_vs;

    if ((err = rt_input_add_handler(&_vs.input_handler)))
    {
        return (int)err;
    }

    if (!(_vs.render_task = rt_thread_create("vuart", virtual_serial_render_task, &_vs,
            DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 32)))
    {
        goto _fail;
    }

    if ((err = render_load_fbdev(_vs.fbdev)))
    {
        LOG_E("Load fbdev error = %s", rt_strerror(err));

        goto _fail;
    }

    if ((err = render_load_font((void *)virtual_font, sizeof(virtual_font),
            &font_colors[COLOR_WHITE], &font_colors[COLOR_BLACK],
            &_vs.start, &_vs.end)))
    {
        LOG_E("Load PSF font error = %s", rt_strerror(err));

        goto _fail;
    }

    render_select_cursor(cursor_shape);

    rt_device_open(_vs.fbdev, 0);
    rt_spin_lock_init(&_vs.lock);

    rt_thread_startup(_vs.render_task);

    _vs.input_int = RT_TRUE;
    _vs.parent.ops = &virtual_serial_ops;
    _vs.parent.config = (struct serial_configure)RT_SERIAL_CONFIG_DEFAULT;
    rt_hw_serial_register(&_vs.parent, "vuart", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &_vs);

    return 0;

_fail:
    rt_input_del_handler(&_vs.input_handler);

    return (int)err;
}
INIT_EXPORT(virtual_serial_setup, "3.end");

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
static int virtual_serial_cmd_color(int argc, char**argv)
{
    const char *color;
    static const char * const color_names[] =
    {
        [COLOR_BLACK]           = "black",
        [COLOR_RED]             = "red",
        [COLOR_GREEN]           = "green",
        [COLOR_YELLOW]          = "yellow",
        [COLOR_BLUE]            = "blue",
        [COLOR_MAGENTA]         = "magenta",
        [COLOR_CYAN]            = "cyan",
        [COLOR_LIGHT_GRAY]      = "light gray",
        [COLOR_DARK_GRAY]       = "dark gray",
        [COLOR_LIGHT_RED]       = "light red",
        [COLOR_LIGHT_GREEN]     = "light green",
        [COLOR_LIGHT_YELLOW]    = "light yellow",
        [COLOR_LIGHT_BLUE]      = "light blue",
        [COLOR_LIGHT_MAGENTA]   = "light magenta",
        [COLOR_LIGHT_CYAN]      = "light cyan",
        [COLOR_WHITE]           = "white",
    };

    if (argc != 2)
    {
        goto _help;
    }

    color = argv[1];

    if (!((color[0] >= '0' && color[0] <= '9') || (color[0] >= 'a' && color[0] <= 'f')) ||
        !((color[1] >= '0' && color[1] <= '9') || (color[1] >= 'a' && color[1] <= 'f')))
    {
        goto _help;
    }

    if (color[0] == color[1])
    {
        rt_kprintf("foreground cannot equal background\n");

        return (int)-RT_EINVAL;
    }

    render_set_foreground(&font_colors[color[0] - (color[0] >= 'a' ? ('a' - 10) : '0')]);
    render_set_background(&font_colors[color[1] - (color[1] >= 'a' ? ('a' - 10) : '0')]);

    return 0;

_help:
    rt_kprintf("Usage: color [attr]\nattr:\n");

    for (int i = 0; i < RT_ARRAY_SIZE(font_colors); ++i)
    {
        rt_kprintf("\t%x = %s\n", i, color_names[i]);
    }

    return (int)-RT_EINVAL;
}
MSH_CMD_EXPORT_ALIAS(virtual_serial_cmd_color, color, set virtual serial foreground and background);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */
