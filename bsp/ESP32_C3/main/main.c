/*
 * Copyright (c) 2021-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-04-24     supperthomas  first version
 * 2022-06-02     supperthomas  fix version
 * 2023-10-20     WCX1024979076 add wifi application
 */

//#include "drivers/spi.h"
// #include "hal/gpio_types.h"
#include "rttypes.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "./drivers/drv_spi.h"
#include "./packages/ESP-IDF-latest/components/hal/include/hal/gpio_types.h"
// #include "/home/lzx/rt-thread/rt-thread/bsp/ESP32_C3/packages/ESP-IDF-latest/tools/mocks/hal/include/hal/gpio_types.h"
//#define GPIO_PIN_REG_14 0x6000903c
#define W25Q_SPI_DEVICE_NAME "spi20"
#define SPI_BUS_NAME "spi2"   
 
void spi_w25q_sample(void)
{
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);
    
    rt_hw_spi_device_attach(SPI_BUS_NAME, W25Q_SPI_DEVICE_NAME, GPIO_NUM_10 );
    
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    struct rt_spi_device *spi_w25q;
    struct rt_spi_configuration cfg;
    
    rt_uint8_t w25x_read_id[7] = {0x9f, 0xff, 0xff, 0x00, 0xff,0xff,0xff};
    rt_uint8_t id[7] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    spi_w25q = (struct rt_spi_device*)rt_device_find(W25Q_SPI_DEVICE_NAME);
    if(!spi_w25q)
    {
        rt_kprintf("spi asmple run failed! can't find %s device\n",W25Q_SPI_DEVICE_NAME);
    }
    else {    
        rt_spi_configure(spi_w25q, &cfg);
        rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

        struct rt_spi_message msg1, msg2,msg3,msg4,msg5,msg6;

        msg1.send_buf   = &w25x_read_id;
        msg1.recv_buf   = &id;
        msg1.length     = 48;//
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = RT_NULL;

        // msg2.send_buf   = &w25x_read_id[1];
        // msg2.recv_buf   = &id[1];
        // msg2.length     = 8;//
        // msg2.cs_take    = 0;
        // msg2.cs_release = 1;
        // msg2.next       = &msg3;

        // msg3.send_buf   = &w25x_read_id[2];
        // msg3.recv_buf   = &id[2];
        // msg3.length     = 8;//
        // msg3.cs_take    = 0;
        // msg3.cs_release = 1;
        // msg3.next       = &msg4;

        // msg4.send_buf   = &w25x_read_id[3];
        // msg4.recv_buf   = &id[3];
        // msg4.length     = 8;//
        // msg4.cs_take    = 0;
        // msg4.cs_release = 1;
        // msg4.next       = &msg5;

        // msg5.send_buf   = &w25x_read_id[4];
        // msg5.recv_buf   = &id[4];
        // msg5.length     = 8;//
        // msg5.cs_take    = 0;
        // msg5.cs_release = 1;
        // msg5.next       = &msg6;

        // msg6.send_buf   = &w25x_read_id[5];
        // msg6.recv_buf   = &id[5];
        // msg6.length     = 8;//
        // msg6.cs_take    = 0;
        // msg6.cs_release = 1;
        // msg6.next       = RT_NULL;


    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

        rt_spi_transfer_message(spi_w25q, &msg1);
        // rt_spi_transfer_message(spi_w25q, &msg2);
        // rt_spi_transfer_message(spi_w25q, &msg3);
        // rt_spi_transfer_message(spi_w25q, &msg4);
        // rt_spi_transfer_message(spi_w25q, &msg5);
        // rt_spi_transfer_message(spi_w25q, &msg6);
        rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", id[3], id[4]);
    
    for(int a = 0; a < sizeof(id); a++)
    {
        rt_kprintf("id is:%x\t", id[a]);
    }

    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    // rt_spi_send_then_recv(spi_w25q, &w25x_read_id, 1, id, 5);
    rt_kprintf("%x%x\n",id[3],id[4]);
    }
}
MSH_CMD_EXPORT(spi_w25q_sample, spi w25q sample);

int main(void)
{
    rt_kprintf("Hello!RT-THREAD!\r\n");
    rt_pin_mode(RT_BSP_LED_PIN, PIN_MODE_OUTPUT);

#ifdef BSP_USING_BLE
    extern void app_main(void);
    esp_timer_init();
    app_main(); //该函数为nimble样例程序入口
#endif /* BSP_USING_BLE */

#ifdef RT_USING_WIFI
    /* set wifi work mode */
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);
#endif /* RT_USING_WIFI */

    while (1)
    {


        rt_pin_write(RT_BSP_LED_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(RT_BSP_LED_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}