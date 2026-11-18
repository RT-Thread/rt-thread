/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#include "drv_usb_hw.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#if defined(RT_USING_USB_DEVICE)
#include "drv_usbd_int.h"
#include "drv_otghs_dev.h"
#endif

#if defined(RT_USING_USB_HOST)
#include "drv_usbh_int.h"
#include "drv_otghs_host.h"
#endif

#if defined(BSP_USING_USB)

#if defined(RT_USING_USB_HOST)
#ifndef USE_ULPI_PHY

#if !defined(BSP_USB_HOST_VBUS_PORT_RCC) || \
    !defined(BSP_USB_HOST_VBUS_PORT) || \
    !defined(BSP_USB_HOST_VBUS_PIN)
#error "Please define the USB host VBUS control pin in board.h"
#endif

#define HOST_POWERSW_PORT_RCC BSP_USB_HOST_VBUS_PORT_RCC
#define HOST_POWERSW_PORT     BSP_USB_HOST_VBUS_PORT
#define HOST_POWERSW_VBUS     BSP_USB_HOST_VBUS_PIN

#else

#ifdef USE_USBHS0
#define HOST_POWERSW_PORT_RCC RCU_GPIOC
#define HOST_POWERSW_PORT     GPIOC
#define HOST_POWERSW_VBUS     GPIO_PIN_7
#endif

#ifdef USE_USBHS1
#define HOST_POWERSW_PORT_RCC RCU_GPIOC
#define HOST_POWERSW_PORT     GPIOC
#define HOST_POWERSW_VBUS     GPIO_PIN_9
#endif

#endif

#endif

/*!
    \brief      configure USB GPIO
    \param[in]  usb_periph: USBHS0 or USBHS1
    \param[out] none
    \retval     none
*/
void usb_gpio_config(void)
{
#ifdef USE_USBHS0
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);

    /* ULPI_STP(PC0) GPIO pin configuration */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_0);

    /* ULPI_CK(PA5) GPIO pin configuration */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_5);

    /* ULPI_NXT(PC3) GPIO pin configuration */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_3);

    /* ULPI_DIR(PC2) GPIO pin configuration */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_2);

    /* ULPI_D1(PB0), ULPI_D2(PB1), ULPI_D3(PB10), ULPI_D4(PB11) \
       ULPI_D5(PB12), ULPI_D6(PB13) and ULPI_D7(PB5) GPIO pin configuration */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_0 |
                      GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ,
                            GPIO_PIN_12 |
                                GPIO_PIN_13 | GPIO_PIN_5);

    /* ULPI_D0(PA3) GPIO pin configuration */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_3);

    gpio_af_set(GPIOA, GPIO_AF_10, GPIO_PIN_5);
    gpio_af_set(GPIOB, GPIO_AF_10, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13);
    gpio_af_set(GPIOC, GPIO_AF_10, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);

#endif /* USE_USBHS0 */

#ifdef USE_USBHS1
    rcu_periph_clock_enable(RCU_GPIOH);
    rcu_periph_clock_enable(RCU_GPIOG);

    /* ULPI_STP(PH2) GPIO pin configuration */
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_2);


    /* ULPI_CK(PH5) GPIO pin configuration */
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_5);

    /* ULPI_NXT(PH4) GPIO pin configuration */
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_4);

    /* ULPI_DIR(PH3) GPIO pin configuration */
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_3);

    /* ULPI_D0(PH6) GPIO pin configuration */
    /* ULPI_D1(PH7), ULPI_D2(PH8), ULPI_D3(PH9), ULPI_D4(PH10) \
       ULPI_D5(PH11), ULPI_D6(PH12) and ULPI_D7(PG5) GPIO pin configuration */
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 |
                      GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ,
                            GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 |
                                GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);

    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, GPIO_PIN_5);

    gpio_af_set(GPIOG, GPIO_AF_8, GPIO_PIN_5);
    gpio_af_set(GPIOH, GPIO_AF_8, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
#endif /* USE_USBHS1 */
}

#ifdef USE_USBHS0
/*!
    \brief      this function handles USBHS0 interrupt
    \param[in]  usb_periph: USBHS0 or USBHS1
    \param[out] none
    \retval     none
*/
void USBHS0_IRQHandler(void)
{
    rt_interrupt_enter();

#if defined(BSP_USB_USING_DEVICE)
    gd_usb_irq_count++;
    usbd_isr(&gd_usb_device_core);
#endif

    rt_interrupt_leave();
}

