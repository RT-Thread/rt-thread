
#include "rtconfig.h"
#ifdef BSP_USING_QSPI
#include <rtthread.h>
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif
#include "auto_test.h"
#include "rtdevice.h"
#include "drv_qspi.h"
#include "fqspi_flash.h"
#include "fiopad.h"
#include "fqspi_hw.h"
#include "drv_qspi.h"
/*example*/
struct rt_qspi_message qspi_write_message;
struct rt_qspi_message qspi_read_message;

static struct rt_qspi_device *qspi_test_device;        /* phytium device bus handle */
rt_err_t qspi_init()
{
    rt_err_t res = RT_EOK;
    res = phytium_qspi_bus_attach_device("QSPI0", "QSPIDEV");
    RT_ASSERT(res == RT_EOK);
    qspi_test_device = (struct rt_qspi_device *)rt_device_find("QSPIDEV");

    return res;
}

/*write cmd example message improvement*/
rt_err_t qspi_sample()
{
    rt_err_t res = RT_EOK;
    rt_size_t trans_res = 0;

    res = qspi_init();

    phytium_qspi_bus *qspi_bus;
    qspi_bus = (phytium_qspi_bus *) qspi_test_device->parent.bus->parent.user_data;
    /*Read and write flash chip fixed area repeatedly*/
    qspi_write_message.address.content = qspi_bus->fqspi.flash_size[0] - 0x100;/*Flash address*/
    qspi_write_message.instruction.content = 0x02 ;/*write cmd*/
    qspi_write_message.parent.send_buf = "phytium hello world!";
    qspi_write_message.parent.length = strlen((char *)qspi_write_message.parent.send_buf) + 1;
    rt_qspi_transfer_message(qspi_test_device, &qspi_write_message);

    qspi_read_message.address.content = qspi_bus->fqspi.flash_size[0] - 0x100;/*Flash address*/
    qspi_read_message.instruction.content = 0x03 ;/*write cmd*/
    qspi_read_message.parent.length = 128;/*write cmd*/
    qspi_read_message.parent.recv_buf = (rt_uint8_t *)rt_malloc(sizeof(rt_uint8_t) * qspi_read_message.parent.length);
    trans_res = rt_qspi_transfer_message(qspi_test_device, &qspi_read_message);

    if (trans_res != qspi_read_message.parent.length)
    {
        LOG_E("The qspi read data length is incorrect.\r\n");
        res = RT_ERROR;
        goto exit;
    }

    char *send_ptr = (char *)qspi_write_message.parent.send_buf;
    char *recv_ptr = (char *)qspi_read_message.parent.recv_buf;

    for (int i = 0; i < qspi_write_message.parent.length; i++)
    {
        if (send_ptr[i] != recv_ptr[i])
        {
            LOG_E("The qspi read and write data is inconsistent.\r\n");
            res = RT_ERROR;
            goto exit;
        }
    }

    rt_uint8_t recv;
    rt_uint8_t cmd = 0x9F;/*read the flash status reg2*/
    rt_qspi_send_then_recv(qspi_test_device, &cmd, sizeof(cmd), &recv, sizeof(recv));
    if (recv == 0x0)
    {
        LOG_E("The status reg is incorrect, recv = %x, res = %x\n", recv, res);
        res = RT_ERROR;
        goto exit;
    }

exit:
    /* print message on example run result */
    if (res == RT_EOK)
    {
        rt_kprintf("%s@%d:rtthread qspi flash test example [success].\r\n", __func__, __LINE__);
    }
    else
    {
        rt_kprintf("%s@%d:rtthread qspi flash test example [failure], res = %d\r\n", __func__, __LINE__, res);
    }

    return res;
}

/* Enter qspi_sample command for testing */
MSH_CMD_EXPORT(qspi_sample, qspi sample);
#endif