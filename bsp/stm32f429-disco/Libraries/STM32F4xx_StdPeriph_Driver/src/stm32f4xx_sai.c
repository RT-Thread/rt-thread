/**
  ******************************************************************************
  * @file    stm32f4xx_sai.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    08-November-2013  
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Serial Audio Interface (SAI):
  *           + Initialization and Configuration
  *           + Data transfers functions
  *           + DMA transfers management
  *           + Interrupts and flags management 
  *           
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..] 
    
       (#) Enable peripheral clock using the following functions 
           RCC_APB2PeriphClockCmd(RCC_APB2Periph_SAI1, ENABLE) for SAI1
  
       (#) For each SAI Block A/B enable SCK, SD, FS and MCLK GPIO clocks 
           using RCC_AHB1PeriphClockCmd() function.
  
       (#) Peripherals alternate function: 
           (++) Connect the pin to the desired peripherals' Alternate 
                Function (AF) using GPIO_PinAFConfig() function.
           (++) Configure the desired pin in alternate function by:
                GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
           (++) Select the type, pull-up/pull-down and output speed via 
                GPIO_PuPd, GPIO_OType and GPIO_Speed members
           (++) Call GPIO_Init() function
           -@@- If an external clock source is used then the I2S CKIN pin should be 
               also configured in Alternate function Push-pull pull-up mode.
                
      (#) The SAI clock can be generated from different clock source :
          PLL I2S, PLL SAI or external clock source.
          (++) The PLL I2S is configured using the following functions RCC_PLLI2SConfig(), 
               RCC_PLLI2SCmd(ENABLE), RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY) and 
               RCC_SAIPLLI2SClkDivConfig() or;
              
          (++) The PLL SAI is configured using the following functions RCC_PLLSAIConfig(), 
               RCC_PLLSAICmd(ENABLE), RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) and 
               RCC_SAIPLLSAIClkDivConfig()or;          
              
          (++) External clock source is configured using the function 
               RCC_I2SCLKConfig(RCC_I2S2CLKSource_Ext) and after setting correctly the 
               define constant I2S_EXTERNAL_CLOCK_VAL in the stm32f4xx_conf.h file.      
                
      (#) Each SAI Block A or B has its own clock generator to make these two blocks 
          completely independent. The Clock generator is configured using RCC_SAIBlockACLKConfig() and 
          RCC_SAIBlockBCLKConfig() functions.
                  
      (#) Each SAI Block A or B can be configured separetely : 
          (++) Program the Master clock divider, Audio mode, Protocol, Data Length, Clock Strobing Edge, 
               Synchronous mode, Output drive and FIFO Thresold using SAI_Init() function.   
               In case of master mode, program the Master clock divider (MCKDIV) using 
               the following formula :  
               (+++) MCLK_x = SAI_CK_x / (MCKDIV * 2) with MCLK_x = 256 * FS
               (+++) FS = SAI_CK_x / (MCKDIV * 2) * 256
               (+++) MCKDIV = SAI_CK_x / FS * 512
         (++) Program the Frame Length, Frame active Length, FS Definition, FS Polarity, 
              FS Offset using SAI_FrameInit() function.    
         (++) Program the Slot First Bit Offset, Slot Size, Slot Number, Slot Active 
              using SAI_SlotInit() function. 
                   
      (#) Enable the NVIC and the corresponding interrupt using the function 
          SAI_ITConfig() if you need to use interrupt mode. 
  
      (#) When using the DMA mode 
          (++) Configure the DMA using DMA_Init() function
          (++) Active the needed channel Request using SAI_DMACmd() function
   
      (#) Enable the SAI using the SAI_Cmd() function.
   
      (#) Enable the DMA using the DMA_Cmd() function when using DMA mode. 
  
      (#) The SAI has some specific functions which can be useful depending 
          on the audio protocol selected.  
          (++) Enable Mute mode when the audio block is a transmitter using SAI_MuteModeCmd()
               function and configure the value transmitted during mute using SAI_MuteValueConfig().  
          (++) Detect the Mute mode when audio block is a receiver using SAI_MuteFrameCounterConfig().             
          (++) Enable the MONO mode without any data preprocessing in memory when the number
               of slot is equal to 2 using SAI_MonoModeConfig() function.
          (++) Enable data companding algorithm (U law and A law) using SAI_CompandingModeConfig().
          (++) Choose the behavior of the SD line in output when an inactive slot is sent 
               on the data line using SAI_TRIStateConfig() function.   
  [..]               
   (@)    In master TX mode: enabling the audio block immediately generates the bit clock 
          for the external slaves even if there is no data in the FIFO, However FS signal 
          generation is conditioned by the presence of data in the FIFO.
                 
   (@)    In master RX mode: enabling the audio block immediately generates the bit clock 
          and FS signal for the external slaves. 
                
   (@)    It is mandatory to respect the following conditions in order to avoid bad SAI behavior: 
            (+@)  First bit Offset <= (SLOT size - Data size)
            (+@)  Data size <= SLOT size
            (+@)  Number of SLOT x SLOT size = Frame length
            (+@)  The number of slots should be even when bit FSDEF in the SAI_xFRCR is set.    
  
    @endverbatim  
                                    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_sai.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SAI 
  * @brief SAI driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* *SAI registers Masks */
