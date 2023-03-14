#include <os.h>
#include <rtthread.h>

#include <rthw.h>
#ifdef RT_USING_SMART
#include <mmu.h>
#include <lwp_arch.h>
#else
#define PV_OFFSET 0
#endif
#include <cache.h>

#include <hal_atomic.h>
#include <hal_interrupt.h>
#include <ktimer.h>
#include <typedef.h>

#define TIMER_FREQ    (24000000)

typedef unsigned long cycles_t;

#ifndef CSR_TIME
#define CSR_TIME    0xc01
#endif
#ifdef __ASSEMBLY__
#define __ASM_STR(x)    x
#else
#define __ASM_STR(x)    #x
#endif
#define csr_read(csr)                       \
    ({                              \
        register unsigned long __v;             \
        __asm__ __volatile__ ("csrr %0, " __ASM_STR(csr)    \
                              : "=r" (__v) :            \
                              : "memory");          \
        __v;                            \
    })

static inline cycles_t get_cycles(void)
{
    return csr_read(CSR_TIME);
}

static inline uint64_t get_cycles64(void)
{
    return get_cycles();
}

static inline uint32_t arch_timer_get_cntfrq(void)
{
    uint32_t val = TIMER_FREQ;
    return val;
}

static inline uint64_t arch_counter_get_cntpct(void)
{
    uint64_t cval;

    cval = get_cycles64();
    return cval;
}

rt_weak int msleep(unsigned int msecs)
{
    rt_thread_mdelay(msecs);
    return 0;
}

void rt_hw_us_delay(rt_uint32_t us)
{
    uint64_t start, target;
    uint64_t frequency;

    frequency = arch_timer_get_cntfrq();
    start = arch_counter_get_cntpct();
    target = frequency / 1000000ULL * us;

    while (arch_counter_get_cntpct() - start <= target) ;
}

rt_weak int usleep(unsigned int usecs)
{
    int tickDiv = 1000 * (1000 / CONFIG_HZ);
    int ticks   = usecs / tickDiv;
    int msecs   = usecs % tickDiv;

    if (ticks)
    {
        rt_thread_delay(ticks);
    }
    if (msecs)
    {
        rt_hw_us_delay(usecs);
    }
    return 0;
}

unsigned long awos_arch_virt_to_phys(unsigned long virtaddr)
{
    return virtaddr - PV_OFFSET;
}

unsigned long awos_arch_phys_to_virt(unsigned long physaddr)
{
    return physaddr + PV_OFFSET;
}

#include <interrupt.h>
void enable_irq(unsigned int irq)
{
    rt_hw_interrupt_umask(irq);
}

void disable_irq(unsigned int irq)
{
    rt_hw_interrupt_mask(irq);
}

const void *free_irq(unsigned int irq, void *dev_id)
{
    const void *ret = RT_NULL;

    return ret;
}

int request_threaded_irq(unsigned int irq, irq_handler_t handler,
                         irq_handler_t thread_fn, unsigned long irqflags,
                         const char *devname, void *dev_id)
{
    rt_hw_interrupt_install(irq, (rt_isr_handler_t)handler, dev_id, devname);
    return 0;
}


void awos_arch_mems_flush_icache_region(unsigned long start, unsigned long len)
{
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, (void *)start, len);
}

void awos_arch_mems_clean_dcache_region(unsigned long start, unsigned long len)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)start, len);
}

void awos_arch_mems_clean_flush_dcache_region(unsigned long start, unsigned long len)
{
    rt_hw_cpu_dcache_clean_and_invalidate((void *)start, len);
}

void awos_arch_mems_flush_dcache_region(unsigned long start, unsigned long len)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)start, len);
}

void awos_arch_clean_flush_cache(void)
{
    rt_hw_cpu_dcache_clean_all();
    rt_hw_cpu_icache_invalidate_all();
}

void awos_arch_clean_flush_cache_region(unsigned long start, unsigned long len)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)start, len);
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, (void *)start, len);
}

void awos_arch_flush_cache(void)
{
    rt_hw_cpu_dcache_invalidate_all();
    rt_hw_cpu_icache_invalidate_all();
}

void awos_arch_clean_dcache(void)
{
    rt_hw_cpu_dcache_clean_all();
}

