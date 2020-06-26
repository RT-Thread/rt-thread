
#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern unsigned int __end__;
extern unsigned int __HeapLimit;
#define HEAP_BEGIN    (void*)&__end__
#define HEAP_END      (void*)&__HeapLimit
#endif

void rt_hw_board_init(void);

#endif

