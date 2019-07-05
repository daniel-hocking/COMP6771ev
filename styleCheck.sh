#!/bin/bash

# This script must be placed in the root directory of the git repo

if test $# -eq 0
then
  main="./assignments/ev/client.cpp"
  wl_h="./assignments/ev/euclidean_vector.h"
  wl_cpp="./assignments/ev/euclidean_vector.cpp"
  wl_t="./assignments/ev/euclidean_vector_test.cpp"
  clang-format -i "$main" && python cpplint.py "$main"
  clang-format -i "$wl_h" && python cpplint.py "$wl_h"
  clang-format -i "$wl_cpp" && python cpplint.py "$wl_cpp"
  clang-format -i "$wl_t" && python cpplint.py "$wl_t"
else
  for file in "$@"
  do
    clang-format -i "$file" && python cpplint.py "$file"
  done
fi
