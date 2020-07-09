/**
  *********************************************************************************
  *
  * @file    ald_cmu.c
  * @brief   CMU module driver.
  *
  * @version V1.0
  * @date    22 Nov 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
     *** System clock configure ***
     =================================
     [..]
       (+) If you don't change system clock, you can using ald_cmu_clock_config_default() API.
           It will select HRC as system clock. The system clock is 24MHz.
       (+) If you want to change system clock, you can using ald_cmu_clock_config() API.
           You can select one of the following as system clock:
             @ref CMU_CLOCK_HRC   2MHz or 24MHz
             @ref CMU_CLOCK_LRC   32768Hz
             @ref CMU_CLOCK_LOSC  32768Hz
             @ref CMU_CLOCK_PLL1  36MHz/48MHz/72MHz/96MHz
             @ref CMU_CLOCK_HOSC  1MHz -- 24MHz
       (+) If you select CMU_CLOCK_PLL1 as system clock, it must config the PLL1
           using ald_cmu_pll1_config() API. The input of clock must be 4MHz.
       (+) If you get current clock, you can using ald_cmu_get_clock() API.

     *** BUS division control ***
     ===================================

     MCLK            sys_clk
     -------DIV_SYS-----------+--------------------------System(Core, DMA, Systick ... etc.)
                              |
                              |                  hclk1
                              +------DIV_AHB1------------Peripheral(GPIO, CRC, ... etc.)
                              |
                              |                  hclk2
                              +------DIV_AHB2------------Peripheral(EBI, QSPI, ... etc.)
                              |
                              |                  pclk1
                              +------DIV_APB1------------Peripheral(TIM, UART, ... etc.)
                              |
                              |                  pclk2
                              +------DIV_APB2------------Peripheral(ADC, WWDT, ... etc.)

     [..]
       (+) Configure the division using ald_cmu_div_config() API.
       (+) Get sys_clk using ald_cmu_get_sys_clock() API.
       (+) Get hclk1 using ald_cmu_get_hclk1_clock() API.
       (+) Get pclk1 using ald_cmu_get_pclk1_clock() API.
       (+) Get pclk2 using ald_cmu_get_pclk2_clock() API.

     *** Clock safe configure ***
     ===================================
     [..]
       (+) If you select CMU_CLOCK_HOSC as system clock, you need enable
           clock safe using ald_cmu_hosc_safe_config() API. It will change
           CMU_CLOCK_HRC as system clock, when the outer crystal stoped.
       (+) If you select CMU_CLOCK_LOSC as system clock, you need enable
           clock safe using ald_cmu_losc_safe_config() API. It will change
           CMU_CLOCK_LRC as system clock, when the outer crystal stoped.
       (+) If you select CMU_CLOCK_PLL1 as system clock, you need enable
           clock safe using ald_cmu_pll_safe_config() API. It will change
           CMU_CLOCK_HRC as system clock, when the pll1 is lose.
       (+) The ald_cmu_irq_cbk() will be invoked, when CMU interrupt has
           been occurred. You can overwrite this function in application.

     *** Clock output configure ***
     ===================================
     [..]
       (+) Output high-speed clock using ald_cmu_output_high_clock_config() API.
       (+) Output low-speed clock using ald_cmu_output_low_clock_config() API.

     *** Peripheral clock configure ***
     ===================================
     [..]
       (+) Configure buzz clock using ald_cmu_buzz_config() API.
       (+) Selected lptim0 clock using ald_cmu_lptim0_clock_select() API.
       (+) Selected lpuart clock using ald_cmu_lpuart0_clock_select() API.
       (+) Selected lcd clock using ald_cmu_lcd_clock_select() API.
       (+) Selected qspi clock using ald_cmu_qspi_clock_select() API.
       (+) Configure usb clock using ald_cmu_usb_clock_config() API.
       (+) Enable/Disable peripheral clock using ald_cmu_perh_clock_config() API.
       (+) Selected stop1 clock using ald_cmu_stop1_clock_sel() API.

     *** CMU ALD driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in CMU driver.

      (+) CMU_HRC_SEL_BY_SW():         HRC clock config by software.
      (+) CMU_HRC_SEL_BY_CFGW():       HRC clock config by CFG Word.
      (+) CMU_HRC_DIV_1MHZ_ENABLE():   Enable HRC divider to 1MHz.
      (+) CMU_HRC_DIV_1MHZ_DISABLE():  Disable HRC divider to 1MHz.
      (+) CMU_HOSC_DIV_1MHZ_ENABLE():  Enable HOSC divider to 1MHz.
      (+) CMU_HOSC_DIV_1MHZ_DISABLE(): Disable HOSC divider to 1MHz.
      (+) CMU_LOSC_ENABLE():           Enable outer low crystal(32768Hz).
      (+) CMU_LOSC_DISABLE():          Disable outer low crystal(32768Hz).
      (+) CMU_LRC_ENABLE():            Enable LRC(32768Hz).
      (+) CMU_LRC_DISABLE():           Disable LRC(32768Hz).
      (+) CMU_ULRC_ENABLE():           Enable ULRC(10KHz).
      (+) CMU_ULRC_DISABLE():          Disable ULRC(10KHz).
      (+) CMU_LP_LRC_ENABLE():         Enable low power LRC(32768Hz).
      (+) CMU_LP_LRC_DISABLE():        Disable low power LRC(32768Hz).
      (+) CMU_LP_LOSC_ENABLE():        Enable low power LOSC(32768Hz).
      (+) CMU_LP_LOSC_DISABLE():       Disable low power LOSC(32768Hz).
      (+) CMU_LP_HRC_ENABLE():         Enable low power HRC(2MHz or 24MHz).
      (+) CMU_LP_HRC_DISABLE():        Disable low power HRC(2MHz OR 24MHz).
      (+) CMU_LP_HOSC_ENABLE():        Enable low power HOSC(1MHz -- 24MHz).
      (+) CMU_LP_HOSC_DISABLE():       Disable low power HOSC(1MHz -- 24MHz).

     [..]
      (@) You can refer to the CMU driver header file for used the macros

  @endverbatim
  ******************************************************************************
  */

