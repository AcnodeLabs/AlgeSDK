echo %1
echo %2
rmdir %USERPROFILE%\Desktop\AlgePackages\%1
mkdir %USERPROFILE%\Desktop\AlgePackages\%1
mkdir %USERPROFILE%\Desktop\AlgePackages\%1\Apps
mkdir %USERPROFILE%\Desktop\AlgePackages\%1\Apps\%1
copy %2..\..\Apps\%1\*.hpp %USERPROFILE%\Desktop\AlgePackages\%1\Apps
mkdir %USERPROFILE%\Desktop\AlgePackages\%1\Apps\%1.Assets\Data
mkdir %USERPROFILE%\Desktop\AlgePackages\%1\Platforms\Alge-Windows
