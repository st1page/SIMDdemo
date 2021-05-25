#!/bin/bash
#set -x
set -e
set -u
make clean
make

for exec_file in `ls test_*`;
do
    echo "running $exec_file"
    ./$exec_file | tee $exec_file.result
    perf stat -e cache-misses ./$exec_file 2>&1 | tee -a $exec_file.result
done