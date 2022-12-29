# **nuwriter_scripts**

Some scripts can help you program firmware into storages in this folder.

## **Requirement**

### [Python3 for Window](https://www.python.org/downloads/windows/)

After installing Python3, some plug-in as below must be installed.

```bash
pip3 install pyusb usb crypto ecdsa crcmod tqdm pycryptodome
```

Notice:

- Tested python3 version is 3.10.1.
- Please remember to add Python to PATH environment variable.

### [Libusb for Window](http://sourceforge.net/projects/libusb/files/libusb-1.0/libusb-1.0.20/libusb-1.0.20.7z/download)

On Windows platform, it is required to install libusb manually.

```bash
Step 1: Download the library extract the download file.
Step 2: Copy MS64\dll\libusb-1.0.dll to C:\Windows\System32.
Step 3: Copy MS64\dll\libusb-1.0.lib to C:\Users\<user name>\AppData\Local\Programs\Python\<python ver>\Lib.
```

### [USB Driver for Window](https://github.com/OpenNuvoton/MA35D1_NuWriter/blob/master/driver/WinUSB4NuVCOM.exe?raw=true)

NuWriter must install **WinUSB4NuVCOM.exe** on the computer.

## **Double-click Scripts for Windows**

If your NuWriter_MA35 python running is ready, you can do following batch script files for Window directly.

### **nuwriter_ddr_download_and_run.bat**

Download rtthread.bin binary file into DDR. The address is 0x80400000.

### **nuwriter_sd_programming.bat**

Program header, DDR timing setting and rtthread.bin binary file into SD card or EMMC.

### **nuwriter_spinand_programming.bat**

Program header, DDR timing setting and rtthread.bin binary file into SPI NAND flash.

### **nuwriter_nand_programming.bat**

Program header, DDR timing setting and rtthread.bin binary file into NAND flash.


## **Bash Scripts for Linux**

If your NuWriter_MA35 python running is ready, you can do following bash script files for Linux directly.
If not, the **install_linux.sh** will help user to install related python module installation.

```bash
# ./install_linux.sh
```

### **nuwriter_ddr_download_and_run.sh**

Download rtthread.bin binary file into DDR. The address is 0x80400000.

### **nuwriter_sd_programming.sh**

Program header, DDR timing setting and rtthread.bin binary file into SD card or EMMC.

### **nuwriter_spinand_programming.sh**

Program header, DDR timing setting and rtthread.bin binary file into SPI NAND flash.

### **nuwriter_nand_programming.sh**

Program header, DDR timing setting and rtthread.bin binary file into NAND flash.


## **Troubleshoot**

### **Fail to create symbolic folder**

```bash
Create symbolic folder conv failed
```

- To switch **Developer Mode** in Window. To enter [Settings], [Update & Security], [For developers], [Developer Mode] page, then set it **On**
- Use **Administrator** permission to install python3, libusb and utilities.

### **Use NuWriter_MA35.exe**

Due to the python execution file size and saving network bandwidth, we just only release the python code in this repository. We also provide [NuWriter_MA35.exe](https://github.com/OpenNuvoton/MA35D1_NuWriter/blob/master/EXE/NuWriter_MA35.exe?raw=true) python execution. You can run the packaged app without installing a Python interpreter or any modules. You can use **NuWriter_MA35.exe** and do some modification.

```bash
To modify "py -3 nuwriter.py" to "NuWriter_MA35.exe"
```

For example, the **nuwriter_ddr_download_and_run.bat** modification is as following:

```bash
:forever_develop
NuWriter_MA35.exe -a ddrimg\enc_ddr3_winbond_256mb.bin
IF %ERRORLEVEL% EQU 0 (
   NuWriter_MA35.exe -o execute -w ddr 0x80400000 ..\rtthread.bin
)
pause
goto :forever_develop
```

## **See also**

[NuWriter Repository](https://github.com/OpenNuvoton/MA35D1_NuWriter)
