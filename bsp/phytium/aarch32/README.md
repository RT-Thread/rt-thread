
# AARCH32 工作模式使用

- 当开发者需要基于我方芯片进行开发时，可以从以下几个步骤出发配置芯片

## 1. 如何选择芯片

```shell
    scons --menuconfig
```

开发者通过以下选择进行配置

```
Standalone Setting > Board Configuration > Chip 
```

![](./figures/chip_select.png)
![](./figures/phytium_cpu_select.png)

## 2. 如何选择驱动


```shell
    scons --menuconfig
```

开发者通过以下选项进行驱动的使能

```
Hardware Drivers Config > On-chip Peripheral Drivers
```

![](./figures/select_driver.png)


## 3. 开启SDK中内部调试信息


```shell
    scons --menuconfig
```

开发者通过以下选项进行调试信息等级的设置

![](./figures/select_debug_info.png)



## 4. 编译程序

```shell
    scons -c
    scons
```

- 完成编译之后目录下将会生成以下几个文件

```
rtthread.bin
rtthread.elf
rtthread.map
```
