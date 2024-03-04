#include"rtconfig.h"
#ifdef BSP_USING_SPI
#include"rtconfig.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"
#define LOG_TAG      "spi_drv"
#include "drv_log.h"
#include <string.h>
#include "fparameters.h"
#include "fcpu_info.h"
#include "fkernel.h"
#include "ftypes.h"

#include <dfs_file.h>
#include "fspim.h"
#include "fspim_hw.h" /* include low-level header file for internal probe */
#include "drv_spi.h"
static struct rt_spi_device spi_flash_device;
/* spi test example */
static void fspim_test_sample(int argc, char *argv[])
{
    static struct rt_spi_device *spi_device = RT_NULL;
    static struct rt_spi_device *spi_bus = RT_NULL;

#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)
    spi_bus = (struct rt_spi_device *)rt_device_find("SPI2");
    rt_spi_bus_attach_device(&spi_flash_device, "flash", "SPI2", spi_bus);
#endif

#if defined(FIREFLY_DEMO_BOARD)
    spi_bus = (struct rt_spi_device *)rt_device_find("SPI0");
    rt_spi_bus_attach_device(&spi_flash_device, "flash", "SPI0", spi_bus);
#endif

    rt_uint8_t send_to_flash_id = 0x9f; /* Flash cmd */
    rt_uint8_t recv_from_falsh_id1[5] = {0};
    rt_uint8_t recv_from_falsh_id2[5] = {0};

    /* find the spi device to get the device handle */
    spi_device = (struct rt_spi_device *)rt_device_find("flash");
    if (!spi_device)
    {
        rt_kprintf("fspim_test_sample run failed! can't find flash device!\n");
    }
    else
    {
        static struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &send_to_flash_id;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;

        msg2.send_buf   = RT_NULL;
        msg2.recv_buf   = recv_from_falsh_id2;
        msg2.length     = 5;
        msg2.cs_take    = 0;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;

        /* send the command to read the ID using rt_spi_send_then_recv() */
        rt_spi_send_then_recv(spi_device, &send_to_flash_id, 1, recv_from_falsh_id1, 5);
        rt_kprintf("use rt_spi_send_then_recv() read flash ID is:0x%x 0x%x 0x%x 0x%x 0x%x\n", recv_from_falsh_id1[0], recv_from_falsh_id1[1], recv_from_falsh_id1[2], recv_from_falsh_id1[3], recv_from_falsh_id1[4]);

        /* send the command to read the ID using rt_spi_transfer_message() */
        rt_spi_transfer_message(spi_device, &msg1);
        rt_kprintf("use rt_spi_transfer_message() read flash ID is:0x%x 0x%x 0x%x 0x%x 0x%x\n", recv_from_falsh_id2[0], recv_from_falsh_id2[1], recv_from_falsh_id2[2], recv_from_falsh_id2[3], recv_from_falsh_id2[4]);
    }
}
MSH_CMD_EXPORT(fspim_test_sample, "fspim test sample");
#endif