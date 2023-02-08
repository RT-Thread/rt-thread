/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-24     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 * 2020-12-15     liuhy         update libraries
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_i2c.h"


#ifdef RT_USING_I2C

#define TIMEOUT 0x0FFF
/* I2C struct definition */
#ifdef BSP_USING_I2C0
    static i2c_handle_t _h_i2c0;
#endif

#ifdef BSP_USING_I2C1
    static i2c_handle_t _h_i2c1;
#endif

static void _i2c_init(void)
{
    gpio_init_t gpio_instruct;

    /* Initialize I2C Pin */
    gpio_instruct.mode = GPIO_MODE_OUTPUT;
    gpio_instruct.odos = GPIO_OPEN_DRAIN;
    gpio_instruct.pupd = GPIO_PUSH_UP;
    gpio_instruct.odrv = GPIO_OUT_DRIVE_NORMAL;
    gpio_instruct.flt  = GPIO_FILTER_DISABLE;
    gpio_instruct.type = GPIO_TYPE_CMOS;
    gpio_instruct.func = GPIO_FUNC_5;

#ifdef BSP_USING_I2C0

#if  defined(ES_I2C0_SCL_GPIO_FUNC)&&defined(ES_I2C0_SCL_GPIO_PORT)&&defined(ES_I2C0_SCL_GPIO_PIN)
    gpio_instruct.func = ES_I2C0_SCL_GPIO_FUNC;
    ald_gpio_init(ES_I2C0_SCL_GPIO_PORT, ES_I2C0_SCL_GPIO_PIN, &gpio_instruct);
#endif

#if  defined(ES_I2C0_SDA_GPIO_FUNC)&&defined(ES_I2C0_SDA_GPIO_PORT)&&defined(ES_I2C0_SDA_GPIO_PIN)
    gpio_instruct.func = ES_I2C0_SDA_GPIO_FUNC;
    ald_gpio_init(ES_I2C0_SDA_GPIO_PORT, ES_I2C0_SDA_GPIO_PIN, &gpio_instruct);
#endif

    /* Initialize I2C Function */
    _h_i2c0.perh = I2C0;
    _h_i2c0.init.duty         = I2C_DUTYCYCLE_2;
    _h_i2c0.init.clk_speed    = ES_I2C0_CLK_SPEED;
    _h_i2c0.init.own_addr1    = ES_I2C0_OWN_ADDR1;
    _h_i2c0.init.addr_mode    = ES_I2C0_ADDR_MODE;
    _h_i2c0.init.general_call = ES_I2C0_GENERAL_CALL;
    _h_i2c0.init.no_stretch   = ES_I2C0_STRETCH;

    ald_i2c_reset(&_h_i2c0);
    ald_i2c_init(&_h_i2c0);

#endif

#ifdef BSP_USING_I2C1

#if  defined(ES_I2C1_SCL_GPIO_FUNC)&&defined(ES_I2C1_SCL_GPIO_PORT)&&defined(ES_I2C1_SCL_GPIO_PIN)
    gpio_instruct.func = ES_I2C1_SCL_GPIO_FUNC;
    ald_gpio_init(ES_I2C1_SCL_GPIO_PORT, ES_I2C1_SCL_GPIO_PIN, &gpio_instruct);
#endif

#if  defined(ES_I2C1_SDA_GPIO_FUNC)&&defined(ES_I2C1_SDA_GPIO_PORT)&&defined(ES_I2C1_SDA_GPIO_PIN)
    gpio_instruct.func = ES_I2C1_SDA_GPIO_FUNC;
    ald_gpio_init(ES_I2C1_SDA_GPIO_PORT, ES_I2C1_SDA_GPIO_PIN, &gpio_instruct);
#endif

    /* Initialize i2c function */
    _h_i2c1.perh = I2C1;
    _h_i2c1.init.duty         = I2C_DUTYCYCLE_2;
    _h_i2c1.init.clk_speed    = ES_I2C1_CLK_SPEED;
    _h_i2c1.init.own_addr1    = ES_I2C1_OWN_ADDR1;
    _h_i2c1.init.addr_mode    = ES_I2C1_ADDR_MODE;
    _h_i2c1.init.general_call = ES_I2C1_GENERAL_CALL;
    _h_i2c1.init.no_stretch   = ES_I2C1_STRETCH;

    ald_i2c_reset(&_h_i2c1);
    ald_i2c_init(&_h_i2c1);

#endif
}

static rt_ssize_t es32f0_master_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags & RT_I2C_RD)
        {
            if (ald_i2c_master_recv(bus->priv, msg->addr << 1, msg->buf, msg->len, TIMEOUT) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
        else
        {
            if (ald_i2c_master_send(bus->priv, msg->addr << 1, msg->buf, msg->len, TIMEOUT) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
    }

    ret = i;

out:
    LOG_E("send stop condition\n");

    return ret;
}

const struct rt_i2c_bus_device_ops es32f0_i2c_ops =
{
    es32f0_master_xfer,
    RT_NULL,
    RT_NULL,
};

int rt_hw_i2c_init(void)
{
    int result = RT_EOK;

    _i2c_init();

#ifdef BSP_USING_I2C0
    /* define i2c Instance */
    static struct rt_i2c_bus_device _i2c_device0;
    rt_memset((void *)&_i2c_device0, 0, sizeof(struct rt_i2c_bus_device));
    _i2c_device0.ops = &es32f0_i2c_ops;
    _i2c_device0.priv = &_h_i2c0;
    result = rt_i2c_bus_device_register(&_i2c_device0, ES_DEVICE_NAME_I2C0);
    if (result != RT_EOK)
    {
        return result;
    }
#endif

#ifdef BSP_USING_I2C1
    /* define i2c Instance */
    static struct rt_i2c_bus_device _i2c_device1;
    rt_memset((void *)&_i2c_device1, 0, sizeof(struct rt_i2c_bus_device));

    _i2c_device1.ops = &es32f0_i2c_ops;
    _i2c_device1.priv = &_h_i2c1;
    rt_i2c_bus_device_register(&_i2c_device1, ES_DEVICE_NAME_I2C1);
    if (result != RT_EOK)
    {
        return result;
    }
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
