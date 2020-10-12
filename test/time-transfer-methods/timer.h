//
// Created by lukemartinlogan on 10/12/20.
//

#ifndef LINUX_BIO_KM_TIMER_H
#define LINUX_BIO_KM_TIMER_H

#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>
#include <list>
#include <sstream>

class Timer {
private:
    std::string log_path_;
    std::chrono::steady_clock::time_point t1_;
    std::chrono::steady_clock::time_point t2_;
    std::list<double> log_;

public:
    Timer() {}
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
    void Start(void) {
        t1_ = std::chrono::steady_clock::now();
    }
    void End(void) {
        t2_ = std::chrono::steady_clock::now();
        double msec = std::chrono::duration_cast<std::chrono::duration<double>>(t2_ - t1_).count()*1000;
        log_.emplace_back(msec);
    }
    void AddNsec(unsigned long long ns) {
        double msec = ((double)(ns))/1000000;
        log_.emplace_back(msec);
    }
    void Append(void) {
        FILE *log = fopen(log_path_.c_str(), "a+");
        if(log == NULL) {
            std::cout << "Could not open log" << std::endl;
            exit(1);
        }
        fseek(log, 0, SEEK_END);
        std::stringstream ss;
        for(double msec : log_) {
            ss << std::to_string(msec) << "\n";
        }
        std::string times = ss.str();
        int cnt = fwrite(times.c_str(), 1, times.size(), log);
        if(cnt != times.size()) {
            std::cout << "Did not append to log" << std::endl;
            exit(1);
        }
        fclose(log);
    }
};

#endif //LINUX_BIO_KM_TIMER_H
