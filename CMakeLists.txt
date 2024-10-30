cmake_minimum_required(VERSION 3.10)

project(ProyectoMain C)

set(CMAKE_C_STANDARD 11)

if(WIN32)
    if(NOT MSVC)
        message(FATAL_ERROR "Este proyecto solo está configurado para MSVC en Windows")
    endif()
endif()

add_executable(ProyectoMain Source/main.c)

target_include_directories(ProyectoMain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)

file(GLOB TXT_FILES "${CMAKE_SOURCE_DIR}/Resources/*.txt")
foreach(txt_file ${TXT_FILES})
    add_custom_command(
        TARGET ProyectoMain POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${txt_file} $<TARGET_FILE_DIR:ProyectoMain>/resources
    )
endforeach()