#include "ald_cmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup CMU CMU
  * @brief CMU module driver
  * @{
  */

/**
  * @defgroup CMU_Private_Variables CMU Private Variables
  * @{
  */
uint32_t __system_clock  = 24000000;
/**
  * @}
  */

/** @defgroup CMU_Private_Functions CMU Private Functions
  * @{
  */

/**
  * @brief  Update the current system clock. This function
  *         will be invoked, when system clock has changed.
  * @param  clock: The new clock.
  * @retval None
  */

static void cmu_clock_update(uint32_t clock)
{
	__system_clock = clock;

	if (clock > 1000000)
		ald_tick_init(TICK_INT_PRIORITY);

	return;
}

/**
  * @brief  CMU module interrupt handler
  * @retval None
  */
void ald_cmu_irq_handler(void)
{
	/* HOSC stop */
	if (READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK) && READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK)) {
		SYSCFG_UNLOCK();
		SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK);
		SYSCFG_LOCK();

		if ((READ_BIT(CMU->HOSMCR, CMU_HOSMCR_CLKS_MSK))
				&& ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 1)
				|| ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 5))))
			cmu_clock_update(READ_BIT(CMU->CFGR, CMU_CFGR_HRCFST_MSK) ? 2000000 : 24000000);
		ald_cmu_irq_cbk(CMU_HOSC_STOP);
	}

	/* HOSC start */
	if (READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK) && READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK)) {
		SYSCFG_UNLOCK();
		SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK);
		SYSCFG_LOCK();

		if (!(READ_BIT(CMU->HOSMCR, CMU_HOSMCR_CLKS_MSK))
				&& ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 5)))
			cmu_clock_update((READ_BITS(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, CMU_HOSCCFG_FREQ_POSS) + 1) * 1000000);
		ald_cmu_irq_cbk(CMU_HOSC_START);
	}

	/* LOSC stop */
	if (READ_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIF_MSK) && READ_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK)) {
		SYSCFG_UNLOCK();
		SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIF_MSK);
		SYSCFG_LOCK();
		ald_cmu_irq_cbk(CMU_LOSC_STOP);
	}

	/* LOSC start */
	if (READ_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIF_MSK) && READ_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIE_MSK)) {
		SYSCFG_UNLOCK();
		SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIF_MSK);
		SYSCFG_LOCK();
		ald_cmu_irq_cbk(CMU_LOSC_START);
	}

	/* PLL1 lose */
	if (READ_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK) && READ_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK)) {
		SYSCFG_UNLOCK();
		SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK);
		SYSCFG_LOCK();

		if (READ_BIT(CMU->PULMCR, CMU_PULMCR_CLKS_MSK)
				&& ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 1)
				|| ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 5))))
			cmu_clock_update(READ_BIT(CMU->CFGR, CMU_CFGR_HRCFST_MSK) ? 2000000 : 24000000);
		ald_cmu_irq_cbk(CMU_PLL1_UNLOCK);
	}

	return;
}
/**
  * @}
  */

