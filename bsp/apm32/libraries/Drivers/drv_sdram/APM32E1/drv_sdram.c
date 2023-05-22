/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-28     luobeihai    first version
 */

#include <board.h>

#ifdef BSP_USING_SDRAM
#include "drv_sdram.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.sdram"
#include <drv_log.h>

/* SDRAM GPIO Clock */
#define RCM_SDRAM_GPIO_PERIPH (RCM_APB2_PERIPH_AFIO  | \
                                RCM_APB2_PERIPH_GPIOB | \
                                RCM_APB2_PERIPH_GPIOC | \
                                RCM_APB2_PERIPH_GPIOD | \
                                RCM_APB2_PERIPH_GPIOE | \
                                RCM_APB2_PERIPH_GPIOF | \
                                RCM_APB2_PERIPH_GPIOG)

/* SDRAM Peripheral Clock */
#define RCM_SDRAM_PERIPH (RCM_AHB_PERIPH_SMC)

#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

/**
 * @brief   SDRAM divider Number
 */
typedef enum
{
    RCM_DMC_DIV_1,
    RCM_DMC_DIV_2,
    RCM_DMC_DIV_4 = 3
} RCM_DMC_DIV_T;

/**
  * @brief  Configs the SDRAM clock prescaler
  * @param  SDRAMDiv: Specifies the SDRAM clock prescaler from the DMC clock.
  * @retval None
  */
static void RCM_ConfigSDRAMCLK(RCM_DMC_DIV_T SDRAMDiv)
{
    RCM->CFG_B.SDRAMPSC = SDRAMDiv;
}

/**
  * @brief  sdram gpio init
  * @param  None
  * @retval None
  */
static void SDRAM_GPIO_Init(void)
{
    GPIO_Config_T gpioConfig;

    RCM_EnableAPB2PeriphClock(RCM_SDRAM_GPIO_PERIPH);

    /** SDRAM pins assignment */
    /**
     +-------------------------+--------------------------+--------------------------+
     | PB10 <-> MMC_SDRAM_UDQM | PC10 <-> MMC_SDRAM_D8    | PD2  <-> MMC_SDRAM_D10   |
     | PB11 <-> MMC_SDRAM_CKE  | PC11 <-> MMC_SDRAM_D9    | PD3  <-> MMC_SDRAM_D11   |
     |                         |                          | PD4  <-> MMC_SDRAM_D12   |
     |                         |                          | PD5  <-> MMC_SDRAM_D13   |
     |                         |                          | PD6  <-> MMC_SDRAM_D14   |
     +-------------------------+--------------------------+--------------------------+
     | PE3  <-> MMC_SDRAM_D4   | PF0  <-> MMC_SDRAM_D7    | PG0  <-> MMC_SDRAM_A3    |
     | PE5  <-> MMC_SDRAM_D5   | PF2  <-> MMC_SDRAM_NCS   | PG9  <-> MMC_SDRAM_D15   |
     | PE6  <-> MMC_SDRAM_D6   | PF4  <-> MMC_SDRAM_NRAS  | PG12 <-> MMC_SDRAM_D0    |
     | PE8  <-> MMC_SDRAM_A4   | PF5  <-> MMC_SDRAM_NCAS  | PG13 <-> MMC_SDRAM_D1    |
     | PE9  <-> MMC_SDRAM_A5   | PF6  <-> MMC_SDRAM_NWE   | PG14 <-> MMC_SDRAM_D2    |
     | PE10 <-> MMC_SDRAM_A6   | PF10 <-> MMC_SDRAM_LDQM  | PG15 <-> MMC_SDRAM_D3    |
     | PE11 <-> MMC_SDRAM_A7   | PF11 <-> MMC_SDRAM_Bank  |                          |
     | PE12 <-> MMC_SDRAM_A8   | PF12 <-> MMC_SDRAM_A10   |                          |
     | PE13 <-> MMC_SDRAM_A9   | PF13 <-> MMC_SDRAM_A0    |                          |
     | PE15 <-> MMC_SDRAM_CLK  | PF14 <-> MMC_SDRAM_A1    |                          |
     |                         | PF15 <-> MMC_SDRAM_A2    |                          |
     +-------------------------+--------------------------+--------------------------+
    */

    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.mode = GPIO_MODE_AF_PP;

    gpioConfig.pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_Config(GPIOB, &gpioConfig);

    gpioConfig.pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_Config(GPIOC, &gpioConfig);

    gpioConfig.pin = GPIO_PIN_2 | GPIO_PIN_3 |
                     GPIO_PIN_4 | GPIO_PIN_5 |
                     GPIO_PIN_6;
    GPIO_Config(GPIOD, &gpioConfig);

    gpioConfig.pin = GPIO_PIN_3 | GPIO_PIN_5 |
                     GPIO_PIN_6 | GPIO_PIN_8 |
                     GPIO_PIN_9 | GPIO_PIN_10|
                     GPIO_PIN_11 | GPIO_PIN_12 |
                     GPIO_PIN_13 | GPIO_PIN_15 ;
    GPIO_Config(GPIOE, &gpioConfig);

    gpioConfig.pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_4 |
                     GPIO_PIN_5 | GPIO_PIN_6 |
                     GPIO_PIN_10 |GPIO_PIN_11 |
                     GPIO_PIN_12 | GPIO_PIN_13|
                     GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Config(GPIOF, &gpioConfig);

    gpioConfig.pin = GPIO_PIN_0 | GPIO_PIN_9|
                     GPIO_PIN_12 | GPIO_PIN_13 |
                     GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Config(GPIOG, &gpioConfig);
}

