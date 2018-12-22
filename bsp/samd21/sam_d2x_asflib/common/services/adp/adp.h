/**
 * \file
 *
 * \brief ADP service implementation
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef ADP_H_INCLUDED
#define ADP_H_INCLUDED

#include <compiler.h>

/** Version of ADP implemented here */
#define ADP_VERSION                 1

/** Start token for ADP data */
#define ADP_TOKEN                   0xFF

/** Maximum number of streams from PC to target */
#define ADP_MAX_INCOMMING_STREAMS   5
/** Maximum number of streams from target to PC */
#define ADP_MAX_OUTGOING_STREAMS    5

/** Maximum number of bytes target can request from PC in one request */
#define ADP_MAX_BYTE_REQUEST        20

/** Length of ADP packet header: Token, Message ID, Data Length */
#define ADP_LENGTH_PACKET_HEADER    4

/** Maximum number of bytes in data part of ADP packet */
#define ADP_MAX_PACKET_DATA_SIZE    254

/** Maximum number of all bytes in ADP packet */
#define  ADP_MAX_PACKET_LENGTH (ADP_LENGTH_PACKET_HEADER + ADP_MAX_PACKET_DATA_SIZE)

/** Key used to identify proper handshake message */
#define ADP_HANDSHAKE_KEY {0x58, 0x99, 0xAB, 0xC9, 0x0F, 0xE2, 0xF7, 0xAA}

/** ADP RGB color definitions. Other RGB values can be used as well */
#define ADP_COLOR_WHITE   0xFF, 0xFF, 0xFF
#define ADP_COLOR_BLACK   0x00, 0x00, 0x00
#define ADP_COLOR_SILVER  0xC0, 0xC0, 0xC0
#define ADP_COLOR_GRAY    0x80, 0x80, 0x80
#define ADP_COLOR_MAROON  0x80, 0x00, 0x00
#define ADP_COLOR_RED     0xFF, 0x00, 0x00
#define ADP_COLOR_PURPLE  0x80, 0x00, 0x80
#define ADP_COLOR_FUCHSIA 0xFF, 0x00, 0xFF
#define ADP_COLOR_GREEN   0x00, 0x80, 0x00
#define ADP_COLOR_LIME    0x00, 0xFF, 0x00
#define ADP_COLOR_OLIVE   0x80, 0x80, 0x00
#define ADP_COLOR_YELLOW  0xFF, 0xFF, 0x00
#define ADP_COLOR_NAVY    0x00, 0x00, 0x80
#define ADP_COLOR_BLUE    0x00, 0x00, 0xFF
#define ADP_COLOR_TEAL    0x00, 0x80, 0x80
#define ADP_COLOR_AQUA    0x00, 0xFF, 0xFF
#define ADP_COLOR_ORANGE  0xFF, 0xA5, 0x00

/** States in receive state machine */
enum rx_state_e {
	/** We are idle, waiting for a new packet */
	RX_STATE_IDLE,
	/** Start symbol received, waiting for Message ID */
	RX_STATE_WAIT_MSG_ID,
	/** Message ID received, waiting for data length */
	RX_STATE_WAIT_LENGTH_LSB,
	/** Message ID received, waiting for data length */
	RX_STATE_WAIT_LENGTH_MSB,
	/** Length received; we are receiving packet data */
	RX_STATE_GET_DATA,
	/** Start symbol received */
	RX_STATE_GOT_SYMBOL,
};

/** Max length of labels */
 #define ADP_CONF_MAX_LABEL 20

static inline void adp_set_color(uint8_t* struct_member, uint8_t c_red, uint8_t c_green, uint8_t c_blue)
{
	struct_member[0] = c_red;
	struct_member[1] = c_green;
	struct_member[2] = c_blue;
}


#define adp_set_string(struct_member, string)                  \
		Assert(sizeof(struct_member));                         \
		strncpy(struct_member, string, sizeof(struct_member)); \
		struct_member[sizeof(struct_member)-1] = '\0';

/* MESSAGE FORMAT */
SHORTENUM struct adp_msg_format {
	/* Start token for ADP data */
	uint8_t protocol_token;
	/* Describes what data is sent */
	uint8_t protocol_msg_id;
	/* Length of data packet */
	uint16_t data_length;
	/* Data packet for the message */
	uint8_t data[ADP_MAX_PACKET_DATA_SIZE];
};


