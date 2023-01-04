#include <stdio.h>
#include <stdlib.h>

#include <hal_cmd.h>
#include <sunxi_hal_thermal.h>
#include <hal_timer.h>

int cmd_ths_gt(int argc, char **argv)
{
    int ret, temp, i;
    static int init = 0;

    if (!init) {
        hal_ths_init();
        init = 1;
        hal_msleep(1000);
    }

    printf("ths get temp\n");

    ret = hal_ths_get_temp(0, &temp);
    if (ret < 0)
        printf("Fail to get temp.\n");
    else
        printf("\ntemp:%d\n", temp);

    return 0;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_ths_gt, ths_gt, thermal get temp)

