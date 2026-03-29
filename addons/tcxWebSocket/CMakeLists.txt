# =============================================================================
# tcxWebSocket - WebSocket Client Addon
# =============================================================================

cmake_minimum_required(VERSION 3.16)

set(ADDON_NAME tcxWebSocket)

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

add_library(tc::tcxWebSocket ALIAS ${ADDON_NAME})

foreach(_t IN LISTS _ADDON_TARGETS)
    target_include_directories(${_t} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
endforeach()

# Depends on TrussC and tcxTls (for wss:// on native)
# If tcxTls is not used, only ws:// will work on native.
if(EMSCRIPTEN)
    foreach(_t IN LISTS _ADDON_TARGETS)
        target_link_libraries(${_t} PUBLIC TrussC)
        target_link_options(${_t} PUBLIC "SHELL:-lwebsocket.js")
    endforeach()
else()
    foreach(_t IN LISTS _ADDON_TARGETS)
        target_link_libraries(${_t} PUBLIC TrussC tc::tcxTls)
        if(MSVC)
            set_target_properties(${_t} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
            target_link_libraries(${_t} PUBLIC legacy_stdio_definitions)
        endif()
    endforeach()
endif()
