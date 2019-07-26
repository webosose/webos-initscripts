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

add_subdirectory(src/initctl)
add_subdirectory(src/utils)

##### environments #####
webos_configure_source_files(systemd_in_global_env
    files/systemd/environments/30-webos-global.conf)

set(systemd_conf
    files/systemd/environments/system.conf)

##### overrides #####
set(systemd_override
    files/systemd/overrides/)

##### scripts #####
webos_configure_source_files(systemd_in_scripts
    files/systemd/scripts/common/configurator-activity.sh
    files/systemd/scripts/configurator-db8.sh
    files/systemd/scripts/connman.sh
    files/systemd/scripts/db8-maindb.sh
    files/systemd/scripts/devmode.sh
    files/systemd/scripts/jail.sh
    files/systemd/scripts/luna-download-mgr.sh
    files/systemd/scripts/maliit-server.sh
    files/systemd/scripts/pm-log-daemon-stop.sh
    files/systemd/scripts/populate-volatile.sh
    files/systemd/scripts/sam.sh
    files/systemd/scripts/settings-service.sh
    files/systemd/scripts/swap-on.sh
    files/systemd/scripts/usbctrl.sh
    files/systemd/scripts/webos-bluetooth-service.sh
    files/systemd/scripts/zram-on.sh)

set(systemd_enable_systemd_environments
    files/systemd/scripts/get-systemd-environments.sh)

##### services #####
set(systemd_service_units
    files/systemd/services/)

##### targets #####
set(systemd_target_units
    files/systemd/targets/)

##### tmpfiles #####
webos_configure_source_files(systemd_in_tmpfile
    files/systemd/tmpfiles/30-run.conf
    files/systemd/tmpfiles/31-var.conf)

# install global env files
install(FILES
    ${systemd_in_global_env}
    ${systemd_conf}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system.conf.d)

# install override
install(DIRECTORY
    ${systemd_override}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system)

# install systemd scripts
install(PROGRAMS
    ${systemd_in_scripts}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system/scripts)

# install support to enable systemd environments on console
install(PROGRAMS
    ${systemd_enable_systemd_environments}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/profile.d)

# install systemd units
install(DIRECTORY
    ${systemd_service_units}
    ${systemd_target_units}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system)

# install temp files
install(FILES
    ${systemd_in_tmpfile}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/tmpfiles.d)
