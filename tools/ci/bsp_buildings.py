import os
import shutil
import re
import multiprocessing
import yaml

def add_summary(text):
    """
    add summary to github action.
    """
    os.system(f'echo "{text}" >> $GITHUB_STEP_SUMMARY ;')


def run_cmd(cmd, output_info=True):
    """
    run command and return output and result.
    """
    print('\033[1;32m' + cmd + '\033[0m')

    output_str_list = []
    res = 0

    if output_info:
        res = os.system(cmd + " > output.txt 2>&1")
    else:
        res = os.system(cmd + " > /dev/null 2>output.txt")

    with open("output.txt", "r") as file:
        output_str_list = file.readlines()

    for line in output_str_list:
        print(line, end='')

    os.remove("output.txt")

    return output_str_list, res


def build_bsp(bsp, scons_args=''):
    """
    build bsp.

    cd {rtt_root}
    scons -C bsp/{bsp} --pyconfig-silent > /dev/null

    cd {rtt_root}/bsp/{bsp}
    pkgs --update > /dev/null
    pkgs --list

    cd {rtt_root}
    scons -C bsp/{bsp} -j{nproc} {scons_args}

    cd {rtt_root}/bsp/{bsp}
    scons -c > /dev/null
    rm -rf packages

    """
    success = True
    os.chdir(rtt_root)
    if os.path.exists(f"{rtt_root}/bsp/{bsp}/Kconfig"):
        os.chdir(rtt_root)
        run_cmd(f'scons -C bsp/{bsp} --pyconfig-silent', output_info=False)

        os.chdir(f'{rtt_root}/bsp/{bsp}')
        run_cmd('pkgs --update', output_info=False)
        run_cmd('pkgs --list')

        nproc = multiprocessing.cpu_count()
        os.chdir(rtt_root)
        cmd = f'scons -C bsp/{bsp} -j{nproc} {scons_args}'
        __, res = run_cmd(cmd, output_info=True)

        if res != 0:
            success = False

    os.chdir(f'{rtt_root}/bsp/{bsp}')
    run_cmd('scons -c', output_info=False)

    pkg_dir = os.path.join(rtt_root, 'bsp', bsp, 'packages')
    shutil.rmtree(pkg_dir, ignore_errors=True)

    return success


def append_file(source_file, destination_file):
    """
    append file to another file.
    """
    with open(source_file, 'r') as source:
        with open(destination_file, 'a') as destination:
            for line in source:
                destination.write(line)

def check_scons_args(file_path):
    args = []
    with open(file_path, 'r') as file:
        for line in file:
            match = re.search(r'#\s*scons:\s*(.*)', line)
            if match:
                args.append(match.group(1).strip())
    return ' '.join(args)

def get_details_and_dependencies(details, projects, seen=None):
    if seen is None:
        seen = set()
    detail_list = []
    if details is not None:
        for dep in details:
            if dep not in seen:
                dep_details=projects.get(dep)
                seen.add(dep)
                if dep_details is not None:
                    if dep_details.get('depends') is not None:
                        detail_temp=get_details_and_dependencies(dep_details.get('depends'), projects, seen)
                        for line in detail_temp:
                            detail_list.append(line)
                    if dep_details.get('kconfig') is not None:
                        for line in dep_details.get('kconfig'):
                            detail_list.append(line)
            else:
                print(f"::error::There are some problems with attachconfig depend: {dep}");
    return detail_list

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

    attachconfig_dir = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
    attach_path = os.path.join(attachconfig_dir, attach_file)

    append_file(attach_path, config_file)

    scons_args = check_scons_args(attach_path)

    res = build_bsp(bsp, scons_args)

    shutil.copyfile(config_bacakup, config_file)
    os.remove(config_bacakup)

    return res


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
        res = build_bsp(bsp)
        if not res:
            print(f"::error::build {bsp} failed")
            add_summary(f"- ❌ build {bsp} failed.")
            failed += 1
        else:
            add_summary(f'- ✅ build {bsp} success.')
        print("::endgroup::")

        yml_files_content = []
        directory = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
        if os.path.exists(directory):
            for root, dirs, files in os.walk(directory):
                for filename in files:
                    if filename.endswith('attachconfig.yml'):
                        file_path = os.path.join(root, filename)
                        if os.path.exists(file_path):
                            try:
                                with open(file_path, 'r') as file:
                                    content = yaml.safe_load(file)
                                    if content is None:
                                        continue
                                    yml_files_content.append(content)
                            except yaml.YAMLError as e:
                                print(f"::error::Error parsing YAML file: {e}")
                                continue
                            except Exception as e:
                                print(f"::error::Error reading file: {e}")
                                continue
        
        config_file = os.path.join(rtt_root, 'bsp', bsp, '.config')

        for projects in yml_files_content:
            for name, details in projects.items():
                count += 1
                config_bacakup = config_file+'.origin'
                shutil.copyfile(config_file, config_bacakup)
                with open(config_file, 'a') as destination:
                    if details.get("kconfig") is None:
                        continue
                    if(projects.get(name) is not None):
                        detail_list=get_details_and_dependencies([name],projects)
                        for line in detail_list:
                            destination.write(line + '\n')
                scons_arg=[]
                if details.get('scons_arg') is not None:
                    for line in details.get('scons_arg'):
                        scons_arg.append(line)
                scons_arg_str=' '.join(scons_arg) if scons_arg else ' '
                print(f"::group::\tCompiling yml project: =={count}==={name}=scons_arg={scons_arg_str}==")
                res = build_bsp(bsp, scons_arg_str)
                if not res:
                    print(f"::error::build {bsp} {name} failed.")
                    add_summary(f'\t- ❌ build {bsp} {name} failed.')
                    failed += 1
                else:
                    add_summary(f'\t- ✅ build {bsp} {name} success.')
                print("::endgroup::")

                shutil.copyfile(config_bacakup, config_file)
                os.remove(config_bacakup)

        attach_dir = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
        attach_list = []
        for root, dirs, files in os.walk(attach_dir):
            for file in files:
                if file.endswith('attach'):
                    file_path = os.path.join(root, file)
                    relative_path = os.path.relpath(file_path, attach_dir)
                    attach_list.append(relative_path)

        for attach_file in attach_list:
            count += 1
            print(f"::group::\tCompiling BSP: =={count}=== {bsp} {attach_file}===")
            res = build_bsp_attachconfig(bsp, attach_file)
            if not res:
                print(f"::error::build {bsp} {attach_file} failed.")
                add_summary(f'\t- ❌ build {attach_file} failed.')
                failed += 1
            else:
                add_summary(f'\t- ✅ build {attach_file} success.')
            print("::endgroup::")

    exit(failed)
