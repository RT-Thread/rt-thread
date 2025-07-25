#include <string.h>
#include <drv/qspi.h>
#include <drv/tick.h>
#include <drv/irq.h>

#define QSPI_DEFAULT_TRANSFER_SIZE   8U

csi_error_t csi_qspi_init(csi_qspi_t *qspi, uint32_t idx)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    if (target_get(DEV_CD_QSPI_TAG, idx, &qspi->dev) != CSI_OK) {
        ret = CSI_ERROR;
    } else {
        qspi->state.writeable = 1U;
        qspi->state.readable  = 1U;
        qspi->state.error     = 0U;
        qspi->callback        = NULL;
        qspi->arg             = NULL;
        qspi->tx_data         = NULL;
        qspi->rx_data         = NULL;
        qspi->send            = NULL;
        qspi->receive         = NULL;
        qspi->send_receive    = NULL;
        qspi->tx_dma          = NULL;
        qspi->rx_dma          = NULL;
    }

    return ret;
}

void csi_qspi_uninit(csi_qspi_t *qspi)
{
    CSI_PARAM_CHK_NORETVAL(qspi);

    ///< TODO：复位QSPI所有的寄存器

    ///< 禁止QSPI中断控制器对应的中断，注销QSPI中断服务函数
    csi_irq_disable((uint32_t)qspi->dev.irq_num);
    csi_irq_detach((uint32_t)qspi->dev.irq_num);
}

csi_error_t csi_qspi_attach_callback(csi_qspi_t *qspi, void *callback, void *arg)
{
    CSI_PARAM_CHK(qspi    , CSI_ERROR);
    CSI_PARAM_CHK(callback, CSI_ERROR);

    qspi->callback  = callback;
    qspi->arg       = arg;

    ///< 注册QSPI中断服务函数，使能QSPI中断控制器对应的中断
    csi_irq_attach((uint32_t)qspi->dev.irq_num, NULL, &qspi->dev);
    csi_irq_enable((uint32_t)qspi->dev.irq_num);

    return CSI_OK;
}

void csi_qspi_detach_callback(csi_qspi_t *qspi)
{
    CSI_PARAM_CHK_NORETVAL(qspi);

    qspi->callback  = NULL;
    qspi->arg       = NULL;

    ///< 禁止QSPI中断控制器对应的中断，注销QSPI中断服务函数
    csi_irq_disable((uint32_t)qspi->dev.irq_num);
    csi_irq_detach((uint32_t)qspi->dev.irq_num);
}

uint32_t csi_qspi_frequence(csi_qspi_t *qspi, uint32_t hz)
{
    CSI_PARAM_CHK(qspi, 0U);
    CSI_PARAM_CHK(hz,   0U);

    ///< TODO：配置QSPI的频率
    ///< TODO：获取QSPI的分频到div
    ///< TODO：根据QSPI的工作频率和div获取QSPI实际使用的频率到hz

    return hz;
}

csi_error_t csi_qspi_mode(csi_qspi_t *qspi, csi_qspi_mode_t mode)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    switch (mode) {
        case QSPI_CLOCK_MODE_0:
            ///< TODO：配置QSPI时钟的极性和相位
            break;

        case QSPI_CLOCK_MODE_1:
            ///< TODO：配置QSPI时钟的极性和相位
            break;

        case QSPI_CLOCK_MODE_2:
            ///< TODO：配置QSPI时钟的极性和相位
            break;

        case QSPI_CLOCK_MODE_3:
            ///< TODO：配置QSPI时钟的极性和相位
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

void qspi_config_command(csi_qspi_t *qspi, csi_qspi_command_t *cmd)
{

    /* configure instruction */
    if (cmd->instruction.disabled == (bool)false) {
        ///< TODO：在QSPI的STIG模式下配置QSPI的命令操作码
    }

    /* configure address */
    if (cmd->address.disabled == (bool)false) {
        ///< TODO：在QSPI的STIG模式下启用QSPI的命令地址
        ///< TODO：在QSPI的STIG模式下设置QSPI的命令地址字节的大小
        ///< TODO：在QSPI的STIG模式下设置QSPI的命令地址
    }

    /* configure dummy cycles */
    if (cmd->dummy_count) {
        ///< TODO：在QSPI的STIG模式下设置QSPI的周期数
    }

    /* configure mode */
    if (cmd->alt.disabled == (bool)false) {
        ///< TODO：在QSPI的STIG模式下使能mode bit
        ///< TODO：在QSPI的STIG模式下配置QSPI的mode bits
    }

    /* configure DDR */
    if (cmd->ddr_enable) {
        ///< TODO：使能QSPI的DDR位
    }
}

csi_error_t qspi_execute_stig_command(csi_qspi_t *qspi, uint32_t timeout)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    ///< TODO：设置QSPI的执行命令

    ///< TODO：通过while循环等待QSPI进程结束处于空闲状态，超时则超时退出

    return ret;
}

