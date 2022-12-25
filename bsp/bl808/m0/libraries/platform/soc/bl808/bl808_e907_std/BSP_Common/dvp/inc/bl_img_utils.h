#ifndef __BL_IMG_UTILITY_H__
#define __BL_IMG_UTILITY_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <FreeRTOS.h>
#include <task.h>

#if !defined(MIN)
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#endif

#if !defined(MAX)
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

typedef struct {
    TickType_t tick;
    uint32_t   pmc_cntr;
    uint32_t   pmxev_cntr;
} img_perf_t;

int32_t round_off(int32_t data, int32_t round_bit);
int32_t alpha_blend(int32_t data_0, int32_t data_1, int32_t alpha_0, int32_t alpha_precision);
int32_t clip(int32_t min, int32_t max, int32_t data);
int32_t soft_clip(int32_t min, int32_t max, int32_t data, int32_t slope, int32_t slope_precision);
bool    within(int32_t min, int32_t max, int32_t data);
int     even_division(int dividend, int divisor);

void img_perf_enter();
void img_perf_get(char* tag, img_perf_t *perf);
void img_perf_printer(char* tag, img_perf_t *start, img_perf_t *end);
void img_perf_exit();

int utils_get_resolution_param(char *optarg, uint32_t *width, uint32_t *height);

#endif
