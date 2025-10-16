#
# Copyright (c) 2006-2023, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2023-05-16     dejavudwh    the first version
#

import yaml
import logging
import os
import subprocess

def init_logger():
    log_format = "[%(filename)s %(lineno)d %(levelname)s] %(message)s "
    date_format = '%Y-%m-%d  %H:%M:%S %a '
    logging.basicConfig(level=logging.INFO,
                        format=log_format,
                        datefmt=date_format,
                        )

class CheckOut:
    def __init__(self):
        pass
    
    def __exclude_file(self, file_path):
        dir_number = file_path.split('/')
        ignore_path = file_path

        # gets the file path depth.
        for i in dir_number:
            # current directory.
            dir_name = os.path.dirname(ignore_path)
            ignore_path = dir_name
            # judge the ignore file exists in the current directory.
            ignore_file_path = os.path.join(dir_name, ".ignore_format.yml")
            if not os.path.exists(ignore_file_path):
                continue
            try:
                with open(ignore_file_path) as f:
                    ignore_config = yaml.safe_load(f.read())
                file_ignore = ignore_config.get("file_path", [])
                dir_ignore = ignore_config.get("dir_path", [])
            except Exception as e:
                logging.error(e)
                continue
            logging.debug("ignore file path: {}".format(ignore_file_path))
            logging.debug("file_ignore: {}".format(file_ignore))
            logging.debug("dir_ignore: {}".format(dir_ignore))
            try:
                # judge file_path in the ignore file.
                for file in file_ignore:
                    if file is not None:
                        file_real_path = os.path.join(dir_name, file)
                        if file_real_path == file_path:
                            logging.info("ignore file path: {}".format(file_real_path))
                            return 0

                file_dir_path = os.path.dirname(file_path)
                for _dir in dir_ignore:
                    if _dir is not None:
                        dir_real_path = os.path.join(dir_name, _dir)
                        if file_dir_path.startswith(dir_real_path):
                            logging.info("ignore dir path: {}".format(dir_real_path))
                            return 0
            except Exception as e:
                logging.error(e)
                continue

        return 1
    
    def get_new_file(self):
        result = subprocess.run(['git', 'diff', '--name-only', 'HEAD', 'origin/master', '--diff-filter=ACMR', '--no-renames', '--full-index'], stdout = subprocess.PIPE)
        file_list = result.stdout.decode().strip().split('\n')
        new_files = []
        for line in file_list:
            logging.info("modified file -> {}".format(line))
            result = self.__exclude_file(line)
            if result != 0:
                new_files.append(line)
        
        return new_files