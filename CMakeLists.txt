
cmake_minimum_required(VERSION 2.6)
include_directories("/usr/local/lily")

add_library(linenoise SHARED lily_linenoise.c linenoise.c)
set_target_properties(
    linenoise
    PROPERTIES
        PREFIX ""
        COMPILE_FLAGS "-fPIC -g"
)    
    