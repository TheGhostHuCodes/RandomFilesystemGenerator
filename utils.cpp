// Copyright 2016 Yung-Jin Hu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "utils.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace fs = boost::filesystem;
using namespace std;

void utils::PrintSpaceInfo(const fs::path& path) {
    auto spaceInfo = fs::space(path);
    cout << "Capacity: " << utils::PrettyPrintBytes(spaceInfo.capacity) << endl;
    cout << "Free: " << utils::PrettyPrintBytes(spaceInfo.free) << endl;
    cout << "Available: " << utils::PrettyPrintBytes(spaceInfo.available)
         << endl;
}

string utils::PrettyPrintBytes(const long& nBytes) {
    vector<string> units{" ", " Ki", " Mi", " Gi", " Ti", " Pi", " Ei", " Zi"};
    auto num = static_cast<double>(nBytes);
    for (auto unit : units) {
        if (abs(num) < 1024.0) {
            return std::string(std::to_string(num) + unit + "B");
        }
        num /= 1024.0;
    }
    return std::string(std::to_string(num) + "YiB");
}
