//
// Created by lukemartinlogan on 10/12/20.
//

#ifndef LINUX_BIO_KM_TIMER_H
#define LINUX_BIO_KM_TIMER_H

#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>

class Timer {
private:
    std::string log_path_;
    std::chrono::steady_clock::time_point t1_;
    std::chrono::steady_clock::time_point t2_;
    double msec_;

public:
    Timer() : msec_(0) {}
    Timer(std::string log_dir, int test_id) {
        SetLogPath(log_dir, test_id);
    }
    void SetLogPath(std::string log_dir, int test_id) {
        if(log_dir.back() == '/') {
            log_path_ = log_dir + "test" + std::to_string(test_id) + ".txt";
        }
        else {
            log_path_ = log_dir + "/" + "test" + std::to_string(test_id) + ".txt";
        }
    }
    void Resume(void) {
        t1_ = std::chrono::steady_clock::now();
    }
    void Pause(void) {
        t2_ = std::chrono::steady_clock::now();
        msec_ += std::chrono::duration_cast<std::chrono::duration<double>>(t2_ - t1_).count()*1000;
    }
    void Reset(void) {
        msec_ = 0;
    }
    void AddNsec(unsigned long long ns) {
        msec_ += ((double)(ns))/1000000;
    }
    double msec(void) {
        return msec_;
    }
    void Append(void) {
        FILE *log = fopen(log_path_.c_str(), "a+");
        if(log == NULL) {
            std::cout << "Could not open log" << std::endl;
            exit(1);
        }
        fseek(log, 0, SEEK_END);
        std::string time = std::to_string(msec_) + "\n";
        int cnt = fwrite(time.c_str(), 1, time.size(), log);
        if(cnt != time.size()) {
            std::cout << "Did not append to log" << std::endl;
            exit(1);
        }
        fclose(log);
    }
};

#endif //LINUX_BIO_KM_TIMER_H
