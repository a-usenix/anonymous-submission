#!/bin/bash

bench_dir=`ls`

for i in $bench_dir; do
  echo "current module is ${i}"
  echo "cd ${i}"
  cd ${i}
  echo "cur directory is `pwd`"
  echo "Build and Excuting ${i}"
  make flash
  echo "sleep 2m"
  sleep 2m
  cd ../
  echo "done!"
done
