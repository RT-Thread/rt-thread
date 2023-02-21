/***************************************************************************//**
* \file cy_capsense_gesture_lib.h
* \version 3.0
*
* \brief
* Provides the gesture interface.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#ifndef CY_CAPSENSE_GESTURE_LIB_H
#define CY_CAPSENSE_GESTURE_LIB_H

#include <stdint.h>

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))

#if defined(__cplusplus)
extern "C" {
#endif


/******************************************************************************/
/** \addtogroup group_capsense_gesture_structures *//** \{ */
/******************************************************************************/

/** Gesture configuration structure */
typedef struct
{
    /* Common parameters */
    uint16_t resolutionX;                                       /**< Widget maximum position X-axis */
    uint16_t resolutionY;                                       /**< Widget maximum position Y-axis */

    /* Enabled gesture */
    uint16_t gestureEnableMask;                                 /**< Enabled gesture mask */

    /* Timeout */
    uint16_t flickTimeoutMax;                                   /**< Flick maximum timeout */
    uint16_t edgeTimeoutMax;                                    /**< Edge Swipe maximum timeout */
    uint16_t clickTimeoutMax;                                   /**< Click maximum timeout */
    uint16_t clickTimeoutMin;                                   /**< Click minimum timeout */
    uint16_t secondClickIntervalMax;                            /**< Second Click maximum interval */
    uint16_t secondClickIntervalMin;                            /**< Second Click minimum interval */

    /* Distance */
    uint16_t zoomDistanceMin;                                   /**< Zoom minimum distance */
    uint16_t flickDistanceMin;                                  /**< Flick minimum distance */
    uint16_t scrollDistanceMin;                                 /**< Scroll minimum distance */
    uint16_t rotateDistanceMin;                                 /**< Rotate minimum distance */
    uint16_t edgeDistanceMin;                                   /**< Edge Swipe minimum distance */
    uint8_t secondClickDistanceMax;                             /**< Second Click maximum distance */
    uint8_t clickDistanceMax;                                   /**< Click maximum distance */

    /* Debounce */
    uint8_t zoomDebounce;                                       /**< Zoom debounce */
    uint8_t scrollDebounce;                                     /**< Scroll debounce */
    uint8_t rotateDebounce;                                     /**< Rotate debounce */

    /* Edge Swipe Specific */
    uint8_t edgeAngleMax;                                       /**< Edge Swipe maximum angle */
    uint8_t edgeEdgeSize;                                       /**< Edge Swipe border size */
} cy_stc_capsense_gesture_config_t;

/** Gesture position structure */
typedef struct
{
    uint16_t x;                                                 /**< X axis position */
    uint16_t y;                                                 /**< Y axis position */
} cy_stc_capsense_gesture_position_t;

/** Gesture One Finger Single Click context structure */
typedef struct
{
    uint32_t touchStartTime1;                                   /**< Touchdown time */
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position */
    uint8_t state;                                              /**< Gesture state */
} cy_stc_capsense_ofsc_context_t;

/** Gesture One Finger Double Click context structure */
typedef struct
{
    uint32_t touchStartTime1;                                   /**< Touchdown time */
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position */
    uint8_t state;                                              /**< Gesture state */
} cy_stc_capsense_ofdc_context_t;

/** Gesture One Finger Click and Drag context structure */
typedef struct
{
    uint32_t touchStartTime1;                                   /**< Touchdown time */
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position */
    uint8_t state;                                              /**< Gesture state */
} cy_stc_capsense_ofcd_context_t;

/** Gesture Two Finger Single Click context structure */
typedef struct
{
    uint32_t touchStartTime1;                                   /**< Touchdown time of the first touch */
    uint32_t touchStartTime2;                                   /**< Touchdown time of the second touch */
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position of the first touch */
    cy_stc_capsense_gesture_position_t touchStartPosition2;     /**< Touchdown position of the second touch */
    uint8_t state;                                              /**< Gesture state */
} cy_stc_capsense_tfsc_context_t;

/** Gesture One Finger Scroll context structure */
typedef struct
{
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position */
    uint8_t state;                                              /**< Gesture state */
    uint8_t debounce;                                           /**< Gesture debounce counter */
    uint8_t direction;                                          /**< Last reported direction */
} cy_stc_capsense_ofsl_context_t;

/** Gesture Two Finger Scroll context structure */
typedef struct
{
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position of the first touch */
    cy_stc_capsense_gesture_position_t touchStartPosition2;     /**< Touchdown position of the second touch */
    uint8_t state;                                              /**< Gesture state */
    uint8_t debounce;                                           /**< Gesture debounce counter */
    uint8_t direction;                                          /**< Last reported direction */
} cy_stc_capsense_tfsl_context_t;

/** Gesture One Finger Flick context structure */
typedef struct
{
    uint32_t touchStartTime1;                                   /**< Touchdown time */
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position */
    uint8_t state;                                              /**< Gesture state */
} cy_stc_capsense_offl_context_t;

