#!/bin/sh

make || exit $?
cat /proc/cpuinfo | sed '/^$/,$d'
echo "~~~~~~~~~~~~~~~~~~~~~~~~~"
./fptest | column -t -s"`printf '\t'`"
