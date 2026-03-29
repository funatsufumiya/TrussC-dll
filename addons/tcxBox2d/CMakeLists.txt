# =============================================================================
# tcxBox2d - TrussC Box2D Addon
# =============================================================================

cmake_minimum_required(VERSION 3.16)

set(ADDON_NAME tcxBox2d)

# Fetch Box2D via FetchContent
include(FetchContent)
FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG v2.4.1
)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(BOX2D_USER_SETTINGS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(box2d)

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

foreach(_t IN LISTS _ADDON_TARGETS)
    target_include_directories(${_t} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    target_link_libraries(${_t} PUBLIC box2d TrussC)
endforeach()
