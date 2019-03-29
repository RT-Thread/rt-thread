@echo off

@rem if debug_info=1, Debugging Print Information will be turned on
set debug_info=0
@rem if make_fal=1, Partition tables are put into firmware
set make_fal=0
@rem Setting firmware output directory
set out_path=.\Bin
@rem Setting the bin file path
set bin_file=.\rtthread.bin
@rem Setting winnermicro libraries path
set wmlib_path=.\packages\wm_libraries-
@rem Setting the 1M flash layout file
set layout_1M_file=.
@rem Setting the 2M flash layout file
set layout_2M_file=.
@rem Setting the makeimg by adding rtt flash original fls
set makeimg_new_fls=.

if "%wmlib_path:~0,1%" == "." (set wmlib_path=%~dp0%wmlib_path%)
@rem find winnermicro libraries full path
for /f "delims=" %%i in ('dir /ad /b /s %wmlib_path%*') do (set wmlib_path_full=%%i)
@rem Setting the version.txt file path
set version_file=%wmlib_path_full%\Tools\version.txt
@rem Setting the secboot.img file path
set secboot_file=%wmlib_path_full%\Tools\secboot.img
@rem Setting the wm_gzip.exe file path
set wm_gzip_file=%wmlib_path_full%\Tools\wm_gzip.exe
@rem Setting the makeimg.exe file path
set makeimg_file=%wmlib_path_full%\Tools\makeimg.exe
@rem Setting the makeimg_all.exe file path
set makeimg_all_file=%wmlib_path_full%\Tools\makeimg_all.exe

@rem Prepare to generate firmware

@rem Get the full path
if "%out_path:~0,1%" == "." (set out_path=%~dp0%out_path%)
if "%bin_file:~0,1%" == "." (set bin_file=%~dp0%bin_file%)

@rem Create output folder
if not exist "%out_path%" (md "%out_path%")

@rem Copy the required files
if exist "%bin_file%" (copy "%bin_file%" "%out_path%") else (echo makeimg err! No bin file found: %bin_file% & goto end)
if exist "%version_file%" (copy "%version_file%" "%out_path%") else (echo makeimg err! No version file found: %version_file% & goto end)
if exist "%secboot_file%" (copy "%secboot_file%" "%out_path%") else (echo makeimg err! No secboot file found: %secboot_file% & goto end)

@rem Check the existence of firmware generation tools
if not exist "%wm_gzip_file%" (echo makeimg err! No wm_gzip file found: "%wm_gzip_file%" & goto end)
if not exist "%makeimg_file%" (echo makeimg err! No makeimg file found: "%makeimg_file%" & goto end)
if not exist "%makeimg_all_file%" (echo makeimg err! No makeimg_all file found: "%makeimg_all_file%" & goto end)

@rem Get File Names and File Extensions
for /f "delims=" %%A in ('dir /b %bin_file%') do set "bin_file_name=%%A"
for /f "delims=." %%A in ('dir /b %bin_file%') do set bin_name=%%A
for /f "delims=%bin_name%" %%A in ('dir /b %bin_file%') do set bin_extend=%%A
for /f "delims=" %%A in ('dir /b %version_file%') do set "version_file_name=%%A"
for /f "delims=" %%A in ('dir /b %secboot_file%') do set "secboot_file_name=%%A"

@rem Print Debug Information
if not "%debug_info%"=="0" (echo bin_file_name:%bin_file_name% & echo bin_name:%bin_name% & echo bin_extend:%bin_extend% & echo version_file_name:%version_file_name% & echo secboot_file_name:%secboot_file_name%)

echo makeimg 1M Flash...

@rem Start making 1M flash firmware
set file_pos_1M=_1M

@rem Create command parameters
set wm_gzip_cmd="%out_path%\%bin_file_name%"
set makeimg_img_cmd="%out_path%\%bin_file_name%" "%out_path%\%bin_name%%file_pos_1M%.img" 0 0 "%out_path%\%version_file_name%" 90000 10100
set makeimg_gz_img_cmd="%out_path%\%bin_file_name%.gz" "%out_path%\%bin_name%_GZ%file_pos_1M%.img" 0 1 "%out_path%\%version_file_name%" 90000 10100 "%out_path%\%bin_file_name%"
set makeimg_sec_img_cmd="%out_path%\%bin_file_name%" "%out_path%\%bin_name%_SEC%file_pos_1M%.img" 0 0 "%out_path%\%version_file_name%" 90000 10100
set makeimg_all_cmd="%out_path%\%secboot_file_name%" "%out_path%\%bin_name%%file_pos_1M%.img" "%out_path%\%bin_name%%file_pos_1M%.FLS"

@rem Print command Information
if not "%debug_info%"=="0" (echo wm_gzip %wm_gzip_cmd%)
if not "%debug_info%"=="0" (echo makeimg %makeimg_img_cmd%)
if not "%debug_info%"=="0" (echo makeimg %makeimg_gz_img_cmd%)
if not "%debug_info%"=="0" (echo makeimg %makeimg_sec_img_cmd%)
if not "%debug_info%"=="0" (echo makeimg_all %makeimg_all_cmd%)

