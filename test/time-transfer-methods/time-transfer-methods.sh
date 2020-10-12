#!/bin/bash

#ENVIRONMENT VARS:
#TEST_FILE: the file you will use to perform I/O tests
#LOG_DIR: the directory where you will store output logs

CMD=$1
TEST_ID=$2
INTERFACE=$3
RW=$4
BUFTYPE=$5
REQ_SIZE=$6
ITER=$7
REPS=$8

for REP in $(seq 1 ${REPS}); do
  sudo sync
  sudo sysctl -w vm.drop_caches=3
  sudo ${CMD} ${TEST_ID} ${INTERFACE} ${RW} ${BUFTYPE} ${REQ_SIZE} ${ITER} ${TEST_FILE} ${LOG_DIR}
done