cmake_minimum_required(VERSION 3.13.5)

project(No-Sleep LANGUAGES C RC)

if(NOT WIN32)
    message(FATAL_ERROR "Windows is the only supported platform!")
endif()

math(EXPR BUILD_BITS "${CMAKE_SIZEOF_VOID_P} * 8")

list(APPEND NOSLEEP_SOURCE
    controls.c
    guifonts.c
    main.c
    nosleep.h
    resource.h
    state.c
)

list(APPEND NOSLEEP_RESOURCES
    ${PROJECT_SOURCE_DIR}/res/Button_Click.wav
    ${PROJECT_SOURCE_DIR}/res/NoSleep.ico
    ${PROJECT_SOURCE_DIR}/NoSleep.exe.manifest
)
set_source_files_properties(nosleep.rc PROPERTIES OBJECT_DEPENDS "${NOSLEEP_RESOURCES}")

# Add application EXE
add_executable(NoSleep WIN32 ${NOSLEEP_SOURCE} nosleep.rc)
if(BUILD_BITS EQUAL 64)
    set_target_properties(NoSleep PROPERTIES OUTPUT_NAME "NoSleep64")
endif()

# Link Windows libraries
target_link_libraries(NoSleep winmm comctl32)
