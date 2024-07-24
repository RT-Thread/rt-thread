/*!
    \file    gd32h7xx_syscfg.c
    \brief   SYSCFG driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32h7xx_syscfg.h"
/*!
    \brief      reset the SYSCFG registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_deinit(void)
{
    rcu_periph_reset_enable(RCU_SYSCFGRST);
    rcu_periph_reset_disable(RCU_SYSCFGRST);
}

/*!
    \brief      enable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9)
    \param[in]  i2c_fmp
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
      \arg        SYSCFG_I2C2_FMP: I2C2 fast mode plus
      \arg        SYSCFG_I2C3_FMP: I2C3 fast mode plus
      \arg        SYSCFG_I2C_FMP_PB6: I2C fast mode plus on PB6 pin
      \arg        SYSCFG_I2C_FMP_PB7: I2C fast mode plus on PB7 pin
      \arg        SYSCFG_I2C_FMP_PB8: I2C fast mode plus on PB8 pin
      \arg        SYSCFG_I2C_FMP_PB9: I2C fast mode plus on PB9 pin
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp)
{
    SYSCFG_PMCFG |= i2c_fmp;
}

/*!
    \brief      disable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9)
    \param[in]  i2c_fmp
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
      \arg        SYSCFG_I2C2_FMP: I2C2 fast mode plus
      \arg        SYSCFG_I2C3_FMP: I2C3 fast mode plus
      \arg        SYSCFG_I2C_FMP_PB6: I2C fast mode plus on PB6 pin
      \arg        SYSCFG_I2C_FMP_PB7: I2C fast mode plus on PB7 pin
      \arg        SYSCFG_I2C_FMP_PB8: I2C fast mode plus on PB8 pin
      \arg        SYSCFG_I2C_FMP_PB9: I2C fast mode plus on PB9 pin
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp)
{
    SYSCFG_PMCFG &= (uint32_t)(~i2c_fmp);
}

/*!
    \brief      open analog switch (Pxy and Pxy_C are separated pads)
    \param[in]  gpio_answ: GPIO analog switch
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_PA0_ANALOG_SWITCH: PA0 analog switch
      \arg        SYSCFG_PA1_ANALOG_SWITCH: PA1 analog switch
      \arg        SYSCFG_PC2_ANALOG_SWITCH: PC2 analog switch
      \arg        SYSCFG_PC3_ANALOG_SWITCH: PC3 analog switch
    \param[out] none
    \retval     none
*/
void syscfg_analog_switch_enable(uint32_t gpio_answ)
{
    SYSCFG_PMCFG |= gpio_answ;
}

/*!
    \brief      close analog switch (Pxy and Pxy_C are connected through the analog switch)
    \param[in]  gpio_answ: GPIO analog switch
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_PA0_ANALOG_SWITCH: PA0 analog switch
      \arg        SYSCFG_PA1_ANALOG_SWITCH: PA1 analog switch
      \arg        SYSCFG_PC2_ANALOG_SWITCH: PC2 analog switch
      \arg        SYSCFG_PC3_ANALOG_SWITCH: PC3 analog switch
    \param[out] none
    \retval     none
*/
void syscfg_analog_switch_disable(uint32_t gpio_answ)
{
    SYSCFG_PMCFG &= (uint32_t)(~gpio_answ);
}

/*!
    \brief      configure the PHY interface for the ethernet MAC
    \param[in]  enet_periph: ENETx(x=0,1)
    \param[in]  phy_interface: specifies the media interface mode
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_ENET_PHY_MII: MII mode is selected
      \arg        SYSCFG_ENET_PHY_RMII: RMII mode is selected
    \param[out] none
    \retval     none
*/
void syscfg_enet_phy_interface_config(uint32_t ethernet, uint32_t phy_interface)
{
    uint32_t reg;
    /* read the value of SYSCFG_PMCFG register */
    reg = SYSCFG_PMCFG;
    /* configure the ENET media interface */
    if(ENET0 == ethernet)
    {
        reg &= ~SYSCFG_PMCFG_ENET0_PHY_SEL;
        reg |= ENET0_MEDIA_INTERFACE(phy_interface);
    } else {
        reg &= ~SYSCFG_PMCFG_ENET1_PHY_SEL;
        reg |= ENET1_MEDIA_INTERFACE(phy_interface);
    }
    SYSCFG_PMCFG = reg;
}