/* MSG_REQ_HANDSHAKE */
#define MSG_REQ_HANDSHAKE 0x00
#define MSQ_REQ_HANDSHAKE_LEN 10
enum adp_handshake_options {
	/* Use GPIO */
	ADP_HANDSHAKE_OPTIONS_GPIO,
	/* Lock configuration */
	ADP_HANDSHAKE_OPTIONS_LOCK,
};
SHORTENUM struct adp_msg_request_handshake {
	/* Version of protocol on target */
	uint8_t protocol_version;
	/* Is GPIO in use in this app?
	 * Can user change configuration on PC side? 
	 */
	uint8_t options;
	/* Token used to verify ADP protocol */
	uint8_t key[8];
};

/* MSG_RES_HANDSHAKE */
#define MSG_RES_HANDSHAKE 0x10
enum adp_handshake_status {
	/* Handshake accepted */
	ADP_HANDSHAKE_ACCEPTED,
	/* Handshake rejected. Invalid protocol version */
	ADP_HANDSHAKE_REJECTED_PROTOCOL,
	/* Handshake rejected. Other reason */
	ADP_HANDSHAKE_REJECTED_OTHER,
};
SHORTENUM struct adp_msg_response_handshake {
	enum adp_handshake_status status;
};

enum adp_handshake_status adp_wait_for_handshake(void);

/* MSG_REQ_STATUS */
#define MSG_REQ_STATUS 0x02
#define MSG_REQ_STATUS_LEN 0
/* This message has no data */

/* MSG_RES_STATUS */
#define MSG_RES_STATUS 0x12
enum adp_status_code {
	/* Invalid packet received */
	ADP_STATUS_INVALID_PACKET,
	/* Invalid configuration data received */
	ADP_STATUS_INVALID_CONFIGURATION,
	/* Data ready to be transmitted to target */
	ADP_STATUS_DATA_READY,
	/* Invalid stream request (req_data) */
	ADP_STATUS_INVALID_REQUEST,
	/* No data available on stream (req_data) */
	ADP_STATUS_NO_DATA,
	/* Request target software reset */
	ADP_STATUS_RESET,
};
SHORTENUM struct adp_msg_response_status {
	enum adp_status_code status;
};

enum adp_status_code adp_request_status(void);

/* MSG_RES_DATA */
#define MSG_RES_DATA 0x14
#define MSG_RES_DATA_MAX_LEN (ADP_MAX_BYTE_REQUEST + 4)
SHORTENUM struct adp_msg_response_data {
	/* ID of stream */
	uint8_t stream_id;
	/* Number of bytes in packet. 
	 * If the target has requested data from an unknown stream, or if stream 
	 * has no data to send, this field should be set to 0 and the appropriate 
	 * status flag should be set.
	 */
	uint8_t bytes_sent;
	/* The data */		
	uint8_t data[ADP_MAX_BYTE_REQUEST];
};

void adp_request_data(uint8_t stream_id, uint8_t bytes_to_send, struct adp_msg_response_data *response);

#define MSG_RES_PACKET_DATA_MAX_LEN (ADP_MAX_BYTE_REQUEST + 2)
SHORTENUM struct adp_msg_packet_data {
	uint16_t stream_id;
	uint8_t bytes_sent;
	uint8_t data[ADP_MAX_BYTE_REQUEST];
};
bool adp_receive_packet_data(uint8_t *receive_buf);

/* MSG_CONF_STREAM */
enum adp_stream_type {
	ADP_STREAM_EVENT,
	ADP_STREAM_STRING,
	ADP_STREAM_UINT_8,
	ADP_STREAM_INT_8,
	ADP_STREAM_UINT_16,
	ADP_STREAM_INT_16,
	ADP_STREAM_UINT_32,
	ADP_STREAM_INT_32,
	ADP_STREAM_XY_8,
	ADP_STREAM_XY_16,
	ADP_STREAM_XY_32,
	ADP_STREAM_BOOL,
	ADP_STREAM_FLOAT,
};

enum adp_stream_state {
	ADP_STREAM_OFF,
	ADP_STREAM_ON,
};

enum adp_stream_mode {
	/* Incoming (normal) */
	ADP_STREAM_IN,
	/* Incoming (single value) */
	ADP_STREAM_IN_SINGLE,
	/* Outgoing */
	ADP_STREAM_OUT,
};

