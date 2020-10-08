#!/bin/bash

#Environment Vars:
#TEST_FILE

DEPTH=$1
CMD=$2
OUT=$3

echo "Making function graph of depth ${DEPTH}"
echo "Using command: ${CMD}"

sudo sync
sudo sysctl -w vm.drop_caches=3

sudo trace-cmd record --max-graph-depth ${DEPTH} -p function_graph -g ${SYS_OPEN} -g ${SYS_READ} -g ${SYS_WRITE} -g ${SYS_CLOSE} -F ${CMD} ${TEST_FILE}
sudo trace-cmd report > $OUT 
