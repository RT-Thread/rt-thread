#include <string.h>
#include <rtthread.h>

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/button.h>

#include "snake.h"

#define LATTICE_SIZE        (20)
#define FOOD_MAX            (8)

#define WALL_COLOR          RTGUI_RGB(255, 0, 0)
#define SNAKE_COLOR         RTGUI_RGB(0, 100, 200)
#define SNAKE_HEAD_COLOR    RTGUI_RGB(180, 70, 130)
#define BACKGROUND_COLOR    RTGUI_RGB(153, 153, 0)
#define FOOD_COLOR          RTGUI_RGB(128, 0, 0)

static rtgui_timer_t *timer;
static rt_size_t room_size_x, room_size_y;
static rt_size_t lattice_size_x, lattice_size_y;
static struct rtgui_rect room_rect, lattice_rect;

map_t      *map;
SNAKE_DIR   run_state;
rt_int32_t  snake_len;
rt_int32_t  food_num;
point_t     second_node;

static void snake_fill_lattice(struct rtgui_dc *dc,
                               rt_uint32_t x,
                               rt_uint32_t y,
                               rtgui_color_t color)
{
    struct rtgui_rect rect;

    // coordinate  conversion
    y = (lattice_size_y - 1) - y;

    RTGUI_DC_BC(dc) = color;

    rect.x1 = lattice_rect.x1 + (LATTICE_SIZE * x);
    rect.x2 = rect.x1 + LATTICE_SIZE;
    rect.x1 += 2;

    rect.y1 = lattice_rect.y1 + (LATTICE_SIZE * y);
    rect.y2 = rect.y1 + LATTICE_SIZE;
    rect.y1 += 2;

    rtgui_dc_fill_rect(dc, &rect);
}

static void snake_draw(struct rtgui_widget *widget)
{
    struct rtgui_dc *dc;
    struct rtgui_rect rect;
    rt_uint32_t i;

    dc = rtgui_dc_begin_drawing(widget);
    if (dc == RT_NULL)
    {
        rt_kprintf("dc == RT_NULL\r\n");
        return;
    }

    /* get room size, run once frist. */
    if ((room_size_x == 0) || (room_size_y == 0))
    {
        rt_size_t tmp;

        rtgui_widget_get_rect(widget, &rect);
        rt_kprintf("rect => x1:%d x2:%d, y1:%d y2:%d\r\n", rect.x1, rect.x2, rect.y1, rect.y2);

        room_size_x = rect.x2 - rect.x1;
        room_size_y = rect.y2 - rect.y1;
        memcpy(&room_rect, &rect, sizeof(struct rtgui_rect));
        rt_kprintf("room_rect => x1:%d x2:%d, y1:%d y2:%d\r\n",
                   room_rect.x1, room_rect.x2,
                   room_rect.y1, room_rect.y2);

        lattice_size_x = (room_rect.x2 - room_rect.x1) / LATTICE_SIZE;
        lattice_size_y = (room_rect.y2 - room_rect.y1) / LATTICE_SIZE;
        lattice_size_x -= 2;
        lattice_size_y -= 2;
        rt_kprintf("lattice_size_x:%d lattice_size_y:%d\r\n",
                   lattice_size_x,
                   lattice_size_y);

        tmp = (room_rect.x2 - room_rect.x1) - (LATTICE_SIZE * lattice_size_x);
        lattice_rect.x1 = room_rect.x1 + (tmp / 2);
        lattice_rect.x2 = lattice_rect.x1 + (LATTICE_SIZE * lattice_size_x);

        tmp = (room_rect.y2 - room_rect.y1) - (LATTICE_SIZE * lattice_size_y);
        lattice_rect.y1 = room_rect.y1 + (tmp / 2);
        lattice_rect.y2 = lattice_rect.y1 + (LATTICE_SIZE * lattice_size_y);
        rt_kprintf("lattice_rect => x1:%d x2:%d, y1:%d y2:%d\r\n",
                   lattice_rect.x1, lattice_rect.x2,
                   lattice_rect.y1, lattice_rect.y2);

        /* create snake. */
        {
            point_t start;
            map = map_init(lattice_size_x, lattice_size_y);
            if (map != RT_NULL)
            {
                start.x = snake_init_pointx;
                start.y = snake_init_pointy;
                run_state = SNAKE_DIR_DOWN;

                if (snake_init(&start, snake_length_init, run_state, map))
                {
                    food_num = 1;
                    food_init(map, food_num);
                }
                else
                {
                    map_deinit(map);
                    map = RT_NULL;
                }
            }
        }
    }

    RTGUI_DC_BC(dc) = BACKGROUND_COLOR;
    rtgui_dc_fill_rect(dc, &room_rect);

    memcpy(&rect, &lattice_rect, sizeof(struct rtgui_rect));
    rect.x2 += 1;
    rect.y2 += 1;
    RTGUI_DC_FC(dc) = WALL_COLOR;
    rtgui_dc_draw_rect(dc, &rect);

    for (i = 1; i < lattice_size_y; i++)
    {
        memcpy(&rect, &lattice_rect, sizeof(struct rtgui_rect));
        rect.x1 += 1;
        rect.x2 -= 1;
        rtgui_dc_draw_horizontal_line(dc, rect.x1, rect.x2,
                                      rect.y1 + (LATTICE_SIZE * i));
    }

    for (i = 1; i < lattice_size_x; i++)
    {
        memcpy(&rect, &lattice_rect, sizeof(struct rtgui_rect));
        rect.y1 += 1;
        rect.y2 -= 1;
        rtgui_dc_draw_vertical_line(dc, rect.x1 + (LATTICE_SIZE * i),
                                    rect.y1, rect.y2);
    }

    /* draw snake. */
    {
        rt_int32_t x, y;
        rt_bool_t first_node = RT_TRUE;

        for (y = 0; y < map->height; y++)
        {
            for (x = 0; x < map->width; x++)
            {
                switch (map->range[y * map->width + x])
                {
                case NORMAL:
                    break;
                case FOOD:
                    snake_fill_lattice(dc, x, y, FOOD_COLOR);
                    break;
                case OVER:
                    if (first_node)
                    {
                        first_node = RT_FALSE;
                        second_node.x = x;
                        second_node.y = y;
                        snake_fill_lattice(dc, x, y, SNAKE_HEAD_COLOR);
                    }
                    else
                    {
                        snake_fill_lattice(dc, x, y, SNAKE_COLOR);
                    }
                    break;
                }
            }

        }
    }

    rtgui_dc_end_drawing(dc);

    return;
}

