
import os
import shutil

out_path='./'
bin_file_name='rtthread.bin'
pack_path='./pack'
out_file='./rtthread_air105'

if __name__=='__main__':
    if os.path.exists(out_file+'.soc'):
        os.remove(out_file+'.soc')
    shutil.copy(out_path+bin_file_name, pack_path+'/'+bin_file_name)
    shutil.make_archive(out_file, 'zip', root_dir=pack_path)
    os.remove(pack_path+'/'+bin_file_name)
    os.rename(out_file+'.zip',out_file+'.soc')
    print('end')