#define MSG_CONF_ACK       0x30
#define ADP_ACK_NOT_OK     0
#define ADP_ACK_OK         1

#define MSG_CONF_INFO      0x28
#define MSG_CONF_INFO_LEN
bool adp_configure_info(const char* title, const char* description);

#define MSG_CONF_STREAM     0x20
#define MSG_CONF_STREAM_LEN 5
SHORTENUM struct adp_msg_configure_stream {
	/* ID of stream */
	uint16_t stream_id;
	/* Stream type */
	enum adp_stream_type type;
	/* Stream mode/direction */
	enum adp_stream_mode mode;
	/* Stream state */
	enum adp_stream_state state;
};

static inline void adp_configure_stream_get_defaults(struct adp_msg_configure_stream *const config)
{
	Assert(config);
	config->stream_id = 0;
	config->type = ADP_STREAM_UINT_8;
	config->mode = ADP_STREAM_OUT;
	config->state = ADP_STREAM_ON;
}

bool adp_configure_stream(struct adp_msg_configure_stream *const config, const char* label);

/* MSG_CONF_TOGGLE_STREAM */
#define MSG_CONF_TOGGLE_STREAM   0x21
#define MSG_CONF_TOGGLE_STREAM_LEN 3
SHORTENUM struct adp_msg_toggle_stream {
	uint16_t               stream_id;
	enum adp_stream_state  state;
};
bool adp_toggle_stream(struct adp_msg_toggle_stream *const config);

/* MSG_CONF_GRAPH */
#define MSG_CONF_GRAPH           0x22
#define MSG_CONF_GRAPH_LEN       23

enum adp_graph_scale_mode {
	ADP_GRAPH_SCALE_OFF,
	ADP_GRAPH_SCALE_AUTO
};

enum adp_graph_scroll_mode {
	/* No scrolling */
	ADP_GRAPH_SCROLL_OFF,
	/* Stepping */
	ADP_GRAPH_SCROLL_STEP,
	/* Scroll */
	ADP_GRAPH_SCROLL_SCROLL,
	/* Circular/sweep */
	ADP_GRAPH_SCROLL_CIRCULAR
};

SHORTENUM struct adp_msg_configure_graph {
	/* ID of new graph */
	uint8_t graph_id;
	/* Range Xmin value */
	uint32_t x_min;
	/* Range Xmax value */
	uint32_t x_max;
	/* Xscale numerator */
	uint32_t x_scale_numerator;
	/* X range scale value. Set to 0 to enable auto range */
	uint32_t x_scale_denominator;
	/* Vertical scaling */
	enum adp_graph_scale_mode scale_mode;
	/* RGB background color */
	uint8_t background_color[3];
	/* Horizontal scrolling */
	enum adp_graph_scroll_mode scroll_mode;
};

static inline void adp_configure_graph_get_defaults(struct adp_msg_configure_graph *const config)
{
	Assert(config);
	config->graph_id = 0;
	config->x_min = 0;
	config->x_max = 0;
	config->x_scale_numerator = 0;
	config->x_scale_denominator = 0;
	config->scale_mode = ADP_GRAPH_SCALE_OFF;
	adp_set_color(config->background_color, ADP_COLOR_WHITE);
	config->scroll_mode = ADP_GRAPH_SCROLL_SCROLL;
}

bool adp_configure_graph(struct adp_msg_configure_graph *const config, \
						const char* graph_label, const char* x_label);

/* MSG_CONF_AXIS */
#define MSG_CONF_AXIS       0x29
#define MSG_CONF_AXIS_LEN   24
SHORTENUM struct adp_msg_conf_axis {
	/* ID of new axis */
	uint16_t axis_id;
	/* ID of graph */
	uint16_t graph_id;
	/* Range Ymin value */
	int32_t y_min;
	/* Range Ymax value */
	int32_t y_max;
	/* X range scale value.	Set to 0 to enable auto range */
	uint32_t x_scale_numerator;
	/* X range scale value.	Set to 0 to enable auto range */
	uint32_t x_scale_denominator;
	/* Mode */
	uint8_t mode;                                         // TODO
	/* RGB color */
	uint8_t color[3];
};

