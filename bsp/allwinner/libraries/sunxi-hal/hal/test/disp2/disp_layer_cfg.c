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
int msleep(unsigned int msecs);
extern int disp_ioctl(int cmd, void *arg);
extern int disp_release(void);
extern int disp_open(void);

int disp_layer_clear(u32 screen_index, u32 chn, u32 layer)
{
    struct disp_layer_config config;
    unsigned long arg[6];
    int ret = -1, i ,j;
    disp_open();
    memset(&config, 0, sizeof(struct disp_layer_config));

    arg[0] = screen_index;
    arg[1] = (unsigned long)&config;
    arg[2] = 1;
    arg[3] = 0;

    config.enable = false;
    config.channel = chn;
    config.layer_id = layer;
    ret = disp_ioctl(DISP_LAYER_SET_CONFIG,
                  (void *)arg);
    msleep(10);
    if (0 != ret)
        printf("fail to set layer cfg\n");
    disp_release();

    return ret;

}

int disp_layer_clear_all(u32 screen_index)
{
    struct disp_layer_config config;
    unsigned long arg[6];
    int ret = -1, i ,j;

    memset(&config, 0, sizeof(struct disp_layer_config));

    arg[0] = screen_index;
    arg[1] = (unsigned long)&config;
    arg[2] = 1;
    arg[3] = 0;

    disp_open();
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            config.enable = false;
            config.channel = i;
            config.layer_id = j;
            disp_ioctl(DISP_LAYER_SET_CONFIG,
                          (void *)arg);
            msleep(10);
            if (0 != ret)
                printf("fail to set layer cfg\n");
        }
    }

    disp_release();
    return ret;

}
int disp_layer_get_resolution(u32 screen_index, u32 *width, u32 *height)
{
    unsigned long arg[6];

    if (!width || !height) {
        printf("NULL pointer!\n");
        return -1;
    }
    disp_open();
    arg[0] = screen_index;
    *width = disp_ioctl(DISP_GET_SCN_WIDTH, (void *)arg);
    *height = disp_ioctl(DISP_GET_SCN_HEIGHT, (void *)arg);
    disp_release();
    return 0;
}

