#!/bin/bash

gcc -o test1 test1.c

echo "Running test with normal output..."
./test1 -normal

echo "Running test with fflush output..."
./test1 -fflush

echo "Running test with newline output..."
./test1 -n

echo "Running test with normal output redirection..."
./test1 -redirect_normal

echo "Running test with fflush output redirection..."
./test1 -redirect_fflush

echo "Running test with newline output redirection..."
./test1 -redirect_n

echo "Running test with all options..."
./test1 -normal -fflush -n -redirect_normal -redirect_fflush -redirect_n