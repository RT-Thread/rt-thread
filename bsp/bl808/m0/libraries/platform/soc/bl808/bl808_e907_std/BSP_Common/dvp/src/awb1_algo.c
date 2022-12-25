#include <string.h>
#include <bl808_dsp2.h>

#include "img_param.h"
#include "awb1_algo.h"

#include "bl_img_utils.h"

/*********************** constants ********************************/

#define AWB_STATS_GRID_NUM_X   (32)
#define AWB_STATS_GRID_NUM_Y   (32)
#define AWB_STATS_GRID_NUM     ((AWB_STATS_GRID_NUM_X)*(AWB_STATS_GRID_NUM_Y))

#define AWB_MODE_MIN        AWB_MODE_AUTO
#define AWB_MODE_MAX        (AWB_MODE_NUM - 1)


#define DEFAULT_COLOR_TEMP      5000

#if FAST_CAPTURE_MODE
#define INIT_AWB_SPEED          16
#else
#define INIT_AWB_SPEED          5
#endif

typedef struct __awb_obj_t awb_obj_t;
typedef int (*AWB_ALGO_FUNC)(awb_obj_t*);

struct __awb_obj_t{
    awb_info_t        awb_info;
    uint32_t          awb_configed;
    uint32_t          awb_config_update;
    rb_gain_fp_t      rb_gain_f;
    int               awb_speed;       /* 0 ~ 16 */
    AWB_MODE          new_awb_mode;
    BL_COLOR_TEMP     new_color_temp;
    AWB_ALGO_FUNC     awb_algo_func;
};

/*********************** type defines ********************************/
typedef struct {
    int gr_ratio;
    int gb_ratio;
} wb_ratio_t;

typedef struct  {
    void* awb_stats_data;
    int is_awb_stats_update;
} dsp2_awb_stats_info_t;

/*********************** helper functions ********************************/


/*********************** global varibles ********************************/

static awb_obj_t awb_obj;
static dsp2_awb_stats_info_t awb_stats_info;
static dsp2_awb_sum_t awb_stats_data[AWB_STATS_GRID_NUM];

static void awb_obj_reset()
{
    memset(&awb_obj, 0, sizeof(awb_obj_t));
    awb_obj.awb_info.color_temp = -1;        /* uknown color temp */
}

static void awb_stats_reset()
{
    if (NULL == awb_stats_info.awb_stats_data) {
        awb_stats_info.awb_stats_data = &awb_stats_data;
        if (NULL == awb_stats_info.awb_stats_data) {
            MSG("pvPortMalloc(AWB Grid) error\r\n");
            return;
        }
    }

    memset(awb_stats_info.awb_stats_data, 0, AWB_STATS_GRID_NUM*sizeof(dsp2_awb_sum_t));
    awb_stats_info.is_awb_stats_update = -1;
}

static void rgb_sum_to_wb_ratio(RGB_SUM_S *rgb_sum, DSP2_RB_Gain_Type *rb_gain, wb_ratio_t *wb_ratio)
{
    /* (g_sum / r_sum) * 1024 */
    wb_ratio->gr_ratio = DIV_ROUND(rgb_sum->g_sum << 10, rgb_sum->r_sum);
    wb_ratio->gb_ratio = DIV_ROUND(rgb_sum->g_sum << 10, rgb_sum->b_sum);
}

static bool match_white_region(wb_ratio_t *wb_ratio, const white_region_t *white_region)
{
    int i, j, c = 0;
    int testx = wb_ratio->gr_ratio;
    int testy = wb_ratio->gb_ratio;
    const vertex_t *vert_array = &white_region->hexagon.vert_array[0];

    for (i = 0, j = VERT_NUM-1; i < VERT_NUM; j = i++) {
      if ( ((vert_array[i].verty >= testy) != (vert_array[j].verty >= testy)) &&
        (testx <= (vert_array[j].vertx - vert_array[i].vertx) * (testy - vert_array[i].verty) /
        (vert_array[j].verty - vert_array[i].verty) + vert_array[i].vertx) )
         c = !c;
    }
    return (bool)c;
}

