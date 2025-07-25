 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include <sys_clk.h>
#include <drv/iic.h>
#include <drv/irq.h>
#include <drv/dma.h>
#include <drv/tick.h>
#include <drv/porting.h>

extern uint16_t iic_tx_hs_num[];
extern uint16_t iic_rx_hs_num[];

///< TODO：IIC_EEPROM_MAX_WRITE_LEN需要根据实际情况进行设置
#define IIC_EEPROM_MAX_WRITE_LEN     0x1U ///< IIC的eeprom的最大可写长度
///< TODO：IIC_MAX_FIFO需要根据实际情况进行设置
#define IIC_MAX_FIFO                    0x8U ///< IIC的FIFO的最大深度

void dw_iic_slave_tx_handler(void *arg)
{
    CSI_PARAM_CHK_NORETVAL(arg);

    ///< TODO：清除中断并获取中断状态

    ///< TODO：根据中断状态发送数据
    ///< TODO：根据中断状态处理异常并执行用户回调函数

}

void dw_iic_tx_handler(void *arg)
{
    CSI_PARAM_CHK_NORETVAL(arg);

    ///< TODO：清除中断并获取中断状态

    ///< TODO：根据中断状态发送数据
    ///< TODO：根据中断状态处理异常并执行用户回调函数
}

void dw_iic_rx_handler(void *arg)
{
    CSI_PARAM_CHK_NORETVAL(arg);

    ///< TODO：清除中断并获取中断状态

    ///< TODO：根据中断状态接收数据
    ///< TODO：根据中断状态处理异常并执行用户回调函数
}

void dw_iic_slave_rx_handler(void *arg)
{
    CSI_PARAM_CHK_NORETVAL(arg);

    ///< TODO：清除中断并获取中断状态

    ///< TODO：根据中断状态接收数据
    ///< TODO：根据中断状态处理异常并执行用户回调函数

}

/**
  \brief       start slave mode dma send data
  \param[in]   iic handle of iic instance
*/
void iic_slave_send_data_with_dma_irq(void *arg)
{
    CSI_PARAM_CHK_NORETVAL(arg);

    ///< TODO：清除中断并获取中断状态
    ///< TODO：清除IIC所有的中断
    ///< TODO：关闭IIC所有的中断

    ///< TODO：根据中断状态用DMA模式发送数据
}

static void dw_iic_dma_event_cb(csi_dma_ch_t *dma, csi_dma_event_t event, void *arg)
{
    CSI_PARAM_CHK_NORETVAL(dma);

    ///< TODO：根据DMA传输的状态处理异常事件并调用用户回调函数
    ///< TODO：根据DMA传输的状态处理DMA传输完成事件并调用用户回调函数
}
/**
  \brief       Init IIC ctrl block
               1. Initializes the resources needed for the IIC instance
               2.registers event callback function and user param for the callback
  \param[in]   iic handle of iic instance
  \param[in]   idx index of instance
  \param[in]   cb  event callback function \ref csi_iic_event_cb_t
  \param[in]   arg user private param  for event callback
  \return      \ref csi_error_t
*/
csi_error_t csi_iic_init(csi_iic_t *iic, uint32_t idx)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    ret = target_get(DEV_DW_IIC_TAG, idx, &iic->dev);

    if (ret == 0) {
        ///< TODO：把IIC从机地址设置为0
        ///< TODO：关闭IIC
        ///< TODO：清除IIC所有的中断
        ///< TODO：关闭IIC所有的中断
        ///< TODO：设置IIC从机在接收到来自主机的读取请求时不刷新FIFO中的数据
    }

    iic->state.writeable = 1U;
    iic->state.readable  = 1U;
    iic->state.error     = 0U;
    iic->send = NULL;
    iic->receive = NULL;
    iic->rx_dma = NULL;
    iic->tx_dma = NULL;
    iic->callback = NULL;

    return ret;

}

/**
  \brief       De-initialize IIC Instanc
               stops operation and releases the software resources used by the Instance
  \param[in]   iic handle of iic instance
  \return      \ref csi_error_t
*/
void csi_iic_uninit(csi_iic_t *iic)
{
    CSI_PARAM_CHK_NORETVAL(iic);

    iic->state.error     = 0U;
    iic->state.writeable = 0U;
    iic->state.readable  = 0U;
    iic->send            = NULL;
    iic->receive         = NULL;
    iic->rx_dma          = NULL;
    iic->tx_dma          = NULL;

    ///< TODO：关闭IIC所有的中断
    ///< TODO：清除IIC所有的中断
    ///< TODO：关闭IIC

    // 禁止中断控制器对应的中断，注销中断服务函数
    csi_irq_disable((uint32_t)iic->dev.irq_num);
    csi_irq_detach((uint32_t)iic->dev.irq_num);
}

