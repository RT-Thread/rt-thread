py -3 nuwriter.py -c header-sram-leave_ibr.json
IF %ERRORLEVEL% EQU 0 (
    py -3 nuwriter.py -p pack-sd-leave_ibr.json -o stuff
)
pause