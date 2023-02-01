#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <usb/sunxi_hal_udc.h>
#include <hal_cmd.h>
#include <hal_log.h>

static void show_ed_test_help(void)
{
    printf("Usage: ed_test test_type\n");
    printf("test_type: test_j_state\n");
    printf("           : test_k_state\n");
    printf("           : test_se0_nak\n");
    printf("           : test_pack\n");
}

static int cmd_hal_udc_ed_test(int argc, const char **argv)
{
    if (argc != 2)
    {
        show_ed_test_help();
        return 0;
    }
    ed_test(argv[1], strlen(argv[1]));
    return 0;

}
FINSH_FUNCTION_EXPORT_CMD(cmd_hal_udc_ed_test, __cmd_hal_udc_ed_test, udc hal ed tests)

static void show_hal_udc_dl_adjust_help(void)
{
    printf("Usage: hal_udc_dl_adjust driverlevel\n");
    printf("driverlevel: [0-15]\n");
}

static int cmd_hal_udc_dl_adjust(int argc, const char **argv)
{
    int driver_level = 0;
    if (argc != 2)
    {
        show_hal_udc_dl_adjust_help();
        return 0;
    }

    driver_level = atoi(argv[1]);

    if (driver_level < 0 || driver_level > 15)
    {
        printf("driver_level err:%s\n", argv[1]);
        show_hal_udc_dl_adjust_help();
        return 0;
    }
    hal_udc_driverlevel_adjust(driver_level);
    return 0;

}
FINSH_FUNCTION_EXPORT_CMD(cmd_hal_udc_dl_adjust, __cmd_hal_udc_dl_adjust, udc hal driverlevel adjust)
