/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CMD_DEFS_H_
#define _CMD_DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

enum cmd_code_type {
    CMD_CODE_TYEP_STATUS = 0,
    CMD_CODE_TYEP_EVENT,
};

enum cmd_status {
    CMD_STATUS_ACKED        = 100,  /* already acked, no need to send respond */

    /* success status */
    CMD_STATUS_SUCCESS_MIN  = 200,
    CMD_STATUS_OK           = 200,  /* command exec success */
    CMD_STATUS_SUCCESS_MAX  = 200,

    /* error status */
    CMD_STATUS_ERROR_MIN    = 400,
    CMD_STATUS_UNKNOWN_CMD  = 400,  /* unknown command */
    CMD_STATUS_INVALID_ARG  = 401,  /* invalid argument */
    CMD_STATUS_FAIL         = 402,  /* command exec failed */
    CMD_STATUS_ERROR_MAX    = 402,
};

enum cmd_event {
    CMD_EVENT_MIN           = 600,
    CMD_EVENT_TEST_FINISH   = 600,
    CMD_EVENT_TIMER_NOTIFY  = 601,
    CMD_EVENT_RTC_NOTIFY    = 602,
    CMD_EVENT_MQTT_MSG_RECV = 603,
    CMD_EVENT_WDG_TIMEOUT   = 604,
    CMD_EVENT_MAX           = 604,
};

#ifdef __cplusplus
}
#endif

#endif /* _CMD_DEFS_H_ */
