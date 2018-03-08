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

#ifndef SYSTEMD_H_
#define SYSTEMD_H_

#include <iostream>
#include <sys/types.h>

using namespace std;

class Systemd {
public:
  static Systemd& getInstance() {
    static Systemd _instance;
    return _instance;
  }

  virtual ~Systemd();

  bool notify(string name);
  bool startUnit(string name, bool isBlock);

private:
  static const std::string SYSTEMD_CONFIG_PATH;

  Systemd();

  pid_t getPid(string processName);

  string m_state;

};

#endif /* SYSTEMD_H_ */
