@echo off
setlocal enabledelayedexpansion

REM Get the current script's folder
set "scriptDir=%~dp0"

REM Remove trailing backslash
set "scriptDir=%scriptDir:~0,-1%"

REM Get parent and grandparent folder names
for %%a in ("%scriptDir%") do (
    for %%b in ("%%~dpa.") do (
        set "parent=%%~nxa"
    )
)

REM Create a temporary folder to hold column files
set "tempdir=%~dp0temp_cols"
mkdir "%tempdir%" 2>nul

set /a colNum=0

REM Loop through each CSV and extract first column with filename as header
for %%f in (*.csv) do (
    set /a colNum+=1
    set "filename=%%~nf"
    set "outfile=%tempdir%\col!colNum!.txt"

    > "!outfile!" (
        echo !filename!
        for /f "usebackq tokens=1 delims=," %%a in ("%%f") do (
            echo %%a
        )
    )
)

REM Determine the max number of lines among all column files
set maxLines=0
for %%f in (%tempdir%\col*.txt) do (
    set /a lines=0
    for /f %%l in (%%f) do set /a lines+=1
    if !lines! gtr !maxLines! set maxLines=!lines!
)

REM Combine columns horizontally
set "outFile=%~dp0%parent%.csv"
del "%outFile%" 2>nul

(
for /l %%i in (1,1,!maxLines!) do (
    set "row="
    for /l %%j in (1,1,!colNum!) do (
        set "cell="
        for /f "tokens=*" %%c in ('more +%%i "%tempdir%\col%%j.txt" ^| findstr /n "^" ^| findstr "^1:"') do (
            set "cell=%%c"
            set "cell=!cell:*:=!"
        )
        if defined row (
            set "row=!row!,!cell!"
        ) else (
            set "row=!cell!"
        )
    )
    echo(!row!
)
) > "%outFile%"

REM Cleanup
rd /s /q "%tempdir%"

echo Done! Combined CSV created as %parent%.csv"
pause