void awos_arch_clean_flush_dcache(void)
{
    rt_hw_cpu_dcache_clean_all();
    rt_hw_cpu_dcache_invalidate_all();
}

void awos_arch_flush_dcache(void)
{
    rt_hw_cpu_dcache_invalidate_all();
}

void awos_arch_flush_icache_all(void)
{
    rt_hw_cpu_icache_invalidate_all();
}

rt_weak int32_t hal_spi_gpio_cfg_count(const char *secname)
{
    rt_kprintf("FUNCTION:%s not implemented.\n", __FUNCTION__);
    return 0;
}

int32_t esCFG_GetGPIOSecKeyCount(char *GPIOSecName)
{
    int id;

    if (!rt_strcmp(GPIOSecName, "pwm1") || !rt_strcmp(GPIOSecName, "pwm2") || !rt_strcmp(GPIOSecName, "pwm7"))
    {
        return 1;
    }
    else if (!rt_strcmp(GPIOSecName, "sdc0") || !rt_strcmp(GPIOSecName, "sdc1"))
    {
        return 6;
    }
    else if (!rt_strcmp(GPIOSecName, "spi0"))
    {
        return hal_spi_gpio_cfg_count(GPIOSecName);
    }
    else if (sscanf(GPIOSecName, "twi%d", &id) == 1)
    {
        return 2;
    }
    return 0;
}

rt_weak int hal_spi_gpio_cfg_load(user_gpio_set_t *gpio_cfg, int32_t GPIONum, int id)
{
    rt_kprintf("FUNCTION:%s not implemented.\n", __FUNCTION__);
    return -1;
}

rt_weak int hal_i2c_gpio_cfg_load(user_gpio_set_t *gpio_cfg, int32_t GPIONum, int id)
{
    rt_kprintf("FUNCTION:%s not implemented.\n", __FUNCTION__);
    return -1;
}

#define CFG_GPIO_PORT(p) ((p) - 'A' + 1)

int32_t esCFG_GetGPIOSecData(char *GPIOSecName, void *pGPIOCfg, int32_t GPIONum)
{
    user_gpio_set_t *gpio_cfg = (user_gpio_set_t *) pGPIOCfg;
    int i;
    int id;

    if (!rt_strcmp(GPIOSecName, "pwm1"))
    {
        rt_strncpy(gpio_cfg->gpio_name, "PB6", 4);
        gpio_cfg->data = 0;
        gpio_cfg->drv_level = 3;
        gpio_cfg->mul_sel = 5; // PWM
        gpio_cfg->port = CFG_GPIO_PORT('B'); // PORT-G
        gpio_cfg->port_num = 6; // PG13
        gpio_cfg->pull = 0; // pull disable
    }
    else if (!rt_strcmp(GPIOSecName, "pwm2"))
    {
        rt_strncpy(gpio_cfg->gpio_name, "PG13", 5);
        gpio_cfg->data = 0;
        gpio_cfg->drv_level = 3;
        gpio_cfg->mul_sel = 5; // PWM
        gpio_cfg->port = CFG_GPIO_PORT('G'); // PORT-G
        gpio_cfg->port_num = 13; // PG13
        gpio_cfg->pull = 0; // pull disable
    }
    else if (!rt_strcmp(GPIOSecName, "pwm7"))
    {
        rt_strncpy(gpio_cfg->gpio_name, "PD22", 5);
        gpio_cfg->data = 0;
        gpio_cfg->drv_level = 3;
        gpio_cfg->mul_sel = 5; // PWM
        gpio_cfg->port = CFG_GPIO_PORT('D'); // PORT-D
        gpio_cfg->port_num = 22; // PD22
        gpio_cfg->pull = 0; // pull disable
    }
    else if (!rt_strcmp(GPIOSecName, "sdc0"))
    {
        /*
        [sdc0]
        ;sdc0_used          = 1
        ;bus-width      = 4
        sdc0_d1            = port:PF00<2><1><1><default>
        sdc0_d0            = port:PF01<2><1><1><default>
        sdc0_clk           = port:PF02<2><1><1><default>
        sdc0_cmd           = port:PF03<2><1><1><default>
        sdc0_d3            = port:PF04<2><1><1><default>
        sdc0_d2            = port:PF05<2><1><1><default>
        */
        for (i = 0; i < GPIONum; i++)
        {
            strcpy(gpio_cfg->gpio_name, GPIOSecName);
            gpio_cfg->port = CFG_GPIO_PORT('F');
            gpio_cfg->port_num = i;
            gpio_cfg->mul_sel = 2;
            gpio_cfg->pull = 1;
            gpio_cfg->drv_level = 1;
            gpio_cfg->data = 0;
            gpio_cfg++;
        }
    }
    else if (!rt_strcmp(GPIOSecName, "sdc1"))
    {
        /*
        [sdc1]
        ;sdc1_used          = 1
        ;bus-width= 4
        sdc1_clk           = port:PG00<2><1><1><default>
        sdc1_cmd           = port:PG01<2><1><1><default>
        sdc1_d0            = port:PG02<2><1><1><default>
        sdc1_d1            = port:PG03<2><1><1><default>
        sdc1_d2            = port:PG04<2><1><1><default>
        sdc1_d3            = port:PG05<2><1><1><default>
        */
        for (i = 0; i < GPIONum; i++)
        {
            strcpy(gpio_cfg->gpio_name, GPIOSecName);
            gpio_cfg->port = CFG_GPIO_PORT('G');
            gpio_cfg->port_num = i;
            gpio_cfg->mul_sel = 2;
            gpio_cfg->pull = 1;
            gpio_cfg->drv_level = 1;
            gpio_cfg->data = 0;
            gpio_cfg++;
        }
    }
    else if (sscanf(GPIOSecName, "spi%d", &id) == 1)
    {
        return hal_spi_gpio_cfg_load(gpio_cfg, GPIONum, id);
    }
    else if (sscanf(GPIOSecName, "twi%d", &id) == 1)
    {
        extern int hal_i2c_gpio_cfg_load(user_gpio_set_t *gpio_cfg, int32_t GPIONum, int id);
        return hal_i2c_gpio_cfg_load(gpio_cfg, GPIONum, id);
    }
    return 0;
}

