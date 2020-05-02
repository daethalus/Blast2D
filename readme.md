-DVCPKG_TARGET_TRIPLET=x64-windows-static 
-DCMAKE_TOOLCHAIN_FILE=vcpcklocation\scripts\buildsystems\vcpkg.cmake

./vcpkg.exe install glfw3:x64-windows-static

./vcpkg.exe install glad:x64-windows-static