/**
 ******************************************************************************
  * @brief   TIMER functions of the firmware library.
 ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_timer.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup TIMER
  * @brief TIMER driver modules
  * @{
  */

/** @defgroup TIMER_Private_Defines
  * @{
  */
/* TIMER registers bit mask */
#define SMC_ETR_MASK               ((uint16_t)0x00FF)
#define CHCTLR_OFFSET              ((uint16_t)0x0018)
#define CHE_CHE_SET                ((uint16_t)0x0001)
#define CHE_CHNE_SET               ((uint16_t)0x0004)
/**
  * @}
  */

/* Private function prototypes */
static void TI1_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter);
static void TI2_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter);
static void TI3_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter);
static void TI4_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter);

/** @defgroup TIMER_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the TIMER .
  * @param  TIMERx:  x ={ 0-13 } .
  * @retval None
  */
void TIMER_DeInit(TIMER_TypeDef *TIMERx)
{
    if (TIMERx == TIMER0) {
        RCC->APB2RCR |= RCC_APB2PERIPH_TIMER0RST;
        RCC->APB2RCR &= ~RCC_APB2PERIPH_TIMER0;
    } else if (TIMERx == TIMER1) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER1RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER1;
    } else if (TIMERx == TIMER2) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER2RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER2;
    } else if (TIMERx == TIMER3) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER3RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER3;
    } else if (TIMERx == TIMER4) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER4RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER4;
    } else if (TIMERx == TIMER5) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER5RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER5;
    } else if (TIMERx == TIMER6) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER6RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER6;
    } else if (TIMERx == TIMER7) {
        RCC->APB2RCR |= RCC_APB2PERIPH_TIMER7RST;
        RCC->APB2RCR &= ~RCC_APB2PERIPH_TIMER7;
    } else if (TIMERx == TIMER8) {
        RCC->APB2RCR |= RCC_APB2PERIPH_TIMER8RST;
        RCC->APB2RCR &= ~RCC_APB2PERIPH_TIMER8;
    } else if (TIMERx == TIMER9) {
        RCC->APB2RCR |= RCC_APB2PERIPH_TIMER9RST;
        RCC->APB2RCR &= ~RCC_APB2PERIPH_TIMER9;
    } else if (TIMERx == TIMER10) {
        RCC->APB2RCR |= RCC_APB2PERIPH_TIMER10RST;
        RCC->APB2RCR &= ~RCC_APB2PERIPH_TIMER10;
    } else if (TIMERx == TIMER11) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER11RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER11;
    } else if (TIMERx == TIMER12) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER12RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER12;
    } else if (TIMERx == TIMER13) {
        RCC->APB1RCR |= RCC_APB1PERIPH_TIMER13RST;
        RCC->APB1RCR &= ~RCC_APB1PERIPH_TIMER13;
    }
}

/**
  * @brief  Initialize the specified Timer
  * @param  TIMERx:  x ={ 0 -13 } .
  * @param  TIMER_Init: pointer to a TIMER_BaseInitPara structure.
  * @retval None
  */
void TIMER_BaseInit(TIMER_TypeDef *TIMERx, TIMER_BaseInitPara *TIMER_Init)
{
    uint16_t tmpctlr1 = 0;

    tmpctlr1 = TIMERx->CTLR1;

    if ((TIMERx == TIMER0) || (TIMERx == TIMER7) || (TIMERx == TIMER1) || (TIMERx == TIMER2) ||
            (TIMERx == TIMER3) || (TIMERx == TIMER4) || (TIMERx == TIMER8) || (TIMERx == TIMER9)
            || (TIMERx == TIMER10) || (TIMERx == TIMER11) || (TIMERx == TIMER12) || (TIMERx == TIMER13)) {
        /* Configure the Counter Mode */
        tmpctlr1 &= (uint16_t)(~((uint16_t)(TIMER_CTLR1_DIR | TIMER_CTLR1_CAM)));
        tmpctlr1 |= (uint32_t)TIMER_Init->TIMER_CounterMode;
    }

    if ((TIMERx != TIMER5) && (TIMERx != TIMER6)) {
        /* Configure the clock division */
        tmpctlr1 &= (uint16_t)(~((uint16_t)TIMER_CTLR1_CDIV));
        tmpctlr1 |= (uint32_t)TIMER_Init->TIMER_ClockDivision;
    }

    TIMERx->CTLR1 = tmpctlr1;

    /* Configure the Autoreload value */
    TIMERx->CARL = TIMER_Init->TIMER_Period ;

    /* Configure the Prescaler value */
    TIMERx->PSC = TIMER_Init->TIMER_Prescaler;

    if ((TIMERx == TIMER0)  ||
            (TIMERx == TIMER7)) {
        /* Configure the Repetition Counter value */
        TIMERx->CREP = TIMER_Init->TIMER_RepetitionCounter;
    }

    /* Generate an update event */
    TIMERx->EVG = TIMER_PSC_RELOAD_NOW;
}

/**
  * @brief  Fill each TIMER_BaseInitPara Struct member with a default value.
  * @param  TIMER_Init: pointer to a TIMER_BaseInitPara structure.
  * @retval None
  */
void TIMER_BaseStructInit(TIMER_BaseInitPara *TIMER_Init)
{
    /* Fill the default value */
    TIMER_Init->TIMER_Period                = 0xFFFFFFFF;
    TIMER_Init->TIMER_Prescaler             = 0x0000;
    TIMER_Init->TIMER_ClockDivision         = TIMER_CDIV_DIV1;
    TIMER_Init->TIMER_CounterMode           = TIMER_COUNTER_UP;
    TIMER_Init->TIMER_RepetitionCounter     = 0x0000;
}

/**
  * @brief  Configure the TIMER Prescaler.
  * @param  TIMERx:  x ={ 0-13 }
  * @param  Prescaler:  Prescaler value
  * @param  TIMER_PSCReloadMode:  Prescaler Reload mode
  *   This value will be :
  *     @arg TIMER_PSC_RELOAD_UPDATE    : The Prescaler is loaded at the next update event.
  *     @arg TIMER_PSC_RELOAD_NOW       : The Prescaler is loaded right now.
  * @retval None
  */
void TIMER_PrescalerConfig(TIMER_TypeDef *TIMERx, uint16_t Prescaler, uint16_t TIMER_PSCReloadMode)
{
    /* Set PSC */
    TIMERx->PSC = Prescaler;

    /* Choose reload mode */
    TIMERx->EVG = TIMER_PSCReloadMode;
}

/**
  * @brief  Configure the TIMER Counter Mode
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_CounterMode:  the Counter Mode
  *   This value will be :
  *     @arg TIMER_COUNTER_UP             : Up Counting Mode
  *     @arg TIMER_COUNTER_DOWN           : Down Counting Mode
  *     @arg TIMER_COUNTER_CENTER_ALIGNED1: Center Aligned Counting Mode1
  *     @arg TIMER_COUNTER_CENTER_ALIGNED2: Center Aligned Counting Mode2
  *     @arg TIMER_COUNTER_CENTER_ALIGNED3: Center Aligned Counting Mode3
  * @retval None
  */
void TIMER_CounterMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_CounterMode)
{
    uint16_t tmpctlr1 = 0;

    tmpctlr1 = TIMERx->CTLR1;

    /* Reset the CAM and DIR Bits */
    tmpctlr1 &= (uint16_t)(~((uint16_t)(TIMER_CTLR1_DIR | TIMER_CTLR1_CAM)));

    /* Configures the Counter Mode */
    tmpctlr1 |= TIMER_CounterMode;

    /* Update the TIMER CTLR1 */
    TIMERx->CTLR1 = tmpctlr1;
}

/**
  * @brief  Configure the TIMER Counter Register value
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  Counter: the Counter register new value.
  * @retval None
  */
void TIMER_SetCounter(TIMER_TypeDef *TIMERx, uint32_t Counter)
{
    TIMERx->CNT = Counter;
}

/**
  * @brief  Configure the Autoreload value
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  AutoReloadValue:
  * @retval None
  */
void TIMER_SetAutoreload(TIMER_TypeDef *TIMERx, uint32_t AutoReloadValue)
{
    TIMERx->CARL = AutoReloadValue;
}

/**
  * @brief  Get the Counter value.
  * @param  TIMERx:  x ={ 0-13 } .
  * @retval Counter Register value.
  */
uint32_t TIMER_GetCounter(TIMER_TypeDef *TIMERx)
{
    return TIMERx->CNT;
}

/**
  * @brief  Get the Prescaler value.
  * @param  TIMERx:  x ={ 0-13 } .
  * @retval Prescaler Register value
  */
uint16_t TIMER_GetPrescaler(TIMER_TypeDef *TIMERx)
{
    return TIMERx->PSC;
}

/**
  * @brief  Configure the TIMERx Update event.
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  NewValue: new value of the TIMERx UPDIS bit
  *   This value will be :
  *     @arg ENABLE  : Update Enbale
  *     @arg DISABLE : Update Disable
  * @retval None
  */
void TIMER_UpdateDisableConfig(TIMER_TypeDef *TIMERx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        TIMERx->CTLR1 |= TIMER_CTLR1_UPDIS;
    } else {
        TIMERx->CTLR1 &= (uint16_t)~((uint16_t)TIMER_CTLR1_UPDIS);
    }
}

/**
  * @brief  Configure the TIMER Update Request source.
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  TIMER_UpdateSrc: Configures the Update source.
  *   This value will be :
  *     @arg TIMER_UPDATE_SRC_GLOBAL    : Update generate by setting of UPG bit or the counter
  *                                       overflow/underflow , or the slave mode controller trigger.
  *     @arg TIMER_UPDATE_SRC_REGULAR   : Update generate only by counter overflow/underflow.
  * @retval None
  */
void TIMER_UpdateRequestConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_UpdateSrc)
{
    if (TIMER_UpdateSrc != TIMER_UPDATE_SRC_GLOBAL) {
        TIMERx->CTLR1 |= TIMER_CTLR1_UPS;
    } else {
        TIMERx->CTLR1 &= (uint16_t)~((uint16_t)TIMER_CTLR1_UPS);
    }
}

/**
  * @brief  Configure the CARL Preload function
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  NewValue: the state of the Preload function on CARL.
  *   This value will be :
  *     @arg ENABLE
  *     @arg DISABLE
  * @retval None
  */
void TIMER_CARLPreloadConfig(TIMER_TypeDef *TIMERx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Set the CARL Preload Bit */
        TIMERx->CTLR1 |= TIMER_CTLR1_ARSE;
    } else {
        /* Reset the CARL Preload Bit */
        TIMERx->CTLR1 &= (uint16_t)~((uint16_t)TIMER_CTLR1_ARSE);
    }
}