/**
  \brief      config iic master or slave mode
  \param[in]  iic    handle of iic instance
  \param[in]  mode   iic mode \ref csi_iic_mode_t
  \return     \ref csi_error_t
*/
csi_error_t csi_iic_mode(csi_iic_t *iic, csi_iic_mode_t mode)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;

    if (mode == IIC_MODE_MASTER) {
        iic->mode = IIC_MODE_MASTER;

        ///< TODO：设置IIC为主机模式

        ret = CSI_OK;
    } else if (mode == IIC_MODE_SLAVE) {
        iic->mode = IIC_MODE_SLAVE;

        ///< TODO：设置IIC为从机模式

        ret = CSI_OK;
    }

    return ret;
}

/**
  \brief      config iic addr mode
  \param[in]  iic        handle of iic instance
  \param[in]  addr_mode  iic addr mode
  \return     \ref csi_error_t
*/
csi_error_t csi_iic_addr_mode(csi_iic_t *iic, csi_iic_addr_mode_t addr_mode)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;

    if (addr_mode == IIC_ADDRESS_7BIT) {

        ///< TODO：设置主机地址为7位
        ///< TODO：设置从机地址为7位

        ret = CSI_OK;
    } else if (addr_mode == IIC_ADDRESS_10BIT) {

        ///< TODO：设置主机地址为10位
        ///< TODO：设置从机地址为10位

        ret = CSI_OK;
    }

    return ret;
}

/**
  \brief      config iic speed
  \param[in]  iic    handle of iic instance
  \param[in]  speed  iic speed mode
  \return     \ref csi_error_t
*/
csi_error_t csi_iic_speed(csi_iic_t *iic, csi_iic_speed_t speed)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;

    if (speed == IIC_BUS_SPEED_STANDARD) {

        ///< TODO：设置IIC为标准模式,100KHZ
        ///< TODO：获取IIC使用的频率
        ///< TODO：标准模式设置SCL时钟的高周期计数
        ///< TODO：标准模式设置SCL时钟的低周期计数

        ret = CSI_OK;
    } else if (speed == IIC_BUS_SPEED_FAST) {

        ///< TODO：设置IIC为快速模式,400KHz
        ///< TODO：获取IIC使用的频率
        ///< TODO：快速模式设置SCL时钟的高周期计数
        ///< TODO：快速模式设置SCL时钟的低周期计数

        ret = CSI_OK;
    } else if (speed == IIC_BUS_SPEED_FAST_PLUS) {
        ///< TODO：设置IIC为快速+模式,1MHz
        ///< TODO：获取IIC使用的频率
        ///< TODO：快速模式+设置SCL时钟的高周期计数
        ///< TODO：快速模式+设置SCL时钟的低周期计数
    } else if (speed == IIC_BUS_SPEED_HIGH) {

        ///< TODO：设置IIC为高速模式,3.4MHz
        ///< TODO：获取IIC使用的频率
        ///< TODO：高速模式设置SCL时钟的高周期计数
        ///< TODO：高速模式设置SCL时钟的低周期计数

        ret = CSI_OK;
    }

    return ret;
}

/**
  \brief      config iic own addr
  \param[in]  iic      handle of iic instance
  \param[in]  own_addr own addr
  \return     \ref csi_error_t
*/
csi_error_t csi_iic_own_addr(csi_iic_t *iic, uint32_t own_addr)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< TODO：设置IIC从机的地址，注意该配置只在SLAVE模式下生效

    return ret;
}

/**
  \brief       Start sending data as IIC Master.
               This function is blocking
  \param[in]   iic            handle of iic instance
  \param[in]   devaddr        addrress of slave device
  \param[in]   data           data to send to IIC Slave
  \param[in]   size           size of data items to send
  \param[in]   timout         unit of time delay
  \return      master send real size and error code
*/
int32_t csi_iic_master_send(csi_iic_t *iic, uint32_t devaddr, const void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    int32_t send_count = 0;
    uint8_t *send_data = (void *)data;

    if ((send_data == NULL) || (size == 0U)) {
        send_count = (int32_t)CSI_ERROR;
    } else {

        ///< TODO：关闭IIC
        ///< TODO：设置IIC从设备地址
        ///< TODO：打开IIC
        ///< TODO：发送数据
        ///< TODO：超时则超时退出

    }

    return send_count;
}

