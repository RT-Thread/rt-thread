/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"

#ifdef RT_USING_PDM

/* messagequeue define */
struct rt_messagequeue pdm_mq;

static rt_uint8_t am_pdm_buffer_pool[1024];

#define NWA_FRAME_SAMPLES   160    /* 8k, 16bit, mono audio data */
#define PDM_FIFO_THRESHOLD  NWA_FRAME_SAMPLES

#define PDM_GPIO_CLK        22
#define PDM_GPIO_CFG_CLK    AM_HAL_PIN_22_PDM_CLK
#define PDM_GPIO_DATA       23
#define PDM_GPIO_CFG_DATA   AM_HAL_PIN_23_PDM_DATA

static am_hal_pdm_config_t g_sPDMConfig =
{
    AM_HAL_PDM_PCFG_LRSWAP_DISABLE | AM_HAL_PDM_PCFG_RIGHT_PGA_0DB | AM_HAL_PDM_PCFG_LEFT_PGA_0DB
            | AM_HAL_PDM_PCFG_MCLKDIV_DIV1 | AM_HAL_PDM_PCFG_SINC_RATE(48) | AM_HAL_PDM_PCFG_ADCHPD_ENABLE
            | AM_HAL_PDM_PCFG_HPCUTOFF(0x1) | AM_HAL_PDM_PCFG_CYCLES(0x1) | AM_HAL_PDM_PCFG_SOFTMUTE_DISABLE
            | AM_HAL_PDM_PCFG_PDMCORE_ENABLE, /* Set the PDM configuration */
    AM_HAL_PDM_IOCLK_750KHZ | AM_HAL_PDM_VCFG_RSTB_NORMAL | AM_HAL_PDM_VCFG_PDMCLK_ENABLE
            | AM_HAL_PDM_VCFG_I2SMODE_DISABLE | AM_HAL_PDM_VCFG_BCLKINV_DISABLE | AM_HAL_PDM_VCFG_DMICDEL_DISABLE
            | AM_HAL_PDM_VCFG_SELAP_INTERNAL | AM_HAL_PDM_VCFG_PACK_DISABLE | AM_HAL_PDM_VCFG_CHANNEL_LEFT, /* Set the Voice Configuration */
    PDM_FIFO_THRESHOLD, /* Select the FIFO PCM sample threshold 0~256 */
};

/**
 * @brief Get the pdm data.
 *
 * @param None.
 *
 * This function Get the pdm data.
 *
 * @return None.
 */
rt_uint8_t am_pdm_data_get(rt_uint8_t *buff, rt_uint16_t size)
{
    rt_uint8_t pdm_rbufftemp[340];

    /* wait pdm message forever */
    rt_mq_recv(&pdm_mq, pdm_rbufftemp, 340, RT_WAITING_FOREVER);

    /* copy the data */
    rt_memcpy(buff, (char *)pdm_rbufftemp, size);

    return 0;
}

/**
 * @brief Start the pdm.
 *
 * @param None.
 *
 * This function Start the pdm.
 *
 * @return None.
 */
void am_pdm_start(void)
{
    /* Enable PDM */
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);
    am_hal_pdm_enable();
}

/**
 * @brief Stop the pdm.
 *
 * @param None.
 *
 * This function Stop the pdm.
 *
 * @return None.
 */
void am_pdm_stop(void)
{
    /* Disable PDM */
    am_hal_interrupt_disable(AM_HAL_INTERRUPT_PDM);
    am_hal_pdm_disable();
}

/**
 * @brief Get the pdm left gain.
 *
 * @param None.
 *
 * This function Get the pdm left gain.
 *
 * @return gain_val.
 */
uint8_t am_pdm_left_gain_get(void)
{
    /* get the left gain */
    return am_hal_pdm_left_gain_get();
}

/**
 * @brief Set the pdm left gain.
 *
 * @param gain_val.
 *
 * This function Set the pdm left gain.
 *
 * @return None.
 */
void am_pdm_left_gain_set(uint8_t gain_val)
{
    /* set the left gain */
    am_hal_pdm_left_gain_set(gain_val);
}

/**
 * @brief Get the pdm right gain.
 *
 * @param None.
 *
 * This function Get the pdm right gain.
 *
 * @return gain_val.
 */
uint8_t am_pdm_right_gain_get(void)
{
    /* get the right gain */
    return am_hal_pdm_right_gain_get();
}

/**
 * @brief Set the pdm right gain.
 *
 * @param gain_val.
 *
 * This function Set the pdm right gain.
 *
 * @return None.
 */
void am_pdm_right_gain_set(uint8_t gain_val)
{
    /* set the right gain */
    am_hal_pdm_right_gain_set(gain_val);
}

/**
 * @brief Interrupt handler for the PDM
 *
 * This function is Interrupt handler for the PDM
 *
 * @return None.
 */
void am_pdm_isr (void)
{
    int i;
    rt_int16_t pdm_sbufftemp[160];

    /* Clear the PDM interrupt */
    am_hal_pdm_int_clear(AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF | AM_HAL_PDM_INT_FIFO);

    for (i = 0; i < PDM_FIFO_THRESHOLD; i++)  /* adjust as needed */
    {
        pdm_sbufftemp[i] = (rt_int16_t)am_hal_pdm_fifo_data_read();
    }

    /* send the message */
    rt_mq_send(&pdm_mq, pdm_sbufftemp, PDM_FIFO_THRESHOLD*sizeof(rt_int16_t));
}

/**
 * @brief Initialize the PDM
 *
 * This function initialize the PDM
 *
 * @return None.
 */
int rt_hw_pdm_init(void)
{
    /* Enable power to modules used */
    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_PDM);

    /* Enable the PDM clock and data */
    am_hal_gpio_pin_config(PDM_GPIO_CLK, PDM_GPIO_CFG_CLK | AM_HAL_GPIO_HIGH_DRIVE);
    am_hal_gpio_pin_config(PDM_GPIO_DATA, PDM_GPIO_CFG_DATA );

    /* PDM setting */
    am_hal_pdm_config(&g_sPDMConfig);

    /* Enable PDM interrupts */
    am_hal_pdm_int_enable(AM_HAL_PDM_INT_FIFO);

    /* Clear PDM interrupts */
    am_hal_pdm_int_clear(AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF | AM_HAL_PDM_INT_FIFO);

    /* messagequeue init */
    rt_mq_init(&pdm_mq, "mq_pdm",
            &am_pdm_buffer_pool[0],
            340 - sizeof(void*),
            sizeof(am_pdm_buffer_pool),
            RT_IPC_FLAG_FIFO);

    //rt_kprintf("pdm_init!\n");

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(rt_hw_pdm_init);
#endif

#endif

/*@}*/
