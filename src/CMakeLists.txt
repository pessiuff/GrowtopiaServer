project(server LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB INCLUDE_FILES
    *.hpp
    **/*.hpp
    **/**/*.hpp
    **/**/**/*.hpp
    **/**/**/**/*.hpp
)
file(GLOB SOURCE_FILES
    *.cpp
    **/*.cpp
    **/**/*.cpp
    **/**/**/*.cpp
    **/**/**/**/*.cpp
)

add_executable(${PROJECT_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/runtime/cache/items.dat
                ${CMAKE_CURRENT_BINARY_DIR}/cache/items.dat)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/runtime/https/cert.pem
                ${CMAKE_CURRENT_BINARY_DIR}/https/cert.pem)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/runtime/https/key.pem
                ${CMAKE_CURRENT_BINARY_DIR}/https/key.pem)

if (MSVC)
    add_definitions(/EHsc)
else ()
    add_definitions(-fexceptions)
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN 
    SPDLOG_FMT_EXTERNAL
    CPPHTTPLIB_OPENSSL_SUPPORT
)

find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)
find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(unofficial-libmariadb REQUIRED)
find_path(HTTPLIB_INCLUDE_DIR   "httplib.h")

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${HTTPLIB_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    magic_enum::magic_enum
    spdlog::spdlog
    OpenSSL::SSL
    unofficial::libmariadb
    sqlpp11::sqlpp11
    Pal::Sigslot
    enet
)