/***************************************************************************//**
* \file cy_capsense_generator_v3.c
* \version 3.0
*
* \brief
* This file contains the source of functions common for register map
* generator module.
*
********************************************************************************
* \copyright
* Copyright 2020-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <string.h>
#include "cycfg_capsense_defines.h"
#include "cycfg_peripherals.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_sensing_v3.h"
#include "cy_capsense_generator_v3.h"
#if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
    #include "cy_msc.h"
#endif

#if (defined(CY_IP_M0S8MSCV3))

/*******************************************************************************
* Internal function prototypes
*******************************************************************************/
#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
static void Cy_CapSense_GenerateCtrlMuxSwControl(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
static void Cy_CapSense_ApplyShieldConfig(
                cy_stc_msc_mode_config_t * ptrBaseCfgMode,
                const cy_stc_capsense_context_t * context);
#endif

static void Cy_CapSense_ConfigSensorClock(
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                const cy_stc_capsense_context_t * context);

cy_capsense_status_t Cy_CapSense_GenerateSensorConfigValid(
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                cy_stc_capsense_context_t * context);

uint32_t Cy_CapSense_AdjustSnsClkDivider(
                uint8_t snsMethod,
                uint8_t snsClkSource,
                uint16_t snsClkDivider);


/*******************************************************************************
* Function Name: Cy_CapSense_GenerateBaseConfig
****************************************************************************//**
*
* Generates the configuration for all registers that have to be configured
* one-time to initialize the MSC block.
*
* \param chIndex
* The desired channel index.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is performed successfully.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_GenerateBaseConfig(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context)
{
    uint32_t i;
    uint32_t snsMethod;
    uint32_t idCounter;
    uint8_t * ptrMapping;
    uint32_t cdacDitherEnabled;
    uint32_t snsMethodInternal;
    cy_stc_capsense_internal_context_t * ptrIntrCxt = context->ptrInternalContext;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        cy_stc_msc_mode_config_t * ptrBaseCfgMode;
    #endif

    const cy_stc_msc_base_config_t cy_capsense_smTemplate = CY_CAPSENSE_SENSING_METHOD_BASE_TEMPLATE;

    cy_capsense_status_t capStatus = CY_CAPSENSE_STATUS_SUCCESS;

    cy_stc_msc_base_config_t * ptrBaseCfg;
    const cy_stc_msc_base_config_t * ptrTemplateCfg;
    const cy_stc_msc_channel_config_t * ptrMscChConfig = &context->ptrCommonConfig->ptrMscChConfig[chIndex];

    /*
     * BASE CONFIGURATION
     */
    ptrBaseCfg = &context->ptrBaseFrameContext[chIndex];
    ptrTemplateCfg = &cy_capsense_smTemplate;

    /* Copies template of a base config */
    ptrBaseCfg->ctl = ptrTemplateCfg->ctl;
    if(context->ptrCommonContext->modClk > 1u)
    {
        ptrBaseCfg->ctl &= (~MSC_CTL_CLK_MSC_RATIO_Msk);
    }
    else
    {
        ptrBaseCfg->ctl |= MSC_CTL_CLK_MSC_RATIO_Msk;
    }

    ptrBaseCfg->spare = ptrTemplateCfg->spare;
    ptrBaseCfg->scanCtl1 = ptrTemplateCfg->scanCtl1;
    ptrBaseCfg->scanCtl2 = ptrTemplateCfg->scanCtl2;
    ptrBaseCfg->initCtl1 = ptrTemplateCfg->initCtl1;
    ptrBaseCfg->initCtl2 = ptrTemplateCfg->initCtl2;
    ptrBaseCfg->initCtl3 = ptrTemplateCfg->initCtl3;
    ptrBaseCfg->initCtl4 = ptrTemplateCfg->initCtl4;
    ptrBaseCfg->senseDutyCtl = ptrTemplateCfg->senseDutyCtl;
    ptrBaseCfg->sensePeriodCtl = ptrTemplateCfg->sensePeriodCtl;
    ptrBaseCfg->filterCtl = ptrTemplateCfg->filterCtl;
    ptrBaseCfg->ccompCdacCtl = ptrTemplateCfg->ccompCdacCtl;
    ptrBaseCfg->ditherCdacCtl = ptrTemplateCfg->ditherCdacCtl;
    ptrBaseCfg->cswCtl = ptrTemplateCfg->cswCtl;
    ptrBaseCfg->swSelGpio = ptrTemplateCfg->swSelGpio;
    ptrBaseCfg->swSelCdacRe = ptrTemplateCfg->swSelCdacRe;
    ptrBaseCfg->swSelCdacCo = ptrTemplateCfg->swSelCdacCo;
    ptrBaseCfg->swSelCdacCf = ptrTemplateCfg->swSelCdacCf;
    ptrBaseCfg->swSelCmod1 = ptrTemplateCfg->swSelCmod1;
    ptrBaseCfg->swSelCmod2 = ptrTemplateCfg->swSelCmod2;
    ptrBaseCfg->swSelCmod3 = ptrTemplateCfg->swSelCmod3;
    ptrBaseCfg->swSelCmod4 = ptrTemplateCfg->swSelCmod4;

    if((CY_CAPSENSE_MSC0_CMOD1PADD_PIN != ptrMscChConfig->pinCmod1) &&
       (CY_CAPSENSE_MSC1_CMOD1PADD_PIN != ptrMscChConfig->pinCmod1))
    {
        ptrBaseCfg->swSelCmod1 = 0u;
        ptrBaseCfg->swSelCmod2 = 0u;
    }
    else
    {
        ptrBaseCfg->swSelCmod3 = 0u;
        ptrBaseCfg->swSelCmod4 = 0u;
    }

    ptrBaseCfg->obsCtl = ptrTemplateCfg->obsCtl;
    ptrBaseCfg->intr = ptrTemplateCfg->intr;
    ptrBaseCfg->intrSet = ptrTemplateCfg->intrSet;
    ptrBaseCfg->intrMask = ptrTemplateCfg->intrMask;

    /* Set the scanning mode */
    #if (CY_CAPSENSE_SCAN_MODE_DMA_DRIVEN == CY_CAPSENSE_SCAN_MODE)
        ptrBaseCfg->ctl |= CY_CAPSENSE_SCAN_MODE_DMA_DRIVEN << MSC_CTL_OPERATING_MODE_Pos;
    #endif /* (CY_CAPSENSE_SCAN_MODE_DMA_DRIVEN == CY_CAPSENSE_SCAN_MODE) */

    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        ptrBaseCfg->swSelGpio = 0u;
    #endif

    /* Frame is not started */
    ptrBaseCfg->frameCmd = 0x00u;

    /* Clear Structures */
    (void)memset(&ptrBaseCfg->sensorConfig, 0, sizeof(cy_stc_msc_sensor_config_t));
    (void)memset(&ptrBaseCfg->swSelCsw[0u], 0, CY_MSC_CSW_NUM * CY_CAPSENSE_BYTE_IN_32_BIT);
    (void)memset(&ptrBaseCfg->mode, 0, sizeof(cy_stc_msc_mode_config_t) * CY_MSC_MODES_NUM);

    /*
     * MODE CONFIGURATION
     */
    idCounter = 0u;
    ptrMapping = &ptrIntrCxt->mapSenseMethod[0u];
    for (i = 0u; i < CY_CAPSENSE_REG_MODE_NUMBER; i++)
    {
        ptrMapping[i] = CY_CAPSENSE_REG_MODE_UNDEFINED;
    }
    if (0u == context->ptrCommonConfig->numWd)
    {
        capStatus |= CY_CAPSENSE_STATUS_BAD_CONFIG;
    }
    /* For each widget */
    for (i = 0u; i < context->ptrCommonConfig->numWd; i++)
    {
        cdacDitherEnabled = context->ptrWdContext[i].cdacDitherEn;

        /* Calculate REG_MODE value */
        snsMethod = context->ptrWdConfig[i].senseMethod;
        snsMethodInternal = snsMethod - 1u;

        if (CY_CAPSENSE_ENABLE == cdacDitherEnabled)
        {
            /* Shift sense mode to cdac dither enabled modes */
            snsMethodInternal += CY_CAPSENSE_REG_MODE_DITHERING;
        }

        /* If a method is a new method then register the method */
        if (ptrMapping[snsMethodInternal] == CY_CAPSENSE_REG_MODE_UNDEFINED)
        {
            if (CY_MSC_SENSE_MODE_NUMBER < idCounter)
            {
                capStatus |= CY_CAPSENSE_STATUS_CONFIG_OVERFLOW;
                break;
            }
            else
            {
                ptrMapping[snsMethodInternal] = (uint8_t)idCounter;
                ptrBaseCfg->mode[idCounter] = ptrTemplateCfg->mode[snsMethodInternal];

                #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                        if(CY_CAPSENSE_CSX_GROUP == snsMethod)
                        {
                            ptrBaseCfg->mode[idCounter].senseDutyCtl = CY_CAPSENSE_FW_CSX_AMUX_MODE_SENSE_DUTY_CTL_VALUE;
                        }
                    #endif
                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                        if(CY_CAPSENSE_CSD_GROUP == snsMethod)
                        {
                            ptrBaseCfg->mode[idCounter].senseDutyCtl = 0u;
                        }
                    #endif
                #endif

                if((CY_CAPSENSE_MSC0_CMOD1PADD_PIN != ptrMscChConfig->pinCmod1) &&
                   (CY_CAPSENSE_MSC1_CMOD1PADD_PIN != ptrMscChConfig->pinCmod1))
                {
                    ptrBaseCfg->mode[idCounter].swSelComp &= (~MSC_MODE_SW_SEL_COMP_CPCS1_Msk);
                    ptrBaseCfg->mode[idCounter].swSelComp &= (~MSC_MODE_SW_SEL_COMP_CMCS2_Msk);
                    ptrBaseCfg->mode[idCounter].swSelComp |= MSC_MODE_SW_SEL_COMP_CPCS3_Msk;
                    ptrBaseCfg->mode[idCounter].swSelComp |= MSC_MODE_SW_SEL_COMP_CMCS4_Msk;

                    ptrBaseCfg->mode[idCounter].swSelSh &= (~MSC_MODE_SW_SEL_SH_C1SHG_Msk);
                    ptrBaseCfg->mode[idCounter].swSelSh |= MSC_MODE_SW_SEL_SH_C3SHG_Msk;
                }

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                    if(CY_CAPSENSE_CSX_GROUP == snsMethod)
                    {
                        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                            ptrBaseCfg->mode[idCounter].swSelTop = CY_CAPSENSE_CSX_FW_AMUX_MODE_SW_SEL_TOP_VALUE;
                        #else
                            ptrBaseCfg->mode[idCounter].swSelTop = CY_CAPSENSE_CSX_FW_CTLMUX_MODE_SW_SEL_TOP_VALUE;
                        #endif

                        if(CY_CAPSENSE_SNS_CONNECTION_VDDA_BY_2 == ptrIntrCxt->intrCsxInactSnsConn)
                        {
                            /* Close the reference to filter switch */
                            ptrBaseCfg->mode[idCounter].swSelTop |= MSC_MODE_SW_SEL_TOP_RMF_Msk;
                            #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                                ptrBaseCfg->mode[idCounter].swSelSh = CY_CAPSENSE_FW_CSX_VDDA2_AMUX_MODE_SW_SEL_SH_VALUE;
                            #else
                                ptrBaseCfg->mode[idCounter].swSelSh = CY_CAPSENSE_FW_CSX_VDDA2_CTLMUX_MODE_SW_SEL_SH_VALUE;
                            #endif
                        }
                    }
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

                idCounter++;
            }
        }
    }
    ptrIntrCxt->numSenseMethod = (uint8_t)idCounter;

    /*
     * PINS CONFIGURATION
     */
    for (i = 0u; i < CY_CAPSENSE_CTRLMUX_PIN_STATE_NUMBER; i++)
    {
        ptrBaseCfg->swSelCswFunc[i] = ptrTemplateCfg->swSelCswFunc[i];
    }

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN))
        if (CY_CAPSENSE_SHIELD_PASSIVE == context->ptrCommonConfig->csdShieldMode)
        {
            ptrBaseCfg->swSelCswFunc[CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD] =
                    CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_CSW_VALUE;
        }
    #endif

    /*
     * CONFIGURATION FROM CAPSENSE&trade; DATA STRUCTURE
     */

    /* Initialize interrupts for all enabled MSC channels */
    #if (CY_CAPSENSE_SCAN_MODE_DMA_DRIVEN == CY_CAPSENSE_SCAN_MODE)
        ptrBaseCfg->intrMask |= MSC_INTR_MASK_FRAME_Msk;
    #else
        ptrBaseCfg->intrMask |= MSC_INTR_MASK_SCAN_Msk;
    #endif /* (CY_CAPSENSE_SCAN_MODE_DMA_DRIVEN == CY_CAPSENSE_SCAN_MODE) */

    /* Shielding is available in CSD only */
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN))
        if(CY_CAPSENSE_REG_MODE_UNDEFINED != ptrMapping[CY_CAPSENSE_REG_MODE_CSD])
        {
            ptrBaseCfgMode = &ptrBaseCfg->mode[ptrMapping[CY_CAPSENSE_REG_MODE_CSD]];
            Cy_CapSense_ApplyShieldConfig(ptrBaseCfgMode, context);
        }

        if(CY_CAPSENSE_REG_MODE_UNDEFINED != ptrMapping[CY_CAPSENSE_REG_MODE_CSD_DITHERING])
        {
            ptrBaseCfgMode = &ptrBaseCfg->mode[ptrMapping[CY_CAPSENSE_REG_MODE_CSD_DITHERING]];
            Cy_CapSense_ApplyShieldConfig(ptrBaseCfgMode, context);
        }
    #endif

    /* Generating the common configuration for the Compensation CDAC */
    #if((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CDAC_COMP_USAGE) || \
        (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CDAC_COMP_USAGE))
        ptrBaseCfg->ccompCdacCtl |= (uint32_t)ptrIntrCxt->proOffsetCdacComp << MSC_CCOMP_CDAC_CTL_SEL_CO_PRO_OFFSET_Pos;
    #else
        ptrBaseCfg->swSelCdacCo = 0u;
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CIC2_FILTER_EN)
        /* Generating the common configuration for the CIC2 Filter */
        ptrBaseCfg->filterCtl = 0x01uL << MSC_FILTER_CTL_FILTER_MODE_Pos;
    #endif

    /* Generating the common configuration for the control mux switch control */
    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        Cy_CapSense_GenerateCtrlMuxSwControl(chIndex, context);
    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */

    /* Generating the common configuration for the dithering CapDAC */
    ptrBaseCfg->ditherCdacCtl = (uint32_t)context->ptrCommonContext->cdacDitherSeed |
                                ((uint32_t)context->ptrCommonContext->cdacDitherPoly << MSC_DITHER_CDAC_CTL_LFSR_POLY_FL_Pos);

    /* Configures synchronization signals */

    /* Sync_Clock */
    ptrBaseCfg->ctl &= ~MSC_CTL_CLK_SYNC_EN_Msk;
    /* If SYNC_CLK is enabled, generates CLK_SYNC_EN only for the Master channel */
    if ((((uint32_t)context->ptrCommonConfig->masterChannelId) == (chIndex + context->ptrCommonConfig->channelOffset)) &&
        (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->syncClockEn))
    {
        ptrBaseCfg->ctl |= (uint32_t)context->ptrCommonConfig->syncClockEn << MSC_CTL_CLK_SYNC_EN_Pos;
    }
    /* Frame Start */
    ptrBaseCfg->ctl &= ~MSC_CTL_EXT_FRAME_START_EN_Msk;
    /*
     * If EXT_FRAME_START is enabled, generates EXT_FRAME_START_EN for all channels,
     * except of the Master channel which is generating FRAME_START for all another channels
     */
    if ((((uint32_t)context->ptrCommonConfig->masterChannelId) == (chIndex + context->ptrCommonConfig->channelOffset)) &&
        (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->syncFrameStartEn))
    {
        ptrBaseCfg->ctl |= (uint32_t)context->ptrCommonConfig->syncFrameStartEn << MSC_CTL_EXT_FRAME_START_EN_Pos;
    }
    /* Generating the multi-channel mode for each channel with updating the sensor control registers */
    if (0u != context->ptrCommonConfig->syncMode)
    {
        context->ptrCommonConfig->ptrMscChConfig[chIndex].ptrMscBase->SNS_CTL =
                        ((uint32_t)context->ptrCommonConfig->syncMode << MSC_SNS_CTL_MULTI_CH_MODE_Pos);
    }

    /* Generating the common configuration for the clock dithering */
    ptrBaseCfg->sensePeriodCtl = ((uint32_t)context->ptrCommonContext->lfsrPoly << MSC_SENSE_PERIOD_CTL_LFSR_POLY_Pos) |
                                 ((uint32_t)context->ptrCommonContext->lfsrScale << MSC_SENSE_PERIOD_CTL_LFSR_SCALE_Pos);

    /* Generating the common configuration for the number of the auto-resampling cycles and the counter behaviour when the
     * RAW_COUNT exceeds 0xFFFF
     */
    ptrBaseCfg->scanCtl1 &= ~MSC_SCAN_CTL1_NUM_AUTO_RESAMPLE_Msk;
    ptrBaseCfg->scanCtl1 &= ~MSC_SCAN_CTL1_RAW_COUNT_MODE_Msk;
    ptrBaseCfg->scanCtl1 |= (uint32_t)context->ptrCommonConfig->numBadScans << MSC_SCAN_CTL1_NUM_AUTO_RESAMPLE_Pos;
    ptrBaseCfg->scanCtl1 |= (uint32_t)context->ptrCommonConfig->counterMode << MSC_SCAN_CTL1_RAW_COUNT_MODE_Pos;

    /* Generating the common configuration for the number of epilogue cycles */
    ptrBaseCfg->scanCtl2 &= ~MSC_SCAN_CTL2_NUM_EPI_CYCLES_Msk;
    if (0u < ptrIntrCxt->numEpiCycles)
    {
        ptrBaseCfg->scanCtl2 |= (uint32_t)ptrIntrCxt->numEpiCycles << MSC_SCAN_CTL2_NUM_EPI_CYCLES_Pos;
    }
    else
    {
        ptrBaseCfg->scanCtl2 |= (uint32_t)(1uL << MSC_SCAN_CTL2_NUM_EPI_CYCLES_Pos);
    }

    /* Generating the common configuration for the system level chopping */
    ptrBaseCfg->scanCtl2 &= ~MSC_SCAN_CTL2_CHOP_POL_Msk;
    ptrBaseCfg->scanCtl2 |= (uint32_t)context->ptrCommonConfig->chopPolarity << MSC_SCAN_CTL2_CHOP_POL_Pos;

    /* Generating the common configuration for the coarse initialization and coarse short phase */
    ptrBaseCfg->initCtl1 &= ~MSC_INIT_CTL1_NUM_INIT_CMOD_12_RAIL_CYCLES_Msk;
    ptrBaseCfg->initCtl1 &= ~MSC_INIT_CTL1_NUM_INIT_CMOD_12_SHORT_CYCLES_Msk;
    ptrBaseCfg->initCtl2 &= ~MSC_INIT_CTL2_NUM_INIT_CMOD_34_RAIL_CYCLES_Msk;
    ptrBaseCfg->initCtl2 &= ~MSC_INIT_CTL2_NUM_INIT_CMOD_34_SHORT_CYCLES_Msk;

    if((CY_CAPSENSE_MSC0_CMOD1PADD_PIN == ptrMscChConfig->pinCmod1) ||
       (CY_CAPSENSE_MSC1_CMOD1PADD_PIN == ptrMscChConfig->pinCmod1))
    {
        ptrBaseCfg->initCtl1 |= (uint32_t)ptrIntrCxt->numCoarseInitChargeCycles << MSC_INIT_CTL1_NUM_INIT_CMOD_12_RAIL_CYCLES_Pos;
        ptrBaseCfg->initCtl1 |= (uint32_t)ptrIntrCxt->numCoarseInitSettleCycles << MSC_INIT_CTL1_NUM_INIT_CMOD_12_SHORT_CYCLES_Pos;
        ptrBaseCfg->initCtl3 |= CY_CAPSENSE_CMOD12_PAIR_SELECTION << MSC_INIT_CTL3_CMOD_SEL_Pos;
    }
    else
    {
        ptrBaseCfg->initCtl2 |= (uint32_t)ptrIntrCxt->numCoarseInitChargeCycles << MSC_INIT_CTL2_NUM_INIT_CMOD_34_RAIL_CYCLES_Pos;
        ptrBaseCfg->initCtl2 |= (uint32_t)ptrIntrCxt->numCoarseInitSettleCycles << MSC_INIT_CTL2_NUM_INIT_CMOD_34_SHORT_CYCLES_Pos;
        ptrBaseCfg->initCtl3 |= (uint32_t)CY_CAPSENSE_CMOD34_PAIR_SELECTION << MSC_INIT_CTL3_CMOD_SEL_Pos;
    }
    ptrBaseCfg->initCtl3 &= ~MSC_INIT_CTL3_NUM_PRO_OFFSET_CYCLES_Msk;
    ptrBaseCfg->initCtl3 |= (uint32_t)ptrIntrCxt->numProOffsetCycles << MSC_INIT_CTL3_NUM_PRO_OFFSET_CYCLES_Pos;

    /* Generating the common configuration for the number of sub-conversions to be run during PRO_DUMMY and PRO_WAIT phases. */
    ptrBaseCfg->initCtl4 &= ~MSC_INIT_CTL4_NUM_PRO_DUMMY_SUB_CONVS_Msk;
    ptrBaseCfg->initCtl4 &= ~MSC_INIT_CTL4_NUM_PRO_WAIT_CYCLES_Msk;
    ptrBaseCfg->initCtl4 |= (uint32_t)context->ptrCommonContext->numFineInitCycles << MSC_INIT_CTL4_NUM_PRO_DUMMY_SUB_CONVS_Pos;
    ptrBaseCfg->initCtl4 |= (uint32_t)context->ptrInternalContext->numFineInitWaitCycles << MSC_INIT_CTL4_NUM_PRO_WAIT_CYCLES_Pos;

    return (capStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_GenerateSensorConfigValid
****************************************************************************//**
*
* Generates the configuration for registers that have to be configured to start
* a scan for a single sensor.
*
* \param scanSlot
* Slot to scan
*
* \param ptrSensorCfg
* Specifies the pointer to the sensor configuration to be filled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is performed successfully.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_GenerateSensorConfigValid(
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;
    uint32_t widgetSenseMethod;
    uint32_t snsMethodInternal;
    cy_capsense_status_t capStatus = (uint32_t)CY_CAPSENSE_BAD_PARAM_E;

    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] = 0u;
    ptrSensorCfg[CY_CAPSENSE_SNS_CDAC_CTL_INDEX] = 0u;
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] = 0u;

    /* Sensor clock configuration */
    Cy_CapSense_ConfigSensorClock(scanSlot, &ptrSensorCfg[0u], context);

    /* CapDAC configuration */
    capStatus = Cy_CapSense_GenerateCdacConfig(scanSlot, &ptrSensorCfg[0u], context);

    /* CIC2 filter control */
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] &= ~MSC_SNS_CTL_DECIM_RATE_Msk;
    wdIndex = context->ptrScanSlots[scanSlot].wdId;
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CIC2_FILTER_EN)
        ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= ((uint32_t)context->ptrWdContext[wdIndex].cicRate - 1u) << MSC_SNS_CTL_DECIM_RATE_Pos;
    #endif

    /* Update widget sense method */
    snsMethodInternal = context->ptrWdConfig[wdIndex].senseMethod;
    snsMethodInternal -= 1u;
    if (CY_CAPSENSE_ENABLE == context->ptrWdContext[wdIndex].cdacDitherEn)
    {
        /* Shift sense mode to cdac dither enabled modes */
        snsMethodInternal += CY_CAPSENSE_REG_MODE_DITHERING;
    }
    widgetSenseMethod = context->ptrInternalContext->mapSenseMethod[snsMethodInternal];
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] &= ~MSC_SNS_CTL_SENSE_MODE_SEL_Msk;
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= widgetSenseMethod << MSC_SNS_CTL_SENSE_MODE_SEL_Pos;

    /* Multi-channel mode */
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] &= ~MSC_SNS_CTL_MULTI_CH_MODE_Msk;
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= (uint32_t)context->ptrCommonConfig->syncMode << MSC_SNS_CTL_MULTI_CH_MODE_Pos;

    /* System level chopping */
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] &= ~MSC_SNS_SCAN_CTL_NUM_CONV_Msk;
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] |= ((uint32_t)context->ptrWdConfig[wdIndex].numChopCycles - 1u) << MSC_SNS_SCAN_CTL_NUM_CONV_Pos;

    /* Number of sub-conversions */
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] &= ~MSC_SNS_SCAN_CTL_NUM_SUB_CONVS_Msk;
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] |= ((uint32_t)context->ptrWdContext[wdIndex].numSubConversions - 1u) << MSC_SNS_SCAN_CTL_NUM_SUB_CONVS_Pos;

    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] &= ~(MSC_SNS_SCAN_CTL_INIT_BYPASS_Msk);
    if((CY_CAPSENSE_ENABLE == context->ptrWdContext[wdIndex].coarseInitBypassEn) &&
       ((scanSlot % CY_CAPSENSE_SLOT_COUNT) != context->ptrWdConfig[wdIndex].firstSlotId))
    {
        ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] |= (MSC_SNS_SCAN_CTL_INIT_BYPASS_Msk);
    }

    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= (MSC_SNS_CTL_VALID_Msk);
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= (MSC_SNS_CTL_START_SCAN_Msk);

   return (capStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_GenerateSensorConfig
****************************************************************************//**
*
* Generates configuration to configure registers to
* the scan of the single sensor in the specified slot of the specified channel.
*
* \param chIndex
* The specified channel index.
*
* \param scanSlot
* The specified slot index.
*
* \param ptrSensorCfg
* Specifies the pointer to the sensor configuration to be filled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is performed successfully.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_GenerateSensorConfig(
                uint32_t chIndex,
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;
    uint32_t slotIndex = scanSlot;
    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
        uint32_t nextChIndex;
    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
    cy_capsense_status_t capStatus = CY_CAPSENSE_STATUS_BAD_PARAM;

    wdIndex = context->ptrScanSlots[scanSlot].wdId;

    if((wdIndex == CY_CAPSENSE_SLOT_EMPTY) ||
       (wdIndex == CY_CAPSENSE_SLOT_SHIELD_ONLY) ||
       (wdIndex == CY_CAPSENSE_SLOT_TX_ONLY))
    {
        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
            if (chIndex == 0u)
            {
                slotIndex = scanSlot + CY_CAPSENSE_SLOT_COUNT;
            }
            else
            {
                slotIndex = scanSlot - CY_CAPSENSE_SLOT_COUNT;
            }
        #else /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
            nextChIndex = ((chIndex == 0u) ? 1u : 0u);
            slotIndex = context->ptrActiveScanSns[chIndex].currentChannelSlotIndex + (nextChIndex * CY_CAPSENSE_SLOT_COUNT);
        #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)*/

        /* Generate proper config for sensor */
        capStatus = Cy_CapSense_GenerateSensorConfigValid(slotIndex, ptrSensorCfg, context);
    }
    else
    {
        /* Generate proper config for sensor */
        capStatus = Cy_CapSense_GenerateSensorConfigValid(slotIndex, ptrSensorCfg, context);
    }

    return (capStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_GenerateAllSensorConfig
****************************************************************************//**
*
* Generates configuration to configure registers to start
* a scan for all sensors of the specified channel.
*
* \param chId
* Channel ID
*
* \param ptrSensorCfg
* Specifies the pointer to the sensor configuration to be filled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_GenerateAllSensorConfig(
                uint32_t chId,
                uint32_t * ptrSensorCfg,
                cy_stc_capsense_context_t * context)
{
    uint32_t i = 0u;
    uint32_t scanSlotIndex;
    uint32_t scanSlotIndexValid;
    uint32_t sensorCfgTmp[CY_MSC_6_SNS_REGS] = {0u, 0u, 0u, 0u, 0u, 0u};
    uint32_t * ptrSensorCfgLocal = ptrSensorCfg;

    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        uint32_t snsMask;
        uint32_t snsMaskInactive = 0u;
        uint32_t snsFuncState;
        uint32_t snsFuncStateSelfCap;
        uint32_t snsFuncStateMutualCap;
        uint32_t snsIndex;
        uint32_t wdIndex;
        uint32_t slotValue;
        uint32_t widgetSenseGroup;
        const cy_stc_capsense_electrode_config_t * eltdPinCfg;

        #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_MULTI_PHASE_ENABLED)
            uint32_t j = 0u;
            uint32_t pattern;
            uint32_t snsMaskNegative;
            uint32_t snsFuncStateNegative;
        #endif

        /* Get mask for all pins in control mux switch registers */
        snsMaskInactive = context->ptrBaseFrameContext[chId].cswCtl;

        /* Define mutual cap pin state */
        snsFuncStateMutualCap = CY_CAPSENSE_CTRLMUX_PIN_STATE_GND;
        switch (context->ptrInternalContext->intrCsxInactSnsConn)
        {
            case CY_CAPSENSE_SNS_CONNECTION_HIGHZ:
                snsFuncStateMutualCap = CY_CAPSENSE_CTRLMUX_PIN_STATE_HIGH_Z;
                break;
            case CY_CAPSENSE_SNS_CONNECTION_VDDA_BY_2:
                snsFuncStateMutualCap = CY_CAPSENSE_CTRLMUX_PIN_STATE_VDDA2;
                break;
            default:
                /* No action for other connections */
                break;
        }

        /* Define self cap pin state */
        snsFuncStateSelfCap = CY_CAPSENSE_CTRLMUX_PIN_STATE_GND;
        switch (context->ptrInternalContext->intrCsdInactSnsConn)
        {
            case CY_CAPSENSE_SNS_CONNECTION_HIGHZ:
                snsFuncStateSelfCap = CY_CAPSENSE_CTRLMUX_PIN_STATE_HIGH_Z;
                break;
            case CY_CAPSENSE_SNS_CONNECTION_SHIELD:
                snsFuncStateSelfCap = CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD;
                break;
            default:
                /* No action for other connections */
                break;
        }
    #endif

    for (scanSlotIndex = 0u; scanSlotIndex < CY_CAPSENSE_SLOT_COUNT; scanSlotIndex++)
    {
        scanSlotIndexValid = scanSlotIndex + ((chId + context->ptrCommonConfig->channelOffset) * CY_CAPSENSE_SLOT_COUNT);
        (void)Cy_CapSense_GenerateSensorConfig((chId + context->ptrCommonConfig->channelOffset), scanSlotIndexValid, &sensorCfgTmp[0u], context);

        /* Does this for Control Mux connection only */
        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
            slotValue = context->ptrScanSlots[scanSlotIndexValid].wdId;
            if (CY_CAPSENSE_SLOT_EMPTY == slotValue)
            {
                scanSlotIndexValid = (((chId + 1u) % CY_CAPSENSE_TOTAL_CH_NUMBER) * CY_CAPSENSE_SLOT_COUNT) +
                                     scanSlotIndex;
                wdIndex = context->ptrScanSlots[scanSlotIndexValid].wdId;
                widgetSenseGroup = context->ptrWdConfig[wdIndex].senseMethod;
                if (CY_CAPSENSE_CSD_GROUP == widgetSenseGroup)
                {
                    snsFuncState = snsFuncStateSelfCap;
                }
                else
                {
                    snsFuncState = snsFuncStateMutualCap;
                }
                /* INACTIVE SENSORS */
                Cy_CapSense_CalculateMaskRegisters(snsMaskInactive, snsFuncState, &sensorCfgTmp[0u]);
            }
            else
            {
                if (CY_CAPSENSE_SLOT_SHIELD_ONLY <= slotValue)
                {
                    scanSlotIndexValid = ((uint32_t)context->ptrScanSlots[scanSlotIndexValid].snsId *
                                          CY_CAPSENSE_SLOT_COUNT) + scanSlotIndex;
                }

                snsIndex = context->ptrScanSlots[scanSlotIndexValid].snsId;
                wdIndex = context->ptrScanSlots[scanSlotIndexValid].wdId;
                widgetSenseGroup = context->ptrWdConfig[wdIndex].senseMethod;
                snsFuncState = snsFuncStateMutualCap;
                if (CY_CAPSENSE_CSD_GROUP == widgetSenseGroup)
                {
                    snsFuncState = snsFuncStateSelfCap;
                }
                /* INACTIVE SENSORS */
                Cy_CapSense_CalculateMaskRegisters(snsMaskInactive, snsFuncState, &sensorCfgTmp[0u]);

                /* ACTIVE SELF-CAP SENSOR */
                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                    if (CY_CAPSENSE_SLOT_SHIELD_ONLY > slotValue)
                    {
                        /* Initializes an active sensor (including ganged sensors) by SNS, RX or TX sensor state */
                        if (CY_CAPSENSE_CSD_GROUP == widgetSenseGroup)
                        {
                            snsMask = 0u;
                            snsFuncState = CY_CAPSENSE_CTRLMUX_PIN_STATE_SNS;
                            eltdPinCfg = &context->ptrWdConfig[wdIndex].ptrEltdConfig[snsIndex];
                            /* Proceed only if electrode configuration belongs to selected channel */
                            if ((chId + context->ptrCommonConfig->channelOffset) == eltdPinCfg->chId)
                            {
                                /* Loop through all pads for this electrode (ganged sensor) */
                                for (i = 0u; i < eltdPinCfg->numPins; i++)
                                {
                                    snsMask |= 0x01uL << eltdPinCfg->ptrPin[i].padNumber;
                                }
                                Cy_CapSense_CalculateMaskRegisters(snsMask, snsFuncState, &sensorCfgTmp[0u]);
                            }
                        }
                    }
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

                /* ACTIVE MUTUAL-CAP SENSOR */
                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                    if (CY_CAPSENSE_CSX_GROUP == widgetSenseGroup)
                    {
                        if (CY_CAPSENSE_SLOT_SHIELD_ONLY > slotValue)
                        {
                            /* RX ELECTRODE */
                            snsMask = 0u;
                            snsFuncState = CY_CAPSENSE_CTRLMUX_PIN_STATE_RX;
                            i = snsIndex / context->ptrWdConfig[wdIndex].numRows;
                            eltdPinCfg = &context->ptrWdConfig[wdIndex].ptrEltdConfig[i];
                            if ((chId + context->ptrCommonConfig->channelOffset) == eltdPinCfg->chId)
                            {
                                /* Loop through all pads for this electrode (ganged sensor) */
                                for (i = 0u; i < eltdPinCfg->numPins; i++)
                                {
                                    snsMask |= 0x01uL << eltdPinCfg->ptrPin[i].padNumber;
                                }
                                Cy_CapSense_CalculateMaskRegisters(snsMask, snsFuncState, &sensorCfgTmp[0u]);
                            }
                        }

                        /* Handles multi-phase TX feature */
                        #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_MULTI_PHASE_ENABLED)
                            if (context->ptrWdConfig[wdIndex].mptxOrder >= CY_CAPSENSE_MPTX_MIN_ORDER)
                            {
                                /* Multiple TX ELECTRODES */
                                snsMask = 0u;
                                snsMaskNegative = 0u;
                                snsFuncState = CY_CAPSENSE_CTRLMUX_PIN_STATE_TX;
                                snsFuncStateNegative = CY_CAPSENSE_CTRLMUX_PIN_STATE_TX_NEGATIVE;
                                /* Finds the first sensor number in mptx group */
                                i = snsIndex - (snsIndex % context->ptrWdConfig[wdIndex].mptxOrder);
                                /* Finds TX electrode of the first group sensor */
                                i = context->ptrWdConfig[wdIndex].numCols + (i % context->ptrWdConfig[wdIndex].numRows);
                                eltdPinCfg = &context->ptrWdConfig[wdIndex].ptrEltdConfig[i];
                                /* Finding the right vector / pattern for mptx operation */
                                pattern = context->ptrWdConfig[wdIndex].ptrMptxTable->vector;
                                i = (snsIndex % context->ptrWdConfig[wdIndex].mptxOrder);
                                if (0u != i)
                                {
                                    pattern = (pattern >> i) | (pattern << (context->ptrWdConfig[wdIndex].mptxOrder - i));
                                }
                                if (CY_CAPSENSE_MPTX_MAX_ORDER > context->ptrWdConfig[wdIndex].mptxOrder)
                                {
                                    pattern &= (0x01uL << context->ptrWdConfig[wdIndex].mptxOrder) - 1u;
                                }
                                /* Loop through all involved mptx TX electrodes, positive and negative */
                                for (j = 0u; j < context->ptrWdConfig[wdIndex].mptxOrder; j++)
                                {
                                    if ((chId + context->ptrCommonConfig->channelOffset) == eltdPinCfg->chId)
                                    {
                                        if (0u != (pattern & 0x01u))
                                        {
                                            /* Loop through all pads for this electrode (ganged sensor) */
                                            for (i = 0u; i < eltdPinCfg->numPins; i++)
                                            {
                                                snsMask |= 0x01uL << eltdPinCfg->ptrPin[i].padNumber;
                                            }
                                        }
                                        else
                                        {
                                            /* Loop through all pads for this electrode (ganged sensor) */
                                            for (i = 0u; i < eltdPinCfg->numPins; i++)
                                            {
                                                snsMaskNegative |= 0x01uL << eltdPinCfg->ptrPin[i].padNumber;
                                            }
                                        }
                                    }
                                    pattern >>= 0x01u;
                                    eltdPinCfg++;
                                }
                                Cy_CapSense_CalculateMaskRegisters(snsMask, snsFuncState, &sensorCfgTmp[0u]);
                                Cy_CapSense_CalculateMaskRegisters(snsMaskNegative, snsFuncStateNegative, &sensorCfgTmp[0u]);
                            }
                            else
                            {
                                /* TX ELECTRODE */
                                snsMask = 0u;
                                snsFuncState = CY_CAPSENSE_CTRLMUX_PIN_STATE_TX;
                                i = context->ptrWdConfig[wdIndex].numCols +
                                        (snsIndex % context->ptrWdConfig[wdIndex].numRows);
                                eltdPinCfg = &context->ptrWdConfig[wdIndex].ptrEltdConfig[i];
                                if ((chId + context->ptrCommonConfig->channelOffset) == eltdPinCfg->chId)
                                {
                                    /* Loop through all pads for this electrode (ganged sensor) */
                                    for (i = 0u; i < eltdPinCfg->numPins; i++)
                                    {
                                        snsMask |= 0x01uL << eltdPinCfg->ptrPin[i].padNumber;
                                    }
                                    Cy_CapSense_CalculateMaskRegisters(snsMask, snsFuncState, &sensorCfgTmp[0u]);
                                }
                            }
                        #else
                            /* TX ELECTRODE */
                            snsMask = 0u;
                            snsFuncState = CY_CAPSENSE_CTRLMUX_PIN_STATE_TX;
                            i = context->ptrWdConfig[wdIndex].numCols +
                                    (snsIndex % context->ptrWdConfig[wdIndex].numRows);
                            eltdPinCfg = &context->ptrWdConfig[wdIndex].ptrEltdConfig[i];
                            if ((chId + context->ptrCommonConfig->channelOffset) == eltdPinCfg->chId)
                            {
                                /* Loop through all pads for this electrode (ganged sensor) */
                                for (i = 0u; i < eltdPinCfg->numPins; i++)
                                {
                                    snsMask |= 0x01uL << eltdPinCfg->ptrPin[i].padNumber;
                                }
                                Cy_CapSense_CalculateMaskRegisters(snsMask, snsFuncState, &sensorCfgTmp[0u]);
                            }
                        #endif
                    }
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

                /* SHIELD ELECTRODE */
                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                    if (0u < context->ptrCommonConfig->csdShieldNumPin)
                    {
                        snsMask = 0u;
                        /* Connect shield to CSX_ISC in CSX mode */
                        snsFuncState = (CY_CAPSENSE_CSD_GROUP == widgetSenseGroup) ?
                                        CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD :
                                        snsFuncStateMutualCap;

                        for (i = 0u; i < context->ptrCommonConfig->csdShieldNumPin; i++)
                        {
                            if ((chId + context->ptrCommonConfig->channelOffset) == context->ptrShieldPinConfig[i].chId)
                            {
                                snsMask |= 0x01uL << context->ptrShieldPinConfig[i].padNumber;
                            }
                        }
                        Cy_CapSense_CalculateMaskRegisters(snsMask, snsFuncState, &sensorCfgTmp[0u]);
                    }
                #endif
            }
        #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */

        /* Store results */
        for (i = 0u; i < CY_MSC_6_SNS_REGS; i++)
        {
            ptrSensorCfgLocal[i] = sensorCfgTmp[i];
        }
        ptrSensorCfgLocal += CY_MSC_6_SNS_REGS;
    }
}


#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
/*******************************************************************************
* Function Name: Cy_CapSense_CalculateMaskRegisters
****************************************************************************//**
*
* Calculates the mask for pins that have to be updated for Control MUX
* connection.
*
* \param mask
* Specifies the mask of pins that should be updated.
*
* \param funcState
* Specifies the pin state functionality.
*
* \param ptrCfg
* Specifies the pointer to the mask registers.
*
*******************************************************************************/
void Cy_CapSense_CalculateMaskRegisters(
                uint32_t mask,
                uint32_t funcState,
                uint32_t * ptrCfg)
{
    uint32_t * ptrCfgMask = ptrCfg;

    ptrCfgMask[0u] &= ~mask;
    ptrCfgMask[1u] &= ~mask;
    ptrCfgMask[2u] &= ~mask;
    if (0u != (funcState & 0x04u))
    {
        ptrCfgMask[0u] |= mask;
    }
    if (0u != (funcState & 0x02u))
    {
        ptrCfgMask[1u] |= mask;
    }
    if (0u != (funcState & 0x01u))
    {
        ptrCfgMask[2u] |= mask;
    }
}
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */


/*******************************************************************************
* Function Name: Cy_CapSense_GenerateCdacConfig
****************************************************************************//**
*
* Generates the Cap DAC configuration for a selected sensor.
*
* \param scanSlot
* Slot to scan
*
* \param ptrSensorCfg
* Specifies the pointer to the sensor configuration to be filled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is performed successfully.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_GenerateCdacConfig(
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                const cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t capStatus = 0u;
    const cy_stc_capsense_widget_config_t * ptrWdCfg;
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt;
    uint32_t compDiv;
    uint32_t wdIndex;
    uint32_t snsIndex;
    uint32_t cdacLfsrScale;
    uint32_t snsCdacCtlReg = 0u;

    wdIndex = context->ptrScanSlots[scanSlot].wdId;
    snsIndex = context->ptrScanSlots[scanSlot].snsId;
    ptrWdCfg  = &context->ptrWdConfig[wdIndex];
    ptrSnsCxt = &ptrWdCfg->ptrSnsContext[snsIndex];

    /* Compensation CDAC Divider */
    compDiv = context->ptrWdContext[wdIndex].cdacCompDivider;
    compDiv = (compDiv > 0u) ? (compDiv - 1u) : 0u;
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] &= ~MSC_SNS_SCAN_CTL_COMP_DIV_Msk;
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] |= compDiv << MSC_SNS_SCAN_CTL_COMP_DIV_Pos;

    /* Cap DAC dithering control */
    snsCdacCtlReg = 0u;

    snsCdacCtlReg |= MSC_SNS_CDAC_CTL_CLOCK_REF_RATE_Msk;

    if (CY_CAPSENSE_ENABLE == ptrWdCfg->ptrWdContext->cdacDitherEn)
    {
        cdacLfsrScale = context->ptrWdContext[wdIndex].cdacDitherValue;
        snsCdacCtlReg |= cdacLfsrScale << MSC_SNS_CDAC_CTL_LFSR_SCALE_FL_Pos;
        snsCdacCtlReg |= MSC_SNS_CDAC_CTL_FL_EN_Msk;
    }

    #if(CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
        if (0u != (CY_CAPSENSE_MW_STATE_CALIBRATION_SINGLE_MASK & context->ptrCommonContext->status))
        {
            /* If calibration, reuse compensation CDAC field as Ref CDAC in single CDAC mode */
            snsCdacCtlReg |= ((uint32_t)ptrSnsCxt->cdacComp) << MSC_SNS_CDAC_CTL_SEL_RE_Pos;
        }
        else
        {
            /* Ref CDAC Code setup */
            if ((CY_CAPSENSE_CSD_GROUP == ptrWdCfg->senseMethod) &&
                (ptrWdCfg->numCols <= snsIndex))
            {
                snsCdacCtlReg |= ((uint32_t)ptrWdCfg->ptrWdContext->rowCdacRef) <<
                                                    MSC_SNS_CDAC_CTL_SEL_RE_Pos;
            }
            else
            {
                snsCdacCtlReg |= ((uint32_t)ptrWdCfg->ptrWdContext->cdacRef) <<
                                                    MSC_SNS_CDAC_CTL_SEL_RE_Pos;
            }

            if(((CY_CAPSENSE_CSD_GROUP == ptrWdCfg->senseMethod) &&
                (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->csdCdacCompEn)) ||
               ((CY_CAPSENSE_CSX_GROUP == ptrWdCfg->senseMethod) &&
                (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->csxCdacCompEn)))
            {
                snsCdacCtlReg |= ((uint32_t)ptrSnsCxt->cdacComp) << MSC_SNS_CDAC_CTL_SEL_CO_Pos;
            }
        }
    #else
        if (0u == (CY_CAPSENSE_MW_STATE_CALIBRATION_SINGLE_MASK & context->ptrCommonContext->status))
        {
            /* Ref CDAC Code setup */
            if ((CY_CAPSENSE_CSD_GROUP == ptrWdCfg->senseMethod) &&
                (ptrWdCfg->numCols <= snsIndex))
            {
                snsCdacCtlReg |= ((uint32_t)ptrWdCfg->ptrWdContext->rowCdacRef) <<
                                                    MSC_SNS_CDAC_CTL_SEL_RE_Pos;
            }
            else
            {
                snsCdacCtlReg |= ((uint32_t)ptrWdCfg->ptrWdContext->cdacRef) <<
                                                    MSC_SNS_CDAC_CTL_SEL_RE_Pos;
            }

            if(((CY_CAPSENSE_CSD_GROUP == ptrWdCfg->senseMethod) &&
                (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->csdCdacCompEn)) ||
               ((CY_CAPSENSE_CSX_GROUP == ptrWdCfg->senseMethod) &&
                (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->csxCdacCompEn)))
            {
                snsCdacCtlReg |= ((uint32_t)ptrSnsCxt->cdacComp) << MSC_SNS_CDAC_CTL_SEL_CO_Pos;
            }
        }
    #endif

    ptrSensorCfg[CY_CAPSENSE_SNS_CDAC_CTL_INDEX] = snsCdacCtlReg;

    return (capStatus);
}


