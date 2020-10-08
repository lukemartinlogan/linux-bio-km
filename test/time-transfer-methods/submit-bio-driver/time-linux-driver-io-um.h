
#ifndef LINUX_DRIVER_IO_H
#define LINUX_DRIVER_IO_H

#define NETLINK_USER 31
#define MAX_DEVNAME 32

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned long long ktime_t;

struct km_request {
    int code;
    char dev_name[MAX_DEVNAME];
    size_t sector;
    void *usr_buf;
    size_t length;
    ktime_t time_ns;
};

void init_labstor_syscalls(void);

int mount_dev(char *dev);

int write_bypass(char *dev, size_t sector, void *usr_buf, size_t length, ktime_t *time_ns);

int read_bypass(char *dev, size_t sector, void *usr_buf, size_t length, ktime_t *time_ns);

#ifdef __cplusplus
}
#endif

#endif