static int match_all_white_region(wb_ratio_t *wb_ratio, int white_point_cnt[])
{
    int wr_idx;
    int wr_num = img_param_get_num_white_region();
    const white_region_t *white_region;

    for (wr_idx = 0; wr_idx < wr_num; wr_idx++) {
        img_param_get_white_region(wr_idx, &white_region);
        if (match_white_region(wb_ratio, white_region)) {
            white_point_cnt[wr_idx]++;
            //MSG("\t %d_%d \r\n", wb_ratio->gr_ratio, wb_ratio->gb_ratio); //for AWB tuning with AMB_AWB_tool
            //MSG("\t\t ----> match white region [%d]!!!\r\n", wr_idx);
        }
    }

    return 0;
}

static int weight_avg_color_temp(int white_point_cnt[], BL_COLOR_TEMP *color_temp)
{
    int i;
    const white_region_t *white_region;
    int num_regions = img_param_get_num_white_region();
    int ct_sum = 0;
    int total_wp_cnt = 0;

    for (i = 0; i < num_regions; i++) {
        img_param_get_white_region(i, &white_region);
        ct_sum += white_region->color_temp * white_point_cnt[i] * white_region->weight;
        total_wp_cnt += white_point_cnt[i] * white_region->weight;
        MSG("\t %dK: %d \t wt: %d\r\n", white_region->color_temp, white_point_cnt[i], white_region->weight);
    }

    if (total_wp_cnt != 0) {
        *color_temp = ct_sum / total_wp_cnt;
    } else {
        *color_temp = DEFAULT_COLOR_TEMP;
    }

    return 0;
}

static int calc_color_temp(DSP2_RB_Gain_Type *rb_gain, BL_COLOR_TEMP *color_temp)
{
    int i;
    int valid_grid_num;
    RGB_SUM_S rgb_sum;
    wb_ratio_t wb_ratio;
    int white_point_cnt[img_param_get_num_white_region()];

    MSG("curr rb gain (%d, %d)\r\n", rb_gain->r_gain, rb_gain->b_gain);
    memset(white_point_cnt, 0, sizeof(white_point_cnt));

    DSP2_Get_AWB_ValidGridNum(&valid_grid_num);

    for (i = 0; i < AWB_STATS_GRID_NUM; i++) {
        // DSP2_Get_AWB_Sum(i, &rgb_sum);
        rgb_sum.r_sum = ((dsp2_awb_sum_t*)(awb_stats_info.awb_stats_data))[i].r_sum;
        rgb_sum.g_sum = ((dsp2_awb_sum_t*)(awb_stats_info.awb_stats_data))[i].g_sum;
        rgb_sum.b_sum = ((dsp2_awb_sum_t*)(awb_stats_info.awb_stats_data))[i].b_sum;
        //MSG("rgb_sum[%d] (%d, %d, %d)\r\n", i, rgb_sum.r_sum, rgb_sum.g_sum, rgb_sum.b_sum);

        rgb_sum_to_wb_ratio(&rgb_sum, rb_gain, &wb_ratio);

        //MSG("\t tile (%d, %d), wb ratio (%d, %d)\r\n", i/32, i%32, wb_ratio.gr_ratio, wb_ratio.gb_ratio);
        //MSG("\t %d_%d \r\n", wb_ratio.gr_ratio, wb_ratio.gb_ratio); //for AWB tuning with AMB_AWB_tool
        match_all_white_region(&wb_ratio, white_point_cnt);
    }

    MSG("white point count:\r\n");

    weight_avg_color_temp(white_point_cnt, color_temp);

    MSG(">> target CT: %dK\r\n", *color_temp);

    return 0;
}

