// Copyright (c) 2018 LG Electronics, Inc.
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

#include "Stop.h"
#include "Logger.h"
#include "Util.cpp"
#include "Logger.cpp"

#include <sys/types.h>
#include <stdlib.h>
#include <cstring>

Stop::Stop() {

}

Stop::~Stop() {

}

void Stop::process(vector<string>& cmdLine) {
  g_logger.write("[DEBUG] processing stop ");

  if (cmdLine.size() != 2) {
    cerr << "Error! wrong parameter count! ex) stop [servicename]" << endl;
    return;
  }

  string cmd = "systemctl stop " + cmdLine[1];
  exec(cmd);
  cout << "stop " << cmdLine[1] << endl;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> cmdLine;
  string dbgmsg = "[DEBUG] COMMAND : ";

  for (int index = 0; index < argc; index++) {
    cmdLine.emplace_back(argv[index]);
    dbgmsg += argv[index];
    dbgmsg += " ";
  }

  g_logger.write(dbgmsg);

  Stop stop;
  stop.process(cmdLine);

  g_logger.write("[DEBUG] EXIT");
  g_logger.endl();

  return 0;
}
