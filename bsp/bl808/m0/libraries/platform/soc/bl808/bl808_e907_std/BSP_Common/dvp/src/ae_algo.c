#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <bl808_common.h>
#include <bl808_dsp2.h>

#include "image_sensor.h"
#include "img_param.h"

#include "ae_algo.h"
#include "bl_img_utils.h"

#define AE_STATS_GRID_NUM_X   (12)
#define AE_STATS_GRID_NUM_Y   (8)
#define AE_STATS_GRID_NUM     ((AE_STATS_GRID_NUM_X)*(AE_STATS_GRID_NUM_Y))

#define AE_UPDATE_MODE       (1 << 0)
#define AE_UPDATE_TARGET     (1 << 1)
#define AE_UPDATE_GAIN       (1 << 2)
#define AE_UPDATE_EXPO       (1 << 3)
#define AE_UPDATE_METERING   (1 << 4)

#define INIT_AE_ISO             1400
#define INIT_AE_EXPO_TIME       EXPO_TIME_1_100_SEC


#define AE_MODE_MIN             AE_MODE_AUTO
#define AE_MODE_MAX             ((AE_MODE_INVALID) - (1))
#define AE_METERING_MIN         AE_METERING_AVERAGE

#define AE_SYSGAIN_STEP        (GAIN_6_DB / 32)

#if FAST_CAPTURE_MODE
#define SKIP_FRAMES             2
#define INIT_AE_SPEED           16
#else
#define SKIP_FRAMES             2
#define INIT_AE_SPEED           3
#endif

typedef struct  {
    void* ae_stats_data;
    int   is_ae_stats_update;
} dsp2_ae_stats_info_t;

typedef enum {
    AE_FSM_INITED = 0,
    AE_FSM_BOOTING,
    AE_FSM_STABLE,
    AE_FSM_CONVERGENCE,
} AE_FSM;


typedef struct {
    ae_info_t        ae_info;
    int              ae_speed;
    AE_STATE         ae_state;
    int              sys_gain_max_reached;
    int              sys_gain_min_reached;
    int              luma_avg;
    int              force_ae_gain_update;
    uint32_t         ae_config_update;
    AE_MODE          new_ae_mode;
    AE_METERING      new_ae_metering;
    float            new_gain;
    BL_EXPO_TIME     new_expo;
    int              ae_start_skip_index;
    int              ae_boot_skip_index;
    int              ae_boot_index;
    int              max_sysgain_step;
    AE_FSM           ae_fsm;
} ae_obj_t;

/* TODO: dB step may change with different sensor */
static int shutter_table_step = AE_SYSGAIN_STEP;
static int max_sys_gain, min_sys_gain;
static int ae_max_gain = INT_TO_GAIN_DB(36);       /* start with no limitation */
static int ae_max_exposure = EXPO_TIME_1_25_SEC;    /* start with no limitation */
static int ae_min_exposure = EXPO_TIME_MIN;         /* start with no limitation */
static ae_obj_t ae_obj;
BL_EXPO_TIME sensor_expo_time;
BL_GAIN_DB sensor_gain;
static dsp2_ae_sum_t ae_stats_data[AE_STATS_GRID_NUM];

static dsp2_ae_stats_info_t ae_stats_info;

