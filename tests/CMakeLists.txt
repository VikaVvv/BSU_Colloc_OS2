cmake_minimum_required(VERSION 3.15)

# Скачиваем Catch2 если нет
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.7
)
FetchContent_MakeAvailable(Catch2)

# Тестовый исполняемый файл
add_executable(SingletonTests
    TestSingleton.cpp
)

target_link_libraries(SingletonTests
    PRIVATE
    SingletonCore
    Catch2::Catch2
)

enable_testing()
add_test(NAME SingletonTests COMMAND SingletonTests)