cmake_minimum_required(VERSION 3.10)

# プロジェクト名
project(PasswordAnalysis)

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