// Copyright (c) 2021 LG Electronics, Inc.
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
#include <unistd.h>

#include <iostream>
using namespace std;

int *gp;

int funcC()
{
    cout << "funcC\n";

    cout << "double delete\n";
    delete gp;

    return 0;
}

int funcB()
{
    cout << "funcB\n";

    cout << "delete\n";
    delete gp;

    funcC();

    return 0;
}

int funcA()
{
    cout << "funcA\n";

    cout << "new\n";
    gp = new int[3];

    cout << "assign 100\n";
    gp[0] = 100;
    cout << "gp[0] : " << gp[0] << endl;

    funcB();
    // never return

    cout << "assign 110\n";
    gp[0] = 110;
    cout << "gp[0] : " << gp[0] << endl;

    return 0;
}

int main(void)
{
    cout << "main\n";

    funcA();

    cout << "main exit\n";

    return 0;
}