/* shutter table with 0.1875 dB step */
static const BL_EXPO_TIME shutter_table_ns[] = {
    10000000    ,       /* 0 dB */
    9785721     ,       /* -0.1875 dB */
    9576033     ,       /* -0.375 dB */
    9370838     ,
    9170040     ,
    8973545     ,
    8781261     ,
    8593096     ,
    8408964     ,
    8228777     ,
    8052452     ,
    7879904     ,
    7711054     ,
    7545822     ,
    7384131     ,
    7225904     ,
    7071068     ,
    6919549     ,
    6771278     ,
    6626183     ,
    6484198     ,
    6345255     ,
    6209289     ,
    6076237     ,
    5946036     ,
    5818624     ,
    5693943     ,
    5571934     ,
    5452539     ,
    5335702     ,
    5221369     ,
    5109486     ,
    5000000     ,       /* -6 dB */
    4892860     ,
    4788016     ,
    4685419     ,
    4585020     ,
    4486773     ,
    4390630     ,
    4296548     ,
    4204482     ,
    4114389     ,
    4026226     ,
    3939952     ,
    3855527     ,
    3772911     ,
    3692065     ,
    3612952     ,
    3535534     ,
    3459775     ,
    3385639     ,
    3313092     ,
    3242099     ,
    3172627     ,
    3104645     ,
    3038118     ,
    2973018     ,
    2909312     ,
    2846972     ,
    2785967     ,
    2726269     ,
    2667851     ,
    2610684     ,
    2554743     ,
    2500000     ,
    2446430     ,
    2394008     ,
    2342710     ,
    2292510     ,
    2243386     ,
    2195315     ,
    2148274     ,
    2102241     ,
    2057194     ,
    2013113     ,
    1969976     ,
    1927764     ,
    1886456     ,
    1846033     ,
    1806476     ,
    1767767     ,
    1729887     ,
    1692819     ,
    1656546     ,
    1621049     ,
    1586314     ,
    1552322     ,
    1519059     ,
    1486509     ,
    1454656     ,
    1423486     ,
    1392983     ,
    1363135     ,
    1333926     ,
    1305342     ,
    1277371     ,
    1250000     ,
    1223215     ,
    1197004     ,
    1171355     ,
    1146255     ,
    1121693     ,
    1097658     ,
    1074137     ,
    1051121     ,
    1028597     ,
    1006556     ,
    984988  ,
    963882  ,
    943228  ,
    923016  ,
    903238  ,
    883883  ,
    864944  ,
    846410  ,
    828273  ,
    810525  ,
    793157  ,
    776161  ,
    759530  ,
    743254  ,
    727328  ,
    711743  ,
    696492  ,
    681567  ,
    666963  ,
    652671  ,
    638686  ,
    625000  ,
    611608  ,
    598502  ,
    585677  ,
    573128  ,
    560847  ,
    548829  ,
    537069  ,
    525560  ,
    514299  ,
    503278  ,
    492494  ,
    481941  ,
    471614  ,
    461508  ,
    451619  ,
    441942  ,
    432472  ,
    423205  ,
    414136  ,
    405262  ,
    396578  ,
    388081  ,
    379765  ,
    371627  ,
    363664  ,
    355871  ,
    348246  ,
    340784  ,
    333481  ,
    326336  ,
    319343  ,
    312500  ,
    305804  ,
    299251  ,
    292839  ,
    286564  ,
    280423  ,
    274414  ,
    268534  ,
    262780  ,
    257149  ,
    251639  ,
    246247  ,
    240970  ,
    235807  ,
    230754  ,
    225810  ,
    220971  ,
    216236  ,
    211602  ,
    207068  ,
    202631  ,
    198289  ,
    194040  ,
    189882  ,
    185814  ,
    181832  ,
    177936  ,
    174123  ,
    170392  ,
    166741  ,
    163168  ,
    159671  ,
    156250  ,
    152902  ,
    149626  ,
    146419  ,
    143282  ,
    140212  ,
    137207  ,
    134267  ,
    131390  ,
    128575  ,
    125820  ,
    123124  ,
    120485  ,
    117903  ,
    115377  ,
    112905  ,
    110485  ,
    108118  ,
    105801  ,
    103534  ,
    101316  ,
    99145   ,
    97020   ,
    94941   ,
    92907   ,
    90916   ,
    88968   ,
    87061   ,
    85196   ,
    83370   ,
    81584   ,
    79836   ,
    78125   ,
    76451   ,
    74813   ,
    73210   ,
    71641   ,
    70106   ,
    68604   ,
    67134   ,
    65695   ,
    64287   ,
    62910   ,
    61562   ,
    60243   ,
    58952   ,
    57689   ,
    56452   ,
    55243   ,
    54059   ,
    52901   ,
    51767   ,
    50658   ,
    49572   ,
    48510   ,
    47471   ,
    46453   ,
    45458   ,
    44484   ,
    43531   ,
    42598   ,
    41685   ,
    40792   ,
    39918   ,
    39063   ,
    38225   ,
    37406   ,
    36605   ,
    35820   ,
    35053   ,
    34302   ,
    33567   ,
    32848   ,   /* -49.5 dB or 1/30444 sec */
    32144   ,
    31455   ,
    30781   ,
    30121   ,
    29476   ,
    28844   ,
    28226   ,
    27621   ,
    27029   ,
    26450   ,
    25884   ,
    25329   ,
    24786   ,
    24255   ,
    23735   ,
    23227   ,
    22729   ,
    22242   ,
    21765   ,
    21299   ,
    20843   ,
    20396   ,
    19959   ,
    19531   ,   /* -54 dB or 1/51200 sec */
};

static void ae_obj_reset()
{
    memset(&ae_obj, 0, sizeof(ae_obj_t));
    ae_obj.ae_info.luma_target = 50;
    ae_obj.ae_info.sys_gain = 0;
    ae_obj.ae_info.iso = INIT_AE_ISO;
    ae_obj.ae_info.expo_time = INIT_AE_EXPO_TIME;
    ae_obj.ae_speed = INIT_AE_SPEED;
    ae_obj.max_sysgain_step = GAIN_6_DB;
}

static void ae_stats_reset()
{
    if (NULL == ae_stats_info.ae_stats_data) {
        ae_stats_info.ae_stats_data = &ae_stats_data;
        if (NULL == ae_stats_info.ae_stats_data) {
            MSG("pvPortMalloc(AE Grid) error\r\n");
            return;
        }
    }

    memset(ae_stats_info.ae_stats_data, 0, AE_STATS_GRID_NUM*sizeof(dsp2_ae_sum_t));
    ae_stats_info.is_ae_stats_update = -1;
}

