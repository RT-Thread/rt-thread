#!/usr/bin/env python3
import os
import json
import requests
import time
from datetime import datetime, timezone

def trigger_workflow_directly(workflow_name, github_token, repo):
    """直接触发工作流"""
    headers = {
        "Authorization": f"token {github_token}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    # 首先获取工作流ID
    workflow_id = get_workflow_id(github_token, repo, workflow_name)
    if not workflow_id:
        print(f"✗ Workflow '{workflow_name}' not found")
        return False
    
    # 使用 workflow_dispatch API 直接触发
    dispatch_url = f"https://api.github.com/repos/{repo}/actions/workflows/{workflow_id}/dispatches"  # 🔧 修复：添加这行
    
    # 根据工作流实际定义的输入参数进行调整
    dispatch_data = {
        "ref": "master",
        "inputs": {
            "trigger_type": "scheduled"  # 使用工作流实际定义的输入参数
        }
    }
    
    try:
        print(f"Triggering workflow: {workflow_name} (ID: {workflow_id})")
        response = requests.post(dispatch_url, headers=headers, json=dispatch_data)  # 🔧 修复：现在 dispatch_url 已定义
        
        if response.status_code == 204:
            print(f"✓ Successfully triggered workflow: {workflow_name}")
            return True
        else:
            print(f"✗ Failed to trigger {workflow_name}: {response.status_code}")
            print(f"Response: {response.text}")
            return False
            
    except Exception as e:
        print(f"✗ Error triggering {workflow_name}: {str(e)}")
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
        print(f"Available workflows: {[w['name'] for w in workflows]}")
    else:
        print(f"Failed to get workflows: {response.status_code}")
    
    return None

def main():
    github_token = os.getenv("GITHUB_TOKEN")
    repo = os.getenv("GITHUB_REPOSITORY")
    workflows_json = os.getenv("TARGET_WORKFLOWS")
    
    if not all([github_token, repo, workflows_json]):
        raise ValueError("Missing required environment variables")
    
    try:
        workflows = json.loads(workflows_json)
    except json.JSONDecodeError:
        raise ValueError("Invalid TARGET_WORKFLOWS JSON format")
    
    print(f"Directly triggering {len(workflows)} workflows...")
    
    success_count = 0
    for i, workflow in enumerate(workflows):
        success = trigger_workflow_directly(workflow, github_token, repo)
        if success:
            success_count += 1
        
        # 在触发之间等待
        if i < len(workflows) - 1:
            print("Waiting 10 seconds before next trigger...")
            time.sleep(10)
    
    print(f"Triggering completed: {success_count}/{len(workflows)} successful")

if __name__ == "__main__":
    main()