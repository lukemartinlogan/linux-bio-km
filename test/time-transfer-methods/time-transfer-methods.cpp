
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <stddef.h>
#include <sys/mman.h>
#include <linux/mman.h>
#include <time-linux-driver-io-um.h>

class Timer {
private:
    std::string log_path_;
    std::chrono::steady_clock::time_point t1_;
    std::chrono::steady_clock::time_point t2_;
    double msec_ = 0;

public:
    Timer(std::string log_dir, std::string test_id) {
        if(log_dir.back() == '/') {
            log_path_ = log_dir + test_id + ".txt";
        }
        else {
            log_path_ = log_dir + "/" + test_id + ".txt";
        }
    }

    void Start(void) {
        t1_ = std::chrono::steady_clock::now();
    }
    void End(void) {
        t2_ = std::chrono::steady_clock::now();
    }
    void CalcDiff(void) {
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2_ - t1_);
        msec_ = time_span.count()*1000;
    };
    void SetNsec(ktime_t ns) {
        msec_ = ((double)(ns))/1000000;
    }
    double msec(void) {
        return msec_;
    }

    void Append(void) {
        FILE *log = fopen(log_path_.c_str(), "a+");
        if(log == NULL) {
            printf("Could not open log\n");
            exit(1);
        }
        fseek(log, 0, SEEK_END);
        std::string time = std::to_string(msec_) + "\n";
        int cnt = fwrite(time.c_str(), 1, time.size(), log);
        if(cnt != time.size()) {
            printf("Did not append to log\n");
            exit(1);
        }
        fclose(log);
    }
};

void test0(size_t filesz, char *path, char *log_dir)
{
    Timer t(log_dir, "test0");
    char *buffer = (char*)aligned_alloc(4096, filesz);
    if(buffer == NULL) {
        printf("Could not allocate memory (test0)\n");
        exit(1);
    }
    memset(buffer, 0, filesz);

    FILE *f = fopen(path, "w");
    if(f == NULL) {
        printf("Could not open file (test0)\n");
        exit(1);
    }
    t.Start();
    int cnt = fwrite(buffer, 1, filesz, f);
    if(cnt != filesz) {
        printf("Could not write to file (test0)\n");
        exit(1);
    }
    t.End();
    fclose(f);
    free(buffer);

    t.CalcDiff();
    printf("Time [test=0]: %lf msec\n", t.msec());
    t.Append();
}

void test1(size_t filesz, char *path, char *log_dir)
{
    Timer t(log_dir, "test1");
    char *buffer = (char*)aligned_alloc(4096, filesz);
    if(buffer == NULL) {
        printf("Could not allocate memory (test1)\n");
        exit(1);
    }
    memset(buffer, 0, filesz);

    FILE *f = fopen(path, "w");
    if(f == NULL) {
        printf("Could not open file (test1)\n");
        exit(1);
    }
    t.Start();
    int cnt = fwrite(buffer, 1, filesz, f);
    if(cnt != filesz) {
        printf("Could not write to file (test1)\n");
        exit(1);
    }
    fclose(f);
    t.End();
    free(buffer);

    t.CalcDiff();
    printf("Time [test=1]: %lf msec\n", t.msec());
    t.Append();
}