#define CR1_CLEAR_MASK            ((uint32_t)0xFF07C010)
#define FRCR_CLEAR_MASK           ((uint32_t)0xFFF88000)
#define SLOTR_CLEAR_MASK          ((uint32_t)0x0000F020)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SAI_Private_Functions
  * @{
  */

/** @defgroup SAI_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  
  [..]
  This section provides a set of functions allowing to initialize the SAI Audio 
  Block Mode, Audio Protocol, Data size, Synchronization between audio block, 
  Master clock Divider, Fifo threshold, Frame configuration, slot configuration,
  Tristate mode, Companding mode and Mute mode.  
  [..] 
  The SAI_Init(), SAI_FrameInit() and SAI_SlotInit() functions follows the SAI Block
  configuration procedures for Master mode and Slave mode (details for these procedures 
  are available in reference manual(RM0090).
  
@endverbatim
  * @{
  */

/**
  * @brief  Deinitialize the SAIx peripheral registers to their default reset values.
  * @param  SAIx: To select the SAIx peripheral, where x can be the different instances 
  *                     
  * @retval None
  */
void SAI_DeInit(SAI_TypeDef* SAIx)
{
  /* Check the parameters */
  assert_param(IS_SAI_PERIPH(SAIx));

  /* Enable SAI1 reset state */
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_SAI1, ENABLE);
  /* Release SAI1 from reset state */
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_SAI1, DISABLE);  
}

/**
  * @brief  Initializes the SAI Block x peripheral according to the specified 
  *         parameters in the SAI_InitStruct.
  *         
  * @note   SAI clock is generated from a specific output of the PLLSAI or a specific  
  *         output of the PLLI2S or from an alternate function bypassing the PLL I2S.
  *        
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  SAI_InitStruct: pointer to a SAI_InitTypeDef structure that
  *         contains the configuration information for the specified SAI Block peripheral.             
  * @retval None
  */
void SAI_Init(SAI_Block_TypeDef* SAI_Block_x, SAI_InitTypeDef* SAI_InitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  
  /* Check the SAI Block parameters */
  assert_param(IS_SAI_BLOCK_MODE(SAI_InitStruct->SAI_AudioMode));
  assert_param(IS_SAI_BLOCK_PROTOCOL(SAI_InitStruct->SAI_Protocol));
  assert_param(IS_SAI_BLOCK_DATASIZE(SAI_InitStruct->SAI_DataSize));
  assert_param(IS_SAI_BLOCK_FIRST_BIT(SAI_InitStruct->SAI_FirstBit));
  assert_param(IS_SAI_BLOCK_CLOCK_STROBING(SAI_InitStruct->SAI_ClockStrobing));
  assert_param(IS_SAI_BLOCK_SYNCHRO(SAI_InitStruct->SAI_Synchro));
  assert_param(IS_SAI_BLOCK_OUTPUT_DRIVE(SAI_InitStruct->SAI_OUTDRIV));
  assert_param(IS_SAI_BLOCK_NODIVIDER(SAI_InitStruct->SAI_NoDivider));
  assert_param(IS_SAI_BLOCK_MASTER_DIVIDER(SAI_InitStruct->SAI_MasterDivider));
  assert_param(IS_SAI_BLOCK_FIFO_THRESHOLD(SAI_InitStruct->SAI_FIFOThreshold));

  /* SAI Block_x CR1 Configuration */
  /* Get the SAI Block_x CR1 value */
  tmpreg = SAI_Block_x->CR1;
  /* Clear MODE, PRTCFG, DS, LSBFIRST, CKSTR, SYNCEN, OUTDRIV, NODIV, and MCKDIV bits */
  tmpreg &= CR1_CLEAR_MASK;
  /* Configure SAI_Block_x: Audio mode, Protocol, Data Size, first transmitted bit, Clock strobing 
     edge, Synchronization mode, Output drive, Master Divider and FIFO level */  
  /* Set MODE bits according to SAI_AudioMode value       */
  /* Set PRTCFG bits according to SAI_Protocol value      */
  /* Set DS bits according to SAI_DataSize value          */
  /* Set LSBFIRST bit according to SAI_FirstBit value     */
  /* Set CKSTR bit according to SAI_ClockStrobing value   */
  /* Set SYNCEN bit according to SAI_Synchro value        */
  /* Set OUTDRIV bit according to SAI_OUTDRIV value       */
  /* Set NODIV bit according to SAI_NoDivider value       */
  /* Set MCKDIV bits according to SAI_MasterDivider value */
  tmpreg |= (uint32_t)(SAI_InitStruct->SAI_AudioMode     | SAI_InitStruct->SAI_Protocol  |
                       SAI_InitStruct->SAI_DataSize      | SAI_InitStruct->SAI_FirstBit  |  
                       SAI_InitStruct->SAI_ClockStrobing | SAI_InitStruct->SAI_Synchro   |  
                       SAI_InitStruct->SAI_OUTDRIV       | SAI_InitStruct->SAI_NoDivider | 
                       (uint32_t)((SAI_InitStruct->SAI_MasterDivider) << 20));
  /* Write to SAI_Block_x CR1 */
  SAI_Block_x->CR1 = tmpreg;
  
  /* SAI Block_x CR2 Configuration */
  /* Get the SAIBlock_x CR2 value */
  tmpreg = SAI_Block_x->CR2;
  /* Clear FTH bits */
  tmpreg &= ~(SAI_xCR2_FTH);
  /* Configure the FIFO Level */
  /* Set FTH bits according to SAI_FIFOThreshold value */ 
  tmpreg |= (uint32_t)(SAI_InitStruct->SAI_FIFOThreshold);
  /* Write to SAI_Block_x CR2 */
  SAI_Block_x->CR2 = tmpreg;
}

