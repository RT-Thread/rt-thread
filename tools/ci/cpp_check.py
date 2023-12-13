#
# Copyright (c) 2006-2023, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2023-05-16     dejavudwh    the first version
#

import click
import logging
import subprocess
import sys
import format_ignore

class CPPCheck:
    def __init__(self, file_list):
        self.file_list = file_list

    def check(self):
        file_list_filtered = [file for file in self.file_list if file.endswith(('.c', '.cpp', '.cc', '.cxx'))]
        logging.info("Start to static code analysis.")
        check_result = True
        for file in file_list_filtered:
            result = subprocess.run(['cppcheck', '-DRTM_EXPORT', '--enable=warning', 'performance', 'portability', '--inline-suppr', '--error-exitcode=1', '--force', file], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
            logging.info(result.stdout.decode())
            logging.info(result.stderr.decode())
            if result.stderr:
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
