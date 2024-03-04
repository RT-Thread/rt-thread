
#include "rtconfig.h"
#ifdef BSP_USING_QSPI
#include <rtthread.h>
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif
#include "rtdevice.h"
#include "drv_qspi.h"
#include "fqspi_flash.h"
#include "fiopad.h"
#include "fqspi_hw.h"
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
    rt_kprintf("qspi_test_device addr == %p\n", qspi_test_device);

    return res;
}

/*write cmd example message improvement*/
void qspi_thread(void *parameter)
{
    rt_err_t res;

    qspi_init();

    /*Read and write flash chip fixed area repeatedly*/
    qspi_write_message.address.content = 0x360000 ;/*Flash address*/
    qspi_write_message.instruction.content = 0x02 ;/*write cmd*/
    qspi_write_message.parent.send_buf = "phytium hello world!";
    qspi_write_message.parent.length = strlen((char *)qspi_write_message.parent.send_buf) + 1;
    rt_qspi_transfer_message(qspi_test_device, &qspi_write_message);

    qspi_read_message.address.content = 0x360000 ;/*Flash address*/
    qspi_read_message.instruction.content = 0x03 ;/*write cmd*/
    rt_qspi_transfer_message(qspi_test_device, &qspi_read_message);

    rt_uint8_t recv;
    rt_uint8_t cmd = 0x9F;/*read the flash status reg2*/
    res = rt_qspi_send_then_recv(qspi_test_device, &cmd, sizeof(cmd), &recv, sizeof(recv));
    RT_ASSERT(res != RT_EOK);
    rt_kprintf("The status reg = %x \n", recv);

}

rt_err_t qspi_sample(int argc, char *argv[])
{
    rt_thread_t thread;
    rt_err_t res;
    thread = rt_thread_create("qspi_thread", qspi_thread, RT_NULL, 4096, 25, 10);
    res = rt_thread_startup(thread);
    RT_ASSERT(res == RT_EOK);

    return res;
}
/* Enter qspi_sample command for testing */
MSH_CMD_EXPORT(qspi_sample, qspi sample);
#endif