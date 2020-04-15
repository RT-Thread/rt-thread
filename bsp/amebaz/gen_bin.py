import re
import subprocess
import os
import platform

#tool_pwd=os.path.normpath(os.getcwd()+r'/packages/realtek_ameba/sdk-ameba-v4.0b_without_NDA_GCC_V1.0.0/component/soc/realtek/8711b/misc/iar_utility/common/tools')

pwd=[]
def findfile(path,filename):
    for x in os.listdir(path):
    	if x=='8195a':
    		continue
        x=os.path.join(path,x)
        if os.path.isdir(x):
            findfile(x,filename)
        else:
            if filename in os.path.split(x)[1]:
                pwd.append(os.path.split(x)[0])
                break
    return

findfile(os.path.abspath('.'),'pick.exe')
if pwd:
	print(pwd[0])

tool_pwd=str(pwd[0])

def grep_func(file,str):
	fd=open(file,'r')
	strtmp=r'^[0-9]{8}\s[a-zA-Z]{1}\s%s$' % str
	for line in fd.readlines():
		if re.match(strtmp,line):
			#print(line)
			value=re.split(r'[\s+]+',line)
			fd.close()
			return value[0]
	fd.close()

#=====================start=======================

os.system(r'arm-none-eabi-objdump -d rtthread.axf > application.asm')
os.system(r'arm-none-eabi-size rtthread.axf')
os.system(r'arm-none-eabi-nm rtthread.axf | sort > application.nmap')

#====================process=====================

addr1=grep_func(r'application.nmap','__ram_image2_text_start__')
addr2=grep_func(r'application.nmap','__ram_image2_text_end__')
addr3=grep_func(r'application.nmap','__ram_image2_text_start__')
addr4=grep_func(r'application.nmap','__ram_image2_text_end__')
addr5=grep_func(r'application.nmap','__xip_image2_start__')
addr6=grep_func(r'application.nmap','__xip_image2_start__')

sysstr = platform.system()
print(sysstr)
if(sysstr == "Linux"):
	exec_pick=os.path.join(tool_pwd,'pick')
	exec_checksum=os.path.join(tool_pwd,'checksum')
	os.system('chmod +x ' + exec_pick)
	os.system('chmod +x ' + exec_checksum)
	#print(exec_pick)
elif(sysstr == "Windows"):
	exec_pick=os.path.join(tool_pwd,'pick.exe')
	exec_checksum=os.path.join(tool_pwd,'checksum.exe')
	#print(exec_pick)
else:
	print("not support!!!")

exec_pick_param1=r' 0x%s 0x%s ram_2.r.bin ram_2.bin raw' % (addr1,addr2)
exec_pick_param2=r' 0x%s 0x%s ram_2.bin ram_2.p.bin' % (addr3,addr4)
exec_pick_param3=r' 0x%s 0x%s xip_image2.bin xip_image2.p.bin' % (addr5,addr6)
#print(exec_pick_param1)
#print(exec_pick_param2)
#print(exec_pick_param3)

exec_cmd1=exec_pick+exec_pick_param1
exec_cmd2=exec_pick+exec_pick_param2
exec_cmd3=exec_pick+exec_pick_param3
#print(exec_cmd1)
#print(exec_cmd2)
#print(exec_cmd3)

os.system(exec_cmd1)
os.system(exec_cmd2)
os.system(exec_cmd3)

#================create bin file================

if os.path.exists('image2_all_ota1.bin'):
	os.remove('image2_all_ota1.bin')

with open('xip_image2.p.bin','rb') as src:
	with open('image2_all_ota1.bin', 'wb') as dst:
    		dst.write(src.read())

with open('ram_2.p.bin','rb') as src:
	with open('image2_all_ota1.bin', 'ab') as dst:
    		dst.write(src.read())

exec_cmd4 = exec_checksum + ' image2_all_ota1.bin || true'
os.system(exec_cmd4)

os.remove("ram_2.bin")
os.remove("ram_2.p.bin")
os.remove("ram_2.r.bin")
os.remove("xip_image2.bin")
os.remove("xip_image2.p.bin")
os.remove("rdp.bin")

print("Done...")

#=====================end=======================