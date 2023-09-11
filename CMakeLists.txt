cmake_minimum_required(VERSION 3.0.0)
project(CountdownTimer VERSION 0.1.0 LANGUAGES C CXX)

# ソースファイルのリストを自動的に取得
file(GLOB SOURCES "src/*.cpp")

# プロジェクトの実行可能ファイルをビルド
add_executable(CountdownTimer ${SOURCES})

# raygui を使用する場合は、必要
target_compile_definitions(CountdownTimer PRIVATE
    RAYGUI_IMPLEMENTATION
    BUILD_LIBTYPE_SHARED
)

# Raylibのヘッダーファイルのパスを設定
include_directories(include)

# Raylibのライブラリをリンク
target_link_libraries(CountdownTimer PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
    ${CMAKE_SOURCE_DIR}/lib/libraylibdll.a
    opengl32 gdi32 winmm
)