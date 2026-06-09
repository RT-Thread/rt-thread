# RT-Thread AI Agent Rules / RT-Thread AI Agent 规则

## What this is / 这是什么

- Rules for AI agents working in this repository. / 约束在本仓库内工作的 AI Agent。
- Core principle: make only minimal, task-focused, verifiable changes. / 核心原则：只做最小化、面向任务、可验证的改动。

## Allowed / 可以做什么

- Read files directly related to the task. / 阅读与任务直接相关的文件。
- Make minimal required edits, and update directly related docs or tests when needed. / 仅做完成任务所需的最小改动，并在需要时同步更新直接相关的文档或测试。
- Use existing directories, scripts, and checks. / 复用现有目录、脚本和检查流程。

## Strictly forbidden / 严格禁止

- Unrelated refactors, bulk renames, repo-wide formatting, or unrelated file changes. / 与任务无关的重构、批量重命名、全仓格式化或其他无关改动。
- Generated artifacts, temporary files, logs, binaries, local environment files, or secrets. / 提交生成物、临时文件、日志、二进制文件、本地环境文件或任何密钥等敏感信息。
- Dependency churn, third-party/imported code changes, or weakened/removed tests unless the task explicitly requires them. / 除非任务明确要求，否则禁止随意变更依赖、修改第三方/导入代码，或弱化/删除测试。
- History rewrites or overwriting others' work. / 改写历史或覆盖他人工作成果。

## Placement / 放置规则

- Use existing directories such as `bsp/`, `components/`, `documentation/`, `examples/`, `include/`, `libcpu/`, `src/`, and `tools/`. / 使用现有目录，如 `bsp/`、`components/`、`documentation/`、`examples/`、`include/`、`libcpu/`、`src/`、`tools/`。
- Keep repository-entry files such as `AGENTS.md`, `README.md`, and `LICENSE` in the root; put general documentation in `documentation/`. / `AGENTS.md`、`README.md`、`LICENSE` 等仓库入口文件放在根目录；通用文档放在 `documentation/`。

## Precedence / 优先级

- If a more specific repository rule conflicts with this file, follow `.github/CONTRIBUTING.md`, `documentation/7.contribution/coding_style_cn.md`, and `documentation/7.contribution/coding_style_en.md`. / 如与更具体的仓库规则冲突，以 `.github/CONTRIBUTING.md`、`documentation/7.contribution/coding_style_cn.md`、`documentation/7.contribution/coding_style_en.md` 为准。