/**
  \brief       Start receiving data as IIC Master.
               This function is blocking
  \param[in]   iic      handle to operate.
  \param[in]   devaddr  iic addrress of slave device.
  \param[out]  data     Pointer to buffer for data to receive from IIC receiver
  \param[in]   size     size of data items to receive
  \param[in]   timeout  unit of time delay
  \return      master receive real size and error code
*/
int32_t csi_iic_master_receive(csi_iic_t *iic, uint32_t devaddr, void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    int32_t read_count = 0;
    uint8_t *receive_data = (void *)data;

    if ((receive_data == NULL) || (size == 0U)) {
        read_count = (int32_t)CSI_ERROR;
    } else {

        ///< TODO：关闭IIC
        ///< TODO：设置IIC从设备地址
        ///< TODO：打开IIC

        ///< TODO：配置IIC为接收数据
        ///< TODO：等待IIC接收数据，超时则超时退出
        ///< TODO：读数据寄存器接收数据

    }

    return read_count;
}

static csi_error_t iic_master_send_intr(csi_iic_t *iic, uint32_t devaddr, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if ((data == NULL) || (size == 0U)) {
        ret = CSI_ERROR;
    } else {
        if (iic->state.writeable == 0U) {
            ret = CSI_BUSY;
        } else {

            ///< TODO：设置IIC从设备地址

            iic->data            = (uint8_t *)data;
            iic->size            = size;
            iic->state.writeable = 0U;

            ///< TODO：关闭IIC
            ///< TODO：清除IIC所有的中断
            ///< TODO：关闭IIC所有的中断
            ///< TODO：使能发送中断
            ///< TODO：设置发送FIFO的触发级别
            ///< TODO：打开IIC

        }
    }

    return ret;
}

static csi_error_t iic_master_send_dma(csi_iic_t *iic, uint32_t devaddr, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    csi_dma_ch_config_t config;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));
    csi_dma_ch_t *dma_ch = (csi_dma_ch_t *)iic->tx_dma;

    iic->data = (void *)data;
    iic->size = size;
    iic->state.writeable = 0U;

    ///< TODO：关闭IIC
    ///< TODO：清除IIC所有的中断
    ///< TODO：关闭IIC所有的中断
    ///< TODO：设置IIC从设备地址
    ///< TODO：使能IIC的DMA发送
    ///< TODO：设置DMA传输的触发级别

    config.src_inc = DMA_ADDR_INC;
    config.dst_inc = DMA_ADDR_CONSTANT;
    config.src_tw = DMA_DATA_WIDTH_8_BITS;
    config.dst_tw = DMA_DATA_WIDTH_8_BITS;
    config.trans_dir = DMA_MEM2PERH;
    config.handshake = iic_tx_hs_num[iic->dev.idx];

    ///< 配置DMA通道
    csi_dma_ch_config(dma_ch, &config);

    soc_dcache_clean_invalid_range((unsigned long)iic->data, iic->size);

    ///< TODO：调用csi_dma_ch_start开启IIC使用的DMA通道
    ///< TODO：打开IIC

    return ret;
}

/**
  \brief       Start sending data as IIC Master.
               This function is non-blocking,\ref csi_iic_event_e is signaled when transfer completes or error happens.
  \param[in]   iic            handle to operate.
  \param[in]   devaddr        iic addrress of slave device. |_BIT[7:1]devaddr_|_BIT[0]R/W_|
                              eg: BIT[7:0] = 0xA0, devaddr = 0x50.
  \param[in]   data           data to send to IIC Slave
  \param[in]   num            size of data items to send
  \return      \ref csi_error_t
*/
csi_error_t csi_iic_master_send_async(csi_iic_t *iic, uint32_t devaddr, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    csi_iic_master_send_async_t send_func;

    if (iic->send) {
        send_func = iic->send;
        send_func(iic, devaddr, data, size);
    } else {
        ///< 注册发送中断服务函数、打开中断控制器对应的中断
        csi_irq_attach((uint32_t)iic->dev.irq_num, &dw_iic_tx_handler, &iic->dev);
        csi_irq_enable((uint32_t)iic->dev.irq_num);

        ///< 开始IIC主机模式以中断方式发送数据
        iic_master_send_intr(iic, devaddr, data, size);
    }

    return ret;
}

