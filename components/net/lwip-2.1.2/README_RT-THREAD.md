# lwip 移植说明

为了适配 RT-Thread 网卡设备，RT-Thread 团队基于原 [lwip](http://savannah.nongnu.org/projects/lwip/) 进行了一些修改，本文档记录了相关修改内容。

> 本 lwip-2.1.2 版本基于 [lwip STABLE-2_1_2_RELEASE](https://git.savannah.gnu.org/git/lwip.git) 版本移植而来。


| Date | Author | Notes |
| :---- | :---- | :---- |
| 2019-09-02 | MurphyZhao | 增加 lwip 2.1.2 移植说明 |

## 修改内容

### src/api

- `src/api/sockets.c` 增加 `lwip_tryget_socket` 函数，作为 `tryget_socket` 函数的全局实现
- `src/api/sockets.c` 在 `alloc_socket` 函数中，增加 SAL 移植函数 `rt_wqueue_init`

```
#ifdef SAL_USING_POSIX
      rt_wqueue_init(&sockets[i].wait_head);
#endif
```

### src/app

- 增加 `ping/ping.c`，便于在 finsh/msh 中使用 ping 功能
- 增加 `tftp/tftp_port.c`，便于在 finsh/msh 中使用 tftp_server 功能

### src/arch

增加 `src/arch` 目录，存储对接 RT-Thread 设备框架的移植文件，从 lwip-2.0.2 版本中的移植文件修改而来。

### src/core

- 在 `src/core/dns.c` 的 `dns_setserver` 函数中增加 RT-Thread netdev 相关的移植
- 在 `src/core/netif.c` 中增加 RT-Thread netdev 相关的移植

### src/include

- 在 `src/include/lwip/priv/sockets_priv.h` 中增加 SAL 相关的移植

    在 `lwip_sock` 结构体中增加 `  rt_wqueue_t wait_head;` 成员。

- 在 `src/include/lwip/init.h` 中的版本号后增加 `U` 标识
- 在 `src/include/lwip/sockets.h` 中增加 `LWIP_SOCKET_SELECT`，解决开启 RT_USING_POSIX 是的冲突
- 在 `src/include/netif/` 中增加 `ethernetif.h`，用于对接 RT-Thread 网卡设备

### src/netif

- 在 `src/netif/` 中增加 `ethernetif.c`，用于对接 RT-Thread 网卡设备
- 在 `src/netif/lowpan6.c` 中增加 `LWIP_6LOWPAN` 宏定义，以防止编译错误

### src

- 在 src 目录下，增加 `src/lwipopts.h`，用于 lwip 功能裁剪以及配置设置
- 在 src 目录下，增加 `src/lwippools.h`，用于定义 `LWIP_MALLOC_MEMPOOL`

### 其它

- 增加 SConscript 文件，用于 scons 构建
- 增加 README_RT-THREAD.md 文件，用于记录相对原 lwip 源码的改动
