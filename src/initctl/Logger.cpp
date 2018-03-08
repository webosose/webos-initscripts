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

#include <time.h>
#include <unistd.h>

#include "Logger.h"
#include "Main.h"

Logger g_logger;

Logger::Logger()
{
    fileStream.open(PATH_LOG_FILE, std::ofstream::out | std::ofstream::app);
}

Logger::~Logger()
{
    fileStream.close();
}

void Logger::write(std::string message)
{
    static char buffer[256];
    struct timespec now;

    if (clock_gettime(CLOCK_MONOTONIC, &now) == -1) {
        std::cout << "cannot get system clock" << std::endl;
        return;
    }
    if (!fileStream.is_open()) {
        std::cout << "file open error " << PATH_LOG_FILE << std::endl;
        return;
    }

    sprintf(buffer, "[%lld.%.9ld] %s\n", (long long)now.tv_sec, now.tv_nsec, message.c_str());
    fileStream << buffer;
}

void Logger::endl()
{
    if (!fileStream.is_open()) {
        std::cout << "file open error " << PATH_LOG_FILE << std::endl;
        return;
    }
    fileStream << std::endl;
}