static csi_error_t iic_master_receive_intr(csi_iic_t  *iic, uint32_t devaddr, void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if ((data == NULL) || (size == 0U)) {
        ret = CSI_ERROR;
    } else {
        if (iic->state.readable == 0U) {
            ret = CSI_BUSY;
        } else {

            iic->data                = (uint8_t *)data;
            iic->size                = size;
            iic->state.readable      = 0U;
            unsigned long temp = size;
            iic->priv = (void *)temp;       ///< iic->priv used to record the transmission value

            ///< TODO：关闭IIC
            ///< TODO：清除IIC所有的中断
            ///< TODO：关闭IIC所有的中断
            ///< TODO：设置IIC从设备地址
            ///< TODO：IIC使能主机接收中断
            ///< TODO：打开IIC
        }
    }

    return ret;
}

/**
  \brief       Start receiving data as IIC Master.
               This function is non-blocking,\ref csi_iic_event_t is signaled when transfer completes or error happens.
               \ref csi_iic_get_status can get operating status.
  \param[in]   iic            handle to operate.
  \param[in]   devaddr        iic addrress of slave device.
  \param[out]  data           pointer to buffer for data to receive from IIC receiver
  \param[in]   size           size of data items to receive
  \return      \ref csi_error_t
*/
csi_error_t csi_iic_master_receive_async(csi_iic_t  *iic, uint32_t devaddr, void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    /*the hardware only support master send with dma and master receive only use interrupt*/
    ///< 注册发送中断服务函数、打开中断控制器对应的中断
    csi_irq_attach((uint32_t)iic->dev.irq_num, &dw_iic_rx_handler, &iic->dev);
    csi_irq_enable((uint32_t)iic->dev.irq_num);

    ///< 开始IIC主机模式以中断方式接收数据
    ret = iic_master_receive_intr(iic, devaddr, data, size);
    return ret;
}

/**
  \brief       Start transmitting data as IIC Master.
               This function is blocking
  \param[in]   iic            handle of iic instance
  \param[in]   devaddr        addrress of slave device
  \param[in]   memaddr        internal addr of device
  \param[in]   memaddr_size   internal addr mode of device
  \param[in]   data           data to send to IIC Slave
  \param[in]   size           size of data items to send
  \param[in]   timout         unit of time delay
  \return      memory send real size and error code
*/
int32_t csi_iic_mem_send(csi_iic_t *iic, uint32_t devaddr, uint16_t memaddr, csi_iic_mem_addr_size_t memaddr_size, const void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    int32_t send_count = 0;
    uint8_t *send_data = (void *)data;
    uint8_t mem_addr_flag = 1U;
    uint8_t page_inx = 0U;

    if ((send_data == NULL) || (size == 0U)) {
        send_count = (int32_t)CSI_ERROR;
    } else {

        ///< TODO：关闭IIC
        ///< TODO：设置IIC从设备地址
        ///< TODO：打开IIC

        if (memaddr_size == IIC_MEM_ADDR_SIZE_8BIT) {

            ///< TODO：IIC发送设备内部地址
            ///< TODO：等待发送完成，超时则超时退出

            if (ret != CSI_OK) {
                send_count = (int32_t)ret;
                mem_addr_flag = 0U;
            }
        }

        if (memaddr_size == IIC_MEM_ADDR_SIZE_16BIT) {

            ///< TODO：IIC通过两次写数据寄存器发送设备内部16位的地址
            ///< TODO：等待发送完成，超时则超时退出

            if (ret != CSI_OK) {
                send_count = (int32_t)ret;
                mem_addr_flag = 0U;
            }
        }

        while (mem_addr_flag) {

            ///< TODO：IIC发送数据
            ///< TODO：等待发送完成，超时则超时退出

            if (ret != CSI_OK) {
                send_count = (int32_t)ret;
                break;
            }

            send_count ++;
            page_inx ++;

            if ((page_inx == IIC_EEPROM_MAX_WRITE_LEN) && (send_count != (int32_t)size)) {
                page_inx = 0U;
                memaddr = memaddr + IIC_EEPROM_MAX_WRITE_LEN;

                if (memaddr_size == IIC_MEM_ADDR_SIZE_8BIT) {

                    ///< TODO：IIC发送设备内部地址
                    ///< TODO：等待发送完成，超时则超时退出

                    if (ret != CSI_OK) {
                        send_count = (int32_t)ret;
                        mem_addr_flag = 0U;
                    }
                }

                if (memaddr_size == IIC_MEM_ADDR_SIZE_16BIT) {

                    ///< TODO：IIC通过两次写数据寄存器发送设备内部16位的地址
                    ///< TODO：等待发送完成，超时则超时退出

                    if (ret != CSI_OK) {
                        send_count = (int32_t)ret;
                        mem_addr_flag = 0U;
                    }
                }

            }

        }
    }

    return send_count;
}

