@echo off

cd Install

set ROOTPATH=C:\devkitpro
set LIBPATH=%ROOTPATH%\libnds\lib
set INCPATH=%ROOTPATH%\libnds\include
set VHAMPATH=%ROOTPATH%\PAlib\vham\templates\project

echo Please verify that those paths are correct.

echo Libnds directory: %ROOTPATH%
echo Include directory: %INCPATH%
echo Library directory: %LIBPATH%

echo If they are not, please close this window now and edit this bat file to set up the correct paths.
echo If they are correct, press any key to continue.

pause

set INCPATH=%INCPATH%\ulib\

echo Copying header files...

md %INCPATH%

copy drawing.h %INCPATH%
copy glWrapper.h %INCPATH%
copy keys.h %INCPATH%
copy loading_utility.h %INCPATH%
copy map.h %INCPATH%
copy messagebox.h %INCPATH%
copy text.h %INCPATH%
copy ulib.h %INCPATH%
copy VirtualFile.h %INCPATH%

echo Copying libraries...

copy libpng.a %LIBPATH%
copy libz.a %LIBPATH%
copy libul.a %LIBPATH%


echo Copy terminated!
echo Do you want to create Visual HAM templates for uLibrary?
echo If you don't, please close this window.
echo Else, please verify that it's the right VHAM template path:
echo %VHAMPATH%
pause

cd ..
xcopy /E /I Templates %VHAMPATH%

echo Installation terminated!
pause