static void set_rgb_threshold(dsp2_awb_stats_conf_t *awb_stats_conf)
{
#if 0
    awb_stats_conf->r_max_thr = 3072;
    awb_stats_conf->r_min_thr = 64;
    awb_stats_conf->g_max_thr = 3072;
    awb_stats_conf->g_min_thr = 64;
    awb_stats_conf->b_max_thr = 3072;
    awb_stats_conf->b_min_thr = 64;
#else
    awb_stats_conf->r_max_thr = 4095;
    awb_stats_conf->r_min_thr = 0;
    awb_stats_conf->g_max_thr = 4095;
    awb_stats_conf->g_min_thr = 0;
    awb_stats_conf->b_max_thr = 4095;
    awb_stats_conf->b_min_thr = 0;
#endif
}

static int awb1_stats_enable(aaa_stats_cfg_t *stats)
{
    dsp2_awb_stats_conf_t awb_stats_conf;

    awb_stats_conf.grid_num_x  = AWB_STATS_GRID_NUM_X;
    awb_stats_conf.grid_num_y  = AWB_STATS_GRID_NUM_Y;
    awb_stats_conf.img_width   = stats->act_win.width;
    awb_stats_conf.img_height  = stats->act_win.height;
    awb_stats_conf.grid_width  = even_division(stats->act_win.width, AWB_STATS_GRID_NUM_X);
    awb_stats_conf.grid_height = even_division(stats->act_win.height, AWB_STATS_GRID_NUM_Y);
    awb_stats_conf.roi_start_x = (awb_stats_conf.img_width \
        - AWB_STATS_GRID_NUM_X*awb_stats_conf.grid_width)/2 ;
    awb_stats_conf.roi_start_y = (awb_stats_conf.img_height \
        - AWB_STATS_GRID_NUM_Y*awb_stats_conf.grid_height)/2 ;
    awb_stats_conf.roi_width   = AWB_STATS_GRID_NUM_X*awb_stats_conf.grid_width;
    awb_stats_conf.roi_height  = AWB_STATS_GRID_NUM_Y*awb_stats_conf.grid_height;

    set_rgb_threshold(&awb_stats_conf);

    DSP2_Set_AWB_Stats_Conf(&awb_stats_conf);
    DSP2_Set_AWB_State(ENABLE);

    return 0;
}

#if 0
static int get_rgb_sum(RGB_SUM_S *rgb_sum)
{
    int i;
    int total_grid_num, valid_grid_num;
    int buf_idx;
    int init_buf_idx;
    RGB_SUM_S grid_rgb_sum;

    memset(rgb_sum, 0, sizeof(*rgb_sum));

    DSP2_Get_AWB_ValidGridNum(&total_grid_num, &valid_grid_num);

    for (i = 0; i < total_grid_num; i++) {
        DSP2_Get_AWB_Sum(i, &grid_rgb_sum, &buf_idx);
        rgb_sum->r_sum += grid_rgb_sum.r_sum;
        rgb_sum->g_sum += grid_rgb_sum.g_sum;
        rgb_sum->b_sum += grid_rgb_sum.b_sum;
        if (i == 0) {
            init_buf_idx = buf_idx;
        };
        if (buf_idx != init_buf_idx) {
            MSG("Got AWB stats from different frames! %d, %d\r\n", init_buf_idx, buf_idx);
        }
//        MSG("\t\t grid[%d]: r %d, g %d, b %d\r\n", i, grid_rgb_sum.r_sum, grid_rgb_sum.g_sum, grid_rgb_sum.b_sum);
    }


//    MSG("valid grid number: %d\r\n", valid_grid_num);
//    MSG("Rsum %d, Gsum %d, Bsum %d\r\n", rgb_sum->r_sum, rgb_sum->g_sum, rgb_sum->b_sum);

    return 0;
}
#endif