/** @defgroup CMU_Public_Functions CMU Public Functions
  * @{
  */

/** @defgroup CMU_Public_Functions_Group1 System clock configuration
  * @brief    System clock configuration functions
  *
  * @verbatim
  ==============================================================================
              ##### System clock Configuration functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure system clock using default parameters.
      (+) Configure system clock using specified parameters.
      (+) Configure PLL1 using specified parameters.
      (+) Get system clock.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure system clock using default.
  *         Select CMU_CLOCK_HRC(24MHz) as system clock and
  *         enable CMU_CLOCK_LRC(32768Hz).
  * @retval The status of ALD.
  */
ald_status_t ald_cmu_clock_config_default(void)
{
	uint32_t cnt = 4000, tmp;

	SYSCFG_UNLOCK();

	/* Select HRC */
	MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);

	while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

	if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != CMU_CLOCK_HRC) {
		SYSCFG_LOCK();
		return ERROR;
	}

	WRITE_REG(CMU->CFGR, 0x0);
	CLEAR_BIT(CMU->CFGR, CMU_CFGR_HRCFST_MSK);	/* Select 24Mhz */

	tmp = READ_REG(CMU->CLKENR);
	/* Enable HRC/LRC/LOSC */
	SET_BIT(tmp, CMU_CLKENR_HRCEN_MSK | CMU_CLKENR_LRCEN_MSK | CMU_CLKENR_LOSCEN_MSK);
	WRITE_REG(CMU->CLKENR, tmp);
	/* Reset LRC */
	for (cnt = 0; cnt < 10000; ++cnt);
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
	SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);

	SYSCFG_LOCK();
	return OK;
}

/**
  * @brief  Configure system clock using specified parameters
  * @param  clk: The parameter can be one of the following:
  *           @arg @ref CMU_CLOCK_HRC  2MHz or 24MHz
  *           @arg @ref CMU_CLOCK_LRC  32768Hz
  *           @arg @ref CMU_CLOCK_LOSC 32768Hz
  *           @arg @ref CMU_CLOCK_PLL1 One of @ref cmu_pll1_output_t
  *           @arg @ref CMU_CLOCK_HOSC 1MHz -- 24MHz
  * @param  clock: The clock which will be set. the value depends
  *         on the parameter of clk.
  * @retval The status of ALD.
  */