/** Gesture One Finger Edge Swipe context structure */
typedef struct
{
    uint32_t touchStartTime1;                                   /**< Touchdown time */
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position */
    uint8_t state;                                              /**< Gesture state */
    uint8_t edge;                                               /**< Detected edge */
} cy_stc_capsense_ofes_context_t;

/** Gesture Two Finger Zoom context structure */
typedef struct
{
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position of the first touch */
    cy_stc_capsense_gesture_position_t touchStartPosition2;     /**< Touchdown position of the second touch */
    uint16_t distanceX;                                         /**< History of X-axis displacement */
    uint16_t distanceY;                                         /**< History of Y-axis displacement */
    uint8_t state;                                              /**< Gesture state */
    uint8_t debounce;                                           /**< Gesture debounce counter */
} cy_stc_capsense_tfzm_context_t;

/** Gesture One Finger Rotate context structure */
typedef struct
{
    cy_stc_capsense_gesture_position_t touchStartPosition1;     /**< Touchdown position */
    uint8_t state;                                              /**< Gesture state */
    uint8_t history;                                            /**< History of detected movements */
    uint8_t debounce;                                           /**< Gesture debounce counter */
} cy_stc_capsense_ofrt_context_t;

/** Gesture global context structure */
typedef struct
{
    cy_stc_capsense_gesture_position_t position1;               /**< Current position of the first touch */
    cy_stc_capsense_gesture_position_t positionLast1;           /**< Previous position of the first touch */
    cy_stc_capsense_gesture_position_t position2;               /**< Current position of the second touch */
    cy_stc_capsense_gesture_position_t positionLast2;           /**< Previous position of the second touch */

    uint32_t timestamp;                                         /**< Current timestamp */
    uint16_t detected;                                          /**< Detected gesture mask */
    uint16_t direction;                                         /**< Mask of direction of detected gesture */

    cy_stc_capsense_ofrt_context_t ofrtContext;                 /**< One-finger rotate gesture context */
    cy_stc_capsense_ofsl_context_t ofslContext;                 /**< One-finger scroll gesture context */
    cy_stc_capsense_tfzm_context_t tfzmContext;                 /**< Two-finger zoom gesture context */
    cy_stc_capsense_tfsc_context_t tfscContext;                 /**< Two-finger single click gesture context */
    cy_stc_capsense_ofes_context_t ofesContext;                 /**< One-finger edge swipe gesture context */
    cy_stc_capsense_offl_context_t offlContext;                 /**< One-finger flick gesture context */
    cy_stc_capsense_ofsc_context_t ofscContext;                 /**< One-finger single click gesture context */
    cy_stc_capsense_ofdc_context_t ofdcContext;                 /**< One-finger double click gesture context */
    cy_stc_capsense_ofcd_context_t ofcdContext;                 /**< One-finger click and drag gesture context */
    cy_stc_capsense_tfsl_context_t tfslContext;                 /**< Two-finger scroll gesture context */

    uint8_t numPosition;                                        /**< Current number of touches */
    uint8_t numPositionLast;                                    /**< Previous number of touches */
} cy_stc_capsense_gesture_context_t;

/** \} */


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/

/*******************************************************************************
* Function Name: Cy_CapSense_Gesture_ResetState
****************************************************************************//**
*
* Initializes internal variables and states.
*
* \param context
* The pointer to the gesture context structure
* \ref cy_stc_capsense_gesture_context_t.
*
*******************************************************************************/
void Cy_CapSense_Gesture_ResetState(
                cy_stc_capsense_gesture_context_t * context);


/*******************************************************************************
* Function Name: Cy_CapSense_Gesture_Decode
****************************************************************************//**
*
* Decodes all enabled gestures. This function is called each scanning cycle.
*
* \param timestamp
* Current timestamp.
*
* \param touchNumber
* The number of touches. Also this parameter defines the size of position array.
*
* \param position
* The pointer to the array of positions \ref cy_stc_capsense_gesture_position_t.
*
* \param config
* The pointer to the gesture configuration structure
* \ref cy_stc_capsense_gesture_config_t.
*
* \param context
* The pointer to the gesture context structure
* \ref cy_stc_capsense_gesture_context_t.
*
*******************************************************************************/
void Cy_CapSense_Gesture_Decode(
                uint32_t timestamp,
                uint32_t touchNumber,
                const cy_stc_capsense_gesture_position_t * position,
                const cy_stc_capsense_gesture_config_t * config,
                cy_stc_capsense_gesture_context_t * context);
/** \} \endcond */

/*******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************/
/** \addtogroup group_capsense_macros_gesture *//** \{ */
/******************************************************************************/
/* Enable and Detection */
/** No gesture detected */
#define CY_CAPSENSE_GESTURE_NO_GESTURE                      (0x00u)
/** All gestures enable / detection mask */
#define CY_CAPSENSE_GESTURE_ALL_GESTURES_MASK               (0x03FFu)
/** Gesture enable filtering mask */
#define CY_CAPSENSE_GESTURE_FILTERING_MASK                  (0x8000u)
/** Detection mask of Touchdown */
#define CY_CAPSENSE_GESTURE_TOUCHDOWN_MASK                  (0x2000u)
/** Detection mask of Lift Off */
#define CY_CAPSENSE_GESTURE_LIFTOFF_MASK                    (0x4000u)

