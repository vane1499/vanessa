cmake_minimum_required(VERSION 3.16)
project(tienda_belleza LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# incluye
include_directories(${CMAKE_SOURCE_DIR}/include)
set(UI_FILES ui/mainwindow.ui)

set(SRC
    src/main.cpp
    src/mainwindow.cpp
    src/product.cpp
    src/store.cpp
    src/utils.cpp
    src/console.cpp
)

set(HEADERS
    include/mainwindow.h
    include/product.h
    include/store.h
)

qt_add_executable(tienda_belleza
    ${SRC}
    ${HEADERS}
    ${UI_FILES}
)
qt_add_executable(tienda_belleza
    src/main.cpp
    src/mainwindow.cpp
    src/product.cpp
    src/store.cpp
    src/utils.cpp
    src/console.cpp
    ui/mainwindow.ui   # 👈 importante
)

# uic genera ui_mainwindow.h
qt_finalize_executable(tienda_belleza)

target_link_libraries(tienda_belleza PRIVATE Qt6::Widgets)

# Instalación opcional
install(TARGETS tienda_belleza DESTINATION bin)
