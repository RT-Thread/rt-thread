/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