static int ae_stats_enable(aaa_stats_cfg_t *stats)
{
    dsp2_ae_stats_conf_t ae_stats_conf;

    ae_stats_conf.grid_num_x  = AE_STATS_GRID_NUM_X;
    ae_stats_conf.grid_num_y  = AE_STATS_GRID_NUM_Y;
    ae_stats_conf.img_width   = stats->act_win.width;
    ae_stats_conf.img_height  = stats->act_win.height;
    ae_stats_conf.grid_width  = even_division(stats->act_win.width, AE_STATS_GRID_NUM_X);
    ae_stats_conf.grid_height = even_division(stats->act_win.height, AE_STATS_GRID_NUM_Y);
    ae_stats_conf.roi_start_x = (ae_stats_conf.img_width \
        - AE_STATS_GRID_NUM_X*ae_stats_conf.grid_width)/2 ;
    ae_stats_conf.roi_start_y = (ae_stats_conf.img_height \
        - AE_STATS_GRID_NUM_Y*ae_stats_conf.grid_height)/2 ;
    ae_stats_conf.roi_width   = AE_STATS_GRID_NUM_X*ae_stats_conf.grid_width;
    ae_stats_conf.roi_height  = AE_STATS_GRID_NUM_Y*ae_stats_conf.grid_height;

    DSP2_Set_AE_Stats_Conf(&ae_stats_conf);
    DSP2_Set_AE_State(ENABLE);

    return 0;
}

static uint16_t ae_metering_tbl[AE_METERING_NUM][AE_STATS_GRID_NUM] =
{
    { // AE_METERING_AVERAGE
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    },
    { // AE_METERING_CENTER_WEIGHTED
        // 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
        // 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
        // 136, 136, 136, 614, 614, 614, 614, 614, 614, 136, 136, 136,
        // 136, 136, 136, 614, 614, 614, 614, 614, 614, 136, 136, 136,
        // 136, 136, 136, 614, 614, 614, 614, 614, 614, 136, 136, 136,
        // 136, 136, 136, 614, 614, 614, 614, 614, 614, 136, 136, 136,
        // 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
        // 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
        2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
        2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
        2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    },
    { // AE_METERING_SPOT
        0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,  1,  1,  0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,  1,  1,  0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0
    },
    { // AE_METERING_CUSTOM
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    }
};

//static uint8_t histo_weight_tbl[256]={
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//};

static int ae_luma_avg(void)
{
    int i;
    uint32_t luma, weighed_luma;
    uint32_t luma_sum = 0, meter_weight_sum = 0;
    //uint32_t histo_weight_sum = 0;
    uint8_t weight;
    AE_METERING m_mode = ae_obj.ae_info.ae_metering;
    //uint32_t luma_grid[AE_STATS_GRID_NUM];

    for (i = 0; i < AE_STATS_GRID_NUM; i++) {
        // DSP2_Get_AE_Sum(i, AE_GRID_DATA_Y, &luma);
        luma = ((dsp2_ae_sum_t*)(ae_stats_info.ae_stats_data))[i].y_sum;
        //luma_grid[i] = luma;
        weight = ae_metering_tbl[m_mode][i];
        weighed_luma = luma * weight;
        meter_weight_sum += weight;

        // weight = histo_weight_tbl[luma];
        // weighed_luma *= weight;
        // histo_weight_sum += weight;

        luma_sum += weighed_luma;
        //MSG("\t\t YSUM[%d]: value %d, total 0x%x\r\n", i, luma, luma_sum);
    }
#if 0
    MSG("==print ae grid==\r\n");
    for (int i = 0; i < 8; i++) {
        MSG("[%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d]\r\n", \
            luma_grid[12*i],  luma_grid[12*i+1],luma_grid[12*i+2],luma_grid[12*i+3],luma_grid[12*i+4],luma_grid[12*i+5],\
            luma_grid[12*i+6],luma_grid[12*i+7],luma_grid[12*i+8],luma_grid[12*i+9],luma_grid[12*i+10],luma_grid[12*i+11]);
    }
#endif
    //MSG("luma_sum %d, weight_sum%d, luma_sum/weight_sum is %d,\r\n",  luma_sum,meter_weight_sum,(int)luma_sum/meter_weight_sum);
    //return DIV_ROUND(DIV_ROUND(luma_sum * AE_STATS_GRID_NUM, meter_weight_sum), histo_weight_sum);
    return DIV_ROUND(luma_sum, meter_weight_sum);
}

static BL_GAIN_DB gen_sys_gain_by_expo_gain(BL_EXPO_TIME expo, BL_GAIN_DB gain)
{
    return -GAIN_DB_FLOAT_TO_INT(GAIN_X_TO_DB((float)EXPO_TIME_1_100_SEC/expo)) + gain;
}

