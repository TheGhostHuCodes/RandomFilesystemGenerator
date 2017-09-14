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

#ifndef RANDOMFILESYSTEMGENERATOR_STOPWATCH_H
#define RANDOMFILESYSTEMGENERATOR_STOPWATCH_H

#include <iostream>
#include <chrono>

using namespace std::chrono;

class StopWatch {
  public:
    explicit StopWatch(bool start)
        : _start(system_clock::time_point::min()), _log(std::cout) {
        if (start) {
            Start();
        }
    }

    explicit StopWatch(char const* activity = "StopWatch", bool start = true)
        : _start(system_clock::time_point::min()), _log(std::cout) {
        _activity = activity;
        if (start) {
            Start();
        }
    };

    StopWatch(std::ostream& log, char const* activity = "StopWatch",
              bool start = true)
        : _start(system_clock::time_point::min()), _log(log) {
        _activity = activity;
        if (start) {
            Start();
        }
    }

    // Stop and destroy a stopwatch.
    ~StopWatch() { Stop(); }

    // Clears the timer.
    void Reset() { _start = system_clock::time_point::min(); }

    // Returns true if the timer is running.
    bool IsStarted() const {
        return (_start != system_clock::time_point::min());
    }

    void Start(char const* event_name = "start") {
        _log << _activity << ": " << event_name << std::endl;
        _start = system_clock::now();
    }

    // Stop a running stopwatch, set/return elapsed time.
    unsigned long Stop(char const* event_name = "stop") {
        auto duration = GetMilliseconds();
        _log << _activity << ": " << event_name << ": " << duration << " ms"
             << std::endl;
        return duration;
    }

    // Get the number of milliseconds since the timer was started.
    unsigned long GetMilliseconds() {
        if (IsStarted()) {
            return (unsigned long)(duration_cast<milliseconds>(
                                       system_clock::now() - _start)
                                       .count());
        }
        return 0;
    }

  private:
    system_clock::time_point _start;
    char const* _activity;
    std::ostream& _log;
};
#endif // RANDOMFILESYSTEMGENERATOR_STOPWATCH_H
