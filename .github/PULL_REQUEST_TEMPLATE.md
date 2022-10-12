## 拉取/合并请求描述：(PR description)

[
这段方括号里的内容是您**必须填写并替换掉**的，否则PR不可能被合并。**方括号外面的内容不需要修改，但请仔细阅读。**
The content in this square bracket must be filled in and replaced, otherwise, PR can not be merged. The contents outside square brackets need not be changed, but please read them carefully.

请在这里填写您的PR描述，可以包括以下之一的内容：为什么提交这份PR；解决的问题是什么，你的解决方案是什么；
Please fill in your PR description here, which can include one of the following items: why to submit this PR; what is the problem solved and what is your solution;

并确认并列出已经在什么情况或板卡上进行了测试。
And confirm in which case or board has been tested.
]

以下的内容不应该在提交PR时的message修改，修改下述message，PR会被直接关闭。请在提交PR后，浏览器查看PR并对以下检查项逐项check，没问题后逐条在页面上打钩。
The following content must not be changed in the submitted PR message. Otherwise, the PR will be closed immediately. After submitted PR, please use a web browser to visit PR, and check items one by one, and ticked them if no problem.

### 当前拉取/合并请求的状态 Intent for your PR

必须选择一项 Choose one (Mandatory):

- [ ] 本拉取/合并请求是一个草稿版本 This PR is for a code-review and is intended to get feedback
- [ ] 本拉取/合并请求是一个成熟版本 This PR is mature, and ready to be integrated into the repo

### 代码质量 Code Quality：

我在这个拉取/合并请求中已经考虑了 As part of this pull request, I've considered the following:

- [ ] 已经仔细查看过代码改动的对比 Already check the difference between PR and old code
- [ ] 代码风格正确，包括缩进空格，命名及其他风格 Style guide is adhered to, including spacing, naming and other styles
- [ ] 没有垃圾代码，代码尽量精简，不包含`#if 0`代码，不包含已经被注释了的代码 All redundant code is removed and cleaned up
- [ ] 所有变更均有原因及合理的，并且不会影响到其他软件组件代码或BSP All modifications are justified and not affect other components or BSP
- [ ] 对难懂代码均提供对应的注释 I've commented appropriately where code is tricky
- [ ] 本拉取/合并请求代码是高质量的 Code in this PR is of high quality
- [ ] 本拉取/合并使用[formatting](https://github.com/mysterywolf/formatting)等源码格式化工具确保格式符合[RT-Thread代码规范](../documentation/contribution_guide/coding_style_cn.md) This PR complies with [RT-Thread code specification](../documentation/contribution_guide/coding_style_en.txt) 