int32_t esCFG_GetKeyValue(char *SecName, char *KeyName, int32_t Value[], int32_t Count)
{
    if (!rt_strcmp("target", SecName))
    {
        /*
        [target]
        boot_clock      = 1008
        storage_type    = 1
        */
        if (!rt_strcmp("storage_type", KeyName))
        {
            if (Count == 1)
            {
                *Value = 1;
                return 0;
            }
        }
        else if (!rt_strcmp("boot_clock", KeyName))
        {
            if (Count == 1)
            {
                *Value = 1008;
                return 0;
            }
        }
    }
    else if (!rt_strcmp("card_product", SecName))
    {
        /*
        [card_product]
        card_product_used    = 1
        card_product_storage = 3
        */
        if (!rt_strcmp("card_product_used", KeyName))
        {
            if (Count == 1)
            {
                *Value = 1;
                return 0;
            }
        } else if (!rt_strcmp("card_product_storage", KeyName))
        {
            if (Count == 1)
            {
                *Value = 3;
                return 0;
            }
        }
    }
    else if (!rt_strcmp("sdcard_global", SecName))
    {
        /*
        [sdcard_global]
        used_card_no    = 0x01
        ;used_card_no = 0x01, when use card0
        ;used_card_no = 0x02, when use card1
        ;used_card_no = 0x03, when use card0 & card1
        internal_card = 0x00
        ;internal_card = 0x00, 无内置卡内置卡
        ;internal_card = 0x01, card0 做内置卡
        ;internal_card = 0x02, card1 做内置卡
        */
        if (!rt_strcmp("internal_card", KeyName))
        {
            *Value = 0x01;
            return 0;
        } else if (!rt_strcmp("used_card_no", KeyName))
        {
            *Value = 0x03;
            return 0;
        }
    }
    return -1;
}

int do_gettimeofday(struct timespec64 *ts)
{
    if (ts)
    {
        ts->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        ts->tv_nsec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000000 / RT_TICK_PER_SECOND);
    }
    return 0;
}

int eLIBs_printf(const char *fmt, ...)
{
    va_list args;
    rt_size_t length;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];

    va_start(args, fmt);

    length = rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
    if (length > RT_CONSOLEBUF_SIZE - 1)
        length = RT_CONSOLEBUF_SIZE - 1;
    va_end(args);

    rt_kputs(rt_log_buf);
}
