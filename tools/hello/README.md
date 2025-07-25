# Hello Component

这是一个使用package.json配置的RT-Thread组件示例，展示了如何使用package.json来替代传统的SConscript中DefineGroup的方式。

## 文件结构

```
hello/
├── hello.h          # 头文件
├── hello.c          # 源文件
├── package.json     # 组件配置文件
├── SConscript       # 构建脚本
└── README.md        # 说明文档
```

## package.json配置说明

package.json文件包含了组件的所有构建信息：

- `name`: 组件名称
- `version`: 版本号
- `description`: 组件描述
- `author`: 作者信息
- `license`: 许可证
- `source_files`: 源文件列表
- `CPPPATH`: 头文件搜索路径
- `CPPDEFINES`: 预定义宏
- `depends`: 依赖的组件

## 使用方法

1. 将hello文件夹复制到你的RT-Thread项目的components目录下
2. 在应用代码中包含头文件：
   ```c
   #include "hello.h"
   ```
3. 调用hello_world函数：
   ```c
   hello_world();  // 输出: Hello World!
   ```

## 构建过程

SConscript文件会：
1. 导入package.py模块
2. 调用BuildPackage函数处理package.json
3. 自动创建DefineGroup并返回构建对象

这种方式比传统的SConscript更加简洁和易于维护。 