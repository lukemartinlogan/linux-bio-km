//
// Created by lukemartinlogan on 10/12/20.
//

#ifndef LINUX_BIO_KM_KMCLIENT_H
#define LINUX_BIO_KM_KMCLIENT_H

#include <iostream>
#include <string>
#include "FileClient.h"
#include "submit-bio-driver/time-linux-driver-io-um.h"

class KMClient : public FileClient {
private:
    int fd_;
public:
    KMClient(std::string path, BufferType btype, size_t req_size, char val, std::string log_dir, int test_id) : FileClient(path, btype, req_size, val, log_dir, test_id) {
        init_labstor_syscalls();
    }

    void Read(size_t off, size_t size) {
        ktime_t ns;
        if(read_bypass(path_.c_str(), off, buffer_.Get(), size, &ns) < 0) {
            std::cout << "Could not complete write" << std::endl;
            exit(1);
        }
        t_.AddNsec(ns);
    }

    void Write(size_t off, size_t size) {
        ktime_t ns;
        if(write_bypass(path_.c_str(), off, buffer_.Get(), size, &ns) < 0) {
            std::cout << "Could not complete write" << std::endl;
            exit(1);
        }
        t_.AddNsec(ns);
    }
};

#endif //LINUX_BIO_KM_KMCLIENT_H
