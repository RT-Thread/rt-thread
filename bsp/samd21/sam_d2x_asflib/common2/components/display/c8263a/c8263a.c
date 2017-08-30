/**
 * \file
 *
 * \brief Management of C8263A LCD Glass component.
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
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

#include "slcd.h"
#include "c8263a.h"
#include "config_c8263a.h"
#include <string.h>

const uint32_t charactor_map[] = {
	0xE85C, 0x2008, 0xA314, 0xA30C, 0x6308, 0xC30C, 0xC31C, 0xA008, 0xE31C, 0xE30C, /* 0-9 */
	0xE318, 0xA68C, 0xC014, 0xA48C, 0xC314, 0xC310, 0xC21C, /* A-G */
	0x6318, 0x8484, 0x201C, 0x4930, 0x4014, 0x7818, 0x7038, /* H-N */
	0xE01C, 0xE310, 0xE03C, 0xE330, 0xC30C, 0x8480, /* O-T */
	0x601C, 0x4850, 0x6078, 0x1860, 0x1880, 0x8844  /* U-Z */
};
const uint32_t num_map[10] = {0x77, 0x24, 0x5d, 0x6d, 0x2e, 0x6b, 0x7b, 0x25, 0x7f, 0x6f };

void c8263a_init(void)
{
	struct slcd_config config;

	slcd_get_config_defaults(&config);
	config.enable_bias_buffer = true;
	slcd_init(&config);

	slcd_set_frame_counter(SLCD_FRAME_COUNTER_0,false,CONF_C8263A_FC0);
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_1,false,CONF_C8263A_FC1);
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_2,false,CONF_C8263A_FC2);
	slcd_set_contrast(CONF_C8263A_CONTRAST);
	slcd_enable();
}

void c8263a_show_all(void)
{
	slcd_set_display_memory();
}

void c8263a_clear_all(void)
{
	slcd_disable_blink();
	slcd_disable_circular_shift();
	slcd_clear_display_memory();
}

void c8263a_show_text(const uint8_t *data)
{
	Assert(data);
	uint32_t len = (uint32_t)strlen((char *) data);

	len = (len > C8263A_MAX_CHAR) ? C8263A_MAX_CHAR : len;

	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,C8263A_CHAR_MAP_NUM_SEG-1);
	for(uint32_t i = 0 ; i < len ; i++) {
		if(data[i] >= '0' && data[i] <= '9') {
			slcd_character_write_data(0,C8263A_CHAR_SEG_INDEX_S+i*C8263A_CHAR_MAP_NUM_SEG,
				charactor_map[data[i] - '0'],C8263A_CHAR_MASK);
		} else if(data[i] >= 'A' && data[i] <= 'Z') {
			slcd_character_write_data(0,C8263A_CHAR_SEG_INDEX_S+i*C8263A_CHAR_MAP_NUM_SEG,
				charactor_map[data[i] - 'A' +10],C8263A_CHAR_MASK);
		} else if(data[i] >= 'a' && data[i] <= 'z') {
			slcd_character_write_data(0,C8263A_CHAR_SEG_INDEX_S+i*C8263A_CHAR_MAP_NUM_SEG,
				charactor_map[data[i] - 'a' +10],C8263A_CHAR_MASK);
		} else {
			slcd_character_write_data(0,C8263A_CHAR_SEG_INDEX_S+i*C8263A_CHAR_MAP_NUM_SEG,
				charactor_map[0],C8263A_CHAR_MASK);
		}

	}

}
void c8263a_clear_text(void)
{
	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,C8263A_CHAR_MAP_NUM_SEG-1);
	for(uint32_t i = 0 ; i < C8263A_MAX_CHAR ; i++) {
	  slcd_character_write_data(0,C8263A_CHAR_SEG_INDEX_S+i*C8263A_CHAR_MAP_NUM_SEG,0,C8263A_CHAR_MASK);
	}
}

void c8263a_show_icon(uint8_t icon_com, uint8_t icon_seg)
{
	slcd_set_pixel(icon_com, icon_seg);
}

void c8263a_clear_icon(uint8_t icon_com, uint8_t icon_seg)
{
	slcd_clear_pixel(icon_com, icon_seg);
}

void c8263a_blink_icon_start(uint8_t icon_com, uint8_t icon_seg)
{
	if (icon_seg < 2) {
		slcd_disable();
		struct slcd_blink_config blink_config;
		slcd_blink_get_config_defaults(&blink_config);
		blink_config.blink_all_seg = false;
		blink_config.fc = CONF_C8263A_BLINK_TIMER;
		slcd_blink_set_config(&blink_config);
		slcd_set_pixel(icon_com, icon_seg);
		slcd_set_blink_pixel(icon_com, icon_seg);
		slcd_enable_frame_counter(CONF_C8263A_BLINK_TIMER);
		slcd_enable_blink();
		slcd_enable();
	}

}

void c8263a_blink_icon_stop(uint8_t icon_com, uint8_t icon_seg)
{
	if (icon_seg < 2) {
		slcd_disable_blink();
		slcd_disable();
		slcd_clear_blink_pixel(icon_com, icon_seg);
		slcd_enable_blink();
		slcd_enable();
	}
}

void c8263a_blink_screen(void)
{
	slcd_disable_blink();
	slcd_disable();
	struct slcd_blink_config blink_config;
	slcd_blink_get_config_defaults(&blink_config);
	blink_config.blink_all_seg = true;
	blink_config.fc = CONF_C8263A_BLINK_TIMER;
	slcd_blink_set_config(&blink_config);

	slcd_enable_frame_counter(CONF_C8263A_BLINK_TIMER);
	slcd_enable_blink();
	slcd_enable();
}

