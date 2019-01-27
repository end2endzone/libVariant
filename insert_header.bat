@echo off

call :INSERT %~dp0libVariant\dllmain.cpp
call :INSERT %~dp0libVariant\FloatLimits.h
call :INSERT %~dp0libVariant\libVariantApi.h
call :INSERT %~dp0libVariant\StringEncoder.h
call :INSERT %~dp0libVariant\StringParser.h
call :INSERT %~dp0libVariant\targetver.h
call :INSERT %~dp0libVariant\TypeCast.h
call :INSERT %~dp0libVariant\TypeInfo.h
call :INSERT %~dp0libVariant\TypeUnion.h
call :INSERT %~dp0libVariant\Variant.cpp
call :INSERT %~dp0libVariant\Variant.h
call :INSERT %~dp0libVariant\VariantTemplates.h

call :INSERT %~dp0libVariantTests\gtesthelper.cpp
call :INSERT %~dp0libVariantTests\gtesthelper.h
call :INSERT %~dp0libVariantTests\main.cpp
call :INSERT %~dp0libVariantTests\targetver.h
call :INSERT %~dp0libVariantTests\TestFloatLimits.cpp
call :INSERT %~dp0libVariantTests\TestFloatLimits.h
call :INSERT %~dp0libVariantTests\TestStringEncoder.cpp
call :INSERT %~dp0libVariantTests\TestStringEncoder.h
call :INSERT %~dp0libVariantTests\TestTypeCastSaturation.cpp
call :INSERT %~dp0libVariantTests\TestTypeCastSaturation.h
call :INSERT %~dp0libVariantTests\TestTypeInfo.cpp
call :INSERT %~dp0libVariantTests\TestTypeInfo.h
call :INSERT %~dp0libVariantTests\TestTypeUnion.cpp
call :INSERT %~dp0libVariantTests\TestTypeUnion.h
call :INSERT %~dp0libVariantTests\TestVariant.cpp
call :INSERT %~dp0libVariantTests\TestVariant.h
call :INSERT %~dp0libVariantTests\TestVariantTemplate.cpp
call :INSERT %~dp0libVariantTests\TestVariantTemplate.h


pause


GOTO :EOF


:INSERT
REM %1 is the file path to add the header
echo Processing file %1...
move /y "%~1" "%~1.tmp" >NUL
type %~dp0copyright.txt>"%~1"
type "%~1.tmp">>"%~1"
del "%~1.tmp" >NUL

:EOF