static inline void adp_add_axis_to_graph_get_defaults(struct adp_msg_conf_axis *const config)
{
	Assert(config);
	config->axis_id = 0;
	config->graph_id = 0;
	config->y_min = 0;
	config->y_max = 0;
	config->x_scale_numerator = 0;
	config->x_scale_denominator = 0;
	config->mode = 0;
	adp_set_color(config->color, ADP_COLOR_BLACK);
}

bool adp_add_axis_to_graph(struct adp_msg_conf_axis *const config, const char* label);

/* MSG_CONF_ADD_STREAM_TO_GRAPH */
#define MSG_CONF_ADD_STREAM_TO_AXIS       0x23
#define MSG_CONF_ADD_STREAM_TO_AXIS_LEN   32

#define ADP_AXIS_LINE_bm    0x01
#define ADP_AXIS_POINTS_bm  0x02

SHORTENUM struct adp_msg_add_stream_to_axis {
	/* ID of graph */
	uint16_t graph_id;
	/* ID of new axis */
	uint16_t axis_id;
	/* ID of stream */
	uint16_t stream_id;
	/* Sample rate of stream, set to 0 if NA */
	uint32_t sample_rate_numerator;
	/* Sample rate of stream, set to 0 if NA */
	uint32_t sample_rate_denominator;
	/* Range Ymin value */
	uint32_t y_scale_numerator;
	/* Range Ymax value */
	uint32_t y_scale_denominator;
	/* Offset of values */
	uint32_t y_offset;
	/* Adjust the transparency */
	uint8_t transparency;
	/* For graphs:  bit 0 = line on/off
	 *              bit 1 = points on/off
	 * For text:    bit 0 = flag
	 *              bit 1 = text
	 */
	uint8_t mode;                           // TODO
	/* Thickness of line */
	uint8_t line_thickness;
	/* RGB color of line */
	uint8_t line_color[3];
};

static inline void adp_add_stream_to_axis_get_defaults(struct adp_msg_add_stream_to_axis *const config)
{
	Assert(config);
	config->graph_id = 0;
	config->axis_id = 0;
	config->stream_id = 0;
	config->sample_rate_numerator = 0;
	config->sample_rate_denominator = 0;
	config->y_scale_numerator = 0;
	config->y_scale_denominator = 0;
	config->y_offset = 0;
	config->transparency = 0;
	config->mode = ADP_AXIS_LINE_bm;
	config->line_thickness = 1;
	adp_set_color(config->line_color, ADP_COLOR_BLACK);
}

bool adp_add_stream_to_axis(struct adp_msg_add_stream_to_axis *const config);

/* MSG_CONF_CURSOR_TO_GRAPH */
#define MSG_CONF_CURSOR_TO_GRAPH     0x24
#define MSG_CONF_CURSOR_TO_GRAPH_LEN 35
SHORTENUM struct adp_msg_add_cursor_to_graph {
	/* ID of streama */
	uint16_t stream_id;
	/* ID of graph */
	uint16_t graph_id;
	/* ID of axis */
	uint16_t axis_id;
	/* Thickness of line */
	uint8_t thickness;
	/* RGB color of cursor */
	uint8_t color[3];
	/* Starting point of cursor */
	uint32_t initial_value;
	/* Minimum allowed value */
	uint32_t minimum_value;
	/* Maximum */
	uint32_t maximum_value;
	/* Numerator of scaling value */
	uint32_t scale_numerator;
	/* Denominator of scaling value */
	uint32_t scale_denominator;
	/* Offset of value */
	uint32_t scale_offset;
	/* The style of line: Solid, dashed, dotted.. */
	uint8_t line_style;          // TODO
};

static inline void adp_add_cursor_to_graph_get_defaults(struct adp_msg_add_cursor_to_graph *const config)
{
	Assert(config);
	config->stream_id = 0;
	config->graph_id = 0;
	config->axis_id = 0;
	config->thickness = 1;
	adp_set_color(config->color, ADP_COLOR_WHITE);
	config->initial_value = 0;
	config->minimum_value = 0;
	config->maximum_value = 0;
	config->scale_numerator = 0;
	config->scale_denominator = 0;
	config->scale_offset = 0;
	config->line_style = 0;
}

bool adp_add_cursor_to_graph(struct adp_msg_add_cursor_to_graph *const config, const char* label);

