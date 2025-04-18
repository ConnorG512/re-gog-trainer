# Platform / Architecture:
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

set(triple i686-w64-mingw32)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET ${triple})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)



# # Set the target architecture
# set(CMAKE_CXX_FLAGS "--target=i686-w64-windows-gnu")
# # Windows defines 
# add_definitions(-D_WIN32 -D_WINDOWS -D__WIN32__ -D_MINGW_USE_MINGW_ANSI_STDIO=1)
#
# # MinGW directories
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/i686-w64-mingw32/include")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/lib/gcc/i686-w64-mingw32/include")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include")
#
# # search headers and libraries in the target environment
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
