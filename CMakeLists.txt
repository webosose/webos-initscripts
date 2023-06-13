# Copyright (c) 2007-2023 LG Electronics, Inc.
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
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 2.8.7)

project(webos-initscripts C CXX)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC7)
webos_component(3 0 0)

webos_distro_dep()
webos_distro_variant_dep()

add_subdirectory(src/upstart-utils/initctl)
add_subdirectory(src/upstart-utils/utils)


#################################
# /etc/profile.d
#################################

set(systemd_enable_systemd_environments
    common/etc/profile.d/get-systemd-environments.sh)

install(PROGRAMS
    ${systemd_enable_systemd_environments}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/profile.d)


#################################
# /etc/tmpfiles.d
#################################

webos_configure_source_files(in_tmpfile
    common/etc/tmpfiles.d/30-run.conf
    common/etc/tmpfiles.d/31-var.conf)

install(FILES
    ${in_tmpfile}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/tmpfiles.d)


#################################
# /etc/systemd/system.conf.d
#################################

webos_configure_source_files(systemd_in_global_env
    common/etc/systemd/system.conf.d/webos-global.conf)

set(systemd_conf
    common/etc/systemd/system.conf.d/system.conf)

install(FILES
    ${systemd_in_global_env}
    ${systemd_conf}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system.conf.d)


#################################
# /etc/systemd/system
#################################

file(GLOB etc_units
    "common/etc/systemd/system/*.service"
    "common/etc/systemd/system/*.socket"
    "common/etc/systemd/system/*.timer")

install(FILES ${etc_units} DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system)


#################################
# /lib/systemd/system
#################################

file(GLOB lib_units
    "common/lib/systemd/system/*.slice"
    "common/lib/systemd/system/*.service"
    "common/lib/systemd/system/*.path"
    "common/lib/systemd/system/*.target")

install(FILES ${lib_units} DESTINATION ${WEBOS_INSTALL_BASE_LIBDIR}/systemd/system)

set(lib_wants
    common/lib/systemd/system/default-webos.target.wants
    common/lib/systemd/system/local-fs.target.wants
    common/lib/systemd/system/multi-user.target.wants
    common/lib/systemd/system/webos-bd.target.wants
    common/lib/systemd/system/webos-cbd.target.wants
    common/lib/systemd/system/webos-dis.target.wants
    common/lib/systemd/system/webos-ibd.target.wants
    common/lib/systemd/system/webos-mbd.target.wants
    common/lib/systemd/system/webos-rbd.target.wants
    common/lib/systemd/system/multi-user.target.wants
    common/lib/systemd/system/webos-bd.target.wants
    common/lib/systemd/system/webos-cbd.target.wants)

install(DIRECTORY
    ${lib_wants}
    DESTINATION ${WEBOS_INSTALL_BASE_LIBDIR}/systemd/system)


#################################
# /lib/systemd/system/scripts
#################################

install(PROGRAMS common/lib/systemd/system/scripts/save-journald-logs.py DESTINATION ${WEBOS_INSTALL_BASE_LIBDIR}/systemd/system/scripts)

webos_configure_source_files(lib_in_scripts
    common/lib/systemd/system/scripts/configurator-db8.sh
    common/lib/systemd/system/scripts/devmode.sh
    common/lib/systemd/system/scripts/fluent-bit.sh
    common/lib/systemd/system/scripts/jail.sh
    common/lib/systemd/system/scripts/luna-download-mgr.sh
    common/lib/systemd/system/scripts/maliit-server.sh
    common/lib/systemd/system/scripts/populate-volatile.sh
    common/lib/systemd/system/scripts/sam.sh
    common/lib/systemd/system/scripts/settings-service.sh
    common/lib/systemd/system/scripts/swap-on.sh
    common/lib/systemd/system/scripts/usbctrl.sh
    common/lib/systemd/system/scripts/webos-bluetooth-service.sh
    common/lib/systemd/system/scripts/webos-connman-adapter.sh
    common/lib/systemd/system/scripts/prepare-system-dirs.sh
    common/lib/systemd/system/scripts/zram-on.sh)

install(PROGRAMS ${lib_in_scripts} DESTINATION ${WEBOS_INSTALL_BASE_LIBDIR}/systemd/system/scripts)


#################################
# /usr/bin
#################################

webos_configure_source_files(preference-dir-info
   common/usr/bin/preference-dir-info)

install(PROGRAMS ${preference-dir-info} DESTINATION ${WEBOS_INSTALL_BINDIR})

file(GLOB bin_in_scripts
    "common/usr/bin/collect"
    "common/usr/bin/*info")

install(PROGRAMS ${bin_in_scripts} DESTINATION ${WEBOS_INSTALL_BINDIR})
