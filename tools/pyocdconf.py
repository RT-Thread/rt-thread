import os
import json

def get_continue_same_char_num(s1, s2):
    num = 0
    len_s1 = len(s1)
    list_s1 = []
    for i in range(len_s1):
        two_s1 = s1[0:i+1]
        list_s1.append(two_s1)
    for i in list_s1:
        if s2.startswith(i) and len(i) > num:
            num = len(i)
    return num

def get_value_from_launch(key):
    launch_path = '.vscode/launch.json'

    if os.path.exists(launch_path):
        launch_file = open(launch_path, 'r')
        if launch_file:
            launch_json = json.loads(launch_file.read())

            if launch_json.get('configurations') == None:
                return
            if len(launch_json.get('configurations')) == 0:
                return
            launch_file.close()

            return launch_json.get('configurations')[0].get(key)
        return
    return

def get_cmsisPack_targetId():
    # where cmsisPack is located
    cmsispack_path = get_value_from_launch('cmsisPack')
    if cmsispack_path == None:
        cmsispack_path = input("Please enter the path of cmsisPack : ")
    # Check whether the path to cmsisPack exists
    if not os.path.exists(cmsispack_path):
        print("Path error, cmsisPack does not exist.")
        return (None, None)

    # Get soc series
    soc_series = get_value_from_launch('targetId')
    if soc_series == None:
        soc_series = input("Please enter the soc series : ")

    # View the targetId supported by cmsisPack
    result = os.popen('python -m pyocd json --target --pack ' + cmsispack_path)
    pyocd_json = json.loads(result.read())
    if pyocd_json['status'] != 0:
        print("get targetId list failed.")
        return (None, None)

    # Finds the targetId closest to the input and supported by cmsisPack
    same_char_num_max = 0
    best_soc_series = None
    for target in pyocd_json['targets']:
        if (target['source'] == 'pack'):
            if (same_char_num_max < get_continue_same_char_num(target['name'], soc_series)):
                same_char_num_max = get_continue_same_char_num(target['name'], soc_series)
                best_soc_series = target['name']

    return (cmsispack_path, best_soc_series)
