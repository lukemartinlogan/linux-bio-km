//
// Created by lukemartinlogan on 10/12/20.
//

#ifndef LINUX_BIO_KM_POSIXCLIENT_H
#define LINUX_BIO_KM_POSIXCLIENT_H

#include <iostream>
#include <string>
#include "FileClient.h"
#include <unistd.h>
#include <fcntl.h>

class PosixClient : public FileClient {
private:
    int fd_;
public:
    PosixClient(std::string path, BufferType btype, size_t req_size, char val, std::string log_dir, int test_id) : FileClient(path, btype, req_size, val, log_dir, test_id) {
        fd_ = open(path.c_str(), O_DIRECT | O_RDWR);
        if(fd_ < 0) {
            std::cout << "Could not open file: " << path << std::endl;
            exit(1);
        }
    }

    ~PosixClient() {
        close(fd_);
    }

    void Read(size_t off, size_t size) {
        lseek(fd_, off, SEEK_SET);
        t_.Resume();
        int cnt = read(fd_, buffer_.Get(), req_size_);
        t_.Pause();

        if(cnt != req_size_) {
            std::cout << "Could not read from file: " << path_ << std::endl;
            exit(1);
        }
    }

    void Write(size_t off, size_t size) {
        lseek(fd_, off, SEEK_SET);
        t_.Resume();
        int cnt = write(fd_, buffer_.Get(), req_size_);
        t_.Pause();

        if(cnt != req_size_) {
            std::cout << "Could not write to file: " << path_ << std::endl;
            exit(1);
        }
    }
};

#endif //LINUX_BIO_KM_POSIXCLIENT_H
