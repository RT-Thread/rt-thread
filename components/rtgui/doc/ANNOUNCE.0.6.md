RTGUI 0.6版发布纪要

# 为什么是 0.6？

RTGUI 是作为 RT-Thread 的一个组件存在的。这次新发布的版本是在原 RTGUI 基础上重
构而来的。原 RTGUI 没有独立的版本号。暂设其为 0.5。所以本版本号取 0.6，为在原有
基础上改进之意。以后我们会每个月发布一个新版本。下一个版本号会是 0.6.1。

# 运行环境

理论上原来可以运行 RTGUI 的设备上都可以运行新的 RTGUI。本版本自带一个 Windows
模拟器，用来方便地评估运行效果。默认的运行环境是 realtouch。RT-Thread 中的模拟
器也是可以运作的。

# 新版本有什么特点？

0. 新版本的 GUI 摒弃了原有的 workbench/view/window 的工作方式。转换成全面向
   window的工作方式。原有的 workbench/view 可以用 notebook 来实现。
0. 用 `rtgui_app` 对线程进行了抽象。
0. 事件驱动更彻底：
    0. 将事件处理机制集成进 `rtgui_object`。
    0. 添加了`RTGUI_EVENT_SHOW` 和 `RTGUI_EVENT_HIDE` 来通知控件将要被显示/隐藏。
    0. 底层代码中对事件的应用更加彻底。
0. 重构了自动布局方式。使得控件的摆放更加方便。

# 增强

- 添加了 TJPGD 引擎。使得小内存系统解码 jpeg 图片成为可能。(onelife)
- 添加了对单色屏的支持(onelife)
- bmp 图像引擎的重构(onelife)
- bmp 图像的旋转/缩放，以及功能性增强(amsl)
- 增加屏幕快照功能(amsl)
- PNG 引擎增加 Alpha 通道支持(amsl)
- 新增 edit 多行文本编辑控件。(amsl)
- 增加了 Model/View 的编程框架。(Grissiom)
- 添加了缩减字库的特性，开启后可以自动添加用到的汉字，不用的汉字字形不会加入到
  字库当中。使得 GUI 能够在小 ROM 系统上得以应用。(Grissiom)
- 新增 digtube 七段码显示控件(prife)
- demo/benchmark 新增了 FPS 输出(amsl)
- 新增 box/panel/groupbox，支持自动布局(Bernard)

# API 变化

除了 workbench/view 的消失以外，还有如下的 API 变化：

- c05a301, 68e3e30: `rtgui_{menu,win}_hiden` 被重命名为 `rtgui_{menu,win}_hide`。
- 05e4894: 将 `struct rtgui_widget` 中的 `mini_{height,width}` 重命名为 `min_{height,width}`。
- 等等……

今后很长时间内，新版本的 RTGUI 会与此版本的 API 尽量只增不减，保持兼容。

# Bug fixes

- 00a6690: 解决了 `rtgui_notebook_set_current_by_index` 中重绘标签页的 bug。感
  谢 prife 提交 bug 信息和补丁。
- 6850ff2: 解决了 `last_mevent_widget` 引起的事件传送失败。感谢 heryon 提交bug
  报告。
- 9143e11: 解决了 jpeg 引擎中的内存泄漏。感谢 Young 提供 bug 信息。
- fbd567c: 解决了 `rtgui_textbox_set_line_length` 的 bug。
- 9b67b66: 修复了窗口标题栏渐变效果的绘制。
- fc3abbf: 修复了 `rtgui_label_set_text`。感谢 tanghong668 提供 bug 信息。
- d41586c: 修复了窗口激活时重复刷新的问题。感谢 onelife 提供 bug 信息。
- ab08de6: 修复了字库缓存的 bug。感谢 rtt\_fans 提供 bug 信息。
- 等等……

除了上面提到的，luoyuncong2012, lgnq, shaolin 也有贡献。上面的列表也必然是不完
整的。感谢编写了第一版 RTGUI 的 Bernard 和其他大侠们，没有他们的辛勤劳动，也不
会有今天的版本。感谢各位使用和支持RTGUI的开发人员，是你们 RTGUI 体现了 RTGUI 的
价值。
