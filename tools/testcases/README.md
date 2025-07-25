# 测试用例目录

本目录包含 RT-Thread 工具的测试脚本。

## 测试脚本

### test_preprocessor.py
SCons PreProcessor 补丁功能测试脚本。测试与 building.py 的集成，验证预处理器补丁是否正常工作。

### test_refactor.py
验证目标模块重构是否成功的测试脚本。测试内容包括：
- 目标模块导入
- Building.py 导入
- 目标函数调用

### mock_rtconfig.py
用于测试的模拟 rtconfig 模块。在实际 rtconfig 不可用的测试场景中提供模拟的 rtconfig 模块。

## 使用方法

要运行测试，请导航到此目录并执行：

```bash
python test_preprocessor.py
python test_refactor.py
```

## 说明

- 这些测试脚本用于验证 RT-Thread 工具的功能
- 可以独立运行或作为测试套件的一部分
- mock_rtconfig.py 文件被其他测试脚本用来模拟 rtconfig 模块 