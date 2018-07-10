cmake_minimum_required(VERSION 2.8) 
project(NiceFramework C) 

set(APP_NAME run) 

set(SOURCE_FOLDER Source) 

set(SOURCES 
    ${SOURCE_FOLDER}/main.c 

    ${SOURCE_FOLDER}/NF/NFArray.c 
    ${SOURCE_FOLDER}/NF/NFError.c 
    ${SOURCE_FOLDER}/NF/NFHashTable.c 
    ${SOURCE_FOLDER}/NF/NFMemory.c
)

include_directories(Include) 
include_directories(Source) 

set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -g -ansi")

set(CMAKE_C_FLAGS_RELEASE     "${CMAKE_C_FLAGS_RELEASE} -Wall -O2 -ansi")

add_executable(${APP_NAME} ${SOURCES})
