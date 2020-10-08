#!/bin/bash

#THIS SCRIPT MUST BE RUN IN THE ROOT USER

#ENVIRONMENT VARS:
#TEST_FILE: the file you will use to perform I/O tests
#LOG_DIR: the directory where you will store output logs
#SYS_READ: the name of the read() syscall
#SYS_WRITE: the name of the write() syscall

TEST_ID=$1
EXEC=$2
TEST_CASE=$3
BS=$4
COUNT=$5

sudo sync
sudo sysctl -w vm.drop_caches=3
sudo trace-cmd record -c --max-graph-depth 0 -p function_graph -g ${SYS_READ} -g ${SYS_WRITE} -F ${EXEC} ${TEST_CASE} ${BS} ${COUNT} ${TEST_FILE}
trace-cmd report >${LOG_DIR}/${TEST_ID}.txt
