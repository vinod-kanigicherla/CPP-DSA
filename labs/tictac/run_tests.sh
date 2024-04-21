#!/bin/bash

PROGRAM=./game-check

TEST_DIR=./data

for testcase in "$TEST_DIR"/*.ttt
do
    echo "Running test case: $testcase"
    cat "$testcase" | $PROGRAM
    echo "Test case completed: $testcase"
    echo "--------------------------------"
done
