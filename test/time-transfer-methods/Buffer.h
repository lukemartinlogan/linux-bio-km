//
// Created by lukemartinlogan on 10/12/20.
//

#ifndef LINUX_BIO_KM_BUFFER_H
#define LINUX_BIO_KM_BUFFER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <linux/mman.h>

enum class BufferType {
    kMalloc, kHugePages
};

class Buffer {
private:
    char *buffer_;
    void Malloc(size_t size, char value) {
        buffer_ =  (char*)aligned_alloc(4096, size);
        if(buffer_ == NULL) {
            std::cout << "Could not allocate memory\n";
            exit(1);
        }
        memset(buffer_, value, size);
    }
    void HugePages(size_t size, char value) {
        char *buffer = (char*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
        if(buffer == MAP_FAILED) {
            std::cout << "Could not allocate memory\n";
            exit(1);
        }
        memset(buffer_, value, size);
    }

public:
    Buffer() : buffer_(nullptr) {}
    Buffer(BufferType type, size_t size, char value) {
        Alloc(type, size, value);
    }
    ~Buffer() {
        if(buffer_) {
            free(buffer_);
        }
    }
    void Alloc(BufferType type, size_t size, char value) {
        switch(type) {
            case BufferType::kMalloc: {
                Malloc(size, value);
                break;
            }
            case BufferType::kHugePages: {
                HugePages(size, value);
                break;
            }
        }
    }
    char *Get() { return buffer_; }
};

#endif //LINUX_BIO_KM_BUFFER_H
