/*
Copyright 2020 Shenzhen Academy of Aerospace Technology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Change Logs:
Date           Author       Notes
2020-10-16     Dystopia     the first version
*/

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

void rt_hw_interrupt_control(int vector, int priority, int route);
int rt_hw_interrupt_get_active(int fiq_irq);
void rt_hw_interrupt_ack(int fiq_irq);
void rt_hw_interrupt_trigger(int vector);
void rt_hw_interrupt_clear(int vector);

#endif
