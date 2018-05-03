/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include <rtdevice.h>
#include <rthw.h>
#include "i2c.h"
#include "inc/fh_driverlib.h"
#include "board_info.h"

//#define FH_I2C_DEBUG

#ifdef FH_I2C_DEBUG
#define PRINT_I2C_DBG(fmt, args...)     \
    do                                  \
    {                                   \
        rt_kprintf("FH_I2C_DEBUG: ");   \
        rt_kprintf(fmt, ## args);       \
    }                                   \
    while(0)
#else
#define PRINT_I2C_DBG(fmt, args...)  do { } while (0)
#endif



static void fh_i2c_xfer_init(struct rt_i2c_bus_device *dev, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct i2c_driver *i2c_drv = (struct i2c_driver *)dev->priv;
    struct fh_i2c_obj *i2c_obj = (struct fh_i2c_obj *)i2c_drv->priv;
	rt_uint32_t ic_con;

	/* if the slave address is ten bit address, ERROR*/
    if (msgs[i2c_drv->msg_write_idx].flags & I2C_M_TEN)
    {
        rt_kprintf("ERROR: %s, ten bit address is NOT supported\n", __func__);
        return;
    }

	/* Disable the adapter */
	I2C_WaitMasterIdle(i2c_obj);

	I2C_Enable(i2c_obj, RT_FALSE);

	/* set the slave (target) address */
	I2C_SetSlaveAddress(i2c_obj, msgs[i2c_drv->msg_write_idx].addr);

	/* Enable interrupts */
	I2C_SetInterruptMask(i2c_obj, DW_IC_INTR_DEFAULT_MASK);

    /* Enable the adapter */
    I2C_Enable(i2c_obj, RT_TRUE);
}


static rt_size_t fh_i2c_xfer(struct rt_i2c_bus_device *dev,
		struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct i2c_driver *i2c_drv = (struct i2c_driver *)dev->priv;
    struct fh_i2c_obj *i2c_obj = (struct fh_i2c_obj *)i2c_drv->priv;
    int ret;
	struct rt_i2c_msg *pmsg = RT_NULL;

	PRINT_I2C_DBG(">>>>>>>>>>>>>%s start\n", __func__);

    rt_completion_init(&i2c_drv->transfer_completion);

	ret = rt_mutex_take(i2c_drv->lock, RT_WAITING_FOREVER );

	i2c_drv->msgs = msgs;
	i2c_drv->msgs_num = num;
	i2c_drv->msg_read_idx = 0;
	i2c_drv->msg_write_idx = 0;
	i2c_drv->cmd_err = 0;
	i2c_drv->msg_err = 0;
	i2c_drv->status = STATUS_IDLE;
	i2c_obj->abort_source = 0;

    ret = I2C_WaitDeviceIdle(i2c_obj);
    if (ret < 0)
    {
        //I2C_SetDataCmd(i2c_obj, 0x200);
        //goto done;
    }

	fh_i2c_xfer_init(dev, msgs, num);

	ret = rt_completion_wait(&i2c_drv->transfer_completion, RT_TICK_PER_SECOND);
	PRINT_I2C_DBG("%s transfer finished\n", "rt_completion_wait");
    if(ret)
	{
        rt_kprintf("ERROR: %s, transfer timeout\n", __func__);
        I2C_SetDataCmd(i2c_obj, 0x200);
        I2C_Init(i2c_obj);
		ret = -RT_ETIMEOUT;
		goto done;
	}

	if (i2c_drv->msg_err)
	{
		rt_kprintf("i2c_priv->msg_err: %d\n", i2c_drv->msg_err);
		ret = i2c_drv->msg_err;
		goto done;
	}

	/* no error */
	if (!i2c_drv->cmd_err)
	{
		/* Disable the adapter */
	    I2C_WaitMasterIdle(i2c_obj);
	    I2C_Enable(i2c_obj, RT_FALSE);
		ret = num;
		goto done;
	}

	/* We have an error */
	if (i2c_drv->cmd_err == DW_IC_ERR_TX_ABRT)
	{
		rt_kprintf("ERROR: %s, i2c_priv>cmd_err == DW_IC_ERR_TX_ABRT\n", __func__);
		ret = I2C_HandleTxAbort(i2c_obj);
		goto done;
	}

	ret = 1;

done:
    I2C_Enable(i2c_obj, RT_FALSE);
    rt_mutex_release(i2c_drv->lock);
    PRINT_I2C_DBG(">>>>>>>>>>>>>%s end\n", __func__);
	return ret;

}


/*
 * Initiate (and continue) low level master read/write transaction.
 * This function is only called from i2c_fh_isr, and pumping i2c_msg
 * messages into the tx buffer.  Even if the size of i2c_msg data is
 * longer than the size of the tx buffer, it handles everything.
 */
static void i2c_fh_xfer_msg(struct rt_i2c_bus_device *dev)
{
    struct i2c_driver *i2c_drv = (struct i2c_driver *)dev->priv;
    struct fh_i2c_obj *i2c_obj = (struct fh_i2c_obj *)i2c_drv->priv;
	struct rt_i2c_msg *msgs = i2c_drv->msgs;
	rt_uint32_t intr_mask, cmd;
	int tx_limit, rx_limit;
	rt_uint32_t addr = msgs[i2c_drv->msg_write_idx].addr;
	rt_uint32_t buf_len = i2c_drv->tx_buf_len;
	rt_uint8_t *buf = i2c_drv->tx_buf;

	PRINT_I2C_DBG("%s start, msgs_num: %d, write_idx: %d\n", __func__, i2c_drv->msgs_num, i2c_drv->msg_write_idx);

	intr_mask = DW_IC_INTR_DEFAULT_MASK;

	for (; i2c_drv->msg_write_idx < i2c_drv->msgs_num; i2c_drv->msg_write_idx++)
	{
		/*
		 * if target address has changed, we need to
		 * reprogram the target address in the i2c
		 * adapter when we are done with this transfer
		 */
		if (msgs[i2c_drv->msg_write_idx].addr != addr) {
			rt_kprintf(
					"ERROR: %s, invalid target address\n", __func__);
			i2c_drv->msg_err = 1;
			break;
		}

		if (msgs[i2c_drv->msg_write_idx].len == 0) {
			rt_kprintf(
					"ERROR: %s, invalid message length\n", __func__);
			i2c_drv->msg_err = 1;
			break;
		}

		if (!(i2c_drv->status & STATUS_WRITE_IN_PROGRESS))
		{
			/* new i2c_msg */
			buf = msgs[i2c_drv->msg_write_idx].buf;
			buf_len = msgs[i2c_drv->msg_write_idx].len;

			PRINT_I2C_DBG("new msg: len: %d, buf: 0x%x\n", buf_len, buf[0]);
		}

		tx_limit = i2c_obj->config.tx_fifo_depth - I2C_GetTransmitFifoLevel(i2c_obj);
		rx_limit = i2c_obj->config.rx_fifo_depth - I2C_GetReceiveFifoLevel(i2c_obj);

		while (buf_len > 0 && tx_limit > 0 && rx_limit > 0)
		{
			if (msgs[i2c_drv->msg_write_idx].flags & RT_I2C_RD)
			{
				cmd = 0x100;
				rx_limit--;
			}
			else
			{
				cmd = *buf++;
			}

			tx_limit--; buf_len--;

			if(!buf_len)
			{
			    //2015-11-8 ar0130 bug fixed
			    while(I2C_GetTransmitFifoLevel(i2c_obj));
			    cmd |= 0x200;
			}

			I2C_SetDataCmd(i2c_obj, cmd);
		}

		i2c_drv->tx_buf = buf;
		i2c_drv->tx_buf_len = buf_len;

		if (buf_len > 0)
		{
			/* more bytes to be written */
		    i2c_drv->status |= STATUS_WRITE_IN_PROGRESS;
			break;
		}
		else
		{
		    i2c_drv->status &= ~STATUS_WRITE_IN_PROGRESS;
		}
	}

	/*
	 * If i2c_msg index search is completed, we don't need TX_EMPTY
	 * interrupt any more.
	 */

	if (i2c_drv->msg_write_idx == i2c_drv->msgs_num)
	    intr_mask &= ~DW_IC_INTR_TX_EMPTY;

	if (i2c_drv->msg_err)
	{
	    rt_kprintf("ERROR: %s, msg_err: %d\n", __func__, i2c_drv->msg_err);
	    intr_mask = 0;
	}

	I2C_SetInterruptMask(i2c_obj, intr_mask);

	PRINT_I2C_DBG("%s end\n", __func__);
}

static void i2c_fh_read(struct rt_i2c_bus_device *dev)
{
	struct i2c_driver *i2c_drv = (struct i2c_driver *)dev->priv;
	struct fh_i2c_obj *i2c_obj = (struct fh_i2c_obj *)i2c_drv->priv;
	struct rt_i2c_msg *msgs = i2c_drv->msgs;
	int rx_valid;

	PRINT_I2C_DBG("%s start, msgs_num: %d, read_idx: %d\n", __func__, i2c_drv->msgs_num, i2c_drv->msg_read_idx);

	for (; i2c_drv->msg_read_idx < i2c_drv->msgs_num; i2c_drv->msg_read_idx++)
	{
		rt_uint32_t len;
		rt_uint8_t *buf;

		if (!(msgs[i2c_drv->msg_read_idx].flags & RT_I2C_RD))
		    continue;

		if (!(i2c_drv->status & STATUS_READ_IN_PROGRESS))
		{
			len = msgs[i2c_drv->msg_read_idx].len;
			buf = msgs[i2c_drv->msg_read_idx].buf;
		}
		else
		{
		    PRINT_I2C_DBG("STATUS_READ_IN_PROGRESS\n");
			len = i2c_drv->rx_buf_len;
			buf = i2c_drv->rx_buf;
		}

		rx_valid = I2C_GetReceiveFifoLevel(i2c_obj);

		if(rx_valid == 0)
		{
			rt_kprintf("ERROR: %s, rx_valid == 0\n", __func__);
		}
		PRINT_I2C_DBG("%s, len=%d, rx_valid=%d\n", __func__, len, rx_valid);
		for (; len > 0 && rx_valid > 0; len--, rx_valid--)
		{
			*buf++ = I2C_GetData(i2c_obj);
		}

		PRINT_I2C_DBG("i2c_fh_read, len: %d, buf[0]: 0x%x\n", msgs[i2c_drv->msg_read_idx].len, msgs[i2c_drv->msg_read_idx].buf[0]);

		if (len > 0)
		{
		    PRINT_I2C_DBG("len > 0\n");
			i2c_drv->status |= STATUS_READ_IN_PROGRESS;
			i2c_drv->rx_buf_len = len;
			i2c_drv->rx_buf = buf;
			return;
		}
		else
		    i2c_drv->status &= ~STATUS_READ_IN_PROGRESS;
	}

	PRINT_I2C_DBG("%s end\n", __func__);
}

/*
 * Interrupt service routine. This gets called whenever an I2C interrupt
 * occurs.
 */
static void fh_i2c_interrupt(int this_irq, void *dev_id)
{
    struct i2c_driver *i2c_drv = dev_id;
    struct rt_i2c_bus_device *i2c_bus_dev = i2c_drv->i2c_bus_dev;
    struct fh_i2c_obj *i2c_obj = (struct fh_i2c_obj *)i2c_drv->priv;
	rt_uint32_t stat;

	stat = I2C_ClearAndGetInterrupts(i2c_obj);
	PRINT_I2C_DBG("status: 0x%x, mask: 0x%x\n", stat, I2C_GetInterruptMask(i2c_obj));

	if (stat & DW_IC_INTR_TX_ABRT)
	{
	    PRINT_I2C_DBG("DW_IC_INTR_TX_ABRT\n");
		i2c_drv->cmd_err |= DW_IC_ERR_TX_ABRT;
		i2c_drv->status = STATUS_IDLE;

		/*
		 * Anytime TX_ABRT is set, the contents of the tx/rx
		 * buffers are flushed.  Make sure to skip them.
		 */
		I2C_SetInterruptMask(i2c_obj, 0);
		goto tx_aborted;
	}

	if (stat & DW_IC_INTR_RX_FULL)
	{
		i2c_fh_read(i2c_bus_dev);
	}

	if (stat & DW_IC_INTR_TX_EMPTY)
	{
		i2c_fh_xfer_msg(i2c_bus_dev);
	}

	/*
	 * No need to modify or disable the interrupt mask here.
	 * i2c_fh_xfer_msg() will take care of it according to
	 * the current transmit status.
	 */

tx_aborted:
	if ((stat & (DW_IC_INTR_TX_ABRT | DW_IC_INTR_STOP_DET)) || i2c_drv->msg_err)
	    rt_completion_done(&i2c_drv->transfer_completion);

}

static const struct rt_i2c_bus_device_ops fh_i2c_ops =
{
    .master_xfer = fh_i2c_xfer,
};

int fh_i2c_probe(void *priv_data)
{
    int ret;
    struct i2c_driver *i2c_drv;
    struct rt_i2c_bus_device *i2c_bus_dev;
    struct fh_i2c_obj *i2c_obj = (struct fh_i2c_obj *)priv_data;
    char i2c_dev_name[5] = {0};

    PRINT_I2C_DBG("%s start\n", __func__);

    i2c_bus_dev = (struct rt_i2c_bus_device*)rt_malloc(sizeof(struct rt_i2c_bus_device));
    rt_memset(i2c_bus_dev, 0, sizeof(struct rt_i2c_bus_device));
    i2c_bus_dev->ops = &fh_i2c_ops;

    rt_sprintf(i2c_dev_name, "%s%d", "i2c", i2c_obj->id);
    ret = rt_i2c_bus_device_register(i2c_bus_dev, i2c_dev_name);

    if (ret != RT_EOK)
    {
        rt_kprintf("ERROR:rt_spi_bus_register failed, ret=%d\n", ret);
        return -RT_ENOMEM;
    }

    //priv struct init
    i2c_drv = (struct i2c_driver*)rt_malloc(sizeof(struct i2c_driver));
    rt_memset(i2c_drv, 0, sizeof(struct i2c_driver));

    i2c_drv->i2c_bus_dev = i2c_bus_dev;
    i2c_drv->priv = priv_data;
    i2c_bus_dev->priv = i2c_drv;

    i2c_drv->lock = rt_mutex_create("i2c_mux", RT_IPC_FLAG_FIFO);
    if(i2c_obj->id == 0){
        rt_hw_interrupt_install(i2c_obj->irq, fh_i2c_interrupt,
                                (void *)i2c_drv, "i2c_0");
    }
    else if(i2c_obj->id == 1){
        rt_hw_interrupt_install(i2c_obj->irq, fh_i2c_interrupt,
                                (void *)i2c_drv, "i2c_1");
    }

    rt_hw_interrupt_umask(i2c_obj->irq);

    //fixme: get from clk tree
    i2c_obj->input_clock = 15000;

    I2C_Init(i2c_obj);

    PRINT_I2C_DBG("%s end\n", __func__);
    return ret;

}

int fh_i2c_exit(void *priv_data)
{
    return 0;
}

struct fh_board_ops i2c_driver_ops =
{
    .probe = fh_i2c_probe,
    .exit = fh_i2c_exit,
};

void rt_hw_i2c_init(void)
{
    int ret;

    PRINT_I2C_DBG("%s start\n", __func__);
    fh_board_driver_register("i2c", &i2c_driver_ops);
    PRINT_I2C_DBG("%s end\n", __func__);
    //fixme: never release?
}

static rt_err_t fh_i2c_read_reg(struct rt_i2c_bus_device *fh81_i2c,
		rt_uint16_t reg, rt_uint8_t *data) {
	struct rt_i2c_msg msg[2];
	rt_uint8_t send_buf[2];
	rt_uint8_t recv_buf[1] = {0};

	PRINT_I2C_DBG("%s start\n", __func__);

	//  send_buf[0] = ((reg >> 8) & 0xff);
	send_buf[0] = (reg & 0xFF);

	msg[0].addr = 0x51;
	msg[0].flags = RT_I2C_WR;
	msg[0].len = 1;
	msg[0].buf = send_buf;

	msg[1].addr = 0x51;
	msg[1].flags = RT_I2C_RD;
	msg[1].len = 1;
	msg[1].buf = recv_buf;

	rt_i2c_transfer(fh81_i2c, msg, 2);
	*data = recv_buf[0];
	return RT_EOK;
}
static rt_err_t fh_i2c_write_reg(struct rt_i2c_bus_device *fh81_i2c,
		rt_uint16_t reg, rt_uint8_t data) {
	struct rt_i2c_msg msg;
	rt_uint8_t send_buf[3];

	PRINT_I2C_DBG("%s start\n", __func__);

	// send_buf[0] = ((reg >> 8) & 0xff);
	send_buf[1] = (reg & 0xFF);
	send_buf[2] = data;

	msg.addr = 0x51;
	msg.flags = RT_I2C_WR;
	msg.len = 2;
	msg.buf = send_buf;

	rt_i2c_transfer(fh81_i2c, &msg, 1);
	PRINT_I2C_DBG("%s end\n", __func__);
	return RT_EOK;
}

void i2c_test_sensor() {
	struct rt_i2c_bus_device *fh81_i2c;
	struct rt_i2c_msg msg[2];
	rt_uint8_t data[1] = { 0x00 };

	fh81_i2c = rt_i2c_bus_device_find("i2c1");

	fh_i2c_write_reg(fh81_i2c, 0x04, 0x02);

	fh_i2c_read_reg(fh81_i2c, 0x02, data);

	rt_kprintf("data read from 0x3038 is 0x%x\r\n", data[0]);
	PRINT_I2C_DBG("%s end\n", __func__);
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(i2c_test_sensor, sensor i2c test);
#endif

