/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup IOPORT
 * @{
 **********************************************************************************************************************/

#ifndef R_IOPORT_H
#define R_IOPORT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#include "r_ioport_api.h"
#include "r_ioport_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define IOPORT_SINGLE_PORT_NUM    (4)
#define IOPORT_PORT_GROUP_NUM     (2)
#define IOPORT_PORT_GROUP_1       (0)
#define IOPORT_PORT_GROUP_2       (1)
#define IOPORT_SINGLE_PORT_0      (0)
#define IOPORT_SINGLE_PORT_1      (1)
#define IOPORT_SINGLE_PORT_2      (2)
#define IOPORT_SINGLE_PORT_3      (3)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Pin selection for port group
 *  @note Event link must be configured by the ELC
 */
typedef enum e_ioport_event_pin_selection
{
    IOPORT_EVENT_PIN_SELECTION_NONE  = 0x00, ///< No pin selection for port group
    IOPORT_EVENT_PIN_SELECTION_PIN_0 = 0x01, ///< Select pin 0 to port group
    IOPORT_EVENT_PIN_SELECTION_PIN_1 = 0x02, ///< Select pin 1 to port group
    IOPORT_EVENT_PIN_SELECTION_PIN_2 = 0x04, ///< Select pin 2 to port group
    IOPORT_EVENT_PIN_SELECTION_PIN_3 = 0x08, ///< Select pin 3 to port group
    IOPORT_EVENT_PIN_SELECTION_PIN_4 = 0x10, ///< Select pin 4 to port group
    IOPORT_EVENT_PIN_SELECTION_PIN_5 = 0x20, ///< Select pin 5 to port group
    IOPORT_EVENT_PIN_SELECTION_PIN_6 = 0x40, ///< Select pin 6 to port group
    IOPORT_EVENT_PIN_SELECTION_PIN_7 = 0x80, ///< Select pin 7 to port group
} ioport_event_pin_selection_t;

/** Port group operation
 *  @note Event link must be configured by the ELC
 */
typedef enum e_ioport_event_output_operation
{
    IOPORT_EVENT_OUTPUT_OPERATION_LOW    = 0x0, ///< Set Low output to output operation
    IOPORT_EVENT_OUTPUT_OPERATION_HIGH   = 0x1, ///< Set High output to output operation
    IOPORT_EVENT_OUTPUT_OPERATION_TOGGLE = 0x2, ///< Set toggle output to output operation
    IOPORT_EVENT_OUTPUT_OPERATION_BUFFER = 0x3, ///< Set buffer value output to output operation
} ioport_event_output_operation_t;

/** Input port group event control
 *  @note Event link must be configured by the ELC
 */
typedef enum e_ioport_event_control
{
    IOPORT_EVENT_CONTROL_DISABLE = 0x0, ///< Disable function related with event link
    IOPORT_EVENT_CONTROL_ENABLE  = 0x1, ///< Enable function related with event link
} ioport_event_control_t;

/** Single port event direction
 *  @note Event link must be configured by the ELC
 */
typedef enum e_ioport_event_direction
{
    IOPORT_EVENT_DIRECTION_OUTPUT = 0x0, ///< Set output direction to single port
    IOPORT_EVENT_DIRECTION_INPUT  = 0x1, ///< Set input direction to single port
} ioport_event_direction_t;

/** Input event edge detection
 *  @note Event link must be configured by the ELC
 */
typedef enum e_ioport_event_detection
{
    IOPORT_EVENT_DETECTION_RISING_EDGE  = 0x0, ///< Set rising edge to event detection for input event
    IOPORT_EVENT_DETECTION_FALLING_EDGE = 0x1, ///< Set falling edge to event detection for input event
    IOPORT_EVENT_DETECTION_BOTH_EGDE    = 0x2, ///< Set both edges to event detection for input event
} ioport_event_detection_t;

/** Initial value for buffer register
 *  @note Event link must be configured by the ELC
 */
typedef enum e_ioport_event_initial_buffer_value
{
    IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW  = 0U, ///< Set low input to initial value of buffer register for input port group
    IOPORT_EVENT_INITIAL_BUFFER_VALUE_HIGH = 1U, ///< Set high input to initial value of buffer register for input port group
} ioport_event_initial_buffer_value_t;

/** Single port configuration
 *  @note Event link must be configured by the ELC
 */
typedef struct st_ioport_event_single
{
    ioport_event_control_t          event_control;  ///< Event link control for single port
    ioport_event_direction_t        direction;      ///< Event direction for single port
    uint16_t                        port_num;       ///< Port number specified to single port
    ioport_event_output_operation_t operation;      ///< Single port operation select
    ioport_event_detection_t        edge_detection; ///< Edge detection select
} ioport_event_single_t;

/** Output port group configuration
 *  @note Event link must be configured by the ELC
 */
typedef struct st_ioport_event_group_output
{
    uint8_t pin_select;                        ///< Port number specified to output port group
    ioport_event_output_operation_t operation; ///< Port group operation select
} ioport_event_group_output_t;

/** Input port group configuration
 *  @note Event link must be configured by the ELC
 */
typedef struct st_ioport_event_group_input
{
    ioport_event_control_t   event_control;     ///< Event link control for input port group
    ioport_event_detection_t edge_detection;    ///< Edge detection select
    ioport_event_control_t   overwrite_control; ///< Buffer register overwrite control
    uint8_t pin_select;                         ///< Port number specified to input port group
    uint8_t buffer_init_value;                  ///< Buffer register initial value
} ioport_event_group_input_t;

/** IOPORT extended configuration for event link function
 *  @note Event link must be configured by the ELC
 */
typedef struct  st_ioport_extend_cfg
{
    ioport_event_group_output_t port_group_output_cfg[IOPORT_PORT_GROUP_NUM]; ///< Output port group configuration
    ioport_event_group_input_t  port_group_input_cfg[IOPORT_PORT_GROUP_NUM];  ///< Input port group configuration
    ioport_event_single_t       single_port_cfg[IOPORT_SINGLE_PORT_NUM];      ///< Single input port configuration
} ioport_extend_cfg_t;

/** IOPORT private control block. DO NOT MODIFY. Initialization occurs when R_IOPORT_Open() is called. */
typedef struct st_ioport_instance_ctrl
{
    uint32_t             open;         // Whether or not ioport is open
    void const         * p_context;    // Pointer to context to be passed into callback
    ioport_cfg_t const * p_cfg;        // Pointer to the configuration block
} ioport_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ioport_api_t g_ioport_on_ioport;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_IOPORT_Open(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_IOPORT_Close(ioport_ctrl_t * const p_ctrl);
fsp_err_t R_IOPORT_PinsCfg(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_IOPORT_PinCfg(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);
fsp_err_t R_IOPORT_PinEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event);
fsp_err_t R_IOPORT_PinEventOutputWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value);
fsp_err_t R_IOPORT_PinRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);
fsp_err_t R_IOPORT_PinWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level);
fsp_err_t R_IOPORT_PortDirectionSet(ioport_ctrl_t * const p_ctrl,
                                    bsp_io_port_t         port,
                                    ioport_size_t         direction_values,
                                    ioport_size_t         mask);
fsp_err_t R_IOPORT_PortEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_event_data);
fsp_err_t R_IOPORT_PortEventOutputWrite(ioport_ctrl_t * const p_ctrl,
                                        bsp_io_port_t         port,
                                        ioport_size_t         event_data,
                                        ioport_size_t         mask_value);
fsp_err_t R_IOPORT_PortRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value);
fsp_err_t R_IOPORT_PortWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask);

/*******************************************************************************************************************//**
 * @} (end defgroup IOPORT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IOPORT_H