static BL_GAIN_DB calc_max_sys_gain(BL_GAIN_DB ae_max_gain, BL_EXPO_TIME ae_max_expo)
{
    BL_GAIN_DB sensor_max_gain;

    sensor_max_gain = SENSOR_MAX_GAIN;

    if (sensor_max_gain > ae_max_gain)
        sensor_max_gain = ae_max_gain;

    MSG("sensor max gain %.4f dB\r\n", GAIN_DB_INT_TO_FLOAT(sensor_max_gain));

    if (ae_max_expo < EXPO_TIME_1_50_SEC) {
        return sensor_max_gain;
    }
    else if (ae_max_expo < EXPO_TIME_1_25_SEC) {
        return (sensor_max_gain + INT_TO_GAIN_DB(6));
    } else {
        return (sensor_max_gain + INT_TO_GAIN_DB(12));
    }
}

static BL_GAIN_DB calc_min_sys_gain(BL_EXPO_TIME ae_min_expo)
{
    return gen_sys_gain_by_expo_gain(ae_min_expo, GAIN_0_DB);
}

static void ae_set_FSM(AE_FSM fsm)
{
    MSG("AE FSM transfer from %d to %d\r\n", (int)ae_obj.ae_fsm, (int)fsm);
    ae_obj.ae_fsm = fsm;
}

static AE_FSM ae_get_FSM()
{
    return ae_obj.ae_fsm;
}

static void check_sys_gain(BL_GAIN_DB *sys_gain)
{
    if (*sys_gain > max_sys_gain) {
        *sys_gain = max_sys_gain;
        ae_obj.sys_gain_max_reached = 1;
        MSG("Max system gain reached!\r\n");
    } else {
        ae_obj.sys_gain_max_reached = 0;
    }

    if (*sys_gain < min_sys_gain) {
        *sys_gain = min_sys_gain;
        ae_obj.sys_gain_min_reached = 1;
        MSG("Min system gain reached!\r\n");
    } else {
        ae_obj.sys_gain_min_reached = 0;
    }
}

// should be open to user && use linear interplation
static void ae_update_speed_sysgain(int luma_target, int luma_avg)
{
    if (AE_FSM_BOOTING == ae_get_FSM()) {
        ae_obj.ae_speed = 3;
    }

    if (abs(luma_avg - luma_target) < 5 )  {
        ae_obj.ae_speed  = 2;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*2;
        return;
    }
    if (abs(luma_avg - luma_target) < 10) {
        ae_obj.ae_speed  = 2;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*4;
        return;
    }
    if (abs(luma_avg - luma_target) < 20) {
        ae_obj.ae_speed  = 2;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*8;
        return;
    }
    if (abs(luma_avg - luma_target) < 40) {
        ae_obj.ae_speed  = 2;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*16;
        return;
    }
    if (abs(luma_avg - luma_target) < 50) {
        ae_obj.ae_speed  = 3;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*32;
        return;
    }
    if (abs(luma_avg - luma_target) < 60) {
        ae_obj.ae_speed  = 3;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*64;
        return;
    }
    if (abs(luma_avg - luma_target) < 120) {
        ae_obj.ae_speed  = 4;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*64;
        return;
    }
    if (abs(luma_avg - luma_target) < 255) {
        ae_obj.ae_speed  = 5;
        ae_obj.max_sysgain_step = AE_SYSGAIN_STEP*64;
        return;
    }
}

static void calc_sys_gain(BL_GAIN_DB pre_sys_gain, int luma_target, BL_GAIN_DB *sys_gain)
{
    float luma_next;

    ae_update_speed_sysgain(luma_target, ae_obj.luma_avg);
    luma_next = (float)(ae_obj.ae_speed * luma_target + (16 - ae_obj.ae_speed) * ae_obj.luma_avg) / 16;
    *sys_gain = GAIN_DB_FLOAT_TO_INT(GAIN_X_TO_DB(luma_next/ae_obj.luma_avg)) + pre_sys_gain;
    MSG("luma_target %d, luma avg %d, speed %d, luma next %.1f, sys_gain %.4f dB, pre_sys_gain %.4f dB\r\n",
            luma_target,  ae_obj.luma_avg, ae_obj.ae_speed, luma_next
            , GAIN_DB_INT_TO_FLOAT(*sys_gain), GAIN_DB_INT_TO_FLOAT(pre_sys_gain));

    if (AE_FSM_BOOTING == ae_get_FSM()) {
        return;
    }

    int diff_sysgain = *sys_gain - ae_obj.ae_info.sys_gain;
    if (abs(diff_sysgain) > ae_obj.max_sysgain_step) {
        *sys_gain = ae_obj.ae_info.sys_gain + (abs(diff_sysgain)/diff_sysgain)*ae_obj.max_sysgain_step;
    }

    return;
}