#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
/*******************************************************************************
* Function Name: Cy_CapSense_GenerateCtrlMuxSwControl
****************************************************************************//**
*
* Generates the Control MUX Switch Control register configuration.
*
* \param chIndex
* The desired channel index.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_GenerateCtrlMuxSwControl(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context)
{
    uint32_t cswFuncMode = 0uL;
    uint32_t i;
    const cy_stc_capsense_pin_config_t * ptrPinCfg = context->ptrPinConfig;

    for (i = 0u; i < context->ptrCommonConfig->numPin; i++)
    {
        if ((chIndex + context->ptrCommonConfig->channelOffset) == ptrPinCfg->chId)
        {
            cswFuncMode |= (0x01uL << ptrPinCfg->padNumber);
        }
        ptrPinCfg++;
    }

    ptrPinCfg = context->ptrShieldPinConfig;
    for (i = 0u; i < context->ptrCommonConfig->csdShieldNumPin; i++)
    {
        if ((chIndex + context->ptrCommonConfig->channelOffset) == ptrPinCfg->chId)
        {
            cswFuncMode |= (0x01uL << ptrPinCfg->padNumber);
        }
        ptrPinCfg++;
    }
    context->ptrBaseFrameContext[chIndex].cswCtl = cswFuncMode;
}
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_ApplyShieldConfig
****************************************************************************//**
*
* Applies shield configuration to the base configuration.
*
* \param ptrBaseCfgMode
* Specifies the pointer to the sense mode registers structure
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_ApplyShieldConfig(
                cy_stc_msc_mode_config_t * ptrBaseCfgMode,
                const cy_stc_capsense_context_t * context)
{
    ptrBaseCfgMode->senseDutyCtl &= ~(MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH0_EN_Msk |
                                      MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH1_EN_Msk);
    /* Active Shield mode */
    if (CY_CAPSENSE_SHIELD_ACTIVE == context->ptrCommonConfig->csdShieldMode)
    {
        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
            ptrBaseCfgMode->swSelTop &= ~CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_TOP_MASK;
            ptrBaseCfgMode->swSelTop |= CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_TOP_VALUE;
            ptrBaseCfgMode->swSelSh  |= CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_SH_VALUE;

        #else /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
            /* Amux sensor_connection_method */
            ptrBaseCfgMode->swSelTop &= ~CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_TOP_MASK;
            ptrBaseCfgMode->swSelTop |= CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_TOP_VALUE;
            ptrBaseCfgMode->swSelSh  |= CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_SH_VALUE;
        #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
    }
    /* Passive Shield mode */
    else
    {
        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
            ptrBaseCfgMode->swSelTop &= ~CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_TOP_MASK;
            ptrBaseCfgMode->swSelTop |= CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_TOP_VALUE;
            ptrBaseCfgMode->senseDutyCtl |= ((1u << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH0_EN_Pos) |
                                             (1u << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH1_EN_Pos));
        #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
    }
}
#endif

