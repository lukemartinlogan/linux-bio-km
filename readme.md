
# Linux BIO KM

The Linux I/O stack introduces multiple overheads that reduce the
performance of every I/O operation. This is a test to compare the
performance of traditional filesystem I/O with that of a kernel
module that calls submit_bio() directly. We include tools for
profiling the Linux I/O stack and for comparing raw performance.

# 2. Dependencies

Linux 4.15+  
cmake 3.10 or higher  
C++17 compiler  
C11 compiler  
trace-cmd  

# 3. Building

```
cd /path/to/linux-bio-km   
mkdir build  
cd build
cmake ../
make -j4  
```

## 4. Enable HugePages (optional)

HugPages have been named as a significant way to reduce overheads for large,
sequential I/O in memory mapped files. You can enable HugePages as follows:

### 4-1. Find the HugePage size

You can find the set of support HugePage sizes by running the following:
```
ls /sys/kernel/mm/hugepages
```

See which sizes are supported. Hopefully something between 2MB to 16MB is 
supported. Note: this will show page sizes in KB, not MB.

### 4-2. Edit the kernel boot parameters

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

### 5-1-1. Set environment variables

We must set:
* Which device/file we want to perform I/O with  
* Which directory we want to store the output logs from each test  

```
export TEST_FILE="/path/to/whatever..."  
export LOG_DIR="/path/to/log/directory/..." 
```

### 5-1-2. Get the trace

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

### 5-1-3. Parse the trace

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

### 5-1-4. Prune the trace (optional)

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
reading data from a disk.

### 5-2-1. Set environment variables

First, we must set which device/file we want to perform I/O with and then
set which directory we want to store the output logs from each test.

```
export TEST_FILE="/path/to/whatever..."  
export LOG_DIR="/path/to/log/directory/..."  
```

### 5-2-2. Setup the kernel module

```
make build-km
make insert-km
sudo ./mount /dev/[DEVICE]
make remove-km
```

Mount uses a device file, such as /dev/sda; don't use partitions such as
/dev/sda1. The KM requires exclusive access to entire drive.

### 5-2-3. Run tests

You can run the following tests for 100M writes:
```
make time-direct-write-100M  
make time-direct-write-huge-100M  
make time-bypass-write-100M
```

And for 100M reads:
```
make time-direct-read-100M  
make time-direct-read-huge-100M  
make time-bypass-read-100M
```

You can verify the correctness of the KM as follows:
```
sudo ./verify-write ${TEST_FILE} 0B 100M 8
sudo dd if=/dev/zero of=${TEST_FILE} bs=100M count=1
```
The bypass test will write the value 8 to the first 100M of the device. 

NOTE: these tests will drop the OSes page cache before each iteration, which
requires root priveliges.
    
NOTE: The kernel module will break if you use too large of a block size.
No more than 100M since kernel can only alloc first 4GB of RAM. 

### 5-2-4. Get statistics

This will print out the mean, range, and standard deviation for each test
case.

> make time-transfer-stats-100M 

This will also store a CSV and JSON file in the log directory containing the 
statistics.