static int calc_expo_and_gain(BL_GAIN_DB sys_gain, BL_EXPO_TIME *expo_time, BL_GAIN_DB *gain)
{
    int shutter_index = 0;

    if (sys_gain >= INT_TO_GAIN_DB(12)) {
        *expo_time = EXPO_TIME_1_25_SEC;
        *gain = sys_gain - INT_TO_GAIN_DB(12);
    } else if (sys_gain >= GAIN_6_DB) {
        *expo_time = EXPO_TIME_1_50_SEC;
        *gain = sys_gain - GAIN_6_DB;
    } else if (sys_gain >= 0){
        *expo_time = EXPO_TIME_1_100_SEC;
        *gain = sys_gain;
    } else {
        shutter_index = DIV_ROUND(-(sys_gain), shutter_table_step);
        CHECK_PARAM(shutter_index < sizeof(shutter_table_ns)/sizeof(shutter_table_ns[0]));
        *expo_time = shutter_table_ns[shutter_index];
        *gain = GAIN_0_DB;
    }

//    MSG("sys_gain %d, index %d, shutter %d\r\n", sys_gain, shutter_index, shutter_table_ns[shutter_index]);
    MSG("sys_gain %.4f dB, expo 1/%d sec, gain %.4f dB\r\n", GAIN_DB_INT_TO_FLOAT(sys_gain),
        EXPO_TIME_TO_INT(*expo_time), GAIN_DB_INT_TO_FLOAT(*gain));

    return 0;
}

static int calc_band_size(BL_GAIN_DB sys_gain)
{
    int band_size;

    /* calculate band size */
    if (sys_gain > -INT_TO_GAIN_DB(21))
        band_size = 3;      /* increase from 1 to 2, adding AE tolerence for SC1245 */
    else if (sys_gain > -INT_TO_GAIN_DB(25))
        band_size = 3;
    else if (sys_gain > -INT_TO_GAIN_DB(28))
        band_size = 4;
    else if (sys_gain > -INT_TO_GAIN_DB(31))
        band_size = 5;
    else if (sys_gain > -INT_TO_GAIN_DB(35))
        band_size = 6;
    else if (sys_gain > -INT_TO_GAIN_DB(37))
        band_size = 7;
    else if (sys_gain > -INT_TO_GAIN_DB(40))
        band_size = 9;
    else
        band_size = 9;

    return band_size;
}

static void calc_ae_result(ae_obj_t *ae_obj)
{
    BL_EXPO_TIME expo_time;
    BL_GAIN_DB gain;
    BL_GAIN_DB sys_gain;

    MSG("=== AE Loop ===\r\n");
    calc_sys_gain(ae_obj->ae_info.sys_gain, ae_obj->ae_info.luma_target, &sys_gain);
    check_sys_gain(&sys_gain);

    if (sys_gain != ae_obj->ae_info.sys_gain) {
        // int diff_sysgain = sys_gain - ae_obj->ae_info.sys_gain;
        // if (abs(diff_sysgain) > 256) {
            // ae_obj->ae_info.sys_gain = ae_obj->ae_info.sys_gain + (abs(diff_sysgain)/diff_sysgain)*256;
        // }
        // else {
            ae_obj->ae_info.sys_gain = sys_gain;
        // }
        ae_obj->ae_info.sys_gain_update = 1;

        calc_expo_and_gain(sys_gain, &expo_time, &gain);

        /* update AE result and inform other imgCtrl functions if necessary */
        if (expo_time != ae_obj->ae_info.expo_time) {
            ae_obj->ae_info.expo_time = expo_time;
            ae_obj->ae_info.expo_time_update = 1;
        }
        if (gain != ae_obj->ae_info.iso) {
            ae_obj->ae_info.iso = gain;
            ae_obj->ae_info.iso_update = 1;
        }
    }
}

#ifdef TEST_AE_LINEARITY
static void test_sys_gain(void)
{
    static BL_GAIN_DB sys_gain;
    BL_EXPO_TIME expo_time;
    BL_GAIN_DB gain;

//    sys_gain -= shutter_table_step;
    sys_gain += (GAIN_6_DB/16);
    if (sys_gain > max_sys_gain)
        sys_gain = 0;

    if (sys_gain < min_sys_gain)
        sys_gain = 0;

    calc_expo_and_gain(sys_gain, &expo_time, &gain);
    sensor_expo_time = expo_time;
    sensor_gain = gain;
}
#endif

#if 0
static void print_shadow_hightlight(void)
{
    int shadow_strength;
    int highlight_strength;

    DSP2_Get_Shadow_Stats(&shadow_strength);
    DSP2_Get_Highlight_Stats(&highlight_strength);
    MSG("shadow %d, highlight %d\r\n", shadow_strength, highlight_strength);
}
#endif

static void print_ae_value(int luma_avg, int luma_gap, int band_size, ae_obj_t *ae_obj)
{
    MSG("luma %d, gap %d, band %d\r\n", luma_avg, luma_gap, band_size);
}

