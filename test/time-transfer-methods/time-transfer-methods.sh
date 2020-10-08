#!/bin/bash

#ENVIRONMENT VARS:
#TEST_FILE: the file you will use to perform I/O tests
#LOG_DIR: the directory where you will store output logs

CMD=$1
TEST_CASE=$2
SIZE_IN_MB=$3
NUM_ITER=$4

for ITER in $(seq 1 $NUM_ITER); do
  sudo sync
  sudo sysctl -w vm.drop_caches=3
  sudo ${CMD} ${TEST_CASE} ${SIZE_IN_MB} ${TEST_FILE} ${LOG_DIR}
done