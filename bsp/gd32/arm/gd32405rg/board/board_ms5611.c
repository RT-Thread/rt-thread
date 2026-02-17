/*******************************************************************************
 * @file board_ms5611.c
 * @author ShiHongchao
 * @date 2025-12-14
 * @version V0.1
 * @brief 使用ms5611软件包向传感器框架注册ms5611气压传感器
 *******************************************************************************
*/

#include <rtdevice.h>

#define LOG_TAR "board.ms5611"
#include <rtdbg.h>

#include "board.h"
#include "sensor_meas_ms5611.h"

int board_ms5611_init(void)
{
    int rsult = rt_hw_ms5611_init("ms5611", &(struct rt_sensor_config){
        .intf.dev_name = "hwi2c0",
    });
    if(rsult != RT_EOK)
    {
        LOG_E("ms5611 init failed");
        return rsult;
    }

    return rsult;
}
INIT_DEVICE_EXPORT(board_ms5611_init);
