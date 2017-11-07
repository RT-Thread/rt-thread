#ifndef __INTERRUPT_H
#define __INTERRUPT_H
#include "io.h"
void rt_hw_interrupt_mask(int num);
void rt_hw_interrupt_unmask(int num);
#endif
