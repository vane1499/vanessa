# ================================
# CMake para el módulo src/
# Arquitectura limpia (modelos, persistencia, managers, vistas)
# ================================

set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# -------------------------
# MODELOS
# -------------------------
add_library(modelos
    modelos/producto.cpp
)
target_include_directories(modelos PUBLIC
    ${SRC_ROOT}
    ${SRC_ROOT}/modelos
)

# -------------------------
# PERSISTENCIA
# -------------------------
add_library(persistencia
    persistencia/persist_sqlite.cpp
)
target_include_directories(persistencia PUBLIC
    ${SRC_ROOT}
    ${SRC_ROOT}/persistencia
    ${SRC_ROOT}/modelos
)
target_link_libraries(persistencia PUBLIC Qt6::Core Qt6::Sql modelos)

# -------------------------
# MANAGERS
# -------------------------
add_library(managers
    managers/producto_manager.cpp
)
target_include_directories(managers PUBLIC
    ${SRC_ROOT}
    ${SRC_ROOT}/managers
    ${SRC_ROOT}/persistencia
    ${SRC_ROOT}/modelos
)
target_link_libraries(managers PUBLIC persistencia modelos)

# -------------------------
# EJECUTABLE CONSOLA
# -------------------------
add_executable(tienda_consola
    vistas/consola/main_console.cpp
)
target_include_directories(tienda_consola PRIVATE
    ${SRC_ROOT}
    ${SRC_ROOT}/vistas/consola
)
target_link_libraries(tienda_consola PRIVATE managers persistencia modelos Qt6::Core Qt6::Sql)

# -------------------------====================================================
# CURSES / PDCURSES
# -------------------------
find_package(Curses REQUIRED)
if (WIN32)
    message(STATUS "Using PDCurses (Windows)")

    set(CURSES_INCLUDE_PATH "C:/pdcurses")
    set(CURSES_LIBRARY "C:/pdcurses/wincon/pdcurses.a")   # ESTA ES TU RUTA REAL

    include_directories(${CURSES_INCLUDE_PATH})
else()
    find_package(Curses REQUIRED)
endif()


if (Curses_FOUND)
    message(STATUS "Found Curses: includes=${CURSES_INCLUDE_DIR} libs=${CURSES_LIBRARIES}")
endif()

# -------------------------
# EJECUTABLE TUI
# -------------------------
add_executable(tienda_tui
    vistas/tui/main_tui.cpp
    vistas/tui/tui_curses.cpp
)

target_include_directories(tienda_tui PRIVATE
    ${SRC_ROOT}
    ${SRC_ROOT}/vistas/tui
    ${CURSES_INCLUDE_DIR}
    C:/pdcurses/include
)

target_link_libraries(tienda_tui PRIVATE
    managers
    persistencia
    modelos
    Qt6::Core
    Qt6::Sql
    ${CURSES_LIBRARIES}
)

# -------------------------
# TESTS OPCIONALES
# -------------------------
option(ENABLE_TESTS "Enable unit tests" OFF)
if (ENABLE_TESTS)
    add_subdirectory(tests)
endif()

# Ruta donde esta curses.h
include_directories("C:/pdcurses")

# Ruta donde esta la biblioteca pdcurses.a
link_directories("C:/pdcurses/wincon")
target_link_libraries(tienda_tui PRIVATE ${CURSES_LIBRARY})
