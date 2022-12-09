/***************************************************************************//**
* \file cy_capsense_centroid.c
* \version 3.0
*
* \brief
* This file provides the source code for the centroid calculation methods
* of the CAPSENSE&trade; middleware.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include "cy_syslib.h"
#include "cy_capsense_centroid.h"
#include "cy_capsense_common.h"
#include "cy_capsense_lib.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_filter.h"
#include "cycfg_capsense_defines.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))
#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_SLIDER_EN) || (CY_CAPSENSE_DISABLE != CY_CAPSENSE_TOUCHPAD_EN))


/*******************************************************************************
* Local definition
*******************************************************************************/
#define CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_LENGTH        (3u)
#define CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_PREVIOUS      (0u)
#define CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_CENTER        (1u)
#define CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_NEXT          (2u)
#define CY_CAPSENSE_LINEAR_SLIDER_MIN_SNS_COUNT         (3u)
#define CY_CAPSENSE_TOUCHPAD_MIN_COL_SNS_COUNT          (3u)
#define CY_CAPSENSE_TOUCHPAD_MIN_ROW_SNS_COUNT          (3u)

/* Minimum valid age */
#define CY_CAPSENSE_CSX_TOUCHPAD_AGE_START              (0x0100u)
#define CY_CAPSENSE_CSX_TOUCHPAD_Z_SHIFT                (0x04u)
#define CY_CAPSENSE_CSX_TOUCHPAD_BYTE_SHIFT             (8u)
#define CY_CAPSENSE_CENTROID_ROUND_VALUE                (0x7Fu)
#define CY_CAPSENSE_NO_LOCAL_MAX                        (0xFFFFu)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    static void Cy_CapSense_TransferTouch(
                    uint32_t newIndex,
                    uint32_t oldIndex,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    static void Cy_CapSense_NewTouch(
                    uint32_t newIndex,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    static uint32_t Cy_CapSense_CalcDistance(
                    uint32_t newIndex,
                    uint32_t oldIndex,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    static void Cy_CapSense_Hungarian(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    static void Cy_CapSense_CopyTouchRecord(
                    cy_stc_capsense_position_t * destination,
                    const cy_stc_capsense_position_t * source);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    __STATIC_INLINE void Cy_CapSense_TouchDownDebounce(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    __STATIC_INLINE void Cy_CapSense_SortByAge(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    __STATIC_INLINE uint8_t Cy_CapSense_GetLowestId(uint8_t idMask);
#endif
/** \} \endcond */


#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_DIPLEX_SLIDER_EN) ||\
    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_DIPLEX_SLIDER_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_DpCentroidDiplex
****************************************************************************//**
*
* Finds touch position of a Linear slider widget with enabled diplexing.
*
* In scope of position searching this function finds the local maximum with the
* highest raw count. If such maximums are more than one, then the maximum with the
* bigger sum of neighboring sensors is taken for further processing. Then the position
* is calculated using centroid algorithm with three sensors.
*
* At least two neighboring sensors should cross finger threshold. Then the algorithm
* is able to distinguish where real touch is located (direct part of slider or
* diplex part of slider) and corresponding position is reported. Otherwise no
* touch is reported.
*
* This function does not detect two or more touches.
*
* \param newTouch
* The pointer to the touch structure where found position is stored.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
*******************************************************************************/
void Cy_CapSense_DpCentroidDiplex(
                cy_stc_capsense_touch_t * newTouch,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t sum;
    uint32_t diffM;
    uint32_t diffP;
    uint32_t snsIndex;
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt;
    const uint8_t * ptrDpxTable;
    uint32_t snsCount = ptrWdConfig->numSns;

    uint32_t maxSum = 0u;
    uint32_t maxDiff = 0u;
    uint32_t maxIndex = CY_CAPSENSE_NO_LOCAL_MAX;
    uint32_t threshold = ptrWdConfig->ptrWdContext->fingerTh;
    int32_t numerator = 0;
    int32_t denominator = 0;
    uint32_t multiplier;
    uint32_t offset;

    threshold -= ptrWdConfig->ptrWdContext->hysteresis;
    ptrDpxTable = ptrWdConfig->ptrDiplexTable;

    /* Find maximum signal */
    ptrSnsCxt = ptrWdConfig->ptrSnsContext;
    for (snsIndex = 0u; snsIndex < snsCount; snsIndex++)
    {
        if (maxDiff < ptrSnsCxt->diff)
        {
            maxDiff = ptrSnsCxt->diff;
        }
        ptrSnsCxt++;
    }

    /* Find sensor index with maximum sum ([i-1],[i],[i+1]) including diplex part */
    ptrSnsCxt = ptrWdConfig->ptrSnsContext;
    for (snsIndex = 0u; snsIndex < (snsCount << 1u); snsIndex++)
    {
        /* Potential maximum */
        if (maxDiff == ptrSnsCxt[ptrDpxTable[snsIndex]].diff)
        {
            /* Get sum of differences around maximum */
            diffM = (snsIndex > 0u) ? ptrSnsCxt[ptrDpxTable[snsIndex - 1u]].diff : 0u;
            diffP = (snsIndex < ((snsCount << 1u) - 1u)) ? ptrSnsCxt[ptrDpxTable[snsIndex + 1u]].diff : 0u;
            sum = ptrSnsCxt[ptrDpxTable[snsIndex]].diff + diffM + diffP;
            if ((diffM < threshold) && (diffP < threshold))
            {
                sum = 0u;
            }
            if (maxSum < sum)
            {
                /* New maximum */
                maxIndex = snsIndex;
                maxSum = sum;
                numerator = (int32_t)diffP - (int32_t)diffM;
            }
        }
    }

    if ((maxIndex != CY_CAPSENSE_NO_LOCAL_MAX) && (maxSum > 0u))
    {
        multiplier = (uint32_t)ptrWdConfig->xResolution << 8u;
        /* Calculate position */
        if (0u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CALC_METHOD_MASK))
        {
            multiplier /= ((snsCount << 1u) - 1u);
            offset = 0u;
        }
        else
        {
            multiplier /= (snsCount << 1u);
            offset = multiplier >> 1u;
        }

        denominator = (int32_t)maxSum;
        denominator = ((numerator * (int32_t)multiplier) / denominator) + (((int32_t)maxIndex * (int32_t)multiplier) + (int32_t)offset);

        /* Round result and shift 8 bits left */
        newTouch->numPosition = CY_CAPSENSE_POSITION_ONE;
        newTouch->ptrPosition[0u].x = (uint16_t)(((uint32_t)denominator + CY_CAPSENSE_CENTROID_ROUND_VALUE) >> 8u);
    }
    else
    {
        newTouch->numPosition = CY_CAPSENSE_POSITION_NONE;
    }
}
#endif /*((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_DIPLEX_SLIDER_EN) ||\
          (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_DIPLEX_SLIDER_EN)) */


#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_LINEAR_SLIDER_EN) ||\
    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_LINEAR_SLIDER_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_DpCentroidLinear
****************************************************************************//**
*
* Finds touch position of a Linear slider widget.
*
* In scope of position searching this function finds the local maximum with the
* highest raw count. If such maximums are more than one, then the maximum with
* bigger sum of neighboring sensors is taken for further processing. Then the position
* is calculated using centroid algorithm with three sensors.
*
* This function does not detect two or more touches.
*
* \param newTouch
* The pointer to the touch structure where the found position is stored.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
*******************************************************************************/
void Cy_CapSense_DpCentroidLinear(
                cy_stc_capsense_touch_t * newTouch,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t snsIndex = 0u;
    uint32_t snsCount = ptrWdConfig->numSns;

    uint32_t diffM;
    uint32_t diffP;
    uint32_t sum = 0u;
    uint32_t maxSum = 0u;
    uint32_t maxDiff = 0u;
    uint32_t maxIndex = CY_CAPSENSE_NO_LOCAL_MAX;
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt;
    int32_t numerator = 0;
    int32_t denominator = 0;
    uint32_t multiplier;
    uint32_t offset;

    if(snsCount < CY_CAPSENSE_LINEAR_SLIDER_MIN_SNS_COUNT)
    {
        snsCount = CY_CAPSENSE_LINEAR_SLIDER_MIN_SNS_COUNT;
    }

    if (1u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CENTROID_NUMBER_MASK))
    {
        /* Find maximum signal */
        ptrSnsCxt = ptrWdConfig->ptrSnsContext;
        for (snsIndex = 0u; snsIndex < snsCount; snsIndex++)
        {
            if (ptrSnsCxt->diff > maxDiff)
            {
                maxDiff = ptrSnsCxt->diff;
            }
            ptrSnsCxt++;
        }

        /* Find index of sensor with maximum signal */
        ptrSnsCxt = ptrWdConfig->ptrSnsContext;
        for (snsIndex = 0u; snsIndex < snsCount; snsIndex++)
        {
            /* Potential maximum */
            if (maxDiff == ptrSnsCxt->diff)
            {
                /* Get sum of differences around maximum */
                diffM = (snsIndex > 0u) ? (ptrSnsCxt - 1u)->diff : 0u;
                diffP = (snsIndex < (snsCount - 1u)) ? (ptrSnsCxt + 1u)->diff : 0u;
                sum = ptrSnsCxt->diff + diffM + diffP;
                if (maxSum < sum)
                {
                    /* New maximum */
                    maxIndex = snsIndex;
                    maxSum = sum;
                    numerator = (int32_t)diffP - (int32_t)diffM;
                }
            }
            ptrSnsCxt++;
        }

        if ((maxIndex != CY_CAPSENSE_NO_LOCAL_MAX) && (maxSum > 0u))
        {
            /* Calculate position */
            multiplier = (uint32_t)ptrWdConfig->xResolution << 8u;
            if (0u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CALC_METHOD_MASK))
            {
                multiplier /= (snsCount - 1u);
                offset = 0u;
            }
            else
            {
                multiplier /= snsCount;
                offset = multiplier >> 1u;
            }

            denominator = (int32_t)maxSum;
            denominator = ((numerator * (int32_t)multiplier) / denominator) + (((int32_t)maxIndex * (int32_t)multiplier) + (int32_t)offset);

            /* Round result and shift 8 bits left */
            newTouch->numPosition = CY_CAPSENSE_POSITION_ONE;
            newTouch->ptrPosition[0u].x = (uint16_t)(((uint32_t)denominator + CY_CAPSENSE_CENTROID_ROUND_VALUE) >> 8u);
        }
        else
        {
            newTouch->numPosition = CY_CAPSENSE_POSITION_NONE;
        }
    }
    else
    {
        /* This is a place holder for local maximum searching when number of centroids could be more than one */
    }
}
#endif /* ((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_LINEAR_SLIDER_EN) ||\
           (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_LINEAR_SLIDER_EN)) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_RADIAL_SLIDER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_DpCentroidRadial