ald_status_t ald_cmu_clock_config(cmu_clock_t clk, uint32_t clock)
{
	uint32_t cnt = 4000;

	assert_param(IS_CMU_CLOCK(clk));
	SYSCFG_UNLOCK();

	switch (clk) {
	case CMU_CLOCK_HRC:
		assert_param(clock == 24000000 || clock == 2000000);

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != CMU_CLOCK_HRC) {
			SYSCFG_LOCK();
			return ERROR;
		}

		if (clock == 24000000)
			CLEAR_BIT(CMU->CFGR, CMU_CFGR_HRCFSW_MSK);
		else
			SET_BIT(CMU->CFGR, CMU_CFGR_HRCFSW_MSK);

		SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);

		for (cnt = 4000; cnt; --cnt);
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCRDY_MSK))) && (--cnt));

		cmu_clock_update(clock);
		break;

	case CMU_CLOCK_LRC:
		/* Close SysTick interrupt in lower clock */
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, CMU_CLOCK_LRC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != CMU_CLOCK_LRC) {
			SYSCFG_LOCK();
			return ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);

		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LRCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LRCRDY_MSK))) && (--cnt));

		cmu_clock_update(32768);
		break;

	case CMU_CLOCK_LOSC:
		/* Close SysTick interrupt in lower clock */
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, CMU_CLOCK_LOSC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != CMU_CLOCK_LOSC) {
			SYSCFG_LOCK();
			return ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);

		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LOSCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LOSCRDY_MSK))) && (--cnt));

		cmu_clock_update(32768);
		break;

	case CMU_CLOCK_PLL1:
		MODIFY_REG(CMU->CSR, CMU_CSR_CFT_CMD_MSK, 0xAA << CMU_CSR_CFT_CMD_POSS);
		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, CMU_CLOCK_PLL1 << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != CMU_CLOCK_PLL1) {
			SYSCFG_LOCK();
			return ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);

		for (cnt = 0; cnt < 5000; ++cnt);
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1ACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK))) && (--cnt));

		if (clock == 96000000) {
			ald_cmu_div_config(CMU_HCLK_1, CMU_DIV_2);
			ald_cmu_div_config(CMU_HCLK_2, CMU_DIV_2);
			ald_cmu_div_config(CMU_PCLK_1, CMU_DIV_2);
			ald_cmu_div_config(CMU_PCLK_2, CMU_DIV_4);
			for (cnt = 0; cnt < 20000; ++cnt);
		}
		if (clock == 72000000) {
			ald_cmu_div_config(CMU_PCLK_2, CMU_DIV_4);
		}
		if (clock == 48000000) {
			ald_cmu_div_config(CMU_PCLK_2, CMU_DIV_2);
		}

		cmu_clock_update(clock);
		break;

	case CMU_CLOCK_HOSC:
		assert_param(clock <= 24000000);

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, CMU_CLOCK_HOSC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != CMU_CLOCK_HOSC) {
			SYSCFG_LOCK();
			return ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
		MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, clock / 1000000 - 1);

		for (cnt = 8000; cnt; --cnt);
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK))) && (--cnt));

		cmu_clock_update(clock);
		break;

	default:
		break;
	}

	SYSCFG_LOCK();
	return OK;
}



/**
  * @brief  Configure PLL1 using specified parameters.
  * @param  input: The input clock type.
  * @param  output: The output clock which can be 36MHz/48MHz/72MHz/96MHz.
  *           When input = CMU_PLL1_INPUT_PLL2; then output must be
  *           CMU_PLL1_OUTPUT_36M, and then the real clock is (32768x1024)Hz.
  * @retval None
  */
void ald_cmu_pll1_config(cmu_pll1_input_t input, cmu_pll1_output_t output)
{
	uint32_t cnt = 4000;

	assert_param(IS_CMU_PLL1_INPUT(input));
	assert_param(IS_CMU_PLL1_OUTPUT(output));

	SYSCFG_UNLOCK();

	if (input == CMU_PLL1_INPUT_HRC_6) {
		SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
	}
	else if (input == CMU_PLL1_INPUT_PLL2) {
		SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
		CLEAR_BIT(CMU->PLLCFG, CMU_PLLCFG_PLL2RFS_MSK);
		SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL2EN_MSK);
	}
	else {
		SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
		for (cnt = 0; cnt < 10000; ++cnt);
		cnt = 20000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK))) && (--cnt));
	}

	MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1RFS_MSK, input << CMU_PLLCFG_PLL1RFS_POSS);
	MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1OS_MSK, output << CMU_PLLCFG_PLL1OS_POSS);
	SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);

	for (cnt = 0; cnt < 4000; ++cnt);
	while ((READ_BIT(CMU->PLLCFG, CMU_PLLCFG_PLL1LCKN_MSK)) && (--cnt));
	cnt = 4000;
	while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK))) && (--cnt));

	SET_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
	MODIFY_REG(CMU->PULMCR, CMU_PULMCR_MODE_MSK, 0x3 << CMU_PULMCR_MODE_POSS);

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Gets current system clock.
  * @retval The value of system clock.
  */
uint32_t ald_cmu_get_clock(void)
{
	return __system_clock;
}

/**
  * @}
  */

/** @defgroup CMU_Public_Functions_Group2 BUS division control
  * @brief    BUS division control functions
  *
  * @verbatim
  ==============================================================================
              ##### BUS division control functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the bus division.
      (+) Get ahb1 clock.
      (+) Get sys bus clock.
      (+) Get apb1 clock.
      (+) Get apb2 clock.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure the bus division.
  * @param  bus: The type of bus:
  *          @arg CMU_HCLK_1
  *          @arg CMU_SYS
  *          @arg CMU_PCLK_1
  *          @arg CMU_PCLK_2
  * @param  div: The value of divider.
  * @retval None
  */
