cmake_minimum_required(VERSION 3.22)

include(FetchContent)
FetchContent_Declare(
    pico_sdk
    GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk.git
    GIT_TAG 2.1.0
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(pico_sdk)

project(
    pico_usb_hid_generic_linkage_code
    VERSION 1.0.0
    LANGUAGES C CXX ASM
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(APP_NAME "${PROJECT_NAME}.elf")

file(GLOB APP_FILES CONFIGURE_DEPENDS "${APP_DIR}/*.cpp" "${APP_DIR}/*.c")

add_executable("${APP_NAME}" ${APP_FILES})
target_link_libraries("${APP_NAME}" PRIVATE pico_stdlib tinyusb_device tinyusb_board)
target_include_directories("${APP_NAME}" PRIVATE "${INC_DIR}")
pico_add_extra_outputs("${APP_NAME}")