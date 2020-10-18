# SPDX-License-Identifier: LGPL-2.1+

#-------------------------------
# PROJECT INFORMATION
#-------------------------------

cmake_minimum_required(VERSION 3.13)

project(sdevent-cpp VERSION 0.1.0 LANGUAGES C CXX)

include(GNUInstallDirs)

#-------------------------------
# PERFORMING CHECKS & PREPARING THE DEPENDENCIES
#-------------------------------

find_package(PkgConfig REQUIRED)
pkg_check_modules(Systemd IMPORTED_TARGET GLOBAL libsystemd>=221)
if(NOT TARGET PkgConfig::Systemd)
    message(FATAL_ERROR "libsystemd of version at least 221 is required, but was not found ")
endif()
add_library(Systemd::Libsystemd ALIAS PkgConfig::Systemd)
set(LIBSYSTEMD_VERSION ${Systemd_VERSION})

#-------------------------------
# SOURCE FILES CONFIGURATION
#-------------------------------

set(SDEVENTCPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SDEVENTCPP_INCLUDE_SUBDIR sdevent-cpp)
set(SDEVENTCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${SDEVENTCPP_INCLUDE_SUBDIR})

set(SDEVENTCPP_CPP_SRCS
    ${SDEVENTCPP_SOURCE_DIR}/sdevent.cpp
)

set(SDEVENTCPP_HDR_SRCS
)

set(SDEVENTCPP_PUBLIC_HDRS
    ${SDEVENTCPP_INCLUDE_DIR}/sdevent.hpp
)

set(SDEVENTCPP_SRCS ${SDEVENTCPP_CPP_SRCS} ${SDEVENTCPP_HDR_SRCS} ${SDEVENTCPP_PUBLIC_HDRS})

#-------------------------------
# GENERAL COMPILER CONFIGURATION
#-------------------------------

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

#----------------------------------
# LIBRARY BUILD INFORMATION
#----------------------------------

set(SDEVENTCPP_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(SDEVENTCPP_VERSION "${PROJECT_VERSION}")

add_library(sdevent-cpp SHARED ${SDEVENTCPP_SRCS})

target_link_libraries(sdevent-cpp PUBLIC Systemd::Libsystemd)

target_include_directories(sdevent-cpp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(sdevent-cpp
    PROPERTIES PUBLIC_HEADER "${SDEVENTCPP_PUBLIC_HDRS}"
    VERSION "${SDEVENTCPP_VERSION}"
    SOVERSION "${SDEVENTCPP_VERSION_MAJOR}"
)

#----------------------------------
# INSTALLATION
#----------------------------------

install(TARGETS sdevent-cpp
        EXPORT sdevent-cpp-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT libraries
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libraries
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT static_libraries
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${SDEVENTCPP_INCLUDE_SUBDIR} COMPONENT dev
)

#----------------------------------
# TESTS
#----------------------------------

option(BUILD_TESTS "Build and install tests (default OFF)" OFF)

if(BUILD_TESTS)
    message(STATUS "Building with tests")
    enable_testing()
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()
