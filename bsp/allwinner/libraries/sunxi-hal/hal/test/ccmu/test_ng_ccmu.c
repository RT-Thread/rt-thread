#include <stdlib.h>
#include <hal_log.h>
#include <hal_cmd.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <common_ccmu.h>
#include <rtthread.h>

int clk_number[] = {
    CLK_SRC_NUMBER,
    CLK_RTC_NUMBER,
    CLK_NUMBER,
    CLK_R_NUMBER,
    0
};

int reset_number[] = {
    RST_BUS_NUMBER,
    RST_R_BUS_NUMBER,
    0,
};

char *strict_clks[] = {
    "pll-ddr0",
    "riscv",
    "pll-cpux",
    "pll-periph0-parent",
    "riscv-axi",
    "apb1",
    "fanout-27m",
    NULL,
};

int is_strict_clk(hal_clk_t clk)
{
    int i;
    for (i = 0; strict_clks[i] != NULL; i++)
    {
        if (!strcmp(clk->name, strict_clks[i]))
            return 1;
    }

    return 0;
}

static uint32_t esMEMS_FreeMemSize(void)
{
    rt_uint32_t total, used, max_used;
    rt_uint32_t aval;

    rt_memory_info(&total, &used, &max_used);
    aval = total - used;
    return aval;
}

int cmd_test_ng_ccmu(int argc, char **argv)
{
    int i, j;

    hal_clk_type_t clk_type;
    hal_clk_id_t   clk_id;
    hal_clk_status_t clk_status;
    hal_clk_t clk, p_clk;
    u32  old_rate, new_rate, p_rate;

    hal_reset_type_t reset_type;
    hal_reset_id_t  reset_id;
    struct reset_control *reset;
    int reset_status;

    printf("free size = 0x%x\n", esMEMS_FreeMemSize());
    for (i = HAL_SUNXI_FIXED_CCU; i < HAL_SUNXI_CCU_NUMBER; i++)
    {
        clk_type = i;
        for (j = 0; j < clk_number[i]; j++)
        {
            clk_id = j;
            printf("get clock, type:%d, id:%d\n", clk_type, clk_id);
            clk = hal_clock_get(clk_type, clk_id);

            clk_status = hal_clock_is_enabled(clk);
            printf("clock %s status:%s\n", clk->name, clk_status? "disabled" : "enabled");
            printf("enable clock %s\n", clk->name);
            hal_clock_enable(clk);
            clk_status = hal_clock_is_enabled(clk);
            printf("clock %s status:%s\n", clk->name, clk_status? "disabled" : "enabled");

            if (is_strict_clk(clk))
                continue;

            p_clk = hal_clk_get_parent(clk);
            if (p_clk)
            printf("clock %s\'s parent is: %s\n", clk->name, p_clk->name);
            else
            printf("clock %s is root clk\n", clk->name);

            old_rate = hal_clk_get_rate(clk);
            printf("clockk %s rate: %d\n", clk->name, old_rate);
            old_rate /= 2;
            printf("clock %s set rate: %d\n", clk->name, old_rate);
            hal_clk_set_rate(clk, old_rate);
            new_rate = hal_clk_get_rate(clk);
            printf("clock %s get rate: %d\n", clk->name, new_rate);

            //printf("disable clock %s\n", clk->name);
            //hal_clock_disable(clk);
            //clk_status = hal_clock_is_enabled(clk);
            //printf("clock %s status:%s\n", clk->name, clk_status? "disabled" : "enabled");

            //hal_clock_put(p_clk);
            //hal_clock_put(clk);
        }
    }

    printf("free size = 0x%x\n", esMEMS_FreeMemSize());
    for (i = HAL_SUNXI_RESET; i < HAL_SUNXI_RESET_NUMBER; i++)
    {
    reset_type = i;
    for (j = 0; j < reset_number[i]; j++)
    {
        reset_id = j;

        printf("reset: get reset control, type:%d, id: %d\n", reset_type, reset_id);
        reset = hal_reset_control_get(reset_type, reset_id);

        printf("reset: control deassert\n");
        hal_reset_control_deassert(reset);

        reset_status = hal_reset_control_status(reset);
        printf("reset status: %s", reset_status ? "assert" : "deassert");

        printf("reset: put reset control, type:%d, id: %d\n", reset_type, reset_id);
        hal_reset_control_put(reset);
    }
    }

    printf("free size = 0x%x\n", esMEMS_FreeMemSize());
    return 0;
}

MSH_CMD_EXPORT_ALIAS(cmd_test_ng_ccmu, hal_ccmu, sunxi - ng ccmu hal APIs tests)