****************************************************************************//**
*
* Finds touch position of a Radial slider widget.
*
* In scope of position searching this function finds the local maximum with the
* highest raw count. If such maximums are more than one, then the maximum with
* bigger sum of neighboring sensors is taken for further processing. Then the position
* is calculated using centroid algorithm with three sensors.
*
* This function does not detect two or more touches.
*
* \param newTouch
* The pointer to the touch structure where found position is stored.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
*******************************************************************************/
void Cy_CapSense_DpCentroidRadial(
                cy_stc_capsense_touch_t * newTouch,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t snsIndex = 0u;
    uint32_t snsCount = ptrWdConfig->numSns;

    uint32_t diffM;
    uint32_t diffP;
    uint32_t sum = 0u;
    uint32_t maxSum = 0u;
    uint32_t maxDiff = 0u;
    uint32_t maxIndex = CY_CAPSENSE_NO_LOCAL_MAX;
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt;
    int32_t numerator = 0;
    int32_t denominator = 0;
    uint32_t multiplier;

    if (1u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CENTROID_NUMBER_MASK))
    {
        /* Find maximum signal */
        ptrSnsCxt = ptrWdConfig->ptrSnsContext;
        for (snsIndex = 0u; snsIndex < snsCount; snsIndex++)
        {
            if (ptrSnsCxt->diff > maxDiff)
            {
                maxDiff = ptrSnsCxt->diff;
            }
            ptrSnsCxt++;
        }

        /* Find index of sensor with maximum signal */
        ptrSnsCxt = ptrWdConfig->ptrSnsContext;
        for (snsIndex = 0u; snsIndex < snsCount; snsIndex++)
        {
            /* Potential maximum */
            if (maxDiff == ptrSnsCxt->diff)
            {
                /* Get sum of differences around maximum */
                diffM = (snsIndex > 0u) ? (ptrSnsCxt - 1u)->diff : ptrWdConfig->ptrSnsContext[snsCount - 1u].diff;
                diffP = (snsIndex < (snsCount - 1u)) ? (ptrSnsCxt + 1u)->diff : ptrWdConfig->ptrSnsContext[0u].diff;
                sum = ptrSnsCxt->diff + diffM + diffP;
                if (maxSum < sum)
                {
                    /* New maximum */
                    maxIndex = snsIndex;
                    maxSum = sum;
                    numerator = (int32_t)diffP - (int32_t)diffM;
                }
            }
            ptrSnsCxt++;
        }

        if ((maxIndex != CY_CAPSENSE_NO_LOCAL_MAX) && (maxSum > 0u))
        {
            /* Calculate position */
            multiplier = ((uint32_t)ptrWdConfig->xResolution << 8u) / snsCount;

            denominator = (int32_t)maxSum;
            denominator = ((numerator * (int32_t)multiplier) / denominator) + ((int32_t)maxIndex * (int32_t)multiplier);

            if (denominator < 0)
            {
                denominator += ((int32_t)snsCount * (int32_t)multiplier);
            }
            /* Round result and shift 8 bits left */
            newTouch->numPosition = CY_CAPSENSE_POSITION_ONE;
            newTouch->ptrPosition[0u].x = (uint16_t)(((uint32_t)denominator + CY_CAPSENSE_CENTROID_ROUND_VALUE) >> 8u);
        }
        else
        {
            newTouch->numPosition = CY_CAPSENSE_POSITION_NONE;
        }
    }
    else
    {
        /* This is a place holder for local maximum searching when number of centroids could be more than one */
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_RADIAL_SLIDER_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_DpCentroidTouchpad
****************************************************************************//**
*
* Finds touch position of a CSD Touchpad widget.
*
* In scope of position searching this function finds the local maximum with the
* highest raw count. If such maximums are more than one, then the maximum with
* bigger sum of neighboring sensors is taken for further processing. Then the position
* is calculated using centroid algorithm with three sensors.
*
* This function does not detect two or more touches.
*
* \param newTouch
* The pointer to the touch structure where found position is stored.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
*******************************************************************************/
void Cy_CapSense_DpCentroidTouchpad(
                cy_stc_capsense_touch_t * newTouch,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t snsIndex = 0u;
    uint32_t snsCount = ptrWdConfig->numSns;
    uint32_t colCount = ptrWdConfig->numCols;
    uint32_t rowCount = ptrWdConfig->numRows;

    uint32_t diffM;
    uint32_t diffP;
    uint32_t sum = 0u;
    uint32_t maxSum = 0u;
    uint32_t maxDiff = 0u;
    uint32_t maxIndex = CY_CAPSENSE_NO_LOCAL_MAX;
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt;
    int32_t numerator = 0;
    int32_t denominator = 0;
    uint32_t multiplier;
    uint32_t offset;

    if(CY_CAPSENSE_TOUCHPAD_MIN_COL_SNS_COUNT > colCount)
    {
        colCount = CY_CAPSENSE_TOUCHPAD_MIN_COL_SNS_COUNT;
    }

    if(CY_CAPSENSE_TOUCHPAD_MIN_ROW_SNS_COUNT > rowCount)
    {
        rowCount = CY_CAPSENSE_TOUCHPAD_MIN_ROW_SNS_COUNT;
    }

    if (1u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CENTROID_NUMBER_MASK))
    {
        /***********************************************************************
        * X Axis (Cols)
        ***********************************************************************/
        sum = 0u;
        maxSum = 0u;
        maxDiff = 0u;
        /* Find maximum signal */
        ptrSnsCxt = ptrWdConfig->ptrSnsContext;
        for (snsIndex = 0u; snsIndex < colCount; snsIndex++)
        {
            if (ptrSnsCxt->diff > maxDiff)
            {
                maxDiff = ptrSnsCxt->diff;
            }
            ptrSnsCxt++;
        }

        /* Find index of sensor with maximum signal */
        ptrSnsCxt = ptrWdConfig->ptrSnsContext;
        for (snsIndex = 0u; snsIndex < colCount; snsIndex++)
        {
            /* Potential maximum */
            if (maxDiff == ptrSnsCxt->diff)
            {
                /* Get sum of differences around maximum */
                diffM = (snsIndex > 0u) ? (ptrSnsCxt - 1u)->diff : 0u;
                diffP = (snsIndex < (colCount - 1u)) ? (ptrSnsCxt + 1u)->diff : 0u;
                sum = ptrSnsCxt->diff + diffM + diffP;
                /* Check whether this sum is maximum sum */
                if (maxSum < sum)
                {
                    /* New maximum */
                    maxIndex = snsIndex;
                    maxSum = sum;
                    numerator = (int32_t)diffP - (int32_t)diffM;
                }
            }
            ptrSnsCxt++;
        }

        if ((maxIndex != CY_CAPSENSE_NO_LOCAL_MAX) && (maxSum > 0u))
        {
            /* Calculate position */
            multiplier = (uint32_t)ptrWdConfig->xResolution << 8u;
            if (0u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CALC_METHOD_MASK))
            {
                multiplier /= (colCount - 1u);
                offset = 0u;
            }
            else
            {
                multiplier /= colCount;
                offset = multiplier >> 1u;
            }

            denominator = (int32_t)maxSum;
            denominator = ((numerator * (int32_t)multiplier) / denominator) + (((int32_t)maxIndex * (int32_t)multiplier) + (int32_t)offset);

            /* Round result and shift 8 bits left */
            newTouch->numPosition = CY_CAPSENSE_POSITION_ONE;
            newTouch->ptrPosition[0u].x = (uint16_t)(((uint32_t)denominator + CY_CAPSENSE_CENTROID_ROUND_VALUE) >> 8u);
        }
        else
        {
            newTouch->numPosition = CY_CAPSENSE_POSITION_NONE;
        }

        if(newTouch->numPosition != CY_CAPSENSE_POSITION_NONE)
        {
            /***********************************************************************
            * Y Axis (Rows)
            ***********************************************************************/
            sum = 0u;
            maxSum = 0u;
            maxDiff = 0u;
            maxIndex = CY_CAPSENSE_NO_LOCAL_MAX;
            /* Find maximum signal */
            ptrSnsCxt = &ptrWdConfig->ptrSnsContext[colCount];
            for (snsIndex = colCount; snsIndex < snsCount; snsIndex++)
            {
                if (ptrSnsCxt->diff > maxDiff)
                {
                    maxDiff = ptrSnsCxt->diff;
                }
                ptrSnsCxt++;
            }

            /* Find index of sensor with maximum signal */
            ptrSnsCxt = &ptrWdConfig->ptrSnsContext[colCount];
            for (snsIndex = 0u; snsIndex < rowCount; snsIndex++)
            {
                /* Potential maximum */
                if (maxDiff == ptrSnsCxt->diff)
                {
                    /* Get sum of differences around maximum */
                    diffM = (snsIndex > 0u) ? (ptrSnsCxt - 1u)->diff : 0u;
                    diffP = (snsIndex < (rowCount - 1u)) ? (ptrSnsCxt + 1u)->diff : 0u;
                    sum = ptrSnsCxt->diff + diffM + diffP;
                    /* Check if this sum is maximum sum */
                    if (maxSum < sum)
                    {
                        /* New maximum */
                        maxIndex = snsIndex;
                        maxSum = sum;
                        numerator = (int32_t)diffP - (int32_t)diffM;
                    }
                }
                ptrSnsCxt++;
            }

            if ((maxIndex != CY_CAPSENSE_NO_LOCAL_MAX) && (maxSum > 0u))
            {
                /* Calculate position */
                multiplier = (uint32_t)ptrWdConfig->yResolution << 8u;
                if (0u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CALC_METHOD_MASK))
                {
                    multiplier /= (rowCount - 1u);
                    offset = 0u;
                }
                else
                {
                    multiplier /= rowCount;
                    offset = multiplier >> 1u;
                }

                denominator = (int32_t)maxSum;
                denominator = ((numerator * (int32_t)multiplier) / denominator) + (((int32_t)maxIndex * (int32_t)multiplier) + (int32_t)offset);

                /* Round result and shift 8 bits left */
                newTouch->ptrPosition[0].y = (uint16_t)(((uint32_t)denominator + CY_CAPSENSE_CENTROID_ROUND_VALUE) >> 8u);
            }
            else
            {
                newTouch->numPosition = CY_CAPSENSE_POSITION_NONE;
            }
        }
    }
    else
    {
        /* This is a place holder for local maximum searching when number of centroids could be more than one */
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN) */

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_ADVANCED_CENTROID_5X5_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_DpAdvancedCentroidTouchpad
****************************************************************************//**
*
* Finds touch position of a CSD touchpad widget using an advanced centroid
* algorithm.
*
* This function is able to detect two touch positions using a centroid algorithm
* with matrix 5*5 of sensors and virtual sensors on the edges.
*
* \param newTouch
* The pointer to the touch structure where the found position is stored.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
*******************************************************************************/
void Cy_CapSense_DpAdvancedCentroidTouchpad(
                cy_stc_capsense_touch_t * newTouch,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t i;
    const cy_stc_capsense_sensor_context_t * ptrSnsIndex = ptrWdConfig->ptrSnsContext;
    uint16_t * ptrDiffIndex = ptrWdConfig->ptrCsdTouchBuffer;
    cy_stc_capsense_advanced_centroid_config_t advCfg;

    advCfg.fingerTh = ptrWdConfig->ptrWdContext->fingerTh;
    advCfg.penultimateTh = ptrWdConfig->advConfig.penultimateTh;
    advCfg.virtualSnsTh = ptrWdConfig->advConfig.virtualSnsTh;
    advCfg.resolutionX = ptrWdConfig->xResolution;
    advCfg.resolutionY = ptrWdConfig->yResolution;
    advCfg.snsCountX = ptrWdConfig->numCols;
    advCfg.snsCountY = ptrWdConfig->numRows;
    advCfg.crossCouplingTh = ptrWdConfig->advConfig.crossCouplingTh;
    advCfg.edgeCorrectionEn = 0u;
    advCfg.twoFingersEn = 0u;

    if ((ptrWdConfig->centroidConfig & CY_CAPSENSE_CENTROID_NUMBER_MASK) > CY_CAPSENSE_POSITION_ONE)
    {
        advCfg.twoFingersEn = 1u;
    }
    if (0u != (ptrWdConfig->centroidConfig & CY_CAPSENSE_EDGE_CORRECTION_MASK))
    {
        advCfg.edgeCorrectionEn = 1u;
    }
    for (i = 0u; i < ptrWdConfig->numSns; i++)
    {
        ptrDiffIndex[i] = ptrSnsIndex[i].diff;
    }

    Cy_CapSense_AdvancedCentroidGetTouchCoordinates_Lib(
                &advCfg,
                ptrWdConfig->ptrCsdTouchBuffer,
                newTouch);
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_ADVANCED_CENTROID_5X5_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_DpFindLocalMaxDd
****************************************************************************//**
*
* Finds up to five local maximums for CSX Touchpad.
*
* This function takes an array of differences of the specified widget and
* finds up to five local maximums. The found maximums are stored in the CSX buffer
* ptrCsxTouchBuffer \ref cy_stc_capsense_csx_touch_buffer_t.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
void Cy_CapSense_DpFindLocalMaxDd(
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    const cy_stc_capsense_widget_context_t * ptrWdCxt = ptrWdConfig->ptrWdContext;
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt =  ptrWdConfig->ptrSnsContext;
    uint32_t thresholdOff = (uint32_t)ptrWdCxt->fingerTh - ptrWdCxt->hysteresis;
    uint32_t thresholdOn = (uint32_t)ptrWdCxt->fingerTh + ptrWdCxt->hysteresis;
    uint16_t currDiff;
    uint8_t rx;
    uint8_t tx;
    uint8_t snsShift;
    uint8_t lastRx = ptrWdConfig->numCols - 1u;
    uint8_t lastTx = ptrWdConfig->numRows - 1u;
    uint32_t proceed = 0u;
    uint32_t touchNum = 0u;
    cy_stc_capsense_position_t * ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0u];

    for (rx = CY_CAPSENSE_CSX_TOUCHPAD_MAX_PEAKS; rx-- > 0u;)
    {
        ptrNewPeak[rx].id = CY_CAPSENSE_CSX_TOUCHPAD_ID_UNDEFINED;
    }

    ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0u];
    /* Go through all Rx electrodes */
    for (rx = 0u; rx <= lastRx; rx++)
    {
        /*
        * Go through all Tx and RX (changed above) electrodes intersections
        * and check whether the local maximum requirement is met.
        */
        for (tx = 0u; tx <= lastTx; tx++)
        {
            proceed = 0u;
            currDiff = ptrSnsCxt->diff;
            if (thresholdOff <= (uint32_t)currDiff)
            {
                /*
                * Check local maximum requirement: Comparing raw count
                * of a local maximum candidate with raw counts of sensors
                * from the previous row.
                */
                if (rx > 0u)
                {
                    /* Check the sensor from the previous row and the next column */
                    snsShift = lastTx;
                    if ((tx < lastTx) && (currDiff <= (ptrSnsCxt - snsShift)->diff))
                    {
                        proceed = 1u;
                    }
                    if (0u == proceed)
                    {
                        /* Check the sensor from the previous row and the same column */
                        snsShift++;
                        if (currDiff <= (ptrSnsCxt - snsShift)->diff)
                        {
                            proceed = 1u;
                        }
                    }
                    if (0u == proceed)
                    {
                        /* Check the sensor from the previous row and the previous column */
                        snsShift++;
                        if ((tx > 0u) && (currDiff <= (ptrSnsCxt - snsShift)->diff))
                        {
                            proceed = 1u;
                        }
                    }
                }
                /*
                * Check local maximum requirement: Comparing raw count
                * of a local maximum candidate with raw counts of sensors
                * from the next row.
                */
                if ((0u == proceed) && (rx < lastRx))
                {
                    /* Check the sensor from the next row and the next column */
                    snsShift = lastTx + 2u;
                    if ((tx < lastTx) && (currDiff < (ptrSnsCxt + snsShift)->diff))
                    {
                        proceed = 1u;
                    }
                    if (0u == proceed)
                    {
                        /* Check the sensor from the next row and the same column */
                        snsShift--;
                        if (currDiff < (ptrSnsCxt + snsShift)->diff)
                        {
                            proceed = 1u;
                        }
                    }
                    if (0u == proceed)
                    {
                        /* Check the sensor from the next row and the previous column */
                        snsShift--;
                        if ((tx > 0u) && (currDiff < (ptrSnsCxt + snsShift)->diff))
                        {
                            proceed = 1u;
                        }
                    }
                }
                /*
                * Check local maximum requirement: Comparing raw count
                * of a local maximum candidate with raw counts of sensors
                * from the same row and the next column. */
                if ((0u == proceed) && (tx < lastTx))
                {
                    if (currDiff < (ptrSnsCxt + 1u)->diff)
                    {
                        proceed = 1u;
                    }
                }
                /* Check the sensor from the same row and the previous column */
                if ((0u == proceed) && (tx > 0u))
                {
                    if (currDiff <= (ptrSnsCxt - 1u)->diff)
                    {
                        proceed = 1u;
                    }
                }
                /* Add local maximum to the touch structure if there is room. */
                if (0u == proceed)
                {
                    ptrNewPeak->x = rx;
                    ptrNewPeak->y = tx;
                    if (currDiff < thresholdOn)
                    {
                        ptrNewPeak->id |= CY_CAPSENSE_CSX_TOUCHPAD_ID_ON_FAIL;
                    }
                    touchNum++;
                    ptrNewPeak++;
                }
            }
            ptrSnsCxt++;
            if (touchNum >= CY_CAPSENSE_CSX_TOUCHPAD_MAX_PEAKS)
            {
                break;
            }
        }
        if (touchNum >= CY_CAPSENSE_CSX_TOUCHPAD_MAX_PEAKS)
        {
            break;
        }
    }
    ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber = (uint8_t)touchNum;
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/* CY_ID633 */
#if defined(__ICCARM__)
    #pragma optimize=none
