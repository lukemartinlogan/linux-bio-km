#!/bin/bash

#Environment variables
#LOG_DIR: the location of the directory containing the test logs

STATS_PY=$1
SIZE_MB=$2

python3 ${STATS_PY} ${LOG_DIR} ${SIZE_MB}