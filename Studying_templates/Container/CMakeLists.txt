cmake_minimum_required(VERSION 3.15)	# Проверка версии CMake.
										# Если версия установленой программы
										# старее указаной, произайдёт аварийный выход.

set(CMAKE_CXX_COMPILER clang++-12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -std=c++20 -Wall -fdeclspec -march=native") #-fsanitize=address

set(DLL "-lsfml-graphics -lsfml-window -lsfml-system")
set(NO_OPT "-fno-elide-constructors")

project(Container)			# Название проекта

set(SOURCE_EXE main.cpp)	# Установка переменной со списком исходников для исполняемого файла

include_directories("src/Container/" 
                    "src/Trainings/"
                    "src/Types/Intercepted_int/")

set(SOURCES src/Container/Container.cpp 
            src/Container/Static_mem.cpp 
            src/Container/Dynamic_mem.cpp
            src/Types/Intercepted_int/Intercepted_int.cpp)

add_executable(main ${SOURCE_EXE} ${SOURCES})