/**
  \brief       Start receiving data as IIC Master.
               This function is blocking
  \param[in]   iic            handle to operate.
  \param[in]   devaddr        iic addrress of slave device.
  \param[in]   memaddr        internal addr of device
  \param[in]   memaddr_mode   internal addr mode of device
  \param[out]  data           Pointer to buffer for data to receive from IIC receiver
  \param[in]   size           size of data items to receive
  \param[in]   timeout        unit of time delay
  \return      memory receive real size and error code
*/
int32_t csi_iic_mem_receive(csi_iic_t *iic, uint32_t devaddr, uint16_t memaddr, csi_iic_mem_addr_size_t memaddr_size, void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    int32_t read_count = 0;
    uint8_t *receive_data = (void *)data;
    uint8_t mem_addr_flag = 1U;

    if ((receive_data == NULL) || (size == 0U)) {
        read_count = (int32_t)CSI_ERROR;
    } else {

        ///< TODO：关闭IIC
        ///< TODO：设置IIC从设备地址
        ///< TODO：打开IIC

        if (memaddr_size == IIC_MEM_ADDR_SIZE_8BIT) {

            ///< TODO：IIC发送设备内部地址
            ///< TODO：等待发送完成，超时则超时退出

            if (ret != CSI_OK) {
                mem_addr_flag = 0U;
            }
        }

        if (memaddr_size == IIC_MEM_ADDR_SIZE_16BIT) {

            ///< TODO：IIC通过两次写数据寄存器发送设备内部16位的地址
            ///< TODO：等待发送完成，超时则超时退出

            if (ret != CSI_OK) {
                mem_addr_flag = 0U;
            }
        }

        uint32_t cmd_num;

        if (mem_addr_flag == 1U) {
            if (size < IIC_MAX_FIFO) {
                for (read_count = 0; read_count < (int32_t)size; read_count++) {
                    ///< TODO：设置IIC为接收数据模式
                }

                ///< TODO：等待接收数据，超时则超时退出

                if (ret == CSI_OK) {
                    for (read_count = 0; read_count < (int32_t)size; read_count++) {
                        ///< TODO：IIC读数据寄存器接收数据
                    }
                } else {
                    read_count = (int32_t)ret;
                }

            } else {
                read_count = 0;

                for (cmd_num = size; cmd_num > (size - IIC_MAX_FIFO); cmd_num--) {
                    ///< TODO：设置IIC为接收数据模式
                }

                while (mem_addr_flag) {

                    ///< TODO：等待接收数据，超时则超时退出

                    if (ret != CSI_OK) {
                        read_count = (int32_t)ret;
                        break;
                    }

                    ///< TODO：IIC读数据寄存器接收数据

                    read_count ++;

                    if (cmd_num > 0U) {

                        ///< TODO：设置IIC为接收数据模式

                        cmd_num --;
                    }
                }
            }
        } else {
            read_count = (int32_t)CSI_ERROR;
        }

    }

    return read_count;
}

/**
  \brief       Start sending data as IIC Slave.
               This function is blocking
  \param[in]   iic      handle to operate.
  \param[in]   data     Pointer to buffer with data to transmit to IIC Master
  \param[in]   size     size of data items to send
  \param[in]   timeout  uint in mini-second
  \return      slave send real size and error code
*/
int32_t csi_iic_slave_send(csi_iic_t *iic, const void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    int32_t send_count = 0;
    uint8_t *send_data = (void *)data;

    if ((send_data == NULL) || (size == 0U)) {
        send_count = (int32_t)CSI_ERROR;
    } else {

        ///< TODO：打开IIC
        ///< TODO：超时则退出
        ///< TODO：获取原始中断的状态
        ///< TODO：根据中断的状态IIC写数据寄存器发送数据
        ///< TODO：等待发送完成，超时则超时退出
    }

    return send_count;
}

