py -3 nuwriter.py -c header-nand.json
py -3 nuwriter.py -p pack-nand.json

py -3 nuwriter.py -a ddrimg\enc_ddr3_winbond_512mb.bin
IF %ERRORLEVEL% EQU 0 (
    py -3 nuwriter.py -w spinand pack/pack.bin
)
PAUSE