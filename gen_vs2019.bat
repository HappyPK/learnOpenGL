del %~dp0build /f/s/q/a
del %~dp0bin /f/s/q/a

if not exist build mkdir build
cd build
if not exist vc16 mkdir vc16
cd vc16

cmake ../../ -G "Visual Studio 16 2019"

cd ../../