#endif /* USE_USBHS0 */

#ifdef USE_USBHS1
/*!
    \brief      this function handles USBHS1 interrupt
    \param[in]  usb_periph: USBHS0 or USBHS1
    \param[out] none
    \retval     none
*/
void USBHS1_IRQHandler(void)
{
    rt_interrupt_enter();

#if defined(BSP_USB_USING_HOST)
    gd_usbh_irq_count++;
    usbh_isr(&gd_usb_host_core);
#endif

    rt_interrupt_leave();
}

#endif /* USE_USBHS1 */

/*!
    \brief      resume MCU clock
    \param[in]  usb_periph: USBHS0 or USBHS1
    \param[out] none
    \retval     none
*/
static void resume_mcu_clk(void)
{
    /* enable HXTAL */
    rcu_osci_on(RCU_HXTAL);

    /* wait till HXTAL is ready */
    while (RESET == rcu_flag_get(RCU_FLAG_HXTALSTB))
    {
    }

    /* enable PLL */
    rcu_osci_on(RCU_PLL0_CK);

    /* wait till PLL is ready */
    while (RESET == rcu_flag_get(RCU_FLAG_PLL0STB))
    {
    }

    /* select PLL as system clock source */
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL0P);

    /* wait till PLL is used as system clock source */
    while (RCU_SCSS_PLL0P != rcu_system_clock_source_get())
    {
    }
}

#ifdef USE_USBHS0
/*!
    \brief      this function handles USBHS0 wakeup interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USBHS0_WKUP_IRQHandler(void)
{
    rt_interrupt_enter();

    if (gd_usb_device_core.bp.low_power)
    {
        resume_mcu_clk();

#ifndef USE_IRC48M
        rcu_usb48m_clock_config(IDX_USBHS0, RCU_USB48MSRC_PLL0R);
#else
            /* enable IRC48M clock */
        rcu_osci_on(RCU_IRC48M);

            /* wait till IRC48M is ready */
        while (SUCCESS != rcu_osci_stab_wait(RCU_IRC48M))
        {
        }

        rcu_ck48m_clock_config(RCU_CK48MSRC_IRC48M);
#endif /* USE_IRC48M */

        rcu_periph_clock_enable(RCU_USBHS0);

        usb_clock_active(&gd_usb_device_core);
    }

    exti_interrupt_flag_clear(EXTI_31);

    rt_interrupt_leave();
}

#endif /* USE_USBHS0 */

#ifdef USE_USBHS1
/*!
    \brief      this function handles USBHS1 wakeup interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USBHS1_WKUP_IRQHandler(void)
{
    rt_interrupt_enter();

    if (gd_usb_host_core.bp.low_power)
    {
        resume_mcu_clk();

#ifndef USE_IRC48M
        rcu_usb48m_clock_config(IDX_USBHS1, RCU_USB48MSRC_PLL1Q);
#else
            /* enable IRC48M clock */
        rcu_osci_on(RCU_IRC48M);

            /* wait till IRC48M is ready */
        while (SUCCESS != rcu_osci_stab_wait(RCU_IRC48M))
        {
        }

        rcu_ck48m_clock_config(RCU_CK48MSRC_IRC48M);
#endif /* USE_IRC48M */

        rcu_periph_clock_enable(RCU_USBHS1);

        usb_clock_active(&gd_usb_host_core);
    }

    exti_interrupt_flag_clear(EXTI_32);

    rt_interrupt_leave();
}

#endif /* USE_USBHS1 */

#ifdef USB_DEDICATED_EP1_ENABLED

#ifdef USE_USBHS0
/*!
    \brief      this function handles USBHS0 dedicated endpoint 1 OUT interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USBHS0_EP1_OUT_IRQHandler(void)
{
    usbd_int_dedicated_ep1out(&cdc_acm);
}

#endif /* USE_USBHS0 */

#ifdef USE_USBHS1
/*!
    \brief      this function handles USBHS1 dedicated endpoint 1 OUT interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USBHS1_EP1_OUT_IRQHandler(void)
{
    usbd_int_dedicated_ep1out(&cdc_acm);
}

#endif /* USE_USBHS1 */

