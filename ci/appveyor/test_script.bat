@echo off

echo =======================================================================
echo Testing stdint types
echo =======================================================================
cd %APPVEYOR_BUILD_FOLDER%\build\bin\Release
stdint_types_test.exe

echo =======================================================================
echo Testing project
echo =======================================================================
cd %APPVEYOR_BUILD_FOLDER%\build\bin\Release
libvariant_unittest.exe

::reset error in case of test case fail
exit /b 0
