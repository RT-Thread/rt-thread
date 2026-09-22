/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04     zylx         first version
 * 2023-08-20     yuanzihao    adapter gd32f4xx
 * 2026-09-08     CYFS         initialize SDRAM safely and report readiness and throughput
 */

#include <board.h>

#ifdef BSP_USING_SDRAM
#include <sdram_port.h>
#include <rthw.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.sdram"
#include <drv_log.h>

#ifndef SDRAM_HEAP_BEGIN
#define SDRAM_HEAP_BEGIN    SDRAM_BANK_ADDR
#endif
#ifndef SDRAM_HEAP_SIZE
#define SDRAM_HEAP_SIZE     SDRAM_SIZE
#endif

static exmc_sdram_parameter_struct        sdram_init_struct;
static exmc_sdram_command_parameter_struct     sdram_command_init_struct;
static exmc_sdram_timing_parameter_struct  sdram_timing_init_struct;
static rt_bool_t sdram_ready;
#if defined(SOC_SERIES_GD32H77x_H78X)
static uint32_t sdram_sdclk_hz;
static uint32_t sdram_refresh_count;
#endif
#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif


rt_weak void rt_hw_sdram_gpio_init(void)
{
    /* enable EXMC clock*/
    rcu_periph_clock_enable(RCU_EXMC);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_GPIOH);

    /* common GPIO configuration */
    /* SDNWE(PC0),SDNE0(PC2),SDCKE0(PC3) pin configuration */
    gpio_af_set(GPIOC, GPIO_AF_12, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, SDRAM_GPIO_SPEED, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);

    /* D2(PD0),D3(PD1),D13(PD8),D14(PD9),D15(PD10),D0(PD14),D1(PD15) pin configuration */
    gpio_af_set(GPIOD, GPIO_AF_12, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_8 | GPIO_PIN_9 |
                GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_8 | GPIO_PIN_9 |
                  GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, SDRAM_GPIO_SPEED, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_8 | GPIO_PIN_9 |
                            GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);

    /* NBL0(PE0),NBL1(PE1),D4(PE7),D5(PE8),D6(PE9),D7(PE10),D8(PE11),D9(PE12),D10(PE13),D11(PE14),D12(PE15) pin configuration */
    gpio_af_set(GPIOE, GPIO_AF_12, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7  | GPIO_PIN_8 |
                GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7  | GPIO_PIN_8 |
                  GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                  GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, SDRAM_GPIO_SPEED, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7  | GPIO_PIN_8 |
                            GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* A0(PF0),A1(PF1),A2(PF2),A3(PF3),A4(PF4),A5(PF5),NRAS(PF11),A6(PF12),A7(PF13),A8(PF14),A9(PF15) pin configuration */
    gpio_af_set(GPIOF, GPIO_AF_12, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  |
                GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_11 | GPIO_PIN_12 |
                GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  |
                  GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_11 | GPIO_PIN_12 |
                  GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, SDRAM_GPIO_SPEED, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  |
                            GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_11 | GPIO_PIN_12 |
                            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* A10(PG0),A11(PG1),A12(PG2),A14(PG4),A15(PG5),SDCLK(PG8),NCAS(PG15) pin configuration */
    gpio_af_set(GPIOG, GPIO_AF_12, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                  GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, SDRAM_GPIO_SPEED, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                            GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15);

}

#if defined(SOC_SERIES_GD32H77x_H78X)
static uint32_t sdram_clock_hz_get(void)
{
    uint32_t clock_hz;
    uint32_t divider;

    switch (RCU_CFG4 & RCU_CFG4_EXMCSEL)
    {
    case RCU_EXMCSRC_AHB:
        clock_hz = rcu_clock_freq_get(CK_AHB);
        break;
    case RCU_EXMCSRC_PLL0Q:
        clock_hz = rcu_clock_freq_get(CK_PLL0Q);
        break;
    case RCU_EXMCSRC_PLL1R:
        clock_hz = rcu_clock_freq_get(CK_PLL1R);
        break;
    case RCU_EXMCSRC_PER:
        clock_hz = rcu_clock_freq_get(CK_PER);
        break;
    default:
        return 0U;
    }

    switch (EXMC_SDCTL(EXMC_SDRAM_DEVICE0) &
            (EXMC_SDCTL_SDCLK | EXMC_SDCTL_SDCLK_2))
    {
    case EXMC_SDCLK_PERIODS_2_CK_EXMC: divider = 2U; break;
    case EXMC_SDCLK_PERIODS_3_CK_EXMC: divider = 3U; break;
    case EXMC_SDCLK_PERIODS_4_CK_EXMC: divider = 4U; break;
    case EXMC_SDCLK_PERIODS_5_CK_EXMC: divider = 5U; break;
    default: return 0U;
    }
    return clock_hz / divider;
}

static uint32_t sdram_refresh_count_get(uint32_t sdclk_hz)
{
    uint32_t cycles = (uint32_t)(((uint64_t)sdclk_hz * SDRAM_REFRESH_PERIOD_MS) /
                                 (1000U * SDRAM_REFRESH_ROWS));

    /* Round down so refresh never exceeds 64 ms / 8192 rows. */
    if ((cycles <= 20U) || ((cycles - 20U) > (EXMC_SDARI_ARINTV >> 1U)))
    {
        return 0U;
    }
    return cycles - 20U;
}
#endif

/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  Command: Pointer to SDRAM command structure
  * @retval None
  */
static rt_err_t SDRAM_Initialization_Sequence(exmc_sdram_parameter_struct *hsdram, exmc_sdram_command_parameter_struct *Command)
{
    __IO uint32_t tmpmrd = 0;
    uint32_t target_bank = 0;
    uint32_t sdram_device = SDRAM_DEVICE;
    uint32_t command_content = 0;

    uint32_t timeout = SDRAM_TIMEOUT;

#if SDRAM_TARGET_BANK == 1
    target_bank = EXMC_SDRAM_DEVICE0_SELECT;
#else
    target_bank = EXMC_SDRAM_DEVICE1_SELECT;
#endif

    rt_hw_sdram_gpio_init();
    /* EXMC SDRAM device initialization sequence --------------------------------*/
    /* Step 1 : configure SDRAM timing registers --------------------------------*/
    /* LMRD: 2 clock cycles */
    sdram_timing_init_struct.load_mode_register_delay = LOADTOACTIVEDELAY;
    /* XSRD: min = 75ns */
    sdram_timing_init_struct.exit_selfrefresh_delay = EXITSELFREFRESHDELAY;
    /* RASD: min=44ns , max=120k (ns) */
    sdram_timing_init_struct.row_address_select_delay = ROWCYCLEDELAY;
    /* ARFD: min=66ns */
    sdram_timing_init_struct.auto_refresh_delay = SELFREFRESHTIME;
    /* WRD:  min=1 Clock cycles +7.5ns */
    sdram_timing_init_struct.write_recovery_delay = WRITERECOVERYTIME;
    /* RPD:  min=20ns */
    sdram_timing_init_struct.row_precharge_delay = RPDELAY;
    /* RCD:  min=20ns */
    sdram_timing_init_struct.row_to_column_delay = RCDDELAY;

    /* step 2 : configure SDRAM control registers ---------------------------------*/
    sdram_init_struct.sdram_device = sdram_device;
    sdram_init_struct.column_address_width = SDRAM_COLUMN_BITS;
    sdram_init_struct.row_address_width = SDRAM_ROW_BITS;
    sdram_init_struct.data_width = SDRAM_DATA_WIDTH;
    sdram_init_struct.internal_bank_number = EXMC_SDRAM_4_INTER_BANK;
    sdram_init_struct.cas_latency = SDRAM_CAS_LATENCY;
    sdram_init_struct.write_protection = DISABLE;
    sdram_init_struct.sdclock_config = SDCLOCK_PERIOD;
    sdram_init_struct.burst_read_switch = SDRAM_BURST_READ;
    sdram_init_struct.pipeline_read_delay = SDRAM_RPIPE_DELAY;
    sdram_init_struct.timing  = &sdram_timing_init_struct;
    /* EXMC SDRAM bank initialization */
    exmc_sdram_init(&sdram_init_struct);
#if defined(SOC_SERIES_GD32H77x_H78X)
    sdram_sdclk_hz = sdram_clock_hz_get();
    sdram_refresh_count = sdram_refresh_count_get(sdram_sdclk_hz);
    if (sdram_refresh_count == 0U)
    {
        LOG_E("invalid SDRAM clock/refresh configuration");
        return -RT_ERROR;
    }
#endif

    /* step 3 : configure CKE high command---------------------------------------*/
    sdram_command_init_struct.command = EXMC_SDRAM_CLOCK_ENABLE;
    sdram_command_init_struct.bank_select = target_bank;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_1_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    while((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    if(0 == timeout) {
        return RT_ERROR;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* CKE startup delay must run before PRECHARGE; the scheduler is not running. */
    rt_hw_us_delay(1000U);

    /* step 5 : configure precharge all command----------------------------------*/
    sdram_command_init_struct.command = EXMC_SDRAM_PRECHARGE_ALL;
    sdram_command_init_struct.bank_select = target_bank;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_1_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    if(0 == timeout) {
        return RT_ERROR;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 6 : configure Auto-Refresh command-----------------------------------*/
    sdram_command_init_struct.command = EXMC_SDRAM_AUTO_REFRESH;
    sdram_command_init_struct.bank_select = target_bank;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_8_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    if(0 == timeout) {
        return RT_ERROR;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 7 : configure load mode register command-----------------------------*/
    /* program mode register */
    command_content = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1        |
                      SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                      SDRAM_MODEREG_CAS_LATENCY_3           |
                      SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                      SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    sdram_command_init_struct.command = EXMC_SDRAM_LOAD_MODE_REGISTER;
    sdram_command_init_struct.bank_select = target_bank;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_1_SDCLK;
    sdram_command_init_struct.mode_register_content = command_content;

    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    if(0 == timeout) {
        return RT_ERROR;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 8 : set the auto-refresh rate counter--------------------------------*/
    /* 64ms, 8192-cycle refresh, 64ms/8192=7.81us */
    /* (7.81 us * SDCLK_Freq) - 20 */
#if defined(SOC_SERIES_GD32H77x_H78X)
    exmc_sdram_refresh_count_set(sdram_refresh_count);
#else
    exmc_sdram_refresh_count_set(SDRAM_REFRESH_COUNT);
#endif

    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    if(0 == timeout) {
        return RT_ERROR;
    }
    return RT_EOK;

}

#ifdef RT_USING_MEMHEAP_AS_HEAP
static rt_err_t _sdram_memory_boundary_test(void)
{
    volatile uint32_t *head = (volatile uint32_t *)SDRAM_HEAP_BEGIN;
    volatile uint32_t *tail = (volatile uint32_t *)(SDRAM_HEAP_BEGIN + SDRAM_HEAP_SIZE - sizeof(uint32_t));

    *head = 0x55AA1234U;
    *tail = 0xAA55ABCDU;
    __DSB();

    rt_kprintf("sdram boundary test: head=0x%08X, tail=0x%08X\n", *head, *tail);
    if ((*head != 0x55AA1234U) || (*tail != 0xAA55ABCDU))
    {
        LOG_E("SDRAM boundary test failed!");
        return -RT_ERROR;
    }

    return RT_EOK;
}
#endif

rt_bool_t rt_hw_sdram_is_ready(void)
{
    return sdram_ready;
}

static int SDRAM_Init(void)
{
    int result = RT_EOK;

    sdram_ready = RT_FALSE;
    /* Initialize the SDRAM controller */
    if (SDRAM_Initialization_Sequence(&sdram_init_struct, &sdram_command_init_struct) != RT_EOK)
    {
        LOG_E("SDRAM init failed!");
        result = -RT_ERROR;
    }
    else
    {
        rt_kprintf("sdram controller init success, mapped at 0x%X, size is %d bytes, data width is %d\n",
                   SDRAM_BANK_ADDR, SDRAM_SIZE, SDRAM_DATA_WIDTH);
#if defined(SOC_SERIES_GD32H77x_H78X)
        rt_kprintf("sdram actual sdclk=%u Hz refresh_count=%u\n",
                   sdram_sdclk_hz, sdram_refresh_count);
#endif
#ifdef RT_USING_MEMHEAP_AS_HEAP
        if (_sdram_memory_boundary_test() != RT_EOK)
        {
            result = -RT_ERROR;
        }
        else if (rt_memheap_init(&system_heap, "sdram", (void *)SDRAM_HEAP_BEGIN, SDRAM_HEAP_SIZE) != RT_EOK)
        {
            LOG_E("SDRAM memheap init failed!");
            result = -RT_ERROR;
        }
        else
        {
            rt_kprintf("sdram memheap init success, mapped at 0x%X, size is %d bytes\n",
                       SDRAM_HEAP_BEGIN, SDRAM_HEAP_SIZE);
        }
#endif
    }

    sdram_ready = (result == RT_EOK);
    return result;
}
INIT_BOARD_EXPORT(SDRAM_Init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
#ifdef RT_USING_MEMHEAP_AS_HEAP
#define SDRAM_TEST_SIZE      (1024U * 1024U)
#define SDRAM_TEST_PASSES    8U

#if SDRAM_DATA_WIDTH_IN_NUMBER == 8
typedef uint8_t sdram_test_data_t;
#elif SDRAM_DATA_WIDTH_IN_NUMBER == 16
typedef uint16_t sdram_test_data_t;
#else
typedef uint32_t sdram_test_data_t;
#endif

static void sdram_test_print_speed(const char *operation, rt_tick_t ticks)
{
    uint32_t elapsed_ms;
    uint32_t speed;

    if (ticks == 0U)
    {
        rt_kprintf("%-8s %10u  <1 tick       N/A\n", operation,
                   SDRAM_TEST_SIZE * SDRAM_TEST_PASSES / 1024U);
        return;
    }

    elapsed_ms = (uint32_t)((uint64_t)ticks * 1000U / RT_TICK_PER_SECOND);
    speed = (uint32_t)((uint64_t)SDRAM_TEST_SIZE * SDRAM_TEST_PASSES *
                       RT_TICK_PER_SECOND * 100U / ((uint64_t)ticks * 1024U * 1024U));
    rt_kprintf("%-8s %10u %10u %8u.%02u\n", operation,
               SDRAM_TEST_SIZE * SDRAM_TEST_PASSES / 1024U,
               elapsed_ms, speed / 100U, speed % 100U);
}
#endif /* RT_USING_MEMHEAP_AS_HEAP */

int sdram_test(void)
{
#ifdef RT_USING_MEMHEAP_AS_HEAP
    void *allocation;
    volatile sdram_test_data_t *buffer;
    sdram_test_data_t data;
    sdram_test_data_t expected;
    uint32_t i;
    uint32_t pass;
    rt_tick_t start_time;
    rt_tick_t write_ticks;
    rt_tick_t read_ticks;
    int result = RT_EOK;

    if (!sdram_ready)
    {
        rt_kprintf("SDRAM test failed: SDRAM is not ready.\n");
        return -RT_ERROR;
    }

    /* Allocate from SDRAM explicitly and keep cache operations off heap metadata. */
    allocation = rt_memheap_alloc(&system_heap, SDRAM_TEST_SIZE + RT_CPU_CACHE_LINE_SZ - 1U);
    if (allocation == RT_NULL)
    {
        rt_kprintf("SDRAM test failed: cannot allocate %u KiB from the SDRAM heap.\n",
                   SDRAM_TEST_SIZE / 1024U);
        return -RT_ENOMEM;
    }
    buffer = (volatile sdram_test_data_t *)RT_ALIGN((rt_uintptr_t)allocation,
                                                   RT_CPU_CACHE_LINE_SZ);

    rt_kprintf("SDRAM test: buffer=%p, size=%u KiB, access=%u-bit, passes=%u\n",
               (void *)buffer, SDRAM_TEST_SIZE / 1024U,
               (unsigned int)(sizeof(*buffer) * 8U), SDRAM_TEST_PASSES);
    rt_kprintf("CPU sequential access; timing includes cache maintenance.\n");
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH | RT_HW_CACHE_INVALIDATE,
                        (void *)buffer, SDRAM_TEST_SIZE);
    __DSB();

    start_time = rt_tick_get();
    for (pass = 0; pass < SDRAM_TEST_PASSES; pass++)
    {
        for (i = 0; i < SDRAM_TEST_SIZE / sizeof(*buffer); i++)
        {
            buffer[i] = (sdram_test_data_t)(i ^ 0x55555555U);
        }
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)buffer, SDRAM_TEST_SIZE);
    }
    __DSB();
    write_ticks = rt_tick_get() - start_time;

    start_time = rt_tick_get();
    for (pass = 0; pass < SDRAM_TEST_PASSES; pass++)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)buffer, SDRAM_TEST_SIZE);
        for (i = 0; i < SDRAM_TEST_SIZE / sizeof(*buffer); i++)
        {
            (void)buffer[i];
        }
    }
    __DSB();
    read_ticks = rt_tick_get() - start_time;

    rt_kprintf("Operation  Total KiB    Time ms       MiB/s\n");
    sdram_test_print_speed("Write", write_ticks);
    sdram_test_print_speed("Read", read_ticks);

    /* Verify separately so comparisons are not counted as read throughput. */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)buffer, SDRAM_TEST_SIZE);
    for (i = 0; i < SDRAM_TEST_SIZE / sizeof(*buffer); i++)
    {
        expected = (sdram_test_data_t)(i ^ 0x55555555U);
        data = buffer[i];
        if (data != expected)
        {
            rt_kprintf("Verify: FAIL at %p, expected=0x%08X, actual=0x%08X\n",
                       (void *)&buffer[i], (unsigned int)expected, (unsigned int)data);
            result = -RT_ERROR;
            break;
        }
    }

    rt_memheap_free(allocation);
    if (result == RT_EOK)
    {
        rt_kprintf("Verify: PASS\n");
    }
    return result;
#else
    rt_kprintf("SDRAM test requires RT_USING_MEMHEAP_AS_HEAP.\n");
    return -RT_ENOSYS;
#endif /* RT_USING_MEMHEAP_AS_HEAP */
}
MSH_CMD_EXPORT(sdram_test, test SDRAM read/write speed and data integrity);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SDRAM */