#ifdef USE_USBHS0
/*!
    \brief      this function handles USBHS0 dedicated endpoint 1 IN interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USBHS0_EP1_IN_IRQHandler(void)
{
    usbd_int_dedicated_ep1in(&cdc_acm);
}

#endif /* USE_USBHS0 */

#ifdef USE_USBHS1
/*!
    \brief      this function handles USBHS1 dedicated endpoint 1 IN interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USBHS1_EP1_IN_IRQHandler(void)
{
    usbd_int_dedicated_ep1in(&cdc_acm);
}

#endif /* USE_USBHS1 */

#endif /* USB_DEDICATED_EP1_ENABLED */

/*!
    \brief      configure USB clock
    \param[in]  usb_periph: USBHS0 or USBHS1
    \param[out] none
    \retval     none
*/
void usb_rcu_config(uint32_t usb_periph)
{
    pmu_usb_regulator_enable();
    pmu_usb_voltage_detector_enable();
    while (SET != pmu_flag_get(PMU_FLAG_USB33RF))
    {
    }

#ifndef USE_IRC48M
    if (USBHS0 == usb_periph)
    {
        rcu_periph_clock_enable(RCU_USBHS0);

        /* Required by the GD32H77x USBHS0 embedded-PHY startup sequence. */
        ((usb_gr *)USBHS0_REG_BASE)->GUSBCS |= GUSBCS_EMBPHY_FS;
        ((usb_gr *)USBHS0_REG_BASE)->GCCFG |= GCCFG_PWRON;

        rcu_pllusb0_config(RCU_PLLUSBHSPRE_HXTAL, RCU_PLLUSBHSPRE_DIV5,
                           RCU_PLLUSBHS_MUL96, RCU_USBHS_DIV10);
        RCU_ADDCTL1 |= RCU_ADDCTL1_PLLUSBHS0EN;
        while (0U == (RCU_ADDCTL1 & RCU_ADDCTL1_PLLUSBHS0STB))
        {
        }

        rcu_usb48m_clock_config(IDX_USBHS0, RCU_USB48MSRC_PLLUSBHS);
    }
    else if (USBHS1 == usb_periph)
    {
        rcu_periph_clock_enable(RCU_USBHS1);

        /* configure the pll1 input and output clock range */
        rcu_pll_input_output_clock_range_config(IDX_PLL1, RCU_PLL1RNG_4M_8M, RCU_PLL1VCO_192M_836M);

        rcu_pll1_config(5, 96, 2, 10, 2);
        /* enable PLL1Q clock output */
        rcu_pll_clock_output_enable(RCU_PLL1Q);
        rcu_osci_on(RCU_PLL1_CK);

        rcu_usbhs_pll1qpsc_config(IDX_USBHS1, RCU_USBHSPSC_DIV1);

        rcu_usb48m_clock_config(IDX_USBHS1, RCU_USB48MSRC_PLL1Q);
    }

#else
    /* enable IRC48M clock */
    rcu_osci_on(RCU_IRC48M);

    /* wait till IRC48M is ready */
    while (SUCCESS != rcu_osci_stab_wait(RCU_IRC48M))
    {
    }

    rcu_ck48m_clock_config(RCU_CK48MSRC_IRC48M);

    if (USBHS0 == usb_periph)
    {
        rcu_periph_clock_enable(RCU_USBHS0);
        rcu_usb48m_clock_config(IDX_USBHS0, RCU_USB48MSRC_IRC48M);
    }
    else if (USBHS1 == usb_periph)
    {
        rcu_periph_clock_enable(RCU_USBHS1);
        rcu_usb48m_clock_config(IDX_USBHS1, RCU_USB48MSRC_IRC48M);
    }

#endif /* USE_IRC48M */

#ifdef USE_ULPI_PHY
#ifdef USE_USBHS0
    rcu_periph_clock_enable(RCU_USBHS0ULPI);
#endif

#ifdef USE_USBHS1
    rcu_periph_clock_enable(RCU_USBHS1ULPI);
#endif
#endif /* USE_ULPI_PHY */
}

