cmake_minimum_required(VERSION 3.16)

project(LexerWithAutomat VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(PROJECT_SOURCES
    lexer.cpp
    lexer.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Res.qrc
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(LexerWithAutomat
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(LexerWithAutomat
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(LexerWithAutomat
    PRIVATE
        Qt${QT_VERSION_MAJOR}::PrintSupport
        Qt${QT_VERSION_MAJOR}::Widgets
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_finalize_executable(LexerWithAutomat)
endif()