/**
  * @brief  Select the TIMER Single Pulse Mode.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_SPMode: specifies the SPM Mode to be used.
  *   This value will be :
  *     @arg TIMER_SP_MODE_SINGLE
  *     @arg TIMER_SP_MODE_REPETITIVE
  * @retval None
  */
void TIMER_SinglePulseMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_SPMode)
{
    /* Reset the SPM Bit */
    TIMERx->CTLR1 &= (uint16_t)~((uint16_t)TIMER_CTLR1_SPM);

    /* Set the SPM Bit */
    TIMERx->CTLR1 |= TIMER_SPMode;
}

/**
  * @brief  Configure the TIMERx Clock Division value.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_CDIV: the clock division value.
  *   This value will be :
  *     @arg TIMER_CDIV_DIV1: TDTS = Tck_tim
  *     @arg TIMER_CDIV_DIV2: TDTS = 2*Tck_tim
  *     @arg TIMER_CDIV_DIV4: TDTS = 4*Tck_tim
  * @retval None
  */
void TIMER_SetClockDivision(TIMER_TypeDef *TIMERx, uint16_t TIMER_CDIV)
{
    /* Reset the CDIV value*/
    TIMERx->CTLR1 &= (uint16_t)~((uint16_t)TIMER_CTLR1_CDIV);

    /* Set the CDIV value */
    TIMERx->CTLR1 |= TIMER_CDIV;
}

/**
  * @brief  ENABLE or DISABLE the TIMER.
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_Enable(TIMER_TypeDef *TIMERx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the TIMER */
        TIMERx->CTLR1 |= TIMER_CTLR1_CNTE;
    } else {
        /* Disable the TIMER */
        TIMERx->CTLR1 &= (uint16_t)(~((uint16_t)TIMER_CTLR1_CNTE));
    }
}

/**
  * @brief  Configure the: Break feature, dead time, Lock level, ROS/IOS State and the OAE
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  TIMER_BKDTInit: pointer to a TIMER_BKDTInitPara structure that
  *         contains the BKDT Register configuration  information for the TIMER.
  * @retval None
  */
void TIMER_BKDTConfig(TIMER_TypeDef *TIMERx, TIMER_BKDTInitPara *TIMER_BKDTInit)
{
    TIMERx->BKDT = (uint32_t)TIMER_BKDTInit->TIMER_ROSState      |
                   TIMER_BKDTInit->TIMER_IOSState      |
                   TIMER_BKDTInit->TIMER_LOCKLevel     |
                   TIMER_BKDTInit->TIMER_DeadTime      |
                   TIMER_BKDTInit->TIMER_Break         |
                   TIMER_BKDTInit->TIMER_BreakPolarity |
                   TIMER_BKDTInit->TIMER_OutAuto;
}

/**
  * @brief  Fill TIMER_BKDTInit structure member with default value.
  * @param  TIMER_BKDTInit :  pointer to a TIMER_BKDTInitPara structure which will be initialized.
  * @retval None
  */
void TIMER_BKDTStructInit(TIMER_BKDTInitPara *TIMER_BKDTInit)
{
    TIMER_BKDTInit->TIMER_ROSState         = TIMER_ROS_STATE_DISABLE;
    TIMER_BKDTInit->TIMER_IOSState         = TIMER_IOS_STATE_DISABLE;
    TIMER_BKDTInit->TIMER_LOCKLevel        = TIMER_LOCK_LEVEL_OFF;
    TIMER_BKDTInit->TIMER_DeadTime         = 0x00;
    TIMER_BKDTInit->TIMER_Break            = TIMER_BREAK_DISABLE;
    TIMER_BKDTInit->TIMER_BreakPolarity    = TIMER_BREAK_POLARITY_LOW;
    TIMER_BKDTInit->TIMER_OutAuto          = TIMER_OUTAUTO_DISABLE;
}

/**
  * @brief  Enable or disable the TIMER ALL Outputs.
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  NewValue: ENABLE or DISABLE .
  * @retval None
  */
void TIMER_CtrlPWMOutputs(TIMER_TypeDef *TIMERx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the TIMER ALL Output */
        TIMERx->BKDT |= TIMER_BKDT_POE;
    } else {
        /* Disable the TIMER ALL Output */
        TIMERx->BKDT &= (uint16_t)(~((uint16_t)TIMER_BKDT_POE));
    }
}

/**
  * @brief  Initialize the TIMERx Channel1 with TIMER_OCInitPara .
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_OCInit : pointer to a TIMER_OCInitPara structure .
  * @retval None
  */
void TIMER_OC1_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit)
{
    uint16_t tmpchctlrx = 0, tmpche = 0, tmpctlr2 = 0;

    /* Disable the Channel 1: Reset the CH1E Bit */
    TIMERx->CHE &= (uint16_t)(~(uint16_t)TIMER_CHE_CH1E);

    /* Get the TIMERx CHE register value */
    tmpche = TIMERx->CHE;

    /* Get the TIMERx CTLR2 register value */
    tmpctlr2 =    TIMERx->CTLR2;

    /* Get the TIMERx CHCTLR1 register value */
    tmpchctlrx = TIMERx->CHCTLR1;

    /* Reset the Output Compare Mode Bits */
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR1_CH1OM));
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR1_CH1M));

    /* Select the Output Compare Mode */
    tmpchctlrx |= TIMER_OCInit->TIMER_OCMode;

    /* Reset the Output Polarity */
    tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH1P));

    /* Set the Output Compare Polarity */
    tmpche |= TIMER_OCInit->TIMER_OCPolarity;

    /* Set the Output State */
    tmpche |= TIMER_OCInit->TIMER_OutputState;

    if ((TIMERx == TIMER0) || (TIMERx == TIMER7)) {
        /* Reset the Output complementary Polarity */
        tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH1NP));

        /* Set the Output complementary Polarity */
        tmpche |= TIMER_OCInit->TIMER_OCNPolarity;

        /* Reset the Output complementary State */
        tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH1NE));

        /* Set the Output complementary State */
        tmpche |= TIMER_OCInit->TIMER_OutputNState;

        /* Reset the Ouput Compare and Output Compare complementary IDLE State */
        tmpctlr2 &= (uint16_t)(~((uint16_t)TIMER_CTLR2_ISO1));
        tmpctlr2 &= (uint16_t)(~((uint16_t)TIMER_CTLR2_ISO1N));

        /* Set the Output Idle state */
        tmpctlr2 |= TIMER_OCInit->TIMER_OCIdleState;

        /* Set the Output complementary Idle state */
        tmpctlr2 |= TIMER_OCInit->TIMER_OCNIdleState;
    }

    /* Write to TIMERx CTLR2 */
    TIMERx->CTLR2 = tmpctlr2;

    /* Write to TIMERx CHCTLR1 */
    TIMERx->CHCTLR1 = tmpchctlrx;

    /* Set the Capture / Compare Register value */
    TIMERx->CHCC1 = TIMER_OCInit->TIMER_Pulse;

    /* Write to TIMERx CHE */
    TIMERx->CHE = tmpche;
}

/**
  * @brief  Initialize the TIMERx Channel2 with TIMER_OCInitPara .
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_OCInit : pointer to a TIMER_OCInitPara structure .
  * @retval None
  */
void TIMER_OC2_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit)
{
    uint16_t tmpchctlrx = 0, tmpche = 0, tmpctlr2 = 0;

    /* Disable the Channel 2: Reset the CH2E Bit */
    TIMERx->CHE &= (uint16_t)(~((uint16_t)TIMER_CHE_CH2E));

    /* Get the TIMERx CHE register value */
    tmpche = TIMERx->CHE;

    /* Get the TIMERx CTLR2 register value */
    tmpctlr2 =    TIMERx->CTLR2;

    /* Get the TIMERx CHCTLR1 register value */
    tmpchctlrx = TIMERx->CHCTLR1;

    /* Reset the Output Compare Mode Bits */
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR1_CH2OM));
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR1_CH2M));

    /* Select the Output Compare Mode */
    tmpchctlrx |= (uint16_t)(TIMER_OCInit->TIMER_OCMode << 8);

    /* Reset the Output Polarity */
    tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH2P));

    /* Set the Output Compare Polarity */
    tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OCPolarity << 4);

    /* Set the Output State */
    tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OutputState << 4);

    if ((TIMERx == TIMER0) || (TIMERx == TIMER7)) {
        /* Reset the Output complementary Polarity */
        tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH2NP));

        /* Set the Output complementary Polarity */
        tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OCNPolarity << 4);

        /* Reset the Output complementary State */
        tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH2NE));

        /* Set the Output complementary State */
        tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OutputNState << 4);

        /* Reset the Ouput Compare and Output Compare complementary IDLE State */
        tmpctlr2 &= (uint16_t)(~((uint16_t)TIMER_CTLR2_ISO2));
        tmpctlr2 &= (uint16_t)(~((uint16_t)TIMER_CTLR2_ISO2N));

        /* Set the Output Idle state */
        tmpctlr2 |= (uint16_t)(TIMER_OCInit->TIMER_OCIdleState << 2);

        /* Set the Output complementary Idle state */
        tmpctlr2 |= (uint16_t)(TIMER_OCInit->TIMER_OCNIdleState << 2);
    }

    /* Write to TIMERx CTLR2 */
    TIMERx->CTLR2 = tmpctlr2;

    /* Write to TIMERx CHCTLR1 */
    TIMERx->CHCTLR1 = tmpchctlrx;

    /* Set the Capture / Compare Register value */
    TIMERx->CHCC2 = TIMER_OCInit->TIMER_Pulse;

    /* Write to TIMERx CHE */
    TIMERx->CHE = tmpche;
}

/**
  * @brief  Initialize the TIMERx Channel3 with TIMER_OCInitPara .
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8} .
  * @param  TIMER_OCInit : pointer to a TIMER_OCInitPara structure .
  * @retval None
  */
