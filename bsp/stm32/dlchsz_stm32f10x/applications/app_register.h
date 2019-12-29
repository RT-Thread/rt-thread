#ifndef __APP_REGISTER_H__
#define __APP_REGISTER_H__

#include <board.h>

#pragma pack(push)
#pragma pack(1)
struct tab_bits_rubbish_station {
	rt_uint16_t light:1; 	//照明灯
	rt_uint16_t reserved[3];
};

struct tab_bits {
	rt_uint16_t reserved[16];
	struct tab_bits_rubbish_station rubbish_station;
	rt_uint16_t reserved[];
	
}; 

struct tab_input_registers {
	
};

struct tab_register {
	
};
#pragma pack(pop)

struct app_register {
	
};

extern struct app_register g_app_register;

#endif

