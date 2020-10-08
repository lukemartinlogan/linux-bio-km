
#include <fcntl.h>
#include <unistd.h>
#include <string>

int main(int argc, char **argv)
{
    if(argc != 2) {
        printf("USAGE: /path/to/trace-posix-syscalls [TEST_FILE]\n");
        exit(1);
    }

    char *test_file = argv[1];
    int fd = open(test_file, O_DIRECT | O_CREAT | O_RDWR);
    if(fd < 0) {
        perror("Could not open file");
        exit(1);
    }
    char *buf = (char*)aligned_alloc(4096, 4096);

    lseek(fd, 0, SEEK_SET);
    if(write(fd, buf, 4096) < 0) {
        perror("Could not call write to file");
        exit(1);
    }
    lseek(fd, 0, SEEK_SET);
    if(read(fd, buf, 4096) < 0) {
        perror("Could not call read to file");
        exit(1);
    }

    close(fd);
    remove("test-posix.txt");
}