void TIMER_OC3_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit)
{
    uint16_t tmpchctlrx = 0, tmpche = 0, tmpctlr2 = 0;

    /* Disable the Channel 3: Reset the CH3E Bit */
    TIMERx->CHE &= (uint16_t)(~((uint16_t)TIMER_CHE_CH3E));

    /* Get the TIMERx CHE register value */
    tmpche = TIMERx->CHE;

    /* Get the TIMERx CTLR2 register value */
    tmpctlr2 =    TIMERx->CTLR2;

    /* Get the TIMERx CHCTLR2 register value */
    tmpchctlrx = TIMERx->CHCTLR2;

    /* Reset the Output Compare Mode Bits */
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR2_CH3OM));
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR2_CH3M));

    /* Select the Output Compare Mode */
    tmpchctlrx |= TIMER_OCInit->TIMER_OCMode;

    /* Reset the Output Polarity */
    tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH3P));

    /* Set the Output Compare Polarity */
    tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OCPolarity << 8);

    /* Set the Output State */
    tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OutputState << 8);

    if ((TIMERx == TIMER0) || (TIMERx == TIMER7)) {
        /* Reset the Output complementary Polarity */
        tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH3NP));

        /* Set the Output complementary Polarity */
        tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OCNPolarity << 8);

        /* Reset the Output complementary State */
        tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH3NE));

        /* Set the Output complementary State */
        tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OutputNState << 8);

        /* Reset the Ouput Compare and Output Compare complementary IDLE State */
        tmpctlr2 &= (uint16_t)(~((uint16_t)TIMER_CTLR2_ISO3));
        tmpctlr2 &= (uint16_t)(~((uint16_t)TIMER_CTLR2_ISO3N));

        /* Set the Output Idle state */
        tmpctlr2 |= (uint16_t)(TIMER_OCInit->TIMER_OCIdleState << 4);

        /* Set the Output complementary Idle state */
        tmpctlr2 |= (uint16_t)(TIMER_OCInit->TIMER_OCNIdleState << 4);
    }
    /* Write to TIMERx CTLR2 */
    TIMERx->CTLR2 = tmpctlr2;

    /* Write to TIMERx CHCTLR2 */
    TIMERx->CHCTLR2 = tmpchctlrx;

    /* Set the Capture / Compare Register value */
    TIMERx->CHCC3 = TIMER_OCInit->TIMER_Pulse;

    /* Write to TIMERx CHE */
    TIMERx->CHE = tmpche;
}

/**
  * @brief  Initialize the TIMERx Channel4 with TIMER_OCInitPara .
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8} .
  * @param  TIMER_OCInit : pointer to a TIMER_OCInitPara structure .
  * @retval None
  */
void TIMER_OC4_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit)
{
    uint16_t tmpchctlrx = 0, tmpche = 0, tmpctlr2 = 0;

    /* Disable the Channel 4: Reset the CH4E Bit */
    TIMERx->CHE &= (uint16_t)(~((uint16_t)TIMER_CHE_CH4E));

    /* Get the TIMERx CHE register value */
    tmpche = TIMERx->CHE;

    /* Get the TIMERx CTLR2 register value */
    tmpctlr2 =    TIMERx->CTLR2;

    /* Get the TIMERx CHCTLR2 register value */
    tmpchctlrx = TIMERx->CHCTLR2;

    /* Reset the Output Compare Mode Bits */
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR2_CH4OM));
    tmpchctlrx &= (uint16_t)(~((uint16_t)TIMER_CHCTLR2_CH4M));

    /* Select the Output Compare Mode */
    tmpchctlrx |= (uint16_t)(TIMER_OCInit->TIMER_OCMode << 8);

    /* Reset the Output Polarity */
    tmpche &= (uint16_t)(~((uint16_t)TIMER_CHE_CH4P));

    /* Set the Output Compare Polarity */
    tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OCPolarity << 12);

    /* Set the Output State */
    tmpche |= (uint16_t)(TIMER_OCInit->TIMER_OutputState << 12);

    if ((TIMERx == TIMER0) || (TIMERx == TIMER7)) {
        /* Reset the Ouput Compare IDLE State */
        tmpctlr2 &= (uint16_t)(~((uint16_t)TIMER_CTLR2_ISO4));

        /* Set the Output Idle state */
        tmpctlr2 |= (uint16_t)(TIMER_OCInit->TIMER_OCIdleState << 6);
    }

    /* Write to TIMERx CTLR2 */
    TIMERx->CTLR2 = tmpctlr2;

    /* Write to TIMERx CHCTLR2 */
    TIMERx->CHCTLR2 = tmpchctlrx;

    /* Set the Capture Compare Register value */
    TIMERx->CHCC4 = TIMER_OCInit->TIMER_Pulse;

    /* Write to TIMERx CHE */
    TIMERx->CHE = tmpche;
}

/**
  * @brief  Fill TIMER_OCInitPara member with default value.
  * @param  TIMER_OCInit: pointer to a TIMER_OCInitPara structure.
  * @retval None
  */
void TIMER_OCStructInit(TIMER_OCInitPara *TIMER_OCInit)
{
    TIMER_OCInit->TIMER_OCMode         = TIMER_OC_MODE_TIMING;
    TIMER_OCInit->TIMER_OutputState    = TIMER_OUTPUT_STATE_DISABLE;
    TIMER_OCInit->TIMER_OutputNState   = TIMER_OUTPUTN_STATE_DISABLE;
    TIMER_OCInit->TIMER_Pulse          = 0x0000000;
    TIMER_OCInit->TIMER_OCPolarity     = TIMER_OC_POLARITY_HIGH;
    TIMER_OCInit->TIMER_OCNPolarity    = TIMER_OC_POLARITY_HIGH;
    TIMER_OCInit->TIMER_OCIdleState    = TIMER_OC_IDLE_STATE_RESET;
    TIMER_OCInit->TIMER_OCNIdleState   = TIMER_OCN_IDLE_STATE_RESET;
}

/**
  * @brief  Configure the TIMER Output Compare Mode.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_Ch:
  *   This value will be :
  *     @arg TIMER_CH_1
  *     @arg TIMER_CH_2
  *     @arg TIMER_CH_3
  *     @arg TIMER_CH_4
  * @param  TIMER_OCMode: the TIMER Output Compare Mode.
  *   This value will be :
  *     @arg TIMER_OC_MODE_TIMING
  *     @arg TIMER_OC_MODE_ACTIVE
  *     @arg TIMER_OC_MODE_TOGGLE
  *     @arg TIMER_OC_MODE_PWM1
  *     @arg TIMER_OC_MODE_PWM2
  *     @arg TIMER_FORCED_HIGH
  *     @arg TIMER_FORCED_LOW
  * @retval None
  */
void TIMER_OCxModeConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_Ch, uint16_t TIMER_OCMode)
{
    uint32_t tmp = 0;
    uint16_t tmp1 = 0;

    tmp = (uint32_t) TIMERx;
    tmp += CHCTLR_OFFSET;

    tmp1 = CHE_CHE_SET << (uint16_t)TIMER_Ch;

    /* Disable the Channel: Reset the CHxE Bit */
    TIMERx->CHE &= (uint16_t) ~tmp1;

    if ((TIMER_Ch == TIMER_CH_1) || (TIMER_Ch == TIMER_CH_3)) {
        tmp += (TIMER_Ch >> 1);

        /* Reset the CHxOM bits in the CHCTLRx register */
        *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TIMER_CHCTLR1_CH1OM);

        /* Configure the CHxOM bits in the CHCTLRx register */
        *(__IO uint32_t *) tmp |= TIMER_OCMode;
    } else {
        tmp += (uint16_t)(TIMER_Ch - (uint16_t)4) >> (uint16_t)1;

        /* Reset the CHxOM bits in the CHCTLRx register */
        *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TIMER_CHCTLR1_CH2OM);

        /* Configure the CHxOM bits in the CHCTLRx register */
        *(__IO uint32_t *) tmp |= (uint16_t)(TIMER_OCMode << 8);
    }
}

/**
  * @brief  Configure the TIMERx Capture or Compare Register value
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  CompValue1: the Capture / Compare1 register new value
  * @retval None
  */
void TIMER_Compare1Config(TIMER_TypeDef *TIMERx, uint32_t CompValue1)
{
    TIMERx->CHCC1 = CompValue1 ;
}

/**
  * @brief  Configure the TIMERx Capture or Compare Register value
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  CompValue2: the Capture / Compare1 register new value
  * @retval None
  */
void TIMER_Compare2Config(TIMER_TypeDef *TIMERx, uint32_t CompValue2)
{
    TIMERx->CHCC2 = CompValue2;
}

/**
  * @brief  Configure the TIMERx Capture or Compare Register value
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  CompValue3: the Capture / Compare1 register new value
  * @retval None
  */
void TIMER_Compare3Config(TIMER_TypeDef *TIMERx, uint32_t CompValue3)
{
    TIMERx->CHCC3 = CompValue3;
}

/**
  * @brief  Configure the TIMERx Capture or Compare Register value
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  CompValue4: the Capture / Compare1 register new value
  * @retval None
  */
void TIMER_Compare4Config(TIMER_TypeDef *TIMERx, uint32_t CompValue4)
{
    TIMERx->CHCC4 = CompValue4;
}

/**
  * @brief  Force the TIMERx output level to high or low
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_Forced: forced the output level.
  *   This value will be :
  *     @arg TIMER_FORCED_HIGH: Force output high level
  *     @arg TIMER_FORCED_LOW : Force output low level
  * @retval None
  */
void TIMER_Forced_OC1(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the CH1OM Bits */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1OM);

    /* Configure The Forced output Mode */
    tmpchctlr1 |= TIMER_Forced ;

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  Force the TIMERx output level to high or low
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_Forced: forced the output level.
  *   This value will be :
  *     @arg TIMER_FORCED_HIGH: Force output high level
  *     @arg TIMER_FORCED_LOW : Force output low level
  * @retval None
  */
void TIMER_Forced_OC2(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the CH2OM Bits */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH2OM);

    /* Configure The Forced output Mode */
    tmpchctlr1 |= (uint16_t)(TIMER_Forced << 8);

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  Force the TIMERx output level to high or low
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_Forced: forced the output level.
  *   This value will be :
  *     @arg TIMER_FORCED_HIGH: Force output high level
  *     @arg TIMER_FORCED_LOW : Force output low level
  * @retval None
  */
void TIMER_Forced_OC3(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the CH3OM Bits */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH3OM);

    /* Configure The Forced output Mode */
    tmpchctlr2 |= TIMER_Forced ;

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  Force the TIMERx output level to high or low
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_Forced: forced the output level.
  *   This value will be :
  *     @arg TIMER_FORCED_HIGH: Force output high level
  *     @arg TIMER_FORCED_LOW : Force output low level
  * @retval None
  */
void TIMER_Forced_OC4(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the CH4OM Bits */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH4OM);

    /* Configure The Forced output Mode */
    tmpchctlr2 |= (uint16_t)(TIMER_Forced << 8);

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  Configure the TIMER Capture or Compare Preload Control bit
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_CC_PreloadControl(TIMER_TypeDef *TIMERx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Set the CCSE Bit */
        TIMERx->CTLR2 |= TIMER_CTLR2_CCSE;
    } else {
        /* Reset the CCSE Bit */
        TIMERx->CTLR2 &= (uint16_t)~((uint16_t)TIMER_CTLR2_CCSE);
    }
}

