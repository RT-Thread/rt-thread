import os
import re
import glob
import shutil
import multiprocessing


def add_summary(text):
    """
    add summary to github action.
    """
    os.system(f'echo "{text}" >> $GITHUB_STEP_SUMMARY ;')


def run_cmd(cmd):
    """
    run command and return output and result.
    """
    print('\033[1;32m' + cmd + '\033[0m')
    res = os.system(cmd + " > output.txt 2>&1")
    with open("output.txt", "r") as file:
        output = file.readlines()
    for line in output:
        print(line, end='')
    os.remove("output.txt")
    return output, res


def build_bsp(bsp):
    """
    build bsp.

    cd {rtt_root}
    scons -C bsp/{bsp} --pyconfig-silent

    cd {rtt_root}/bsp/{bsp}
    pkgs --upgrade-script-force
    pkgs --update
    pkgs --list

    cd {rtt_root}
    scons -C bsp/{bsp} -j{nproc} --debug=time

    cd {rtt_root}/bsp/{bsp}
    scons -c
    rm -rf packages

    """
    success = True
    os.chdir(rtt_root)
    if os.path.exists(f"{rtt_root}/bsp/{bsp}/Kconfig"):
        os.chdir(rtt_root)
        run_cmd(f'scons -C bsp/{bsp} --pyconfig-silent')

        os.chdir(f'{rtt_root}/bsp/{bsp}')
        run_cmd('pkgs --upgrade-script-force')
        run_cmd('pkgs --update')
        run_cmd('pkgs --list')

        nproc = multiprocessing.cpu_count()
        os.chdir(rtt_root)
        output, res = run_cmd(f'scons -C bsp/{bsp} -j{nproc} --debug=time')

        total_time = 0
        for line in output:
            pattern = r"Total command execution time: (\d+\.\d+) seconds"
            match = re.search(pattern, line)
            if match:
                total_time = match.group(1)
                break
        if res != 0:
            success = False

    os.chdir(f'{rtt_root}/bsp/{bsp}')
    run_cmd('scons -c')

    pkg_dir = os.path.join(rtt_root, 'bsp', bsp, 'packages')
    shutil.rmtree(pkg_dir, ignore_errors=True)

    return success, total_time


def append_file(source_file, destination_file):
    """
    append file to another file.
    """
    with open(source_file, 'r') as source:
        with open(destination_file, 'a') as destination:
            for line in source:
                destination.write(line)


def build_bsp_attachconfig(bsp, attach_file):
    """
    build bsp with attach config.

    cp bsp/{bsp}/.config bsp/{bsp}/.config.origin
    cat .ci/attachconfig/{attach_file} >> bsp/{bsp}/.config

    build_bsp()

    cp bsp/{bsp}/.config.origin bsp/{bsp}/.config
    rm bsp/{bsp}/.config.origin

    """
    config_file = os.path.join(rtt_root, 'bsp', bsp, '.config')
    config_bacakup = config_file+'.origin'
    shutil.copyfile(config_file, config_bacakup)

    append_file(attach_file, config_file)

    res, total_time = build_bsp(bsp)

    shutil.copyfile(config_bacakup, config_file)
    os.remove(config_bacakup)

    return res, total_time


if __name__ == "__main__":
    """
    build all bsp and attach config.

    1. build all bsp.
    2. build all bsp with attach config.

    """
    failed = 0
    count = 0

    rtt_root = os.getcwd()
    srtt_bsp = os.getenv('SRTT_BSP').split(',')

    for bsp in srtt_bsp:
        count += 1
        print(f"::group::Compiling BSP: =={count}=== {bsp} ====")
        res, total_time = build_bsp(bsp)
        if not res:
            print(f"::error::build {bsp} failed")
            add_summary(f"- ❌ build {bsp} failed in {total_time} s.")
            failed += 1
        else:
            add_summary(f'- ✅ build {bsp} success in {total_time} s.')
        print("::endgroup::")

        attach_dir = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
        attach_files = glob.glob(os.path.join(attach_dir, '*.attach'))
        for attach_file in attach_files:
            count += 1
            attach = os.path.basename(attach_file)
            print(f"::group::\tCompiling BSP: =={count}=== {bsp} {attach}===")
            res, total_time = build_bsp_attachconfig(bsp, attach_file)
            if not res:
                print(f"::error::build {bsp} {attach} failed.")
                add_summary(f'\t- ❌ build {attach} failed in {total_time} s.')
                failed += 1
            else:
                add_summary(f'\t- ✅ build {attach} success in {total_time} s.')
            print("::endgroup::")

    exit(failed)
