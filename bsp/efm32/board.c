/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-21   onelife     Initial creation for EFM32
 * 2011-05-06   onelife     Add EFM32 development kit and SPI Flash support
 * 2011-07-12   onelife     Add SWO output enable function
 * 2011-12-08   onelife     Add giant gecko development kit support
 * 2011-12-09   onelife     Add giant gecko support
 * 2011-12-09   onelife     Add LEUART module support
 * 2011-12-14   onelife     Add LFXO enabling routine in driver initialization function
 * 2011-12-15   onelife     Add MicroSD initialization routine in driver
 *                          initialization function
 * 2011-12-29   onelife     Add keys and joystick initialization routine in
 *                          driver initialization function
 * 2012-02-15   onelife     Modify SWO setup function to support giant gecko
 * 2012-xx-xx   onelife     Modify system clock and ticket related code
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IS_NVIC_VECTTAB(VECTTAB)        (((VECTTAB) == RAM_MEM_BASE) || \
                                        ((VECTTAB) == FLASH_MEM_BASE))
#define IS_NVIC_OFFSET(OFFSET)          ((OFFSET) < 0x000FFFFF)

/***************************************************************************//**
 * @addtogroup SysTick_clock_source
 * @{
 ******************************************************************************/
#define SysTick_CLKSource_MASK          ((rt_uint32_t)0x00000004)
#define SysTick_CLKSource_RTC           ((rt_uint32_t)0x00000000)
#define SysTick_CLKSource_HFCORECLK     ((rt_uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE)   (((SOURCE) == SysTick_CLKSource_RTC) || \
                                        ((SOURCE) == SysTick_CLKSource_HFCORECLK))
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
 *   Indicate the vector table is allocated in RAM or ROM
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
 *   Configure the SysTick clock source
 *
 * @details
 *
 * @note
 *
 * @param[in] SysTick_CLKSource
 *   Specifies the SysTick clock source.
 *
 * @arg SysTick_CLKSource_HCLK_Div8
 *   AHB clock divided by 8 selected as SysTick clock source.
 *
 * @arg SysTick_CLKSource_HCLK
 *   AHB clock selected as SysTick clock source.
 ******************************************************************************/
static void SysTick_CLKSourceConfig(rt_uint32_t SysTick_CLKSource)
{
    /* Check the parameters */
    RT_ASSERT(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));

    rt_uint32_t ctrl = SysTick->CTRL;

    ctrl &= ~SysTick_CLKSource_MASK;
    ctrl |= SysTick_CLKSource;

    SysTick->CTRL = ctrl;
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
#if defined(EFM32_USING_LFXO)
    /* LETIMER0 configurations */
    const LETIMER_Init_TypeDef letimerInit =
    {
        .enable         = true,                 /* Start counting when init completed. */
        .debugRun       = false,                /* Counter shall not keep running during debug halt. */
        .rtcComp0Enable = false,                /* Don't start counting on RTC COMP0 match. */
        .rtcComp1Enable = false,                /* Don't start counting on RTC COMP1 match. */
        .comp0Top       = true,                 /* Load COMP0 register into CNT when counter underflows. COMP is used as TOP */
        .bufTop         = false,                /* Don't load COMP1 into COMP0 when REP0 reaches 0. */
        .out0Pol        = 0,                    /* Idle value for output 0. */
        .out1Pol        = 0,                    /* Idle value for output 1. */
        .ufoa0          = letimerUFOANone,      /* No output on output 0. */
        .ufoa1          = letimerUFOANone,      /* No output on output 1. */
        .repMode        = letimerRepeatFree     /* Count until stopped by SW. */
    };

    CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_8);
    CMU_ClockEnable(cmuClock_LETIMER0, true);
    LETIMER_CompareSet(LETIMER0, 0,
        EFM32_LETIMER_TOP_100HZ * RT_TICK_PER_SECOND / 100);

    /* Enable underflow interrupt */
    LETIMER_IntClear(LETIMER0, LETIMER_IF_UF);
    LETIMER_IntEnable(LETIMER0, LETIMER_IF_UF);
    /* Enable LETIMER0 interrupt vector in NVIC */
    NVIC_ClearPendingIRQ(LETIMER0_IRQn);
    NVIC_SetPriority(LETIMER0_IRQn, EFM32_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(LETIMER0_IRQn);

    /* Start LETIMER0 */
    LETIMER_Init(LETIMER0, &letimerInit);
#else
    rt_uint32_t     coreClk;
    rt_uint32_t     cnts;

    coreClk = SystemCoreClockGet();
    cnts = coreClk / RT_TICK_PER_SECOND;

    SysTick_Config(cnts);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HFCORECLK);