static int calc_rb_gain_by_color_temp(BL_COLOR_TEMP color_temp, DSP2_RB_Gain_Type *rb_gain)
{
    int wb_info_idx;
    BL_COLOR_TEMP color_temp_L, color_temp_H;
    const wb_info_t *wb_info_L, *wb_info_H;
    intpl_point_t point_L, point_H;
    int gain_tmp;
    int num_wb_modes = img_param_get_num_manual_wb_info();

    for (wb_info_idx = 0; wb_info_idx < (num_wb_modes - 1); wb_info_idx++) {

        img_param_get_manual_wb_info(wb_info_idx, &wb_info_L);
        img_param_get_manual_wb_info(wb_info_idx + 1, &wb_info_H);

        color_temp_L = wb_info_L->color_temp;
        color_temp_H = wb_info_H->color_temp;

        if (color_temp >= color_temp_L && color_temp <= color_temp_H) {
            /* now we get the range of color temp */

            /* interplate r_gain */
            point_L = create_intpl_point(color_temp_L, wb_info_L->rb_gain.r_gain);
            point_H = create_intpl_point(color_temp_H, wb_info_H->rb_gain.r_gain);
            linear_interpolate(&point_L, &point_H, color_temp, &gain_tmp);
            rb_gain->r_gain = gain_tmp;

            /* interplate b_gain */
            point_L = create_intpl_point(color_temp_L, wb_info_L->rb_gain.b_gain);
            point_H = create_intpl_point(color_temp_H, wb_info_H->rb_gain.b_gain);
            linear_interpolate(&point_L, &point_H, color_temp, &gain_tmp);
            rb_gain->b_gain = gain_tmp;
            return 0;
        }

        if (wb_info_idx == 0 && color_temp < color_temp_L) {
            *rb_gain = wb_info_L->rb_gain;
            return 0;
        }

        if (wb_info_idx == (num_wb_modes - 2) && color_temp > color_temp_H) {
            *rb_gain = wb_info_H->rb_gain;
            return 0;
        }
    }

    /* should never reach here */
    return -1;
}

/* update AWB result and accordingly other image control function */
static void update_awb_result(awb_obj_t *awb_obj)
{
    if (awb_obj->awb_info.ct_update) {
        calc_rb_gain_by_color_temp(awb_obj->awb_info.color_temp, &(awb_obj->awb_info.rb_gain));
        awb_obj->awb_info.rb_gain_update = 1;
    }
}

static int awb1_clear_info()
{
    awb_obj.awb_info.rb_gain_update = 0;
    awb_obj.awb_info.ct_update = 0;

    return 0;
}

static int awb1_advanced(awb_obj_t *awb_obj)
{
    BL_COLOR_TEMP target_ct;

#if (FAST_CAPTURE_MODE)
    /* skip awb computing due to performance limit on M4 or FPGA */
    return 0;
#endif

//    TickType_t start_time_ms = xTaskGetTickCount();
    calc_color_temp(&(awb_obj->awb_info.rb_gain), &target_ct);
//    MSG("elapse %lu ms\r\n", xTaskGetTickCount() - start_time_ms);

    awb_obj->awb_info.color_temp = (int)(awb_obj->awb_speed*target_ct
        + (16-awb_obj->awb_speed)*awb_obj->awb_info.color_temp)/16;

    MSG(">> next CT: %dK\r\n", awb_obj->awb_info.color_temp);

    awb_obj->awb_info.ct_update = 1;

    return 0;
}

