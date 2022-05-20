/*
  ******************************************************************************
  * @file    HAL_TKEY.c
  * @version V1.0.0
  * @date    2020
  * @brief   DMA HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Direct Memory Access (DMA) peripheral:
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

__IO uint32_t u32Regbackup;

/************************************************************************
 * function   : TKEY_IRQHandler
 * Description: tkey interrupt service routine.
 * input :
 *         none
 * return: none
 ************************************************************************/
void TKEY_IRQHandler(void)
{
    TKEY->ISR = 0xFFF;
}

/************************************************************************
 * function   : HAL_TKEY_MspInit
 * Description: Init the hardware, GPIO and clock, etc.
 * input      : htkey : TKEY handle
 * return     : none
 ************************************************************************/
void HAL_TKEY_MspInit(TKEY_HandleTypeDef* htkey)
{
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle;
    uint8_t ucI;

    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /* TKEY0 GPIO inition*/
        if(htkey->ChannelData[ucI].ChannelId < 4)             /*TKEY0-3 -> PA10-13*/
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 10));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOA, &GPIO_Handle);
        }

        if((htkey->ChannelData[ucI].ChannelId >= 4)&&(htkey->ChannelData[ucI].ChannelId <= 5))          /*TKEY4-5 -> PD6-7*/
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 2));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOD, &GPIO_Handle);
        }

        if((htkey->ChannelData[ucI].ChannelId >= 6)&&(htkey->ChannelData[ucI].ChannelId <= 7))          /*TKEY6-7 -> PA14-15*/
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 8));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOA, &GPIO_Handle);
        }

        if((htkey->ChannelData[ucI].ChannelId >= 8)&&(htkey->ChannelData[ucI].ChannelId <= 10))          /*TKEY8-10 -> PC10-12*/
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 2));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOC, &GPIO_Handle);
        }

        if(htkey->ChannelData[ucI].ChannelId == 11)          /*TKEY11 -> PD2*/
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId - 9));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOD, &GPIO_Handle);
        }

        if((htkey->ChannelData[ucI].ChannelId >= 12)&&(htkey->ChannelData[ucI].ChannelId <= 15))          /*TKEY12-15 -> PB3-6*/
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId - 9));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOB, &GPIO_Handle);
        }
    }

    if(htkey->Init.ShieldEn == TKEY_CR_SCAN_ENABLE)  /*TKEY_SHIELD -> PB7*/
    {
        GPIO_Handle.Pin            = GPIO_PIN_7;
        GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
        GPIO_Handle.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_Handle);
    }

    /*Set the Cs(PB9) and Creg(PB8) pin to analog*/
    GPIO_Handle.Pin            = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
    GPIO_Handle.Pull           = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_Handle);

    SCU->RCHCR |= ((15 << 17) | SCU_RCHCR_RC4M_EN); //RC4M TRIM and Enable.
    while((SCU->RCHCR & SCU_RCHCR_RC4MRDY) == 0x00);
    SCU->CCR2 |= SCU_CCR2_TKSCLK_SEL;  //TKEY use the RC4M as clock.

    System_Enable_RC32K(); //RC32K Enable.

    System_Module_Reset(RST_TKEY);

    /* Enable TKEY Clock */
    System_Module_Enable(EN_TKEY);

    /* Disable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_DisableIRQ(TKEY_IRQn);
}

/************************************************************************
 * function   : HAL_TKEY_Start
 * Description: TKEY start to scan
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Start(TKEY_HandleTypeDef* htkey)
{
    /* Check the parameters */
    if(!IS_TKEY_ALL_INSTANCE(htkey->Instance)) return HAL_ERROR;
    /*Enable the Tkey scan*/
    SET_BIT(htkey->Instance->CR , TKEY_CR_SCAN);

    /*Start the Tkey scan*/
    SET_BIT(htkey->Instance->CR, TKEY_CR_START);

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_Stop
 * Description: TKEY stop the scan
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Stop(TKEY_HandleTypeDef* htkey)
{
    /* Check the parameters */
    if(!IS_TKEY_ALL_INSTANCE(htkey->Instance)) return HAL_ERROR;

    /*Check if the Tkey scan is busy*/
    while(READ_BIT(htkey->Instance->ISR , TKEY_ISR_BUSY)){}

    /*disable the Tkey scan*/
    CLEAR_BIT(htkey->Instance->CR, TKEY_CR_SCAN);

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_Suspend
 * Description: Set the sleep parameters.
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Suspend(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    __IO uint32_t *gu32RegTemp;

    /* Check the parameters */
    if(!IS_TKEY_ALL_INSTANCE(htkey->Instance)) return HAL_ERROR;

    /* Disable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_DisableIRQ(TKEY_IRQn);

    u32Regbackup = htkey->Instance->SMPR;
    MODIFY_REG(htkey->Instance->SMPR, TKEY_SMPR_SWT_MASK, TKEY_SMPR_SWT(htkey->ScanPara.SleepScanWaitTime));   //Slow down the scan speed.

    SET_BIT(htkey->Instance->CR, TKEY_CR_SLEEP);      //Enable the wakeup.

    SET_BIT(htkey->Instance->IER, TKEY_IER_WAKEUPIE); //Enable the wakeup interrupt.

    gu32RegTemp = &htkey->Instance->CH0;
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /* Write the base data and the wakeup threshold.*/
        *(gu32RegTemp + htkey->ChannelData[ucI].ChannelId) = htkey->ChannelData[ucI].Tkey_Data->Data;
        *(gu32RegTemp - 16 + htkey->ChannelData[ucI].ChannelId) = htkey->ChannelData[ucI].Tkey_RefPara->RefDelta*htkey->ScanPara.WakeUpThRatio;
    }

    /* Enable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_EnableIRQ(TKEY_IRQn);

    /*Start the Tkey scan*/
    SET_BIT(htkey->Instance->CR, TKEY_CR_START);

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_Resume
 * Description: Resume the wakeup parameters.
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Resume(TKEY_HandleTypeDef* htkey)
{
    /* Disable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_DisableIRQ(TKEY_IRQn);

    CLEAR_BIT(htkey->Instance->IER, TKEY_IER_WAKEUPIE); //Disable the wakeup interrupt.

    htkey->Instance->SMPR = u32Regbackup;     //Use the backup scan value.
    CLEAR_BIT(htkey->Instance->CR, TKEY_CR_SLEEP);      //Disable the wakeup.

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_ReadNr
 * Description: Read the count number of the Cr.
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_ReadNr(TKEY_HandleTypeDef* htkey)
{
    HAL_StatusTypeDef Status = HAL_OK;
    /* Check the parameters */
    if(!IS_TKEY_ALL_INSTANCE(htkey->Instance)) return HAL_ERROR;

    /*Check if the Tkey scan is busy*/
    while(READ_BIT(htkey->Instance->ISR , TKEY_ISR_BUSY)){}

    /*Set the CREN, enabel the internal channel scan*/
    SET_BIT(htkey->Instance->CR, TKEY_CR_CREN);

    /*Clear the SLEEP, use normal scan mode*/
    CLEAR_BIT(htkey->Instance->CR, TKEY_CR_SLEEP);

    /* Clear all flag */
    htkey->Instance->ISR = 0x07;
    HAL_TKEY_Start(htkey);

    while(!READ_BIT(htkey->Instance->ISR, TKEY_ISR_EOC))
    {
        if(!READ_BIT(htkey->Instance->ISR, TKEY_ISR_BUSY)) //Some times will stop.restart.
            SET_BIT(htkey->Instance->CR, TKEY_CR_START);

        if(READ_BIT(htkey->Instance->ISR, TKEY_ISR_TIMEOUT))
        {
            SET_BIT(htkey->Instance->ISR, TKEY_ISR_TIMEOUT); //Clear the timeout flag
            Status = HAL_ERROR;
            break;
        }
    }

    htkey->Instance->ISR = TKEY_ISR_EOC;

    htkey->NrData = htkey->Instance->DR;

    return Status;
}

/************************************************************************
 * function   : HAL_TKEY_ReadChannelData
 * Description: Read the count number of the all channels.
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_ReadChannelData(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    __IO uint32_t *gu32RegTemp;

    htkey->Instance->ISR = 0x07;
    if(!(htkey->Instance->CR & TKEY_CR_CONT))
    {
        /*Start the Tkey scan*/
        SET_BIT(htkey->Instance->CR, TKEY_CR_START);
    }

    while(!READ_BIT(htkey->Instance->ISR, TKEY_ISR_EOC))
    {
        if(!READ_BIT(htkey->Instance->ISR, TKEY_ISR_BUSY)) //Some times will stop.restart.
            SET_BIT(htkey->Instance->CR, TKEY_CR_START);

        if(READ_BIT(htkey->Instance->ISR, TKEY_ISR_TIMEOUT))
        {
            SET_BIT(htkey->Instance->ISR, TKEY_ISR_TIMEOUT); //Clear the timeout flag
            return HAL_ERROR;
        }
    }

    htkey->Instance->ISR = TKEY_ISR_EOC;

    gu32RegTemp = &htkey->Instance->CH0;
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /* Read the data and calculate the delta.*/
        htkey->ChannelData[ucI].Tkey_Data->Data = *(gu32RegTemp + htkey->ChannelData[ucI].ChannelId);
        htkey->ChannelData[ucI].Tkey_Data->Delta = (INT32)htkey->ChannelData[ucI].Tkey_Data->RefData - (INT32)htkey->ChannelData[ucI].Tkey_Data->Data;
    }

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_ReadAllNx
 * Description: Read the count number of the all channels first time, and start the scan.
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_ReadAllNx(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;

    /* Check the parameters */
    if(!IS_TKEY_ALL_INSTANCE(htkey->Instance)) return HAL_ERROR;

    /*Clear the CREN, disable the internal channel scan*/
    CLEAR_BIT(htkey->Instance->CR, TKEY_CR_CREN);

    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /*Enable the channels*/
        htkey->Instance->CXSELR |= (1<<htkey->ChannelData[ucI].ChannelId);
        /*If the channel need compensation*/
        if(htkey->ChannelData[ucI].Tkey_RefPara->CrSelect)
            htkey->Instance->CRSELR |= (1<<htkey->ChannelData[ucI].ChannelId);
    }
    /*Clear the SLEEP, use normal scan mode*/
    CLEAR_BIT(htkey->Instance->CR, TKEY_CR_SLEEP);

    HAL_TKEY_Start(htkey);

    HAL_TKEY_ReadChannelData(htkey);

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_StartUpStateProcess
 * Description: Init the TKEY channel data.
 * input      : ChannelData : TKEY channel data handle point to TKEY_ChannelDataDef.
 * return     : None
 ************************************************************************/
