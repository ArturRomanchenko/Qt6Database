cmake_minimum_required(VERSION 3.5)

project(CarDealer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        window.cpp
        window.h
        interface.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CarDealer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        interactions.cpp
        interactions.h
        themes.h
        themes.cpp
        res.qrc
    )
else()
    if(ANDROID)
        add_library(CarDealer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(CarDealer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CarDealer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CarDealer PRIVATE Qt6::Widgets Qt6::Sql)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CarDealer)
endif()
set_target_properties(CarDealer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CarDealer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CarDealer)
endif()
