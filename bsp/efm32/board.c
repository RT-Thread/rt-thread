/***************************************************************************//**
 * @file 	board.c
 * @brief 	Board support of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 0.4 beta
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-12-21	onelife		Initial creation for EFM32
 * 2011-05-06	onelife		Add EFM32 development kit and SPI Flash support
 * 2011-07-12	onelife		Add SWO output enable function
 * 2011-12-08	onelife		Add giant gecko development kit support
 * 2011-12-09	onelife		Add giant gecko support
 * 2011-12-09   onelife     Add LEUART module support
 * 2011-12-14   onelife     Add LFXO enabling routine in driver initialization
 *  function
 * 2011-12-15   onelife     Add MicroSD enabling routine in driver
 *  initialization function
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IS_NVIC_VECTTAB(VECTTAB) 		(((VECTTAB) == RAM_MEM_BASE) || \
										((VECTTAB) == FLASH_MEM_BASE))
#define IS_NVIC_OFFSET(OFFSET) 			((OFFSET) < 0x000FFFFF)

/***************************************************************************//**
 * @addtogroup SysTick_clock_source
 * @{
 ******************************************************************************/
#define SysTick_CLKSource_HCLK_Div8		((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK			((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE)	(((SOURCE) == SysTick_CLKSource_HCLK) || \
										((SOURCE) == SysTick_CLKSource_HCLK_Div8))
/***************************************************************************//**
 * @}
 ******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Set the allocation and offset of the vector table
 *
 * @details
 *
 * @note
 *
 * @param[in] NVIC_VectTab
 *	 Indicate the vector table is allocated in RAM or ROM
 *
 * @param[in] Offset
 *   The vector table offset
 ******************************************************************************/
static void NVIC_SetVectorTable(
	rt_uint32_t NVIC_VectTab,
	rt_uint32_t Offset)
{
	/* Check the parameters */
	RT_ASSERT(IS_NVIC_VECTTAB(NVIC_VectTab));
	RT_ASSERT(IS_NVIC_OFFSET(Offset));

	SCB->VTOR = NVIC_VectTab | (Offset & (rt_uint32_t)0x1FFFFF80);
}

/***************************************************************************//**
 * @brief
 *   Configure the address of vector table
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
static void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM
	/* Set the vector table allocated at 0x20000000 */
	NVIC_SetVectorTable(RAM_MEM_BASE, 0x0);
#else  /* VECT_TAB_FLASH  */
	/* Set the vector table allocated at 0x00000000 */
	NVIC_SetVectorTable(FLASH_MEM_BASE, 0x0);
#endif

	/* Set NVIC Preemption Priority Bits: 0 bit for pre-emption, 4 bits for
	   subpriority */
	NVIC_SetPriorityGrouping(0x7UL);

	/* Set Base Priority Mask Register */
	__set_BASEPRI(EFM32_BASE_PRI_DEFAULT);
}

/***************************************************************************//**
 * @brief
 *   Enable high frequency crystal oscillator (HFXO), and set HFCLK domain to
 * use HFXO as source.
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
static void efm_hfxo_switch(void)
{
  CMU_TypeDef *cmu = CMU;

  /* Turning on HFXO to increase frequency accuracy. */
  /* Waiting until oscillator is stable */
  cmu->OSCENCMD = CMU_OSCENCMD_HFXOEN;
  while (!(cmu->STATUS && CMU_STATUS_HFXORDY)) ;

  /* Switching the CPU clock source to HFXO */
  cmu->CMD = CMU_CMD_HFCLKSEL_HFXO;

  /* Turning off the high frequency RC Oscillator (HFRCO) */
  /* GENERATL WARNING! Make sure not to disable the current
   * source of the HFCLK. */
  cmu->OSCENCMD = CMU_OSCENCMD_HFRCODIS;
}

/***************************************************************************//**
 * @brief
 *   Configure the SysTick clock source
 *
 * @details
 *
 * @note
 *
 * @param[in] SysTick_CLKSource
 *	 Specifies the SysTick clock source.
 *
 * @arg SysTick_CLKSource_HCLK_Div8
 * 	 AHB clock divided by 8 selected as SysTick clock source.
 *
 * @arg SysTick_CLKSource_HCLK
 *	 AHB clock selected as SysTick clock source.
 ******************************************************************************/
static void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
  RT_ASSERT(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));

  if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
  }
}

