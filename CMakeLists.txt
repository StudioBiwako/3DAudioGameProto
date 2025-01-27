cmake_minimum_required(VERSION 3.27)
project(8_72)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

find_package(OpenAL REQUIRED)

add_executable(8_72 main.cpp
        Components/Window/Window.cpp
        Components/Window/Window.h
        Components/Archer/Archer.cpp
        Components/Archer/Archer.h
        Components/AudioEngine/AudioEngine.cpp
        Components/AudioEngine/AudioEngine.h
        Components/Player/Player.cpp
        Components/Player/Player.h
)

target_link_libraries(8_72
        Qt::Core
        Qt::Gui
        Qt::Widgets
        OpenAL::OpenAL
)