/**
  * @brief  Initializes the SAI Block Audio frame according to the specified 
  *         parameters in the SAI_FrameInitStruct.
  *         
  * @note   this function has no meaning if the AC'97 or SPDIF audio protocol 
  *         are selected. 
  *               
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  SAI_FrameInitStruct: pointer to an SAI_FrameInitTypeDef structure that
  *         contains the configuration of audio frame for a specified SAI Block                       
  * @retval None
  */
void SAI_FrameInit(SAI_Block_TypeDef* SAI_Block_x, SAI_FrameInitTypeDef* SAI_FrameInitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  
  /* Check the SAI Block frame parameters */
  assert_param(IS_SAI_BLOCK_FRAME_LENGTH(SAI_FrameInitStruct->SAI_FrameLength));
  assert_param(IS_SAI_BLOCK_ACTIVE_FRAME(SAI_FrameInitStruct->SAI_ActiveFrameLength));
  assert_param(IS_SAI_BLOCK_FS_DEFINITION(SAI_FrameInitStruct->SAI_FSDefinition));
  assert_param(IS_SAI_BLOCK_FS_POLARITY(SAI_FrameInitStruct->SAI_FSPolarity));
  assert_param(IS_SAI_BLOCK_FS_OFFSET(SAI_FrameInitStruct->SAI_FSOffset));

  /* SAI Block_x FRCR Configuration */
  /* Get the SAI Block_x FRCR value */
  tmpreg = SAI_Block_x->FRCR;
  /* Clear FRL, FSALL, FSDEF, FSPOL, FSOFF bits */
  tmpreg &= FRCR_CLEAR_MASK;
  /* Configure SAI_Block_x Frame: Frame Length, Active Frame Length, Frame Synchronization
     Definition, Frame Synchronization Polarity and Frame Synchronization Polarity */
  /* Set FRL bits according to SAI_FrameLength value         */
  /* Set FSALL bits according to SAI_ActiveFrameLength value */
  /* Set FSDEF bit according to SAI_FSDefinition value       */
  /* Set FSPOL bit according to SAI_FSPolarity value         */
  /* Set FSOFF bit according to SAI_FSOffset value           */
  tmpreg |= (uint32_t)((uint32_t)(SAI_FrameInitStruct->SAI_FrameLength - 1)  | 
                       SAI_FrameInitStruct->SAI_FSOffset     | 
                       SAI_FrameInitStruct->SAI_FSDefinition |    
                       SAI_FrameInitStruct->SAI_FSPolarity   |                        
                       (uint32_t)((SAI_FrameInitStruct->SAI_ActiveFrameLength - 1) << 8));
                       
  /* Write to SAI_Block_x FRCR */
  SAI_Block_x->FRCR = tmpreg;
}

/**
  * @brief  Initializes the SAI Block audio Slot according to the specified 
  *         parameters in the SAI_SlotInitStruct.
  *         
  * @note   this function has no meaning if the AC'97 or SPDIF audio protocol 
  *         are selected.
  *               
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  SAI_SlotInitStruct: pointer to an SAI_SlotInitTypeDef structure that
  *         contains the configuration of audio slot for a specified SAI Block                      
  * @retval None
  */
void SAI_SlotInit(SAI_Block_TypeDef* SAI_Block_x, SAI_SlotInitTypeDef* SAI_SlotInitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  
  /* Check the SAI Block Slot parameters */
  assert_param(IS_SAI_BLOCK_FIRSTBIT_OFFSET(SAI_SlotInitStruct->SAI_FirstBitOffset));
  assert_param(IS_SAI_BLOCK_SLOT_SIZE(SAI_SlotInitStruct->SAI_SlotSize));
  assert_param(IS_SAI_BLOCK_SLOT_NUMBER(SAI_SlotInitStruct->SAI_SlotNumber));
  assert_param(IS_SAI_SLOT_ACTIVE(SAI_SlotInitStruct->SAI_SlotActive));

  /* SAI Block_x SLOTR Configuration */
  /* Get the SAI Block_x SLOTR value */
  tmpreg = SAI_Block_x->SLOTR;
  /* Clear FBOFF, SLOTSZ, NBSLOT, SLOTEN bits */
  tmpreg &= SLOTR_CLEAR_MASK;
  /* Configure SAI_Block_x Slot: First bit offset, Slot size, Number of Slot in  
     audio frame and slots activated in audio frame */
  /* Set FBOFF bits according to SAI_FirstBitOffset value  */
  /* Set SLOTSZ bits according to SAI_SlotSize value       */
  /* Set NBSLOT bits according to SAI_SlotNumber value     */
  /* Set SLOTEN bits according to SAI_SlotActive value     */
  tmpreg |= (uint32_t)(SAI_SlotInitStruct->SAI_FirstBitOffset | 
                       SAI_SlotInitStruct->SAI_SlotSize       | 
                       SAI_SlotInitStruct->SAI_SlotActive     |    
                       (uint32_t)((SAI_SlotInitStruct->SAI_SlotNumber - 1) <<  8));
                       
  /* Write to SAI_Block_x SLOTR */
  SAI_Block_x->SLOTR = tmpreg;
}

