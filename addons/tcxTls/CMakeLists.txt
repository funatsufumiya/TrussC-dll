# =============================================================================
# tcxTls - TLS/SSL Support Addon
# =============================================================================

cmake_minimum_required(VERSION 3.16)

set(ADDON_NAME tcxTls)

# Fetch mbedTLS via FetchContent
include(FetchContent)
FetchContent_Declare(
    mbedtls
    GIT_REPOSITORY https://github.com/Mbed-TLS/mbedtls.git
    GIT_TAG v3.5.0
)
set(ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(ENABLE_PROGRAMS OFF CACHE BOOL "" FORCE)
set(MBEDTLS_FATAL_WARNINGS OFF CACHE BOOL "" FORCE)
set(DISABLE_PACKAGE_CONFIG_AND_INSTALL ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(mbedtls)

# Source files
file(GLOB ADDON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB ADDON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

if(TRUSSC_BUILD_SHARED_AND_STATIC)
    add_library(${ADDON_NAME} SHARED ${ADDON_SOURCES} ${ADDON_HEADERS})
    add_library(${ADDON_NAME}_static STATIC ${ADDON_SOURCES} ${ADDON_HEADERS})
    set(_ADDON_TARGETS ${ADDON_NAME} ${ADDON_NAME}_static)
else()
    add_library(${ADDON_NAME} STATIC ${ADDON_SOURCES} ${ADDON_HEADERS})
    set(_ADDON_TARGETS ${ADDON_NAME})
endif()

add_library(tc::tcxTls ALIAS ${ADDON_NAME})

foreach(_t IN LISTS _ADDON_TARGETS)
    target_include_directories(${_t} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(${_t} PUBLIC TrussC PRIVATE mbedtls mbedx509 mbedcrypto)
endforeach()