/*******************************************************************************
* Function Name: Cy_CapSense_ConfigSensorClock
****************************************************************************//**
*
* This function configures the sense clock for different modes.
*
* \param scanSlot
* Slot to scan
*
* \param ptrSensorCfg
* Specifies the pointer to the sensor configuration to be filled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_ConfigSensorClock(
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                const cy_stc_capsense_context_t * context)
{
    uint8_t lfsrBitsVal;
    uint8_t lfsrModeVal;
    uint16_t snsClkDividerVal;

    uint32_t wdIndex = context->ptrScanSlots[scanSlot].wdId;
    const cy_stc_capsense_widget_context_t * ptrWdCxt = &context->ptrWdContext[wdIndex];
    const cy_stc_capsense_widget_config_t * ptrWdCfg = &context->ptrWdConfig[wdIndex];

    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] &= ~(MSC_SNS_CTL_SENSE_DIV_Msk |
                                                 MSC_SNS_CTL_LFSR_MODE_Msk |
                                                 MSC_SNS_CTL_LFSR_BITS_Msk);

    /* Getting column sense clock divider */
    snsClkDividerVal = ptrWdCxt->snsClk;
    if((CY_CAPSENSE_CSD_GROUP == ptrWdCfg->senseMethod) &&
       (ptrWdCfg->numCols <= context->ptrScanSlots[scanSlot].snsId))
    {
        snsClkDividerVal = ptrWdCxt->rowSnsClk;
    }

    snsClkDividerVal = (uint16_t)Cy_CapSense_AdjustSnsClkDivider(ptrWdCfg->senseMethod,
                                                ptrWdCxt->snsClkSource, snsClkDividerVal);

    snsClkDividerVal -= 1u;
    lfsrBitsVal = (ptrWdCxt->lfsrBits & CY_CAPSENSE_LFSR_BITS_RANGE_MASK);
    lfsrModeVal = (ptrWdCxt->snsClkSource & CY_CAPSENSE_CLK_SOURCE_MASK);

    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= (((uint32_t)snsClkDividerVal) << MSC_SNS_CTL_SENSE_DIV_Pos) |
                                                ((uint32_t)lfsrModeVal << MSC_SNS_CTL_LFSR_MODE_Pos) |
                                                ((uint32_t)lfsrBitsVal << MSC_SNS_CTL_LFSR_BITS_Pos);
}