static void snake_update(struct rtgui_widget *widget)
{
    struct rtgui_dc *dc;
    rt_int32_t x, y;
    rt_uint32_t i;

    dc = rtgui_dc_begin_drawing(widget);
    if (dc == RT_NULL)
    {
        rt_kprintf("dc == RT_NULL\r\n");
        return;
    }

    snake_fill_lattice(dc, second_node.x, second_node.y, SNAKE_COLOR);
    second_node = map->snake_flush[0];

    for (i = 0; i < 3; i++)
    {
        if (i < 2)
        {
            x = map->snake_flush[i].x;
            y = map->snake_flush[i].y;
        }
        else
        {
            x = map->food_flush[0].x;
            y = map->food_flush[0].y;
        }

        if ((x >= 0) && (y >= 0))
        {
            switch (map->range[(map->width * y) + x])
            {
            case NORMAL:
                snake_fill_lattice(dc, x, y, BACKGROUND_COLOR);
                break;
            case FOOD:
                snake_fill_lattice(dc, x, y, FOOD_COLOR);
                break;
            case OVER:
                if (0 == i)
                    snake_fill_lattice(dc, x, y, SNAKE_HEAD_COLOR);
                else
                    snake_fill_lattice(dc, x, y, SNAKE_COLOR);
                break;
            }
        }
    }

    rtgui_dc_end_drawing(dc);
    return;
}

