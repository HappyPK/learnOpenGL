if not exist build mkdir build
cd build
if not exist vc16 mkdir vc16
cd vc16

cmake ../../ -G "Visual Studio 16 2019"

cd ../../