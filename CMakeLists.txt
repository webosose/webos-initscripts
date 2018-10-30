# Copyright (c) 2007-2018 LG Electronics, Inc.
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

##### overrides #####
set(systemd_override
    files/systemd/overrides/multi-user.target.wants)

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    set(systemd_distro_override
        files/systemd/overrides/webos-cbd.target.wants)
endif()

##### scripts #####
webos_configure_source_files(systemd_in_scripts
    files/systemd/scripts/common/configurator-db8.sh
    files/systemd/scripts/common/connman.sh
    files/systemd/scripts/common/jail.sh
    files/systemd/scripts/common/luna-download-mgr.sh
    files/systemd/scripts/common/maliit-server.sh
    files/systemd/scripts/common/populate-volatile.sh
    files/systemd/scripts/common/sam.sh
    files/systemd/scripts/common/settings-service.sh
    files/systemd/scripts/common/usbctrl.sh
    files/systemd/scripts/common/wpa-supplicant.sh)

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    webos_configure_source_files(systemd_distro_in_scripts
        files/systemd/scripts/distro/${WEBOS_TARGET_DISTRO}/db8-maindb.sh
        files/systemd/scripts/distro/${WEBOS_TARGET_DISTRO}/devmode.sh
        files/systemd/scripts/distro/${WEBOS_TARGET_DISTRO}/pm-log-daemon-stop.sh
        files/systemd/scripts/distro/${WEBOS_TARGET_DISTRO}/swap-on.sh
        files/systemd/scripts/distro/${WEBOS_TARGET_DISTRO}/webapp-mgr.sh
        files/systemd/scripts/distro/${WEBOS_TARGET_DISTRO}/webos-bluetooth-service.sh
        files/systemd/scripts/distro/${WEBOS_TARGET_DISTRO}/zram-on.sh)
endif()

set(systemd_enable_systemd_environments
    files/systemd/scripts/common/get-systemd-environments.sh)

##### services & targets #####
set(systemd_units
    files/systemd/services/common/activitymanager.service
    files/systemd/services/common/appinstalld.service
    files/systemd/services/common/audiod.service
    files/systemd/services/common/audiooutputd.service
    files/systemd/services/common/booster.service
    files/systemd/services/common/bootd.service
    files/systemd/services/common/configd.service
    files/systemd/services/common/configurator-activity.service
    files/systemd/services/common/configurator-db8.service
    files/systemd/services/common/connman.service
    files/systemd/services/common/crashd.service
    files/systemd/services/common/db8-maindb.service
    files/systemd/services/common/db8-mediadb.service
    files/systemd/services/common/db8-pre-config.service
    files/systemd/services/common/db8-tempdb.service
    files/systemd/services/common/devmode.service
    files/systemd/services/common/dropbear.service
    files/systemd/services/common/dropbear.socket
    files/systemd/services/common/ecryptfs.service
    files/systemd/services/common/event-monitor.service
    files/systemd/services/common/jail.service
    files/systemd/services/common/ls-hubd.service
    files/systemd/services/common/lsm-ready.path
    files/systemd/services/common/lsm-ready.service
    files/systemd/services/common/luna-download-mgr.service
    files/systemd/services/common/luna-sys-service.service
    files/systemd/services/common/maliit-server.service
    files/systemd/services/common/notificationmgr.service
    files/systemd/services/common/nyx-utils.service
    files/systemd/services/common/pacrunner.service
    files/systemd/services/common/pm-klog-daemon.service
    files/systemd/services/common/populate-volatile.service
    files/systemd/services/common/rdxd.service
    files/systemd/services/common/sam.service
    files/systemd/services/common/second-screen-gateway.service
    files/systemd/services/common/settings-service-recovery.service
    files/systemd/services/common/settings-service.service
    files/systemd/services/common/sleepd.service
    files/systemd/services/common/sntp.service
    files/systemd/services/common/systemd-journal-flush.service
    files/systemd/services/common/systemd-journald.service
    files/systemd/services/common/umediaserver.service
    files/systemd/services/common/usbctrl.service
    files/systemd/services/common/webos-connman-adapter.service
    files/systemd/services/common/wpa-supplicant.service
    files/systemd/services/common/wpa_supplicant.service
    files/systemd/targets/default-webos.target
    files/systemd/targets/webos-bd.target
    files/systemd/targets/webos-cbd.target
    files/systemd/targets/webos-dis.target
    files/systemd/targets/webos-ibd.target
    files/systemd/targets/webos-mbd.target
    files/systemd/targets/webos-rbd.target)

if(${WEBOS_TARGET_DISTRO} STREQUAL "webos")
    set(systemd_distro_units
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/avoutputd.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/db8.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/pm-log-daemon.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/pulseaudio.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/surface-manager.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/swap-on.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/webapp-mgr.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/webos-bluetooth-service.service
        files/systemd/services/distro/${WEBOS_TARGET_DISTRO}/zram-on.service)
endif()

##### tmpfiles #####
webos_configure_source_files(systemd_in_tmpfile
    files/systemd/tmpfiles/30-run.conf
    files/systemd/tmpfiles/31-var.conf)

# install global env files
install(FILES
    ${systemd_global_env}
    ${systemd_in_global_env}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system.conf.d)

# install override
install(DIRECTORY
    ${systemd_override}
    ${systemd_distro_override}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system)

# install systemd scripts
install(PROGRAMS
    ${systemd_in_scripts}
    ${systemd_distro_in_scripts}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system/scripts)

# install support to enable systemd environments on console
install(PROGRAMS
    ${systemd_enable_systemd_environments}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/profile.d)

# install systemd units
install(FILES
    ${systemd_units}
    ${systemd_distro_units}
    ${systemd_machine_units}
    ${systemd_in_units}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/systemd/system)

# install temp files
install(FILES
    ${systemd_tmpfile}
    ${systemd_in_tmpfile}
    DESTINATION ${WEBOS_INSTALL_SYSCONFDIR}/tmpfiles.d)
