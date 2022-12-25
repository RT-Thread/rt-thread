#ifndef __BNR_FIRMWARE_H__
#define __BNR_FIRMWARE_H__

#include "img_struct.h"

void bnr_init();
void bnr_config(const bnr_fw_config_t *config);
void bnr_control(BL_GAIN_DB gain);
void bnr_hw_update(void);

void bnr_control_debug();
#endif
