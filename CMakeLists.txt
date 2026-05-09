# 1. 指定最低 CMake 版本（3.15 支持 modern CMake 特性）
cmake_minimum_required(VERSION 3.15)

# 2. 定义项目名称、版本号、使用的语言
project(KZ VERSION 0.1.0 LANGUAGES CXX)

# 3. 设置 C++ 标准为 C++17（现代 C++ 足够，且大部分编译器支持）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 不要使用编译器扩展，保证跨平台行为一致
set(CMAKE_CXX_EXTENSIONS OFF)

# 4. 开启编译警告（相当于 g++ 的 -Wall -Wextra -Wpedantic）
if(MSVC)
    add_compile_options(/W4)          # MSVC 高警告级别
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 5. 设置可执行文件的输出目录（可选，让 build 目录更整洁）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 6. 收集所有源文件（推荐显式列出，也可用 GLOB，但正式项目显式更好）
#    这里先用显式列出，后续增加文件时手动添加
set(SOURCES
    src/main.cpp
)

# 7. 添加可执行文件目标
add_executable(kz 
    src/main.cpp
)

# 设置可执行文件输出到 build/bin 目录（相对于构建目录）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 8. 指定头文件搜索路径（public/private/interface）
#    PRIVATE 表示仅该目标自己需要，不会传递给依赖此目标的其他目标
target_include_directories(kz PRIVATE include)

# 9. 如果有第三方库，可以用 target_link_libraries 链接，比如：
#    find_package(nlohmann_json REQUIRED)
#    target_link_libraries(kz PRIVATE nlohmann_json::nlohmann_json)

# 10. 为 Debug 和 Release 模式分别设置不同的编译选项（可选）
target_compile_definitions(kz PRIVATE $<$<CONFIG:Debug>:KZ_DEBUG>)
if(NOT MSVC)
    target_compile_options(kz PRIVATE $<$<CONFIG:Debug>:-O0 -g>)
    target_compile_options(kz PRIVATE $<$<CONFIG:Release>:-O3 -DNDEBUG>)
endif()

# 11. 开启测试（如果需要，可后续添加单元测试）
# enable_testing()
# add_test(NAME kz_test COMMAND kz --test)