cmake_minimum_required(VERSION 3.28)
project(DocGenerator)

set(CMAKE_CXX_STANDARD 17)

############### minidocx ###############
add_subdirectory(external/minidocx-0.5.0)

############### SQLiteC++ ###############
add_subdirectory(external/SQLiteCpp-3.3.1)

add_executable(DocGenerator main.cpp
        external/Randomizer/Randomizer.cpp
        external/Randomizer/Randomizer.h
        src/files/DocGenerator.cpp
        src/headers/DocGenerator.h)

target_link_libraries(DocGenerator
        minidocx
        SQLiteCpp sqlite3 pthread)