void ald_cmu_div_config(cmu_bus_t bus, cmu_div_t div)
{
	assert_param(IS_CMU_BUS(bus));
	assert_param(IS_CMU_DIV(div));

	SYSCFG_UNLOCK();

	switch (bus) {
	case CMU_HCLK_1:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, div << CMU_CFGR_HCLK1DIV_POSS);
		break;

	case CMU_HCLK_2:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_HCLK2DIV_MSK, div << CMU_CFGR_HCLK2DIV_POSS);
		break;

	case CMU_SYS:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, div << CMU_CFGR_SYSDIV_POSS);

		if ((__system_clock >> div) <= 1000000) {
			/* Close SysTick interrupt in lower clock */
			SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
		}
		else {
			ald_tick_init(TICK_INT_PRIORITY);
		}

		break;

	case CMU_PCLK_1:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, div << CMU_CFGR_PCLK1DIV_POSS);
		break;

	case CMU_PCLK_2:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, div << CMU_CFGR_PCLK2DIV_POSS);
		break;

	default:
		break;
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Get AHB1 clock.
  * @retval The value of AHB1 clock.
  */
uint32_t ald_cmu_get_hclk1_clock(void)
{
	uint32_t sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
	uint32_t ahb_div = READ_BITS(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, CMU_CFGR_HCLK1DIV_POSS);

	return (__system_clock >> sys_div) >> ahb_div;
}

/**
  * @brief  Get SYS clock
  * @retval The value of SYS clock
  */
uint32_t ald_cmu_get_sys_clock(void)
{
	uint32_t sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);

	return __system_clock >> sys_div;
}

/**
  * @brief  Get APB1 clock.
  * @retval The value of APB1 clock.
  */
uint32_t ald_cmu_get_pclk1_clock(void)
{
	uint32_t sys_div  = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
	uint32_t apb1_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, CMU_CFGR_PCLK1DIV_POSS);

	return (__system_clock >> sys_div) >> apb1_div;
}

/**
  * @brief  Get APB2 clock.
  * @retval The value of APB2 clock.
  */
uint32_t ald_cmu_get_pclk2_clock(void)
{
	uint32_t sys_div  = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
	uint32_t apb2_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, CMU_CFGR_PCLK2DIV_POSS);

	return (__system_clock >> sys_div) >> apb2_div;
}
/**
  * @}
  */

/** @defgroup CMU_Public_Functions_Group3 Clock safe configure
  * @brief    Clock safe configure functions
  *
  * @verbatim
  ==============================================================================
              ##### Clock safe configure functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Enable/Disable outer high crystal safe mode.
      (+) Enable/Disable outer low crystal safe mode.
      (+) Enable/Disable PLL1 safe mode.
      (+) Interrupt callback function.

    @endverbatim
  * @{
  */

/**
  * @brief  Enable/Disable outer high crystal safe mode.
  * @param  clock: the value of outer crystal frequency.
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_hosc_safe_config(cmu_hosc_range_t clock, type_func_t status)
{
	assert_param(IS_CMU_HOSC_RANGE(clock));
	assert_param(IS_FUNC_STATE(status));

	SYSCFG_UNLOCK();

	if (status) {
		SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK);
		MODIFY_REG(CMU->HOSMCR, CMU_HOSMCR_FRQS_MSK, clock << CMU_HOSMCR_FRQS_POSS);
		SET_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
		SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);

		ald_mcu_irq_config(CMU_IRQn, 3, 3, ENABLE);
	}
	else {
		CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
		CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);

		if (READ_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK) == 0 && READ_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK) == 0)
			ald_mcu_irq_config(CMU_IRQn, 3, 3, DISABLE);
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Enable/Disable outer low crystal safe mode.
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_losc_safe_config(type_func_t status)
{
	assert_param(IS_FUNC_STATE(status));
	SYSCFG_UNLOCK();

	if (status) {
		SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIF_MSK);
		SET_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK);
		SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK);

		ald_mcu_irq_config(CMU_IRQn, 3, 3, ENABLE);
	}
	else {
		CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK);
		CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK);

		if (READ_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK) == 0 && READ_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK) == 0)
			ald_mcu_irq_config(CMU_IRQn, 3, 3, DISABLE);
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Enable/Disable PLL1 safe mode.
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_pll_safe_config(type_func_t status)
{
	assert_param(IS_FUNC_STATE(status));
	SYSCFG_UNLOCK();

	if (status) {
		SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK);
		MODIFY_REG(CMU->PULMCR, CMU_PULMCR_MODE_MSK, 2 << CMU_PULMCR_MODE_POSS);
		SET_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
		SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);

		ald_mcu_irq_config(CMU_IRQn, 3, 3, ENABLE);
	}
	else {
		CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
		CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);

		if (READ_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK) == 0 && READ_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK) == 0)
			ald_mcu_irq_config(CMU_IRQn, 3, 3, DISABLE);
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Get clock state.
  * @param  sr: The state type, see @ref cmu_clock_state_t.
  * @retval SET/RESET
  */
