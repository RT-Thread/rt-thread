#ifndef OPENAMP_CONFIGS_H
#define OPENAMP_CONFIGS_H

#include "fmmu.h"
#include "memory_layout.h"
#include "board.h"

#if defined __cplusplus
extern "C" {
#endif

/* 从核发送消息时，需要指定发送的cpu的核号，用来确定软件中断的发送到哪个核上 */

#define MASTER_CORE_MASK              255 /* 采用协商好的方式，给所有核心都发送中断，注意：裸机接口层PhytiumProcNotify()做了区分 */

#if defined __cplusplus
}
#endif

#endif /* OPENAMP_CONFIGS_H */
