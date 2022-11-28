#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <rtthread.h>
#include <hal_mem.h>
#include <log.h>
#include <video/sunxi_display2.h>
#include "disp_layer_cfg.h"
#include "disp_mem.h"

#define FILE_PATH                      "/mnt/F/FourPeople_1280x720_30.bin"     /*  "/mnt/E/vidyo4_1280x720_30.bin" ok*/
#define WIDTH                                 1280
#define HEIGHT                                720
#define CROP_X 0LL
#define CROP_Y 0LL
#define CROP_W 1280LL
#define CROP_H 720LL
#define SCREEN_W 800
#define SCREEN_H 480
#define ZORDER 4

#define FILE_SIZE                                      489600
#define LAYER_ID  0 //must layer 0  and other layer will be used when using lbc input
#define CHANNEL_ID  0  //must channel 0

#define LBC_IS_LOSSY                                1
//#define LBC_PITCH                                  12312
#define LBC_RC_EN                                   0
//#define LBC_SEG_BIT                              123

int msleep(unsigned int msecs);
extern int disp_ioctl(int cmd, void *arg);
extern int disp_release(void);
extern int disp_open(void);

void cal(u32 *seg_tar_bits_out, u32 *seg_line_tar_bits_out, u32 seg_rc_en)
{
    u32 seg_width = 16, seg_height = 4;
    u32 bit_depth = 8;
    u32 enc_c_ratio = 333;
    u32 cmp_ratio = 400;
    u32 ALIGN = 128;
    u32 frm_width = WIDTH;
    u32 seg_tar_bits = 0, dec_segline_tar_bits = 0;

    seg_tar_bits = ((seg_width * seg_height * bit_depth * cmp_ratio * 3 / 2000) / ALIGN) * ALIGN;
    if (seg_rc_en == 0)
    {
        dec_segline_tar_bits = ((frm_width + seg_width - 1) / seg_width) * seg_tar_bits;
    }
    else if (seg_rc_en == 1)
    {
        dec_segline_tar_bits = ((frm_width + seg_width - 1) / seg_width * seg_width * seg_height * bit_depth * cmp_ratio * 3 / 2000 + ALIGN - 1) / ALIGN * ALIGN;
    }

    *seg_tar_bits_out = seg_tar_bits/8;
    *seg_line_tar_bits_out = dec_segline_tar_bits/8;
    printf("seg_bit:%d pitch=%d\n",seg_tar_bits/8,dec_segline_tar_bits/8);
}

int lbc_test(int argc, char **argv)
{
    unsigned long arg[6];
    int id, width, height, ret, sw, sh, fb_width, fb_height, i, n;
    struct test_layer_cfg test_config;
    struct test_layer_cfg *test_cfg;
    test_cfg = &test_config;
    u32 pitch,seg_bit;

    cal(&seg_bit,&pitch, LBC_RC_EN);
    memset(test_cfg, 0, sizeof(struct test_layer_cfg));


    printf("request mem_id 0\n");
    disp_open();
    disp_mem(0, WIDTH, HEIGHT, 0, FILE_PATH);
    test_cfg->mem_id = 0;
    test_cfg->screen_id = 0;


    test_cfg->layer_cfg.info.fb.crop.x = CROP_X << 32;
    test_cfg->layer_cfg.info.fb.crop.y = CROP_Y << 32;
    test_cfg->layer_cfg.info.fb.crop.width = CROP_W << 32;
    test_cfg->layer_cfg.info.fb.crop.height = CROP_H << 32;


    test_cfg->layer_cfg.info.fb.size[0].width = WIDTH;
    test_cfg->layer_cfg.info.fb.size[0].height = HEIGHT;
    test_cfg->layer_cfg.info.fb.size[1].width = WIDTH/2;
    test_cfg->layer_cfg.info.fb.size[1].height = HEIGHT/2;
    test_cfg->layer_cfg.info.fb.size[2].width = WIDTH/2;
    test_cfg->layer_cfg.info.fb.size[2].height = HEIGHT/2;
    test_cfg->layer_cfg.enable = 1;


    test_cfg->layer_cfg.info.screen_win.x = 0;
    test_cfg->layer_cfg.info.screen_win.y = 0;
    test_cfg->layer_cfg.info.screen_win.width = SCREEN_W;
    test_cfg->layer_cfg.info.screen_win.height = SCREEN_H;

    test_cfg->layer_cfg.info.alpha_mode = 0;
    test_cfg->layer_cfg.info.alpha_value = 255;
    test_cfg->layer_cfg.info.zorder = ZORDER;

    test_cfg->layer_cfg.layer_id = LAYER_ID;
    test_cfg->layer_cfg.channel = CHANNEL_ID;



    test_cfg->layer_cfg.info.fb.lbc_en = 1;
    test_cfg->layer_cfg.info.fb.lbc_info.is_lossy = LBC_IS_LOSSY;
    test_cfg->layer_cfg.info.fb.lbc_info.rc_en = LBC_RC_EN;
    test_cfg->layer_cfg.info.fb.lbc_info.pitch = pitch;
    test_cfg->layer_cfg.info.fb.lbc_info.seg_bit = seg_bit;


    test_cfg->layer_cfg.info.fb.format = DISP_FORMAT_YUV420_P;//must be this format



    printf("Start get mem addr\n");

    arg[0] = test_cfg->mem_id;
    arg[1] = 0;
    arg[2] = 0;
    arg[3] = 0;
    test_cfg->layer_cfg.info.fb.addr[0] = disp_mem_getadr(test_cfg->mem_id);

    //test_cfg->layer_cfg.info.fb.addr[1] =
    //    (test_cfg->layer_cfg.info.fb.addr[0] +
    //    WIDTH * HEIGHT);
    //test_cfg->layer_cfg.info.fb.addr[2] =
    //    (test_cfg->layer_cfg.info.fb.addr[0] +
    //    WIDTH * HEIGHT * 5 / 4);


    arg[0] = test_cfg->screen_id;
    arg[1] = (unsigned long)&test_cfg->layer_cfg;
    arg[2] = 1;
    arg[3] = 0;
    printf("Start show layer\n");
    ret = disp_ioctl(DISP_LAYER_SET_CONFIG, (void *)arg);
    if (0 != ret)
        printf("fail to set layer cfg %d\n",ret);
    disp_release();


    printf("press any key to clear layer\n");
    getchar();

    disp_layer_clear_all(0);

    disp_mem_clear(0);

    return 0;
}





FINSH_FUNCTION_EXPORT_ALIAS(lbc_test, __cmd_disp_lbc_test, disp lbc test);

