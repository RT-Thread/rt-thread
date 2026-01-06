import subprocess  
import os

# 每个 target_dir 对应一个配置：env 脚本 + 自定义的 first_commands 列表
target_configs = {
    "../../../aarch64": {
        "env_script": "thread-env-aarch64.sh",
        "first_commands": [
            "scons --attach=board.e2000d_demo_rtthread",
            "scons --attach=board.e2000q_demo_rtthread",
            "scons --attach=board.phytium_pi_rtthread",
            "scons --attach=board.pd2408_test_a_rtthread", 
            "scons --attach=board.pd2408_test_b_rtthread",
        ]
    },
    "../../../aarch32": {
        "env_script": "thread-env-aarch32.sh",
        "first_commands": [
            "scons --attach=board.e2000d_demo_rtthread",
            "scons --attach=board.e2000q_demo_rtthread",
            "scons --attach=board.phytium_pi_rtthread",             
        ]
    },
}

# 固定命令（每组后执行）
fixed_commands = [
    "make clean",
    "scons -j8",
    "make mv_auto_test_file",
    "scons --attach=default",
]

# <<< 新增 >>> 指定要检查/清理的 ELF 文件输出目录
build_output_path = "/home/zhugy/tftpboot/rtthread_elfs/"

# <<< 新增 >>> 删除路径下的所有 ELF 文件
def remove_elf_files_in_path(target_path):
    abs_target_path = os.path.abspath(target_path)
    print(f"\n====== 清理路径: {abs_target_path} 中的 ELF 文件 ======")
    removed_any = False

    for root, dirs, files in os.walk(abs_target_path):
        for file in files:
            if file.endswith(".elf"):
                file_path = os.path.join(root, file)
                try:
                    os.remove(file_path)
                    print(f"🗑️ 删除: {file_path}")
                    removed_any = True
                except Exception as e:
                    print(f"⚠️ 删除失败: {file_path}, 错误: {e}")


# <<< 新增 >>> 执行前先清理 build_output_path 中的 ELF 文件
remove_elf_files_in_path(build_output_path)

# 执行命令组的函数
def run_commands_in_directory(target_dir, env_script, first_commands):
    abs_target_dir = os.path.abspath(target_dir)
    script_dir = os.path.abspath(os.path.dirname(__file__))
    env_script_path = os.path.join(script_dir, env_script)

    print(f"\n>>> 进入目录: {abs_target_dir}")
    print(f">>> 使用环境脚本: {env_script_path}")

    for i, first_cmd in enumerate(first_commands, start=1):
        print(f"\n== 执行第 {i} 组命令 ==")

        # 构造 bash 命令
        full_command = (
            f"bash -c '"
            f"source \"{env_script_path}\" && "
            f"pushd \"{abs_target_dir}\" > /dev/null && "
            f"{first_cmd} && "
            f"{' && '.join(fixed_commands)} && "
            f"popd > /dev/null'"
        )

        subprocess.run(full_command, shell=True)

# 遍历所有配置项并执行命令
for target_dir, config in target_configs.items():
    run_commands_in_directory(
        target_dir,
        config["env_script"],
        config["first_commands"]
    )

# >>> 检查 build_output_path 下的所有 ELF 文件 <<<
def find_elf_files_in_path(search_path):
    abs_search_path = os.path.abspath(search_path)
    print(f"\n====== 检查路径: {abs_search_path} 下的 ELF 文件 ======")

    elf_files = []
    for root, dirs, files in os.walk(abs_search_path):
        for file in files:
            if file.endswith(".elf"):
                elf_files.append(os.path.join(root, file))

    if elf_files:
        for elf in elf_files:
            print(f"✔️ 找到 ELF 文件: {elf}")
    else:
        print("⚠️ 未找到 ELF 文件")

# 最后执行 ELF 文件检查
find_elf_files_in_path(build_output_path)
