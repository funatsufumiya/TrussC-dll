@echo off
REM =============================================================================
REM TrussC Project Generator Build Script (Windows)
REM =============================================================================
REM Run this script to build projectGenerator
REM =============================================================================

echo ==========================================
echo   TrussC Project Generator Build Script
echo ==========================================
echo.

REM Move to script directory
cd /d "%~dp0"
set SCRIPT_DIR=%cd%

REM Source directory
set SOURCE_DIR=%SCRIPT_DIR%\tools\projectGenerator

REM Create build folder
if not exist "%SOURCE_DIR%\build" (
    echo Creating build directory...
    mkdir "%SOURCE_DIR%\build"
)

cd /d "%SOURCE_DIR%\build"

REM Setup Visual Studio environment
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath`) do set VS_PATH=%%i
if defined VS_PATH call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x64

REM CMake configuration
echo Running CMake...
cmake ..
if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo Please make sure CMake is installed and in your PATH.
    echo.
    pause
    exit /b 1
)

REM Build
echo.
echo Building...
cmake --build . --config Release --parallel
if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Build failed!
    echo.
    pause
    exit /b 1
)

REM Create symlink to binary in distribution folder (requires admin or Developer Mode)
echo.
echo Creating symlink to distribution folder...
if exist "%SCRIPT_DIR%\projectGenerator.exe" del "%SCRIPT_DIR%\projectGenerator.exe"
mklink "%SCRIPT_DIR%\projectGenerator.exe" "%SOURCE_DIR%\bin\projectGenerator.exe"
if %ERRORLEVEL% neq 0 (
    echo Symlink failed, falling back to copy...
    copy /Y "%SOURCE_DIR%\bin\projectGenerator.exe" "%SCRIPT_DIR%\"
)

copy /Y "%SOURCE_DIR%\..\..\..\trussc\build-windows\Release\TrussC.dll" "%SOURCE_DIR%\bin\TrussC.dll"
copy /Y "%SOURCE_DIR%\..\..\..\trussc\build-windows\Release\TrussC.dll" "%SCRIPT_DIR%\TrussC.dll"

echo.
echo ==========================================
echo   Build completed successfully!
echo ==========================================
echo.
echo Launching projectGenerator...
start "" "%SCRIPT_DIR%\projectGenerator.exe"