/**
  * @brief  Fills each SAI_InitStruct member with its default value.
  * @param  SAI_InitStruct: pointer to a SAI_InitTypeDef structure which will 
  *         be initialized.  
  * @retval None
  */
void SAI_StructInit(SAI_InitTypeDef* SAI_InitStruct)
{
  /* Reset SAI init structure parameters values */
  /* Initialize the SAI_AudioMode member */
  SAI_InitStruct->SAI_AudioMode = SAI_Mode_MasterTx;
  /* Initialize the SAI_Protocol member */
  SAI_InitStruct->SAI_Protocol = SAI_Free_Protocol;
  /* Initialize the SAI_DataSize member */
  SAI_InitStruct->SAI_DataSize = SAI_DataSize_8b;
  /* Initialize the SAI_FirstBit member */
  SAI_InitStruct->SAI_FirstBit = SAI_FirstBit_MSB;
  /* Initialize the SAI_ClockStrobing member */
  SAI_InitStruct->SAI_ClockStrobing = SAI_ClockStrobing_FallingEdge;
  /* Initialize the SAI_Synchro member */
  SAI_InitStruct->SAI_Synchro = SAI_Asynchronous;
  /* Initialize the SAI_OUTDRIV member */
  SAI_InitStruct->SAI_OUTDRIV = SAI_OutputDrive_Disabled;
  /* Initialize the SAI_NoDivider member */
  SAI_InitStruct->SAI_NoDivider = SAI_MasterDivider_Enabled;
  /* Initialize the SAI_MasterDivider member */
  SAI_InitStruct->SAI_MasterDivider = 0;
  /* Initialize the SAI_FIFOThreshold member */
  SAI_InitStruct->SAI_FIFOThreshold = SAI_Threshold_FIFOEmpty;
}

/**
  * @brief  Fills each SAI_FrameInitStruct member with its default value.
  * @param  SAI_FrameInitStruct: pointer to a SAI_FrameInitTypeDef structure 
  *         which will be initialized.                     
  * @retval None
  */
void SAI_FrameStructInit(SAI_FrameInitTypeDef* SAI_FrameInitStruct)
{
  /* Reset SAI Frame init structure parameters values */
  /* Initialize the SAI_FrameLength member */
  SAI_FrameInitStruct->SAI_FrameLength = 8;
  /* Initialize the SAI_ActiveFrameLength member */
  SAI_FrameInitStruct->SAI_ActiveFrameLength = 1;
  /* Initialize the SAI_FSDefinition member */
  SAI_FrameInitStruct->SAI_FSDefinition = SAI_FS_StartFrame;
  /* Initialize the SAI_FSPolarity member */
  SAI_FrameInitStruct->SAI_FSPolarity = SAI_FS_ActiveLow;
  /* Initialize the SAI_FSOffset member */
  SAI_FrameInitStruct->SAI_FSOffset = SAI_FS_FirstBit;
}

/**
  * @brief  Fills each SAI_SlotInitStruct member with its default value.
  * @param  SAI_SlotInitStruct: pointer to a SAI_SlotInitTypeDef structure 
  *         which will be initialized.                     
  * @retval None
  */
void SAI_SlotStructInit(SAI_SlotInitTypeDef* SAI_SlotInitStruct)
{
  /* Reset SAI Slot init structure parameters values */
  /* Initialize the SAI_FirstBitOffset member */
  SAI_SlotInitStruct->SAI_FirstBitOffset = 0;
  /* Initialize the SAI_SlotSize member */
  SAI_SlotInitStruct->SAI_SlotSize = SAI_SlotSize_DataSize;
  /* Initialize the SAI_SlotNumber member */
  SAI_SlotInitStruct->SAI_SlotNumber = 1;
  /* Initialize the SAI_SlotActive member */
  SAI_SlotInitStruct->SAI_SlotActive = SAI_Slot_NotActive;

}

/**
  * @brief  Enables or disables the specified SAI Block peripheral.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  NewState: new state of the SAI_Block_x peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SAI_Cmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SAI peripheral */
    SAI_Block_x->CR1 |= SAI_xCR1_SAIEN;
  }
  else
  {
    /* Disable the selected SAI peripheral */
    SAI_Block_x->CR1 &= ~(SAI_xCR1_SAIEN);
  }
}

