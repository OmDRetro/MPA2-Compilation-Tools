@echo off
cls

echo Bulk audio file conversion kit by OmDRetro
echo.
echo Converting files to 16 bit PCM
echo.

setlocal enabledelayedexpansion

set "input_dir=Input"
set "output_dir=Output"
set "ffmpeg_path=.\bin\ffmpeg.exe"

if not exist "%input_dir%" mkdir "%input_dir%"
if not exist "%output_dir%" mkdir "%output_dir%"

for %%f in ("%input_dir%\.aac" "%input_dir%\.ac3" "%input_dir%\.ac4" "%input_dir%\.alaw" "%input_dir%\.amr" "%input_dir%\.ape" "%input_dir%\.aptx" "%input_dir%\.awb" "%input_dir%\.caf" "%input_dir%\.dts" "%input_dir%\.dtshd" "%input_dir%\.eac3" "%input_dir%\.flac" "%input_dir%\.gsm" "%input_dir%\.m4a" "%input_dir%\.mlp" "%input_dir%\.mp1" "%input_dir%\.mp2" "%input_dir%\.mp3" "%input_dir%\.mp4" "%input_dir%\.mpc" "%input_dir%\.mulaw" "%input_dir%\.ogg" "%input_dir%\.oma" "%input_dir%\.opus" "%input_dir%\.wav" "%input_dir%\.wv") do (
    set "file_name=%%~nf"  REM Corrected line: use %%~nf to get the file name without extension
    set "file_ext=%%~xf"

    echo.Converting "%%f"
	echo.
	echo Please select the bitrate quality
	echo   1 : 16000 ~ Highest quality audio
	echo   2 : 11025 ~ Medium quality audio
	echo   3 : 8000 ~ Lowest quality audio
	echo.
	echo.
	echo. If your input is not from the choices, this application will quit.
	echo.
    set /p "choice= Please enter your choice: "
    if !choice! equ 1 set bitrate=16000
    if !choice! equ 2 set bitrate=11025
    if !choice! equ 3 set bitrate=8000
    if not !choice! equ 1 if not !choice! equ 2 if not !choice! equ 3 goto exit

    set "output_file=%output_dir%\!file_name!.pcm"  REM Corrected line: use !file_name! to access the variable
    echo Output dir: %output_dir%
    echo File name: !file_name!
    echo Output file: !output_file!

    %ffmpeg_path% -y -i "%%f" -acodec pcm_s16le -f s16le -ac 1 -ar !bitrate! "!output_file!"
	
	cls
)

echo.
echo Complete.
