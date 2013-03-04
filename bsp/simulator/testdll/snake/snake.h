#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <rtthread.h>

#define snake_length_max                  20  //最大蛇长
#define snake_length_init                 3   //初始化蛇长
#define snake_room_size_hight             8   //房子高 0-255 建议>8
#define snake_room_size_widht             8   //房子宽 0-255 建议>8

#define snake_init_pointx               1
#define snake_init_pointy               2

typedef struct
{
    rt_int32_t x, y;
} point_t;

typedef struct
{
    rt_int32_t width;       // max x
    rt_int32_t height;      // max y
    rt_uint8_t *range;      // map, map->range[y * map->width + x]
    point_t snake_flush[2];
    point_t food_flush[1];
} map_t;

typedef enum
{
    SNAKE_DIR_UP,
    SNAKE_DIR_DOWN,
    SNAKE_DIR_LEFT,
    SNAKE_DIR_RIGHT
} SNAKE_DIR;

typedef enum
{
    FOOD,       // 吃到水果
    OVER,       // 咬到自身
    NORMAL      // 正常行动
} SYS_STE;

typedef struct
{
    point_t body;
    rt_list_t list;
} snake_t;

// 构造一个地图
map_t *map_init(rt_uint32_t width, rt_uint32_t heigth);

// 构造一条指定长度的蛇在指定点
rt_bool_t snake_init(const point_t *start, const int length, const SNAKE_DIR dir, map_t *map);

// 构造出食物
rt_bool_t food_init(map_t *map, rt_uint32_t max_num);

void map_deinit(map_t *map);

void snake_deinit(void);

void food_deinit(void);

SYS_STE snake_step(SNAKE_DIR dir, map_t *map);

rt_bool_t snake_restart(const point_t *start, const int length, const SNAKE_DIR dir, map_t *map);

#endif
