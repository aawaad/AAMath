call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64

REM cl %1

IF NOT EXIST build mkdir build
pushd build
cl -Oi -EHa- -WX -W4 -wd4201 -wd4100 -wd4189 /FC /Z7 /nologo ..\src\main.cpp
popd
