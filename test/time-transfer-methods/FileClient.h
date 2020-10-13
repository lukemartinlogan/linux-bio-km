//
// Created by lukemartinlogan on 10/12/20.
//

#ifndef LINUX_BIO_KM_FILECLIENT_H
#define LINUX_BIO_KM_FILECLIENT_H

#include "timer.h"
#include "Buffer.h"

class FileClient {
protected:
    Timer t_;
    Buffer buffer_;
    char value_;
    size_t req_size_;
    std::string path_;

public:
    FileClient(std::string path, BufferType btype, size_t req_size, char val, std::string log_dir, std::string test_id) : path_(path), value_(val), req_size_(req_size), buffer_(btype, req_size, val), t_(log_dir, test_id) {}
    virtual void Read(size_t off, size_t size) = 0;
    virtual void Write(size_t off, size_t size) = 0;
    void LogTime() {
        t_.Append();
    }
};

#endif //LINUX_BIO_KM_FILECLIENT_H