/**
  * @brief  Configure the TIMER channel 1 Capture or Compare Preload register
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_OCPreload : state of the TIMERx Preload register
  *   This value will be :
  *     @arg TIMER_OC_PRELOAD_ENABLE
  *     @arg TIMER_OC_PRELOAD_DISABLE
  * @retval None
  */
void TIMER_OC1_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the CH1OSE Bit */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1OSE);

    /* Enable or Disable  the Output Compare Preload  */
    tmpchctlr1 |= TIMER_OCPreload;

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  Configure the TIMER channel 2 Capture or Compare Preload register
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_OCPreload : state of the TIMERx Preload register
  *   This value will be :
  *     @arg TIMER_OC_PRELOAD_ENABLE
  *     @arg TIMER_OC_PRELOAD_DISABLE
  * @retval None
  */
void TIMER_OC2_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the CH2OSE Bit */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH2OSE);

    /* Enable or Disable  the Output Compare Preload  */
    tmpchctlr1 |= (uint16_t)(TIMER_OCPreload << 8);

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  Configure the TIMER channel 3 Capture or Compare Preload register
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCPreload : state of the TIMERx Preload register
  *   This value will be :
  *     @arg TIMER_OC_PRELOAD_ENABLE
  *     @arg TIMER_OC_PRELOAD_DISABLE
  * @retval None
  */
void TIMER_OC3_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the CH3OSE Bit */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH3OSE);

    /* Enable or Disable  the Output Compare Preload  */
    tmpchctlr2 |= TIMER_OCPreload;

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  Configure the TIMER channel 4 Capture or Compare Preload register
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCPreload : state of the TIMERx Preload register
  *   This value will be :
  *     @arg TIMER_OC_PRELOAD_ENABLE
  *     @arg TIMER_OC_PRELOAD_DISABLE
  * @retval None
  */
void TIMER_OC4_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the CH4OSE Bit */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH4OSE);

    /* Enable or Disable the Output Compare Preload  */
    tmpchctlr2 |= (uint16_t)(TIMER_OCPreload << 8);

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  Configure the TIMER channel 1 Compare output Fast mode
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_OCFast: state of the Compare Output Fast Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_FAST_ENABLE : output fast enable
  *     @arg TIMER_OC_FAST_DISABLE: output fast disable
  * @retval None
  */
void TIMER_OC1_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the CH1OFE Bit */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1OFE);

    /* Enable or Disable the Output Compare Fast Bit  */
    tmpchctlr1 |= TIMER_OCFast;

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  Configure the TIMER channel 2 Compare output Fast mode
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_OCFast: state of the Compare Output Fast Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_FAST_ENABLE : output fast enable
  *     @arg TIMER_OC_FAST_DISABLE: output fast disable
  * @retval None
  */
void TIMER_OC2_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the CH2OFE Bit */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH2OFE);

    /* Enable or Disable the Output Compare Fast Bit  */
    tmpchctlr1 |= (uint16_t)(TIMER_OCFast << 8);

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  Configure the TIMER channel 3 Compare output Fast mode
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCFast: state of the Compare Output Fast Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_FAST_ENABLE : output fast enable
  *     @arg TIMER_OC_FAST_DISABLE: output fast disable
  * @retval None
  */
void TIMER_OC3_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the CH3OFE Bit */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH3OFE);

    /* Enable or Disable the Output Compare Fast Bit  */
    tmpchctlr2 |= TIMER_OCFast;

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  Configure the TIMER channel 4 Compare output Fast mode
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCFast: state of the Compare Output Fast Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_FAST_ENABLE : output fast enable
  *     @arg TIMER_OC_FAST_DISABLE: output fast disable
  * @retval None
  */
void TIMER_OC4_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the CH4OFE Bit */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH4OFE);

    /* Enable or Disable the Output Compare Fast Bit */
    tmpchctlr2 |= (uint16_t)(TIMER_OCFast << 8);

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  If Clear the OCREF signal on an external event
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_CLEAR_ENABLE : Output clear enable
  *     @arg TIMER_OC_CLEAR_DISABLE: Output clear disable
  * @retval None
  */
void TIMER_OC1_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the CH1OCE Bit */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1OCE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpchctlr1 |= TIMER_OCClear;

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  If Clear the OCREF signal on an external event
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_OCClear: new state the Output Compare Clear Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_CLEAR_ENABLE : Output clear enable
  *     @arg TIMER_OC_CLEAR_DISABLE: Output clear disable
  * @retval None
  */
void TIMER_OC2_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear)
{
    uint16_t tmpchctlr1 = 0;

    tmpchctlr1 = TIMERx->CHCTLR1;

    /* Reset the OC2CE Bit */
    tmpchctlr1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH2OCE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpchctlr1 |= (uint16_t)(TIMER_OCClear << 8);

    TIMERx->CHCTLR1 = tmpchctlr1;
}

/**
  * @brief  If Clear the OCREF signal on an external event
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCClear: new state the Output Compare Clear Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_CLEAR_ENABLE : Output clear enable
  *     @arg TIMER_OC_CLEAR_DISABLE: Output clear disable
  * @retval None
  */
void TIMER_OC3_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the CH3OCE Bit */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH3OCE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpchctlr2 |= TIMER_OCClear;

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  If Clear the OCREF signal on an external event
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCClear: new state the Output Compare Clear Enable Bit.
  *   This value will be :
  *     @arg TIMER_OC_CLEAR_ENABLE : Output clear enable
  *     @arg TIMER_OC_CLEAR_DISABLE: Output clear disable
  * @retval None
  */
void TIMER_OC4_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear)
{
    uint16_t tmpchctlr2 = 0;

    tmpchctlr2 = TIMERx->CHCTLR2;

    /* Reset the OC4CE Bit */
    tmpchctlr2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH4OCE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpchctlr2 |= (uint16_t)(TIMER_OCClear << 8);

    TIMERx->CHCTLR2 = tmpchctlr2;
}

/**
  * @brief  Configure the TIMERx channel 1 polarity.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_OCPolarity :
  *   This value will be :
  *     @arg TIMER_OC_POLARITY_HIGH:  active high
  *     @arg TIMER_OC_POLARITY_LOW :  active low
  * @retval None
  */
void TIMER_OC1_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity)
{
    uint16_t tmpche = 0;

    tmpche = TIMERx->CHE;

    /* Configures the CH1P Bit */
    tmpche &= (uint16_t)~((uint16_t)TIMER_CHE_CH1P);
    tmpche |= TIMER_OCPolarity;

    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the TIMERx Channel 1 complementary polarity.
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  TIMER_OCNPolarity:
  *   This value will be :
  *     @arg TIMER_OCN_POLARITY_HIGH:  active high
  *     @arg TIMER_OCN_POLARITY_LOW:  active low
  * @retval None
  */
void TIMER_OC1N_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCNPolarity)
{
    uint16_t tmpche = 0;

    tmpche = TIMERx->CHE;

    /* Configures the CH1NP Bit */
    tmpche &= (uint16_t)~((uint16_t)TIMER_CHE_CH1NP);
    tmpche |= TIMER_OCNPolarity;

    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the TIMERx channel 2 polarity.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_OCPolarity :
  *   This value will be :
  *     @arg TIMER_OC_POLARITY_HIGH:  active high
  *     @arg TIMER_OC_POLARITY_LOW :  active low
  * @retval None
  */
void TIMER_OC2_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity)
{
    uint16_t tmpche = 0;

    tmpche = TIMERx->CHE;

    /* Configure the CH2P Bit */
    tmpche &= (uint16_t)~((uint16_t)TIMER_CHE_CH2P);
    tmpche |= (uint16_t)(TIMER_OCPolarity << 4);

    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the TIMERx Channel 2 complementary polarity.
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  TIMER_OCNPolarity:
  *   This value will be :
  *     @arg TIMER_OCN_POLARITY_HIGH:  active high
  *     @arg TIMER_OCN_POLARITY_LOW:  active low
  * @retval None
  */
void TIMER_OC2N_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCNPolarity)
{
    uint16_t tmpche = 0;

    tmpche = TIMERx->CHE;

    /* Configure the CH2NP Bit */
    tmpche &= (uint16_t)~((uint16_t)TIMER_CHE_CH2NP);
    tmpche |= (uint16_t)(TIMER_OCNPolarity << 4);

    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the TIMERx channel 3 polarity.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCPolarity :
  *   This value will be :
  *     @arg TIMER_OC_POLARITY_HIGH:  active high
  *     @arg TIMER_OC_POLARITY_LOW :  active low
  * @retval None
  */
void TIMER_OC3_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity)
{
    uint16_t tmpche = 0;

    tmpche = TIMERx->CHE;

    /* Configure the CH3P Bit */
    tmpche &= (uint16_t)~((uint16_t)TIMER_CHE_CH3P);
    tmpche |= (uint16_t)(TIMER_OCPolarity << 8);

    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the TIMERx Channel 3 complementary polarity.
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  TIMER_OCNPolarity:
  *   This value will be :
  *     @arg TIMER_OCN_POLARITY_HIGH:  active high
  *     @arg TIMER_OCN_POLARITY_LOW :  active low
  * @retval None
  */
void TIMER_OC3N_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCNPolarity)
{
    uint16_t tmpche = 0;

    tmpche = TIMERx->CHE;

    /* Configure the CH3NP Bit */
    tmpche &= (uint16_t)~((uint16_t)TIMER_CHE_CH3NP);
    tmpche |= (uint16_t)(TIMER_OCNPolarity << 8);

    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the TIMERx channel 4 polarity.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_OCPolarity :
  *   This value will be :
  *     @arg TIMER_OC_POLARITY_HIGH:  active high
  *     @arg TIMER_OC_POLARITY_LOW :  active low
  * @retval None
  */
void TIMER_OC4_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity)
{
    uint16_t tmpche = 0;

    tmpche = TIMERx->CHE;

    /* Configure the CH4P Bit */
    tmpche &= (uint16_t)~((uint16_t)TIMER_CHE_CH4P);
    tmpche |= (uint16_t)(TIMER_OCPolarity << 12);


    TIMERx->CHE = tmpche;
}

/**
  * @brief  Turn-on or off the Channel x Capture or Compare .
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_Ch:
  *   This value will be :
  *     @arg TIMER_CH_1:
  *     @arg TIMER_CH_2:
  *     @arg TIMER_CH_3:
  *     @arg TIMER_CH_4:
  * @param  TIMER_CCx:  the TIMER Channel CCxE bit new value.
  *   This value will be:
  *     @arg TIMER_CCX_ENABLE
  *     @arg TIMER_CCX_DISABLE
  * @retval None
  */
