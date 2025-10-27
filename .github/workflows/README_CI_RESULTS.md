# CI Results Comment Workflow

## Overview / 概述

This feature automatically posts CI test results as comments on Pull Requests, making it easier for contributors and reviewers to see the status of all CI checks at a glance.

此功能自动将 CI 测试结果作为评论发布到 Pull Request 中，使贡献者和审阅者更容易一目了然地看到所有 CI 检查的状态。

## Implementation / 实现方式

The feature uses **two complementary approaches** to ensure CI results are always visible:
该功能使用**两种互补方法**来确保 CI 结果始终可见：

### 1. Direct Workflow Integration (Immediate) / 直接工作流集成（立即生效）

Each main CI workflow includes a `post-ci-status` job that:
每个主要 CI 工作流都包含一个 `post-ci-status` 作业，它：

- ✅ Works immediately on PR branches (no merge required) / 立即在 PR 分支上生效（无需合并）
- 📝 Updates a single comment with workflow status / 使用工作流状态更新单个评论
- 🔄 Runs after each workflow completes / 在每个工作流完成后运行

**Modified Workflows:**
- `bsp_buildings.yml`
- `static_code_analysis.yml`
- `format_check.yml`
- `utest_auto_run.yml`

### 2. Workflow Run Trigger (After Merge) / 工作流运行触发器（合并后）

The `ci_results_comment.yml` workflow:
`ci_results_comment.yml` 工作流：

- ⏰ Triggers when CI workflows complete / 在 CI 工作流完成时触发
- 📊 Provides comprehensive summary of all workflows / 提供所有工作流的全面摘要
- 🔍 Shows detailed job-level information / 显示详细的作业级信息
- ⚠️ **Only works after merged to master** / **仅在合并到 master 后才有效**

## Features / 功能特性

1. **Automatic Updates / 自动更新**: The comment is automatically created when CI workflows complete and updated as new workflows finish.
   / 当 CI 工作流完成时自动创建评论，并在新工作流完成时更新。

2. **Comprehensive Summary / 全面总结**: Shows the status of all major CI workflows including:
   / 显示所有主要 CI 工作流的状态，包括：
   - RT-Thread BSP Static Build Check / BSP 静态构建检查
   - Static code analysis / 静态代码分析
   - Check File Format and License / 文件格式和许可证检查
   - utest_auto_run / 单元测试自动运行

3. **Status Indicators / 状态指示器**:
   - ✅ Success / 成功
   - ❌ Failure / 失败
   - 🟠 Queued / 排队中
   - 🟡 In Progress / 进行中
   - ⏭️ Skipped / 已跳过

4. **Detailed Information / 详细信息**: Expandable sections show individual job results within each workflow.
   / 可展开的部分显示每个工作流中的各个作业结果。

## How It Works / 工作原理

1. The workflow is triggered when any of the monitored CI workflows complete.
   / 当任何受监控的 CI 工作流完成时，将触发此工作流。

2. It collects the status of all workflows and jobs for the associated Pull Request.
   / 它收集关联 Pull Request 的所有工作流和作业的状态。

3. A formatted comment is posted (or updated if one already exists) with the current CI status.
   / 发布（或更新已存在的）格式化评论，显示当前 CI 状态。

## Comment Format / 评论格式

The comment includes:
评论包括：

- **Overall Summary / 总体摘要**: Quick statistics showing count of passed, failed, queued, in-progress, and skipped workflows.
  / 快速统计数据，显示通过、失败、排队、进行中和跳过的工作流数量。

- **Detailed Results / 详细结果**: Collapsible sections for each workflow with links to individual jobs.
  / 每个工作流的可折叠部分，包含指向各个作业的链接。

## Benefits / 优势

1. **Visibility / 可见性**: Contributors can immediately see which CI checks have passed or failed without navigating to the Actions tab.
   / 贡献者无需导航到 Actions 选项卡即可立即查看哪些 CI 检查通过或失败。

2. **Efficiency / 效率**: Reviewers can quickly assess the CI status before reviewing the code.
   / 审阅者可以在审查代码之前快速评估 CI 状态。

3. **Transparency / 透明度**: All stakeholders have a clear view of the PR's CI status.
   / 所有利益相关者都可以清楚地了解 PR 的 CI 状态。

## Permissions Required / 所需权限

The workflow requires the following permissions:
工作流需要以下权限：

- `pull-requests: write` - To create and update comments / 创建和更新评论
- `issues: write` - To post comments on PR issues / 在 PR 问题上发布评论
- `actions: read` - To read workflow run status / 读取工作流运行状态
- `checks: read` - To read check run status / 读取检查运行状态

## Configuration / 配置

The workflow monitors the following workflows by default:
工作流默认监控以下工作流：

```yaml
workflows:
  - "RT-Thread BSP Static Build Check"
  - "Static code analysis"
  - "Check File Format and License"
  - "utest_auto_run"
```

To add more workflows to monitor, edit the `.github/workflows/ci_results_comment.yml` file and add workflow names to the `workflows` list.

要监控更多工作流，请编辑 `.github/workflows/ci_results_comment.yml` 文件并将工作流名称添加到 `workflows` 列表中。

## Troubleshooting / 故障排除

### Comment not appearing / 评论未出现

1. Ensure the workflow has the required permissions / 确保工作流具有所需权限
2. Check that the PR is from a branch in the repository (not a fork) / 检查 PR 是否来自存储库中的分支（而非分支）
3. Verify the workflow is enabled in the repository settings / 验证工作流在存储库设置中已启用

### Comment not updating / 评论未更新

1. The comment updates when a monitored workflow completes / 当受监控的工作流完成时，评论会更新
2. Check the Actions tab to see if the workflow is running / 检查 Actions 选项卡以查看工作流是否正在运行
3. Look for errors in the workflow logs / 在工作流日志中查找错误

## Contributing / 贡献

Contributions to improve this workflow are welcome! Please follow the standard contribution process outlined in the CONTRIBUTING.md file.

欢迎改进此工作流的贡献！请遵循 CONTRIBUTING.md 文件中概述的标准贡献流程。