/* MSG_CONF_GPIO_TO_GRAPH */
#define MSG_CONF_GPIO_TO_GRAPH       0x25
#define MSG_CONF_GPIO_TO_GRAPH_LEN   15
SHORTENUM struct adp_msg_conf_gpio_to_graph {
	/* ID of graph */
	uint16_t graph_id;
	/* GPIO number to add to graph. Bit 0: GPIO0. bit 1: GPIO1 etc. */
	uint8_t gpio_number;
	/* Used to group graphs and cursors to the same scale */
	uint8_t group_id;
	/* Adjust the transparency */
	uint8_t transparency;
	/* Mode */
	uint16_t mode;                                    // TODO
	/* Thickness of line */
	uint8_t line_thickness;
	/* RGB color of line when GPIO pin is high */
	uint8_t line_color_high_state[3];
	/* RGB color of line when GPIO pin is low */
	uint8_t line_color_low_state[3];
	/* The style of line */
	uint8_t line_style;
};

static inline void adp_gpio_to_graph_get_defaults(struct adp_msg_conf_gpio_to_graph *const config)
{
	Assert(config);
	config->graph_id = 0;
	config->gpio_number = 0;
	config->group_id = 0;
	config->transparency = 0;
	config->mode = 0;
	config->line_thickness = 1;
	adp_set_color(config->line_color_high_state, ADP_COLOR_WHITE);
	adp_set_color(config->line_color_low_state, ADP_COLOR_WHITE);
	config->line_style = 0;
}

bool adp_add_gpio_to_graph(struct adp_msg_conf_gpio_to_graph *const config, \
						const char* tag_high_state, const char* tag_low_state);

/* MSG_CONF_TERMINAL */
#define MSG_CONF_TERMINAL        0x26
#define MSG_CONF_TERMINAL_LEN    10
SHORTENUM struct adp_msg_conf_terminal {
	/* ID of terminal */
	uint16_t terminal_id;
	/* Number of characters wide */
	uint8_t width;
	/* Number of characters high */
	uint8_t height;
	/* RGB background color */
	uint8_t background_color[3];
	/* RGB background color */
	uint8_t foreground_color[3];
};

static inline void adp_configure_terminal_get_defaults(struct adp_msg_conf_terminal *const config)
{
	Assert(config);
	config->terminal_id = 0;
	config->width = 80;
	config->height = 25;
	adp_set_color(config->background_color, ADP_COLOR_WHITE);
	adp_set_color(config->foreground_color, ADP_COLOR_BLACK);
}

bool adp_configure_terminal(struct adp_msg_conf_terminal *const config, const char* label);

/* MSG_CONF_ADD_TO_TERMINAL */
#define MSG_CONF_ADD_TO_TERMINAL       0x27
#define MSG_CONF_ADD_TO_TERMINAL_LEN   11
SHORTENUM struct adp_msg_add_stream_to_terminal {
	/* ID of Terminal */
	uint16_t terminal_id;
	/* ID of stream */
	uint16_t stream_id;
	/* 0bx x x N T S F F
	 * N = implicit newline in incoming text
	 * T = enable tag
	 * S = timestamped
	 * F = format (Hex, decimal, binary, ascii)
	 */
	uint8_t mode;                                    // TODO
	/* RGB color of the text stream received */
	uint8_t text_color[3];
	/* RGB color of the tag text */
	uint8_t tag_text_color[3];
};

static inline void adp_add_stream_to_terminal_get_defaults(struct adp_msg_add_stream_to_terminal *const config)
{
	Assert(config);
	config->terminal_id = 0;
	config->stream_id = 0;
	config->mode = 0;
	adp_set_color(config->text_color, ADP_COLOR_BLACK);
	adp_set_color(config->tag_text_color, ADP_COLOR_BLACK);
}

bool adp_add_stream_to_terminal(struct adp_msg_add_stream_to_terminal *const config, const char* tag_text);

/* MSG_CONF_DASHBOARD */
#define MSG_CONF_DASHBOARD       0x2A
#define MSG_CONF_DASHBOARD_LEN   7
SHORTENUM struct adp_msg_conf_dashboard {
	uint16_t dashboard_id;
	uint8_t color[3];
	uint16_t height;
};

static inline void adp_conf_dashboard_get_defaults(struct adp_msg_conf_dashboard *const config)
{
	Assert(config);
	config->dashboard_id = 0;
	adp_set_color(config->color, ADP_COLOR_BLACK);
	config->height = 100;
}