#if 0
static int awb1_grey_world(awb_obj_t *awb_obj)
{
    static int skip_num = 0;
    float K=100.0f;

    float Rerr, Berr;
    RGB_SUM_S rgb_sum;
    float rgain_f = awb_obj->rb_gain_f.r_gain;
    float bgain_f = awb_obj->rb_gain_f.b_gain;

    get_rgb_sum(&rgb_sum);

    /* The AWB stats does not get affected by RGB gain, so we need add RGB gain to reflect the final image color */
    rgb_sum.r_sum = (uint64_t)rgb_sum.r_sum * awb_obj->rb_gain.r_gain / RGB_GAIN_1X;
    rgb_sum.b_sum = (uint64_t)rgb_sum.b_sum * awb_obj->rb_gain.b_gain / RGB_GAIN_1X;

    /* avoid the devider to be zero */
    if (rgb_sum.g_sum == 0)
        rgb_sum.g_sum = 1;

    if (awb_info.awb_info != AWB_MODE_AUTO) {
        if (skip_num++ > 50) {
            MSG("Rsum %d, Gsum %d, Bsum %d\r\n", rgb_sum.r_sum, rgb_sum.g_sum, rgb_sum.b_sum);
            skip_num = 0;
        }
        return 0;
    }

    MSG("Rsum %d, Gsum %d, Bsum %d\r\n", rgb_sum.r_sum, rgb_sum.g_sum, rgb_sum.b_sum);
    MSG("\t R/G ratio = %.4f, B/G ratio = %.4f\r\n",
        (float)rgb_sum.r_sum/rgb_sum.g_sum, (float)rgb_sum.b_sum/rgb_sum.g_sum);

    Rerr = 1.0f-(float)rgb_sum.r_sum/rgb_sum.g_sum;
    Berr = 1.0f-(float)rgb_sum.b_sum/rgb_sum.g_sum;

    MSG("\t Rerr = %.4f, Berr = %.4f\r\n", Rerr, Berr);

    rgain_f = (rgain_f + Rerr*K);
    bgain_f = (bgain_f + Berr*K);

    MSG("rgain_f %.2f, bgain_f %.2f\r\n", rgain_f, bgain_f);

    if ( rgain_f < 2560.0f ) //80
        rgain_f = 2560.0f;  //80
    else if (rgain_f > 12800.0f ) //225
        rgain_f = 12800.0f;

    if( bgain_f < 2560.0f ) //211
        bgain_f = 2560.0f;  //211
    else if (bgain_f > 22400.0f )  //600    //236*1.6
        bgain_f = 22400.0f;

    awb_obj->rb_gain_f.r_gain = rgain_f;
    awb_obj->rb_gain_f.b_gain = bgain_f;
    awb_obj->rb_gain.r_gain = FLOAT_TO_INT(rgain_f);
    awb_obj->rb_gain.b_gain = FLOAT_TO_INT(bgain_f);
    awb_obj->awb_info.rb_gain_update = 1;

    return 0;
}
#endif

static bool is_awb1_stats_update(void)
{
    return (0 == awb_stats_info.is_awb_stats_update);
}

static void awb1_update_stats(void)
{
    //  trade space for time; also could use  trade time for space
    awb_stats_info.is_awb_stats_update = DSP2_Get_AWB_Stats(AWB_STATS_GRID_NUM, \
        (uint32_t*)(awb_stats_info.awb_stats_data));
}

static int awb1_set_mode(AWB_MODE mode)
{
    if (!is_param_valid(mode, AWB_MODE_MIN, AWB_MODE_MAX)) {
        MSG("awb_set_mode: invalid AWB mode %d!\r\n", mode);
        return -1;
    }

    awb_obj.new_awb_mode = mode;
    awb_obj.awb_config_update |= AWB_UPDATE_BIT_MODE;

    MSG("awb_set_mode: %d\r\n", mode);

    return 0;
}

static int awb1_get_mode(AWB_MODE *mode)
{
    *mode = awb_obj.awb_info.awb_mode;

    return 0;
}

/* for debug purpose only */
static int awb1_set_color_temp(BL_COLOR_TEMP color_temp)
{
    awb_obj.new_color_temp = color_temp;

    awb_obj.awb_config_update |= AWB_UPDATE_BIT_COLOR_TEMP;

    MSG("awb_set_color_temp: %d K\r\n", color_temp);

    return 0;
}

