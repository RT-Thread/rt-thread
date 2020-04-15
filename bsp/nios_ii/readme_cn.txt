1. 按常规方法建立一个空白Nios II工程.
2. 添加本目录的所有源程序和头文件,并添加RT-Thread内核及Nios II CPU所需要的文件.
─rt-thread
   │
   ├─include
   │      rtdef.h
   │      rthw.h
   │      rtm.h
   │      rtthread.h
   │
   ├─libcpu
   │  └─nios
   │      └─nios_ii
   │              context_gcc.S
   │              interrupt.c
   │              stack.c
   │              vector.S
   │
   └─src
           clock.c
           device.c
           idle.c
           ipc.c
           irq.c
           kservice.c
           kservice.h
           mem.c
           mempool.c
           object.c
           rtm.c
           scheduler.c
           SConscript
           slab.c
           thread.c
           timer.c
3. 添加头文件搜索路径
4. 根据需要修改rtconfig.h (默认为基本内核)