int disp_layer_cfg(struct test_layer_cfg *test_cfg)
{
    unsigned long arg[6];
    int id, width, height, ret, sw, sh, fb_width, fb_height, i, n;

    if (!test_cfg) {
        printf("Null pointer!\n");
        return -1;
    }

    if (1 == test_cfg->fullscreen) {
        /* full-screen display */
        printf("full screen display\n");
    }
    disp_open();
    if (test_cfg->clear) {
        printf("clear \n");

        test_cfg->layer_cfg.enable = 0;
        arg[0] = test_cfg->screen_id;
        arg[1] = (unsigned long)&test_cfg->layer_cfg;
        arg[2] = 1;
        arg[3] = 0;
        disp_ioctl(DISP_LAYER_SET_CONFIG, (void *)arg);
        disp_release();
        return 0;
    }

    arg[0] = test_cfg->screen_id;
    test_cfg->width = disp_ioctl(DISP_GET_SCN_WIDTH, (void *)arg);
    test_cfg->height = disp_ioctl(DISP_GET_SCN_HEIGHT, (void *)arg);

    fb_width = sw = test_cfg->layer_cfg.info.fb.size[0].width;
    fb_height = sh = test_cfg->layer_cfg.info.fb.size[0].height;

    if (test_cfg->layer_cfg.info.fb.flags & DISP_BF_STEREO_FP) {
        fb_height = fb_height / 2;
    }

    arg[0] = test_cfg->mem_id;
    arg[1] = 0;
    arg[2] = 0;
    arg[3] = 0;
    test_cfg->layer_cfg.info.fb.addr[0] = disp_mem_getadr(test_cfg->mem_id);

    test_cfg->layer_cfg.info.fb.size[0].width = fb_width;
    test_cfg->layer_cfg.info.fb.size[0].height = fb_height;
    if (test_cfg->layer_cfg.info.fb.format == DISP_FORMAT_YUV444_P) {

        test_cfg->layer_cfg.info.fb.addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0]);
        test_cfg->layer_cfg.info.fb.addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 2);
        test_cfg->layer_cfg.info.fb.trd_right_addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 3);
        test_cfg->layer_cfg.info.fb.trd_right_addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.trd_right_addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height * 2);

        test_cfg->layer_cfg.info.fb.size[1].width =
            test_cfg->layer_cfg.info.fb.size[0].width;
        test_cfg->layer_cfg.info.fb.size[1].height =
            test_cfg->layer_cfg.info.fb.size[0].height;
        test_cfg->layer_cfg.info.fb.size[2].width =
            test_cfg->layer_cfg.info.fb.size[0].width;
        test_cfg->layer_cfg.info.fb.size[2].height =
            test_cfg->layer_cfg.info.fb.size[0].height;

    } else if (test_cfg->layer_cfg.info.fb.format == DISP_FORMAT_YUV422_P ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV422_SP_UVUV ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV422_SP_VUVU ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV422_SP_UVUV ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV422_SP_VUVU) {

        test_cfg->layer_cfg.info.fb.addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0]);
        test_cfg->layer_cfg.info.fb.addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 3 / 2);
        test_cfg->layer_cfg.info.fb.trd_right_addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 2);
        test_cfg->layer_cfg.info.fb.trd_right_addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.trd_right_addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height * 3 / 2);

        test_cfg->layer_cfg.info.fb.size[1].width =
            test_cfg->layer_cfg.info.fb.size[0].width / 2;
        test_cfg->layer_cfg.info.fb.size[1].height =
            test_cfg->layer_cfg.info.fb.size[0].height;
        test_cfg->layer_cfg.info.fb.size[2].width =
            test_cfg->layer_cfg.info.fb.size[0].width / 2;
        test_cfg->layer_cfg.info.fb.size[2].height =
            test_cfg->layer_cfg.info.fb.size[0].height;

    } else if (test_cfg->layer_cfg.info.fb.format == DISP_FORMAT_YUV411_P ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV411_SP_UVUV ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV411_SP_VUVU ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV411_SP_UVUV ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV411_SP_VUVU) {

        test_cfg->layer_cfg.info.fb.addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0]);
        test_cfg->layer_cfg.info.fb.addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 5 / 4);
        test_cfg->layer_cfg.info.fb.trd_right_addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 3 / 2);
        test_cfg->layer_cfg.info.fb.trd_right_addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.trd_right_addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height * 5 / 4);

        test_cfg->layer_cfg.info.fb.size[1].width =
            test_cfg->layer_cfg.info.fb.size[0].width / 4;
        test_cfg->layer_cfg.info.fb.size[1].height =
            test_cfg->layer_cfg.info.fb.size[0].height;
        test_cfg->layer_cfg.info.fb.size[2].width =
            test_cfg->layer_cfg.info.fb.size[0].width / 4;
        test_cfg->layer_cfg.info.fb.size[2].height =
            test_cfg->layer_cfg.info.fb.size[0].height;

    } else if (test_cfg->layer_cfg.info.fb.format == DISP_FORMAT_YUV420_P ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV420_SP_UVUV ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV420_SP_VUVU ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV420_SP_UVUV ||
           test_cfg->layer_cfg.info.fb.format ==
               DISP_FORMAT_YUV420_SP_VUVU) {

        test_cfg->layer_cfg.info.fb.addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0]);
        test_cfg->layer_cfg.info.fb.addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 5 / 4);
        test_cfg->layer_cfg.info.fb.trd_right_addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 3 / 2);
        test_cfg->layer_cfg.info.fb.trd_right_addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.trd_right_addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height * 5 / 4);

        test_cfg->layer_cfg.info.fb.size[1].width =
            test_cfg->layer_cfg.info.fb.size[0].width / 2;
        test_cfg->layer_cfg.info.fb.size[1].height =
            test_cfg->layer_cfg.info.fb.size[0].height / 2;
        test_cfg->layer_cfg.info.fb.size[2].width =
            test_cfg->layer_cfg.info.fb.size[0].width / 2;
        test_cfg->layer_cfg.info.fb.size[2].height =
            test_cfg->layer_cfg.info.fb.size[0].height / 2;
    } else {
        /* INTERLEAVED */
        test_cfg->layer_cfg.info.fb.addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height / 3 * 0);
        test_cfg->layer_cfg.info.fb.addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height / 3 * 1);
        test_cfg->layer_cfg.info.fb.addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height / 3 * 2);
        test_cfg->layer_cfg.info.fb.trd_right_addr[0] =
            (int)(test_cfg->layer_cfg.info.fb.addr[0] +
              fb_width * fb_height * 3 / 2);
        test_cfg->layer_cfg.info.fb.trd_right_addr[1] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height);
        test_cfg->layer_cfg.info.fb.trd_right_addr[2] =
            (int)(test_cfg->layer_cfg.info.fb.trd_right_addr[0] +
              fb_width * fb_height * 3 / 2);

        test_cfg->layer_cfg.info.fb.size[1].width =
            test_cfg->layer_cfg.info.fb.size[0].width;
        test_cfg->layer_cfg.info.fb.size[1].height =
            test_cfg->layer_cfg.info.fb.size[0].height;
        test_cfg->layer_cfg.info.fb.size[2].width =
            test_cfg->layer_cfg.info.fb.size[0].width;
        test_cfg->layer_cfg.info.fb.size[2].height =
            test_cfg->layer_cfg.info.fb.size[0].height;
    }

    if ((0 == test_cfg->layer_cfg.info.screen_win.width) ||
        (0 == test_cfg->layer_cfg.info.screen_win.height)) {
        if (1 == test_cfg->fullscreen) {
            /* full-screen display */
            printf("full screen display\n");
            test_cfg->layer_cfg.info.screen_win.width =
                test_cfg->width;
            test_cfg->layer_cfg.info.screen_win.height =
                test_cfg->height;
        } else {
            /* origin size display */
            /* cut out-of-screen part */
            if (test_cfg->layer_cfg.info.fb.crop.width >
                test_cfg->width)
                test_cfg->layer_cfg.info.fb.crop.width =
                    test_cfg->width;
            if (test_cfg->layer_cfg.info.fb.crop.height >
                test_cfg->height)
                test_cfg->layer_cfg.info.fb.crop.height =
                    test_cfg->height;

            test_cfg->layer_cfg.info.screen_win.width =
                (unsigned int)
                test_cfg->layer_cfg.info.fb.crop.width;
            test_cfg->layer_cfg.info.screen_win.height =
                (unsigned int)
                test_cfg->layer_cfg.info.fb.crop.height;
        }
    }
    test_cfg->layer_cfg.info.fb.crop.x = test_cfg->layer_cfg.info.fb.crop.x
                         << 32;
    test_cfg->layer_cfg.info.fb.crop.y = test_cfg->layer_cfg.info.fb.crop.y
                         << 32;
    test_cfg->layer_cfg.info.fb.crop.width =
        test_cfg->layer_cfg.info.fb.crop.width << 32;
    test_cfg->layer_cfg.info.fb.crop.height =
        test_cfg->layer_cfg.info.fb.crop.height << 32;

    test_cfg->layer_cfg.enable = 1;
    arg[0] = test_cfg->screen_id;
    arg[1] = (unsigned long)&test_cfg->layer_cfg;
    arg[2] = 1;
    arg[3] = 0;
    ret = disp_ioctl(DISP_LAYER_SET_CONFIG, (void *)arg);
    if (0 != ret)
        printf("fail to set layer cfg %d\n",ret);
    disp_release();
    return 0;
}



