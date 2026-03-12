#!/usr/bin/env python3
import os
import json
import requests
import time
import sys
from datetime import datetime, timezone

def wait_for_workflows_to_appear(github_token, repo, workflow_names, start_time, max_wait=300):
    """等待工作流出现在API中"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    print(f"Waiting for {len(workflow_names)} workflows to appear...")
    print(f"Start time: {start_time}")
    print(f"Max wait time: {max_wait} seconds")
    
    found_workflows = set()
    start_timestamp = time.time()
    
    while time.time() - start_timestamp < max_wait:
        all_found = True
        
        for workflow_name in workflow_names:
            if workflow_name in found_workflows:
                continue
                
            workflow_id = get_workflow_id(github_token, repo, workflow_name)
            if not workflow_id:
                print(f"Workflow {workflow_name} not found, skipping")
                found_workflows.add(workflow_name)
                continue
            
            # 检查是否有新的运行
            runs = get_recent_runs(github_token, repo, workflow_id, start_time)
            if runs:
                print(f"✓ Found new run for {workflow_name}: {runs[0]['id']}")
                found_workflows.add(workflow_name)
            else:
                print(f"⏳ Waiting for {workflow_name}...")
                all_found = False
        
        if all_found:
            print("✓ All workflows have started!")
            return True
        
        time.sleep(10)  # 每10秒检查一次
    
    print("⚠️ Timeout waiting for workflows to appear")
    print(f"Found {len(found_workflows)} out of {len(workflow_names)} workflows")
    return False

def get_workflow_id(github_token, repo, workflow_name):
    """获取工作流ID"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    url = f"https://api.github.com/repos/{repo}/actions/workflows"
    response = requests.get(url, headers=headers)
    
    if response.status_code == 200:
        workflows = response.json()["workflows"]
        for workflow in workflows:
            if workflow["name"] == workflow_name:
                return workflow["id"]
    return None

def get_recent_runs(github_token, repo, workflow_id, start_time):
    """获取开始时间后的运行"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    url = f"https://api.github.com/repos/{repo}/actions/workflows/{workflow_id}/runs"
    params = {"per_page": 5}
    
    response = requests.get(url, headers=headers, params=params)
    if response.status_code != 200:
        return []
    
    runs = response.json()["workflow_runs"]
    start_time_dt = datetime.fromisoformat(start_time.replace('Z', '+00:00'))
    
    recent_runs = []
    for run in runs:
        run_time = datetime.fromisoformat(run["created_at"].replace('Z', '+00:00'))
        if run_time >= start_time_dt:
            recent_runs.append(run)
    
    return recent_runs

def main():
    github_token = os.getenv("GITHUB_TOKEN")
    repo = os.getenv("GITHUB_REPOSITORY")
    workflows_json = os.getenv("TARGET_WORKFLOWS")
    start_time = sys.argv[1] if len(sys.argv) > 1 else datetime.now(timezone.utc).isoformat()
    
    if not all([github_token, repo, workflows_json]):
        raise ValueError("Missing required environment variables")
    
    workflows = json.loads(workflows_json)
    success = wait_for_workflows_to_appear(github_token, repo, workflows, start_time)
    
    if not success:
        print("Proceeding anyway, some workflows may not be detected...")

if __name__ == "__main__":
    main()