static void snake_handler(struct rtgui_widget *widget, rtgui_event_t *event)
{
    struct rtgui_event_kbd *ekbd;

    ekbd = (struct rtgui_event_kbd *) event;
    if (ekbd->type == RTGUI_KEYDOWN)
    {
        switch (ekbd->key)
        {
        case RTGUIK_UP:
            rt_kprintf("RTGUIK_UP\r\n");
            run_state = SNAKE_DIR_UP;
            break;
        case RTGUIK_DOWN:
            rt_kprintf("RTGUIK_DOWN\r\n");
            run_state = SNAKE_DIR_DOWN;
            break;
        case RTGUIK_LEFT:
            rt_kprintf("RTGUIK_LEFT\r\n");
            run_state = SNAKE_DIR_LEFT;
            break;
        case RTGUIK_RIGHT:
            rt_kprintf("RTGUIK_RIGHT\r\n");
            run_state = SNAKE_DIR_RIGHT;
            break;
        default:
            break;
        }
    }
}

static rt_bool_t event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);

    rt_kprintf("event_handler\r\n");

    if (event->type == RTGUI_EVENT_PAINT)
    {
        rt_kprintf("RTGUI_EVENT_PAINT\r\n");
        rtgui_win_event_handler((struct rtgui_object *)object, event);
        snake_draw(widget);
        rtgui_timer_start(timer);
    }
    else if (event->type == RTGUI_EVENT_SHOW)
    {
        rt_kprintf("RTGUI_EVENT_SHOW\r\n");
        rtgui_win_event_handler((struct rtgui_object *)object, event);
        snake_draw(widget);
        rtgui_timer_start(timer);
    }
    else if (event->type == RTGUI_EVENT_HIDE)
    {
        rt_kprintf("RTGUI_EVENT_HIDE\r\n");
        rtgui_win_event_handler((struct rtgui_object *)object, event);
        rtgui_timer_stop(timer);
    }
    else if (event->type == RTGUI_EVENT_WIN_DEACTIVATE)
    {
        rt_kprintf("RTGUI_EVENT_WIN_DEACTIVATE\r\n");
        rtgui_win_event_handler((struct rtgui_object *)object, event);
        rtgui_timer_stop(timer);
    }
    else if (event->type == RTGUI_EVENT_KBD)
    {
        rtgui_win_event_handler((struct rtgui_object *)object, event);
        snake_handler(widget, event);
    }
    else
    {
        rt_kprintf("event->type:%d\r\n", event->type);
        return rtgui_win_event_handler((struct rtgui_object *)object, event);
    }

    return RT_FALSE;
}

static void timeout(struct rtgui_timer *timer, void *parameter)
{
    struct rtgui_widget *widget;
    SYS_STE ret;

    if (!map)
        return;

    ret = snake_step(run_state, map);
    if (OVER == ret)
        return;

    if (FOOD == ret)
    {
        snake_len++;
        if (snake_len >= (map->width * map->height) / 3)
        {
            point_t start;

            start.x = snake_init_pointx;
            start.y = snake_init_pointy;
            run_state = SNAKE_DIR_DOWN;
            snake_len = snake_length_init;

            if (!snake_restart(&start, snake_len, run_state, map))
            {
                map_deinit(map);
                snake_deinit();
                map = RT_NULL;
            }
        }

        food_init(map, 1);
    }

    widget = RTGUI_WIDGET(parameter);
    snake_update(widget);
}

void snake_main(void)
{
    struct rtgui_app *application;
    struct rtgui_win *win;
    rtgui_rect_t rect;

    application = rtgui_app_create("sanke_app");
    if (application != RT_NULL)
    {
        rtgui_get_screen_rect(&rect);
        rtgui_set_mainwin_rect(&rect);
        win = rtgui_mainwin_create(RT_NULL,
                                   "sanke_win",
                                   RTGUI_WIN_STYLE_MAINWIN | RTGUI_WIN_STYLE_DESTROY_ON_CLOSE);
        if (win == RT_NULL)
        {
            rt_kprintf("sanke_win create fail!\r\n");
            return;
        }

        rtgui_object_set_event_handler(RTGUI_OBJECT(win), event_handler);

        timer = rtgui_timer_create(RT_TICK_PER_SECOND / 2,
                                   RT_TIMER_FLAG_PERIODIC,
                                   timeout,
                                   (void *)win);

        rtgui_win_show(win, RT_TRUE);

        //退出后才返回
        map_deinit(map);
        snake_deinit();
        food_deinit();
        rtgui_app_destroy(application);
    }
}

#include <finsh.h>
FINSH_FUNCTION_EXPORT(snake_main, snake run)