void c8263a_blink_disable(void)
{
	slcd_disable_frame_counter(CONF_C8263A_BLINK_TIMER);
	slcd_disable_blink();
}

void c8263a_set_contrast(uint8_t contrast)
{
	slcd_set_contrast(contrast);
}

void c8263a_show_battery(enum c8263a_battery_value val)
{
	if (val <= C8263A_BATTERY_THREE )
	{
		slcd_clear_pixel(C8263A_ICON_BAT_LEVEL_1);
		slcd_clear_pixel(C8263A_ICON_BAT_LEVEL_2);
		slcd_clear_pixel(C8263A_ICON_BAT_LEVEL_3);
		slcd_set_pixel(C8263A_ICON_BAT);
		switch (val) {
			case C8263A_BATTERY_THREE:
				slcd_set_pixel(C8263A_ICON_BAT_LEVEL_3);
			case C8263A_BATTERY_TWO:
				slcd_set_pixel(C8263A_ICON_BAT_LEVEL_2);
			case C8263A_BATTERY_ONE:
				slcd_set_pixel(C8263A_ICON_BAT_LEVEL_1);
				break;
			case C8263A_BATTERY_NONE:
				break;
		}
	}
}

void c8263a_show_wireless(enum c8263a_wireless_value val)
{
	slcd_clear_pixel(C8263A_ICON_WLESS_LEVEL_1);
	slcd_clear_pixel(C8263A_ICON_WLESS_LEVEL_2);
	slcd_clear_pixel(C8263A_ICON_WLESS_LEVEL_3);
	slcd_set_pixel(C8263A_ICON_WLESS_LEVEL_0);
	switch (val) {
		case C8263A_WIRELESS_THREE:
			slcd_set_pixel(C8263A_ICON_WLESS_LEVEL_3);
		case C8263A_WIRELESS_TWO:
			slcd_set_pixel(C8263A_ICON_WLESS_LEVEL_2);
		case C8263A_WIRELESS_ONE:
			slcd_set_pixel(C8263A_ICON_WLESS_LEVEL_1);
			break;
		case C8263A_WIRELESS_NONE:
			break;
	}
}

void c8263a_show_numeric_dec(int32_t value)
{
	uint32_t tmp=0;
	uint8_t i=0;
	Assert(value > -200000);
	Assert(value < 200000);

	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,C8263A_DIGITAL_MAP_NUM_SEG-1);

	if(value < 0) {
		slcd_set_pixel(C8263A_ICON_MINUS);
	} else {
		slcd_clear_pixel(C8263A_ICON_MINUS);
	}

	tmp = Abs(value);

	if (tmp > 99999) {
		slcd_set_pixel(C8263A_ICON_MINUS_SEG1);
		slcd_set_pixel(C8263A_ICON_MINUS_SEG2);
		tmp -= 100000;
	} else {
		slcd_clear_pixel(C8263A_ICON_MINUS_SEG1);
		slcd_clear_pixel(C8263A_ICON_MINUS_SEG2);
	}

	while(tmp != 0 && i < C8263A_MAX_DIGITAL){
		if (i == C8263A_MAX_DIGITAL - 1) {
			slcd_character_write_data(0,C8263A_DIGITAL_SEG_INDEX_E - i*C8263A_DIGITAL_MAP_NUM_SEG - 2,
					num_map[tmp%10],C8263A_DIGITAL_MASK);
		} else {
			slcd_character_write_data(0,C8263A_DIGITAL_SEG_INDEX_E - i*C8263A_DIGITAL_MAP_NUM_SEG,
					num_map[tmp%10],C8263A_DIGITAL_MASK);
		}
		tmp /=10;
		i++;
	}
}

void c8263a_clear_numeric_dec(void)
{
	slcd_clear_pixel(C8263A_ICON_MINUS);
	slcd_clear_pixel(C8263A_ICON_MINUS_SEG1);
	slcd_clear_pixel(C8263A_ICON_MINUS_SEG2);
	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,C8263A_DIGITAL_MAP_NUM_SEG-1);
	for(uint32_t i = 0 ; i < C8263A_MAX_DIGITAL ; i++) {
		if (i == 0) {
	  		slcd_character_write_data(0,C8263A_DIGITAL_SEG_INDEX_S + i*C8263A_DIGITAL_MAP_NUM_SEG,
					0, C8263A_DIGITAL_MASK);
		} else {
			slcd_character_write_data(0,C8263A_DIGITAL_SEG_INDEX_S + i*C8263A_DIGITAL_MAP_NUM_SEG + 2,
					0, C8263A_DIGITAL_MASK);
		}
	}
}

void c8263a_circular_animation_start(uint8_t size, uint8_t data)
{
	struct slcd_circular_shift_config cfg;
	slcd_disable();
	slcd_circular_shift_get_config_defaults(&cfg);
	cfg.data = data;
	cfg.size = size;
	cfg.dir = C8263A_CSR_DIR;
	cfg.fc = CONF_C8263A_CIRCULAR_ANIMATION_TIMER;
	slcd_circular_shift_set_config(&cfg);
	slcd_enable_circular_shift();
	slcd_enable_frame_counter(CONF_C8263A_CIRCULAR_ANIMATION_TIMER);
	slcd_enable();
}

void c8263a_circular_animation_stop(void)
{
	slcd_disable_frame_counter(CONF_C8263A_CIRCULAR_ANIMATION_TIMER);
	slcd_disable_circular_shift();
}

