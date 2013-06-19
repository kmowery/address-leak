#!/bin/bash

if [ ! -d "llvm-3.2" ]; then
  echo "Please run this script in the directory containing 'llvm-3.2/'."
  exit 1
fi

echo "Building LLVM 3.2 for OS X 10.8.4 with XCode 4.6.3."
echo "  (might need tweaks for other platforms)"
echo "================================================================================"

set -x

mkdir -p llvm-build
cd llvm-build
../llvm-3.2/configure --enable-libcpp --with-c-include-dirs=/usr/lib/c++/v1/:/usr/include:.
make -j4