static int ae_clear_info()
{
    ae_obj.ae_info.expo_time_update = 0;
    ae_obj.ae_info.iso_update = 0;
    ae_obj.ae_info.sys_gain_update = 0;

    return 0;
}

static bool is_ae_stats_update(void)
{
    return (0 == ae_stats_info.is_ae_stats_update);
}

static bool is_ae_skip_frame()
{
    if (ae_obj.ae_boot_index > ae_obj.ae_boot_skip_index) {
        return 0;
    }

    ae_obj.ae_boot_index++;

    if (ae_obj.ae_boot_index == ae_obj.ae_start_skip_index) {
        MSG("AE booting!\r\n");
        ae_set_FSM(AE_FSM_BOOTING);
        return 1;
    }

    if (ae_obj.ae_boot_index == ae_obj.ae_boot_skip_index) {
        return 1;
    }

    return 0;
}

void ae_update_stats(void)
{
    ae_stats_info.is_ae_stats_update = DSP2_Get_AE_Stats(AE_STATS_GRID_NUM, \
        (uint32_t*)(ae_stats_info.ae_stats_data));
}

int ae_get_mode(AE_MODE *mode)
{
    *mode = ae_obj.ae_info.ae_mode;
    return 0;
}

int ae_set_mode(AE_MODE mode)
{
    if (!is_param_valid(mode, AE_MODE_MIN, AE_MODE_MAX)) {
        MSG("ae_set_mode: invalid AE mode %d!\r\n", mode);
        return -1;
    }

    ae_obj.new_ae_mode = mode;
    ae_obj.ae_config_update |= AE_UPDATE_MODE;

    MSG("ae_set_mode: %d\r\n", mode);

    return 0;
}

int ae_get_metering_mode(AE_METERING *mode)
{
    *mode = ae_obj.ae_info.ae_metering;
    return 0;
}

int ae_set_metering_mode(AE_METERING mode)
{
    if (!is_param_valid(mode, AE_METERING_MIN, AE_METERING_NUM)) {
        MSG("ae_set_metering_mode: invalid AE metering mode %d!\r\n", mode);
        return -1;
    }

    ae_obj.new_ae_metering = mode;
    ae_obj.ae_config_update |= AE_UPDATE_METERING;

    MSG("ae_set_metering_mode: %d\r\n", mode);

    return 0;
}

/* Target value ranges from 0~255 */
int ae_set_luma_target(int target)
{
    if (target < 0 || target > 255) {
        MSG("ae_set_luma_target: invalid ae target value!\r\n");
        return -1;
    }

    ae_obj.ae_info.luma_target = target;
    ae_obj.ae_config_update |= AE_UPDATE_TARGET;

    MSG("ae_set_luma_target: %d\r\n", target);

    return 0;
}

/* Target value ranges from 0~255 */
int ae_get_luma_target(int *target)
{
    *target = ae_obj.ae_info.luma_target;

    return 0;
}

/* Speed value ranges from 0~10 */
int ae_set_speed(int speed)
{
    if (speed < 0 || speed > 16) {
        MSG("ae_set_speed: ae speed %d out of range!\r\n", speed);
        return -1;
    }

    ae_obj.ae_speed = speed;

    MSG("ae_set_speed: %d\r\n", ae_obj.ae_speed);

    return 0;
}

/* Luma value ranges from 0~255 */
int ae_get_luma(void)
{
    return ae_obj.luma_avg;
}

int ae_set_exposure_max(BL_EXPO_TIME max_expo)
{
    if (max_expo < SENSOR_MIN_EXPO_TIME || max_expo > SENSOR_MAX_EXPO_TIME) {
        MSG("ae_set_exposure_max: exposure value %d out of range!\r\n", max_expo);
        return -1;
    }

    /* TODO: temporarily shutter speed limit higher than 1/100 sec is not supported */
    if (max_expo < EXPO_TIME_1_100_SEC) {
        return -1;
    }

    ae_max_exposure = max_expo;

    max_sys_gain = calc_max_sys_gain(ae_max_gain, ae_max_exposure);

    return 0;
}

int ae_get_exposure_max(BL_EXPO_TIME *max_expo)
{
    *max_expo = ae_max_exposure;

    return 0;
}

int ae_set_exposure_min(BL_EXPO_TIME min_expo)
{
    if (min_expo < SENSOR_MIN_EXPO_TIME || min_expo > SENSOR_MAX_EXPO_TIME) {
        MSG("ae_set_exposure_min: exposure value %d out of range!\r\n", min_expo);
        return -1;
    }

    ae_min_exposure = min_expo;

    min_sys_gain = calc_min_sys_gain(ae_min_exposure);

    return 0;
}

int ae_get_exposure_min(BL_EXPO_TIME *min_expo)
{
    *min_expo = ae_min_exposure;

    return 0;
}

