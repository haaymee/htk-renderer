@echo off

:: === CONFIGURATION ===
set BUILD_DIR=Build
set THIRDPARTY_DIR="ThirdParty"
set GENERATOR="Visual Studio 17 2022"
set CONFIG=Debug

echo -----------------------------------
echo Regenerating CMake project...
echo -----------------------------------

cmake -S . -B %BUILD_DIR% -G %GENERATOR% -DCMAKE_BUILD_TYPE=%CONFIG%

echo.
echo -----------------------------------
echo Building project...
echo -----------------------------------

cmake --build %BUILD_DIR% --config %CONFIG%

echo.
echo -----------------------------------
echo Build complete!
echo -----------------------------------
pause