static int awb1_get_color_temp(BL_COLOR_TEMP *color_temp)
{
    *color_temp = awb_obj.awb_info.color_temp;

    return 0;
}

static int awb1_set_gain(DSP2_RGB_Gain_Type *rgb_gain)
{
    DSP2_Set_AWB_Gain(rgb_gain);

    awb_obj.awb_info.rb_gain.r_gain = rgb_gain->r_gain;
    awb_obj.awb_info.rb_gain.b_gain = rgb_gain->b_gain;

    return 0;
}

static int awb1_get_gain(DSP2_RGB_Gain_Type *rgb_gain)
{
    DSP2_Get_AWB_Gain(rgb_gain);
    return 0;
}

static int awb1_config(awb_config_t *config, bool is_virtual_sensor)
{
    if (is_virtual_sensor) {
        awb_obj.awb_speed = 16;
    }

    awb1_stats_enable(&(config->stats_cfg));
    awb_obj.awb_configed = 1;

    return 0;
}

static int awb1_get_info(awb_info_t **awb_info)
{
    *awb_info = &(awb_obj.awb_info);
    return 0;
}

static int awb1_control(void)
{
    if (!awb_obj.awb_configed) {
        MSG("AWB can't run! Not configured\r\n");
        return -1;
    }

    awb1_clear_info();
    awb1_update_stats();

    /* Check if AWB config is updated */
    if (awb_obj.awb_config_update) {
        if (awb_obj.awb_config_update & AWB_UPDATE_BIT_MODE) {
            awb_obj.awb_info.awb_mode = awb_obj.new_awb_mode;
        }

        /* if new color temp is not equal to previous one, awb_info.ct_update color temp related param */
        if (awb_obj.awb_config_update & AWB_UPDATE_BIT_COLOR_TEMP &&
            awb_obj.new_color_temp != awb_obj.awb_info.color_temp) {
            awb_obj.awb_info.color_temp = awb_obj.new_color_temp;
            awb_obj.awb_info.ct_update = 1;
        }

        awb_obj.awb_config_update = 0;
    }

    if (awb_obj.awb_info.awb_mode != AWB_MODE_AUTO) {
        return 0;
    }

    if (!is_awb1_stats_update()) {
        return -1;
    }

    awb_obj.awb_algo_func(&awb_obj);
    update_awb_result(&awb_obj);

    return 0;
}

static void awb_func_init(awb_func_t *func)
{
    func->config          = awb1_config;
    func->control         = awb1_control;
    func->get_info        = awb1_get_info;
    func->set_mode        = awb1_set_mode;
    func->get_mode        = awb1_get_mode;
    func->set_gain        = awb1_set_gain;
    func->get_gain        = awb1_get_gain;
    func->set_color_temp  = awb1_set_color_temp;
    func->get_color_temp  = awb1_get_color_temp;
}

int awb1_init(awb_func_t *func)
{
    awb_obj_reset();
    awb_stats_reset();
    awb_obj.awb_algo_func = awb1_advanced;

    awb_obj.awb_info.awb_mode = AWB_MODE_AUTO;
    awb_obj.awb_speed = INIT_AWB_SPEED;

    awb_obj.awb_info.rb_gain.r_gain = 6144;
    awb_obj.awb_info.rb_gain.b_gain = 5280;

    awb_obj.rb_gain_f.r_gain = (float)6144;
    awb_obj.rb_gain_f.b_gain = (float)5280;

    awb_obj.awb_info.rb_bias.r_gain = RGB_GAIN_1X;
    awb_obj.awb_info.rb_bias.b_gain = RGB_GAIN_1X;

    DSP2_Set_RB_Gain(&(awb_obj.awb_info.rb_gain));

    awb_func_init(func);

    MSG("awb_config: rgain %d, bgain %d\r\n", awb_obj.awb_info.rb_gain.r_gain, awb_obj.awb_info.rb_gain.b_gain);
    return 0;
}