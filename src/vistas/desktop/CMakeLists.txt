# desktop/CMakeLists.txt
set(DESKTOP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tienda_desktop
    main_desktop.cpp
    MainWindow.cpp
    MainWindow.h
)

target_include_directories(tienda_desktop PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${DESKTOP_ROOT}
)

target_link_libraries(tienda_desktop PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Sql
    managers
    persistencia
    modelos
)
