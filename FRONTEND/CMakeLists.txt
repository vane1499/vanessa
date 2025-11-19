cmake_minimum_required(VERSION 3.16)
project(tienda_belleza LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# activar generación automática de moc/uic/rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# indicar explícitamente dónde buscar los .ui (esto arregla el problema de búsqueda)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# includes de proyecto
include_directories(${CMAKE_SOURCE_DIR}/include)

# archivos fuentes
set(SRC
    src/main.cpp
    src/mainwindow.cpp
    src/product.cpp
    src/store.cpp
    src/utils.cpp
    src/console.cpp
)

# headers
set(HEADERS
    include/mainwindow.h
    include/product.h
    include/store.h
    include/utils.h
)

# recoger todos los .ui (asegura que si hay más, se incluyan)
file(GLOB UI_FILES "${CMAKE_SOURCE_DIR}/ui/*.ui")

# Asegurar buenas prácticas de compilación
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

qt_add_executable(tienda_belleza
    ${SRC}
    ${HEADERS}
    ${UI_FILES}
)
# Incluir directorios para todos los headers
target_include_directories(tienda_belleza PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)


# Asegurar que el compilador vea los headers generados por autogen
# (el directorio exacto se crea en build/tienda_belleza_autogen/include)
target_include_directories(tienda_belleza PRIVATE ${CMAKE_BINARY_DIR}/tienda_belleza_autogen/include)

target_link_libraries(tienda_belleza PRIVATE Qt6::Widgets)

qt_finalize_executable(tienda_belleza)

install(TARGETS tienda_belleza DESTINATION bin)