/**
  \brief       Start receiving data as IIC Slave.
               This function is blocking
  \param[in]   iic     handle to operate.
  \param[out]  data    Pointer to buffer for data to receive from IIC Master
  \param[in]   size    size of data items to receive
  \param[in]   timeout uint in mini-second
  \return      slave receive real size and error code
*/
int32_t csi_iic_slave_receive(csi_iic_t *iic, void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    int32_t read_count = 0;
    uint8_t *receive_data = (void *)data;

    if ((receive_data == NULL) || (size == 0U)) {
        read_count = (int32_t)CSI_ERROR;
    } else {

        ///< TODO：打开IIC

        while (1) {
            ///< TODO：等待接收数据，超时则超时退出

            if (ret != CSI_OK) {
                read_count = (int32_t)ret;
                break;
            }

            ///< TODO：IIC读数据寄存器发送数据
            read_count ++;

            if (read_count == (int32_t)size) {
                break;
            }
        }
    }

    return read_count;
}

static csi_error_t iic_slave_send_dma(csi_iic_t *iic, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    csi_dma_ch_config_t config;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));
    csi_dma_ch_t *dma_ch = (csi_dma_ch_t *)iic->tx_dma;

    iic->data = (void *)data;
    iic->size = size;
    iic->state.writeable = 0U;

    ///< TODO：关闭IIC
    ///< TODO：清除IIC所有的中断
    ///< TODO：关闭IIC所有的中断
    ///< TODO：IIC从机使能发送中断

    ///< 注册DMA发送完成中断服务函数、打开中断控制器对应的中断
    csi_irq_attach((uint32_t)iic->dev.irq_num, &iic_slave_send_data_with_dma_irq, &iic->dev); ///< if use slave send dma attach will change
    csi_irq_enable((uint32_t)iic->dev.irq_num);

    config.src_inc = DMA_ADDR_INC;
    config.dst_inc = DMA_ADDR_CONSTANT;
    config.src_tw = DMA_DATA_WIDTH_8_BITS;
    config.dst_tw = DMA_DATA_WIDTH_8_BITS;
    config.trans_dir = DMA_MEM2PERH;
    config.handshake = iic_tx_hs_num[iic->dev.idx];

    ///< 配置DMA通道
    csi_dma_ch_config(dma_ch, &config);

    ///< TODO：打开IIC

    return ret;
}

static csi_error_t iic_slave_send_intr(csi_iic_t *iic, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if ((data == NULL) || (size == 0U)) {
        ret = CSI_ERROR;
    } else {
        if (iic->state.writeable == 0U) {
            ret = CSI_BUSY;
        } else {

            iic->data              = (uint8_t *)data;
            iic->size              = size;
            iic->state.writeable   = 0U;

            ///< TODO：关闭IIC
            ///< TODO：清除IIC所有的中断
            ///< TODO：关闭IIC所有的中断
            ///< TODO：IIC从机使能发送中断
            ///< TODO：打开IIC
        }
    }

    return ret;
}

/**
\brief       Start transmitting data as IIC Slave.
             This function is non-blocking,\ref csi_iic_event_t is signaled when transfer completes or error happens.
\param[in]   iic       handle to operate.
\param[in]   data      Pointer to buffer with data to transmit to IIC Master
\param[in]   size      size of data items to send
\return      \ref csi_error_t
*/
csi_error_t csi_iic_slave_send_async(csi_iic_t *iic, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    csi_iic_slave_send_async_t send_func;

    if (iic->send) {
        send_func = iic->send;
        ///< 注册发送中断服务函数、使能中断控制器对应的中断
        csi_irq_attach((uint32_t)iic->dev.irq_num, &iic_slave_send_data_with_dma_irq, &iic->dev);
        csi_irq_enable((uint32_t)iic->dev.irq_num);
        send_func(iic, data, size);
    } else {
        ///< 注册发送中断服务函数、使能中断控制器对应的中断
        csi_irq_attach((uint32_t)iic->dev.irq_num, &dw_iic_slave_tx_handler, &iic->dev);
        csi_irq_enable((uint32_t)iic->dev.irq_num);

        ///< 开始IIC从机模式以中断方式发送数据
        iic_slave_send_intr(iic, data, size);
    }

    return ret;
}

static csi_error_t iic_slave_receive_intr(csi_iic_t *iic, void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if ((data == NULL) || (size == 0U)) {
        ret =  CSI_ERROR;
    } else {
        if (iic->state.readable == 0U) {
            ret = CSI_BUSY;
        } else {

            iic->data            = (uint8_t *)data;
            iic->size            = size;
            iic->state.readable  = 0U;

            ///< TODO：关闭IIC
            ///< TODO：清除IIC所有的中断
            ///< TODO：关闭IIC所有的中断
            ///< TODO：使能IIC从机接收中断

            ///< TODO：打开IIC
        }
    }

    return ret;
}

