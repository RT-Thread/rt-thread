# RT-Thread package.json 构建支持

## 概述

RT-Thread支持使用package.json来定义组件的构建配置，作为传统SConscript的简化替代方案。

## 现有支持

### package.json格式
```json
{
  "name": "hello",
  "description": "Hello World component for RT-Thread",
  "type": "rt-thread-component",
  "dependencies": ["RT_USING_HELLO"],
  "defines": [],
  "sources": [{
    "name": "src",
    "dependencies": [],
    "includes": ["."],
    "files": ["hello.c"]
  }]
}
```

### 字段说明
- **name**: 组件名称（必需）
- **type**: 必须为"rt-thread-component"（必需）
- **description**: 组件描述
- **dependencies**: 全局依赖，数组形式的宏定义
- **defines**: 全局宏定义
- **sources**: 源文件组数组，每组可包含：
  - **name**: 源组名称
  - **dependencies**: 源组特定依赖
  - **includes**: 头文件搜索路径
  - **files**: 源文件列表（支持通配符）

## 使用方式

### 1. 在SConscript中使用

方式一：使用PackageSConscript（推荐）
```python
from building import *

objs = PackageSConscript('package.json')
Return('objs')
```

方式二：直接调用BuildPackage
```python
Import('env')
from package import BuildPackage

objs = BuildPackage('package.json')
Return('objs')
```

### 2. 目录结构示例
```
mycomponent/
├── SConscript
├── package.json
├── mycomponent.c
├── mycomponent.h
└── src/
    └── helper.c
```

### 3. 完整示例

package.json:
```json
{
  "name": "mycomponent",
  "description": "My RT-Thread component",
  "type": "rt-thread-component",
  "dependencies": ["RT_USING_MYCOMPONENT"],
  "defines": ["MY_VERSION=1"],
  "sources": [
    {
      "name": "main",
      "dependencies": [],
      "includes": ["."],
      "files": ["mycomponent.c"]
    },
    {
      "name": "helper",
      "dependencies": ["RT_USING_MYCOMPONENT_HELPER"],
      "includes": ["src"],
      "files": ["src/*.c"]
    }
  ]
}
```

## 工作原理

1. **依赖检查**：首先检查全局dependencies，如果不满足则跳过整个组件
2. **源组处理**：遍历sources数组，每个源组独立检查dependencies
3. **路径处理**：includes相对路径基于package.json所在目录
4. **文件匹配**：使用SCons的Glob函数处理文件通配符
5. **构建调用**：最终调用DefineGroup创建构建组

## 与DefineGroup的对比

| 特性 | package.json | DefineGroup |
|------|--------------|-------------|
| 配置方式 | JSON文件 | Python代码 |
| 依赖管理 | 结构化 | 函数参数 |
| 源文件组织 | 分组管理 | 单一列表 |
| 条件编译 | 源组级别 | 整体级别 |
| 灵活性 | 中等 | 高 |
| 易用性 | 高 | 中等 |

## 最佳实践

1. **简单组件优先使用package.json**：配置清晰，易于维护
2. **复杂逻辑使用SConscript**：需要动态逻辑时使用传统方式
3. **混合使用**：可以在同一项目中混用两种方式

## 注意事项

1. package.json必须是有效的JSON格式
2. type字段必须为"rt-thread-component"
3. 文件路径相对于package.json所在目录
4. 依赖不满足时会静默跳过，不会报错
5. 与RT-Thread构建系统完全集成，不支持独立构建