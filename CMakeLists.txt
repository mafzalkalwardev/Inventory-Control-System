cmake_minimum_required(VERSION 3.16)
project(InventoryControl VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(InventoryControl
    src/main.cpp
    src/Product.cpp
    src/HashTable.cpp
    src/FileHandler.cpp
    src/InventorySystem.cpp
    src/Validator.cpp
    src/Utils.cpp
)

target_include_directories(InventoryControl PRIVATE include)

# Static-link MinGW runtime so the .exe runs without libstdc++/libgcc on PATH
if(MINGW)
    target_link_options(InventoryControl PRIVATE -static -static-libgcc -static-libstdc++)
endif()

# Copy data directory next to the executable so relative paths work at runtime
add_custom_command(TARGET InventoryControl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:InventoryControl>/data
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/data/users.dat
            $<TARGET_FILE_DIR:InventoryControl>/data/users.dat
)
