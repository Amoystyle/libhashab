#!/bin/sh

# Compile the 32 bit wrapper in 32 bit mode
gcc -o libhashab32_wrapper libhashab32_wrapper.c -ldl -fno-stack-protector -m32

# Build the libhashab.so library
gcc -c -fpic libhashab.c
gcc -shared -o libhashab.so libhashab.o
