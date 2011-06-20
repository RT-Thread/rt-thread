/******************************************************************//**
 * @file 		board.c
 * @brief 	USART driver of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-12-21	onelife		Initial creation for EFM32
 * 2011-05-06	onelife		Add EFM32 development kit and SPI Flash support
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup efm32
* @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
#define IS_NVIC_VECTTAB(VECTTAB) 		(((VECTTAB) == RAM_MEM_BASE) || \
										((VECTTAB) == FLASH_MEM_BASE))
#define IS_NVIC_OFFSET(OFFSET) 			((OFFSET) < 0x000FFFFF)

/******************************************************************//**
* @addtogroup SysTick_clock_source
* @{
*********************************************************************/
#define SysTick_CLKSource_HCLK_Div8		((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK			((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE)	(((SOURCE) == SysTick_CLKSource_HCLK) || \
										((SOURCE) == SysTick_CLKSource_HCLK_Div8))
/******************************************************************//**
 * @}
*********************************************************************/

/* Private macro --------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *	  Set the allocation and offset of the vector table 
 *
 * @details
 *
 * @note
 *
 * @param[in] NVIC_VectTab
 *	 Indicate the vector table is allocated in RAM or ROM
 *
 * @param[in] Offset
 *	The vector table offset
 *********************************************************************/
static void NVIC_SetVectorTable(rt_uint32_t NVIC_VectTab, rt_uint32_t Offset)
{ 
	/* Check the parameters */
	RT_ASSERT(IS_NVIC_VECTTAB(NVIC_VectTab));
	RT_ASSERT(IS_NVIC_OFFSET(Offset));  

	SCB->VTOR = NVIC_VectTab | (Offset & (rt_uint32_t)0x1FFFFF80);
}

/******************************************************************//**
 * @brief
 *	  Configure the address of vector table 
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
static void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM
	/* Set the vector table allocated at 0x20000000 */
	NVIC_SetVectorTable(RAM_MEM_BASE, 0x0);
#else  /* VECT_TAB_FLASH  */
	/* Set the vector table allocated at 0x00000000 */
	NVIC_SetVectorTable(FLASH_MEM_BASE, 0x0);
#endif

	/* Set NVIC Preemption Priority Bits: 0 bit for pre-emption, 4 bits for subpriority */
	NVIC_SetPriorityGrouping(0x7UL);

	/* Set Base Priority Mask Register */
	__set_BASEPRI(EFM32_BASE_PRI_DEFAULT);
}

/******************************************************************//**
 * @brief
 *	  Enable high frequency crystal oscillator (HFXO), and set HFCLK domain to use HFXO as 
 * source.
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
static void switchToHFXO(void)
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

/******************************************************************//**
 * @brief
 *	  Configure the SysTick clock source
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
 *********************************************************************/
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

/******************************************************************//**
 * @brief
 *	  Configure the SysTick for OS tick.
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
static void  SysTick_Configuration(void)
{
	rt_uint32_t 	core_clock;
	rt_uint32_t 	cnts;

	switchToHFXO();
	core_clock = SystemCoreClockGet();
	cnts = core_clock / RT_TICK_PER_SECOND;

	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
}

/******************************************************************//**
 * @brief
 *	  Initialize the board.
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
void rt_hw_board_init(void)
{
	/* Chip errata */
	CHIP_Init();

#if defined(EFM32_G290_DK)
	/* Initialize DVK board register access */
	DVK_init();
#endif

	/* NVIC Configuration */
	NVIC_Configuration();

	/* Configure external oscillator */
	SystemHFXOClockSet(EFM32_HFXO_FREQUENCY);
	
	/* Configure the SysTick */
	SysTick_Configuration();	
}

/******************************************************************//**
 * @brief
 *	  Initialize the hardware drivers.
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
void rt_hw_driver_init(void)
{
	CMU_ClockEnable(cmuClock_HFPER, true);

	/* Enable GPIO */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Enabling clock to the interface of the low energy modules */
	CMU_ClockEnable(cmuClock_CORELE, true);

	/* Initialize DMA */
	rt_hw_dma_init();

	/* Initialize USART */
#if defined(EFM32_G290_DK)
	DVK_enablePeripheral(DVK_RS232A);
	DVK_enablePeripheral(DVK_SPI);
#endif
#if (defined(RT_USING_USART0) || defined(RT_USING_USART1) || defined(RT_USING_USART2))
	rt_hw_usart_init();
#endif

	/* Setup console */
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
}

/******************************************************************//**
 * @}
*********************************************************************/

