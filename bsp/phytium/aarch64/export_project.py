import os
import shutil

print('=== Exporting Phytium BSP for RT-Studio ====')

board_src_path = os.path.abspath(r'../board')
librs_src_path = os.path.abspath(r'../libraries')
app_src_path = os.path.abspath(r'../applications')

board_dst_path = os.path.abspath(r'./board')
librs_dst_path = os.path.abspath(r'./libraries')
app_dst_path = os.path.abspath(r'./applications')

print(' Copying BSP board from {} to {}'.format(board_src_path, board_dst_path))
print(' Copying BSP libraries from {} to {}'.format(librs_src_path, librs_dst_path))

if os.path.exists(board_dst_path):
    shutil.rmtree(board_dst_path)

if os.path.exists(librs_dst_path):
    shutil.rmtree(librs_dst_path)

if os.path.exists(app_dst_path):
    shutil.rmtree(app_dst_path)

shutil.copytree(board_src_path, board_dst_path)
shutil.copytree(librs_src_path, librs_dst_path)
shutil.copytree(app_src_path, app_dst_path)

os.system(r'scons --dist-ide --project-name=phytium-a64 --project-path=./phytium-a64')

if os.path.exists(board_dst_path):
    shutil.rmtree(board_dst_path)

if os.path.exists(librs_dst_path):
    shutil.rmtree(librs_dst_path)

if os.path.exists(app_dst_path):
    shutil.rmtree(app_dst_path)