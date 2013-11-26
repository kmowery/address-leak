#!/bin/bash

# DEBUG
#scandbg=1
# DEBUG

test -z "$scanlog" && scanlog="/tmp/scan.log"

# data logging
log()
{
	printf '%s\n' "$*" >> "$scanlog"
}

# initial log
log C "`basename "$0"`" "$@"

# remove scan directory
PATH="${PATH#"`dirname "$0"`":}"

# retrieve arguments array
args=("$@")

# verify we are comping c or c++
for i in "${!args[@]}"
do
	arg="${args[$i]}"
	test -z "${arg%%*.c}" && { cmd=clang ; break ; }
	test -z "${arg%%*.cpp}" && { cmd=clang++ ; break ; }
	test -z "${arg%%*.cxx}" && { cmd=clang++ ; break ; }
	arg=""
done

# no input indicates thsi is not a compilation step we car about
test -z "$arg" && { test "$scandbg" && log S "skipping, no input" ; "`basename "$0"`" "$@" ; exit $? ; }

# set input
input="$arg"
test "$scandbg" && log I "input file '$input'"

# retrieve output argument index
for i in "${!args[@]}"
do
	arg="${args[$i]}"
	test -z "${arg%%-o*}" && break
	arg=""
done

# verify we found an output file path
test -z "$arg" && { log E "no output file name" ; "`basename "$0"`" "$@" ; exit $? ; }

# set output
output="${arg#-o}"
test -z "$output" && { i=$(($i+1)) ; output="${args[$i]}" ; }
test "$scandbg" && log I "output file '$output'"

# replace output with llvm file
args[$i]="${args[$i]%.o}.llvm"
llvm="${args[$i]#-o}"

# try building llvm
"$cmd" -emit-llvm "${args[@]}" && ch="B" || ch="F"
log $ch "$cmd" -emit-llvm "${args[@]}"

# execute gcc
"`basename "$0"`" "$@"
