/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2019-07-16  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#ifndef __APPLICATION_CAN_H_
#define __APPLICATION_CAN_H_

#include <rtthread.h>

/**
 * @brief External function definitions
 *
 */
rt_err_t can_demo_run(void);

rt_err_t can_send_message(struct can_message *msg, rt_uint32_t timeouts);

#endif // __APPLICATION_CAN_H_
