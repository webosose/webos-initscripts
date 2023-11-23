// Copyright (c) 2017-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include <sys/types.h>
#include <sys/types.h>

#include "Environment.h"
#include "InitCtl.h"
#include "Logger.h"
#include "Systemd.h"
#include "Util.h"

map<std::string, std::string> InitCtl::s_blockUnits = {
    { "ime-activate", "maliit-server.service" }
};

map<std::string, std::string> InitCtl::s_notifyUnits = {
    { "ls-hubd-ready", "ls-hubd" },
    { "lsm-ready", "surface-manager" },
    { "activitymanager-ready", "activitymanager" },
    { "settingsservice-ready", "SettingsService" },
    { "pdm-ready", "physical-device-manager" }
};

unordered_map<std::string, std::string> InitCtl::s_noBlockUnits = {
    { "core-boot-done", "webos-cbd.target" },
    { "init-boot-done", "webos-ibd.target" },
    { "datastore-init-start", "webos-dis.target" },
    { "minimal-boot-done", "webos-mbd.target" },
    { "rest-boot-done", "webos-rbd.target" },
    { "boot-done", "webos-bd.target" }
};

InitCtl::InitCtl()
{

}

InitCtl::~InitCtl()
{

}

void InitCtl::process(std::vector<std::string> cmdLine, bool bootmode)
{
    string logicalName;

    if (bootmode) {
        logicalName = cmdLine[cmdLine.size() - 2];
        logicalName.erase(0, 9);
    } else {
        logicalName = cmdLine[cmdLine.size() - 1];
    }

    g_logger.write("[DEBUG] TOUCH : " + logicalName);
    string touchCommand = "/bin/touch /tmp/" + logicalName;
    Util::exec(std::move(touchCommand));

    if (s_blockUnits.end() != s_blockUnits.find(logicalName)) {
        g_logger.write("[INFO] BLOCK UNIT : " + s_blockUnits.find(logicalName)->second);
        Systemd::getInstance().startUnit(s_blockUnits.find(logicalName)->second, true);
    } else if (s_noBlockUnits.end() != s_noBlockUnits.find(logicalName)) {
        g_logger.write("[INFO] NOBLOCK UNIT : " + s_noBlockUnits.find(logicalName)->second);
        Systemd::getInstance().startUnit(s_noBlockUnits.find(logicalName)->second, false);
    } else if (s_notifyUnits.end() != s_notifyUnits.find(logicalName)) {
        string processName = s_notifyUnits.find(logicalName)->second;
        g_logger.write("[INFO] NOTIFY : " + processName);
        Systemd::getInstance().notify(std::move(processName));
    }
}
