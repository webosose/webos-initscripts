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

#include <fstream>
#include <dirent.h>
#include <stdlib.h>

#include <systemd/sd-daemon.h>
#include <systemd/sd-event.h>

#include "Systemd.h"
#include "Util.h"
#include "Logger.h"

const std::string Systemd::SYSTEMD_CONFIG_PATH = "/lib/systemd/system/";

Systemd::Systemd() {
  m_state = "READY=1\n"
            "STATUS=initctl notifies ready event";
}

Systemd::~Systemd() {

}

bool Systemd::notify(string name) {
  pid_t pid = getPid(name);
  if (pid <= 0) {
    g_logger.write("[FATAL] Negative PID");
    return false;
  }

  char debug[256];
  snprintf(debug, sizeof(debug), "[DEBUG] name(%s) / pid(%d)", name.c_str(), pid);
  g_logger.write(debug);

  if (sd_pid_notify(pid, 0, m_state.c_str()) <= 0) {
    g_logger.write("[FATAL] Failed in sd_pid_notify");
    return false;
  }
  return true;
}

bool Systemd::startUnit(string name, bool isBlock) {
    std::string unitFilePath = SYSTEMD_CONFIG_PATH + name;
    g_logger.write("[INFO] UNIT_PATH : " + unitFilePath);

    std::ifstream unitStream(unitFilePath.c_str());
    if (!unitStream.good()) {
        g_logger.write("[FATAL] Cannot find unit");
        return false;
    }

    std::string command = "systemctl start ";

    if (!isBlock)
        command += "--no-block ";
    command += name;

    std::string result = Util::exec(command);
    return true;
}

pid_t Systemd::getPid(string processName)
{
  pid_t pid = -1;

  // Open the /proc directory
  DIR* dir = opendir("/proc");
  if (dir == NULL)
    return -1;

  // Enumerate all entries in directory until process found
  struct dirent* entry;
  while (pid < 0 && (entry = readdir(dir))) {
    // Skip non-numeric entries
    int id = atoi(entry->d_name);
    if (id <= 0) continue;

    // Read contents of virtual /proc/{pid}/cmdline file
    string cmdlinePath = string("/proc/") + entry->d_name + "/cmdline";
    ifstream cmdlineStream(cmdlinePath.c_str());
    string cmdline;
    getline(cmdlineStream, cmdline);

    // /proc/{pid}/cmdline is empty
    if (cmdline.empty()) continue;

    // Keep first cmdline item which contains the program path
    size_t pos = cmdline.find('\0');
    if (pos != string::npos)
      cmdline = cmdline.substr(0, pos);

    // Keep program name only, removing the path
    pos = cmdline.rfind('/');
    if (pos != string::npos)
      cmdline = cmdline.substr(pos + 1);

    // Compare against requested process name
    if (processName == cmdline)
      pid = id;
  }
  closedir(dir);
  return pid;
}
