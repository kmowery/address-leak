#!/bin/bash

if [ ! -d "llvm-build" ]; then
  echo "Please run this script in the directory containing 'llvm-build/'."
  exit 1
fi

if [ ! -d "WebKit-r151611" ]; then
  echo "Please run this script in the directory containing 'WebKit-r151611/'."
  exit 1
fi

CLANG=`pwd`/llvm-build/Release+Asserts/bin/clang

if [ ! -e ${CLANG} ]; then
  echo "Can't find the clang compiler!"
  echo "Looked for:"
  echo "  ${CLANG}"
  echo
  echo "Please build LLVM+clang before running this script."
  echo
  exit 1
fi



echo "Building WebKit."
echo "================================================================================"

set -x

cd WebKit-r151611
CC=${CLANG} CXX=${CLANG} ./Tools/Scripts/build-webkit -verbose

