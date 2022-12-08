#include <sunxi_hal_common.h>
#include <hal_clk.h>
#include <hal_prcm.h>

void hal_clock_init(void)
{
    ccu_init();
}

hal_clk_status_t hal_clk_set_parent(hal_clk_id_t clk, hal_clk_id_t parent)
{
    return ccu_set_mclk_src(clk, parent) == OK ?
            HAL_CLK_STATUS_OK :
            HAL_CLK_STATUS_INVALID_PARAMETER;
}

hal_clk_id_t hal_clk_get_parent(hal_clk_id_t clk)
{
    return ccu_get_mclk_src(clk);
}

u32 hal_clk_recalc_rate(hal_clk_id_t clk)
{
    return ccu_get_sclk_freq(clk);
}

u32 hal_clk_round_rate(hal_clk_id_t clk, u32 rate)
{
    /* TODO */
    return HAL_CLK_RATE_UNINITIALIZED;
}

u32 hal_clk_get_rate(hal_clk_id_t clk)
{
    return ccu_get_sclk_freq(clk);
}

hal_clk_status_t hal_clk_set_rate(hal_clk_id_t clk, u32 rate)
{
    return ccu_set_sclk_freq(clk, rate) == OK ?
            HAL_CLK_STATUS_OK :
            HAL_CLK_STATUS_INVALID_PARAMETER;
}

hal_clk_status_t hal_clock_is_enabled(hal_clk_id_t clk)
{
    /* FIXME: always return disabled */
    return HAL_CLK_STATUS_DISABLED;
}

hal_clk_status_t hal_clock_enable(hal_clk_id_t clk)
{
    if (ccu_set_mclk_reset(clk, CCU_CLK_NRESET) != OK)
        return HAL_CLK_STATUS_ERROR_CLK_ENABLED_FAILED;

    if (ccu_set_mclk_onoff(clk, CCU_CLK_ON) != OK)
        return HAL_CLK_STATUS_ERROR_CLK_ENABLED_FAILED;

    return HAL_CLK_STATUS_OK;
}

hal_clk_status_t hal_clock_disable(hal_clk_id_t clk)
{
    if (ccu_set_mclk_onoff(clk, CCU_CLK_OFF) != OK)
        return HAL_CLK_STATUS_ERROR_CLK_ENABLED_FAILED;

    if (ccu_set_mclk_reset(clk, CCU_CLK_RESET) != OK)
        return HAL_CLK_STATUS_ERROR_CLK_ENABLED_FAILED;

    return HAL_CLK_STATUS_OK;
}