/* Gain value ranges from 0 ~ 72 */
int ae_set_gain_max(float gain_f)
{
    float sensor_max_gain_f = 0.0f;

    ae_get_sensor_gain_max(&sensor_max_gain_f);

     if (gain_f < 0 || gain_f > sensor_max_gain_f) {
        MSG("ae_set_gain_max: gain value %.4f out of range!\r\n", gain_f);
        return -1;
    }

    ae_max_gain = GAIN_DB_FLOAT_TO_INT(gain_f);

    max_sys_gain = calc_max_sys_gain(ae_max_gain, EXPO_TIME_1_25_SEC);

    ae_obj.force_ae_gain_update = 1;

    MSG("ae_set_gain_max: %.4f dB\r\n", gain_f);

    return 0;
}

int ae_get_gain_min(float *gain_f)
{
    *gain_f = GAIN_DB_INT_TO_FLOAT(ae_max_gain);

    return 0;
}

int ae_get_sensor_exposure_max(BL_EXPO_TIME *max_expo)
{
    return SENSOR_MAX_EXPO_TIME;
}

int ae_get_sensor_exposure_min(BL_EXPO_TIME *min_expo)
{
    return SENSOR_MIN_EXPO_TIME;
}

int ae_get_sensor_gain_max(float *max_gain_f)
{
    *max_gain_f = GAIN_DB_INT_TO_FLOAT(SENSOR_MAX_EXPO_TIME);
    return 0;
}

int ae_set_sensor_exposure(BL_EXPO_TIME expo_time)
{
    if (ae_obj.ae_info.ae_mode != AE_MODE_LOCK && ae_obj.ae_info.ae_mode != AE_MODE_DBG_VIRTUAL) {
        MSG("ae_set_sensor_exposure: failure, ae is not locked!\r\n");
        return -1;
    }

    ae_obj.new_expo = expo_time;
    ae_obj.ae_config_update |= AE_UPDATE_EXPO;

    return 0;
}

int ae_get_sensor_exposure(BL_EXPO_TIME *expo_time)
{
    if (ae_obj.ae_info.ae_mode == AE_MODE_DBG_VIRTUAL) {
        *expo_time = ae_obj.ae_info.expo_time;
        return 0;
    }

    *expo_time = sensor_expo_time;

    return 0;
}

/* Gain value ranges from 0 ~ 72 */
int ae_set_sensor_gain(float gain_f)
{
    if (ae_obj.ae_info.ae_mode != AE_MODE_LOCK && ae_obj.ae_info.ae_mode != AE_MODE_DBG_VIRTUAL) {
        MSG("ae_set_sensor_gain: failure, ae is not locked!\r\n");
        return -1;
    }

    ae_obj.new_gain = gain_f;
    ae_obj.ae_config_update |= AE_UPDATE_GAIN;

    return 0;
}

int ae_get_sensor_gain(float *gain_f)
{
    BL_GAIN_DB gain;

    if (ae_obj.ae_info.ae_mode == AE_MODE_DBG_VIRTUAL) {
        *gain_f= GAIN_DB_INT_TO_FLOAT(ae_obj.ae_info.iso);
        return 0;
    }

    gain = sensor_gain;

    *gain_f = GAIN_DB_INT_TO_FLOAT(gain);
    return 0;
}

int ae_get_info(ae_info_t **ae_info)
{
    *ae_info = &(ae_obj.ae_info);
    return 0;
}

void ae_force_refresh(void)
{
    ae_obj.force_ae_gain_update = 1;
}

int ae_init(void)
{
    ae_obj.ae_info.ae_mode = AE_MODE_AUTO;
    ae_clear_info();
    return 0;
}

int ae_config(ae_config_t *config, bool is_virtual_sensor)
{
    BL_EXPO_TIME sensor_min_expo_time;

    ae_obj_reset();
    ae_stats_reset();

    if (is_virtual_sensor) {
        ae_obj.ae_info.ae_mode = AE_MODE_DBG_VIRTUAL;
        ae_stats_enable(&(config->stats_cfg));
        ae_set_mode(AE_MODE_DBG_VIRTUAL);
        ae_set_speed(16);
        ae_obj.ae_state = AE_STATE_INITED;
        return 0;
    }

    sensor_min_expo_time = SENSOR_MIN_EXPO_TIME;

    if (sensor_min_expo_time < ae_min_exposure)
        sensor_min_expo_time = ae_min_exposure;

    max_sys_gain = calc_max_sys_gain(ae_max_gain, EXPO_TIME_1_25_SEC);
    min_sys_gain = calc_min_sys_gain(sensor_min_expo_time);

    MSG("sensor min expo time %d ns\r\n", sensor_min_expo_time);
    MSG("max sys gain %.2f dB\r\n", GAIN_DB_INT_TO_FLOAT(max_sys_gain));
    MSG("min sys gain %.2f dB\r\n", GAIN_DB_INT_TO_FLOAT(min_sys_gain));

    /* set starting point */
    // sensor_expo_time = INIT_AE_EXPO_TIME;
    // sensor_gain = INIT_AE_ISO;

    ae_stats_enable(&(config->stats_cfg));
    ae_obj.ae_boot_index = 0;
    ae_obj.ae_start_skip_index = IMG_START_SKIP_NUM;
    ae_obj.ae_boot_skip_index = IMG_START_SKIP_NUM+2;
    ae_obj.ae_info.sys_gain = gen_sys_gain_by_expo_gain(ae_obj.ae_info.expo_time, ae_obj.ae_info.iso);
    ae_set_FSM(AE_FSM_INITED);

    /* force update of gain to refresh IQ params, even if AE target is already met */
    if (ae_obj.ae_info.ae_mode == AE_MODE_AUTO) {
        ae_obj.force_ae_gain_update = 1;
    }
    ae_obj.ae_state = AE_STATE_INITED;

    return 0;
}

