# Lua on RT-Thread

## 简介
RT-Thread中的Lua修改自[eLua](http://www.eluaproject.net/)的Lua-5.1.4版本。
采用gcc工具链时，Lua依赖于newlib库，采用keil时，Lua依赖于arm的标准c库。
启动lua的RAM占用情况
    - 标准的lua        17.1904296875 KB
    - 优化的lua        5.01953125 KB
    注：数据来自print(collectgarbage('count'))的输出
优化是指采用一个lua patch --- [Lua Tiny RAM](http://www.eluaproject.net/doc/v0.8/en_arch_ltr.html)

## 使用
在RT-Thread的finsh中，调用lua()获得一个lua解释器。
在lua解释器中
    - 可以调用lua标准库中的函数，如：print('hello, lua on rt-thread')
    - 可以执行脚本文件，如：dofile('/hello.lua')
    - 可以定义新的函数，如：function sinc(x) return math.sin(x)/x end
    - etc.

## 配置
    1.通过在rtconfig.h中定义RT_USING_LUA加入lua组件
    2.可以定义RT_LUA_OPTRAM减少RAM占用
    3.可以定义RT_LUS_USE_EXLIBS而添加外部库，如arduino的常用函数封装为一个arduino库
    3.更多的配置项可以在luaconf.h中找到

## 开发相关
    - lua组件依赖于libc，需要在rtconfig.h中定义RT_USING_LIBC
    - 开启编译器对C99的支持，如MDK中，在C/C++选项的Misc Controls输入框中添加--c99
    - 使用gcc时，需要在链接脚本中定义_stext和_etext，.ordata*放在两者之间。用于判断数据是read-only和writable  
      使用keil时，需要在分散加载文件中把rodata放在ER_IROM1区
    - 添加新的模块，参见exlibs/lexamplelib.c
    
## 目录说明
    - lua：从eLua获得Lua-5.1.4版本代码
    - exlibs：external libraries，外部库代码，如example库
    - applications：Lua应用代码，如finsh中lua()
    - test：测试代码
