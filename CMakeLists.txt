cmake_minimum_required(VERSION 3.20)
project(lab_application)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку сигналов/слотов
set(CMAKE_AUTOMOC ON)

# Указываем путь к Qt
set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt/6.11.0")

# Находим компоненты Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(${PROJECT_NAME} src/main.cpp
        include/inventory.h
        include/mainWindow.h
        include/product.h
        src/inventory.cpp
        src/mainWindow.cpp
        src/product.cpp)

# Линкуем библиотеки Qt
target_link_libraries(${PROJECT_NAME}
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
)

# Отключаем OpenGL для Qt
add_definitions(-DQT_NO_OPENGL)

set(SOURCES
        src/main.cpp
        src/mainWindow.cpp
        src/product.cpp
        src/inventory.cpp
)

set(HEADERS
        include/mainWindow.h
        include/product.h
        include/inventory.h
)