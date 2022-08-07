/***************************************************************************//**
* \file cy_capsense_centroid.h
* \version 3.0
*
* \brief
* This file provides the function prototypes for the centroid calculation
* methods.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_CENTROID_H)
#define CY_CAPSENSE_CENTROID_H

#include "cy_capsense_lib.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cycfg_capsense_defines.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))
#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_SLIDER_EN) || (CY_CAPSENSE_DISABLE != CY_CAPSENSE_TOUCHPAD_EN))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Function Prototypes - internal functions
*******************************************************************************/

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/

#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_LINEAR_SLIDER_EN) ||\
    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_LINEAR_SLIDER_EN))
    void Cy_CapSense_DpCentroidLinear(
                    cy_stc_capsense_touch_t * newTouch,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_RADIAL_SLIDER_EN)
    void Cy_CapSense_DpCentroidRadial(
                    cy_stc_capsense_touch_t * newTouch,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_DIPLEX_SLIDER_EN) ||\
    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_DIPLEX_SLIDER_EN))
    void Cy_CapSense_DpCentroidDiplex(
                    cy_stc_capsense_touch_t * newTouch,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN)
    void Cy_CapSense_DpCentroidTouchpad(
                    cy_stc_capsense_touch_t * newTouch,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_ADVANCED_CENTROID_5X5_EN)
    void Cy_CapSense_DpAdvancedCentroidTouchpad(
                    cy_stc_capsense_touch_t * newTouch,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    void Cy_CapSense_DpFindLocalMaxDd(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    void Cy_CapSense_DpCalcTouchPadCentroid(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    void Cy_CapSense_DpTouchTracking(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    void Cy_CapSense_DpFilterTouchRecord(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POSITION_FILTER_EN)
    void Cy_CapSense_InitPositionFilters(
                    uint32_t filterConfig,
                    const cy_stc_capsense_position_t * ptrInput,
                    cy_stc_capsense_position_t * ptrHistory);
    void Cy_CapSense_RunPositionFilters(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    cy_stc_capsense_position_t * ptrInput,
                    cy_stc_capsense_position_t * ptrHistory);
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_POSITION_FILTER_EN)
        void Cy_CapSense_RunPositionFiltersRadial(
                        const cy_stc_capsense_widget_config_t * ptrWdConfig,
                        cy_stc_capsense_position_t * ptrInput,
                        cy_stc_capsense_position_t * ptrHistory);
    #endif
    void Cy_CapSense_ProcessPositionFilters(
                    cy_stc_capsense_touch_t * newTouch,
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif
/** \} \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* ((CY_CAPSENSE_DISABLE != CY_CAPSENSE_SLIDER_EN) || (CY_CAPSENSE_DISABLE != CY_CAPSENSE_TOUCHPAD_EN)) */
#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

#endif /* CY_CAPSENSE_CENTROID_H */


/* [] END OF FILE */