void HAL_TKEY_StartUpStateProcess(const TKEY_ChannelDataDef *ChannelData)
{
    ChannelData->Tkey_Data->DebIn = ChannelData->Tkey_RefPara->DebIn;
    ChannelData->Tkey_Data->DebOut = ChannelData->Tkey_RefPara->DebOut;
    ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
}

/************************************************************************
 * function   : HAL_TKEY_DebDetectStateProcess
 * Description: The TKEY detect action state process.
 * input      : ChannelData : TKEY channel data handle point to TKEY_ChannelDataDef.
 * return     : None
 ************************************************************************/
void HAL_TKEY_DebDetectStateProcess(const TKEY_ChannelDataDef *ChannelData)
{
    if (ChannelData->Tkey_Data->Delta >= ChannelData->Tkey_RefPara->DetectInTH)
    {
        if (ChannelData->Tkey_Data->DebIn > 0)
        {
            ChannelData->Tkey_Data->DebIn--;
        }
        if (ChannelData->Tkey_Data->DebIn == 0)
        {
            ChannelData->Tkey_Data->StateId = TKEY_STATEID_DETECT;
            ChannelData->Tkey_Data->DebOut = ChannelData->Tkey_RefPara->DebOut;
        }
      // else stay in Debounce Detect
    }
    else
    {
        ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
        ChannelData->Tkey_Data->DebIn = ChannelData->Tkey_RefPara->DebIn;
    }
}

