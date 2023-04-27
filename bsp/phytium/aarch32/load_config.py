import os
import shutil
import argparse

parser = argparse.ArgumentParser()
parser.description='please enter parameter <target_platform> '
parser.add_argument("-p", "--platform", help="platform name", type=str, default="")
args = parser.parse_args()

print('=== Loading RT-Thread Config for {} ===='.format(args.platform))

src_path = './configs/rtconfig_{}.h'.format(args.platform)
dst_path = './rtconfig.h'
print(' Copying config from {} to {}'.format(src_path, dst_path))

if os.path.exists(src_path):
    if os.path.exists(dst_path):
        os.remove(dst_path)

    shutil.copyfile(src_path, dst_path)
else:
    print("Target file not found !!!")