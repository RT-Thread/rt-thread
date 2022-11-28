#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <rtthread.h>
#include <hal_mem.h>
#include <hal_cmd.h>
#include "dev_disp.h"
static void printf_from_to(unsigned long from, unsigned long to)
{
    unsigned int num = (to - from)/16;
    while(num--){
        printf("0x%08lx: ",from);
        printf("0x%08x 0x%08x 0x%08x 0x%08x\n",
            (*((volatile unsigned int  *)(from))),
            (*((volatile unsigned int  *)(from+4))),
            (*((volatile unsigned int  *)(from+8))),
            (*((volatile unsigned int  *)(from+12)))
        );
        from+=16;
    }
}
static void print_reg(void)
{
    printf("=========dump register================\n");
    printf("DE top register\n\n");
    printf_from_to(0x05000000,0x050000f0);
    printf("DE global register\n\n");
    printf_from_to(0x05100000,0x05100020);
    printf("DE blender register\n");
    printf_from_to(0x05101000,0x05101100);

    printf("DE VI overlay (channel 0) register\n");
    printf_from_to(0x05102000,0x051020ff);
    printf("DE UI overlay (channel 1) register\n");
    printf_from_to(0x05103000,0x051030ff);

    printf("DE VI scaler register\n");
    printf_from_to(0x05120000,0x05121000);

    printf("DE UI scaler (channel 1) register\n");
    printf_from_to(0x05140000,0x05141000);

    printf("tcon lcd0\n");
    printf_from_to(0x05461000,0x05461240);
    printf("disp if top\n");
    printf_from_to(0x05460000,0x05460100);
    printf("csc\n");
    printf_from_to(0x51b0000,0x51b00ff);
}
static int cmd_disp_debug(int argc, const char **argv)
{
    int i = 0, err = 0;
    struct disp_manager *mgr = NULL;
    u32 num_screens;
    char tmp[10] = {0};

    num_screens = bsp_disp_feat_get_num_screens();


    if (argc == 1) {
        disp_sys_show();
    } else {

        while(i < argc) {
            /*colorbar*/
            if ( ! strcmp(argv[i], "-c")) {
                if (argc > i+2) {
                    i+=1;
                    disp_colorbar_store(atoi(argv[i]), atoi(argv[i + 1]));
                    i+=1;
                } else {
                    DE_WRN("-c para error!\n");
                    err++;
                }
            }
            if ( ! strcmp(argv[i], "-r")) {
                print_reg();
            }
            /*switch display*/
            if ( ! strcmp(argv[i], "-s")) {
                if (argc > i+3) {
                    i+=1;
                    bsp_disp_device_switch(atoi(argv[i]), atoi(argv[i + 1]), atoi(argv[i + 2]));
                    i+=2;
                } else {
                    DE_WRN("-s para error!\n");
                    err++;
                }
            }
            /*dump de data*/
            if ( ! strcmp(argv[i], "-d")) {
                if (argc > i+2) {
                    i+=1;
                    disp_capture_dump(atoi(argv[i]), argv[i + 1]);
                    i+=1;
                } else {
                    DE_WRN("-d para error!\n");
                    err++;
                }
            }

            /*enhance */
            if ( ! strcmp(argv[i], "-e")) {
                if (argc > i+2) {
                    i+=1;

                    switch(argv[i][0]) {
                    case 'm'://mode
                        disp_enhance_mode_store(atoi(argv[i + 1]), atoi(argv[i + 2]));
                        break;
                    case 's'://saturation
                        disp_enhance_saturation_store(atoi(argv[i + 1]), atoi(argv[i + 2]));
                        break;
                    case 'b'://bright
                        disp_enhance_bright_store(atoi(argv[i + 1]), atoi(argv[i + 2]));
                        break;
                    case 'c'://contrast
                        disp_enhance_contrast_store(atoi(argv[i + 1]), atoi(argv[i + 2]));
                        break;
                    case 'g'://gamma color_temperature
                        printf("gamma %s %s %d %d\n",argv[i + 1],argv[i + 2],atoi(argv[i + 1]), atoi(argv[i + 2]));
                        disp_color_temperature_store(atoi(argv[i + 1]), atoi(argv[i + 2]));
                        break;
                    case 'n'://denoise
                        disp_enhance_denoise_store(atoi(argv[i + 1]), atoi(argv[i + 2]));
                        break;
                    case 'd'://detail
                        disp_enhance_detail_store(atoi(argv[i + 1]), atoi(argv[i + 2]));
                        break;
                    case 'p'://print

                        if (atoi(argv[i + 1]) < 0 || atoi(argv[i + 1]) > 1) {
                            i-=1;
                            DE_WRN("para error!\n");
                            break;
                        }
                        DISP_PRINT("screen %d:\n", atoi(argv[i + 1]));
                        disp_enhance_mode_show(atoi(argv[i + 1]), tmp);
                        DISP_PRINT("mode %s\n", tmp);
                        disp_enhance_saturation_show(atoi(argv[i + 1]), tmp);
                        DISP_PRINT("saturation %s\n", tmp);
                        disp_enhance_bright_show(atoi(argv[i + 1]), tmp);
                        DISP_PRINT("bright %s\n", tmp);
                        disp_enhance_contrast_show(atoi(argv[i + 1]), tmp);
                        DISP_PRINT("contrast %s\n", tmp);
                        disp_color_temperature_show(atoi(argv[i + 1]), tmp);
                        DISP_PRINT("color_temperature %s\n", tmp);
                        disp_enhance_denoise_show(atoi(argv[i + 1]), tmp);
                        DISP_PRINT("denoise %s\n", tmp);
                        disp_enhance_detail_show(atoi(argv[i + 1]), tmp);
                        DISP_PRINT("detail %s\n", tmp);
                        i-=1;
                        break;
                    default:
                        DE_WRN("para error!\n");
                        break;
                    }
                    i+=2;
                } else {
                    DE_WRN("para error!\n");
                    err++;
                }
            }

            /*backlight*/
            if ( ! strcmp(argv[i], "-b")) {
                if (argc > i+2) {
                    i+=1;
                    if (atoi(argv[i]) < num_screens) {
                        DE_WRN("set backligt:lcd%d %d\n", atoi(argv[i]), atoi(argv[i + 1]));
                        mgr = g_disp_drv.mgr[atoi(argv[i])];
                        mgr->device->set_bright(mgr->device, atoi(argv[i + 1]));
                    }
                    i+=1;
                } else {
                    DE_WRN("-b para error!\n");
                    err++;
                }
            }
            ++i;
        }
    }
    return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(cmd_disp_debug, __cmd_disp, disp cmd);
