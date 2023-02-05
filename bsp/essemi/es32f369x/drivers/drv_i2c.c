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
 * 2019-11-01     wangyq        update libraries
 * 2020-01-14     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 * 2022-07-11     shiwa         Support for RT_NO_START/RT_NO_STOP
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
    gpio_instruct.podrv = GPIO_OUT_DRIVE_6;
    gpio_instruct.nodrv = GPIO_OUT_DRIVE_6;
    gpio_instruct.flt  = GPIO_FILTER_DISABLE;
    gpio_instruct.type = GPIO_TYPE_CMOS;


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
    _h_i2c0.init.module       = I2C_MODULE_MASTER;
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
    _h_i2c1.init.module       = I2C_MODULE_MASTER;
    _h_i2c1.init.clk_speed    = ES_I2C1_CLK_SPEED;
    _h_i2c1.init.own_addr1    = ES_I2C1_OWN_ADDR1;
    _h_i2c1.init.addr_mode    = ES_I2C1_ADDR_MODE;
    _h_i2c1.init.general_call = ES_I2C1_GENERAL_CALL;
    _h_i2c1.init.no_stretch   = ES_I2C1_STRETCH;

    ald_i2c_reset(&_h_i2c1);
    ald_i2c_init(&_h_i2c1);

#endif
}
#define _I2C_NO_START 0x1
#define _I2C_NO_STOP  0x2
int _i2c_master_req(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout,uint32_t req_write)
{
    if (hperh->init.addr_mode == I2C_ADDR_7BIT) {
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
    }
    else {
        SET_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
    }

    MODIFY_REG(hperh->perh->CON2, I2C_CON2_SADD_MSK, dev_addr << I2C_CON2_SADD_POSS);
    if (req_write)
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);
    else
        SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);

    return OK;
}
int _i2c_wait_flag(i2c_handle_t *hperh, uint32_t flag, flag_status_t status, uint32_t timeout)
{
    uint32_t tickstart = 0;

        tickstart = ald_get_tick();
            while (I2C_GET_FLAG(hperh, flag) == status) {
                if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout)) {
                    hperh->error_code |= I2C_ERROR_TIMEOUT;
                    return TIMEOUT;
                }
            }

        return OK;
}
int _i2c_wait_txe(i2c_handle_t *hperh, uint32_t timeout)
{
    uint32_t tickstart = ald_get_tick();

    while (I2C_GET_FLAG(hperh, I2C_STAT_THTH) == RESET) {
        if (I2C_GET_IT_FLAG(hperh, I2C_IT_ARLO)) {
            hperh->error_code |= I2C_ERROR_ARLO;
            return ERROR;
        }

        if (I2C_GET_IT_FLAG(hperh, I2C_IT_NACK) == SET) {
            hperh->error_code |= I2C_ERROR_AF;
            return ERROR;
        }

        if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
            hperh->error_code |= I2C_ERROR_TIMEOUT;
            return ERROR;
        }
    }

    return OK;
}
int _i2c_master_send(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                 uint32_t size, uint32_t timeout,uint32_t flag)
{
    if (hperh->state != I2C_STATE_READY)
        return BUSY;

    if ((buf == NULL) || (size == 0))
        return  ERROR;
    if ((flag&_I2C_NO_START)==0x0) //NOSTART==0
    {
        if (_i2c_wait_flag(hperh, I2C_STAT_BUSY, SET, 100) != OK)
            return BUSY;
        _i2c_master_req(hperh, dev_addr, timeout,1);
    }
    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = I2C_STATE_BUSY_TX;
    hperh->mode       = I2C_MODE_MASTER;
    hperh->error_code = I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    if ((flag&_I2C_NO_STOP)!=0)  //NOSTOP==1
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    else
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    if (size <= 0xFF) {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
    }
    else {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }


    SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
    if ((flag&_I2C_NO_START)==0x0) //NOSTART=0
        SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    while (size > 0) {
        hperh->perh->TXDATA  = (*buf++);
        size--;
        hperh->xfer_count++;

        if (_i2c_wait_txe(hperh, timeout) != OK)
            goto ERROR;

        if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK))) {
            if (_i2c_wait_flag(hperh, I2C_STAT_TCR, RESET, 10) == OK) {
                if (size > 0xFF) {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
                }
                else {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
                    if ((flag&_I2C_NO_STOP)==0)
                        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
                }
            }
            else {
                goto ERROR;
            }
        }
    }

    if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK) == SET)
        goto SUCCESS;

    //NOSTOP==1
    if ((flag&_I2C_NO_STOP)!=0&&_i2c_wait_flag(hperh, I2C_STAT_TCR, RESET, 10) == OK)
    {
        goto SUCCESS;
    }

    if (_i2c_wait_flag(hperh, I2C_STAT_TC, RESET, 10) == OK) {
        if ((flag&_I2C_NO_STOP)==0x0)      //NOSTOP==0
            SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        goto SUCCESS;
    }
    else {
        goto ERROR;
    }

ERROR:
    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    hperh->state = I2C_STATE_READY;
    hperh->mode  = I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ERROR;

SUCCESS:
    hperh->state = I2C_STATE_READY;
    hperh->mode  = I2C_MODE_NONE;
    __UNLOCK(hperh);

    return OK;
}

static rt_ssize_t es32f3_master_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->buf==NULL||msg->len==0)
        {
            continue;
        }
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
            uint32_t f=((msg->flags&RT_I2C_NO_START)?0x1:0)|((msg->flags&RT_I2C_NO_STOP)?0x2:0);
            if (I2C_GET_FLAG((i2c_handle_t *)bus->priv, I2C_STAT_BUSY) == RESET)
            {
                f=f&(~_I2C_NO_START);
            }
            if (_i2c_master_send(bus->priv, msg->addr << 1, msg->buf, msg->len, TIMEOUT,f) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
    }

    ret = i;

out:
    LOG_D("send stop condition\n");

    return ret;
}

const struct rt_i2c_bus_device_ops es32f3_i2c_ops =
{
    es32f3_master_xfer,
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

    _i2c_device0.ops = &es32f3_i2c_ops;
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

    _i2c_device1.ops = &es32f3_i2c_ops;
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
