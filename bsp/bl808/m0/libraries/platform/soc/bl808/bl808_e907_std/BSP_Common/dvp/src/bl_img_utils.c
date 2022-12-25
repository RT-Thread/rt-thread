#include "bl_img_utils.h"
#include "bflb_platform.h"

int32_t round_off(int32_t data, int32_t round_bit)
{
    if (round_bit == 1) {
      return data >> round_bit;
    }
    else {
      return (data + (1 << (round_bit - 1))) >> round_bit;
    }
}

int32_t alpha_blend(int32_t data_0, int32_t data_1, int32_t alpha_0, int32_t alpha_prec)
{
    return round_off(alpha_0 * (data_0 - data_1) + (data_1 << alpha_prec), alpha_prec);
}

int32_t clip(int32_t min, int32_t max, int32_t data)
{
    if (data < min) {
      return min;
    }
    else if (data > max) {
      return max;
    }
    else {
      return data;
    }
}

int32_t soft_clip(int32_t min, int32_t max, int32_t data, int32_t slope, int32_t slope_precision)
{
    int32_t data_blend;

    if (data < min) {
        data_blend = min;
    }
    else if (data > max) {
        data_blend = max;
    }
    else {
        data_blend = data;
    }

    return alpha_blend(data, data_blend, slope, slope_precision);
}

bool within(int32_t min, int32_t max, int32_t data)
{
    if (data >= min && data <= max) {
        return true;
    }
    else {
        return false;
    }
}

int even_division(int dividend, int divisor)
{
    int tmp = dividend/divisor;
    return (tmp - tmp % 2);
}

void img_perf_enter()
{
    vTaskEnterCritical();
    //PMC_Reset_All();
    //PMC_Select(0);
    MSG("================ENTER IMG PERF==================\r\n");
}

void img_perf_get(char* tag, img_perf_t *perf)
{
    perf->tick       = xTaskGetTickCount();
    //perf->pmc_cntr   = __get_PMCCNTR();
    //perf->pmxev_cntr = __get_PMXEVCNTR();
    MSG("[%s] tick: %lu, pmc_cntr: %d, pmxev_cntr: %d\r\n",
        tag, (long unsigned int)perf->tick, perf->pmc_cntr, perf->pmxev_cntr);
}

void img_perf_printer(char* tag, img_perf_t *start, img_perf_t *end)
{
    TickType_t elapse_time;
    uint32_t pmc_num, pmxev_num;
    float mcps, mips;

    elapse_time = end->tick - start->tick;
    pmc_num     = end->pmc_cntr - start->pmc_cntr;
    pmxev_num   = end->pmxev_cntr - start->pmxev_cntr;

    mcps = (float)pmc_num/elapse_time/1000;
    mips = (float)pmxev_num/elapse_time/1000;

    MSG("[%s]: pmc_num: %d,  pmxev_num: %d\r\n",
        tag, pmc_num, pmxev_num);
    MSG("[%s]: TICK: %lu,  MCPS: %.2f, MIPS: %.2f\r\n",
        tag, (long unsigned int)elapse_time, mcps, mips);
}

void img_perf_exit()
{
    MSG("================EXIT IMG PERF==================\r\n");
    //PMC_Reset_All();
    vTaskExitCritical();
}

int utils_get_resolution_param(char *optarg, uint32_t *width, uint32_t *height)
{
    if ((strstr(optarg, "1080p") != 0) || (strstr(optarg, "1080P") != 0)) {
        *width = 1920;
        *height = 1080;
    } else if ((strstr(optarg, "720p") != 0) || (strstr(optarg, "720P") != 0)) {
        *width = 1280;
        *height = 720;
    } else if ((strstr(optarg, "svga") != 0) || (strstr(optarg, "SVGA") != 0)) {
        *width = 800;
        *height = 600;
    } else if ((strstr(optarg, "vga") != 0) || (strstr(optarg, "VGA") != 0)) {
        *width = 640;
        *height = 480;
    } else if (sscanf(optarg, "%ux%u", width, height) == 2) {
    } else {
        return -1;
    }

    return 0;
}
