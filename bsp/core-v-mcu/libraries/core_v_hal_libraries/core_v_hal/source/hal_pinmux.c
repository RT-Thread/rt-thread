/*
 * Copyright 2021 QuickLogic
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 #include "rtconfig.h"
 #include "core-v-mcu-config.h"
 #include "hal_apb_soc_ctrl_regs.h"
 #include "hal_pinmux.h"
 #ifdef PKG_USING_FREERTOS_WRAPPER
 #include "FreeRTOS.h"
 #endif
 void hal_setpullup(uint8_t io_num, uint8_t on) {
 	SocCtrl_t*		psoc_ctrl = SOC_CTRL_START_ADDR;

 	configASSERT (io_num < N_IO);
	psoc_ctrl->io_ctrl_b[io_num].cfg = on;
 }
 
 void hal_setpinmux(uint8_t io_num, uint8_t mux_sel) {
 	SocCtrl_t*		psoc_ctrl = SOC_CTRL_START_ADDR;
 	
 	configASSERT (io_num < N_IO);
	psoc_ctrl->io_ctrl_b[io_num].mux = mux_sel;
 }
 
 uint8_t hal_getpinmux(uint8_t io_num) {
 	SocCtrl_t*		psoc_ctrl = SOC_CTRL_START_ADDR;
 	
 	configASSERT (io_num < N_IO);
	return psoc_ctrl->io_ctrl_b[io_num].mux;
 }
