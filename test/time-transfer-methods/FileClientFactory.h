//
// Created by lukemartinlogan on 10/12/20.
//

#ifndef LINUX_BIO_KM_FILECLIENTFACTORY_H
#define LINUX_BIO_KM_FILECLIENTFACTORY_H

#include "FileClient.h"
#include "PosixClient.h"
#include "KMClient.h"
#include <memory>
#include <string>

enum class FileClientType {
    kPosixClient, kKMClient
};

class FileClientFactory {
public:
    static std::shared_ptr<FileClient> Get(FileClientType type, std::string path, BufferType btype, size_t req_size, char value, std::string log_dir, int test_id) {
        switch(type) {
            case FileClientType::kPosixClient: {
                return std::make_shared<PosixClient>(path, btype, req_size, value, log_dir, test_id);
            }
            case FileClientType::kKMClient: {
                return std::make_shared<KMClient>(path, btype, req_size, value, log_dir, test_id);
            }
        }
        return nullptr;
    }
};

#endif //LINUX_BIO_KM_FILECLIENTFACTORY_H