#endif /* (__ICCARM__) */
/*******************************************************************************
* Function Name: Cy_CapSense_DpCalcTouchPadCentroid
****************************************************************************//**
*
* Calculates the position for each local maximum using the 3x3 algorithm.
*
* This function calculates position coordinates of found local maximums.
* The found positions are stored in the CSX buffer ptrCsxTouchBuffer
* \ref cy_stc_capsense_csx_touch_buffer_t.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
void Cy_CapSense_DpCalcTouchPadCentroid(
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt =  ptrWdConfig->ptrSnsContext;
    uint8_t number;
    uint8_t i;
    uint8_t j;
    uint32_t lastRx = (uint32_t)ptrWdConfig->numCols - 1u;
    uint32_t lastTx = (uint32_t)ptrWdConfig->numRows - 1u;
    uint16_t centroid[3u][3u];
    int32_t weightedSumX;
    int32_t weightedSumY;
    uint32_t totalSum;
    uint32_t multiplierX;
    uint32_t offsetX;
    uint32_t multiplierY;
    uint32_t offsetY;
    uint32_t touchNum = ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber;
    cy_stc_capsense_position_t * ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0];

    for(number = 0u; number < touchNum; number++)
    {
        /* Set the sensor pointer to the local maximum sensor */
        ptrSnsCxt =  ptrWdConfig->ptrSnsContext;
        ptrSnsCxt += (ptrNewPeak->y + (ptrNewPeak->x * ptrWdConfig->numRows));

        /* Prepare 3x3 centroid two dimensional array */
        /* Fill each row */
        for (i = 0u; i < CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_LENGTH; i++)
        {
            /*
            * The first  condition could be valid only when local max on the first row (0 row) of Touchpad
            * The second condition could be valid only when local max on the last row of Touchpad
            * Then corresponding row (zero or the last) of 3x3 array is initialized to 0u
            */
            if (((((int32_t)ptrNewPeak->x - 1) + (int32_t)i) < 0) ||
                ((((int32_t)ptrNewPeak->x - 1) + (int32_t)i) > (int32_t)lastRx))
            {
                centroid[CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_PREVIOUS][i] = 0u;
                centroid[CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_CENTER][i] = 0u;
                centroid[CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_NEXT][i] = 0u;
            }
            else
            {
                /* Fill each column */
                for (j = 0u; j < CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_LENGTH; j++)
                {
                    /*
                    * The first condition could be valid only when local max
                    * on the first column (0 row) of Touchpad. The second
                    * condition could be valid only when local max on the last
                    * column of Touchpad. Then corresponding column (zero or
                    * the last) of 3x3 array is initialized to 0u.
                    */
                    if (((((int32_t)ptrNewPeak->y - 1) + (int32_t)j) < 0) ||
                        ((((int32_t)ptrNewPeak->y - 1) + (int32_t)j) > (int32_t)lastTx))
                    {
                        centroid[j][i] = 0u;
                    }
                    else
                    {
                        centroid[j][i] = (uint16_t)(ptrSnsCxt + (((i - 1u) * ptrWdConfig->numRows) + (j - 1u)))->diff; //MISRA?
                    }
                }
            }
        }

        weightedSumX = 0;
        weightedSumY = 0;
        totalSum = 0u;

        /* Calculate centroid */
        for (i = 0u; i < CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_LENGTH; i++)
        {
            for (j = 0u; j < CY_CAPSENSE_CSX_TOUCHPAD_CENTROID_LENGTH; j++)
            {
                totalSum += centroid[i][j];
                weightedSumX += (int32_t)centroid[i][j] * ((int32_t)j - 1);
                weightedSumY += (int32_t)centroid[i][j] * ((int32_t)i - 1);
            }
        }

        /* The X position is calculated.
        * The weightedSumX value depends on a finger position shifted regarding
        * the X electrode (ptrNewTouches.x).
        * The multiplier ptrWdConfig->xCentroidMultiplier is a short from:
        * CY_CAPSENSE_TOUCHPAD0_X_RESOLUTION * 256u) / (CY_CAPSENSE_TOUCHPAD0_NUM_RX - CONFIG))
        * where CONFIG = 0 or 1 depends on TouchpadMultiplerMethod parameter.
        */
        /* Calculate position */
        multiplierX = (uint32_t)ptrWdConfig->xResolution << 8u;
        multiplierY = (uint32_t)ptrWdConfig->yResolution << 8u;
        if (0u == (ptrWdConfig->centroidConfig & CY_CAPSENSE_CALC_METHOD_MASK))
        {
            multiplierX /= lastRx;
            offsetX = 0u;
            multiplierY /= lastTx;
            offsetY = 0u;
        }
        else
        {
            multiplierX /= (lastRx + 1u);
            offsetX = multiplierX >> 1u;
            multiplierY /= (lastTx + 1u);
            offsetY = multiplierY >> 1u;
        }

        weightedSumX = ((weightedSumX * (int32_t)multiplierX) / (int32_t)totalSum) +
                        ((((int32_t)ptrNewPeak->x) * (int32_t)multiplierX) + (int32_t)offsetX);

        /* The X position is rounded to the nearest integer value and normalized to the resolution range */
        ptrNewPeak->x = (uint16_t)(((uint32_t)weightedSumX + CY_CAPSENSE_CENTROID_ROUND_VALUE) >> 8u);
        /* The Y position is calculated.
        * The weightedSumY value depends on a finger position shifted regarding the Y electrode (ptrWdConfig->ptrNewTouches.y)
        * The multiplier ptrWdConfig->yCentroidMultiplier is a short from:
        * CY_CAPSENSE_TOUCHPAD0_Y_RESOLUTION * 256u) / (CY_CAPSENSE_TOUCHPAD0_NUM_TX - CONFIG))
        * where CONFIG = 0 or 1 depends on TouchpadMultiplerMethod parameter
        */
        weightedSumY = ((weightedSumY * (int32_t)multiplierY) / (int32_t)totalSum) +
                        ((((int32_t)ptrNewPeak->y) * (int32_t)multiplierY) + (int32_t)offsetY);

        /* The Y position is rounded to the nearest integer value and normalized to the resolution range */
        ptrNewPeak->y = (uint16_t)(((uint32_t)weightedSumY + CY_CAPSENSE_CENTROID_ROUND_VALUE) >> 8u);

        /* The z value is a sum of raw counts of sensors that form 3x3 matrix with a local maximum in the center */
        ptrNewPeak->z = (uint8_t)(totalSum >> CY_CAPSENSE_CSX_TOUCHPAD_Z_SHIFT);
        ptrNewPeak++;
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_DpTouchTracking
****************************************************************************//**
*
* Tracks touches.
*
* This function tracks the found touches:
* - associates them with previous touches applying the Hungarian algorithm.
* - applies debounce filters.
* - suppresses excessive touches.
*
* The final touch data are stored in the CSX buffer ptrCsxTouchBuffer
* \ref cy_stc_capsense_csx_touch_buffer_t. This function should be called
* each scan cycle even when touch is not detected.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
void Cy_CapSense_DpTouchTracking(
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t i;

    const cy_stc_capsense_position_t * ptrNewPeak;
    cy_stc_capsense_position_t * ptrOldPeak;

    uint32_t newTouchNum = ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber;
    uint32_t oldTouchNum = ptrWdConfig->ptrCsxTouchHistory->oldPeakNumber;

    int8_t * fingerPosIndex = &ptrWdConfig->ptrCsxTouchBuffer->fingerPosIndexMap[0u];

    if ((0u != newTouchNum) || (0u != oldTouchNum))
    {
        /* Initialize variables */
        ptrWdConfig->ptrCsxTouchBuffer->newActiveIdsMask = 0u;
        /* Getting active touch IDs from previous scan */
        ptrWdConfig->ptrCsxTouchHistory->oldActiveIdsMask = 0u;

        ptrOldPeak = &ptrWdConfig->ptrCsxTouchHistory->oldPeak[0u];
        for (i = 0u; i < oldTouchNum; i++)
        {
            ptrWdConfig->ptrCsxTouchHistory->oldActiveIdsMask |= (uint8_t)(1u << ptrOldPeak->id);
            ptrOldPeak++;
        }

        if (0u < newTouchNum)
        {
            if (0u == oldTouchNum)
            {
                /* If the previous touch tracking had not any touches */
                for (i = 0u; i < newTouchNum; i++)
                {
                    /* Initializes a new touch, set ID to next value and Age to 0 */
                    Cy_CapSense_NewTouch(i, ptrWdConfig);
                }
            }
            else
            {
                /* Don't call Hungarian for 1 current and 1 previous touch */
                fingerPosIndex[0u] = 0;
                if ((1u != newTouchNum) || (1u != oldTouchNum))
                {
                    Cy_CapSense_Hungarian(ptrWdConfig);
                }
                /* General case */
                if (newTouchNum >= oldTouchNum)
                {
                    ptrOldPeak = &ptrWdConfig->ptrCsxTouchHistory->oldPeak[0u];
                    for (i = 0u; i < oldTouchNum; i++)
                    {
                        if (ptrWdConfig->ptrCsxTouchHistory->velocity < Cy_CapSense_CalcDistance((uint32_t)fingerPosIndex[i], i, ptrWdConfig))
                        {
                            /* Set new ID and reset Age */
                            Cy_CapSense_NewTouch((uint32_t)fingerPosIndex[i], ptrWdConfig);
                        }
                        else
                        {
                            /* Set ID to previous value and increase Age */
                            ptrWdConfig->ptrCsxTouchBuffer->newActiveIdsMask |= (uint8_t)(1u << (ptrOldPeak->id));
                            Cy_CapSense_TransferTouch((uint32_t)fingerPosIndex[i], i, ptrWdConfig);
                        }
                        ptrOldPeak++;
                    }
                }
                else
                {
                    ptrOldPeak = &ptrWdConfig->ptrCsxTouchHistory->oldPeak[0u];
                    for (i = 0u; i < newTouchNum; i++)
                    {
                        if (ptrWdConfig->ptrCsxTouchHistory->velocity < Cy_CapSense_CalcDistance(i, (uint32_t)fingerPosIndex[i], ptrWdConfig))
                        {
                            /* Set new ID and reset Age. */
                            Cy_CapSense_NewTouch(i, ptrWdConfig);
                        }
                        else
                        {
                            /* Set ID to previous value and increase Age. */
                            ptrWdConfig->ptrCsxTouchBuffer->newActiveIdsMask |= (uint8_t)(1u << (ptrOldPeak->id));
                            Cy_CapSense_TransferTouch(i, (uint32_t)fingerPosIndex[i], ptrWdConfig);
                        }
                        ptrOldPeak++;
                    }
                }
                /* Added new fingers, they need to assign ID */
                if (newTouchNum > oldTouchNum)
                {
                    /* Search new fingers */
                    ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0u];
                    for (i = 0u; i < newTouchNum; i++)
                    {
                        /* New finger found */
                        if (0u != (ptrNewPeak->id & CY_CAPSENSE_CSX_TOUCHPAD_ID_UNDEFINED))
                        {
                            Cy_CapSense_NewTouch(i, ptrWdConfig);
                        }
                        ptrNewPeak++;
                    }
                }
            }

            Cy_CapSense_TouchDownDebounce(ptrWdConfig);
        }

        Cy_CapSense_SortByAge(ptrWdConfig);
        newTouchNum = ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber;

        /* Store new touches as old touches */
        ptrWdConfig->ptrCsxTouchHistory->oldPeakNumber = (uint8_t)newTouchNum;
        ptrWdConfig->ptrCsxTouchHistory->oldActiveIdsMask = ptrWdConfig->ptrCsxTouchBuffer->newActiveIdsMask;
        ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0u];
        ptrOldPeak = &ptrWdConfig->ptrCsxTouchHistory->oldPeak[0u];
        for (i = newTouchNum; i-- > 0u;)
        {
            Cy_CapSense_CopyTouchRecord(ptrOldPeak, ptrNewPeak);
            ptrNewPeak++;
            ptrOldPeak++;
        }
    }
 }
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_TransferTouch
****************************************************************************//**
*
* Transfers a touch from history array into active current array.
*
* This function transfers touch specified by oldIndex from history touch array
* by copying its ID, increments age and decrements debounce (if debounce > 0)
* parameters into currently active touch structure
*
* \param newIndex
* The touch index of touch array in the active touch structure.
*
* \param oldIndex
* The touch index of touch array in the history touch structure.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
static void Cy_CapSense_TransferTouch(
                uint32_t newIndex,
                uint32_t oldIndex,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t touchId;
    uint32_t touchAge;
    uint32_t touchDebounce;
    cy_stc_capsense_position_t * ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[newIndex];
    const cy_stc_capsense_position_t * ptrOldPeak = &ptrWdConfig->ptrCsxTouchHistory->oldPeak[oldIndex];

    touchId = (uint32_t)ptrOldPeak->id & CY_CAPSENSE_CSX_TOUCHPAD_ID_MASK;
    touchAge = ((uint32_t)ptrOldPeak->z & CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK) >> CY_CAPSENSE_CSX_TOUCHPAD_BYTE_SHIFT;
    touchDebounce = ((uint32_t)ptrOldPeak->id & CY_CAPSENSE_CSX_TOUCHPAD_DEBOUNCE_MASK) >> CY_CAPSENSE_CSX_TOUCHPAD_BYTE_SHIFT;

    /* Increase AGE by 1 if possible */
    if (touchAge < CY_CAPSENSE_CSX_TOUCHPAD_MAX_AGE)
    {
        touchAge++;
    }
    /* Decrement Debounce counter if possible */
    if (touchDebounce > 0u)
    {
        touchDebounce--;
    }

    ptrNewPeak->id = (uint16_t)(touchId | (uint16_t)(touchDebounce << CY_CAPSENSE_CSX_TOUCHPAD_BYTE_SHIFT));
    ptrNewPeak->z &= (uint16_t)~CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK;
    ptrNewPeak->z |= (uint16_t)(touchAge << CY_CAPSENSE_CSX_TOUCHPAD_BYTE_SHIFT);
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_NewTouch
****************************************************************************//**
*
* Set ID, age, and on debounce parameters for a new touch.
*
* If raw count is lower than the finger-On-Threshold,
* then the corresponding touch is marked with CY_CAPSENSE_CSX_TOUCHPAD_ID_ON_FAIL
* in the ID and will be deleted from the new touch structure in Cy_CapSense_SortByAge()
* (new touch structure is reorganized in this case).
*
* \param newIndex
* The touch index of touch array in the active touch structure.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
static void Cy_CapSense_NewTouch(
                uint32_t newIndex,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t idx;
    cy_stc_capsense_position_t * ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[newIndex];

    /* Touch is not accepted */
    if (0u == (ptrNewPeak->id & CY_CAPSENSE_CSX_TOUCHPAD_ID_ON_FAIL))
    {
        /* Create a bit map of ID's currently used and previously used and search for the new lowest ID */
        idx = Cy_CapSense_GetLowestId(ptrWdConfig->ptrCsxTouchHistory->oldActiveIdsMask |
                ptrWdConfig->ptrCsxTouchBuffer->newActiveIdsMask);

        /* Indicate that ID is now taken */
        ptrWdConfig->ptrCsxTouchBuffer->newActiveIdsMask |= (uint8_t)(1u << idx);

        /* Set AGE */
        ptrNewPeak->z &= (uint16_t)~CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK;
        ptrNewPeak->z |= CY_CAPSENSE_CSX_TOUCHPAD_AGE_START;

        /* Set ID and Debounce */
        ptrNewPeak->id = (uint16_t)idx | (uint16_t)(((uint16_t)ptrWdConfig->ptrWdContext->onDebounce - 1u) << CY_CAPSENSE_CSX_TOUCHPAD_BYTE_SHIFT);
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_GetLowestId
****************************************************************************//**
*
* Returns the lowest available free touch ID.
*
* \param idMask
* The mask of IDs used in active and history touch structures.
*
* \return
* Returns the lowest available touch ID. If no ID is available,
* CY_CAPSENSE_CSX_TOUCHPAD_ID_ABSENT is returned.
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_CapSense_GetLowestId(uint8_t idMask)
{
    uint32_t idx;
    uint32_t touchId = CY_CAPSENSE_CSX_TOUCHPAD_ID_ABSENT;
    uint32_t idMaskLocal = (uint32_t)idMask;

    /* Search for the lowest available ID */
    for (idx = CY_CAPSENSE_CSX_TOUCHPAD_ID_MIN; idx <= CY_CAPSENSE_CSX_TOUCHPAD_ID_MAX; idx++)
    {
        /* Determine whether the new ID is available */
        if (0u == (idMaskLocal & 1u))
        {
            touchId = idx;
            break;
        }

        idMaskLocal >>= 1u;
    }

    /* Return an indicator of failure */
    return (uint8_t)(touchId);
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_TouchDownDebounce
****************************************************************************//**
*
* Handles touchdown debouncing.
*
* Even if a new touch is detected, it is not considered as active until the
* debounce counter has not reached zero. If the debounce counter has reached zero,
* the touchdown mask is cleared. Otherwise the age of the new finger is cleared
* (it is considered as not active).
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CapSense_TouchDownDebounce(
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t i;
    cy_stc_capsense_position_t * ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0u];

    for (i = 0u; i < ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber; i++)
    {
        /* If it is a touchdown debouncing finger its age is set to zero */
        if (0u != (ptrNewPeak->id & CY_CAPSENSE_CSX_TOUCHPAD_DEBOUNCE_MASK))
        {
            /* Set the age to zero - finger is not active */
            ptrNewPeak->z &= (uint16_t)~CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK;
        }
        ptrNewPeak++;
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CalcDistance
****************************************************************************//**
*
* Calculates squared distance between history and active touch structures
* pointed by the input parameters.
*
* \param newIndex
* The index of touch in the active touch structure.
*
* \param oldIndex
* The index of touch in the history touch structure.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
* \return
* Returns the squared distance.
*
*******************************************************************************/
static uint32_t Cy_CapSense_CalcDistance(
                uint32_t newIndex,
                uint32_t oldIndex,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    const cy_stc_capsense_position_t * ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[newIndex];
    const cy_stc_capsense_position_t * ptrOldPeak = &ptrWdConfig->ptrCsxTouchHistory->oldPeak[oldIndex];

    int32_t xDistance = (int32_t)(ptrOldPeak->x) - (int32_t)(ptrNewPeak->x);
    int32_t yDistance = (int32_t)(ptrOldPeak->y) - (int32_t)(ptrNewPeak->y);

    xDistance *= xDistance;
    yDistance *= yDistance;

    return ((uint32_t)xDistance + (uint32_t)yDistance);
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_Hungarian
****************************************************************************//**
*
* Executes the Hungarian method on a distance map to track motion of two
* touch sets (old touches vs new touches).
*
* This function uses the Hungarian method described in specification 001-63362.
* There is no bound checking on the parameters. It is the calling function's
* responsibility to ensure parameter validity.
* The function output is a fingerPosIndexMap array stored in the CSX buffer
* where associations between the previous and current touches are returned.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
static void Cy_CapSense_Hungarian(
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    cy_stc_capsense_csx_touch_buffer_t * ptrBuffer = ptrWdConfig->ptrCsxTouchBuffer;
    /*
    * Number of elements in column of distanceMap matrix. This value must
    * be greater than or equal to 1.
    */
    int32_t * col = &ptrBuffer->colMap[0u];
    /*
    * Number of elements in row of distanceMap matrix. This value must be
    * greater than or equal to colCount.
    */
    int32_t * row = &ptrBuffer->rowMap[0u];
    int32_t * mins = &ptrBuffer->minsMap[0u];
    int8_t * links = &ptrBuffer->linksMap[0u];
    int8_t * visited = &ptrBuffer->visitedMap[0u];
    int8_t * markIndices = &ptrBuffer->markIndicesMap[0u];
    /*
    * The 2-dimensional map of distances between the nodes in each
    * coordinate set. The 1st index of distanceMap corresponds to nodes
    * in the 1st coordinate data set, and the 2nd index of distanceMap
    * corresponds to the 2nd coordinate data set. Each element in
    * distanceMap is the square of the distance between the
    * corresponding coordinates in the 1st and 2nd data set.
    */
    int32_t * distance = &ptrBuffer->distanceMap[0u];

    int32_t delta = 0;
    int32_t colValue = 0;
    int32_t markedI = 0;
    int32_t markedJ = 0;
    int32_t i = 0;
    int32_t iIndex = 0;
    int32_t j = 0;
    int32_t jIndex = 0;

    uint32_t rowCount = ptrBuffer->newPeakNumber;
    uint32_t colCount = ptrWdConfig->ptrCsxTouchHistory->oldPeakNumber;

    /* Fill distance map */
    if (rowCount >= colCount)
    {
        for (i = (int32_t)rowCount; i-- > 0; )
        {
            for (j = (int32_t)colCount; j-- > 0; )
            {
                distance[((uint32_t)i * CY_CAPSENSE_CSX_TOUCHPAD_MAX_PEAKS) + (uint32_t)j] = (int32_t)Cy_CapSense_CalcDistance((uint32_t)i, (uint32_t)j, ptrWdConfig);
            }
        }
    }
    else
    {
        for (i = (int32_t)colCount; i-- > 0;)
        {
            for (j = (int32_t)rowCount; j-- > 0;)
            {
                distance[((uint32_t)i * CY_CAPSENSE_CSX_TOUCHPAD_MAX_PEAKS) + (uint32_t)j] = (int32_t)Cy_CapSense_CalcDistance((uint32_t)j, (uint32_t)i, ptrWdConfig);
            }
        }
        colValue = (int32_t)colCount;
        colCount = rowCount;
        rowCount = (uint32_t)colValue;
    }

    (void)memset(col, 0, (uint32_t)colCount * 4u);

    /* Initialize row and markIndices arrays */
    for (i = (int32_t)rowCount; i-- > 0;)
    {
        row[i] = 0;
        markIndices[i] = -1;
    }

    /* Go through all columns */
    for (i = (int32_t)colCount; i-- > 0;)
    {
        /* Initialize visited, links, mins arrays. They are used for every column */
        for (iIndex = (int32_t)rowCount; iIndex-- > 0;)
        {
            visited[iIndex] = 0;
            links[iIndex] = -1;
            mins[iIndex] = INT32_MAX;
        }

        /* Next two variables are used to mark column and row */
        markedI = i;
        markedJ = -1;

        while (markedI != -1)
        {
            j = -1;
            colValue = col[markedI];

            /* Go through all rows */
            for (jIndex = (int32_t)rowCount; jIndex-- > 0;)
            {
                if (visited[jIndex] == 0)
                {
                    delta = distance[((uint32_t)jIndex * CY_CAPSENSE_CSX_TOUCHPAD_MAX_PEAKS) + (uint32_t)markedI] - row[jIndex] - colValue;

                    /* Find the minimum element index in column i */
                    if (mins[jIndex] > delta)
                    {
                        mins[jIndex] = delta;
                        links[jIndex] = (int8_t)markedJ;
                    }

                    if ((j == -1) || (mins[jIndex] < mins[j]))
                    {
                        j = jIndex;
                    }
                }
            }

            if(j == -1)
            {
                j = 0;
            }

            delta = mins[j];

            /* Go through all rows */
            for (jIndex = (int32_t)rowCount; jIndex-- > 0;)
            {
                if (visited[jIndex] != 0)
                {
                    col[markIndices[jIndex]] += delta;
                    row[jIndex] -= delta;
                }
                else
                {
                    mins[jIndex] -= delta;
                }
            }

            col[i] +=  delta;

            visited[j] = 1;
            markedJ = j;
            markedI = markIndices[j];
        }

        while (links[j] != -1)
        {
            markIndices[j] = markIndices[links[j]];
            j = links[j];
        }

        markIndices[j] = (int8_t)i;
    }

    /* Provide an association between two sets of touches */
    for (j = (int32_t)rowCount; j-- > 0;)
    {
        if (markIndices[j] != -1)
        {
            ptrBuffer->fingerPosIndexMap[markIndices[j]] = (int8_t)j;
        }
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_SortByAge
****************************************************************************//**
*
* Sorts the new touch array by:
* 1. age (in decrementing order)
* and
* 2. id (in incrementing order) fields.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CapSense_SortByAge(
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t i;
    uint32_t j;
    cy_stc_capsense_position_t tempPeak;
    cy_stc_capsense_position_t * ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0u];
    cy_stc_capsense_position_t * ptrNewPeakJ;
    uint32_t newTouchNum = ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber;

    /*
     * Delete failed touch by coping (rewriting) the last touch content to the failed touch.
     * If the last touch record is invalid, try the penultimate touch record and so on.
     */
    for (i = 0u; i < newTouchNum; i++)
    {
        if ((ptrNewPeak->id & CY_CAPSENSE_CSX_TOUCHPAD_ID_MASK) > CY_CAPSENSE_CSX_TOUCHPAD_ID_MAX)
        {
            for (j = (newTouchNum - 1u); j > i; j--)
            {
                /*
                * Check the touch records from the last to the current.
                * If the touch record is valid, then replace the current touch record.
                */
                ptrNewPeakJ = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[j];
                if ((ptrNewPeakJ->id & CY_CAPSENSE_CSX_TOUCHPAD_ID_MASK) <= CY_CAPSENSE_CSX_TOUCHPAD_ID_MAX)
                {
                    Cy_CapSense_CopyTouchRecord(ptrNewPeak, ptrNewPeakJ);

                    /* Finish the loop. The valid touch record is found and copied. */
                    break;
                }
                else
                {
                    /* Decrement the number of touch records.
                     * The last touch record is invalid - try the penultimate touch record.
                     */
                    newTouchNum--;
                }
            }

            /* Decrement the number of touch records.
             * The last touch record is valid and copied to the current position (i)
             */
            newTouchNum--;
        }
        ptrNewPeak++;
    }

    /* Set new number of touches */
    ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber = (uint8_t)newTouchNum;

    ptrNewPeak = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[0u];
    /* Sort new touches structure */
    for (i = 0u; i < newTouchNum; i++)
    {
        for (j = (i + 1u); j < newTouchNum; j++)
        {
            ptrNewPeakJ = &ptrWdConfig->ptrCsxTouchBuffer->newPeak[j];
            /* If next touches have higher age or lower id with the same age then swap touches */
            if (((ptrNewPeak->z & CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK) < (ptrNewPeakJ->z & CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK)) ||
                (((ptrNewPeak->z & CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK) == (ptrNewPeakJ->z & CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK)) && (ptrNewPeak->id > ptrNewPeakJ->id)))
            {
                /* Swap touches */
                Cy_CapSense_CopyTouchRecord(&tempPeak, ptrNewPeak);
                Cy_CapSense_CopyTouchRecord(ptrNewPeak, ptrNewPeakJ);
                Cy_CapSense_CopyTouchRecord(ptrNewPeakJ, &tempPeak);
            }
        }
        ptrNewPeak++;
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CopyTouchRecord
****************************************************************************//**
*
* Copies content from the source touch structure to the destination touch structure.
*
* \param destination
* The pointer to the destination touch structure \ref cy_stc_capsense_position_t.
*
* \param source
* The pointer to the source touch structure \ref cy_stc_capsense_position_t.
*
*******************************************************************************/
static void Cy_CapSense_CopyTouchRecord(
                cy_stc_capsense_position_t * destination,
                const cy_stc_capsense_position_t * source)
{
    *destination = *source;
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_DpFilterTouchRecord
****************************************************************************//**
*
* Filters position data of every valid touch if enabled and copies data into
* public touch array.
*
* This function checks every touch in the new touch structure. If the touch is
* valid (valid id and age > 0), then touch is filtered if the filter is enabled.
* At the end, the corresponding fields are updated in the public touch structure.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
void Cy_CapSense_DpFilterTouchRecord(
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t i;
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_POSITION_FILTER_EN)
        uint32_t j;
    #endif
    uint32_t reportedTouchNum = 0u;
    uint32_t peakNum = ptrWdConfig->ptrCsxTouchBuffer->newPeakNumber;
    uint32_t maxTouch;
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_POSITION_FILTER_EN)
        uint32_t filterSize;
        uint32_t newTouchFlag = 0u;
    #endif

    cy_stc_capsense_position_t * ptrWdTouch = ptrWdConfig->ptrWdContext->wdTouch.ptrPosition;
    cy_stc_capsense_position_t * ptrNewPeak = ptrWdConfig->ptrCsxTouchBuffer->newPeak;
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_POSITION_FILTER_EN)
        cy_stc_capsense_position_t * ptrHistory;
        uint32_t historyFlag[CY_CAPSENSE_MAX_CENTROIDS] = {0u};
    #endif

    /* Define number of touches that should be reported */
    for (i = 0u; i < CY_CAPSENSE_MAX_CENTROIDS; i++)
    {
        /*
        * Age must be higher than 0 otherwise the touch does not pass
        * debounce procedure. It exists in the array for correct
        * touch tracking and debouncing.
        */
        if ((i < peakNum) && ((ptrNewPeak->z & CY_CAPSENSE_CSX_TOUCHPAD_AGE_MASK) > 0u))
        {
            reportedTouchNum++;
        }
        ptrNewPeak++;
    }

    maxTouch = (uint32_t)ptrWdConfig->centroidConfig & CY_CAPSENSE_CENTROID_NUMBER_MASK;
    if (reportedTouchNum > maxTouch)
    {
        reportedTouchNum = maxTouch;
    }

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_POSITION_FILTER_EN)
    if (0u != (ptrWdConfig->posFilterConfig & CY_CAPSENSE_POSITION_FILTERS_MASK))
    {
        filterSize = (ptrWdConfig->posFilterConfig & CY_CAPSENSE_POSITION_FILTERS_SIZE_MASK) >>
                        CY_CAPSENSE_POSITION_FILTERS_SIZE_OFFSET;

        /* Go through all new touches */
        ptrNewPeak = ptrWdConfig->ptrCsxTouchBuffer->newPeak;
        for (i = 0u; i < reportedTouchNum; i++)
        {
            newTouchFlag = 0u;
            /* Find index in the history array that corresponds to the new touch */
            ptrHistory = ptrWdConfig->ptrPosFilterHistory->ptrPosition;
            for (j = 0u; j < maxTouch; j++)
            {
                /* ID must match */
                if (ptrHistory->id == ptrNewPeak->id)
                {
                    /* Filter X and Y position of touch that exists from previous scan */
                    Cy_CapSense_RunPositionFilters(ptrWdConfig, ptrNewPeak, ptrHistory);
                    /* Mark history touch as assigned */
                    historyFlag[j] = 1u;
                    newTouchFlag = 1u;
                    /* Because the touch is found and processed, go to the next new touch */
                    break;
                }
                ptrHistory += filterSize;
            }
            /* The touch is not found in history */
            if (0u == newTouchFlag)
            {
                /* Find a place to keep history and initialize it */
                ptrHistory = ptrWdConfig->ptrPosFilterHistory->ptrPosition;
                for (j = 0u; j < maxTouch; j++)
                {
                    if (0u == historyFlag[j])
                    {
                        Cy_CapSense_InitPositionFilters(ptrWdConfig->posFilterConfig,
                                                        ptrNewPeak,
                                                        ptrHistory);
                        historyFlag[j] = 1u;
                        /* Assignment is done; go to the next new touch */
                        break;
                    }
                    ptrHistory += filterSize;
                }
            }
            ptrNewPeak++;
        }
        /* Reset all non-assigned history IDs */
        ptrHistory = ptrWdConfig->ptrPosFilterHistory->ptrPosition;
        for (j = 0u; j < maxTouch; j++)
        {
            if (0u == historyFlag[j])
            {
                ptrHistory->id = CY_CAPSENSE_CSX_TOUCHPAD_ID_UNDEFINED;
            }
            ptrHistory += filterSize;
        }
    }
    #endif /*(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_POSITION_FILTER_EN)*/

    /* Go through all touch fields in the data structure */
    ptrNewPeak = ptrWdConfig->ptrCsxTouchBuffer->newPeak;
    for (i = 0u; i < maxTouch; i++)
    {
        ptrWdTouch->id = CY_CAPSENSE_CSX_TOUCHPAD_ID_UNDEFINED;

        if (i < reportedTouchNum)
        {
            /* Report touch to the data structure */
            ptrWdTouch->x = ptrNewPeak->x;
            ptrWdTouch->y = ptrNewPeak->y;
            ptrWdTouch->z = ptrNewPeak->z;
            ptrWdTouch->id = ptrNewPeak->id;
        }
        ptrNewPeak++;
        ptrWdTouch++;
    }

    ptrWdConfig->ptrWdContext->wdTouch.numPosition = (uint8_t)reportedTouchNum;
    if (0u == reportedTouchNum)
    {
        ptrWdConfig->ptrWdContext->status &= (uint8_t)~CY_CAPSENSE_WD_ACTIVE_MASK;
    }
    else
    {
        ptrWdConfig->ptrWdContext->status = CY_CAPSENSE_WD_ACTIVE_MASK;
    }
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN) */


#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POSITION_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_InitPositionFilters
****************************************************************************//**
*
* Initializes history of touch structures by provided current touch states.
*
* \param filterConfig
* The configuration of filters of the widget.
*
* \param ptrInput
* The pointer to the position structure that holds currently detected
* position values.
*
* \param ptrHistory
* The pointer to the position structure that holds previous historical
* position values.
*
*******************************************************************************/
void Cy_CapSense_InitPositionFilters(
                uint32_t filterConfig,
                const cy_stc_capsense_position_t * ptrInput,
                cy_stc_capsense_position_t * ptrHistory)
{
    cy_stc_capsense_position_t * ptrHistoryIndex = ptrHistory;

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_MEDIAN_FILTER_EN)
        if (0u != (filterConfig & CY_CAPSENSE_POSITION_MED_MASK))
        {
            *ptrHistoryIndex = *ptrInput;
            ptrHistoryIndex++;
            *ptrHistoryIndex = *ptrInput;
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_IIR_FILTER_EN)
        if (0u != (filterConfig & CY_CAPSENSE_POSITION_IIR_MASK))
        {
            *ptrHistoryIndex = *ptrInput;
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_ADAPTIVE_FILTER_EN)
        if (0u != (filterConfig & CY_CAPSENSE_POSITION_AIIR_MASK))
        {
            ptrHistoryIndex->x = ptrInput->x;
            ptrHistoryIndex->y = ptrInput->y;
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_AVERAGE_FILTER_EN)
        if (0u != (filterConfig & CY_CAPSENSE_POSITION_AVG_MASK))
        {
            *ptrHistoryIndex = *ptrInput;
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_JITTER_FILTER_EN)
        if (0u != (filterConfig & CY_CAPSENSE_POSITION_JIT_MASK))
        {
            *ptrHistoryIndex = *ptrInput;
            ptrHistoryIndex++;
        }
    #endif
}


/*******************************************************************************
* Function Name: Cy_CapSense_RunPositionFilters
****************************************************************************//**
*
* Applies enabled filters to position specified by ptrInput argument and stores
* history into ptrHistory.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
* \param ptrInput
* The pointer to the position structure that holds currently detected
* position values.
*
* \param ptrHistory
* The pointer to the position structure that holds previous historical
* position values.
*
*******************************************************************************/
void Cy_CapSense_RunPositionFilters(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_position_t * ptrInput,
                cy_stc_capsense_position_t * ptrHistory)
{
    #if (CY_CAPSENSE_POS_MEDIAN_FILTER_EN || CY_CAPSENSE_POS_AVERAGE_FILTER_EN)
        uint32_t temp;
    #endif
    uint32_t xPos = ptrInput->x;
    uint32_t yPos = ptrInput->y;
    cy_stc_capsense_position_t * ptrHistoryIndex = ptrHistory;
    uint32_t filterCfg = ptrWdConfig->posFilterConfig;
    #if (0u != CY_CAPSENSE_POS_IIR_FILTER_EN)
        uint32_t coeffIIR = (uint32_t)(filterCfg & CY_CAPSENSE_POSITION_IIR_COEFF_MASK) >> CY_CAPSENSE_POSITION_IIR_COEFF_OFFSET;
    #endif

    #if (0u != CY_CAPSENSE_POS_MEDIAN_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_MED_MASK))
        {
            temp = Cy_CapSense_FtMedian((uint32_t)ptrHistoryIndex[1u].x, (uint32_t)ptrHistoryIndex[0u].x, xPos);
            ptrHistoryIndex[1u].x = ptrHistoryIndex[0u].x;
            ptrHistoryIndex[0u].x = (uint16_t)xPos;
            xPos = temp;
            temp = Cy_CapSense_FtMedian((uint32_t)ptrHistoryIndex[1u].y, (uint32_t)ptrHistoryIndex[0u].y, yPos);
            ptrHistoryIndex[1u].y = ptrHistoryIndex[0u].y;
            ptrHistoryIndex[0u].y = (uint16_t)yPos;
            yPos = temp;
            ptrHistoryIndex++;
            ptrHistoryIndex++;
        }
    #endif

    #if (0u != CY_CAPSENSE_POS_IIR_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_IIR_MASK))
        {
            xPos = Cy_CapSense_FtIIR1stOrder(xPos, (uint32_t)ptrHistoryIndex->x, coeffIIR);
            ptrHistoryIndex->x = (uint16_t)xPos;
            yPos = Cy_CapSense_FtIIR1stOrder(yPos, (uint32_t)ptrHistoryIndex->y, coeffIIR);
            ptrHistoryIndex->y = (uint16_t)yPos;
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_ADAPTIVE_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_AIIR_MASK))
        {
            Cy_CapSense_AdaptiveFilterRun_Lib(&ptrWdConfig->aiirConfig, ptrHistoryIndex, &xPos, &yPos);
            ptrHistoryIndex++;
        }
    #endif

    #if (0u != CY_CAPSENSE_POS_AVERAGE_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_AVG_MASK))
        {
            temp = xPos;
            xPos = (xPos + ptrHistoryIndex->x) >> 1u;
            ptrHistoryIndex->x = (uint16_t)temp;
            temp = yPos;
            yPos = (yPos + ptrHistoryIndex->y) >> 1u;
            ptrHistoryIndex->y = (uint16_t)temp;
            ptrHistoryIndex++;
        }
    #endif

    #if (0u != CY_CAPSENSE_POS_JITTER_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_JIT_MASK))
        {
            xPos = Cy_CapSense_FtJitter(xPos, (uint32_t)ptrHistoryIndex->x);
            ptrHistoryIndex->x = (uint16_t)xPos;
            yPos = Cy_CapSense_FtJitter(yPos, (uint32_t)ptrHistoryIndex->y);
            ptrHistoryIndex->y = (uint16_t)yPos;
        }
    #endif
    ptrInput->x = (uint16_t)xPos;
    ptrInput->y = (uint16_t)yPos;
}

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_POSITION_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_RunPositionFiltersRadial
****************************************************************************//**
*
* Applies enabled filters to position specified by the ptrInput argument and stores
* history into ptrHistory. Filtering considers specific widget type where
* the next value after maximum position is zero and vise versa.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
* \param ptrInput
* The pointer to the position structure that holds currently detected
* position values.
*
* \param ptrHistory
* The pointer to the position structure that holds previous historical
* position values.
*
*******************************************************************************/
void Cy_CapSense_RunPositionFiltersRadial(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_position_t * ptrInput,
                cy_stc_capsense_position_t * ptrHistory)
{
    /*
    * If new position crosses the zero point in one or another direction,
    * the position variable with the smaller value is increased by the
    * slider resolution. This is done for the proper filtering. For
    * example, xResolution = 100, currPosition = 95, newPosition = 5.
    * If no actions are taken, then the average filter will give a value of
    * 50 - which is wrong. But if the position values are adjusted as
    * mentioned here, we will get newPosition equal 105 and the average
    * will be 100. Later this filtered value will be adjusted further
    * to not cross the xResolution and it will end up with 0u - which
    * is correct average result for the provided example.
    */

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_MEDIAN_FILTER_EN)
        uint32_t z1;
        uint32_t z2;
    #endif
    #if (CY_CAPSENSE_POS_IIR_FILTER_EN || CY_CAPSENSE_ADAPTIVE_FILTER_EN || CY_CAPSENSE_POS_AVERAGE_FILTER_EN)
        uint32_t temp;
    #endif
    /* The register contains max position value, so therefore it is increased by 1 */
    uint32_t centroidResolution = (uint32_t)ptrWdConfig->xResolution + 1u;
    uint32_t halfResolution = centroidResolution >> 1u;
    uint32_t xPos = ptrInput->x;
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_ADAPTIVE_FILTER_EN)
        uint32_t yPos = 0u;
    #endif
    cy_stc_capsense_position_t * ptrHistoryIndex = ptrHistory;
    uint32_t filterCfg = ptrWdConfig->posFilterConfig;
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_IIR_FILTER_EN)
        uint32_t coeffIIR = (uint32_t)(filterCfg & CY_CAPSENSE_POSITION_IIR_COEFF_MASK) >> CY_CAPSENSE_POSITION_IIR_COEFF_OFFSET;
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_MEDIAN_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_MED_MASK))
        {
            /* Get the filter history for further zero-cross correction */
            z1 = ptrHistoryIndex[0u].x;
            z2 = ptrHistoryIndex[1u].x;
            /* Preserve the filter history without zero-cross correction */
            ptrHistoryIndex[1u].x = ptrHistoryIndex[0u].x;
            ptrHistoryIndex[0u].x = (uint16_t)xPos;

            /* Perform zero-cross correction */
            if (z1 > (halfResolution + xPos))
            {
                xPos += centroidResolution;
            }
            if (xPos > (halfResolution + z1))
            {
                z1 += centroidResolution;
                z2 += centroidResolution;
            }
            if (z2 > (halfResolution + z1))
            {
                z1 += centroidResolution;
                xPos += centroidResolution;
            }
            if (z1 > (halfResolution + z2))
            {
                z2 += centroidResolution;
            }

            /* Perform filtering */
            xPos = Cy_CapSense_FtMedian(z2, z1, xPos);
            /* Perform zero-cross correction of filtered position */
            if (xPos >= centroidResolution)
            {
                xPos -= centroidResolution;
            }
            ptrHistoryIndex++;
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_IIR_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_IIR_MASK))
        {
            /* Perform zero-cross correction */
            if (ptrHistoryIndex->x > (halfResolution + xPos))
            {
                xPos += centroidResolution;
            }
            if (xPos > (halfResolution + ptrHistoryIndex->x))
            {
                ptrHistoryIndex->x += (uint16_t)centroidResolution;
            }
            if (ptrHistoryIndex->x > xPos)
            {
                temp = ptrHistoryIndex->x - xPos;
            }
            else
            {
                temp = xPos - ptrHistoryIndex->x;
            }

            /*
            * IIR filter can accumulate a delay up to a full circle and even more.
            * This situation is not supported by the middleware. If the difference
            * between the new position and IIR filter history is bigger than
            * half of resolution, then all enabled position filters are reset.
            */
            if(temp >= halfResolution)
            {
                /* Perform Initialization */
                Cy_CapSense_InitPositionFilters(filterCfg, ptrInput, ptrHistory);
            }
            else
            {
                /* Perform filtering */
                xPos = Cy_CapSense_FtIIR1stOrder(xPos, (uint32_t)ptrHistoryIndex->x, coeffIIR);
                /* Perform zero-cross correction of filtered position */
                if (xPos >= centroidResolution)
                {
                    xPos -= centroidResolution;
                }
                ptrHistoryIndex->x = (uint16_t)xPos;
            }
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_ADAPTIVE_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_AIIR_MASK))
        {
            /* Perform zero-cross correction */
            if (ptrHistoryIndex->x > (halfResolution + xPos))
            {
                xPos += centroidResolution;
            }
            if (xPos > (halfResolution + ptrHistoryIndex->x))
            {
                ptrHistoryIndex->x += (uint16_t)centroidResolution;
            }
            if (ptrHistoryIndex->x > xPos)
            {
                temp = ptrHistoryIndex->x - xPos;
            }
            else
            {
                temp = xPos - ptrHistoryIndex->x;
            }

            /*
            * IIR filter can accumulate delay up to full circle and even more.
            * This situation is not supported by the middleware. If the difference
            * between the new position and IIR filter history is bigger than
            * half of resolution, then all enabled position filters are reset.
            */
            if(temp >= halfResolution)
            {
                /* Perform Initialization */
                Cy_CapSense_InitPositionFilters(filterCfg, ptrInput, ptrHistory);
            }
            else
            {
                /* Perform filtering */
                Cy_CapSense_AdaptiveFilterRun_Lib(&ptrWdConfig->aiirConfig, ptrHistoryIndex, &xPos, &yPos);
                /* Perform zero-cross correction of filtered position */
                if (xPos >= centroidResolution)
                {
                    xPos -= centroidResolution;
                }
                ptrHistoryIndex->x = (uint16_t)xPos;
            }
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_AVERAGE_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_AVG_MASK))
        {
            temp = xPos;
            /* Perform zero-cross correction */
            if (ptrHistoryIndex->x > (halfResolution + xPos))
            {
                xPos += centroidResolution;
            }
            if (xPos > (halfResolution + ptrHistoryIndex->x))
            {
                ptrHistoryIndex->x += (uint16_t)centroidResolution;
            }
            /* Perform filtering */
            xPos = (xPos + ptrHistoryIndex->x) >> 1u;
            /* Perform zero-cross correction of filtered position */
            if (xPos >= centroidResolution)
            {
                xPos -= centroidResolution;
            }
            ptrHistoryIndex->x = (uint16_t)temp;
            ptrHistoryIndex++;
        }
    #endif

    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_JITTER_FILTER_EN)
        if (0u != (filterCfg & CY_CAPSENSE_POSITION_JIT_MASK))
        {
            /* Perform zero-cross correction */
            if (ptrHistoryIndex->x > (halfResolution + xPos))
            {
                xPos += centroidResolution;
            }
            if (xPos > (halfResolution + ptrHistoryIndex->x))
            {
                ptrHistoryIndex->x += (uint16_t)centroidResolution;
            }
            /* Perform filtering */
            xPos = Cy_CapSense_FtJitter(xPos, (uint32_t)ptrHistoryIndex->x);
            /* Perform zero-cross correction of filtered position */
            if (xPos >= centroidResolution)
            {
                xPos -= centroidResolution;
            }
            ptrHistoryIndex->x = (uint16_t)xPos;
        }
    #endif

    ptrInput->x = (uint16_t)xPos;
}
#endif /*(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_POSITION_FILTER_EN)*/

