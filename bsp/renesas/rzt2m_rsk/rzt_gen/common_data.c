/* generated common source file - do not edit */
#include "common_data.h"
/** IOPORT interface configuration for event link **/
            const ioport_extend_cfg_t  g_ioport_cfg_extend =
            {
                .port_group_output_cfg[IOPORT_PORT_GROUP_1] =
                {
                    .pin_select   = (uint8_t)( IOPORT_EVENT_PIN_SELECTION_NONE),
                    .operation    = IOPORT_EVENT_OUTPUT_OPERATION_LOW
                },
                .port_group_output_cfg[IOPORT_PORT_GROUP_2] =
                {
                    .pin_select   = (uint8_t)( IOPORT_EVENT_PIN_SELECTION_NONE),
                    .operation    = IOPORT_EVENT_OUTPUT_OPERATION_LOW
                },
                .port_group_input_cfg[IOPORT_PORT_GROUP_1] =
                {
                    .event_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .pin_select    = (uint8_t)( IOPORT_EVENT_PIN_SELECTION_NONE),
                    .edge_detection    = IOPORT_EVENT_DETECTION_RISING_EDGE,
                    .overwrite_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .buffer_init_value = IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 7U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 6U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 5U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 4U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 3U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 2U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 1U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW
                },
                .port_group_input_cfg[IOPORT_PORT_GROUP_2] =
                {
                    .event_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .pin_select    = (uint8_t)( IOPORT_EVENT_PIN_SELECTION_NONE),
                    .edge_detection    = IOPORT_EVENT_DETECTION_RISING_EDGE,
                    .overwrite_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .buffer_init_value = IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 7U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 6U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 5U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 4U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 3U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 2U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW << 1U | IOPORT_EVENT_INITIAL_BUFFER_VALUE_LOW
                },
                .single_port_cfg[IOPORT_SINGLE_PORT_0] =
                {
                    .event_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .direction = IOPORT_EVENT_DIRECTION_OUTPUT,
                    .port_num  = (uint16_t)BSP_IO_PORT_16_PIN_0,
                    .operation = IOPORT_EVENT_OUTPUT_OPERATION_LOW,
                    .edge_detection = IOPORT_EVENT_DETECTION_RISING_EDGE
                },
                .single_port_cfg[IOPORT_SINGLE_PORT_1] =
                {
                    .event_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .direction = IOPORT_EVENT_DIRECTION_OUTPUT,
                    .port_num  = (uint16_t)BSP_IO_PORT_16_PIN_0,
                    .operation = IOPORT_EVENT_OUTPUT_OPERATION_LOW,
                    .edge_detection = IOPORT_EVENT_DETECTION_RISING_EDGE
                },
                .single_port_cfg[IOPORT_SINGLE_PORT_2] =
                {
                    .event_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .direction = IOPORT_EVENT_DIRECTION_OUTPUT,
                    .port_num  = (uint16_t)BSP_IO_PORT_16_PIN_0,
                    .operation = IOPORT_EVENT_OUTPUT_OPERATION_LOW,
                    .edge_detection = IOPORT_EVENT_DETECTION_RISING_EDGE
                },
                .single_port_cfg[IOPORT_SINGLE_PORT_3] =
                {
                    .event_control = IOPORT_EVENT_CONTROL_DISABLE,
                    .direction = IOPORT_EVENT_DIRECTION_OUTPUT,
                    .port_num  = (uint16_t)BSP_IO_PORT_16_PIN_0,
                    .operation = IOPORT_EVENT_OUTPUT_OPERATION_LOW,
                    .edge_detection = IOPORT_EVENT_DETECTION_RISING_EDGE
                }
            };

ioport_instance_ctrl_t g_ioport_ctrl;

const ioport_instance_t g_ioport =
        {
            .p_api = &g_ioport_on_ioport,
            .p_ctrl = &g_ioport_ctrl,
            .p_cfg = &g_bsp_pin_cfg
        };
void g_common_init(void) {
}
