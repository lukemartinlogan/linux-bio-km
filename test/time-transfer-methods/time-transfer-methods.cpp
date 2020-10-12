
#include <cstdio>
#include "FileClientFactory.h"

void SequentialRead(std::shared_ptr<FileClient> &client, size_t req_size, size_t iter) {
    std::cout << iter << std::endl;
    for(size_t i = 0; i < iter; ++i) {
        client->Read(i*req_size, req_size);
    }
    client->LogTime();
}

void SequentialWrite(std::shared_ptr<FileClient> &client, size_t req_size, size_t iter) {
    for(size_t i = 0; i < iter; ++i) {
        client->Write(i*req_size, req_size);
    }
    client->LogTime();
}

size_t to_size(char *num)
{
    int len = strlen(num);
    if(num[len-1] == 'k' || num[len-1] == 'K') {
        return (size_t)atoi(num)*(1ull<<10);
    }
    else if(num[len-1] == 'm' || num[len-1] == 'M') {
        return (size_t)atoi(num)*(1ull<<20);
    }
    else if(num[len-1] == 'g' || num[len-1] == 'G') {
        return (size_t)atoi(num)*(1ull<<30);
    }
    else if(num[len-1] == 'b' || num[len-1] == 'B') {
        return (size_t)atoi(num);
    }

    printf("Invalid integer type\n");
    exit(1);
}

int main(int argc, char **argv)
{
    if(argc != 9) {
        printf("Usage: /path/to/time-transfer-methods [test-id] [interface] [rw] [buffer] [size [kmg]] [iter] [file-path] [log-dir]\n");
        exit(1);
    }

    int test = atoi(argv[1]);
    FileClientType file_client_type = static_cast<FileClientType>(atoi(argv[2]));
    int rw = atoi(argv[3]);
    BufferType buf_type = static_cast<BufferType>(atoi(argv[4]));
    size_t req_size = to_size(argv[5]);
    size_t iter = atoi(argv[6]);
    std::string path = argv[7];
    std::string log_dir = argv[8];
    std::shared_ptr<FileClient> client = FileClientFactory::Get(file_client_type, path, buf_type, req_size, test, log_dir, test);

    std::cout << req_size << std::endl;
    std::cout << iter << std::endl;
    std::cout << rw << std::endl;
    switch(rw) {
        case 0: {
            SequentialRead(client, req_size, iter);
            break;
        }
        case 1: {
            SequentialWrite(client, req_size, iter);
            break;
        }
    }
}