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
#include "boost/filesystem.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

static std::random_device rd;
static std::mt19937 gen{rd()};

const unsigned int SUCCESS = 0;
const unsigned int ERROR_IN_COMMAND_LINE = 1;
const unsigned int ERROR_UNHANDLED_EXCEPTION = 2;

int main(int argc, char** argv) {
    try {
        po::options_description desc(
            "Random Filesystem Generator: Allowed options");
        // clang-format off
        desc.add_options()
                ("help,h", "produce help message")
                ("size,s", po::value<long>(), "size of file in bytes");
        // clang-format on
        po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if (vm.count("help")) {
                std::cout << desc << std::endl;
                return SUCCESS;
            }
            if (vm.empty()) {
                throw po::error("Please use with program options");
            }

            po::notify(vm);

            auto fileSizeInBytes = vm["size"].as<long>();
            auto cwd = fs::current_path();
            auto uniqueFilename = fs::unique_path();

            std::uniform_int_distribution<unsigned short> dist{
                std::numeric_limits<unsigned char>::min(),
                std::numeric_limits<unsigned char>::max()};

            fs::ofstream randFile(cwd / uniqueFilename,
                                  std::ofstream::out | std::ofstream::binary);

            std::vector<unsigned char> buf;
            std::generate_n(std::back_inserter(buf), fileSizeInBytes,
                            [&dist]() -> unsigned char {
                                return static_cast<unsigned char>(dist(gen));
                            });
            randFile.write(reinterpret_cast<char*>(buf.data()),
                           fileSizeInBytes);
            randFile.close();
            return SUCCESS;
        } catch (po::error& ex) {
            std::cerr << "ERROR: " << ex.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
    } catch (std::exception& ex) {
        std::cerr << "Unhandled exception reached the top of main: "
                  << ex.what() << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
}
