
# Linux BIO KM

The Linux I/O stack introduces multiple overheads that reduce the
performance of every I/O operation. This is a test to compare the
performance of traditional filesystem I/O with that of a kernel
module that calls submit_bio() directly. We include tools for
profiling the Linux I/O stack and for comparing raw performance.

# 2. Dependencies

Linux 4.5+  
cmake 3.10 or higher  
C++17 compiler  
C11 compiler  
trace-cmd  

# 3. Building

cd /path/to/LabStor  
mkdir build  
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX="/path/to/install"  
make -j4  
make install

## 4. Enable HugePages (optional)

### 4-1. Create a HugePage cache

HugPages have been named as a significant way to reduce overheads for large,
sequential I/O in memory mapped files. You can enable HugePages as follows:

#### 4-1-1. Find the HugePage size

You can find the set of support HugePage sizes by running the following:
```
ls /sys/kernel/mm/hugepages
```

See which sizes are supported. Hopefully something between 2MB to 16MB is 
supported. Note: this will show page sizes in KB, not MB.

#### 4-1-2. Edit the kernel boot parameters

For the GRUB bootloader, open the grub config file as follows:

```
sudo gedit /etc/default/grub
```

Find the line that says "GRUB_CMDLINE_LINUX_DEFAULT", and add
the following arguments to the list (without quotations):
* "hugepagesz=S", where S is size of HugePage you want to allocate
    * You can use the following suffixes to indicate scale: [kKmMgG]
    * For example, 2M would represent 2 megabytes
* "hugepages=N", where N is the number of HugePages
 
After that, update the bootloader and reboot:
```
sudo update-grub  
sudo reboot
```

You can run the command below in order to check if the changes were
made:

```
cat /proc/meminfo | grep HugePages
```

SOURCES:
* https://wiki.ubuntu.com/Kernel/KernelBootParameters,
* https://www.kernel.org/doc/Documentation/vm/hugetlbpage.txt


# 5. Tests

## 5-1. Profile different I/O methods

This test allows you to see what happens in the kernel when you call read()/write().
This test depends on trace-cmd.

### 5-1-1. Determine the syscall names

Before we can trace what happens with these system calls, we have to 
figure out their names. In order to do this, run the following
command:  

```
export TEST_FILE="/path/to/wherever"
make trace-all-syscalls
```  
TEST_FILE will be used to perform I/O with by the test. You must set this
environment variable.
  
You can find the system call names as follows:

```
cat trace-all-syscalls.txt | grep sys_open
cat trace-all-syscalls.txt | grep sys_read
cat trace-all-syscalls.txt | grep sys_write
cat trace-all-syscalls.txt | grep sys_close
```

The trace-all-syscalls.txt is located in your working directory.

### 5-1-2. Set environment variables

We must set:
* Which device/file we want to perform I/O with  
* Which directory we want to store the output logs from each test  
* The system calls we want to trace

```
export TEST_FILE="/path/to/whatever..."  
export LOG_DIR="/path/to/log/directory/..." 
export SYS_OPEN=__x64_sys_open  
export SYS_READ=__x64_sys_read   
export SYS_WRITE=__x64_sys_write  
export SYS_CLOSE=__x64_sys_close  
```

### 5-1-3. Get the trace

These will perform 4K I/O and trace the path to perform it.
```
make trace-buffered-read-4K
make trace-direct-read-4K
make trace-buffered-write-4K
make trace-direct-write-4K
``` 
You can use 4K, 64K, 1M and 10M instead of 100M as well.

This will output function graph .txt files that are human-readable to your
LOG_DIR.

### 5-1-4. Parse the trace

This will output a JSON file that aggregates the time measurements from
the function graph to your LOG_DIR (.json.collapsed)

```
make parse-buffered-read-4K
make parse-direct-read-4K
make parse-buffered-write-4K
make parse-direct-write-4K
``` 

Note: this code will only work if the function stack is completely correct.
When profiling very large I/O calls, the stack reproduction will drop
curly braces that result in complications.

### 5-1-5. Prune the trace (optional)

This will output a JSON file that returns only the functions who makes up
at least a THRESHOLD% of the total runtime of its parent function.

```
export THRESHOLD=[some-fraction]  
make prune-buffered-read-4K
make prune-direct-read-4K
make prune-buffered-write-4K
make prune-direct-write-4K
``` 

An example value for THRESHOLD would be .5 or .25. It should be any value
between 0 and 1.

This will output a (.json.collapsed.pruned) file to the LOG_DIR.

## 5-2. Time different I/O methods

We want to bypass as many overheads introduced by the Linux kernel as possible.
In this experiment, we test multiple approaches for putting data on a disk and
reading data from a disk. We perform the following tests:
* Performance of fwrite  
* Performance of fwrite/fflush  
* Performance of fwrite with 2MB HugePages  
* Performance of fwrite/fflush with 2MB HugePages  
* Performance of write with O_DIRECT  
* Performance of write with O_DIRECT and 2MB HugePages  
* Performance of a kernel module that directly calls submit_bio()  

### 5-2-1. Set environment variables

First, we must set which device/file we want to perform I/O with and then
set which directory we want to store the output logs from each test.

```
export TEST_FILE="/path/to/whatever..."  
export LOG_DIR="/path/to/log/directory/..."  
```

NOTE: your log directory MUST end in a trailing slash.

### 5-2-2. Setup the kernel module

```
make build-linux-driver-io-km
make insert-linux-driver-io-km
./mount /dev/[DEVICE]
make remove-linux-driver-io-km
```

Mount uses a device file, such as /dev/sda; don't use partitions such as
/dev/sda1. The KM requires exclusive access to entire drive.

### 5-2-3. Run tests

You can run the following tests for 100M writes:
```
make time-fwrite-100M  
make time-fwrite-flush-100M  
make time-fwrite-huge-100M  
make time-fwrite-flush-huge-100M  
make time-direct-write-100M  
make time-direct-write-huge-100M  
make time-bypass-write-100M
```

And for 100M reads:
```
make time-fread-100M  
make time-fread-flush-100M  
make time-fread-huge-100M  
make time-fread-flush-huge-100M  
make time-direct-read-100M  
make time-direct-read-huge-100M  
make time-bypass-read-100M
```

NOTE: these tests will drop the OSes page cache before each iteration, which
requires root priveliges.

### 5-2-4. Get statistics

This will print out the mean, range, and standard deviation for each test
case.

> make time-transfer-stats-100M 

This will also store a CSV and JSON file in the log directory containing the 
statistics.