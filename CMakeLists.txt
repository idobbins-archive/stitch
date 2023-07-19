
cmake_minimum_required(VERSION 3.24)

project(stitch)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror -fno-exceptions)
endif()

target_sources(${PROJECT_NAME} PRIVATE
        main.cpp
        )

find_package(OpenCV REQUIRED)
target_include_directories(${PROJECT_NAME} INTERFACE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

#target_compile_options(${PROJECT_NAME} PRIVATE -Ofast -march=native)