flag_status_t ald_cmu_get_clock_state(cmu_clock_state_t sr)
{
	assert_param(IS_CMU_CLOCK_STATE(sr));

	if (READ_BIT(CMU->CLKSR, sr))
		return SET;

	return RESET;
}

/**
  * @brief  Interrupt callback function.
  * @note   This function is declared as __weak to be overwritten in case of other
  *         implementations in user file.
  * @retval None
  */
__weak void ald_cmu_irq_cbk(cmu_security_t se)
{
	return;
}
/**
  * @}
  */

/** @defgroup CMU_Public_Functions_Group4 Clock output configure
  * @brief    Clock output configure functions
  *
  * @verbatim
  ==============================================================================
              ##### Clock output configure functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the high-speed clock output.
      (+) Configure the low-speed clock output.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure the high-speed clock output.
  * @param  sel: Select the source:
  *           @arg CMU_OUTPUT_HIGH_SEL_HOSC
  *           @arg CMU_OUTPUT_HIGH_SEL_LOSC
  *           @arg CMU_OUTPUT_HIGH_SEL_HRC
  *           @arg CMU_OUTPUT_HIGH_SEL_LRC
  *           @arg CMU_OUTPUT_HIGH_SEL_HOSM
  *           @arg CMU_OUTPUT_HIGH_SEL_PLL1
  *           @arg CMU_OUTPUT_HIGH_SEL_PLL2
  *           @arg CMU_OUTPUT_HIGH_SEL_SYSCLK
  * @param  div: The value of divider:
  *           @arg CMU_OUTPUT_DIV_1
  *           @arg CMU_OUTPUT_DIV_2
  *           @arg CMU_OUTPUT_DIV_4
  *           @arg CMU_OUTPUT_DIV_8
  *           @arg CMU_OUTPUT_DIV_16
  *           @arg CMU_OUTPUT_DIV_32
  *           @arg CMU_OUTPUT_DIV_64
  *           @arg CMU_OUTPUT_DIV_128
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_output_high_clock_config(cmu_output_high_sel_t sel,
		cmu_output_high_div_t div, type_func_t status)
{
	assert_param(IS_CMU_OUTPUT_HIGH_SEL(sel));
	assert_param(IS_CMU_OUTPUT_HIGH_DIV(div));
	assert_param(IS_FUNC_STATE(status));

	SYSCFG_UNLOCK();

	if (status) {
		MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCOS_MSK, sel << CMU_CLKOCR_HSCOS_POSS);
		MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCODIV_MSK, div << CMU_CLKOCR_HSCODIV_POSS);
		SET_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
	}
	else {
		CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Configure the low-speed clock output.
  * @param  sel: Select the source:
  *           @arg CMU_OUTPUT_LOW_SEL_LOSC
  *           @arg CMU_OUTPUT_LOW_SEL_LRC
  *           @arg CMU_OUTPUT_LOW_SEL_LOSM
  *           @arg CMU_OUTPUT_LOW_SEL_BUZZ
  *           @arg CMU_OUTPUT_LOW_SEL_ULRC
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_output_low_clock_config(cmu_output_low_sel_t sel, type_func_t status)
{
	assert_param(IS_CMU_OUTPUT_LOW_SEL(sel));
	assert_param(IS_FUNC_STATE(status));

	SYSCFG_UNLOCK();

	if (status) {
		MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_LSCOS_MSK, sel << CMU_CLKOCR_LSCOS_POSS);
		SET_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
	}
	else {
		CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
	}

	SYSCFG_LOCK();
	return;
}
/**
  * @}
  */

