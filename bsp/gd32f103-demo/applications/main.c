#include <rtthread.h>
#include <rtdevice.h>
#include <gd32f10x.h>
#include <easyflash.h>

int main(void)
{
    rt_uint32_t rebootCount = 0;
    size_t len = 0;
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, GPIO_OCTL_OCTL13);

    rt_kprintf("[FMC_SIZE=%dkb, FMC_BGINE=%x, FMC_END=%x]\n", FMC_SIZE, FLASH_BASE, FLASH_BASE + (FMC_SIZE * 1024));
    fal_init();
    easyflash_init();

    if (ef_get_env_blob("rebootCount", &rebootCount, sizeof(rebootCount), &len) == sizeof(rebootCount))
    {
        rt_kprintf("rebootCount=%d\n", rebootCount++);
    }
    if (ef_set_env_blob("rebootCount", &rebootCount, sizeof(rebootCount)) != EF_NO_ERR)
    {
        rt_kprintf("rebootCount save fail!\n");
    }

    while (1)
    {
        gpio_bit_set(GPIOB, GPIO_OCTL_OCTL13);
        rt_thread_delay(100);
        gpio_bit_reset(GPIOB, GPIO_OCTL_OCTL13);
        rt_thread_delay(100);
    }
    return 0;
}

/******************** end of file *******************/

