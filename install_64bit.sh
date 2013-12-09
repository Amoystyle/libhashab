#!/bin/sh

mkdir -p /usr/lib/x86_64-linux-gnu/libgpod
mkdir -p /usr/lib64/libgpod/
cp libhashab32.so /usr/lib/x86_64-linux-gnu/libgpod/libhashab32.so
cp libhashab32_wrapper /usr/lib/x86_64-linux-gnu/libgpod/libhashab32_wrapper
cp libhashab64.so /usr/lib/x86_64-linux-gnu/libgpod/libhashab.so
cp libhashab32.so /usr/lib64libgpod/libhashab32.so
cp libhashab32_wrapper /usr/lib64/libgpod/libhashab32_wrapper
cp libhashab64.so /usr/lib64/libgpod/libhashab.so

