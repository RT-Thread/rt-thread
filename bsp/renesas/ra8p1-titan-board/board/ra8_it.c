#include <rtthread.h>
#include "hal_data.h"

rt_weak void user_uart0_callback(uart_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void spi0_callback(spi_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void rtc_callback(rtc_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void sdhi0_callback(sdmmc_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void canfd0_callback(can_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void timer0_callback(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void user_ether0_callback(ether_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

rt_weak void rmac_phy_target_rtl8211_initialize(rmac_phy_instance_ctrl_t *p_instance_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
}

rt_weak bool rmac_phy_target_rtl8211_is_support_link_partner_ability(rmac_phy_instance_ctrl_t *p_instance_ctrl,
                                                                     uint32_t line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    return true;
}

rt_weak const canfd_afl_entry_t p_canfd0_afl[CANFD_CFG_AFL_CH0_RULE_NUM] = {0};

rt_weak ospi_b_xspi_command_set_t g_hyper_ram_commands[] =
{
    {
        .protocol = SPI_FLASH_PROTOCOL_8D_8D_8D,
        .frame_format = OSPI_B_FRAME_FORMAT_XSPI_PROFILE_2_EXTENDED,
        .latency_mode = OSPI_B_LATENCY_MODE_FIXED,
        .command_bytes = OSPI_B_COMMAND_BYTES_1,
        .address_bytes = SPI_FLASH_ADDRESS_BYTES_4,

        .read_command = 0xA0,
        .read_dummy_cycles = 11,
        .program_command = 0x20,
        .program_dummy_cycles = 11,

        .address_msb_mask = 0xF0,
        .status_needs_address = false,

        .p_erase_commands = RT_NULL,
    }
};

