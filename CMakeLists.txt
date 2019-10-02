# Copyright (c) 2007-2019 LG Electronics, Inc.
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

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    add_subdirectory(src/initctl)
    add_subdirectory(src/utils)
endif()

##### environments #####
webos_configure_source_files(systemd_in_global_env
    files/systemd/environments/30-webos-global.conf)

set(systemd_conf
    files/systemd/environments/system.conf)

##### overrides #####
set(systemd_common_override
    files/systemd/overrides/common/default-webos.target.wants
    files/systemd/overrides/common/local-fs.target.wants
    files/systemd/overrides/common/multi-user.target.wants
    files/systemd/overrides/common/webos-bd.target.wants
    files/systemd/overrides/common/webos-cbd.target.wants
    files/systemd/overrides/common/webos-dis.target.wants
    files/systemd/overrides/common/webos-ibd.target.wants
    files/systemd/overrides/common/webos-mbd.target.wants
    files/systemd/overrides/common/webos-rbd.target.wants)

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    set(systemd_distro_override
        files/systemd/overrides/${WEBOS_TARGET_DISTRO}/multi-user.target.wants
        files/systemd/overrides/${WEBOS_TARGET_DISTRO}/webos-bd.target.wants
        files/systemd/overrides/${WEBOS_TARGET_DISTRO}/webos-cbd.target.wants)
endif()

##### scripts #####
webos_configure_source_files(systemd_common_in_scripts
    files/systemd/scripts/common/booster.sh
    files/systemd/scripts/common/configurator-db8.sh
    files/systemd/scripts/common/devmode.sh
    files/systemd/scripts/common/jail.sh
    files/systemd/scripts/common/luna-download-mgr.sh
    files/systemd/scripts/common/maliit-server.sh
    files/systemd/scripts/common/populate-volatile.sh
    files/systemd/scripts/common/sam.sh
    files/systemd/scripts/common/settings-service.sh)

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    webos_configure_source_files(systemd_distro_in_scripts
        files/systemd/scripts/${WEBOS_TARGET_DISTRO}/swap-on.sh
        files/systemd/scripts/${WEBOS_TARGET_DISTRO}/usbctrl.sh
        files/systemd/scripts/${WEBOS_TARGET_DISTRO}/webos-bluetooth-service.sh
        files/systemd/scripts/${WEBOS_TARGET_DISTRO}/zram-on.sh)
endif()

set(systemd_enable_systemd_environments
    files/systemd/scripts/common/get-systemd-environments.sh)

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    set(journald_log_handle_script
        files/systemd/scripts/${WEBOS_TARGET_DISTRO}/save-journald-logs.py)
endif()

##### services #####
set(systemd_common_service_units
    files/systemd/services/common/)

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    set(systemd_distro_service_units
        files/systemd/services/${WEBOS_TARGET_DISTRO}/)
endif()

set(systemd_mask_service_units
    files/systemd/services/mask/)

##### targets #####
set(systemd_common_target_units
    files/systemd/targets/common/)

##### tmpfiles #####
webos_configure_source_files(systemd_in_tmpfile
    files/systemd/tmpfiles/30-run.conf
    files/systemd/tmpfiles/31-var.conf)


##################################
# Install to /etc/...
##################################

# Global env files
install(FILES
    ${systemd_in_global_env}
    ${systemd_conf}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system.conf.d)

# Support to enable systemd environments on console
install(PROGRAMS
    ${systemd_enable_systemd_environments}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/profile.d)

# tmpfiles
install(FILES
    ${systemd_in_tmpfile}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/tmpfiles.d)

# Masking and Override systemd module
install(DIRECTORY
    ${systemd_mask_service_units}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system)


##################################
# Install to /lib/...
##################################

# install overrides (target wants)
install(DIRECTORY
    ${systemd_common_override}
    ${systemd_distro_override}
    DESTINATION ${WEBOS_INSTALL_BASE_LIBDIR}/systemd/system)

# install scripts
install(PROGRAMS
    ${systemd_common_in_scripts}
    ${systemd_distro_in_scripts}
    ${journald_log_handle_script}
    DESTINATION ${WEBOS_INSTALL_BASE_LIBDIR}/systemd/system/scripts)

# install systemd units
install(DIRECTORY
    ${systemd_common_service_units}
    ${systemd_distro_service_units}
    ${systemd_common_target_units}
    DESTINATION ${WEBOS_INSTALL_BASE_LIBDIR}/systemd/system)