/** @defgroup CMU_Public_Functions_Group5 Peripheral Clock configure
  * @brief    Peripheral clock configure functions
  *
  * @verbatim
  ==============================================================================
              ##### Peripheral clock configure functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure buzz clock.
      (+) Select lptim0 clock source.
      (+) Select lpuart0 clock source.
      (+) Select lcd clock source.
      (+) Enable/Disable peripheral clock.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure buzz clock.
  *         freq = sysclk / (2^(div + 1) * (dat + 1))
  * @param  div: The value of divider.
  * @param  dat: The value of coefficient.
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_buzz_config(cmu_buzz_div_t div, uint16_t dat, type_func_t status)
{
	assert_param(IS_CMU_BUZZ_DIV(div));
	assert_param(IS_FUNC_STATE(status));

	SYSCFG_UNLOCK();

	if (status) {
		MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_DIV_MSK, div << CMU_BUZZCR_DIV_POSS);
		MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_DAT_MSK, dat << CMU_BUZZCR_DAT_POSS);
		SET_BIT(CMU->BUZZCR, CMU_BUZZCR_EN_MSK);
	}
	else {
		CLEAR_BIT(CMU->BUZZCR, CMU_BUZZCR_EN_MSK);
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Select lptim0 clock source.
  * @param  clock: The clock source:
  *           @arg CMU_LP_PERH_CLOCK_SEL_PCLK2
  *           @arg CMU_LP_PERH_CLOCK_SEL_PLL1
  *           @arg CMU_LP_PERH_CLOCK_SEL_PLL2
  *           @arg CMU_LP_PERH_CLOCK_SEL_HRC
  *           @arg CMU_LP_PERH_CLOCK_SEL_HOSC
  *           @arg CMU_LP_PERH_CLOCK_SEL_LRC
  *           @arg CMU_LP_PERH_CLOCK_SEL_LOSC
  *           @arg CMU_LP_PERH_CLOCK_SEL_ULRC
  *           @arg CMU_LP_PERH_CLOCK_SEL_HRC_1M
  *           @arg CMU_LP_PERH_CLOCK_SEL_HOSC_1M
  *           @arg CMU_LP_PERH_CLOCK_SEL_LOSM
  *           @arg CMU_LP_PERH_CLOCK_SEL_HOSM
  * @retval None
  */
void ald_cmu_lptim0_clock_select(cmu_lp_perh_clock_sel_t clock)
{
	assert_param(IS_CMU_LP_PERH_CLOCK_SEL(clock));

	SYSCFG_UNLOCK();
	MODIFY_REG(CMU->PERICR, CMU_PERICR_LPTIM0_MSK, clock << CMU_PERICR_LPTIM0_POSS);
	SYSCFG_LOCK();

	return;
}

/**
  * @brief  Select lpuart0 clock source.
  * @param  clock: The clock source:
  *           @arg CMU_LP_PERH_CLOCK_SEL_PCLK2
  *           @arg CMU_LP_PERH_CLOCK_SEL_PLL1
  *           @arg CMU_LP_PERH_CLOCK_SEL_PLL2
  *           @arg CMU_LP_PERH_CLOCK_SEL_HRC
  *           @arg CMU_LP_PERH_CLOCK_SEL_HOSC
  *           @arg CMU_LP_PERH_CLOCK_SEL_LRC
  *           @arg CMU_LP_PERH_CLOCK_SEL_LOSC
  *           @arg CMU_LP_PERH_CLOCK_SEL_ULRC
  *           @arg CMU_LP_PERH_CLOCK_SEL_HRC_1M
  *           @arg CMU_LP_PERH_CLOCK_SEL_HOSC_1M
  *           @arg CMU_LP_PERH_CLOCK_SEL_LOSM
  *           @arg CMU_LP_PERH_CLOCK_SEL_HOSM
  * @retval None
  */
void ald_cmu_lpuart0_clock_select(cmu_lp_perh_clock_sel_t clock)
{
	assert_param(IS_CMU_LP_PERH_CLOCK_SEL(clock));

	SYSCFG_UNLOCK();
	MODIFY_REG(CMU->PERICR, CMU_PERICR_LPUART0_MSK, clock << CMU_PERICR_LPUART0_POSS);
	SYSCFG_LOCK();

	return;
}

/**
  * @brief  Select lcd clock source.
  * @param  clock: The clock source:
  *           @arg CMU_LCD_SEL_LOSM
  *           @arg CMU_LCD_SEL_LOSC
  *           @arg CMU_LCD_SEL_LRC
  *           @arg CMU_LCD_SEL_ULRC
  *           @arg CMU_LCD_SEL_HRC_1M
  *           @arg CMU_LCD_SEL_HOSC_1M
  * @retval None
  */
