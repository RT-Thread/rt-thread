/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef PLATFORM_DEF_H_
#define PLATFORM_DEF_H_

#include "rtconfig.h"

#ifdef CONFIG_CHIP_FH8620
#ifdef CONFIG_BOARD_DEV
#include "fh8620/dev_board/board_def.h"
#endif
#endif

#ifdef CONFIG_CHIP_FH8620
#ifdef CONFIG_BOARD_TEST
#include "fh8620/test_board/board_def.h"
#endif
#endif

#ifdef CONFIG_CHIP_FH8620
#ifdef CONFIG_BOARD_IOTCAM
#include "fh8620/iot_cam/board_def.h"
#endif
#endif

#ifdef CONFIG_CHIP_FH8620G
#ifdef CONFIG_BOARD_DEV
#include "fh8620g/dev_board/board_def.h"
#endif
#endif

#ifdef CONFIG_CHIP_FH8620G
#ifdef CONFIG_BOARD_TEST
#include "fh8620g/test_board/board_def.h"
#endif
#endif


#ifdef CONFIG_CHIP_FH8810
#ifdef CONFIG_BOARD_DEV
#include "fh8810/dev_board/board_def.h"
#endif
#endif



#ifdef CONFIG_CHIP_FH8810
#ifdef CONFIG_BOARD_TEST
#include "fh8810/test_board/board_def.h"
#endif
#endif





#endif /* TEST_H_ */
