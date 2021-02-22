del %~dp0build /f/s/q/a
del %~dp0bin /f/s/q/a

if not exist bin mkdir bin

if not exist build mkdir build
cd build
if not exist vc16 mkdir vc16
cd vc16

conan install ..\..\  -g cmake_multi  -s compiler="Visual Studio" -s compiler.version=16 -s arch=x86_64 -s build_type=Debug
if %errorlevel% neq 0 exit
conan install ..\..\  -g cmake_multi  -s compiler="Visual Studio" -s compiler.version=16 -s arch=x86_64 -s build_type=Release
if %errorlevel% neq 0 exit

cmake ../../ -G "Visual Studio 16 2019"

cd ../../
pause