/************************************************************************
 * function   : HAL_TKEY_DebReleaseDetectStateProcess
 * Description: The TKEY detect to release state process.
 * input      : ChannelData : TKEY channel data handle point to TKEY_ChannelDataDef.
 * return     : None
 ************************************************************************/
void HAL_TKEY_DebReleaseDetectStateProcess(const TKEY_ChannelDataDef *ChannelData)
{
    if (ChannelData->Tkey_Data->Delta >= ChannelData->Tkey_RefPara->DetectOutTH)
    {
        ChannelData->Tkey_Data->StateId = TKEY_STATEID_DETECT;
        ChannelData->Tkey_Data->DebOut = ChannelData->Tkey_RefPara->DebOut;
    }
    else
    {
        if (ChannelData->Tkey_Data->DebOut > 0)
        {
            ChannelData->Tkey_Data->DebOut--;
        }
        if (ChannelData->Tkey_Data->DebOut == 0)
        {
            ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
            ChannelData->Tkey_Data->DebIn = ChannelData->Tkey_RefPara->DebIn;
        }
    }
}

/************************************************************************
 * function   : HAL_TKEY_Init
 * Description: Init the TKEY.
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Init(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    uint32_t u32RegTemp;

    /* Check the TKEY handle allocation */
    if (htkey == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if(!IS_TKEY_ALL_INSTANCE(htkey->Instance)) return HAL_ERROR;
    if(!IS_TKEY_ALL_VKEYSEL(htkey->Init.VkeySel)) return HAL_ERROR;
    if(!IS_TKEY_ALL_VREFSEL(htkey->Init.VrefSel)) return HAL_ERROR;
    if(!IS_TKEY_ALL_SHIELDEN(htkey->Init.ShieldEn)) return HAL_ERROR;
    if(!IS_TKEY_ALL_SCANWAITTIME(htkey->Init.ScanWaitTime)) return HAL_ERROR;
    if(!IS_TKEY_ALL_CSDISCHARGETIME(htkey->Init.CsDisChargeTime)) return HAL_ERROR;
    if(!IS_TKEY_ALL_SW1(htkey->Init.Sw1H)) return HAL_ERROR;
    if(!IS_TKEY_ALL_SW1(htkey->Init.Sw1L)) return HAL_ERROR;

    /* Init the low level hardware : GPIO, CLOCK, NVIC, DMA */
    HAL_TKEY_MspInit(htkey);

    /*Check if the Tkey scan is busy*/
    while(READ_BIT(htkey->Instance->ISR , TKEY_ISR_BUSY)){}

    HAL_TKEY_Stop(htkey);

    /*Config the Tkey control register*/
    u32RegTemp =  ((TKEY_CR_CHARGESEL_LDO << 11)& TKEY_CR_CHARGESEL) | \
                  (TKEY_CR_VKEYSEL(htkey->Init.VkeySel) & TKEY_CR_VKEYSEL_MASK) | \
                  (TKEY_CR_VREFSEL(htkey->Init.VrefSel) & TKEY_CR_VREFSEL_MASK) | \
                  ((TKEY_CR_SPREAD_DISABLE << 5)& TKEY_CR_SPREAD) | \
                  ((TKEY_CR_CONT_ENABLE << 4)& TKEY_CR_CONT) | \
                  ((htkey->Init.ShieldEn << 3)& TKEY_CR_SHIELDEN);

    WRITE_REG(htkey->Instance->CR,u32RegTemp);

     /*Config the Tkey TKEY_SMPR register*/
    u32RegTemp = (TKEY_SMPR_SWT(htkey->Init.ScanWaitTime) & TKEY_SMPR_SWT_MASK) | \
                 (TKEY_SMPR_CST(htkey->Init.CsDisChargeTime) & TKEY_SMPR_CST_MASK);

    WRITE_REG(htkey->Instance->SMPR,u32RegTemp);

     /*Config the Tkey TKEY_SOFR register*/
    u32RegTemp = (TKEY_SOFR_SW1H(htkey->Init.Sw1H) & TKEY_SOFR_SW1H_MASK) | \
                 (TKEY_SOFR_SW1L(htkey->Init.Sw1L) & TKEY_SOFR_SW1L_MASK);

    WRITE_REG(htkey->Instance->SOFR,u32RegTemp);

    HAL_TKEY_ReadNr(htkey);

    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /* if need calibrate , read the data to the reference data.*/
        htkey->ChannelData[ucI].Tkey_Data->StateId = TKEY_STATEID_STARTUP;
        htkey->ChannelData[ucI].Tkey_Data->ReferenceFlag = 1;

        htkey->ChannelData[ucI].Tkey_RefPara->DetectInTH = htkey->ChannelData[ucI].Tkey_RefPara->RefDelta*htkey->ScanPara.DetectInThRatio;
        htkey->ChannelData[ucI].Tkey_RefPara->DetectOutTH =  htkey->ChannelData[ucI].Tkey_RefPara->RefDelta*htkey->ScanPara.DetectOutThRatio;
        htkey->ChannelData[ucI].Tkey_RefPara->CalibratTH =   htkey->ChannelData[ucI].Tkey_RefPara->RefDelta*htkey->ScanPara.CalibratThRatio;
    }

    HAL_TKEY_ReadAllNx(htkey);
    /* Clear all keys*/
    htkey->ChannelDetected = 0;
    htkey->ChannelDetectedNum  = 0;

    return  HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_DetectProcess
 * Description: TKEY detect main process.
 * input      : htkey : TKEY handle
 * return     : None.
 ************************************************************************/