@rem Execute firmware generation commands
"%wm_gzip_file%" %wm_gzip_cmd%
"%makeimg_file%" %makeimg_img_cmd%
"%makeimg_file%" %makeimg_gz_img_cmd%
"%makeimg_file%" %makeimg_sec_img_cmd%
"%makeimg_all_file%" %makeimg_all_cmd%

@rem Delete temporary files
if exist "%out_path%\%bin_name%%file_pos_1M%.img" (del "%out_path%\%bin_name%%file_pos_1M%.img")
if exist "%out_path%\%bin_file_name%.gz" (del "%out_path%\%bin_file_name%.gz")

@rem Start making 2M flash firmware
echo makeimg 2M Flash...

set file_pos_2M=_2M

@rem Create command parameters
set wm_gzip_cmd="%out_path%\%bin_file_name%"
set makeimg_img_cmd="%out_path%\%bin_file_name%" "%out_path%\%bin_name%%file_pos_2M%.img" 3 0 "%out_path%\%version_file_name%" 100000 10100
set makeimg_gz_img_cmd="%out_path%\%bin_file_name%.gz" "%out_path%\%bin_name%_GZ%file_pos_2M%.img" 3 1 "%out_path%\%version_file_name%" 100000 10100 "%out_path%\%bin_file_name%"
set makeimg_sec_img_cmd="%out_path%\%bin_file_name%" "%out_path%\%bin_name%_SEC%file_pos_2M%.img" 3 0 "%out_path%\%version_file_name%" 100000 10100
set makeimg_all_cmd="%out_path%\%secboot_file_name%" "%out_path%\%bin_name%%file_pos_2M%.img" "%out_path%\%bin_name%%file_pos_2M%.FLS"

@rem Print command Information
if not "%debug_info%"=="0" (echo wm_gzip %wm_gzip_cmd%)
if not "%debug_info%"=="0" (echo makeimg %makeimg_img_cmd%)
if not "%debug_info%"=="0" (echo makeimg %makeimg_gz_img_cmd%)
if not "%debug_info%"=="0" (echo makeimg %makeimg_sec_img_cmd%)
if not "%debug_info%"=="0" (echo makeimg_all %makeimg_all_cmd%)

@rem Execute firmware generation commands
"%wm_gzip_file%" %wm_gzip_cmd%
"%makeimg_file%" %makeimg_img_cmd%
"%makeimg_file%" %makeimg_gz_img_cmd%
"%makeimg_file%" %makeimg_sec_img_cmd%
"%makeimg_all_file%" %makeimg_all_cmd%

@rem Delete temporary files
if exist "%out_path%\%bin_name%%file_pos_2M%.img" (del "%out_path%\%bin_name%%file_pos_2M%.img")
if exist "%out_path%\%bin_file_name%.gz" (del "%out_path%\%bin_file_name%.gz")

@rem Partition tables are put into firmware 
if not "%make_fal%"=="1" ( goto end)

@rem Get the full path
if "%layout_1M_file:~0,1%" == "." (set layout_1M_file=%~dp0%layout_1M_file%)
if "%layout_2M_file:~0,1%" == "." (set layout_2M_file=%~dp0%layout_2M_file%)
if "%makeimg_new_fls:~0,1%" == "." (set makeimg_new_fls=%~dp0%makeimg_new_fls%)

@rem Check whether the file exists
if not exist "%layout_1M_file%" (echo makeimg err! No makeimg file found: "%layout_1M_file%" & goto end)
if not exist "%layout_2M_file%" (echo makeimg err! No makeimg file found: "%layout_2M_file%" & goto end)
if not exist "%makeimg_new_fls%" (echo makeimg err! No makeimg file found: "%makeimg_new_fls%" & goto end)

@rem Create command parameters to new fls
set makeimg_new_cmd_1M="%out_path%\%bin_name%%file_pos_1M%.FLS" "%layout_1M_file%" "%out_path%\%bin_name%_layout%file_pos_1M%.FLS"
@rem Execute generation fls cmd
"%makeimg_new_fls%" %makeimg_new_cmd_1M%

@rem Create command parameters to new fls
set makeimg_new_cmd_2M="%out_path%\%bin_name%%file_pos_2M%.FLS" "%layout_2M_file%" "%out_path%\%bin_name%_layout%file_pos_2M%.FLS"
@rem Execute generation fls cmd
"%makeimg_new_fls%" %makeimg_new_cmd_2M%

@rem Delete temporary files
if exist "%out_path%\%bin_name%_1M.FLS" (del "%out_path%\%bin_name%%file_pos_1M%.FLS")
if exist "%out_path%\%bin_name%_2M.FLS" (del "%out_path%\%bin_name%%file_pos_2M%.FLS")

:end
echo end