void ald_cmu_lcd_clock_select(cmu_lcd_clock_sel_t clock)
{
	assert_param(IS_CMU_LCD_CLOCK_SEL(clock));

	SYSCFG_UNLOCK();
	MODIFY_REG(CMU->PERICR, CMU_PERICR_LCD_MSK, clock << CMU_PERICR_LCD_POSS);
	SYSCFG_LOCK();

	return;
}

/**
  * @brief  Select QSPI clock source.
  * @param  clock: The clock source, see @ref cmu_qspi_clock_sel_t.
  * @retval None
  */
void ald_cmu_qspi_clock_select(cmu_qspi_clock_sel_t clock)
{
	assert_param(IS_CMU_QSPI_CLOCK_SEL(clock));

	SYSCFG_UNLOCK();
	MODIFY_REG(CMU->PERICR, CMU_PERICR_QSPICS_MSK, clock << CMU_PERICR_QSPICS_POSS);
	SYSCFG_LOCK();

	return;
}

/**
  * @brief  Configure USB clock source.
  * @param  clock: The clock source, see @ref cmu_usb_clock_sel_t.
  * @param  div: The clock division, see @ref cmu_usb_div_t.
  * @retval None
  */
void ald_cmu_usb_clock_config(cmu_usb_clock_sel_t clock, cmu_usb_div_t div)
{
	assert_param(IS_CMU_USB_CLOCK_SEL(clock));
	assert_param(IS_CMU_USB_DIV(div));

	SYSCFG_UNLOCK();
	MODIFY_REG(CMU->PERICR, CMU_PERICR_USBPHYCS_MSK, clock << CMU_PERICR_USBPHYCS_POSS);
	MODIFY_REG(CMU->PERIDIVR, CMU_PERIDIVR_USBPHYDIV_MSK, div << CMU_PERIDIVR_USBPHYDIV_POSS);
	SYSCFG_LOCK();

	return;
}

/**
  * @brief  Enable/Disable peripheral clock.
  * @param  perh: The type of peripheral, you can see @ref cmu_perh_t
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_perh_clock_config(cmu_perh_t perh, type_func_t status)
{
	uint32_t idx, pos;

	assert_param(IS_CMU_PERH(perh));
	assert_param(IS_FUNC_STATE(status));

	SYSCFG_UNLOCK();

	if (perh == CMU_PERH_ALL) {
		if (status) {
			WRITE_REG(CMU->AHB1ENR, ~0);
			WRITE_REG(CMU->APB1ENR, ~0);
			WRITE_REG(CMU->APB2ENR, ~0);
		}
		else {
			WRITE_REG(CMU->AHB1ENR, 0);
			WRITE_REG(CMU->APB1ENR, 0);
			WRITE_REG(CMU->APB2ENR, 0);
		}

		SYSCFG_LOCK();
		return;
	}

	idx = (perh >> 27) & 0x3;
	pos = perh & ~(0x3 << 27);

	if (status) {
		switch (idx) {
		case 0:
			SET_BIT(CMU->AHB1ENR, pos);
			break;

		case 1:
			SET_BIT(CMU->APB1ENR, pos);
			break;

		case 2:
			SET_BIT(CMU->APB2ENR, pos);
			break;

		default:
			break;
		}
	}
	else {
		switch (idx) {
		case 0:
			CLEAR_BIT(CMU->AHB1ENR, pos);
			break;

		case 1:
			CLEAR_BIT(CMU->APB1ENR, pos);
			break;

		case 2:
			CLEAR_BIT(CMU->APB2ENR, pos);
			break;

		default:
			break;
		}
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Select stop1 clock.
  * @param  clock: See @ref cmu_stop1_clock_t
  * @retval None
  */
void ald_cmu_stop1_clock_sel(cmu_stop1_clock_t clock)
{
	assert_param(IS_CMU_STOP1_CLOCK(clock));

	SYSCFG_UNLOCK();
	MODIFY_REG(CMU->LPENR, CMU_LPENR_STOP1CS_MSK, clock << CMU_LPENR_STOP1CS_POSS);
	SYSCFG_LOCK();
	return;
}
/**
 * @}
 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