bool adp_add_dashboard(struct adp_msg_conf_dashboard *const config, const char* label);

/* MSG_CONF_DASHBOARD_ELEMENT */
#define MSG_CONF_DASHBOARD_ELEMENT 0x2B

enum adp_dashboard_element_type {
	ADP_ELEMENT_TYPE_LABEL,
	ADP_ELEMENT_TYPE_BUTTON,
	ADP_ELEMENT_TYPE_SLIDER,
	ADP_ELEMENT_TYPE_PROGRESS,
	ADP_ELEMENT_TYPE_SIGNAL,
	ADP_ELEMENT_TYPE_SEGMENT,
	ADP_ELEMENT_TYPE_GRAPH,
	ADP_ELEMENT_TYPE_TEXT,
	ADP_ELEMENT_TYPE_RADIO,
	ADP_ELEMENT_TYPE_PIE,
};

#define MSG_CONF_DASHBOARD_COMMON_LEN    14
#define ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS \
	uint16_t  dashboard_id; \
	uint16_t  element_id;   \
	uint8_t   z_index;      \
	uint16_t  x;            \
	uint16_t  y;            \
	uint16_t  width;        \
	uint16_t  height;       \
	enum adp_dashboard_element_type element_type 

SHORTENUM struct adp_msg_conf_dashboard_element_common {
	/* Dashboard ID */
	uint16_t  dashboard_id;
	/* Unique ID of element */
	uint16_t  element_id;
	/* Order index */
	uint8_t   z_index;
	/* X-coordinate of element location. 0 is leftmost position on dashboard */
	uint16_t  x;
	/* Y-coordinate of element location. 0 is topmost position on dashboard */
	uint16_t  y;
	/* Width of element */
	uint16_t  width;
	/* Height of element */
	uint16_t  height;
	/* See each element type below */
	enum adp_dashboard_element_type element_type;
};

static inline void adp_conf_dashboard_element_get_defaults(struct adp_msg_conf_dashboard_element_common *const config)
{
	Assert(config);
	config->dashboard_id = 0;
	config->element_id = 0;
	config->z_index = 0;
	config->x = 0;
	config->y = 0;
	config->width = 0;
	config->height = 0;
}

enum adp_label_attribute_alignment {
	BOLD_OFF_ITALIC_OFF,
	BOLD_ON_ITALIC_OFF,
	BOLD_OFF_ITALIC_ON,
	BOLD_ON_ITALIC_ON,
};

enum adp_label_horisontal_alignment {
	HORISONTAL_ALIGNMENT_LEFT,
	HORISONTAL_ALIGNMENT_CENTER,
	HORISONTAL_ALIGNMENT_RIGHT,
};

enum adp_label_vertical_alignment {
	VERTICAL_ALIGNMENT_TOP,
	VERTICAL_ALIGNMENT_CENTER,
	VERTICAL_ALIGNMENT_BOTTOM,
};

#define ADP_ELEMENT_TYPE_LABEL_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 12)
SHORTENUM struct adp_msg_conf_dashboard_element_label {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint8_t                             font_size;
	uint8_t                             attribute;                               // TODO
	enum adp_label_horisontal_alignment horisontal_alignment;
	enum adp_label_vertical_alignment   vertical_alignment;
	uint8_t                             background_transparency;
	uint8_t                             background_color[3];
	uint8_t                             foreground_transparency;
	uint8_t                             foreground_color[3];
};

static inline void adp_conf_dashboard_label_get_defaults(struct adp_msg_conf_dashboard_element_label *const config)
{
	adp_conf_dashboard_element_get_defaults((struct adp_msg_conf_dashboard_element_common*)config);
	config->element_type = ADP_ELEMENT_TYPE_LABEL;
	config->font_size = 10;
	config->attribute = 0;
	config->horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT;
	config->vertical_alignment = VERTICAL_ALIGNMENT_CENTER;
	config->background_transparency = 0;
	adp_set_color(config->background_color, ADP_COLOR_BLACK);
	config->foreground_transparency = 0;
	adp_set_color(config->foreground_color, ADP_COLOR_BLACK);
}

bool adp_add_label_to_dashboard(struct adp_msg_conf_dashboard_element_label *const config, const char* label);

#define ADP_ELEMENT_TYPE_BUTTON_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 1)

