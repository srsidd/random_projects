#!/usr/bin/env bash

cur_dir=${PWD}  # Get current dir
devel_dir="devel"  # Directory in which to look for setup script

while :
do
  # Check if we reached home
  if [ ${cur_dir} == ${HOME} ]; then
    echo "Reached home, devel space not found"
    break
  fi
  # Check if current directory has "devel" subdirectory
  if [ -d "${cur_dir}/devel" ]; then
    source "${cur_dir}/devel/setup.bash"
    echo "sourced"
    break
  fi
  # Go up one directory and repeat
  cur_dir="$(dirname "${cur_dir}")"

done