static csi_error_t iic_slave_receive_dma(csi_iic_t *iic, void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    csi_dma_ch_config_t config;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));
    csi_dma_ch_t *dma = (csi_dma_ch_t *)iic->rx_dma;

    iic->data = (uint8_t *)data;
    iic->size = size;
    iic->state.readable = 0U;

    ///< TODO：关闭IIC
    ///< TODO：清除IIC所有的中断
    ///< TODO：关闭IIC所有的中断
    ///< TODO：IIC DMA接收模式的使能
    ///< TODO：设置IIC DMA模式接收数据的触发级别

    config.src_inc = DMA_ADDR_CONSTANT;
    config.dst_inc = DMA_ADDR_INC;
    config.src_tw = DMA_DATA_WIDTH_8_BITS;
    config.dst_tw = DMA_DATA_WIDTH_8_BITS;
    config.trans_dir = DMA_PERH2MEM;
    config.handshake = iic_rx_hs_num[iic->dev.idx];

    ///< 配置DMA通道
    csi_dma_ch_config(dma, &config);

    soc_dcache_clean_invalid_range((unsigned long)iic->data, iic->size);

    ///< TODO：调用csi_dma_ch_start开启IIC使用的DMA的通道
    ///< TODO：打开IIC

    return ret;
}

/**
\brief       Start receiving data as IIC Slave.
             This function is non-blocking,\ref iic_event_e is signaled when transfer completes or error happens.
\param[in]   handle  iic handle to operate.
\param[out]  data    Pointer to buffer for data to receive from IIC Master
\param[in]   size    size of data items to receive
\return      \ref csi_error_t
*/
csi_error_t csi_iic_slave_receive_async(csi_iic_t *iic, void *data, uint32_t size)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    csi_iic_slave_receive_async_t receive_func;

    if (iic->receive) {
        receive_func = iic->receive;
        receive_func(iic, data, size);
    } else {
        ///< 初始化接收中断服务函数、使能中断控制器对应的中断
        csi_irq_attach((uint32_t)iic->dev.irq_num, &dw_iic_slave_rx_handler, &iic->dev);
        csi_irq_enable((uint32_t)iic->dev.irq_num);

        ///< TODO：开始IIC从机模式以中断方式发送数据
        iic_slave_receive_intr(iic, data, size);
    }

    return ret;
}

/**
\brief       Attach callback to the iic
\param[in]   iic          iic handle to operate.
\param[in]   cb           event callback function \ref csi_iic_callback_t
\param[in]   arg          user private param  for event callback
\return      \ref csi_error_t
*/
csi_error_t csi_iic_attach_callback(csi_iic_t *iic, void *callback, void *arg)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    iic->callback = callback;
    iic->arg = arg;
    return ret;
}

/**
\brief       detach callback from the iic
\param[in]   iic          iic handle to operate.
*/
void csi_iic_detach_callback(csi_iic_t *iic)
{
    CSI_PARAM_CHK_NORETVAL(iic);
    iic->callback = NULL;
    iic->arg = NULL;
    iic->send = NULL;
    iic->receive = NULL;
    ///< 禁止中断控制器对应的中断、注销中断服务函数
    csi_irq_disable((uint32_t)iic->dev.irq_num);
    csi_irq_detach((uint32_t)iic->dev.irq_num);
}

/**
\brief       config iic stop to generate
\param[in]   iic        iic handle to operate.
\param[in]   enable     Transfer operation is pending - Stop condition will not be generated.
\return      \ref csi_error_t
*/
csi_error_t csi_iic_xfer_pending(csi_iic_t *iic, bool enable)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_UNSUPPORTED;
    return ret;
}

