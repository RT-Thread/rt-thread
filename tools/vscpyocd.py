import os
import sys
import json

def create_need_files(targetId, packpath):
    """
    Generate pyocd.yaml files
    """
    yaml_file = open('pyocd.yaml', 'w')
    if yaml_file:
        yaml_file.write('\npack:\n')
        yaml_file.write('  - ' + packpath + '\n')
        yaml_file.close()

    """
    Generate .vscode/launch.json files
    """
    vsc_launch_file = open('.vscode/launch.json', 'w')
    if vsc_launch_file:
        config_obj = {}
        config_obj['name'] = 'Cortex Debug'
        config_obj['cwd'] = '${workspaceFolder}'
        config_obj['executable'] = 'rt-thread.elf'
        config_obj['request'] = 'launch'
        config_obj['type'] = 'cortex-debug'
        config_obj['runToEntryPoint'] = 'Reset_Handler'
        config_obj['servertype'] = 'pyocd'
        if os.getenv('RTT_EXEC_PATH'):
            config_obj['armToolchainPath'] = os.getenv('RTT_EXEC_PATH').replace('\\', '/')
        else:
            print('env <RTT_EXEC_PATH> not set!')
        config_obj['toolchainPrefix'] = 'arm-none-eabi'
        config_obj['targetId'] = targetId

        json_obj = {}
        json_obj['version'] = '0.2.0'
        json_obj['configurations'] = [config_obj]
        vsc_launch_file.write(json.dumps(json_obj, ensure_ascii=False, indent=4))
        vsc_launch_file.close()

    """
    Generate .vscode/tasks.json files
    """
    vsc_tasks_file = open('.vscode/tasks.json', 'w')
    if vsc_tasks_file:
        task_build_obj = {}
        task_build_obj['type'] = 'shell'
        task_build_obj['label'] = 'Build target files'
        task_build_obj['command'] = 'scons'
        task_build_obj['args'] = ['-j12']
        task_build_obj['problemMatcher'] = ['$gcc']
        task_build_obj['group'] = 'build'

        task_download_obj = {}
        task_download_obj['type'] = 'shell'
        task_download_obj['label'] = 'Download code to flash memory'
        task_download_obj['command'] = 'python'
        task_download_obj['args'] = ['-m', 'pyocd', 'flash', '--erase', 'chip', '--target', \
                                    targetId, 'rt-thread.elf']
        task_download_obj['problemMatcher'] = ['$gcc']
        task_download_obj['group'] = 'build'

        task_build_download_obj = task_download_obj.copy()
        task_build_download_obj['label'] = 'Build and Download'
        task_build_download_obj['dependsOn'] = 'Build target files'

        json_obj = {}
        json_obj['version'] = '2.0.0'
        json_obj['tasks'] = [task_build_obj, task_download_obj, task_build_download_obj]
        vsc_tasks_file.write(json.dumps(json_obj, ensure_ascii=False, indent=4))
        vsc_tasks_file.close()

def similar_char_num(str1, str2):
    lstr1 = len(str1)
    lstr2 = len(str2)
    record = [[0 for i in range(lstr2+1)] for j in range(lstr1+1)]
    similar_num = 0

    for i in range(lstr1):
        for j in range(lstr2):
            if str1[i] == str2[j]:
                record[i+1][j+1] = record[i][j] + 1
                if record[i+1][j+1] > similar_num:
                    similar_num = record[i+1][j+1]
    return similar_num

def get_socName_from_rtconfig():
    socName = None
    rtconfig_file = open('rtconfig.h', 'r')
    if rtconfig_file:
        for line in rtconfig_file.readlines():
            if 'SOC' in line and 'FAMILY' not in line and 'SERIES' not in line:
                socName = line.strip().split('_')[-1]
        rtconfig_file.close()
        return socName

def get_pack_from_env():
    if os.environ.get('ENV_ROOT') == None:
        if sys.platform == 'win32':
            home_dir = os.environ['USERPROFILE']
            env_dir  = os.path.join(home_dir, '.env')
        else:
            home_dir = os.environ['HOME']
            env_dir  = os.path.join(home_dir, '.env')
    else:
        env_dir =  os.environ.get('ENV_ROOT')

    pack_dir = env_dir.replace('\\', '/') + '/tools/cmsisPacks/'

    if not os.path.exists(pack_dir):
        print('<%s> does not exist, please create.' % pack_dir)
        return

    # get soc name from <rtconfig.h> file
    socName = get_socName_from_rtconfig()
    if socName == None:
        return

    # Find the pack that best matches soc name
    max_similar_num = 0
    max_similar_pack = None
    for file in os.listdir(pack_dir):
        if str(file).endswith('.pack'):
            similar_num = similar_char_num(socName, file)
            if(similar_num > max_similar_num):
                max_similar_num = similar_num
                max_similar_pack = file
    print('SOC<%s> match the pack is <%s>' % (socName, max_similar_pack))
    if max_similar_pack == None:
        return

    return pack_dir + max_similar_pack

def get_trgetId_from_pack(pack):
    # get soc name from <rtconfig.h> file
    socName = get_socName_from_rtconfig()
    if socName == None:
        return

    # View the soc supported by the most similar cmsisPack
    result = os.popen('python -m pyocd json --target --pack ' + pack)
    pyocd_json = json.loads(result.read())
    if pyocd_json['status'] != 0:
        return

    # Find the targetId that best matches soc name
    max_similar_num = 0
    max_similar_targetId = None
    for target in pyocd_json['targets']:
        if (target['source'] == 'pack'):
            similar_num = similar_char_num(socName.lower(), target['name'])
            if(similar_num > max_similar_num):
                max_similar_num = similar_num
                max_similar_targetId = target['name']
    print('SOC<%s> match the targetId is <%s>' % (socName, max_similar_targetId))
    if max_similar_targetId == None:
        return
    if max_similar_num < len(socName):
        print('<%s> not match the <%s>' % (socName, pack))
        return

    return max_similar_targetId

def GenerateVSCodePyocdConfig(pack):
    if pack == 'env':
        pack = get_pack_from_env()
        if pack == None:
            return
    else:
        # Check is exist
        if not os.path.exists(pack):
            return
        # Check is file
        if not os.path.isfile(pack):
            return
        # Check is pack
        if not str(pack).endswith('.pack'):
            return

    pack = pack.replace('\\', '/')

    targetId = get_trgetId_from_pack(pack)
    if targetId ==None:
        return

    create_need_files(targetId, pack)
    print('Pyocd Config Done!')

    return

