# コンパイラの設定
# set(CMAKE_C_COMPILER "C:/msys64/usr/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER "C:/msys64/usr/bin/g++.exe")
# set(CMAKE_C_COMPILER gcc)
# set(CMAKE_CXX_COMPILER g++)

cmake_minimum_required(VERSION 3.10)

# プロジェクト名
project(PasswordAnalysis)

# vcpkgの設定
# set(CMAKE_TOOLCHAIN_FILE "C:/Users/m6018/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake")

# CMAKE_PREFIX_PATHの設定
# set(CMAKE_PREFIX_PATH "C:/Users/m6018/Documents/vcpkg/installed/x64-windows")

# ソースファイルの設定
set(SOURCES
    src/main.cpp
    src/analysis.cpp
)

# インクルードディレクトリの設定
include_directories(${PROJECT_SOURCE_DIR}/include)

# 実行可能ファイルの生成
add_executable(pascheck ${SOURCES})

# C++の標準を設定
set_target_properties(pascheck PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

# 必要なライブラリのリンク
find_package(libssh2 CONFIG REQUIRED)
target_link_libraries(pascheck PRIVATE libssh2::libssh2)
target_link_libraries(pascheck PRIVATE ws2_32)

# スタティックリンクを有効にする
set(CMAKE_EXE_LINKER_FLAGS "-static")

# システムのインクルードディレクトリを追加
include_directories(${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})