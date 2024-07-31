@echo off
cls

echo SCFW MPAC rom packing tool by OmDRetro
echo.
echo Generate an MPAC album for MPA2 (*.MPAC)
echo.

setlocal enabledelayedexpansion

set "input_dir=Input"


set "MPAConcat=.\bin\MPAHeaderConcatenator.exe"
set "MPACgen=.\bin\MPAC-Packer.exe"

if not exist "%MPAConcat%" (
	echo. %MPAConcat% is missing
	pause
	goto exit
)

if not exist "%MPACgen%" (
	echo. %MPACgen% is missing
	pause
	goto exit
)

start "" "%MPAConcat%"
call "%MPAConcat%"

echo DONE!

start "" "%MPACgen%"
call "%MPACgen%"


:exit
echo.
echo The ALBUM.MPAC ROM is compiled in the Output folder
pause