/*!
    \brief      configure USB interrupt
    \param[in]  usb_periph: USBHS0 or USBHS1
    \param[out] none
    \retval     none
*/
void usb_intr_config(uint32_t usb_periph)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);

    if (USBHS0 == usb_periph)
    {
        nvic_irq_enable((uint8_t)USBHS0_IRQn, 3U, 0U);
    }
    else if (USBHS1 == usb_periph)
    {
        nvic_irq_enable((uint8_t)USBHS1_IRQn, 3U, 0U);
    }

    /* enable the power module clock */
    rcu_periph_clock_enable(RCU_PMU);

    if (USBHS0 == usb_periph)
    {
        /* USB wakeup EXTI line configuration */
        exti_interrupt_flag_clear(EXTI_31);
        exti_init(EXTI_31, EXTI_INTERRUPT, EXTI_TRIG_RISING);
        exti_interrupt_enable(EXTI_31);

        nvic_irq_enable((uint8_t)USBHS0_WKUP_IRQn, 1U, 0U);
    }
    else if (USBHS1 == usb_periph)
    {
        /* USB wakeup EXTI line configuration */
        exti_interrupt_flag_clear(EXTI_32);
        exti_init(EXTI_32, EXTI_INTERRUPT, EXTI_TRIG_RISING);
        exti_interrupt_enable(EXTI_32);

        nvic_irq_enable((uint8_t)USBHS1_WKUP_IRQn, 1U, 0U);
    }

#ifdef USB_DEDICATED_EP1_ENABLED

#ifdef USE_USBHS0
    nvic_irq_enable((uint8_t)USBHS0_EP1_OUT_IRQn, 1U, 0U);
    nvic_irq_enable((uint8_t)USBHS0_EP1_IN_IRQn, 1U, 0U);
#endif /* USE_USBHS0 */

#ifdef USE_USBHS1
    nvic_irq_enable((uint8_t)USBHS1_EP1_OUT_IRQn, 1U, 0U);
    nvic_irq_enable((uint8_t)USBHS1_EP1_IN_IRQn, 1U, 0U);
#endif /* USE_USBHS1 */

#endif /* USB_DEDICATED_EP1_ENABLED */
}


#if defined(RT_USING_USB_HOST)
/*!
    \brief      drives the VBUS signal through GPIO
    \param[in]  state: VBUS states
    \param[out] none
    \retval     none
*/
void usb_vbus_drive(uint8_t state)
{
    if (0U == state)
    {
        /* disable is needed on output of the power switch */
        gpio_bit_reset(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
    }
    else
    {
        /* enable the power switch by driving the enable high */
        gpio_bit_set(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
    }
}

/*!
    \brief      configures the GPIO for the VBUS
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usb_vbus_config(void)
{
    rcu_periph_clock_enable(HOST_POWERSW_PORT_RCC);

    /* USB host VBUS control pin configuration */
    gpio_mode_set(HOST_POWERSW_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HOST_POWERSW_VBUS);
    gpio_output_options_set(HOST_POWERSW_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, HOST_POWERSW_VBUS);

    /* by default, disable is needed on output of the power switch */
    usb_vbus_drive(0U);

    /* delay is need for stabilizing the VBUS low in reset condition,
     * when VBUS = 1 and reset-button is pressed by user
     */
    usb_mdelay(200);
}

#endif

/*!
    \brief      delay in microseconds
    \param[in]  usec: value of delay required in microseconds
    \param[out] none
    \retval     none
*/
void usb_udelay(const uint32_t usec)
{
    rt_hw_us_delay(usec);
}

/*!
    \brief      delay in milliseconds
    \param[in]  msec: value of delay required in milliseconds
    \param[out] none
    \retval     none
*/
void usb_mdelay(const uint32_t msec)
{
    rt_hw_us_delay(msec * 1000U);
}

/*!
    \brief      configure the PLL of USB
    \param[in]  usb_periph: USBHS0
    \param[out] none
    \retval     none
*/
void pllusb_rcu_config(uint32_t usb_periph)
{
    if (USBHS0 == usb_periph)
    {
        rcu_pllusb0_config(RCU_PLLUSBHSPRE_HXTAL, RCU_PLLUSBHSPRE_DIV5, RCU_PLLUSBHS_MUL96, RCU_USBHS_DIV10);
        RCU_ADDCTL1 |= RCU_ADDCTL1_PLLUSBHS0EN;
        while (0U == (RCU_ADDCTL1 & RCU_ADDCTL1_PLLUSBHS0STB))
        {
        }

        rcu_usb48m_clock_config(IDX_USBHS0, RCU_USB48MSRC_PLLUSBHS);
    }
}

#endif /* BSP_USING_USB */
