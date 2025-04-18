import os
import rtconfig
import platform
import subprocess

def generate_ldscript(input, output):

    if not os.path.exists(input):
        print('Error: file', input, 'not found')
        return

    if os.path.exists(output):
        os.remove(output)

    if rtconfig.PLATFORM == 'gcc':

        gcc_cmd = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)

        # gcc -E -P -x c $input -o $output
        if (platform.system() == 'Windows'):
            child = subprocess.Popen([gcc_cmd, '-E', '-P', '-x', 'c', input, '-o', output], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        else:
            child = subprocess.Popen(gcc_cmd + f' -E -P -x c {input} -o {output}', stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

        child.communicate()

        print(output, 'is generated from', input)
