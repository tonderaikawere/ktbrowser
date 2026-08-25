@echo off
echo ===================================================
echo Building CodeBrowser Native Windows Executable
echo ===================================================

if not exist build mkdir build
cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
if %ERRORLEVEL% neq 0 (
    echo CMake Configuration failed!
    exit /b %ERRORLEVEL%
)

cmake --build . --config Release
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

echo Running Unit Tests...
ctest --output-on-failure

echo ===================================================
echo CodeBrowser built successfully! Executable in build/
echo ===================================================
cd ..
