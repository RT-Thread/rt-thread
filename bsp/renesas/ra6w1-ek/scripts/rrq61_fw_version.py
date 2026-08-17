import os
import subprocess


def get_git_cmd_output(cmd):
    script_dir = os.path.dirname(os.path.abspath(__file__))
    p = subprocess.run(['git', '-C', script_dir] + cmd, check=True,
                       capture_output=True)
    return p.stdout.decode('ascii').strip()


def get_fw_version():
    version_value = None
    try:
        git_hash = get_git_cmd_output(['rev-parse', '--short=10', 'HEAD'])
        git_count = get_git_cmd_output(['rev-list', '--all', '--count'])
        version_value = f'{git_hash}-{git_count}'
    except:
        pass
    return version_value
