# fdt

## 1、介绍
fdt基于libfdt进行封装，可实现在内存或文件系统中加载dtb设备树，对内存中的设备树修改、解析，并转换为设备节点树，通过该节点树开发者可通过设备树信息开发驱动。

### 1.1 目录结构
| 名称 | 说明 |
| ---- | ---- |
| docs  | 文档目录 |
| examples | 例子目录，并有相应的一些说明 |
| inc  | 头文件目录 |
| src  | 源代码目录 |

### 1.2 许可证
fdt package 遵循 GPL-3.0 许可，详见 LICENSE 文件。

### 1.3 依赖
- RT-Thread 3.0+

## 2、如何打开 fdt
使用 fdt package 需要在 RT-Thread 的包管理器中选择它，具体路径如下：

```
RT-Thread online packages
    tools packages --->
        [*] Device Tree package in RT-Thread
```

## 3、使用 fdt
在打开 fdt package 后，当进行 bsp 编译时，它会被加入到 bsp 工程中进行编译。

* 完整的 API 手册可以访问这个[链接](docs/api.md)
* 更多文档位于 [`/docs`](/docs) 下，使用前 **务必查看**

## 4、注意事项
如果发生`libfdt`库冲突，在package管理菜单中取消选择`Enable libfdt`

## 5、联系方式

* 维护：GuEe-GUI
* 主页：https://github.com/GuEe-GUI/fdt