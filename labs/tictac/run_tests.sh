#!/bin/bash

# Path to your executable program
PROGRAM=./game-check

# Directory containing your test case files
TEST_DIR=./data

# Loop over all .ttt files in the directory
for testcase in "$TEST_DIR"/*.ttt
do
    echo "Running test case: $testcase"
    cat "$testcase" | $PROGRAM
    echo "Test case completed: $testcase"
    echo "--------------------------------"
done