void HAL_TKEY_DetectProcess(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    const TKEY_ChannelDataDef *ChannelData;

    HAL_TKEY_ReadChannelData(htkey);

    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        ChannelData = &htkey->ChannelData[ucI];
        switch(ChannelData->Tkey_Data->StateId)
        {
            case TKEY_STATEID_STARTUP :
                HAL_TKEY_StartUpStateProcess(ChannelData);
                break;
            case TKEY_STATEID_RELEASE :
                HAL_TKEY_DebDetectStateProcess(ChannelData);
                break;
            case TKEY_STATEID_DETECT :
                if(htkey->ScanTimer >= htkey->ScanPara.DetectingTimeout)
                    htkey->ChannelDetecting |= (1 << ChannelData->ChannelId);
                HAL_TKEY_DebReleaseDetectStateProcess(ChannelData);
                if(ChannelData->Tkey_Data->StateId == TKEY_STATEID_RELEASE)
                {
                    htkey->ChannelDetected |= (1 << ChannelData->ChannelId);
                    htkey->ChannelValue = ChannelData->ChannelId;
                    htkey->ChannelDetectedNum++;
                    htkey->ChannelDetecting &= ~(1 << ChannelData->ChannelId);
                    htkey->ScanTimer = 0;    //Reset the timer when detect Key release.
                }
                break;
            default :
                break;
        }

        if((htkey->ChannelData[ucI].Tkey_Data->Delta > htkey->ChannelData[ucI].Tkey_RefPara->CalibratTH) \
            ||(htkey->ChannelData[ucI].Tkey_Data->Delta < (-htkey->ChannelData[ucI].Tkey_RefPara->CalibratTH)))
        {
            htkey->ScanTimer++;
            if(htkey->ScanTimer >= htkey->ScanPara.CalibratTimeout)
            {
                htkey->CalFlag = 1;     //Need calibrate.
                htkey->ScanTimer = 0;
                htkey->ChannelDetected = 0;
                htkey->ChannelDetecting = 0;
                break;
           }
        }
        if((htkey->ChannelData[ucI].Tkey_Data->Delta > 2*htkey->ChannelData[ucI].Tkey_RefPara->RefDelta) \
            ||(htkey->ChannelData[ucI].Tkey_Data->Delta < (-htkey->ChannelData[ucI].Tkey_RefPara->RefDelta)))
        {
            htkey->CalFlag = 1;     //Need calibrate.
            htkey->ScanTimer = 0;
            htkey->ChannelDetected = 0;
            htkey->ChannelDetecting = 0;
            break;
        }

        if(htkey->ChannelDetecting)  //If don't need detecting.
        {
            htkey->ChannelDetecting = 0;
            htkey->CalFlag = 1;     //Need calibrate.
        }
    }
}

/************************************************************************
 * function   : HAL_TKEY_Calibrate_RefData
 * Description: TKEY Calibrate the base Reference Data.
 * input      : htkey : TKEY handle
                CalTimes: The calibrat times.
 * return     : None
 ************************************************************************/
void HAL_TKEY_Calibrate_RefData(TKEY_HandleTypeDef* htkey, uint8_t CalTimes)
{
    uint8_t ucI,ucJ;
    uint32_t sum[16];

    memset(sum,0,sizeof(sum));
    for(ucJ=0; ucJ < CalTimes; ucJ++)
    {
        HAL_TKEY_ReadChannelData(htkey);
        for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
        {
            if(htkey->ChannelData[ucI].Tkey_Data->Data)
            {
                sum[ucI] +=  htkey->ChannelData[ucI].Tkey_Data->Data;
            }
            if(ucJ == (CalTimes-1))
            {
                htkey->ChannelData[ucI].Tkey_Data->RefData =  sum[ucI]/CalTimes;
            }
        }
    }
}
