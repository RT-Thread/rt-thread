#
# Copyright (c) 2006-2021, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2021-04-01     LiuKang      the first version
#

import os
import re
import sys
import click
import yaml
import chardet
import logging
import datetime


def init_logger():
    log_format = "[%(filename)s %(lineno)d %(levelname)s] %(message)s "
    date_format = '%Y-%m-%d  %H:%M:%S %a '
    logging.basicConfig(level=logging.INFO,
                        format=log_format,
                        datefmt=date_format,
                        )


class CheckOut:
    def __init__(self, rtt_repo, rtt_branch):
        self.root = os.getcwd()
        self.rtt_repo = rtt_repo
        self.rtt_branch = rtt_branch

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
        file_list = list()
        try:
            os.system('git remote add rtt_repo {}'.format(self.rtt_repo))
            os.system('git fetch rtt_repo')
            os.system('git reset rtt_repo/{} --soft'.format(self.rtt_branch))
            os.system('git status > git.txt')
        except Exception as e:
            logging.error(e)
            return None
        try:
            with open('git.txt', 'r') as f:
                file_lines = f.readlines()
        except Exception as e:
            logging.error(e)
            return None
        file_path = ''
        for line in file_lines:
            if 'new file' in line:
                file_path = line.split('new file:')[1].strip()
                logging.info('new file -> {}'.format(file_path))
            elif 'deleted' in line:
                logging.info('deleted file -> {}'.format(line.split('deleted:')[1].strip()))
            elif 'modified' in line:
                file_path = line.split('modified:')[1].strip()
                logging.info('modified file -> {}'.format(file_path))
            else:
                continue

            result = self.__exclude_file(file_path)
            if result != 0:
                file_list.append(file_path)

        return file_list


class FormatCheck:
    def __init__(self, file_list):
        self.file_list = file_list

    def __check_file(self, file_lines, file_path):
        line_num = 1
        check_result = True
        for line in file_lines:
            # check line start
            line_start = line.replace(' ', '')
            # find tab
            if line_start.startswith('\t'):
                logging.error("{} line[{}]: please use space replace tab at the start of this line.".format(file_path, line_num))
                check_result = False
            # check line end
            lin_end = line.split('\n')[0]
            if lin_end.endswith(' ') or lin_end.endswith('\t'):
                logging.error("{} line[{}]: please delete extra space at the end of this line.".format(file_path, line_num))
                check_result = False
            line_num += 1

        return check_result

    def check(self):
        logging.info("Start to check files format.")
        if len(self.file_list) == 0:
            logging.warning("There are no files to check format.")
            return True
        encoding_check_result = True
        format_check_result = True
        for file_path in self.file_list:
            code = ''
            if file_path.endswith(".c") or file_path.endswith(".h"):
                try:
                    with open(file_path, 'rb') as f:
                        file = f.read()
                        # get file encoding
                        code = chardet.detect(file)['encoding']
                except Exception as e:
                    logging.error(e)
            else:
                continue

            if code != 'utf-8' and code != 'ascii':
                logging.error("[{0}]: encoding not utf-8, please format it.".format(file_path))
                encoding_check_result = False
            else:
                logging.info('[{0}]: encoding check success.'.format(file_path))

            with open(file_path, 'r', encoding = "utf-8") as f:
                file_lines = f.readlines()
            format_check_result = self.__check_file(file_lines, file_path)    

        if not encoding_check_result or not format_check_result:
            logging.error("files format check fail.")
            return False

        logging.info("files format check success.")

        return True


class LicenseCheck:
    def __init__(self, file_list):
        self.file_list = file_list

    def check(self):
        current_year = datetime.date.today().year
        logging.info("current year: {}".format(current_year))
        if len(self.file_list) == 0:
            logging.warning("There are no files to check license.")
            return 0
        logging.info("Start to check files license.")
        check_result = True
        for file_path in self.file_list:
            if file_path.endswith(".c") or file_path.endswith(".h"):
                try:
                    with open(file_path, 'r') as f:
                        file = f.readlines()
                except Exception as e:
                    logging.error(e)
            else:
                continue

            if 'Copyright' in file[1] and 'SPDX-License-Identifier: Apache-2.0' in file[3]:
                try:
                    license_year = re.search(r'2006-\d{4}', file[1]).group()
                    true_year = '2006-{}'.format(current_year)
                    if license_year != true_year:
                        logging.warning("[{0}]: license year: {} is not true: {}, please update.".format(file_path,
                                                                                                         license_year,
                                                                                                         true_year))
                                                                                                
                    else:
                        logging.info("[{0}]: license check success.".format(file_path))
                except Exception as e:
                    logging.error(e)
            
            else:
                logging.error("[{0}]: license check fail.".format(file_path))
                check_result = False

        return check_result


@click.group()
@click.pass_context
def cli(ctx):
    pass


@cli.command()
@click.option(
    '--license',
    "check_license",
    required=False,
    type=click.BOOL,
    flag_value=True,
    help="Enable File license check.",
)
@click.argument(
    'repo',
    nargs=1,
    type=click.STRING,
    default='https://github.com/RT-Thread/rt-thread',
)
@click.argument(
    'branch',
    nargs=1,
    type=click.STRING,
    default='master',
)
def check(check_license, repo, branch):
    """
    check files license and format.
    """
    init_logger()
    # get modified files list
    checkout = CheckOut(repo, branch)
    file_list = checkout.get_new_file()
    if file_list is None:
        logging.error("checkout files fail")
        sys.exit(1)

    # check modified files format
    format_check = FormatCheck(file_list)
    format_check_result = format_check.check()
    license_check_result = True
    if check_license:
        license_check = LicenseCheck(file_list)
        license_check_result = license_check.check()

    if not format_check_result or not license_check_result:
        logging.error("file format check or license check fail.")
        sys.exit(1)
    logging.info("check success.")
    sys.exit(0)


if __name__ == '__main__':
    cli()
