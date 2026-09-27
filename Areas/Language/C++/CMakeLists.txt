cmake_minimum_required(VERSION 3.16)
project(IIiad_Cpp17 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)

# One executable per CaseStudy/<case> directory, built from every *.cpp in it.
set(CASE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CaseStudy")
file(GLOB CASE_DIRS CONFIGURE_DEPENDS "${CASE_ROOT}/*")

foreach(case_dir IN LISTS CASE_DIRS)
    if(IS_DIRECTORY "${case_dir}")
        get_filename_component(case_name "${case_dir}" NAME)
        file(GLOB case_srcs CONFIGURE_DEPENDS "${case_dir}/*.cpp")
        if(case_srcs)
            add_executable("${case_name}" ${case_srcs})
            target_include_directories("${case_name}" PRIVATE "${case_dir}")
        endif()
    endif()
endforeach()
