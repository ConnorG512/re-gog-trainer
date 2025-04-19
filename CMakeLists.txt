cmake_minimum_required(VERSION 3.27)
project(RE-GoG-Trainer CXX)

set(CMAKE_CXX_STANDARD 20)

# include toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/windows32-toolchain.cmake")

# Windows defines 
add_definitions(-D_WIN32 -D_WINDOWS -D__WIN32__ -D_MINGW_USE_MINGW_ANSI_STDIO=1)

# Statically link libstdc++ and libgcc
# set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Compile and link launcher
add_executable(re-gog-trainer-launcher 
  ./src/launcher/launcher.cpp
  ./src/util/logger.cpp
)
target_link_libraries(re-gog-trainer-launcher PRIVATE user32)

# Compile and link DLL
add_library(re-gog-trainer SHARED 
  ./src/trainer/dll.cpp
  ./src/trainer/memory_patcher.cpp
  ./src/util/logger.cpp
)
# target_link_libraries(re-gog-trainer PRIVATE user32)

