#
# Copyright (c) 2006-2023, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2023-05-16     dejavudwh    the first version
# 2024-09-12     supperthomas add cppcheck summary for detail
#

import click
import logging
import subprocess
import sys
import format_ignore
import os
'''
--suppress=syntaxError：
该选项用于抑制特定的错误类型。在这里，syntaxError 是被忽略的错误类型。这意味着 Cppcheck 不会报告语法错误（syntaxError）。这是因为在某些情况下，分析工具可能会误报语法错误，但 CI（持续集成）系统会在编译时捕获这些错误，因此可以忽略。

--enable=warning：
该选项用于启用特定类型的检查。Cppcheck 可以检查不同的级别和种类的问题，如错误、警告、性能问题等。--enable=warning 启用的是警告级别的检查，帮助检测代码中可能存在的问题，但不是严重的错误。

performance：
Cppcheck 可以启用多个检查种类，在这里指定了 performance，意味着会检查与代码性能相关的潜在问题，例如不必要的拷贝操作、无效的条件判断等。这有助于提高代码的运行效率。

portability：
Cppcheck 会检查代码的可移植性问题。可移植性检查帮助发现代码在不同平台或编译器中可能遇到的问题，如特定平台上不支持的类型、函数或特性。这对跨平台开发非常重要。

--inline-suppr：
该选项允许在代码中使用注释来抑制特定的警告或错误信息。通过这种方式，开发者可以直接在代码中添加注释，告诉 Cppcheck 忽略某些检查或警告。例如，开发者可以在代码中添加 // cppcheck-suppress <message> 来抑制特定的警告信息。

--error-exitcode=1：
该选项告诉 Cppcheck 如果遇到错误，就返回指定的退出码。在这里指定的是 1。这对自动化工具非常有用，尤其是在 CI 环境中，因为它可以通过检查返回码来判断 Cppcheck 是否发现了错误。如果有错误，CI 系统会将整个任务标记为失败。

--force：
这个选项强制 Cppcheck 对所有文件进行检查，即使它检测到编译条件缺失或某些配置问题。通常，如果某些宏定义或依赖项缺失，Cppcheck 可能会跳过某些文件的检查。但 --force 会强制工具继续执行分析，即使有可能缺少某些信息。这在某些大型项目中很有用，可以确保所有文件都经过检查。
'''
def add_summary(text):
    """
    add summary to github action.
    """
    os.system(f'echo "{text}" >> $GITHUB_STEP_SUMMARY ;')
    
class CPPCheck:
    def __init__(self, file_list):
        self.file_list = file_list

    def check(self):
        file_list_filtered = [file for file in self.file_list if file.endswith(('.c', '.cpp', '.cc', '.cxx'))]
        logging.info("Start to static code analysis.")
        check_result = True
        for file in file_list_filtered:
            result = subprocess.run(
                [
                    'cppcheck',
                    '-DRT_ASSERT(x)=',
                    '-DRTM_EXPORT(x)=',
                    '-Drt_list_for_each_entry(a,b,c)=a=(void*)b;',
                    '-I include',
                    '-I thread/components/finsh',
                    # it's okay because CI will do the real compilation to check this
                    '--suppress=syntaxError',
                    '--check-level=exhaustive',
                    '--enable=warning',
                    'performance',
                    'portability',
                    '--inline-suppr',
                    '--error-exitcode=1',
                    '--force',
                    file
                ],
                stdout = subprocess.PIPE, stderr = subprocess.PIPE)
            logging.info(result.stdout.decode())
            logging.info(result.stderr.decode())
            if result.stderr:
                add_summary("The following errors are for reference only. If they are not actual issues, please ignore them and do not make unnecessary modifications.")
                add_summary("以下错误仅供参考，如果发现没有问题，请直接忽略，不需要强行修改")
                add_summary(f"- :rotating_light: {result.stderr.decode()}")
                check_result = False
        return check_result

@click.group()
@click.pass_context
def cli(ctx):
    pass

@cli.command()
def check():
    """
    static code analysis(cppcheck).
    """
    format_ignore.init_logger()
    # get modified files list
    checkout = format_ignore.CheckOut()
    file_list = checkout.get_new_file()
    if file_list is None:
        logging.error("checkout files fail")
        sys.exit(1)

    # use cppcheck
    cpp_check = CPPCheck(file_list)
    cpp_check_result = cpp_check.check()

    if not cpp_check_result:
        logging.error("static code analysis(cppcheck) fail.")
        sys.exit(1)
    logging.info("check success.")
    sys.exit(0)


if __name__ == '__main__':
    cli()