void TIMER_CCxCmd(TIMER_TypeDef *TIMERx, uint16_t TIMER_Ch, uint16_t TIMER_CCx)
{
    uint16_t tmp = 0;

    tmp = CHE_CHE_SET << TIMER_Ch;

    /* Reset the CCx Bit  */
    TIMERx->CHE &= (uint16_t)~ tmp;

    /* Configure the CCx Bit */
    TIMERx->CHE |= (uint16_t)(TIMER_CCx << TIMER_Ch);
}

/**
  * @brief  Turn-on or off the Channel x complementary Capture or Compare
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  TIMER_Ch:
  *   This value will be :
  *     @arg TIMER_CH_1:
  *     @arg TIMER_CH_2:
  *     @arg TIMER_CH_3:
  * @param  TIMER_CCxN: the Channel CCxN bit new value.
  *   This value will be:
  *     @arg TIMER_CCXN_ENABLE
  *     @arg TIMER_CCXN_DISABLE
  * @retval None
  */
void TIMER_CCxNCmd(TIMER_TypeDef *TIMERx, uint16_t TIMER_Ch, uint16_t TIMER_CCxN)
{
    uint16_t tmp = 0;

    tmp = CHE_CHNE_SET << TIMER_Ch;

    /* Reset the CCxN Bit  */
    TIMERx->CHE &= (uint16_t) ~tmp;

    /* Configure the CCxN Bit */
    TIMERx->CHE |= (uint16_t)(TIMER_CCxN << TIMER_Ch);
}

/**
  * @brief  Select control shadow register update control.
  * @param  TIMERx:  x ={ 1, 8 } .
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_SelectCOM(TIMER_TypeDef *TIMERx, TypeState NewValue)
{

    if (NewValue != DISABLE) {
        /* Set the CCUC Bit */
        TIMERx->CTLR2 |= TIMER_CTLR2_CCUC;
    } else {
        /* Reset the CCUC Bit */
        TIMERx->CTLR2 &= (uint16_t)~((uint16_t)TIMER_CTLR2_CCUC);
    }
}

/**
  * @brief  Initialize the Input Capture parameters of the timer
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_ICInit: pointer to a TIMER_ICInitPara structure
  * @retval None
  */
void TIMER_ICInit(TIMER_TypeDef *TIMERx, TIMER_ICInitPara *TIMER_ICInit)
{

    if (TIMER_ICInit->TIMER_CH == TIMER_CH_1) {
        TI1_Config(TIMERx, TIMER_ICInit->TIMER_ICPolarity,
                   TIMER_ICInit->TIMER_ICSelection,
                   TIMER_ICInit->TIMER_ICFilter);

        /* Set the Input Capture Prescaler value */
        TIMER_Set_IC1_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);
    } else if (TIMER_ICInit->TIMER_CH == TIMER_CH_2) {
        TI2_Config(TIMERx, TIMER_ICInit->TIMER_ICPolarity,
                   TIMER_ICInit->TIMER_ICSelection,
                   TIMER_ICInit->TIMER_ICFilter);

        /* Set the Input Capture Prescaler value */
        TIMER_Set_IC2_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);
    } else if (TIMER_ICInit->TIMER_CH == TIMER_CH_3) {
        TI3_Config(TIMERx, TIMER_ICInit->TIMER_ICPolarity,
                   TIMER_ICInit->TIMER_ICSelection,
                   TIMER_ICInit->TIMER_ICFilter);

        /* Set the Input Capture Prescaler value */
        TIMER_Set_IC3_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);
    } else {
        TI4_Config(TIMERx, TIMER_ICInit->TIMER_ICPolarity,
                   TIMER_ICInit->TIMER_ICSelection,
                   TIMER_ICInit->TIMER_ICFilter);

        /* Set the Input Capture Prescaler value */
        TIMER_Set_IC4_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);
    }
}

/**
  * @brief  Fill TIMER_ICInitPara member with default value.
  * @param  TIMER_ICInit : pointer to a TIMER_ICInitPara structure
  * @retval None
  */
void TIMER_ICStructInit(TIMER_ICInitPara *TIMER_ICInit)
{
    TIMER_ICInit->TIMER_CH               = TIMER_CH_1;
    TIMER_ICInit->TIMER_ICPolarity       = TIMER_IC_POLARITY_RISING;
    TIMER_ICInit->TIMER_ICSelection      = TIMER_IC_SELECTION_DIRECTTI;
    TIMER_ICInit->TIMER_ICPrescaler      = TIMER_IC_PSC_DIV1;
    TIMER_ICInit->TIMER_ICFilter         = 0x00;
}

/**
  * @brief  Configure the TIMER PWM input Capture mode parameters
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_ICInit: pointer to a TIMER_ICInitPara structure
  * @retval None
  */
void TIMER_PWMCaptureConfig(TIMER_TypeDef *TIMERx, TIMER_ICInitPara *TIMER_ICInit)
{
    uint16_t icoppositepolarity      = TIMER_IC_POLARITY_RISING;
    uint16_t icoppositeselection     = TIMER_IC_SELECTION_DIRECTTI;

    /* Select the Opposite Input Polarity */
    if (TIMER_ICInit->TIMER_ICPolarity == TIMER_IC_POLARITY_RISING) {
        icoppositepolarity = TIMER_IC_POLARITY_FALLING;
    } else {
        icoppositepolarity = TIMER_IC_POLARITY_RISING;
    }

    /* Select the Opposite Input */
    if (TIMER_ICInit->TIMER_ICSelection == TIMER_IC_SELECTION_DIRECTTI) {
        icoppositeselection = TIMER_IC_SELECTION_INDIRECTTI;
    } else {
        icoppositeselection = TIMER_IC_SELECTION_DIRECTTI;
    }

    if (TIMER_ICInit->TIMER_CH == TIMER_CH_1) {
        TI1_Config(TIMERx, TIMER_ICInit->TIMER_ICPolarity,
                   TIMER_ICInit->TIMER_ICSelection,
                   TIMER_ICInit->TIMER_ICFilter);

        TIMER_Set_IC1_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);

        TI2_Config(TIMERx, icoppositepolarity, icoppositeselection, TIMER_ICInit->TIMER_ICFilter);

        TIMER_Set_IC2_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);
    } else {
        TI2_Config(TIMERx, TIMER_ICInit->TIMER_ICPolarity,
                   TIMER_ICInit->TIMER_ICSelection,
                   TIMER_ICInit->TIMER_ICFilter);

        TIMER_Set_IC2_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);

        TI1_Config(TIMERx, icoppositepolarity, icoppositeselection, TIMER_ICInit->TIMER_ICFilter);

        TIMER_Set_IC1_Prescaler(TIMERx, TIMER_ICInit->TIMER_ICPrescaler);
    }
}

/**
  * @brief  Read the TIMERx Input Capture value.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @retval None
  */
uint32_t TIMER_GetCapture1(TIMER_TypeDef *TIMERx)
{
    return TIMERx->CHCC1;
}

/**
  * @brief  Read the TIMERx Input Capture value.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @retval None
  */
uint32_t TIMER_GetCapture2(TIMER_TypeDef *TIMERx)
{
    return TIMERx->CHCC2;
}

/**
  * @brief  Read the TIMERx Input Capture value.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @retval None
  */
uint32_t TIMER_GetCapture3(TIMER_TypeDef *TIMERx)
{
    return TIMERx->CHCC3;
}

/**
  * @brief  Read the TIMERx Input Capture value.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @retval None
  */
uint32_t TIMER_GetCapture4(TIMER_TypeDef *TIMERx)
{
    return TIMERx->CHCC4;
}

/**
  * @brief  Configure the TIMERx Input Capture prescaler.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14} .
  * @param  TIMER_ICPSC: the Input Capture1 prescaler value.
  *   This value will be :
  *     @arg TIMER_IC_PSC_DIV1: no prescaler
  *     @arg TIMER_IC_PSC_DIV2: divided by 2
  *     @arg TIMER_IC_PSC_DIV4: divided by 4
  *     @arg TIMER_IC_PSC_DIV8: divided by 8
  * @retval None
  */
void TIMER_Set_IC1_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC)
{
    TIMERx->CHCTLR1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1ICP);

    TIMERx->CHCTLR1 |= TIMER_ICPSC;
}

/**
  * @brief  Configure the TIMERx Input Capture prescaler.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_ICPSC: the Input Capture1 prescaler value.
  *   This value will be :
  *     @arg TIMER_IC_PSC_DIV1: no prescaler
  *     @arg TIMER_IC_PSC_DIV2: divided by 2
  *     @arg TIMER_IC_PSC_DIV4: divided by 4
  *     @arg TIMER_IC_PSC_DIV8: divided by 8
  * @retval None
  */
void TIMER_Set_IC2_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC)
{
    TIMERx->CHCTLR1 &= (uint16_t)~((uint16_t)TIMER_CHCTLR1_CH2ICP);

    TIMERx->CHCTLR1 |= (uint16_t)(TIMER_ICPSC << 8);
}

/**
  * @brief  Configure the TIMERx Input Capture prescaler.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_ICPSC: the Input Capture1 prescaler value.
  *   This value will be :
  *     @arg TIMER_IC_PSC_DIV1: no prescaler
  *     @arg TIMER_IC_PSC_DIV2: divided by 2
  *     @arg TIMER_IC_PSC_DIV4: divided by 4
  *     @arg TIMER_IC_PSC_DIV8: divided by 8
  * @retval None
  */
void TIMER_Set_IC3_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC)
{
    TIMERx->CHCTLR2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH3ICP);

    TIMERx->CHCTLR2 |= TIMER_ICPSC;
}

/**
  * @brief  Configure the TIMERx Input Capture prescaler.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_ICPSC: the Input Capture1 prescaler value.
  *   This value will be :
  *     @arg TIMER_IC_PSC_DIV1: no prescaler
  *     @arg TIMER_IC_PSC_DIV2: divided by 2
  *     @arg TIMER_IC_PSC_DIV4: divided by 4
  *     @arg TIMER_IC_PSC_DIV8: divided by 8
  * @retval None
  */
void TIMER_Set_IC4_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC)
{
    TIMERx->CHCTLR2 &= (uint16_t)~((uint16_t)TIMER_CHCTLR2_CH4ICP);

    TIMERx->CHCTLR2 |= (uint16_t)(TIMER_ICPSC << 8);
}

