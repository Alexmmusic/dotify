cmake_minimum_required(VERSION 3.10)
project(Dotify)

# Establece el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agrega los archivos fuente
add_executable(Dotify
    main.cpp
    normalizador.cpp
    TGameEngine.cpp
)

# Añade directorios de encabezados (.h)
target_include_directories(Dotify PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Añade directorios de librerías (.a, .so, etc.)
link_directories(${CMAKE_SOURCE_DIR}/bin)

# Vincula las bibliotecas
target_link_libraries(Dotify PRIVATE
    ${CMAKE_SOURCE_DIR}/bin/libSDL2.a
    ${CMAKE_SOURCE_DIR}/bin/libSDL2_image.a
    ${CMAKE_SOURCE_DIR}/bin/libSDL2_ttf.a
    
    # Dependencias del sistema requeridas por SDL2
    m
    dl
    pthread
    rt
    X11
    Xext
    Xcursor
    Xinerama
    Xi
    Xrandr
    wayland-client
    wayland-cursor
    wayland-egl
    xkbcommon
    asound
    pulse
    pulse-simple

    freetype
)




