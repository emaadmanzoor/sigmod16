#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# first compile the solution
./compile.sh

# then compile the test harness
cd ${DIR}/test-harness
make harness

# then test the executable
./harness init-file.txt workload-file.txt result-file.txt ../src/apsp.py
