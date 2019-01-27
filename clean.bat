@echo off
del .\libVariant\*.user
del .\libVariantTests\*.user
del .\*.ncb
attrib -h -r -s *.suo
del .\*.suo
rmdir /Q /S .\libVariant\Win32
rmdir /Q /S .\libVariant\x64
rmdir /Q /S .\libVariantCodeGenerator\Win32
rmdir /Q /S .\libVariantCodeGenerator\x64
rmdir /Q /S .\libVariantTests\Win32
rmdir /Q /S .\libVariantTests\x64
rmdir /Q /S .\Win32
rmdir /Q /S .\x64
rmdir /Q /S .\ipch
pause
