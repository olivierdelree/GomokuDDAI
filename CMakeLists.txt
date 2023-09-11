cmake_minimum_required(VERSION 3.26)
project(GomokuDDAI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6Widgets REQUIRED)

include_directories("include")
set(CMAKE_PREFIX_PATH "lib/Qt/6.5.2/mingw_64")
add_executable(GomokuDDAI
        main.cpp
        src/MainWindow.cpp
        include/MainWindow.h
        src/MainMenuScene.cpp
        include/MainMenuScene.h
        src/MainGameScene.cpp
        include/MainGameScene.h)
target_link_libraries(GomokuDDAI PRIVATE Qt6::Widgets
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
