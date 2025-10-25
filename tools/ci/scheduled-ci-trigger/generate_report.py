#!/usr/bin/env python3
import json
import os
from datetime import datetime, timedelta
from typing import List, Dict, Any

def load_monitoring_results() -> List[Dict[str, Any]]:
    """加载 monitoring_results.json"""
    if not os.path.exists("monitoring_results.json"):
        print("No monitoring results found")
        return []
    try:
        with open("monitoring_results.json", "r", encoding="utf-8") as f:
            return json.load(f)
    except (json.JSONDecodeError, OSError) as e:
        print(f"Error loading monitoring_results.json: {e}")
        return []

def get_beijing_time() -> datetime:
    return datetime.utcnow() + timedelta(hours=8)

def format_time(dt: datetime) -> str:
    return dt.strftime("%Y-%m-%d %H:%M")

def classify_error(step_name: str, job_name: str) -> str:
    """错误类型分类"""
    step_lower = step_name.lower()
    if any(x in step_lower for x in ["test", "suite", "pytest", "unittest"]):
        return "TEST_FAILURE"
    if "lint" in step_lower or "flake8" in step_lower:
        return "LINT_ERROR"
    if "build" in step_lower or "compile" in step_lower:
        return "BUILD_ERROR"
    if "deploy" in step_lower or "upload" in step_lower or "publish" in step_lower:
        return "DEPLOY_ERROR"
    if "check" in step_lower or "validate" in step_lower or "verify" in step_lower:
        return "VALIDATION_ERROR"
    if "generate" in step_lower or "render" in step_lower:
        return "GENERATION_ERROR"
    return "UNKNOWN"

def generate_report():
    """生成符合最新样式的故障聚合报告"""
    results = load_monitoring_results()
    if not results:
        return

    failed_workflows = [r for r in results if r.get('conclusion') == 'failure']
    if not failed_workflows:
        print("No failed workflows to report")
        return

    now = get_beijing_time()
    date_str = now.strftime("%Y%m%d")

    # 时间范围
    created_times = [
        datetime.fromisoformat(r["created_at"].replace("Z", "+00:00")) + timedelta(hours=8)
        for r in failed_workflows
    ]
    updated_times = [
        datetime.fromisoformat(r["updated_at"].replace("Z", "+00:00")) + timedelta(hours=8)
        for r in failed_workflows
    ]
    start_time = min(created_times)
    end_time = max(updated_times)

    total = len(results)
    failed_count = len(failed_workflows)
    success_rate = 0.0 if total == 0 else round((total - failed_count) / total * 100, 1)

    # === 第一行：用于 JS 提取标题（必须）===
    report = f"# {date_str}_ci_integration-failed-report\n\n"

    # === 第二行：用户看到的主标题（H1）===
    report += f"# 🚨 {date_str} GitHub Actions 故障聚合报告 | Incident Aggregate Report\n\n"

    # === 执行概览 ===
    report += f"## 执行概览 | Executive Summary\n"
    report += f"- **监控时间范围 | Monitoring Period**: {format_time(start_time)}–{format_time(end_time)} (UTC+8)\n"
    report += f"- **检测到失败运行 | Failed Runs Detected**: {failed_count}个\n"
    report += f"- **成功率 | Success Rate**: {success_rate}% \n\n"

    # === 故障详情 ===
    report += f"## 🔍 故障详情 | Failure Details\n\n"

    for wf in failed_workflows:
        run_id = wf.get("run_id", "N/A")
        name = wf["name"]
        html_url = wf.get("html_url", "#")
        details = wf.get("failure_details", [])

        report += f"**📌 Run-{run_id}** | [{name}]({html_url})\n"

        if not details:
            report += "└─ 无失败作业详情 | No details of failed jobs\n\n"
            continue

        failed_jobs = [j for j in details if j.get("steps")]
        for i, job in enumerate(failed_jobs):
            job_name = job["name"]
            steps = job["steps"]
            job_prefix = "└─" if i == len(failed_jobs) - 1 else "├─"
            report += f"{job_prefix} **失败作业 | Failed Job**: {job_name}\n"

            for j, step in enumerate(steps):
                step_name = step["name"]
                step_num = step["number"]
                error_type = classify_error(step_name, job_name)
                step_prefix = "   └─" if j == len(steps) - 1 else "   ├─"
                report += f"{step_prefix} **失败步骤 | Failed Step**: {step_name} (Step {step_num})\n"
                indent = "      " if j == len(steps) - 1 else "   │   "
                report += f"{indent}**错误类型 | Error Type**: `{error_type}`\n"
        report += "\n"

    # === Team Collaboration & Support ===
    report += f"## 👥 团队协作与支持 | Team Collaboration & Support\n\n"
    report += f"请求维护支持：本报告需要RT-Thread官方团队的专业经验进行审核与指导。 \n"
    report += f"Call for Maintenance Support: This report requires the expertise of the RT-Thread official team for review and guidance.\n\n"
    report += f"提审负责人：@Rbb666 @kurisaW\n"
    report += f"Requested Reviewers from RT-Thread: @Rbb666 @kurisaW\n\n"
    report += f"烦请尽快关注此事，万分感谢。  \n"
    report += f"Your prompt attention to this matter is greatly appreciated.\n"

    # 保存
    try:
        with open("failure_details.md", "w", encoding="utf-8") as f:
            f.write(report.rstrip() + "\n")
        print("Report generated: failure_details.md")
        print(f"Report size: {os.path.getsize('failure_details.md')} bytes")
    except Exception as e:
        print(f"Error writing report: {e}")

if __name__ == "__main__":
    generate_report()