void test2(size_t filesz, char *path, char *log_dir)
{
    Timer t(log_dir, "test2");
    char *buffer = (char*)mmap(NULL, filesz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    if(buffer == MAP_FAILED) {
        perror("Could not allocate memory (test2)\n");
        exit(1);
    }
    memset(buffer, 0, filesz);

    FILE *f = fopen(path, "w");
    if(f == NULL) {
        printf("Could not open file (test2)\n");
        exit(1);
    }
    t.Start();
    int cnt = fwrite(buffer, 1, filesz, f);
    if(cnt != filesz) {
        printf("Could not write to file (test2)\n");
        exit(1);
    }
    t.End();
    fclose(f);
    munmap(buffer, filesz);

    t.CalcDiff();
    printf("Time [test=2]: %lf msec\n", t.msec());
    t.Append();
}

void test3(size_t filesz, char *path, char *log_dir)
{
    Timer t(log_dir, "test3");
    char *buffer = (char*)mmap(NULL, filesz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    if(buffer == MAP_FAILED) {
        printf("Could not allocate memory (test3)\n");
        exit(1);
    }
    memset(buffer, 0, filesz);

    FILE *f = fopen(path, "w");
    if(f == NULL) {
        printf("Could not open file (test3)\n");
        exit(1);
    }
    t.Start();
    int cnt = fwrite(buffer, 1, filesz, f);
    if(cnt != filesz) {
        printf("Could not write to file (test3)\n");
        exit(1);
    }
    fclose(f);
    t.End();
    munmap(buffer, filesz);

    t.CalcDiff();
    printf("Time [test=3]: %lf msec\n", t.msec());
    t.Append();
}

void test4(size_t filesz, char *path, char *log_dir)
{
    Timer t(log_dir, "test4");
    char *buffer = (char*)aligned_alloc(4096, filesz);
    if(buffer == NULL) {
        printf("Could not allocate memory (test4)\n");
        exit(1);
    }
    memset(buffer, 0, filesz);

    int fd = open(path, O_DIRECT | O_WRONLY);
    if(fd < 0) {
        printf("Could not open file (test4)\n");
        exit(1);
    }
    t.Start();
    int cnt = write(fd, buffer, filesz);
    if(cnt < 0) {
        printf("Could not write to file (test4)\n");
        exit(1);
    }
    close(fd);
    t.End();

    t.CalcDiff();
    printf("Time [test=4]: %lf msec\n", t.msec());
    t.Append();
}

void test5(size_t filesz, char *path, char *log_dir)
{
    Timer t(log_dir, "test5");
    char *buffer = (char*)mmap(NULL, filesz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    if(buffer == MAP_FAILED) {
        printf("Could not allocate memory (test5)\n");
        exit(1);
    }
    memset(buffer, 0, filesz);

    int fd = open(path, O_DIRECT | O_WRONLY);
    if(fd < 0) {
        printf("Could not open file (test5)\n");
        exit(1);
    }
    t.Start();
    int cnt = write(fd, buffer, filesz);
    if(cnt < 0) {
        printf("Could not write to file (test5)\n");
        exit(1);
    }
    close(fd);
    t.End();
    munmap(buffer, filesz);

    t.CalcDiff();
    printf("Time [test=5]: %lf msec\n", t.msec());
    t.Append();
}

void test6(size_t filesz, char *path, char *log_dir)
{
    Timer t(log_dir, "test6");
    char *buffer = (char*)aligned_alloc(4096, filesz);
    if(buffer == NULL) {
        printf("Could not allocate memory (test6)\n");
        exit(1);
    }
    memset(buffer, 0, filesz);

    ktime_t ns;
    init_labstor_syscalls();
    if(write_bypass(path, 0, buffer, filesz, &ns) < 0) {
        printf("Could not complete I/O (test6)");
        exit(1);
    }

    t.SetNsec(ns);
    printf("Time [test=6]: %lf msec\n", t.msec());
    t.Append();
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
    if(argc != 5) {
        printf("Usage: /path/to/time-transfer-methods [test-case] [size [kmg]] [file-path] [log-dir]\n");
        printf("0: fwrite(file)\n");
        printf("1: fwrite(file)/flush\n");
        printf("2: fwrite(file); huge pages\n");
        printf("3: fwrite(file)/flush; huge pages\n");
        printf("4: write(file, O_DIRECT)\n");
        printf("5: write(file, O_DIRECT); huge pages\n");
        printf("6: write_bypass()\n");
        exit(1);
    }

    int test = atoi(argv[1]);
    size_t filesz = to_size(argv[2]);
    char *path = argv[3];
    char *log_dir = argv[4];

    switch(test) {
        case 0: {
            test0(filesz, path, log_dir);
            break;
        }
        case 1: {
            test1(filesz, path, log_dir);
            break;
        }
        case 2: {
            test2(filesz, path, log_dir);
            break;
        }
        case 3: {
            test3(filesz, path, log_dir);
            break;
        }
        case 4: {
            test4(filesz, path, log_dir);
            break;
        }
        case 5: {
            test5(filesz, path, log_dir);
            break;
        }
        case 6: {
            test6(filesz, path, log_dir);
            break;
        }
    }
}