/**
  \brief       link DMA channel to iic device
  \param[in]   iic handle to operate.
  \param[in]   tx_dma the DMA channel handle for send, when it is NULL means to unlink the channel
  \param[in]   rx_dma the DMA channel handle for receive, when it is NULL means to unlink the channel
  \return      error code
*/
csi_error_t csi_iic_link_dma(csi_iic_t *iic, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;

    if (iic->callback != NULL) {
        if (iic->mode == IIC_MODE_MASTER) {
            /*the hardware only support master send with dma and master receive only use interrupt*/
            if (tx_dma != NULL) {
                tx_dma->parent = iic;
                ///< 申请DMA通道
                ret = csi_dma_ch_alloc(tx_dma, -1, -1);

                if (ret == CSI_OK) {
                    ///< 注册DMA中断服务函数
                    csi_dma_ch_attach_callback(tx_dma, dw_iic_dma_event_cb, NULL);
                    iic->tx_dma = tx_dma;
                    ///< 注册IIC主机模式以DMA模式发送数据函数
                    iic->send = iic_master_send_dma;
                } else {
                    tx_dma->parent = NULL;
                }
            } else {
                if (iic->tx_dma) {
                    ///< 注销DMA中断服务函数和释放DMA通道
                    csi_dma_ch_detach_callback(iic->tx_dma);
                    csi_dma_ch_free(iic->tx_dma);
                    ///< 注册IIC主机模式以中断模式发送数据函数
                    iic->send = iic_master_send_intr;
                    iic->tx_dma = NULL;
                }

                ret = CSI_OK;
            }
        } else if (iic->mode == IIC_MODE_SLAVE) {
            /*the hardware only support slave receive with dma and slave send only use interrupt*/
            if (tx_dma != NULL) {
                tx_dma->parent = iic;
                ///< 申请DMA通道
                ret = csi_dma_ch_alloc(tx_dma, -1, -1);

                if (ret == CSI_OK) {
                    ///< 注册DMA中断服务函数
                    csi_dma_ch_attach_callback(tx_dma, dw_iic_dma_event_cb, NULL);
                    iic->tx_dma = tx_dma;
                    ///< 注册IIC主机模式以DMA模式发送数据函数
                    iic->send = iic_slave_send_dma;
                } else {
                    tx_dma->parent = NULL;
                }
            } else {
                if (iic->tx_dma) {
                    ///< 注销DMA中断服务函数和释放DMA通道
                    csi_dma_ch_detach_callback(iic->tx_dma);
                    csi_dma_ch_free(iic->tx_dma);
                    ///< 注册IIC从机模式以中断模式发送数据函数
                    iic->send = iic_slave_send_intr;
                    iic->tx_dma = NULL;
                }

                ret = CSI_OK;
            }

            if (rx_dma != NULL) {
                rx_dma->parent = iic;
                ///< 申请DMA通道
                ret = csi_dma_ch_alloc(rx_dma, -1, -1);

                if (ret == CSI_OK) {
                    iic->rx_dma = rx_dma;
                    ///< 注册DMA中断服务函数
                    csi_dma_ch_attach_callback(rx_dma, dw_iic_dma_event_cb, NULL);
                    ///< 注册IIC从机模式以DMA模式发送数据函数
                    iic->receive = iic_slave_receive_dma;
                } else {
                    rx_dma->parent = NULL;
                }
            } else {
                if (iic->rx_dma) {
                    ///< 注销DMA中断服务函数和释放DMA通道
                    csi_dma_ch_detach_callback(iic->rx_dma);
                    csi_dma_ch_free(iic->rx_dma);
                    ///< 注册IIC从机模式以中断模式发送数据函数
                    iic->receive = iic_slave_receive_intr;
                    iic->rx_dma = NULL;
                }

                ret = CSI_OK;
            }
        }
    }

    return ret;
}

/**
\brief       start receiving data as IIC Slave.
             This function is non-blocking,\ref iic_event_e is signaled when transfer completes or error happens.
\param[in]   iic   handle to operate.
\param[out]  state iic state \ref csi_state_t
\return      \ref csi_error_t
*/
csi_error_t csi_iic_get_state(csi_iic_t *iic, csi_state_t *state)
{
    CSI_PARAM_CHK(iic, CSI_ERROR);
    CSI_PARAM_CHK(state, CSI_ERROR);
    *state = iic->state;
    return CSI_OK;
}

#ifdef CONFIG_PM
static csi_error_t dw_iic_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;

    switch (action) {
        case PM_DEV_SUSPEND:
            ///< TODO：恢复IIC寄存器
            break;

        case PM_DEV_RESUME:
            ///< TODO：保存IIC寄存器
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_iic_enable_pm(csi_iic_t *iic)
{
    ///< TODO：注册IIC低功耗处理函数dw_iic_pm_action
}

void csi_iic_disable_pm(csi_iic_t *iic)
{
    csi_pm_dev_unregister(&iic->dev);
}
#endif