int parse_cmdline_and_set_config(int argc, char **argv)
{
    int err = 0;
    int i = 0;
    struct test_layer_cfg layer_cfg;
    struct test_layer_cfg *p = &layer_cfg;
    while(i<argc) {
        printf("%s ",argv[i]);
        i++;
    }
    printf("\n");
    memset(p, 0, sizeof(struct test_layer_cfg));
    i = 0;
    while(i < argc) {
        if ( ! strcmp(argv[i], "-ch")) {
            if (argc > i+1) {
                i+=1;
                p->screen_id = atoi(argv[i]);
            }
            else{
                printf("screen_id para error!\n");
                err++;
            }
        }

        if ( ! strcmp(argv[i], "-mem_id")) {
            if (argc > i+1) {
                i+=1;
                p->mem_id = atoi(argv[i]);
            }
            else{
                printf("mem_id para error!\n");
                err++;
            }
        }

        if ( ! strcmp(argv[i], "-layer_id")) {
            if (argc > i+1) {
                i++;
                p->layer_id = atoi(argv[i]);
                p->layer_cfg.layer_id = p->layer_id;
            }
            else{
                printf("layer_id para error!\n");
                err++;
            }
        }

        if( ! strcmp(argv[i], "-channel_id")){
            if(argc > i+1){
                i++;
                p->layer_cfg.channel = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-layer_mode")) {
            if (argc > i+1) {
                i++;
                p->layer_cfg.info.mode = atoi(argv[i]);
            }
        }

        if( ! strcmp(argv[i], "-zorder")){
            if(argc > i+1){
                i++;
                p->layer_cfg.info.zorder = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-alpha")) {
            if (argc > i+2) {
                i++;
                p->layer_cfg.info.alpha_mode= atoi(argv[i]);
                i++;
                p->layer_cfg.info.alpha_value= atoi(argv[i]);
            }   else {
                printf("-alpha para err!\n\n");
                err ++;
            }
        }

        if ( ! strcmp(argv[i], "-in_fb")) {
            if (argc > i+8) {
                i++;
                p->layer_cfg.info.fb.format = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.size[0].width = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.size[0].height = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.crop.x = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.crop.y = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.crop.width = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.crop.height = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.align[0] = atoi(argv[i]);
            }   else {
                printf("-in_fb para err!\n\n");
                err ++;
            }
        }

        if( ! strcmp(argv[i], "-color_space")){
            if(argc > i+1){
                i++;
                p->layer_cfg.info.fb.color_space = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-prem")) {
            if (argc > i+1) {
                i++;
                p->layer_cfg.info.fb.pre_multiply = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-flags")) {
            if (argc > i+1) {
                i++;
                p->layer_cfg.info.fb.flags = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-scan")) {
            if (argc > i+1) {
                i++;
                p->layer_cfg.info.fb.scan = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-trd")) {
            if (argc > i+3) {
                i++;
                p->layer_cfg.info.fb.flags = atoi(argv[i]);
                i++;
                p->layer_cfg.info.b_trd_out = atoi(argv[i]);
                i++;
                p->layer_cfg.info.out_trd_mode = atoi(argv[i]);
            } else {
                printf("-trd para err!\n\n");
                err ++;
            }
        }

        if ( ! strcmp(argv[i], "-screen_win")) {
            if (argc > i+4) {
                i++;
                p->layer_cfg.info.screen_win.x = atoi(argv[i]);
                i++;
                p->layer_cfg.info.screen_win.y = atoi(argv[i]);
                i++;
                p->layer_cfg.info.screen_win.width = atoi(argv[i]);
                i++;
                p->layer_cfg.info.screen_win.height = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-id")) {
            if (argc > i+1) {
                i++;
                p->layer_cfg.info.id = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-clr")) {
            if (argc > i+1) {
                i++;
                p->clear = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-fullscreen")) {
                p->fullscreen = 1;
        }

        // if ( ! strcmp(argv[i], "-screen_size")) {
            // if (argc > i+2) {
                // i++;
                // p->width = atoi(argv[i]);
                // i++;
                // p->height = atoi(argv[i]);
            // }
        // }

        i++;
    }

    if(err > 0) {
        printf("example : ./disp_layer_cfg -ch 0 -mem_id 0 -layer_id 0 -channel_id 0 "
            "-in_fb 0 1280 800 0 0 1280 800 4  -layer_mode 0  -alpha 1 255 -screen_win 0 0 250 150\n");
        return -1;
    } else {
        return disp_layer_cfg(p);
    }
}



FINSH_FUNCTION_EXPORT_ALIAS(parse_cmdline_and_set_config, disp_layer_cfg, disp set layer);

