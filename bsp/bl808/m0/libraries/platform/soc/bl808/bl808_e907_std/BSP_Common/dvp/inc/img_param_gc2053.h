#include <stdint.h>

#if(IMAGE_SENSOR_USE == IMAGE_SENSOR_GC2053)
static const img_param_state_container_t state_tbl = {
    .state[DSP2_ADJ_AE]                = ENABLE,
    .state[DSP2_ADJ_AWB]               = ENABLE,
    .state[DSP2_ADJ_BLC]               = ENABLE,
    .state[DSP2_ADJ_DPC]               = DISABLE,
    .state[DSP2_ADJ_BNR]               = ENABLE,
    .state[DSP2_ADJ_LSC]               = DISABLE,
    .state[DSP2_ADJ_CCM]               = ENABLE,
    .state[DSP2_ADJ_GAMMA]             = ENABLE,
    .state[DSP2_ADJ_WDR]               = ENABLE,
    .state[DSP2_ADJ_SATURATION]        = ENABLE,
    .state[DSP2_ADJ_NR]                = ENABLE,
    .state[DSP2_ADJ_EE]                = ENABLE,
    .state[DSP2_ADJ_CS]                = ENABLE,
};

#if 1 // chenyi 1130
static const ae_target_container_t ae_target = {
    .header = {
        .module = DSP2_ADJ_AE_TARGET,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* ae target */
    .ae_target = {
        50,      // ISO_100_0DB
        50,      // ISO_200_6DB
        50,      // ISO_400_12DB
        50,      // ISO_800_18DB
        50,      // ISO_1600_24DB
        50,      // ISO_3200_30DB
        50,      // ISO_6400_36DB
        50,      // ISO_12800_42DB
        50,      // ISO_25600_48DB
        50,      // ISO_51200_54DB
    },
};

static const wb_info_t wb_gain_map[] = {
    /* r_gain, b_gain, color_temp */
    { {4213, 14106, }, 2300 },     // H - 2300K
    { {5002, 11834, }, 2856 },     // A - 2856K
    { {5700, 9630,  }, 4000 },     // TL84 - 4000K
    { {6740, 9918,  }, 4150 },     // CWF - 4150K
    { {7155, 7840,  }, 5000 },     // D50 - 5000K
    { {8100, 6560,  }, 6500 },     // D65 - 6500K
    { {9062, 5937,  }, 7500 },     // D75 - 7500K
};

static const wb_info_container_t wb_info = {
    .header = {
        .module = DSP2_ADJ_AWB_GAIN,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_wb_info = sizeof(wb_gain_map)/sizeof(wb_gain_map[0]),
    .wb_info = wb_gain_map,
};

static const wb_bais_t wb_bias_map[] = {
    /* r_gain, b_gain, sys_gain */
    { {3850, 3900, }, -36 },     //
    { {4096, 4096, }, -3 },     //
};

static const wb_bias_container_t wb_bias = {
    .header = {
        .module = DSP2_ADJ_AWB_BIAS,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_wb_bias = sizeof(wb_bias_map)/sizeof(wb_bias_map[0]),
    .wb_bias = wb_bias_map,
};

static const white_region_t white_region_map[] = {
    /* H 2300K */
    {
        {{  /* #1,   #2,      #3,       #4,       #5,       #6      */
            833,2401,912,2417,974,2294,1025,2141,923,2138,801,2234
        }},
        .weight             = 1,
        .color_temp         = 2300,
    },
    /* A 2856K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            962,2140,1062,2141,1115,1998,1051,1929,993,1932,969,1989
        }},
        .weight             = 1,
        .color_temp         = 2856,
    },
    /* TL84 4000K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1192,1984,1274,2023,1318,1947,1344,1833,1246,1802,1219,1861
        }},
        .weight             = 2,
        .color_temp         = 4000,
    },
    /* CWF 4150K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1328,1969,1390,1997,1405,1935,1433,1859,1370,1856,1349,1911
        }},
        .weight             = 1,
        .color_temp         = 4150,
    },
    /* D50 5000K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1264,1665,1544,1784,1634,1686,1720,1621,1490,1468,1398,1513
        }},
        .weight             = 2,
        .color_temp         = 5000,
    },
    /* D65 6500K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1431,1435,1720,1617,1763,1511,1738,1371,1673,1309,1562,1309
        }},
        .weight             = 8,
        .color_temp         = 6500,
    },
    /* D75 7500K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1627,1327,1709,1400,1838,1358,1834,1296,1688,1253,1640,1292
        }},
        .weight             = 4,
        .color_temp         = 7500,
    },
};

static const white_region_container_t white_region = {
    .header = {
        .module = DSP2_ADJ_AWB_REGION,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_white_region = sizeof(white_region_map)/sizeof(white_region_map[0]),
    .white_region = white_region_map,
};

static const black_lvl_corr_container_t black_lvl_corr = {
    .header = {
        .module = DSP2_ADJ_BLC,
        .policy = DSP2_POL_INIT,
        .table  = DSP2_TBL_INIT,
    },
    .black_lvl_corr = {
        64 << 2,
    },
};

static const defect_corr_container_t defect_corr = {
    .header = {
        .module = DSP2_ADJ_DPC,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* thres 1, thres 2 */
    .defect_corr = {
        {10,    20,    },     // ISO_100_0DB
        {10,    10,    },     // ISO_200_6DB
        {10,    5,     },     // ISO_400_12DB
        {10,    5,     },     // ISO_800_18DB
        {10,    5,     },     // ISO_1600_24DB
        {30,    20,    },     // ISO_3200_30DB
        {30,    20,    },     // ISO_6400_36DB
        {30,    20,    },     // ISO_12800_42DB
        {30,    20,    },     // ISO_25600_48DB
        {30,    20,    },     // ISO_51200_54DB
    },
};

static const bnr_fw_config_container_t bnr_fw_config = {
    .header = {
        .module = DSP2_ADJ_BNR,
        .policy = DSP2_POL_INIT,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    .bnr_fw_config = {
        .th_base_r  = 15,
        .th_base_g  = 15,
        .th_base_b  = 15,
        .th_slope_r = 20,
        .th_slope_g = 20,
        .th_slope_b = 20,
    },
};

static const lens_shade_corr_t lsc_map[] = {
    /* R: coefA, coefB, coefC, coefD, coefE, coefG */
    /* G: coefA, coefB, coefC, coefD, coefE, coefG */
    /* B: coefA, coefB, coefC, coefD, coefE, coefG */
    /* max_R, max_G, max_B */

    /* A light */
    {
        {{  -196,366,107,-203,231,-2 }},     // R
        {{  -169,320,112,-161,189,0 }},      // G
        {{  -174,311,114,-157,186,-1 }},     // B
        {  166,164,167 },
        2856,
    },
    /* D65 */
    {
        {{  -196,366,107,-203,231,-2 }},     // R
        {{  -169,320,112,-161,189,0 }},      // G
        {{  -174,311,114,-157,186,-1 }},     // B
        {  166,164,167 },
        6500,
    },
};

static const lens_shade_corr_container_t lens_shading_corr = {
    .header = {
        .module = DSP2_ADJ_LSC,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_lsc = sizeof(lsc_map)/sizeof(lsc_map[0]),
    .lens_shading_corr = lsc_map,
};

static const color_corr_t color_corr_map[] = {
#if 1
    { {{ 834, -204, -118, -177, 768, -78, -6, -642, 1161  }}, 2856 },      // A - 2856K
    { {{ 843, -245, -85, -179, 735, -44, -22, -392, 927  }}, 4000 },       // TL84 - 4000K
    { {{ 996, -420, -64, -264, 826, -50, -21, -364, 897  }}, 4150 },     // CWF - 4150K
    { {{ 856, -341, -3, -192, 790, -85, 5, -398, 905   }}, 5000 },       // D50 - 5000K
    { {{ 978, -420, -45, -249, 815, -54, -43, -315, 870  }}, 6500 },       // D65 - 6500K
#else   //xiaofang gamma
    { {{ 805,-23,-270,-253,928,-163,-221,-907,1640  }}, 2856 },      // A - 2856K
    { {{ 633,-194,73,-211,575,148,-139,-528,1179  }}, 4000 },        // TL84 - 4000K
    { {{ 862,-421,71,-244,686,70,-89,-469,1070  }}, 4150 },          // CWF - 4150K
    { {{ 853,-334,-7,-155,784,-118,-17,-562,1090   }}, 5000 },       // D50 - 5000K
    { {{ 727,-251,36,-179,754,-63,-82,-241,835  }}, 6500 },          // D65 - 6500K
#endif
};

static const color_corr_container_t color_corr = {
    .header = {
        .module = DSP2_ADJ_CCM,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_color_corr = sizeof(color_corr_map)/sizeof(color_corr_map[0]),
    .color_corr = color_corr_map,
};

static const gamma_corr_t gamma_corr_map[] = {
    {
        {{
        0, 58, 115, 172, 228, 284, 339, 393, 447, 500, 553, 605, 656, 707, 757, 807,
        856, 904, 952, 999, 1045, 1091, 1137, 1182, 1226, 1269, 1312, 1355, 1397, 1438, 1479, 1519,
        1559, 1598, 1636, 1674, 1711, 1748, 1784, 1820, 1855, 1889, 1923, 1957, 1990, 2022, 2054, 2085,
        2116, 2146, 2175, 2204, 2233, 2261, 2288, 2315, 2342, 2368, 2393, 2418, 2442, 2466, 2489, 2512,
        2534, 2556, 2577, 2598, 2618, 2638, 2657, 2676, 2695, 2713, 2730, 2748, 2765, 2781, 2797, 2813,
        2829, 2844, 2859, 2874, 2888, 2902, 2916, 2930, 2943, 2957, 2970, 2983, 2995, 3008, 3020, 3032,
        3044, 3056, 3068, 3080, 3092, 3103, 3115, 3126, 3137, 3149, 3160, 3171, 3181, 3192, 3203, 3213,
        3224, 3234, 3244, 3255, 3265, 3275, 3285, 3295, 3305, 3314, 3324, 3333, 3343, 3352, 3362, 3371,
        3380, 3390, 3399, 3408, 3417, 3426, 3435, 3443, 3452, 3461, 3469, 3478, 3486, 3494, 3503, 3511,
        3519, 3527, 3535, 3543, 3550, 3558, 3566, 3573, 3580, 3588, 3595, 3602, 3609, 3616, 3623, 3629,
        3636, 3642, 3649, 3655, 3661, 3667, 3673, 3679, 3685, 3691, 3696, 3702, 3708, 3713, 3719, 3724,
        3729, 3735, 3740, 3745, 3750, 3756, 3761, 3766, 3771, 3776, 3781, 3786, 3791, 3796, 3801, 3806,
        3811, 3816, 3821, 3827, 3832, 3837, 3842, 3847, 3852, 3857, 3862, 3867, 3872, 3877, 3882, 3887,
        3892, 3897, 3902, 3907, 3912, 3916, 3921, 3926, 3931, 3936, 3940, 3945, 3950, 3954, 3959, 3963,
        3968, 3972, 3977, 3981, 3986, 3990, 3994, 3998, 4002, 4006, 4010, 4014, 4018, 4022, 4026, 4030,
        4033, 4037, 4040, 4044, 4047, 4051, 4054, 4057, 4060, 4063, 4066, 4069, 4072, 4074, 4077, 4095,
        }},
        -3,
    },
    {
        {{
        0, 58, 115, 172, 228, 284, 339, 393, 447, 500, 553, 605, 656, 707, 757, 807,
        856, 904, 952, 999, 1045, 1091, 1137, 1182, 1226, 1269, 1312, 1355, 1397, 1438, 1479, 1519,
        1559, 1598, 1636, 1674, 1711, 1748, 1784, 1820, 1855, 1889, 1923, 1957, 1990, 2022, 2054, 2085,
        2116, 2146, 2175, 2204, 2233, 2261, 2288, 2315, 2342, 2368, 2393, 2418, 2442, 2466, 2489, 2512,
        2534, 2556, 2577, 2598, 2618, 2638, 2657, 2676, 2695, 2713, 2730, 2748, 2765, 2781, 2797, 2813,
        2829, 2844, 2859, 2874, 2888, 2902, 2916, 2930, 2943, 2957, 2970, 2983, 2995, 3008, 3020, 3032,
        3044, 3056, 3068, 3080, 3092, 3103, 3115, 3126, 3137, 3149, 3160, 3171, 3181, 3192, 3203, 3213,
        3224, 3234, 3244, 3255, 3265, 3275, 3285, 3295, 3305, 3314, 3324, 3333, 3343, 3352, 3362, 3371,
        3380, 3390, 3399, 3408, 3417, 3426, 3435, 3443, 3452, 3461, 3469, 3478, 3486, 3494, 3503, 3511,
        3519, 3527, 3535, 3543, 3550, 3558, 3566, 3573, 3580, 3588, 3595, 3602, 3609, 3616, 3623, 3629,
        3636, 3642, 3649, 3655, 3661, 3667, 3673, 3679, 3685, 3691, 3696, 3702, 3708, 3713, 3719, 3724,
        3729, 3735, 3740, 3745, 3750, 3756, 3761, 3766, 3771, 3776, 3781, 3786, 3791, 3796, 3801, 3806,
        3811, 3816, 3821, 3827, 3832, 3837, 3842, 3847, 3852, 3857, 3862, 3867, 3872, 3877, 3882, 3887,
        3892, 3897, 3902, 3907, 3912, 3916, 3921, 3926, 3931, 3936, 3940, 3945, 3950, 3954, 3959, 3963,
        3968, 3972, 3977, 3981, 3986, 3990, 3994, 3998, 4002, 4006, 4010, 4014, 4018, 4022, 4026, 4030,
        4033, 4037, 4040, 4044, 4047, 4051, 4054, 4057, 4060, 4063, 4066, 4069, 4072, 4074, 4077, 4095,
        }},
        6,
    },
};


static const gamma_corr_container_t gamma_corr = {
    .header = {
        .module = DSP2_ADJ_GAMMA,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_EV,
    },
    .num_gamma_corr = sizeof(gamma_corr_map)/sizeof(gamma_corr_map[0]),
    .gamma_corr = gamma_corr_map,
};

static const wdr_fw_config_t wdr_fw_config_map[] = {
    /*cs_weight,cs_gain_thresh,curve_weight,enh_weight,enh_c_gain_extra_slope,sys_gain_db;*/
        {{8,          1,             16,         16,        48},                     -12},
        {{8,          1,             4,          4,         48},                     -6},
        {{8,          1,             0,          0,         48},                     -3},
};

static const wdr_fw_config_container_t wdr_fw_config = {
    .header = {
        .module = DSP2_ADJ_WDR,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_EV,
    },
    .num_wdr_fw_config = sizeof(wdr_fw_config_map)/sizeof(wdr_fw_config_map[0]),
    .wdr_fw_config = wdr_fw_config_map
};

static const saturation_container_t saturation = {
    .header = {
        .module = DSP2_ADJ_SATURATION,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* saturation */
    .saturation = {
        { 128,  },    // ISO_100_0DB
        { 128,  },    // ISO_200_6DB
        { 128,  },    // ISO_400_12DB
        { 100,  },    // ISO_800_18DB
        { 90,   },    // ISO_1600_24DB
        { 90,   },    // ISO_3200_30DB
        { 90,   },    // ISO_6400_36DB
        { 80,   },    // ISO_12800_42DB
        { 80,   },    // ISO_25600_48DB
        { 80,   },    // ISO_51200_54DB
    },
};

static const noise_reduct_container_t noise_reduction = {
    .header = {
        .module = DSP2_ADJ_NR,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* noise_lvl */
    {
        { 2,    },    // ISO_100_0DB
        { 6,    },    // ISO_200_6DB
        { 10,   },    // ISO_400_12DB
        { 16,   },    // ISO_800_18DB
        { 24,   },    // ISO_1600_24DB
        { 32,   },    // ISO_3200_30DB
        { 48,   },    // ISO_6400_36DB
        { 63,   },    // ISO_12800_42DB
        { 63,   },    // ISO_25600_48DB
        { 63,   },    // ISO_51200_54DB
    },
    .filt_str_2d = 2,  /* str_2d */
    .filt_str_3d = 4,  /* str_3d */
};

static const edge_enhance_container_t edge_enhance = {
    .header = {
        .module = DSP2_ADJ_EE,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* posStr, negStr, posOvrStr, negOvrStr, nrStr, dirThr, noDirThr, flatThr, txtThr, edgeThr */
    .edgeEnhance = {
        { 80,   80,    127,      127,       0,      60,     90,      80,      300,      12000,},    // ISO_100_0DB
        { 80,   80,    127,      127,       0,      60,     90,      80,      300,      12000,},    // ISO_200_6DB
        { 60,   60,    127,      127,       0,      60,     90,      80,      300,      12000,},    // ISO_400_12DB
        { 40,   40,    127,      127,       64,     60,     90,      80,      300,      12000,},    // ISO_800_18DB
        { 20,   20,    127,      127,       255,    60,     90,      80,      300,      12000,},    // ISO_1600_24DB
        { 20,   20,    127,      127,       255,    60,     90,      80,      300,      12000,},    // ISO_3200_30DB
        { 20,   20,    127,      127,       255,    60,     90,      80,      300,      12000,},    // ISO_6400_36DB
        { 20,   20,    127,      127,       255,    60,     90,      80,      300,      12000,},    // ISO_12800_42DB
        { 20,   20,    127,      127,       255,    60,     90,      80,      300,      12000,},    // ISO_25600_48DB
        { 20,   20,    127,      127,       255,    60,     90,      80,      300,      12000,},    // ISO_51200_54DB
},
    /* luma weight table */
    .lumaWgtTbl = {{
        128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
        128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    }},
};

static const chroma_suppress_container_t chroma_suppress = {
    .header = {
        .module = DSP2_ADJ_CS,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    .csCfg = {
        {                                          // ISO_100_0DB
            8,  1,
        },
        {                                          // ISO_200_6DB
            8,  2,
        },
        {                                          // ISO_400_12DB
            8,  3,
        },
        {                                          // ISO_800_18DB
            8,  4,
        },
        {                                          // ISO_1600_24DB
            8,  5,
        },
        {                                          // ISO_3200_30DB
            8,  6,
        },
        {                                          // ISO_6400_36DB
            8,  7,
        },
        {                                          // ISO_12800_42DB
            8,  8,
        },
        {                                          // ISO_51200_54DB
            8,  8,
        },
    },
};

#else // GC Board
static const ae_target_container_t ae_target = {
    .header = {
        .module = DSP2_ADJ_AE_TARGET,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* ae target */
    .ae_target = {
        50,      // ISO_100_0DB
        50,      // ISO_200_6DB
        50,      // ISO_400_12DB
        50,      // ISO_800_18DB
        50,      // ISO_1600_24DB
        50,      // ISO_3200_30DB
        50,      // ISO_6400_36DB
        50,      // ISO_12800_42DB
        50,      // ISO_25600_48DB
        50,      // ISO_51200_54DB
    },
};

static const wb_info_t wb_gain_map[] = {
    /* r_gain, b_gain, color_temp */
    { {4110, 14380, }, 2300 },     // H - 2300K
    { {4900, 12020, }, 2856 },     // A - 2856K
    { {5790, 10380, }, 4000 },     // TL84 - 4000K
    { {6720, 10340, }, 4150 },     // CWF - 4150K
    { {6890, 7960,  }, 5000 },     // D50 - 5000K
    { {8050, 6482,  }, 6500 },     // D65 - 6500K
    { {8840, 6128,  }, 7500 },     // D75 - 7500K
};

static const wb_info_container_t wb_info = {
    .header = {
        .module = DSP2_ADJ_AWB_GAIN,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_wb_info = sizeof(wb_gain_map)/sizeof(wb_gain_map[0]),
    .wb_info = wb_gain_map,
};

static const wb_bais_t wb_bias_map[] = {
    /* r_gain, b_gain, sys_gain */
    { {3850, 3900, }, -36 },     //
    { {4096, 4096, }, -3 },     //
};

static const wb_bias_container_t wb_bias = {
    .header = {
        .module = DSP2_ADJ_AWB_BIAS,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_wb_bias = sizeof(wb_bias_map)/sizeof(wb_bias_map[0]),
    .wb_bias = wb_bias_map,
};

static const white_region_t white_region_map[] = {
    /* H 2300K */
    {
        {{  /* #1,   #2,      #3,       #4,       #5,       #6      */
            833,2401,912,2417,974,2294,1025,2141,923,2138,801,2234
        }},
        .weight             = 1,
        .color_temp         = 2300,
    },
    /* A 2856K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            962,2140,1062,2141,1115,1998,1051,1929,993,1932,969,1989
        }},
        .weight             = 1,
        .color_temp         = 2856,
    },
    /* TL84 4000K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1192,1984,1274,2023,1318,1947,1344,1833,1246,1802,1219,1861
        }},
        .weight             = 2,
        .color_temp         = 4000,
    },
    /* CWF 4150K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1328,1969,1390,1997,1405,1935,1433,1859,1370,1856,1349,1911
        }},
        .weight             = 1,
        .color_temp         = 4150,
    },
    /* D50 5000K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1264,1665,1544,1784,1634,1686,1720,1621,1490,1468,1398,1513
        }},
        .weight             = 2,
        .color_temp         = 5000,
    },
    /* D65 6500K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1431,1435,1720,1617,1763,1511,1738,1371,1673,1309,1562,1309
        }},
        .weight             = 8,
        .color_temp         = 6500,
    },
    /* D75 7500K */
    {
        {{   /* #1,   #2,      #3,       #4,       #5,       #6      */
            1627,1327,1709,1400,1838,1358,1834,1296,1688,1253,1640,1292
        }},
        .weight             = 4,
        .color_temp         = 7500,
    },
};

static const white_region_container_t white_region = {
    .header = {
        .module = DSP2_ADJ_AWB_REGION,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_white_region = sizeof(white_region_map)/sizeof(white_region_map[0]),
    .white_region = white_region_map,
};

static const black_lvl_corr_container_t black_lvl_corr = {
    .header = {
        .module = DSP2_ADJ_BLC,
        .policy = DSP2_POL_INIT,
        .table  = DSP2_TBL_INIT,
    },
    .black_lvl_corr = {
        64 << 2,
    },
};

static const defect_corr_container_t defect_corr = {
    .header = {
        .module = DSP2_ADJ_DPC,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* thres 1, thres 2 */
    .defect_corr = {
        {10,    20,    },     // ISO_100_0DB
        {10,    10,    },     // ISO_200_6DB
        {10,    5,     },     // ISO_400_12DB
        {10,    5,     },     // ISO_800_18DB
        {10,    5,     },     // ISO_1600_24DB
        {30,    20,    },     // ISO_3200_30DB
        {30,    20,    },     // ISO_6400_36DB
        {30,    20,    },     // ISO_12800_42DB
        {30,    20,    },     // ISO_25600_48DB
        {30,    20,    },     // ISO_51200_54DB
    },
};

static const bnr_fw_config_container_t bnr_fw_config = {
    .header = {
        .module = DSP2_ADJ_BNR,
        .policy = DSP2_POL_INIT,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    .bnr_fw_config = {
        .th_base_r  = 28,
        .th_base_g  = 28,
        .th_base_b  = 28,
        .th_slope_r = 32,
        .th_slope_g = 32,
        .th_slope_b = 32,
    },
};

static const lens_shade_corr_t lsc_map[] = {
    /* R: coefA, coefB, coefC, coefD, coefE, coefG */
    /* G: coefA, coefB, coefC, coefD, coefE, coefG */
    /* B: coefA, coefB, coefC, coefD, coefE, coefG */
    /* max_R, max_G, max_B */

    /* A light */
    {
        {{  -196,366,107,-203,231,-2 }},     // R
        {{  -169,320,112,-161,189,0 }},      // G
        {{  -174,311,114,-157,186,-1 }},     // B
        {  166,164,167 },
        2856,
    },
    /* D65 */
    {
        {{  -196,366,107,-203,231,-2 }},     // R
        {{  -169,320,112,-161,189,0 }},      // G
        {{  -174,311,114,-157,186,-1 }},     // B
        {  166,164,167 },
        6500,
    },
};

static const lens_shade_corr_container_t lens_shading_corr = {
    .header = {
        .module = DSP2_ADJ_LSC,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_lsc = sizeof(lsc_map)/sizeof(lsc_map[0]),
    .lens_shading_corr = lsc_map,
};


static const color_corr_t color_corr_map[] = {
#if 1
    { {{ 778,165,-431,-320,1090,-258,-310,-832,1654  }}, 2856 },      // A - 2856K
    { {{ 799,-163,-125,-251,790,-27,-136,-616,1265  }}, 4000 },       // TL84 - 4000K
    { {{ 1186,-487,-187,-261,900,-127,-108,-560,1180  }}, 4150 },     // CWF - 4150K
    { {{ 881,-275,-94,-192,869,-165,-25,-525,1062   }}, 5000 },       // D50 - 5000K
    { {{ 915,-209,-194,-212,1012,-288,-58,-397,966  }}, 6500 },       // D65 - 6500K
#else   //xiaofang gamma
    { {{ 805,-23,-270,-253,928,-163,-221,-907,1640  }}, 2856 },      // A - 2856K
    { {{ 633,-194,73,-211,575,148,-139,-528,1179  }}, 4000 },        // TL84 - 4000K
    { {{ 862,-421,71,-244,686,70,-89,-469,1070  }}, 4150 },          // CWF - 4150K
    { {{ 853,-334,-7,-155,784,-118,-17,-562,1090   }}, 5000 },       // D50 - 5000K
    { {{ 727,-251,36,-179,754,-63,-82,-241,835  }}, 6500 },          // D65 - 6500K
#endif
};

static const color_corr_container_t color_corr = {
    .header = {
        .module = DSP2_ADJ_CCM,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_COLOR_TMPER,
    },
    .num_color_corr = sizeof(color_corr_map)/sizeof(color_corr_map[0]),
    .color_corr = color_corr_map,
};

static const gamma_corr_t gamma_corr_map[] = {
    {
        {{
            0, 74, 146, 217, 286, 352, 417, 481, 542, 602, 660, 717, 771, 825, 876, 926,
            975, 1022, 1068, 1112, 1155, 1197, 1237, 1276, 1314, 1351, 1386, 1420, 1454, 1486, 1517, 1547,
            1576, 1604, 1631, 1657, 1682, 1707, 1731, 1754, 1776, 1798, 1818, 1839, 1858, 1877, 1896, 1914,
            1931, 1948, 1965, 1981, 1997, 2013, 2028, 2043, 2058, 2072, 2087, 2101, 2115, 2129, 2143, 2158,
            2172, 2186, 2200, 2214, 2229, 2243, 2257, 2271, 2286, 2300, 2314, 2329, 2343, 2357, 2372, 2386,
            2400, 2414, 2428, 2443, 2457, 2471, 2484, 2498, 2512, 2526, 2539, 2553, 2566, 2580, 2593, 2606,
            2619, 2632, 2644, 2657, 2670, 2682, 2694, 2707, 2719, 2731, 2743, 2754, 2766, 2778, 2789, 2801,
            2812, 2824, 2835, 2846, 2857, 2868, 2880, 2890, 2901, 2912, 2923, 2934, 2945, 2955, 2966, 2977,
            2987, 2998, 3008, 3019, 3029, 3040, 3050, 3060, 3071, 3081, 3091, 3101, 3112, 3122, 3132, 3142,
            3152, 3162, 3172, 3182, 3192, 3202, 3212, 3222, 3232, 3241, 3251, 3261, 3270, 3280, 3290, 3299,
            3309, 3318, 3328, 3337, 3346, 3356, 3365, 3374, 3383, 3393, 3402, 3411, 3420, 3429, 3438, 3447,
            3456, 3465, 3474, 3483, 3492, 3501, 3509, 3518, 3527, 3536, 3544, 3553, 3562, 3570, 3579, 3587,
            3596, 3605, 3613, 3622, 3630, 3638, 3647, 3655, 3664, 3672, 3680, 3689, 3697, 3705, 3713, 3722,
            3730, 3738, 3746, 3754, 3763, 3771, 3779, 3787, 3795, 3803, 3811, 3819, 3827, 3835, 3843, 3851,
            3858, 3866, 3874, 3882, 3890, 3898, 3905, 3913, 3921, 3929, 3936, 3944, 3952, 3959, 3967, 3975,
            3982, 3990, 3997, 4005, 4013, 4020, 4028, 4035, 4043, 4050, 4057, 4065, 4072, 4080, 4087, 4095
        }},
        -3,
    },
    {
        {{
            0, 74, 146, 217, 286, 352, 417, 481, 542, 602, 660, 717, 771, 825, 876, 926,
            975, 1022, 1068, 1112, 1155, 1197, 1237, 1276, 1314, 1351, 1386, 1420, 1454, 1486, 1517, 1547,
            1576, 1604, 1631, 1657, 1682, 1707, 1731, 1754, 1776, 1798, 1818, 1839, 1858, 1877, 1896, 1914,
            1931, 1948, 1965, 1981, 1997, 2013, 2028, 2043, 2058, 2072, 2087, 2101, 2115, 2129, 2143, 2158,
            2172, 2186, 2200, 2214, 2229, 2243, 2257, 2271, 2286, 2300, 2314, 2329, 2343, 2357, 2372, 2386,
            2400, 2414, 2428, 2443, 2457, 2471, 2484, 2498, 2512, 2526, 2539, 2553, 2566, 2580, 2593, 2606,
            2619, 2632, 2644, 2657, 2670, 2682, 2694, 2707, 2719, 2731, 2743, 2754, 2766, 2778, 2789, 2801,
            2812, 2824, 2835, 2846, 2857, 2868, 2880, 2890, 2901, 2912, 2923, 2934, 2945, 2955, 2966, 2977,
            2987, 2998, 3008, 3019, 3029, 3040, 3050, 3060, 3071, 3081, 3091, 3101, 3112, 3122, 3132, 3142,
            3152, 3162, 3172, 3182, 3192, 3202, 3212, 3222, 3232, 3241, 3251, 3261, 3270, 3280, 3290, 3299,
            3309, 3318, 3328, 3337, 3346, 3356, 3365, 3374, 3383, 3393, 3402, 3411, 3420, 3429, 3438, 3447,
            3456, 3465, 3474, 3483, 3492, 3501, 3509, 3518, 3527, 3536, 3544, 3553, 3562, 3570, 3579, 3587,
            3596, 3605, 3613, 3622, 3630, 3638, 3647, 3655, 3664, 3672, 3680, 3689, 3697, 3705, 3713, 3722,
            3730, 3738, 3746, 3754, 3763, 3771, 3779, 3787, 3795, 3803, 3811, 3819, 3827, 3835, 3843, 3851,
            3858, 3866, 3874, 3882, 3890, 3898, 3905, 3913, 3921, 3929, 3936, 3944, 3952, 3959, 3967, 3975,
            3982, 3990, 3997, 4005, 4013, 4020, 4028, 4035, 4043, 4050, 4057, 4065, 4072, 4080, 4087, 4095

        }},
        6,
    },
};

static const gamma_corr_container_t gamma_corr = {
    .header = {
        .module = DSP2_ADJ_GAMMA,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_EV,
    },
    .num_gamma_corr = sizeof(gamma_corr_map)/sizeof(gamma_corr_map[0]),
    .gamma_corr = gamma_corr_map,
};

static const wdr_fw_config_t wdr_fw_config_map[] = {
    /*cs_weight,cs_gain_thresh,curve_weight,enh_weight,enh_c_gain_extra_slope,sys_gain_db;*/
        {{8,          1,             16,         16,        48},                     -12},
        {{8,          1,             4,          4,         48},                     -6},
        {{8,          1,             0,          0,         48},                     -3},
};

static const wdr_fw_config_container_t wdr_fw_config = {
    .header = {
        .module = DSP2_ADJ_WDR,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_CUSTOM_EV,
    },
    .num_wdr_fw_config = sizeof(wdr_fw_config_map)/sizeof(wdr_fw_config_map[0]),
    .wdr_fw_config = wdr_fw_config_map
};

static const saturation_container_t saturation = {
    .header = {
        .module = DSP2_ADJ_SATURATION,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* saturation */
    .saturation = {
        { 128,  },    // ISO_100_0DB
        { 128,  },    // ISO_200_6DB
        { 128,  },    // ISO_400_12DB
        { 100,  },    // ISO_800_18DB
        { 90,   },    // ISO_1600_24DB
        { 90,   },    // ISO_3200_30DB
        { 90,   },    // ISO_6400_36DB
        { 80,   },    // ISO_12800_42DB
        { 80,   },    // ISO_25600_48DB
        { 80,   },    // ISO_51200_54DB
    },
};

static const noise_reduct_container_t noise_reduction = {
    .header = {
        .module = DSP2_ADJ_NR,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* noise_lvl */
    {
        { 2,    },    // ISO_100_0DB
        { 6,    },    // ISO_200_6DB
        { 10,   },    // ISO_400_12DB
        { 16,   },    // ISO_800_18DB
        { 24,   },    // ISO_1600_24DB
        { 32,   },    // ISO_3200_30DB
        { 48,   },    // ISO_6400_36DB
        { 63,   },    // ISO_12800_42DB
        { 63,   },    // ISO_25600_48DB
        { 63,   },    // ISO_51200_54DB
    },
    .filt_str_2d = 4,  /* str_2d */
    .filt_str_3d = 2,  /* str_3d */
};

static const edge_enhance_container_t edge_enhance = {
    .header = {
        .module = DSP2_ADJ_EE,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    /* posStr, negStr, posOvrStr, negOvrStr, nrStr, dirThr, noDirThr, flatThr, txtThr, edgeThr */
    .edgeEnhance = {
        { 80,   80,    127,      127,       0,      60,     90,      126,      127,      12000,},    // ISO_100_0DB
        { 80,   80,    127,      127,       0,      60,     90,      126,      127,      12000,},    // ISO_200_6DB
        { 60,   60,    127,      127,       0,      60,     90,      126,      127,      12000,},    // ISO_400_12DB
        { 40,   40,    127,      127,       64,     60,     90,      126,      127,      12000,},    // ISO_800_18DB
        { 20,   20,    127,      127,       255,    60,     90,      126,      127,      12000,},    // ISO_1600_24DB
        { 20,   20,    127,      127,       255,    60,     90,      126,      127,      12000,},    // ISO_3200_30DB
        { 20,   20,    127,      127,       255,    60,     90,      126,      127,      12000,},    // ISO_6400_36DB
        { 20,   20,    127,      127,       255,    60,     90,      126,      127,      12000,},    // ISO_12800_42DB
        { 20,   20,    127,      127,       255,    60,     90,      126,      127,      12000,},    // ISO_25600_48DB
        { 20,   20,    127,      127,       255,    60,     90,      126,      127,      12000,},    // ISO_51200_54DB
    },
    /* luma weight table */
    .lumaWgtTbl = {{
        128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
        128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    }},
};

static const chroma_suppress_container_t chroma_suppress = {
    .header = {
        .module = DSP2_ADJ_CS,
        .policy = DSP2_POL_INTERPL,
        .table  = DSP2_TBL_AUTO_ISO,
    },
    .csCfg = {
        {                                          // ISO_100_0DB
            8,  1,
        },
        {                                          // ISO_200_6DB
            8,  2,
        },
        {                                          // ISO_400_12DB
            8,  3,
        },
        {                                          // ISO_800_18DB
            8,  4,
        },
        {                                          // ISO_1600_24DB
            8,  5,
        },
        {                                          // ISO_3200_30DB
            8,  6,
        },
        {                                          // ISO_6400_36DB
            8,  7,
        },
        {                                          // ISO_12800_42DB
            8,  8,
        },
        {                                          // ISO_51200_54DB
            8,  8,
        },
    },
};

#endif
#endif