/**
  * @brief  Configure interrupts Enables
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  TIMER_INT:  the interrupts sources to Configure.
  *   This value will be :
  *     @arg TIMER_INT_UPDATE  : update Interrupt
  *     @arg TIMER_INT_CH1     : Channel 1 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH2     : Channel 2 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH3     : Channel 3 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH4     : Channel 4 Capture or Compare Interrupt
  *     @arg TIMER_INT_CCUG    : Commutation Interrupt
  *     @arg TIMER_INT_TRIGGER : Trigger Interrupt
  *     @arg TIMER_INT_BREAK   : Break Interrupt
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_INTConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        TIMERx->DIE |= TIMER_INT;
    } else {
        TIMERx->DIE &= (uint16_t)~TIMER_INT;
    }
}

/**
  * @brief  Generate the software event
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  TIMER_EventSrc:
  *   This value will be :
  *     @arg TIMER_EVENT_SRC_UPDATE  : update Event
  *     @arg TIMER_EVENT_SRC_CH1     : Channel 1 Capture or Compare Event
  *     @arg TIMER_EVENT_SRC_CH2     : Channel 2 Capture or Compare Event
  *     @arg TIMER_EVENT_SRC_CH3     : Channel 3 Capture or Compare Event
  *     @arg TIMER_EVENT_SRC_CH4     : Channel 4 Capture or Compare Event
  *     @arg TIMER_EVENT_SRC_COM     : COM event
  *     @arg TIMER_EVENT_SRC_TRIGGER : Trigger Event
  *     @arg TIMER_EVENT_SRC_BREAK   : Break event
  * @retval None
  */
void TIMER_GenerateEvent(TIMER_TypeDef *TIMERx, uint16_t TIMER_EventSrc)
{
    TIMERx->EVG = TIMER_EventSrc;
}

/**
  * @brief  Get current flag status
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  TIMER_FLAG:
  *   This value will be :
  *     @arg TIMER_FLAG_UPDATE  : update Flag
  *     @arg TIMER_FLAG_CH1     : Channel 1 Capture or Compare Flag
  *     @arg TIMER_FLAG_CH2     : Channel 2 Capture or Compare Flag
  *     @arg TIMER_FLAG_CH3     : Channel 3 Capture or Compare Flag
  *     @arg TIMER_FLAG_CH4     : Channel 4 Capture or Compare Flag
  *     @arg TIMER_FLAG_COM     : Commutation Flag
  *     @arg TIMER_FLAG_TRIGGER : Trigger Flag
  *     @arg TIMER_FLAG_BREAK   : Break Flag
  *     @arg TIMER_FLAG_CH1OF   : Channel 1 Capture or Compare overcapture Flag
  *     @arg TIMER_FLAG_CH2OF   : Channel 2 Capture or Compare overcapture Flag
  *     @arg TIMER_FLAG_CH3OF   : Channel 3 Capture or Compare overcapture Flag
  *     @arg TIMER_FLAG_CH4OF   : Channel 4 Capture or Compare overcapture Flag
  * @retval The state of TIMER_FLAG ( SET or RESET ).
  */
TypeState TIMER_GetBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_FLAG)
{
    if ((TIMERx->STR & TIMER_FLAG) != (uint16_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the flags
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  TIMER_FLAG: the flag bit to clear.
  *   This value will be :
  *     @arg TIMER_FLAG_UPDATE  : update Flag
  *     @arg TIMER_FLAG_CH1     : Channel 1 Capture or Compare Flag
  *     @arg TIMER_FLAG_CH2     : Channel 2 Capture or Compare Flag
  *     @arg TIMER_FLAG_CH3     : Channel 3 Capture or Compare Flag
  *     @arg TIMER_FLAG_CH4     : Channel 4 Capture or Compare Flag
  *     @arg TIMER_FLAG_COM     : Commutation Flag
  *     @arg TIMER_FLAG_TRIGGER : Trigger Flag
  *     @arg TIMER_FLAG_BREAK   : Break Flag
  *     @arg TIMER_FLAG_CH1OF   : Channel 1 Capture or Compare overcapture Flag
  *     @arg TIMER_FLAG_CH2OF   : Channel 2 Capture or Compare overcapture Flag
  *     @arg TIMER_FLAG_CH3OF   : Channel 3 Capture or Compare overcapture Flag
  *     @arg TIMER_FLAG_CH4OF   : Channel 4 Capture or Compare overcapture Flag
  * @retval None
  */
void TIMER_ClearBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_FLAG)
{
    TIMERx->STR = (uint16_t)~TIMER_FLAG;
}

/**
  * @brief  Get interrupt state
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  TIMER_INT:
  *   This value will be :
  *     @arg TIMER_INT_UPDATE: update Interrupt
  *     @arg TIMER_INT_CH1     : Channel 1 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH2     : Channel 2 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH3     : Channel 3 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH4     : Channel 4 Capture or Compare Interrupt
  *     @arg TIMER_INT_CCUG    : Commutation Interrupt
  *     @arg TIMER_INT_TRIGGER : Trigger Interrupt
  *     @arg TIMER_INT_BREAK   : Break Interrupt
  * @retval The new state of the TIMER_INT(SET or RESET).
  */
TypeState TIMER_GetIntBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_INT)
{
    uint16_t TypeState = 0x0, itenable = 0x0;

    TypeState = TIMERx->STR & TIMER_INT;
    itenable = TIMERx->DIE & TIMER_INT;

    if ((TypeState != (uint16_t)RESET) && (itenable != (uint16_t)RESET)) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the interrupt pending bits
  * @param  TIMERx:  x ={ 0-13 } .
  * @param  TIMER_INT:
  *   This value will be :
  *     @arg TIMER_INT_UPDATE: update Interrupt
  *     @arg TIMER_INT_CH1     : Channel 1 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH2     : Channel 2 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH3     : Channel 3 Capture or Compare Interrupt
  *     @arg TIMER_INT_CH4     : Channel 4 Capture or Compare Interrupt
  *     @arg TIMER_INT_CCUG    : Commutation Interrupt
  *     @arg TIMER_INT_TRIGGER : Trigger Interrupt
  *     @arg TIMER_INT_BREAK   : Break Interrupt
  * @retval None
  */
void TIMER_ClearIntBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_INT)
{
    TIMERx->STR = (uint16_t)~TIMER_INT;
}

/**
  * @brief  Configure the DMA .
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_DMABase: DMA Base address.
  *   This value will be :
  *     @arg TIMER_DMA_BASE_ADDR_CTLR1
  *     @arg TIMER_DMA_BASE_ADDR_CTLR2
  *     @arg TIMER_DMA_BASE_ADDR_SMC
  *     @arg TIMER_DMA_BASE_ADDR_DIE
  *     @arg TIMER_DMA_BASE_ADDR_STR
  *     @arg TIMER_DMA_BASE_ADDR_EVG
  *     @arg TIMER_DMA_BASE_ADDR_CHCTLR1
  *     @arg TIMER_DMA_BASE_ADDR_CHCTLR2
  *     @arg TIMER_DMA_BASE_ADDR_CHE
  *     @arg TIMER_DMA_BASE_ADDR_CNT
  *     @arg TIMER_DMA_BASE_ADDR_PSC
  *     @arg TIMER_DMA_BASE_ADDR_CARL
  *     @arg TIMER_DMA_BASE_ADDR_CREP
  *     @arg TIMER_DMA_BASE_ADDR_CHCC1
  *     @arg TIMER_DMA_BASE_ADDR_CHCC2
  *     @arg TIMER_DMA_BASE_ADDR_CHCC3
  *     @arg TIMER_DMA_BASE_ADDR_CHCC4
  *     @arg TIMER_DMA_BASE_ADDR_BKDT
  *     @arg TIMER_DMA_BASE_ADDR_DCTLR
  *     @arg TIMER_DMA_BASE_ADDR_DTRSF
  * @param  TIMER_DMABurstLength: DMA Burst length.
  *     This value will be :
  *            [ TIMER_DMA_BURST_1TRANSFER , TIMER_DMA_BURST_18TRANSFERS ]
  * @retval None
  */
void TIMER_DMAConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_DMABase, uint16_t TIMER_DMABurstLength)
{
    TIMERx->DCTLR = TIMER_DMABase | TIMER_DMABurstLength;
}

/**
  * @brief  Configure the TIMERx's DMA Requests
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 } .
  * @param  TIMER_DMASrc: the DMA Request sources.
  *   This value will be :
  *     @arg TIMER_DMA_UPDATE  : update start DMA
  *     @arg TIMER_DMA_CH1     : Channel 1 Capture or Compare start DMA
  *     @arg TIMER_DMA_CH2     : Channel 2 Capture or Compare start DMA
  *     @arg TIMER_DMA_CH3     : Channel 3 Capture or Compare start DMA
  *     @arg TIMER_DMA_CH4     : Channel 4 Capture or Compare start DMA
  *     @arg TIMER_DMA_COM     : Commutation DMA
  *     @arg TIMER_DMA_TRIGGER : Trigger DMA
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_DMACmd(TIMER_TypeDef *TIMERx, uint16_t TIMER_DMASrc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMA */
        TIMERx->DIE |= TIMER_DMASrc;
    } else {
        /* Disable the DMA */
        TIMERx->DIE &= (uint16_t)~TIMER_DMASrc;
    }
}

/**
  * @brief  Select the Capture or Compare DMA source
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  NewValue: ENABLE or DISABLE
  * @retval None
  */
void TIMER_CC_DMA(TIMER_TypeDef *TIMERx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        TIMERx->CTLR2 |= TIMER_CTLR2_DMAS;
    } else {
        TIMERx->CTLR2 &= (uint16_t)~((uint16_t)TIMER_CTLR2_DMAS);
    }
}

/**
  * @brief  Configure the internal Clock
  * @param  TIMERx: x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 }
  * @retval None
  */
void TIMER_InternalClockConfig(TIMER_TypeDef *TIMERx)
{
    TIMERx->SMC &= (uint16_t)(~((uint16_t)TIMER_SMC_SMC));
}

/**
  * @brief  Configure the Internal Trigger as External Input Clock
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_InputTriSrc:
  *   This value will be :
  *     @arg  TIMER_TS_ITR0 : Internal Trigger 0
  *     @arg  TIMER_TS_ITR1 : Internal Trigger 1
  *     @arg  TIMER_TS_ITR2 : Internal Trigger 2
  *     @arg  TIMER_TS_ITR3 : Internal Trigger 3
  * @retval None
  */
void TIMER_ITRxExtClock(TIMER_TypeDef *TIMERx, uint16_t TIMER_InputTriSrc)
{
    /* Select the Internal Trigger */
    TIMER_SelectInputTrigger(TIMERx, TIMER_InputTriSrc);

    /* Select the External clock mode1 */
    TIMERx->SMC |= TIMER_SLAVE_MODE_EXTERNAL1;
}