SHORTENUM struct adp_msg_conf_dashboard_element_button {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint8_t font_size;
};

static inline void adp_conf_dashboard_button_get_defaults(struct adp_msg_conf_dashboard_element_button *const config)
{
	adp_conf_dashboard_element_get_defaults((struct adp_msg_conf_dashboard_element_common*)config);
	config->element_type = ADP_ELEMENT_TYPE_BUTTON;
	config->font_size = 10;
}

bool adp_add_button_to_dashboard(struct adp_msg_conf_dashboard_element_button *const config, const char* label);

#define ADP_ELEMENT_TYPE_SLIDER_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 12)
SHORTENUM struct adp_msg_conf_dashboard_element_slider {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint32_t minimum_value;
	uint32_t maximum_value;
	uint32_t initial_value;
};

static inline void adp_conf_dashboard_slider_get_defaults(struct adp_msg_conf_dashboard_element_slider *const config)
{
	adp_conf_dashboard_element_get_defaults((struct adp_msg_conf_dashboard_element_common*)config);
	config->element_type = ADP_ELEMENT_TYPE_SLIDER;
	config->minimum_value = 0;
	config->maximum_value = 100;
	config->initial_value = 0;
}

bool adp_add_slider_to_dashboard(struct adp_msg_conf_dashboard_element_slider *const config);

#define ADP_ELEMENT_TYPE_SIGNAL_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 8)
SHORTENUM struct adp_msg_conf_dashboard_element_signal {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint8_t on_transparency;
	uint8_t on_color[3];
	uint8_t off_transparency;
	uint8_t off_color[3];
};

static inline void adp_conf_dashboard_signal_get_defaults(struct adp_msg_conf_dashboard_element_signal *const config)
{
	adp_conf_dashboard_element_get_defaults((struct adp_msg_conf_dashboard_element_common*)config);
	config->element_type = ADP_ELEMENT_TYPE_SIGNAL;
	config->on_transparency = 0;
	adp_set_color(config->on_color, ADP_COLOR_WHITE);
	config->off_transparency = 0;
	adp_set_color(config->off_color, ADP_COLOR_BLACK);
}

bool adp_add_signal_to_dashboard(struct adp_msg_conf_dashboard_element_signal *const config);

#define ADP_ELEMENT_TYPE_PROGRESS_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 15)
SHORTENUM struct adp_msg_conf_dashboard_element_progress {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint32_t minimum_value;
	uint32_t maximum_value;
	uint32_t initial_value;
	uint8_t color[3];
};

static inline void adp_conf_dashboard_progress_get_defaults(struct adp_msg_conf_dashboard_element_progress *const config)
{
	adp_conf_dashboard_element_get_defaults((struct adp_msg_conf_dashboard_element_common*)config);
	config->element_type = ADP_ELEMENT_TYPE_PROGRESS;
	config->minimum_value = 0;
	config->maximum_value = 100;
	config->initial_value = 0;
	adp_set_color(config->color, ADP_COLOR_BLACK);
}

bool adp_add_progress_to_dashboard(struct adp_msg_conf_dashboard_element_progress *const config);

#define ADP_ELEMENT_TYPE_SEGMENT_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 6)
SHORTENUM struct adp_msg_conf_dashboard_element_segment {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	/* Values: 1 ~ 20 */
	uint8_t segment_count;
	/* Values: 2 ~ 16*/
	uint8_t base;
	uint8_t transparency;
	uint8_t color[3];
};

static inline void adp_conf_dashboard_segment_get_defaults(struct adp_msg_conf_dashboard_element_segment *const config)
{
	adp_conf_dashboard_element_get_defaults((struct adp_msg_conf_dashboard_element_common*)config);
	config->element_type = ADP_ELEMENT_TYPE_SEGMENT;
	config->segment_count = 1;
	config->base = 10;
	config->transparency = 0;
	adp_set_color(config->color, ADP_COLOR_BLACK);
}

bool adp_add_segment_to_dashboard(struct adp_msg_conf_dashboard_element_segment *const config);

/* MSG_CONF_ADD_GRAPH_TO_ELEMENT */
#define  ADP_ELEMENT_TYPE_GRAPH_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 27)
typedef union {
	struct {
		uint8_t mouse:1;
		uint8_t fit_graph:1;
		uint8_t :6;
	} bit;
	uint8_t reg;
} mode_type;