/*******************************************************************************
* Function Name: Cy_CapSense_AdjustSnsClkDivider
****************************************************************************//**
*
* If the PRS is selected as the Sense Clock source, adjusts the Sense Clock
* divider to obtain the max frequency of the PRS sequence equal to
* ModClkFreq / SenseClkDivider. Updates the sense Clock divider with the minimal
* supported value in case if it is out of range for the specified parameters.
*
* \param snsMethod
*  Specifies the widget group:
*   - CSD (CY_CAPSENSE_CSD_GROUP)
*   - CSX (CY_CAPSENSE_CSX_GROUP)
*
* \param snsClkSource
*  Specifies the sense Clock source, supported by MSCv3 HW:
*   - CY_CAPSENSE_CLK_SOURCE_DIRECT
*   - CY_CAPSENSE_CLK_SOURCE_SSC
*   - CY_CAPSENSE_CLK_SOURCE_PRS
*
* \param snsClkDivider
* The divider value for the sense clock.
*
* \return
*  Adjusted value of the Sense Clock divider.
*
*******************************************************************************/
uint32_t Cy_CapSense_AdjustSnsClkDivider(
                        uint8_t snsMethod,
                        uint8_t snsClkSource,
                        uint16_t snsClkDivider)
{
    uint16_t snsClkDividerTmp;
    uint32_t snsClkDividerShift;
    uint32_t snsClkSourceTmp;

    snsClkDividerTmp = snsClkDivider;
    snsClkSourceTmp = ((uint32_t)snsClkSource & CY_CAPSENSE_CLK_SOURCE_MASK);

    if(CY_CAPSENSE_CSD_GROUP == snsMethod)
    {
        snsClkDividerShift = CY_CAPSENSE_4PH_PRS_SNS_CLOCK_DIVIDER_SHIFT;
    }
    else
    {
        snsClkDividerShift = CY_CAPSENSE_2PH_PRS_SNS_CLOCK_DIVIDER_SHIFT;
    }

    if(CY_CAPSENSE_CLK_SOURCE_PRS == snsClkSourceTmp)
    {
        snsClkDividerTmp >>= snsClkDividerShift;
    }

    return (snsClkDividerTmp);
}


#endif /* CY_IP_M0S8MSCV3 */


/* [] END OF FILE */
