@echo off

gcc neuralnet.c -o neuralnet.exe -Wall -Wextra -O2

if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b
)

echo Build complete. Running program...
echo.

neuralnet.exe

pause