#endif
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
void Swo_Configuration(void)
{
    rt_uint32_t *dwt_ctrl = (rt_uint32_t *) 0xE0001000;
    rt_uint32_t *tpiu_prescaler = (rt_uint32_t *) 0xE0040010;
    rt_uint32_t *tpiu_protocol = (rt_uint32_t *) 0xE00400F0;

    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
    /* Enable Serial wire output pin */
    GPIO->ROUTE |= GPIO_ROUTE_SWOPEN;
#if defined(_EFM32_GIANT_FAMILY)
    /* Set location 0 */
    GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) | GPIO_ROUTE_SWLOCATION_LOC0;

    /* Enable output on pin - GPIO Port F, Pin 2 */
    GPIO->P[5].MODEL &= ~(_GPIO_P_MODEL_MODE2_MASK);
    GPIO->P[5].MODEL |= GPIO_P_MODEL_MODE2_PUSHPULL;
    #else
    /* Set location 1 */
    GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) | GPIO_ROUTE_SWLOCATION_LOC1;
    /* Enable output on pin */
    GPIO->P[2].MODEH &= ~(_GPIO_P_MODEH_MODE15_MASK);
    GPIO->P[2].MODEH |= GPIO_P_MODEH_MODE15_PUSHPULL;
#endif
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

    /* Disable all DVK interrupts */
    DVK_disableInterrupt(BC_INTEN_MASK);
    DVK_clearInterruptFlags(BC_INTFLAG_MASK);
#endif

    /* config NVIC Configuration */
    NVIC_Configuration();

#if defined(EFM32_USING_HFXO)
    /* Configure external oscillator */
    SystemHFXOClockSet(EFM32_HFXO_FREQUENCY);

    /* Switching the CPU clock source to HFXO */
    CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

    /* Turning off the high frequency RC Oscillator (HFRCO) */
    CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);
#endif

#if defined(EFM32_USING_LFXO)
    CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO);
    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
#endif

#if defined(EFM32_SWO_ENABLE)
    /* Enable SWO */
    Swo_Configuration();
#endif

    /* Enable high frequency peripheral clock */
    CMU_ClockEnable(cmuClock_HFPER, true);
    /* Enabling clock to the interface of the low energy modules */
    CMU_ClockEnable(cmuClock_CORELE, true);
    /* Enable GPIO clock */
    CMU_ClockEnable(cmuClock_GPIO, true);

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
    /* Initialize DMA */
    rt_hw_dma_init();

    /* Select LFXO for specified module (and wait for it to stabilize) */
#if (!defined(EFM32_USING_LFXO) && defined(RT_USING_RTC))
#error "Low frequency clock source is needed for using RTC"
#endif

#if (!defined(EFM32_USING_LFXO )&& \
    (defined(RT_USING_LEUART0) || defined(RT_USING_LEUART1)))
#error "Low frequency clock source is needed for using LEUART"
#endif

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
 #if defined(EFM32GG_DK3750)
    DVK_enablePeripheral(DVK_ETH);
 #endif
#endif

    /* Initialize LCD */
#if defined(EFM32_USING_LCD)
    efm32_spiLcd_init();
#endif

    /* Initialize Keys */
#if defined(EFM32_USING_KEYS)
 #if defined(EFM32GG_DK3750)
    efm32_hw_keys_init();
 #endif
#endif

}

/***************************************************************************//**
 * @}
 ******************************************************************************/