/*******************************************************************************
* Function Name: Cy_CapSense_ProcessPositionFilters
****************************************************************************//**
*
* Performs filtering of touch positions applying enabled filters.
*
* \param newTouch
* The pointer to the touch structure.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure
* \ref cy_stc_capsense_widget_config_t.
*
*******************************************************************************/
void Cy_CapSense_ProcessPositionFilters(
                cy_stc_capsense_touch_t * newTouch,
                const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    uint32_t posIndex;
    uint32_t filterCfg;
    uint32_t numPosMin;
    uint32_t filterSize;
    cy_stc_capsense_position_t * ptrHistory;
    cy_stc_capsense_position_t * ptrPos;
    uint32_t numPos = newTouch->numPosition;

    /* Position filtering */
    if ((CY_CAPSENSE_POSITION_NONE != numPos) && (CY_CAPSENSE_POSITION_MULTIPLE != numPos))
    {
        filterCfg = ptrWdConfig->posFilterConfig;
        numPosMin = ptrWdConfig->ptrPosFilterHistory->numPosition;
        ptrPos = newTouch->ptrPosition;
        ptrHistory = ptrWdConfig->ptrPosFilterHistory->ptrPosition;
        filterSize = (filterCfg & CY_CAPSENSE_POSITION_FILTERS_SIZE_MASK) >> CY_CAPSENSE_POSITION_FILTERS_SIZE_OFFSET;

        /* The same actions should be done for cases with no touches or multiple touches */
        if (CY_CAPSENSE_POSITION_MULTIPLE == numPosMin)
        {
            numPosMin = CY_CAPSENSE_POSITION_NONE;
        }

        /* Find number of position that exists from previous processing */
        if (numPosMin > numPos)
        {
            numPosMin = numPos;
        }

        /* Process touches that exists from previous processing */
        #if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_RADIAL_SLIDER_EN) &&\
            (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_POSITION_FILTER_EN))
            if((uint8_t)CY_CAPSENSE_WD_RADIAL_SLIDER_E == ptrWdConfig->wdType)
            {
                for (posIndex = 0u; posIndex < numPosMin; posIndex++)
                {
                    Cy_CapSense_RunPositionFiltersRadial(ptrWdConfig, ptrPos, ptrHistory);
                    ptrPos++;
                    ptrHistory += filterSize;
                }
            }
            else
            {
                for (posIndex = 0u; posIndex < numPosMin; posIndex++)
                {
                    Cy_CapSense_RunPositionFilters(ptrWdConfig, ptrPos, ptrHistory);
                    ptrPos++;
                    ptrHistory += filterSize;
                }
            }
        #else
            for (posIndex = 0u; posIndex < numPosMin; posIndex++)
            {
                Cy_CapSense_RunPositionFilters(ptrWdConfig, ptrPos, ptrHistory);
                ptrPos++;
                ptrHistory += filterSize;
            }
        #endif
        /* Initialize all rest newly detected touches */
        for (; posIndex < numPos; posIndex++)
        {
            Cy_CapSense_InitPositionFilters(filterCfg, ptrPos, ptrHistory);
            ptrPos++;
            ptrHistory += filterSize;
        }
    }
    /* Finally, copy number of positions */
    ptrWdConfig->ptrPosFilterHistory->numPosition = (uint8_t)numPos;
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POSITION_FILTER_EN) */
#endif /* ((CY_CAPSENSE_DISABLE != CY_CAPSENSE_SLIDER_EN) || (CY_CAPSENSE_DISABLE != CY_CAPSENSE_TOUCHPAD_EN)) */
#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

/* [] END OF FILE */