/**
  * @brief  Configures the mono mode for the selected SAI block.
  * 
  * @note  This function has a meaning only when the number of slot is equal to 2. 
  *      
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  SAI_MonoMode: specifies the SAI block mono mode.
  *          This parameter can be one of the following values:
  *            @arg SAI_MonoMode : Set mono audio mode
  *            @arg SAI_StreoMode : Set streo audio mode                       
  * @retval None
  */
void SAI_MonoModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_Mono_StreoMode)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_MONO_STREO_MODE(SAI_MonoMode));
  /* Clear MONO bit */
  SAI_Block_x->CR1 &= ~(SAI_xCR1_MONO);
  /* Set new Mono Mode value */
  SAI_Block_x->CR1 |= SAI_MonoMode;
}

/**
  * @brief  Configures the TRIState managment on data line for the selected SAI block.
  * 
  * @note  This function has a meaning only when the SAI block is configured in transmitter 
  *      
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  SAI_TRIState: specifies the SAI block TRIState management.
  *          This parameter can be one of the following values:
  *            @arg SAI_Output_NotReleased : SD output line is still drived by the SAI.
  *            @arg SAI_Output_Released : SD output line is released (HI-Z)                       
  * @retval None
  */
void SAI_TRIStateConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_TRIState)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_TRISTATE_MANAGEMENT(SAI_TRIState));
  /* Clear MONO bit */
  SAI_Block_x->CR1 &= ~(SAI_xCR1_MONO);
  /* Set new Mono Mode value */
  SAI_Block_x->CR1 |= SAI_MonoMode;  
  
}

/**
  * @brief  Configures the companding mode for the selected SAI block.
  * 
  * @note  The data expansion or data compression are determined by the state of
  *        SAI block selected (transmitter or receiver). 

  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.              
  * @param  SAI_CompandingMode: specifies the SAI block companding mode.
  *          This parameter can be one of the following values:
  *            @arg SAI_NoCompanding : no companding algorithm set
  *            @arg SAI_ULaw_1CPL_Companding : Set U law (algorithm 1's complement representation)
  *            @arg SAI_ALaw_1CPL_Companding : Set A law (algorithm 1's complement repesentation)  
  *            @arg SAI_ULaw_2CPL_Companding : Set U law (algorithm 2's complement representation)
  *            @arg SAI_ALaw_2CPL_Companding : Set A law (algorithm 2's complement repesentation)  
  * @retval None
  */
void SAI_CompandingModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_CompandingMode)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_COMPANDING_MODE(SAI_CompandingMode));
  /* Clear Companding Mode bits */
  SAI_Block_x->CR2 &= ~(SAI_xCR2_COMP);
  /* Set new Companding Mode value */
  SAI_Block_x->CR2 |= SAI_CompandingMode;
}

/**
  * @brief  Enables or disables the Mute mode for the selected SAI block.
  *    
  * @note   This function has a meaning only when the audio block is transmitter
  * @note   Mute mode is applied for an entire frame for all the valid slot
  *         It becomes active at the end of an audio frame when set somewhere in a frame. 
  *         Mute mode exit occurs at the end of the frame in which the bit MUTE has been set.
  *
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  NewState: new state of the SAIx block. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SAI_MuteModeCmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SAI block mute mode */
    SAI_Block_x->CR2 |= SAI_xCR2_MUTE;
  }
  else
  {
    /* Disable the selected SAI SS output */
    SAI_Block_x->CR2 &= ~(SAI_xCR2_MUTE);
  }
}

/**
  * @brief  Configure the mute value for the selected SAI block.
  *    
  * @note   This function has a meaning only when the audio block is transmitter
  * @note   the configuration last value sent during mute mode has only a meaning 
  *          when the number of slot is lower or equal to 2 and if the MUTE bit is set.
  *           
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  SAI_MuteValue: specifies the SAI block mute value.
  *          This parameter can be one of the following values:
  *            @arg SAI_ZeroValue : bit value 0 is sent during Mute Mode
  *            @arg SAI_LastSentValue : Last value is sent during Mute Mode  
  * @retval None
  */
void SAI_MuteValueConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteValue)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_MUTE_VALUE(SAI_MuteValue));
  
  /* Clear Mute value bits */
  SAI_Block_x->CR2 &= ~(SAI_xCR2_MUTEVAL);
  /* Set new Mute value */
  SAI_Block_x->CR2 |= SAI_MuteValue;
}

/**
  * @brief  Enables or disables the Mute mode for the selected SAI block. 
  *
  * @note   This function has a meaning only when the audio block is Receiver
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  SAI_MuteCounter: specifies the SAI block mute value.
  *         This parameter can be a number between 0 and 63.  
 
  * @retval None
  */
void SAI_MuteFrameCounterConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteCounter)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_MUTE_COUNTER(SAI_MuteCounter));
  
  /* Clear Mute value bits */
  SAI_Block_x->CR2 &= ~(SAI_xCR2_MUTECNT);
  /* Set new Mute value */
  SAI_Block_x->CR2 |= (SAI_MuteCounter << 7);
}