int32_t qspi_send(csi_qspi_t *qspi, uint32_t timeout)
{
    int32_t ret = 0;

    ret = qspi_execute_stig_command(qspi, timeout);

    /* return actual send count */
    if (ret == 0) {
        ret = (int32_t)qspi->tx_size;
    }

    qspi->tx_size = 0U;
    return ret;
}

int32_t csi_qspi_send(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(cmd,  CSI_ERROR);
    CSI_PARAM_CHK(timeout, CSI_ERROR);

    int32_t  ret = CSI_OK;

    do {
        if ((qspi->state.writeable == 0U) || (qspi->state.readable == 0U)) {
            ret = CSI_BUSY;
            break;
        }

        ///< TODO：复位控制STIG生成的SPI事务的寄存器

        qspi_config_command(qspi, cmd);

        if (size == 0U) {

            ret = qspi_execute_stig_command(qspi, timeout);

            ///< TODO：复位控制STIG生成的SPI事务的寄存器
            break;
        }

        qspi->state.writeable = 0U;
        qspi->tx_data         = (void *)data;
        qspi->tx_size         = size;
        ///< TODO：获取QSPI命令的地址

        /* TODU: transfer use indirect access mode, only support STIG mode */
        if (qspi->tx_size > QSPI_DEFAULT_TRANSFER_SIZE) {
            qspi->state.writeable = 1U;
            ret = CSI_ERROR;
            break;
        }

        /* configure qspi registers */
        ///< TODO：使能QSPI写数据
        ///< TODO：配置QSPI写数据字节的大小
        ///< TODO：配置QSPI命令地址
        ///< TODO：写数据

        qspi->state.writeable = 1U;
        ret = qspi_send(qspi, timeout);

    } while (0);

    return ret;
}


int32_t csi_qspi_receive(csi_qspi_t *qspi, csi_qspi_command_t *cmd, void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(cmd,  CSI_ERROR);
    CSI_PARAM_CHK(timeout, CSI_ERROR);

    uint32_t address;
    int32_t  ret   = CSI_OK;
    uint32_t count = 0U;
    uint32_t current_size = 0U;

    do {
        if ((qspi->state.writeable == 0U) || (qspi->state.readable == 0U)) {
            ret = CSI_BUSY;
            break;
        }

        qspi_config_command(qspi, cmd);

        if (size == 0U) {
            ret = qspi_execute_stig_command(qspi, timeout);

            ///< TODO：复位控制STIG生成的SPI事务的寄存器
            break;
        }


        qspi->rx_data        = data;
        qspi->rx_size        = size;
        qspi->state.readable = 0U;
        ///< TODO：获取QSPI命令的地址到address

        /* transfer loop */
        /* TODU: transfer use indirect access mode */
        while (qspi->rx_size > 0U) {
            current_size = (qspi->rx_size > QSPI_DEFAULT_TRANSFER_SIZE) ? (uint32_t) QSPI_DEFAULT_TRANSFER_SIZE : qspi->rx_size;

            /* configure qspi registers */
            ///< TODO：配置QSPI读数据字节的大小
            ///< TODO：使能QSPI读数据
            ///< TODO：配置QSPI命令地址
            ret = (int32_t)qspi_execute_stig_command(qspi, timeout);

            if (ret < 0) {
                break;
            }

            ///< TODO：读数据到qspi->rx_data
            qspi->rx_data  += current_size;
            qspi->rx_size  -= current_size;
            count   += current_size;
            address +=  current_size;
        }

        qspi->state.readable = 1U;

        ///< TODO：复位控制STIG生成的SPI事务的寄存器
    } while (0);

    /* return actual sent count if no error occur */
    if (ret >= 0) {
        ret = (int32_t)count;
    }

    return ret;
}

