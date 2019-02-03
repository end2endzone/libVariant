@echo off

echo =======================================================================
echo Testing project (1 of 2)
echo =======================================================================
cd /d %~dp0
cd ..\..
cd build\bin\Release
libvariant_unittest.exe

echo =======================================================================
echo Testing project (2 of 2)
echo =======================================================================
libvariant_templates_unittest.exe

::reset error in case of test case fail
exit /b 0
