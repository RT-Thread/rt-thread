#!/usr/bin/env python3
import os
import json
import requests
import time
import sys
from datetime import datetime, timezone

def save_monitoring_results(results):
    # Keep the last complete snapshot if the process stops during a write.
    with open("monitoring_results.json.tmp", "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2)
    os.replace("monitoring_results.json.tmp", "monitoring_results.json")

def monitor_workflows(github_token, repo, workflow_names, start_time):
    """监控工作流运行"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    # Include unfinished workflows so a partial snapshot cannot report success.
    monitoring_results = [{
        "name": name,
        "status": "not_monitored",
        "conclusion": "error",
        "error": "Monitoring did not complete for this workflow"
    } for name in workflow_names]
    save_monitoring_results(monitoring_results)
    
    for index, workflow_name in enumerate(workflow_names):
        print(f"\n=== Monitoring {workflow_name} ===")
        
        try:
            workflow_id = get_workflow_id(github_token, repo, workflow_name)
            if not workflow_id:
                monitoring_results[index] = {
                    "name": workflow_name,
                    "status": "error",
                    "conclusion": "error", 
                    "error": "Workflow not found"
                }
                continue
            
            # 查找开始时间后的运行
            runs = get_recent_runs(github_token, repo, workflow_id, start_time)
            
            if not runs:
                print(f"No runs found for {workflow_name} after {start_time}")
                monitoring_results[index] = {
                    "name": workflow_name,
                    "status": "not_found",
                    "conclusion": "not_found",
                    "error": f"No dispatched runs found after {start_time}"
                }
            else:
                # 监控找到的运行
                run_to_monitor = min(runs, key=lambda run: run["created_at"])
                print(f"Monitoring run: {run_to_monitor['id']}")
                result = monitor_single_run(github_token, repo, run_to_monitor["id"], workflow_name)
                monitoring_results[index] = result
                
        except Exception as e:
            print(f"Error monitoring {workflow_name}: {str(e)}")
            monitoring_results[index] = {
                "name": workflow_name,
                "status": "error",
                "conclusion": "error",
                "error": str(e)
            }
        finally:
            save_monitoring_results(monitoring_results)
    
    return monitoring_results

def get_all_runs(github_token, repo, workflow_id, per_page=10):
    """获取所有运行"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    url = f"https://api.github.com/repos/{repo}/actions/workflows/{workflow_id}/runs"
    params = {
        "per_page": per_page,
        "event": "workflow_dispatch",
        "branch": "master",
    }
    
    response = requests.get(url, headers=headers, params=params, timeout=30)
    if response.status_code == 200:
        return response.json()["workflow_runs"]
    return []

def get_recent_runs(github_token, repo, workflow_id, start_time):
    """获取开始时间后的运行"""
    all_runs = get_all_runs(github_token, repo, workflow_id, 10)
    start_time_dt = datetime.fromisoformat(start_time.replace('Z', '+00:00'))
    
    recent_runs = []
    for run in all_runs:
        run_time = datetime.fromisoformat(run["created_at"].replace('Z', '+00:00'))
        if run_time >= start_time_dt:
            recent_runs.append(run)
    
    return recent_runs

def monitor_single_run(github_token, repo, run_id, workflow_name):
    """监控单个运行"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    max_wait_time = 7200  # Allow two hours for queued BSP builds.
    check_interval = 30
    start_time = time.monotonic()
    
    print(f"Monitoring {workflow_name} (run {run_id})")
    
    while time.monotonic() - start_time < max_wait_time:
        url = f"https://api.github.com/repos/{repo}/actions/runs/{run_id}"
        response = requests.get(url, headers=headers, timeout=30)
        
        if response.status_code != 200:
            print(f"Error getting run status: {response.status_code}")
            time.sleep(check_interval)
            continue
        
        run_data = response.json()
        status = run_data["status"]
        conclusion = run_data.get("conclusion")
        
        print(f"  {workflow_name}: status={status}, conclusion={conclusion}")
        
        if status == "completed":
            result = {
                "name": workflow_name,
                "run_id": run_id,
                "status": status,
                "conclusion": conclusion,
                "html_url": run_data["html_url"],
                "created_at": run_data["created_at"],
                "updated_at": run_data["updated_at"]
            }
            
            if conclusion != "success":
                result["failure_details"] = get_failure_logs(github_token, repo, run_id)
            
            return result
        
        time.sleep(check_interval)
    
    # 超时
    return {
        "name": workflow_name,
        "run_id": run_id,
        "status": "timed_out",
        "conclusion": "timed_out",
        "html_url": f"https://github.com/{repo}/actions/runs/{run_id}",
        "error": "Monitoring timed out after 120 minutes",
        "failure_details": get_failure_logs(github_token, repo, run_id)
    }

def get_failure_logs(github_token, repo, run_id):
    """获取失败日志"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    try:
        jobs_url = f"https://api.github.com/repos/{repo}/actions/runs/{run_id}/jobs"
        failure_details = []
        page = 1
        while True:
            jobs_response = requests.get(
                jobs_url, headers=headers,
                params={"per_page": 100, "page": page}, timeout=30)
            jobs_response.raise_for_status()
            jobs_data = jobs_response.json()["jobs"]
            for job in jobs_data:
                if job.get("conclusion") not in ("success", "skipped", "neutral"):
                    job_info = {
                        "name": job["name"],
                        "status": job.get("status"),
                        "conclusion": job.get("conclusion"),
                        "steps": []
                    }
                    
                    for step in job.get("steps", []):
                        if step.get("conclusion") not in ("success", "skipped", "neutral"):
                            job_info["steps"].append({
                                "name": step["name"],
                                "number": step["number"],
                                "status": step.get("status"),
                                "conclusion": step.get("conclusion")
                            })
                    
                    failure_details.append(job_info)
            if len(jobs_data) < 100:
                break
            page += 1
        
        return failure_details
    except Exception as e:
        print(f"Error getting failure logs: {e}")
        return []

def get_workflow_id(github_token, repo, workflow_name):
    """获取工作流ID"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    url = f"https://api.github.com/repos/{repo}/actions/workflows"
    response = requests.get(url, headers=headers, params={"per_page": 100}, timeout=30)
    
    if response.status_code == 200:
        workflows = response.json()["workflows"]
        for workflow in workflows:
            if workflow["name"] == workflow_name:
                return workflow["id"]
    return None

def main():
    github_token = os.getenv("GITHUB_TOKEN")
    repo = os.getenv("GITHUB_REPOSITORY")
    workflows_json = os.getenv("TARGET_WORKFLOWS")
    start_time = sys.argv[1] if len(sys.argv) > 1 else datetime.now(timezone.utc).isoformat()
    
    if not all([github_token, repo, workflows_json]):
        raise ValueError("Missing required environment variables")
    
    workflows = json.loads(workflows_json)
    results = monitor_workflows(github_token, repo, workflows, start_time)
    
    print(f"\n=== Monitoring Summary ===")
    for result in results:
        status_icon = "✅" if result.get("conclusion") == "success" else "❌" if result.get("conclusion") == "failure" else "⚠️"
        print(f"{status_icon} {result['name']}: {result.get('conclusion', 'unknown')}")

    return 0 if results and all(r.get("conclusion") == "success" for r in results) else 1

if __name__ == "__main__":
    sys.exit(main())