/**
  * @brief  Reinitialize the FIFO pointer
  *   
  * @note   The FIFO pointers can be reinitialized at anytime The data present 
  *         into the FIFO, if it is not empty, will be lost. 
  * 
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  * @param  NewState: new state of the selected SAI TI communication mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SAI_FlushFIFO(SAI_Block_TypeDef* SAI_Block_x)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

  /* FIFO flush */
  SAI_Block_x->CR2 |= SAI_xCR2_FFLUSH;
}

/**
  * @}
  */

/** @defgroup SAI_Group2 Data transfers functions
 *  @brief   Data transfers functions
 *
@verbatim   
 ===============================================================================
                       ##### Data transfers functions #####
 ===============================================================================  
  [..]
  This section provides a set of functions allowing to manage the SAI data transfers.
  [..]
  In reception, data are received and then stored into an internal FIFO while 
  In transmission, data are first stored into an internal FIFO before being 
  transmitted.
  [..]
  The read access of the SAI_xDR register can be done using the SAI_ReceiveData()
  function and returns the Rx buffered value. Whereas a write access to the SAI_DR 
  can be done using SAI_SendData() function and stores the written data into 
  Tx buffer.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the most recent received data by the SAI block x peripheral. 
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral. 
  *         
  * @retval The value of the received data.
  */
uint32_t SAI_ReceiveData(SAI_Block_TypeDef* SAI_Block_x)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  
  /* Return the data in the DR register */
  return SAI_Block_x->DR;
}

/**
  * @brief  Transmits a Data through the SAI block x peripheral.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  *        
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SAI_SendData(SAI_Block_TypeDef* SAI_Block_x, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  
  /* Write in the DR register the data to be sent */
  SAI_Block_x->DR = Data;
}

/**
  * @}
  */

/** @defgroup SAI_Group3 DMA transfers management functions
 *  @brief   DMA transfers management functions
  *
@verbatim   
 ===============================================================================
                  ##### DMA transfers management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the SAI Block x DMA interface.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral. 
  * @param  NewState: new state of the selected SAI block DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SAI_DMACmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected SAI block mute mode */
    SAI_Block_x->CR1 |= SAI_xCR1_DMAEN;
  }
  else
  {
    /* Disable the selected SAI SS output */
    SAI_Block_x->CR1 &= ~(SAI_xCR1_DMAEN);
  }
}

/**
  * @}
  */

