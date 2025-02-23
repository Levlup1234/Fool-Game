cmake_minimum_required(VERSION 3.15)

project(fool_game) # имя проекта

set(SOURCE_EXE main.cpp)    # Переменная списка исходников
set(SOURCE_LIB game_state.cpp)  # Переменная библиотеки

add_library(game_state STATIC ${SOURCE_LIB})   # Добавляем библиотеку
add_executable(game ${SOURCE_EXE})  # Исполняемый файл
target_link_libraries(game game_state) # Линковщик библиотек
