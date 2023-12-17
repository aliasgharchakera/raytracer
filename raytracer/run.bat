@echo off

rem Check if the number of arguments is correct
if "%~1"=="" (
    echo Usage: %0 ^<source_file.cpp^> [file_type]
    exit /b 1
)

rem Get the source file from the command-line argument
set "source_file=%~1"

rem Get the file type from the command-line argument
set "file_type=%~2"

rem Compile C++ code
g++ raytracer.cpp cameras/*.cpp geometry/*.cpp lights/*.cpp materials/*.cpp samplers/*.cpp utilities/*.cpp world/*.cpp build/"build%file_type%%source_file%".cpp -o a.exe

rem Run the compiled C++ program
a.exe

rem Run the Python script
python convert.py %source_file% %file_type%

rem Delete the compiled C++ program
del a.exe

rem Delete the ppm file
del scene.ppm