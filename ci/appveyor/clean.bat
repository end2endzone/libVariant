@echo off

:: Validate appveyor's environment
if "%APPVEYOR_BUILD_FOLDER%"=="" (
  echo Please define 'APPVEYOR_BUILD_FOLDER' environment variable.
  exit /B 1
)

cd /d %APPVEYOR_BUILD_FOLDER%

echo Deleting 'build' directory...
if exist "%APPVEYOR_BUILD_FOLDER%\build" rmdir /S /Q "%APPVEYOR_BUILD_FOLDER%\build"
if %errorlevel% neq 0 exit /b %errorlevel%
echo done.
echo.

echo Deleting 'third_parties' directory...
if exist "%APPVEYOR_BUILD_FOLDER%\third_parties" rmdir /S /Q "%APPVEYOR_BUILD_FOLDER%\third_parties"
if %errorlevel% neq 0 exit /b %errorlevel%
echo done.
echo.

::Return to launch folder
cd /d %~dp0