/***************************************************************************//**
 * @brief
 *   Configure the SysTick for OS tick.
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
static void  SysTick_Configuration(void)
{
	rt_uint32_t 	core_clock;
	rt_uint32_t 	cnts;

	efm_hfxo_switch();
	core_clock = SystemCoreClockGet();
	cnts = core_clock / RT_TICK_PER_SECOND;

	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
}

/***************************************************************************//**
 * @brief
 *   Enable SWO.
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void efm_swo_setup(void)
{
	rt_uint32_t *dwt_ctrl = (rt_uint32_t *) 0xE0001000;
	rt_uint32_t *tpiu_prescaler = (rt_uint32_t *) 0xE0040010;
	rt_uint32_t *tpiu_protocol = (rt_uint32_t *) 0xE00400F0;

	CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
	/* Enable Serial wire output pin */
	GPIO->ROUTE |= GPIO_ROUTE_SWOPEN;
	/* Set location 1 */
	GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) | GPIO_ROUTE_SWLOCATION_LOC1;
	/* Enable output on pin */
	GPIO->P[2].MODEH &= ~(_GPIO_P_MODEH_MODE15_MASK);
	GPIO->P[2].MODEH |= GPIO_P_MODEH_MODE15_PUSHPULL;
	/* Enable debug clock AUXHFRCO */
	CMU->OSCENCMD = CMU_OSCENCMD_AUXHFRCOEN;

	while(!(CMU->STATUS & CMU_STATUS_AUXHFRCORDY));

	/* Enable trace in core debug */
	CoreDebug->DHCSR |= 1;
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

	/* Enable PC and IRQ sampling output */
	*dwt_ctrl = 0x400113FF;
	/* Set TPIU prescaler to 16. */
	*tpiu_prescaler = 0xf;
	/* Set protocol to NRZ */
	*tpiu_protocol = 2;
	/* Unlock ITM and output data */
	ITM->LAR = 0xC5ACCE55;
	ITM->TCR = 0x10009;
}

/***************************************************************************//**
 * @brief
 *   Initialize the board.
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void rt_hw_board_init(void)
{
	/* Chip errata */
	CHIP_Init();

    /* Initialize DVK board register access */
#if defined(EFM32_GXXX_DK)
	DVK_init();
#elif defined(EFM32GG_DK3750)
    DVK_init(DVK_Init_EBI);
#endif

	/* NVIC Configuration */
	NVIC_Configuration();

	/* Configure external oscillator */
	SystemHFXOClockSet(EFM32_HFXO_FREQUENCY);

	/* Configure the SysTick */
	SysTick_Configuration();
}

/***************************************************************************//**
 * @brief
 *   Initialize the hardware drivers.
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void rt_hw_driver_init(void)
{
	CMU_ClockEnable(cmuClock_HFPER, true);

	/* Enable GPIO */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Enabling clock to the interface of the low energy modules */
	CMU_ClockEnable(cmuClock_CORELE, true);

    /* Starting LFXO and waiting until it is stable */
#if defined(EFM32_USING_LFXO)
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

    /* Select LFXO for specified module (and wait for it to stabilize) */
 #if (defined(RT_USING_LEUART0) || defined(RT_USING_LEUART1))
    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
 #endif
 #if defined(RT_USING_RTC)
    CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO);
 #endif
#endif

    /* Enable SWO */
#if defined(EFM32_SWO_ENABLE)
	efm_swo_setup();
#endif

	/* Initialize DMA */
	rt_hw_dma_init();

	/* Initialize USART */
#if (defined(RT_USING_USART0) || defined(RT_USING_USART1) || \
    defined(RT_USING_USART2) || defined(RT_USING_UART0) || \
    defined(RT_USING_UART1))
	rt_hw_usart_init();
#endif

    /* Initialize LEUART */
#if (defined(RT_USING_LEUART0) || defined(RT_USING_LEUART1))
    rt_hw_leuart_init();
#endif

	/* Setup Console */
#if defined(EFM32_GXXX_DK)
    DVK_enablePeripheral(DVK_RS232A);
    DVK_enablePeripheral(DVK_SPI);
#elif defined(EFM32GG_DK3750)
 #if (RT_CONSOLE_DEVICE == EFM_UART1)
    DVK_enablePeripheral(DVK_RS232_UART);
 #elif (RT_CONSOLE_DEVICE == EFM_LEUART1)
    DVK_enablePeripheral(DVK_RS232_LEUART);
 #endif
#endif
	rt_console_set_device(CONSOLE_DEVICE);

	/* Initialize Timer */
#if (defined(RT_USING_TIMER0) || defined(RT_USING_TIMER1) || defined(RT_USING_TIMER2))
	rt_hw_timer_init();
#endif

	/* Initialize ADC */
#if defined(RT_USING_ADC0)
	rt_hw_adc_init();
#endif

	/* Initialize ACMP */
#if (defined(RT_USING_ACMP0) || defined(RT_USING_ACMP1))
	rt_hw_acmp_init();
#endif

	/* Initialize IIC */
#if (defined(RT_USING_IIC0) || defined(RT_USING_IIC1))
	rt_hw_iic_init();
#endif

	/* Initialize RTC */
#if defined(RT_USING_RTC)
	rt_hw_rtc_init();
#endif

    /* Enable SPI access to MicroSD card */
#if defined(EFM32_USING_SPISD)
 #if defined(EFM32_GXXX_DK)
    DVK_writeRegister(BC_SPI_CFG, 1);
 #elif defined(EFM32GG_DK3750)
    DVK_enablePeripheral(DVK_MICROSD);
 #endif
#endif

    /* Enable SPI access to Ethernet */
#if defined(EFM32_USING_ETHERNET)
    DVK_enablePeripheral(DVK_ETH);
#endif
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
