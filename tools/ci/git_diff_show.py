# 
# Copyright (c) 2025, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2025-05-15     supperthomas add PR status show
# 2025-05-22     hydevcode    替换bsp_building.yml的判断文件修改机制,并将PR status show合并进bsp_building.yml
import subprocess
import sys
import os
import re
import argparse
import locale
from typing import List, Dict

import json
from typing import List

try:
    from git_utils import get_blob_size
    from git_utils import get_merge_base as git_get_merge_base
    from git_utils import get_name_status_lines
except ImportError:
    from tools.ci.git_utils import get_blob_size
    from tools.ci.git_utils import get_merge_base as git_get_merge_base
    from tools.ci.git_utils import get_name_status_lines

class FileDiff:
    def __init__(self, path: str, status: str, size_change: int = 0, old_size: int = 0, new_size: int = 0):
        self.path = path
        self.status = status  # A (added), M (modified), D (deleted), R (renamed)
        self.size_change = size_change
        self.old_size = old_size
        self.new_size = new_size
        
    def __str__(self):
        if self.status == 'A':
            return f"Added {self.path}: {self.size_change} bytes"
        elif self.status == 'D':
            return f"Deleted {self.path}: was {self.old_size} bytes"
        elif self.status == 'M' or self.status == 'R':
            return f"Modified {self.path}: {self.size_change} bytes change"
        else:
            return f"{self.status} {self.path}"
            
class GitDiffAnalyzer:
    def __init__(self, target_branch: str):
        self.target_branch = target_branch
        self.encoding = locale.getpreferredencoding()

    def get_diff_files(self) -> List[FileDiff]:
        """获取当前分支与目标分支之间的差异文件"""
        # 找到当前分支和目标分支的最近共同祖先
        merge_base = self.get_merge_base()
        if not merge_base:
            print("No common ancestor found between current branch and target branch")
            sys.exit(1)
            
        # 获取差异文件列表
        print("git diff --name-status {} HEAD".format(merge_base))
        try:
            lines = get_name_status_lines(merge_base, "HEAD", self.encoding)
            output = "\n".join(lines)
            print(output)
        except RuntimeError as e:
            print("Error executing git diff: {}".format(e))
            sys.exit(1)
            
        if not output:
            print("No differences between current branch and target branch")
            sys.exit(0)
            
        # 处理可能的换行符问题
        output = output.replace('\r\n', '\n')
        lines = output.split('\n')
        
        file_diffs = []
        for line in lines:
            line = line.strip()
            if not line:
                continue
                
            parts = line.split('\t')
            if len(parts) < 2:
                # 可能是重命名文件，格式为 "RXXX\told_path\tnew_path"
                match = re.match(r'R(\d+)\t(.+)\t(.+)', line)
                if match:
                    status = 'R'
                    old_path = match.group(2)
                    new_path = match.group(3)
                    # 计算重命名文件的修改大小
                    old_size = self.get_file_size(old_path, self.target_branch)
                    new_size = self.get_file_size(new_path, 'HEAD')
                    size_change = new_size - old_size if old_size > 0 else new_size
                    file_diffs.append(FileDiff(new_path, status, size_change, old_size, new_size))
            else:
                status = parts[0][0]  # 取状态码的第一个字符
                path = parts[1]
                
                if status == 'A':
                    # 新增文件，计算大小
                    size = self.get_file_size(path, 'HEAD')
                    file_diffs.append(FileDiff(path, status, size, 0, size))
                elif status == 'D':
                    # 删除文件，计算原大小
                    size = self.get_file_size(path, self.target_branch)
                    file_diffs.append(FileDiff(path, status, 0, size, 0))
                elif status == 'M':
                    # 修改文件，计算大小变化
                    old_size = self.get_file_size(path, self.target_branch)
                    new_size = self.get_file_size(path, 'HEAD')
                    size_change = new_size - old_size
                    file_diffs.append(FileDiff(path, status, size_change, old_size, new_size))
                    
        return file_diffs

    def get_merge_base(self) -> str:
        """获取当前分支和目标分支的最近共同祖先"""
        try:
            print("git merge-base {} HEAD".format(self.target_branch))
            return git_get_merge_base(self.target_branch, "HEAD", self.encoding)
        except RuntimeError as e:
            print("Error executing git merge-base: {}".format(e))
            return None

    def get_file_size(self, path: str, ref: str) -> int:
        """Get the size of a file at the specified git ref."""
        return get_blob_size(ref, path, self.encoding)

