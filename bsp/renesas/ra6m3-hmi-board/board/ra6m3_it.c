#include <rtthread.h>
#include "hal_data.h"

#ifdef BSP_USING_CAN
rt_weak void can0_callback(can_callback_args_t *p_args)
{
}
#endif

#ifdef BSP_USING_ETH
rt_weak void user_ether0_callback(ether_callback_args_t *p_args)
{
}
#endif

#ifdef BSP_USING_I2S
rt_weak void i2s_callback(i2s_callback_args_t *p_args)
{
}
#endif

#ifdef BSP_USING_JPEG
rt_weak void decode_callback(jpeg_callback_args_t *p_args)
{
}
#endif

#ifdef BSP_USING_LCD
rt_weak void _ra_port_display_callback(display_callback_args_t *p_args)
{
}
#endif
