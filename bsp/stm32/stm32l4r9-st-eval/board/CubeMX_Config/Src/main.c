/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gfxmmu_lut.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DMA2D_HandleTypeDef hdma2d;

DSI_HandleTypeDef hdsi;

GFXMMU_HandleTypeDef hgfxmmu;

LTDC_HandleTypeDef hltdc;

UART_HandleTypeDef huart3;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_LTDC_Init(void);
static void MX_FMC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_DSIHOST_DSI_Init(void);
static void MX_GFXMMU_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART3_UART_Init();
    MX_LTDC_Init();
    MX_FMC_Init();
    MX_DMA2D_Init();
    MX_DSIHOST_DSI_Init();
    MX_GFXMMU_Init();
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /**Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
    {
        Error_Handler();
    }
    /**Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 2;
    RCC_OscInitStruct.PLL.PLLN = 30;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /**Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_DSI
                                         |RCC_PERIPHCLK_LTDC;
    PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
    PeriphClkInit.DsiClockSelection = RCC_DSICLKSOURCE_DSIPHY;
    PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLLSAI2_DIV2;
    PeriphClkInit.PLLSAI2.PLLSAI2Source = RCC_PLLSOURCE_HSE;
    PeriphClkInit.PLLSAI2.PLLSAI2M = 2;
    PeriphClkInit.PLLSAI2.PLLSAI2N = 8;
    PeriphClkInit.PLLSAI2.PLLSAI2P = RCC_PLLP_DIV2;
    PeriphClkInit.PLLSAI2.PLLSAI2R = RCC_PLLR_DIV2;
    PeriphClkInit.PLLSAI2.PLLSAI2Q = RCC_PLLQ_DIV2;
    PeriphClkInit.PLLSAI2.PLLSAI2ClockOut = RCC_PLLSAI2_LTDCCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

    /* USER CODE BEGIN DMA2D_Init 0 */

    /* USER CODE END DMA2D_Init 0 */

    /* USER CODE BEGIN DMA2D_Init 1 */

    /* USER CODE END DMA2D_Init 1 */
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_M2M;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
    hdma2d.Init.OutputOffset = 0;
    hdma2d.Init.BytesSwap = DMA2D_BYTES_REGULAR;
    hdma2d.Init.LineOffsetMode = DMA2D_LOM_PIXELS;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0;
    hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
    hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DMA2D_Init 2 */

    /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief DSIHOST Initialization Function
  * @param None
  * @retval None
  */
