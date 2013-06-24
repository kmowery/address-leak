#!/bin/bash

WEBKIT_DIR="WebKit-r151611"

if [ ! -d "llvm-build" ]; then
  echo "Please run this script in the directory containing 'llvm-build/'."
  exit 1
fi

if [ ! -d "llvm-3.2" ]; then
  echo "Please run this script in the directory containing 'llvm-3.2/'."
  exit 1
fi

if [ ! -d ${WEBKIT_DIR} ]; then
  echo "Please run this script in the directory containing '${WEBKIT_DIR}/'."
  exit 1
fi

CLANG=`pwd`/llvm-build/Release+Asserts/bin/clang
SCANBUILD=`pwd`/llvm-3.2/tools/clang/tools/scan-build/scan-build

ANALYSIS_DIR=`pwd`/analysis



if [ ! -e ${CLANG} ]; then
  echo "Can't find clang!"
  echo "Looked for:"
  echo "  ${CLANG}"
  echo
  echo "Please build LLVM+clang before running this script."
  echo
  exit 1
fi

if [ ! -e ${SCANBUILD} ]; then
  echo "Can't find scan-build!"
  echo "Looked for:"
  echo "  ${SCANBUILD}"
  echo
  echo "Please build LLVM+clang before running this script."
  echo
  exit 1
fi

if [ ! -d ${ANALYSIS_DIR} ]; then
  mkdir -p ${ANALYSIS_DIR}
fi

if [ -d ${WEBKIT_DIR}/WebKitBuild/ ]; then
  echo "================================================================================"
  echo "Cleaning WebKit"
  echo "================================================================================"
  set -x
  rm -r ${WEBKIT_DIR}/WebKitBuild/
  set +x
fi

echo "================================================================================"
echo "Building WebKit"
echo "================================================================================"

set -x

cd ${WEBKIT_DIR}
${SCANBUILD} -v -v -v -o ${ANALYSIS_DIR} --use-cc=${CLANG} --use-c++=${CLANG} --use-analyzer=${CLANG} ./Tools/Scripts/build-webkit -verbose

