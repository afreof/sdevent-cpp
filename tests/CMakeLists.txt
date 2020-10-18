# SPDX-License-Identifier: LGPL-2.1+

cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0048 NEW)
project(sdevent_test LANGUAGES CXX)

find_package(PkgConfig)
pkg_search_module(GTEST REQUIRED gtest_main)

add_executable(sdevent_test
    integrationtests/test_sdevent.cpp
    integrationtests/fixture_sdevent.cpp
    integrationtests/fixture_sdevent.hpp
)

target_link_libraries(sdevent_test
    ${GTEST_LDFLAGS}
    sdevent-cpp
)

target_compile_options(sdevent_test PUBLIC ${GTEST_CFLAGS})
