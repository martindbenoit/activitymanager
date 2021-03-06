# @@@LICENSE
#
# Copyright (c) 2009-2013 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# LICENSE@@@

cmake_minimum_required(VERSION 2.8.7)

project(activitymanager CXX)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC2)
webos_component(2 0 0)

include(FindPkgConfig)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${GLIB2_CFLAGS_OTHER})

pkg_check_modules(OPENSSL REQUIRED openssl)
include_directories(${OPENSSL_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${OPENSSL_CFLAGS_OTHER})

pkg_check_modules(LS2 REQUIRED luna-service2)
include_directories(${LS2_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${LS2_CFLAGS_OTHER})

find_package(Boost REQUIRED COMPONENTS regex)
include_directories(${Boost_INCLUDE_DIRS})

pkg_check_modules(DB8 REQUIRED db8)
include_directories(${DB8_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${DB8_CFLAGS_OTHER})

pkg_check_modules(PMLOG REQUIRED PmLogLib)
include_directories(${PMLOG_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${PMLOG_CFLAGS_OTHER})

# There is a call to system("initctl ...") in ServiceApp.cpp which is compiled in for
# all implementations except WEBOS_TARGET_MACHINE_IMPL_SIMULATOR
webos_machine_impl_dep()

include_directories(include/internal)
webos_add_compiler_flags(ALL -Wall -Wno-error=strict-aliasing -Wconversion -DMOJ_LINUX -DBOOST_SP_DISABLE_THREADS -DUSE_PMLOG)
webos_add_compiler_flags(DEBUG -DMOJ_DEBUG)

# MojoDb generates warnings in core/MojObject.h, so no -Werror
#webos_add_compiler_flags(ALL -Werror )

webos_add_linker_options (ALL "--no-undefined")

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(activitymanager ${SOURCE_FILES})
target_link_libraries(activitymanager
                      ${DB8_LDFLAGS}
                      ${Boost_LIBRARIES}
                      ${GLIB2_LDFLAGS}
                      ${OPENSSL_LDFLAGS}
                      ${LS2_LDFLAGS}
                      ${PMLOG_LDFLAGS}
                     )

webos_build_daemon()
webos_build_system_bus_files()
webos_build_db8_files()

if (WEBOS_CONFIG_BUILD_TESTS)
  webos_add_compiler_flags(ALL -DUNITTEST)
endif()
