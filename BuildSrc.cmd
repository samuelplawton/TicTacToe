@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem ===== Auto settings =====
for %%D in ("%CD%") do set "APP_NAME=%%~nD"   rem exe name = repo folder
set "SRC_DIR=src"
set "OUT_DIR=build"
set "STD=c++17"

if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

rem Collect sources
set "CPP_LIST="
for /f "delims=" %%F in ('dir /s /b "%SRC_DIR%\*.cpp" 2^>nul') do set "CPP_LIST=!CPP_LIST! "%%~fF""
if "%CPP_LIST%"=="" (
  echo No .cpp files found under "%SRC_DIR%".
  pause
  exit /b 1
)

rem Prefer CMake if present
if exist "CMakeLists.txt" (
  echo [CMake] Configuring and building...
  cmake -S . -B "%OUT_DIR%" -DCMAKE_BUILD_TYPE=Release || goto :fail
  cmake --build "%OUT_DIR%" --config Release || goto :fail
  rem Copy most recent exe to standard name
  for /f "delims=" %%E in ('powershell -NoP -C "Get-ChildItem -Recurse -File \"%OUT_DIR%\" -Filter *.exe ^| Sort-Object LastWriteTime -Desc ^| Select-Object -First 1 -Expand FullName"') do (
    copy /y "%%~fE" "%OUT_DIR%\%APP_NAME%.exe" >nul 2>nul
  )
  if exist "%OUT_DIR%\%APP_NAME%.exe" goto :ok
)

rem Try MSVC cl.exe
where cl >nul 2>nul
if %ERRORLEVEL%==0 (
  echo [MSVC] Building with cl.exe...
  pushd "%OUT_DIR%"
  cl /std:%STD% /O2 /W4 /EHsc %CPP_LIST% /Fe:"%APP_NAME%.exe" || (popd & goto :fail)
  popd
  goto :ok
)

rem Try MinGW g++
where g++ >nul 2>nul
if %ERRORLEVEL%==0 (
  echo [g++] Building with MinGW...
  g++ -std=%STD% -O2 -Wall -Wextra -Wpedantic %CPP_LIST% -o "%OUT_DIR%\%APP_NAME%.exe" || goto :fail
  goto :ok
)

echo No compiler found. Use "x64 Native Tools Command Prompt for VS" (MSVC) or install MinGW-w64.
goto :fail

:ok
echo.
echo ✅ Built "%CD%\%OUT_DIR%\%APP_NAME%.exe"
exit /b 0

:fail
echo.
echo ❌ Build failed.
pause
exit /b 1