/*!
    \brief      configure the GPIO pin as EXTI Line
    \param[in]  exti_port: specify the GPIO port used in EXTI
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_GPIOx(x = A,B,C,D,E,F,G,H,J,K): EXTI GPIO port
    \param[in]  exti_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_PINx(GPIOA x = 0..15,GPIOB x = 0..15,GPIOC x = 0..15,GPIOD x = 0..15,GPIOE x = 0..15,
                  GPIOF x = 0..15,GPIOG x = 0..15,GPIOH x = 0..15,GPIOI x = 0..15,GPIOJ x = 8,9,10,11, GPIOK x = 0,1,2,4,5,6): EXTI GPIO pin
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t clear_exti_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(exti_pin)));
    uint32_t config_exti_mask = ((uint32_t)exti_port) << (EXTI_SS_MSTEP(exti_pin));

    switch(exti_pin / EXTI_SS_JSTEP)
    {
    case EXTISS0:
        /* clear EXTI source line(0..3) */
        SYSCFG_EXTISS0 &= clear_exti_mask;
        /* configure EXTI soure line(0..3) */
        SYSCFG_EXTISS0 |= config_exti_mask;
        break;
    case EXTISS1:
        /* clear EXTI soure line(4..7) */
        SYSCFG_EXTISS1 &= clear_exti_mask;
        /* configure EXTI soure line(4..7) */
        SYSCFG_EXTISS1 |= config_exti_mask;
        break;
    case EXTISS2:
        /* clear EXTI soure line(8..11) */
        SYSCFG_EXTISS2 &= clear_exti_mask;
        /* configure EXTI soure line(8..11) */
        SYSCFG_EXTISS2 |= config_exti_mask;
        break;
    case EXTISS3:
        /* clear EXTI soure line(12..15) */
        SYSCFG_EXTISS3 &= clear_exti_mask;
        /* configure EXTI soure line(12..15) */
        SYSCFG_EXTISS3 |= config_exti_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable module lockup function (function can be disabled by system reset)
    \param[in]  lockup:
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_LVD_LOCKUP: LVD signal
      \arg        SYSCFG_CPU_LOCKUP: CPU lockup signal
      \arg        SYSCFG_BKPRAM_LOCKUP: Region 2 backup SRAM ECC double error signal
      \arg        SYSCFG_SRAM1_LOCKUP: Region 1 SRAM1 ECC double error signal
      \arg        SYSCFG_SRAM0_LOCKUP: Region 1 SRAM0 ECC double error signal
      \arg        SYSCFG_DTCM_LOCKUP: Region 0 DTCM ECC double error signal
      \arg        SYSCFG_ITCM_LOCKUP: Region 0 ITCM-RAM ECC double error signal
      \arg        SYSCFG_AXIRAM_LOCKUP: Region 0 AXI-SRAM ECC double error signal
    \param[out] none
    \retval     none
*/
void syscfg_lockup_enable(uint32_t lockup)
{
    SYSCFG_LKCTL |= lockup;
}

