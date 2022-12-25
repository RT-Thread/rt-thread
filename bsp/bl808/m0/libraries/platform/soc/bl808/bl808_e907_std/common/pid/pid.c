/**
 * @file pid.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#include "pid.h"

void pid_init(pid_alg_t *pid)
{
    pid->set_val = 0.0f;
    pid->out_val = 0.0f;

    pid->last_error = 0.0f;
    pid->prev_error = 0.0f;

    pid->kp = 3.0f;
    pid->ki = 0.0f;
    pid->kd = 0.0f;

    pid->i_error = 0.0f;
    pid->sum_error = 0.0f;

    pid->max_val = 32;
    pid->min_val = -32;
}

// standard pid
float standard_pid_cal(pid_alg_t *pid, float next_val)
{
    pid->set_val = next_val;
    pid->i_error = pid->set_val - pid->out_val;
    pid->sum_error += pid->i_error;
    pid->out_val = pid->kp * pid->i_error + pid->ki * pid->sum_error + pid->kd * (pid->i_error - pid->last_error);
    pid->last_error = pid->i_error;

    return pid->out_val;
}

// increment pid
float increment_pid_cal(pid_alg_t *pid, float next_val)
{
    pid->set_val = next_val;
    pid->i_error = pid->set_val - pid->out_val;
    float increment = pid->kp * (pid->i_error - pid->prev_error) + pid->ki * pid->i_error + pid->kd * (pid->i_error - 2 * pid->prev_error + pid->last_error);
    pid->out_val += increment;
    pid->last_error = pid->prev_error;
    pid->prev_error = pid->i_error;

    return pid->out_val;
}
