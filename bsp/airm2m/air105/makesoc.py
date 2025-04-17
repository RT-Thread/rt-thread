import os
import sys
import shutil
import urllib.request
out_path='./'
bin_file_name='rtthread.bin'
pack_path='./pack'
out_file='./rtthread_air105'

cwd_path = os.getcwd()
if __name__=='__main__':
    
    print(cwd_path)
    if os.path.exists(out_file+'.soc'):
        os.remove(out_file+'.soc')

    if not os.path.exists(pack_path+'/bootloader.bin'):
        urllib.request.urlretrieve("http://cdndownload.openluat.com/rt-thread/airm2m/air105/bootloader.bin", pack_path + '/bootloader.bin')

    if not os.path.exists(pack_path+'/soc_download.exe'):
        urllib.request.urlretrieve("http://cdndownload.openluat.com/rt-thread/airm2m/air105/bootloader.bin", pack_path + '/bootloader.bin')

    shutil.copy(out_path+bin_file_name, pack_path+'/'+bin_file_name)
    shutil.make_archive(out_file, 'zip', root_dir=pack_path)
    os.remove(pack_path+'/'+bin_file_name)
    os.rename(out_file+'.zip',out_file+'.soc')

    print('end')