def format_size(size: int) -> str:
    """将字节大小转换为人类可读的格式"""
    if size >= 0:
        if size < 1024:
            return f"{size} bytes"
        elif size < 1024 * 1024:
            return f"{size / 1024:.1f} KB"
        elif size < 1024 * 1024 * 1024:
            return f"{size / (1024 * 1024):.1f} MB"
        else:
            return f"{size / (1024 * 1024 * 1024):.1f} GB"
    else:
        temp_size=abs(size)
        if temp_size < 1024:
            return f"-{temp_size} bytes"
        elif temp_size < 1024 * 1024:
            return f"-{temp_size / 1024:.1f} KB"
        elif temp_size < 1024 * 1024 * 1024:
            return f"-{temp_size / (1024 * 1024):.1f} MB"
        else:
            return f"-{temp_size / (1024 * 1024 * 1024):.1f} GB"

def is_bsp(path):
    return os.path.isfile(os.path.join(path, "rtconfig.h"))

def filter_bsp_config(file_diffs: List[FileDiff], config_path: str):
    # 读取原始JSON配置
    with open(config_path, 'r', encoding='utf-8') as f:
        config = json.load(f)

    # 获取所有修改的文件路径（统一使用Linux风格路径）
    modified_paths = [diff.path.replace('\\', '/') for diff in file_diffs]
    print(modified_paths)
    if not modified_paths:
        print("master分支运行")
        return

    bsp_paths = set()
    bsp_in_but_not_bsp_paths = set()
    all_print_paths = set()
    for modified_path in modified_paths:
        parts = modified_path.strip(os.sep).split('/')
        if not parts:
            continue
        first_level = parts[0]
        first_level_path = os.path.join(os.getcwd(), first_level)

        #处理bsp路径的逻辑
        if first_level == "bsp":
            temp_path=os.path.join(os.getcwd(), modified_path)
            # 判断是否是文件
            if not os.path.isdir(modified_path):
                temp_path = os.path.dirname(temp_path)

            #循环搜索每一级是否有rtconfig.h
            while temp_path !=first_level_path:
                if is_bsp(temp_path):
                    bsp_paths.add(temp_path)
        
                    break
                temp_path=os.path.dirname(temp_path)

            if temp_path ==first_level_path:
                bsp_in_but_not_bsp_paths.add(parts[1])

        else:
            #非bsp路径逻辑
            all_print_paths.add(first_level_path)

    # 变成相对路径
    bsp_list = set()
    for path in sorted(bsp_paths):
        current_working_dir = os.path.join(os.getcwd(), "bsp/")
        if path.startswith(current_working_dir):
            bsp_list.add(path[len(current_working_dir):].lstrip(os.sep))
        else:
            bsp_list.add(path)  # 如果 first_level_path 不以 current_working_dir 开头，则保持不变

    # 处理修改了bsp外的文件的情况
    filtered_bsp = [
        path for path in bsp_list
        if path.split('/')[0] not in bsp_in_but_not_bsp_paths
    ]

    merged_result = filtered_bsp + list(bsp_in_but_not_bsp_paths)

    filtered_legs = []
    for leg in config["legs"]:
        matched_paths = [
            path for path in leg.get("SUB_RTT_BSP", [])
            if any(keyword in path for keyword in merged_result)
        ]
        if matched_paths:
            filtered_legs.append({**leg, "SUB_RTT_BSP": matched_paths})

    # 生成新的配置
    new_config = {"legs": filtered_legs}

    # 判断有没有修改到bsp外的文件，有的话则编译全部
    if not all_print_paths:
        print(new_config)
        file_name = ".github/ALL_BSP_COMPILE_TEMP.json"

        # 将 new_config 写入文件
        with open(file_name, "w", encoding="utf-8") as file:
            json.dump(new_config, file, ensure_ascii=False, indent=4)


def main():
        # 源文件路径
    source_file = ".github/ALL_BSP_COMPILE.json"  # 替换为你的文件路径

    # 目标文件路径
    target_file = ".github/ALL_BSP_COMPILE_TEMP.json"  # 替换为你的目标文件路径

    # 读取源文件并过滤掉带有 // 的行
    with open(source_file, "r", encoding="utf-8") as infile, open(target_file, "w", encoding="utf-8") as outfile:
        for line in infile:
            if not line.lstrip().startswith("//"):
                outfile.write(line)
    
    parser = argparse.ArgumentParser(description='Compare current branch with target branch and show file differences.')
    parser.add_argument('target_branch', help='Target branch to compare against (e.g., master)')
    args = parser.parse_args()
    
    analyzer = GitDiffAnalyzer(args.target_branch)
    file_diffs = analyzer.get_diff_files()

    # 生成报告
    generate_report(file_diffs, args.target_branch)

    filter_bsp_config(file_diffs,".github/ALL_BSP_COMPILE_TEMP.json")

    
