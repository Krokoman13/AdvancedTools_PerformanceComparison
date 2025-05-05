@echo off
setlocal enabledelayedexpansion

:: Get full path and folder name
set "baseDir=%~dp0"
for %%A in ("%baseDir:~0,-1%") do set "parentName=%%~nxA"

:: For each subfolder in the current directory
for /d %%F in (*) do (
    if exist "%%F\*.csv" (
        set "folderName=%%F"
        set "outputFile=%baseDir%!parentName!_%%F.csv"
        del "!outputFile!" 2>nul

        set "first=1"
        for %%C in ("%baseDir%%%F\*.csv") do (
            set "csvPath=%%~fC"
            if !first! equ 1 (
                copy /b "!csvPath!" "!outputFile!" >nul
                set "first=0"
            ) else (
                powershell -NoProfile -Command ^
                "$a = Get-Content -LiteralPath '!outputFile!';" ^
                "$b = Get-Content -LiteralPath '!csvPath!';" ^
                "$max = [Math]::Max($a.Count, $b.Count);" ^
                "$out = for ($i = 0; $i -lt $max; $i++) { ($a[$i] + '') + ',' + ($b[$i] + '') };" ^
                "$out | Set-Content -LiteralPath '!outputFile!'"
            )
        )
    )
)

echo Done!
pause