SHORTENUM struct adp_msg_conf_dashboard_element_graph {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint8_t title_color[3];
	uint8_t background_color[3];
	uint8_t graph_background_color[3];
	uint8_t plot_count;
	float x_min;
	float x_max;
	float y_min;
	float y_max;
	mode_type mode;
};

static inline void adp_conf_dashboard_graph_get_defaults(struct adp_msg_conf_dashboard_element_graph *const config)
{
	adp_conf_dashboard_element_get_defaults((struct adp_msg_conf_dashboard_element_common*)config);
	config->element_type = ADP_ELEMENT_TYPE_GRAPH;
	adp_set_color(config->title_color, ADP_COLOR_WHITE);
	adp_set_color(config->background_color, ADP_COLOR_BLACK);
	adp_set_color(config->graph_background_color, ADP_COLOR_BLACK);
	config->plot_count = 1;
	config->x_min = 0;
	config->x_max = 10;
	config->y_min = 0;
	config->y_max = 5;
	config->mode.bit.fit_graph = 1;
	config->mode.bit.mouse = 0;
}

bool adp_add_graph_to_dashboard(struct adp_msg_conf_dashboard_element_graph *const config, const char* title);


/* MSG_CONF_ADD_TEXT_TO_ELEMENT */
#define  ADP_ELEMENT_TYPE_TEXT_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 12)
SHORTENUM struct adp_msg_conf_dashboard_element_text {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint8_t minimum[4];
	uint8_t maximum[4];
	uint8_t value[4];
};

bool adp_add_text_to_dashboard(struct adp_msg_conf_dashboard_element_text *const config);

/* MSG_CONF_ADD_RADIO_TO_ELEMENT */
#define  ADP_ELEMENT_TYPE_RADIO_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 3)

enum adp_radio_orientation {
	HORIZONTAL,
	VERTICAL,
};

SHORTENUM struct adp_msg_conf_dashboard_element_radio {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint8_t font_size;
	uint8_t number_items;
	enum adp_radio_orientation orientation;
};
bool adp_add_radio_to_dashboard(struct adp_msg_conf_dashboard_element_radio *const config, const char* text);

/* MSG_CONF_ADD_PIE_TO_ELEMENT */
#define  ADP_ELEMENT_TYPE_PIE_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 7)

SHORTENUM struct adp_msg_conf_dashboard_element_pie {
	ADP_DASHBOARD_ELEMENT_COMMON_MEMBERS;
	uint8_t background_color[3];
	uint8_t title_color[3];
	uint8_t number_slices;
};
bool adp_add_pie_to_dashboard(struct adp_msg_conf_dashboard_element_pie *const config, const char* title);

/* MSG_CONF_ADD_STREAM_TO_ELEMENT */
#define MSG_CONF_ADD_STREAM_TO_ELEMENT       0x2C
#define MSG_CONF_ADD_STREAM_TO_ELEMENT_LEN   6

SHORTENUM struct adp_conf_add_stream_to_element {
	uint16_t dashboard_id;
	uint16_t element_id;
	uint16_t stream_id;
};

bool adp_add_stream_to_element(struct adp_conf_add_stream_to_element *const config);

/* MSG_DATA_STREAM */
#define MSG_DATA_STREAM 0x40
SHORTENUM struct adp_msg_data_stream_data {
	uint16_t stream_id;
	uint8_t data_size;
	uint8_t *data;
};

SHORTENUM struct adp_msg_data_stream {
	uint8_t number_of_streams;
	struct adp_msg_data_stream_data stream[ADP_MAX_OUTGOING_STREAMS];
};

bool adp_send_stream(struct adp_msg_data_stream *const stream_data, uint8_t* receive_buf);
bool adp_send_single_stream(uint8_t stream_id, uint8_t* data, uint8_t data_size, uint8_t* receive_buf);
bool adp_transceive_stream(struct adp_msg_data_stream *const stream_data, uint8_t *receive_buf);
bool adp_transceive_single_stream(uint16_t stream_id, uint8_t* data, uint8_t data_size, uint8_t* receive_buf);

/* Init SPI/TWI interface used. And some other misc init */
void adp_init(void);
uint16_t adp_add_send_byte(uint8_t* buffer, uint8_t index, uint8_t* data, uint16_t length);

#endif
