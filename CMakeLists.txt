
message(STATUS "=== OpenLieroVita ===")
message(STATUS "VitaSDK: $ENV{VITASDK}")
message(STATUS "SDL2:  ${SDL2_INCLUDE_DIRS}")

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_compile_options(-mthumb -ffunction-sections -fdata-sections -fvisibility=hidden -fvisibility-inlines-hidden)

cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(openlierovita)
include("${VITASDK}/share/vita.cmake" REQUIRED)
include("$ENV{VITASDK}/share/vita.toolchain.cmake" REQUIRED)

find_package(SDL2 REQUIRED)

find_package(SDL2_Image QUIET)

if(NOT SDL2_IMAGE_FOUND)
    find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
        HINTS $ENV{VITASDK}/arm-vita-eabi/include/SDL2)
    find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image SDL_image
        HINTS $ENV{VITASDK}/arm-vita-eabi/lib)
    find_library(SDL2_WEBP_LIBRARY NAMES webp
        HINTS $ENV{VITASDK}/arm-vita-eabi/lib)
    find_library(SDL2_WEBPDECODER_LIBRARY NAMES webpdecoder
        HINTS $ENV{VITASDK}/arm-vita-eabi/lib)
    find_library(SDL2_WEBPDEMUX_LIBRARY NAMES webpdemux
        HINTS $ENV{VITASDK}/arm-vita-eabi/lib)
    find_library(SDL2_WEBPMUX_LIBRARY NAMES webpmux
        HINTS $ENV{VITASDK}/arm-vita-eabi/lib)
    find_library(SDL2_PTHREAD_LIBRARY NAMES pthread
        HINTS $ENV{VITASDK}/arm-vita-eabi/lib)

    if(NOT SDL2_IMAGE_LIBRARY)
        message(FATAL_ERROR "SDL2_image not found; install it or set SDL2_IMAGE_DIR")
    endif()
endif()

set(VITA_APP_NAME "OpenLieroVita")
set(VITA_TITLEID  "LIER01337")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-DVITA)
set(SOURCES
    src/game/bobject.cpp
    src/game/bonus.cpp
    src/game/common.cpp
    src/game/console.cpp
    src/game/constants.cpp
    src/game/filesystem.cpp
    src/game/game.cpp
    src/game/level.cpp
    src/game/math.cpp
    src/game/ninjarope.cpp
    src/game/nobject.cpp
    src/game/rand.cpp
    src/game/settings.cpp
    src/game/sobject.cpp
    src/game/spectatorviewport.cpp
    src/game/stats_recorder.cpp
    src/game/sys.cpp
    src/game/text.cpp
    src/game/viewport.cpp
    src/game/weapon.cpp
    src/game/worm.cpp
    src/game/ai/dijkstra.cpp
    src/game/ai/predictive_ai.cpp
    src/game/gfx/blit.cpp
    src/game/gfx/font.cpp
    src/game/gfx/palette.cpp
    src/game/gfx/renderer.cpp
    src/game/gfx/sprite.cpp
    src/game/mixer/mixer.c
    src/game/mixer/player.cpp
    src/gvl/zlib/miniz.c
    src/gvl/system/system.c
    src/gvl/support/bits.c
    src/gvl/support/debug.cpp
    src/gvl/support/platform.cpp
    src/gvl/support/profile.cpp
    src/gvl/io2/stream.cpp
    src/gvl/io2/convert.cpp
    src/gvl/containers/list.cpp
)

set(GAME_SOURCES ${SOURCES}
    src/game/gfx.cpp
    src/game/keys.cpp
    src/game/main.cpp
    src/game/replay.cpp
    src/game/sfx.cpp
    src/game/weapsel.cpp
    src/game/controller/commonController.cpp
    src/game/controller/localController.cpp
    src/game/controller/replayController.cpp
    src/game/controller/stats_presenter.cpp
    src/game/menu/booleanSwitchBehavior.cpp
    src/game/menu/enumBehavior.cpp
    src/game/menu/hiddenMenu.cpp
    src/game/menu/integerBehavior.cpp
    src/game/menu/itemBehavior.cpp
    src/game/menu/mainMenu.cpp
    src/game/menu/menu.cpp
    src/game/menu/menuItem.cpp
    src/game/menu/timeBehavior.cpp
)

include_directories(
    src
    src/game
)

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

set(SDL2_IMAGE_LINK_LIB "")
if(TARGET SDL2::SDL2_image)
    set(SDL2_IMAGE_LINK_LIB SDL2::SDL2_image)
elseif(SDL2_IMAGE_LIBRARY)
    set(SDL2_IMAGE_LINK_LIB ${SDL2_IMAGE_LIBRARY})
    if(SDL2_WEBP_LIBRARY)
        list(APPEND SDL2_IMAGE_LINK_LIB ${SDL2_WEBP_LIBRARY})
    endif()
    if(SDL2_WEBPDECODER_LIBRARY)
        list(APPEND SDL2_IMAGE_LINK_LIB ${SDL2_WEBPDECODER_LIBRARY})
    endif()
    if(SDL2_WEBPDEMUX_LIBRARY)
        list(APPEND SDL2_IMAGE_LINK_LIB ${SDL2_WEBPDEMUX_LIBRARY})
    endif()
    if(SDL2_WEBPMUX_LIBRARY)
        list(APPEND SDL2_IMAGE_LINK_LIB ${SDL2_WEBPMUX_LIBRARY})
    endif()
    if(SDL2_PTHREAD_LIBRARY)
        list(APPEND SDL2_IMAGE_LINK_LIB ${SDL2_PTHREAD_LIBRARY})
    endif()
endif()

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 ${SDL2_IMAGE_LINK_LIB})
# target_link_libraries(${PROJECT_NAME}
#     SDL2::SDL2
#     SDL2::SDL2_image
# )

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)