int ae_control(void)
{
    static int skip_calc_cnt = 0;

    int ae_calc_needed = 1;
    int luma_gap;
    int band_size;
    int ae_ctl_update = 0;

    if (ae_obj.ae_state == AE_STATE_IDLE) {
        MSG("AE can't run as AE is not initialized!\r\n");
        return -1;
    }

    ae_obj.luma_avg = ae_luma_avg();
    ae_clear_info();
    ae_update_stats();

    if (is_ae_skip_frame()) {
        return -1;
    }

    MSG("luma %d\r\n", ae_obj.luma_avg);

    /* Check if AE config is updated */
    if (ae_obj.ae_config_update) {

        if (ae_obj.ae_config_update & AE_UPDATE_MODE) {
            ae_obj.ae_info.ae_mode = ae_obj.new_ae_mode;
        }

        if (ae_obj.ae_config_update & AE_UPDATE_METERING) {
            ae_obj.ae_info.ae_metering = ae_obj.new_ae_metering;
            ae_ctl_update = 1;
        }

        if (ae_obj.ae_config_update & AE_UPDATE_EXPO) {
            ae_obj.ae_info.expo_time = ae_obj.new_expo;
            ae_obj.ae_info.expo_time_update = 1;
        }

        if (ae_obj.ae_config_update & AE_UPDATE_GAIN) {
            ae_obj.ae_info.iso = GAIN_DB_FLOAT_TO_INT(ae_obj.new_gain);
            ae_obj.ae_info.iso_update = 1;
        }

        if ((ae_obj.ae_config_update & AE_UPDATE_EXPO) || (ae_obj.ae_config_update & AE_UPDATE_GAIN)) {
            ae_obj.ae_info.sys_gain = gen_sys_gain_by_expo_gain(ae_obj.ae_info.expo_time, ae_obj.ae_info.iso);
        }

        ae_obj.ae_config_update = 0;
    }

    if (ae_obj.luma_avg == 0)
        ae_obj.luma_avg = 1;

#if 0   /* Expo time test */
    static int shutter_time = 100;
    MSG("luma %d\r\n", luma_avg);

    if (shutter_time < 25)
        shutter_time = 25;

    sensor_expo_time = SEC_TO_NS(1) / shutter_time;
    shutter_time --;
    return 0;
#endif

#ifdef TEST_AE_LINEARITY   /* System gain test */
    MSG("luma %d\r\n", ae_obj.luma_avg);
    test_sys_gain();
    return 0;
#endif

    if (ae_obj.ae_info.ae_mode == AE_MODE_LOCK || ae_obj.ae_info.ae_mode == AE_MODE_DBG_VIRTUAL) {
        return -1;
    }

    if (!is_ae_stats_update()) {
        return -1;
    }

    luma_gap = ae_obj.ae_info.luma_target - ae_obj.luma_avg;
    band_size = calc_band_size(ae_obj.ae_info.sys_gain);

    /* skip AE adjustment if the luma is very close to the target */
    if ((abs(luma_gap) <= band_size)) {
        ae_calc_needed = 0;
    }

    if (ae_calc_needed || ae_ctl_update) {
        if (AE_FSM_STABLE == ae_get_FSM()) {
            ae_set_FSM(AE_FSM_CONVERGENCE);
        }
        calc_ae_result(&ae_obj);
        print_ae_value(ae_obj.luma_avg, luma_gap, band_size, &ae_obj);
    }
    else {
        if (skip_calc_cnt++ > 50) {
            skip_calc_cnt = 0;
            print_ae_value(ae_obj.luma_avg, luma_gap, band_size, &ae_obj);
        }
        if (AE_FSM_STABLE != ae_get_FSM()) {
            print_ae_value(ae_obj.luma_avg, luma_gap, band_size, &ae_obj);
            ae_set_FSM(AE_FSM_STABLE);
        }
    }

    /* force update of gain to refresh IQ params, based on the current gain value */
    if (ae_obj.force_ae_gain_update) {
        ae_obj.ae_info.iso_update = 1;
        ae_obj.force_ae_gain_update = 0;  /* clear flag */
    }

    return 0;
}


