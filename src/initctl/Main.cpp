// Copyright (c) 2017-2020 LG Electronics, Inc.
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

#include <stdio.h>
#include <iostream>
#include <string>

#include "InitCtl.h"
#include "Logger.h"

#include "Main.h"

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

  bool bootmode = false;
  if (dbgmsg.find("BOOTMODE") != string::npos)
      bootmode = true;

  InitCtl initCtl;
  try {
      initCtl.process(cmdLine, bootmode);
  } catch (const std::exception& e) {
      g_logger.write("[DEBUG] initctl process is failed=Message" + string(e.what()));
  }

  g_logger.write("[DEBUG] EXIT");
  g_logger.endl();
  return 0;
}
