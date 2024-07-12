cmake_minimum_required(VERSION 3.20)

set(project "TankGame")
project(${project} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(raylib)
#add_subdirectory(src/raylib-tileson)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/player.png
#        ${CMAKE_CURRENT_BINARY_DIR}/res COPYONLY)
#        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/bullet.png
#        ${CMAKE_CURRENT_BINARY_DIR}/res COPYONLY)

set(${project}_SOURCES
        src/raylib-tileson/raylib-tileson.cpp
        src/textures.cpp
        src/font.cpp
        src/sound.cpp
        src/scene.cpp 
        src/player.cpp
        src/enemy.cpp
        src/block.h
        src/projectile.cpp
        src/explosion.h
        src/entitycreator.cpp
        src/game.h
        hello.cpp
        )

#set(${project}_HEADERS
#        src/object.h
#        src/player.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})
#        ${${project}_HEADERS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res) # Работает корректно только в новоявленной папке build, все свои новые ресурсы надо дублировать в билде ручками

add_executable(${project}
        ${${project}_SOURCE_LIST})

#add_executable(hello "hello.cpp")
#target_link_libraries(hello raylib raylib-tileson)

target_link_libraries(${project} PUBLIC raylib) #PUBLIC raylib-tileson)