int32_t csi_qspi_send_receive(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *tx_data, void *rx_data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(cmd,  CSI_ERROR);
    CSI_PARAM_CHK(tx_data, CSI_ERROR);
    CSI_PARAM_CHK(rx_data, CSI_ERROR);
    CSI_PARAM_CHK(size,    CSI_ERROR);
    CSI_PARAM_CHK(timeout, CSI_ERROR);

    return 0;
}

csi_error_t csi_qspi_send_async(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(cmd,  CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    return CSI_UNSUPPORTED;
}

csi_error_t csi_qspi_receive_async(csi_qspi_t *qspi, csi_qspi_command_t *cmd, void *data, uint32_t size)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(cmd,  CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    return CSI_UNSUPPORTED;
}

csi_error_t csi_qspi_send_receive_async(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *tx_data, void *rx_data, uint32_t size)
{
    CSI_PARAM_CHK(qspi,    CSI_ERROR);
    CSI_PARAM_CHK(cmd,     CSI_ERROR);
    CSI_PARAM_CHK(tx_data, CSI_ERROR);
    CSI_PARAM_CHK(rx_data, CSI_ERROR);
    CSI_PARAM_CHK(size,    CSI_ERROR);

    return CSI_UNSUPPORTED;
}

csi_error_t csi_qspi_get_state(csi_qspi_t *qspi, csi_state_t *state)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(state, CSI_ERROR);

    *state = qspi->state;
    return CSI_OK;
}

csi_error_t csi_qspi_link_dma(csi_qspi_t *qspi, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(tx_dma, CSI_ERROR);
    CSI_PARAM_CHK(rx_dma, CSI_ERROR);

    return CSI_UNSUPPORTED;
}

csi_error_t csi_qspi_memory_mapped(csi_qspi_t *qspi, csi_qspi_command_t *cmd)
{
    CSI_PARAM_CHK(qspi, CSI_ERROR);
    CSI_PARAM_CHK(cmd,  CSI_ERROR);

    ///< TODO：配置读取操作码的宽度

    ///< TODO：配置指令类型

    ///< TODO：配置读数据地址的宽度
    ///< TODO：配置读数据的宽度

    ///< TODO：配置读数据的周期

    if (cmd->alt.disabled == (bool)false) {
        ///< TODO：使能读数据模式
        ///< TODO：配置QSPI模式字节的大小
    } else {
        ///< TODO：禁止读数据模式
    }

    if (cmd->ddr_enable) {
        ///< TODO：使能QSPI的DDR位
    }

    return CSI_OK;
}

#ifdef CONFIG_PM
static csi_error_t dw_qspi_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;

    switch (action) {
        case PM_DEV_SUSPEND:
            ///< TODO：恢复QSPI寄存器
            break;

        case PM_DEV_RESUME:
            ///< TODO：保存QSPI寄存器
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_qspi_enable_pm(csi_qspi_t *qspi)
{
    ///< TODO：注册QSPI低功耗处理函数dw_qspi_pm_action
}

void csi_qspi_disable_pm(csi_qspi_t *qspi)
{
    csi_pm_dev_unregister(&qspi->dev);
}
#endif
