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

#include <iostream>
#include <fstream>
#include <random>
#include "boost/program_options.hpp"

namespace po = boost::program_options;

static std::random_device rd;
static std::mt19937 gen{rd()};

int main(int argc, char** argv) {
    po::options_description desc(
        "Random Filesystem Generator: Allowed options");
    // clang-format off
    desc.add_options()
      ("help", "produce help message")
      ("size", po::value<long>(), "size of file in bytes")
    ;
    // clang-format on
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    auto fileSizeInBytes = vm["size"].as<long>();

    std::uniform_int_distribution<unsigned short> dist{
        std::numeric_limits<unsigned char>::min(),
        std::numeric_limits<unsigned char>::max()};
    std::ofstream randFile("random.bin",
                           std::ofstream::out | std::ofstream::binary);

    std::vector<unsigned char> buf;
    std::generate_n(std::back_inserter(buf), fileSizeInBytes,
                    [&dist]() -> unsigned char { return dist(gen); });
    randFile.write(reinterpret_cast<char*>(buf.data()), fileSizeInBytes);
    randFile.close();
    return 0;
}
