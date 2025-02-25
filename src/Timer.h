#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
#include <thread>

class Timer {
public:
    Timer();
    void start();
    void pause();
    void resume();
    double elapsed() const;
    void reset();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> pause_time;
    bool paused;
};

void spinWait(double nanoseconds);

#endif // TIMER_H
