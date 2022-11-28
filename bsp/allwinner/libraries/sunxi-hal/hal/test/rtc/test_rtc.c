#include <stdio.h>
#include <hal_log.h>
#include <hal_cmd.h>
#include <sunxi_hal_rtc.h>

static int callback(void)
{
    printf("alarm interrupt\n");
    return 0;
}

static int cmd_test_rtc(int argc, const char **argv)
{
    unsigned int enable = 0;
    struct rtc_time rtc_tm;
    struct rtc_wkalrm wkalrm;

    hal_rtc_init();

    hal_rtc_register_callback(callback);

    if (hal_rtc_gettime(&rtc_tm))
    {
        printf("sunxi rtc gettime error\n");
    }

    wkalrm.enabled = 1;
    wkalrm.time = rtc_tm;
    if(rtc_tm.tm_min > 0)
        rtc_tm.tm_min -= 1;
    else
        wkalrm.time.tm_min += 1;

    printf("alarm time %04d-%02d-%02d %02d:%02d:%02d\n",
           wkalrm.time.tm_year + 1900, wkalrm.time.tm_mon + 1, wkalrm.time.tm_mday,
           wkalrm.time.tm_hour, wkalrm.time.tm_min, wkalrm.time.tm_sec);

    if (hal_rtc_settime(&rtc_tm))
    {
        printf("sunxi rtc settime error\n");
    }

    if (hal_rtc_setalarm(&wkalrm))
    {
        printf("sunxi rtc setalarm error\n");
    }

    if (hal_rtc_getalarm(&wkalrm))
    {
        printf("sunxi rtc getalarm error\n");
    }

    if (hal_rtc_gettime(&rtc_tm))
    {
        printf("sunxi rtc gettime error\n");
    }

    //if do hal_rtc_alarm_irq_enable and hal_rtc_uninit, alarm will not work
    hal_rtc_alarm_irq_enable(enable);

    hal_rtc_deinit();
    return 0;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_test_rtc, hal_rtc, rtc hal APIs tests)