/** @defgroup SAI_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
  *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================  
  [..]
  This section provides a set of functions allowing to configure the SAI Interrupts 
  sources and check or clear the flags or pending bits status.
  The user should identify which mode will be used in his application to manage 
  the communication: Polling mode, Interrupt mode or DMA mode. 
    
  *** Polling Mode ***
  ====================
  [..]
  In Polling Mode, the SAI communication can be managed by 7 flags:
     (#) SAI_FLAG_FREQ : to indicate if there is a FIFO Request to write or to read.
     (#) SAI_FLAG_MUTEDET : to indicate if a MUTE frame detected
     (#) SAI_FLAG_OVRUDR : to indicate if an Overrun or Underrun error occur
     (#) SAI_FLAG_AFSDET : to indicate if there is the detection of a audio frame 
                          synchronisation (FS) earlier than expected
     (#) SAI_FLAG_LFSDET : to indicate if there is the detection of a audio frame 
                          synchronisation (FS) later than expected              
     (#) SAI_FLAG_CNRDY : to indicate if  the codec is not ready to communicate during 
                         the reception of the TAG 0 (slot0) of the AC97 audio frame 
     (#) SAI_FLAG_WCKCFG: to indicate if wrong clock configuration in master mode 
                         error occurs.
  [..]
  In this Mode it is advised to use the following functions:
     (+) FlagStatus SAI_GetFlagStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG);
     (+) void SAI_ClearFlag(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG);

  *** Interrupt Mode ***
  ======================
  [..]
  In Interrupt Mode, the SAI communication can be managed by 7 interrupt sources
  and 7 pending bits: 
  (+) Pending Bits:
     (##) SAI_IT_FREQ : to indicate if there is a FIFO Request to write or to read.
     (##) SAI_IT_MUTEDET : to indicate if a MUTE frame detected.
     (##) SAI_IT_OVRUDR : to indicate if an Overrun or Underrun error occur.
     (##) SAI_IT_AFSDET : to indicate if there is the detection of a audio frame 
                          synchronisation (FS) earlier than expected.
     (##) SAI_IT_LFSDET : to indicate if there is the detection of a audio frame 
                          synchronisation (FS) later than expected.              
     (##) SAI_IT_CNRDY : to indicate if  the codec is not ready to communicate during 
                         the reception of the TAG 0 (slot0) of the AC97 audio frame. 
     (##) SAI_IT_WCKCFG: to indicate if wrong clock configuration in master mode 
                         error occurs.

  (+) Interrupt Source:
     (##) SAI_IT_FREQ : specifies the interrupt source for FIFO Request.
     (##) SAI_IT_MUTEDET : specifies the interrupt source for MUTE frame detected.
     (##) SAI_IT_OVRUDR : specifies the interrupt source for overrun or underrun error.
     (##) SAI_IT_AFSDET : specifies the interrupt source for anticipated frame synchronization
                          detection interrupt.
     (##) SAI_IT_LFSDET : specifies the interrupt source for late frame synchronization
                          detection interrupt.             
     (##) SAI_IT_CNRDY : specifies the interrupt source for codec not ready interrupt
     (##) SAI_IT_WCKCFG: specifies the interrupt source for wrong clock configuration
                         interrupt.
  [..]                     
  In this Mode it is advised to use the following functions:
     (+) void SAI_ITConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT, FunctionalState NewState);
     (+) ITStatus SAI_GetITStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT);
     (+) void SAI_ClearITPendingBit(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT);

  *** DMA Mode ***
  ================
  [..]
  In DMA Mode, each SAI audio block has an independent DMA interface in order to 
  read or to write into the SAI_xDR register (to hit the internal FIFO). 
  There is one DMA channel by audio block following basic DMA request/acknowledge 
  protocol.
  [..]
  In this Mode it is advised to use the following function:
    (+) void SAI_DMACmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState);
  [..]
  This section provides also functions allowing to
   (+) Check the SAI Block enable status
   (+)Check the FIFO status 
   
  *** SAI Block Enable status ***
  ===============================
  [..]
  After disabling a SAI Block, it is recommended to check (or wait until) the SAI Block 
  is effectively disabled. If a Block is disabled while an audio frame transfer is ongoing
  the current frame will be transferred and the block will be effectively disabled only at 
  the end of audio frame. 
  To monitor this state it is possible to use the following function:
    (+) FunctionalState SAI_GetCmdStatus(SAI_Block_TypeDef* SAI_Block_x); 
 
  *** SAI Block FIFO status ***
  =============================
  [..]
  It is possible to monitor the FIFO status when a transfer is ongoing using the following 
  function:
    (+) uint32_t SAI_GetFIFOStatus(SAI_Block_TypeDef* SAI_Block_x);
    
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified SAI Block interrupts.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral. 
  * @param  SAI_IT: specifies the SAI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg SAI_IT_FREQ: FIFO Request interrupt mask
  *            @arg SAI_IT_MUTEDET: MUTE detection interrupt mask
  *            @arg SAI_IT_OVRUDR: overrun/underrun interrupt mask
  *            @arg SAI_IT_AFSDET: anticipated frame synchronization detection 
  *                                interrupt mask  
  *            @arg SAI_IT_LFSDET: late frame synchronization detection interrupt 
  *                                mask
  *            @arg SAI_IT_CNRDY: codec not ready interrupt mask
  *            @arg SAI_IT_WCKCFG: wrong clock configuration interrupt mask      
  * @param  NewState: new state of the specified SAI interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SAI_ITConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SAI_BLOCK_CONFIG_IT(SAI_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected SAI Block interrupt */
    SAI_Block_x->IMR |= SAI_IT;
  }
  else
  {
    /* Disable the selected SAI Block interrupt */
    SAI_Block_x->IMR &= ~(SAI_IT);
  }
}

/**
  * @brief  Checks whether the specified SAI block x flag is set or not.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral. 
  * @param  SAI_FLAG: specifies the SAI block flag to check. 
  *          This parameter can be one of the following values:
  *            @arg SAI_FLAG_FREQ: FIFO Request flag.  
  *            @arg SAI_FLAG_MUTEDET: MUTE detection flag.  
  *            @arg SAI_FLAG_OVRUDR: overrun/underrun flag.
  *            @arg SAI_FLAG_WCKCFG: wrong clock configuration flag.            
  *            @arg SAI_FLAG_CNRDY: codec not ready flag. 
  *            @arg SAI_FLAG_AFSDET: anticipated frame synchronization detection flag.
  *            @arg SAI_FLAG_LFSDET: late frame synchronization detection flag.
  * @retval The new state of SAI_FLAG (SET or RESET).
  */
FlagStatus SAI_GetFlagStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_GET_FLAG(SAI_FLAG));
  
  /* Check the status of the specified SAI flag */
  if ((SAI_Block_x->SR & SAI_FLAG) != (uint32_t)RESET)
  {
    /* SAI_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* SAI_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the SAI_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the specified SAI Block x flag.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral. 
  * @param  SAI_FLAG: specifies the SAI block flag to check. 
  *          This parameter can be one of the following values: 
  *            @arg SAI_FLAG_MUTEDET: MUTE detection flag.  
  *            @arg SAI_FLAG_OVRUDR: overrun/underrun flag.
  *            @arg SAI_FLAG_WCKCFG: wrong clock configuration flag.            
  *            @arg SAI_FLAG_CNRDY: codec not ready flag. 
  *            @arg SAI_FLAG_AFSDET: anticipated frame synchronization detection flag.
  *            @arg SAI_FLAG_LFSDET: late frame synchronization detection flag. 
  *  
  * @note    FREQ (FIFO Request) flag is cleared : 
  *          - When the audio block is transmitter and the FIFO is full or the FIFO   
  *            has one data (one buffer mode) depending the bit FTH in the
  *            SAI_xCR2 register.
  *          - When the audio block is receiver and the FIFO is not empty           
  *  
  * @retval None
  */
void SAI_ClearFlag(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_CLEAR_FLAG(SAI_FLAG));
    
  /* Clear the selected SAI Block flag */
  SAI_Block_x->CLRFR |= SAI_FLAG;
}

