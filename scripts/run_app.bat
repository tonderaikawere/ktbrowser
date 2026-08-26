@echo off
echo Launching KT Browser...

python -c "import PyQt6" >nul 2>&1
if %ERRORLEVEL% equ 0 (
    echo Launching Python KT Browser (PyQt6 WebEngine)...
    python ktbrowser_qt6.py
) else (
    echo Building & Launching Native C++ Executable...
    call scripts\build_direct.bat
)