def add_summary(text):
    """
    add summary to github action.
    """
    if "GITHUB_STEP_SUMMARY" in os.environ:
        summary_path = os.environ["GITHUB_STEP_SUMMARY"]  # 获取摘要文件路径

        # 将 text 写入摘要文件（追加模式）
        with open(summary_path, "a") as f:  # "a" 表示追加模式
            f.write(text + "\n")  # 写入文本并换行
    else:
        print("Environment variable $GITHUB_STEP_SUMMARY is not set.")

def summarize_diff(label, count, size=None):
    """格式化输出变更摘要"""
    line = f"  {label:<12} {count:>3} files"
    if size is not None:
        line += f" ({format_size(size)})"
    add_summary(line)

def generate_report(file_diffs: List[FileDiff], target_branch: str):
    """生成差异报告"""

    add_summary(f"# 📊 **Comparison between {target_branch} and Current Branch**\n")
    
    # 分类统计
    added_files         = [f for f in file_diffs if f.status.startswith('A')]
    removed_files       = [f for f in file_diffs if f.status.startswith('D')]
    modified_files      = [f for f in file_diffs if f.status.startswith('M')]
    renamed_files       = [f for f in file_diffs if f.status.startswith('R')]
    copied_files        = [f for f in file_diffs if f.status.startswith('C')]
    unmerged_files      = [f for f in file_diffs if f.status.startswith('U')]
    type_changed_files  = [f for f in file_diffs if f.status.startswith('T')]
    
    # 计算总变化量
    total_added         = sum(f.size_change for f in added_files)
    total_removed       = sum(f.old_size for f in removed_files)
    total_modified      = sum(f.size_change for f in modified_files)
    total_copied        = sum(f.size_change for f in copied_files)
    total_renamed       = sum(f.old_size for f in renamed_files)
    total_type_changed  = sum(f.size_change for f in type_changed_files)

    total_size_change   = sum(f.size_change for f in file_diffs)
    # === 汇总输出 ===
    summarize_diff("Total:", len(file_diffs))
    summarize_diff("Added:", len(added_files), total_added)
    summarize_diff("Removed:", len(removed_files), total_removed)
    summarize_diff("Modified:", len(modified_files), total_modified)
    summarize_diff("Renamed:", len(renamed_files), total_renamed)
    summarize_diff("Copied:", len(copied_files), total_copied)
    summarize_diff("Type Changed:", len(type_changed_files), total_type_changed)
    summarize_diff("Unmerged:", len(unmerged_files))


    if total_size_change > 0:
        change_desc = f"📈 **Increase of {format_size(total_size_change)}**"
    elif total_size_change < 0:
        change_desc = f"📉 **Reduction of {format_size(abs(total_size_change))}**"
    else:
        change_desc = "➖ **No net size change**"

    add_summary(f"\n### 📦 **Total Size Change:** {change_desc} (Excluding removed files)")

    
    # 显示详细差异文件内容
    add_summary("\n## 📂 **Detailed File Changes**\n")

    for diff in file_diffs:
        add_summary(f"📄 {diff.path} —  **[{diff.status}]**")

        # 文件状态处理
        if diff.status.startswith('A'):
            add_summary(f"📦 Size: {format_size(diff.new_size)}")

        elif diff.status.startswith(('M', 'R')):  # 修改或重命名
            add_summary(f"📏 Original size: {format_size(diff.old_size)}")
            add_summary(f"📐 New size: {format_size(diff.new_size)}")

            delta = diff.size_change
            if delta > 0:
                change_str = f"📈 Increased by {format_size(delta)}"
            elif delta < 0:
                change_str = f"📉 Reduced by {format_size(abs(delta))}"
            else:
                change_str = "➖ No size change"

            add_summary(f"📊 Size change: {change_str}")

        elif diff.status.startswith('D'):
            add_summary(f"🗑️ Original size: {format_size(diff.old_size)}")

        elif diff.status.startswith('C'):
            add_summary(f"📎 Copied from size: {format_size(diff.old_size)} → {format_size(diff.new_size)}")

        elif diff.status.startswith('T'):
            add_summary("⚙️ File type changed")

        elif diff.status.startswith('U'):
            add_summary("⚠️ Unmerged conflict detected")

        else:
            add_summary("❓ Unknown change type")

        add_summary("\n\n")

if __name__ == "__main__":
    main()