/*!
    \brief      select timer channel input source
    \param[in]  timer_input: TIMER channel input select, refer to timer_channel_input_enum
      \arg        TIMER7_CI0_INPUT_TIMER7_CH0: select CMP1 output as TIMER7 CI0
      \arg        TIMER7_CI0_INPUT_CMP1_OUT: select TIMER7 CH0 as TIMER7 CI0
      \arg        TIMER7_CI1_INPUT_TIMER7_CH1: select TIMER7 CH1 as TIMER7 CI1
      \arg        TIMER7_CI2_INPUT_TIMER7_CH2: select TIMER7 CH2 as TIMER7 CI2
      \arg        TIMER7_CI3_INPUT_TIMER7_CH3: select TIMER7 CH3 as TIMER7 CI3
      \arg        TIMER0_CI0_INPUT_TIMER0_CH0: select CMP0 output as TIMER0 CI0
      \arg        TIMER0_CI0_INPUT_CMP0_OUT: select TIMER0 CH0 as TIMER0 CI0
      \arg        TIMER0_CI1_INPUT_TIMER0_CH1: select TIMER0 CH1 as TIMER0 CI1
      \arg        TIMER0_CI2_INPUT_TIMER0_CH2: select TIMER0 CH2 as TIMER0 CI2
      \arg        TIMER0_CI3_INPUT_TIMER0_CH3: select TIMER0 CH3 as TIMER0 CI3
      \arg        TIMER2_CI0_INPUT_TIMER2_CH0: select TIMER2 CH0 as TIMER2 CI0
      \arg        TIMER2_CI0_INPUT_CMP0_OUT: select CMP0 as TIMER2 CI0
      \arg        TIMER2_CI0_INPUT_CMP1_OUT: select CMP1 as TIMER2 CI0
      \arg        TIMER2_CI0_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 as TIMER2 CI0
      \arg        TIMER2_CI1_INPUT_TIMER2_CH1: select TIMER2 CH1 as TIMER2 CI1
      \arg        TIMER2_CI2_INPUT_TIMER2_CH2: select TIMER2 CH2 as TIMER2 CI2
      \arg        TIMER2_CI3_INPUT_TIMER2_CH3: select TIMER2 CH3 as TIMER2 CI3
      \arg        TIMER1_CI0_INPUT_TIMER1_CH0: select TIMER1 CH0 as TIMER1 CI0
      \arg        TIMER1_CI1_INPUT_TIMER1_CH1: select TIMER1 CH1 as TIMER1 CI1
      \arg        TIMER1_CI2_INPUT_TIMER1_CH2: select TIMER1 CH2 as TIMER1 CI2
      \arg        TIMER1_CI3_INPUT_TIMER1_CH3: select TIMER1 CH3 as TIMER1 CI3
      \arg        TIMER1_CI3_INPUT_CMP0_OUT: select CMP0 output as TIMER1 CI3
      \arg        TIMER1_CI3_INPUT_CMP1_OUT: select CMP1 output as TIMER1 CI3
      \arg        TIMER1_CI3_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 output as TIMER1 CI3
      \arg        TIMER4_CI0_INPUT_TIMER4_CH0: select TIMER4 CH0 as TIMER4 CI0
      \arg        TIMER4_CI1_INPUT_TIMER4_CH1: select TIMER4 CH1 as TIMER4 CI1
      \arg        TIMER4_CI2_INPUT_TIMER4_CH2: select TIMER4 CH2 as TIMER4 CI2
      \arg        TIMER4_CI3_INPUT_TIMER4_CH3: select TIMER4 CH3 as TIMER4 CI3
      \arg        TIMER3_CI0_INPUT_TIMER3_CH0: select TIMER3 CH0 as TIMER3 CI0
      \arg        TIMER3_CI1_INPUT_TIMER3_CH1: select TIMER3 CH1 as TIMER3 CI1
      \arg        TIMER3_CI2_INPUT_TIMER3_CH2: select TIMER3 CH2 as TIMER3 CI2
      \arg        TIMER3_CI3_INPUT_TIMER3_CH3: select TIMER3 CH3 as TIMER3 CI3
      \arg        TIMER23_CI0_INPUT_TIMER23_CH0: select TIMER23 CH0 as TIMER23 CI0
      \arg        TIMER23_CI1_INPUT_TIMER23_CH1: select TIMER23 CH1 as TIMER23 CI1
      \arg        TIMER23_CI2_INPUT_TIMER23_CH2: select TIMER23 CH2 as TIMER23 CI2
      \arg        TIMER23_CI3_INPUT_TIMER23_CH3: select TIMER23 CH3 as TIMER23 CI3
      \arg        TIMER22_CI0_INPUT_TIMER22_CH0: select TIMER22 CH0 as TIMER22 CI0
      \arg        TIMER22_CI1_INPUT_TIMER22_CH1: select TIMER22 CH1 as TIMER22 CI1
      \arg        TIMER22_CI2_INPUT_TIMER22_CH2: select TIMER22 CH2 as TIMER22 CI2
      \arg        TIMER22_CI3_INPUT_TIMER22_CH3: select TIMER22 CH3 as TIMER22 CI3
      \arg        TIMER22_CI3_INPUT_CMP0_OUT: select CMP0 output as TIMER22 CI3
      \arg        TIMER22_CI3_INPUT_CMP1_OUT: select CMP1 output as TIMER22 CI3
      \arg        TIMER22_CI3_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 output as TIMER22 CI3
      \arg        TIMER31_CI0_INPUT_TIMER31_CH0: select TIMER31 CH0 as TIMER31 CI0
      \arg        TIMER31_CI0_INPUT_CMP0_OUT: select CMP0 output as TIMER31 CI0
      \arg        TIMER31_CI0_INPUT_CMP1_OUT: select CMP1 output as TIMER31 CI0
      \arg        TIMER31_CI0_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 output as TIMER31 CI0
      \arg        TIMER31_CI1_INPUT_TIMER31_CH1: select TIMER31 CH1 as TIMER31 CI1
      \arg        TIMER31_CI2_INPUT_TIMER31_CH2: select TIMER31 CH2 as TIMER31 CI2
      \arg        TIMER31_CI3_INPUT_TIMER31_CH3: select TIMER31 CH3 as TIMER31 CI3
      \arg        TIMER30_CI0_INPUT_TIMER30_CH0: select TIMER30 CH0 as TIMER30 CI0
      \arg        TIMER30_CI0_INPUT_CMP0_OUT: select CMP0 output as TIMER30 CI0
      \arg        TIMER30_CI0_INPUT_CMP1_OUT: select CMP1 output as TIMER30 CI0
      \arg        TIMER30_CI0_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 output as TIMER30 CI0
      \arg        TIMER30_CI1_INPUT_TIMER30_CH1: select TIMER30 CH1 as TIMER30 CI1
      \arg        TIMER30_CI2_INPUT_TIMER30_CH2: select TIMER30 CH2 as TIMER30 CI2
      \arg        TIMER30_CI3_INPUT_TIMER30_CH3: select TIMER30 CH3 as TIMER30 CI3
      \arg        TIMER14_CI0_INPUT_TIMER14_CH0: select TIMER14 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_TIMER1_CH0: select TIMER1 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_TIMER2_CH0: select TIMER2 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_TIMER3_CH0: select TIMER3 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_LXTAL: select LXTAL as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER14 CI0
      \arg        TIMER14_CI1_INPUT_TIMER14_CH1: select TIMER14 CH1 as TIMER14 CI1
      \arg        TIMER14_CI1_INPUT_TIMER1_CH1: select TIMER1 CH1 as TIMER14 CI1
      \arg        TIMER14_CI1_INPUT_TIMER2_CH1: select TIMER2 CH1 as TIMER14 CI1
      \arg        TIMER14_CI1_INPUT_TIMER3_CH1: select TIMER3 CH1 as TIMER14 CI1
      \arg        TIMER40_CI0_INPUT_TIMER40_CH0: select TIMER40 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_TIMER2_CH0: select TIMER2 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_TIMER3_CH0: select TIMER3 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_TIMER4_CH0: select TIMER4 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_LXTAL: select LXTAL as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER40 CI0
      \arg        TIMER40_CI1_INPUT_TIMER40_CH1: select TIMER40 CH1 as TIMER40 CI0
      \arg        TIMER40_CI1_INPUT_TIMER2_CH1: select TIMER2 CH1 as TIMER40 CI0
      \arg        TIMER40_CI1_INPUT_TIMER3_CH1: select TIMER3 CH1 as TIMER40 CI0
      \arg        TIMER40_CI1_INPUT_TIMER4_CH1: select TIMER4 CH1 as TIMER40 CI0
      \arg        TIMER41_CI0_INPUT_TIMER41_CH0: select TIMER41 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_TIMER3_CH0: select TIMER3 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_TIMER4_CH0: select TIMER4 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_TIMER22_CH0: select TIMER22 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_LXTAL: select LXTAL as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER41 CI0
      \arg        TIMER41_CI1_INPUT_TIMER41_CH1: select TIMER41 CH1 as TIMER41 CI1
      \arg        TIMER41_CI1_INPUT_TIMER3_CH1: select TIMER3 CH1 as TIMER41 CI1
      \arg        TIMER41_CI1_INPUT_TIMER4_CH1: select TIMER4 CH1 as TIMER41 CI1
      \arg        TIMER41_CI1_INPUT_TIMER22_CH1: select TIMER22 CH1 as TIMER41 CI1
      \arg        TIMER42_CI0_INPUT_TIMER42_CH0: select TIMER42 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_TIMER4_CH0: select TIMER4 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_TIMER22_CH0: select TIMER22 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_TIMER23_CH0: select TIMER23 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_LXTAL: select LXTAL as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER42 CI0
      \arg        TIMER42_CI1_INPUT_TIMER42_CH1: select TIMER42 CH1 as TIMER42 CI1
      \arg        TIMER42_CI1_INPUT_TIMER4_CH1: select TIMER4 CH1 as TIMER42 CI1
      \arg        TIMER42_CI1_INPUT_TIMER22_CH1: select TIMER22 CH1 as TIMER42 CI1
      \arg        TIMER42_CI1_INPUT_TIMER23_CH1: select TIMER23 CH1 as TIMER42 CI1
      \arg        TIMER15_CI0_INPUT_TIMER15_CH0: select TIMER15 CH0 as TIMER15 CI0
      \arg        TIMER15_CI0_INPUT_IRC32K: select IRC32K as TIMER15 CI0
      \arg        TIMER15_CI0_INPUT_LXTAL: select LXTAL as TIMER15 CI0
      \arg        TIMER15_CI0_INPUT_WKUP_IT: select WKUP IT as TIMER15 CI0
      \arg        TIMER16_CI0_INPUT_TIMER16_CH0: select TIMER16 CH0 as TIMER16 CI0
      \arg        TIMER16_CI0_INPUT_HXTAL_RTCDIV: select HXTAL/RTCDIV 1M as TIMER16 CI0
      \arg        TIMER16_CI0_INPUT_CKOUT0: select CKOUT0 as TIMER16 CI0
      \arg        TIMER43_CI0_INPUT_TIMER43_CH0: select TIMER43 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_TIMER22_CH0: select TIMER22 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_TIMER23_CH0: select TIMER23 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_TIMER30_CH0: select TIMER30 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_LXTAL: select LXTAL as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER43 CI0
      \arg        TIMER43_CI1_INPUT_TIMER43_CH1: select TIMER43 CH1 as TIMER43 CI1
      \arg        TIMER43_CI1_INPUT_TIMER22_CH1: select TIMER22 CH1 as TIMER43 CI1
      \arg        TIMER43_CI1_INPUT_TIMER23_CH1: select TIMER23 CH1 as TIMER43 CI1
      \arg        TIMER43_CI1_INPUT_TIMER30_CH1: select TIMER30 CH1 as TIMER43 CI1
      \arg        TIMER44_CI0_INPUT_TIMER44_CH0: select TIMER44 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_TIMER23_CH0: select TIMER23 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_TIMER30_CH0: select TIMER30 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_TIMER31_CH0: select TIMER31 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_LXTAL: select LXTAL as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER44 CI0
      \arg        TIMER44_CI1_INPUT_TIMER44_CH1: select TIMER44 CH1 as TIMER44 CI1
      \arg        TIMER44_CI1_INPUT_TIMER23_CH1: select TIMER23 CH1 as TIMER44 CI1
      \arg        TIMER44_CI1_INPUT_TIMER30_CH1: select TIMER30 CH1 as TIMER44 CI1
      \arg        TIMER44_CI1_INPUT_TIMER31_CH1: select TIMER31 CH1 as TIMER44 CI1
    \param[out] none
    \retval     none
*/
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input)
{
    uint32_t clear_timer_mask = ~((uint32_t)TIMER_IS_MASK << (TIMER_BIT_POS(timer_input)));
    uint32_t config_timer_mask = (TIMER_SEL_VAL(timer_input) << TIMER_BIT_POS(timer_input));

    switch(TIMER_REG_INDEX(timer_input))
    {
    case TIMERCISEL0:
        /* clear TIMER channel input select */
        SYSCFG_TIMERCISEL0 &= clear_timer_mask;
        /* config TIMER channel input */
        SYSCFG_TIMERCISEL0 |= config_timer_mask;
        break;
    case TIMERCISEL1:
        /* clear TIMER channel input select */
        SYSCFG_TIMERCISEL1 &= clear_timer_mask;
        /* config TIMER channel input */
        SYSCFG_TIMERCISEL1 |= config_timer_mask;
        break;
    case TIMERCISEL2:
        /* clear TIMER channel input select */
        SYSCFG_TIMERCISEL2 &= clear_timer_mask;
        /* config TIMER channel input */
        SYSCFG_TIMERCISEL2 |= config_timer_mask;
        break;
    case TIMERCISEL3:
        /* clear TIMER channel input select */
        SYSCFG_TIMERCISEL3 &= clear_timer_mask;
        /* config TIMER channel input */
        SYSCFG_TIMERCISEL3 |= config_timer_mask;
        break;
    case TIMERCISEL4:
        /* clear TIMER channel input select */
        SYSCFG_TIMERCISEL4 &= clear_timer_mask;
        /* config TIMER channel input */
        SYSCFG_TIMERCISEL4 |= config_timer_mask;
        break;
    case TIMERCISEL5:
        /* clear TIMER channel input select */
        SYSCFG_TIMERCISEL5 &= clear_timer_mask;
        /* config TIMER channel input */
        SYSCFG_TIMERCISEL5 |= config_timer_mask;
        break;
    case TIMERCISEL6:
        /* clear TIMER channel input select */
        SYSCFG_TIMERCISEL6 &= clear_timer_mask;
        /* config TIMER channel input */
        SYSCFG_TIMERCISEL6 |= config_timer_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief    configure the I/O compensation cell
    \param[in]  syscfg_cps: specifies the I/O compensation cell mode
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_IO_COMPENSATION_ENABLE: I/O compensation cell is enabled
      \arg        SYSCFG_IO_COMPENSATION_DISABLE: I/O compensation cell is disabled
    \param[out] none
    \retval     none
*/
void syscfg_io_compensation_config(uint32_t syscfg_cps)
{
    uint32_t reg;

    reg = SYSCFG_CPSCTL;
    /* reset the SYSCFG_CPSCTL_CPS_EN bit and set according to syscfg_compensation */
    reg &= ~SYSCFG_CPSCTL_CPS_EN;
    SYSCFG_CPSCTL = (reg | syscfg_cps);
}

/*!
    \brief      enable I/O speed optimization, high-speed at low-voltage
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_io_low_voltage_speed_optimization_enable(void)
{
    SYSCFG_CPSCTL |= SYSCFG_CPSCTL_IOSPDOP;
}

/*!
    \brief      disable I/O speed optimization, high-speed at low-voltage
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_io_low_voltage_speed_optimization_disable(void)
{
    SYSCFG_CPSCTL &= ~SYSCFG_CPSCTL_IOSPDOP;
}

/*!
    \brief      set P/N MOS compensation value
    \param[in]  mos
                only one parameter can be selected which is shown as below:
      \arg        NMOS_COMPENSATION: NMOS
      \arg        PMOS_COMPENSATION: PMOS
    \param[in]  code: P/N MOS compensation value
    \param[out] none
    \retval     none
*/
void syscfg_pnmos_compensation_code_set(uint32_t mos, uint32_t code)
{
    uint32_t value;
    value = SYSCFG_CPSCCCFG;
    if(NMOS_COMPENSATION == mos)
    {
        value &= ~SYSCFG_CPSCCCFG_NCPSCC;
        value |= (code & 0x0FU);
    } else {
        value &= ~SYSCFG_CPSCCCFG_PCPSCC;
        value |= ((code & 0x0FU) << 4U);
    }
    SYSCFG_CPSCCCFG = value;
}

/*!
    \brief      set secure SRAM size
    \param[in]  SRAM size
                only one parameter can be selected which is shown as below:
      \arg        SECURE_SRAM_SIZE_0KB: secure SRAM size is 0KB
      \arg        SECURE_SRAM_SIZE_32KB: secure SRAM size is 32KB
      \arg        SECURE_SRAM_SIZE_64KB: secure SRAM size is 64KB
      \arg        SECURE_SRAM_SIZE_128KB: secure SRAM size is 128KB
    \param[out] none
    \retval     none
*/
void syscfg_secure_sram_size_set(uint32_t size)
{
    SYSCFG_SRAMCFG0 &= (uint32_t)(~SYSCFG_SRAMCFG0_SECURE_SRAM_SIZE);
    SYSCFG_SRAMCFG0 |= size;
}

/*!
    \brief      get secure SRAM size
    \param[in]  none
    \param[out] none
    \retval     SRAM size
      \arg        SECURE_SRAM_SIZE_0KB: secure SRAM size is 0KB
      \arg        SECURE_SRAM_SIZE_32KB: secure SRAM size is 32KB
      \arg        SECURE_SRAM_SIZE_64KB: secure SRAM size is 64KB
      \arg        SECURE_SRAM_SIZE_128KB: secure SRAM size is 128KB
*/
uint32_t syscfg_secure_sram_size_get(void)
{
    return (SYSCFG_SRAMCFG0 & SYSCFG_SRAMCFG0_SECURE_SRAM_SIZE);
}

/*!
    \brief      get BOOT mode
    \param[in]  none
    \param[out] none
    \retval     boot mode
      \arg        BOOT_SRAM: BOOT from SRAM (ITCM/DTCM/RAM shared/AXI SRAM)
      \arg        BOOT_SECURITY: BOOT from Security
      \arg        BOOT_SYSTEM: BOOT_SYS (BootLoader)
      \arg        BOOT_USER_FLASH: BOOT_USER (User flash OSPI0/1)
*/
uint32_t syscfg_bootmode_get(void)
{
    return ((SYSCFG_USERCFG & SYSCFG_USERCFG_BOOT_MODE) >> 4U);
}

/*!
    \brief      enable TCM wait state
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_tcm_wait_state_enable(void)
{
    SYSCFG_SRAMCFG1 |= SYSCFG_SRAMCFG1_TCM_WAITSTATE;
}

/*!
    \brief      disable TCM wait state
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_tcm_wait_state_disable(void)
{
    SYSCFG_SRAMCFG1 &= ~SYSCFG_SRAMCFG1_TCM_WAITSTATE;
}

/*!
    \brief      enable FPU interrupt
    \param[in]  fpu_int: FPU interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INEXACT: inexact interrupt
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: input abnormal interrupt
      \arg        SYSCFG_FPUINT_OVERFLOW: overflow interrupt
      \arg        SYSCFG_FPUINT_UNDERFLOW: underflow interrupt
      \arg        SYSCFG_FPUINT_DIV0: divide-by-zero interrupt
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: invalid operation interrupt
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_enable(uint32_t fpu_int)
{
    SYSCFG_FPUINTEN |= fpu_int;
}

/*!
    \brief      disable FPU interrupt
    \param[in]  fpu_int: FPU interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INEXACT: inexact interrupt
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: input abnormal interrupt
      \arg        SYSCFG_FPUINT_OVERFLOW: overflow interrupt
      \arg        SYSCFG_FPUINT_UNDERFLOW: underflow interrupt
      \arg        SYSCFG_FPUINT_DIV0: divide-by-zero interrupt
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: invalid operation interrupt
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_disable(uint32_t fpu_int)
{
    SYSCFG_FPUINTEN &= (uint32_t)(~fpu_int);
}

/*!
    \brief      get compensation cell flags
    \param[in]  cps_flag: compensation flag
      \arg        SYSCFG_FLAG_IO_LOW_VOLTAGE: I/O in low voltage state flag, product supply voltage is working below 2.5V
      \arg        SYSCFG_FLAG_COMPENSATION_READY: I/O compensation cell ready flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_compensation_flag_get(uint32_t cps_flag)
{
    if(SYSCFG_CPSCTL & cps_flag)
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      get the ICACHE or DCACHE detection and error information
    \param[in]  cache:
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_STATUS: select ICACHE
      \arg        DCACHE_STATUS: select DCACHE
    \param[in]  status:
                only one parameter can be selected which is shown as below:
      \arg        CPU_CACHE_ERROR_DETECTION: select detection information
      \arg        CPU_CACHE_ERROR_BANK: select error information
    \param[out] none
    \retval     value
*/
uint32_t syscfg_cpu_cache_status_get(uint32_t cache, uint32_t status)
{
    uint32_t value = 0U;
    switch(cache)
    {
    /* get ICACHE information */
    case ICACHE_STATUS:
        if(CPU_CACHE_ERROR_DETECTION == status)
        {
            /* return detection information */
            value = (uint32_t)((SYSCFG_CPUICAC & SYSCFG_CPUICAC_CPU_ICDET) >> 28U);
        } else {
            /* return error bank information */
            value = (uint32_t)((SYSCFG_CPUICAC & SYSCFG_CPUICAC_CPU_ICERR) >> 6U);
        }
        break;
    /* get DCACHE information */
    case DCACHE_STATUS:
        if(CPU_CACHE_ERROR_DETECTION == status)
        {
            /* return detection information */
            value = (uint32_t)((SYSCFG_CPUDCAC & SYSCFG_CPUICAC_CPU_ICDET) >> 28U);
        } else {
            /* return error bank information */
            value = (uint32_t)((SYSCFG_CPUDCAC & SYSCFG_CPUICAC_CPU_ICERR) >> 6U);
        }
        break;
    default:
        break;
    }
    return value;
}

/*!
    \brief      get brownout reset threshold level
    \param[in]  none
    \param[out] none
    \retval     BOR level
      \arg        BOR_OFF: no BOR function
      \arg        BOR_THRESHOLD_VAL1: BOR threshold value 1
      \arg        BOR_THRESHOLD_VAL2: BOR threshold value 2
      \arg        BOR_THRESHOLD_VAL3: BOR threshold value 3
*/
uint32_t syscfg_brownout_reset_threshold_level_get(void)
{
    return (SYSCFG_USERCFG & SYSCFG_USERCFG_BOR_TH);
}
