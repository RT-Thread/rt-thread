/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __CORE_TASK_H__
#define __CORE_TASK_H__
typedef struct
{
    uint32_t ID;
    uint32_t Param1;
    uint32_t Param2;
    uint32_t Param3;
}Task_EventStruct;
#define OS_EVENT Task_EventStruct
HANDLE Task_Create(TaskFun_t EntryFunction, void *Param, uint32_t StackSize, uint32_t Priority, const char *Name);
void Task_SendEvent(HANDLE TaskHandle, uint32_t ID, uint32_t P1, uint32_t P2, uint32_t P3);
int32_t Task_GetEvent(HANDLE TaskHandle, uint32_t TargetEventID, Task_EventStruct *OutEvent, CBFuncEx_t Callback, uint64_t Tick);
int32_t Task_GetEventByMS(HANDLE TaskHandle, uint32_t TargetEventID, Task_EventStruct *OutEvent, CBFuncEx_t Callback, uint32_t ms);
HANDLE Task_GetCurrent(void);
void Task_DelayTick(uint64_t Tick);
void Task_DelayUS(uint32_t US);
void Task_DelayMS(uint32_t MS);
#endif
