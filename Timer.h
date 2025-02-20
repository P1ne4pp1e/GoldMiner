#ifndef TIMER
#define TIMER

#include <iostream>
#include <chrono>
#include <thread>

class Timer {
public:
    Timer() : start_time(std::chrono::high_resolution_clock::now()), paused(false) {}

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        paused = false;
    }

    void pause() {
        if (!paused) {
            pause_time = std::chrono::high_resolution_clock::now();
            paused = true;
        }
    }

    void resume() {
        if (paused) {
            auto now = std::chrono::high_resolution_clock::now();
            start_time += now - pause_time;
            paused = false;
        }
    }

    double elapsed() const {
        auto end_time = paused ? pause_time : std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end_time - start_time).count();
    }

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
        pause_time = std::chrono::time_point<std::chrono::high_resolution_clock>();
        paused = false;
    }


private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> pause_time;
    bool paused;
};

void spinWait(double nanoseconds) {
    auto start = std::chrono::high_resolution_clock::now();
    auto target = start + std::chrono::nanoseconds(static_cast<long long>(nanoseconds));

    while (std::chrono::high_resolution_clock::now() < target) {
        // 自旋等待
    }
}

#endif