static void MX_DSIHOST_DSI_Init(void)
{

    /* USER CODE BEGIN DSIHOST_Init 0 */

    /* USER CODE END DSIHOST_Init 0 */

    DSI_PLLInitTypeDef PLLInit = {0};
    DSI_HOST_TimeoutTypeDef HostTimeouts = {0};
    DSI_PHY_TimerTypeDef PhyTimings = {0};
    DSI_LPCmdTypeDef LPCmd = {0};

    /* USER CODE BEGIN DSIHOST_Init 1 */

    /* USER CODE END DSIHOST_Init 1 */
    hdsi.Instance = DSI;
    hdsi.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;
    hdsi.Init.TXEscapeCkdiv = 4;
    hdsi.Init.NumberOfLanes = DSI_ONE_DATA_LANE;
    PLLInit.PLLNDIV = 20;
    PLLInit.PLLIDF = DSI_PLL_IN_DIV1;
    PLLInit.PLLODF = DSI_PLL_OUT_DIV2;
    if (HAL_DSI_Init(&hdsi, &PLLInit) != HAL_OK)
    {
        Error_Handler();
    }
    HostTimeouts.TimeoutCkdiv = 1;
    HostTimeouts.HighSpeedTransmissionTimeout = 0;
    HostTimeouts.LowPowerReceptionTimeout = 0;
    HostTimeouts.HighSpeedReadTimeout = 0;
    HostTimeouts.LowPowerReadTimeout = 0;
    HostTimeouts.HighSpeedWriteTimeout = 0;
    HostTimeouts.HighSpeedWritePrespMode = DSI_HS_PM_DISABLE;
    HostTimeouts.LowPowerWriteTimeout = 0;
    HostTimeouts.BTATimeout = 0;
    if (HAL_DSI_ConfigHostTimeouts(&hdsi, &HostTimeouts) != HAL_OK)
    {
        Error_Handler();
    }
    PhyTimings.ClockLaneHS2LPTime = 17;
    PhyTimings.ClockLaneLP2HSTime = 12;
    PhyTimings.DataLaneHS2LPTime = 8;
    PhyTimings.DataLaneLP2HSTime = 8;
    PhyTimings.DataLaneMaxReadTime = 0;
    PhyTimings.StopWaitTime = 0;

    if (HAL_DSI_ConfigPhyTimer(&hdsi, &PhyTimings) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DSI_ConfigFlowControl(&hdsi, DSI_FLOW_CONTROL_BTA) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DSI_SetLowPowerRXFilter(&hdsi, 10000) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DSI_ConfigErrorMonitor(&hdsi, HAL_DSI_ERROR_NONE) != HAL_OK)
    {
        Error_Handler();
    }
    LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_DISABLE;
    LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_DISABLE;
    LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_DISABLE;
    LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_DISABLE;
    LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_DISABLE;
    LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_DISABLE;
    LPCmd.LPGenLongWrite = DSI_LP_GLW_DISABLE;
    LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_DISABLE;
    LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_DISABLE;
    LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_DISABLE;
    LPCmd.LPDcsLongWrite = DSI_LP_DLW_DISABLE;
    LPCmd.LPMaxReadPacket = DSI_LP_MRDP_DISABLE;
    LPCmd.AcknowledgeRequest = DSI_ACKNOWLEDGE_DISABLE;
    if (HAL_DSI_ConfigCommand(&hdsi, &LPCmd) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DSIHOST_Init 2 */

    /* USER CODE END DSIHOST_Init 2 */

}

/**
  * @brief GFXMMU Initialization Function
  * @param None
  * @retval None
  */
static void MX_GFXMMU_Init(void)
{

    /* USER CODE BEGIN GFXMMU_Init 0 */

    /* USER CODE END GFXMMU_Init 0 */

    /* USER CODE BEGIN GFXMMU_Init 1 */

    /* USER CODE END GFXMMU_Init 1 */
    hgfxmmu.Instance = GFXMMU;
    hgfxmmu.Init.BlocksPerLine = GFXMMU_192BLOCKS;
    hgfxmmu.Init.DefaultValue = 0;
    hgfxmmu.Init.Buffers.Buf0Address = 0;
    hgfxmmu.Init.Buffers.Buf1Address = 0;
    hgfxmmu.Init.Buffers.Buf2Address = 0;
    hgfxmmu.Init.Buffers.Buf3Address = 0;
    hgfxmmu.Init.Interrupts.Activation = ENABLE;
    if (HAL_GFXMMU_Init(&hgfxmmu) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_GFXMMU_ConfigLut(&hgfxmmu, GFXMMU_LUT_FIRST, GFXMMU_LUT_SIZE, (uint32_t)gfxmmu_lut_config) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN GFXMMU_Init 2 */

    /* USER CODE END GFXMMU_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

    /* USER CODE BEGIN LTDC_Init 0 */

    /* USER CODE END LTDC_Init 0 */

    LTDC_LayerCfgTypeDef pLayerCfg = {0};
    LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

    /* USER CODE BEGIN LTDC_Init 1 */

    /* USER CODE END LTDC_Init 1 */
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 7;
    hltdc.Init.VerticalSync = 3;
    hltdc.Init.AccumulatedHBP = 14;
    hltdc.Init.AccumulatedVBP = 5;
    hltdc.Init.AccumulatedActiveW = 654;
    hltdc.Init.AccumulatedActiveH = 485;
    hltdc.Init.TotalWidth = 660;
    hltdc.Init.TotalHeigh = 487;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
        Error_Handler();
    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 0;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 0;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    pLayerCfg.Alpha = 0;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    pLayerCfg.FBStartAdress = GFXMMU_VIRTUAL_BUFFER0_BASE;
    pLayerCfg.ImageWidth = 0;
    pLayerCfg.ImageHeight = 0;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
        Error_Handler();
    }
    pLayerCfg1.WindowX0 = 0;
    pLayerCfg1.WindowX1 = 0;
    pLayerCfg1.WindowY0 = 0;
    pLayerCfg1.WindowY1 = 0;
    pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    pLayerCfg1.Alpha = 0;
    pLayerCfg1.Alpha0 = 0;
    pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    pLayerCfg1.FBStartAdress = GFXMMU_VIRTUAL_BUFFER0_BASE;
    pLayerCfg1.ImageWidth = 0;
    pLayerCfg1.ImageHeight = 0;
    pLayerCfg1.Backcolor.Blue = 0;
    pLayerCfg1.Backcolor.Green = 0;
    pLayerCfg1.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_LTDC_SetPitch(&hltdc, 768, 0) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_LTDC_SetPitch(&hltdc, 768, 1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN LTDC_Init 2 */

    /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

    /* USER CODE BEGIN USART3_Init 0 */

    /* USER CODE END USART3_Init 0 */

    /* USER CODE BEGIN USART3_Init 1 */

    /* USER CODE END USART3_Init 1 */
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART3_Init 2 */

    /* USER CODE END USART3_Init 2 */

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{
    FMC_NORSRAM_TimingTypeDef Timing;

    /** Perform the SRAM1 memory initialization sequence
    */
    hsram1.Instance = FMC_NORSRAM_DEVICE;
    hsram1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
    /* hsram1.Init */
    hsram1.Init.NSBank = FMC_NORSRAM_BANK1;
    hsram1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    hsram1.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
    hsram1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
    hsram1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
    hsram1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
    hsram1.Init.WriteOperation = FMC_WRITE_OPERATION_DISABLE;
    hsram1.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
    hsram1.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
    hsram1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
    hsram1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    hsram1.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
    hsram1.Init.NBLSetupTime = 0;
    hsram1.Init.PageSize = FMC_PAGE_SIZE_NONE;
    /* Timing */
    Timing.AddressSetupTime = 15;
    Timing.AddressHoldTime = 15;
    Timing.DataSetupTime = 255;
    Timing.DataHoldTime = 0;
    Timing.BusTurnAroundDuration = 15;
    Timing.CLKDivision = 16;
    Timing.DataLatency = 17;
    Timing.AccessMode = FMC_ACCESS_MODE_A;
    /* ExtTiming */

    if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
    {
        Error_Handler( );
    }

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    HAL_PWREx_EnableVddIO2();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
