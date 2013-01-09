#include <string.h>
#include <stdlib.h>
#include <rtthread.h>
#include "snake.h"

#define ASSERT_RET(x, ret)  \
    do{                     \
        if (x)              \
            return ret;     \
    }while(0)

rt_list_t snake_head;
SNAKE_DIR prevdir, newdir;

static SNAKE_DIR dir_adjust(SNAKE_DIR dir)
{
    if ((SNAKE_DIR_UP == prevdir && SNAKE_DIR_DOWN != dir)
            || (SNAKE_DIR_DOWN == prevdir && SNAKE_DIR_UP != dir)
            || (SNAKE_DIR_LEFT == prevdir && SNAKE_DIR_RIGHT != dir)
            || (SNAKE_DIR_RIGHT == prevdir && SNAKE_DIR_LEFT != dir)
       )
    {
        newdir = dir;
    }
    else
    {
        rt_kprintf("dirction change error\n\r");
    }

    return newdir;
}

static void across_XY(point_t *node, const map_t *map)
{
    RT_ASSERT(node != RT_NULL && map != RT_NULL);

    // 如果长度超出当前边框则可以穿越墙到对面
    node->x = (node->x + map->width) % map->width;
    node->y = (node->y + map->height) % map->height;
}

static SYS_STE node_update(snake_t *tail, const point_t *node, map_t *map)
{
    SYS_STE ret;
    point_t *pos;

    RT_ASSERT(tail != RT_NULL && node != RT_NULL && map != RT_NULL);

    pos = map->snake_flush;
    pos[0].x = pos[0].y = -1;
    pos[1].x = pos[1].y = -1;

    ret = (SYS_STE)map->range[node->y * map->width + node->x];

    if (FOOD == map->range[node->y * map->width + node->x])
    {
        // 吃一个食物增加一个节点
        snake_t *new = (snake_t *)rt_malloc(sizeof(snake_t));
        if (!new)
            return NORMAL;

        pos[0] = *node;
        new->body = *node;
        rt_list_insert_after(&snake_head, &new->list);
    }
    else if (NORMAL == map->range[node->y * map->width + node->x])
    {
        // 将尾巴修改后拿到头部，其他不变
        rt_list_remove(&tail->list);
        map->range[tail->body.y * map->width + tail->body.x] = NORMAL;

        pos[0] = *node;
        pos[1] = tail->body;

        tail->body = *node;
        rt_list_insert_after(&snake_head, &tail->list);
    }

    map->range[node->y * map->width + node->x] = OVER;

    if (ret != OVER)
        prevdir = newdir;

    return ret;
}


map_t *map_init(rt_uint32_t width, rt_uint32_t heigth)
{
    map_t *map = rt_malloc(sizeof(map_t));

    if (map != RT_NULL)
    {
        map->range = rt_malloc(heigth * width);

        if (!map->range)
        {
            rt_free(map);
            map = RT_NULL;
        }
        else
        {
            map->width = width;
            map->height = heigth;
            memset(map->range, NORMAL, heigth * width);
        }
    }

    return map;
}

// 构造一条指定长度的蛇在指定点
rt_bool_t snake_init(const point_t *start, const int length, const SNAKE_DIR dir, map_t *map)
{
    rt_int32_t i;
    rt_int32_t inc_x, inc_y;
    point_t old = *start;

    ASSERT_RET(!map || !start, RT_FALSE);

    rt_list_init(&snake_head);

    if (dir == SNAKE_DIR_UP || dir == SNAKE_DIR_DOWN)
    {
        if (map->height <= length)
            return RT_FALSE;

        inc_x = 0;
        inc_y = dir == SNAKE_DIR_DOWN ? 1 : -1;  // 反向延长身子，头部在指定位置
        old.y -= inc_y;
    }
    else
    {
        if (map->width <= length)
            return RT_FALSE;

        inc_y = 0;
        inc_x = dir == SNAKE_DIR_RIGHT ? -1 : 1;
        old.x -= inc_x;
    }

    for (i = 0; i < length; i++)
    {
        snake_t *new = (snake_t *)rt_malloc(sizeof(snake_t));
        if (!new)
            return RT_FALSE;

        new->body.y = inc_y + old.y;
        new->body.x = inc_x + old.x;

        // 如果长度超出当前边框则可以穿越墙到对面
        across_XY(&new->body, map);

        map->range[new->body.y * map->width + new->body.x] = OVER;

        old = new->body;
        rt_list_insert_before(&snake_head, &new->list);
    }

    prevdir = dir;

    return RT_TRUE;
}

// 构造出食物
rt_bool_t food_init(map_t *map, rt_uint32_t max_num)
{
    point_t food;

#ifndef FOOD_TIMEOUT
#define FOOD_TIMEOUT    10
#endif

    rt_uint32_t timeout, num;

    ASSERT_RET(!map, RT_FALSE);

    num = 0;
    timeout = rt_tick_get();
    srand(rand());

    map->food_flush[0].x = map->food_flush[0].y = -1;

    do
    {
        food.x = rand() % map->width;
        food.y = rand() % map->height;

        if (map->range[food.y * map->width + food.x] == NORMAL)
        {
            map->food_flush[0] = food;
            map->range[food.y * map->width + food.x] = FOOD;
            num++;
        }
    }
    while (num < max_num && rt_tick_get() - timeout < FOOD_TIMEOUT);

    return num;
}

void map_deinit(map_t *map)
{
    if (map)
    {
        if (map->range)
        {
            rt_free(map->range);
            map->range = RT_NULL;
        }
        rt_free(map);
    }
}

void snake_deinit(void)
{
    snake_t *node;

    while (!rt_list_isempty(&snake_head))
    {
        node = rt_list_entry(snake_head.prev, snake_t, list);
        rt_list_remove(&node->list);
        rt_free(node);
    }
}

void food_deinit(void)
{

}

SYS_STE snake_step(SNAKE_DIR dir, map_t *map)
{
    snake_t *tail, *head;
    point_t node;

    ASSERT_RET(!map, RT_FALSE);

    dir = dir_adjust(dir);

    // 取出头尾两个节点，其他节点不需要改变
    tail = rt_list_entry(snake_head.prev, snake_t, list);
    head = rt_list_entry(snake_head.next, snake_t, list);

    node = head->body;

    // 构造一个新的蛇头坐标
    switch (dir)
    {
    case SNAKE_DIR_UP:
    case SNAKE_DIR_DOWN:
        node.y = head->body.y + (dir == SNAKE_DIR_DOWN ? -1 : 1);
        break;
    case SNAKE_DIR_LEFT:
    case SNAKE_DIR_RIGHT:
        node.x = head->body.x + (dir == SNAKE_DIR_RIGHT ? 1 : -1);
        break;
    }
    across_XY(&node, map);

    return node_update(tail, &node, map);
}

rt_bool_t snake_restart(const point_t *start, const int length, const SNAKE_DIR dir, map_t *map)
{
    ASSERT_RET(!map || !start, RT_FALSE);

    snake_deinit();
    memset(map->range, NORMAL, map->width * map->height);

    return snake_init(start, length, dir, map);
}