/**
  * @brief  sdram init
  * @param  None
  * @retval None
  */
static int SDRAM_Init(void)
{
    int result = RT_EOK;

    DMC_Config_T dmc_init_config;
    DMC_TimingConfig_T dmc_timing_config;

    /* Config the SDRAM clock prescaler */
    RCM_ConfigSDRAMCLK(RCM_DMC_DIV_2);

    /* enable sdram clock */
    RCM_EnableAHBPeriphClock(RCM_SDRAM_PERIPH);

    /* sdram gpio init */
    SDRAM_GPIO_Init();

    /* dmc timing config */
    dmc_timing_config.latencyCAS = DMC_CAS_LATENCY_3;        //!< Configure CAS latency period
    dmc_timing_config.tARP       = DMC_AUTO_REFRESH_10;      //!< Configure auto refresh period
    dmc_timing_config.tRAS       = DMC_RAS_MINIMUM_5;        //!< Configure line activation and precharging minimum time
    dmc_timing_config.tCMD       = DMC_ATA_CMD_7;            //!< Configure active to active period
    dmc_timing_config.tRCD       = DMC_DELAY_TIME_2;         //!< Configure RAS To CAS delay Time
    dmc_timing_config.tRP        = DMC_PRECHARGE_2;          //!< Configure precharge period
    dmc_timing_config.tWR        = DMC_NEXT_PRECHARGE_2;     //!< Configure time between the Last Data and The Next Precharge for write
    dmc_timing_config.tXSR       = 6;                        //!< Configure XSR0
    dmc_timing_config.tRFP       = 0xC3;                     //!< Configure refresh Cycle

#if SDRAM_TARGET_BANK == 1
    dmc_init_config.bankWidth     = DMC_BANK_WIDTH_1;        //!< Configure bank address width
#else
    dmc_init_config.bankWidth     = DMC_BANK_WIDTH_2;        //!< Configure bank address width
#endif
    dmc_init_config.clkPhase      = DMC_CLK_PHASE_REVERSE;   //!< Configure clock phase
    dmc_init_config.rowWidth      = SDRAM_ROW_BITS;          //!< Configure row address width
    dmc_init_config.colWidth      = SDRAM_COLUMN_BITS;       //!< Configure column address width
    dmc_init_config.memorySize    = SDRAM_MEMORY_SIZE;
    dmc_init_config.timing        = dmc_timing_config;

    DMC_Config(&dmc_init_config);
    DMC_ConfigOpenBank(DMC_BANK_NUMBER_2);
    DMC_EnableAccelerateModule();

    DMC_Enable();

    LOG_D("sdram clock: %d MHz\r\n", RCM_ReadSYSCLKFreq()/1000000/(RCM->CFG_B.SDRAMPSC + 1));
    LOG_D("sdram init success, mapped at 0x%X, size is %d bytes, data width is %d", SDRAM_BANK_ADDR, SDRAM_SIZE, SDRAM_DATA_WIDTH);

#ifdef RT_USING_MEMHEAP_AS_HEAP
    /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
    rt_memheap_init(&system_heap, "sdram", (void *)SDRAM_BANK_ADDR, SDRAM_SIZE);
#endif

    return result;
}
INIT_BOARD_EXPORT(SDRAM_Init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int sdram_test(void)
{
    int i = 0;
    uint32_t start_time = 0, time_cast = 0;
#if SDRAM_DATA_WIDTH == 8
    char data_width = 1;
    uint8_t data = 0;
#elif SDRAM_DATA_WIDTH == 16
    char data_width = 2;
    uint16_t data = 0;
#else
    char data_width = 4;
    uint32_t data = 0;
#endif

    /* write data */
    LOG_D("Writing the %ld bytes data, waiting....", SDRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == 8
        *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint8_t)(i % 100);
#elif SDRAM_DATA_WIDTH == 16
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint16_t)(i % 1000);
#else
        *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint32_t)(i % 1000);
#endif
    }
    time_cast = rt_tick_get() - start_time;
    LOG_D("Write data success, total time: %d.%03dS.", time_cast / RT_TICK_PER_SECOND,
          time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    LOG_D("start Reading and verifying data, waiting....");
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == 8
        data = *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 100)
        {
            LOG_E("SDRAM test failed!");
            break;
        }
#elif SDRAM_DATA_WIDTH == 16
        data = *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 1000)
        {
            LOG_E("SDRAM test failed!");
            break;
        }
#else
        data = *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 1000)
        {
            LOG_E("SDRAM test failed!");
            break;
        }
#endif
    }

    if (i >= SDRAM_SIZE / data_width)
    {
        LOG_D("SDRAM test success!");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(sdram_test, sdram test)
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SDRAM */
