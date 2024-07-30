cmake_minimum_required(VERSION 3.14)
project(map-view)

set(CMAKE_CXX_STANDARD 17)

find_package(freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

# Пытаемся найти предустановленный SFML
find_package(SFML COMPONENTS graphics)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # Если SFML не найден - выкачиваем и собираем из исходников
    message(STATUS "Get SFML from the source code")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    # Обход потенциальных проблем при сборке sfml-graphics
    # (stb_image.h: 'argument': conversion from 'int' to 'short')
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

add_executable(map-view
        main.cpp
        TilesSourceImpl.cpp
        TileData.cpp
        Scene.cpp
        EventsImpl.cpp
        RenderImpl.cpp
        Builder.cpp
        TileCache.cpp
        Tile.cpp
        Geography.cpp
        Geography.hpp
        Location.hpp
        BaseQtCanvas.cpp
        BaseQtCanvas.hpp
        SFMLWidget.cpp
        SFMLWidget.hpp
)
target_link_libraries(map-view PRIVATE
        Freetype::Freetype
        Qt5::Widgets
        Qt5::Gui
        Qt5::Core
        Qt5::QWindowsIntegrationPlugin
        sfml-graphics)

target_compile_options(map-view PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
