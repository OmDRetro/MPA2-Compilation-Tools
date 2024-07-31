@echo off
cls

echo Bulk audio file conversion kit by OmDRetro
echo.
echo Generate Headers for pre-packing (*.hdat)
echo.

setlocal enabledelayedexpansion

set "input_dir=Input"

set "MPAhGen=.\bin\MPAhGen.exe"

if not exist "%input_dir%" mkdir "%input_dir%"

for %%f in ("%input_dir%\*.mpa") do (
    set "file_name=%%~nf"
    set "file_ext=%%~xf"

    echo.Generating header "%%f"

    %MPAhGen% "%%f"
	
	cls
)

echo.
echo Step 3a is complete. Please execute Step 3b after closing this window.
pause
