# Roadmap for RT-Thread 1.2.0 #

The document is the mainly task of RT-Thread 1.2.0. In this series, there will be a full manual document for RT-Thread 1.x series. The format of document is markdown document[0] on github.com and some hardware environment is used in document (RT-Thread Real-Touch[1]).

The document will be wroten in Chinese firstly. At least when RT-Thread 1.2.0 has officially released, the Chinese edition of manual is ready. The manual includes:

1. RT-Thread Kernel (The basic facilities in RTOS)
2. How to port RT-Thread in a new architecture.
3. RT-Thread components.
4. How to debug in RT-Thread. 

## Other codes changes in planning ##

### Improvement on bsp porting ###

- LPC18xx & LPC43xx
  * USB host and device driver;

- Other BSP.
  * welcome contributions. 

### New features on Components ###

- device IPC
  * implement the work queue[2].
  * implement the rwlock[3].
  * The APIs are like *BSD, but implement in RT-Thread

- finsh shell
  * implement a UNIX style shell, and this shell can execute application module. 

- device file system
  * implement select[4] API for device object in RT-Thread. 

- lwIP TCP/IP stack
  * enable IPv6 feature[5].

- gdb server or stub

[0] RT-Thread manual: https://github.com/RT-Thread/manual-doc
[1] RT-Thread Real-Touch: https://github.com/RT-Thread/realtouch-stm32f4
[2] work queue: http://fxr.watson.org/fxr/source/sys/workqueue.h?v=NETBSD
[3] rwlock: http://fxr.watson.org/fxr/source/sys/rwlock.h?v=NETBSD
[4] select API: http://pubs.opengroup.org/onlinepubs/7908799/xsh/select.html
[5] dual IPv4/v6 stack: http://lwip.wikia.com/wiki/LwIP_IPv4/IPv6_stacks
