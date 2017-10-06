Andes Maintainer:  **It's a very early and draft porting yet.**

E-Mail : Archer Zhang <archer.zhang@wh-mx.com>

## 文件（夹）添加和修改

1. 在bsp目录下，添加AE210P目录，这是Andes AE210P EVB（N1068A）的主目录；
2. 在libcpu目录下，添加nds32目录，这是Andes N10系列Core的体系目录；
3. 由于编译器的原因，修改了finsh.h文件的Line：74 - 75，如下
```c
    #if !(defined(__GNUC__) && defined(__x86_64__))
    //typedef unsigned int size_t; // 注释这个typedef
    #include <stddef.h> // 添加两个头文件包含
    #include <string.h>
    #else
```

4. 由于串口未使用中断接收，而是使用了查询接收，所以修改了shell.c文件，如下
```c
    a. Line：316～317
    //rt_device_set_rx_indicate(shell->device, finsh_rx_ind);
    //rt_device_open(shell->device, (RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX));
    rt_device_open(shell->device, (RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_STREAM));

    b. Line：326，注释该行
    // if (rt_sem_take(&shell->rx_sem, RT_WAITING_FOREVER) != RT_EOK) continue;

    c. Line：553，添加CPU占用的释放

    rt_thread_delay(1); // 或者rt-schedule();
```

## 工程管理

1. 该工程使用Makefile管理，Makefile即文件AE210P/Makefile。编译如下：
```bash
    make APP=rtthread AE210P=1 USING_CLI=1 DEBUG=1 all
    make APP=rtthread AE210P=1 USING_CLI=1 DEBUG=1 clean
```

## Tool Chain/IDE

1. IDE：AndeSight_V300_STD

这是一个基于Eclipse和GNU、GDB的环境，参阅对应工具/环境的标准文档即可。

关于创建工程和调试，请参阅《Andes工程创建和调试.docx》。

## 测试目标板（PCBA）

1. AE210P EVB
