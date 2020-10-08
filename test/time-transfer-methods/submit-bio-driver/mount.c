
#include <stdio.h>
#include <stdlib.h>
#include <time-linux-driver-io-um.h>

int main(int argc, char **argv)
{
	if(argc != 2) {
		printf("USAGE: ./mount [path/to/device/file]\n");
		exit(1);
	}
	char *dev = argv[1];
	int code = 0;
	
	printf("Mounting %s\n", dev);
	init_labstor_syscalls();
	code = mount_dev(dev);
	printf("CODE: %d\n", code);
}
