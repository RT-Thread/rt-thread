# RT-Thread SConscript 编写指南

## 目录

1. [概述](#概述)
2. [基础语法](#基础语法)
3. [常用模式](#常用模式)
4. [高级技巧](#高级技巧)
5. [最佳实践](#最佳实践)
6. [示例集合](#示例集合)
7. [常见问题](#常见问题)

## 概述

SConscript是RT-Thread构建系统中的模块构建脚本，每个组件或目录都可以有自己的SConscript文件。本指南将详细介绍如何编写高质量的SConscript文件。

### SConscript在构建系统中的位置

```
项目根目录/
├── SConstruct          # 主构建脚本
├── applications/
│   └── SConscript      # 应用层构建脚本
├── drivers/
│   └── SConscript      # 驱动层构建脚本
└── components/
    ├── SConscript      # 组件主脚本
    └── finsh/
        └── SConscript  # 子组件脚本
```

## 基础语法

### 1. 基本结构

```python
# 导入构建模块
from building import *

# 获取当前目录
cwd = GetCurrentDir()

# 定义源文件
src = ['main.c', 'app.c']

# 定义头文件路径
CPPPATH = [cwd]

# 定义组
group = DefineGroup('Applications', src, depend = [''], CPPPATH = CPPPATH)

# 返回组对象
Return('group')
```

### 2. 导入building模块

```python
from building import *
```

这行代码导入了RT-Thread构建系统的所有函数，包括：
- `GetCurrentDir()` - 获取当前目录
- `DefineGroup()` - 定义组件组
- `GetDepend()` - 检查依赖
- `Glob()` - 文件通配符匹配
- `SrcRemove()` - 移除源文件
- `DoBuilding()` - 执行构建

### 3. 源文件定义

#### 手动指定文件列表
```python
src = ['file1.c', 'file2.c', 'file3.c']
```

#### 使用通配符
```python
src = Glob('*.c')           # 当前目录所有.c文件
src = Glob('src/*.c')       # src子目录所有.c文件
src = Glob('**/*.c')        # 递归所有子目录的.c文件
```

#### 混合使用
```python
src = ['main.c'] + Glob('drivers/*.c')
```

### 4. 条件编译

#### 基于宏定义
```python
src = ['common.c']

if GetDepend('RT_USING_SERIAL'):
    src += ['serial.c']

if GetDepend('RT_USING_I2C'):
    src += ['i2c.c']
```

#### 基于平台
```python
import rtconfig

if rtconfig.PLATFORM == 'gcc':
    src += ['gcc_specific.c']
elif rtconfig.PLATFORM == 'armcc':
    src += ['keil_specific.c']
```

### 5. 移除文件

```python
src = Glob('*.c')
SrcRemove(src, ['test.c', 'debug.c'])  # 移除不需要的文件
```

## 常用模式

### 1. 简单组件模式

最基础的SConscript模式：

```python
from building import *

src = Glob('*.c')
CPPPATH = [GetCurrentDir()]

group = DefineGroup('MyComponent', src, depend = ['RT_USING_MYCOMPONENT'], 
                    CPPPATH = CPPPATH)

Return('group')
```

### 2. 条件编译模式

根据配置选项包含不同的源文件：

```python
from building import *

src = ['core.c']
CPPPATH = [GetCurrentDir()]

# 功能模块条件编译
if GetDepend('MYCOMPONENT_USING_FEATURE_A'):
    src += ['feature_a.c']

if GetDepend('MYCOMPONENT_USING_FEATURE_B'):
    src += ['feature_b.c']

# 平台相关代码
if rtconfig.PLATFORM == 'gcc':
    src += ['port_gcc.c']
elif rtconfig.PLATFORM == 'armcc':
    src += ['port_keil.c']
elif rtconfig.PLATFORM == 'iccarm':
    src += ['port_iar.c']

group = DefineGroup('MyComponent', src, depend = ['RT_USING_MYCOMPONENT'], 
                    CPPPATH = CPPPATH)

Return('group')
```

### 3. 多目录组织模式

处理复杂的目录结构：

```python
from building import *

cwd = GetCurrentDir()

# 源文件来自多个目录
src = Glob('src/*.c')
src += Glob('port/*.c')
src += Glob('hal/*.c')

# 多个头文件路径
CPPPATH = [
    cwd,
    cwd + '/include',
    cwd + '/internal',
    cwd + '/port'
]

# 根据配置添加特定目录
if GetDepend('RT_USING_LWIP'):
    src += Glob('lwip/*.c')
    CPPPATH += [cwd + '/lwip']

group = DefineGroup('Network', src, depend = ['RT_USING_NETWORK'], 
                    CPPPATH = CPPPATH)

Return('group')
```

### 4. 递归子目录模式

自动处理所有子目录的SConscript：

```python
import os
from building import *

objs = []
cwd = GetCurrentDir()

# 获取所有子目录
list = os.listdir(cwd)

# 需要跳过的目录
skip_dirs = ['test', 'doc', 'examples', '.git']

for d in list:
    path = os.path.join(cwd, d)
    # 检查是否是目录且包含SConscript
    if os.path.isdir(path) and d not in skip_dirs:
        if os.path.isfile(os.path.join(path, 'SConscript')):
            objs = objs + SConscript(os.path.join(d, 'SConscript'))

Return('objs')
```

### 5. 库文件链接模式

链接预编译的库文件：

```python
from building import *
import os

cwd = GetCurrentDir()

# 只包含必要的接口文件
src = ['lib_interface.c']

CPPPATH = [cwd + '/include']

# 库文件配置
LIBS = []
LIBPATH = []

# 根据架构选择库文件
import rtconfig
if rtconfig.ARCH == 'arm':
    if rtconfig.CPU == 'cortex-m4':
        LIBS += ['mylib_cm4']
        LIBPATH += [cwd + '/lib/cortex-m4']
    elif rtconfig.CPU == 'cortex-m3':
        LIBS += ['mylib_cm3']
        LIBPATH += [cwd + '/lib/cortex-m3']

group = DefineGroup('MyLib', src, depend = ['RT_USING_MYLIB'], 
                    CPPPATH = CPPPATH, LIBS = LIBS, LIBPATH = LIBPATH)

Return('group')
```

## 高级技巧

### 1. 本地编译选项

为特定模块设置独立的编译选项：

```python
from building import *

src = Glob('*.c')
CPPPATH = [GetCurrentDir()]

# 全局编译选项（影响依赖此组件的其他组件）
CPPDEFINES = ['GLOBAL_DEFINE']

# 本地编译选项（仅影响当前组件）
LOCAL_CFLAGS = ''
LOCAL_CPPDEFINES = ['LOCAL_DEFINE']
LOCAL_CPPPATH = ['./private']

# 根据编译器设置优化选项
import rtconfig
if rtconfig.PLATFORM == 'gcc':
    LOCAL_CFLAGS += ' -O3 -funroll-loops'
elif rtconfig.PLATFORM == 'armcc':
    LOCAL_CFLAGS += ' -O3 --loop_optimization_level=2'

group = DefineGroup('HighPerf', src, depend = ['RT_USING_HIGHPERF'],
    CPPPATH = CPPPATH,
    CPPDEFINES = CPPDEFINES,
    LOCAL_CFLAGS = LOCAL_CFLAGS,
    LOCAL_CPPDEFINES = LOCAL_CPPDEFINES,
    LOCAL_CPPPATH = LOCAL_CPPPATH
)

Return('group')
```

### 2. 动态源文件生成

在构建时生成源文件：

```python
from building import *
import time

def generate_version_file():
    """生成版本信息文件"""
    version_c = '''
/* Auto-generated file, do not edit! */
#include "version.h"

const char *build_time = "%s";
const char *version = "%s";
''' % (time.strftime('%Y-%m-%d %H:%M:%S'), '1.0.0')
    
    with open('version_gen.c', 'w') as f:
        f.write(version_c)

# 生成文件
generate_version_file()

src = ['main.c', 'version_gen.c']
CPPPATH = [GetCurrentDir()]

group = DefineGroup('App', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
```

### 3. 复杂依赖处理

处理复杂的依赖关系：

```python
from building import *

src = []
CPPPATH = [GetCurrentDir()]
CPPDEFINES = []

# 基础功能
if GetDepend('RT_USING_DEVICE'):
    src += ['device_core.c']
    
    # 串口驱动（依赖设备框架）
    if GetDepend('RT_USING_SERIAL'):
        src += ['serial.c']
        
        # 串口DMA（依赖串口驱动）
        if GetDepend('RT_SERIAL_USING_DMA'):
            src += ['serial_dma.c']
            CPPDEFINES += ['SERIAL_USING_DMA']
    
    # SPI驱动（依赖设备框架）
    if GetDepend('RT_USING_SPI'):
        src += ['spi.c']
        
        # SPI DMA（依赖SPI驱动）
        if GetDepend('RT_SPI_USING_DMA'):
            src += ['spi_dma.c']

# 错误检查
if GetDepend('RT_SERIAL_USING_DMA') and not GetDepend('RT_USING_SERIAL'):
    print('Error: RT_SERIAL_USING_DMA requires RT_USING_SERIAL!')
    exit(1)

group = DefineGroup('Drivers', src, depend = ['RT_USING_DEVICE'], 
                    CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

Return('group')
```

### 4. 平台特定实现

根据不同平台包含不同实现：

```python
from building import *
import rtconfig

cwd = GetCurrentDir()
src = ['common.c']
CPPPATH = [cwd, cwd + '/include']

# 架构相关目录映射
arch_map = {
    'arm': {
        'cortex-m3': 'arm/cortex-m3',
        'cortex-m4': 'arm/cortex-m4',
        'cortex-m7': 'arm/cortex-m7',
        'cortex-a': 'arm/cortex-a'
    },
    'risc-v': {
        'rv32': 'riscv/rv32',
        'rv64': 'riscv/rv64'
    },
    'x86': {
        'i386': 'x86/i386',
        'x86_64': 'x86/x86_64'
    }
}

# 根据架构和CPU选择实现
if hasattr(rtconfig, 'ARCH') and hasattr(rtconfig, 'CPU'):
    arch = rtconfig.ARCH
    cpu = rtconfig.CPU
    
    if arch in arch_map and cpu in arch_map[arch]:
        port_dir = arch_map[arch][cpu]
        port_src = Glob(port_dir + '/*.c')
        port_src += Glob(port_dir + '/*.S')
        src += port_src
        CPPPATH += [cwd + '/' + port_dir]
    else:
        print('Warning: No port for %s - %s' % (arch, cpu))

group = DefineGroup('MyDriver', src, depend = ['RT_USING_MYDRIVER'], 
                    CPPPATH = CPPPATH)

Return('group')
```

### 5. 第三方库集成

集成第三方库的模板：

```python
from building import *
import os

cwd = GetCurrentDir()

# 第三方库路径
lib_path = cwd + '/3rdparty/libfoo'

# 检查库是否存在
if not os.path.exists(lib_path):
    print('Error: libfoo not found at', lib_path)
    print('Please run: git submodule update --init')
    Return('group')

# 库源文件
src = Glob(lib_path + '/src/*.c')

# 移除不需要的文件
SrcRemove(src, [
    lib_path + '/src/test.c',
    lib_path + '/src/example.c'
])

# 头文件路径
CPPPATH = [
    lib_path + '/include',
    cwd + '/port'  # 移植层头文件
]

# 添加移植层
src += Glob('port/*.c')

# 配置宏定义
CPPDEFINES = ['LIBFOO_RTOS_RTTHREAD']

# 根据配置启用功能
if GetDepend('LIBFOO_ENABLE_FLOAT'):
    CPPDEFINES += ['LIBFOO_USE_FLOAT']

if GetDepend('LIBFOO_ENABLE_STDIO'):
    CPPDEFINES += ['LIBFOO_USE_STDIO']

group = DefineGroup('libfoo', src, depend = ['RT_USING_LIBFOO'], 
                    CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

Return('group')
```

### 6. 条件导出符号

根据配置导出不同的API：

```python
from building import *

src = ['core.c']
CPPPATH = [GetCurrentDir()]

# API版本控制
if GetDepend('RT_USING_MODULE_API_V2'):
    src += ['api_v2.c']
    CPPDEFINES = ['MODULE_API_VERSION=2']
else:
    src += ['api_v1.c']
    CPPDEFINES = ['MODULE_API_VERSION=1']

# 根据配置级别导出不同功能
if GetDepend('MODULE_EXPERT_MODE'):
    src += ['expert_api.c']
    CPPDEFINES += ['EXPORT_EXPERT_API']

group = DefineGroup('Module', src, depend = ['RT_USING_MODULE'], 
                    CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

Return('group')
```

## 最佳实践

### 1. 文件组织原则

```
component/
├── SConscript          # 主构建脚本
├── Kconfig             # 配置选项
├── README.md           # 组件说明
├── include/            # 公开头文件
│   └── component.h
├── src/                # 源文件
│   ├── core.c
│   └── utils.c
├── port/               # 平台相关代码
│   ├── cortex-m/
│   └── risc-v/
└── examples/           # 示例代码
    └── example.c
```

### 2. 依赖管理最佳实践

```python
from building import *

# 1. 明确声明依赖
REQUIRED_DEPS = ['RT_USING_DEVICE', 'RT_USING_HEAP']

# 2. 检查必要依赖
for dep in REQUIRED_DEPS:
    if not GetDepend(dep):
        print('Error: %s requires %s' % ('MyComponent', dep))
        Return('group')

# 3. 可选依赖
src = ['core.c']

# 可选功能
OPTIONAL_FEATURES = {
    'RT_MYCOMPONENT_USING_DMA': 'dma.c',
    'RT_MYCOMPONENT_USING_INTERRUPT': 'interrupt.c',
    'RT_MYCOMPONENT_USING_STATS': 'statistics.c'
}

for macro, file in OPTIONAL_FEATURES.items():
    if GetDepend(macro):
        src += [file]

group = DefineGroup('MyComponent', src, depend = ['RT_USING_MYCOMPONENT'])
Return('group')
```

### 3. 错误处理

```python
from building import *
import os

# 检查关键文件
critical_files = ['config.h', 'version.h']
for f in critical_files:
    if not os.path.exists(f):
        print('Error: Missing required file:', f)
        # 返回空组，不中断整体构建
        group = DefineGroup('MyComponent', [], depend = [''])
        Return('group')

# 检查工具链
import rtconfig
supported_toolchains = ['gcc', 'armcc', 'iar']
if rtconfig.PLATFORM not in supported_toolchains:
    print('Warning: Toolchain %s not tested' % rtconfig.PLATFORM)

# 正常构建流程
src = Glob('*.c')
group = DefineGroup('MyComponent', src, depend = ['RT_USING_MYCOMPONENT'])
Return('group')
```

### 4. 性能优化

```python
from building import *
import os

# 1. 缓存文件列表（避免重复扫描）
_file_cache = {}

def cached_glob(pattern):
    if pattern not in _file_cache:
        _file_cache[pattern] = Glob(pattern)
    return _file_cache[pattern]

# 2. 延迟加载（仅在需要时扫描）
src = []
if GetDepend('RT_USING_MYCOMPONENT'):
    src = cached_glob('*.c')
    
    if GetDepend('RT_MYCOMPONENT_USING_EXTRA'):
        src += cached_glob('extra/*.c')

# 3. 避免深度递归（使用显式路径）
# 不好的做法
# src = Glob('**/*.c')  # 递归所有子目录

# 好的做法
src = Glob('*.c')
src += Glob('core/*.c')
src += Glob('hal/*.c')

group = DefineGroup('MyComponent', src, depend = ['RT_USING_MYCOMPONENT'])
Return('group')
```

### 5. 文档化

```python
"""
SConscript for MyComponent

This component provides [功能描述]

Configuration:
    RT_USING_MYCOMPONENT - Enable this component
    RT_MYCOMPONENT_USING_DMA - Enable DMA support
    RT_MYCOMPONENT_BUFFER_SIZE - Buffer size (default: 256)

Dependencies:
    - RT_USING_DEVICE (required)
    - RT_USING_DMA (optional, for DMA support)
"""

from building import *

# ... 构建脚本内容 ...
```

## 示例集合

### 示例1：设备驱动SConscript

```python
from building import *

cwd = GetCurrentDir()

# 驱动源文件
src = []
CPPPATH = [cwd + '/../inc']

# I2C驱动
if GetDepend('RT_USING_I2C'):
    src += ['drv_i2c.c']

# SPI驱动
if GetDepend('RT_USING_SPI'):
    src += ['drv_spi.c']
    
    # QSPI支持
    if GetDepend('RT_USING_QSPI'):
        src += ['drv_qspi.c']

# USB驱动
if GetDepend('RT_USING_USB'):
    src += ['drv_usb.c']
    if GetDepend('RT_USING_USB_HOST'):
        src += ['drv_usbh.c']
    if GetDepend('RT_USING_USB_DEVICE'):
        src += ['drv_usbd.c']

# SDIO驱动
if GetDepend('RT_USING_SDIO'):
    src += ['drv_sdio.c']

group = DefineGroup('Drivers', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
```

### 示例2：网络组件SConscript

```python
from building import *

cwd = GetCurrentDir()
src = []
CPPPATH = [cwd]

# 网络接口层
if GetDepend('RT_USING_NETDEV'):
    src += Glob('netdev/*.c')
    CPPPATH += [cwd + '/netdev']

# SAL套接字抽象层
if GetDepend('RT_USING_SAL'):
    src += Glob('sal/src/*.c')
    src += Glob('sal/socket/*.c')
    CPPPATH += [cwd + '/sal/include']
    
    # AT指令支持
    if GetDepend('SAL_USING_AT'):
        src += Glob('sal/impl/af_inet_at.c')
    
    # LwIP支持
    if GetDepend('SAL_USING_LWIP'):
        src += Glob('sal/impl/af_inet_lwip.c')

# AT指令框架
if GetDepend('RT_USING_AT'):
    src += Glob('at/src/*.c')
    CPPPATH += [cwd + '/at/include']
    
    # AT Socket
    if GetDepend('AT_USING_SOCKET'):
        src += Glob('at/at_socket/*.c')

group = DefineGroup('Network', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
```

### 示例3：文件系统SConscript

```python
from building import *

cwd = GetCurrentDir()
src = []
CPPPATH = [cwd + '/include']

# DFS框架
if GetDepend('RT_USING_DFS'):
    src += Glob('src/*.c')
    
    # ELM FatFS
    if GetDepend('RT_USING_DFS_ELMFAT'):
        src += Glob('filesystems/elmfat/*.c')
        # FatFS版本选择
        if GetDepend('RT_DFS_ELM_USE_LFN'):
            src += ['filesystems/elmfat/ffunicode.c']
    
    # ROMFS
    if GetDepend('RT_USING_DFS_ROMFS'):
        src += ['filesystems/romfs/dfs_romfs.c']
    
    # DevFS
    if GetDepend('RT_USING_DFS_DEVFS'):
        src += ['filesystems/devfs/devfs.c']
    
    # NFS
    if GetDepend('RT_USING_DFS_NFS'):
        src += Glob('filesystems/nfs/*.c')
        CPPPATH += [cwd + '/filesystems/nfs']

group = DefineGroup('Filesystem', src, depend = ['RT_USING_DFS'], 
                    CPPPATH = CPPPATH)

Return('group')
```

### 示例4：使用package.json的SConscript

```python
from building import *
import os
import json

cwd = GetCurrentDir()

# 尝试使用package.json
package_file = os.path.join(cwd, 'package.json')
if os.path.exists(package_file):
    # 使用自动构建
    objs = BuildPackage(package_file)
else:
    # 手动构建
    src = Glob('src/*.c')
    CPPPATH = [cwd + '/include']
    
    # 读取配置
    config_file = os.path.join(cwd, 'config.json')
    if os.path.exists(config_file):
        with open(config_file, 'r') as f:
            config = json.load(f)
            
        # 根据配置添加源文件
        for feature in config.get('features', []):
            if GetDepend('RT_USING_' + feature.upper()):
                src += Glob('src/%s/*.c' % feature)
    
    objs = DefineGroup('MyPackage', src, depend = ['RT_USING_MYPACKAGE'], 
                       CPPPATH = CPPPATH)

Return('objs')
```

## 常见问题

### Q1: 如何调试SConscript？

```python
from building import *

# 1. 打印调试信息
print('Current directory:', GetCurrentDir())
print('GetDepend RT_USING_XXX:', GetDepend('RT_USING_XXX'))

# 2. 打印源文件列表
src = Glob('*.c')
print('Source files:', src)

# 3. 条件调试输出
if GetOption('verbose'):
    print('Detailed debug info...')

# 4. 检查环境变量
import os
print('RTT_ROOT:', os.getenv('RTT_ROOT'))
```

### Q2: 如何处理可选的依赖？

```python
from building import *

src = ['core.c']

# 可选依赖处理
optional_deps = {
    'RT_USING_SERIAL': ['serial.c', 'serial_ops.c'],
    'RT_USING_CAN': ['can.c', 'can_ops.c'],
    'RT_USING_I2C': ['i2c.c', 'i2c_ops.c']
}

for dep, files in optional_deps.items():
    if GetDepend(dep):
        src += files

# 检查组合依赖
if GetDepend('RT_USING_SERIAL') and GetDepend('RT_USING_DMA'):
    src += ['serial_dma.c']

group = DefineGroup('Drivers', src, depend = ['RT_USING_DEVICE'])
Return('group')
```

### Q3: 如何支持多个工具链？

```python
from building import *
import rtconfig

src = ['common.c']

# 工具链特定文件
toolchain_files = {
    'gcc': ['gcc_startup.S', 'gcc_specific.c'],
    'armcc': ['keil_startup.s', 'keil_specific.c'],
    'iccarm': ['iar_startup.s', 'iar_specific.c']
}

if rtconfig.PLATFORM in toolchain_files:
    src += toolchain_files[rtconfig.PLATFORM]
else:
    print('Warning: Unknown toolchain', rtconfig.PLATFORM)

# 工具链特定编译选项
LOCAL_CFLAGS = ''
if rtconfig.PLATFORM == 'gcc':
    LOCAL_CFLAGS = '-Wno-unused-function'
elif rtconfig.PLATFORM == 'armcc':
    LOCAL_CFLAGS = '--diag_suppress=177'

group = DefineGroup('MyComponent', src, depend = [''], 
                    LOCAL_CFLAGS = LOCAL_CFLAGS)
Return('group')
```

### Q4: 如何处理生成的代码？

```python
from building import *
import subprocess

def generate_code():
    """生成代码"""
    # 运行代码生成器
    cmd = ['python', 'codegen.py', '-o', 'generated.c']
    subprocess.check_call(cmd)

# 确保生成代码
if GetDepend('RT_USING_CODEGEN'):
    generate_code()
    src = ['generated.c']
else:
    src = ['default.c']

group = DefineGroup('Generated', src, depend = [''])
Return('group')
```

### Q5: 如何组织大型项目？

```python
# 主SConscript
from building import *

objs = []

# 子模块列表
modules = [
    'core',
    'drivers',
    'network',
    'filesystem',
    'gui'
]

# 根据配置包含模块
for module in modules:
    # 检查模块是否启用
    if GetDepend('RT_USING_' + module.upper()):
        # 构建子模块
        objs += SConscript(module + '/SConscript')

Return('objs')
```

## 总结

编写高质量的SConscript需要：

1. **清晰的结构**：合理组织源文件和目录
2. **正确的依赖**：准确声明和检查依赖关系
3. **平台兼容**：处理不同工具链和平台的差异
4. **性能考虑**：避免不必要的文件扫描
5. **错误处理**：优雅处理各种异常情况
6. **文档完善**：添加必要的注释和说明

通过遵循本指南的建议和最佳实践，可以编写出易维护、可扩展的构建脚本，为RT-Thread项目的构建提供坚实的基础。