/**
  * @brief  Checks whether the specified SAI Block x interrupt has occurred or not.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral. 
  * @param  SAI_IT: specifies the SAI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg SAI_IT_FREQ: FIFO Request interrupt 
  *            @arg SAI_IT_MUTEDET: MUTE detection interrupt 
  *            @arg SAI_IT_OVRUDR: overrun/underrun interrupt 
  *            @arg SAI_IT_AFSDET: anticipated frame synchronization detection interrupt                                    
  *            @arg SAI_IT_LFSDET: late frame synchronization detection interrupt                                
  *            @arg SAI_IT_CNRDY: codec not ready interrupt 
  *            @arg SAI_IT_WCKCFG: wrong clock configuration interrupt 
  *                
  * @retval The new state of SAI_IT (SET or RESET).
  */
ITStatus SAI_GetITStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t  enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_CONFIG_IT(SAI_IT));
  
  /* Get the SAI_IT enable bit status */
  enablestatus = (SAI_Block_x->IMR & SAI_IT) ;

  /* Check the status of the specified SAI interrupt */
  if (((SAI_Block_x->SR & SAI_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* SAI_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* SAI_IT is reset */
    bitstatus = RESET;
  }
  /* Return the SAI_IT status */
  return bitstatus;
}

/**
  * @brief  Clears the SAI Block x interrupt pending bit.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral. 
  * @param  SAI_IT: specifies the SAI Block interrupt pending bit to clear. 
  *          This parameter can be one of the following values:  
  *            @arg SAI_IT_MUTEDET: MUTE detection interrupt.  
  *            @arg SAI_IT_OVRUDR: overrun/underrun interrupt.
  *            @arg SAI_IT_WCKCFG: wrong clock configuration interrupt.            
  *            @arg SAI_IT_CNRDY: codec not ready interrupt. 
  *            @arg SAI_IT_AFSDET: anticipated frame synchronization detection interrupt.
  *            @arg SAI_IT_LFSDET: late frame synchronization detection interrupt. 
  *  
  * @note    FREQ (FIFO Request) flag is cleared : 
  *          - When the audio block is transmitter and the FIFO is full or the FIFO   
  *            has one data (one buffer mode) depending the bit FTH in the
  *            SAI_xCR2 register.
  *          - When the audio block is receiver and the FIFO is not empty  
  *            
  * @retval None
  */
void SAI_ClearITPendingBit(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT)
{
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  assert_param(IS_SAI_BLOCK_CONFIG_IT(SAI_IT));

  /* Clear the selected SAI Block x interrupt pending bit */
  SAI_Block_x->CLRFR |= SAI_IT; 
}

/**
  * @brief  Returns the status of EN bit for the specified SAI Block x.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  *   
  * @note    After disabling a SAI Block, it is recommended to check (or wait until) 
  *          the SAI Block is effectively disabled. If a Block is disabled while
  *          an audio frame transfer is ongoing, the current frame will be 
  *          transferred and the block will be effectively disabled only at 
  *          the end of audio frame.  
  *      
  * @retval Current state of the DMAy Streamx (ENABLE or DISABLE).
  */
FunctionalState SAI_GetCmdStatus(SAI_Block_TypeDef* SAI_Block_x)
{
  FunctionalState state = DISABLE;

  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  if ((SAI_Block_x->CR1 & (uint32_t)SAI_xCR1_SAIEN) != 0)
  {
    /* The selected SAI Block x EN bit is set (audio frame transfer is ongoing) */
    state = ENABLE;
  }
  else
  {
    /* The selected SAI Block x EN bit is cleared (SAI Block is disabled and 
        all transfers are complete) */
    state = DISABLE;
  }
  return state;
}

/**
  * @brief  Returns the current SAI Block x FIFO filled level.
  * @param  SAI_Block_x: where x can be A or B to select the SAI Block peripheral.
  *   
  * @retval The FIFO filling state.
  *           - SAI_FIFOStatus_Empty: when FIFO is empty  
  *           - SAI_FIFOStatus_Less1QuarterFull: when FIFO is less than 1 quarter-full 
  *                                               and not empty.
  *           - SAI_FIFOStatus_1QuarterFull: if more than 1 quarter-full.
  *           - SAI_FIFOStatus_HalfFull: if more than 1 half-full.
  *           - SAI_FIFOStatus_3QuartersFull: if more than 3 quarters-full.
  *           - SAI_FIFOStatus_Full: when FIFO is full
  */
uint32_t SAI_GetFIFOStatus(SAI_Block_TypeDef* SAI_Block_x)
{
  uint32_t tmpreg = 0;
 
  /* Check the parameters */
  assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
  
  /* Get the FIFO level bits */
  tmpreg = (uint32_t)((SAI_Block_x->SR & SAI_xSR_FLVL));
  
  return tmpreg;
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