/**
  * @brief  Configure the External Trigger as External Input Clock
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_TIxExCLKSrc: Trigger source.
  *   This value will be :
  *     @arg TIMER_TIX_EXCLK1_SRC_TI1ED : TI1 Edge Detector
  *     @arg TIMER_TIX_EXCLK1_SRC_TI1   : Filtered Timer Input 1
  *     @arg TIMER_TIX_EXCLK1_SRC_TI2   : Filtered Timer Input 2
  * @param  TIMER_ICPolarity:
  *   This value will be :
  *     @arg TIMER_IC_POLARITY_RISING
  *     @arg TIMER_IC_POLARITY_FALLING
  * @param  ICFilter: specifies the filter value.
  *   This parameter must be a value between 0x0 and 0xF.
  * @retval None
  */
void TIMER_TIxExtCLkConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_TIxExCLKSrc,
                           uint16_t TIMER_ICPolarity, uint16_t ICFilter)
{
    /* Select the Input Clock Source */
    if (TIMER_TIxExCLKSrc == TIMER_TIX_EXCLK1_SRC_TI2) {
        TI2_Config(TIMERx, TIMER_ICPolarity, TIMER_IC_SELECTION_DIRECTTI, ICFilter);
    } else {
        TI1_Config(TIMERx, TIMER_ICPolarity, TIMER_IC_SELECTION_DIRECTTI, ICFilter);
    }

    /* Select the Trigger source */
    TIMER_SelectInputTrigger(TIMERx, TIMER_TIxExCLKSrc);

    /* Enter the External clock mode1 */
    TIMERx->SMC |= TIMER_SLAVE_MODE_EXTERNAL1;
}

/**
  * @brief  Configure the External clock Mode1
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8  } .
  * @param  TIMER_ExtTriPrescaler: The external Trigger Prescaler.
  *   This value will be :
  *     @arg TIMER_EXT_TRI_PSC_OFF: no divided.
  *     @arg TIMER_EXT_TRI_PSC_DIV2: divided by 2.
  *     @arg TIMER_EXT_TRI_PSC_DIV4: divided by 4.
  *     @arg TIMER_EXT_TRI_PSC_DIV8: divided by 8.
  * @param  TIMER_ExtTriPolarity:  Trigger Polarity.
  *   This value will be :
  *     @arg TIMER_EXT_TRI_POLARITY_INVERTED   : active low or falling edge active.
  *     @arg TIMER_EXT_TRI_POLARITY_NONINVERTED: active high or rising edge active.
  * @param  ExtTriFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIMER_ETRClockMode1Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ExTriPrescaler, uint16_t TIMER_ExTriPolarity,
                               uint16_t ExtTriFilter)
{
    uint16_t tmpsmc = 0;

    /* Configure the external Trigger  Clock source */
    TIMER_ETRConfig(TIMERx, TIMER_ExTriPrescaler, TIMER_ExTriPolarity, ExtTriFilter);

    /* Get the TIMERx SMC register value */
    tmpsmc = TIMERx->SMC;

    tmpsmc &= (uint16_t)(~((uint16_t)TIMER_SMC_SMC));

    /* Select the External clock mode1 */
    tmpsmc |= TIMER_SLAVE_MODE_EXTERNAL1;

    /* Select the Trigger selection : ETRF */
    tmpsmc &= (uint16_t)(~((uint16_t)TIMER_SMC_TRGS));
    tmpsmc |= TIMER_TS_ETRF;

    TIMERx->SMC = tmpsmc;
}

/**
  * @brief  Configure the External clock Mode2
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_ExtTriPrescaler: The external Trigger Prescaler.
  *   This value will be :
  *     @arg TIMER_EXT_TRI_PSC_OFF: no divided.
  *     @arg TIMER_EXT_TRI_PSC_DIV2: divided by 2.
  *     @arg TIMER_EXT_TRI_PSC_DIV4: divided by 4.
  *     @arg TIMER_EXT_TRI_PSC_DIV8: divided by 8.
  * @param  TIMER_ExtTriPolarity:  Trigger Polarity.
  *   This value will be :
  *     @arg TIMER_EXT_TRI_POLARITY_INVERTED   : active low or falling edge active.
  *     @arg TIMER_EXT_TRI_POLARITY_NONINVERTED: active high or rising edge active.
  * @param  ExtTriFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIMER_ETRClockMode2Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ExTriPrescaler,
                               uint16_t TIMER_ExTriPolarity, uint16_t ExtTriFilter)
{
    /* Configure the ETR Clock source */
    TIMER_ETRConfig(TIMERx, TIMER_ExTriPrescaler, TIMER_ExTriPolarity, ExtTriFilter);

    /* Select the External clock mode2 */
    TIMERx->SMC |= TIMER_SMC_ECM2E;
}

/**
  * @brief  Select the Input Trigger source
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_InputTriSrc: The Input Trigger source.
  *   This value will be :
  *     @arg TIMER_TS_ITR0    : Internal Trigger 0
  *     @arg TIMER_TS_ITR1    : Internal Trigger 1
  *     @arg TIMER_TS_ITR2    : Internal Trigger 2
  *     @arg TIMER_TS_ITR3    : Internal Trigger 3
  *     @arg TIMER_TS_TI1F_ED : TI1 Edge Detector
  *     @arg TIMER_TS_TI1FP1  : Filtered Timer Input 1
  *     @arg TIMER_TS_TI2FP2  : Filtered Timer Input 2
  *     @arg TIMER_TS_ETRF    : External Trigger input
  * @retval None
  */
void TIMER_SelectInputTrigger(TIMER_TypeDef *TIMERx, uint16_t TIMER_InputTriSrc)
{
    uint16_t tmpsmc = 0;

    tmpsmc = TIMERx->SMC;

    /* Reset the TS Bits */
    tmpsmc &= (uint16_t)(~((uint16_t)TIMER_SMC_TRGS));

    /* Set the Input Trigger source */
    tmpsmc |= TIMER_InputTriSrc ;

    TIMERx->SMC = tmpsmc;
}

/**
  * @brief  Configure the TIMERx Trigger Output Mode.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 ,10 , 11 , 13 , 14} .
  * @param  TIMER_TriOutSrc:
  *   This value will be :
  *     @arg TIMER_TRI_OUT_SRC_RESET  : The UPG bit in the TIMERx_EVG register as TriO.
  *     @arg TIMER_TRI_OUT_SRC_ENABLE : The CEN bit in TIMERx_CTLR1 as TriO.
  *     @arg TIMER_TRI_OUT_SRC_UPDATE : Update event as TriO.
  *     @arg TIMER_TRI_OUT_SRC_OC1    : capture or compare match ( CC1IF bit set ) as TriO.
  *     @arg TIMER_TRI_OUT_SRC_OC1REF : OC1REF as TriO.
  *     @arg TIMER_TRI_OUT_SRC_OC2REF : OC2REF as TriO.
  *     @arg TIMER_TRI_OUT_SRC_OC3REF : OC3REF as TriO.
  *     @arg TIMER_TRI_OUT_SRC_OC4REF : OC4REF as TriO.
  * @retval None
  */
void TIMER_SelectOutputTrigger(TIMER_TypeDef *TIMERx, uint16_t TIMER_TriOutSrc)
{
    /* Reset the MMC Bits */
    TIMERx->CTLR2 &= (uint16_t)~((uint16_t)TIMER_CTLR2_MMC);

    /* Configures the TriO source */
    TIMERx->CTLR2 |=  TIMER_TriOutSrc;
}

/**
  * @brief  Configure the TIMERx Slave Mode
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_SlaveMode:
  *   This value will be :
  *     @arg TIMER_SLAVE_MODE_RESET     : The trigger signal reset the timer
  *     @arg TIMER_SLAVE_MODE_GATED     : The trigger signal enable the counter when high.
  *     @arg TIMER_SLAVE_MODE_TRIGGER   : The trigger signal starts the counter.
  *     @arg TIMER_SLAVE_MODE_EXTERNAL1 : The trigger signal as a counter clock.
  * @retval None
  */
void TIMER_SelectSlaveMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_SlaveMode)
{
    /* Reset the SMC Bits */
    TIMERx->SMC &= (uint16_t)~((uint16_t)TIMER_SMC_SMC);

    /* Configure the Slave Mode */
    TIMERx->SMC |= TIMER_SlaveMode;
}

/**
  * @brief  Configure the TIMERx Master or Slave Mode
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 10 , 11 , 13 , 14} .
  * @param  TIMER_MasterSlaveMode:
  *   This value will be :
  *     @arg TIMER_MASTER_SLAVE_MODE_ENABLE  : synchronize master and slave by TriO
  *     @arg TIMER_MASTER_SLAVE_MODE_DISABLE : Don't synchronize
  * @retval None
  */
void TIMER_SelectMasterSlaveMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_MasterSlaveMode)
{
    /* Reset the MSM Bit */
    TIMERx->SMC &= (uint16_t)~((uint16_t)TIMER_SMC_MSM);

    /* Configure the MSM Bit */
    TIMERx->SMC |= TIMER_MasterSlaveMode;
}

/**
  * @brief  Configure the External Trigger (ETR)
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_ExTriPrescaler: external Trigger Prescaler.
  *   This value will be :
  *     @arg TIMER_EXT_TRI_PSC_OFF : no divided.
  *     @arg TIMER_EXT_TRI_PSC_DIV2: divided by 2.
  *     @arg TIMER_EXT_TRI_PSC_DIV4: divided by 4.
  *     @arg TIMER_EXT_TRI_PSC_DIV8: divided by 8.
  * @param  TIMER_ExtTriPolarity:  Trigger Polarity.
  *   This value will be :
  *     @arg TIMER_EXT_TRI_POLARITY_INVERTED   : active low or falling edge active.
  *     @arg TIMER_EXT_TRI_POLARITY_NONINVERTED: active high or rising edge active.
  * @param  ExtTRGFilter: The External Trigger signal Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIMER_ETRConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_ExTriPrescaler, uint16_t TIMER_ExTriPolarity,
                     uint16_t ExtTriFilter)
{
    uint16_t tmpsmc = 0;

    tmpsmc = TIMERx->SMC;

    /*Reset the ETR Bits */
    tmpsmc &= SMC_ETR_MASK;

    /* Configure the Prescaler, the Filter value and the Polarity */
    tmpsmc |= (uint16_t)(TIMER_ExTriPrescaler | (uint16_t)(TIMER_ExTriPolarity | (uint16_t)(ExtTriFilter << (uint16_t)8)));

    TIMERx->SMC = tmpsmc;
}

