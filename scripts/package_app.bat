@echo off
echo Packaging KT Browser into Standalone Distribution...

pyinstaller --onedir --noconsole --name "ktbrowser" --icon "ktbrowser.ico" ktbrowser_qt6.py

if %ERRORLEVEL% equ 0 (
    echo Package build complete! Executable is located in dist/ktbrowser/ktbrowser.exe
) else (
    echo Packaging failed! Ensure pyinstaller is installed via pip install pyinstaller.
)