/** Enable / detection mask of one-finger single click gesture */
#define CY_CAPSENSE_GESTURE_ONE_FNGR_SINGLE_CLICK_MASK      (0x0001u)
/** Enable / detection mask of one-finger double click gesture */
#define CY_CAPSENSE_GESTURE_ONE_FNGR_DOUBLE_CLICK_MASK      (0x0002u)
/** Enable / detection mask of one-finger click and drag gesture */
#define CY_CAPSENSE_GESTURE_ONE_FNGR_CLICK_DRAG_MASK        (0x0004u)
/** Enable / detection mask of two-finger single click gesture */
#define CY_CAPSENSE_GESTURE_TWO_FNGR_SINGLE_CLICK_MASK      (0x0008u)
/** Enable / detection mask of one-finger scroll gesture */
#define CY_CAPSENSE_GESTURE_ONE_FNGR_SCROLL_MASK            (0x0010u)
/** Enable / detection mask of two-finger scroll gesture */
#define CY_CAPSENSE_GESTURE_TWO_FNGR_SCROLL_MASK            (0x0020u)
/** Enable / detection mask of one-finger edge swipe gesture */
#define CY_CAPSENSE_GESTURE_ONE_FNGR_EDGE_SWIPE_MASK        (0x0040u)
/** Enable / detection mask of one-finger flick gesture */
#define CY_CAPSENSE_GESTURE_ONE_FNGR_FLICK_MASK             (0x0080u)
/** Enable / detection mask of one-finger rotate gesture */
#define CY_CAPSENSE_GESTURE_ONE_FNGR_ROTATE_MASK            (0x0100u)
/** Enable / detection mask of two-finger zoom gesture */
#define CY_CAPSENSE_GESTURE_TWO_FNGR_ZOOM_MASK              (0x0200u)

/* Direction Offsets */
/** Offset of direction of one-finger scroll gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_OFFSET_ONE_SCROLL     (0x00u)
/** Offset of direction of two-finger scroll gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_OFFSET_TWO_SCROLL     (0x02u)
/** Offset of direction of one-finger edge swipe gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_OFFSET_ONE_EDGE       (0x04u)
/** Offset of direction of one-finger rotate gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_OFFSET_ONE_ROTATE     (0x06u)
/** Offset of direction of two-finger zoom gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_OFFSET_TWO_ZOOM       (0x07u)
/** Offset of direction of one-finger flick gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_OFFSET_ONE_FLICK      (0x08u)

/* Direction Masks */
/** Mask of direction of one-finger scroll gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_MASK_ONE_SCROLL       (0x0003u)
/** Mask of direction of two-finger scroll gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_MASK_TWO_SCROLL       (0x000Cu)
/** Mask of direction of one-finger edge swipe gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_MASK_ONE_EDGE         (0x0030u)
/** Mask of direction of one-finger rotate gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_MASK_ONE_ROTATE       (0x0040u)
/** Mask of direction of two-finger zoom gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_MASK_TWO_ZOOM         (0x0080u)
/** Mask of direction of one-finger flick gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_MASK_ONE_FLICK        (0x0700u)

/** An extra direction offset returned by Cy_CapSense_DecodeWidgetGestures() */
#define CY_CAPSENSE_GESTURE_DIRECTION_OFFSET                (16u)

/* Direction */
/** CLOCKWISE direction of Rotate gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_CW                    (0x00u)
/** COUNTER CLOCKWISE direction of Rotate gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_CCW                   (0x01u)

/** ZOOM-IN direction of Zoom gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_IN                    (0x00u)
/** ZOOM-OUT direction of Zoom gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_OUT                   (0x01u)

/** UP direction of Scroll, Flick and Edge Swipe gestures */
#define CY_CAPSENSE_GESTURE_DIRECTION_UP                    (0x00u)
/** DOWN direction of Scroll, Flick and Edge Swipe gestures */
#define CY_CAPSENSE_GESTURE_DIRECTION_DOWN                  (0x01u)
/** RIGHT direction of Scroll, Flick and Edge Swipe gestures */
#define CY_CAPSENSE_GESTURE_DIRECTION_RIGHT                 (0x02u)
/** LEFT direction of Scroll, Flick and Edge Swipe gestures */
#define CY_CAPSENSE_GESTURE_DIRECTION_LEFT                  (0x03u)
/** UP-RIGHT direction of Flick gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_UP_RIGHT              (0x04u)
/** DOWN-LEFT direction of Flick gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_DOWN_LEFT             (0x05u)
/** DOWN-RIGHT direction of Flick gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_DOWN_RIGHT            (0x06u)
/** UP-LEFT direction of Flick gesture */
#define CY_CAPSENSE_GESTURE_DIRECTION_UP_LEFT               (0x07u)

/** \} */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

#endif /* CY_CAPSENSE_GESTURE_LIB_H */


/* [] END OF FILE */