/**
  * @brief  Configure the Encoder Interface.
  * @param  TIMERx:  x ={ 1 , 8 , 9 , 12 } .
  * @param  TIMER_EncoderMode:
  *   This value will be :
  *     @arg TIMER_ENCODER_MODE_TI1  : Counter counts on TI1FP1 edge depending on TI2FP2 level.
  *     @arg TIMER_ENCODER_MODE_TI2  : Counter counts on TI2FP2 edge depending on TI1FP1 level.
  *     @arg TIMER_ENCODER_MODE_TI12 : Counter counts on both TI1FP1 and TI2FP2 edges depending
  *                                    on the level of the other input.
  * @param  TIMER_IC1Polarity: input capture 1 Polarity
  *   This value will be :
  *     @arg TIMER_IC_POLARITY_FALLING : capture Falling edge.
  *     @arg TIMER_IC_POLARITY_RISING  : capture  Rising edge.
  * @param  TIMER_IC2Polarity: input capture 2 Polarity
  *   This value will be :
  *     @arg TIMER_IC_POLARITY_FALLING : capture Falling edge.
  *     @arg TIMER_IC_POLARITY_RISING  : capture  Rising edge.
  * @retval None
  */
void TIMER_EncoderInterfaceConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_EncoderMode,
                                  uint16_t TIMER_IC1Polarity, uint16_t TIMER_IC2Polarity)
{
    uint16_t tmpsmc     = 0;
    uint16_t tmpchctlr1 = 0;
    uint16_t tmpche     = 0;

    tmpsmc = TIMERx->SMC;

    tmpchctlr1 = TIMERx->CHCTLR1;

    tmpche = TIMERx->CHE;

    /* select the encoder Mode */
    tmpsmc &= (uint16_t)(~((uint16_t)TIMER_SMC_SMC));
    tmpsmc |= TIMER_EncoderMode;

    tmpchctlr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1M)) & (uint16_t)(~((uint16_t)TIMER_CHCTLR1_CH2M)));
    tmpchctlr1 |= TIMER_CHCTLR1_CH1M_0 | TIMER_CHCTLR1_CH2M_0;

    /* select the TI1 and the TI2 Polarities*/
    tmpche &= (uint16_t)~((uint16_t)(TIMER_CHE_CH1P | TIMER_CHE_CH1NP)) & (uint16_t)~((uint16_t)(TIMER_CHE_CH2P | TIMER_CHE_CH2NP));
    tmpche |= (uint16_t)(TIMER_IC1Polarity | (uint16_t)(TIMER_IC2Polarity << (uint16_t)4));

    TIMERx->SMC = tmpsmc;

    TIMERx->CHCTLR1 = tmpchctlr1;

    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the Hall sensor interface
  * @param  TIMERx:  x ={ 1 , 8 } .
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_SelectHallSensor(TIMER_TypeDef *TIMERx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        TIMERx->CTLR2 |= TIMER_CTLR2_TI1S;
    } else {
        TIMERx->CTLR2 &= (uint16_t)~((uint16_t)TIMER_CTLR2_TI1S);
    }
}

/* Private functions */
/**
  * @brief  Configure the TI1 as Capture Input.
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 10 , 11 , 12 , 13 , 14}  .
  * @param  TIMER_ICPolarity: Input Capture Polarity.
  *   This value will be :
  *     @arg TIMER_IC_POLARITY_RISING  : Capture rising edge
  *     @arg TIMER_IC_POLARITY_FALLING : Capture falling edge
  * @param  TIMER_ICSelection: Input Capture source.
  *   This value will be :
  *     @arg TIMER_IC_SELECTION_DIRECTTI   : connected to IC1.
  *     @arg TIMER_IC_SELECTION_INDIRECTTI : connected to IC2.
  *     @arg TIMER_IC_SELECTION_TRC        : connected to TRC.
  * @param  TIMER_ICFilter:  Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter)
{
    uint16_t tmpchctlr1 = 0, tmpche = 0;

    /* Disable the Channel 1 */
    TIMERx->CHE &= (uint16_t)~((uint16_t)TIMER_CHE_CH1E);
    tmpchctlr1 = TIMERx->CHCTLR1;
    tmpche = TIMERx->CHE;

    /* Select the Input and Configure the filter */
    tmpchctlr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1M)) & ((uint16_t)~((uint16_t)TIMER_CHCTLR1_CH1ICF)));
    tmpchctlr1 |= (uint16_t)(TIMER_ICSelection | (uint16_t)(TIMER_ICFilter << (uint16_t)4));

    /* Configure the Polarity and channel enable Bit */
    tmpche &= (uint16_t)~((uint16_t)(TIMER_CHE_CH1P | TIMER_CHE_CH1NP));
    tmpche |= (uint16_t)(TIMER_ICPolarity | (uint16_t)TIMER_CHE_CH1E);

    TIMERx->CHCTLR1 = tmpchctlr1;
    TIMERx->CHE = tmpche;
}

/**
  * @brief  Configure the TI2 as Capture Input.
  * @note   None
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 , 9 , 12 } .
  * @param  TIMER_ICPolarity:  Input Capture Polarity.
  *   This value will be :
  *     @arg TIMER_IC_POLARITY_RISING  : Capture rising edge
  *     @arg TIMER_IC_POLARITY_FALLING : Capture falling edge
  * @param  TIMER_ICSelection:  Input Capture source.
  *   This value will be :
  *     @arg TIMER_IC_SELECTION_DIRECTTI   : connected to IC2.
  *     @arg TIMER_IC_SELECTION_INDIRECTTI : connected to IC1.
  *     @arg TIMER_IC_SELECTION_TRC        : connected to TRC.
  * @param  TIMER_ICFilter:  Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter)
{
    uint16_t tmpchctlr1 = 0, tmpche = 0, tmp = 0;

    /* Disable the Channel 2 */
    TIMERx->CHE &= (uint16_t)~((uint16_t)TIMER_CHE_CH2E);
    tmpchctlr1 = TIMERx->CHCTLR1;
    tmpche     = TIMERx->CHE;
    tmp        = (uint16_t)(TIMER_ICPolarity << 4);

    /* Select the Input and Configure the filter */
    tmpchctlr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIMER_CHCTLR1_CH2M)) & ((uint16_t)~((uint16_t)TIMER_CHCTLR1_CH2ICF)));
    tmpchctlr1 |= (uint16_t)(TIMER_ICFilter << 12);
    tmpchctlr1 |= (uint16_t)(TIMER_ICSelection << 8);

    /* Configure the Polarity and channel enable Bit */
    tmpche &= (uint16_t)~((uint16_t)(TIMER_CHE_CH2P | TIMER_CHE_CH2NP));
    tmpche |= (uint16_t)(tmp | (uint16_t)TIMER_CHE_CH2E);

    TIMERx->CHCTLR1 = tmpchctlr1 ;
    TIMERx->CHE     = tmpche;
}

/**
  * @brief  Configure the TI3 as Capture Input
  * @note   None
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_ICPolarity:  Input Capture Polarity.
  *   This value will be :
  *     @arg TIMER_IC_POLARITY_RISING  : Capture rising edge
  *     @arg TIMER_IC_POLARITY_FALLING : Capture falling edge
  * @param  TIMER_ICSelection:  Input Capture source.
  *   This value will be :
  *     @arg TIMER_IC_SELECTION_DIRECTTI   : connected to IC3.
  *     @arg TIMER_IC_SELECTION_INDIRECTTI : connected to IC4.
  *     @arg TIMER_IC_SELECTION_TRC        : connected to TRC.
  * @param  TIMER_ICFilter:  Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI3_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter)
{
    uint16_t tmpchctlr2 = 0, tmpche = 0, tmp = 0;

    /* Disable the Channel 3 */
    TIMERx->CHE &= (uint16_t)~((uint16_t)TIMER_CHE_CH3E);
    tmpchctlr2 = TIMERx->CHCTLR2;
    tmpche = TIMERx->CHE;
    tmp = (uint16_t)(TIMER_ICPolarity << 8);

    /* Select the Input and Configure the filter */
    tmpchctlr2 &= (uint16_t)(((uint16_t)~((uint16_t)TIMER_CHCTLR2_CH3M)) & ((uint16_t)~((uint16_t)TIMER_CHCTLR2_CH3ICF)));
    tmpchctlr2 |= (uint16_t)(TIMER_ICSelection | (uint16_t)(TIMER_ICFilter << (uint16_t)4));

    /* Configure the Polarity and channel enable Bit */
    tmpche &= (uint16_t)~((uint16_t)(TIMER_CHE_CH3P | TIMER_CHE_CH3NP));
    tmpche |= (uint16_t)(tmp | (uint16_t)TIMER_CHE_CH3E);

    TIMERx->CHCTLR2 = tmpchctlr2;
    TIMERx->CHE     = tmpche;
}

/**
  * @brief  Configure the TI4 as Capture Input
  * @param  TIMERx:  x ={ 1 , 2 , 3 , 4 , 5 , 8 } .
  * @param  TIMER_ICPolarity:  Input Capture Polarity.
  *   This value will be :
  *     @arg TIMER_IC_POLARITY_RISING  : Capture rising edge
  *     @arg TIMER_IC_POLARITY_FALLING : Capture falling edge
  * @param  TIMER_ICSelection:  Input Capture source.
  *   This value will be :
  *     @arg TIMER_IC_SELECTION_DIRECTTI   : connected to IC4.
  *     @arg TIMER_IC_SELECTION_INDIRECTTI : connected to IC3.
  *     @arg TIMER_IC_SELECTION_TRC        : connected to TRC.
  * @param  TIMER_ICFilter:  Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI4_Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPolarity, uint16_t TIMER_ICSelection,
                       uint16_t TIMER_ICFilter)
{
    uint16_t tmpchctlr2 = 0, tmpche = 0, tmp = 0;

    /* Disable the Channel 4 */
    TIMERx->CHE &= (uint16_t)~((uint16_t)TIMER_CHE_CH4E);
    tmpchctlr2 = TIMERx->CHCTLR2;
    tmpche = TIMERx->CHE;
    tmp = (uint16_t)(TIMER_ICPolarity << 12);

    /* Select the Input and Configure the filter */
    tmpchctlr2 &= (uint16_t)((uint16_t)(~(uint16_t)TIMER_CHCTLR2_CH4M) & ((uint16_t)~((uint16_t)TIMER_CHCTLR2_CH4ICF)));
    tmpchctlr2 |= (uint16_t)(TIMER_ICSelection << 8);
    tmpchctlr2 |= (uint16_t)(TIMER_ICFilter << 12);

    /* Configure the Polarity and channel enable Bit */
    tmpche &= (uint16_t)~((uint16_t)(TIMER_CHE_CH4P | TIMER_CHE_CH4NP));
    tmpche &= (uint16_t)~((uint16_t)(TIMER_CHE_CH4P));
    tmpche |= (uint16_t)(tmp | (uint16_t)TIMER_CHE_CH4E);

    TIMERx->CHCTLR2 = tmpchctlr2;
    TIMERx->CHE = tmpche;
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

